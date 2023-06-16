#include <iostream>

#include "lwe_param.h"
 
using namespace fhe_deck; 

LWEParam::LWEParam(int n, long Q, KeyDistribution key_d, double stddev){
    this->n = n;
    this->Q = Q;
    this->key_d = key_d;
    this->stddev = stddev;
}
 

LWEParam LWEParam::modulus_switch(long new_modulus){  
    double new_stddev = (new_modulus * this->stddev)/this->Q;
    if(new_stddev < 3.2){
        // TODO: This is a solrt of hack solution.
        // Actually we should choose it based on the key distribution, and the expected rounding error for the key distribution.
        // But to do this, perhaps the key_d parameter should be a more complex struct with hamming weight etc.  
        new_stddev = 3.2;
    } 
    LWEParam new_param(this->n, new_modulus, this->key_d, new_stddev); 
    return new_param;
}

long* LWEParam::init_ct(){ 
    long* ct = new long[this->n+1]; 
    for(int i = 0; i < n+1; ++i){
        ct[i] = 0;
    }
    return ct;
}
  
 
void LWEParam::scalar_mul(long *out, long *ct, long scalar){
    for(int i = 0; i <= n; ++i){
        out[i] = (ct[i] * scalar) % Q;
    }
}

void LWEParam::scalar_mul_lazy(long *out, long *ct, long scalar){
    for(int i = 0; i <= n; ++i){
        out[i] = (ct[i] * scalar);
    }
}

void LWEParam::add(long *out, long *ct_1, long *ct_2){
    for(int i = 0; i <= n; ++i){
        out[i] = (ct_1[i] + ct_2[i]) % Q;
    }
}

void LWEParam::add_lazy(long *out, long *ct_1, long *ct_2){
    for(int i = 0; i <= n; ++i){
        out[i] = (ct_1[i] + ct_2[i]);
    }
}


void LWEParam::switch_modulus(long *out_ct, long *in_ct, LWEParam &new_param){ 
    double temp; 
    for(int i = 0; i < n+1; ++i){
        temp =  new_param.Q *  in_ct[i];
        out_ct[i] = (long)round(temp/(double)Q); 
    }
}


void LWEParam::switch_modulus(long *out_ct, long *in_ct, std::shared_ptr<LWEParam> new_param){ 
    double temp; 
    for(int i = 0; i < n+1; ++i){
        temp =  new_param->Q *  in_ct[i];
        out_ct[i] = (long)round(temp/(double)Q); 
    }
}

/*
template <class Archive>
void lwe_param::serialize(Archive & ar ){ 
    ar(n, Q, key_d, stddev); 
}

*/


LWECT::LWECT(std::shared_ptr<LWEParam> lwe_param){
    this->param = lwe_param;
    this->ct = param->init_ct();
    this->init = true;
    
}

LWECT::LWECT(std::shared_ptr<LWEParam> lwe_param, long* ct){
    this->param = lwe_param;
    this->ct = param->init_ct();
    this->init = true;
    for(int i = 0; i < param->n+1; ++i){
        this->ct[i] = ct[i];
    }
}


LWECT::LWECT(const LWECT &c){  
    this->param = c.param;
    this->ct = param->init_ct();
    //this->pe = c.pe;
    for(int i = 0; i < param->n+1; ++i){
        this->ct[i] = c.ct[i];
    }
    this->init = true;
}




LWECT::LWECT(LWECT &c){  
    this->param = c.param;
    this->ct = param->init_ct(); 
    for(int i = 0; i < param->n+1; ++i){
        this->ct[i] = c.ct[i];
    }
    this->init = true;
}


LWECT::LWECT(LWECT *c){  
    this->param = c->param;
    this->ct = param->init_ct(); 
    for(int i = 0; i < param->n+1; ++i){
        this->ct[i] = c->ct[i];
    }
    this->init = true;
}
 


LWECT::~LWECT(){    
    delete[] ct;
}

void LWECT::scalar_mul(long scalar){
    for(int i = 0; i <= param->n; ++i){
        ct[i] = (ct[i] * scalar) % param->Q;
    }
}

void LWECT::mul(long scalar){
    for(int i = 0; i <= param->n; ++i){
        ct[i] = (ct[i] * scalar) % param->Q;
    }
}

void LWECT::scalar_mul_lazy(long scalar){
    for(int i = 0; i <= param->n; ++i){
        ct[i] = (ct[i] * scalar);
    }
}

void LWECT::add(LWECT *c){
    for(int i = 0; i <= param->n; ++i){
        this->ct[i] = (this->ct[i] + c->ct[i]) % param->Q;
    }
}

void LWECT::sub(LWECT *c){
    for(int i = 0; i <= param->n; ++i){
        this->ct[i] = Utils::integer_mod_form(this->ct[i] - c->ct[i], param->Q);
    }
}

void LWECT::add_lazy(LWECT *c){
    for(int i = 0; i <= param->n; ++i){
        this->ct[i] = this->ct[i] + c->ct[i] ;
    }
}
 

void LWECT::add(long b){ 
    this->ct[0] = (this->ct[0] + b) % this->param->Q;
}
 

void LWECT::sub(long b){
    this->ct[0] = Utils::integer_mod_form(this->ct[0] - b, param->Q);
}


