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
> ├── CMakeLists.txt
> ├── fhe_core_builder.sh
> ├── src/
> │   ├── serialization/
> │   │   └── ... (generated *.pb.cc / *.pb.h from .proto)
> │   ├── toolkit_python.cpp
> │   └── toolkit_wasm.cpp
> ├── example_wasm/
> │   └── ...
> ```

- **`CMakeLists.txt`**: Defines how to build the core library (Python/WASM).
- **`fhe_core_builder.sh`**: Primary build script; handles dependencies, compilation, and artifact copying to sibling repos.
- **`src/`**: Core C++ source code:
  - `toolkit_python.cpp` (Pybind module entry point)
  - `toolkit_wasm.cpp` (WASM entry point)
  - `serialization/` (generated C++ from `.proto` files, plus any additional logic)
- **`example_wasm/`**: Simple usage example for the WASM build, which can load `cpp_sdk.wasm`/`.js`.

---

## Prerequisites

1. **C++17** compiler (GCC 9 or newer recommended)
2. **CMake** (version 3.14 or newer)
3. **Python** (3.12+) for Python build (plus headers, e.g., `python3-dev`)
4. **Node.js** for WASM testing or `npm install` steps, if needed


---
