#include "fhe_configuration.h"

using namespace fhe_deck;

/*
=========================================================== TFHEKeyGenerator (Named Parameters) =================================================

*/

FHEConfiguration::FHEConfiguration(FHENamedParams name){
    this->name = name; 
}
   
void FHEConfiguration::generate_keys(){
    if(this->name == FHENamedParams::tfhe_11_B){
        init_tfhe_11_B();
    } else if(this->name == FHENamedParams::tfhe_11_flood){
        init_tfhe_11_flood();
    } else if(this->name == FHENamedParams::tfhe_11_NTT){
        init_tfhe_11_NTT();
    }else if(this->name == FHENamedParams::tfhe_11_NTT_flood){
        init_tfhe_11_NTT_flood();
    }else if(this->name == FHENamedParams::tfhe_11_NTT_amortized){
        init_tfhe_11_NTT_amortized();
    }else if(this->name == FHENamedParams::tfhe_12_NTT_amortized){
        init_tfhe_12_NTT_amortized();
    }else if(this->name == FHENamedParams::ntrunium_12_NTT){
        init_ntrunium_12_NTT();
    }
    else{ 
        throw std::runtime_error("TFHEKeyGenerator::TFHEKeyGenerator: Parameter set note supported! Perhaps the chosen parameter set requires additional dependencies to be compiled?"); 
    }
}

std::shared_ptr<LWESK> FHEConfiguration::get_secret_key(){
    return secret_key;
}
    
std::shared_ptr<FunctionalBootstrapPublicKey> FHEConfiguration::get_functional_bootstrap_pk(){
    return bootstrap_pk;
}

std::shared_ptr<LWEPublicKey> FHEConfiguration::get_encrypt_pk(){
    return encrypt_pk;
}

std::shared_ptr<AbstractAccumulatorBuilder> FHEConfiguration::get_accumulator_builder(){
    return accumulator_builder;
}

std::shared_ptr<SanitizationKey> FHEConfiguration::get_sanitization_key(){
    return sanitization_pk;
}
  
void FHEConfiguration::init_tfhe_11_NTT(){ 
    /// =================== Parameter Definition for the Functional Bootstrapping Algorithm

    // 2**11
    int degree = 2048; 
    // 2**48 - 16383 % 2*(2**11) = 1 (NTT Friendly), Base-4096 decomposition of 281474976694273: [1, 4092, 4095, 4095], L_2 norm: 7091.016499769268
    long coef_modulus = 281474976694273;
    double rlwe_stddev = 3.2; 
    // 2**8
    long gadget_decomp_base = 256;  
    // stddev_simul approx  2**(17.78)
    double stddev_simul = 225812;  
    int masking_size = 8192;
    // stddev_simul approx  2**(12.37) 
    double stddev_masking = 8192;
    KeyDistribution rlwe_key_type = ternary;
    std::shared_ptr<RLWEParam> rlwe_param(new RLWEParam(negacyclic, degree, coef_modulus, any, hexl_ntt));
    //Gadget deter_gadget = Gadget(N, Q, rlwe_basis * rlwe_basis * rlwe_basis, signed_decomposition_gadget);
    //Gadget rand_gadget = Gadget(N, Q, rlwe_basis, stddev_simul, discrete_gaussian_gadget);
    std::shared_ptr<Gadget> deter_gadget(new SignedDecompositionGadget(degree, coef_modulus, gadget_decomp_base * gadget_decomp_base * gadget_decomp_base));
    std::shared_ptr<Gadget> rand_gadget(new DiscreteGaussianSamplingGadget(degree, coef_modulus, gadget_decomp_base, stddev_simul));
    //std::shared_ptr<RLWEGadgetParam> rlwe_gadget_param = std::shared_ptr<RLWEGadgetParam>(new RLWEGadgetParam(rlwe_param, deter_gadget)); 
    //sk_arithmetic = hexl_ntt;

    // 2**9 + 400
    int lwe_dim = 912;
    // 2**7
    int lwe_ks_decomp_base = 128;
    // 2**(26) 
    double lwe_stddev = 67108864;
    std::shared_ptr<LWEParam> lwe_param(new LWEParam(lwe_dim, coef_modulus));
    //std::shared_ptr<LWEGadgetParam> lwe_gadget_param(new LWEGadgetParam(lwe_param, lwe_ks_decomp_base)); 

    default_encoding = PlaintextEncoding(full_domain, 4, coef_modulus); 
    FullDomainBootstrappingAlgorithm fdfb_alg = liu_micciancio_polyakov;

    /// =================== Generate Secret keys  
    
    // Generate GadgetLWE key. Its the LWE key for LWE-to-LWE-Key Switching.
    std::shared_ptr<LWESK> g_lwe(new LWESK(lwe_param, lwe_stddev, binary)); 
    std::shared_ptr<LWEGadgetSK> lwe_gadget_sk(new LWEGadgetSK(g_lwe, lwe_ks_decomp_base)); 
    // Gen GadgetRLWESecretKey. its the RLWE Key for Blind Rotation. 
    std::shared_ptr<RLWESK> rlwe(new RLWESK(rlwe_param, rlwe_key_type, rlwe_stddev)); 
    std::shared_ptr<RLWEGadgetSK> rlwe_gadget_sk(new RLWEGadgetSK(deter_gadget, rlwe)); 
    std::shared_ptr<RLWEGadgetSK> rlwe_rand_gadget_sk(new RLWEGadgetSK(rand_gadget, rlwe)); 
    // This key is the main decryption key for the scheme.
    this->secret_key = std::shared_ptr<LWESK>(rlwe->extract_lwe_key());
 
    /// =================== Generate Public keys  
     
    // Masking Key Gen
    this->encrypt_pk = std::shared_ptr<LWEPublicKey>(new LWEPublicKey(secret_key, masking_size, stddev_masking)); 
     
    // The blind rotation key  (run procedure depending on Enum Configuration)
    BlindRotationPublicKey *blind_rotation_key = new GINXBlindRotationKey(rlwe_gadget_sk, lwe_gadget_sk->lwe);   
    BlindRotationPublicKey *rand_blind_rotation_key = new GINXBlindRotationKey(rlwe_rand_gadget_sk, lwe_gadget_sk->lwe);  
    // Key Switching Key Gen
    LWEToLWEKeySwitchKey *ks_public_key = new LWEToLWEKeySwitchKey(secret_key, lwe_gadget_sk); 
    // Build the public key  
    std::shared_ptr<LWEParam> lwe_param_rot(new LWEParam(lwe_dim, rlwe_param->size * 2)); 
    // Init Accumulator Builder and Blind Rotation Output Builder
    accumulator_builder = std::shared_ptr<AbstractAccumulatorBuilder>(new RLWEAccumulatorBuilder(rlwe_param));
    std::shared_ptr<BlindRotateOutputBuilder> blind_rotate_output_builder(new RLWEBlindRotateOutputBuilder(rlwe_param));

    // Generate the Functional Bootstrapping Public Key and its Specific Values 
    /// TODO: Initialize this lwe_param_tiny inside the LMPFunctionalBootstrapPublicKey constructor
    std::shared_ptr<LWEParam> lwe_param_tiny(new LWEParam(lwe_dim, rlwe_param->size)); 
    bootstrap_pk = std::shared_ptr<FunctionalBootstrapPublicKey>(new LMPFunctionalBootstrapPublicKey(
        lwe_param_rot, 
        lwe_param_tiny,
        blind_rotation_key, 
        ks_public_key, 
        blind_rotate_output_builder, 
        accumulator_builder));
    

    sanitization_pk =  std::shared_ptr<SanitizationKey>(new KluczniakRandomizedBootstrapping(bootstrap_pk, accumulator_builder, encrypt_pk));
    this->is_secret_key_set = true;
    this->is_encrypt_pk_set = true;
    this->is_bootstrap_pk_set = true;
    this->is_sanitization_supported = true;
} 
 

