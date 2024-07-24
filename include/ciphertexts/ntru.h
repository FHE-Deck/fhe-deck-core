 
#ifndef NTRU_H
#define NTRU_H

#include <NTL/ZZX.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_p.h>
#include <complex>
#include "sample.h"
#include "utils.h" 
#include "fft_plan.h"

#include "lwe.h"
#include "polynomial.h"
#include "polynomial_ciphertext.h"
#include "gadget.h"


#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
 
namespace fhe_deck{


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
    PolynomialArithmetic arithmetic = ntl;
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

    /// @brief Constructs the NTRUParam object. 
    /// @param ring_degree The degree of the ring.
    /// @param coef_modulus The coefficient modulus.
    /// @param mul_engine The polynomial multiplication engine.
    NTRUParam(int32_t ring_degree, uint64_t coef_modulus, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine);
   
    NTRUParam(NTRUParam &c);

    NTRUParam& operator=(NTRUParam other);

    /// @brief Constructs a new VectorCT object implemented as NTRUCT.
    /// @param param The parameters of the NTRU encryption scheme. Usually its the same object. 
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
    void negacyclic_rotate(NTRUCT *out, int32_t rot);

    /// @brief Cyclical rotation of the ciphertext polynomial.
    /// @param out The output ciphertext.
    /// @param rot The rotation amount.
    void cyclic_rotate(NTRUCT *out, int32_t rot);

    /// @brief Negacyclic rotation of the ciphertext polynomial.
    /// @param out The output ciphertext.
    /// @param rot The rotation amount.
    void homomorphic_rotate(VectorCT *out, int32_t rot);

    /// @brief Adds this ciphertext to ct and store the result in out.
    /// @param out The output ciphertext.
    /// @param ct The input ciphertext.
    void add(VectorCT *out,  VectorCT *ct);
 
    /// @brief Adds x to this ciphertext, and stores the result in out.
    /// @param out The output ciphertext.
    /// @param x The input polynomial.
    void add(NTRUCT *out, Polynomial *x);

    /// @brief Subtracts ct from this ciphertext, and stores the result in out.
    /// @param out The output ciphertext.
    /// @param ct The input ciphertext.
    void sub(VectorCT *out, VectorCT *ct);
 
    /// @brief Subtracts x from this ciphertext, and stores the result in out. 
    /// @param out The output ciphertext.
    /// @param x The input polynomial.
    void sub(NTRUCT *out, Polynomial *x); 
 
    /// @brief Multiplies this ciphertexts with x, and stores the result in out.
    /// @param out The output ciphertext.
    /// @param x The input polynomial.
    void mul(NTRUCT *out, Polynomial *x);

    /// @brief Negates this ciphertexts coefficients and stores the result in out.
    /// @param out The output ciphertext.
    void neg(VectorCT *out);
 
    /// @brief Extracts an LWE ciphertext that encodes the constant coefficient. 
    /// @param out The output LWE ciphertext.
    void extract_lwe(LWECT *out);
 
    /// @brief Produces a string representation of this object. 
    /// @return The string representation.
    std::string to_string();
    
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
};

/**
 * @brief NTRUSK class is used to store the secret key of the NTRU encryption scheme, and implements the encryption and decryption operations.
 */
class NTRUSK{

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
  
    NTRUSK(const NTRUSK &other);

    NTRUSK& operator=(const NTRUSK other);
  
    /// @brief Encrypts the message polynomial m, and stores the result in out.
    /// @param out The output ciphertext. 
    /// @param m The input polynomial.
    void encrypt(NTRUCT *out, Polynomial *m);
 
    /// @brief Encrypts the message polynomial m, and returns the result.
    /// @param m The input polynomial.
    /// @return Creates and returns a new ciphertext.
    NTRUCT* encrypt(Polynomial *m); 

    /// @brief Encodes and the message polynomial m, and returns the result.
    /// @param m The input polynomial.
    /// @param encoding The encoding scheme.
    /// @return Creates and returns a new ciphertext.
    NTRUCT* encode_and_encrypt(Polynomial* m, PlaintextEncoding encoding);
 
    /// @brief Partially decrypts the ciphertext. Multiplies the ct polynomial with sk. 
    /// @param phase The output polynomial.
    /// @param ct The input ciphertext.
    void partial_decrypt(Polynomial *phase, NTRUCT *ct);
 
    /// @brief Decrypts the input ciphertext, and returns a new polynomial.
    /// @param ct The input ciphertext.
    /// @param encoding The encoding scheme.
    /// @return Creates and returns a new polynomial.
    Polynomial* decrypt(NTRUCT *ct, PlaintextEncoding encoding);
 
    /// @brief Decrypts ct, and stores the result in out.
    /// @param out The  output polynomial.
    /// @param ct the input ciphertext.
    /// @param encoding The encoding scheme.
    void decrypt(Polynomial *out, NTRUCT *ct, PlaintextEncoding encoding);
   
    /// @brief Encrypts msg * inv_sk. 
    /// @param msg The input polynomial.
    /// @return Creates and returns a new ciphertext.
    NTRUCT* kdm_encrypt(Polynomial* msg); 
 
