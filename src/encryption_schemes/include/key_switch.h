#pragma once

#include "key_aux.pb.h"
#include "perm_utils_core.h"
#include "perm_utils_extended.h"
#include "pt_shape.h"
#include "mod_ops.h"

namespace key_switch {

    template <class EncryptionScheme>
    typename EncryptionScheme::CiphertextType gen(
        context::Context& context,
        TTensor& sk_inner,
        TTensor& sk_outer
    ) {
        if (sk_inner.dim() < 3)
            sk_inner = sk_inner.unsqueeze(0);
        auto external_shape = sk_inner.sizes().vec();
        external_shape.pop_back();
        pt_shape::PtShape pt_shape = pt_shape::PtShape(
            sk_inner.size(1),
            external_shape,
            1 // n_axis_external
        );
        optional<std::vector<double>> t_pt_scale = nullopt;
        if (context.is_ckks)
            t_pt_scale = std::vector<double>(1, 1);
        auto switch_key = EncryptionScheme().init_ct(
            context, sk_outer, sk_inner, pt_shape, context.init_state, t_pt_scale, false /* is_external */
        );
        return static_cast<typename EncryptionScheme::CiphertextType&>(switch_key);
    }

    template <class EncryptionScheme>
    typename EncryptionScheme::CiphertextType gen_full_key(
        context::Context& context,
        TTensor& sk,
        optional<bool> half_sized = nullopt
    ) {
        perm_utils::CrtPermutations perms_crt_base = perm_utils::get_perms_base_crt(
            context, half_sized
        );
        TTensor sk_permutations = perm_utils::propagate_crt_perms_on_input(
            sk, perms_crt_base, -2, true
        );
        return gen<EncryptionScheme>(context, sk_permutations, sk);
    }

    template <class EncryptionScheme>
    typename EncryptionScheme::CiphertextType gen_base_key(
        context::Context& context,
        TTensor& sk,
        optional<bool> half_sized = nullopt
    ) {
        perm_utils::CrtPermutations perms_crt_base = perm_utils::get_perms_base_crt(
            context, half_sized
        );
        TTensor sk_clone = sk.clone();
        TTensor sk_permutations = perm_utils::apply_crt_permutation(
            sk_clone, perms_crt_base, -2
        );
        auto res = gen<EncryptionScheme>(context, sk_permutations, sk);
        res.a = res.a.moveaxis(0, -4);
        res.b = res.b.moveaxis(0, -4);
        return res;
    }

    template <class EncryptionScheme>
    typename EncryptionScheme::CiphertextType get_square_key(
        context::Context& context,
        TTensor& sk
    ) {
        auto sk_sqr = t_eng::modmul(sk, sk, context.init_state.q_list(), false);
        auto expanded_sk = t_eng::cat({sk.unsqueeze(0), sk_sqr.unsqueeze(0)}, 0);
        return gen<EncryptionScheme>(context, expanded_sk, sk);
    }

    template <class EncryptionScheme>
    class KeyAux {
        public:
        typename EncryptionScheme::CiphertextType base_key;
        typename EncryptionScheme::CiphertextType full_key;
        typename EncryptionScheme::CiphertextType identity_key;
        typename EncryptionScheme::CiphertextType square_key;
        std::vector<lattica_proto::AuxKeyType> required_keys;

        KeyAux() {}

        void init(typename EncryptionScheme::KeyAuxProto proto) {
            required_keys = std::vector<lattica_proto::AuxKeyType>();
            if (proto.has_base_key()) {
                base_key.init(proto.base_key());
                required_keys.push_back(lattica_proto::BASE_KEY);
            }
            if (proto.has_full_key()) {
                full_key.init(proto.full_key());
                required_keys.push_back(lattica_proto::FULL_KEY);
            }
            if (proto.has_identity_key()) {
                identity_key.init(proto.identity_key());
                required_keys.push_back(lattica_proto::IDENTITY_KEY);
            }
            if (proto.has_square_key()) {
                square_key.init(proto.square_key());
                required_keys.push_back(lattica_proto::SQUARE_KEY);
            }
        }

        typename EncryptionScheme::KeyAuxProto to_proto(
                optional<typename EncryptionScheme::KeyAuxProto*> t_proto = nullopt
        ) {
            typename EncryptionScheme::KeyAuxProto* proto = t_proto ? t_proto.value() : new typename EncryptionScheme::KeyAuxProto();
            for (lattica_proto::AuxKeyType key_type : required_keys) {
                switch (key_type) {
                    case lattica_proto::AuxKeyType::BASE_KEY: {
                        typename EncryptionScheme::CiphertextTypeProto* base_key_proto = proto->mutable_base_key();
                        base_key.to_proto(base_key_proto);
                        break;
                    }
                    case lattica_proto::AuxKeyType::FULL_KEY: {
                        typename EncryptionScheme::CiphertextTypeProto* full_key_proto = proto->mutable_full_key();
                        full_key.to_proto(full_key_proto);
                        break;
                    }
                    case lattica_proto::AuxKeyType::IDENTITY_KEY: {
                        typename EncryptionScheme::CiphertextTypeProto* identity_key_proto = proto->mutable_identity_key();
                        identity_key.to_proto(identity_key_proto);
                        break;
                    }
                    case lattica_proto::AuxKeyType::SQUARE_KEY: {
                        typename EncryptionScheme::CiphertextTypeProto* square_key_proto = proto->mutable_square_key();
                        square_key.to_proto(square_key_proto);
                        break;
                    }
                    default:
                        throw std::invalid_argument("Invalid key type");
                }
            }
            return *proto;
        }

        KeyAux(string& proto_str) : KeyAux() {
            GOOGLE_PROTOBUF_VERIFY_VERSION;
            typename EncryptionScheme::KeyAuxProto proto;
            proto.ParseFromString(proto_str);
            init(proto);
        }

        KeyAux init_values(
            context::Context& context,
            TTensor& sk,
            std::vector<lattica_proto::AuxKeyType> t_required_keys
        ) {
            required_keys = t_required_keys;
            for (lattica_proto::AuxKeyType key_type : t_required_keys) {
                switch (key_type) {
                    case lattica_proto::AuxKeyType::BASE_KEY:
                        base_key = gen_base_key<EncryptionScheme>(context, sk, context.is_ckks);
                        break;
                    case lattica_proto::AuxKeyType::FULL_KEY:
                        full_key = gen_full_key<EncryptionScheme>(context, sk, context.is_ckks);
                        break;
                    case lattica_proto::AuxKeyType::IDENTITY_KEY:
                        identity_key = gen<EncryptionScheme>(context, sk, sk);
                        break;
                    case lattica_proto::AuxKeyType::SQUARE_KEY:
                        square_key = get_square_key<EncryptionScheme>(context, sk);
                        break;
                    default:
                        throw std::invalid_argument("Invalid key type");
                }
            }
            return *this;
        }

    };  // class KeyAux

} // namespace key_switch