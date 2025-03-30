#include "encryption_scheme_utils.h"

namespace pt_shape {

py::bytes py_convert_internal_to_external(
        string& serialized_a,
        string& pt_shape_proto_str) {
    return py::bytes(raw_convert_internal_to_external(serialized_a, pt_shape_proto_str));
}

py::bytes py_convert_external_to_internal(
        string& serialized_a,
        string& pt_shape_proto_str) {
    return py::bytes(raw_convert_external_to_internal(serialized_a, pt_shape_proto_str));
}

} // namespace pt_shape

namespace plaintext {

py::bytes py_encode_pt(
        string& context_proto_str,
        string& serialized_pt) {
    return py::bytes(raw_encode_pt(context_proto_str, serialized_pt));
}

py::bytes py_decode_pt(
        string& context_proto_str,
        string& serialized_pt) {
    return py::bytes(raw_decode_pt(context_proto_str, serialized_pt));
}

} // namespace plaintext
