#include "ckks_g.h"

namespace encryption_schemes {

TTensor _CKKS_G::_enc(
    context::Context& context,
    global_params_and_state::State& state,
    TTensor& pt,
    TTensor& sk,
    TTensor& a,
    TTensor& e
) {
    pt = mod_utils::to_crt_tensor(state.q_list(), pt);
    return _EncryptionScheme_G::_enc(context, state, pt, sk, a, e);
}

} // namespace encryption_schemes
