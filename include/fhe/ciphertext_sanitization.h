#ifndef CIPHERTEXT_SANITIZATION_H
#define CIPHERTEXT_SANITIZATION_H

#include "lwe.h"
#include "functional_bootstrap.h"
 
namespace fhe_deck{
  
class SanitizationKey{

    public: 

    virtual ~SanitizationKey() = default;

    virtual void sanitize(LWECT *ct_out, LWECT *ct_in, PlaintextEncoding encoding) = 0;

    template <class Archive>
    void save( Archive & ar ) const
    {     
    }
        
    template <class Archive>
    void load( Archive & ar )
    {    
    }    

};


class DucasStehleWashingMachine : public SanitizationKey{
 
    public: 

        std::shared_ptr<FunctionalBootstrapPublicKey> fun_bootstrap_pk; 

        std::shared_ptr<AbstractAccumulatorBuilder> accumulator_builder;

        std::shared_ptr<LWEPublicKey> masking_pk; 

        int washing_cycles;

        ~DucasStehleWashingMachine() = default;

        DucasStehleWashingMachine() = default;

        DucasStehleWashingMachine(
            std::shared_ptr<FunctionalBootstrapPublicKey> fun_bootstrap_pk, 
            std::shared_ptr<AbstractAccumulatorBuilder> accumulator_builder,
            std::shared_ptr<LWEPublicKey> masking_pk,
            int washing_cycles);

        void sanitize(LWECT *ct_out, LWECT *ct_in, PlaintextEncoding encoding); 

    template <class Archive>
    void save( Archive & ar ) const
    {    
        ar(cereal::base_class<SanitizationKey>(this));     
        ar(fun_bootstrap_pk, accumulator_builder, masking_pk, washing_cycles);
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
        ar(cereal::base_class<SanitizationKey>(this));     
        ar(fun_bootstrap_pk, accumulator_builder, masking_pk, washing_cycles);
    }    

};


class KluczniakRandomizedBootstrapping : public SanitizationKey{
 
    public: 

        std::shared_ptr<FunctionalBootstrapPublicKey> fun_bootstrap_pk; 

        std::shared_ptr<AbstractAccumulatorBuilder> accumulator_builder;

        std::shared_ptr<LWEPublicKey> masking_pk; 
  
        ~KluczniakRandomizedBootstrapping() = default;

        KluczniakRandomizedBootstrapping() = default;

        KluczniakRandomizedBootstrapping(
            std::shared_ptr<FunctionalBootstrapPublicKey> fun_bootstrap_pk, 
            std::shared_ptr<AbstractAccumulatorBuilder> accumulator_builder,
            std::shared_ptr<LWEPublicKey> masking_pk);

        void sanitize(LWECT *ct_out, LWECT *ct_in, PlaintextEncoding encoding); 

    template <class Archive>
    void save( Archive & ar ) const
    {    
        ar(cereal::base_class<SanitizationKey>(this));     
        ar(fun_bootstrap_pk, accumulator_builder, masking_pk);
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
        ar(cereal::base_class<SanitizationKey>(this));     
        ar(fun_bootstrap_pk, accumulator_builder, masking_pk);
    }    
};

}


CEREAL_REGISTER_TYPE(fhe_deck::DucasStehleWashingMachine)
CEREAL_REGISTER_TYPE(fhe_deck::KluczniakRandomizedBootstrapping)

#endif 