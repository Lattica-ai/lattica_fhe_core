#include "modsum.h"

SINGLE_PRECISION _modsum(SINGLE_PRECISION a, SINGLE_PRECISION b, SINGLE_PRECISION p) {
    SINGLE_PRECISION res = a + b;
    return res < p ? res : res - p;
}

void cpu_apply_modsum_tcc(
    at::Tensor result,
    const at::Tensor a,
    const SINGLE_PRECISION b,
    const SINGLE_PRECISION p) {

        at::TensorIterator iter = at::TensorIteratorConfig()
          .add_output(result)
          .add_input(a)
          .build();

        at::native::cpu_kernel(iter, [b, p] (SINGLE_PRECISION a) -> SINGLE_PRECISION {
            return _modsum(a, b, p);
        });
    }

void cpu_apply_modsum_ttt(
    at::Tensor result,
    const at::Tensor a,
    const at::Tensor b,
    const at::Tensor p) {

        at::TensorIterator iter = at::TensorIteratorConfig()
          .add_output(result)
          .add_input(a)
          .add_input(b)
          .add_input(p)
          .build();

        at::native::cpu_kernel(iter, [] (
            SINGLE_PRECISION a, SINGLE_PRECISION b, SINGLE_PRECISION p) -> SINGLE_PRECISION {
            return _modsum(a, b, p);
        });
    }

void cpu_apply_modsum_ttc(
    at::Tensor result,
    const at::Tensor a,
    const at::Tensor b,
    const SINGLE_PRECISION p) {

        at::TensorIterator iter = at::TensorIteratorConfig()
          .add_output(result)
          .add_input(a)
          .add_input(b)
          .build();

        at::native::cpu_kernel(iter, [p] (SINGLE_PRECISION a, SINGLE_PRECISION b) -> SINGLE_PRECISION {
            return _modsum(a, b, p);
        });
    }

void cpu_apply_modsum_tct(
    at::Tensor result,
    const at::Tensor a,
    const SINGLE_PRECISION b,
    const at::Tensor p) {

        at::TensorIterator iter = at::TensorIteratorConfig()
          .add_output(result)
          .add_input(a)
          .add_input(p)
          .build();

        at::native::cpu_kernel(iter, [b] (SINGLE_PRECISION a, SINGLE_PRECISION p) -> SINGLE_PRECISION {
            return _modsum(a, b, p);
        });
    }
