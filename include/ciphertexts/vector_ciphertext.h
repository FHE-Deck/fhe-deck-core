
#ifndef VECTOR_CIPHERTEXT_H
#define VECTOR_CIPHERTEXT_H


/**
 * @file vector_ciphertext.h
 */

#include "global_headers.h"

#include "interface/plaintext_encoding.h" 

namespace FHEDeck{
 
/**
 * @brief Interface for vector ciphertexts. Intended to be used for homomorphic operations on vectors. Example implementations include RLWE and and NTRU.
 */
class VectorCT{

    public:   
  
    /// @brief Destructor
    virtual ~VectorCT() = default;
  
    /// @brief Rotates the plaintext within the ciphertext without affecting its decryptability. ote that this isn't necessarily a cyclic rotation. It's up to the implementation how the rotation is done.
    /// @param out The output ciphertext
    /// @param rot The amount of rotation
    virtual void homomorphic_rotate(VectorCT &out, int32_t rot) = 0;

    /// @brief Adds this ciphertext and ct, and stores the result in out.
    /// @param out The output ciphertext
    /// @param ct The ciphertext to add
    virtual void add(VectorCT &out, const VectorCT &ct) = 0;
    
    /// @brief Subtracts ct from this ciphertext, and stores the result in out.
    /// @param out The output ciphertext
    /// @param ct The input ciphertext
    virtual void sub(VectorCT &out, const VectorCT &ct) = 0;
  
    /// @brief Negates this ciphertext and stores the result in out.
    /// @param out The output ciphertext
    virtual void neg(VectorCT &out) = 0; 

    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const {}
        
    template <class Archive>
    void load( Archive & ar ) {} 
    #endif 
};

/**
 * @brief Interface for vector ciphertext parameters. Example implementations include RLWEParam and NTRUParam.
 */
class VectorCTParam{
    public:

    /// @brief The size of the vector
    int32_t size; 

    /// @brief Initiates a VectorCT object which is not necessarily decryptable. its for allocating space. 
    virtual std::shared_ptr<VectorCT> init_ct(std::shared_ptr<VectorCTParam> param) = 0;

    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const {}
        
    template <class Archive>
    void load( Archive & ar ) { }
    #endif  
};

class VectorCTSK{

    public:

    std::shared_ptr<VectorCTParam> vector_ct_param;

    /// @brief Destructor
    virtual ~VectorCTSK() = default;


    /// @brief The encryption function. Encrypts the message m, and stores the result in out.
    /// @param out The resulting ciphertext. It is assumed the object is properly initialized.
    /// @param m Polynomial message to be encrypted.
    virtual void encrypt(VectorCT &out, const Vector &m) = 0;  
    
    /// @brief The encryption function. Encrypts the message m, and returns the resulting ciphertext.
    /// @param m The polynomial message to be encrypted.
    /// @return Creates and returns the resulting ciphertext.
    virtual std::shared_ptr<VectorCT> encrypt(const Vector &m) = 0; 

    /// @brief Encodes the message m using the encoding scheme, and encrypts it.
    /// @param m The input message.
    /// @param encoding The encoding scheme.
    /// @return Creates and returns the resulting ciphertext.
    virtual std::shared_ptr<VectorCT> encode_and_encrypt(const Vector& m, PlaintextEncoding encoding) = 0;

    /// @brief Encodes the message m using the encoding scheme, and encrypts it.
    /// @param m The input message.
    /// @param encoding The encoding scheme.
    /// @return Creates and returns the resulting ciphertext.
    virtual void encode_and_encrypt(VectorCT& out, const Vector& m, PlaintextEncoding encoding) = 0;

    /// @brief  Decrypts the ciphertext ct, and returns the resulting polynomial.
    /// @param ct The input ciphertext.
    /// @param encoding The encoding scheme.
    /// @return Creates a new polynomial and which is the result of the decryption.
    virtual std::shared_ptr<Vector> decrypt(const VectorCT &ct, PlaintextEncoding encoding) = 0;
  
    /// @brief Decrypts the ciphertext ct, and stores the result in out.
    /// @param out The resulting polynomial.
    /// @param ct The input ciphertext.
    /// @param encoding The plaintext encoding scheme.
    virtual void decrypt(Vector &out, const VectorCT &ct, PlaintextEncoding encoding) = 0;
    
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
class GadgetVectorCT{

    public: 

    /// @brief Destructor
    virtual ~GadgetVectorCT() = default;

    /// @brief Multiplies this with ct, and stores the result in out.
    /// @param out The output ciphertext
    /// @param ct The input ciphertext
    virtual void mul(VectorCT &out, const VectorCT &ct) = 0;

    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const {}
        
    template <class Archive>
    void load( Archive & ar ) {}
    #endif  
};

/**
 * @brief Interface for gadget vector ciphertext secret key. Example implementations include GadgetRLWESK and GadgetNTRUSK.
 */
class GadgetVectorCTSK{

    public: 
 
    /// @brief The parameters of the VactorCT scheme
    std::shared_ptr<VectorCTParam> vector_ct_param;
    /// @brief The secret key of the VactorCT scheme
    std::shared_ptr<VectorCTSK> secret_key;

    /// @brief Destructor
    virtual ~GadgetVectorCTSK() = default;

    /// @brief Encrypts the msg vector and returns the ciphertext
    /// @param msg The message to encrypt
    /// @param size The size of the message
    /// @return Creates a new ciphertext
    virtual std::shared_ptr<GadgetVectorCT> gadget_encrypt(const uint64_t *msg, int32_t size) = 0; 
      
    /// @brief Encrypts the msg vector and returns the ciphertext
    /// @param msg The message to encrypt
    /// @param size The size of the message
    /// @return Creates a new ciphertext
    virtual std::shared_ptr<GadgetVectorCT> gadget_encrypt(const Vector &msg) = 0;  

    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const {}
        
    template <class Archive>
    void load( Archive & ar ) {} 
    #endif 
    
};

} /// End of namespace FHEDeck

#endif