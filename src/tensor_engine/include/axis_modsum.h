#pragma once

#include <ATen/detail/FunctionTraits.h>
#include <ATen/native/cpu/Reduce.h>

void _axis_modsum(at::TensorIteratorBase& iter);

void cpu_apply_axis_modsum(
    at::Tensor result,
    const at::Tensor a,
    const at::Tensor p);