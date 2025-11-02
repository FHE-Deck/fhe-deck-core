 
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <math.h> 
#include <fstream>

#include "verbose_stream.hpp"
/// @brief  This flag is defined in test_main.cpp
extern bool verbose;

#include "fhe_deck.h"
  
using namespace FHEDeck;
  
void ntru_test(int32_t test_num, int64_t N, int64_t Q, PolynomialArithmetic arithmetic){
    
    #if defined(USE_CEREAL) 
  
    int32_t plaintext_modulus = 13;
    //Sampler rand;
    std::shared_ptr<Distribution> rand = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, plaintext_modulus-1));
    KeyDistribution rlwe_key_type = KeyDistribution::binary;
    std::shared_ptr<NTRUParam> ntru_par(new NTRUParam(RingType::negacyclic, N, Q, arithmetic));
     
   {
        /// Serialize and Deserialize  RLWE Param 
        std::ofstream os("NTRUParam_test", std::ios::binary); 
        cereal::BinaryOutputArchive oarchive(os); 
        oarchive(ntru_par); 
        os.close();   
    }  
    {
        std::shared_ptr<NTRUParam> ntru_par_test;
        std::ifstream is("NTRUParam_test", std::ios::binary);
        cereal::BinaryInputArchive iarchive(is);  
        iarchive(ntru_par_test);  
        if(ntru_par->size != ntru_par_test->size || ntru_par->coef_modulus != ntru_par_test->coef_modulus){
            FAIL(); 
        } 
        std::remove("NTRUParam_test"); 
    }

      
    std::shared_ptr<NTRUSK> sk; 
    std::shared_ptr<NTRUSK> ntru_sk_test(new NTRUSK(ntru_par, 3.2));  
    { 
        /// Serialize and Deserialize  RLWE Param 
        std::ofstream os("NTRUSK_test", std::ios::binary); 
        cereal::BinaryOutputArchive oarchive(os); 
        oarchive(ntru_sk_test); 
        os.close();   
    }  
    {  
        std::ifstream is("NTRUSK_test", std::ios::binary);
        cereal::BinaryInputArchive iarchive(is);  
        iarchive(sk);   
        std::remove("NTRUSK_test"); 
    }


   Polynomial sk_test = Polynomial(ntru_par->size, plaintext_modulus);  
   sk->sk.mul(sk_test, sk->inv_sk, ntru_par->mul_engine);  
   
    Polynomial m(ntru_par->size, plaintext_modulus); 
     
    PlaintextEncoding encoding(PlaintextEncodingType::full_domain, plaintext_modulus, Q); 
    std::shared_ptr<NTRUCT> ct(new NTRUCT(ntru_par)); 
    Polynomial out(ntru_par->size, plaintext_modulus);   
    bool test = true;
    for(int32_t i = 0; i < test_num; ++i){ 
        rand->fill_array(m.vec, ntru_par->size); 
        sk->kdm_encode_and_encrypt(*ct.get(), m, encoding); 
         {
            /// Serialize and Deserialize  RLWE Param 
            std::ofstream os("NTRUCT_test", std::ios::binary); 
            cereal::BinaryOutputArchive oarchive(os); 
            oarchive(ct); 
            os.close();   
         }  
         std::shared_ptr<NTRUCT> ct_test;
         { 
            std::ifstream is("NTRUCT_test", std::ios::binary);
            cereal::BinaryInputArchive iarchive(is);  
            iarchive(ct_test);   
            std::remove("NTRUCT_test"); 
         }

        sk->decrypt(out, *ct_test.get(), encoding); 
        if(!Utils::is_eq_poly(out.vec, m.vec, N)){
            FAIL();
        }
    }

    bool add_test = true;
    Polynomial m_1(ntru_par->size, plaintext_modulus);
    Polynomial m_2(ntru_par->size, plaintext_modulus);
    Polynomial exp(ntru_par->size, plaintext_modulus);
    for(int32_t i = 0; i < test_num; ++i){    
        rand->fill_array(m_1.vec, ntru_par->size);   
        rand->fill_array(m_2.vec, ntru_par->size);    
        for(int32_t j = 0; j < ntru_par->size; ++j){ 
            exp.vec[j] = (m_1.vec[j] + m_2.vec[j]) % plaintext_modulus;
        }  
        std::shared_ptr<NTRUCT> ct_1 = sk->kdm_encode_and_encrypt(m_1, encoding);
        std::shared_ptr<NTRUCT> ct_2 = sk->kdm_encode_and_encrypt(m_2, encoding);  
        std::shared_ptr<NTRUCT> ct_3(new NTRUCT(ntru_par)); 
         
        ct_1->add(*ct_3.get(), *ct_2.get());   
        sk->decrypt(out, *ct_3.get(), encoding);    
          
        Utils::array_mod_form(out.vec, out.vec, N, plaintext_modulus);    
        if(!Utils::is_eq_poly(out.vec, exp.vec, N)){
            FAIL(); 
        }
    } 

    bool sub_test = true; 
    for(int32_t i = 0; i < test_num; ++i){    
        rand->fill_array(m_1.vec, ntru_par->size); 
        rand->fill_array(m_2.vec, ntru_par->size);   
        for(int32_t j = 0; j < ntru_par->size; ++j){ 
            exp.vec[j] = Utils::integer_mod_form(m_1.vec[j] - m_2.vec[j], plaintext_modulus);
        }   
        std::shared_ptr<NTRUCT> ct_1(sk->kdm_encode_and_encrypt(m_1, encoding));
        std::shared_ptr<NTRUCT> ct_2(sk->kdm_encode_and_encrypt(m_2, encoding));  
        NTRUCT ct_3(ntru_par);  
        ct_1->sub(ct_3, *ct_2.get());   
        sk->decrypt(out, ct_3, encoding);     
        Utils::array_mod_form(out.vec, out.vec, N, plaintext_modulus);    
        if(!Utils::is_eq_poly(out.vec, exp.vec, N)){
            FAIL(); 
        }
    } 
 
    bool neg_test = true; 
    for(int32_t i = 0; i < test_num; ++i){     
        rand->fill_array(m_1.vec, ntru_par->size); 
        for(int32_t j = 0; j < ntru_par->size; ++j){ 
            exp.vec[j] = Utils::integer_mod_form(-m_1.vec[j], plaintext_modulus);
        }   
        std::shared_ptr<NTRUCT> ct_1(sk->kdm_encode_and_encrypt(m_1, encoding)); 
        NTRUCT ct_3(ntru_par); 
        ct_1->neg(ct_3);
        sk->decrypt(out, ct_3, encoding);     
        Utils::array_mod_form(out.vec, out.vec, N, plaintext_modulus);    
        if(!Utils::is_eq_poly(out.vec, exp.vec, N)){
            FAIL(); 
        }
    } 

 
    std::shared_ptr<Distribution> rand_rot = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, 2*N));
    bool negacyclic_rotate_test = true; 
    int64_t rot;
    for(int32_t i = 0; i < test_num; ++i){       
        rand->fill_array(m_1.vec, ntru_par->size);
        rot = rand_rot->next(); 
        m_1.negacyclic_rotate(exp, rot);
        Utils::array_mod_form(exp.vec, exp.vec, N, plaintext_modulus);
        std::shared_ptr<NTRUCT> ct_1(sk->kdm_encode_and_encrypt(m_1, encoding)); 
        NTRUCT ct_3(ntru_par); 
        ct_1->negacyclic_rotate(ct_3, rot);
        sk->decrypt(out, ct_3, encoding);     
        Utils::array_mod_form(out.vec, out.vec, N, plaintext_modulus);    
        if(!Utils::is_eq_poly(out.vec, exp.vec, N)){
            FAIL(); 
        }
    } 
 
 
    PolynomialMultiplicationEngineBuilder builder = PolynomialMultiplicationEngineBuilder();
    builder.set_degree(ntru_par->size);
    builder.set_coef_modulus(plaintext_modulus);
    builder.set_polynomial_arithmetic(PolynomialArithmetic::naive);
    std::shared_ptr<PolynomialMultiplicationEngine> ntt_engine = builder.build();

    bool mul_test = true; 
    m_1.set_multiplication_engine(ntt_engine);

    Polynomial scalar(ntru_par->size, plaintext_modulus); 
    scalar.zeroize();
    for(int i = 0; i < test_num; ++i){ 
        rand->fill_array(m_1.vec, N);  
        rand->fill_array(scalar.vec,  N/64);
        m_1.mul(exp, scalar); 
        std::shared_ptr<NTRUCT> ct_1(sk->kdm_encode_and_encrypt(m_1, encoding)); 
        NTRUCT ct_3(ntru_par);
        ct_1->mul(ct_3, scalar); 
        sk->decrypt(out, ct_3, encoding);  
        if(!Utils::is_eq_poly(out.vec, exp.vec, N)){
            print_out << "NTRU MUL test: Fail" << std::endl;
            print_out << "out: " << Utils::to_string(out.vec, 15) << std::endl;  
            print_out << "exp: " << Utils::to_string(exp.vec, 15) << std::endl;  
            mul_test = false; 
            FAIL();
        }
    } 


   std::shared_ptr<LWESK> lwe_sk(sk->extract_lwe_key());  
   LWECT lwe_ct(lwe_sk->param);
   int64_t lwe_msg;
   test = true;
   for(int32_t i = 0; i < test_num; ++i){ 
      rand->fill_array(m.vec, N); 
      ct = std::shared_ptr<NTRUCT>(sk->kdm_encode_and_encrypt(m, encoding));
      ct->extract_lwe(lwe_ct); 
      sk->decrypt(out, *ct.get(), encoding); 
      lwe_msg = lwe_sk->decrypt(lwe_ct, encoding); 
      if(!(out.vec[0] == lwe_msg)){
        FAIL(); 
      }
   } 
  #endif
}
 
