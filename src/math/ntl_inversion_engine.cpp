#include "math/ntl_inversion_engine.h" 

using namespace FHEDeck;
   
NTLInversionEngine::NTLInversionEngine(const int degree, const int64_t coef_modulus){
    m_degree = degree;
    m_coef_modulus = coef_modulus;
    m_poly_mod = std::vector<int64_t>(degree+1, 0);
    m_poly_mod[0] = 1;
    m_poly_mod[degree] = 1;
    m_ring_poly = get_ring_poly(RingType::negacyclic, degree, coef_modulus);
}


bool NTLInversionEngine::inv(Polynomial &out, const Polynomial &in)const{ 
    NTL::ZZ_pX temp_f; 
    set_polynomial_from_array(temp_f, in.get(), in.size(), m_coef_modulus);
    NTL::ZZ_pX temp_inv_f;  
    int64_t status = NTL::InvModStatus(temp_inv_f, temp_f, m_ring_poly);   
    set_array_from_polynomial(out.get(), out.size(), temp_inv_f);    
    return (status == 0); 
}

void NTLInversionEngine::set_polynomial_from_array(NTL::ZZ_pX &poly, int64_t *f, int32_t sizeof_f, int64_t Q)const{
    NTL::ZZ_p coef;
    coef.init(NTL::ZZ(Q));
    for(int32_t i = 0; i < sizeof_f; ++i){
        coef = f[i];
        NTL::SetCoeff(poly, i, coef);
    } 
}


void NTLInversionEngine::set_array_from_polynomial(int64_t *f, int32_t sizeof_array, NTL::ZZ_pX poly)const{ 
    for(int32_t i = 0; i < sizeof_array; ++i){
        f[i] = 0;
    }
    int64_t deg = NTL::deg(poly);
    for(int32_t i = 0; i <= deg; ++i){
         f[i] = NTL::conv<long>(poly[i]);
    } 
}


NTL::ZZ_pX NTLInversionEngine::get_ring_poly(RingType ring, int64_t N, int64_t modulus)const{
    NTL::ZZ_pX out;
    int64_t *psi_arr = new long[N+1]; 
    psi_arr[N] = 1;
    for(int32_t i=1; i < N; ++i){
            psi_arr[i] = 0;
    } 
    if(ring==RingType::cyclic){
        psi_arr[0] = modulus-1;
    }else{
        psi_arr[0] = 1;
    }
    set_polynomial_from_array(out, psi_arr, N+1, modulus); 
    delete[] psi_arr;
    return out;
}
 