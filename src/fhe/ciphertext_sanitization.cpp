#include "ciphertext_sanitization.h"

using namespace fhe_deck;

DucasStehleWashingMachine::DucasStehleWashingMachine(
            std::shared_ptr<FunctionalBootstrapPublicKey> fun_bootstrap_pk, 
            std::shared_ptr<AbstractAccumulatorBuilder> accumulator_builder,
            std::shared_ptr<LWEPublicKey> masking_pk,
            int32_t washing_cycles){

    this->fun_bootstrap_pk = fun_bootstrap_pk;
    this->accumulator_builder = accumulator_builder;
    this->masking_pk = masking_pk;
    this->washing_cycles = washing_cycles;
}

void DucasStehleWashingMachine::sanitize(LWECT& ct_out, const LWECT& ct_in, const PlaintextEncoding &encoding){
    auto fun_identity = [](int64_t m) -> int64_t {
        return m; 
    };   
    std::shared_ptr<VectorCTAccumulator> acc(accumulator_builder->prepare_accumulator(fun_identity, encoding));
    LWECT ct_of_zero(masking_pk->param);
    for(int32_t i = 0; i < washing_cycles; ++i){
        masking_pk->encrypt(ct_of_zero, 0);
        ct_in.add(ct_out, ct_of_zero);
        /// TODO: Flood with noice
        /// TODO: This part should be in the FunctionalBootstrap public key - change it also in fhe_context examples
        /// NOTE: Similar as for KluczniakRandomizedBootstrapping, I'm executing blind rotation twice, where one time is actually enough.
        if(encoding.type == full_domain){    
            fun_bootstrap_pk->full_domain_bootstrap(ct_out, acc, ct_out, encoding);
        }else if(encoding.type == partial_domain){  
            fun_bootstrap_pk->bootstrap(ct_out,  acc, ct_out); 
        }else if(encoding.type == signed_limied_short_int){    
            LWECT c_in_copy(ct_out.param);
            ct_out.add(c_in_copy, encoding.encode_message(encoding.plaintext_space));
            fun_bootstrap_pk->bootstrap(ct_out, acc, c_in_copy);   
        } 
    } 
}

KluczniakRandomizedBootstrapping::KluczniakRandomizedBootstrapping(
            std::shared_ptr<FunctionalBootstrapPublicKey> fun_bootstrap_pk, 
            std::shared_ptr<AbstractAccumulatorBuilder> accumulator_builder,
            std::shared_ptr<LWEPublicKey> masking_pk){

    this->fun_bootstrap_pk = fun_bootstrap_pk;
    this->accumulator_builder = accumulator_builder;
    this->masking_pk = masking_pk; 
}

void KluczniakRandomizedBootstrapping::sanitize(LWECT& ct_out, const LWECT& ct_in, const PlaintextEncoding &encoding){
    auto fun_identity = [](int64_t m) -> int64_t {
        return m; 
    };   
    std::shared_ptr<VectorCTAccumulator> acc(accumulator_builder->prepare_accumulator(fun_identity, encoding)); 
    /// TODO: This part should be in the FunctionalBootstrap public key - change it also in fhe_context examples
    if(encoding.type == full_domain){    
        /// NOTE: With full domain its sort of a problem because we run randomized blind rotation twice, where one time is enough.
        // For now I leave it like this due to code readability. I don't want to have multiple blind rotation keys in the FunctionalBootstrapPublicKey class.
        fun_bootstrap_pk->full_domain_bootstrap(ct_out, acc, ct_in, encoding);
    }else if(encoding.type == partial_domain){  
        fun_bootstrap_pk->bootstrap(ct_out,  acc, ct_in); 
    }else if(encoding.type == signed_limied_short_int){    
        LWECT c_in_copy(ct_in.param);
        ct_in.add(c_in_copy, encoding.encode_message(encoding.plaintext_space));
        fun_bootstrap_pk->bootstrap(ct_out, acc, c_in_copy);   
    } 
    LWECT ct_of_zero(masking_pk->param);
    masking_pk->encrypt(ct_of_zero, 0);
    ct_out.add(ct_out, ct_of_zero); 
}


