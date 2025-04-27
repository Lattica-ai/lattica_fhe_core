#include "mod_params_and_state.h"

namespace mod_params_and_state {

void ModState::init(lattica_proto::ModState proto) {
    active_q = Num(proto.active_q().data().c_str());
    active_len_q_list = proto.active_len_q_list();
    active_q_list = serialization_utils::deser_tensor(proto.active_q_list());
    active_rows = serialization_utils::deser_tensor(proto.active_rows());
    active_cols = serialization_utils::deser_tensor(proto.active_cols());
    active_reconstruction_terms = std::vector<Num>();
    int num_recon_terms = proto.active_reconstruction_terms_size();
    for (int i = 0; i < num_recon_terms; i++) {
        Num recon_term(proto.active_reconstruction_terms(i).data().c_str());
        active_reconstruction_terms.push_back(recon_term);
    }
}

lattica_proto::ModState ModState::to_proto(optional<lattica_proto::ModState*> t_proto) {
    lattica_proto::ModState* proto = t_proto ? t_proto.value() : new lattica_proto::ModState();
    lattica_proto::BigInt* active_q_proto = proto->mutable_active_q();
    std::vector<char> active_q_vec_char;
    active_q.print(active_q_vec_char);
    std::string active_q_str(active_q_vec_char.begin(), active_q_vec_char.end() - 1);
    active_q_proto->set_data(active_q_str);
    proto->set_active_len_q_list(active_len_q_list);
    serialization_utils::ser_tensor(active_q_list, proto->mutable_active_q_list());
    serialization_utils::ser_tensor(active_rows, proto->mutable_active_rows());
    serialization_utils::ser_tensor(active_cols, proto->mutable_active_cols());
    int num_recon_terms = active_reconstruction_terms.size();
    for (int i = 0; i < num_recon_terms; i++) {
        Num recon_term = active_reconstruction_terms[i];
        lattica_proto::BigInt* recon_term_proto = proto->add_active_reconstruction_terms();
        std::vector<char> recon_term_vec_char;
        recon_term.print(recon_term_vec_char);
        std::string recon_term_str(recon_term_vec_char.begin(), recon_term_vec_char.end() - 1);
        recon_term_proto->set_data(recon_term_str);
    }
    return *proto;
}

ModState::ModState(const string& proto_str) : ModState() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    lattica_proto::ModState proto;
    proto.ParseFromString(proto_str);
    init(proto);
}

TTensor& ModState::slice_to_active_q_list(TTensor& a) {
    std::vector<int64_t> orig_shape = a.sizes().vec();
    a = a.reshape({-1, a.size(-2), a.size(-1)});
    a = a.index({Slice(None), active_rows, Slice(None)});
    TTensor cols_view = active_cols.unsqueeze(0).unsqueeze(-1);
    a = t_eng::take_along_axis(a, cols_view, -1);
    a = a.flatten(0, -3);
    orig_shape.resize(a.dim() - 2);
    orig_shape.push_back(-1);
    a = a.reshape(orig_shape);
    return a;
}

TTensor& ModState::q_list() {
    return active_q_list;
}

int ModState::len_q_list() const {
    return active_len_q_list;
}

const Num& ModState::get_active_q() const {
    return active_q;
}

TTensor& ModState::get_active_rows() {
    return active_rows;
}

size_t ModState::get_active_reconstruction_terms_size() const {
    return active_reconstruction_terms.size();
}

const Num& ModState::get_active_reconstruction_terms(int i) const  {
    return active_reconstruction_terms[i];
}

} // namespace mod_params_and_state
