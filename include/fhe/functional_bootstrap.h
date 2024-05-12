
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
    // LWE after modulus switching to 2*N (Can actually be extracted form the blind rotation key);
    std::shared_ptr<LWEParam> lwe_par;  
    // Needed to build a special accumulators, like acc_one that is used in the amortized bootstrapping.
    std::shared_ptr<AbstractAccumulatorBuilder> accumulator_builder;
    // Special accumulator for blind rotating just the Delta * 1. Its used for the amortized method given that is it supported.
    std::shared_ptr<VectorCTAccumulator> acc_one;
    // Generated from lwe_par, lwe_par_tiny, and extract_lwe_par
    LWEModSwitcher ms_from_gadget_to_par; 
 
    std::shared_ptr<BlindRotateOutput> br_out;
    std::shared_ptr<BlindRotateOutput> br_temp;
    // Indicates whether a full_domain bootstrap supports function amortization. The flag needs to be set in the implementation of this class.
    bool is_full_domain_bootstrap_function_amortizable = false;
   
    void bootstrap(LWECT *lwe_ct_out, std::shared_ptr<VectorCTAccumulator> acc_in, LWECT *lwe_ct_in);
     
    virtual void full_domain_bootstrap(LWECT *lwe_ct_out, std::shared_ptr<VectorCTAccumulator> acc_in, LWECT *lwe_ct_in, PlaintextEncoding &encoding) = 0;
    
    std::vector<LWECT> bootstrap(std::vector<std::shared_ptr<VectorCTAccumulator>> acc_in_vec, LWECT *lwe_ct_in, PlaintextEncoding &encoding);
 
    virtual std::vector<LWECT> full_domain_bootstrap(std::vector<std::shared_ptr<VectorCTAccumulator>> acc_in_vec, LWECT *lwe_ct_in, PlaintextEncoding &encoding) = 0;
  
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
};

// The Bootstrapping algorithm from Liu, Micciancio, Polyakov. Large-Precision Homomorphic Sign Evaluation Using FHEW/TFHE Bootstrapping.
class LMPFunctionalBootstrapPublicKey: public FunctionalBootstrapPublicKey{

    public: 

    // LWE after modulus switching to N (Is computed from lwe_par)
    std::shared_ptr<LWEParam> lwe_par_tiny;
    LWEModSwitcher ms_from_gadget_to_tiny_par;
    
    // Special Accumulator for computing the MSB in Full Domain Functional Bootstrapping 
    std::shared_ptr<VectorCTAccumulator> acc_msb;
     
    LMPFunctionalBootstrapPublicKey(
        std::shared_ptr<LWEParam> lwe_par, 
        std::shared_ptr<LWEParam> lwe_par_tiny, 
        BlindRotationPublicKey *blind_rotation_key, 
        LWEToLWEKeySwitchKey *key_switch_key, 
        std::shared_ptr<BlindRotateOutputBuilder> blind_rotate_output_builder,  
        std::shared_ptr<AbstractAccumulatorBuilder> accumulator_builder);

    void full_domain_bootstrap(LWECT *lwe_ct_out, std::shared_ptr<VectorCTAccumulator> acc_in, LWECT *lwe_ct_in, PlaintextEncoding &encoding);

    std::vector<LWECT> full_domain_bootstrap(std::vector<std::shared_ptr<VectorCTAccumulator>> acc_in_vec, LWECT *lwe_ct_in, PlaintextEncoding &encoding);
};
 
// Here comes the implementation of the Kluczniak Schild Functional Bootstrapping from an upcomming paper. 
class KluczniakSchildFunctionalBootstrapPublicKey: public FunctionalBootstrapPublicKey{

    public: 

    // LWE after modulus switching to N (Is computed from lwe_par)
    std::shared_ptr<LWEParam> lwe_par_tiny;
    
    // Special Accumulator for computing the MSB in Full Domain Functional Bootstrapping 
    std::shared_ptr<VectorCTAccumulator> acc_msb;
     
    KluczniakSchildFunctionalBootstrapPublicKey(
        std::shared_ptr<LWEParam> lwe_par, 
        std::shared_ptr<LWEParam> lwe_par_tiny, 
        BlindRotationPublicKey *blind_rotation_key, 
        LWEToLWEKeySwitchKey *key_switch_key, 
        std::shared_ptr<BlindRotateOutputBuilder> blind_rotate_output_builder,  
        std::shared_ptr<AbstractAccumulatorBuilder> accumulator_builder);

    void full_domain_bootstrap(LWECT *lwe_ct_out, std::shared_ptr<VectorCTAccumulator> acc_in, LWECT *lwe_ct_in, PlaintextEncoding &encoding);

    std::vector<LWECT> full_domain_bootstrap(std::vector<std::shared_ptr<VectorCTAccumulator>> acc_in_vec, LWECT *lwe_ct_in, PlaintextEncoding &encoding);
};

}

#endif
