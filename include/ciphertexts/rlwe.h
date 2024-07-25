
#ifndef RLWE_H
#define RLWE_H
 
#include "enums.h"
#include "sample.h"
#include "fft_plan.h"
#include "lwe.h"
#include "gadget.h"
#include "hexl/hexl.hpp"
#include "utils.h"
#include "polynomial.h"
#include "polynomial_multiplication_engine_builder.h"
#include "polynomial_ciphertext.h"
#include "plaintext_encoding.h" 
 
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
 
namespace fhe_deck{
 
/**
 * @brief RLWEParam class is used to store the parameters of the RLWE encryption scheme.
 */
class RLWEParam : public PolynomialCTParam{

  public: 
    /// @brief The coefficient modulus
    uint64_t coef_modulus;  
    /// @brief The ring type
    RingType ring;
    /// @brief Indicates the implementation of the multiplication engine. Used to deserialize the RLWEParm object. This way we don't need to serialize the engine itself.
    PolynomialArithmetic arithmetic = ntl;
    /// @brief The polynomial multiplication engine. 
    std::shared_ptr<PolynomialMultiplicationEngine> mul_engine;
    /// @brief Indicates if the multiplication engine is initialized. Used to avoid multiple initializations.
 
    ~RLWEParam() = default; 

    RLWEParam() = default; 
       
    /// @brief Constructs a new RLWEParam object
    /// @param ring Used by the multiplication engine builder.
    /// @param ring_degree The degree of the ring.
    /// @param coef_modulus The coefficient modulus.
    /// @param arithmetic The polynomial arithmetic indicates the implementation of the multiplication engine.
    RLWEParam(RingType ring, int32_t ring_degree, uint64_t coef_modulus, PolynomialArithmetic arithmetic);

    /// @brief Constructs a new RLWEParam object
    /// @param ring_degree The degree of the ring.
    /// @param coef_modulus The coefficient modulus.
    /// @param mul_engine The multiplication engine.
    RLWEParam(int32_t ring_degree, uint64_t coef_modulus, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine);
   
    RLWEParam(RLWEParam &c);

    RLWEParam& operator=(RLWEParam other);

    /// @brief Constructs a new VectorCT object implemented as RLWECT.
    /// @param param The parameters of the RLWE encryption scheme. Usually its the same object. 
    /// @return Retuns a new VectorCT object.
    VectorCT* init_ct(std::shared_ptr<VectorCTParam> param);
      
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
 
  private:

    /// @brief Initializes the multiplication engine.
    void init_mul_engine(); 
};

/**
 * @brief The RLWE ciphertext class. 
 * Consists of polynomials b and a s.t. b = a*s + e + M, where e and M are the error and message respectively, and s is the secret key polynomial. 
 */
class RLWECT : public PolynomialCT{

  public:
  
    /// @brief The parameters of the RLWE encryption scheme.
    std::shared_ptr<RLWEParam> param;  

    /// @brief The polynomial a, in the RLWE ciphertext (a, b) s.t. b = a*s + e + M.
    Polynomial a;
    /// @brief The polynomial b, in the RLWE ciphertext (a, b) s.t. b = a*s + e + M.
    Polynomial b;  
    
    ~RLWECT() = default;

    RLWECT() = default;

    /// @brief Constructs a new RLWECT object.
    /// @param param The parameters of the RLWE encryption scheme.
    RLWECT(std::shared_ptr<RLWEParam> param);
 
    /// @brief Copy constructor
    /// @param other reference to the RLWECT object to be copied.
    RLWECT(const RLWECT &other);
   
    /// @brief = operator
    /// @param other reference to the RLWECT object to be copied.
    RLWECT& operator=(RLWECT other);
  
    /// @brief Negacyclicly rotates the coefficients of the ciphertext polynomials.
    /// @param out The ouptut RLWECT object.
    /// @param rot The size of the rotation. 
    void negacyclic_rotate(RLWECT *out, int32_t rot);

    /// @brief Cyclical rotation the coefficients of the ciphertext polynomials.
    /// @param out The ouptut RLWECT object.
    /// @param rot The size of the rotation. 
    void cyclic_rotate(RLWECT *out, int32_t rot);

    /// @brief Depending on the RLWEParam ring type, performs a cyclic or nagacyclic rotation the coefficients of the ciphertext polynomials.
    /// @param out The ouptut RLWECT object.
    /// @param rot The size of the rotation. 
    void homomorphic_rotate(VectorCT *out, int32_t rot);

