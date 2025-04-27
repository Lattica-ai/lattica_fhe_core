#pragma once

#include "mod_utils.h"
#include "context.h"
#include "crt_utils.h"

namespace context {
    string raw_create_context(const string& proto_str);
} // namespace context

namespace global_params_and_state {
    string raw_create_params(const string& proto_str);
    string raw_create_state(const string& proto_str);
} // namespace global_params_and_state

namespace crt_params_and_state {
    string raw_create_crt_params(const string& proto_str);
    string raw_create_crt_state(const string& proto_str);
} // namespace crt_params_and_state

namespace mod_params_and_state {
    string raw_create_mod_state(const string& proto_str);
} // namespace mod_params_and_state

namespace crt_utils {
    string raw_crt_to_coefs(
            const string& crt_params_proto_str,
            const string& crt_state_proto_str,
            const string& serialized_a,
            int axis,
            bool tile = false);

    string raw_coefs_to_crt(
            const string& crt_params_proto_str,
            const string& crt_state_proto_str,
            const string& serialized_a,
            int axis,
            bool tile = false);

    string raw_crt_to_coefs_q(
            const string& ctx_proto_str,
            const string& state_proto_str,
            const string& serialized_a,
            int axis = -2,
            bool tile = false);

    string raw_coefs_to_crt_q(
            const string& ctx_proto_str,
            const string& state_proto_str,
            const string& serialized_a,
            int axis = -2,
            bool tile = false);

    string raw_crt_to_coefs_p(
            const string& ctx_proto_str,
            const string& serialized_a);

    string raw_coefs_to_crt_p(
            const string& ctx_proto_str,
            const string& serialized_a);
} // namespace crt_utils

namespace mod_utils {
    string raw_to_crt_tensor(const string& serialized_q_list, const string& serialized_a);

    std::vector<string> raw_from_crt_tensor_to_bigint(
        const string& mod_state_proto_str,
        const string& serialized_a,
        const string& final_mod);
} // namespace mod_utils