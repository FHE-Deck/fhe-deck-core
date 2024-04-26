#include "polynomial.h"
 
using namespace fhe_deck;
 
  
IntelHexlNTTEngine::IntelHexlNTTEngine(int degree, long coef_modulus){ 
    this->degree = degree;
    this->coef_modulus = coef_modulus;
    this->ntt = intel::hexl::NTT(degree, coef_modulus);
    this->type = hexl_ntt;
}
 
void IntelHexlNTTEngine::to_coef(Polynomial *in){
    this->to_coef(in, in); 
}

void IntelHexlNTTEngine::to_coef(Polynomial *out, PolynomialEvalForm *in){
    ntt.ComputeInverse((uint64_t*) out->coefs, (uint64_t*)  in->eval_long, 1, 1);  
    out->is_eval_form = false;
}
 
void IntelHexlNTTEngine::to_coef(Polynomial *out, Polynomial *in){
    if(in->is_eval_form){ 
        to_coef(out, &in->poly_eval_form); 
    }else{
        Utils::cp(out->coefs, in->coefs, in->degree); 
    }
}

void IntelHexlNTTEngine::to_coef(PolynomialArrayCoefForm *out, PolynomialArrayEvalForm *in){
    long* in_poly;
    long* out_poly;
    for(int i = 0; i < in->array_size; ++i){
        in_poly = &in->eval_long[i * in->size];
        out_poly = &out->poly_array[i * out->degree];
        ntt.ComputeInverse((uint64_t*) out_poly, (uint64_t*) in_poly, 1, 1);  
    } 
}


void IntelHexlNTTEngine::to_eval(Polynomial *in){ 
    this->to_eval(in, in); 
}

void IntelHexlNTTEngine::to_eval(PolynomialEvalForm *out, Polynomial *in){ 
    // Here we make sure that the coefficients are in propper form.
    long* coefs_mod_form = new long[in->degree];
    Utils::array_mod_form(coefs_mod_form, in->coefs, in->degree, in->coef_modulus); 
    ntt.ComputeForward((uint64_t*) out->eval_long, (uint64_t*) coefs_mod_form, 1, 1);  
    delete[] coefs_mod_form;
}

void IntelHexlNTTEngine::to_eval(Polynomial *out, Polynomial *in){  
    if(in->is_eval_form){ 
        out->poly_eval_form = in->poly_eval_form;
        out->is_eval_form = true;
        return;
    }
    if(!out->poly_eval_form.is_init){  
        out->poly_eval_form = PolynomialEvalForm(new long[out->degree], out->degree, out->coef_modulus);   
    }   
    this->to_eval(&out->poly_eval_form, in); 
    out->is_eval_form = true; 
}

void IntelHexlNTTEngine::to_eval(PolynomialArrayEvalForm *out, PolynomialArrayCoefForm *in){
    long* in_poly;
    long* out_poly;
    for(int i = 0; i < in->array_size; ++i){
        in_poly = &in->poly_array[i * in->degree];
        out_poly = &out->eval_long[i * out->size];
        ntt.ComputeForward((uint64_t*) out_poly, (uint64_t*) in_poly, 1, 1);  
    } 
}

void IntelHexlNTTEngine::mul(PolynomialEvalForm *out, PolynomialEvalForm *in_1, PolynomialEvalForm *in_2){
    intel::hexl::EltwiseMultMod((uint64_t*) out->eval_long, 
                (uint64_t*) in_1->eval_long, 
                (uint64_t*) in_2->eval_long, 
                out->size, out->coef_modulus, 1);
}

void IntelHexlNTTEngine::mul(Polynomial *out, Polynomial *in_1, Polynomial *in_2){   
    if(!out->poly_eval_form.is_init){ 
        out->poly_eval_form = PolynomialEvalForm(new long[out->degree], out->degree, out->coef_modulus); 
    }
    if(in_1->is_eval_form && in_2->is_eval_form){
        this->mul(&out->poly_eval_form, &in_1->poly_eval_form, &in_2->poly_eval_form);
            out->is_eval_form = true; 
    }else{ 
        throw std::logic_error("IntelHexlNTTEngine::mul: Polynomials must be in eval form.");
    }
}

Polynomial IntelHexlNTTEngine::mul(Polynomial *in_1, Polynomial *in_2){ 
    if(in_1->degree != in_2->degree){
        throw std::logic_error("IntelHexlNTTEngine::mul: Size of polynomials doesn't match.");
    }
    if(in_1->coef_modulus != in_2->coef_modulus){
        throw std::logic_error("IntelHexlNTTEngine::mul: Coefficient modulus doesn't match.");
    }
    Polynomial out(in_1->degree, in_1->coef_modulus); 
    mul(&out, in_1, in_2);    
    return out;
}

void IntelHexlNTTEngine::multisum(Polynomial *out, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2, bool coef_form){  


    long* in_1_temp = in_1->poly_array;
    long* in_2_temp = in_2->eval_long;
    long* temp = new long[in_2->size];  
    Utils::array_mod_form(in_1_temp, in_1_temp, in_1->degree, in_1->coef_modulus); 
    ntt.ComputeForward((uint64_t*) temp, (uint64_t*) in_1_temp, 1, 1);  
    intel::hexl::EltwiseMultMod((uint64_t*) out->coefs, (uint64_t*) temp, (uint64_t*) in_2_temp, in_2->size, in_2->coef_modulus, 1);

    for(int i = 1; i < in_2->array_size; ++i){
        in_1_temp = &in_1->poly_array[i * in_1->degree];
        in_2_temp = &in_2->eval_long[i * in_2->size];
        Utils::array_mod_form(in_1_temp, in_1_temp, in_1->degree, in_1->coef_modulus); 
        ntt.ComputeForward((uint64_t*) temp, (uint64_t*) in_1_temp, 1, 1);  
        intel::hexl::EltwiseMultMod((uint64_t*) temp, (uint64_t*) temp, (uint64_t*) in_2_temp, in_2->size, in_2->coef_modulus, 1);
        intel::hexl::EltwiseAddMod((uint64_t*) out->coefs, (uint64_t*) temp, (uint64_t*) out->coefs, in_2->size, in_2->coef_modulus);
    }
    if(coef_form){ 
        ntt.ComputeInverse((uint64_t*) out->coefs, (uint64_t*) out->coefs, 1, 1);  
    }
    delete[] temp;

}

FFTWNegacyclicEngine::FFTWNegacyclicEngine(int degree, long coef_modulus){ 
    this->degree = degree;
    this->coef_modulus = coef_modulus; 
    this->type = double_fft;
    engine = FFTPlan(negacyclic, degree, false);  
}
 
