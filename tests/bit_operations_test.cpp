#include <gtest/gtest.h>
#include <cassert> 

#include "fhe_deck.h"


/// @brief  This flag is defined in test_main.cpp
extern bool verbose;

using namespace FHEDeck;

TEST(BitOperations, StressTest){

    FHEContext context;  
    context.generate_context(FHENamedParams::tfhe_11_NTT); 
    PlaintextEncoding encoding = context.get_default_plaintext_encoding();
    encoding.set_type(PlaintextEncodingType::partial_domain);
    encoding.set_plaintext_space(4);

 
    Ciphertext c0  = context.encrypt(0, encoding);  
    Ciphertext c1  = context.encrypt(1, encoding);    
    Ciphertext c2  = context.encrypt(2, encoding);  
    Ciphertext c3  = context.encrypt(3, encoding);  
   
    ASSERT_EQ(context.decrypt(c0), 0); 
    ASSERT_EQ(context.decrypt(c1), 1); 
    ASSERT_EQ(context.decrypt(c2), 2); 
    ASSERT_EQ(context.decrypt(c3), 3); 
 

    auto fun_ham = [](long m) -> long {
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
 
    auto fun_nand = [](long m) -> long {
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
    // ct_nand(0, 0) == 1
    ASSERT_EQ(context.decrypt(ct_nand), 1);  
 
    ct0 = ct_nand;  
    ct1 = context.encrypt(0, encoding);  
    combined = ct0 + (ct1 * 2);  
    ct_nand = context.eval(combined, lut_fun_nand); 
    // ct_nand(0, 1) == 1
    ASSERT_EQ(context.decrypt(ct_nand), 1); 

    ct0 = context.encrypt(0, encoding);  
    ct1 = ct_nand;  
    combined = ct0 + (ct1 * 2);  
    ct_nand = context.eval(combined, lut_fun_nand); 
    // ct_nand(1, 0) == 1
    ASSERT_EQ(context.decrypt(ct_nand), 1); 
 
    ct0 = ct_nand;  
    ct1 = ct_nand;  
    combined = ct0 + (ct1 * 2);  
    ct_nand = context.eval(combined, lut_fun_nand); 
    // , "ct_nand(1, 1) == 0"
    ASSERT_EQ(context.decrypt(ct_nand), 0); 
 
    for(int32_t i = 0; i < 20; ++i){ 
        // 0 Nand 0
        ct0 = ct_nand; 
        ct1 = ct_nand; 
        combined = ct0 + (ct1 * 2);      
        ct_nand = context.eval(combined, lut_fun_nand);  
        // ct_nand(0, 0) == 1
        ASSERT_EQ(context.decrypt(ct_nand), 1);  
    
        ct0 = ct_nand;  
        ct1 = context.encrypt(0, encoding);  
        combined = ct0 + (ct1 * 2);   
        ct_nand = context.eval(combined, lut_fun_nand);  
        // ct_nand(0, 1) == 1
        ASSERT_EQ(context.decrypt(ct_nand), 1); 

        ct0 = context.encrypt(0, encoding);  
        ct1 = ct_nand;  
        combined = ct0 + (ct1 * 2);   
        ct_nand = context.eval(combined, lut_fun_nand); 
        // ct_nand(1, 0) == 1 
        ASSERT_EQ(context.decrypt(ct_nand), 1); 
    
        ct0 = ct_nand;  
        ct1 = ct_nand;  
        combined = ct0 + (ct1 * 2);    
        ct_nand = context.eval(combined, lut_fun_nand);  
        // ct_nand(1, 1) == 0
        ASSERT_EQ(context.decrypt(ct_nand), 0);  
    }  
}
