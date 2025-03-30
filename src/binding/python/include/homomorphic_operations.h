#pragma once

#include "common_homomorphic_operations.h"
#include <string>
#include <pybind11/stl.h>
namespace py = pybind11;

namespace homom_ops {

py::bytes py_create_query_client_block(std::string& proto_str);

py::bytes py_create_query_client_sequential_hom_op(std::string& proto_str);

py::bytes py_apply_clear(
    int64_t op_type_int,
    std::string& serialized_context,
    std::string& serialized_pt,
    std::string& serialized_apply_clear_params);

} // namespace homom_ops
