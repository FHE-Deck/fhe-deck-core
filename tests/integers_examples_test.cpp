#include <gtest/gtest.h>

#include <iostream>
#include <cassert>
#include <chrono>
#include "fhe_deck.h" 
#include "verbose_stream.hpp"

 /// @brief  This flag is defined in test_main.cpp
extern bool verbose;

using namespace FHEDeck;
 
void test_digit_integer(FHENamedParams param_set){ 
    FHEContext context;  
    context.generate_context(param_set);

    /// NOTE: The base is 2**5 = 32.
    /// But the plaintext space to encrypt these digits should be 2**6 = 64.
    /// What is the precision??? 
    DigitConfig config(context, 1 << 5, 2);  
    int32_t msg_1{17};
    int32_t msg_2{15};
    DigitInteger d1 = config.encrypt(msg_1);
    DigitInteger d2 = config.encrypt(msg_2);
    DigitInteger* ptr = &d2;
 
    ASSERT_TRUE(config.decrypt(d1) == msg_1); 
    ASSERT_TRUE(config.decrypt(d2) == msg_2); 
 
    ASSERT_TRUE(config.decrypt(d1+d2) == (msg_1 + msg_2)); 
    ASSERT_TRUE(config.decrypt(d1+16) == (msg_1 + 16)); 
    ASSERT_TRUE(config.decrypt(d1+5) == (msg_1 + 5)); 
    ASSERT_TRUE(config.decrypt(d1+30) == (msg_1 + 30));
 
    ASSERT_TRUE(config.decrypt(d1-d2) == (msg_1 - msg_2));
 
    ASSERT_TRUE(config.decrypt(d1-16) == (msg_1 - 16));
 

    DigitInteger d3 = d1 + d2; 
    ASSERT_TRUE(config.decrypt(d3) == (msg_1 + msg_2)); 

    DigitInteger d3_carry = d1.add_with_carry(d2); 
    ASSERT_TRUE(config.decrypt(d3_carry) == (msg_1 + msg_2)); 
    ASSERT_TRUE(context.decrypt(d3_carry.encrypted_digits.back()) == 0);

    DigitInteger d4 = d2 - d1; 
    ASSERT_TRUE(context.decrypt(d4) == Utils::integer_mod_form(msg_2 - msg_1, config.max+1)); 

    DigitInteger d4_carry = d2.subtract_with_carry(d1); 
    ASSERT_TRUE(context.decrypt(d4_carry) == Utils::integer_mod_form(msg_2 - msg_1, (config.max+1)*2)); 
    ASSERT_TRUE(context.decrypt(d4_carry.encrypted_digits.back()) == 1);
      
}
 

void test_rns_integer(FHENamedParams param_set){
    print_out << "test_rns_integer(FHENamedParams param_set)" << std::endl;
    FHEContext context;  
    context.generate_context(param_set);
    //RNSBase base({61, 47, 59, 53});
    RNSConfig base(context, {17, 19, 23, 13});
    int32_t msg_1{20};
    int32_t msg_2{17};
    RNSInteger c1(msg_1, base);
    RNSInteger c2(msg_2, base);
  
    ASSERT_TRUE(context.decrypt(c1) == msg_1); 
    ASSERT_TRUE(context.decrypt(c2) == msg_2);
    RNSInteger c3 = c1 + c2;
    ASSERT_TRUE(context.decrypt(c3) == (msg_1 + msg_2)); 
    RNSInteger c4 = c1 - c2;
    ASSERT_TRUE(context.decrypt(c4) == (msg_1 - msg_2)); 

    RNSInteger c5 = c1 * 20;
    ASSERT_TRUE(context.decrypt(c5) == (msg_1 * 20)); 

    RNSInteger c6 = c1 * c2;
    ASSERT_TRUE(context.decrypt(c6) == (msg_1 * msg_2)); 
}

