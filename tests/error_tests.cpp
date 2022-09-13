 
#include <iostream>
#include "../include/lwe.h"
#include "../include/ntru.h"
#include "../include/utils.h"





double mean(long* errors, int size_of_errors){
    double sum = 0;
    for(int i = 0; i < size_of_errors; ++i){
        sum += (double)errors[i];
    }
    return sum / (double)size_of_errors;
}

double variance(long* errors, int size_of_errors){
    double m = mean(errors, size_of_errors);
    //std::cout << "In Variance - mean: " << m << std::endl;
    double sum = 0.0;
    double square = 0.0;
    for(int i = 0; i < size_of_errors; ++i){
        square = errors[i] - m;
        square *= square;
        sum += square;
    }
    //std::cout << "In Variance - sum: " << sum << std::endl;
    //std::cout << "In Variance - size_of_errors: " << size_of_errors << std::endl;
    return sum/(double)size_of_errors;
}

double standard_deviation(double var){
    return sqrt(var);
}

 
void plain_lwe_test(int test_num){
    std::cout << "=== plain_lwe_test: Testing Error for Encryption === " << std::endl;
    
    int n = 512;
    double stddev = 3.2;
    long Q = 101; 
    lwe_sk lwe(n, Q, stddev, binary); 

    long *ct = lwe.lwe_par.init_ct();
    long* errors = new long[test_num];
    for(int i = 0; i < test_num; ++i){
        // Measure time here - do we need to measure stuff here?
        lwe.encrypt(ct, 0); 
        // Stop measuring time here
        errors[i] = lwe.error(ct, 0);
        
    }
    double emp_mean = mean(errors, test_num);
    double emp_var = variance(errors, test_num);
    double emp_stddev = standard_deviation(emp_var);
    std::cout << "    - empirical mean: " <<  emp_mean << std::endl;
    std::cout << "    - empirical variance: " <<  emp_var << std::endl;
    std::cout << "    - expected variance: " <<  stddev * stddev << std::endl;
    std::cout << "    - empirical stddev: " <<  emp_stddev << std::endl;
    std::cout << "    - expected stddev: " <<  stddev << std::endl;
    delete(ct);
    delete(errors);
}
 

void plain_ntru_test(int test_num){ 
    std::cout << "=== plain_ntru_test: Testing Error for Encryption === " << std::endl; 
    // Prime number: 2**26 - 5
    long Q = 67108859;
    // Prime number:  2**11 -9
    int N = 2039; 
    double stddev = 3.2;
    ntru_param ntru_par(cyclic, N, Q, any, stddev);
    ntru_sk ntru(ntru_par); 
    // Encryption the zero message in the NTRU ciphertext 
    long* msg = ntru.param.init_zero_poly();
    //long *ct = ntru.param.init_poly(); 
    ntru_ct ct(ntru_par);
    long* errors = new long[test_num];
    long *phase = ntru.param.init_poly();
    int iterations = test_num/N;
    
    for(int i = 0; i < iterations; ++i){ 
        ntru.encrypt(&ct, msg);  
        ntru.phase(phase, &ct); 
        for(int j = 0; j < N; ++j){ 
            errors[N * i + j] = phase[j];
        } 
    }
    ntru.encrypt(&ct, msg);  
    ntru.phase(phase, &ct);
    int rest = test_num % N;
    for(int j = 0; j < rest; ++j){
        errors[N * iterations + j] = phase[j];
    }  
    double emp_mean = mean(errors, test_num);
    double emp_var = variance(errors, test_num);
    double emp_stddev = standard_deviation(emp_var); 
    std::cout << "    - empirical mean: " <<  emp_mean << std::endl;
    std::cout << "    - empirical variance: " <<  emp_var << std::endl;
    std::cout << "    - empirical stddev: " <<  emp_stddev << std::endl;


    std::cout << "=== plain_ntru_test: Testing Error for modulus switching === " << std::endl; 
    // Prime: 2**20 - 3
    long small_Q = 1048573;
    ntru_param ntru_par_small = ntru_par.mod_switch(small_Q);
    ntru_sk ntru_small = ntru.mod_switch(small_Q);
    //long* ct_small = ntru_par.init_poly();
    ntru_ct ct_small(ntru_par_small);

    for(int i = 0; i < iterations; ++i){ 
        ntru.encrypt(&ct, msg);  
        // Modulus switch the ciphertext
        //ntru_sk::switch_modulus(ct_small, ct, ntru_par_small, ntru_par);
        ct_small = ct.mod_switch(ntru_par_small);
        ntru_small.phase(phase, &ct_small);
        for(int j = 0; j < N; ++j){ 
            errors[N * i + j] = phase[j];
        } 
    }
    ntru.encrypt(&ct, msg);   
    //ntru_sk::switch_modulus(ct_small, ct, ntru_par_small, ntru_par);
    ct_small = ct.mod_switch(ntru_par_small);
    // Lets check  
    ntru_small.phase(phase, &ct_small); 
    //rest = test_num % N;
    for(int j = 0; j < rest; ++j){
        errors[N * iterations + j] = phase[j];
    }  
    emp_mean = mean(errors, test_num);
    emp_var = variance(errors, test_num);
    emp_stddev = standard_deviation(emp_var); 
    std::cout << "    - empirical mean: " <<  emp_mean << std::endl;
    std::cout << "    - empirical variance: " <<  emp_var << std::endl;
    std::cout << "    - empirical stddev: " <<  emp_stddev << std::endl;


    std::cout << "=== plain_ntru_test: Second Modulus Switching === " << std::endl; 
    // Prime: 2**18 - 5
    small_Q = 262139;
    ntru_par_small = ntru_par.mod_switch(small_Q);
    ntru_small = ntru.mod_switch(small_Q); 

    for(int i = 0; i < iterations; ++i){ 
        ntru.encrypt(&ct, msg);  
        // Modulus switch the ciphertext
        // ntru_sk::switch_modulus(ct_small, ct, ntru_par_small, ntru_par);
        ct_small = ct.mod_switch(ntru_par_small);
        ntru_small.phase(phase, &ct_small);
        for(int j = 0; j < N; ++j){ 
            errors[N * i + j] = phase[j];
        } 
    }
    ntru.encrypt(&ct, msg);  
    // ntru_sk::switch_modulus(ct_small, ct, ntru_par_small, ntru_par);
    ct_small = ct.mod_switch(ntru_par_small);
    ntru_small.phase(phase, &ct_small);
    //rest = test_num % N;
    for(int j = 0; j < rest; ++j){
        errors[N * iterations + j] = phase[j];
    }  
    emp_mean = mean(errors, test_num);
    emp_var = variance(errors, test_num);
    emp_stddev = standard_deviation(emp_var); 
    std::cout << "    - empirical mean: " <<  emp_mean << std::endl;
    std::cout << "    - empirical variance: " <<  emp_var << std::endl;
    std::cout << "    - empirical stddev: " <<  emp_stddev << std::endl;


    std::cout << "=== plain_ntru_test: Switch to power of two 2**20 === " << std::endl; 
    // Prime: 2**20  
    small_Q = 1048576;
    ntru_par_small = ntru_par.mod_switch(small_Q);
    ntru_small = ntru.mod_switch(small_Q); 

    for(int i = 0; i < iterations; ++i){ 
        ntru.encrypt(&ct, msg);  
        // Modulus switch the ciphertext
        //ntru_sk::switch_modulus(ct_small, ct, ntru_par_small, ntru_par);
        ct_small = ct.mod_switch(ntru_par_small);
        ntru_small.phase(phase, &ct_small);
        for(int j = 0; j < N; ++j){ 
            errors[N * i + j] = phase[j];
        } 
    }
    ntru.encrypt(&ct, msg);   
    // ntru_sk::switch_modulus(ct_small, ct, ntru_par_small, ntru_par);
    ct_small = ct.mod_switch(ntru_par_small);
    // Lets check  
    ntru_small.phase(phase, &ct_small); 
    //rest = test_num % N;
    for(int j = 0; j < rest; ++j){
        errors[N * iterations + j] = phase[j];
    }  
    emp_mean = mean(errors, test_num);
    emp_var = variance(errors, test_num);
    emp_stddev = standard_deviation(emp_var); 
    std::cout << "    - empirical mean: " <<  emp_mean << std::endl;
    std::cout << "    - empirical variance: " <<  emp_var << std::endl;
    std::cout << "    - empirical stddev: " <<  emp_stddev << std::endl;

    std::cout << "=== plain_ntru_test: Switch to power of two 2**18 === " << std::endl; 
    // Prime: 2**18 
    small_Q = 262144;
    ntru_par_small = ntru_par.mod_switch(small_Q);
    ntru_small = ntru.mod_switch(small_Q); 

    for(int i = 0; i < iterations; ++i){ 
        ntru.encrypt(&ct, msg);  
        // Modulus switch the ciphertext
        /// ntru_sk::switch_modulus(ct_small, ct, ntru_par_small, ntru_par); 
        ct_small = ct.mod_switch(ntru_par_small);
        ntru_small.phase(phase, &ct_small);
        for(int j = 0; j < N; ++j){ 
            errors[N * i + j] = phase[j];
        } 
    }
    ntru.encrypt(&ct, msg);  
    //ntru_sk::switch_modulus(ct_small, ct, ntru_par_small, ntru_par);
    ct_small = ct.mod_switch(ntru_par_small);
    ntru_small.phase(phase, &ct_small);
    //rest = test_num % N;
    for(int j = 0; j < rest; ++j){
        errors[N * iterations + j] = phase[j];
    }  
    emp_mean = mean(errors, test_num);
    emp_var = variance(errors, test_num);
    emp_stddev = standard_deviation(emp_var); 
    std::cout << "    - empirical mean: " <<  emp_mean << std::endl;
    std::cout << "    - empirical variance: " <<  emp_var << std::endl;
    std::cout << "    - empirical stddev: " <<  emp_stddev << std::endl;
 
    delete(msg);
    // delete(ct);
    delete(errors);
    delete(phase);
}




