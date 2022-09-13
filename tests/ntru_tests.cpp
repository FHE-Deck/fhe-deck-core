 

#include <iostream>
#include "../include/lwe.h"
#include "../include/ntru.h"
#include "../include/ntru_param.h"
#include "../include/fft_plan.h"
#include <NTL/ZZX.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_p.h>
#include <random>
#include <math.h>

/*
void ntru_param_test(){

    std::cout << "========= ntru_param_test ============" << std::endl; 
   // Setting up parameters
   int N = 5;
   long Q = 29; 
   double stddev = 3.2;
   long t = 4;
   long delta_Q_t = (long)round((double)Q/(double)t); 
   ntru_param param(cyclic, N, Q, any, stddev); 

   long msg[N] = {1, 2, 3, 4, 5};
   long *out = param.init_poly();
   param.rotate(out, msg, 2);
   std::cout << "Rotated: " << utils::to_string(out, N) << std::endl;


   msg[0] = -28;
   std::cout << "msg[0]: " << utils::integer_signed_form(msg[0], Q) << std::endl; 
 
}


void small_modulu_ntru_tests(){
   
   std::cout << "========= small_modulu_ntru_tests ============" << std::endl; 
   // Setting up parameters
   int N = 4;
   long Q = 101; 
   double stddev = 3.2;
   long t = 4;
   long delta_Q_t = (long)round((double)Q/(double)t); 
   ntru_param param(cyclic, N, Q, any, stddev);  
 
   //  Key generation
   long *key = param.init_poly();
   long *inv_key = param.init_poly();
   ntru_sk::key_gen(key, inv_key, param);
   ntru_sk ntru(param, key, inv_key);

   NTL::ZZ_pX key_poly;
   utils::set_polynomial_from_array(key_poly, key, N, Q);
   NTL::ZZ_pX inv_key_poly;
   utils::set_polynomial_from_array(inv_key_poly, inv_key, N, Q);
   // Lets multiply both, and check whether we get 1, modulo psi 
   NTL::ZZ_pX res;
   NTL::MulMod(res, key_poly, inv_key_poly, param.psi_poly);
   if(res == 1){
      std::cout << "- Test Key generation: OK" << std::endl;
   }else{
      std::cout << "- Test Key generation: Fail" << std::endl;
   }  
 
   // std::cout << "-------- Testing Encryption and Decryption..." << std::endl;  
   int sizeof_msg = param.N;
   long* msg = param.init_zero_poly();
   msg[1] = delta_Q_t * 1;

   NTL::ZZ_pX msg_poly;
   utils::set_polynomial_from_array(msg_poly, msg, sizeof_msg, Q);
   long *msg_round = new long[sizeof_msg];
   utils::array_rounding(msg_round, msg, sizeof_msg, Q, t);
   NTL::ZZ_pX msg_round_poly;
   utils::set_polynomial_from_array(msg_round_poly, msg_round, sizeof_msg, Q);
   if(msg_round_poly[0] == 0 && msg_round_poly[1] == 1){
      std::cout << "- Rounding Test: OK" << std::endl;
   }else{
      std::cout << "- Rounding Test: Fail" << std::endl;
      std::cout << "msg_poly: " << msg_poly << std::endl;
      std::cout << "msg_round_poly: " << msg_round_poly << std::endl;
   } 
   NTL::ZZ_pX msg_expected_poly = NTL::MulMod(msg_round_poly, key_poly, param.psi_poly);
   // std::cout << "msg_poly(" << msg_round_poly << ") * key_poly(" << key_poly << ") = msg_expected_poly" << msg_expected_poly << std::endl;
 

   long *ct_ntru = ntru.encrypt(msg);  
   long *out_msg = ntru.decrypt(ct_ntru, t);
   NTL::ZZ_pX out_msg_poly;
   utils::set_polynomial_from_array(out_msg_poly, out_msg, N, Q);
   if(out_msg_poly == msg_expected_poly){
      std::cout << "- Decryption test: OK" << std::endl;
   }else{
      std::cout << "- Decryption test: Fail"  << std::endl;
      std::cout << "out_msg_poly" << out_msg_poly << std::endl;
      std::cout << "msg_expected_poly" << msg_expected_poly << std::endl;
   } 
  
}
*/



