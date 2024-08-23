 

#include <iostream>
#include "lwe.h"
#include "ntru.h" 
#include "lwe_to_lwe_keyswitch.h"
#include "fft_plan.h"
#include <NTL/ZZX.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_p.h>
#include <random>
#include <math.h>

#include <fstream>

using namespace fhe_deck;
 

void ntru_test(int32_t test_num, int64_t N, int64_t Q, PolynomialArithmetic arithmetic){
    std::cout << "=========== ntru_test (N = " << N << ", Q = " << Q << ") ========= " << std::endl;
  
    int32_t t = 13;
    //Sampler rand;
    std::shared_ptr<Distribution> rand = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, t-1));
    KeyDistribution rlwe_key_type = binary;
    std::shared_ptr<NTRUParam> ntru_par(new NTRUParam(negacyclic, N, Q, arithmetic));
    
 
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
            std::cout << "NTRU Param Serialization Test: Fail" << std::endl;   
        }else{
            std::cout << "NTRU Param Serialization Test: OK" << std::endl;  
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


   Polynomial sk_test = Polynomial(ntru_par->size, ntru_par->coef_modulus);  
   sk->sk.mul(&sk_test, &sk->inv_sk, ntru_par->mul_engine);  
   
    Polynomial m(ntru_par->size, ntru_par->coef_modulus); 
     
    PlaintextEncoding encoding(full_domain, t, Q); 
    std::unique_ptr<NTRUCT> ct(new NTRUCT(ntru_par)); 
    Polynomial out(ntru_par->size, ntru_par->coef_modulus);  
    std::cout << "Start" << std::endl;
    bool test = true;
    for(int32_t i = 0; i < test_num; ++i){
        //rand.uniform_array(m.coefs, N, t); 
        rand->fill_array(m.coefs, N); 
         sk->kdm_encode_and_encrypt(ct.get(), &m, encoding); 

         {
            /// Serialize and Deserialize  RLWE Param 
            std::ofstream os("NTRUCT_test", std::ios::binary); 
            cereal::BinaryOutputArchive oarchive(os); 
            oarchive(ct); 
            os.close();   
         }  
         std::unique_ptr<NTRUCT> ct_test;
         { 
            std::ifstream is("NTRUCT_test", std::ios::binary);
            cereal::BinaryInputArchive iarchive(is);  
            iarchive(ct_test);   
            std::remove("NTRUCT_test"); 
         }

        sk->decrypt(&out, ct_test.get(), encoding); 
        //Utils::array_mod_form(out.coefs, out.coefs, N, t);
        if(!Utils::is_eq_poly(out.coefs, m.coefs, N)){
            std::cout << "NTRU_test: Fail" << std::endl;
            std::cout << "out: " << Utils::to_string(out.coefs, ntru_par->size) << std::endl;  
            std::cout << "m: " << Utils::to_string(m.coefs, ntru_par->size) << std::endl;  
            test = false;
            return;
        }
    }
    if(test){
        std::cout << "NTRU_test: OK" << std::endl;
    }else{ 
        throw std::logic_error("NTRU_test: Fail");
    }

    bool add_test = true;
    Polynomial m_1(ntru_par->size, ntru_par->coef_modulus);
    Polynomial m_2(ntru_par->size, ntru_par->coef_modulus);
    Polynomial exp(ntru_par->size, ntru_par->coef_modulus);
    for(int32_t i = 0; i < test_num; ++i){   
        //rand.uniform_array(m_1.coefs, ntru_par->size, t);  
        rand->fill_array(m_1.coefs,ntru_par->size);  

        //rand.uniform_array(m_2.coefs, ntru_par->size, t); 
        rand->fill_array(m_2.coefs,ntru_par->size);    
        for(int32_t j = 0; j < ntru_par->size; ++j){ 
            exp.coefs[j] = (m_1.coefs[j] + m_2.coefs[j]) % t;
        }  
          
        //RLWECT ct_1 = sk->scale_and_encrypt(&m_1, t);
        //RLWECT ct_2 = sk->scale_and_encrypt(&m_2, t);  
        std::unique_ptr<NTRUCT> ct_1(sk->kdm_encode_and_encrypt(&m_1, encoding));
        std::unique_ptr<NTRUCT> ct_2(sk->kdm_encode_and_encrypt(&m_2, encoding));  
        std::unique_ptr<NTRUCT> ct_3(new NTRUCT(ntru_par)); 
         
        ct_1->add(ct_3.get(), ct_2.get());   
        sk->decrypt(&out, ct_3.get(), encoding);    
          
        Utils::array_mod_form(out.coefs, out.coefs, N, t);    
        if(!Utils::is_eq_poly(out.coefs, exp.coefs, N)){
            std::cout << "NTRU ADD test: Fail" << std::endl;
            std::cout << "out: " << Utils::to_string(out.coefs, ntru_par->size) << std::endl;  
            std::cout << "exp: " << Utils::to_string(exp.coefs, ntru_par->size) << std::endl;  
            std::cout << "m_1: " << Utils::to_string(m_1.coefs, ntru_par->size) << std::endl;  
            std::cout << "m_2: " << Utils::to_string(m_2.coefs, ntru_par->size) << std::endl;  
            add_test = false;
            return;
        }
    }
    if(add_test){
        std::cout << "NTRU ADD test: OK" << std::endl;
    }else{ 
        throw std::logic_error("NTRU ADD test: Fail");
    }


    bool sub_test = true; 
    for(int32_t i = 0; i < test_num; ++i){   
        //rand.uniform_array(m_1.coefs, ntru_par->size, t);  
        rand->fill_array(m_1.coefs,ntru_par->size);
        //rand.uniform_array(m_2.coefs, ntru_par->size, t);
        rand->fill_array(m_2.coefs,ntru_par->size);   
        for(int32_t j = 0; j < ntru_par->size; ++j){ 
            exp.coefs[j] = Utils::integer_mod_form(m_1.coefs[j] - m_2.coefs[j], t);
        }   
        std::unique_ptr<NTRUCT> ct_1(sk->kdm_encode_and_encrypt(&m_1, encoding));
        std::unique_ptr<NTRUCT> ct_2(sk->kdm_encode_and_encrypt(&m_2, encoding));  
        NTRUCT ct_3(ntru_par);  
        ct_1->sub(&ct_3, ct_2.get());   
        sk->decrypt(&out, &ct_3, encoding);     
        Utils::array_mod_form(out.coefs, out.coefs, N, t);    
        if(!Utils::is_eq_poly(out.coefs, exp.coefs, N)){
            std::cout << "NTRU SUB test: Fail" << std::endl;
            std::cout << "out: " << Utils::to_string(out.coefs, ntru_par->size) << std::endl;  
            std::cout << "exp: " << Utils::to_string(exp.coefs, ntru_par->size) << std::endl;  
            std::cout << "m_1: " << Utils::to_string(m_1.coefs, ntru_par->size) << std::endl;  
            std::cout << "m_2: " << Utils::to_string(m_2.coefs, ntru_par->size) << std::endl;  
            sub_test = false;
            return;
        }
    }
    if(sub_test){
        std::cout << "NTRU SUB test: OK" << std::endl;
    }else{ 
        throw std::logic_error("NTRU SUB test: Fail");
    }
 
    bool neg_test = true; 
    for(int32_t i = 0; i < test_num; ++i){   
        //rand.uniform_array(m_1.coefs, ntru_par->size, t);   
        rand->fill_array(m_1.coefs,ntru_par->size); 
        for(int32_t j = 0; j < ntru_par->size; ++j){ 
            exp.coefs[j] = Utils::integer_mod_form(-m_1.coefs[j], t);
        }   
        std::unique_ptr<NTRUCT> ct_1(sk->kdm_encode_and_encrypt(&m_1, encoding)); 
        NTRUCT ct_3(ntru_par); 
        ct_1->neg(&ct_3);
        sk->decrypt(&out, &ct_3, encoding);     
        Utils::array_mod_form(out.coefs, out.coefs, N, t);    
        if(!Utils::is_eq_poly(out.coefs, exp.coefs, N)){
            std::cout << "NTRU NEG test: Fail" << std::endl;
            std::cout << "out: " << Utils::to_string(out.coefs, ntru_par->size) << std::endl;  
            std::cout << "exp: " << Utils::to_string(exp.coefs, ntru_par->size) << std::endl;  
            std::cout << "m_1: " << Utils::to_string(m_1.coefs, ntru_par->size) << std::endl;   
            neg_test = false;
            return;
        }
    }
    if(neg_test){
        std::cout << "NTRU NEG test: OK" << std::endl;
    }else{ 
        throw std::logic_error("NTRU NEG test: Fail");
    }

      std::shared_ptr<Distribution> rand_rot = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, 2*N));
    bool negacyclic_rotate_test = true; 
    int64_t rot;
    for(int32_t i = 0; i < test_num; ++i){   
        //rand.uniform_array(m_1.coefs, ntru_par->size, t);    
        rand->fill_array(m_1.coefs,ntru_par->size);
        rot = rand_rot->next();
        Utils::negacyclic_rotate_poly(exp.coefs, m_1.coefs, N, rot);
        Utils::array_mod_form(exp.coefs, exp.coefs, N, t);
        std::unique_ptr<NTRUCT> ct_1(sk->kdm_encode_and_encrypt(&m_1, encoding)); 
        NTRUCT ct_3(ntru_par); 
        ct_1->negacyclic_rotate(&ct_3, rot);
        sk->decrypt(&out, &ct_3, encoding);     
        Utils::array_mod_form(out.coefs, out.coefs, N, t);    
        if(!Utils::is_eq_poly(out.coefs, exp.coefs, N)){
            std::cout << "NTRU Negacyclic Rotate test: Fail" << std::endl;
            std::cout << "out: " << Utils::to_string(out.coefs, ntru_par->size) << std::endl;  
            std::cout << "exp: " << Utils::to_string(exp.coefs, ntru_par->size) << std::endl;  
            std::cout << "m_1: " << Utils::to_string(m_1.coefs, ntru_par->size) << std::endl;   
            neg_test = false;
            return;
        }
    }
    if(negacyclic_rotate_test){
        std::cout << "NTRU Negacyclic Rotate test: OK" << std::endl;
    }else{ 
        throw std::logic_error("NTRU Negacyclic Rotate test: Fail");
    }
 
   /// TODO: Fix this test
   /*
    bool mul_test = true;
    Polynomial scalar(ntru_par->size, ntru_par->coef_modulus, ntru_par->mul_engine); 
    for(int i = 0; i < test_num; ++i){
        //rand.uniform_array(m_1.coefs, N, t);  
        rand->fill_array(m_1.coefs, N); 
        // NOTE: We are doing a quite sparse polynomial here, because the error may blow up and the test will fail
        //rand.uniform_array(scalar.coefs, N/64, t);
        rand->fill_array(scalar.coefs,  N/64);
        Utils::mul_mod(exp.coefs, m_1.coefs, N, scalar.coefs, N, N, t, negacyclic);
        std::unique_ptr<NTRUCT> ct_1(sk->kdm_encode_and_encrypt(&m_1, encoding)); 
        NTRUCT ct_3(ntru_par);
        ct_1->mul(&ct_3, &scalar); 
        sk->decrypt(&out, &ct_3, encoding); 
        //Utils::array_mod_form(out.coefs, out.coefs, N, t); 
        if(!Utils::is_eq_poly(out.coefs, exp.coefs, N)){
            std::cout << "NTRU MUL test: Fail" << std::endl;
            std::cout << "out: " << Utils::to_string(out.coefs, ntru_par->size) << std::endl;  
            std::cout << "exp: " << Utils::to_string(exp.coefs, ntru_par->size) << std::endl;  
            mul_test = false;
            return;
        }
    }
    if(mul_test){
        std::cout << "NTRU MUL test: OK" << std::endl;
    }else{ 
        throw std::logic_error("NTRU MUL test: Fail");
    } 
   */

 
   std::shared_ptr<LWESK> lwe_sk(sk->extract_lwe_key());  
   LWECT lwe_ct(lwe_sk->param);
   int64_t lwe_msg;
   test = true;
   for(int32_t i = 0; i < test_num; ++i){
      //rand.uniform_array(m.coefs, N, t);  
      rand->fill_array(m.coefs, N); 
      ct = std::unique_ptr<NTRUCT>(sk->kdm_encode_and_encrypt(&m, encoding));
      ct->extract_lwe(&lwe_ct); 
      sk->decrypt(&out, ct.get(), encoding); 
      lwe_msg = lwe_sk->decrypt(&lwe_ct, encoding); 
      if(!(out.coefs[0] == lwe_msg)){
         std::cout << "LWE_NTRU_Extraction_test: Fail" << std::endl;   
         std::cout << "sk->sk: " << Utils::to_string(sk->sk.coefs, sk->param->size) << std::endl;  
         std::cout << std::endl; 
         std::cout << "lwe_sk: " << Utils::to_string(lwe_sk->key, lwe_sk->param->dim) << std::endl;  
         std::cout << std::endl;   
         std::cout << "ct: " << Utils::to_string(ct->ct_poly.coefs, sk->param->size) << std::endl;  
         std::cout << std::endl; 
         std::cout << "lwe_ct: " << Utils::to_string((int64_t*)lwe_ct.ct, lwe_sk->param->dim+1) << std::endl;  
         std::cout << std::endl; 
         std::cout << "out.coefs[0]: " << out.coefs[0] << std::endl;  
         std::cout << "m.coefs[0]: " << m.coefs[0] << std::endl;  
         std::cout << "lwe_msg: " << lwe_msg << std::endl;   
         test = false;
         return;
      }
   }
   if(test){
     std::cout << "LWE_NTRU_Extraction_test: OK" << std::endl;
   }else{ 
     throw std::logic_error("LWE_NTRU_Extraction_test: Fail");
   } 
  
}

 

