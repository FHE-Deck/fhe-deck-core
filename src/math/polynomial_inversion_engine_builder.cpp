#include "math/polynomial_inversion_engine_builder.h"
 
#include "math/ntl_inversion_engine.h" 
#include "math/euclidean_inversion_engine.h"

using namespace fhe_deck; 
 
PolynomialInversionEngineBuilder::PolynomialInversionEngineBuilder(int32_t degree, int64_t coef_modulus){
    this->degree = degree;
    this->coef_modulus = coef_modulus;
}

std::shared_ptr<PolynomialInversionEngine> PolynomialInversionEngineBuilder::build(){
 
#if defined(USE_NTL)
    std::cout << "Using the NTL Inversion Engine" << std::endl;
    return std::make_shared<NTLInversionEngine>(degree, coef_modulus);
#else
    std::cout << "Using the Euclidean (Default) Inversion Engine" << std::endl;
    return std::make_shared<EuclideanInversionEngine>(degree, coef_modulus);
#endif 
 

}