void gadget_ntru_test(int32_t test_num,  int64_t N, int64_t Q, int64_t base, PolynomialArithmetic arithmetic){
    
    #if defined(USE_CEREAL) 
    int32_t plaintext_modulus = 5; 
    PlaintextEncoding encoding(PlaintextEncodingType::full_domain, plaintext_modulus, Q);
    //Sampler rand;
    std::shared_ptr<Distribution> rand = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, plaintext_modulus-1)); 
    KeyDistribution rlwe_key_type = KeyDistribution::ternary;
    std::shared_ptr<NTRUParam> ntru_par(new NTRUParam(RingType::negacyclic, N, Q, arithmetic)); 
    std::shared_ptr<NTRUSK> sk = std::shared_ptr<NTRUSK>(new NTRUSK(ntru_par, 3.2));   
       
   std::shared_ptr<Gadget> deter_gadget = std::shared_ptr<Gadget>(new SignedDecompositionGadget(N, Q, base));
   NTRUGadgetSK gadget_sk;
   NTRUGadgetSK gadget_sk_test(deter_gadget, sk);
   {
      /// Serialize and Deserialize  RLWE Param 
      std::ofstream os("NTRUGadgetSK_test", std::ios::binary); 
      cereal::BinaryOutputArchive oarchive(os); 
      oarchive(gadget_sk_test); 
      os.close();   
   }  
   std::unique_ptr<NTRUCT> ct_test;
   { 
      std::ifstream is("NTRUGadgetSK_test", std::ios::binary);
      cereal::BinaryInputArchive iarchive(is);  
      iarchive(gadget_sk);   
      std::remove("NTRUGadgetSK_test"); 
   }

  
    PolynomialMultiplicationEngineBuilder builder = PolynomialMultiplicationEngineBuilder();
    builder.set_degree(ntru_par->size);
    builder.set_coef_modulus(plaintext_modulus);
    builder.set_polynomial_arithmetic(PolynomialArithmetic::naive);
    std::shared_ptr<PolynomialMultiplicationEngine> ntt_engine = builder.build();


    Polynomial m(ntru_par->size, plaintext_modulus); 
    m.set_multiplication_engine(ntt_engine);
    Polynomial out(ntru_par->size, plaintext_modulus);
    out.set_multiplication_engine(ntt_engine);
    Polynomial gadget_m(ntru_par->size, plaintext_modulus);
    gadget_m.set_multiplication_engine(ntt_engine);
    gadget_m.zeroize();
    gadget_m.vec[0] = 1;
    Polynomial exp_poly(ntru_par->size, plaintext_modulus);
    exp_poly.set_multiplication_engine(ntt_engine);
   
    bool test = true; 
    for(int32_t i = 0; i < test_num; ++i){ 
        rand->fill_array(m.vec, N); 
        rand->fill_array(gadget_m.vec, N);  
        m.mul(exp_poly, gadget_m); 
        std::shared_ptr<NTRUCT> ct(sk->kdm_encode_and_encrypt(m, encoding));
        std::shared_ptr<NTRUGadgetCT> g_ct_test = std::static_pointer_cast<NTRUGadgetCT>(std::shared_ptr<GadgetVectorCT>(gadget_sk.gadget_encrypt(gadget_m))); 
         std::shared_ptr<NTRUGadgetCT> g_ct;
         {
            /// Serialize and Deserialize  NTRU Param 
            std::ofstream os("NTRUGadgetCT_test", std::ios::binary); 
            cereal::BinaryOutputArchive oarchive(os); 
            oarchive(g_ct_test); 
            os.close();   
         }  
         std::unique_ptr<NTRUCT> ct_test;
         { 
            std::ifstream is("NTRUGadgetCT_test", std::ios::binary);
            cereal::BinaryInputArchive iarchive(is);  
            iarchive(g_ct);   
            std::remove("NTRUGadgetCT_test"); 
         }

        NTRUCT ct_prod(ntru_par); 
        g_ct->mul(ct_prod, *ct.get()); 
        sk->decrypt(out, ct_prod, encoding);
        Utils::array_mod_form(out.vec, out.vec, N, plaintext_modulus);
        if(!Utils::is_eq_poly(out.vec, exp_poly.vec, N)){ 
            print_out << "\rFail at: " << i << std::endl;
            print_out << "gadget ntru test: Fail" << std::endl;
            print_out << "out: " << Utils::to_string(out.vec, ntru_par->size) << std::endl;  
            print_out << "exp_poly: " << Utils::to_string(exp_poly.vec, ntru_par->size) << std::endl;  
            print_out << "m: " << Utils::to_string(m.vec, ntru_par->size) << std::endl;  
            test = false; 
            FAIL();
        } 
    }   
 
    #endif
}

