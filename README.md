
# Lattica FHE Core

This repository contains the source code for the **Lattica Client FHE SDK**, which powers encrypted inference for AI workloads using Fully Homomorphic Encryption (FHE). The SDK provides a portable FHE implementation that compiles into a shared library used both by the Lattica Python and JS clients.

---

## 🛠️ Build Instructions

### Requirements

- Linux x86_64  
- C++17-compatible compiler (e.g. `g++ ≥ 9`)  
- CMake ≥ 3.14  
- Python ≥ 3.8  
- `pybind11` (auto-handled via CMake)  
- `setuptools`, `wheel` (for Python packaging)

### Build Steps

```bash
git clone https://github.com/Lattica-ai/lattica_fhe_core.git
cd lattica_fhe_core-main

mkdir build && cd build
cmake -DPYTHON_ENABLED=ON ..
make -j 32
```

This will generate a Python extension shared library named like:

```
cpp_sdk.cpython-312-x86_64-linux-gnu.so
```

---

## ▶️ Using This Build in the Lattica Client

To replace the binary distributed by `lattica-query`:

1. Install the query client as described here:  
   👉 https://platformdocs.lattica.ai/how-to-guides/client-installation/how-to-install-query-client

2. Locate the installed `.so` file by running:

```bash
pip show -f lattica-fhe-core
```

3. Replace the installed `cpp_sdk.*.so` file with the one you built.

---


## 📁 Project Structure

A detailed breakdown of the major components in this repository:

---

### `src/encryption_schemes/`  
Implements the supported encryption schemes used by the Lattica client.

- Includes `ckks`, `rbgv`, and two GSW-like variants (`*_g`, `*_g_crt`) based on gadget matrix decompositions.
- Each scheme provides:
  - Encoding and decoding of plaintext data  
  - Encryption and decryption procedures  
  - Key generation, including auxiliary key-switching keys
- All cryptographic randomness is generated via **Libsodium**

---

### `src/context_utils/`  
Provides utilities for interpreting and validating encryption context parameters.

- Parameters are received from the backend per model — they are not generated locally.
- Includes logic for:
  - Representing data in **double-CRT form**
  - Managing modulus chains and per-prime decompositions
  - Ensuring structural compatibility of runtime contexts

---

### `src/homomorphic_operations/`  
Implements **apply-clear** versions of homomorphic operations.

- These simulate encrypted computation by applying the logic directly to plaintext inputs.
- Used only for client-side validation and debugging — no encrypted computation is performed here.
- Actual homomorphic execution is handled remotely by the Lattica backend.

---

### `src/binding/python/`  
Defines the Python interface via `pybind11`.

- These four functions are exposed:
  1. `py_generate_key(...)`
  2. `py_enc(...)`
  3. `py_dec(...)`
  4. `py_apply_client_block(...)`

---

### `src/encryption_scheme_utils/`  
Implements abstractions for representing and manipulating the structure of plaintext data.

- Defines the `pt_shape` object, which describes logical dimensions, padding, and layout

---

### `src/tensor_engine/`  
Implements the core arithmetic and layout handling logic for encrypted and plaintext data.

- All data — including ciphertexts, plaintexts, and context elements — is represented as **tensors**
- Built on **PyTorch tensor operations**, with select extensions for FHE-specific requirements
- Includes custom kernels for modular arithmetic routines: addition, multiplication, NTT, inverse NTT

---

### `src/serialization/`  
Handles serialization and deserialization of all major objects.

- Implemented using **Protocol Buffers (protobuf)**
- Supports efficient encoding of ciphertexts, plaintexts, keys, and context objects

---

### `src/slot_permutation/`  
Implements **coefficient permutations**, supports both:
- Permutations in the **coefficient basis**
- Permutations in the **CRT basis**

---

### `src/` (top-level)  
- `num.cpp`: Implements **multi-precision integer arithmetic**
- `toolkit_python.cpp`: Entry point for the Python integration layer

---

## 🔐 License

See [LICENSE.txt](./LICENSE.txt) for license details.

For support, please contact the Lattica team or consult internal documentation.
