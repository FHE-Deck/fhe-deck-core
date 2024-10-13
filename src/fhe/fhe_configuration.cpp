#include "fhe_configuration.h"

using namespace fhe_deck;


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


void BasicBootstrapBuilder::transfer_parameters(BasicBootstrapBuilder& other){ 
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
    this->br_algorithm = other.br_algorithm; 
    this->fdfb_algorithm = other.fdfb_algorithm;
}

void BasicBootstrapBuilder::transfer_secret_key(BasicBootstrapBuilder& other){
    this->lwe_param = other.lwe_param;
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

void BasicBootstrapBuilder::build(){

    if(!is_gadget_vector_build){ 
        build_vector_ct_gadget();
        is_gadget_vector_build = true;
    }
    if(!is_secret_keys_build){ 
        build_secret_keys();
        is_gadget_vector_build = true;
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
     
}

void BasicBootstrapBuilder::build_secret_keys(){ 
    this->lwe_param = std::make_shared<LWEParam>(this->lwe_dim, this->lwe_modulus);  
    /// =================== Generate Secret keys   
    /// Generate GadgetLWE key. Its the LWE key for LWE-to-LWE-Key Switching.
    std::shared_ptr<LWESK> gadget_lwe = std::make_shared<LWESK>(lwe_param, this->lwe_stddev, KeyDistribution::binary); 
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
        blind_rotation_key = std::make_shared<CGGIBlindRotationKey>(secret_key->gadget_sk, lwe_gadget_sk->lwe);   
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

void BasicBootstrapBuilder::setup_liu_micciancio_polyakov(){ 
 
        if(this->vector_encyption_type == VectorEncryptionType::RLWE){  
            std::shared_ptr<RLWEParam> rlwe_param = std::static_pointer_cast<RLWEParam>(vector_ct_param);
            boot_acc_builder = std::shared_ptr<VectorCTAccumulatorBuilder>(new RLWEAccumulatorBuilder(rlwe_param));
            func_boot_acc_builder = std::shared_ptr<VectorCTAccumulatorBuilder>(new RLWEAccumulatorBuilder(rlwe_param));
            multivalue_acc_builder = std::make_shared<PolynomialSpecificationBuilder>(rlwe_param->size); 
        }else if(this->vector_encyption_type == VectorEncryptionType::NTRU){ 
            std::shared_ptr<NTRUGadgetSK> ntru_gadget_sk =  std::static_pointer_cast<NTRUGadgetSK>(secret_key->gadget_sk); 
            std::shared_ptr<NTRUParam> ntru_param = std::static_pointer_cast<NTRUParam>(vector_ct_param);
            boot_acc_builder = std::shared_ptr<VectorCTAccumulatorBuilder>(new NTRUAccumulatorBuilder(ntru_gadget_sk->sk));
            func_boot_acc_builder = std::shared_ptr<VectorCTAccumulatorBuilder>(new NTRUAccumulatorBuilder(ntru_gadget_sk->sk));
            multivalue_acc_builder = std::make_shared<PolynomialSpecificationBuilder>(ntru_param->size); 
        }
        else{
            throw std::logic_error(" BasicBootstrapBuilder::build(): liu_micciancio_polyakov doesn't support the given vector_encyption_type");
        } 
        std::shared_ptr<PreparedVectorCTAccumulators> prepared_acc_builder = std::make_shared<PreparedVectorCTAccumulators>(boot_acc_builder); 
        std::shared_ptr<LWEParam> lwe_param_rot(new LWEParam(lwe_dim, vector_ct_param->size * 2));  
        std::shared_ptr<LWEParam> lwe_param_tiny(new LWEParam(lwe_dim, vector_ct_param->size)); 
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
            func_boot_acc_builder = std::make_shared<KSFunctionSpecificationBuilder>(rlwe_param->size, rlwe_param->coef_modulus);
            multivalue_acc_builder = std::make_shared<KSFunctionSpecificationBuilder>(rlwe_param->size, rlwe_param->coef_modulus);
  
            std::shared_ptr<RLWEGadgetSK> rlwe_gadget_sk =  std::static_pointer_cast<RLWEGadgetSK>(secret_key->gadget_sk); 
            std::shared_ptr<Gadget> deter_gadget_rksk = std::shared_ptr<Gadget>(new SignedDecompositionGadget(degree, coef_modulus, lwe_to_rlwe_decomp_base));
            std::shared_ptr<RLWEGadgetSK> rlwe_gadget_sk_rksk = std::shared_ptr<RLWEGadgetSK>(new RLWEGadgetSK(deter_gadget_rksk, rlwe_gadget_sk->rlwe_sk));
            rlwe_ksk = std::make_shared<LWEToRLWEKeySwitchKey>(this->secret_key->lwe_sk, rlwe_gadget_sk_rksk);
        }else{
            throw std::logic_error(" BasicBootstrapBuilder::build(): kluczniak_shield_fdfb2 doesn't support the given vector_encyption_type");
        }  
        std::shared_ptr<PreparedVectorCTAccumulators> prepared_acc_builder = std::make_shared<PreparedVectorCTAccumulators>(boot_acc_builder);
        std::shared_ptr<LWEParam> lwe_param_rot(new LWEParam(lwe_dim, vector_ct_param->size * 2));
        std::shared_ptr<LWEParam> lwe_param_tiny(new LWEParam(lwe_dim, vector_ct_param->size * 2));
        bootstrap_pk = std::make_shared<KSFunctionalBootstrapPublicKey>( 
                lwe_param_rot, 
                blind_rotation_key,
                ks_public_key,
                rlwe_ksk,
                blind_rotate_output_builder,
                prepared_acc_builder);

}

 
/*
=========================================================== TFHEKeyGenerator (Named Parameters) ================================================= 
*/

FHEConfiguration::FHEConfiguration(FHENamedParams name){
    eval_key.name = name; 
}
   
void FHEConfiguration::generate_keys(){
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
 
  
void FHEConfiguration::init_tfhe_11_NTT(){ 
   
    builder.set_vector_encryption_parameters(VectorEncryptionType::RLWE, KeyDistribution ::ternary, 3.2);
    builder.set_ring_parameters(2048, 281474976694273, RingType::negacyclic, PolynomialArithmetic::ntt64);
    builder.set_gadget_parameters(GadgetType::signed_decomposition_gadget, 16777216);
    builder.set_lwe_key_switching_parameters(912, 281474976694273, KeyDistribution::binary, 128, 67108864);
    builder.set_blind_rotation_algorithm(BlindRotationAlgorithm::cggi_binary);
    builder.set_full_domain_bootstrap_algorithm(FullDomainBootstrappingAlgorithm::liu_micciancio_polyakov);
    builder.build(); 
    this->secret_key = builder.secret_key; 
    eval_key.boot_acc_builder = builder.boot_acc_builder;
    eval_key.func_boot_acc_builder = builder.func_boot_acc_builder;
    eval_key.multivalue_acc_builder = builder.multivalue_acc_builder;
    eval_key.bootstrap_pk = builder.bootstrap_pk;
    // Masking Key Gen 
    eval_key.default_encoding = PlaintextEncoding(PlaintextEncodingType::full_domain, 4, 281474976694273); 
    eval_key.encrypt_pk = std::shared_ptr<LWEPublicKey>(new LWEPublicKey(secret_key->lwe_sk, 8192, 8192)); 
 
    sanitization_builder.transfer_parameters(builder); 
    sanitization_builder.set_gadget_parameters(GadgetType::discrete_gaussian_gadget, 256);
    sanitization_builder.gadget_stddev = 225812; 

    sanitization_builder.transfer_key_switching_key(builder);
    sanitization_builder.transfer_secret_key(builder); 
 
    sanitization_builder.build(); 
    eval_key.sanitization_pk =  std::shared_ptr<SanitizationKey>(new KluczniakRandomizedBootstrapping(sanitization_builder.bootstrap_pk, eval_key.boot_acc_builder, eval_key.encrypt_pk));
    
    this->is_secret_key_set = true;
    eval_key.is_encrypt_pk_set = true;
    eval_key.is_bootstrap_pk_set = true;
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
    builder.build(); 
    this->secret_key = builder.secret_key; 
    eval_key.boot_acc_builder = builder.boot_acc_builder;
    eval_key.func_boot_acc_builder = builder.func_boot_acc_builder;
    eval_key.multivalue_acc_builder = builder.multivalue_acc_builder;
    eval_key.bootstrap_pk = builder.bootstrap_pk;
    // Masking Key Gen 
    eval_key.default_encoding = PlaintextEncoding(PlaintextEncodingType::full_domain, 4, 281474976694273); 
    eval_key.encrypt_pk = std::shared_ptr<LWEPublicKey>(new LWEPublicKey(secret_key->lwe_sk, 8192, 8192)); 

    // Now reset the Gadget to the randomized one  
    sanitization_builder.set_vector_encryption_parameters(VectorEncryptionType::RLWE, KeyDistribution::ternary, 3.2);
    sanitization_builder.set_ring_parameters(2048, 281474976694273, RingType::negacyclic, PolynomialArithmetic::ntt64);
    sanitization_builder.set_gadget_parameters(GadgetType::signed_decomposition_gadget, 256);
    sanitization_builder.gadget_stddev = 225812;
    sanitization_builder.set_lwe_key_switching_parameters(912, 281474976694273, KeyDistribution::binary, 128, 67108864);
    sanitization_builder.set_blind_rotation_algorithm(BlindRotationAlgorithm::cggi_binary);
    sanitization_builder.set_full_domain_bootstrap_algorithm(FullDomainBootstrappingAlgorithm::liu_micciancio_polyakov);

    sanitization_builder.transfer_key_switching_key(builder);
    sanitization_builder.transfer_secret_key(builder); 
      
    sanitization_builder.build(); 
    eval_key.sanitization_pk =  std::shared_ptr<SanitizationKey>(new DucasStehleWashingMachine(sanitization_builder.bootstrap_pk, eval_key.boot_acc_builder, eval_key.encrypt_pk, 4));
      
    this->is_secret_key_set = true;
    eval_key.is_encrypt_pk_set = true;
    eval_key.is_bootstrap_pk_set = true;
    eval_key.is_sanitization_supported = true;
} 
 
void FHEConfiguration::init_tfhe_11_flood(){ 
 
    builder.set_vector_encryption_parameters(VectorEncryptionType::RLWE, KeyDistribution::ternary, 3.2);
    builder.set_ring_parameters(2048, 68719476736, RingType::negacyclic, PolynomialArithmetic::double_fft);
    builder.set_gadget_parameters(GadgetType::signed_decomposition_gadget, 4096);
    builder.set_lwe_key_switching_parameters(912, 68719476736, KeyDistribution::binary, 128, 16384);
    builder.set_blind_rotation_algorithm(BlindRotationAlgorithm::cggi_binary);
    builder.set_full_domain_bootstrap_algorithm(FullDomainBootstrappingAlgorithm::liu_micciancio_polyakov);
    builder.build(); 
    this->secret_key = builder.secret_key; 
    eval_key.boot_acc_builder = builder.boot_acc_builder;
    eval_key.func_boot_acc_builder = builder.func_boot_acc_builder;
    eval_key.multivalue_acc_builder = builder.multivalue_acc_builder;
    eval_key.bootstrap_pk = builder.bootstrap_pk;
    // Masking Key Gen 
    eval_key.default_encoding = PlaintextEncoding(PlaintextEncodingType::full_domain, 4, 68719476736); 
    eval_key.encrypt_pk = std::shared_ptr<LWEPublicKey>(new LWEPublicKey(secret_key->lwe_sk, 3370, 4010391)); 
 
    this->is_secret_key_set = true;
    eval_key.is_encrypt_pk_set = true;
    eval_key.is_bootstrap_pk_set = true;
    eval_key.is_sanitization_supported = false;
} 

void FHEConfiguration::init_tfhe_11_NTT_amortized(){ 
  
    builder.set_vector_encryption_parameters(VectorEncryptionType::RLWE, KeyDistribution::ternary, 3.2);
    builder.set_ring_parameters(2048, 2251799813640193, RingType::negacyclic, PolynomialArithmetic::ntt64);
    builder.set_gadget_parameters(GadgetType::signed_decomposition_gadget, 262144);
    builder.set_lwe_key_switching_parameters(950, 2251799813640193, KeyDistribution::binary, 512, 262144);
    builder.set_blind_rotation_algorithm(BlindRotationAlgorithm::cggi_binary);
    builder.set_full_domain_bootstrap_algorithm(FullDomainBootstrappingAlgorithm::liu_micciancio_polyakov);
    builder.build(); 
    this->secret_key = builder.secret_key; 
    eval_key.boot_acc_builder = builder.boot_acc_builder;
    eval_key.func_boot_acc_builder = builder.func_boot_acc_builder;
    eval_key.multivalue_acc_builder = builder.multivalue_acc_builder;
    eval_key.bootstrap_pk = builder.bootstrap_pk;
    // Masking Key Gen 
    eval_key.default_encoding = PlaintextEncoding(PlaintextEncodingType::partial_domain, 8, 2251799813640193); 
    eval_key.encrypt_pk = std::shared_ptr<LWEPublicKey>(new LWEPublicKey(secret_key->lwe_sk, 8050, 8192)); 
 
    this->is_secret_key_set = true;
    eval_key.is_encrypt_pk_set = true;
    eval_key.is_bootstrap_pk_set = true;
    eval_key.is_sanitization_supported = false;
} 
 

void FHEConfiguration::init_tfhe_12_NTT_amortized(){  
 
    builder.set_vector_encryption_parameters(VectorEncryptionType::RLWE, KeyDistribution::ternary, 3.2);
    builder.set_ring_parameters(4096, 18014398509309953,  RingType::negacyclic, PolynomialArithmetic::ntt64);
    builder.set_gadget_parameters(GadgetType::signed_decomposition_gadget, 65536);
    builder.set_lwe_key_switching_parameters(950, 18014398509309953, KeyDistribution::binary, 512, 262144);
    builder.set_blind_rotation_algorithm(BlindRotationAlgorithm::cggi_binary);
    builder.set_full_domain_bootstrap_algorithm(FullDomainBootstrappingAlgorithm::liu_micciancio_polyakov);
    builder.build(); 
    this->secret_key = builder.secret_key; 
    eval_key.boot_acc_builder = builder.boot_acc_builder;
    eval_key.func_boot_acc_builder = builder.func_boot_acc_builder;
    eval_key.multivalue_acc_builder = builder.multivalue_acc_builder;
    eval_key.bootstrap_pk = builder.bootstrap_pk;
    // Masking Key Gen 
    eval_key.default_encoding = PlaintextEncoding(PlaintextEncodingType::partial_domain, 16, 18014398509309953); 
    eval_key.encrypt_pk = std::shared_ptr<LWEPublicKey>(new LWEPublicKey(secret_key->lwe_sk, 14936, 16384)); 
 
    this->is_secret_key_set = true;
    eval_key.is_encrypt_pk_set = true;
    eval_key.is_bootstrap_pk_set = true; 
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
    builder.build(); 
    this->secret_key = builder.secret_key; 
    eval_key.boot_acc_builder = builder.boot_acc_builder;
    eval_key.func_boot_acc_builder = builder.func_boot_acc_builder;
    eval_key.multivalue_acc_builder = builder.multivalue_acc_builder;
    eval_key.bootstrap_pk = builder.bootstrap_pk;
    // Masking Key Gen 
    eval_key.default_encoding = PlaintextEncoding(PlaintextEncodingType::full_domain, 32, 281474976694273); 
    eval_key.encrypt_pk = std::shared_ptr<LWEPublicKey>(new LWEPublicKey(secret_key->lwe_sk, 14936, 16384)); 
 
    this->is_secret_key_set = true;
    eval_key.is_encrypt_pk_set = true;
    eval_key.is_bootstrap_pk_set = true;
    eval_key.is_sanitization_supported = false;
} 



void FHEConfiguration::init_ntrunium_12_NTT(){ 
   
    builder.set_vector_encryption_parameters(VectorEncryptionType::NTRU, KeyDistribution::ternary, 1/4.0);
    builder.set_ring_parameters(4096, 35184371884033, RingType::negacyclic, PolynomialArithmetic::ntt64);
    builder.set_gadget_parameters(GadgetType::signed_decomposition_gadget,  32768);
    builder.set_lwe_key_switching_parameters(750, 35184371884033, KeyDistribution::binary, 2, 16384);
    builder.set_blind_rotation_algorithm(BlindRotationAlgorithm::cggi_binary);
    builder.set_full_domain_bootstrap_algorithm(FullDomainBootstrappingAlgorithm::liu_micciancio_polyakov);
    builder.build(); 
    this->secret_key = builder.secret_key; 
    eval_key.boot_acc_builder = builder.boot_acc_builder;
    eval_key.func_boot_acc_builder = builder.func_boot_acc_builder;
    eval_key.multivalue_acc_builder = builder.multivalue_acc_builder;
    eval_key.bootstrap_pk = builder.bootstrap_pk;
    // Masking Key Gen 
    eval_key.default_encoding = PlaintextEncoding(PlaintextEncodingType::full_domain, 4, 35184371884033); 
    eval_key.encrypt_pk = std::shared_ptr<LWEPublicKey>(new LWEPublicKey(secret_key->lwe_sk, 8192, 8192)); 
  
    this->is_secret_key_set = true;
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
    builder.build(); 
    this->secret_key = builder.secret_key; 
    eval_key.boot_acc_builder = builder.boot_acc_builder;
    eval_key.func_boot_acc_builder = builder.func_boot_acc_builder;
    eval_key.multivalue_acc_builder = builder.multivalue_acc_builder;
    eval_key.bootstrap_pk = builder.bootstrap_pk;
    // Masking Key Gen 
    eval_key.default_encoding = PlaintextEncoding(PlaintextEncodingType::full_domain, 32, 2251799813640193); 
    eval_key.encrypt_pk = std::shared_ptr<LWEPublicKey>(new LWEPublicKey(secret_key->lwe_sk, 3370, 3.19)); 
 
    this->is_secret_key_set = true;
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
    builder.build(); 
    this->secret_key = builder.secret_key; 
    eval_key.boot_acc_builder = builder.boot_acc_builder;
    eval_key.func_boot_acc_builder = builder.func_boot_acc_builder;
    eval_key.multivalue_acc_builder = builder.multivalue_acc_builder;
    eval_key.bootstrap_pk = builder.bootstrap_pk;
    // Masking Key Gen 
    eval_key.default_encoding = PlaintextEncoding(PlaintextEncodingType::full_domain, 32, 4503599627366401); 
    eval_key.encrypt_pk = std::shared_ptr<LWEPublicKey>(new LWEPublicKey(secret_key->lwe_sk, 3370, 3.19)); 
 
    this->is_secret_key_set = true;
    eval_key.is_encrypt_pk_set = true;
    eval_key.is_bootstrap_pk_set = true;
    eval_key.is_sanitization_supported = false;
}

