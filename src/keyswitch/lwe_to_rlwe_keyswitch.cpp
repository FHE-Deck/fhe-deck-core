#include "keyswitch/lwe_to_rlwe_keyswitch.h"

using namespace FHEDeck;

LWEToRLWEKeySwitchKey::LWEToRLWEKeySwitchKey(std::shared_ptr<LWESK> sk_origin, std::shared_ptr<RLWEGadgetSK> sk_dest) {
    dest_param = sk_dest->rlwe_sk->param;
    init();
    key_switching_key_gen(sk_origin, sk_dest);
}

LWEToRLWEKeySwitchKey::LWEToRLWEKeySwitchKey(const LWEToRLWEKeySwitchKey &other){
    throw std::runtime_error("LWEToRLWEKeySwitchKey::LWEToRLWEKeySwitchKey(const LWEToRLWEKeySwitchKey &other)");
}

LWEToRLWEKeySwitchKey& LWEToRLWEKeySwitchKey::operator=(const LWEToRLWEKeySwitchKey other){
    throw std::runtime_error("LWEToRLWEKeySwitchKey& LWEToRLWEKeySwitchKey::operator=(const LWEToRLWEKeySwitchKey other)");
    return *this;
}

void LWEToRLWEKeySwitchKey::init(){
    degree_inv = Utils::mod_inv(dest_param->size, dest_param->coef_modulus); 
    bits_degree = Utils::number_of_bits(dest_param->size) - 1;
    mask_mod_degree_times_two = dest_param->size * 2 - 1;
    mask_mod_degree = dest_param->size - 1;  
}

void LWEToRLWEKeySwitchKey::key_switching_key_gen(std::shared_ptr<LWESK> sk_origin, std::shared_ptr<RLWEGadgetSK> sk_dest) { 
    /// TODO: Try to just copy the key here, instead of calling with size and modulus
    /// TODO: perhaps copying isn't needed at all? 
    Polynomial sk_origin_poly(sk_origin->key, sk_dest->rlwe_sk->sk_poly.size(), sk_dest->rlwe_sk->sk_poly.modulus()); 
    Polynomial sk_auto(sk_dest->rlwe_sk->sk_poly.size(), sk_dest->rlwe_sk->sk_poly.modulus());  
    for(int i = 2; i <= dest_param->size; i *= 2) {
        eval_auto_poly(sk_auto, sk_origin_poly, i+1); 
        ext_key_content.push_back(sk_dest->extended_encrypt(sk_auto)); 
    }
}
   
void LWEToRLWEKeySwitchKey::lwe_to_rlwe_key_switch(RLWECT& rlwe_ct_out, const LWECT& lwe_ct_in) { 
    rlwe_ct_out.b.zeroize(); 
    rlwe_ct_out.b[0] = lwe_ct_in.ct[0];   
 
    rlwe_ct_out.a[0] =  lwe_ct_in.ct[1];
    for(int i = 1; i < dest_param->size; ++i){
        rlwe_ct_out.a[dest_param->size - i] = dest_param->coef_modulus - lwe_ct_in.ct[i+1];
    } 

    rlwe_ct_out.mul(rlwe_ct_out, degree_inv); 
    RLWECT buf(dest_param);
    for(int i = bits_degree; i >= 1; i--) {
        eval_auto(buf, rlwe_ct_out, i);
        rlwe_ct_out.add(rlwe_ct_out, buf);
    }
}

void LWEToRLWEKeySwitchKey::eval_auto(RLWECT& rlwe_ct_out, const RLWECT& rlwe_ct_in, uint32_t log2_idx) {
    /// Then multiply the auto_a part with the automorphism 
    /// Add the authomorphism of b to the output. 
    //// Yep: (0, auto(b)) + Key(auto(s)) * auto(a) 
    int64_t idx = (1 << log2_idx);  
    Polynomial auto_a(rlwe_ct_in.a.size(), rlwe_ct_in.a.modulus()); 
    eval_auto_poly(auto_a, rlwe_ct_in.a, idx + 1); 
    ext_key_content[log2_idx - 1]->mul(rlwe_ct_out, auto_a);
    Polynomial auto_b(rlwe_ct_in.b.size(), rlwe_ct_in.b.modulus());
    eval_auto_poly(auto_b, rlwe_ct_in.b, idx + 1);
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
            perm = (i * idx) & mask_mod_degree_times_two;
            new_idx = perm & mask_mod_degree; 
            if(perm == new_idx){
                out_poly[new_idx] = in_poly[i];
            }else{ 
                out_poly[new_idx] = in_poly.modulus() - in_poly[i];
            }
        }
    }
} 