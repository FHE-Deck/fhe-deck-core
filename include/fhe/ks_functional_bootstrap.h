#ifndef KS_FUNCTIONAL_BOOTSTRAP_H
#define KS_FUNCTIONAL_BOOTSTRAP_H
 
/**
 * @file ks_functional_bootstrap.h
 */

#include "global_headers.h"

#include "fhe/functional_bootstrap.h"

namespace FHEDeck{
 
/** 
 * @brief The new functional bootstrapping key.
 */
class KSFunctionalBootstrapPublicKey: public FunctionalBootstrapPublicKey{

    public:  
  
    std::shared_ptr<LWEToRLWEKeySwitchKey> rlwe_ksk;
    std::shared_ptr<RLWEParam> poly_ct_params;

    KSFunctionalBootstrapPublicKey(
        std::shared_ptr<LWEParam> lwe_par,  
        std::shared_ptr<BlindRotationPublicKey> blind_rotation_key, 
        std::shared_ptr<LWEToLWEKeySwitchKey> key_switch_key,
        std::shared_ptr<LWEToRLWEKeySwitchKey> key_switch_key_rlwe,
        std::shared_ptr<BlindRotateOutputBuilder> blind_rotate_output_builder,
        std::shared_ptr<PreparedVectorCTAccumulators> prepared_acc_builder);

    void init();

    void full_domain_bootstrap(LWECT& lwe_ct_out, std::shared_ptr<FunctionSpecification> acc_in, const LWECT& lwe_ct_in, const PlaintextEncoding &input_encoding, const PlaintextEncoding &output_encoding);

    std::vector<LWECT> full_domain_bootstrap(std::vector<std::shared_ptr<FunctionSpecification>> acc_in_vec, const LWECT& lwe_ct_in, const PlaintextEncoding &input_encoding, const PlaintextEncoding &output_encoding);

    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    { 
        ar(cereal::base_class<FunctionalBootstrapPublicKey>(this));    
        ar(rlwe_ksk);    
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
        ar(cereal::base_class<FunctionalBootstrapPublicKey>(this));      
        ar(rlwe_ksk);     
        init();
    } 
    #endif 
 
};

} /// End of namespace FHEDeck

#endif