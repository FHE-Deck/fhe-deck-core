#include "plaintext_encoding.h"
using namespace fhe_deck;
 
PlaintextEncoding::PlaintextEncoding(PlaintextEncodingType type, long plaintext_space, long ciphertext_modulus){
    this->type = type;
    this->plaintext_space = plaintext_space;
    this->ciphertext_modulus = ciphertext_modulus;
    if(type == full_domain){ 
        this->ticks =  plaintext_space;
    }else if(type ==  partial_domain){ 
        this->ticks = 2 * plaintext_space; 
    }else if(type == signed_limied_short_int){ 
        this->ticks = 4 * plaintext_space;
    }else{
        throw std::logic_error("Non existent plaintext encoding type");
    }  
}


long PlaintextEncoding::encode_message(long message){
    double scale = (double)ciphertext_modulus/this->ticks; 
    return round(scale * message);
}
 
        
long PlaintextEncoding::decode_message(long phase){
    long message = 0;
    if(type == full_domain){ 
        double scale = this->ticks/(double)ciphertext_modulus;
        message = round(phase * scale) ;
        message %= plaintext_space;
    }else if(type ==  partial_domain){ 
        double scale = this->ticks/(double)ciphertext_modulus; 
        message = round(phase * scale) ; 
        message %= plaintext_space;
    }else if(type == signed_limied_short_int){ 
        double scale = this->ticks/(double)ciphertext_modulus;
        message = round(phase * scale);
        message = Utils::integer_signed_form(message, plaintext_space*4);
    }else{
        throw std::logic_error("Non existent plaintext encoding type");
    }
    return message;
} 
