 
#ifndef LWE_TO_LWE_KEYSWITCH_H
#define LWE_TO_LWE_KEYSWITCH_H

#include "lwe.h"  
 
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>


namespace fhe_deck{


 
class LWEToLWEKeySwitchKey{

  public:

    long ***ksk;
    std::shared_ptr<LWEParam> origin;
    // To
    LWEGadgetParam destination;
    KeySwitchType ks_type;
 
    ~LWEToLWEKeySwitchKey();

    LWEToLWEKeySwitchKey(LWESK *sk_origin, LWEGadgetSK *sk_dest);
 
    LWEToLWEKeySwitchKey(const LWEToLWEKeySwitchKey &other);
   
    LWEToLWEKeySwitchKey& operator=(const LWEToLWEKeySwitchKey other);
 
    void lwe_to_lwe_key_switch_lazy(long *lwe_ct_out, long *lwe_ct_in);

    void lwe_to_lwe_key_switch_partial_lazy(long *lwe_ct_out, long *lwe_ct_in);

    void lwe_to_lwe_key_switch(long *lwe_ct_out, long *lwe_ct_in);

    void set_key_switch_type();

    void key_switching_key_gen(LWESK *sk_origin, LWEGadgetSK *sk_dest);

}; 
 
}


#endif
 
 