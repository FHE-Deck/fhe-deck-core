 
#include <iostream>
#include <complex>
#include <fftw3.h>
#include <chrono>
#include "../include/utils.h"
#include "../include/sample.h"
#include "../include/fft_plan.h"
#include "../include/enums.h"



void mult_test(){

    int tests = 10000; 
    long sample_modulus = 1073741824;
    fftw_complex* fftw_c_1 = new fftw_complex[tests];
    std::complex<double> std_c_1[tests];
    sampler sam;
    for(int i = 0; i < tests; ++i){
        fftw_c_1[i][0] = sam.uniform(sample_modulus);
        fftw_c_1[i][1] = sam.uniform(sample_modulus);
        std_c_1[i].real(fftw_c_1[i][0]);
        std_c_1[i].imag(fftw_c_1[i][1]);
    }
    fftw_complex* fftw_c_2 = new fftw_complex[tests];
    std::complex<double> std_c_2[tests];
    for(int i = 0; i < tests; ++i){
        fftw_c_2[i][0] = sam.uniform(sample_modulus);
        fftw_c_2[i][1] = sam.uniform(sample_modulus);
        std_c_2[i].real(fftw_c_2[i][0]);
        std_c_2[i].imag(fftw_c_2[i][1]);
    }
    fftw_complex* fftw_c_out = new fftw_complex[tests];
    fft_plan plan(cyclic, tests/2);
    std::chrono::high_resolution_clock::time_point start, end; 

    std::cout << "plan_size: " << plan.plan_size << std::endl;
    start = std::chrono::high_resolution_clock::now();  
    plan.mul_eval_form(fftw_c_out, fftw_c_1, fftw_c_2);
    end = std::chrono::high_resolution_clock::now(); 
    std::cout << "fft_w_complex mul time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;
    
     std::complex<double> std_c_out[tests];
    start = std::chrono::high_resolution_clock::now(); 
    for(int i = 0; i < tests; ++i){ 
        std_c_out[i] = std_c_1[i] * std_c_2[i];
    }
    end = std::chrono::high_resolution_clock::now(); 
    std::cout << "std::complex<double> mul time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;
 
}



void int_vs_auto_test(){

    int tests = 1000; 
    // 2**30
    long modulus = 1073741824;
    long mask = modulus -1;
    long sample_modulus = modulus * 65536; 
    sampler sam;
    long a[tests];
    long b[tests];
    long c[tests];
    for(int i = 0; i < tests; ++i){
        a[i] = sam.uniform(sample_modulus);
        b[tests] = sam.uniform(sample_modulus);
    }

    std::chrono::high_resolution_clock::time_point start, end; 

    
    start = std::chrono::high_resolution_clock::now(); 
    for(auto i = 0; i < tests; ++i){
        c[i] = b[i] % modulus;
    }
    end = std::chrono::high_resolution_clock::now(); 
    std::cout << "auto time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;

    start = std::chrono::high_resolution_clock::now(); 
    for(int i = 0; i < tests; ++i){
        c[i] = a[i] % modulus;
    }
    end = std::chrono::high_resolution_clock::now(); 
    std::cout << "int time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;
 
}


void int_vs_vector_test(){

    int tests = 33554432; 
    // 2**50
    long modulus = 1073741824;
    long mask = modulus -1;
    long sample_modulus = modulus * 65536; 
    sampler sam;

    std::chrono::high_resolution_clock::time_point start, end; 

    start = std::chrono::high_resolution_clock::now(); 
    long a[tests];
    for(int i = 0; i < tests; ++i){
        a[i] = 0;
    }
    end = std::chrono::high_resolution_clock::now(); 
    std::cout << "Initialize null table time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;

    start = std::chrono::high_resolution_clock::now(); 
    std::vector<long> b(tests, 0);
    end = std::chrono::high_resolution_clock::now(); 
    std::cout << "Initialize null vector time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;


    long c[tests];
    for(int i = 0; i < tests; ++i){
        a[i] = sam.uniform(sample_modulus);
        b[tests] = sam.uniform(sample_modulus);
    }

    start = std::chrono::high_resolution_clock::now(); 
    for(int i = 0; i < tests; ++i){
        c[i] = a[i] % modulus;
    }
    end = std::chrono::high_resolution_clock::now(); 
    std::cout << "Iterate the table time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;
    
    std::vector<long> c_vec(tests, 0);
    start = std::chrono::high_resolution_clock::now(); 
    for(std::vector<long>::iterator it = b.begin(); it != b.end(); ++it){
        (*it) %= modulus;
    }
    end = std::chrono::high_resolution_clock::now(); 
    std::cout << "Iterate the vector time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;
 
}



