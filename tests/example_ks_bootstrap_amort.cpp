  
#include <gtest/gtest.h>
#include <chrono>
#include "fhe_deck.h"

/// @brief  This flag is defined in test_main.cpp
extern bool verbose;

using namespace FHEDeck;

 
TEST(KSAmortizedTest, StressTest){
    FHEContext ctx;
    ctx.generate_context(FHENamedParams::tfhe_11_KS_amortized);  
    std::shared_ptr<FunctionalBootstrapPublicKey> ks_pk = ctx.config->eval_key.bootstrap_pk; 

    PlaintextEncoding encoding = ctx.get_default_plaintext_encoding();
    encoding.set_type(PlaintextEncodingType::full_domain);
    encoding.set_plaintext_space(4);
    Ciphertext lwe_out = ctx.encrypt(0, encoding); 

    // Some functions
    std::function<int64_t(int64_t,int64_t)> F_1_0 = [](int64_t a, int64_t b) { return  (a) % b;};
    std::function<int64_t(int64_t)> F_1 = std::bind(F_1_0, std::placeholders::_1, encoding.get_plaintext_space());
    std::function<int64_t(int64_t,int64_t)> F_2_0 = [](int64_t a, int64_t b) { return  (a % 2) % b;};
    std::function<int64_t(int64_t)> F_2 = std::bind(F_2_0, std::placeholders::_1, encoding.get_plaintext_space());
    std::function<int64_t(int64_t,int64_t)> F_3_0 = [](int64_t a, int64_t b) { return  ((a*a ^ 0x41) + a * 3 + 7 * (a & 0xa)) % b;};
    std::function<int64_t(int64_t)> F_3 = std::bind(F_3_0, std::placeholders::_1, encoding.get_plaintext_space());
    std::function<int64_t(int64_t,int64_t)> F_4_0 = [](int64_t a, int64_t b) { return  (4 * (a / 4)) % b;};
    std::function<int64_t(int64_t)> F_4 = std::bind(F_4_0, std::placeholders::_1, encoding.get_plaintext_space());
    std::function<int64_t(int64_t,int64_t)> F_5_0 = [](int64_t a, int64_t b) { return  (a + (a << 1) + (a >> 1)) % b;};
    std::function<int64_t(int64_t)> F_5 = std::bind(F_5_0, std::placeholders::_1, encoding.get_plaintext_space());
    

    std::vector<std::function<int64_t(int64_t)>> F_vec = {F_1, F_2, F_3, F_4, F_5};
  
    std::vector<HomomorphicAccumulator> acc_vec;
    for(auto& F: F_vec) {
        acc_vec.push_back(ctx.setup_function(F, encoding));
    }

    auto message = rand() % encoding.get_plaintext_space();
    auto lwe_in = ctx.encrypt(message, encoding);

    auto start = std::chrono::high_resolution_clock::now(); 
    auto results = ctx.eval(lwe_in, acc_vec);
    auto stop = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    long correct = 0;
    
    for (int i = 0; i < F_vec.size(); i++) {
        long dec  = ctx.decrypt(results[i]);
        long target = F_vec[i](message);
        correct += dec == target;
    }
 
    ASSERT_EQ(correct, F_vec.size());  
}

TEST(KSAmortizedTest, PolynomialEvalTest){

    FHEContext ctx;
    ctx.generate_context(FHENamedParams::tfhe_11_KS_amortized);  
    std::shared_ptr<FunctionalBootstrapPublicKey> ks_pk = ctx.config->eval_key.bootstrap_pk; 

    PlaintextEncoding encoding = ctx.get_default_plaintext_encoding();
    encoding.set_type(PlaintextEncodingType::full_domain);
    encoding.set_plaintext_space(4);
    Ciphertext lwe_out = ctx.encrypt(0, encoding); 

    // Some function 
    std::function<int64_t(int64_t,int64_t)> F_1_0 = [](int64_t a, int64_t b) { return  (a) % b;};
    std::function<int64_t(int64_t)> F_1 = std::bind(F_1_0, std::placeholders::_1, encoding.get_plaintext_space());
    std::function<int64_t(int64_t,int64_t)> F_2_0 = [](int64_t a, int64_t b) { return  (a*a) % b;};
    std::function<int64_t(int64_t)> F_2 = std::bind(F_2_0, std::placeholders::_1, encoding.get_plaintext_space());
    std::function<int64_t(int64_t,int64_t)> F_3_0 = [](int64_t a, int64_t b) { return  (a*a*a) % b;};
    std::function<int64_t(int64_t)> F_3 = std::bind(F_3_0, std::placeholders::_1, encoding.get_plaintext_space());
    std::function<int64_t(int64_t,int64_t)> F_4_0 = [](int64_t a, int64_t b) { return  (a*a*a*a) % b;};
    std::function<int64_t(int64_t)> F_4 = std::bind(F_4_0, std::placeholders::_1, encoding.get_plaintext_space());
    std::function<int64_t(int64_t,int64_t)> F_5_0 = [](int64_t a, int64_t b) { return  (a*a*a*a*a) % b;};
    std::function<int64_t(int64_t)> F_5 = std::bind(F_5_0, std::placeholders::_1, encoding.get_plaintext_space());

    std::vector<std::function<int64_t(int64_t)>> F_vec = {F_1, F_2, F_3, F_4, F_5};
  
    std::vector<HomomorphicAccumulator> acc_vec;
    for(auto& F: F_vec) {
        acc_vec.push_back(ctx.setup_function(F, encoding));
    }

    auto message = rand() % encoding.get_plaintext_space();
    auto lwe_in = ctx.encrypt(message, encoding);

    std::vector<int64_t> scalars = {1, 2, 3, 4, 5}; 
    int64_t scalar = 0;
    std::vector<Ciphertext> results;
    /// Amortized test.
    auto start = std::chrono::high_resolution_clock::now(); 
    /// NOTE: Comment for parametrer sets without amortization
    //results = ctx.eval_lut_amortized(lwe_in, acc_vec);
    /// NOTE: Uncomment for parametrer sets without amortization 
    for(int i = 0; i < acc_vec.size(); ++i){
        Ciphertext ct = ctx.eval(lwe_in, acc_vec[i]);
        results.push_back(ct);
    }
     
    Ciphertext poly_out = ctx.eval_affine_function(results, scalars, scalar); 
    auto stop = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    long correct = 0;
    
    long exp_poly =  scalar;   
    long dec_poly = ctx.decrypt(poly_out);

    for (int i = 0; i < F_vec.size(); i++) {

        long dec  = ctx.decrypt(results[i]);
        exp_poly += (F_vec[i](message) * scalars[i]) % encoding.get_plaintext_space(); 
        long target = F_vec[i](message); 
        correct += dec == target;
    } 
    ASSERT_EQ(correct, F_vec.size());  
}
 