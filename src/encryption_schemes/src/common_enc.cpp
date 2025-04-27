#include "common_enc.h"

namespace encryption_schemes {

// Ciphertext implementation
Ciphertext::Ciphertext(
    TTensor& t_a,
    TTensor& t_b,
    pt_shape::PtShape& t_pt_shape,
    global_params_and_state::State& t_state
) : a(t_a), b(t_b), pt_shape(t_pt_shape), state(t_state) {}

Ciphertext Ciphertext::init_from_ct_and_state(
    Ciphertext& ct,
    global_params_and_state::State& t_state
) {
    return Ciphertext(ct.a, ct.b, ct.pt_shape, t_state);
}

void Ciphertext::init(lattica_proto::Ciphertext proto) {
    a = serialization_utils::deser_tensor(proto.a());
    b = serialization_utils::deser_tensor(proto.b());
    pt_shape.init(proto.pt_shape());
    if (proto.has_state()) {
        state = global_params_and_state::State();
        state.value().init(proto.state());
    }
}

lattica_proto::Ciphertext Ciphertext::to_proto(optional<lattica_proto::Ciphertext*> t_proto) {
    lattica_proto::Ciphertext* proto = t_proto ? t_proto.value() : new lattica_proto::Ciphertext();
    serialization_utils::ser_tensor(a, proto->mutable_a());
    serialization_utils::ser_tensor(b, proto->mutable_b());
    lattica_proto::PtShape* pt_shape_proto = proto->mutable_pt_shape();
    pt_shape.to_proto(pt_shape_proto);
    if (state.has_value()) {
        lattica_proto::State* state_proto = proto->mutable_state();
        state.value().to_proto(state_proto);
    }
    return *proto;
}

Ciphertext::Ciphertext(const string& proto_str)
    : Ciphertext() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    lattica_proto::Ciphertext proto;
    proto.ParseFromString(proto_str);
    init(proto);
}

Ciphertext Ciphertext::make_copy(
    optional<TTensor> t_a,
    optional<TTensor> t_b,
    optional<pt_shape::PtShape> t_pt_shape,
    optional<global_params_and_state::State> t_state
) {
    TTensor t_a_ = t_a ? t_a.value() : a;
    TTensor t_b_ = t_b ? t_b.value() : b;
    pt_shape::PtShape t_pt_shape_ = t_pt_shape ? t_pt_shape.value() : pt_shape;
    global_params_and_state::State t_state_ = t_state ? t_state.value() : state.value();
    return Ciphertext(t_a_, t_b_, t_pt_shape_, t_state_);
}

Ciphertext Ciphertext::get_item(at::ArrayRef<at::indexing::TensorIndex> indices) {
    TTensor a_slice = a.index(indices);
    TTensor b_slice = b.index(indices);
    return make_copy(a_slice, b_slice);
}

void Ciphertext::pack_for_transmission() {
    state = nullopt;
}

void Ciphertext::unpack_from_transmission(global_params_and_state::State& t_state) {
    state = t_state;
}

TTensor& Ciphertext::get_a() {
    return a;
}

TTensor& Ciphertext::get_b() {
    return b;
}

void Ciphertext::set_a(const TTensor& t_a) {
    a = t_a;
}

void Ciphertext::set_b(const TTensor& t_b) {
    b = t_b;
}

pt_shape::PtShape& Ciphertext::get_pt_shape() {
    return pt_shape;
}

global_params_and_state::State& Ciphertext::get_state() {
    return state.value();
}

bool Ciphertext::has_state() const {
    return state.has_value();
}

void Ciphertext::set_state(const global_params_and_state::State& t_state) {
    state = t_state;
}

// AbstractEncryptionScheme implementation
std::tuple<TTensor, TTensor> AbstractEncryptionScheme::_sample_randomness(
    context::Context& context,
    global_params_and_state::State& state,
    pt_shape::PtShape& pt_shape,
    TTensorShape additional_dims,
    int n_axis
) {
    std::cout << "AbstractEncryptionScheme::_sample_randomness" << std::endl;

    std::vector<int64_t> rand_dims(pt_shape.get_internal_shape());
    rand_dims.insert(rand_dims.end(), additional_dims.begin(), additional_dims.end());
    rand_dims[3] = context.get_n();

    // Initialize tensor e
    TTensor e = t_eng::empty(rand_dims, T_ENG_FLOAT32_TYPE);
    t_eng::generate_random_normal(e, 0, context.get_err_std());
    e = t_eng::round(e);
    e = e.to(T_ENG_INT_TYPE);
    e = crt_utils::coefs_to_crt_q(context, state, e, n_axis, true);

    std::vector<int64_t> a_shape(rand_dims);
    a_shape.push_back(state.len_q_list());
    TTensor a = t_eng::empty(a_shape);

    for (int i = 0; i < state.len_q_list(); i++) {
        SINGLE_PRECISION q_i = state.q_list().index({i}).item<SINGLE_PRECISION>();
        TTensor a_i = a.index({Ellipsis, i});
        t_eng::generate_random_integers(a_i, 0, q_i, T_ENG_INT_TYPE);
    }

    return std::make_tuple(a, e);
}