void mod_reduction_test(){

    int tests = 100000; 
    // 2**30
    //long modulus = 1125899906842624;
    long modulus = 65536;
    long mask = modulus -1;
    long sample_modulus = modulus * 65536; 
    sampler sam;
    long a[tests];
    long b[tests];
    long c[tests];
    for(int i = 0; i < tests; ++i){
        a[i] = sam.uniform(sample_modulus);
        b[i] = sam.uniform(sample_modulus); 
    }
 
    std::chrono::high_resolution_clock::time_point start, end; 
 
    start = std::chrono::high_resolution_clock::now(); 
    for(int i = 0; i < tests; ++i){
        c[i] = b[i] & mask;
    }
    end = std::chrono::high_resolution_clock::now(); 
    std::cout << "Using mask time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;
 
    start = std::chrono::high_resolution_clock::now(); 
    for(int i = 0; i < tests; ++i){
        c[i] = a[i] % modulus;
    }
    end = std::chrono::high_resolution_clock::now(); 
    std::cout << "Using modulo time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;
  
}


void fft_mul_test(){

   int N = 5;
   long Q = 1073741827;   
   long *psi = new long[N+1];
   psi[0] = Q-1; 
   psi[N] = 1;
   for(int i=1; i < N; ++i){
      psi[i] = 0;
   } 
   double stddev = 3.2;
   sampler rand;
   NTL::ZZ_pX psi_poly;
   utils::set_polynomial_from_array(psi_poly, psi, N+1, Q); 
   ntru_param param(cyclic, N, Q, any, stddev); 
 
    long poly_1[N] = {1, 0, 1, 0, 1};
    long poly_2[N] = {0, 1, 0, 0, 0};

    long *prod = new long[N];
    utils::mul_mod(prod, poly_1, N, poly_2, N, param.N, param.Q, param.ring);
    std::cout << "prod: " << utils::to_string(prod, N) << std::endl;


    // Set up FFT stuff.
    double *in;
    fftw_complex *out;
    fftw_plan plan_to_eval_form, plan_to_coef_form;
    in = (double*) fftw_malloc(sizeof(double) * 2 * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 2 * N);
    plan_to_eval_form = fftw_plan_dft_r2c_1d(2*N, in, out,  FFTW_PATIENT);
    plan_to_coef_form = fftw_plan_dft_c2r_1d(2*N, out, in,  FFTW_PATIENT);

    // Setting poly_1 data to the fft engine
    for(int i = 0; i < N; ++i){
        in[i] = (double)poly_1[i];
        in[i+N] = 0.0;
    }
    
    // Compute FFT of poly_1
    fftw_execute(plan_to_eval_form);  
    fftw_complex *poly_1_eval = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 2 * N); 
    for(int i = 0; i < 2*N; ++i){ 
        poly_1_eval[i][0] = out[i][0];
        poly_1_eval[i][1] = out[i][1];
    } 
    // Setting poly_2 data to the fft engine
    // Note that I divide it by 2*N
    // The reason is, that it seem the inverse FFT doesn't take 1/2N - so I do it here. 
    double divisor = (double)2*N;
    for(int i = 0; i < N; ++i){
        in[i] = (double)poly_2[i]/ divisor;
        in[i+N] = 0.0;
    }
    // Compute FFT of poly_2
    fftw_execute(plan_to_eval_form);  
    fftw_complex *poly_2_eval = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 2 * N); 
    for(int i = 0; i < 2*N; ++i){ 
        poly_2_eval[i][0] = out[i][0];
        poly_2_eval[i][1] = out[i][1];
    } 
      
    // Multiply the vectors (Note that its complex multiplication)
    for(int i = 0; i < 2*N; ++i){
        out[i][0] = poly_1_eval[i][0] * poly_2_eval[i][0] - poly_1_eval[i][1] * poly_2_eval[i][1];
        out[i][1] = poly_1_eval[i][0] * poly_2_eval[i][1] + poly_1_eval[i][1] * poly_2_eval[i][0];
    } 
    // Compute inverse FFT 
    fftw_execute(plan_to_coef_form); 
    double *coef_prod = new double[2 * N];
    long *coef_prod_rounded = new long[2 * N];
    for(int i = 0; i < 2*N; ++i){
        coef_prod[i] = in[i];
        //std::cout << "in[" <<i << "]: " << in[i] << std::endl;
        // round to long
        coef_prod_rounded[i] = (long)round(in[i]);
    } 
    std::cout << "coef_prod_rounded: " << utils::to_string(coef_prod_rounded, 2*N) << std::endl;
    long *result = new long[N];
    for(int i = 0; i < N; ++i){
         result[i] = coef_prod_rounded[i];
         // We also compute the cyclic convolution at this point.
         result[i] += coef_prod_rounded[i+N];
    } 
    
    // The result should be the same as prod.
    if(utils::is_eq_poly(result, prod, N)){
        std::cout << "FFT Polynomials Multiplication Test: OK" << std::endl;
    }else{
        std::cout << "FFT Polynomials Multiplication Test: Fail" << std::endl;
    }

}


