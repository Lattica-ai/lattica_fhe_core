# ------------------------------------------------------------------------------
# PythonBuild.cmake
# ------------------------------------------------------------------------------
# Only proceed if PYTHON_ENABLED is ON
if(NOT PYTHON_ENABLED)
    return()
endif()


include(ExternalProject)

set(PYTHON_MIN_VERSION 3.12)

execute_process(
    COMMAND python3 -c "import torch; print(torch.__path__[0])"
    OUTPUT_VARIABLE TORCH_SITE_PACKAGES_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Set include and lib directories based on that path
set(TORCH_INCLUDE_DIR "${TORCH_SITE_PACKAGES_PATH}/include")
set(TORCH_LIB_DIR "${TORCH_SITE_PACKAGES_PATH}/lib")
set(TORCH_INCLUDE_DIRS "${TORCH_INCLUDE_DIR};${TORCH_INCLUDE_DIR}/torch/csrc/api/include")

message(STATUS "Resolved TORCH_INCLUDE_DIR: ${TORCH_INCLUDE_DIR}")
message(STATUS "Resolved TORCH_LIB_DIR: ${TORCH_LIB_DIR}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--copy-dt-needed-entries -fPIC -march=native -funroll-loops -fpeel-loops -ftracer -funswitch-loops -Wno-unknown-pragmas")



message(STATUS "Find or install libsodium")
set(LIBSODIUM_INSTALL_DIR "${CMAKE_BINARY_DIR}/libsodium-install")
set(LIBSODIUM_INCLUDE_DIRS "${LIBSODIUM_INSTALL_DIR}/include")
set(LIBSODIUM_LIBRARY_DIRS "${LIBSODIUM_INSTALL_DIR}/lib")
ExternalProject_Add(
    libsodium_ext
    GIT_REPOSITORY https://github.com/jedisct1/libsodium.git
    GIT_TAG stable
    CONFIGURE_COMMAND ./configure --prefix=${LIBSODIUM_INSTALL_DIR}
    BUILD_COMMAND make
    INSTALL_COMMAND make install
    BUILD_IN_SOURCE 1
)

message(STATUS "Found Libsodium include dirs: ${LIBSODIUM_INCLUDE_DIRS}")
message(STATUS "Found Libsodium libraries: ${LIBSODIUM_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,${LIBSODIUM_LIBRARY_DIRS}")


message(STATUS "Find or install protobuf")
# Find or install protobuf v5.27.1

set(PROTOBUF_INSTALL_DIR "${CMAKE_BINARY_DIR}/protobuf-install")
set(PROTOBUF_INCLUDE_DIRS "${PROTOBUF_INSTALL_DIR}/include")
set(PROTOBUF_LIBRARY_DIRS "${PROTOBUF_INSTALL_DIR}/lib")
set(protobuf_libs
    protobuf.a
    absl_random_internal_distribution_test_util.a absl_random_internal_randen_slow.a absl_random_internal_pool_urbg.a absl_random_seed_gen_exception.a absl_flags_commandlineflag.a absl_log_flags.a absl_cordz_info.a absl_strings.a absl_malloc_internal.a absl_log_entry.a absl_vlog_config_internal.a absl_periodic_sampler.a absl_random_seed_sequences.a absl_flags_config.a absl_exponential_biased.a absl_hash.a absl_random_internal_randen_hwaes_impl.a absl_log_sink.a absl_log_internal_message.a absl_flags_program_name.a absl_str_format_internal.a absl_cordz_sample_token.a absl_random_distributions.a absl_flags_internal.a absl_bad_optional_access.a absl_flags_parse.a absl_log_internal_format.a absl_time_zone.a absl_city.a absl_kernel_timeout_internal.a absl_log_internal_check_op.a absl_crc_internal.a absl_leak_check.a absl_flags_private_handle_accessor.a absl_log_initialize.a absl_synchronization.a absl_cordz_handle.a absl_log_internal_conditions.a absl_log_internal_fnmatch.a absl_log_internal_nullguard.a absl_flags_usage.a absl_bad_variant_access.a absl_random_internal_randen.a absl_strerror.a absl_log_internal_proto.a absl_hashtablez_sampler.a absl_statusor.a absl_scoped_set_env.a absl_demangle_internal.a absl_random_internal_randen_hwaes.a absl_int128.a absl_cord_internal.a absl_random_internal_seed_material.a absl_cord.a absl_flags_usage_internal.a absl_bad_any_cast_impl.a absl_string_view.a absl_low_level_hash.a absl_log_internal_globals.a absl_log_globals.a absl_die_if_null.a absl_spinlock_wait.a absl_civil_time.a absl_log_severity.a absl_crc_cord_state.a absl_examine_stack.a absl_debugging_internal.a absl_raw_logging_internal.a absl_crc32c.a absl_log_internal_log_sink_set.a absl_failure_signal_handler.a absl_graphcycles_internal.a absl_flags_marshalling.a absl_flags_commandlineflag_internal.a absl_status.a absl_random_internal_platform.a absl_time.a absl_base.a absl_flags_reflection.a absl_raw_hash_set.a absl_crc_cpu_detect.a absl_cordz_functions.a absl_stacktrace.a absl_throw_delegate.a absl_strings_internal.a absl_symbolize.a
    utf8_range.a libutf8_validity.a
)

ExternalProject_Add(
  protobuf_ext
  GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
  GIT_TAG        v5.27.1
  CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=${PROTOBUF_INSTALL_DIR}
    -Dprotobuf_BUILD_TESTS=OFF
    -Dprotobuf_BUILD_EXAMPLES=OFF
    -Dprotobuf_BUILD_PROTOBUF_BINARIES=ON
    -Dprotobuf_BUILD_PROTOC_BINARIES=OFF
    -Dprotobuf_BUILD_LIBPROTOC=OFF
    -Dprotobuf_BUILD_LIBUPB=OFF
    -Dprotobuf_BUILD_SHARED_LIBS=OFF
    -DCMAKE_CXX_FLAGS=-D_GLIBCXX_USE_CXX11_ABI=0\ -fPIC
    -DCMAKE_C_FLAGS=-fPIC
    -DCMAKE_CXX_STANDARD=17
)

message(STATUS "Find pybind11, Python")
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

add_dependencies(${TARGET_NAME} libsodium_ext)
add_dependencies(${TARGET_NAME} protobuf_ext)

target_include_directories(${TARGET_NAME} PRIVATE
    ${Python3_INCLUDE_DIRS}
    ${LIBSODIUM_INCLUDE_DIRS}
    ${PROTOBUF_INCLUDE_DIRS}
    ${TORCH_INCLUDE_DIRS}
    ${COMMON_INCLUDE_DIRS}
)


target_link_directories(${TARGET_NAME}
    PRIVATE
    ${TORCH_LIB_DIR}
    ${LIBSODIUM_LIBRARY_DIRS}
    ${PROTOBUF_LIBRARY_DIRS}
)


# Link everything together
target_link_libraries(
  ${TARGET_NAME}
  PRIVATE
    "-Wl,--start-group"
      pybind11::module
      torch_cpu
      c10
      libsodium.so
      ${protobuf_libs}
    "-Wl,--end-group"
)

