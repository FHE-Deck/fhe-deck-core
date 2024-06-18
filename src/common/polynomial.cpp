#include "polynomial.h"
 
using namespace fhe_deck;
 

void PolynomialMultiplicationEngine::mul(Polynomial *out, Polynomial *in_1, Polynomial *in_2){   
    PolynomialEvalForm* eval_in_1 = init_polynomial_eval_form();
    to_eval(eval_in_1, in_1);  
    PolynomialEvalForm* eval_in_2 = init_polynomial_eval_form();
    to_eval(eval_in_2, in_2); 
    PolynomialEvalForm* eval_out = init_polynomial_eval_form(); 
    mul(eval_out, eval_in_1, eval_in_2);  
    to_coef(out, eval_out); 
    delete eval_in_1;
    delete eval_in_2;
    delete eval_out;
}
  
IntelHexlNTTEngine::IntelHexlNTTEngine(int32_t degree, int64_t coef_modulus){ 
    this->degree = degree;
    this->coef_modulus = coef_modulus;
    this->ntt = intel::hexl::NTT(degree, coef_modulus);
    this->type = hexl_ntt;
}
  
void IntelHexlNTTEngine::to_coef(Polynomial *out, PolynomialEvalForm *in){
    PolynomialEvalFormLongInteger* in_cast = static_cast<PolynomialEvalFormLongInteger*>(in);
    ntt.ComputeInverse((uint64_t*) out->coefs, (uint64_t*)  in_cast->eval_long, 1, 1);   
}
  
void IntelHexlNTTEngine::to_coef(PolynomialArrayCoefForm *out, PolynomialArrayEvalForm *in){
    PolynomialArrayEvalFormLong* in_cast = static_cast<PolynomialArrayEvalFormLong*>(in);
    int64_t* in_poly;
    int64_t* out_poly;
    for(int32_t i = 0; i < in->array_size; ++i){
        in_poly = &in_cast->eval_long[i * in->size];
        out_poly = &out->poly_array[i * out->degree];
        ntt.ComputeInverse((uint64_t*) out_poly, (uint64_t*) in_poly, 1, 1);  
    } 
}

PolynomialEvalForm* IntelHexlNTTEngine::init_polynomial_eval_form(){ 
    return new PolynomialEvalFormLongInteger(new int64_t[degree], degree, coef_modulus);
}

PolynomialArrayEvalForm* IntelHexlNTTEngine::init_polynomial_array_eval_form(int32_t array_size){ 
    return new PolynomialArrayEvalFormLong(array_size, degree, coef_modulus); 
}
 
void IntelHexlNTTEngine::to_eval(PolynomialEvalForm *out, Polynomial *in){ 
    PolynomialEvalFormLongInteger* out_cast = static_cast<PolynomialEvalFormLongInteger*>(out);
    // Here we make sure that the coefficients are in propper form.
    int64_t* coefs_mod_form = new int64_t[in->degree];
    Utils::array_mod_form(coefs_mod_form, in->coefs, in->degree, in->coef_modulus); 
    ntt.ComputeForward((uint64_t*) out_cast->eval_long, (uint64_t*) coefs_mod_form, 1, 1);  
    delete[] coefs_mod_form;
}
 
void IntelHexlNTTEngine::to_eval(PolynomialArrayEvalForm *out, PolynomialArrayCoefForm *in){ 
    PolynomialArrayEvalFormLong* out_cast = static_cast<PolynomialArrayEvalFormLong*>(out);
    int64_t* in_poly;
    int64_t* out_poly; 
    for(int32_t i = 0; i < in->array_size; ++i){
        in_poly = &in->poly_array[i * in->degree];
        out_poly = &out_cast->eval_long[i * out_cast->size];
        ntt.ComputeForward((uint64_t*) out_poly, (uint64_t*) in_poly, 1, 1);   
    } 
}

void IntelHexlNTTEngine::mul(PolynomialEvalForm *out, PolynomialEvalForm *in_1, PolynomialEvalForm *in_2){ 
    PolynomialEvalFormLongInteger* out_cast = static_cast<PolynomialEvalFormLongInteger*>(out);
    PolynomialEvalFormLongInteger* in_1_cast = static_cast<PolynomialEvalFormLongInteger*>(in_1);
    PolynomialEvalFormLongInteger* in_2_cast = static_cast<PolynomialEvalFormLongInteger*>(in_2); 
    intel::hexl::EltwiseMultMod((uint64_t*) out_cast->eval_long, 
                (uint64_t*) in_1_cast->eval_long, 
                (uint64_t*) in_2_cast->eval_long, 
                out->size, out->coef_modulus, 1); 
}
 
void IntelHexlNTTEngine::multisum(Polynomial *out, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2){   
    PolynomialArrayEvalFormLong* in_2_cast = static_cast<PolynomialArrayEvalFormLong*>(in_2);
    int64_t* in_1_temp = in_1->poly_array;
    int64_t* in_2_temp = in_2_cast->eval_long; 
    int64_t* temp = new int64_t[in_2_cast->size];  
    /// TODO: Need to assure the input polynomials are already in mod_form
    Utils::array_mod_form(in_1_temp, in_1_temp, in_1->degree, in_1->coef_modulus); 
    ntt.ComputeForward((uint64_t*) temp, (uint64_t*) in_1_temp, 1, 1);  
    intel::hexl::EltwiseMultMod((uint64_t*) out->coefs, (uint64_t*) temp, (uint64_t*) in_2_temp, in_2_cast->size, in_2_cast->coef_modulus, 1); 
    for(int32_t i = 1; i < in_2_cast->array_size; ++i){
        in_1_temp = &in_1->poly_array[i * in_1->degree];
        in_2_temp = &in_2_cast->eval_long[i * in_2_cast->size]; 
        Utils::array_mod_form(in_1_temp, in_1_temp, in_1->degree, in_1->coef_modulus); 
        ntt.ComputeForward((uint64_t*) temp, (uint64_t*) in_1_temp, 1, 1);  
        intel::hexl::EltwiseMultMod((uint64_t*) temp, (uint64_t*) temp, (uint64_t*) in_2_temp, in_2_cast->size, in_2_cast->coef_modulus, 1);
        intel::hexl::EltwiseAddMod((uint64_t*) out->coefs, (uint64_t*) temp, (uint64_t*) out->coefs, in_2_cast->size, in_2_cast->coef_modulus);
    }
    ntt.ComputeInverse((uint64_t*) out->coefs, (uint64_t*) out->coefs, 1, 1);  
    delete[] temp; 
}

void IntelHexlNTTEngine::multisum(Polynomial *out, PolynomialArrayEvalForm *in_1, PolynomialArrayEvalForm *in_2){   
    PolynomialArrayEvalFormLong* in_1_cast = static_cast<PolynomialArrayEvalFormLong*>(in_1);
    PolynomialArrayEvalFormLong* in_2_cast = static_cast<PolynomialArrayEvalFormLong*>(in_2);
    int64_t* in_1_temp = in_1_cast->eval_long;
    int64_t* in_2_temp = in_2_cast->eval_long; 
    int64_t* temp = new int64_t[in_2_cast->size];   
    intel::hexl::EltwiseMultMod((uint64_t*) out->coefs, (uint64_t*) in_1_temp, (uint64_t*) in_2_temp, in_2_cast->size, in_2_cast->coef_modulus, 1); 
    for(int32_t i = 1; i < in_2_cast->array_size; ++i){
        in_1_temp = &in_1_cast->eval_long[i * in_1_cast->size];
        in_2_temp = &in_2_cast->eval_long[i * in_2_cast->size];    
        intel::hexl::EltwiseMultMod((uint64_t*) temp, (uint64_t*) in_1_temp, (uint64_t*) in_2_temp, in_2_cast->size, in_2_cast->coef_modulus, 1);
        intel::hexl::EltwiseAddMod((uint64_t*) out->coefs, (uint64_t*) temp, (uint64_t*) out->coefs, in_2_cast->size, in_2_cast->coef_modulus); 
    }
    ntt.ComputeInverse((uint64_t*) out->coefs, (uint64_t*) out->coefs, 1, 1);  
    delete[] temp; 
}