void gadget_ntru_test(int32_t test_num,  int64_t N, int64_t Q, int64_t base, PolynomialArithmetic arithmetic){
    std::cout << "============== gadget_rlwe_test (N = " << N << ", Q = "<< Q << ", base: " << base << ") ==================" << std::endl;
  
    int32_t t = 5; 
    PlaintextEncoding encoding(full_domain, t, Q);
    //Sampler rand;
    std::shared_ptr<Distribution> rand = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, t-1)); 
    KeyDistribution rlwe_key_type = ternary;
    std::shared_ptr<NTRUParam> ntru_par(new NTRUParam(negacyclic, N, Q, arithmetic)); 
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


    Polynomial m(ntru_par->size, ntru_par->coef_modulus); 
    Polynomial out(ntru_par->size, ntru_par->coef_modulus);
    Polynomial gadget_m(ntru_par->size, ntru_par->coef_modulus);
    gadget_m.zeroize();
    gadget_m.coefs[0] = 1;
    Polynomial exp_poly(ntru_par->size, ntru_par->coef_modulus);


   
    bool test = true;
    std::cerr << "Test: " << 0 ;
    for(int32_t i = 0; i < test_num; ++i){
        //rand.uniform_array(m.coefs, N, t); 
        rand->fill_array(m.coefs, N);
       // rand.uniform_array(gadget_m.coefs, N, t); 
        rand->fill_array(gadget_m.coefs, N); 
        Utils::mul_mod(exp_poly.coefs, m.coefs, N, gadget_m.coefs, N, N, t, negacyclic);
        std::unique_ptr<NTRUCT> ct(sk->kdm_encode_and_encrypt(&m, encoding));
        std::shared_ptr<NTRUGadgetCT> g_ct_test = std::static_pointer_cast<NTRUGadgetCT>(std::shared_ptr<GadgetVectorCT>(gadget_sk.gadget_encrypt(&gadget_m))); 
         std::shared_ptr<NTRUGadgetCT> g_ct;
         {
            /// Serialize and Deserialize  RLWE Param 
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
        std::cerr << "\rTest: " << i ;
        g_ct->mul(&ct_prod, ct.get()); 
        sk->decrypt(&out, &ct_prod, encoding);
        Utils::array_mod_form(out.coefs, out.coefs, N, t);
        if(!Utils::is_eq_poly(out.coefs, exp_poly.coefs, N)){ 
            std::cerr << "\rFail at: " << i << std::endl;
            std::cerr << "gadget rlwe test: Fail" << std::endl;
            std::cerr << "out: " << Utils::to_string(out.coefs, ntru_par->size) << std::endl;  
            std::cerr << "exp_poly: " << Utils::to_string(exp_poly.coefs, ntru_par->size) << std::endl;  
            std::cerr << "m: " << Utils::to_string(m.coefs, ntru_par->size) << std::endl;  
            test = false;
            break;
        } 
    }
    std::cerr << "\rTest: " << 100 << std::endl; 
    if(test){
        std::cerr << "gadget rlwe test: OK" << std::endl;
    }else{ 
        throw std::logic_error("gadget rlwe test: Fail");
    }     
 

}

