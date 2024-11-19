#include "math/fft_plan.h"

using namespace fhe_deck;

FFTPlan::~FFTPlan(){    
    if(is_init == false){
        return;
    }
    if(long_arithmetic){
        fftwl_destroy_plan(plan_to_eval_form_l);
        fftwl_destroy_plan(plan_to_coef_form_l);
        fftwl_free(in_l); 
        fftwl_free(out_l); 
    }else{
        fftw_destroy_plan(plan_to_eval_form);
        fftw_destroy_plan(plan_to_coef_form);
        fftw_free(in); 
        fftw_free(out);  
    } 
}

 
 
FFTPlan::FFTPlan(RingType ring, int32_t N){   
    this->ring = ring;
    this->N = N; 
    init_tables(); 
}
 
FFTPlan::FFTPlan(RingType ring, int32_t N, bool long_arithmetic){   
    this->ring = ring;
    this->N = N;
    this->long_arithmetic = long_arithmetic;
    init_tables();   
}


FFTPlan::FFTPlan(const FFTPlan& other){ 
    this->ring = other.ring;
    this->N = other.N;
    this->long_arithmetic = other.long_arithmetic;
    init_tables();
}

FFTPlan& FFTPlan::operator=(FFTPlan other){ 
    if (this == &other)
    { 
        return *this;
    } 
    this->ring = other.ring;
    this->N = other.N;
    this->long_arithmetic = other.long_arithmetic;
    init_tables();
    return *this;
}

void FFTPlan::init_tables(){
    if(ring == RingType::cyclic){ 
     this->plan_size = N; 
    }else if(ring == RingType::negacyclic){
        this->plan_size = 2*N; 
    } 
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
    this->is_init = true;
}



fftw_complex* FFTPlan::init_fft_poly(){
    return new fftw_complex[plan_size]; 
}

fftwl_complex* FFTPlan::init_fft_poly_l(){
    return new fftwl_complex[plan_size]; 
}
  


void FFTPlan::to_eval_form(fftw_complex* eval_form, int64_t *poly){  
    for(int32_t i = 0; i < N; ++i){ 
        in[i] = (double)poly[i];
        if(ring==RingType::negacyclic){
            in[i+N] = -in[i]; 
        } 
    }
    for(int32_t i = 0; i < plan_size; ++i){
        out[i][0] = 0;
        out[i][1] = 0;
    } 
    fftw_execute(plan_to_eval_form);    
    for(int32_t i = 0; i < plan_size; ++i){ 
        eval_form[i][0] = out[i][0];
        eval_form[i][1] = out[i][1];
    } 
}

void FFTPlan::to_eval_form(fftw_complex* eval_form, int32_t *poly){ 
    for(int32_t i = 0; i < N; ++i){ 
        in[i] = (double)poly[i];
        if(ring==RingType::negacyclic){
            in[i+N] = -in[i];  
        } 
    }
    for(int32_t i = 0; i < plan_size; ++i){
        out[i][0] = 0;
        out[i][1] = 0;
    }
    fftw_execute(plan_to_eval_form);  
    for(int32_t i = 0; i < plan_size; ++i){ 
        eval_form[i][0] = out[i][0];
        eval_form[i][1] = out[i][1];
    } 
}
    
  
void FFTPlan::to_eval_form_scale(fftw_complex* eval_form, int64_t *poly){ 
    // DONE: Scale should be precomputed in the constructor
    // DONE: For cyclic scale is plan_size, for negacyclic its plan_size * 2 (I think)
    //double scale = (double)plan_size;
    for(int32_t i = 0; i < N; ++i){ 
        in[i] = (double)poly[i] / plan_size; 
        if(ring==RingType::negacyclic){
            in[i+N] = -in[i]; 
        } 
    }
    for(int32_t i = 0; i < plan_size; ++i){
        out[i][0] = 0;
        out[i][1] = 0;
    }
    fftw_execute(plan_to_eval_form);  
    for(int32_t i = 0; i < plan_size; ++i){ 
        eval_form[i][0] = out[i][0];
        eval_form[i][1] = out[i][1];
    }  
}


void FFTPlan::to_eval_form_scale(fftw_complex* eval_form, int64_t *poly, double additional_scale){  
    double scale = (double)(plan_size * additional_scale);
    for(int32_t i = 0; i < N; ++i){   
        in[i] = (double)poly[i] / scale; 
        if(ring==RingType::negacyclic){
            in[i+N] = -in[i]; 
        } 
    }
    for(int32_t i = 0; i < plan_size; ++i){
        out[i][0] = 0;
        out[i][1] = 0;
    } 
    fftw_execute(plan_to_eval_form);   
    for(int32_t i = 0; i < plan_size; ++i){ 
        eval_form[i][0] = out[i][0];
        eval_form[i][1] = out[i][1];
    }   
}
 

