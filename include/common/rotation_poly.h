#ifndef ROTATION_POLY_H
#define ROTATION_POLY_H

#include "utils.h"
#include "plaintext_encoding.h"
#include "polynomial.h"

namespace fhe_deck{



class RotationPoly : public Polynomial{
 
public:

    //long* coefs;
    //long N; 
    PlaintextEncoding output_encoding;
    bool is_encoded = true; 
    bool is_amortized_form = false;

    ~RotationPoly();

    RotationPoly() = default;
 
    RotationPoly(long (*f)(long message, long plaintext_space), long degree, PlaintextEncoding output_encoding, bool is_amortized_form = false);

    RotationPoly(long (*f)(long message), long degree, PlaintextEncoding output_encoding, bool is_amortized_form = false);
 
    RotationPoly(long* coefs, long degree, PlaintextEncoding output_encoding, bool is_amortized_form = false);
  
    RotationPoly(const RotationPoly &poly);

    RotationPoly& operator=(const RotationPoly other);

    void encode();

    void decode();

    void to_amortization_form();

    void to_non_amortized_form();

    static void set_polynomial(long* lookup_polynomial, long (*f)(long message), long t, long N, long Q);
 
    static RotationPoly rot_msb(int t, long N, long Q); 

    static RotationPoly rot_one(long N, long Q); 
 
 
    // Deprecated
    static long* rot_identity(int t, long N, long Q); 

    // Deprecated
    static long* rot_uni_poly(int* poly, int poly_size, int t, long N, long Q);

    // Deprecated
    static long* rot_is_zero_of_poly(int* poly, int poly_size, int t, long N, long Q, int t_out);

    // Deprecated
    static long* rot_square_and_div_by_4(int t, long N, long Q); 

    // TODO: Delete this stuff. 
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