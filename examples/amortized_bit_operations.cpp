#include <iostream>
#include <chrono>
#include "fhe_deck.h"
#include <cassert>
#define assertm(exp, msg) assert(((void)msg, exp))


using namespace fhe_deck;

int32_t main(){

    FHEContext ctx; 
    std::cerr << "Generate Keys..." ;
    ctx.generate_context(FHENamedParams::tfhe_11_NTT_amortized);  
    std::cerr << "\rGenerate Keys: OK" << std::endl;
    int64_t elapsed = 0;   
    int32_t num_of_evals = 0;
    std::chrono::_V2::system_clock::time_point start;
    std::chrono::_V2::system_clock::time_point stop;
    
    std::cerr << "Setup functions...";

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
    bit_decomp_luts.push_back(ctx.setup_function(first_bit));
    bit_decomp_luts.push_back(ctx.setup_function(second_bit));
    bit_decomp_luts.push_back(ctx.setup_function(third_bit));

    std::vector<int64_t> comp = {1, 2, 4}; 

    Ciphertext ct, ct2;
    Ciphertext temp, temp_0, temp_1, temp_2;
    std::vector<Ciphertext> out_cts;
    int32_t test_num = 10;
    int32_t repetition_num = 5;
    int32_t msg;
    int64_t dec;
    std::cerr << "\rSetup functions: OK" << std::endl;
    std::cerr << "Testing..." ;
    for(int32_t i = 0; i < test_num; ++i){
        msg = i % 8;
        ct = ctx.encrypt_public(msg);
        for(int32_t j = 0; j < repetition_num; ++j){  
            start = std::chrono::high_resolution_clock::now(); 
            out_cts = ctx.eval(ct, bit_decomp_luts);   
            stop = std::chrono::high_resolution_clock::now(); 
            elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
            num_of_evals++;
            ct2 = ctx.eval_affine_function(out_cts, comp, 0);  
            
            dec = ctx.decrypt(ct2);
            if(dec != msg){
                std::cout << "Fail after " << i  << ", " << j << " tests!" << std::endl;
                std::cout << "Expected: " << msg << std::endl;
                std::cout << "Decrypted: " << dec << std::endl;  
                std::cout << "Separate Bits: " << ctx.decrypt(out_cts[0]) << " " << ctx.decrypt(out_cts[1]) << " " << ctx.decrypt(out_cts[2]) << std::endl;
                temp_0 = out_cts[0] * comp[0];
                std::cout << "temp_0: " << ctx.decrypt(temp_0) << std::endl;
                temp_1 = out_cts[1] * comp[1];
                std::cout << "temp_1: " << ctx.decrypt(temp_1) << std::endl;
                temp_2 = out_cts[2] * comp[2];
                std::cout << "temp_2: " << ctx.decrypt(temp_2) << std::endl; 
                temp = temp_0 + temp_1 + temp_2; 
                std::cout << "temp: " << ctx.decrypt(temp) << std::endl; 
 
                temp_0 = ctx.eval(ct, bit_decomp_luts[0]);
                std::cout << "eval_lut with bit_decomp_luts[0]: " << ctx.decrypt(temp_0) << std::endl; 
                temp_1 = ctx.eval(ct, bit_decomp_luts[1]);
                std::cout << "eval_lut with bit_decomp_luts[1]: " << ctx.decrypt(temp_1) << std::endl; 
                temp_2 = ctx.eval(ct, bit_decomp_luts[2]);
                std::cout << "eval_lut with bit_decomp_luts[2]: " << ctx.decrypt(temp_2) << std::endl; 
                temp = temp_0 + temp_1 + temp_2; 
                std::cout << "temp: " << ctx.decrypt(temp) << std::endl; 
                return 0;
            } 
            ct = ct2;
        }
    }
    std::cerr << "\rTesting: OK" << std::endl; 
    
    std::cout << "Time elapsed:  " << elapsed << " ms, " << (double)elapsed/1000.0 << " s" << std::endl; 
    std::cout << "Time per eval:  " << (double)elapsed/num_of_evals << " ms, " << ((double)elapsed/num_of_evals)/1000.0 << " s" << std::endl; 
}