    /// @brief Add ct to this, and store the result in out.
    /// @param out The output RLWECT object.
    /// @param ct The input RLWECT object.
    void add(VectorCT *out,  VectorCT *ct);
 
    /// @brief Add the polynomial x to this, and store the result in out.
    /// @param out The output RLWECT object.
    /// @param x The input polynomial.
    void add(RLWECT *out, Polynomial *x);

    /// @brief Subtract ct from this, and store the result in out.
    /// @param out The output RLWECT object.
    /// @param ct The input RLWECT object.
    void sub(VectorCT *out, VectorCT *ct);
 
    /// @brief Subtract the polynomial x from this, and store the result in out.
    /// @param out The output RLWECT object.
    /// @param x The input polynomial.
    void sub(RLWECT *out, Polynomial *x); 
 
    /// @brief Multiply this by the polynomial x, and store the result in out.
    /// @param out The output RLWECT object.
    /// @param x The input polynomial.
    void mul(RLWECT *out, Polynomial *x);

    /// @brief Multiply this by the integer x, and store the result in out.
    /// @param out The output RLWECT object.
    /// @param x The input integer.
    void mul(RLWECT *out, int64_t x);

    /// @brief Negate the coefficients of this ciphertext's polynomials, and store the result in out.
    /// @param out The output RLWECT object.
    void neg(VectorCT *out);
  
    /// @brief Extracts the LWE ciphertext encrypting the constant coefficient from the RLWE ciphertext.
    /// @param out The output ciphertext
    /// @note The function operates only on the ciphertext vector of out, and doesn't set its parameters field. It is assumed that out is properly initialized. 
    /// @todo The function works for negacyclic rings only. It may be a problem when other rings are used.  
    void extract_lwe(LWECT *out); 

    /// @brief Extracts the LWE ciphertext encrypting the 'position' coefficient from the RLWE ciphertext.
    /// @param out The output ciphertext
    /// @param position The position of the coefficient to be extracted.
    /// @note The function operates only on the ciphertext vector of out, and doesn't set its parameters field. It is assumed that out is properly initialized.  
    /// @todo The function works for negacyclic rings only. It may be a problem when other rings are used. 
    void extract_lwe(LWECT *out, uint32_t position); 
 
    /// @brief Build a string representation of the ciphertext polynomials a and b. It was used for some simple testing. 
    /// @return The string representation. 
    std::string to_string();
    
  template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(cereal::base_class<PolynomialCT>(this));   
        ar(param, a, b); 
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
        ar(cereal::base_class<PolynomialCT>(this));   
        ar(param, a, b); 
    }  
};
  

  
/**
 * @brief Implementation of the GSW scheme over the RLWE encryption scheme. It consists of RLWECT(base^i * message) and RLWECT(- base^i * message * secret key).
 */
class RLWEGadgetCT : public GadgetPolynomialCT{ 

  public:
  
  /// @brief  The parameters of the RLWE encryption scheme.
  std::shared_ptr<RLWEParam> rlwe_param;
  /// @brief The gadget decomposition object.
  std::shared_ptr<Gadget> gadget;

  bool is_init = false;  
  /// @brief Evaluation forms of the polynomials a from the RLWECT(base^i * message) ciphertexts.
  std::unique_ptr<PolynomialArrayEvalForm> array_eval_a;
  /// @brief Evaluation forms of the polynomials b from the RLWECT(base^i * message) ciphertexts.
  std::unique_ptr<PolynomialArrayEvalForm> array_eval_b;
  /// @brief Evaluation forms of the polynomials a from the RLWECT(- base^i * message * secret key) ciphertexts. 
  std::unique_ptr<PolynomialArrayEvalForm> array_eval_a_sk;
  /// @brief Evaluation forms of the polynomials b from the RLWECT(- base^i * message * secret key) ciphertexts. 
  std::unique_ptr<PolynomialArrayEvalForm> array_eval_b_sk;
   
  
   
  /// @brief Frees deter_ct_a_dec and  deter_ct_b_dec
  ~RLWEGadgetCT();
  /// @brief Default constructor
  RLWEGadgetCT() = default;
  /// @brief Constructs the object. 
  /// @param rlwe_param The parameters of the RLWE encryption scheme.
  /// @param gadget The gadget decomposition object. 
  /// @param gadget_ct The RLWECT(base^i * message) ciphertexts.
  /// @param gadget_ct_sk The RLWECT(- base^i * message * secret key) ciphertexts.
  RLWEGadgetCT(std::shared_ptr<RLWEParam> rlwe_param, std::shared_ptr<Gadget> gadget, std::vector<std::unique_ptr<RLWECT>> &gadget_ct, std::vector<std::unique_ptr<RLWECT>> &gadget_ct_sk);

