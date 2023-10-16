
#ifndef RLWE_HOM_ACC_SCHEME_H
#define RLWE_HOM_ACC_SCHEME_H
 
#include "ciphertext.h"
#include "lwe.h"
#include "rlwe.h"
#include "rlwe_param.h"  
#include "rotation_poly.h"
 
 
namespace fhe_deck{


class TFHEPublicKey{

    public:
        
    RLWEGadgetParam rlwe_gadget_param; 

    bool is_init = false;

    // The blind rotation key
    RLWEGadgetCT *bk; 
    


    // The key switching key
    long ***ksk;
    LWEGadgetParam lwe_gadget_param;
    KeySwitchType ks_type;



    // Masking size
    int masking_size;
    // Masking key
    long **masking_key;   
    double stddev_masking;
    Sampler rand_masking;



    // LWE after modulus switching to 2*N;
    std::shared_ptr<LWEParam> lwe_par;

    // LWE after modulus switching to N
    std::shared_ptr<LWEParam> lwe_par_tiny;

    // Special Accumulator for computing the MSB in Full Domain Functional Bootstrapping
    long* acc_msb;
    // Special accumulator for blind rotating just the Delta * 1. Its used for the amortized method
    long* acc_one;

    // LWE after extracting from RLWE. So the modulus is the same as the RLWE modulus.
    std::shared_ptr<LWEParam> extract_lwe_par;


    // Parameteres of the encoding of the LWE key in the blind rotation. These are paramters about the secret key of lwe_par (and lwe_g_par as lwe_par is a modulus switch of lwe_g_par)
    KeyDistribution key_d;
    int sizeof_ext_s;
    long *u;
    int sizeof_u;

    LWEModSwitcher ms_from_gadget_to_par;
    LWEModSwitcher ms_from_gadget_to_tiny_par;

    PlaintextEncoding default_encoding;

    ~TFHEPublicKey();

    TFHEPublicKey() = default;
 
    TFHEPublicKey(RLWEGadgetParam rlwe_gadget_par, LWEGadgetParam lwe_gadget_par, std::shared_ptr<LWEParam> lwe_par, RLWEGadgetCT *bk, long ***ksk, long **masking_key, int masking_size, double stddev_masking, PlaintextEncoding default_encoding);

    TFHEPublicKey(const TFHEPublicKey &other);
   
    TFHEPublicKey& operator=(const TFHEPublicKey other);

    void blind_rotate(RLWECT *out, long* lwe_ct_in, long *acc_msg, GadgetMulMode mode);

    void extract_lwe_from_rlwe(long *lwe_ct_out, const RLWECT *rlwe_ct_in);


    // KS
    void lwe_to_lwe_key_switch_lazy(long *lwe_ct_out, long *lwe_ct_in);
    // KS
    void lwe_to_lwe_key_switch_partial_lazy(long *lwe_ct_out, long *lwe_ct_in);
    // KS
    void lwe_to_lwe_key_switch(long *lwe_ct_out, long *lwe_ct_in);
    // KS
    void set_key_switch_type();

 
    void mask_ciphertext(long *lwe_ct_out);

    LWECT encrypt(long message);
 
    void bootstrap(long *lwe_ct_out, long *acc_in, long *lwe_ct_in, GadgetMulMode mode);
 
    void functional_bootstrap_initial(long *lwe_ct_out, long *acc_in, long *lwe_ct_in, GadgetMulMode mode);

    void functional_bootstrap(long *lwe_ct_out, long *acc_in, long *lwe_ct_in, GadgetMulMode mode, int t);
    
    std::vector<LWECT> bootstrap(std::vector<RotationPoly> acc_in_vec, long *lwe_ct_in, GadgetMulMode mode, PlaintextEncoding encoding);
 
    std::vector<LWECT> functional_bootstrap_initial(std::vector<RotationPoly> acc_in_vec, long *lwe_ct_in, GadgetMulMode mode, PlaintextEncoding encoding);

    std::vector<LWECT> functional_bootstrap(std::vector<RotationPoly> acc_in_vec, long *lwe_ct_in, GadgetMulMode mode, PlaintextEncoding encoding);
    


    
    template <class Archive>
    void save( Archive & ar ) const
    {    
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
    }
        
    template <class Archive>
    void load( Archive & ar )
    {    
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
        this->is_init = true;
    } 
 

    private:

    // Temporary variables. Initialized in the constructors because initialization is expensive
    RLWECT out_ct;
    RLWECT temp_ct;
    RLWECT next_acc;

    void init_binary_key();
    void init_ternary_key();
  
    void copy_blind_rotation_key(RLWEGadgetCT *bk);
  
    void copy_key_switching_key(long ***ksk);

    void copy_masking_key(long **masking_key);
 
};


}

#endif
