#ifndef ROTATION_POLY_H
#define ROTATION_POLY_H

#include "utils.h"

class rotation_poly{


public:

    long* lookup_polynomial;
    long N;
    long Q;
    long t;
    bool is_scaled = true;

    ~rotation_poly();

    rotation_poly() = default;

    rotation_poly(long* lookup_polynomial, long t, long N, long Q);

    rotation_poly(long (*f)(long message, long plaintext_space), long t, long N, long Q);

    rotation_poly(long (*f)(long message), long t, long N, long Q);

    rotation_poly(const rotation_poly &poly);


    static void set_polynomial(long* lookup_polynomial, long (*f)(long message), long t, long N, long Q);

    void flip_scale();
    
    static long* rot_msb(int t, long N, long Q); 

    static long* rot_one(long N); 

    // Deprecated
    static long* rot_identity(int t, long N, long Q); 

    // Deprecated
    static long* rot_uni_poly(int* poly, int poly_size, int t, long N, long Q);

    // Deprecated
    static long* rot_is_zero_of_poly(int* poly, int poly_size, int t, long N, long Q, int t_out);

    // Deprecated
    static long* rot_square_and_div_by_4(int t, long N, long Q); 


    // NOTE: REmind that this is a special rotation polynomial, and is not going to work correctly with all bootstrappings
    // Deprecated
    static long* rot_is_zero(int t, long N, long Q);
    // Deprecated
    static long* rot_inv_mod(int t, long N, long Q); 
    // Deprecated
    static long* cyclic_rot_identity(int t, long N, long Q); 
    // Deprecated
    static long* cyclic_rot_inv_mod(int t, long N, long Q); 
    // Deprecated
    static long* cyclic_rot_square_and_div_by_4(int t, long N, long Q); 
    // Deprecated
    static long* cyclic_rot_uni_poly(int* poly, int poly_size, int t, long N, long Q);  

};

#endif