void kdm_plain_ntru_test(int test_num){ 
    std::cout << "=== kdm_plain_ntru_test: Testing Error for Encryption === " << std::endl; 
    sample rand;
    // Prime number: 2**26 - 5
    long Q = 67108859;  
    // Prime number:  2**11 -9
    int N = 2039; 
    double stddev = 3.2;
    int t = 8;
    ntru_param ntru_par(cyclic, N, Q, any, stddev);
    ntru_sk ntru(ntru_par); 
    // Encryption the zero message in the NTRU ciphertext 
    long* msg = ntru.param.init_zero_poly();
    long* msg_scaled = ntru.param.init_zero_poly();
    long scale = Q/t;
    //long *ct = ntru.param.init_poly();
    ntru_ct ct; 
    long *dec = ntru.param.init_poly(); 
    long* errors = new long[test_num];
    //long *phase = ntru.param.init_poly();
    long *err = ntru.param.init_poly(); 
    int iterations = test_num/N;
    int correctness_test = 0; 
  
    for(int i = 0; i < iterations; ++i){ 
        // Here it would be good to encrypt a 
        rand.uniform_array(msg, N, t);   
        ntru.kdm_scale_and_encrypt(&ct, msg, t);     
        ntru.decrypt(dec, &ct, t);   
        utils::array_mod_form(dec, dec, ntru_par.N, t);   
        if(!utils::is_eq_poly(dec, msg, ntru_par.N)){   
            correctness_test++;   
        }  
        //ntru.phase(phase, ct); 
        // Here actually rounding the phase (calling decrypt) should give us the message msg. 
        // Now need to subtract scaled msg from phase! 
        utils::mul_scalar(msg_scaled, msg, N, scale); 
        //TODO: Here is a bug: I need to have msg in signed form
        utils::array_signed_form(msg_scaled, msg_scaled, N, Q);
        // phase - msg
        // ntru_par.sub(err, phase, msg_scaled);
        ntru.error(err, &ct, msg_scaled);
        for(int j = 0; j < N; ++j){ 
            errors[N * i + j] = err[j];
        } 
    }
    rand.uniform_array(msg, N, t);
    ntru.kdm_scale_and_encrypt(&ct, msg, t);   
    ntru.decrypt(dec, &ct, t); 
    utils::array_mod_form(dec, dec, ntru_par.N, t); 
    if(!utils::is_eq_poly(dec, msg, ntru_par.N)){
        correctness_test++;
    } 
    //ntru.phase(phase, ct);
    utils::mul_scalar(msg_scaled, msg, N, scale);
    utils::array_signed_form(msg_scaled, msg_scaled, N, Q);
    //ntru_par.sub(err, phase, msg_scaled);
    ntru.error(err, &ct, msg_scaled);
    int rest = test_num % N;
    for(int j = 0; j < rest; ++j){
        errors[N * iterations + j] = err[j];
    }   
    if(correctness_test>0){
        std::cout << "Correctness Check: Fail(" << correctness_test << ")" << std::endl;
        std::cout << "msg: " << utils::to_string(msg, N) << std::endl;
        std::cout << "dec: " << utils::to_string(dec, N) << std::endl;
    }else{
        std::cout << "Correctness Check: OK" << std::endl; 
    }

    double emp_mean = mean(errors, test_num);
    double emp_var = variance(errors, test_num);
    double emp_stddev = standard_deviation(emp_var); 
    std::cout << "    - empirical mean: " <<  emp_mean << std::endl;
    std::cout << "    - empirical variance: " <<  emp_var << std::endl;
    std::cout << "    - empirical stddev: " <<  emp_stddev << std::endl;


    std::cout << "=== kdm_plain_ntru_test: Testing Error for modulus switching === " << std::endl; 
    // Here I encrypt with the large modulus, modulus switch the ciphertext (nothing fancy)
    // Prime: 2**20 - 3
    long small_Q = 1048573;
    ntru_param ntru_par_small = ntru_par.mod_switch(small_Q);
    ntru_sk ntru_small = ntru.mod_switch(small_Q);
    ntru_ct ct_small;
    long small_scale = small_Q/t;
    correctness_test = 0; 
    for(int i = 0; i < iterations; ++i){ 
        rand.uniform_array(msg, N, t); 
        ntru.kdm_scale_and_encrypt(&ct, msg, t);  
        // ntru_sk::switch_modulus(ct_small, ct, ntru_par_small, ntru_par);
        ct_small = ct.mod_switch(ntru_par_small);
        ntru_small.decrypt(dec, &ct_small, t); 
        utils::array_mod_form(dec, dec, ntru_par_small.N, t);   
        if(!utils::is_eq_poly(dec, msg, ntru_par_small.N)){ 
            correctness_test++; 
        }   
        // Modulus switch the ciphertext 
        //ntru_small.phase(phase, ct_small);
        utils::mul_scalar(msg_scaled, msg, N, small_scale);
        utils::array_signed_form(msg_scaled, msg_scaled, N, small_Q);
        //ntru_par_small.sub(err, phase, msg_scaled);
        ntru.error(err, &ct_small, msg_scaled);
        for(int j = 0; j < N; ++j){ 
            errors[N * i + j] = err[j];
        } 
    }
    rand.uniform_array(msg, N, t);
    ntru.kdm_scale_and_encrypt(&ct, msg, t);  
    // ntru_sk::switch_modulus(ct_small, ct, ntru_par_small, ntru_par); 
    ct_small = ct.mod_switch(ntru_par_small);
    ntru_small.decrypt(dec, &ct_small, t);
    utils::array_mod_form(dec, dec, ntru_par_small.N, t);  
    if(!utils::is_eq_poly(dec, msg, ntru_par_small.N)){
        correctness_test++;
    }  
    // Lets check  
    //ntru_small.phase(phase, ct_small); 
    utils::mul_scalar(msg_scaled, msg, N, small_scale);
    utils::array_signed_form(msg_scaled, msg_scaled, N, small_Q);

    // std::cout << "small_scale: " << small_scale << std::endl;
    // std::cout << "msg: " << utils::to_string(msg, N) << std::endl << std::endl;
    // std::cout << "msg_scaled: " << utils::to_string(msg_scaled, N) << std::endl << std::endl;
    // std::cout << "phase: " << utils::to_string(phase, N) << std::endl << std::endl; 
    //ntru_par_small.sub(err, phase, msg_scaled);
    ntru.error(err, &ct_small, msg_scaled);
    // std::cout << "err: " << utils::to_string(err, rest) << std::endl;
    for(int j = 0; j < rest; ++j){
        errors[N * iterations + j] = err[j];
    }  
    if(correctness_test>0){
        std::cout << "Correctness Check: Fail(" << correctness_test << ")" << std::endl;
        std::cout << "msg: " << utils::to_string(msg, N) << std::endl;
        std::cout << "dec: " << utils::to_string(dec, N) << std::endl;
    }else{
        std::cout << "Correctness Check: OK" << std::endl; 
    }
    emp_mean = mean(errors, test_num);
    emp_var = variance(errors, test_num);
    emp_stddev = standard_deviation(emp_var); 
    std::cout << "    - empirical mean: " <<  emp_mean << std::endl;
    std::cout << "    - empirical variance: " <<  emp_var << std::endl;
    std::cout << "    - empirical stddev: " <<  emp_stddev << std::endl;


    std::cout << "=== kdm_plain_ntru_test: Second Modulus Switching === " << std::endl; 
    // Here we do the encryption with ntru_small! So all the modulus switching etc. is done in the background
    // Prime: 2**18 - 5
    small_Q = 262139;
    small_scale = small_Q/t;
    ntru_par_small = ntru_par.mod_switch(small_Q);
    ntru_small = ntru.mod_switch(small_Q); 
    correctness_test = 0;
    for(int i = 0; i < iterations; ++i){ 
        rand.uniform_array(msg, N, t);
        ntru_small.kdm_scale_and_encrypt(&ct, msg, t);   
        ntru_small.decrypt(dec, &ct, t); 
        utils::array_mod_form(dec, dec, ntru_par_small.N, t);   
        if(!utils::is_eq_poly(dec, msg, ntru_par_small.N)){ 
            correctness_test++; 
        }   
        // ntru_small.phase(phase, ct);
        utils::mul_scalar(msg_scaled, msg, N, small_scale);
        utils::array_signed_form(msg_scaled, msg_scaled, N, small_Q);
        // ntru_par_small.sub(err, phase, msg_scaled); 
        ntru.error(err, &ct, msg_scaled);
        for(int j = 0; j < N; ++j){ 
            errors[N * i + j] = err[j];
        } 
    }
    rand.uniform_array(msg, N, t);
    ntru_small.kdm_scale_and_encrypt(&ct, msg, t);   
    ntru_small.decrypt(dec, &ct, t); 
    utils::array_mod_form(dec, dec, ntru_par_small.N, t);   
    if(!utils::is_eq_poly(dec, msg, ntru_par_small.N)){ 
        correctness_test++; 
    }   
    //ntru_small.phase(phase, ct);
    utils::mul_scalar(msg_scaled, msg, N, small_scale);
    utils::array_signed_form(msg_scaled, msg_scaled, N, small_Q);
    //ntru_par_small.sub(err, phase, msg_scaled); 
    ntru.error(err, &ct, msg_scaled);
    //rest = test_num % N;
    for(int j = 0; j < rest; ++j){
        errors[N * iterations + j] = err[j];
    }  
    if(correctness_test>0){
        std::cout << "Correctness Check: Fail(" << correctness_test << ")" << std::endl;
        std::cout << "msg: " << utils::to_string(msg, N) << std::endl;
        std::cout << "dec: " << utils::to_string(dec, N) << std::endl;
    }else{
        std::cout << "Correctness Check: OK" << std::endl; 
    }
    emp_mean = mean(errors, test_num);
    emp_var = variance(errors, test_num);
    emp_stddev = standard_deviation(emp_var); 
    std::cout << "    - empirical mean: " <<  emp_mean << std::endl;
    std::cout << "    - empirical variance: " <<  emp_var << std::endl;
    std::cout << "    - empirical stddev: " <<  emp_stddev << std::endl;


    std::cout << "=== kdm_plain_ntru_test: Switch to power of two 2**20 === " << std::endl; 
    // Prime: 2**20  
    small_Q = 1048576; 
    small_scale = small_Q/t;
    ntru_par_small = ntru_par.mod_switch(small_Q);
    ntru_small = ntru.mod_switch(small_Q); 
    correctness_test = 0;
    for(int i = 0; i < iterations; ++i){ 
        rand.uniform_array(msg, N, t);
        ntru_small.kdm_scale_and_encrypt(&ct, msg, t);   
        ntru_small.decrypt(dec, &ct, t); 
        utils::array_mod_form(dec, dec, ntru_par_small.N, t);   
        if(!utils::is_eq_poly(dec, msg, ntru_par_small.N)){ 
            correctness_test++; 
        }   
        //ntru_small.phase(phase, ct);
        utils::mul_scalar(msg_scaled, msg, N, small_scale);
        utils::array_signed_form(msg_scaled, msg_scaled, N, small_Q);
        //ntru_par_small.sub(err, phase, msg_scaled); 
        ntru.error(err, &ct, msg_scaled);
        for(int j = 0; j < N; ++j){ 
            errors[N * i + j] = err[j];
        } 
    }
    rand.uniform_array(msg, N, t);
    ntru_small.kdm_scale_and_encrypt(&ct, msg, t);   
    ntru_small.decrypt(dec, &ct, t); 
    utils::array_mod_form(dec, dec, ntru_par_small.N, t);   
    if(!utils::is_eq_poly(dec, msg, ntru_par_small.N)){ 
        correctness_test++; 
    }   
    //ntru_small.phase(phase, ct);
    utils::mul_scalar(msg_scaled, msg, N, small_scale);
    utils::array_signed_form(msg_scaled, msg_scaled, N, small_Q);
    //ntru_par_small.sub(err, phase, msg_scaled); 
    ntru.error(err, &ct, msg_scaled);
    //rest = test_num % N;
    for(int j = 0; j < rest; ++j){
        errors[N * iterations + j] = err[j];
    }  
    if(correctness_test>0){
        std::cout << "Correctness Check: Fail(" << correctness_test << ")" << std::endl;
        std::cout << "msg: " << utils::to_string(msg, N) << std::endl;
        std::cout << "dec: " << utils::to_string(dec, N) << std::endl;
    }else{
        std::cout << "Correctness Check: OK" << std::endl; 
    }
    emp_mean = mean(errors, test_num);
    emp_var = variance(errors, test_num);
    emp_stddev = standard_deviation(emp_var); 
    std::cout << "    - empirical mean: " <<  emp_mean << std::endl;
    std::cout << "    - empirical variance: " <<  emp_var << std::endl;
    std::cout << "    - empirical stddev: " <<  emp_stddev << std::endl;
  
    delete(msg);
    // delete(ct);
    delete(errors);
    // delete(phase);
}




