#pragma once

#include "crt_utils.h"
#include "common_enc.h"

namespace encryption_schemes {

class _EncryptionScheme_G : public AbstractEncryptionScheme {
public:
    std::tuple<TTensor, TTensor> sample_randomness(
        context::Context& context,
        pt_shape::PtShape& pt_shape,
        optional<global_params_and_state::State> t_state) override;

    std::tuple<TTensor, TTensor> dec_and_get_error(
        context::Context& context,
        TTensor& sk,
        Ciphertext& ct) override;

protected:
    virtual TTensor _enc(
        context::Context& context,
        global_params_and_state::State& state,
        TTensor& pt,
        TTensor& sk,
        TTensor& a,
        TTensor& e) override;
};

} // namespace encryption_schemes