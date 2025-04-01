#include "modlt.h"

SINGLE_PRECISION _modlt(SINGLE_PRECISION a, SINGLE_PRECISION p) {
    SINGLE_PRECISION res = a < 0 ? a + p : a;
    return res;
}

void cpu_apply_modlt_tc(
    at::Tensor result,
    const at::Tensor a,
    const SINGLE_PRECISION p) {

        at::TensorIterator iter = at::TensorIteratorConfig()
          .add_output(result)
          .add_input(a)
          .build();

        at::native::cpu_kernel(iter, [p] (SINGLE_PRECISION a) -> SINGLE_PRECISION {
            return _modlt(a, p);
        });
    }


void cpu_apply_modlt_tt(
    at::Tensor result,
    const at::Tensor a,
    const at::Tensor p) {

        at::TensorIterator iter = at::TensorIteratorConfig()
          .add_output(result)
          .add_input(a)
          .add_input(p)
          .build();

        at::native::cpu_kernel(iter, [] (
            SINGLE_PRECISION a, SINGLE_PRECISION p) -> SINGLE_PRECISION {
            return _modlt(a, p);
        });
    }

