#include "slot_permutations.h"

namespace perm_utils {

py::bytes py_apply_crt_permutation_elementwise(
    std::string& serialized_a,
    std::string& perms_proto_str,
    int axis,
    int elements_axis) {
    return py::bytes(raw_apply_crt_permutation_elementwise(serialized_a, perms_proto_str, axis, elements_axis));
}

py::bytes py_apply_crt_permutation(
    std::string& serialized_a,
    std::string& perms_proto_str, 
    int axis,
    int elements_axis) {
    return py::bytes(raw_apply_crt_permutation(serialized_a, perms_proto_str, axis, elements_axis));
}

py::bytes py_propagate_crt_perms_on_input(
    std::string& serialized_a,
    std::string& perms_proto_str,
    int axis,
    bool return_identity) {
    return py::bytes(raw_propagate_crt_perms_on_input(serialized_a, perms_proto_str, axis, return_identity));
}

} // namespace perm_utils
