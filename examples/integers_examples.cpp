#include <iostream>
#include <cassert>
#include <chrono>
#include "fhe_deck.h" 

 
using namespace FHEDeck;

/**
 * @brief This example shows how to use encrypted big integers that are decomposed into digits.  
 */
void digit_integers_examples(FHENamedParams param_set); 

/**
 * @brief This example shows how to use encrypted big integers that are represented in the residue number system (RNS).
 */
void rns_examples(FHENamedParams param_set);

/**
 * @brief This example shows how to convert between encrypted integers in the residue number system (RNS) and encrypted integers that are decomposed into digits. 
 */
void rns_and_digit_conversions_example(FHENamedParams param_set);


int main(){  

    digit_integers_examples(FHENamedParams::tfhe_11_KS_amortized); 

    rns_examples(FHENamedParams::tfhe_11_KS_amortized);
 
    rns_and_digit_conversions_example(FHENamedParams::tfhe_11_KS_amortized);

}
 
void digit_integers_examples(FHENamedParams param_set){
    std::cout << "======== Digit Integers Examples ===========" << std::endl;
    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl;
    context.generate_context(param_set);

    /// NOTE: The base is 2**5 = 32. 

    DigitConfig config(context, 1 << 5, 2);  
    /// Choose some messages.
    int32_t msg_1{17};
    int32_t msg_2{15};
    /// Encrypt the messages as a DigitInteger
    DigitInteger d1 = config.encrypt(msg_1);
    DigitInteger d2 = config.encrypt(msg_2);
    DigitInteger* ptr = &d2;
 
    std::cout << "d1: " << context.decrypt(d1) << std::endl;
    assert(config.decrypt(d1) == msg_1); 
    std::cout << "d2: " << context.decrypt(d2) << std::endl;
    assert(config.decrypt(d2) == msg_2); 
 
    
    std::cout << "d1+d2: " << context.decrypt(d1+d2) << std::endl;
    assert(config.decrypt(d1+d2) == (msg_1 + msg_2)); 
    
    std::cout << "d1+16: " << context.decrypt(d1+16) << std::endl;
    assert(config.decrypt(d1+16) == (msg_1 + 16)); 
     
    
    std::cout << "d1-d2: " << context.decrypt(d1-d2) << std::endl;
    assert(config.decrypt(d1-d2) == (msg_1 - msg_2));
 
    
    std::cout << "d1-16: " << context.decrypt(d1-16) << std::endl;
    assert(config.decrypt(d1-16) == (msg_1 - 16));
 

    /// We can also extract the carry when digits will overflow after addition.
    DigitInteger d3 = d1 + d2; 
    std::cout << "d3: " << context.decrypt(d3) << std::endl;
    assert(config.decrypt(d3) == (msg_1 + msg_2)); 

    DigitInteger d3_carry = d1.add_with_carry(d2);  
    assert(config.decrypt(d3_carry) == (msg_1 + msg_2)); 
    
    std::cout << "d3_carry: " << context.decrypt(d3_carry.encrypted_digits.back()) << std::endl;
    assert(context.decrypt(d3_carry.encrypted_digits.back()) == 0);

    DigitInteger d4 = d2 - d1; 
    std::cout << "d4: " << context.decrypt(d4) << std::endl;
    assert(context.decrypt(d4) == Utils::integer_mod_form(msg_2 - msg_1, config.max+1)); 

    DigitInteger d4_carry = d2.subtract_with_carry(d1); 
    assert(context.decrypt(d4_carry) == Utils::integer_mod_form(msg_2 - msg_1, (config.max+1)*2)); 
    std::cout << "d4_carry: " << context.decrypt(d4_carry.encrypted_digits.back()) << std::endl;
    assert(context.decrypt(d4_carry.encrypted_digits.back()) == 1);
      
}
 

void rns_examples(FHENamedParams param_set){
    std::cout << "======== RNS Examples ===========" << std::endl;

    std::cout << "Generate Keys..." << std::endl;
    FHEContext context(param_set); 
    /// We define the RNS base by providing a list of moduli.
    /// The full modulus will in this case be: 17*19*23*13 = 96577 
    RNSConfig base(context, {17, 19, 23, 13});
    /// Example messages
    int32_t msg_1{20};
    int32_t msg_2{17};
    /// Encrypt the messages as a RNS integers
    RNSInteger c1 = base.encrypt(msg_1);
    RNSInteger c2 = base.encrypt(msg_2);
    
    /// Lets check if the RNS integers decrypt to the correct values. 
    std::cout << "c1: " << context.decrypt(c1) << std::endl;
    assert(context.decrypt(c1) == msg_1); 
    std::cout << "c2: " << context.decrypt(c2) << std::endl;
    assert(context.decrypt(c2) == msg_2);

    /// Now we can do some operations on the encrypted messages.
    RNSInteger c3 = c1 + c2;
    std::cout << "c3 = c1 + c2: " << context.decrypt(c3) << std::endl; 
    assert(context.decrypt(c3) == (msg_1 + msg_2)); 

    RNSInteger c4 = c1 - c2;
    std::cout << "c4 = c1 - c2: " << context.decrypt(c4) << std::endl; 
    assert(context.decrypt(c4) == (msg_1 - msg_2)); 

    RNSInteger c5 = c1 * 20;
    std::cout << "c5 = c1 * 20: " << context.decrypt(c5) << std::endl; 
    assert(context.decrypt(c5) == (msg_1 * 20)); 

    RNSInteger c6 = c1 * c2;
    std::cout << "c6 = c1 * c2: " << context.decrypt(c6) << std::endl; 
    assert(context.decrypt(c6) == (msg_1 * msg_2)); 
  
}
 


void rns_and_digit_conversions_example(FHENamedParams param_set){

    std::cout << "======== RNS and Digit Conversions Example ===========" << std::endl;
    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl;
    context.generate_context(param_set);

    /// First we define the RNS and the digit decomposition bases.  
    RNSConfig base(context, {17, 19, 13});
    DigitConfig config(context, 1 << 4, 4); 
    /// Example message
    int32_t msg{1234};
    /// Encrypt the message as a RNS integer 
    RNSInteger rns_ct(msg, base); 
    /// Now we convert the RNS integer to a DigitInteger by calling the appropriate construcotr.
    DigitInteger digit_ct(config, rns_ct);                
    /// Lets check if the conversion was correct.
    std::cout << "digit_ct: " << context.decrypt(digit_ct) << std::endl;
    assert(context.decrypt(digit_ct) == msg); 
    /// Now we will convert the DigitInteger back to a RNS integer.
    RNSInteger back_to_rns(digit_ct, base);
    /// And check if its correct
    std::cout << "back_to_rns: " << context.decrypt(back_to_rns) << std::endl;
    assert(context.decrypt(back_to_rns) == msg);
}

 