void FHEConfiguration::init_tfhe_11_NTT_flood(){ 
    // 2**11
    int degree = 2048;
    // 2**36 - 12287 % 2*(2**11) = 1 (NTT friendly prime)
    //long Q = 68719464449;
    // 2**48 - 16383 % 2*(2**11) = 1 (NTT Friendly), Base-4096 decomposition of 281474976694273: [1, 4092, 4095, 4095], L_2 norm: 7091.016499769268
    long coef_modulus = 281474976694273;
    double rlwe_stddev = 3.2;
    // 2**4 -> 2**12
    long gadget_decomp_base = 256; 
    // Set to dummy 1 (here we tests noise flooding which will perform similarly to deter)
    double stddev_simul = 225812;  
    int masking_size = 8192;
    // stddev_simul approx  2**(12.37)
    double stddev_masking = 8192;
    KeyDistribution rlwe_key_type = ternary;

    std::shared_ptr<RLWEParam> rlwe_param(new RLWEParam(negacyclic, degree, coef_modulus, any, hexl_ntt));
    //Gadget deter_gadget = Gadget(N, Q, rlwe_basis * rlwe_basis * rlwe_basis, signed_decomposition_gadget);
    //Gadget rand_gadget = Gadget(N, Q, rlwe_basis, stddev_simul, signed_decomposition_gadget);
    std::shared_ptr<Gadget> deter_gadget = std::shared_ptr<Gadget>(new SignedDecompositionGadget(degree, coef_modulus, gadget_decomp_base * gadget_decomp_base * gadget_decomp_base)); 
    std::shared_ptr<Gadget> sanit_gadget = std::shared_ptr<Gadget>(new SignedDecompositionGadget(degree, coef_modulus, gadget_decomp_base)); 
    //std::shared_ptr<RLWEGadgetParam> rlwe_gadget_param = std::shared_ptr<RLWEGadgetParam>(new RLWEGadgetParam(rlwe_param, deter_gadget)); 
     
    // 2**9 + 400
    int lwe_dim = 912;
    int lwe_ks_decomp_base = 128;
    // 2**(26)
    double lwe_stddev = 67108864; 
    std::shared_ptr<LWEParam> lwe_param = std::shared_ptr<LWEParam>(new LWEParam(lwe_dim, coef_modulus));
    //std::shared_ptr<LWEGadgetParam> lwe_gadget_param = std::shared_ptr<LWEGadgetParam>(new LWEGadgetParam(lwe_param, lwe_ks_decomp_base)); 
    //LWEGadgetParam lwe_gadget_param = LWEGadgetParam(std::shared_ptr<LWEParam>(new LWEParam(lwe_dim, coef_modulus, binary, lwe_stddev)), lwe_ks_decomp_base); 

    default_encoding = PlaintextEncoding(full_domain, 4, coef_modulus); 
    FullDomainBootstrappingAlgorithm fdfb_alg = liu_micciancio_polyakov;


    /// =================== Generate Secret keys 
    
    // Generate GadgetLWE key. Its the LWE key for LWE-to-LWE-Key Switching.
    std::shared_ptr<LWESK> g_lwe = std::shared_ptr<LWESK>(new LWESK(lwe_param, lwe_stddev, binary)); 
    std::shared_ptr<LWEGadgetSK> lwe_gadget_sk(new LWEGadgetSK(g_lwe, lwe_ks_decomp_base)); 
    // Gen GadgetRLWESecretKey. its the RLWE Key for Blind Rotation. 
    std::shared_ptr<RLWESK> rlwe = std::shared_ptr<RLWESK>(new RLWESK(rlwe_param, rlwe_key_type, rlwe_stddev)); 
    std::shared_ptr<RLWEGadgetSK> rlwe_gadget_sk = std::shared_ptr<RLWEGadgetSK>(new RLWEGadgetSK(deter_gadget, rlwe));
    std::shared_ptr<RLWEGadgetSK> rlwe_rand_gadget_sk(new RLWEGadgetSK(sanit_gadget, rlwe)); 
    // lwe_sk after modulus switching to 2*N (for negacyclic ring). 
    std::shared_ptr<LWEParam> lwe_param_for_blind_rotation = std::shared_ptr<LWEParam>(new LWEParam(lwe_dim, degree * 2)); 
    std::shared_ptr<fhe_deck::LWESK> lwe_sk = std::shared_ptr<LWESK>(new LWESK(lwe_param, g_lwe->key, lwe_stddev,  binary)); 
    // Extracting the LWE Key to decrypt the constant coefficients of a RLWE ciphertext.
    // This key is the main decryption key for the scheme.
    this->secret_key = std::shared_ptr<LWESK>(rlwe->extract_lwe_key());
 
    /// =================== Generate Public Keys 

    // Key Switching Key Gen
    LWEToLWEKeySwitchKey *ks_public_key = new LWEToLWEKeySwitchKey(secret_key, lwe_gadget_sk); 
    // Masking Key Gen
    this->encrypt_pk = std::shared_ptr<LWEPublicKey>(new LWEPublicKey(secret_key, masking_size, stddev_masking));
    //LWEPublicKey *masking_public_key = new LWEPublicKey(secret_key, masking_size, stddev_masking);
    // The blind rotation key  
    BlindRotationPublicKey *blind_rotation_key = new GINXBlindRotationKey(rlwe_gadget_sk, lwe_sk); 
    BlindRotationPublicKey *rand_blind_rotation_key = new GINXBlindRotationKey(rlwe_rand_gadget_sk, lwe_gadget_sk->lwe); 
    // Init Accumulator builder
    accumulator_builder = std::shared_ptr<AbstractAccumulatorBuilder>(new RLWEAccumulatorBuilder(rlwe_param));
    // Build the public key 
    std::shared_ptr<LWEParam> lwe_param_rot(new LWEParam(lwe_dim, rlwe_param->size * 2)); 
    std::shared_ptr<LWEParam> lwe_param_tiny(new LWEParam(lwe_dim, rlwe_param->size)); 
    std::shared_ptr<BlindRotateOutputBuilder> blind_rotate_output_builder = std::shared_ptr<RLWEBlindRotateOutputBuilder>(new RLWEBlindRotateOutputBuilder(rlwe_param));
    bootstrap_pk = std::shared_ptr<FunctionalBootstrapPublicKey>(new LMPFunctionalBootstrapPublicKey(
        lwe_param_rot, 
        lwe_param_tiny,
        blind_rotation_key, 
        ks_public_key, 
        blind_rotate_output_builder, 
        accumulator_builder));

    sanitization_pk =  std::shared_ptr<SanitizationKey>(new DucasStehleWashingMachine(bootstrap_pk, accumulator_builder, encrypt_pk, 4));

    this->is_secret_key_set = true;
    this->is_encrypt_pk_set = true;
    this->is_bootstrap_pk_set = true;
    this->is_sanitization_supported = true;
} 

