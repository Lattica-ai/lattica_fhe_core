#include <ATen/ATen.h>
#include "ckks.h"
#include "mod_ops.h"
#include "num.h"

namespace encryption_schemes {

// CKKS_Ciphertext implementation
CKKS_Ciphertext::CKKS_Ciphertext(
    TTensor& t_a, TTensor& t_b,
    pt_shape::PtShape& t_pt_shape,
    global_params_and_state::State& t_state,
    std::vector<double> t_pt_scale
) : Ciphertext(t_a, t_b, t_pt_shape, t_state) {
    pt_scale = t_pt_scale;
}

Ciphertext CKKS_Ciphertext::init_from_ct_and_state(
    CKKS_Ciphertext& ct,
    global_params_and_state::State& t_state
) {
    CKKS_Ciphertext new_ct = CKKS_Ciphertext(
        ct.get_a(), ct.get_b(), ct.get_pt_shape(), t_state, ct.get_pt_scale());
    return new_ct;
}

void CKKS_Ciphertext::init(lattica_proto::CKKS_Ciphertext proto) {
    Ciphertext::init(proto.ciphertext());
    int pt_scale_size = proto.pt_scale_size();
    for (int i = 0; i < pt_scale_size; i++) {
        pt_scale.push_back(proto.pt_scale(i));
    }
}

lattica_proto::CKKS_Ciphertext CKKS_Ciphertext::to_proto(optional<lattica_proto::CKKS_Ciphertext*> t_proto) {
    lattica_proto::CKKS_Ciphertext* proto = t_proto ? t_proto.value() : new lattica_proto::CKKS_Ciphertext();
    lattica_proto::Ciphertext* ct_proto = proto->mutable_ciphertext();
    Ciphertext::to_proto(ct_proto);
    for (double pt_scale_val : pt_scale)
        proto->add_pt_scale(pt_scale_val);
    return *proto;
}

CKKS_Ciphertext::CKKS_Ciphertext(const string& proto_str) : CKKS_Ciphertext() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    lattica_proto::CKKS_Ciphertext proto;
    proto.ParseFromString(proto_str);
    init(proto);
}

Ciphertext CKKS_Ciphertext::make_copy(
    optional<TTensor> t_a,
    optional<TTensor> t_b,
    optional<pt_shape::PtShape> t_pt_shape,
    optional<global_params_and_state::State> t_state
) {
    Ciphertext new_ct = Ciphertext::make_copy(t_a, t_b, t_pt_shape, t_state);
    return CKKS_Ciphertext(
        new_ct.get_a(), new_ct.get_b(), new_ct.get_pt_shape(), new_ct.get_state(), pt_scale);
}

std::vector<double>& CKKS_Ciphertext::get_pt_scale() {
    return pt_scale;
}

CKKS_Ciphertext _CKKS::init_ct(
    context::Context& context,
    TTensor& sk,
    TTensor& pt,
    pt_shape::PtShape& pt_shape,
    optional<global_params_and_state::State> t_state,
    optional<std::vector<double>> t_pt_scale,
    bool is_external
) {
    Ciphertext ct = AbstractCiphertextInitializer::_init_ct(context, sk, pt, pt_shape, t_state, is_external);
    std::vector<double> pt_scale = t_pt_scale ? t_pt_scale.value() : std::vector<double>(1, context.get_pt_scale());
    return CKKS_Ciphertext(ct.get_a(), ct.get_b(), ct.get_pt_shape(), ct.get_state(), pt_scale);
}

TTensor _CKKS::_enc(
    context::Context& context,
    global_params_and_state::State& state,
    TTensor& pt,
    TTensor& sk,
    TTensor& a,
    TTensor& e
) {
    TTensor sk_a = t_eng::modmul(a, sk, state.q_list(), false);
    pt = pt.to(T_ENG_INT_TYPE);
    pt = mod_utils::to_crt_tensor(state.q_list(), pt);
    pt = crt_utils::coefs_to_crt_q(context, state, pt, -2, false);
    TTensor b = t_eng::modsum(sk_a, e + pt, state.q_list(), true);
    return b;
}

