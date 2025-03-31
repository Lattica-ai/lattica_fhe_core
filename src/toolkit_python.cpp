#include <pybind11/pybind11.h>
namespace py = pybind11;
#include "interface_binding_python.h"

#ifdef DEEP_BINDING
#include "deep_binding_python.h"
PYBIND11_MODULE(cpp_sdk_with_deep_binding, m) {
#else
PYBIND11_MODULE(cpp_sdk, m) {
#endif

    define_interface_bindings(m);
#ifdef DEEP_BINDING
    define_deep_bindings(m);
#endif
}
