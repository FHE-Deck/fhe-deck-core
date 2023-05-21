 
#include "../include/rlwe_hom_acc_scheme.h"
#include "../include/rlwe_hom_acc_scheme_gen.h"  
#include <chrono>
#include <thread>

void extract_and_key_switch_test(){
    std::cout << "============ extract_and_key_switch_test =============" << std::endl;

    rlwe_hom_acc_scheme_named_param_generator params(rlwe_hom_acc_scheme_small_test);
    std::cout << "params.generate_bootstapping_keys();" << std::endl;
    params.generate_bootstapping_keys();

    int t = 3;
    // Make an RLWE encryption of something.
    std::cout << "long* m = params.boot_sk.rlwe_gadget.gadget_param.param.init_zero_poly();" << std::endl;
    long* m = params.boot_sk->rlwe_gadget.gadget_param.param.init_zero_poly();
    m[0] = 1;
    std::cout << "rlwe_ct r_ct = params.boot_sk.rlwe_gadget.sk.scale_and_encrypt(m, t);" << std::endl;
    rlwe_ct r_ct = params.boot_sk->rlwe_gadget.sk.scale_and_encrypt(m, t);

    // Extract the LWE ciphertext 
    long *ext_ct = params.boot_sk->extract_lwe.lwe_par.init_ct();
    std::cout << "r_ct: " << r_ct.to_string() << std::endl;
    std::cout << "params.boot.extract_lwe_from_rlwe(ext_ct, r_ct);" << std::endl;
    params.boot->extract_lwe_from_rlwe(ext_ct, &r_ct);
 
    std::cout << "ext_ct: " << utils::to_string(ext_ct, params.boot->rlwe_gadget_par.param.N+1) << std::endl;
 
    // Check if extraction works (if it doesn't work at this point then need to test better)  
    std::cout << "Decrypting the extracted ciphertext:" << std::endl;
    long dec_ext_ct = params.boot_sk->extract_lwe.decrypt(ext_ct, t);
    std::cout << "dec_ext_ct with extract_lwe: " << dec_ext_ct << std::endl;

    dec_ext_ct  = ext_ct[0]; 
    for(int i = 1; i < params.boot->rlwe_gadget_par.param.N+1; ++i){ 
        dec_ext_ct -= ext_ct[i] * params.boot_sk->rlwe_gadget.sk.s[i-1];
        dec_ext_ct = dec_ext_ct % params.boot->rlwe_gadget_par.param.Q; 
    } 
    dec_ext_ct = round(((double)t/params.boot->rlwe_gadget_par.param.Q) * dec_ext_ct);
    dec_ext_ct = utils::integer_mod_form(dec_ext_ct, t); 
 
    std::cout << "dec_ext_ct: " << dec_ext_ct << std::endl;
    // Key switch the extracted ciphertext

    long *lwe_c = params.boot->lwe_gadget_par.lwe_par.init_ct();
    params.boot->lwe_to_lwe_key_switch_lazy(lwe_c, ext_ct);
    // Decrypt the key switched ciphertexts
    long out = params.boot_sk->lwe_gadget.lwe.decrypt(lwe_c, t);
    std::cout << "out: " << out << std::endl;


    // Encrypt something with params.boot_sk.extract_lwe, and check if key switch is OK.
    long* ext_ct_fresh = params.boot_sk->extract_lwe.scale_and_encrypt(m[0], t);
    params.boot->lwe_to_lwe_key_switch_lazy(lwe_c, ext_ct_fresh);
    // Decrypt the key switched ciphertexts
    out = params.boot_sk->lwe_gadget.lwe.decrypt(lwe_c, t);
    std::cout << "out fresh: " << out << std::endl;


}


