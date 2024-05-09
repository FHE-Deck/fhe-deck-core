#include "functional_bootstrap.h"

using namespace fhe_deck;
   
void FunctionalBootstrapPublicKey::bootstrap(LWECT *lwe_ct_out, std::shared_ptr<VectorCTAccumulator> acc_in, LWECT *lwe_ct_in){      
    // 1) Key switch to \ZZ_Q^{n+1}    
    LWECT lwe_c(ms_from_gadget_to_par.from); 
    key_switch_key->lwe_to_lwe_key_switch(&lwe_c, lwe_ct_in);  
 
    // 2) Mod switch to \ZZ_2N^{n+1}  
    ms_from_gadget_to_par.switch_modulus(lwe_c.ct, lwe_c.ct);
  
    // 3) Blind rotate    
    blind_rotation_key->blind_rotate(br_out->accumulator, &lwe_c, acc_in);
    // 4) Sample Extract    
    br_out->extract_lwe(lwe_ct_out);   
}
 
std::vector<LWECT> FunctionalBootstrapPublicKey::bootstrap(std::vector<std::shared_ptr<VectorCTAccumulator>> acc_in_vec, LWECT *lwe_ct_in, PlaintextEncoding &encoding){   
    // 1) Key switch to \ZZ_Q^{n+1}  
    LWECT lwe_c(ms_from_gadget_to_par.from); 
    this->key_switch_key->lwe_to_lwe_key_switch(&lwe_c, lwe_ct_in);  
    // 2) Mod switch to \ZZ_2N^{n+1}  
    this->ms_from_gadget_to_par.switch_modulus(lwe_c.ct, lwe_c.ct); 
    // 3) Blind rotate      
    this->acc_one = std::shared_ptr<VectorCTAccumulator>(accumulator_builder->get_acc_one(encoding)); 
    this->blind_rotation_key->blind_rotate(br_out->accumulator, &lwe_c, acc_one); 
    // 4) Post Rotation
    LWECT lwe_ct_out(key_switch_key->origin);
    std::vector<LWECT> out_vec; 
    for(std::shared_ptr<VectorCTAccumulator> i:  acc_in_vec){      
        br_out->post_rotation(br_temp, i);   
        br_temp->extract_lwe(&lwe_ct_out); 
        out_vec.push_back(lwe_ct_out); 
    }  
    return out_vec;
}
  
LMPFunctionalBootstrapPublicKey::LMPFunctionalBootstrapPublicKey(
        std::shared_ptr<LWEParam> lwe_par, 
        std::shared_ptr<LWEParam> lwe_par_tiny, 
        BlindRotationPublicKey *blind_rotation_key, 
        LWEToLWEKeySwitchKey *key_switch_key,  
        std::shared_ptr<BlindRotateOutputBuilder> blind_rotate_output_builder,
        std::shared_ptr<AbstractAccumulatorBuilder> accumulator_builder){ 
    this->is_full_domain_bootstrap_function_amortizable = true;
    this->blind_rotation_key = std::shared_ptr<BlindRotationPublicKey>(blind_rotation_key);
    this->key_switch_key = std::shared_ptr<LWEToLWEKeySwitchKey>(key_switch_key);
    this->accumulator_builder = accumulator_builder;
    this->lwe_par = lwe_par; 
    this->lwe_par_tiny = lwe_par_tiny;
 
    // Initialize BlindRotateOutputs  
    this->br_out = std::shared_ptr<BlindRotateOutput>(blind_rotate_output_builder->build()); 
    this->br_temp = std::shared_ptr<BlindRotateOutput>(blind_rotate_output_builder->build());
    // Special Accumulator for the full domain functional bootstrapping, computing the most signifficant bit. 
    this->acc_msb = std::shared_ptr<VectorCTAccumulator>(this->accumulator_builder->get_acc_msb());   
    // Mod Switch from Extracted Q to 2 * N 
    this->ms_from_gadget_to_par = LWEModSwitcher(this->key_switch_key->destination, this->lwe_par);
    // Mod Switch from Extracted Q to N 
    this->ms_from_gadget_to_tiny_par = LWEModSwitcher(this->key_switch_key->destination, this->lwe_par_tiny);
}
  