    /// @brief Encrypts msg * inv_sk, and stores the result in ct_out
    /// @param ct_out The output ciphertext.
    /// @param msg The input polynomial.
    void kdm_encrypt(NTRUCT *ct_out, Polynomial* msg);
    
    /// @brief Encodes msg,  encrypts encoding.encode(msg) * inv_sk, and stores the result in ct_out
    /// @param ct_out The output ciphertext.
    /// @param msg The input polynomial.
    /// @param encoding The input encoding.
    void kdm_encode_and_encrypt(NTRUCT *ct_out, Polynomial* msg, PlaintextEncoding encoding);
    
    /// @brief Encodes msg,  encrypts encoding.encode(msg) * inv_sk.
    /// @param msg The input polynomial.
    /// @param encoding The input encoding.
    /// @return Creates and returns a new ciphertext.
    NTRUCT* kdm_encode_and_encrypt(Polynomial* msg, PlaintextEncoding encoding);
  
    /// @brief Extracts the LWE key.
    /// @return Creates and returns a new LWE key, with a newly created LWEParam object.
    LWESK* extract_lwe_key();
   
    template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(param, sk, inv_sk, noise_stddev);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
      ar(param, sk, inv_sk, noise_stddev);  
      this->sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(-1, 1)); 
      this->error_dist = std::shared_ptr<Distribution>(new StandardRoundedGaussianDistribution(0, noise_stddev));
    }  
};

  
/**
 * @brief NTRUGadgetCT class implements the extended NTRU ciphertext of the form NTRU(base^i m), that can be multiplied with NTRUCT.

 */
class NTRUGadgetCT : public GadgetPolynomialCT{ 

  public:
  
  /// @brief The parameters of the NTRU encryption scheme.
  std::shared_ptr<NTRUParam> ntru_param;
  /// @brief The decomposition gadget. 
  std::shared_ptr<Gadget> gadget;
  /// @brief Flag indicating whether the gadget is initialized.
  bool is_init = false;  
  /// @brief The array evaluation form holding the decomposition of the ciphertext.
  std::unique_ptr<PolynomialArrayEvalForm> array_eval_a;  
  /// @brief Array pointing to memory locations of the decomposition of the ciphertext.
  int64_t** deter_ct_a_dec; 
  /// @brief Array holding the decomposition of the ciphertext.
  PolynomialArrayCoefForm deter_ct_a_dec_poly; 
   
  /// @brief Free deter_ct_a_dec memory.
  ~NTRUGadgetCT();

  /// @brief Default constructor.
  NTRUGadgetCT() = default;
   
  /// @brief Constructs the NTRUGadgetCT object.
  /// @param ntru_param The parameters of the NTRU encryption scheme.
  /// @param gadget The decomposition gadget.
  /// @param gadget_ct The array of NTRUCT objects.
  NTRUGadgetCT(std::shared_ptr<NTRUParam> ntru_param, std::shared_ptr<Gadget> gadget, std::vector<std::unique_ptr<NTRUCT>> &gadget_ct);

  NTRUGadgetCT(const NTRUGadgetCT& other);

  NTRUGadgetCT& operator=(const NTRUGadgetCT other);

  /// @brief Initializes deter_ct_a_dec, deter_ct_a_dec_poly and array_eval_a
  /// @param gadget_ct 
  void init(std::vector<std::unique_ptr<NTRUCT>> &gadget_ct);
   
  /// @brief Multiplies this with the input ct, and stores the result in out.
  /// @param out The output ciphertext.
  /// @param ct The input ciphertext.
  void mul(VectorCT *out, const VectorCT *ct);

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
        set_gadget_decomp_arrays();    
        this->is_init = true;  
    } 
     
  private:
    
  void set_gadget_decomp_arrays();
  
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

    NTRUGadgetSK(const NTRUGadgetSK &other);

    NTRUGadgetSK& operator=(const NTRUGadgetSK other);

    /// @brief Encrypts the input polynomial msg, and returns the result.
    /// @param msg The input polynomial.
    /// @return Creates and returns a new ciphertext.        
    GadgetVectorCT* gadget_encrypt(Polynomial *msg); 

    /// @brief Encrypts the input message array msg, and returns the result.
    /// @param msg The input message array.
    /// @param size The size of the input message array.
    /// @return Creates and returns a new ciphertext.
    GadgetVectorCT* gadget_encrypt(uint64_t *msg, int32_t size); 

    /// @brief Encrypts msg * inv_sk, and stores the result in ct_out.
    /// @param msg The input polynomial.
    /// @return Creates and returns a new ciphertext.
    GadgetVectorCT* kdm_gadget_encrypt(Polynomial *msg); 

    /// @brief Encrypts msg * inv_sk, and stores the result in ct_out.
    /// @param msg The input polynomial.
    /// @param size The size of the input message array.
    /// @return Creates and returns a new ciphertext.
    GadgetVectorCT* kdm_gadget_encrypt(uint64_t *msg, int32_t size); 
   
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
    } 
};
 
} /// End of namespace fhe_deck


CEREAL_REGISTER_TYPE(fhe_deck::NTRUParam)
CEREAL_REGISTER_TYPE(fhe_deck::NTRUCT)
CEREAL_REGISTER_TYPE(fhe_deck::NTRUGadgetCT)
CEREAL_REGISTER_TYPE(fhe_deck::NTRUGadgetSK)


#endif