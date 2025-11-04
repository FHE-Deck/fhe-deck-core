#include <gtest/gtest.h>

#include <iostream>
#include "fhe_deck.h"
#include "verbose_stream.hpp"

/// @brief  This flag is defined in test_main.cpp
extern bool verbose;

using namespace FHEDeck;


void gadget_sampling_correctness_test(int test_num, int N, long Q, int base, double stddev, GadgetType type){
    print_out << "============ gadget_sampling_correctness_test ==========" << std::endl; 
    std::shared_ptr<Distribution> rand = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, Q-1)); 
    std::shared_ptr<Gadget> g;
    if(type == GadgetType::signed_decomposition_gadget){  
        g = std::shared_ptr<Gadget>(new SignedDecompositionGadget(N, Q, base)); 
    }else if(type == GadgetType::discrete_gaussian_gadget){ 
        g = std::shared_ptr<Gadget>(new DiscreteGaussianSamplingGadget(N, Q, base, stddev)); 
    }  
      
    Polynomial poly(N, Q);
    PolynomialArrayCoefForm decomp(N, Q, base); 
    Polynomial result(N, Q);
    long temp;
    for(int k = 0; k < test_num; ++k){
        // Choose some random poly 
        rand->fill_array(poly.vec, N);
        // Sample
        g->sample(decomp, poly.vec); 
        // Compose back modulo Q, and compare to poly
        for(int i = 0; i < N; ++i){
            result[i] = 0;
            for(int j = 0; j < g->digits; ++j){
                temp = decomp.vec_array_2d[j][i];
                for(int k = 0; k < j; ++k){
                    temp *= base;
                    temp %= Q;
                }  
                result[i] += temp;
            }
        }
        Utils::array_mod_form(result.vec, result.vec, N, Q); 
        if(result != poly){   
            FAIL();
        } 
    }   
}

 

void printing_outcome(int test_num, int N, long Q, int base, double stddev, GadgetType type){ 
    std::shared_ptr<Distribution> rand = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, Q));
    std::shared_ptr<Gadget> g;
    if(type == GadgetType::signed_decomposition_gadget){  
        g = std::shared_ptr<Gadget>(new SignedDecompositionGadget(N, Q, base)); 
    }else if(type == GadgetType::discrete_gaussian_gadget){ 
        g = std::shared_ptr<Gadget>(new DiscreteGaussianSamplingGadget(N, Q, base, stddev)); 
    }    
    Polynomial poly(N, Q);
    PolynomialArrayCoefForm decomp(N, Q, base);
    long* signed_decomp = new long[N];  
    Polynomial result(N, Q);
    long* decomp_flat = new long[g->digits * g->degree];
    long temp;
    for(int k = 0; k < test_num; ++k){
        // Choose some random poly 
        rand->fill_array(poly.vec, N); 
        // Sample
        g->sample(decomp, poly.vec); 
        for(int j = 0; j < g->digits; ++j){
            Utils::array_signed_form(signed_decomp, decomp.vec_array_2d[j], N, Q); 
        }
        // Compose back modulo Q, and compare to poly
        for(int i = 0; i < N; ++i){
            result[i] = 0;
            for(int j = 0; j < g->digits; ++j){
                temp = decomp.vec_array_2d[j][i]; 
                decomp_flat[j * N + i]  = decomp.vec_array_2d[j][i];
                for(int k = 0; k < j; ++k){
                    temp *= base;
                    temp %= Q;
                }  
                result[i] += temp;
            }
        } 
        Utils::array_mod_form(result.vec, result.vec, N, Q); 
        
        if(result != poly){  
            FAIL(); 
        } 
    } 
  
    double mean = Utils::mean(decomp_flat, g->digits * g->degree);
    long max = Utils::max(decomp_flat, g->digits * g->degree);
    long min = Utils::min(decomp_flat, g->digits * g->degree); 
    long var = Utils::variance(decomp_flat, g->digits * g->degree, mean);
    long s = Utils::standard_deviation(decomp_flat, g->digits * g->degree, mean);
    long positive = Utils::count_positive(decomp_flat, g->digits * g->degree);
    long negative = Utils::count_negative(decomp_flat, g->digits * g->degree); 
 
    delete[] decomp_flat;   
}


struct GadgetTestParams {
    int test_num;
    int N;
    long Q;
    int base;
    double stddev;
    GadgetType type;
};


class GadgetSamplingTest : public ::testing::TestWithParam<GadgetTestParams> {};

TEST_P(GadgetSamplingTest, Correctness) {
    GadgetTestParams p = GetParam();
    gadget_sampling_correctness_test(p.test_num, p.N, p.Q, p.base, p.stddev, p.type);
}

INSTANTIATE_TEST_SUITE_P(
    GadgetSamplingParams,
    GadgetSamplingTest,
    ::testing::Values(
        GadgetTestParams{100, 64, 512, 8, 0.0, GadgetType::signed_decomposition_gadget},
        GadgetTestParams{100, 64, 512, 8, 15, GadgetType::discrete_gaussian_gadget},
        GadgetTestParams{100, 2048, 21001, 8, 15, GadgetType::discrete_gaussian_gadget},
        // NTT prime smaller than 2**32
        GadgetTestParams{100, 2048, 4294955009, 256, 300, GadgetType::discrete_gaussian_gadget},
        // NTT prime smaller than 2**33
        GadgetTestParams{100, 2048, 8589905921, 1024, 1025, GadgetType::discrete_gaussian_gadget},
        // NTT prime smaller than 2**36
        GadgetTestParams{100, 2048, 68719464449, 16, 20, GadgetType::discrete_gaussian_gadget},
        // NTT prime smaller than 2**45
        GadgetTestParams{100, 2048, 35184372088831, 16, 20, GadgetType::discrete_gaussian_gadget},
        // Testing Power of base. Q = 2**48 = 256**6
        GadgetTestParams{100, 1000, 281474976710656, 256, 225812, GadgetType::discrete_gaussian_gadget}
    )
);

 