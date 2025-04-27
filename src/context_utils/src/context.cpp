#include "context.h"

namespace context {

Context::Context(const std::string& proto_str) : Context() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    lattica_proto::Context proto;
    proto.ParseFromString(proto_str);
    init(proto);
}

void Context::init(lattica_proto::Context proto) {
    params.init(proto.params());
    init_state.init(proto.init_state());
    is_ckks_ = proto.is_ckks();
}

lattica_proto::Context Context::to_proto(std::optional<lattica_proto::Context*> t_proto) {
    lattica_proto::Context* proto = t_proto ? t_proto.value() : new lattica_proto::Context();
    lattica_proto::Params* params_proto = proto->mutable_params();
    params.to_proto(params_proto);
    lattica_proto::State* init_state_proto = proto->mutable_init_state();
    init_state.to_proto(init_state_proto);
    proto->set_is_ckks(is_ckks_);
    return *proto;
}

TTensor& Context::p() {
    return params.p();
}

int Context::p_np() {
    return params.p_np();
}

perm_utils::CrtPermutations& Context::get_perms_base_crt() {
    return params.get_perms_base_crt();
}

crt_params_and_state::CrtParams& Context::get_crt_params() {
    return params.get_crt_params();
}

global_params_and_state::State& Context::get_state() {
    return init_state;
}

global_params_and_state::GParams& Context::get_g_params() {
    return params.get_g_params();
}

global_params_and_state::GParams& Context::get_pt_g_params() {
    return params.get_pt_g_params();
}

int Context::get_n() {
    return params.get_n();
}

int Context::get_err_std() {
    return params.get_err_std();
}

TTensor& Context::get_q_list() {
    return init_state.q_list();
}

int64_t Context::get_pt_scale() {
    return params.get_pt_scale();
}

bool Context::is_ckks() const {
    return is_ckks_;
}

const Num& Context::get_active_q() const {
    return init_state.get_active_q();
}

crt_params_and_state::CrtParams& Context::get_pt_pack_params() {
    return params.get_pt_pack_params();
}

crt_params_and_state::CrtState& Context::get_pt_pack_state() {
    return params.get_pt_pack_state();
}

} // namespace context
