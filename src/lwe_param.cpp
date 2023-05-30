#include "../include/lwe_param.h"
#include <iostream>
 
lwe_param::lwe_param(){}

lwe_param::lwe_param(int n, long Q, key_dist key_d, double stddev){
    this->n = n;
    this->Q = Q;
    this->key_d = key_d;
    this->stddev = stddev;
}
 

lwe_param lwe_param::modulus_switch(long new_modulus){  
    double new_stddev = (new_modulus * this->stddev)/this->Q;
    if(new_stddev < 3.2){
        // TODO: This is a solrt of hack solution.
        // Actually we should choose it based on the key distribution, and the expected rounding error for the key distribution.
        // But to do this, perhaps the key_d parameter should be a more complex struct with hamming weight etc.  
        new_stddev = 3.2;
    } 
    lwe_param new_param(this->n, new_modulus, this->key_d, new_stddev); 
    return new_param;
}

long* lwe_param::init_ct(){ 
    long* ct = new long[this->n+1]; 
    for(int i = 0; i < n+1; ++i){
        ct[i] = 0;
    }
    return ct;
}
  
 
void lwe_param::scalar_mul(long *out, long *ct, long scalar){
    for(int i = 0; i <= n; ++i){
        out[i] = (ct[i] * scalar) % Q;
    }
}

void lwe_param::scalar_mul_lazy(long *out, long *ct, long scalar){
    for(int i = 0; i <= n; ++i){
        out[i] = (ct[i] * scalar);
    }
}

void lwe_param::add(long *out, long *ct_1, long *ct_2){
    for(int i = 0; i <= n; ++i){
        out[i] = (ct_1[i] + ct_2[i]) % Q;
    }
}

void lwe_param::add_lazy(long *out, long *ct_1, long *ct_2){
    for(int i = 0; i <= n; ++i){
        out[i] = (ct_1[i] + ct_2[i]);
    }
}



void lwe_param::switch_modulus(long *out_ct, long *in_ct, lwe_param &new_param){ 
    double temp; 
    for(int i = 0; i < n+1; ++i){
        temp =  new_param.Q *  in_ct[i];
        out_ct[i] = (long)round(temp/(double)Q); 
    }
}

/*
template <class Archive>
void lwe_param::serialize(Archive & ar ){ 
    ar(n, Q, key_d, stddev); 
}

*/


lwe_ct::lwe_ct(lwe_param lwe_param){
    this->lwe_par = lwe_param;
    this->ct = lwe_par.init_ct();
    this->init = true;
    
}

lwe_ct::lwe_ct(lwe_param lwe_param, long* ct){
    this->lwe_par = lwe_param;
    this->ct = lwe_par.init_ct();
    this->init = true;
    for(int i = 0; i < lwe_par.n+1; ++i){
        this->ct[i] = ct[i];
    }
}


lwe_ct::lwe_ct(const lwe_ct &c){  
    this->lwe_par = c.lwe_par;
    this->ct = lwe_par.init_ct();
    //this->pe = c.pe;
    for(int i = 0; i < lwe_par.n+1; ++i){
        this->ct[i] = c.ct[i];
    }
    this->init = true;
}




lwe_ct::lwe_ct(lwe_ct &c){  
    this->lwe_par = c.lwe_par;
    this->ct = lwe_par.init_ct();
    //this->pe = c.pe;
    for(int i = 0; i < lwe_par.n+1; ++i){
        this->ct[i] = c.ct[i];
    }
    this->init = true;
}


lwe_ct::lwe_ct(lwe_ct *c){  
    this->lwe_par = c->lwe_par;
    this->ct = lwe_par.init_ct();
    //this->pe = c.pe;
    for(int i = 0; i < lwe_par.n+1; ++i){
        this->ct[i] = c->ct[i];
    }
    this->init = true;
}
 


lwe_ct::~lwe_ct(){    
    delete[] ct;
}

void lwe_ct::scalar_mul(long scalar){
    for(int i = 0; i <= lwe_par.n; ++i){
        ct[i] = (ct[i] * scalar) % lwe_par.Q;
    }
}

void lwe_ct::mul(long scalar){
    for(int i = 0; i <= lwe_par.n; ++i){
        ct[i] = (ct[i] * scalar) % lwe_par.Q;
    }
}

void lwe_ct::scalar_mul_lazy(long scalar){
    for(int i = 0; i <= lwe_par.n; ++i){
        ct[i] = (ct[i] * scalar);
    }
}

void lwe_ct::add(lwe_ct *c){
    for(int i = 0; i <= lwe_par.n; ++i){
        this->ct[i] = (this->ct[i] + c->ct[i]) % lwe_par.Q;
    }
}

void lwe_ct::sub(lwe_ct *c){
    for(int i = 0; i <= lwe_par.n; ++i){
        this->ct[i] = utils::integer_mod_form(this->ct[i] - c->ct[i], lwe_par.Q);
    }
}

void lwe_ct::add_lazy(lwe_ct *c){
    for(int i = 0; i <= lwe_par.n; ++i){
        this->ct[i] = this->ct[i] + c->ct[i] ;
    }
}

/*
void lwe_ct::add(ciphertext* b){
    //lwe_ct* ct_cast = dynamic_cast<lwe_ct*>(b);
    lwe_ct ct_cast(b);
    add(&ct_cast);
}
*/


void lwe_ct::add(long b){ 
    this->ct[0] = (this->ct[0] + b) % this->lwe_par.Q;
}

