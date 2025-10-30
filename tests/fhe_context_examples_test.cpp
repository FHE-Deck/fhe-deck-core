#include <gtest/gtest.h>

#include <iostream>
#include <cassert>
#include <chrono>
#include "fhe_deck.h" 
#include "verbose_stream.hpp"

/// @brief  This flag is defined in test_main.cpp
extern bool verbose;
 
using namespace FHEDeck;

void test_for_default_full_domain_encoding(FHENamedParams param_set){
 
    FHEContext context;  
    
    context.generate_context(param_set);  
    int32_t modulus = context.get_default_plaintext_space();
    PlaintextEncoding encoding = context.get_default_plaintext_encoding();
    encoding.set_type(PlaintextEncodingType::full_domain);
     
    int32_t c1_plain = 1;
    Ciphertext c1  = context.encrypt(c1_plain, encoding);  
    int32_t c2_plain = 2;
    Ciphertext c2  = context.encrypt(2, encoding);  
 
    // Decrypt(c1) == 1
    ASSERT_EQ(context.decrypt(c1), c1_plain); 
    
    // Decrypt(c2) == 2
    ASSERT_EQ(context.decrypt(c2), c2_plain); 
 
    int32_t c3_plain = 0;
    Ciphertext c3 = context.encrypt(c3_plain, encoding);
    c3.add(c3, c1); 
    c3_plain = (c3_plain + c1_plain) % modulus; 
    // Decrypt(c3+c1) == 1
    ASSERT_EQ(context.decrypt(c3), c3_plain); 
    c3.add(c3, c2); 
    c3_plain = (c3_plain + c2_plain) % modulus;
    // Decrypt(c3+c1+c2) == 3
    ASSERT_EQ(context.decrypt(c3),c3_plain); 
    c3.add(c3, c2); 
    c3_plain = (c3_plain + c2_plain) % modulus;  
    // Decrypt(c3+c1+c2+c2) == 1
    ASSERT_EQ(context.decrypt(c3), c3_plain); 
 
    c3.mul(c3, 3); 
    c3_plain = (c3_plain * 3) % modulus;
    // Decrypt((c3+c1+c2+c2) * 3) == 3
    ASSERT_EQ(context.decrypt(c3), c3_plain); 
  
    Ciphertext ct1 = c1; 
    Ciphertext ct2 = c2;
    // Decrypt(ct1) == 1
    ASSERT_EQ(context.decrypt(ct1), c1_plain); 

    // Decrypt(ct2) == 2
    ASSERT_EQ(context.decrypt(ct2), c2_plain); 
    Ciphertext ct3 = ct1 + 1;  
    c3_plain = (c1_plain + 1) % modulus;
    // Decrypt(ct1 + 1) == 2 
    ASSERT_EQ(context.decrypt(ct3), c3_plain); 

    ct3 = 1 + ct1;  
    c3_plain = (1 + c1_plain) % modulus;
    // Decrypt((1+ ct1)) == 2
    ASSERT_EQ(context.decrypt(ct3), c3_plain); 

    ct3 = ct1 - 2; 
    c3_plain = Utils::integer_mod_form(c1_plain - 2, modulus);
    // Decrypt((ct1 - 2)) == 3
    ASSERT_EQ(context.decrypt(ct3), c3_plain); 

    ct3 = 2 - ct1; 
    c3_plain = Utils::integer_mod_form(2 - c1_plain, modulus);
    // Decrypt((2 - ct1)) == 1
    ASSERT_EQ(context.decrypt(ct3), c3_plain); 
 
    ct3 = ct1 * 2; 
    c3_plain = (c1_plain * 2) % modulus;
    // Decrypt((ct1 * 2)) == 2
    ASSERT_EQ(context.decrypt(ct3), c3_plain); 

    ct3 = 2 * ct1; 
    c3_plain = (2 * c1_plain) % modulus;
    // Decrypt((2 * ct1)) == 2
    ASSERT_EQ(context.decrypt(ct3), c3_plain); 

    ct3 = ct1 + ct2; 
    c3_plain = (c1_plain + c2_plain) % modulus;
    // Decrypt((ct1 + ct2)) == 3
    ASSERT_EQ(context.decrypt(ct3), c3_plain); 

    ct3 = ct2 - ct1; 
    c3_plain = Utils::integer_mod_form(c2_plain - c1_plain, modulus);
    
    // Decrypt((ct2 - ct1)) == 1
    ASSERT_EQ(context.decrypt(ct3), c3_plain); 

    // Decrypt(ct1) == 1
    ASSERT_EQ(context.decrypt(ct1), c1_plain);  

    ct3 = - ct1; 
    c3_plain = Utils::integer_mod_form(-c1_plain, modulus);
    // Decrypt((ct3 = - ct1))) == 3
    ASSERT_EQ(context.decrypt(ct3), c3_plain);  

    // Decrypt(ct1) == 1
    ASSERT_EQ(context.decrypt(ct1), c1_plain);  
     
    Ciphertext ct4 = ct1;
    int32_t c4_plain = c1_plain;
    // Decrypt((ct4 = ct1))) == 1
    ASSERT_EQ(context.decrypt(ct4), c4_plain); 
    
    ct4 = ct1;
    c4_plain = c1_plain;
    // Decrypt((ct4 = ct1))) == 1
    ASSERT_EQ(context.decrypt(ct4), c4_plain);  
    ct4 = ct2;
    c4_plain = c2_plain;
    // Decrypt((ct4 = ct2))) == 2
    ASSERT_EQ(context.decrypt(ct4), c4_plain);  
  
    std::vector<Ciphertext> v;
    v.push_back(ct1);
    v.push_back(ct2);

    std::vector<int64_t> scalars;
    scalars.push_back(2);
    scalars.push_back(1);
    int64_t scalar = 3;
    ct4 = context.eval_affine_function(v, scalars, scalar);  

    c4_plain = Utils::integer_mod_form(c1_plain * 2 + c2_plain * 1 + 3, modulus);
    // The outcome should be 3, because (2 * 1 + 1 * 2 + 3) % 4 = 3
    ASSERT_EQ(context.decrypt(ct4), c4_plain);  
  
    auto id = [](int64_t m) -> int64_t {
        return m;
    }; 
  
    HomomorphicAccumulator lut_identity = context.setup_function(id, encoding); 
   
    ct4 = context.eval(ct1, lut_identity);  
    
    c4_plain = c1_plain; 
    ASSERT_EQ(context.decrypt(ct4), c4_plain);  
 
    auto id_plus = [](int64_t m) -> int64_t {
        return (m+1);
    }; 

    HomomorphicAccumulator lut_id_plus = context.setup_function(id_plus, encoding); 
 
    ct4 = context.eval(ct1, lut_id_plus);  
    c4_plain = Utils::integer_mod_form(id_plus(c1_plain), modulus); 
    ASSERT_EQ(context.decrypt(ct4), c4_plain);  

    ct4 = context.eval(ct4, lut_id_plus); 
    c4_plain = Utils::integer_mod_form(id_plus(c4_plain), modulus);
    ASSERT_EQ(context.decrypt(ct4), c4_plain);  
    
    ct4 = context.eval(ct4, lut_id_plus);  
    c4_plain = Utils::integer_mod_form(id_plus(c4_plain), modulus);
    ASSERT_EQ(context.decrypt(ct4), c4_plain); 
    
    std::function<int64_t(int64_t,int64_t)> fun_msb = [](int64_t m, int64_t t) -> int64_t {
        if(m < t/2){
            return 0;
        }else{
            return 1;
        } 
    }; 
    std::function<int64_t(int64_t)> fun_msb_t = std::bind(fun_msb, std::placeholders::_1, modulus);
    HomomorphicAccumulator lut_fun_msb = context.setup_function(fun_msb_t, encoding); 
 
    ct4 = context.eval(ct1, lut_fun_msb);  
    c4_plain = fun_msb_t(c1_plain);
    ASSERT_EQ(context.decrypt(ct4), c4_plain);  
}


