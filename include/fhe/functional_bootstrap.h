
#ifndef FUNCTIONAL_BOOTSTRAP_H
#define FUNCTIONAL_BOOTSTRAP_H
 
#include "ciphertext.h"
#include "lwe.h"
#include "rlwe.h" 
#include "rotation_poly.h"
#include "ginx_blind_rotation.h"
#include "lwe_to_lwe_keyswitch.h" 
 
namespace fhe_deck{
 

class FunctionalBootstrapPublicKey{

    public:
        
    // Blind Rotation Key  
    std::shared_ptr<BlindRotationPublicKey> blind_rotation_key;
   
    // Key Switching key, form extracted LWE to output LWE
    std::shared_ptr<LWEToLWEKeySwitchKey> key_switch_key;
    
    // Masking public key
    std::shared_ptr<LWEPublicKey> masking_public_key;  

    FullDomainBootstrappingAlgorithm fdfb_alg;

    // LWE after modulus switching to 2*N (Can actually be extracted form the blind rotation key);
    std::shared_ptr<LWEParam> lwe_par;  
    
    // LWE after modulus switching to N (Is computed from lwe_par)
    std::shared_ptr<LWEParam> lwe_par_tiny;
 
    // TODO rotation_poly_size should be thrown out of the window. Problem is that its used in fhe_context to build new LUTs (rotation polynomials.)
    //long rotation_poly_size;
 
    // Special Accumulator for computing the MSB in Full Domain Functional Bootstrapping
    std::shared_ptr<AbstractAccumulator> acc_msb;
    // Special accumulator for blind rotating just the Delta * 1. Its used for the amortized method.
    std::shared_ptr<AbstractAccumulator> acc_one;

    // LWE after extracting from RLWE. So the modulus is the same as the RLWE modulus. (Can be extracted from the blind_rotation_key)
    std::shared_ptr<LWEParam> extract_lwe_par;

    // Generated from lwe_par, lwe_par_tiny, and extract_lwe_par
    LWEModSwitcher ms_from_gadget_to_par;

    LWEModSwitcher ms_from_gadget_to_tiny_par;

  
    ~FunctionalBootstrapPublicKey();

    FunctionalBootstrapPublicKey() = default;
   
    FunctionalBootstrapPublicKey(BlindRotationPublicKey *blind_rotation_key, LWEToLWEKeySwitchKey *key_switch_key, LWEPublicKey *masking_public_key, FullDomainBootstrappingAlgorithm fdfb_alg);

    FunctionalBootstrapPublicKey(const FunctionalBootstrapPublicKey &other);
   
    FunctionalBootstrapPublicKey& operator=(const FunctionalBootstrapPublicKey other);
  
    LWECT encrypt(long message);
     
    void bootstrap(LWECT *lwe_ct_out, std::shared_ptr<AbstractAccumulator> acc_in, LWECT *lwe_ct_in);
     
    void full_domain_bootstrap(LWECT *lwe_ct_out, std::shared_ptr<AbstractAccumulator> acc_in, LWECT *lwe_ct_in, int t);
   
    void liu_micciancio_polyakov_bootstrap(LWECT *lwe_ct_out, std::shared_ptr<AbstractAccumulator> acc_in, LWECT *lwe_ct_in, int t);
      
    std::vector<LWECT> bootstrap(std::vector<std::shared_ptr<AbstractAccumulator>> acc_in_vec, LWECT *lwe_ct_in, PlaintextEncoding encoding);
 
    std::vector<LWECT> full_domain_bootstrap(std::vector<std::shared_ptr<AbstractAccumulator>> acc_in_vec, LWECT *lwe_ct_in, PlaintextEncoding encoding);
 
    std::vector<LWECT> liu_micciancio_polyakov_bootstrap(std::vector<std::shared_ptr<AbstractAccumulator>> acc_in_vec, LWECT *lwe_ct_in, PlaintextEncoding encoding);
    
 
    template <class Archive>
    void save( Archive & ar ) const
    {    
        /*
        // Serialization of the parameters
        ar(rlwe_gadget_param, lwe_gadget_param, lwe_par, masking_size, stddev_masking, default_encoding);  
        
        // Serialization of the Blind Rotation Key
        for(int i = 0; i < this->sizeof_ext_s; ++i){ 
            ar(this->bk[i]);
        } 
 
        // Serialization Of the Key Switching Key
        for(int i = 0; i < this->rlwe_gadget_param.rlwe_param->N; ++i){  
            for(int j = 0; j < this->lwe_gadget_param.ell; ++j){  
                for(int k = 0; k < this->lwe_gadget_param.lwe_param->n+1; ++k){
                    ar(this->ksk[i][j][k]);
                }
            }
        }  

        // Serialization of the masking or public key
        for(int i = 0; i < masking_size; ++i){   
            for(int j = 0; j < extract_lwe_par->n+1; ++j)
            {
                ar(this->masking_key[i][j]);
            }   
        }  
        */
    }
        
