#pragma once

#include "common_g.h"
#include "ckks.h"
#include "mod_utils.h"

namespace encryption_schemes {

class _CKKS_G : public _EncryptionScheme_G, public _CKKS {
public:
    virtual TTensor _enc(
        context::Context& context,
        global_params_and_state::State& state,
        TTensor& pt,
        TTensor& sk,
        TTensor& a,
        TTensor& e
    ) override;
};

} // namespace encryption_schemes