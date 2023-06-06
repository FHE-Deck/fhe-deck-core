
#ifndef RLWE_HOM_ACC_SCHEME_GEN_H
#define RLWE_HOM_ACC_SCHEME_GEN_H
 
#include "lwe.h"
#include "rlwe.h"
#include "rlwe_param.h"
#include "rlwe_hom_acc_scheme.h"

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>

class rlwe_hom_acc_scheme_gen{
 
    public:
 
    gadget_rlwe_sk rlwe_gadget;
 
    lwe_gadget_sk lwe_gadget;

    // LWE after modulus switching;
    lwe_sk lwe;

    // Need to have a LWE instance for the input to the bootstrapping (currently we don't have!!!)
    lwe_sk extract_lwe;
   
    bool is_ext_init = false;
    int sizeof_ext_s;
    long *u;
    int sizeof_u;
    long *ext_s;

    // How many LWE ciphertexts we need for masking key or the sanitization bootstrapping?
    int masking_size;
    double stddev_masking;

    plaintext_encoding default_encoding;

    ~rlwe_hom_acc_scheme_gen();

    rlwe_hom_acc_scheme_gen() = default;

    // Generates the secret keys 
    rlwe_hom_acc_scheme_gen(rlwe_gadget_param rlwe_gadget_par, lwe_gadget_param lwe_gadget_par, polynomial_arithmetic sk_arithmetic, int masking_size, double stddev_masking, plaintext_encoding default_encoding);

    rlwe_hom_acc_scheme_gen(const rlwe_hom_acc_scheme_gen& other);

    rlwe_hom_acc_scheme_gen& operator=(const rlwe_hom_acc_scheme_gen other);


    std::shared_ptr<rlwe_hom_acc_scheme> get_public_param();

    void set_public_params(rlwe_hom_acc_scheme *boot_pk);
 
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
          
        long q = rlwe_gadget.gadget_param.param.N * 2;  
        this->lwe = lwe_gadget.lwe.modulus_switch(q);    
        if(lwe_gadget.lwe_g_par.lwe_par.key_d == binary){   
            this->init_binary_key(); 
        }else{  
            this->init_ternary_key();
        }     
    }  

 
    private:

    long* extract_rlwe_key();

    long*** key_switching_key_gen();
 
    long** masking_key_gen();
    
    rlwe_gadget_ct* blind_rotation_key_gen();

    void init_binary_key();

    void init_ternary_key();

};


enum rlwe_hom_acc_scheme_named_param{ 
    rlwe_hom_acc_scheme_small_test, rlwe_hom_acc_scheme_C_11_B, rlwe_hom_acc_scheme_C_11_flood, rlwe_hom_acc_scheme_C_11_NTT, rlwe_hom_acc_scheme_C_11_NTT_flood, rlwe_hom_acc_scheme_C_11_NTT_amortized
};


class rlwe_hom_acc_scheme_named_param_generator{ 
    
    public:  
    std::unique_ptr<rlwe_hom_acc_scheme_gen> boot_sk; 
    std::shared_ptr<rlwe_hom_acc_scheme> boot;
 
    rlwe_gadget_param rlwe_gadget_par;
    lwe_gadget_param lwe_gadget_par;

    polynomial_arithmetic sk_arithmetic = ntl;

    plaintext_encoding default_encoding;

    int masking_size;
    double stddev_masking;

    rlwe_hom_acc_scheme_named_param_generator() = default;

    rlwe_hom_acc_scheme_named_param_generator(rlwe_hom_acc_scheme_named_param name);
 
    void generate_bootstapping_keys(); 

    rlwe_hom_acc_scheme_gen generate_secret_key();

    void init_rlwe_hom_acc_scheme_small_test();
 
    void init_rlwe_hom_acc_scheme_C_11_NTT(); 

    void init_rlwe_hom_acc_scheme_C_11_NTT_flood();

    void init_rlwe_hom_acc_scheme_C_11_B(); 

    void init_rlwe_hom_acc_scheme_C_11_flood();

    void init_rlwe_hom_acc_scheme_C_11_NTT_amortized(); 
 

};

#endif