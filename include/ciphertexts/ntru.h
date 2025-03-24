 
#ifndef NTRU_H
#define NTRU_H


/**
 * @file ntru.h
 */

#include "global_headers.h"

#include "common/sample.h"
#include "common/utils.h"  
#include "common/gadget.h" 
#include "ciphertexts/lwe.h"
#include "ciphertexts/polynomial_ciphertext.h"
#include "math/polynomial.h"
#include "math/polynomial_inversion_engine_builder.h"
#include "math/polynomial_multiplication_engine_builder.h"
 
namespace FHEDeck{
 
/**
 * @brief NTRUParam class is used to store the parameters of the NTRU encryption scheme.
 */
class NTRUParam : public PolynomialCTParam{

  public: 
    /// @brief The coefficiant modulus.
    uint64_t coef_modulus; 
    /// @brief The ring type.
    RingType ring;
    /// @brief The modulus type. 
    //ModulusType mod_type;   
    /// @brief The polynomial arithmetic indicates the implementation of the multiplication engine.
    PolynomialArithmetic arithmetic = PolynomialArithmetic::ntt64;
    /// @brief The polynomial multiplication engine.
    std::shared_ptr<PolynomialMultiplicationEngine> mul_engine;
    /// @brief Flag indicating whether the multiplication engine is initialized.
    bool is_mul_engine_init = false;
 
    /// @brief Defaukt constructor.
    NTRUParam() = default; 
    /// @brief Constructs the NTRUParam object.
    /// @param ring The ring type.
    /// @param ring_degree The degree of the ring.
    /// @param coef_modulus The coefficient modulus.
    /// @param arithmetic The polynomial arithmetic.
    NTRUParam(RingType ring, int32_t ring_degree, uint64_t coef_modulus, PolynomialArithmetic arithmetic);
 
    NTRUParam(NTRUParam &c);

    NTRUParam& operator=(NTRUParam other);

    /// @brief Constructs a new VectorCT object implemented as NTRUCT.
    /// @param param The parameters of the NTRU encryption scheme. Usually its the same object. 
    /// @return Retuns a new VectorCT object.
    std::shared_ptr<VectorCT> init_ct(std::shared_ptr<VectorCTParam> param);
         
    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(cereal::base_class<PolynomialCTParam>(this));   
      ar(ring, size, coef_modulus, arithmetic);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
      ar(cereal::base_class<PolynomialCTParam>(this));   
      ar(ring, size, coef_modulus, arithmetic);   
      init_mul_engine(); 
    } 
    #endif
 
  private:
    void init_mul_engine(); 
};
 
class NTRUCT : public PolynomialCT{

    public:
  
    /// @brief The parameters of the NTRU encryption scheme.
    std::shared_ptr<NTRUParam> param;  
    /// @brief The ciphertext polynomial.
    Polynomial ct_poly; 

    /// @brief Default constructor.
    NTRUCT() = default;

    /// @brief Constructs the NTRUCT object.
    /// @param param The parameters of the NTRU encryption scheme.
    NTRUCT(std::shared_ptr<NTRUParam> param);
 
    NTRUCT(const NTRUCT &other);
   
    NTRUCT& operator=(NTRUCT other);
  
    /// @brief Negacyclic rotation of the ciphertext polynomial.
    /// @param out The output ciphertext.
    /// @param rot The rotation amount.
    void negacyclic_rotate(NTRUCT &out, int32_t rot);

    /// @brief Cyclical rotation of the ciphertext polynomial.
    /// @param out The output ciphertext.
    /// @param rot The rotation amount.
    void cyclic_rotate(NTRUCT &out, int32_t rot);

    /// @brief Negacyclic rotation of the ciphertext polynomial.
    /// @param out The output ciphertext.
    /// @param rot The rotation amount.
    void homomorphic_rotate(VectorCT &out, int32_t rot);

    /// @brief Adds this ciphertext to ct and store the result in out.
    /// @param out The output ciphertext.
    /// @param ct The input ciphertext.
    void add(VectorCT &out, const VectorCT &ct);
 
    /// @brief Adds x to this ciphertext, and stores the result in out.
    /// @param out The output ciphertext.
    /// @param x The input polynomial.
    void add(NTRUCT &out, const Polynomial &x);