void large_modulu_ntru_tests(){
   
   std::cout << "========= large_modulu_ntru_tests ============" << std::endl; 
   // Setting up parameters
   int N = 2048;
   long Q = 1073741827; 
   double stddev = 3.2;
   long t = 8;
   long delta_Q_t = (long)round((double)Q/(double)t); 
 
   ntru_param param(negacyclic, N, Q, any, stddev);  

   //  Key generation
   long *key = param.init_poly();
   long *inv_key = param.init_poly();
   ntru_sk::key_gen(key, inv_key, param);
   ntru_sk ntru(param, key, inv_key);
     
   std::cout << "-------- Testing Encryption and Decryption..." << std::endl;  
   int sizeof_msg = param.N;
   long* msg = param.init_zero_poly(); 
  
   std::cout << "Encrypt..." << std::endl;
   ntru_ct ct_ntru = ntru.encrypt(msg); 
   std::cout << "Decrypt..." << std::endl;
   long *out_msg = ntru.decrypt(&ct_ntru, t); 
   std::cout << "Testing..." << std::endl;
   if(utils::is_eq_poly(out_msg, msg, param.N)){
      std::cout << "- Decryption 1 test: OK" << std::endl;
   }else{
      std::cout << "- Decryption 1 test: Fail"  << std::endl;
   } 
  
 
   msg[0] = delta_Q_t; 
   ntru_ct ct_ntru_3 = ntru.encrypt(msg); 
   long *out_msg_2 = ntru.decrypt(&ct_ntru_3, t);
   //long *key_signed = param.init_poly();
   //utils::array_signed_form(key_signed, key, param.N, param.Q);
   // Remind that msg_expected_poly is the message multiplied by the secret key 
   if(utils::is_eq_poly(out_msg_2, key, param.N)){
      std::cout << "- Decryption 2 test: OK" << std::endl;
   }else{
      std::cout << "- Decryption 2 test: Fail"  << std::endl;
      std::cout << "out_msg_2: " << utils::to_string(out_msg_2, param.N) << std::endl;
      std::cout << "key: " << utils::to_string(key, param.N) << std::endl;
   } 
 
}



void kdm_ntru_tests(){
   
   std::cout << "========= kdm_ntru_tests ============" << std::endl; 
   // Setting up parameters
   int N = 2048;
   long Q = 1073741827; 
   double stddev = 3.2;
   long t = 8;
   long delta_Q_t = (long)round((double)Q/(double)t); 
 
   ntru_param param(negacyclic, N, Q, any, stddev);  

   //  Key generation
   long *key = param.init_poly();
   long *inv_key = param.init_poly();
   ntru_sk::key_gen(key, inv_key, param);
   ntru_sk ntru(param, key, inv_key);
     
   // std::cout << "-------- Testing Encryption and Decryption..." << std::endl;  
   int sizeof_msg = param.N; 
   long* exp_msg = param.init_zero_poly(); 
   exp_msg[0] = 0;
   exp_msg[1] = 1;
   exp_msg[2] = 2;
   //exp_msg[3] = 3;
   //exp_msg[4] = 4;
   long* msg = param.init_zero_poly(); 
   for(int i = 0; i < sizeof_msg; ++i){
      msg[i] = exp_msg[i] * delta_Q_t; 
   }
   

   ntru_ct ct_ntru = ntru.kdm_encrypt(msg); 
   long *out_msg = ntru.decrypt(&ct_ntru, t); 
   if(utils::is_eq_poly(out_msg, exp_msg, param.N)){
      std::cout << "- KDM Decryption Test: OK" << std::endl;
   }else{
      std::cout << "- KDM Decryption Test: Fail"  << std::endl;
      std::cout << "out_msg: " << utils::to_string(out_msg, param.N) << std::endl;
      std::cout << "msg: " << utils::to_string(msg, param.N) << std::endl;
      std::cout << "exp_msg: " << utils::to_string(exp_msg, param.N) << std::endl;
   } 
   
 
}