void FFTWNegacyclicEngine::to_eval(Polynomial *in){ 
    this->to_eval(in, in); 
}

void FFTWNegacyclicEngine::to_coef(Polynomial *in){
    this->to_coef(in, in); 
}

void FFTWNegacyclicEngine::to_eval(PolynomialEvalForm *out, Polynomial *in){
    engine.to_eval_form(out->eval_fftw, in->coefs); 
}

void FFTWNegacyclicEngine::to_eval(Polynomial *out, Polynomial *in){ 
    if(in->is_eval_form){ 
        out->poly_eval_form = in->poly_eval_form;
        out->is_eval_form = true;
        return;
    }
    if(!out->poly_eval_form.is_init){ 
        out->poly_eval_form = PolynomialEvalForm(engine.init_fft_poly(), engine.plan_size, out->coef_modulus); 
    } 
    to_eval(&out->poly_eval_form, in); 
    out->is_eval_form = true;
}

void FFTWNegacyclicEngine::to_eval(PolynomialArrayEvalForm *out, PolynomialArrayCoefForm *in){ 
    long *in_poly;
    fftw_complex *out_poly;
    for (int i = 0; i < in->array_size; ++i)
    {  
        in_poly = &in->poly_array[i * in->degree];
        out_poly = &out->eval_fftw[i * out->size];  
        engine.to_eval_form_scale(out_poly, in_poly, 2.0);  
    } 
}

void FFTWNegacyclicEngine::to_coef(Polynomial *out, PolynomialEvalForm *in){ 
    engine.to_coef_form(out->coefs, in->eval_fftw);
    // Divide by the scale (polynomial size times two.)
    // NOTE: For FHE its nice to scale one of the polynomials in the key
    // That is this rescaling could be precomputed. But here the Engine and later Polynomial class are oblivious to that.
    // Maybe we can add precomputation in the future - now its not a bootleneck anyway.
    double scale = (double)(engine.plan_size * 2);
    for(int i = 0; i < degree; ++i){   
        out->coefs[i] = round((double)out->coefs[i] / scale); 
    }
    out->is_eval_form = false;
}
 
void FFTWNegacyclicEngine::to_coef(Polynomial *out, Polynomial *in){
     if(in->is_eval_form){ 
        to_coef(out, &in->poly_eval_form); 
    }else{
        Utils::cp(out->coefs, in->coefs, in->degree);
        out->is_eval_form = false;
    }
}

void FFTWNegacyclicEngine::to_coef(PolynomialArrayCoefForm *out, PolynomialArrayEvalForm *in){
    long *out_poly;
    fftw_complex *in_poly;
    for (int i = 0; i < in->array_size; ++i)
    {
        in_poly = &in->eval_fftw[i * in->size];
        out_poly = &out->poly_array[i * out->degree];
        engine.to_coef_form(out_poly, in_poly); 
    }
}

void FFTWNegacyclicEngine::mul(PolynomialEvalForm *out, PolynomialEvalForm *in_1, PolynomialEvalForm *in_2){
    // Remind that one of the polynomials must be scaled by the plan_size times two. 
    engine.mul_eval_form(out->eval_fftw, 
            in_1->eval_fftw, 
            in_2->eval_fftw);  
}
 
void FFTWNegacyclicEngine::mul(Polynomial *out, Polynomial *in_1, Polynomial *in_2){   
    if(!out->poly_eval_form.is_init){  
        out->poly_eval_form = PolynomialEvalForm(engine.init_fft_poly(), engine.plan_size, out->coef_modulus);
    }
    if(in_1->is_eval_form && in_2->is_eval_form){ 
        this->mul(&out->poly_eval_form, &in_1->poly_eval_form, &in_2->poly_eval_form); 
            out->is_eval_form = true;  
    }else{ 
        throw std::logic_error("FFTWNegacyclicEngine::mul: Polynomials must be in eval form.");
    }
}

Polynomial FFTWNegacyclicEngine::mul(Polynomial *in_1, Polynomial *in_2){
    if(in_1->degree != in_2->degree){
        throw std::logic_error("FFTWNegacyclicEngine::mul: Size of polynomials doesn't match.");
    }
    if(in_1->coef_modulus != in_2->coef_modulus){
        throw std::logic_error("FFTWNegacyclicEngine::mul: Coefficient modulus doesn't match.");
    }
    Polynomial out(in_1->degree, in_1->coef_modulus); 
    this->mul(&out, in_1, in_2);    
    return out;
}


void FFTWNegacyclicEngine::multisum(Polynomial *out, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2, bool coef_form){   
    long* in_1_temp = in_1->poly_array;
    fftw_complex* in_2_temp = in_2->eval_fftw;
    fftw_complex* fft_prod_new = new fftw_complex[in_2->size]; 
    fftw_complex* fft_multisum_eval_new = new fftw_complex[in_2->size]; 
    
    engine.to_eval_form(fft_multisum_eval_new, in_1_temp);   
    engine.mul_eval_form(fft_multisum_eval_new, fft_multisum_eval_new, in_2_temp);  
 
    for(int i = 1; i < in_2->array_size; ++i){
        in_1_temp = &in_1->poly_array[i * in_1->degree];
        in_2_temp = &in_2->eval_fftw[i * in_2->size];
        
        engine.to_eval_form(fft_prod_new, in_1_temp);  
        engine.mul_eval_form(fft_prod_new, fft_prod_new, in_2_temp); 
        engine.add_eval_form(fft_multisum_eval_new, fft_multisum_eval_new, fft_prod_new); 
    }
    if(coef_form){ 
        engine.to_coef_form(out->coefs, fft_multisum_eval_new);
        Utils::array_mod_form(out->coefs, out->coefs, in_1->degree, in_1->coef_modulus);
        out->is_eval_form = false; 
    }
    delete[] fft_prod_new; 
    delete[] fft_multisum_eval_new; 
}
 


FFTWLongNegacyclicEngine::FFTWLongNegacyclicEngine(int degree, long coef_modulus){ 
    this->degree = degree;
    this->coef_modulus = coef_modulus; 
    engine = FFTPlan(negacyclic, degree, true);  
    this->type = long_double_fft;
}
 
void FFTWLongNegacyclicEngine::to_eval(Polynomial *in){ 
    this->to_eval(in, in); 
}

void FFTWLongNegacyclicEngine::to_coef(Polynomial *in){
    this->to_coef(in, in); 
}
 
void FFTWLongNegacyclicEngine::to_eval(PolynomialEvalForm *out, Polynomial *in){
    engine.to_eval_form_l(out->eval_fftwl, in->coefs);   
}

