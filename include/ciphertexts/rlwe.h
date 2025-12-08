
#ifndef RLWE_H
#define RLWE_H
 
/**
 * @file rlwe.h
 */

 #include "global_headers.h"

#include "common/sample.h" 
#include "common/gadget.h" 
#include "common/utils.h"
#include "math/polynomial.h"
#include "math/polynomial_multiplication_engine_builder.h"
#include "ciphertexts/polynomial_ciphertext.h"
#include "ciphertexts/lwe.h"
#include "interface/plaintext_encoding.h" 
  
namespace FHEDeck{
 
/**
 * @brief RLWEParam class is used to store the parameters of the RLWE encryption scheme.
 */
class RLWEParam : public PolynomialCTParam{

  protected:
    /// @brief The coefficient modulus
    uint64_t m_coef_modulus;  
    /// @brief The ring type
    /// TODO: Most likley not actually needed for anything
    RingType m_ring;
    /// @brief Indicates the implementation of the multiplication engine. Used to deserialize the RLWEParm object. This way we don't need to serialize the engine itself.
    PolynomialArithmetic m_arithmetic = PolynomialArithmetic::ntt64;
    /// @brief The polynomial multiplication engine. 
    std::shared_ptr<PolynomialMultiplicationEngine> m_mul_engine; 

  public: 
   
    RLWEParam() = default; 
       
    /// @brief Constructs a new RLWEParam object
    /// @param ring Used by the multiplication engine builder.
    /// @param ring_degree The degree of the ring.
    /// @param coef_modulus The coefficient modulus.
    /// @param arithmetic The polynomial arithmetic indicates the implementation of the multiplication engine.
    RLWEParam(RingType ring, int32_t ring_degree, uint64_t coef_modulus, PolynomialArithmetic arithmetic);
 
    RLWEParam(RLWEParam &c) = delete;

    RLWEParam& operator=(RLWEParam other) = delete;

    /// @brief Constructs a new VectorCT object implemented as RLWECT.
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

    /// @brief Initializes the multiplication engine.
    void init_mul_engine(); 
};

/**
 * @brief The RLWE ciphertext class. 
 * Consists of polynomials b and a s.t. b = a*s + e + M, where e and M are the error and message respectively, and s is the secret key polynomial. 
 */
class RLWECT : public PolynomialCT{
  
  protected:

    /// @brief The parameters of the RLWE encryption scheme.
    std::shared_ptr<const RLWEParam> m_param;  

    /// @brief The polynomial a, in the RLWE ciphertext (a, b) s.t. b = a*s + e + M.
    Polynomial m_a;
    /// @brief The polynomial b, in the RLWE ciphertext (a, b) s.t. b = a*s + e + M.
    Polynomial m_b;  

  public:
   
    RLWECT() = default;

    /// @brief Constructs a new RLWECT object.
    /// @param param The parameters of the RLWE encryption scheme.
    RLWECT(std::shared_ptr<RLWEParam> param);
 
    RLWECT(std::shared_ptr<RLWEParam> param, const Polynomial& a, const Polynomial& b);

    RLWECT(std::shared_ptr<RLWEParam> param, Polynomial&& a, Polynomial&& b);
    
    /// @brief Copy constructor
    /// @param other reference to the RLWECT object to be copied.
    RLWECT(const RLWECT &other);
  
    /// @brief = operator
    /// @param other reference to the RLWECT object to be copied.
    RLWECT& operator=(RLWECT other);
  
    /// @brief Negacyclicly rotates the coefficients of the ciphertext polynomials.
    /// @param out The ouptut RLWECT object.
    /// @param rot The size of the rotation. 
    void negacyclic_rotate(RLWECT &out, int32_t rot)const;

    /// @brief Cyclical rotation the coefficients of the ciphertext polynomials.
    /// @param out The ouptut RLWECT object.
    /// @param rot The size of the rotation. 
    void cyclic_rotate(RLWECT &out, int32_t rot)const;

    /// @brief Depending on the RLWEParam ring type, performs a cyclic or nagacyclic rotation the coefficients of the ciphertext polynomials.
    /// @param out The ouptut RLWECT object.
    /// @param rot The size of the rotation. 
    void homomorphic_rotate(VectorCT &out, int32_t rot)const override;

