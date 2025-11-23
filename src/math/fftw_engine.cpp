#include "math/fftw_engine.h"
 
using namespace FHEDeck;

FFTPlan::~FFTPlan(){     
    fftw_destroy_plan(plan_to_eval_form);
    fftw_destroy_plan(plan_to_coef_form);
    fftw_free(in); 
    fftw_free(out);   
}
 
 
FFTPlan::FFTPlan(RingType ring, int32_t N){   
    this->ring = ring;
    this->N = N; 
    init_tables(); 
}
  
void FFTPlan::init_tables(){
    if(ring == RingType::cyclic){ 
     this->plan_size = N; 
    }else if(ring == RingType::negacyclic){
        this->plan_size = 2*N; 
    }  
    in = (double*) fftw_malloc(sizeof(double) * plan_size);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) *  plan_size);
    plan_to_eval_form = fftw_plan_dft_r2c_1d(plan_size, in, out,  FFTW_PATIENT);
    plan_to_coef_form = fftw_plan_dft_c2r_1d(plan_size, out, in,  FFTW_PATIENT);   
}
 
fftw_complex* FFTPlan::init_fft_poly(){
    return new fftw_complex[plan_size]; 
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


FFTWNegacyclicEngine::FFTWNegacyclicEngine(int32_t degree, int64_t coef_modulus){ 
    this->degree = degree;
    this->coef_modulus = coef_modulus; 
    engine = std::make_unique<FFTPlan>(RingType::negacyclic, degree);  
    this->type = PolynomialArithmetic::double_fft;
}

std::shared_ptr<PolynomialEvalForm> FFTWNegacyclicEngine::init_polynomial_eval_form(){
    return std::make_shared<PolynomialEvalFormComplex>(engine->init_fft_poly(), engine->plan_size);
}

std::shared_ptr<PolynomialArrayEvalForm> FFTWNegacyclicEngine::init_polynomial_array_eval_form(int32_t array_size){
    return std::make_shared<PolynomialArrayEvalFormComplex>(this->engine->plan_size, array_size); 
}
  
void FFTWNegacyclicEngine::to_eval(PolynomialEvalForm &out, const Polynomial &in){
    PolynomialEvalFormComplex& out_cast = static_cast<PolynomialEvalFormComplex&>(out);
    Polynomial input = in; 
    input.signed_form();
    engine->to_eval_form(out_cast.eval, input.get()); 
    out_cast.scale = 1.0;
}
 
void FFTWNegacyclicEngine::to_eval(PolynomialArrayEvalForm &out, const PolynomialArray &in){ 
    PolynomialArrayEvalFormComplex& out_cast = static_cast<PolynomialArrayEvalFormComplex&>(out);  
    for (int32_t i = 0; i < in.array_size; ++i)
    {   
        const VectorView in_poly = in[i];    
        engine->to_eval_form(out_cast[i].get(), in_poly.get());  
    } 
    out_cast.scale = 1.0;
}

void FFTWNegacyclicEngine::to_coef(Polynomial &out, const PolynomialEvalForm &in){ 
    const PolynomialEvalFormComplex& in_cast = static_cast<const PolynomialEvalFormComplex&>(in);
    engine->to_coef_form_scale(out.get(), in_cast.eval, in_cast.scale);  
    out.normalize();
}
  
void FFTWNegacyclicEngine::to_coef(PolynomialArray &out, const PolynomialArrayEvalForm &in){
    const PolynomialArrayEvalFormComplex& in_cast = static_cast<const PolynomialArrayEvalFormComplex&>(in);  
    for (int32_t i = 0; i < in_cast.array_size; ++i)
    { 
        VectorView out_poly = out[i];
        engine->to_coef_form_scale(out_poly.get(), in_cast[i].get(), in_cast.scale);   
        out_poly.normalize();
    }  
}

void FFTWNegacyclicEngine::mul(PolynomialEvalForm &out, const PolynomialEvalForm &in_1, const PolynomialEvalForm &in_2){
    PolynomialEvalFormComplex& out_cast = static_cast<PolynomialEvalFormComplex&>(out);
    const PolynomialEvalFormComplex& in_1_cast = static_cast<const PolynomialEvalFormComplex&>(in_1);
    const PolynomialEvalFormComplex& in_2_cast = static_cast<const PolynomialEvalFormComplex&>(in_2); 
    engine->mul_eval_form(out_cast.eval, 
            in_1_cast.eval, 
            in_2_cast.eval);  
    out_cast.scale = 2.0 * (in_1_cast.scale * in_2_cast.scale);
}
 
void FFTWNegacyclicEngine::multisum(Polynomial &out, const PolynomialArray &in_1, const PolynomialArrayEvalForm &in_2){   
    const PolynomialArrayEvalFormComplex& in_2_cast = static_cast<const PolynomialArrayEvalFormComplex&>(in_2); 
    Vector in_1_temp = in_1[0]; 
    std::unique_ptr<fftw_complex[]> fft_prod_new = std::make_unique<fftw_complex[]>(in_2_cast.size);
    std::unique_ptr<fftw_complex[]> fft_multisum_eval_new = std::make_unique<fftw_complex[]>(in_2_cast.size);
    
    in_1_temp.signed_form();
    engine->to_eval_form(fft_multisum_eval_new.get(), in_1_temp.get());   
    engine->mul_eval_form(fft_multisum_eval_new.get(), fft_multisum_eval_new.get(), in_2_cast[0].get());  
 
    for(int32_t i = 1; i < in_2_cast.array_size; ++i){ 
        Vector in_1_temp = in_1[i]; 
        in_1_temp.signed_form();
        engine->to_eval_form(fft_prod_new.get(), in_1_temp.get());  
        engine->mul_eval_form(fft_prod_new.get(), fft_prod_new.get(), in_2_cast[i].get()); 
        engine->add_eval_form(fft_multisum_eval_new.get(), fft_multisum_eval_new.get(), fft_prod_new.get()); 
    }  
    double scale = in_2_cast.scale * 2.0;
    engine->to_coef_form_scale(out.get(), fft_multisum_eval_new.get(), scale); 
    out.normalize();
}
 
void FFTWNegacyclicEngine::multisum(Polynomial &out, const PolynomialArrayEvalForm &in_1, const PolynomialArrayEvalForm &in_2){    
    const PolynomialArrayEvalFormComplex& in_1_cast = static_cast<const PolynomialArrayEvalFormComplex&>(in_1);
    const PolynomialArrayEvalFormComplex& in_2_cast = static_cast<const PolynomialArrayEvalFormComplex&>(in_2); 
    std::unique_ptr<fftw_complex[]> fft_prod_new = std::make_unique<fftw_complex[]>(in_2_cast.size);
    std::unique_ptr<fftw_complex[]> fft_multisum_eval_new = std::make_unique<fftw_complex[]>(in_2_cast.size);
      
    engine->mul_eval_form(fft_multisum_eval_new.get(), in_1_cast[0].get(), in_2_cast[0].get());   
    for(int32_t i = 1; i < in_2_cast.array_size; ++i){ 
         
        engine->mul_eval_form(fft_prod_new.get(), in_1_cast[i].get(), in_2_cast[i].get()); 
        engine->add_eval_form(fft_multisum_eval_new.get(), fft_multisum_eval_new.get(), fft_prod_new.get()); 
    } 
    double scale = in_1_cast.scale * in_2_cast.scale * 2.0;
    engine->to_coef_form_scale(out.get(), fft_multisum_eval_new.get(), scale);  
    out.normalize(); 
}
 
void FFTWNegacyclicEngine::multisum(Polynomial &out_multisum, PolynomialArrayEvalForm &out_in_1_eval, const PolynomialArray &in_1, const PolynomialArrayEvalForm &in_2){   
    const PolynomialArrayEvalFormComplex& in_2_cast = static_cast<const PolynomialArrayEvalFormComplex&>(in_2);
    PolynomialArrayEvalFormComplex& out_in_1_eval_cast = static_cast<PolynomialArrayEvalFormComplex&>(out_in_1_eval);
    Vector in_1_temp = in_1[0]; 
    std::unique_ptr<fftw_complex[]> fft_prod_new = std::make_unique<fftw_complex[]>(in_2_cast.size);
    std::unique_ptr<fftw_complex[]> fft_multisum_eval_new = std::make_unique<fftw_complex[]>(in_2_cast.size);
    
    in_1_temp.signed_form();
    engine->to_eval_form(out_in_1_eval_cast[0].get(), in_1_temp.get());   
    engine->mul_eval_form(fft_multisum_eval_new.get(), out_in_1_eval_cast[0].get(), in_2_cast[0].get());  
 
    for(int32_t i = 1; i < in_2_cast.array_size; ++i){
        Vector in_1_temp = in_1[i]; 
        in_1_temp.signed_form();
        engine->to_eval_form(out_in_1_eval_cast[i].get(), in_1_temp.get());  
        engine->mul_eval_form(fft_prod_new.get(), out_in_1_eval_cast[i].get(), in_2_cast[i].get()); 
        engine->add_eval_form(fft_multisum_eval_new.get(), fft_multisum_eval_new.get(), fft_prod_new.get()); 
    } 
    double scale =  in_2_cast.scale * 2.0;
    out_in_1_eval_cast.scale = 1.0;
    engine->to_coef_form_scale(out_multisum.get(), fft_multisum_eval_new.get(), scale); 
    out_multisum.normalize();
}
 
