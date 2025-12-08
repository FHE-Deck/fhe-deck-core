 
#ifndef LWE_H
#define LWE_H

/**
 * @file lwe.h
 */
 
#include "global_headers.h"
  
#include "common/sample.h"
#include "interface/plaintext_encoding.h" 
   
namespace FHEDeck{
  
/** 
 * @brief LWE Parameters.  
 */  
class LWEParam{

  protected:

  /// @brief LWE Dimension
  int32_t m_dim;
  /// @brief LWE Dimension
  int64_t m_modulus; 

  public:  
 
  /// NOTE: Never explicitely used in FHE-Deck, but its required by cereal.
  LWEParam() = default;
 
  /// @brief Constructs the LWE Parameters. 
  /// @param dim Dimension of the LWE instance
  /// @param modulus Modulus of the LWE instance
  LWEParam(int32_t dim, int64_t modulus); 

  int32_t dim()const;

  int64_t modulus()const;

  #if defined(USE_CEREAL)
   template<class Archive> 
   void serialize(Archive & ar) 
   { 
     ar(m_dim, m_modulus); 
   }   
   #endif

};

/** 
 * @brief LWE Ciphertext. Stores the ciphertext vector, and implements all public operations on the ciphertext. 
 */
class LWECT{
 
  protected:
 
    /// @brief Pointer to the LWE parameters.
    std::shared_ptr<LWEParam> m_param;
    /// @brief Array that stores the ciphertext. If s is a secret key, then ct[0] = - sum_{i=1}^{dim} s[i]*ct[i] + e + M.  
    Vector m_ct; 

  public:


    /// NOTE: Never explicitely used in FHE-Deck, but its required by cereal.
    LWECT() = default; 

    /// @brief Initializes the ciphertext and allocates memory for the ciphertext vector.
    /// @param lwe_par Pointer to the LWE parameters.
    LWECT(std::shared_ptr<LWEParam> lwe_par);

    /// @brief Copy Constructor
    /// @param c Reference to a LWECT object, that will be copied.
    LWECT(const LWECT &c);

    /// @brief = Operator
    /// @param other Object that will be copied. 
    /// @return Reference to the copied object.
    LWECT& operator=(const LWECT other); 

    int64_t& operator[](int32_t index);

    int64_t operator[](int32_t index)const;

    std::shared_ptr<LWEParam> param()const;

    Vector& ct_vec();

    const Vector& ct_vec()const;

    /// @brief Clones the ciphertext.
    /// @return Returns a pointer to the cloned ciphertext.
    std::unique_ptr<LWECT> clone()const;

    /// @brief Multiplies this ciphertext by a scalar, and stores the result in out.
    /// @param out The output ciphertext.
    /// @param scalar The input scalar.
    void mul(LWECT &out, int64_t scalar)const;

    /// @brief The same as mul, but the multiplication is done wihtout modulus reduction.
    void mul_lazy(LWECT &out, int64_t scalar)const; 

    /// @brief Add in to this ciphertext, and store the result in out.
    /// @param out The output ciphertext.
    /// @param in The input ciphertext.
    void add(LWECT &out, const LWECT &in)const; 

    /// @brief Subtract in from this ciphertext, and store the result in out.
    /// @param out The output ciphertext.
    /// @param in The input ciphertext.
    void sub(LWECT &out, const LWECT &in)const; 

    /// @brief Same void add(LWECT *out, LWECT *in) as add but without modulus reduction.
    void add_lazy(LWECT &out, const LWECT &in)const;  

    /// @brief Add the scalar b to this ciphertext, and store the result in out.
    /// @param out The output ciphertext.
    /// @param b The input scalar.
    void add(LWECT &out, int64_t b)const; 

    /// @brief Subtract b from this ciphertext, and store the result in out.
    /// @param out The output ciphertext.
    /// @param b The input scalar.
    void sub(LWECT& out, int64_t b)const;

    /// @brief Negate this ciphertext, and store the result in out.
    /// @param out The output ciphertext.
    void neg(LWECT& out)const;
  

    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(m_param, m_ct);    
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(m_param, m_ct);  
    } 
    #endif
};
 
 /**
  * @brief A modulus switcching Class. We initialize an object by giving it two pointers to LWEParam objects that have the same dimension but different modulus. 
  * Then we can switch the modulus of a LWECT ciphertext from the first to the second modulus.
  */
class LWEModSwitcher{

