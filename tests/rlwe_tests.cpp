#include <iostream>
#include "rlwe_param.h"
#include "rlwe.h"
#include "utils.h"

using namespace fhe_deck;

void rlwe_test(int test_num){
    std::cout << "=========== rlwe_test ========= " << std::endl;

    long N = 512;
    // NTL and FFT can use this:
    //long Q = 268435456;

    // Lets take Q to be a a NTT friendly prime (for the fft based tests its gonna work anyway)
    // Q = 67104769 = 2**26 - 4095 
    long Q = 67104769;

    int t = 13;
    Sampler rand;
    std::shared_ptr<RLWEParam> rlwe_par(new RLWEParam(negacyclic, N, Q, ternary, any, 3.2, hexl_ntt));
    RLWESK sk(rlwe_par, hexl_ntt); 

    long* m = rlwe_par->init_zero_poly();
    rand.uniform_array(m, N, t); 
    RLWECT ct = sk.scale_and_encrypt(m, t); 
    long* out = rlwe_par->init_poly(); 

    bool test = true;
    for(int i = 0; i < test_num; ++i){
        rand.uniform_array(m, N, t);
        RLWECT ct = sk.scale_and_encrypt(m, t);
        sk.decrypt(out, &ct, t);
        Utils::array_mod_form(out, out, N, t);
        if(!Utils::is_eq_poly(out, m, N)){
            std::cout << "rlwe_test: Fail" << std::endl;
            std::cout << "out: " << Utils::to_string(out, rlwe_par->N) << std::endl;  
            std::cout << "m: " << Utils::to_string(m, rlwe_par->N) << std::endl;  
            test = false;
            break;
        }
    }
    if(test){
        std::cout << "rlwe_test: OK" << std::endl;
    } 

 
    bool add_test = true;
    long* m_1 = rlwe_par->init_zero_poly();
    long* m_2 = rlwe_par->init_zero_poly();
    long* exp = rlwe_par->init_zero_poly();
    for(int i = 0; i < test_num; ++i){  
        rand.uniform_array(m_1, N, t);
        //utils::array_mod_form(m_1, m_1, N, t);  
        rand.uniform_array(m_2, N, t);
        //utils::array_mod_form(m_2, m_2, N, t); 
        for(int j = 0; j < N; ++j){
            //exp[j] = utils::integer_mod_form(m_1[j] + m_2[j],  t);
            exp[j] = (m_1[j] + m_2[j]) % t;
        } 
        RLWECT ct_1 = sk.scale_and_encrypt(m_1, t);
        RLWECT ct_2 = sk.scale_and_encrypt(m_2, t); 
        RLWECT ct_3; 
        ct_1.add(&ct_3, &ct_2);  
        sk.decrypt(out, &ct_3, t);   
        Utils::array_mod_form(out, out, N, t);  
        if(!Utils::is_eq_poly(out, exp, N)){
            std::cout << "rlwe ADD test: Fail" << std::endl;
            std::cout << "out: " << Utils::to_string(out, rlwe_par->N) << std::endl;  
            std::cout << "exp: " << Utils::to_string(exp, rlwe_par->N) << std::endl;  
            std::cout << "m_1: " << Utils::to_string(m_1, rlwe_par->N) << std::endl;  
            std::cout << "m_2: " << Utils::to_string(m_2, rlwe_par->N) << std::endl;  
            add_test = false;
            break;
        }
    }
    if(add_test){
        std::cout << "rlwe ADD test: OK" << std::endl;
    } 

    bool mul_test = true;
    long* scalar = rlwe_par->init_zero_poly();
    // Lets do a mul test here 
    for(int i = 0; i < test_num; ++i){
        rand.uniform_array(m_1, N, t);   
        // NOTE: We are doing a quite sparse polynomial here, because the error may blow up and the test will fail
        rand.uniform_array(scalar, N/64, t);
        Utils::mul_mod(exp, m_1, N, scalar, N, N, t, negacyclic);
        RLWECT ct_1 = sk.scale_and_encrypt(m_1, t); 
        RLWECT ct_3;
        ct_1.mul(&ct_3, scalar); 
        sk.decrypt(out, &ct_3, t); 
        Utils::array_mod_form(out, out, N, t); 
        if(!Utils::is_eq_poly(out, exp, N)){
            std::cout << "rlwe MUL test: Fail" << std::endl;
            std::cout << "out: " << Utils::to_string(out, rlwe_par->N) << std::endl;  
            std::cout << "exp: " << Utils::to_string(exp, rlwe_par->N) << std::endl;  
            mul_test = false;
            break;
        }
    }
    if(mul_test){
        std::cout << "rlwe MUL test: OK" << std::endl;
    } 

}


