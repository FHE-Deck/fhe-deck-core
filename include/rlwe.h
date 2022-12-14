
#ifndef RLWE_H
#define RLWE_H

#include "rlwe_param.h"


class rlwe_sk{

    public:
    rlwe_param param;
    long *s; 
    polynomial_arithmetic arithmetic;

    intel::hexl::NTT ntt; 
    fftw_complex *eval_s;
    long *eval_s_ntt;

    rlwe_sk();
 

    rlwe_sk(rlwe_param param, polynomial_arithmetic arithmetic);

    rlwe_sk(rlwe_param param, long *s, polynomial_arithmetic arithmetic);
  
    rlwe_ct encrypt(long* m);

    rlwe_ct scale_and_encrypt(long* m, int t);

    // Uses SK
    void phase(long *phase, const rlwe_ct *ct);
    // Uses SK
    long* decrypt(const rlwe_ct *ct, int t);
    // Uses SK
    void decrypt(long *out, const rlwe_ct *ct, int t);

    void set_arithmetic_specific_variables();

};


class gadget_rlwe_sk{

    public:

    rlwe_gadget_param gadget_param; 
    rlwe_sk sk;

    gadget_rlwe_sk();

    gadget_rlwe_sk(const gadget_rlwe_sk &other);

    gadget_rlwe_sk(rlwe_gadget_param gadget_param, rlwe_sk sk);

    // Outputs a rlwe_gadget_ct: encryptions of msg * 2**i and msg * sk * 2**i
    rlwe_gadget_ct gadget_encrypt(long* msg);
  
    // Outputs encryptions of msg * 2**i
    void extended_encrypt(long** out, long* msg); 
};

#endif