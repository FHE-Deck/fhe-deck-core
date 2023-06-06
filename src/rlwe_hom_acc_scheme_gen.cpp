
#include "../include/rlwe_hom_acc_scheme_gen.h"


rlwe_hom_acc_scheme_gen::~rlwe_hom_acc_scheme_gen(){
    if(is_ext_init){ 
        delete[] u;
        delete[] ext_s;
    }
}
 

rlwe_hom_acc_scheme_gen::rlwe_hom_acc_scheme_gen(rlwe_gadget_param rlwe_gadget_par, lwe_gadget_param lwe_gadget_par, polynomial_arithmetic sk_arithmetic, int masking_size, double stddev_masking, plaintext_encoding default_encoding){   
    rlwe_sk rlwe(rlwe_gadget_par.param, sk_arithmetic); 
    this->rlwe_gadget =  gadget_rlwe_sk(rlwe_gadget_par, rlwe);
    this->masking_size = masking_size;
    this->stddev_masking = stddev_masking;
    this->default_encoding = default_encoding;
 
    lwe_sk g_lwe = lwe_sk(lwe_gadget_par.lwe_par);
    this->lwe_gadget = lwe_gadget_sk(lwe_gadget_par, g_lwe); 
    long q = rlwe.param.N * 2; 
    this->lwe = lwe_gadget.lwe.modulus_switch(q);    
    // Another LWE for the extracted  
    lwe_param extract_lwe_par = lwe_param(rlwe.param.N, rlwe.param.Q, rlwe_gadget_par.param.key_type, rlwe_gadget_par.param.stddev);
    long* extract_key = extract_rlwe_key();
    extract_lwe = lwe_sk(extract_lwe_par, extract_key); 
 
    if(lwe_gadget.lwe_g_par.lwe_par.key_d == binary){   
        this->init_binary_key(); 
    }else{  
        this->init_ternary_key();
    }   
    delete[] extract_key;   
}


rlwe_hom_acc_scheme_gen::rlwe_hom_acc_scheme_gen(const rlwe_hom_acc_scheme_gen& other){
    this->rlwe_gadget =  other.rlwe_gadget;
    this->masking_size = other.masking_size;
    this->stddev_masking = other.stddev_masking;
    this->default_encoding = other.default_encoding;
 
    this->lwe_gadget = other.lwe_gadget;  
    this->lwe = other.lwe; 
 
    this->extract_lwe = other.extract_lwe;
 
    if(lwe_gadget.lwe_g_par.lwe_par.key_d == binary){   
        this->init_binary_key(); 
    }else{  
        this->init_ternary_key();
    }    
 
}

rlwe_hom_acc_scheme_gen& rlwe_hom_acc_scheme_gen::operator=(const rlwe_hom_acc_scheme_gen other){ 
    if (this == &other)
    {
        return *this;
    } 
    this->masking_size = other.masking_size;  
    this->stddev_masking = other.stddev_masking;  
    this->default_encoding = other.default_encoding;  
    this->lwe_gadget = other.lwe_gadget;    
    this->lwe = other.lwe;   
    this->extract_lwe = other.extract_lwe;  

    this->rlwe_gadget = other.rlwe_gadget;  
    if(lwe_gadget.lwe_g_par.lwe_par.key_d == binary){   
        this->init_binary_key(); 
    }else{  
        this->init_ternary_key();
    }     
    return *this;
}


std::shared_ptr<rlwe_hom_acc_scheme> rlwe_hom_acc_scheme_gen::get_public_param(){   
    // The key switching key
    long ***ksk = key_switching_key_gen();  
    // Masking Key Gen
    long **masking_key = masking_key_gen();   
    // The blind rotation key 
    rlwe_gadget_ct *bk = blind_rotation_key_gen();   
    return std::shared_ptr<rlwe_hom_acc_scheme>(new rlwe_hom_acc_scheme(rlwe_gadget.gadget_param, lwe_gadget.lwe_g_par, lwe.lwe_par, bk, ksk, masking_key, masking_size, stddev_masking, default_encoding)); 
}

void rlwe_hom_acc_scheme_gen::set_public_params(rlwe_hom_acc_scheme *boot_pk){
    // The key switching key
    long ***ksk = key_switching_key_gen();  
    // Masking Key Gen
    long **masking_key = masking_key_gen();   
    // The blind rotation key 
    rlwe_gadget_ct *bk = blind_rotation_key_gen();   
    boot_pk = new rlwe_hom_acc_scheme(rlwe_gadget.gadget_param, lwe_gadget.lwe_g_par, lwe.lwe_par, bk, ksk, masking_key, masking_size, stddev_masking, default_encoding); 
}


long* rlwe_hom_acc_scheme_gen::extract_rlwe_key(){ 
    long* key = new long[rlwe_gadget.gadget_param.param.N];
    for(int i = 0; i < rlwe_gadget.gadget_param.param.N; ++i){
        key[i] = -rlwe_gadget.sk.s[i];
    }
    return key;
}


