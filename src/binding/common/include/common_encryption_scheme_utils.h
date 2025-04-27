#pragma once

#include "pt_shape.h"
#include "plaintext.h"

namespace pt_shape {

std::string raw_convert_internal_to_external(
    const std::string& serialized_a,
    const std::string& pt_shape_proto_str);

std::string raw_convert_external_to_internal(
    const std::string& serialized_a,
    const std::string& pt_shape_proto_str);

} // namespace pt_shape

namespace plaintext {

std::string raw_encode_pt(
    const std::string& context_proto_str,
    const std::string& serialized_pt);

std::string raw_decode_pt(
    const std::string& context_proto_str,
    const std::string& serialized_pt);

} // namespace plaintext
