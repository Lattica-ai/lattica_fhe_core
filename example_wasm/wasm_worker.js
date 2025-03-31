var Module = {};
Module.onRuntimeInitialized = async () => {
  console.log("WASM runtime initialized inside Worker");
  self.onmessage = async (msg) => {
    console.log("message from main received in wasm execution worker:", msg);
    switch (msg.data) {
      case 'enc':
        await demo_enc();
        break;
      case 'apply_client_block':
        await demo_apply_client_block();
        break;
      case 'dec':
        await demo_dec();
        break;
      case 'generate_key':
        await demo_generate_key();
        break;
      default:
        console.log("Unknown message received in wasm execution worker:", msg);
    }
    self.postMessage("done with wasm execution: " + msg.data);
    return 0;
  }
};
importScripts('example_wasm.js');
importScripts('cpp_sdk.js');

