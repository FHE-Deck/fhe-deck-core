#include <iostream>
#include "../include/rlwe_param.h"
#include "../include/rlwe.h"
#include "../include/utils.h"

void rlwe_test(int test_num){
    std::cout << "=========== rlwe_test ========= " << std::endl;

    int N = 4096;
    int Q = 268435456;
    int t = 13;
    sample rand;
    rlwe_param rlwe_par(negacyclic, N, Q, ternary, any, 3.2);
    rlwe_sk sk(rlwe_par);
    //std::cout << "rlwe_par.init_zero_poly();" << std::endl;
    long* m = rlwe_par.init_zero_poly();
    rand.uniform_array(m, N, t);
    //std::cout << "sk.scale_and_encrypt(m, t);" << std::endl;
    rlwe_ct ct = sk.scale_and_encrypt(m, t);
    //std::cout << "sk.decrypt(ct, t);" << std::endl;
    long* out = rlwe_par.init_poly();
    //sk.decrypt(&ct, t);
    //utils::array_mod_form(out, out, N, t);
    //std::cout << "out: " << utils::to_string(out, rlwe_par.N) << std::endl;  
    //std::cout << "m: " << utils::to_string(m, rlwe_par.N) << std::endl;  

    bool test = true;
    for(int i = 0; i < test_num; ++i){
        rand.uniform_array(m, N, t);
        rlwe_ct ct = sk.scale_and_encrypt(m, t);
        sk.decrypt(out, &ct, t);
        utils::array_mod_form(out, out, N, t);
        if(!utils::is_eq_poly(out, m, N)){
            std::cout << "rlwe_test: Fail" << std::endl;
            std::cout << "out: " << utils::to_string(out, rlwe_par.N) << std::endl;  
            std::cout << "m: " << utils::to_string(m, rlwe_par.N) << std::endl;  
            test = false;
        }
    }
    if(test){
        std::cout << "rlwe_test: OK" << std::endl;
    } 

    bool add_test = true;
    long* m_1 = rlwe_par.init_zero_poly();
    long* m_2 = rlwe_par.init_zero_poly();
    long* exp = rlwe_par.init_zero_poly();
    for(int i = 0; i < test_num; ++i){
        rand.uniform_array(m_1, N, t);
        rand.uniform_array(m_2, N, t);
        for(int i = 0; i < N; ++i){
            exp[i] = (m_1[i] + m_2[i]) % t;
        }
        rlwe_ct ct_1 = sk.scale_and_encrypt(m_1, t);
        rlwe_ct ct_2 = sk.scale_and_encrypt(m_2, t); 
        rlwe_ct ct_3;
        ct_1.add(&ct_3, &ct_2); 
        sk.decrypt(out, &ct_3, t); 
        utils::array_mod_form(out, out, N, t); 
        if(!utils::is_eq_poly(out, exp, N)){
            std::cout << "rlwe ADD test: Fail" << std::endl;
            std::cout << "out: " << utils::to_string(out, rlwe_par.N) << std::endl;  
            std::cout << "exp: " << utils::to_string(exp, rlwe_par.N) << std::endl;  
            add_test = false;
        }
    }
    if(add_test){
        std::cout << "rlwe ADD test: OK" << std::endl;
    } 

}




void gadget_rlwe_basic_test(int test_num, gadget_mul_mode mode){
    std::cout << "gadget_rlwe_basic_test" << std::endl;
    int N = 512;
    int Q = 67108864;
    int t = 13; 
    sample rand;
    rlwe_param rlwe_par(negacyclic, N, Q, ternary, any, 3.2);
    rlwe_sk sk(rlwe_par);
    int basis = 8;
    rlwe_gadget_param gadget_rlwe_par(rlwe_par, basis, 0.0);
    gadget_rlwe_sk gadget_sk(gadget_rlwe_par, sk);

    long* m = rlwe_par.init_zero_poly(); 
    long* out = rlwe_par.init_poly();
    long* gadget_m = rlwe_par.init_zero_poly();
    long* exp_poly = rlwe_par.init_poly();
   
    bool test = true;
    for(int i = 0; i < test_num; ++i){
        rand.uniform_array(m, N, t);
        rand.uniform_array(gadget_m, N, t);  
        utils::mul_mod(exp_poly, m, N, gadget_m, N, N, t, negacyclic);
        rlwe_ct ct = sk.scale_and_encrypt(m, t);
        rlwe_gadget_ct g_ct = gadget_sk.gadget_encrypt_fft(gadget_m);
        rlwe_ct ct_prod(&rlwe_par);
        g_ct.mul(&ct_prod, &ct, mode); 
        sk.decrypt(out, &ct_prod, t);
        utils::array_mod_form(out, out, N, t);
        if(!utils::is_eq_poly(out, exp_poly, N)){
            std::cout << "Fail at: " << i << std::endl;
            std::cout << "gadget rlwe test: Fail" << std::endl;
            std::cout << "out: " << utils::to_string(out, rlwe_par.N) << std::endl;  
            std::cout << "exp_poly: " << utils::to_string(exp_poly, rlwe_par.N) << std::endl;  
            test = false;
            break;
        }
    }
    if(test){
        std::cout << "gadget rlwe test: OK" << std::endl;
    }  

}