void IntelHexlNTTEngine::multisum(Polynomial *out_multisum, PolynomialArrayEvalForm *out_in_1_eval, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2){   
    PolynomialArrayEvalFormLong* in_2_cast = static_cast<PolynomialArrayEvalFormLong*>(in_2);
    PolynomialArrayEvalFormLong* out_in_1_eval_cast = static_cast<PolynomialArrayEvalFormLong*>(out_in_1_eval);
    int64_t* in_1_temp = in_1->poly_array;
    int64_t* in_2_temp = in_2_cast->eval_long; 
    int64_t* temp = new long[in_2_cast->size];  
    int64_t* out_eval = out_in_1_eval_cast->eval_long;
    /// TODO: Need to assure the input polynomials is already in mod_form
    Utils::array_mod_form(in_1_temp, in_1_temp, in_1->degree, in_1->coef_modulus); 
    ntt.ComputeForward((uint64_t*) out_eval, (uint64_t*) in_1_temp, 1, 1);  
    intel::hexl::EltwiseMultMod((uint64_t*) out_multisum->coefs, (uint64_t*) out_eval, (uint64_t*) in_2_temp, in_2_cast->size, in_2_cast->coef_modulus, 1); 
    for(int32_t i = 1; i < in_2_cast->array_size; ++i){
        in_1_temp = &in_1->poly_array[i * in_1->degree];
        in_2_temp = &in_2_cast->eval_long[i * in_2_cast->size]; 
        out_eval = &out_in_1_eval_cast->eval_long[i * out_in_1_eval_cast->size];
        Utils::array_mod_form(in_1_temp, in_1_temp, in_1->degree, in_1->coef_modulus); 
        ntt.ComputeForward((uint64_t*) out_eval, (uint64_t*) in_1_temp, 1, 1);  
        intel::hexl::EltwiseMultMod((uint64_t*) temp, (uint64_t*) out_eval, (uint64_t*) in_2_temp, in_2_cast->size, in_2_cast->coef_modulus, 1);
        intel::hexl::EltwiseAddMod((uint64_t*) out_multisum->coefs, (uint64_t*) temp, (uint64_t*) out_multisum->coefs, in_2_cast->size, in_2_cast->coef_modulus);
    }
    ntt.ComputeInverse((uint64_t*) out_multisum->coefs, (uint64_t*) out_multisum->coefs, 1, 1);  
    delete[] temp; 
}


FFTWNegacyclicEngine::FFTWNegacyclicEngine(int32_t degree, int64_t coef_modulus){ 
    this->degree = degree;
    this->coef_modulus = coef_modulus; 
    this->type = double_fft;
    engine = FFTPlan(negacyclic, degree, false);  
}

PolynomialEvalForm* FFTWNegacyclicEngine::init_polynomial_eval_form(){
    return new PolynomialEvalFormFFTWComplex(engine.init_fft_poly(), engine.plan_size, coef_modulus);
}

PolynomialArrayEvalForm* FFTWNegacyclicEngine::init_polynomial_array_eval_form(int32_t array_size){
    return new PolynomialArrayEvalFormFFTWComplex(this, array_size); 
}
  
void FFTWNegacyclicEngine::to_eval(PolynomialEvalForm *out, Polynomial *in){
    PolynomialEvalFormFFTWComplex* out_cast = static_cast<PolynomialEvalFormFFTWComplex*>(out);
    engine.to_eval_form(out_cast->eval_fftw, in->coefs); 
}
 
void FFTWNegacyclicEngine::to_eval(PolynomialArrayEvalForm *out, PolynomialArrayCoefForm *in){ 
    PolynomialArrayEvalFormFFTWComplex* out_cast = static_cast<PolynomialArrayEvalFormFFTWComplex*>(out);
    int64_t *in_poly;
    fftw_complex *out_poly;
    for (int32_t i = 0; i < in->array_size; ++i)
    {  
        in_poly = &in->poly_array[i * in->degree];
        out_poly = &out_cast->eval_fftw[i * out_cast->size];  
        engine.to_eval_form_scale(out_poly, in_poly, 2.0);  
    } 
}

void FFTWNegacyclicEngine::to_coef(Polynomial *out, PolynomialEvalForm *in){ 
    PolynomialEvalFormFFTWComplex* in_cast = static_cast<PolynomialEvalFormFFTWComplex*>(in);
    engine.to_coef_form(out->coefs, in_cast->eval_fftw);
    // Divide by the scale (polynomial size times two.)
    // NOTE: For FHE its nice to scale one of the polynomials in the key
    // That is this rescaling could be precomputed. But here the Engine and later Polynomial class are oblivious to that.
    // Maybe we can add precomputation in the future - now its not a bootleneck anyway.
    double scale = (double)(engine.plan_size * 2);
    for(int32_t i = 0; i < degree; ++i){   
        out->coefs[i] = round((double)out->coefs[i] / scale); 
    } 
}
  
void FFTWNegacyclicEngine::to_coef(PolynomialArrayCoefForm *out, PolynomialArrayEvalForm *in){
    PolynomialArrayEvalFormFFTWComplex* in_cast = static_cast<PolynomialArrayEvalFormFFTWComplex*>(in);
    int64_t *out_poly;
    fftw_complex *in_poly;
    for (int32_t i = 0; i < in_cast->array_size; ++i)
    {
        in_poly = &in_cast->eval_fftw[i * in_cast->size];
        out_poly = &out->poly_array[i * out->degree];
        engine.to_coef_form(out_poly, in_poly); 
    }
}

void FFTWNegacyclicEngine::mul(PolynomialEvalForm *out, PolynomialEvalForm *in_1, PolynomialEvalForm *in_2){
    PolynomialEvalFormFFTWComplex* out_cast = static_cast<PolynomialEvalFormFFTWComplex*>(out);
    PolynomialEvalFormFFTWComplex* in_1_cast = static_cast<PolynomialEvalFormFFTWComplex*>(in_1);
    PolynomialEvalFormFFTWComplex* in_2_cast = static_cast<PolynomialEvalFormFFTWComplex*>(in_2);
    // Remind that one of the polynomials must be scaled by the plan_size times two. 
    engine.mul_eval_form(out_cast->eval_fftw, 
            in_1_cast->eval_fftw, 
            in_2_cast->eval_fftw);  
}


