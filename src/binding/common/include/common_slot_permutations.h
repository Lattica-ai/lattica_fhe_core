#pragma once

#include <string>

namespace perm_utils {

    std::string raw_apply_crt_permutation_elementwise(
            const std::string& serialized_a,
            const std::string& perms_proto_str,
            int axis = -2,
            int elements_axis = 0);

    std::string raw_apply_crt_permutation(
            const std::string& serialized_a,
            const std::string& perms_proto_str,
            int axis = -2,
            int elements_axis = 0);

    std::string raw_propagate_crt_perms_on_input(
            const std::string& serialized_a,
            const std::string& perms_proto_str,
            int axis = -2,
            bool return_identity = false);

} // namespace perm_utils