void FFTWLongNegacyclicEngine::to_eval(Polynomial *out, Polynomial *in){ 
    if(in->is_eval_form){
        out->poly_eval_form = in->poly_eval_form;
        out->is_eval_form = true;
        return;
    }
    if(!out->poly_eval_form.is_init){ 
        out->poly_eval_form = PolynomialEvalForm(engine.init_fft_poly_l(), engine.plan_size,  out->coef_modulus);
    } 
    to_eval(&out->poly_eval_form, in);   
    out->is_eval_form = true;
}

void FFTWLongNegacyclicEngine::to_eval(PolynomialArrayEvalForm *out, PolynomialArrayCoefForm *in){
    long *in_poly;
    fftwl_complex *out_poly;
    for (int i = 0; i < in->array_size; ++i)
    {
        in_poly = &in->poly_array[i * in->degree];
        out_poly = &out->eval_fftwl[i * out->size];
        engine.to_eval_form_l(out_poly, in_poly); 
    }
} 

void FFTWLongNegacyclicEngine::to_coef(Polynomial *out, PolynomialEvalForm *in){
    engine.to_coef_form_l(out->coefs, in->eval_fftwl);   
        double scale = (double)(engine.plan_size * 2);
        for(int i = 0; i < degree; ++i){   
            out->coefs[i] = round((double)out->coefs[i] / scale); 
        }
        out->is_eval_form = false;
}
 
void FFTWLongNegacyclicEngine::to_coef(Polynomial *out, Polynomial *in){
     if(in->is_eval_form){  
        to_coef(out, &in->poly_eval_form); 
    }else{
        Utils::cp(out->coefs, in->coefs, in->degree);
        out->is_eval_form = false;
    }
}

void FFTWLongNegacyclicEngine::to_coef(PolynomialArrayCoefForm *out, PolynomialArrayEvalForm *in){
    long *out_poly;
    fftwl_complex *in_poly;
    for (int i = 0; i < in->array_size; ++i)
    {
        in_poly = &in->eval_fftwl[i * in->size];
        out_poly = &out->poly_array[i * out->degree];
        engine.to_coef_form_l(out_poly, in_poly); 
    }
}

void FFTWLongNegacyclicEngine::mul(PolynomialEvalForm *out, PolynomialEvalForm *in_1, PolynomialEvalForm *in_2){
    engine.mul_eval_form_l(out->eval_fftwl, in_1->eval_fftwl, in_2->eval_fftwl);
}
 
void FFTWLongNegacyclicEngine::mul(Polynomial *out, Polynomial *in_1, Polynomial *in_2){  
    if(!out->poly_eval_form.is_init){ 
        out->poly_eval_form = PolynomialEvalForm(engine.init_fft_poly_l(), engine.plan_size, out->coef_modulus);
    }
    if(in_1->is_eval_form && in_2->is_eval_form){ 
        this->mul(&out->poly_eval_form, &in_1->poly_eval_form, &in_2->poly_eval_form);
        out->is_eval_form = true;  
    }else{ 
        throw std::logic_error("FFTWNegacyclicEngine::mul: Polynomials must be in eval form.");
    }
}

Polynomial FFTWLongNegacyclicEngine::mul(Polynomial *in_1, Polynomial *in_2){
    if(in_1->degree != in_2->degree){
        throw std::logic_error("FFTWNegacyclicEngine::mul: Size of polynomials doesn't match.");
    }
    if(in_1->coef_modulus != in_2->coef_modulus){
        throw std::logic_error("FFTWNegacyclicEngine::mul: Coefficient modulus doesn't match.");
    }
    Polynomial out(in_1->degree, in_1->coef_modulus); 
    mul(&out, in_1, in_2);    
    return out;
}

void FFTWLongNegacyclicEngine::multisum(Polynomial *out, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2, bool coef_form){
    long* in_1_temp = in_1->poly_array;
    fftwl_complex* in_2_temp = in_2->eval_fftwl;
    fftwl_complex* temp = new fftwl_complex[in_2->size]; 
    
    engine.to_eval_form_l(temp, in_1_temp);  
    engine.mul_eval_form_l(out->poly_eval_form.eval_fftwl, temp, in_2_temp);  

    for(int i = 1; i < in_2->array_size; ++i){
        in_1_temp = &in_1->poly_array[i * in_1->degree];
        in_2_temp = &in_2->eval_fftwl[i * in_2->size];
        
        engine.to_eval_form_l(temp, in_1_temp);  
        engine.mul_eval_form_l(temp, temp, in_2_temp); 
        engine.add_eval_form_l(out->poly_eval_form.eval_fftwl, out->poly_eval_form.eval_fftwl, temp); 
    }
    if(coef_form){
        this->to_coef(out); 
    }
}
 
NTLMultiplicationEngine::NTLMultiplicationEngine(int degree, long coef_modulus, RingType ring_type){ 
    this->degree = degree;
    this->coef_modulus = coef_modulus;  
    this->ring = this->get_ring_poly(ring_type); 
    this->type = ntl;
}
 
void NTLMultiplicationEngine::to_eval(Polynomial *in){ 
    throw std::runtime_error("NTLMultiplicationEngine::to_eval(Polynomial *in): Not supported for NTL.");
}

void NTLMultiplicationEngine::to_coef(Polynomial *in){
    throw std::runtime_error("NTLMultiplicationEngine::to_coef(Polynomial *in): Not supported for NTL.");
}
 
void NTLMultiplicationEngine::to_eval(PolynomialEvalForm *out, Polynomial *in){
    throw std::runtime_error("NTLMultiplicationEngine::to_eval(PolynomialEvalForm *out, Polynomial *in): Not supported for NTL.");
}

void NTLMultiplicationEngine::to_eval(Polynomial *out, Polynomial *in){
    throw std::runtime_error("NTLMultiplicationEngine::to_eval(Polynomial *out, Polynomial *in): Not supported for NTL.");
}

void NTLMultiplicationEngine::to_eval(PolynomialArrayEvalForm *out, PolynomialArrayCoefForm *in){
    throw std::runtime_error("NTLMultiplicationEngine::to_eval(PolynomialArrayEvalForm *out, PolynomialArrayCoefForm *in): Not supported for NTL.");
}

void NTLMultiplicationEngine::to_coef(Polynomial *out, PolynomialEvalForm *in){
    throw std::runtime_error("NTLMultiplicationEngine::to_coef(Polynomial *out, PolynomialEvalForm *in): Not supported for NTL.");
}
 
