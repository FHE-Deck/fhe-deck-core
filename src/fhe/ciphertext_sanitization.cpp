#include "ciphertext_sanitization.h"

using namespace fhe_deck;

DucasStehleWashingMachine::DucasStehleWashingMachine(
            std::shared_ptr<FunctionalBootstrapPublicKey> fun_bootstrap_pk, 
            std::shared_ptr<AbstractAccumulatorBuilder> accumulator_builder,
            std::shared_ptr<LWEPublicKey> masking_pk,
            int washing_cycles){

    this->fun_bootstrap_pk = fun_bootstrap_pk;
    this->accumulator_builder = accumulator_builder;
    this->masking_pk = masking_pk;
    this->washing_cycles = washing_cycles;
}

void DucasStehleWashingMachine::sanitize(LWECT *ct, PlaintextEncoding encoding){
    auto fun_identity = [](long m) -> long {
        return m; 
    };   
    std::shared_ptr<VectorCTAccumulator> acc(accumulator_builder->prepare_accumulator(fun_identity, encoding));
    LWECT ct_of_zero(masking_pk->param);
    for(int i = 0; i < washing_cycles; ++i){
        masking_pk->encrypt(&ct_of_zero, 0);
        ct->add(ct, &ct_of_zero);
        /// TODO: Flood with noice
        /// TODO: This part should be in the FunctionalBootstrap public key - change it also in fhe_context examples
        if(encoding.type == full_domain){    
            fun_bootstrap_pk->full_domain_bootstrap(ct, acc, ct, encoding);
        }else if(encoding.type == partial_domain){  
            fun_bootstrap_pk->bootstrap(ct,  acc, ct); 
        }else if(encoding.type == signed_limied_short_int){    
            LWECT c_in_copy(ct->param);
            ct->add(&c_in_copy, encoding.encode_message(encoding.plaintext_space));
            fun_bootstrap_pk->bootstrap(ct, acc, &c_in_copy);   
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

void KluczniakRandomizedBootstrapping::sanitize(LWECT *ct, PlaintextEncoding encoding){
    auto fun_identity = [](long m) -> long {
        return m; 
    };   
    std::shared_ptr<VectorCTAccumulator> acc(accumulator_builder->prepare_accumulator(fun_identity, encoding));
    LWECT ct_of_zero(masking_pk->param);
    masking_pk->encrypt(&ct_of_zero, 0);
    ct->add(ct, &ct_of_zero); 
    /// TODO: This part should be in the FunctionalBootstrap public key - change it also in fhe_context examples
    if(encoding.type == full_domain){    
        fun_bootstrap_pk->full_domain_bootstrap(ct, acc, ct, encoding);
    }else if(encoding.type == partial_domain){  
        fun_bootstrap_pk->bootstrap(ct,  acc, ct); 
    }else if(encoding.type == signed_limied_short_int){    
        LWECT c_in_copy(ct->param);
        ct->add(&c_in_copy, encoding.encode_message(encoding.plaintext_space));
        fun_bootstrap_pk->bootstrap(ct, acc, &c_in_copy);   
    } 
}


