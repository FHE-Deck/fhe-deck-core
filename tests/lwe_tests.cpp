 
#include <gtest/gtest.h>

#include <iostream>
#include <fstream>

#include "fhe_deck.h" 
#include "verbose_stream.hpp"

/// @brief  This flag is defined in test_main.cpp
extern bool verbose;

using namespace FHEDeck;
 
 
TEST(LWETests, BasicLWETest){    
#if defined(USE_CEREAL)
   print_out << "========= Testing LWE ============" << std::endl;
    
    int32_t n = 10;
    int64_t Q = 1073741827; 
    double stddev = 3.2;
    std::shared_ptr<LWEParam> param(new LWEParam(n, Q));
    LWESK lwe_sk(param, stddev, KeyDistribution::binary);  

    {
        /// Serialize and Deserialize  LWE Param 
        std::ofstream os_lwe_param("lweParam_test", std::ios::binary); 
        cereal::BinaryOutputArchive oarchive_lwe_param(os_lwe_param); 
        oarchive_lwe_param(param); 
        os_lwe_param.close();   
    } 
  
    {
        std::shared_ptr<LWEParam> param2;
        std::ifstream is_lwe_param("lweParam_test", std::ios::binary);
        cereal::BinaryInputArchive iarchive_lwe_param(is_lwe_param);  
        iarchive_lwe_param(param2);  
        if(param->dim != param2->dim || param->modulus != param2->modulus){
            FAIL();
            print_out << "Param Serialization Test: Fail" << std::endl; 
            print_out << "param->dim: " << param->dim << ", param2->dim: " << param2->dim <<  std::endl;    
        } 
        std::remove("lweParam_test"); 
    }

    {
        /// Serialize and Deserialize LWE SK 
        std::ofstream os_lwe_sk("lwe_sk_test", std::ios::binary); 
        cereal::BinaryOutputArchive oarchive_lwe_sk(os_lwe_sk); 
        oarchive_lwe_sk(lwe_sk); 
        os_lwe_sk.close();   
    }
    {   
        LWESK lwe_sk_2;
        std::ifstream is_lwe_sk("lwe_sk_test", std::ios::binary);
        cereal::BinaryInputArchive iarchive_lwe_sk(is_lwe_sk);  
        iarchive_lwe_sk(lwe_sk_2);  
        if(lwe_sk.param->dim != lwe_sk_2.param->dim || 
            lwe_sk.param->modulus != lwe_sk_2.param->modulus || 
            lwe_sk.stddev != lwe_sk_2.stddev || lwe_sk.key_type != lwe_sk_2.key_type){
                print_out << "LWESK Serialization Test: Fail" << std::endl;  
                FAIL();
        } 
        for(int32_t i{0}; i < lwe_sk.param->dim; ++i){
            if(lwe_sk.key[i] != lwe_sk_2.key[i]){  
                print_out << "LWESK Serialization Test: Fail" << std::endl;  
                FAIL();
            }
        }
        std::remove("lwe_sk_test");
    }

    int64_t t = 8;
    PlaintextEncoding encoding(PlaintextEncodingType::full_domain, t, Q);
    int64_t delta_Q_t = (int64_t)round((double)Q/(double)t);
    int64_t msg = 2;
    int64_t scaled_msg = encoding.encode_message(msg);

    std::shared_ptr<LWECT> ct(lwe_sk.encrypt(scaled_msg)); 
    int64_t phase = lwe_sk.partial_decrypt(*ct.get());
    int64_t error = phase - scaled_msg;
    int64_t dec = lwe_sk.decrypt(*ct.get(), encoding); 


    {
        /// Serialize and Deserialize Cihertext
        std::ofstream os_ct("lwe_ct_test", std::ios::binary); 
        cereal::BinaryOutputArchive oarchive_ct(os_ct); 
        oarchive_ct(ct); 
        os_ct.close();   
    }
    {
        std::shared_ptr<LWECT> ct_test;
        std::ifstream is_ct("lwe_ct_test", std::ios::binary);
        cereal::BinaryInputArchive iarchive_ct(is_ct);  
        iarchive_ct(ct_test);  
        if(ct->param->dim != ct_test->param->dim || 
            ct->param->modulus != ct_test->param->modulus ||  
            (ct->ct != ct_test->ct)){
                print_out << "LWECT Serialization Test: Fail" << std::endl;  
                FAIL();
        } 
        std::remove("lwe_ct_test"); 
    }

    ASSERT_EQ(dec, msg); 
 
    int64_t scalar = 3; 
    LWECT ct_mul(param); 
    ct->mul(ct_mul, scalar); 
    int64_t scalar_dec = lwe_sk.decrypt(ct_mul, encoding); 
    int64_t expected = (msg * scalar) % t;
    int64_t scalar_error =  lwe_sk.partial_decrypt(ct_mul) - expected * delta_Q_t;
    ASSERT_EQ(scalar_dec, expected); 

  
    int64_t m_1 = 2;
    int64_t m_2 = 3;
    std::shared_ptr<LWECT> ct_1 = lwe_sk.encrypt(delta_Q_t * m_1);
    std::shared_ptr<LWECT> ct_2 = lwe_sk.encrypt(delta_Q_t * m_2); 
    LWECT ct_added(param);
    ct_1->add(ct_added, *ct_2);
    int64_t added_expected = (m_1 + m_2) % t;
    int64_t added_dec = lwe_sk.decrypt(ct_added, encoding);
    ASSERT_EQ(added_expected, added_dec); 

    #endif  
}

 
TEST(LWETests, GadgetMulTest){    
#if defined(USE_CEREAL)
    print_out << "========= gadget_multiplication_test ============" << std::endl;
    
    int32_t n = 10;
    int64_t Q = 1073741827; 
    double stddev = 3.2;
    std::shared_ptr<LWEParam> param =  std::shared_ptr<LWEParam>(new LWEParam(n, Q)); 
    std::shared_ptr<LWESK> lwe = std::shared_ptr<LWESK>(new LWESK(param, stddev, KeyDistribution::binary));  
      
    int64_t t = 8;
    PlaintextEncoding encoding(PlaintextEncodingType::full_domain, t, Q);
    int64_t delta_Q_t = (int64_t)round((double)Q/(double)t);
    int64_t msg = 2;
    int64_t scaled_msg = delta_Q_t * msg;
    int64_t gadget_msg = 3;

   // int32_t k = 3;
   // 2**3
   int32_t base = 8;
   // From python
   // 11 = math.ceil(math.log(1073741827, 8)) 

    LWEGadgetSK lwe_g(lwe, base); 
    /// Serialize and Deserialize LWEGadgetSK 
    std::ofstream os_lwe_sk("LWEGadgetSK_test", std::ios::binary); 
    cereal::BinaryOutputArchive oarchive_lwe_sk(os_lwe_sk); 
    oarchive_lwe_sk(lwe_g); 
    os_lwe_sk.close();   
    LWEGadgetSK gadget_lwe_sk;
    std::ifstream is_lwe_sk("LWEGadgetSK_test", std::ios::binary);
    cereal::BinaryInputArchive iarchive_lwe_sk(is_lwe_sk);  
    iarchive_lwe_sk(gadget_lwe_sk);  
    if(lwe_g.base != gadget_lwe_sk.base || 
        lwe_g.digits != gadget_lwe_sk.digits || 
        lwe_g.bits_base != gadget_lwe_sk.bits_base){
            FAIL();
        print_out << "LWEGadgetSK Serialization Test: Fail" << std::endl;  
    } 
    std::remove("LWEGadgetSK_test"); 


    LWECT ct(param); 

    std::shared_ptr<LWEGadgetCT> gadget_ct(gadget_lwe_sk.gadget_encrypt(gadget_msg));
  
    {
        /// Serialize and Deserialize LWEGadgetSK 
        std::ofstream os_glwe_ct("LWEGadgetCT_test", std::ios::binary); 
        cereal::BinaryOutputArchive oarchive_glwe_ct(os_glwe_ct); 
        oarchive_glwe_ct(gadget_ct); 
        os_glwe_ct.close();  
    }
    {
        std::shared_ptr<LWEGadgetCT> gadget_ct_test;
        std::ifstream is_glwe_ct("LWEGadgetCT_test", std::ios::binary);
        cereal::BinaryInputArchive iarchive_glwe_ct(is_glwe_ct);  
        iarchive_glwe_ct(gadget_ct_test);  
        if(gadget_ct->base != gadget_ct_test->base || 
            gadget_ct->digits != gadget_ct_test->digits || 
            gadget_ct->bits_base != gadget_ct_test->bits_base){
                FAIL();
            print_out << "LWEGadgetCT Serialization Test: Fail" << std::endl;  
        } 
        std::remove("LWEGadgetCT_test"); 
    }


    gadget_ct->gadget_mul(ct, scaled_msg);
  
    int64_t dec = lwe->decrypt(ct, encoding);
    int64_t expected = (msg * gadget_msg) % t;
    ASSERT_EQ(dec, expected);
  
    #endif
}
 