LWECT& LWECT::operator=(const LWECT other){  
    if (this == &other)
    {
        return *this;
    }   
    if(init==false){
        this->param = other.param;
        this->ct = param->init_ct(); 
        for(int i = 0; i < param->n+1; ++i){
            this->ct[i] = other.ct[i];
        }
        this->init = true;
    }
    else if(init && (param->n == other.param->n)){ 
        param = other.param;
        for(int i = 0; i < param->n+1; ++i){
            ct[i] = other.ct[i];
        }
    }else{
        throw std::logic_error("Wrong case in lwe_ct::operator=");
    } 
    return *this;
} 

 
LWECT LWECT::operator+(long b){   
    LWECT ct_out(this);   
    ct_out.ct[0] = Utils::integer_mod_form(ct_out.ct[0] + b, param->Q);
    return ct_out; 
}
   

LWECT LWECT::operator+(LWECT b){  
    LWECT ct_out(this);  
    ct_out.add(&b); 
    return ct_out;
}
   

LWECT LWECT::operator+(LWECT *b){  
    LWECT ct_out(this);  
    ct_out.add(b); 
    return ct_out;
}


LWECT LWECT::operator-(long b){  
    LWECT ct_out(this);  
    ct_out.ct[0] = Utils::integer_mod_form(ct_out.ct[0] - b, param->Q); 
    return ct_out; 
}
    
LWECT LWECT::operator-(LWECT b){  
    LWECT ct_out(this);  
    ct_out.sub(&b); 
    return ct_out;
}

LWECT LWECT::operator-(LWECT *b){  
    LWECT ct_out(this);  
    ct_out.sub(b); 
    return ct_out;
}

LWECT LWECT::operator-(){  
    LWECT ct_out(this);  
    for(int i = 0; i < param->n+1; ++i){
        ct_out.ct[i] = Utils::integer_mod_form(-this->ct[i], param->Q);
    } 
    return ct_out;
}


LWECT LWECT::operator*(long b){
    LWECT ct_out = new LWECT(this);  
    ct_out.mul(b);
    return ct_out; 
}  

   
LWECT operator+(long b, LWECT ct){ 
    LWECT ct_out(&ct);  
    ct_out.ct[0] = Utils::integer_mod_form(ct_out.ct[0] +  b, ct_out.param->Q);
    return ct_out; 
}

LWECT operator-(long b, LWECT ct){
    LWECT temp = -ct;
    LWECT ct_out(&temp);
    ct_out.ct[0] = Utils::integer_mod_form(ct_out.ct[0] + b, ct_out.param->Q);
    return ct_out; 
}

LWECT operator*(long b, LWECT ct){
    LWECT ct_out(&ct);  
    ct_out.mul(b);
    return ct_out; 
}
 

 
LWEGadgetParam::LWEGadgetParam(std::shared_ptr<LWEParam> lwe_par, int basis){
      this->lwe_param = lwe_par;
      this->basis = basis; 
      // Note that for now, we accept only power of two basis (because our decomposition is written this way)
      this->k = 1;
      long temp = 2;
      while(temp < basis){
            temp *= 2;
            this->k++;
      }
      this->ell = 1;
      temp = basis;
       
      while(temp < this->lwe_param->Q){
            temp *= basis;
            this->ell++;
      }
}


long** LWEGadgetParam::init_gadget_ct(){
    long **gadget_ct = new long*[this->ell];
    for(int i = 0; i < this->ell; ++i){
        gadget_ct[i] = this->lwe_param->init_ct();
    } 
    return gadget_ct;
}



void LWEGadgetParam::gadget_mul(long *out_ct, long** gadget_ct, long scalar){
    for(int i = 0; i < lwe_param->n+1; ++i){
        out_ct[i] = 0;
    }
    long *scalar_decomposed = new long[ell]; 
    Utils::integer_decomp(scalar_decomposed, scalar, basis, k, ell);
    long *temp_ct = new long[lwe_param->n+1];
    for(int i = 0; i < ell; ++i){
        lwe_param->scalar_mul(temp_ct, gadget_ct[i], scalar_decomposed[i]);
        lwe_param->add(out_ct, out_ct, temp_ct);
    }
    delete[] scalar_decomposed;
    delete[] temp_ct;
}



void LWEGadgetParam::gadget_mul_lazy(long *out_ct, long** gadget_ct, long scalar){  
    for(int i = 0; i < lwe_param->n+1; ++i){
        out_ct[i] = 0;
    }
    long *scalar_decomposed = new long[ell]; 
    Utils::integer_decomp(scalar_decomposed, scalar, basis, k, ell);
    if(basis==2){
        for(int i = 0; i < ell; ++i){
            if(scalar_decomposed[i]==1){
                lwe_param->add_lazy(out_ct, out_ct, gadget_ct[i]);
            }
        }
    }else{
        long *temp_ct = new long[lwe_param->n+1];
        for(int i = 0; i < ell; ++i){
            lwe_param->scalar_mul_lazy(temp_ct, gadget_ct[i], scalar_decomposed[i]);
            lwe_param->add_lazy(out_ct, out_ct, temp_ct);
        } 
        delete[] temp_ct;
    } 
    // Modulus reduction only at the  end
    Utils::array_mod_form(out_ct, out_ct, lwe_param->n+1, lwe_param->Q); 
    delete[] scalar_decomposed;
}
