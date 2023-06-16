#include "ciphertext.h"

using namespace fhe_deck;

Ciphertext::~Ciphertext(){ 
    if(is_lwe_ct){
        delete this->lwe_c; 
    }
}
 
  
Ciphertext::Ciphertext(LWECT &lwe_c, PlaintextEncoding encoding, FHEContext* context){
    this->lwe_c = new LWECT(lwe_c);
    this->is_lwe_ct = true; 
    this->is_init = true;
    this->encoding = encoding; 
    this->context = context; 
}

Ciphertext::Ciphertext(const Ciphertext &other){ 
    this->encoding = other.encoding;
    if(other.is_lwe_ct){
        this->lwe_c = new LWECT(other.lwe_c);
        this->is_lwe_ct = true; 
        this->is_init = true;
        this->context = other.context;
    }else{
        throw std::logic_error("Ciphertext type not supported!");
    }
}
        
Ciphertext& Ciphertext::operator=(const Ciphertext other){  
    if (this == &other)
    {
        return *this;
    }    
    if(!this->is_init && other.is_lwe_ct){  
        this->encoding = other.encoding;
        this->lwe_c  = new LWECT(other.lwe_c); 
        this->is_lwe_ct = true; 
        this->is_init = true;  
        this->context = other.context; 
        return *this;
    } else if(other.is_lwe_ct && this->is_lwe_ct){    
        this->encoding = other.encoding;
        this->lwe_c->param = other.lwe_c->param;
        for(int i = 0; i < this->lwe_c->param->n+1; ++i){
            this->lwe_c->ct[i] = other.lwe_c->ct[i];
        } 
    }else{ 
        throw std::logic_error("Most likely wrong Ciphertext type!");
    }  
    return *this;
}


Ciphertext::Ciphertext(Ciphertext &other){
    this->encoding = other.encoding;
    if(other.is_lwe_ct){
        this->lwe_c = new LWECT(other.lwe_c);
        this->is_lwe_ct = true;
        this->is_init = true; 
        this->context = other.context;
    }else{
        throw std::logic_error("Ciphertext type not supported!");
    }
}

void Ciphertext::add(Ciphertext* ct){
    if(is_lwe_ct){
        this->lwe_c->add(ct->lwe_c);
    }else{
        throw std::logic_error("Ciphertext type not supported!");
    }
}
 

void Ciphertext::sub(Ciphertext* ct){
    if(is_lwe_ct){
        this->lwe_c->sub(ct->lwe_c);
    }else{
        throw std::logic_error("Ciphertext type not supported!");
    }
}
 

void Ciphertext::mul(long b){
    if(is_lwe_ct){
        this->lwe_c->mul(b);
    }else{
       throw std::logic_error("Ciphertext type not supported!");
    }
} 
     



Ciphertext Ciphertext::operator+(long b){
    if(is_lwe_ct){
        LWECT c = this->lwe_c->operator+(this->encoding.encode_message(b));
        return Ciphertext(c, this->encoding, this->context);
    }else{
        throw std::logic_error("Ciphertext type not supported!");
    }
}


Ciphertext Ciphertext::operator+(Ciphertext ct){ 
    if(is_lwe_ct){ 
        LWECT c = this->lwe_c->operator+(ct.lwe_c);
        return Ciphertext(c, this->encoding, this->context);
    }else{
        throw std::logic_error("Ciphertext type not supported!");
    }
}


Ciphertext Ciphertext::operator-(long b){
    if(is_lwe_ct){
        LWECT c = this->lwe_c->operator-(this->encoding.encode_message(b));
        return Ciphertext(c, this->encoding, this->context);
    }else{
        throw std::logic_error("Ciphertext type not supported!");
    }
}


Ciphertext Ciphertext::operator-(Ciphertext ct){
    if(is_lwe_ct){
        LWECT c = this->lwe_c->operator-(ct.lwe_c);
        return Ciphertext(c, this->encoding, this->context);
    }else{
        throw std::logic_error("Ciphertext type not supported!");
    }
}


Ciphertext Ciphertext::operator-(){
    if(is_lwe_ct){
        LWECT c = this->lwe_c->operator-();
        return Ciphertext(c, this->encoding, this->context);
    }else{
        throw std::logic_error("Ciphertext type not supported!");
    }
}
    

Ciphertext Ciphertext::operator*(long b){
    if(is_lwe_ct){
        LWECT c = this->lwe_c->operator*(b);
        return Ciphertext(c, this->encoding, this->context);
    }else{
        throw std::logic_error("Ciphertext type not supported!");
    }
}


Ciphertext operator+(long b, Ciphertext ct){
    return ct.operator+(b); 
}

Ciphertext operator-(long b, Ciphertext ct){
    Ciphertext out = -ct;
    return out - b;
}

Ciphertext operator*(long b, Ciphertext ct){ 
    return ct.operator*(b); 
}
 
