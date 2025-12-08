#include "fhe/ks_functional_bootstrap.h"

using namespace FHEDeck;
 

KSFunctionalBootstrapPublicKey::KSFunctionalBootstrapPublicKey(
        std::shared_ptr<LWEParam> lwe_par,  
        std::shared_ptr<BlindRotationPublicKey> blind_rotation_key, 
        std::shared_ptr<LWEToLWEKeySwitchKey> key_switch_key,
        std::shared_ptr<LWEToRLWEKeySwitchKey> key_switch_key_rlwe,
        std::shared_ptr<BlindRotateOutputBuilder> blind_rotate_output_builder,
        std::shared_ptr<PreparedVectorCTAccumulators> prepared_acc_builder) { 

    m_blind_rotation_key = blind_rotation_key;
    m_key_switch_key = key_switch_key;
    m_prepared_acc_builder = prepared_acc_builder;
    m_lwe_par = lwe_par;
    m_blind_rotate_output_builder = blind_rotate_output_builder;  
    m_rlwe_ksk = key_switch_key_rlwe;  
    init();
}
 
void KSFunctionalBootstrapPublicKey::init(){
    m_is_full_domain_bootstrap_function_amortizable = true;
    m_poly_ct_params  = m_rlwe_ksk->dest_param();
    m_ms_from_keyswitch_to_par = LWEModSwitcher(m_key_switch_key->destination(), m_lwe_par);
}
  
void KSFunctionalBootstrapPublicKey::full_domain_bootstrap(LWECT &lwe_ct_out,
                                                                        std::shared_ptr<FunctionSpecification> acc_in,
                                                                        const LWECT &lwe_ct_in,
                                                                        const PlaintextEncoding &input_encoding, 
                                                                        const PlaintextEncoding &output_encoding) {   

    LWECT lwe_c_N(m_key_switch_key->destination());
    m_key_switch_key->lwe_to_lwe_key_switch(lwe_c_N, lwe_ct_in); 
    //lwe_c_N.param = m_ms_from_keyswitch_to_par.to;
    //m_ms_from_keyswitch_to_par.switch_modulus(lwe_c_N, lwe_c_N);  
    lwe_c_N = m_ms_from_keyswitch_to_par.switch_modulus(lwe_c_N); 
    /// NOTE: In the paper its N / t. But the modulus is 2*N, which is why we add here: modulus / (2 * t).
    lwe_c_N.add(lwe_c_N, lwe_c_N.param()->modulus() / (2 * input_encoding.get_plaintext_space()));   
    /// Blind rotate to compute the msb
    std::shared_ptr<VectorCTAccumulator> acc_msb = m_prepared_acc_builder->get_acc_msb(output_encoding); 
    std::shared_ptr<BlindRotateOutput> br_out(m_blind_rotate_output_builder->build()); 
    m_blind_rotation_key->blind_rotate(*br_out->accumulator, lwe_c_N, acc_msb);  
    br_out->extract_lwe(lwe_ct_out); 
    /// lwe_ct_out contains now the MSB of the input ciphertext
    lwe_ct_out.add(lwe_ct_out, m_poly_ct_params->modulus() / (2 * output_encoding.get_plaintext_space()));  
    std::shared_ptr<RLWECT> acc_proto = std::make_shared<RLWECT>(m_poly_ct_params);
    /// acc_proto is a RLWECT that contain the MSB of the input ciphertext
    m_rlwe_ksk->lwe_to_rlwe_key_switch(*acc_proto, lwe_ct_out); 
    /// Construct the acc_proto rotation polynomial that will be used for the final blind rotation
    std::shared_ptr<KSFunctionSpecification> acc_in_F = std::static_pointer_cast<KSFunctionSpecification>(acc_in);  
    Polynomial rot_delta = acc_in_F->poly_msb_1; 
    /// Compute rot_delta = poly_0 - poly_1  
    rot_delta.sub(rot_delta, acc_in_F->poly_msb_0);    
    Polynomial poly_0(m_poly_ct_params->size(), m_poly_ct_params->modulus()); 
    output_encoding.encode_message(poly_0, acc_in_F->poly_msb_0);
    // Compute Q/t * MSB(m) * (poly_1 - poly_0) + poly_0
    acc_proto->mul(*acc_proto, rot_delta);  
    acc_proto->add(*acc_proto, poly_0); 
    /// TODO: pad poly, can be merged into LWE-RLWE keyswitch later if necessary
    Polynomial pad_poly(m_poly_ct_params->size(), m_poly_ct_params->modulus());
    pad_poly.zeroize(); 
    int32_t ones_in_pad_poly;
    if(input_encoding.get_plaintext_space() % 2 == 0){ 
        ones_in_pad_poly = 2 * (m_poly_ct_params->size() / input_encoding.get_plaintext_space());      
    }else{ 
        ones_in_pad_poly =  (m_poly_ct_params->size() / input_encoding.get_plaintext_space());    
    } 
    for(int32_t i = 0; i < ones_in_pad_poly; i++) {
        pad_poly[i] = 1;
    }
    /// Multiply acc_proto with pad_poly
    acc_proto->mul(*acc_proto, pad_poly); 
    /// Final blind rotate & extract
    std::shared_ptr<VectorCTAccumulator> acc_F = std::make_shared<VectorCTAccumulator>(acc_proto);
    m_blind_rotation_key->blind_rotate(*br_out->accumulator, lwe_c_N, acc_F); 
    br_out->extract_lwe(lwe_ct_out); 
}
  
