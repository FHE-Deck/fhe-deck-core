#ifndef GINX_BLIND_ROTATION_H
#define GINX_BLIND_ROTATION_H

#include "lwe.h"
#include "rlwe.h" 
#include "rotation_poly.h"
#include "blind_rotation.h"

namespace fhe_deck{

 
class GINXBlindRotationKey : public BlindRotationPublicKey{

    public:
    
    // The blind rotation key 
    /// TODO: Perhap we shold use md_span?
    std::vector<std::unique_ptr<GadgetVectorCT>> bk;
    // Parameteres of the encoding of the LWE key in the blind rotation. These are paramters about the secret key of lwe_par (and lwe_g_par as lwe_par is a modulus switch of lwe_g_par)
    KeyDistribution key_d;
    int sizeof_ext_s;  
 
    ~GINXBlindRotationKey();
      
    GINXBlindRotationKey(std::shared_ptr<GadgetVectorCTSK> gadget_sk, std::shared_ptr<LWESK> lwe_sk);
 
    void blind_rotate(VectorCT* out, LWECT* lwe_ct_in, std::shared_ptr<VectorCTAccumulator> acc_msg);
   
    private:  

    void blind_rotation_key_gen(std::shared_ptr<GadgetVectorCTSK> rlwe_gadget_sk, std::shared_ptr<long[]> ext_s);

    // Temporary variable used in blind rotate. Initialized in the constructors because initialization may be expensive.
    VectorCT* next_acc; 
   
    long* init_binary_extended_lwe_key(std::shared_ptr<LWESK> lwe_sk);
    /// TODO: Leave this for a ternary blind rotation alg. that gonna be implemented in the future.
    long* init_ternary_extended_lwe_key(std::shared_ptr<LWESK> lwe_sk);
};

 
}

#endif