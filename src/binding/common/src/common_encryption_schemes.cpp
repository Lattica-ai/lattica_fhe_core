#include "common_encryption_schemes.h"
#include "rbgv.h"
#include "rbgv_g.h"
#include "rbgv_g_crt.h"
#include "ckks.h"
#include "ckks_g.h"
#include "ckks_g_crt.h"

namespace encryption_schemes {

    // RBGV
    string raw__RBGV__enc(
            string& context_proto_str,
            string& state_proto_str,
            string& serialized_pt,
            string& serialized_sk,
            string& serialized_a,
            string& serialized_e) {
        TTensor pt = serialization_utils::deser_tensor_from_str(serialized_pt);
        TTensor sk = serialization_utils::deser_tensor_from_str(serialized_sk);
        TTensor a = serialization_utils::deser_tensor_from_str(serialized_a);
        TTensor e = serialization_utils::deser_tensor_from_str(serialized_e);
        context::Context context = context::Context(context_proto_str);
        global_params_and_state::State state = global_params_and_state::State(state_proto_str);
        auto res = _RBGV()._enc(context, state, pt, sk, a, e);
        return serialization_utils::ser_tensor_to_bytes(res);
    }

    std::tuple<string, string> raw__RBGV_dec_and_get_error(
                string& context_proto_str,
                string& serialized_sk_coefs,
                string& ct_proto_str) {
        TTensor sk_coefs = serialization_utils::deser_tensor_from_str(serialized_sk_coefs);
        context::Context context = context::Context(context_proto_str);
        RBGV_Ciphertext ct = RBGV_Ciphertext(ct_proto_str);
        auto res = _RBGV().dec_and_get_error(context, sk_coefs, ct);
        auto res1 = serialization_utils::ser_tensor_to_bytes(std::get<0>(res));
        auto res2 = serialization_utils::ser_tensor_to_bytes(std::get<1>(res));
        return std::make_tuple(res1, res2);
    }

    // CKKS
    string raw__CKKS__enc(
            string& context_proto_str,
            string& state_proto_str,
            string& serialized_pt,
            string& serialized_sk,
            string& serialized_a,
            string& serialized_e) {
        TTensor pt = serialization_utils::deser_tensor_from_str(serialized_pt);
        TTensor sk = serialization_utils::deser_tensor_from_str(serialized_sk);
        TTensor a = serialization_utils::deser_tensor_from_str(serialized_a);
        TTensor e = serialization_utils::deser_tensor_from_str(serialized_e);
        context::Context context = context::Context(context_proto_str);
        global_params_and_state::State state = global_params_and_state::State(state_proto_str);
        auto res = _CKKS()._enc(context, state, pt, sk, a, e);
        return serialization_utils::ser_tensor_to_bytes(res);
    }

    std::tuple<string, string> raw__CKKS_dec_and_get_error(
                string& context_proto_str,
                string& serialized_sk_coefs,
                string& ct_proto_str) {
        TTensor sk_coefs = serialization_utils::deser_tensor_from_str(serialized_sk_coefs);
        context::Context context = context::Context(context_proto_str);
        CKKS_Ciphertext ct = CKKS_Ciphertext(ct_proto_str);
        auto res = _CKKS().dec_and_get_error(context, sk_coefs, ct);
        auto res1 = serialization_utils::ser_tensor_to_bytes(std::get<0>(res));
        auto res2 = serialization_utils::ser_tensor_to_bytes(std::get<1>(res));
        return std::make_tuple(res1, res2);
    }

    string raw__CKKS_unpack_pt(
            string& context_proto_str,
            string& serialized_pt_packed,
            string& serialized_pt_scale) {
        TTensor pt_packed = serialization_utils::deser_tensor_from_str(serialized_pt_packed);
        context::Context context = context::Context(context_proto_str);
        lattica_proto::CKKS_Pt_Scale* proto = new lattica_proto::CKKS_Pt_Scale();
        proto->ParseFromString(serialized_pt_scale);
        std::vector<double> pt_scale;
        for (int i = 0; i < proto->pt_scale_size(); i++) {
            pt_scale.push_back(proto->pt_scale(i));
        }
        auto res = _CKKS().unpack_pt(context, pt_packed, pt_scale);
        return serialization_utils::ser_tensor_to_bytes(res);
    }

