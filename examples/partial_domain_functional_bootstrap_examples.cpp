#include <iostream> 
#include "fhe_deck.h" 
#include <cassert>


using namespace FHEDeck;


void basic_partial_encoding_example(FHENamedParams param_set);
void computing_linear_functions_and_boolean_gates(FHENamedParams param_set);
void sanitization(FHENamedParams param_set);
void basic_function_amortization_example(FHENamedParams param_set);
void advanced_function_amortization(FHENamedParams param_set);

int main(){  
       
    basic_partial_encoding_example(FHENamedParams::tfhe_11_NTT);
   
    computing_linear_functions_and_boolean_gates(FHENamedParams::tfhe_11_NTT);

    sanitization(FHENamedParams::tfhe_11_NTT);

    basic_function_amortization_example(FHENamedParams::tfhe_11_NTT);

    advanced_function_amortization(FHENamedParams::tfhe_12_NTT_amortized);
 }
 


void basic_partial_encoding_example(FHENamedParams param_set){

    std::cout << "=========== Basic Partial Domain Example =============" << std::endl;
 
    /// Generate the secret and public key by instantiating the FHEContext with the desired parameter set.
    std::cout << "Generate Keys..." << std::endl;
    FHEContext context(param_set);  
    /// NOTE: Alternatively you can instantiate FHEContext, and generate the keys by calling the generate_context method as follows.
    /* 
    FHEContext context;
    context.generate_context(param_set);
    */
     
    /// Get the plaintext encoding algorithm. Its used to encode the messages before encryption.
    PlaintextEncoding encoding = context.get_default_plaintext_encoding();
    /// The default plaintext encoding is defined by a parameter set.
    /// Lets print the default encoding type for param_set.
    std::cout << "Default Encoding Space: " << encoding.get_plaintext_space() << std::endl;
    /// Lets make sure the plaintext space is 2 bits, that is 2^2 = 4.
    encoding.set_plaintext_space(4);
    std::cout << "New plaintext space: " << encoding.get_plaintext_space() << std::endl;
    /// The default encoding type is a enum class. To make sure that we use partial domain encoding set it as follows.
    encoding.set_type(PlaintextEncodingType::partial_domain);
  
    /// Encrypt messages guiving a plaintext and the encoding to the context.
    Ciphertext c0  = context.encrypt(0, encoding);  
    Ciphertext c1  = context.encrypt(1, encoding);    
    Ciphertext c2  = context.encrypt(2, encoding);  
    Ciphertext c3  = context.encrypt(3, encoding);  
   
    /// Here we verify whether the encryption is correct. 
    std::cout << "Decrypt(c0) = " <<  context.decrypt(c0) << std::endl;  
    std::cout << "Decrypt(c1) == " << context.decrypt(c1) << std::endl;  
    std::cout << "Decrypt(c2) == " << context.decrypt(c2) << std::endl;  
    std::cout << "Decrypt(c3) == " << context.decrypt(c0) << std::endl; 
 
    /// If we want to compute a function on the ciphertexts, lets define the function as follows.
    /// Note that the functions that we can define must return an integer. 
    /// Also remind, that the functions are computed on the plaintexts, 
    // so make sure that the domain of the function is the same as the plaintext space.
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

    /// Having the function definition, we can set up a homomorphic accumulator.
    /// This step precomputes certain values for the functional bootstrapping algorithm that allow it to compute fun_ham. 
    HomomorphicAccumulator lut_fun_ham = context.setup_function(fun_ham, encoding); 

    /// Now we evaluate fun_ham on c0, by running eval of the ciphertext and the homomorphic accumulator.
    Ciphertext ct4; 
    ct4 = context.eval(c0, lut_fun_ham); 
    /// Output should be 0
    std::cout << "context.decrypt(&ct4): " << context.decrypt(ct4) << std::endl;  
  
    /// Here we evaluate c1
    ct4 = context.eval(c1, lut_fun_ham); 
    /// Output should be 1
    std::cout << "context.decrypt(&ct4): " << context.decrypt(ct4) << std::endl; 
 
    /// Evaluate c2
    ct4 = context.eval(c2, lut_fun_ham); 
    /// Output should be 1
    std::cout << "context.decrypt(&ct4): " << context.decrypt(ct4) << std::endl; 
 
    /// And evaluate c3
    ct4 = context.eval(c3, lut_fun_ham); 
    /// Now output should be 2
    std::cout << "context.decrypt(&ct4): " << context.decrypt(ct4) << std::endl;  
 
}

 

