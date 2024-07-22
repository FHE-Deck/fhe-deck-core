#ifndef KS_FUNCTIONAL_BOOTSTRAP_H
#define KS_FUNCTIONAL_BOOTSTRAP_H

#include "functional_bootstrap.h"

namespace fhe_deck{
 
/** 
 * @brief The new functional bootstrapping key.
 */
class KSFunctionalBootstrapPublicKey: public FunctionalBootstrapPublicKey{

    public:  

    // LWE after modulus switching to N (Is computed from lwe_par)
    std::shared_ptr<LWEParam> lwe_par_tiny;

    std::shared_ptr<LWEToRLWEKeySwitchKey> rlwe_ksk;
     
    KSFunctionalBootstrapPublicKey(
        std::shared_ptr<LWEParam> lwe_par, 
        std::shared_ptr<LWEParam> lwe_par_tiny, 
        BlindRotationPublicKey *blind_rotation_key, 
        LWEToLWEKeySwitchKey *key_switch_key,
        LWEToRLWEKeySwitchKey *key_switch_key_rlwe,
        std::shared_ptr<BlindRotateOutputBuilder> blind_rotate_output_builder,  
        std::shared_ptr<AbstractAccumulatorBuilder> accumulator_builder);

    void full_domain_bootstrap(LWECT *lwe_ct_out, std::shared_ptr<VectorCTAccumulator> acc_in, LWECT *lwe_ct_in, PlaintextEncoding &encoding);

    std::vector<LWECT> full_domain_bootstrap(std::vector<std::shared_ptr<VectorCTAccumulator>> acc_in_vec, LWECT *lwe_ct_in, PlaintextEncoding &encoding);
};

}

#endif