void NTLMultiplicationEngine::to_coef(Polynomial *out, Polynomial *in){
    throw std::runtime_error("NTLMultiplicationEngine::to_coef(Polynomial *out, Polynomial *in): Not supported for NTL.");
}

void NTLMultiplicationEngine::to_coef(PolynomialArrayCoefForm *out, PolynomialArrayEvalForm *in){
    throw std::runtime_error("NTLMultiplicationEngine::to_coef(PolynomialArrayCoefForm *out, PolynomialArrayEvalForm *in): Not supported for NTL.");
}
 
void NTLMultiplicationEngine::mul(PolynomialEvalForm *out, PolynomialEvalForm *in_1, PolynomialEvalForm *in_2){
    throw std::logic_error("NTLMultiplicationEngine::mul(PolynomialEvalForm *out, PolynomialEvalForm *in_1, PolynomialEvalForm *in_2): Not supported for NTL.");
}

void NTLMultiplicationEngine::mul(Polynomial *out, Polynomial *in_1, Polynomial *in_2){  
    NTL::ZZ_pX in_1_poly;
   this->set_polynomial_from_array(in_1_poly, in_1->coefs, degree, coef_modulus);
   NTL::ZZ_pX in_2_poly;
   this->set_polynomial_from_array(in_2_poly, in_2->coefs, degree, coef_modulus);
   NTL::ZZ_pX res = NTL::MulMod(in_1_poly, in_2_poly, ring); 
   this->set_array_from_polynomial(out->coefs, degree, res);
}

Polynomial NTLMultiplicationEngine::mul(Polynomial *in_1, Polynomial *in_2){
    if(in_1->degree != in_2->degree){
        throw std::logic_error("NTLMultiplicationEngine::mul: Size of polynomials doesn't match.");
    }
    if(in_1->coef_modulus != in_2->coef_modulus){
        throw std::logic_error("NTLMultiplicationEngine::mul: Coefficient modulus doesn't match.");
    }
    Polynomial out(in_1->degree, in_1->coef_modulus); 
    mul(&out, in_1, in_2);    
    return out;
}
 
void NTLMultiplicationEngine::multisum(Polynomial *out, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2, bool coef_form){
    throw std::runtime_error("NTLMultiplicationEngine::multisum(Polynomial *out, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2): Not implemented Yet.");
}

NTL::ZZ_pX NTLMultiplicationEngine::get_ring_poly(RingType ring){
    NTL::ZZ_pX out;
    long *psi_arr = new long[degree+1]; 
    psi_arr[degree] = 1;
    for(int i=1; i < degree; ++i){
            psi_arr[i] = 0;
    } 
    if(ring==cyclic){
        psi_arr[0] = coef_modulus-1;
    }else{
        psi_arr[0] = 1;
    }
    this->set_polynomial_from_array(out, psi_arr, degree+1, coef_modulus); 
    delete[] psi_arr;
    return out;
}

void NTLMultiplicationEngine::set_polynomial_from_array(NTL::ZZ_pX &poly, long *f, int sizeof_f, long Q){
    NTL::ZZ_p coef;
    coef.init(NTL::ZZ(Q));
    for(int i = 0; i < sizeof_f; ++i){
        coef = f[i];
        NTL::SetCoeff(poly, i, coef);
    } 
}

void NTLMultiplicationEngine::set_array_from_polynomial(long *f, int sizeof_array, NTL::ZZ_pX poly){ 
    for(int i = 0; i < sizeof_array; ++i){
        f[i] = 0;
    }
    long deg = NTL::deg(poly);
    for(int i = 0; i <= deg; ++i){
         f[i] = NTL::conv<long>(poly[i]);
    } 
}

void PolynomialMultiplicationEngineBuilder::set_coef_modulus(long coef_modulus){
    this->coef_modulus = coef_modulus;
}