void extract_and_key_switch_test(int32_t test_num, int64_t N, int64_t Q, PolynomialArithmetic arithmetic){
   std::cout << "=========== extract_and_key_switch_test (N = " << N << ", Q = " << Q << ") ========= " << std::endl;

   int32_t t = 13;
   //Sampler rand;
   std::shared_ptr<Distribution> rand = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, t)); 
   KeyDistribution rlwe_key_type = binary;
   std::shared_ptr<NTRUParam> ntru_par(new NTRUParam(negacyclic, N, Q, arithmetic)); 
   std::shared_ptr<NTRUSK> sk(new NTRUSK(ntru_par, 3.2));  
   Polynomial m(ntru_par->size, ntru_par->coef_modulus);  
   PlaintextEncoding encoding(full_domain, t, Q); 
   std::unique_ptr<NTRUCT> ct(new NTRUCT(ntru_par)); 
   Polynomial out(ntru_par->size, ntru_par->coef_modulus);  

   
   std::shared_ptr<LWESK> lwe_sk(sk->extract_lwe_key());  
   LWECT lwe_ct(lwe_sk->param);
   int64_t lwe_msg;
   bool test = true;
   for(int32_t i = 0; i < test_num; ++i){
      //rand.uniform_array(m.coefs, N, t);  
      rand->fill_array(m.coefs, N);
      ct = std::unique_ptr<NTRUCT>(sk->kdm_encode_and_encrypt(&m, encoding));
      ct->extract_lwe(&lwe_ct); 
      sk->decrypt(&out, ct.get(), encoding); 
      lwe_msg = lwe_sk->decrypt(&lwe_ct, encoding); 
      if(!(out.coefs[0] == lwe_msg)){
         std::cout << "LWE_NTRU_Extraction_test: Fail" << std::endl;   
         std::cout << "sk->sk: " << Utils::to_string(sk->sk.coefs, sk->param->size) << std::endl;  
         std::cout << std::endl; 
         std::cout << "lwe_sk: " << Utils::to_string(lwe_sk->key, lwe_sk->param->dim) << std::endl;  
         std::cout << std::endl;   
         std::cout << "ct: " << Utils::to_string(ct->ct_poly.coefs, sk->param->size) << std::endl;  
         std::cout << std::endl; 
         std::cout << "lwe_ct: " << Utils::to_string((int64_t*)lwe_ct.ct, lwe_sk->param->dim+1) << std::endl;  
         std::cout << std::endl; 
         std::cout << "out.coefs[0]: " << out.coefs[0] << std::endl;  
         std::cout << "m.coefs[0]: " << m.coefs[0] << std::endl;  
         std::cout << "lwe_msg: " << lwe_msg << std::endl;   
         test = false;
         return;
      }
   }
   if(test){
     std::cout << "LWE_NTRU_Extraction_test: OK" << std::endl;
   }else{ 
     throw std::logic_error("LWE_NTRU_Extraction_test: Fail");
   }  

   std::shared_ptr<LWEParam> lwe_target_param(new LWEParam(256, Q));
   double stddev_target = 3.2; 
   std::shared_ptr<LWESK> lwe_sk_target(new LWESK(lwe_target_param, stddev_target, binary));   
   //std::shared_ptr<LWEGadgetParam> gadget_param(new  LWEGadgetParam(lwe_target_param, 16));
   std::shared_ptr<LWEGadgetSK> gadget_lwe_sk_target(new LWEGadgetSK(lwe_sk_target, 16)); 
   std::shared_ptr<LWEToLWEKeySwitchKey> ksk(new LWEToLWEKeySwitchKey(lwe_sk, gadget_lwe_sk_target));
   LWECT ct_target(lwe_target_param);

   test = true;
   for(int32_t i = 0; i < test_num; ++i){
      //rand.uniform_array(m.coefs, N, t);  
      rand->fill_array(m.coefs, N);
      ct = std::unique_ptr<NTRUCT>(sk->kdm_encode_and_encrypt(&m, encoding));
      ct->extract_lwe(&lwe_ct); 
      ksk->lwe_to_lwe_key_switch(&ct_target, &lwe_ct); 
      sk->decrypt(&out, ct.get(), encoding); 
      lwe_msg = lwe_sk_target->decrypt(&ct_target, encoding); 
      if(!(out.coefs[0] == lwe_msg)){
            std::cout << "LWE_NTRU_Key_Swiitching_test: Fail" << std::endl;    
            std::cout << "out.coefs[0]: " << out.coefs[0] << std::endl;  
            std::cout << "m.coefs[0]: " << m.coefs[0] << std::endl;  
            std::cout << "lwe_msg: " << lwe_msg << std::endl;   
            test = false;
            return;
      }
   }
   if(test){
     std::cout << "LWE_NTRU_Key_Swiitching_test: OK" << std::endl;
   }else{ 
     throw std::logic_error("LWE_NTRU_Key_Swiitching_test: Fail");
   }   
}




