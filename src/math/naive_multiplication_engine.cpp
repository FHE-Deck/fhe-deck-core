#include "math/naive_multiplication_engine.h"
 
using namespace FHEDeck;

NaiveNegacyclicMultiplicationEngine::NaiveNegacyclicMultiplicationEngine(int32_t degree, int64_t coef_modulus){
    this->degree = degree;
    this->coef_modulus = coef_modulus;
    this->m_type = PolynomialArithmetic::naive;
}

std::shared_ptr<PolynomialEvalForm> NaiveNegacyclicMultiplicationEngine::init_polynomial_eval_form(){
    return std::make_shared<PolynomialEvalFormLongInteger>(new int64_t[degree], degree, coef_modulus);
} 

std::shared_ptr<PolynomialArrayEvalForm> NaiveNegacyclicMultiplicationEngine::init_polynomial_array_eval_form(int32_t array_size){
    return std::make_shared<PolynomialArrayEvalFormLong>(array_size, degree, coef_modulus); 
}

void NaiveNegacyclicMultiplicationEngine::to_eval(PolynomialEvalForm &out, const Polynomial &in){
        PolynomialEvalFormLongInteger& out_cast = static_cast<PolynomialEvalFormLongInteger&>(out);
        for(int32_t i = 0; i < degree; ++i){ 
            out_cast.eval_long[i] = in[i];
        }
}
    
void NaiveNegacyclicMultiplicationEngine::to_eval(PolynomialArrayEvalForm &out, const PolynomialArray &in){
    PolynomialArrayEvalFormLong& out_cast = static_cast<PolynomialArrayEvalFormLong&>(out);
    //int64_t* in_poly;
    //int64_t* out_poly; 
    for(int32_t i = 0; i < in.size(); ++i){
        //in_poly = &in.vec_array.get()[i * in.size];
        //out_poly = &out_cast.eval_long[i * out_cast.size];
        for(int32_t j = 0; j < degree; ++j){ 
            out_cast[i][j] = in[i][j];
        } 
    } 
}

void NaiveNegacyclicMultiplicationEngine::to_coef(Polynomial &out, const PolynomialEvalForm &in){
    const PolynomialEvalFormLongInteger& in_cast = static_cast<const PolynomialEvalFormLongInteger&>(in);
    for(int32_t i = 0; i < degree; ++i){ 
            out[i] = in_cast.eval_long[i];
    }
}
 
void NaiveNegacyclicMultiplicationEngine::to_coef(PolynomialArray &out, const PolynomialArrayEvalForm &in){
    const PolynomialArrayEvalFormLong& in_cast = static_cast<const PolynomialArrayEvalFormLong&>(in);
    //int64_t* in_poly;
    //int64_t* out_poly;
    for(int32_t i = 0; i < in.array_size; ++i){
        //in_poly = &in_cast.eval_long[i * in.size];
        //out_poly = &out.vec_array.get()[i * out.size];
        for(int32_t j = 0; j < degree; ++j){ 
            out[i][j] = in_cast[i][j];
    } 
    } 
}
  
void NaiveNegacyclicMultiplicationEngine::mul(PolynomialEvalForm &out, const PolynomialEvalForm &in_1, const PolynomialEvalForm &in_2){
    PolynomialEvalFormLongInteger& out_cast = static_cast<PolynomialEvalFormLongInteger&>(out);
    const PolynomialEvalFormLongInteger& in_1_cast = static_cast<const PolynomialEvalFormLongInteger&>(in_1);
    const PolynomialEvalFormLongInteger& in_2_cast = static_cast<const PolynomialEvalFormLongInteger&>(in_2); 
    mul(out_cast.eval_long, in_1_cast.eval_long, in_2_cast.eval_long); 
}

void NaiveNegacyclicMultiplicationEngine::multisum(Polynomial &out, const PolynomialArray &in_1, const PolynomialArrayEvalForm &in_2){
    const PolynomialArrayEvalFormLong& in_2_cast = static_cast<const PolynomialArrayEvalFormLong&>(in_2);    
    Polynomial mult(degree, coef_modulus);
    mul(out.get(), in_1[0].get(), in_2_cast[0].get());
    for(int32_t i = 1; i < in_2_cast.array_size; ++i){     
        mul(mult.get(), in_1[i].get(), in_2_cast[i].get());
        out.add(out, mult);
    } 
}

void NaiveNegacyclicMultiplicationEngine::multisum(Polynomial &out, const PolynomialArrayEvalForm &in_1, const PolynomialArrayEvalForm &in_2){
    const PolynomialArrayEvalFormLong& in_1_cast = static_cast<const PolynomialArrayEvalFormLong&>(in_1);
    const PolynomialArrayEvalFormLong& in_2_cast = static_cast<const PolynomialArrayEvalFormLong&>(in_2); 
    Polynomial mult(degree, coef_modulus);
    mul(out.get(), in_1_cast[0].get(), in_2_cast[0].get());
    for(int32_t i = 1; i < in_2_cast.array_size; ++i){      
        mul(mult.get(), in_1_cast[i].get(), in_2_cast[i].get());
        out.add(out, mult);
    } 
}
 
void NaiveNegacyclicMultiplicationEngine::multisum(Polynomial &out_multisum, PolynomialArrayEvalForm &out_in_1_eval, const PolynomialArray &in_1, const PolynomialArrayEvalForm &in_2){
    /// NOTE: This is the NaiveNegacyclicMultiplicationEngine, there is actually no eval form here. 
    /// But, some procedures use the eval form, for efficiency, so the decision made, was to just copy the input polynomial. 
    PolynomialArrayEvalFormLong& out_in_1_eval_cast = static_cast<PolynomialArrayEvalFormLong&>(out_in_1_eval);
    for(int32_t i = 0; i < out_in_1_eval.full_size; ++i){
        out_in_1_eval_cast.eval_long[i] = in_1[0].get()[i];
    }
    const PolynomialArrayEvalFormLong& in_2_cast = static_cast<const PolynomialArrayEvalFormLong&>(in_2);    
    Polynomial mult(degree, coef_modulus);
    mul(out_multisum.get(), in_1[0].get(), in_2_cast[0].get());
    for(int32_t i = 1; i < in_2_cast.array_size; ++i){     
        mul(mult.get(), in_1[i].get(), in_2_cast[i].get());
        out_multisum.add(out_multisum, mult);
    } 
}

void NaiveNegacyclicMultiplicationEngine::mul(int64_t* out, int64_t* in_1, int64_t* in_2){ 
    for (int i = 0; i < degree; ++i) { 
        out[i] = 0;
        for (int32_t j = 0; j <= i; ++j) {
            __int128 temp = (__int128)in_1[j] * (__int128)in_2[(degree - j + i) % degree];
            out[i] = (out[i] + temp) % coef_modulus;
        }
        for (int32_t j = i+1; j < degree; ++j) {
            //out[i] -= in_1[j] * in_2[(degree - j + i) % degree];
            __int128 temp = (in_1[j] * in_2[(degree - j + i) % degree]) % coef_modulus;
            out[i] = Utils::integer_mod_form(out[i] - temp, coef_modulus);
        }
    } 
}