void computing_linear_functions_and_boolean_gates(FHENamedParams param_set){

    std::cout << "=========== Computing Linear Functions and Boolean Gates =============" << std::endl;
 
    /// Initialize keys as in the basic_partial_encoding_example
    std::cout << "Generate Keys..." << std::endl;
    FHEContext context(param_set);    
    PlaintextEncoding encoding = context.get_default_plaintext_encoding(); 
    encoding.set_plaintext_space(4); 
    encoding.set_type(PlaintextEncodingType::partial_domain);
   

    /// Now we will compute a NAND function on two input ciphertexts.
    /// This exmaples will show how to use linear operations in between funcitonal bootstraps.
    /// Along the way we show how to run the evaluation algorithm without precomputing an homomorphic accumulator.
    /// NOTE: The fun_nand function expects to get as input a two bit number. 
    /// If we add a bigger number then the output is 2, whihc may not make sense.
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

    /// Lets dencrypt two bits. 
    Ciphertext ct0 = context.encrypt(1, encoding);  
    Ciphertext ct1 = context.encrypt(0, encoding);
    // The combined ciphertext sets the bit in ct0 as the first bit in a two bit sequence, and ct1 as the second bit.   
    Ciphertext combined = ct0 + (ct1 * 2);   
    /// Evaluate lut_fun_nand on combined. 
    Ciphertext ct_nand = context.eval(combined, lut_fun_nand); 
    // Output should be 1.
    std::cout << "ct_nand(0, 0) == " << context.decrypt(ct_nand) << std::endl; 

    /// Encrypt 1 and 0
    ct0 = context.encrypt(1, encoding);  
    ct1 = context.encrypt(0, encoding);  
    combined = ct0 + (ct1 * 2);  
    ct_nand = context.eval(combined, lut_fun_nand);  
    // Output should be 1.
    std::cout << "ct_nand(0, 0) == " << context.decrypt(ct_nand) << std::endl; 

    /// Encrypt 0 and 1
    ct0 = context.encrypt(0, encoding);  
    ct1 = context.encrypt(1, encoding);  
    combined = ct0 + (ct1 * 2);  
    ct_nand = context.eval(combined, lut_fun_nand);
    // Output should be 1.
    std::cout << "ct_nand(0, 0) == " << context.decrypt(ct_nand) << std::endl; 

    /// Encrypt 1 and 1
    ct0 = context.encrypt(1, encoding);  
    ct1 = context.encrypt(1, encoding);  
    combined = ct0 + (ct1 * 2);  
    ct_nand = context.eval(combined, lut_fun_nand);  
    // Output should be 0.
    std::cout << "ct_nand(0, 0) == " << context.decrypt(ct_nand) << std::endl; 
 

    /// Finally, if we want to sanitize a ciphertext to get circuit privacy 
    /// (the ciphertext doesn't reveal what computation was performed) 
    /// then we can do this as follows.
    Ciphertext sanitized = context.sanitize(ct_nand); 
    // Output should be the same as the previous ct_nand.
    std::cout << "Sanitized == " << context.decrypt(ct_nand) << std::endl; 
 
}

 
void sanitization(FHENamedParams param_set){

    std::cout << "=========== Sanitization Example =============" << std::endl;
 
    /// Initialize keys as in the basic_partial_encoding_example
    std::cout << "Generate Keys..." << std::endl;
    FHEContext context(param_set);    
    PlaintextEncoding encoding = context.get_default_plaintext_encoding(); 
    encoding.set_plaintext_space(4); 
    encoding.set_type(PlaintextEncodingType::partial_domain);
   
  
    /// Lets dencrypt two bits. 
    Ciphertext ct0 = context.encrypt(1, encoding);  
    Ciphertext ct1 = context.encrypt(0, encoding);
    // The combined ciphertext sets the bit in ct0 as the first bit in a two bit sequence, and ct1 as the second bit.   
    Ciphertext combined = ct0 + (ct1 * 2);    

    /// Finally, if we want to sanitize a ciphertext to get circuit privacy 
    /// (the ciphertext doesn't reveal what computation was performed) 
    /// then we can do this as follows.
    /// In other words the sanitized ciphertext should be indistinguishable from a freshly generated ciphertext on which nothing was computed yet. 
    std::cout << "Sanitizing a ciphertext..." << std::endl;
    Ciphertext sanitized = context.sanitize(combined); 
    // Output should be the same as the previous combined. That is it should be 1.
    std::cout << "Sanitized ciphertext decrypts to == " << context.decrypt(combined) << std::endl; 
 
}