/*
// TODO: This should be in some utils test
void decomposition_test(){
 
   std::cout << "========= decomposition_test =============" << std::endl;
   long Q = 1073741827; 
   // Testing Integer decomposition
   // a in binary is = 1 111 011
   long a = 123;
   // So decomposition should give us 1, 111, 011.
   // In integer its 1, 7, 3. And indeed 3 + 8 * 7 + 64 * 1 = 123
   int k = 3;
   // 2**3
   int basis = 8;
   // From python
   // 11 = math.ceil(math.log(1073741827, 8))
   int ell = 11;
   long* dec_a = new long[ell];
   ntru_sk::integer_decomp(dec_a, a, basis, k, ell); 
   int temp_basis = 1;
   long composed = dec_a[0];
   for(int i = 1; i < ell; ++i){ 
      temp_basis = temp_basis * basis;
      composed = composed + (dec_a[i] * temp_basis);
   }
   if(composed == a){
      std::cout << "- Integer Composition Test: OK" << std::endl;
   }else{
      std::cout << "- Integer Composition Test: Fail" << std::endl;
   }

   // Test Polynomial Decomposition
   int sizeof_b = 3;
   long b[sizeof_b] = {4, 18, 14};
   long **dec_b = new long*[ell];
   for(int i = 0; i < ell; ++i){
      dec_b[i] = new long[sizeof_b];
   }
   utils::decomp(dec_b, b, sizeof_b, basis, k, ell); 
   long *comp_b = new long[sizeof_b];
   utils::compose(comp_b, dec_b, sizeof_b, basis, ell); 
   
   if(utils::is_eq_poly(comp_b, b, sizeof_b)){
      std::cout << "- Polynomials Decomposition Test: OK" << std::endl;
   }else{
      std::cout << "- Polynomials Decomposition Test: Fail" << std::endl;
   }
 
   // Another test:
   long t = 8;
   long delta_Q_t = (long)round((double)Q/(double)t);
   int sizeof_scalar = 1;
   long scalar[sizeof_scalar] = {delta_Q_t * 1}; 
   long **dec_scalar = new long*[ell];
   for(int i = 0; i < ell; ++i){
      dec_scalar[i] = new long[sizeof_scalar];
   }
   utils::decomp(dec_scalar, scalar, sizeof_scalar, basis, k, ell); 
   long *comp_scalar = new long[sizeof_scalar];
   utils::compose(comp_scalar, dec_scalar, sizeof_scalar, basis, ell); 
   
   if(utils::is_eq_poly(comp_scalar, scalar, sizeof_scalar)){
      std::cout << "- Scalar Decomposition Test: OK" << std::endl;
   }else{
      std::cout << "- Scalar Decomposition Test: Fail" << std::endl;
   }
   

   // Testing Signed Decomp
   Q = 1073741827; 
   sizeof_b = 3;
   b[0] = Q-2342;
   b[1] = Q-12;
   b[2] = 12309;

   utils::signed_decomp(dec_b, b, sizeof_b, basis, k, ell, Q); 
 

   //long *comp_b = new long[sizeof_b];
   utils::compose(comp_b, dec_b, sizeof_b, basis, ell); 
   utils::array_signed_form(b, b, sizeof_b, Q);
   
   if(utils::is_eq_poly(comp_b, b, sizeof_b)){
      std::cout << "- Signed Polynomials Decomposition Test: OK" << std::endl;
   }else{
      std::cout << "- Signed Polynomials Decomposition Test: Fail" << std::endl;
      std::cout << "comp_b: " << utils::to_string(comp_b, sizeof_b) << std::endl;
   }


}
*/




void temp_test_decryption_single_coefficient(){
   std::cout << "========= temp_test_decryption_single_coefficient ============" << std::endl; 
   // Setting up parameters
   int N = 8;
   long Q = 1073741827; 
   double stddev = 3.2;
   long t = 8;
   long delta_Q_t = (long)round((double)Q/(double)t);
    
   ntru_param param(negacyclic, N, Q, any, stddev); 
  
   //  Key generation
   long *key = param.init_poly();
   long *inv_key = param.init_poly();
   ntru_sk::key_gen(key, inv_key, param); 
   ntru_sk ntru(param, key, inv_key);
 
   long* msg = param.init_zero_poly();
   msg[0] = delta_Q_t * 1;
   ntru_ct ct = ntru.encrypt(msg); 
   long *out = ntru.decrypt(&ct, t);
   
   //std::cout << "key: " << utils::to_string(key, param.N) << std::endl;
   //std::cout << "out: " << utils::to_string(out, param.N) << std::endl;
 
   // ``Decrypting'' the first coefficient only.   
   long first_coef = utils::integer_mod_form(ntru.decrypt_coef(&ct, t), param.Q);  
   first_coef = first_coef % param.Q;
   if(first_coef == utils::integer_mod_form(out[0], param.Q)){
      std::cout << "Decrypting Constant Coefficient Test: OK" << std::endl;
   }else{
      std::cout << "Decrypting Constant Coefficient Test: Fail" << std::endl;
      std::cout << "first_coef: " << first_coef << std::endl;
      std::cout << "out[0]: " << out[0] << std::endl;
   }
 
}


