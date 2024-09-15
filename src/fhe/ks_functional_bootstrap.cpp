#include "ks_functional_bootstrap.h"

using namespace fhe_deck;
 

KSFunctionalBootstrapPublicKey::KSFunctionalBootstrapPublicKey(
        std::shared_ptr<LWEParam> lwe_par,  
        fhe_deck::BlindRotationPublicKey *blind_rotation_key, 
        fhe_deck::LWEToLWEKeySwitchKey *key_switch_key,
        fhe_deck::LWEToRLWEKeySwitchKey *key_switch_key_rlwe,
        std::shared_ptr<BlindRotateOutputBuilder> blind_rotate_output_builder,
        std::shared_ptr<AbstractAccumulatorBuilder> accumulator_builder) { 

    this->blind_rotation_key = std::shared_ptr<BlindRotationPublicKey>(blind_rotation_key);
    this->key_switch_key = std::shared_ptr<LWEToLWEKeySwitchKey>(key_switch_key);
    this->accumulator_builder = accumulator_builder;
    this->lwe_par = lwe_par;
    this->blind_rotate_output_builder = blind_rotate_output_builder;  
    this->rlwe_ksk = std::shared_ptr<LWEToRLWEKeySwitchKey>(key_switch_key_rlwe);  
    init();
}

void KSFunctionalBootstrapPublicKey::init(){
    is_full_domain_bootstrap_function_amortizable = true;
    this->poly_ct_params  = rlwe_ksk->dest_param;
    this->ms_from_keyswitch_to_par = LWEModSwitcher(this->key_switch_key->destination, this->lwe_par);
}
  
void KSFunctionalBootstrapPublicKey::full_domain_bootstrap(fhe_deck::LWECT &lwe_ct_out,
                                                                        std::shared_ptr<VectorCTAccumulator> acc_in,
                                                                        const fhe_deck::LWECT &lwe_ct_in,
                                                                        const fhe_deck::PlaintextEncoding &encoding) { 
    LWECT lwe_c_N(this->key_switch_key->destination);
    key_switch_key->lwe_to_lwe_key_switch(lwe_c_N, lwe_ct_in); 
    lwe_c_N.param = ms_from_keyswitch_to_par.to;
    ms_from_keyswitch_to_par.switch_modulus(lwe_c_N, lwe_c_N);  
    lwe_c_N.add(lwe_c_N, lwe_c_N.param->modulus / (2 * encoding.plaintext_space));   
    /// Blind rotate to compute the msb
    std::shared_ptr<VectorCTAccumulator> acc_msb(this->accumulator_builder->get_acc_msb(encoding)); 
    std::shared_ptr<BlindRotateOutput> br_out(blind_rotate_output_builder->build()); 
    this->blind_rotation_key->blind_rotate(*br_out->accumulator, lwe_c_N, acc_msb);  
    br_out->extract_lwe(lwe_ct_out); 
    /// lwe_ct_out contain nw the MSB of the input ciphertext
    lwe_ct_out.add(lwe_ct_out, poly_ct_params->coef_modulus / (2 * encoding.plaintext_space));  
    std::shared_ptr<RLWECT> acc_proto = std::make_shared<RLWECT>(poly_ct_params);
    /// acc_proto is a RLWECT that contain the MSB of the input ciphertext
    this->rlwe_ksk->lwe_to_rlwe_key_switch(*acc_proto.get(), lwe_ct_out); 
    /// Construct the acc_proto rotation polynomial that will be used for the final blind rotation
    std::shared_ptr<FunctionalAccumulator> acc_in_F = std::static_pointer_cast<FunctionalAccumulator>(acc_in);  
    Polynomial rot_delta = acc_in_F->poly_msb_1; 
    /// Compute rot_delta = poly_0 - poly_1  
    rot_delta.sub(rot_delta, acc_in_F->poly_msb_0);    
    Polynomial poly_0(poly_ct_params->size, poly_ct_params->coef_modulus); 
    encoding.encode_message(poly_0, acc_in_F->poly_msb_0);
    // Compute Q/t * MSB(m) * (poly_1 - poly_0) + poly_0
    acc_proto->mul(*acc_proto.get(), rot_delta);  
    acc_proto->add(*acc_proto.get(), poly_0); 
    /// TODO: pad poly, can be merged into LWE-RLWE keyswitch later if necessary
    Polynomial pad_poly(poly_ct_params->size, poly_ct_params->coef_modulus);
    pad_poly.zeroize(); 
    for(long i = 0; i < 2 * (poly_ct_params->size / encoding.plaintext_space); i++) {
        pad_poly.coefs[i] = 1;
    }
    /// Multiply acc_proto with pad_poly
    acc_proto->mul(*acc_proto.get(), pad_poly); 
    /// Final blind rotate & extract
    std::shared_ptr<VectorCTAccumulator> acc_F = std::make_shared<VectorCTAccumulator>(acc_proto);
    this->blind_rotation_key->blind_rotate(*br_out->accumulator, lwe_c_N, acc_F); 
    br_out->extract_lwe(lwe_ct_out);
 
}
 
