#include "homomorphic_operations.h"
#include "common_homomorphic_operations.h"

namespace homom_ops {

py::bytes py_create_query_client_block(std::string& proto_str) 
{
    return py::bytes(raw_create_query_client_block(proto_str));
}

py::bytes py_create_query_client_sequential_hom_op(std::string& proto_str) 
{
    return py::bytes(raw_create_query_client_sequential_hom_op(proto_str));
}

py::bytes py_apply_clear(
    int64_t op_type_int,
    std::string& serialized_context,
    std::string& serialized_pt,
    std::string& serialized_apply_clear_params) 
{
    return py::bytes(raw_apply_clear(
        op_type_int, 
        serialized_context, 
        serialized_pt, 
        serialized_apply_clear_params));
}

} // namespace homom_ops
