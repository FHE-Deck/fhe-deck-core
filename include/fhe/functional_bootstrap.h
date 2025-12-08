
#ifndef FUNCTIONAL_BOOTSTRAP_H
#define FUNCTIONAL_BOOTSTRAP_H
 

/**
 * @file functional_bootstrap.h
 */

#include "global_headers.h"

#include "interface/ciphertext.h"
#include "interface/rotation_poly.h"
#include "ciphertexts/lwe.h"
#include "ciphertexts/rlwe.h" 
#include "fhe/cggi_blind_rotation.h" 
#include "keyswitch/lwe_to_lwe_keyswitch.h" 
#include "keyswitch/lwe_to_rlwe_keyswitch.h" 
 
namespace FHEDeck{
  
/**
 * @brief The FunctionalBootstrapPublicKey class. Class is used to implement functional bootstrapping. 
 * That is, a procedure that computes a function of the plaintext encoded in the ciphertext, and outputs a ciphertext which noise magnitude is independent of the input ciphertext.
 */
class FunctionalBootstrapPublicKey{

    protected:

    
    /// @brief Blind Rotation Key  
    std::shared_ptr<BlindRotationPublicKey> m_blind_rotation_key;
    /// @brief Key Switching key, form extracted LWE to output LWE
    std::shared_ptr<LWEToLWEKeySwitchKey> m_key_switch_key;
    /// @brief LWE after modulus switching to 2*N (Can actually be extracted form the blind rotation key);
    std::shared_ptr<LWEParam> m_lwe_par;   
    /// @brief Needed to build a special accumulators, like acc_one that is used in the amortized bootstrapping.
    std::shared_ptr<PreparedVectorCTAccumulators> m_prepared_acc_builder;
    /// @brief A modulus switcher, that switcher from the LWE ciphertext extracted from a blind rotation output to a LWE with a smaller modulus.
    LWEModSwitcher m_ms_from_extract_to_intermediate; 
    /// @brief A modulus switcher, that switcher from the LWE ciphertext output by a LWE key switch to the LWE that is ready to be blind rotated. 
    LWEModSwitcher m_ms_from_keyswitch_to_par; 
    /// @brief The blind rotate output builder.
    std::shared_ptr<BlindRotateOutputBuilder> m_blind_rotate_output_builder;
    /// @brief Indicates whether a full_domain bootstrap supports function amortization. The flag needs to be set in the implementation of this class.
    bool m_is_full_domain_bootstrap_function_amortizable = false;

    public:
        
   
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
    virtual void full_domain_bootstrap(LWECT &lwe_ct_out, std::shared_ptr<FunctionSpecification> acc_in, const LWECT &lwe_ct_in, const PlaintextEncoding &input_encoding, const PlaintextEncoding &output_encoding) = 0;
    
    /// @brief Multivalue bootstrapping procedure. Its not necesarily a full domain bootstrapping. Applies a vector of accumulators, and returns a vector of bootstrapped ciphertexts.
    /// @param lwe_ct_out The output ciphertext
    /// @param acc_in The input accumulator specifying the function to be computed.
    /// @param lwe_ct_in The input ciphertext that we will bootstrap.
    /// @param output_encoding The encoding of the output ciphertexts (note input encodings need to be handled in the FunctionSpecification's in acc_in_vec)
    std::vector<LWECT> bootstrap(std::vector<std::shared_ptr<FunctionSpecification>> acc_in_vec, const LWECT &lwe_ct_in, const PlaintextEncoding &output_encoding);
 
    /// @brief Full domain bootstrapping procedure. Applies a vector of accumulators, and returns a vector of bootstrapped ciphertexts.
    /// @param lwe_ct_out The output ciphertext
    /// @param acc_in The input accumulator specifying the function to be computed.
    /// @param lwe_ct_in The input ciphertext that we will bootstrap.
    /// @param encoding The encoding of the plaintext in the input ciphertext.
    virtual std::vector<LWECT> full_domain_bootstrap(std::vector<std::shared_ptr<FunctionSpecification>> acc_in_vec, const LWECT &lwe_ct_in, const PlaintextEncoding &input_encoding, const PlaintextEncoding &output_encoding) = 0;

    bool is_amortizable()const;

  #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    {   
      ar(m_blind_rotation_key, m_key_switch_key, m_lwe_par, m_prepared_acc_builder, m_blind_rotate_output_builder);    
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
      ar(m_blind_rotation_key, m_key_switch_key, m_lwe_par, m_prepared_acc_builder, m_blind_rotate_output_builder);  
    }    
  #endif 
 
};
  

} /// End of namespace FHEDeck
  

#endif