void extract_and_key_switch_test(int32_t test_num, int64_t N, int64_t Q, PolynomialArithmetic arithmetic){ 

   int32_t plaintext_modulus = 13; 
   std::shared_ptr<Distribution> rand = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, plaintext_modulus)); 
   KeyDistribution rlwe_key_type = KeyDistribution::binary;
   std::shared_ptr<NTRUParam> ntru_par(new NTRUParam(RingType::negacyclic, N, Q, arithmetic)); 
   std::shared_ptr<NTRUSK> sk(new NTRUSK(ntru_par, 3.2));  
   Polynomial m(ntru_par->size, ntru_par->coef_modulus);  
   PlaintextEncoding encoding(PlaintextEncodingType::full_domain, plaintext_modulus, Q); 
   std::shared_ptr<NTRUCT> ct(new NTRUCT(ntru_par)); 
   Polynomial out(ntru_par->size, ntru_par->coef_modulus);  

   
   std::shared_ptr<LWESK> lwe_sk(sk->extract_lwe_key());  
   LWECT lwe_ct(lwe_sk->param);
   int64_t lwe_msg;
   bool test = true;
   for(int32_t i = 0; i < test_num; ++i){ 
      rand->fill_array(m.vec, ntru_par->size);
      ct = std::shared_ptr<NTRUCT>(sk->kdm_encode_and_encrypt(m, encoding));
      ct->extract_lwe(lwe_ct); 
      sk->decrypt(out, *ct.get(), encoding); 
      lwe_msg = lwe_sk->decrypt(lwe_ct, encoding);  
      if(!(out.vec[0] == lwe_msg)){ 
        FAIL(); 
      }
   } 

   std::shared_ptr<LWEParam> lwe_target_param(new LWEParam(256, Q));
   double stddev_target = 3.2; 
   std::shared_ptr<LWESK> lwe_sk_target(new LWESK(lwe_target_param, stddev_target, KeyDistribution::binary));    
   std::shared_ptr<LWEGadgetSK> gadget_lwe_sk_target(new LWEGadgetSK(lwe_sk_target, 16)); 
   std::shared_ptr<LWEToLWEKeySwitchKey> ksk(new LWEToLWEKeySwitchKey(lwe_sk, gadget_lwe_sk_target));
   LWECT ct_target(lwe_target_param);

   test = true;
   for(int32_t i = 0; i < test_num; ++i){  
      rand->fill_array(m.vec, ntru_par->size);
      ct = std::shared_ptr<NTRUCT>(sk->kdm_encode_and_encrypt(m, encoding));
      ct->extract_lwe(lwe_ct); 
      ksk->lwe_to_lwe_key_switch(ct_target, lwe_ct); 
      sk->decrypt(out, *ct.get(), encoding); 
      lwe_msg = lwe_sk_target->decrypt(ct_target, encoding); 
      if(!(out.vec[0] == lwe_msg)){
            FAIL(); 
      }
   } 
}
 
