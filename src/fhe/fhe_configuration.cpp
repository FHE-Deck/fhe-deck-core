#include "fhe/fhe_configuration.h"

using namespace FHEDeck;


BasicBootstrapBuilder::BasicBootstrapBuilder(){
    this->secret_key = std::make_shared<FHESecretKey>();
}
 
void BasicBootstrapBuilder::set_ring_parameters(int64_t degree, int64_t coef_modulus,RingType ring_type, PolynomialArithmetic arithmetic){
    this->degree = degree;
    this->coef_modulus = coef_modulus;
    this->ring_type = ring_type;
    this->arithmetic = arithmetic;
}

void BasicBootstrapBuilder::set_vector_encryption_parameters(VectorEncryptionType vector_encyption_type, KeyDistribution key_distribution, double stddev){
    this->vector_encyption_type = vector_encyption_type;
    this->key_distribution = key_distribution;
    this->stddev = stddev;
}

void BasicBootstrapBuilder::set_gadget_parameters(GadgetType gadget_type, int64_t gadget_decomp_base){
    this->gadget_type = gadget_type;
    this->gadget_decomp_base = gadget_decomp_base;
}

void BasicBootstrapBuilder::set_gadget_stddev(double gadget_stddev){
    this->gadget_stddev = gadget_stddev;
}

void BasicBootstrapBuilder::set_lwe_key_switching_parameters(int32_t dimension, int64_t lwe_modulus, KeyDistribution lwe_key_distribution, int64_t decomp_base, double lwe_stddev){
    this->lwe_dim = dimension;
    this->lwe_modulus = lwe_modulus;
    this->lwe_key_distribution = lwe_key_distribution;
    this->lwe_ks_decomp_base = decomp_base;
    this->lwe_stddev = lwe_stddev;
}

 

void BasicBootstrapBuilder::set_full_domain_bootstrap_algorithm(FullDomainBootstrappingAlgorithm fdfb_algorithm){
    this->fdfb_algorithm = fdfb_algorithm;
}

void BasicBootstrapBuilder::set_lwe_to_rlwe_keyswitch_parameters(int64_t lwe_to_rlwe_decomp_base){
    this->lwe_to_rlwe_decomp_base = lwe_to_rlwe_decomp_base;
}

void BasicBootstrapBuilder::set_blind_rotation_algorithm(BlindRotationAlgorithm br_algorithm){
    this->br_algorithm = br_algorithm;
}

void BasicBootstrapBuilder::set_public_key_parameters(int64_t size, double stddev){
    this->pk_size = size;
    this->pk_stddev = stddev;
}

void BasicBootstrapBuilder::set_default_plaintext_encoding(PlaintextEncodingType plaintext_encoding_type, int64_t plaintext_space){
    this->plaintext_encoding_type = plaintext_encoding_type;
    this->plaintext_space = plaintext_space;
}

void BasicBootstrapBuilder::transfer_parameters(const BasicBootstrapBuilder& other){ 
    this->degree = other.degree;
    this->coef_modulus = other.coef_modulus;
    this->stddev = other.stddev;   
    this->ring_type = other.ring_type;
    this->arithmetic = other.arithmetic;
    this->vector_ct_secret_key = other.vector_ct_secret_key; 
    this->gadget_type = other.gadget_type;
    this->gadget_decomp_base = other.gadget_decomp_base;
    this->vector_encyption_type = other.vector_encyption_type; 
    this->key_distribution = other.key_distribution; 
    this->gadget_stddev = other.gadget_stddev;  
    this->lwe_dim = other.lwe_dim;
    this->lwe_modulus = other.lwe_modulus;
    this->lwe_ks_decomp_base = other.lwe_ks_decomp_base;
    this->lwe_stddev = other.lwe_stddev; 
    this->lwe_key_distribution = other.lwe_key_distribution;  
    this->lwe_to_rlwe_decomp_base = other.lwe_to_rlwe_decomp_base;
    this->pk_size = other.pk_size; 
    this->pk_stddev = pk_stddev; 
    this->br_algorithm = other.br_algorithm; 
    this->fdfb_algorithm = other.fdfb_algorithm; 
    this->plaintext_encoding_type  = other.plaintext_encoding_type;
    this->plaintext_space = other.plaintext_space;
}

