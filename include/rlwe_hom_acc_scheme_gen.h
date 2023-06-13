
#ifndef RLWE_HOM_ACC_SCHEME_GEN_H
#define RLWE_HOM_ACC_SCHEME_GEN_H
 
#include "lwe.h"
#include "rlwe.h"
#include "rlwe_param.h"
#include "rlwe_hom_acc_scheme.h"

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>


namespace fhe_deck{

class TFHESecretKey{
 
    public:
 
    RLWEGadgetSK rlwe_gadget;
 
    LWEGadgetSK lwe_gadget;

    // LWE after modulus switching;
    LWESK lwe;

    // Need to have a LWE instance for the input to the bootstrapping (currently we don't have!!!)
    LWESK extract_lwe;
   
    bool is_ext_init = false;
    int sizeof_ext_s;
    long *u;
    int sizeof_u;
    long *ext_s;

    // How many LWE ciphertexts we need for masking key or the sanitization bootstrapping?
    int masking_size;
    double stddev_masking;

    PlaintextEncoding default_encoding;

    ~TFHESecretKey();

    TFHESecretKey() = default;

    // Generates the secret keys 
    TFHESecretKey(RLWEGadgetParam rlwe_gadget_par, LWEGadgetParam lwe_gadget_par, PolynomialArithmetic sk_arithmetic, int masking_size, double stddev_masking, PlaintextEncoding default_encoding);

    TFHESecretKey(const TFHESecretKey& other);

    TFHESecretKey& operator=(const TFHESecretKey other);


    std::shared_ptr<TFHEPublicKey> get_public_param();

    void set_public_params(TFHEPublicKey *boot_pk);
 
    // This is a special way of encoding the lwe, so that we can immediately do a functional blind rotation
    long* scale_and_encrypt_initial_lwe(long m, int t);

    // This is a special way of encoding the lwe, so that we can immediately do a functional blind rotation
    void scale_and_encrypt_initial_lwe(long* ct, long m, int t);

 
    template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(rlwe_gadget, lwe_gadget, extract_lwe, masking_size, stddev_masking, default_encoding);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
        ar(rlwe_gadget, lwe_gadget, extract_lwe, masking_size, stddev_masking, default_encoding);  
          
        long q = rlwe_gadget.gadget_param.rlwe_param->N * 2;  
        this->lwe = lwe_gadget.lwe.modulus_switch(q);    
        if(lwe_gadget.gadget_param.lwe_param->key_d == binary){   
            this->init_binary_key(); 
        }else{  
            this->init_ternary_key();
        }     
    }  

 
    private:

    long* extract_rlwe_key();

    long*** key_switching_key_gen();
 
    long** masking_key_gen();
    
    RLWEGadgetCT* blind_rotation_key_gen();

    void init_binary_key();

    void init_ternary_key();

};


enum TFHENamedParams{ 
    rlwe_hom_acc_scheme_small_test, rlwe_hom_acc_scheme_C_11_B, rlwe_hom_acc_scheme_C_11_flood, rlwe_hom_acc_scheme_C_11_NTT, rlwe_hom_acc_scheme_C_11_NTT_flood, rlwe_hom_acc_scheme_C_11_NTT_amortized
};


class TFHEKeyGenerator{ 
    
    public:  
    std::unique_ptr<TFHESecretKey> boot_sk; 
    std::shared_ptr<TFHEPublicKey> boot_pk;
 
    RLWEGadgetParam rlwe_gadget_par;
    LWEGadgetParam lwe_gadget_par;

    PolynomialArithmetic sk_arithmetic = ntl;

    PlaintextEncoding default_encoding;

    int masking_size;
    double stddev_masking;

    TFHEKeyGenerator() = default;

    TFHEKeyGenerator(TFHENamedParams name);
 
    void generate_bootstapping_keys(); 

    TFHESecretKey generate_secret_key();

    void init_rlwe_hom_acc_scheme_small_test();
 
    void init_rlwe_hom_acc_scheme_C_11_NTT(); 

    void init_rlwe_hom_acc_scheme_C_11_NTT_flood();

    void init_rlwe_hom_acc_scheme_C_11_B(); 

    void init_rlwe_hom_acc_scheme_C_11_flood();

    void init_rlwe_hom_acc_scheme_C_11_NTT_amortized(); 
 

};

}

#endif