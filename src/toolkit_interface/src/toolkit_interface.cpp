#include "google/protobuf/message.h"
#include "toolkit_interface.h"
#include "context.h"
#include "common_enc.h"
#include "abstract.h"
#include "key_switch.h"
#include "ckks_g_crt.h"
#include "rbgv_g_crt.h"
#include "apply_clear.h"

namespace toolkit_interface {

SerializedKeySet raw_generate_key(
    const string& serialized_homseq,
    const string& serialized_context)
{
    context::Context context = context::Context(serialized_context);

    // generate secret key
    TTensor sk, sk_coefs;
    std::tie(sk, sk_coefs) = encryption_schemes::AbstractEncryptionScheme().sample_secret_key(context, nullopt);
    lattica_proto::TensorHolder sk_proto = lattica_proto::TensorHolder();
    serialization_utils::ser_tensor(sk, &sk_proto);
    lattica_proto::TensorHolder sk_coefs_proto = lattica_proto::TensorHolder();
    serialization_utils::ser_tensor(sk_coefs, &sk_coefs_proto);

    // generate public key
    homom_ops::QueryClientSequentialHomOp client_seq_hom_op = homom_ops::QueryClientSequentialHomOp(serialized_homseq);
    std::string key_aux_proto_str;
    if (context.is_ckks()) {
        key_aux_proto_str = key_switch::KeyAux<encryption_schemes::_CKKS_G_CRT>().init_values(
            context, sk, client_seq_hom_op.get_key_types()).to_proto().SerializeAsString();
    } else {
        key_aux_proto_str = key_switch::KeyAux<encryption_schemes::_RBGV_G_CRT>().init_values(
            context, sk, client_seq_hom_op.get_key_types()).to_proto().SerializeAsString();
    }

    return std::make_tuple(
        std::make_tuple(
            sk_proto.SerializeAsString(),
            sk_coefs_proto.SerializeAsString()
        ),
        key_aux_proto_str
    );
}

string raw_enc(
    const string& serialized_context,
    const string& serialized_sk,
    const string& serialized_pt,
    bool pack_for_transmission,
    optional<int> n_axis_external)
{
    TTensor sk = serialization_utils::deser_tensor_from_str(serialized_sk);
    TTensor pt = serialization_utils::deser_tensor_from_str(serialized_pt);
    context::Context context = context::Context(serialized_context);

    // convert pt to internal shape
    auto internal_n = context.get_n();
    if (context.is_ckks()) {
        internal_n /= 2;
    }
    std::vector<int64_t> external_shape = pt.sizes().vec();
    auto new_pt_shape = pt_shape::PtShape(internal_n, external_shape, n_axis_external);

    // encrypt
    string ct_proto_str;
    if (context.is_ckks()) {
        auto ct = encryption_schemes::_CKKS().pack_and_init_ct(
            context, sk, pt, new_pt_shape, nullopt);
        if (pack_for_transmission) {
            ct.pack_for_transmission();
        }
        ct_proto_str = ct.to_proto().SerializeAsString();
    } else {
        auto ct = encryption_schemes::_RBGV().pack_and_init_ct(
            context, sk, pt, new_pt_shape, nullopt);
        if (pack_for_transmission) {
            ct.pack_for_transmission();
        }
        ct_proto_str = ct.to_proto().SerializeAsString();
    }
    return ct_proto_str;
}

string raw_dec(
    const string& serialized_context,
    const string& serialized_sk_coefs,
    const string& serialized_ct)
{
    lattica_proto::TensorHolder sk_coefs_proto = lattica_proto::TensorHolder();
    sk_coefs_proto.ParseFromString(serialized_sk_coefs);
    TTensor sk_coefs = serialization_utils::deser_tensor(sk_coefs_proto);
    context::Context context = context::Context(serialized_context);

    // decrypt
    TTensor pt;
    if (context.is_ckks()) {
        lattica_proto::CKKS_Ciphertext ct_proto = lattica_proto::CKKS_Ciphertext();
        ct_proto.ParseFromString(serialized_ct);
        auto ct = encryption_schemes::CKKS_Ciphertext();
        ct.init(ct_proto);
        if (!ct.has_state()) {
            ct.set_state(context.get_state());
        }
        pt = encryption_schemes::_CKKS().dec_and_unpack(context, sk_coefs, ct);
    } else {
        lattica_proto::RBGV_Ciphertext ct_proto = lattica_proto::RBGV_Ciphertext();
        ct_proto.ParseFromString(serialized_ct);
        auto ct = encryption_schemes::RBGV_Ciphertext();
        ct.init(ct_proto);
        if (!ct.has_state()) {
            ct.set_state(context.get_state());
        }
        pt = encryption_schemes::_RBGV().dec_and_unpack(context, sk_coefs, ct);
    }

    lattica_proto::TensorHolder pt_proto = lattica_proto::TensorHolder();
    serialization_utils::ser_tensor(pt, &pt_proto);
    return pt_proto.SerializeAsString();
}

string raw_apply_client_block(
    const string& serialized_block,
    const string& serialized_context,
    const string& serialized_pt)
{
    context::Context context = context::Context(serialized_context);
    lattica_proto::TensorHolder pt_proto = lattica_proto::TensorHolder();
    pt_proto.ParseFromString(serialized_pt);
    TTensor pt = serialization_utils::deser_tensor(pt_proto);
    homom_ops::QueryClientBlock block = homom_ops::QueryClientBlock(serialized_block);

    auto len_block = block.get_op_types_size();
    for (size_t i = 0; i < len_block; i++) {
        auto& op_type = block.get_op_type(i);
        auto& apply_clear_params = block.get_apply_clear_params(i);
        pt = homom_ops::apply_clear(op_type, context, pt, apply_clear_params);
    }

    serialization_utils::ser_tensor(pt, &pt_proto);
    return pt_proto.SerializeAsString();
}

} // namespace toolkit_interface
