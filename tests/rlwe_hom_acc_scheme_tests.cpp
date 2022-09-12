 
#include "../include/rlwe_hom_acc_scheme.h"
#include "../include/rlwe_hom_acc_scheme_gen.h"  
#include <chrono>
#include <thread>

void extract_and_key_switch_test(){
    std::cout << "============ extract_and_key_switch_test =============" << std::endl;

    rlwe_hom_acc_scheme_named_param_generator params(rlwe_hom_acc_scheme_small_test);
    std::cout << "params.generate_bootstapping_keys();" << std::endl;
    params.generate_bootstapping_keys();

    int t = 7;
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
    params.boot->lwe_to_lwe_key_switch(lwe_c, ext_ct);
    // Decrypt the key switched ciphertexts
    long out = params.boot_sk->lwe_gadget.lwe.decrypt(lwe_c, t);
    std::cout << "out: " << out << std::endl;


    // Encrypt something with params.boot_sk.extract_lwe, and check if key switch is OK.
    long* ext_ct_fresh = params.boot_sk->extract_lwe.scale_and_encrypt(m[0], t);
    params.boot->lwe_to_lwe_key_switch(lwe_c, ext_ct_fresh);
    // Decrypt the key switched ciphertexts
    out = params.boot_sk->lwe_gadget.lwe.decrypt(lwe_c, t);
    std::cout << "out fresh: " << out << std::endl;


}

void test_negacyclic_rotate_poly(){

    int N = 16;
    long* poly = new long[N];
    for(int i = 0; i < N; ++i){
        poly[i] = i;
    }
    std::cout << "poly:    " << utils::to_string(poly, N) << std::endl ;

    long* rot_poly = new long[N];

    // Note that rot may be in [0, 2*N)!
    int rot = 16 + 4;
    utils::negacyclic_rotate_poly(rot_poly, poly, N, rot);
    std::cout << "rot_poly: " << utils::to_string(rot_poly, N) << std::endl ;


}

