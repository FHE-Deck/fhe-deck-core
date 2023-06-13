 
#include "../include/ntrunium_gen.h"
using namespace fhe_deck;

ntrunium_gen::~ntrunium_gen(){
    delete[] ext_s;
    delete[] u; 
}


ntrunium_gen::ntrunium_gen(){
}

ntrunium_gen::ntrunium_gen(gadget_ntru ntru_g, ntru_param ntru_par, LWEGadgetSK lwe_g){  
    this->ntru_g = ntru_g;
    this->ntru_par = ntru_par;
    this->lwe_g = lwe_g;   
    long q; 
     if(ntru_g.gadget_param.param.ring==cyclic){
        // Cyclic ring
        q = ntru_g.gadget_param.param.N; 
    }else{
        // Negacyclic ring
        q = 2 * ntru_g.gadget_param.param.N;  
    }   
    this->lwe = lwe_g.lwe.modulus_switch(q);   
    if(lwe_g.gadget_param.lwe_param->key_d == binary){   
        this->init_binary_key(); 
    }else{  
        this->init_ternary_key();
    }    
}

   


void ntrunium_gen::init_binary_key(){
        sizeof_u = 1;
        this->u = new long[sizeof_u];
        u[0] = 1;
        sizeof_ext_s = lwe.param->n;
        this->ext_s = new long[sizeof_ext_s];
        for(int i = 0; i < lwe.param->n; ++i){
            this->ext_s[i] = lwe.s[i];
        }
}


void ntrunium_gen::init_ternary_key(){
        sizeof_u = 2;
        this->u = new long[sizeof_u];
        u[0] = -1;
        u[1] = 1;
        sizeof_ext_s = 2*lwe.param->n; 
        this->ext_s = new long[sizeof_ext_s];
        for(int i = 0; i < lwe.param->n; ++i){
            switch(lwe.s[i]){
                    case -1:
                            ext_s[i] = 1;
                            ext_s[i+lwe.param->n] = 0;
                            break;
                    case 0:  
                            ext_s[i] = 0;
                            ext_s[i+lwe.param->n] = 0;
                            break;
                    case 1:  
                            ext_s[i] = 0;
                            ext_s[i+lwe.param->n] = 1;
                            break;
                    default: std::cout << "Fatal Error: lwe.s[" << i << "]: " << lwe.s[i] << std::endl;
            } 
        }
}

ntrunium* ntrunium_gen::get_ntrunium(){   
    long ***ksk = ntru_to_lwe_key_switch_key_gen();  
    ntru_gadget_ct* bk_gadget = blind_rotation_key_gen();     
    return new ntrunium(ntru_g.gadget_param, ntru_par, lwe_g.gadget_param, lwe.param, ksk, bk_gadget);
}



long*** ntrunium_gen::ntru_to_lwe_key_switch_init(){  
    long ***ksk = new long**[ntru_g.gadget_param.param.N];  
    for(int i = 0; i < ntru_g.gadget_param.param.N; ++i){
        ksk[i] = new long*[lwe_g.gadget_param.ell];
        for(int j = 0; j < lwe_g.gadget_param.ell; ++j){ 
            ksk[i][j] = lwe_g.gadget_param.lwe_param->init_ct();
        }
    }
    return ksk;
}



long*** ntrunium_gen::ntru_to_lwe_key_switch_key_gen(){ 
    long*** ksk = ntrunium_gen::ntru_to_lwe_key_switch_init();  
    ksk[0] = lwe_g.gadget_encrypt(ntru_g.ntru.f[0]);  
    for(int i = 1; i < ntru_g.gadget_param.param.N; ++i){ 
        ksk[i] = lwe_g.gadget_encrypt(-ntru_g.ntru.f[ntru_g.gadget_param.param.N-i]);  
    } 
    return ksk;
}


void ntrunium_gen::ntru_to_lwe_key_switch_delete(long*** ksk, LWEGadgetParam lwe_g_par, ntru_param ntru_par){
    for(int i = 0; i < ntru_par.N; ++i){ 
        for(int j = 0; j < lwe_g_par.ell; ++j){ 
            delete(ksk[i][j]);  
        }
        delete(ksk[i]);
    }
    delete(ksk);
}
 
 



ntru_gadget_ct* ntrunium_gen::blind_rotation_key_gen(){   
    long *ext_key_mono = ntru_g.gadget_param.param.init_zero_poly();  
    ntru_gadget_ct* bk_gadget = new ntru_gadget_ct[sizeof_ext_s];
    for(int i = 0; i < sizeof_ext_s; ++i){ 
        ext_key_mono[0] = ext_s[i];     
        bk_gadget[i] = ntru_g.gadget_encrypt(ext_key_mono);   
    } 
    delete[] ext_key_mono; 
    return bk_gadget;
}
 
ntrunium_named_param_generator::~ntrunium_named_param_generator(){  
}

