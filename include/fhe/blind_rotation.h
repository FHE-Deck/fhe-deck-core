#ifndef BLIND_ROTATION_H
#define BLIND_ROTATION_H

#include "lwe.h"
#include "rlwe.h" 
#include "rotation_poly.h"


namespace fhe_deck{



class AbstractAccumulator{
    public:

    virtual void setup_amortization()  = 0;

};



class HomomorphicAccumulator{
    public:

    HomomorphicAccumulator(std::shared_ptr<AbstractAccumulator> accumulator){
        this->accumulator = accumulator;
    }

    std::shared_ptr<AbstractAccumulator> accumulator;

};

class RotationPolyAccumulator : public AbstractAccumulator{ 

    public:

    RotationPolyAccumulator(RotationPoly rot_poly);

    void setup_amortization();

    RotationPoly rot_poly;
    RotationPoly rot_poly_amortized;  
};

  
/*
    Wrapps the output of a blind rotation algorithm.
    For instance can be a RLWE, NTRU, and other.

    Its a wrapper, because from the point aaf view of a ciphertext class, I dop't need post_rotation for instance.
*/
class BlindRotateOutput{

    public:

    BlindRotationOutputType type;

    RLWECT* rlwe_ct; 

    ~BlindRotateOutput();

    BlindRotateOutput(RLWECT* rlwe_ct);

    void extract_lwe(long* lwe_ct);

    void post_rotation(std::shared_ptr<BlindRotateOutput> bl_out, std::shared_ptr<AbstractAccumulator> acc);

};




class BlindRotationPublicKey{
 
    public:

    virtual ~BlindRotationPublicKey(){};

    // Size of the rotation vector.
    // For example in FHEW over Z[X]/(X^N + 1), rotation_size = 2*N
    // But if we implement over Z[X]/(X^N - 1), then the rotation size would be 2*N
    long rotation_size;

    // The actual size of the rotation vector. 
    // For exmaple over Z[X]/(X^N + 1), the actual rotation size is N, because the polynomials have N coefficients.
    // Over Z[X]/(X^N - 1) then the rotation size and the actual rotation 
    long actual_rotation_size;

    // LWE after modulus switching to rotation_size;
    std::shared_ptr<LWEParam> lwe_par;  

    // LWE after modulus switching to rotation_size;
    std::shared_ptr<LWEParam> actual_lwe_par;   
 
    virtual void blind_rotate(std::shared_ptr<BlindRotateOutput> out, long* lwe_ct_in, std::shared_ptr<AbstractAccumulator> acc_msg, GadgetMulMode mode = deter) = 0;
   
    virtual std::shared_ptr<BlindRotateOutput> init_blind_rotate_output() = 0; 

    virtual std::shared_ptr<AbstractAccumulator> prepare_accumulator(long (*f)(long message), PlaintextEncoding output_encoding) = 0;

    virtual std::shared_ptr<AbstractAccumulator> prepare_accumulator(long (*f)(long message, long plaintext_space), PlaintextEncoding output_encoding) = 0;

    // TODO: Here I actually need some accumulator setup, and these have to be somehow defined there.
    virtual std::shared_ptr<AbstractAccumulator> get_acc_msb() = 0;
    virtual std::shared_ptr<AbstractAccumulator> get_acc_one(PlaintextEncoding output_encoding) = 0;
  
};


}

#endif 