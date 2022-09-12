/*
PLEASE DO NOT DISTRIBUTE!!! This version is for review only. 
*/


#ifndef NTRU_PARAM_H
#define NTRU_PARAM_H

#include "enums.h"
#include "sample.h"
#include "utils.h"
#include "fft_plan.h" 

#include "hexl/hexl.hpp"


class ntru_param{

  public:
 
    ring_type ring;
    int N; 
    double stddev;
    long Q; 

    fft_plan *engine;
    sample rand;

    ~ntru_param();
    
    ntru_param(); 

    ntru_param(ring_type ring, int N, long Q,  double stddev);

    ntru_param(ring_type ring, int N, long Q,  double stddev, bool long_arithmetic);
    
    ntru_param mod_switch(long new_modulus);

    // These are used to initialize messages (perhaps we should also encapsulate messages in a class?)
    // Not sure actually
    long* init_poly();

    long* init_zero_poly();

    fftw_complex* init_fft_poly();

    fftwl_complex* init_fft_poly_l(); 
};

 

class ntru_ct{

    public:

    ntru_param param;
    long *c; 
    bool init = false;

    ntru_ct();

    ntru_ct(ntru_param &param);

    ntru_ct(ntru_param &param, long *c);

    ntru_ct(const ntru_ct &other);
  
    ~ntru_ct();

    ntru_ct& operator=(const ntru_ct other);
    
    // This algs should overload +, -, sub, (although or now we can leave it)
 
    ntru_ct negacyclic_rotate(int rot);

    ntru_ct add(const ntru_ct *ct);

    ntru_ct sub(const ntru_ct *ct);

    ntru_ct neg();

    ntru_ct mod_switch(long new_modulus);

    ntru_ct mod_switch(ntru_param new_param);
 
    std::string to_string();

   private:

    void add(long *out, long *in_1, long *in_2);
  
    void sub(long *out, long *in_1, long *in_2);
  
    void neg(long *out, long *in);
  
};

 
class ntru_gadget_param{

  public:
    ntru_param param;
    int ell;
    int k;
    int basis; 

    polynomial_arithmetic arithmetic;

    ntru_gadget_param();
    
    ntru_gadget_param(ntru_param &ntru_par, int basis, polynomial_arithmetic arithmetic);

}; 


class ntru_gadget_ct{

  public:

  ntru_param param;

  long **gadget_ct;

  long **gadget_ct_ntt_eval;

  fftw_complex **gadget_ct_eval;

  fftwl_complex **gadget_ct_eval_l;

  polynomial_arithmetic arithmetic;

  intel::hexl::NTT ntt; 

  bool init = false;

  // TODO: Of course this gadget param have to be changed after we write the gadget class
    int ell;
    int k;
    int basis; 
    
  ~ntru_gadget_ct();

  ntru_gadget_ct();
    
  ntru_gadget_ct(ntru_param &ntru_par, int basis, polynomial_arithmetic arithmetic);
     
  ntru_gadget_ct(const ntru_gadget_ct &other);

  ntru_gadget_ct& operator=(const ntru_gadget_ct other);
   
  void init_gadget_ct();

  void init_gadget_ct_fft();

  void init_gadget_ct_fft_l();

  void init_gadget_ct_ntt();

    void delete_gadget_ct(long** ct);

    void delete_gadget_ct_fft(fftw_complex** ct);

    void delete_gadget_ct_fft(fftwl_complex** ct); 

  
    // Public Gadget 
    void gadget_mul(ntru_ct *out, ntru_ct *c_1);
 
    void gadget_mul(ntru_ct *out, long *scalar);

    void gadget_mul(long *out, long *c_1);
 
    void to_eval();

    // Public Gadget
    void gadget_mul_fft(long *out, long *c_1, fftw_complex **c_2);
    //void gadget_mul_fft(long *out, ntru_ct *c_1, fftw_complex **c_2);

    void gadget_mul_fft(long *out, long *c_1, fftwl_complex **c_2);
    //void gadget_mul_fft(long *out, ntru_ct *c_1, fftwl_complex **c_2);
    
    void gadget_mul_hexl_ntt(long *out, long *ct_1, long **c_2);
 
    void to_coef();

 
};

 

#endif