void test_for_partial_domain_encoding(FHENamedParams param_set){
    
    FHEContext context;  
    context.generate_context(param_set);
    
    //  The default encoding for this is actually full domain.   
    PlaintextEncoding encoding = context.get_default_plaintext_encoding();
    encoding.set_type(PlaintextEncodingType::partial_domain);
 
    #if defined(USE_CEREAL)
    {
        /// Serialize and Deserialize LWEGadgetSK  
        std::ofstream os_glwe_ct("fhe_context_test", std::ios::binary); 
        
        cereal::BinaryOutputArchive oarchive_glwe_ct(os_glwe_ct); 
        oarchive_glwe_ct(context.config->secret_key); 
        os_glwe_ct.close();  
    }
    std::shared_ptr<FHESecretKey> secret_key;
    {
        std::ifstream is_glwe_ct("fhe_context_test", std::ios::binary);
        cereal::BinaryInputArchive iarchive_glwe_ct(is_glwe_ct);  
        iarchive_glwe_ct(secret_key);   
        std::remove("fhe_context_test"); 
    }
    context.config->secret_key = secret_key;
    {
        /// Serialize and Deserialize LWEGadgetSK  
        std::ofstream os_glwe_ct("fhe_context_test", std::ios::binary); 
        cereal::BinaryOutputArchive oarchive_glwe_ct(os_glwe_ct); 
        oarchive_glwe_ct(context.config->eval_key.bootstrap_pk); 
        os_glwe_ct.close();  
    }
    std::shared_ptr<FunctionalBootstrapPublicKey> bootstrap_pk;
    {
        std::ifstream is_glwe_ct("fhe_context_test", std::ios::binary);
        cereal::BinaryInputArchive iarchive_glwe_ct(is_glwe_ct);  
        iarchive_glwe_ct(bootstrap_pk);   
        std::remove("fhe_context_test"); 
    }
    context.config->eval_key.bootstrap_pk = bootstrap_pk;
    {
        std::ofstream os_glwe_ct("fhe_context_test", std::ios::binary); 
        cereal::BinaryOutputArchive oarchive_glwe_ct(os_glwe_ct); 
        oarchive_glwe_ct(context.config->eval_key.boot_acc_builder); 
        os_glwe_ct.close();  
    }
    std::shared_ptr<VectorCTAccumulatorBuilder> boot_acc_builder;
    {
        std::ifstream is_glwe_ct("fhe_context_test", std::ios::binary);
        cereal::BinaryInputArchive iarchive_glwe_ct(is_glwe_ct);  
        iarchive_glwe_ct(boot_acc_builder);   
        std::remove("fhe_context_test"); 
    }
    context.config->eval_key.boot_acc_builder = boot_acc_builder; 

    {
        std::ofstream os_glwe_ct("fhe_context_test", std::ios::binary); 
        cereal::BinaryOutputArchive oarchive_glwe_ct(os_glwe_ct); 
        oarchive_glwe_ct(context.config->eval_key.encrypt_pk); 
        os_glwe_ct.close();  
    }
    std::shared_ptr<LWEPublicKey> encrypt_pk; 
    {
        std::ifstream is_glwe_ct("fhe_context_test", std::ios::binary);
        cereal::BinaryInputArchive iarchive_glwe_ct(is_glwe_ct);  
        iarchive_glwe_ct(encrypt_pk);   
        std::remove("fhe_context_test"); 
    }
    context.config->eval_key.encrypt_pk = encrypt_pk; 
    {
        std::ofstream os_glwe_ct("fhe_context_test", std::ios::binary); 
        cereal::BinaryOutputArchive oarchive_glwe_ct(os_glwe_ct); 
        oarchive_glwe_ct(context.config->eval_key.sanitization_pk); 
        os_glwe_ct.close();  
    }
    std::shared_ptr<SanitizationKey> sanitization_pk;
    {
        std::ifstream is_glwe_ct("fhe_context_test", std::ios::binary);
        cereal::BinaryInputArchive iarchive_glwe_ct(is_glwe_ct);  
        iarchive_glwe_ct(sanitization_pk);   
        std::remove("fhe_context_test"); 
    }
    context.config->eval_key.sanitization_pk = sanitization_pk; 
    #endif
 

    Ciphertext c0  = context.encrypt(0, encoding);  
    Ciphertext c1  = context.encrypt(1, encoding);    
    Ciphertext c2  = context.encrypt(2, encoding);  
    Ciphertext c3  = context.encrypt(3, encoding);  
   
    // Decrypt(c0) == 0
    ASSERT_EQ(context.decrypt(c0), 0); 
    // Decrypt(c0) == 1
    ASSERT_EQ(context.decrypt(c1), 1); 
    // Decrypt(c0) == 2
    ASSERT_EQ(context.decrypt(c2), 2); 
    // Decrypt(c0) == 3
    ASSERT_EQ(context.decrypt(c3), 3); 
 

    auto fun_ham = [](int64_t m) -> int64_t {
        switch(m){
            case 0: 
                return 0;
                break;
            case 1: 
                return 1; 
                break;
            case 2: 
                return 1;   
                break; 
            case 3: 
                return 2;  
            default:
                return 0;
        }
    }; 
      
    HomomorphicAccumulator lut_fun_ham = context.setup_function(fun_ham, encoding); 

     
    Ciphertext ct4; 
    ct4 = context.eval(c0, lut_fun_ham); 
    ASSERT_EQ(context.decrypt(ct4), 0); 
  
    ct4 = context.eval(c1, lut_fun_ham); 
    ASSERT_EQ(context.decrypt(ct4), 1);
    
    ct4 = context.eval(c2, lut_fun_ham); 
    ASSERT_EQ(context.decrypt(ct4), 1);
    
    ct4 = context.eval(c3, lut_fun_ham); 
    ASSERT_EQ(context.decrypt(ct4), 2); 

    auto fun_nand = [](int64_t m) -> int64_t {
        switch(m){
            case 0: 
                return 1;
                break;
            case 1: 
                return 1; 
                break;
            case 2: 
                return 1;   
                break; 
            case 3: 
                return 0;  
            default:
                return 2;
        }
    }; 
    HomomorphicAccumulator lut_fun_nand = context.setup_function(fun_nand, encoding); 

    Ciphertext ct0 = context.encrypt(1, encoding);  
    Ciphertext ct1 = context.encrypt(0, encoding);   
    Ciphertext combined = ct0 + (ct1 * 2);   
    Ciphertext ct_nand = context.eval(combined, lut_fun_nand); 
    ASSERT_EQ(context.decrypt(ct_nand), 1); 


    ct0 = context.encrypt(1, encoding);  
    ct1 = context.encrypt(0, encoding);  
    combined = ct0 + (ct1 * 2);  
    ct_nand = context.eval(combined, lut_fun_nand); 
    ASSERT_EQ(context.decrypt(ct_nand), 1); 

    ct0 = context.encrypt(0, encoding);  
    ct1 = context.encrypt(1, encoding);  
    combined = ct0 + (ct1 * 2);  
    ct_nand = context.eval(combined, lut_fun_nand); 
    ASSERT_EQ(context.decrypt(ct_nand), 1); 
 
    ct0 = context.encrypt(1, encoding);  
    ct1 = context.encrypt(1, encoding);  
    combined = ct0 + (ct1 * 2);  
    ct_nand = context.eval(combined, lut_fun_nand); 
    ASSERT_EQ(context.decrypt(ct_nand),  0); 
 
    Ciphertext sanitized = context.sanitize(ct_nand);
    ASSERT_EQ(context.decrypt(sanitized),  0); 
}




