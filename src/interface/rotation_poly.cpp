#include "interface/rotation_poly.h"
 
using namespace FHEDeck;

/*
RotationPoly::~RotationPoly(){
    if(is_init){ 
        delete[] this->coefs;
    }
}
*/

RotationPoly::RotationPoly(const RotationPoly &poly){ 
    this->vec = new int64_t[poly.size];
    this->output_encoding = poly.output_encoding;
    this->modulus = poly.modulus;
    this->size = poly.size; 
    for(int32_t i = 0; i < this->size; ++i){   
        this->vec[i] = poly[i]; 
    } 
    this->is_init = true;
}


RotationPoly& RotationPoly::operator=(const RotationPoly other){
    if(!this->is_init){  
        this->vec = new int64_t[other.size];
    }
    this->output_encoding = other.output_encoding;
    this->modulus = other.modulus;
    this->size = other.size; 
    for(int32_t i = 0; i < this->size; ++i){   
        this->vec[i] = other[i]; 
    } 
    this->is_init = true;
    return *this;
}

RotationPoly::RotationPoly(std::function<int64_t(int64_t)> f, int64_t degree, PlaintextEncoding input_encoding, PlaintextEncoding output_encoding){
    this->size = degree; 
    this->input_encoding = input_encoding;
    this->output_encoding = output_encoding;
    this->modulus = output_encoding.get_ciphertext_modulus();
    this->is_amortized_form = true;
    this->vec = new int64_t[degree];
     
    //PlaintextEncoding input_encoding; 
    PlaintextEncoding in_enc_mod_switch;
    if(input_encoding.get_type() == PlaintextEncodingType::full_domain){ 
        in_enc_mod_switch = PlaintextEncoding(input_encoding.get_type(), input_encoding.get_plaintext_space(), degree);
    }else if(input_encoding.get_type() == PlaintextEncodingType::partial_domain){ 
        in_enc_mod_switch = PlaintextEncoding(input_encoding.get_type(), input_encoding.get_plaintext_space(), 2*degree);
    }else if(input_encoding.get_type() == PlaintextEncodingType::signed_limied_short_int){ 
        in_enc_mod_switch = PlaintextEncoding(PlaintextEncodingType::signed_limied_short_int_bl, input_encoding.get_plaintext_space(), 2*degree);
    }
 
    int64_t arg;
    int32_t i = degree-1;  
    while(in_enc_mod_switch.decode_message(i) == 0){  
            arg = f(in_enc_mod_switch.decode_message(i));  
 
            vec[degree-i-1] = output_encoding.encode_message(arg) ; 
            i--;
    }
    while(i >= 0){  
        arg = f(in_enc_mod_switch.decode_message(i));
     
        vec[degree-i-1] = output_encoding.encode_message(-arg);  
        i--;
    } 
    this->is_init = true;
}

RotationPoly::RotationPoly(std::function<int64_t(int64_t,int64_t)> f, int64_t size, PlaintextEncoding output_encoding, bool is_amortized_form){ 
    this->size = size;  
    this->input_encoding = output_encoding;
    this->output_encoding = output_encoding;
    this->modulus = output_encoding.get_ciphertext_modulus();
    this->is_amortized_form = is_amortized_form;
    this->vec = new int64_t[size]; 
    PlaintextEncoding in_enc_mod_switch; 
    if(input_encoding.get_type() == PlaintextEncodingType::full_domain){ 
        in_enc_mod_switch = PlaintextEncoding(input_encoding.get_type(), input_encoding.get_plaintext_space(), size);
    }else if(input_encoding.get_type() == PlaintextEncodingType::partial_domain){ 
        in_enc_mod_switch = PlaintextEncoding(input_encoding.get_type(), input_encoding.get_plaintext_space(), 2*size);
    }else if(input_encoding.get_type() == PlaintextEncodingType::signed_limied_short_int){
        // Actually I need to have some sort of special encoding here. 
        in_enc_mod_switch = PlaintextEncoding(PlaintextEncodingType::signed_limied_short_int_bl, output_encoding.get_plaintext_space(), 2*size);
    }else{
         throw std::logic_error("Non existend encoding type!");
    }

    int64_t arg;
    int32_t i = size-1; 
    while(in_enc_mod_switch.decode_message(i) == 0){ 
            arg = f(in_enc_mod_switch.decode_message(i), in_enc_mod_switch.get_plaintext_space()); 
            vec[size-i-1] = output_encoding.encode_message(arg); 
            i--;
    }
    while(i >= 0){ 
        arg = f(in_enc_mod_switch.decode_message(i), in_enc_mod_switch.get_plaintext_space()); 
        vec[size-i-1] = output_encoding.encode_message(-arg);  
        i--;
    } 
    this->is_init = true;
}

