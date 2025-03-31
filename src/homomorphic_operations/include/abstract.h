#pragma once

#include "hom_op.pb.h"

namespace homom_ops {

class QueryClientBlock {
public:
    int block_index;
    bool is_last;
    std::vector<lattica_proto::HomOpType> op_types;
    std::vector<lattica_proto::ApplyClearParams> apply_clear_params_list;

    QueryClientBlock();
    void init(lattica_proto::QueryClientBlock proto);
    lattica_proto::QueryClientBlock to_proto(std::optional<lattica_proto::QueryClientBlock*> t_proto = std::nullopt);
    QueryClientBlock(std::string& proto_str);
};

class QueryClientSequentialHomOp {
public:
    std::vector<QueryClientBlock> client_blocks;
    std::vector<lattica_proto::AuxKeyType> key_types;

    QueryClientSequentialHomOp();
    void init(lattica_proto::QueryClientSequentialHomOp proto);
    lattica_proto::QueryClientSequentialHomOp to_proto(std::optional<lattica_proto::QueryClientSequentialHomOp*> t_proto = std::nullopt);
    QueryClientSequentialHomOp(std::string& proto_str);
};

} // namespace homom_ops