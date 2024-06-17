
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
#include "vector_ciphertext.h"
#include "plaintext_encoding.h"
 
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
 
namespace fhe_deck{
 

class RLWEParam : public VectorCTParam{

  public: 
    long coef_modulus;  
    RingType ring;
    ModulusType mod_type;   
    PolynomialArithmetic arithmetic = ntl;

    std::shared_ptr<PolynomialMultiplicationEngine> mul_engine;
    bool is_mul_engine_init = false;
 
    ~RLWEParam() = default; 

    RLWEParam() = default; 
       
    RLWEParam(RingType ring, int ring_degree, long coef_modulus, ModulusType mod_type, PolynomialArithmetic arithmetic);

    RLWEParam(int ring_degree, long coef_modulus, ModulusType mod_type, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine);
   
    RLWEParam(RLWEParam &c);

    RLWEParam& operator=(RLWEParam other);

    VectorCT* init_ct(std::shared_ptr<VectorCTParam> param);
      
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(cereal::base_class<VectorCTParam>(this));   
      ar(ring, size, coef_modulus, mod_type, arithmetic);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(cereal::base_class<VectorCTParam>(this));   
      ar(ring, size, coef_modulus, mod_type, arithmetic);  
      init_mul_engine(); 
    } 
 
  private:
    void init_mul_engine(); 
};

class RLWECT : public VectorCT{

  public:
  
    std::shared_ptr<RLWEParam> param; 
    // Polynomials b, and a s.t. b = a*s + e + M, where e and M are the error and message respectively, and s is the secret key polynomial 
    Polynomial a;
    Polynomial b;  
    
    ~RLWECT() = default;

    RLWECT() = default;

    RLWECT(std::shared_ptr<RLWEParam> param);
 
    RLWECT(const RLWECT &other);
   
    RLWECT& operator=(RLWECT other);
  
    void negacyclic_rotate(RLWECT *out, int rot);

    void cyclic_rotate(RLWECT *out, int rot);

    void homomorphic_rotate(VectorCT *out, int rot);

    void add(VectorCT *out,  VectorCT *ct);
 
    void add(RLWECT *out, Polynomial *x);

    void sub(VectorCT *out, VectorCT *ct);
 
    void sub(RLWECT *out, Polynomial *x); 
 
    void mul(RLWECT *out, Polynomial *x);

    void neg(VectorCT *out);
  
    void extract_lwe(LWECT *out); 
 
    std::string to_string();
    
  template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(cereal::base_class<VectorCT>(this));   
        ar(param, a, b); 
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
        ar(cereal::base_class<VectorCT>(this));   
        ar(param, a, b); 
    }  
};
  
  
class RLWEGadgetCT : public GadgetVectorCT{ 

  public:
  
  std::shared_ptr<RLWEParam> rlwe_param;
  std::shared_ptr<Gadget> gadget;

  bool is_init = false;  
  std::unique_ptr<PolynomialArrayEvalForm> array_eval_a;
  std::unique_ptr<PolynomialArrayEvalForm> array_eval_b;
  std::unique_ptr<PolynomialArrayEvalForm> array_eval_a_sk;
  std::unique_ptr<PolynomialArrayEvalForm> array_eval_b_sk;
   
  long** deter_ct_a_dec;
  long** deter_ct_b_dec;  
  PolynomialArrayCoefForm deter_ct_a_dec_poly;
  PolynomialArrayCoefForm deter_ct_b_dec_poly;
   
  ~RLWEGadgetCT();

  RLWEGadgetCT() = default;
   
  RLWEGadgetCT(std::shared_ptr<RLWEParam> rlwe_param, std::shared_ptr<Gadget> gadget, std::vector<std::unique_ptr<RLWECT>> &gadget_ct, std::vector<std::unique_ptr<RLWECT>> &gadget_ct_sk);

  RLWEGadgetCT(const RLWEGadgetCT& other);

