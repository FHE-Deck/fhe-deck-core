
#include "fhe/lmp_functional_bootstrap.h"

using namespace FHEDeck;

LMPFunctionalBootstrapPublicKey::LMPFunctionalBootstrapPublicKey(
        std::shared_ptr<LWEParam> lwe_par, 
        std::shared_ptr<LWEParam> lwe_par_tiny, 
        std::shared_ptr<BlindRotationPublicKey> blind_rotation_key, 
        std::shared_ptr<LWEToLWEKeySwitchKey> key_switch_key,  
        std::shared_ptr<BlindRotateOutputBuilder> blind_rotate_output_builder,
        std::shared_ptr<PreparedVectorCTAccumulators> prepared_acc_builder){ 
    m_is_full_domain_bootstrap_function_amortizable = true;
    m_blind_rotation_key = blind_rotation_key;
    m_key_switch_key = key_switch_key;
    m_blind_rotate_output_builder = blind_rotate_output_builder;
    m_prepared_acc_builder = prepared_acc_builder;
    m_lwe_par = lwe_par; 
    m_lwe_par_tiny = lwe_par_tiny; 
    init();
}

void LMPFunctionalBootstrapPublicKey::init(){ 

    std::shared_ptr<LWEParam> lwe_par_extract(m_blind_rotate_output_builder->build_extract_lwe_param());
    std::shared_ptr<LWEParam> lwe_par_intermediate = std::make_shared<LWEParam>(lwe_par_extract->dim(), m_key_switch_key->destination()->modulus()); 
    m_ms_from_extract_to_intermediate = LWEModSwitcher(lwe_par_extract, lwe_par_intermediate);  
    // Mod Switch from Extracted Q to 2 * N 
    m_ms_from_keyswitch_to_par = LWEModSwitcher(m_key_switch_key->destination(), m_lwe_par);
    // Mod Switch from Extracted Q to N 
    m_ms_from_gadget_to_tiny_par = LWEModSwitcher(m_key_switch_key->destination(), m_lwe_par_tiny);
}
  
void LMPFunctionalBootstrapPublicKey::full_domain_bootstrap(LWECT& lwe_ct_out, 
                                                            std::shared_ptr<FunctionSpecification> acc_in, 
                                                            const LWECT& lwe_ct_in, 
                                                            const PlaintextEncoding &input_encoding, 
                                                            const PlaintextEncoding &output_encoding){    
    // 1) Key switch to \ZZ_Q^{n+1}   
    LWECT lwe_c_N(m_ms_from_keyswitch_to_par.from_param()); 
    LWECT lwe_c(m_ms_from_keyswitch_to_par.from_param()); 
    m_key_switch_key->lwe_to_lwe_key_switch(lwe_c_N, lwe_ct_in);  
    // 2) Mod switch to \ZZ_2N^{n+1} Note that this should actually modulus switch to N not to 2N!  
    m_ms_from_gadget_to_tiny_par.switch_modulus(lwe_c_N, lwe_c_N); 
    // Shifting to have the ``payload'' so that its within (0, N) 
    // - otherwise for message 0, we could have negative noise and the phase could be also in (N, 2N) 
    lwe_c[0] = lwe_c_N[0] + round((double)m_lwe_par_tiny->modulus()/(2 * input_encoding.get_plaintext_space())); 
    // In case modulus reduction happens here, we need to flip the extracted MSB
    bool modulus_reduction_event = false;
    if(lwe_c[0] >= m_lwe_par_tiny->modulus()){  
        lwe_c[0] = lwe_c[0] % m_lwe_par_tiny->modulus(); 
        modulus_reduction_event = true;
    }
    // Copy  
    for(int32_t i = 1; i < m_lwe_par_tiny->dim()+1; ++i){
        lwe_c[i] = lwe_c_N[i];
    }    
    // 3) Blind rotate (Compute the sign, but with scale 2N/2 = N!)   
    std::shared_ptr<BlindRotateOutput> br_out(m_blind_rotate_output_builder->build()); 
    PlaintextEncoding msb_mask_pt_encoding(PlaintextEncodingType::full_domain, 4, output_encoding.get_ciphertext_modulus());
    std::shared_ptr<VectorCTAccumulator> acc_msb(m_prepared_acc_builder->get_acc_sgn(msb_mask_pt_encoding));   
    m_blind_rotation_key->blind_rotate(*br_out->accumulator, lwe_c, acc_msb);   
    // 4) Sample Extract (I can perform it oon the lwe_ct_out because it should have the right dimension)  
    br_out->extract_lwe(lwe_ct_out);
    m_ms_from_extract_to_intermediate.switch_modulus(lwe_ct_out, lwe_ct_out); 
    m_key_switch_key->lwe_to_lwe_key_switch(lwe_c, lwe_ct_out); 
    // 2) Mod switch to \ZZ_2N^{n+1} Note that this should actually modulus switch to N not to 2N!  
    m_ms_from_keyswitch_to_par.switch_modulus(lwe_c, lwe_c); 
    // Add lwe_c + lwe_c_N (this should eliminate the msb in lwe_c_N) 
    /// TODO: Do it through the LWECT class.... Unless the moduli don't fit..
    //lwe_c.add(&lwe_c, &lwe_c_N);
    for(int32_t i = 0; i < m_lwe_par->dim()+1; ++i){
        lwe_c[i] = (lwe_c[i] + lwe_c_N[i]) % m_lwe_par->modulus();
    }   
    if(modulus_reduction_event){ 
        lwe_c[0] = Utils::integer_mod_form(lwe_c[0] - (int64_t)round((double)(3 * m_lwe_par->modulus())/4), m_lwe_par->modulus());
    }else{
        lwe_c[0] = Utils::integer_mod_form(lwe_c[0] - (int64_t)round((double)m_lwe_par->modulus()/4), m_lwe_par->modulus());
    }  
    // 3) Blind rotate 
    std::shared_ptr<VectorCTAccumulator> acc_in_cast = std::static_pointer_cast<VectorCTAccumulator>(acc_in);
    m_blind_rotation_key->blind_rotate(*br_out->accumulator, lwe_c, acc_in_cast);
    // 4) Sample Extract   
    br_out->extract_lwe(lwe_ct_out); 
    m_ms_from_extract_to_intermediate.switch_modulus(lwe_ct_out, lwe_ct_out);
} 

