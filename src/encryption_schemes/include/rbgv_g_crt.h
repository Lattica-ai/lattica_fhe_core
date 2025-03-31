#pragma once

#include "rbgv.h"
#include "common_g_crt.h"

namespace encryption_schemes {

class _RBGV_G_CRT : public _EncryptionScheme_G_CRT, public _RBGV {
public:
    virtual std::tuple<TTensor, TTensor> sample_randomness(
        context::Context& context,
        pt_shape::PtShape& pt_shape,
        optional<global_params_and_state::State> t_state) override;

    virtual TTensor _enc(
        context::Context& context,
        global_params_and_state::State& state,
        TTensor& pt,
        TTensor& sk,
        TTensor& a,
        TTensor& e) override;
};

} // namespace encryption_schemes