#include "perm_utils_core.h"

namespace perm_utils {

TTensor apply_crt_permutation_elementwise(
        TTensor& a,
        CrtPermutations crt_perms,
        int axis,
        int elements_axis) {
    axis = axis < 0 ? a.dim() + axis : axis;
    std::vector<int64_t> new_shape(a.dim(), 1);
    new_shape[axis] = crt_perms.get_n();
    new_shape[elements_axis] = crt_perms.get_nperms();
    TTensor new_idxs = crt_perms.new_idxs.reshape(new_shape);
    return t_eng::take_along_axis(a, new_idxs, axis);
}

TTensor apply_crt_permutation(
        TTensor& a,
        CrtPermutations crt_perms,
        int axis,
        int elements_axis) {
    a = a.unsqueeze(elements_axis);

    TTensor res = apply_crt_permutation_elementwise(
        a, crt_perms, axis /*axis*/, elements_axis /*elements_axis*/);

    return res;
}

}  // namespace perm_utils
