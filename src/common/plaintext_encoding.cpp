#include "plaintext_encoding.h"
using namespace fhe_deck;
 
PlaintextEncoding::PlaintextEncoding(PlaintextEncodingType type, int64_t plaintext_space, int64_t ciphertext_modulus){
    this->type = type;
    this->plaintext_space = plaintext_space;
    this->ciphertext_modulus = ciphertext_modulus;
    if(type == full_domain){ 
        this->ticks =  plaintext_space;
    }else if(type ==  partial_domain){ 
        this->ticks = 2 * plaintext_space; 
    }else if(type == signed_limied_short_int){ 
        this->ticks = 4 * plaintext_space;
    }else if(type == signed_limied_short_int_bl){
        this->ticks = 4 * plaintext_space;
    }else{
        throw std::logic_error("Non existent plaintext encoding type");
    }  
}


int64_t PlaintextEncoding::encode_message(int64_t message){
    double scale = (double)ciphertext_modulus/this->ticks; 
    return round(scale * message);
}
 
        
int64_t PlaintextEncoding::decode_message(int64_t phase){ 
    int64_t message = 0;
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
        message = Utils::integer_signed_form(message, this->ticks); 
    }else if(type == signed_limied_short_int_bl){ 
        double scale = this->ticks/(double)ciphertext_modulus;
        message = round(phase * scale);   
        if(message == 0){
            return 0;
        }
        else if(message < plaintext_space){
            // We have a negative number
            return -(plaintext_space - message) ; 
        }
        // We have a positive number
        return message % plaintext_space; 
    }else{
        throw std::logic_error("Non existent plaintext encoding type");
    }
    return message;
} 
