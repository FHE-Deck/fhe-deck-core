 
#ifndef NTRUNIUM_GEN_H
#define NTRUNIUM_GEN_H

#include <math.h>
#include "lwe.h" 
#include "ntru.h"
#include "ntru_param.h"
#include "ntrunium.h"


namespace fhe_deck{

class ntrunium_gen{

public:

    // NTRU Gadget parameters for blind rotation
    gadget_ntru ntru_g;
    // NTRU parameters: this is the smaller modulus NTRU (its what goes in and out of the bootstrapping)
    ntru_param ntru_par;
    // LWE gadget parameters for keyswitching from NTRU to LWE
    LWEGadgetSK lwe_g;
    // LWE parameters for the LWE to blind rotate (modulus switched after the key switching, so the secret key is the same)
    LWESK lwe;
  
    // This is for the extension of the secret key for the blind rotation algorithm
    long *ext_s;
    int sizeof_ext_s;
    long *u;
    int sizeof_u;
 

    ~ntrunium_gen();

    ntrunium_gen();

    ntrunium_gen(gadget_ntru ntru_g_par, ntru_param ntru_par, LWEGadgetSK lwe_g_par);
    
    void init_binary_key();

    void init_ternary_key();

    ntrunium* get_ntrunium();

    // No Secret keys involved, but makes sense only when constructing the key switching key
    long*** ntru_to_lwe_key_switch_init();
  
    // Secret keys involved 
    long*** ntru_to_lwe_key_switch_key_gen();

    // No secret key involved but lets leave it here for now at least
    void ntru_to_lwe_key_switch_delete(long*** ksk, LWEGadgetParam lwe_g_par, ntru_param ntru_par);
 
    ntru_gadget_ct* blind_rotation_key_gen();
      
};

 
enum ntrunium_named_param{
    ntrunium_C_11_T, ntrunium_C_12_T, ntrunium_C_13_T, ntrunium_C_14_T,
    ntrunium_C_11_B, ntrunium_C_12_B, ntrunium_C_13_B, ntrunium_C_14_B,
    ntrunium_small_test_params_B
}; 

class ntrunium_named_param_generator{ 
    
    public: 
    int N;  
    //long Q_pot;   
    long P; 
    long Q;
    double ntru_stddev;
    int ntru_basis;
    ntru_param ntru_par; 
    ntru_param ntru_par_P;  

    ntru_sk ntru_P; 
    ntru_sk ntru; 

    ntru_gadget_param ntru_g_par; 
    gadget_ntru g_ntru; 

    // LWE parameters for key switching
    int n;  
    int lwe_stddev;
    int lwe_basis;
    std::shared_ptr<LWEParam> param; 
    LWESK lwe; 
    LWEGadgetParam lwe_g_par; 
    LWEGadgetSK lwe_g; 
    LWEParam lwe_par_small;
    LWESK lwe_small;
    
    ntrunium_gen* boot_sk; 
    ntrunium* boot; 

    ~ntrunium_named_param_generator();

    ntrunium_named_param_generator() = default;

    ntrunium_named_param_generator(ntrunium_named_param name);
 
    void generate_bootstapping_keys(); 
 
    void init_ntrunium_small_test_params_B();

    void init_ntrunium_C_11_T();

    void init_ntrunium_C_12_T();

    void init_ntrunium_C_13_T();

    void init_ntrunium_C_14_T();

    void init_ntrunium_C_11_B();

    void init_ntrunium_C_12_B();

    void init_ntrunium_C_13_B();

    void init_ntrunium_C_14_B();

};

 
}

#endif