    /// @brief Add ct to this, and store the result in out.
    /// @param out The output RLWECT object.
    /// @param ct The input RLWECT object.
    void add(VectorCT &out, const VectorCT &ct)const override;
 
    /// @brief Add the polynomial x to this, and store the result in out.
    /// @param out The output RLWECT object.
    /// @param x The input polynomial.
    void add(RLWECT &out, const Polynomial &x)const;

    /// @brief Subtract ct from this, and store the result in out.
    /// @param out The output RLWECT object.
    /// @param ct The input RLWECT object.
    void sub(VectorCT &out, const VectorCT &ct)const override;
 
    /// @brief Subtract the polynomial x from this, and store the result in out.
    /// @param out The output RLWECT object.
    /// @param x The input polynomial.
    void sub(RLWECT &out, const Polynomial &x)const; 
 
    /// @brief Multiply this by the polynomial x, and store the result in out.
    /// @param out The output RLWECT object.
    /// @param x The input polynomial.
    void mul(RLWECT &out, const Polynomial &x)const;

    /// @brief Multiply this by the integer x, and store the result in out.
    /// @param out The output RLWECT object.
    /// @param x The input integer.
    void mul(RLWECT &out, int64_t x)const;

    /// @brief Negate the coefficients of this ciphertext's polynomials, and store the result in out.
    /// @param out The output RLWECT object.
    void neg(VectorCT &out)const;
  
    /// @brief Extracts the LWE ciphertext encrypting the constant coefficient from the RLWE ciphertext.
    /// @param out The output ciphertext
    /// @note The function operates only on the ciphertext vector of out, and doesn't set its parameters field. It is assumed that out is properly initialized. 
    /// @todo The function works for negacyclic rings only. It may be a problem when other rings are used.  
    void extract_lwe(LWECT &out)const; 

    /// @brief Extracts the LWE ciphertext encrypting the 'position' coefficient from the RLWE ciphertext.
    /// @param out The output ciphertext
    /// @param position The position of the coefficient to be extracted.
    /// @note The function operates only on the ciphertext vector of out, and doesn't set its parameters field. It is assumed that out is properly initialized.  
    /// @todo The function works for negacyclic rings only. It may be a problem when other rings are used. 
    void extract_lwe(LWECT &out, uint32_t position)const; 
 
    /// @brief Build a string representation of the ciphertext polynomials a and b. It was used for some simple testing. 
    /// @return The string representation. 
    std::string to_string()const;

    const RLWEParam& param()const;
 
    const Polynomial& a()const;

    const Polynomial& b()const;

        /// @brief Copy set the a component
    /// @param in The a component of the ciphertext
    void a(const Polynomial& in);

    /// @brief Copy set the b component
    /// @param in The b component of the ciphertext
    void b(const Polynomial& in);

    /// @brief Move set the a component
    /// @param in The a component of the ciphertext
    void a(Polynomial&& in);

    /// @brief Move set the b component
    /// @param in The b component of the ciphertext
    void b(Polynomial&& in);
    
  #if defined(USE_CEREAL)
  template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(cereal::base_class<PolynomialCT>(this));   
        ar(m_param, m_a, m_b); 
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
        ar(cereal::base_class<PolynomialCT>(this));   
        ar(m_param, m_a, m_b); 
    }  
    #endif 
};
  


/**
 * @brief Implementation of the GSW scheme over the RLWE encryption scheme. It consists of RLWECT(base^i * message).
 */
class ExtendedRLWECT : public ExtendedPolynomialCT{ 

  protected: 

  /// @brief  The parameters of the RLWE encryption scheme.
  std::shared_ptr<RLWEParam> m_rlwe_param;
  /// @brief The gadget decomposition object.
  std::shared_ptr<Gadget> m_gadget; 
  /// @brief Evaluation forms of the polynomials a from the RLWECT(base^i * message) ciphertexts.
  std::shared_ptr<PolynomialArrayEvalForm> m_array_eval_a;
  /// @brief Evaluation forms of the polynomials b from the RLWECT(base^i * message) ciphertexts.
  std::shared_ptr<PolynomialArrayEvalForm> m_array_eval_b; 

  public:
    