// Power of two parameter set
void FHEConfiguration::init_tfhe_11_B(){ 
    // 2**11
    int degree = 2048;
    // 2**36
    long coef_modulus = 68719476736;
    double rlwe_stddev = 3.2;
    // 2**4
    long gadget_decomp_base = 16; 
    double stddev_simul = 505;
    int masking_size = 3370;
    double stddev_masking = 4010391;
    KeyDistribution rlwe_key_type = ternary;
 
    std::shared_ptr<RLWEParam> rlwe_param(new RLWEParam(negacyclic, degree, coef_modulus, any, double_fft));
    //Gadget deter_gadget = Gadget(N, Q, rlwe_basis * rlwe_basis * rlwe_basis, signed_decomposition_gadget);
    //Gadget rand_gadget = Gadget(N, Q, rlwe_basis, stddev_simul, discrete_gaussian_gadget);
    std::shared_ptr<Gadget> deter_gadget = std::shared_ptr<Gadget>(new SignedDecompositionGadget(degree, coef_modulus, gadget_decomp_base * gadget_decomp_base * gadget_decomp_base)); 
    //std::shared_ptr<RLWEGadgetParam> rlwe_gadget_param = std::shared_ptr<RLWEGadgetParam>(new RLWEGadgetParam(rlwe_param, deter_gadget));  
   //sk_arithmetic = double_fft;

    // 2**9 + 430
    int lwe_dim = 912;
    int lwe_ks_decomp_base = 128;
    // 2**(14)
    double lwe_stddev = 16384;  
    std::shared_ptr<LWEParam> lwe_param = std::shared_ptr<LWEParam>(new LWEParam(lwe_dim, coef_modulus));
    //std::shared_ptr<LWEGadgetParam> lwe_gadget_param = std::shared_ptr<LWEGadgetParam>(new LWEGadgetParam(lwe_param, lwe_ks_decomp_base)); 
    //LWEGadgetParam lwe_gadget_param = LWEGadgetParam(std::shared_ptr<LWEParam>(new LWEParam(lwe_dim, coef_modulus, binary, lwe_stddev)), lwe_ks_decomp_base); 

    default_encoding = PlaintextEncoding(full_domain, 4, coef_modulus); 
    FullDomainBootstrappingAlgorithm fdfb_alg = liu_micciancio_polyakov;

    /// =================== Generate Secret keys 
    
    // Generate GadgetLWE key. Its the LWE key for LWE-to-LWE-Key Switching.
    std::shared_ptr<LWESK> g_lwe(new LWESK(lwe_param, lwe_stddev, binary)); 
    std::shared_ptr<LWEGadgetSK> lwe_gadget_sk(new LWEGadgetSK(g_lwe, lwe_ks_decomp_base)); 
    // Gen GadgetRLWESecretKey. its the RLWE Key for Blind Rotation. 
    std::shared_ptr<RLWESK> rlwe = std::shared_ptr<RLWESK>(new RLWESK(rlwe_param, rlwe_key_type, rlwe_stddev)); 
    std::shared_ptr<RLWEGadgetSK> rlwe_gadget_sk = std::shared_ptr<RLWEGadgetSK>(new RLWEGadgetSK(deter_gadget, rlwe));
    // lwe_sk after modulus switching to 2*N (for negacyclic ring). 
    std::shared_ptr<LWEParam> lwe_param_for_blind_rotation = std::shared_ptr<LWEParam>(new LWEParam(lwe_dim, degree * 2)); 
    std::shared_ptr<fhe_deck::LWESK> lwe_sk = std::shared_ptr<LWESK>(new LWESK(lwe_param, g_lwe->key, lwe_stddev,  binary));  
    // Extracting the LWE Key to decrypt the constant coefficients of a RLWE ciphertext.
    // This key is the main decryption key for the scheme.
    this->secret_key = std::shared_ptr<LWESK>(rlwe->extract_lwe_key());
 
    /// =================== Generate Public Keys 

    // Key Switching Key Gen
    LWEToLWEKeySwitchKey *ks_public_key = new LWEToLWEKeySwitchKey(secret_key, lwe_gadget_sk); 
    // Masking Key Gen
    this->encrypt_pk = std::shared_ptr<LWEPublicKey>(new LWEPublicKey(secret_key, masking_size, stddev_masking)); 
    //LWEPublicKey *masking_public_key = new LWEPublicKey(secret_key, masking_size, stddev_masking);
    // The blind rotation key  
    BlindRotationPublicKey *blind_rotation_key = new GINXBlindRotationKey(rlwe_gadget_sk, lwe_sk); 
    // Init Accumulator builder
    accumulator_builder = std::shared_ptr<AbstractAccumulatorBuilder>(new RLWEAccumulatorBuilder(rlwe_param));
    // Build the public key 
    std::shared_ptr<LWEParam> lwe_param_rot(new LWEParam(lwe_dim, rlwe_param->size * 2)); 
    std::shared_ptr<LWEParam> lwe_param_tiny(new LWEParam(lwe_dim, rlwe_param->size)); 
    std::shared_ptr<BlindRotateOutputBuilder> blind_rotate_output_builder(new RLWEBlindRotateOutputBuilder(rlwe_param));
    bootstrap_pk = std::shared_ptr<FunctionalBootstrapPublicKey>(new LMPFunctionalBootstrapPublicKey(
        lwe_param_rot, 
        lwe_param_tiny,
        blind_rotation_key, 
        ks_public_key, 
        blind_rotate_output_builder, 
        accumulator_builder));

    this->is_secret_key_set = true;
    this->is_encrypt_pk_set = true;
    this->is_bootstrap_pk_set = true;
    this->is_sanitization_supported = true;
} 

 
void FHEConfiguration::init_tfhe_11_flood(){ 
    // 2**11
    int degree = 2048;
    // 2**36
    long coef_modulus = 68719476736;
    double rlwe_stddev = 3.2;
    // 2**4
    long gadget_decomp_base = 16; 
    double stddev_simul = 505;
    int masking_size = 3370;
    double stddev_masking = 4010391;
    KeyDistribution rlwe_key_type = ternary;

    std::shared_ptr<RLWEParam> rlwe_param(new RLWEParam(negacyclic, degree, coef_modulus, any, double_fft));
    //Gadget deter_gadget = Gadget(N, Q, rlwe_basis * rlwe_basis * rlwe_basis, signed_decomposition_gadget);
    //Gadget rand_gadget = Gadget(N, Q, rlwe_basis, signed_decomposition_gadget);
    std::shared_ptr<Gadget> deter_gadget = std::shared_ptr<Gadget>(new SignedDecompositionGadget(degree, coef_modulus, gadget_decomp_base * gadget_decomp_base * gadget_decomp_base)); 
    //std::shared_ptr<RLWEGadgetParam> rlwe_gadget_param = std::shared_ptr<RLWEGadgetParam>(new RLWEGadgetParam(rlwe_param, deter_gadget)); 

    /// Parameters for the LWE to LWE Key Switching Key
    // 2**9 + 430
    int lwe_dim = 912;
    int lwe_ks_decomp_base = 128;
    // 2**(14) 
    double lwe_stddev = 16384;
    std::shared_ptr<LWEParam> lwe_param = std::shared_ptr<LWEParam>(new LWEParam(lwe_dim, coef_modulus));
    //std::shared_ptr<LWEGadgetParam> lwe_gadget_param = std::shared_ptr<LWEGadgetParam>(new LWEGadgetParam(lwe_param, lwe_ks_decomp_base)); 
    //LWEGadgetParam lwe_gadget_param = LWEGadgetParam(std::shared_ptr<LWEParam>(new LWEParam(lwe_dim, coef_modulus, binary, lwe_stddev)), lwe_ks_decomp_base); 

    default_encoding = PlaintextEncoding(full_domain, 4, coef_modulus); 
    FullDomainBootstrappingAlgorithm fdfb_alg = liu_micciancio_polyakov;

    /// =================== Generate Secret keys 
    
    // Generate GadgetLWE key. Its the LWE key for LWE-to-LWE-Key Switching.
    std::shared_ptr<LWESK> g_lwe = std::shared_ptr<LWESK>(new LWESK(lwe_param, lwe_stddev, binary)); 
    std::shared_ptr<LWEGadgetSK> lwe_gadget_sk(new LWEGadgetSK(g_lwe, lwe_ks_decomp_base)); 
    // Gen GadgetRLWESecretKey. its the RLWE Key for Blind Rotation. 
    std::shared_ptr<RLWESK> rlwe = std::shared_ptr<RLWESK>(new RLWESK(rlwe_param, rlwe_key_type, rlwe_stddev)); 
    std::shared_ptr<RLWEGadgetSK> rlwe_gadget_sk = std::shared_ptr<RLWEGadgetSK>(new RLWEGadgetSK(deter_gadget, rlwe));
    // lwe_sk after modulus switching to 2*N (for negacyclic ring). 
    std::shared_ptr<LWEParam> lwe_param_for_blind_rotation = std::shared_ptr<LWEParam>(new LWEParam(lwe_dim, degree * 2)); 
    std::shared_ptr<fhe_deck::LWESK> lwe_sk = std::shared_ptr<LWESK>(new LWESK(lwe_param, g_lwe->key, lwe_stddev,  binary)); 
    // Extracting the LWE Key to decrypt the constant coefficients of a RLWE ciphertext.
    // This key is the main decryption key for the scheme.
    this->secret_key = std::shared_ptr<LWESK>(rlwe->extract_lwe_key());
 
    /// =================== Generate Public Keys 

    // Key Switching Key Gen
    LWEToLWEKeySwitchKey *ks_public_key = new LWEToLWEKeySwitchKey(secret_key, lwe_gadget_sk); 
    // Masking Key Gen
    this->encrypt_pk = std::shared_ptr<LWEPublicKey>(new LWEPublicKey(secret_key, masking_size, stddev_masking));
    //LWEPublicKey *masking_public_key = new LWEPublicKey(secret_key, masking_size, stddev_masking);
    // The blind rotation key  
    BlindRotationPublicKey *blind_rotation_key = new GINXBlindRotationKey(rlwe_gadget_sk, lwe_sk); 
    // Init Accumulator builder
    accumulator_builder = std::shared_ptr<AbstractAccumulatorBuilder>(new RLWEAccumulatorBuilder(rlwe_param));
    // Build the public key 
    std::shared_ptr<LWEParam> lwe_param_rot(new LWEParam(lwe_dim, rlwe_param->size * 2)); 
    std::shared_ptr<LWEParam> lwe_param_tiny(new LWEParam(lwe_dim, rlwe_param->size)); 
    std::shared_ptr<BlindRotateOutputBuilder> blind_rotate_output_builder = std::shared_ptr<RLWEBlindRotateOutputBuilder>(new RLWEBlindRotateOutputBuilder(rlwe_param));
    bootstrap_pk = std::shared_ptr<FunctionalBootstrapPublicKey>(new LMPFunctionalBootstrapPublicKey(
        lwe_param_rot, 
        lwe_param_tiny,
        blind_rotation_key, 
        ks_public_key, 
        blind_rotate_output_builder, 
        accumulator_builder));

    this->is_secret_key_set = true;
    this->is_encrypt_pk_set = true;
    this->is_bootstrap_pk_set = true;
    this->is_sanitization_supported = true;
} 

