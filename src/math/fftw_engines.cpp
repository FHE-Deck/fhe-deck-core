#include "fftw_engines.h"

using namespace fhe_deck;



FFTWNegacyclicEngine::FFTWNegacyclicEngine(int32_t degree, int64_t coef_modulus){ 
    this->degree = degree;
    this->coef_modulus = coef_modulus; 
    this->type = double_fft;
    engine = FFTPlan(negacyclic, degree, false);  
}

PolynomialEvalForm* FFTWNegacyclicEngine::init_polynomial_eval_form(){
    return new PolynomialEvalFormFFTWComplex(engine.init_fft_poly(), engine.plan_size);
}

PolynomialArrayEvalForm* FFTWNegacyclicEngine::init_polynomial_array_eval_form(int32_t array_size){
    return new PolynomialArrayEvalFormFFTWComplex(this->engine.plan_size, array_size); 
}
  
void FFTWNegacyclicEngine::to_eval(PolynomialEvalForm &out, Polynomial &in){
    PolynomialEvalFormFFTWComplex& out_cast = static_cast<PolynomialEvalFormFFTWComplex&>(out);
    std::shared_ptr<Polynomial> input = std::make_shared<Polynomial>(in.degree, in.coef_modulus);
    Utils::array_signed_form(input->coefs, in.coefs, in.degree, in.coef_modulus); 
    engine.to_eval_form(out_cast.eval_fftw, input->coefs); 
    out_cast.scale = 1.0;
}
 
void FFTWNegacyclicEngine::to_eval(PolynomialArrayEvalForm &out, PolynomialArrayCoefForm &in){ 
    PolynomialArrayEvalFormFFTWComplex& out_cast = static_cast<PolynomialArrayEvalFormFFTWComplex&>(out);
    int64_t *in_poly;
    fftw_complex *out_poly;
    std::shared_ptr<Polynomial> input = std::make_shared<Polynomial>(in.degree, in.coef_modulus);
    for (int32_t i = 0; i < in.array_size; ++i)
    {  
        in_poly = &in.poly_array[i * in.degree];
        Utils::array_signed_form(input->coefs, in_poly, in.degree, in.coef_modulus);
        out_poly = &out_cast.eval_fftw[i * out_cast.size];  
        //engine.to_eval_form_scale(out_poly, in_poly, 2.0);  
        engine.to_eval_form(out_poly, in_poly);  
    } 
    out_cast.scale = 1.0;
}

void FFTWNegacyclicEngine::to_coef(Polynomial &out, PolynomialEvalForm &in){ 
    PolynomialEvalFormFFTWComplex& in_cast = static_cast<PolynomialEvalFormFFTWComplex&>(in);
    engine.to_coef_form_scale(out.coefs, in_cast.eval_fftw, in_cast.scale); 
    Utils::array_mod_form(out.coefs, out.coefs, out.degree, out.coef_modulus);
}
  
void FFTWNegacyclicEngine::to_coef(PolynomialArrayCoefForm &out, PolynomialArrayEvalForm &in){
    PolynomialArrayEvalFormFFTWComplex& in_cast = static_cast<PolynomialArrayEvalFormFFTWComplex&>(in);
    int64_t *out_poly;
    fftw_complex *in_poly;
    for (int32_t i = 0; i < in_cast.array_size; ++i)
    {
        in_poly = &in_cast.eval_fftw[i * in_cast.size];
        out_poly = &out.poly_array[i * out.degree];
        engine.to_coef_form_scale(out_poly, in_poly, in_cast.scale);  
        Utils::array_mod_form(out_poly, out_poly, out.degree, out.coef_modulus);
    }
}

