#ifndef LWE_TO_RLWE_KEYSWITCH_H
#define LWE_TO_RLWE_KEYSWITCH_H

/**
 * @file lwe_to_rlwe_keyswitch.h
 */

#include "lwe.h"
#include "rlwe.h"

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>


namespace fhe_deck{

    class LWEToRLWEKeySwitchKey{

    public:
        /// @brief The content of the key switching key (all its ciphertexts)
        /// @todo This should be an extended ciphertext (like a GSW) handled in a separate class. 
        std::vector<std::vector<std::unique_ptr<RLWECT>>> key_content;
        /// @brief LWE Parameter from which we do the switching.
        //std::shared_ptr<LWEParam> origin;
        /// @brief Gadget parameters (for something...)
        std::shared_ptr<Gadget>  destination;
        /// @brief The gadget used to decompose the destination ciphertext.
        std::shared_ptr<RLWEParam> destination_param;
        SignedDecompositionGadget gadget;
        KeySwitchType ks_type; 
        bool use_automorphism = true;

        LWEToRLWEKeySwitchKey(std::shared_ptr<LWESK> sk_origin, std::shared_ptr<RLWEGadgetSK> sk_dest);

        LWEToRLWEKeySwitchKey(const LWEToRLWEKeySwitchKey &other);

        LWEToRLWEKeySwitchKey& operator=(const LWEToRLWEKeySwitchKey other); 

        void lwe_to_rlwe_key_switch(RLWECT *rlwe_ct_out, LWECT *lwe_ct_in);

        void eval_auto_poly(Polynomial* __restrict out_poly, Polynomial* __restrict in_poly, uint32_t log2_idx);

        void eval_auto(RLWECT* rlwe_ct_out, RLWECT* rlwe_ct_in, uint32_t log2_idx); 

        void key_switching_key_gen(std::shared_ptr<LWESK> sk_origin, std::shared_ptr<RLWEGadgetSK> sk_dest);

        private:
        /// Values precomputed in the constructor.
        int64_t degree_inv;
        int64_t bits_degree;
        uint32_t mask2;
        uint32_t mask;

    };

}


#endif //LWE_TO_RLWE_KEYSWITCH_H