// =====================
// NTRU Test Parameters
// =====================

struct NTRUTestParam {
    int32_t test_num;
    int64_t N;
    int64_t Q;
    PolynomialArithmetic arithmetic;
};

struct GadgetNTRUTestParam {
    int32_t test_num;
    int64_t N;
    int64_t Q;
    int64_t base;
    PolynomialArithmetic arithmetic;
};


// =====================
// Basic NTRU Test
// =====================

class NTRUBasicTest : public ::testing::TestWithParam<NTRUTestParam> {};

TEST_P(NTRUBasicTest, BasicNTRU) {
    const auto& p = GetParam();
    ntru_test(p.test_num, p.N, p.Q, p.arithmetic);
}

INSTANTIATE_TEST_SUITE_P(
    BasicNTRUTest,
    NTRUBasicTest,
    ::testing::Values(
        NTRUTestParam{100, 4096, 35184371884033, PolynomialArithmetic::ntt64},
        NTRUTestParam{100, 4096, 288230376151130113, PolynomialArithmetic::ntt64},
        NTRUTestParam{100, 4096, 1152921504606830593, PolynomialArithmetic::ntt64},
        NTRUTestParam{100, 4096, 2305843009213554689, PolynomialArithmetic::ntt64},
        NTRUTestParam{100, 4096, 4611686018427322369, PolynomialArithmetic::ntt64}
    )
);