void test_for_signed_limied_short_int(FHENamedParams param_set){
     
    FHEContext context;  
    // NOTE: tfhe_11_NTT can still handle a plaintext space equal to 4, but if you test with tfhe_11_B teh test will most likely fail
    context.generate_context(param_set); 
    PlaintextEncoding encoding = context.get_default_plaintext_encoding();
    encoding.set_type(PlaintextEncodingType::signed_limied_short_int);
      
    Ciphertext ct0 = context.encrypt(0, encoding);   
    Ciphertext ct1 = context.encrypt(1, encoding); 
    Ciphertext ct2 = context.encrypt(2, encoding);    
    Ciphertext ct3 = context.encrypt(3, encoding); 
     
    Ciphertext mct1 = context.encrypt(-1, encoding); 
    Ciphertext mct2 = context.encrypt(-2, encoding);    
    Ciphertext mct3 = context.encrypt(-3, encoding); 
  
    Ciphertext ct4 = context.encrypt(4, encoding);  
   
    Ciphertext mct4 = context.encrypt(-4, encoding); 

    ASSERT_EQ(context.decrypt(ct0), 0); 
    ASSERT_EQ(context.decrypt(ct1), 1); 
    ASSERT_EQ(context.decrypt(ct2),  2); 
    ASSERT_EQ(context.decrypt(ct3),  3); 
    
    ASSERT_EQ(context.decrypt(mct1),  -1); 
    ASSERT_EQ(context.decrypt(mct2),  -2); 
    ASSERT_EQ(context.decrypt(mct3),  -3); 
 
    Ciphertext ct_add = ct1 + mct1;
    ASSERT_EQ(context.decrypt(ct_add),  0); 
    ct_add = ct2 + mct2;
    ASSERT_EQ(context.decrypt(ct_add),  0);  
    ct_add = ct3 + mct3;
    ASSERT_EQ(context.decrypt(ct_add),  0); 
    ct_add = ct1 + mct2;
    ASSERT_EQ(context.decrypt(ct_add),  -1); 
    ct_add = ct2 + mct3;
    ASSERT_EQ(context.decrypt(ct_add), -1); 
    ct_add = ct1 + mct3;
    ASSERT_EQ(context.decrypt(ct_add),  -2); 
    ct_add = ct3 + mct1;
    ASSERT_EQ(context.decrypt(ct_add),  2); 
 
    auto fun_identity = [](int64_t m) -> int64_t {
        return m; 
    };    
   
    HomomorphicAccumulator lut_fun_identity = context.setup_function(fun_identity, encoding);  
   
    Ciphertext ct_id = context.eval(mct1, lut_fun_identity);  
    ct_id = context.eval(ct_id, lut_fun_identity); 
    ASSERT_EQ(context.decrypt(ct_id),  -1);
    
    ct_id = context.eval(mct2, lut_fun_identity);  
    ct_id = context.eval(ct_id, lut_fun_identity); 
    ASSERT_EQ(context.decrypt(ct_id), -2);
    
    ct_id = context.eval(mct3, lut_fun_identity);  
    ct_id = context.eval(ct_id, lut_fun_identity); 
    ASSERT_EQ(context.decrypt(ct_id), -3);
    
    ct_id = context.eval(ct0, lut_fun_identity);  
    ct_id = context.eval(ct_id, lut_fun_identity); 
    ASSERT_EQ(context.decrypt(ct_id), 0);
    
    ct_id = context.eval(ct1, lut_fun_identity);  
    ct_id = context.eval(ct_id, lut_fun_identity); 
    ASSERT_EQ(context.decrypt(ct_id), 1);
    
    ct_id = context.eval(ct2, lut_fun_identity);  
    ct_id = context.eval(ct_id, lut_fun_identity); 
    ASSERT_EQ(context.decrypt(ct_id), 2);
    
    ct_id = context.eval(ct3, lut_fun_identity);  
    ct_id = context.eval(ct_id, lut_fun_identity); 
    ASSERT_EQ(context.decrypt(ct_id), 3); 
 
    auto fun_relu = [](int64_t m) -> int64_t {
        if(m >= 0){
            return m; 
        }else{
            return 0;
        }
    };  
  
    Ciphertext ct_relu = context.eval(ct2, fun_relu);   
    ASSERT_EQ(context.decrypt(ct_relu), 2);
    
    ct_relu = context.eval(mct3, fun_relu);  
    ASSERT_EQ(context.decrypt(ct_relu), 0);
    
    ct_relu = context.eval(ct1, fun_relu);  
    ASSERT_EQ(context.decrypt(ct_relu), 1);
    
    ct_relu = context.eval(ct2, fun_relu); 
    ASSERT_EQ(context.decrypt(ct_relu), 2);
    
    ct_relu = context.eval(ct3, fun_relu);  
    ASSERT_EQ(context.decrypt(ct_relu), 3);
    
    ct_relu = context.eval(mct1, fun_relu);  
    ASSERT_EQ(context.decrypt(ct_relu), 0);
    
    ct_relu = context.eval(mct2, fun_relu);  
    ASSERT_EQ(context.decrypt(ct_relu), 0);
    
    ct_relu = context.eval(mct3, fun_relu);  
    ASSERT_EQ(context.decrypt(ct_relu), 0); 
}
 

