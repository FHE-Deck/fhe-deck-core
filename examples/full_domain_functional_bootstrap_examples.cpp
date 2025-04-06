#include <iostream>
#include <cassert>
#include <chrono>
#include "fhe_deck.h" 


#define assertm(exp, msg) assert(((void)msg, exp))
 
using namespace FHEDeck;

/**
 * @brief This example shows limitations of the partial domain bootstraping algorithm.  
 */
void partial_domain_bootstrapping_fail_example(FHENamedParams param_set);

/**
 * @brief This example shows how to use the full domain bootstrapping algorithm to overcome the limitations of partial domain bootstrapping. 
 */
void full_domain_bootstrapping_example(FHENamedParams param_set);

/**
 * @brief This example shows how to use the full domain bootstrapping and modular arithmetic. 
 */
void full_domain_bootstrapping_and_modular_arithmetic(FHENamedParams param_set);

/**
 * @brief This example shows how to use the function amortization for full domain bootstrapping. 
 * Function amortization allows to bootstrap and compute multiple function on the same input ciphertext at the cost of a single bootstrapping invocation.
 */
void function_amortization_for_full_domain_bootstrapping(FHENamedParams param_set);


int main(){

    partial_domain_bootstrapping_fail_example(FHENamedParams::tfhe_11_NTT);

    full_domain_bootstrapping_example(FHENamedParams::tfhe_11_NTT);

    full_domain_bootstrapping_and_modular_arithmetic(FHENamedParams::tfhe_11_NTT);

    function_amortization_for_full_domain_bootstrapping(FHENamedParams::tfhe_11_KS_amortized);

}

void partial_domain_bootstrapping_fail_example(FHENamedParams param_set){
    std::cout << "=========== Partial Domain Bootstrapping Fail Example =============" << std::endl;

    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl;
    
    context.generate_context(param_set); 
    
    
    PlaintextEncoding encoding = context.get_default_plaintext_encoding();
    /// Set partial domain encoding.
    encoding.set_type(PlaintextEncodingType::partial_domain); 

    /// Set a modulus. Operations will be done in modulo this modulus.
    int32_t modulus = 11;
    encoding.set_plaintext_space(modulus);
     
    int32_t c1_plain = 5;
    Ciphertext c1  = context.encrypt(c1_plain, encoding);  
    int32_t c2_plain = 7;
    Ciphertext c2  = context.encrypt(c2_plain, encoding);  
  
    std::cout << "Decrypt(c1) == 1: " << context.decrypt(c1) << std::endl; 
     
    std::cout << "Decrypt(c2) == 2: " << context.decrypt(c2) << std::endl; 
 
    Ciphertext c3 = c1 + c2;

    std::cout << "Decrypt(c1 + c2) == 1: " << context.decrypt(c3) << std::endl;

    /// Now lets compute the identity function on c3
    auto id = [](int64_t m) -> int64_t {
        return m;
    }; 
    /// To compute we can precompute a HomomorphicAccumulator given the function and the input encoding.
    HomomorphicAccumulator lut_identity = context.setup_function(id, encoding); 
    /// Evaluate the function.
    Ciphertext c_cout = context.eval(c3, lut_identity);   

    std::cout << "Decrypt(id(c3)): " << context.decrypt(c_cout) << std::endl;
    /// NOTE: The result should be 1, but is -1 modulo 11 = 10.
    /// For the identity function the sign of the function of simply off by hte sign.
    /// But other functions may behave in weird ways and return values that aren't in the domain of the function.
 
}



void full_domain_bootstrapping_example(FHENamedParams param_set){
    std::cout << "=========== Full Domain Bootstrapping Example =============" << std::endl;

    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl;
    
    context.generate_context(param_set); 
    
    
    PlaintextEncoding encoding = context.get_default_plaintext_encoding();
    /// Set partial domain encoding.
    encoding.set_type(PlaintextEncodingType::full_domain); 

    /// Set a modulus. Operations will be done in modulo this modulus.
    int32_t modulus = 11;
    encoding.set_plaintext_space(modulus);
     
    int32_t c1_plain = 5;
    Ciphertext c1  = context.encrypt(c1_plain, encoding);  
    int32_t c2_plain = 7;
    Ciphertext c2  = context.encrypt(c2_plain, encoding);  
  
    std::cout << "Decrypt(c1) == 1: " << context.decrypt(c1) << std::endl; 
     
    std::cout << "Decrypt(c2) == 2: " << context.decrypt(c2) << std::endl; 
 
    Ciphertext c3 = c1 + c2;

    std::cout << "Decrypt(c1 + c2) == 1: " << context.decrypt(c3) << std::endl;

    /// Now lets compute the identity function on c3
    auto id = [](int64_t m) -> int64_t {
        return m;
    }; 
    /// To compute we can precompute a HomomorphicAccumulator given the function and the input encoding.
    HomomorphicAccumulator lut_identity = context.setup_function(id, encoding); 
    /// Evaluate the function.
    Ciphertext c_cout = context.eval(c3, lut_identity);   

    std::cout << "Decrypt(id(c3)): " << context.decrypt(c_cout) << std::endl;
    /// NOTE: The result should be 1, but is -1 modulo 11 = 10.
    /// For the identity function the sign of the function of simply off by hte sign.
    /// But other functions may behave in weird ways and return values that aren't in the domain of the function.
 
}