ntrunium_named_param_generator::ntrunium_named_param_generator(ntrunium_named_param name){
    if(name == ntrunium_C_11_T){ 
        init_ntrunium_C_11_T();
    }else if (name == ntrunium_C_12_T)
    { 
        init_ntrunium_C_12_T();
    }else if (name == ntrunium_C_13_T)
    { 
        init_ntrunium_C_13_T();
    }else if (name == ntrunium_C_14_T)
    { 
        init_ntrunium_C_14_T();
    }else if (name == ntrunium_C_11_B)
    {
        init_ntrunium_C_11_B();
    }else if (name == ntrunium_C_12_B)
    {
        init_ntrunium_C_12_B();
    }else if (name == ntrunium_C_13_B)
    {
        init_ntrunium_C_13_B();
    }else if (name == ntrunium_C_14_B)
    {
        init_ntrunium_C_14_B();
    }else if (name == ntrunium_small_test_params_B)
    {
        init_ntrunium_small_test_params_B();
    }
    
}


void ntrunium_named_param_generator::generate_bootstapping_keys(){    
    this->boot_sk = new ntrunium_gen(g_ntru, ntru_par, lwe_g);   
    this->boot = boot_sk->get_ntrunium();     
} 
 


void ntrunium_named_param_generator::init_ntrunium_C_11_T(){
  
}
 

void ntrunium_named_param_generator::init_ntrunium_C_12_T(){
 
}

void ntrunium_named_param_generator::init_ntrunium_C_13_T(){
 
    
}

void ntrunium_named_param_generator::init_ntrunium_C_14_T(){
 
}



void ntrunium_named_param_generator::init_ntrunium_small_test_params_B(){ 
    // NTRU parameters
    // Prime modulus: 2**30 - 35
    P = 1073741789;  
    Q = 33554393; 
    ntru_stddev = 3.2; 
    N = 128; 
    ntru_basis = 16;      
    ntru_par = ntru_param(negacyclic, N, Q, ntru_stddev); 
    ntru_par_P =  ntru_param(negacyclic, N, P, ntru_stddev);  
    ntru_g_par = ntru_gadget_param(ntru_par_P, ntru_basis, double_fft);

    // LWE Parameters
    n = 10; 
    lwe_stddev = 2;  
    lwe_basis = 2; 
    param = std::shared_ptr<LWEParam>(new LWEParam(n, Q, binary, lwe_stddev));  
    lwe = LWESK(param);
    lwe_g_par = LWEGadgetParam(param, lwe_basis);
    lwe_g = LWEGadgetSK(lwe_g_par, lwe);
    // negacyclic ring so small lwe is:
    long q = 2 * ntru_g_par.param.N; 
    lwe_par_small = lwe_g.gadget_param.lwe_param->modulus_switch(q);  
    lwe_small = lwe_g.lwe.modulus_switch(q);
  
    // Let generate the secret keys for NTRU
    //  Key generation 
    ntru_P = ntru_sk(ntru_par_P);
    ntru = ntru_P.mod_switch(Q); 
    g_ntru = gadget_ntru(ntru_g_par, ntru_P); 
    
}



void ntrunium_named_param_generator::init_ntrunium_C_11_B(){ 
    // NTRU parameters
    // Prime: 2**30-35
    P = 1073741789;  
    // Prime: 2**25-39
    Q = 33554393; 
    ntru_stddev = 1/4; 
    // 2**11
    N = 2048; 
    // 2**6
    ntru_basis = 64;   
    ntru_par = ntru_param(negacyclic, N, Q, ntru_stddev); 
    ntru_par_P =  ntru_param(negacyclic, N, P, ntru_stddev);  
    ntru_g_par = ntru_gadget_param(ntru_par_P, ntru_basis, double_fft);

    // LWE Parameters
    // 2**9 + 125
    n = 637; 
    // 2**10
    lwe_stddev = 1024;  
    lwe_basis = 2; 
    param = std::shared_ptr<LWEParam>(new LWEParam(n, Q, binary, lwe_stddev));  
    lwe = LWESK(param);
    lwe_g_par = LWEGadgetParam(param, lwe_basis);
    lwe_g = LWEGadgetSK(lwe_g_par, lwe);
    // negacyclic ring so small lwe is:
    long q = 2 * ntru_g_par.param.N; 
    lwe_par_small = lwe_g.gadget_param.lwe_param->modulus_switch(q);  
    lwe_small = lwe_g.lwe.modulus_switch(q);
  
    // Let generate the secret keys for NTRU
    //  Key generation 
    ntru_P = ntru_sk(ntru_par_P);
    ntru = ntru_P.mod_switch(Q); 
    g_ntru = gadget_ntru(ntru_g_par, ntru_P); 
    
}

