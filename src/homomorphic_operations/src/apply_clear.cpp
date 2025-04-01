#include <ATen/ATen.h>
#include "apply_clear.h"
#include "modsum.h"
#include "serialization_utils.h"
#include "modmul.h"
#include "plaintext.h"
#include "ckks.h"

namespace homom_ops {

TTensor const_add_clear(
    context::Context& context,
    TTensor& pt,
    lattica_proto::ConstAddApplyClearParams apply_clear_params
) {
    TTensor data = serialization_utils::deser_tensor(apply_clear_params.data());
    if (context.is_ckks) {
        auto res = at::add(pt, data);
        return encryption_schemes::_CKKS().to_default_pt_tensor(res);
    } else {
        auto p = context.params.p();
        pt = plaintext::encode_pt(context, pt);
        data = plaintext::encode_pt(context, data);
        auto res = t_eng::modsum(pt, data, p);
        return plaintext::decode_pt(context, res);
    }
}

TTensor _const_mul_clear(
    context::Context& context,
    TTensor& pt,
    TTensor& data
) {
    if (context.is_ckks) {
        auto res = at::mul(pt, data);
        return encryption_schemes::_CKKS().to_default_pt_tensor(res);
    } else {
        auto p = context.params.p();
        pt = plaintext::encode_pt(context, pt);
        data = plaintext::encode_pt(context, data);
        auto res = t_eng::modmul(pt, data, p);
        return plaintext::decode_pt(context, res);
    }
}

TTensor const_mul_clear(
    context::Context& context,
    TTensor& pt,
    lattica_proto::ConstMulApplyClearParams apply_clear_params
) {
    TTensor data = serialization_utils::deser_tensor(apply_clear_params.data());
    return _const_mul_clear(context, pt, data);
}

TTensor square_clear(
    context::Context& context,
    TTensor& pt
) {
    return _const_mul_clear(context, pt, pt);
}

TTensor mat_mul_clear(
    context::Context& context,
    TTensor& pt,
    lattica_proto::ConstMatMulApplyClearParams apply_clear_params
) {
    TTensor data = serialization_utils::deser_tensor(apply_clear_params.data());
    int pt_mul_axis = apply_clear_params.pt_mul_axis();

    int cols = data.size(0);
    if (pt_mul_axis < 0) {
        pt_mul_axis += pt.dim();
    }

    auto old_pt_shape = pt.sizes().vec();
    if (pt_mul_axis == pt.dim() - 1) {
        pt = pt.unsqueeze(-1);
    } else {
        pt = pt.flatten(pt_mul_axis + 1, -1);
    }

    if (pt_mul_axis == 0) {
        pt = pt.unsqueeze(0);
    } else {
        pt = pt.flatten(0, pt_mul_axis - 1);
    }

    data = data.unsqueeze(-1).unsqueeze(-3);

    TTensor res;
    if (context.is_ckks) {
        res = pt * data;
        res = encryption_schemes::_CKKS().to_default_pt_tensor(res);
        res = res.sum(-2);
    } else {
        auto p = context.params.p();
        pt = plaintext::encode_pt(context, pt);
        data = plaintext::encode_pt(context, data);
        res = t_eng::modmul(pt, data, p);
        res = t_eng::axis_modsum(res.unsqueeze(-1), -3, p).squeeze(-1);
        res = plaintext::decode_pt(context, res);
    }

    auto res_shape = std::vector<int64_t>({cols});
    res_shape.insert(res_shape.end(), old_pt_shape.begin(), old_pt_shape.begin() + pt_mul_axis);
    res_shape.insert(res_shape.end(), old_pt_shape.begin() + pt_mul_axis + 1, old_pt_shape.end());

    return res.reshape(res_shape);
}

TTensor unfold_clear(
    context::Context& context,
    TTensor& pt,
    lattica_proto::UnfoldApplyClearParams apply_clear_params
) {
    int kernel_size = apply_clear_params.kernel_size();
    int padding = apply_clear_params.padding();
    int stride = apply_clear_params.stride();

    // TODO: assume symmetric kernel for now
    auto unfolded = at::im2col(
        pt,
        {kernel_size, kernel_size},
        {1, 1}, // dilation
        {padding, padding},
        {stride, stride}
    );

    return unfolded;
}

TTensor reshape_clear(
    context::Context& context,
    TTensor& pt,
    lattica_proto::ReshapeApplyClearParams apply_clear_params
) {
    std::vector<int64_t> dims_vec;
    int dims_size = apply_clear_params.dims_size();

    for (int i = 0; i < dims_size; i++) {
        dims_vec.push_back(apply_clear_params.dims(i));
    }

    return pt.reshape(dims_vec);
}

TTensor softmax_clear(
    context::Context& context,
    TTensor& pt,
    lattica_proto::SoftmaxApplyClearParams apply_clear_params
) {
    int dim = apply_clear_params.dim();
    return pt.softmax(dim);
}

TTensor relu_clear(
    context::Context& context,
    TTensor& pt
) {
    return pt.relu();
}

TTensor clamp_clear(
    context::Context& context,
    TTensor& pt,
    lattica_proto::ClampApplyClearParams apply_clear_params
) {
    return at::clamp(pt, apply_clear_params.min_val(), apply_clear_params.max_val());
}

TTensor apply_clear(
    lattica_proto::HomOpType op_type,
    context::Context& context,
    TTensor& pt,
    lattica_proto::ApplyClearParams apply_clear_params
) {
    switch (op_type) {
        case lattica_proto::HomOpType::ConstAdd:
            return const_add_clear(context, pt, apply_clear_params.const_add());
        case lattica_proto::HomOpType::ConstMul:
            return const_mul_clear(context, pt, apply_clear_params.const_mul());
        case lattica_proto::HomOpType::Square:
            return square_clear(context, pt);
        case lattica_proto::HomOpType::MatMulBaseKey:
        case lattica_proto::HomOpType::MatMulFullKey:
            return mat_mul_clear(context, pt, apply_clear_params.const_mat_mul());
        case lattica_proto::HomOpType::Unfold:
            return unfold_clear(context, pt, apply_clear_params.unfold());
        case lattica_proto::HomOpType::Reshape:
            return reshape_clear(context, pt, apply_clear_params.reshape());
        case lattica_proto::HomOpType::Softmax:
            return softmax_clear(context, pt, apply_clear_params.softmax());
        case lattica_proto::HomOpType::ReLU:
            return relu_clear(context, pt);
        case lattica_proto::HomOpType::Clamp:
            return clamp_clear(context, pt, apply_clear_params.clamp());
        default:
            throw std::invalid_argument("ApplyClear not implemented for HomOpType");
    }
}

} // namespace homom_ops
