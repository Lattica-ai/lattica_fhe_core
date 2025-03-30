#include "encryption_schemes.h"

namespace encryption_schemes {

    // RBGV
    py::bytes py__RBGV__enc(
            string& context_proto_str,
            string& state_proto_str,
            string& serialized_pt,
            string& serialized_sk,
            string& serialized_a,
            string& serialized_e) {
        return py::bytes(raw__RBGV__enc(context_proto_str, state_proto_str, serialized_pt, serialized_sk, serialized_a, serialized_e));
    }

    std::tuple<py::bytes, py::bytes> py__RBGV_dec_and_get_error(
            string& context_proto_str,
            string& serialized_sk_coefs,
            string& ct_proto_str) {
        auto [res1, res2] = raw__RBGV_dec_and_get_error(context_proto_str, serialized_sk_coefs, ct_proto_str);
        return std::make_tuple(py::bytes(res1), py::bytes(res2));
    }

    // CKKS
    py::bytes py__CKKS__enc(
            string& context_proto_str,
            string& state_proto_str,
            string& serialized_pt,
            string& serialized_sk,
            string& serialized_a,
            string& serialized_e) {
        return py::bytes(raw__CKKS__enc(context_proto_str, state_proto_str, serialized_pt, serialized_sk, serialized_a, serialized_e));
    }

    std::tuple<py::bytes, py::bytes> py__CKKS_dec_and_get_error(
            string& context_proto_str,
            string& serialized_sk_coefs,
            string& ct_proto_str) {
        auto [res1, res2] = raw__CKKS_dec_and_get_error(context_proto_str, serialized_sk_coefs, ct_proto_str);
        return std::make_tuple(py::bytes(res1), py::bytes(res2));
    }

    py::bytes py__CKKS_unpack_pt(
            string& context_proto_str,
            string& serialized_pt_packed,
            string& serialized_pt_scale) {
        return py::bytes(raw__CKKS_unpack_pt(context_proto_str, serialized_pt_packed, serialized_pt_scale));
    }

    py::bytes py__CKKS_pack_pt(
            string& context_proto_str,
            string& serialized_pt,
            string& serialized_pt_scale) {
        return py::bytes(raw__CKKS_pack_pt(context_proto_str, serialized_pt, serialized_pt_scale));
    }

    // CKKS_G
    py::bytes py__CKKS_G__enc(
            string& context_proto_str,
            string& state_proto_str,
            string& serialized_pt,
            string& serialized_sk,
            string& serialized_a,
            string& serialized_e) {
        return py::bytes(raw__CKKS_G__enc(context_proto_str, state_proto_str, serialized_pt, serialized_sk, serialized_a, serialized_e));
    }

    // RBGV_G
    py::bytes py__RBGV_G__enc(
            string& context_proto_str,
            string& state_proto_str,
            string& serialized_pt,
            string& serialized_sk,
            string& serialized_a,
            string& serialized_e) {
        return py::bytes(raw__RBGV_G__enc(context_proto_str, state_proto_str, serialized_pt, serialized_sk, serialized_a, serialized_e));
    }

    // RBGV_G_CRT
    py::bytes py__RBGV_G_CRT__enc(
            string& context_proto_str,
            string& state_proto_str,
            string& serialized_pt,
            string& serialized_sk,
            string& serialized_a,
            string& serialized_e) {
        return py::bytes(raw__RBGV_G_CRT__enc(context_proto_str, state_proto_str, serialized_pt, serialized_sk, serialized_a, serialized_e));
    }

    // CKKS_G_CRT
    py::bytes py__CKKS_G_CRT__enc(
            string& context_proto_str,
            string& state_proto_str,
            string& serialized_pt,
            string& serialized_sk,
            string& serialized_a,
            string& serialized_e) {
        return py::bytes(raw__CKKS_G_CRT__enc(context_proto_str, state_proto_str, serialized_pt, serialized_sk, serialized_a, serialized_e));
    }

} // namespace encryption_schemes


namespace key_switch {

    py::bytes py_gen(
            string& context_proto_str,
            string& serialized_sk_inner,
            string& serialized_sk_outer) {
        return py::bytes(raw_gen(context_proto_str, serialized_sk_inner, serialized_sk_outer));
    }

    py::bytes py_gen_full_key(
            string& context_proto_str,
            string& serialized_sk,
            bool half_sized) {
        return py::bytes(raw_gen_full_key(context_proto_str, serialized_sk, half_sized));
    }

    py::bytes py_gen_base_key(
            string& context_proto_str,
            string& serialized_sk,
            bool half_sized) {
        return py::bytes(raw_gen_base_key(context_proto_str, serialized_sk, half_sized));
    }

    py::bytes py_get_square_key(
            string& context_proto_str,
            string& serialized_sk) {
        return py::bytes(raw_get_square_key(context_proto_str, serialized_sk));
    }

    py::bytes py_create_aux_key(bool is_ckks, string& proto_str) {
        return py::bytes(raw_create_aux_key(is_ckks, proto_str));
    }

} // namespace key_switch
