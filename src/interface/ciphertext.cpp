#include "interface/ciphertext.h" 
#include "interface/fhe_context.h"

using namespace FHEDeck;
  
Ciphertext::Ciphertext(std::shared_ptr<LWECT> lwe_c, const PlaintextEncoding& encoding, const FHEContext& context){
    this->lwe_c = lwe_c; 
    this->encoding = encoding; 
    this->context = &context; 
}
   
Ciphertext::Ciphertext(const Ciphertext &other){  
    this->encoding = other.encoding;  
    this->lwe_c = std::shared_ptr<LWECT>(other.lwe_c->clone()); 
    this->context = other.context; 
}
    
Ciphertext& Ciphertext::operator=(const Ciphertext& other){   
    if (this == &other)
    {
        return *this;
    }    

    encoding = other.encoding;
    lwe_c = std::shared_ptr<LWECT>(other.lwe_c->clone()); 
    context = other.context;   
    return *this;
}
 
void Ciphertext::add(Ciphertext& out, const Ciphertext& in) const{ 
    lwe_c->add(*out.lwe_c, *in.lwe_c); 
}
  
void Ciphertext::sub(Ciphertext& out, const Ciphertext& in) const{ 
    lwe_c->sub(*out.lwe_c, *in.lwe_c); 
}
  
void Ciphertext::mul(Ciphertext& out, const int64_t b) const{ 
    lwe_c->mul(*out.lwe_c, b); 
} 
      
Ciphertext Ciphertext::operator+(int64_t b) const{ 
    std::shared_ptr<LWECT> c(new LWECT(lwe_c->param));
    lwe_c->add(*c, encoding.encode_message(b)); 
    return Ciphertext(c, encoding, *context); 
}
 
Ciphertext Ciphertext::operator+(const Ciphertext& ct) const{ 
    std::shared_ptr<LWECT> c(new LWECT(lwe_c->param));
    lwe_c->add(*c, *ct.lwe_c);
    return Ciphertext(c, this->encoding, *context);
}
 
Ciphertext Ciphertext::operator-(int64_t b) const{ 
    std::shared_ptr<LWECT> c(new LWECT(lwe_c->param));
    lwe_c->sub(*c, this->encoding.encode_message(b));
    return Ciphertext(c, this->encoding, *context); 
}
 
Ciphertext Ciphertext::operator-(const Ciphertext& ct) const{
    std::shared_ptr<LWECT> c(new LWECT(lwe_c->param));
    lwe_c->sub(*c, *ct.lwe_c);
    return Ciphertext(c, this->encoding, *context);
}
 
Ciphertext Ciphertext::operator-() const{ 
    std::shared_ptr<LWECT> c(new LWECT(lwe_c->param));
    lwe_c->neg(*c);
    return Ciphertext(c, this->encoding, *context); 
}
     
Ciphertext Ciphertext::operator*(int64_t b) const{
    std::shared_ptr<LWECT> c(new LWECT(lwe_c->param));
    lwe_c->mul(*c, b);
    return Ciphertext(c, this->encoding, *context);
}
 
Ciphertext operator+(int64_t b, const Ciphertext& ct){
    return ct.operator+(b); 
}

Ciphertext operator-(int64_t b, const Ciphertext& ct){
    Ciphertext out = -ct;
    return out + b;
}

Ciphertext operator*(int64_t b, const Ciphertext& ct){ 
    return ct.operator*(b); 
} 