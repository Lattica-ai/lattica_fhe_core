#pragma once

#include "context.pb.h"
#include "global_params_and_state.h"

namespace context {

class Context {
public:
    Context() = default;
    Context(const std::string& proto_str);

    void init(lattica_proto::Context proto);
    lattica_proto::Context to_proto(std::optional<lattica_proto::Context*> t_proto = std::nullopt);

    TTensor& p();
    int p_np();
    perm_utils::CrtPermutations& get_perms_base_crt();
    crt_params_and_state::CrtParams& get_crt_params();
    global_params_and_state::State& get_state();
    global_params_and_state::GParams& get_g_params();
    global_params_and_state::GParams& get_pt_g_params();
    int get_n();
    int get_err_std();
    TTensor& get_q_list();
    int64_t get_pt_scale();
    bool is_ckks() const;
    const Num& get_active_q() const;
    crt_params_and_state::CrtParams& get_pt_pack_params();
    crt_params_and_state::CrtState& get_pt_pack_state();

private:
    global_params_and_state::Params params;
    global_params_and_state::State init_state;
    bool is_ckks_;
};

} // namespace context
