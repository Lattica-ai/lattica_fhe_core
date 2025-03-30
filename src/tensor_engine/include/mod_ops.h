#pragma once

#include "modmul.h"
#include "modsum.h"
#include "modsub.h"
#include "modlt.h"
#include "axis_modsum.h"

namespace t_eng {

    std::vector<int64_t> _broadcast_shapes(std::vector<TTensorShape> shapes);
    TTensor axis_modsum(TTensor a, int axis, TTensor q_list);
    TTensor _get_result_container(TTensor& a, bool inplace, std::vector<int64_t>& result_shape, TTensor* out = nullptr);
    TTensor modmul(TTensor a, TTensor b, TTensor m, bool inplace = true, TTensor* out = nullptr);
    TTensor modmul(TTensor a, TTensor b, SINGLE_PRECISION m, bool inplace = true, TTensor* out = nullptr);
    TTensor modmul(TTensor a, SINGLE_PRECISION b, TTensor m, bool inplace = true, TTensor* out = nullptr);
    TTensor modmul(TTensor a, SINGLE_PRECISION b, SINGLE_PRECISION m, bool inplace = true, TTensor* out = nullptr);
    TTensor modsum(TTensor a, TTensor b, TTensor m, bool inplace = true, TTensor* out = nullptr);
    TTensor modsum(TTensor a, TTensor b, SINGLE_PRECISION m, bool inplace = true, TTensor* out = nullptr);
    TTensor modsum(TTensor a, SINGLE_PRECISION b, TTensor m, bool inplace = true, TTensor* out = nullptr);
    TTensor modsum(TTensor a, SINGLE_PRECISION b, SINGLE_PRECISION m, bool inplace = true, TTensor* out = nullptr);
    TTensor modsub(TTensor a, TTensor b, TTensor m, bool inplace = true, TTensor* out = nullptr);
    TTensor modsub(TTensor a, TTensor b, SINGLE_PRECISION m, bool inplace = true, TTensor* out = nullptr);
    TTensor modsub(TTensor a, SINGLE_PRECISION b, TTensor m, bool inplace = true, TTensor* out = nullptr);
    TTensor modsub(TTensor a, SINGLE_PRECISION b, SINGLE_PRECISION m, bool inplace = true, TTensor* out = nullptr);
    TTensor modlt(TTensor a, SINGLE_PRECISION m, bool inplace = true, TTensor* out = nullptr);
    TTensor modlt(TTensor a, TTensor m, bool inplace = true, TTensor* out = nullptr);

} // namespace t_eng