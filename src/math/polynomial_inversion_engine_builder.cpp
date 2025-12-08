#include "math/polynomial_inversion_engine_builder.h"
 
#include "math/ntl_inversion_engine.h" 
#include "math/euclidean_inversion_engine.h"

using namespace FHEDeck; 
 
PolynomialInversionEngineBuilder::PolynomialInversionEngineBuilder(int32_t degree, int64_t coef_modulus){
    m_degree = degree;
    m_coef_modulus = coef_modulus;
}

std::shared_ptr<PolynomialInversionEngine> PolynomialInversionEngineBuilder::build(){
 
#if defined(USE_NTL) 
    return std::make_shared<NTLInversionEngine>(m_degree, m_coef_modulus);
#else 
    return std::make_shared<EuclideanInversionEngine>(degree, coef_modulus);
#endif 
  
}