void FFTWNegacyclicEngine::multisum(Polynomial *out, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2){   
    PolynomialArrayEvalFormFFTWComplex* in_2_cast = static_cast<PolynomialArrayEvalFormFFTWComplex*>(in_2);
    int64_t* in_1_temp = in_1->poly_array;
    fftw_complex* in_2_temp = in_2_cast->eval_fftw;
    fftw_complex* fft_prod_new = new fftw_complex[in_2_cast->size]; 
    fftw_complex* fft_multisum_eval_new = new fftw_complex[in_2_cast->size]; 
    
    engine.to_eval_form(fft_multisum_eval_new, in_1_temp);   
    engine.mul_eval_form(fft_multisum_eval_new, fft_multisum_eval_new, in_2_temp);  
 
    for(int32_t i = 1; i < in_2_cast->array_size; ++i){
        in_1_temp = &in_1->poly_array[i * in_1->degree];
        in_2_temp = &in_2_cast->eval_fftw[i * in_2_cast->size];
        
        engine.to_eval_form(fft_prod_new, in_1_temp);  
        engine.mul_eval_form(fft_prod_new, fft_prod_new, in_2_temp); 
        engine.add_eval_form(fft_multisum_eval_new, fft_multisum_eval_new, fft_prod_new); 
    } 
    engine.to_coef_form(out->coefs, fft_multisum_eval_new);
    Utils::array_mod_form(out->coefs, out->coefs, in_1->degree, in_1->coef_modulus); 
    delete[] fft_prod_new; 
    delete[] fft_multisum_eval_new; 
}


void FFTWNegacyclicEngine::multisum(Polynomial *out, PolynomialArrayEvalForm *in_1, PolynomialArrayEvalForm *in_2){   
    PolynomialArrayEvalFormFFTWComplex* in_1_cast = static_cast<PolynomialArrayEvalFormFFTWComplex*>(in_1);
    PolynomialArrayEvalFormFFTWComplex* in_2_cast = static_cast<PolynomialArrayEvalFormFFTWComplex*>(in_2);
    fftw_complex* in_1_temp = in_1_cast->eval_fftw;
    fftw_complex* in_2_temp = in_2_cast->eval_fftw;
    fftw_complex* fft_prod_new = new fftw_complex[in_2_cast->size]; 
    fftw_complex* fft_multisum_eval_new = new fftw_complex[in_2_cast->size]; 
    
    //engine.to_eval_form(fft_multisum_eval_new, in_1_temp);   
    engine.mul_eval_form(fft_multisum_eval_new, in_1_temp, in_2_temp);  
 
    for(int32_t i = 1; i < in_2_cast->array_size; ++i){
        in_1_temp = &in_1_cast->eval_fftw[i * in_1_cast->size];
        in_2_temp = &in_2_cast->eval_fftw[i * in_2_cast->size];
         
        engine.mul_eval_form(fft_prod_new, in_1_temp, in_2_temp); 
        engine.add_eval_form(fft_multisum_eval_new, fft_multisum_eval_new, fft_prod_new); 
    } 
    engine.to_coef_form(out->coefs, fft_multisum_eval_new);
    Utils::array_mod_form(out->coefs, out->coefs, out->degree, in_1->coef_modulus); 
    delete[] fft_prod_new; 
    delete[] fft_multisum_eval_new; 
}

   
void FFTWNegacyclicEngine::multisum(Polynomial *out_multisum, PolynomialArrayEvalForm *out_in_1_eval, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2){   
    PolynomialArrayEvalFormFFTWComplex* in_2_cast = static_cast<PolynomialArrayEvalFormFFTWComplex*>(in_2);
    PolynomialArrayEvalFormFFTWComplex* out_in_1_eval_cast = static_cast<PolynomialArrayEvalFormFFTWComplex*>(out_in_1_eval);
    int64_t* in_1_temp = in_1->poly_array;
    fftw_complex* out_eval = out_in_1_eval_cast->eval_fftw;
    fftw_complex* in_2_temp = in_2_cast->eval_fftw;
    fftw_complex* fft_prod_new = new fftw_complex[in_2_cast->size]; 
    fftw_complex* fft_multisum_eval_new = new fftw_complex[in_2_cast->size]; 
    
    engine.to_eval_form(out_eval, in_1_temp);   
    engine.mul_eval_form(fft_multisum_eval_new, out_eval, in_2_temp);  
 
    for(int32_t i = 1; i < in_2_cast->array_size; ++i){
        in_1_temp = &in_1->poly_array[i * in_1->degree];
        out_eval = &out_in_1_eval_cast->eval_fftw[i * out_in_1_eval_cast->size];
        in_2_temp = &in_2_cast->eval_fftw[i * in_2_cast->size];
        
        engine.to_eval_form(out_eval, in_1_temp);  
        engine.mul_eval_form(fft_prod_new, out_eval, in_2_temp); 
        engine.add_eval_form(fft_multisum_eval_new, fft_multisum_eval_new, fft_prod_new); 
    } 
    engine.to_coef_form(out_multisum->coefs, fft_multisum_eval_new);
    Utils::array_mod_form(out_multisum->coefs, out_multisum->coefs, in_1->degree, in_1->coef_modulus); 
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
    return new PolynomialEvalFormFFTWLongComplex(engine.init_fft_poly_l(), engine.plan_size, coef_modulus);
}

PolynomialArrayEvalForm* FFTWLongNegacyclicEngine::init_polynomial_array_eval_form(int32_t size){
    return new PolynomialArrayEvalFormFFTWLongComplex(this, size);
}
 
void FFTWLongNegacyclicEngine::to_eval(PolynomialEvalForm *out, Polynomial *in){
    PolynomialEvalFormFFTWLongComplex* out_cast = static_cast<PolynomialEvalFormFFTWLongComplex*>(out);
    engine.to_eval_form_l(out_cast->eval_fftwl, in->coefs);   
}
 
void FFTWLongNegacyclicEngine::to_eval(PolynomialArrayEvalForm *out, PolynomialArrayCoefForm *in){
    PolynomialArrayEvalFormFFTWLongComplex* out_cast = static_cast<PolynomialArrayEvalFormFFTWLongComplex*>(out);
    int64_t *in_poly;
    fftwl_complex *out_poly;
    for (int32_t i = 0; i < in->array_size; ++i)
    {
        in_poly = &in->poly_array[i * in->degree];
        out_poly = &out_cast->eval_fftwl[i * out_cast->size];
        engine.to_eval_form_l(out_poly, in_poly); 
    }
} 

void FFTWLongNegacyclicEngine::to_coef(Polynomial *out, PolynomialEvalForm *in){
    PolynomialEvalFormFFTWLongComplex* in_cast = static_cast<PolynomialEvalFormFFTWLongComplex*>(in);
    engine.to_coef_form_l(out->coefs, in_cast->eval_fftwl);   
        long double scale = (long double)(engine.plan_size * 2);
        for(int32_t i = 0; i < degree; ++i){   
            out->coefs[i] = roundl((long double)out->coefs[i] / scale); 
        } 
}
  
void FFTWLongNegacyclicEngine::to_coef(PolynomialArrayCoefForm *out, PolynomialArrayEvalForm *in){
    PolynomialArrayEvalFormFFTWLongComplex* in_cast = static_cast<PolynomialArrayEvalFormFFTWLongComplex*>(in);
    int64_t *out_poly;
    fftwl_complex *in_poly;
    for (int32_t i = 0; i < in_cast->array_size; ++i)
    {
        in_poly = &in_cast->eval_fftwl[i * in_cast->size];
        out_poly = &out->poly_array[i * out->degree];
        engine.to_coef_form_l(out_poly, in_poly); 
    }
}