void BasicBootstrapBuilder::transfer_secret_key(BasicBootstrapBuilder& other){
    this->lwe_param = other.lwe_param;
    this->gadget_lwe = other.gadget_lwe;
    this->lwe_gadget_sk = other.lwe_gadget_sk;
    this->secret_key->lwe_sk = other.secret_key->lwe_sk;
    this->vector_ct_param = other.vector_ct_param;
    this->vector_ct_secret_key = other.vector_ct_secret_key;
    this->blind_rotate_output_builder = other.blind_rotate_output_builder;
    this->is_secret_keys_build = true;
}
        
void BasicBootstrapBuilder::transfer_key_switching_key(BasicBootstrapBuilder& other){
    this->ks_public_key = other.ks_public_key;
    this->is_lwe_to_lwe_keyswitch_build = true; 
}

void BasicBootstrapBuilder::transfer_public_key(BasicBootstrapBuilder& other){
    this->encrypt_pk = other.encrypt_pk;
    this->is_public_key_build = true;
}

void BasicBootstrapBuilder::build(){

    if(!is_gadget_vector_build){ 
        build_vector_ct_gadget();
        is_gadget_vector_build = true;
    }
    if(!is_secret_keys_build){ 
        build_secret_keys();
        is_gadget_vector_build = true;
    }
    if(!is_public_key_build){
        build_public_key();
        is_public_key_build = true;
    }
    if(!is_vector_ct_gadget_secret_key_build){
        build_vector_ct_gadget_secret_key();
        is_vector_ct_gadget_secret_key_build = true;
    }
    if(!is_blind_rotation_key_build){ 
        build_blind_rotation_key();
        is_blind_rotation_key_build = true;
    }
    if(!is_lwe_to_lwe_keyswitch_build){ 
        build_lwe_to_lwe_key_switching_key();
        is_lwe_to_lwe_keyswitch_build = true;
    }
    if(!is_functional_bootstrap_build){ 
        build_functional_bootstrap_key();
        is_lwe_to_lwe_keyswitch_build = true;
    }
    if(!is_plaintext_encoding_build){
        build_plaintext_encoding();
        is_plaintext_encoding_build = true;
    }
     
}

void BasicBootstrapBuilder::build_secret_keys(){ 
    this->lwe_param = std::make_shared<LWEParam>(this->lwe_dim, this->lwe_modulus);  
    /// =================== Generate Secret keys   
    /// Generate GadgetLWE key. Its the LWE key for LWE-to-LWE-Key Switching.
    gadget_lwe = std::make_shared<LWESK>(lwe_param, this->lwe_stddev, KeyDistribution::binary); 
    this->lwe_gadget_sk = std::make_shared<LWEGadgetSK>(gadget_lwe, lwe_ks_decomp_base);  
    /// Generate Keys for the blind rotation gadget
    if(this->vector_encyption_type == VectorEncryptionType::RLWE){ 
        std::shared_ptr<RLWEParam> rlwe_param = std::make_shared<RLWEParam>(this->ring_type, this->degree, this->coef_modulus, this->arithmetic); 
        this->vector_ct_param = rlwe_param;
        std::shared_ptr<RLWESK> rlwe = std::make_shared<RLWESK>(rlwe_param, this->key_distribution, this->stddev); 
        this->secret_key->lwe_sk = std::shared_ptr<LWESK>(rlwe->extract_lwe_key());   
        this->blind_rotate_output_builder = std::make_shared<RLWEBlindRotateOutputBuilder>(std::static_pointer_cast<RLWEParam>(vector_ct_param));
        this->vector_ct_secret_key = rlwe;
   
    }else if(this->vector_encyption_type == VectorEncryptionType::NTRU){
        std::shared_ptr<NTRUParam> ntru_param = std::make_shared<NTRUParam>(this->ring_type, this->degree, this->coef_modulus, this->arithmetic); 
        this->vector_ct_param = ntru_param;
        std::shared_ptr<NTRUSK> ntru_sk = std::make_shared<NTRUSK>(ntru_param, this->stddev);  
        this->secret_key->lwe_sk = std::shared_ptr<LWESK>(ntru_sk->extract_lwe_key());   
        this->blind_rotate_output_builder = std::make_shared<NTRUBlindRotateOutputBuilder>(std::static_pointer_cast<NTRUParam>(vector_ct_param));
        this->vector_ct_secret_key = ntru_sk;
 
    } else{
        throw std::logic_error("BasicBootstrapBuilder::build() Unrecognized Vector Encryption Type");
    }
}
 

