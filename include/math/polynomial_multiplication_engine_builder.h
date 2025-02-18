#ifndef POLYNOMIAL_MULTIPLICATION_ENGINE_BUILDER_H
#define POLYNOMIAL_MULTIPLICATION_ENGINE_BUILDER_H
 
/**
 * @file polynomial_multiplication_engine_builder.h
 */

#include "global_headers.h"

#include "math/polynomial.h"


namespace FHEDeck{
   
/**
 * @brief This class is used to build a PolynomialMultiplicationEngine object.  
 */
class PolynomialMultiplicationEngineBuilder{

    public:
    int64_t coef_modulus;
    int64_t degree;
    RingType ring;
    PolynomialArithmetic arithmetic;
    ModulusType mod_type;

    bool is_init = false;

    PolynomialMultiplicationEngineBuilder() = default;

    void set_coef_modulus(const int64_t coef_modulus);

    void set_degree(const int64_t degree);

    void set_ring_type(const RingType ring);

    void set_polynomial_arithmetic(const PolynomialArithmetic arithmetic);

    void set_modulus_type(const ModulusType mod_type);

    std::shared_ptr<PolynomialMultiplicationEngine> build(); 
};


} /// End of namespace FHEDeck
 
#endif