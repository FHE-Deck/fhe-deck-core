#ifndef BLIND_ROTATION_H
#define BLIND_ROTATION_H


/**
 * @file blind_rotation.h
 */


#include "lwe.h"
#include "rlwe.h" 
#include "ntru.h" 
#include "rotation_poly.h"
#include "vector_ciphertext.h"

namespace fhe_deck{

/**
 * @brief This class is used by blind rotation implementations. It is takes as a mandatory imput to blind rotation.
 * Typically it holds a rotation polynomial, or a RLWE/NTRU ciphertext encrypting a rotation polynomial. 
 */
class VectorCTAccumulator{ 

    public:
    /// @brief Vector ciphertext, that defines the content of the Accumulator.
    std::shared_ptr<VectorCT> acc_content; 
    /// @brief Rotation Polynomial
    RotationPoly rot_poly;
    /// @brief Rotation Polynomial that is prepared for amortization.
    RotationPoly rot_poly_amortized;   
    bool amortization = false;
    
    VectorCTAccumulator(std::shared_ptr<VectorCT> acc_content, RotationPoly rot_poly, bool amortization = true);

    VectorCTAccumulator(std::shared_ptr<VectorCT> acc_content, bool amortization = false);
  
    VectorCTAccumulator(VectorCTAccumulator &other);
 
    VectorCTAccumulator& operator=(const VectorCTAccumulator other);
};

/**
 * @brief Encapsulates the VectorCTAccumulator. 
 * This class is only used by the very high level interface (FHEContext) so that programmers don't have to deal with smart pointers at the high-level. 
 */
class HomomorphicAccumulator{
    public:
    /// @brief The smart pointer that we wan to encapsulate. 
    std::shared_ptr<VectorCTAccumulator> accumulator;

    HomomorphicAccumulator(std::shared_ptr<VectorCTAccumulator> accumulator){
        this->accumulator = accumulator;
    }
};

 /// TODO: Check what this exactly does, and whether we can implement it with existing accumulators.
 /**
  * @brief Implements VectorCTAccumulator.
  */
class FunctionalAccumulator : public VectorCTAccumulator {

    public:
        using BootFunction = std::function<long(long,long)>;

        Polynomial poly_msb_0;
        Polynomial poly_msb_1;

        BootFunction func;
        long (*func_ptr)(long message, long plaintext_space);

        // debug
        Polynomial sk;

        FunctionalAccumulator(const BootFunction& boot_F, long dim, long coef_modulus, PlaintextEncoding encoding);

        FunctionalAccumulator(long (*f)(long message, long plaintext_space), long dim, long coef_modulus, PlaintextEncoding encoding); 
};

/**
 * @brief This class is used to build a VectorCTAccumulator object.  It implements various methods to build an accumulator. 
 */
class AbstractAccumulatorBuilder{

    public:
    
    /// @brief Build an accumulator given a function specification and an output encoding specifying how plaintexts should be encoded.
    /// @param f The function that blind rotation given the accumulator should compute.
    /// @param output_encoding The encoding of the plaintexts. 
    /// @return Returns a new object of VectorCTAccumulator.
    virtual VectorCTAccumulator* prepare_accumulator(int64_t (*f)(int64_t message), PlaintextEncoding output_encoding) = 0;

    /// @brief Build an accumulator given a function specification and an output encoding specifying how plaintexts should be encoded.
    /// @param f The function that blind rotation given the accumulator should compute.
    /// @param output_encoding The encoding of the plaintexts. 
    /// @return Returns a new object of VectorCTAccumulator.
    virtual VectorCTAccumulator* prepare_accumulator(int64_t (*f)(int64_t message, int64_t plaintext_space), PlaintextEncoding output_encoding) = 0;

    /// @brief This is a special function, that returns a accumulator which after blind rotation will return the most significant bit of the message. 
    /// @return Returns a new object of VectorCTAccumulator.
    /// NOTE: The most signifficant bit is computed by rotating a polynomial over a negacyclic polynomial ring. This accumulator is used by LMPFunctionalBootstrapPublicKey 
    virtual VectorCTAccumulator* get_acc_sgn(PlaintextEncoding output_encoding) = 0;

    /// @brief This is a special function, that returns a accumulator which after blind rotation will return the most significant bit of the message. 
    /// @return Returns a new object of VectorCTAccumulator.
    /// NOTE: The most signifficant bit is computed by rotating a polynomial over a negacyclic polynomial ring. This accumulator is used by LMPFunctionalBootstrapPublicKey 
    virtual VectorCTAccumulator* get_acc_msb(PlaintextEncoding output_encoding) = 0;
  
