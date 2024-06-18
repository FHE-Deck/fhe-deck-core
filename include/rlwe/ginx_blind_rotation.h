#ifndef GINX_BLIND_ROTATION_H
#define GINX_BLIND_ROTATION_H

#include "lwe.h"
#include "rlwe.h" 
#include "rotation_poly.h"
#include "blind_rotation.h"

#include <cereal/archives/binary.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>

namespace fhe_deck{

 
class GINXBlindRotationKey : public BlindRotationPublicKey{

    public:
    
    // The blind rotation key 
    /// TODO: Perhap we shold use md_span?
    std::vector<std::unique_ptr<GadgetVectorCT>> bk; 
    std::shared_ptr<VectorCTParam> vector_ct_param;
 
    ~GINXBlindRotationKey() = default;

    GINXBlindRotationKey() = default;
      
    GINXBlindRotationKey(std::shared_ptr<GadgetVectorCTSK> gadget_sk, std::shared_ptr<LWESK> lwe_sk);
 
    void blind_rotate(VectorCT* out, LWECT* lwe_ct_in, std::shared_ptr<VectorCTAccumulator> acc_msg);


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
   
    private:  

    void blind_rotation_key_gen(std::shared_ptr<GadgetVectorCTSK> rlwe_gadget_sk, std::shared_ptr<uint64_t[]> ext_s);

    // Temporary variable used in blind rotate. Initialized in the constructors because initialization may be expensive.
    //VectorCT* next_acc; 
   
    uint64_t* init_binary_extended_lwe_key(std::shared_ptr<LWESK> lwe_sk);
    /// TODO: Leave this for a ternary blind rotation alg. that gonna be implemented in the future.
    uint64_t* init_ternary_extended_lwe_key(std::shared_ptr<LWESK> lwe_sk);
};
 
}/// End of namespace fhe_deck

CEREAL_REGISTER_TYPE(fhe_deck::GINXBlindRotationKey)

#endif