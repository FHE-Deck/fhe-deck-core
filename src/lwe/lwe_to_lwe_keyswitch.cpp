#include <lwe_to_lwe_keyswitch.h>

using namespace fhe_deck;
  


LWEToLWEKeySwitchKey::~LWEToLWEKeySwitchKey(){ 
    for(int i = 0; i < origin->dim; ++i){ 
        for(int j = 0; j < destination.ell; ++j){ 
            delete[] ksk[i][j];
        }
        delete[] ksk[i];
    } 
    delete[] ksk;  
}



LWEToLWEKeySwitchKey::LWEToLWEKeySwitchKey(std::shared_ptr<LWESK> sk_origin, std::shared_ptr<LWEGadgetSK> sk_dest){
    origin = sk_origin->param;
    destination = sk_dest->gadget_param;
    set_key_switch_type();
    key_switching_key_gen(sk_origin, sk_dest);
}


LWEToLWEKeySwitchKey::LWEToLWEKeySwitchKey(const LWEToLWEKeySwitchKey &other){
    this->origin = other.origin;
    this->destination = other.destination;
    set_key_switch_type();
    this->ksk = new long**[origin->dim]; 
    for(int i = 0; i < origin->dim; ++i){
        this->ksk[i] = new long*[destination.ell];
        for(int j = 0; j < destination.ell; ++j){ 
            this->ksk[i][j] = destination.lwe_param->init_ct();
            for(int k = 0; k < destination.lwe_param->dim+1; ++k){
                this->ksk[i][j][k] = other.ksk[i][j][k];
            }
        }
    }  
}

   
LWEToLWEKeySwitchKey& LWEToLWEKeySwitchKey::operator=(const LWEToLWEKeySwitchKey other){
    this->origin = other.origin;
    this->destination = other.destination;
    set_key_switch_type();
    this->ksk = new long**[origin->dim]; 
    for(int i = 0; i < origin->dim; ++i){
        this->ksk[i] = new long*[destination.ell];
        for(int j = 0; j < destination.ell; ++j){ 
            this->ksk[i][j] = destination.lwe_param->init_ct();
            for(int k = 0; k < destination.lwe_param->dim+1; ++k){
                this->ksk[i][j][k] = other.ksk[i][j][k];
            }
        }
    }  
    return *this;
}

 
void LWEToLWEKeySwitchKey::key_switching_key_gen(std::shared_ptr<LWESK> sk_origin, std::shared_ptr<LWEGadgetSK> sk_dest){ 
 
    ksk = new long**[origin->dim]; 
    for(int i = 0; i < origin->dim; ++i){
        ksk[i] = new long*[destination.ell];
        for(int j = 0; j < destination.ell; ++j){ 
            ksk[i][j] = destination.lwe_param->init_ct();
        }
    }  
    for(int i = 0; i < origin->dim; ++i){   
        ksk[i] = sk_dest->gadget_encrypt(sk_origin->s[i]);  
    }  
}  



void LWEToLWEKeySwitchKey::set_key_switch_type(){ 
    long bits_Q = Utils::power_times(destination.lwe_param->modulus, 2);
    long bits_base = Utils::power_times(destination.base, 2);
    long bits_N = Utils::power_times(origin->dim, 2);  
    long sum_lazy_bits = bits_Q + bits_base + destination.ell + bits_N;
    long sum_partial_lazy_bits = bits_Q + bits_base + destination.ell + 1;
    if(sum_lazy_bits < 64){ 
        ks_type = lazy_key_switch;
    }else if(sum_partial_lazy_bits < 64){ 
        ks_type = partial_lazy_key_switch;
    }else{ 
        ks_type = standard_key_switch;
    }
}


 
void LWEToLWEKeySwitchKey::lwe_to_lwe_key_switch_lazy(long *lwe_ct_out, long *lwe_ct_in){
    destination.gadget_mul_lazy(lwe_ct_out, ksk[0], lwe_ct_in[1]); 
    long *temp_lwe_ct = destination.lwe_param->init_ct(); 
    for(int i=2; i < origin->dim+1; ++i){  
        destination.gadget_mul_lazy(temp_lwe_ct, ksk[i-1], lwe_ct_in[i]); 
        destination.lwe_param->add_lazy(lwe_ct_out, lwe_ct_out, temp_lwe_ct); 
    }  
    lwe_ct_out[0] = lwe_ct_in[0] + lwe_ct_out[0];
    Utils::array_mod_form(lwe_ct_out, lwe_ct_out, destination.lwe_param->dim+1, destination.lwe_param->modulus); 
    //lwe_ct_out->param = destination.lwe_param;
    delete[] temp_lwe_ct;
}


void LWEToLWEKeySwitchKey::lwe_to_lwe_key_switch_partial_lazy(long *lwe_ct_out, long *lwe_ct_in){
    destination.gadget_mul_lazy(lwe_ct_out, ksk[0], lwe_ct_in[1]); 
    long *temp_lwe_ct = destination.lwe_param->init_ct(); 
    for(int i=2; i < origin->dim+1; ++i){  
        destination.gadget_mul_lazy(temp_lwe_ct, ksk[i-1], lwe_ct_in[i]); 
        destination.lwe_param->add_lazy(lwe_ct_out, lwe_ct_out, temp_lwe_ct); 
        Utils::array_mod_form(lwe_ct_out, lwe_ct_out, destination.lwe_param->dim+1, destination.lwe_param->modulus);
    } 
    // Add the ``b'' term
    lwe_ct_out[0] = lwe_ct_in[0] + lwe_ct_out[0]; 
    Utils::array_mod_form(lwe_ct_out, lwe_ct_out, destination.lwe_param->dim+1, destination.lwe_param->modulus);
    //lwe_ct_out->param = destination.lwe_param;
    delete[] temp_lwe_ct;
}

 
void LWEToLWEKeySwitchKey::lwe_to_lwe_key_switch(long *lwe_ct_out, long *lwe_ct_in){
    destination.gadget_mul(lwe_ct_out, ksk[0], lwe_ct_in[1]); 
    long *temp_lwe_ct = destination.lwe_param->init_ct(); 
    for(int i=2; i < origin->dim+1; ++i){  
        destination.gadget_mul(temp_lwe_ct, ksk[i-1], lwe_ct_in[i]); 
        destination.lwe_param->add(lwe_ct_out, lwe_ct_out, temp_lwe_ct); 
    }  
    lwe_ct_out[0] = lwe_ct_in[0] + lwe_ct_out[0];
    Utils::array_mod_form(lwe_ct_out, lwe_ct_out, destination.lwe_param->dim+1, destination.lwe_param->modulus);
    //lwe_ct_out->param = destination.lwe_param;
    delete[] temp_lwe_ct;
}
 
