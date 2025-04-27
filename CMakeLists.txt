cmake_minimum_required(VERSION 3.14)
project(LatticaCppSdk VERSION 0.1.1)

# ------------------------------------------------------------------------------
# Load the common/base config
# ------------------------------------------------------------------------------
include(cmake/BaseConfig.cmake)

# ------------------------------------------------------------------------------
# If Python is enabled, load Python build
# ------------------------------------------------------------------------------
if(PYTHON_ENABLED)
    include(cmake/PythonBuild.cmake)
endif()

# ------------------------------------------------------------------------------
# If WASM is enabled, load WASM build
# ------------------------------------------------------------------------------
if(WASM_ENABLED)
    include(cmake/WasmBuild.cmake)
endif()
