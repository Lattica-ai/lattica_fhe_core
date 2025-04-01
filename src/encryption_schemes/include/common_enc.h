#pragma once

#include "ciphertexts.pb.h"
#include "tensor_engine.h"
#include "crt_utils.h"
#include "pt_shape.h"

namespace encryption_schemes {

class Ciphertext {
public:
    TTensor a;
    TTensor b;
    pt_shape::PtShape pt_shape;
    std::optional<global_params_and_state::State> state;

    Ciphertext(
        TTensor& t_a,
        TTensor& t_b,
        pt_shape::PtShape& t_pt_shape,
        global_params_and_state::State& t_state
    );

    virtual Ciphertext init_from_ct_and_state(
        Ciphertext& ct,
        global_params_and_state::State& t_state
    );

    Ciphertext();

    virtual void init(lattica_proto::Ciphertext proto);

    lattica_proto::Ciphertext to_proto(optional<lattica_proto::Ciphertext*> t_proto = nullopt);

    Ciphertext(string& proto_str);

    virtual Ciphertext make_copy(
        optional<TTensor> t_a = {},
        optional<TTensor> t_b = {},
        optional<pt_shape::PtShape> t_pt_shape = {},
        optional<global_params_and_state::State> t_state = {}
    );

    virtual Ciphertext get_item(at::ArrayRef<at::indexing::TensorIndex> indices);

    virtual void pack_for_transmission();

    virtual void unpack_from_transmission(global_params_and_state::State& t_state);
};

class AbstractEncryptionScheme {
public:
    std::tuple<TTensor, TTensor> _sample_randomness(
        context::Context& context,
        global_params_and_state::State& state,
        pt_shape::PtShape& pt_shape,
        TTensorShape additional_dims = {},
        int n_axis = -2
    );

    virtual std::tuple<TTensor, TTensor> sample_randomness(
        context::Context& context,
        pt_shape::PtShape& pt_shape,
        optional<global_params_and_state::State> t_state
    );

    std::tuple<TTensor, TTensor> sample_secret_key(
        context::Context& context,
        optional<global_params_and_state::State> t_state
    );

    virtual TTensor _enc(
        context::Context& context,
        global_params_and_state::State& state,
        TTensor& pt,
        TTensor& sk,
        TTensor& a,
        TTensor& e
    );

    virtual TTensor pack_pt(
        context::Context& context,
        TTensor& pt,
        optional<std::vector<double>> t_pt_scale = nullopt
    );

    virtual std::tuple<TTensor, TTensor> dec_and_get_error(
        context::Context& context,
        TTensor& sk,
        Ciphertext& ct
    );

    TTensor dec(
        context::Context& context,
        TTensor& sk,
        Ciphertext& ct,
        bool convert_to_external=true
    );

    virtual TTensor unpack_pt(
        context::Context& context,
        TTensor& pt_packed,
        optional<std::vector<double>> t_pt_scale = nullopt
    );

    virtual TTensor dec_and_unpack(
        context::Context& context,
        TTensor& sk,
        Ciphertext& ct,
        bool convert_to_external=true
    );

    virtual Ciphertext apply_mod_switch_down_drop(
        Ciphertext& ct,
        Slice relative_new_indices
    );
};

class AbstractCiphertextInitializer : public AbstractEncryptionScheme {
public:
    Ciphertext _init_ct(
        context::Context& context,
        TTensor& sk,
        TTensor& pt,
        pt_shape::PtShape& pt_shape,
        optional<global_params_and_state::State> t_state,
        bool is_external=true
    );
};

} // namespace encryption_schemes