  protected: 
    /// @brief Pointer to the LWE parameters of the ciphertext before the modulus switch.
  std::shared_ptr<LWEParam> m_from;
  /// @brief Pointer to the LWE parameters of the ciphertext after the modulus switch.
  std::shared_ptr<LWEParam> m_to;
  /// @brief Flag that indicates if we need to use long arithmetic. Depending on the modulus we rescale the ciphertext over double or long double floating point numbers.
  bool m_is_long_arithmetic = false;

  public:


  /// @brief The size of the ciphertext.
  int32_t ct_size;
  /// @brief Modulus of the ciphertext before the modulus switch, already cast from uint64_t to double.
  double Q_from;
  /// @brief Modulus of the ciphertext after the modulus switch, already cast from uint64_t to double.
  double Q_to; 
  /// @brief Modulus of the ciphertext before the modulus switch, already cast from uint64_t to long double.
  long double long_Q_from;
  /// @brief Modulus of the ciphertext after the modulus switch, already cast from uint64_t to long double.
  long double long_Q_to;

  LWEModSwitcher() = default;
  
  /// @brief Initializes the LWE Mod Switcher with the two LWE Parameters.
  /// @param from LWE Parameters of the ciphertext before the modulus switch.
  /// @param to LWE Parameters of the ciphertext after the modulus switch.
  LWEModSwitcher(std::shared_ptr<LWEParam> from, std::shared_ptr<LWEParam> to);
  
  /// @brief Switch modulus of in_ct, and store the result in out_ct.
  /// @param out_ct The output ciphertext.
  /// @param in_ct The input ciphertext.
  /// @note The function changes only the ct field of out_ct. In particular, it doesn't sent the parameters field, so you must make sure out_ct has the right parameters and is already initialized.
  void switch_modulus(LWECT &out_ct, const LWECT& in_ct);

  LWECT switch_modulus(const LWECT& in_ct);

  std::shared_ptr<LWEParam> from_param()const;

  std::shared_ptr<LWEParam> to_param()const;
};
 
/**
 * @brief A class that stors the LWE secret key and operations on the secret key like encryption or decryption. 
*/
class LWESK {

  /// The freindships are necessary because we are encrypting the LWESK itself in the key switching generation procedures.
  friend class LWEToLWEKeySwitchKey;
  friend class LWEToRLWEKeySwitchKey;
  friend class CGGIBlindRotationKey;

  protected:
    /// @brief Pointer to the LWE parameters.
    std::shared_ptr<LWEParam> m_param; 
    /// @brief Pointer to the uniform distribution.
    std::shared_ptr<Distribution> m_unif_dist; 
    /// @brief Pointer to the error distribution.
    std::shared_ptr<Distribution> m_error_dist;
    /// @brief Type of the key distribution.
    KeyDistribution m_key_type;
    /// @brief Standard deviation of the error distribution.
    double m_stddev;
    /// @brief The secret key. Initialized in the constructors and freed in the destructor. 
    Vector m_key;   
    /// @brief Needed if in the multiplicaiton of integers in the secret key and the LWE ciphertext exceed 64-bits.
    std::unique_ptr<LongIntegerMultipler> m_multiplier; 
 
    public:  


    /// NOTE: Never explicitely used in FHE-Deck, but its required by cereal.
    LWESK() = default;

    /// @brief Constructrs the LWE secret key.
    /// @param lwe_par LWE parameters.
    /// @param stddev Standard deviation of the error distribution.
    /// @param key_type Key distribution according to which we choose the key. 
    LWESK(std::shared_ptr<LWEParam> lwe_par, double stddev, KeyDistribution key_type);

    /// @brief Constructs the LWESK object, but takes the secret key as an input. 
    /// @param lwe_par LWE parameters.
    /// @param key Pointer to the secret key. This object will create a copy of the key.
    /// @param stddev Stadard deviation of the error distribution.
    /// @param key_type Key distribution according to which the key was choosen. 
    LWESK(std::shared_ptr<LWEParam> lwe_par, int64_t* key, double stddev, KeyDistribution key_type);
 
    /// @brief Deleted so that you are not tempted to copy the secret key around. 
    LWESK(const LWESK &other) = delete;

    /// @brief Deleted so that you are not tempted to copy the secret key around. 
    LWESK& operator=(const LWESK other)  = delete;
 
    /// @brief Encryption a message m, and returns a pointer to a new LWECT object.
    /// @param m The input message. Should be an integer in the ciphertext modulus range.
    /// @return Pointer to the new ciphertext. 
    std::unique_ptr<LWECT> encrypt(int64_t m);

    /// @brief Encryption a message m, and stores the result in out
    /// @param out pointer to the output ciphertext. It is assumed it is already initialized with the right parameters.  
    /// @param m The input message. Should be an integer in the ciphertext modulus range.
    void encrypt(LWECT& out, int64_t m); 
    
