 
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
 
    protected: 

      /// @brief The coefficiant modulus.
    uint64_t m_coef_modulus; 
    /// @brief The ring type.
    RingType m_ring; 
    /// @brief The polynomial arithmetic indicates the implementation of the multiplication engine.
    PolynomialArithmetic m_arithmetic = PolynomialArithmetic::ntt64;
    /// @brief The polynomial multiplication engine.
    std::shared_ptr<PolynomialMultiplicationEngine> m_mul_engine;
    /// @brief Flag indicating whether the multiplication engine is initialized.
    //bool m_is_mul_engine_init = false;

  public: 

 
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
         
    uint64_t modulus()const;
    
    std::shared_ptr<PolynomialMultiplicationEngine> mul_engine()const; 

    RingType ring()const;

    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(cereal::base_class<PolynomialCTParam>(this));   
      ar(m_ring, m_size, m_coef_modulus, m_arithmetic);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
      ar(cereal::base_class<PolynomialCTParam>(this));   
      ar(m_ring, m_size, m_coef_modulus, m_arithmetic);   
      init_mul_engine(); 
    } 
    #endif
 
  private:
    void init_mul_engine(); 
};
 
class NTRUCT : public PolynomialCT{

    protected: 

      /// @brief The parameters of the NTRU encryption scheme.
    std::shared_ptr<NTRUParam> m_param;  
    /// @brief The ciphertext polynomial.
    Polynomial m_ct_poly; 

    public:
   
    /// @brief Default constructor.
    NTRUCT() = default;

    /// @brief Constructs the NTRUCT object.
    /// @param param The parameters of the NTRU encryption scheme.
    NTRUCT(std::shared_ptr<NTRUParam> param);
 
    NTRUCT(std::shared_ptr<NTRUParam> param, const Polynomial& ct_poly);

    NTRUCT(std::shared_ptr<NTRUParam> param, Polynomial&& ct_poly);
 
    NTRUCT(const NTRUCT &other);
   
    NTRUCT& operator=(NTRUCT other);
  
    /// @brief Negacyclic rotation of the ciphertext polynomial.
    /// @param out The output ciphertext.
    /// @param rot The rotation amount.
    void negacyclic_rotate(NTRUCT &out, int32_t rot)const;

    /// @brief Cyclical rotation of the ciphertext polynomial.
    /// @param out The output ciphertext.
    /// @param rot The rotation amount.
    void cyclic_rotate(NTRUCT &out, int32_t rot)const;

    /// @brief Negacyclic rotation of the ciphertext polynomial.
    /// @param out The output ciphertext.
    /// @param rot The rotation amount.
    void homomorphic_rotate(VectorCT &out, int32_t rot)const override;

    /// @brief Adds this ciphertext to ct and store the result in out.
    /// @param out The output ciphertext.
    /// @param ct The input ciphertext.
    void add(VectorCT &out, const VectorCT &ct)const override;
 
    /// @brief Adds x to this ciphertext, and stores the result in out.
    /// @param out The output ciphertext.
    /// @param x The input polynomial.
    void add(NTRUCT &out, const Polynomial &x)const;

    /// @brief Subtracts ct from this ciphertext, and stores the result in out.
    /// @param out The output ciphertext.
    /// @param ct The input ciphertext.
    void sub(VectorCT &out, const VectorCT &ct)const override;
 
    /// @brief Subtracts x from this ciphertext, and stores the result in out. 
    /// @param out The output ciphertext.
    /// @param x The input polynomial.
    void sub(NTRUCT &out, const Polynomial &x)const; 
 
    /// @brief Multiplies this ciphertexts with x, and stores the result in out.
    /// @param out The output ciphertext.
    /// @param x The input polynomial.
    void mul(NTRUCT &out, const Polynomial &x)const;

    /// @brief Negates this ciphertexts coefficients and stores the result in out.
    /// @param out The output ciphertext.
    void neg(VectorCT &out)const override;
 
    /// @brief Extracts an LWE ciphertext that encodes the constant coefficient. 
    /// @param out The output LWE ciphertext.
    void extract_lwe(LWECT &out)const;
 
    /// @brief Produces a string representation of this object. 
    /// @return The string representation.
    std::string to_string()const;

    const Polynomial& ct_poly()const;
    
