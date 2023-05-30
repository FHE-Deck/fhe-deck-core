 
#include <chrono>
#include <iostream> 
#include "../include/ntrunium.h"  
#include "../include/ntrunium_gen.h"
#include "../include/rotation_poly.h"
#include <NTL/ZZX.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_p.h>
#include <random>   

void test_key_switching(ntrunium_named_param param_name){

    std::cout << "=============== test_key_switching =================" << std::endl;
  
    ntrunium_named_param_generator param_gen(param_name); 
    param_gen.generate_bootstapping_keys();  
    sampler rand; 
    int t = 5;
       

    long* msg = param_gen.ntru.param.init_zero_poly();

    ntru_ct ct = param_gen.ntru.encrypt(msg); 
    long *out = param_gen.ntru.decrypt(&ct, t); 
    
    long *lwe_ct = param_gen.lwe_g_par.lwe_par.init_ct();
    // Key Switch to LWE 
    param_gen.boot->ntru_to_lwe_key_switch(lwe_ct, &ct); 
    long dec = param_gen.lwe_g.lwe.decrypt(lwe_ct, t);
    // Decrypt the resulting LWE ciphertexts. 
    if(dec == utils::integer_mod_form(out[0], t)){
        std::cout << "Key Switching Test: OK" << std::endl;
    }else{
        std::cout << "Key Switching Test: Fail" << std::endl;
        std::cout << "out[0]: " << out[0] << std::endl;
        std::cout << "utils::integer_mod_form(out[0], t): " << utils::integer_mod_form(out[0], t) << std::endl;
        std::cout << "dec: " << dec << std::endl;
    }

    delete param_gen.boot;
    delete param_gen.boot_sk;
    delete[] msg;
    delete[] out;
    delete[] lwe_ct;
}
 
 



void rotating_ntru_test(){
    std::cout << "=============== rotating_ntru_test =================" << std::endl;

    int N = 2048; 
    // LWE Parameters
    int n = 607; 
    long q = N; 
    long Q_pot = 1073741824;   
    long Q = Q_pot-35;

    // LWE error is set to zero, bacase we set the phase value manually to test blind rotation
    double lwe_stddev = 0; 
    double ntru_stddev = 3.2; 

    // The dimensions and the error are ridiculus, but here we only make a basic test
    lwe_param param(n, q, binary, lwe_stddev); 
    lwe_sk lwe(param);
    long t = 3; 
    long delta_q_t = (long)round((double)q/(double)t); 

    // NTRU Parameters 
    ntru_param ntru_par(cyclic, N, Q, any, ntru_stddev);  
 

    //  Key generation
    long *key = ntru_par.init_poly(); 
    long *inv_key = ntru_par.init_poly();   
    ntru_sk::key_gen(key, inv_key, ntru_par);     
    ntru_sk ntru(ntru_par, key, inv_key); 
   
    long* acc_msg = rotation_poly::cyclic_rot_identity(t, N, Q);    
    ntru_ct acc = ntru.kdm_encrypt(acc_msg); 
    // Test Single Rotation
    ntru_ct acc_rot_test(ntru_par); 
    long* rotation_test_dec = ntru_par.init_zero_poly(); 
    long* rotation_of_acc_msg = ntru_par.init_zero_poly(); 
    bool single_rot_test = true; 
    for(int i = 0; i < N; ++i){ 
        utils::rotate_poly(acc_rot_test.c, acc.c, ntru_par.engine->N, i); 
        utils::rotate_poly(rotation_of_acc_msg, acc_msg, ntru_par.engine->N, i); 
        ntru.decrypt(rotation_test_dec, &acc_rot_test, t); 
        utils::array_mod_form(rotation_test_dec, rotation_test_dec, N, t);  
        if(utils::is_eq_poly(rotation_of_acc_msg, rotation_test_dec, ntru_par.N)){ 
            std::cout << "Test Single Rotation: Fail" << std::endl;  
            single_rot_test = false;   
        }
        
    }
    if(single_rot_test){ 
        std::cout << "Test Single Rotation: OK" << std::endl; 
    } 
     
    // Encrypt the ciphertext that we want to bootstrap
    long ct_msg = 0;  
    long *ct = lwe.encrypt(ct_msg);  
    long phase = lwe.phase(ct);   

    // Test rotating NTRU LWE decryption 
    long ct_msg_test_rot = delta_q_t * 0; 
    long *ct_test_rot = ntru_par.init_poly(); 
    long phase_test_rot = lwe.phase(ct);  
    long* ct_rotation_test_dec = ntru_par.init_zero_poly(); 
    long* expected_rotation_test = ntru_par.init_zero_poly(); 
 
    long *acc_test_rot = ntru_par.init_zero_poly(); 
    ntru_ct acc_test_rot_next(ntru_par);
    bool rotation_decrypt_test = true;
    for(int j = 0; j < N; ++j){ 
        lwe.encrypt(ct, j);  
        phase = lwe.phase(ct);    
        utils::rotate_poly(expected_rotation_test, acc_msg, ntru_par.engine->N, phase);
        utils::array_rounding(expected_rotation_test, expected_rotation_test, ntru_par.N, Q, t);
        utils::array_mod_form(expected_rotation_test, expected_rotation_test, ntru_par.N, t);
        // Decrypt by rotating
        for(int i = 0; i < ntru_par.N; ++i){ 
            acc_test_rot[i] = 0;
            acc_test_rot_next.c[i] = 0;
        } 
        utils::rotate_poly(acc_test_rot, acc.c, ntru_par.engine->N, ct[0]);
        for(int i = 0; i < n; ++i){
            if(lwe.s[i] == 1){   
                utils::rotate_poly(acc_test_rot_next.c, acc_test_rot, ntru_par.engine->N, ct[i+1]);
            }else{ 
                // TODO Why rotation by 0 makes sense here?
                utils::rotate_poly(acc_test_rot_next.c, acc_test_rot, ntru_par.engine->N, 0);
            } 
            utils::rotate_poly(acc_test_rot, acc_test_rot_next.c, ntru_par.engine->N, 0);
        } 
        ntru.decrypt(ct_rotation_test_dec, &acc_test_rot_next, t);
        utils::array_mod_form(ct_rotation_test_dec, ct_rotation_test_dec, N, t); 
        if(!utils::is_eq_poly(ct_rotation_test_dec, expected_rotation_test, ntru_par.N)){ 
            std::cout << "Ciphertext Rotation Test: Fail" << std::endl;
            std::cout << "fail at: " << j << std::endl;  
            std::cout << "phase: " << phase << std::endl;
            std::cout << "ct_rotation_test_dec: " << utils::to_string(ct_rotation_test_dec, N) << std::endl;  
            std::cout << "expected_rotation_test: " << utils::to_string(expected_rotation_test, N) << std::endl; 
            rotation_decrypt_test = false;
            break;
        } 
    }
    if(rotation_decrypt_test){
        std::cout << "Ciphertext Rotation Test: OK" << std::endl;
    } 

    delete[] acc_msg;
    delete[] rotation_test_dec;
    delete[] rotation_of_acc_msg;
    delete[] ct;
    delete[] ct_test_rot;
    delete[] ct_rotation_test_dec;
    delete[] expected_rotation_test; 
    delete[] acc_test_rot;
}



