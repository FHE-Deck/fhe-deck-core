#include "interface/rotation_poly.h"
 
using namespace fhe_deck;

RotationPoly::~RotationPoly(){
    if(is_init){ 
        delete[] this->coefs;
    }
}

RotationPoly::RotationPoly(const RotationPoly &poly){ 
    this->coefs = new int64_t[poly.degree];
    this->output_encoding = poly.output_encoding;
    this->coef_modulus = poly.coef_modulus;
    this->degree = poly.degree; 
    for(int32_t i = 0; i < this->degree; ++i){   
        this->coefs[i] = poly.coefs[i]; 
    } 
    this->is_init = true;
}


RotationPoly& RotationPoly::operator=(const RotationPoly other){
    if(!this->is_init){  
        this->coefs = new int64_t[other.degree];
    }
    this->output_encoding = other.output_encoding;
    this->coef_modulus = other.coef_modulus;
    this->degree = other.degree; 
    for(int32_t i = 0; i < this->degree; ++i){   
        this->coefs[i] = other.coefs[i]; 
    } 
    this->is_init = true;
    return *this;
}

RotationPoly::RotationPoly(std::function<int64_t(int64_t,int64_t)> f, int64_t degree, PlaintextEncoding output_encoding, bool is_amortized_form){ 
    this->degree = degree; 
    this->output_encoding = output_encoding;
    this->coef_modulus = output_encoding.ciphertext_modulus;
    this->is_amortized_form = is_amortized_form;
    coefs = new int64_t[degree]; 
    PlaintextEncoding input_encoding; 
    if(output_encoding.type == PlaintextEncodingType::full_domain){ 
        input_encoding = PlaintextEncoding(output_encoding.type, output_encoding.plaintext_space, degree);
    }else if(output_encoding.type == PlaintextEncodingType::partial_domain){ 
        input_encoding = PlaintextEncoding(output_encoding.type, output_encoding.plaintext_space, 2*degree);
    }else if(output_encoding.type == PlaintextEncodingType::signed_limied_short_int){
        // Actually I need to have some sort of special encoding here. 
        input_encoding = PlaintextEncoding(PlaintextEncodingType::signed_limied_short_int_bl, output_encoding.plaintext_space, 2*degree);
    }else{
         throw std::logic_error("Non existend encoding type!");
    }

    int64_t arg;
    int32_t i = degree-1; 
    while(input_encoding.decode_message(i) == 0){ 
            arg = f(input_encoding.decode_message(i), input_encoding.plaintext_space); 
            coefs[degree-i-1] = output_encoding.encode_message(arg); 
            i--;
    }
    while(i >= 0){ 
        arg = f(input_encoding.decode_message(i), input_encoding.plaintext_space); 
        coefs[degree-i-1] = output_encoding.encode_message(-arg);  
        i--;
    } 
    this->is_init = true;
}

RotationPoly::RotationPoly(std::function<int64_t(int64_t)> f, int64_t degree, PlaintextEncoding output_encoding, bool is_amortized_form){
    this->degree = degree; 
    this->output_encoding = output_encoding;
    this->coef_modulus = output_encoding.ciphertext_modulus;
    this->is_amortized_form = is_amortized_form;
    this->coefs = new int64_t[degree];
     
    PlaintextEncoding input_encoding; 
    if(output_encoding.type == PlaintextEncodingType::full_domain){ 
        input_encoding = PlaintextEncoding(output_encoding.type, output_encoding.plaintext_space, degree);
    }else if(output_encoding.type == PlaintextEncodingType::partial_domain){ 
        input_encoding = PlaintextEncoding(output_encoding.type, output_encoding.plaintext_space, 2*degree);
    }else if(output_encoding.type == PlaintextEncodingType::signed_limied_short_int){ 
        input_encoding = PlaintextEncoding(PlaintextEncodingType::signed_limied_short_int_bl, output_encoding.plaintext_space, 2*degree);
    }
 
    int64_t arg;
    int32_t i = degree-1;  
    while(input_encoding.decode_message(i) == 0){  
            arg = f(input_encoding.decode_message(i));  
 
            coefs[degree-i-1] = output_encoding.encode_message(arg) ; 
            i--;
    }
    while(i >= 0){  
        arg = f(input_encoding.decode_message(i));
     
        coefs[degree-i-1] = output_encoding.encode_message(-arg);  
        i--;
    } 
    this->is_init = true;
}
  
void RotationPoly::encode(){
    if(is_encoded){
        return;
    } 
    PlaintextEncoding input_encoding(output_encoding.type, output_encoding.plaintext_space, 2*degree);
    int32_t i = degree-1; 
    while(input_encoding.decode_message(i) == 0){  
            coefs[degree-i-1] = output_encoding.encode_message(coefs[degree-i-1]); 
            i--;
    }
    while(i >= 0){ 
        coefs[degree-i-1] = output_encoding.encode_message(coefs[degree-i-1]); 
        i--;
    } 
    is_encoded = true;
}

 void RotationPoly::decode(){
    if(!is_encoded){
        return;
    }
    for(int32_t i = 0; i < degree; ++i){  
         this->coefs[i] = output_encoding.decode_message(coefs[i]);
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
    Utils::array_mod_form(this->coefs, this->coefs, degree, output_encoding.ciphertext_modulus); 
    is_amortized_form = true;
}

void RotationPoly::to_non_amortized_form(){
    if(!is_amortized_form){
        return;
    }
    Utils::array_signed_form(this->coefs, this->coefs, degree, output_encoding.ciphertext_modulus); 
    if(!is_encoded){
        encode();   
    }
    is_amortized_form = false;
}
   
/* Note: this doesn't realy compute the sign function. For zero for example it computes 1
    But note that this is actually specific to a particular functional bootstrapipng algorithm. Its not used anywhere else. 
*/
RotationPoly RotationPoly::rot_sgn(int32_t plaintext_space, int64_t degree, int64_t ciphertext_modulus){
    int64_t delta_Q_t = (int64_t)round((double)ciphertext_modulus/(double)plaintext_space); 
    int64_t* acc = new int64_t[degree]; 
    for(int32_t i = 0; i < degree; ++i){
        acc[i] =  Utils::integer_mod_form(delta_Q_t * -1, ciphertext_modulus); 
    } 
    RotationPoly out;
    out.degree = degree;
    out.coef_modulus = ciphertext_modulus;
    out.coefs = acc;
    out.is_init = true;
    return out;
}

RotationPoly RotationPoly::rot_msb(int32_t plaintext_space, int64_t degree, int64_t ciphertext_modulus){
    int64_t delta_Q_t = (int64_t)round((double)ciphertext_modulus/(double)(plaintext_space*2)); 
    int64_t* acc = new int64_t[degree]; 
    for(int32_t i = 0; i < degree; ++i){
        acc[i] =  Utils::integer_mod_form(delta_Q_t, ciphertext_modulus); 
    } 
    RotationPoly out;
    out.degree = degree;
    out.coef_modulus = ciphertext_modulus;
    out.coefs = acc;
    out.is_init = true;
    return out;
}

RotationPoly RotationPoly::rot_one(int64_t N, int64_t Q){
    int64_t* acc = new int64_t[N]; 
    for(int32_t i = 0; i < N; ++i){
        acc[i] = 0;
    }  
    RotationPoly out;
    out.degree = N; 
    out.coef_modulus = Q;
    out.coefs = acc;
    out.is_init = true;
    return out;
}
 