void fft_random_mul_test(){
    std::cout << "================= fft_random_mul_test =================" << std::endl;
   int N = 5;
   // This is approx 31 bits prime
   // long Q = 1073741827;  
   // Here we have around 20 bits prime
   //long Q = 1048583; 
   // Here we have a very small prime
   long Q = 7919;
   long *psi = new long[N+1];
   psi[0] = Q-1; 
   psi[N] = 1;
   for(int i=1; i < N; ++i){
      psi[i] = 0;
   } 
   double stddev = 3.2;
   sampler rand;
   NTL::ZZ_pX psi_poly;
   utils::set_polynomial_from_array(psi_poly, psi, N+1, Q); 
   ntru_param param(cyclic, N, Q, any, stddev); 
 
    // Choose uniformly random polynomials
    long poly_1[N];
    long poly_2[N];
    rand.uniform_array(poly_1, N, Q);
    rand.uniform_array(poly_2, N, Q); 
    std::cout << "poly_1: " << utils::to_string(poly_1, N) << std::endl;
    std::cout << "poly_2: " << utils::to_string(poly_2, N) << std::endl;

    long *prod = new long[N];
    utils::mul_mod(prod, poly_1, N, poly_2, N, param.N, param.Q, param.ring);
    std::cout << "prod: " << utils::to_string(prod, N) << std::endl;
 
    // Set up FFT stuff.
    double *in;
    fftw_complex *out;
    fftw_plan plan_to_eval_form, plan_to_coef_form;
    in = (double*) fftw_malloc(sizeof(double) * 2 * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 2 * N);
    plan_to_eval_form = fftw_plan_dft_r2c_1d(2*N, in, out,  FFTW_PATIENT);
    plan_to_coef_form = fftw_plan_dft_c2r_1d(2*N, out, in,  FFTW_PATIENT);

    // Setting poly_1 data to the fft engine
    // Note that this is without scaling
    for(int i = 0; i < N; ++i){
        in[i] = (double)poly_1[i];
        in[i+N] = 0.0;
    }
    // Compute FFT of poly_1
    fftw_execute(plan_to_eval_form);  
    fftw_complex *poly_1_eval = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 2 * N); 
    for(int i = 0; i < 2*N; ++i){ 
        poly_1_eval[i][0] = out[i][0];
        poly_1_eval[i][1] = out[i][1];
    } 
    // Setting poly_2 data to the fft engine
    // Note that I divide it by 2*N
    // The reason is, that it seem the inverse FFT doesn't take 1/2N - so I do it here. 
    double divisor = (double)2*N;
    for(int i = 0; i < N; ++i){
        in[i] = (double)poly_2[i]/ divisor;
        in[i+N] = 0.0;
    }
    // Compute FFT of poly_2
    fftw_execute(plan_to_eval_form);  
    fftw_complex *poly_2_eval = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 2 * N); 
    for(int i = 0; i < 2*N; ++i){ 
        poly_2_eval[i][0] = out[i][0];
        poly_2_eval[i][1] = out[i][1];
    } 

    // Multiply the vectors (Note that its complex multiplication)
    for(int i = 0; i < 2*N; ++i){
        out[i][0] = poly_1_eval[i][0] * poly_2_eval[i][0] - poly_1_eval[i][1] * poly_2_eval[i][1];
        out[i][1] = poly_1_eval[i][0] * poly_2_eval[i][1] + poly_1_eval[i][1] * poly_2_eval[i][0];
    } 
    // Compute inverse FFT 
    fftw_execute(plan_to_coef_form); 
    double *coef_prod = new double[2 * N];
    long *coef_prod_rounded = new long[2 * N];
    for(int i = 0; i < 2*N; ++i){
        coef_prod[i] = in[i]; 
        // round to long
        coef_prod_rounded[i] = (long)round(in[i]); 
    } 
    std::cout << "coef_prod_rounded: " << utils::to_string(coef_prod_rounded, 2*N) << std::endl;
    long *result = new long[N];
    for(int i = 0; i < N; ++i){
         result[i] = coef_prod_rounded[i] % Q;
         // We also compute the cyclic convolution at this point.
         result[i] =  (result[i] + coef_prod_rounded[i+N]) % Q;
    } 
    
    // The result should be the same as prod.
    if(utils::is_eq_poly(result, prod, N)){
        std::cout << "FFT Polynomials Multiplication Test: OK" << std::endl;
    }else{
        std::cout << "FFT Polynomials Multiplication Test: Fail" << std::endl;
        std::cout << "prod: " << utils::to_string(prod, N) << std::endl;
        std::cout << "result: " << utils::to_string(result, N) << std::endl;
        long *diff = new long[N];
        for(int i =0; i < N; ++i){
            diff[i] = prod[i] - result[i];
        }
        std::cout << "diff: " << utils::to_string(diff, N) << std::endl;
    }

}