void FFTWLongNegacyclicEngine::mul(PolynomialEvalForm *out, PolynomialEvalForm *in_1, PolynomialEvalForm *in_2){
    PolynomialEvalFormFFTWLongComplex* out_cast = static_cast<PolynomialEvalFormFFTWLongComplex*>(out);
    PolynomialEvalFormFFTWLongComplex* in_1_cast = static_cast<PolynomialEvalFormFFTWLongComplex*>(in_1);
    PolynomialEvalFormFFTWLongComplex* in_2_cast = static_cast<PolynomialEvalFormFFTWLongComplex*>(in_2);
    engine.mul_eval_form_l(out_cast->eval_fftwl, in_1_cast->eval_fftwl, in_2_cast->eval_fftwl);
}
  
void FFTWLongNegacyclicEngine::multisum(Polynomial *out, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2){
    PolynomialArrayEvalFormFFTWLongComplex* in_2_cast = static_cast<PolynomialArrayEvalFormFFTWLongComplex*>(in_2);
    int64_t* in_1_temp = in_1->poly_array;
    fftwl_complex* in_2_temp = in_2_cast->eval_fftwl;
    fftwl_complex* fft_prod_new = new fftwl_complex[in_2_cast->size]; 
    fftwl_complex* fft_multisum_eval_new = new fftwl_complex[in_2_cast->size]; 
    
    engine.to_eval_form_l(fft_multisum_eval_new, in_1_temp);   
    engine.mul_eval_form_l(fft_multisum_eval_new, fft_multisum_eval_new, in_2_temp);  
 
    for(int32_t i = 1; i < in_2_cast->array_size; ++i){
        in_1_temp = &in_1->poly_array[i * in_1->degree];
        in_2_temp = &in_2_cast->eval_fftwl[i * in_2_cast->size];
        
        engine.to_eval_form_l(fft_prod_new, in_1_temp);  
        engine.mul_eval_form_l(fft_prod_new, fft_prod_new, in_2_temp); 
        engine.add_eval_form_l(fft_multisum_eval_new, fft_multisum_eval_new, fft_prod_new); 
    }
    engine.to_coef_form_l(out->coefs, fft_multisum_eval_new);
    Utils::array_mod_form(out->coefs, out->coefs, in_1->degree, in_1->coef_modulus); 
    delete[] fft_prod_new; 
    delete[] fft_multisum_eval_new;  
}

void FFTWLongNegacyclicEngine::multisum(Polynomial *out, PolynomialArrayEvalForm *in_1, PolynomialArrayEvalForm *in_2){
    PolynomialArrayEvalFormFFTWLongComplex* in_1_cast = static_cast<PolynomialArrayEvalFormFFTWLongComplex*>(in_1);
    PolynomialArrayEvalFormFFTWLongComplex* in_2_cast = static_cast<PolynomialArrayEvalFormFFTWLongComplex*>(in_2);
    fftwl_complex* in_1_temp = in_1_cast->eval_fftwl;
    fftwl_complex* in_2_temp = in_2_cast->eval_fftwl;
    fftwl_complex* fft_prod_new = new fftwl_complex[in_2_cast->size]; 
    fftwl_complex* fft_multisum_eval_new = new fftwl_complex[in_2_cast->size]; 
       
    engine.mul_eval_form_l(fft_multisum_eval_new, in_1_temp, in_2_temp);  
 
    for(int32_t i = 1; i < in_2_cast->array_size; ++i){
        in_1_temp = &in_1_cast->eval_fftwl[i * in_1_cast->size];
        in_2_temp = &in_2_cast->eval_fftwl[i * in_2_cast->size];
         
        engine.mul_eval_form_l(fft_prod_new, in_1_temp, in_2_temp); 
        engine.add_eval_form_l(fft_multisum_eval_new, fft_multisum_eval_new, fft_prod_new); 
    }
    engine.to_coef_form_l(out->coefs, fft_multisum_eval_new);
    Utils::array_mod_form(out->coefs, out->coefs, out->degree, in_1->coef_modulus); 
    delete[] fft_prod_new; 
    delete[] fft_multisum_eval_new;  
}

void FFTWLongNegacyclicEngine::multisum(Polynomial *out_multisum, PolynomialArrayEvalForm *out_in_1_eval, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2){
    PolynomialArrayEvalFormFFTWLongComplex* out_in_1_eval_cast = static_cast<PolynomialArrayEvalFormFFTWLongComplex*>(out_in_1_eval);
    PolynomialArrayEvalFormFFTWLongComplex* in_2_cast = static_cast<PolynomialArrayEvalFormFFTWLongComplex*>(in_2);
    int64_t* in_1_temp = in_1->poly_array;
    fftwl_complex* out_eval_temp = out_in_1_eval_cast->eval_fftwl;
    fftwl_complex* in_2_temp = in_2_cast->eval_fftwl;
    fftwl_complex* fft_prod_new = new fftwl_complex[in_2_cast->size]; 
    fftwl_complex* fft_multisum_eval_new = new fftwl_complex[in_2_cast->size]; 
    
    engine.to_eval_form_l(out_eval_temp, in_1_temp);   
    engine.mul_eval_form_l(fft_multisum_eval_new, out_eval_temp, in_2_temp);  
 
    for(int32_t i = 1; i < in_2_cast->array_size; ++i){
        in_1_temp = &in_1->poly_array[i * in_1->degree];
        in_2_temp = &in_2_cast->eval_fftwl[i * in_2_cast->size];
        out_eval_temp = &out_in_1_eval_cast->eval_fftwl[i * out_in_1_eval_cast->size];
        
        engine.to_eval_form_l(out_eval_temp, in_1_temp);  
        engine.mul_eval_form_l(fft_prod_new, out_eval_temp, in_2_temp); 
        engine.add_eval_form_l(fft_multisum_eval_new, fft_multisum_eval_new, fft_prod_new); 
    }
    engine.to_coef_form_l(out_multisum->coefs, fft_multisum_eval_new);
    Utils::array_mod_form(out_multisum->coefs, out_multisum->coefs, in_1->degree, in_1->coef_modulus); 
    delete[] fft_prod_new; 
    delete[] fft_multisum_eval_new;  
}
   
void PolynomialMultiplicationEngineBuilder::set_coef_modulus(int64_t coef_modulus){
    this->coef_modulus = coef_modulus;
}

void PolynomialMultiplicationEngineBuilder::set_degree(int64_t degree){
    this->degree = degree;
}

void PolynomialMultiplicationEngineBuilder::set_ring_type(RingType ring){
    this->ring = ring;
}

void PolynomialMultiplicationEngineBuilder::set_polynomial_arithmetic(PolynomialArithmetic arithmetic){
    this->arithmetic = arithmetic;
    this->is_init = true;
}

void PolynomialMultiplicationEngineBuilder::set_modulus_type(ModulusType mod_type){
    this->mod_type = mod_type;
}

std::shared_ptr<PolynomialMultiplicationEngine> PolynomialMultiplicationEngineBuilder::build(){
    if(!is_init){
        throw std::logic_error("PolynomialMultiplicationEngineBuilder::build(): No polynomial arithmetic type set!");
    }
    if(arithmetic == hexl_ntt){
        return std::shared_ptr<PolynomialMultiplicationEngine>(new IntelHexlNTTEngine(degree, coef_modulus));
    }
    if(arithmetic == double_fft){ 
        return std::shared_ptr<PolynomialMultiplicationEngine>(new FFTWNegacyclicEngine(degree, coef_modulus));
    }
    if(arithmetic == long_double_fft){
        return std::shared_ptr<PolynomialMultiplicationEngine>(new FFTWLongNegacyclicEngine(degree, coef_modulus));
    }
    if(arithmetic == ntl){
        throw std::logic_error("NTL Not Supported Yet.");
    }
    throw std::logic_error("PolynomialMultiplicationEngineBuilder::build(): Polynomial arithmetic not supported!");
}