void FHEConfiguration::init_tfhe_11_NTT_amortized(){ 
    // 2**11
    int degree = 2048; 
    // (2**51 - 45055) % 2*(2**11) = 1 and prime (NTT Friendly),   
    long coef_modulus = 2251799813640193;  

    double rlwe_stddev = 3.2; 
    KeyDistribution rlwe_key_type = ternary;
    // 2**9
    long gadget_decomp_base = 512;  
    // stddev_simul approx  2**(19.28)
    double stddev_simul = 638072;  

    int masking_size = 8050;
    // stddev_simul approx  2**(11.22)
    double stddev_masking = 8192;

    std::shared_ptr<RLWEParam> rlwe_param(new RLWEParam(negacyclic, degree, coef_modulus, any, hexl_ntt));
    //Gadget deter_gadget = Gadget(N, Q, rlwe_basis * rlwe_basis, signed_decomposition_gadget);
    std::shared_ptr<Gadget> deter_gadget = std::shared_ptr<Gadget>(new SignedDecompositionGadget(degree, coef_modulus, gadget_decomp_base * gadget_decomp_base)); 
    //Gadget rand_gadget = Gadget(N, Q, rlwe_basis, stddev_simul, discrete_gaussian_gadget);
    //std::shared_ptr<RLWEGadgetParam> rlwe_gadget_param = std::shared_ptr<RLWEGadgetParam>(new RLWEGadgetParam(rlwe_param, deter_gadget)); 
    //sk_arithmetic = hexl_ntt;
 
    int lwe_dim = 950;
    // 2**9
    int lwe_ks_decomp_base = 512;
    // 2**(23) 
    double lwe_stddev = 262144;
    std::shared_ptr<LWEParam> lwe_param = std::shared_ptr<LWEParam>(new LWEParam(lwe_dim, coef_modulus));
    //std::shared_ptr<LWEGadgetParam> lwe_gadget_param = std::shared_ptr<LWEGadgetParam>(new LWEGadgetParam(lwe_param, lwe_ks_decomp_base)); 
    //LWEGadgetParam lwe_gadget_param = LWEGadgetParam(std::shared_ptr<LWEParam>(new LWEParam(lwe_dim, coef_modulus, binary, lwe_stddev)), lwe_ks_decomp_base); 

    default_encoding = PlaintextEncoding(partial_domain, 8, coef_modulus); 
    FullDomainBootstrappingAlgorithm fdfb_alg = liu_micciancio_polyakov;

    /// =================== Generate Secret keys 
    
    // Generate GadgetLWE key. Its the LWE key for LWE-to-LWE-Key Switching.
    std::shared_ptr<LWESK> g_lwe = std::shared_ptr<LWESK>(new LWESK(lwe_param, lwe_stddev, binary)); 
    std::shared_ptr<LWEGadgetSK> lwe_gadget_sk(new LWEGadgetSK(g_lwe, lwe_ks_decomp_base)); 
    // Gen GadgetRLWESecretKey. its the RLWE Key for Blind Rotation. 
    std::shared_ptr<RLWESK> rlwe = std::shared_ptr<RLWESK>(new RLWESK(rlwe_param, rlwe_key_type, rlwe_stddev)); 
    std::shared_ptr<RLWEGadgetSK> rlwe_gadget_sk = std::shared_ptr<RLWEGadgetSK>(new RLWEGadgetSK(deter_gadget, rlwe));
    // lwe_sk after modulus switching to 2*N (for negacyclic ring). 
    std::shared_ptr<LWEParam> lwe_param_for_blind_rotation = std::shared_ptr<LWEParam>(new LWEParam(lwe_dim, degree * 2)); 
    std::shared_ptr<fhe_deck::LWESK> lwe_sk = std::shared_ptr<LWESK>(new LWESK(lwe_param, g_lwe->key, lwe_stddev,  binary)); 
    // Extracting the LWE Key to decrypt the constant coefficients of a RLWE ciphertext.
    // This key is the main decryption key for the scheme.
    this->secret_key = std::shared_ptr<LWESK>(rlwe->extract_lwe_key());
 
    /// =================== Generate Public Keys 

    // Key Switching Key Gen
    LWEToLWEKeySwitchKey *ks_public_key = new LWEToLWEKeySwitchKey(secret_key, lwe_gadget_sk); 
    // Masking Key Gen
    this->encrypt_pk = std::shared_ptr<LWEPublicKey>(new LWEPublicKey(secret_key, masking_size, stddev_masking));
    //LWEPublicKey *masking_public_key = new LWEPublicKey(secret_key, masking_size, stddev_masking);
    // The blind rotation key  
    BlindRotationPublicKey *blind_rotation_key = new GINXBlindRotationKey(rlwe_gadget_sk, lwe_sk); 
    // Init Accumulator builder
    accumulator_builder = std::shared_ptr<AbstractAccumulatorBuilder>(new RLWEAccumulatorBuilder(rlwe_param));
    // Build the public key 
    std::shared_ptr<LWEParam> lwe_param_rot(new LWEParam(lwe_dim, rlwe_param->size * 2)); 
    std::shared_ptr<LWEParam> lwe_param_tiny(new LWEParam(lwe_dim, rlwe_param->size)); 
    std::shared_ptr<BlindRotateOutputBuilder> blind_rotate_output_builder = std::shared_ptr<RLWEBlindRotateOutputBuilder>(new RLWEBlindRotateOutputBuilder(rlwe_param));
    bootstrap_pk = std::shared_ptr<FunctionalBootstrapPublicKey>(new LMPFunctionalBootstrapPublicKey(
        lwe_param_rot, 
        lwe_param_tiny,
        blind_rotation_key, 
        ks_public_key, 
        blind_rotate_output_builder, 
        accumulator_builder));

    this->is_secret_key_set = true;
    this->is_encrypt_pk_set = true;
    this->is_bootstrap_pk_set = true;
    this->is_sanitization_supported = true;
} 
 

