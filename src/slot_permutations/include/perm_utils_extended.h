#pragma once

#include "tensor_engine.h"
#include "context.h"

namespace perm_utils {

    TTensor propagate_crt_perms_on_input(
            TTensor& a,
            CrtPermutations crt_perms,
            int axis = -2,
            bool return_identity = false);

    CrtPermutations get_perms_base_crt(
            context::Context context, 
            std::optional<bool> half_sized = std::nullopt);

}
