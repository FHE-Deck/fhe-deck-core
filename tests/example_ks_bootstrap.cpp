
#include <gtest/gtest.h>

#include "cassert"
#include "fhe_deck.h" 

#include <chrono>

 /// @brief  This flag is defined in test_main.cpp
extern bool verbose;

using namespace FHEDeck;
using namespace std::chrono;
  
TEST(KSBootstrapTest, FDFBTest){
 
    FHEContext ctx; 
    ctx.generate_context(FHENamedParams::lmp_12_NTT_amortized);  
    PlaintextEncoding encoding = ctx.get_default_plaintext_encoding();
    encoding.set_plaintext_space(32);
    std::shared_ptr<FunctionalBootstrapPublicKey> ks_pk = ctx.config->eval_key.bootstrap_pk; 
    int64_t t = encoding.get_plaintext_space();
    Ciphertext lwe_out = ctx.encrypt(0, encoding);
    int64_t N = lwe_out.lwe_c->param->dim;
    int64_t Q = lwe_out.lwe_c->param->modulus;
 
    std::function<long(long,long)> F_in_0 = [](long a, long b) { return  ((a*a ^ 0x41) + a * 3 + 7 * (a & 0xa)) % b;};  
    std::function<int64_t(int64_t)> F_in = std::bind(F_in_0, std::placeholders::_1, t);
    HomomorphicAccumulator acc = ctx.setup_function(F_in);

    // Check every case 
    int64_t correct = 0; 
    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();
    int64_t elapsed = 0; 
    for (int32_t i = 0; i < t; i++) {
        int32_t message = i;
        Ciphertext lwe_in = ctx.encrypt(message, encoding);
 
        start = high_resolution_clock::now();
        ks_pk->full_domain_bootstrap(*lwe_out.lwe_c, acc.func_boot_acc, *lwe_in.lwe_c, encoding, encoding);  
        stop = high_resolution_clock::now();
        elapsed = elapsed + duration_cast<milliseconds>(stop-start).count();
 
        int64_t dec = ctx.decrypt(lwe_out);
  
        int64_t target = F_in(message); 

        correct += (target == dec);
    }
     
    ASSERT_EQ(correct, t);  
}
 