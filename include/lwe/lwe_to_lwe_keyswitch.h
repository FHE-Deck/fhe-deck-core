 
#ifndef LWE_TO_LWE_KEYSWITCH_H
#define LWE_TO_LWE_KEYSWITCH_H

#include "lwe.h"  
 
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
 
namespace fhe_deck{
  
class LWEToLWEKeySwitchKey{

  public:

    std::unique_ptr<std::unique_ptr<LWEGadgetCT>[]> key_content;
    std::shared_ptr<LWEParam> origin; 
    std::shared_ptr<LWEParam>  destination;
    KeySwitchType ks_type;
   
    LWEToLWEKeySwitchKey() = default;

    LWEToLWEKeySwitchKey(std::shared_ptr<LWESK> sk_origin, std::shared_ptr<LWEGadgetSK> sk_dest);
 
    LWEToLWEKeySwitchKey(const LWEToLWEKeySwitchKey &other);
   
    LWEToLWEKeySwitchKey& operator=(const LWEToLWEKeySwitchKey other);
    
    void lwe_to_lwe_key_switch_lazy(LWECT *lwe_ct_out, LWECT *lwe_ct_in);

    void lwe_to_lwe_key_switch_partial_lazy(LWECT *lwe_ct_out, LWECT *lwe_ct_in);
    
    void lwe_to_lwe_key_switch_bussy(LWECT *lwe_ct_out, LWECT *lwe_ct_in);

    void lwe_to_lwe_key_switch(LWECT *lwe_ct_out, LWECT *lwe_ct_in);

    void set_key_switch_type(long base, int digits);

    void key_switching_key_gen(std::shared_ptr<LWESK> sk_origin, std::shared_ptr<LWEGadgetSK> sk_dest);

    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(origin, destination, ks_type);  
      //ar(key_content);   
      for(int i = 0; i < origin->dim; ++i){      
        ar(key_content[i]);  
      }   

    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(origin, destination, ks_type);
      //ar(key_content);     
      key_content = std::unique_ptr<std::unique_ptr<LWEGadgetCT>[]>(new std::unique_ptr<LWEGadgetCT>[origin->dim]); 
      for(int i = 0; i < origin->dim; ++i){      
        ar(key_content[i]);  
      }   
    }    

}; 
 
} /// End of nameespace fhe_deck


#endif
 
 