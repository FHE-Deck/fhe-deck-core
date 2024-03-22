#include "fhe_configuration.h"

using namespace fhe_deck;

 
/*
=========================================================== TFHEKeyGenerator (Named Parameters) =================================================

*/

FHEConfiguration::FHEConfiguration(FHENamedParams name){
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
        // TODO: Should be an exception!
        std::cout << "TFHEKeyGenerator::TFHEKeyGenerator: No parameter set selected!" <<  std::endl;
    }
}
  

void FHEConfiguration::generate_bootstapping_keys(){
    this->boot_sk = std::unique_ptr<FunctionalBootstrapSecretKey>(new FunctionalBootstrapSecretKey(rlwe_gadget_par, lwe_gadget_par, masking_size, stddev_masking, default_encoding, fdfb_alg)); 
    this->boot_pk = boot_sk->get_public_param(); 
} 

FunctionalBootstrapSecretKey FHEConfiguration::generate_secret_key(){
    return FunctionalBootstrapSecretKey(rlwe_gadget_par, lwe_gadget_par, masking_size, stddev_masking, default_encoding, fdfb_alg);
}
 
   
void FHEConfiguration::init_tfhe_11_NTT(){ 
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
    rlwe_gadget_par = std::shared_ptr<RLWEGadgetParam>(new RLWEGadgetParam(rlwe_par, rlwe_basis, deter_gadget, rand_gadget)); 
    //sk_arithmetic = hexl_ntt;

    // 2**9 + 400
    int n = 912;
    // 2**7
    int lwe_basis = 128;
    // 2**(26) 
    double lwe_stddev = 67108864;
    //LWEParam lwe_par(n, Q, binary, lwe_stddev);
    lwe_gadget_par = LWEGadgetParam(std::shared_ptr<LWEParam>(new LWEParam(n, Q, binary, lwe_stddev)), lwe_basis); 

    default_encoding = PlaintextEncoding(full_domain, 4, Q);
    fdfb_alg = liu_micciancio_polyakov;
} 
 

void FHEConfiguration::init_tfhe_11_NTT_flood(){ 
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
    rlwe_gadget_par = std::shared_ptr<RLWEGadgetParam>(new RLWEGadgetParam(rlwe_par, rlwe_basis, deter_gadget, rand_gadget)); 
    
    //sk_arithmetic = ntl;

    // 2**9 + 400
    int n = 912;
    int lwe_basis = 128;
    // 2**(26)
    double lwe_stddev = 67108864; 
    
    lwe_gadget_par = LWEGadgetParam(std::shared_ptr<LWEParam>(new LWEParam(n, Q, binary, lwe_stddev)), lwe_basis); 

    default_encoding = PlaintextEncoding(full_domain, 4, Q); 
    fdfb_alg = liu_micciancio_polyakov;
} 



// Power of two parameter set
void FHEConfiguration::init_tfhe_11_B(){ 
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
    rlwe_gadget_par = std::shared_ptr<RLWEGadgetParam>(new RLWEGadgetParam(rlwe_par, rlwe_basis, deter_gadget, rand_gadget));  
   //sk_arithmetic = double_fft;

    // 2**9 + 430
    int n = 912;
    int lwe_basis = 128;
    // 2**(14)
    double lwe_stddev = 16384; 
    //LWEParam lwe_par(n, Q, binary, lwe_stddev);
    lwe_gadget_par = LWEGadgetParam(std::shared_ptr<LWEParam>(new LWEParam(n, Q, binary, lwe_stddev)), lwe_basis); 

    default_encoding = PlaintextEncoding(full_domain, 4, Q); 
    fdfb_alg = liu_micciancio_polyakov;
} 

 
void FHEConfiguration::init_tfhe_11_flood(){ 
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
    rlwe_gadget_par = std::shared_ptr<RLWEGadgetParam>(new RLWEGadgetParam(rlwe_par, rlwe_basis, deter_gadget, rand_gadget)); 
    //sk_arithmetic = double_fft;

    // 2**9 + 430
    int n = 912;
    int lwe_basis = 128;
    // 2**(14) 
    double lwe_stddev = 16384;
    
    lwe_gadget_par = LWEGadgetParam(std::shared_ptr<LWEParam>(new LWEParam(n, Q, binary, lwe_stddev)), lwe_basis); 

    default_encoding = PlaintextEncoding(full_domain, 4, Q); 
    fdfb_alg = liu_micciancio_polyakov;
} 

 


void FHEConfiguration::init_tfhe_11_NTT_amortized(){ 
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
    rlwe_gadget_par = std::shared_ptr<RLWEGadgetParam>(new RLWEGadgetParam(rlwe_par, rlwe_basis, deter_gadget, rand_gadget)); 
    //sk_arithmetic = hexl_ntt;
 
    int n = 950;
    // 2**9
    int lwe_basis = 512;
    // 2**(23) 
    double lwe_stddev = 262144;
    //LWEParam lwe_par(n, Q, binary, lwe_stddev);
    lwe_gadget_par = LWEGadgetParam(std::shared_ptr<LWEParam>(new LWEParam(n, Q, binary, lwe_stddev)), lwe_basis); 

    default_encoding = PlaintextEncoding(partial_domain, 8, Q); 
    fdfb_alg = liu_micciancio_polyakov;
} 




void FHEConfiguration::init_tfhe_12_NTT_amortized(){  
    // 2**12
    int N = 4096; 
    // (2**51 - 131071) % 2*(2**12) = 1 and prime (NTT Friendly),   
    //long Q = 2251799813554177;
    // 52-bit modulus
    //long Q = 4503599627149313;
    // 53-bit modulus
    //long Q = 9007199254429697;
    // 54-bit modulus
    long Q =  18014398509309953;
 


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
    rlwe_gadget_par = std::shared_ptr<RLWEGadgetParam>(new RLWEGadgetParam(rlwe_par, rlwe_basis, deter_gadget, rand_gadget)); 
    //sk_arithmetic = hexl_ntt; 

    int n = 950;
    // 2**9
    int lwe_basis = 512; 
    // 2**(23) 
    double lwe_stddev = 262144;
    //LWEParam lwe_par(n, Q, binary, lwe_stddev);
    lwe_gadget_par = LWEGadgetParam(std::shared_ptr<LWEParam>(new LWEParam(n, Q, binary, lwe_stddev)), lwe_basis); 

    default_encoding = PlaintextEncoding(partial_domain, 16, Q); 
    fdfb_alg = liu_micciancio_polyakov;
} 
