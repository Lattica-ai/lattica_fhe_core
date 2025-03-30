#pragma once

#include "common_encryption_schemes.h"
#include <pybind11/stl.h>
namespace py = pybind11;

namespace encryption_schemes {

    // RBGV
    py::bytes py__RBGV__enc(
            string& context_proto_str,
            string& state_proto_str,
            string& serialized_pt,
            string& serialized_sk,
            string& serialized_a,
            string& serialized_e);

    std::tuple<py::bytes, py::bytes> py__RBGV_dec_and_get_error(
            string& context_proto_str,
            string& serialized_sk_coefs,
            string& ct_proto_str);

    // CKKS
    py::bytes py__CKKS__enc(
            string& context_proto_str,
            string& state_proto_str,
            string& serialized_pt,
            string& serialized_sk,
            string& serialized_a,
            string& serialized_e);

    std::tuple<py::bytes, py::bytes> py__CKKS_dec_and_get_error(
            string& context_proto_str,
            string& serialized_sk_coefs,
            string& ct_proto_str);

    py::bytes py__CKKS_unpack_pt(
            string& context_proto_str,
            string& serialized_pt_packed,
            string& serialized_pt_scale);

    py::bytes py__CKKS_pack_pt(
            string& context_proto_str,
            string& serialized_pt,
            string& serialized_pt_scale);

    // CKKS_G
    py::bytes py__CKKS_G__enc(
            string& context_proto_str,
            string& state_proto_str,
            string& serialized_pt,
            string& serialized_sk,
            string& serialized_a,
            string& serialized_e);

    // RBGV_G
    py::bytes py__RBGV_G__enc(
            string& context_proto_str,
            string& state_proto_str,
            string& serialized_pt,
            string& serialized_sk,
            string& serialized_a,
            string& serialized_e);

    // RBGV_G_CRT
    py::bytes py__RBGV_G_CRT__enc(
            string& context_proto_str,
            string& state_proto_str,
            string& serialized_pt,
            string& serialized_sk,
            string& serialized_a,
            string& serialized_e);

    // CKKS_G_CRT
    py::bytes py__CKKS_G_CRT__enc(
            string& context_proto_str,
            string& state_proto_str,
            string& serialized_pt,
            string& serialized_sk,
            string& serialized_a,
            string& serialized_e);

} // namespace encryption_schemes


namespace key_switch {

    py::bytes py_gen(
            string& context_proto_str,
            string& serialized_sk_inner,
            string& serialized_sk_outer);

    py::bytes py_gen_full_key(
            string& context_proto_str,
            string& serialized_sk,
            bool half_sized);

    py::bytes py_gen_base_key(
            string& context_proto_str,
            string& serialized_sk,
            bool half_sized);

    py::bytes py_get_square_key(
            string& context_proto_str,
            string& serialized_sk);

    py::bytes py_create_aux_key(bool is_ckks, string& proto_str);

} // namespace key_switch
