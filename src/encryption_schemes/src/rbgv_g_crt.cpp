#include "rbgv_g_crt.h"

namespace encryption_schemes {

std::tuple<TTensor, TTensor> _RBGV_G_CRT::sample_randomness(
    context::Context& context,
    pt_shape::PtShape& pt_shape,
    optional<global_params_and_state::State> t_state)
{
    return _EncryptionScheme_G_CRT::sample_randomness(context, pt_shape, t_state);
}

TTensor _RBGV_G_CRT::_enc(
    context::Context& context,
    global_params_and_state::State& state,
    TTensor& pt,
    TTensor& sk,
    TTensor& a,
    TTensor& e)
{
    TTensor e_scaled = t_eng::modmul(e, context.params.p(), state.q_list());
    return _EncryptionScheme_G_CRT::_enc(context, state, pt, sk, a, e_scaled);
}

} // namespace encryption_schemes