void mod_switch_keys_only(){ 
    std::cout << "=== mod_switch_keys_only === " << std::endl;

    // Prime number: 2**26 - 5
    long Q = 67108859;
    // Prime number:  2**11 -9
    int N = 2039;
    //int N = 21;
    double stddev = 3.2;
    ntru_param ntru_par(cyclic, N, Q, any, stddev);
    ntru_sk ntru(ntru_par); 
    long *key = ntru.f;
    long *inv_key = ntru.inv_f;

    long *out = new long[ntru_par.N];
    utils::mul_mod(out, key, ntru_par.N, inv_key, ntru_par.N, ntru_par.N, ntru_par.Q, ntru_par.ring);
    //std::cout << "key * inv_key mod Q: " << utils::to_string(out, ntru_par.N) << std::endl;
     
    // Prime: 2**20 - 3
    long small_Q = 1048573;
    // Prime: 2**18 - 5
    small_Q = 262139;
    ntru_param ntru_par_small = ntru_par.mod_switch(small_Q);
    long *inv_key_scaled = ntru_par_small.init_poly();
    double temp;
    for(int i = 0; i < ntru_par.N; ++i){
        temp = (double)inv_key[i] * small_Q;
        inv_key_scaled[i] = (long)round(temp/Q);
    }
    utils::mul_mod(out, key, ntru_par_small.N, inv_key_scaled, ntru_par_small.N, ntru_par_small.N, ntru_par_small.Q, ntru_par.ring);
    utils::array_signed_form(out, out, ntru_par_small.N, ntru_par_small.Q);
    //std::cout << "key: " << utils::to_string(out, ntru_par.N) << std::endl;

    double emp_mean = mean(out, ntru_par_small.N);
    double emp_var = variance(out, ntru_par_small.N);
    double emp_stddev = standard_deviation(emp_var); 
    std::cout << "    - empirical mean: " <<  emp_mean << std::endl;
    std::cout << "    - empirical variance: " <<  emp_var << std::endl;
    std::cout << "    - empirical stddev: " <<  emp_stddev << std::endl;
}


