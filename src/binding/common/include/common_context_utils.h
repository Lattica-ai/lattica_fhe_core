#pragma once

#include "mod_utils.h"
#include "context.h"
#include "crt_utils.h"

namespace context {
    string raw_create_context(string& proto_str);
} // namespace context

namespace global_params_and_state {
    string raw_create_params(string& proto_str);
    string raw_create_state(string& proto_str);
} // namespace global_params_and_state

namespace crt_params_and_state {
    string raw_create_crt_params(string& proto_str);
    string raw_create_crt_state(string& proto_str);
} // namespace crt_params_and_state

namespace mod_params_and_state {
    string raw_create_mod_state(string& proto_str);
} // namespace mod_params_and_state

namespace crt_utils {
    string raw_crt_to_coefs(
            string& crt_params_proto_str,
            string& crt_state_proto_str,
            string& serialized_a,
            int axis,
            bool tile = false);

    string raw_coefs_to_crt(
            string& crt_params_proto_str,
            string& crt_state_proto_str,
            string& serialized_a,
            int axis,
            bool tile = false);

    string raw_crt_to_coefs_q(
            string& ctx_proto_str,
            string& state_proto_str,
            string& serialized_a,
            int axis = -2,
            bool tile = false);

    string raw_coefs_to_crt_q(
            string& ctx_proto_str,
            string& state_proto_str,
            string& serialized_a,
            int axis = -2,
            bool tile = false);

    string raw_crt_to_coefs_p(
            string& ctx_proto_str,
            string& serialized_a);

    string raw_coefs_to_crt_p(
            string& ctx_proto_str,
            string& serialized_a);
} // namespace crt_utils

namespace mod_utils {
    string raw_to_crt_tensor(string& serialized_q_list, string& serialized_a);

    std::vector<string> raw_from_crt_tensor_to_bigint(
        string& mod_state_proto_str,
        string& serialized_a,
        string final_mod);
} // namespace mod_utils