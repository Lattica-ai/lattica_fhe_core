#pragma once

#include <string>
#include <optional>

namespace toolkit_interface {

using SerializedSecretKey = std::tuple<std::string, std::string>;  // (sk, sk_coefs)
using SerializedKeySet = std::tuple<SerializedSecretKey, std::string>;  // (secret_keys, public_key_aux)

SerializedKeySet raw_generate_key(
    const std::string& serialized_homseq,
    const std::string& serialized_context);

std::string raw_enc(
    const std::string& serialized_context,
    const std::string& serialized_sk,
    const std::string& serialized_pt,
    bool pack_for_transmission = false,
    std::optional<int> n_axis_external = std::nullopt);

std::string raw_dec(
    const std::string& serialized_context,
    const std::string& serialized_sk_coefs,
    const std::string& serialized_ct);

std::string raw_apply_client_block(
    const std::string& serialized_block,
    const std::string& serialized_context,
    const std::string& serialized_pt);

} // namespace toolkit_interface