    /// @brief Subtracts ct from this ciphertext, and stores the result in out.
    /// @param out The output ciphertext.
    /// @param ct The input ciphertext.
    void sub(VectorCT &out, const VectorCT &ct);
 
    /// @brief Subtracts x from this ciphertext, and stores the result in out. 
    /// @param out The output ciphertext.
    /// @param x The input polynomial.
    void sub(NTRUCT &out, const Polynomial &x); 
 
    /// @brief Multiplies this ciphertexts with x, and stores the result in out.
    /// @param out The output ciphertext.
    /// @param x The input polynomial.
    void mul(NTRUCT &out, const Polynomial &x);

    /// @brief Negates this ciphertexts coefficients and stores the result in out.
    /// @param out The output ciphertext.
    void neg(VectorCT &out);
 
    /// @brief Extracts an LWE ciphertext that encodes the constant coefficient. 
    /// @param out The output LWE ciphertext.
    void extract_lwe(LWECT &out);
 
    /// @brief Produces a string representation of this object. 
    /// @return The string representation.
    std::string to_string();
    
  #if defined(USE_CEREAL)
  template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(cereal::base_class<PolynomialCT>(this));   
        ar(param, ct_poly); 
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
        ar(cereal::base_class<PolynomialCT>(this));   
        ar(param, ct_poly); 
    }  
    #endif
};

/**
 * @brief NTRUSK class is used to store the secret key of the NTRU encryption scheme, and implements the encryption and decryption operations.
 */
class NTRUSK : public VectorCTSK{

    public:

    /// @brief  The parameters of the NTRU encryption scheme.
    std::shared_ptr<NTRUParam> param;   
    /// @brief The secret key polynomial.
    Polynomial sk; 
    /// @brief The multiplicative inverse of secret key polynomial.
    Polynomial inv_sk; 
    /// @brief Flag indicating whether the secret key is initialized.
    bool is_init = false;   
    /// @brief The error distribution.
    std::shared_ptr<Distribution> error_dist;
    /// @brief The secret key distribution.
    std::shared_ptr<Distribution> sk_dist;
    /// @brief The noise standard deviation.
    double noise_stddev;
   
    /// @brief Default constructor.
    NTRUSK() = default;
  
    /// @brief Constructs the NTRUSK object.
    /// @param param The NTRU parameters.
    /// @param noise_stddev The noise standard deviation.
    NTRUSK(std::shared_ptr<NTRUParam> param, double noise_stddev); 
  
    /// @brief Generates the secret key. 
    /// NOTE: Depends on NTL need to init a Inversion Engine for that. 
    void key_gen();
  
    NTRUSK(const NTRUSK &other) = delete;

    NTRUSK& operator=(const NTRUSK other) = delete;
  
    /// @brief Encrypts the message polynomial m, and stores the result in out.
    /// @param out The output ciphertext. 
    /// @param m The input polynomial.
    void encrypt(VectorCT &out, const Vector &m)override;
 
    /// @brief Encrypts the message polynomial m, and returns the result.
    /// @param m The input polynomial.
    /// @return Creates and returns a new ciphertext.
    std::shared_ptr<VectorCT> encrypt(const Vector &m)override; 

    /// @brief Encodes and the message polynomial m, and returns the result.
    /// @param m The input polynomial.
    /// @param encoding The encoding scheme.
    /// @return Creates and returns a new ciphertext.
    std::shared_ptr<VectorCT> encode_and_encrypt(const Vector &m, PlaintextEncoding encoding)override;

    /// @brief Encodes and the message polynomial m, and returns the result.
    /// @param m The input polynomial.
    /// @param encoding The encoding scheme.
    /// @return Creates and returns a new ciphertext.
    void encode_and_encrypt(VectorCT& out, const Vector &m, PlaintextEncoding encoding)override;
 
    /// @brief Partially decrypts the ciphertext. Multiplies the ct polynomial with sk. 
    /// @param phase The output polynomial.
    /// @param ct The input ciphertext.
    void partial_decrypt(Polynomial &phase, const NTRUCT &ct);
 
