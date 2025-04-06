#include <iostream>
#include <cassert>
#include <chrono>
#include "fhe_deck.h" 


#define assertm(exp, msg) assert(((void)msg, exp))
 
using namespace FHEDeck;

 
/**
 * @brief This exampels shows a specific encoding type that alows to handle signed integers in a partial domain. 
 * Note, that this encoding variant sacrafices correctness and presicion, and suffers of similar limitations as partical domain encoding.
 */
void partial_domain_signed_int_encoding_example(FHENamedParams param_set);

int main(){
    partial_domain_signed_int_encoding_example(FHENamedParams::tfhe_11_NTT); 
}


void partial_domain_signed_int_encoding_example(FHENamedParams param_set){
    
    std::cout << "=========== Partial Domain Signed int Encoding Example =============" << std::endl;
 

    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl;
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

    assertm(context.decrypt(ct0) == 0, "context.decrypt(&ct0) == 0");
    std::cout << "context.decrypt(ct0) == 0: "   << context.decrypt(ct0) << std::endl;
    assertm(context.decrypt(ct1) == 1, "context.decrypt(&ct1) == 1");
    std::cout << "context.decrypt(ct1) == 1: "   << context.decrypt(ct1) << std::endl;
    assertm(context.decrypt(ct2) == 2, "context.decrypt(&ct2) == 2");
    std::cout << "context.decrypt(ct2) == 2: "   << context.decrypt(ct2) <<  std::endl;
    assertm(context.decrypt(ct3) == 3, "context.decrypt(&ct3) == 3");
    std::cout << "context.decrypt(ct3) == 3: "   << context.decrypt(ct3) << std::endl;
    
    assertm(context.decrypt(mct1) == -1, "context.decrypt(&mct1) == -1");
    std::cout << "context.decrypt(mct1) == -1: "   << context.decrypt(mct1) << std::endl;
    assertm(context.decrypt(mct2) == -2, "context.decrypt(&mct1) == -2");
    std::cout << "context.decrypt(mct2) == -2: "   << context.decrypt(mct2) << std::endl;
    assertm(context.decrypt(mct3) == -3, "context.decrypt(&mct1) == -3");
    std::cout << "context.decrypt(mct3) == -3: "   << context.decrypt(mct3) << std::endl;

 
    std::cout << "Decrypt(ct4): " << context.decrypt(ct4) << std::endl; 
 
    std::cout << "Decrypt(mct4): " << context.decrypt(mct4) << std::endl;
 
    Ciphertext ct_add = ct1 + mct1;
    //assertm(context.decrypt(ct_add) == 0, "context.decrypt(&ct1 + mct1) == 0");
    std::cout << "Decrypt(ct_add = ct1 + mct1): "  << context.decrypt(ct_add) << std::endl; 
    ct_add = ct2 + mct2;
    //assertm(context.decrypt(ct_add) == 0, "context.decrypt(&ct_add) == 0");
    std::cout << "Decrypt(ct_add = ct2 + mct2): "   << context.decrypt(ct_add) << std::endl;  
    ct_add = ct3 + mct3;
    //assertm(context.decrypt(ct_add) == 0, "context.decrypt(&ct_add) == 0");
    std::cout << "Decrypt(ct_add = ct3 + mct3): "  << context.decrypt(ct_add) << std::endl; 
    ct_add = ct1 + mct2;
    //assertm(context.decrypt(ct_add) == -1, "context.decrypt(&ct_add) == -1");
    std::cout << "Decrypt(ct_add = ct1 + mct2): OK"  << std::endl; 
    ct_add = ct2 + mct3;
    //assertm(context.decrypt(ct_add) == -1, "context.decrypt(&ct_add) == -1");
    std::cout << "Decrypt(ct_add = ct2 + mct3): "  << context.decrypt(ct_add) << std::endl; 
    ct_add = ct1 + mct3;
    //assertm(context.decrypt(ct_add) == -2, "context.decrypt(&ct_add) == -1");
    std::cout << "Decrypt(ct_add = ct1 + mct3): "  << context.decrypt(ct_add) <<  std::endl; 
    ct_add = ct3 + mct1;
    //assertm(context.decrypt(ct_add) == 2, "context.decrypt(&ct_add) == 2");
    std::cout << "Decrypt(ct_add = ct3 + mct1): "  << context.decrypt(ct_add) << std::endl; 

  
 
    auto fun_identity = [](int64_t m) -> int64_t {
        return m; 
    };    
   
    HomomorphicAccumulator lut_fun_identity = context.setup_function(fun_identity, encoding);  
   
    Ciphertext ct_id = context.eval(mct1, lut_fun_identity);  
    ct_id = context.eval(ct_id, lut_fun_identity); 
    assertm(context.decrypt(ct_id) == -1, "context.eval_lut(&mct1, lut_fun_identity) == -1");
    std::cout << "context.eval_lut(mct1, lut_fun_identity) == -1: "  << context.decrypt(ct_id) << std::endl; 

    
    ct_id = context.eval(mct2, lut_fun_identity);   
    ct_id = context.eval(ct_id, lut_fun_identity); 
    assertm(context.decrypt(ct_id) == -2, "context.eval_lut(&mct2, lut_fun_identity) == -2");
    std::cout << "context.eval_lut(&mct2, lut_fun_identity) == -2: "  << context.decrypt(ct_id) << std::endl;  

     

    auto fun_relu = [](int64_t m) -> int64_t {
        if(m >= 0){
            return m; 
        }else{
            return 0;
        }
    };  
  
    Ciphertext ct_relu = context.eval(ct2, fun_relu);   
    assertm(context.decrypt(ct_relu) == 2, "context.eval_lut(&ct2, fun_relu) == 2");
    std::cout << "context.eval_lut(&ct2, fun_relu) == 2: " << context.decrypt(ct_relu) << std::endl; 

    
    ct_relu = context.eval(mct3, fun_relu);   
    assertm(context.decrypt(ct_relu) == 0, "context.eval_lut(&mct3, fun_relu) == 0");
    std::cout << "context.eval_lut(&mct0, fun_relu) == 0: " << context.decrypt(ct_relu) << std::endl; 
   
     
     
}
 