PolynomialEvalFormLongInteger::~PolynomialEvalFormLongInteger(){
    if(is_init){
        delete[] eval_long;
    }
}

PolynomialEvalFormLongInteger::PolynomialEvalFormLongInteger(int64_t* eval_long, int32_t size, int64_t coef_modulus){
    this->eval_long = eval_long;
    this->coef_modulus = coef_modulus;
    this->is_init = true; 
    this->size = size;
}

void PolynomialEvalFormLongInteger::zeroize(){ 
    for(int32_t i = 0; i < size; ++i){
        this->eval_long[i] = 0;
    }
}

void PolynomialEvalFormLongInteger::add(PolynomialEvalForm *out, PolynomialEvalForm *other){ 
    PolynomialEvalFormLongInteger* other_cast = static_cast<PolynomialEvalFormLongInteger*>(other);
    PolynomialEvalFormLongInteger* out_cast = static_cast<PolynomialEvalFormLongInteger*>(out);
    for(int32_t i = 0; i < size; ++i){
        out_cast->eval_long[i] = this->eval_long[i] + other_cast->eval_long[i];
    }
}

void PolynomialEvalFormLongInteger::sub(PolynomialEvalForm *out, PolynomialEvalForm *other){
    PolynomialEvalFormLongInteger* other_cast = static_cast<PolynomialEvalFormLongInteger*>(other);
    PolynomialEvalFormLongInteger* out_cast = static_cast<PolynomialEvalFormLongInteger*>(out);
    for(int32_t i = 0; i < size; ++i){
        out_cast->eval_long[i] = this->eval_long[i] - other_cast->eval_long[i];
    }  
}

void PolynomialEvalFormLongInteger::mul(PolynomialEvalForm *out, int64_t scalar){
    PolynomialEvalFormLongInteger* out_cast = static_cast<PolynomialEvalFormLongInteger*>(out);
    for(int32_t i = 0; i < size; ++i){
        out_cast->eval_long[i] = this->eval_long[i] * scalar;
    } 
}
 
void PolynomialEvalFormLongInteger::neg(PolynomialEvalForm *out){
    PolynomialEvalFormLongInteger* out_cast = static_cast<PolynomialEvalFormLongInteger*>(out);
    for(int32_t i = 0; i < size; ++i){
        out_cast->eval_long[i] = -this->eval_long[i];
    } 
}
 
void PolynomialEvalFormLongInteger::mod_reduce(int64_t Q){
    Utils::array_mod_form(this->eval_long, this->eval_long, size, Q);  
} 

PolynomialEvalFormFFTWComplex::~PolynomialEvalFormFFTWComplex(){
    if(is_init){
        delete[] eval_fftw;
    }
}
 
PolynomialEvalFormFFTWComplex::PolynomialEvalFormFFTWComplex(fftw_complex* eval_fftw, int32_t size, int64_t coef_modulus){
    this->eval_fftw = eval_fftw;
    this->coef_modulus = coef_modulus;
    this->is_init = true; 
    this->size = size; 
}

void PolynomialEvalFormFFTWComplex::zeroize(){
    for(int32_t i = 0; i < size; ++i){
        this->eval_fftw[i][0] = 0;
        this->eval_fftw[i][1] = 0;
    }
}

void PolynomialEvalFormFFTWComplex::add(PolynomialEvalForm *out, PolynomialEvalForm *other){
    PolynomialEvalFormFFTWComplex* other_cast = static_cast<PolynomialEvalFormFFTWComplex*>(other);
    PolynomialEvalFormFFTWComplex* out_cast = static_cast<PolynomialEvalFormFFTWComplex*>(out);
    for(int32_t i = 0; i < size; ++i){
        out_cast->eval_fftw[i][0] = this->eval_fftw[i][0] + other_cast->eval_fftw[i][0];
        out_cast->eval_fftw[i][1] = this->eval_fftw[i][1] + other_cast->eval_fftw[i][1];
    } 
}

void PolynomialEvalFormFFTWComplex::sub(PolynomialEvalForm *out, PolynomialEvalForm *other){
    PolynomialEvalFormFFTWComplex* other_cast = static_cast<PolynomialEvalFormFFTWComplex*>(other);
    PolynomialEvalFormFFTWComplex* out_cast = static_cast<PolynomialEvalFormFFTWComplex*>(out);
    for(int32_t i = 0; i < size; ++i){
        out_cast->eval_fftw[i][0] = this->eval_fftw[i][0] - other_cast->eval_fftw[i][0];
        out_cast->eval_fftw[i][1] = this->eval_fftw[i][1] - other_cast->eval_fftw[i][1];
    } 
}

void PolynomialEvalFormFFTWComplex::mul(PolynomialEvalForm *out, int64_t scalar){
    PolynomialEvalFormFFTWComplex* out_cast = static_cast<PolynomialEvalFormFFTWComplex*>(out);
    for(int32_t i = 0; i < size; ++i){
        out_cast->eval_fftw[i][0] = this->eval_fftw[i][0] * scalar;
        out_cast->eval_fftw[i][1] = this->eval_fftw[i][1] * scalar;
    }  
}
 
void PolynomialEvalFormFFTWComplex::neg(PolynomialEvalForm *out){ 
    PolynomialEvalFormFFTWComplex* out_cast = static_cast<PolynomialEvalFormFFTWComplex*>(out);
    for(int32_t i = 0; i < size; ++i){
        out_cast->eval_fftw[i][0] = -this->eval_fftw[i][0];
        out_cast->eval_fftw[i][1] = -this->eval_fftw[i][1];
    } 
}

void PolynomialEvalFormFFTWComplex::mod_reduce(int64_t Q){ 
}

PolynomialEvalFormFFTWLongComplex::~PolynomialEvalFormFFTWLongComplex(){
    if(is_init){
        delete[] eval_fftwl;
    }
}
  
PolynomialEvalFormFFTWLongComplex::PolynomialEvalFormFFTWLongComplex(fftwl_complex* eval_fftwl, int32_t size, int64_t coef_modulus){
    this->eval_fftwl = eval_fftwl;
    this->coef_modulus = coef_modulus;
    this->is_init = true; 
    this->size = size; 
}

void PolynomialEvalFormFFTWLongComplex::zeroize(){
    for(int32_t i = 0; i < size; ++i){
        this->eval_fftwl[i][0] = 0;
        this->eval_fftwl[i][1] = 0;
    }
}

void PolynomialEvalFormFFTWLongComplex::add(PolynomialEvalForm *out, PolynomialEvalForm *other){
    PolynomialEvalFormFFTWLongComplex* other_cast = static_cast<PolynomialEvalFormFFTWLongComplex*>(other);
    PolynomialEvalFormFFTWLongComplex* out_cast = static_cast<PolynomialEvalFormFFTWLongComplex*>(out);
    for(int32_t i = 0; i < size; ++ i){
        out_cast->eval_fftwl[i][0] = this->eval_fftwl[i][0] + other_cast->eval_fftwl[i][0];
        out_cast->eval_fftwl[i][1] = this->eval_fftwl[i][1] + other_cast->eval_fftwl[i][1];
    }       
}
 
