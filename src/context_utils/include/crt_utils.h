#pragma once

#include "ntt_utils.h"
#include "context.h"

namespace crt_utils {

TTensor crt_to_coefs(
    crt_params_and_state::CrtParams& crt_params,
    crt_params_and_state::CrtState& crt_state,
    TTensor& a,
    int axis,
    bool tile = false);

TTensor coefs_to_crt(
    crt_params_and_state::CrtParams& crt_params,
    crt_params_and_state::CrtState& crt_state,
    TTensor& a,
    int axis,
    bool tile = false);

TTensor crt_to_coefs_q(
    context::Context& ctx,
    global_params_and_state::State& state,
    TTensor& a,
    int axis = -2,
    bool tile = false);

TTensor coefs_to_crt_q(
    context::Context& ctx,
    global_params_and_state::State& state,
    TTensor& a,
    int axis = -2,
    bool tile = false);

TTensor crt_to_coefs_p(
    context::Context& ctx,
    TTensor& a);

TTensor coefs_to_crt_p(
    context::Context& ctx,
    TTensor& a);

} // namespace crt_utils