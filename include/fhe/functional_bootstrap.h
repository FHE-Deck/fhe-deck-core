
#ifndef FUNCTIONAL_BOOTSTRAP_H
#define FUNCTIONAL_BOOTSTRAP_H
 

/**
 * @file functional_bootstrap.h
 */


#include "interface/ciphertext.h"
#include "ciphertexts/lwe.h"
#include "ciphertexts/rlwe.h" 
#include "interface/rotation_poly.h"
#include "fhe/cggi_blind_rotation.h"
#include "keyswitch/lwe_to_lwe_keyswitch.h" 
#include "keyswitch/lwe_to_rlwe_keyswitch.h" 


#include <cereal/archives/binary.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>
 
namespace fhe_deck{
  
/**
 * @brief The FunctionalBootstrapPublicKey class. Class is used to implement functional bootstrapping. 
 * That is, a procedure that computes a function of the plaintext encoded in the ciphertext, and outputs a ciphertext which noise magnitude is independent of the input ciphertext.
 */
class FunctionalBootstrapPublicKey{

    public:
        
    /// @brief Blind Rotation Key  
    std::shared_ptr<BlindRotationPublicKey> blind_rotation_key;
    /// @brief Key Switching key, form extracted LWE to output LWE
    std::shared_ptr<LWEToLWEKeySwitchKey> key_switch_key;
    /// @brief LWE after modulus switching to 2*N (Can actually be extracted form the blind rotation key);
    std::shared_ptr<LWEParam> lwe_par;   
    /// @brief Needed to build a special accumulators, like acc_one that is used in the amortized bootstrapping.
    std::shared_ptr<PreparedVectorCTAccumulators> prepared_acc_builder;
    /// @brief A modulus switcher, that switcher from the LWE ciphertext extracted from a blind rotation output to a LWE with a smaller modulus.
    LWEModSwitcher ms_from_extract_to_intermediate; 
    /// @brief A modulus switcher, that switcher from the LWE ciphertext output by a LWE key switch to the LWE that is ready to be blind rotated. 
    LWEModSwitcher ms_from_keyswitch_to_par; 
    /// @brief The blind rotate output builder.
    std::shared_ptr<BlindRotateOutputBuilder> blind_rotate_output_builder;
    /// @brief Indicates whether a full_domain bootstrap supports function amortization. The flag needs to be set in the implementation of this class.
    bool is_full_domain_bootstrap_function_amortizable = false;
   
    /// @brief The bootstrapping procedure. Its not necesarily a full domain bootstrapping. 
    /// @param lwe_ct_out The output ciphertext
    /// @param acc_in The input accumulator specifying the function to be computed.
    /// @param lwe_ct_in The input ciphertext that we will bootstrap.
    void bootstrap(LWECT &lwe_ct_out, std::shared_ptr<FunctionSpecification> acc_in, const LWECT &lwe_ct_in);
     
    /// @brief Full domain bootstrapping procedure.  
    /// @param lwe_ct_out The output ciphertext
    /// @param acc_in The input accumulator specifying the function to be computed.
    /// @param lwe_ct_in The input ciphertext that we will bootstrap.
    /// @param encoding The encoding of the plaintext in the input ciphertext.
    virtual void full_domain_bootstrap(LWECT &lwe_ct_out, std::shared_ptr<FunctionSpecification> acc_in, const LWECT &lwe_ct_in, const PlaintextEncoding &encoding) = 0;
    
    /// @brief Multivalue bootstrapping procedure. Its not necesarily a full domain bootstrapping. Applies a vector of accumulators, and returns a vector of bootstrapped ciphertexts.
    /// @param lwe_ct_out The output ciphertext
    /// @param acc_in The input accumulator specifying the function to be computed.
    /// @param lwe_ct_in The input ciphertext that we will bootstrap.
    std::vector<LWECT> bootstrap(std::vector<std::shared_ptr<FunctionSpecification>> acc_in_vec, const LWECT &lwe_ct_in, const PlaintextEncoding &encoding);
 
    /// @brief Full domain bootstrapping procedure. Applies a vector of accumulators, and returns a vector of bootstrapped ciphertexts.
    /// @param lwe_ct_out The output ciphertext
    /// @param acc_in The input accumulator specifying the function to be computed.
    /// @param lwe_ct_in The input ciphertext that we will bootstrap.
    /// @param encoding The encoding of the plaintext in the input ciphertext.
    virtual std::vector<LWECT> full_domain_bootstrap(std::vector<std::shared_ptr<FunctionSpecification>> acc_in_vec, const LWECT &lwe_ct_in, const PlaintextEncoding &encoding) = 0;

    template <class Archive>
    void save( Archive & ar ) const
    {   
      ar(blind_rotation_key, key_switch_key, lwe_par, prepared_acc_builder, blind_rotate_output_builder);    
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
      ar(blind_rotation_key, key_switch_key, lwe_par, prepared_acc_builder, blind_rotate_output_builder);  
    }    
 
};
  

}
  

#endif
