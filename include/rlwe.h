
#ifndef RLWE_H
#define RLWE_H

#include "rlwe_param.h"


class rlwe_sk{

    public:
    rlwe_param param;
    long *s; 
    bool is_init = false;
    polynomial_arithmetic sk_arithmetic;

    intel::hexl::NTT ntt; 

    bool is_fft_init = false;
    fftw_complex *eval_s;
    
    bool is_ntt_init = false;
    long *eval_s_ntt;

    ~rlwe_sk();

    rlwe_sk() = default;
  
    rlwe_sk(rlwe_param param, polynomial_arithmetic sk_arithmetic); 

    rlwe_sk(rlwe_param param, long *s, polynomial_arithmetic sk_arithmetic);

    rlwe_sk(const rlwe_sk &other);

    rlwe_sk& operator=(const rlwe_sk other);


    rlwe_ct encrypt(long* m);

    rlwe_ct scale_and_encrypt(long* m, int t);

    // Uses SK
    void phase(long *phase, const rlwe_ct *ct);
    // Uses SK
    long* decrypt(const rlwe_ct *ct, int t);
    // Uses SK
    void decrypt(long *out, const rlwe_ct *ct, int t);

    void set_arithmetic_specific_variables();
 
    
    template <class Archive>
    void save( Archive & ar ) const
    { 
        std::vector<long> s_arr; 
        for(int i = 0; i < param.N; ++i){
            s_arr.push_back(s[i]);
        }
        ar(param, sk_arithmetic, s_arr);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
        std::vector<long> s_arr;
      ar(param, sk_arithmetic, s_arr);  
      sk_arithmetic = sk_arithmetic;  
      this->s = new long[param.N];
      for(int i = 0; i < param.N; ++i){
        this->s[i] = s_arr[i];
      } 
      set_arithmetic_specific_variables(); 
    }  
};


class gadget_rlwe_sk{

    public:

    rlwe_gadget_param gadget_param; 
    rlwe_sk sk;

    gadget_rlwe_sk() = default;

    gadget_rlwe_sk(rlwe_gadget_param gadget_param, rlwe_sk sk);

    gadget_rlwe_sk(const gadget_rlwe_sk &other);

    gadget_rlwe_sk& operator=(const gadget_rlwe_sk other);

    // Outputs a rlwe_gadget_ct: encryptions of msg * 2**i and msg * sk * 2**i
    rlwe_gadget_ct gadget_encrypt(long* msg);
  
    // Outputs encryptions of msg * 2**i
    void extended_encrypt(long** out, long* msg); 
 
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(gadget_param, sk);   
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(gadget_param, sk);   
    } 
};

#endif