void test_rotation_polynomials(int num_of_tests){
    std::cout << "=================== test_rotation_polynomials =======================" << std::endl;
    long Q = 128;
    long t = 13;
    // NOTE: Here N is the same as Q! Don't forget about that, or you get rubish.
    long N = Q;
    sampler rand; 
    long x;
    long result;
    long result_rounded; 
    long rot;
    long expected;

    // Test identity polynomial
    long *id_acc = rotation_poly::cyclic_rot_identity(t, N, Q);
    long *rotated_poly = new long[N];
    bool id_test = true;
    for(int i = 0; i < num_of_tests; ++i){
        x = rand.uniform(t); 
        rot = (long)round((Q * x)/t);
        // Eventually I might add a small gaussian error here.
        utils::rotate_poly(rotated_poly, id_acc, N, rot);
        result = rotated_poly[0];
        result_rounded = utils::integer_rounding(result, Q, t);
        result_rounded = utils::integer_mod_form(result_rounded, t);
        if(result_rounded != x){
            std::cout << "ID Test: Fail" << std::endl;
            std::cout << "At: " << i << std::endl;
            std::cout << "x:" << x << std::endl;
            std::cout << "result:" << result << std::endl;
            std::cout << "result_rounded:" << result_rounded << std::endl;
            std::cout << "rot: " << rot << std::endl;
            std::cout << "rot_rounded: " << utils::integer_mod_form(utils::integer_rounding(rot, Q, t), t) << std::endl;
            std::cout << "id_acc: " << utils::to_string(id_acc, N) << std::endl;
            std::cout << "rotated_poly: " << utils::to_string(rotated_poly, N) << std::endl; 
            id_test = false;
            break;
        }
    }
    if(id_test){
        std::cout << "ID Test: OK" << std::endl;
    }


    // Test inv mod
    long *inv_mod_acc = rotation_poly::cyclic_rot_inv_mod(t, N, Q);
    bool inv_mod_test = true; 
    for(int i = 0; i < num_of_tests; ++i){
        x = rand.uniform(t) % t; 
        // Compute what we expect
        if(x == 0){
            expected = 0;
        }else{
            expected = utils::mod_inv(x, t);
        }
        rot = (long)round((Q * x)/t);
        // Eventually I might add a small gaussian error here.
        utils::rotate_poly(rotated_poly, inv_mod_acc, N, rot);
        result = rotated_poly[0];
        result_rounded = utils::integer_rounding(result, Q, t);
        result_rounded = utils::integer_mod_form(result_rounded, t);
        if(result_rounded != expected){
            std::cout << "Inv Mod Test: Fail" << std::endl;
            std::cout << "At: " << i << std::endl;
            std::cout << "x:" << x << std::endl;
            std::cout << "expected:" << expected << std::endl;
            std::cout << "result:" << result << std::endl;
            std::cout << "result_rounded:" << result_rounded << std::endl;
            std::cout << "rot: " << rot << std::endl;
            std::cout << "rot_rounded: " << utils::integer_mod_form(utils::integer_rounding(rot, Q, t), t) << std::endl;
            std::cout << "inv_mod_acc: " << utils::to_string(inv_mod_acc, N) << std::endl;
            std::cout << "rotated_poly: " << utils::to_string(rotated_poly, N) << std::endl; 
            id_test = false;
            break;
        }
    }
    if(inv_mod_test){
        std::cout << "Inv Mod Test: OK" << std::endl;
    }

 
    // Test Multiplication
    long a = 0;
    long b = 0;
    long sum_exp;
    long sub_exp;
    long sum, sub;
    long* power_sum_acc = rotation_poly::cyclic_rot_square_and_div_by_4(t, N, Q);
    long* power_sum = new long[N];

    bool mul_mod_test = true; 
    for(int i = 0; i < num_of_tests; ++i){
        a = rand.uniform(t); 
        b = rand.uniform(t); 
        // Compute what we expect 
        expected = (a * b) % t;  
        sum_exp = (a + b) % t; 
        sub_exp = utils::integer_mod_form(a - b, t); 
        rot = (long)round((Q * sum_exp)/t); 
        utils::rotate_poly(power_sum, power_sum_acc, N, rot);
        sum = power_sum[0]; 

        rot = (long)round((Q * sub_exp)/t); 
        utils::rotate_poly(power_sum, power_sum_acc, N, rot);
        sub = power_sum[0];  

        result = (sum - sub) % Q;
        result_rounded = utils::integer_rounding(result, Q, t);
        result_rounded = utils::integer_mod_form(result_rounded, t);
        if(result_rounded != expected){
            std::cout << "Mul Mod test: Fail" << std::endl;
            std::cout << "At: " << i << std::endl;
            std::cout << "a:" << a << std::endl;
            std::cout << "b:" << b << std::endl;
            std::cout << "utils::mod_inv(4, t): " << utils::mod_inv(4, t) << std::endl;
            std::cout << "expected:" << expected << std::endl;
            std::cout << "result:" << result << std::endl;
            std::cout << "result_rounded:" << result_rounded << std::endl;
            //std::cout << "rot: " << rot << std::endl;
            std::cout << "rot_rounded: " << utils::integer_mod_form(utils::integer_rounding(rot, Q, t), t) << std::endl;
            std::cout << "inv_mod_acc: " << utils::to_string(inv_mod_acc, N) << std::endl;
            std::cout << "rotated_poly: " << utils::to_string(rotated_poly, N) << std::endl; 
            mul_mod_test = false;
            break;
        }
    }
    if(mul_mod_test){
        std::cout << "Mul Mod Test: OK" << std::endl;
    }

    // Test polynomial evaluation
    int size_of_poly = 10000;
    int *test_poly = new int[size_of_poly];
    for(int i = 0; i < size_of_poly; ++i){
        test_poly[i] = rand.uniform(t); 
    } 
    long *poly_eval_acc = rotation_poly::cyclic_rot_uni_poly(test_poly, size_of_poly, t, N, Q);
    bool poly_eval_test = true; 
    for(int i = 0; i < num_of_tests; ++i){
        x = rand.uniform(t); 
        // Compute what we expect 
        expected = utils::eval_poly_mod(x, test_poly, size_of_poly, t);
        rot = (long)round((Q * x)/t);
        // Eventually I might add a small gaussian error here.
        utils::rotate_poly(rotated_poly, poly_eval_acc, N, rot);
        result = rotated_poly[0];
        result_rounded = utils::integer_rounding(result, Q, t);
        result_rounded = utils::integer_mod_form(result_rounded, t);
        if(result_rounded != expected){
            std::cout << "Polynomial Eval Test: Fail" << std::endl;
            std::cout << "At: " << i << std::endl;
            std::cout << "x:" << x << std::endl;
            std::cout << "expected:" << expected << std::endl;
            std::cout << "result:" << result << std::endl;
            std::cout << "result_rounded:" << result_rounded << std::endl;
            std::cout << "rot: " << rot << std::endl;
            std::cout << "rot_rounded: " << utils::integer_mod_form(utils::integer_rounding(rot, Q, t), t) << std::endl;
            std::cout << "test_poly: " << utils::to_string(test_poly, size_of_poly) << std::endl;
            std::cout << "poly_eval_acc: " << utils::to_string(poly_eval_acc, N) << std::endl;
            std::cout << "rotated_poly: " << utils::to_string(rotated_poly, N) << std::endl; 
            poly_eval_test = false;
            break;
        }
    }
    if(poly_eval_test){
        std::cout << "Polynomial Eval Test: OK" << std::endl;
    }

    delete[] id_acc;
    delete[] rotated_poly;
    delete[] inv_mod_acc;
    delete[] power_sum_acc;
    delete[] power_sum;
    delete[] test_poly;
    delete[] poly_eval_acc;
}
 
 
  


