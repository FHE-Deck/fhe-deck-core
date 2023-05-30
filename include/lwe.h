 
#ifndef LWE_H
#define LWE_H

#include <random>
#include <iostream>
#include "lwe_param.h"  
#include "utils.h"

class lwe_sk {
 
    public:  
    lwe_param lwe_par;

    // This is all secret  
    sampler rand; 
    long *s;
    bool is_init = false;
  
    ~lwe_sk();

    lwe_sk();

    lwe_sk(int n, long Q, double stddev, key_dist key_d);

    lwe_sk(lwe_param lwe_par);

    lwe_sk(lwe_param lwe_par, long* key);
 
    lwe_sk(const lwe_sk &other);

    lwe_sk& operator=(const lwe_sk other);

    lwe_param get_lwe_param();
   
    long* encrypt(long m);
    
    lwe_ct encrypt_ct(long m);

    // Secret
    void encrypt(long* ct, long m);


    // Secret
    long* scale_and_encrypt(long m, int t);
    // Secret
    void scale_and_encrypt(long* ct, long m, int t);

    // Secret
    long phase(long *ct);
    // Secret 
    long error(long *ct, long m);
    // Secret
    long decrypt(long *ct,  int t); 

    // Public
    lwe_sk modulus_switch(long new_modulus);



    
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(lwe_par);  
      std::vector<long> s_arr; 
      for(int i = 0; i < lwe_par.n; ++i){
        s_arr.push_back(s[i]);
      }
      ar(s_arr) ;
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(lwe_par);
      std::vector<long> s_arr;
      ar(s_arr);
      this->s = new long[lwe_par.n];
      for(int i = 0; i < lwe_par.n; ++i){
        this->s[i] = s_arr[i];
      } 
    } 

};


class lwe_gadget_sk{

  public:
    lwe_gadget_param lwe_g_par;
    lwe_sk lwe;

    lwe_gadget_sk();

    lwe_gadget_sk(lwe_gadget_param lwe_g_par, lwe_sk lwe);
  
    lwe_gadget_sk(const lwe_gadget_sk& other);

    lwe_gadget_sk& operator=(const lwe_gadget_sk other);
 
    // Secret Gadget
    long** gadget_encrypt(long m);
    // Secret Gadget
    void gadget_encrypt(long** gadget_ct, long m);


    
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(lwe_g_par, lwe);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(lwe_g_par, lwe);  
    }   
  
};



#endif