void basic_Ciphertext_tests(FHENamedParams param_set){
 
    FHEContext context;  
    context.generate_context(param_set);
    PlaintextEncoding encoding = context.get_default_plaintext_encoding(); 
    Ciphertext c1  = context.encrypt(1, encoding);  
    ASSERT_EQ(context.decrypt(c1), 1);
    
    Ciphertext c2  = c1;   
    ASSERT_EQ(context.decrypt(c2), 1); 
    c1 = c2;
    ASSERT_EQ(context.decrypt(c1), 1); 
}



void amortized_full_domain_bootstrap_test(FHENamedParams param_set){

    FHEContext context;  
    context.generate_context(param_set);  
    PlaintextEncoding encoding = context.get_default_plaintext_encoding();
    encoding.set_type(PlaintextEncodingType::full_domain);

    auto id = [](int64_t m) -> int64_t {
        return m;
    }; 
  
    HomomorphicAccumulator lut_identity = context.setup_function(id, encoding); 

    std::vector<HomomorphicAccumulator> luts;
    luts.push_back(lut_identity);
    luts.push_back(lut_identity);
 
    Ciphertext ct1 = context.encrypt_public(1, encoding); 

    std::vector<Ciphertext> out_cts = context.eval(ct1, luts);
 
    ASSERT_EQ(context.decrypt(out_cts[0]), 1);  
    ASSERT_EQ(context.decrypt(out_cts[1]), 1);  
    out_cts = context.eval(ct1, luts);
    ASSERT_EQ(context.decrypt(out_cts[0]), 1); 
    ASSERT_EQ(context.decrypt(out_cts[1]), 1); 

    auto first_bit = [](int64_t m) -> int64_t {
        return m % 2;
    };  
  
    auto second_bit = [](int64_t m) -> int64_t {
        return (m % 4)/2;
    };  

    auto third_bit = [](int64_t m) -> int64_t {
        return (m % 8)/4; 
    };  

    std::vector<HomomorphicAccumulator> bit_decomp_luts;
    bit_decomp_luts.push_back(context.setup_function(first_bit, encoding));
    bit_decomp_luts.push_back(context.setup_function(second_bit, encoding));
    bit_decomp_luts.push_back(context.setup_function(third_bit, encoding));

    Ciphertext ct0 = context.encrypt_public(0, encoding);
    Ciphertext ct2 = context.encrypt_public(2, encoding);
    Ciphertext ct3 = context.encrypt_public(3, encoding);
    Ciphertext ct4 = context.encrypt_public(4, encoding);
    Ciphertext ct5 = context.encrypt_public(5, encoding);
    Ciphertext ct6 = context.encrypt_public(6, encoding);
    Ciphertext ct7 = context.encrypt_public(7, encoding);


    out_cts = context.eval(ct0, bit_decomp_luts);
    print_out << "context.decrypt(out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    print_out << "context.decrypt(out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    print_out << "context.decrypt(out_cts[2]): " << context.decrypt(out_cts[2]) << std::endl;
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 0);  

    out_cts = context.eval(ct1, bit_decomp_luts);
    print_out << "context.decrypt(out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    print_out << "context.decrypt(out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    print_out << "context.decrypt(out_cts[2]): " << context.decrypt(out_cts[2]) << std::endl;
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 0);  

    out_cts = context.eval(ct2, bit_decomp_luts);
    print_out << "context.decrypt(out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    print_out << "context.decrypt(out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    print_out << "context.decrypt(out_cts[2]): " << context.decrypt(out_cts[2]) << std::endl;
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 0);  

    out_cts = context.eval(ct3, bit_decomp_luts);
    print_out << "context.decrypt(out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    print_out << "context.decrypt(out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    print_out << "context.decrypt(out_cts[2]): " << context.decrypt(out_cts[2]) << std::endl;
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 0);  

    out_cts = context.eval(ct4, bit_decomp_luts);
    print_out << "context.decrypt(out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    print_out << "context.decrypt(out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    print_out << "context.decrypt(out_cts[2]): " << context.decrypt(out_cts[2]) << std::endl;
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 1);  
 
    out_cts = context.eval(ct5, bit_decomp_luts);
    print_out << "context.decrypt(out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    print_out << "context.decrypt(out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    print_out << "context.decrypt(out_cts[2]): " << context.decrypt(out_cts[2]) << std::endl;
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 1);  
 
    out_cts = context.eval(ct6, bit_decomp_luts);
    print_out << "context.decrypt(out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    print_out << "context.decrypt(out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    print_out << "context.decrypt(out_cts[2]): " << context.decrypt(out_cts[2]) << std::endl;
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 1);  
 
    out_cts = context.eval(ct7, bit_decomp_luts);
    print_out << "context.decrypt(out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    print_out << "context.decrypt(out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    print_out << "context.decrypt(out_cts[2]): " << context.decrypt(out_cts[2]) << std::endl;
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 1);  
}
 