void test_ntru_mod_switching(){
 
   std::cout << "========= test_ntru_mod_switching ============" << std::endl; 

   // The test must be different:
   // We generate the secret key with respect to the new Q
   // But we do encryption for the old Q
   // Do I actually need to ``switch" the inverse key modulus to have a rescaled representation of -1?
 
   // Setting up parameters
   int N = 8; 
   long Q = 1073741831; 
   double stddev = 3.2;
   long t = 8;
   long delta_Q_t = (long)round((double)Q/(double)t); 
   ntru_param param(negacyclic, N, Q, any, stddev); 
  
   //  Key generation
   long *key = param.init_poly();
   long *inv_key = param.init_poly(); 
   ntru_sk::key_gen(key, inv_key, param); 
   ntru_sk ntru(param, key, inv_key);

   long* msg = param.init_zero_poly();
   msg[0] = delta_Q_t * 1;
   ntru_ct ct = ntru.encrypt(msg); 
   long *out = ntru.decrypt(&ct, t); 
 
   long new_Q = 1073741827; 
   //long* key_signed = param.init_poly();
   //utils::array_signed_form(key_signed, key, param.N, param.Q);
   std::cout << "key_signed: " << utils::to_string(key, param.N) << std::endl;  
   long *new_key = key;
   long* new_inv_key = inv_key;
   ntru_param new_param(negacyclic, N, new_Q, any, stddev); 
   ntru_sk new_ntru(new_param, new_key, new_inv_key);
 

   //long *new_ct = ntru_sk::switch_modulus(ct, new_param, param);
   ntru_ct new_ct = ct.mod_switch(new_param);
   
   long *new_out = new_ntru.decrypt(&new_ct, t); 
   if(utils::is_eq_poly(new_out, out, new_param.N)){
      std::cout << "Modulus Switching Test: OK"  <<   std::endl;
   }else{
      std::cout << "Modulus Switching Test: Fail"  <<   std::endl;
   }
 
   ntru_ct kdm_ct = ntru.kdm_encrypt(msg); 
   long *kdm_out = ntru.decrypt(&kdm_ct, t); 
   //long *new_kdm_ct = ntru_sk::switch_modulus(ct, new_param, param); 
   ntru_ct new_kdm_ct = ct.mod_switch(new_param);
   long *new_kdm_out = new_ntru.decrypt(&kdm_ct, t); 
   if(utils::is_eq_poly(new_kdm_out, kdm_out, new_param.N)){
      std::cout << "KDM Modulus Switching Test: OK"  <<   std::endl;
   }else{
      std::cout << "KDM Modulus Switching Test: Fail"  <<   std::endl;
   }

   long* larger_msg = ntru.param.init_poly();
   for(int i = 0; i < ntru.param.N; ++i){
      larger_msg[i] = delta_Q_t * 2;
   }
   ntru_ct kdm_ct_2 = ntru.kdm_encrypt(larger_msg); 
   long *kdm_out_2 = ntru.decrypt(&kdm_ct_2, t); 
   //long *new_kdm_ct_2 = ntru_sk::switch_modulus(kdm_ct_2, new_param, param); 
   ntru_ct new_kdm_ct_2 = kdm_ct_2.mod_switch(new_param);
   long *new_kdm_out_2 = new_ntru.decrypt(&new_kdm_ct_2, t); 
   if(utils::is_eq_poly(kdm_out_2, new_kdm_out_2, new_param.N)){
      std::cout << "KDM Modulus Switching Test 2: OK"  <<   std::endl;
   }else{
      std::cout << "KDM Modulus Switching Test 2: Fail"  <<   std::endl;
   }

}  