void blind_rotation_test(int test_num, rlwe_hom_acc_scheme_named_param param_name, gadget_mul_mode mode){
    std::cout << "============ blind_rotation_test =============" << std::endl; 
    rlwe_hom_acc_scheme_named_param_generator params(param_name);
    std::cout << "params.generate_bootstapping_keys();" << std::endl;
    params.generate_bootstapping_keys();
    int t = 4; 

    // Create LWE of zero - with zero stddev error
    // Note this must be the LWE with modulus mathing 2*N
    long* ct = params.boot->lwe_par.init_ct();
    params.boot_sk->lwe.encrypt(ct, 0);
    long e = params.boot_sk->lwe.error(ct, 0);
    ct[0] = utils::integer_mod_form(ct[0] - e, params.boot_sk->lwe.lwe_par.Q); 
    

    // Create a rotation polynomial for the (not realy) identity function
    // Initiate these messages
    long* acc = rotation_poly::rot_identity(t, params.boot->rlwe_gadget_par.param.N, params.boot->rlwe_gadget_par.param.Q);
    long* acc_rotation = params.boot->rlwe_gadget_par.param.init_poly();
    bool br_test = true;
    rlwe_ct out_ct(&params.boot->rlwe_gadget_par.param);
    long* out = params.boot->rlwe_gadget_par.param.init_poly();
    std::cout << "Start Test: " << std::endl;
    long phase;
    for(int i = 0; i < test_num; ++i){
        // Iterate the phase for the LWE ciphertext
        ct[0] = ct[0]+1 % params.boot_sk->lwe.lwe_par.Q; 
        phase = params.boot_sk->lwe.phase(ct); 
        // Blind rotate the LWE ciphertext
        params.boot->blind_rotate(&out_ct, ct, acc, mode);
        // Compare with negacyclic rotations of acc_msg - rotation by i
        utils::negacyclic_rotate_poly(acc_rotation, acc, params.boot->rlwe_gadget_par.param.N, phase);
        utils::array_rounding(acc_rotation, acc_rotation, params.boot->rlwe_gadget_par.param.N, params.boot->rlwe_gadget_par.param.Q, t);
        params.boot_sk->rlwe_gadget.sk.decrypt(out, &out_ct, t); 
        utils::array_mod_form(acc_rotation, acc_rotation, params.boot->rlwe_gadget_par.param.N, t);
        utils::array_mod_form(out, out, params.boot->rlwe_gadget_par.param.N, t);
        if(!utils::is_eq_poly(acc_rotation, out, params.boot->rlwe_gadget_par.param.N)){
            std::cout << "blind_rotation_test: Fail at i: " << i <<  std::endl;
            std::cout << "acc: " << utils::to_string(acc, params.boot->rlwe_gadget_par.param.N) << std::endl;
            std::cout << "out: " << utils::to_string(out, params.boot->rlwe_gadget_par.param.N) << std::endl;
            std::cout << "acc_rotation: " << utils::to_string(acc_rotation, params.boot->rlwe_gadget_par.param.N) << std::endl;
            std::cout << "phase: " << phase << std::endl;
            br_test = false;
            break;
        }
    }
    if(br_test){
        std::cout << "blind_rotation_test: OK" << std::endl;
    } 

    delete params.boot;
    delete params.boot_sk;
    delete[] ct; 
    delete[] out;
    delete[] acc; 
    delete[] acc_rotation;
}

 


