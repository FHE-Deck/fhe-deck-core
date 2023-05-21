#ifndef PLAINTEXT_ENCODING_H
#define PLAINTEXT_ENCODING_H
 
#include <iostream>
#include "enums.h"  
#include "utils.h"

class plaintext_encoding{

public:

    plaintext_encoding_type type = full_domain;
    long plaintext_space = 0;
    long ciphertext_modulus = 0;

    plaintext_encoding();

    plaintext_encoding(plaintext_encoding_type type, long plaintext_space, long ciphertext_modulus);
    
    long encode_message(long message);

    long decode_message(long phase);
  
};

#endif