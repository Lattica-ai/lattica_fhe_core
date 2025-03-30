#include "context.h"

namespace context {

Context::Context()
    : params(global_params_and_state::Params()),
      init_state(global_params_and_state::State()) {
}

void Context::init(lattica_proto::Context proto) {
    params.init(proto.params());
    init_state.init(proto.init_state());
    is_ckks = proto.is_ckks();
}

lattica_proto::Context Context::to_proto(std::optional<lattica_proto::Context*> t_proto) {
    lattica_proto::Context* proto = t_proto ? t_proto.value() : new lattica_proto::Context();
    lattica_proto::Params* params_proto = proto->mutable_params();
    params.to_proto(params_proto);
    lattica_proto::State* init_state_proto = proto->mutable_init_state();
    init_state.to_proto(init_state_proto);
    proto->set_is_ckks(is_ckks);
    return *proto;
}

Context::Context(std::string& proto_str) : Context() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    lattica_proto::Context proto;
    proto.ParseFromString(proto_str);
    init(proto);
}

} // namespace context
