 
#ifndef LWE_PARAM_H
#define LWE_PARAM_H

#include "sample.h" 
#include "utils.h" 
#include "enums.h"
//#include "ciphertext.h" 

 
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>

class lwe_param{

  public:  

  int n;
  long Q; 

  // TODO: Actually key_d and stddev should be rather in secret key params
  key_dist key_d;
  double stddev;

  lwe_param();
 
  lwe_param(int n, long Q, key_dist key_d, double stddev); 
   
    long* init_ct();
 
    void scalar_mul(long *out, long *ct, long scalar);

    void scalar_mul_lazy(long *out, long *ct, long scalar);

    void add(long *out, long *ct_1, long *ct_2);

    void add_lazy(long *out, long *ct_1, long *ct_2); 

    lwe_param modulus_switch(long new_modulus);

    void switch_modulus(long *out_ct, long *in_ct, lwe_param &new_param);

 
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(n, Q);
      ar(key_d, stddev); 
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(n, Q);
      ar(key_d, stddev );
      
    } 
  
};

class lwe_ct{
 
  public:
 
    lwe_param lwe_par;

    bool init = false;
 
    long *ct;

    lwe_ct() = default;

    // Initializes the ciphertext with zeros (the actual initialization will be done in some encrypt)
    lwe_ct(lwe_param lwe_par);

    lwe_ct(lwe_param lwe_par, long* ct);

    lwe_ct(const lwe_ct &c);
 
    lwe_ct(lwe_ct &c);

    lwe_ct(lwe_ct *c);
   

    ~lwe_ct();

    lwe_ct& operator=(const lwe_ct other);
   
    void scalar_mul(long scalar);
    
    void scalar_mul_lazy(long scalar);
 
    void mul(long b);
    
    void add(lwe_ct *ct);
 
    void sub(lwe_ct *ct);
    
    void add_lazy(lwe_ct *ct); 
    
    void switch_modulus(lwe_param &new_param);
  
    void add(long b);
  
    void sub(long b);
   
    lwe_ct operator+(long b);

    lwe_ct operator+(lwe_ct ct);

    lwe_ct operator+(lwe_ct *ct);

    lwe_ct operator-(long b);

    lwe_ct operator-(lwe_ct ct);

    lwe_ct operator-(lwe_ct *ct);

    lwe_ct operator-();
    
    lwe_ct operator*(long b);  



    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(lwe_par); 

      std::vector<long> ct_arr; 
      for(int i = 0; i < lwe_par.n; ++i){
        ct_arr.push_back(ct[i]);
      }
      ar(ct_arr) ;
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(lwe_par);
      std::vector<long> ct_arr;
      ar(ct_arr);
      ct = new long[lwe_par.n];
      for(int i = 0; i < lwe_par.n; ++i){
        ct[i] = ct_arr[i];
      }
    } 


};


lwe_ct operator+(long b, lwe_ct ct);

lwe_ct operator-(long b, lwe_ct ct);

lwe_ct operator*(long b, lwe_ct ct);


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