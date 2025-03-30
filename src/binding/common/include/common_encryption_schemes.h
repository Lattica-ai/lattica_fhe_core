#pragma once

#include "key_switch.h"

namespace encryption_schemes {

    // RBGV
    string raw__RBGV__enc(
            string& context_proto_str,
            string& state_proto_str,
            string& serialized_pt,
            string& serialized_sk,
            string& serialized_a,
            string& serialized_e);

    std::tuple<string, string> raw__RBGV_dec_and_get_error(
            string& context_proto_str,
            string& serialized_sk_coefs,
            string& ct_proto_str);

    // CKKS
    string raw__CKKS__enc(
            string& context_proto_str,
            string& state_proto_str,
            string& serialized_pt,
            string& serialized_sk,
            string& serialized_a,
            string& serialized_e);

    std::tuple<string, string> raw__CKKS_dec_and_get_error(
            string& context_proto_str,
            string& serialized_sk_coefs,
            string& ct_proto_str);

    string raw__CKKS_unpack_pt(
            string& context_proto_str,
            string& serialized_pt_packed,
            string& serialized_pt_scale);

    string raw__CKKS_pack_pt(
            string& context_proto_str,
            string& serialized_pt,
            string& serialized_pt_scale);

    // CKKS_G
    string raw__CKKS_G__enc(
            string& context_proto_str,
            string& state_proto_str,
            string& serialized_pt,
            string& serialized_sk,
            string& serialized_a,
            string& serialized_e);

    // RBGV_G
    string raw__RBGV_G__enc(
            string& context_proto_str,
            string& state_proto_str,
            string& serialized_pt,
            string& serialized_sk,
            string& serialized_a,
            string& serialized_e);

    // RBGV_G_CRT
    string raw__RBGV_G_CRT__enc(
            string& context_proto_str,
            string& state_proto_str,
            string& serialized_pt,
            string& serialized_sk,
            string& serialized_a,
            string& serialized_e);

    // CKKS_G_CRT
    string raw__CKKS_G_CRT__enc(
            string& context_proto_str,
            string& state_proto_str,
            string& serialized_pt,
            string& serialized_sk,
            string& serialized_a,
            string& serialized_e);

} // namespace encryption_schemes

namespace key_switch {
    
    using namespace encryption_schemes;
    
    string raw_gen(
            string& context_proto_str,
            string& serialized_sk_inner,
            string& serialized_sk_outer);

    string raw_gen_full_key(
            string& context_proto_str,
            string& serialized_sk,
            bool half_sized);

    string raw_gen_base_key(
            string& context_proto_str,
            string& serialized_sk,
            bool half_sized);

    string raw_get_square_key(
            string& context_proto_str,
            string& serialized_sk);

    string raw_create_aux_key(bool is_ckks, string& proto_str);

} // namespace key_switch