void FFTPlan::to_coef_form(int64_t *coef_form, fftw_complex* eval_form){ 
    for(int32_t i = 0; i < plan_size; ++i){
        out[i][0] = eval_form[i][0];
        out[i][1] = eval_form[i][1];
    }
    fftw_execute(plan_to_coef_form);  
    int32_t copy;
    if(ring == RingType::cyclic){
        copy = plan_size;
    }else if(ring == RingType::negacyclic){
        copy = plan_size/2;
    }
    for(int32_t i = 0; i < copy; ++i){ 
        coef_form[i] = (int64_t)round(in[i]);
    }
}


void FFTPlan::to_coef_form(double *coef_form, fftw_complex* eval_form){
    for(int32_t i = 0; i < plan_size; ++i){
        out[i][0] = eval_form[i][0];
        out[i][1] = eval_form[i][1];
    }
    fftw_execute(plan_to_coef_form); 
    int32_t copy;
    if(ring == RingType::cyclic){
        copy = plan_size;
    }else if(ring == RingType::negacyclic){
        copy = plan_size/2;
    }
    for(int32_t i = 0; i < copy; ++i){ 
        coef_form[i] = in[i];
    }
} 

void FFTPlan::to_coef_form_scale(int64_t *coef_form, fftw_complex* eval_form, double additional_scale){
    double scale = (double)(plan_size * additional_scale);
    for(int32_t i = 0; i < plan_size; ++i){
        out[i][0] = eval_form[i][0];
        out[i][1] = eval_form[i][1];
    }
    fftw_execute(plan_to_coef_form);  
    int32_t copy;
    if(ring == RingType::cyclic){
        copy = plan_size;
    }else if(ring == RingType::negacyclic){
        copy = plan_size/2;
    }
    for(int32_t i = 0; i < copy; ++i){ 
        coef_form[i] = (int64_t)round(in[i]/scale);
    }
}

void FFTPlan::to_coef_form_scale(double *coef_form, fftw_complex* eval_form, double additional_scale){
    double scale = (double)(plan_size * additional_scale);
    for(int32_t i = 0; i < plan_size; ++i){
        out[i][0] = eval_form[i][0];
        out[i][1] = eval_form[i][1];
    }
    fftw_execute(plan_to_coef_form); 
    int32_t copy;
    if(ring == RingType::cyclic){
        copy = plan_size;
    }else if(ring == RingType::negacyclic){
        copy = plan_size/2;
    }
    for(int32_t i = 0; i < copy; ++i){ 
        coef_form[i] = in[i]/scale;
    }
}
 
void FFTPlan::add_eval_form(fftw_complex *sum, fftw_complex* in_1, fftw_complex* in_2){
    // Add the vectors (Note that its complex multiplication)
    if(ring == RingType::cyclic){
        for(int32_t i = 0; i < plan_size; ++i){
            sum[i][0] = in_1[i][0] + in_2[i][0];
            sum[i][1] = in_1[i][1] + in_2[i][1];
        }
    } else if(ring == RingType::negacyclic){ 
        for(int32_t i = 0; i < plan_size; i+=2){
            sum[i][0] = 0.0;
            sum[i][1] = 0.0;
            sum[i+1][0] = in_1[i+1][0] + in_2[i+1][0];
            sum[i+1][1] = in_1[i+1][1] + in_2[i+1][1];
        }
    } 
}

void FFTPlan::mul_eval_form(fftw_complex *prod, fftw_complex* in_1, fftw_complex* in_2){
    // Multiply the vectors (Note that its complex multiplication)
    double temp;  
    if(ring == RingType::cyclic){
        for(int32_t i = 0; i < plan_size; ++i){ 
            temp = in_1[i][0] * in_2[i][0] - in_1[i][1] * in_2[i][1];
            prod[i][1] = in_1[i][0] * in_2[i][1] + in_1[i][1] * in_2[i][0];
            prod[i][0] = temp; 
        }
    } else if(ring == RingType::negacyclic){ 
        int32_t ip = 0;
        int32_t half = plan_size/2;
        for(int32_t i = 0; i < half; i+=2){
            ip = i+1;
            prod[i][0] = 0.0;
            prod[i][1] = 0.0;
            prod[half+i][0] = 0.0;
            prod[half+i][1] = 0.0;
            temp = in_1[ip][0] * in_2[ip][0] - in_1[ip][1] * in_2[ip][1];
            prod[ip][1] = in_1[ip][0] * in_2[ip][1] + in_1[ip][1] * in_2[ip][0];
            prod[ip][0] = temp; 
            prod[half+ip][1] = -prod[ip][1];
        }
    } 
} 



// ================================ Long Arithmetic Specific =====================================

// TODO Do the same changes (copy paste) to include negacyclic stuff, but change double to long double

void FFTPlan::to_eval_form_l(fftwl_complex* eval_form_l, int64_t *poly){ 
    for(int32_t i = 0; i < N; ++i){ 
        in_l[i] = (long double)poly[i];
        if(ring==RingType::negacyclic){
            in_l[i+N] = -in_l[i];  
        } 
    }
    for(int32_t i = 0; i < plan_size; ++i){
        out_l[i][0] = 0;
        out_l[i][1] = 0;
    }
    fftwl_execute(plan_to_eval_form_l);  
    for(int32_t i = 0; i < plan_size; ++i){ 
        eval_form_l[i][0] = out_l[i][0];
        eval_form_l[i][1] = out_l[i][1];
    } 
}

