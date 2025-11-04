#include <gtest/gtest.h>

#include "fhe_deck.h"
#include "verbose_stream.hpp"

/// @brief  This flag is defined in test_main.cpp
extern bool verbose;

using namespace FHEDeck; 


#if defined(USE_NTL)
void compare_naive_with_ntl(int32_t degree, int64_t modulus){

    std::shared_ptr<Distribution> rand_uni = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, modulus));
    PolynomialMultiplicationEngineBuilder builder = PolynomialMultiplicationEngineBuilder();
    builder.set_degree(degree);
    builder.set_coef_modulus(modulus);
    builder.set_polynomial_arithmetic(PolynomialArithmetic::ntt64);   
    std::shared_ptr<PolynomialMultiplicationEngine> mul_engine =  builder.build();
    NTLInversionEngine ntl_engine(degree, modulus);
    EuclideanInversionEngine euclid_engine(degree, modulus);

    Polynomial poly(degree, modulus);
    Polynomial one(degree, modulus);
    one.zeroize();
    one[0] = 1;
 
    for(int32_t i = 0; i < 100; ++i){  
        rand_uni->fill_array(poly.vec, degree);
        Polynomial inv_poly(degree, modulus);
        Polynomial inv_poly_2(degree, modulus);  
        bool has_inverse = ntl_engine.inv(inv_poly, poly);
        bool has_inverse_2 = euclid_engine.inv(inv_poly_2, poly);
        if(has_inverse != has_inverse_2){
            FAIL();
        }
        if(has_inverse){ 
            Polynomial mul_poly(degree, modulus);  
            mul_engine->mul(mul_poly, poly, inv_poly_2);
            if(one != mul_poly){  
                print_out << "Inversion Fail "  << std::endl;
                print_out << "inv_poly: " << inv_poly.to_string(5) << std::endl;
                print_out << "inv_poly_2: " << inv_poly_2.to_string(5) << std::endl;
                FAIL();
            } 
        } 
    } 
}
#endif

void test_integer_inv(int32_t degree, int64_t modulus){

    EuclideanInversionEngine euclid_engine(degree, modulus);
    std::shared_ptr<Distribution> rand_uni = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, modulus)); 
    bool test = true;  
    for(int32_t i =0; i < 1000; ++i){ 
        uint64_t x =  rand_uni->next();
        uint64_t inv_x = Utils::mod_inv(x, modulus);
        uint64_t result = ((__int128_t)x * (__int128_t)inv_x) % (__int128_t)modulus; 
        if(result != 1){
            print_out << "Inverse Fail" << std::endl; 
            print_out << "("<< x << " * " << inv_x << ") % " << modulus << " = " << result << std::endl; 
            FAIL();
        }
    }  
}

void poly_sub_test(int32_t degree, int64_t modulus){
    EuclideanInversionEngine euclid_engine(degree, modulus);
    std::shared_ptr<Distribution> rand_uni = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, modulus)); 
    std::vector<int64_t> poly_1;
    poly_1.resize(degree);
    rand_uni->fill_array(poly_1.data(), degree); 
    std::vector<int64_t> poly_2 = poly_1;
    std::vector<int64_t> test_poly = euclid_engine.polynomial_subtraction(poly_1, poly_2, modulus); 

    for(int i = 0; i < test_poly.size(); ++i){ 
        if(test_poly[i] != 0){
            FAIL();
        }
    }  
    poly_2.resize(10);
    test_poly = euclid_engine.polynomial_subtraction(poly_1, poly_2, modulus); 
    for(int32_t i = 0; i < 10; ++i){
        if(test_poly[i] != 0){
            FAIL();
        }
    }
    for(int32_t i = 10; i < degree; ++i){
        if(test_poly[i] != poly_1[i]){
            FAIL();
        }
    }  
    test_poly = euclid_engine.polynomial_subtraction(poly_2, poly_1, modulus); 
    for(int32_t i = 0; i < 10; ++i){
        if(test_poly[i] != 0){
            FAIL();
        }
    }
    for(int32_t i = 10; i < degree; ++i){
        if(Utils::integer_mod_form(-poly_1[i], modulus) != test_poly[i]){
            FAIL();
        }
    } 
}


#if defined(USE_NTL)
void poly_mul_test(int32_t degree, int64_t modulus){
    EuclideanInversionEngine euclid_engine(degree, modulus);
    std::shared_ptr<Distribution> rand_uni = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, modulus)); 
    std::vector<int64_t> poly_1;
    poly_1.resize(degree);
    rand_uni->fill_array(poly_1.data(), degree); 
    std::vector<int64_t> poly_2;
    poly_2.resize(degree);
    rand_uni->fill_array(poly_2.data(), degree); 

    NTL::ZZ p(modulus);
    NTL::ZZ_p::init(p);

    NTL::ZZ_pX ntl_poly_1;
    NTL::ZZ_pX ntl_poly_2;
    for (int i = 0; i < degree; ++i){
        NTL::SetCoeff(ntl_poly_1, i, poly_1[i]);  
        NTL::SetCoeff(ntl_poly_2, i, poly_2[i]);  
    }

    std::vector<int64_t> poly_test  = euclid_engine.polynomial_multiplication(poly_1, poly_2, modulus);
    NTL::ZZ_pX ntl_poly_test = ntl_poly_1 * ntl_poly_2; 
    for(int i = 0; i < deg(ntl_poly_test); ++i){
        if(coeff(ntl_poly_test, i) != poly_test[i]){
            FAIL();
        }
    } 
} 

