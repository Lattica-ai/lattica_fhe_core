#pragma once

#include "toolkit_interface.h"
#include <string>
#include <cstdint>

namespace toolkit_interface {

    struct ArrayResult {
        uintptr_t ptr;
        size_t length;
    };

    struct GenerateKeyWasmOutput {
        ArrayResult sk;
        ArrayResult sk_coefs;
        ArrayResult pk;
    };

    ArrayResult getPersistentMemory(std::string bytes);

    GenerateKeyWasmOutput wasm_generate_key(
        const uintptr_t serialized_homseq_ptr,
        const size_t serialized_homseq_size,
        const uintptr_t serialized_context_ptr,
        const size_t serialized_context_size
    );

    ArrayResult wasm_enc(
        const uintptr_t serialized_context_ptr,
        const size_t serialized_context_size,
        const uintptr_t serialized_sk_ptr,
        const size_t serialized_sk_size,
        const uintptr_t serialized_pt_ptr,
        const size_t serialized_pt_size,
        bool pack_for_transmission = false,
        int n_axis_external = -1  // Use -1 as a default to indicate nullopt
    );

    ArrayResult wasm_dec(
        const uintptr_t serialized_context_ptr,
        const size_t serialized_context_size,
        const uintptr_t serialized_sk_ptr,
        const size_t serialized_sk_size,
        const uintptr_t serialized_ct_ptr,
        const size_t serialized_ct_size
    );

    ArrayResult wasm_apply_client_block(
        const uintptr_t serialized_block_ptr,
        const size_t serialized_block_size,
        const uintptr_t serialized_context_ptr,
        const size_t serialized_context_size,
        const uintptr_t serialized_pt_ptr,
        const size_t serialized_pt_size
    );

    // Helper function to free memory
    void freeMemory(uintptr_t ptr);

} // namespace toolkit_interface