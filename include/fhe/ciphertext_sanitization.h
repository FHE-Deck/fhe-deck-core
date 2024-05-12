#ifndef CIPHERTEXT_SANITIZATION_H
#define CIPHERTEXT_SANITIZATION_H

#include "lwe.h"
#include "functional_bootstrap.h"
 
namespace fhe_deck{
  
class SanitizationKey{

    public: 

    virtual void sanitize(LWECT *ct, PlaintextEncoding encoding) = 0;
};


class DucasStehleWashingMachine : public SanitizationKey{
 
    public: 

        std::shared_ptr<FunctionalBootstrapPublicKey> fun_bootstrap_pk; 

        std::shared_ptr<AbstractAccumulatorBuilder> accumulator_builder;

        std::shared_ptr<LWEPublicKey> masking_pk; 

        int washing_cycles;

        DucasStehleWashingMachine(
            std::shared_ptr<FunctionalBootstrapPublicKey> fun_bootstrap_pk, 
            std::shared_ptr<AbstractAccumulatorBuilder> accumulator_builder,
            std::shared_ptr<LWEPublicKey> masking_pk,
            int washing_cycles);

        void sanitize(LWECT *ct, PlaintextEncoding encoding); 
};


class KluczniakRandomizedBootstrapping : public SanitizationKey{
 
    public: 

        std::shared_ptr<FunctionalBootstrapPublicKey> fun_bootstrap_pk; 

        std::shared_ptr<AbstractAccumulatorBuilder> accumulator_builder;

        std::shared_ptr<LWEPublicKey> masking_pk; 
  
        KluczniakRandomizedBootstrapping(
            std::shared_ptr<FunctionalBootstrapPublicKey> fun_bootstrap_pk, 
            std::shared_ptr<AbstractAccumulatorBuilder> accumulator_builder,
            std::shared_ptr<LWEPublicKey> masking_pk);

        void sanitize(LWECT *ct, PlaintextEncoding encoding); 
};

}

#endif 