  #if defined(USE_CEREAL)
  template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(cereal::base_class<PolynomialCT>(this));   
        ar(m_param, m_ct_poly); 
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
        ar(cereal::base_class<PolynomialCT>(this));   
        ar(m_param, m_ct_poly); 
    }  
    #endif
};

/**
 * @brief NTRUSK class is used to store the secret key of the NTRU encryption scheme, and implements the encryption and decryption operations.
 */
class NTRUSK : public VectorCTSK{

    protected:

    /// @brief  The parameters of the NTRU encryption scheme.
    std::shared_ptr<NTRUParam> m_param;   
    /// @brief The secret key polynomial.
    Polynomial m_sk; 
    /// @brief The multiplicative inverse of secret key polynomial.
    Polynomial m_inv_sk; 
    /// @brief Flag indicating whether the secret key is initialized.
    //bool m_is_init = false;   
    /// @brief The error distribution.
    std::shared_ptr<Distribution> m_error_dist;
    /// @brief The secret key distribution.
    std::shared_ptr<Distribution> m_sk_dist;
    /// @brief The noise standard deviation.
    double m_noise_stddev;
 
    public:
 
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
    void encrypt(VectorCT &out, const Vector &m) override;
 
    /// @brief Encrypts the message polynomial m, and returns the result.
    /// @param m The input polynomial.
    /// @return Creates and returns a new ciphertext.
    std::shared_ptr<VectorCT> encrypt(const Vector &m) override; 

    /// @brief Encodes and the message polynomial m, and returns the result.
    /// @param m The input polynomial.
    /// @param encoding The encoding scheme.
    /// @return Creates and returns a new ciphertext.
    std::shared_ptr<VectorCT> encode_and_encrypt(const Vector &m, PlaintextEncoding encoding) override;

    /// @brief Encodes and the message polynomial m, and returns the result.
    /// @param m The input polynomial.
    /// @param encoding The encoding scheme.
    /// @return Creates and returns a new ciphertext.
    void encode_and_encrypt(VectorCT& out, const Vector &m, PlaintextEncoding encoding) override;
 
    /// @brief Partially decrypts the ciphertext. Multiplies the ct polynomial with sk. 
    /// @param phase The output polynomial.
    /// @param ct The input ciphertext.
    void partial_decrypt(Polynomial &phase, const NTRUCT &ct);
 
    /// @brief Decrypts the input ciphertext, and returns a new polynomial.
    /// @param ct The input ciphertext.
    /// @param encoding The encoding scheme.
    /// @return Creates and returns a new polynomial.
    std::shared_ptr<Vector> decrypt(const VectorCT &ct, PlaintextEncoding encoding) override;
 
    /// @brief Decrypts ct, and stores the result in out.
    /// @param out The  output polynomial.
    /// @param ct the input ciphertext.
    /// @param encoding The encoding scheme.
    void decrypt(Vector &out, const VectorCT &ct, PlaintextEncoding encoding) override;
   
    /// @brief Encrypts msg * inv_sk. 
    /// @param msg The input polynomial.
    /// @return Creates and returns a new ciphertext.
    std::shared_ptr<NTRUCT> kdm_encrypt(const Polynomial &msg); 
 
    /// @brief Encrypts msg * inv_sk, and stores the result in ct_out
    /// @param ct_out The output ciphertext.
    /// @param msg The input polynomial.
    void kdm_encrypt(NTRUCT &ct_out, const Polynomial &msg) ;
    
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

    std::shared_ptr<NTRUParam> param()const;
   
