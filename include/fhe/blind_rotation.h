#ifndef BLIND_ROTATION_H
#define BLIND_ROTATION_H


/**
 * @file blind_rotation.h
 */

#include "global_headers.h"

#include "ciphertexts/lwe.h"
#include "ciphertexts/rlwe.h" 
#include "ciphertexts/ntru.h" 
#include "ciphertexts/vector_ciphertext.h"
#include "interface/rotation_poly.h"

namespace FHEDeck{
 
/**
 * @brief Common interface to specify functions for functional bootstrapping. 
 */
class FunctionSpecification{

};

/**
 * @brief This class is used by blind rotation implementations. It is takes as a mandatory imput to blind rotation.
 * Typically it holds a rotation polynomial, or a RLWE/NTRU ciphertext encrypting a rotation polynomial. 
 * TODO: Perhpas we should revisit the use of VectorCTAccumulator as well as PreparedVectorCTAccumulators and other. 
 * After revisiting the code after a year, I don't have a immediate answer as to why these classes should exist.
 *  Maybe it can be done easier.
 */
class VectorCTAccumulator : public FunctionSpecification{ 

    protected:

    /// @brief Vector ciphertext, that defines the content of the Accumulator.
    std::shared_ptr<VectorCT> m_acc_content; 

    public:
 
    VectorCTAccumulator(std::shared_ptr<VectorCT> acc_content);
  
    VectorCTAccumulator(VectorCTAccumulator &other);
 
    VectorCTAccumulator& operator=(const VectorCTAccumulator other);

    std::shared_ptr<const VectorCT> content()const;
 
};
 
class PolynomialSpecification : public FunctionSpecification{

    protected:
    /// @brief Rotation Polynomial
    RotationPoly m_rot_poly;

    public:
     
    PolynomialSpecification(RotationPoly rot_poly);

    RotationPoly poly();
};
 
 /**
  * @brief Implements VectorCTAccumulator.
  */
class KSFunctionSpecification : public FunctionSpecification {

    public: 

        Polynomial poly_msb_0;
        Polynomial poly_msb_1; 
 
        KSFunctionSpecification(const std::function<long(long,long)> f, long dim, long coef_modulus, PlaintextEncoding input_encoding); 
 
};


/**
 * @brief Encapsulates the VectorCTAccumulator. 
 * This class is only used by the very high level interface (FHEContext) so that programmers don't have to deal with smart pointers at the high-level. 
 */
class HomomorphicAccumulator{
    public:
    /// @brief The smart pointer that we want to encapsulate. 
    std::shared_ptr<FunctionSpecification> boot_acc;
    std::shared_ptr<FunctionSpecification> func_boot_acc;
    std::shared_ptr<FunctionSpecification> multivalue_acc;

    PlaintextEncoding input_encoding;
    PlaintextEncoding output_encoding;

    HomomorphicAccumulator() = default;

    HomomorphicAccumulator(std::shared_ptr<FunctionSpecification> boot_acc, 
    std::shared_ptr<FunctionSpecification> func_boot_acc,
    std::shared_ptr<FunctionSpecification> multivalue_acc,
    PlaintextEncoding input_encoding,
    PlaintextEncoding output_encoding){
        this->boot_acc = boot_acc;
        this->func_boot_acc = func_boot_acc;
        this->multivalue_acc = multivalue_acc;
        this->input_encoding = input_encoding;
        this->output_encoding = output_encoding;
    }
 
    /// @brief Copy constructor
    HomomorphicAccumulator(const HomomorphicAccumulator& other){  
        if (this != &other) { 
            input_encoding = other.input_encoding;
            output_encoding = other.output_encoding;
            boot_acc = other.boot_acc;
            func_boot_acc = other.func_boot_acc;
            multivalue_acc = other.multivalue_acc; 
        }  
    }
 

    /// @brief Copy assignment operator
    HomomorphicAccumulator& operator=(const HomomorphicAccumulator& other) { 
        if (this != &other) {
            input_encoding = other.input_encoding;
            output_encoding = other.output_encoding;
            boot_acc = other.boot_acc;
            func_boot_acc = other.func_boot_acc;
            multivalue_acc = other.multivalue_acc; 
        }
        return *this;
    }


    /// @brief Move constructor
    HomomorphicAccumulator(HomomorphicAccumulator&& other){  
        if (this != &other) { 
            input_encoding = other.input_encoding;
            output_encoding = other.output_encoding;
            boot_acc = std::move(other.boot_acc);
            func_boot_acc = std::move(other.func_boot_acc);
            multivalue_acc = std::move(other.multivalue_acc); 
        }  
    }
 

