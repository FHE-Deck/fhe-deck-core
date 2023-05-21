#include <iostream>
#include "../include/rlwe_param.h"
#include "../include/rlwe.h"
#include "../include/utils.h"

void rlwe_test(int test_num){
    std::cout << "=========== rlwe_test ========= " << std::endl;

    long N = 512;
    // NTL and FFT can use this:
    //long Q = 268435456;

    // Lets take Q to be a a NTT friendly prime (for the fft based tests its gonna work anyway)
    // Q = 67104769 = 2**26 - 4095 
    long Q = 67104769;

    int t = 13;
    sampler rand;
    rlwe_param rlwe_par(negacyclic, N, Q, ternary, any, 3.2, hexl_ntt);
    rlwe_sk sk(rlwe_par, hexl_ntt); 

    long* m = rlwe_par.init_zero_poly();
    rand.uniform_array(m, N, t); 
    rlwe_ct ct = sk.scale_and_encrypt(m, t); 
    long* out = rlwe_par.init_poly(); 

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
            break;
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
        //utils::array_mod_form(m_1, m_1, N, t);  
        rand.uniform_array(m_2, N, t);
        //utils::array_mod_form(m_2, m_2, N, t); 
        for(int j = 0; j < N; ++j){
            //exp[j] = utils::integer_mod_form(m_1[j] + m_2[j],  t);
            exp[j] = (m_1[j] + m_2[j]) % t;
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
            std::cout << "m_1: " << utils::to_string(m_1, rlwe_par.N) << std::endl;  
            std::cout << "m_2: " << utils::to_string(m_2, rlwe_par.N) << std::endl;  
            add_test = false;
            break;
        }
    }
    if(add_test){
        std::cout << "rlwe ADD test: OK" << std::endl;
    } 

    bool mul_test = true;
    long* scalar = rlwe_par.init_zero_poly();
    // Lets do a mul test here 
    for(int i = 0; i < test_num; ++i){
        rand.uniform_array(m_1, N, t);   
        // NOTE: We are doing a quite sparse polynomial here, because the error may blow up and the test will fail
        rand.uniform_array(scalar, N/64, t);
        utils::mul_mod(exp, m_1, N, scalar, N, N, t, negacyclic);
        rlwe_ct ct_1 = sk.scale_and_encrypt(m_1, t); 
        rlwe_ct ct_3;
        ct_1.mul(&ct_3, scalar); 
        sk.decrypt(out, &ct_3, t); 
        utils::array_mod_form(out, out, N, t); 
        if(!utils::is_eq_poly(out, exp, N)){
            std::cout << "rlwe MUL test: Fail" << std::endl;
            std::cout << "out: " << utils::to_string(out, rlwe_par.N) << std::endl;  
            std::cout << "exp: " << utils::to_string(exp, rlwe_par.N) << std::endl;  
            mul_test = false;
            break;
        }
    }
    if(mul_test){
        std::cout << "rlwe MUL test: OK" << std::endl;
    } 

}