void test_power_of_two_ntru_mod_switching(){
 
   std::cout << "========= test_power_of_two_ntru_mod_switching ============" << std::endl; 
 
   // Strategy:
   // 1) Take a ``close to the power of two (a little smaller) prime, with parameters.
   // 2) Generate a secret key in this prime field. 
   // 3) Take a power of two paramater set, and encrypt the message in power of two (using the previous encryption key)
   // 4) Modulus switch to the prime power
   // 5) Decrypt
  
   // Setting up parameters
   int N = 8;
   // Q = 2^20: a close prime is: Q-3 = 1048573
   long Q_pot = 1048576; 
   long Q = Q_pot - 3;
   double stddev = 3.2;
   long t = 8;
   long delta_Q_t_pot = (long)round((double)Q_pot/(double)t); 
   //long delta_Q_t = (long)round((double)Q/(double)t); 
   ntru_param param(negacyclic, N, Q, any, stddev); 
   ntru_param param_pot(negacyclic, N, Q_pot, power_of_two, stddev); 
  
   //  Key generation
   long *key = param.init_poly();
   long *inv_key = param.init_poly();
   ntru_sk::key_gen(key, inv_key, param);
   ntru_sk ntru(param, key, inv_key);  
   ntru_sk ntru_pot(param_pot, key, inv_key);
 

   // Now we encrypt with param_pot for power of two
   //int sizeof_msg = 1;
   long *msg = param_pot.init_zero_poly();
   msg[0] = {delta_Q_t_pot * 1};  
   //long *ct = ntru_pot.encrypt(msg); 
   ntru_ct ct = ntru_pot.encrypt(msg);
   // This ciphertext is not decryptable
   
   // Switch modulus to a prime modulus
   //long *new_ct = ntru_sk::switch_modulus(ct, param, param_pot);
   ntru_ct new_ct = ct.mod_switch(param);
 

   // Decrypt (should be an encryption of sk * 1 - so basically encryption of sk)
   long *new_out = ntru.decrypt(&new_ct, t); 
 
   //long* out = param.init_poly();
   //out[0] = 1;
   //long* signed_key = param.init_poly();
   //utils::array_signed_form(signed_key, key, param.N, param.Q);
   if(utils::is_eq_poly(new_out, key, param.N)){
      std::cout << "Power of Two Modulus Switching Test: OK"  <<   std::endl;
   }else{
      std::cout << "Power of Two Modulus Switching Test: Fail"  <<   std::endl;
      std::cout << "new_out: " << utils::to_string(new_out, param.N) << std::endl;
      std::cout << "key: " << utils::to_string(key, param.N) << std::endl;
   } 
 
   
   msg[0] = {delta_Q_t_pot * 0};
   msg[1] = {delta_Q_t_pot * 1}; 
   msg[2] = {delta_Q_t_pot * 2}; 
   msg[3] = {delta_Q_t_pot * 3}; 
   msg[4] = {delta_Q_t_pot * 4}; 
   long *msg_round = param_pot.init_poly();
   utils::array_rounding(msg_round, msg, param_pot.N, param_pot.Q, t);
   // long *kdm_ct = ntru.kdm_encrypt(msg);  
   ntru_ct kdm_ct = ntru.kdm_encrypt(msg);  
   // long *new_kdm_ct = ntru_sk::switch_modulus(ct, param, param_pot); 
   ntru_ct new_kdm_ct = ct.mod_switch(param);
   long *new_kdm_out = ntru.decrypt(&kdm_ct, t); 
   utils::array_mod_form(new_kdm_out, new_kdm_out, param.N, t);
   if(utils::is_eq_poly(new_kdm_out, msg_round, param.N)){
      std::cout << "KDM Power of Two Modulus Switching Test: OK"  <<   std::endl;
   }else{
      std::cout << "KDM  Power of Two Modulus Switching Test: Fail"  <<   std::endl;
      std::cout << "new_kdm_out: " << utils::to_string(new_kdm_out, param.N) << std::endl;
      std::cout << "msg_round: " << utils::to_string(msg_round, param.N) << std::endl;
   }
}


 
void power_of_two_reduction_test(){
  
   // 2^20
   long Q = 1048576;
   long a = Q - 10;
   long b = Q - 5; 
   unsigned long mask = Q-1;
   long c = a + b;
   long c_red = c & mask;
   if(c_red == (c%Q)){
      std::cout << "Power of two Addition Test: OK" << std::endl;
   }else{
      std::cout << "Power of two Addition Test: Fail" << std::endl;
   }

   a = 5;
   b = 7;
   c = a-b;
   c_red = c & mask;
   if(c_red == (Q+c)){
      std::cout << "Power of two Addition Test: OK" << std::endl;
   }else{
      std::cout << "Power of two Addition Test: Fail" << std::endl;
      std::cout << "c_red: " << c_red << ", c: " << c << ", (Q-c): " << (Q+c) << std::endl;
   }
}

 

