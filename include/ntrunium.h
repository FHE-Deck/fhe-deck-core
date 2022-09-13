 
#ifndef NTRUNIUM_H
#define NTRUNIUM_H

#include "lwe.h"
#include "ntru.h"
#include "lwe_param.h"
#include "ntru_param.h"
#include "rotation_poly.h"

class ntrunium{

    public:

    // NTRU Gadget Parameters for the bootstrapping key
    ntru_gadget_param ntru_g_par;
    // NTRU paramaters for NTRU ciphertexts (smaller modulus than the gadget NTRU, but the same key)
    ntru_param ntru_par;
    // LWE Gadget parameters for the key switching key (we key switch from ntru_par to LWE)
    lwe_gadget_param lwe_g_par;
    // LWE parameters for modswithing to Z_2N. For the LWE that is blind rotated (in bootstrapping we modulus switch from lwe_g_par to lwe_par and blind rotate lwe_par)
    lwe_param lwe_par;
    // LWE parameters for modswithing to Z_N. For functional bootstrapping
    lwe_param lwe_par_tiny;
     

    long ***ksk;
    // Blind rotation key 
    ntru_gadget_ct *bk_gadget;  
 

    // Parameteres of the encoding of the LWE key in the blind rotation. These are paramters about the secret key of lwe_par (and lwe_g_par as lwe_par is a modulus switch of lwe_g_par)
    key_dist key_d;
    int sizeof_ext_s;
    long *u;
    int sizeof_u;

    ~ntrunium();

    ntrunium();

    ntrunium(ntru_gadget_param ntru_g_par, ntru_param ntru_par, lwe_gadget_param lwe_g_par, lwe_param lwe_par,  long ***ksk, ntru_gadget_ct *bk);
      
    void init_binary_key();

    void init_ternary_key();

    // Key Switching
    void ntru_to_lwe_key_switch(long *lwe_ct, ntru_ct *ct);
  
    // Blind Rotation 
    ntru_ct blind_rotate(ntru_ct *acc_in, long *lwe_ct);
  
    ntru_ct bootstrap(ntru_ct *acc_in, ntru_ct *ct, int t);
  
    // TODO: acc_msb should be initialized somehow by the class, but we would need to specify different plaintext spaces
    // So maybe a list with acc_msb + a function that initializes them (from a public key), 
    // then functional_bootstrap chooses the acc based on the t given as input. (but that is for future iteration)
    ntru_ct functional_bootstrap(ntru_ct *acc_in, ntru_ct *acc_msb, ntru_ct *ct, int t);

    void ntru_to_lwe_key_switch_delete(); 
     
};

#endif