void BasicBootstrapBuilder::build_public_key(){
    this->encrypt_pk =std::make_shared<LWEPublicKey>(secret_key->lwe_sk, this->pk_size, this->pk_stddev); 
}

void BasicBootstrapBuilder::build_vector_ct_gadget(){
    if(gadget_type == GadgetType::signed_decomposition_gadget){
        vector_ct_gadget = std::make_shared<SignedDecompositionGadget>(this->degree, this->coef_modulus, this->gadget_decomp_base);
    }else if(gadget_type == GadgetType::discrete_gaussian_gadget){
        vector_ct_gadget = std::make_shared<DiscreteGaussianSamplingGadget>(this->degree, this->coef_modulus, this->gadget_decomp_base, this->gadget_stddev);
    }else{
        throw std::logic_error("BasicBootstrapBuilder::build() Unrecognized Gadget Type");
    }
}
 
void BasicBootstrapBuilder::build_vector_ct_gadget_secret_key(){ 
    if(this->vector_encyption_type == VectorEncryptionType::RLWE){   
        std::shared_ptr<RLWESK> rlwe_sk = std::static_pointer_cast<RLWESK>(vector_ct_secret_key);
        secret_key->gadget_sk = std::make_shared<RLWEGadgetSK>(vector_ct_gadget, rlwe_sk);   

    }else if(this->vector_encyption_type == VectorEncryptionType::NTRU){  
        std::shared_ptr<NTRUSK> ntru_sk = std::static_pointer_cast<NTRUSK>(vector_ct_secret_key);
        secret_key->gadget_sk = std::make_shared<NTRUGadgetSK>(vector_ct_gadget, ntru_sk);   
    } else{
        throw std::logic_error("BasicBootstrapBuilder::build() Unrecognized Vector Encryption Type");
    }
}

void BasicBootstrapBuilder::build_blind_rotation_key(){ 
    if(this->br_algorithm == BlindRotationAlgorithm::cggi_binary){ 
        blind_rotation_key = std::make_shared<CGGIBlindRotationKey>(secret_key->gadget_sk, gadget_lwe);   
    }else{
        throw std::logic_error("BasicBootstrapBuilder::build() Unrecognized Blind Rotation Algorithm");
    }
}

void BasicBootstrapBuilder::build_lwe_to_lwe_key_switching_key(){ 
    ks_public_key = std::make_shared<LWEToLWEKeySwitchKey>(secret_key->lwe_sk, lwe_gadget_sk); 
}

void BasicBootstrapBuilder::build_functional_bootstrap_key(){
    // Build the public key  
    if(fdfb_algorithm == FullDomainBootstrappingAlgorithm::liu_micciancio_polyakov){
        setup_liu_micciancio_polyakov();
    }else if(fdfb_algorithm == FullDomainBootstrappingAlgorithm::kluczniak_shield_fdfb2){ 
        setup_kluczniak_shield_fdfb2();
    }else{
        throw std::logic_error("BasicBootstrapBuilder::build() Unrecognized Full Domain Bootstrapping Algorithm");
    }
}

