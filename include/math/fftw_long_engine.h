#ifndef FFTW_LONG_ENGINE_H
#define FFTW_LONG_ENGINE_H

/**
 * @file fftw_long_engine.h
 */

#include "math/polynomial.h"
#include "fft_plan.h"

namespace fhe_deck{
 
class FFTWLongNegacyclicEngine : public PolynomialMultiplicationEngine{

    public:
 
    FFTLongPlan engine; 

    int32_t degree;
    int64_t coef_modulus;

    FFTWLongNegacyclicEngine(int32_t degree, int64_t coef_modulus); 
  
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

};
 

}

#endif 