    /// @brief Encodes and encrypts a message m, and returns a pointer to a new LWECT object.
    /// @param m The input message.
    /// @param encoding The plaintext encoding specification. It is used to encode the message m, before encrypting it. 
    /// @return Returns a pointer to the new ciphertext, that encrypts encoding.encode(m).
    std::unique_ptr<LWECT> encode_and_encrypt(int64_t m, PlaintextEncoding encoding); 
    
    /// @brief Encodes and encrypts a message m, and stores the result in out.
    /// @param m The input message.
    /// @param encoding The plaintext encoding specification. It is used to encode the message m, before encrypting it. 
    /// @param out Stores the resulting ciphertext, that encrypts encoding.encode(m). It is assumed out is already initialized. 
    void encode_and_encrypt(LWECT& out, int64_t m, PlaintextEncoding encoding);
  
    /// @brief Partially decrypts a ciphertext. That is, this function computes the inner product of the secret key and the ciphertext, and returns the result.
    /// @param out The in ciphertext. 
    /// @return Returns result of the inner produict. 
    int64_t partial_decrypt(const LWECT& in); 

    /// @brief Decrypts the input ciphertext. 
    /// @param in The input ciphertext.
    /// @param encoding The plaintext encoding specification, that is used to decode the message after decryption.
    /// @return Returns the decrypted message.
    int64_t decrypt(LWECT& in, PlaintextEncoding encoding); 

    std::shared_ptr<LWEParam> param()const;
 
    KeyDistribution key_type()const; 

    double stddev()const;
   
    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(m_param);  
      std::vector<int64_t> s_arr; 
      for(int32_t i = 0; i < m_param->dim(); ++i){
        s_arr.push_back(m_key[i]);
      }
      ar(s_arr, m_stddev, m_key_type);
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(m_param);
      std::vector<int64_t> s_arr;
      ar(s_arr, m_stddev, m_key_type);
      init(); 
      for(int32_t i = 0; i < m_param->dim(); ++i){
        m_key[i] = s_arr[i];
      }   
    } 
    #endif

    private:

    /// @brief Initializes the distributions and allocates memory for the secret key.
    void init();
    /// @brief Generates the secret key according to the key distribution.
    void init_key();

};
    
/**
 * @brief A class that stores a vector of LWECT ciphertexts encrypting message * base^{i} for i = 0, 1, ..., digits-1. Its used to multiply with large scalars. 
 */
class LWEGadgetCT{

  friend class LWEGadgetSK;

  protected:

  /// TODO: Perhpas this shuld be done with the gadget class consistently with the Ring Ciphertexts?
  /// @brief Decomposition base
  int64_t m_base;
  /// @brief Number of digits in the decomposition.
  int32_t m_digits;
  /// @brief Number of bits in the base.
  int32_t m_bits_base;  
  /// @brief Pointer to the LWE parameters.
  std::shared_ptr<LWEParam> m_lwe_param;
  /// @brief Array of pointers to the ciphertexts. 
  std::unique_ptr<std::unique_ptr<LWECT>[]> m_ct_content;

  public: 
   
  LWEGadgetCT() = default;

  /// @brief Constructs the object.
  /// @param lwe_par Pointer to the LWE parameters.
  /// @param base The decomposition base.  
  LWEGadgetCT(std::shared_ptr<LWEParam> lwe_par, int64_t base);
  
  /// @brief Multiplication of this object by a scalar.
  /// @param out_ct The LWECT that stores the result.
  /// @param scalar The input scalar.
  void gadget_mul(LWECT& out_ct, int64_t scalar); 

  /// @brief Multiplication of this object by a scalar without modulus reduction.
  /// @param out_ct The LWECT that stores the result.
  /// @param scalar The input scalar.
  void gadget_mul_lazy(LWECT& out_ct, int64_t scalar); 

  
  int64_t base()const;
    
  int32_t digits()const; 

  #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(m_base, m_digits, m_bits_base, m_lwe_param);    
      for(int32_t i = 0; i < m_digits; ++i){
        ar(m_ct_content[i]);
      } 
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(m_base, m_digits, m_bits_base, m_lwe_param); 
      m_ct_content = std::unique_ptr<std::unique_ptr<LWECT>[]>(new std::unique_ptr<LWECT>[m_digits]); 
      for(int32_t i = 0; i < m_digits; ++i){
        ar(m_ct_content[i]);
      } 
    }  
    #endif
};

