#pragma once

#include "crt_params_and_state.h"

namespace ntt_utils {

    TTensor ntt(crt_params_and_state::CrtParams& crt_params,
                crt_params_and_state::CrtState& crt_state,
                TTensor& a,
                int axis,
                bool inplace = true);

    TTensor intt(crt_params_and_state::CrtParams& crt_params,
                 crt_params_and_state::CrtState& crt_state,
                 TTensor& a,
                 int axis);

} // namespace ntt_utils