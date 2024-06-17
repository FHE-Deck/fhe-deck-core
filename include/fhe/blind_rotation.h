#ifndef BLIND_ROTATION_H
#define BLIND_ROTATION_H

#include "lwe.h"
#include "rlwe.h" 
#include "ntru.h" 
#include "rotation_poly.h"
#include "vector_ciphertext.h"

namespace fhe_deck{

 
class VectorCTAccumulator{ 

    public:

    std::shared_ptr<VectorCT> acc_content; 
    RotationPoly rot_poly;
    RotationPoly rot_poly_amortized;   
    bool amortization = false;
    
    VectorCTAccumulator(std::shared_ptr<VectorCT> acc_content, RotationPoly rot_poly, bool amortization = true);

    VectorCTAccumulator(std::shared_ptr<VectorCT> acc_content, bool amortization = false);
  
    VectorCTAccumulator(VectorCTAccumulator &other);
 
    VectorCTAccumulator& operator=(const VectorCTAccumulator other);
};

class HomomorphicAccumulator{
    public:
 
    std::shared_ptr<VectorCTAccumulator> accumulator;

    HomomorphicAccumulator(std::shared_ptr<VectorCTAccumulator> accumulator){
        this->accumulator = accumulator;
    }
};

class AbstractAccumulatorBuilder{

    public:
    
    virtual VectorCTAccumulator* prepare_accumulator(long (*f)(long message), PlaintextEncoding output_encoding) = 0;

    virtual VectorCTAccumulator* prepare_accumulator(long (*f)(long message, long plaintext_space), PlaintextEncoding output_encoding) = 0;

    virtual VectorCTAccumulator* get_acc_msb() = 0;
  
    virtual VectorCTAccumulator* get_acc_one(PlaintextEncoding output_encoding) = 0; 

    template <class Archive>
    void save( Archive & ar ) const { }
        
    template <class Archive>
    void load( Archive & ar ) { } 

};

class RLWEAccumulatorBuilder : public AbstractAccumulatorBuilder{

    public:

    std::shared_ptr<RLWEParam> param;

    RLWEAccumulatorBuilder() = default;

    RLWEAccumulatorBuilder(std::shared_ptr<RLWEParam> param);

    VectorCTAccumulator* prepare_accumulator(long (*f)(long message), PlaintextEncoding output_encoding);

    VectorCTAccumulator* prepare_accumulator(long (*f)(long message, long plaintext_space), PlaintextEncoding output_encoding); 
  
    VectorCTAccumulator* get_acc_msb();
  
    VectorCTAccumulator* get_acc_one(PlaintextEncoding output_encoding);

    template <class Archive>
    void save( Archive & ar ) const { 
        ar(cereal::base_class<AbstractAccumulatorBuilder>(this));    
        ar(param);
    }
        
    template <class Archive>
    void load( Archive & ar ) { 
        ar(cereal::base_class<AbstractAccumulatorBuilder>(this));    
        ar(param);
    } 
};
  

class NTRUAccumulatorBuilder : public AbstractAccumulatorBuilder{

    public:

    std::shared_ptr<NTRUParam> param;
    /// TODO: Need to make a public version. 
    std::shared_ptr<NTRUSK> sk;
    bool is_sk_set = false;

    NTRUAccumulatorBuilder() = default;

    NTRUAccumulatorBuilder(std::shared_ptr<NTRUSK> sk);

    VectorCTAccumulator* prepare_accumulator(long (*f)(long message), PlaintextEncoding output_encoding);

    VectorCTAccumulator* prepare_accumulator(long (*f)(long message, long plaintext_space), PlaintextEncoding output_encoding); 
  
    VectorCTAccumulator* get_acc_msb();
  
    VectorCTAccumulator* get_acc_one(PlaintextEncoding output_encoding);

    template <class Archive>
    void save( Archive & ar ) const { 
        ar(cereal::base_class<AbstractAccumulatorBuilder>(this));    
        ar(param, sk);
    }
        
    template <class Archive>
    void load( Archive & ar ) { 
        ar(cereal::base_class<AbstractAccumulatorBuilder>(this));    
        ar(param, sk);
        this->is_sk_set = true;
    } 
};
  
/*
    Interface for outputs of a blind rotation algorithm.
    I could use VectorCT instead, but I decided to go with a new interface because post rotation with an VectorCTAccumulator 
    I don't feal that it belongs within the scope of an ciphertext.
*/ 
class BlindRotateOutput{

