
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


#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
 
namespace fhe_deck{
 
class RLWEParam{

  public:
 
    int degree; 
    long coef_modulus;
    // TODO: stddev is actually irrelevant to public RLWEParameters. Its only releveant to RLWESK. Maybe delete it from here? 
    double stddev;

    RingType ring;
    // Is this even used somewhere now? 
    ModulusType mod_type;  
    KeyDistribution key_type; 
    PolynomialArithmetic arithmetic = ntl;

    std::shared_ptr<PolynomialMultiplicationEngine> mul_engine;
    bool is_mul_engine_init = false;
 
    RLWEParam() = default; 
       
    RLWEParam(RingType ring, int degree, long coef_modulus, KeyDistribution key_type, ModulusType mod_type, double stddev, PolynomialArithmetic arithmetic);

    RLWEParam(int degree, long coef_modulus, KeyDistribution key_type, ModulusType mod_type, double stddev, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine);
   
    RLWEParam(RLWEParam &c);

    RLWEParam& operator=(RLWEParam other);
       
    Polynomial init_poly();
 
    Polynomial init_zero_poly();
   
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(ring, degree, stddev, coef_modulus, mod_type, key_type, arithmetic);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(ring, degree, stddev, coef_modulus, mod_type, key_type, arithmetic);   
    } 
 
  private:
    void init_mul_engine(); 
};


class RLWECT{

    public:
  
    std::shared_ptr<RLWEParam> param; 
    // Polynomials b, and a s.t. b = a*s + e + M, where e and M are the error and message respectively, a nd s is the secret key polynomial
    Polynomial a;
    Polynomial b; 
    RLWECT() = default;

    RLWECT(std::shared_ptr<RLWEParam> param);
 
    RLWECT(const RLWECT &other);
   
    RLWECT& operator=(RLWECT other);
  
    void negacyclic_rotate(RLWECT *out, int rot);

    void add(RLWECT *out,  RLWECT *ct);
 
    void add(RLWECT *out, Polynomial *x);

    void sub(RLWECT *out, RLWECT *ct);
 
    void sub(RLWECT *out, Polynomial *x); 
 
    void mul(RLWECT *out, Polynomial *x);

    void neg(RLWECT *out);

    void extract_lwe(long *lwe_ct_out);

    LWECT extract_lwe(std::shared_ptr<LWEParam> lwe_par);
 
    std::string to_string();
    
  template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(param);  
        for(int i = 0; i < this->param->degree; ++i){
          ar(a.coefs[i]);
          ar(b.coefs[i]);
        }  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
        ar(param);    
        a = this->param->init_poly();
        b = this->param->init_poly(); 
        for(int i = 0; i < this->param->degree; ++i){
          ar(a.coefs[i]);
          ar(b.coefs[i]);
        } 
    } 
 
};


enum GadgetMulMode {simul, deter};



class RLWEGadgetParam{

  public:
  
  std::shared_ptr<RLWEParam> rlwe_param;
   
  std::shared_ptr<Gadget> deter_gadget; 

  RLWEGadgetParam() = default;
       
  RLWEGadgetParam(std::shared_ptr<RLWEParam> rlwe_param, int basis, std::shared_ptr<Gadget> deter_gadget);
 
  RLWEGadgetParam(const RLWEGadgetParam &other);
 
  RLWEGadgetParam& operator=(const RLWEGadgetParam other);
  
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(rlwe_param, deter_gadget);    
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(rlwe_param, deter_gadget);   
    }  
};
 
class RLWEGadgetCT{

  public:
 
  std::shared_ptr<RLWEGadgetParam> gadget_param; 
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
   
  RLWEGadgetCT(std::shared_ptr<RLWEGadgetParam> gadget_param, std::vector<RLWECT> &gadget_ct, std::vector<RLWECT> &gadget_ct_sk);

  RLWEGadgetCT(const RLWEGadgetCT& other);

  RLWEGadgetCT& operator=(const RLWEGadgetCT other);

  void init(std::vector<RLWECT> &gadget_ct, std::vector<RLWECT> &gadget_ct_sk);
   
  void mul(RLWECT *out, const RLWECT *ct);
   
    template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(gadget_param);     
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
        ar(gadget_param);     
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
    Polynomial sk; 
    bool is_init = false;  
    std::shared_ptr<Distribution> unif_dist;
    std::shared_ptr<Distribution> error_dist;
    std::shared_ptr<Distribution> sk_dist;
  
    RLWESK() = default;
  
    RLWESK(std::shared_ptr<RLWEParam> param); 
  
    RLWESK(const RLWESK &other);

    RLWESK& operator=(const RLWESK other);
  
    void encrypt(RLWECT *out, Polynomial *m);

    RLWECT encrypt(Polynomial *m);
 
    RLWECT scale_and_encrypt(Polynomial* m, int t);

    // Uses SK
    void phase(Polynomial *phase, RLWECT *ct);

    // Uses SK
    Polynomial decrypt(RLWECT *ct, int t);

    // Uses SK
    void decrypt(Polynomial *out, RLWECT *ct, int t);
 
    void extract_lwe_key(long* lwe_key);
    
    template <class Archive>
    void save( Archive & ar ) const
    { 
        std::vector<long> s_arr; 
        for(int i = 0; i < param->degree; ++i){
            s_arr.push_back(this->sk.coefs[i]);
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


class RLWEGadgetSK{

    public:
 
    std::shared_ptr<RLWEGadgetParam> gadget_param;  
    std::shared_ptr<RLWESK> sk;

    RLWEGadgetSK() = default;

    RLWEGadgetSK(std::shared_ptr<RLWEGadgetParam> gadget_param, std::shared_ptr<RLWESK> sk);

    RLWEGadgetSK(const RLWEGadgetSK &other);

    RLWEGadgetSK& operator=(const RLWEGadgetSK other);
    
    RLWEGadgetCT gadget_encrypt(long* msg); 
 
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(gadget_param, sk);   
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(gadget_param, sk);   
    } 
};




}

#endif