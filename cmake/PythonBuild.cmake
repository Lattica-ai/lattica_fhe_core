# ------------------------------------------------------------------------------
# PythonBuild.cmake
# ------------------------------------------------------------------------------
# Only proceed if PYTHON_ENABLED is ON
if(NOT PYTHON_ENABLED)
    return()
endif()

set(PYTHON_MIN_VERSION 3.12)

# Torch paths from Python virtualenv
set(LIBTORCH_LIB_DIR "${LATTICE_TOOLKIT_DIR}/build_scripts/.venv_cpu/lib/python3.12/site-packages/torch/lib")
set(LIBTORCH_SO_FILES
    ${LIBTORCH_LIB_DIR}/libaoti_custom_ops.so
    ${LIBTORCH_LIB_DIR}/libbackend_with_compiler.so
    ${LIBTORCH_LIB_DIR}/libc10.so
    ${LIBTORCH_LIB_DIR}/libgomp-a34b3233.so.1
    ${LIBTORCH_LIB_DIR}/libjitbackend_test.so
    ${LIBTORCH_LIB_DIR}/libshm.so
    ${LIBTORCH_LIB_DIR}/libtorch.so
    ${LIBTORCH_LIB_DIR}/libtorch_cpu.so
    ${LIBTORCH_LIB_DIR}/libtorch_global_deps.so
    ${LIBTORCH_LIB_DIR}/libtorch_python.so
    ${LIBTORCH_LIB_DIR}/libtorchbind_test.so
)

set(LIBTORCH_INCLUDE_DIR "${LATTICE_TOOLKIT_DIR}/build_scripts/.venv_cpu/lib/python3.12/site-packages/torch/include")
set(LIBTORCH_INCLUDE_TORCH_DIR "${LIBTORCH_INCLUDE_DIR}/torch")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--copy-dt-needed-entries -fPIC -march=native -funroll-loops -fpeel-loops -ftracer -funswitch-loops -Wno-unknown-pragmas")

set(LIBSODIUM_NATIVE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../libsodium/build_python/")
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
    ${LIBSODIUM_NATIVE_LIB_DIR}
    "/usr/local/lib"
    "/usr/local/lib64"
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
    ${LIBSODIUM_NATIVE_LIBRARY}
    cpuinfo.a
    ${protobuf_libs}
    "-Wl,--end-group"
)