// =====================
// Extract & Key Switch Test
// =====================

class NTRUExtractAndKeySwitchTest : public ::testing::TestWithParam<NTRUTestParam> {};

TEST_P(NTRUExtractAndKeySwitchTest, ExtractAndKeySwitch) {
    const auto& p = GetParam();
    extract_and_key_switch_test(p.test_num, p.N, p.Q, p.arithmetic);
}

INSTANTIATE_TEST_SUITE_P(
    ExtractAndKeySwitchNTRUTest,
    NTRUExtractAndKeySwitchTest,
    ::testing::Values(
        NTRUTestParam{100, 4096, 35184371884033, PolynomialArithmetic::ntt64},
        NTRUTestParam{100, 4096, 288230376151130113, PolynomialArithmetic::ntt64},
        NTRUTestParam{100, 4096, 1152921504606830593, PolynomialArithmetic::ntt64},
        NTRUTestParam{100, 4096, 2305843009213554689, PolynomialArithmetic::ntt64},
        NTRUTestParam{100, 4096, 4611686018427322369, PolynomialArithmetic::ntt64}
    )
);


// =====================
// Gadget NTRU Test
// =====================

class NTRUGadgetTest : public ::testing::TestWithParam<GadgetNTRUTestParam> {};

TEST_P(NTRUGadgetTest, GadgetNTRU) {
    const auto& p = GetParam();
    gadget_ntru_test(p.test_num, p.N, p.Q, p.base, p.arithmetic);
}

INSTANTIATE_TEST_SUITE_P(
    GadgetNTRUTest,
    NTRUGadgetTest,
    ::testing::Values(
        GadgetNTRUTestParam{100, 512, 67104769, 8, PolynomialArithmetic::ntt64},
        GadgetNTRUTestParam{100, 4096, 288230376151130113, 8, PolynomialArithmetic::ntt64},
        GadgetNTRUTestParam{100, 4096, 1152921504606830593, 8, PolynomialArithmetic::ntt64},
        GadgetNTRUTestParam{10, 4096, 2305843009213554689, 4, PolynomialArithmetic::ntt64},
        GadgetNTRUTestParam{10, 4096, 35184371884033, 32768, PolynomialArithmetic::ntt64}
    )
);
 

  