    string raw__CKKS_pack_pt(
            string& context_proto_str,
            string& serialized_pt,
            string& serialized_pt_scale) {
        TTensor pt = serialization_utils::deser_tensor_from_str(serialized_pt);
        lattica_proto::CKKS_Pt_Scale* proto = new lattica_proto::CKKS_Pt_Scale();
        proto->ParseFromString(serialized_pt_scale);
        std::vector<double> pt_scale;
        for (int i = 0; i < proto->pt_scale_size(); i++) {
            pt_scale.push_back(proto->pt_scale(i));
        }
        context::Context context = context::Context(context_proto_str);
        auto res = _CKKS().pack_pt(context, pt, pt_scale);
        return serialization_utils::ser_tensor_to_bytes(res);
    }

    // CKKS_G
    string raw__CKKS_G__enc(
            string& context_proto_str,
            string& state_proto_str,
            string& serialized_pt,
            string& serialized_sk,
            string& serialized_a,
            string& serialized_e) {
        TTensor pt = serialization_utils::deser_tensor_from_str(serialized_pt);
        TTensor sk = serialization_utils::deser_tensor_from_str(serialized_sk);
        TTensor a = serialization_utils::deser_tensor_from_str(serialized_a);
        TTensor e = serialization_utils::deser_tensor_from_str(serialized_e);
        context::Context context = context::Context(context_proto_str);
        global_params_and_state::State state = global_params_and_state::State(state_proto_str);
        auto res = _CKKS_G()._enc(context, state, pt, sk, a, e);
        return serialization_utils::ser_tensor_to_bytes(res);
    }

    // RBGV_G
    string raw__RBGV_G__enc(
            string& context_proto_str,
            string& state_proto_str,
            string& serialized_pt,
            string& serialized_sk,
            string& serialized_a,
            string& serialized_e) {
        TTensor pt = serialization_utils::deser_tensor_from_str(serialized_pt);
        TTensor sk = serialization_utils::deser_tensor_from_str(serialized_sk);
        TTensor a = serialization_utils::deser_tensor_from_str(serialized_a);
        TTensor e = serialization_utils::deser_tensor_from_str(serialized_e);
        context::Context context = context::Context(context_proto_str);
        global_params_and_state::State state = global_params_and_state::State(state_proto_str);
        auto res = _RBGV_G()._enc(context, state, pt, sk, a, e);
        return serialization_utils::ser_tensor_to_bytes(res);
    }

    // RBGV_G_CRT
    string raw__RBGV_G_CRT__enc(
            string& context_proto_str,
            string& state_proto_str,
            string& serialized_pt,
            string& serialized_sk,
            string& serialized_a,
            string& serialized_e) {
        TTensor pt = serialization_utils::deser_tensor_from_str(serialized_pt);
        TTensor sk = serialization_utils::deser_tensor_from_str(serialized_sk);
        TTensor a = serialization_utils::deser_tensor_from_str(serialized_a);
        TTensor e = serialization_utils::deser_tensor_from_str(serialized_e);
        context::Context context = context::Context(context_proto_str);
        global_params_and_state::State state = global_params_and_state::State(state_proto_str);
        auto res = _RBGV_G_CRT()._enc(context, state, pt, sk, a, e);
        return serialization_utils::ser_tensor_to_bytes(res);
    }

    // CKKS_G_CRT
    string raw__CKKS_G_CRT__enc(
            string& context_proto_str,
            string& state_proto_str,
            string& serialized_pt,
            string& serialized_sk,
            string& serialized_a,
            string& serialized_e) {
        TTensor pt = serialization_utils::deser_tensor_from_str(serialized_pt);
        TTensor sk = serialization_utils::deser_tensor_from_str(serialized_sk);
        TTensor a = serialization_utils::deser_tensor_from_str(serialized_a);
        TTensor e = serialization_utils::deser_tensor_from_str(serialized_e);
        context::Context context = context::Context(context_proto_str);
        global_params_and_state::State state = global_params_and_state::State(state_proto_str);
        auto res = _CKKS_G_CRT()._enc(context, state, pt, sk, a, e);
        return serialization_utils::ser_tensor_to_bytes(res);
    }

} // namespace encryption_schemes

