#include "math/fftw_long_engine.h"
 
using namespace FHEDeck;
 
FFTLongPlan::~FFTLongPlan(){     
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
    engine = std::make_unique<FFTLongPlan>(RingType::negacyclic, degree);  
    this->m_type = PolynomialArithmetic::long_double_fft;
}
  
std::shared_ptr<PolynomialEvalForm> FFTWLongNegacyclicEngine::init_polynomial_eval_form(){
    return std::make_shared<PolynomialEvalFormLongComplex>(engine->plan_size);
}

std::shared_ptr<PolynomialArrayEvalForm> FFTWLongNegacyclicEngine::init_polynomial_array_eval_form(int32_t size){
    return std::make_shared<PolynomialArrayEvalFormLongComplex>(this->engine->plan_size, size);
}
 
void FFTWLongNegacyclicEngine::to_eval(PolynomialEvalForm &out, const Polynomial &in){
    PolynomialEvalFormLongComplex& out_cast = static_cast<PolynomialEvalFormLongComplex&>(out);
    Polynomial input = in; 
    input.signed_form();
    engine->to_eval_form_l(out_cast.get(), input.get()); 
    out_cast.scale(1.0); 
}
 
void FFTWLongNegacyclicEngine::to_eval(PolynomialArrayEvalForm &out, const PolynomialArray &in){
    PolynomialArrayEvalFormLongComplex& out_cast = static_cast<PolynomialArrayEvalFormLongComplex&>(out);  
    for (int32_t i = 0; i < in.size(); ++i)
    {   
        VectorView in_poly = in[i];   
        engine->to_eval_form_l(out_cast[i].data(), in_poly.get());  
    } 
    out_cast.scale(1.0);
} 

void FFTWLongNegacyclicEngine::to_coef(Polynomial &out, const PolynomialEvalForm &in){
    const PolynomialEvalFormLongComplex& in_cast = static_cast<const PolynomialEvalFormLongComplex&>(in);
    engine->to_coef_form_scale_l(out.get(), in_cast.get(), in_cast.scale());  
    out.normalize();
}
  
void FFTWLongNegacyclicEngine::to_coef(PolynomialArray &out, const PolynomialArrayEvalForm &in){
    const PolynomialArrayEvalFormLongComplex& in_cast = static_cast<const PolynomialArrayEvalFormLongComplex&>(in);  
    for (int32_t i = 0; i < in_cast.size(); ++i)
    { 
        VectorView out_poly = out[i];
        engine->to_coef_form_scale_l(out_poly.get(), in_cast[i].data(), in_cast.scale());   
        out_poly.normalize();
    } 
}

void FFTWLongNegacyclicEngine::mul(PolynomialEvalForm &out, const PolynomialEvalForm &in_1, const PolynomialEvalForm &in_2){
    PolynomialEvalFormLongComplex& out_cast = static_cast<PolynomialEvalFormLongComplex&>(out);
    const PolynomialEvalFormLongComplex& in_1_cast = static_cast<const PolynomialEvalFormLongComplex&>(in_1);
    const PolynomialEvalFormLongComplex& in_2_cast = static_cast<const PolynomialEvalFormLongComplex&>(in_2); 
    engine->mul_eval_form_l(out_cast.get(), 
            in_1_cast.get(), 
            in_2_cast.get());  
    out_cast.scale(2.0 * (in_1_cast.scale() * in_2_cast.scale()));

}
  
void FFTWLongNegacyclicEngine::multisum(Polynomial &out, const PolynomialArray &in_1, const PolynomialArrayEvalForm &in_2){
    const PolynomialArrayEvalFormLongComplex& in_2_cast = static_cast<const PolynomialArrayEvalFormLongComplex&>(in_2);
    Vector in_1_temp = in_1[0]; 
    std::unique_ptr<fftwl_complex[]> fft_prod_new = std::make_unique<fftwl_complex[]>(in_2_cast.eval_form_size());
    std::unique_ptr<fftwl_complex[]> fft_multisum_eval_new = std::make_unique<fftwl_complex[]>(in_2_cast.eval_form_size());
    
    in_1_temp.signed_form();
    engine->to_eval_form_l(fft_multisum_eval_new.get(), in_1_temp.get());   
    engine->mul_eval_form_l(fft_multisum_eval_new.get(), fft_multisum_eval_new.get(), in_2_cast[0].data());  
 
    for(int32_t i = 1; i < in_2_cast.size(); ++i){
        Vector in_1_temp = in_1[i]; 
        in_1_temp.signed_form();
        engine->to_eval_form_l(fft_prod_new.get(), in_1_temp.get());  
        engine->mul_eval_form_l(fft_prod_new.get(), fft_prod_new.get(), in_2_cast[i].data()); 
        engine->add_eval_form_l(fft_multisum_eval_new.get(), fft_multisum_eval_new.get(), fft_prod_new.get()); 
    }  
    double scale = in_2_cast.scale() * 2.0;
    engine->to_coef_form_scale_l(out.get(), fft_multisum_eval_new.get(), scale); 
    out.normalize(); 
}

