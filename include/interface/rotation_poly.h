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
 
    RotationPoly(int64_t (*f)(int64_t message, int64_t plaintext_space), int64_t degree, PlaintextEncoding output_encoding, bool is_amortized_form = false);

    RotationPoly(int64_t (*f)(int64_t message), int64_t degree, PlaintextEncoding output_encoding, bool is_amortized_form = false); 
  
    RotationPoly(const RotationPoly &poly);

    RotationPoly& operator=(const RotationPoly other);

    void encode();

    void decode();

    void to_amortization_form();

    void to_non_amortized_form();
   
    static RotationPoly rot_msb(int32_t t, int64_t N, int64_t Q); 

    static RotationPoly rot_one(int64_t N, int64_t Q); 
   
};




}

#endif