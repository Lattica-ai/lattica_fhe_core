#pragma once

#include <ATen/TensorIndexing.h>
#include <ATen/core/TensorBody.h>
#include <thread>

using TTensor = at::Tensor;
using TTensorShape = at::IntArrayRef;

#define SINGLE_PRECISION int64_t
#define DOUBLE_PRECISION __int128_t
#define T_ENG_INT_TYPE at::kLong
#define T_ENG_FLOAT_TYPE at::kDouble
#define T_ENG_FLOAT32_TYPE at::kFloat
#define T_ENG_COMPLEX_TYPE at::kComplexDouble
#define MAX_THREAD std::thread::hardware_concurrency()
