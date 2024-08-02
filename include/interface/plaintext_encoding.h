#ifndef PLAINTEXT_ENCODING_H
#define PLAINTEXT_ENCODING_H
 
/**
 * @file plaintext_encoding.h
 */

#include <iostream>
#include "enums.h"  
#include "utils.h"

namespace fhe_deck{
 
/// @brief Class for encoding and decoding plaintext messages used pre-processing and post-processing in LWE-like encryption decryption procedures. 
class PlaintextEncoding{

public:

    /// @brief Type of encoding used for encoding and decoding plaintext messages.
    PlaintextEncodingType type = full_domain;
    /// @brief Number of elements in the plaintext space.
    int64_t plaintext_space = 0;
    /// @brief Ciphertext modulus used for encoding and decoding plaintext messages.
    int64_t ciphertext_modulus = 0;

    /// @brief Default constructor.
    PlaintextEncoding() = default;

    /// @brief Constructs the plaintext encodings. 
    /// @param type Type of the plaintext encoding.
    /// @param plaintext_space The number of elements in the plaintext space.
    /// @param ciphertext_moduluse The ciphertext modulus. This plaintext encoding instance will work correctly only for these ciphertext modulus.
    PlaintextEncoding(PlaintextEncodingType type, int64_t plaintext_space, int64_t ciphertext_moduluse);
    
    /// @brief Encode a message.
    /// @param message The message to be encoded.
    /// @return The encoded message.
    int64_t encode_message(int64_t message);

    /// @brief Decode a message.
    /// @param phase The encoded message. 
    /// @return The decoded message. 
    int64_t decode_message(int64_t encoded_message);

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

    private: 
    
    /// @brief Number of ticks used for encoding and decoding plaintext messages. It depents on the encoding type.
    int64_t ticks = 0;
  
};

}

#endif