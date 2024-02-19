
#ifndef FHE_CONFIGURATION_H
#define FHE_CONFIGURATION_H
 
#include "lwe.h"
#include "rlwe.h" 
#include "functional_bootstrap.h"

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>


namespace fhe_deck{
 

enum FHENamedParams{ 
    tfhe_11_B, tfhe_11_flood, tfhe_11_NTT, tfhe_11_NTT_flood, tfhe_11_NTT_amortized, tfhe_12_NTT_amortized
};


class FHEConfiguration{ 
    
    public:  
    std::unique_ptr<FunctionalBootstrapSecretKey> boot_sk; 
    std::shared_ptr<FunctionalBootstrapPublicKey> boot_pk;
 
    RLWEGadgetParam rlwe_gadget_par;
    LWEGadgetParam lwe_gadget_par;

    PolynomialArithmetic sk_arithmetic = ntl;

    PlaintextEncoding default_encoding;

    FullDomainBootstrappingAlgorithm fdfb_alg;

    int masking_size;
    double stddev_masking;

    FHEConfiguration() = default;

    FHEConfiguration(FHENamedParams name);
 
    // TODO: Isn't this deprecated?
    void generate_bootstapping_keys(); 

    FunctionalBootstrapSecretKey generate_secret_key();

    void init_tfhe_small_test();
 
    void init_tfhe_11_NTT(); 

    void init_tfhe_11_NTT_flood();

    void init_tfhe_11_B(); 

    void init_tfhe_11_flood();

    void init_tfhe_11_NTT_amortized(); 

    void init_tfhe_12_NTT_amortized();
 

};

}

#endif