#include "tensor_engine.h"
#include "csprng_poly.h"

using namespace c10_lattica_nspace;
using namespace at_lattica_nspace::indexing;

namespace t_eng {

std::tuple<TTensor, int, TTensor> reshape_4d(TTensor a, int axis, TTensor out) {
    axis = (axis < 0) ? axis : axis - a.dim();

    if (axis < -3) {
        a = a.flatten(axis + 1, -2);
        if (out.defined()) {
            out = out.flatten(axis + 1, -2);
        }
        axis = -3;
    } else if (axis == -2) {
        a = a.unsqueeze(-2);
        if (out.defined()) {
            out = out.unsqueeze(-2);
        }
        axis = -3;
    }

    int axis_shape = (axis < 0) ? axis + a.dim() : axis;
    std::vector<int64_t> new_shape = {-1};
    auto sliced_shape = a.sizes().slice(axis_shape);
    new_shape.insert(new_shape.end(), sliced_shape.begin(), sliced_shape.end());
    a = a.reshape(new_shape);

    if (out.defined()) {
        std::vector<int64_t> new_shape = {-1};
        auto sliced_shape = out.sizes().slice(axis_shape);
        new_shape.insert(new_shape.end(), sliced_shape.begin(), sliced_shape.end());
        out = out.reshape(new_shape);
    }

    return std::make_tuple(a, axis, out);
}

TTensor mod(TTensor a, TTensor m, bool inplace) {
    if (inplace) {
        return a.remainder_(m);
    }
    return a.remainder(m);
}

TTensor take_along_axis(TTensor a, TTensor idxs, int axis) {
    return a.take_along_dim(idxs, axis);
}

TTensor empty(std::vector<int64_t> sizes, optional<at_lattica_nspace::ScalarType> dtype) {
    return at_lattica_nspace::empty(sizes, dtype.value());
}

TTensor eye(int n, optional<at_lattica_nspace::ScalarType> dtype) {
    return at_lattica_nspace::eye(n, dtype.value());
}

TTensor vander(TTensor a, int n, bool increasing) {
    return at_lattica_nspace::vander(a, n, increasing);
}

TTensor round(TTensor a) {
    return a.round();
}

TTensor pad_single_axis(TTensor a, int pad, int axis) {
    std::vector<int64_t> padding(-axis*2 - 1, 0);
    padding.push_back(pad);
    return at_lattica_nspace::constant_pad_nd(a, padding, 0);
}

TTensor rfft(TTensor a, int n ,int axis) {
    a = a.to(T_ENG_FLOAT_TYPE);
    return at_lattica_nspace::fft_rfft(a, n, axis).contiguous();
}

TTensor irfft(TTensor a, int n, int axis) {
    return at_lattica_nspace::fft_irfft(a, n, axis).contiguous();
}

TTensor ifft(TTensor a, int n, int axis) {
    return at_lattica_nspace::fft_ifft(a, n, axis).contiguous();
}

TTensor arange(int64_t start, int64_t end, int64_t step) {
    return at_lattica_nspace::arange(start, end, step);
}

TTensor pow(TTensor a, TTensor b) {
    return at_lattica_nspace::pow(a, b);
}

TTensor pow(c10_lattica_nspace::Scalar a, TTensor b) {
    return at_lattica_nspace::pow(a, b);
}

TTensor pow(TTensor a, c10_lattica_nspace::Scalar b) {
    return at_lattica_nspace::pow(a, b);
}

TTensor flip(TTensor a, std::vector<int64_t> dims) {
    return at_lattica_nspace::flip(a, dims);
}

TTensor cat(std::vector<TTensor> tensors, int axis) {
    return at_lattica_nspace::cat(tensors, axis);
}

TTensor sum(TTensor a, int axis) {
    return at_lattica_nspace::sum(a, axis);
}

TTensor real(TTensor a) {
    return at_lattica_nspace::real(a);
}

void generate_random_integers(TTensor& tensor, int64_t low, int64_t high, at_lattica_nspace::ScalarType dtype) {
    if (high <= static_cast<int64_t>(std::numeric_limits<int32_t>::max())) {
        switch (dtype) {
            case T_ENG_INT_TYPE:
                generate_random_int32_tensor(tensor, low, high);
                break;
            default:
                throw std::invalid_argument("Unsupported dtype for random integers. Use T_ENG_INT_TYPE.");
        }
    } else {
        generate_random_int64_tensor(tensor, high);
    }
}

void generate_random_normal(TTensor& tensor, float mean, float std) {
    generate_random_normal_tensor(tensor, mean, std);
}

}