 
#ifndef LWE_PARAM_H
#define LWE_PARAM_H

#include "sample.h" 
#include "utils.h" 
#include "enums.h"
//#include "ciphertext.h" 
 
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>


namespace fhe_deck{

class LWEParam{

  public:  

  int n;
  long Q; 

  // TODO: Actually key_d and stddev should be rather in secret key params
  KeyDistribution key_d;
  double stddev;

  LWEParam() = default;
 
  LWEParam(int n, long Q, KeyDistribution key_d, double stddev); 
   
    long* init_ct();
 
    void scalar_mul(long *out, long *ct, long scalar);

    void scalar_mul_lazy(long *out, long *ct, long scalar);

    void add(long *out, long *ct_1, long *ct_2);

    void add_lazy(long *out, long *ct_1, long *ct_2); 

    LWEParam modulus_switch(long new_modulus);

    void switch_modulus(long *out_ct, long *in_ct, LWEParam &new_param);

    void switch_modulus(long *out_ct, long *in_ct, std::shared_ptr<LWEParam> new_param);
 
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
      ar(key_d, stddev);
      
    } 
  
};


class LWECT{
 
  public:
 
    std::shared_ptr<LWEParam> param;

    bool init = false;
 
    long *ct;

    LWECT() = default;

    // Initializes the ciphertext with zeros (the actual initialization will be done in some encrypt)
    LWECT(std::shared_ptr<LWEParam> lwe_par);

    LWECT(std::shared_ptr<LWEParam> lwe_par, long* ct);

    LWECT(const LWECT &c);
 
    LWECT(LWECT &c);

    LWECT(LWECT *c); 

    ~LWECT();

    LWECT& operator=(const LWECT other);
   
    void scalar_mul(long scalar);
    
    void scalar_mul_lazy(long scalar);
 
    void mul(long b);
    
    void add(LWECT *ct);
 
    void sub(LWECT *ct);
    
    void add_lazy(LWECT *ct); 
    
    //void switch_modulus(LWEParam &new_param);
  
    void add(long b);
  
    void sub(long b);
   
    LWECT operator+(long b);

    LWECT operator+(LWECT ct);

    LWECT operator+(LWECT *ct);

    LWECT operator-(long b);

    LWECT operator-(LWECT ct);

    LWECT operator-(LWECT *ct);

    LWECT operator-();
    
    LWECT operator*(long b);  



    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(param); 

      std::vector<long> ct_arr; 
      for(int i = 0; i < param->n+1; ++i){
        ct_arr.push_back(ct[i]);
      }
      ar(ct_arr) ;
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(param);
      std::vector<long> ct_arr;
      ar(ct_arr);
      ct = new long[param->n+1];
      for(int i = 0; i < param->n+1; ++i){
        ct[i] = ct_arr[i];
      }
      this->init = true;
    } 


};


LWECT operator+(long b, LWECT ct);

LWECT operator-(long b, LWECT ct);

LWECT operator*(long b, LWECT ct);



class LWEModSwitcher{

  public:
  std::shared_ptr<LWEParam> from;
  std::shared_ptr<LWEParam> to;

  bool long_arithmetic = false;

  // Some precomputation
  int ct_size;
  double Q_from;
  double Q_to;
  double temp; 
  // If we need larger precision
  long double long_Q_from;
  long double long_Q_to;
  long double long_temp; 

  LWEModSwitcher() = default;

  // Initializes the ciphertext with zeros (the actual initialization will be done in some encrypt)
  LWEModSwitcher(std::shared_ptr<LWEParam> from, std::shared_ptr<LWEParam> to);
  
  void switch_modulus(long *out_ct, long *in_ct);
    
};



/*
class LWEToLWEKeySwitchKey{

  public:

    long ***ksk;
    std::shared_ptr<LWEParam> origin;
    // To
    LWEGadgetParam destination;
    KeySwitchType ks_type;


    LWEToLWEKeySwitchKey();

 
    // KS
    void lwe_to_lwe_key_switch_lazy(long *lwe_ct_out, long *lwe_ct_in);
    // KS
    void lwe_to_lwe_key_switch_partial_lazy(long *lwe_ct_out, long *lwe_ct_in);
    // KS
    void lwe_to_lwe_key_switch(long *lwe_ct_out, long *lwe_ct_in);
    // KS
    void set_key_switch_type();

    //key_switching_key_gen(LWEGadgetSK *sk);

};
*/




class LWEGadgetParam{

  public:
    int basis;
    int ell;
    int k;
    std::shared_ptr<LWEParam> lwe_param;

    LWEGadgetParam() = default;

    LWEGadgetParam(std::shared_ptr<LWEParam> lwe_par, int basis);

    long** init_gadget_ct(); 

  // Public Gadget
    void gadget_mul(long *out_ct, long** gadget_ct, long scalar);
    // Public Gadget
    void gadget_mul_lazy(long *out_ct, long** gadget_ct, long scalar);
   
  
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(lwe_param, basis, ell, k);
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(lwe_param, basis, ell, k);
    } 
 
};

}
 
#endif