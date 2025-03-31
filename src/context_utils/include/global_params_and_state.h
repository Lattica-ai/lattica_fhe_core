#pragma once

#include "global_params_and_state.pb.h"
#include "mod_params_and_state.h"
#include "crt_params_and_state.h"
#include "dataclasses.h"

namespace global_params_and_state {

class State {
public:
    mod_params_and_state::ModState mod_state;
    crt_params_and_state::CrtState crt_state;

    State();
    void init(lattica_proto::State proto);
    lattica_proto::State to_proto(optional<lattica_proto::State*> t_proto = nullopt);
    State(string& proto_str);
    
    TTensor& q_list();
    int len_q_list();
    TTensor& active_rows();
};

class GParams {
public:
    int g_exp;
    int g_base_bits;
    TTensor g_vec;

    GParams();
    void init(lattica_proto::GParams proto);
    lattica_proto::GParams to_proto(optional<lattica_proto::GParams*> t_proto = nullopt);
    GParams(string& proto_str);
    
    TTensor& get_g_vec(State state);
};

class Params {
public:
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
    c10_lattica_nspace::complex<double> xi;

    Params();
    void init(lattica_proto::Params proto);
    lattica_proto::Params to_proto(optional<lattica_proto::Params*> t_proto = nullopt);
    Params(string& proto_str);
    
    TTensor& p();
    int p_np();
};

} // namespace global_params_and_state