#include "keyswitch/lwe_to_lwe_keyswitch.h"

using namespace FHEDeck;
     
LWEToLWEKeySwitchKey::LWEToLWEKeySwitchKey(std::shared_ptr<LWESK> sk_origin, std::shared_ptr<LWEGadgetSK> sk_dest){
    origin = sk_origin->param; 
    destination = sk_dest->lwe->param; 
    set_key_switch_type(sk_dest->base, sk_dest->digits);
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
    key_content = std::unique_ptr<std::shared_ptr<LWEGadgetCT>[]>(new std::shared_ptr<LWEGadgetCT>[origin->dim]); 
    for(int32_t i = 0; i < origin->dim; ++i){      
        key_content[i] = sk_dest->gadget_encrypt(sk_origin->key[i]);  
    }   
} 
 
void LWEToLWEKeySwitchKey::set_key_switch_type(uint64_t base, int32_t digits){ 
    uint32_t bits_Q = Utils::power_times(destination->modulus, 2);
    uint32_t bits_base = Utils::power_times(base, 2);
    uint32_t bits_N = Utils::power_times(origin->dim, 2);  
    uint32_t sum_lazy_bits = bits_Q + bits_base + digits + bits_N;
    uint32_t sum_partial_lazy_bits = bits_Q + bits_base + digits + 1;
    if(sum_lazy_bits < 64){ 
    }else if(this->ks_type == KeySwitchType::partial_lazy_key_switch){
        ks_type = KeySwitchType::lazy_key_switch;  
    }else if(sum_partial_lazy_bits < 64){ 
        ks_type = KeySwitchType::partial_lazy_key_switch; 
    }else{ 
        ks_type = KeySwitchType::standard_key_switch; 
    }
}
 
void LWEToLWEKeySwitchKey::lwe_to_lwe_key_switch(LWECT& lwe_ct_out, const LWECT& lwe_ct_in){  
    if(this->ks_type == KeySwitchType::lazy_key_switch){
        lwe_to_lwe_key_switch_lazy(lwe_ct_out, lwe_ct_in);
    }else if(this->ks_type == KeySwitchType::partial_lazy_key_switch){
        lwe_to_lwe_key_switch_partial_lazy(lwe_ct_out, lwe_ct_in);
    } 
    lwe_to_lwe_key_switch_bussy(lwe_ct_out, lwe_ct_in);   
}
  
void LWEToLWEKeySwitchKey::lwe_to_lwe_key_switch_lazy(LWECT& lwe_ct_out, const LWECT& lwe_ct_in){ 
    key_content[0]->gadget_mul_lazy(lwe_ct_out, lwe_ct_in.ct[1]); 
    LWECT temp_lwe_ct(destination);
    for(int32_t i=2; i < origin->dim+1; ++i){  
        key_content[i-1]->gadget_mul_lazy(temp_lwe_ct, lwe_ct_in.ct[i]);  
        lwe_ct_out.add_lazy(lwe_ct_out, temp_lwe_ct);
    }  
    lwe_ct_out.ct[0] = lwe_ct_in.ct[0] + lwe_ct_out.ct[0];
    lwe_ct_out.ct.normalize();
    //Utils::array_mod_form(lwe_ct_out.ct, lwe_ct_out.ct, destination->dim+1, destination->modulus);   
}
 
void LWEToLWEKeySwitchKey::lwe_to_lwe_key_switch_partial_lazy(LWECT& lwe_ct_out, const LWECT& lwe_ct_in){ 
    key_content[0]->gadget_mul_lazy(lwe_ct_out, lwe_ct_in.ct[1]); 
    LWECT temp_lwe_ct(destination);  
    for(int32_t i=2; i < origin->dim+1; ++i){   
        key_content[i-1]->gadget_mul_lazy(temp_lwe_ct, lwe_ct_in.ct[i]);  
        lwe_ct_out.add(lwe_ct_out, temp_lwe_ct);
    }  
    // Add the ``b'' term
    lwe_ct_out.ct[0] = lwe_ct_in.ct[0] + lwe_ct_out.ct[0]; 
    lwe_ct_out.ct.normalize(); 
    //Utils::array_mod_form(lwe_ct_out.ct, lwe_ct_out.ct, destination->dim+1, destination->modulus);   
} 
 
void LWEToLWEKeySwitchKey::lwe_to_lwe_key_switch_bussy(LWECT& lwe_ct_out, const LWECT& lwe_ct_in){ 
    key_content[0]->gadget_mul(lwe_ct_out, lwe_ct_in.ct[1]); 
    LWECT temp_lwe_ct(destination);
    for(int32_t i=2; i < origin->dim+1; ++i){  
        key_content[i-1]->gadget_mul(temp_lwe_ct, lwe_ct_in.ct[i]);  
        lwe_ct_out.add(lwe_ct_out, temp_lwe_ct);
    }  
    lwe_ct_out.ct[0] = lwe_ct_in.ct[0] + lwe_ct_out.ct[0];
    lwe_ct_out.ct.normalize();
    //Utils::array_mod_form(lwe_ct_out.ct, lwe_ct_out.ct, destination->dim+1, destination->modulus);  
}