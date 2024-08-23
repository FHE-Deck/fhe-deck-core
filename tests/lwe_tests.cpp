 
#include <iostream>
#include <fstream>
#include "lwe.h" 
#include <NTL/ZZX.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_p.h>
#include <random>


using namespace fhe_deck;

void write_param(std::shared_ptr<LWEParam> param){ 
    LWEParam param_temp(param->dim, param->modulus);
    std::ofstream os("lweParam_test", std::ios::binary); 
    cereal::BinaryOutputArchive oarchive(os); 
    oarchive(param); 
    os.close();
}


void basic_lwe_test(){ 
   std::cout << "========= Testing LWE ============" << std::endl;
    
    int32_t n = 10;
    int64_t Q = 1073741827; 
    double stddev = 3.2;
    std::shared_ptr<LWEParam> param(new LWEParam(n, Q));
    LWESK lwe_sk(param, stddev, binary);  

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
            std::cout << "Param Serialization Test: Fail" << std::endl; 
            std::cout << "param->dim: " << param->dim << ", param2->dim: " << param2->dim <<  std::endl;    
        }else{
            std::cout << "Param Serialization Test: OK" << std::endl;  
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
            lwe_sk.stddev != lwe_sk_2.stddev || lwe_sk.key_type != lwe_sk_2.key_type ||
            (Utils::is_eq_poly(lwe_sk.key, lwe_sk_2.key, lwe_sk.param->dim) == false)){
            std::cout << "LWESK Serialization Test: Fail" << std::endl;  
        }else{
            std::cout << "LWESK Serialization Test: OK" << std::endl;  
        }  
        std::remove("lwe_sk_test");
    }

    int64_t t = 8;
    PlaintextEncoding encoding(full_domain, t, Q);
    int64_t delta_Q_t = (int64_t)round((double)Q/(double)t);
    int64_t msg = 2;
    int64_t scaled_msg = encoding.encode_message(msg);

    std::shared_ptr<LWECT> ct(lwe_sk.encrypt(scaled_msg)); 
    int64_t phase = lwe_sk.partial_decrypt(ct.get());
    int64_t error = phase - scaled_msg;
    int64_t dec = lwe_sk.decrypt(ct.get(), encoding); 


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
            (Utils::is_eq_poly((int64_t*)ct->ct, (int64_t*)ct->ct, lwe_sk.param->dim+1) == false)){
            std::cout << "LWECT Serialization Test: Fail" << std::endl;  
        }else{
            std::cout << "LWECT Serialization Test: OK" << std::endl;  
        }  
        std::remove("lwe_ct_test"); 
    }

     
    if(dec == msg){
        std::cout << "Basic LWE Decryption Test: OK" << std::endl; 
    }else{
        std::cout << "Basic LWE Decryption Test: Fail" << std::endl; 
    }
 
    int64_t scalar = 3; 
    LWECT ct_mul(param); 
    ct->mul(&ct_mul, scalar); 
    int64_t scalar_dec = lwe_sk.decrypt(&ct_mul, encoding); 
    int64_t expected = (msg * scalar) % t;
    int64_t scalar_error =  lwe_sk.partial_decrypt(&ct_mul) - expected * delta_Q_t;
    if(scalar_dec == expected){
        std::cout << "Scalar Multiplication Test: OK" << std::endl; 
    }else{
        std::cout << "Scalar Multiplication Test: Fail" << std::endl; 
        std::cout << "scalar_dec: " << scalar_dec << std::endl; 
        std::cout << "scalar_error: " << scalar_error << std::endl;
    }

  
    int64_t m_1 = 2;
    int64_t m_2 = 3;
    LWECT *ct_1 = lwe_sk.encrypt(delta_Q_t * m_1);
    LWECT *ct_2 = lwe_sk.encrypt(delta_Q_t * m_2); 
    LWECT ct_added(param);
    ct_1->add(&ct_added, ct_2);
    int64_t added_expected = (m_1 + m_2) % t;
    int64_t added_dec = lwe_sk.decrypt(&ct_added, encoding);
    if(added_expected == added_dec){
        std::cout << "LWE Add Test: OK" << std::endl; 
    }else{
        std::cout << "LWE Add Test: Fail" << std::endl; 
        std::cout << "added_expected: " << added_expected << std::endl; 
        std::cout << "added_dec: " << added_dec << std::endl; 
    }
 
    delete ct_1;
    delete ct_2;
}


