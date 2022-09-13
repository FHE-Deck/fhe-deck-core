 

#include "../include/lwe.h"
   
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
}

lwe_sk::lwe_sk(lwe_param lwe_par){
    this->lwe_par = lwe_par;  
    this->s = new long[lwe_par.n];
    if(lwe_par.key_d == binary){ 
        this->rand.binary_array(this->s, lwe_par.n); 
    }else{
        rand.ternary_array(this->s, lwe_par.n); 
    }
}


lwe_sk::lwe_sk(lwe_param lwe_par, long* key){
    this->lwe_par = lwe_par;  
    this->s = new long[lwe_par.n];
    for(int i = 0; i < lwe_par.n; ++i){
        this->s[i] = key[i];
    } 
}

 

lwe_param lwe_sk::get_lwe_param(){
    return lwe_par;
}


long* lwe_sk::encrypt(long m){
    long *ct = lwe_par.init_ct(); 
    lwe_sk::encrypt(ct, m);
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
    return utils::integer_mod_form(phase, lwe_par.Q);;
}


long lwe_sk::error(long *ct,  long m){   
    return utils::integer_signed_form((lwe_sk::phase(ct) - m) % lwe_par.Q, lwe_par.Q);;
}

long lwe_sk::decrypt(long *ct, int t){ 
    double d_phase = (double)lwe_sk::phase(ct); 
    long out = round(((double)t/lwe_par.Q) * d_phase);
    return utils::integer_signed_form(out % t, lwe_par.Q);
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



