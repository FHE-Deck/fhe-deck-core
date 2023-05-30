#ifndef ENUMS_H
#define ENUMS_H


enum ring_type {cyclic, negacyclic};
enum modulus_type {any, power_of_two}; 
enum key_dist {binary, ternary, uniform};

enum polynomial_arithmetic {ntl, double_fft, long_double_fft, hexl_ntt};
 
enum gadget_type {signed_decomposition_gadget, discrete_gaussian_gadget};

enum key_switch_type {standard_key_switch, lazy_key_switch, partial_lazy_key_switch};
 
  


enum plaintext_encoding_type {signed_limied_short_int, full_domain, partial_domain};



#endif