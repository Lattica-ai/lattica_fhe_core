#include "common_g.h"
#include "ATen/ATen.h"

namespace encryption_schemes {

std::tuple<TTensor, TTensor> _EncryptionScheme_G::sample_randomness(
        context::Context& context,
        pt_shape::PtShape& pt_shape,
        optional<global_params_and_state::State> t_state) {
    
    global_params_and_state::State state = t_state ? t_state.value() : context.init_state;
    std::vector<int64_t> additional_dims = {context.params.pt_g_params.g_exp};
    return _sample_randomness(context, state, pt_shape, additional_dims, -3 /* n_axis */);
}

std::tuple<TTensor, TTensor> _EncryptionScheme_G::dec_and_get_error(
        context::Context& context,
        TTensor& sk,
        Ciphertext& ct) {
    
    Ciphertext ct_common = ct.get_item({"...", 0, Slice()});
    return AbstractEncryptionScheme::dec_and_get_error(context, sk, ct_common);
}

TTensor _EncryptionScheme_G::_enc(
        context::Context& context,
        global_params_and_state::State& state,
        TTensor& pt,
        TTensor& sk,
        TTensor& a,
        TTensor& e) {
    
    auto params = context.params;
    TTensor sk_a = t_eng::modmul(
        a, sk.unsqueeze(-2), state.q_list(), false
    );
    
    TTensor pt_g = t_eng::modmul(
        params.pt_g_params.get_g_vec(state),
        pt.unsqueeze(-2),
        state.q_list(), false
    );
    
    pt_g = crt_utils::coefs_to_crt_q(context, state, pt_g, -3);
    TTensor b = t_eng::modsum(sk_a, e + pt_g, state.q_list(), true);
    
    return b;
}

} // namespace encryption_schemes