void blind_rotation_test(int test_num, gadget_mul_mode mode){
    std::cout << "============ blind_rotation_test =============" << std::endl; 
    rlwe_hom_acc_scheme_named_param_generator params(rlwe_hom_acc_scheme_C_11_B);
    std::cout << "params.generate_bootstapping_keys();" << std::endl;
    params.generate_bootstapping_keys();
    int t = 7; 

    // Create LWE of zero - with zero stddev error
    // Note this must be the LWE with modulus mathing 2*N
    long* ct = params.boot->lwe_par.init_ct();
    params.boot_sk->lwe.encrypt(ct, 0);
    long e = params.boot_sk->lwe.error(ct, 0);
    ct[0] = (ct[0] - e) % params.boot_sk->lwe.lwe_par.Q; 

    // Create a rotation polynomial for the (not realy) identity function
    // Initiate these messages
    long* acc = rlwe_hom_acc_scheme::rot_identity(t, params.boot->rlwe_gadget_par.param.N, params.boot->rlwe_gadget_par.param.Q);
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
        if(!utils::is_eq_poly(acc_rotation, out, params.boot->rlwe_gadget_par.param.N)){
            std::cout << "blind_rotation_test: Fail" << std::endl;
            std::cout << "acc: " << utils::to_string(acc, params.boot->rlwe_gadget_par.param.N) << std::endl;
            std::cout << "out: " << utils::to_string(out, params.boot->rlwe_gadget_par.param.N) << std::endl;
            std::cout << "acc_rotation: " << utils::to_string(acc_rotation, params.boot->rlwe_gadget_par.param.N) << std::endl;
            br_test = false;
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


void bootstrap_test(int test_num, gadget_mul_mode mode){
    std::cout << "============ blind_rotation_test =============" << std::endl; 
    rlwe_hom_acc_scheme_named_param_generator params(rlwe_hom_acc_scheme_C_11_B);
    //rlwe_hom_acc_scheme_named_param_generator params(rlwe_hom_acc_scheme_small_test); 
    params.generate_bootstapping_keys();
    int t = 8; 
     
 
    long* ct = params.boot->extract_lwe_par.init_ct();  
    long* ct_out = params.boot->extract_lwe_par.init_ct(); 
 
    std::cout << "------ rot_identity_test start" << std::endl;
    // Create a rotation polynomial for the (not realy) identity function
    // Initiate these messages
    long* acc = rlwe_hom_acc_scheme::rot_identity(t, params.boot->rlwe_gadget_par.param.N, params.boot->rlwe_gadget_par.param.Q);  
    long* acc_rot = new long[params.boot->rlwe_gadget_par.param.N];
    bool br_test = true;  
    long out;
    long phase;
    long exp;

    std::chrono::high_resolution_clock::time_point start, end; 
    float single_psi_loop_time = 0.0;

    long* lwe_c = params.boot->lwe_gadget_par.lwe_par.init_ct();
    for(int i = 0; i < test_num; ++i){  
        params.boot_sk->extract_lwe.scale_and_encrypt(ct, 0, t);  
        phase = params.boot_sk->extract_lwe.phase(ct);   
        phase = (params.boot->rlwe_gadget_par.param.N * 2 * phase)/params.boot_sk->extract_lwe.lwe_par.Q; 
        // Rotating by phase doesn't make sense!!! I would need to rescale this to a 2N modulus instead of running this stuff as is!!!
        utils::negacyclic_rotate_poly(acc_rot, acc, params.boot->rlwe_gadget_par.param.N, phase);

        // Lets do key switching here
        params.boot->lwe_to_lwe_key_switch(lwe_c, ct);
        // Decrypt the key switched ciphertexts  
        // Lets get the phase of this ciphertexts - rotate the accumulator according to this phase, and see what we get 

        start = std::chrono::high_resolution_clock::now(); 
        params.boot->bootstrap(ct_out, acc, ct, mode); 
        end = std::chrono::high_resolution_clock::now(); 
        single_psi_loop_time  += std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();


        out = params.boot_sk->extract_lwe.decrypt(ct_out, t); 
        exp =  (long)round((t * (double)acc_rot[0])/params.boot->rlwe_gadget_par.param.Q) % t;
        if(!(out == exp)){
            std::cout << "rot_identity_test: Fail" << std::endl;
            std::cout << "i: " << i << std::endl;
            std::cout << "out: " << out << std::endl; 
            std::cout << "exp: " << exp << std::endl;
            std::cout << "phase: " << phase << std::endl;
            std::cout << "acc: " << utils::to_string(acc, params.boot->rlwe_gadget_par.param.N) << std::endl;  
            std::cout << "acc_rot: " << utils::to_string(acc_rot, params.boot->rlwe_gadget_par.param.N) << std::endl;  
            br_test = false;
            break;
        }
    }
    if(br_test){
        std::cout << "rot_identity_test: OK" << std::endl;
    } 
    std::cout << "Time for Single Bootstrap: " << single_psi_loop_time/test_num/1000 << " [s]" << std::endl;

    std::cout << "-------- msb_test  start" << std::endl;
    // NOTE: This test may fail, in corner cases (like zero or t-1.)
    bool msb_test = true;   
    long* acc_msb = rlwe_hom_acc_scheme::rot_msb(t, params.boot->rlwe_gadget_par.param.N, params.boot->rlwe_gadget_par.param.Q); 
    long m;
    single_psi_loop_time = 0.0;
    for(int i = 0; i < test_num; ++i){  
       m = params.boot_sk->lwe.rand.uniform(t); 
        if(m < t/2){
            exp = 1;
        }else{
            exp = t-1;
        }  
        params.boot_sk->extract_lwe.scale_and_encrypt(ct, m, t); 
        // NOTE: Need to shift the ciphertext a little bit, because e.g. for m=0, the error may be negative
        // Consequently, the sign will be wrong - because of negacyclicity its difficult to set the rotation polynomial appropriately, because of that.
        ct[0] += round((double)params.boot_sk->extract_lwe.lwe_par.Q / (2 * t));
        phase = params.boot_sk->extract_lwe.phase(ct);   
        // Do I modulus switch the phase correctly?
        phase = (params.boot->rlwe_gadget_par.param.N * 2 * phase)/params.boot_sk->extract_lwe.lwe_par.Q; 
        // Rotating by phase doesn't make sense!!! I would need to rescale this to a 2N modulus instead of running this stuff as is!!!
        utils::negacyclic_rotate_poly(acc_rot, acc_msb, params.boot->rlwe_gadget_par.param.N, phase); 


        start = std::chrono::high_resolution_clock::now(); 
        params.boot->bootstrap(ct_out, acc_msb, ct, mode);  
        end = std::chrono::high_resolution_clock::now(); 
        single_psi_loop_time  += std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();

        out = params.boot_sk->extract_lwe.decrypt(ct_out, t); 
          
        if(!(out == exp)){
            std::cout << "msb_test: Fail" << std::endl;
            std::cout << "i: " << i << std::endl;
            std::cout << "out: " << out << std::endl; 
            std::cout << "exp: " << exp << std::endl;  
            std::cout << "phase: " << phase << std::endl;
            std::cout << "acc_msb: " << utils::to_string(acc_msb, params.boot->rlwe_gadget_par.param.N) << std::endl;  
            std::cout << "acc_rot: " << utils::to_string(acc_msb, params.boot->rlwe_gadget_par.param.N) << std::endl;  
            msb_test = false;
            break;
        }
    }
    if(msb_test){
        std::cout << "msb_test: OK" << std::endl;
    }  
    std::cout << "Time for Single Bootstrap: " << single_psi_loop_time/test_num/1000 << " [s]" << std::endl;

    delete params.boot;
    delete params.boot_sk;
    delete[] ct;
    delete[] ct_out;
    delete[] acc;
    delete[] acc_rot;
    delete[] lwe_c;
    delete[] acc_msb;
}




void functional_bootstrap_test(int test_num, gadget_mul_mode mode){
    std::cout << "============ functional_bootstrap_test =============" << std::endl; 
    rlwe_hom_acc_scheme_named_param_generator params(rlwe_hom_acc_scheme_C_11_B);
    // rlwe_hom_acc_scheme_named_param_generator params(rlwe_hom_acc_scheme_small_test); 
    params.generate_bootstapping_keys();
    int t = 8; 
     
    lwe_sk *gadget_lwe = &params.boot_sk->lwe_gadget.lwe;  
    lwe_sk *small_lwe = &params.boot_sk->lwe;  
    lwe_sk *extract_lwe = &params.boot_sk->extract_lwe;
    rlwe_sk *br_lwe = &params.boot_sk->rlwe_gadget.sk; 
    

    long* ct = params.boot->extract_lwe_par.init_ct();  
    long* ct_out = params.boot->extract_lwe_par.init_ct(); 
 
    std::cout << "------ rot_identity_test start" << std::endl;
    // Create a rotation polynomial for the (not realy) identity function
    // Initiate these messages
    long* acc = rlwe_hom_acc_scheme::rot_identity(t, params.boot->rlwe_gadget_par.param.N, params.boot->rlwe_gadget_par.param.Q);  
    bool br_test = true;  
    long out;
    long phase;
    long exp;
    long m;
    long* lwe_c = params.boot->lwe_gadget_par.lwe_par.init_ct();

    std::chrono::high_resolution_clock::time_point start, end; 
    float single_psi_loop_time = 0.0;

    for(int i = 0; i < test_num; ++i){   
        m = i; 
        params.boot_sk->extract_lwe.scale_and_encrypt(ct, m, t);   
        // Lets get the phase of this ciphertexts - rotate the accumulator according to this phase, and see what we get   
        start = std::chrono::high_resolution_clock::now();  
        params.boot->functional_bootstrap(ct_out, acc, ct, mode, t);  
        end = std::chrono::high_resolution_clock::now(); 
        single_psi_loop_time  += std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();

        out = params.boot_sk->extract_lwe.decrypt(ct_out, t);   
        exp = i; 
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





void functional_bootstrap_initial_test(int test_num, gadget_mul_mode mode){
    std::cout << "============ functional_bootstrap_initial_test =============" << std::endl; 
    rlwe_hom_acc_scheme_named_param_generator params(rlwe_hom_acc_scheme_C_11_B);
    // FBTFHE_named_param_generator params(FBTFHE_small_test); 
    params.generate_bootstapping_keys();
    int t = 8; 
      
    long* ct = params.boot->extract_lwe_par.init_ct();  
    long* ct_out = params.boot->extract_lwe_par.init_ct(); 
 
    std::cout << "------ rot_identity_test start" << std::endl;
    // Create a rotation polynomial for the (not realy) identity function
    // Initiate these messages
    long* acc = rlwe_hom_acc_scheme::rot_identity(t, params.boot->rlwe_gadget_par.param.N, params.boot->rlwe_gadget_par.param.Q);  
    bool br_test = true;  
    long out;
    long phase;
    long exp;
    long m;
    long* lwe_c = params.boot->lwe_gadget_par.lwe_par.init_ct();
    for(int i = 0; i < test_num; ++i){  
        //m = params.boot_sk.lwe.rand.uniform(t); 
        m = i; 
        // params.boot_sk.extract_lwe.scale_and_encrypt(ct, m, t);    
        params.boot_sk->scale_and_encrypt_initial_lwe(ct, m, t);
        // Lets get the phase of this ciphertexts - rotate the accumulator according to this phase, and see what we get 
        //params.boot.functional_bootstrap_testing(ct_out, acc, ct, mode, t, gadget_lwe, small_lwe, extract_lwe, br_lwe); 
        params.boot->functional_bootstrap_initial(ct_out, acc, ct, mode); 
        out = params.boot_sk->extract_lwe.decrypt(ct_out, t);   
        exp = i; 
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
    if(br_test){
        std::cout << "rot_identity_test: OK" << std::endl;
    } 
}




void functional_bootstrap_initial_polynomial_eval_test(int test_num, gadget_mul_mode mode){
    std::cout << "============ functional_bootstrap_initial_polynomial_eval_test =============" << std::endl; 
    rlwe_hom_acc_scheme_named_param_generator params(rlwe_hom_acc_scheme_C_11_B);
    // rlwe_hom_acc_scheme_named_param_generator params(rlwe_hom_acc_scheme_small_test); 
    params.generate_bootstapping_keys();
    int t = 83; 
      
    long* ct = params.boot->extract_lwe_par.init_ct();  
    long* ct_out = params.boot->extract_lwe_par.init_ct(); 
 
    std::cout << "------ rot_uni_poly start" << std::endl;
    // Create a rotation polynomial for the (not realy) identity function
    // Initiate these messages
    // Test polynomial evaluation
    int size_of_poly = 10000; 
    int *test_poly = new int[size_of_poly];
    for(int i = 0; i < size_of_poly; ++i){
        test_poly[i] = params.boot->rlwe_gadget_par.param.rand.uniform(t); 
    } 
    long *poly_eval_acc = rlwe_hom_acc_scheme::rot_uni_poly(test_poly, size_of_poly, t, params.boot->rlwe_gadget_par.param.N, params.boot->rlwe_gadget_par.param.Q); 
    bool br_test = true;  
    long out;
    long phase;
    long exp;
    long m;
    long* lwe_c = params.boot->lwe_gadget_par.lwe_par.init_ct();
    for(int i = 0; i < test_num; ++i){  
        //m = params.boot_sk.lwe.rand.uniform(t); 
        m = i; 
        // params.boot_sk.extract_lwe.scale_and_encrypt(ct, m, t);    
        params.boot_sk->scale_and_encrypt_initial_lwe(ct, m, t);
        phase = params.boot_sk->lwe.phase(ct);
        // Lets get the phase of this ciphertexts - rotate the accumulator according to this phase, and see what we get  
        params.boot->functional_bootstrap_initial(ct_out, poly_eval_acc, ct, mode); 
        out = params.boot_sk->extract_lwe.decrypt(ct_out, t);   

        // Evaluate the polynomial:
        exp = utils::eval_poly_mod(i, test_poly, size_of_poly, t); 
        if(!(out == exp)){
            std::cout << "rot_uni_poly: Fail" << std::endl;
            std::cout << "i: " << i << std::endl;
            std::cout << "out: " << out << std::endl; 
            std::cout << "exp: " << exp << std::endl;
            std::cout << "phase: " << phase << std::endl;  
            std::cout << "poly_eval_acc: "  << utils::to_string(poly_eval_acc, params.boot->rlwe_gadget_par.param.N) << std::endl;
            br_test = false;
            break;
        }
    }
    if(br_test){
        std::cout << "rot_uni_poly: OK" << std::endl;
    } 
}

void exec_boot(rlwe_hom_acc_scheme_named_param_generator* params, int j, long* lwe_sum, long **ct_out, long **poly_eval_acc, long **ct, gadget_mul_mode mode){
    std::cout << "Start j: " << j << std::endl;
    params->boot->functional_bootstrap_initial(ct_out[j], poly_eval_acc[j], ct[j], mode);    
    for(int k = 0; k < params->boot->extract_lwe_par.n+1; ++k){
            lwe_sum[k] = lwe_sum[k] + ct_out[j][k];
    } 
    std::cout << "End j: " << j << std::endl;
}


void functional_bootstrap_PSI_test(int test_num){
    std::cout << "============ functional_bootstrap_PSI_test =============" << std::endl; 
    rlwe_hom_acc_scheme_named_param_generator params(rlwe_hom_acc_scheme_C_11_B); 
    params.generate_bootstapping_keys();

    // Primes: 43, 47, 53, 59, 61, 67, 71, 73, 79, 83 
    int t = 21; 
    int num_of_primes = 10;
    int* t_table = new int[num_of_primes];
    t_table[0] = 43;
    t_table[1] = 47;
    t_table[2] = 53;
    t_table[3] = 59;
    t_table[4] = 61;
    t_table[5] = 67;
    t_table[6] = 71;
    t_table[7] = 73;
    t_table[8] = 79;
    t_table[9] = 83;
    long prime_prod = 1;
    for(int i = 0; i < num_of_primes; ++i){
        prime_prod *= t_table[i];
    }
 
    std::cout << "------ Start test" << std::endl;
    // Create a rotation polynomial for the (not realy) identity function
    // Initiate these messages
    // Test polynomial evaluation
    int size_of_poly = 10000; 
    std::cout << "Set polynomials..." << std::endl;
    int** test_poly = new int*[num_of_primes];
    for(int i = 0; i < num_of_primes; ++i){
        test_poly[i] = new int[size_of_poly];
        for(int j = 0; j < size_of_poly; ++j){
            test_poly[i][j] = params.boot->rlwe_gadget_par.param.rand.uniform(t_table[i]); 
        } 
    }
    std::cout << "Set rotation polynomials" << std::endl;
    long** poly_eval_acc = new long*[num_of_primes];
    for(int i = 0; i < num_of_primes; ++i){
        poly_eval_acc[i] = rlwe_hom_acc_scheme::rot_is_zero_of_poly(test_poly[i], size_of_poly, t_table[i], params.boot->rlwe_gadget_par.param.N, params.boot->rlwe_gadget_par.param.Q, t); 
    }
    long *poly_is_zero_acc = rlwe_hom_acc_scheme::rot_is_zero(t, params.boot->rlwe_gadget_par.param.N, params.boot->rlwe_gadget_par.param.Q); 


    bool br_test = true;  
    long out; 
    long exp;
    long m;
    long* m_crt = new long[num_of_primes];
    long* lwe_c = params.boot->lwe_gadget_par.lwe_par.init_ct();
    long* lwe_sum = params.boot->extract_lwe_par.init_ct();
    for(int i = 0; i < params.boot->extract_lwe_par.n+1; ++i){
        lwe_sum[i] = 0;
    }

    // Setup and encrypt all messages here 
    long** ct = new long*[num_of_primes];
    long** ct_out = new long*[num_of_primes];
    for(int i = 0; i < num_of_primes; ++i){   
        // CRT Decompose m everything in a loop
        // The first iteration sets the lwe_sum ciphertext, the other in the loop will add their results to this ciphertext 
        ct[i] = params.boot->extract_lwe_par.init_ct(); 
        
        ct_out[i] = params.boot->extract_lwe_par.init_ct(); 
    }
     
    //params.boot_sk.extract_lwe.encrypt(ct, 0); 
    long* ct_out_final = params.boot->extract_lwe_par.init_ct(); 

    // Time
    std::chrono::high_resolution_clock::time_point start, end; 
    float single_psi_loop_time = 0.0;
 
    std::cout << "Test loop..." << std::endl;
    // Declate threads
    int num_threads = std::thread::hardware_concurrency();
    std::cout << "num_threads: " << num_threads << std::endl;
    std::thread* boot_execs = new std::thread[num_of_primes];
      
    for(int i = 0; i < test_num; ++i){  
        // m should actually be from the product of all primes
        m = params.boot_sk->lwe.rand.uniform(prime_prod);   
        // CRT Decompose m everything in a loop
        for(int j = 0; j < num_of_primes; ++j){ 
            m_crt[i] = m % t_table[i];
            params.boot_sk->scale_and_encrypt_initial_lwe(ct[j], m_crt[j], t_table[j]); 
        }
   
        start = std::chrono::high_resolution_clock::now(); 
        // TODO: Run this in parallel
        for(int j = 0; j < num_of_primes; ++j){ 
            // Bootstrap each CRT decomposition sequential 
            // Bootstrap in parallel
            boot_execs[j] = std::thread(exec_boot, &params, j, lwe_sum, ct_out, poly_eval_acc, ct, signed_decomp);
        }   
        // Wait here until the parallel functions finish 
         
        for(int j =0; j < num_of_primes; ++j){
            boot_execs[j].join();
        } 
        std::cout << "Add all together..." << std::endl;  
        // Modulus reduce lwe_sum
        for(int k = 0; k < params.boot->extract_lwe_par.n+1; ++k){
                lwe_sum[k]  = lwe_sum[k] % params.boot->extract_lwe_par.Q;
        }   
        // Final bootstrap to check if the result is 0 or not 
        params.boot->bootstrap(ct_out_final, poly_is_zero_acc, lwe_sum, simul);

        end = std::chrono::high_resolution_clock::now(); 
        single_psi_loop_time  += std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();

        // Decrypt the result (Yeah - but with what scale?)
        out = params.boot_sk->extract_lwe.decrypt(ct_out_final, t);  
  
        // Evaluate all the polynomials, if all are zero, then output 1, if any is non-zero then output 0
        exp = 1;
        for(int j = 0; j < num_of_primes; ++j){
            long eval = utils::eval_poly_mod(m_crt[j], test_poly[j], size_of_poly, t_table[j]); 
            if(0 != eval){
                exp = 0;  
            }
        }  
        if(!(out == exp)){
            std::cout << "functional_bootstrap_PSI_test: Fail" << std::endl;
            std::cout << "i: " << i << std::endl;
            std::cout << "out: " << out << std::endl; 
            std::cout << "exp: " << exp << std::endl;   
            br_test = false;
            break;
        }
    }
    if(br_test){
        std::cout << "functional_bootstrap_PSI_test: OK" << std::endl;
    } 

    std::cout << "Time for Evaluating the PSI circuit: " << single_psi_loop_time/test_num/1000 << " [s]" << std::endl;

}


void functional_bootstrap_PSI_smarter_test(int test_num){
    std::cout << "============ functional_bootstrap_PSI_test =============" << std::endl; 
    rlwe_hom_acc_scheme_named_param_generator params(rlwe_hom_acc_scheme_C_11_B);
    // rlwe_hom_acc_scheme_named_param_generator params(rlwe_hom_acc_scheme_small_test); 
    params.generate_bootstapping_keys();

    // Primes: 43, 47, 53, 59, 61, 67, 71, 73, 79, 83 
    int t = 21; 
    int num_of_primes = 6 ;
    int* t_table = new int[num_of_primes];
    t_table[0] = 43;
    t_table[1] = 47;
    t_table[2] = 53;
    t_table[3] = 59;
    t_table[4] = 61;
    t_table[5] = 67;
    t_table[6] = 71;
    t_table[7] = 73;
    t_table[8] = 79;
    t_table[9] = 83;
    long prime_prod = 1;
    for(int i = 0; i < num_of_primes; ++i){
        prime_prod *= t_table[i];
    }
 
    std::cout << "------ Start test" << std::endl;
    // Create a rotation polynomial for the (not realy) identity function
    // Initiate these messages
    // Test polynomial evaluation
    int size_of_poly = 10000; 
    std::cout << "Set polynomials..." << std::endl;
    int** test_poly = new int*[num_of_primes];
    for(int i = 0; i < num_of_primes; ++i){
        test_poly[i] = new int[size_of_poly];
        for(int j = 0; j < size_of_poly; ++j){
            test_poly[i][j] = params.boot->rlwe_gadget_par.param.rand.uniform(t_table[i]); 
        } 
    }
    std::cout << "Set rotation polynomials" << std::endl;
    long** poly_eval_acc = new long*[num_of_primes];
    rlwe_ct* rot_acc = new rlwe_ct[num_of_primes];
    for(int i = 0; i < num_of_primes; ++i){
        poly_eval_acc[i] = rlwe_hom_acc_scheme::rot_is_zero_of_poly(test_poly[i], size_of_poly, t_table[i], params.boot->rlwe_gadget_par.param.N, params.boot->rlwe_gadget_par.param.Q, t); 
 
        rot_acc[i] = params.boot_sk->rlwe_gadget.sk.encrypt(poly_eval_acc[i]);
    } 
    long *poly_is_zero_acc = rlwe_hom_acc_scheme::rot_is_zero(t, params.boot->rlwe_gadget_par.param.N, params.boot->rlwe_gadget_par.param.Q); 
    rlwe_ct rot_sum;
    rlwe_ct rotated_ct;

    bool br_test = true;  
    long out; 
    long exp;
    long m;
    long* m_crt = new long[num_of_primes];
    long* lwe_c = params.boot->lwe_gadget_par.lwe_par.init_ct();
    long* lwe_sum = params.boot->extract_lwe_par.init_ct();
    for(int i = 0; i < params.boot->extract_lwe_par.n+1; ++i){
        lwe_sum[i] = 0;
    }

    // Setup and encrypt all messages here 
    long** ct = new long*[num_of_primes];
    long** ct_out = new long*[num_of_primes];
    for(int i = 0; i < num_of_primes; ++i){   
        // CRT Decompose m everything in a loop
        // The first iteration sets the lwe_sum ciphertext, the other in the loop will add their results to this ciphertext 
        ct[i] = params.boot->extract_lwe_par.init_ct(); 
        
        ct_out[i] = params.boot->extract_lwe_par.init_ct(); 
    }
      
    long* ct_out_final = params.boot->extract_lwe_par.init_ct(); 

    // Time
    std::chrono::high_resolution_clock::time_point start, end; 
    float single_psi_loop_time = 0.0;
    double single_loop_decryption_time = 0.0;
 
    std::cout << "Test loop..." << std::endl; 
      
    for(int i = 0; i < test_num; ++i){  
        // m should actually be from the product of all primes
        m = params.boot_sk->lwe.rand.uniform(prime_prod);   
        // CRT Decompose m everything in a loop
        for(int j = 0; j < num_of_primes; ++j){ 
            m_crt[j] = m % t_table[j]; 
            m_crt[j] = (long)round(m_crt[j] * params.boot->bk->gadget_param.param.N / (double)t_table[j]);
        }

        start = std::chrono::high_resolution_clock::now();  
        // Do the negacyclic rotation... 
        rot_acc[0].negacyclic_rotate(&rot_sum, m_crt[0]);  
        for(int j = 1; j < num_of_primes; ++j){    
            rot_acc[j].negacyclic_rotate(&rotated_ct, m_crt[j]); 
            rot_sum.add(&rot_sum, &rotated_ct);
        }     
         
        params.boot->extract_lwe_from_rlwe(lwe_sum, &rot_sum); 
        // Final bootstrap to check if the result is 0 or not 
        params.boot->bootstrap(ct_out_final, poly_is_zero_acc, lwe_sum, simul);

        end = std::chrono::high_resolution_clock::now(); 
        single_psi_loop_time  += std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();

        // Decrypt the result (Yeah - but with what scale?)
        start = std::chrono::high_resolution_clock::now(); 
        out = params.boot_sk->extract_lwe.decrypt(ct_out_final, t);  
        end = std::chrono::high_resolution_clock::now(); 
        single_loop_decryption_time  += std::chrono::duration_cast<std::chrono::microseconds>( end - start ).count();
  
        // Evaluate all the polynomials, if all are zero, then output 1, if any is non-zero then output 0
        exp = 1;
        for(int j = 0; j < num_of_primes; ++j){
            long eval = utils::eval_poly_mod(m_crt[j], test_poly[j], size_of_poly, t_table[j]); 
            if(0 != eval){
                exp = 0;  
            }
        }  
        if(!(out == exp)){
            std::cout << "functional_bootstrap_PSI_test: Fail" << std::endl;
            std::cout << "i: " << i << std::endl;
            std::cout << "out: " << out << std::endl; 
            std::cout << "exp: " << exp << std::endl;   
            br_test = false;
            break;
        }
    }
    if(br_test){
        std::cout << "functional_bootstrap_PSI_test: OK" << std::endl;
    } 

    std::cout << "Time for Evaluating the PSI circuit: " << single_psi_loop_time/test_num/1000 << " [s]" << std::endl;
    std::cout << "Time for Evaluating the PSI circuit: " << single_loop_decryption_time/test_num << " [micro seconds]" << std::endl;

}



int main(){

    // These two tests are crap
    // test_negacyclic_rotate_poly();
    // extract_and_key_switch_test();
    blind_rotation_test(10, simul); 
    // The tests below fail for some reason
    //functional_bootstrap_initial_test(8, signed_decomp);
    //functional_bootstrap_initial_polynomial_eval_test(8, signed_decomp);
    //functional_bootstrap_PSI_test(1);
    

    // The relevant performance tests
    bootstrap_test(5, simul); 
    functional_bootstrap_test(5, simul);
    // The PSI test is derecated
    //functional_bootstrap_PSI_smarter_test(5);
}