void LMPFunctionalBootstrapPublicKey::full_domain_bootstrap(LWECT *lwe_ct_out, std::shared_ptr<VectorCTAccumulator> acc_in, LWECT *lwe_ct_in, PlaintextEncoding &encoding){    
    // 1) Key switch to \ZZ_Q^{n+1}   
    LWECT lwe_c_N(ms_from_gadget_to_par.from); 
    LWECT lwe_c(ms_from_gadget_to_par.from); 
    key_switch_key->lwe_to_lwe_key_switch(&lwe_c_N, lwe_ct_in);  
    // 2) Mod switch to \ZZ_2N^{n+1} Note that this should actually modulus switch to N not to 2N!  
    ms_from_gadget_to_tiny_par.switch_modulus(lwe_c_N.ct, lwe_c_N.ct); 
    // Shifting to have the ``payload'' so that its within (0, N) 
    // - otherwise for message 0, we could have negative noise and the phase could be also in (N, 2N) 
    lwe_c.ct[0] = lwe_c_N.ct[0] + round((double)lwe_par_tiny->modulus/(2 * encoding.plaintext_space)); 
    // In case modulus reduction happens here, we need to flip the extracted MSB
    bool modulus_reduction_event = false;
    if(lwe_c.ct[0] >= lwe_par_tiny->modulus){  
        lwe_c.ct[0] = lwe_c.ct[0] % lwe_par_tiny->modulus; 
        modulus_reduction_event = true;
    }
    // Copy  
    for(int i = 1; i < lwe_par_tiny->dim+1; ++i){
        lwe_c.ct[i] = lwe_c_N.ct[i];
    }    
    // 3) Blind rotate (Compute the sign, but with scale 2N/2 = N!)   
    blind_rotation_key->blind_rotate(br_out->accumulator, &lwe_c, acc_msb);   
    // 4) Sample Extract (I can perform it oon the lwe_ct_out because it should have the right dimension)  
    br_out->extract_lwe(lwe_ct_out);
    // And again: 
    key_switch_key->lwe_to_lwe_key_switch(&lwe_c, lwe_ct_out); 
    // 2) Mod switch to \ZZ_2N^{n+1} Note that this should actually modulus switch to N not to 2N!  
    ms_from_gadget_to_par.switch_modulus(lwe_c.ct, lwe_c.ct); 
    // Add lwe_c + lwe_c_N (this should eliminate the msb in lwe_c_N) 
    // TODO: DO it through the LWECT class.... Unless the moduli don't fit..
    //lwe_c.add(&lwe_c, &lwe_c_N);
    for(int i = 0; i < this->lwe_par->dim+1; ++i){
        lwe_c.ct[i] = (lwe_c.ct[i] + lwe_c_N.ct[i]) % lwe_par->modulus;
    }   
    if(modulus_reduction_event){ 
        lwe_c.ct[0] = Utils::integer_mod_form(lwe_c.ct[0] - (long)round((double)(3 * lwe_par->modulus)/4), lwe_par->modulus);
    }else{
        lwe_c.ct[0] = Utils::integer_mod_form(lwe_c.ct[0] - (long)round((double)lwe_par->modulus/4), lwe_par->modulus);
    }  
    // 3) Blind rotate 
    blind_rotation_key->blind_rotate(br_out->accumulator, &lwe_c, acc_in);
    // 4) Sample Extract   
    br_out->extract_lwe(lwe_ct_out); 
} 

std::vector<LWECT> LMPFunctionalBootstrapPublicKey::full_domain_bootstrap(std::vector<std::shared_ptr<VectorCTAccumulator>> acc_in_vec, LWECT *lwe_ct_in, PlaintextEncoding &encoding){   
    // 1) Key switch to \ZZ_Q^{n+1} 
    LWECT lwe_c_N(ms_from_gadget_to_par.from);
    LWECT lwe_c(ms_from_gadget_to_par.from);
    LWECT lwe_ct_out(key_switch_key->origin);
    key_switch_key->lwe_to_lwe_key_switch(&lwe_c_N, lwe_ct_in);
    // 2) Mod switch to \ZZ_2N^{n+1} Note that this should actually modulus switch to N not to 2N! 
    ms_from_gadget_to_tiny_par.switch_modulus(lwe_c_N.ct, lwe_c_N.ct);
    // Shifting to have the ``payload'' withing (0, N) 
    // - otherwise for message 0, we could have negative noise and the phase could be also in (N, 2N) 
    lwe_c.ct[0] = lwe_c_N.ct[0] + round((double)lwe_par_tiny->modulus/(2 * encoding.ticks)); 
    // In case modulus reduction happens here, we need to flip the extracted MSB
    bool modulus_reduction_event = false;
    if(lwe_c.ct[0] >= lwe_par_tiny->modulus){  
        lwe_c.ct[0] = lwe_c.ct[0] % lwe_par_tiny->modulus; 
        modulus_reduction_event = true;
    }
    // Copy  
    for(int i = 1; i < lwe_par_tiny->dim+1; ++i){
        lwe_c.ct[i] = lwe_c_N.ct[i];
    }    
    // 3) Blind rotate (Compute the sign, but with scale 2N/2 = N!)   
    blind_rotation_key->blind_rotate(br_out->accumulator, &lwe_c, acc_msb);
    // 4) Sample Extract (I can perform it oon the lwe_ct_out because it should have the right dimension)  
    br_out->extract_lwe(&lwe_ct_out);
    key_switch_key->lwe_to_lwe_key_switch(&lwe_c_N, lwe_ct_in);
    // 2) Mod switch to \ZZ_2N^{n+1} Note that this should actually modulus switch to N not to 2N! 
    ms_from_gadget_to_par.switch_modulus(lwe_c.ct, lwe_c.ct);
    // Add lwe_c + lwe_c_N (this should eliminate the msb in lwe_c_N)  
    for(int i = 0; i < lwe_par->dim+1; ++i){
        lwe_c.ct[i] = (lwe_c.ct[i] + lwe_c_N.ct[i]) % lwe_par->modulus;
    }  
    if(modulus_reduction_event){ 
        lwe_c.ct[0] = Utils::integer_mod_form(lwe_c.ct[0] - (long)round((double)(3 * lwe_par->modulus)/4), lwe_par->modulus);
    }else{
        lwe_c.ct[0] = Utils::integer_mod_form(lwe_c.ct[0] - (long)round((double)lwe_par->modulus/4), lwe_par->modulus);
    }  
    // 3) Blind rotate  
    acc_one = std::shared_ptr<VectorCTAccumulator>(accumulator_builder->get_acc_one(encoding));
    blind_rotation_key->blind_rotate(br_out->accumulator, &lwe_c, acc_one);
    std::vector<LWECT> out_vec; 
    for(std::shared_ptr<VectorCTAccumulator> i:  acc_in_vec){    
        br_out->post_rotation(br_temp, i);   
        br_temp->extract_lwe(&lwe_ct_out); 
        out_vec.push_back(lwe_ct_out);  
    }  
    return out_vec;
} 
  




 