  /// @brief Default constructor
  ExtendedRLWECT() = default;
  /// @brief Constructs the object. 
  /// @param rlwe_param The parameters of the RLWE encryption scheme.
  /// @param gadget The gadget decomposition object. 
  /// @param gadget_ct The RLWECT(base^i * message) ciphertexts.
  /// @param gadget_ct_sk The RLWECT(- base^i * message * secret key) ciphertexts.
  ExtendedRLWECT(std::shared_ptr<RLWEParam> rlwe_param, std::shared_ptr<Gadget> gadget, std::vector<std::shared_ptr<RLWECT>> &gadget_ct);
  
  /// @brief Function that initializes deter_ct_a_dec_poly, deter_ct_b_dec_poly, and the pointer tables deter_ct_a_dec and deter_ct_b_dec.
  /// @param gadget_ct The RLWECT(base^i * message) ciphertexts.
  /// @param gadget_ct_sk The RLWECT(- base^i * message * secret key) ciphertexts.
  void init(std::vector<std::shared_ptr<RLWECT>> &gadget_ct);
   
  /// @brief Multiplication of this by ct, and store the result in out.
  /// @param out The result of the multiplication.
  /// @param ct The input ciphertext. 
  void mul(VectorCT &out, const Vector &scalar);
   
  #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(cereal::base_class<GadgetPolynomialCT>(this));   
        ar(m_rlwe_param, m_gadget, m_array_eval_a, m_array_eval_b);     
    }
        
    template <class Archive>
    void load( Archive & ar )
    {    
        ar(cereal::base_class<GadgetPolynomialCT>(this));   
        ar(m_rlwe_param, m_gadget, m_array_eval_a, m_array_eval_b);    
    }  
  #endif 
  
};



  
/**
 * @brief Implementation of the GSW scheme over the RLWE encryption scheme. It consists of RLWECT(base^i * message) and RLWECT(- base^i * message * secret key).
 */
class RLWEGadgetCT : public GadgetPolynomialCT{ 

  protected: 

  /// @brief  The parameters of the RLWE encryption scheme.
  std::shared_ptr<RLWEParam> m_rlwe_param;
  /// @brief The gadget decomposition object.
  std::shared_ptr<Gadget> m_gadget;
 
  /// @brief Evaluation forms of the polynomials a from the RLWECT(base^i * message) ciphertexts.
  std::shared_ptr<PolynomialArrayEvalForm> m_array_eval_a;
  /// @brief Evaluation forms of the polynomials b from the RLWECT(base^i * message) ciphertexts.
  std::shared_ptr<PolynomialArrayEvalForm> m_array_eval_b;
  /// @brief Evaluation forms of the polynomials a from the RLWECT(- base^i * message * secret key) ciphertexts. 
  std::shared_ptr<PolynomialArrayEvalForm> m_array_eval_a_sk;
  /// @brief Evaluation forms of the polynomials b from the RLWECT(- base^i * message * secret key) ciphertexts. 
  std::shared_ptr<PolynomialArrayEvalForm> m_array_eval_b_sk;

  public:
   
  /// @brief Default constructor
  RLWEGadgetCT() = default;
  /// @brief Constructs the object. 
  /// @param rlwe_param The parameters of the RLWE encryption scheme.
  /// @param gadget The gadget decomposition object. 
  /// @param gadget_ct The RLWECT(base^i * message) ciphertexts.
  /// @param gadget_ct_sk The RLWECT(- base^i * message * secret key) ciphertexts.
  RLWEGadgetCT(std::shared_ptr<RLWEParam> rlwe_param, std::shared_ptr<Gadget> gadget, std::vector<std::shared_ptr<RLWECT>> &gadget_ct, std::vector<std::shared_ptr<RLWECT>> &gadget_ct_sk);

  RLWEGadgetCT(const RLWEGadgetCT& other) = delete;

  RLWEGadgetCT& operator=(const RLWEGadgetCT other) = delete;

  /// @brief Function that initializes deter_ct_a_dec_poly, deter_ct_b_dec_poly, and the pointer tables deter_ct_a_dec and deter_ct_b_dec.
  /// @param gadget_ct The RLWECT(base^i * message) ciphertexts.
  /// @param gadget_ct_sk The RLWECT(- base^i * message * secret key) ciphertexts.
  void init(std::vector<std::shared_ptr<RLWECT>> &gadget_ct, std::vector<std::shared_ptr<RLWECT>> &gadget_ct_sk);
   
