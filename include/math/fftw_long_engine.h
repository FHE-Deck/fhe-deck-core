#ifndef FFTW_LONG_ENGINE_H
#define FFTW_LONG_ENGINE_H

/**
 * @file fftw_long_engine.h
 */

#include "math/polynomial.h"
//#include "fft_plan.h"
#include <fftw3.h>

namespace fhe_deck{



/**
 * @brief This class is a wrapper around the FFTW library. It is used to compute the FFT of a polynomial in the ring Z[X]/(X^N+1) or Z[X]/(X^N-1)
 */
class FFTLongPlan{

    public:
    
    // Ring type is either cyclic or negacyclic
    RingType ring;
    // N is the number of coefficients
    uint32_t N; 
    // Plan size is the size of the plan e.g. 2N for (X^N+1) and N for (X^N-1) 
    uint32_t plan_size; 
    
    bool is_init = false;

    // Long Arithmetic Related
    fftwl_plan plan_to_eval_form_l, plan_to_coef_form_l;
    long double *in_l;
    fftwl_complex *out_l;
    bool long_arithmetic = false;
 
    FFTLongPlan() = default;

    FFTLongPlan(RingType ring, int32_t N);

    FFTLongPlan(RingType ring, int32_t N, bool long_arithmetic);

    FFTLongPlan(const FFTLongPlan& other);

    FFTLongPlan& operator=(FFTLongPlan other);

    ~FFTLongPlan();
  
    fftwl_complex* init_fft_poly_l();
  
    // Long arithmetic 

    // Note that we still only support operations on polynomials with 64-bit coefs max. 
    void to_eval_form_l(fftwl_complex* eval_form, int64_t *poly); 

    void to_eval_form_l(fftwl_complex* eval_form, int32_t *poly);
   
    void to_eval_form_scale_l(fftwl_complex* eval_form, int64_t *poly);

     // It divides the coefficients by (plan_size * additional_scale) before computing the FFT
    void to_eval_form_scale_l(fftwl_complex* eval_form, int64_t *poly, long double additional_scale);
   
    void to_coef_form_l(int64_t *coef_form, fftwl_complex* eval_form);

    void to_coef_form_l(long double *coef_form, fftwl_complex* eval_form);
    
    void to_coef_form_scale_l(int64_t *coef_form, fftwl_complex* eval_form, long double scale);

    void to_coef_form_scale_l(long double *coef_form, fftwl_complex* eval_form, long double scale);
 
    void add_eval_form_l(fftwl_complex *sum, fftwl_complex* in_1, fftwl_complex* in_2);

    void mul_eval_form_l(fftwl_complex *prod, fftwl_complex* in_1, fftwl_complex* in_2);

    private:

    void init_tables();


};


 
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