#include "rlwe_hom_acc_scheme_gen.h"

using namespace fhe_deck;

TFHESecretKey::~TFHESecretKey(){
    if(is_ext_init){ 
        delete[] u;
        delete[] ext_s;
    }
}
 

TFHESecretKey::TFHESecretKey(RLWEGadgetParam rlwe_gadget_par, LWEGadgetParam lwe_gadget_par, PolynomialArithmetic sk_arithmetic, int masking_size, double stddev_masking, PlaintextEncoding default_encoding){   
    RLWESK rlwe(rlwe_gadget_par.rlwe_param, sk_arithmetic); 
    this->rlwe_gadget =  RLWEGadgetSK(rlwe_gadget_par, rlwe);
    this->masking_size = masking_size;
    this->stddev_masking = stddev_masking;
    this->default_encoding = default_encoding;
 
    LWESK g_lwe = LWESK(lwe_gadget_par.lwe_param);
    this->lwe_gadget = LWEGadgetSK(lwe_gadget_par, g_lwe); 
    long q = rlwe.param->N * 2; 
    this->lwe = lwe_gadget.lwe.modulus_switch(q);     
    long* extract_key = extract_rlwe_key();
    extract_lwe = LWESK(std::shared_ptr<LWEParam>(new LWEParam(rlwe.param->N, rlwe.param->Q, rlwe_gadget_par.rlwe_param->key_type, rlwe_gadget_par.rlwe_param->stddev)), extract_key); 
 
    if(lwe_gadget.gadget_param.lwe_param->key_d == binary){   
        this->init_binary_key(); 
    }else{  
        this->init_ternary_key();
    }   
    delete[] extract_key;   
}


TFHESecretKey::TFHESecretKey(const TFHESecretKey& other){
    this->rlwe_gadget =  other.rlwe_gadget;
    this->masking_size = other.masking_size;
    this->stddev_masking = other.stddev_masking;
    this->default_encoding = other.default_encoding;
 
    this->lwe_gadget = other.lwe_gadget;  
    this->lwe = other.lwe; 
 
    this->extract_lwe = other.extract_lwe;
 
    if(lwe_gadget.gadget_param.lwe_param->key_d == binary){   
        this->init_binary_key(); 
    }else{  
        this->init_ternary_key();
    }    
 
}

TFHESecretKey& TFHESecretKey::operator=(const TFHESecretKey other){ 
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
    if(lwe_gadget.gadget_param.lwe_param->key_d == binary){   
        this->init_binary_key(); 
    }else{  
        this->init_ternary_key();
    }     
    return *this;
}


std::shared_ptr<TFHEPublicKey> TFHESecretKey::get_public_param(){     
    // The key switching key
    long ***ksk = key_switching_key_gen();   
    // Masking Key Gen
    long **masking_key = masking_key_gen();    
    // The blind rotation key 
    RLWEGadgetCT *bk = blind_rotation_key_gen();   
    return std::shared_ptr<TFHEPublicKey>(new TFHEPublicKey(rlwe_gadget.gadget_param, lwe_gadget.gadget_param, lwe.param, bk, ksk, masking_key, masking_size, stddev_masking, default_encoding)); 
}

void TFHESecretKey::set_public_params(TFHEPublicKey *boot_pk){
    // The key switching key
    long ***ksk = key_switching_key_gen();  
    // Masking Key Gen
    long **masking_key = masking_key_gen();   
    // The blind rotation key 
    RLWEGadgetCT *bk = blind_rotation_key_gen();   
    boot_pk = new TFHEPublicKey(rlwe_gadget.gadget_param, lwe_gadget.gadget_param, lwe.param, bk, ksk, masking_key, masking_size, stddev_masking, default_encoding); 
}


long* TFHESecretKey::extract_rlwe_key(){ 
    long* key = new long[rlwe_gadget.gadget_param.rlwe_param->N];
    for(int i = 0; i < rlwe_gadget.gadget_param.rlwe_param->N; ++i){
        key[i] = -rlwe_gadget.sk.s[i];
    }
    return key;
}


void TFHESecretKey::init_binary_key(){
        sizeof_u = 1;
        this->u = new long[sizeof_u];
        u[0] = 1;
        sizeof_ext_s = lwe.param->n;
        this->ext_s = new long[sizeof_ext_s];
        for(int i = 0; i < lwe.param->n; ++i){
            this->ext_s[i] = lwe.s[i];
        }
        is_ext_init = true;
}

