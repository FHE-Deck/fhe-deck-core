

#ifndef RLWE_PARAM_H
#define RLWE_PARAM_H

#include "enums.h"
#include "sample.h"
#include "fft_plan.h"
#include "gadget.h"


class rlwe_param{

  public:
 
    ring_type ring;
    int N;
    sampler rand;
    double stddev;
    long Q;
    modulus_type mod_type;
    key_dist key_type;

    polynomial_arithmetic arithmetic = ntl;

    // TODO: Perhaps we should have a separate engine in each gadget ciphertext for example?
    // Not sure. Need to think about it. 
    // TODO: Also if arithmetic is not FFT but NTT or NTL then we don't need to initialize this at all
    fft_plan *engine;
    //bool init = false;
  
    intel::hexl::NTT ntt; 

    long mask;

    ~rlwe_param(); 

    rlwe_param(); 
     
    //rlwe_param(ring_type ring, int N, long Q, key_dist key_type, modulus_type mod_type, double stddev);

    //rlwe_param(ring_type ring, int N, long Q, key_dist key_type, modulus_type mod_type, double stddev, bool long_arithmetic = false);

    rlwe_param(ring_type ring, int N, long Q, key_dist key_type, modulus_type mod_type, double stddev, polynomial_arithmetic arithmetic);
       
    rlwe_param(const rlwe_param &c);

    rlwe_param& operator=(const rlwe_param other);
   
    void set_computing_engine();

    long* init_poly();

    long* init_zero_poly();

  // These FFT poly perhaps should be initialized by fft_plan?
    fftw_complex* init_fft_poly();

    fftwl_complex* init_fft_poly_l();


    
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(ring, N, stddev, Q, mod_type, key_type, arithmetic);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(ring, N, stddev, Q, mod_type, key_type, arithmetic);  
      set_computing_engine(); 
    } 


};


class rlwe_ct{

    public:
 

    rlwe_param *param;
    long *b;
    long *a;

    long mask;

    bool init = false;
  
    rlwe_ct();

    rlwe_ct(rlwe_param *param);

    rlwe_ct(rlwe_param *param, long *b, long *a);
  
    ~rlwe_ct();

    rlwe_ct& operator=(const rlwe_ct other);
  
    void negacyclic_rotate(rlwe_ct *out, int rot);

    void add(rlwe_ct *out, const rlwe_ct *ct);

    void add(rlwe_ct *out, long* x);

    void sub(rlwe_ct *out, const rlwe_ct *ct);

    void sub(rlwe_ct *out, long* x); 

    void mul(rlwe_ct *out, long *x);

    void neg(rlwe_ct *out);
 
    std::string to_string();




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


enum gadget_mul_mode {simul, deter};



class rlwe_gadget_param{

  public:

  //polynomial_arithmetic arithmetic;

  rlwe_param param;
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
  
  gadget deter_gadget;
  gadget rand_gadget;

  rlwe_gadget_param();
   
   
  rlwe_gadget_param(rlwe_param &rlwe_par, int basis, gadget &deter_gadget, gadget &rand_gadget);


  
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(param, deter_gadget, rand_gadget);    
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(param, deter_gadget, rand_gadget);  
         
    } 
  

};


class rlwe_gadget_ct{

  public:

  rlwe_gadget_param gadget_param;

  rlwe_ct *gadget_ct;
  rlwe_ct *gadget_ct_sk;
 
  fftw_complex **eval_a;
  fftw_complex **eval_b;

  fftw_complex **eval_a_sk;
  fftw_complex **eval_b_sk;
 

  intel::hexl::NTT ntt; 
  long **ntt_eval_a;
  long **ntt_eval_b;

  long **ntt_eval_a_sk;
  long **ntt_eval_b_sk;

 
  
  // Mask for power of two modulus reduction
  long mask;

  bool init = false;

  rlwe_gadget_ct();

  rlwe_gadget_ct(rlwe_gadget_param gadget_param);

  ~rlwe_gadget_ct();

  rlwe_gadget_ct(const rlwe_gadget_ct& other);

  rlwe_gadget_ct& operator=(const rlwe_gadget_ct other);


  void mul(rlwe_ct *out, const rlwe_ct *ct, gadget_mul_mode mode);
 
  void multisum_fft(long *out, long** arr, fftw_complex **c_arr, int ell, int w);

  void multisum_any_fft(long *out, long** arr, fftw_complex **c_arr);

  void multisum_ntt(long *out, long** arr, long **c_arr, int ell, int w);

  void multisum_any_ntt(long *out, long** arr, long **c_arr);
   
  void to_eval();

  void to_coef();
 
 


 
  private:

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
  

#endif