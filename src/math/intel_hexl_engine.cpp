#include "math/intel_hexl_engine.h"

using namespace FHEDeck;
   
IntelHexlNTTEngine::IntelHexlNTTEngine(int32_t degree, int64_t coef_modulus){ 
    this->degree = degree;
    this->coef_modulus = coef_modulus;
    this->ntt = intel::hexl::NTT(degree, coef_modulus);
    this->type = PolynomialArithmetic::ntt64;
}
  
void IntelHexlNTTEngine::to_coef(Polynomial &out, const PolynomialEvalForm &in){ 
    const PolynomialEvalFormLongInteger& in_cast = static_cast<const PolynomialEvalFormLongInteger&>(in);
    ntt.ComputeInverse((uint64_t*) out.vec, (uint64_t*)  in_cast.eval_long, 1, 1);   
}
  
void IntelHexlNTTEngine::to_coef(PolynomialArrayCoefForm &out, const PolynomialArrayEvalForm &in){ 
    const PolynomialArrayEvalFormLong& in_cast = static_cast<const PolynomialArrayEvalFormLong&>(in);
    int64_t* in_poly;
    int64_t* out_poly;
    for(int32_t i = 0; i < in.array_size; ++i){
        in_poly = &in_cast.eval_long[i * in.size];
        out_poly = &out.poly_array[i * out.degree];
        ntt.ComputeInverse((uint64_t*) out_poly, (uint64_t*) in_poly, 1, 1);  
    } 
}

std::shared_ptr<PolynomialEvalForm> IntelHexlNTTEngine::init_polynomial_eval_form(){ 
    return std::make_shared<PolynomialEvalFormLongInteger>(new int64_t[degree], degree, coef_modulus);
}

std::shared_ptr<PolynomialArrayEvalForm> IntelHexlNTTEngine::init_polynomial_array_eval_form(int32_t array_size){ 
    return std::make_shared<PolynomialArrayEvalFormLong>(array_size, degree, coef_modulus); 
}
 
void IntelHexlNTTEngine::to_eval(PolynomialEvalForm &out, const Polynomial &in){  
    const PolynomialEvalFormLongInteger& out_cast = static_cast<const PolynomialEvalFormLongInteger&>(out);
    // Here we make sure that the coefficients are in propper form.
    int64_t* coefs_mod_form = new int64_t[in.degree];
    Utils::array_mod_form(coefs_mod_form, in.vec, in.degree, in.coef_modulus); 
    ntt.ComputeForward((uint64_t*) out_cast.eval_long, (uint64_t*) coefs_mod_form, 1, 1);  
    delete[] coefs_mod_form;
}
 
void IntelHexlNTTEngine::to_eval(PolynomialArrayEvalForm &out, const PolynomialArrayCoefForm &in){  
    const PolynomialArrayEvalFormLong& out_cast = static_cast<const PolynomialArrayEvalFormLong&>(out);
    int64_t* in_poly;
    int64_t* out_poly; 
    for(int32_t i = 0; i < in.array_size; ++i){
        in_poly = &in.poly_array[i * in.degree];
        out_poly = &out_cast.eval_long[i * out_cast.size];
        ntt.ComputeForward((uint64_t*) out_poly, (uint64_t*) in_poly, 1, 1);   
    } 
}

void IntelHexlNTTEngine::mul(PolynomialEvalForm &out, const PolynomialEvalForm &in_1, const PolynomialEvalForm &in_2){  
    PolynomialEvalFormLongInteger& out_cast = static_cast<PolynomialEvalFormLongInteger&>(out);
    const PolynomialEvalFormLongInteger& in_1_cast = static_cast<const PolynomialEvalFormLongInteger&>(in_1);
    const PolynomialEvalFormLongInteger& in_2_cast = static_cast<const PolynomialEvalFormLongInteger&>(in_2); 
    intel::hexl::EltwiseMultMod((uint64_t*) out_cast.eval_long, 
                (uint64_t*) in_1_cast.eval_long, 
                (uint64_t*) in_2_cast.eval_long, 
                out_cast.size, out_cast.coef_modulus, 1); 
}
 
