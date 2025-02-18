
#ifndef POLYNOMIAL_CIPHERTEXT_H
#define POLYNOMIAL_CIPHERTEXT_H

#include "global_headers.h"

#include "math/polynomial.h"
#include "ciphertexts/vector_ciphertext.h"
 
/**
 * @file polynomial_ciphertext.h
 */


namespace FHEDeck{
 

/**
 * @brief Interface for vector ciphertext parameters. Example implementations include RLWEParam and NTRUParam.
 */
class PolynomialCTParam : public VectorCTParam {

    public:
  
    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const {
        ar(cereal::base_class<VectorCTParam>(this));  
    }
        
    template <class Archive>
    void load( Archive & ar ) {
        ar(cereal::base_class<VectorCTParam>(this));  
    } 
    #endif
};

 

/**
 * @brief Interface for vector ciphertexts. Intended to be used for homomorphic operations on vectors. Example implementations include RLWE and and NTRU.
 */
class PolynomialCT : public VectorCT{

    public:   
  
    /// @brief Destructor
    virtual ~PolynomialCT() = default;
    
    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const {
        ar(cereal::base_class<VectorCT>(this)); 
    }
        
    template <class Archive>
    void load( Archive & ar ) {
        ar(cereal::base_class<VectorCT>(this)); 
    } 
    #endif 
};


/**
 * @brief Interface for gadget vector ciphertext. This object can be multiplied with a VectorCT and the result is a VectorCT. Example implementations include GadgetRLWECT and GadgetNTRUCT.
 */
class ExtendedPolynomialCT{

    public: 

    /// @brief Destructor
    virtual ~ExtendedPolynomialCT() = default;

    /// @brief Multiplies this with ct, and stores the result in out.
    /// @param out The output ciphertext
    /// @param ct The input ciphertext
    virtual void mul(VectorCT &out, const Polynomial &scalar) = 0;

    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const {}
        
    template <class Archive>
    void load( Archive & ar ) {} 
    #endif
};

/**
 * @brief Interface for gadget vector ciphertext. This object can be multiplied with a VectorCT and the result is a VectorCT. Example implementations include GadgetRLWECT and GadgetNTRUCT.
 */
class GadgetPolynomialCT : public GadgetVectorCT{

    public: 

    /// @brief Destructor
    virtual ~GadgetPolynomialCT() = default;
  
    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const {
        ar(cereal::base_class<GadgetVectorCT>(this));   
    }
        
    template <class Archive>
    void load( Archive & ar ) {
        ar(cereal::base_class<GadgetVectorCT>(this));   
    } 
    #endif
};


/**
 * @brief Interface for gadget vector ciphertext secret key. Example implementations include GadgetRLWESK and GadgetNTRUSK.
 */
class GadgetPolynomialCTSK : public GadgetVectorCTSK{

    public: 

    /// @brief Destructor
    virtual ~GadgetPolynomialCTSK() = default;

    /// @brief Encrypts the message msg, and returns the resulting ciphertext.
    /// @param msg The input message.
    /// @return Creates a new object that stores the resulting ciphertext.
    virtual std::shared_ptr<ExtendedPolynomialCT> extended_encrypt(const Polynomial &msg) = 0; 

    /// @brief Encrypts the message msg, and returns the resulting ciphertext.
    /// @param msg The input message.
    /// @param size the size of the msg array (should be smaller than the ring size)
    /// @return Creates a new object that stores the resulting ciphertext.
    virtual std::shared_ptr<ExtendedPolynomialCT> extended_encrypt(const uint64_t *msg, int32_t size) = 0; 
    
    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const {
        ar(cereal::base_class<GadgetVectorCTSK>(this));     
    }
        
    template <class Archive>
    void load( Archive & ar ) {
        ar(cereal::base_class<GadgetVectorCTSK>(this));     
    } 
    #endif 
};

} /// End of namespace FHEDeck

#endif