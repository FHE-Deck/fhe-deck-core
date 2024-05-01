#include <lwe_to_lwe_keyswitch.h>

using namespace fhe_deck;
    
 
LWEToLWEKeySwitchKey::LWEToLWEKeySwitchKey(std::shared_ptr<LWESK> sk_origin, std::shared_ptr<LWEGadgetSK> sk_dest){
    origin = sk_origin->param;
    destination = sk_dest->gadget_param;
    set_key_switch_type();
    key_switching_key_gen(sk_origin, sk_dest);
}
 
LWEToLWEKeySwitchKey::LWEToLWEKeySwitchKey(const LWEToLWEKeySwitchKey &other){
    throw std::runtime_error("LWEToLWEKeySwitchKey::LWEToLWEKeySwitchKey(const LWEToLWEKeySwitchKey &other)"); 
}
 
LWEToLWEKeySwitchKey& LWEToLWEKeySwitchKey::operator=(const LWEToLWEKeySwitchKey other){
    throw std::runtime_error("LWEToLWEKeySwitchKey& LWEToLWEKeySwitchKey::operator=(const LWEToLWEKeySwitchKey other)"); 
    return *this;
}
 
void LWEToLWEKeySwitchKey::key_switching_key_gen(std::shared_ptr<LWESK> sk_origin, std::shared_ptr<LWEGadgetSK> sk_dest){  
    key_content = std::shared_ptr<std::unique_ptr<LWEGadgetCT>[]>(new std::unique_ptr<LWEGadgetCT>[origin->dim]);
    for(int i = 0; i < origin->dim; ++i){   
        key_content[i] = std::unique_ptr<LWEGadgetCT>(sk_dest->gadget_encrypt(sk_origin->key[i]));  
    }  
} 
 
void LWEToLWEKeySwitchKey::set_key_switch_type(){ 
    long bits_Q = Utils::power_times(destination->lwe_param->modulus, 2);
    long bits_base = Utils::power_times(destination->base, 2);
    long bits_N = Utils::power_times(origin->dim, 2);  
    long sum_lazy_bits = bits_Q + bits_base + destination->ell + bits_N;
    long sum_partial_lazy_bits = bits_Q + bits_base + destination->ell + 1;
    if(sum_lazy_bits < 64){ 
        ks_type = lazy_key_switch;  
    }else if(sum_partial_lazy_bits < 64){ 
        ks_type = partial_lazy_key_switch; 
    }else{ 
        ks_type = standard_key_switch; 
    }
}
 
void LWEToLWEKeySwitchKey::lwe_to_lwe_key_switch(LWECT *lwe_ct_out, LWECT *lwe_ct_in){  
    if(this->ks_type == lazy_key_switch){
        lwe_to_lwe_key_switch_lazy(lwe_ct_out, lwe_ct_in);
    }else if(this->ks_type == partial_lazy_key_switch){
        lwe_to_lwe_key_switch_partial_lazy(lwe_ct_out, lwe_ct_in);
    } 
    lwe_to_lwe_key_switch_bussy(lwe_ct_out, lwe_ct_in);   
}
  
void LWEToLWEKeySwitchKey::lwe_to_lwe_key_switch_lazy(LWECT *lwe_ct_out, LWECT *lwe_ct_in){ 
    key_content[0]->gadget_mul_lazy(lwe_ct_out, lwe_ct_in->ct[1]); 
    LWECT temp_lwe_ct(destination->lwe_param);
    for(int i=2; i < origin->dim+1; ++i){  
        key_content[i-1]->gadget_mul_lazy(&temp_lwe_ct, lwe_ct_in->ct[i]); 
        destination->lwe_param->add_lazy(lwe_ct_out->ct, lwe_ct_out->ct, temp_lwe_ct.ct); 
    }  
    lwe_ct_out->ct[0] = lwe_ct_in->ct[0] + lwe_ct_out->ct[0];
    Utils::array_mod_form(lwe_ct_out->ct, lwe_ct_out->ct, destination->lwe_param->dim+1, destination->lwe_param->modulus);   
}
 
void LWEToLWEKeySwitchKey::lwe_to_lwe_key_switch_partial_lazy(LWECT *lwe_ct_out, LWECT *lwe_ct_in){ 
    key_content[0]->gadget_mul_lazy(lwe_ct_out, lwe_ct_in->ct[1]); 
    LWECT temp_lwe_ct(destination->lwe_param);  
    for(int i=2; i < origin->dim+1; ++i){   
        key_content[i-1]->gadget_mul_lazy(&temp_lwe_ct, lwe_ct_in->ct[i]); 
        destination->lwe_param->add_lazy(lwe_ct_out->ct, lwe_ct_out->ct, temp_lwe_ct.ct);  
        Utils::array_mod_form(lwe_ct_out->ct, lwe_ct_out->ct, destination->lwe_param->dim+1, destination->lwe_param->modulus); 
    }  
    // Add the ``b'' term
    lwe_ct_out->ct[0] = lwe_ct_in->ct[0] + lwe_ct_out->ct[0];  
    Utils::array_mod_form(lwe_ct_out->ct, lwe_ct_out->ct, destination->lwe_param->dim+1, destination->lwe_param->modulus);   
} 
 
void LWEToLWEKeySwitchKey::lwe_to_lwe_key_switch_bussy(LWECT *lwe_ct_out, LWECT *lwe_ct_in){ 
    key_content[0]->gadget_mul(lwe_ct_out, lwe_ct_in->ct[1]); 
    LWECT temp_lwe_ct(destination->lwe_param);
    for(int i=2; i < origin->dim+1; ++i){  
        key_content[i-1]->gadget_mul(&temp_lwe_ct, lwe_ct_in->ct[i]); 
        destination->lwe_param->add(lwe_ct_out->ct, lwe_ct_out->ct, temp_lwe_ct.ct); 
    }  
    lwe_ct_out->ct[0] = lwe_ct_in->ct[0] + lwe_ct_out->ct[0];
    Utils::array_mod_form(lwe_ct_out->ct, lwe_ct_out->ct, destination->lwe_param->dim+1, destination->lwe_param->modulus);  
}