  RLWEGadgetCT(const RLWEGadgetCT& other);

  RLWEGadgetCT& operator=(const RLWEGadgetCT other);

  /// @brief Function that initializes deter_ct_a_dec_poly, deter_ct_b_dec_poly, and the pointer tables deter_ct_a_dec and deter_ct_b_dec.
  /// @param gadget_ct The RLWECT(base^i * message) ciphertexts.
  /// @param gadget_ct_sk The RLWECT(- base^i * message * secret key) ciphertexts.
  void init(std::vector<std::unique_ptr<RLWECT>> &gadget_ct, std::vector<std::unique_ptr<RLWECT>> &gadget_ct_sk);
   
  /// @brief Multiplication of this by ct, and store the result in out.
  /// @param out The result of the multiplication.
  /// @param ct The input ciphertext. 
  void mul(VectorCT *out, const VectorCT *ct);
   
    template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(cereal::base_class<GadgetPolynomialCT>(this));   
        ar(rlwe_param, gadget, array_eval_a, array_eval_b, array_eval_a_sk, array_eval_b_sk);     
    }
        
    template <class Archive>
    void load( Archive & ar )
    {    
        ar(cereal::base_class<GadgetPolynomialCT>(this));   
        ar(rlwe_param, gadget, array_eval_a, array_eval_b, array_eval_a_sk, array_eval_b_sk);  
        //this->out_minus = RLWECT(rlwe_param);  
        this->poly_decomp_eval_form = std::shared_ptr<PolynomialArrayEvalForm>(rlwe_param->mul_engine->init_polynomial_array_eval_form(gadget->digits));
        init_gadget_decomp_tables();    
        this->is_init = true;  
    } 
  
  private:
 
  /// @brief Pointers to the continuous memory storing the gadget decomposed polynomials deter_ct_a_dec_poly.
  int64_t** poly_decomp;  
  /// @brief The array of polynomials that are the result of gadget decomposition. 
  PolynomialArrayCoefForm poly_decomp_coef_form; 

  /// @brief Temporary variable which stores the evaluation form of a decomposed polynomial. Used in Multiplication, initialized in init.
  std::shared_ptr<PolynomialArrayEvalForm> poly_decomp_eval_form;
  
  void init_gadget_decomp_tables();
  
};
  
/**
 * @brief The RLWE secret key class.
 */
class RLWESK{

    public:

    /// @brief The parameters of the RLWE encryption scheme.
    std::shared_ptr<RLWEParam> param; 
    /// @brief The type of the key distribution.
    KeyDistribution key_type; 
    /// @brief The secret key polynomial.
    Polynomial sk_poly; 
    /// @brief The secret key polynomial in evaluation form.
    std::unique_ptr<PolynomialEvalForm> sk_poly_eval; 
    /// @brief Indicates if the object is initialized. Used to avoid multiple initializations.
    bool is_init = false;  
    /// @brief The uniform distribution used to generate the "a" component of the RLWE ciphertext (a, b = a*sk_poly + e + m).
    std::shared_ptr<Distribution> unif_dist;
    /// @brief The noise distribution
    std::shared_ptr<Distribution> error_dist; 
    double noise_stddev;
  
    /// @brief default destructor
    RLWESK() = default;
  
    /// @brief Constructs the secret key object.
    /// @param param The RLWE parameters.
    /// @param key_type The Key distribution type.
    /// @param noise_stddev The standard deviation of the noise.
    RLWESK(std::shared_ptr<RLWEParam> param, KeyDistribution key_type, double noise_stddev); 
  
    /// @brief Throw an exception.
    /// @param other 
    RLWESK(const RLWESK &other);

    /// @brief Throw an exception.
    RLWESK& operator=(const RLWESK other);
  
    /// @brief The encryption function. Encrypts the message m, and stores the result in out.
    /// @param out The resulting ciphertext. It is assumed the object is properly initialized.
    /// @param m Polynomial message to be encrypted.
    void encrypt(RLWECT *out, Polynomial *m);  
    
