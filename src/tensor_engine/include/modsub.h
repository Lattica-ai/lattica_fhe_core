#pragma once

#include "ATen/native/cpu/Loops.h"
#include "ATen/native/DispatchStub.h"
#include "ATen/native/TensorIterator.h"

#include "lattica_tensor_defs.h"

SINGLE_PRECISION _modsub(SINGLE_PRECISION a, SINGLE_PRECISION b, SINGLE_PRECISION p);

void cpu_apply_modsub_tcc(
    at_lattica_nspace::Tensor result,
    const at_lattica_nspace::Tensor a,
    const SINGLE_PRECISION b,
    const SINGLE_PRECISION p);

void cpu_apply_modsub_ttt(
    at_lattica_nspace::Tensor result,
    const at_lattica_nspace::Tensor a,
    const at_lattica_nspace::Tensor b,
    const at_lattica_nspace::Tensor p);

void cpu_apply_modsub_ttc(
    at_lattica_nspace::Tensor result,
    const at_lattica_nspace::Tensor a,
    const at_lattica_nspace::Tensor b,
    const SINGLE_PRECISION p);

void cpu_apply_modsub_tct(
    at_lattica_nspace::Tensor result,
    const at_lattica_nspace::Tensor a,
    const SINGLE_PRECISION b,
    const at_lattica_nspace::Tensor p);
