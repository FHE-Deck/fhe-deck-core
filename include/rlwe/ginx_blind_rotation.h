#ifndef GINX_BLIND_ROTATION_H
#define GINX_BLIND_ROTATION_H

#include "lwe.h"
#include "rlwe.h" 
#include "rotation_poly.h"
#include "blind_rotation.h"

namespace fhe_deck{

 
class GINXBlindRotationKey : public BlindRotationPublicKey{

    public:

    // Parameters of the Gadget RLWE in the blind todation key
    std::shared_ptr<RLWEGadgetParam> rlwe_gadget_param; 

    bool is_init = false;

    // The blind rotation key
    RLWEGadgetCT *bk; 
    
    // LWE after modulus switching to 2*N; 

    // Parameteres of the encoding of the LWE key in the blind rotation. These are paramters about the secret key of lwe_par (and lwe_g_par as lwe_par is a modulus switch of lwe_g_par)
    KeyDistribution key_d;
    int sizeof_ext_s; 
    long *u;
    int sizeof_u;
 
    ~GINXBlindRotationKey();

    GINXBlindRotationKey(std::shared_ptr<RLWEGadgetSK> rlwe_gadget_sk, std::shared_ptr<LWESK> lwe);

    GINXBlindRotationKey(const GINXBlindRotationKey &other);
   
    GINXBlindRotationKey& operator=(const GINXBlindRotationKey other);
  
    void blind_rotate(std::shared_ptr<BlindRotateOutput> out, long* lwe_ct_in, std::shared_ptr<AbstractAccumulator> acc_msg, GadgetMulMode mode = deter);

    std::shared_ptr<BlindRotateOutput> init_blind_rotate_output();

    std::shared_ptr<AbstractAccumulator> prepare_accumulator(long (*f)(long message), PlaintextEncoding output_encoding);

    std::shared_ptr<AbstractAccumulator> prepare_accumulator(long (*f)(long message, long plaintext_space), PlaintextEncoding output_encoding);

    // TODO: Here I actually need some accumulator setup, and these have to be somehow defined there.
    std::shared_ptr<AbstractAccumulator> get_acc_msb(){  
        RotationPoly poly = RotationPoly::rot_msb(4, rlwe_gadget_param->rlwe_param->N, rlwe_gadget_param->rlwe_param->Q);  
        AbstractAccumulator *acc = new RotationPolyAccumulator(poly);  

        std::shared_ptr<AbstractAccumulator> out = std::shared_ptr<AbstractAccumulator>(acc);
  
        return out; 
    }

    std::shared_ptr<AbstractAccumulator> get_acc_one(PlaintextEncoding output_encoding){
        RotationPoly poly = RotationPoly::rot_one(rlwe_gadget_param->rlwe_param->N, output_encoding.ciphertext_modulus);
        poly.coefs[1] = output_encoding.encode_message(1);
        AbstractAccumulator *acc = new RotationPolyAccumulator(poly);  
        return std::shared_ptr<AbstractAccumulator>(acc); 
    }
 
  
    private:
    
    void blind_rotation_key_gen(std::shared_ptr<RLWEGadgetSK> rlwe_gadget_sk, long* ext_s);

    // Temporary variable used in blind rotate. Initialized in the constructors because initialization is expensive.
    RLWECT next_acc;
 
    void init_binary_key();
    void init_ternary_key();

    long* init_binary_extended_lwe_key(std::shared_ptr<LWESK> lwe_sk);
    long* init_ternary_extended_lwe_key(std::shared_ptr<LWESK> lwe_sk);

    void copy_blind_rotation_key(RLWEGadgetCT *bk);

};

 
}

#endif