void FHEConfiguration::init_tfhe_12_NTT_amortized(){  
    // 2**12
    int degree = 4096; 
    // (2**51 - 131071) % 2*(2**12) = 1 and prime (NTT Friendly),   
    //long Q = 2251799813554177;
    // 52-bit modulus
    //long Q = 4503599627149313;
    // 53-bit modulus
    //long Q = 9007199254429697;
    // 54-bit modulus
    long coef_modulus =  18014398509309953;
  
    double rlwe_stddev = 3.2; 
    KeyDistribution rlwe_key_type = ternary;
    // 2**8
    long gadget_decomp_base = 256;  
    // stddev_simul approx  2**(19.28)
    double stddev_simul = 638072;   
    // 2**13
    int masking_size = 14936;
    // stddev_simul approx  2**(14)
    double stddev_masking = 16384;

    std::shared_ptr<RLWEParam> rlwe_param(new RLWEParam(negacyclic, degree, coef_modulus, any, hexl_ntt)); 
    std::shared_ptr<Gadget> deter_gadget = std::shared_ptr<Gadget>(new SignedDecompositionGadget(degree, coef_modulus, gadget_decomp_base * gadget_decomp_base)); 
    
    //Gadget rand_gadget = Gadget(N, Q, rlwe_basis, stddev_simul, discrete_gaussian_gadget); 
    //std::shared_ptr<RLWEGadgetParam> rlwe_gadget_param = std::shared_ptr<RLWEGadgetParam>(new RLWEGadgetParam(rlwe_param, deter_gadget)); 
    //sk_arithmetic = hexl_ntt; 

    int lwe_dim = 950;
    // 2**9
    int lwe_ks_decomp_base = 512; 
    // 2**(23) 
    double lwe_stddev = 262144;
    std::shared_ptr<LWEParam> lwe_param = std::shared_ptr<LWEParam>(new LWEParam(lwe_dim, coef_modulus));
    //std::shared_ptr<LWEGadgetParam> lwe_gadget_param = std::shared_ptr<LWEGadgetParam>(new LWEGadgetParam(lwe_param, lwe_ks_decomp_base)); 
    //LWEGadgetParam lwe_gadget_par = LWEGadgetParam(std::shared_ptr<LWEParam>(new LWEParam(lwe_dim, coef_modulus, binary, lwe_stddev)), lwe_ks_decomp_base); 

    default_encoding = PlaintextEncoding(partial_domain, 16, coef_modulus); 
    FullDomainBootstrappingAlgorithm fdfb_alg = liu_micciancio_polyakov;

    /// =================== Generate Secret keys 
    
    // Generate GadgetLWE key. Its the LWE key for LWE-to-LWE-Key Switching.
    std::shared_ptr<LWESK> g_lwe = std::shared_ptr<LWESK>(new LWESK(lwe_param, lwe_stddev, binary)); 
    std::shared_ptr<LWEGadgetSK> lwe_gadget_sk(new LWEGadgetSK(g_lwe, lwe_ks_decomp_base)); 
    // Gen GadgetRLWESecretKey. its the RLWE Key for Blind Rotation. 
    std::shared_ptr<RLWESK> rlwe = std::shared_ptr<RLWESK>(new RLWESK(rlwe_param, rlwe_key_type, rlwe_stddev)); 
    std::shared_ptr<RLWEGadgetSK> rlwe_gadget_sk = std::shared_ptr<RLWEGadgetSK>(new RLWEGadgetSK(deter_gadget, rlwe));
    // lwe_sk after modulus switching to 2*N (for negacyclic ring). 
    std::shared_ptr<LWEParam> lwe_param_for_blind_rotation = std::shared_ptr<LWEParam>(new LWEParam(lwe_dim, degree * 2)); 
    std::shared_ptr<fhe_deck::LWESK> lwe_sk = std::shared_ptr<LWESK>(new LWESK(lwe_param, g_lwe->key, lwe_stddev,  binary)); 
    // Extracting the LWE Key to decrypt the constant coefficients of a RLWE ciphertext.
    // This key is the main decryption key for the scheme.
    this->secret_key = std::shared_ptr<LWESK>(rlwe->extract_lwe_key());
 
    /// =================== Generate Public Keys 

    // Key Switching Key Gen
    LWEToLWEKeySwitchKey *ks_public_key = new LWEToLWEKeySwitchKey(secret_key, lwe_gadget_sk); 
    // Masking Key Gen
    this->encrypt_pk = std::shared_ptr<LWEPublicKey>(new LWEPublicKey(secret_key, masking_size, stddev_masking));
    //LWEPublicKey *masking_public_key = new LWEPublicKey(secret_key, masking_size, stddev_masking);
    // The blind rotation key  
    BlindRotationPublicKey *blind_rotation_key = new GINXBlindRotationKey(rlwe_gadget_sk, lwe_sk); 
    // Init Accumulator builder
    accumulator_builder = std::shared_ptr<AbstractAccumulatorBuilder>(new RLWEAccumulatorBuilder(rlwe_param));
    // Build the public key 
    std::shared_ptr<LWEParam> lwe_param_rot(new LWEParam(lwe_dim, rlwe_param->size * 2)); 
    std::shared_ptr<LWEParam> lwe_param_tiny(new LWEParam(lwe_dim, rlwe_param->size)); 
    std::shared_ptr<BlindRotateOutputBuilder> blind_rotate_output_builder = std::shared_ptr<RLWEBlindRotateOutputBuilder>(new RLWEBlindRotateOutputBuilder(rlwe_param));
    bootstrap_pk = std::shared_ptr<FunctionalBootstrapPublicKey>(new LMPFunctionalBootstrapPublicKey(
        lwe_param_rot, 
        lwe_param_tiny,
        blind_rotation_key, 
        ks_public_key, 
        blind_rotate_output_builder, 
        accumulator_builder));

    this->is_secret_key_set = true;
    this->is_encrypt_pk_set = true;
    this->is_bootstrap_pk_set = true;
    this->is_sanitization_supported = true;
} 



