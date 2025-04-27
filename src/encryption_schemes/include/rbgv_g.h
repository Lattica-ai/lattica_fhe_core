#pragma once

#include "tensor_engine.h"
#include "common_g.h"
#include "rbgv.h"

namespace encryption_schemes {

class _RBGV_G : public _EncryptionScheme_G, public _RBGV {
public:
    TTensor _enc(
        context::Context& context,
        global_params_and_state::State& state,
        TTensor& pt,
        TTensor& sk,
        TTensor& a,
        TTensor& e
    ) override;
};
} // namespace encryption_schemes