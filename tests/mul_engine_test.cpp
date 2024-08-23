#include "polynomial.h"
#include "polynomial_multiplication_engine_builder.h"
#include "intel_hexl_engine.h"
#include "fftw_engines.h"

using namespace fhe_deck; 

void mul_test(int32_t tests,std::shared_ptr<PolynomialMultiplicationEngine> engine_left, std::shared_ptr<PolynomialMultiplicationEngine> engine_right, int32_t degree, int64_t modulus, int64_t bound){

    std::shared_ptr<Distribution> rand_uni = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, degree));
    std::shared_ptr<Distribution> rand_bound = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, bound));
 
    bool test_eval_equal = true;
    for(int32_t i = 0; i < tests; ++i){
        Polynomial input_poly(degree, modulus);
        rand_uni->fill_array(input_poly.coefs, degree);
 
        std::shared_ptr<PolynomialEvalForm> left_eval(engine_left->init_polynomial_eval_form());
        std::shared_ptr<PolynomialEvalForm> right_eval(engine_right->init_polynomial_eval_form());

        engine_left->to_eval(left_eval.get(), &input_poly);
        engine_right->to_eval(right_eval.get(), &input_poly);
        
        Polynomial left_poly(degree, modulus);
        Polynomial right_poly(degree, modulus);
        engine_left->to_coef(&left_poly, left_eval.get());
        engine_right->to_coef(&right_poly, right_eval.get());

        if(!Utils::is_eq_poly(left_poly.coefs, right_poly.coefs, degree)){
            test_eval_equal = false;
            std::cout << "Test Eval Equivalence: Fail at " << i << std::endl;
            std::cout << "input_poly.coefs: " << Utils::to_string(input_poly.coefs, 5) << std::endl;
            std::cout << "left_poly.coefs: " << Utils::to_string(left_poly.coefs, 5) << std::endl;
            std::cout << "right_poly.coefs: " << Utils::to_string(right_poly.coefs, 5) << std::endl;
            break;
        }
    }
    if(test_eval_equal){
        std::cout << "Test Eval Equivalence: OK" << std::endl;
    }else{
        std::cout << "Test Eval Equivalence: False" << std::endl;
    }
 

    bool test_eval_equal_array = true;
    int32_t array_size = 10;
    std::shared_ptr<PolynomialArrayEvalForm> left_eval_array(engine_left->init_polynomial_array_eval_form(array_size));
    std::shared_ptr<PolynomialArrayEvalForm> right_eval_array(engine_right->init_polynomial_array_eval_form(array_size));
    for(int32_t i = 0; i < tests; ++i){
        PolynomialArrayCoefForm input_array(degree, modulus, array_size);
        rand_uni->fill_array(input_array.poly_array, input_array.full_size);

        engine_left->to_eval(left_eval_array.get(), &input_array);
        engine_right->to_eval(right_eval_array.get(), &input_array);
        
        PolynomialArrayCoefForm left_poly_array(degree, modulus, array_size);
        PolynomialArrayCoefForm right_poly_array(degree, modulus, array_size);
        engine_left->to_coef(&left_poly_array, left_eval_array.get());
        engine_right->to_coef(&right_poly_array, right_eval_array.get());

        if(left_poly_array.full_size != right_poly_array.full_size){
            test_eval_equal_array = false;
            break;
        } 
        if(!Utils::is_eq_poly(left_poly_array.poly_array, right_poly_array.poly_array, left_poly_array.full_size)){
            test_eval_equal_array = false;
            std::cout << "input_array.poly_array: " << Utils::to_string(input_array.poly_array, 5) << std::endl;
            std::cout << "left_poly_array.poly_array: " << Utils::to_string(left_poly_array.poly_array, 5) << std::endl;
            std::cout << "right_poly_array.poly_array: " << Utils::to_string(right_poly_array.poly_array, 5) << std::endl;
            break;
        }
    }
    if(test_eval_equal_array){
        std::cout << "Test Eval Array Form Equivalence: OK" << std::endl;
    }else{
        std::cout << "Test Eval Array Form Equivalence: False" << std::endl;
    }

 
    /// TODO: Multiplication Test (multiply two polynomials twice, and check if the output is the same)
    bool test_mul = true;
    for(int32_t i = 0; i < tests; ++i){
        Polynomial poly_1(degree, modulus);
        Polynomial poly_2(degree, modulus);
        rand_uni->fill_array(poly_1.coefs, degree);
        rand_bound->fill_array(poly_2.coefs, degree);


        std::shared_ptr<PolynomialEvalForm> left_eval_1(engine_left->init_polynomial_eval_form());
        std::shared_ptr<PolynomialEvalForm> left_eval_2(engine_left->init_polynomial_eval_form());
        std::shared_ptr<PolynomialEvalForm> left_eval_out(engine_left->init_polynomial_eval_form());
        std::shared_ptr<PolynomialEvalForm> right_eval_1(engine_right->init_polynomial_eval_form());
        std::shared_ptr<PolynomialEvalForm> right_eval_2(engine_right->init_polynomial_eval_form());
        std::shared_ptr<PolynomialEvalForm> right_eval_out(engine_right->init_polynomial_eval_form());

        engine_left->to_eval(left_eval_1.get(), &poly_1);
        engine_left->to_eval(left_eval_2.get(), &poly_2);
        engine_right->to_eval(right_eval_1.get(), &poly_1);
        engine_right->to_eval(right_eval_2.get(), &poly_2);

        engine_left->mul(left_eval_out.get(), left_eval_1.get(), left_eval_2.get());
        engine_right->mul(right_eval_out.get(), right_eval_1.get(), right_eval_2.get());
        
        Polynomial left_poly(degree, modulus);
        Polynomial right_poly(degree, modulus);
        engine_left->to_coef(&left_poly, left_eval_out.get());
        engine_right->to_coef(&right_poly, right_eval_out.get());

        if(!Utils::is_eq_poly(left_poly.coefs, right_poly.coefs, degree)){
            test_mul = false; 
            std::cout << "left_poly.coefs: " << Utils::to_string(left_poly.coefs, 5) << std::endl;
            std::cout << "right_poly.coefs: " << Utils::to_string(right_poly.coefs, 5) << std::endl;
            break;
        }
    }
    if(test_mul){
        std::cout << "Test Multiplication Test: OK" << std::endl;
    }else{
        std::cout << "Test Multiplication Test: False" << std::endl;
    }

    /// TODO: Multisum 1 test: Precompute one array to eval form, and compute the multisum with a PolynomialArrayCoefForm

    array_size = 10;
    bool test_multisum = true;
    for(int32_t i = 0; i < tests; ++i){
        PolynomialArrayCoefForm poly_array_1(degree, modulus, array_size);
        PolynomialArrayCoefForm poly_array_2(degree, modulus, array_size);
        rand_uni->fill_array(poly_array_1.poly_array, poly_array_1.full_size);
        rand_bound->fill_array(poly_array_2.poly_array, poly_array_2.full_size);

        std::shared_ptr<PolynomialArrayEvalForm> left_eval_1(engine_left->init_polynomial_array_eval_form(array_size));
        std::shared_ptr<PolynomialArrayEvalForm> left_eval_2(engine_left->init_polynomial_array_eval_form(array_size));
        std::shared_ptr<PolynomialArrayEvalForm> right_eval_1(engine_right->init_polynomial_array_eval_form(array_size));
        std::shared_ptr<PolynomialArrayEvalForm> right_eval_2(engine_right->init_polynomial_array_eval_form(array_size));
 

        engine_left->to_eval(left_eval_1.get(), &poly_array_1);
        engine_left->to_eval(left_eval_2.get(), &poly_array_2);
        engine_right->to_eval(right_eval_1.get(), &poly_array_1);
        engine_right->to_eval(right_eval_2.get(), &poly_array_2);

        Polynomial left_out(degree, modulus);
        Polynomial right_out(degree, modulus);

        engine_left->multisum(&left_out, left_eval_1.get(), left_eval_2.get());
        engine_right->multisum(&right_out, right_eval_1.get(), right_eval_2.get());
          
        if(!Utils::is_eq_poly(left_out.coefs, right_out.coefs, degree)){
            test_multisum = false;
            std::cout << "left_out.coefs: " << Utils::to_string(left_out.coefs, 5) << std::endl;
            std::cout << "right_out.coefs: " << Utils::to_string(right_out.coefs, 5) << std::endl;
            break;
        }
    }
    if(test_multisum){
        std::cout << "Test Multisum 1: OK" << std::endl;
    }else{
        std::cout << "Test Multisum 1: False" << std::endl;
    }
 
    /// TODO: Multisum 2 test: Precompute one array to eval form, and compute the multisum that return the PolynomialArrayEvalForm
    /// In the same test, use the PolynomialArrayEvalForm from the previous and compute another multisum that takes all eval form as input. 
 
    array_size = 10;
    bool test_multisum_2 = true;
    bool test_eval_2 = true;
    for(int32_t i = 0; i < tests; ++i){
        PolynomialArrayCoefForm poly_array_1(degree, modulus, array_size);
        PolynomialArrayCoefForm poly_array_2(degree, modulus, array_size);
        rand_uni->fill_array(poly_array_1.poly_array, poly_array_1.full_size);
        rand_bound->fill_array(poly_array_2.poly_array, poly_array_2.full_size);

        std::shared_ptr<PolynomialArrayEvalForm> left_eval_1(engine_left->init_polynomial_array_eval_form(array_size));
        std::shared_ptr<PolynomialArrayEvalForm> left_eval_2(engine_left->init_polynomial_array_eval_form(array_size));
        std::shared_ptr<PolynomialArrayEvalForm> right_eval_1(engine_right->init_polynomial_array_eval_form(array_size));
        std::shared_ptr<PolynomialArrayEvalForm> right_eval_2(engine_right->init_polynomial_array_eval_form(array_size));
 
 
        engine_left->to_eval(left_eval_2.get(), &poly_array_2); 
        engine_right->to_eval(right_eval_2.get(), &poly_array_2);

        Polynomial left_out(degree, modulus);
        Polynomial right_out(degree, modulus);

        engine_left->multisum(&left_out, left_eval_1.get(), &poly_array_1, left_eval_2.get());
        engine_right->multisum(&right_out, right_eval_1.get(), &poly_array_1, right_eval_2.get());
          
        if(!Utils::is_eq_poly(left_out.coefs, right_out.coefs, degree)){
            test_multisum_2 = false;
            std::cout << "left_out.coefs: " << Utils::to_string(left_out.coefs, 5) << std::endl;
            std::cout << "right_out.coefs: " << Utils::to_string(right_out.coefs, 5) << std::endl;
            break;
        }
 
        PolynomialArrayCoefForm poly_array_1_left(degree, modulus, array_size);
        PolynomialArrayCoefForm poly_array_1_right(degree, modulus, array_size);
        engine_left->to_coef(&poly_array_1_left, left_eval_1.get());
        engine_right->to_coef(&poly_array_1_right, right_eval_1.get());
        if(!Utils::is_eq_poly(poly_array_1_left.poly_array, poly_array_1_right.poly_array, poly_array_1_left.full_size)){
            test_eval_2 = false;
            break;
        } 
    }
    if(test_multisum_2){
        std::cout << "Test Multisum 2: OK" << std::endl;
    }else{
        std::cout << "Test Multisum 2: False" << std::endl;
    }
    if(test_eval_2){
        std::cout << "Test Eval Equivalence 2: OK" << std::endl;
    }else{
        std::cout << "Test Eval Equivalence 2: False" << std::endl;
    }

}



int main() { 
 
    int32_t degree = 2048;
    int64_t modulus = 4294955009l;
    std::shared_ptr<IntelHexlNTTEngine> ntt_engine = std::make_shared<IntelHexlNTTEngine>(degree, modulus);  
    std::shared_ptr<FFTWNegacyclicEngine> fft_engine = std::make_shared<FFTWNegacyclicEngine>(degree, modulus);   
    std::shared_ptr<PolynomialMultiplicationEngine> engine_left = std::static_pointer_cast<PolynomialMultiplicationEngine>(ntt_engine);
    std::shared_ptr<PolynomialMultiplicationEngine> engine_right = std::static_pointer_cast<PolynomialMultiplicationEngine>(fft_engine);
    mul_test(10, engine_left, engine_right, 2048, 4294955009, 2048);
  
    return 0;
}