void rlwe_hom_acc_scheme_gen::init_binary_key(){
        sizeof_u = 1;
        this->u = new long[sizeof_u];
        u[0] = 1;
        sizeof_ext_s = lwe.lwe_par.n;
        this->ext_s = new long[sizeof_ext_s];
        for(int i = 0; i < lwe.lwe_par.n; ++i){
            this->ext_s[i] = lwe.s[i];
        }
        is_ext_init = true;
}

void rlwe_hom_acc_scheme_gen::init_ternary_key(){
        sizeof_u = 1;
        this->u = new long[sizeof_u];
        u[0] = 1;
        sizeof_ext_s = lwe.lwe_par.n;
        this->ext_s = new long[sizeof_ext_s];
        for(int i = 0; i < lwe.lwe_par.n; ++i){
            this->ext_s[i] = lwe.s[i];
        }
        is_ext_init = true;
}



long*** rlwe_hom_acc_scheme_gen::key_switching_key_gen(){ 
    // Initialize the key switching key
    long ***ksk = new long**[rlwe_gadget.gadget_param.param.N]; 
    for(int i = 0; i < rlwe_gadget.gadget_param.param.N; ++i){
        ksk[i] = new long*[lwe_gadget.lwe_g_par.ell];
        for(int j = 0; j < lwe_gadget.lwe_g_par.ell; ++j){ 
            ksk[i][j] = lwe_gadget.lwe_g_par.lwe_par.init_ct();
        }
    } 
    for(int i = 0; i < rlwe_gadget.gadget_param.param.N; ++i){  
        ksk[i] = lwe_gadget.gadget_encrypt(-rlwe_gadget.sk.s[i]);  
    } 
    return ksk;
}

long** rlwe_hom_acc_scheme_gen::masking_key_gen(){ 
    // Initialize the key switching key
    long **masking_key = new long*[masking_size]; 
    for(int i = 0; i < masking_size; ++i){ 
        masking_key[i] = extract_lwe.encrypt(0);   
    }
    return masking_key;
}
    

rlwe_gadget_ct* rlwe_hom_acc_scheme_gen::blind_rotation_key_gen(){  
    long *ext_key_mono = rlwe_gadget.gadget_param.param.init_zero_poly(); 
    rlwe_gadget_ct* bk = new rlwe_gadget_ct[sizeof_ext_s];   
    for(int i = 0; i < sizeof_ext_s; ++i){  
        ext_key_mono[0] = ext_s[i];    
        bk[i] = rlwe_gadget.gadget_encrypt(ext_key_mono); 
    }  
    delete[] ext_key_mono; 
    return bk;
}



// This is a special way of encoding the lwe, so that we can immediately do a functional blind rotation
 long* rlwe_hom_acc_scheme_gen::scale_and_encrypt_initial_lwe(long m, int t){
     long* out = lwe.lwe_par.init_ct();
     scale_and_encrypt_initial_lwe(out, m, t);
     return out;
 }
    
    // This is a special way of encoding the lwe, so that we can immediately do a functional blind rotation
 void rlwe_hom_acc_scheme_gen::scale_and_encrypt_initial_lwe(long* ct, long m, int t){ 
    double scale = (double)lwe.lwe_par.Q/ (2 * t);
    long m_scaled =  (long)round((double)m * scale); 
    lwe.encrypt(ct, m_scaled);
 }
 


rlwe_hom_acc_scheme_named_param_generator::rlwe_hom_acc_scheme_named_param_generator(rlwe_hom_acc_scheme_named_param name){
    if(name == rlwe_hom_acc_scheme_C_11_B){
        init_rlwe_hom_acc_scheme_C_11_B();
    } else if(name == rlwe_hom_acc_scheme_C_11_flood){
        init_rlwe_hom_acc_scheme_C_11_flood();
    } else if(name == rlwe_hom_acc_scheme_small_test){
        init_rlwe_hom_acc_scheme_small_test();
    } else if(name == rlwe_hom_acc_scheme_C_11_NTT){
            init_rlwe_hom_acc_scheme_C_11_NTT();
    }else if(name == rlwe_hom_acc_scheme_C_11_NTT_flood){
            init_rlwe_hom_acc_scheme_C_11_NTT_flood();
    }else if(name == rlwe_hom_acc_scheme_C_11_NTT_amortized){
            init_rlwe_hom_acc_scheme_C_11_NTT_amortized();
    }
    else{
        std::cout << "No parameter set selected!" <<  std::endl;
    }
}
 

