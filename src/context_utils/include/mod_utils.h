#pragma once

#include "num.h"
#include "tensor_engine.h"
#include "mod_params_and_state.h"
#include <ATen/Parallel.h>

namespace mod_utils {

    TTensor to_crt_tensor(TTensor& q_list, TTensor& a);

    void print_big_num(Num& a);

    std::vector<Num> from_crt_tensor_to_bigint(
            mod_params_and_state::ModState& mod_state,
            TTensor& a,
            const Num& final_mod);

    std::vector<std::string> from_crt_tensor_to_bigint(
            mod_params_and_state::ModState& mod_state,
            TTensor& a,
            const std::string& final_mod);

} // namespace mod_utils