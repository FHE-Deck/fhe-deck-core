#include "keyswitch/lwe_to_rlwe_keyswitch.h"

using namespace FHEDeck;

LWEToRLWEKeySwitchKey::LWEToRLWEKeySwitchKey(const LWESK& sk_origin, const RLWEGadgetSK& sk_dest) {
    m_dest_param = sk_dest.param();
    init();
    key_switching_key_gen(sk_origin, sk_dest);
}
 
void LWEToRLWEKeySwitchKey::init(){
    m_degree_inv = Utils::mod_inv(m_dest_param->size(), m_dest_param->modulus()); 
    m_bits_degree = Utils::number_of_bits(m_dest_param->size()) - 1;
    m_mask_mod_degree_times_two = m_dest_param->size() * 2 - 1;
    m_mask_mod_degree = m_dest_param->size() - 1;  
}

void LWEToRLWEKeySwitchKey::key_switching_key_gen(const LWESK& sk_origin, const RLWEGadgetSK& sk_dest) {  
    //Polynomial sk_origin_poly = sk_origin.m_key; 
    Polynomial sk_auto(m_dest_param->size(), m_dest_param->modulus());  
    for(int i = 2; i <= m_dest_param->size(); i *= 2) {
        eval_auto_poly(sk_auto, sk_origin.m_key, i+1); 
        m_ext_key_content.push_back(sk_dest.extended_encrypt(sk_auto)); 
    }
}
   
void LWEToRLWEKeySwitchKey::lwe_to_rlwe_key_switch(RLWECT& out, const LWECT& lwe_ct_in) {   
    Polynomial a(m_dest_param->size(), m_dest_param->modulus());
    Polynomial b(m_dest_param->size(), m_dest_param->modulus()); 
    b[0] = lwe_ct_in[0];    
    a[0] =  lwe_ct_in[1];
    for(int i = 1; i < m_dest_param->size(); ++i){
        a[m_dest_param->size() - i] = m_dest_param->modulus() - lwe_ct_in[i+1];
    } 
    RLWECT temp(m_dest_param, std::move(a), std::move(b));
    temp.mul(temp, m_degree_inv); 
    RLWECT buf(m_dest_param);
    for(int i = m_bits_degree; i >= 1; i--) {
        eval_auto(buf, temp, i);
        temp.add(temp, buf);
    }
    out = std::move(temp);
}

std::shared_ptr<RLWEParam> LWEToRLWEKeySwitchKey::dest_param()const{
    return m_dest_param;
}

void LWEToRLWEKeySwitchKey::eval_auto(RLWECT& rlwe_ct_out, const RLWECT& rlwe_ct_in, uint32_t log2_idx) {
    /// Then multiply the auto_a part with the automorphism 
    /// Add the authomorphism of b to the output. 
    //// Yep: (0, auto(b)) + Key(auto(s)) * auto(a) 
    int64_t idx = (1 << log2_idx);  

    Polynomial auto_a(m_dest_param->size(), m_dest_param->modulus()); 
    eval_auto_poly(auto_a, rlwe_ct_in.a(), idx + 1); 
    m_ext_key_content[log2_idx - 1]->mul(rlwe_ct_out, auto_a);
    Polynomial auto_b(m_dest_param->size(), m_dest_param->modulus());
    eval_auto_poly(auto_b, rlwe_ct_in.b(), idx + 1);
    rlwe_ct_out.add(rlwe_ct_out, auto_b);  
}

void LWEToRLWEKeySwitchKey::eval_auto_poly(FHEDeck::Polynomial& out_poly,
                                           const FHEDeck::Polynomial& in_poly, uint32_t idx) {
    // we know the degree is a power of 2 
    if (idx == out_poly.size() + 1) {
        // N + 1 automorphism just negates odd entries
        for(uint32_t i = 0; i < out_poly.size(); i+=2) {
            out_poly[i] = in_poly[i]; 
            out_poly[i+1] = in_poly.modulus() - in_poly[i+1];
        }
    } else { 
        uint32_t perm;
        uint32_t new_idx;
        for (uint32_t i = 0; i < out_poly.size(); i++) { 
            perm = (i * idx) & m_mask_mod_degree_times_two;
            new_idx = perm & m_mask_mod_degree; 
            if(perm == new_idx){
                out_poly[new_idx] = in_poly[i];
            }else{ 
                out_poly[new_idx] = in_poly.modulus() - in_poly[i];
            }
        }
    }
} 