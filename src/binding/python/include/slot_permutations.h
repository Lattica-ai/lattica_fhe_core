#pragma once

#include "common_slot_permutations.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

namespace perm_utils {

py::bytes py_apply_crt_permutation_elementwise(
    std::string& serialized_a,
    std::string& perms_proto_str,
    int axis = -2,
    int elements_axis = 0);

py::bytes py_apply_crt_permutation(
    std::string& serialized_a,
    std::string& perms_proto_str,
    int axis = -2,
    int elements_axis = 0);

py::bytes py_propagate_crt_perms_on_input(
    std::string& serialized_a,
    std::string& perms_proto_str,
    int axis = -2,
    bool return_identity = false);

} // namespace perm_utils