void amortized_partial_domain_bootstrap_test(FHENamedParams param_set){
    
    FHEContext context;  
    context.generate_context(param_set); 
    PlaintextEncoding encoding = context.get_default_plaintext_encoding();
    encoding.set_type(PlaintextEncodingType::partial_domain);
  
    auto first_bit = [](int64_t m) -> int64_t {
        return m % 2;
    };  
  
    auto second_bit = [](int64_t m) -> int64_t {
        return (m % 4)/2;
    };  

    auto third_bit = [](int64_t m) -> int64_t {
        return (m % 8)/4; 
    };  

    std::vector<HomomorphicAccumulator> bit_decomp_luts;
    bit_decomp_luts.push_back(context.setup_function(first_bit, encoding));
    bit_decomp_luts.push_back(context.setup_function(second_bit, encoding));
    bit_decomp_luts.push_back(context.setup_function(third_bit, encoding));

    Ciphertext ct0 = context.encrypt_public(0, encoding); 
    Ciphertext ct1 = context.encrypt_public(1, encoding); 
    Ciphertext ct2 = context.encrypt_public(2, encoding);
    Ciphertext ct3 = context.encrypt_public(3, encoding);
    Ciphertext ct4 = context.encrypt_public(4, encoding);
    Ciphertext ct5 = context.encrypt_public(5, encoding);
    Ciphertext ct6 = context.encrypt_public(6, encoding);
    Ciphertext ct7 = context.encrypt_public(7, encoding);


    std::vector<Ciphertext> out_cts = context.eval(ct0, bit_decomp_luts); 
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 0);  

    out_cts = context.eval(ct1, bit_decomp_luts);
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 0);  

    out_cts = context.eval(ct2, bit_decomp_luts);  
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 0);  

    out_cts = context.eval(ct3, bit_decomp_luts);
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 0);  

    out_cts = context.eval(ct4, bit_decomp_luts);
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 1);  
 
    out_cts = context.eval(ct5, bit_decomp_luts);
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 1);  
 
    out_cts = context.eval(ct6, bit_decomp_luts);
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 1); 
    
    out_cts = context.eval(ct7, bit_decomp_luts);
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 1);  
}

 

