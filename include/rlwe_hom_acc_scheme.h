
#ifndef RLWE_HOM_ACC_SCHEME_H
#define RLWE_HOM_ACC_SCHEME_H
 
#include "lwe.h"
#include "rlwe.h"
#include "rlwe_param.h"  
#include "../include/rotation_poly.h"
#include "ciphertext.h"
 
class rlwe_hom_acc_scheme{

    public:
        
    rlwe_gadget_param rlwe_gadget_par; 

    // The blind rotation key
    rlwe_gadget_ct *bk;
    
    // The key switching key
    long ***ksk;
    lwe_gadget_param lwe_gadget_par;
    key_switch_type ks_type;

    // Masking size
    int masking_size;
    // Masking key
    long **masking_key;   
    double stddev_masking;
    sampler rand_masking;

    // LWE after modulus switching to 2*N;
    lwe_param lwe_par;

    // LWE after modulus switching to N
    lwe_param lwe_par_tiny;

    // Special Accumulator for computing the MSB in Full Domain Functional Bootstrapping
    long* acc_msb;
    // Special accumulator for blind rotating just the Delta * 1. Its used for the amortized method
    long* acc_one;

    // LWE after extracting from RLWE. So the modulus is the same as the RLWE modulus.
    lwe_param extract_lwe_par;

    // Parameteres of the encoding of the LWE key in the blind rotation. These are paramters about the secret key of lwe_par (and lwe_g_par as lwe_par is a modulus switch of lwe_g_par)
    key_dist key_d;
    int sizeof_ext_s;
    long *u;
    int sizeof_u;

    plaintext_encoding default_encoding;

    ~rlwe_hom_acc_scheme();

    rlwe_hom_acc_scheme();

    // TODO: In ntrunium.h the key distribution (for the LWE gadget param) is given as input
    // But actually it should be in the corresponding LWE_param.
    // TODO: rlwe_gadget_par is already pointed to in rlwe_gadget_ct
    rlwe_hom_acc_scheme(rlwe_gadget_param rlwe_gadget_par, lwe_gadget_param lwe_gadget_par, lwe_param lwe_par, rlwe_gadget_ct *bk, long ***ksk, long **masking_key, int masking_size, double stddev_masking, plaintext_encoding default_encoding);

    void blind_rotate(rlwe_ct *out, long* lwe_ct_in, long *acc_msg, gadget_mul_mode mode);

    void extract_lwe_from_rlwe(long *lwe_ct_out, const rlwe_ct *rlwe_ct_in);

    void lwe_to_lwe_key_switch_lazy(long *lwe_ct_out, long *lwe_ct_in);

    void lwe_to_lwe_key_switch_partial_lazy(long *lwe_ct_out, long *lwe_ct_in);

    void lwe_to_lwe_key_switch(long *lwe_ct_out, long *lwe_ct_in);

    void set_key_switch_type();

    void mask_ciphertext(long *lwe_ct_out);

    lwe_ct encrypt(long message);
 
    void bootstrap(long *lwe_ct_out, long *acc_in, long *lwe_ct_in, gadget_mul_mode mode);
 
    void functional_bootstrap_initial(long *lwe_ct_out, long *acc_in, long *lwe_ct_in, gadget_mul_mode mode);

    void functional_bootstrap(long *lwe_ct_out, long *acc_in, long *lwe_ct_in, gadget_mul_mode mode, int t);
   

    std::vector<lwe_ct> bootstrap(std::vector<rotation_poly> acc_in_vec, long *lwe_ct_in, gadget_mul_mode mode, int t);
 
    std::vector<lwe_ct> functional_bootstrap_initial(std::vector<rotation_poly> acc_in_vec, long *lwe_ct_in, gadget_mul_mode mode, int t);

    std::vector<lwe_ct> functional_bootstrap(std::vector<rotation_poly> acc_in_vec, long *lwe_ct_in, gadget_mul_mode mode, int t);
    

    private:

    void init_binary_key();
    void init_ternary_key();
 
 
};


#endif