void PolynomialEvalFormFFTWLongComplex::sub(PolynomialEvalForm *out, PolynomialEvalForm *other){
    PolynomialEvalFormFFTWLongComplex* other_cast = static_cast<PolynomialEvalFormFFTWLongComplex*>(other);
    PolynomialEvalFormFFTWLongComplex* out_cast = static_cast<PolynomialEvalFormFFTWLongComplex*>(out);
    for(int32_t i = 0; i < size; ++i){
        out_cast->eval_fftwl[i][0] = this->eval_fftwl[i][0] - other_cast->eval_fftwl[i][0];
        out_cast->eval_fftwl[i][1] = this->eval_fftwl[i][1] - other_cast->eval_fftwl[i][1];
    } 
}

void PolynomialEvalFormFFTWLongComplex::mul(PolynomialEvalForm *out, int64_t scalar){
    PolynomialEvalFormFFTWLongComplex* out_cast = static_cast<PolynomialEvalFormFFTWLongComplex*>(out);
    for(int32_t i = 0; i < size; ++i){
            out_cast->eval_fftwl[i][0] = this->eval_fftwl[i][0] * scalar;
            out_cast->eval_fftwl[i][1] = this->eval_fftwl[i][1] * scalar;
        } 
}
 
void PolynomialEvalFormFFTWLongComplex::neg(PolynomialEvalForm *out){
    PolynomialEvalFormFFTWLongComplex* out_cast = static_cast<PolynomialEvalFormFFTWLongComplex*>(out);
    for(int32_t i = 0; i < size; ++i){
            out_cast->eval_fftwl[i][0] = -this->eval_fftwl[i][0];
            out_cast->eval_fftwl[i][1] = -this->eval_fftwl[i][1];
        } 
}
 
void PolynomialEvalFormFFTWLongComplex::mod_reduce(int64_t Q){
}
 
Polynomial::~Polynomial(){ 
    if(this->is_init){
        delete[] coefs; 
    } 
}

Polynomial::Polynomial(int32_t degree, int64_t coef_modulus){
    this->init(degree, coef_modulus);
}
 
Polynomial::Polynomial(int32_t degree, int64_t coef_modulus, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine){
    this->init(degree, coef_modulus);
    this->mul_engine = mul_engine;
    is_mul_engine_set = true; 
}

Polynomial::Polynomial(int32_t degree, int64_t coef_modulus, std::shared_ptr<PolynomialInversionEngine> inv_engine){
    this->init(degree, coef_modulus);
    this->inv_engine = inv_engine;
    this->is_inv_engine_set = true;
}

Polynomial::Polynomial(int32_t degree, int64_t coef_modulus, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine, std::shared_ptr<PolynomialInversionEngine> inv_engine){
    this->init(degree, coef_modulus);
    this->mul_engine = mul_engine;
    is_mul_engine_set = true; 
    this->inv_engine = inv_engine;
    this->is_inv_engine_set = true;
}

void Polynomial::init(int32_t degree, int64_t coef_modulus){
    this->degree = degree;
    this->coef_modulus = coef_modulus;
    this->coef_modulus_bit_size = Utils::power_times(coef_modulus, 2);
    this->coefs = new int64_t[degree];
    this->is_init = true;
}
 
Polynomial::Polynomial(const Polynomial &other){
    this->init(other.degree, other.coef_modulus); 
    Utils::cp(this->coefs, other.coefs, this->degree);  
    this->mul_engine = other.mul_engine;
    this->is_mul_engine_set = other.is_mul_engine_set; 
    this->inv_engine = other.inv_engine;
    this->is_inv_engine_set = other.is_inv_engine_set;
} 
  
Polynomial& Polynomial::operator=(const Polynomial other){
    if(!this->is_init){ 
        this->init(other.degree, other.coef_modulus);
    }
    Utils::cp(this->coefs, other.coefs, this->degree);  
    this->mul_engine = other.mul_engine;
    this->is_mul_engine_set = other.is_mul_engine_set; 
    this->inv_engine = other.inv_engine;
    this->is_inv_engine_set = other.is_inv_engine_set;
    return *this;
}
 
void Polynomial::set_multiplication_engine(std::shared_ptr<PolynomialMultiplicationEngine> mul_engine){
    this->mul_engine = mul_engine;
    this->is_mul_engine_set = true; 
}

void Polynomial::set_inversion_engine(std::shared_ptr<PolynomialInversionEngine> inv_engine){
    this->inv_engine = inv_engine;
    this->is_inv_engine_set = true; 
}

void Polynomial::cyclic_rotate(Polynomial *out, int64_t rotation){
    Utils::rotate_poly(out->coefs, this->coefs, this->degree, rotation);  
}

void Polynomial::negacyclic_rotate(Polynomial *out, int64_t rotation){   
    Utils::negacyclic_rotate_poly(out->coefs, this->coefs, this->degree, rotation);  
    Utils::array_mod_form(out->coefs, out->coefs, this->degree, this->coef_modulus);
}
 
void Polynomial::to_eval(PolynomialEvalForm *out){ 
    mul_engine->to_eval(out, this);
}
 
void Polynomial::zeroize(){
    for(int32_t i = 0; i < degree; ++i){
        coefs[i] = 0;
    }
}

Polynomial Polynomial::clone(){
    if(!is_init){
        return Polynomial(degree, coef_modulus);
    }
    Polynomial out;
    if(is_mul_engine_set && is_inv_engine_set){
        out = Polynomial(degree, coef_modulus, mul_engine, inv_engine);
    }else if(is_mul_engine_set){
        out = Polynomial(degree, coef_modulus, mul_engine);
    }else if(is_inv_engine_set){
        out = Polynomial(degree, coef_modulus, inv_engine);
    }
    Utils::cp(out.coefs, coefs, degree);
    out.is_init = true;
    return out;
}
 
void Polynomial::add(Polynomial *out, Polynomial *other){
    if(this->degree != other->degree){
        throw std::logic_error("Polynomial::add: Both Polynomials must be the same size!");
    }
    if(this->coef_modulus != other->coef_modulus){
        throw std::logic_error("Polynomial::add: Both Polynomials must have the same coefficient modulus!");
    } 
    this->add_coef(out, other);  
}

void Polynomial::add_coef(Polynomial *out, Polynomial *other){
    for(int32_t i = 0; i < degree; ++i){
        out->coefs[i] = coefs[i] + other->coefs[i];
        out->coefs[i] %= this->coef_modulus;
    }
}


void Polynomial::sub(Polynomial *out, Polynomial *other){ 
    if(this->degree != other->degree){
        throw std::logic_error("Polynomial::add: Both Polynomials must be the same size!");
    }
    if(this->coef_modulus != other->coef_modulus){
        throw std::logic_error("Polynomial::add: Both Polynomials must have the same coefficient modulus!");
    }
    sub_coef(out, other);
}

void Polynomial::sub_coef(Polynomial *out, Polynomial *other){
    for(int32_t i = 0; i < degree; ++i){
        out->coefs[i] = this->coefs[i] - other->coefs[i];    
    }
    Utils::array_mod_form(out->coefs, out->coefs, degree, this->coef_modulus); 
}

void Polynomial::neg(Polynomial *out){
    neg_coef(out);  
}

void Polynomial::neg_coef(Polynomial *out){
    for(int32_t i = 0; i < degree; ++i){
        out->coefs[i] = -this->coefs[i];
    }
    Utils::array_mod_form(out->coefs, out->coefs, degree, this->coef_modulus); 
}