    /// @brief Move assignment operator
    HomomorphicAccumulator& operator=(HomomorphicAccumulator&& other) { 
        if (this != &other) {
            input_encoding = other.input_encoding;
            output_encoding = other.output_encoding;
            boot_acc = std::move(other.boot_acc);
            func_boot_acc = std::move(other.func_boot_acc);
            multivalue_acc = std::move(other.multivalue_acc); 
        }
        return *this;
    } 
};

/**
 * @brief This class is used to build a VectorCTAccumulator object.  It implements various methods to build an accumulator. 
 */
class AbstractFunctionBuilder{

    public:
    

    /// @brief Build an accumulator given a function specification and an output encoding specifying how plaintexts should be encoded.
    /// @param f The function that blind rotation given the accumulator should compute. 
    /// @param input_encoding The encoding of the plaintexts in the input ciphertext. 
    /// @param output_encoding The encoding of the plaintexts in the output ciphertexts. 
    /// @return Returns a new object of VectorCTAccumulator.
    virtual std::shared_ptr<FunctionSpecification> prepare_specification(std::function<int64_t(int64_t)> f, PlaintextEncoding input_encoding, PlaintextEncoding output_encoding) = 0;
 
    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const { }
        
    template <class Archive>
    void load( Archive & ar ) { } 
    #endif 
};

class VectorCTAccumulatorBuilder : public AbstractFunctionBuilder{
 
    public:
    std::shared_ptr<VectorCTParam> param; 
  
    virtual std::shared_ptr<VectorCTAccumulator> prepare_accumulator(Vector& vec) = 0; 

    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const {
        ar(cereal::base_class<AbstractFunctionBuilder>(this));    
        ar(param);
     }
        
    template <class Archive>
    void load( Archive & ar ) { 
        ar(cereal::base_class<AbstractFunctionBuilder>(this));    
        ar(param);
    } 
    #endif 

};


class PolynomialSpecificationBuilder final : public AbstractFunctionBuilder{

    public:

    /// @brief The degree of the polynomial specification.
    int32_t degree;

    PolynomialSpecificationBuilder() = default;

    PolynomialSpecificationBuilder(int32_t degree);
 
    std::shared_ptr<FunctionSpecification> prepare_specification(std::function<int64_t(int64_t)> f, PlaintextEncoding input_encoding, PlaintextEncoding output_encoding) override;
  
    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const {
        ar(cereal::base_class<AbstractFunctionBuilder>(this));    
        ar(degree);
     }
        
    template <class Archive>
    void load( Archive & ar ) { 
        ar(cereal::base_class<AbstractFunctionBuilder>(this));    
        ar(degree);
    } 
    #endif 

};

class KSFunctionSpecificationBuilder final : public AbstractFunctionBuilder{

    public:

    int32_t degree;
    int64_t coef_modulus;

    KSFunctionSpecificationBuilder() = default;

    KSFunctionSpecificationBuilder(int32_t degree, int64_t coef_modulus);

    std::shared_ptr<FunctionSpecification> prepare_specification(std::function<int64_t(int64_t)> f, PlaintextEncoding input_encoding, PlaintextEncoding output_encoding) override;
 
    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const {
        ar(cereal::base_class<AbstractFunctionBuilder>(this));    
        ar(degree, coef_modulus);
    }
        
    template <class Archive>
    void load( Archive & ar ) { 
        ar(cereal::base_class<AbstractFunctionBuilder>(this));    
        ar(degree, coef_modulus);
    } 
    #endif 
};

/**
 * @brief Build VectorCTAccumulator where the VectorCT is a RLWE ciphertext.
 */
class RLWEAccumulatorBuilder final : public VectorCTAccumulatorBuilder{

    public: 

    RLWEAccumulatorBuilder() = default;

    RLWEAccumulatorBuilder(std::shared_ptr<RLWEParam> param);
 
    std::shared_ptr<FunctionSpecification> prepare_specification(std::function<int64_t(int64_t)> f, PlaintextEncoding input_encoding, PlaintextEncoding output_encoding) override;
 
    std::shared_ptr<VectorCTAccumulator> prepare_accumulator(Vector& vec) override;
   
    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const { 
        ar(cereal::base_class<VectorCTAccumulatorBuilder>(this));    
        //ar(param);
    }
        
