 

#include "../include/lwe.h"
   

using namespace fhe_deck;
LWESK::~LWESK(){
    if(is_init){
        delete[] s;
    }
}


LWESK::LWESK(){}


LWESK::LWESK(int n, long Q,  double stddev, KeyDistribution key_d){
    //LWEParam lwe_par(n, Q, key_d, stddev);
    this->param = std::shared_ptr<LWEParam>(new LWEParam(n, Q, key_d, stddev));  
    this->s = new long[param->n];
    if(key_d == binary){ 
        this->rand.binary_array(this->s, param->n); 
    }else{
        rand.ternary_array(this->s, param->n); 
    }
    is_init = true;
}

LWESK::LWESK(std::shared_ptr<LWEParam> lwe_par){
    this->param = lwe_par;  
    this->s = new long[param->n];
    if(param->key_d == binary){ 
        this->rand.binary_array(this->s, param->n); 
    }else{
        rand.ternary_array(this->s, param->n); 
    }
    is_init = true;
}


LWESK::LWESK(std::shared_ptr<LWEParam> lwe_par, long* key){
    this->param = lwe_par;  
    this->s = new long[lwe_par->n];
    for(int i = 0; i < lwe_par->n; ++i){
        this->s[i] = key[i];
    } 
    is_init = true;
}


LWESK::LWESK(const LWESK &other){
    this->param = other.param;
     this->s = new long[param->n];
    for(int i = 0; i < param->n; ++i){
        this->s[i] = other.s[i];
    } 
    this->is_init = true;
    is_init = true;
}
 

LWESK& LWESK::operator=(const LWESK other){
    if (this == &other)
    {
        return *this;
    }
    if(this->is_init == false){
        this->param = other.param;
        this->s = new long[param->n];
        for(int i = 0; i < param->n; ++i){
            this->s[i] = other.s[i];
        } 
        this->is_init = true;
    }else if(this->is_init && param->n == other.param->n){
        for(int i = 0; i < param->n; ++i){
            this->s[i] = other.s[i];
        } 
    }else{
        throw std::logic_error("Wrong case in lwe_sk::operator=");
    } 
    return *this;
}
 
LWEParam LWESK::get_lwe_param(){
    return LWEParam(param->n, param->Q, param->key_d, param->stddev);
} 


long* LWESK::encrypt(long m){
    long *ct = param->init_ct(); 
    LWESK::encrypt(ct, m);
    return ct;
}

LWECT LWESK::encrypt_ct(long m){
    LWECT ct(param);
    encrypt(ct.ct, m);
    return ct;
}





void LWESK::encrypt(long *ct, long m){    
    ct[0] = (long)round(rand.gaussian(0, param->stddev)) + (long)m;  
    for(int i=1; i < param->n+1; ++i){   
        ct[i] = Utils::integer_mod_form(rand.uniform(param->Q), param->Q); 
        ct[0] -= s[i-1] * ct[i];
        ct[0] = Utils::integer_mod_form(ct[0] % param->Q, param->Q);
    }   
}


 long* LWESK::scale_and_encrypt(long m, int t){
    double scale = (double)param->Q/t;
    long m_scaled =  (long)round((double)m*scale); 
    return LWESK::encrypt(m_scaled);
 }
 
 void LWESK::scale_and_encrypt(long* ct, long m, int t){ 
    double scale = (double)param->Q/t;
    long m_scaled =  (long)round((double)m*scale); 
    encrypt(ct, m_scaled); 
} 



long LWESK::phase(long *ct){
    long phase  = ct[0]; 
    for(int i = 1; i < param->n+1; ++i){ 
        phase += ct[i] * s[i-1];
        phase = phase % param->Q; 
    }   
    return Utils::integer_mod_form(phase, param->Q);
}


long LWESK::error(long *ct,  long m){   
    return Utils::integer_signed_form((LWESK::phase(ct) - m) % param->Q, param->Q); 
}

long LWESK::decrypt(long *ct, int t){ 
    long d_phase = LWESK::phase(ct);  
    long out = round(((double)t/param->Q) * d_phase); 
    return Utils::integer_mod_form(out, t);
}
   
LWESK LWESK::modulus_switch(long new_modulus){
    LWEParam lwe_par = this->param->modulus_switch(new_modulus);
    LWESK lwe(std::shared_ptr<LWEParam>(new LWEParam(lwe_par.n, lwe_par.Q, lwe_par.key_d, lwe_par.stddev)), this->s);
    //LWESK lwe(lwe_par, this->s);
    return lwe;
}
 

LWEGadgetSK::LWEGadgetSK(){}


LWEGadgetSK::LWEGadgetSK(LWEGadgetParam lwe_g_par, LWESK lwe){
    this->lwe = lwe;
    this->gadget_param = lwe_g_par;
}

LWEGadgetSK::LWEGadgetSK(const LWEGadgetSK &other){
    this->gadget_param = other.gadget_param;
    this->lwe = other.lwe;
}


LWEGadgetSK& LWEGadgetSK::operator=(const LWEGadgetSK other){
    this->gadget_param = other.gadget_param;
    this->lwe = other.lwe;
    return *this;
}

long** LWEGadgetSK::gadget_encrypt(long m){ 
    long **gadget_ct = gadget_param.init_gadget_ct(); 
    gadget_encrypt(gadget_ct, m);
    return gadget_ct;
}

void LWEGadgetSK::gadget_encrypt(long** gadget_ct, long m){
    long temp_basis = 1; 
    gadget_ct[0] = lwe.encrypt(m);
    for(int i = 1; i < gadget_param.ell; ++i){
        temp_basis *= gadget_param.basis; 
        gadget_ct[i] = lwe.encrypt(m * temp_basis);
    } 
}



