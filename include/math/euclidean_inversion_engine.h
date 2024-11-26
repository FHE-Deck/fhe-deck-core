#ifndef EUCLIDEAN_INVERSION_ENGINES_H
#define EUCLIDEAN_INVERSION_ENGINES_H


#include "math/polynomial.h"


namespace fhe_deck{
    
class EuclideanInversionEngine : public PolynomialInversionEngine{

    public: 
    
    std::vector<int64_t> poly_mod;
    int32_t degree;
    int64_t coef_modulus;

    EuclideanInversionEngine(const int32_t degree, const int64_t coef_modulus);
  
    /// @brief Computes the multiplivative inverse of the given polynomial, if such inverse exists. 
    /// @param out The output polynomial
    /// @param in The input polynomial
    bool inv(Polynomial &out, const Polynomial &in)const;
     
    std::tuple<std::vector<int64_t>, std::vector<int64_t>, std::vector<int64_t>> xgcd(const std::vector<int64_t>& a, const std::vector<int64_t>& b, uint64_t p)const;

    std::pair<std::vector<int64_t>, std::vector<int64_t>> polynomial_division(const std::vector<int64_t>& a, const std::vector<int64_t>& b, uint64_t p)const;

    std::vector<int64_t> polynomial_multiplication(const std::vector<int64_t>& a, const std::vector<int64_t>& b, uint64_t p)const;

    std::vector<int64_t> polynomial_subtraction(const std::vector<int64_t>& a, const std::vector<int64_t>& b, uint64_t p)const;

    std::pair<int64_t, std::pair<int64_t, int64_t>> extended_euclidean_algorithm(int64_t a, int64_t b)const;

    int64_t modular_inverse(int64_t a, int64_t m) const;
};

}

#endif