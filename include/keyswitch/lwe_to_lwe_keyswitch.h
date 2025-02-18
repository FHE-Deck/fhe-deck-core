 
#ifndef LWE_TO_LWE_KEYSWITCH_H
#define LWE_TO_LWE_KEYSWITCH_H

/**
 * @file lwe_to_lwe_keyswitch.h
 */
#include "global_headers.h"
 
#include "ciphertexts/lwe.h"  
  
namespace FHEDeck{
  
class LWEToLWEKeySwitchKey{

  public:

    /// @brief The content of the key switching key (all its ciphertexts)
    std::shared_ptr<std::shared_ptr<LWEGadgetCT>[]> key_content;
    /// @brief  LWE Parameter from which we do the switching. 
    std::shared_ptr<LWEParam> origin; 
    /// @brief The LWE Parameters of the destination ciphertext. 
    std::shared_ptr<LWEParam>  destination;
   
    /// @brief Default constructor
    LWEToLWEKeySwitchKey() = default;

    /// @brief Builds the key switching key. 
    /// @param sk_origin The secret key of the origin ciphertext.
    /// @param sk_dest The secret key of the destination ciphertext. Its a gadget secret key, because we need the decomposistion base. 
    LWEToLWEKeySwitchKey(std::shared_ptr<LWESK> sk_origin, std::shared_ptr<LWEGadgetSK> sk_dest);
 
    /// @brief Copy constructor
    LWEToLWEKeySwitchKey(const LWEToLWEKeySwitchKey &other);
   
    /// @brief Assignment operator
    LWEToLWEKeySwitchKey& operator=(const LWEToLWEKeySwitchKey other);
    
    /// @brief Lazy key switching (modulus reduction only at the end of the procedure)
    /// @param lwe_ct_out The output ciphertext
    /// @param lwe_ct_in The input ciphertext
    void lwe_to_lwe_key_switch_lazy(LWECT& lwe_ct_out, const LWECT& lwe_ct_in);

    /// @brief Partially lazy key switching (gadget multiiplication is lazy)
    /// @param lwe_ct_out The output ciphertext
    /// @param lwe_ct_in The input ciphertext
    void lwe_to_lwe_key_switch_partial_lazy(LWECT& lwe_ct_out, const LWECT& lwe_ct_in);
    
    /// @brief Key switching with full modulus reduction at each step
    /// @param lwe_ct_out The output ciphertext
    /// @param lwe_ct_in The input ciphertext
    void lwe_to_lwe_key_switch_bussy(LWECT& lwe_ct_out, const LWECT& lwe_ct_in);

    /// @brief Key switching with full modulus reduction at each step
    /// @param lwe_ct_out The output ciphertext
    /// @param lwe_ct_in The input ciphertext
    /// @note The function changes only the ct field of lwe_ct_out. In particular, it doesn't sent the parameters field, so you must make sure lwe_ct_out has the right parameters and is already initialized.
    void lwe_to_lwe_key_switch(LWECT& lwe_ct_out, const LWECT& lwe_ct_in);
 
  #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(origin, destination, ks_type);  
      //ar(key_content);   
      for(int32_t i = 0; i < origin->dim; ++i){      
        ar(key_content[i]);  
      }   

    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(origin, destination, ks_type);
      //ar(key_content);     
      key_content = std::shared_ptr<std::shared_ptr<LWEGadgetCT>[]>(new std::shared_ptr<LWEGadgetCT>[origin->dim]); 
      for(int32_t i = 0; i < origin->dim; ++i){      
        ar(key_content[i]);  
      }   
    }    
    #endif 
    
    private:  
    /// @brief Key switch type. Described whether we do full modulus reduction, or lazy or partially lazy evaluation. 
    KeySwitchType ks_type;

    /// @brief Calculates whether we can affort a lazy or partially lazy key switch based on the decomposition base, digits and ciphertext modulus. Its used only in the constructor.
    /// @param base The decomposition base
    /// @param digits The number of digits in the decomposition
    void set_key_switch_type(uint64_t base, int32_t digits);

    /// @brief Generates the key switching key. Irts used only in the constructor.
    /// @param sk_origin The secret key of the origin ciphertext.
    /// @param sk_dest The secret key of the destination ciphertext. Its a gadget secret key, because we need the decomposistion base. 
    void key_switching_key_gen(std::shared_ptr<LWESK> sk_origin, std::shared_ptr<LWEGadgetSK> sk_dest);

}; 
 
} /// End of nameespace FHEDeck

#endif
 
 