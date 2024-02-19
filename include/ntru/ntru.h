 
#ifndef NTRU_H
#define NTRU_H

#include <NTL/ZZX.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_p.h>
#include <complex>
#include "sample.h"
#include "utils.h"
#include "ntru_param.h"
#include "fft_plan.h"
 
namespace fhe_deck{

class ntru_sk {
  
  public:

    ntru_param param;
    long *f;
    long *inv_f; 

    bool modulus_switched = false;
    ntru_param higher_mod_param;

    ~ntru_sk();

    ntru_sk();

    // The construtor chooses ternary secret keys
    ntru_sk(ntru_param param);

    // The construtor takes key from the outside
    ntru_sk(ntru_param param, long *f, long *inv_f);

    // The construtor takes key from the outside, setd the modulus switched flag, and the higher_mod_param
    // This is used only when creating a ntru_sk instance by modulus switching
    ntru_sk(ntru_param param, long *f, long *inv_f, ntru_param higher_mod_param);
 
    ntru_sk& operator=(const ntru_sk other);

    // TODO These should go to sample
    static void ternary_poly(NTL::ZZ_pX &temp_f, ntru_param &param);

    static void gaussian_poly(NTL::ZZ_pX &temp_f, ntru_param &param);

    // Generates SK
    void key_gen();

    // Generates SK
    void static key_gen(long *f, long *inv_f, ntru_param &param);
   
    ntru_ct encrypt(long* msg);

    void encrypt(ntru_ct *ct_out, long* msg);

    // Just as encrypt but perfoms computation via NTL
    void naive_encrypt(ntru_ct *ct_out, long* msg);

    // Encrypts msg * inv_f. Doesn't scale the message! 
    ntru_ct kdm_encrypt(long* msg);

    // Encrypts msg * inv_f. Doesn't scale the message!
    void kdm_encrypt(ntru_ct *ct_out, long* msg);
    // Encrypts msg * inv_f. Scales the message (so message should be mod t)
    void kdm_scale_and_encrypt(ntru_ct *ct_out, long* msg, int t);
    // Encrypts msg * inv_f. Scales the message (so message should be mod t) 
    ntru_ct kdm_scale_and_encrypt(long* msg, int t);

    // Uses SK
    //void phase(long *phase, long *ct);
    void phase(long *phase, ntru_ct *ct);

    void error(long *err, ntru_ct *ct, long* msg);

    // Uses SK 
    long* decrypt(ntru_ct *ct, int t);
    // Uses SK 
    void decrypt(long *out, ntru_ct *ct, int t);
 
    // Uses SK 
    long decrypt_coef(ntru_ct *ct, int t);

    // Change name to switch_modulus
    ntru_sk mod_switch(long new_modulus);
  
};


class gadget_ntru{
 
  public: 

    ntru_gadget_param gadget_param;

    ntru_sk ntru;

    gadget_ntru();

    gadget_ntru(ntru_gadget_param gadget_param, ntru_sk ntru);
   
    ntru_gadget_ct gadget_encrypt(long* msg); 
 
    void gadget_encrypt(long** out, long* msg);
 

};

}

#endif