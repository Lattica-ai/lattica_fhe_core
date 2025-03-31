#pragma once

#include "ATen/detail/FunctionTraits.h"
#include "ATen/native/cpu/Reduce.h"

void _axis_modsum(at_lattica_nspace::TensorIteratorBase& iter);

void cpu_apply_axis_modsum(
    at_lattica_nspace::Tensor result,
    const at_lattica_nspace::Tensor a,
    const at_lattica_nspace::Tensor p);