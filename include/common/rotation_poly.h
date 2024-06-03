#ifndef ROTATION_POLY_H
#define ROTATION_POLY_H

#include "utils.h"
#include "plaintext_encoding.h"
#include "polynomial.h"

namespace fhe_deck{



class RotationPoly : public Polynomial{
 
public:

    PlaintextEncoding output_encoding;
    bool is_encoded = true; 
    bool is_amortized_form = false;

    ~RotationPoly();

    RotationPoly() = default;
 
    RotationPoly(long (*f)(long message, long plaintext_space), long degree, PlaintextEncoding output_encoding, bool is_amortized_form = false);

    RotationPoly(long (*f)(long message), long degree, PlaintextEncoding output_encoding, bool is_amortized_form = false); 
  
    RotationPoly(const RotationPoly &poly);

    RotationPoly& operator=(const RotationPoly other);

    void encode();

    void decode();

    void to_amortization_form();

    void to_non_amortized_form();
   
    static RotationPoly rot_msb(int t, long N, long Q); 

    static RotationPoly rot_one(long N, long Q); 
   
};




}

#endif