void basic_function_amortization_example(FHENamedParams param_set){
    std::cout << "=========== Function Amortization Examples (Multi-Value Bootstrapping) =============" << std::endl;
 
    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl;
    context.generate_context(param_set); 
    PlaintextEncoding encoding = context.get_default_plaintext_encoding();
    encoding.set_type(PlaintextEncodingType::partial_domain);
    encoding.set_plaintext_space(8);

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

    /// Encrypt numbers in [0,7]. 
    /// Note that the plaintext space is 3-bits.
    Ciphertext ct0 = context.encrypt_public(0, encoding); 
    Ciphertext ct1 = context.encrypt_public(1, encoding); 
    Ciphertext ct2 = context.encrypt_public(2, encoding);
    Ciphertext ct3 = context.encrypt_public(3, encoding);
    Ciphertext ct4 = context.encrypt_public(4, encoding);
    Ciphertext ct5 = context.encrypt_public(5, encoding);
    Ciphertext ct6 = context.encrypt_public(6, encoding);
    Ciphertext ct7 = context.encrypt_public(7, encoding);

    /// Run bit_decomposition executes three functions on the input ciphertext with only a single bootstrapping.
    std::vector<Ciphertext> out_cts = context.eval(ct0, bit_decomp_luts); 
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 0); 
    std::cout << "Test Bin Decomp 0: OK" << std::endl;

    /// Decompose the second number
    out_cts = context.eval(ct1, bit_decomp_luts); 
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 0); 
    std::cout << "Test Bin Decomp 1: OK" << std::endl;
  
    out_cts = context.eval(ct2, bit_decomp_luts); 
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 0); 
    std::cout << "Test Bin Decomp 2: OK" << std::endl;

    out_cts = context.eval(ct3, bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 0); 
    std::cout << "Test Bin Decomp 3: OK" << std::endl;

    out_cts = context.eval(ct4, bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 1); 
    std::cout << "Test Bin Decomp 4: OK" << std::endl;


    out_cts = context.eval(ct5, bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 1); 
    std::cout << "Test Bin Decomp 5: OK" << std::endl;


    out_cts = context.eval(ct6, bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 1); 
    std::cout << "Test Bin Decomp 6: OK" << std::endl;


    out_cts = context.eval(ct7, bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 1); 
    std::cout << "Test Bin Decomp 7: OK" << std::endl;

}
 
