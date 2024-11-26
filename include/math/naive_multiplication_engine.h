#ifndef NAIVE_MULTIPLICATION_ENGINE_H
#define NAIVE_MULTIPLICATION_ENGINE_H
  
/**
 * @file naive_multiplication_engine.h
 */

#include "math/polynomial.h"

namespace fhe_deck{
/**
 * @brief Implementation of PolynomialMultiplicationEngine. The multiplication is naive. 
 */
class NaiveNegacyclicMultiplicationEngine : public PolynomialMultiplicationEngine{

    public:
  
    
    int32_t degree;
    int64_t coef_modulus;

    NaiveNegacyclicMultiplicationEngine(int32_t degree, int64_t coef_modulus); 
    
    std::shared_ptr<PolynomialEvalForm> init_polynomial_eval_form(); 

    std::shared_ptr<PolynomialArrayEvalForm> init_polynomial_array_eval_form(int32_t array_size);

    void to_eval(PolynomialEvalForm &out, const Polynomial &in);
    
    void to_eval(PolynomialArrayEvalForm &out, const PolynomialArrayCoefForm &in);

    void to_coef(Polynomial &out, const PolynomialEvalForm &in);
 
    void to_coef(PolynomialArrayCoefForm &out, const PolynomialArrayEvalForm &in);
  
    void mul(PolynomialEvalForm &out, const PolynomialEvalForm &in_1, const PolynomialEvalForm &in_2);

    void multisum(Polynomial &out, const PolynomialArrayCoefForm &in_1, const PolynomialArrayEvalForm &in_2);

    void multisum(Polynomial &out, const PolynomialArrayEvalForm &in_1, const PolynomialArrayEvalForm &in_2);
 
    void multisum(Polynomial &out_multisum, PolynomialArrayEvalForm &out_in_1_eval, const PolynomialArrayCoefForm &in_1, const PolynomialArrayEvalForm &in_2);

    private:

    void mul(int64_t* out, int64_t* in_1, int64_t* in_2);
};

}/// End of namespace fhe_deck


#endif