void BasicBootstrapBuilder::build_plaintext_encoding(){ 
    this->default_encoding = PlaintextEncoding(this->plaintext_encoding_type, this->plaintext_space, encrypt_pk->param()->modulus()); 
}

void BasicBootstrapBuilder::setup_liu_micciancio_polyakov(){ 
 
        if(this->vector_encyption_type == VectorEncryptionType::RLWE){  
            std::shared_ptr<RLWEParam> rlwe_param = std::static_pointer_cast<RLWEParam>(vector_ct_param);
            boot_acc_builder = std::shared_ptr<VectorCTAccumulatorBuilder>(new RLWEAccumulatorBuilder(rlwe_param));
            func_boot_acc_builder = std::shared_ptr<VectorCTAccumulatorBuilder>(new RLWEAccumulatorBuilder(rlwe_param));
            multivalue_acc_builder = std::make_shared<PolynomialSpecificationBuilder>(rlwe_param->size()); 
        }else if(this->vector_encyption_type == VectorEncryptionType::NTRU){ 
            std::shared_ptr<NTRUGadgetSK> ntru_gadget_sk =  std::static_pointer_cast<NTRUGadgetSK>(secret_key->gadget_sk); 
            std::shared_ptr<NTRUParam> ntru_param = std::static_pointer_cast<NTRUParam>(vector_ct_param);
            std::shared_ptr<NTRUSK> sk = std::static_pointer_cast<NTRUSK>(vector_ct_secret_key);
            boot_acc_builder = std::shared_ptr<VectorCTAccumulatorBuilder>(new NTRUAccumulatorBuilder(sk));
            func_boot_acc_builder = std::shared_ptr<VectorCTAccumulatorBuilder>(new NTRUAccumulatorBuilder(sk));
            multivalue_acc_builder = std::make_shared<PolynomialSpecificationBuilder>(ntru_param->size()); 
        }
        else{
            throw std::logic_error(" BasicBootstrapBuilder::build(): liu_micciancio_polyakov doesn't support the given vector_encyption_type");
        } 
        std::shared_ptr<PreparedVectorCTAccumulators> prepared_acc_builder = std::make_shared<PreparedVectorCTAccumulators>(boot_acc_builder); 
        std::shared_ptr<LWEParam> lwe_param_rot(new LWEParam(lwe_dim, vector_ct_param->size() * 2));  
        std::shared_ptr<LWEParam> lwe_param_tiny(new LWEParam(lwe_dim, vector_ct_param->size())); 
        bootstrap_pk = std::make_shared<LMPFunctionalBootstrapPublicKey>(
            lwe_param_rot, 
            lwe_param_tiny,
            blind_rotation_key, 
            ks_public_key, 
            blind_rotate_output_builder, 
            prepared_acc_builder);
}

