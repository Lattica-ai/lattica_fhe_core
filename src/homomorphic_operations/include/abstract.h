#pragma once

#include "hom_op.pb.h"

namespace homom_ops {

class QueryClientBlock {
public:
    QueryClientBlock() = default;
    QueryClientBlock(const std::string& proto_str);
    void init(lattica_proto::QueryClientBlock proto);
    lattica_proto::QueryClientBlock to_proto(std::optional<lattica_proto::QueryClientBlock*> t_proto = std::nullopt);

    size_t get_op_types_size() const;
    lattica_proto::HomOpType& get_op_type(size_t index);
    lattica_proto::ApplyClearParams& get_apply_clear_params(size_t index);

private:
    int block_index;
    bool is_last;
    std::vector<lattica_proto::HomOpType> op_types;
    std::vector<lattica_proto::ApplyClearParams> apply_clear_params_list;
};

class QueryClientSequentialHomOp {
public:
    QueryClientSequentialHomOp() = default;
    QueryClientSequentialHomOp(const std::string& proto_str);
    void init(lattica_proto::QueryClientSequentialHomOp proto);
    lattica_proto::QueryClientSequentialHomOp to_proto(std::optional<lattica_proto::QueryClientSequentialHomOp*> t_proto = std::nullopt);

    std::vector<lattica_proto::AuxKeyType>& get_key_types();

private:
    std::vector<QueryClientBlock> client_blocks;
    std::vector<lattica_proto::AuxKeyType> key_types;
};

} // namespace homom_ops