    /// @brief This is a special function, that returns an VectorCTAccumulator that has in its first position "1", and other positions are "0".
    /// @return Returns a new object of VectorCTAccumulator.
    /// NOTE: This accumulator is used by LMPFunctionalBootstrapPublicKey 
    virtual VectorCTAccumulator* get_acc_one(PlaintextEncoding output_encoding) = 0; 

    template <class Archive>
    void save( Archive & ar ) const { }
        
    template <class Archive>
    void load( Archive & ar ) { } 

};

/**
 * @brief Build VectorCTAccumulator where the VectorCT is a RLWE ciphertext.
 */
class RLWEAccumulatorBuilder : public AbstractAccumulatorBuilder{

    public:
    /// @brief The RLWE parameters.
    std::shared_ptr<RLWEParam> param;

    RLWEAccumulatorBuilder() = default;

    RLWEAccumulatorBuilder(std::shared_ptr<RLWEParam> param);

    /// @brief Computes a VectorCTAccumulator that embeds the function f.
    /// @param f The funciton f.
    /// @param output_encoding The plaintext encoding used to encode messages on the vector accumulator.
    /// @return Pointer to the new vector CTAccumulator object.
    VectorCTAccumulator* prepare_accumulator(int64_t (*f)(int64_t message), PlaintextEncoding output_encoding);

    /// @brief Computes a VectorCTAccumulator that embeds the function f.
    /// @param f The funciton f.
    /// @param output_encoding The plaintext encoding used to encode messages on the vector accumulator.
    /// @return Pointer to the new vector CTAccumulator object.
    VectorCTAccumulator* prepare_accumulator(int64_t (*f)(int64_t message, int64_t plaintext_space), PlaintextEncoding output_encoding); 
  
    /// @brief Return a Accumulator that computes the most significant bit of the message.
    /// @return The accumulator. 
    VectorCTAccumulator* get_acc_sgn(PlaintextEncoding output_encoding);
  
    VectorCTAccumulator* get_acc_msb(PlaintextEncoding output_encoding);
  
    /// @brief Return a acccumulator that has its first position set to 1, and all other positions set to 0.
    /// @param output_encoding The encoding used to encode the first position to 1.
    /// @return Pointer to the new vector CTAccumulator object.
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
  
/**
 * @brief Build VectorCTAccumulator where the VectorCT is a NTRU ciphertext.
 */
class NTRUAccumulatorBuilder : public AbstractAccumulatorBuilder{

    public:

    /// @brief The NTRU parameters.
    std::shared_ptr<NTRUParam> param;

    /// @brief The NTRU parameters.
    /// TODO: Need to make a public version. 
    std::shared_ptr<NTRUSK> sk;
    /// @brief A flag indicating whether the secret key is set.
    bool is_sk_set = false;

    NTRUAccumulatorBuilder() = default;

    NTRUAccumulatorBuilder(std::shared_ptr<NTRUSK> sk);

    /// @brief Computes a VectorCTAccumulator that embeds the function f.
    /// @param f The funciton f.
    /// @param output_encoding The plaintext encoding used to encode messages on the vector accumulator.
    /// @return Pointer to the new vector CTAccumulator object.
    VectorCTAccumulator* prepare_accumulator(int64_t (*f)(int64_t message), PlaintextEncoding output_encoding);

    /// @brief Computes a VectorCTAccumulator that embeds the function f.
    /// @param f The funciton f.
    /// @param output_encoding The plaintext encoding used to encode messages on the vector accumulator.
    /// @return Pointer to the new vector CTAccumulator object.
    VectorCTAccumulator* prepare_accumulator(int64_t (*f)(int64_t message, int64_t plaintext_space), PlaintextEncoding output_encoding); 
  
    /// @brief Return a Accumulator that computes the most significant bit of the message.
    /// @return The accumulator. 
    VectorCTAccumulator* get_acc_sgn(PlaintextEncoding output_encoding);

    VectorCTAccumulator* get_acc_msb(PlaintextEncoding output_encoding);
  
    /// @brief Return a acccumulator that has its first position set to 1, and all other positions set to 0.
    /// @param output_encoding The encoding used to encode the first position to 1.
    /// @return Pointer to the new vector CTAccumulator object.
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
   
/**
 * @brief Interface for outputs of a blind rotation algorithm.
    I could use VectorCT instead, but I decided to go with a new interface because post rotation with an VectorCTAccumulator 
    I don't feal that it belongs within the scope of an ciphertext.
 */
class BlindRotateOutput{

    public:
    /// @brief The accumulator. Its the ouptut VectorCT that is the product of blind rotation.  
    VectorCT* accumulator;

