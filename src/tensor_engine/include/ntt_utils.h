#pragma once

#include "crt_params_and_state.h"
#include "thread_utils.h"

namespace ntt_utils {

    void core_ntt_with_pool(NttArgs& nttArgs);

    TTensor ntt(crt_params_and_state::CrtParams& crt_params,
                crt_params_and_state::CrtState& crt_state,
                TTensor& a,
                int axis,
                bool inplace = true);

    void core_intt_with_pool(NttArgs& nttArgs);

    TTensor intt(crt_params_and_state::CrtParams& crt_params,
                 crt_params_and_state::CrtState& crt_state,
                 TTensor& a,
                 int axis);

} // namespace ntt_utils