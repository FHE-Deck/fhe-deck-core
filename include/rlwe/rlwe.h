
#ifndef RLWE_H
#define RLWE_H

#include "rlwe_param.h"


namespace fhe_deck{

class RLWESK{

    public:
    std::shared_ptr<RLWEParam> param;
    long *s; 
    bool is_init = false;
    PolynomialArithmetic sk_arithmetic;

    Sampler rand;

    intel::hexl::NTT ntt; 
    bool is_ntt_init = false;
    long *eval_s_ntt;


    FFTPlan engine; 
    bool is_fft_init = false;
    fftw_complex *eval_s;
    

    ~RLWESK();

    RLWESK() = default;
  
    RLWESK(std::shared_ptr<RLWEParam> param, PolynomialArithmetic sk_arithmetic); 

    RLWESK(std::shared_ptr<RLWEParam> param, long *s, PolynomialArithmetic sk_arithmetic);

    RLWESK(const RLWESK &other);

    RLWESK& operator=(const RLWESK other);


    RLWECT encrypt(long* m);

    RLWECT scale_and_encrypt(long* m, int t);

    // Uses SK
    void phase(long *phase, const RLWECT *ct);
    // Uses SK
    long* decrypt(const RLWECT *ct, int t);
    // Uses SK
    void decrypt(long *out, const RLWECT *ct, int t);

    void set_arithmetic_specific_variables();
 
    
    template <class Archive>
    void save( Archive & ar ) const
    { 
        std::vector<long> s_arr; 
        for(int i = 0; i < param->N; ++i){
            s_arr.push_back(s[i]);
        }
        ar(param, sk_arithmetic, s_arr);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      std::vector<long> s_arr;
      ar(param, sk_arithmetic, s_arr);   
      this->s = new long[param->N];
      for(int i = 0; i < param->N; ++i){
        this->s[i] = s_arr[i];
      } 
      set_arithmetic_specific_variables(); 
    }  
};


class RLWEGadgetSK{

    public:

    RLWEGadgetParam gadget_param; 
    RLWESK sk;

    RLWEGadgetSK() = default;

    RLWEGadgetSK(RLWEGadgetParam gadget_param, RLWESK sk);

    RLWEGadgetSK(const RLWEGadgetSK &other);

    RLWEGadgetSK& operator=(const RLWEGadgetSK other);

    // Outputs a rlwe_gadget_ct: encryptions of msg * 2**i and msg * sk * 2**i
    RLWEGadgetCT gadget_encrypt(long* msg);
  
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

}

#endif