void test_blind_rotate_named_params(ntrunium_named_param param_name, int num_of_rotations){ 
    std::cout << "=============== test_blind_rotate_named_params =================" << std::endl; 
 
    ntrunium_named_param_generator param_gen(param_name);  
    param_gen.generate_bootstapping_keys();
 
    int t = 3;
    // Create the identity function for the acc (its with power of two parameters) 
    long* acc_msg = rotation_poly::rot_identity(t, param_gen.N, param_gen.P);    
    ntru_ct acc_pot = param_gen.ntru_P.kdm_encrypt(acc_msg);   
    long *ct = param_gen.lwe_par_small.init_ct();
    long* msg = param_gen.ntru.param.init_zero_poly();
  
    ntru_ct out_acc_pot(param_gen.ntru_par_P); 
    ntru_ct acc_out_test(param_gen.ntru.param); 
    long *acc_msg_test = param_gen.ntru.param.init_poly(); 
    long *exp_acc = param_gen.ntru_par.init_poly();  
    ntru_ct out_acc(param_gen.ntru_par);

    long* init_acc = rotation_poly::rot_identity(t, param_gen.N, param_gen.Q);
    utils::array_rounding(init_acc, init_acc, param_gen.N, param_gen.Q, t);  


    // These parameters are after bootstrapping 
    long* out_msg = param_gen.ntru.param.init_poly(); 

    // Here I will set the number of rotations, because its difficult to go through all N
    
    bool blind_rotation_test = true;
    long test_phase;
    std::cout << "Start test " << std::endl;
    for(int i = 0; i < num_of_rotations; ++i){ 
        // Fresh encryption of i  
        param_gen.lwe_small.encrypt(ct, i); 
        test_phase = param_gen.lwe_small.phase(ct); 
        // Blind rotate  
        out_acc_pot = param_gen.boot->blind_rotate(&acc_pot, ct);  
        // Decrypt the output of blind rotation
        //param_gen.ntru_P.decrypt(out_msg, &out_acc_pot, t); 
        // Should be rotate by phase
        utils::negacyclic_rotate_poly(exp_acc, init_acc, param_gen.ntru_par.engine->N,test_phase); 
        // Now we need to switch out_acc from ntru_par_pot to ntru_par   
        out_acc = out_acc_pot.mod_switch(param_gen.ntru_par);
        param_gen.ntru.decrypt(out_msg, &out_acc, t);
        if(!utils::is_eq_poly(out_msg, exp_acc, param_gen.ntru_par.N)){
            std::cout << "Blind Rotation Test: Fail" << std::endl;
            std::cout << "Fail at:      " << i << std::endl;
            std::cout << "out:          " << utils::to_string(out_msg, param_gen.ntru_par.N) << std::endl;
            std::cout << "exp_acc:      " << utils::to_string(exp_acc, param_gen.ntru_par.N) << std::endl; 
            acc_out_test = acc_pot.mod_switch(param_gen.ntru_par);
            param_gen.ntru.decrypt(acc_msg_test, &acc_out_test, t);
            std::cout << "acc_msg_test: " << utils::to_string(acc_msg_test, param_gen.ntru_par.N) << std::endl;
 
            std::cout << "test_phase: " << test_phase << std::endl; 
            blind_rotation_test = false;

            // Lets to the blind rotation again on fresh ciphertexts to check whether we get the same 
            param_gen.ntru_P.kdm_encrypt(&acc_pot, acc_msg);  
            // Blind rotate
            out_acc_pot = param_gen.boot->blind_rotate(&acc_pot, ct);   
            utils::rotate_poly(exp_acc, init_acc, param_gen.ntru_par.engine->N, i);
            // Now we need to switch out_acc from ntru_par_pot to ntru_par 
            out_acc = out_acc_pot.mod_switch(param_gen.ntru_par);
            param_gen.ntru.decrypt(out_msg, &out_acc, t);
            std::cout << "out:          " << utils::to_string(out_msg, param_gen.ntru_par.N) << std::endl;
            break;
        }  
    }
    if(blind_rotation_test){
        std::cout << "Blind Rotation Test: OK" << std::endl;
    } 
    delete param_gen.boot;
    delete param_gen.boot_sk;
    delete[] msg;
    delete[] ct;
    delete[] acc_msg;
    delete[] out_msg; 
    delete[] acc_msg_test;
    delete[] exp_acc;
    delete[] init_acc;
}