/*
void lwe_ct::sub(ciphertext* b){
    //lwe_ct* ct_cast = dynamic_cast<lwe_ct*>(b);
    lwe_ct ct_cast(b);
    sub(&ct_cast);
}
*/

void lwe_ct::sub(long b){
    this->ct[0] = utils::integer_mod_form(this->ct[0] - b, lwe_par.Q);
}


lwe_ct& lwe_ct::operator=(const lwe_ct other){  
    if (this == &other)
    {
        return *this;
    }   
    if(init && (lwe_par.n == other.lwe_par.n)){ 
        lwe_par = other.lwe_par;
        for(int i = 0; i < lwe_par.n+1; ++i){
            ct[i] = other.ct[i];
        }
    }else{
        throw 0;
    } 
    return *this;
} 

 
lwe_ct lwe_ct::operator+(long b){   
    lwe_ct ct_out(this);   
    ct_out.ct[0] = utils::integer_mod_form(ct_out.ct[0] + b, lwe_par.Q);
    return ct_out; 
}
   

lwe_ct lwe_ct::operator+(lwe_ct b){  
    lwe_ct ct_out(this);  
    ct_out.add(&b); 
    return ct_out;
}
   

lwe_ct lwe_ct::operator+(lwe_ct *b){  
    lwe_ct ct_out(this);  
    ct_out.add(b); 
    return ct_out;
}


lwe_ct lwe_ct::operator-(long b){  
    lwe_ct ct_out(this);  
    ct_out.ct[0] = utils::integer_mod_form(ct_out.ct[0] - b, lwe_par.Q); 
    return ct_out; 
}
    
lwe_ct lwe_ct::operator-(lwe_ct b){  
    lwe_ct ct_out(this);  
    ct_out.sub(&b); 
    return ct_out;
}

lwe_ct lwe_ct::operator-(lwe_ct *b){  
    lwe_ct ct_out(this);  
    ct_out.sub(b); 
    return ct_out;
}

lwe_ct lwe_ct::operator-(){  
    lwe_ct ct_out(this);  
    for(int i = 0; i < lwe_par.n+1; ++i){
        ct_out.ct[i] = utils::integer_mod_form(-this->ct[i], lwe_par.Q);
    } 
    return ct_out;
}


lwe_ct lwe_ct::operator*(long b){
    lwe_ct ct_out = new lwe_ct(this);  
    ct_out.mul(b);
    return ct_out; 
}  

   
lwe_ct operator+(long b, lwe_ct ct){ 
    lwe_ct ct_out(&ct);  
    ct_out.ct[0] = utils::integer_mod_form(ct_out.ct[0] +  b, ct_out.lwe_par.Q);
    return ct_out; 
}

lwe_ct operator-(long b, lwe_ct ct){
    lwe_ct temp = -ct;
    lwe_ct ct_out(&temp);
    ct_out.ct[0] = utils::integer_mod_form(ct_out.ct[0] + b, ct_out.lwe_par.Q);
    return ct_out; 
}

lwe_ct operator*(long b, lwe_ct ct){
    lwe_ct ct_out(&ct);  
    ct_out.mul(b);
    return ct_out; 
}
 



 lwe_gadget_param::lwe_gadget_param(){}

lwe_gadget_param::lwe_gadget_param(lwe_param lwe_par, int basis){
      this->lwe_par = lwe_par;
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
       
      while(temp < this->lwe_par.Q){
            temp *= basis;
            this->ell++;
      }
}


long** lwe_gadget_param::init_gadget_ct(){
    long **gadget_ct = new long*[this->ell];
    for(int i = 0; i < this->ell; ++i){
        gadget_ct[i] = this->lwe_par.init_ct();
    } 
    return gadget_ct;
}



void lwe_gadget_param::gadget_mul(long *out_ct, long** gadget_ct, long scalar){
    for(int i = 0; i < lwe_par.n+1; ++i){
        out_ct[i] = 0;
    }
    long *scalar_decomposed = new long[ell]; 
    utils::integer_decomp(scalar_decomposed, scalar, basis, k, ell);
    long *temp_ct = new long[lwe_par.n+1];
    for(int i = 0; i < ell; ++i){
        lwe_par.scalar_mul(temp_ct, gadget_ct[i], scalar_decomposed[i]);
        lwe_par.add(out_ct, out_ct, temp_ct);
    }
    delete[] scalar_decomposed;
    delete[] temp_ct;
}



void lwe_gadget_param::gadget_mul_lazy(long *out_ct, long** gadget_ct, long scalar){  
    for(int i = 0; i < lwe_par.n+1; ++i){
        out_ct[i] = 0;
    }
    long *scalar_decomposed = new long[ell]; 
    utils::integer_decomp(scalar_decomposed, scalar, basis, k, ell);
    if(basis==2){
        for(int i = 0; i < ell; ++i){
            if(scalar_decomposed[i]==1){
                lwe_par.add_lazy(out_ct, out_ct, gadget_ct[i]);
            }
        }
    }else{
        long *temp_ct = new long[lwe_par.n+1];
        for(int i = 0; i < ell; ++i){
            lwe_par.scalar_mul_lazy(temp_ct, gadget_ct[i], scalar_decomposed[i]);
            lwe_par.add_lazy(out_ct, out_ct, temp_ct);
        } 
        delete[] temp_ct;
    } 
    // Modulus reduction only at the  end
    utils::array_mod_form(out_ct, out_ct, lwe_par.n+1, lwe_par.Q); 
    delete[] scalar_decomposed;
}