std::tuple<TTensor, TTensor> AbstractEncryptionScheme::sample_randomness(
    context::Context& context,
    pt_shape::PtShape& pt_shape,
    optional<global_params_and_state::State> t_state
) {
    global_params_and_state::State state = t_state ? t_state.value() : context.get_state();
    return _sample_randomness(context, state, pt_shape);
}

std::tuple<TTensor, TTensor> AbstractEncryptionScheme::sample_secret_key(
    context::Context& context,
    optional<global_params_and_state::State> t_state
) {
    global_params_and_state::State state = t_state ? t_state.value() : context.get_state();
    TTensor coefs_sk = t_eng::empty({context.get_n()}, T_ENG_INT_TYPE);
    t_eng::generate_random_integers(coefs_sk, 0, 2, T_ENG_INT_TYPE);
    TTensor sk = coefs_sk.clone();
    sk = crt_utils::coefs_to_crt_q(context, state, sk, -2, true);
    return std::make_tuple(sk, coefs_sk);
}

TTensor AbstractEncryptionScheme::_enc(
    context::Context& context,
    global_params_and_state::State& state,
    TTensor& pt,
    TTensor& sk,
    TTensor& a,
    TTensor& e
) {
    std::cout << "AbstractEncryptionScheme::_enc" << std::endl;
    std::logic_error("Not implemented");
    return t_eng::empty({0});
}

TTensor AbstractEncryptionScheme::pack_pt(
    context::Context& context,
    TTensor& pt,
    optional<std::vector<double>> t_pt_scale
) {
    std::logic_error("Not implemented");
    return t_eng::empty({0});
}

std::tuple<TTensor, TTensor> AbstractEncryptionScheme::dec_and_get_error(
    context::Context& context,
    TTensor& sk,
    Ciphertext& ct
) {
    std::logic_error("Not implemented");
    return std::make_tuple(t_eng::empty({0}), t_eng::empty({0}));
}

TTensor AbstractEncryptionScheme::dec(
    context::Context& context,
    TTensor& sk,
    Ciphertext& ct,
    bool convert_to_external
) {
    std::tuple<TTensor, TTensor> res_and_error = dec_and_get_error(context, sk, ct);
    TTensor pt = std::get<0>(res_and_error);
    if (convert_to_external) {
        pt = pt_shape::convert_internal_to_external(pt, ct.get_pt_shape());
    }
    return pt;
}

TTensor AbstractEncryptionScheme::unpack_pt(
    context::Context& context,
    TTensor& pt_packed,
    optional<std::vector<double>> t_pt_scale
) {
    std::logic_error("Not implemented");
    return t_eng::empty({0});
}

TTensor AbstractEncryptionScheme::dec_and_unpack(
    context::Context& context,
    TTensor& sk,
    Ciphertext& ct,
    bool convert_to_external
) {
    std::tuple<TTensor, TTensor> res_and_error = dec_and_get_error(context, sk, ct);
    TTensor pt = std::get<0>(res_and_error);
    pt = unpack_pt(context, pt);
    if (convert_to_external) {
        pt = pt_shape::convert_internal_to_external(pt, ct.get_pt_shape());
    }
    return pt;
}

Ciphertext AbstractEncryptionScheme::apply_mod_switch_down_drop(
    Ciphertext& ct,
    Slice relative_new_indices
) {
    return ct.get_item({"...", relative_new_indices});
}

// AbstractCiphertextInitializer implementation
Ciphertext AbstractCiphertextInitializer::_init_ct(
    context::Context& context,
    TTensor& sk,
    TTensor& pt,
    pt_shape::PtShape& pt_shape,
    optional<global_params_and_state::State> t_state,
    bool is_external
) {
    global_params_and_state::State state = t_state ? t_state.value() : context.get_state();
    if (is_external) {
        pt = pt_shape::convert_external_to_internal(pt, pt_shape);
    }
    TTensor a, e;
    std::tie(a, e) = sample_randomness(context, pt_shape, state);
    TTensor b = _enc(context, state, pt, sk, a, e);
    return Ciphertext(a, b, pt_shape, state);
}

} // namespace encryption_schemes
