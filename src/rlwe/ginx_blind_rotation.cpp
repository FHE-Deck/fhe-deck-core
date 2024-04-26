#include "ginx_blind_rotation.h"

using namespace fhe_deck;
  

GINXBlindRotationKey::GINXBlindRotationKey(std::shared_ptr<GadgetVectorCTSK> gadget_sk, std::shared_ptr<LWESK> lwe_sk){ 
    this->lwe_par = lwe_sk->param;   
    this->next_acc = gadget_sk->vector_ct_param->init_ct();
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
    acc->acc->homomorphic_rotate(out, lwe_ct_in->ct[0]);  
    if(key_d==binary){      
        for(int i = 0; i < lwe_par->dim; ++i){    
            out->homomorphic_rotate(next_acc, lwe_ct_in->ct[i+1]);   
            next_acc->sub(next_acc, out);      
            bk[i]->mul(next_acc, next_acc);    
            next_acc->add(out, out); 
        }  
    } 
    else if(key_d==ternary){   
        // Rotatate back (multipliation by X^{-ct[i+1]}) and mul with bk_eval[i]
        long back_rotations;
         for(int i = 0; i < lwe_par->dim; ++i){  
            back_rotations = Utils::integer_mod_form(-lwe_ct_in->ct[i+1], lwe_par->modulus); 
            out->homomorphic_rotate(next_acc, back_rotations);
            next_acc->sub(next_acc, out);  
            bk[i]->mul(out, next_acc);
            // TODO: is this correct? Should be perhpa swith next ACC and not with out->acc
            next_acc->add(out, out);  
        } 
        // Rotatate forward (multipliation by X^{ct[i+1]}) and mul with bk_eval[lwe_par.n+i]
         for(int i = 0; i < lwe_par->dim; ++i){ 
            out->homomorphic_rotate(next_acc, back_rotations);
            next_acc->sub(next_acc, out);  
            bk[lwe_par->dim+i]->mul(out, next_acc);
            // TODO: is this correct? Should be perhpa swith next ACC and not with out->acc
            next_acc->add(out, out);   
        }
    }else{ 
        throw std::logic_error("GINXBlindRotationKey::blind_rotate: key_d not supported!");
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

 