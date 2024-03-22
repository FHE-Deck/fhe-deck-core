 
#ifndef LWE_H
#define LWE_H

#include <random>
#include <iostream> 
#include "utils.h"

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
 
    // TODO: This is handled by a LWECT
    void scalar_mul(long *out, long *ct, long scalar);
    // TODO: This is handled by a LWECT
    void scalar_mul_lazy(long *out, long *ct, long scalar);
    // TODO: This is handled by a LWECT
    void add(long *out, long *ct_1, long *ct_2);
    // TODO: This is handled by a LWECT
    void add_lazy(long *out, long *ct_1, long *ct_2); 

    LWEParam modulus_switch(long new_modulus);

    // TODO: This is handled by a LWEModSwitcher
    void switch_modulus(long *out_ct, long *in_ct, LWEParam &new_param);
    // TODO: This is handled by a LWEModSwitcher
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

 


class LWESK {
 
    public:  
    std::shared_ptr<LWEParam> param;
  
    std::shared_ptr<Distribution> unif_dist;
    std::shared_ptr<Distribution> error_dist;
    std::shared_ptr<Distribution> sk_dist;

    long *s;
    bool is_init = false;
  
    ~LWESK();

    LWESK();

    LWESK(int n, long Q, double stddev, KeyDistribution key_d);

    LWESK(std::shared_ptr<LWEParam> lwe_par);
  
    LWESK(std::shared_ptr<LWEParam> lwe_par, long* key);
 
    LWESK(const LWESK &other);

    LWESK& operator=(const LWESK other);

    std::shared_ptr<LWEParam> get_lwe_param();
   
    long* encrypt(long m);
    
    LWECT encrypt_ct(long m);

    void encrypt(long* ct, long m);
    
    long* scale_and_encrypt(long m, int t);
    
    void scale_and_encrypt(long* ct, long m, int t);
 
    long phase(long *ct);
    
    long error(long *ct, long m);

    // NOTE: Decryption only makes sense with respect to a Plaintext encoding.   
    long decrypt(long *ct,  int t); 
 
    std::shared_ptr<LWESK> modulus_switch(long new_modulus);
 
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(param);  
      std::vector<long> s_arr; 
      for(int i = 0; i < param->n; ++i){
        s_arr.push_back(s[i]);
      }
      ar(s_arr) ;
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(param);
      std::vector<long> s_arr;
      ar(s_arr);
      this->s = new long[param->n];
      for(int i = 0; i < param->n; ++i){
        this->s[i] = s_arr[i];
      } 
    } 

};

 




class LWEGadgetParam{

  public:
    int basis;
    int ell;
    int k;
    std::shared_ptr<LWEParam> lwe_param;

    LWEGadgetParam() = default;

    LWEGadgetParam(std::shared_ptr<LWEParam> lwe_par, int basis);

    long** init_gadget_ct(); 

    void gadget_mul(long *out_ct, long** gadget_ct, long scalar);
    
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


 


class LWEGadgetSK{

  public:
    LWEGadgetParam gadget_param;
    std::shared_ptr<LWESK> lwe;

    LWEGadgetSK();

    LWEGadgetSK(LWEGadgetParam lwe_g_par, std::shared_ptr<LWESK> lwe);
  
    LWEGadgetSK(const LWEGadgetSK& other);

    LWEGadgetSK& operator=(const LWEGadgetSK other);
  
    long** gadget_encrypt(long m); 

    void gadget_encrypt(long** gadget_ct, long m);
 
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(gadget_param, lwe);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(gadget_param, lwe);  
    }    
};





class LWEPublicKey{

  public:
 
    /*
      TODO Change this stddev stuff to uniform.
      Gaussian here doens't make much sense.
    */
    double stddev; 
    Sampler rand_masking;
  
    long **public_key;
    int size; 

    std::shared_ptr<LWEParam> param;

    ~LWEPublicKey();

    LWEPublicKey(std::shared_ptr<LWESK> lwe_sk, int key_size, double stddev);

    LWEPublicKey(const LWEPublicKey &other);
   
    LWEPublicKey& operator=(const LWEPublicKey other);
 
    void mask_ciphertext(long *ct);

    LWECT encrypt(long message);

    LWECT ciphertext_of_zero();
 
};


 



}

#endif