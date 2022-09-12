/*
PLEASE DO NOT DISTRIBUTE!!! This version is for review only. 
*/

#include <fftw3.h>
#include <random>
#include <iostream>

#include "../include/fft_plan.h"

  

fft_plan::~fft_plan(){    
    fftw_destroy_plan(plan_to_eval_form);
    fftw_destroy_plan(plan_to_coef_form);
    fftw_free(in); 
    fftw_free(out);    
}


// TODO: Need to take information on whether we have cyclic or nagacyclic convolution
fft_plan::fft_plan(ring_type ring, int N){   
    this->ring = ring;
    this->N = N;
    if(ring == cyclic){ 
     this->plan_size = N; 
    }else if(ring == negacyclic){
        this->plan_size = 2*N; 
    }
    
    in = (double*) fftw_malloc(sizeof(double) * plan_size);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) *  plan_size);
    plan_to_eval_form = fftw_plan_dft_r2c_1d(plan_size, in, out,  FFTW_PATIENT);
    plan_to_coef_form = fftw_plan_dft_c2r_1d(plan_size, out, in,  FFTW_PATIENT); 
    //plan_init = true;  
}

// TODO: Need to take information on whether we have cyclic or nagacyclic convolution
fft_plan::fft_plan(ring_type ring, int N, bool long_arithmetic){   
    this->ring = ring;
    this->N = N;
    if(ring == cyclic){ 
     this->plan_size = N; 
    }else if(ring == negacyclic){
        this->plan_size = 2*N; 
    }
    this->long_arithmetic = long_arithmetic;
    if(!long_arithmetic){
        in = (double*) fftw_malloc(sizeof(double) * plan_size);
        out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) *  plan_size);
        plan_to_eval_form = fftw_plan_dft_r2c_1d(plan_size, in, out,  FFTW_PATIENT);
        plan_to_coef_form = fftw_plan_dft_c2r_1d(plan_size, out, in,  FFTW_PATIENT); 
    }else{
        in_l = (long double*) fftw_malloc(sizeof(long double) * plan_size);
        out_l = (fftwl_complex*) fftw_malloc(sizeof(fftwl_complex) *  plan_size);
        plan_to_eval_form_l = fftwl_plan_dft_r2c_1d(plan_size, in_l, out_l,  FFTW_PATIENT);
        plan_to_coef_form_l = fftwl_plan_dft_c2r_1d(plan_size, out_l, in_l,  FFTW_PATIENT); 
    } 
    //plan_init = true;   
}


void fft_plan::to_eval_form(fftw_complex* eval_form, long *poly){ 
    for(int i = 0; i < N; ++i){ 
        in[i] = (double)poly[i];
        if(ring==negacyclic){
            in[i+N] = -in[i]; 
        } 
    }
    fftw_execute(plan_to_eval_form);  
    for(int i = 0; i < plan_size; ++i){ 
        eval_form[i][0] = out[i][0];
        eval_form[i][1] = out[i][1];
    } 
}

void fft_plan::to_eval_form(fftw_complex* eval_form, int *poly){ 
    for(int i = 0; i < N; ++i){ 
        in[i] = (double)poly[i];
        if(ring==negacyclic){
            in[i+N] = -in[i];  
        } 
    }
    fftw_execute(plan_to_eval_form);  
    for(int i = 0; i < plan_size; ++i){ 
        eval_form[i][0] = out[i][0];
        eval_form[i][1] = out[i][1];
    } 
}
    
 
void fft_plan::to_eval_form_scale(fftw_complex* eval_form, long *poly){ 
    // DONE: Scale should be precomputed in the constructor
    // DONE: For cyclic scale is plan_size, for negacyclic its plan_size * 2 (I think)
    //double scale = (double)plan_size;
    for(int i = 0; i < N; ++i){ 
        in[i] = (double)poly[i] / plan_size; 
        if(ring==negacyclic){
            in[i+N] = -in[i]; 
        } 
    }
    fftw_execute(plan_to_eval_form);  
    for(int i = 0; i < plan_size; ++i){ 
        eval_form[i][0] = out[i][0];
        eval_form[i][1] = out[i][1];
    }  
}


