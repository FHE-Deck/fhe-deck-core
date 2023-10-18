#ifndef CIPHERTEXT_H
#define CIPHERTEXT_H

#include <iostream>
#include "lwe.h"
#include "enums.h"  
#include "plaintext_encoding.h" 

namespace fhe_deck{
    
class FHEContext; // Forward declaration

class Ciphertext{

    public: 
 
        LWECT *lwe_c;
        bool is_lwe_ct = false;

        bool is_init = false;
 
        PlaintextEncoding encoding;

        FHEContext* context;

        ~Ciphertext();

        Ciphertext() = default;
  
        Ciphertext(LWECT &lwe_c, PlaintextEncoding encoding, FHEContext* context);
 
        Ciphertext(const Ciphertext &c);

        Ciphertext(Ciphertext &other);
 
        Ciphertext& operator=(const Ciphertext other);
 
        void add(Ciphertext* ct);

        void sub(Ciphertext* ct) ;

        void mul(long b);
  
        Ciphertext operator+(long b);

        Ciphertext operator+(Ciphertext ct);

        Ciphertext operator-(long b);

        Ciphertext operator-(Ciphertext ct);

        Ciphertext operator-();
    
        Ciphertext operator*(long b);
 
};


}
  
fhe_deck::Ciphertext operator+(long b, fhe_deck::Ciphertext ct);

fhe_deck::Ciphertext operator-(long b, fhe_deck::Ciphertext ct);

fhe_deck::Ciphertext operator*(long b, fhe_deck::Ciphertext ct);

#endif