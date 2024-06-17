
#ifndef FUNCTIONAL_BOOTSTRAP_H
#define FUNCTIONAL_BOOTSTRAP_H
 
#include "ciphertext.h"
#include "lwe.h"
#include "rlwe.h" 
#include "rotation_poly.h"
#include "ginx_blind_rotation.h"
#include "lwe_to_lwe_keyswitch.h" 


#include <cereal/archives/binary.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>
 
namespace fhe_deck{
  
class FunctionalBootstrapPublicKey{

    public:
        
    // Blind Rotation Key  
    std::shared_ptr<BlindRotationPublicKey> blind_rotation_key;
    // Key Switching key, form extracted LWE to output LWE
    std::shared_ptr<LWEToLWEKeySwitchKey> key_switch_key;
    // LWE after modulus switching to 2*N (Can actually be extracted form the blind rotation key);
    std::shared_ptr<LWEParam> lwe_par;  
    // Needed to build a special accumulators, like acc_one that is used in the amortized bootstrapping.
    std::shared_ptr<AbstractAccumulatorBuilder> accumulator_builder;

    // Special accumulator for blind rotating just the Delta * 1. Its used for the amortized method given that is it supported.
    //std::shared_ptr<VectorCTAccumulator> acc_one;
    // Generated from lwe_par, lwe_par_tiny, and extract_lwe_par
    LWEModSwitcher ms_from_gadget_to_par; 
 
    std::shared_ptr<BlindRotateOutputBuilder> blind_rotate_output_builder;
    //std::shared_ptr<BlindRotateOutput> br_out;
    //std::shared_ptr<BlindRotateOutput> br_temp;
    // Indicates whether a full_domain bootstrap supports function amortization. The flag needs to be set in the implementation of this class.
    bool is_full_domain_bootstrap_function_amortizable = false;
   
    void bootstrap(LWECT *lwe_ct_out, std::shared_ptr<VectorCTAccumulator> acc_in, LWECT *lwe_ct_in);
     
    virtual void full_domain_bootstrap(LWECT *lwe_ct_out, std::shared_ptr<VectorCTAccumulator> acc_in, LWECT *lwe_ct_in, PlaintextEncoding &encoding) = 0;
    
    std::vector<LWECT> bootstrap(std::vector<std::shared_ptr<VectorCTAccumulator>> acc_in_vec, LWECT *lwe_ct_in, PlaintextEncoding &encoding);
 
    virtual std::vector<LWECT> full_domain_bootstrap(std::vector<std::shared_ptr<VectorCTAccumulator>> acc_in_vec, LWECT *lwe_ct_in, PlaintextEncoding &encoding) = 0;

    template <class Archive>
    void save( Archive & ar ) const
    {  
        /// TODO: Need to change this class in genral. Need to have the Blind rotations output builder. 
      ar(blind_rotation_key, key_switch_key, lwe_par, accumulator_builder, blind_rotate_output_builder);    
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
      ar(blind_rotation_key, key_switch_key, lwe_par, accumulator_builder, blind_rotate_output_builder);  
    }    


};

// The Bootstrapping algorithm from Liu, Micciancio, Polyakov. Large-Precision Homomorphic Sign Evaluation Using FHEW/TFHE Bootstrapping.
class LMPFunctionalBootstrapPublicKey: public FunctionalBootstrapPublicKey{

    public: 

    //std::shared_ptr<BlindRotateOutputBuilder> blind_rotate_output_builder;

    // LWE after modulus switching to N (Is computed from lwe_par)
    std::shared_ptr<LWEParam> lwe_par_tiny;
    LWEModSwitcher ms_from_gadget_to_tiny_par;
    
    // Special Accumulator for computing the MSB in Full Domain Functional Bootstrapping 
    //std::shared_ptr<VectorCTAccumulator> acc_msb;

    LMPFunctionalBootstrapPublicKey() = default;
     
    LMPFunctionalBootstrapPublicKey(
        std::shared_ptr<LWEParam> lwe_par, 
        std::shared_ptr<LWEParam> lwe_par_tiny, 
        std::shared_ptr<BlindRotationPublicKey> blind_rotation_key, 
        std::shared_ptr<LWEToLWEKeySwitchKey> key_switch_key, 
        std::shared_ptr<BlindRotateOutputBuilder> blind_rotate_output_builder,  
        std::shared_ptr<AbstractAccumulatorBuilder> accumulator_builder);

    void init();

    void full_domain_bootstrap(LWECT *lwe_ct_out, std::shared_ptr<VectorCTAccumulator> acc_in, LWECT *lwe_ct_in, PlaintextEncoding &encoding);

    std::vector<LWECT> full_domain_bootstrap(std::vector<std::shared_ptr<VectorCTAccumulator>> acc_in_vec, LWECT *lwe_ct_in, PlaintextEncoding &encoding);

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
};
 
// Here comes the implementation of the Kluczniak Schild Functional Bootstrapping from an upcomming paper. 
class KluczniakSchildFunctionalBootstrapPublicKey: public FunctionalBootstrapPublicKey{

    public: 

    // LWE after modulus switching to N (Is computed from lwe_par)
    std::shared_ptr<LWEParam> lwe_par_tiny;
    
    // Special Accumulator for computing the MSB in Full Domain Functional Bootstrapping 
    std::shared_ptr<VectorCTAccumulator> acc_msb;
     
    KluczniakSchildFunctionalBootstrapPublicKey(
        std::shared_ptr<LWEParam> lwe_par, 
        std::shared_ptr<LWEParam> lwe_par_tiny, 
        BlindRotationPublicKey *blind_rotation_key, 
        LWEToLWEKeySwitchKey *key_switch_key, 
        std::shared_ptr<BlindRotateOutputBuilder> blind_rotate_output_builder,  
        std::shared_ptr<AbstractAccumulatorBuilder> accumulator_builder);

    void full_domain_bootstrap(LWECT *lwe_ct_out, std::shared_ptr<VectorCTAccumulator> acc_in, LWECT *lwe_ct_in, PlaintextEncoding &encoding);

    std::vector<LWECT> full_domain_bootstrap(std::vector<std::shared_ptr<VectorCTAccumulator>> acc_in_vec, LWECT *lwe_ct_in, PlaintextEncoding &encoding);
};

}

CEREAL_REGISTER_TYPE(fhe_deck::LMPFunctionalBootstrapPublicKey)

#endif
