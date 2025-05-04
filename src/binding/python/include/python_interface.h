#pragma once

#include "toolkit_interface.h"
#include <pybind11/stl.h>
namespace py = pybind11;

namespace toolkit_interface {

namespace python_interface {

/**
 * @typedef SerializedSecretKey
 * A pair of serialized secret-key tensor and its coefficient tensor.
 */
using SerializedSecretKey = std::tuple<py::bytes, py::bytes>;

/**
 * @typedef SerializedKeySet
 * A tuple of SerializedSecretKey and serialized auxiliary evaluation key.
 */
using SerializedKeySet = std::tuple<SerializedSecretKey, py::bytes>;
}

/**
 * Generate a homomorphic encryption key pair and auxiliary evaluation key.
 *
 * Produces the serialized secret key tensor, its coefficient tensor,
 * and the auxiliary evaluation key tailored to the encryption scheme (CKKS or RBGV).
 *
 * @param serialized_homseq   Protobuf-serialized specification of homomorphic operations.
 * @param serialized_context  Protobuf-serialized encryption context parameters.
 * @return A tuple:
 *   - First element: a pair of py::bytes containing the serialized secret key tensor
 *     and serialized secret-key coefficient tensor.
 *   - Second element: py::bytes containing the serialized auxiliary evaluation key.
 */
python_interface::SerializedKeySet py_generate_key(
    const std::string& serialized_homseq,
    const std::string& serialized_context
);

/**
 * Encrypt a plaintext tensor into a ciphertext.
 *
 * Deserializes the secret key and plaintext tensors, computes the internal plaintext shape
 * (halving the slot count for CKKS), encrypts via CKKS or RBGV scheme, optionally packs
 * for optimized transmission, and serializes the resulting ciphertext.
 *
 * @param serialized_context      Protobuf-serialized encryption context parameters.
 * @param serialized_sk           Protobuf-serialized secret-key coefficient tensor.
 * @param serialized_pt           Protobuf-serialized plaintext tensor.
 * @param pack_for_transmission   If true, applies pack_for_transmission() to the ciphertext.
 * @param n_axis_external         Optional external axis size influencing plaintext shape.
 * @return py::bytes containing the serialized ciphertext.
 */
py::bytes py_enc(
    const std::string& serialized_context,
    const std::string& serialized_sk,
    const std::string& serialized_pt,
    bool pack_for_transmission = false,
    std::optional<int> n_axis_external = std::nullopt
);

/**
 * Decrypt a ciphertext tensor back to plaintext.
 *
 * Deserializes secret-key coefficients and ciphertext, restores internal state
 * if missing, then performs decryption and unpacking for CKKS or RBGV scheme,
 * and serializes the resulting plaintext tensor.
 *
 * @param serialized_context   Protobuf-serialized encryption context parameters.
 * @param serialized_sk        Protobuf-serialized secret-key coefficient tensor.
 * @param serialized_ct        Protobuf-serialized ciphertext tensor.
 * @return py::bytes containing the serialized decrypted plaintext tensor.
 */
py::bytes py_dec(
    const std::string& serialized_context,
    const std::string& serialized_sk,
    const std::string& serialized_ct
);

/**
 * Apply a client-side homomorphic operation block to a plaintext tensor.
 *
 * Deserializes a QueryClientBlock message, iterates through its operations,
 * applies each operation with homom_ops::apply_clear(), then serializes the
 * transformed plaintext tensor.
 *
 * @param serialized_block     Protobuf-serialized block of homomorphic operations.
 * @param serialized_context   Protobuf-serialized encryption context parameters.
 * @param serialized_pt        Protobuf-serialized plaintext tensor.
 * @return py::bytes containing the serialized tensor after applying all operations.
 */
py::bytes py_apply_client_block(
    const std::string& serialized_block,
    const std::string& serialized_context,
    const std::string& serialized_pt
);

} // namespace toolkit_interface
