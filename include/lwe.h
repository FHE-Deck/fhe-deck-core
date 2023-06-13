 
#ifndef LWE_H
#define LWE_H

#include <random>
#include <iostream>
#include "lwe_param.h"  
#include "utils.h"

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>


namespace fhe_deck{

class LWESK {
 
    public:  
    std::shared_ptr<LWEParam> param;
 
    Sampler rand; 
    long *s;
    bool is_init = false;
  
    ~LWESK();

    LWESK();

    LWESK(int n, long Q, double stddev, KeyDistribution key_d);

    LWESK(std::shared_ptr<LWEParam> lwe_par);

    LWESK(std::shared_ptr<LWEParam> lwe_par, long* key);
 
    LWESK(const LWESK &other);

    LWESK& operator=(const LWESK other);

    LWEParam get_lwe_param();
   
    long* encrypt(long m);
    
    LWECT encrypt_ct(long m);

    void encrypt(long* ct, long m);
    
    long* scale_and_encrypt(long m, int t);
    
    void scale_and_encrypt(long* ct, long m, int t);


    long phase(long *ct);
    
    long error(long *ct, long m);
    
    long decrypt(long *ct,  int t); 
 
    LWESK modulus_switch(long new_modulus);

    
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


class LWEGadgetSK{

  public:
    LWEGadgetParam gadget_param;
    LWESK lwe;

    LWEGadgetSK();

    LWEGadgetSK(LWEGadgetParam lwe_g_par, LWESK lwe);
  
    LWEGadgetSK(const LWEGadgetSK& other);

    LWEGadgetSK& operator=(const LWEGadgetSK other);
 
    // Secret Gadget
    long** gadget_encrypt(long m);
    // Secret Gadget
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

}

#endif