void FFTPlan::to_eval_form_l(fftwl_complex* eval_form_l, int32_t *poly){ 
    for(int32_t i = 0; i < N; ++i){ 
        in_l[i] = (long double)poly[i];
        if(ring==RingType::negacyclic){
            in_l[i+N] = -in_l[i];  
        }  
    }
    for(int32_t i = 0; i < plan_size; ++i){
        out_l[i][0] = 0;
        out_l[i][1] = 0;
    }
    fftwl_execute(plan_to_eval_form_l);  
    for(int32_t i = 0; i < plan_size; ++i){ 
        eval_form_l[i][0] = out_l[i][0];
        eval_form_l[i][1] = out_l[i][1];
    } 
}
    

void FFTPlan::to_eval_form_scale_l(fftwl_complex* eval_form_l, int64_t *poly){ 
    long double scale = (double)plan_size;
    for(int32_t i = 0; i < N; ++i){ 
        in_l[i] = (long double)poly[i] / (long double)scale; 
        if(ring==RingType::negacyclic){
            in_l[i+N] = -in_l[i]; 
        } 
    }
    for(int32_t i = 0; i < plan_size; ++i){
        out_l[i][0] = 0;
        out_l[i][1] = 0;
    }
    fftwl_execute(plan_to_eval_form_l);  
    for(int32_t i = 0; i < plan_size; ++i){ 
        eval_form_l[i][0] = out_l[i][0];
        eval_form_l[i][1] = out_l[i][1];
    } 
}


void FFTPlan::to_eval_form_scale_l(fftwl_complex* eval_form_l, int64_t *poly, double additional_scale){ 
    long double scale = (double)(plan_size * additional_scale) ;
    for(int32_t i = 0; i < N; ++i){ 
        in_l[i] = (long double)poly[i] / scale; 
        if(ring==RingType::negacyclic){
            in_l[i+N] = -in_l[i]; 
        } 
    }
    for(int32_t i = 0; i < plan_size; ++i){
        out_l[i][0] = 0;
        out_l[i][1] = 0;
    }
    fftwl_execute(plan_to_eval_form_l);  
    for(int32_t i = 0; i < plan_size; ++i){ 
        eval_form_l[i][0] = out_l[i][0];
        eval_form_l[i][1] = out_l[i][1];
    } 
}
  

void FFTPlan::to_coef_form_l(int64_t *coef_form_l, fftwl_complex* eval_form_l){
    for(int32_t i = 0; i < plan_size; ++i){
        out_l[i][0] = eval_form_l[i][0];
        out_l[i][1] = eval_form_l[i][1];
    }
    for(int32_t i = 0; i < plan_size; ++i){
        out_l[i][0] = 0;
        out_l[i][1] = 0;
    }
    fftwl_execute(plan_to_coef_form_l); 
    int32_t copy;
    if(ring == RingType::cyclic){
        copy = plan_size;
    }else if(ring == RingType::negacyclic){
        copy = plan_size/2;
    } 
    for(int32_t i = 0; i < copy; ++i){
        coef_form_l[i] = in_l[i];
    }
}

 
void FFTPlan::add_eval_form_l(fftwl_complex *sum_l, fftwl_complex* in_1_l, fftwl_complex* in_2_l){

    // Add the vectors (Note that its complex multiplication)
    if(ring == RingType::cyclic){
        for(int32_t i = 0; i < plan_size; ++i){
            sum_l[i][0] = in_1_l[i][0] + in_2_l[i][0];
            sum_l[i][1] = in_1_l[i][1] + in_2_l[i][1];
        }
    } else if(ring == RingType::negacyclic){ 
        for(int32_t i = 0; i < plan_size; i+=2){
            sum_l[i][0] = 0.0;
            sum_l[i][1] = 0.0;
            sum_l[i+1][0] = in_1_l[i+1][0] + in_2_l[i+1][0];
            sum_l[i+1][1] = in_1_l[i+1][1] + in_2_l[i+1][1];
        }
    }  
}

void FFTPlan::mul_eval_form_l(fftwl_complex *prod_l, fftwl_complex* in_1_l, fftwl_complex* in_2_l){ 
    // Multiply the vectors (Note that its complex multiplication)
    long double temp_l;  
    if(ring == RingType::cyclic){
        for(int32_t i = 0; i < plan_size; ++i){ 
            temp_l = in_1_l[i][0] * in_2_l[i][0] - in_1_l[i][1] * in_2_l[i][1];
            prod_l[i][1] = in_1_l[i][0] * in_2_l[i][1] + in_1_l[i][1] * in_2_l[i][0];
            prod_l[i][0] = temp_l; 
        }
    } else if(ring == RingType::negacyclic){ 
        int32_t ip = 0;
        int32_t half = plan_size/2; 
        for(int32_t i = 0; i < half; i+=2){ 
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
