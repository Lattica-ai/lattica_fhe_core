#pragma once

#include "csprng_poly.h"
#include <optional>

using namespace c10_lattica_nspace;
using namespace at_lattica_nspace::indexing;

namespace t_eng {

    std::tuple<TTensor, int, TTensor> reshape_4d(TTensor a, int axis, TTensor out);
    TTensor mod(TTensor a, TTensor m, bool inplace = true);
    TTensor take_along_axis(TTensor a, TTensor idxs, int axis);
    TTensor empty(std::vector<int64_t> sizes, optional<at_lattica_nspace::ScalarType> dtype = T_ENG_INT_TYPE);
    TTensor eye(int n, optional<at_lattica_nspace::ScalarType> dtype = T_ENG_INT_TYPE);
    TTensor vander(TTensor a, int n, bool increasing);
    TTensor round(TTensor a);
    TTensor pad_single_axis(TTensor a, int pad, int axis);
    TTensor rfft(TTensor a, int n ,int axis);
    TTensor irfft(TTensor a, int n, int axis);
    TTensor ifft(TTensor a, int n, int axis);
    TTensor arange(int64_t start, int64_t end, int64_t step);
    TTensor pow(TTensor a, TTensor b);
    TTensor pow(c10_lattica_nspace::Scalar a, TTensor b);
    TTensor pow(TTensor a, c10_lattica_nspace::Scalar b);
    TTensor flip(TTensor a, std::vector<int64_t> dims);
    TTensor cat(std::vector<TTensor> tensors, int axis);
    TTensor sum(TTensor a, int axis);
    TTensor real(TTensor a);
    void generate_random_integers(TTensor& tensor, int64_t low, int64_t high, at_lattica_nspace::ScalarType dtype);
    void generate_random_normal(TTensor& tensor, float mean, float std);

}