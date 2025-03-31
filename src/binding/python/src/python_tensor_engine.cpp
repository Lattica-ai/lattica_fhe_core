#include "python_tensor_engine.h"

namespace ntt_utils {

py::bytes py_ntt(
    std::string& crt_params_proto_str,
    std::string& crt_state_proto_str,
    std::string& serialized_a,
    int axis,
    bool inplace) {
    return py::bytes(raw_ntt(crt_params_proto_str, crt_state_proto_str, serialized_a, axis, inplace));
}

py::bytes py_intt(
    std::string& crt_params_proto_str,
    std::string& crt_state_proto_str,
    std::string& serialized_a,
    int axis) {
    return py::bytes(raw_intt(crt_params_proto_str, crt_state_proto_str, serialized_a, axis));
}

} // namespace ntt_utils
