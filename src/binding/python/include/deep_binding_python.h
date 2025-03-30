#pragma once

#include <pybind11/pybind11.h>
namespace py = pybind11;

#include "python_tensor_engine.h"
#include "slot_permutations.h"
#include "context_utils.h"
#include "encryption_scheme_utils.h"
#include "encryption_schemes.h"
#include "homomorphic_operations.h"

void define_deep_bindings(py::module &m) {

  // slot permutations
  m.def("raw_apply_crt_permutation_elementwise", &perm_utils::py_apply_crt_permutation_elementwise, "raw_apply_crt_permutation_elementwise");
  m.def("raw_apply_crt_permutation", &perm_utils::py_apply_crt_permutation, "raw_apply_crt_permutation");
  m.def("raw_propagate_crt_perms_on_input", &perm_utils::py_propagate_crt_perms_on_input, "raw_propagate_crt_perms_on_input");
  // initialize objects
  m.def("raw_create_context", &context::py_create_context, "raw_create_context");
  m.def("raw_create_params", &global_params_and_state::py_create_params, "raw_create_params");
  m.def("raw_create_state", &global_params_and_state::py_create_state, "raw_create_state");
  m.def("raw_create_mod_state", &mod_params_and_state::py_create_mod_state, "raw_create_mod_state");
  m.def("raw_create_crt_state", &crt_params_and_state::py_create_crt_state, "raw_create_crt_state");
  m.def("raw_create_crt_params", &crt_params_and_state::py_create_crt_params, "raw_create_crt_params");
  // tensor engine
  m.def("raw_intt", &ntt_utils::py_intt, "raw_intt");
  m.def("raw_ntt", &ntt_utils::py_ntt, "raw_ntt");
  // crt utils
  m.def("raw_crt_to_coefs", &crt_utils::py_crt_to_coefs, "raw_crt_to_coefs");
  m.def("raw_coefs_to_crt", &crt_utils::py_coefs_to_crt, "raw_coefs_to_crt");
  m.def("raw_crt_to_coefs_q", &crt_utils::py_crt_to_coefs_q, "raw_crt_to_coefs_q");
  m.def("raw_coefs_to_crt_q", &crt_utils::py_coefs_to_crt_q, "raw_coefs_to_crt_q");
  m.def("raw_crt_to_coefs_p", &crt_utils::py_crt_to_coefs_p, "raw_crt_to_coefs_p");
  m.def("raw_coefs_to_crt_p", &crt_utils::py_coefs_to_crt_p, "raw_coefs_to_crt_p");
  // mod utils
  m.def("raw_to_crt_tensor", &mod_utils::py_to_crt_tensor, "raw_to_crt_tensor");
  m.def("raw_from_crt_tensor_to_bigint", &mod_utils::py_from_crt_tensor_to_bigint, "raw_from_crt_tensor_to_bigint", py::return_value_policy::reference);
  // pt_shape
  m.def("raw_convert_internal_to_external", &pt_shape::py_convert_internal_to_external, "raw_convert_internal_to_external");
  m.def("raw_convert_external_to_internal", &pt_shape::py_convert_external_to_internal, "raw_convert_external_to_internal");
  // plaintext
  m.def("raw_encode_pt", &plaintext::py_encode_pt, "raw_encode_pt");
  m.def("raw_decode_pt", &plaintext::py_decode_pt, "raw_decode_pt");
  // encryption schemes
  m.def("raw__RBGV__enc", &encryption_schemes::py__RBGV__enc, "raw__RBGV__enc");
  m.def("raw__RBGV_dec_and_get_error", &encryption_schemes::py__RBGV_dec_and_get_error, "raw__RBGV_dec_and_get_error");
  m.def("raw__CKKS__enc", &encryption_schemes::py__CKKS__enc, "raw__CKKS__enc");
  m.def("raw__CKKS_dec_and_get_error", &encryption_schemes::py__CKKS_dec_and_get_error, "raw__CKKS_dec_and_get_error");
  m.def("raw__CKKS_unpack_pt", &encryption_schemes::py__CKKS_unpack_pt, "raw__CKKS_unpack_pt");
  m.def("raw__CKKS_pack_pt", &encryption_schemes::py__CKKS_pack_pt, "raw__CKKS_pack_pt");
  m.def("raw__CKKS_G__enc", &encryption_schemes::py__CKKS_G__enc, "raw__CKKS_G__enc");
  m.def("raw__RBGV_G__enc", &encryption_schemes::py__RBGV_G__enc, "raw__RBGV_G__enc");
  m.def("raw__RBGV_G_CRT__enc", &encryption_schemes::py__RBGV_G_CRT__enc, "raw__RBGV_G_CRT__enc");
  m.def("raw__CKKS_G_CRT__enc", &encryption_schemes::py__CKKS_G_CRT__enc, "raw__CKKS_G_CRT__enc");
  // key switch
  m.def("raw_gen", &key_switch::py_gen, "raw_gen");
  m.def("raw_gen_full_key", &key_switch::py_gen_full_key, "raw_gen_full_key");
  m.def("raw_gen_base_key", &key_switch::py_gen_base_key, "raw_gen_base_key");
  m.def("raw_get_square_key", &key_switch::py_get_square_key, "raw_get_square_key");
  m.def("raw_create_aux_key", &key_switch::py_create_aux_key, "raw_create_aux_key");

  // homomorphic operations
  m.def("raw_create_query_client_block", &homom_ops::py_create_query_client_block, "raw_create_query_client_block");
  m.def("raw_create_query_client_sequential_hom_op", &homom_ops::py_create_query_client_sequential_hom_op, "raw_create_query_client_sequential_hom_op");
  m.def("raw_apply_clear", &homom_ops::py_apply_clear, "raw_apply_clear");
}