void PolynomialMultiplicationEngineBuilder::set_degree(long degree){
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

PolynomialEvalForm::~PolynomialEvalForm(){
    if(is_eval_long){
        delete[] eval_long;
    }
    if(is_eval_fftw){
        delete[] eval_fftw;
    }
    if(is_eval_fftwl){
        delete[] eval_fftwl;
    }
}
 
PolynomialEvalForm::PolynomialEvalForm(long* eval_long, int size, long coef_modulus){ 
    this->eval_long = eval_long;  
    this->coef_modulus = coef_modulus;
    this->is_init = true;
    this->is_eval_long = true;
    this->size = size; 
}

PolynomialEvalForm::PolynomialEvalForm(fftw_complex* eval_fftw, int size, long coef_modulus){
    this->eval_fftw = eval_fftw;
    this->coef_modulus = coef_modulus;
    this->is_init = true;
    this->is_eval_fftw = true;
    this->size = size;
}

PolynomialEvalForm::PolynomialEvalForm(fftwl_complex* eval_fftwl, int size, long coef_modulus){
    this->eval_fftwl = eval_fftwl;
    this->coef_modulus = coef_modulus;
    this->is_init = true;
    this->is_eval_fftwl = true;
    this->size = size;
}
 
PolynomialEvalForm::PolynomialEvalForm(const PolynomialEvalForm &other){ 
    this->is_init = other.is_init;
    this->size = other.size;
    this->coef_modulus = other.coef_modulus;
    this->is_eval_long = other.is_eval_long;
    this->is_eval_fftw = other.is_eval_fftw;
    this->is_eval_fftwl = other.is_eval_fftwl; 
    if(is_eval_long){
        eval_long = new long[size];
        Utils::cp(this->eval_long, other.eval_long, size);
    }
    if(is_eval_fftw){
        eval_fftw = new fftw_complex[size];
        for(int i = 0; i < size; ++i){
            eval_fftw[i][0] = other.eval_fftw[i][0];
            eval_fftw[i][1] = other.eval_fftw[i][1];
        }
    }
    if(is_eval_fftwl){
        eval_fftwl = new fftwl_complex[size];
        for(int i = 0; i < size; ++i){
            eval_fftwl[i][0] = other.eval_fftwl[i][0];
            eval_fftwl[i][1] = other.eval_fftwl[i][1];
        }
    }
}

PolynomialEvalForm& PolynomialEvalForm::operator=(const PolynomialEvalForm other){ 
    this->is_init = other.is_init;
    this->size = other.size;
    this->coef_modulus = other.coef_modulus;
    this->is_eval_long = other.is_eval_long;
    this->is_eval_fftw = other.is_eval_fftw;
    this->is_eval_fftwl = other.is_eval_fftwl; 
    if(this->is_eval_long){ 
        this->eval_long = new long[this->size]; 
        Utils::cp(this->eval_long, other.eval_long, this->size);
    }
    if(this->is_eval_fftw){
        this->eval_fftw = new fftw_complex[size];
        for(int i = 0; i < size; ++i){
            this->eval_fftw[i][0] = other.eval_fftw[i][0];
            this->eval_fftw[i][1] = other.eval_fftw[i][1];
        }
    }
    if(this->is_eval_fftwl){
        this->eval_fftwl = new fftwl_complex[size];
        for(int i = 0; i < size; ++i){
            this->eval_fftwl[i][0] = other.eval_fftwl[i][0];
            this->eval_fftwl[i][1] = other.eval_fftwl[i][1];
        }
    }
    return *this;
}

void PolynomialEvalForm::zeroize(){
    if(this->is_eval_long){
        for(int i = 0; i < size; ++i){
            this->eval_long[i] = 0;
        }
    }else if(this->is_eval_fftw){
        for(int i = 0; i < size; ++i){
            this->eval_fftw[i][0] = 0;
            this->eval_fftw[i][1] = 0;
        }
    }else if(this->is_eval_fftwl){
        for(int i = 0; i < size; ++i){
            this->eval_fftwl[i][0] = 0;
            this->eval_fftwl[i][1] = 0;
        }
    }else{
        throw std::logic_error("PolynomialEvalForm::add: No evaluation form initialized!");
    }
}

void PolynomialEvalForm::add(PolynomialEvalForm *out, PolynomialEvalForm *other){
    if(out->is_eval_long && this->is_eval_long && other->is_eval_long){
        for(int i = 0; i < size; ++i){
            out->eval_long[i] = this->eval_long[i] + other->eval_long[i];
        }
    }else if(out->is_eval_fftw && this->is_eval_fftw && other->is_eval_fftw){ 
        for(int i = 0; i < size; ++i){
            out->eval_fftw[i][0] = this->eval_fftw[i][0] + other->eval_fftw[i][0];
            out->eval_fftw[i][1] = this->eval_fftw[i][1] + other->eval_fftw[i][1];
        } 
    }else if(out->is_eval_fftwl && this->is_eval_fftwl && other->is_eval_fftwl){
        for(int i = 0; i < size; ++i){
            out->eval_fftwl[i][0] = this->eval_fftwl[i][0] + other->eval_fftwl[i][0];
            out->eval_fftwl[i][1] = this->eval_fftwl[i][1] + other->eval_fftwl[i][1];
        } 
    }else{
        throw std::logic_error("PolynomialEvalForm::add: No evaluation form initialized!");
    }
}

void PolynomialEvalForm::sub(PolynomialEvalForm *out, PolynomialEvalForm *other){
    if(out->is_eval_long && this->is_eval_long && other->is_eval_long){
        for(int i = 0; i < size; ++i){
            out->eval_long[i] = this->eval_long[i] - other->eval_long[i];
        }
    }else if(out->is_eval_fftw && this->is_eval_fftw && other->is_eval_fftw){ 
        for(int i = 0; i < size; ++i){
            out->eval_fftw[i][0] = this->eval_fftw[i][0] - other->eval_fftw[i][0];
            out->eval_fftw[i][1] = this->eval_fftw[i][1] - other->eval_fftw[i][1];
        } 
    }else if(out->is_eval_fftwl && this->is_eval_fftwl && other->is_eval_fftwl){
        for(int i = 0; i < size; ++i){
            out->eval_fftwl[i][0] = this->eval_fftwl[i][0] - other->eval_fftwl[i][0];
            out->eval_fftwl[i][1] = this->eval_fftwl[i][1] - other->eval_fftwl[i][1];
        } 
    }else{
        throw std::logic_error("PolynomialEvalForm::add: No evaluation form initialized!");
    }
}

void PolynomialEvalForm::mul(PolynomialEvalForm *out, long scalar){
    if(out->is_eval_long && this->is_eval_long){
        for(int i = 0; i < size; ++i){
            out->eval_long[i] = this->eval_long[i] * scalar;
        }
    }else if(out->is_eval_fftw && this->is_eval_fftw){ 
        for(int i = 0; i < size; ++i){
            out->eval_fftw[i][0] = this->eval_fftw[i][0] * scalar;
            out->eval_fftw[i][1] = this->eval_fftw[i][1] * scalar;
        } 
    }else if(out->is_eval_fftwl && this->is_eval_fftwl){
        for(int i = 0; i < size; ++i){
            out->eval_fftwl[i][0] = this->eval_fftwl[i][0] * scalar;
            out->eval_fftwl[i][1] = this->eval_fftwl[i][1] * scalar;
        } 
    }else{
        throw std::logic_error("PolynomialEvalForm::add: No evaluation form initialized!");
    }
}
 
void PolynomialEvalForm::neg(PolynomialEvalForm *out){
    if(out->is_eval_long && this->is_eval_long){
        for(int i = 0; i < size; ++i){
            out->eval_long[i] = -this->eval_long[i];
        }
    }else if(out->eval_fftw && this->eval_fftw){ 
        for(int i = 0; i < size; ++i){
            out->eval_fftw[i][0] = -this->eval_fftw[i][0];
            out->eval_fftw[i][1] = -this->eval_fftw[i][1];
        } 
    }else if(out->eval_fftwl && this->eval_fftwl){
        for(int i = 0; i < size; ++i){
            out->eval_fftwl[i][0] = -this->eval_fftwl[i][0];
            out->eval_fftwl[i][1] = -this->eval_fftwl[i][1];
        } 
    }else{
        throw std::logic_error("PolynomialEvalForm::add: No evaluation form initialized!");
    }
}
 
void PolynomialEvalForm::mod_reduce(long Q){
    if(this->eval_long){ 
        Utils::array_mod_form(this->eval_long, this->eval_long, size, Q); 
    } 
}
 
Polynomial::~Polynomial(){ 
    if(this->is_init){
        delete[] coefs;
    } 
}

Polynomial::Polynomial(int degree, long coef_modulus){
    this->init(degree, coef_modulus);
}
 
Polynomial::Polynomial(int degree, long coef_modulus, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine){
    this->init(degree, coef_modulus);
    this->mul_engine = mul_engine;
    is_mul_engine_set = true; 
}

Polynomial::Polynomial(int degree, long coef_modulus, std::shared_ptr<PolynomialInversionEngine> inv_engine){
    this->init(degree, coef_modulus);
    this->inv_engine = inv_engine;
    this->is_inv_engine_set = true;
}

Polynomial::Polynomial(int degree, long coef_modulus, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine, std::shared_ptr<PolynomialInversionEngine> inv_engine){
    this->init(degree, coef_modulus);
    this->mul_engine = mul_engine;
    is_mul_engine_set = true; 
    this->inv_engine = inv_engine;
    this->is_inv_engine_set = true;
}

void Polynomial::init(int degree, long coef_modulus){
    this->degree = degree;
    this->coef_modulus = coef_modulus;
    this->coef_modulus_bit_size = Utils::power_times(coef_modulus, 2);
    this->coefs = new long[degree];
    is_init = true;
}
 
Polynomial::Polynomial(const Polynomial &other){
    this->init(other.degree, other.coef_modulus); 
    Utils::cp(this->coefs, other.coefs, this->degree); 
    this->poly_eval_form = other.poly_eval_form;
    this->mul_engine = other.mul_engine;
    this->is_mul_engine_set = other.is_mul_engine_set; 
    this->inv_engine = other.inv_engine;
    this->is_inv_engine_set = other.is_inv_engine_set;
} 
  
Polynomial& Polynomial::operator=(const Polynomial other){
    this->init(other.degree, other.coef_modulus);
    Utils::cp(this->coefs, other.coefs, this->degree); 
    this->poly_eval_form = other.poly_eval_form;
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

void Polynomial::cyclic_rotate(Polynomial *out, long rotation){
    Utils::rotate_poly(out->coefs, this->coefs, this->degree, rotation);  
}

void Polynomial::negacyclic_rotate(Polynomial *out, long rotation){   
    Utils::negacyclic_rotate_poly(out->coefs, this->coefs, this->degree, rotation);  
    Utils::array_mod_form(out->coefs, out->coefs, this->degree, this->coef_modulus);
}

void Polynomial::to_eval(){
    mul_engine->to_eval(this);
}


void Polynomial::to_eval(PolynomialEvalForm *out){
    throw std::logic_error("Polynomial::to_eval(PolynomialEvalForm *out): Not Implemented Yet!");
}

void Polynomial::to_eval(Polynomial *out){
    if(this->degree != out->degree){
        throw std::logic_error("Polynomial::to_eval: Both Polynomials must be the same size!");
    }
    if(this->coef_modulus != out->coef_modulus){
        throw std::logic_error("Polynomial::to_eval: Both Polynomials must have the same coefficient modulus!");
    } 
    if(this->is_eval_form){
        out->poly_eval_form = this->poly_eval_form;
        out->is_eval_form = true;
    }else{ 
        Utils::cp(out->coefs, this->coefs, degree);
        mul_engine->to_eval(out); 
    }
}

void Polynomial::to_coef(){
    mul_engine->to_coef(this);
}

void Polynomial::to_coef(Polynomial *out){
    if(this->degree != out->degree){
        throw std::logic_error("Polynomial::to_coef: Both Polynomials must be the same size!");
    }
    if(this->coef_modulus != out->coef_modulus){
        throw std::logic_error("Polynomial::to_coef: Both Polynomials must have the same coefficient modulus!");
    }

    if(out->is_eval_form){
        out->poly_eval_form = this->poly_eval_form; 
        mul_engine->to_coef(out);
    }else{
        Utils::cp(out->coefs, this->coefs, degree);
    }
}

void Polynomial::zeroize(){
    if(this->is_eval_form){
        this->poly_eval_form.zeroize();
    }else{
        for(int i = 0; i < degree; ++i){
            coefs[i] = 0;
        }
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
    if(!is_eval_form){ 
        Utils::cp(out.coefs, coefs, degree);
        out.is_eval_form = false;
    }else{
        out.poly_eval_form = poly_eval_form;
        out.is_eval_form = true;
    }
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
    if(this->is_eval_form && other->is_eval_form){
        this->poly_eval_form.add(&out->poly_eval_form, &other->poly_eval_form); 
        out->poly_eval_form.mod_reduce(this->coef_modulus);
        return;
    }
    if(!this->is_eval_form && !other->is_eval_form){
        this->add_coef(out, other); 
        return;
    }
    else{
        throw std::logic_error("Polynomial::add: Both Polynomials must be in the same form (coef or eval)!");
    }
}

void Polynomial::add_coef(Polynomial *out, Polynomial *other){
    for(int i = 0; i < degree; ++i){
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
    if(this->is_eval_form && other->is_eval_form){
        this->poly_eval_form.sub(&out->poly_eval_form, &other->poly_eval_form);
        this->poly_eval_form.mod_reduce(this->coef_modulus);
        return;
    }
    if(!this->is_eval_form && !other->is_eval_form){ 
        sub_coef(out, other);
        return;
    }
    else{
        throw std::logic_error("Polynomial::add: Both Polynomials must be in the same form (coef or eval)!");
    }
}

void Polynomial::sub_coef(Polynomial *out, Polynomial *other){
    for(int i = 0; i < degree; ++i){
        out->coefs[i] = this->coefs[i] - other->coefs[i];    
    }
    Utils::array_mod_form(out->coefs, out->coefs, degree, this->coef_modulus); 
}

void Polynomial::neg(Polynomial *out){
    if(is_eval_form){
        this->poly_eval_form.neg(&out->poly_eval_form);
        out->poly_eval_form.mod_reduce(this->coef_modulus);
    }else{
        neg_coef(out); 
    }
}

void Polynomial::neg_coef(Polynomial *out){
    for(int i = 0; i < degree; ++i){
        out->coefs[i] = -this->coefs[i];
    }
    Utils::array_mod_form(out->coefs, out->coefs, degree, this->coef_modulus); 
}

void Polynomial::mul(Polynomial *out, long scalar){ 
    if(this->degree != out->degree){
        throw std::logic_error("Polynomial::mul(Polynomial *out, long scalar): Degrees of polynomials don't match!");
    }
    if(this->coef_modulus != out->coef_modulus){
        throw std::logic_error("Polynomial::mul(Polynomial *out, long scalar): Coefficient moduli of polynomials don't match!");
    }
    if(this->is_eval_form && out->is_eval_form){
        this->poly_eval_form.mul(&out->poly_eval_form, scalar);
    }else if(!this->is_eval_form && !out->is_eval_form){  
        int scalar_bit_size = Utils::number_of_bits(scalar);
        if((scalar_bit_size + this->coef_modulus_bit_size) < 64){
            for(int j=0; j < this->degree; ++j){ 
                out->coefs[j] = (this->coefs[j] * scalar) % this->coef_modulus;  
            }
        }else{
            // Note that we need to handle the case scalar is bigger. 
            int free_bits = 63 - this->coef_modulus_bit_size;
            long div = Utils::pow(free_bits, 2); 
            for(int j=0; j < this->degree; ++j){  
                long temp_scalar = scalar;
                while(temp_scalar > div){ 
                    // TODO: Make bit shift with free_bits
                    temp_scalar /= div; 
                    out->coefs[j] = (this->coefs[j] * div) % this->coef_modulus;  
                }  
                out->coefs[j] = (this->coefs[j] * temp_scalar) % this->coef_modulus;   
            } 
        }
    }else{
        throw std::logic_error("Polynomial::mul(Polynomial *out, Polynomial *other): No multiplication engin set!");
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
    // TODO Doesn't make sense here - Why not immediately compute the eval forms without playing around with those Polynomial classes?
    Polynomial eval_this(this->degree, this->coef_modulus);
    Polynomial eval_other(this->degree, this->coef_modulus); 
    mul_engine->to_eval(&eval_this, this); 
  
    mul_engine->to_eval(&eval_other, other);  
    mul_engine->mul(out, &eval_this, &eval_other);  
    mul_engine->to_coef(out);  
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

PolynomialArrayCoefForm::PolynomialArrayCoefForm(int degree, long coef_modulus, int array_size){
    this->init(degree, coef_modulus, array_size);
}
 
PolynomialArrayCoefForm::PolynomialArrayCoefForm(int degree, long coef_modulus, int array_size, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine){ 
    this->init(degree, coef_modulus, array_size);
    this->mul_engine = mul_engine;
    is_mul_engine_set = true; 
}
  
void PolynomialArrayCoefForm::init(int degree, long coef_modulus, int array_size){ 
    this->degree = degree;
    this->coef_modulus = coef_modulus;
    this->array_size = array_size; 
    this->full_size = this->array_size * this->degree; 
    this->poly_array = new long[full_size];
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

void PolynomialArrayCoefForm::set_polynomial_at(int i, Polynomial *poly){
    if(poly->degree != this->degree){
        throw std::logic_error("PolynomialArrayCoefForm::set_polynomial_at(int i, Polynomial *poly): degrees are inconsistent.");
    }
    if(poly->coef_modulus != this->coef_modulus){
        throw std::logic_error("PolynomialArrayCoefForm::set_polynomial_at(int i, Polynomial *poly): coef_moduli are inconsistent.");
    }
    for(int j = 0; j < this->degree; ++j){
        this->poly_array[i * degree + j] = poly->coefs[j];
    }
}
  
void PolynomialArrayCoefForm::set_multiplication_engine(std::shared_ptr<PolynomialMultiplicationEngine> mul_engine){
    this->mul_engine = mul_engine;
}
  
void PolynomialArrayCoefForm::add(PolynomialArrayCoefForm *out, PolynomialArrayCoefForm *other){
    for(int i = 0; i < full_size; ++i){
        out->poly_array[i] = poly_array[i] + other->poly_array[i];
        out->poly_array[i] %= this->coef_modulus;
    }
}
  
void PolynomialArrayCoefForm::sub(PolynomialArrayCoefForm *out, PolynomialArrayCoefForm *other){
    for(int i = 0; i < full_size; ++i){
        out->poly_array[i] = this->poly_array[i] - other->poly_array[i];    
    }
    Utils::array_mod_form(out->poly_array, out->poly_array, full_size, this->coef_modulus); 
}
  
void PolynomialArrayCoefForm::neg(PolynomialArrayCoefForm *out){
    for(int i = 0; i < full_size; ++i){
        out->poly_array[i] = -this->poly_array[i];
    }
    Utils::array_mod_form(out->poly_array, out->poly_array, full_size, this->coef_modulus); 
}
  
void PolynomialArrayCoefForm::mul(PolynomialArrayCoefForm *out, long scalar){
    for(int i = 0; i < full_size; ++i){
        out->poly_array[i] = poly_array[i] + scalar;
        out->poly_array[i] %= this->coef_modulus;
    }
}
   
 

PolynomialArrayEvalForm::~PolynomialArrayEvalForm(){ 
    if(this->is_init){
        if(is_eval_long){ 
            delete[] eval_long;
        }
        if(is_eval_fftw){ 
            delete[] eval_fftw;
        }
        if(is_eval_fftwl){ 
            delete[] eval_fftwl;
        }
    }
    
}


PolynomialArrayEvalForm::PolynomialArrayEvalForm(std::shared_ptr<PolynomialMultiplicationEngine> mul_engine, int array_size){ 
    this->is_init = true; 
    this->array_size = array_size; 
  
    if(mul_engine->type == hexl_ntt){ 
        std::shared_ptr<IntelHexlNTTEngine> engine = std::static_pointer_cast<IntelHexlNTTEngine>(mul_engine);
        this->size = engine->degree;
        this->coef_modulus = engine->coef_modulus;
        this->full_size = this->size * array_size; 
        this->eval_long = new long[full_size]; 
        this->is_eval_long = true;  
    }else if(mul_engine->type == double_fft){
        std::shared_ptr<FFTWNegacyclicEngine> engine = std::static_pointer_cast<FFTWNegacyclicEngine>(mul_engine); 
        this->size = engine->engine.plan_size; 
        this->coef_modulus = engine->coef_modulus;
        this->full_size = this->size * array_size; 
        this->eval_fftw = new fftw_complex[full_size];  
        this->is_eval_fftw = true;  
    }else if(mul_engine->type == long_double_fft){
        std::shared_ptr<FFTWLongNegacyclicEngine> engine = std::static_pointer_cast<FFTWLongNegacyclicEngine>(mul_engine);
        this->size = engine->engine.plan_size;
        this->coef_modulus = engine->coef_modulus;
        this->full_size = this->size * array_size; 
        this->eval_fftwl = new fftwl_complex[full_size]; 
        this->is_eval_fftwl = true; 
    }else{
        throw std::logic_error("PolynomialArrayEvalForm(std::shared_ptr<PolynomialMultiplicationEngine> mul_engine, int size, int array_size): Multiplication engine not suported!");
    } 
}
 


PolynomialArrayEvalForm::PolynomialArrayEvalForm(const PolynomialArrayEvalForm &other){ 
    this->is_init = other.is_init;
    this->size = other.size;
    this->is_eval_long = other.is_eval_long;
    this->is_eval_fftw = other.is_eval_fftw;
    this->is_eval_fftwl = other.is_eval_fftwl; 
    this->array_size = other.array_size;
    this->coef_modulus = other.coef_modulus;

    this->full_size = size * array_size;  
    if(this->is_eval_long){
        this->eval_long = new long[this->full_size];
        Utils::cp(this->eval_long, other.eval_long, this->full_size);
    }
    if(this->is_eval_fftw){
        this->eval_fftw = new fftw_complex[full_size];
        for(int i = 0; i < this->full_size; ++i){
            this->eval_fftw[i][0] = other.eval_fftw[i][0];
            this->eval_fftw[i][1] = other.eval_fftw[i][1];
        }
    }
    if(this->is_eval_fftwl){
        this->eval_fftwl = new fftwl_complex[full_size];
        for(int i = 0; i < this->full_size; ++i){
            this->eval_fftwl[i][0] = other.eval_fftwl[i][0];
            this->eval_fftwl[i][1] = other.eval_fftwl[i][1];
        }
    }
}


PolynomialArrayEvalForm& PolynomialArrayEvalForm::operator=(const PolynomialArrayEvalForm other){ 
 
    this->is_init = other.is_init;
    this->size = other.size;
    this->is_eval_long = other.is_eval_long;
    this->is_eval_fftw = other.is_eval_fftw;
    this->is_eval_fftwl = other.is_eval_fftwl; 
    this->array_size = other.array_size;
    this->coef_modulus = other.coef_modulus;
 
    this->full_size = size * array_size;  

    if(this->is_eval_long){
        this->eval_long = new long[full_size];
        Utils::cp(this->eval_long, other.eval_long, full_size);
    }
    if(this->is_eval_fftw){ 
        this->eval_fftw = new fftw_complex[full_size]; 
        for(int i = 0; i < this->full_size; ++i){
            this->eval_fftw[i][0] = other.eval_fftw[i][0];
            this->eval_fftw[i][1] = other.eval_fftw[i][1];
        } 
    }
    if(this->is_eval_fftwl){
        this->eval_fftwl = new fftwl_complex[full_size];
        for(int i = 0; i < full_size; ++i){
            this->eval_fftwl[i][0] = other.eval_fftwl[i][0];
            this->eval_fftwl[i][1] = other.eval_fftwl[i][1];
        }
    } 
    return *this;
}

 

void PolynomialArrayEvalForm::add(PolynomialArrayEvalForm &out, PolynomialArrayEvalForm &other){
    if(out.is_eval_long && this->is_eval_long && other.is_eval_long){
        for(int i = 0; i < full_size; ++i){
            out.eval_long[i] = this->eval_long[i] + other.eval_long[i];
        }
    }else if(out.is_eval_fftw && this->is_eval_fftw && other.is_eval_fftw){ 
        for(int i = 0; i < full_size; ++i){
            out.eval_fftw[i][0] = this->eval_fftw[i][0] + other.eval_fftw[i][0];
            out.eval_fftw[i][1] = this->eval_fftw[i][1] + other.eval_fftw[i][1];
        } 
    }else if(out.is_eval_fftwl && this->is_eval_fftwl && other.is_eval_fftwl){
        for(int i = 0; i < full_size; ++i){
            out.eval_fftwl[i][0] = this->eval_fftwl[i][0] + other.eval_fftwl[i][0];
            out.eval_fftwl[i][1] = this->eval_fftwl[i][1] + other.eval_fftwl[i][1];
        } 
    }else{
        throw std::logic_error("PolynomialEvalForm::add: No evaluation form initialized!");
    }
}


void PolynomialArrayEvalForm::sub(PolynomialArrayEvalForm &out, PolynomialArrayEvalForm &other){
    if(out.is_eval_long && this->is_eval_long && other.is_eval_long){
        for(int i = 0; i < full_size; ++i){
            out.eval_long[i] = this->eval_long[i] - other.eval_long[i];
        }
    }else if(out.is_eval_fftw && this->is_eval_fftw && other.is_eval_fftw){ 
        for(int i = 0; i < full_size; ++i){
            out.eval_fftw[i][0] = this->eval_fftw[i][0] - other.eval_fftw[i][0];
            out.eval_fftw[i][1] = this->eval_fftw[i][1] - other.eval_fftw[i][1];
        } 
    }else if(out.is_eval_fftwl && this->is_eval_fftwl && other.is_eval_fftwl){
        for(int i = 0; i < full_size; ++i){
            out.eval_fftwl[i][0] = this->eval_fftwl[i][0] - other.eval_fftwl[i][0];
            out.eval_fftwl[i][1] = this->eval_fftwl[i][1] - other.eval_fftwl[i][1];
        } 
    }else{
        throw std::logic_error("PolynomialEvalForm::add: No evaluation form initialized!");
    }
}

void PolynomialArrayEvalForm::mul(PolynomialArrayEvalForm &out, long scalar){
    if(out.is_eval_long && this->is_eval_long){
        for(int i = 0; i < full_size; ++i){
            out.eval_long[i] = this->eval_long[i] * scalar;
        }
    }else if(out.is_eval_fftw && this->is_eval_fftw){ 
        for(int i = 0; i < full_size; ++i){
            out.eval_fftw[i][0] = this->eval_fftw[i][0] * scalar;
            out.eval_fftw[i][1] = this->eval_fftw[i][1] * scalar;
        } 
    }else if(out.is_eval_fftwl && this->is_eval_fftwl){
        for(int i = 0; i < full_size; ++i){
            out.eval_fftwl[i][0] = this->eval_fftwl[i][0] * scalar;
            out.eval_fftwl[i][1] = this->eval_fftwl[i][1] * scalar;
        } 
    }else{
        throw std::logic_error("PolynomialEvalForm::add: No evaluation form initialized!");
    }
}

void PolynomialArrayEvalForm::neg(PolynomialArrayEvalForm &out){
    if(out.is_eval_long && this->is_eval_long){
        for(int i = 0; i < full_size; ++i){
            out.eval_long[i] = -this->eval_long[i];
        }
    }else if(out.eval_fftw && this->eval_fftw){ 
        for(int i = 0; i < full_size; ++i){
            out.eval_fftw[i][0] = -this->eval_fftw[i][0];
            out.eval_fftw[i][1] = -this->eval_fftw[i][1];
        } 
    }else if(out.eval_fftwl && this->eval_fftwl){
        for(int i = 0; i < full_size; ++i){
            out.eval_fftwl[i][0] = -this->eval_fftwl[i][0];
            out.eval_fftwl[i][1] = -this->eval_fftwl[i][1];
        } 
    }else{
        throw std::logic_error("PolynomialEvalForm::add: No evaluation form initialized!");
    }
}


void PolynomialArrayEvalForm::mod_reduce(long modulus){
    if(this->eval_long){ 
        Utils::array_mod_form(this->eval_long, this->eval_long, full_size, modulus); 
    } 
}
 









