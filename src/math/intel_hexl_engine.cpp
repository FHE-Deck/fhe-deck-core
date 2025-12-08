#include "math/intel_hexl_engine.h"

using namespace FHEDeck;
   
IntelHexlNTTEngine::IntelHexlNTTEngine(int32_t degree, int64_t coef_modulus){ 
    m_degree = degree;
    m_coef_modulus = coef_modulus;
    m_ntt = intel::hexl::NTT(degree, coef_modulus);
    m_type = PolynomialArithmetic::ntt64;
}
  
void IntelHexlNTTEngine::to_coef(Polynomial &out, const PolynomialEvalForm &in){ 
    const PolynomialEvalFormLongInteger& in_cast = static_cast<const PolynomialEvalFormLongInteger&>(in);
    m_ntt.ComputeInverse((uint64_t*) out.get(), (uint64_t*)  in_cast.get(), 1, 1);   
}
  
void IntelHexlNTTEngine::to_coef(PolynomialArray &out, const PolynomialArrayEvalForm &in){ 
    const PolynomialArrayEvalFormLong& in_cast = static_cast<const PolynomialArrayEvalFormLong&>(in); 
    for(int32_t i = 0; i < in.size(); ++i){ 
        m_ntt.ComputeInverse((uint64_t*) out[i].get(), (uint64_t*) in_cast[i].data(), 1, 1);  
    } 
}

std::shared_ptr<PolynomialEvalForm> IntelHexlNTTEngine::init_polynomial_eval_form(){ 
    return std::make_shared<PolynomialEvalFormLongInteger>(m_degree, m_coef_modulus);
}

std::shared_ptr<PolynomialArrayEvalForm> IntelHexlNTTEngine::init_polynomial_array_eval_form(int32_t array_size){ 
    return std::make_shared<PolynomialArrayEvalFormLong>(array_size, m_degree, m_coef_modulus); 
}
 
void IntelHexlNTTEngine::to_eval(PolynomialEvalForm &out, const Polynomial &in){  
    const PolynomialEvalFormLongInteger& out_cast = static_cast<const PolynomialEvalFormLongInteger&>(out); 
    m_ntt.ComputeForward((uint64_t*) out_cast.get(), (uint64_t*) in.get(), 1, 1);   
}
 
void IntelHexlNTTEngine::to_eval(PolynomialArrayEvalForm &out, const PolynomialArray &in){  
    const PolynomialArrayEvalFormLong& out_cast = static_cast<const PolynomialArrayEvalFormLong&>(out);  
    for(int32_t i = 0; i < in.size(); ++i){ 
        VectorView in_poly = in[i]; 
        m_ntt.ComputeForward((uint64_t*) out_cast[i].data(), (uint64_t*) in_poly.get(), 1, 1);   
    } 
}

void IntelHexlNTTEngine::mul(PolynomialEvalForm &out, const PolynomialEvalForm &in_1, const PolynomialEvalForm &in_2){  
    PolynomialEvalFormLongInteger& out_cast = static_cast<PolynomialEvalFormLongInteger&>(out);
    const PolynomialEvalFormLongInteger& in_1_cast = static_cast<const PolynomialEvalFormLongInteger&>(in_1);
    const PolynomialEvalFormLongInteger& in_2_cast = static_cast<const PolynomialEvalFormLongInteger&>(in_2); 
    intel::hexl::EltwiseMultMod((uint64_t*) out_cast.get(), 
                (uint64_t*) in_1_cast.get(), 
                (uint64_t*) in_2_cast.get(), 
                out_cast.size(), out_cast.modulus(), 1); 
}
 