void bogus_power_of_two_modulus_switch_tests(int test_num){ 
    std::cout << "=== bogus_power_of_two_modulus_switch_tests: Testing Error for Encryption === " << std::endl;  
    // Power of two: 2**30
    long Q_pot = 1073741824;
    // Prime: 2**30 + 3
    long Q_plus = Q_pot+3; 
    // Prime number: 2**25 - 39
    long Q = 33554393;
    // Prime: Q_pot-35
    //long Q = Q_pot-35;
    // Prime number:  2**11 -9
    int N = 2039;
    //int N = 21;
    double stddev = 3.2;
 
    ntru_param ntru_par_plus(cyclic, N, Q_plus, any, stddev);
    ntru_sk ntru_plus(ntru_par_plus); 
    ntru_param ntru_par_pot = ntru_par_plus.mod_switch(Q_pot);
    ntru_param ntru_par = ntru_par_plus.mod_switch(Q);
    ntru_sk ntru_pot = ntru_plus.mod_switch(Q_pot);
    ntru_sk ntru = ntru_plus.mod_switch(Q);
 
    // Encryption the zero message in the NTRU ciphertext 
    long* msg_pot = ntru_par_pot.init_zero_poly();
    //long *ct_pot = ntru_par_pot.init_poly(); 
    ntru_ct ct_pot;
    //long *ct = ntru_par.init_poly(); 
    ntru_ct ct;
    long* errors = new long[test_num];
    long *phase = ntru.param.init_poly();
    long *dec = ntru.param.init_poly();
    int iterations = test_num/N;
    int t = 8;
    int correctness_test = 0;
    for(int i = 0; i < iterations; ++i){ 
        ntru_pot.encrypt(&ct_pot, msg_pot);  
        //ntru_sk::switch_modulus(ct, ct_pot, ntru_par, ntru_par_pot);
        ct = ct_pot.mod_switch(ntru_par);
        ntru.phase(phase, &ct); 
        for(int j = 0; j < N; ++j){ 
            errors[N * i + j] = phase[j];
        } 
        // Decrypt for t = 2 - in this test it doesn't matter because the decryption should be 0 anyway
        ntru.decrypt(dec, &ct, t); 
        if(!utils::is_eq_poly(dec, msg_pot, ntru_par.N)){
            correctness_test++;
        }
    }
    ntru_pot.encrypt(&ct_pot, msg_pot);  
    //ntru_sk::switch_modulus(ct, ct_pot, ntru_par, ntru_par_pot);
    ct = ct_pot.mod_switch(ntru_par);
    ntru.phase(phase, &ct);
    int rest = test_num % N;
    for(int j = 0; j < rest; ++j){
        errors[N * iterations + j] = phase[j];
    }  
    // Decrypt for t = 2 - in this test it doesn't matter because the decryption should be 0 anyway
    ntru.decrypt(dec, &ct, t); 
    if(!utils::is_eq_poly(dec, msg_pot, ntru_par.N)){
        correctness_test++;
        // std::cout << "dec: " << utils::to_string(dec, ntru_par.N) << std::endl;
    }
    if(correctness_test >0){
        std::cout << "Correctness test: Fail (" << correctness_test << ")" << std::endl;
    }else{
        std::cout << "Correctness test: OK" << std::endl;
    }
    double emp_mean = mean(errors, test_num);
    double emp_var = variance(errors, test_num);
    double emp_stddev = standard_deviation(emp_var); 
    std::cout << "    - empirical mean: " <<  emp_mean << std::endl;
    std::cout << "    - empirical variance: " <<  emp_var << std::endl;
    std::cout << "    - empirical stddev: " <<  emp_stddev << std::endl;
 
}
 

