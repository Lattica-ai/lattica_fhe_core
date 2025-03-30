#pragma once

#include "toolkit_interface.h"
#include <pybind11/stl.h>
namespace py = pybind11;

namespace toolkit_interface {

    std::tuple<std::tuple<py::bytes, py::bytes>, py::bytes> py_generate_key(
        std::string& serialized_homseq,
        std::string& serialized_context
    );

    py::bytes py_enc(
        std::string& serialized_context,
        std::string& serialized_sk,
        std::string& serialized_pt,
        bool pack_for_transmission = false,
        std::optional<int> n_axis_external = std::nullopt
    );

    py::bytes py_dec(
        std::string& serialized_context,
        std::string& serialized_sk,
        std::string& serialized_ct
    );

    py::bytes py_apply_client_block(
        std::string& serialized_block,
        std::string& serialized_context,
        std::string& serialized_pt
    );

} // namespace toolkit_interface