void TFHESecretKey::init_ternary_key(){
        sizeof_u = 1;
        this->u = new long[sizeof_u];
        u[0] = 1;
        sizeof_ext_s = lwe.param->n;
        this->ext_s = new long[sizeof_ext_s];
        for(int i = 0; i < lwe.param->n; ++i){
            this->ext_s[i] = lwe.s[i];
        }
        is_ext_init = true;
}



long*** TFHESecretKey::key_switching_key_gen(){ 
    // Initialize the key switching key
    long ***ksk = new long**[rlwe_gadget.gadget_param.rlwe_param->N]; 
    for(int i = 0; i < rlwe_gadget.gadget_param.rlwe_param->N; ++i){
        ksk[i] = new long*[lwe_gadget.gadget_param.ell];
        for(int j = 0; j < lwe_gadget.gadget_param.ell; ++j){ 
            ksk[i][j] = lwe_gadget.gadget_param.lwe_param->init_ct();
        }
    } 
    for(int i = 0; i < rlwe_gadget.gadget_param.rlwe_param->N; ++i){  
        ksk[i] = lwe_gadget.gadget_encrypt(-rlwe_gadget.sk.s[i]);  
    } 
    return ksk;
}

long** TFHESecretKey::masking_key_gen(){ 
    // Initialize the key switching key
    long **masking_key = new long*[masking_size]; 
    for(int i = 0; i < masking_size; ++i){ 
        masking_key[i] = extract_lwe.encrypt(0);   
    }
    return masking_key;
}
    

RLWEGadgetCT* TFHESecretKey::blind_rotation_key_gen(){  
    
    long *ext_key_mono = rlwe_gadget.gadget_param.rlwe_param->init_zero_poly(); 
    RLWEGadgetCT* bk = new RLWEGadgetCT[sizeof_ext_s];    
    for(int i = 0; i < sizeof_ext_s; ++i){   
        ext_key_mono[0] = ext_s[i];    
        bk[i] = rlwe_gadget.gadget_encrypt(ext_key_mono); 
    }   
     
    delete[] ext_key_mono; 
    return bk;
}



// This is a special way of encoding the lwe, so that we can immediately do a functional blind rotation
 long* TFHESecretKey::scale_and_encrypt_initial_lwe(long m, int t){
     long* out = lwe.param->init_ct();
     scale_and_encrypt_initial_lwe(out, m, t);
     return out;
 }
    
    // This is a special way of encoding the lwe, so that we can immediately do a functional blind rotation
 void TFHESecretKey::scale_and_encrypt_initial_lwe(long* ct, long m, int t){ 
    double scale = (double)lwe.param->Q/ (2 * t);
    long m_scaled =  (long)round((double)m * scale); 
    lwe.encrypt(ct, m_scaled);
 }
 


TFHEKeyGenerator::TFHEKeyGenerator(TFHENamedParams name){
    if(name == tfhe_11_B){
        init_tfhe_11_B();
    } else if(name == tfhe_11_flood){
        init_tfhe_11_flood();
    } else if(name == tfhe_11_NTT){
        init_tfhe_11_NTT();
    }else if(name == tfhe_11_NTT_flood){
        init_tfhe_11_NTT_flood();
    }else if(name == tfhe_11_NTT_amortized){
        init_tfhe_11_NTT_amortized();
    }else if(name == tfhe_12_NTT_amortized){
        init_tfhe_12_NTT_amortized();
    }
    else{
        std::cout << "No parameter set selected!" <<  std::endl;
    }
}
 

void TFHEKeyGenerator::generate_bootstapping_keys(){
    this->boot_sk = std::unique_ptr<TFHESecretKey>(new TFHESecretKey(rlwe_gadget_par, lwe_gadget_par, sk_arithmetic, masking_size, stddev_masking, default_encoding)); 
    this->boot_pk = boot_sk->get_public_param(); 
} 

TFHESecretKey TFHEKeyGenerator::generate_secret_key(){
    return TFHESecretKey(rlwe_gadget_par, lwe_gadget_par, sk_arithmetic, masking_size, stddev_masking, default_encoding);
}
 
 



