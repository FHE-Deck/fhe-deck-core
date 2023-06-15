#include "fhe_context.h"
 
#include <cassert>
#define assertm(exp, msg) assert(((void)msg, exp))

using namespace fhe_deck;

int main(){
    
    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl;
    context.generate_context(rlwe_hom_acc_scheme_C_11_NTT);
    context.set_default_message_encoding_type(partial_domain);
    context.set_default_plaintext_space(4);

 
    Ciphertext c0  = context.encrypt(0);  
    Ciphertext c1  = context.encrypt(1);    
    Ciphertext c2  = context.encrypt(2);  
    Ciphertext c3  = context.encrypt(3);  
  
    std::cout << "context.decrypt(&c0)" <<  context.decrypt(&c0) << std::endl;
    assertm(context.decrypt(&c0) == 0, "Decrypt(c0) == 0");
    std::cout << "Decrypt(c0) == 0: OK" << std::endl; 

    std::cout << "context.decrypt(&c1)" <<  context.decrypt(&c1) << std::endl;
    assertm(context.decrypt(&c1) == 1, "Decrypt(c1) == 1");
    std::cout << "Decrypt(c1) == 1: OK" << std::endl; 

    std::cout << "context.decrypt(&c2)" <<  context.decrypt(&c2) << std::endl;
    assertm(context.decrypt(&c2) == 2, "Decrypt(c2) == 2");
    std::cout << "Decrypt(c2) == 2: OK" << std::endl; 

    std::cout << "context.decrypt(&c3)" <<  context.decrypt(&c3) << std::endl;
    assertm(context.decrypt(&c3) == 3, "Decrypt(c3) == 3");
    std::cout << "Decrypt(c3) == 3: OK" << std::endl; 
 

    auto fun_ham = [](long m, long t) -> long {
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

    RotationPoly lut_fun_ham = context.genrate_lut(fun_ham);  
    std::cout << "Computing Hammming Weights..." << std::endl;
    Ciphertext ct4;
    ct4 = context.eval_lut(&c0, lut_fun_ham); 
    assertm(context.decrypt(&ct4) == 0, "context.eval_lut(c0, lut_fun_ham) == 0");
    std::cout << "context.eval_lut(c0, lut_fun_ham) == 0: OK" << std::endl;  

    ct4 = context.eval_lut(&c1, lut_fun_ham); 
    assertm(context.decrypt(&ct4) == 1, "context.eval_lut(c1, lut_fun_ham) == 1");
    std::cout << "context.eval_lut(c1, lut_fun_ham) == 1: OK" << std::endl;  

    ct4 = context.eval_lut(&c2, lut_fun_ham); 
    assertm(context.decrypt(&ct4) == 1, "context.eval_lut(c2, lut_fun_ham) == 1");
    std::cout << "context.eval_lut(c2, lut_fun_ham) == 1: OK" << std::endl;  

    ct4 = context.eval_lut(&c3, lut_fun_ham); 
    assertm(context.decrypt(&ct4) == 2, "context.eval_lut(c3, lut_fun_ham) == 2");
    std::cout << "context.eval_lut(c3, lut_fun_ham) == 2: OK" << std::endl;  
 
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
    RotationPoly lut_fun_nand = context.genrate_lut(fun_nand); 
  
    Ciphertext ct0 = context.encrypt(1);  
    Ciphertext ct1 = context.encrypt(0);   

    Ciphertext combined = ct0 + (ct1 * 2);   
    Ciphertext ct_nand = context.eval_lut(&combined, lut_fun_nand); 
    assertm(context.decrypt(&ct_nand) == 1, "ct_nand(0, 0) == 1");  
 
    ct0 = ct_nand;  
    ct1 = context.encrypt(0);  
    combined = ct0 + (ct1 * 2);  
    ct_nand = context.eval_lut(&combined, lut_fun_nand); 
    assertm(context.decrypt(&ct_nand) == 1, "ct_nand(0, 1) == 1"); 

    ct0 = context.encrypt(0);  
    ct1 = ct_nand;  
    combined = ct0 + (ct1 * 2);  
    ct_nand = context.eval_lut(&combined, lut_fun_nand); 
    assertm(context.decrypt(&ct_nand) == 1, "ct_nand(1, 0) == 1"); 
 
    ct0 = ct_nand;  
    ct1 = ct_nand;  
    combined = ct0 + (ct1 * 2);  
    ct_nand = context.eval_lut(&combined, lut_fun_nand); 
    assertm(context.decrypt(&ct_nand) == 0, "ct_nand(1, 1) == 0"); 

    std::cout << "Stress testing..." << std::endl;  
    for(int i = 0; i < 20; ++i){ 
        // 0 Nand 0
        ct0 = ct_nand; 
        ct1 = ct_nand; 
        combined = ct0 + (ct1 * 2);    
        ct_nand = context.eval_lut(&combined, lut_fun_nand);  
        assertm(context.decrypt(&ct_nand) == 1, "ct_nand(0, 0) == 1");  
    
        ct0 = ct_nand;  
        ct1 = context.encrypt(0);  
        combined = ct0 + (ct1 * 2);  
        ct_nand = context.eval_lut(&combined, lut_fun_nand);  
        assertm(context.decrypt(&ct_nand) == 1, "ct_nand(0, 1) == 1"); 

        ct0 = context.encrypt(0);  
        ct1 = ct_nand;  
        combined = ct0 + (ct1 * 2);  
        ct_nand = context.eval_lut(&combined, lut_fun_nand);  
        assertm(context.decrypt(&ct_nand) == 1, "ct_nand(1, 0) == 1"); 
    
        ct0 = ct_nand;  
        ct1 = ct_nand;  
        combined = ct0 + (ct1 * 2);  
        ct_nand = context.eval_lut(&combined, lut_fun_nand);  
        assertm(context.decrypt(&ct_nand) == 0, "ct_nand(1, 1) == 0");  
    } 
    std::cout << "Stress Test: OK" << std::endl;
}
