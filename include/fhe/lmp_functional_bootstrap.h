
#ifndef LMP_FUNCTIONAL_BOOTSTRAP_H
#define LMP_FUNCTIONAL_BOOTSTRAP_H


/**
 * @file lmp_functional_bootstrap.h
 */

#include "global_headers.h"

#include "fhe/functional_bootstrap.h"

namespace FHEDeck{
       
/**
 * The Bootstrapping algorithm from Liu, Micciancio, Polyakov. Large-Precision Homomorphic Sign Evaluation Using FHEW/TFHE Bootstrapping. https://eprint.iacr.org/2021/1337
 */
class LMPFunctionalBootstrapPublicKey: public FunctionalBootstrapPublicKey{

    public: 

    // LWE after modulus switching to the degree of the polynomial ring (Its computed from lwe_par)
    std::shared_ptr<LWEParam> lwe_par_tiny;
    LWEModSwitcher ms_from_gadget_to_tiny_par;
     
    LMPFunctionalBootstrapPublicKey() = default;
     
    LMPFunctionalBootstrapPublicKey(
        std::shared_ptr<LWEParam> lwe_par, 
        std::shared_ptr<LWEParam> lwe_par_tiny, 
        std::shared_ptr<BlindRotationPublicKey> blind_rotation_key, 
        std::shared_ptr<LWEToLWEKeySwitchKey> key_switch_key, 
        std::shared_ptr<BlindRotateOutputBuilder> blind_rotate_output_builder,  
        std::shared_ptr<PreparedVectorCTAccumulators> accumulator_builder);

    void init();

    void full_domain_bootstrap(LWECT& lwe_ct_out, std::shared_ptr<FunctionSpecification> acc_in, const LWECT& lwe_ct_in, const PlaintextEncoding &input_encoding, const PlaintextEncoding &output_encoding);

    std::vector<LWECT> full_domain_bootstrap(std::vector<std::shared_ptr<FunctionSpecification>> acc_in_vec, const LWECT& lwe_ct_in, const PlaintextEncoding &input_encoding, const PlaintextEncoding &output_encoding);

    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    { 
        ar(cereal::base_class<FunctionalBootstrapPublicKey>(this));    
        ar(lwe_par_tiny);    
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
        ar(cereal::base_class<FunctionalBootstrapPublicKey>(this));      
        ar(lwe_par_tiny);    
        init();
    } 
    #endif 
};

} /// End of namespace FHEDeck

#if defined(USE_CEREAL)
CEREAL_REGISTER_TYPE(FHEDeck::LMPFunctionalBootstrapPublicKey)
#endif 

#endif 