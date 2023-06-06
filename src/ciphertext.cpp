#include "../include/ciphertext.h"


ciphertext::~ciphertext(){ 
    if(is_lwe_ct){
        delete this->lwe_c; 
    }
}
 
  
ciphertext::ciphertext(lwe_ct &lwe_c, plaintext_encoding encoding, fhe_context* context){
    this->lwe_c = new lwe_ct(lwe_c);
    this->is_lwe_ct = true; 
    this->is_init = true;
    this->encoding = encoding; 
    this->context = context; 
}

ciphertext::ciphertext(const ciphertext &other){ 
    this->encoding = other.encoding;
    if(other.is_lwe_ct){
        this->lwe_c = new lwe_ct(other.lwe_c);
        this->is_lwe_ct = true; 
        this->is_init = true;
        this->context = other.context;
    }else{
        throw 0;
    }
}
        
ciphertext& ciphertext::operator=(const ciphertext other){  
    if (this == &other)
    {
        return *this;
    }    
    if(!this->is_init && other.is_lwe_ct){  
        this->encoding = other.encoding;
        this->lwe_c  = new lwe_ct(other.lwe_c); 
        this->is_lwe_ct = true; 
        this->is_init = true;  
        this->context = other.context; 
        return *this;
    } else if(other.is_lwe_ct && this->is_lwe_ct){    
        this->encoding = other.encoding;
        this->lwe_c->lwe_par = other.lwe_c->lwe_par;
        for(int i = 0; i < this->lwe_c->lwe_par.n+1; ++i){
            this->lwe_c->ct[i] = other.lwe_c->ct[i];
        } 
    }else{ 
        throw 0;
    }  
    return *this;
}


ciphertext::ciphertext(ciphertext &other){
    this->encoding = other.encoding;
    if(other.is_lwe_ct){
        this->lwe_c = new lwe_ct(other.lwe_c);
        this->is_lwe_ct = true;
        this->is_init = true; 
        this->context = other.context;
    }else{
        throw 0;
    }
}

void ciphertext::add(ciphertext* ct){
    if(is_lwe_ct){
        this->lwe_c->add(ct->lwe_c);
    }else{
        throw 0;
    }
}
 

void ciphertext::sub(ciphertext* ct){
    if(is_lwe_ct){
        this->lwe_c->sub(ct->lwe_c);
    }else{
        throw 0;
    }
}
 

void ciphertext::mul(long b){
    if(is_lwe_ct){
        this->lwe_c->mul(b);
    }else{
        throw 0;
    }
} 
     



ciphertext ciphertext::operator+(long b){
    if(is_lwe_ct){
        lwe_ct c = this->lwe_c->operator+(this->encoding.encode_message(b));
        return ciphertext(c, this->encoding, this->context);
    }else{
        throw 0;
    }
}


ciphertext ciphertext::operator+(ciphertext ct){ 
    if(is_lwe_ct){ 
        lwe_ct c = this->lwe_c->operator+(ct.lwe_c);
        return ciphertext(c, this->encoding, this->context);
    }else{
        throw 0;
    }
}


ciphertext ciphertext::operator-(long b){
    if(is_lwe_ct){
        lwe_ct c = this->lwe_c->operator-(this->encoding.encode_message(b));
        return ciphertext(c, this->encoding, this->context);
    }else{
        throw 0;
    }
}


ciphertext ciphertext::operator-(ciphertext ct){
    if(is_lwe_ct){
        lwe_ct c = this->lwe_c->operator-(ct.lwe_c);
        return ciphertext(c, this->encoding, this->context);
    }else{
        throw 0;
    }
}


ciphertext ciphertext::operator-(){
    if(is_lwe_ct){
        lwe_ct c = this->lwe_c->operator-();
        return ciphertext(c, this->encoding, this->context);
    }else{
        throw 0;
    }
}
    

ciphertext ciphertext::operator*(long b){
    if(is_lwe_ct){
        lwe_ct c = this->lwe_c->operator*(b);
        return ciphertext(c, this->encoding, this->context);
    }else{
        throw 0;
    }
}


ciphertext operator+(long b, ciphertext ct){
    return ct.operator+(b); 
}

ciphertext operator-(long b, ciphertext ct){
    ciphertext out = -ct;
    return out - b;
}

ciphertext operator*(long b, ciphertext ct){ 
    return ct.operator*(b); 
}
 