void gadget_rlwe_encrypt_test(int test_num, gadget_mul_mode mode, polynomial_arithmetic arithmetic){
    std::cout << "========== gadget_rlwe_encrypt_test ==========" << std::endl;
    int N = 512;
    // Lets take Q to be a a NTT friendly prime (for the fft based tests its gonna work anyway)
    // Q = 67104769 = 2**26 - 4095
    long Q = 67104769;
    //int Q = 67108864;
    int t = 13; 
    sampler rand;
    rlwe_param rlwe_par(negacyclic, N, Q, ternary, any, 3.2, hexl_ntt);
    rlwe_sk sk(rlwe_par, hexl_ntt);
    int basis = 8;
    gadget deter_gadget = gadget(N, Q, basis, signed_decomposition_gadget);
    gadget rand_gadget = gadget(N, Q, basis, 0.0, discrete_gaussian_gadget);
    rlwe_gadget_param gadget_rlwe_par(rlwe_par, basis, deter_gadget, rand_gadget);
    gadget_rlwe_sk gadget_sk(gadget_rlwe_par, sk);

    long* gadget_m = rlwe_par.init_zero_poly();
    
    rlwe_gadget_ct g_ct = gadget_sk.gadget_encrypt(gadget_m);  
    rlwe_gadget_ct g_ct_copy = g_ct;  
    g_ct.to_coef();
    bool test = true;
    for(int i = 0; i < test_num; ++i){ 
        g_ct = gadget_sk.gadget_encrypt(gadget_m); 
        g_ct_copy = g_ct;   
        g_ct.to_coef();
        for(int j = 0; j < gadget_rlwe_par.ell_max; ++j){
            if(!utils::is_eq_poly(g_ct.gadget_ct[j].a, g_ct_copy.gadget_ct[j].a, rlwe_par.N)){
                std::cout << "gadget_rlwe_encrypt_test: Fail at j=" << j << std::endl;
                std::cout << "g_ct.gadget_ct[j].a: " << utils::to_string(g_ct.gadget_ct[j].a, rlwe_par.N) <<  std::endl;
                std::cout << "g_ct_copy.gadget_ct[j].a: " << utils::to_string(g_ct_copy.gadget_ct[j].a, rlwe_par.N) <<  std::endl;
                test = false;
                break;
            }
            if(!utils::is_eq_poly(g_ct.gadget_ct[j].b, g_ct_copy.gadget_ct[j].b, rlwe_par.N)){
                std::cout << "gadget_rlwe_encrypt_test: Fail at j=" << j << std::endl;
                std::cout << "g_ct.gadget_ct[j].b: " << utils::to_string(g_ct.gadget_ct[j].b, rlwe_par.N) <<  std::endl;
                std::cout << "g_ct_copy.gadget_ct[j].b: " << utils::to_string(g_ct_copy.gadget_ct[j].b, rlwe_par.N) <<  std::endl;
                test = false;
                break;
            }
            if(!utils::is_eq_poly(g_ct.gadget_ct_sk[j].a, g_ct_copy.gadget_ct_sk[j].a, rlwe_par.N)){
                std::cout << "gadget_rlwe_encrypt_test: Fail at j=" << j << std::endl;
                std::cout << "g_ct.gadget_ct_sk[j].a: " << utils::to_string(g_ct.gadget_ct_sk[j].a, rlwe_par.N) <<  std::endl;
                std::cout << "g_ct_copy.gadget_ct_sk[j].a: " << utils::to_string(g_ct_copy.gadget_ct_sk[j].a, rlwe_par.N) <<  std::endl;
                test = false;
                break;
            }
            if(!utils::is_eq_poly(g_ct.gadget_ct_sk[j].b, g_ct_copy.gadget_ct_sk[j].b, rlwe_par.N)){
                std::cout << "gadget_rlwe_encrypt_test: Fail at j=" << j << std::endl;
                std::cout << "g_ct.gadget_ct_sk[j].b: " << utils::to_string(g_ct.gadget_ct_sk[j].b, rlwe_par.N) <<  std::endl;
                std::cout << "g_ct_copy.gadget_ct_sk[j].b: " << utils::to_string(g_ct_copy.gadget_ct_sk[j].b, rlwe_par.N) <<  std::endl;
                test = false;
                break;
            }
        } 
    }
    if(test){
        std::cout << "gadget_rlwe_encrypt_test: OK" << std::endl;
    }
}


void gadget_rlwe_basic_test(int test_num, gadget_mul_mode mode, polynomial_arithmetic arithmetic){
    std::cout << "========== gadget_rlwe_basic_test ==========" << std::endl;
    int N = 512;
    // Lets take Q to be a a NTT friendly prime (for the fft based tests its gonna work anyway)
    // Q = 67104769 = 2**26 - 4095
    long Q = 67104769;
    //int Q = 67108864;
    int t = 13; 
    sampler rand;
    rlwe_param rlwe_par(negacyclic, N, Q, ternary, any, 3.2, hexl_ntt);
    rlwe_sk sk(rlwe_par, hexl_ntt);
    int basis = 8;
    gadget deter_gadget = gadget(N, Q, basis*basis, signed_decomposition_gadget);
    gadget rand_gadget = gadget(N, Q, basis, 0.0, discrete_gaussian_gadget);
    rlwe_gadget_param gadget_rlwe_par(rlwe_par, basis, deter_gadget, rand_gadget);
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
        rlwe_gadget_ct g_ct = gadget_sk.gadget_encrypt(gadget_m); 
        
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

void gadget_rlwe_test(int test_num, gadget_mul_mode mode, polynomial_arithmetic arithmetic){
    std::cout << "============== gadget_rlwe_test ==================" << std::endl;
    int N = 512;
    // Lets take Q to be a a NTT friendly prime (for the fft based tests its gonna work anyway)
    // Q = 67104769 = 2**26 - 4095
    long Q = 67104769;
    int t = 5; 
    sampler rand;
    rlwe_param rlwe_par(negacyclic, N, Q, ternary, any, 3.2, arithmetic);
    rlwe_sk sk(rlwe_par, hexl_ntt);
    int basis = 8;
    gadget deter_gadget = gadget(N, Q, basis, signed_decomposition_gadget);
    gadget rand_gadget = gadget(N, Q, basis, 0.0, discrete_gaussian_gadget);
    rlwe_gadget_param gadget_rlwe_par(rlwe_par, basis, deter_gadget, rand_gadget);
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
        rlwe_gadget_ct g_ct = gadget_sk.gadget_encrypt(gadget_m);
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





int main(){
    rlwe_test(10);
    gadget_rlwe_encrypt_test(100, deter, hexl_ntt);
    gadget_rlwe_basic_test(1, deter, hexl_ntt);
    gadget_rlwe_test(100, deter, hexl_ntt);
  
    return 0;
}