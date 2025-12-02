#ifndef UTILS_H
#define UTILS_H
  
/**
 * @file utils.h
 */
#include "global_headers.h" 
#include "math/vector.h"
  
namespace FHEDeck{

class Utils{

    public:
   
        static std::pair<int64_t, std::pair<int64_t, int64_t>> extended_euclidean_algorithm(int64_t a, int64_t b);
  
        static int64_t mod_inv(int64_t in, int64_t modulus);
  
        /// Returns the smallest k, s.t. base**k >= x. For x = 0 and x = 1 it returns 1.
        /// TODO: Note. IN some cases return floor(log2(x)/log2(base))+1; returns a different value than this.
        /// But if I use return floor(log2(x)/log2(base))+1; then bootstrapp isn't correct. Need to check why. 
        /// int32_t number_of_digits(int64_t x, int64_t base) give the actuall digit number based on floor(log2(x)/log2(base))+1
        /// It seems that as some point I'm asking about the log_2(x) where x is a power of two. That is why I get discrepancies, and where use of nomber_of_digits fails. 
        /// Many decomposition algorithms are specialized for powers of two. 
        static int32_t power_times(int64_t x, int64_t base);

        static int32_t number_of_digits(int64_t x, int64_t base);

        static bool is_power_of(int64_t x, int64_t base);

        static int64_t pow(int64_t x, int64_t base);

        static int64_t abs(int64_t x);

        // Returns the smallest m s.t. 2**m < x. I cannot rely on the log function from the math library due to precision
        static int32_t number_of_bits(int64_t x);
  
        static int64_t integer_signed_form(int64_t in, int64_t Q);
  
        static int64_t integer_mod_form(int64_t in, int64_t Q);
  
        static std::vector<int64_t> integer_decomp(int64_t in , int32_t basis, int32_t k, int32_t ell);

        static int64_t integer_compose(const std::vector<int64_t>& dec_in, int32_t basis, int32_t ell);
 
        // Some stuff for statistics
        static int64_t max(const std::vector<int64_t>& in);

        static int64_t min(const std::vector<int64_t>& in);

        static double mean(const std::vector<int64_t>& in);

        static double variance(const std::vector<int64_t>& in);

        static double variance(const std::vector<int64_t>& in, double mean);

        static double standard_deviation(const std::vector<int64_t>& in);

        static double standard_deviation(const std::vector<int64_t>& in, double mean);

        static int64_t infinity_norm(const std::vector<int64_t>& in);

        static long* count_occurences(const std::vector<int64_t>& in);

        static int64_t count_positive(const std::vector<int64_t>& in);

        static int64_t count_negative(const std::vector<int64_t>& in);

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

    LongIntegerMultipler(uint64_t modulus);
 
    uint64_t mul(uint64_t in_1, uint64_t in_2);
};
 
 
} /// End of namespace FHEDeck

#endif