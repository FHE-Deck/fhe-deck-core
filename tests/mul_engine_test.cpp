
#include <gtest/gtest.h>

#include "fhe_deck.h"
#include <chrono>
#include "verbose_stream.hpp"

/// @brief  This flag is defined in test_main.cpp
extern bool verbose;

using namespace FHEDeck; 

void mul_test(int32_t tests, std::shared_ptr<PolynomialMultiplicationEngine> engine_left, std::shared_ptr<PolynomialMultiplicationEngine> engine_right, int32_t degree, int64_t modulus, int64_t bound){
    print_out << "====== mul_test ==========" << std::endl;
    std::shared_ptr<Distribution> rand_uni = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, degree));
    std::shared_ptr<Distribution> rand_bound = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, bound));
  

    bool test_eval_equal = true;
    for(int32_t i = 0; i < tests; ++i){
        Polynomial input_poly(degree, modulus); 
        rand_uni->fill(input_poly);
        
        std::shared_ptr<PolynomialEvalForm> left_eval(engine_left->init_polynomial_eval_form()); 
        std::shared_ptr<PolynomialEvalForm> right_eval(engine_right->init_polynomial_eval_form()); 
         
         
        engine_left->to_eval(*left_eval.get(), input_poly); 
 
        engine_right->to_eval(*right_eval.get(), input_poly); 

        Polynomial left_poly(degree, modulus);
        Polynomial right_poly(degree, modulus);

        
        engine_left->to_coef(left_poly, *left_eval.get());
        engine_right->to_coef(right_poly, *right_eval.get());

        if(left_poly != right_poly){
            FAIL(); 
            print_out << "Test Eval Equivalence: Fail at " << i << std::endl;
            print_out << "input_poly.coefs: " <<  input_poly.to_string(5) << std::endl;
            print_out << "left_poly.coefs: " << left_poly.to_string(5) << std::endl;
            print_out << "right_poly.coefs: " << right_poly.to_string(5) << std::endl; 
        }
    } 

    bool test_eval_equal_array = true;
    int32_t array_size = 10;
    std::shared_ptr<PolynomialArrayEvalForm> left_eval_array(engine_left->init_polynomial_array_eval_form(array_size));
    std::shared_ptr<PolynomialArrayEvalForm> right_eval_array(engine_right->init_polynomial_array_eval_form(array_size));
    for(int32_t i = 0; i < tests; ++i){
        PolynomialArray input_array(degree, modulus, array_size); 
        rand_uni->fill(input_array); 

        engine_left->to_eval(*left_eval_array.get(), input_array);
        engine_right->to_eval(*right_eval_array.get(), input_array);
        
        PolynomialArray left_poly_array(degree, modulus, array_size);
        PolynomialArray right_poly_array(degree, modulus, array_size);
        engine_left->to_coef(left_poly_array, *left_eval_array.get());
        engine_right->to_coef(right_poly_array, *right_eval_array.get());

        if(left_poly_array != right_poly_array){
            FAIL();   
        }
    } 

    /// Multiplication Test (multiply two polynomials twice, and check if the output is the same)
    bool test_mul = true;
    for(int32_t i = 0; i < tests; ++i){
        Polynomial poly_1(degree, modulus);
        Polynomial poly_2(degree, modulus); 
        rand_uni->fill(poly_1); 
        rand_bound->fill(poly_2);


        std::shared_ptr<PolynomialEvalForm> left_eval_1(engine_left->init_polynomial_eval_form());
        std::shared_ptr<PolynomialEvalForm> left_eval_2(engine_left->init_polynomial_eval_form());
        std::shared_ptr<PolynomialEvalForm> left_eval_out(engine_left->init_polynomial_eval_form());
        std::shared_ptr<PolynomialEvalForm> right_eval_1(engine_right->init_polynomial_eval_form());
        std::shared_ptr<PolynomialEvalForm> right_eval_2(engine_right->init_polynomial_eval_form());
        std::shared_ptr<PolynomialEvalForm> right_eval_out(engine_right->init_polynomial_eval_form());

        engine_left->to_eval(*left_eval_1.get(), poly_1);
        engine_left->to_eval(*left_eval_2.get(), poly_2);
        engine_right->to_eval(*right_eval_1.get(), poly_1);
        engine_right->to_eval(*right_eval_2.get(), poly_2);
 
        engine_left->mul(*left_eval_out.get(), *left_eval_1.get(), *left_eval_2.get()); 
 
        engine_right->mul(*right_eval_out.get(), *right_eval_1.get(), *right_eval_2.get());
        
        Polynomial left_poly(degree, modulus);
        Polynomial right_poly(degree, modulus);
        engine_left->to_coef(left_poly, *left_eval_out.get());
        engine_right->to_coef(right_poly, *right_eval_out.get());

        if(left_poly != right_poly){
            FAIL(); 
            print_out << "left_poly.coefs: " << left_poly.to_string(5) << std::endl;
            print_out << "right_poly.coefs: " << right_poly.to_string(5) << std::endl; 
        }
    } 

    /// Multisum 1 test: Precompute one array to eval form, and compute the multisum with a PolynomialArrayCoefForm 
    array_size = 10;
    bool test_multisum = true;
    for(int32_t i = 0; i < tests; ++i){
        PolynomialArray poly_array_1(degree, modulus, array_size);
        PolynomialArray poly_array_2(degree, modulus, array_size); 
        rand_uni->fill(poly_array_1); 
        rand_bound->fill(poly_array_2);

        std::shared_ptr<PolynomialArrayEvalForm> left_eval_1(engine_left->init_polynomial_array_eval_form(array_size));
        std::shared_ptr<PolynomialArrayEvalForm> left_eval_2(engine_left->init_polynomial_array_eval_form(array_size));
        std::shared_ptr<PolynomialArrayEvalForm> right_eval_1(engine_right->init_polynomial_array_eval_form(array_size));
        std::shared_ptr<PolynomialArrayEvalForm> right_eval_2(engine_right->init_polynomial_array_eval_form(array_size));
 

        engine_left->to_eval(*left_eval_1.get(), poly_array_1);
        engine_left->to_eval(*left_eval_2.get(), poly_array_2);
        engine_right->to_eval(*right_eval_1.get(), poly_array_1);
        engine_right->to_eval(*right_eval_2.get(), poly_array_2);

        Polynomial left_out(degree, modulus);
        Polynomial right_out(degree, modulus);
 
        engine_left->multisum(left_out, *left_eval_1.get(), *left_eval_2.get()); 
 
        engine_right->multisum(right_out, *right_eval_1.get(), *right_eval_2.get()); 
          
        if(left_out != right_out){
            FAIL(); 
            print_out << "left_out.coefs: " << left_out.to_string(5) << std::endl;
            print_out << "right_out.coefs: " <<  right_out.to_string(5) << std::endl; 
        }
    }
 
 
    /// Multisum 2 test: Precompute one array to eval form, and compute the multisum that return the PolynomialArrayEvalForm
    /// In the same test, use the PolynomialArrayEvalForm from the previous and compute another multisum that takes all eval form as input.  
    array_size = 10;
    bool test_multisum_2 = true;
    bool test_eval_2 = true;
    for(int32_t i = 0; i < tests; ++i){
        PolynomialArray poly_array_1(degree, modulus, array_size);
        PolynomialArray poly_array_2(degree, modulus, array_size); 
        rand_uni->fill(poly_array_1); 
        rand_bound->fill(poly_array_2);

        std::shared_ptr<PolynomialArrayEvalForm> left_eval_1(engine_left->init_polynomial_array_eval_form(array_size));
        std::shared_ptr<PolynomialArrayEvalForm> left_eval_2(engine_left->init_polynomial_array_eval_form(array_size));
        std::shared_ptr<PolynomialArrayEvalForm> right_eval_1(engine_right->init_polynomial_array_eval_form(array_size));
        std::shared_ptr<PolynomialArrayEvalForm> right_eval_2(engine_right->init_polynomial_array_eval_form(array_size));
 
 
        engine_left->to_eval(*left_eval_2.get(), poly_array_2); 
        engine_right->to_eval(*right_eval_2.get(), poly_array_2);

        Polynomial left_out(degree, modulus);
        Polynomial right_out(degree, modulus);

        engine_left->multisum(left_out, *left_eval_1.get(), poly_array_1, *left_eval_2.get());
        engine_right->multisum(right_out, *right_eval_1.get(), poly_array_1, *right_eval_2.get());
          
        if(left_out != right_out){
            FAIL(); 
            print_out << "left_out.coefs: " <<  left_out.to_string(5) << std::endl;
            print_out << "right_out.coefs: " << right_out.to_string(5) << std::endl; 
        }
 
        PolynomialArray poly_array_1_left(degree, modulus, array_size);
        PolynomialArray poly_array_1_right(degree, modulus, array_size);
        engine_left->to_coef(poly_array_1_left, *left_eval_1.get());
        engine_right->to_coef(poly_array_1_right, *right_eval_1.get());
        if(poly_array_1_left != poly_array_1_right){
            FAIL(); 
        } 
    } 

}