  /// @brief Multiplication of this by ct, and store the result in out.
  /// @param out The result of the multiplication.
  /// @param ct The input ciphertext. 
  void mul(VectorCT &out, const VectorCT &ct);
   
  #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(cereal::base_class<GadgetPolynomialCT>(this));   
        ar(m_rlwe_param, m_gadget, m_array_eval_a, m_array_eval_b, m_array_eval_a_sk, m_array_eval_b_sk);     
    }
        
    template <class Archive>
    void load( Archive & ar )
    {    
        ar(cereal::base_class<GadgetPolynomialCT>(this));   
        ar(m_rlwe_param, m_gadget, m_array_eval_a, m_array_eval_b, m_array_eval_a_sk, m_array_eval_b_sk);    
    } 
    #endif 
    
};
  
/**
 * @brief The RLWE secret key class.
 */
class RLWESK : public VectorCTSK{

    /// RLWEGadgetSK needs direct access the RLWESK polynomial in its encryption procedure.
    friend class RLWEGadgetSK;

    protected: 
 
    /// @brief The parameters of the RLWE encryption scheme.
    std::shared_ptr<RLWEParam> m_param; 
    /// @brief The type of the key distribution.
    KeyDistribution m_key_type; 
    /// @brief The secret key polynomial.
    Polynomial m_sk_poly; 
    /// @brief The secret key polynomial in evaluation form.
    std::shared_ptr<PolynomialEvalForm> m_sk_poly_eval;  
    /// @brief The uniform distribution used to generate the "a" component of the RLWE ciphertext (a, b = a*sk_poly + e + m).
    std::shared_ptr<Distribution> m_unif_dist;
    /// @brief The noise distribution
    std::shared_ptr<Distribution> m_error_dist; 
    /// @brief The noise standard deviation.  
    double m_noise_stddev;

    public:
 
    /// @brief default destructor
    RLWESK() = default;
  
    /// @brief Constructs the secret key object.
    /// @param param The RLWE parameters.
    /// @param key_type The Key distribution type.
    /// @param noise_stddev The standard deviation of the noise.
    RLWESK(std::shared_ptr<RLWEParam> param, KeyDistribution key_type, double noise_stddev); 
 
    RLWESK(const RLWESK &other) = delete;
 
    RLWESK& operator=(const RLWESK other) = delete;
  
    /// @brief The encryption function. Encrypts the message m, and stores the result in out.
    /// @param out The resulting ciphertext. It is assumed the object is properly initialized.
    /// @param m Polynomial message to be encrypted.
    void encrypt(VectorCT &out, const Vector &m)override;  
    
    /// @brief The encryption function. Encrypts the message m, and returns the resulting ciphertext.
    /// @param m The polynomial message to be encrypted.
    /// @return Creates and returns the resulting ciphertext.
    std::shared_ptr<VectorCT> encrypt(const Vector &m)override; 

    /// @brief Encodes the message m using the encoding scheme, and encrypts it.
    /// @param m The input message.
    /// @param encoding The encoding scheme.
    /// @return Creates and returns the resulting ciphertext.
    void encode_and_encrypt(VectorCT& out, const Vector& m, PlaintextEncoding encoding)override;

    /// @brief Encodes the message m using the encoding scheme, and encrypts it.
    /// @param m The input message.
    /// @param encoding The encoding scheme.
    /// @return Creates and returns the resulting ciphertext.
    std::shared_ptr<VectorCT> encode_and_encrypt(const Vector& m, PlaintextEncoding encoding)override;
     
    /// @brief Partial decryption. Runs b - a*sk_poly, and stores the result in out.
    /// @param phase The resulting partial decryption. 
    /// @param ct The input ciphertext.
    void partial_decrypt(Polynomial &phase, const RLWECT &ct);
  
    /// @brief  Decrypts the ciphertext ct, and returns the resulting polynomial.
    /// @param ct The input ciphertext.
    /// @param encoding The encoding scheme.
    /// @return Creates a new polynomial and which is the result of the decryption.
    std::shared_ptr<Vector> decrypt(const VectorCT &ct, PlaintextEncoding encoding)override;
  
