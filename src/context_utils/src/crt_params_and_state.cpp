#include "crt_params_and_state.h"
#include "serialization_utils.h"

namespace crt_params_and_state {

CrtState::CrtState() : mod_state(mod_params_and_state::ModState()) {}

void CrtState::init(lattica_proto::CrtState proto) {
    mod_state.init(proto.mod_state());
    active_psi_arr = serialization_utils::deser_tensor(proto.active_psi_arr());
    active_psi_inv_arr = serialization_utils::deser_tensor(proto.active_psi_inv_arr());
    active_n_inv_list = serialization_utils::deser_tensor(proto.active_n_inv_list());
}

lattica_proto::CrtState CrtState::to_proto(std::optional<lattica_proto::CrtState*> t_proto) {
    lattica_proto::CrtState* proto = t_proto ? t_proto.value() : new lattica_proto::CrtState();
    lattica_proto::ModState* mod_state_proto = proto->mutable_mod_state();
    mod_state.to_proto(mod_state_proto);
    serialization_utils::ser_tensor(active_psi_arr, proto->mutable_active_psi_arr());
    serialization_utils::ser_tensor(active_psi_inv_arr, proto->mutable_active_psi_inv_arr());
    serialization_utils::ser_tensor(active_n_inv_list, proto->mutable_active_n_inv_list());
    return *proto;
}

CrtState::CrtState(std::string& proto_str) : CrtState() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    lattica_proto::CrtState proto;
    proto.ParseFromString(proto_str);
    init(proto);
}

TTensor& CrtState::q_list() { 
    return mod_state.q_list(); 
}

int CrtState::len_q_list() { 
    return mod_state.len_q_list(); 
}

CrtParams::CrtParams() {}

void CrtParams::init(lattica_proto::CrtParams proto) {
    m = proto.m();
    n = proto.n();
    logn = proto.logn();
    perm = serialization_utils::deser_tensor(proto.perm());
    perm_pairs = serialization_utils::deser_tensor(proto.perm_pairs());
}

lattica_proto::CrtParams CrtParams::to_proto(std::optional<lattica_proto::CrtParams*> t_proto) {
    lattica_proto::CrtParams* proto = t_proto ? t_proto.value() : new lattica_proto::CrtParams();
    proto->set_m(m);
    proto->set_n(n);
    proto->set_logn(logn);
    serialization_utils::ser_tensor(perm, proto->mutable_perm());
    serialization_utils::ser_tensor(perm_pairs, proto->mutable_perm_pairs());
    return *proto;
}

CrtParams::CrtParams(std::string& proto_str) : CrtParams() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    lattica_proto::CrtParams proto;
    proto.ParseFromString(proto_str);
    init(proto);
}

}  // namespace crt_params_and_state
