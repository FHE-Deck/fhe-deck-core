#ifndef BLIND_ROTATION_H
#define BLIND_ROTATION_H

#include "lwe.h"
#include "rlwe.h" 
#include "rotation_poly.h"
#include "vector_ciphertext.h"

namespace fhe_deck{

 
class VectorCTAccumulator{ 

    public:

    std::shared_ptr<VectorCT> acc; 
    RotationPoly rot_poly;
    RotationPoly rot_poly_amortized;   
    bool amortization = false;
  
    VectorCTAccumulator(std::shared_ptr<RLWEParam> param, RotationPoly rot_poly, bool amortization = true);

    VectorCTAccumulator(std::shared_ptr<VectorCT> acc, bool amortization = false);
  
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

};

class RLWEAccumulatorBuilder : public AbstractAccumulatorBuilder{

    public:

    std::shared_ptr<RLWEParam> param;

    RLWEAccumulatorBuilder(std::shared_ptr<RLWEParam> param);

    VectorCTAccumulator* prepare_accumulator(long (*f)(long message), PlaintextEncoding output_encoding);

    VectorCTAccumulator* prepare_accumulator(long (*f)(long message, long plaintext_space), PlaintextEncoding output_encoding); 

    /// TODO: Implement the following.
    //VectorCTAccumulator* prepare_accumulator(VectorCT* acc, PlaintextEncoding output_encoding); 

    VectorCTAccumulator* get_acc_msb();
  
    VectorCTAccumulator* get_acc_one(PlaintextEncoding output_encoding);
};
 
/*
    Interface for outputs of a blind rotation algorithm.
    I could use VectorCT instead, but I decided to go with a new interface because post rotation with an VectorCTAccumulator 
    I don't feal that it belongs within the scope of an ciphertext.
*/ 
class BlindRotateOutput{

    public:

    VectorCT* accumulator;

    ~BlindRotateOutput(){};
  
    /// TODO: Input should be LWECT 
    //virtual void extract_lwe(long* lwe_ct) = 0;
    virtual void extract_lwe(LWECT* out) = 0;

    virtual void post_rotation(std::shared_ptr<BlindRotateOutput> bl_out, std::shared_ptr<VectorCTAccumulator> acc) = 0; 
};

class BlindRotateOutputBuilder{

    public: 

    virtual BlindRotateOutput* build() = 0; 
};

class RLWEBlindRotateOutputBuilder : public BlindRotateOutputBuilder{

    public: 

    std::shared_ptr<RLWEParam> param;

    RLWEBlindRotateOutputBuilder(std::shared_ptr<RLWEParam> param);

    BlindRotateOutput* build(); 
};

class RLWEBlindRotateOutput : public BlindRotateOutput{

    public:
    // Will point at the VectorCT accumulator. I will do casting already in the constructor. 
    // The pointer is freed in the destructor. 
    RLWECT* accumulator_ptr;

    ~RLWEBlindRotateOutput();
    
    RLWEBlindRotateOutput(std::shared_ptr<RLWEParam> param);

    //void extract_lwe(long* lwe_ct);

    void extract_lwe(LWECT* out);

    void post_rotation(std::shared_ptr<BlindRotateOutput> bl_out, std::shared_ptr<VectorCTAccumulator> acc); 
};
 
class BlindRotationPublicKey{
 
    public:

    virtual ~BlindRotationPublicKey(){};
   
    std::shared_ptr<LWEParam> lwe_par;  
  
    virtual void blind_rotate(VectorCT* out, LWECT* lwe_ct_in, std::shared_ptr<VectorCTAccumulator> acc_msg) = 0;

};
 
}// End of namespace fhe_deck

#endif 