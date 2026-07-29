#include "keyswitch/lwe_to_rgsw_keyswitch.h"

using namespace FHEDeck;


LWEToRGSWKeySwitchKey::LWEToRGSWKeySwitchKey(const LWESK& sk_origin, const RLWEGadgetSK& sk_dest)
    : lwe_to_rlwe_ks_key(sk_origin, sk_dest)
{
    /// Initiate the key switching key LWE to RLWE key switching key. 
    /// Initiate the RGSW ciphertext of its own secret key.
    ct_of_sk_dest = sk_dest.gadget_encrypt_sk();
    rlwe_param = sk_dest.param();
    gadget_param = sk_dest.gadget();
}
 

RLWEGadgetCT LWEToRGSWKeySwitchKey::lwe_to_rlwe_key_switch(const LWEGadgetCT& lwe_ct_in)
{ 

    std::vector<RLWECT> rlwe_ct_out;
    for(const auto& lwe_ct : lwe_ct_in.m_ct_content){
        RLWECT rlwe_ct(rlwe_param);
        lwe_to_rlwe_ks_key.lwe_to_rlwe_key_switch(rlwe_ct, lwe_ct);
        rlwe_ct_out.push_back(rlwe_ct);       
    }
    std::vector<RLWECT> rlwe_ct_out_sk;
    for(const auto& rlwe_ct : rlwe_ct_out){
        RLWECT rlwe_ct_sk(rlwe_param);
        ct_of_sk_dest.mul(rlwe_ct_sk, rlwe_ct);
        rlwe_ct_out_sk.push_back(rlwe_ct_sk);
    } 
    return RLWEGadgetCT(rlwe_param, gadget_param, rlwe_ct_out, rlwe_ct_out_sk);
}
