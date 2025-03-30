#pragma once

#include "common_encryption_scheme_utils.h"
#include <pybind11/stl.h>
namespace py = pybind11;

namespace pt_shape {

    py::bytes py_convert_internal_to_external(
            string& serialized_a,
            string& pt_shape_proto_str);

    py::bytes py_convert_external_to_internal(
            string& serialized_a,
            string& pt_shape_proto_str);

} // namespace pt_shape

namespace plaintext {

    py::bytes py_encode_pt(
            string& context_proto_str,
            string& serialized_pt);

    py::bytes py_decode_pt(
            string& context_proto_str,
            string& serialized_pt);

} // namespace plaintext
