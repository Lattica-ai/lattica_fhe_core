#include "wasm_interface.h"
#include <cstring>
#include <tuple>

namespace toolkit_interface {

ArrayResult getPersistentMemory(std::string bytes) {
    uint8_t* output = new uint8_t[bytes.size()];
    memcpy(output, bytes.data(), bytes.size());

    return { reinterpret_cast<uintptr_t>(output), bytes.size() };
}

GenerateKeyWasmOutput wasm_generate_key(
    const uintptr_t serialized_homseq_ptr,
    const size_t serialized_homseq_size,
    const uintptr_t serialized_context_ptr,
    const size_t serialized_context_size
) {
    std::string serialized_homseq(reinterpret_cast<const char*>(serialized_homseq_ptr), serialized_homseq_size);
    std::string serialized_context(reinterpret_cast<const char*>(serialized_context_ptr), serialized_context_size);

    auto result = raw_generate_key(serialized_homseq, serialized_context);

    std::string sk = std::get<0>(std::get<0>(result));
    std::string sk_coefs = std::get<1>(std::get<0>(result));
    std::string pk = std::get<1>(result);

    return {
        getPersistentMemory(sk),
        getPersistentMemory(sk_coefs),
        getPersistentMemory(pk)
    };
}

ArrayResult wasm_enc(
    const uintptr_t serialized_context_ptr,
    const size_t serialized_context_size,
    const uintptr_t serialized_sk_ptr,
    const size_t serialized_sk_size,
    const uintptr_t serialized_pt_ptr,
    const size_t serialized_pt_size,
    bool pack_for_transmission,
    int n_axis_external
) {
    std::optional<int> axis = (n_axis_external == -1) ? std::nullopt : std::optional<int>(n_axis_external);

    std::string serialized_context(reinterpret_cast<const char*>(serialized_context_ptr), serialized_context_size);
    std::string serialized_sk(reinterpret_cast<const char*>(serialized_sk_ptr), serialized_sk_size);
    std::string serialized_pt(reinterpret_cast<const char*>(serialized_pt_ptr), serialized_pt_size);

    std::string result = raw_enc(serialized_context, serialized_sk, serialized_pt, pack_for_transmission, axis);

    return getPersistentMemory(result);
}

ArrayResult wasm_dec(
    const uintptr_t serialized_context_ptr,
    const size_t serialized_context_size,
    const uintptr_t serialized_sk_ptr,
    const size_t serialized_sk_size,
    const uintptr_t serialized_ct_ptr,
    const size_t serialized_ct_size
) {
    std::string serialized_context(reinterpret_cast<const char*>(serialized_context_ptr), serialized_context_size);
    std::string serialized_sk(reinterpret_cast<const char*>(serialized_sk_ptr), serialized_sk_size);
    std::string serialized_ct(reinterpret_cast<const char*>(serialized_ct_ptr), serialized_ct_size);

    std::string result = raw_dec(serialized_context, serialized_sk, serialized_ct);

    return getPersistentMemory(result);
}

ArrayResult wasm_apply_client_block(
    const uintptr_t serialized_block_ptr,
    const size_t serialized_block_size,
    const uintptr_t serialized_context_ptr,
    const size_t serialized_context_size,
    const uintptr_t serialized_pt_ptr,
    const size_t serialized_pt_size
) {
    std::string serialized_block(reinterpret_cast<const char*>(serialized_block_ptr), serialized_block_size);
    std::string serialized_context(reinterpret_cast<const char*>(serialized_context_ptr), serialized_context_size);
    std::string serialized_pt(reinterpret_cast<const char*>(serialized_pt_ptr), serialized_pt_size);

    std::string result = raw_apply_client_block(serialized_block, serialized_context, serialized_pt);

    return getPersistentMemory(result);
}

void freeMemory(uintptr_t ptr) {
    delete[] reinterpret_cast<uint8_t*>(ptr);
}

} // namespace toolkit_interface
