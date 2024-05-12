
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
 
    RLWEParam() = default; 
       
    RLWEParam(RingType ring, int ring_degree, long coef_modulus, ModulusType mod_type, PolynomialArithmetic arithmetic);

    RLWEParam(int ring_degree, long coef_modulus, ModulusType mod_type, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine);
   
    RLWEParam(RLWEParam &c);

    RLWEParam& operator=(RLWEParam other);

    VectorCT* init_ct();
      
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(ring, size, coef_modulus, mod_type, arithmetic);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(ring, size, coef_modulus, mod_type, arithmetic);   
    } 
 
  private:
    void init_mul_engine(); 
};

class RLWECT : public VectorCT{

  public:
  
    std::shared_ptr<RLWEParam> param; 
    // Polynomials b, and a s.t. b = a*s + e + M, where e and M are the error and message respectively, and s is the secret key polynomial
    /// TODO: should those be smart pointers? 
    Polynomial a;
    Polynomial b; 
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
        ar(param);  
        for(int i = 0; i < this->param->size; ++i){
          ar(a.coefs[i]);
          ar(b.coefs[i]);
        }  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
        ar(param);    
        a = *new Polynomial(param->size, param->coef_modulus, param->mul_engine); 
        b = *new Polynomial(param->size, param->coef_modulus, param->mul_engine); 
        for(int i = 0; i < this->param->size; ++i){
          ar(a.coefs[i]);
          ar(b.coefs[i]);
        } 
    }  
};
  
  
class RLWEGadgetCT : public GadgetVectorCT{ 

  public:
  
  std::shared_ptr<RLWEParam> rlwe_param;
  std::shared_ptr<Gadget> gadget;

  bool is_init = false;  
  PolynomialArrayEvalForm array_eval_a;
  PolynomialArrayEvalForm array_eval_b;
  PolynomialArrayEvalForm array_eval_a_sk;
  PolynomialArrayEvalForm array_eval_b_sk;
   
  long** deter_ct_a_dec;
  long** deter_ct_b_dec;  
  PolynomialArrayCoefForm deter_ct_a_dec_poly;
  PolynomialArrayCoefForm deter_ct_b_dec_poly;
   
  ~RLWEGadgetCT();

  RLWEGadgetCT() = default;
   
  RLWEGadgetCT(std::shared_ptr<RLWEParam> rlwe_param, std::shared_ptr<Gadget> gadget, std::vector<RLWECT> &gadget_ct, std::vector<RLWECT> &gadget_ct_sk);

  RLWEGadgetCT(const RLWEGadgetCT& other);

  RLWEGadgetCT& operator=(const RLWEGadgetCT other);

  void init(std::vector<RLWECT> &gadget_ct, std::vector<RLWECT> &gadget_ct_sk);
   
  void mul(VectorCT *out, const VectorCT *ct);
   
    template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(rlwe_param, gadget);     
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
        ar(rlwe_param, gadget);      
        this->is_init = true;
    } 
  
  private:

  // Temporary variable needed for multiplication. Its initialized in already in the constructors.
  RLWECT out_minus;
  
  void init_gadget_decomp_tables();

  void set_gadget_decomp_arrays();
  
};
  
class RLWESK{

    public:

    std::shared_ptr<RLWEParam> param; 
    KeyDistribution key_type; 
    Polynomial sk_poly; 
    bool is_init = false;  
    std::shared_ptr<Distribution> unif_dist;
    std::shared_ptr<Distribution> error_dist;
    std::shared_ptr<Distribution> sk_dist;
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
        std::vector<long> s_arr; 
        for(int i = 0; i < param->size; ++i){
            s_arr.push_back(this->sk_poly.coefs[i]);
        }
        ar(param, s_arr);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      std::vector<long> s_arr;
      ar(param, s_arr);    
    }  
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
      ar(gadget, rlwe_sk);   
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(gadget, rlwe_sk);   
    } 
};
 
}

#endif