void FFTWLongNegacyclicEngine::multisum(Polynomial &out, const PolynomialArrayEvalForm &in_1, const PolynomialArrayEvalForm &in_2){
    const PolynomialArrayEvalFormLongComplex& in_1_cast = static_cast<const PolynomialArrayEvalFormLongComplex&>(in_1);
    const PolynomialArrayEvalFormLongComplex& in_2_cast = static_cast<const PolynomialArrayEvalFormLongComplex&>(in_2); 
    std::unique_ptr<fftwl_complex[]> fft_prod_new = std::make_unique<fftwl_complex[]>(in_2_cast.eval_form_size());
    std::unique_ptr<fftwl_complex[]> fft_multisum_eval_new = std::make_unique<fftwl_complex[]>(in_2_cast.eval_form_size());
      
    engine->mul_eval_form_l(fft_multisum_eval_new.get(), in_1_cast[0].data(), in_2_cast[0].data());   
    for(int32_t i = 1; i < in_2_cast.size(); ++i){ 
        engine->mul_eval_form_l(fft_prod_new.get(), in_1_cast[i].data(), in_2_cast[i].data()); 
        engine->add_eval_form_l(fft_multisum_eval_new.get(), fft_multisum_eval_new.get(), fft_prod_new.get()); 
    } 
    long double scale = in_1_cast.scale() * in_2_cast.scale() * 2.0;
    engine->to_coef_form_scale_l(out.get(), fft_multisum_eval_new.get(), scale);  
    out.normalize(); 
}

void FFTWLongNegacyclicEngine::multisum(Polynomial &out_multisum, PolynomialArrayEvalForm &out_in_1_eval, const PolynomialArray &in_1, const PolynomialArrayEvalForm &in_2){
    const PolynomialArrayEvalFormLongComplex& in_2_cast = static_cast<const PolynomialArrayEvalFormLongComplex&>(in_2);
    PolynomialArrayEvalFormLongComplex& out_in_1_eval_cast = static_cast<PolynomialArrayEvalFormLongComplex&>(out_in_1_eval);
    Vector in_1_temp = in_1[0]; 
    std::unique_ptr<fftwl_complex[]> fft_prod_new = std::make_unique<fftwl_complex[]>(in_2_cast.eval_form_size());
    std::unique_ptr<fftwl_complex[]> fft_multisum_eval_new = std::make_unique<fftwl_complex[]>(in_2_cast.eval_form_size());
    
    in_1_temp.signed_form();
    engine->to_eval_form_l(out_in_1_eval_cast[0].data(), in_1_temp.get());   
    engine->mul_eval_form_l(fft_multisum_eval_new.get(), out_in_1_eval_cast[0].data(), in_2_cast[0].data());  
 
    for(int32_t i = 1; i < in_2_cast.size(); ++i){
        in_1_temp = in_1[i];
        in_1_temp.signed_form(); 
        engine->to_eval_form_l(out_in_1_eval_cast[i].data(), in_1_temp.get());  
        engine->mul_eval_form_l(fft_prod_new.get(), out_in_1_eval_cast[i].data(), in_2_cast[i].data()); 
        engine->add_eval_form_l(fft_multisum_eval_new.get(), fft_multisum_eval_new.get(), fft_prod_new.get()); 
    } 
    double scale =  in_2_cast.scale() * 2.0;
    out_in_1_eval_cast.scale(1.0);
    engine->to_coef_form_scale_l(out_multisum.get(), fft_multisum_eval_new.get(), scale);  
    out_multisum.normalize(); 
}
   