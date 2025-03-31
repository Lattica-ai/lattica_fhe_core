#include "common_homomorphic_operations.h"
#include "abstract.h"
#include "apply_clear.h"

namespace homom_ops {

string raw_create_query_client_block(string& proto_str) {
    QueryClientBlock res = QueryClientBlock(proto_str);
    std::cout << "QueryClientBlock created" << std::endl;
    auto res_proto = res.to_proto();
    std::cout << "created proto" << std::endl;
    string res_str = res_proto.SerializeAsString();
    std::cout << "created res_str" << std::endl;
    return res_str;
}

string raw_create_query_client_sequential_hom_op(string& proto_str) {
    QueryClientSequentialHomOp res = QueryClientSequentialHomOp(proto_str);
    std::cout << "QueryClientSequentialHomOp created" << std::endl;
    auto res_proto = res.to_proto();
    std::cout << "created proto" << std::endl;
    string res_str = res_proto.SerializeAsString();
    std::cout << "created res_str" << std::endl;
    return res_str;
}

string raw_apply_clear(
    int64_t op_type_int,
    string& serialized_context,
    string& serialized_pt,
    string& serialized_apply_clear_params) {
    context::Context context = context::Context(serialized_context);
    lattica_proto::TensorHolder pt_proto = lattica_proto::TensorHolder();
    pt_proto.ParseFromString(serialized_pt);
    TTensor pt = serialization_utils::deser_tensor(pt_proto);
    lattica_proto::ApplyClearParams apply_clear_params_proto;
    apply_clear_params_proto.ParseFromString(serialized_apply_clear_params);
    lattica_proto::HomOpType op_type = static_cast<lattica_proto::HomOpType>(op_type_int);

    TTensor res = apply_clear(op_type, context, pt, apply_clear_params_proto);

    lattica_proto::TensorHolder res_proto = lattica_proto::TensorHolder();
    serialization_utils::ser_tensor(res, &res_proto);
    return res_proto.SerializeAsString();
}

} // namespace homom_ops
