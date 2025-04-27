#include <ATen/Parallel.h>
#include "ntt_utils.h"
#include "mod_ops.h"

namespace ntt_utils {

    SINGLE_PRECISION _modmul(SINGLE_PRECISION a, SINGLE_PRECISION b, SINGLE_PRECISION p) {
        DOUBLE_PRECISION temp = (DOUBLE_PRECISION)a * (DOUBLE_PRECISION)b;
        return (SINGLE_PRECISION)(temp % p);
    }

    SINGLE_PRECISION _modsum(SINGLE_PRECISION a, SINGLE_PRECISION b, SINGLE_PRECISION p) {
        SINGLE_PRECISION res = a + b;
        return res < p ? res : res - p;
    }

    SINGLE_PRECISION _modsub(SINGLE_PRECISION a, SINGLE_PRECISION b, SINGLE_PRECISION p) {
        SINGLE_PRECISION res = a - b;
        return res < 0 ? res + p : res;
    }

    TTensor ntt(crt_params_and_state::CrtParams& crt_params,
                crt_params_and_state::CrtState& crt_state,
                TTensor& a,
                int axis,
                bool inplace) {

        auto& q_list = crt_state.q_list();
        // Reshape 'a' and 'result' into 4D tensor
        std::vector<int64_t> result_shape = t_eng::_broadcast_shapes({a.sizes(), q_list.sizes()});
        TTensor result = t_eng::_get_result_container(a, inplace, result_shape, nullptr);
        std::tie(a, axis, result) = t_eng::reshape_4d(a, axis, result);

        // Fix negative values
        result = t_eng::modlt(a, q_list, inplace, &result);

        auto n = crt_params.get_n();
        auto result_accessor = result.packed_accessor32<int64_t,4,at::DefaultPtrTraits>();
        auto q_list_accessor = q_list.packed_accessor32<int64_t,1,at::DefaultPtrTraits>();
        auto s_accessor = crt_state.get_active_psi_arr().packed_accessor32<int64_t,2,at::DefaultPtrTraits>();
        int64_t nb_poly = result.size(0)*result.size(2)*result.size(3);


        // Multithreaded computation
        at::parallel_for(0, nb_poly, 1, [&](int64_t begin, int64_t end) {
            for (int64_t x = begin; x < end; ++x) {

                int64_t k = x / (result_accessor.size(2) * result_accessor.size(3));
                int64_t l = (x / result_accessor.size(3)) % result_accessor.size(2);
                int64_t q = x % result_accessor.size(3);

                int64_t t = n;

                for (int64_t m = 1; m < n; m = 2 * m) {
                    t /= 2;

                    for (int64_t i = 0; i < m; i++) {
                        int64_t j1 = 2 * i * t;
                        int64_t j2 = j1 + t;
                        auto s = s_accessor[q][m + i];

                        for (int64_t j = j1; j < j2; j++) {
                            auto u = result_accessor[k][j][l][q];
                            auto v = result_accessor[k][j + t][l][q];
                            auto p = q_list_accessor[q];

                            v = _modmul(v, s, p);
                            auto modsub_res = _modsub(u, v, p);
                            result_accessor[k][j][l][q] = _modsum(u, v, p);
                            result_accessor[k][j + t][l][q] = modsub_res;
                        }
                    }
                }
            }
        });

        // Apply permutation
        result = result.index({Ellipsis, crt_params.get_perm(), Slice(), Slice()});

        // Reshape 'result' from 4D into input shape
        result = result.reshape(result_shape);

        return result;
    }

    TTensor intt(
                crt_params_and_state::CrtParams& crt_params,
                crt_params_and_state::CrtState& crt_state,
                TTensor& a,
                int axis) {

        auto& q_list = crt_state.q_list();
        // Reshape 'a' and 'result' into 4D tensor
        std::vector<int64_t> result_shape = t_eng::_broadcast_shapes({a.sizes(), q_list.sizes()});
        TTensor result = t_eng::_get_result_container(a, true, result_shape, nullptr);
        std::tie(a, axis, result) = t_eng::reshape_4d(a, axis, result);

        // Apply permutation
        a = a.index({Ellipsis, crt_params.get_perm(), Slice(), Slice()});

        // Fix negative values
        result = t_eng::modlt(a, q_list, false, &result);

        auto n = crt_params.get_n();
        auto result_accessor = result.packed_accessor32<int64_t,4,at::DefaultPtrTraits>();
        auto q_list_accessor = q_list.packed_accessor32<int64_t,1,at::DefaultPtrTraits>();
        auto s_accessor = crt_state.get_active_psi_inv_arr().packed_accessor32<int64_t,2,at::DefaultPtrTraits>();
        int64_t nb_poly = result.size(0)*result.size(2)*result.size(3);

        // Multithreaded computation
        at::parallel_for(0, nb_poly, 1, [&](int64_t begin, int64_t end) {
            for (int64_t x = begin; x < end; x++) {

                int64_t k = x / (result_accessor.size(2)*result_accessor.size(3));
                int64_t l = (x / result_accessor.size(3)) % result_accessor.size(2);
                int64_t q = x % result_accessor.size(3);

                int64_t t = 1;
                int64_t m = n/2;
                while (m >= 1) {

                    for (int64_t tid = 0; tid < n/2; tid++) {
                        int64_t i_tid = tid / t;
                        int64_t idx_u = i_tid * t + tid;
                        int64_t idx_v = idx_u + t;
                        int64_t idx_psi = m + i_tid;

                        auto s = s_accessor[q][idx_psi];

                        auto u = result_accessor[k][idx_u][l][q];
                        auto v = result_accessor[k][idx_v][l][q];
                        auto p = q_list_accessor[q];

                        auto modsub_res = _modsub(u, v, p);
                        result_accessor[k][idx_u][l][q] = _modsum(u, v, p);
                        result_accessor[k][idx_v][l][q] = _modmul(modsub_res, s, p);
                    }
                    t *= 2;
                    m /= 2;
                }
            }
        });

        result = t_eng::modmul(result, crt_state.get_active_n_inv_list(), crt_state.q_list(), false, &result);

        // Reshape 'result' from 4D into input shape
        result = result.reshape(result_shape);

        return result;
    }

} // namespace ntt_utils