class MulEngineTestsParam{
    
    public: 

    int32_t tests;
    int32_t degree;
    int64_t modulus;
    int64_t bound;
    PolynomialArithmetic arithmetic_left; 
    PolynomialArithmetic arithmetic_right; 

    std::shared_ptr<PolynomialMultiplicationEngine> left_engine;
    std::shared_ptr<PolynomialMultiplicationEngine> right_engine;
    

    MulEngineTestsParam(int32_t tests, 
        int32_t degree, 
        int64_t modulus, 
        PolynomialArithmetic arithmetic_left, 
        PolynomialArithmetic arithmetic_right,
        int64_t bound): 
        tests(tests), degree(degree), modulus(modulus), arithmetic_left(arithmetic_left), arithmetic_right(arithmetic_right), bound(bound){
            PolynomialMultiplicationEngineBuilder builder = PolynomialMultiplicationEngineBuilder();
            builder.set_degree(degree);
            builder.set_coef_modulus(modulus);
            builder.set_polynomial_arithmetic(arithmetic_left);
            left_engine = builder.build();
            builder.set_polynomial_arithmetic(arithmetic_right);
            right_engine = builder.build();
    }
};

class MulEngineTestSuite : public ::testing::TestWithParam<MulEngineTestsParam> {};

TEST_P(MulEngineTestSuite, MultEngine) {
    const auto& p = GetParam();
    mul_test(p.tests,  p.left_engine, p.right_engine, p.degree, p.modulus, p.bound);
}

INSTANTIATE_TEST_SUITE_P(
    MultEngine,
    MulEngineTestSuite,
    ::testing::Values(
        MulEngineTestsParam{10, 2048, 4294955009, PolynomialArithmetic::ntt64, PolynomialArithmetic::double_fft, 16777216},
        MulEngineTestsParam{10, 2048, 281474976694273, PolynomialArithmetic::ntt64, PolynomialArithmetic::double_fft, 16777216},
        MulEngineTestsParam{10, 2048, 281474976694273, PolynomialArithmetic::naive, PolynomialArithmetic::double_fft, 16777216},
        MulEngineTestsParam{10, 2048, 281474976694273, PolynomialArithmetic::naive, PolynomialArithmetic::ntt64, 16777216},
        MulEngineTestsParam{10, 2048, 281474976694273, PolynomialArithmetic::long_double_fft, PolynomialArithmetic::double_fft, 16777216},
        MulEngineTestsParam{10, 2048, 281474976694273, PolynomialArithmetic::long_double_fft, PolynomialArithmetic::naive, 16777216},
        MulEngineTestsParam{10, 2048, 281474976694273, PolynomialArithmetic::long_double_fft, PolynomialArithmetic::ntt64, 16777216}
    )
);
  