void FFTWNegacyclicEngine::mul(PolynomialEvalForm &out, PolynomialEvalForm &in_1, PolynomialEvalForm &in_2){
    PolynomialEvalFormFFTWComplex& out_cast = static_cast<PolynomialEvalFormFFTWComplex&>(out);
    PolynomialEvalFormFFTWComplex& in_1_cast = static_cast<PolynomialEvalFormFFTWComplex&>(in_1);
    PolynomialEvalFormFFTWComplex& in_2_cast = static_cast<PolynomialEvalFormFFTWComplex&>(in_2); 
    engine.mul_eval_form(out_cast.eval_fftw, 
            in_1_cast.eval_fftw, 
            in_2_cast.eval_fftw);  
    out_cast.scale = 2.0 * (in_1_cast.scale * in_2_cast.scale);
}


void FFTWNegacyclicEngine::multisum(Polynomial &out, PolynomialArrayCoefForm &in_1, PolynomialArrayEvalForm &in_2){   
    PolynomialArrayEvalFormFFTWComplex& in_2_cast = static_cast<PolynomialArrayEvalFormFFTWComplex&>(in_2);
    int64_t* in_1_temp = in_1.poly_array;
    fftw_complex* in_2_temp = in_2_cast.eval_fftw;
    fftw_complex* fft_prod_new = new fftw_complex[in_2_cast.size]; 
    fftw_complex* fft_multisum_eval_new = new fftw_complex[in_2_cast.size]; 
    
    Utils::array_signed_form(in_1_temp, in_1_temp, in_1.degree, in_1.coef_modulus); 
    engine.to_eval_form(fft_multisum_eval_new, in_1_temp);   
    engine.mul_eval_form(fft_multisum_eval_new, fft_multisum_eval_new, in_2_temp);  
 
    for(int32_t i = 1; i < in_2_cast.array_size; ++i){
        in_1_temp = &in_1.poly_array[i * in_1.degree];
        in_2_temp = &in_2_cast.eval_fftw[i * in_2_cast.size];
        
        Utils::array_signed_form(in_1_temp, in_1_temp, in_1.degree, in_1.coef_modulus); 
        engine.to_eval_form(fft_prod_new, in_1_temp);  
        engine.mul_eval_form(fft_prod_new, fft_prod_new, in_2_temp); 
        engine.add_eval_form(fft_multisum_eval_new, fft_multisum_eval_new, fft_prod_new); 
    }  
    double scale = in_2_cast.scale * 2.0;
    engine.to_coef_form_scale(out.coefs, fft_multisum_eval_new, scale);
    Utils::array_mod_form(out.coefs, out.coefs, in_1.degree, in_1.coef_modulus); 
    delete[] fft_prod_new; 
    delete[] fft_multisum_eval_new; 
}


