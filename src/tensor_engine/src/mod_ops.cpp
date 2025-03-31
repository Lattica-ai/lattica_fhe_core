#include "mod_ops.h"
#include "tensor_engine.h"

namespace t_eng {

    std::vector<int64_t> _broadcast_shapes(std::vector<TTensorShape> shapes) {
        // Assumes that the shapes are broadcastable.
        int max_dim = 0;
        for (auto& shape : shapes) {
            max_dim = std::max(max_dim, (int)shape.size());
        }
        std::vector<int64_t> result_shape(max_dim, 1);
        for (int i = 0; i < max_dim; i++) {
            for (auto& shape : shapes) {
                int shape_missing_dims = max_dim - shape.size();
                if (i >= shape_missing_dims) {
                    result_shape[i] = std::max(result_shape[i], shape[i - shape_missing_dims]);
                }
            }
        }
        return result_shape;
    }

    TTensor axis_modsum(
            TTensor a,
            int axis,
            TTensor q_list) {
        if (a.size(axis) <= 1)
            return a;
        std::vector<int64_t> result_shape = a.sizes().vec();
        if (axis < 0)
            axis += result_shape.size();
        result_shape[axis] = 1;
        TTensor out = t_eng::empty(result_shape);
        cpu_apply_axis_modsum(out, a, q_list);
        out = out.squeeze(axis);
        return out;
    }

    TTensor _get_result_container(TTensor& a, bool inplace, std::vector<int64_t>& result_shape, TTensor* out) {
        if (out != nullptr) {
            return *out;
        }
        if (inplace && (result_shape == a.sizes().vec())) {
            return a;
        }
        return t_eng::empty(result_shape);
    }

    TTensor modmul(TTensor a, TTensor b, TTensor m, bool inplace, TTensor* out) {
        std::vector<int64_t> result_shape = _broadcast_shapes({a.sizes(), b.sizes(), m.sizes()});
        TTensor result = _get_result_container(a, inplace, result_shape, out);
        cpu_apply_modmul_ttt(result, a, b, m);
        return result;
    }

    TTensor modmul(TTensor a, TTensor b, SINGLE_PRECISION m, bool inplace, TTensor* out) {
        std::vector<int64_t> result_shape = _broadcast_shapes({a.sizes(), b.sizes()});
        TTensor result = _get_result_container(a, inplace, result_shape, out);
        cpu_apply_modmul_ttc(result, a, b, m);
        return result;
    }

    TTensor modmul(TTensor a, SINGLE_PRECISION b, TTensor m, bool inplace, TTensor* out) {
        std::vector<int64_t> result_shape = _broadcast_shapes({a.sizes(), m.sizes()});
        TTensor result = _get_result_container(a, inplace, result_shape, out);
        cpu_apply_modmul_tct(result, a, b, m);
        return result;
    }

    TTensor modmul(TTensor a, SINGLE_PRECISION b, SINGLE_PRECISION m, bool inplace, TTensor* out) {
        std::vector<int64_t> result_shape = _broadcast_shapes({a.sizes()});
        TTensor result = _get_result_container(a, inplace, result_shape, out);
        cpu_apply_modmul_tcc(result, a, b, m);
        return result;
    }

    TTensor modsum(TTensor a, TTensor b, TTensor m, bool inplace, TTensor* out) {
        std::vector<int64_t> result_shape = _broadcast_shapes({a.sizes(), b.sizes(), m.sizes()});
        TTensor result = _get_result_container(a, inplace, result_shape, out);
        cpu_apply_modsum_ttt(result, a, b, m);
        return result;
    }

    TTensor modsum(TTensor a, TTensor b, SINGLE_PRECISION m, bool inplace, TTensor* out) {
        std::vector<int64_t> result_shape = _broadcast_shapes({a.sizes(), b.sizes()});
        TTensor result = _get_result_container(a, inplace, result_shape, out);
        cpu_apply_modsum_ttc(result, a, b, m);
        return result;
    }

    TTensor modsum(TTensor a, SINGLE_PRECISION b, TTensor m, bool inplace, TTensor* out) {
        std::vector<int64_t> result_shape = _broadcast_shapes({a.sizes(), m.sizes()});
        TTensor result = _get_result_container(a, inplace, result_shape, out);
        cpu_apply_modsum_tct(result, a, b, m);
        return result;
    }

    TTensor modsum(TTensor a, SINGLE_PRECISION b, SINGLE_PRECISION m, bool inplace, TTensor* out) {
        std::vector<int64_t> result_shape = _broadcast_shapes({a.sizes()});
        TTensor result = _get_result_container(a, inplace, result_shape, out);
        cpu_apply_modsum_tcc(result, a, b, m);
        return result;
    }

    TTensor modsub(TTensor a, TTensor b, TTensor m, bool inplace, TTensor* out) {
        std::vector<int64_t> result_shape = _broadcast_shapes({a.sizes(), b.sizes(), m.sizes()});
        TTensor result = _get_result_container(a, inplace, result_shape, out);
        cpu_apply_modsub_ttt(result, a, b, m);
        return result;
    }

    TTensor modsub(TTensor a, TTensor b, SINGLE_PRECISION m, bool inplace, TTensor* out) {
        std::vector<int64_t> result_shape = _broadcast_shapes({a.sizes(), b.sizes()});
        TTensor result = _get_result_container(a, inplace, result_shape, out);
        cpu_apply_modsub_ttc(result, a, b, m);
        return result;
    }

    TTensor modsub(TTensor a, SINGLE_PRECISION b, TTensor m, bool inplace, TTensor* out) {
        std::vector<int64_t> result_shape = _broadcast_shapes({a.sizes(), m.sizes()});
        TTensor result = _get_result_container(a, inplace, result_shape, out);
        cpu_apply_modsub_tct(result, a, b, m);
        return result;
    }

    TTensor modsub(TTensor a, SINGLE_PRECISION b, SINGLE_PRECISION m, bool inplace, TTensor* out) {
        std::vector<int64_t> result_shape = _broadcast_shapes({a.sizes()});
        TTensor result = _get_result_container(a, inplace, result_shape, out);
        cpu_apply_modsub_tcc(result, a, b, m);
        return result;
    }

    TTensor modlt(TTensor a, SINGLE_PRECISION m, bool inplace, TTensor* out) {
        std::vector<int64_t> result_shape = _broadcast_shapes({a.sizes()});
        TTensor result = _get_result_container(a, inplace, result_shape, out);
        cpu_apply_modlt_tc(result, a, m);
        return result;
    }

    TTensor modlt(TTensor a, TTensor m, bool inplace, TTensor* out) {
        std::vector<int64_t> result_shape = _broadcast_shapes({a.sizes(), m.sizes()});
        TTensor result = _get_result_container(a, inplace, result_shape, out);
        cpu_apply_modlt_tt(result, a, m);
        return result;
    }

} // namespace t_eng