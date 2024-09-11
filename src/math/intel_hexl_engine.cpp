#include "intel_hexl_engine.h"

using namespace fhe_deck;
 


IntelHexlNTTEngine::IntelHexlNTTEngine(int32_t degree, int64_t coef_modulus){ 
    this->degree = degree;
    this->coef_modulus = coef_modulus;
    this->ntt = intel::hexl::NTT(degree, coef_modulus);
    this->type = ntt64;
}
  
void IntelHexlNTTEngine::to_coef(Polynomial &out, PolynomialEvalForm &in){
    //PolynomialEvalFormLongInteger* in_cast = static_cast<PolynomialEvalFormLongInteger*>(in);
    PolynomialEvalFormLongInteger& in_cast = static_cast<PolynomialEvalFormLongInteger&>(in);
    ntt.ComputeInverse((uint64_t*) out.coefs, (uint64_t*)  in_cast.eval_long, 1, 1);   
}
  
void IntelHexlNTTEngine::to_coef(PolynomialArrayCoefForm &out, PolynomialArrayEvalForm &in){
    //PolynomialArrayEvalFormLong* in_cast = static_cast<PolynomialArrayEvalFormLong*>(in);
    PolynomialArrayEvalFormLong& in_cast = static_cast<PolynomialArrayEvalFormLong&>(in);
    int64_t* in_poly;
    int64_t* out_poly;
    for(int32_t i = 0; i < in.array_size; ++i){
        in_poly = &in_cast.eval_long[i * in.size];
        out_poly = &out.poly_array[i * out.degree];
        ntt.ComputeInverse((uint64_t*) out_poly, (uint64_t*) in_poly, 1, 1);  
    } 
}

PolynomialEvalForm* IntelHexlNTTEngine::init_polynomial_eval_form(){ 
    return new PolynomialEvalFormLongInteger(new int64_t[degree], degree, coef_modulus);
}

PolynomialArrayEvalForm* IntelHexlNTTEngine::init_polynomial_array_eval_form(int32_t array_size){ 
    return new PolynomialArrayEvalFormLong(array_size, degree, coef_modulus); 
}
 
void IntelHexlNTTEngine::to_eval(PolynomialEvalForm &out, Polynomial &in){ 
    //PolynomialEvalFormLongInteger* out_cast = static_cast<PolynomialEvalFormLongInteger*>(out);
    PolynomialEvalFormLongInteger& out_cast = static_cast<PolynomialEvalFormLongInteger&>(out);
    // Here we make sure that the coefficients are in propper form.
    int64_t* coefs_mod_form = new int64_t[in.degree];
    Utils::array_mod_form(coefs_mod_form, in.coefs, in.degree, in.coef_modulus); 
    ntt.ComputeForward((uint64_t*) out_cast.eval_long, (uint64_t*) coefs_mod_form, 1, 1);  
    delete[] coefs_mod_form;
}
 
void IntelHexlNTTEngine::to_eval(PolynomialArrayEvalForm &out, PolynomialArrayCoefForm &in){ 
    //PolynomialArrayEvalFormLong* out_cast = static_cast<PolynomialArrayEvalFormLong*>(out);
    PolynomialArrayEvalFormLong& out_cast = static_cast<PolynomialArrayEvalFormLong&>(out);
    int64_t* in_poly;
    int64_t* out_poly; 
    for(int32_t i = 0; i < in.array_size; ++i){
        in_poly = &in.poly_array[i * in.degree];
        out_poly = &out_cast.eval_long[i * out_cast.size];
        ntt.ComputeForward((uint64_t*) out_poly, (uint64_t*) in_poly, 1, 1);   
    } 
}

void IntelHexlNTTEngine::mul(PolynomialEvalForm &out, PolynomialEvalForm &in_1, PolynomialEvalForm &in_2){ 
    //PolynomialEvalFormLongInteger* out_cast = static_cast<PolynomialEvalFormLongInteger*>(out);
    //PolynomialEvalFormLongInteger* in_1_cast = static_cast<PolynomialEvalFormLongInteger*>(in_1);
    //PolynomialEvalFormLongInteger* in_2_cast = static_cast<PolynomialEvalFormLongInteger*>(in_2); 
    PolynomialEvalFormLongInteger& out_cast = static_cast<PolynomialEvalFormLongInteger&>(out);
    PolynomialEvalFormLongInteger& in_1_cast = static_cast<PolynomialEvalFormLongInteger&>(in_1);
    PolynomialEvalFormLongInteger& in_2_cast = static_cast<PolynomialEvalFormLongInteger&>(in_2); 
    intel::hexl::EltwiseMultMod((uint64_t*) out_cast.eval_long, 
                (uint64_t*) in_1_cast.eval_long, 
                (uint64_t*) in_2_cast.eval_long, 
                out_cast.size, out_cast.coef_modulus, 1); 
}
 
