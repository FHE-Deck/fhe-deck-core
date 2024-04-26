
#ifndef FHE_CONFIGURATION_H
#define FHE_CONFIGURATION_H
 
#include "lwe.h"
#include "rlwe.h" 
#include "functional_bootstrap.h"

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>


namespace fhe_deck{
 

enum class FHENamedParams{ 
    tfhe_11_B, tfhe_11_flood, tfhe_11_NTT, tfhe_11_NTT_flood, tfhe_11_NTT_amortized, tfhe_12_NTT_amortized
};


class FHEConfiguration{ 
    
    public:   

    FHENamedParams name;

    std::shared_ptr<LWESK> secret_key;
    std::shared_ptr<FunctionalBootstrapPublicKey> fun_bootstrap_pk; 
    std::shared_ptr<LWEPublicKey> encrypt_public_key; 
    std::shared_ptr<AbstractAccumulatorBuilder> accumulator_builder;
 
    PlaintextEncoding default_encoding;

    FHEConfiguration() = default;

    FHEConfiguration(FHENamedParams name);
   
    void generate_keys();

    std::shared_ptr<LWESK> get_secret_key();
    
    std::shared_ptr<FunctionalBootstrapPublicKey> get_functional_bootstrap_pk();

    std::shared_ptr<LWEPublicKey> get_encrypt_pk(); 

    std::shared_ptr<AbstractAccumulatorBuilder> get_accumulator_builder(); 
 
    void init_tfhe_11_NTT(); 

    void init_tfhe_11_NTT_flood();

    void init_tfhe_11_B(); 

    void init_tfhe_11_flood();

    void init_tfhe_11_NTT_amortized(); 

    void init_tfhe_12_NTT_amortized();
};

}

#endif