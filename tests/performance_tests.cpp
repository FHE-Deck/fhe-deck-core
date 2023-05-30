 

#include <iostream>
#include "../include/ntrunium.h" 
#include "../include/ntrunium_gen.h" 
#include "../include/lwe.h"
#include "../include/lwe_param.h"
#include "../include/ntru.h"
#include "../include/ntru_param.h"
#include "../include/rlwe_hom_acc_scheme.h"
#include "../include/rlwe_hom_acc_scheme_gen.h"
#include <NTL/ZZX.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_p.h>
#include <random>
#include <cmath>
#include <chrono>

 
void ntrunium_performance_test(ntrunium_named_param param_name, int test_num){
    std::cout << "=== ntrunium_performance_test: Testing Timings and Errors === " << std::endl;
 
    ntrunium_named_param_generator param_gen(param_name);
    std::cout << "- Generate Bootstrapping Keys... " << std::endl;
    param_gen.generate_bootstapping_keys(); 

    std::cout << "- Initialize accumulator... " << std::endl;
    // Create a accumulator that encrypts zero (with respect to ntru_par_pot) 
    long* acc_msg = param_gen.ntru_par_P.init_zero_poly();
    ntru_ct acc = param_gen.ntru_P.kdm_encrypt(acc_msg);
    ntru_ct out_acc(param_gen.ntru_g_par.param);  
    ntru_ct out_acc_prime_mod(param_gen.ntru_g_par.param);  
    
    // The LWE ciphertexts to blind rotate
    long lwe_msg = 0;
    long *lwe_ct = param_gen.lwe_par_small.init_ct();
    long *lwe_ct_post_ks = param_gen.lwe_g.lwe_g_par.lwe_par.init_ct();
    long *lwe_ct_new = param_gen.lwe_par_small.init_ct();
  
    // Time
    std::chrono::high_resolution_clock::time_point start, end; 
    float sum_time_blind_rotation = 0;
    float ntru_mod_switch_time  = 0;
    float key_switching_time = 0;
    float lwe_mod_switch_time = 0;

    // Errors
    long* phase_error = param_gen.ntru_g_par.param.init_poly();
    long* ntru_error_measure = new long[test_num];
    long* lwe_error_measure = new long[test_num];

    // Testing Loop
    std::cout << "- Start Test... " << std::endl;
    for(int i = 0; i < test_num; ++i){ 
        // New LWE ct of zero 
        param_gen.lwe_small.encrypt(lwe_ct, lwe_msg); 
   
        // Blind Rotate 
        start = std::chrono::high_resolution_clock::now(); 
        out_acc = param_gen.boot->blind_rotate(&acc, lwe_ct);  
        end = std::chrono::high_resolution_clock::now(); 
        sum_time_blind_rotation += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();   
  
        // Modulus switch from ntru_par_pot, to ntru_par
        start = std::chrono::high_resolution_clock::now(); 
        out_acc_prime_mod = out_acc.mod_switch(param_gen.ntru.param);
        end = std::chrono::high_resolution_clock::now();
        ntru_mod_switch_time  += std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();  

        // TODO At this point its possible to phase, which should give us the error only and check the error 
        param_gen.ntru.phase(phase_error, &out_acc_prime_mod); 
        ntru_error_measure[i] = utils::integer_signed_form(phase_error[0], param_gen.ntru.param.Q); 
 
        // Key Switching from ntru_par, to lwe_par.
        start = std::chrono::high_resolution_clock::now();
        param_gen.boot->ntru_to_lwe_key_switch(lwe_ct_post_ks, &out_acc_prime_mod);
        end = std::chrono::high_resolution_clock::now();
        key_switching_time += std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();  
 
        // Modulus Switching from lwe_par, to lwe_par_small
        start = std::chrono::high_resolution_clock::now();
        param_gen.lwe_g.lwe_g_par.lwe_par.switch_modulus(lwe_ct_new, lwe_ct_post_ks, param_gen.lwe_par_small);
        end = std::chrono::high_resolution_clock::now();
        lwe_mod_switch_time += std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();  

        lwe_error_measure[i] = utils::integer_signed_form(param_gen.lwe_small.error(lwe_ct_new, 0), param_gen.lwe_par_small.Q); 
    } 

    double avg_time_blind_rotation = sum_time_blind_rotation/ test_num ;
    std::cout << "Avg Time Blind Rotations: " << avg_time_blind_rotation << " [ms], " << avg_time_blind_rotation/1000 << " [s]" << std::endl;
 
    double avg_ntru_mod_switch_time = ntru_mod_switch_time/ test_num;
    std::cout << "Avg Time NTRU Mod Switch [ms]: " << avg_ntru_mod_switch_time << std::endl;
 
    double avg_key_switching_time = key_switching_time/ test_num;
    std::cout << "Avg Time Key Switching [ms]: " << avg_key_switching_time << " [ms], " << avg_key_switching_time/1000 << " [s]" << std::endl;
 
    double avg_lwe_mod_switch_time =  lwe_mod_switch_time/  test_num;
    std::cout << "Avg Time LWE Mod Switch [ms]: " << avg_lwe_mod_switch_time << std::endl;

    double overal_time = avg_time_blind_rotation + avg_ntru_mod_switch_time + avg_key_switching_time + avg_lwe_mod_switch_time;
    std::cout << "Avg Time Bootstrapping [ms]: " << overal_time << std::endl;
      
    delete(lwe_ct);
    delete(lwe_ct_post_ks);
    delete(lwe_ct_new);

    delete(phase_error);
    delete(ntru_error_measure); 
    delete(lwe_error_measure);
  
}