std::vector<LWECT> LMPFunctionalBootstrapPublicKey::full_domain_bootstrap(std::vector<std::shared_ptr<FunctionSpecification>> acc_in_vec, 
                                                                        const LWECT& lwe_ct_in, 
                                                                        const PlaintextEncoding &input_encoding, 
                                                                        const PlaintextEncoding &output_encoding){   
    // 1) Key switch to \ZZ_Q^{n+1}   
    LWECT lwe_c_N(m_ms_from_keyswitch_to_par.from_param()); 
    LWECT lwe_c(m_ms_from_keyswitch_to_par.from_param()); 
    m_key_switch_key->lwe_to_lwe_key_switch(lwe_c_N, lwe_ct_in);  
    // 2) Mod switch to \ZZ_2N^{n+1} Note that this should actually modulus switch to N not to 2N!  
    m_ms_from_gadget_to_tiny_par.switch_modulus(lwe_c_N, lwe_c_N); 
    // Shifting to have the ``payload'' so that its within (0, N) 
    // - otherwise for message 0, we could have negative noise and the phase could be also in (N, 2N) 
    lwe_c[0] = lwe_c_N[0] + round((double)m_lwe_par_tiny->modulus()/(2 * input_encoding.get_plaintext_space())); 
    // In case modulus reduction happens here, we need to flip the extracted MSB
    bool modulus_reduction_event = false;
    if(lwe_c[0] >= m_lwe_par_tiny->modulus()){  
        lwe_c[0] = lwe_c[0] % m_lwe_par_tiny->modulus(); 
        modulus_reduction_event = true;
    }
    // Copy  
    for(int32_t i = 1; i < m_lwe_par_tiny->dim()+1; ++i){
        lwe_c[i] = lwe_c_N[i];
    }    
    // 3) Blind rotate (Compute the sign, but with scale 2N/2 = N!)   
    std::shared_ptr<BlindRotateOutput> br_out(m_blind_rotate_output_builder->build()); 
    PlaintextEncoding msb_mask_pt_encoding(PlaintextEncodingType::full_domain, 4, output_encoding.get_ciphertext_modulus());
    std::shared_ptr<VectorCTAccumulator> acc_msb(m_prepared_acc_builder->get_acc_sgn(msb_mask_pt_encoding));   
    m_blind_rotation_key->blind_rotate(*br_out->accumulator, lwe_c, acc_msb);   
    // 4) Sample Extract (I can perform it oon the lwe_ct_out because it should have the right dimension)  
    LWECT lwe_ct_out(m_key_switch_key->origin());
    br_out->extract_lwe(lwe_ct_out);
    m_ms_from_extract_to_intermediate.switch_modulus(lwe_ct_out, lwe_ct_out); 
    m_key_switch_key->lwe_to_lwe_key_switch(lwe_c, lwe_ct_out); 
    // 2) Mod switch to \ZZ_2N^{n+1} Note that this should actually modulus switch to N not to 2N!  
    m_ms_from_keyswitch_to_par.switch_modulus(lwe_c, lwe_c); 
    // Add lwe_c + lwe_c_N (this should eliminate the msb in lwe_c_N) 
    /// TODO: Do it through the LWECT class.... Unless the moduli don't fit..
    //lwe_c.add(&lwe_c, &lwe_c_N);
    for(int32_t i = 0; i < m_lwe_par->dim()+1; ++i){
        lwe_c[i] = (lwe_c[i] + lwe_c_N[i]) % m_lwe_par->modulus();
    }   
    if(modulus_reduction_event){ 
        lwe_c[0] = Utils::integer_mod_form(lwe_c[0] - (int64_t)round((double)(3 * m_lwe_par->modulus())/4), m_lwe_par->modulus());
    }else{
        lwe_c[0] = Utils::integer_mod_form(lwe_c[0] - (int64_t)round((double)m_lwe_par->modulus()/4), m_lwe_par->modulus());
    }  
    // 3) Blind rotate 
    std::shared_ptr<VectorCTAccumulator> acc_one = std::shared_ptr<VectorCTAccumulator>(m_prepared_acc_builder->get_acc_one(output_encoding));
    m_blind_rotation_key->blind_rotate(*br_out->accumulator, lwe_c, acc_one);
    std::vector<LWECT> out_vec; 
    std::shared_ptr<BlindRotateOutput> br_temp(m_blind_rotate_output_builder->build()); 
    for(std::shared_ptr<FunctionSpecification> i:  acc_in_vec){      
        br_out->post_rotation(br_temp, i);   
        br_temp->extract_lwe(lwe_ct_out); 
        m_ms_from_extract_to_intermediate.switch_modulus(lwe_ct_out, lwe_ct_out);
        out_vec.push_back(lwe_ct_out); 
    }  
    return out_vec;
} 
