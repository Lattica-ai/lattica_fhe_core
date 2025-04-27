#include "crt_utils.h"

namespace crt_utils {

TTensor crt_to_coefs(
        crt_params_and_state::CrtParams& crt_params,
        crt_params_and_state::CrtState& crt_state,
        TTensor& a,
        int axis,
        bool tile)
{
    if (tile)
        a = a.unsqueeze(-1);
    TTensor res = ntt_utils::intt(crt_params, crt_state, a, axis);
    return res;
}

TTensor coefs_to_crt(
        crt_params_and_state::CrtParams& crt_params,
        crt_params_and_state::CrtState& crt_state,
        TTensor& a,
        int axis,
        bool tile)
{
    if (tile)
        a = a.unsqueeze(-1);
    TTensor res = ntt_utils::ntt(crt_params, crt_state, a, axis);
    return res;
}

TTensor crt_to_coefs_q(
        context::Context& ctx,
        global_params_and_state::State& state,
        TTensor& a,
        int axis,
        bool tile)
{
    TTensor res = crt_to_coefs(ctx.get_crt_params(), state.get_crt_state(), a, axis, tile);
    return res;
}

TTensor coefs_to_crt_q(
        context::Context& ctx,
        global_params_and_state::State& state,
        TTensor& a,
        int axis,
        bool tile)
{
    TTensor res = coefs_to_crt(ctx.get_crt_params(), state.get_crt_state(), a, axis, tile);
    return res;
}

TTensor crt_to_coefs_p(
        context::Context& ctx,
        TTensor& a)
{
    a = a.unsqueeze(-1);
    TTensor res = crt_to_coefs(ctx.get_pt_pack_params(), ctx.get_pt_pack_state(), a, -2, false);
    res = res.squeeze(-1);
    return res;
}

TTensor coefs_to_crt_p(
        context::Context& ctx,
        TTensor& a)
{
    a = a.unsqueeze(-1);
    TTensor res = coefs_to_crt(ctx.get_pt_pack_params(), ctx.get_pt_pack_state(), a, -2, false);
    res = res.squeeze(-1);
    return res;
}

} // namespace crt_utils