    public:

    VectorCT* accumulator;

    virtual ~BlindRotateOutput() = default;
   
    virtual void extract_lwe(LWECT* out) = 0;

    virtual void post_rotation(std::shared_ptr<BlindRotateOutput> bl_out, std::shared_ptr<VectorCTAccumulator> acc) = 0; 
};

class BlindRotateOutputBuilder{

    public: 

    virtual BlindRotateOutput* build() = 0; 

    template <class Archive>
    void save( Archive & ar ) const { }
        
    template <class Archive>
    void load( Archive & ar ) { } 
};

class RLWEBlindRotateOutputBuilder : public BlindRotateOutputBuilder{

    public: 
  
    std::shared_ptr<RLWEParam> rlwe_param;

    RLWEBlindRotateOutputBuilder() = default;   
  
    RLWEBlindRotateOutputBuilder(std::shared_ptr<RLWEParam> param);
  
    BlindRotateOutput* build(); 

    template <class Archive>
    void save( Archive & ar ) const { 
        ar(cereal::base_class<BlindRotateOutputBuilder>(this));    
        ar(rlwe_param);
    }
        
    template <class Archive>
    void load( Archive & ar ) { 
        ar(cereal::base_class<BlindRotateOutputBuilder>(this));    
        ar(rlwe_param);
    } 
};


class NTRUBlindRotateOutputBuilder : public BlindRotateOutputBuilder{

    public: 
   
    std::shared_ptr<NTRUParam> ntru_param;

    NTRUBlindRotateOutputBuilder() = default;
 
    NTRUBlindRotateOutputBuilder(std::shared_ptr<NTRUParam> param);

    BlindRotateOutput* build(); 

    template <class Archive>
    void save( Archive & ar ) const { 
        ar(cereal::base_class<BlindRotateOutputBuilder>(this));    
        ar(ntru_param);
    }
        
    template <class Archive>
    void load( Archive & ar ) { 
        ar(cereal::base_class<BlindRotateOutputBuilder>(this));    
        ar(ntru_param);
    } 
};

class RLWEBlindRotateOutput : public BlindRotateOutput{

    public:
    // Will point at the VectorCT accumulator. 
    // I will do casting already in the constructor. 
    // The pointer is freed in the destructor. 
    RLWECT* accumulator_ptr;

    ~RLWEBlindRotateOutput();
    
    RLWEBlindRotateOutput(std::shared_ptr<RLWEParam> param);

    void extract_lwe(LWECT* out);

    void post_rotation(std::shared_ptr<BlindRotateOutput> bl_out, std::shared_ptr<VectorCTAccumulator> acc); 
};

class NTRUBlindRotateOutput : public BlindRotateOutput{

    public:
    // Will point at the VectorCT accumulator. I will do casting already in the constructor. 
    // The pointer is freed in the destructor. 
    NTRUCT* accumulator_ptr;

    ~NTRUBlindRotateOutput();
    
    NTRUBlindRotateOutput(std::shared_ptr<NTRUParam> param);
  
    void extract_lwe(LWECT* out);

    void post_rotation(std::shared_ptr<BlindRotateOutput> bl_out, std::shared_ptr<VectorCTAccumulator> acc); 
};
 
class BlindRotationPublicKey{
 
    public:

    virtual ~BlindRotationPublicKey() = default;
   
    std::shared_ptr<LWEParam> lwe_par;  
  
    virtual void blind_rotate(VectorCT* out, LWECT* lwe_ct_in, std::shared_ptr<VectorCTAccumulator> acc_msg) = 0;

    template <class Archive>
    void save( Archive & ar ) const {
        ar(lwe_par);    
    }
        
    template <class Archive>
    void load( Archive & ar ) {
        ar(lwe_par);    
    } 

};
 
}/// End of namespace fhe_deck

CEREAL_REGISTER_TYPE(fhe_deck::RLWEAccumulatorBuilder)
CEREAL_REGISTER_TYPE(fhe_deck::NTRUAccumulatorBuilder) 
CEREAL_REGISTER_TYPE(fhe_deck::RLWEBlindRotateOutputBuilder)
CEREAL_REGISTER_TYPE(fhe_deck::NTRUBlindRotateOutputBuilder)

#endif 