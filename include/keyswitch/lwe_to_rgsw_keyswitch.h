

#ifndef LWE_TO_RGSW_KEYSWITCH_H
#define LWE_TO_RGSW_KEYSWITCH_H

/**
 * @file lwe_to_rgsw_keyswitch.h
 */
#include "global_headers.h"

#include "ciphertexts/lwe.h"
#include "ciphertexts/rlwe.h"
#include "keyswitch/lwe_to_rlwe_keyswitch.h"
 
namespace FHEDeck{

    class LWEToRGSWKeySwitchKey{

    protected:
   
    LWEToRLWEKeySwitchKey lwe_to_rlwe_ks_key;
    RLWEGadgetCT ct_of_sk_dest;
    std::shared_ptr<const RLWEParam> rlwe_param;
    std::shared_ptr<Gadget> gadget_param;
   

    public:
          
        LWEToRGSWKeySwitchKey(const LWESK& sk_origin, const RLWEGadgetSK& sk_dest);
 
        LWEToRGSWKeySwitchKey(const LWEToRGSWKeySwitchKey &other) = delete;

        LWEToRGSWKeySwitchKey& operator=(const LWEToRGSWKeySwitchKey other) = delete;
 
        RLWEGadgetCT lwe_to_rlwe_key_switch(const LWEGadgetCT& lwe_ct_in);

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


#endif //LWE_TO_RGSW_KEYSWITCH_H