void FFTWNegacyclicEngine::multisum(Polynomial &out, PolynomialArrayEvalForm &in_1, PolynomialArrayEvalForm &in_2){    
    PolynomialArrayEvalFormFFTWComplex& in_1_cast = static_cast<PolynomialArrayEvalFormFFTWComplex&>(in_1);
    PolynomialArrayEvalFormFFTWComplex& in_2_cast = static_cast<PolynomialArrayEvalFormFFTWComplex&>(in_2);
    fftw_complex* in_1_temp = in_1_cast.eval_fftw;
    fftw_complex* in_2_temp = in_2_cast.eval_fftw;
    fftw_complex* fft_prod_new = new fftw_complex[in_2_cast.size]; 
    fftw_complex* fft_multisum_eval_new = new fftw_complex[in_2_cast.size]; 
      
    engine.mul_eval_form(fft_multisum_eval_new, in_1_temp, in_2_temp);   
    for(int32_t i = 1; i < in_2_cast.array_size; ++i){
        in_1_temp = &in_1_cast.eval_fftw[i * in_1_cast.size];
        in_2_temp = &in_2_cast.eval_fftw[i * in_2_cast.size];
         
        engine.mul_eval_form(fft_prod_new, in_1_temp, in_2_temp); 
        engine.add_eval_form(fft_multisum_eval_new, fft_multisum_eval_new, fft_prod_new); 
    } 
    double scale = in_1_cast.scale * in_2_cast.scale * 2.0;
    engine.to_coef_form_scale(out.coefs, fft_multisum_eval_new, scale); 
    Utils::array_mod_form(out.coefs, out.coefs, out.degree, out.coef_modulus); 
    delete[] fft_prod_new; 
    delete[] fft_multisum_eval_new; 
}

   
void FFTWNegacyclicEngine::multisum(Polynomial &out_multisum, PolynomialArrayEvalForm &out_in_1_eval, PolynomialArrayCoefForm &in_1, PolynomialArrayEvalForm &in_2){   
    PolynomialArrayEvalFormFFTWComplex& in_2_cast = static_cast<PolynomialArrayEvalFormFFTWComplex&>(in_2);
    PolynomialArrayEvalFormFFTWComplex& out_in_1_eval_cast = static_cast<PolynomialArrayEvalFormFFTWComplex&>(out_in_1_eval);
    int64_t* in_1_temp = in_1.poly_array;
    fftw_complex* out_eval = out_in_1_eval_cast.eval_fftw;
    fftw_complex* in_2_temp = in_2_cast.eval_fftw;
    fftw_complex* fft_prod_new = new fftw_complex[in_2_cast.size]; 
    fftw_complex* fft_multisum_eval_new = new fftw_complex[in_2_cast.size]; 
    
    Utils::array_signed_form(in_1_temp, in_1_temp, in_1.degree, in_1.coef_modulus); 
    engine.to_eval_form(out_eval, in_1_temp);   
    engine.mul_eval_form(fft_multisum_eval_new, out_eval, in_2_temp);  
 
    for(int32_t i = 1; i < in_2_cast.array_size; ++i){
        in_1_temp = &in_1.poly_array[i * in_1.degree];
        out_eval = &out_in_1_eval_cast.eval_fftw[i * out_in_1_eval_cast.size];
        in_2_temp = &in_2_cast.eval_fftw[i * in_2_cast.size];
        
        Utils::array_signed_form(in_1_temp, in_1_temp, in_1.degree, in_1.coef_modulus); 
        engine.to_eval_form(out_eval, in_1_temp);  
        engine.mul_eval_form(fft_prod_new, out_eval, in_2_temp); 
        engine.add_eval_form(fft_multisum_eval_new, fft_multisum_eval_new, fft_prod_new); 
    } 
    double scale =  in_2_cast.scale * 2.0;
    out_in_1_eval_cast.scale = 1.0;
    engine.to_coef_form_scale(out_multisum.coefs, fft_multisum_eval_new, scale);
    Utils::array_mod_form(out_multisum.coefs, out_multisum.coefs, in_1.degree, out_multisum.coef_modulus); 
    delete[] fft_prod_new; 
    delete[] fft_multisum_eval_new; 
}
 



FFTWLongNegacyclicEngine::FFTWLongNegacyclicEngine(int32_t degree, int64_t coef_modulus){ 
    this->degree = degree;
    this->coef_modulus = coef_modulus; 
    engine = FFTPlan(negacyclic, degree, true);  
    this->type = long_double_fft;
}
  
PolynomialEvalForm* FFTWLongNegacyclicEngine::init_polynomial_eval_form(){
    return new PolynomialEvalFormFFTWLongComplex(engine.init_fft_poly_l(), engine.plan_size);
}

PolynomialArrayEvalForm* FFTWLongNegacyclicEngine::init_polynomial_array_eval_form(int32_t size){
    return new PolynomialArrayEvalFormFFTWLongComplex(this->engine.plan_size, size);
}
 
void FFTWLongNegacyclicEngine::to_eval(PolynomialEvalForm &out, Polynomial &in){
    PolynomialEvalFormFFTWLongComplex& out_cast = static_cast<PolynomialEvalFormFFTWLongComplex&>(out);
    engine.to_eval_form_l(out_cast.eval_fftwl, in.coefs);   
}
 