void fft_random_convolve_test(){
    std::cout << "================= fft_random_convolve_test =================" << std::endl;
   int N = 5;
   // This is approx 31 bits prime
   // long Q = 1073741827;  
   // Here we have around 20 bits prime
   //long Q = 1048583; 
   // Here we have a very small prime
   long Q = 7919;
   long *psi = new long[N+1];
   psi[0] = Q-1; 
   psi[N] = 1;
   for(int i=1; i < N; ++i){
      psi[i] = 0;
   } 
   double stddev = 3.2;
   sampler rand;
   NTL::ZZ_pX psi_poly;
   utils::set_polynomial_from_array(psi_poly, psi, N+1, Q); 
   ntru_param param(cyclic, N, Q, any, stddev); 
 
    // Choose uniformly random polynomials
    long poly_1[N];
    long poly_2[N];
    rand.uniform_array(poly_1, N, Q);
    rand.uniform_array(poly_2, N, Q); 
    std::cout << "poly_1: " << utils::to_string(poly_1, N) << std::endl;
    std::cout << "poly_2: " << utils::to_string(poly_2, N) << std::endl;

    long *prod = new long[N];
    utils::mul_mod(prod, poly_1, N, poly_2, N, param.N, param.Q, param.ring);
    std::cout << "prod: " << utils::to_string(prod, N) << std::endl;



    // Set up FFT stuff.
    double *in;
    fftw_complex *out;
    fftw_plan plan_to_eval_form, plan_to_coef_form;
    in = (double*) fftw_malloc(sizeof(double) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    plan_to_eval_form = fftw_plan_dft_r2c_1d(N, in, out,  FFTW_PATIENT);
    plan_to_coef_form = fftw_plan_dft_c2r_1d(N, out, in,  FFTW_PATIENT);

    // Setting poly_1 data to the fft engine
    // Note that this is without scaling
    for(int i = 0; i < N; ++i){
        in[i] = (double)poly_1[i]; 
    }
    // Compute FFT of poly_1
    fftw_execute(plan_to_eval_form);  
    fftw_complex *poly_1_eval = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N); 
    for(int i = 0; i < N; ++i){ 
        poly_1_eval[i][0] = out[i][0];
        poly_1_eval[i][1] = out[i][1];
    } 
    // Setting poly_2 data to the fft engine
    // Note that I divide it by N
    // The reason is, that it seem the inverse FFT doesn't take 1/N - so I do it here. 
    double divisor = (double) N;
    for(int i = 0; i < N; ++i){
        in[i] = (double)poly_2[i]/ divisor; 
    }
    // Compute FFT of poly_2
    fftw_execute(plan_to_eval_form);  
    fftw_complex *poly_2_eval = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N); 
    for(int i = 0; i <  N; ++i){ 
        poly_2_eval[i][0] = out[i][0];
        poly_2_eval[i][1] = out[i][1];
    } 

    // Multiply the vectors (Note that its complex multiplication)
    for(int i = 0; i < N; ++i){
        out[i][0] = poly_1_eval[i][0] * poly_2_eval[i][0] - poly_1_eval[i][1] * poly_2_eval[i][1];
        out[i][1] = poly_1_eval[i][0] * poly_2_eval[i][1] + poly_1_eval[i][1] * poly_2_eval[i][0];
    } 
    // Compute inverse FFT 
    fftw_execute(plan_to_coef_form); 
    double *coef_prod = new double[N];
    long *coef_prod_rounded = new long[N];
    for(int i = 0; i < N; ++i){
        coef_prod[i] = in[i]; 
        // round to long
        coef_prod_rounded[i] = (long)round(in[i]); 
    } 
    std::cout << "coef_prod_rounded: " << utils::to_string(coef_prod_rounded, N) << std::endl;
    long *result = new long[N];
    for(int i = 0; i < N; ++i){
         result[i] = coef_prod_rounded[i] % Q;
         // NOTE: That the cyclic convolution should already be given by the FFT multiplication
         //result[i] =  (result[i] + coef_prod_rounded[i+N]) % Q;
    } 
    
    // The result should be the same as prod.
    if(utils::is_eq_poly(result, prod, N)){
        std::cout << "FFT Polynomials Multiplication Test: OK" << std::endl;
    }else{
        std::cout << "FFT Polynomials Multiplication Test: Fail" << std::endl;
        std::cout << "prod: " << utils::to_string(prod, N) << std::endl;
        std::cout << "result: " << utils::to_string(result, N) << std::endl;
        long *diff = new long[N];
        for(int i =0; i < N; ++i){
            diff[i] = prod[i] - result[i];
        }
        std::cout << "diff: " << utils::to_string(diff, N) << std::endl;
    }

}


