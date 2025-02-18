#ifndef CIPHERTEXT_SANITIZATION_H
#define CIPHERTEXT_SANITIZATION_H
 
/**
 * @file ciphertext_sanitization.h
 */

#include "global_headers.h"

#include "ciphertexts/lwe.h"
#include "fhe/functional_bootstrap.h"
 
namespace FHEDeck{
  
/**
 * @brief Interface for public keys used to sanitize a ciphertext. Ciphertexts after sanitization look like fresh ciphertexts. Necessary for circuit privacy among others. 
 */
class SanitizationKey{

    public: 
    /// @brief Default destructor
    virtual ~SanitizationKey() = default;

    /// @brief The sanitization method. 
    /// @param ct_out Output LWE ciphertext
    /// @param ct_in Input LWE ciphertext
    /// @param encoding Plaintext encoding. 
    virtual void sanitize(LWECT &ct_out, const LWECT &ct_in, const PlaintextEncoding &encoding) = 0;

    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    {     
    }
        
    template <class Archive>
    void load( Archive & ar )
    {    
    }    
    #endif 

};

/**
 * @brief The scheme from https://eprint.iacr.org/2016/164, but with the optimizations from https://eprint.iacr.org/2022/1459
 */
class DucasStehleWashingMachine : public SanitizationKey{
 
    public: 
        /// @brief The functional bootstrap public key
        std::shared_ptr<FunctionalBootstrapPublicKey> fun_bootstrap_pk; 
        /// @brief The accumulator builder (we need to compute the identity function)
        std::shared_ptr<AbstractFunctionBuilder> accumulator_builder;
        /// @brief The masking public key (used to sample a fresh ciphertext of zero)
        std::shared_ptr<LWEPublicKey> masking_pk; 
        /// @brief Number of washing cycles
        int32_t washing_cycles;

        ~DucasStehleWashingMachine() = default;

        DucasStehleWashingMachine() = default;

        /// @brief Constructs the object. 
        /// @param fun_bootstrap_pk The functional bootstrap public key
        /// @param accumulator_builder The accumulator builder (we need to compute the identity function)
        /// @param masking_pk The masking public key (used to sample a fresh ciphertext of zero)
        /// @param washing_cycles Number of washing cycles
        DucasStehleWashingMachine(
            std::shared_ptr<FunctionalBootstrapPublicKey> fun_bootstrap_pk, 
            std::shared_ptr<AbstractFunctionBuilder> accumulator_builder,
            std::shared_ptr<LWEPublicKey> masking_pk,
            int32_t washing_cycles);

        /// @brief Outputs a ciphertexts that is statistically independent of the input ciphertext, but that encrypts the same plaintext.
        /// @param ct_out The output ciphertext
        /// @param ct_in The input ciphertext
        /// @param encoding The plaintext encoding
        void sanitize(LWECT &ct_out, const LWECT &ct_in, const PlaintextEncoding &encoding); 

    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    {    
        ar(cereal::base_class<SanitizationKey>(this));     
        ar(fun_bootstrap_pk, accumulator_builder, masking_pk, washing_cycles);
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
        ar(cereal::base_class<SanitizationKey>(this));     
        ar(fun_bootstrap_pk, accumulator_builder, masking_pk, washing_cycles);
    }    
    #endif 

};

/**
 * The scheme from https://eprint.iacr.org/2022/1459
 */
class KluczniakRandomizedBootstrapping : public SanitizationKey{
 
    public: 
        /// @brief The functional bootstrap public key
        std::shared_ptr<FunctionalBootstrapPublicKey> fun_bootstrap_pk; 
        /// @brief The accumulator builder (we need to compute the identity function)
        std::shared_ptr<AbstractFunctionBuilder> accumulator_builder;
        /// @brief The masking public key (used to sample a fresh ciphertext of zero)
        std::shared_ptr<LWEPublicKey> masking_pk; 
  
        ~KluczniakRandomizedBootstrapping() = default;

        KluczniakRandomizedBootstrapping() = default;

        /// @brief Constructs the object.
        /// @param fun_bootstrap_pk The functional bootstrap public key
        /// @param accumulator_builder The accumulator builder (we need to compute the identity function)
        /// @param masking_pk The masking public key (used to sample a fresh ciphertext of zero)
        KluczniakRandomizedBootstrapping(
            std::shared_ptr<FunctionalBootstrapPublicKey> fun_bootstrap_pk, 
            std::shared_ptr<AbstractFunctionBuilder> accumulator_builder,
            std::shared_ptr<LWEPublicKey> masking_pk);

        /// @brief Sanitizes a LWE ciphertext. THe output ciphertext is statistically independent of the input ciphertext, but encrypts the same plaintext.
        /// @param ct_out The output ciphertext
        /// @param ct_in The input ciphertext
        /// @param encoding The plaintext encoding used for the messages. 
        void sanitize(LWECT &ct_out, const LWECT &ct_in, const PlaintextEncoding &encoding); 

    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    {    
        ar(cereal::base_class<SanitizationKey>(this));     
        ar(fun_bootstrap_pk, accumulator_builder, masking_pk);
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
        ar(cereal::base_class<SanitizationKey>(this));     
        ar(fun_bootstrap_pk, accumulator_builder, masking_pk);
    }    
    #endif 
};

}/// End of namespace FHEDeck

/// NOTE: Registering the types for serialization with cereal. 
#if defined(USE_CEREAL)
CEREAL_REGISTER_TYPE(FHEDeck::DucasStehleWashingMachine)
CEREAL_REGISTER_TYPE(FHEDeck::KluczniakRandomizedBootstrapping)
#endif 

#endif 