#pragma once

#include "global_params_and_state.pb.h"
#include "mod_params_and_state.h"
#include "crt_params_and_state.h"
#include "dataclasses.h"

namespace global_params_and_state {

class State {
public:
    State() = default;
    State(const string& proto_str);
    void init(lattica_proto::State proto);
    lattica_proto::State to_proto(optional<lattica_proto::State*> t_proto = nullopt);

    TTensor& q_list();
    int len_q_list() const;
    const Num& get_active_q() const;
    TTensor& get_active_rows();
    TTensor& slice_to_active_q_list(TTensor& a);

    mod_params_and_state::ModState& get_mod_state();
    crt_params_and_state::CrtState& get_crt_state();

private:
    mod_params_and_state::ModState mod_state;
    crt_params_and_state::CrtState crt_state;
};

class GParams {
public:
    GParams() = default;
    GParams(const string& proto_str);
    void init(lattica_proto::GParams proto);
    lattica_proto::GParams to_proto(optional<lattica_proto::GParams*> t_proto = nullopt);

    TTensor& get_g_vec(State& state);
    int get_g_exp() const;

private:
    int g_exp;
    int g_base_bits;
    TTensor g_vec;
};

class Params {
public:
    Params() = default;
    Params(const string& proto_str);
    void init(lattica_proto::Params proto);
    lattica_proto::Params to_proto(optional<lattica_proto::Params*> t_proto = nullopt);

    TTensor& p();
    int p_np();

    perm_utils::CrtPermutations& get_perms_base_crt();
    crt_params_and_state::CrtParams& get_crt_params();
    crt_params_and_state::CrtParams& get_pt_pack_params();
    crt_params_and_state::CrtState& get_pt_pack_state();
    GParams& get_g_params();
    GParams& get_pt_g_params();
    int get_n() const;
    int get_err_std() const;
    int64_t get_pt_scale() const;

private:
    int n;
    int logn;
    int err_std;
    int sk_std;
    int64_t pt_scale;
    GParams g_params;
    GParams pt_g_params;
    crt_params_and_state::CrtParams crt_params;
    crt_params_and_state::CrtParams pt_pack_params;
    mod_params_and_state::ModState pt_mod_state;
    crt_params_and_state::CrtState pt_pack_state;
    TTensor n_range;
    perm_utils::CrtPermutations perms_base_crt;
    c10::complex<double> xi;
};

} // namespace global_params_and_state