
#ifndef FHE_CONFIGURATION_H
#define FHE_CONFIGURATION_H
 

/**
 * @file fhe_configuration.h
 */

#include "global_headers.h"

#include "ciphertexts/lwe.h"
#include "ciphertexts/rlwe.h" 
#include "fhe/ciphertext_sanitization.h"
#include "fhe/functional_bootstrap.h"
#include "fhe/lmp_functional_bootstrap.h"
#include "fhe/ks_functional_bootstrap.h"
 
namespace FHEDeck{
  
enum class FHENamedParams{ 
    tfhe_11_flood, tfhe_11_NTT, tfhe_11_NTT_flood, tfhe_11_NTT_amortized, tfhe_12_NTT_amortized, lmp_12_NTT_amortized, ntrunium_12_NTT, tfhe_11_KS, tfhe_11_KS_amortized
};
 
 
class PublicEvaluationKey{

    public: 
         
    FHENamedParams name;

    bool is_bootstrap_pk_set = false;
    std::shared_ptr<FunctionalBootstrapPublicKey> bootstrap_pk;  

    std::shared_ptr<VectorCTAccumulatorBuilder> boot_acc_builder; 
    std::shared_ptr<AbstractFunctionBuilder> func_boot_acc_builder;
    std::shared_ptr<AbstractFunctionBuilder> multivalue_acc_builder;
    
    PlaintextEncoding default_encoding; 
    
    bool is_encrypt_pk_set = false;
    std::shared_ptr<LWEPublicKey> encrypt_pk; 
    
    bool is_sanitization_supported = false;
    std::shared_ptr<SanitizationKey> sanitization_pk;

    PublicEvaluationKey() = default;

    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    {   
        /// NOTE: Only public keys are stored. The secret key needs to be storred separately.
        ar(name);
        ar(is_bootstrap_pk_set);
        if(is_bootstrap_pk_set){
            ar(bootstrap_pk, boot_acc_builder, func_boot_acc_builder, multivalue_acc_builder, default_encoding);
        }
        ar(is_encrypt_pk_set);
        if(is_encrypt_pk_set){
            ar(encrypt_pk);
        }
        ar(is_sanitization_supported);
        if(is_sanitization_supported){
            ar(sanitization_pk);
        }   
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
        /// NOTE: Only public keys are stored. The secret key needs to be storred separately.
        ar(name);
        ar(is_bootstrap_pk_set);
        if(is_bootstrap_pk_set){
            ar(bootstrap_pk, boot_acc_builder, func_boot_acc_builder, multivalue_acc_builder, default_encoding);
        }
        ar(is_encrypt_pk_set);
        if(is_encrypt_pk_set){
            ar(encrypt_pk);
        }
        ar(is_sanitization_supported);
        if(is_sanitization_supported){
            ar(sanitization_pk);
        }   
    }    
    #endif 

};
 

class FHESecretKey{

    public:

    std::shared_ptr<LWESK> lwe_sk;
    std::shared_ptr<GadgetVectorCTSK> gadget_sk;

    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    {    
        ar(lwe_sk, gadget_sk); 
    }
        
    template <class Archive>
    void load( Archive & ar )
    {     
        ar(lwe_sk, gadget_sk); 
    }    
    #endif 

};


class BasicBootstrapBuilder{

    public:
 
    std::shared_ptr<FHESecretKey> secret_key;
    std::shared_ptr<FunctionalBootstrapPublicKey> bootstrap_pk; 

    bool is_gadget_vector_build = false;
    bool is_secret_keys_build = false;
    bool is_public_key_build = false;
    bool is_vector_ct_gadget_secret_key_build = false;
    bool is_blind_rotation_key_build = false;
    bool is_lwe_to_lwe_keyswitch_build = false;
    bool is_functional_bootstrap_build = false;
    bool is_plaintext_encoding_build = false;


    /// @brief Below are parameters for the ring scheme
    int64_t degree;
    int64_t coef_modulus;
    double stddev;  
    
    RingType ring_type;
    PolynomialArithmetic arithmetic;
    std::shared_ptr<VectorCTSK> vector_ct_secret_key;
     
    GadgetType gadget_type;
    int64_t gadget_decomp_base;
    VectorEncryptionType vector_encyption_type; 
    KeyDistribution key_distribution;

    /// @brief Consider actually to load the gadget from the outside... How would this look like? 
    double gadget_stddev;

    /// @brief Below are parameters for the LWE Key switchihng
    int32_t lwe_dim;
    int64_t lwe_modulus;
    int64_t lwe_ks_decomp_base;
    double lwe_stddev; 
    KeyDistribution lwe_key_distribution;

    /// @brief Parameters for LWE to RLWE key switching
    int64_t lwe_to_rlwe_decomp_base;

    /// @brief Blind Rotation algorithm
    BlindRotationAlgorithm br_algorithm;
    /// @brief The algorithm for Full domain functional bootstrapping
    FullDomainBootstrappingAlgorithm fdfb_algorithm;

