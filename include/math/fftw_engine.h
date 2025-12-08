#ifndef FFTW_ENGINES_H
#define FFTW_ENGINES_H

/**
 * @file fftw_engine.h
 */
#include "global_headers.h"
 
#include "fftw3.h"
#include "math/polynomial.h" 

namespace FHEDeck{
    
/**
 * @brief This class is a wrapper around the FFTW library. It is used to compute the FFT of a polynomial in the ring Z[X]/(X^N+1) or Z[X]/(X^N-1)
 */
class FFTPlan{

    protected: 
    
    // Ring type is either cyclic or negacyclic
    RingType m_ring;
    // N is the number of coefficients
    uint32_t m_N; 
    // Plan size is the size of the plan e.g. 2N for (X^N+1) and N for (X^N-1) 
    uint32_t m_plan_size;
    double *m_in;
    fftw_complex *m_out;
    fftw_plan m_plan_to_eval_form, m_plan_to_coef_form;

    public:
    
    FFTPlan() = default;

    FFTPlan(RingType ring, int32_t N);

    FFTPlan(const FFTPlan& other) = delete;

    FFTPlan& operator=(FFTPlan other) = delete;

    ~FFTPlan();

    fftw_complex* init_fft_poly();
 
    void to_eval_form(fftw_complex* eval_form, int64_t *poly); 

    void to_eval_form(fftw_complex* eval_form, int32_t *poly);
    
    // It divides the coefficients by (plan_size * additional_scale) before computing the FFT
    void to_eval_form_scale(fftw_complex* eval_form, int64_t *poly, double additional_scale);
 
    void to_coef_form(int64_t *coef_form, fftw_complex* eval_form);

    void to_coef_form(double *coef_form, fftw_complex* eval_form);

    void to_coef_form_scale(int64_t *coef_form, fftw_complex* eval_form, double scale);

    void to_coef_form_scale(double *coef_form, fftw_complex* eval_form, double scale);
 
    void add_eval_form(fftw_complex *sum, fftw_complex* in_1, fftw_complex* in_2);

    void mul_eval_form(fftw_complex *prod, fftw_complex* in_1, fftw_complex* in_2);

    private:

    void init_tables();
 
};


  
/**
 * @brief Implementation of PolynomialMultiplicationEngine using Intel Hexl NTT. Its evaluation from is PolynomialEvalFormFFTWComplex
 */
class FFTWNegacyclicEngine : public PolynomialMultiplicationEngine{

    protected: 

    std::unique_ptr<FFTPlan> m_engine;  
    int32_t m_degree;
    int64_t m_coef_modulus;

    public:
 

    FFTWNegacyclicEngine(int32_t degree, int64_t coef_modulus); 
    
    std::shared_ptr<PolynomialEvalForm> init_polynomial_eval_form(); 

    std::shared_ptr<PolynomialArrayEvalForm> init_polynomial_array_eval_form(int32_t array_size);

    void to_eval(PolynomialEvalForm &out, const Polynomial &in);
    
    void to_eval(PolynomialArrayEvalForm &out, const PolynomialArray &in);

    void to_coef(Polynomial &out, const PolynomialEvalForm &in);
 
    void to_coef(PolynomialArray &out, const PolynomialArrayEvalForm &in);
  
    void mul(PolynomialEvalForm &out, const PolynomialEvalForm &in_1, const PolynomialEvalForm &in_2);

    void multisum(Polynomial &out, const PolynomialArray &in_1, const PolynomialArrayEvalForm &in_2);

    void multisum(Polynomial &out, const PolynomialArrayEvalForm &in_1, const PolynomialArrayEvalForm &in_2);
 
    void multisum(Polynomial &out_multisum, PolynomialArrayEvalForm &out_in_1_eval, const PolynomialArray &in_1, const PolynomialArrayEvalForm &in_2);
};
 
} /// End of namespace FHEDeck

#endif 
