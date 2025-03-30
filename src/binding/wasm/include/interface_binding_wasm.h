#pragma once

#include <emscripten/bind.h>
#include "wasm_interface.h"

EMSCRIPTEN_BINDINGS(m) {

    emscripten::value_object<toolkit_interface::GenerateKeyWasmOutput>("GenerateKeyWasmOutput")
        .field("sk", &toolkit_interface::GenerateKeyWasmOutput::sk)
        .field("sk_coefs", &toolkit_interface::GenerateKeyWasmOutput::sk_coefs)
        .field("pk", &toolkit_interface::GenerateKeyWasmOutput::pk);

    emscripten::value_object<toolkit_interface::ArrayResult>("ArrayResult")
        .field("ptr", &toolkit_interface::ArrayResult::ptr)
        .field("length", &toolkit_interface::ArrayResult::length);

    emscripten::function("generate_key", &toolkit_interface::wasm_generate_key);
    emscripten::function("enc", &toolkit_interface::wasm_enc);
    emscripten::function("freeMemory", &toolkit_interface::freeMemory);
    emscripten::function("dec", &toolkit_interface::wasm_dec);
    emscripten::function("apply_client_block", &toolkit_interface::wasm_apply_client_block);
}

