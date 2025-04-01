cmake_minimum_required(VERSION 3.14)
project(LatticaCppSdk)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0 -O3")

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

set(LATTICE_TOOLKIT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../lattice-toolkit")

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
    ${SRC_DIR}/multithreading/include
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

# ------------------------------------------------------------------------------
# PYTHON BUILD
# ------------------------------------------------------------------------------
if(PYTHON_ENABLED)
    set(PYTHON_MIN_VERSION 3.12)

    # Torch paths from Python virtualenv
    set(LIBTORCH_LIB_DIR "${LATTICE_TOOLKIT_DIR}/.venv/lib/python3.12/site-packages/torch/lib")
    set(LIBTORCH_SO_FILES
        ${LIBTORCH_LIB_DIR}/libtorch.so
        ${LIBTORCH_LIB_DIR}/libtorch_cpu.so
        ${LIBTORCH_LIB_DIR}/libtorch_cuda.so
        ${LIBTORCH_LIB_DIR}/libtorch_cuda_linalg.so
        ${LIBTORCH_LIB_DIR}/libtorch_global_deps.so
        ${LIBTORCH_LIB_DIR}/libtorch_python.so
        ${LIBTORCH_LIB_DIR}/libc10.so
        ${LIBTORCH_LIB_DIR}/libc10_cuda.so
        ${LIBTORCH_LIB_DIR}/libshm.so
        ${LIBTORCH_LIB_DIR}/libcaffe2_nvrtc.so
    )

    set(LIBTORCH_INCLUDE_DIR "${LATTICE_TOOLKIT_DIR}/.venv/lib/python3.12/site-packages/torch/include")
    set(LIBTORCH_INCLUDE_TORCH_DIR "${LIBTORCH_INCLUDE_DIR}/torch")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--copy-dt-needed-entries -Wall -fPIC")

    set(LIBSODIUM_NATIVE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libsodium/native-build")
    set(LIBSODIUM_NATIVE_INCLUDE_DIR "${LIBSODIUM_NATIVE_DIR}/include")
    set(LIBSODIUM_NATIVE_LIB_DIR "${LIBSODIUM_NATIVE_DIR}/lib")
    set(LIBSODIUM_NATIVE_LIBRARY "${LIBSODIUM_NATIVE_LIB_DIR}/libsodium.so")

    message(STATUS "Using Libsodium (Native) include: ${LIBSODIUM_NATIVE_INCLUDE_DIR}")
    message(STATUS "Using Libsodium (Native) library: ${LIBSODIUM_NATIVE_LIBRARY}")

    # Find pybind11, Python
    find_package(Python3 ${PYTHON_MIN_VERSION} REQUIRED COMPONENTS Interpreter Development)
    if(Python3_VERSION VERSION_LESS ${PYTHON_MIN_VERSION})
        message(FATAL_ERROR "Python ${PYTHON_MIN_VERSION} or newer is required. Found version: ${Python3_VERSION}")
    endif()
    message(STATUS "Using Python version: ${Python3_VERSION}")

    find_package(pybind11 REQUIRED)

    file(GLOB_RECURSE BINDING_PYTHON_SRC "${SRC_DIR}/binding/python/src/*.cpp")

    # Define the target
    pybind11_add_module(${TARGET_NAME}
        src/toolkit_python.cpp
        ${ALL_SOURCES}
        ${BINDING_PYTHON_SRC}
        ${serfiles_SRC}
    )

    target_include_directories(${TARGET_NAME} PRIVATE
        ${Python3_INCLUDE_DIRS}
        ${LIBSODIUM_NATIVE_INCLUDE_DIR}
        ${LIBTORCH_INCLUDE_DIR}
        ${LIBTORCH_INCLUDE_TORCH_DIR}
        ${COMMON_INCLUDE_DIRS}
    )


    target_link_directories(${TARGET_NAME}
        PRIVATE
        ${LIBTORCH_LIB_DIR}
        "/usr/local/lib"
        "/usr/local/lib64"
        ${LIBSODIUM_NATIVE_LIBRARY}
    )


    set(ABSL_COMPILED_PATH "${PROTOBUF_PATH}/build_python/third_party/abseil-cpp")
    set(protobuf_libs
        protobuf.a
        absl_random_internal_distribution_test_util.a absl_random_internal_randen_slow.a absl_random_internal_pool_urbg.a absl_random_seed_gen_exception.a absl_flags_commandlineflag.a absl_log_flags.a absl_cordz_info.a absl_strings.a absl_malloc_internal.a absl_log_entry.a absl_vlog_config_internal.a absl_periodic_sampler.a absl_random_seed_sequences.a absl_poison.a absl_flags_config.a absl_exponential_biased.a absl_hash.a absl_random_internal_randen_hwaes_impl.a absl_log_sink.a absl_log_internal_structured_proto.a absl_log_internal_message.a absl_flags_program_name.a absl_str_format_internal.a absl_cordz_sample_token.a absl_random_distributions.a absl_flags_internal.a absl_bad_optional_access.a absl_tracing_internal.a absl_flags_parse.a absl_log_internal_format.a absl_demangle_rust.a absl_time_zone.a absl_city.a absl_kernel_timeout_internal.a absl_log_internal_check_op.a absl_crc_internal.a absl_leak_check.a absl_flags_private_handle_accessor.a absl_log_initialize.a absl_synchronization.a absl_cordz_handle.a absl_log_internal_conditions.a absl_log_internal_fnmatch.a absl_log_internal_nullguard.a absl_flags_usage.a absl_bad_variant_access.a absl_random_internal_randen.a absl_strerror.a absl_log_internal_proto.a absl_hashtablez_sampler.a absl_statusor.a absl_scoped_set_env.a absl_utf8_for_code_point.a absl_decode_rust_punycode.a absl_demangle_internal.a absl_random_internal_randen_hwaes.a absl_int128.a absl_cord_internal.a absl_random_internal_seed_material.a absl_cord.a absl_flags_usage_internal.a absl_bad_any_cast_impl.a absl_string_view.a absl_low_level_hash.a absl_log_internal_globals.a absl_log_globals.a absl_die_if_null.a absl_spinlock_wait.a absl_civil_time.a absl_log_severity.a absl_crc_cord_state.a absl_examine_stack.a absl_debugging_internal.a absl_raw_logging_internal.a absl_crc32c.a absl_log_internal_log_sink_set.a absl_failure_signal_handler.a absl_graphcycles_internal.a absl_flags_marshalling.a absl_flags_commandlineflag_internal.a absl_status.a absl_random_internal_platform.a absl_time.a absl_base.a absl_flags_reflection.a absl_raw_hash_set.a absl_crc_cpu_detect.a absl_cordz_functions.a absl_stacktrace.a absl_throw_delegate.a absl_strings_internal.a absl_symbolize.a
        utf8_range.a libutf8_validity.a
        ${ABSL_COMPILED_PATH}/absl/base/CMakeFiles/malloc_internal.dir/internal/low_level_alloc.cc.o
        ${ABSL_COMPILED_PATH}/absl/log/CMakeFiles/log_sink.dir/log_sink.cc.o
        ${ABSL_COMPILED_PATH}/absl/time/CMakeFiles/time_zone.dir/internal/cctz/src/time_zone_libc.cc.o
        ${ABSL_COMPILED_PATH}/absl/time/CMakeFiles/time_zone.dir/internal/cctz/src/time_zone_fixed.cc.o
        ${ABSL_COMPILED_PATH}/absl/time/CMakeFiles/time_zone.dir/internal/cctz/src/time_zone_impl.cc.o
        ${ABSL_COMPILED_PATH}/absl/time/CMakeFiles/time_zone.dir/internal/cctz/src/time_zone_if.cc.o
        ${ABSL_COMPILED_PATH}/absl/time/CMakeFiles/time_zone.dir/internal/cctz/src/time_zone_info.cc.o
        ${ABSL_COMPILED_PATH}/absl/time/CMakeFiles/time_zone.dir/internal/cctz/src/time_zone_lookup.cc.o
        ${ABSL_COMPILED_PATH}/absl/time/CMakeFiles/time_zone.dir/internal/cctz/src/time_zone_format.cc.o
        ${ABSL_COMPILED_PATH}/absl/time/CMakeFiles/time_zone.dir/internal/cctz/src/time_zone_posix.cc.o
        ${ABSL_COMPILED_PATH}/absl/time/CMakeFiles/time_zone.dir/internal/cctz/src/zone_info_source.cc.o
        ${ABSL_COMPILED_PATH}/absl/synchronization/CMakeFiles/kernel_timeout_internal.dir/internal/kernel_timeout.cc.o
        ${ABSL_COMPILED_PATH}/absl/debugging/CMakeFiles/debugging_internal.dir/internal/vdso_support.cc.o
        ${ABSL_COMPILED_PATH}/absl/debugging/CMakeFiles/debugging_internal.dir/internal/elf_mem_image.cc.o
        ${ABSL_COMPILED_PATH}/absl/debugging/CMakeFiles/debugging_internal.dir/internal/address_is_readable.cc.o
        ${ABSL_COMPILED_PATH}/absl/strings/CMakeFiles/cord_internal.dir/internal/cord_rep_btree_reader.cc.o
        ${ABSL_COMPILED_PATH}/absl/strings/CMakeFiles/cord_internal.dir/internal/cord_rep_btree_navigator.cc.o
        ${ABSL_COMPILED_PATH}/absl/profiling/CMakeFiles/exponential_biased.dir/internal/exponential_biased.cc.o
        ${ABSL_COMPILED_PATH}/absl/debugging/CMakeFiles/demangle_rust.dir/internal/demangle_rust.cc.o
        ${ABSL_COMPILED_PATH}/absl/debugging/CMakeFiles/demangle_internal.dir/internal/demangle.cc.o
        ${ABSL_COMPILED_PATH}/absl/debugging/CMakeFiles/decode_rust_punycode.dir/internal/decode_rust_punycode.cc.o
        ${ABSL_COMPILED_PATH}/absl/debugging/CMakeFiles/utf8_for_code_point.dir/internal/utf8_for_code_point.cc.o
        ${ABSL_COMPILED_PATH}/absl/crc/CMakeFiles/crc_internal.dir/internal/crc.cc.o
        ${ABSL_COMPILED_PATH}/absl/crc/CMakeFiles/crc_internal.dir/internal/crc_x86_arm_combined.cc.o
    )

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,${LIBSODIUM_NATIVE_LIB_DIR},--no-as-needed")

    # Link everything together
    target_link_libraries(
        ${TARGET_NAME}
        PRIVATE
        "-Wl,--start-group"
        pybind11::module
        ${LIBTORCH_SO_FILES}
        cpuinfo.a
        ${protobuf_libs}
        ${LIBSODIUM_NATIVE_LIBRARY}
        "-Wl,--end-group"
    )

endif()

# ------------------------------------------------------------------------------
# WASM BUILD
# ------------------------------------------------------------------------------
if(WASM_ENABLED)
    # Torch Lattica is in the sibling "lattice-toolkit/torch_lattica"
    set(TORCH_LATTICA_PATH  "${LATTICE_TOOLKIT_DIR}/torch_lattica")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -sDISABLE_EXCEPTION_CATCHING=0 -pthread -flto")
    set(COMMON_INCLUDE_DIRS ${COMMON_INCLUDE_DIRS} ${TORCH_LATTICA_PATH}/src/)
    set( BASE_LIB ${WASM_BASE_DIR} )
    link_directories(${BASE_LIB}/lib)

    set(LIBSODIUM_WASM_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libsodium/wasm-build")
    set(LIBSODIUM_WASM_INCLUDE_DIR "${LIBSODIUM_WASM_DIR}/include")
    set(LIBSODIUM_WASM_LIB_DIR "${LIBSODIUM_WASM_DIR}/lib")
    set(LIBSODIUM_WASM_LIBRARY "${LIBSODIUM_WASM_LIB_DIR}/libsodium.a")

    message(STATUS "Using Libsodium (WASM) include: ${LIBSODIUM_WASM_INCLUDE_DIR}")
    message(STATUS "Using Libsodium (WASM) library: ${LIBSODIUM_WASM_LIBRARY}")

    file(GLOB_RECURSE BINDING_WASM_SRC "${SRC_DIR}/binding/wasm/src/*.cpp")

    # Torch Lattica "register" files
    set(registerfiles_SRC
        ${TORCH_LATTICA_PATH}/src/ATen/RegisterSchema.cpp
        ${TORCH_LATTICA_PATH}/src/ATen/RegisterBackendSelect.cpp
        ${TORCH_LATTICA_PATH}/src/ATen/core/BackendSelectFallbackKernel.cpp
        ${TORCH_LATTICA_PATH}/src/ATen/core/VariableFallbackKernel.cpp
        ${TORCH_LATTICA_PATH}/src/ATen/RegisterCPU.cpp
        ${TORCH_LATTICA_PATH}/src/ATen/RegisterCompositeExplicitAutograd.cpp
        ${TORCH_LATTICA_PATH}/src/ATen/RegisterCompositeImplicitAutograd.cpp
    )

    add_executable(
        ${TARGET_NAME}
        src/toolkit_wasm.cpp
        ${ALL_SOURCES}
        ${BINDING_WASM_SRC}
        ${serfiles_SRC}
        ${registerfiles_SRC}
    )

    target_link_directories(${TARGET_NAME} PRIVATE "${TORCH_LATTICA_PATH}/build_wasm/")

    target_include_directories(${TARGET_NAME} PRIVATE
        ${BASE_LIB}/include
        ${LIBSODIUM_WASM_INCLUDE_DIR}
        ${COMMON_INCLUDE_DIRS}
    )

    target_link_libraries(
        ${TARGET_NAME}
        TorchLattica
        cpuinfo.a
        protobuf.a
        ${LIBSODIUM_WASM_LIBRARY}
        absl_random_internal_distribution_test_util.a
        absl_random_internal_randen_slow.a
        absl_random_internal_pool_urbg.a
        absl_random_seed_gen_exception.a
        absl_flags_commandlineflag.a
        absl_log_flags.a
        absl_cordz_info.a
        absl_strings.a
        absl_malloc_internal.a
        absl_log_entry.a
        absl_vlog_config_internal.a
        absl_periodic_sampler.a
        absl_random_seed_sequences.a
        absl_poison.a
        absl_flags_config.a
        absl_exponential_biased.a
        absl_hash.a
        absl_random_internal_randen_hwaes_impl.a
        absl_log_internal_conditions.a
        absl_log_internal_format.a
        absl_log_internal_globals.a
        absl_log_internal_log_sink_set.a
        absl_log_internal_nullguard.a
        absl_log_internal_proto.a
        absl_log_severity.a
        absl_log_sink.a
        absl_log_internal_check_op.a
        absl_log_internal_message.a
        absl_flags_program_name.a
        absl_str_format_internal.a
        absl_cordz_sample_token.a
        absl_random_distributions.a
        absl_flags_internal.a
        absl_bad_optional_access.a
        absl_tracing_internal.a
        absl_flags_parse.a
        absl_demangle_rust.a
        absl_time_zone.a
        absl_city.a
        absl_kernel_timeout_internal.a
        absl_crc_internal.a
        absl_leak_check.a
        absl_flags_private_handle_accessor.a
        absl_log_initialize.a
        absl_synchronization.a
        absl_cordz_handle.a
        absl_log_internal_fnmatch.a
        absl_flags_usage.a
        absl_bad_variant_access.a
        absl_random_internal_randen.a
        absl_strerror.a
        absl_hashtablez_sampler.a
        absl_statusor.a
        absl_scoped_set_env.a
        absl_utf8_for_code_point.a
        absl_decode_rust_punycode.a
        absl_demangle_internal.a
        absl_random_internal_randen_hwaes.a
        absl_int128.a
        absl_cord_internal.a
        absl_random_internal_seed_material.a
        absl_cord.a
        absl_flags_usage_internal.a
        absl_bad_any_cast_impl.a
        absl_string_view.a
        absl_low_level_hash.a
        absl_log_globals.a
        absl_die_if_null.a
        absl_spinlock_wait.a
        absl_civil_time.a
        absl_crc_cord_state.a
        absl_examine_stack.a
        absl_debugging_internal.a
        absl_raw_logging_internal.a
        absl_crc32c.a
        absl_failure_signal_handler.a
        absl_graphcycles_internal.a
        absl_flags_marshalling.a
        absl_flags_commandlineflag_internal.a
        absl_status.a
        absl_random_internal_platform.a
        absl_time.a
        absl_base.a
        absl_flags_reflection.a
        absl_raw_hash_set.a
        absl_crc_cpu_detect.a
        absl_cordz_functions.a
        absl_stacktrace.a
        absl_throw_delegate.a
        absl_strings_internal.a
        absl_symbolize.a
        utf8_range.a
        libutf8_validity.a
    )
    # Add specific flags for this executable
    target_compile_options(${TARGET_NAME} PRIVATE
        --bind
        -sWASM=1
        -pthread
        -sPTHREAD_POOL_SIZE=navigator.hardwareConcurrency
        -sINITIAL_MEMORY=33554432
        -sSTACK_SIZE=16777216
        -sMAXIMUM_MEMORY=3221225472
        -sALLOW_MEMORY_GROWTH=1
        -sMALLOC=mimalloc
        -sENVIRONMENT=web,worker,node
        -sEXPORTED_FUNCTIONS=_malloc,_free
        -flto
    )
    target_link_options(${TARGET_NAME} PRIVATE
        --bind
        -sWASM=1
        -pthread
        -sPTHREAD_POOL_SIZE=navigator.hardwareConcurrency
        -sINITIAL_MEMORY=33554432
        -sSTACK_SIZE=16777216
        -sMAXIMUM_MEMORY=3221225472
        -sALLOW_MEMORY_GROWTH=1
        -sMALLOC=mimalloc
        -sENVIRONMENT=web,worker,node
        -sEXPORTED_FUNCTIONS=_malloc,_free
    )

endif()