void rlwe_hom_acc_scheme_named_param_generator::generate_bootstapping_keys(){
    this->boot_sk = std::unique_ptr<rlwe_hom_acc_scheme_gen>(new rlwe_hom_acc_scheme_gen(rlwe_gadget_par, lwe_gadget_par, sk_arithmetic, masking_size, stddev_masking, default_encoding)); 
    this->boot = boot_sk->get_public_param(); 
} 

rlwe_hom_acc_scheme_gen rlwe_hom_acc_scheme_named_param_generator::generate_secret_key(){
    return rlwe_hom_acc_scheme_gen(rlwe_gadget_par, lwe_gadget_par, sk_arithmetic, masking_size, stddev_masking, default_encoding);
}
 

void rlwe_hom_acc_scheme_named_param_generator::init_rlwe_hom_acc_scheme_small_test(){
    // TODO: For now I just put some parameters for testing
    int N = 32;
    // 2**13
    long Q = 4096;
    double rlwe_stddev = 0;
    int rlwe_basis = 2;
    double stddev_simul = rlwe_basis;
    rlwe_param rlwe_par(negacyclic, N, Q, ternary, any, rlwe_stddev, double_fft);
    gadget deter_gadget = gadget(N, Q, rlwe_basis, signed_decomposition_gadget);
    gadget rand_gadget = gadget(N, Q, rlwe_basis, stddev_simul, discrete_gaussian_gadget);
    rlwe_gadget_par = rlwe_gadget_param(rlwe_par, rlwe_basis, deter_gadget, rand_gadget);
    
    int n = 10;
    int lwe_basis = 2;
    double lwe_stddev = 0;
    lwe_param lwe_par(n, Q, binary, lwe_stddev);
    lwe_gadget_par = lwe_gadget_param(lwe_par, lwe_basis); 

    default_encoding = plaintext_encoding(full_domain, 4, Q);
} 





void rlwe_hom_acc_scheme_named_param_generator::init_rlwe_hom_acc_scheme_C_11_NTT(){ 
    // 2**11
    int N = 2048; 
    // 2**48 - 16383 % 2*(2**11) = 1 (NTT Friendly), Base-4096 decomposition of 281474976694273: [1, 4092, 4095, 4095], L_2 norm: 7091.016499769268
    long Q = 281474976694273;
    double rlwe_stddev = 3.2; 
    // 2**8
    int rlwe_basis = 256;  
    // stddev_simul approx  2**(17.78)
    double stddev_simul = 225812;  
    masking_size = 8192;
    // stddev_simul approx  2**(12.37)
    stddev_masking = 8192;

    rlwe_param rlwe_par(negacyclic, N, Q, ternary, any, rlwe_stddev, hexl_ntt);
    gadget deter_gadget = gadget(N, Q, rlwe_basis * rlwe_basis * rlwe_basis, signed_decomposition_gadget);
    gadget rand_gadget = gadget(N, Q, rlwe_basis, stddev_simul, discrete_gaussian_gadget);
    rlwe_gadget_par = rlwe_gadget_param(rlwe_par, rlwe_basis, deter_gadget, rand_gadget); 
    sk_arithmetic = hexl_ntt;

    // 2**9 + 400
    int n = 912;
    // 2**7
    int lwe_basis = 128;
    // 2**(26) 
    double lwe_stddev = 67108864;
    lwe_param lwe_par(n, Q, binary, lwe_stddev);
    lwe_gadget_par = lwe_gadget_param(lwe_par, lwe_basis); 

    default_encoding = plaintext_encoding(full_domain, 4, Q);
} 




void rlwe_hom_acc_scheme_named_param_generator::init_rlwe_hom_acc_scheme_C_11_NTT_flood(){ 
    // 2**11
    int N = 2048;
    // 2**36 - 12287 % 2*(2**11) = 1 (NTT friendly prime)
    //long Q = 68719464449;
    // 2**48 - 16383 % 2*(2**11) = 1 (NTT Friendly), Base-4096 decomposition of 281474976694273: [1, 4092, 4095, 4095], L_2 norm: 7091.016499769268
    long Q = 281474976694273;
    double rlwe_stddev = 3.2;
    // 2**4 -> 2**12
    int rlwe_basis = 256; 
    // Set to dummy 1 (here we tests noise flooding which will perform similarly to deter)
    double stddev_simul = 225812;  
    masking_size = 8192;
    // stddev_simul approx  2**(12.37)
    stddev_masking = 8192;

    rlwe_param rlwe_par(negacyclic, N, Q, ternary, any, rlwe_stddev, hexl_ntt);
    gadget deter_gadget = gadget(N, Q, rlwe_basis * rlwe_basis * rlwe_basis, signed_decomposition_gadget);
    gadget rand_gadget = gadget(N, Q, rlwe_basis, stddev_simul, signed_decomposition_gadget);
    rlwe_gadget_par = rlwe_gadget_param(rlwe_par, rlwe_basis, deter_gadget, rand_gadget);
    // TODO: The correct one should be ntl or hexl_ntt - but hexl_ntt has a bug, and ntl is slow so for now I leave double_fft (larger error so its rather not the best)
    sk_arithmetic = ntl;

    // 2**9 + 400
    int n = 912;
    int lwe_basis = 128;
    // 2**(14)
    double lwe_stddev = 67108864; 
    lwe_param lwe_par(n, Q, binary, lwe_stddev);
    lwe_gadget_par = lwe_gadget_param(lwe_par, lwe_basis); 

    default_encoding = plaintext_encoding(full_domain, 4, Q);
} 



