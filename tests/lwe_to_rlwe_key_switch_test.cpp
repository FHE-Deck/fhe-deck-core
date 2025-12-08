#include <gtest/gtest.h>

#include "cassert"
#include "fhe_deck.h"  

/// @brief  This flag is defined in test_main.cpp
extern bool verbose;

using namespace FHEDeck;
 
TEST(LWEToRLWEKeySwitch, BasicKeySwitchTest){

    /// TODO: test params harcoded. Would be better to have some flexibility
    long N = 1 << 10;
    long coef_modulus = 68719464449;
    double rlwe_stddev = 0;
    long lwe_dim = N;

    auto rlwe_param = std::make_shared<RLWEParam>(RingType::negacyclic, N, coef_modulus, PolynomialArithmetic::ntt64);
    auto lwe_param = std::make_shared<LWEParam>(lwe_dim, coef_modulus);

    auto rlwe_gadget = std::make_shared<SignedDecompositionGadget>(N,coef_modulus,1 << 4);
    auto sk_rlwe = std::make_shared<RLWESK>(rlwe_param, KeyDistribution::ternary, rlwe_stddev);
    RLWEGadgetSK gadget_sk_rlwe(rlwe_gadget, sk_rlwe);

    //LWESK sk_lwe(lwe_param, sk_rlwe->sk_poly.get(), rlwe_stddev, KeyDistribution::ternary);
    auto sk_lwe = sk_rlwe->extract_lwe_key();

    auto lwe_to_rlwe_key = LWEToRLWEKeySwitchKey(*sk_lwe, gadget_sk_rlwe);

    long message = rand() % (1 << 10);
    auto test_input = sk_lwe->encrypt(message);
    RLWECT output(rlwe_param);

    lwe_to_rlwe_key.lwe_to_rlwe_key_switch(output, *test_input);

    Polynomial dec(N, coef_modulus);
    sk_rlwe->partial_decrypt(dec, output);

    ASSERT_EQ(dec[0], message); 
}