void fft_plan_test(ring_type ring, int num_of_tests){
    std::cout << "================= fft_plan_test =================" << std::endl;
    
   int N = 2048; 
    // Around .. bits modulus 
   long Q = 268435456;
   // ... bits  
   long B = 2048; 
 
    
   double stddev = 3.2;
   sampler rand; 
   ntru_param param(ring, N, Q, any, stddev); 
 
    // Choose uniformly random polynomials
    long poly_1[N];
    long poly_2[N];
    long poly_3[N];
    // This is the polynomials where classinc multiplication is done.
    long *prod = new long[N]; 
    // Setting up the fft_plan and the fft polynomials (for eval form)
    fft_plan engine(ring, N); 
    fftw_complex* poly_1_eval = new fftw_complex[engine.plan_size];
    fftw_complex* poly_2_eval = new fftw_complex[engine.plan_size];
    fftw_complex* poly_3_eval = new fftw_complex[engine.plan_size];
    // The function in evaluation form
    fftw_complex* prod_eval = new fftw_complex[engine.plan_size];
    // THe function in coefficient form
    long *prod_coef = new long[engine.plan_size];
    // Mod reduced (we will compere this with the prod)
    long *prod_mod = new long[N];
    bool test = true;  
    std::chrono::high_resolution_clock::time_point start, end; 
    double total_time = 0;
    std::cout << "Start testing..." << std::endl;
    // Start the test
    for(int i = 0; i < num_of_tests; ++i){
        // Choose random polynomails
        rand.uniform_array(poly_1, N, Q);
        rand.uniform_array(poly_2, N, B); 
        rand.uniform_array(poly_3, N, Q); 
        // Classic multiplication: prod = poly_1 * poly_2 + poly_3
        utils::mul_mod(prod, poly_1, N, poly_2, N, param.N, param.Q, param.ring); 
        utils::add_mod(prod, prod, N, poly_3, N, param.N, param.Q); 
        // FFT multiplication: Get the evaluation forms for poly_1, poly_2, poly_3
        // FFT multiplication: poly_1 and poly_3 are scaled (divided by 2*N)
        // engine.to_eval_form_scale(poly_1_eval, poly_1, scale); 
 
        start = std::chrono::high_resolution_clock::now();  
        if(ring==cyclic){ 
            engine.to_eval_form_scale(poly_1_eval, poly_1); 
        }
        else if(ring==negacyclic){
            engine.to_eval_form_scale(poly_1_eval, poly_1, 2.0); 
        }
        engine.to_eval_form(poly_2_eval, poly_2);
        // engine.to_eval_form_scale(poly_3_eval, poly_3, scale);
        engine.to_eval_form_scale(poly_3_eval, poly_3);
        engine.mul_eval_form(prod_eval, poly_1_eval, poly_2_eval);
        engine.add_eval_form(prod_eval, prod_eval, poly_3_eval);
        engine.to_coef_form(prod_coef, prod_eval);
        utils::mod_reduce(prod_mod, prod_coef, param.Q, param.engine->N); 
        end = std::chrono::high_resolution_clock::now();  
        total_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        utils::array_mod_form(prod_mod, prod_mod, param.N, param.Q);
        // The result should be the same as prod.
        if(!utils::is_eq_poly(prod_mod, prod, N)){ 
            std::cout << "FFT Polynomials Multiplication Test: Fail" << std::endl;
            std::cout << "At test number: " << i << std::endl;
            std::cout << "prod: " << utils::to_string(prod, N) << std::endl;
            std::cout << "result: " << utils::to_string(prod_mod, N) << std::endl;
            long *diff = new long[N];
            for(int i =0; i < N; ++i){
                diff[i] = prod[i] - prod_mod[i];
            }
            std::cout << "diff: " << utils::to_string(diff, N) << std::endl;
            test = false;
            break;
        }
    }
    if(test){
        std::cout << "FFT Polynomials Multiplication Test: OK" << std::endl;
    }

    std::cout << "Time for Single Functional Bootstrap: " << total_time/num_of_tests << " [s]" << std::endl;
}