std::vector<LWECT> KSFunctionalBootstrapPublicKey::full_domain_bootstrap(
        std::vector<std::shared_ptr<VectorCTAccumulator>> acc_in_vec, const fhe_deck::LWECT& lwe_ct_in,
        const fhe_deck::PlaintextEncoding &encoding) { 
 
    LWECT lwe_c_N(this->key_switch_key->destination);
    key_switch_key->lwe_to_lwe_key_switch(lwe_c_N, lwe_ct_in); 
    lwe_c_N.param = ms_from_keyswitch_to_par.to;
    ms_from_keyswitch_to_par.switch_modulus(lwe_c_N, lwe_c_N);  
    lwe_c_N.add(lwe_c_N, lwe_c_N.param->modulus / (2 * encoding.plaintext_space));  
    /// Blind rotate to compute the msb 
    std::shared_ptr<RLWECT> acc_proto = std::make_shared<RLWECT>(poly_ct_params);
    acc_proto->a.zeroize();
    acc_proto->b.zeroize(); 
    uint64_t scal = poly_ct_params->coef_modulus / (2 * encoding.plaintext_space);
    uint64_t skip = poly_ct_params->size / (encoding.plaintext_space);
    /// NOTE: This is the same as pad poly, but encoded with double the plaintext space... 
    for(long i = 0; i < 2 * skip; i++) {
        acc_proto->b.coefs[i] = scal;
    } 
    std::shared_ptr<VectorCTAccumulator> acc_msb = std::make_shared<VectorCTAccumulator>(acc_proto); 
    std::shared_ptr<BlindRotateOutput> br_out(blind_rotate_output_builder->build()); 
    this->blind_rotation_key->blind_rotate(*br_out->accumulator, lwe_c_N, acc_msb);
    RLWECT* br_out_rlwe = static_cast<RLWECT*>(br_out->accumulator);
    std::shared_ptr<RLWECT> acc_minus = std::make_shared<RLWECT>(*br_out_rlwe);
    LWECT acc(lwe_ct_in);
    LWECT tmp(lwe_ct_in);
    br_out_rlwe->extract_lwe(acc, 0);
    for(int i = 1; i < encoding.plaintext_space/2; i++) {
        br_out_rlwe->extract_lwe(tmp, 2 * i * skip);
        acc.add(acc, tmp);
    } 
    this->rlwe_ksk->lwe_to_rlwe_key_switch(*acc_proto.get(), acc);  
    Polynomial pad_poly(poly_ct_params->size, poly_ct_params->coef_modulus);
    pad_poly.zeroize();
    for(long i = 0; i < 2 * (poly_ct_params->size / encoding.plaintext_space); i++) {
        pad_poly.coefs[i] = 1;
    }
    acc_proto->mul(*acc_proto.get(), pad_poly); 
    std::shared_ptr<VectorCTAccumulator> acc_br_2 = std::make_shared<VectorCTAccumulator>(acc_proto);
    this->blind_rotation_key->blind_rotate(*br_out->accumulator, lwe_c_N, acc_br_2); 
    std::shared_ptr<RLWECT> acc_plus = std::make_shared<RLWECT>(*br_out_rlwe);  
    std::vector<LWECT> output;
    LWECT tmp_res(lwe_ct_in); 
    RLWECT plus_res(poly_ct_params);
    RLWECT minus_res(poly_ct_params); 
    for(std::shared_ptr<fhe_deck::VectorCTAccumulator>& acc_in : acc_in_vec) { 
        std::shared_ptr<FunctionalAccumulator> acc_in_F = std::static_pointer_cast<FunctionalAccumulator>(acc_in); 
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
