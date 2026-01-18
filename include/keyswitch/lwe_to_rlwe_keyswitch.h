#ifndef LWE_TO_RLWE_KEYSWITCH_H
#define LWE_TO_RLWE_KEYSWITCH_H

/**
 * @file lwe_to_rlwe_keyswitch.h
 */
#include "global_headers.h"

#include "ciphertexts/lwe.h"
#include "ciphertexts/rlwe.h"
 
namespace FHEDeck{

    class LWEToRLWEKeySwitchKey{

    protected:
 
    /// @brief inverse of the ring degree
    int64_t m_degree_inv;
    /// @brief bit size of the ring degree
    int64_t m_bits_degree;
    /// @brief mask for modulus reduction by dest_param->size * 2 
    uint32_t m_mask_mod_degree_times_two;
    /// @brief mask for modulus reduction by dest_param->size
    uint32_t m_mask_mod_degree; 
    /// @brief The content of the key switching key (all its ciphertexts) 
    std::vector<std::shared_ptr<ExtendedPolynomialCT>> m_ext_key_content;
    /// @brief The parameters of the destination RLWE ciphertext.
    std::shared_ptr<const RLWEParam> m_dest_param;

    void key_switching_key_gen(const LWESK& sk_origin, const RLWEGadgetSK& sk_dest);

    void eval_auto_poly(Polynomial& out_poly, const Polynomial& in_poly, uint32_t log2_idx);

    void eval_auto(RLWECT& rlwe_ct_out, const RLWECT& rlwe_ct_in, uint32_t log2_idx); 

    void init();

    public:
          
        LWEToRLWEKeySwitchKey(const LWESK& sk_origin, const RLWEGadgetSK& sk_dest);
 
        LWEToRLWEKeySwitchKey(const LWEToRLWEKeySwitchKey &other) = delete;

        LWEToRLWEKeySwitchKey& operator=(const LWEToRLWEKeySwitchKey other) = delete;
 
        void lwe_to_rlwe_key_switch(RLWECT& rlwe_ct_out, const LWECT& lwe_ct_in);

        std::shared_ptr<const RLWEParam> dest_param()const;
 
    #if defined(USE_CEREAL)
        template <class Archive>
        void save( Archive & ar ) const
        { 
            ar(m_ext_key_content, m_dest_param);   
        }
            
        template <class Archive>
        void load( Archive & ar )
        {  
            ar(m_ext_key_content, m_dest_param);   
            init(); 
        }    
    #endif 
 
    };

} /// End of namespace FHEDeck


#endif //LWE_TO_RLWE_KEYSWITCH_H