namespace key_switch {

    using namespace encryption_schemes;
    
    string raw_gen(
            string& context_proto_str,
            string& serialized_sk_inner,
            string& serialized_sk_outer) {
        TTensor sk_inner = serialization_utils::deser_tensor_from_str(serialized_sk_inner);
        TTensor sk_outer = serialization_utils::deser_tensor_from_str(serialized_sk_outer);
        context::Context context = context::Context(context_proto_str);
        if (context.is_ckks) {
            auto res = gen<_CKKS_G_CRT>(context, sk_inner, sk_outer);
            auto res_proto = res.to_proto();
            string res_str = res_proto.SerializeAsString();
            return res_str;
        } else {
            auto res = gen<_RBGV_G_CRT>(context, sk_inner, sk_outer);
            auto res_proto = res.to_proto();
            string res_str = res_proto.SerializeAsString();
            return res_str;
        }
    }

    string raw_gen_full_key(
            string& context_proto_str,
            string& serialized_sk,
            bool half_sized) {
        TTensor sk = serialization_utils::deser_tensor_from_str(serialized_sk);
        context::Context context = context::Context(context_proto_str);
        if (context.is_ckks) {
            auto res = gen_full_key<_CKKS_G_CRT>(context, sk, half_sized);
            auto res_proto = res.to_proto();
            string res_str = res_proto.SerializeAsString();
            return res_str;
        } else {
            auto res = gen_full_key<_RBGV_G_CRT>(context, sk, half_sized);
            auto res_proto = res.to_proto();
            string res_str = res_proto.SerializeAsString();
            return res_str;
        }
    }

    string raw_gen_base_key(
            string& context_proto_str,
            string& serialized_sk,
            bool half_sized) {
        TTensor sk = serialization_utils::deser_tensor_from_str(serialized_sk);
        context::Context context = context::Context(context_proto_str);
        if (context.is_ckks) {
            auto res = gen_base_key<_CKKS_G_CRT>(context, sk, half_sized);
            auto res_proto = res.to_proto();
            string res_str = res_proto.SerializeAsString();
            return res_str;
        } else {
            auto res = gen_base_key<_RBGV_G_CRT>(context, sk, half_sized);
            auto res_proto = res.to_proto();
            string res_str = res_proto.SerializeAsString();
            return res_str;
        }
    }

    string raw_get_square_key(
            string& context_proto_str,
            string& serialized_sk) {
        TTensor sk = serialization_utils::deser_tensor_from_str(serialized_sk);
        context::Context context = context::Context(context_proto_str);
        if (context.is_ckks) {
            auto res = get_square_key<_CKKS_G_CRT>(context, sk);
            auto res_proto = res.to_proto();
            string res_str = res_proto.SerializeAsString();
            return res_str;
        } else {
            auto res = get_square_key<_RBGV_G_CRT>(context, sk);
            auto res_proto = res.to_proto();
            string res_str = res_proto.SerializeAsString();
            return res_str;
        }
    }

    string raw_create_aux_key(bool is_ckks, string& proto_str) {
        if (is_ckks) {
            KeyAux res = KeyAux<_CKKS_G_CRT>(proto_str);
            std::cout << "KeyAux created" << std::endl;
            auto res_proto = res.to_proto();
            std::cout << "created proto" << std::endl;
            string res_str = res_proto.SerializeAsString();
            return res_str;
        } else {
            KeyAux res = KeyAux<_RBGV_G_CRT>(proto_str);
            std::cout << "KeyAux created" << std::endl;
            auto res_proto = res.to_proto();
            std::cout << "created proto" << std::endl;
            string res_str = res_proto.SerializeAsString();
            return res_str;
        }
    }

} // namespace key_switch
