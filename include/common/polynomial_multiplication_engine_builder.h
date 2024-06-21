#ifndef POLYNOMIAL_MULTIPLICATION_ENGINE_BUILDER_H
#define POLYNOMIAL_MULTIPLICATION_ENGINE_BUILDER_H
 

#include "polynomial.h"

namespace fhe_deck{
  

class PolynomialMultiplicationEngineBuilder{

    public:
    int64_t coef_modulus;
    int64_t degree;
    RingType ring;
    PolynomialArithmetic arithmetic;
    ModulusType mod_type;

    bool is_init = false;

    PolynomialMultiplicationEngineBuilder() = default;

    void set_coef_modulus(int64_t coef_modulus);

    void set_degree(int64_t degree);

    void set_ring_type(RingType ring);

    void set_polynomial_arithmetic(PolynomialArithmetic arithmetic);

    void set_modulus_type(ModulusType mod_type);

    std::shared_ptr<PolynomialMultiplicationEngine> build(); 
};


}
 
#endif