void correct_power_of_two_modulus_switch_tests(int test_num){ 
    std::cout << "=== correct_power_of_two_modulus_switch_tests: Testing Error for Encryption === " << std::endl;  
    // Power of two: 2**30
    long Q_pot = 1073741824;
    // Prime: 2**30 + 3
    long Q_plus = Q_pot+3; 
    // Prime number: 2**25 - 39
    long Q = 33554393;
    // Prime: Q_pot-35
    //long Q = Q_pot-35;
    // Prime number:  2**11 -9
    int N = 2039;
    //int N = 21;
    double stddev = 3.2;
 
    ntru_param ntru_par_plus(cyclic, N, Q_plus, any, stddev);
    ntru_sk ntru_plus(ntru_par_plus); 
    ntru_param ntru_par_pot = ntru_par_plus.mod_switch(Q_pot);
    ntru_param ntru_par = ntru_par_plus.mod_switch(Q);
    ntru_sk ntru_pot = ntru_plus.mod_switch(Q_pot);
    ntru_sk ntru = ntru_plus.mod_switch(Q);
 
    // Encryption the zero message in the NTRU ciphertext 
    long* msg_zero = ntru_par_plus.init_zero_poly();
    //long *ct_plus = ntru_par_plus.init_poly();  
    ntru_ct ct_plus;
    //long *ct_pot = ntru_par_pot.init_poly(); 
    ntru_ct ct_pot;
    //long *ct = ntru_par.init_poly(); 
    ntru_ct ct;
    long* errors = new long[test_num];
    long *phase = ntru.param.init_poly();
    long *dec = ntru.param.init_poly();
    int iterations = test_num/N;
    int t = 8;
    int correctness_test = 0;
    for(int i = 0; i < iterations; ++i){ 
        ntru_plus.encrypt(&ct_plus, msg_zero);
        //ntru_sk::switch_modulus(ct_pot, ct_plus, ntru_par_pot, ntru_par_plus); 
        ct_pot = ct_plus.mod_switch(ntru_par_pot);
        //ntru_sk::switch_modulus(ct, ct_pot, ntru_par, ntru_par_pot);
        ct = ct_pot.mod_switch(ntru_par);
        ntru.phase(phase, &ct); 
        for(int j = 0; j < N; ++j){ 
            errors[N * i + j] = phase[j];
        } 
        // Decrypt for t = 2 - in this test it doesn't matter because the decryption should be 0 anyway
        ntru.decrypt(dec, &ct, t); 
        if(!utils::is_eq_poly(dec, msg_zero, ntru_par.N)){
            correctness_test++;
        }
    }
    ntru_plus.encrypt(&ct_plus, msg_zero);
    //ntru_sk::switch_modulus(ct_pot, ct_plus, ntru_par_pot, ntru_par_plus); 
    ct_pot = ct_plus.mod_switch(ntru_par_pot);
    //ntru_sk::switch_modulus(ct, ct_pot, ntru_par, ntru_par_pot);
    ct = ct_pot.mod_switch(ntru_par);
    ntru.phase(phase, &ct); 
    int rest = test_num % N; 
    for(int j = 0; j < rest; ++j){ 
        errors[N * iterations + j] = phase[j];
    }  
    // Decrypt for t = 2 - in this test it doesn't matter because the decryption should be 0 anyway
    ntru.decrypt(dec, &ct, t); 
    if(!utils::is_eq_poly(dec, msg_zero, ntru_par.N)){
        correctness_test++;
        // std::cout << "dec: " << utils::to_string(dec, ntru_par.N) << std::endl;
    }
    if(correctness_test >0){
        std::cout << "Correctness test: Fail (" << correctness_test << ")" << std::endl;
    }else{
        std::cout << "Correctness test: OK" << std::endl;
    }
    double emp_mean = mean(errors, test_num);
    double emp_var = variance(errors, test_num);
    double emp_stddev = standard_deviation(emp_var); 
    std::cout << "    - empirical mean: " <<  emp_mean << std::endl;
    std::cout << "    - empirical variance: " <<  emp_var << std::endl;
    std::cout << "    - empirical stddev: " <<  emp_stddev << std::endl;
 
    std::cout << "=== correct_power_of_two_modulus_switch_tests: Testing power of two encryption" << std::endl;
    // In this test directly encrypt in ntru_pot - in actuallity its encrypted mod Q_plus, 
    // mod switched to Q_pot and the message is then added to the resulting ciphertext mod Q_pot.
    // But all is under the hood.
    for(int i = 0; i < iterations; ++i){ 
        //ntru_plus.encrypt(ct_plus, msg_zero);
        ntru_pot.encrypt(&ct_pot, msg_zero);
        //ntru_sk::switch_modulus(ct_pot, ct_plus, ntru_par_pot, ntru_par_plus); 
        //ntru_sk::switch_modulus(ct, ct_pot, ntru_par, ntru_par_pot);
        ct = ct_pot.mod_switch(ntru_par);
        ntru.phase(phase, &ct); 
        for(int j = 0; j < N; ++j){ 
            errors[N * i + j] = phase[j];
        } 
        // Decrypt for t = 2 - in this test it doesn't matter because the decryption should be 0 anyway
        ntru.decrypt(dec, &ct, t); 
        if(!utils::is_eq_poly(dec, msg_zero, ntru_par.N)){
            correctness_test++;
        }
    }
    ntru_plus.encrypt(&ct_plus, msg_zero);
    //ntru_sk::switch_modulus(ct_pot, ct_plus, ntru_par_pot, ntru_par_plus); 
    ct_pot = ct_plus.mod_switch(ntru_par_pot);
    //ntru_sk::switch_modulus(ct, ct_pot, ntru_par, ntru_par_pot);
    ct = ct_pot.mod_switch(ntru_par);
    ntru.phase(phase, &ct); 
    rest = test_num % N; 
    for(int j = 0; j < rest; ++j){ 
        errors[N * iterations + j] = phase[j];
    }  
    // Decrypt for t = 2 - in this test it doesn't matter because the decryption should be 0 anyway
    ntru.decrypt(dec, &ct, t); 
    if(!utils::is_eq_poly(dec, msg_zero, ntru_par.N)){
        correctness_test++;
        // std::cout << "dec: " << utils::to_string(dec, ntru_par.N) << std::endl;
    }
    if(correctness_test >0){
        std::cout << "Correctness test: Fail (" << correctness_test << ")" << std::endl;
    }else{
        std::cout << "Correctness test: OK" << std::endl;
    }
    emp_mean = mean(errors, test_num);
    emp_var = variance(errors, test_num);
    emp_stddev = standard_deviation(emp_var); 
    std::cout << "    - empirical mean: " <<  emp_mean << std::endl;
    std::cout << "    - empirical variance: " <<  emp_var << std::endl;
    std::cout << "    - empirical stddev: " <<  emp_stddev << std::endl;
  
}