void full_domain_bootstrapping_and_modular_arithmetic(FHENamedParams param_set){

    std::cout << "=========== Full Domain Bootstrapping and Modular Arithmetic =============" << std::endl;

    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl;
    
    context.generate_context(param_set); 
    
    
    PlaintextEncoding encoding = context.get_default_plaintext_encoding();
    encoding.set_type(PlaintextEncodingType::full_domain); 

    /// Set a modulus. Operations will be done in modulo this modulus.
    int32_t modulus = 11;
    encoding.set_plaintext_space(modulus);
     
    int32_t c1_plain = 1;
    Ciphertext c1  = context.encrypt(c1_plain, encoding);  
    int32_t c2_plain = 2;
    Ciphertext c2  = context.encrypt(2, encoding);  
  
    std::cout << "Decrypt(c1) == 1: " << context.decrypt(c1) << std::endl; 
     
    std::cout << "Decrypt(c2) == 2: " << context.decrypt(c2) << std::endl; 
 
    /**
     * The following demonstrates correct modular arithmetic on ciphertexts. 
     */
    int32_t c3_plain = 0;
    Ciphertext c3 = context.encrypt(c3_plain, encoding);
    c3.add(c3, c1); 
    c3_plain = (c3_plain + c1_plain) % modulus;
    
    assertm(context.decrypt(c3) == c3_plain, "Decrypt(c3+c1) == 1");
    std::cout << "Decrypt(c3+c1): " << context.decrypt(c3) << std::endl;

    c3.add(c3, c2); 
    c3_plain = (c3_plain + c2_plain) % modulus;
    assertm(context.decrypt(c3) == c3_plain, "Decrypt(c3+c1+c2) == 3");
    std::cout << "Decrypt(c3+c1+c2): " << context.decrypt(c3) << std::endl;
    c3.add(c3, c2); 
    c3_plain = (c3_plain + c2_plain) % modulus; 
    assertm(context.decrypt(c3) == c3_plain, "Decrypt(c3+c1+c2+c2) == 1");
    std::cout << "Decrypt(c3+c1+c2+c2): " << context.decrypt(c3) << std::endl;
 
    c3.mul(c3, 3); 
    c3_plain = (c3_plain * 3) % modulus;
    assertm(context.decrypt(c3) == c3_plain, "Decrypt((c3+c1+c2+c2) * 3) == 3");
    std::cout << "Decrypt((c3+c1+c2+c2) * 3): "  << context.decrypt(c3) << std::endl; 
 
    /**
     * Here are exmaples of copying ciphertexts. The folloiwng will call the copy constructor and copy assignment operator.
     */ 
    std::cout << "Copying to LWE ct objects" << std::endl;
    Ciphertext ct1 = c1; 
    Ciphertext ct2 = c2;
    assertm(context.decrypt(ct1) == c1_plain, "context.decrypt(&ct1) == 1");
    std::cout << "context.decrypt(ct1) == 1: "  << context.decrypt(ct1) << std::endl;

    assertm(context.decrypt(ct2) == c2_plain, "context.decrypt(&ct2) == 2");
    std::cout << "context.decrypt(ct2) == 2: "  << context.decrypt(ct2) << std::endl;


    /**
     * Now we will show how to use the overloaded arithmetic operators for ciphertexts.
     */
    Ciphertext ct3 = ct1 + 1;  
    c3_plain = (c1_plain + 1) % modulus;
    assertm(context.decrypt(ct3) == c3_plain, "context.decrypt(&(ct1 + 1)) == 2");
    std::cout << "context.decrypt(ct1 + 1): "  << context.decrypt(ct3) << std::endl;

    ct3 = 1 + ct1;  
    c3_plain = (1 + c1_plain) % modulus;
    assertm(context.decrypt(ct3) == c3_plain, "context.decrypt(&(1+ ct1)) == 2");
    std::cout << "context.decrypt(1+ ct1): "  << context.decrypt(ct3) << std::endl;

    ct3 = ct1 - 2; 
    c3_plain = Utils::integer_mod_form(c1_plain - 2, modulus);
    assertm(context.decrypt(ct3) == c3_plain, "context.decrypt(&(ct1 - 2)) == 3");
    std::cout << "context.decrypt(ct1 - 2): "  << context.decrypt(ct3) << std::endl;

    ct3 = 2 - ct1; 
    c3_plain = Utils::integer_mod_form(2 - c1_plain, modulus);
    assertm(context.decrypt(ct3) == c3_plain, "context.decrypt(&(2 - ct1)) == 1");
    std::cout << "context.decrypt(2 - ct1): "  << context.decrypt(ct3) << std::endl;
 
    ct3 = ct1 * 2; 
    c3_plain = (c1_plain * 2) % modulus;
    assertm(context.decrypt(ct3) == c3_plain, "context.decrypt(&(ct1 * 2)) == 2");
    std::cout << "context.decrypt(ct1 * 2): "  << context.decrypt(ct3) << std::endl;

    ct3 = 2 * ct1; 
    c3_plain = (2 * c1_plain) % modulus;
    assertm(context.decrypt(ct3) == c3_plain, "context.decrypt(&(2 * ct1)) == 2");
    std::cout << "context.decrypt(2 * ct1): " << context.decrypt(ct3) << std::endl;

    ct3 = ct1 + ct2; 
    c3_plain = (c1_plain + c2_plain) % modulus;
    assertm(context.decrypt(ct3) == c3_plain, "context.decrypt(&(ct1 + ct2)) == 3");
    std::cout << "context.decrypt(ct1 + ct2): "  << context.decrypt(ct3) << std::endl;

    ct3 = ct2 - ct1; 
    c3_plain = Utils::integer_mod_form(c2_plain - c1_plain, modulus);
    
    assertm(context.decrypt(ct3) == c3_plain, "context.decrypt(&(ct2 - ct1)) == 1");
    std::cout << "context.decrypt(ct2 - ct1): " << context.decrypt(ct3) <<  std::endl;

    assertm(context.decrypt(ct1) == c1_plain, "context.decrypt(&ct1) == 1"); 
    std::cout << "context.decrypt(ct1): " << context.decrypt(ct1) << std::endl;

    ct3 = - ct1; 
    c3_plain = Utils::integer_mod_form(-c1_plain, modulus);
    assertm(context.decrypt(ct3) == c3_plain, "context.decrypt(&(ct3 = - ct1))) == 3"); 
    std::cout << "context.decrypt(- ct1): " << context.decrypt(ct3) << std::endl;
  
 
    /**
     * The context has a build in function that helps to evalluate affine functions on vectors of ciphertexts.
     */
    std::vector<Ciphertext> v;
    v.push_back(ct1);
    v.push_back(ct2);

    std::vector<int64_t> scalars;
    scalars.push_back(2);
    scalars.push_back(1);
    int64_t scalar = 3;
    Ciphertext c_cout = context.eval_affine_function(v, scalars, scalar);  

    int32_t plain_out = Utils::integer_mod_form(c1_plain * 2 + c2_plain * 1 + 3, modulus);
    // The outcome should be 3, because (2 * 1 + 1 * 2 + 3) % 4 = 3
    assertm(context.decrypt(c_cout) == plain_out, "context.decrypt((2 * 1 + 1 * 2 + 3) % 4 = 3)) == 3"); 
    std::cout << "context.decrypt((2 * 1 + 1 * 2 + 3) % 4 = 3)): " << context.decrypt(c_cout) << std::endl; 
  
 
    /// Now lets define a function that computes the identity function.  
    auto id = [](int64_t m) -> int64_t {
        return m;
    }; 
    /// To compute we can precompute a HomomorphicAccumulator given the function and the input encoding.
    HomomorphicAccumulator lut_identity = context.setup_function(id, encoding); 
    /// Evaluate the function.
    /// NOTE: We do not need to precompute the homomorphic accumulator, we can also run the eval function directly.
    c_cout = context.eval(ct1, lut_identity);   

    plain_out = c1_plain;
    assertm(context.decrypt(c_cout) == plain_out, "context.decrypt(context.eval_lut(&ct1, lut_identity)) == 1"); 
    std::cout << "context.decrypt(context.eval_lut(&ct1, lut_identity)): "  << context.decrypt(c_cout) <<  std::endl;
 
    /// We do the same with a function that add 1 to the input.
    auto id_plus = [](int64_t m) -> int64_t {
        return (m+1);
    }; 
    HomomorphicAccumulator lut_id_plus = context.setup_function(id_plus, encoding); 
    c_cout = context.eval(ct1, lut_id_plus);  
    plain_out = Utils::integer_mod_form(id_plus(c1_plain), modulus);
    assertm(context.decrypt(c_cout) == plain_out, "context.decrypt(context.eval_lut(&ct1, lut_id_plus)) == 2"); 
    std::cout << "context.decrypt(context.eval_lut(&ct1, lut_id_plus)): "  << context.decrypt(c_cout) << std::endl;
    
    /// Now we will show how to bind one of the parameters of the function. 
    /// So lets define a function with two parameters. 
    std::function<int64_t(int64_t,int64_t)> fun_msb = [](int64_t m, int64_t t) -> int64_t {
        if(m < t/2){
            return 0;
        }else{
            return 1;
        } 
    }; 
    /// We bind the parameter t to the value of the plaintext modulus.
    std::function<int64_t(int64_t)> fun_msb_t = std::bind(fun_msb, std::placeholders::_1, modulus);
    HomomorphicAccumulator lut_fun_msb = context.setup_function(fun_msb_t, encoding); 
    /// Evaluate the function. Note that the evaluation is always with respect to the first parameter. 
    c_cout = context.eval(ct1, lut_fun_msb);  
    /// And check if the evaluation is correct. 
    plain_out = fun_msb_t(c1_plain);
    assertm(context.decrypt(c_cout) == plain_out, "context.decrypt(context.eval_lut(&ct1, lut_fun_msb)) == 0"); 
    std::cout << "context.decrypt(context.eval_lut(&ct1, lut_fun_msb)): "  << context.decrypt(c_cout) << std::endl;
     
}