    /// @brief Decrypts the ciphertext ct, and stores the result in out.
    /// @param out The resulting polynomial.
    /// @param ct The input ciphertext.
    /// @param encoding The plaintext encoding scheme.
    void decrypt(Vector &out, const VectorCT &ct, PlaintextEncoding encoding)override;
   
    /// @brief Extract a LWE key from this secret key. The LWE secret key decrypt LWE ciphertexts extracted from the RLWE ciphertexts for the zero coefficient.
    /// @return Creates a new object that stores the LWE secret key. Creates also new LWEParam for this object. 
    std::shared_ptr<LWESK> extract_lwe_key();
 
    std::shared_ptr<RLWEParam> param()const;
    
    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    {   
        ar(cereal::base_class<VectorCTSK>(this));   
        ar(m_param, m_key_type, m_sk_poly, m_noise_stddev);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {      
      ar(cereal::base_class<VectorCTSK>(this)); 
      ar(m_param, m_key_type, m_sk_poly, m_noise_stddev);    
      init(); 
    }  
    #endif 

  private:
    void init();
    void key_gen();

};

/**
 * @brief The RLWE gadget secret key class. 
 */
class RLWEGadgetSK : public GadgetPolynomialCTSK{

    protected:
  
    /// @brief The gadget decomposition object.
    std::shared_ptr<Gadget> m_gadget;
    /// @brief the RLWE secret key object.
    std::shared_ptr<RLWESK> m_rlwe_sk;

    public:
    
    /// @brief default constructor. 
    RLWEGadgetSK() = default;

    /// @brief Constructs the object.
    /// @param gadget The gadget decomposition object.
    /// @param rlwe_sk The RLWE secret key object.
    RLWEGadgetSK(std::shared_ptr<Gadget> gadget, std::shared_ptr<RLWESK> rlwe_sk);
 
    RLWEGadgetSK(const RLWEGadgetSK &other) = delete;
 
    RLWEGadgetSK& operator=(const RLWEGadgetSK other) = delete;
       
    /// @brief Encrypts the message msg, and returns the resulting ciphertext.
    /// @param msg The input message.
    /// @return Creates a new object that stores the resulting ciphertext.
    std::shared_ptr<GadgetVectorCT> gadget_encrypt(const Vector &msg)const override; 

    /// @brief Encrypts the message msg, and returns the resulting ciphertext.
    /// @param msg The input message.
    /// @param size the size of the msg array (should be smaller than the ring size)
    /// @return Creates a new object that stores the resulting ciphertext. 
    std::shared_ptr<GadgetVectorCT> gadget_encrypt(const std::vector<int64_t>& msg)const override;  

    /// @brief Encrypts the message msg, and returns the resulting ciphertext.
    /// @param msg The input message.
    /// @return Creates a new object that stores the resulting ciphertext.
    std::shared_ptr<ExtendedPolynomialCT> extended_encrypt(const Vector &msg)const override; 

    /// @brief Encrypts the message msg, and returns the resulting ciphertext.
    /// @param msg The input message.
    /// @param size the size of the msg array (should be smaller than the ring size)
    /// @return Creates a new object that stores the resulting ciphertext.
    std::shared_ptr<ExtendedPolynomialCT> extended_encrypt(const std::vector<int64_t>& msg)const override;  

    std::shared_ptr<RLWEParam> param()const;

    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(cereal::base_class<GadgetPolynomialCTSK>(this));     
      ar(m_gadget, m_rlwe_sk);   
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(cereal::base_class<GadgetPolynomialCTSK>(this));     
      ar(m_gadget, m_rlwe_sk);   
      m_secret_key = m_rlwe_sk;
    } 
    #endif 

  private:

  std::vector<std::shared_ptr<RLWECT>> ext_enc(Polynomial &msg)const;

};
 
} /// End of namesapce FHEDeck

#if defined(USE_CEREAL)
CEREAL_REGISTER_TYPE(FHEDeck::RLWEParam)
CEREAL_REGISTER_TYPE(FHEDeck::RLWECT)
CEREAL_REGISTER_TYPE(FHEDeck::RLWESK)
CEREAL_REGISTER_TYPE(FHEDeck::RLWEGadgetCT)
CEREAL_REGISTER_TYPE(FHEDeck::RLWEGadgetSK)
#endif 
 
#endif