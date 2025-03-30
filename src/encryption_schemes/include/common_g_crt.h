#pragma once

#include "crt_utils.h"
#include "pt_shape.h"
#include "common_enc.h"

namespace encryption_schemes {

class _EncryptionScheme_G_CRT : public AbstractEncryptionScheme {
public:
    virtual std::tuple<TTensor, TTensor> sample_randomness(
        context::Context& context,
        pt_shape::PtShape& pt_shape,
        optional<global_params_and_state::State> t_state
    ) override;

    virtual TTensor _enc(
        context::Context& context,
        global_params_and_state::State& state,
        TTensor& pt,
        TTensor& sk,
        TTensor& a,
        TTensor& e
    ) override;

    Ciphertext apply_mod_switch_down_drop(
        Ciphertext& ct,
        Slice relative_new_indices
    ) override;
};

} // namespace encryption_schemes