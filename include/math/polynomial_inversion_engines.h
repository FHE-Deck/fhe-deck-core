#ifndef POLYNOMIAL_INVERSION_ENGINES_H
#define POLYNOMIAL_INVERSION_ENGINES_H

#include "polynomial.h"

namespace fhe_deck{
    
class EuclideanInversionEngine : PolynomialInversionEngine{

    public: 
    
    Polynomial poly_mod;

    EuclideanInversionEngine(const Polynomial& poly_mod);

    /// @brief Computes the multiplivative inverse of the given polynomial, if such inverse exists. 
    /// @param out The output polynomial
    /// @param in The input polynomial
    void inv(Polynomial &out, const Polynomial &in);

    private:

    // Given polynomials a, b returns u, v s.t. au + bv = g, where g is the gcd of polynomials,
    void euclid_alg(Polynomial& g, Polynomial& u, Polynomial& v, const Polynomial &a, const Polynomial &b);
 
    void poly_division(Polynomial& quotient, Polynomial& reminder, const Polynomial& divided, const Polynomial& divisor);

    void trivial_poly_mul(Polynomial& out, Polynomial& in_1, Polynomial& in_2);

    std::pair<int, std::pair<int, int>> extended_euclidean_algorithm(int a, int b);

};


  
}

#endif 