void ntrunium_named_param_generator::init_ntrunium_C_12_B(){
    // NTRU parameters
    // Prime: 2**40-87
    //P = 1099511627689;  
    // Prime: 2**45-204799 % 2*N = 1
    P = 35184371884033;
    // Prime: 2**33-9
    Q = 8589934583; 
    ntru_stddev = 1/4; 
    // 2**12
    N = 4096; 
    // 2**10
    //ntru_basis = 1024;   
    // 2**15
    ntru_basis = 32768;  
    ntru_par = ntru_param(negacyclic, N, Q, ntru_stddev); 
    ntru_par_P =  ntru_param(negacyclic, N, P, ntru_stddev);  
    ntru_g_par = ntru_gadget_param(ntru_par_P, ntru_basis, hexl_ntt);

    // LWE Parameters
    // 2**9 + 238
    n = 750; 
    // 2**14
    lwe_stddev = 16384;  
    lwe_basis = 2; 
    param = std::shared_ptr<LWEParam>(new LWEParam(n, Q, binary, lwe_stddev));  
    lwe = LWESK(param);
    lwe_g_par = LWEGadgetParam(param, lwe_basis);
    lwe_g = LWEGadgetSK(lwe_g_par, lwe);
    // negacyclic ring so small lwe is:
    long q = 2 * ntru_g_par.param.N; 
    lwe_par_small = lwe_g.gadget_param.lwe_param->modulus_switch(q);  
    lwe_small = lwe_g.lwe.modulus_switch(q);
  
    // Let generate the secret keys for NTRU
    //  Key generation 
    ntru_P = ntru_sk(ntru_par_P);
    ntru = ntru_P.mod_switch(Q); 
    g_ntru = gadget_ntru(ntru_g_par, ntru_P); 
}

void ntrunium_named_param_generator::init_ntrunium_C_13_B(){
    // NTRU parameters
    // Prime: 2**40-87
    //P = 1099511627689;  
    // Prime: 2**45-475135 % 2*N = 1
    P = 35184371613697;
    // Prime: 2**34-41
    Q = 17179869143; 
    ntru_stddev = 1/4; 
    // 2**13
    N = 8192; 
    // 2**10
    //ntru_basis = 1024;   
    // 2**15
    ntru_basis = 32768;  
    ntru_par = ntru_param(negacyclic, N, Q, ntru_stddev); 
    ntru_par_P =  ntru_param(negacyclic, N, P, ntru_stddev);  
    ntru_g_par = ntru_gadget_param(ntru_par_P, ntru_basis, hexl_ntt);

    // LWE Parameters
    // 2**9 + 315
    n = 827; 
    // 2**14
    lwe_stddev = 16384;  
    lwe_basis = 2; 
    param = std::shared_ptr<LWEParam>(new LWEParam(n, Q, binary, lwe_stddev));  
    lwe = LWESK(param);
    lwe_g_par = LWEGadgetParam(param, lwe_basis);
    lwe_g = LWEGadgetSK(lwe_g_par, lwe);
    // negacyclic ring so small lwe is:
    long q = 2 * ntru_g_par.param.N; 
    lwe_par_small = lwe_g.gadget_param.lwe_param->modulus_switch(q);  
    lwe_small = lwe_g.lwe.modulus_switch(q);
  
    // Let generate the secret keys for NTRU
    //  Key generation 
    ntru_P = ntru_sk(ntru_par_P);
    ntru = ntru_P.mod_switch(Q); 
    g_ntru = gadget_ntru(ntru_g_par, ntru_P); 
 
}

void ntrunium_named_param_generator::init_ntrunium_C_14_B(){
    // NTRU parameters  
    // Prime: 2**45-950271 % 2*N = 1
    P = 35184371138561;
    // Prime: 2**36-5
    Q = 68719476731; 
    ntru_stddev = 1/4; 
    // 2**14
    N = 16384; 
    // 2**10
    //ntru_basis = 1024;   
    // 2**15
    ntru_basis = 32768;    
    ntru_par = ntru_param(negacyclic, N, Q, ntru_stddev); 
    ntru_par_P =  ntru_param(negacyclic, N, P, ntru_stddev);  
    ntru_g_par = ntru_gadget_param(ntru_par_P, ntru_basis, hexl_ntt);

    // LWE Parameters
    // 2**9 + 390
    n = 902; 
    // 2**14
    lwe_stddev = 16384;  
    lwe_basis = 2; 
    param = std::shared_ptr<LWEParam>(new LWEParam(n, Q, binary, lwe_stddev));  
    lwe = LWESK(param);
    lwe_g_par = LWEGadgetParam(param, lwe_basis);
    lwe_g = LWEGadgetSK(lwe_g_par, lwe);
    // negacyclic ring so small lwe is:
    long q = 2 * ntru_g_par.param.N; 
    lwe_par_small = lwe_g.gadget_param.lwe_param->modulus_switch(q);  
    lwe_small = lwe_g.lwe.modulus_switch(q);
  
    // Let generate the secret keys for NTRU
    //  Key generation 
    ntru_P = ntru_sk(ntru_par_P);
    ntru = ntru_P.mod_switch(Q); 
    g_ntru = gadget_ntru(ntru_g_par, ntru_P); 
}
 