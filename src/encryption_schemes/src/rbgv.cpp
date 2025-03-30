#include "ATen/ATen.h"
#include "rbgv.h"
#include "num.h"
#include "plaintext.h"
#include "mod_utils.h"

namespace encryption_schemes {

RBGV_Ciphertext::RBGV_Ciphertext(
    TTensor& t_a,
    TTensor& t_b,
    pt_shape::PtShape& t_pt_shape,
    global_params_and_state::State& t_state,
    int t_correction_factor
) : Ciphertext(t_a, t_b, t_pt_shape, t_state) {
    correction_factor = t_correction_factor;
}

Ciphertext RBGV_Ciphertext::init_from_ct_and_state(
    RBGV_Ciphertext& ct,
    global_params_and_state::State& t_state
) {
    RBGV_Ciphertext new_ct = RBGV_Ciphertext(
        ct.a, ct.b, ct.pt_shape, t_state, ct.correction_factor);
    return new_ct;
}

RBGV_Ciphertext::RBGV_Ciphertext() {}

void RBGV_Ciphertext::init(lattica_proto::RBGV_Ciphertext proto) {
    Ciphertext::init(proto.ciphertext());
    correction_factor = proto.correction_factor();
}

lattica_proto::RBGV_Ciphertext RBGV_Ciphertext::to_proto(
    optional<lattica_proto::RBGV_Ciphertext*> t_proto
) {
    lattica_proto::RBGV_Ciphertext* proto = t_proto ? t_proto.value() : new lattica_proto::RBGV_Ciphertext();
    lattica_proto::Ciphertext* ct_proto = proto->mutable_ciphertext();
    Ciphertext::to_proto(ct_proto);
    proto->set_correction_factor(correction_factor);
    return *proto;
}

RBGV_Ciphertext::RBGV_Ciphertext(string& proto_str) : RBGV_Ciphertext() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    lattica_proto::RBGV_Ciphertext proto;
    proto.ParseFromString(proto_str);
    init(proto);
}

Ciphertext RBGV_Ciphertext::make_copy(
    optional<TTensor> t_a,
    optional<TTensor> t_b,
    optional<pt_shape::PtShape> t_pt_shape,
    optional<global_params_and_state::State> t_state
) {
    Ciphertext new_ct = Ciphertext::make_copy(t_a, t_b, t_pt_shape, t_state);
    return RBGV_Ciphertext(
        new_ct.a, new_ct.b, new_ct.pt_shape, new_ct.state.value(), correction_factor);
}

RBGV_Ciphertext _RBGV::init_ct(
    context::Context& context,
    TTensor& sk,
    TTensor& pt,
    pt_shape::PtShape& pt_shape,
    optional<global_params_and_state::State> t_state,
    optional<std::vector<double>> t_pt_scale,
    bool is_external
) {
    Ciphertext ct = AbstractCiphertextInitializer::_init_ct(
        context, sk, pt, pt_shape, t_state, is_external);
    return RBGV_Ciphertext(ct.a, ct.b, ct.pt_shape, ct.state.value());
}

TTensor _RBGV::_enc(
    context::Context& context,
    global_params_and_state::State& state,
    TTensor& pt,
    TTensor& sk,
    TTensor& a,
    TTensor& e
) {
    auto params = context.params;
    TTensor sk_a = t_eng::modmul(a, sk, state.q_list(), false);
    pt = plaintext::encode_pt(context, pt);
    TTensor e_scaled = t_eng::modmul(e, params.p(), state.q_list());
    pt = crt_utils::coefs_to_crt_q(context, state, pt, -2, true);
    TTensor b = t_eng::modsum(sk_a, e_scaled + pt, state.q_list(), true);
    return b;
}

TTensor _RBGV::pack_pt(
    context::Context& context,
    TTensor& pt,
    optional<std::vector<double>> t_pt_scale
) {
    pt = plaintext::encode_pt(context, pt);
    pt = crt_utils::crt_to_coefs_p(context, pt);
    return pt;
}

RBGV_Ciphertext _RBGV::pack_and_init_ct(
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

std::tuple<TTensor, TTensor> _RBGV::dec_and_get_error(
    context::Context& context,
    TTensor& sk_coefs,
    Ciphertext& ct
) {
    auto params = context.params;
    auto state = ct.state.value();

    sk_coefs = sk_coefs.unsqueeze(-2).unsqueeze(-2);
    sk_coefs = mod_utils::to_crt_tensor(state.q_list(), sk_coefs);
    sk_coefs = t_eng::mod(-sk_coefs, state.q_list());
    TTensor sk = crt_utils::coefs_to_crt_q(context, state, sk_coefs, -2, false).unsqueeze(-3);
    TTensor sk_a = t_eng::modmul(ct.a, sk, state.q_list(), false);
    TTensor temp = t_eng::modsum(ct.b, sk_a, state.q_list(), false);
    temp = crt_utils::crt_to_coefs_q(context, state, temp, -2, false);
    Num q = Num(state.mod_state.active_q);
    Num half_q = q / 2;
    std::vector<Num> temp_res = mod_utils::from_crt_tensor_to_bigint(state.mod_state, temp, q);

    std::vector<int64_t> res_shape = temp.sizes().vec();
    res_shape.pop_back();
    TTensor pt_res = t_eng::empty(res_shape);
    TTensor err = t_eng::empty(res_shape);
    pt_res = pt_res.reshape({-1});
    err = err.reshape({-1});

    for (int i = 0; i < temp_res.size(); i++) {
        Num temp_i = temp_res[i];
        if (temp_i > half_q) {
            temp_i = temp_i - q;
        }
        temp_i = temp_i * dynamic_cast<RBGV_Ciphertext*>(&ct)->correction_factor;
        Num pt_i = temp_i % params.p_np();
        if (pt_i < 0) {
            pt_i = pt_i + params.p_np();
        }
        int pt_res_i;
        pt_i.can_convert_to_int(&pt_res_i);
        pt_res[i] = pt_res_i;

        temp_i = temp_i - pt_i;
        temp_i = temp_i / params.p_np();
        int err_i;
        temp_i.can_convert_to_int(&err_i);
        err[i] = err_i;
    }

    pt_res = pt_res.reshape(res_shape);
    err = err.reshape(res_shape);
    pt_res = plaintext::decode_pt(context, pt_res);
    return std::make_tuple(pt_res, err);
}

TTensor _RBGV::unpack_pt(
    context::Context& context,
    TTensor& pt_packed,
    optional<std::vector<double>> t_pt_scale
) {
    pt_packed = plaintext::encode_pt(context, pt_packed);
    pt_packed = crt_utils::coefs_to_crt_p(context, pt_packed);
    pt_packed = plaintext::decode_pt(context, pt_packed);
    return pt_packed;
}

TTensor _RBGV::to_default_pt_tensor(TTensor& pt) {
    return pt.to(T_ENG_INT_TYPE);
}

} // namespace encryption_schemes