void gadget_ntru_tests(){

   std::cout << "========= gadget_ntru_tests ============" << std::endl; 
   // Setting up parameters
   int N = 8;
   long Q = 1073741827; 
   //long Q = 7919;
   double stddev = 3.2;
   long t = 8;
   long delta_Q_t = (long)round((double)Q/(double)t); 
   ntru_param param(negacyclic, N, Q, any, stddev); 
 
 
   //  Key generation
   long *key = param.init_poly();
   long *inv_key = param.init_poly();
   ntru_sk::key_gen(key, inv_key, param);
   ntru_sk ntru(param, key, inv_key);

   NTL::ZZ_pX key_poly;
   utils::set_polynomial_from_array(key_poly, key, N, Q);
   NTL::ZZ_pX inv_key_poly;
   utils::set_polynomial_from_array(inv_key_poly, inv_key, N, Q);
   // Lets multiply both, and check whether we get 1, modulo psi 
   NTL::ZZ_pX res; 
   NTL::MulMod(res, key_poly, inv_key_poly, utils::get_ring_poly(param.ring, N, Q));
   if(res == 1){
      std::cout << "- Test Key generation: OK" << std::endl;
   }else{
      std::cout << "- Test Key generation: Fail" << std::endl;
   }

   // math.ceil(math.log(1073741827, 8)) = 11
   // math.log(8, 2) = 3
   int basis = 8;
   ntru_gadget_param g_par(param, basis, double_fft); 
   gadget_ntru g_ntru(g_par, ntru);
   if(g_par.ell == 11 && g_par.k == 3){
      std::cout << "Gadget Parameter Setup Test 1: OK" << std::endl;
   }else{
      std::cout << "Gadget Parameter Setup Test 1: Fail" << std::endl;
   } 

   // This is the message for the gadget
   //int sizeof_gadget_msg = 1;
   long* gadget_msg = param.init_zero_poly();
   gadget_msg[0] = 1;

   //int sizeof_scalar = 2;
   long* scalar = param.init_zero_poly();
   scalar[1] = delta_Q_t * 1;

   long* scalar_key = param.init_poly();
   utils::mul_mod(scalar_key, scalar, param.N, key, param.N, N, Q, negacyclic); 
   long* scalar_key_rounded = param.init_poly();
   utils::array_rounding(scalar_key_rounded, scalar_key, param.N, Q, t); 
 
   //long **gadget_ct = g_ntru.gadget_encrypt(gadget_msg);
   ntru_gadget_ct gadget_ct = g_ntru.gadget_encrypt(gadget_msg);
   //std::cout << "gadget_ct[0]: " << utils::to_string(gadget_ct[0], param.N) << std::endl; 

   //ntru_ct out_ct;
   //ntru_ct out_ct = g_par.gadget_mul(scalar, gadget_ct);
   ntru_ct out_ct(param);
   gadget_ct.gadget_mul(&out_ct, scalar);
   //std::cout << "out_ct after multiplication: " << out_ct.to_string() << std::endl;
   long *out_msg = ntru.decrypt(&out_ct, t);

   if(utils::is_eq_poly(out_msg, scalar_key_rounded, param.N)){
      std::cout << "Gadget Scalar Multiplication Test 1: OK" << std::endl;
   }
   else{
      std::cout << "Gadget Scalar Multiplication Test 1: Fail" << std::endl;
      std::cout << "out_msg: " << utils::to_string(out_msg, param.N) << std::endl;
      std::cout << "key: " << utils::to_string(key, param.N) << std::endl;
   }

 
   // Encrypting scalar_key
   ntru_ct ct_1 = ntru.encrypt(scalar);
   // Decryption should give us the scalar multiplied by the secret key.
   //long *out_ct_2 = param.init_poly();
   //ntru_ct out_ct_2 = g_par.gadget_mul(&ct_1,  gadget_ct);
   ntru_ct out_ct_2(param);
   gadget_ct.gadget_mul(&out_ct_2, &ct_1);
   // Decryption of out_ct_2 should give us the scalar multiplied by the secret key because the gadget ciphertext encrypts 1.
   long *out_msg_2 = ntru.decrypt(&out_ct_2, t);
   if(utils::is_eq_poly(out_msg_2, scalar_key_rounded, param.N)){
      std::cout << "Gadget Ciphertext Multiplication Test 2: OK" << std::endl;
   }
   else{
      std::cout << "Gadget Ciphertext Multiplication Test 2: Fail" << std::endl;
      std::cout << "out_msg_2: " << utils::to_string(out_msg_2, param.N) << std::endl;
      std::cout << "key: " << utils::to_string(key, param.N) << std::endl;
   }

}

 