    template <class Archive>
    void load( Archive & ar )
    {    
        /*
        ar(rlwe_gadget_param, lwe_gadget_param, lwe_par, masking_size, stddev_masking, default_encoding);  

        LWEParam lwe_par_tiny = lwe_par->modulus_switch(this->rlwe_gadget_param.rlwe_param->N);
        this->lwe_par_tiny = std::shared_ptr<LWEParam>(new LWEParam(lwe_par_tiny.n, lwe_par_tiny.Q, lwe_par_tiny.key_d, lwe_par_tiny.stddev));
        this->rand_masking = Sampler(0.0, stddev_masking); 
        extract_lwe_par = std::shared_ptr<LWEParam>(new LWEParam(rlwe_gadget_param.rlwe_param->N, rlwe_gadget_param.rlwe_param->Q, lwe_par->key_d, lwe_par->stddev)); 
        this->temp_ct = RLWECT(rlwe_gadget_param.rlwe_param);
        this->next_acc = RLWECT(rlwe_gadget_param.rlwe_param);
        this->out_ct = RLWECT(rlwe_gadget_param.rlwe_param);  
        this->out_ct.set_computing_engine();
        this->key_d = lwe_par->key_d;
        if(this->key_d == binary){  
            init_binary_key(); 
        }else{ 
            init_ternary_key();
        } 
        set_key_switch_type();
        this->acc_msb = RotationPoly::rot_msb(4, rlwe_gadget_param.rlwe_param->N, rlwe_gadget_param.rlwe_param->Q); 
        this->acc_one  = RotationPoly::rot_one(rlwe_gadget_param.rlwe_param->N);
         
        this->bk = new RLWEGadgetCT[this->sizeof_ext_s];
        for(int i = 0; i < this->sizeof_ext_s; ++i){
            ar(this->bk[i]);
        }
 
        this->ksk = new long**[rlwe_gadget_param.rlwe_param->N]; 
        for(int i = 0; i < this->rlwe_gadget_param.rlwe_param->N; ++i){
            this->ksk[i] = new long*[this->lwe_gadget_param.ell];
            for(int j = 0; j < this->lwe_gadget_param.ell; ++j){ 
                this->ksk[i][j] = new long[this->lwe_gadget_param.lwe_param->n+1];
                for(int k = 0; k < this->lwe_gadget_param.lwe_param->n+1; ++k){ 
                    ar(this->ksk[i][j][k]);
                }
            }
        } 
 
        this->masking_key = new long*[masking_size]; 
        for(int i = 0; i < masking_size; ++i){ 
            this->masking_key[i] = extract_lwe_par->init_ct();
            for(int j = 0; j < extract_lwe_par->n+1; ++j)
            {
                ar(this->masking_key[i][j]);
            } 
        } 

        // Set the LWE modulus swicher  
        this->ms_from_gadget_to_par = LWEModSwitcher(this->lwe_gadget_param.lwe_param, this->lwe_par);
        this->ms_from_gadget_to_tiny_par = LWEModSwitcher(this->lwe_gadget_param.lwe_param, this->lwe_par_tiny);

        this->is_init = true;
        */
    } 
 

    private:

    // Temporary variables. Initialized in the constructors because initialization is expensive 
    RLWECT next_acc;
 
    std::shared_ptr<BlindRotateOutput> br_out;
    std::shared_ptr<BlindRotateOutput> br_temp;


    void init_binary_key();

    void init_ternary_key();
  
    void copy_blind_rotation_key(RLWEGadgetCT *bk);
  
    void copy_key_switching_key(long ***ksk);

    void copy_masking_key(long **masking_key);
 
};

  

class FunctionalBootstrapSecretKey{
 
    public:
 
    std::shared_ptr<RLWEGadgetSK> rlwe_gadget_sk;
 
    
    std::shared_ptr<LWEGadgetSK> lwe_gadget_sk;

    // LWE after modulus switching;
    std::shared_ptr<LWESK> lwe_sk;

    // Need to have an LWE instance for the input to the bootstrapping (currently we don't have!!!)
    std::shared_ptr<LWESK> extract_lwe_sk;
   
    bool is_ext_init = false;
    int sizeof_ext_s;
    long *u;
    int sizeof_u;
    long *ext_s;

    // How many LWE ciphertexts we need for masking key or the sanitization bootstrapping?
    int masking_size;
    double stddev_masking;

    PlaintextEncoding default_encoding;

    FullDomainBootstrappingAlgorithm fdfb_alg;

    ~FunctionalBootstrapSecretKey();

    FunctionalBootstrapSecretKey() = default;

    // Generates the secret keys 
    FunctionalBootstrapSecretKey(std::shared_ptr<RLWEGadgetParam> rlwe_gadget_par, LWEGadgetParam lwe_gadget_par, int masking_size, double stddev_masking, PlaintextEncoding default_encoding, FullDomainBootstrappingAlgorithm fdfb_alg);

    FunctionalBootstrapSecretKey(const FunctionalBootstrapSecretKey& other);

    FunctionalBootstrapSecretKey& operator=(const FunctionalBootstrapSecretKey other);
 
    std::shared_ptr<FunctionalBootstrapPublicKey> get_public_param();
  
    // This is a special way of encoding the lwe, so that we can immediately do a functional blind rotation
    long* scale_and_encrypt_initial_lwe(long m, int t);

    // This is a special way of encoding the lwe, so that we can immediately do a functional blind rotation
    void scale_and_encrypt_initial_lwe(long* ct, long m, int t);

 
    template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(rlwe_gadget_sk, lwe_gadget_sk, extract_lwe_sk, masking_size, stddev_masking, default_encoding);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
        ar(rlwe_gadget_sk, lwe_gadget_sk, extract_lwe_sk, masking_size, stddev_masking, default_encoding);  
          
        long q = rlwe_gadget_sk->gadget_param->rlwe_param->degree * 2;  
        this->lwe_sk = lwe_gadget_sk->lwe->modulus_switch(q);    
        if(lwe_gadget_sk->gadget_param.lwe_param->key_d == binary){   
            this->init_binary_key(); 
        }else{  
            this->init_ternary_key();
        }     
    }  
 
    private:
  
    void init_binary_key();

    void init_ternary_key();

};
 


}

#endif
