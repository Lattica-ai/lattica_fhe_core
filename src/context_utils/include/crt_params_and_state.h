#pragma once

#include "crt_params_and_state.pb.h"
#include "tensor_engine.h"
#include "mod_params_and_state.h"

namespace crt_params_and_state {

class CrtState {
public:
    mod_params_and_state::ModState mod_state;
    TTensor active_psi_arr;
    TTensor active_psi_inv_arr;
    TTensor active_n_inv_list;
    bool load_children_to_t_eng = true;

    CrtState();
    
    void init(lattica_proto::CrtState proto);
    lattica_proto::CrtState to_proto(std::optional<lattica_proto::CrtState*> t_proto = std::nullopt);
    CrtState(std::string& proto_str);
    
    TTensor& q_list();
    int len_q_list();
};

class CrtParams {
public:
    int m;
    int n;
    int logn;
    TTensor perm;
    TTensor perm_pairs;
    bool load_children_to_t_eng = true;

    CrtParams();
    
    void init(lattica_proto::CrtParams proto);
    lattica_proto::CrtParams to_proto(std::optional<lattica_proto::CrtParams*> t_proto = std::nullopt);
    CrtParams(std::string& proto_str);
};

}  // namespace crt_params_and_state