void fft_plan::to_eval_form_scale(fftw_complex* eval_form, long *poly, double additional_scale){ 
    // DONE: Scale should be precomputed in the constructor
    // DONE: For cyclic scale is plan_size, for negacyclic its plan_size * 2 (I think)
    double scale = (double)(plan_size * additional_scale);
    for(int i = 0; i < N; ++i){   
        in[i] = (double)poly[i] / scale; 
        if(ring==negacyclic){
            in[i+N] = -in[i]; 
        } 
    }
    fftw_execute(plan_to_eval_form);  
    for(int i = 0; i < plan_size; ++i){ 
        eval_form[i][0] = out[i][0];
        eval_form[i][1] = out[i][1];
    }  
}
 

void fft_plan::to_coef_form(long *coef_form, fftw_complex* eval_form){
    for(int i = 0; i < plan_size; ++i){
        out[i][0] = eval_form[i][0];
        out[i][1] = eval_form[i][1];
    }
    fftw_execute(plan_to_coef_form); 
    int copy;
    if(ring == cyclic){
        copy = plan_size;
    }else if(ring == negacyclic){
        copy = plan_size/2;
    }
    for(int i = 0; i < copy; ++i){ 
        coef_form[i] = (long)round(in[i]);
    }
}


void fft_plan::to_coef_form(double *coef_form, fftw_complex* eval_form){
    for(int i = 0; i < plan_size; ++i){
        out[i][0] = eval_form[i][0];
        out[i][1] = eval_form[i][1];
    }
    fftw_execute(plan_to_coef_form); 
    int copy;
    if(ring == cyclic){
        copy = plan_size;
    }else if(ring == negacyclic){
        copy = plan_size/2;
    }
    for(int i = 0; i < copy; ++i){ 
        coef_form[i] = in[i];
    }
} 
 
void fft_plan::add_eval_form(fftw_complex *sum, fftw_complex* in_1, fftw_complex* in_2){
    // Add the vectors (Note that its complex multiplication)
    if(ring == cyclic){
        for(int i = 0; i < plan_size; ++i){
            sum[i][0] = in_1[i][0] + in_2[i][0];
            sum[i][1] = in_1[i][1] + in_2[i][1];
        }
    } else if(ring == negacyclic){ 
        for(int i = 0; i < plan_size; i+=2){
            sum[i][0] = 0.0;
            sum[i][1] = 0.0;
            sum[i+1][0] = in_1[i+1][0] + in_2[i+1][0];
            sum[i+1][1] = in_1[i+1][1] + in_2[i+1][1];
        }
    } 
}

void fft_plan::mul_eval_form(fftw_complex *prod, fftw_complex* in_1, fftw_complex* in_2){
    // Multiply the vectors (Note that its complex multiplication)
    double temp;  
    if(ring == cyclic){
        for(int i = 0; i < plan_size; ++i){ 
            temp = in_1[i][0] * in_2[i][0] - in_1[i][1] * in_2[i][1];
            prod[i][1] = in_1[i][0] * in_2[i][1] + in_1[i][1] * in_2[i][0];
            prod[i][0] = temp; 
        }
    } else if(ring == negacyclic){ 
        int ip = 0;
        int half = plan_size/2;
        for(int i = 0; i < half; i+=2){
            ip = i+1;
            prod[i][0] = 0.0;
            prod[i][1] = 0.0;
            prod[half+i][0] = 0.0;
            prod[half+i][1] = 0.0;
            temp = in_1[ip][0] * in_2[ip][0] - in_1[ip][1] * in_2[ip][1];
            prod[ip][1] = in_1[ip][0] * in_2[ip][1] + in_1[ip][1] * in_2[ip][0];
            prod[ip][0] = temp; 
            prod[half+ip][1] =  -prod[ip][1];
        }
    } 
} 



// ================================ Long Arithmetic Specific =====================================

// TODO Do the same changes (copy paste) to include negacyclic stuff, but change double to long double

void fft_plan::to_eval_form_l(fftwl_complex* eval_form_l, long *poly){ 
    for(int i = 0; i < N; ++i){ 
        in_l[i] = (long double)poly[i];
        if(ring==negacyclic){
            in_l[i+N] = -in_l[i];  
        } 
    }
    fftwl_execute(plan_to_eval_form_l);  
    for(int i = 0; i < plan_size; ++i){ 
        eval_form_l[i][0] = out_l[i][0];
        eval_form_l[i][1] = out_l[i][1];
    } 
}