void Polynomial::mul(Polynomial *out, int64_t scalar){ 
    if(this->degree != out->degree){
        throw std::logic_error("Polynomial::mul(Polynomial *out, int64_t scalar): Degrees of polynomials don't match!");
    }
    if(this->coef_modulus != out->coef_modulus){
        throw std::logic_error("Polynomial::mul(Polynomial *out, int64_t scalar): Coefficient moduli of polynomials don't match!");
    } 
    int32_t scalar_bit_size = Utils::number_of_bits(scalar);
    if((scalar_bit_size + this->coef_modulus_bit_size) < 64){
        for(int32_t j=0; j < this->degree; ++j){ 
            out->coefs[j] = (this->coefs[j] * scalar) % this->coef_modulus;  
        }
    }else{
        /// TODO: The case where the scalar is bigger is handled by LongIntegerMultipler class in util.h. Use it here.
         // Note that we need to handle the case scalar is bigger. 
        int32_t free_bits = 63 - this->coef_modulus_bit_size;
        int64_t div = Utils::pow(free_bits, 2); 
        for(int32_t j=0; j < this->degree; ++j){  
            int64_t temp_scalar = scalar;
            while(temp_scalar > div){ 
                /// TODO: Make bit shift with free_bits instead of difision
                temp_scalar /= div; 
                out->coefs[j] = (this->coefs[j] * div) % this->coef_modulus;  
            }  
            out->coefs[j] = (this->coefs[j] * temp_scalar) % this->coef_modulus;   
        } 
    } 
}

void Polynomial::mul(Polynomial *out, Polynomial *other){   
    if(this->is_mul_engine_set){ 
        this->mul(out, other, this->mul_engine); 
    }else{
        throw std::logic_error("Polynomial::mul(Polynomial *out, Polynomial *other): No multiplication engin set!");
    }
}

void Polynomial::mul(Polynomial *out, Polynomial *other, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine){  
    mul_engine->mul(out, this, other); 
}
  
void Polynomial::inv(Polynomial *out){
    this->inv_engine->inv(out, *this);
}

void Polynomial::inv(Polynomial *out, std::shared_ptr<PolynomialInversionEngine> inv_engine){
    inv_engine->inv(out, *this);
}
 
PolynomialArrayCoefForm::~PolynomialArrayCoefForm(){ 
    if(this->is_init){
        delete[] poly_array;
    } 
}

PolynomialArrayCoefForm::PolynomialArrayCoefForm(int32_t degree, int64_t coef_modulus, int32_t array_size){
    this->init(degree, coef_modulus, array_size);
}
 
PolynomialArrayCoefForm::PolynomialArrayCoefForm(int32_t degree, int64_t coef_modulus, int32_t array_size, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine){ 
    this->init(degree, coef_modulus, array_size);
    this->mul_engine = mul_engine;
    is_mul_engine_set = true; 
}
  
void PolynomialArrayCoefForm::init(int32_t degree, int64_t coef_modulus, int32_t array_size){ 
    this->degree = degree;
    this->coef_modulus = coef_modulus;
    this->array_size = array_size; 
    this->full_size = this->array_size * this->degree; 
    this->poly_array = new int64_t[full_size];
    this->is_init = true; 
}
 
PolynomialArrayCoefForm::PolynomialArrayCoefForm(const PolynomialArrayCoefForm &other){
    this->init(other.degree, other.coef_modulus, other.array_size); 
    Utils::cp(this->poly_array, other.poly_array, this->full_size);  
    this->mul_engine = other.mul_engine;
    this->is_mul_engine_set = other.is_mul_engine_set;  
} 
  
PolynomialArrayCoefForm& PolynomialArrayCoefForm::operator=(const PolynomialArrayCoefForm other){
    this->init(other.degree, other.coef_modulus, other.array_size);
    Utils::cp(this->poly_array, other.poly_array, this->full_size);  
    this->mul_engine = other.mul_engine;
    this->is_mul_engine_set = other.is_mul_engine_set;  
    return *this;
}

void PolynomialArrayCoefForm::set_polynomial_at(int32_t i, Polynomial *poly){
    if(poly->degree != this->degree){
        throw std::logic_error("PolynomialArrayCoefForm::set_polynomial_at(int32_t i, Polynomial *poly): degrees are inconsistent.");
    }
    if(poly->coef_modulus != this->coef_modulus){
        throw std::logic_error("PolynomialArrayCoefForm::set_polynomial_at(int32_t i, Polynomial *poly): coef_moduli are inconsistent.");
    }
    for(int32_t j = 0; j < this->degree; ++j){
        this->poly_array[i * degree + j] = poly->coefs[j];
    }
}
  
void PolynomialArrayCoefForm::set_multiplication_engine(std::shared_ptr<PolynomialMultiplicationEngine> mul_engine){
    this->mul_engine = mul_engine;
}
  
void PolynomialArrayCoefForm::add(PolynomialArrayCoefForm *out, PolynomialArrayCoefForm *other){
    for(int32_t i = 0; i < full_size; ++i){
        out->poly_array[i] = poly_array[i] + other->poly_array[i];
        out->poly_array[i] %= this->coef_modulus;
    }
}
  
void PolynomialArrayCoefForm::sub(PolynomialArrayCoefForm *out, PolynomialArrayCoefForm *other){
    for(int32_t i = 0; i < full_size; ++i){
        out->poly_array[i] = this->poly_array[i] - other->poly_array[i];    
    }
    Utils::array_mod_form(out->poly_array, out->poly_array, full_size, this->coef_modulus); 
}
  
void PolynomialArrayCoefForm::neg(PolynomialArrayCoefForm *out){
    for(int32_t i = 0; i < full_size; ++i){
        out->poly_array[i] = -this->poly_array[i];
    }
    Utils::array_mod_form(out->poly_array, out->poly_array, full_size, this->coef_modulus); 
}
  
void PolynomialArrayCoefForm::mul(PolynomialArrayCoefForm *out, int64_t scalar){
    for(int32_t i = 0; i < full_size; ++i){
        out->poly_array[i] = poly_array[i] + scalar;
        out->poly_array[i] %= this->coef_modulus;
    }
}

PolynomialArrayEvalFormLong::~PolynomialArrayEvalFormLong(){
    if(this->is_init){
        delete[] eval_long;
    } 
}

PolynomialArrayEvalFormLong::PolynomialArrayEvalFormLong(int32_t array_size, int64_t degree, int64_t coef_modulus){
    this->array_size = array_size;
    this->size = degree;
    this->coef_modulus = coef_modulus;
    this->full_size = array_size * this->size;
    this->eval_long = new int64_t[full_size];
    this->is_init = true; 
}

void PolynomialArrayEvalFormLong::add(PolynomialArrayEvalForm *out, PolynomialArrayEvalForm *other){
    PolynomialArrayEvalFormLong* other_cast = static_cast<PolynomialArrayEvalFormLong*>(other);
    PolynomialArrayEvalFormLong* out_cast = static_cast<PolynomialArrayEvalFormLong*>(out);
    for(int32_t i = 0; i < full_size; ++i){
         out_cast->eval_long[i] = this->eval_long[i] + other_cast->eval_long[i];
    }
}

void PolynomialArrayEvalFormLong::sub(PolynomialArrayEvalForm *out, PolynomialArrayEvalForm *other){
    PolynomialArrayEvalFormLong* other_cast = static_cast<PolynomialArrayEvalFormLong*>(other);
    PolynomialArrayEvalFormLong* out_cast = static_cast<PolynomialArrayEvalFormLong*>(out);
    for(int32_t i = 0; i < full_size; ++i){
         out_cast->eval_long[i] = this->eval_long[i] - other_cast->eval_long[i];
    }
}


