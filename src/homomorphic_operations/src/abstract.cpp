#include "abstract.h"

namespace homom_ops {

// QueryClientBlock implementation
QueryClientBlock::QueryClientBlock() {}

void QueryClientBlock::init(lattica_proto::QueryClientBlock proto) {
    block_index = proto.block_index();
    is_last = proto.is_last();
    
    int num_op_types = proto.op_types_size();
    for (int i = 0; i < num_op_types; i++) {
        op_types.push_back(static_cast<lattica_proto::HomOpType>(proto.op_types(i)));
    }
    
    int num_apply_clear_params = proto.apply_clear_params_list_size();
    for (int i = 0; i < num_apply_clear_params; i++) {
        apply_clear_params_list.push_back(proto.apply_clear_params_list(i));
    }
}

lattica_proto::QueryClientBlock QueryClientBlock::to_proto(std::optional<lattica_proto::QueryClientBlock*> t_proto) {
    lattica_proto::QueryClientBlock* proto = t_proto ? t_proto.value() : new lattica_proto::QueryClientBlock();
    proto->set_block_index(block_index);
    proto->set_is_last(is_last);
    
    int num_op_types = op_types.size();
    for (int i = 0; i < num_op_types; i++) {
        proto->add_op_types(static_cast<lattica_proto::HomOpType>(op_types[i]));
    }
    
    int num_apply_clear_params = apply_clear_params_list.size();
    for (int i = 0; i < num_apply_clear_params; i++) {
        lattica_proto::ApplyClearParams* apply_clear_params_proto = proto->add_apply_clear_params_list();
        apply_clear_params_proto->CopyFrom(apply_clear_params_list[i]);
    }
    
    return *proto;
}

QueryClientBlock::QueryClientBlock(std::string& proto_str) : QueryClientBlock() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    lattica_proto::QueryClientBlock proto;
    proto.ParseFromString(proto_str);
    init(proto);
}

// QueryClientSequentialHomOp implementation
QueryClientSequentialHomOp::QueryClientSequentialHomOp() {}

void QueryClientSequentialHomOp::init(lattica_proto::QueryClientSequentialHomOp proto) {
    int num_client_blocks = proto.client_blocks_size();
    for (int i = 0; i < num_client_blocks; i++) {
        QueryClientBlock client_block = QueryClientBlock();
        client_block.init(proto.client_blocks(i));
        client_blocks.push_back(client_block);
    }
    
    int num_key_types = proto.key_types_size();
    for (int i = 0; i < num_key_types; i++) {
        key_types.push_back(static_cast<lattica_proto::AuxKeyType>(proto.key_types(i)));
    }
}

lattica_proto::QueryClientSequentialHomOp QueryClientSequentialHomOp::to_proto(std::optional<lattica_proto::QueryClientSequentialHomOp*> t_proto) {
    lattica_proto::QueryClientSequentialHomOp* proto = t_proto ? t_proto.value() : new lattica_proto::QueryClientSequentialHomOp();
    
    int num_client_blocks = client_blocks.size();
    for (int i = 0; i < num_client_blocks; i++) {
        lattica_proto::QueryClientBlock* client_block_proto = proto->add_client_blocks();
        client_blocks[i].to_proto(client_block_proto);
    }
    
    int num_key_types = key_types.size();
    for (int i = 0; i < num_key_types; i++) {
        proto->add_key_types(static_cast<lattica_proto::AuxKeyType>(key_types[i]));
    }
    
    return *proto;
}

QueryClientSequentialHomOp::QueryClientSequentialHomOp(std::string& proto_str) : QueryClientSequentialHomOp() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    lattica_proto::QueryClientSequentialHomOp proto;
    proto.ParseFromString(proto_str);
    init(proto);
}

} // namespace homom_ops