void FFTWLongNegacyclicEngine::to_eval(PolynomialArrayEvalForm &out, PolynomialArrayCoefForm &in){
    PolynomialArrayEvalFormFFTWLongComplex& out_cast = static_cast<PolynomialArrayEvalFormFFTWLongComplex&>(out);
    int64_t *in_poly;
    fftwl_complex *out_poly;
    for (int32_t i = 0; i < in.array_size; ++i)
    {
        in_poly = &in.poly_array[i * in.degree];
        out_poly = &out_cast.eval_fftwl[i * out_cast.size];
        engine.to_eval_form_l(out_poly, in_poly); 
    }
} 

void FFTWLongNegacyclicEngine::to_coef(Polynomial &out, PolynomialEvalForm &in){
    PolynomialEvalFormFFTWLongComplex& in_cast = static_cast<PolynomialEvalFormFFTWLongComplex&>(in);
    engine.to_coef_form_l(out.coefs, in_cast.eval_fftwl);   
        long double scale = (long double)(engine.plan_size * 2);
        for(int32_t i = 0; i < degree; ++i){   
            out.coefs[i] = roundl((long double)out.coefs[i] / scale); 
        } 
}
  
void FFTWLongNegacyclicEngine::to_coef(PolynomialArrayCoefForm &out, PolynomialArrayEvalForm &in){
    PolynomialArrayEvalFormFFTWLongComplex& in_cast = static_cast<PolynomialArrayEvalFormFFTWLongComplex&>(in);
    int64_t *out_poly;
    fftwl_complex *in_poly;
    for (int32_t i = 0; i < in_cast.array_size; ++i)
    {
        in_poly = &in_cast.eval_fftwl[i * in_cast.size];
        out_poly = &out.poly_array[i * out.degree];
        engine.to_coef_form_l(out_poly, in_poly); 
    }
}

void FFTWLongNegacyclicEngine::mul(PolynomialEvalForm &out, PolynomialEvalForm &in_1, PolynomialEvalForm &in_2){
    PolynomialEvalFormFFTWLongComplex& out_cast = static_cast<PolynomialEvalFormFFTWLongComplex&>(out);
    PolynomialEvalFormFFTWLongComplex& in_1_cast = static_cast<PolynomialEvalFormFFTWLongComplex&>(in_1);
    PolynomialEvalFormFFTWLongComplex& in_2_cast = static_cast<PolynomialEvalFormFFTWLongComplex&>(in_2);
    engine.mul_eval_form_l(out_cast.eval_fftwl, in_1_cast.eval_fftwl, in_2_cast.eval_fftwl);
}
  
void FFTWLongNegacyclicEngine::multisum(Polynomial &out, PolynomialArrayCoefForm &in_1, PolynomialArrayEvalForm &in_2){
    PolynomialArrayEvalFormFFTWLongComplex& in_2_cast = static_cast<PolynomialArrayEvalFormFFTWLongComplex&>(in_2);
    int64_t* in_1_temp = in_1.poly_array;
    fftwl_complex* in_2_temp = in_2_cast.eval_fftwl;
    fftwl_complex* fft_prod_new = new fftwl_complex[in_2_cast.size]; 
    fftwl_complex* fft_multisum_eval_new = new fftwl_complex[in_2_cast.size]; 
    
    engine.to_eval_form_l(fft_multisum_eval_new, in_1_temp);   
    engine.mul_eval_form_l(fft_multisum_eval_new, fft_multisum_eval_new, in_2_temp);  
 
    for(int32_t i = 1; i < in_2_cast.array_size; ++i){
        in_1_temp = &in_1.poly_array[i * in_1.degree];
        in_2_temp = &in_2_cast.eval_fftwl[i * in_2_cast.size];
        
        engine.to_eval_form_l(fft_prod_new, in_1_temp);  
        engine.mul_eval_form_l(fft_prod_new, fft_prod_new, in_2_temp); 
        engine.add_eval_form_l(fft_multisum_eval_new, fft_multisum_eval_new, fft_prod_new); 
    }
    engine.to_coef_form_l(out.coefs, fft_multisum_eval_new);
    Utils::array_mod_form(out.coefs, out.coefs, in_1.degree, out.coef_modulus); 
    delete[] fft_prod_new; 
    delete[] fft_multisum_eval_new;  
}

