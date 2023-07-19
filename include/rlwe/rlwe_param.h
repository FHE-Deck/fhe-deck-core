

#ifndef RLWE_PARAM_H
#define RLWE_PARAM_H

#include "enums.h"
#include "sample.h"
#include "fft_plan.h"
#include "gadget.h"
#include "hexl/hexl.hpp"

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>


namespace fhe_deck{

class RLWEParam{

  public:
 
    RingType ring;
    int N;
    //sampler rand;
    double stddev;
    long Q;
    ModulusType mod_type;
    KeyDistribution key_type;

    PolynomialArithmetic arithmetic = ntl;
    
    RLWEParam() = default; 
       
    RLWEParam(RingType ring, int N, long Q, KeyDistribution key_type, ModulusType mod_type, double stddev, PolynomialArithmetic arithmetic);
       
    RLWEParam(const RLWEParam &c);

    RLWEParam& operator=(const RLWEParam other);
     
    long* init_poly();

    long* init_zero_poly();
   
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


};


class RLWECT{

    public:
  
    std::shared_ptr<RLWEParam> param;

    long *b;
    long *a;
   
    bool is_init = false;

    bool is_engine_set = false;
    
    FFTPlan engine; 
  
    intel::hexl::NTT ntt; 


    ~RLWECT();
  
    RLWECT() = default;

    RLWECT(std::shared_ptr<RLWEParam> param);

    RLWECT(std::shared_ptr<RLWEParam> param, long *b, long *a);

    RLWECT(const RLWECT &other);
  

    RLWECT& operator=(const RLWECT other);
  
    void negacyclic_rotate(RLWECT *out, int rot);

    void add(RLWECT *out, const RLWECT *ct);

    void add(RLWECT *out, long* x);

    void sub(RLWECT *out, const RLWECT *ct);

    void sub(RLWECT *out, long* x); 

    void mul(RLWECT *out, long *x);

    void neg(RLWECT *out);
 
    std::string to_string();
    
    void set_computing_engine();
  
  template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(param);  
        for(int i = 0; i < this->param->N; ++i){
          ar(a[i]);
          ar(b[i]);
        }  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
        ar(param);    
        a = this->param->init_poly();
        b = this->param->init_poly(); 
        for(int i = 0; i < this->param->N; ++i){
          ar(a[i]);
          ar(b[i]);
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
    
  RLWEGadgetParam(std::shared_ptr<RLWEParam> rlwe_par, int basis, Gadget &deter_gadget, Gadget &rand_gadget);
 
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

  RLWEGadgetParam gadget_param;

  bool is_init = false;
  RLWECT *gadget_ct;
  RLWECT *gadget_ct_sk;

  FFTPlan engine;
  fftw_complex **eval_a;
  fftw_complex **eval_b;

  fftw_complex **eval_a_sk;
  fftw_complex **eval_b_sk;
 

  intel::hexl::NTT ntt; 
  long **ntt_eval_a;
  long **ntt_eval_b;

  long **ntt_eval_a_sk;
  long **ntt_eval_b_sk;


  // Temorary arrays for gadget decomposition
  long** simul_ct_a_dec;
  long** simul_ct_b_dec;
  long** deter_ct_a_dec;
  long** deter_ct_b_dec;

  
  // Mask for power of two modulus reduction
  long mask;
 
  RLWEGadgetCT() = default;

  RLWEGadgetCT(RLWEGadgetParam gadget_param);

  ~RLWEGadgetCT();

  RLWEGadgetCT(const RLWEGadgetCT& other);

  RLWEGadgetCT& operator=(const RLWEGadgetCT other);
 
  void mul(RLWECT *out, const RLWECT *ct, GadgetMulMode mode);
 
  void multisum_fft(long *out, long** arr, fftw_complex **c_arr, int ell, int w);

  void multisum_any_fft(long *out, long** arr, fftw_complex **c_arr);

  void multisum_ntt(long *out, long** arr, long **c_arr, int ell, int w);

  void multisum_any_ntt(long *out, long** arr, long **c_arr);
   
  void to_eval();

  void to_coef();

 
    template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(gadget_param);    
        for(int i = 0; i < gadget_param.ell_max; ++i){
            ar(gadget_ct[i]);
            ar(gadget_ct_sk[i]);
        }   
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
        ar(gadget_param);   
        gadget_ct = new RLWECT[gadget_param.ell_max];
        gadget_ct_sk = new RLWECT[gadget_param.ell_max]; 
        for(int i = 0; i < gadget_param.ell_max; ++i){
            ar(gadget_ct[i]); 
            ar(gadget_ct_sk[i]); 
        }   

        out_minus = RLWECT(gadget_param.rlwe_param);
        set_computing_engine();
        if(gadget_param.rlwe_param->arithmetic == double_fft){
            init_fft_eval();
        }else if(gadget_param.rlwe_param->arithmetic == hexl_ntt){ 
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
  

}

#endif