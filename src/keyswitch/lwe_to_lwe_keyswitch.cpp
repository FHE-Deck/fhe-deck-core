#include "keyswitch/lwe_to_lwe_keyswitch.h"

using namespace FHEDeck;
     
LWEToLWEKeySwitchKey::LWEToLWEKeySwitchKey(std::shared_ptr<LWESK> sk_origin, std::shared_ptr<LWEGadgetSK> sk_dest){
    m_origin = sk_origin->param(); 
    m_destination = sk_dest->param(); 
    set_key_switch_type(sk_dest->base(), sk_dest->digits());
    key_switching_key_gen(sk_origin, sk_dest);
}
   
void LWEToLWEKeySwitchKey::key_switching_key_gen(std::shared_ptr<LWESK> sk_origin, std::shared_ptr<LWEGadgetSK> sk_dest){   
    m_key_content = std::unique_ptr<std::shared_ptr<LWEGadgetCT>[]>(new std::shared_ptr<LWEGadgetCT>[m_origin->dim()]); 
    for(int32_t i = 0; i < m_origin->dim(); ++i){      
        m_key_content[i] = sk_dest->gadget_encrypt(sk_origin->m_key[i]);  
    }   
} 
 
void LWEToLWEKeySwitchKey::set_key_switch_type(uint64_t base, int32_t digits){ 
    uint32_t bits_Q = Utils::power_times(m_destination->modulus(), 2);
    uint32_t bits_base = Utils::power_times(base, 2);
    uint32_t bits_N = Utils::power_times(m_origin->dim(), 2);  
    uint32_t sum_lazy_bits = bits_Q + bits_base + digits + bits_N;
    uint32_t sum_partial_lazy_bits = bits_Q + bits_base + digits + 1;
    if(sum_lazy_bits < 64){ 
    }else if(m_ks_type == KeySwitchType::partial_lazy_key_switch){
        m_ks_type = KeySwitchType::lazy_key_switch;  
    }else if(sum_partial_lazy_bits < 64){ 
        m_ks_type = KeySwitchType::partial_lazy_key_switch; 
    }else{ 
        m_ks_type = KeySwitchType::standard_key_switch; 
    }
}
 
void LWEToLWEKeySwitchKey::lwe_to_lwe_key_switch(LWECT& lwe_ct_out, const LWECT& lwe_ct_in){  
    if(m_ks_type == KeySwitchType::lazy_key_switch){
        lwe_to_lwe_key_switch_lazy(lwe_ct_out, lwe_ct_in);
    }else if(m_ks_type == KeySwitchType::partial_lazy_key_switch){
        lwe_to_lwe_key_switch_partial_lazy(lwe_ct_out, lwe_ct_in);
    } 
    lwe_to_lwe_key_switch_bussy(lwe_ct_out, lwe_ct_in);   
}
  
void LWEToLWEKeySwitchKey::lwe_to_lwe_key_switch_lazy(LWECT& lwe_ct_out, const LWECT& lwe_ct_in){ 
    m_key_content[0]->gadget_mul_lazy(lwe_ct_out, lwe_ct_in[1]); 
    LWECT temp_lwe_ct(m_destination);
    for(int32_t i=2; i < m_origin->dim()+1; ++i){  
        m_key_content[i-1]->gadget_mul_lazy(temp_lwe_ct, lwe_ct_in[i]);  
        lwe_ct_out.add_lazy(lwe_ct_out, temp_lwe_ct);
    }  
    lwe_ct_out[0] = lwe_ct_in[0] + lwe_ct_out[0];
    lwe_ct_out.ct_vec().normalize(); 
}
 
void LWEToLWEKeySwitchKey::lwe_to_lwe_key_switch_partial_lazy(LWECT& lwe_ct_out, const LWECT& lwe_ct_in){ 
    m_key_content[0]->gadget_mul_lazy(lwe_ct_out, lwe_ct_in[1]); 
    LWECT temp_lwe_ct(m_destination);  
    for(int32_t i=2; i < m_origin->dim()+1; ++i){   
        m_key_content[i-1]->gadget_mul_lazy(temp_lwe_ct, lwe_ct_in[i]);  
        lwe_ct_out.add(lwe_ct_out, temp_lwe_ct);
    }  
    // Add the ``b'' term
    lwe_ct_out[0] = lwe_ct_in[0] + lwe_ct_out[0]; 
    lwe_ct_out.ct_vec().normalize();  
} 
 
void LWEToLWEKeySwitchKey::lwe_to_lwe_key_switch_bussy(LWECT& lwe_ct_out, const LWECT& lwe_ct_in){ 
    m_key_content[0]->gadget_mul(lwe_ct_out, lwe_ct_in[1]); 
    LWECT temp_lwe_ct(m_destination);
    for(int32_t i=2; i < m_origin->dim()+1; ++i){  
        m_key_content[i-1]->gadget_mul(temp_lwe_ct, lwe_ct_in[i]);  
        lwe_ct_out.add(lwe_ct_out, temp_lwe_ct);
    }  
    lwe_ct_out[0] = lwe_ct_in[0] + lwe_ct_out[0];
    lwe_ct_out.ct_vec().normalize(); 
}

std::shared_ptr<LWEParam> LWEToLWEKeySwitchKey::origin()const{
    return m_origin;
}
    
std::shared_ptr<LWEParam>  LWEToLWEKeySwitchKey::destination()const{
    return m_destination;
}