RotationPoly::RotationPoly(std::function<int64_t(int64_t)> f, int64_t size, PlaintextEncoding output_encoding, bool is_amortized_form){
    this->size = size; 
    this->input_encoding = output_encoding;
    this->output_encoding = output_encoding;
    this->modulus = output_encoding.get_ciphertext_modulus();
    this->is_amortized_form = is_amortized_form;
    this->vec = new int64_t[size];
     
    //PlaintextEncoding input_encoding; 
    PlaintextEncoding in_enc_mod_switch;
    if(input_encoding.get_type() == PlaintextEncodingType::full_domain){ 
        in_enc_mod_switch = PlaintextEncoding(input_encoding.get_type(), input_encoding.get_plaintext_space(), size);
    }else if(input_encoding.get_type() == PlaintextEncodingType::partial_domain){ 
        in_enc_mod_switch = PlaintextEncoding(input_encoding.get_type(), input_encoding.get_plaintext_space(), 2*size);
    }else if(input_encoding.get_type() == PlaintextEncodingType::signed_limied_short_int){ 
        in_enc_mod_switch = PlaintextEncoding(PlaintextEncodingType::signed_limied_short_int_bl, input_encoding.get_plaintext_space(), 2*size);
    }
 
    int64_t arg;
    int32_t i = size-1;  
    while(in_enc_mod_switch.decode_message(i) == 0){  
            arg = f(in_enc_mod_switch.decode_message(i));  
 
            vec[size-i-1] = output_encoding.encode_message(arg) ; 
            i--;
    }
    while(i >= 0){  
        arg = f(in_enc_mod_switch.decode_message(i));
     
        vec[size-i-1] = output_encoding.encode_message(-arg);  
        i--;
    } 
    this->is_init = true;
}
  
void RotationPoly::encode(){
    if(is_encoded){
        return;
    } 


    PlaintextEncoding in_enc_mod_switch; 
    if(input_encoding.get_type() == PlaintextEncodingType::full_domain){ 
        in_enc_mod_switch = PlaintextEncoding(input_encoding.get_type(), input_encoding.get_plaintext_space(), size);
    }else if(input_encoding.get_type() == PlaintextEncodingType::partial_domain){ 
        in_enc_mod_switch = PlaintextEncoding(input_encoding.get_type(), input_encoding.get_plaintext_space(), 2*size);
    }else if(input_encoding.get_type() == PlaintextEncodingType::signed_limied_short_int){
        // Actually I need to have some sort of special encoding here. 
        in_enc_mod_switch = PlaintextEncoding(PlaintextEncodingType::signed_limied_short_int_bl, output_encoding.get_plaintext_space(), 2*size);
    }else{
         throw std::logic_error("Non existend encoding type!");
    }

    /// NOTE: For some reason I didn't chose full domain etc. here.... It worked anyway... Don't know why....
    //PlaintextEncoding input_encoding(output_encoding.type, output_encoding.plaintext_space, 2*size);
    int32_t i = size-1; 
    while(in_enc_mod_switch.decode_message(i) == 0){  
            vec[size-i-1] = output_encoding.encode_message(vec[size-i-1]); 
            i--;
    }
    while(i >= 0){ 
        vec[size-i-1] = output_encoding.encode_message(vec[size-i-1]); 
        i--;
    } 
    is_encoded = true;
}

 void RotationPoly::decode(){
    if(!is_encoded){
        return;
    }
    for(int32_t i = 0; i < size; ++i){  
         this->vec[i] = output_encoding.decode_message(vec[i]);
    } 
    is_encoded = false;
}

void RotationPoly::to_amortization_form(){
    if(is_amortized_form){
        return;
    }
    if(is_encoded){
        decode();   
    }
    Utils::array_mod_form(this->vec, this->vec, size, output_encoding.get_ciphertext_modulus()); 
    is_amortized_form = true;
}

void RotationPoly::to_non_amortized_form(){
    if(!is_amortized_form){
        return;
    }
    Utils::array_signed_form(this->vec, this->vec, size, output_encoding.get_ciphertext_modulus()); 
    if(!is_encoded){
        encode();   
    }
    is_amortized_form = false;
}
   
/* Note: this doesn't realy compute the sign function. For zero for example it computes 1
    But note that this is actually specific to a particular functional bootstrapipng algorithm. Its not used anywhere else. 
*/
RotationPoly RotationPoly::rot_sgn(int32_t plaintext_space, int64_t size, int64_t ciphertext_modulus){
    int64_t delta_Q_t = (int64_t)round((double)ciphertext_modulus/(double)plaintext_space); 
    int64_t* acc = new int64_t[size]; 
    for(int32_t i = 0; i < size; ++i){
        acc[i] =  Utils::integer_mod_form(delta_Q_t * -1, ciphertext_modulus); 
    } 
    RotationPoly out;
    out.size = size;
    out.modulus = ciphertext_modulus;
    out.vec = acc;
    out.is_init = true;
    return out;
}

RotationPoly RotationPoly::rot_msb(int32_t plaintext_space, int64_t size, int64_t ciphertext_modulus){
    int64_t delta_Q_t = (int64_t)round((double)ciphertext_modulus/(double)(plaintext_space*2)); 
    int64_t* acc = new int64_t[size]; 
    for(int32_t i = 0; i < size; ++i){
        acc[i] =  Utils::integer_mod_form(delta_Q_t, ciphertext_modulus); 
    } 
    RotationPoly out;
    out.size = size;
    out.modulus = ciphertext_modulus;
    out.vec = acc;
    out.is_init = true;
    return out;
}

RotationPoly RotationPoly::rot_one(int64_t size, int64_t modulus){
    int64_t* acc = new int64_t[size]; 
    for(int32_t i = 0; i < size; ++i){
        acc[i] = 0;
    }  
    RotationPoly out;
    out.size = size; 
    out.modulus = modulus;
    out.vec = acc;
    out.is_init = true;
    return out;
}
 