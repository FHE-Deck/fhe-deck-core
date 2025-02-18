#include "interface/plaintext_encoding.h"

using namespace FHEDeck;
 
PlaintextEncoding::PlaintextEncoding(PlaintextEncodingType type, int64_t plaintext_space, int64_t ciphertext_modulus){
    this->type = type;
    this->plaintext_space = plaintext_space;
    this->ciphertext_modulus = ciphertext_modulus;
    calculate_ticks(); 
}

PlaintextEncodingType PlaintextEncoding::get_type()const{
    return type;
}

void PlaintextEncoding::set_type(PlaintextEncodingType type){
    this->type = type;
    calculate_ticks();
}

int64_t PlaintextEncoding::get_plaintext_space()const{
    return plaintext_space;
}

void PlaintextEncoding::set_plaintext_space(int64_t plaintext_space){
    this->plaintext_space = plaintext_space;
    calculate_ticks();
}

int64_t PlaintextEncoding::get_ciphertext_modulus()const{
    return ciphertext_modulus;
}

void PlaintextEncoding::set_ciphertext_modulus(int64_t ciphertext_modulus){
    this->ciphertext_modulus = ciphertext_modulus;
    calculate_ticks();
}

void PlaintextEncoding::calculate_ticks(){
    if(type == PlaintextEncodingType::full_domain){ 
        this->ticks =  plaintext_space;
    }else if(type ==  PlaintextEncodingType::partial_domain){ 
        this->ticks = 2 * plaintext_space; 
    }else if(type == PlaintextEncodingType::signed_limied_short_int){ 
        this->ticks = 4 * plaintext_space;
    }else if(type == PlaintextEncodingType::signed_limied_short_int_bl){
        this->ticks = 4 * plaintext_space;
    }else{
        throw std::logic_error("Non existent plaintext encoding type");
    }  
}

int64_t PlaintextEncoding::encode_message(int64_t message)const{ 
    /// TODO: Its better to first multiply the message by the ciphertext modulus, divide by ticks and then round.
    /// FOr now tests with ks_functional_bootstrap fail. Perhaps the test enforces this encoding somehow. Need to check it out. 
    uint64_t scale = ciphertext_modulus/ticks; 
    return (int64_t)((__int128_t(message) * __int128_t(scale)) % __int128_t(ciphertext_modulus)); 
}
 
        
int64_t PlaintextEncoding::decode_message(int64_t encoded_message)const{ 
    int64_t message = 0;
    if(type == PlaintextEncodingType::full_domain){ 
        double scale = this->ticks/(double)ciphertext_modulus;
        message = round(encoded_message * scale) ;
        message %= plaintext_space;
    }else if(type ==  PlaintextEncodingType::partial_domain){ 
        double scale = this->ticks/(double)ciphertext_modulus; 
        message = round(encoded_message * scale) ;   
        message %= plaintext_space;  
    }else if(type == PlaintextEncodingType::signed_limied_short_int){   
        double scale = this->ticks/(double)ciphertext_modulus; 
        message = round(encoded_message * scale);  
        message = Utils::integer_signed_form(message, this->ticks); 
    }else if(type == PlaintextEncodingType::signed_limied_short_int_bl){ 
        double scale = this->ticks/(double)ciphertext_modulus;
        message = round(encoded_message * scale);   
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

 
void PlaintextEncoding::encode_message(Vector& out, const Vector& message)const{ 
    for(int32_t i = 0; i < message.size; ++i){
        out.vec[i] = encode_message(message.vec[i]);
    }
}
 
void PlaintextEncoding::decode_message(Vector& out, const Vector& encoded_message)const{
    for(int32_t i = 0; i < encoded_message.size; ++i){
        out.vec[i] = decode_message(encoded_message.vec[i]);
    }
}

bool PlaintextEncoding::operator==(const PlaintextEncoding &other) const{
    return (type == other.type) && (plaintext_space == other.plaintext_space) && (ciphertext_modulus == other.ciphertext_modulus);
}

bool PlaintextEncoding::operator!=(const PlaintextEncoding &other) const{
    return (type != other.type) || (plaintext_space != other.plaintext_space) || (ciphertext_modulus != other.ciphertext_modulus);
}