void FFTWLongNegacyclicEngine::multisum(Polynomial &out, PolynomialArrayEvalForm &in_1, PolynomialArrayEvalForm &in_2){
    PolynomialArrayEvalFormFFTWLongComplex& in_1_cast = static_cast<PolynomialArrayEvalFormFFTWLongComplex&>(in_1);
    PolynomialArrayEvalFormFFTWLongComplex& in_2_cast = static_cast<PolynomialArrayEvalFormFFTWLongComplex&>(in_2);
    fftwl_complex* in_1_temp = in_1_cast.eval_fftwl;
    fftwl_complex* in_2_temp = in_2_cast.eval_fftwl;
    fftwl_complex* fft_prod_new = new fftwl_complex[in_2_cast.size]; 
    fftwl_complex* fft_multisum_eval_new = new fftwl_complex[in_2_cast.size]; 
       
    engine.mul_eval_form_l(fft_multisum_eval_new, in_1_temp, in_2_temp);  
 
    for(int32_t i = 1; i < in_2_cast.array_size; ++i){
        in_1_temp = &in_1_cast.eval_fftwl[i * in_1_cast.size];
        in_2_temp = &in_2_cast.eval_fftwl[i * in_2_cast.size];
         
        engine.mul_eval_form_l(fft_prod_new, in_1_temp, in_2_temp); 
        engine.add_eval_form_l(fft_multisum_eval_new, fft_multisum_eval_new, fft_prod_new); 
    }
    engine.to_coef_form_l(out.coefs, fft_multisum_eval_new);
    Utils::array_mod_form(out.coefs, out.coefs, out.degree, out.coef_modulus); 
    delete[] fft_prod_new; 
    delete[] fft_multisum_eval_new;  
}

void FFTWLongNegacyclicEngine::multisum(Polynomial &out_multisum, PolynomialArrayEvalForm &out_in_1_eval, PolynomialArrayCoefForm &in_1, PolynomialArrayEvalForm &in_2){
    PolynomialArrayEvalFormFFTWLongComplex& out_in_1_eval_cast = static_cast<PolynomialArrayEvalFormFFTWLongComplex&>(out_in_1_eval);
    PolynomialArrayEvalFormFFTWLongComplex& in_2_cast = static_cast<PolynomialArrayEvalFormFFTWLongComplex&>(in_2);
    int64_t* in_1_temp = in_1.poly_array;
    fftwl_complex* out_eval_temp = out_in_1_eval_cast.eval_fftwl;
    fftwl_complex* in_2_temp = in_2_cast.eval_fftwl;
    fftwl_complex* fft_prod_new = new fftwl_complex[in_2_cast.size]; 
    fftwl_complex* fft_multisum_eval_new = new fftwl_complex[in_2_cast.size]; 
    
    engine.to_eval_form_l(out_eval_temp, in_1_temp);   
    engine.mul_eval_form_l(fft_multisum_eval_new, out_eval_temp, in_2_temp);  
 
    for(int32_t i = 1; i < in_2_cast.array_size; ++i){
        in_1_temp = &in_1.poly_array[i * in_1.degree];
        in_2_temp = &in_2_cast.eval_fftwl[i * in_2_cast.size];
        out_eval_temp = &out_in_1_eval_cast.eval_fftwl[i * out_in_1_eval_cast.size];
        
        engine.to_eval_form_l(out_eval_temp, in_1_temp);  
        engine.mul_eval_form_l(fft_prod_new, out_eval_temp, in_2_temp); 
        engine.add_eval_form_l(fft_multisum_eval_new, fft_multisum_eval_new, fft_prod_new); 
    }
    engine.to_coef_form_l(out_multisum.coefs, fft_multisum_eval_new);
    Utils::array_mod_form(out_multisum.coefs, out_multisum.coefs, in_1.degree, out_multisum.coef_modulus); 
    delete[] fft_prod_new; 
    delete[] fft_multisum_eval_new;  
}
   