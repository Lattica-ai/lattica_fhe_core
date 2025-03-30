#pragma once

#include "common_tensor_engine.h"
#include <pybind11/stl.h>
namespace py = pybind11;

namespace ntt_utils {

py::bytes py_ntt(
    std::string& crt_params_proto_str,
    std::string& crt_state_proto_str,
    std::string& serialized_a,
    int axis,
    bool inplace = true);

py::bytes py_intt(
    std::string& crt_params_proto_str,
    std::string& crt_state_proto_str,
    std::string& serialized_a,
    int axis);

} // namespace ntt_utils
