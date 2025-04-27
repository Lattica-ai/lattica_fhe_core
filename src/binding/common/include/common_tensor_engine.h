#pragma once

#include <string>

namespace ntt_utils {

/**
 * Performs a Number Theoretic Transform on the given tensor.
 *
 * @param crt_params_proto_str Serialized CrtParams
 * @param crt_state_proto_str Serialized CrtState
 * @param serialized_a Serialized tensor to transform
 * @param axis Axis along which to perform the transform
 * @param inplace Whether to perform the transform in-place
 * @return Serialized result tensor
 */
std::string raw_ntt(
    const std::string& crt_params_proto_str,
    const std::string& crt_state_proto_str,
    const std::string& serialized_a,
    int axis,
    bool inplace = true);

/**
 * Performs an Inverse Number Theoretic Transform on the given tensor.
 *
 * @param crt_params_proto_str Serialized CrtParams
 * @param crt_state_proto_str Serialized CrtState
 * @param serialized_a Serialized tensor to transform
 * @param axis Axis along which to perform the transform
 * @return Serialized result tensor
 */
std::string raw_intt(
    const std::string& crt_params_proto_str,
    const std::string& crt_state_proto_str,
    const std::string& serialized_a,
    int axis);

} // namespace ntt_utils