void IntelHexlNTTEngine::multisum(Polynomial &out, const PolynomialArrayCoefForm &in_1, const PolynomialArrayEvalForm &in_2){    
    const PolynomialArrayEvalFormLong& in_2_cast = static_cast<const PolynomialArrayEvalFormLong&>(in_2);
    int64_t* in_1_temp = in_1.poly_array;
    int64_t* in_2_temp = in_2_cast.eval_long; 
    int64_t* temp = new int64_t[in_2_cast.size];   
    ntt.ComputeForward((uint64_t*) temp, (uint64_t*) in_1_temp, 1, 1);  
    intel::hexl::EltwiseMultMod((uint64_t*) out.vec, (uint64_t*) temp, (uint64_t*) in_2_temp, in_2_cast.size, in_2_cast.coef_modulus, 1); 
    for(int32_t i = 1; i < in_2_cast.array_size; ++i){
        in_1_temp = &in_1.poly_array[i * in_1.degree];
        in_2_temp = &in_2_cast.eval_long[i * in_2_cast.size];  
        ntt.ComputeForward((uint64_t*) temp, (uint64_t*) in_1_temp, 1, 1);  
        intel::hexl::EltwiseMultMod((uint64_t*) temp, (uint64_t*) temp, (uint64_t*) in_2_temp, in_2_cast.size, in_2_cast.coef_modulus, 1);
        intel::hexl::EltwiseAddMod((uint64_t*) out.vec, (uint64_t*) temp, (uint64_t*) out.vec, in_2_cast.size, in_2_cast.coef_modulus);
    }
    ntt.ComputeInverse((uint64_t*) out.vec, (uint64_t*) out.vec, 1, 1);  
    delete[] temp; 
}

void IntelHexlNTTEngine::multisum(Polynomial &out, const PolynomialArrayEvalForm &in_1, const PolynomialArrayEvalForm &in_2){    
    const PolynomialArrayEvalFormLong& in_1_cast = static_cast<const PolynomialArrayEvalFormLong&>(in_1);
    const PolynomialArrayEvalFormLong& in_2_cast = static_cast<const PolynomialArrayEvalFormLong&>(in_2);
    int64_t* in_1_temp = in_1_cast.eval_long;
    int64_t* in_2_temp = in_2_cast.eval_long; 
    int64_t* temp = new int64_t[in_2_cast.size];   
    intel::hexl::EltwiseMultMod((uint64_t*) out.vec, (uint64_t*) in_1_temp, (uint64_t*) in_2_temp, in_2_cast.size, in_2_cast.coef_modulus, 1); 
    for(int32_t i = 1; i < in_2_cast.array_size; ++i){
        in_1_temp = &in_1_cast.eval_long[i * in_1_cast.size];
        in_2_temp = &in_2_cast.eval_long[i * in_2_cast.size];    
        intel::hexl::EltwiseMultMod((uint64_t*) temp, (uint64_t*) in_1_temp, (uint64_t*) in_2_temp, in_2_cast.size, in_2_cast.coef_modulus, 1);
        intel::hexl::EltwiseAddMod((uint64_t*) out.vec, (uint64_t*) temp, (uint64_t*) out.vec, in_2_cast.size, in_2_cast.coef_modulus); 
    }
    ntt.ComputeInverse((uint64_t*) out.vec, (uint64_t*) out.vec, 1, 1);  
    delete[] temp; 
}


void IntelHexlNTTEngine::multisum(Polynomial &out_multisum, PolynomialArrayEvalForm &out_in_1_eval, const PolynomialArrayCoefForm &in_1, const PolynomialArrayEvalForm &in_2){   
    const PolynomialArrayEvalFormLong& in_2_cast = static_cast<const PolynomialArrayEvalFormLong&>(in_2);
    const PolynomialArrayEvalFormLong& out_in_1_eval_cast = static_cast<const PolynomialArrayEvalFormLong&>(out_in_1_eval);
    int64_t* in_1_temp = in_1.poly_array;
    int64_t* in_2_temp = in_2_cast.eval_long; 
    int64_t* temp = new long[in_2_cast.size];  
    int64_t* out_eval = out_in_1_eval_cast.eval_long; 
    ntt.ComputeForward((uint64_t*) out_eval, (uint64_t*) in_1_temp, 1, 1);  
    intel::hexl::EltwiseMultMod((uint64_t*) out_multisum.vec, (uint64_t*) out_eval, (uint64_t*) in_2_temp, in_2_cast.size, in_2_cast.coef_modulus, 1); 
    for(int32_t i = 1; i < in_2_cast.array_size; ++i){
        in_1_temp = &in_1.poly_array[i * in_1.degree];
        in_2_temp = &in_2_cast.eval_long[i * in_2_cast.size]; 
        out_eval = &out_in_1_eval_cast.eval_long[i * out_in_1_eval_cast.size]; 
        ntt.ComputeForward((uint64_t*) out_eval, (uint64_t*) in_1_temp, 1, 1);  
        intel::hexl::EltwiseMultMod((uint64_t*) temp, (uint64_t*) out_eval, (uint64_t*) in_2_temp, in_2_cast.size, in_2_cast.coef_modulus, 1);
        intel::hexl::EltwiseAddMod((uint64_t*) out_multisum.vec, (uint64_t*) temp, (uint64_t*) out_multisum.vec, in_2_cast.size, in_2_cast.coef_modulus);
    }
    ntt.ComputeInverse((uint64_t*) out_multisum.vec, (uint64_t*) out_multisum.vec, 1, 1);  
    delete[] temp; 
}