    /// @brief Decrypts the input ciphertext, and returns a new polynomial.
    /// @param ct The input ciphertext.
    /// @param encoding The encoding scheme.
    /// @return Creates and returns a new polynomial.
    std::shared_ptr<Vector> decrypt(const VectorCT &ct, PlaintextEncoding encoding)override;
 
    /// @brief Decrypts ct, and stores the result in out.
    /// @param out The  output polynomial.
    /// @param ct the input ciphertext.
    /// @param encoding The encoding scheme.
    void decrypt(Vector &out, const VectorCT &ct, PlaintextEncoding encoding)override;
   
    /// @brief Encrypts msg * inv_sk. 
    /// @param msg The input polynomial.
    /// @return Creates and returns a new ciphertext.
    std::shared_ptr<NTRUCT> kdm_encrypt(const Polynomial &msg); 
 
    /// @brief Encrypts msg * inv_sk, and stores the result in ct_out
    /// @param ct_out The output ciphertext.
    /// @param msg The input polynomial.
    void kdm_encrypt(NTRUCT &ct_out, const Polynomial &msg);
    
    /// @brief Encodes msg,  encrypts encoding.encode(msg) * inv_sk, and stores the result in ct_out
    /// @param ct_out The output ciphertext.
    /// @param msg The input polynomial.
    /// @param encoding The input encoding.
    void kdm_encode_and_encrypt(NTRUCT &ct_out, const Polynomial &msg, PlaintextEncoding encoding);
    
    /// @brief Encodes msg,  encrypts encoding.encode(msg) * inv_sk.
    /// @param msg The input polynomial.
    /// @param encoding The input encoding.
    /// @return Creates and returns a new ciphertext.
    std::shared_ptr<NTRUCT> kdm_encode_and_encrypt(const Polynomial &msg, PlaintextEncoding encoding);
  
    /// @brief Extracts the LWE key.
    /// @return Creates and returns a new LWE key, with a newly created LWEParam object.
    std::shared_ptr<LWESK> extract_lwe_key();
   
   #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(cereal::base_class<VectorCTSK>(this));   
        ar(param, sk, inv_sk, noise_stddev);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {    
      ar(cereal::base_class<VectorCTSK>(this));   
      ar(param, sk, inv_sk, noise_stddev);   
      init();
    }  
    #endif

    private:
      void init();
};

  
/**
 * @brief NTRUGadgetCT class implements the extended NTRU ciphertext of the form NTRU(base^i m), that can be multiplied with NTRUCT.

 */
class NTRUGadgetCT : public GadgetPolynomialCT, public ExtendedPolynomialCT{ 

  public:
  
  /// @brief The parameters of the NTRU encryption scheme.
  std::shared_ptr<NTRUParam> ntru_param;
  /// @brief The decomposition gadget. 
  std::shared_ptr<Gadget> gadget;
  /// @brief Flag indicating whether the gadget is initialized.
  bool is_init = false;  
  /// @brief The array evaluation form holding the decomposition of the ciphertext.
  std::shared_ptr<PolynomialArrayEvalForm> array_eval_a;  
 
  /// @brief Free deter_ct_a_dec memory.
  ~NTRUGadgetCT();

  /// @brief Default constructor.
  NTRUGadgetCT() = default;
   
  /// @brief Constructs the NTRUGadgetCT object.
  /// @param ntru_param The parameters of the NTRU encryption scheme.
  /// @param gadget The decomposition gadget.
  /// @param gadget_ct The array of NTRUCT objects.
  NTRUGadgetCT(std::shared_ptr<NTRUParam> ntru_param, std::shared_ptr<Gadget> gadget, std::vector<std::shared_ptr<NTRUCT>> &gadget_ct);

  NTRUGadgetCT(const NTRUGadgetCT& other);

  NTRUGadgetCT& operator=(const NTRUGadgetCT other);

  /// @brief Initializes deter_ct_a_dec, deter_ct_a_dec_poly and array_eval_a
  /// @param gadget_ct 
  void init(std::vector<std::shared_ptr<NTRUCT>>& gadget_ct);
   
  /// @brief Multiplies this with the input ct, and stores the result in out.
  /// @param out The output ciphertext.
  /// @param ct The input ciphertext.
  void mul(VectorCT &out, const VectorCT &ct);

