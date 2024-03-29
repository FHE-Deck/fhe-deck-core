#ifndef ROTATION_POLY_H
#define ROTATION_POLY_H

#include "utils.h"
#include "plaintext_encoding.h"


namespace fhe_deck{

class RotationPoly{
 
public:

    long* lookup_polynomial;
    long N; 
    PlaintextEncoding output_encoding;
    bool is_encoded = true; 
    bool is_amortized_form = false;

    ~RotationPoly();

    RotationPoly() = default;

    
    RotationPoly(long (*f)(long message, long plaintext_space), long N, PlaintextEncoding output_encoding, bool is_amortized_form = false);

    RotationPoly(long (*f)(long message), long N, PlaintextEncoding output_encoding, bool is_amortized_form = false);
 
    RotationPoly(long* lookup_polynomial, long N, PlaintextEncoding output_encoding, bool is_amortized_form = false);
  
    RotationPoly(const RotationPoly &poly);

    void encode();

    void decode();

    void to_amortization_form();

    void to_non_amortized_form();

    static void set_polynomial(long* lookup_polynomial, long (*f)(long message), long t, long N, long Q);

 
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

}

#endif