   #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(cereal::base_class<VectorCTSK>(this));   
        ar(m_param, m_sk, m_inv_sk, m_noise_stddev);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {    
      ar(cereal::base_class<VectorCTSK>(this));   
      ar(m_param, m_sk, m_inv_sk, m_noise_stddev);   
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

  protected: 

    /// @brief The parameters of the NTRU encryption scheme.
  std::shared_ptr<NTRUParam> m_ntru_param;
  /// @brief The decomposition gadget. 
  std::shared_ptr<Gadget> m_gadget; 
  /// @brief The array evaluation form holding the decomposition of the ciphertext.
  std::shared_ptr<PolynomialArrayEvalForm> m_array_eval_a;  

  public:
   
  /// @brief Default constructor.
  NTRUGadgetCT() = default;
   
  /// @brief Constructs the NTRUGadgetCT object.
  /// @param ntru_param The parameters of the NTRU encryption scheme.
  /// @param gadget The decomposition gadget.
  /// @param gadget_ct The array of NTRUCT objects.
  NTRUGadgetCT(std::shared_ptr<NTRUParam> ntru_param, std::shared_ptr<Gadget> gadget, std::vector<std::shared_ptr<NTRUCT>> &gadget_ct);

  NTRUGadgetCT(const NTRUGadgetCT& other) = delete;

  NTRUGadgetCT& operator=(const NTRUGadgetCT other) = delete;

  /// @brief Initializes deter_ct_a_dec, deter_ct_a_dec_poly and array_eval_a
  /// @param gadget_ct 
  void init(std::vector<std::shared_ptr<NTRUCT>>& gadget_ct);
   
  /// @brief Multiplies this with the input ct, and stores the result in out.
  /// @param out The output ciphertext.
  /// @param ct The input ciphertext.
  void mul(VectorCT &out, const VectorCT &ct) override;

  void mul(VectorCT &out, const Vector &scalar) override;

  #if defined(USE_CEREAL)
  template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(cereal::base_class<GadgetPolynomialCT>(this));   
        ar(m_ntru_param, m_gadget, m_array_eval_a);     
    }
        
    template <class Archive>
    void load( Archive & ar )
    {    
        ar(cereal::base_class<GadgetPolynomialCT>(this));   
        ar(m_ntru_param, m_gadget, m_array_eval_a);      
    } 
    #endif
       
};
   
/**
 * @brief NTRUGadgetSK class implements encryption methods to produce NTRUGadgetCT
 */
class NTRUGadgetSK : public GadgetPolynomialCTSK{

    protected:

    /// @brief The decomposition gadget.
    std::shared_ptr<Gadget> m_gadget;
    /// @brief The secret key of the NTRU encryption scheme.
    std::shared_ptr<NTRUSK> m_sk;
 
    public:

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
    std::shared_ptr<GadgetVectorCT> gadget_encrypt(const Vector &msg)const override; 

    /// @brief Encrypts the input message array msg, and returns the result.
    /// @param msg The input message array.
    /// @param size The size of the input message array.
    /// @return Creates and returns a new ciphertext.
    std::shared_ptr<GadgetVectorCT> gadget_encrypt(const std::vector<int64_t>& msg)const override;  
     
    /// @brief Encrypts msg * inv_sk, and stores the result in ct_out.
    /// @param msg The input polynomial.
    /// @return Creates and returns a new ciphertext.
    std::shared_ptr<GadgetVectorCT> kdm_gadget_encrypt(const Polynomial &msg)const; 

    /// @brief Encrypts msg * inv_sk, and stores the result in ct_out.
    /// @param msg The input polynomial.
    /// @param size The size of the input message array.
    /// @return Creates and returns a new ciphertext.
    std::shared_ptr<GadgetVectorCT> kdm_gadget_encrypt(const std::vector<int64_t>& msg)const;  

    /// @brief Encrypts the message msg, and returns the resulting ciphertext.
    /// @param msg The input message.
    /// @return Creates a new object that stores the resulting ciphertext.
    std::shared_ptr<ExtendedPolynomialCT> extended_encrypt(const Vector &msg)const override; 

    /// @brief Encrypts the message msg, and returns the resulting ciphertext.
    /// @param msg The input message.
    /// @param size the size of the msg array (should be smaller than the ring size)
    /// @return Creates a new object that stores the resulting ciphertext.
    std::shared_ptr<ExtendedPolynomialCT> extended_encrypt(const std::vector<int64_t>& msg)const override;  
   
    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    { 
        ar(cereal::base_class<GadgetPolynomialCTSK>(this));     
        ar(m_gadget, m_sk);   
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
        ar(cereal::base_class<GadgetPolynomialCTSK>(this));     
        ar(m_gadget, m_sk);   
        m_secret_key = m_sk;
    } 
    #endif

    private:
 
    /// TODO: Make this non-const (public interfaced will be forced to do compies, and check formal formating, but this is free to change the message.)
    /// The alternative is, that you copy the message twice, what doesn't make sense. 
    /// Also, its not publicly available, so the user shoulnd't be affected by this. 
    std::vector<std::shared_ptr<NTRUCT>> ext_enc(const Vector &msg)const;
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