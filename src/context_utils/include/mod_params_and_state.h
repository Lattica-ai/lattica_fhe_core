#pragma once
#include "mod_params_and_state.pb.h"
#include "serialization_utils.h"
#include "num.h"

namespace mod_params_and_state {

class ModState {
public:
    Num active_q;
    int active_len_q_list;
    TTensor active_q_list;
    TTensor active_rows;
    TTensor active_cols;
    std::vector<Num> active_reconstruction_terms;

    ModState();
    ModState(string& proto_str);
    void init(lattica_proto::ModState proto);
    lattica_proto::ModState to_proto(optional<lattica_proto::ModState*> t_proto = nullopt);
    TTensor& q_list();
    int len_q_list();
    TTensor& slice_to_active_q_list(TTensor& a);
};

} // namespace mod_params_and_state