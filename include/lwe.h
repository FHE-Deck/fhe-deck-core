/*
PLEASE DO NOT DISTRIBUTE!!! This version is for review only. 
*/


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
    sample rand; 
    long *s;
  
    lwe_sk();

    lwe_sk(int n, long Q, double stddev, key_dist key_d);

    lwe_sk(lwe_param lwe_par);

    lwe_sk(lwe_param lwe_par, long* key);

    lwe_param get_lwe_param();

    // Secret
    // void init_binary_key();
    // Secret
    // void init_ternary_key();

    // Secret
    long* encrypt(long m);
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

};


class lwe_gadget_sk{

  public:
    lwe_gadget_param lwe_g_par;
    lwe_sk lwe;

    lwe_gadget_sk();

    lwe_gadget_sk(lwe_gadget_param lwe_g_par, lwe_sk lwe);
  
    // Secret Gadget
    long** gadget_encrypt(long m);
    // Secret Gadget
    void gadget_encrypt(long** gadget_ct, long m);
    
  
};



#endif