void gadget_ntru_fft_tests(){

   std::cout << "========= gadget_ntru_fft_tests ============" << std::endl; 
   // Setting up parameters
   int N = 8;
   long Q = 2017;  
   double stddev = 1;
   long t = 5;
   long delta_Q_t = (long)round((double)Q/(double)t); 
   ntru_param param(negacyclic, N, Q, stddev); 
 
   //  Key generation
   long *key = param.init_poly();
   long *inv_key = param.init_poly(); 
   ntru_sk::key_gen(key, inv_key, param); 
   ntru_sk ntru(param, key, inv_key);
 
   int basis = 2;
   ntru_gadget_param g_par(param, basis, hexl_ntt); 
   gadget_ntru g_ntru(g_par, ntru);
  
 

   // This is the message for the gadget 
   long* gadget_msg = param.init_zero_poly();
   gadget_msg[0] = 1;

   // This message is what we want to multiply 
   long* msg = param.init_zero_poly();
   msg[1] = 4;
   long* msg_scaled = param.init_zero_poly();
   msg_scaled[1] = delta_Q_t * msg[1]; 
   long* scalar = param.init_zero_poly(); 
   scalar[1] = msg_scaled[1];
 

   ntru_gadget_ct gadget_ct = g_ntru.gadget_encrypt(gadget_msg);  
        
   // Set up the key multiplied by the scalar
   long* scalar_key = param.init_poly();
   utils::mul_mod(scalar_key, msg_scaled, param.N, key, N, N, Q, negacyclic); 
   long* scalar_key_rounded = param.init_poly();
   utils::array_rounding(scalar_key_rounded, scalar_key, param.N, Q, t);
  
    
   ntru_ct out_ct(param);
   gadget_ct.gadget_mul(&out_ct, scalar); 
   // Lets do it multiple times 
   gadget_ct.gadget_mul(&out_ct, scalar);  
   long *out_msg = ntru.decrypt(&out_ct, t);

   if(utils::is_eq_poly(out_msg, scalar_key_rounded, param.N)){
      std::cout << "Gadget Scalar Multiplication Test 1: OK" << std::endl;
   }
   else{
      std::cout << "Gadget Scalar Multiplication Test 1: Fail" << std::endl;
      std::cout << "out_msg: " << utils::to_string(out_msg, param.N) << std::endl;
      std::cout << "scalar_key_rounded: " << utils::to_string(scalar_key_rounded, param.N) << std::endl;
      std::cout << "key: " << utils::to_string(key, param.N) << std::endl;
   }
   
   // Encrypting scalar_key
   ntru_ct ct_1 = ntru.kdm_encrypt(scalar);  
     
   // Decryption should give us the scalar multiplied by the secret key
   ntru_ct out_ct_2(param);
   gadget_ct.gadget_mul(&out_ct_2, &ct_1); 

   // This modulus reduced gadget multiplication should be in out_ct_2
   // Decryption of out_ct_2 should give us the scalar multiplied by the secret key because the gadget ciphertext encrypts 1.
   long *out_msg_2 = ntru.decrypt(&out_ct_2, t);  
   utils::array_mod_form(out_msg_2, out_msg_2, N, t); 
   if(utils::is_eq_poly(out_msg_2, msg, param.N)){
      std::cout << "Gadget Ciphertext Multiplication Test 2: OK" << std::endl;
   }
   else{
      std::cout << "Gadget Ciphertext Multiplication Test 2: Fail" << std::endl;
      std::cout << "out_msg_2: " << utils::to_string(out_msg_2, param.N) << std::endl;
      std::cout << "key: " << utils::to_string(key, param.N) << std::endl;
      std::cout << "msg: " << utils::to_string(msg, param.N) << std::endl;
   } 
}

  


int main(){
  
   large_modulu_ntru_tests(); 
   kdm_ntru_tests();
   temp_test_decryption_single_coefficient();
 
   test_ntru_mod_switching();  
   //test_power_of_two_ntru_mod_switching();  
 
   gadget_ntru_fft_tests();

   // TODO: These tests need to be rewriten 
   //gadget_ntru_tests();
   //gadget_ntru_fft_tests();
 
   return 0;
}