void gadget_rlwe_test(int test_num, gadget_mul_mode mode){
    std::cout << "gadget_rlwe_test" << std::endl;
    int N = 4096;
    int Q = 268435456;
    int t = 5; 
    sample rand;
    rlwe_param rlwe_par(negacyclic, N, Q, ternary, any, 3.2);
    rlwe_sk sk(rlwe_par);
    int basis = 8;
    rlwe_gadget_param gadget_rlwe_par(rlwe_par, basis, 0.0);
    gadget_rlwe_sk gadget_sk(gadget_rlwe_par, sk);

    long* m = rlwe_par.init_zero_poly(); 
    long* out = rlwe_par.init_poly();
    long* gadget_m = rlwe_par.init_zero_poly();
    gadget_m[0] = 1;
    long* exp_poly = rlwe_par.init_poly();
   
    bool test = true;
    for(int i = 0; i < test_num; ++i){
        rand.uniform_array(m, N, t); 
        rand.uniform_array(gadget_m, N, t); 
        utils::mul_mod(exp_poly, m, N, gadget_m, N, N, t, negacyclic);
        rlwe_ct ct = sk.scale_and_encrypt(m, t);
        rlwe_gadget_ct g_ct = gadget_sk.gadget_encrypt_fft(gadget_m);
        rlwe_ct ct_prod(&rlwe_par);
        g_ct.mul(&ct_prod, &ct, mode); 
        sk.decrypt(out, &ct_prod, t);
        utils::array_mod_form(out, out, N, t);
        if(!utils::is_eq_poly(out, exp_poly, N)){
            std::cout << "Fail at: " << i << std::endl;
            std::cout << "gadget rlwe test: Fail" << std::endl;
            std::cout << "out: " << utils::to_string(out, rlwe_par.N) << std::endl;  
            std::cout << "exp_poly: " << utils::to_string(exp_poly, rlwe_par.N) << std::endl;  
            std::cout << "m: " << utils::to_string(m, rlwe_par.N) << std::endl;  
            test = false;
            break;
        }
    }
    if(test){
        std::cout << "gadget rlwe test: OK" << std::endl;
    }  

}


void gaussian_sample_test(){
    // That is a very dummy test for gaussian sampling from qZZ - actually, I should do some real deal Gaussian sampling tests.
    std::cout << "gaussian_sample_test" << std::endl;
    sample rand;

    int samples = 10;
    long q = 8;
    double stddev = 40;
    for(int i = 0; i < samples; ++i){
        std::cout << "i: " << rand.gaussian(q, 0, stddev) << std::endl;
        std::cout << "i/q: " << rand.gaussian(q, 0, stddev)/q << std::endl;
    } 
}

void rlwe_gaussian_gadget_test(){
    std::cout << "gadget_rlwe_test" << std::endl;
    int N = 2;
    int Q = 512;
    int t = 5;
    sample rand;
    rlwe_param rlwe_par(negacyclic, N, Q, ternary, any, 3.2);
    rlwe_sk sk(rlwe_par);
    int basis = 8;
    double gadget_stddev = basis * 5;
    rlwe_gadget_param gadget_rlwe_par(rlwe_par, basis, gadget_stddev);
    gadget_rlwe_sk gadget_sk(gadget_rlwe_par, sk);

    long* gadget_vector = new long[gadget_rlwe_par.ell];
    int powers_of_basis = 1;
    for(int i = 0; i < gadget_rlwe_par.ell; ++i){
        gadget_vector[i] = powers_of_basis;
        powers_of_basis *= basis;
    }

    std::cout << "gadget_rlwe_par.ell: " << gadget_rlwe_par.ell << std::endl;
    std::cout << "gadget_rlwe_par.k: " << gadget_rlwe_par.k << std::endl;
    std::cout << "powers_of_basis: " << utils::to_string(gadget_vector, gadget_rlwe_par.ell) << std::endl;
    long* m = rlwe_par.init_zero_poly(); 
    m[0] = 1;
    m[1] = 34;
    //m[2] = 125;
    //m[4] = 467;
    std::cout << "m: " << utils::to_string(m, N) << std::endl;
 
    // Decomp c_1. 
    long **decomposed = new long*[gadget_rlwe_par.ell]; 
    for(int i = 0; i < gadget_rlwe_par.ell; ++i){  
        decomposed[i] = gadget_rlwe_par.param.init_zero_poly();  
    }
    utils::gaussian_sample(decomposed, m, gadget_rlwe_par.param.N, gadget_rlwe_par.basis, gadget_rlwe_par.k, gadget_rlwe_par.ell, gadget_rlwe_par.param.rand);
    //rlwe_gadget_ct ct(gadget_rlwe_par);  
    //std::cout << "Start Gaussian Sampling..." << std::endl;
    //long** decomposed = ct.gaussian_sample(m);
    for(int i = 0; i < gadget_rlwe_par.ell; ++i){
        std::cout << "decomposed[i]: " << utils::to_string(decomposed[i], N) << std::endl;
    }

    long composed;
    for(int j = 0; j < N; j++){
        composed = 0;
        for(int i = 0; i < gadget_rlwe_par.ell; ++i){
            composed +=  gadget_vector[i] * decomposed[i][j];
            //std::cout << "decomposed[i]: " << utils::to_string(decomposed[i], N) << std::endl;
        }
        std::cout << "Composed["<<j<<"]: " <<  composed % Q  << std::endl;
        std::cout << "Composed["<<j<<"]: " << utils::integer_mod_form(composed, Q) << std::endl;
    }

}




int main(){
    //rlwe_test(10);
    gadget_rlwe_basic_test(100, simul);
    gadget_rlwe_test(100, simul);

    //gaussian_sample_test();
    //rlwe_gaussian_gadget_test();

    return 0;
}