void amortized_12_partial_domain_bootstrap_test(FHENamedParams param_set){ 

    FHEContext context;  
    context.generate_context(param_set); 
    PlaintextEncoding encoding = context.get_default_plaintext_encoding();
  
    auto first_bit = [](int64_t m) -> int64_t {
        return m % 2;
    };  
  
    auto second_bit = [](int64_t m) -> int64_t {
        return (m % 4)/2;
    };  

    auto third_bit = [](int64_t m) -> int64_t {
        return (m % 8)/4; 
    };  

    auto fourth_bit = [](int64_t m) -> int64_t {
        return (m % 16)/8; 
    };  

    std::vector<HomomorphicAccumulator> bit_decomp_luts;
    bit_decomp_luts.push_back(context.setup_function(first_bit));
    bit_decomp_luts.push_back(context.setup_function(second_bit));
    bit_decomp_luts.push_back(context.setup_function(third_bit));
    bit_decomp_luts.push_back(context.setup_function(fourth_bit));

    Ciphertext ct0 = context.encrypt_public(0, encoding); 
    Ciphertext ct1 = context.encrypt_public(1, encoding); 
    Ciphertext ct2 = context.encrypt_public(2,encoding);
    Ciphertext ct3 = context.encrypt_public(3, encoding);
    Ciphertext ct4 = context.encrypt_public(4, encoding);
    Ciphertext ct5 = context.encrypt_public(5, encoding);
    Ciphertext ct6 = context.encrypt_public(6, encoding);
    Ciphertext ct7 = context.encrypt_public(7, encoding);
    Ciphertext ct8 = context.encrypt_public(8, encoding);
    Ciphertext ct9 = context.encrypt_public(9, encoding);
    Ciphertext ct10 = context.encrypt_public(10, encoding);
    Ciphertext ct11 = context.encrypt_public(11, encoding);
    Ciphertext ct12 = context.encrypt_public(12, encoding);
    Ciphertext ct13 = context.encrypt_public(13, encoding);
    Ciphertext ct14 = context.encrypt_public(14, encoding);
    Ciphertext ct15 = context.encrypt_public(15, encoding);


    int64_t elapsed = 0; 
    std::chrono::_V2::system_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::vector<Ciphertext> out_cts = context.eval(ct0, bit_decomp_luts);
    std::chrono::_V2::system_clock::time_point stop = std::chrono::high_resolution_clock::now();
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
  
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[3]) == 0);  
  
    out_cts = context.eval(ct1, bit_decomp_luts);  
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[3]) == 0); 
    
    out_cts = context.eval(ct2, bit_decomp_luts);   
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[3]) == 0); 

    out_cts = context.eval(ct3, bit_decomp_luts);
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[3]) == 0); 

    out_cts = context.eval(ct4, bit_decomp_luts);
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[3]) == 0); 
    
    out_cts = context.eval(ct5, bit_decomp_luts);
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[3]) == 0); 
    
    out_cts = context.eval(ct6, bit_decomp_luts);
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[3]) == 0);  

    out_cts = context.eval(ct7, bit_decomp_luts);
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[3]) == 0); 
    
    out_cts = context.eval(ct8, bit_decomp_luts);
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[3]) == 1); 
    
    out_cts = context.eval(ct9, bit_decomp_luts);
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[3]) == 1); 
    
    out_cts = context.eval(ct10, bit_decomp_luts);
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[3]) == 1); 
    
    out_cts = context.eval(ct11, bit_decomp_luts);
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[3]) == 1); 
    
    out_cts = context.eval(ct12, bit_decomp_luts);
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[3]) == 1); 
    
    out_cts = context.eval(ct13, bit_decomp_luts);
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[3]) == 1); 
    
    out_cts = context.eval(ct14, bit_decomp_luts);
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 0); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[3]) == 1); 
    
    out_cts = context.eval(ct15, bit_decomp_luts);
    ASSERT_TRUE(context.decrypt(out_cts[0]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[1]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[2]) == 1); 
    ASSERT_TRUE(context.decrypt(out_cts[3]) == 1);  
}




void serialization_test(FHENamedParams param_set){ 

    FHEContext first_context;  
    try{
        
        first_context.generate_context(param_set); 
        PlaintextEncoding encoding = first_context.get_default_plaintext_encoding(); 
        first_context.save_secret_key("z_sk.cereal");  
        first_context.save_public_key("z_pk.cereal");
    
        FHEContext context;   
        context.load_secret_key("z_sk.cereal");  
        context.load_public_key("z_pk.cereal"); 
        std::remove("z_sk.cereal"); 
        std::remove("z_pk.cereal"); 
 
        Ciphertext ct0 = context.encrypt_public(1, encoding);   
        ASSERT_TRUE(context.decrypt(ct0) == 1);
         
        auto id_0 = [](int64_t m, int64_t t) -> int64_t {
            return m % t;
        }; 
        std::function<int64_t(int64_t)> id = std::bind(id_0, std::placeholders::_1, context.get_default_plaintext_space());
        ct0 = context.eval(ct0, id);  
     
        context.save_Ciphertext("z_ct.cereal", ct0);   
        Ciphertext ct_out = context.load_Ciphertext("z_ct.cereal"); 

        ASSERT_TRUE(context.decrypt(ct_out) == 1); 
         
        std::ofstream os("z_rlwe_ct.cereal", std::ios::binary);
        os << ct_out; 
        os.close();
 
        Ciphertext ct_from_stream = context.load_Ciphertext("z_rlwe_ct.cereal");
        ASSERT_TRUE(context.decrypt(ct_from_stream) == 1);
 
        std::remove("z_ct.cereal"); 
        std::remove("z_rlwe_ct.cereal");  
        
    }catch (std::logic_error& e) {
        std::cerr << "Serialization_test Error: " << e.what() << std::endl;
    }
}

/// TODO: Include this into the test suite with params:
    //test_full_change_plaintext_space(FHENamedParams::tfhe_11_NTT);

    //test_full_change_plaintext_space(FHENamedParams::tfhe_11_NTT_amortized);

    //test_full_change_plaintext_space(FHENamedParams::tfhe_11_KS);

    //test_full_change_plaintext_space(FHENamedParams::tfhe_11_KS_amortized); 
