#include "fhe/ciphertext_sanitization.h"

using namespace FHEDeck;

DucasStehleWashingMachine::DucasStehleWashingMachine(
            std::shared_ptr<FunctionalBootstrapPublicKey> fun_bootstrap_pk, 
            std::shared_ptr<AbstractFunctionBuilder> accumulator_builder,
            std::shared_ptr<LWEPublicKey> masking_pk,
            int32_t washing_cycles){

    m_fun_bootstrap_pk = fun_bootstrap_pk;
    m_accumulator_builder = accumulator_builder;
    m_masking_pk = masking_pk;
    m_washing_cycles = washing_cycles;
}

void DucasStehleWashingMachine::sanitize(LWECT& ct_out, const LWECT& ct_in, const PlaintextEncoding &encoding){
    auto fun_identity = [](int64_t m) -> int64_t {
        return m; 
    };    
    std::shared_ptr<FunctionSpecification> acc(m_accumulator_builder->prepare_specification(fun_identity, encoding, encoding));
    LWECT ct_of_zero(m_masking_pk->param());
    for(int32_t i = 0; i < m_washing_cycles; ++i){
        m_masking_pk->encrypt(ct_of_zero, 0);
        ct_in.add(ct_out, ct_of_zero);
        /// TODO: Flood with noice
        /// TODO: This part should be in the FunctionalBootstrap public key - change it also in fhe_context examples
        /// NOTE: Similar as for KluczniakRandomizedBootstrapping, I'm executing blind rotation twice, where one time is actually enough.
        if(encoding.get_type() == PlaintextEncodingType::full_domain){    
            m_fun_bootstrap_pk->full_domain_bootstrap(ct_out, acc, ct_out, encoding, encoding);
        }else if(encoding.get_type() == PlaintextEncodingType::partial_domain){  
            m_fun_bootstrap_pk->bootstrap(ct_out,  acc, ct_out); 
        }else if(encoding.get_type() == PlaintextEncodingType::signed_limied_short_int){    
            LWECT c_in_copy(ct_out.param());
            ct_out.add(c_in_copy, encoding.encode_message(encoding.get_plaintext_space()));
            m_fun_bootstrap_pk->bootstrap(ct_out, acc, c_in_copy);   
        } 
    } 
}

KluczniakRandomizedBootstrapping::KluczniakRandomizedBootstrapping(
            std::shared_ptr<FunctionalBootstrapPublicKey> fun_bootstrap_pk, 
            std::shared_ptr<AbstractFunctionBuilder> accumulator_builder,
            std::shared_ptr<LWEPublicKey> masking_pk){

    m_fun_bootstrap_pk = fun_bootstrap_pk;
    m_accumulator_builder = accumulator_builder;
    m_masking_pk = masking_pk; 
}

void KluczniakRandomizedBootstrapping::sanitize(LWECT& ct_out, const LWECT& ct_in, const PlaintextEncoding &encoding){
    auto fun_identity = [](int64_t m) -> int64_t {
        return m; 
    };   
    std::shared_ptr<FunctionSpecification> acc(m_accumulator_builder->prepare_specification(fun_identity, encoding, encoding));
    /// TODO: This part should be in the FunctionalBootstrap public key - change it also in fhe_context examples
    if(encoding.get_type() == PlaintextEncodingType::full_domain){    
        /// NOTE: With full domain its sort of a problem because we run randomized blind rotation twice, where one time is enough.
        // For now I leave it like this due to code readability. I don't want to have multiple blind rotation keys in the FunctionalBootstrapPublicKey class.
        m_fun_bootstrap_pk->full_domain_bootstrap(ct_out, acc, ct_in, encoding, encoding);
    }else if(encoding.get_type() == PlaintextEncodingType::partial_domain){  
        m_fun_bootstrap_pk->bootstrap(ct_out,  acc, ct_in); 
    }else if(encoding.get_type() == PlaintextEncodingType::signed_limied_short_int){    
        LWECT c_in_copy(ct_in.param());
        ct_in.add(c_in_copy, encoding.encode_message(encoding.get_plaintext_space()));
        m_fun_bootstrap_pk->bootstrap(ct_out, acc, c_in_copy);   
    } 
    LWECT ct_of_zero(m_masking_pk->param());
    m_masking_pk->encrypt(ct_of_zero, 0);
    ct_out.add(ct_out, ct_of_zero); 
}


