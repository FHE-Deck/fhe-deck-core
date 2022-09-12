

#ifndef RLWE_PARAM_H
#define RLWE_PARAM_H

#include "enums.h"
#include "sample.h"
#include "fft_plan.h"



class rlwe_param{

  public:
 
    ring_type ring;
    int N;
    sample rand;
    double stddev;
    long Q;
    modulus_type mod_type;
    key_dist key_type;

    fft_plan *engine;
    bool init = false;
  
    long mask;

    ~rlwe_param(); 

    rlwe_param(); 
     
    rlwe_param(ring_type ring, int N, long Q, key_dist key_type, modulus_type mod_type, double stddev);

    rlwe_param(ring_type ring, int N, long Q, key_dist key_type, modulus_type mod_type, double stddev, bool long_arithmetic);
       
    long* init_poly();

    long* init_zero_poly();

    fftw_complex* init_fft_poly();

    fftwl_complex* init_fft_poly_l();

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

    void sub(rlwe_ct *out, const rlwe_ct *ct);

    void neg(rlwe_ct *out);
 
    std::string to_string();

   private:

    void add(long *out, long *in_1, long *in_2);

    long* add(long *in_1, long *in_2);

    void sub(long *out, long *in_1, long *in_2);

    long* sub(long *in_1, long *in_2);

    void neg(long *out, long *in);

    long* neg(long *in);
  
};


enum gadget_mul_mode {simul, signed_decomp};

class rlwe_gadget_param{

  public:
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

  // Standard deviation for the gaussian sampling algorithm (for randomized gadget decomposition) when mode = simul
  // We will set it always to basis * 4.5. It should be basis * omega(sqrt(log N)), but for practical N, 
  // 4.5 upperbounds sqrt(log N). E.g. math.sqrt(20) approx 4.47, but we will never use a ring of size N = 2**20. 
  // According to [MP12] stddev should be basis * omega(sqrt(log N)) for the special case where Q = basis**(ell)
  double stddev_simul;

  // parameters for binomial distribution 
  long n_binom;
  long n_binom_half;
  double p_binom;
  sample gadget_rand;

  rlwe_gadget_param();
    
  rlwe_gadget_param(rlwe_param &rlwe_par, int basis, double stddev_simul);
   
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

  bool eval = false;
  
  // Mask for power of two modulus reduction
  long mask;

  bool init = false;

  rlwe_gadget_ct();

  rlwe_gadget_ct(rlwe_gadget_param gadget_param);

  ~rlwe_gadget_ct();

  rlwe_gadget_ct& operator=(const rlwe_gadget_ct other);


  void mul(rlwe_ct *out, const rlwe_ct *ct, gadget_mul_mode mode);
 
  void multisum(long *out, long** arr, fftw_complex **c_arr);

  void multisum_any(long *out, long** arr, fftw_complex **c_arr);
   
  void to_eval();

  void to_coef();

  // TODO: Acutally, this should be private, but I need to test it separately
  // Also, for now, only this class uses the method, 
  //but it makes perfect sense for future to have a separate class with gadgets
  long** gaussian_sample(long *in);
 
 
  private:

    long** decompose(long *in);
 
   //void gadget_mul_fft(long* out, long *c_1, fftw_complex **c_2);

   //void gadget_mul_fft(long* out, long *c_1, fftwl_complex **c_2);
  
    void mod_reduce(long *out_poly, long *in_poly);

    void mod_reduce(long *out_poly, long double *in_poly_l);

};






#endif