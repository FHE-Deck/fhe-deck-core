#include "math/fftw_engine.h"
 
using namespace FHEDeck;

FFTPlan::~FFTPlan(){    
    if(is_init == false){
        return;
    } 
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
    in = (double*) fftw_malloc(sizeof(double) * plan_size);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) *  plan_size);
    plan_to_eval_form = fftw_plan_dft_r2c_1d(plan_size, in, out,  FFTW_PATIENT);
    plan_to_coef_form = fftw_plan_dft_c2r_1d(plan_size, out, in,  FFTW_PATIENT);  
    this->is_init = true;
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
    
  
void FFTPlan::to_eval_form_scale(fftw_complex* eval_form, int64_t *poly){ 
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


FFTWNegacyclicEngine::FFTWNegacyclicEngine(int32_t degree, int64_t coef_modulus){ 
    this->degree = degree;
    this->coef_modulus = coef_modulus; 
    engine = FFTPlan(RingType::negacyclic, degree, false);  
    this->type = PolynomialArithmetic::double_fft;
}

std::shared_ptr<PolynomialEvalForm> FFTWNegacyclicEngine::init_polynomial_eval_form(){
    return std::make_shared<PolynomialEvalFormComplex>(engine.init_fft_poly(), engine.plan_size);
}

std::shared_ptr<PolynomialArrayEvalForm> FFTWNegacyclicEngine::init_polynomial_array_eval_form(int32_t array_size){
    return std::make_shared<PolynomialArrayEvalFormComplex>(this->engine.plan_size, array_size); 
}
  
void FFTWNegacyclicEngine::to_eval(PolynomialEvalForm &out, const Polynomial &in){
    PolynomialEvalFormComplex& out_cast = static_cast<PolynomialEvalFormComplex&>(out);
    std::shared_ptr<Polynomial> input = std::make_shared<Polynomial>(in.degree, in.coef_modulus);
    Utils::array_signed_form(input->vec, in.vec, in.degree, in.coef_modulus); 
    engine.to_eval_form(out_cast.eval, input->vec); 
    out_cast.scale = 1.0;
}
 
void FFTWNegacyclicEngine::to_eval(PolynomialArrayEvalForm &out, const PolynomialArrayCoefForm &in){ 
    PolynomialArrayEvalFormComplex& out_cast = static_cast<PolynomialArrayEvalFormComplex&>(out);
    int64_t *in_poly;
    fftw_complex *out_poly;
    std::shared_ptr<Polynomial> input = std::make_shared<Polynomial>(in.degree, in.coef_modulus);
    for (int32_t i = 0; i < in.array_size; ++i)
    {  
        in_poly = &in.poly_array[i * in.degree];
        Utils::array_signed_form(input->vec, in_poly, in.degree, in.coef_modulus);
        out_poly = &out_cast.eval[i * out_cast.size];    
        engine.to_eval_form(out_poly, in_poly);  
    } 
    out_cast.scale = 1.0;
}

void FFTWNegacyclicEngine::to_coef(Polynomial &out, const PolynomialEvalForm &in){ 
    const PolynomialEvalFormComplex& in_cast = static_cast<const PolynomialEvalFormComplex&>(in);
    engine.to_coef_form_scale(out.vec, in_cast.eval, in_cast.scale); 
    Utils::array_mod_form(out.vec, out.vec, out.degree, out.coef_modulus);
}
  
void FFTWNegacyclicEngine::to_coef(PolynomialArrayCoefForm &out, const PolynomialArrayEvalForm &in){
    const PolynomialArrayEvalFormComplex& in_cast = static_cast<const PolynomialArrayEvalFormComplex&>(in);
    int64_t *out_poly;
    fftw_complex *in_poly;
    for (int32_t i = 0; i < in_cast.array_size; ++i)
    {
        in_poly = &in_cast.eval[i * in_cast.size];
        out_poly = &out.poly_array[i * out.degree];
        engine.to_coef_form_scale(out_poly, in_poly, in_cast.scale);  
        Utils::array_mod_form(out_poly, out_poly, out.degree, out.coef_modulus);
    }
}

void FFTWNegacyclicEngine::mul(PolynomialEvalForm &out, const PolynomialEvalForm &in_1, const PolynomialEvalForm &in_2){
    PolynomialEvalFormComplex& out_cast = static_cast<PolynomialEvalFormComplex&>(out);
    const PolynomialEvalFormComplex& in_1_cast = static_cast<const PolynomialEvalFormComplex&>(in_1);
    const PolynomialEvalFormComplex& in_2_cast = static_cast<const PolynomialEvalFormComplex&>(in_2); 
    engine.mul_eval_form(out_cast.eval, 
            in_1_cast.eval, 
            in_2_cast.eval);  
    out_cast.scale = 2.0 * (in_1_cast.scale * in_2_cast.scale);
}


void FFTWNegacyclicEngine::multisum(Polynomial &out, const PolynomialArrayCoefForm &in_1, const PolynomialArrayEvalForm &in_2){   
    const PolynomialArrayEvalFormComplex& in_2_cast = static_cast<const PolynomialArrayEvalFormComplex&>(in_2);
    int64_t* in_1_temp = in_1.poly_array;
    fftw_complex* in_2_temp = in_2_cast.eval;
    fftw_complex* fft_prod_new = new fftw_complex[in_2_cast.size]; 
    fftw_complex* fft_multisum_eval_new = new fftw_complex[in_2_cast.size]; 
    
    Utils::array_signed_form(in_1_temp, in_1_temp, in_1.degree, in_1.coef_modulus); 
    engine.to_eval_form(fft_multisum_eval_new, in_1_temp);   
    engine.mul_eval_form(fft_multisum_eval_new, fft_multisum_eval_new, in_2_temp);  
 
    for(int32_t i = 1; i < in_2_cast.array_size; ++i){
        in_1_temp = &in_1.poly_array[i * in_1.degree];
        in_2_temp = &in_2_cast.eval[i * in_2_cast.size];
        
        Utils::array_signed_form(in_1_temp, in_1_temp, in_1.degree, in_1.coef_modulus); 
        engine.to_eval_form(fft_prod_new, in_1_temp);  
        engine.mul_eval_form(fft_prod_new, fft_prod_new, in_2_temp); 
        engine.add_eval_form(fft_multisum_eval_new, fft_multisum_eval_new, fft_prod_new); 
    }  
    double scale = in_2_cast.scale * 2.0;
    engine.to_coef_form_scale(out.vec, fft_multisum_eval_new, scale);
    Utils::array_mod_form(out.vec, out.vec, in_1.degree, in_1.coef_modulus); 
    delete[] fft_prod_new; 
    delete[] fft_multisum_eval_new; 
}


void FFTWNegacyclicEngine::multisum(Polynomial &out, const PolynomialArrayEvalForm &in_1, const PolynomialArrayEvalForm &in_2){    
    const PolynomialArrayEvalFormComplex& in_1_cast = static_cast<const PolynomialArrayEvalFormComplex&>(in_1);
    const PolynomialArrayEvalFormComplex& in_2_cast = static_cast<const PolynomialArrayEvalFormComplex&>(in_2);
    fftw_complex* in_1_temp = in_1_cast.eval;
    fftw_complex* in_2_temp = in_2_cast.eval;
    fftw_complex* fft_prod_new = new fftw_complex[in_2_cast.size]; 
    fftw_complex* fft_multisum_eval_new = new fftw_complex[in_2_cast.size]; 
      
    engine.mul_eval_form(fft_multisum_eval_new, in_1_temp, in_2_temp);   
    for(int32_t i = 1; i < in_2_cast.array_size; ++i){
        in_1_temp = &in_1_cast.eval[i * in_1_cast.size];
        in_2_temp = &in_2_cast.eval[i * in_2_cast.size];
         
        engine.mul_eval_form(fft_prod_new, in_1_temp, in_2_temp); 
        engine.add_eval_form(fft_multisum_eval_new, fft_multisum_eval_new, fft_prod_new); 
    } 
    double scale = in_1_cast.scale * in_2_cast.scale * 2.0;
    engine.to_coef_form_scale(out.vec, fft_multisum_eval_new, scale); 
    Utils::array_mod_form(out.vec, out.vec, out.degree, out.coef_modulus); 
    delete[] fft_prod_new; 
    delete[] fft_multisum_eval_new; 
}

   
void FFTWNegacyclicEngine::multisum(Polynomial &out_multisum, PolynomialArrayEvalForm &out_in_1_eval, const PolynomialArrayCoefForm &in_1, const PolynomialArrayEvalForm &in_2){   
    const PolynomialArrayEvalFormComplex& in_2_cast = static_cast<const PolynomialArrayEvalFormComplex&>(in_2);
    PolynomialArrayEvalFormComplex& out_in_1_eval_cast = static_cast<PolynomialArrayEvalFormComplex&>(out_in_1_eval);
    int64_t* in_1_temp = in_1.poly_array;
    fftw_complex* out_eval = out_in_1_eval_cast.eval;
    fftw_complex* in_2_temp = in_2_cast.eval;
    fftw_complex* fft_prod_new = new fftw_complex[in_2_cast.size]; 
    fftw_complex* fft_multisum_eval_new = new fftw_complex[in_2_cast.size]; 
    
    Utils::array_signed_form(in_1_temp, in_1_temp, in_1.degree, in_1.coef_modulus); 
    engine.to_eval_form(out_eval, in_1_temp);   
    engine.mul_eval_form(fft_multisum_eval_new, out_eval, in_2_temp);  
 
    for(int32_t i = 1; i < in_2_cast.array_size; ++i){
        in_1_temp = &in_1.poly_array[i * in_1.degree];
        out_eval = &out_in_1_eval_cast.eval[i * out_in_1_eval_cast.size];
        in_2_temp = &in_2_cast.eval[i * in_2_cast.size];
        
        Utils::array_signed_form(in_1_temp, in_1_temp, in_1.degree, in_1.coef_modulus); 
        engine.to_eval_form(out_eval, in_1_temp);  
        engine.mul_eval_form(fft_prod_new, out_eval, in_2_temp); 
        engine.add_eval_form(fft_multisum_eval_new, fft_multisum_eval_new, fft_prod_new); 
    } 
    double scale =  in_2_cast.scale * 2.0;
    out_in_1_eval_cast.scale = 1.0;
    engine.to_coef_form_scale(out_multisum.vec, fft_multisum_eval_new, scale);
    Utils::array_mod_form(out_multisum.vec, out_multisum.vec, in_1.degree, out_multisum.coef_modulus); 
    delete[] fft_prod_new; 
    delete[] fft_multisum_eval_new; 
}
 
