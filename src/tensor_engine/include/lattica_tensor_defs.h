#pragma once

#include "ATen/TensorIndexing.h"
#include "ATen/core/TensorBody.h"

using TTensor = at_lattica_nspace::Tensor;
using TTensorShape = at_lattica_nspace::IntArrayRef;

#define SINGLE_PRECISION int64_t
#define DOUBLE_PRECISION __int128_t
#define T_ENG_INT_TYPE at_lattica_nspace::kLong
#define T_ENG_FLOAT_TYPE at_lattica_nspace::kDouble
#define T_ENG_FLOAT32_TYPE at_lattica_nspace::kFloat
#define T_ENG_COMPLEX_TYPE at_lattica_nspace::kComplexDouble
#define MAX_THREAD std::thread::hardware_concurrency()
