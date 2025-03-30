#include "rbgv_g.h"
#include "plaintext.h"

namespace encryption_schemes {

    TTensor _RBGV_G::_enc(
        context::Context& context,
        global_params_and_state::State& state,
        TTensor& pt,
        TTensor& sk,
        TTensor& a,
        TTensor& e
    ) {
        auto params = context.params;
        TTensor sk_a = t_eng::modmul(
            a, sk.unsqueeze(-2), state.q_list(), false
        );
        TTensor e_scaled = t_eng::modmul(e, params.p(), state.q_list());
        pt = plaintext::encode_pt(context, pt).unsqueeze(-1);
        return _EncryptionScheme_G::_enc(context, state, pt, sk, a, e_scaled);
    }

} // namespace encryption_schemes
