 
#ifndef FFT_PLAN_H
#define FFT_PLAN_H

#include <fftw3.h>
#include <random>
#include "../include/enums.h"


class fft_plan{

    public:
    
    // Ring type is either cyclic or negacyclic
    ring_type ring;
    // N is the number of coefficients
    int N; 
    // Plan size is the size of the plan e.g. 2N for (X^N+1) and N for (X^N-1) 
    int plan_size;
    double *in;
    fftw_complex *out;
    fftw_plan plan_to_eval_form, plan_to_coef_form;
    
    bool is_init = false;

    // Long Arithmetic Related
    fftwl_plan plan_to_eval_form_l, plan_to_coef_form_l;
    long double *in_l;
    fftwl_complex *out_l;
    bool long_arithmetic = false;
 
    fft_plan() = default;

    fft_plan(ring_type ring, int N);

    fft_plan(ring_type ring, int N, bool long_arithmetic);

    fft_plan(const fft_plan& other);

    fft_plan& operator=(const fft_plan other);

    ~fft_plan();
 
    void to_eval_form(fftw_complex* eval_form, long *poly); 

    void to_eval_form(fftw_complex* eval_form, int *poly);
   
    // It divides the coefficients by plan_size before computing the FFT
    void to_eval_form_scale(fftw_complex* eval_form, long *poly);

    // It divides the coefficients by (plan_size * additional_scale) before computing the FFT
    void to_eval_form_scale(fftw_complex* eval_form, long *poly, double additional_scale);
 
    void to_coef_form(long *coef_form, fftw_complex* eval_form);

    void to_coef_form(double *coef_form, fftw_complex* eval_form);
 
    void add_eval_form(fftw_complex *sum, fftw_complex* in_1, fftw_complex* in_2);

    void mul_eval_form(fftw_complex *prod, fftw_complex* in_1, fftw_complex* in_2);


    // Long arithmetic


    // Note that we still only support operations on polynomials with 64-bit coefs max. 
    void to_eval_form_l(fftwl_complex* eval_form, long *poly); 

    void to_eval_form_l(fftwl_complex* eval_form, int *poly);
   
    void to_eval_form_scale_l(fftwl_complex* eval_form, long *poly);

     // It divides the coefficients by (plan_size * additional_scale) before computing the FFT
    void to_eval_form_scale_l(fftwl_complex* eval_form, long *poly, double additional_scale);
 
    // To coefficient form where we return a 64-bit long makes only sense if the output polynomial is in 64-bits.
    // However, without modular reduction we cannot guarantee that the outcome (for example for multiplication of two polynomails) will not lie outside 64-bits
    //void to_coef_form(long *coef_form, fftw_complex* eval_form);

    void to_coef_form_l(long *coef_form, fftwl_complex* eval_form);
 
    void add_eval_form_l(fftwl_complex *sum, fftwl_complex* in_1, fftwl_complex* in_2);

    void mul_eval_form_l(fftwl_complex *prod, fftwl_complex* in_1, fftwl_complex* in_2);
 

    private:

    void init_tables();


};

#endif