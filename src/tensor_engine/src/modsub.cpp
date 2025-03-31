#include "modsub.h"

SINGLE_PRECISION _modsub(SINGLE_PRECISION a, SINGLE_PRECISION b, SINGLE_PRECISION p) {
    SINGLE_PRECISION res = a - b;
    return res < 0 ? res + p : res;
}

void cpu_apply_modsub_tcc(
    at_lattica_nspace::Tensor result,
    const at_lattica_nspace::Tensor a,
    const SINGLE_PRECISION b,
    const SINGLE_PRECISION p) {

        at_lattica_nspace::TensorIterator iter = at_lattica_nspace::TensorIteratorConfig()
          .add_output(result)
          .add_input(a)
          .build();

        at_lattica_nspace::native::cpu_kernel(iter, [b, p] (SINGLE_PRECISION a) -> SINGLE_PRECISION {
            return _modsub(a, b, p);
        });
    }

void cpu_apply_modsub_ttt(
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
            return _modsub(a, b, p);
        });
    }

void cpu_apply_modsub_ttc(
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
            return _modsub(a, b, p);
        });
    }

void cpu_apply_modsub_tct(
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
            return _modsub(a, b, p);
        });
    }