void gadget_rlwe_encrypt_test(int test_num, GadgetMulMode mode, PolynomialArithmetic arithmetic){
    std::cout << "========== gadget_rlwe_encrypt_test ==========" << std::endl;
    int N = 512;
    // Lets take Q to be a a NTT friendly prime (for the fft based tests its gonna work anyway)
    // Q = 67104769 = 2**26 - 4095
    long Q = 67104769;
    //int Q = 67108864;
    int t = 13; 
    Sampler rand;
    std::shared_ptr<RLWEParam> rlwe_par(new RLWEParam(negacyclic, N, Q, ternary, any, 3.2, hexl_ntt));
    RLWESK sk(rlwe_par, hexl_ntt);
    int basis = 8;
    Gadget deter_gadget = Gadget(N, Q, basis, signed_decomposition_gadget);
    Gadget rand_gadget = Gadget(N, Q, basis, 0.0, discrete_gaussian_gadget);
    RLWEGadgetParam gadget_rlwe_par(rlwe_par, basis, deter_gadget, rand_gadget);
    RLWEGadgetSK gadget_sk(gadget_rlwe_par, sk);

    long* gadget_m = rlwe_par->init_zero_poly();
    
    std::cout << "Encrypt something" << std::endl;
    RLWEGadgetCT g_ct = gadget_sk.gadget_encrypt(gadget_m);  
    std::cout << "Copy gadget ciphertext..." << std::endl;
    RLWEGadgetCT g_ct_copy = g_ct;  
    std::cout << "Run to coef form" << std::endl;
    g_ct.to_coef();
    bool test = true;
    for(int i = 0; i < test_num; ++i){ 
        g_ct = gadget_sk.gadget_encrypt(gadget_m); 
        g_ct_copy = g_ct;   
        g_ct.to_coef();
        for(int j = 0; j < gadget_rlwe_par.ell_max; ++j){
            if(!Utils::is_eq_poly(g_ct.gadget_ct[j].a, g_ct_copy.gadget_ct[j].a, rlwe_par->N)){
                std::cout << "gadget_rlwe_encrypt_test: Fail at j=" << j << std::endl;
                std::cout << "g_ct.gadget_ct[j].a: " << Utils::to_string(g_ct.gadget_ct[j].a, rlwe_par->N) <<  std::endl;
                std::cout << "g_ct_copy.gadget_ct[j].a: " << Utils::to_string(g_ct_copy.gadget_ct[j].a, rlwe_par->N) <<  std::endl;
                test = false;
                break;
            }
            if(!Utils::is_eq_poly(g_ct.gadget_ct[j].b, g_ct_copy.gadget_ct[j].b, rlwe_par->N)){
                std::cout << "gadget_rlwe_encrypt_test: Fail at j=" << j << std::endl;
                std::cout << "g_ct.gadget_ct[j].b: " << Utils::to_string(g_ct.gadget_ct[j].b, rlwe_par->N) <<  std::endl;
                std::cout << "g_ct_copy.gadget_ct[j].b: " << Utils::to_string(g_ct_copy.gadget_ct[j].b, rlwe_par->N) <<  std::endl;
                test = false;
                break;
            }
            if(!Utils::is_eq_poly(g_ct.gadget_ct_sk[j].a, g_ct_copy.gadget_ct_sk[j].a, rlwe_par->N)){
                std::cout << "gadget_rlwe_encrypt_test: Fail at j=" << j << std::endl;
                std::cout << "g_ct.gadget_ct_sk[j].a: " << Utils::to_string(g_ct.gadget_ct_sk[j].a, rlwe_par->N) <<  std::endl;
                std::cout << "g_ct_copy.gadget_ct_sk[j].a: " << Utils::to_string(g_ct_copy.gadget_ct_sk[j].a, rlwe_par->N) <<  std::endl;
                test = false;
                break;
            }
            if(!Utils::is_eq_poly(g_ct.gadget_ct_sk[j].b, g_ct_copy.gadget_ct_sk[j].b, rlwe_par->N)){
                std::cout << "gadget_rlwe_encrypt_test: Fail at j=" << j << std::endl;
                std::cout << "g_ct.gadget_ct_sk[j].b: " << Utils::to_string(g_ct.gadget_ct_sk[j].b, rlwe_par->N) <<  std::endl;
                std::cout << "g_ct_copy.gadget_ct_sk[j].b: " << Utils::to_string(g_ct_copy.gadget_ct_sk[j].b, rlwe_par->N) <<  std::endl;
                test = false;
                break;
            }
        } 
    }
    if(test){
        std::cout << "gadget_rlwe_encrypt_test: OK" << std::endl;
    }
}


