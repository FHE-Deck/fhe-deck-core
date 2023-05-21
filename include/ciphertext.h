#ifndef CIPHERTEXT_H
#define CIPHERTEXT_H

#include <iostream>
#include "lwe_param.h"
#include "enums.h"  
#include "plaintext_encoding.h"

class ciphertext{

    public: 
 
        lwe_ct *lwe_c;
        bool is_lwe_ct = false;

        bool is_init = false;
 
        plaintext_encoding encoding;

        ~ciphertext();

        ciphertext();
 

        ciphertext(lwe_ct &lwe_c, plaintext_encoding encoding);
 
        ciphertext(const ciphertext &c);

        ciphertext(ciphertext &other);


        ciphertext& operator=(const ciphertext other);

  
        void add(ciphertext* ct);

        void sub(ciphertext* ct) ;

        void mul(long b);
  
        ciphertext operator+(long b);

        ciphertext operator+(ciphertext ct);

        ciphertext operator-(long b);

        ciphertext operator-(ciphertext ct);

        ciphertext operator-();
    
        ciphertext operator*(long b);
 
};



ciphertext operator+(long b, ciphertext ct);

ciphertext operator-(long b, ciphertext ct);

ciphertext operator*(long b, ciphertext ct);

#endif