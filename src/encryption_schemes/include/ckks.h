#pragma once

#include "ciphertexts.pb.h"
#include "key_aux.pb.h"
#include "common_enc.h"
#include "mod_utils.h"

namespace encryption_schemes {

class CKKS_Ciphertext : public Ciphertext {
public:
    std::vector<double> pt_scale;

    CKKS_Ciphertext(
        TTensor& t_a, TTensor& t_b,
        pt_shape::PtShape& t_pt_shape,
        global_params_and_state::State& t_state,
        std::vector<double> t_pt_scale
    );

    virtual Ciphertext init_from_ct_and_state(
        CKKS_Ciphertext& ct,
        global_params_and_state::State& t_state
    );

    CKKS_Ciphertext();

    virtual void init(lattica_proto::CKKS_Ciphertext proto);

    lattica_proto::CKKS_Ciphertext to_proto(optional<lattica_proto::CKKS_Ciphertext*> t_proto = nullopt);

    CKKS_Ciphertext(string& proto_str);

    virtual Ciphertext make_copy(
        optional<TTensor> t_a = {},
        optional<TTensor> t_b = {},
        optional<pt_shape::PtShape> t_pt_shape = {},
        optional<global_params_and_state::State> t_state = {}
    );
}; // class CKKS_Ciphertext

struct packPtArgs {
    TTensor pt;
    TTensor col;
    TTensor result;
    int64_t start;
    int64_t end;
};

class _CKKS : public AbstractCiphertextInitializer {
public:
    typedef CKKS_Ciphertext CiphertextType;
    typedef lattica_proto::CKKS_Ciphertext CiphertextTypeProto;
    typedef lattica_proto::CKKS_AuxKey KeyAuxProto;

    CKKS_Ciphertext init_ct(
        context::Context& context,
        TTensor& sk,
        TTensor& pt,
        pt_shape::PtShape& pt_shape,
        optional<global_params_and_state::State> t_state,
        optional<std::vector<double>> t_pt_scale = nullopt,
        bool is_external = true
    );

    virtual TTensor _enc(
        context::Context& context,
        global_params_and_state::State& state,
        TTensor& pt,
        TTensor& sk,
        TTensor& a,
        TTensor& e
    ) override;

    TTensor pack_pt(
        context::Context& context,
        TTensor& pt,
        optional<std::vector<double>> t_pt_scale = nullopt
    ) override;

    std::tuple<TTensor, TTensor> dec_and_get_error(
        context::Context& context,
        TTensor& sk_coefs,
        Ciphertext& ct
    ) override;

    TTensor unpack_pt(
        context::Context& context,
        TTensor& pt_packed,
        optional<std::vector<double>> t_pt_scale
    ) override;

    CKKS_Ciphertext pack_and_init_ct(
        context::Context& context,
        TTensor& sk,
        TTensor& pt,
        pt_shape::PtShape& pt_shape,
        optional<global_params_and_state::State> t_state,
        bool is_external = true
    );

    TTensor dec_and_unpack(
        context::Context& context,
        TTensor& sk,
        Ciphertext& ct,
        bool convert_to_external = true
    ) override;

    TTensor to_default_pt_tensor(TTensor& pt);
}; // class _CKKS

} // namespace encryption_schemes