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
        std::vector<std::unique_ptr<ExtendedPolynomialCT>> ext_key_content;
        /// @brief The parameters of the destination RLWE ciphertext.
        std::shared_ptr<RLWEParam> dest_param;
          
        LWEToRLWEKeySwitchKey(std::shared_ptr<LWESK> sk_origin, std::shared_ptr<RLWEGadgetSK> sk_dest);

        LWEToRLWEKeySwitchKey(const LWEToRLWEKeySwitchKey &other);

        LWEToRLWEKeySwitchKey& operator=(const LWEToRLWEKeySwitchKey other); 

        void lwe_to_rlwe_key_switch(RLWECT& rlwe_ct_out, LWECT& lwe_ct_in);

        void eval_auto_poly(Polynomial& out_poly, Polynomial& in_poly, uint32_t log2_idx);

        void eval_auto(RLWECT& rlwe_ct_out, RLWECT& rlwe_ct_in, uint32_t log2_idx); 

        void key_switching_key_gen(std::shared_ptr<LWESK> sk_origin, std::shared_ptr<RLWEGadgetSK> sk_dest);

        private:
        /// @brief inverse of the ring degree
        int64_t degree_inv;
        /// @brief bit size of the ring degree
        int64_t bits_degree;
        /// @brief mask for modulus reduction by dest_param->size * 2 
        uint32_t mask_mod_degree_times_two;
        /// @brief mask for modulus reduction by dest_param->size
        uint32_t mask_mod_degree;

    };

}


#endif //LWE_TO_RLWE_KEYSWITCH_H