void test_bootstrap_named_params(ntrunium_named_param param_name, int num_of_tests){ 
    std::cout << "=============== test_bootstrap_named_params =================" << std::endl; 
 
    ntrunium_named_param_generator param_gen(param_name);  
    std::cout << "Generate Bootstrapping Keys: " ;
    param_gen.generate_bootstapping_keys(); 
    std::cout << "DONE." << std::endl;
    sampler rand; 
    int t = 6;
    // Create the msb function for the acc (its with power of two parameters) 
    long* acc_msg = rotation_poly::rot_msb(t, param_gen.N, param_gen.P);   
    ntru_ct acc_pot = param_gen.ntru_P.kdm_encrypt(acc_msg);    
    ntru_ct ct(param_gen.ntru.param);
    long* msg = param_gen.ntru.param.init_zero_poly();

    long* testing_msg = param_gen.ntru.param.init_zero_poly();
 
    // These parameters are after bootstrapping 
    long* out_msg = param_gen.ntru.param.init_poly(); 
    bool bootstrap_test = true;
    int expected_out; 
    
    for(int i = 0; i < num_of_tests; ++i){
        // Generate a fresh ciphertext
        rand.uniform_array(msg, param_gen.N, t);
        param_gen.ntru.kdm_scale_and_encrypt(&ct, msg, t); 
        if(msg[0] >= t/2){
            expected_out = t-1;
        }else{
            expected_out = 1;
        }  
        // Bootstrap 
        ct = param_gen.boot->bootstrap(&acc_pot, &ct, t); 
        param_gen.ntru.decrypt(out_msg, &ct, t);
        out_msg[0] = utils::integer_mod_form(out_msg[0], t);
        // Here I should get the most signifficant but of msg
        if(out_msg[0] != expected_out){
            std::cout << "Bootstrapping Test: Fail" << std::endl;
            std::cout << "Fail at:      " << i << std::endl;
            std::cout << "out:          " << utils::to_string(out_msg, param_gen.ntru_par.N) << std::endl;
            std::cout << "msg:      " << utils::to_string(msg, param_gen.ntru_par.N) << std::endl;  
            std::cout << "out_msg[0]: " << out_msg[0] << std::endl;
            std::cout << "msg[0]: " <<  msg[0] << std::endl; 
            std::cout << "expected_out:  " << expected_out << std::endl;

            bootstrap_test = false; 
            break;
        } 
    }
    if(bootstrap_test){
        std::cout << "Bootstrapping Test: OK" << std::endl;
    } 
 
    delete param_gen.boot;
    delete param_gen.boot_sk;
    delete[] msg;
    delete[] testing_msg;
    delete[] acc_msg;
    delete[] out_msg; 
}