void rlwe_performance_test(rlwe_hom_acc_scheme_named_param param_name, int test_num, gadget_mul_mode mode){
    std::cout << "=== rlwe_performance_test: Testing Timings and Errors === " << std::endl;
 
    rlwe_hom_acc_scheme_named_param_generator params(param_name);
    std::cout << "params.generate_bootstapping_keys();" << std::endl;
    params.generate_bootstapping_keys();

    int t = 3;
    std::cout << "- Initialize accumulator... " << std::endl;
    // Create a accumulator that encrypts zero (with respect to ntru_par_pot) 
    long* ct = params.boot->lwe_par.init_ct();
    params.boot_sk->lwe.encrypt(ct, 0);
    long e = params.boot_sk->lwe.error(ct, 0);
    ct[0] = (ct[0] - e) % params.boot_sk->lwe.lwe_par.Q; 
 
    // Initiate these messages
    long* acc = rotation_poly::rot_identity(t, params.boot->rlwe_gadget_par.param.N, params.boot->rlwe_gadget_par.param.Q);
    rlwe_ct out_ct(params.boot->rlwe_gadget_par.param);

    // Time
    std::chrono::high_resolution_clock::time_point start, end; 
    float sum_time_blind_rotation = 0; 
    float key_switching_time_lazy = 0; 
    float key_switching_time_partial_lazy = 0; 
    float key_switching_time = 0; 
 
    long *ext_ct = params.boot_sk->extract_lwe.lwe_par.init_ct();
    long *lwe_c = params.boot->lwe_gadget_par.lwe_par.init_ct();

    // Testing Loop
    std::cout << "- Start Test... " << std::endl;
    for(int i = 0; i < test_num; ++i){  
   
        // Blind Rotate 
        start = std::chrono::high_resolution_clock::now(); 
        params.boot->blind_rotate(&out_ct, ct, acc, mode);
        end = std::chrono::high_resolution_clock::now(); 
        sum_time_blind_rotation += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();   
      
        // Lazy Key Switching from ntru_par, to lwe_par.
        start = std::chrono::high_resolution_clock::now();
        params.boot->lwe_to_lwe_key_switch_lazy(lwe_c, ext_ct);
        end = std::chrono::high_resolution_clock::now();
        key_switching_time_lazy += std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();  


        // Partial Lazy Key Switching from ntru_par, to lwe_par.
        start = std::chrono::high_resolution_clock::now();
        params.boot->lwe_to_lwe_key_switch_partial_lazy(lwe_c, ext_ct);
        end = std::chrono::high_resolution_clock::now();
        key_switching_time_partial_lazy += std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count(); 

        // Key Switching from ntru_par, to lwe_par.
        start = std::chrono::high_resolution_clock::now();
        params.boot->lwe_to_lwe_key_switch(lwe_c, ext_ct);
        end = std::chrono::high_resolution_clock::now();
        key_switching_time += std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();  
   
    } 

    double avg_time_blind_rotation = sum_time_blind_rotation/ test_num ;
    std::cout << "Avg Time Blind Rotations: " << avg_time_blind_rotation << " [ms], " << avg_time_blind_rotation/1000 << " [s]" << std::endl;
  
    double avg_key_switching_time_lazy = key_switching_time_lazy/ test_num;
    std::cout << "Avg Time Lazy Key Switching [ms]: " << avg_key_switching_time_lazy << " [ms], " << avg_key_switching_time_lazy/1000 << " [s]" << std::endl;

    double avg_key_switching_time_partial_lazy = key_switching_time_partial_lazy/ test_num;
    std::cout << "Avg Time Partially Lazy Key Switching [ms]: " << avg_key_switching_time_partial_lazy << " [ms], " << avg_key_switching_time_partial_lazy/1000 << " [s]" << std::endl;

    double avg_key_switching_time = key_switching_time/ test_num;
    std::cout << "Avg Time Key Switching [ms]: " << avg_key_switching_time << " [ms], " << avg_key_switching_time/1000 << " [s]" << std::endl;
  
    double overal_time = avg_time_blind_rotation + avg_key_switching_time;
    std::cout << "Avg Time Bootstrapping [ms]: " << overal_time << std::endl;
       
}
 
int main(){
    std::cout << "Testing Performance" << std::endl;
  
    //ntrunium_performance_test(ntrunium_C_11_B, 10);

    rlwe_performance_test(rlwe_hom_acc_scheme_C_11_NTT, 10, simul);

}