#include "modsum.h"

SINGLE_PRECISION _modsum(SINGLE_PRECISION a, SINGLE_PRECISION b, SINGLE_PRECISION p) {
    SINGLE_PRECISION res = a + b;
    return res < p ? res : res - p;
}

void cpu_apply_modsum_tcc(
    at_lattica_nspace::Tensor result,
    const at_lattica_nspace::Tensor a,
    const SINGLE_PRECISION b,
    const SINGLE_PRECISION p) {

        at_lattica_nspace::TensorIterator iter = at_lattica_nspace::TensorIteratorConfig()
          .add_output(result)
          .add_input(a)
          .build();

        at_lattica_nspace::native::cpu_kernel(iter, [b, p] (SINGLE_PRECISION a) -> SINGLE_PRECISION {
            return _modsum(a, b, p);
        });
    }

void cpu_apply_modsum_ttt(
    at_lattica_nspace::Tensor result,
    const at_lattica_nspace::Tensor a,
    const at_lattica_nspace::Tensor b,
    const at_lattica_nspace::Tensor p) {

        at_lattica_nspace::TensorIterator iter = at_lattica_nspace::TensorIteratorConfig()
          .add_output(result)
          .add_input(a)
          .add_input(b)
          .add_input(p)
          .build();

        at_lattica_nspace::native::cpu_kernel(iter, [] (
            SINGLE_PRECISION a, SINGLE_PRECISION b, SINGLE_PRECISION p) -> SINGLE_PRECISION {
            return _modsum(a, b, p);
        });
    }

void cpu_apply_modsum_ttc(
    at_lattica_nspace::Tensor result,
    const at_lattica_nspace::Tensor a,
    const at_lattica_nspace::Tensor b,
    const SINGLE_PRECISION p) {

        at_lattica_nspace::TensorIterator iter = at_lattica_nspace::TensorIteratorConfig()
          .add_output(result)
          .add_input(a)
          .add_input(b)
          .build();

        at_lattica_nspace::native::cpu_kernel(iter, [p] (SINGLE_PRECISION a, SINGLE_PRECISION b) -> SINGLE_PRECISION {
            return _modsum(a, b, p);
        });
    }

void cpu_apply_modsum_tct(
    at_lattica_nspace::Tensor result,
    const at_lattica_nspace::Tensor a,
    const SINGLE_PRECISION b,
    const at_lattica_nspace::Tensor p) {
          
        at_lattica_nspace::TensorIterator iter = at_lattica_nspace::TensorIteratorConfig()
          .add_output(result)
          .add_input(a)
          .add_input(p)
          .build();

        at_lattica_nspace::native::cpu_kernel(iter, [b] (SINGLE_PRECISION a, SINGLE_PRECISION p) -> SINGLE_PRECISION {
            return _modsum(a, b, p);
        });
    }
