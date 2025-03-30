#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;

#include "python_interface.h"

void define_interface_bindings(py::module &m) {
    m.def("generate_key", &toolkit_interface::py_generate_key, "generate_key");
    m.def("enc", &toolkit_interface::py_enc, "enc");
    m.def("dec", &toolkit_interface::py_dec, "dec");
    m.def("apply_client_block", &toolkit_interface::py_apply_client_block, "apply_client_block");
}