void function_amortization_for_full_domain_bootstrapping(FHENamedParams param_set){
    std::cout << "=========== Function Amortization for Full Domain Bootstrapping =============" << std::endl;


    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl; 
    context.generate_context(param_set); 
    
    PlaintextEncoding encoding = context.get_default_plaintext_encoding();
    encoding.set_type(PlaintextEncodingType::full_domain);

    /**
     * In the following we will extract  three bits from the input ciphertext with only a single bootstrapping invocation.
     */

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
    std::cout << "context.decrypt(out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    std::cout << "context.decrypt(out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    std::cout << "context.decrypt(out_cts[2]): " << context.decrypt(out_cts[2]) << std::endl;
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 0); 
    std::cout << "Test Bin Decomp 0: OK" << std::endl;

    out_cts = context.eval(ct1, bit_decomp_luts);
    std::cout << "context.decrypt(out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    std::cout << "context.decrypt(out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    std::cout << "context.decrypt(out_cts[2]): " << context.decrypt(out_cts[2]) << std::endl;
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 0); 
    std::cout << "Test Bin Decomp 1: OK" << std::endl;

    out_cts = context.eval(ct2, bit_decomp_luts);
    std::cout << "context.decrypt(out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    std::cout << "context.decrypt(out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    std::cout << "context.decrypt(out_cts[2]): " << context.decrypt(out_cts[2]) << std::endl;
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 0); 
    std::cout << "Test Bin Decomp 2: OK" << std::endl;

    out_cts = context.eval(ct3, bit_decomp_luts);
    std::cout << "context.decrypt(out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    std::cout << "context.decrypt(out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    std::cout << "context.decrypt(out_cts[2]): " << context.decrypt(out_cts[2]) << std::endl;
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 0); 
    std::cout << "Test Bin Decomp 3: OK" << std::endl;

    out_cts = context.eval(ct4, bit_decomp_luts);
    std::cout << "context.decrypt(out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    std::cout << "context.decrypt(out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    std::cout << "context.decrypt(out_cts[2]): " << context.decrypt(out_cts[2]) << std::endl;
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 1); 
    std::cout << "Test Bin Decomp 4: OK" << std::endl;


    out_cts = context.eval(ct5, bit_decomp_luts);
    std::cout << "context.decrypt(out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    std::cout << "context.decrypt(out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    std::cout << "context.decrypt(out_cts[2]): " << context.decrypt(out_cts[2]) << std::endl;
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 1); 
    std::cout << "Test Bin Decomp 5: OK" << std::endl;


    out_cts = context.eval(ct6, bit_decomp_luts);
    std::cout << "context.decrypt(out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    std::cout << "context.decrypt(out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    std::cout << "context.decrypt(out_cts[2]): " << context.decrypt(out_cts[2]) << std::endl;
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 1); 
    std::cout << "Test Bin Decomp 6: OK" << std::endl;


    out_cts = context.eval(ct7, bit_decomp_luts);
    std::cout << "context.decrypt(out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    std::cout << "context.decrypt(out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    std::cout << "context.decrypt(out_cts[2]): " << context.decrypt(out_cts[2]) << std::endl;
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 1); 
    std::cout << "Test Bin Decomp 7: OK" << std::endl;

}
 