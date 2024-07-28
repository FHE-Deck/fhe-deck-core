
#ifndef VECTOR_CIPHERTEXT_H
#define VECTOR_CIPHERTEXT_H

#include <memory>

namespace fhe_deck{

///class VectorCT;


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
    virtual void homomorphic_rotate(VectorCT *out, int32_t rot) = 0;

    /// @brief Adds this ciphertext and ct, and stores the result in out.
    /// @param out The output ciphertext
    /// @param ct The ciphertext to add
    virtual void add(VectorCT *out,  VectorCT *ct) = 0;
    
    /// @brief Subtracts ct from this ciphertext, and stores the result in out.
    /// @param out The output ciphertext
    /// @param ct The input ciphertext
    virtual void sub(VectorCT *out, VectorCT *ct) = 0;
  
    /// @brief Negates this ciphertext and stores the result in out.
    /// @param out The output ciphertext
    virtual void neg(VectorCT *out) = 0; 

    template <class Archive>
    void save( Archive & ar ) const {}
        
    template <class Archive>
    void load( Archive & ar ) {} 
};

/**
 * @brief Interface for vector ciphertext parameters. Example implementations include RLWEParam and NTRUParam.
 */
class VectorCTParam{
    public:

    /// @brief The size of the vector
    int32_t size; 

    /// @brief Initiates a VectorCT object which is not necessarily decryptable. its for allocating space.
    /// @param param The parameters of the VectorCT object. It may be weird to take the parameter, as we reference the same object in our applicaitons. The reason its written like this is because we need a shared pointer to be passed to the ciphertexts. 
    virtual VectorCT* init_ct(std::shared_ptr<VectorCTParam> param) = 0;

    template <class Archive>
    void save( Archive & ar ) const {}
        
    template <class Archive>
    void load( Archive & ar ) {} 
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
    virtual void mul(VectorCT *out, const VectorCT *ct) = 0;

    template <class Archive>
    void save( Archive & ar ) const {}
        
    template <class Archive>
    void load( Archive & ar ) {} 
};

/**
 * @brief Interface for gadget vector ciphertext secret key. Example implementations include GadgetRLWESK and GadgetNTRUSK.
 */
class GadgetVectorCTSK{

    public: 
 
    /// @brief The parameters of the VactorCT scheme
    std::shared_ptr<VectorCTParam> vector_ct_param;

    /// @brief Destructor
    virtual ~GadgetVectorCTSK() = default;

    /// @brief Encrypts the msg vector and returns the ciphertext
    /// @param msg The message to encrypt
    /// @param size The size of the message
    /// @return Creates a new ciphertext
    virtual GadgetVectorCT* gadget_encrypt(uint64_t *msg, int32_t size) = 0; 
    
    /// @brief Encrypts the msg coeffficient vector and returns the ciphertext
    /// @param msg The message to encrypt
    /// @param size The size of the message
    /// @return Creates a new ciphertext
    virtual GadgetVectorCT* gadget_encrypt(Polynomial *msg) = 0;  

    template <class Archive>
    void save( Archive & ar ) const {}
        
    template <class Archive>
    void load( Archive & ar ) {} 
};

}

#endif