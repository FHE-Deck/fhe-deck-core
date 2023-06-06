
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

    bool is_init = false;

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

    rlwe_hom_acc_scheme() = default;
 
    rlwe_hom_acc_scheme(rlwe_gadget_param rlwe_gadget_par, lwe_gadget_param lwe_gadget_par, lwe_param lwe_par, rlwe_gadget_ct *bk, long ***ksk, long **masking_key, int masking_size, double stddev_masking, plaintext_encoding default_encoding);

    rlwe_hom_acc_scheme(const rlwe_hom_acc_scheme &other);
   
    rlwe_hom_acc_scheme& operator=(const rlwe_hom_acc_scheme other);

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
    


    
    template <class Archive>
    void save( Archive & ar ) const
    {    
        ar(rlwe_gadget_par, lwe_gadget_par, lwe_par, masking_size, stddev_masking, default_encoding);  
        
        for(int i = 0; i < this->sizeof_ext_s; ++i){ 
            ar(this->bk[i]);
        } 
 
        for(int i = 0; i < this->rlwe_gadget_par.param.N; ++i){  
            for(int j = 0; j < this->lwe_gadget_par.ell; ++j){  
                for(int k = 0; k < this->lwe_gadget_par.lwe_par.n+1; ++k){
                    ar(this->ksk[i][j][k]);
                }
            }
        }  
  
        for(int i = 0; i < masking_size; ++i){   
            for(int j = 0; j < extract_lwe_par.n+1; ++j)
            {
                ar(this->masking_key[i][j]);
            } 
        }  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {    
        ar(rlwe_gadget_par, lwe_gadget_par, lwe_par, masking_size, stddev_masking, default_encoding);  

        this->lwe_par_tiny = lwe_par.modulus_switch(rlwe_gadget_par.param.N); 
        this->rand_masking = sampler(0.0, stddev_masking); 
        extract_lwe_par = lwe_param(rlwe_gadget_par.param.N, rlwe_gadget_par.param.Q, lwe_par.key_d, lwe_par.stddev); 
        this->temp_ct = rlwe_ct(rlwe_gadget_par.param);
        this->next_acc = rlwe_ct(rlwe_gadget_par.param);
        this->out_ct = rlwe_ct(rlwe_gadget_par.param);  
        this->out_ct.set_computing_engine();
        this->key_d = lwe_par.key_d;
        if(this->key_d == binary){  
            init_binary_key(); 
        }else{ 
            init_ternary_key();
        } 
        set_key_switch_type();
        this->acc_msb = rotation_poly::rot_msb(4, rlwe_gadget_par.param.N, rlwe_gadget_par.param.Q); 
        this->acc_one  = rotation_poly::rot_one(rlwe_gadget_par.param.N);
         
        this->bk = new rlwe_gadget_ct[this->sizeof_ext_s];
        for(int i = 0; i < this->sizeof_ext_s; ++i){
            ar(this->bk[i]);
        }
 
        this->ksk = new long**[rlwe_gadget_par.param.N]; 
        for(int i = 0; i < this->rlwe_gadget_par.param.N; ++i){
            this->ksk[i] = new long*[this->lwe_gadget_par.ell];
            for(int j = 0; j < this->lwe_gadget_par.ell; ++j){ 
                this->ksk[i][j] = new long[this->lwe_gadget_par.lwe_par.n+1];
                for(int k = 0; k < this->lwe_gadget_par.lwe_par.n+1; ++k){ 
                    ar(this->ksk[i][j][k]);
                }
            }
        } 
 
        this->masking_key = new long*[masking_size]; 
        for(int i = 0; i < masking_size; ++i){ 
            this->masking_key[i] = extract_lwe_par.init_ct();
            for(int j = 0; j < extract_lwe_par.n+1; ++j)
            {
                ar(this->masking_key[i][j]);
            } 
        } 
        this->is_init = true;
    } 
 

    private:

    // Temporary variables. Initialized in the constructors because initialization is expensive
    rlwe_ct out_ct;
    rlwe_ct temp_ct;
    rlwe_ct next_acc;

    void init_binary_key();
    void init_ternary_key();
  
    void copy_blind_rotation_key(rlwe_gadget_ct *bk);
  
    void copy_key_switching_key(long ***ksk);

    void copy_masking_key(long **masking_key);
 
};


#endif