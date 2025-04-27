#include "common_tensor_engine.h"
#include "serialization_utils.h"
#include "crt_params_and_state.h"
#include "ntt_utils.h"

namespace ntt_utils {

string raw_ntt(
        const string& crt_params_proto_str,
        const string& crt_state_proto_str,
        const string& serialized_a,
        int axis,
        bool inplace) {

    TTensor a = serialization_utils::deser_tensor_from_str(serialized_a);
    crt_params_and_state::CrtParams crt_params = crt_params_and_state::CrtParams(crt_params_proto_str);
    crt_params_and_state::CrtState crt_state = crt_params_and_state::CrtState(crt_state_proto_str);

    auto res = ntt(crt_params, crt_state, a, axis, inplace);
    return serialization_utils::ser_tensor_to_bytes(res);
}

string raw_intt(
        const string& crt_params_proto_str,
        const string& crt_state_proto_str,
        const string& serialized_a,
        int axis) {

    crt_params_and_state::CrtParams crt_params = crt_params_and_state::CrtParams(crt_params_proto_str);
    crt_params_and_state::CrtState crt_state = crt_params_and_state::CrtState(crt_state_proto_str);
    TTensor a = serialization_utils::deser_tensor_from_str(serialized_a);

    auto res = intt(crt_params, crt_state, a, axis);
    return serialization_utils::ser_tensor_to_bytes(res);
}

} // namespace ntt_utils
