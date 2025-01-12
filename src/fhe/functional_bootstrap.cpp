#include "fhe/functional_bootstrap.h" 

using namespace fhe_deck;
   
void FunctionalBootstrapPublicKey::bootstrap(LWECT& lwe_ct_out, std::shared_ptr<FunctionSpecification> acc_in, const LWECT& lwe_ct_in){      
    // 1) Key switch to \ZZ_Q^{n+1}    
    LWECT lwe_c(ms_from_keyswitch_to_par.from); 
    key_switch_key->lwe_to_lwe_key_switch(lwe_c, lwe_ct_in);   
    // 2) Mod switch to \ZZ_2N^{n+1}  
    ms_from_keyswitch_to_par.switch_modulus(lwe_c, lwe_c); 
    // 3) Blind rotate    
    std::shared_ptr<BlindRotateOutput> br_out(blind_rotate_output_builder->build()); 
    blind_rotation_key->blind_rotate(*br_out->accumulator, lwe_c, std::static_pointer_cast<VectorCTAccumulator>(acc_in));
    // 4) Sample Extract    
    br_out->extract_lwe(lwe_ct_out);   
    ms_from_extract_to_intermediate.switch_modulus(lwe_ct_out, lwe_ct_out);
}
 
std::vector<LWECT> FunctionalBootstrapPublicKey::bootstrap(std::vector<std::shared_ptr<FunctionSpecification>> acc_in_vec, const LWECT& lwe_ct_in, const PlaintextEncoding &output_encoding){   
    // 1) Key switch to \ZZ_Q^{n+1}  
    LWECT lwe_c(ms_from_keyswitch_to_par.from); 
    this->key_switch_key->lwe_to_lwe_key_switch(lwe_c, lwe_ct_in);  
    // 2) Mod switch to \ZZ_2N^{n+1}   
    this->ms_from_keyswitch_to_par.switch_modulus(lwe_c, lwe_c); 
    // 3) Blind rotate       
    std::shared_ptr<VectorCTAccumulator> acc_one(prepared_acc_builder->get_acc_one(output_encoding)); 
    std::shared_ptr<BlindRotateOutput> br_out(blind_rotate_output_builder->build()); 
    this->blind_rotation_key->blind_rotate(*br_out->accumulator, lwe_c, acc_one); 
    // 4) Post Rotation
    LWECT lwe_ct_out(key_switch_key->origin);
    std::vector<LWECT> out_vec; 
    std::shared_ptr<BlindRotateOutput> br_temp(blind_rotate_output_builder->build()); 
    for(std::shared_ptr<FunctionSpecification> spec:  acc_in_vec){      
        br_out->post_rotation(br_temp, spec);   
        br_temp->extract_lwe(lwe_ct_out); 
        ms_from_extract_to_intermediate.switch_modulus(lwe_ct_out, lwe_ct_out);
        out_vec.push_back(lwe_ct_out); 
    }  
    return out_vec;
}
  
 