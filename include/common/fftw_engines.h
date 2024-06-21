#ifndef FFTW_ENGINES_H
#define FFTW_ENGINES_H

#include "polynomial.h"

namespace fhe_deck{
 

 

class FFTWNegacyclicEngine : public PolynomialMultiplicationEngine{

    public:
 
    FFTPlan engine; 

    int32_t degree;
    int64_t coef_modulus;

    FFTWNegacyclicEngine(int32_t degree, int64_t coef_modulus); 
    
    PolynomialEvalForm* init_polynomial_eval_form(); 

    PolynomialArrayEvalForm* init_polynomial_array_eval_form(int32_t array_size);

    void to_eval(PolynomialEvalForm *out, Polynomial *in);
    
    void to_eval(PolynomialArrayEvalForm *out, PolynomialArrayCoefForm *in);

    void to_coef(Polynomial *out, PolynomialEvalForm *in);
 
    void to_coef(PolynomialArrayCoefForm *out, PolynomialArrayEvalForm *in);
  
    void mul(PolynomialEvalForm *out, PolynomialEvalForm *in_1, PolynomialEvalForm *in_2);

    void multisum(Polynomial *out, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2);

    void multisum(Polynomial *out, PolynomialArrayEvalForm *in_1, PolynomialArrayEvalForm *in_2);
 
    void multisum(Polynomial *out_multisum, PolynomialArrayEvalForm *out_in_1_eval, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2);
};



class FFTWLongNegacyclicEngine : public PolynomialMultiplicationEngine{

    public:
 
    FFTPlan engine; 

    int32_t degree;
    int64_t coef_modulus;

    FFTWLongNegacyclicEngine(int32_t degree, int64_t coef_modulus); 
  
    PolynomialEvalForm* init_polynomial_eval_form();

    PolynomialArrayEvalForm* init_polynomial_array_eval_form(int32_t array_size);
 
    void to_eval(PolynomialEvalForm *out, Polynomial *in);
 
    void to_eval(PolynomialArrayEvalForm *out, PolynomialArrayCoefForm *in);

    void to_coef(Polynomial *out, PolynomialEvalForm *in);
  
    void to_coef(PolynomialArrayCoefForm *out, PolynomialArrayEvalForm *in);
  
    void mul(PolynomialEvalForm *out, PolynomialEvalForm *in_1, PolynomialEvalForm *in_2);
 
    void multisum(Polynomial *out, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2);

    void multisum(Polynomial *out, PolynomialArrayEvalForm *in_1, PolynomialArrayEvalForm *in_2);

    void multisum(Polynomial *out_multisum, PolynomialArrayEvalForm *out_in_1_eval, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2);

};
 

}

#endif 
