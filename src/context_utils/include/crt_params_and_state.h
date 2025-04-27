#pragma once

#include "crt_params_and_state.pb.h"
#include "tensor_engine.h"
#include "mod_params_and_state.h"

namespace crt_params_and_state {

class CrtState {
public:
    CrtState() = default;
    CrtState(const std::string& proto_str);
    void init(lattica_proto::CrtState proto);
    lattica_proto::CrtState to_proto(std::optional<lattica_proto::CrtState*> t_proto = std::nullopt);

    TTensor& q_list();
    int len_q_list();

    TTensor& get_active_psi_arr();
    TTensor& get_active_psi_inv_arr();
    TTensor& get_active_n_inv_list();

private:
    mod_params_and_state::ModState mod_state;
    TTensor active_psi_arr;
    TTensor active_psi_inv_arr;
    TTensor active_n_inv_list;
    // bool load_children_to_t_eng = true;
};

class CrtParams {
public:
    CrtParams() = default;
    CrtParams(const std::string& proto_str);
    void init(lattica_proto::CrtParams proto);
    lattica_proto::CrtParams to_proto(std::optional<lattica_proto::CrtParams*> t_proto = std::nullopt);

    int get_n();
    TTensor& get_perm();

private:
    int m;
    int n;
    int logn;
    TTensor perm;
    TTensor perm_pairs;
    // bool load_children_to_t_eng = true;
};

}  // namespace crt_params_and_state