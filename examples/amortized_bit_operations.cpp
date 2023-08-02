#include <iostream>
#include "fhe_context.h"

#include <cassert>
#define assertm(exp, msg) assert(((void)msg, exp))


using namespace fhe_deck;

int main(){

    FHEContext ctx; 
    std::cout << "Generate Keys..." << std::endl;
    ctx.generate_context(tfhe_11_NTT_amortized);  
    
    auto first_bit = [](long m) -> long {
        return m % 2;
    };  
  
    auto second_bit = [](long m) -> long {
        return (m % 4)/2;
    };  

    auto third_bit = [](long m) -> long {
        return (m % 8)/4; 
    };  

    std::vector<RotationPoly> bit_decomp_luts;
    bit_decomp_luts.push_back(ctx.genrate_lut(first_bit));
    bit_decomp_luts.push_back(ctx.genrate_lut(second_bit));
    bit_decomp_luts.push_back(ctx.genrate_lut(third_bit));

    std::vector<long> comp = {1, 2, 4}; 

    Ciphertext ct, ct2;
    Ciphertext temp, temp_0, temp_1, temp_2;
    std::vector<Ciphertext> out_cts;
    int test_num = 10;
    int repetition_num = 5;
    int msg;
    long dec;
    for(int i = 0; i < test_num; ++i){
        msg = i % 8;
        ct = ctx.encrypt_public(msg);
        for(int j = 0; j < repetition_num; ++j){  
            out_cts = ctx.eval_lut_amortized(&ct, bit_decomp_luts);   
            ct2 = ctx.eval_affine_function(out_cts, comp, 0);  
            dec = ctx.decrypt(&ct2);
            if(dec != msg){
                std::cout << "Fail after " << i  << ", " << j << " tests!" << std::endl;
                std::cout << "Expected: " << msg << std::endl;
                std::cout << "Decrypted: " << dec << std::endl;  
                std::cout << "Separate Bits: " << ctx.decrypt(&out_cts[0]) << " " << ctx.decrypt(&out_cts[1]) << " " << ctx.decrypt(&out_cts[2]) << std::endl;
                temp_0 = out_cts[0] * comp[0];
                std::cout << "temp_0: " << ctx.decrypt(&temp_0) << std::endl;
                temp_1 = out_cts[1] * comp[1];
                std::cout << "temp_1: " << ctx.decrypt(&temp_1) << std::endl;
                temp_2 = out_cts[2] * comp[2];
                std::cout << "temp_2: " << ctx.decrypt(&temp_2) << std::endl; 
                temp = temp_0 + temp_1 + temp_2; 
                std::cout << "temp: " << ctx.decrypt(&temp) << std::endl; 
 
                temp_0 = ctx.eval_lut(&ct, bit_decomp_luts[0]);
                std::cout << "eval_lut with bit_decomp_luts[0]: " << ctx.decrypt(&temp_0) << std::endl; 
                temp_1 = ctx.eval_lut(&ct, bit_decomp_luts[1]);
                std::cout << "eval_lut with bit_decomp_luts[1]: " << ctx.decrypt(&temp_1) << std::endl; 
                temp_2 = ctx.eval_lut(&ct, bit_decomp_luts[2]);
                std::cout << "eval_lut with bit_decomp_luts[2]: " << ctx.decrypt(&temp_2) << std::endl; 
                temp = temp_0 + temp_1 + temp_2; 
                std::cout << "temp: " << ctx.decrypt(&temp) << std::endl; 
                return 0;
            } 
            ct = ct2;
        }
    }
    std::cout << "Stress test OK" << std::endl;
 
}
