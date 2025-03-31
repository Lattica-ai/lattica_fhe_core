#pragma once

#include <string>

namespace homom_ops {

    /**
     * Creates a query client block from a protobuf string.
     * @param proto_str The serialized protobuf string.
     * @return The serialized result.
     */
    std::string raw_create_query_client_block(std::string& proto_str);

    /**
     * Creates a sequential homomorphic operation for query client.
     * @param proto_str The serialized protobuf std::string.
     * @return The serialized result.
     */
    std::string raw_create_query_client_sequential_hom_op(std::string& proto_str);

    /**
     * Applies a clear operation based on the given parameters.
     * @param op_type_int Operation type as integer.
     * @param serialized_context Serialized context.
     * @param serialized_pt Serialized plaintext.
     * @param serialized_apply_clear_params Serialized parameters for applying clear operation.
     * @return The serialized result.
     */
    std::string raw_apply_clear(
        int64_t op_type_int,
        std::string& serialized_context,
        std::string& serialized_pt,
        std::string& serialized_apply_clear_params);

} // namespace homom_ops
