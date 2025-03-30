#pragma once

#include "tensor_engine.h"
#include "dataclasses.h"

namespace perm_utils {

    TTensor apply_crt_permutation_elementwise(
            TTensor& a,
            CrtPermutations crt_perms,
            int axis = -2,
            int elements_axis = 0);

    TTensor apply_crt_permutation(
            TTensor& a,
            CrtPermutations crt_perms,
            int axis = -2,
            int elements_axis = 0);

}