void test_bootstrap_with_functional_rotation_polynomials(ntrunium_named_param param_name, int num_of_tests){
    std::cout << "=============== test_bootstrap_with_functional_rotation_polynomials ================" << std::endl;

    ntrunium_named_param_generator param_gen(param_name); 
    param_gen.generate_bootstapping_keys(); 
    sampler rand; 
    int t = 5;
    // Create the identity function for the acc (its with power of two parameters) 
    long* acc_msg = rotation_poly::rot_identity(t, param_gen.N, param_gen.P);     
    ntru_ct acc_pot = param_gen.ntru_P.kdm_encrypt(acc_msg);   
    long* acc_msb_msg = rotation_poly::rot_msb(4, param_gen.N, param_gen.P);     
    ntru_ct acc_msb = param_gen.ntru_P.kdm_encrypt(acc_msb_msg);    
    ntru_ct ct(param_gen.ntru.param);
    long* msg = param_gen.ntru.param.init_zero_poly();

    // These parameters are after bootstrapping 
    long* out_msg = param_gen.ntru.param.init_poly(); 
    bool id_bootstrap_test = true;
 
    for(int i = 0; i < num_of_tests; ++i){ 
        msg[0] = rand.uniform(t);
        param_gen.ntru.kdm_scale_and_encrypt(&ct, msg, t);  
        ct = param_gen.boot->functional_bootstrap(&acc_pot, &acc_msb, &ct, t);
        param_gen.ntru.decrypt(out_msg, &ct, t);
        out_msg[0] = utils::integer_mod_form(out_msg[0], t);
        if(out_msg[0] != msg[0]){
            std::cout << "Functional Bootstrapping Identity Function Test: Fail" << std::endl;
            std::cout << "Fail at:      " << i << std::endl;
            std::cout << "out_msg[0]: " << out_msg[0] << std::endl;
            std::cout << "out:          " << utils::to_string(out_msg, param_gen.ntru_par.N) << std::endl;
            std::cout << "msg[0]:      " << utils::to_string(msg, param_gen.ntru_par.N) << std::endl; 
  
            id_bootstrap_test = false; 
            break;
        } 
    }
    if(id_bootstrap_test){
        std::cout << "Functional Bootstrapping Identity Function Test: OK" << std::endl;
    } 
   


    long *inv_mod_acc = rotation_poly::rot_inv_mod(t, param_gen.N, param_gen.P);   
    param_gen.ntru_P.kdm_encrypt(&acc_pot, inv_mod_acc);    
    long x; 
    long expected;
    bool mod_inv_test = true;
    for(int i = 0; i < num_of_tests; ++i){  
        msg[0] = rand.uniform(t);  
        if(msg[0] == 0){
            expected = 0;
        }else{
            expected = utils::mod_inv(msg[0], t);
        }
        param_gen.ntru.kdm_scale_and_encrypt(&ct, msg, t);  
        ct = param_gen.boot->functional_bootstrap(&acc_pot, &acc_msb, &ct, t);
        param_gen.ntru.decrypt(out_msg, &ct, t);
        out_msg[0] = utils::integer_mod_form(out_msg[0], t);
        if(out_msg[0] != expected){
            std::cout << "Functional Bootstrapping Mod Inverse Function Test: Fail" << std::endl;
            std::cout << "Fail at:      " << i << std::endl;
            std::cout << "out_msg[0]: " << out_msg[0] << std::endl;
            std::cout << "out:          " << utils::to_string(out_msg, param_gen.ntru_par.N) << std::endl;
            std::cout << "msg:      " << utils::to_string(msg, param_gen.ntru_par.N) << std::endl; 
  
            mod_inv_test = false; 
            break;
        } 
    }
    if(mod_inv_test){
        std::cout << "Functional Bootstrapping Mod Inverse Function Test: OK" << std::endl;
    } 

    

    long *power_sum_acc = rotation_poly::rot_square_and_div_by_4(t, param_gen.N, param_gen.P);   
    param_gen.ntru_P.kdm_encrypt(&acc_pot, power_sum_acc);    
    ntru_ct ct_a(param_gen.ntru.param);
    ntru_ct ct_b(param_gen.ntru.param);
    ntru_ct power_plus(param_gen.ntru.param);
    ntru_ct power_minus(param_gen.ntru.param);
    ntru_ct out_ct(param_gen.ntru.param); 
    long a, b;  
    bool mul_mod_test = true; 
    for(int i = 0; i < num_of_tests; ++i){  
        a = rand.uniform(t); 
        b = rand.uniform(t); 
        // Compute what we expect 
        expected = (a * b) % t;  
        msg[0] = a;
        param_gen.ntru.kdm_scale_and_encrypt(&ct_a, msg, t);  
        msg[0] = b;
        param_gen.ntru.kdm_scale_and_encrypt(&ct_b, msg, t);
        
        power_plus = ct_a.add(&ct_b); 
        power_minus = ct_a.sub(&ct_b);  
  
        power_plus = param_gen.boot->functional_bootstrap(&acc_pot, &acc_msb, &power_plus, t);
        power_minus = param_gen.boot->functional_bootstrap(&acc_pot, &acc_msb, &power_minus, t);
        out_ct = power_plus.sub(&power_minus); 
        param_gen.ntru.decrypt(out_msg, &out_ct, t);
        out_msg[0] = utils::integer_mod_form(out_msg[0], t);
        if(out_msg[0] != expected){
            std::cout << "Functional Bootstrapping Multiplication Test: Fail" << std::endl;
            std::cout << "Fail at:      " << i << std::endl;
            std::cout << "out_msg[0]: " << out_msg[0] << std::endl;
            std::cout << "out:          " << utils::to_string(out_msg, param_gen.ntru_par.N) << std::endl;
            std::cout << "msg:      " << utils::to_string(msg, param_gen.ntru_par.N) << std::endl; 
  
            mul_mod_test = false; 
            break;
        } 
    }
    if(mul_mod_test){
        std::cout << "Functional Bootstrapping Multiplication Test: OK" << std::endl;
    } 
 
    // Test polynomial evaluation
    int size_of_poly = 10000; 
    int *test_poly = new int[size_of_poly];
    for(int i = 0; i < size_of_poly; ++i){
        test_poly[i] = rand.uniform(t); 
    } 
    long *poly_eval_acc = rotation_poly::rot_uni_poly(test_poly, size_of_poly, t, param_gen.N, param_gen.P); 
    param_gen.ntru_P.kdm_encrypt(&acc_pot, poly_eval_acc);      
    bool uni_poly_test = true;
    for(int i = 0; i < num_of_tests; ++i){  
        msg[0] = rand.uniform(t);    
        expected = utils::eval_poly_mod(msg[0], test_poly, size_of_poly, t);
        param_gen.ntru.kdm_scale_and_encrypt(&ct, msg, t);  
        ct = param_gen.boot->functional_bootstrap(&acc_pot,  &acc_msb, &ct, t);
        param_gen.ntru.decrypt(out_msg, &ct, t);
        out_msg[0] = utils::integer_mod_form(out_msg[0], t);
        if(out_msg[0] != expected){
            std::cout << "Functional Bootstrapping Univariate Polynomial Test: Fail" << std::endl;
            std::cout << "Fail at:      " << i << std::endl;
            std::cout << "out_msg[0]: " << out_msg[0] << std::endl;
            std::cout << "out:          " << utils::to_string(out_msg, param_gen.ntru_par.N) << std::endl;
            std::cout << "msg:      " << utils::to_string(msg, param_gen.ntru_par.N) << std::endl; 
  
            uni_poly_test = false; 
            break;
        } 
        // Testing also when other coefficients of the msg are set to some non-zero value (I could set them to random, but that is faster)
        utils::set(msg, out_msg, param_gen.N);
    }
    if(uni_poly_test){
        std::cout << "Functional Bootstrapping Univariate Polynomial Test: OK" << std::endl;
    }  

    delete param_gen.boot;
    delete param_gen.boot_sk;
    delete[] msg; 
    delete[] acc_msg;
    delete[] acc_msb_msg;
    delete[] out_msg; 
    delete[] inv_mod_acc;
    delete[] power_sum_acc;
    delete[] test_poly;
    delete[] poly_eval_acc;
}
 





 
  
std::string to_string_matrix(int** mat, int n){
    std::string out = "";
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n+1; ++j){
            out = out + std::to_string(mat[i][j]) + ", ";
        }
        out = out + "\n";
    }
    return out;
}
  