    /// @brief The encryption function. Encrypts the message m, and returns the resulting ciphertext.
    /// @param m The polynomial message to be encrypted.
    /// @return Creates and returns the resulting ciphertext.
    RLWECT* encrypt(Polynomial *m); 

    /// @brief Encodes the message m using the encoding scheme, and encrypts it.
    /// @param m The input message.
    /// @param encoding The encoding scheme.
    /// @return Creates and returns the resulting ciphertext.
    RLWECT* encode_and_encrypt(Polynomial* m, PlaintextEncoding encoding);
 
    /// @brief Partial decryption. Runs b - a*sk_poly, and stores the result in out.
    /// @param phase The resulting partial decryption. 
    /// @param ct The input ciphertext.
    void partial_decrypt(Polynomial *phase, RLWECT *ct);
  
    /// @brief  Decrypts the ciphertext ct, and returns the resulting polynomial.
    /// @param ct The input ciphertext.
    /// @param encoding The encoding scheme.
    /// @return Creates a new polynomial and which is the result of the decryption.
    Polynomial* decrypt(RLWECT *ct, PlaintextEncoding encoding);
  
    /// @brief Decrypts the ciphertext ct, and stores the result in out.
    /// @param out The resulting polynomial.
    /// @param ct The input ciphertext.
    /// @param encoding The plaintext encoding scheme.
    void decrypt(Polynomial *out, RLWECT *ct, PlaintextEncoding encoding);
 
    /// @brief Extract a LWE key from this secret key. The LWE secret key decrypt LWE ciphertexts extracted from the RLWE ciphertexts for the zero coefficient.
    /// @param lwe_key An array that stores the LWE secret key.
    void extract_lwe_key(long* lwe_key);

    /// @brief Extract a LWE key from this secret key. The LWE secret key decrypt LWE ciphertexts extracted from the RLWE ciphertexts for the zero coefficient.
    /// @return Creates a new object that stores the LWE secret key. Creates also new LWEParam for this object. 
    LWESK* extract_lwe_key();
    
    template <class Archive>
    void save( Archive & ar ) const
    {       
        ar(param, key_type, sk_poly, noise_stddev);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {      
      ar(param, key_type, sk_poly, noise_stddev);    
      init(); 
    }  

  private:
    void init();
    void key_gen();

};

/**
 * @brief The RLWE gadget secret key class. 
 */
class RLWEGadgetSK : public GadgetPolynomialCTSK{

    public:
  
    /// @brief The gadget decomposition object.
    std::shared_ptr<Gadget> gadget;
    /// @brief the RLWE secret key object.
    std::shared_ptr<RLWESK> rlwe_sk;

    /// @brief default constructor. 
    RLWEGadgetSK() = default;

    /// @brief Constructs the object.
    /// @param gadget The gadget decomposition object.
    /// @param rlwe_sk The RLWE secret key object.
    RLWEGadgetSK(std::shared_ptr<Gadget> gadget, std::shared_ptr<RLWESK> rlwe_sk);

    /// @brief Throws an exception.
    /// @param other 
    RLWEGadgetSK(const RLWEGadgetSK &other);

    /// @brief Throws an exception
    /// @param other 
    /// @return 
    RLWEGadgetSK& operator=(const RLWEGadgetSK other);
       
    /// @brief Encrypts the message msg, and returns the resulting ciphertext.
    /// @param msg The input message.
    /// @return Creates a new object that stores the resulting ciphertext.
    GadgetVectorCT* gadget_encrypt(Polynomial *msg); 

    /// @brief Encrypts the message msg, and returns the resulting ciphertext.
    /// @param msg The input message.
    /// @param size the size of the msg array (should be smaller than the ring size)
    /// @return Creates a new object that stores the resulting ciphertext.
    GadgetVectorCT* gadget_encrypt(uint64_t *msg, int32_t size); 


 
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(cereal::base_class<GadgetPolynomialCTSK>(this));     
      ar(gadget, rlwe_sk);   
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(cereal::base_class<GadgetPolynomialCTSK>(this));     
      ar(gadget, rlwe_sk);   
    } 

  private:

  std::vector<std::unique_ptr<RLWECT>> ext_enc(Polynomial *msg);

};
 
}

CEREAL_REGISTER_TYPE(fhe_deck::RLWEParam)
CEREAL_REGISTER_TYPE(fhe_deck::RLWECT)
CEREAL_REGISTER_TYPE(fhe_deck::RLWEGadgetCT)
CEREAL_REGISTER_TYPE(fhe_deck::RLWEGadgetSK)
 
 
#endif