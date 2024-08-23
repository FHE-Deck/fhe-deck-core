 
#include <iostream>

/*
#include "rlwe_hom_acc_scheme.h"
#include "rlwe_hom_acc_scheme_gen.h"  
#include <chrono>
#include <thread>


using namespace fhe_deck;

void extract_and_key_switch_test(int test_num, TFHENamedParams param_name){
    std::cout << "============ extract_and_key_switch_test =============" << std::endl;

    TFHEKeyGenerator params(param_name); 
    params.generate_bootstapping_keys();

    int t = 3;
    // Make an RLWE encryption of something. 
    long* m = params.boot_sk->rlwe_gadget_sk.gadget_param.rlwe_param->init_zero_poly(); 
    RLWECT r_ct; 
    // Extract the LWE ciphertext 
    long *ext_ct = params.boot_sk->extract_lwe_sk.param->init_ct();
    long dec_ext_ct; 
    std::cerr << "Test extract extract_lwe_from_rlwe: "  ;
    bool test_extract = true;
    for(int i = 0; i < test_num; ++i){
        m[0] = i % t;
        RLWECT r_ct = params.boot_sk->rlwe_gadget_sk.sk.scale_and_encrypt(m, t);
        params.boot_pk->extract_lwe_from_rlwe(ext_ct, &r_ct);
        dec_ext_ct = params.boot_sk->extract_lwe_sk.decrypt(ext_ct, t);
        if(dec_ext_ct != m[0]){
            std::cerr << "Fail at i: " << i << std::endl; 
            std::cerr << "Expected: " << m[0] << std::endl; 
            std::cerr << "dec_ext_ct: " << dec_ext_ct << std::endl; 
            test_extract = false;
            break;
        }
    }
    if(test_extract){
        std::cerr << "OK" << std::endl;
    }
 
 
    // Key switch the extracted ciphertext 
    long *lwe_c = params.boot_pk->lwe_gadget_param.lwe_param->init_ct(); 
    long out, exp;
    bool test_key_switch = true;


    std::cerr << "Test lwe_to_lwe_key_switch: ";
    for(int i = 0; i < test_num; ++i){ 
        exp = i % t;
        params.boot_sk->extract_lwe_sk.scale_and_encrypt(ext_ct, exp, t);
        params.boot_pk->lwe_to_lwe_key_switch(lwe_c, ext_ct);
        out = params.boot_sk->lwe_gadget_sk.lwe.decrypt(lwe_c, t);
        if(out != exp){
            std::cerr << "Fail at i: " << i << std::endl; 
            std::cerr << "exp: " << exp << std::endl; 
            std::cerr << "out: " << dec_ext_ct << std::endl; 
            test_key_switch = false;
            break;
        }
    }
    if(test_key_switch){
        std::cerr << "OK" << std::endl;
    }


    test_key_switch = true;
    std::cerr << "Test lwe_to_lwe_key_switch_partial_lazy: ";
    for(int i = 0; i < test_num; ++i){ 
        exp = i % t;
        params.boot_sk->extract_lwe_sk.scale_and_encrypt(ext_ct, exp, t);
        params.boot_pk->lwe_to_lwe_key_switch_partial_lazy(lwe_c, ext_ct);
        out = params.boot_sk->lwe_gadget_sk.lwe.decrypt(lwe_c, t);
        if(out != exp){
            std::cerr << "Fail at i: " << i << std::endl; 
            std::cerr << "exp: " << exp << std::endl; 
            std::cerr << "out: " << dec_ext_ct << std::endl; 
            test_key_switch = false;
            break;
        }
    }
    if(test_key_switch){
        std::cerr << "OK" << std::endl;
    }


    test_key_switch = true;
    std::cerr << "Test lwe_to_lwe_key_switch_lazy: ";
    for(int i = 0; i < test_num; ++i){ 
        exp = i % t;
        params.boot_sk->extract_lwe_sk.scale_and_encrypt(ext_ct, exp, t);
        params.boot_pk->lwe_to_lwe_key_switch_lazy(lwe_c, ext_ct);
        out = params.boot_sk->lwe_gadget_sk.lwe.decrypt(lwe_c, t);
        if(out != exp){
            std::cerr << "Fail at i: " << i << std::endl; 
            std::cerr << "exp: " << exp << std::endl; 
            std::cerr << "out: " << dec_ext_ct << std::endl; 
            test_key_switch = false;
            break;
        }
    }
    if(test_key_switch){
        std::cerr << "OK" << std::endl;
    }
  
    delete[] m;
    delete[] lwe_c;
    delete[] ext_ct;

}


void blind_rotation_test(int test_num, TFHENamedParams param_name, GadgetMulMode mode){
    std::cout << "============ blind_rotation_test =============" << std::endl; 
    if(mode == deter){
        std::cout << "Mode: Deterministic" << std::endl;
    }else{
        std::cout << "Mode: Sanitization" << std::endl;
    }
    TFHEKeyGenerator params(param_name); 
    params.generate_bootstapping_keys();
    int t = 4; 

    // Create LWE of zero - with zero stddev error
    // Note this must be the LWE with modulus mathing 2*N
    long* ct = params.boot_pk->lwe_par->init_ct();
    params.boot_sk->lwe_sk.encrypt(ct, 0);
    long e = params.boot_sk->lwe_sk.error(ct, 0);
    ct[0] = Utils::integer_mod_form(ct[0] - e, params.boot_sk->lwe_sk.param->Q); 
    

    // Create a rotation polynomial for the (not realy) identity function
    // Initiate these messages
    long* acc = RotationPoly::rot_identity(t, params.boot_pk->rlwe_gadget_param.rlwe_param->N, params.boot_pk->rlwe_gadget_param.rlwe_param->Q);
    long* acc_rotation = params.boot_pk->rlwe_gadget_param.rlwe_param->init_poly();
    bool br_test = true;
    RLWECT out_ct(params.boot_pk->rlwe_gadget_param.rlwe_param);
    long* out = params.boot_pk->rlwe_gadget_param.rlwe_param->init_poly();
    std::cerr << "Test: " << 0 ;
    long phase;
    for(int i = 0; i < test_num; ++i){
        std::cerr << "\rTest: " << i ;
        // Iterate the phase for the LWE ciphertext
        ct[0] = ct[0]+1 % params.boot_sk->lwe_sk.param->Q; 
        phase = params.boot_sk->lwe_sk.phase(ct); 
        // Blind rotate the LWE ciphertext
        params.boot_pk->blind_rotate(&out_ct, ct, acc, mode);
        // Compare with negacyclic rotations of acc_msg - rotation by i
        Utils::negacyclic_rotate_poly(acc_rotation, acc, params.boot_pk->rlwe_gadget_param.rlwe_param->N, phase);
        Utils::array_rounding(acc_rotation, acc_rotation, params.boot_pk->rlwe_gadget_param.rlwe_param->N, params.boot_pk->rlwe_gadget_param.rlwe_param->Q, t);
        params.boot_sk->rlwe_gadget_sk.sk.decrypt(out, &out_ct, t); 
        Utils::array_mod_form(acc_rotation, acc_rotation, params.boot_pk->rlwe_gadget_param.rlwe_param->N, t);
        Utils::array_mod_form(out, out, params.boot_pk->rlwe_gadget_param.rlwe_param->N, t);
        if(!Utils::is_eq_poly(acc_rotation, out, params.boot_pk->rlwe_gadget_param.rlwe_param->N)){
            std::cout << "blind_rotation_test: Fail at i: " << i <<  std::endl;
            std::cout << "acc: " << Utils::to_string(acc, params.boot_pk->rlwe_gadget_param.rlwe_param->N) << std::endl;
            std::cout << "out: " << Utils::to_string(out, params.boot_pk->rlwe_gadget_param.rlwe_param->N) << std::endl;
            std::cout << "acc_rotation: " << Utils::to_string(acc_rotation, params.boot_pk->rlwe_gadget_param.rlwe_param->N) << std::endl;
            std::cout << "phase: " << phase << std::endl;
            br_test = false;
            break;
        }
    }
    std::cerr << "\rTest: " << test_num << std::endl;
    if(br_test){
        std::cout << "blind_rotation_test: OK" << std::endl;
    } 
 
    delete[] ct; 
    delete[] out;
    delete[] acc; 
    delete[] acc_rotation;
}

 


void bootstrap_test(int test_num,  TFHENamedParams param_name, GadgetMulMode mode, bool is_amortized = false){
    std::cout << "============ bootstrap_test =============" << std::endl; 
    if(is_amortized){
        std::cout << "Amortization: ON" << std::endl;
    }else{
        std::cout << "Amortization: OFF" << std::endl;
    } 
    if(mode == deter){
        std::cout << "Mode: Deterministic" << std::endl;
    }else{
        std::cout << "Mode: Sanitization" << std::endl;
    }
    TFHEKeyGenerator params(param_name); 
    params.generate_bootstapping_keys();
    int t = 4; 
     
    long* ct = params.boot_pk->extract_lwe_par->init_ct();  
    long* ct_out = params.boot_pk->extract_lwe_par->init_ct(); 
 
    // Create a rotation polynomial for the (not realy) identity function
    // Initiate these messages
    long* acc = RotationPoly::rot_identity(t, params.boot_pk->rlwe_gadget_param.rlwe_param->N, params.boot_pk->rlwe_gadget_param.rlwe_param->Q);  
    long* acc_rot = new long[params.boot_pk->rlwe_gadget_param.rlwe_param->N];
    bool br_test = true;  
    long out;
    long phase;
    long exp;

    std::chrono::high_resolution_clock::time_point start, end; 
    float single_psi_loop_time = 0.0;

    // This is used only for testing amortized bootstrapping
    PlaintextEncoding encoding(partial_domain, t, params.boot_pk->rlwe_gadget_param.rlwe_param->Q); 
    std::vector<LWECT> out_vec;
    std::vector<RotationPoly> acc_vec;
    // NOTE: Actually I'm hardcoding the rotation polynomial at this point
    acc_vec.push_back(RotationPoly(acc,  params.boot_pk->rlwe_gadget_param.rlwe_param->N, encoding)); 
    acc_vec.push_back(RotationPoly(acc, params.boot_pk->rlwe_gadget_param.rlwe_param->N, encoding)); 
   
    
    long double mod_switching_scale = ((long double)params.boot_pk->rlwe_gadget_param.rlwe_param->N * 2)/((long double)params.boot_sk->extract_lwe_sk.param->Q);

    std::cerr << "Test: " << 0 ;
    for(int i = 0; i < test_num; ++i){   
        std::cerr << "\rTest: " << i << std::endl;
        params.boot_sk->extract_lwe_sk.scale_and_encrypt(ct, i % t, t);  
        phase = params.boot_sk->extract_lwe_sk.phase(ct);   
        //std::cerr << "Test: " << i << ", phase: " << phase << std::endl;
        // TODO: May the problem be sort of here? I Also ge some weird phase here.... Its zero... Funny.
        // We supposed to modulus switch here
        //phase = (params.boot_pk->rlwe_gadget_param.rlwe_param->N * 2 * phase)/params.boot_sk->extract_lwe.param->Q; 
        phase = roundl(mod_switching_scale * (long double)phase);
        //std::cerr << "phase again: " << phase << std::endl;
        
        Utils::negacyclic_rotate_poly(acc_rot, acc, params.boot_pk->rlwe_gadget_param.rlwe_param->N, phase);  
        
        if(is_amortized){
            start = std::chrono::high_resolution_clock::now();  
            out_vec = params.boot_pk->bootstrap(acc_vec, ct, mode, encoding); 
            end = std::chrono::high_resolution_clock::now();  
            single_psi_loop_time  += std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();  
            for(LWECT ele: out_vec){ 
                out = params.boot_sk->extract_lwe_sk.decrypt(ele.ct, t); 
                exp =  (long)round((t * (double)acc_rot[0])/params.boot_pk->rlwe_gadget_param.rlwe_param->Q);
                exp = Utils::integer_mod_form(exp, t);  
                if(!(out == exp)){
                    std::cout << "rot_identity_test: Fail" << std::endl;
                    std::cout << "i: " << i << std::endl;
                    std::cout << "out: " << out << std::endl; 
                    std::cout << "exp: " << exp << std::endl;
                    std::cout << "phase: " << phase << std::endl; 
                    br_test = false;
                    break;
                }
            }
        }else{ 
            start = std::chrono::high_resolution_clock::now(); 
            params.boot_pk->bootstrap(ct_out, acc, ct, mode); 
            end = std::chrono::high_resolution_clock::now(); 
            single_psi_loop_time  += std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();
            
            out = params.boot_sk->extract_lwe_sk.decrypt(ct_out, t);  
            exp =  (long)round((t * (double)acc_rot[0])/params.boot_pk->rlwe_gadget_param.rlwe_param->Q);
            exp = Utils::integer_mod_form(exp, t);  
            if(!(out == exp)){
                std::cout << "rot_identity_test: Fail" << std::endl;
                std::cout << "i: " << i << std::endl;
                std::cout << "out: " << out << std::endl; 
                std::cout << "exp: " << exp << std::endl;
                std::cout << "phase: " << phase << std::endl;
                //std::cout << "ct: " << utils::to_string(ct, params.boot_sk->extract_lwe.lwe_par.n+1) << std::endl; 
                br_test = false;
                break;
            }
        } 
    }
    std::cerr << "\rTest: " << test_num << std::endl;
    if(br_test){
        std::cout << "rot_identity_test: OK" << std::endl;
    } 
    std::cout << "Time for Single Bootstrap: " << single_psi_loop_time/test_num/1000 << " [s]" << std::endl;
 
    delete[] ct;
    delete[] ct_out;
    delete[] acc;
    delete[] acc_rot; 
}

 

 

void functional_bootstrap_test(int test_num, TFHENamedParams param_name,  GadgetMulMode mode, bool is_amortized = false){
    std::cout << "============ functional_bootstrap_test =============" << std::endl; 
    if(is_amortized){
        std::cout << "Amortization: ON" << std::endl;
    }else{
        std::cout << "Amortization: OFF" << std::endl;
    } 
    if(mode == deter){
        std::cout << "Mode: Deterministic" << std::endl;
    }else{
        std::cout << "Mode: Sanitization" << std::endl;
    }
    TFHEKeyGenerator params(param_name); 
    params.generate_bootstapping_keys();
    int t = 5; 
     
    LWESK *gadget_lwe = &params.boot_sk->lwe_gadget_sk.lwe;  
    LWESK *small_lwe = &params.boot_sk->lwe_sk;  
    LWESK *extract_lwe = &params.boot_sk->extract_lwe_sk;
    RLWESK *br_lwe = &params.boot_sk->rlwe_gadget_sk.sk; 
    
    long* ct = params.boot_pk->extract_lwe_par->init_ct();  
    long* ct_out = params.boot_pk->extract_lwe_par->init_ct(); 
  
    // Create a rotation polynomial for the (not realy) identity function
    // Initiate these messages
    long* acc = RotationPoly::rot_identity(t, params.boot_pk->rlwe_gadget_param.rlwe_param->N, params.boot_pk->rlwe_gadget_param.rlwe_param->Q);  
    bool br_test = true;  
    long out; 
    long exp; 
    long* lwe_c = params.boot_pk->lwe_gadget_param.lwe_param->init_ct();


    // This is used only for testing amortized bootstrapping 
    PlaintextEncoding encoding(full_domain, t, params.boot_pk->rlwe_gadget_param.rlwe_param->Q); 
    std::vector<LWECT> out_vec;
    std::vector<RotationPoly> acc_vec;
    acc_vec.push_back(RotationPoly(acc, params.boot_pk->rlwe_gadget_param.rlwe_param->N, encoding)); 
    acc_vec.push_back(RotationPoly(acc, params.boot_pk->rlwe_gadget_param.rlwe_param->N, encoding)); 

    std::chrono::high_resolution_clock::time_point start, end; 
    float single_psi_loop_time = 0.0;

    std::cerr << "Test: " << 0 ;
    for(int i = 0; i < test_num; ++i){    
        std::cerr << "\rTest: " << i ;
        params.boot_sk->extract_lwe_sk.scale_and_encrypt(ct, i % t, t);   
        // Lets get the phase of this ciphertexts - rotate the accumulator according to this phase, and see what we get    
        if(is_amortized){
            start = std::chrono::high_resolution_clock::now();  
            out_vec = params.boot_pk->functional_bootstrap(acc_vec, ct, mode, encoding); 
            end = std::chrono::high_resolution_clock::now();  
            single_psi_loop_time  += std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();  
            for(LWECT ele: out_vec){ 
                out = params.boot_sk->extract_lwe_sk.decrypt(ele.ct, t); 
                exp = Utils::integer_mod_form(i, t); 
                if(!(out == exp)){
                    std::cout << "rot_identity_test: Fail" << std::endl;
                    std::cout << "i: " << i << std::endl;
                    std::cout << "out: " << out << std::endl; 
                    std::cout << "exp: " << exp << std::endl; 
                    br_test = false;
                    break;
                }
            }
        }else{
            start = std::chrono::high_resolution_clock::now();   
            params.boot_pk->functional_bootstrap(ct_out, acc, ct, mode, t);   
            end = std::chrono::high_resolution_clock::now(); 
            single_psi_loop_time  += std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count(); 
            out = params.boot_sk->extract_lwe_sk.decrypt(ct_out, t);   
            exp = Utils::integer_mod_form(i, t); 
            if(!(out == exp)){
                std::cout << "rot_identity_test: Fail" << std::endl;
                std::cout << "i: " << i << std::endl;
                std::cout << "out: " << out << std::endl; 
                std::cout << "exp: " << exp << std::endl; 
                br_test = false;
                break;
            }
        } 
    }
    std::cerr << "\rTest: " << test_num << std::endl;
    if(br_test){
        std::cout << "rot_identity_test: OK" << std::endl;
    }  
    std::cout << "Time for Single Functional Bootstrap: " << single_psi_loop_time/test_num/1000 << " [s]" << std::endl;
 
    delete[] ct;
    delete[] ct_out;
    delete[] acc; 
    delete[] lwe_c; 

}





void functional_bootstrap_initial_test(int test_num, TFHENamedParams param_name,  GadgetMulMode mode, bool is_amortized = false){
    std::cout << "============ functional_bootstrap_initial_test =============" << std::endl; 
    if(is_amortized){
        std::cout << "Amortization: ON" << std::endl;
    }else{
        std::cout << "Amortization: OFF" << std::endl;
    } 
    if(mode == deter){
        std::cout << "Mode: Deterministic" << std::endl;
    }else{
        std::cout << "Mode: Sanitization" << std::endl;
    }
    TFHEKeyGenerator params(param_name);
    // FBTFHE_named_param_generator params(FBTFHE_small_test); 
    params.generate_bootstapping_keys();
    int t = 5; 
       
    long* ct_out = params.boot_pk->extract_lwe_par->init_ct(); 
  
    // Create a rotation polynomial for the (not realy) identity function
    // Initiate these messages
    long* acc = RotationPoly::rot_identity(t, params.boot_pk->rlwe_gadget_param.rlwe_param->N, params.boot_pk->rlwe_gadget_param.rlwe_param->Q);
    long* acc_rot = new long[params.boot_pk->rlwe_gadget_param.rlwe_param->N];
    
    bool br_test = true;  
    long out;
    long phase;
    long exp;
    long exp_rot;
    long m;
    long error;
    long* lwe_c = params.boot_pk->lwe_gadget_param.lwe_param->init_ct();
    double scale = (double)params.boot_pk->rlwe_gadget_param.rlwe_param->N/t;


    // This is used only for testing amortized bootstrapping
    PlaintextEncoding encoding(full_domain, t, params.boot_pk->rlwe_gadget_param.rlwe_param->Q); 
    std::vector<LWECT> out_vec;
    std::vector<RotationPoly> acc_vec;
    acc_vec.push_back(RotationPoly(acc, params.boot_pk->rlwe_gadget_param.rlwe_param->N, encoding)); 
    acc_vec.push_back(RotationPoly(acc, params.boot_pk->rlwe_gadget_param.rlwe_param->N, encoding)); 
 
    std::cerr << "Test: " << 0 ;
    for(int i = 0; i < test_num; ++i){   
        std::cerr << "\rTest: " << i ;
        params.boot_sk->lwe_sk.encrypt(lwe_c, scale * (i % t));
        m = params.boot_sk->lwe_sk.decrypt(lwe_c, t);
        phase = params.boot_sk->lwe_sk.phase(lwe_c);
        error = params.boot_sk->lwe_sk.error(lwe_c, i * (double)params.boot_pk->lwe_par->Q/t);
        Utils::negacyclic_rotate_poly(acc_rot, acc, params.boot_pk->rlwe_gadget_param.rlwe_param->N, phase);  
        exp_rot =  (long)round((t * (double)acc_rot[0])/params.boot_pk->rlwe_gadget_param.rlwe_param->Q);

        if(is_amortized){ 
            out_vec = params.boot_pk->functional_bootstrap_initial(acc_vec, lwe_c, mode, encoding);   
            for(LWECT ele: out_vec){ 
                out = params.boot_sk->extract_lwe_sk.decrypt(ele.ct, t); 
                exp = Utils::integer_mod_form(i, t); 
                if(!(out == exp)){
                    std::cout << "rot_identity_test: Fail" << std::endl;
                    std::cout << "i: " << i << std::endl;
                    std::cout << "out: " << out << std::endl; 
                    std::cout << "exp: " << exp << std::endl; 
                    std::cout << "exp_rot: " << exp_rot << std::endl;
                    br_test = false;
                    break;
                }
            }
        }else{
            params.boot_pk->functional_bootstrap_initial(ct_out, acc, lwe_c, mode);  
            out = params.boot_sk->extract_lwe_sk.decrypt(ct_out, t);   
            exp = Utils::integer_mod_form(i, t); 
            if(!(out == exp)){
                std::cout << "rot_identity_test: Fail" << std::endl;
                std::cout << "i: " << i << std::endl;
                std::cout << "out: " << out << std::endl; 
                std::cout << "exp: " << exp << std::endl;
                std::cout << "m: " << m << std::endl;  
                std::cout << "phase: " << phase << std::endl;  
                std::cout << "error: " << error << std::endl;
                std::cout << "exp_rot: " << exp_rot << std::endl;
                //std::cout << "acc: " << utils::to_string(acc, params.boot->rlwe_gadget_par.param.N) << std::endl;
                br_test = false;
                break;
            }
        } 
    }
    std::cerr << "Test: " << test_num << std::endl;
    if(br_test){
        std::cout << "rot_identity_test: OK" << std::endl;
    } 
}

 

*/

int main(){
 

    //extract_and_key_switch_test(10, tfhe_11_NTT);
    //extract_and_key_switch_test(10, tfhe_11_NTT_amortized);
    //extract_and_key_switch_test(10, tfhe_12_NTT_amortized);

    //blind_rotation_test(10, tfhe_11_NTT, deter); 
    //blind_rotation_test(10, tfhe_11_NTT_amortized, deter); 
    //blind_rotation_test(10, tfhe_12_NTT_amortized, deter); 
    
    //bootstrap_test(10, tfhe_11_B, deter); 

    //bootstrap_test(10, tfhe_11_NTT, deter); 
   
    //functional_bootstrap_initial_test(5, tfhe_11_NTT, simul);  

    //functional_bootstrap_test(5, tfhe_11_NTT, deter, false); 


    std::cout << "--------------- Testing Amortized Bootstrapping --------------------" << std::endl;
  
    //bootstrap_test(5, tfhe_11_NTT_amortized, deter, false); 
    //bootstrap_test(5, tfhe_12_NTT_amortized, deter, false); 


    //functional_bootstrap_test(5, tfhe_11_NTT_amortized, deter, true); 
    //functional_bootstrap_initial_test(5, tfhe_11_NTT_amortized, deter, false); 
 
}