void plaintext_gauss(int* res, int** mat, int n, int modulus){
    std::cout << "plaintext_gauss" << std::endl;
    int num_of_invs = 0;
    int num_of_muls = 0;
    int inv; 

    for(int i = 0; i < n-1; ++i){     
        inv = utils::mod_inv(mat[i][i], modulus);  
        num_of_invs++;
        for(int j = i+1; j < n; ++j)
        { 
            int diag = (mat[j][i] * inv) % modulus;
            num_of_muls++;
            for(int k = 0; k < n+1; ++k)
            { 
                int diag_mat = diag * mat[i][k] % modulus; 
                num_of_muls++;
                mat[j][k] = utils::integer_mod_form(mat[j][k] - diag_mat, modulus);
            }
        }
    } 
    for(int i = n-1; i >= 0; --i){                     
        res[i] = mat[i][n];       
        inv = utils::mod_inv(mat[i][i], modulus);  
        num_of_invs++;
        for(int j = i+1; j < n; ++j) 
        {
            if(i != j)
            {
                int prod = (mat[i][j] * res[j]) % modulus;
                num_of_muls++;
                res[i] = utils::integer_mod_form(res[i] - prod, modulus);
            }          
        }
        res[i] =  utils::integer_mod_form(res[i] * inv, modulus);  
        num_of_muls++;
    }
    std::cout << "num_of_invs: " << num_of_invs << std::endl;
    std::cout << "num_of_muls: " << num_of_muls << std::endl;
    std::cout << "Required Bootstraps: " << num_of_invs + 2 * num_of_muls << std::endl;
}

 

ntru_ct hom_mul(ntru_ct *ct_a, ntru_ct *ct_b, ntru_ct *ct_acc, ntru_ct *acc_msb, ntrunium_named_param_generator param_gen, int t){  
    ntru_ct power_plus =  ct_a->add(ct_b); 
    ntru_ct power_minus = ct_a->sub(ct_b);   
    power_plus = param_gen.boot->functional_bootstrap(ct_acc, acc_msb, &power_plus, t);
    power_minus = param_gen.boot->functional_bootstrap(ct_acc, acc_msb, &power_minus, t);
    return power_plus.sub(&power_minus); 
}



long decrypt(ntrunium_named_param_generator param_gen, ntru_ct *ct, int t){
    long *out_msg = param_gen.ntru_par.init_zero_poly();
    long ret;
    param_gen.ntru.decrypt(out_msg, ct, t);
    ret =  utils::integer_mod_form(out_msg[0], t);
    delete[] out_msg;
    return ret;
}

void homomorphic_plaintext_gauss(ntrunium_named_param_generator param_gen, int* res, int** mat, int n, int t){ 

    long *msg = param_gen.ntru_par.init_zero_poly();
    // Encrypt the matrix
    ntru_ct** mat_ct = new ntru_ct*[n];
    for(int i = 0; i < n; ++i){
        mat_ct[i] = new ntru_ct[n+1];
        for(int j = 0; j <= n; ++j){
            msg[0] = mat[i][j];
            mat_ct[i][j] = param_gen.ntru.kdm_scale_and_encrypt(msg, t);
        }
    } 
    //  Accumulator for the inversion function
    long *inv_mod_rot_poly = rotation_poly::rot_inv_mod(t, param_gen.N, param_gen.P);   
    ntru_ct inv_mod_acc_ct = param_gen.ntru_P.kdm_encrypt(inv_mod_rot_poly); 
    // Accumulator for the multiplication 
    long *power_sum_acc = rotation_poly::rot_square_and_div_by_4(t, param_gen.N, param_gen.P);   
    ntru_ct mul_acc_ct = param_gen.ntru_P.kdm_encrypt(power_sum_acc);    
  
    long* acc_msb_msg = rotation_poly::rot_msb(4, param_gen.N, param_gen.P);     
    ntru_ct acc_msb = param_gen.ntru_P.kdm_encrypt(acc_msb_msg);   

    // Ciphertexts that we use in our homomorphic evaluation
    int inv; 
    ntru_ct inv_ct(param_gen.ntru.param);
    ntru_ct diag_ct(param_gen.ntru.param);
    ntru_ct diag_mat_ct(param_gen.ntru.param);
    ntru_ct prod_ct(param_gen.ntru.param);
    
    ntru_ct *res_ct = new ntru_ct[n];
    //for(int i = 0; i < n; ++i){
    //    res_ct[i](param_gen.ntru_par);
    //} 

    for(int i = 0; i < n-1; ++i){     
        inv_ct = param_gen.boot->functional_bootstrap(&inv_mod_acc_ct, &acc_msb, &mat_ct[i][i], t); 
        //inv = utils::mod_inv(mat[i][i], t);  
        //std::cout << "mat["<<i<<"]["<<i<<"]: " << mat[i][i] << ", inv: " <<  inv << std::endl; 
        //std::cout << "Inv(mat_ct["<<i<<"]["<<i<<"]): " << decrypt(param_gen, &mat_ct[i][i], t) << ", inv: " <<  decrypt(param_gen, &inv_ct, t) << std::endl; 
        for(int j = i+1; j < n; ++j)
        { 
            //int diag = (mat[j][i] * inv) % t;
            diag_ct = hom_mul(&mat_ct[j][i], &inv_ct, &mul_acc_ct, &acc_msb, param_gen, t);
            //std::cout << "diag: " << diag << std::endl;
            //std::cout << "diag_ct: " <<  decrypt(param_gen, diag_ct, t) << std::endl; 
            for(int k = 0; k < n+1; ++k)
            {
                //int diag_mat = diag * mat[i][k] % t; 
                diag_mat_ct = hom_mul(&diag_ct, &mat_ct[i][k], &mul_acc_ct, &acc_msb, param_gen, t);
                //std::cout << "diag_mat: " << diag_mat << std::endl;
                //std::cout << "diag_mat_ct: " <<  decrypt(param_gen, diag_mat_ct, t) << std::endl; 
                //mat[j][k] = utils::integer_mod_form(mat[j][k] - diag_mat, t);
                mat_ct[j][k] = mat_ct[j][k].sub(&diag_mat_ct); 
                //std::cout << "mat[" << j << "][" << k << "]: " << mat[j][k] << std::endl;
                //std::cout << "mat_ct[" << j << "][" << k << "]: " <<  decrypt(param_gen, mat_ct[j][k], t) << std::endl; 
            }
        }
    }  
    for(int i = n-1; i >= 0; --i){                      
        //utils::set(res_ct[i], mat_ct[i][n], param_gen.ntru_par.N);     
        res_ct[i] = mat_ct[i][n]; 
        inv_ct = param_gen.boot->functional_bootstrap(&inv_mod_acc_ct, &acc_msb, &mat_ct[i][i], t); 
        //std::cout << "mat["<<i<<"]["<<i<<"]: " << mat[i][i] << ", inv: " <<  inv << std::endl; 
        //std::cout << "Inv(mat_ct["<<i<<"]["<<i<<"]): " << mat[i][i] << ", inv: " <<  decrypt(param_gen, inv_ct, t) << std::endl; 
        for(int j = i+1; j < n; ++j) 
        {
            if(i != j)
            {
                //int prod = (mat[i][j] * res[j]) % t;
                prod_ct = hom_mul(&mat_ct[i][j], &res_ct[j], &mul_acc_ct, &acc_msb, param_gen, t); 
                //std::cout << "prod: " << prod << std::endl;
                //std::cout << "prod_ct: " << decrypt(param_gen, prod_ct, t) << std::endl;

                //res[i] = utils::integer_mod_form(res[i] - prod, t);
                res_ct[i] = res_ct[i].sub(&prod_ct); 
                //std::cout << "res["<<i<<"]: " << res[i] << std::endl;
                //std::cout << "res_ct["<<i<<"]: " << decrypt(param_gen, res_ct[i], t) << std::endl;
            }          
        }
        
        res_ct[i] = hom_mul(&res_ct[i], &inv_ct, &mul_acc_ct, &acc_msb, param_gen, t); 
        res[i] = decrypt(param_gen, &res_ct[i], t); 
    }  
    delete[] msg;
    delete[] mat_ct;
    delete[] inv_mod_rot_poly;
    delete[] power_sum_acc;
    delete[] acc_msb_msg;
    delete[] res_ct;
}

