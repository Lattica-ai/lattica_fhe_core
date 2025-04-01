#include <ATen/ATen.h>
#include "common_g_crt.h"

namespace encryption_schemes {

std::tuple<TTensor, TTensor> _EncryptionScheme_G_CRT::sample_randomness(
        context::Context& context,
        pt_shape::PtShape& pt_shape,
        optional<global_params_and_state::State> t_state) {

    global_params_and_state::State state = t_state ? t_state.value() : context.init_state;
    std::vector<int64_t> additional_dims = {state.len_q_list(), context.params.pt_g_params.g_exp};
    TTensor a, e;
    std::tie(a, e) = _sample_randomness(context, state, pt_shape, additional_dims, -4 /* n_axis */);
    a = a.moveaxis(0, -4).index({0, 0});
    e = e.moveaxis(0, -4).index({0, 0});
    return std::make_tuple(a, e);
}

TTensor _EncryptionScheme_G_CRT::_enc(
        context::Context& context,
        global_params_and_state::State& state,
        TTensor& pt,
        TTensor& sk,
        TTensor& a,
        TTensor& e) {

    auto params = context.params;
    TTensor sk_a = t_eng::modmul(
        a, sk.unsqueeze(-2).unsqueeze(-2).unsqueeze(-2), state.q_list(), false
    );
    TTensor new_g = (
        t_eng::eye(state.len_q_list()).unsqueeze(1) * params.g_params.get_g_vec(state).unsqueeze(0)
    );
    pt = pt.moveaxis(0, 1);
    TTensor pt_g = t_eng::modmul(
        new_g,
        pt.unsqueeze(-2).unsqueeze(-2),
        state.q_list(), true
    );
    TTensor temp = t_eng::modsum(pt_g, e, state.q_list(), true);
    TTensor b = t_eng::modsum(temp, sk_a, state.q_list(), true);
    return b;
}

Ciphertext _EncryptionScheme_G_CRT::apply_mod_switch_down_drop(
        Ciphertext& ct,
        Slice relative_new_indices) {

    return ct.get_item({"...", relative_new_indices}
            ).get_item({"...", relative_new_indices, Slice(), Slice(), Slice()});
}

} // namespace encryption_schemes
