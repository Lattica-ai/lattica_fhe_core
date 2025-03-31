#include "common_context_utils.h"
#include "serialization_utils.h"
#include <iostream>

namespace context {

string raw_create_context(string& proto_str) {
    Context res = Context(proto_str);
    std::cout << "Context created" << std::endl;
    auto res_proto = res.to_proto();
    std::cout << "created proto" << std::endl;
    string res_str = res_proto.SerializeAsString();
    std::cout << "created res_str" << std::endl;
    return res_str;
}

} // namespace context

namespace global_params_and_state {

string raw_create_params(string& proto_str) {
    Params res = Params(proto_str);
    std::cout << "Params created" << std::endl;
    auto res_proto = res.to_proto();
    std::cout << "created proto" << std::endl;
    string res_str = res_proto.SerializeAsString();
    std::cout << "created res_str" << std::endl;
    return res_str;
}

string raw_create_state(string& proto_str) {
    State res = State(proto_str);
    std::cout << "State created" << std::endl;
    auto res_proto = res.to_proto();
    std::cout << "created proto" << std::endl;
    string res_str = res_proto.SerializeAsString();
    std::cout << "created res_str" << std::endl;
    return res_str;
}

} // namespace global_params_and_state

namespace crt_params_and_state {

string raw_create_crt_params(string& proto_str) {
    CrtParams res = CrtParams(proto_str);
    std::cout << "CrtParams created" << std::endl;
    auto res_proto = res.to_proto();
    std::cout << "created proto" << std::endl;
    string res_str = res_proto.SerializeAsString();
    std::cout << "created res_str" << std::endl;
    return res_str;
}

string raw_create_crt_state(string& proto_str) {
    CrtState res = CrtState(proto_str);
    std::cout << "CrtState created" << std::endl;
    std::cout << "active_q_list: " << res.mod_state.active_q_list << std::endl;
    auto res_proto = res.to_proto();
    std::cout << "created proto" << std::endl;
    string res_str = res_proto.SerializeAsString();
    std::cout << "created res_str" << std::endl;
    return res_str;
}

} // namespace crt_params_and_state

namespace mod_params_and_state {

string raw_create_mod_state(string& proto_str) {
    ModState res = ModState(proto_str);
    std::cout << "ModState created" << std::endl;
    std::cout << "active_q_list: " << res.active_q_list << std::endl;
    auto res_proto = res.to_proto();
    std::cout << "created proto" << std::endl;
    string res_str = res_proto.SerializeAsString();
    std::cout << "created res_str" << std::endl;
    return res_str;
}

} // namespace mod_params_and_state

namespace crt_utils {

string raw_crt_to_coefs(
        string& crt_params_proto_str,
        string& crt_state_proto_str,
        string& serialized_a,
        int axis,
        bool tile) {
    crt_params_and_state::CrtParams crt_params = crt_params_and_state::CrtParams(crt_params_proto_str);
    crt_params_and_state::CrtState crt_state = crt_params_and_state::CrtState(crt_state_proto_str);
    TTensor a = serialization_utils::deser_tensor_from_str(serialized_a);
    TTensor res = crt_to_coefs(crt_params, crt_state, a, axis, tile);
    return serialization_utils::ser_tensor_to_bytes(res);
}

string raw_coefs_to_crt(
        string& crt_params_proto_str,
        string& crt_state_proto_str,
        string& serialized_a,
        int axis,
        bool tile) {
    crt_params_and_state::CrtParams crt_params = crt_params_and_state::CrtParams(crt_params_proto_str);
    crt_params_and_state::CrtState crt_state = crt_params_and_state::CrtState(crt_state_proto_str);
    TTensor a = serialization_utils::deser_tensor_from_str(serialized_a);
    TTensor res = coefs_to_crt(crt_params, crt_state, a, axis, tile);
    return serialization_utils::ser_tensor_to_bytes(res);
}

string raw_crt_to_coefs_q(
        string& ctx_proto_str,
        string& state_proto_str,
        string& serialized_a,
        int axis,
        bool tile) {
    context::Context ctx = context::Context(ctx_proto_str);
    global_params_and_state::State state = global_params_and_state::State(state_proto_str);
    TTensor a = serialization_utils::deser_tensor_from_str(serialized_a);
    TTensor res = crt_to_coefs_q(ctx, state, a, axis, tile);
    return serialization_utils::ser_tensor_to_bytes(res);
}

string raw_coefs_to_crt_q(
        string& ctx_proto_str,
        string& state_proto_str,
        string& serialized_a,
        int axis,
        bool tile) {
    context::Context ctx = context::Context(ctx_proto_str);
    global_params_and_state::State state = global_params_and_state::State(state_proto_str);
    TTensor a = serialization_utils::deser_tensor_from_str(serialized_a);
    TTensor res = coefs_to_crt_q(ctx, state, a, axis, tile);
    return serialization_utils::ser_tensor_to_bytes(res);
}

string raw_crt_to_coefs_p(
        string& ctx_proto_str,
        string& serialized_a) {
    context::Context ctx = context::Context(ctx_proto_str);
    TTensor a = serialization_utils::deser_tensor_from_str(serialized_a);
    TTensor res = crt_to_coefs_p(ctx, a);
    return serialization_utils::ser_tensor_to_bytes(res);
}

string raw_coefs_to_crt_p(
        string& ctx_proto_str,
        string& serialized_a) {
    context::Context ctx = context::Context(ctx_proto_str);
    TTensor a = serialization_utils::deser_tensor_from_str(serialized_a);
    TTensor res = coefs_to_crt_p(ctx, a);
    return serialization_utils::ser_tensor_to_bytes(res);
}

} // namespace crt_utils

namespace mod_utils {

string raw_to_crt_tensor(string& serialized_q_list, string& serialized_a) {
    TTensor q_list = serialization_utils::deser_tensor_from_str(serialized_q_list);
    TTensor a = serialization_utils::deser_tensor_from_str(serialized_a);
    TTensor res = to_crt_tensor(q_list, a);
    return serialization_utils::ser_tensor_to_bytes(res);
}

std::vector<string> raw_from_crt_tensor_to_bigint(
    string& mod_state_proto_str,
    string& serialized_a,
    string final_mod) {
    mod_params_and_state::ModState mod_state = mod_params_and_state::ModState(mod_state_proto_str);
    TTensor a = serialization_utils::deser_tensor_from_str(serialized_a);
    std::vector<string> res = from_crt_tensor_to_bigint(mod_state, a, final_mod);
    return res;
}

} // namespace mod_utils
