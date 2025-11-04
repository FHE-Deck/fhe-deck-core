#include "math/fftw_long_engine.h"
 
using namespace FHEDeck;
 
FFTLongPlan::~FFTLongPlan(){    
    if(is_init == false){
        return;
    } 
        fftwl_destroy_plan(plan_to_eval_form_l);
        fftwl_destroy_plan(plan_to_coef_form_l);
        fftwl_free(in_l); 
        fftwl_free(out_l);  
}
  
FFTLongPlan::FFTLongPlan(RingType ring, int32_t N){   
    this->ring = ring;
    this->N = N; 
    init_tables(); 
}
 
FFTLongPlan::FFTLongPlan(RingType ring, int32_t N, bool long_arithmetic){   
    this->ring = ring;
    this->N = N;
    this->long_arithmetic = long_arithmetic;
    init_tables();   
}
 
FFTLongPlan::FFTLongPlan(const FFTLongPlan& other){ 
    this->ring = other.ring;
    this->N = other.N;
    this->long_arithmetic = other.long_arithmetic;
    init_tables();
}

FFTLongPlan& FFTLongPlan::operator=(FFTLongPlan other){ 
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

void FFTLongPlan::init_tables(){
    if(ring == RingType::cyclic){ 
     this->plan_size = N; 
    }else if(ring == RingType::negacyclic){
        this->plan_size = 2*N; 
    }  
    in_l = (long double*) fftw_malloc(sizeof(long double) * plan_size);
    out_l = (fftwl_complex*) fftw_malloc(sizeof(fftwl_complex) *  plan_size);
    plan_to_eval_form_l = fftwl_plan_dft_r2c_1d(plan_size, in_l, out_l,  FFTW_PATIENT);
    plan_to_coef_form_l = fftwl_plan_dft_c2r_1d(plan_size, out_l, in_l,  FFTW_PATIENT);  
    this->is_init = true;
}




fftwl_complex* FFTLongPlan::init_fft_poly_l(){
    return new fftwl_complex[plan_size]; 
}
  


void FFTLongPlan::to_eval_form_l(fftwl_complex* eval_form_l, int64_t *poly){ 
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

void FFTLongPlan::to_eval_form_l(fftwl_complex* eval_form_l, int32_t *poly){ 
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
    

void FFTLongPlan::to_eval_form_scale_l(fftwl_complex* eval_form_l, int64_t *poly){ 
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


void FFTLongPlan::to_eval_form_scale_l(fftwl_complex* eval_form_l, int64_t *poly, long double additional_scale){ 
    long double scale = (long double)(plan_size * additional_scale) ;
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
  

void FFTLongPlan::to_coef_form_l(int64_t *coef_form_l, fftwl_complex* eval_form_l){
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


void FFTLongPlan::to_coef_form_l(long double *coef_form, fftwl_complex* eval_form){
    for(int32_t i = 0; i < plan_size; ++i){
        out_l[i][0] = eval_form[i][0];
        out_l[i][1] = eval_form[i][1];
    }
    fftwl_execute(plan_to_coef_form_l); 
    int32_t copy;
    if(ring == RingType::cyclic){
        copy = plan_size;
    }else if(ring == RingType::negacyclic){
        copy = plan_size/2;
    }
    for(int32_t i = 0; i < copy; ++i){ 
        coef_form[i] = in_l[i];
    }
}


void FFTLongPlan::to_coef_form_scale_l(int64_t *coef_form, fftwl_complex* eval_form, long double additional_scale){
    long double scale = (long double)(plan_size * additional_scale);
    for(int32_t i = 0; i < plan_size; ++i){
        out_l[i][0] = eval_form[i][0];
        out_l[i][1] = eval_form[i][1];
    }
    fftwl_execute(plan_to_coef_form_l);  
    int32_t copy;
    if(ring == RingType::cyclic){
        copy = plan_size;
    }else if(ring == RingType::negacyclic){
        copy = plan_size/2;
    }
    for(int32_t i = 0; i < copy; ++i){ 
        coef_form[i] = (int64_t)round(in_l[i]/scale);
    }
}

void FFTLongPlan::to_coef_form_scale_l(long double *coef_form, fftwl_complex* eval_form, long double additional_scale){
    long double scale = (long double)(plan_size * additional_scale);
    for(int32_t i = 0; i < plan_size; ++i){
        out_l[i][0] = eval_form[i][0];
        out_l[i][1] = eval_form[i][1];
    }
    fftwl_execute(plan_to_coef_form_l); 
    int32_t copy;
    if(ring == RingType::cyclic){
        copy = plan_size;
    }else if(ring == RingType::negacyclic){
        copy = plan_size/2;
    }
    for(int32_t i = 0; i < copy; ++i){ 
        coef_form[i] = in_l[i]/scale;
    }
}
 
void FFTLongPlan::add_eval_form_l(fftwl_complex *sum_l, fftwl_complex* in_1_l, fftwl_complex* in_2_l){

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

void FFTLongPlan::mul_eval_form_l(fftwl_complex *prod_l, fftwl_complex* in_1_l, fftwl_complex* in_2_l){ 
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


FFTWLongNegacyclicEngine::FFTWLongNegacyclicEngine(int32_t degree, int64_t coef_modulus){ 
    this->degree = degree;
    this->coef_modulus = coef_modulus; 
    engine = FFTLongPlan(RingType::negacyclic, degree, true);  
    this->type = PolynomialArithmetic::long_double_fft;
}
  
std::shared_ptr<PolynomialEvalForm> FFTWLongNegacyclicEngine::init_polynomial_eval_form(){
    return std::make_shared<PolynomialEvalFormLongComplex>(engine.init_fft_poly_l(), engine.plan_size);
}

std::shared_ptr<PolynomialArrayEvalForm> FFTWLongNegacyclicEngine::init_polynomial_array_eval_form(int32_t size){
    return std::make_shared<PolynomialArrayEvalFormLongComplex>(this->engine.plan_size, size);
}
 
void FFTWLongNegacyclicEngine::to_eval(PolynomialEvalForm &out, const Polynomial &in){
    PolynomialEvalFormLongComplex& out_cast = static_cast<PolynomialEvalFormLongComplex&>(out);
    std::shared_ptr<Polynomial> input = std::make_shared<Polynomial>(in.size, in.modulus);
    Utils::array_signed_form(input->vec, in.vec, in.size, in.modulus); 
    engine.to_eval_form_l(out_cast.eval, input->vec); 
    out_cast.scale = 1.0;
 
}
 
void FFTWLongNegacyclicEngine::to_eval(PolynomialArrayEvalForm &out, const PolynomialArrayCoefForm &in){
    PolynomialArrayEvalFormLongComplex& out_cast = static_cast<PolynomialArrayEvalFormLongComplex&>(out);
    int64_t *in_poly;
    fftwl_complex *out_poly;
    std::shared_ptr<Polynomial> input = std::make_shared<Polynomial>(in.size, in.modulus);
    for (int32_t i = 0; i < in.array_size; ++i)
    {  
        in_poly = &in.vec_array[i * in.size];
        Utils::array_signed_form(input->vec, in_poly, in.size, in.modulus);
        out_poly = &out_cast.eval[i * out_cast.size];   
        engine.to_eval_form_l(out_poly, in_poly);  
    } 
    out_cast.scale = 1.0;
} 

void FFTWLongNegacyclicEngine::to_coef(Polynomial &out, const PolynomialEvalForm &in){
    const PolynomialEvalFormLongComplex& in_cast = static_cast<const PolynomialEvalFormLongComplex&>(in);
    engine.to_coef_form_scale_l(out.vec, in_cast.eval, in_cast.scale); 
    //Utils::array_mod_form(out.vec, out.vec, out.size, out.modulus);
    out.normalize();
}
  
void FFTWLongNegacyclicEngine::to_coef(PolynomialArrayCoefForm &out, const PolynomialArrayEvalForm &in){
    const PolynomialArrayEvalFormLongComplex& in_cast = static_cast<const PolynomialArrayEvalFormLongComplex&>(in);
    int64_t *out_poly;
    fftwl_complex *in_poly;
    for (int32_t i = 0; i < in_cast.array_size; ++i)
    {
        in_poly = &in_cast.eval[i * in_cast.size];
        out_poly = &out.vec_array[i * out.size];
        engine.to_coef_form_scale_l(out_poly, in_poly, in_cast.scale);  
        //Utils::array_mod_form(out_poly, out_poly, out.size, out.modulus);
    }
    /// NOTE: Similar as with fftw_engine, normalizing here destroys data locality.
    /// Perhpas its better to do it in to_coef_form_scale_l?
    out.normalize();
}

void FFTWLongNegacyclicEngine::mul(PolynomialEvalForm &out, const PolynomialEvalForm &in_1, const PolynomialEvalForm &in_2){
    PolynomialEvalFormLongComplex& out_cast = static_cast<PolynomialEvalFormLongComplex&>(out);
    const PolynomialEvalFormLongComplex& in_1_cast = static_cast<const PolynomialEvalFormLongComplex&>(in_1);
    const PolynomialEvalFormLongComplex& in_2_cast = static_cast<const PolynomialEvalFormLongComplex&>(in_2); 
    engine.mul_eval_form_l(out_cast.eval, 
            in_1_cast.eval, 
            in_2_cast.eval);  
    out_cast.scale = 2.0 * (in_1_cast.scale * in_2_cast.scale);

}
  
void FFTWLongNegacyclicEngine::multisum(Polynomial &out, const PolynomialArrayCoefForm &in_1, const PolynomialArrayEvalForm &in_2){
    const PolynomialArrayEvalFormLongComplex& in_2_cast = static_cast<const PolynomialArrayEvalFormLongComplex&>(in_2);
    int64_t* in_1_temp = in_1.vec_array;
    fftwl_complex* in_2_temp = in_2_cast.eval;
    fftwl_complex* fft_prod_new = new fftwl_complex[in_2_cast.size]; 
    fftwl_complex* fft_multisum_eval_new = new fftwl_complex[in_2_cast.size]; 
    
    Utils::array_signed_form(in_1_temp, in_1_temp, in_1.size, in_1.modulus); 
    engine.to_eval_form_l(fft_multisum_eval_new, in_1_temp);   
    engine.mul_eval_form_l(fft_multisum_eval_new, fft_multisum_eval_new, in_2_temp);  
 
    for(int32_t i = 1; i < in_2_cast.array_size; ++i){
        in_1_temp = &in_1.vec_array[i * in_1.size];
        in_2_temp = &in_2_cast.eval[i * in_2_cast.size];
        
        Utils::array_signed_form(in_1_temp, in_1_temp, in_1.size, in_1.modulus); 
        engine.to_eval_form_l(fft_prod_new, in_1_temp);  
        engine.mul_eval_form_l(fft_prod_new, fft_prod_new, in_2_temp); 
        engine.add_eval_form_l(fft_multisum_eval_new, fft_multisum_eval_new, fft_prod_new); 
    }  
    double scale = in_2_cast.scale * 2.0;
    engine.to_coef_form_scale_l(out.vec, fft_multisum_eval_new, scale);
    //Utils::array_mod_form(out.vec, out.vec, in_1.size, in_1.modulus); 
    out.normalize();
    delete[] fft_prod_new; 
    delete[] fft_multisum_eval_new; 

}

void FFTWLongNegacyclicEngine::multisum(Polynomial &out, const PolynomialArrayEvalForm &in_1, const PolynomialArrayEvalForm &in_2){
    const PolynomialArrayEvalFormLongComplex& in_1_cast = static_cast<const PolynomialArrayEvalFormLongComplex&>(in_1);
    const PolynomialArrayEvalFormLongComplex& in_2_cast = static_cast<const PolynomialArrayEvalFormLongComplex&>(in_2);
    fftwl_complex* in_1_temp = in_1_cast.eval;
    fftwl_complex* in_2_temp = in_2_cast.eval;
    fftwl_complex* fft_prod_new = new fftwl_complex[in_2_cast.size]; 
    fftwl_complex* fft_multisum_eval_new = new fftwl_complex[in_2_cast.size]; 
      
    engine.mul_eval_form_l(fft_multisum_eval_new, in_1_temp, in_2_temp);   
    for(int32_t i = 1; i < in_2_cast.array_size; ++i){
        in_1_temp = &in_1_cast.eval[i * in_1_cast.size];
        in_2_temp = &in_2_cast.eval[i * in_2_cast.size];
         
        engine.mul_eval_form_l(fft_prod_new, in_1_temp, in_2_temp); 
        engine.add_eval_form_l(fft_multisum_eval_new, fft_multisum_eval_new, fft_prod_new); 
    } 
    long double scale = in_1_cast.scale * in_2_cast.scale * 2.0;
    engine.to_coef_form_scale_l(out.vec, fft_multisum_eval_new, scale); 
    //Utils::array_mod_form(out.vec, out.vec, out.size, out.modulus); 
    out.normalize();
    delete[] fft_prod_new; 
    delete[] fft_multisum_eval_new; 

}

void FFTWLongNegacyclicEngine::multisum(Polynomial &out_multisum, PolynomialArrayEvalForm &out_in_1_eval, const PolynomialArrayCoefForm &in_1, const PolynomialArrayEvalForm &in_2){
    const PolynomialArrayEvalFormLongComplex& in_2_cast = static_cast<const PolynomialArrayEvalFormLongComplex&>(in_2);
    PolynomialArrayEvalFormLongComplex& out_in_1_eval_cast = static_cast<PolynomialArrayEvalFormLongComplex&>(out_in_1_eval);
    int64_t* in_1_temp = in_1.vec_array;
    fftwl_complex* out_eval = out_in_1_eval_cast.eval;
    fftwl_complex* in_2_temp = in_2_cast.eval;
    fftwl_complex* fft_prod_new = new fftwl_complex[in_2_cast.size]; 
    fftwl_complex* fft_multisum_eval_new = new fftwl_complex[in_2_cast.size]; 
    
    Utils::array_signed_form(in_1_temp, in_1_temp, in_1.size, in_1.modulus); 
    engine.to_eval_form_l(out_eval, in_1_temp);   
    engine.mul_eval_form_l(fft_multisum_eval_new, out_eval, in_2_temp);  
 
    for(int32_t i = 1; i < in_2_cast.array_size; ++i){
        in_1_temp = &in_1.vec_array[i * in_1.size];
        out_eval = &out_in_1_eval_cast.eval[i * out_in_1_eval_cast.size];
        in_2_temp = &in_2_cast.eval[i * in_2_cast.size];
        
        Utils::array_signed_form(in_1_temp, in_1_temp, in_1.size, in_1.modulus); 
        engine.to_eval_form_l(out_eval, in_1_temp);  
        engine.mul_eval_form_l(fft_prod_new, out_eval, in_2_temp); 
        engine.add_eval_form_l(fft_multisum_eval_new, fft_multisum_eval_new, fft_prod_new); 
    } 
    double scale =  in_2_cast.scale * 2.0;
    out_in_1_eval_cast.scale = 1.0;
    engine.to_coef_form_scale_l(out_multisum.vec, fft_multisum_eval_new, scale); 
    //Utils::array_mod_form(out_multisum.vec, out_multisum.vec, in_1.size, out_multisum.modulus); 
    out_multisum.normalize();
    delete[] fft_prod_new; 
    delete[] fft_multisum_eval_new; 

}
   