void bootstrap_test(int test_num,  rlwe_hom_acc_scheme_named_param param_name, gadget_mul_mode mode, bool is_amortized = false){
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
    rlwe_hom_acc_scheme_named_param_generator params(param_name); 
    params.generate_bootstapping_keys();
    int t = 4; 
     
    long* ct = params.boot->extract_lwe_par.init_ct();  
    long* ct_out = params.boot->extract_lwe_par.init_ct(); 
 
    // Create a rotation polynomial for the (not realy) identity function
    // Initiate these messages
    long* acc = rotation_poly::rot_identity(t, params.boot->rlwe_gadget_par.param.N, params.boot->rlwe_gadget_par.param.Q);  
    long* acc_rot = new long[params.boot->rlwe_gadget_par.param.N];
    bool br_test = true;  
    long out;
    long phase;
    long exp;

    std::chrono::high_resolution_clock::time_point start, end; 
    float single_psi_loop_time = 0.0;

    // This is used only for testing amortized bootstrapping
    std::vector<lwe_ct> out_vec;
    std::vector<rotation_poly> acc_vec;
    acc_vec.push_back(rotation_poly(acc, t, params.boot->rlwe_gadget_par.param.N, params.boot->rlwe_gadget_par.param.Q));
    acc_vec[0].flip_scale();
    acc_vec.push_back(rotation_poly(acc, t, params.boot->rlwe_gadget_par.param.N, params.boot->rlwe_gadget_par.param.Q));
    acc_vec[1].flip_scale();
   

    std::cout << "------ rot_identity_test start" << std::endl;
    for(int i = 0; i < test_num; ++i){   
         
        params.boot_sk->extract_lwe.scale_and_encrypt(ct, i % t, t);  
        phase = params.boot_sk->extract_lwe.phase(ct);   
        phase = (params.boot->rlwe_gadget_par.param.N * 2 * phase)/params.boot_sk->extract_lwe.lwe_par.Q; 
        
        utils::negacyclic_rotate_poly(acc_rot, acc, params.boot->rlwe_gadget_par.param.N, phase);  
        
        if(is_amortized){
            start = std::chrono::high_resolution_clock::now();  
            out_vec = params.boot->bootstrap(acc_vec, ct, mode, t); 
            end = std::chrono::high_resolution_clock::now();  
            single_psi_loop_time  += std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();  
            for(lwe_ct ele: out_vec){ 
                out = params.boot_sk->extract_lwe.decrypt(ele.ct, t); 
                exp =  (long)round((t * (double)acc_rot[0])/params.boot->rlwe_gadget_par.param.Q);
                exp = utils::integer_mod_form(exp, t);  
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
            params.boot->bootstrap(ct_out, acc, ct, mode); 
            end = std::chrono::high_resolution_clock::now(); 
            single_psi_loop_time  += std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();
            
            out = params.boot_sk->extract_lwe.decrypt(ct_out, t); 
            exp =  (long)round((t * (double)acc_rot[0])/params.boot->rlwe_gadget_par.param.Q);
            exp = utils::integer_mod_form(exp, t); 
            //std::cout << "out: " << out << std::endl;
            //std::cout << "exp: " << exp << std::endl;
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
    if(br_test){
        std::cout << "rot_identity_test: OK" << std::endl;
    } 
    std::cout << "Time for Single Bootstrap: " << single_psi_loop_time/test_num/1000 << " [s]" << std::endl;

    delete params.boot;
    delete params.boot_sk;

    delete[] ct;
    delete[] ct_out;
    delete[] acc;
    delete[] acc_rot; 
}

 

 

void functional_bootstrap_test(int test_num, rlwe_hom_acc_scheme_named_param param_name,  gadget_mul_mode mode, bool is_amortized = false){
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
    rlwe_hom_acc_scheme_named_param_generator params(param_name); 
    params.generate_bootstapping_keys();
    int t = 5; 
     
    lwe_sk *gadget_lwe = &params.boot_sk->lwe_gadget.lwe;  
    lwe_sk *small_lwe = &params.boot_sk->lwe;  
    lwe_sk *extract_lwe = &params.boot_sk->extract_lwe;
    rlwe_sk *br_lwe = &params.boot_sk->rlwe_gadget.sk; 
    
    long* ct = params.boot->extract_lwe_par.init_ct();  
    long* ct_out = params.boot->extract_lwe_par.init_ct(); 
 
    std::cout << "------ rot_identity_test start" << std::endl;
    // Create a rotation polynomial for the (not realy) identity function
    // Initiate these messages
    long* acc = rotation_poly::rot_identity(t, params.boot->rlwe_gadget_par.param.N, params.boot->rlwe_gadget_par.param.Q);  
    bool br_test = true;  
    long out; 
    long exp; 
    long* lwe_c = params.boot->lwe_gadget_par.lwe_par.init_ct();


    // This is used only for testing amortized bootstrapping
    std::vector<lwe_ct> out_vec;
    std::vector<rotation_poly> acc_vec;
    acc_vec.push_back(rotation_poly(acc, t, params.boot->rlwe_gadget_par.param.N, params.boot->rlwe_gadget_par.param.Q));
    acc_vec[0].flip_scale();
    acc_vec.push_back(rotation_poly(acc, t, params.boot->rlwe_gadget_par.param.N, params.boot->rlwe_gadget_par.param.Q));
    acc_vec[1].flip_scale();

    std::chrono::high_resolution_clock::time_point start, end; 
    float single_psi_loop_time = 0.0;

    for(int i = 0; i < test_num; ++i){    
        params.boot_sk->extract_lwe.scale_and_encrypt(ct, i % t, t);   
        // Lets get the phase of this ciphertexts - rotate the accumulator according to this phase, and see what we get    
        if(is_amortized){
            start = std::chrono::high_resolution_clock::now();  
            out_vec = params.boot->functional_bootstrap(acc_vec, ct, mode, t); 
            end = std::chrono::high_resolution_clock::now();  
            single_psi_loop_time  += std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();  
            for(lwe_ct ele: out_vec){ 
                out = params.boot_sk->extract_lwe.decrypt(ele.ct, t); 
                exp = utils::integer_mod_form(i, t); 
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
            params.boot->functional_bootstrap(ct_out, acc, ct, mode, t);   
            end = std::chrono::high_resolution_clock::now(); 
            single_psi_loop_time  += std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count(); 
            out = params.boot_sk->extract_lwe.decrypt(ct_out, t);   
            exp = utils::integer_mod_form(i, t); 
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
    if(br_test){
        std::cout << "rot_identity_test: OK" << std::endl;
    }  
    std::cout << "Time for Single Functional Bootstrap: " << single_psi_loop_time/test_num/1000 << " [s]" << std::endl;

    delete params.boot;
    delete params.boot_sk;
    delete[] ct;
    delete[] ct_out;
    delete[] acc; 
    delete[] lwe_c; 

}





void functional_bootstrap_initial_test(int test_num, rlwe_hom_acc_scheme_named_param param_name,  gadget_mul_mode mode, bool is_amortized = false){
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
    rlwe_hom_acc_scheme_named_param_generator params(param_name);
    // FBTFHE_named_param_generator params(FBTFHE_small_test); 
    params.generate_bootstapping_keys();
    int t = 5; 
       
    long* ct_out = params.boot->extract_lwe_par.init_ct(); 
 
    std::cout << "------ rot_identity_test start" << std::endl;
    // Create a rotation polynomial for the (not realy) identity function
    // Initiate these messages
    long* acc = rotation_poly::rot_identity(t, params.boot->rlwe_gadget_par.param.N, params.boot->rlwe_gadget_par.param.Q);
    long* acc_rot = new long[params.boot->rlwe_gadget_par.param.N];
    
    bool br_test = true;  
    long out;
    long phase;
    long exp;
    long exp_rot;
    long m;
    long error;
    long* lwe_c = params.boot->lwe_gadget_par.lwe_par.init_ct();
    double scale = (double)params.boot->rlwe_gadget_par.param.N/t;


    // This is used only for testing amortized bootstrapping
    std::vector<lwe_ct> out_vec;
    std::vector<rotation_poly> acc_vec;
    acc_vec.push_back(rotation_poly(acc, t, params.boot->rlwe_gadget_par.param.N, params.boot->rlwe_gadget_par.param.Q));
    acc_vec[0].flip_scale();
    acc_vec.push_back(rotation_poly(acc, t, params.boot->rlwe_gadget_par.param.N, params.boot->rlwe_gadget_par.param.Q));
    acc_vec[1].flip_scale();
 

    for(int i = 0; i < test_num; ++i){   
        params.boot_sk->lwe.encrypt(lwe_c, scale * (i % t));
        m = params.boot_sk->lwe.decrypt(lwe_c, t);
        phase = params.boot_sk->lwe.phase(lwe_c);
        error = params.boot_sk->lwe.error(lwe_c, i * (double)params.boot->lwe_par.Q/t);
        utils::negacyclic_rotate_poly(acc_rot, acc, params.boot->rlwe_gadget_par.param.N, phase);  
        exp_rot =  (long)round((t * (double)acc_rot[0])/params.boot->rlwe_gadget_par.param.Q);

        if(is_amortized){ 
            out_vec = params.boot->functional_bootstrap_initial(acc_vec, lwe_c, mode, t);   
            for(lwe_ct ele: out_vec){ 
                out = params.boot_sk->extract_lwe.decrypt(ele.ct, t); 
                exp = utils::integer_mod_form(i, t); 
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
            params.boot->functional_bootstrap_initial(ct_out, acc, lwe_c, mode);  
            out = params.boot_sk->extract_lwe.decrypt(ct_out, t);   
            exp = utils::integer_mod_form(i, t); 
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
    if(br_test){
        std::cout << "rot_identity_test: OK" << std::endl;
    } 
}

 


int main(){
 
    blind_rotation_test(10, rlwe_hom_acc_scheme_C_11_B, simul); 

    bootstrap_test(5, rlwe_hom_acc_scheme_C_11_NTT, simul); 
 
    functional_bootstrap_initial_test(5, rlwe_hom_acc_scheme_C_11_NTT, simul);  

    functional_bootstrap_test(5, rlwe_hom_acc_scheme_C_11_NTT, simul); 


    std::cout << "--------------- Testing Amortized Bootstrapping --------------------" << std::endl;
  
    bootstrap_test(2, rlwe_hom_acc_scheme_C_11_NTT_amortized, deter, true); 
    functional_bootstrap_test(5, rlwe_hom_acc_scheme_C_11_NTT_amortized, deter, true); 
    functional_bootstrap_initial_test(5, rlwe_hom_acc_scheme_C_11_NTT_amortized, deter, true); 
 
}