void fft_plan::to_eval_form_l(fftwl_complex* eval_form_l, int *poly){ 
    for(int i = 0; i < N; ++i){ 
        in_l[i] = (long double)poly[i];
        if(ring==negacyclic){
            in_l[i+N] = -in_l[i];  
        }  
    }
    fftwl_execute(plan_to_eval_form_l);  
    for(int i = 0; i < plan_size; ++i){ 
        eval_form_l[i][0] = out_l[i][0];
        eval_form_l[i][1] = out_l[i][1];
    } 
}
    

void fft_plan::to_eval_form_scale_l(fftwl_complex* eval_form_l, long *poly){ 
    long double scale = (double)plan_size;
    for(int i = 0; i < N; ++i){ 
        in_l[i] = (long double)poly[i] / (long double)scale; 
        if(ring==negacyclic){
            in_l[i+N] = -in_l[i]; 
        } 
    }
    fftwl_execute(plan_to_eval_form_l);  
    for(int i = 0; i < plan_size; ++i){ 
        eval_form_l[i][0] = out_l[i][0];
        eval_form_l[i][1] = out_l[i][1];
    } 
}


void fft_plan::to_eval_form_scale_l(fftwl_complex* eval_form_l, long *poly, double additional_scale){ 
    long double scale = (double)(plan_size * additional_scale) ;
    for(int i = 0; i < N; ++i){ 
        in_l[i] = (long double)poly[i] / scale; 
        if(ring==negacyclic){
            in_l[i+N] = -in_l[i]; 
        } 
    }
    fftwl_execute(plan_to_eval_form_l);  
    for(int i = 0; i < plan_size; ++i){ 
        eval_form_l[i][0] = out_l[i][0];
        eval_form_l[i][1] = out_l[i][1];
    } 
}
  

void fft_plan::to_coef_form_l(long double *coef_form_l, fftwl_complex* eval_form_l){
    for(int i = 0; i < plan_size; ++i){
        out_l[i][0] = eval_form_l[i][0];
        out_l[i][1] = eval_form_l[i][1];
    }
    fftwl_execute(plan_to_coef_form_l); 
    int copy;
    if(ring == cyclic){
        copy = plan_size;
    }else if(ring == negacyclic){
        copy = plan_size/2;
    } 
    for(int i = 0; i < copy; ++i){
        coef_form_l[i] = in_l[i];
    }
}

 
void fft_plan::add_eval_form_l(fftwl_complex *sum_l, fftwl_complex* in_1_l, fftwl_complex* in_2_l){

    // Add the vectors (Note that its complex multiplication)
    if(ring == cyclic){
        for(int i = 0; i < plan_size; ++i){
            sum_l[i][0] = in_1_l[i][0] + in_2_l[i][0];
            sum_l[i][1] = in_1_l[i][1] + in_2_l[i][1];
        }
    } else if(ring == negacyclic){ 
        for(int i = 0; i < plan_size; i+=2){
            sum_l[i][0] = 0.0;
            sum_l[i][1] = 0.0;
            sum_l[i+1][0] = in_1_l[i+1][0] + in_2_l[i+1][0];
            sum_l[i+1][1] = in_1_l[i+1][1] + in_2_l[i+1][1];
        }
    }  
}

void fft_plan::mul_eval_form_l(fftwl_complex *prod_l, fftwl_complex* in_1_l, fftwl_complex* in_2_l){

    // Multiply the vectors (Note that its complex multiplication)
    long double temp_l;  
    if(ring == cyclic){
        for(int i = 0; i < plan_size; ++i){ 
            temp_l = in_1_l[i][0] * in_2_l[i][0] - in_1_l[i][1] * in_2_l[i][1];
            prod_l[i][1] = in_1_l[i][0] * in_2_l[i][1] + in_1_l[i][1] * in_2_l[i][0];
            prod_l[i][0] = temp_l; 
        }
    } else if(ring == negacyclic){ 
        int ip = 0;
        int half = plan_size/2;
        for(int i = 0; i < half; i+=2){
            ip = i+1;
            prod_l[i][0] = 0.0;
            prod_l[i][1] = 0.0;
            prod_l[half+i][0] = 0.0;
            prod_l[half+i][1] = 0.0;
            temp_l = in_1_l[ip][0] * in_2_l[ip][0] - in_1_l[ip][1] * in_2_l[ip][1];
            prod_l[ip][1] = in_1_l[ip][0] * in_2_l[ip][1] + in_1_l[ip][1] * in_2_l[ip][0];
            prod_l[ip][0] = temp_l; 
            prod_l[half+ip][1] =  -prod_l[ip][1];
        }
    }  
} 