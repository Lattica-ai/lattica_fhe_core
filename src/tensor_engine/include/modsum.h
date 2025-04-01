#pragma once

#include <ATen/native/cpu/Loops.h>
#include <ATen/native/DispatchStub.h>
#include <ATen/native/TensorIterator.h>

#include "lattica_tensor_defs.h"

SINGLE_PRECISION _modsum(SINGLE_PRECISION a, SINGLE_PRECISION b, SINGLE_PRECISION p);

void cpu_apply_modsum_tcc(
    at::Tensor result,
    const at::Tensor a,
    const SINGLE_PRECISION b,
    const SINGLE_PRECISION p);

void cpu_apply_modsum_ttt(
    at::Tensor result,
    const at::Tensor a,
    const at::Tensor b,
    const at::Tensor p);

void cpu_apply_modsum_ttc(
    at::Tensor result,
    const at::Tensor a,
    const at::Tensor b,
    const SINGLE_PRECISION p);

void cpu_apply_modsum_tct(
    at::Tensor result,
    const at::Tensor a,
    const SINGLE_PRECISION b,
    const at::Tensor p);
