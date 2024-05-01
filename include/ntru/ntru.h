 
#ifndef NTRU_H
#define NTRU_H

#include <NTL/ZZX.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_p.h>
#include <complex>
#include "sample.h"
#include "utils.h"
#include "ntru_param.h"
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
       
    Polynomial init_poly();
 
    Polynomial init_zero_poly();
   
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

/// TODO: Implement
class NTRUCT : public VectorCT{

    public:
  
    std::shared_ptr<NTRUParam> param; 
    // Polynomials c 
    Polynomial c; 
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

    void extract_lwe(long *lwe_ct_out);

    LWECT extract_lwe(std::shared_ptr<LWEParam> lwe_par);
 
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


/// TODO: Implement
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

    /// TODO: the procedures below simply encrypt msg * inv_f, instead of just msg.
    // So just use the encrypt procedure. 

    // Encrypts msg * inv_f. Doesn't scale the message! 
    NTRUCT kdm_encrypt(Polynomial* msg); 
    // Encrypts msg * inv_f. Doesn't scale the message!
    void kdm_encrypt(NTRUCT *ct_out, Polynomial* msg);
    // Encrypts msg * inv_f. 
    void kdm_encode_and_encrypt(NTRUCT *ct_out, Polynomial* msg, PlaintextEncoding encoding);
    // Encrypts msg * inv_f.  
    NTRUCT kdm_encode_and_encrypt(Polynomial* msg, PlaintextEncoding encoding);
 
    void extract_lwe_key(long* lwe_key);

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
 
  /// std::shared_ptr<GadgetVectorCTParam> gadget_param; 
  std::shared_ptr<NTRUParam> ntru_param;
  std::shared_ptr<Gadget> gadget;

  bool is_init = false;  
  PolynomialArrayEvalForm array_eval_a;
  //PolynomialArrayEvalForm array_eval_b;
  PolynomialArrayEvalForm array_eval_a_sk;
  //PolynomialArrayEvalForm array_eval_b_sk;
   
  long** deter_ct_a_dec;
  //long** deter_ct_b_dec;  
  PolynomialArrayCoefForm deter_ct_a_dec_poly;
  //PolynomialArrayCoefForm deter_ct_b_dec_poly;
   
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
  
 
/// TODO: Implement
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















class ntru_sk {
  
  public:

    ntru_param param;
    long *f;
    long *inv_f; 

    bool modulus_switched = false;
    ntru_param higher_mod_param;

    ~ntru_sk();

    ntru_sk();

    // The construtor chooses ternary secret keys
    ntru_sk(ntru_param param);

    // The construtor takes key from the outside
    ntru_sk(ntru_param param, long *f, long *inv_f);

    // The construtor takes key from the outside, setd the modulus switched flag, and the higher_mod_param
    // This is used only when creating a ntru_sk instance by modulus switching
    ntru_sk(ntru_param param, long *f, long *inv_f, ntru_param higher_mod_param);
 
    ntru_sk& operator=(const ntru_sk other);

    // TODO These should go to sample
    static void ternary_poly(NTL::ZZ_pX &temp_f, ntru_param &param);

    static void gaussian_poly(NTL::ZZ_pX &temp_f, ntru_param &param);

    // Generates SK
    void key_gen();

    // Generates SK
    void static key_gen(long *f, long *inv_f, ntru_param &param);
   
    ntru_ct encrypt(long* msg);

    void encrypt(ntru_ct *ct_out, long* msg); 

    // Just as encrypt but perfoms computation via NTL
    void naive_encrypt(ntru_ct *ct_out, long* msg);

    // Encrypts msg * inv_f. Doesn't scale the message! 
    ntru_ct kdm_encrypt(long* msg);

    // Encrypts msg * inv_f. Doesn't scale the message!
    void kdm_encrypt(ntru_ct *ct_out, long* msg);
    // Encrypts msg * inv_f. Scales the message (so message should be mod t)
    void kdm_scale_and_encrypt(ntru_ct *ct_out, long* msg, int t);
    // Encrypts msg * inv_f. Scales the message (so message should be mod t) 
    ntru_ct kdm_scale_and_encrypt(long* msg, int t);

    // Uses SK
    //void phase(long *phase, long *ct);
    void phase(long *phase, ntru_ct *ct);

    void error(long *err, ntru_ct *ct, long* msg);

    // Uses SK 
    long* decrypt(ntru_ct *ct, int t);
    // Uses SK 
    void decrypt(long *out, ntru_ct *ct, int t);
 
    // Uses SK 
    long decrypt_coef(ntru_ct *ct, int t);

    // Change name to switch_modulus
    ntru_sk mod_switch(long new_modulus);
  
};


class gadget_ntru{
 
  public: 

    ntru_gadget_param gadget_param;

    ntru_sk ntru;

    gadget_ntru();

    gadget_ntru(ntru_gadget_param gadget_param, ntru_sk ntru);
   
    ntru_gadget_ct gadget_encrypt(long* msg); 
 
    void gadget_encrypt(long** out, long* msg); 

};

}

#endif