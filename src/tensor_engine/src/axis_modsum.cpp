#include "axis_modsum.h"
#include "lattica_tensor_defs.h"

void _axis_modsum(at_lattica_nspace::TensorIteratorBase& iter) {

  iter.foreach_reduced_elt([](at_lattica_nspace::TensorIteratorBase &sub_iter) {

    auto reduction_body = [&sub_iter](
        SINGLE_PRECISION acc, SINGLE_PRECISION begin, SINGLE_PRECISION end) -> SINGLE_PRECISION {

          sub_iter.serial_for_each([&acc](char** data, const int64_t* strides, int64_t size) {
              char *in_a = data[1];
              char *in_p = data[2];
              int64_t stride_a = strides[1];
              int64_t stride_p = strides[2];
              for (const auto i : c10_lattica_nspace::irange(size)) {
                 auto a = c10_lattica_nspace::load<SINGLE_PRECISION>(in_a);
                 auto p = c10_lattica_nspace::load<SINGLE_PRECISION>(in_p);
                 acc += a;
                 acc = acc < p ? acc : acc - p;
                 in_a += stride_a;
                 in_p += stride_p;
              }
          }, {begin, end}); // end of sub_iter.serial_for_each

      return acc;
    };  // end of reduction_body

    SINGLE_PRECISION total_acc = (SINGLE_PRECISION)0;
    total_acc = reduction_body(total_acc, 0, sub_iter.numel());

    SINGLE_PRECISION lat_reduce(SINGLE_PRECISION /**/, SINGLE_PRECISION /**/, SINGLE_PRECISION /**/);
    using r_traits = binary_function_traits<decltype(&lat_reduce)>;

    at_lattica_nspace::native::set_results<r_traits>(total_acc, sub_iter, 1);
  }, true);
}

// ======================================================

void cpu_apply_axis_modsum(
    at_lattica_nspace::Tensor result,
    const at_lattica_nspace::Tensor a,
    const at_lattica_nspace::Tensor p) {

        at_lattica_nspace::TensorIterator iter = at_lattica_nspace::TensorIteratorConfig()
          .add_owned_output(result)
          .add_owned_const_input(a)
          .add_owned_const_input(p)
          .resize_outputs(false)
          .is_reduction(true)
          .build();

        _axis_modsum(iter);
    }