// Power of two parameter set
void rlwe_hom_acc_scheme_named_param_generator::init_rlwe_hom_acc_scheme_C_11_B(){ 
    // 2**11
    int N = 2048;
    // 2**36
    long Q = 68719476736;
    double rlwe_stddev = 3.2;
    // 2**4
    int rlwe_basis = 16; 
    double stddev_simul = 505;
    masking_size = 3370;
    stddev_masking = 4010391;

    rlwe_param rlwe_par(negacyclic, N, Q, ternary, any, rlwe_stddev, double_fft);
    gadget deter_gadget = gadget(N, Q, rlwe_basis * rlwe_basis * rlwe_basis, signed_decomposition_gadget);
    gadget rand_gadget = gadget(N, Q, rlwe_basis, stddev_simul, discrete_gaussian_gadget);
    rlwe_gadget_par = rlwe_gadget_param(rlwe_par, rlwe_basis, deter_gadget, rand_gadget);
    sk_arithmetic = double_fft;

    // 2**9 + 430
    int n = 912;
    int lwe_basis = 128;
    // 2**(14)
    double lwe_stddev = 16384; 
    lwe_param lwe_par(n, Q, binary, lwe_stddev);
    lwe_gadget_par = lwe_gadget_param(lwe_par, lwe_basis); 

    default_encoding = plaintext_encoding(full_domain, 4, Q);
} 

 
void rlwe_hom_acc_scheme_named_param_generator::init_rlwe_hom_acc_scheme_C_11_flood(){ 
    // 2**11
    int N = 2048;
    // 2**36
    long Q = 68719476736;
    double rlwe_stddev = 3.2;
    // 2**4
    int rlwe_basis = 16; 
    double stddev_simul = 505;
    masking_size = 3370;
    stddev_masking = 4010391;

    rlwe_param rlwe_par(negacyclic, N, Q, ternary, any, rlwe_stddev, double_fft);
    gadget deter_gadget = gadget(N, Q, rlwe_basis * rlwe_basis * rlwe_basis, signed_decomposition_gadget);
    gadget rand_gadget = gadget(N, Q, rlwe_basis, signed_decomposition_gadget);
    rlwe_gadget_par = rlwe_gadget_param(rlwe_par, rlwe_basis, deter_gadget, rand_gadget);
    sk_arithmetic = double_fft;

    // 2**9 + 430
    int n = 912;
    int lwe_basis = 128;
    // 2**(14) 
    double lwe_stddev = 16384;
    lwe_param lwe_par(n, Q, binary, lwe_stddev);
    lwe_gadget_par = lwe_gadget_param(lwe_par, lwe_basis); 

    default_encoding = plaintext_encoding(full_domain, 4, Q);
} 

 


void rlwe_hom_acc_scheme_named_param_generator::init_rlwe_hom_acc_scheme_C_11_NTT_amortized(){ 
    // 2**11
    int N = 2048; 
    // 2**51 - 131071 % 2*(2**11) = 1 (NTT Friendly),   
    long Q = 2251799813554177;
    double rlwe_stddev = 3.2; 
    // 2**8
    int rlwe_basis = 512;  
    // stddev_simul approx  2**(19.28)
    double stddev_simul = 638072;  

    masking_size = 8;
    // stddev_simul approx  2**(11.22)
    stddev_masking = 2389;

    rlwe_param rlwe_par(negacyclic, N, Q, ternary, any, rlwe_stddev, hexl_ntt);
    gadget deter_gadget = gadget(N, Q, rlwe_basis * rlwe_basis, signed_decomposition_gadget);
    gadget rand_gadget = gadget(N, Q, rlwe_basis, stddev_simul, discrete_gaussian_gadget);
    rlwe_gadget_par = rlwe_gadget_param(rlwe_par, rlwe_basis, deter_gadget, rand_gadget); 
    sk_arithmetic = hexl_ntt;

    // 2**10
    int n = 912;
    // 2**9
    int lwe_basis = 512;
    // 2**(23) 
    double lwe_stddev = 8388608;
    lwe_param lwe_par(n, Q, binary, lwe_stddev);
    lwe_gadget_par = lwe_gadget_param(lwe_par, lwe_basis); 

    default_encoding = plaintext_encoding(full_domain, 16, Q);
} 
