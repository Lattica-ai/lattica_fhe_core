#include "perm_utils_extended.h"
#include "perm_utils_core.h"

namespace perm_utils {

TTensor propagate_crt_perms_on_input(
        TTensor& a,
        CrtPermutations crt_perms,
        int axis,
        bool return_identity) {
    int n_perms = crt_perms.get_nperms();
    std::vector<int64_t> target_shape = a.sizes().vec();
    target_shape.insert(target_shape.begin(), (1 << n_perms));
    TTensor target = t_eng::empty(target_shape);
    target.index_put_({0}, a);
    int start = 1;
    int end = 2;
    for (int i = 0; i < n_perms; i++) {
        TTensor perm_i_idxs = crt_perms.get_new_idxs().index({i}).unsqueeze(0);
        TTensor target_start = target.index({Slice(0, start)});
        TTensor rotated_target = apply_crt_permutation(
            target_start, CrtPermutations(perm_i_idxs), axis);
        target.index_put_({Slice(start, end)}, rotated_target);
        start *= 2;
        end *= 2;
    }
    if (return_identity)
        return target;
    return target.index({Slice(1, None)});
}

CrtPermutations get_perms_base_crt(context::Context context, std::optional<bool> half_sized) {
    if (!half_sized || !half_sized.value()) {
        return context.get_perms_base_crt();
    }
    TTensor new_idxs = context.get_perms_base_crt().get_new_idxs().index({Slice(1, None)});
    return CrtPermutations(new_idxs);
}

}  // namespace perm_utils
