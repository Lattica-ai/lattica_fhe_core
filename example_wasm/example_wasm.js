function jsToWasm(uintArray) {
  const ptr = Module._malloc(uintArray.length);
  Module.HEAPU8.set(uintArray, ptr);
  return ptr;
}

function wasmToJs(wasmArrayResult) {
    return new Uint8Array(Module.HEAPU8.buffer, Number(wasmArrayResult.ptr), wasmArrayResult.length).slice();
}


async function loadDictFromFile(url) {
    const response = await fetch(url);
    const dict = await response.json();

    function decodeValue(value) {
        if (value && typeof value === 'object') {
            if (value.__bytes__) {
                return Uint8Array.from(atob(value.__bytes__), c => c.charCodeAt(0));
            }
            if (value.__tuple__) {
                return value.__tuple__.map(decodeValue);
            }
        }
        return value;
    }

    // Decode any encoded values
    Object.keys(dict).forEach(key => {
        console.log("Decoding key:", key);
        dict[key] = decodeValue(dict[key]);
    });
    return dict;
}

async function demo_apply_client_block() {
    console.log("Loading dictionary from file...");
    const dict = await loadDictFromFile('apply_client_block.json');
    console.log("Dictionary loaded:", dict);

    console.log("Applying client block...");

    console.log("serialization started");
    const wasm_serialized_block_ptr = jsToWasm(dict['serialized_block']);
    const wasm_serialized_context_ptr = jsToWasm(dict['serialized_context']);
    const wasm_serialized_pt_ptr = jsToWasm(dict['serialized_pt']);
    console.log("serialization done");

    const result_wasm = Module.apply_client_block(
        wasm_serialized_block_ptr, dict['serialized_block'].length,
        wasm_serialized_context_ptr, dict['serialized_context'].length,
        wasm_serialized_pt_ptr, dict['serialized_pt'].length,
    );
    const result = wasmToJs(result_wasm);

    console.log('freeing memory started');
    Module.freeMemory(result_wasm.ptr)
    Module._free(wasm_serialized_block_ptr);
    Module._free(wasm_serialized_context_ptr);
    Module._free(wasm_serialized_pt_ptr);
    console.log('freeing memory done');

    const expected = dict['res'];
    console.log("Result:", result);
    console.log("Expected:", expected);
    if (JSON.stringify(result) !== JSON.stringify(expected))
        throw new Error("Result does not match expected");
}

async function demo_enc() {
    console.log("Loading dictionary from file...");
    const dict = await loadDictFromFile('enc.json');
    console.log("Dictionary loaded:", dict);

    console.log("Encrypting...");

    console.log("serialization started");
    const wasm_serialized_context_ptr = jsToWasm(dict['serialized_context']);
    const wasm_serialized_sk_ptr = jsToWasm(dict['serialized_sk']);
    const wasm_serialized_pt_ptr = jsToWasm(dict['serialized_pt']);
    console.log("serialization done");

    try {
        console.log("Module.enc started");
        const res = Module.enc(
            wasm_serialized_context_ptr, dict['serialized_context'].length,
            wasm_serialized_sk_ptr, dict['serialized_sk'].length,
            wasm_serialized_pt_ptr, dict['serialized_pt'].length,
            dict['pack_for_transmission']);
        console.log("Module.enc done");

        console.log("deserialization started");
        const result = wasmToJs(res);
        console.log("deserialization done");

        console.log('freeing memory started', res.ptr, wasm_serialized_context_ptr, wasm_serialized_pt_ptr, wasm_serialized_sk_ptr);
        Module.freeMemory(res.ptr)
        Module._free(wasm_serialized_context_ptr);
        Module._free(wasm_serialized_pt_ptr);
        Module._free(wasm_serialized_sk_ptr);
        console.log('freeing memory done');

        const expected = dict['res'];
        console.log("Result len:", result.length);
        console.log("Expected len:", expected.length);
        // NOTE: The result is not deterministic, so we only check the length
        if (result.length !== expected.length)
            throw new Error("Result does not match expected");
    } catch (e) {
        console.log(e);
    }
}

async function demo_dec() {
    console.log("Loading dictionary from file...");
    const dict = await loadDictFromFile('dec.json');
    console.log("Dictionary loaded:", dict);

    console.log("Decrypting...");
    const wasm_serialized_context_ptr = jsToWasm(dict['serialized_context']);
    const wasm_serialized_sk_ptr = jsToWasm(dict['serialized_sk'][1]);
    const wasm_serialized_ct_ptr = jsToWasm(dict['serialized_ct']);

    const result_wasm = Module.dec(
        wasm_serialized_context_ptr, dict['serialized_context'].length,
        wasm_serialized_sk_ptr, dict['serialized_sk'][1].length,
        wasm_serialized_ct_ptr, dict['serialized_ct'].length,
    );
    const result = wasmToJs(result_wasm);
    const expected = dict['res'];
    console.log("Result:", result);
    console.log("Expected:", expected);
    if (JSON.stringify(result) !== JSON.stringify(expected))
        throw new Error("Result does not match expected");

    console.log('freeing memory started', result_wasm.ptr, wasm_serialized_context_ptr, wasm_serialized_sk_ptr, wasm_serialized_ct_ptr);
    Module.freeMemory(result_wasm.ptr)
    Module._free(wasm_serialized_context_ptr);
    Module._free(wasm_serialized_sk_ptr);
    Module._free(wasm_serialized_ct_ptr);
    console.log('freeing memory done');
}

async function demo_generate_key() {
    console.log("Loading dictionary from file...");
    const dict = await loadDictFromFile('generate_key.json');
    console.log("Dictionary loaded:", dict);

    console.log("Generating key...");

    const wasm_serialized_homseq_ptr = jsToWasm(dict['serialized_homseq']);
    const wasm_serialized_context_ptr = jsToWasm(dict['serialized_context']);

    const result_wasm = Module.generate_key(
        wasm_serialized_homseq_ptr, dict['serialized_homseq'].length,
        wasm_serialized_context_ptr, dict['serialized_context'].length,
    );

    console.log(result_wasm);

    const result = [
        wasmToJs(result_wasm.sk),
        wasmToJs(result_wasm.sk_coefs),
        wasmToJs(result_wasm.pk)
    ]

    const expected = [
        dict['res'][0][0],
        dict['res'][0][1],
        dict['res'][1]
    ]

    for (let i = 0; i < 3; i++) {
        console.log("Result:", result[i]);
        console.log("Expected:", expected[i]);
        if (JSON.stringify(result[i]) !== JSON.stringify(expected[i]))
            throw new Error("Result does not match expected");
    }

    console.log('freeing memory started');
    console.log('freeing result_wasm.sk', result_wasm.sk.ptr);
    Module.freeMemory(result_wasm.sk.ptr);
    console.log('freeing result_wasm.sk_coefs', result_wasm.sk_coefs.ptr);
    Module.freeMemory(result_wasm.sk_coefs.ptr);
    console.log('freeing result_wasm.pk', result_wasm.pk.ptr);
    Module.freeMemory(result_wasm.pk.ptr);
    console.log('freeing wasm_serialized_homseq', wasm_serialized_homseq_ptr);
    Module._free(wasm_serialized_homseq_ptr);
    console.log('freeing wasm_serialized_context', wasm_serialized_context_ptr);
    Module._free(wasm_serialized_context_ptr);
    console.log('freeing memory done');

}