    /// @brief Accumulator builders. Their instantiation depends on differnet full domain bootstraping algorithms, VectorCT's, ring dimensions etc. 
    std::shared_ptr<VectorCTAccumulatorBuilder> boot_acc_builder; 
    std::shared_ptr<AbstractFunctionBuilder> func_boot_acc_builder;
    std::shared_ptr<AbstractFunctionBuilder> multivalue_acc_builder;

    /// @brief Parameters for the public key
    int64_t pk_size; 
    double pk_stddev;
    std::shared_ptr<LWEPublicKey> encrypt_pk;

    /// @brief Key and parameters that are often generated and needed by the bootstrapping algorithms.
    std::shared_ptr<VectorCTParam> vector_ct_param;
    std::shared_ptr<BlindRotationPublicKey> blind_rotation_key;
    std::shared_ptr<LWEToLWEKeySwitchKey> ks_public_key; 
    std::shared_ptr<BlindRotateOutputBuilder> blind_rotate_output_builder;

    std::shared_ptr<Gadget> vector_ct_gadget;
    std::shared_ptr<LWEParam> lwe_param;
    std::shared_ptr<LWEGadgetSK> lwe_gadget_sk;

    /// @brief Parameters for the defauls plaintext encoding
    PlaintextEncoding default_encoding;
    PlaintextEncodingType plaintext_encoding_type;
    int64_t plaintext_space;

    /// @brief Additional Sanitization parameters
    SanitizationAlgorithm sanitization_alg;
    int32_t washing_cycles;

    BasicBootstrapBuilder();
     
    void set_ring_parameters(int64_t degree, int64_t coef_modulus, RingType ring_type, PolynomialArithmetic arithmetic);

    void set_vector_encryption_parameters(VectorEncryptionType vector_encyption_type, KeyDistribution key_distribution, double stddev);

    /// TODO: key_distriibution should be added in ring parameters, or separately (NTRU has ternary hardcoded for instance)
    void set_gadget_parameters(GadgetType gadget_type, int64_t gadget_decomp_base);

    void set_gadget_stddev(double gadget_stddev);

    void set_blind_rotation_algorithm(BlindRotationAlgorithm br_algorithm);

    void set_public_key_parameters(int64_t size, double stddev);

    void set_lwe_key_switching_parameters(int32_t dimension, int64_t lwe_modulus, KeyDistribution lwe_key_distribution, int64_t decomp_base, double lwe_stddev);

    void set_lwe_to_rlwe_keyswitch_parameters(int64_t lwe_to_rlwe_decomp_base);

    void set_full_domain_bootstrap_algorithm(FullDomainBootstrappingAlgorithm fdfb_algorithm);
 
    void set_default_plaintext_encoding(PlaintextEncodingType type, int64_t splaintext_space);
 

    void build();
 
    void build_secret_keys();

    void build_public_key();

    void build_vector_ct_gadget();

    void build_vector_ct_gadget_secret_key(); 

    void build_lwe_to_lwe_key_switching_key();

    void build_blind_rotation_key();

    void build_functional_bootstrap_key();

    void build_plaintext_encoding();
  
    void transfer_parameters(const BasicBootstrapBuilder& other);

    std::shared_ptr<FHEDeck::FHESecretKey> get_secret_key();

    void get_bootstrap_public_key(FHEDeck::PublicEvaluationKey& eval_key);
 

    /// @brief Sets the pointers to the secret key in other to the key in this, and marks the flag that the secret key is already generated.
    /// @param other The other builder object
    void transfer_secret_key(BasicBootstrapBuilder& other);
       
    /// @brief Sets the pointers to the key switching key in other to the key in this, and marks the flag that the key switching key is already generated.
    /// @param other 
    void transfer_key_switching_key(BasicBootstrapBuilder& other);

    /// @brief Sets the pointers to the public key in other to the key in this, and marks the flag that the key switching key is already generated.
    /// @param other 
    void transfer_public_key(BasicBootstrapBuilder& other);

    private:

    void setup_liu_micciancio_polyakov();

    void setup_kluczniak_shield_fdfb2();


};

 

class FHEConfiguration{ 
    
    public:   

    bool is_secret_key_set = false;
    std::shared_ptr<FHESecretKey> secret_key;
 
    PublicEvaluationKey eval_key;

    BasicBootstrapBuilder builder;
    BasicBootstrapBuilder sanitization_builder;
 
    FHEConfiguration() = default;

    FHEConfiguration(FHENamedParams name);
   
    void generate_keys();
 
    void build_sanitization_key(); 

    void init_tfhe_11_NTT(); 
  
    void init_tfhe_11_NTT_flood();
  
    void init_tfhe_11_flood();

    void init_tfhe_11_NTT_amortized(); 

    void init_tfhe_12_NTT_amortized();

    void init_lmp_12_NTT_amortized();

    void init_ntrunium_12_NTT(); 

    void init_tfhe_11_KS();

    void init_tfhe_11_KS_amortized();
 
}; 

} /// End of namespace FHEDeck

#endif