TTensor _CKKS::pack_pt(
    context::Context& context,
    TTensor& pt,
    optional<std::vector<double>> t_pt_scale
) {
    std::vector<double> pt_scale = t_pt_scale ? t_pt_scale.value() : std::vector<double>(1, context.get_pt_scale());

    for (double pt_scale_i : pt_scale) {
        pt = pt * pt_scale_i;
    }

    TTensor flipped_pt = t_eng::flip(pt, {-1});
    auto n = context.get_n();
    pt = t_eng::cat({pt, flipped_pt}, -1);
    pt = pt.to(T_ENG_COMPLEX_TYPE);
    pt = t_eng::ifft(pt, n, -1);

    // Compute the phase: exp(i*pi*j/n).
    c10::complex<double> I(0.0f, 1.0f);
    c10::complex<double> factor_val = I * static_cast<double>(M_PI) / static_cast<double>(n);

    TTensor factor = t_eng::empty({1}, T_ENG_COMPLEX_TYPE);
    factor.index_put_({0}, factor_val);

    TTensor j = t_eng::arange(0, n, 1);
    TTensor j_tensor_complex = j.to(T_ENG_COMPLEX_TYPE);
    TTensor pt_packed = at::exp(factor * j_tensor_complex);

    pt_packed = pt * pt_packed;

    return t_eng::real(pt_packed).round().to(T_ENG_INT_TYPE);
}

std::tuple<TTensor, TTensor> _CKKS::dec_and_get_error(
    context::Context& context,
    TTensor& sk_coefs,
    Ciphertext& ct
) {
    auto& state = ct.get_state();
    sk_coefs = sk_coefs.unsqueeze(-2).unsqueeze(-2);
    sk_coefs = mod_utils::to_crt_tensor(state.q_list(), sk_coefs);
    sk_coefs = t_eng::mod(-sk_coefs, state.q_list());
    TTensor sk = crt_utils::coefs_to_crt_q(context, state, sk_coefs, -2, false).unsqueeze(-3);

    TTensor sk_a = t_eng::modmul(ct.get_a(), sk, state.q_list(), false);
    TTensor pt_crt_scaled = t_eng::modsum(ct.get_b(), sk_a, state.q_list(), false);
    TTensor pt_coefs_scaled = crt_utils::crt_to_coefs_q(context, state, pt_crt_scaled, -2, false);

    const Num& q = state.get_active_q();
    Num half_q = q / 2;
    std::vector<Num> temp_res = mod_utils::from_crt_tensor_to_bigint(state.get_mod_state(), pt_coefs_scaled, q);
    std::vector<int64_t> res_shape = pt_coefs_scaled.sizes().vec();
    res_shape.pop_back();
    TTensor pt_res = t_eng::empty(res_shape, T_ENG_FLOAT_TYPE);
    pt_res = pt_res.reshape({-1});
    at::parallel_for(0, temp_res.size(), 1, [&](int64_t start, int64_t stop) {
        for (int64_t i = start; i < stop; ++i) {
            Num temp_i = temp_res[i];
            if (temp_i > half_q)
                temp_i = temp_i - q;
            pt_res[i] = temp_i.to_double();
        }
    });
    pt_res = pt_res.reshape(res_shape);
    return std::make_tuple(pt_res, t_eng::empty({0}));
}

TTensor _CKKS::unpack_pt(
    context::Context& context,
    TTensor& pt_packed,
    optional<std::vector<double>> t_pt_scale
) {
    std::vector<double> pt_scale = t_pt_scale ? t_pt_scale.value() : std::vector<double>(1, context.get_pt_scale());
    for (size_t i=0; i<pt_scale.size(); i++) {
        pt_packed = pt_packed / pt_scale[i];
    }
    auto n = context.get_n();
    TTensor temp = t_eng::rfft(pt_packed.to(T_ENG_FLOAT_TYPE), n*2, -1);
    temp = temp.index({"...", Slice(1, n, 2)});
    return t_eng::real(temp).contiguous();
}

CKKS_Ciphertext _CKKS::pack_and_init_ct(
    context::Context& context,
    TTensor& sk,
    TTensor& pt,
    pt_shape::PtShape& pt_shape,
    optional<global_params_and_state::State> t_state,
    bool is_external
) {
    if (is_external) {
        pt = pt_shape::convert_external_to_internal(pt, pt_shape);
    }
    pt = pack_pt(context, pt);
    return init_ct(context, sk, pt, pt_shape, t_state,
                 nullopt /* t_pt_scale */, false /* is_external */);
}

TTensor _CKKS::dec_and_unpack(
    context::Context& context,
    TTensor& sk,
    Ciphertext& ct,
    bool convert_to_external
) {
    TTensor pt = dec(context, sk, ct, false /* convert_to_external */);
    pt = unpack_pt(context, pt, dynamic_cast<CKKS_Ciphertext*>(&ct)->get_pt_scale());
    if (convert_to_external) {
        pt = pt_shape::convert_internal_to_external(
            pt, dynamic_cast<CKKS_Ciphertext*>(&ct)->get_pt_shape());
    }
    return pt;
}

TTensor _CKKS::to_default_pt_tensor(TTensor& pt) {
    return pt.to(T_ENG_FLOAT_TYPE);
}


} // namespace encryption_schemes
