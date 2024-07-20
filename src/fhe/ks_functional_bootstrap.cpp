#include "ks_functional_bootstrap.h"

using namespace fhe_deck;
 

KSFunctionalBootstrapPublicKey::KSFunctionalBootstrapPublicKey(
        std::shared_ptr<LWEParam> lwe_par, std::shared_ptr<LWEParam> lwe_par_tiny,
        fhe_deck::BlindRotationPublicKey *blind_rotation_key, fhe_deck::LWEToLWEKeySwitchKey *key_switch_key,
        fhe_deck::LWEToRLWEKeySwitchKey *key_switch_key_rlwe,
        std::shared_ptr<BlindRotateOutputBuilder> blind_rotate_output_builder,
        std::shared_ptr<AbstractAccumulatorBuilder> accumulator_builder) {
     
    throw std::runtime_error("Not implemented");

}

std::vector<LWECT> KSFunctionalBootstrapPublicKey::full_domain_bootstrap(
        std::vector<std::shared_ptr<VectorCTAccumulator>> acc_in_vec, fhe_deck::LWECT *lwe_ct_in,
        fhe_deck::PlaintextEncoding &encoding) {
        
    throw std::runtime_error("Not implemented");  

}



void KSFunctionalBootstrapPublicKey::full_domain_bootstrap(fhe_deck::LWECT *lwe_ct_out,
                                                                        std::shared_ptr<VectorCTAccumulator> acc_in,
                                                                        fhe_deck::LWECT *lwe_ct_in,
                                                                        fhe_deck::PlaintextEncoding &encoding) {
    throw std::runtime_error("Not implemented");
     
}


 