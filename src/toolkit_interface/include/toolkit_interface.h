#pragma once

#include <string>
#include <optional>

namespace toolkit_interface {

std::tuple<std::tuple<std::string, std::string>, std::string> raw_generate_key(
    std::string& serialized_homseq,
    std::string& serialized_context);

std::string raw_enc(
    std::string& serialized_context,
    std::string& serialized_sk,
    std::string& serialized_pt,
    bool pack_for_transmission = false,
    std::optional<int> n_axis_external = std::nullopt);

std::string raw_dec(
    std::string& serialized_context,
    std::string& serialized_sk_coefs,
    std::string& serialized_ct);

std::string raw_apply_client_block(
    std::string& serialized_block,
    std::string& serialized_context,
    std::string& serialized_pt);

} // namespace toolkit_interface