    /// @brief The destructor.
    virtual ~BlindRotateOutput() = default;
   
    /// @brief Extracts a LWE ciphertext from the accumulator.
    /// @param out The output LWE ciphertext.
    virtual void extract_lwe(LWECT& out) = 0;

    /// @brief Performs post rotation. For multi-value bootstrapping this is the step where the accumulator is updated. Its called post rotation, because we usually use it after a blind rotation. 
    /// @param bl_out Output of the post rotation. 
    /// @param acc The accumulator that is used to update this blind rotation output.
    virtual void post_rotation(std::shared_ptr<BlindRotateOutput> bl_out, std::shared_ptr<VectorCTAccumulator> acc) = 0; 
};

/**
 * @brief Interface for builders of blind rotation outputs. Currently, implemented by RLWEBlindRotateOutputBuilder and NTRUBlindRotateOutputBuilder.
 */
class BlindRotateOutputBuilder{

    public: 

    /// @brief Build LWEParameters that are used by extracted LWE Ciphertexts. 
    /// @return A new object of LWEParam.
    virtual LWEParam* build_extract_lwe_param() = 0;

    virtual BlindRotateOutput* build() = 0; 

    template <class Archive>
    void save( Archive & ar ) const { }
        
    template <class Archive>
    void load( Archive & ar ) { } 
};

/**
 * @brief Builder for RLWEBlindRotateOutput.
 */
class RLWEBlindRotateOutputBuilder : public BlindRotateOutputBuilder{

    public: 
    /// @brief The RLWE parameters.
    std::shared_ptr<RLWEParam> rlwe_param;

    RLWEBlindRotateOutputBuilder() = default;   
  
    RLWEBlindRotateOutputBuilder(std::shared_ptr<RLWEParam> param);
  
    LWEParam* build_extract_lwe_param();

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

/**
 * @brief Builder for NTRUBlindRotateOutput.
 */
class NTRUBlindRotateOutputBuilder : public BlindRotateOutputBuilder{

    public: 
    /// @brief The NTRU parameters.
    std::shared_ptr<NTRUParam> ntru_param;

    NTRUBlindRotateOutputBuilder() = default;
 
    NTRUBlindRotateOutputBuilder(std::shared_ptr<NTRUParam> param);

    LWEParam* build_extract_lwe_param();

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

/**
 * @brief Implementation of BlindRotateOutput, where the output of blind rotation is a RLWE ciphertext.
 */
class RLWEBlindRotateOutput : public BlindRotateOutput{

    public:
    
    /// @brief The accumulator pointer.  Will point at the VectorCT accumulator. I will do casting already in the constructor. The pointer is freed in the destructor. 
    RLWECT* accumulator_ptr;

    ~RLWEBlindRotateOutput();
    
    RLWEBlindRotateOutput(std::shared_ptr<RLWEParam> param);

    void extract_lwe(LWECT& out);

    void post_rotation(std::shared_ptr<BlindRotateOutput> bl_out, std::shared_ptr<VectorCTAccumulator> acc); 
};

/**
 * @brief Implementation of BlindRotateOutput, where the output of blind rotation is a NTRU ciphertext.
 */
class NTRUBlindRotateOutput : public BlindRotateOutput{

    public:

    /// @brief The accumulator pointer.  Will point at the VectorCT accumulator. I will do casting already in the constructor. The pointer is freed in the destructor. 
    NTRUCT* accumulator_ptr;

    ~NTRUBlindRotateOutput();
    
    NTRUBlindRotateOutput(std::shared_ptr<NTRUParam> param);
  
    void extract_lwe(LWECT& out);

    void post_rotation(std::shared_ptr<BlindRotateOutput> bl_out, std::shared_ptr<VectorCTAccumulator> acc); 
};
 

/**
 * @brief Interface for blind rotation public keys. This is the interface for the core functionality of bootstrapping. 
 */
class BlindRotationPublicKey{
 
    public:

    /// @brief The destructor.
    virtual ~BlindRotationPublicKey() = default;
   
    /// @brief LWE parameters, that specify the LWE ciphertexts that is decrypted in blind rotation.
    std::shared_ptr<LWEParam> lwe_par;  
  
    /// @brief The blind rotation algorithm.
    /// @param out Output accumulator which is a VectorCT (held usually by a BlindRotationOutput object)
    /// @param lwe_ct_in The input LWE ciphertext that we are going decrypt.
    /// @param acc_msg A VectorCTAccumulator specifying the function that the blind rotation should compute, on the decrypted plaintext.  
    virtual void blind_rotate(VectorCT& out, LWECT& lwe_ct_in, std::shared_ptr<VectorCTAccumulator> acc_msg) = 0;

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