  RLWEGadgetCT& operator=(const RLWEGadgetCT other);

  void init(std::vector<std::unique_ptr<RLWECT>> &gadget_ct, std::vector<std::unique_ptr<RLWECT>> &gadget_ct_sk);
   
  void mul(VectorCT *out, const VectorCT *ct);
   
    template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(cereal::base_class<GadgetVectorCT>(this));   
        ar(rlwe_param, gadget, array_eval_a, array_eval_b, array_eval_a_sk, array_eval_b_sk);     
    }
        
    template <class Archive>
    void load( Archive & ar )
    {    
        ar(cereal::base_class<GadgetVectorCT>(this));   
        ar(rlwe_param, gadget, array_eval_a, array_eval_b, array_eval_a_sk, array_eval_b_sk);  
        //this->out_minus = RLWECT(rlwe_param);  
        this->decomp_poly_array_eval_form = std::shared_ptr<PolynomialArrayEvalForm>(rlwe_param->mul_engine->init_polynomial_array_eval_form(gadget->digits));
        init_gadget_decomp_tables();    
        this->is_init = true;  
    } 
  
  private:

  /// @brief Temporary variable which stores the evaluation form of a decomposed polynomial. Used in Multiplication, initialized in init.
  std::shared_ptr<PolynomialArrayEvalForm> decomp_poly_array_eval_form;
  
  void init_gadget_decomp_tables();
  
};
  
class RLWESK{

    public:

    std::shared_ptr<RLWEParam> param; 
    KeyDistribution key_type; 
    Polynomial sk_poly; 
    std::unique_ptr<PolynomialEvalForm> sk_poly_eval; 
    bool is_init = false;  
    std::shared_ptr<Distribution> unif_dist;
    std::shared_ptr<Distribution> error_dist; 
    double noise_stddev;
  
    RLWESK() = default;
  
    RLWESK(std::shared_ptr<RLWEParam> param, KeyDistribution key_type, double noise_stddev); 
  
    RLWESK(const RLWESK &other);

    RLWESK& operator=(const RLWESK other);
  
    void encrypt(RLWECT *out, Polynomial *m);  
    
    RLWECT* encrypt(Polynomial *m); 
    
    RLWECT* encode_and_encrypt(Polynomial* m, PlaintextEncoding encoding);
 
    void partial_decrypt(Polynomial *phase, RLWECT *ct);
  
    Polynomial* decrypt(RLWECT *ct, PlaintextEncoding encoding);
  
    void decrypt(Polynomial *out, RLWECT *ct, PlaintextEncoding encoding);
 
    void extract_lwe_key(long* lwe_key);

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

class RLWEGadgetSK : public GadgetVectorCTSK{

    public:
  
    std::shared_ptr<Gadget> gadget;
    std::shared_ptr<RLWESK> rlwe_sk;

    RLWEGadgetSK() = default;

    RLWEGadgetSK(std::shared_ptr<Gadget> gadget, std::shared_ptr<RLWESK> rlwe_sk);

    RLWEGadgetSK(const RLWEGadgetSK &other);

    RLWEGadgetSK& operator=(const RLWEGadgetSK other);
       
    GadgetVectorCT* gadget_encrypt(Polynomial *msg); 

    GadgetVectorCT* gadget_encrypt(long *msg, int size); 
 
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(cereal::base_class<GadgetVectorCTSK>(this));     
      ar(gadget, rlwe_sk);   
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(cereal::base_class<GadgetVectorCTSK>(this));     
      ar(gadget, rlwe_sk);   
    } 
};
 
}

CEREAL_REGISTER_TYPE(fhe_deck::RLWEParam)
CEREAL_REGISTER_TYPE(fhe_deck::RLWECT)
CEREAL_REGISTER_TYPE(fhe_deck::RLWEGadgetCT)
CEREAL_REGISTER_TYPE(fhe_deck::RLWEGadgetSK)
 
 
#endif