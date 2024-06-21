#ifndef PLAINTEXT_ENCODING_H
#define PLAINTEXT_ENCODING_H
 
#include <iostream>
#include "enums.h"  
#include "utils.h"

namespace fhe_deck{
 
class PlaintextEncoding{

public:

    PlaintextEncodingType type = full_domain;
    int64_t plaintext_space = 0;
    int64_t ciphertext_modulus = 0;
    int64_t ticks = 0;

    PlaintextEncoding() = default;

    PlaintextEncoding(PlaintextEncodingType type, int64_t plaintext_space, int64_t ciphertext_moduluse);
    
    int64_t encode_message(int64_t message);

    int64_t decode_message(int64_t phase);

    template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(type, plaintext_space, ciphertext_modulus);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
        ar(type, plaintext_space, ciphertext_modulus);
         if(type == full_domain){ 
            this->ticks =  plaintext_space;
        }else if(type ==  partial_domain){ 
            this->ticks = 2 * plaintext_space; 
        }else if(type == signed_limied_short_int){ 
            this->ticks = 4 * plaintext_space;
        }else{
            throw std::logic_error("Non existend encoding type!");
        }  
    } 
  
};

}

#endif