void TFHEKeyGenerator::init_tfhe_11_NTT(){ 
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

    std::shared_ptr<RLWEParam> rlwe_par(new RLWEParam(negacyclic, N, Q, ternary, any, rlwe_stddev, hexl_ntt));
    Gadget deter_gadget = Gadget(N, Q, rlwe_basis * rlwe_basis * rlwe_basis, signed_decomposition_gadget);
    Gadget rand_gadget = Gadget(N, Q, rlwe_basis, stddev_simul, discrete_gaussian_gadget);
    rlwe_gadget_par = RLWEGadgetParam(rlwe_par, rlwe_basis, deter_gadget, rand_gadget); 
    sk_arithmetic = hexl_ntt;

    // 2**9 + 400
    int n = 912;
    // 2**7
    int lwe_basis = 128;
    // 2**(26) 
    double lwe_stddev = 67108864;
    //LWEParam lwe_par(n, Q, binary, lwe_stddev);
    lwe_gadget_par = LWEGadgetParam(std::shared_ptr<LWEParam>(new LWEParam(n, Q, binary, lwe_stddev)), lwe_basis); 

    default_encoding = PlaintextEncoding(full_domain, 4, Q);
} 




void TFHEKeyGenerator::init_tfhe_11_NTT_flood(){ 
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

    std::shared_ptr<RLWEParam> rlwe_par(new RLWEParam(negacyclic, N, Q, ternary, any, rlwe_stddev, hexl_ntt));
    Gadget deter_gadget = Gadget(N, Q, rlwe_basis * rlwe_basis * rlwe_basis, signed_decomposition_gadget);
    Gadget rand_gadget = Gadget(N, Q, rlwe_basis, stddev_simul, signed_decomposition_gadget);
    rlwe_gadget_par = RLWEGadgetParam(rlwe_par, rlwe_basis, deter_gadget, rand_gadget);
    // TODO: The correct one should be ntl or hexl_ntt - but hexl_ntt has a bug, and ntl is slow so for now I leave double_fft (larger error so its rather not the best)
    sk_arithmetic = ntl;

    // 2**9 + 400
    int n = 912;
    int lwe_basis = 128;
    // 2**(14)
    double lwe_stddev = 67108864; 
    //LWEParam lwe_par(n, Q, binary, lwe_stddev);
    lwe_gadget_par = LWEGadgetParam(std::shared_ptr<LWEParam>(new LWEParam(n, Q, binary, lwe_stddev)), lwe_basis); 

    default_encoding = PlaintextEncoding(full_domain, 4, Q);
} 



// Power of two parameter set
void TFHEKeyGenerator::init_tfhe_11_B(){ 
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

    std::shared_ptr<RLWEParam> rlwe_par(new RLWEParam(negacyclic, N, Q, ternary, any, rlwe_stddev, double_fft));
    Gadget deter_gadget = Gadget(N, Q, rlwe_basis * rlwe_basis * rlwe_basis, signed_decomposition_gadget);
    Gadget rand_gadget = Gadget(N, Q, rlwe_basis, stddev_simul, discrete_gaussian_gadget);
    rlwe_gadget_par = RLWEGadgetParam(rlwe_par, rlwe_basis, deter_gadget, rand_gadget);
    sk_arithmetic = double_fft;

    // 2**9 + 430
    int n = 912;
    int lwe_basis = 128;
    // 2**(14)
    double lwe_stddev = 16384; 
    //LWEParam lwe_par(n, Q, binary, lwe_stddev);
    lwe_gadget_par = LWEGadgetParam(std::shared_ptr<LWEParam>(new LWEParam(n, Q, binary, lwe_stddev)), lwe_basis); 

    default_encoding = PlaintextEncoding(full_domain, 4, Q);
} 

 
void TFHEKeyGenerator::init_tfhe_11_flood(){ 
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

    std::shared_ptr<RLWEParam> rlwe_par(new RLWEParam(negacyclic, N, Q, ternary, any, rlwe_stddev, double_fft));
    Gadget deter_gadget = Gadget(N, Q, rlwe_basis * rlwe_basis * rlwe_basis, signed_decomposition_gadget);
    Gadget rand_gadget = Gadget(N, Q, rlwe_basis, signed_decomposition_gadget);
    rlwe_gadget_par = RLWEGadgetParam(rlwe_par, rlwe_basis, deter_gadget, rand_gadget);
    sk_arithmetic = double_fft;

    // 2**9 + 430
    int n = 912;
    int lwe_basis = 128;
    // 2**(14) 
    double lwe_stddev = 16384;
    //LWEParam lwe_par(n, Q, binary, lwe_stddev);
    lwe_gadget_par = LWEGadgetParam(std::shared_ptr<LWEParam>(new LWEParam(n, Q, binary, lwe_stddev)), lwe_basis); 

    default_encoding = PlaintextEncoding(full_domain, 4, Q);
} 

 