void gadget_ntru_errors_test(int test_num){
    std::cout << "=== gadget_ntru_errors_test: Testing Error for Encryption and Multiplication=== " << std::endl;  
 
    // Prime number: 2**25 - 39
    long Q = 33554393; 
    // Prime number:  2**11 -9
    int N = 2039;
    //int N = 21;
    double stddev = 3.2;
  
    ntru_param ntru_par(cyclic, N, Q, any, stddev);
    ntru_sk ntru(ntru_par);
 
    // Gadget Parameters
    int basis = 16;
    ntru_gadget_param ntru_g_par(ntru_par, basis, double_fft);
    gadget_ntru g_ntru(ntru_g_par, ntru);

    // Encryption the zero message in the NTRU ciphertext 
    long* g_msg = ntru_g_par.param.init_zero_poly();
    //g_msg[0] = 1;
    //fftw_complex** g_ct_fft = ntru_g_par.init_gadget_ct_fft();
    //long** g_ct = ntru_g_par.init_gadget_ct();
    ntru_gadget_ct g_ct_fft;
    
    long* msg = ntru.param.init_zero_poly();
    //long *ct = ntru.param.init_poly(); 
    ntru_ct ct;
    //long *out_ct = ntru.param.init_poly();
    ntru_ct out_ct; 
    long *dec = ntru.param.init_poly(); 
    long* errors = new long[test_num];
    long *phase = ntru.param.init_poly();
    int iterations = test_num/N; 
    int t = 8;
    int correctness_test = 0;
    for(int i = 0; i < iterations; ++i){ 
        ntru.encrypt(&ct, msg);   
        g_ct_fft = g_ntru.gadget_encrypt(g_msg);
        g_ct_fft.gadget_mul(&out_ct, &ct);
        ntru.phase(phase, &out_ct); 
        for(int j = 0; j < N; ++j){ 
            errors[N * i + j] = phase[j];
        } 
        ntru.decrypt(dec, &out_ct, t); 
        if(!utils::is_eq_poly(dec, msg, ntru_par.N)){
            correctness_test++; 
        }
    }
    ntru.encrypt(&ct, msg);  
    g_ct_fft = g_ntru.gadget_encrypt(g_msg);
    g_ct_fft.gadget_mul(&out_ct, &ct);
    ntru.phase(phase, &out_ct); 
    int rest = test_num % N;
    for(int j = 0; j < rest; ++j){
        errors[N * iterations + j] = phase[j];
    }  
    ntru.decrypt(dec, &out_ct, t); 
    if(!utils::is_eq_poly(dec, msg, ntru_par.N)){
        correctness_test++;
        std::cout << "dec: " << utils::to_string(dec, ntru_g_par.param.N) << std::endl;
    }
    if(correctness_test >0){
        std::cout << "Correctness test: Fail (" << correctness_test << ")" << std::endl;
        std::cout << "Number of Multiplications: " << iterations+1 << std::endl; 
    }else{
        std::cout << "Correctness test: OK" << std::endl;
    }
    double emp_mean = mean(errors, test_num);
    double emp_var = variance(errors, test_num);
    double emp_stddev = standard_deviation(emp_var); 
    std::cout << "    - empirical mean: " <<  emp_mean << std::endl;
    std::cout << "    - empirical variance: " <<  emp_var << std::endl;
    std::cout << "    - empirical stddev: " <<  emp_stddev << std::endl;

}

 
void gadget_ntru_power_of_two_errors_test(int test_num){
    std::cout << "=== gadget_ntru_power_of_two_errors_test: Testing Error for Encryption, Mod Switch and Multiplication === " << std::endl;  
    // Prime: 2**30 - 35
    long Q = 1073741789;
    // 2**11 - 9
    int N = 2039; 
    double stddev = 3.2;
    ntru_param ntru_par(cyclic, N, Q, any, stddev);
    ntru_sk ntru(ntru_par); 
    // Gadget Parameters
    int basis = 16;
    ntru_gadget_param ntru_g_par(ntru_par, basis, double_fft);
    gadget_ntru g_ntru(ntru_g_par, ntru);

    // Encryption the zero message in the NTRU ciphertext 
    long* g_msg = ntru_g_par.param.init_zero_poly();
    //g_msg[0] = 1;
    //fftw_complex** g_ct = ntru_g_par.init_gadget_ct_fft();
    ntru_gadget_ct g_ct;
    long* msg = ntru.param.init_zero_poly();
    // long *ct = ntru.param.init_poly(); 
    ntru_ct ct;
    //long *out_ct = ntru.param.init_poly(); 
    ntru_ct out_ct;
    long *dec = ntru.param.init_poly(); 
    long* errors = new long[test_num];
    long *phase = ntru.param.init_poly();
    int iterations = test_num/N; 
    int t = 8;
    int correctness_test = 0;
    for(int i = 0; i < iterations; ++i){ 
        ntru.encrypt(&ct, msg);  
        g_ct = g_ntru.gadget_encrypt(g_msg);
        g_ct.gadget_mul(&out_ct, &ct);
        ntru.phase(phase, &out_ct); 
        for(int j = 0; j < N; ++j){ 
            errors[N * i + j] = phase[j];
        } 
        ntru.decrypt(dec, &out_ct, t); 
        if(!utils::is_eq_poly(dec, msg, ntru_par.N)){
            correctness_test++;
        }
    }
    ntru.encrypt(&ct, msg);  
    g_ct = g_ntru.gadget_encrypt(g_msg);
    g_ct.gadget_mul(&out_ct, &ct);
    ntru.phase(phase, &out_ct); 
    int rest = test_num % N;
    for(int j = 0; j < rest; ++j){
        errors[N * iterations + j] = phase[j];
    }  
    ntru.decrypt(dec, &out_ct, t); 
    if(!utils::is_eq_poly(dec, msg, ntru_par.N)){
        correctness_test++;
    }
    if(correctness_test >0){
        std::cout << "Correctness test: Fail (" << correctness_test << ")" << std::endl;
        std::cout << "Number of Multiplications: " << iterations+1 << std::endl; 
    }else{
        std::cout << "Correctness test: OK" << std::endl;
    }
    double emp_mean = mean(errors, test_num);
    double emp_var = variance(errors, test_num);
    double emp_stddev = standard_deviation(emp_var); 
    std::cout << "    - empirical mean: " <<  emp_mean << std::endl;
    std::cout << "    - empirical variance: " <<  emp_var << std::endl;
    std::cout << "    - empirical stddev: " <<  emp_stddev << std::endl; 
} 




