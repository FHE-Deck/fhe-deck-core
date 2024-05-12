 
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
#include "vector_ciphertext.h"
#include "gadget.h"
 
namespace fhe_deck{



class NTRUParam : public VectorCTParam{

  public: 
    long coef_modulus; 

    RingType ring;
    ModulusType mod_type;   
    PolynomialArithmetic arithmetic = ntl;

    std::shared_ptr<PolynomialMultiplicationEngine> mul_engine;
    bool is_mul_engine_init = false;
 
    NTRUParam() = default; 
       
    NTRUParam(RingType ring, int ring_degree, long coef_modulus, ModulusType mod_type, PolynomialArithmetic arithmetic);

    NTRUParam(int ring_degree, long coef_modulus, ModulusType mod_type, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine);
   
    NTRUParam(NTRUParam &c);

    NTRUParam& operator=(NTRUParam other);

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
 
class NTRUCT : public VectorCT{

    public:
  
    std::shared_ptr<NTRUParam> param;  
    Polynomial ct_poly; 
    NTRUCT() = default;

    NTRUCT(std::shared_ptr<NTRUParam> param);
 
    NTRUCT(const NTRUCT &other);
   
    NTRUCT& operator=(NTRUCT other);
  
    void negacyclic_rotate(NTRUCT *out, int rot);

    void cyclic_rotate(NTRUCT *out, int rot);

    void homomorphic_rotate(VectorCT *out, int rot);

    void add(VectorCT *out,  VectorCT *ct);
 
    void add(NTRUCT *out, Polynomial *x);

    void sub(VectorCT *out, VectorCT *ct);
 
    void sub(NTRUCT *out, Polynomial *x); 
 
    void mul(NTRUCT *out, Polynomial *x);

    void neg(VectorCT *out);
 
    void extract_lwe(LWECT *out);
 
    std::string to_string();
    
  template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(param);   
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
        ar(param);   
    }  
};

class NTRUSK{

    public:

    std::shared_ptr<NTRUParam> param;   
    Polynomial sk; 
    Polynomial inv_sk; 
    bool is_init = false;   
    std::shared_ptr<Distribution> error_dist;
    std::shared_ptr<Distribution> sk_dist;
    double noise_stddev;
  
    NTRUSK() = default;
  
    NTRUSK(std::shared_ptr<NTRUParam> param, double noise_stddev); 
 
    /// NOTE: Depends on NTL need to init a Inversion Engine for that. 
    void key_gen();
  
    NTRUSK(const NTRUSK &other);

    NTRUSK& operator=(const NTRUSK other);
  
    void encrypt(NTRUCT *out, Polynomial *m);
 
    NTRUCT encrypt(Polynomial *m); 

    NTRUCT encode_and_encrypt(Polynomial* m, PlaintextEncoding encoding);
 
    void partial_decrypt(Polynomial *phase, NTRUCT *ct);
 
    Polynomial decrypt(NTRUCT *ct, PlaintextEncoding encoding);
 
    void decrypt(Polynomial *out, NTRUCT *ct, PlaintextEncoding encoding);
  
    // Encrypts msg * inv_f. 
    NTRUCT kdm_encrypt(Polynomial* msg); 
    // Encrypts msg * inv_f.  
    void kdm_encrypt(NTRUCT *ct_out, Polynomial* msg);
    // Encrypts msg * inv_f. 
    void kdm_encode_and_encrypt(NTRUCT *ct_out, Polynomial* msg, PlaintextEncoding encoding);
    // Encrypts msg * inv_f.  
    NTRUCT kdm_encode_and_encrypt(Polynomial* msg, PlaintextEncoding encoding);
  
    LWESK* extract_lwe_key();
 
    template <class Archive>
    void save( Archive & ar ) const
    { 
        std::vector<long> s_arr; 
        for(int i = 0; i < param->size; ++i){
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

  
class NTRUGadgetCT : public GadgetVectorCT{ 

  public:
  
  std::shared_ptr<NTRUParam> ntru_param;
  std::shared_ptr<Gadget> gadget;

  bool is_init = false;  
  PolynomialArrayEvalForm array_eval_a;  
   
  long** deter_ct_a_dec; 
  PolynomialArrayCoefForm deter_ct_a_dec_poly; 
   
  ~NTRUGadgetCT();

  NTRUGadgetCT() = default;
   
  NTRUGadgetCT(std::shared_ptr<NTRUParam> ntru_param, std::shared_ptr<Gadget> gadget, std::vector<NTRUCT> &gadget_ct);

  NTRUGadgetCT(const NTRUGadgetCT& other);

  NTRUGadgetCT& operator=(const NTRUGadgetCT other);

  void init(std::vector<NTRUCT> &gadget_ct);
   
  void mul(VectorCT *out, const VectorCT *ct);
   
    template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(ntru_param, gadget);     
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
        ar(ntru_param, gadget);      
        this->is_init = true;
    } 
  
  private:
  
  void init_gadget_decomp_tables();

  void set_gadget_decomp_arrays();
  
};
   
class NTRUGadgetSK : public GadgetVectorCTSK{

    public:
  
    std::shared_ptr<Gadget> gadget;
    std::shared_ptr<NTRUSK> sk;

    NTRUGadgetSK() = default;

    NTRUGadgetSK(std::shared_ptr<Gadget> gadget, std::shared_ptr<NTRUSK> sk);

    NTRUGadgetSK(const NTRUGadgetSK &other);

    NTRUGadgetSK& operator=(const NTRUGadgetSK other);
        
    GadgetVectorCT* gadget_encrypt(Polynomial *msg); 

    GadgetVectorCT* gadget_encrypt(long *msg, int size); 

    GadgetVectorCT* kdm_gadget_encrypt(Polynomial *msg); 

    GadgetVectorCT* kdm_gadget_encrypt(long *msg, int size); 
 
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(gadget, sk);   
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(gadget, sk);   
    } 
};
 
} /// End of namespace fhe_deck

#endif