void BasicBootstrapBuilder::setup_kluczniak_shield_fdfb2(){

        std::shared_ptr<LWEToRLWEKeySwitchKey> rlwe_ksk;
        if(this->vector_encyption_type == VectorEncryptionType::RLWE){ 
            // Init Accumulator Builder and Blind Rotation Output Builder
            std::shared_ptr<RLWEParam> rlwe_param = std::static_pointer_cast<RLWEParam>(vector_ct_param);
            boot_acc_builder = std::shared_ptr<VectorCTAccumulatorBuilder>(new RLWEAccumulatorBuilder(rlwe_param));
            func_boot_acc_builder = std::make_shared<KSFunctionSpecificationBuilder>(rlwe_param->size(), rlwe_param->modulus());
            multivalue_acc_builder = std::make_shared<KSFunctionSpecificationBuilder>(rlwe_param->size(), rlwe_param->modulus());
  
            std::shared_ptr<RLWEGadgetSK> rlwe_gadget_sk =  std::static_pointer_cast<RLWEGadgetSK>(secret_key->gadget_sk); 
            std::shared_ptr<RLWESK> rlwe_sk = std::static_pointer_cast<RLWESK>(vector_ct_secret_key);
            std::shared_ptr<Gadget> deter_gadget_rksk = std::make_shared<SignedDecompositionGadget>(degree, coef_modulus, lwe_to_rlwe_decomp_base);
            std::shared_ptr<RLWEGadgetSK> rlwe_gadget_sk_rksk = std::make_shared<RLWEGadgetSK>(deter_gadget_rksk, rlwe_sk);
            rlwe_ksk = std::make_shared<LWEToRLWEKeySwitchKey>(*this->secret_key->lwe_sk, *rlwe_gadget_sk_rksk);
        }else{
            throw std::logic_error(" BasicBootstrapBuilder::build(): kluczniak_shield_fdfb2 doesn't support the given vector_encyption_type");
        }  
        std::shared_ptr<PreparedVectorCTAccumulators> prepared_acc_builder = std::make_shared<PreparedVectorCTAccumulators>(boot_acc_builder);
        std::shared_ptr<LWEParam> lwe_param_rot(new LWEParam(lwe_dim, vector_ct_param->size() * 2));
        std::shared_ptr<LWEParam> lwe_param_tiny(new LWEParam(lwe_dim, vector_ct_param->size() * 2));
        bootstrap_pk = std::make_shared<KSFunctionalBootstrapPublicKey>( 
                lwe_param_rot, 
                blind_rotation_key,
                ks_public_key,
                rlwe_ksk,
                blind_rotate_output_builder,
                prepared_acc_builder);

}

 std::shared_ptr<FHESecretKey> BasicBootstrapBuilder::get_secret_key(){
    return this->secret_key;
 }

void BasicBootstrapBuilder::get_bootstrap_public_key(PublicEvaluationKey& eval_key){
    if(is_blind_rotation_key_build){
        eval_key.boot_acc_builder = this->boot_acc_builder;
        eval_key.func_boot_acc_builder = this->func_boot_acc_builder;
        eval_key.multivalue_acc_builder = this->multivalue_acc_builder;
        eval_key.bootstrap_pk = this->bootstrap_pk; 
        eval_key.is_bootstrap_pk_set = true;
    } 
    if(is_public_key_build){ 
        eval_key.encrypt_pk = this->encrypt_pk;
        eval_key.is_encrypt_pk_set = true;
    }
    eval_key.default_encoding = this->default_encoding;
}

 
/*
=========================================================== TFHEKeyGenerator (Named Parameters) ================================================= 
*/

FHEConfiguration::FHEConfiguration(FHENamedParams name){
    eval_key.name = name; 
    if(eval_key.name == FHENamedParams::tfhe_11_flood){
        init_tfhe_11_flood();
    } else if(eval_key.name == FHENamedParams::tfhe_11_NTT){
        init_tfhe_11_NTT();
    }else if(eval_key.name == FHENamedParams::tfhe_11_NTT_flood){
        init_tfhe_11_NTT_flood();
    }else if(eval_key.name == FHENamedParams::tfhe_11_NTT_amortized){
        init_tfhe_11_NTT_amortized();
    }else if(eval_key.name == FHENamedParams::tfhe_12_NTT_amortized){
        init_tfhe_12_NTT_amortized();
    }else if(eval_key.name == FHENamedParams::ntrunium_12_NTT){
        init_ntrunium_12_NTT();
    }else if (eval_key.name == FHENamedParams::tfhe_11_KS) {
        init_tfhe_11_KS();
    }else if (eval_key.name == FHENamedParams::tfhe_11_KS_amortized){
        init_tfhe_11_KS_amortized();
    }else if (eval_key.name == FHENamedParams::lmp_12_NTT_amortized){
        init_lmp_12_NTT_amortized();
    }
    else{ 
        throw std::runtime_error("TFHEKeyGenerator::TFHEKeyGenerator: Parameter set note supported! Perhaps the chosen parameter set requires additional dependencies to be compiled?"); 
    }
    
}
   
