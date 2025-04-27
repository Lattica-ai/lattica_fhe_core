#include "global_params_and_state.h"

namespace global_params_and_state {

// State implementation

State::State(const string& proto_str) : State() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    lattica_proto::State proto;
    proto.ParseFromString(proto_str);
    init(proto);
}

void State::init(lattica_proto::State proto) {
    mod_state.init(proto.mod_state());
    crt_state.init(proto.crt_state());
}

lattica_proto::State State::to_proto(optional<lattica_proto::State*> t_proto) {
    lattica_proto::State* proto = t_proto ? t_proto.value() : new lattica_proto::State();
    lattica_proto::ModState* mod_state_proto = proto->mutable_mod_state();
    mod_state.to_proto(mod_state_proto);
    lattica_proto::CrtState* crt_state_proto = proto->mutable_crt_state();
    crt_state.to_proto(crt_state_proto);
    return *proto;
}

TTensor& State::q_list() {
    return mod_state.q_list();
}

int State::len_q_list() const {
    return mod_state.len_q_list();
}

const Num& State::get_active_q() const {
    return mod_state.get_active_q();
}

TTensor& State::get_active_rows() {
    return mod_state.get_active_rows();
}

TTensor& State::slice_to_active_q_list(TTensor& a) {
    return mod_state.slice_to_active_q_list(a);
}

mod_params_and_state::ModState& State::get_mod_state() {
    return mod_state;
}

crt_params_and_state::CrtState& State::get_crt_state() {
    return crt_state;
}

// GParams implementation

GParams::GParams(const string& proto_str) : GParams() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    lattica_proto::GParams proto;
    proto.ParseFromString(proto_str);
    init(proto);
}

void GParams::init(lattica_proto::GParams proto) {
    g_exp = proto.g_exp();
    g_base_bits = proto.g_base_bits();
    g_vec = serialization_utils::deser_tensor(proto.g_vec());
}

lattica_proto::GParams GParams::to_proto(optional<lattica_proto::GParams*> t_proto) {
    lattica_proto::GParams* proto = t_proto ? t_proto.value() : new lattica_proto::GParams();
    proto->set_g_exp(g_exp);
    proto->set_g_base_bits(g_base_bits);
    serialization_utils::ser_tensor(g_vec, proto->mutable_g_vec());
    return *proto;
}

TTensor& GParams::get_g_vec(State& state) {
    return state.slice_to_active_q_list(g_vec);
}

int GParams::get_g_exp() const {
    return g_exp;
}

// Params implementation

Params::Params(const string& proto_str) : Params() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    lattica_proto::Params proto;
    proto.ParseFromString(proto_str);
    init(proto);
}

void Params::init(lattica_proto::Params proto) {
    n = proto.n();
    logn = proto.logn();
    err_std = proto.err_std();
    sk_std = proto.sk_std();
    pt_scale = proto.pt_scale();
    g_params.init(proto.g_params());
    pt_g_params.init(proto.pt_g_params());
    crt_params.init(proto.crt_params());
    pt_pack_params.init(proto.pt_pack_params());
    pt_mod_state.init(proto.pt_mod_state());
    pt_pack_state.init(proto.pt_pack_state());
    n_range = serialization_utils::deser_tensor(proto.n_range());
    perms_base_crt.init(proto.perms_base_crt());
    xi = c10::complex<double>(proto.xi().real(), proto.xi().imag());
}

lattica_proto::Params Params::to_proto(optional<lattica_proto::Params*> t_proto) {
    lattica_proto::Params* proto = t_proto ? t_proto.value() : new lattica_proto::Params();
    proto->set_n(n);
    proto->set_logn(logn);
    proto->set_err_std(err_std);
    proto->set_sk_std(sk_std);
    proto->set_pt_scale(pt_scale);
    lattica_proto::GParams* g_params_proto = proto->mutable_g_params();
    g_params.to_proto(g_params_proto);
    lattica_proto::GParams* pt_g_params_proto = proto->mutable_pt_g_params();
    pt_g_params.to_proto(pt_g_params_proto);
    lattica_proto::CrtParams* crt_params_proto = proto->mutable_crt_params();
    crt_params.to_proto(crt_params_proto);
    lattica_proto::CrtParams* pt_pack_params_proto = proto->mutable_pt_pack_params();
    pt_pack_params.to_proto(pt_pack_params_proto);
    lattica_proto::ModState* pt_mod_state_proto = proto->mutable_pt_mod_state();
    pt_mod_state.to_proto(pt_mod_state_proto);
    lattica_proto::CrtState* pt_pack_state_proto = proto->mutable_pt_pack_state();
    pt_pack_state.to_proto(pt_pack_state_proto);
    serialization_utils::ser_tensor(n_range, proto->mutable_n_range());
    lattica_proto::CrtPermutations* perms_base_crt_proto = proto->mutable_perms_base_crt();
    perms_base_crt.to_proto(perms_base_crt_proto);
    lattica_proto::Complex* xi_proto = proto->mutable_xi();
    xi_proto->set_real(xi.real());
    xi_proto->set_imag(xi.imag());
    return *proto;
}

TTensor& Params::p() {
    return pt_mod_state.q_list();
}

int Params::p_np() {
    return p()[0].item<SINGLE_PRECISION>();
}

perm_utils::CrtPermutations& Params::get_perms_base_crt() {
    return perms_base_crt;
}

crt_params_and_state::CrtParams& Params::get_crt_params() {
    return crt_params;
}

crt_params_and_state::CrtParams& Params::get_pt_pack_params() {
    return pt_pack_params;
}

crt_params_and_state::CrtState& Params::get_pt_pack_state() {
    return pt_pack_state;
}

GParams& Params::get_g_params() {
    return g_params;
}

GParams& Params::get_pt_g_params() {
    return pt_g_params;
}

int Params::get_n() const {
    return n;
}

int Params::get_err_std() const {
    return err_std;
}

int64_t Params::get_pt_scale() const {
    return pt_scale;
}

} // namespace global_params_and_state
