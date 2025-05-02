# ------------------------------------------------------------------------------
# BaseConfig.cmake - common logic
# ------------------------------------------------------------------------------

#Allow automatic LTO config
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0 -O3 -Wall")

# Add option for DEEP_BINDING
option(DEEP_BINDING "Enable deep binding functionality" OFF)

# Set target name based on DEEP_BINDING
set(TARGET_NAME "cpp_sdk")
if(DEEP_BINDING)
    set(TARGET_NAME "cpp_sdk_with_deep_binding")
    add_definitions(-DDEEP_BINDING)
endif()

# Gather serialization sources
file(GLOB_RECURSE serfiles_SRC "src/serialization/src/*.pb.cc")

set(LATTICE_TOOLKIT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(COMMON_INCLUDE_DIRS
    ${SRC_DIR}/
    ${SRC_DIR}/binding/common/include
    ${SRC_DIR}/binding/python/include
    ${SRC_DIR}/binding/wasm/include
    ${SRC_DIR}/tensor_engine/include
    ${SRC_DIR}/serialization/include
    ${SRC_DIR}/slot_permutations/include
    ${SRC_DIR}/context_utils/include
    ${SRC_DIR}/encryption_schemes/include
    ${SRC_DIR}/encryption_scheme_utils/include
    ${SRC_DIR}/homomorphic_operations/include
    ${SRC_DIR}/toolkit_interface/include
)

file(GLOB_RECURSE TENSOR_ENGINE_SRC "${SRC_DIR}/tensor_engine/src/*.cpp")
file(GLOB_RECURSE SERIALIZATION_SRC "${SRC_DIR}/serialization/src/*.cpp")
file(GLOB_RECURSE SLOT_PERMUTATIONS_SRC "${SRC_DIR}/slot_permutations/src/*.cpp")
file(GLOB_RECURSE CONTEXT_UTILS_SRC "${SRC_DIR}/context_utils/src/*.cpp")
file(GLOB_RECURSE ENCRYPTION_SCHEMES_SRC "${SRC_DIR}/encryption_schemes/src/*.cpp")
file(GLOB_RECURSE ENCRYPTION_SCHEME_UTILS_SRC "${SRC_DIR}/encryption_scheme_utils/src/*.cpp")
file(GLOB_RECURSE HOMOMORPHIC_OPERATIONS_SRC "${SRC_DIR}/homomorphic_operations/src/*.cpp")
file(GLOB_RECURSE TOOLKIT_INTERFACE_SRC "${SRC_DIR}/toolkit_interface/src/*.cpp")
file(GLOB_RECURSE BINDING_COMMON_SRC "${SRC_DIR}/binding/common/src/*.cpp")
file(GLOB_RECURSE NUM_SRC "${SRC_DIR}/num.cpp")

# Combine all source files into one variable
set(ALL_SOURCES
    ${TENSOR_ENGINE_SRC}
    ${SERIALIZATION_SRC}
    ${SLOT_PERMUTATIONS_SRC}
    ${CONTEXT_UTILS_SRC}
    ${ENCRYPTION_SCHEMES_SRC}
    ${ENCRYPTION_SCHEME_UTILS_SRC}
    ${HOMOMORPHIC_OPERATIONS_SRC}
    ${TOOLKIT_INTERFACE_SRC}
    ${BINDING_COMMON_SRC}
    ${NUM_SRC}
)