void FHEConfiguration::generate_keys(){
    builder.build(); 
    this->secret_key = builder.get_secret_key();
    this->is_secret_key_set = true;
    builder.get_bootstrap_public_key(eval_key);  
    this->is_eval_key_set = true;
    build_sanitization_key();
}

void FHEConfiguration::build_sanitization_key(){
    if(!eval_key.is_sanitization_supported){
        return;
    }
    sanitization_builder.transfer_key_switching_key(builder);
    sanitization_builder.transfer_secret_key(builder);  
    sanitization_builder.transfer_public_key(builder);
    sanitization_builder.build(); 
    if(sanitization_builder.sanitization_alg == SanitizationAlgorithm::kluczniak){
        eval_key.sanitization_pk =  std::shared_ptr<SanitizationKey>(new KluczniakRandomizedBootstrapping(sanitization_builder.bootstrap_pk, eval_key.boot_acc_builder, eval_key.encrypt_pk));
    }else if(sanitization_builder.sanitization_alg == SanitizationAlgorithm::ducas_stehle){
      
        eval_key.sanitization_pk =  std::shared_ptr<SanitizationKey>(new DucasStehleWashingMachine(sanitization_builder.bootstrap_pk, eval_key.boot_acc_builder, eval_key.encrypt_pk, sanitization_builder.washing_cycles));  
    }else{
        throw std::logic_error("Unsupported SanitizationAlgorithm");
    }
}
 
  
void FHEConfiguration::init_tfhe_11_NTT(){ 
   
    builder.set_vector_encryption_parameters(VectorEncryptionType::RLWE, KeyDistribution ::ternary, 3.2);
    builder.set_ring_parameters(2048, 281474976694273, RingType::negacyclic, PolynomialArithmetic::ntt64); 
    builder.set_gadget_parameters(GadgetType::signed_decomposition_gadget, 16777216);
    builder.set_lwe_key_switching_parameters(912, 281474976694273, KeyDistribution::binary, 128, 67108864);
    builder.set_blind_rotation_algorithm(BlindRotationAlgorithm::cggi_binary);
    builder.set_full_domain_bootstrap_algorithm(FullDomainBootstrappingAlgorithm::liu_micciancio_polyakov);
    builder.set_public_key_parameters(8192, 8192);
    builder.set_default_plaintext_encoding(PlaintextEncodingType::full_domain, 4);
    
    sanitization_builder.sanitization_alg = SanitizationAlgorithm::kluczniak;
    sanitization_builder.transfer_parameters(builder); 
    sanitization_builder.set_gadget_parameters(GadgetType::discrete_gaussian_gadget, 256);
    sanitization_builder.gadget_stddev = 225812; 
    
    eval_key.is_sanitization_supported = true;
 
}  

