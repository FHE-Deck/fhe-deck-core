#include <gtest/gtest.h>

#include <iostream>
#include <chrono>
#include "fhe_deck.h" 
#include "verbose_stream.hpp"
 
using namespace FHEDeck;

/// @brief  This flag is defined in test_main.cpp
extern bool verbose;
 
TEST(AmortizedBitOperations, StressTest){

    FHEContext ctx;  
    ctx.generate_context(FHENamedParams::tfhe_11_NTT_amortized);    
    
    PlaintextEncoding encoding = ctx.get_default_plaintext_encoding(); 

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
    bit_decomp_luts.push_back(ctx.setup_function(first_bit, encoding));
    bit_decomp_luts.push_back(ctx.setup_function(second_bit, encoding));
    bit_decomp_luts.push_back(ctx.setup_function(third_bit, encoding));

    std::vector<int64_t> comp = {1, 2, 4}; 

    Ciphertext ct, ct2;
    Ciphertext temp, temp_0, temp_1, temp_2;
    std::vector<Ciphertext> out_cts;
    int32_t test_num = 10;
    int32_t repetition_num = 5;
    int32_t msg;
    int64_t dec; 
    for(int32_t i = 0; i < test_num; ++i){
        msg = i % 8;
        ct = ctx.encrypt_public(msg, encoding);
        for(int32_t j = 0; j < repetition_num; ++j){   
            out_cts = ctx.eval(ct, bit_decomp_luts);       
            ct2 = ctx.eval_affine_function(out_cts, comp, 0);  
            
            dec = ctx.decrypt(ct2);
            if(dec != msg){ 
                print_out << "Fail after " << i  << ", " << j << " tests!" << std::endl;
                print_out << "Expected: " << msg << std::endl;
                print_out << "Decrypted: " << dec << std::endl;  
                print_out << "Separate Bits: " << ctx.decrypt(out_cts[0]) << " " << ctx.decrypt(out_cts[1]) << " " << ctx.decrypt(out_cts[2]) << std::endl;
                temp_0 = out_cts[0] * comp[0];
                print_out << "temp_0: " << ctx.decrypt(temp_0) << std::endl;
                temp_1 = out_cts[1] * comp[1];
                print_out << "temp_1: " << ctx.decrypt(temp_1) << std::endl;
                temp_2 = out_cts[2] * comp[2];
                print_out << "temp_2: " << ctx.decrypt(temp_2) << std::endl; 
                temp = temp_0 + temp_1 + temp_2; 
                print_out << "temp: " << ctx.decrypt(temp) << std::endl; 
    
                temp_0 = ctx.eval(ct, bit_decomp_luts[0]);
                print_out << "eval_lut with bit_decomp_luts[0]: " << ctx.decrypt(temp_0) << std::endl; 
                temp_1 = ctx.eval(ct, bit_decomp_luts[1]);
                print_out << "eval_lut with bit_decomp_luts[1]: " << ctx.decrypt(temp_1) << std::endl; 
                temp_2 = ctx.eval(ct, bit_decomp_luts[2]);
                print_out << "eval_lut with bit_decomp_luts[2]: " << ctx.decrypt(temp_2) << std::endl; 
                temp = temp_0 + temp_1 + temp_2; 
                print_out << "temp: " << ctx.decrypt(temp) << std::endl;  
                FAIL();
            } 
            ct = ct2;
        }
    } 
}
