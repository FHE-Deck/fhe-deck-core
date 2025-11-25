#include "interface/rotation_poly.h"
 
using namespace FHEDeck;
  
RotationPoly::RotationPoly(
    std::function<int64_t(int64_t)> f, 
    int64_t size, 
    PlaintextEncoding input_encoding, 
    PlaintextEncoding output_encoding): Polynomial(size, output_encoding.get_ciphertext_modulus()){
 
    this->input_encoding = input_encoding;
    this->output_encoding = output_encoding; 
    this->is_amortized_form = true;
    
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
 
            m_vec[size-i-1] = output_encoding.encode_message(arg) ; 
            i--;
    }
    while(i >= 0){  
        arg = f(in_enc_mod_switch.decode_message(i));
     
        m_vec[size-i-1] = output_encoding.encode_message(-arg);  
        i--;
    }  
}

RotationPoly::RotationPoly(
    std::function<int64_t(int64_t,int64_t)> f, 
    int64_t size, 
    PlaintextEncoding output_encoding,
    bool is_amortized_form): Polynomial(size, output_encoding.get_ciphertext_modulus()){ 
     
    this->input_encoding = output_encoding;
    this->output_encoding = output_encoding; 
    this->is_amortized_form = is_amortized_form; 

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
            m_vec[size-i-1] = output_encoding.encode_message(arg); 
            i--;
    }
    while(i >= 0){ 
        arg = f(in_enc_mod_switch.decode_message(i), in_enc_mod_switch.get_plaintext_space()); 
        m_vec[size-i-1] = output_encoding.encode_message(-arg);  
        i--;
    }  
}

RotationPoly::RotationPoly(
    std::function<int64_t(int64_t)> f, 
    int64_t size, 
    PlaintextEncoding output_encoding, 
    bool is_amortized_form): Polynomial(size, output_encoding.get_ciphertext_modulus()){
     
    this->input_encoding = output_encoding;
    this->output_encoding = output_encoding; 
    this->is_amortized_form = is_amortized_form;
    
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
 
            m_vec[size-i-1] = output_encoding.encode_message(arg) ; 
            i--;
    }
    while(i >= 0){  
        arg = f(in_enc_mod_switch.decode_message(i));
     
        m_vec[size-i-1] = output_encoding.encode_message(-arg);  
        i--;
    }  
}
  

RotationPoly::RotationPoly(const RotationPoly &poly): Polynomial(poly.m_size, poly.m_modulus){  
    this->output_encoding = poly.output_encoding;
    
    for(int32_t i = 0; i < this->size(); ++i){   
        m_vec[i] = poly[i]; 
    }  
}


RotationPoly& RotationPoly::operator=(const RotationPoly other){ 
    m_size = other.m_size;
    m_modulus = other.m_modulus;
    init();  
    this->output_encoding = other.output_encoding; 
    for(int32_t i = 0; i < m_size; ++i){   
        m_vec[i] = other[i]; 
    }  
    return *this;
}

void RotationPoly::encode(){
    if(is_encoded){
        return;
    } 
 
    PlaintextEncoding in_enc_mod_switch; 
    if(input_encoding.get_type() == PlaintextEncodingType::full_domain){ 
        in_enc_mod_switch = PlaintextEncoding(input_encoding.get_type(), input_encoding.get_plaintext_space(), m_size);
    }else if(input_encoding.get_type() == PlaintextEncodingType::partial_domain){ 
        in_enc_mod_switch = PlaintextEncoding(input_encoding.get_type(), input_encoding.get_plaintext_space(), 2*m_size);
    }else if(input_encoding.get_type() == PlaintextEncodingType::signed_limied_short_int){
        // Actually I need to have some sort of special encoding here. 
        in_enc_mod_switch = PlaintextEncoding(PlaintextEncodingType::signed_limied_short_int_bl, output_encoding.get_plaintext_space(), 2*m_size);
    }else{
         throw std::logic_error("Non existend encoding type!");
    }

    /// NOTE: For some reason I didn't chose full domain etc. here.... It worked anyway... Don't know why.... 
    int32_t i = m_size-1; 
    while(in_enc_mod_switch.decode_message(i) == 0){  
            m_vec[m_size-i-1] = output_encoding.encode_message(m_vec[m_size-i-1]); 
            i--;
    }
    while(i >= 0){ 
        m_vec[m_size-i-1] = output_encoding.encode_message(m_vec[m_size-i-1]); 
        i--;
    } 
    is_encoded = true;
}

 void RotationPoly::decode(){
    if(!is_encoded){
        return;
    }
    for(int32_t i = 0; i < m_size; ++i){  
        m_vec[i] = output_encoding.decode_message(m_vec[i]);
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
    normalize();  
    is_amortized_form = true;
}

void RotationPoly::to_non_amortized_form(){
    if(!is_amortized_form){
        return;
    }
    Utils::array_signed_form(m_vec, m_vec, m_size, output_encoding.get_ciphertext_modulus()); 
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
    RotationPoly out;
    out.m_size = size;
    out.m_modulus = ciphertext_modulus;
    out.init();
    for(int32_t i = 0; i < size; ++i){
        out.m_vec[i] = Utils::integer_mod_form(delta_Q_t * -1, ciphertext_modulus); 
    }  
    return out;
}

RotationPoly RotationPoly::rot_msb(int32_t plaintext_space, int64_t size, int64_t ciphertext_modulus){
    int64_t delta_Q_t = (int64_t)round((double)ciphertext_modulus/(double)(plaintext_space*2));  
    RotationPoly out;
    out.m_size = size;
    out.m_modulus = ciphertext_modulus;
    out.init();
    for(int32_t i = 0; i < size; ++i){
        out.m_vec[i] = Utils::integer_mod_form(delta_Q_t, ciphertext_modulus); 
    }  
    return out;
}

/// TODO: This procedure should actually be called rot_zero...
/// TODO: Also, question whether we realy need rotation polynomials? Do, we need input and output encodings?
/// If not then perhaps I should have a builder, that builds normal polynomials. Need to think about that...
RotationPoly RotationPoly::rot_one(int64_t size, int64_t modulus){  
    RotationPoly out;
    out.m_size = size; 
    out.m_modulus = modulus;
    out.init();
    for(int32_t i = 0; i < size; ++i){
        out[i] = 0;
    }   
    return out;
}
 