void test_full_change_plaintext_space(FHENamedParams param_set){ 
    FHEContext context;  
    context.generate_context(param_set);  
     
    int modulus_1 = 7;
    int modulus_2 = 13; 
    PlaintextEncoding encoding_1 = context.get_default_plaintext_encoding();
    encoding_1.set_type(PlaintextEncodingType::full_domain);
    encoding_1.set_plaintext_space(modulus_1);
    PlaintextEncoding encoding_2 = encoding_1;
    encoding_2.set_plaintext_space(modulus_2);
    
    Ciphertext ct_in  = context.encrypt(2, encoding_1); 
    
    ASSERT_TRUE(context.decrypt(ct_in) == 2); 
    ASSERT_TRUE(ct_in.encoding.get_plaintext_space() == modulus_1); 
    ASSERT_TRUE(ct_in.encoding.get_type() == PlaintextEncodingType::full_domain); 

    auto id = [](int64_t m) -> int64_t {
        return m;
    }; 
 
    ct_in = context.eval(ct_in, id);  

    ASSERT_TRUE(context.decrypt(ct_in) == 2); 
    ASSERT_TRUE(ct_in.encoding.get_plaintext_space() == modulus_1); 
    ASSERT_TRUE(ct_in.encoding.get_type() == PlaintextEncodingType::full_domain); 
  
    std::function<int64_t(int64_t)> fun_add = [](int64_t m) -> int64_t {
        return (m+8)%11;
    }; 
  
    ASSERT_TRUE(encoding_1.get_plaintext_space() == modulus_1); 
    ASSERT_TRUE(encoding_1.get_type() == PlaintextEncodingType::full_domain);  
    ASSERT_TRUE(encoding_2.get_plaintext_space() == modulus_2); 
    ASSERT_TRUE(encoding_2.get_type() == PlaintextEncodingType::full_domain);  

    HomomorphicAccumulator lut_fun_add = context.setup_function(fun_add, encoding_1, encoding_2); 
    Ciphertext ct_out = context.eval(ct_in, lut_fun_add);
  
    ASSERT_TRUE(ct_out.encoding.get_plaintext_space()  == modulus_2); 
    ASSERT_TRUE(ct_out.encoding.get_type() == PlaintextEncodingType::full_domain);  
    ASSERT_TRUE(context.decrypt(ct_out) == 10); 
}


/// TODO: Include this into the test suite with params: 
    //test_full_change_plaintext_space_amortized(FHENamedParams::tfhe_11_NTT_amortized);
    //test_full_change_plaintext_space_amortized(FHENamedParams::tfhe_11_KS_amortized);
void test_full_change_plaintext_space_amortized(FHENamedParams param_set){ 
    FHEContext context;  
    context.generate_context(param_set); 
    
    int modulus_1 = 7;
    int modulus_2 = 13; 
    PlaintextEncoding encoding_1 = context.get_default_plaintext_encoding();
    encoding_1.set_type(PlaintextEncodingType::full_domain);
    encoding_1.set_plaintext_space(modulus_1);
    PlaintextEncoding encoding_2 = encoding_1;
    encoding_2.set_plaintext_space(modulus_2);
    
    Ciphertext ct_in  = context.encrypt(2, encoding_1); 
    
    ASSERT_TRUE(context.decrypt(ct_in) == 2); 
    ASSERT_TRUE(ct_in.encoding.get_plaintext_space() == modulus_1); 
    ASSERT_TRUE(ct_in.encoding.get_type() == PlaintextEncodingType::full_domain);
    
    auto id = [](int64_t m) -> int64_t {
        return m;
    }; 

    std::vector<HomomorphicAccumulator> id_luts;
    id_luts.push_back(context.setup_function(id, ct_in.encoding, ct_in.encoding));
    id_luts.push_back(context.setup_function(id, ct_in.encoding, ct_in.encoding));
    
    /// TODO: Actually I need to check perhaps whether LUT where build with the same encoding as the input ciphertext for eval.
    /// If not, then need to throw an exeption, with instruction what to do, because its not always possible to recode a rotation poly to a different encoding.
    /// Well general problem now, because tthe HomomorphicAccumulator doesn't have a copy of a encoding...
    /// What options are there:
    /// 1) I just give the encoding copies, to the HomomorphicAccumulator. Then if input or output encodings don't work, then I throw an exception.
    /// 2) I only have setup functions that take input and output encoding explicitely (make the library harder to use if we have a non-trivial case)
    /// OK. I guess I will go with option 1. What bothers mee a bit, is the we cannot reuse LUTs for different encodings.
    /// But if I want flexibility then I can just pass a vector of functions, and generate the LUTs on the fly.
    std::vector<Ciphertext> cts = context.eval(ct_in, id_luts);  

    for(Ciphertext ct: cts){ 
        ASSERT_TRUE(ct.encoding.get_type() == PlaintextEncodingType::full_domain); 
        ASSERT_TRUE(ct.encoding.get_plaintext_space() == modulus_1); 
        ASSERT_TRUE(context.decrypt(ct) == 2); 
    } 
    
    ASSERT_TRUE(encoding_1.get_plaintext_space() == modulus_1); 
    ASSERT_TRUE(encoding_1.get_type() == PlaintextEncodingType::full_domain);  
    ASSERT_TRUE(encoding_2.get_plaintext_space() == modulus_2); 
    ASSERT_TRUE(encoding_2.get_type() == PlaintextEncodingType::full_domain);  
  
    std::function<int64_t(int64_t)> fun_add = [](int64_t m) -> int64_t {
        return (m+8)%11;
    }; 

    std::vector<HomomorphicAccumulator> fun_luts;
    fun_luts.push_back(context.setup_function(fun_add, encoding_1, encoding_2));
    fun_luts.push_back(context.setup_function(fun_add, encoding_1, encoding_2));
 
    std::vector<Ciphertext> ct_outs = context.eval(ct_in, fun_luts);
  
    for(Ciphertext ct_out: ct_outs){
        ASSERT_TRUE(ct_out.encoding.get_plaintext_space()  == modulus_2); 
        ASSERT_TRUE(ct_out.encoding.get_type() == PlaintextEncodingType::full_domain);  
        ASSERT_TRUE(context.decrypt(ct_out) == 10); 
    } 
}
 
/// TODO: Include this into the test suite
   //test_full_fdfb(FHENamedParams::tfhe_11_KS, true);

   //test_full_fdfb(FHENamedParams::tfhe_11_KS_amortized, true);

   //test_full_fdfb(FHENamedParams::tfhe_11_NTT);
