
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
 
    int N; 
    double stddev;
    long Q;

    
    RingType ring;
    // Is this even used somewhere now? 
    ModulusType mod_type;
    
    KeyDistribution key_type;

    PolynomialArithmetic arithmetic = ntl;

    std::shared_ptr<PolynomialMultiplicationEngine> mul_engine;
    bool is_mul_engine_init = false;

    // TODO: Should contain a pointer to default Polynomail multiplication engine
    
    RLWEParam() = default; 
       
    RLWEParam(RingType ring, int N, long Q, KeyDistribution key_type, ModulusType mod_type, double stddev, PolynomialArithmetic arithmetic);

    RLWEParam(int N, long Q, KeyDistribution key_type, ModulusType mod_type, double stddev, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine);
   
    RLWEParam(RLWEParam &c);

    RLWEParam& operator=(RLWEParam other);
     
    //long* init_poly();

    Polynomial init_poly();

    //long* init_zero_poly();

    Polynomial init_zero_poly();
   
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(ring, N, stddev, Q, mod_type, key_type, arithmetic);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(ring, N, stddev, Q, mod_type, key_type, arithmetic);   
    } 


  private:
    void init_mul_engine();

};


class RLWECT{

    public:
  
    std::shared_ptr<RLWEParam> param;

    // Polynomials b, and a s.t. b = a*s + e + M, where e and M are the error and message respectively, a nd s is the secret key polynomial
    //long *b;
    //long *a; 
    Polynomial a;
    Polynomial b;
   
    bool is_init = false;

    bool is_engine_set = false;
    
    // Pointer to default polynomial multiplication engine should be in params.
    // But we should also give a pointer here, with the option to change the pointer.
    // At default we can use the engine form params, but If I wanna have a special 
    // case where each RLWECT has a separate engine then I should be able to have it.

    FFTPlan engine; 
  
    intel::hexl::NTT ntt; 
 
    ~RLWECT();
  
    RLWECT() = default;

    RLWECT(std::shared_ptr<RLWEParam> param);

    //RLWECT(std::shared_ptr<RLWEParam> param, long *b, long *a);

    RLWECT(const RLWECT &other);
   
    RLWECT& operator=(const RLWECT other);
  
    void negacyclic_rotate(RLWECT *out, int rot);

    void add(RLWECT *out,  RLWECT *ct);

    //void add(RLWECT *out, long* x);

    void add(RLWECT *out, Polynomial *x);

    void sub(RLWECT *out, RLWECT *ct);

    //void sub(RLWECT *out, long* x); 

    void sub(RLWECT *out, Polynomial *x); 

    //void mul(RLWECT *out, long *x);

    void mul(RLWECT *out, Polynomial *x);

    void neg(RLWECT *out);

    void extract_lwe(long *lwe_ct_out);

    LWECT extract_lwe(std::shared_ptr<LWEParam> lwe_par);
 
    std::string to_string();
    
    void set_computing_engine();
  
  template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(param);  
        for(int i = 0; i < this->param->N; ++i){
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
        for(int i = 0; i < this->param->N; ++i){
          ar(a.coefs[i]);
          ar(b.coefs[i]);
        }
        set_computing_engine(); 
        is_init = true;
    } 


   private:
 
    void add(long *out, long *in_1, long *in_2);

    long* add(long *in_1, long *in_2);

    void sub(long *out, long *in_1, long *in_2);

    long* sub(long *in_1, long *in_2);

    void neg(long *out, long *in);

    long* neg(long *in); 

    void mul(long *out, long *in_1, long *in_2);

    void mul_fft(long *out, long *in_1, long *in_2);

    void mul_ntt(long *out, long *in_1, long *in_2);
  
};


enum GadgetMulMode {simul, deter};



class RLWEGadgetParam{

  public:
  
  std::shared_ptr<RLWEParam> rlwe_param;

  // Q = basis**ell
  int ell;
  // basis = 2**k
  int k;
  int basis; 
 
  int ell_any;
  int k_any;
  int basis_any;

  int ell_max;
  int w;
  int w_any;
  

  // These gadget objects should be in the Gadget Ciphertext instead of the parameters
  Gadget deter_gadget;
  Gadget rand_gadget;

  RLWEGadgetParam() = default;
    
  RLWEGadgetParam(std::shared_ptr<RLWEParam> rlwe_param, int basis, Gadget &deter_gadget, Gadget &rand_gadget);
 
  RLWEGadgetParam(const RLWEGadgetParam &other);
 
  RLWEGadgetParam& operator=(const RLWEGadgetParam other);
  
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(rlwe_param, deter_gadget, rand_gadget);    
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(rlwe_param, deter_gadget, rand_gadget);  
      setup_the_other_parametrs(); 
    } 
 
    private:

    void setup_the_other_parametrs();
   
};


class RLWEGadgetCT{

  public:

  // TODO Should be a pointer
  std::shared_ptr<RLWEGadgetParam> gadget_param;
 
  // Pointer to default polynomial multiplication engine should be in gadget_param->rlwe_params
  // But we should also give a pointer here, with the option to change the pointer.
  // At default we can use the engine form params, but If I wanna have a special 
  // Case where each RLWEGadgetCT has a separate engine to speed up concurency or something then I should be able to have it.
 
  bool is_init = false;
  // Extended RLWE of a message M
  //RLWECT *gadget_ct;
  // Extended RLWE of a mesage M * sk with where sk is the secret key polynomial. 
  //RLWECT *gadget_ct_sk;

  std::vector<RLWECT> gadget_ct;
  std::vector<RLWECT> gadget_ct_sk;