TEST(LWETests, ModSwitchTest){ 

    print_out << "========= mod_switching_test ============" << std::endl;
    
    int32_t n = 10;
    int64_t Q = 1073741827; 
    double stddev = 3.2;
    std::shared_ptr<LWEParam> param =  std::shared_ptr<LWEParam>(new LWEParam(n, Q)); 
    LWESK lwe(param, stddev, KeyDistribution::binary);  
    int64_t t = 8;
    PlaintextEncoding encoding(PlaintextEncodingType::full_domain, t, Q);
    int64_t delta_Q_t = (int64_t)round((double)Q/(double)t);
    int64_t msg = 2;
    int64_t scaled_msg = delta_Q_t * msg;
 
    std::shared_ptr<LWECT> ct = lwe.encrypt(scaled_msg); 
    int64_t dec = lwe.decrypt(*ct, encoding);  
     
    ASSERT_EQ(dec, msg); 

    int64_t new_Q = 1073741827;
    
    int64_t delta_new_Q_t = (int64_t)round((double)new_Q/(double)t);
    std::shared_ptr<LWEParam> new_param = std::shared_ptr<LWEParam>(new LWEParam(n, new_Q));  
    LWECT new_c(new_param);
    LWEModSwitcher mod_switcher(param, new_param);
    mod_switcher.switch_modulus(new_c, *ct);

    /// TODO: How is this working? I should initialize a lwe secret key which is modulus switched to the new one.
    int64_t new_dec = lwe.decrypt(new_c, encoding);  
    ASSERT_EQ(new_dec, msg);
 
}
 