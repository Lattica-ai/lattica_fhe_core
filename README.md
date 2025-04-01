# Lattica FHE Core

This repository contains the Lattica Fully Homomorphic Encryption (FHE) core logic.

---

## Overview

- **Core Lattica FHE** functionality in C++
- **Python extension** (via pybind11) for integration into Python workflows
- **WASM build** for browser or Node.js environments (using Emscripten)

## Repository Structure

> ```
> lattica_fhe_core_private/
> ├── src/
> │   ├── serialization/
> │   │   └── ... (generated *.pb.cc / *.pb.h from .proto)
> │   ├── toolkit_python.cpp
> │   └── toolkit_wasm.cpp
> ```

- **`src/`**: Core C++ source code:
  - `toolkit_python.cpp` (Pybind module entry point)
  - `toolkit_wasm.cpp` (WASM entry point)
  - `serialization/` (generated C++ from `.proto` files, plus any additional logic)

---

© Lattica AI - See [LICENSE](LICENSE) for license details.

---

For more information, visit [https://www.lattica.ai](https://www.lattica.ai)