void gadget_rlwe_basic_test(int test_num, GadgetMulMode mode, PolynomialArithmetic arithmetic){
    std::cout << "========== gadget_rlwe_basic_test ==========" << std::endl;
    int N = 512;
    // Lets take Q to be a a NTT friendly prime (for the fft based tests its gonna work anyway)
    // Q = 67104769 = 2**26 - 4095
    long Q = 67104769;
    //int Q = 67108864;
    int t = 13; 
    Sampler rand;
    std::shared_ptr<RLWEParam> rlwe_par(new RLWEParam(negacyclic, N, Q, ternary, any, 3.2, hexl_ntt));
    RLWESK sk(rlwe_par, hexl_ntt);
    int basis = 8;
    Gadget deter_gadget = Gadget(N, Q, basis*basis, signed_decomposition_gadget);
    Gadget rand_gadget = Gadget(N, Q, basis, 0.0, discrete_gaussian_gadget);
    RLWEGadgetParam gadget_rlwe_par(rlwe_par, basis, deter_gadget, rand_gadget);
    RLWEGadgetSK gadget_sk(gadget_rlwe_par, sk);
 


    long* m = rlwe_par->init_zero_poly(); 
    long* out = rlwe_par->init_poly();
    long* gadget_m = rlwe_par->init_zero_poly();
    long* exp_poly = rlwe_par->init_poly();
   
    bool test = true;
    for(int i = 0; i < test_num; ++i){
        rand.uniform_array(m, N, t);
        rand.uniform_array(gadget_m, N, t);  
        Utils::mul_mod(exp_poly, m, N, gadget_m, N, N, t, negacyclic);
        RLWECT ct = sk.scale_and_encrypt(m, t);
        RLWEGadgetCT g_ct = gadget_sk.gadget_encrypt(gadget_m); 
        
        RLWECT ct_prod(rlwe_par);
        g_ct.mul(&ct_prod, &ct, mode);  

        sk.decrypt(out, &ct_prod, t);
        Utils::array_mod_form(out, out, N, t);
        if(!Utils::is_eq_poly(out, exp_poly, N)){
            std::cout << "Fail at: " << i << std::endl;
            std::cout << "gadget rlwe test: Fail" << std::endl;
            std::cout << "out: " << Utils::to_string(out, rlwe_par->N) << std::endl;  
            std::cout << "exp_poly: " << Utils::to_string(exp_poly, rlwe_par->N) << std::endl;  
            test = false;
            break;
        }
    }
    if(test){
        std::cout << "gadget rlwe test: OK" << std::endl;
    }  

}

void gadget_rlwe_test(int test_num, GadgetMulMode mode, PolynomialArithmetic arithmetic){
    std::cout << "============== gadget_rlwe_test ==================" << std::endl;
    int N = 512;
    // Lets take Q to be a a NTT friendly prime (for the fft based tests its gonna work anyway)
    // Q = 67104769 = 2**26 - 4095
    long Q = 67104769;
    int t = 5; 
    Sampler rand;
    std::shared_ptr<RLWEParam> rlwe_par(new RLWEParam(negacyclic, N, Q, ternary, any, 3.2, arithmetic));
    RLWESK sk(rlwe_par, arithmetic);
    int basis = 8;
    Gadget deter_gadget = Gadget(N, Q, basis, signed_decomposition_gadget);
    Gadget rand_gadget = Gadget(N, Q, basis, 0.0, discrete_gaussian_gadget);
    RLWEGadgetParam gadget_rlwe_par(rlwe_par, basis, deter_gadget, rand_gadget);
    RLWEGadgetSK gadget_sk(gadget_rlwe_par, sk);

    long* m = rlwe_par->init_zero_poly(); 
    long* out = rlwe_par->init_poly();
    long* gadget_m = rlwe_par->init_zero_poly();
    gadget_m[0] = 1;
    long* exp_poly = rlwe_par->init_poly();
   
    bool test = true;
    for(int i = 0; i < test_num; ++i){
        rand.uniform_array(m, N, t); 
        rand.uniform_array(gadget_m, N, t); 
        Utils::mul_mod(exp_poly, m, N, gadget_m, N, N, t, negacyclic);
        RLWECT ct = sk.scale_and_encrypt(m, t);
        RLWEGadgetCT g_ct = gadget_sk.gadget_encrypt(gadget_m);
        RLWECT ct_prod(rlwe_par);
        g_ct.mul(&ct_prod, &ct, mode); 
        sk.decrypt(out, &ct_prod, t);
        Utils::array_mod_form(out, out, N, t);
        if(!Utils::is_eq_poly(out, exp_poly, N)){
            std::cout << "Fail at: " << i << std::endl;
            std::cout << "gadget rlwe test: Fail" << std::endl;
            std::cout << "out: " << Utils::to_string(out, rlwe_par->N) << std::endl;  
            std::cout << "exp_poly: " << Utils::to_string(exp_poly, rlwe_par->N) << std::endl;  
            std::cout << "m: " << Utils::to_string(m, rlwe_par->N) << std::endl;  
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