int32_t main(){
   
   /*
   large_modulu_ntru_tests(); 
   kdm_ntru_tests();
   temp_test_decryption_single_coefficient();
 
   test_ntru_mod_switching();  
   //test_power_of_two_ntru_mod_switching();  
 
   gadget_ntru_fft_tests(); 
   */ 
 
  
   ntru_test(100, 4096, 35184371884033, ntt64);  
  
   ntru_test(100, 4096, 288230376151130113, ntt64); 
   ntru_test(100, 4096, 1152921504606830593, ntt64);
   ntru_test(100, 4096, 2305843009213554689, ntt64); 
   ntru_test(100, 4096, 4611686018427322369, ntt64);// 57 bit

   extract_and_key_switch_test(100, 4096, 35184371884033, ntt64);
   extract_and_key_switch_test(100, 4096, 288230376151130113, ntt64); 
   extract_and_key_switch_test(100, 4096, 1152921504606830593, ntt64);
 



   /// NOTE: With double_fft there seems to be a problem....
   //gadget_ntru_test(100,  512, 67104769, 8, double_fft);   
   gadget_ntru_test(100, 512, 67104769, 8, ntt64); 
 
   gadget_ntru_test(100, 4096, 288230376151130113, 8, ntt64);
   // 60 bit
   gadget_ntru_test(100, 4096, 1152921504606830593, 8, ntt64);
   // 61 bit (May fail actually because we have basis = 8 decomposition, which is 3 bits, giving us 61+3 = 64 bits.)
   gadget_ntru_test(10, 4096, 2305843009213554689, 4, ntt64); 

   gadget_ntru_test(10, 4096, 35184371884033, 32768, ntt64);   
     
   return 0;
}