void over_64_fft_plan_test(ring_type ring, int num_of_tests){
    std::cout << "================= over_64_fft_plan_test =================" << std::endl;
    // I will test very large rings (N=2^14) and large modulus. 
    // The arithmetic necessary to handle that should be long long (over 64 bits - most likely requires long double for the fft)
    // NOTE: The modulus etc. must be smaller than 64-bits. However, due to large rings, and large moduli 
    // We will multiply two polynomials, one is mod Q, the other one is mod B. But the result is mod Q.
    // N = 2**13
   int N = 8192; 
   N = 4096;
    // Around .. bits modulus
   long Q = 4398046511104;
   Q = 268435456;
   // ... bits  
   long B = 1024;
   double stddev = 3.2;
   sampler rand;
   //NTL::ZZ_pX psi_poly;
   //utils::set_polynomial_from_array(psi_poly, psi, N+1, Q); 
   ntru_param param(ring, N, Q, any, stddev); 
 
    // Choose uniformly random polynomials
    long poly_1[N];
    long poly_2[N];
    long poly_3[N];
    // This is the polynomials where classinc multiplication is done.
    long *prod = new long[N]; 
    // Setting up the fft_plan and the fft polynomials (for eval form)
    fft_plan engine(ring, N, true); 
    fftwl_complex* poly_1_eval = new fftwl_complex[engine.plan_size];
    fftwl_complex* poly_2_eval = new fftwl_complex[engine.plan_size];
    fftwl_complex* poly_3_eval = new fftwl_complex[engine.plan_size]; 
    // The function in evaluation form
    fftwl_complex* prod_eval = new fftwl_complex[engine.plan_size];
    // THe function in coefficient form
    long *prod_coef = new long[engine.plan_size];
    // Mod reduced (we will compere this with the prod)
    long *prod_mod = new long[N];
    bool test = true; 
    std::chrono::high_resolution_clock::time_point start, end; 
    double total_time = 0;
    std::cout << "Start testing..." << std::endl;
    // Start the test
    for(int i = 0; i < num_of_tests; ++i){
        // Choose random polynomails
        rand.uniform_array(poly_1, N, Q);
        rand.uniform_array(poly_2, N, B); 
        rand.uniform_array(poly_3, N, Q); 
        // Classic multiplication: prod = poly_1 * poly_2 + poly_3
        // TODO: Should be done via NTL...hmmm Actuatly its oK
        utils::mul_mod(prod, poly_1, N, poly_2, N, param.N, param.Q, param.ring); 
        utils::add_mod(prod, prod, N, poly_3, N, param.N, param.Q); 
        // FFT multiplication: Get the evaluation forms for poly_1, poly_2, poly_3
        // FFT multiplication: poly_1 and poly_3 are scaled (divided by 2*N)
        // engine.to_eval_form_scale_l(poly_1_eval, poly_1, scale); 
        start = std::chrono::high_resolution_clock::now();  
        if(ring==cyclic){ 
            engine.to_eval_form_scale_l(poly_1_eval, poly_1); 
        }
        else if(ring==negacyclic){
            engine.to_eval_form_scale_l(poly_1_eval, poly_1, 2.0); 
        }
        engine.to_eval_form_l(poly_2_eval, poly_2);
        // engine.to_eval_form_scale_l(poly_3_eval, poly_3, scale);
        engine.to_eval_form_scale_l(poly_3_eval, poly_3);
        engine.mul_eval_form_l(prod_eval, poly_1_eval, poly_2_eval);
        engine.add_eval_form_l(prod_eval, prod_eval, poly_3_eval);
        engine.to_coef_form_l(prod_coef, prod_eval);
        end = std::chrono::high_resolution_clock::now();   
        total_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        utils::mod_reduce(prod_mod, prod_coef, param.Q, param.engine->N);
        utils::array_mod_form(prod_mod, prod_mod, param.N, param.Q);
        // The result should be the same as prod.
        if(!utils::is_eq_poly(prod_mod, prod, N)){ 
            std::cout << "FFT Polynomials Multiplication Test: Fail" << std::endl;
            std::cout << "At test number: " << i << std::endl;
            std::cout << "prod: " << utils::to_string(prod, N) << std::endl;
            std::cout << "result: " << utils::to_string(prod_mod, N) << std::endl;
            long *diff = new long[N];
            for(int i =0; i < N; ++i){
                diff[i] = prod[i] - prod_mod[i];
            }
            std::cout << "diff: " << utils::to_string(diff, N) << std::endl;
            test = false;
            break;
        }
    }
    if(test){
        std::cout << "FFT Polynomials Multiplication Test: OK" << std::endl;
    }

    std::cout << "Time for Single Functional Bootstrap: " << total_time/num_of_tests << " [s]" << std::endl;
}



