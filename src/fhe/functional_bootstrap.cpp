#include "functional_bootstrap.h" 

using namespace fhe_deck;
   
void FunctionalBootstrapPublicKey::bootstrap(LWECT *lwe_ct_out, std::shared_ptr<VectorCTAccumulator> acc_in, LWECT *lwe_ct_in){      
    // 1) Key switch to \ZZ_Q^{n+1}    
    LWECT lwe_c(ms_from_keyswitch_to_par.from); 
    key_switch_key->lwe_to_lwe_key_switch(&lwe_c, lwe_ct_in);   
    // 2) Mod switch to \ZZ_2N^{n+1}  
    ms_from_keyswitch_to_par.switch_modulus(&lwe_c, &lwe_c); 
    // 3) Blind rotate    
    std::shared_ptr<BlindRotateOutput> br_out(blind_rotate_output_builder->build()); 
    blind_rotation_key->blind_rotate(br_out->accumulator, &lwe_c, acc_in);
    // 4) Sample Extract    
    br_out->extract_lwe(lwe_ct_out);   
    ms_from_extract_to_intermediate.switch_modulus(lwe_ct_out, lwe_ct_out);
}
 
std::vector<LWECT> FunctionalBootstrapPublicKey::bootstrap(std::vector<std::shared_ptr<VectorCTAccumulator>> acc_in_vec, LWECT *lwe_ct_in, PlaintextEncoding &encoding){   
    // 1) Key switch to \ZZ_Q^{n+1}  
    LWECT lwe_c(ms_from_keyswitch_to_par.from); 
    this->key_switch_key->lwe_to_lwe_key_switch(&lwe_c, lwe_ct_in);  
    // 2) Mod switch to \ZZ_2N^{n+1}  
    //this->ms_from_gadget_to_par.switch_modulus(lwe_c.ct, lwe_c.ct); 
    this->ms_from_keyswitch_to_par.switch_modulus(&lwe_c, &lwe_c); 
    // 3) Blind rotate      
    //this->acc_one = std::shared_ptr<VectorCTAccumulator>(accumulator_builder->get_acc_one(encoding)); 
    std::shared_ptr<VectorCTAccumulator> acc_one(accumulator_builder->get_acc_one(encoding)); 
    std::shared_ptr<BlindRotateOutput> br_out(blind_rotate_output_builder->build()); 
    this->blind_rotation_key->blind_rotate(br_out->accumulator, &lwe_c, acc_one); 
    // 4) Post Rotation
    LWECT lwe_ct_out(key_switch_key->origin);
    std::vector<LWECT> out_vec; 
    std::shared_ptr<BlindRotateOutput> br_temp(blind_rotate_output_builder->build()); 
    for(std::shared_ptr<VectorCTAccumulator> i:  acc_in_vec){      
        br_out->post_rotation(br_temp, i);   
        br_temp->extract_lwe(&lwe_ct_out); 
        ms_from_extract_to_intermediate.switch_modulus(&lwe_ct_out, &lwe_ct_out);
        out_vec.push_back(lwe_ct_out); 
    }  
    return out_vec;
}
  
 