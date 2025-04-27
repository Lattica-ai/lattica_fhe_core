#include "common_slot_permutations.h"
#include "dataclasses.h"
#include "perm_utils_core.h"
#include "perm_utils_extended.h"

namespace perm_utils {

string raw_apply_crt_permutation_elementwise(
        const string& serialized_a,
        const string& perms_proto_str,
        int axis,
        int elements_axis) {
    TTensor a = serialization_utils::deser_tensor_from_str(serialized_a);
    CrtPermutations crt_perms = CrtPermutations(perms_proto_str);
    auto res = apply_crt_permutation_elementwise(a, crt_perms, axis, elements_axis);
    return serialization_utils::ser_tensor_to_bytes(res);
}

string raw_apply_crt_permutation(
        const string& serialized_a,
        const string& perms_proto_str,
        int axis,
        int elements_axis) {
    TTensor a = serialization_utils::deser_tensor_from_str(serialized_a);
    CrtPermutations crt_perms = CrtPermutations(perms_proto_str);
    auto res = apply_crt_permutation(a, crt_perms, axis, elements_axis);
    return serialization_utils::ser_tensor_to_bytes(res);
}

string raw_propagate_crt_perms_on_input(
        const string& serialized_a,
        const string& perms_proto_str,
        int axis,
        bool return_identity) {
    TTensor a = serialization_utils::deser_tensor_from_str(serialized_a);
    CrtPermutations crt_perms = CrtPermutations(perms_proto_str);
    auto res = propagate_crt_perms_on_input(a, crt_perms, axis, return_identity);
    return serialization_utils::ser_tensor_to_bytes(res);
}

} // namespace perm_utils