void fft_negacyclic_convolution_test(int N, long Q, long B){
    std::cout << "================= fft_negacyclic_convolution_test =================" << std::endl; 
   //int N = 2048; 
    // Around .. bits modulus
   //long Q = 4294967296;
   // ... bits  
   //long B = 262144;  
    
   sampler rand;  
 
    // Choose uniformly random polynomials
    long poly_1[N];
    long poly_2[N];
    long poly_3[N];
    // This is the polynomials where classinc multiplication is done.
    long *prod = new long[N];
    // For FFT: Need to scale one of the polynomials down by 2*N
    //double scale = 2.0 * (double)N;
    // Setting up the fft_plan and the fft polynomials (for eval form)
    fft_plan engine(negacyclic, N); 
    fftw_complex* poly_1_eval = new fftw_complex[engine.plan_size];
    fftw_complex* poly_2_eval = new fftw_complex[engine.plan_size];
    fftw_complex* poly_3_eval = new fftw_complex[engine.plan_size];
    // The function in evaluation form
    fftw_complex* prod_eval = new fftw_complex[engine.plan_size];
    // THe function in coefficient form
    long *prod_coef = new long[engine.plan_size];
    // Mod reduced (we will compere this with the prod)
    long *prod_mod = new long[N];

    rand.uniform_array(poly_1, N, Q);
    rand.uniform_array(poly_2, N, B);
    rand.uniform_array(poly_3, N, Q); 

    utils::mul_mod(prod, poly_1, N, poly_2, N, N, Q, negacyclic); 
    //utils::add_mod(prod, prod, N, poly_3, N, N, Q); 
    //std::cout << "prod: " << utils::to_string(prod, N) << std::endl;
    engine.to_eval_form_scale(poly_1_eval, poly_1, 2.0); 
    engine.to_eval_form_scale(poly_3_eval, poly_3); 
    engine.to_eval_form(poly_2_eval, poly_2);
    engine.mul_eval_form(prod_eval, poly_1_eval, poly_2_eval);
    //engine.add_eval_form(prod_eval, prod_eval, poly_3_eval);
    engine.to_coef_form(prod_coef, prod_eval);
    //param.mod_reduce(prod_mod, prod_coef);
    utils::array_mod_form(prod_mod, prod_coef, N, Q);
    //std::cout << "prod_mod: " << utils::to_string(prod_mod, N) << std::endl;

    if(!utils::is_eq_poly(prod_mod, prod, N)){
        long* diff = new long[N];
        for(int j = 0; j < N; ++j){
            diff[j] = prod[j] - prod_mod[j];
        }
        //std::cout << "diff: " << utils::to_string(diff, N) << std::endl;
        int max = utils::max(diff, N);
        int min = utils::min(diff, N);
        std::cout << "max: " << max <<std::endl;
        std::cout << "min: " << min << std::endl;
        std::cout << "mean: " << utils::mean(diff, N) << std::endl;
        std::cout << "variance: " << utils::variance(diff, N) << std::endl;
        std::cout << "stddev: " << utils::standard_deviation(diff, N) << std::endl; 
        //int size = max - min + 1;
        //std::cout << "size: " << size << std::endl; 
        //long* occurences = utils::count_occurences(diff, N);
        //std::cout << "occurences: " << utils::to_string(occurences, size) << std::endl;
    } 
}