void div_test(int32_t degree, int64_t modulus){
    EuclideanInversionEngine euclid_engine(degree, modulus);
    std::shared_ptr<Distribution> rand_uni = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, modulus)); 
    std::vector<int64_t> poly_1;
    poly_1.resize(degree);
    std::vector<int64_t> poly_2;
    poly_2.resize(degree);

    NTL::ZZ p(modulus);
    NTL::ZZ_p::init(p); 
    NTL::ZZ_pX ntl_poly_1;
    NTL::ZZ_pX ntl_poly_2;
    NTL::ZZ_pX ntl_quotient;
    NTL::ZZ_pX ntl_reminder;
 
    for(int32_t k = 0; k < 1000; ++k){ 
        rand_uni->fill_array(poly_1.data(), degree); 
        rand_uni->fill_array(poly_2.data(), degree);  
        auto [quotient, reminder] = euclid_engine.polynomial_division(poly_1, poly_2, modulus);

        for (int i = 0; i < degree; ++i){
            NTL::SetCoeff(ntl_poly_1, i, poly_1[i]);  
            NTL::SetCoeff(ntl_poly_2, i, poly_2[i]);  
        }
        // Perform polynomial division
        DivRem(ntl_quotient, ntl_reminder, ntl_poly_1, ntl_poly_2);
        if(deg(ntl_quotient) != quotient.size()-1){
            print_out << "Division Failed at Quotient degree is wrong!" << std::endl;
            print_out << "deg(ntl_quotient): " << deg(ntl_quotient) << std::endl;
            print_out << "quotient.size(): " << quotient.size() << std::endl;
            FAIL(); 
        }
        if(deg(ntl_reminder) != reminder.size()-1){
            print_out << "Division Failed at Reminder degree is wrong!" << std::endl; 
            print_out << "deg(ntl_reminder): " << deg(ntl_reminder) << std::endl;
            print_out << "reminder.size(): " << reminder.size() << std::endl;
            FAIL(); 
        }
        for(int32_t i = 0; i < deg(ntl_quotient); ++i){
            if(coeff(ntl_quotient, i) != quotient[i]){
                print_out << "Division Failed at Quotient" << std::endl;
                FAIL();
            }
        } 
        for(int32_t i = 0; i < deg(ntl_reminder); ++i){
            if(coeff(ntl_reminder, i) != reminder[i]){
                print_err << "ntl_reminder: " ;
                for(int i = 0; i < deg(ntl_reminder); ++i){
                    print_err << coeff(ntl_reminder, i) << ", " ;
                }
                print_err << std::endl;
                print_err << "    reminder: " ;
                for(int i = 0; i < deg(ntl_reminder); ++i){
                    print_err << reminder[i] << ", " ;
                }
                print_err << std::endl;
                print_err << "Division Failed at Reminder" << std::endl;
                FAIL();
            }
        }
    } 
}
#endif


struct TestParam{
    int32_t degree;
    int64_t modulus;
};


class IntegerInv : public ::testing::TestWithParam<TestParam> {
};

TEST_P(IntegerInv, IntegerInvTest) {
    TestParam p = GetParam();
    test_integer_inv(p.degree, p.modulus);
}

// Register the parameter sets
INSTANTIATE_TEST_SUITE_P(
    IntegerInvTest,
    IntegerInv,
    ::testing::Values(
        TestParam{2048, 4294955009},
        TestParam{4096, 281474976694273},
        TestParam{4096, 35184371884033}
    )
);



class PolySub : public ::testing::TestWithParam<TestParam> {
};

TEST_P(PolySub, PolySubTest) {
    TestParam p = GetParam();
    poly_sub_test(p.degree, p.modulus);
}

// Register the parameter sets
INSTANTIATE_TEST_SUITE_P(
    PolySubTest,
    PolySub,
    ::testing::Values(
        TestParam{2048, 4294955009},
        TestParam{4096, 281474976694273},
        TestParam{4096, 35184371884033}
    )
);


#if defined(USE_NTL)
 
class PolyMul : public ::testing::TestWithParam<TestParam> {
};

TEST_P(PolyMul, PolyMulTest) {
    TestParam p = GetParam();
    poly_sub_test(p.degree, p.modulus);
}

// Register the parameter sets
INSTANTIATE_TEST_SUITE_P(
    PolyMulTest,
    PolyMul,
    ::testing::Values(
        TestParam{2048, 4294955009},
        TestParam{4096, 281474976694273},
        TestParam{4096, 35184371884033}
    )
);
 

class Division : public ::testing::TestWithParam<TestParam> {
};

TEST_P(Division, DivisionTest) {
    TestParam p = GetParam();
    poly_sub_test(p.degree, p.modulus);
}

// Register the parameter sets
INSTANTIATE_TEST_SUITE_P(
    DivisionTest,
    Division,
    ::testing::Values(
        TestParam{2048, 4294955009},
        TestParam{4096, 281474976694273},
        TestParam{4096, 35184371884033}
    )
);



class CMPNaiveWithNTL : public ::testing::TestWithParam<TestParam> {
};

TEST_P(CMPNaiveWithNTL, CMPNaiveWithNTLTest) {
    TestParam p = GetParam();
    poly_sub_test(p.degree, p.modulus);
}

// Register the parameter sets
INSTANTIATE_TEST_SUITE_P(
    CMPNaiveWithNTLTest,
    CMPNaiveWithNTL,
    ::testing::Values(
        TestParam{2048, 4294955009},
        TestParam{4096, 281474976694273},
        TestParam{4096, 35184371884033}
    )
);


#endif

 