#ifndef POLYNOMIAL_INVERSION_ENGINE_BUILDER_H
#define POLYNOMIAL_INVERSION_ENGINE_BUILDER_H

 
/**
 * @file polynomial_inversion_engine_builder.h
 */

#include "global_headers.h"

#include "math/polynomial.h"

namespace FHEDeck{
    
/**
 * @brief This class is used to build a PolynomialInversionEngine object.  
 */
class PolynomialInversionEngineBuilder{

    protected:

    int64_t m_coef_modulus;
    int32_t m_degree; 

    public:

    PolynomialInversionEngineBuilder(int32_t degree, int64_t coef_modulus);
 
    std::shared_ptr<PolynomialInversionEngine> build(); 
};

} /// End of namespace FHEDeck

#endif