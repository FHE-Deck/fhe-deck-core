#ifndef NTL_INVERSION_ENGINES_H
#define NTL_INVERSION_ENGINES_H

#include "math/polynomial.h"

#include <vector>

#include <NTL/ZZX.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_p.h> 

namespace fhe_deck{
     
   
class NTLInversionEngine : public PolynomialInversionEngine{

    public: 
    
    std::vector<int64_t> poly_mod;
    int32_t degree;
    int64_t coef_modulus;

    NTL::ZZ_pX ring_poly;

    NTLInversionEngine(const int32_t degree, const int64_t coef_modulus);
  
    /// @brief Computes the multiplivative inverse of the given polynomial, if such inverse exists. 
    /// @param out The output polynomial
    /// @param in The input polynomial
    bool inv(Polynomial &out, const Polynomial &in)const;

    private:

    void set_polynomial_from_array(NTL::ZZ_pX &poly, int64_t *f, int32_t sizeof_f, int64_t Q)const;

    void set_array_from_polynomial(int64_t *f, int32_t sizeof_array, NTL::ZZ_pX poly)const;

    NTL::ZZ_pX get_ring_poly(RingType ring, int64_t N, int64_t modulus)const;
};
  
}

#endif 