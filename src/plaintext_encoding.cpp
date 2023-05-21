#include "../include/plaintext_encoding.h"

plaintext_encoding::plaintext_encoding(){}

plaintext_encoding::plaintext_encoding(plaintext_encoding_type type, long plaintext_space, long ciphertext_modulus){
    this->type = type;
    this->plaintext_space = plaintext_space;
    this->ciphertext_modulus = ciphertext_modulus;
}


long plaintext_encoding::encode_message(long message){
    double scale = 0;
    if(type == full_domain){ 
        scale = (double)ciphertext_modulus/plaintext_space;  
    }else if(type ==  partial_domain){ 
        scale = (double)ciphertext_modulus/plaintext_space;
        scale /= 2; 
    }else if(type == signed_limied_short_int){ 
        scale = (double)ciphertext_modulus/(plaintext_space * 4); 
    }else{
        throw 0;
    }
    return round(scale * message);
}
 
        
long plaintext_encoding::decode_message(long phase){
    long message = 0;
    if(type == full_domain){ 
        double scale = plaintext_space/(double)ciphertext_modulus;
        message = round(phase * scale) ;
        message %= plaintext_space;
    }else if(type ==  partial_domain){ 
        double scale = (2*plaintext_space)/(double)ciphertext_modulus;
        message = round(phase * scale);
        message %= plaintext_space;
    }else if(type == signed_limied_short_int){ 
        double scale = (4*plaintext_space)/(double)ciphertext_modulus;
        message = round(phase * scale);
        message = utils::integer_signed_form(message, plaintext_space*4);
    }else{
        throw 0;
    }
    return message;
} 