    template <class Archive>
    void load( Archive & ar ) { 
        ar(cereal::base_class<VectorCTAccumulatorBuilder>(this));    
        //ar(param);
    } 
    #endif 
};
  
/**
 * @brief Build VectorCTAccumulator where the VectorCT is a NTRU ciphertext.
 */
class NTRUAccumulatorBuilder final : public VectorCTAccumulatorBuilder{

    public: 
    /// @brief The NTRU parameters.
    /// TODO: Need to make a public version. 
    std::shared_ptr<NTRUSK> sk;
    /// @brief A flag indicating whether the secret key is set.
    bool is_sk_set = false;

    NTRUAccumulatorBuilder() = default;

    NTRUAccumulatorBuilder(std::shared_ptr<NTRUSK> sk);

    std::shared_ptr<FunctionSpecification> prepare_specification(std::function<int64_t(int64_t)> f, PlaintextEncoding input_encoding, PlaintextEncoding output_encoding) override;
 
    std::shared_ptr<VectorCTAccumulator> prepare_accumulator(Vector& vec) override;
 
    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const { 
        ar(cereal::base_class<VectorCTAccumulatorBuilder>(this));    
        ar(sk);
    }
        
    template <class Archive>
    void load( Archive & ar ) { 
        ar(cereal::base_class<VectorCTAccumulatorBuilder>(this));    
        ar(sk);
        this->is_sk_set = true;
    } 
    #endif 
};


class PreparedVectorCTAccumulators{

    public: 

    std::shared_ptr<VectorCTAccumulatorBuilder> builder;

    PreparedVectorCTAccumulators() = default;

    PreparedVectorCTAccumulators(std::shared_ptr<VectorCTAccumulatorBuilder> builder);

    /// @brief Return a Accumulator that computes the most significant bit of the message.
    /// @return The accumulator. 
    std::shared_ptr<VectorCTAccumulator> get_acc_sgn(PlaintextEncoding output_encoding);

    std::shared_ptr<VectorCTAccumulator> get_acc_msb(PlaintextEncoding output_encoding);
  
    /// @brief Return a acccumulator that has its first position set to 1, and all other positions set to 0.
    /// @param output_encoding The encoding used to encode the first position to 1.
    /// @return Pointer to the new vector CTAccumulator object.
    std::shared_ptr<VectorCTAccumulator> get_acc_one(PlaintextEncoding output_encoding);

    std::shared_ptr<VectorCTAccumulator> get_pad_poly(PlaintextEncoding output_encoding);

    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const {
        ar(builder);
    }
        
    template <class Archive>
    void load( Archive & ar ) {
        ar(builder);
    }
    #endif  
 
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
    virtual void post_rotation(std::shared_ptr<BlindRotateOutput> bl_out, std::shared_ptr<FunctionSpecification> acc) = 0; 
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

    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const { }
        
    template <class Archive>
    void load( Archive & ar ) { }
    #endif  
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

    #if defined(USE_CEREAL)
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
    #endif 
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

    #if defined(USE_CEREAL)
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
    #endif 
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

    void post_rotation(std::shared_ptr<BlindRotateOutput> bl_out, std::shared_ptr<FunctionSpecification> acc); 
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

    void post_rotation(std::shared_ptr<BlindRotateOutput> bl_out, std::shared_ptr<FunctionSpecification> acc); 
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
    virtual void blind_rotate(VectorCT& out, const LWECT& lwe_ct_in, std::shared_ptr<VectorCTAccumulator> acc_msg) = 0;

    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const {
        ar(lwe_par);    
    }
        
    template <class Archive>
    void load( Archive & ar ) {
        ar(lwe_par);    
    } 
    #endif 

};
 
}/// End of namespace FHEDeck

#if defined(USE_CEREAL)
CEREAL_REGISTER_TYPE(FHEDeck::KSFunctionSpecificationBuilder)
CEREAL_REGISTER_TYPE(FHEDeck::PolynomialSpecificationBuilder)
CEREAL_REGISTER_TYPE(FHEDeck::RLWEAccumulatorBuilder)
CEREAL_REGISTER_TYPE(FHEDeck::NTRUAccumulatorBuilder) 
CEREAL_REGISTER_TYPE(FHEDeck::RLWEBlindRotateOutputBuilder)
CEREAL_REGISTER_TYPE(FHEDeck::NTRUBlindRotateOutputBuilder)
#endif 

#endif 