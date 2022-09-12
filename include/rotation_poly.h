#ifndef ROTATION_POLY_H
#define ROTATION_POLY_H

#include "utils.h"

class rotation_poly{

public:
    static long* rot_identity(int t, long N, long Q); 

    static long* rot_msb(int t, long N, long Q); 

    static long* rot_uni_poly(int* poly, int poly_size, int t, long N, long Q);

    static long* rot_is_zero_of_poly(int* poly, int poly_size, int t, long N, long Q, int t_out);

    static long* rot_square_and_div_by_4(int t, long N, long Q); 

    // NOTE: REmind that this is a special rotation polynomial, and is not going to work correctly with all bootstrappings
    static long* rot_is_zero(int t, long N, long Q);
  
    static long* rot_inv_mod(int t, long N, long Q); 

    static long* cyclic_rot_identity(int t, long N, long Q); 

    static long* cyclic_rot_inv_mod(int t, long N, long Q); 

    static long* cyclic_rot_square_and_div_by_4(int t, long N, long Q); 

    static long* cyclic_rot_uni_poly(int* poly, int poly_size, int t, long N, long Q);  

};

#endif