// Return a random system of linear equations.
// Later I will check if the simple gauss solves it, if yet, then I will take it for testing
// n is the dimension
// t is the modulus
int** random_system_of_equations(int n, int t){
    sampler rand; 
    int** mat = new int*[n];
    for(int i = 0; i < n; ++i){
        mat[i] = new int[n+1];
        for(int j = 0; j <= n; ++j){ 
            mat[i][j]  = rand.uniform(t);
        }
    }
    return mat;
}

bool is_solution(int** mat, int* sol, int n, int t){ 
    for(int i = 0; i < n; ++i){
        int comb = 0;
        for(int j = 0; j < n; ++j){
            comb = (comb + mat[i][j] * sol[j]) % t;
        } 
        if(comb != mat[i][n]){
            return false;
        }
    } 
    return true;
}


void plaintext_gaussian_elimination_test(){
    std::cout << "=========================== plaintext_gaussian_elimination_test ======================" << std::endl; 
    int t = 13;
    int n = 2;
    int** mat = new int*[2];
    mat[0] = new int[3];
    mat[1] = new int[3];

    mat[0][0] = 2;
    mat[0][1] = 3;
    mat[0][2] = 1;
    mat[1][0] = 3;
    mat[1][1] = t-1;
    mat[1][2] = 7; 
    std::cout << "mat:" << std::endl;
    std::cout << to_string_matrix(mat, n) << std::endl;
    int* res = new int[n];

    plaintext_gauss(res, mat, n, t);
    std::cout << "res: " << utils::to_string(res, n) << std::endl;
    std::cout << "is_solution: " << is_solution(mat, res, n, t) << std::endl;


    n = 2;
    int* res_test = new int[n];
    int** mat_test = random_system_of_equations(n, t); 
    std::cout << to_string_matrix(mat_test, n) << std::endl;
    plaintext_gauss(res_test, mat_test, n, t);
    std::cout << "res_test: " << utils::to_string(res_test, n) << std::endl;
    std::cout << "is_solution: " << is_solution(mat_test, res_test, n, t) << std::endl;
    std::cout << "mat_test:" << std::endl;

}


