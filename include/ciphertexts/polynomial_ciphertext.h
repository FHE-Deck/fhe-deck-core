
#ifndef POLYNOMIAL_CIPHERTEXT_H
#define POLYNOMIAL_CIPHERTEXT_H

#include "polynomial.h"
#include "vector_ciphertext.h"

namespace fhe_deck{
 

/**
 * @brief Interface for vector ciphertext parameters. Example implementations include RLWEParam and NTRUParam.
 */
class PolynomialCTParam : public VectorCTParam {
    public:

    /// @brief The size of the vector
    //int32_t size; 

    /// @brief Initiates a VectorCT object which is not necessarily decryptable. its for allocating space.
    /// @param param The parameters of the VectorCT object. It may be weird to take the parameter, as we reference the same object in our applicaitons. The reason its written like this is because we need a shared pointer to be passed to the ciphertexts. 
    //virtual VectorCT* init_ct(std::shared_ptr<VectorCTParam> param) = 0;

    template <class Archive>
    void save( Archive & ar ) const {
        ar(cereal::base_class<VectorCTParam>(this));  
    }
        
    template <class Archive>
    void load( Archive & ar ) {
        ar(cereal::base_class<VectorCTParam>(this));  
    } 
};




/**
 * @brief Interface for vector ciphertexts. Intended to be used for homomorphic operations on vectors. Example implementations include RLWE and and NTRU.
 */
class PolynomialCT : public VectorCT{

    public:   
  
    /// @brief Destructor
    virtual ~PolynomialCT() = default;
  
    /// @brief Rotates the plaintext within the ciphertext without affecting its decryptability. ote that this isn't necessarily a cyclic rotation. It's up to the implementation how the rotation is done.
    /// @param out The output ciphertext
    /// @param rot The amount of rotation
    //virtual void homomorphic_rotate(VectorCT *out, int32_t rot) = 0;

    /// @brief Adds this ciphertext and ct, and stores the result in out.
    /// @param out The output ciphertext
    /// @param ct The ciphertext to add
    //virtual void add(VectorCT *out,  VectorCT *ct) = 0;
    
    /// @brief Subtracts ct from this ciphertext, and stores the result in out.
    /// @param out The output ciphertext
    /// @param ct The input ciphertext
   //virtual void sub(VectorCT *out, VectorCT *ct) = 0;
  
    /// @brief Negates this ciphertext and stores the result in out.
    /// @param out The output ciphertext
    //virtual void neg(VectorCT *out) = 0; 

    template <class Archive>
    void save( Archive & ar ) const {
        ar(cereal::base_class<VectorCT>(this)); 
    }
        
    template <class Archive>
    void load( Archive & ar ) {
        ar(cereal::base_class<VectorCT>(this)); 
    } 
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
    virtual void mul(VectorCT *out, const VectorCT *ct) = 0;

    template <class Archive>
    void save( Archive & ar ) const {}
        
    template <class Archive>
    void load( Archive & ar ) {} 
};

/**
 * @brief Interface for gadget vector ciphertext. This object can be multiplied with a VectorCT and the result is a VectorCT. Example implementations include GadgetRLWECT and GadgetNTRUCT.
 */
class GadgetPolynomialCT : public GadgetVectorCT{

    public: 

    /// @brief Destructor
    //virtual ~GadgetPolynomialCT() = default;

    /// @brief Multiplies this with ct, and stores the result in out.
    /// @param out The output ciphertext
    /// @param ct The input ciphertext
    //virtual void mul(VectorCT *out, const VectorCT *ct) = 0;

    template <class Archive>
    void save( Archive & ar ) const {
        ar(cereal::base_class<GadgetVectorCT>(this));   
    }
        
    template <class Archive>
    void load( Archive & ar ) {
        ar(cereal::base_class<GadgetVectorCT>(this));   
    } 
};


/**
 * @brief Interface for gadget vector ciphertext secret key. Example implementations include GadgetRLWESK and GadgetNTRUSK.
 */
class GadgetPolynomialCTSK : public GadgetVectorCTSK{

    public: 

    /// @brief The parameters of the VactorCT scheme
    //std::shared_ptr<VectorCTParam> vector_ct_param;

    /// @brief Encrypts the msg vector and returns the ciphertext
    /// @param msg The message to encrypt
    /// @param size The size of the message
    /// @return Creates a new ciphertext
    //virtual GadgetVectorCT* gadget_encrypt(uint64_t *msg, int32_t size) = 0; 
    
    /// @brief Encrypts the msg coeffficient vector and returns the ciphertext
    /// @param msg The message to encrypt
    /// @param size The size of the message
    /// @return Creates a new ciphertext
    //virtual GadgetVectorCT* gadget_encrypt(Polynomial *msg) = 0;  

    template <class Archive>
    void save( Archive & ar ) const {
        ar(cereal::base_class<GadgetVectorCTSK>(this));     
    }
        
    template <class Archive>
    void load( Archive & ar ) {
        ar(cereal::base_class<GadgetVectorCTSK>(this));     
    } 
};

}

#endif