void FHEConfiguration::init_ntrunium_12_NTT(){ 
    /// =================== Parameter Definition for the Functional Bootstrapping Algorithm

    // 2**11
    int degree = 4096; 
    // 2**45 - 204799 % 2*(2**12) = 1 (NTT Friendly) 
    long coef_modulus = 35184371884033;
    double ntru_stddev = 1/4.0; 
    // 2**15
    long gadget_decomp_base = 32768;  
    // stddev_simul approx  2**(17.78)
    double stddev_simul = 225812;  
    int masking_size = 8192;
    // stddev_simul approx  2**(12.37) 
    double stddev_masking = 8192; 
    std::shared_ptr<NTRUParam> ntru_param(new NTRUParam(negacyclic, degree, coef_modulus, any, hexl_ntt));
    //Gadget deter_gadget = Gadget(N, Q, rlwe_basis * rlwe_basis * rlwe_basis, signed_decomposition_gadget);
    //Gadget rand_gadget = Gadget(N, Q, rlwe_basis, stddev_simul, discrete_gaussian_gadget);
    std::shared_ptr<Gadget> deter_gadget = std::shared_ptr<Gadget>(new SignedDecompositionGadget(degree, coef_modulus, gadget_decomp_base));
    //std::shared_ptr<RLWEGadgetParam> rlwe_gadget_param = std::shared_ptr<RLWEGadgetParam>(new RLWEGadgetParam(rlwe_param, deter_gadget)); 
    //sk_arithmetic = hexl_ntt;

    // 2**9 + 400
    int lwe_dim = 750;
    // 2**7
    int lwe_ks_decomp_base = 2;
    // 2**(26) 
    double lwe_stddev = 16384;
    std::shared_ptr<LWEParam> lwe_param = std::shared_ptr<LWEParam>(new LWEParam(lwe_dim, coef_modulus));
    //std::shared_ptr<LWEGadgetParam> lwe_gadget_param = std::shared_ptr<LWEGadgetParam>(new LWEGadgetParam(lwe_param, lwe_ks_decomp_base)); 

    default_encoding = PlaintextEncoding(full_domain, 4, coef_modulus); 
    FullDomainBootstrappingAlgorithm fdfb_alg = liu_micciancio_polyakov;

    /// =================== Generate Secret keys  
    
    // Generate GadgetLWE key. Its the LWE key for LWE-to-LWE-Key Switching.
    std::shared_ptr<LWESK> g_lwe = std::shared_ptr<LWESK>(new LWESK(lwe_param, lwe_stddev, binary)); 
    std::shared_ptr<LWEGadgetSK> lwe_gadget_sk(new LWEGadgetSK(g_lwe, lwe_ks_decomp_base)); 
    // Gen GadgetNTRUSecretKey. its the NTRU Key for Blind Rotation. 
    std::shared_ptr<NTRUSK> ntru_sk = std::shared_ptr<NTRUSK>(new NTRUSK(ntru_param, ntru_stddev)); 
    std::shared_ptr<NTRUGadgetSK> ntru_gadget_sk = std::shared_ptr<NTRUGadgetSK>(new NTRUGadgetSK(deter_gadget, ntru_sk));
    // lwe_sk after modulus switching to 2*N (for negacyclic ring).  
    std::shared_ptr<LWEParam> lwe_param_for_blind_rotation = std::shared_ptr<LWEParam>(new LWEParam(lwe_dim, degree * 2)); 
    std::shared_ptr<fhe_deck::LWESK> lwe_sk = std::shared_ptr<LWESK>(new LWESK(lwe_param, g_lwe->key, lwe_stddev,  binary)); 
    // Init Accumulator builder and blind rotate output builder.
    accumulator_builder = std::shared_ptr<AbstractAccumulatorBuilder>(new NTRUAccumulatorBuilder(ntru_sk));
    std::shared_ptr<BlindRotateOutputBuilder> blind_rotate_output_builder = std::shared_ptr<NTRUBlindRotateOutputBuilder>(new NTRUBlindRotateOutputBuilder(ntru_param));
    // Extracting the LWE Key to decrypt the constant coefficients of a RLWE ciphertext.
    // This key is the main decryption key for the scheme.
    this->secret_key = std::shared_ptr<LWESK>(ntru_sk->extract_lwe_key());
 
    /// =================== Generate Public Keys 
 
    // Key Switching Key Gen
    LWEToLWEKeySwitchKey *ks_public_key = new LWEToLWEKeySwitchKey(secret_key, lwe_gadget_sk);  
    // Masking Key Gen
    this->encrypt_pk = std::shared_ptr<LWEPublicKey>(new LWEPublicKey(secret_key, masking_size, stddev_masking));
    //LWEPublicKey *masking_public_key = new LWEPublicKey(secret_key, masking_size, stddev_masking);
    // The blind rotation key   
    BlindRotationPublicKey *blind_rotation_key = new GINXBlindRotationKey(ntru_gadget_sk, lwe_sk); 
    // Build the public key 
    // TODO: This modulus switching looks increadibly ugly
    std::shared_ptr<LWEParam> lwe_param_rot(new LWEParam(lwe_dim, ntru_param->size * 2)); 
    std::shared_ptr<LWEParam> lwe_param_tiny(new LWEParam(lwe_dim, ntru_param->size));  
    bootstrap_pk = std::shared_ptr<FunctionalBootstrapPublicKey>(new LMPFunctionalBootstrapPublicKey(
        lwe_param_rot, 
        lwe_param_tiny,
        blind_rotation_key, 
        ks_public_key, 
        blind_rotate_output_builder, 
        accumulator_builder));

    this->is_secret_key_set = true;
    this->is_encrypt_pk_set = true;
    this->is_bootstrap_pk_set = true;
    this->is_sanitization_supported = true;
} 
 