void homomorphic_gaussian_elimination_test(ntrunium_named_param param_name){
    ntrunium_named_param_generator param_gen(param_name); 
    param_gen.generate_bootstapping_keys();
    std::cout << "============================== homomorphic_gaussian_elimination_test ===============================" << std::endl; 
    std::chrono::high_resolution_clock::time_point start, end; 
    float time;
    int t = 13;
    int n;
     
    std::cout << "2 Dim Gauss Test: " << std::endl;
    n = 2;
    int tab_2[n][n+1] = {{6, 8, 6},
                        {11, 4, 9}};   
    int** mat_2 = new int*[n];
    for(int i = 0; i < n; ++i){
        mat_2[i] = new int[n+1]; 
        for(int j = 0; j <= n;++j){
            mat_2[i][j] = tab_2[i][j];
        }
    } 
    std::cout << "mat:" << std::endl;
    std::cout << to_string_matrix(mat_2, 2) << std::endl; 
    int* res_2 = new int[2];
    start = std::chrono::high_resolution_clock::now(); 
    homomorphic_plaintext_gauss(param_gen, res_2, mat_2, 2, t);
    std::cout << "res_2: " << utils::to_string(res_2, 2) << std::endl;
    std::cout << "is solution: " << is_solution(mat_2, res_2, 2, t) << std::endl;
    std::cout << "res: " << utils::to_string(res_2, 2) << std::endl; 
    end = std::chrono::high_resolution_clock::now(); 
    time = std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();  
    std::cout << "Avg Time Blind Rotations: " <<  time/1000 << " [s]" << std::endl;
  
 

    std::cout << "3 Dim Gauss Test: " << std::endl;
    n = 3;
    int tab_3[n][n+1] = {{7, 8, 7, 3},
                        {8, 6, 1, 10 },
                        {10, 4, 9, 10}}; 
    int** mat_3 = new int*[n];
    for(int i = 0; i < n; ++i){
        mat_3[i] = new int[n+1]; 
        for(int j = 0; j <= n;++j){
            mat_3[i][j] = tab_3[i][j];
        }
    } 
    int* res_3 = new int[3]; 
    start = std::chrono::high_resolution_clock::now();  
    homomorphic_plaintext_gauss(param_gen, res_3,  mat_3, 3, t);
    std::cout << "res_3: " << utils::to_string(res_3, 3) << std::endl;
    std::cout << "is solution: " << is_solution(mat_3, res_3, 3, t) << std::endl;
    end = std::chrono::high_resolution_clock::now(); 
    time = std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();  
    std::cout << "Avg Time Blind Rotations: " <<  time/1000 << " [s]" << std::endl; 


    std::cout << "4 Dim Gauss Test: " << std::endl;
    n = 4;
    int tab_4[n][n+1] = {{10, 4, 11, 0, 12}, 
                        {10, 8, 2, 10, 10},
                        {9, 5, 6, 11, 7}, 
                        {7, 8, 1, 10, 10}};
    int** mat_4 = new int*[n];
    for(int i = 0; i < n; ++i){
        mat_4[i] = new int[n+1]; 
        for(int j = 0; j <= n;++j){
            mat_4[i][j] = tab_4[i][j];
        }
    } 
    int* res_4 = new int[4]; 
    start = std::chrono::high_resolution_clock::now(); 
    homomorphic_plaintext_gauss(param_gen, res_4,  mat_4, 4, t);
    std::cout << "res_4: " << utils::to_string(res_4, 4) << std::endl;
    std::cout << "is solution: " << is_solution(mat_4, res_4, 4, t) << std::endl;
    end = std::chrono::high_resolution_clock::now(); 
    time = std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();  
    std::cout << "Avg Time Blind Rotations: " <<  time/1000 << " [s]" << std::endl;


    std::cout << "5 Dim Gauss Test: " << std::endl;
    n = 5;
    int tab_5[n][n+1] = {{6, 10, 8, 5, 3, 8}, 
                        {10, 9, 11, 9, 12, 7},
                        {9, 9, 8, 8, 3, 9}, 
                        {1, 1, 12, 12, 0, 6},
                        {9, 6, 3, 11, 12, 10}};
    int** mat_5 = new int*[n];
    for(int i = 0; i < n; ++i){
        mat_5[i] = new int[n+1]; 
        for(int j = 0; j <= n;++j){
            mat_5[i][j] = tab_5[i][j];
        }
    } 
    int* res_5 = new int[5]; 
    start = std::chrono::high_resolution_clock::now(); 
    homomorphic_plaintext_gauss(param_gen, res_5,  mat_5, 5, t);
    std::cout << "res_5: " << utils::to_string(res_5, 5) << std::endl;
    std::cout << "is solution: " << is_solution(mat_5, res_5, 5, t) << std::endl;
    end = std::chrono::high_resolution_clock::now(); 
    time = std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();  
    std::cout << "Avg Time Blind Rotations: " <<  time/1000 << " [s]" << std::endl;
 
    std::cout << "6 Dim Gauss Test: " << std::endl;
    n = 6;
    int tab_6[n][n+1] = {{6, 11, 3, 8, 12, 10, 0}, 
                        {1, 6, 0, 1, 6, 11, 4},
                        {3, 1, 3, 12, 3, 0, 7}, 
                        {4, 6, 11, 12, 2, 1, 11},
                        {0, 12, 3, 8, 6, 6, 6},
                        {8, 9, 5, 11, 11, 0, 11}};
    int** mat_6 = new int*[n];
    for(int i = 0; i < n; ++i){
        mat_6[i] = new int[n+1]; 
        for(int j = 0; j <= n;++j){
            mat_6[i][j] = tab_6[i][j];
        }
    } 
    int* res_6 = new int[6]; 
    start = std::chrono::high_resolution_clock::now(); 
    homomorphic_plaintext_gauss(param_gen, res_6,  mat_6, 6, t);
    std::cout << "res_6: " << utils::to_string(res_6, 6) << std::endl;
    std::cout << "is solution: " << is_solution(mat_6, res_6, 6, t) << std::endl;
    end = std::chrono::high_resolution_clock::now(); 
    time = std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();  
    std::cout << "Avg Time Blind Rotations: " <<  time/1000 << " [s]" << std::endl;
 

    std::cout << "7 Dim Gauss Test: " << std::endl;
    n = 7;
    int tab_7[n][n+1] = {{9, 3, 7, 5, 1, 7, 12, 10}, 
                        {4, 6, 7, 6, 3, 1, 12, 9},
                        {2, 6, 1, 6, 3, 5, 11, 11}, 
                        {4, 7, 8, 12, 10, 6, 5, 5},
                        {12, 3, 11, 11, 4, 5, 12, 10},
                        {8, 11, 1, 7, 1, 6, 1, 4},
                        {10, 6, 11, 3, 11, 2, 5, 8}};
    int** mat_7 = new int*[n];
    for(int i = 0; i < n; ++i){
        mat_7[i] = new int[n+1]; 
        for(int j = 0; j <= n;++j){
            mat_7[i][j] = tab_7[i][j];
        }
    } 
    int* res_7 = new int[7]; 
    start = std::chrono::high_resolution_clock::now(); 
    homomorphic_plaintext_gauss(param_gen, res_7,  (int**)mat_7, 7, t);
    std::cout << "res_7: " << utils::to_string(res_7, 6) << std::endl;
    std::cout << "is solution: " << is_solution((int**)mat_7, res_7, 7, t) << std::endl;
    end = std::chrono::high_resolution_clock::now(); 
    time = std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();  
    std::cout << "Avg Time Blind Rotations: " <<  time/1000 << " [s]" << std::endl;  


    delete param_gen.boot;
    delete param_gen.boot_sk;
    delete[] mat_2;
    delete[] mat_3;
    delete[] mat_4;
    delete[] mat_5;
    delete[] mat_6;
    delete[] mat_7; 
    delete[] res_2;
    delete[] res_3;
    delete[] res_4;
    delete[] res_5;
    delete[] res_6;
    delete[] res_7;

}
 



int main(){   
 
    test_key_switching(ntrunium_C_12_B); 
    //rotating_ntru_test();
    // This one tests cyclic rotation polynomials (I should verify negacyclic actually)
    //test_rotation_polynomials(1000); 
   
    test_blind_rotate_named_params(ntrunium_C_12_B, 10);
    // Bootstrap computes a negacyclic function 
    test_bootstrap_named_params(ntrunium_C_12_B, 10); 
    test_bootstrap_with_functional_rotation_polynomials(ntrunium_C_12_B, 10);  

    //plaintext_gaussian_elimination_test();  
    // The test below is time consuming
    //homomorphic_gaussian_elimination_test(ntrunium_C_12_B);
}
