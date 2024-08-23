#include "cassert"

#include "fhe_context.h"
#include "lwe_to_rlwe_keyswitch.h"

#define assertm(exp, msg) assert(((void)msg, exp))

using namespace fhe_deck;

int main(int argc, char** argv) {

    // test params harcoded
    long N = 1 << 10;
    long coef_modulus = 68719464449;
    double rlwe_stddev = 0;
    long lwe_dim = N;

    auto rlwe_param = std::make_shared<RLWEParam>(negacyclic, N, coef_modulus, ntt64);
    auto lwe_param = std::make_shared<LWEParam>(lwe_dim, coef_modulus);

    auto rlwe_gadget = std::make_shared<SignedDecompositionGadget>(N,coef_modulus,1 << 4);
    auto sk_rlwe = std::make_shared<RLWESK>(rlwe_param, ternary, rlwe_stddev);
    auto gadget_sk_rlwe = std::make_shared<RLWEGadgetSK>(rlwe_gadget, sk_rlwe);

    auto sk_lwe = std::make_shared<LWESK>(lwe_param, sk_rlwe->sk_poly.coefs, rlwe_stddev, ternary);

    auto lwe_to_rlwe_key = LWEToRLWEKeySwitchKey(sk_lwe, gadget_sk_rlwe);

    long message = rand() % (1 << 10);
    auto test_input = sk_lwe->encrypt(message);
    RLWECT output(rlwe_param);

    lwe_to_rlwe_key.lwe_to_rlwe_key_switch(&output, test_input);

    Polynomial dec(N, coef_modulus);
    sk_rlwe->partial_decrypt(&dec, &output);

    assertm(dec.coefs[0] == message, "\\phase(LWE->RLWE(ct)) == message");
    std::cout << "LWEtoRLWEKeySwitching OK" << std::endl;
}