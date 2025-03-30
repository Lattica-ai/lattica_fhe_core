#include "modlt.h"

SINGLE_PRECISION _modlt(SINGLE_PRECISION a, SINGLE_PRECISION p) {
    SINGLE_PRECISION res = a < 0 ? a + p : a;
    return res;
}

void cpu_apply_modlt_tc(
    at_lattica_nspace::Tensor result,
    const at_lattica_nspace::Tensor a,
    const SINGLE_PRECISION p) {

        at_lattica_nspace::TensorIterator iter = at_lattica_nspace::TensorIteratorConfig()
          .add_output(result)
          .add_input(a)
          .build();

        at_lattica_nspace::native::cpu_kernel(iter, [p] (SINGLE_PRECISION a) -> SINGLE_PRECISION {
            return _modlt(a, p);
        });
    }


void cpu_apply_modlt_tt(
    at_lattica_nspace::Tensor result,
    const at_lattica_nspace::Tensor a,
    const at_lattica_nspace::Tensor p) {

        at_lattica_nspace::TensorIterator iter = at_lattica_nspace::TensorIteratorConfig()
          .add_output(result)
          .add_input(a)
          .add_input(p)
          .build();

        at_lattica_nspace::native::cpu_kernel(iter, [] (
            SINGLE_PRECISION a, SINGLE_PRECISION p) -> SINGLE_PRECISION {
            return _modlt(a, p);
        });
    }

