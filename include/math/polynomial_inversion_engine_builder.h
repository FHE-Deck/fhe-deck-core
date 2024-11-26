#ifndef POLYNOMIAL_INVERSION_ENGINE_BUILDER_H
#define POLYNOMIAL_INVERSION_ENGINE_BUILDER_H

 
/**
 * @file polynomial_inversion_engine_builder.h
 */

#include "math/polynomial.h"

namespace fhe_deck{

    
/**
 * @brief This class is used to build a PolynomialInversionEngine object.  
 */
class PolynomialInversionEngineBuilder{

    public:
    int64_t coef_modulus;
    int32_t degree;
    RingType ring;
    PolynomialArithmetic arithmetic;
    ModulusType mod_type;

    bool is_init = false;

    PolynomialInversionEngineBuilder(int32_t degree, int64_t coef_modulus);
 
    std::shared_ptr<PolynomialInversionEngine> build(); 
};

}

#endif