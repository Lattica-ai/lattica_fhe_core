#pragma once

#include "ATen/native/cpu/Loops.h"
#include "ATen/native/DispatchStub.h"
#include "ATen/native/TensorIterator.h"

#include "lattica_tensor_defs.h"

SINGLE_PRECISION _modlt(SINGLE_PRECISION a, SINGLE_PRECISION p);

void cpu_apply_modlt_tc(
    at_lattica_nspace::Tensor result,
    const at_lattica_nspace::Tensor a,
    const SINGLE_PRECISION p);

void cpu_apply_modlt_tt(
    at_lattica_nspace::Tensor result,
    const at_lattica_nspace::Tensor a,
    const at_lattica_nspace::Tensor p);