std::vector<LWECT> KSFunctionalBootstrapPublicKey::full_domain_bootstrap(
    std::vector<std::shared_ptr<FunctionSpecification>> acc_in_vec, const LWECT& lwe_ct_in,
    const PlaintextEncoding &input_encoding, 
    const PlaintextEncoding &output_encoding) { 

    LWECT lwe_c_N(m_key_switch_key->destination());
    m_key_switch_key->lwe_to_lwe_key_switch(lwe_c_N, lwe_ct_in); 
    //lwe_c_N.param = m_ms_from_keyswitch_to_par.to;
    //m_ms_from_keyswitch_to_par.switch_modulus(lwe_c_N, lwe_c_N);   
    lwe_c_N = m_ms_from_keyswitch_to_par.switch_modulus(lwe_c_N);   
    lwe_c_N.add(lwe_c_N, lwe_c_N.param()->modulus() / (2 * input_encoding.get_plaintext_space()));   
    /// Initialize the pad_poly
    Polynomial pad_poly = build_pad_poly(m_poly_ct_params->size(), m_poly_ct_params->modulus(), input_encoding.get_plaintext_space());
    /// Initialize the one_poly which has only its constant coefficient set to 1/2, and everything else 0. 
    int64_t half = output_encoding.get_ciphertext_modulus() / (2 * output_encoding.get_plaintext_space());
    Polynomial one_poly  = build_one_poly(m_poly_ct_params->size(), m_poly_ct_params->modulus(), half);
    /// Prepare accumulator for the first blind rotation. 
    std::shared_ptr<VectorCTAccumulator> acc_one = m_prepared_acc_builder->builder->prepare_accumulator(one_poly);
    std::shared_ptr<BlindRotateOutput> br_out_one(m_blind_rotate_output_builder->build()); 
    /// Blind rotation to compute X^{decrypt(lwe_c_N)}
    m_blind_rotation_key->blind_rotate(*br_out_one->accumulator, lwe_c_N, acc_one);
    RLWECT* br_out_rlwe_one = static_cast<RLWECT*>(br_out_one->accumulator);
    /// Multiply X^{decrypt(lwe_c_N)} with the "all ones" polynomial, and extract the sign.   
    Polynomial sign_poly = build_sign_poly(m_poly_ct_params->size(), m_poly_ct_params->modulus());
    RLWECT sign_rlwe(m_poly_ct_params);
    br_out_rlwe_one->mul(sign_rlwe, sign_poly);  
    LWECT sign(lwe_ct_in); 
    sign_rlwe.extract_lwe(sign, 0);  
    /// acc_minus holds X^{decrypt} * pad_poly_one
    std::shared_ptr<RLWECT> acc_minus = std::make_shared<RLWECT>(*br_out_rlwe_one);
    acc_minus->mul(*acc_minus, pad_poly);  
    /// Now we are switching from LWE to RLWE and multiplying the RLWE with the pad_poly_one
    std::shared_ptr<RLWECT> acc_proto = std::make_shared<RLWECT>(m_poly_ct_params); 
    m_rlwe_ksk->lwe_to_rlwe_key_switch(*acc_proto, sign);      
    acc_proto->mul(*acc_proto, pad_poly); 

    /// NOTE: You cannot use the other accumulator, because the acc_minus points at it and you need it later. 
    /// Generally a more elegant solution would be to have acc_minus be a copy of the accumulator.
    std::shared_ptr<BlindRotateOutput> br_out(m_blind_rotate_output_builder->build());  
    RLWECT* br_out_rlwe = static_cast<RLWECT*>(br_out->accumulator);   
    std::shared_ptr<VectorCTAccumulator> acc_br_2 = std::make_shared<VectorCTAccumulator>(acc_proto);
    m_blind_rotation_key->blind_rotate(*br_out->accumulator, lwe_c_N, acc_br_2); 
    std::shared_ptr<RLWECT> acc_plus = std::make_shared<RLWECT>(*br_out_rlwe);  
    std::vector<LWECT> output;
    LWECT tmp_res(lwe_ct_in); 
    RLWECT plus_res(m_poly_ct_params);
    RLWECT minus_res(m_poly_ct_params); 
    for(std::shared_ptr<FunctionSpecification>& acc_in : acc_in_vec) { 
        std::shared_ptr<KSFunctionSpecification> acc_in_F = std::static_pointer_cast<KSFunctionSpecification>(acc_in); 
        Polynomial a = acc_in_F->poly_msb_1;
        Polynomial b = acc_in_F->poly_msb_0;
        a.neg(a); 
        Polynomial plus(b);
        plus.add(plus, a);
        Polynomial minus(b);
        minus.sub(minus, a); 
        acc_plus->mul(plus_res, plus);
        acc_minus->mul(minus_res, minus);
        plus_res.add(plus_res, minus_res);
        plus_res.extract_lwe(tmp_res);   
        output.emplace_back(tmp_res);
    }

    return output; 
}


Polynomial KSFunctionalBootstrapPublicKey::build_pad_poly(int32_t dimension, int64_t coef_modulus, int32_t plaintext_modulus){ 
    uint64_t skip;    
    if(plaintext_modulus % 2 == 0){ 
        skip = 2 * (dimension / plaintext_modulus);       
    }else{ 
        skip = (int32_t)round(dimension/plaintext_modulus);   
    }     
    Polynomial pad_poly(dimension, coef_modulus);
    pad_poly.zeroize(); 
    for(long i = 0; i < skip; i++) {
        pad_poly[i] = 1;
    }   
    return pad_poly;
}

Polynomial KSFunctionalBootstrapPublicKey::build_one_poly(int32_t dimension, int64_t coef_modulus, int64_t value){
    Polynomial one_poly(dimension, coef_modulus);
    one_poly.zeroize(); 
    one_poly[0] = value; 
    return one_poly;
}

Polynomial KSFunctionalBootstrapPublicKey::build_sign_poly(int32_t dimension, int64_t coef_modulus){
    Polynomial sign_poly(dimension, coef_modulus);
    sign_poly.zeroize();
    for(long i = 0; i < dimension; i++) {
        sign_poly[i] = 1;
    }  
    return sign_poly;
}