void advanced_function_amortization(FHENamedParams param_set){
    std::cout << "=========== amortized_12_partial_domain_bootstrap_test =============" << std::endl;
 
    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl;
    context.generate_context(param_set); 
    PlaintextEncoding encoding = context.get_default_plaintext_encoding();
   
    /// Define the bit extraction function. The function extracts the bit from the number m on position index.
    auto bit_extract = [](int64_t m, int64_t index) -> int64_t {
        return (m % (1 << (index + 1)))/(1 << index);
    };
 
    /// NOTE: Normaly functional bootstraping computes a univariate funcitons (has only on argument).
    /// bit_extract is multivariate (takes two arguments) so how can we compute it on a ciphertext?
    /// The answer in use std::bind. 
    /// NOTE: Alternatively we would need to manually define a function for every possible index.
    /// But this way we can do this conveniently with one one simple loop. 

    /// Define a vector of homomorphic accumulators that precomputes info for the decomposition functions
    std::vector<HomomorphicAccumulator> bit_decomp_luts;
    for(int32_t index = 0; index < 4; ++index){ 
        /// NOTE: Binding the index to a counter. So each function in the vector computes its respective bit.
        /// This allows us to define funcitons with many inputs, bind them to a value and then conveniently evaluate them on ciphertexts.
        std::function<int64_t(int64_t)> bound_function = std::bind(bit_extract, std::placeholders::_1, index);
        /// Append the bound_function (bound to the current index) to the homomorphic accumulator vector.
        bit_decomp_luts.push_back(context.setup_function(bound_function)); 
    } 
   
    /// Encrypt messages from 0 to 15.
    std::vector<Ciphertext> cts;
    for(int32_t m = 0; m < 16 ; ++m){
        cts.push_back(context.encrypt_public(m, encoding));
    }
  
    /// Compute bit_decomp_luts (four diffferent functions) on the input ciphertexts.
    std::vector<Ciphertext> out_cts = context.eval(cts[0], bit_decomp_luts);  
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 0); 
    assert(context.decrypt(out_cts[3]) == 0); 
    std::cout << "Test Bin Decomp 0: OK" << std::endl; 
  
    out_cts = context.eval(cts[1], bit_decomp_luts); 
      
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 0); 
    assert(context.decrypt(out_cts[3]) == 0); 
    std::cout << "Test Bin Decomp 1: OK" << std::endl;
 
    out_cts = context.eval(cts[2], bit_decomp_luts); 

      
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 0); 
    assert(context.decrypt(out_cts[3]) == 0); 
    std::cout << "Test Bin Decomp 2: OK" << std::endl;

    out_cts = context.eval(cts[3], bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 0); 
    assert(context.decrypt(out_cts[3]) == 0); 
    std::cout << "Test Bin Decomp 3: OK" << std::endl;

    out_cts = context.eval(cts[4], bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 1); 
    assert(context.decrypt(out_cts[3]) == 0); 
    std::cout << "Test Bin Decomp 4: OK" << std::endl;


    out_cts = context.eval(cts[5], bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 1); 
    assert(context.decrypt(out_cts[3]) == 0); 
    std::cout << "Test Bin Decomp 5: OK" << std::endl;


    out_cts = context.eval(cts[6], bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 1); 
    assert(context.decrypt(out_cts[3]) == 0); 
    std::cout << "Test Bin Decomp 6: OK" << std::endl;


    out_cts = context.eval(cts[7], bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 1); 
    assert(context.decrypt(out_cts[3]) == 0); 
    std::cout << "Test Bin Decomp 7: OK" << std::endl;


    out_cts = context.eval(cts[8], bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 0); 
    assert(context.decrypt(out_cts[3]) == 1); 
    std::cout << "Test Bin Decomp 8: OK" << std::endl;


    out_cts = context.eval(cts[9], bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 0); 
    assert(context.decrypt(out_cts[3]) == 1); 
    std::cout << "Test Bin Decomp 9: OK" << std::endl;


    out_cts = context.eval(cts[10], bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 0); 
    assert(context.decrypt(out_cts[3]) == 1); 
    std::cout << "Test Bin Decomp 10: OK" << std::endl;


    out_cts = context.eval(cts[11], bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 0); 
    assert(context.decrypt(out_cts[3]) == 1); 
    std::cout << "Test Bin Decomp 11: OK" << std::endl;


    out_cts = context.eval(cts[12], bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 1); 
    assert(context.decrypt(out_cts[3]) == 1); 
    std::cout << "Test Bin Decomp 12: OK" << std::endl;


    out_cts = context.eval(cts[13], bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 1); 
    assert(context.decrypt(out_cts[3]) == 1); 
    std::cout << "Test Bin Decomp 13: OK" << std::endl;


    out_cts = context.eval(cts[14], bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 1); 
    assert(context.decrypt(out_cts[3]) == 1); 
    std::cout << "Test Bin Decomp 14: OK" << std::endl;


    out_cts = context.eval(cts[15], bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 1); 
    assert(context.decrypt(out_cts[3]) == 1); 
    std::cout << "Test Bin Decomp 15: OK" << std::endl;

}
