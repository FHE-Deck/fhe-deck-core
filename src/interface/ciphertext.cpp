#include "interface/ciphertext.h" 
#include "interface/fhe_context.h"

using namespace FHEDeck;
  
Ciphertext::Ciphertext(std::shared_ptr<LWECT> lwe_c, const PlaintextEncoding& encoding, const FHEContext& context){
    this->lwe_c = lwe_c;
    this->is_lwe_ct = true; 
    this->is_init = true;
    this->encoding = encoding; 
    this->context = &context; 
}
   
Ciphertext::Ciphertext(const Ciphertext &other){  
    this->encoding = other.encoding; 
    if(other.is_lwe_ct){
        this->lwe_c = std::shared_ptr<LWECT>(other.lwe_c->clone());
        this->is_lwe_ct = true; 
        this->is_init = true;
        this->context = other.context;
    }else{
        throw std::logic_error("Ciphertext::Ciphertext(const Ciphertext &other): Ciphertext type not supported!");
    } 
}
    
Ciphertext& Ciphertext::operator=(const Ciphertext& other){   
    if (this == &other)
    {
        return *this;
    }    
    if(!this->is_init && other.is_lwe_ct){  
        this->encoding = other.encoding;
        this->lwe_c = std::shared_ptr<LWECT>(other.lwe_c->clone());
        this->is_lwe_ct = true; 
        this->is_init = true;  
        this->context = other.context;  
        return *this;
    } else if(other.is_lwe_ct && this->is_lwe_ct){    
        this->encoding = other.encoding;
        this->lwe_c->param = other.lwe_c->param;
        for(int i = 0; i < this->lwe_c->param->dim+1; ++i){
            this->lwe_c->ct[i] = other.lwe_c->ct[i];
        } 
    }else{ 
        throw std::logic_error("Ciphertext& Ciphertext::operator=: Most likely wrong Ciphertext type!");
    }  
    return *this;
}
 
void Ciphertext::add(Ciphertext& out, const Ciphertext& in) const{
    if(is_lwe_ct){ 
        
        this->lwe_c->add(*out.lwe_c, *in.lwe_c);
    }else{
        throw std::logic_error("Ciphertext type not supported!");
    }
}
  
void Ciphertext::sub(Ciphertext& out, const Ciphertext& in) const{
    if(is_lwe_ct){ 
        this->lwe_c->sub(*out.lwe_c, *in.lwe_c);
    }else{
        throw std::logic_error("Ciphertext type not supported!");
    }
}
  
void Ciphertext::mul(Ciphertext& out, const int64_t b) const{
    if(is_lwe_ct){ 
        this->lwe_c->mul(*out.lwe_c, b);
    }else{
       throw std::logic_error("Ciphertext type not supported!");
    }
} 
      
Ciphertext Ciphertext::operator+(int64_t b) const{
    if(is_lwe_ct){ 
        std::shared_ptr<LWECT> c(new LWECT(lwe_c->param));
        lwe_c->add(*c, encoding.encode_message(b)); 
        return Ciphertext(c, encoding, *context);
    }else{
        throw std::logic_error("Ciphertext type not supported!");
    }
}
 
Ciphertext Ciphertext::operator+(const Ciphertext& ct) const{ 
    if(is_lwe_ct){  
        std::shared_ptr<LWECT> c(new LWECT(lwe_c->param));
        lwe_c->add(*c, *ct.lwe_c);
        return Ciphertext(c, this->encoding, *context);
    }else{
        throw std::logic_error("Ciphertext type not supported!");
    }
}
 
Ciphertext Ciphertext::operator-(int64_t b) const{
    if(is_lwe_ct){ 
        std::shared_ptr<LWECT> c(new LWECT(lwe_c->param));
        lwe_c->sub(*c, this->encoding.encode_message(b));
        return Ciphertext(c, this->encoding, *context);
    }else{
        throw std::logic_error("Ciphertext type not supported!");
    }
}
 
Ciphertext Ciphertext::operator-(const Ciphertext& ct) const{
    if(is_lwe_ct){ 
        std::shared_ptr<LWECT> c(new LWECT(lwe_c->param));
        lwe_c->sub(*c, *ct.lwe_c);
        return Ciphertext(c, this->encoding, *context);
    }else{
        throw std::logic_error("Ciphertext type not supported!");
    }
}
 
Ciphertext Ciphertext::operator-() const{
    if(is_lwe_ct){ 
        std::shared_ptr<LWECT> c(new LWECT(lwe_c->param));
        lwe_c->neg(*c);
        return Ciphertext(c, this->encoding, *context);
    }else{
        throw std::logic_error("Ciphertext type not supported!");
    }
}
     
Ciphertext Ciphertext::operator*(int64_t b) const{
    if(is_lwe_ct){ 
        std::shared_ptr<LWECT> c(new LWECT(lwe_c->param));
        lwe_c->mul(*c, b);
        return Ciphertext(c, this->encoding, *context);
    }else{
        throw std::logic_error("Ciphertext type not supported!");
    }
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