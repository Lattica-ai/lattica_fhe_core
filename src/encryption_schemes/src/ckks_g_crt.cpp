#include "ckks_g_crt.h"

namespace encryption_schemes {

std::tuple<TTensor, TTensor> _CKKS_G_CRT::sample_randomness(
    context::Context& context,
    pt_shape::PtShape& pt_shape,
    optional<global_params_and_state::State> t_state
) {
    return _EncryptionScheme_G_CRT::sample_randomness(context, pt_shape, t_state);
}

TTensor _CKKS_G_CRT::_enc(
    context::Context& context,
    global_params_and_state::State& state,
    TTensor& pt,
    TTensor& sk,
    TTensor& a,
    TTensor& e
) {
    return _EncryptionScheme_G_CRT::_enc(context, state, pt, sk, a, e);
}

} // namespace encryption_schemes
