#include "common_encryption_scheme_utils.h"
#include "tensor_engine.h"
#include "serialization_utils.h"

namespace pt_shape {

std::string raw_convert_internal_to_external(
    std::string& serialized_a,
    std::string& pt_shape_proto_str) {
    
    PtShape pt_shape = PtShape(pt_shape_proto_str);
    TTensor a = serialization_utils::deser_tensor_from_str(serialized_a);
    auto res = convert_internal_to_external(a, pt_shape);
    return serialization_utils::ser_tensor_to_bytes(res);
}

std::string raw_convert_external_to_internal(
    std::string& serialized_a,
    std::string& pt_shape_proto_str) {
    
    PtShape pt_shape = PtShape(pt_shape_proto_str);
    TTensor a = serialization_utils::deser_tensor_from_str(serialized_a);
    auto res = convert_external_to_internal(a, pt_shape);
    return serialization_utils::ser_tensor_to_bytes(res);
}

} // namespace pt_shape

namespace plaintext {

std::string raw_encode_pt(
    std::string& context_proto_str,
    std::string& serialized_pt) {
    
    context::Context context = context::Context(context_proto_str);
    TTensor pt = serialization_utils::deser_tensor_from_str(serialized_pt);
    auto res = encode_pt(context, pt);
    return serialization_utils::ser_tensor_to_bytes(res);
}

std::string raw_decode_pt(
    std::string& context_proto_str,
    std::string& serialized_pt) {
    
    context::Context context = context::Context(context_proto_str);
    TTensor pt = serialization_utils::deser_tensor_from_str(serialized_pt);
    auto res = decode_pt(context, pt);
    return serialization_utils::ser_tensor_to_bytes(res);
}

} // namespace plaintext
