#include "ginx_blind_rotation.h"

using namespace fhe_deck;
  

GINXBlindRotationKey::~GINXBlindRotationKey(){  
    delete next_acc;  
}

GINXBlindRotationKey::GINXBlindRotationKey(std::shared_ptr<GadgetVectorCTSK> gadget_sk, std::shared_ptr<LWESK> lwe_sk){ 
    this->lwe_par = lwe_sk->param;   
    this->next_acc = gadget_sk->vector_ct_param->init_ct(gadget_sk->vector_ct_param);

    // The follwing code may be sensitive. Especially ext_s and the question of its removal from memory.
    std::shared_ptr<long[]> ext_s;
    this->key_d = lwe_sk->key_type; 
    if(this->key_d == binary){    
        ext_s = std::unique_ptr<long[]>(this->init_binary_extended_lwe_key(lwe_sk)); 
    }else if(this->key_d == ternary){   
        ext_s = std::unique_ptr<long[]>(this->init_ternary_extended_lwe_key(lwe_sk));
    }else{
        throw std::logic_error("GINXBlindRotationKey::GINXBlindRotationKey: Not supported LWE key distribution.");
    }    
    blind_rotation_key_gen(gadget_sk, ext_s);  
}
  
void GINXBlindRotationKey::blind_rotate(VectorCT* out, LWECT* lwe_ct_in, std::shared_ptr<VectorCTAccumulator> acc){    
    acc->acc_content->homomorphic_rotate(out, lwe_ct_in->ct[0]);     
    for(int i = 0; i < lwe_par->dim; ++i){    
        out->homomorphic_rotate(next_acc, lwe_ct_in->ct[i+1]);   
        next_acc->sub(next_acc, out);      
        bk[i]->mul(next_acc, next_acc);    
        next_acc->add(out, out); 
    }   
}
   
void GINXBlindRotationKey::blind_rotation_key_gen(std::shared_ptr<GadgetVectorCTSK> rlwe_gadget_sk, std::shared_ptr<long[]> ext_s){
    long* msg = new long[1];
    for(int i = 0; i < sizeof_ext_s; ++i){    
        msg[0] =  ext_s[i]; 
        bk.push_back(std::unique_ptr<GadgetVectorCT>(rlwe_gadget_sk->gadget_encrypt(msg, 1)));
    }      
}

long* GINXBlindRotationKey::init_binary_extended_lwe_key(std::shared_ptr<LWESK> lwe_sk){
        sizeof_ext_s = lwe_par->dim;
        long* ext_s = new long[sizeof_ext_s];
        for(int i = 0; i < lwe_par->dim; ++i){
            ext_s[i] = lwe_sk->key[i];
        } 
        return ext_s;
}

long* GINXBlindRotationKey::init_ternary_extended_lwe_key(std::shared_ptr<LWESK> lwe_sk){
        sizeof_ext_s = lwe_par->dim;
        long*  ext_s = new long[sizeof_ext_s];
        for(int i = 0; i < lwe_par->dim; ++i){
            ext_s[i] = lwe_sk->key[i];
        } 
        return ext_s;
}

 