void FHEConfiguration::init_tfhe_11_NTT_flood(){ 
 
    //BasicBootstrapBuilder builder;
    builder.set_vector_encryption_parameters(VectorEncryptionType::RLWE, KeyDistribution::ternary, 3.2);
    builder.set_ring_parameters(2048, 281474976694273, RingType::negacyclic, PolynomialArithmetic::ntt64);
    builder.set_gadget_parameters(GadgetType::signed_decomposition_gadget, 16777216);
    builder.set_lwe_key_switching_parameters(912, 281474976694273, KeyDistribution::binary, 128, 67108864);
    builder.set_blind_rotation_algorithm(BlindRotationAlgorithm::cggi_binary);
    builder.set_full_domain_bootstrap_algorithm(FullDomainBootstrappingAlgorithm::liu_micciancio_polyakov);
    builder.set_public_key_parameters(8192, 8192);
    builder.set_default_plaintext_encoding(PlaintextEncodingType::full_domain, 4);
    
    // Now reset the Gadget to the randomized one   
    sanitization_builder.transfer_parameters(builder);
    sanitization_builder.sanitization_alg = SanitizationAlgorithm::ducas_stehle; 
    sanitization_builder.washing_cycles = 4;
    sanitization_builder.set_gadget_parameters(GadgetType::signed_decomposition_gadget, 256);
    sanitization_builder.gadget_stddev = 225812; 
    
    eval_key.is_sanitization_supported = true;
} 
 
 
void FHEConfiguration::init_tfhe_11_flood(){ 
 
    builder.set_vector_encryption_parameters(VectorEncryptionType::RLWE, KeyDistribution::ternary, 3.2);
    builder.set_ring_parameters(2048, 68719476736, RingType::negacyclic, PolynomialArithmetic::double_fft);
    builder.set_gadget_parameters(GadgetType::signed_decomposition_gadget, 4096);
    builder.set_lwe_key_switching_parameters(912, 68719476736, KeyDistribution::binary, 128, 16384);
    builder.set_blind_rotation_algorithm(BlindRotationAlgorithm::cggi_binary);
    builder.set_full_domain_bootstrap_algorithm(FullDomainBootstrappingAlgorithm::liu_micciancio_polyakov);
    builder.set_public_key_parameters(3370, 4010391);
    builder.set_default_plaintext_encoding(PlaintextEncodingType::full_domain, 4);
    
    eval_key.is_sanitization_supported = false;
} 

void FHEConfiguration::init_tfhe_11_NTT_amortized(){ 
  
    builder.set_vector_encryption_parameters(VectorEncryptionType::RLWE, KeyDistribution::ternary, 3.2);
    builder.set_ring_parameters(2048, 2251799813640193, RingType::negacyclic, PolynomialArithmetic::ntt64);
    builder.set_gadget_parameters(GadgetType::signed_decomposition_gadget, 262144);
    builder.set_lwe_key_switching_parameters(950, 2251799813640193, KeyDistribution::binary, 512, 262144);
    builder.set_blind_rotation_algorithm(BlindRotationAlgorithm::cggi_binary);
    builder.set_full_domain_bootstrap_algorithm(FullDomainBootstrappingAlgorithm::liu_micciancio_polyakov);
    builder.set_public_key_parameters(8050, 8192);
    builder.set_default_plaintext_encoding(PlaintextEncodingType::partial_domain, 8);
    
    eval_key.is_sanitization_supported = false;
} 
 

void FHEConfiguration::init_tfhe_12_NTT_amortized(){  
 
    builder.set_vector_encryption_parameters(VectorEncryptionType::RLWE, KeyDistribution::ternary, 3.2);
    builder.set_ring_parameters(4096, 18014398509309953,  RingType::negacyclic, PolynomialArithmetic::ntt64);
    builder.set_gadget_parameters(GadgetType::signed_decomposition_gadget, 65536);
    builder.set_lwe_key_switching_parameters(950, 18014398509309953, KeyDistribution::binary, 512, 262144);
    builder.set_blind_rotation_algorithm(BlindRotationAlgorithm::cggi_binary);
    builder.set_full_domain_bootstrap_algorithm(FullDomainBootstrappingAlgorithm::liu_micciancio_polyakov);
    builder.set_public_key_parameters(14936, 16384);
    builder.set_default_plaintext_encoding(PlaintextEncodingType::partial_domain, 16);
    
    eval_key.is_sanitization_supported = false;
} 
 
/// TODO: I think this parameter set was only for a paper test. Actually could be derived from the init_tfhe_12_NTT_amortized set.
void FHEConfiguration::init_lmp_12_NTT_amortized(){  
  
    builder.set_vector_encryption_parameters(VectorEncryptionType::RLWE, KeyDistribution::ternary, 3.2);
    builder.set_ring_parameters(4096, 281474976694273, RingType::negacyclic, PolynomialArithmetic::ntt64);
    builder.set_gadget_parameters(GadgetType::signed_decomposition_gadget, 1 << 12);
    builder.set_lwe_key_switching_parameters(900, 281474976694273, KeyDistribution::binary, 1 << 3, 3.2);
    builder.set_blind_rotation_algorithm(BlindRotationAlgorithm::cggi_binary);
    builder.set_full_domain_bootstrap_algorithm(FullDomainBootstrappingAlgorithm::liu_micciancio_polyakov);
    builder.set_public_key_parameters(14936, 16384);
    builder.set_default_plaintext_encoding(PlaintextEncodingType::full_domain, 32); 

    eval_key.is_sanitization_supported = false;
} 