void IntelHexlNTTEngine::multisum(Polynomial &out, PolynomialArrayCoefForm &in_1, PolynomialArrayEvalForm &in_2){   
    //PolynomialArrayEvalFormLong* in_2_cast = static_cast<PolynomialArrayEvalFormLong*>(in_2);
    PolynomialArrayEvalFormLong& in_2_cast = static_cast<PolynomialArrayEvalFormLong&>(in_2);
    int64_t* in_1_temp = in_1.poly_array;
    int64_t* in_2_temp = in_2_cast.eval_long; 
    int64_t* temp = new int64_t[in_2_cast.size];   
    ntt.ComputeForward((uint64_t*) temp, (uint64_t*) in_1_temp, 1, 1);  
    intel::hexl::EltwiseMultMod((uint64_t*) out.coefs, (uint64_t*) temp, (uint64_t*) in_2_temp, in_2_cast.size, in_2_cast.coef_modulus, 1); 
    for(int32_t i = 1; i < in_2_cast.array_size; ++i){
        in_1_temp = &in_1.poly_array[i * in_1.degree];
        in_2_temp = &in_2_cast.eval_long[i * in_2_cast.size];  
        ntt.ComputeForward((uint64_t*) temp, (uint64_t*) in_1_temp, 1, 1);  
        intel::hexl::EltwiseMultMod((uint64_t*) temp, (uint64_t*) temp, (uint64_t*) in_2_temp, in_2_cast.size, in_2_cast.coef_modulus, 1);
        intel::hexl::EltwiseAddMod((uint64_t*) out.coefs, (uint64_t*) temp, (uint64_t*) out.coefs, in_2_cast.size, in_2_cast.coef_modulus);
    }
    ntt.ComputeInverse((uint64_t*) out.coefs, (uint64_t*) out.coefs, 1, 1);  
    delete[] temp; 
}

void IntelHexlNTTEngine::multisum(Polynomial &out, PolynomialArrayEvalForm &in_1, PolynomialArrayEvalForm &in_2){   
    //PolynomialArrayEvalFormLong* in_1_cast = static_cast<PolynomialArrayEvalFormLong*>(in_1);
    //PolynomialArrayEvalFormLong* in_2_cast = static_cast<PolynomialArrayEvalFormLong*>(in_2);
    PolynomialArrayEvalFormLong& in_1_cast = static_cast<PolynomialArrayEvalFormLong&>(in_1);
    PolynomialArrayEvalFormLong& in_2_cast = static_cast<PolynomialArrayEvalFormLong&>(in_2);
    int64_t* in_1_temp = in_1_cast.eval_long;
    int64_t* in_2_temp = in_2_cast.eval_long; 
    int64_t* temp = new int64_t[in_2_cast.size];   
    intel::hexl::EltwiseMultMod((uint64_t*) out.coefs, (uint64_t*) in_1_temp, (uint64_t*) in_2_temp, in_2_cast.size, in_2_cast.coef_modulus, 1); 
    for(int32_t i = 1; i < in_2_cast.array_size; ++i){
        in_1_temp = &in_1_cast.eval_long[i * in_1_cast.size];
        in_2_temp = &in_2_cast.eval_long[i * in_2_cast.size];    
        intel::hexl::EltwiseMultMod((uint64_t*) temp, (uint64_t*) in_1_temp, (uint64_t*) in_2_temp, in_2_cast.size, in_2_cast.coef_modulus, 1);
        intel::hexl::EltwiseAddMod((uint64_t*) out.coefs, (uint64_t*) temp, (uint64_t*) out.coefs, in_2_cast.size, in_2_cast.coef_modulus); 
    }
    ntt.ComputeInverse((uint64_t*) out.coefs, (uint64_t*) out.coefs, 1, 1);  
    delete[] temp; 
}


void IntelHexlNTTEngine::multisum(Polynomial &out_multisum, PolynomialArrayEvalForm &out_in_1_eval, PolynomialArrayCoefForm &in_1, PolynomialArrayEvalForm &in_2){   
    //PolynomialArrayEvalFormLong* in_2_cast = static_cast<PolynomialArrayEvalFormLong*>(in_2);
    //PolynomialArrayEvalFormLong* out_in_1_eval_cast = static_cast<PolynomialArrayEvalFormLong*>(out_in_1_eval);
    PolynomialArrayEvalFormLong& in_2_cast = static_cast<PolynomialArrayEvalFormLong&>(in_2);
    PolynomialArrayEvalFormLong& out_in_1_eval_cast = static_cast<PolynomialArrayEvalFormLong&>(out_in_1_eval);
    int64_t* in_1_temp = in_1.poly_array;
    int64_t* in_2_temp = in_2_cast.eval_long; 
    int64_t* temp = new long[in_2_cast.size];  
    int64_t* out_eval = out_in_1_eval_cast.eval_long; 
    ntt.ComputeForward((uint64_t*) out_eval, (uint64_t*) in_1_temp, 1, 1);  
    intel::hexl::EltwiseMultMod((uint64_t*) out_multisum.coefs, (uint64_t*) out_eval, (uint64_t*) in_2_temp, in_2_cast.size, in_2_cast.coef_modulus, 1); 
    for(int32_t i = 1; i < in_2_cast.array_size; ++i){
        in_1_temp = &in_1.poly_array[i * in_1.degree];
        in_2_temp = &in_2_cast.eval_long[i * in_2_cast.size]; 
        out_eval = &out_in_1_eval_cast.eval_long[i * out_in_1_eval_cast.size]; 
        ntt.ComputeForward((uint64_t*) out_eval, (uint64_t*) in_1_temp, 1, 1);  
        intel::hexl::EltwiseMultMod((uint64_t*) temp, (uint64_t*) out_eval, (uint64_t*) in_2_temp, in_2_cast.size, in_2_cast.coef_modulus, 1);
        intel::hexl::EltwiseAddMod((uint64_t*) out_multisum.coefs, (uint64_t*) temp, (uint64_t*) out_multisum.coefs, in_2_cast.size, in_2_cast.coef_modulus);
    }
    ntt.ComputeInverse((uint64_t*) out_multisum.coefs, (uint64_t*) out_multisum.coefs, 1, 1);  
    delete[] temp; 
}
