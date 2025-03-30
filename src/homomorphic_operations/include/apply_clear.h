#pragma once

#include "hom_op.pb.h"
#include "tensor_engine.h"
#include "context.h"

namespace homom_ops {

TTensor const_add_clear(
    context::Context& context,
    TTensor& pt,
    lattica_proto::ConstAddApplyClearParams apply_clear_params
);

TTensor _const_mul_clear(
    context::Context& context,
    TTensor& pt,
    TTensor& data
);

TTensor const_mul_clear(
    context::Context& context,
    TTensor& pt,
    lattica_proto::ConstMulApplyClearParams apply_clear_params
);

TTensor square_clear(
    context::Context& context,
    TTensor& pt
);

TTensor mat_mul_clear(
    context::Context& context,
    TTensor& pt,
    lattica_proto::ConstMatMulApplyClearParams apply_clear_params
);

TTensor unfold_clear(
    context::Context& context,
    TTensor& pt,
    lattica_proto::UnfoldApplyClearParams apply_clear_params
);

TTensor reshape_clear(
    context::Context& context,
    TTensor& pt,
    lattica_proto::ReshapeApplyClearParams apply_clear_params
);

TTensor softmax_clear(
    context::Context& context,
    TTensor& pt,
    lattica_proto::SoftmaxApplyClearParams apply_clear_params
);

TTensor relu_clear(
    context::Context& context,
    TTensor& pt
);

TTensor clamp_clear(
    context::Context& context,
    TTensor& pt,
    lattica_proto::ClampApplyClearParams apply_clear_params
);

TTensor apply_clear(
    lattica_proto::HomOpType op_type,
    context::Context& context,
    TTensor& pt,
    lattica_proto::ApplyClearParams apply_clear_params
);

} // namespace homom_ops