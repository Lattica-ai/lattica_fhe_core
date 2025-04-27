#pragma once

#include "key_switch.h"

namespace encryption_schemes {

    // RBGV
    string raw__RBGV__enc(
            const string& context_proto_str,
            const string& state_proto_str,
            const string& serialized_pt,
            const string& serialized_sk,
            const string& serialized_a,
            const string& serialized_e);

    std::tuple<string, string> raw__RBGV_dec_and_get_error(
            const string& context_proto_str,
            const string& serialized_sk_coefs,
            const string& ct_proto_str);

    // CKKS
    string raw__CKKS__enc(
            const string& context_proto_str,
            const string& state_proto_str,
            const string& serialized_pt,
            const string& serialized_sk,
            const string& serialized_a,
            const string& serialized_e);

    std::tuple<string, string> raw__CKKS_dec_and_get_error(
            const string& context_proto_str,
            const string& serialized_sk_coefs,
            const string& ct_proto_str);

    string raw__CKKS_unpack_pt(
            const string& context_proto_str,
            const string& serialized_pt_packed,
            const string& serialized_pt_scale);

    string raw__CKKS_pack_pt(
            const string& context_proto_str,
            const string& serialized_pt,
            const string& serialized_pt_scale);

    // CKKS_G
    string raw__CKKS_G__enc(
            const string& context_proto_str,
            const string& state_proto_str,
            const string& serialized_pt,
            const string& serialized_sk,
            const string& serialized_a,
            const string& serialized_e);

    // RBGV_G
    string raw__RBGV_G__enc(
            const string& context_proto_str,
            const string& state_proto_str,
            const string& serialized_pt,
            const string& serialized_sk,
            const string& serialized_a,
            const string& serialized_e);

    // RBGV_G_CRT
    string raw__RBGV_G_CRT__enc(
            const string& context_proto_str,
            const string& state_proto_str,
            const string& serialized_pt,
            const string& serialized_sk,
            const string& serialized_a,
            const string& serialized_e);

    // CKKS_G_CRT
    string raw__CKKS_G_CRT__enc(
            const string& context_proto_str,
            const string& state_proto_str,
            const string& serialized_pt,
            const string& serialized_sk,
            const string& serialized_a,
            const string& serialized_e);

} // namespace encryption_schemes

namespace key_switch {

    using namespace encryption_schemes;

    string raw_gen(
            const string& context_proto_str,
            const string& serialized_sk_inner,
            const string& serialized_sk_outer);

    string raw_gen_full_key(
            const string& context_proto_str,
            const string& serialized_sk,
            bool half_sized);

    string raw_gen_base_key(
            const string& context_proto_str,
            const string& serialized_sk,
            bool half_sized);

    string raw_get_square_key(
            const string& context_proto_str,
            const string& serialized_sk);

    string raw_create_aux_key(bool is_ckks, const string& proto_str);

} // namespace key_switch
