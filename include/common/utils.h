 
#ifndef UTILS_H
#define UTILS_H

#include <NTL/ZZX.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_p.h>
#include <string>
#include "sample.h"
#include "enums.h"
//#include "ntru_param.h"



namespace fhe_deck{

class Utils{

    public:

        static void set_polynomial_from_array(NTL::ZZ_pX &poly, long *f, int sizeof_f, long Q);

        static void set_array_from_polynomial(long *array, int sizeof_array, NTL::ZZ_pX poly);

        static void add_polynomials(long *out, long *in_1, long *in_2, int sizeof_in_1, int sizeof_in_2);

        static void mod_polynomial(long *out, long *in, int sizeof_in, long modulus);

        static void mul_scalar(long *out, long *in, int sizeof_in, long scalar);
 

        static void mul_mod(long *out, long *in_1, int sizeof_in_1, long *in_2, int sizeof_in_2, long N, long modulus, RingType ring);
 

        static void add_mod(long *out, long *in_1, int sizeof_in_1, long *in_2, int sizeof_in_2, long N, long modulus);

        static void sub_mod(long *out, long *in_1, int sizeof_in_1, long *in_2, int sizeof_in_2, long N, long modulus);

        static void neg_mod(long *out, long *in_1, int size, long modulus);

        static long mod_inv(long in, long modulus);

        static NTL::ZZ_pX get_ring_poly(RingType ring, long N, long modulus);
 
        static void cp(long *out, long *in, int size);

        // Returns the smallest k, s.t. base**k >= x
        static int power_times(long x, long base);

        static bool is_power_of(long x, long base);

        static long abs(long x);

        // Computes (z**2)/4 mod modulus
        // Its usefull from computing x * y = (x+y)**2/4 - (x-y)**2/4 mod modulus
        // TODO Should be in a class for building rotation polynomials
        static long square_and_div_by_4(long in, long modulus);

        static long eval_poly_mod(long in, int* poly, int poly_size, long modulus);

        static bool is_eq_poly(long *in_1, long *in_2, int sizeof_in);
 
        static void rotate_poly(long *out_poly, long *in_poly, int poly_size, int rot);

        static void negacyclic_rotate_poly(long *out_poly, long *in_poly, int poly_size, int rot);

        static long integer_signed_form(long in, long Q);
 
        static void array_signed_form(long *out, long *in, int sizeof_in, long Q);

        static long integer_mod_form(long in, long Q);

        static void array_mod_form(long *out, long *in, int sizeof_in, long Q);
 
 
        // Below we have functions for rounding and modulus reducing polynomials 
        static void round_and_mod_reduce(long *out_poly, double *in_poly, long modulus, int sizeof_in_poly);

        static void round_and_mod_reduce(long *out_poly, long double *in_poly, long modulus, int sizeof_in_poly);

        static void round_and_mod_reduce_power_of_two(long *out_poly, double *in_poly, long mask, int sizeof_in_poly);

        static void round_and_mod_reduce_power_of_two(long *out_poly, long double *in_poly, long mask, int sizeof_in_poly);  

        static void mod_reduce_power_of_two(long *out_poly, long *in_poly, long modulus, int sizeof_in_poly);

        static void mod_reduce(long *out_poly, long *in_poly, long modulus, int sizeof_in_poly); 

        static void mod_reduce(long *out_poly, long double *in_poly_l, long modulus, int sizeof_in_poly); 




        static long integer_rounding(long in, long Q, long t);

        static void array_rounding(long *out, long *in, int sizeof_in, long Q, long t); 

        static std::string to_string(long *poly, int sizeof_poly);

        static std::string to_string(double *poly, int sizeof_poly);

        static std::string to_string(int *poly, int sizeof_poly);

        static void set(long* out, long* in, int sizeof_in);

        static long integer_compose(long *dec_in, int basis, int ell);

        static void integer_decomp(long *dec_out, long in , int basis, int k, int ell);

        // Below are the gadget (should be perhaps in a separate class?)
        // TODO: All those are in the gadget class - delete from here after testing 
        static void decomp(long **d_ct, long* poly, int sizeof_poly, int basis, int k, int ell);

        static void decomp(int **d_ct, long* poly, int sizeof_poly, int basis, int k, int ell);

        static void signed_decomp(long **d_ct, long* poly, int sizeof_poly, int basis, int k, int ell, long Q);

        static void compose(long *out, long **d_ct, int sizeof_poly, int basis, int ell);
  
        static void gaussian_sample(long **out, long* in, int sizeof_poly, int basis, int k, int ell, Sampler &rand);
 

        // Some stuff for statistics
        static long max(long* in, int N);

        static long min(long* in, int N);

        static double mean(long* in, int N);

        static double variance(long* in, int N);

        static double variance(long* in, int N, double mean);

        static double standard_deviation(long* in, int N);

        static double standard_deviation(long* in, int N, double mean);

        static long infinity_norm(long* in, int N);

        static long* count_occurences(long* in, int N);

        static long count_positive(long* in, int N);

        static long count_negative(long* in, int N);

};

}

#endif