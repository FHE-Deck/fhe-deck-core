 
#ifndef UTILS_H
#define UTILS_H

// TODO: NTL is only needed for testing. Multiplication engine is handled in polynomial.h, so Need to get rid of it here. 
#include <NTL/ZZX.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_p.h>

#include <string>
#include <memory>
#include "sample.h"
#include "enums.h" 

#include <fftw3.h>
 

namespace fhe_deck{

class Utils{

    public:
  
        static void set_polynomial_from_array(NTL::ZZ_pX &poly, int64_t *f, int32_t sizeof_f, int64_t Q);

        static void set_array_from_polynomial(int64_t *array, int32_t sizeof_array, NTL::ZZ_pX poly);

        static void add_polynomials(int64_t *out, int64_t *in_1, int64_t *in_2, int32_t sizeof_in_1, int32_t sizeof_in_2);

        static void mod_polynomial(int64_t *out, int64_t *in, int32_t sizeof_in, int64_t modulus);

        static void mul_scalar(int64_t *out, int64_t *in, int32_t sizeof_in, int64_t scalar);
  
        static void mul_mod(int64_t *out, int64_t *in_1, int32_t sizeof_in_1, int64_t *in_2, int32_t sizeof_in_2, int64_t N, int64_t modulus, RingType ring);
  
        static void add_mod(int64_t *out, int64_t *in_1, int32_t sizeof_in_1, int64_t *in_2, int32_t sizeof_in_2, int64_t N, int64_t modulus);

        static void sub_mod(int64_t *out, int64_t *in_1, int32_t sizeof_in_1, int64_t *in_2, int32_t sizeof_in_2, int64_t N, int64_t modulus);

        static void neg_mod(int64_t *out, int64_t *in_1, int32_t size, int64_t modulus);

        static int64_t mod_inv(int64_t in, int64_t modulus);

        static NTL::ZZ_pX get_ring_poly(RingType ring, int64_t N, int64_t modulus);
 
        static void cp(int64_t *out, int64_t *in, int32_t size);

        // Returns the smallest k, s.t. base**k >= x
        static int32_t power_times(int64_t x, int64_t base);

        static bool is_power_of(int64_t x, int64_t base);

        static int64_t pow(int64_t x, int64_t base);

        static int64_t abs(int64_t x);

        // Returns the smallest m s.t. 2**m < x. I cannot rely on the log function from the math library due to precision
        static int32_t number_of_bits(int64_t x);

        // Computes (z**2)/4 mod modulus
        // Its usefull from computing x * y = (x+y)**2/4 - (x-y)**2/4 mod modulus
        // TODO Should be in a class for building rotation polynomials
        static int64_t square_and_div_by_4(int64_t in, int64_t modulus);

        static int64_t eval_poly_mod(int64_t in, int* poly, int32_t poly_size, int64_t modulus);

        static bool is_eq_poly(int64_t *in_1, int64_t *in_2, int32_t sizeof_in);
 
        static void rotate_poly(int64_t *out_poly, int64_t *in_poly, int32_t poly_size, int32_t rot);

        static void negacyclic_rotate_poly(int64_t *out_poly, int64_t *in_poly, int32_t poly_size, int32_t rot);

        static int64_t integer_signed_form(int64_t in, int64_t Q);
 
        static void array_signed_form(int64_t *out, int64_t *in, int32_t sizeof_in, int64_t Q);

        static int64_t integer_mod_form(int64_t in, int64_t Q);

        static void array_mod_form(int64_t *out, int64_t *in, int32_t sizeof_in, int64_t Q);
 
 
        // Below we have functions for rounding and modulus reducing polynomials 
        static void round_and_mod_reduce(int64_t *out_poly, double *in_poly, int64_t modulus, int32_t sizeof_in_poly);

        static void round_and_mod_reduce(int64_t *out_poly, long double *in_poly, int64_t modulus, int32_t sizeof_in_poly);