void gadget_multiplication_test(){
    std::cout << "========= gadget_multiplication_test ============" << std::endl;
    
    int32_t n = 10;
    int64_t Q = 1073741827; 
    double stddev = 3.2;
    std::shared_ptr<LWEParam> param =  std::shared_ptr<LWEParam>(new LWEParam(n, Q)); 
    std::shared_ptr<LWESK> lwe = std::shared_ptr<LWESK>(new LWESK(param, stddev, binary));  
      
    int64_t t = 8;
    PlaintextEncoding encoding(full_domain, t, Q);
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
        std::cout << "LWEGadgetSK Serialization Test: Fail" << std::endl;  
    }else{
        std::cout << "LWEGadgetSK Serialization Test: OK" << std::endl;  
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
            std::cout << "LWEGadgetCT Serialization Test: Fail" << std::endl;  
        }else{
            std::cout << "LWEGadgetCT Serialization Test: OK" << std::endl;  
        }  
        std::remove("LWEGadgetCT_test"); 
    }


    gadget_ct->gadget_mul(&ct, scaled_msg);
  
    int64_t dec = lwe->decrypt(&ct, encoding);
    int64_t expected = (msg * gadget_msg) % t;
    if(dec == expected){
        std::cout << "Gadget Multiplication Test: OK" << std::endl;
    }else{
        std::cout << "Gadget Multiplication Test: Fail" << std::endl;
        std::cout << "expected: " <<  expected << std::endl;
        std::cout << "dec: " <<  dec << std::endl;
    }

}

void mod_switching_test(){

    std::cout << "========= mod_switching_test ============" << std::endl;
    
    int32_t n = 10;
    int64_t Q = 1073741827; 
    double stddev = 3.2;
    std::shared_ptr<LWEParam> param =  std::shared_ptr<LWEParam>(new LWEParam(n, Q)); 
    LWESK lwe(param, stddev, binary);  
    int64_t t = 8;
    PlaintextEncoding encoding(full_domain, t, Q);
    int64_t delta_Q_t = (int64_t)round((double)Q/(double)t);
    int64_t msg = 2;
    int64_t scaled_msg = delta_Q_t * msg;
 
    LWECT *ct = lwe.encrypt(scaled_msg); 
    int64_t dec = lwe.decrypt(ct, encoding);  
     
    if(dec == msg){
        std::cout << "Basic LWE Decryption Test: OK" << std::endl; 
    }else{
        std::cout << "Basic LWE Decryption Test: Fail" << std::endl; 
    }

    int64_t new_Q = 1073741827;
    
    int64_t delta_new_Q_t = (int64_t)round((double)new_Q/(double)t);
    std::shared_ptr<LWEParam> new_param = std::shared_ptr<LWEParam>(new LWEParam(n, new_Q));  
    LWECT new_c(new_param);
    LWEModSwitcher mod_switcher(param, new_param);
    mod_switcher.switch_modulus(&new_c, ct);

    /// TODO: How is this working? I should initialize a lwe secret key which is modulus switched to the new one.
    int64_t new_dec = lwe.decrypt(&new_c, encoding);  
    if(new_dec == msg){
        std::cout << "LWE Decryption After Modulus Switching Test: OK" << std::endl; 
    }else{
        std::cout << "LWE Decryption After Modulus Switching Test: Fail" << std::endl; 
        std::cout << "new_dec: " << new_dec << ", msg: " << msg << std::endl;
    }
    delete ct;
}


int32_t main(){
 
    basic_lwe_test();
    gadget_multiplication_test();
    mod_switching_test();
}
