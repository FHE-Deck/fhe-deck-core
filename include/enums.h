#ifndef ENUMS_H
#define ENUMS_H


enum ring_type {cyclic, negacyclic};
enum modulus_type {any, power_of_two}; 
enum key_dist {binary, ternary, uniform};

enum polynomial_arithmetic {double_fft, long_double_fft, hexl_ntt};

#endif