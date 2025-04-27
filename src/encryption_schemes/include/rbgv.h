#pragma once

#include "ciphertexts.pb.h"
#include "key_aux.pb.h"
#include "pt_shape.h"
#include "common_enc.h"

namespace encryption_schemes {

class RBGV_Ciphertext : public Ciphertext {
public:
    RBGV_Ciphertext() = default;
    RBGV_Ciphertext(const string& proto_str);
    RBGV_Ciphertext(
        TTensor& t_a,
        TTensor& t_b,
        pt_shape::PtShape& t_pt_shape,
        global_params_and_state::State& t_state,
        int t_correction_factor = 1
    );

    Ciphertext init_from_ct_and_state(
        RBGV_Ciphertext& ct,
        global_params_and_state::State& t_state
    );

    void init(lattica_proto::RBGV_Ciphertext proto);
    lattica_proto::RBGV_Ciphertext to_proto(optional<lattica_proto::RBGV_Ciphertext*> t_proto = nullopt);
    virtual Ciphertext make_copy(
        optional<TTensor> t_a = {},
        optional<TTensor> t_b = {},
        optional<pt_shape::PtShape> t_pt_shape = {},
        optional<global_params_and_state::State> t_state = {}
    );

    int get_correction_factor() const;

private:
    int correction_factor = 1;
};

class _RBGV : public AbstractCiphertextInitializer {
public:
    typedef RBGV_Ciphertext CiphertextType;
    typedef lattica_proto::RBGV_Ciphertext CiphertextTypeProto;
    typedef lattica_proto::RBGV_AuxKey KeyAuxProto;

    RBGV_Ciphertext init_ct(
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

    RBGV_Ciphertext pack_and_init_ct(
        context::Context& context,
        TTensor& sk,
        TTensor& pt,
        pt_shape::PtShape& pt_shape,
        optional<global_params_and_state::State> t_state,
        bool is_external = true
    );

    std::tuple<TTensor, TTensor> dec_and_get_error(
        context::Context& context,
        TTensor& sk_coefs,
        Ciphertext& ct
    ) override;

    TTensor unpack_pt(
        context::Context& context,
        TTensor& pt_packed,
        optional<std::vector<double>> t_pt_scale = nullopt
    ) override;

    TTensor to_default_pt_tensor(TTensor& pt);
};

} // namespace encryption_schemes