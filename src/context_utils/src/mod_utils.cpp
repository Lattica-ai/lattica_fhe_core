#include "mod_utils.h"
#include <iostream>

namespace mod_utils {

TTensor to_crt_tensor(TTensor& q_list, TTensor& a) {
    a = a.unsqueeze(-1);
    return t_eng::mod(a, q_list, false);
}

void print_big_num(Num& a) {
    std::vector<char> res_vec_char;
    a.print(res_vec_char);
    for (auto i : res_vec_char) {
        std::cout << i;
    }
    std::cout << std::endl;
}

std::vector<Num> from_crt_tensor_to_bigint(
        mod_params_and_state::ModState& mod_state,
        TTensor& a,
        Num final_mod) {
    TTensor temp_a = a.reshape({-1, a.size(-1)});
    std::vector<Num> res;
    auto num_el = temp_a.size(0);
    
    for (int j = 0; j < num_el; j++) {
        Num temp = Num(0);
        for (int i = 0; i < mod_state.active_reconstruction_terms.size(); i++) {
            Num temp_a_ij = Num(temp_a[j][i].item<SINGLE_PRECISION>());
            Num recon_term_class = mod_state.active_reconstruction_terms[i];
            temp_a_ij = temp_a_ij * recon_term_class;
            temp = temp + temp_a_ij;
            temp = temp % mod_state.active_q;
        }
        temp = temp % final_mod;
        if (temp < 0) {
            temp = temp + final_mod;
        }
        res.push_back(temp);
    }
    return res;
}

std::vector<std::string> from_crt_tensor_to_bigint(
        mod_params_and_state::ModState& mod_state,
        TTensor& a, 
        std::string final_mod) {
    Num final_mod_bigint = Num(final_mod.c_str());
    std::vector<Num> res_bigint = from_crt_tensor_to_bigint(mod_state, a, final_mod_bigint);
    std::vector<std::string> res;
    
    for (int i = 0; i < res_bigint.size(); i++) {
        std::vector<char> res_vec_char;
        res_bigint[i].print(res_vec_char);
        std::string res_str(res_vec_char.begin(), res_vec_char.end() - 1);
        std::cout << res_str << std::endl;
        res.push_back(res_str);
    }
    return res;
}

} // namespace mod_utils
