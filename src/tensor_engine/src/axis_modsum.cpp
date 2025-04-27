#include <iostream>

#include <ATen/Functions.h>
#include <ATen/Formatting.h>
#include <ATen/AccumulateType.h>
#include <ATen/Context.h>
#include <ATen/Dispatch.h>
#include <c10/core/Scalar.h>
#include <ATen/native/TensorIterator.h>
#include <ATen/native/cpu/Reduce.h>
#include <ATen/native/cpu/ReduceUtils.h>
#include <ATen/native/ReduceAllOps.h>
#include <ATen/native/ReduceOps.h>
#include <ATen/native/SharedReduceOps.h>
#include <ATen/WrapDimUtilsMulti.h>
#include <ATen/TensorIterator.h>
#include <ATen/Parallel.h>
#include <ATen/TensorIteratorInternal.h>

#include "axis_modsum.h"
#include "lattica_tensor_defs.h"

namespace torch {
  using namespace at; // NOLINT
  using c10::nullopt;
  using c10::optional;
  using Dtype = at::ScalarType;
} // namespace torch

// ============== overriden Torch functions =================
namespace at {

  DimCounter::DimCounter(IntArrayRef shape, Range range):
        shape(shape),
        range(range),
        values(shape.size()),
        offset(range.begin) {
            std::fill(values.begin(), values.end(), 0);
            if (range.begin == 0) {
              return;
        }

    int64_t linear_offset = range.begin;
    auto ndim = values.size();
    for (const auto dim : c10::irange(ndim)) {
      int64_t size = shape[dim];
      if (size > 0) {
        values[dim] = linear_offset % size;
        linear_offset /= size;
      }
    }
    TORCH_INTERNAL_ASSERT(linear_offset == 0);
  }

  bool DimCounter::is_done() const {
    return offset >= range.end;
  }

  void DimCounter::increment(const std::array<int64_t, 2>& step) {
    offset += step[0] * step[1];
    auto ndim = values.size();
    int64_t overflow = step[0];
    size_t i = 0;
    if (step[1] != 1) {
      TORCH_INTERNAL_ASSERT(step[0] == shape[0] && values[0] == 0);
      i = 1;
      overflow = step[1];
    }
    for (; i < ndim && overflow > 0; i++) {
      auto size = shape[i];
      auto prev = values[i];
      auto value = prev + overflow;
      if (value >= size) {
        overflow = 1;
        value -= size;
        TORCH_INTERNAL_ASSERT(value < size);
      } else {
        overflow = 0;
      }
      values[i] = static_cast<int64_t>(value);
    }
    TORCH_INTERNAL_ASSERT(overflow == 0 || overflow == 1);
  }

  std::array<int64_t, 2> DimCounter::max_2d_step() const {
    int64_t step0 = std::min(shape[0] - values[0], range.end - offset);
    int64_t step1 = 1;
    if (step0 == shape[0] && !shape.empty()) {
      step1 = std::min(shape[1] - values[1], (range.end - offset) / shape[0]);
    }
    return {step0, step1};
  }


  /// Chooses a dimension over which to parallelize. Prefers the outer-most
  /// dimension thats larger than the number of available threads.
  static int find_split_dim(TensorIteratorBase& iter) {
    int num_threads = at::get_num_threads();
    auto shape = iter.shape();

    // start with the outer-most dimension
    int best_dim = iter.ndim() - 1;
    for (int dim = best_dim; dim >= 0 && !iter.is_dim_reduced(dim); dim--) {
      if (shape[dim] >= num_threads) {
        return dim;
      } else if (shape[dim] > shape[best_dim]) {
        best_dim = dim;
      }
    }

    AT_ASSERT(!iter.is_dim_reduced(best_dim));
    return best_dim;
  }

  void TensorIteratorBase::foreach_reduced_elt(loop_subiter_t loop, bool parallelize) {

    auto shape = this->shape();
    if (output(0).numel() == 0) {
      return;
    }
    if (output(0).numel() == 1) {
      loop(*this);
    }
    else if (numel() < at::internal::GRAIN_SIZE || at::get_num_threads() == 1 ||
    at::in_parallel_region() || !parallelize) {
//        std::cout << "foreach_reduced_elt running sequential, thrds: " << at::get_num_threads() << " numel: " << numel() << std::endl;
      auto reduce_dims = num_reduce_dims();

      auto non_reduced_shape = shape.slice(reduce_dims, shape.size() - reduce_dims);

      int64_t non_reduced_numel = 1;
      for (const auto i : non_reduced_shape) {
        non_reduced_numel *= i;
      }
      DimCounter dims {non_reduced_shape, {0, non_reduced_numel}};
      while (!dims.is_done()) {
        TensorIterator reduced = *this;
        reduced.select_all_keeping_dim(reduce_dims, dims.values);
        loop(reduced);
        dims.increment({1, 1});
      }
    }
    else {
//        std::cout << "foreach_reduced_elt running parallel, thrds: " << at::get_num_threads() << " numel: " << numel() << std::endl;
      int dim = find_split_dim(*this);
      int64_t cols = shape[dim];
//        std::cout << "split dim: " << dim << " cols: " << cols << std::endl;
      at::parallel_for(0, cols, 1, [&](int64_t begin, int64_t end) {
        if (begin == end) {
          return;
        }

        TensorIterator sub_iter(*this);
        sub_iter.narrow(dim, begin, end - begin);
        sub_iter.foreach_reduced_elt(loop, false);
      });
    }
  }
} // namespace at


void _axis_modsum(at::TensorIteratorBase& iter) {

  iter.foreach_reduced_elt([](at::TensorIteratorBase &sub_iter) {

    auto reduction_body = [&sub_iter](
        SINGLE_PRECISION acc, SINGLE_PRECISION begin, SINGLE_PRECISION end) -> SINGLE_PRECISION {

          sub_iter.serial_for_each([&acc](char** data, const int64_t* strides, int64_t size) {
              char *in_a = data[1];
              char *in_p = data[2];
              int64_t stride_a = strides[1];
              int64_t stride_p = strides[2];
              for ([[maybe_unused]] const auto _ : c10::irange(size)) {
                 auto a = c10::load<SINGLE_PRECISION>(in_a);
                 auto p = c10::load<SINGLE_PRECISION>(in_p);
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

    at::native::set_results<r_traits>(total_acc, sub_iter, 1);
  }, true);
}

// ======================================================

void cpu_apply_axis_modsum(
    at::Tensor result,
    const at::Tensor a,
    const at::Tensor p) {

        at::TensorIterator iter = at::TensorIteratorConfig()
          .add_owned_output(result)
          .add_owned_const_input(a)
          .add_owned_const_input(p)
          .resize_outputs(false)
          .is_reduction(true)
          .build();

        _axis_modsum(iter);
    }
