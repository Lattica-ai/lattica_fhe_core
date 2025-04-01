#include "modsub.h"

SINGLE_PRECISION _modsub(SINGLE_PRECISION a, SINGLE_PRECISION b, SINGLE_PRECISION p) {
    SINGLE_PRECISION res = a - b;
    return res < 0 ? res + p : res;
}

void cpu_apply_modsub_tcc(
    at::Tensor result,
    const at::Tensor a,
    const SINGLE_PRECISION b,
    const SINGLE_PRECISION p) {

        at::TensorIterator iter = at::TensorIteratorConfig()
          .add_output(result)
          .add_input(a)
          .build();

        at::native::cpu_kernel(iter, [b, p] (SINGLE_PRECISION a) -> SINGLE_PRECISION {
            return _modsub(a, b, p);
        });
    }

void cpu_apply_modsub_ttt(
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
            return _modsub(a, b, p);
        });
    }

void cpu_apply_modsub_ttc(
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
            return _modsub(a, b, p);
        });
    }

void cpu_apply_modsub_tct(
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
            return _modsub(a, b, p);
        });
    }
