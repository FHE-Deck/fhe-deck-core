
#ifndef FHE_CONFIGURATION_H
#define FHE_CONFIGURATION_H
 
#include "lwe.h"
#include "rlwe.h" 
#include "ciphertext_sanitization.h"
#include "functional_bootstrap.h"
#include "lmp_functional_bootstrap.h"
#include "klu_sch_functional_bootstrap.h"

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>


namespace fhe_deck{
  
enum class FHENamedParams{ 
    tfhe_11_B, tfhe_11_flood, tfhe_11_NTT, tfhe_11_NTT_flood, tfhe_11_NTT_amortized, tfhe_12_NTT_amortized, ntrunium_12_NTT, tfhe_11_KS
};


class PublicEvaluationKey{

    public: 
         
    FHENamedParams name;

    bool is_bootstrap_pk_set = false;
    std::shared_ptr<FunctionalBootstrapPublicKey> bootstrap_pk; 
    std::shared_ptr<AbstractAccumulatorBuilder> accumulator_builder;
    PlaintextEncoding default_encoding; 
    
    bool is_encrypt_pk_set = false;
    std::shared_ptr<LWEPublicKey> encrypt_pk; 
    
    bool is_sanitization_supported = false;
    std::shared_ptr<SanitizationKey> sanitization_pk;

    PublicEvaluationKey() = default;

    template <class Archive>
    void save( Archive & ar ) const
    {   
        /// NOTE: Only public keys are stored. The secret key needs to be storred separately.
        ar(name);
        ar(is_bootstrap_pk_set);
        if(is_bootstrap_pk_set){
            ar(bootstrap_pk, accumulator_builder, default_encoding);
        }
        ar(is_encrypt_pk_set);
        if(is_encrypt_pk_set){
            ar(encrypt_pk);
        }
        ar(is_sanitization_supported);
        if(is_sanitization_supported){
            ar(sanitization_pk);
        }   
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
        /// NOTE: Only public keys are stored. The secret key needs to be storred separately.
        ar(name);
        ar(is_bootstrap_pk_set);
        if(is_bootstrap_pk_set){
            ar(bootstrap_pk, accumulator_builder, default_encoding);
        }
        ar(is_encrypt_pk_set);
        if(is_encrypt_pk_set){
            ar(encrypt_pk);
        }
        ar(is_sanitization_supported);
        if(is_sanitization_supported){
            ar(sanitization_pk);
        }   
    }    

};

class FHEConfiguration{ 
    
    public:   

    
    bool is_secret_key_set = false;
    std::shared_ptr<LWESK> secret_key;
 
    PublicEvaluationKey eval_key;
 
    FHEConfiguration() = default;

    FHEConfiguration(FHENamedParams name);
   
    void generate_keys();
 
 
    void init_tfhe_11_NTT(); 

    void init_tfhe_11_NTT_flood();

    void init_tfhe_11_B(); 

    void init_tfhe_11_flood();

    void init_tfhe_11_NTT_amortized(); 

    void init_tfhe_12_NTT_amortized();

    void init_ntrunium_12_NTT(); 

    void init_tfhe_11_KS();

    

 
};

}

#endif