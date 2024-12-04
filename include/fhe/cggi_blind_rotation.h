#ifndef GINX_BLIND_ROTATION_H
#define GINX_BLIND_ROTATION_H


/**
 * @file cggi_blind_rotation.h
 */


#include "ciphertexts/lwe.h" 
#include "interface/rotation_poly.h"
#include "fhe/blind_rotation.h"

#if defined(USE_CEREAL)
#include <cereal/archives/binary.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>
#endif 

namespace fhe_deck{

/**
 * @brief The CGGIBlindRotationKey class. Implements the blind rotation algorithm from https://eprint.iacr.org/2016/870
 */
class CGGIBlindRotationKey : public BlindRotationPublicKey{

    public:
    
    // The blind rotation key 
    /// TODO: Perhaps we shold use md_span?
    std::vector<std::shared_ptr<GadgetVectorCT>> bk; 
    std::shared_ptr<VectorCTParam> vector_ct_param;
   
    /// @brief Constructor (default constructor is needed for serialization purposes)
    CGGIBlindRotationKey() = default;
      
    /// @brief Constructs the Blind rotation key given a GadgetVectorCTSK, and a LWE secret key.
    /// @param gadget_sk The GadgetVectorCTSK 
    /// @param lwe_sk The LWE secret key, that the blind rotation homomorphically decrypts. 
    CGGIBlindRotationKey(std::shared_ptr<GadgetVectorCTSK> gadget_sk, std::shared_ptr<LWESK> lwe_sk);
 
    /// @brief Blind rotation
    /// @param out The output ciphertext (its assumed to be already allocated, with the proper implementation)
    /// @param lwe_ct_in The LWECT to blind rotate. 
    /// @param acc_msg The accumulator that will be rotated. 
    void blind_rotate(VectorCT& out, const LWECT& lwe_ct_in, std::shared_ptr<VectorCTAccumulator> acc_msg);

    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(cereal::base_class<BlindRotationPublicKey>(this));   
      ar(bk, vector_ct_param);    
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(cereal::base_class<BlindRotationPublicKey>(this));   
      ar(bk, vector_ct_param);    
    }    
    #endif  
   
    private:  

    /// @brief  Blind rotation key generation (its called in the constructor)
    /// @param rlwe_gadget_sk The GadgetVectorCTSK
    /// @param ext_s Extended secret key. The LWE secret key represented in such a format (Binary) that allows us to encrypt it in the blind rotation key.
    void blind_rotation_key_gen(std::shared_ptr<GadgetVectorCTSK> rlwe_gadget_sk, std::shared_ptr<uint64_t[]> ext_s);

    /// @brief Initializes the extended LWE key
    /// @param lwe_sk The LWE secret key
    /// @return Creates a new array which encodes the extended secret key. Its then used in the blind rotation key generation procedure. 
    uint64_t* init_binary_extended_lwe_key(std::shared_ptr<LWESK> lwe_sk);
    
    /// TODO: Leave this for a ternary blind rotation alg. that gonna be implemented in the future.
    uint64_t* init_ternary_extended_lwe_key(std::shared_ptr<LWESK> lwe_sk);
};
 
}/// End of namespace fhe_deck

#if defined(USE_CEREAL)
CEREAL_REGISTER_TYPE(fhe_deck::CGGIBlindRotationKey)
#endif 

#endif