  PolynomialArrayEvalForm array_eval_a;
  PolynomialArrayEvalForm array_eval_b;
  PolynomialArrayEvalForm array_eval_a_sk;
  PolynomialArrayEvalForm array_eval_b_sk;

 

  // Ciphertext polynomials if we're using FFT engine
  FFTPlan engine;
  fftw_complex **eval_a;
  fftw_complex **eval_b;

  fftw_complex **eval_a_sk;
  fftw_complex **eval_b_sk;
 
  // Ciphertext polynomials if we're using NTT engine
  intel::hexl::NTT ntt; 
  long **ntt_eval_a;
  long **ntt_eval_b;

  long **ntt_eval_a_sk;
  long **ntt_eval_b_sk;


  // Temorary arrays for gadget decomposition.
  // The polynomial pointer will point at a table of polynomials, 
  // where each polynomial's coefs pointer will point at the polynomial in the 2D long table.
  // TODO: This is a temporary solution. Certainly we need to rewrite this to a 1D table.  
  long** simul_ct_a_dec;
  long** simul_ct_b_dec;
  long** deter_ct_a_dec;
  long** deter_ct_b_dec; 

  PolynomialArrayCoefForm simul_ct_a_dec_poly;
  PolynomialArrayCoefForm simul_ct_b_dec_poly;
  PolynomialArrayCoefForm deter_ct_a_dec_poly;
  PolynomialArrayCoefForm deter_ct_b_dec_poly;
 

  // Mask for power of two modulus reduction
  long mask;
 
  RLWEGadgetCT() = default;
 

  RLWEGadgetCT(std::shared_ptr<RLWEGadgetParam> gadget_param, std::vector<RLWECT> gadget_ct, std::vector<RLWECT> gadget_ct_sk);

  ~RLWEGadgetCT();

  RLWEGadgetCT(const RLWEGadgetCT& other);

  RLWEGadgetCT& operator=(const RLWEGadgetCT other);

  void init();
 
  void mul(RLWECT *out, const RLWECT *ct, GadgetMulMode mode);
 
  void multisum_fft_test(long *out, long** arr, fftw_complex **c_arr, int ell, int w, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2);

  void multisum_fft(long *out, long** arr, fftw_complex **c_arr, int ell, int w);

  void multisum_any_fft(long *out, long** arr, fftw_complex **c_arr);

  void multisum_ntt_test(long *out, long** arr, long **c_arr, int ell, int w, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2);

  void multisum_ntt(long *out, long** arr, long **c_arr, int ell, int w);

  void multisum_any_ntt(long *out, long** arr, long **c_arr);
  
  void to_eval();

  void to_coef();

 
    template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(gadget_param);    
        for(int i = 0; i < gadget_param->ell_max; ++i){
            ar(gadget_ct[i]);
            ar(gadget_ct_sk[i]);
        }   
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
        ar(gadget_param);   
        gadget_ct = new RLWECT[gadget_param->ell_max];
        gadget_ct_sk = new RLWECT[gadget_param->ell_max]; 
        for(int i = 0; i < gadget_param->ell_max; ++i){
            ar(gadget_ct[i]); 
            ar(gadget_ct_sk[i]); 
        }   

        out_minus = RLWECT(gadget_param->rlwe_param);
        set_computing_engine();
        if(gadget_param->rlwe_param->arithmetic == double_fft){
            init_fft_eval();
        }else if(gadget_param->rlwe_param->arithmetic == hexl_ntt){ 
            init_ntt_eval(); 
        }else{ 
            std::cout << "Arithmetic Currently Not Supported" << std::endl;
        }
        this->to_eval();
        this->is_init = true;
    } 
 
 
  private:

  // Temporary variable needed for multiplication. Its initialized in already in the constructors because initialization is expensive
  RLWECT out_minus;

  // Temporary arrays for ntt multiplication
  long *ntt_multisum_eval;
  long *ntt_prod;

  // Temporary arrays for fft multiplication
  fftw_complex *fft_multisum_eval;
  fftw_complex *fft_prod;   
 
  void set_computing_engine();

  void init_gadget_decomp_tables();

  void set_gadget_decomp_arrays();

  bool is_complex_arry_eq(fftw_complex* in_1, fftw_complex* in_2, int size);

  std::string complex_to_string(fftw_complex* in, int size);
 
  void verify_eval_forms();

  void init_fft_eval();

  void delete_fft_eval();

  void init_ntt_eval();

  void delete_ntt_eval();

  void to_eval_fft();

  void to_coef_fft();

  void to_eval_ntt();

  void to_coef_ntt();

  void mod_reduce(long *out_poly, long *in_poly);

  void mod_reduce(long *out_poly, long double *in_poly_l);

};
  

 

class RLWESK{

    public:

    std::shared_ptr<RLWEParam> param;
    long *s; 
    Polynomial sk;

    bool is_init = false; 
 
    std::shared_ptr<Distribution> unif_dist;
    std::shared_ptr<Distribution> error_dist;
    std::shared_ptr<Distribution> sk_dist;


    intel::hexl::NTT ntt; 
    bool is_ntt_init = false;
    long *eval_s_ntt;
 
    FFTPlan engine; 
    bool is_fft_init = false;
    fftw_complex *eval_s;
    

    ~RLWESK();

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
        for(int i = 0; i < param->N; ++i){
            s_arr.push_back(s[i]);
        }
        ar(param,   s_arr);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      std::vector<long> s_arr;
      ar(param,   s_arr);   
      this->s = new long[param->N];
      for(int i = 0; i < param->N; ++i){
        this->s[i] = s_arr[i];
      }  
    }  
};


class RLWEGadgetSK{

    public:
 
    std::shared_ptr<RLWEGadgetParam> gadget_param; 

    // TODO: This should be a smart pointer! No need to duplicate!
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