void power_of_two_gadget_ntru_times_kdm_ntru_test(int test_num){
    std::cout << "=== power_of_two_gadget_ntru_times_kdm_ntru_test === " << std::endl;  
    // I should start with Q_plus
    // Get ntru_par by mod switching
    // Gadget NTRU from ntru_par (its gonna be mod switched in the background)
    // Encrypt random KDM messages
    // Gadget Encrypt bits
    // If bit was 0, then I check with zero polynomials, if 1, then I check with msg polynomial

    sample rand;
    // Prime: 2**30  
    long Q = 1073741824;  
    Q =  Q-35;
    // O_plus = Q+3  
    long Q_plus = 1073741827;  
    // Q_plus = 2**31 - 1
    Q_plus = 2147483647;
    // 2**11 - 9
    int N = 2039;  
    double stddev = 3.2; 
    ntru_param ntru_par_plus(cyclic, N, Q_plus, any, stddev);
    ntru_sk ntru_plus(ntru_par_plus); 

    ntru_param ntru_par = ntru_par_plus.mod_switch(Q);
    ntru_sk ntru = ntru_plus.mod_switch(Q); 
    //ntru_param ntru_par(cyclic, N, Q, any, stddev);
    //ntru_sk ntru(ntru_par); 

    // Gadget Parameters
    int basis = 16;
    ntru_gadget_param ntru_g_par(ntru_par, basis, double_fft);
    gadget_ntru g_ntru(ntru_g_par, ntru);

    // Encryption the zero message in the NTRU ciphertext 
    long* g_msg = ntru_g_par.param.init_zero_poly();
    //g_msg[0] = 1;
    //fftw_complex** g_ct = ntru_g_par.init_gadget_ct_fft();
    ntru_gadget_ct g_ct;
    long* msg = ntru.param.init_zero_poly();
    long* msg_scaled = ntru.param.init_poly();
    long* exp_msg = ntru.param.init_poly();
    long *err = ntru.param.init_poly(); 
    //long *ct = ntru.param.init_poly(); 
    ntru_ct ct;
    //long *out_ct = ntru.param.init_poly(); 
    ntru_ct out_ct;
    long *dec = ntru.param.init_poly(); 
    long* errors = new long[test_num];
    //long *phase = ntru.param.init_poly();
    int iterations = test_num/N; 
    int t = 8;
    long scale = Q/t;
    int correctness_test = 0;
    for(int i = 0; i < iterations; ++i){ 
        rand.uniform_array(msg, N, t); 
        ntru.kdm_scale_and_encrypt(&ct, msg, t);  
        g_msg[0] = rand.binary();
        g_msg[0] = 0;
        g_ct = g_ntru.gadget_encrypt(g_msg);
        g_ct.gadget_mul(&out_ct, &ct);
        // Need to check whether it decrypts correctly.
        ntru.decrypt(dec, &out_ct, t);
        utils::array_mod_form(dec, dec, ntru_par.N, t);   
        utils::mul_scalar(exp_msg, msg, N, g_msg[0]);
        if(!utils::is_eq_poly(exp_msg, dec, N)){
            correctness_test++;
        }
        // Compute the error
        //ntru.phase(phase, out_ct);   
        //utils::array_signed_form(phase, phase, N, Q); 
        utils::mul_scalar(msg_scaled, exp_msg, N, scale);  
        utils::array_signed_form(msg_scaled, msg_scaled, N, Q); 
        //ntru_par.sub(err, phase, msg_scaled);
        ntru.error(err, &out_ct, msg_scaled);
        for(int j = 0; j < N; ++j){ 
            errors[N * i + j] = err[j];
        } 
    }
    int rest = test_num % N;
    rand.uniform_array(msg, N, t); 
    ntru.kdm_scale_and_encrypt(&ct, msg, t);  
    g_msg[0] = rand.binary();
    g_msg[0] = 0;
    std::cout << "Gadget Encryption...." << std::endl;
    std::cout << "g_msg[0]" << g_msg[0] << std::endl;
    std::cout << "iterations: " << iterations << std::endl;
    g_ct = g_ntru.gadget_encrypt(g_msg);
    g_ct.gadget_mul(&out_ct, &ct);
    // Need to check whether it decrypts correctly.
    ntru.decrypt(dec, &out_ct, t);
    utils::array_mod_form(dec, dec, ntru_par.N, t);   
    // Need dec in mod form
    utils::mul_scalar(exp_msg, msg, N, g_msg[0]);
    if(!utils::is_eq_poly(exp_msg, dec, N)){
        correctness_test++;
    }
    // Compute the error
    //ntru.phase(phase, out_ct);   
    //utils::array_signed_form(phase, phase, N, Q); 
    //std::cout << "phase: " << utils::to_string(phase, N) << std::endl;
    utils::mul_scalar(msg_scaled, exp_msg, N, scale);  
    utils::array_signed_form(msg_scaled, msg_scaled, N, Q); 
    //ntru_par.sub(err, phase, msg_scaled);
    ntru.error(err, &out_ct, msg_scaled);
    //std::cout << "g_msg[0]: " << g_msg[0] << std::endl;
    //std::cout << "err: " << utils::to_string(err, N) << std::endl;
    for(int j = 0; j < rest; ++j){
        errors[N * iterations + j] = err[j];
    }   
    if(correctness_test >0){
        std::cout << "Correctness test: Fail (" << correctness_test << ")" << std::endl;
        std::cout << "Number of Multiplications: " << iterations+1 << std::endl; 
        std::cout << "msg: " << utils::to_string(msg, N) << std::endl;
        std::cout << "exp_msg: " << utils::to_string(exp_msg, N) << std::endl;
        std::cout << "g_msg" << utils::to_string(g_msg, N) << std::endl;
        std::cout << "dec: " << utils::to_string(dec, N) << std::endl;
    }else{
        std::cout << "Correctness test: OK" << std::endl;
    }
    double emp_mean = mean(errors, test_num);
    double emp_var = variance(errors, test_num);
    double emp_stddev = standard_deviation(emp_var); 
    std::cout << "    - empirical mean: " <<  emp_mean << std::endl;
    std::cout << "    - empirical variance: " <<  emp_var << std::endl;
    std::cout << "    - empirical stddev: " <<  emp_stddev << std::endl; 
} 

int main(){

    //plain_lwe_test(5000);
    //plain_ntru_test(20000); 
    kdm_plain_ntru_test(2000);
/*
    mod_switch_keys_only(); 
    bogus_power_of_two_modulus_switch_tests(10000);
    correct_power_of_two_modulus_switch_tests(10000);


    // Computing for 1048576 = 2**20 error coefficients
    // NOTE: When doing fewer tests, I get a mean that is actually quite far from 0. 
    // For more tests it I get a mean close to 0.
    // That is most likely due to the fact that power of two decomposition will not realy give me uniformly random polynomials.
    // They will be uniformaly random conditioned that the sign of the coefficient is the same.  
*/
    gadget_ntru_errors_test(1048576);
    gadget_ntru_power_of_two_errors_test(1048576);
    power_of_two_gadget_ntru_times_kdm_ntru_test(1048576);
}