  void mul(VectorCT &out, const Polynomial &scalar);

  #if defined(USE_CEREAL)
  template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(cereal::base_class<GadgetPolynomialCT>(this));   
        ar(ntru_param, gadget, array_eval_a);     
    }
        
    template <class Archive>
    void load( Archive & ar )
    {    
        ar(cereal::base_class<GadgetPolynomialCT>(this));   
        ar(ntru_param, gadget, array_eval_a);     
        this->is_init = true;  
    } 
    #endif
       
};
   
/**
 * @brief NTRUGadgetSK class implements encryption methods to produce NTRUGadgetCT
 */
class NTRUGadgetSK : public GadgetPolynomialCTSK{

    public:
    /// @brief The decomposition gadget.
    std::shared_ptr<Gadget> gadget;
    /// @brief The secret key of the NTRU encryption scheme.
    std::shared_ptr<NTRUSK> sk;

    /// @brief Default constructor.
    NTRUGadgetSK() = default;

    /// @brief Constructs the NTRUGadgetSK object.
    /// @param gadget The decomposition gadget.
    /// @param sk The secret key of the NTRU encryption scheme.
    NTRUGadgetSK(std::shared_ptr<Gadget> gadget, std::shared_ptr<NTRUSK> sk);

    NTRUGadgetSK(const NTRUGadgetSK &other) = delete;

    NTRUGadgetSK& operator=(const NTRUGadgetSK other) = delete;

    /// @brief Encrypts the input polynomial msg, and returns the result.
    /// @param msg The input polynomial.
    /// @return Creates and returns a new ciphertext.        
    std::shared_ptr<GadgetVectorCT> gadget_encrypt(const Vector &msg); 

    /// @brief Encrypts the input message array msg, and returns the result.
    /// @param msg The input message array.
    /// @param size The size of the input message array.
    /// @return Creates and returns a new ciphertext.
    std::shared_ptr<GadgetVectorCT> gadget_encrypt(const uint64_t *msg, int32_t size); 

    /// @brief Encrypts msg * inv_sk, and stores the result in ct_out.
    /// @param msg The input polynomial.
    /// @return Creates and returns a new ciphertext.
    std::shared_ptr<GadgetVectorCT> kdm_gadget_encrypt(const Polynomial &msg); 

    /// @brief Encrypts msg * inv_sk, and stores the result in ct_out.
    /// @param msg The input polynomial.
    /// @param size The size of the input message array.
    /// @return Creates and returns a new ciphertext.
    std::shared_ptr<GadgetVectorCT> kdm_gadget_encrypt(const uint64_t *msg, int32_t size); 

    /// @brief Encrypts the message msg, and returns the resulting ciphertext.
    /// @param msg The input message.
    /// @return Creates a new object that stores the resulting ciphertext.
    std::shared_ptr<ExtendedPolynomialCT> extended_encrypt(const Polynomial &msg); 

    /// @brief Encrypts the message msg, and returns the resulting ciphertext.
    /// @param msg The input message.
    /// @param size the size of the msg array (should be smaller than the ring size)
    /// @return Creates a new object that stores the resulting ciphertext.
    std::shared_ptr<ExtendedPolynomialCT> extended_encrypt(const uint64_t *msg, int32_t size); 
   
    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    { 
        ar(cereal::base_class<GadgetPolynomialCTSK>(this));     
        ar(gadget, sk);   
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
        ar(cereal::base_class<GadgetPolynomialCTSK>(this));     
        ar(gadget, sk);   
        secret_key = sk;
    } 
    #endif

    private:
 
    std::vector<std::shared_ptr<NTRUCT>> ext_enc(const Polynomial &msg);
};
 
} /// End of namespace FHEDeck

#if defined(USE_CEREAL)
CEREAL_REGISTER_TYPE(FHEDeck::NTRUParam)
CEREAL_REGISTER_TYPE(FHEDeck::NTRUCT)
CEREAL_REGISTER_TYPE(FHEDeck::NTRUSK)
CEREAL_REGISTER_TYPE(FHEDeck::NTRUGadgetCT)
CEREAL_REGISTER_TYPE(FHEDeck::NTRUGadgetSK)
#endif 


#endif