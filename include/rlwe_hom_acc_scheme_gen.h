
#ifndef RLWE_HOM_ACC_SCHEME_GEN_H
#define RLWE_HOM_ACC_SCHEME_GEN_H

#include "lwe.h"
#include "rlwe.h"
#include "rlwe_param.h"
#include "rlwe_hom_acc_scheme.h"


class rlwe_hom_acc_scheme_gen{


    public:
 
    gadget_rlwe_sk rlwe_gadget;
 
    lwe_gadget_sk lwe_gadget;

    // LWE after modulus switching;
    lwe_sk lwe;

    // Need to have a LWE instance for the input to the bootstrapping (currently we don't have!!!)
    lwe_sk extract_lwe;
 
    // Parameteres of the encoding of the LWE key in the blind rotation. These are paramters about the secret key of lwe_par (and lwe_g_par as lwe_par is a modulus switch of lwe_g_par)
    key_dist key_d;
    int sizeof_ext_s;
    long *u;
    int sizeof_u;
    long *ext_s;

    // How many LWE ciphertexts we need for masking key or the sanitization bootstrapping?
    int masking_size;
    double stddev_masking;

    ~rlwe_hom_acc_scheme_gen();

    rlwe_hom_acc_scheme_gen();

    rlwe_hom_acc_scheme_gen(rlwe_gadget_param rlwe_gadget_par, lwe_gadget_param lwe_gadget_par, polynomial_arithmetic sk_arithmetic, int masking_size, double stddev_masking);

    rlwe_hom_acc_scheme* get_public_param();
 
    // This is a special way of encoding the lwe, so that we can immediately do a functional blind rotation
    long* scale_and_encrypt_initial_lwe(long m, int t);

    // This is a special way of encoding the lwe, so that we can immediately do a functional blind rotation
    void scale_and_encrypt_initial_lwe(long* ct, long m, int t);

    private:

    long* extract_rlwe_key();

    long*** key_switching_key_gen();
 
    long** masking_key_gen();
    
    rlwe_gadget_ct* blind_rotation_key_gen();

    void init_binary_key();

    void init_ternary_key();

};


enum rlwe_hom_acc_scheme_named_param{ 
    rlwe_hom_acc_scheme_small_test, rlwe_hom_acc_scheme_C_11_B, rlwe_hom_acc_scheme_C_12_B, rlwe_hom_acc_scheme_C_11_NTT, rlwe_hom_acc_scheme_C_11_NTT_flood
};


class rlwe_hom_acc_scheme_named_param_generator{ 
    
    public:  
    rlwe_hom_acc_scheme_gen* boot_sk; 
    rlwe_hom_acc_scheme* boot;
 
    rlwe_gadget_param rlwe_gadget_par;
    lwe_gadget_param lwe_gadget_par;

    polynomial_arithmetic sk_arithmetic = ntl;

    int masking_size;
    double stddev_masking;

    rlwe_hom_acc_scheme_named_param_generator(rlwe_hom_acc_scheme_named_param name);
 
    void generate_bootstapping_keys(); 

    void init_rlwe_hom_acc_scheme_small_test();
 
    void init_rlwe_hom_acc_scheme_C_11_NTT(); 

    void init_rlwe_hom_acc_scheme_C_11_NTT_flood();

    void init_rlwe_hom_acc_scheme_C_11_B(); 

    void init_rlwe_hom_acc_scheme_C_12_B(); 

};

#endif