void IntelHexlNTTEngine::multisum(Polynomial &out, const PolynomialArray &in_1, const PolynomialArrayEvalForm &in_2){    
    const PolynomialArrayEvalFormLong& in_2_cast = static_cast<const PolynomialArrayEvalFormLong&>(in_2);  
    std::unique_ptr<uint64_t[]> temp = std::make_unique<uint64_t[]>(in_2_cast.eval_form_size());
    m_ntt.ComputeForward((uint64_t*) temp.get(), (uint64_t*) in_1[0].get(), 1, 1);  
    intel::hexl::EltwiseMultMod((uint64_t*) out.get(), (uint64_t*) temp.get(), (uint64_t*) in_2_cast[0].data(), in_2_cast.eval_form_size(), in_2_cast.modulus(), 1); 
    for(int32_t i = 1; i < in_2_cast.size(); ++i){  
        m_ntt.ComputeForward((uint64_t*) temp.get(), (uint64_t*) in_1[i].get(), 1, 1);  
        intel::hexl::EltwiseMultMod((uint64_t*) temp.get(), (uint64_t*) temp.get(), (uint64_t*) in_2_cast[i].data(), in_2_cast.eval_form_size(), in_2_cast.modulus(), 1);
        intel::hexl::EltwiseAddMod((uint64_t*) out.get(), (uint64_t*) temp.get(), (uint64_t*) out.get(), in_2_cast.eval_form_size(), in_2_cast.modulus());
    }
    m_ntt.ComputeInverse((uint64_t*) out.get(), (uint64_t*) out.get(), 1, 1);   
}

void IntelHexlNTTEngine::multisum(Polynomial &out, const PolynomialArrayEvalForm &in_1, const PolynomialArrayEvalForm &in_2){    
    const PolynomialArrayEvalFormLong& in_1_cast = static_cast<const PolynomialArrayEvalFormLong&>(in_1);
    const PolynomialArrayEvalFormLong& in_2_cast = static_cast<const PolynomialArrayEvalFormLong&>(in_2); 
    std::unique_ptr<uint64_t[]> temp = std::make_unique<uint64_t[]>(in_2_cast.eval_form_size());
    intel::hexl::EltwiseMultMod((uint64_t*) out.get(), (uint64_t*) in_1_cast[0].data(), (uint64_t*) in_2_cast[0].data(), in_2_cast.eval_form_size(), in_2_cast.modulus(), 1); 
    for(int32_t i = 1; i < in_2_cast.size(); ++i){   
        intel::hexl::EltwiseMultMod(temp.get(), (uint64_t*) in_1_cast[i].data(), (uint64_t*) in_2_cast[i].data(), in_2_cast.eval_form_size(), in_2_cast.modulus(), 1);
        intel::hexl::EltwiseAddMod((uint64_t*) out.get(), temp.get(), (uint64_t*) out.get(), in_2_cast.eval_form_size(), in_2_cast.modulus()); 
    }
    m_ntt.ComputeInverse((uint64_t*) out.get(), (uint64_t*) out.get(), 1, 1);   
}


void IntelHexlNTTEngine::multisum(Polynomial &out_multisum, PolynomialArrayEvalForm &out_in_1_eval, const PolynomialArray &in_1, const PolynomialArrayEvalForm &in_2){   
    const PolynomialArrayEvalFormLong& in_2_cast = static_cast<const PolynomialArrayEvalFormLong&>(in_2);
    const PolynomialArrayEvalFormLong& out_in_1_eval_cast = static_cast<const PolynomialArrayEvalFormLong&>(out_in_1_eval);  
    std::unique_ptr<uint64_t[]> temp = std::make_unique<uint64_t[]>(in_2_cast.eval_form_size()); 
    m_ntt.ComputeForward((uint64_t*) out_in_1_eval_cast[0].data(), (uint64_t*) in_1[0].get(), 1, 1);  
    intel::hexl::EltwiseMultMod((uint64_t*) out_multisum.get(), (uint64_t*) out_in_1_eval_cast[0].data(), (uint64_t*) in_2_cast[0].data(), in_2_cast.eval_form_size(), in_2_cast.modulus(), 1); 
    for(int32_t i = 1; i < in_2_cast.size(); ++i){  
        m_ntt.ComputeForward((uint64_t*) out_in_1_eval_cast[i].data(), (uint64_t*) in_1[i].get(), 1, 1);  
        intel::hexl::EltwiseMultMod(temp.get(), (uint64_t*) out_in_1_eval_cast[i].data(), (uint64_t*) in_2_cast[i].data(), in_2_cast.eval_form_size(), in_2_cast.modulus(), 1);
        intel::hexl::EltwiseAddMod((uint64_t*) out_multisum.get(), temp.get(), (uint64_t*) out_multisum.get(), in_2_cast.eval_form_size(), in_2_cast.modulus());
    }
    m_ntt.ComputeInverse((uint64_t*) out_multisum.get(), (uint64_t*) out_multisum.get(), 1, 1);   
}
