/*
PLEASE DO NOT DISTRIBUTE!!! This version is for review only. 
*/


#include <iostream>
#include "../include/lwe.h"
#include "../include/lwe_param.h"
#include <NTL/ZZX.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_p.h>
#include <random>


void basic_lwe_test(){ 
   std::cout << "========= Testing LWE ============" << std::endl;
    
    int n = 10;
    long Q = 1073741827; 
    double stddev = 3.2;
    lwe_sk lwe(n, Q, stddev, binary); 
    lwe_param param = lwe.get_lwe_param(); 

    long t = 8;
    long delta_Q_t = (long)round((double)Q/(double)t);
    long msg = 2;
    long scaled_msg = delta_Q_t * msg;

    // long *ct = new long[param.n+1];
    long *ct = lwe.encrypt(scaled_msg);
    //std::cout << "Testing the phase etc.. " << std::endl;
    long phase = lwe.phase(ct);
    long error = lwe.error(ct, scaled_msg);
    long dec = lwe.decrypt(ct, t);
    //std::cout << "Phase: " << phase << std::endl;
    //std::cout << "Error: " << error << std::endl;
    //std::cout << "Decrypt: " << dec << std::endl;
     
    if(dec == msg){
        std::cout << "Basic LWE Decryption Test: OK" << std::endl; 
    }else{
        std::cout << "Basic LWE Decryption Test: Fail" << std::endl; 
    }
 
    long scalar = 3;
    long *ct_mul = new long[param.n+1];
    param.scalar_mul(ct_mul, ct, scalar);
    long scalar_dec = lwe.decrypt(ct_mul, t); 
    long expected = (msg * scalar) % t;
    long scalar_error = lwe.error(ct_mul, expected * delta_Q_t);
    if(scalar_dec == expected){
        std::cout << "Scalar Multiplication Test: OK" << std::endl; 
    }else{
        std::cout << "Scalar Multiplication Test: Fail" << std::endl; 
        std::cout << "scalar_dec: " << scalar_dec << std::endl; 
        std::cout << "scalar_error: " << scalar_error << std::endl;
    }


    // TODO Test Addition
    //long *ct_1 = new long[param.n+1];
    //long *ct_2 = new long[param.n+1];
    long m_1 = 2;
    long m_2 = 3;
    long *ct_1 = lwe.encrypt(delta_Q_t * m_1);
    long *ct_2 = lwe.encrypt(delta_Q_t * m_2);
    long *ct_added = new long[param.n+1];
    param.add(ct_added, ct_1, ct_2);
    long added_expected = (m_1 + m_2) % t;
    long added_dec = lwe.decrypt(ct_added, t);
    if(added_expected == added_dec){
        std::cout << "LWE Add Test: OK" << std::endl; 
    }else{
        std::cout << "LWE Add Test: Fail" << std::endl; 
        std::cout << "added_expected: " << added_expected << std::endl; 
        std::cout << "added_dec: " << added_dec << std::endl; 
    }
    
}


void gadget_multiplication_test(){
    std::cout << "========= gadget_multiplication_test ============" << std::endl;
    
    int n = 10;
    long Q = 1073741827; 
    double stddev = 3.2;
    lwe_sk lwe(n, Q, stddev, binary); 
    lwe_param param = lwe.get_lwe_param(); 
      
    long t = 8;
    long delta_Q_t = (long)round((double)Q/(double)t);
    long msg = 2;
    long scaled_msg = delta_Q_t * msg;
    long gadget_msg = 3;

   // int k = 3;
   // 2**3
   int basis = 8;
   // From python
   // 11 = math.ceil(math.log(1073741827, 8))
   //int ell = 11;
   lwe_gadget_param lwe_g_par(param, basis);
   lwe_gadget_sk lwe_g(lwe_g_par, lwe);

/*
    long **gadget_ct = new long*[ell];
    for(int i = 0; i < ell; ++i){
        gadget_ct[i] = new long[param.n+1];
    } 
*/
    long **gadget_ct = lwe_g.gadget_encrypt(gadget_msg);
    long *ct = param.init_ct();
    lwe_g_par.gadget_mul(ct, gadget_ct, scaled_msg);
    long dec = lwe.decrypt(ct, t);
    long expected = (msg * gadget_msg) % t;
    if(dec == expected){
        std::cout << "Gadget Multiplication Test: OK" << std::endl;
    }else{
        std::cout << "Gadget Multiplication Test: Fail" << std::endl;
        std::cout << "expected: " <<  expected << std::endl;
        std::cout << "dec: " <<  dec << std::endl;
    }

}

void mod_switching_test(){

    std::cout << "========= mod_switching_test ============" << std::endl;
    
    int n = 10;
    long Q = 1073741827; 
    double stddev = 3.2;
    lwe_sk lwe(n, Q, stddev, binary); 
    lwe_param param = lwe.get_lwe_param(); 
 

    long t = 8;
    long delta_Q_t = (long)round((double)Q/(double)t);
    long msg = 2;
    long scaled_msg = delta_Q_t * msg;
 
    long *ct = lwe.encrypt(scaled_msg); 
    long dec = lwe.decrypt(ct, t);  
     
    if(dec == msg){
        std::cout << "Basic LWE Decryption Test: OK" << std::endl; 
    }else{
        std::cout << "Basic LWE Decryption Test: Fail" << std::endl; 
    }

    long new_Q = 1073741827;
    
    long delta_new_Q_t = (long)round((double)new_Q/(double)t);
    lwe_param new_param = param.modulus_switch(new_Q); 
    long *new_ct = param.init_ct();
    param.switch_modulus(new_ct, ct, new_param);
    long new_dec = lwe.decrypt(new_ct, t);  
    if(new_dec == msg){
        std::cout << "LWE Decryption After Modulus Switching Test: OK" << std::endl; 
    }else{
        std::cout << "LWE Decryption After Modulus Switching Test: Fail" << std::endl; 
        std::cout << "new_dec: " << new_dec << ", msg: " << msg << std::endl;
    }
}


int main(){
 
    basic_lwe_test();
    gadget_multiplication_test();
    mod_switching_test();
}