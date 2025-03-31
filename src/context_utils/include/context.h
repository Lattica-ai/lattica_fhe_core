#pragma once

#include "context.pb.h"
#include "global_params_and_state.h"

namespace context {

class Context {
public:
    global_params_and_state::Params params;
    global_params_and_state::State init_state;
    bool is_ckks;

    Context();
    void init(lattica_proto::Context proto);
    lattica_proto::Context to_proto(std::optional<lattica_proto::Context*> t_proto = std::nullopt);
    Context(std::string& proto_str);
};

} // namespace context
