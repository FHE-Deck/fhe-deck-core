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
        // TODO: This is a sort of hack solution.
        // Actually we should choose it based on the key distribution, and the expected rounding error for the key distribution.
        // But to do this, perhaps the key_d parameter should be a more complex struct with hamming weight etc.  
        // Note: that this is needed only when making an encryption w.r.t. the modullus switched LWE. Fortunately, it's not used in the high level ingterface so I leave it for later.
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
    // TODO: There is a bug here. If arithmetic is too big, then double will not be enough. Furthermore, the errors will actually be much higher then they should.
    double temp; 
    for(int i = 0; i < n+1; ++i){
        temp =  new_param.Q *  in_ct[i];
        out_ct[i] = (long)round(temp/(double)Q); 
    }
}


// Deprecated
void LWEParam::switch_modulus(long *out_ct, long *in_ct, std::shared_ptr<LWEParam> new_param){ 
    // TODO: There is a bug here. If arithmetic is too big, then double will not be enough. Furthermore, the errors will actually be much higher then they should. 
    double temp; 
    for(int i = 0; i < n+1; ++i){
        temp =  new_param->Q * in_ct[i];
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
 

LWEModSwitcher::LWEModSwitcher(std::shared_ptr<LWEParam> from, std::shared_ptr<LWEParam> to){
    this->from = from;
    this->to = to;

    // Check if we need long arithmetic
    int bits_from = Utils::number_of_bits(from->Q);
    int bits_to = Utils::number_of_bits(to->Q);
  
    if(from->n != to->n){
        throw std::logic_error("LWEModSwitcher::LWEModSwitcher: Dimension of the from and to LWE parametrs must the the same.");
    }
    ct_size = from->n+1;
    if(bits_from+bits_to <= 52){
        long_arithmetic = false;
        Q_from = from->Q;
        Q_to = to->Q; 
    }else if(bits_from+bits_to <= 112){
        long_arithmetic = true;
        long_Q_from = (long double)from->Q;
        long_Q_to = (long double)to->Q; 
    }else{
        throw std::logic_error("LWEModSwitcher::LWEModSwitcher: Too large moduli.");
    }
}


void LWEModSwitcher::switch_modulus(long *out_ct, long *in_ct){  
    if(long_arithmetic){
        for(int i = 0; i < ct_size; ++i){
            long_temp =  long_Q_to * (long double)in_ct[i];
            out_ct[i] = (long)roundl(long_temp/long_Q_from); 
        } 
    }else{
        for(int i = 0; i < ct_size; ++i){
            temp = Q_to *  (double)in_ct[i];
            out_ct[i] = (long)(temp/Q_from); 
        }
    }   
}




/*
long*** LWEToLWEKeySwitchKey::key_switching_key_gen(LWEGadgetSK *sk){ 
    // Initialize the key switching key
    long ***ksk = new long**[origin->n]; 
    for(int i = 0; i < origin->n; ++i){
        ksk[i] = new long*[destination.ell];
        for(int j = 0; j < destination.ell; ++j){ 
            ksk[i][j] = destination.lwe_param->init_ct();
        }
    } 
    for(int i = 0; i < rlwe_gadget.gadget_param.rlwe_param->N; ++i){  
        ksk[i] = sk.gadget_encrypt(-rlwe_gadget.sk.s[i]);  
    } 
    return ksk;
}



void LWEToLWEKeySwitchKey::set_key_switch_type(){ 
    long bits_Q = Utils::power_times(destination.lwe_param->Q, 2);
    long bits_base = Utils::power_times(destination.basis, 2);
    long bits_N = Utils::power_times(origin->n, 2); 
    destination.ell;
    long sum_lazy_bits = bits_Q + bits_base + destination.ell + bits_N;
    long sum_partial_lazy_bits = bits_Q + bits_base + destination.ell + 1;
    if(sum_lazy_bits < 64){
        std::cout << "rlwe_hom_acc_scheme: Using Lazy Key Switch" << std::endl;
        ks_type = lazy_key_switch;
    }else if(sum_partial_lazy_bits < 64){
        std::cout << "rlwe_hom_acc_scheme: Using Partial Lazy Key Switch" << std::endl;
        ks_type = partial_lazy_key_switch;
    }else{
        std::cout << "Using Standard Key Switch" << std::endl;
        ks_type = standard_key_switch;
    }
}


 
void LWEToLWEKeySwitchKey::lwe_to_lwe_key_switch_lazy(long *lwe_ct_out, long *lwe_ct_in){
    destination.gadget_mul_lazy(lwe_ct_out, ksk[0], lwe_ct_in[1]); 
    long *temp_lwe_ct = destination.lwe_param->init_ct(); 
    for(int i=2; i < origin->n+1; ++i){  
        destination.gadget_mul_lazy(temp_lwe_ct, ksk[i-1], lwe_ct_in[i]); 
        destination.lwe_param->add_lazy(lwe_ct_out, lwe_ct_out, temp_lwe_ct); 
    }  
    lwe_ct_out[0] = lwe_ct_in[0] + lwe_ct_out[0];
    Utils::array_mod_form(lwe_ct_out, lwe_ct_out, destination.lwe_param->n+1, destination.lwe_param->Q); 
    delete[] temp_lwe_ct;
}


void LWEToLWEKeySwitchKey::lwe_to_lwe_key_switch_partial_lazy(long *lwe_ct_out, long *lwe_ct_in){
    destination.gadget_mul_lazy(lwe_ct_out, ksk[0], lwe_ct_in[1]); 
    long *temp_lwe_ct = destination.lwe_param->init_ct(); 
    for(int i=2; i < origin->n+1; ++i){  
        destination.gadget_mul_lazy(temp_lwe_ct, ksk[i-1], lwe_ct_in[i]); 
        destination.lwe_param->add_lazy(lwe_ct_out, lwe_ct_out, temp_lwe_ct); 
        Utils::array_mod_form(lwe_ct_out, lwe_ct_out, destination.lwe_param->n+1, destination.lwe_param->Q);
    } 
    // Add the ``b'' term
    lwe_ct_out[0] = lwe_ct_in[0] + lwe_ct_out[0]; 
    Utils::array_mod_form(lwe_ct_out, lwe_ct_out, destination.lwe_param->n+1, destination.lwe_param->Q);
    delete[] temp_lwe_ct;
}

 
void LWEToLWEKeySwitchKey::lwe_to_lwe_key_switch(long *lwe_ct_out, long *lwe_ct_in){
    destination.gadget_mul(lwe_ct_out, ksk[0], lwe_ct_in[1]); 
    long *temp_lwe_ct = destination.lwe_param->init_ct(); 
    for(int i=2; i < origin->n+1; ++i){  
        destination.gadget_mul(temp_lwe_ct, ksk[i-1], lwe_ct_in[i]); 
        destination.lwe_param->add(lwe_ct_out, lwe_ct_out, temp_lwe_ct); 
    }  
    lwe_ct_out[0] = lwe_ct_in[0] + lwe_ct_out[0];
    Utils::array_mod_form(lwe_ct_out, lwe_ct_out, destination.lwe_param->n+1, destination.lwe_param->Q);
    delete[] temp_lwe_ct;
}

*/


   

 
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
    //Utils::array_mod_form(out_ct, out_ct, lwe_param->n+1, lwe_param->Q); 
    delete[] scalar_decomposed;
}
