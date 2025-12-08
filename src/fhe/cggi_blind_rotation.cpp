#include "fhe/cggi_blind_rotation.h"

using namespace FHEDeck;
  
 

CGGIBlindRotationKey::CGGIBlindRotationKey(std::shared_ptr<GadgetVectorCTSK> gadget_sk, std::shared_ptr<LWESK> lwe_sk){ 
    this->lwe_par = lwe_sk->param();    
    m_vector_ct_param = gadget_sk->vector_ct_param(); 
    /// NOTE: The follwing code may be sensitive. Especially ext_s and the question of its removal from memory.
    std::shared_ptr<uint64_t[]> ext_s;
    ext_s = std::unique_ptr<uint64_t[]>(init_binary_extended_lwe_key(lwe_sk));  
    blind_rotation_key_gen(gadget_sk, ext_s);  
}
  
void CGGIBlindRotationKey::blind_rotate(VectorCT& out, const LWECT& lwe_ct_in, std::shared_ptr<VectorCTAccumulator> acc){     
    std::shared_ptr<VectorCT> next_acc = m_vector_ct_param->init_ct(m_vector_ct_param);  
    acc->content()->homomorphic_rotate(out, lwe_ct_in[0]);  
    for(int32_t i = 0; i < lwe_par->dim(); ++i){    
        out.homomorphic_rotate(*next_acc, lwe_ct_in[i+1]);   
        next_acc->sub(*next_acc, out);      
        m_bk[i]->mul(*next_acc, *next_acc);    
        next_acc->add(out, out); 
    }   
}
   
void CGGIBlindRotationKey::blind_rotation_key_gen(std::shared_ptr<GadgetVectorCTSK> rlwe_gadget_sk, std::shared_ptr<uint64_t[]> ext_s){
    std::vector<int64_t> msg(1);
    for(int32_t i = 0; i < lwe_par->dim(); ++i){    
        msg[0] = ext_s[i]; 
        m_bk.push_back(rlwe_gadget_sk->gadget_encrypt(msg));
    }      
}

uint64_t* CGGIBlindRotationKey::init_binary_extended_lwe_key(std::shared_ptr<LWESK> lwe_sk){ 
        uint64_t* ext_s = new uint64_t[lwe_par->dim()];
        for(int32_t i = 0; i < lwe_par->dim(); ++i){
            ext_s[i] = lwe_sk->m_key[i];
        } 
        return ext_s;
}

uint64_t* CGGIBlindRotationKey::init_ternary_extended_lwe_key(std::shared_ptr<LWESK> lwe_sk){ 
        uint64_t*  ext_s = new uint64_t[lwe_par->dim()];
        for(int32_t i = 0; i < lwe_par->dim(); ++i){
            ext_s[i] = lwe_sk->m_key[i];
        } 
        return ext_s;
}

 