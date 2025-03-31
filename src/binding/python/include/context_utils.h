#pragma once

#include "common_context_utils.h"
#include <pybind11/stl.h>
namespace py = pybind11;

namespace context {
    py::bytes py_create_context(string& proto_str);
} // namespace context

namespace global_params_and_state {
    py::bytes py_create_params(string& proto_str);
    py::bytes py_create_state(string& proto_str);
} // namespace global_params_and_state

namespace crt_params_and_state {
    py::bytes py_create_crt_params(string& proto_str);
    py::bytes py_create_crt_state(string& proto_str);
} // namespace crt_params_and_state

namespace mod_params_and_state {
    py::bytes py_create_mod_state(string& proto_str);
} // namespace mod_params_and_state

namespace crt_utils {
    py::bytes py_crt_to_coefs(
            string& crt_params_proto_str,
            string& crt_state_proto_str,
            string& serialized_a,
            int axis,
            bool tile = false);

    py::bytes py_coefs_to_crt(
            string& crt_params_proto_str,
            string& crt_state_proto_str,
            string& serialized_a,
            int axis,
            bool tile = false);

    py::bytes py_crt_to_coefs_q(
            string& ctx_proto_str,
            string& state_proto_str,
            string& serialized_a,
            int axis = -2,
            bool tile = false);

    py::bytes py_coefs_to_crt_q(
            string& ctx_proto_str,
            string& state_proto_str,
            string& serialized_a,
            int axis = -2,
            bool tile = false);

    py::bytes py_crt_to_coefs_p(string& ctx_proto_str, string& serialized_a);

    py::bytes py_coefs_to_crt_p(string& ctx_proto_str, string& serialized_a);
} // namespace crt_utils

namespace mod_utils {
    py::bytes py_to_crt_tensor(string& serialized_q_list, string& serialized_a);

    py::list py_from_crt_tensor_to_bigint(
        string& mod_state_proto_str,
        string& serialized_a,
        string final_mod
    );
} // namespace mod_utils