void FHEConfiguration::init_ntrunium_12_NTT(){ 
   
    builder.set_vector_encryption_parameters(VectorEncryptionType::NTRU, KeyDistribution::ternary, 1/4.0);
    builder.set_ring_parameters(4096, 35184371884033, RingType::negacyclic, PolynomialArithmetic::ntt64);
    builder.set_gadget_parameters(GadgetType::signed_decomposition_gadget,  32768);
    builder.set_lwe_key_switching_parameters(750, 35184371884033, KeyDistribution::binary, 2, 16384);
    builder.set_blind_rotation_algorithm(BlindRotationAlgorithm::cggi_binary);
    builder.set_full_domain_bootstrap_algorithm(FullDomainBootstrappingAlgorithm::liu_micciancio_polyakov);
    builder.set_public_key_parameters(8192, 8192);
    builder.set_default_plaintext_encoding(PlaintextEncodingType::full_domain, 4); 
   
    eval_key.is_encrypt_pk_set = true;
    eval_key.is_bootstrap_pk_set = true;
    eval_key.is_sanitization_supported = false;
} 
  

void FHEConfiguration::init_tfhe_11_KS() {
 
    builder.set_vector_encryption_parameters(VectorEncryptionType::RLWE, KeyDistribution::ternary, 3.19);
    builder.set_ring_parameters(2048, 2251799813640193,  RingType::negacyclic, PolynomialArithmetic::ntt64);
    builder.set_gadget_parameters(GadgetType::signed_decomposition_gadget, 1 << 17);
    builder.set_lwe_key_switching_parameters(900, 2251799813640193, KeyDistribution::binary, 1<<2, 1 << 12);
    builder.set_lwe_to_rlwe_keyswitch_parameters(1 << 4);
    builder.set_blind_rotation_algorithm(BlindRotationAlgorithm::cggi_binary);
    builder.set_full_domain_bootstrap_algorithm(FullDomainBootstrappingAlgorithm::kluczniak_shield_fdfb2);
    builder.set_public_key_parameters(3370, 3.19); 
    builder.set_default_plaintext_encoding(PlaintextEncodingType::full_domain, 31); 
  
    eval_key.is_encrypt_pk_set = true;
    eval_key.is_bootstrap_pk_set = true;
    eval_key.is_sanitization_supported = false;
}


void FHEConfiguration::init_tfhe_11_KS_amortized() {
 
    builder.set_vector_encryption_parameters(VectorEncryptionType::RLWE, KeyDistribution::ternary, 3.19);
    builder.set_ring_parameters(2048, 4503599627366401, RingType::negacyclic, PolynomialArithmetic::ntt64);
    builder.set_gadget_parameters(GadgetType::signed_decomposition_gadget, 1 << 13);
    builder.set_lwe_key_switching_parameters(900, 4503599627366401, KeyDistribution::binary, 1<<2, 1 << 12);
    builder.set_lwe_to_rlwe_keyswitch_parameters(1 << 4);
    builder.set_blind_rotation_algorithm(BlindRotationAlgorithm::cggi_binary);
    builder.set_full_domain_bootstrap_algorithm(FullDomainBootstrappingAlgorithm::kluczniak_shield_fdfb2);
    builder.set_public_key_parameters(3370, 3.19);
    builder.set_default_plaintext_encoding(PlaintextEncodingType::full_domain, 33); 
  
    eval_key.is_encrypt_pk_set = true;
    eval_key.is_bootstrap_pk_set = true;
    eval_key.is_sanitization_supported = false;
}

