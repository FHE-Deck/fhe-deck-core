 
#ifndef LWE_PARAM_H
#define LWE_PARAM_H

#include "sample.h" 
#include "utils.h" 
#include "enums.h"

class lwe_param{

  public:  

  int n;
  long Q; 
  key_dist key_d;
  double stddev;

  lwe_param();
 
  lwe_param(int n, long Q, key_dist key_d, double stddev); 
  
  // Public
  long* init_ct();


    // Public
    void scalar_mul(long *out, long *ct, long scalar);
    // Public
    void scalar_mul_lazy(long *out, long *ct, long scalar);
    // Public
    void add(long *out, long *ct_1, long *ct_2);
    // Public
    void add_lazy(long *out, long *ct_1, long *ct_2); 
    // Public
    lwe_param modulus_switch(long new_modulus);
    // Public
    void switch_modulus(long *out_ct, long *in_ct, lwe_param &new_param);
 
};


class lwe_gadget_param{

  public:
    int basis;
    int ell;
    int k;
    lwe_param lwe_par;

    lwe_gadget_param();

    lwe_gadget_param(lwe_param lwe_par, int basis);

    long** init_gadget_ct(); 

  // Public Gadget
    void gadget_mul(long *out_ct, long** gadget_ct, long scalar);
    // Public Gadget
    void gadget_mul_lazy(long *out_ct, long** gadget_ct, long scalar);
  
};

 

#endif