void test_choose_digits(FHENamedParams param_set){

    print_out << "test_choose_digits(FHENamedParams param_set)" << std::endl;
    FHEContext context;  
    context.generate_context(param_set);
    PlaintextEncoding encoding = context.get_default_plaintext_encoding();
    encoding.set_type(PlaintextEncodingType::full_domain);
    encoding.set_plaintext_space(1 << 5);

    DigitConfig config(context, 1 << 4, 2);
    DigitInteger dummy(10, config); 
    int32_t size{10};
    int32_t msg[] = {5, 7}; 
    std::vector<Ciphertext> ct_vec_1;
    ct_vec_1.reserve(size);
    std::vector<Ciphertext> ct_vec_2;
    ct_vec_2.reserve(size);
    for(int32_t i = 0; i < size; ++i){ 
        ct_vec_1.push_back(context.encrypt(msg[0], encoding)); 
        ct_vec_2.push_back(context.encrypt(msg[1], encoding));
    } 
 

    int32_t bit{0};
    Ciphertext ctx_bit = context.encrypt(0, encoding); 
    std::vector<Ciphertext> out = dummy.choose_digits(ct_vec_1, ct_vec_2, ctx_bit);
     
    for(int32_t i{0}; i < size; ++i){
        if(context.decrypt(out[i]) != msg[bit]){ 
            FAIL();
        } 
    } 
}
 
void test_converstions_test(FHENamedParams param_set){
 
    FHEContext context;  
    context.generate_context(param_set);

    RNSConfig base(context, {17, 19, 13});
    DigitConfig config(context, 1 << 4, 4); 
    int32_t msg{1234}; 
    RNSInteger rns_ctx(msg, base); 
    DigitInteger digit_ctx(config, rns_ctx);     
    RNSInteger back(digit_ctx, base); 
    ASSERT_EQ(context.decrypt(digit_ctx), context.decrypt(back));
}


// ----- Digit Integer Test -----
class FHEBigIntDigitIntegerTest : public ::testing::TestWithParam<FHENamedParams> {};

TEST_P(FHEBigIntDigitIntegerTest, DigitInteger) {
    FHENamedParams param_set = GetParam();
    test_digit_integer(param_set);
}

INSTANTIATE_TEST_SUITE_P(
    DigitIntegerTest,
    FHEBigIntDigitIntegerTest,
    ::testing::Values(
        FHENamedParams::tfhe_11_KS_amortized
    )
);


// ----- RNS Integer Test -----
class FHEBigIntRNSIntegerTest : public ::testing::TestWithParam<FHENamedParams> {};

TEST_P(FHEBigIntRNSIntegerTest, RNSInteger) {
    FHENamedParams param_set = GetParam();
    test_rns_integer(param_set);
}

INSTANTIATE_TEST_SUITE_P(
    RNSIntegerTest,
    FHEBigIntRNSIntegerTest,
    ::testing::Values(
        FHENamedParams::tfhe_11_KS_amortized
    )
);


// ----- Choose Digits Test -----
class FHEBigIntChooseDigitsTest : public ::testing::TestWithParam<FHENamedParams> {};

TEST_P(FHEBigIntChooseDigitsTest, ChooseDigits) {
    FHENamedParams param_set = GetParam();
    test_choose_digits(param_set);
}

INSTANTIATE_TEST_SUITE_P(
    ChooseDigitsTest,
    FHEBigIntChooseDigitsTest,
    ::testing::Values(
        FHENamedParams::tfhe_11_KS_amortized
    )
);
 

// ----- Conversion Test -----
class FHEBigIntConversionTest : public ::testing::TestWithParam<FHENamedParams> {};

TEST_P(FHEBigIntConversionTest, Conversion) {
    FHENamedParams param_set = GetParam();
    test_converstions_test(param_set);
}

INSTANTIATE_TEST_SUITE_P(
    ConversionTest,
    FHEBigIntConversionTest,
    ::testing::Values(
        FHENamedParams::tfhe_11_KS_amortized
    )
);

 