void TFHEKeyGenerator::init_tfhe_11_NTT_amortized(){ 
    // 2**11
    int N = 2048; 
    // (2**51 - 45055) % 2*(2**11) = 1 and prime (NTT Friendly),   
    long Q = 2251799813640193;  

    double rlwe_stddev = 3.2; 
    // 2**9
    int rlwe_basis = 512;  
    // stddev_simul approx  2**(19.28)
    double stddev_simul = 638072;  

    masking_size = 8050;
    // stddev_simul approx  2**(11.22)
    stddev_masking = 8192;

    std::shared_ptr<RLWEParam> rlwe_par(new RLWEParam(negacyclic, N, Q, ternary, any, rlwe_stddev, hexl_ntt));
    Gadget deter_gadget = Gadget(N, Q, rlwe_basis * rlwe_basis, signed_decomposition_gadget);
    Gadget rand_gadget = Gadget(N, Q, rlwe_basis, stddev_simul, discrete_gaussian_gadget);
    rlwe_gadget_par = RLWEGadgetParam(rlwe_par, rlwe_basis, deter_gadget, rand_gadget); 
    sk_arithmetic = hexl_ntt;
 
    int n = 950;
    // 2**9
    int lwe_basis = 512;
    // 2**(23) 
    double lwe_stddev = 262144;
    //LWEParam lwe_par(n, Q, binary, lwe_stddev);
    lwe_gadget_par = LWEGadgetParam(std::shared_ptr<LWEParam>(new LWEParam(n, Q, binary, lwe_stddev)), lwe_basis); 

    default_encoding = PlaintextEncoding(partial_domain, 8, Q);
} 




void TFHEKeyGenerator::init_tfhe_12_NTT_amortized(){ 
    std::cout << "init_tfhe_12_NTT_amortized" << std::endl;
    // 2**12
    int N = 4096; 
    // (2**51 - 131071) % 2*(2**12) = 1 and prime (NTT Friendly),   
    long Q = 2251799813554177;
    // 52-bit modulus
    //long Q = 4503599627149313;
    // 53-bit modulus
    //long Q = 9007199254429697;
    // 54-bit modulus
    //long Q =  18014398509309953;

    // The 50 bits works. Ofr some reason 51 bits breaks down. 
    // 2**50 - 16383
    //long Q = 1125899906826241;


    double rlwe_stddev = 3.2; 
    // 2**8
    int rlwe_basis = 256;  
    // stddev_simul approx  2**(19.28)
    double stddev_simul = 638072;  

    // 2**13
    masking_size = 14936;
    // stddev_simul approx  2**(14)
    stddev_masking = 16384;

    std::shared_ptr<RLWEParam> rlwe_par(new RLWEParam(negacyclic, N, Q, ternary, any, rlwe_stddev, hexl_ntt)); 
    Gadget deter_gadget = Gadget(N, Q, rlwe_basis * rlwe_basis, signed_decomposition_gadget); 
    Gadget rand_gadget = Gadget(N, Q, rlwe_basis, stddev_simul, discrete_gaussian_gadget); 
    rlwe_gadget_par = RLWEGadgetParam(rlwe_par, rlwe_basis, deter_gadget, rand_gadget); 
    sk_arithmetic = hexl_ntt; 

    
 
    int n = 950;
    // 2**9
    int lwe_basis = 512; 
    // 2**(23) 
    double lwe_stddev = 262144;
    //LWEParam lwe_par(n, Q, binary, lwe_stddev);
    lwe_gadget_par = LWEGadgetParam(std::shared_ptr<LWEParam>(new LWEParam(n, Q, binary, lwe_stddev)), lwe_basis); 

    default_encoding = PlaintextEncoding(partial_domain, 16, Q);
    std::cout << "Finished initializing" << std::endl;
} 