        static void round_and_mod_reduce_power_of_two(int64_t *out_poly, double *in_poly, int64_t mask, int32_t sizeof_in_poly);

        static void round_and_mod_reduce_power_of_two(int64_t *out_poly, long double *in_poly, int64_t mask, int32_t sizeof_in_poly);  

        static void mod_reduce_power_of_two(int64_t *out_poly, int64_t *in_poly, int64_t modulus, int32_t sizeof_in_poly);

        static void mod_reduce(int64_t *out_poly, int64_t *in_poly, int64_t modulus, int32_t sizeof_in_poly); 

        static void mod_reduce(int64_t *out_poly, long double *in_poly_l, int64_t modulus, int32_t sizeof_in_poly); 

        static int64_t integer_rounding(int64_t in, int64_t Q, int64_t t);

        static void array_rounding(int64_t *out, int64_t *in, int32_t sizeof_in, int64_t Q, int64_t t); 

        static std::string to_string(int64_t *poly, int32_t sizeof_poly);

        static std::string to_string(double *poly, int32_t sizeof_poly);

        static std::string to_string(int32_t *poly, int32_t sizeof_poly);

        static std::string complex_to_string(fftw_complex* in, int32_t from, int32_t size);

        static void set(long* out, long* in, int32_t sizeof_in);

        static int64_t integer_compose(int64_t *dec_in, int32_t basis, int32_t ell);

        static void integer_decomp(int64_t *dec_out, int64_t in , int32_t basis, int32_t k, int32_t ell);

        // Below are the gadget (should be perhaps in a separate class?)
        // TODO: All those are in the gadget class - delete from here after testing 
        static void decomp(int64_t **d_ct, long* poly, int32_t sizeof_poly, int32_t basis, int32_t k, int32_t ell);

        static void decomp(int32_t **d_ct, long* poly, int32_t sizeof_poly, int32_t basis, int32_t k, int32_t ell);

        static void signed_decomp(int64_t **d_ct, long* poly, int32_t sizeof_poly, int32_t basis, int32_t k, int32_t ell, int64_t Q);

        static void compose(int64_t *out, int64_t **d_ct, int32_t sizeof_poly, int32_t basis, int32_t ell);
  
        //static void gaussian_sample(int64_t **out, long* in, int32_t sizeof_poly, int32_t basis, int32_t k, int32_t ell, Sampler &rand);
 

        // Some stuff for statistics
        static int64_t max(long* in, int32_t N);

        static int64_t min(long* in, int32_t N);

        static double mean(long* in, int32_t N);

        static double variance(long* in, int32_t N);

        static double variance(long* in, int32_t N, double mean);

        static double standard_deviation(long* in, int32_t N);

        static double standard_deviation(long* in, int32_t N, double mean);

        static int64_t infinity_norm(long* in, int32_t N);

        static long* count_occurences(long* in, int32_t N);

        static int64_t count_positive(long* in, int32_t N);

        static int64_t count_negative(long* in, int32_t N);

};

/// @brief  The class is to handle multiplication of integers within 64-bit long.
/// When multiplying integers where the modulus is higher than 32-bits, there may be a overflow.
/// This class handles such multiplication correctly without implementing big integers.
/// The trick is to build an algorithm analogous to the square-and-multiply method for modular exponentiation,
/// but here we are in the additive group of integers.  
class LongIntegerMultipler{
    
    public: 

    /// @brief Modulus for the computation.
    uint64_t modulus;
    /// @brief Decomposition base
    uint64_t base;
    /// @brief Number of bits of the decomposition base
    uint64_t bits_base;
    /// @brief Modulus_log_base = Log_(base)(modulus)
    uint32_t modulus_log_base;
    /// @brief Table for digit decomposition
    std::unique_ptr<long[]> decomp;

    LongIntegerMultipler(uint64_t modulus);
 
    uint64_t mul(uint64_t in_1, uint64_t in_2);
};


}

#endif