/**
 * @brief A class that knowns how to produce LWEGadgetCT's. 
 */
class LWEGadgetSK{

  friend class BasicBootstrapBuilder;

  protected:

    /// @brief Pointer to the LWE secret key.
    std::shared_ptr<LWESK> m_lwe_sk;

    std::unique_ptr<LongIntegerMultipler> m_multiplier; 

    /// TODO: Perhpas this shuld be done with the gadget class consistently with the Ring Ciphertexts?
    /// @brief Decomposition base.
    int64_t m_base;
    /// @brief Number of digits in the decomposition.
    int32_t m_digits;
    /// @brief Number of bits in the base.
    int32_t m_bits_base;  

  public: 
 
    LWEGadgetSK() = default;
  
    /// @brief Constructs the object.
    /// @param lwe Pointer to the LWE secret key.
    /// @param base The decomposition base.
    LWEGadgetSK(std::shared_ptr<LWESK> lwe, int64_t base);
  
    /// @brief Copy constructor, throws an exception by default. 
    LWEGadgetSK(const LWEGadgetSK& other);

    /// @brief = Operator, throws an exception by default.
    LWEGadgetSK& operator=(const LWEGadgetSK other); 

    /// @brief Encrypts a message m, and returns a pointer to a new LWEGadgetCT object.
    /// @param m The message m
    /// @return A newly constructed LWEGadgetCT object that encrypts m.
    std::shared_ptr<LWEGadgetCT> gadget_encrypt(int64_t m); 

    /// @brief Encrypts a message m, and and stores the result in the out.
    /// @param out The output ciphertext
    /// @param m The message m
    void gadget_encrypt(LWEGadgetCT& out, int64_t m);

    std::shared_ptr<LWEParam> param()const;

    int64_t base()const;
    
    int32_t digits()const; 
  
    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(m_lwe_sk, m_base, m_digits, m_bits_base);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(m_lwe_sk, m_base, m_digits, m_bits_base);  
      m_multiplier = std::make_unique<LongIntegerMultipler>(m_lwe_sk->param()->modulus());
    }    
    #endif
};

/**
 * @brief A class that handles LWE public key functionality. 
 * Currently, its a vector of ciphertexts of zero.
 * To encrypt, we compute a inner product of the ciphertext vector with a freshly sampled vector of small integers and add the message to the resulting LWE ciphertext.
 */
class LWEPublicKey{

  protected:

    double m_stddev; 
    int32_t m_size;  
    std::shared_ptr<Distribution> m_rand_masking;
   
    std::unique_ptr<std::unique_ptr<LWECT>[]> m_public_key_ptr;
    /// @brief Pointer to the LWE parameters.
    std::shared_ptr<LWEParam> m_param;

  public:
  
 
    LWEPublicKey() = default;

    /// @brief Constructs the object.
    /// @param lwe_sk Pointer to the LWE secret key.
    /// @param key_size The size of the public key. Concretely, it gives the number of ciphertexts in the public key.
    /// @param stddev The standard deviation of the error distribution. 
    LWEPublicKey(std::shared_ptr<LWESK> lwe_sk, int32_t key_size, double stddev);

    LWEPublicKey(const LWEPublicKey &other);
   
    LWEPublicKey& operator=(const LWEPublicKey other);
  
    /// @brief Encrypts the message, and stores the result in out.
    /// @param out The output ciphertexts.
    /// @param message The input message.
    void encrypt(LWECT& out, int64_t message);
  
    /// @brief Encrypts the message and output a pointer to a newly created ciphertexts.
    /// @param message The input message.
    /// @return The output ciphertexts. 
    std::unique_ptr<LWECT> encrypt(int64_t message);

    /// @brief  Encrypts zero, and returns a pointer to the ciphertext.
    /// @return The pointer to a fresh enncryption of zero.
    std::unique_ptr<LWECT> ciphertext_of_zero();

    std::shared_ptr<LWEParam> param()const;

    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(m_param, m_stddev, m_size);     
      for(int32_t i = 0; i < m_size; ++i){   
          ar(m_public_key_ptr[i]);  
      }   
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(m_param, m_stddev, m_size); 
      m_rand_masking = std::shared_ptr<Distribution>(new StandardRoundedGaussianDistribution(0, m_stddev));
      m_public_key_ptr = std::unique_ptr<std::unique_ptr<LWECT>[]>(new std::unique_ptr<LWECT>[m_size]); 
      for(int32_t i = 0; i < m_size; ++i){   
          ar(m_public_key_ptr[i]);  
      }   
    }    
    #endif
    
};
 

}/// End of namespace FHEDeck

#endif