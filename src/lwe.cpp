 

#include "../include/lwe.h"
   

lwe_sk::~lwe_sk(){
    if(is_init){
        delete[] s;
    }
}


lwe_sk::lwe_sk(){}


lwe_sk::lwe_sk(int n, long Q,  double stddev, key_dist key_d){
    lwe_param lwe_par(n, Q, key_d, stddev);
    this->lwe_par = lwe_par;  
    this->s = new long[lwe_par.n];
    if(key_d == binary){ 
        this->rand.binary_array(this->s, lwe_par.n); 
    }else{
        rand.ternary_array(this->s, lwe_par.n); 
    }
    is_init = true;
}

lwe_sk::lwe_sk(lwe_param lwe_par){
    this->lwe_par = lwe_par;  
    this->s = new long[lwe_par.n];
    if(lwe_par.key_d == binary){ 
        this->rand.binary_array(this->s, lwe_par.n); 
    }else{
        rand.ternary_array(this->s, lwe_par.n); 
    }
    is_init = true;
}


lwe_sk::lwe_sk(lwe_param lwe_par, long* key){
    this->lwe_par = lwe_par;  
    this->s = new long[lwe_par.n];
    for(int i = 0; i < lwe_par.n; ++i){
        this->s[i] = key[i];
    } 
    is_init = true;
}


lwe_sk::lwe_sk(const lwe_sk &other){
    this->lwe_par = other.lwe_par;
     this->s = new long[lwe_par.n];
    for(int i = 0; i < lwe_par.n; ++i){
        this->s[i] = other.s[i];
    } 
    this->is_init = true;
    is_init = true;
}
 

lwe_sk& lwe_sk::operator=(const lwe_sk other){
    if (this == &other)
    {
        return *this;
    }
    if(this->is_init == false){
        this->lwe_par = other.lwe_par;
        this->s = new long[lwe_par.n];
        for(int i = 0; i < lwe_par.n; ++i){
            this->s[i] = other.s[i];
        } 
        this->is_init = true;
    }else if(this->is_init && lwe_par.n == other.lwe_par.n){
        for(int i = 0; i < lwe_par.n; ++i){
            this->s[i] = other.s[i];
        } 
    }else{
        throw 0;
    } 
    return *this;
}

lwe_param lwe_sk::get_lwe_param(){
    return lwe_par;
}


long* lwe_sk::encrypt(long m){
    long *ct = lwe_par.init_ct(); 
    lwe_sk::encrypt(ct, m);
    return ct;
}

lwe_ct lwe_sk::encrypt_ct(long m){
    lwe_ct ct(lwe_par);
    encrypt(ct.ct, m);
    return ct;
}





void lwe_sk::encrypt(long *ct, long m){    
    ct[0] = (long)round(rand.gaussian(0, lwe_par.stddev)) + (long)m;  
    for(int i=1; i < lwe_par.n+1; ++i){   
        ct[i] = utils::integer_mod_form(rand.uniform(lwe_par.Q), lwe_par.Q); 
        ct[0] -= s[i-1] * ct[i];
        ct[0] = utils::integer_mod_form(ct[0] % lwe_par.Q, lwe_par.Q);
    }   
}


 long* lwe_sk::scale_and_encrypt(long m, int t){
    double scale = (double)lwe_par.Q/t;
    long m_scaled =  (long)round((double)m*scale); 
    return lwe_sk::encrypt(m_scaled);
 }
 
 void lwe_sk::scale_and_encrypt(long* ct, long m, int t){ 
    double scale = (double)lwe_par.Q/t;
    long m_scaled =  (long)round((double)m*scale); 
    encrypt(ct, m_scaled); 
} 



long lwe_sk::phase(long *ct){
    long phase  = ct[0]; 
    for(int i = 1; i < lwe_par.n+1; ++i){ 
        phase += ct[i] * s[i-1];
        phase = phase % lwe_par.Q; 
    }   
    return utils::integer_mod_form(phase, lwe_par.Q);
}


long lwe_sk::error(long *ct,  long m){   
    return utils::integer_signed_form((lwe_sk::phase(ct) - m) % lwe_par.Q, lwe_par.Q); 
}

long lwe_sk::decrypt(long *ct, int t){ 
    long d_phase = lwe_sk::phase(ct);  
    long out = round(((double)t/lwe_par.Q) * d_phase); 
    return utils::integer_mod_form(out, t);
}
   
lwe_sk lwe_sk::modulus_switch(long new_modulus){
    lwe_param lwe_par = this->lwe_par.modulus_switch(new_modulus);
    lwe_sk lwe(lwe_par, this->s);
    return lwe;
}
 

lwe_gadget_sk::lwe_gadget_sk(){}


lwe_gadget_sk::lwe_gadget_sk(lwe_gadget_param lwe_g_par, lwe_sk lwe){
    this->lwe = lwe;
    this->lwe_g_par = lwe_g_par;
}

lwe_gadget_sk::lwe_gadget_sk(const lwe_gadget_sk &other){
    this->lwe_g_par = other.lwe_g_par;
    this->lwe = other.lwe;
}


lwe_gadget_sk& lwe_gadget_sk::operator=(const lwe_gadget_sk other){
    this->lwe_g_par = other.lwe_g_par;
    this->lwe = other.lwe;
    return *this;
}

long** lwe_gadget_sk::gadget_encrypt(long m){ 
    long **gadget_ct = lwe_g_par.init_gadget_ct(); 
    gadget_encrypt(gadget_ct, m);
    return gadget_ct;
}

void lwe_gadget_sk::gadget_encrypt(long** gadget_ct, long m){
    long temp_basis = 1; 
    gadget_ct[0] = lwe.encrypt(m);
    for(int i = 1; i < lwe_g_par.ell; ++i){
        temp_basis *= lwe_g_par.basis; 
        gadget_ct[i] = lwe.encrypt(m * temp_basis);
    } 
}