void test_full_fdfb(FHENamedParams param_set, bool amortized = false){
    
    FHEContext context;  
    context.generate_context(param_set);  
    int32_t modulus = 15;   
    PlaintextEncoding encoding = context.get_default_plaintext_encoding();
    encoding.set_type(PlaintextEncodingType::full_domain);
    encoding.set_plaintext_space(modulus);
  
    auto times_in_two_and_square = [](int32_t m, int32_t modulus) -> int32_t{  
        return m;
    };  
    std::function<int64_t(int64_t)> function = std::bind(times_in_two_and_square, std::placeholders::_1, modulus);

    HomomorphicAccumulator acc = context.setup_function(function, encoding);
    std::vector<HomomorphicAccumulator> accs;
    accs.push_back(acc);
  
    int32_t tests{10};
    bool is_correct{true}; 
    std::cerr << "Testing input: " << 0 ;
    for(int32_t input{0}; input < modulus; ++input){ 
        std::cerr << "\rTesting input: " << input ;
        for(int32_t i{0}; i < tests; ++i){
            Ciphertext ct_in  = context.encrypt(input, encoding);   
            int32_t dec{-1};
            
            if(amortized){
                std::vector<Ciphertext> ct_outs = context.eval(ct_in, accs); 
                dec = context.decrypt(ct_outs[0]);
            }else{ 
                Ciphertext ct_out = context.eval(ct_in, acc); 
                dec = context.decrypt(ct_out);
            }
            if(dec != times_in_two_and_square(input, modulus)){ 
                print_out << "Test Full Domain Function Bootstrapping: Fail for input: " << input << " at i = " << i << std::endl; 
                print_out << "Should be: " << times_in_two_and_square(input, modulus) << std::endl;
                print_out << "Is: " << dec << std::endl;
                FAIL();
            }  
        }
    } 
}

// ----- Fixture for FullDomainEncoding -----
class FHEContextFullDomainTest : public ::testing::TestWithParam<FHENamedParams> {};

TEST_P(FHEContextFullDomainTest, FullDomainEncoding) {
    FHENamedParams param_set = GetParam();
    test_for_default_full_domain_encoding(param_set);
}

INSTANTIATE_TEST_SUITE_P(
    FullDomainEncoding,
    FHEContextFullDomainTest,
    ::testing::Values(
        FHENamedParams::tfhe_11_NTT,
        FHENamedParams::tfhe_11_NTT_amortized,
        FHENamedParams::ntrunium_12_NTT,
        FHENamedParams::tfhe_11_KS
    )
);


// ----- Fixture for PartialDomainEncoding -----
class FHEContextPartialDomainTest : public ::testing::TestWithParam<FHENamedParams> {};

TEST_P(FHEContextPartialDomainTest, PartialDomainEncoding) {
    FHENamedParams param_set = GetParam();
    test_for_partial_domain_encoding(param_set);
}

INSTANTIATE_TEST_SUITE_P(
    PartialDomainEncoding,
    FHEContextPartialDomainTest,
    ::testing::Values(
        FHENamedParams::tfhe_11_NTT,
        FHENamedParams::tfhe_11_NTT_flood
    )
);


// ----- Signed Limited Encoding -----
class FHEContextSignedLimitedTest : public ::testing::TestWithParam<FHENamedParams> {};

TEST_P(FHEContextSignedLimitedTest, SignedLimitedEncoding) {
    FHENamedParams param_set = GetParam();
    test_for_signed_limied_short_int(param_set);
}

INSTANTIATE_TEST_SUITE_P(
    SignedLimitedEncoding,
    FHEContextSignedLimitedTest,
    ::testing::Values(
        FHENamedParams::tfhe_11_NTT
    )
);


// ----- Amortized Partial Domain Encoding -----
class FHEContextAmortizedPartialDomainTest : public ::testing::TestWithParam<FHENamedParams> {};

TEST_P(FHEContextAmortizedPartialDomainTest, AmortizedPartialDomainEncoding) {
    FHENamedParams param_set = GetParam();
    amortized_partial_domain_bootstrap_test(param_set);
}

INSTANTIATE_TEST_SUITE_P(
    AmortizedPartialDomainEncoding,
    FHEContextAmortizedPartialDomainTest,
    ::testing::Values(
        FHENamedParams::tfhe_11_NTT_amortized
    )
);


// ----- Amortized Full Domain Encoding -----
class FHEContextAmortizedFullDomainTest : public ::testing::TestWithParam<FHENamedParams> {};

TEST_P(FHEContextAmortizedFullDomainTest, AmortizedFullDomainEncoding) {
    FHENamedParams param_set = GetParam();
    amortized_full_domain_bootstrap_test(param_set);
}

INSTANTIATE_TEST_SUITE_P(
    AmortizedFullDomainEncoding,
    FHEContextAmortizedFullDomainTest,
    ::testing::Values(
        FHENamedParams::tfhe_11_KS_amortized
    )
);


// ----- Amortized Full Domain Encoding 12 -----
class FHEContextAmortizedFullDomain12Test : public ::testing::TestWithParam<FHENamedParams> {};

TEST_P(FHEContextAmortizedFullDomain12Test, AmortizedFullDomainEncoding_12) {
    FHENamedParams param_set = GetParam();
    amortized_12_partial_domain_bootstrap_test(param_set);
}

INSTANTIATE_TEST_SUITE_P(
    AmortizedFullDomainEncoding_12,
    FHEContextAmortizedFullDomain12Test,
    ::testing::Values(
        FHENamedParams::tfhe_12_NTT_amortized
    )
);


// ----- Serialization -----
class FHEContextSerializationTest : public ::testing::TestWithParam<FHENamedParams> {};

TEST_P(FHEContextSerializationTest, Serialization) {
    FHENamedParams param_set = GetParam();
    serialization_test(param_set);
}

INSTANTIATE_TEST_SUITE_P(
    SerializationTest,
    FHEContextSerializationTest,
    ::testing::Values(
        FHENamedParams::tfhe_11_NTT
    )
);
 