void PolynomialArrayEvalFormLong::mul(PolynomialArrayEvalForm *out, int64_t scalar){
    PolynomialArrayEvalFormLong* out_cast = static_cast<PolynomialArrayEvalFormLong*>(out); 
    for(int32_t i = 0; i < full_size; ++i){
        out_cast->eval_long[i] = this->eval_long[i] * scalar;
    }
}

void PolynomialArrayEvalFormLong::neg(PolynomialArrayEvalForm *out){
    PolynomialArrayEvalFormLong* out_cast = static_cast<PolynomialArrayEvalFormLong*>(out); 
    for(int32_t i = 0; i < full_size; ++i){
        out_cast->eval_long[i] = -this->eval_long[i];
    }
}

void PolynomialArrayEvalFormLong::mod_reduce(int64_t modulus){
    Utils::array_mod_form(this->eval_long, this->eval_long, full_size, modulus); 
}


PolynomialArrayEvalFormFFTWComplex::~PolynomialArrayEvalFormFFTWComplex(){
    if(this->is_init){
        delete[] eval_fftw;
    }
}   

PolynomialArrayEvalFormFFTWComplex::PolynomialArrayEvalFormFFTWComplex(FFTWNegacyclicEngine* mul_engine, int32_t array_size){ 
    this->array_size = array_size;
    this->size = mul_engine->engine.plan_size; 
    this->coef_modulus = mul_engine->coef_modulus;
    this->full_size = this->size * array_size; 
    this->eval_fftw = new fftw_complex[full_size];   
    this->is_init = true;
}


void PolynomialArrayEvalFormFFTWComplex::add(PolynomialArrayEvalForm *out, PolynomialArrayEvalForm *other){
    PolynomialArrayEvalFormFFTWComplex* other_cast = static_cast<PolynomialArrayEvalFormFFTWComplex*>(other);
    PolynomialArrayEvalFormFFTWComplex* out_cast = static_cast<PolynomialArrayEvalFormFFTWComplex*>(out);
    for(int32_t i = 0; i < full_size; ++i){
            out_cast->eval_fftw[i][0] = this->eval_fftw[i][0] + other_cast->eval_fftw[i][0];
            out_cast->eval_fftw[i][1] = this->eval_fftw[i][1] + other_cast->eval_fftw[i][1];
        } 
}

void PolynomialArrayEvalFormFFTWComplex::sub(PolynomialArrayEvalForm *out, PolynomialArrayEvalForm *other){
    PolynomialArrayEvalFormFFTWComplex* other_cast = static_cast<PolynomialArrayEvalFormFFTWComplex*>(other);
    PolynomialArrayEvalFormFFTWComplex* out_cast = static_cast<PolynomialArrayEvalFormFFTWComplex*>(out);
    for(int32_t i = 0; i < full_size; ++i){
            out_cast->eval_fftw[i][0] = this->eval_fftw[i][0] - other_cast->eval_fftw[i][0];
            out_cast->eval_fftw[i][1] = this->eval_fftw[i][1] - other_cast->eval_fftw[i][1];
        } 
}


void PolynomialArrayEvalFormFFTWComplex::mul(PolynomialArrayEvalForm *out, int64_t scalar){
    PolynomialArrayEvalFormFFTWComplex* out_cast = static_cast<PolynomialArrayEvalFormFFTWComplex*>(out);
     for(int32_t i = 0; i < full_size; ++i){
            out_cast->eval_fftw[i][0] = this->eval_fftw[i][0] * scalar;
            out_cast->eval_fftw[i][1] = this->eval_fftw[i][1] * scalar;
        } 
}

void PolynomialArrayEvalFormFFTWComplex::neg(PolynomialArrayEvalForm *out){
    PolynomialArrayEvalFormFFTWComplex* out_cast = static_cast<PolynomialArrayEvalFormFFTWComplex*>(out);
    for(int32_t i = 0; i < full_size; ++i){
            out_cast->eval_fftw[i][0] = -this->eval_fftw[i][0];
            out_cast->eval_fftw[i][1] = -this->eval_fftw[i][1];
        } 
}

void PolynomialArrayEvalFormFFTWComplex::mod_reduce(int64_t modulus){ 
}


PolynomialArrayEvalFormFFTWLongComplex::~PolynomialArrayEvalFormFFTWLongComplex(){
    if(this->is_init){
        delete[] eval_fftwl;
    }
}

PolynomialArrayEvalFormFFTWLongComplex::PolynomialArrayEvalFormFFTWLongComplex(FFTWLongNegacyclicEngine* mul_engine, int32_t array_size){ 
    this->array_size = array_size;
    this->size = mul_engine->engine.plan_size;
    this->coef_modulus = mul_engine->coef_modulus;
    this->full_size = this->size * array_size; 
    this->eval_fftwl = new fftwl_complex[full_size];  
    this->is_init = true;
}

void PolynomialArrayEvalFormFFTWLongComplex::add(PolynomialArrayEvalForm *out, PolynomialArrayEvalForm *other){
    PolynomialArrayEvalFormFFTWLongComplex* out_cast = static_cast<PolynomialArrayEvalFormFFTWLongComplex*>(out);
    PolynomialArrayEvalFormFFTWLongComplex* other_cast = static_cast<PolynomialArrayEvalFormFFTWLongComplex*>(other);
    for(int32_t i = 0; i < full_size; ++i){
        out_cast->eval_fftwl[i][0] = this->eval_fftwl[i][0] + other_cast->eval_fftwl[i][0];
        out_cast->eval_fftwl[i][1] = this->eval_fftwl[i][1] + other_cast->eval_fftwl[i][1];
    } 
}

void PolynomialArrayEvalFormFFTWLongComplex::sub(PolynomialArrayEvalForm *out, PolynomialArrayEvalForm *other){
    PolynomialArrayEvalFormFFTWLongComplex* out_cast = static_cast<PolynomialArrayEvalFormFFTWLongComplex*>(out);
    PolynomialArrayEvalFormFFTWLongComplex* other_cast = static_cast<PolynomialArrayEvalFormFFTWLongComplex*>(other);
    for(int32_t i = 0; i < full_size; ++i){
        out_cast->eval_fftwl[i][0] = this->eval_fftwl[i][0] - other_cast->eval_fftwl[i][0];
        out_cast->eval_fftwl[i][1] = this->eval_fftwl[i][1] - other_cast->eval_fftwl[i][1];
    } 
}

void PolynomialArrayEvalFormFFTWLongComplex::mul(PolynomialArrayEvalForm *out, int64_t scalar){
    PolynomialArrayEvalFormFFTWLongComplex* out_cast = static_cast<PolynomialArrayEvalFormFFTWLongComplex*>(out);
    for(int32_t i = 0; i < full_size; ++i){
        out_cast->eval_fftwl[i][0] = this->eval_fftwl[i][0] * scalar;
        out_cast->eval_fftwl[i][1] = this->eval_fftwl[i][1] * scalar;
    }
}

void PolynomialArrayEvalFormFFTWLongComplex::neg(PolynomialArrayEvalForm *out){
    PolynomialArrayEvalFormFFTWLongComplex* out_cast = static_cast<PolynomialArrayEvalFormFFTWLongComplex*>(out);
    for(int32_t i = 0; i < full_size; ++i){
        out_cast->eval_fftwl[i][0] = -this->eval_fftwl[i][0];
        out_cast->eval_fftwl[i][1] = -this->eval_fftwl[i][1];
    } 
}

void PolynomialArrayEvalFormFFTWLongComplex::mod_reduce(int64_t modulus){
}