void fft_negacyclic_convolution_test_long_double(int num_of_tests){
    std::cout << "================= fft_plan_test =================" << std::endl; 
   int N = 2048; 
    // Around .. bits modulus
   long Q = 4294967296;
   // ... bits  
   long B = 32; 
   /*
   int N = 4; 
    // Around .. bits modulus
   long Q = 13;
   // ... bits  
   long B = 13;
   */
    
   double stddev = 3.2;
   sampler rand; 
   //ntru_param param(negacyclic, N, Q, any, stddev); 
 
    // Choose uniformly random polynomials
    long poly_1[N];
    long poly_2[N];
    long poly_3[N];
    // This is the polynomials where classinc multiplication is done.
    long *prod = new long[N];
    // For FFT: Need to scale one of the polynomials down by 2*N
    //double scale = 2.0 * (double)N;
    // Setting up the fft_plan and the fft polynomials (for eval form)
    fft_plan engine(negacyclic, N, true); 
    fftwl_complex* poly_1_eval = new fftwl_complex[engine.plan_size];
    fftwl_complex* poly_2_eval = new fftwl_complex[engine.plan_size];
    fftwl_complex* poly_3_eval = new fftwl_complex[engine.plan_size];
    // The function in evaluation form
    fftwl_complex* prod_eval = new fftwl_complex[engine.plan_size];
    // THe function in coefficient form
    long *prod_coef = new long[engine.plan_size];
    // Mod reduced (we will compere this with the prod)
    long *prod_mod = new long[N];

    rand.uniform_array(poly_1, N, Q);
    rand.uniform_array(poly_2, B, Q);
    rand.uniform_array(poly_3, N, Q); 

    utils::mul_mod(prod, poly_1, N, poly_2, N, N, Q, negacyclic); 
    //utils::add_mod(prod, prod, N, poly_3, N, N, Q); 
    //std::cout << "prod: " << utils::to_string(prod, N) << std::endl;
    engine.to_eval_form_scale_l(poly_1_eval, poly_1, 2.0); 
    engine.to_eval_form_scale_l(poly_3_eval, poly_3); 
    engine.to_eval_form_l(poly_2_eval, poly_2);
    engine.mul_eval_form_l(prod_eval, poly_1_eval, poly_2_eval);
    //engine.add_eval_form(prod_eval, prod_eval, poly_3_eval);
    engine.to_coef_form_l(prod_coef, prod_eval);
    //param.mod_reduce(prod_mod, prod_coef);
    utils::array_mod_form(prod_mod, prod_coef, N, Q);
    //std::cout << "prod_mod: " << utils::to_string(prod_mod, N) << std::endl;

    if(!utils::is_eq_poly(prod_mod, prod, N)){
        long* diff = new long[N];
        for(int j = 0; j < N; ++j){
            diff[j] = prod[j] - prod_mod[j];
        }
        std::cout << "diff: " << utils::to_string(diff, N) << std::endl;
    } 
}


int main(){
 
    // Some performance tests
    //int_vs_auto_test();
    //int_vs_vector_test();  
    //mod_reduction_test();
    //mult_test();
    //fft_random_mul_test();
    //fft_random_convolve_test();

    //fft_mul_test();
    
    //over_64_fft_plan_test(negacyclic, 100);
    // NOTE: pay attention to the ring - for negacyclic we need a power of two cyclotomic.
    //fft_plan_test(cyclic, 100);  
    
    //fft_negacyclic_convolution_test_long_double(100);

    fft_negacyclic_convolution_test(4096, 4398046511104, 16);
    fft_negacyclic_convolution_test(4096, 4398046511104, 64);
    fft_negacyclic_convolution_test(4096, 4398046511104, 256);
    fft_negacyclic_convolution_test(4096, 4398046511104, 1024);
    fft_negacyclic_convolution_test(4096, 4398046511104, 4096);
    fft_negacyclic_convolution_test(4096, 4398046511104, 16384);
    fft_negacyclic_convolution_test(4096, 4398046511104, 65536);
    fft_negacyclic_convolution_test(4096, 4398046511104, 262144);
     
}