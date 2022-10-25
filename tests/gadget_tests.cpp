#include <iostream>
#include "../include/gadget.h"




void gadget_sampling_correctness_test(int test_num, int N, long Q, int base, double stddev, gadget_type type){
    std::cout << "============ gadget_sampling_correctness_test ==========" << std::endl; 
    sampler rand;
    //int N = 64;
    //long Q = 512;
    //int basis = 8;
    gadget g;
    if(type == signed_decomposition_gadget){ 
        std::cout << "Testing: signed_decomposition_gadget" << std::endl;
        g = gadget(N, Q, base,  type); 
    }else if(type == discrete_gaussian_gadget){
        std::cout << "Testing: discrete_gaussian_gadget" << std::endl;
        g = gadget(N, Q, base, stddev, type); 
    } 
    long* gadget_vector = g.get_gadget_vector();  
    long* poly = new long[N];
    long** decomp = g.init_out(); 
    unsigned long* result = new unsigned long[N]; 
    long temp;
    for(int k = 0; k < test_num; ++k){
        // Choose some random poly
        rand.uniform_array(poly, N, Q); 
        // Sample
        g.sample(decomp, poly); 
        // Compose back modulo Q, and compare to poly
        for(int i = 0; i < N; ++i){
            result[i] = 0;
            for(int j = 0; j < g.ell; ++j){
                temp = decomp[j][i];
                for(int k = 0; k < j; ++k){
                    temp *= base;
                    temp %= Q;
                } 
                //result[i] +=  gadget_vector[j] * decomp[j][i]; 
                result[i] += temp;
            }
        }
        utils::array_mod_form((long*)result, (long*)result, N, Q); 
        if(!utils::is_eq_poly((long*)result, poly, N)){  
            std::cout << "gadget_sampling_correctness_test: Fail at k: " << k << std::endl; 
            std::cout << "ell: " << g.ell << std::endl;
            std::cout << "Q: " << Q << std::endl;
            std::cout << "poly: " << utils::to_string(poly, N) << std::endl;
            std::cout << "result: " << utils::to_string((long*)result, N) << std::endl;
            for(int i = 0; i < g.ell; ++i){
                std::cout << "decomp[" << i << "]: " << utils::to_string(decomp[i], N) << std::endl;
            }
            std::cout << "Let recreate the error: " << std::endl;
            for(int i = 0; i < N; ++i){
                result[i] = 0;
                for(int j = 0; j < g.ell; ++j){
                    std::cout << "gadget_vector[" << j << "]: " << gadget_vector[j] << std::endl;
                    std::cout << "decomp[" << j << "][i]: " << decomp[j][i] << std::endl;
                    result[i] +=  gadget_vector[j] * decomp[j][i]; 
                    std::cout << "result[" << i << "]: " << result[i] << std::endl;
                } 
            }
            utils::array_mod_form((long*)result, (long*)result, N, Q);
            return;
        } 
    } 
    g.delete_out(decomp);
    delete[] gadget_vector;
    delete[] poly;
    delete[] result; 
    std::cout << "gadget_sampling_correctness_test: OK" << std::endl;  
}


void general_modulus_gaussian_samping_precomputed_values_test(){
    std::cout << "============ general_modulus_gaussian_samping_precomputed_values_test ==========" << std::endl; 
    sampler rand;
    int N = 64;
    long Q = 2048;
    int basis = 8;
    gadget g = gadget(N, Q, basis, 16.0, discrete_gaussian_gadget);  

    std::cout << "g.ell: " << g.ell << std::endl;
    // Test l and h
    if(g.l[0] * g.l[0] + g.h[1] * g.h[1] != g.r * g.r - g.basis * g.basis){
        std::cout << "- Fail at: g.l[0] * g.l[0] + g.h[1] * g.h[1] != g.r * g.r - g.basis * g.basis!" << std::endl;
        std::cout << "Left: " << g.l[0] * g.l[0] + g.h[1] * g.h[1] << std::endl;
        std::cout << "Right: " <<  g.r * g.r - g.basis * g.basis << std::endl;
        std::cout << "g.l[0]: " << g.l[0] << std::endl;
        std::cout << "g.h[1]: " << g.h[1] << std::endl;
        std::cout << "g.r: " << g.r << std::endl;
        std::cout << "g.basis: " << g.basis << std::endl;
        //return;
    }
    for(int i = 1; i < g.ell-1; ++i){
        if(g.l[i] * g.l[i] + g.h[i] * g.h[i] != g.r * g.r - (g.basis * g.basis - 1)){
            std::cout << "- Fail at: g.l[i] * g.l[i] + g.h[i] * g.h[i] != g.r * g.r - (g.basis * g.basis - 1)! in i:" << i << std::endl;
            std::cout << "Left: " << g.l[i] * g.l[i] + g.h[i] * g.h[i] << std::endl;
            std::cout << "Right: " <<  g.r * g.r - (g.basis * g.basis - 1) << std::endl;
            std::cout << "g.l[i]: " << g.l[i] << std::endl;
            std::cout << "g.h[i]: " << g.h[i] << std::endl;
            std::cout << "g.r: " << g.r << std::endl;
            std::cout << "g.basis: " << g.basis << std::endl;
        }

        if(g.l[i] * g.h[i] != g.basis){
            std::cout << "- Fail at: g.l[i] * g.h[i] != g.basis! in i:" << i << std::endl;
            std::cout << "Left: " << g.l[i] * g.h[i] << std::endl;
            std::cout << "Right: " <<  g.basis << std::endl;
            std::cout << "g.l[i]: " << g.l[i] << std::endl;
            std::cout << "g.h[i]: " << g.h[i] << std::endl; 
            std::cout << "g.basis: " << g.basis << std::endl;
        }
    }
    if(g.l[g.ell-1] * g.l[g.ell-1]  != g.r * g.r - g.basis * g.basis){
        std::cout << "- Fail at: g.l[g.ell-1] * g.l[g.ell-1]  != g.r * g.r - g.basis * g.basis!" << std::endl;
        std::cout << "Left: " << g.l[g.ell-1] * g.l[g.ell-1] << std::endl;
        std::cout << "Right: " <<  g.r * g.r - g.basis * g.basis << std::endl;
        std::cout << "g.l[g.ell-1] : " << g.l[g.ell-1]  << std::endl; 
        std::cout << "g.r: " << g.r << std::endl;
        std::cout << "g.basis: " << g.basis << std::endl;
        //return;
    }

    // test d
    if(g.d[0] *  g.basis != g.q_decomp[0]){
        std::cout << "- Fail at: g.d[i] *  g.basis  != g.q_decomp[i]! in i:" << 0 << std::endl;
        std::cout << "Left: " << g.d[0] *  g.basis << std::endl;
        std::cout << "Right: " <<  g.q_decomp[0] << std::endl;
        std::cout << "g.d[0]: " << g.d[0] << std::endl;
        std::cout << "g.q_decomp[i]: " << g.q_decomp[0] << std::endl; 
        std::cout << "g.basis: " << g.basis << std::endl;
    } 
    for(int i = 1; i < g.ell-1; ++i){
        if(g.d[i] *  g.basis - g.d[i-1] != g.q_decomp[i]){
            std::cout << "- Fail at: g.d[i] *  g.basis  != g.q_decomp[i]! in i:" << i << std::endl;
            std::cout << "Left: " << g.d[i] *  g.basis - g.d[i-1]  << std::endl;
            std::cout << "Right: " <<  g.q_decomp[i] << std::endl;
            std::cout << "g.d[i]: " << g.d[i] << std::endl;
            std::cout << "g.q_decomp[i]: " << g.q_decomp[i] << std::endl; 
            std::cout << "g.basis: " << g.basis << std::endl;
        } 
    } 
}

void printing_outcome(int test_num, int N, long Q, int base, double stddev, gadget_type type){
    std::cout << "============ printing_outcome ==========" << std::endl; 
    sampler rand; 
    gadget g;
    if(type == signed_decomposition_gadget){ 
        std::cout << "Testing: signed_decomposition_gadget" << std::endl;
        g = gadget(N, Q, base,  type); 
    }else if(type == discrete_gaussian_gadget){
        std::cout << "Testing: discrete_gaussian_gadget" << std::endl;
        g = gadget(N, Q, base, stddev, type); 
    } 
    long* gadget_vector = g.get_gadget_vector();  
    long* poly = new long[N];
    long** decomp = g.init_out(); 
    long* signed_decomp = new long[N]; 
    unsigned long* result = new unsigned long[N]; 
    long* decomp_flat = new long[g.ell * g.N];
    long temp;
    for(int k = 0; k < test_num; ++k){
        // Choose some random poly
        rand.uniform_array(poly, N, Q); 
        
        //std::cout << "Test " << k << " - poly: " << utils::to_string(poly, N) << std::endl;
        // Sample
        g.sample(decomp, poly); 
        for(int j = 0; j < g.ell; ++j){
            utils::array_signed_form(signed_decomp, decomp[j], N, Q);
            //std::cout << "decomp[" << j << "]: " << utils::to_string((long*)signed_decomp, N) << std::endl;
        }
        // Compose back modulo Q, and compare to poly
        for(int i = 0; i < N; ++i){
            result[i] = 0;
            for(int j = 0; j < g.ell; ++j){
                temp = decomp[j][i]; 
                decomp_flat[j * N + i]  = decomp[j][i];
                for(int k = 0; k < j; ++k){
                    temp *= base;
                    temp %= Q;
                }  
                result[i] += temp;
            }
        } 
        utils::array_mod_form((long*)result, (long*)result, N, Q); 
        
        if(!utils::is_eq_poly((long*)result, poly, N)){  
            std::cout << "gadget_sampling_correctness_test: Fail at k: " << k << std::endl; 
            std::cout << "ell: " << g.ell << std::endl;
            std::cout << "Q: " << Q << std::endl;
            std::cout << "poly: " << utils::to_string(poly, N) << std::endl;
            std::cout << "result: " << utils::to_string((long*)result, N) << std::endl;
            for(int i = 0; i < g.ell; ++i){
                std::cout << "decomp[" << i << "]: " << utils::to_string(decomp[i], N) << std::endl;
            }
            std::cout << "Let recreate the error: " << std::endl;
            for(int i = 0; i < N; ++i){
                result[i] = 0;
                for(int j = 0; j < g.ell; ++j){
                    std::cout << "gadget_vector[" << j << "]: " << gadget_vector[j] << std::endl;
                    std::cout << "decomp[" << j << "][i]: " << decomp[j][i] << std::endl;
                    result[i] +=  gadget_vector[j] * decomp[j][i]; 
                    std::cout << "result[" << i << "]: " << result[i] << std::endl;
                } 
            }
            utils::array_mod_form((long*)result, (long*)result, N, Q);
            return;
        } 
    } 

    //std::cout << "decomp_flat: " << utils::to_string(decomp_flat, g.ell * g.N) << std::endl;  
    double mean = utils::mean(decomp_flat, g.ell * g.N);
    long max = utils::max(decomp_flat, g.ell * g.N);
    long min = utils::min(decomp_flat, g.ell * g.N); 
    long var = utils::variance(decomp_flat, g.ell * g.N, mean);
    long s = utils::standard_deviation(decomp_flat, g.ell * g.N, mean);
    long positive = utils::count_positive(decomp_flat, g.ell * g.N);
    long negative = utils::count_negative(decomp_flat, g.ell * g.N);
    std::cout << "mean(decomp_flat): " << mean << ", 2**(" << utils::power_times(utils::abs(mean), 2) << ")" << std::endl;
    std::cout << "max(decomp_flat): " << max << ", 2**(" << utils::power_times(utils::abs(max), 2) << ")" << std::endl;
    std::cout << "min(decomp_flat): " << min << ", 2**(" << utils::power_times(utils::abs(min), 2) << ")" << std::endl; 
    std::cout << "positive/negative: " << (double)positive/(double)negative   << std::endl; 
    std::cout << "variance(decomp_flat): " << var << ", 2**(" << utils::power_times(utils::abs(var), 2) << ")" << std::endl;
    std::cout << "standard_deviation(decomp_flat): " << s << ", 2**(" << utils::power_times(utils::abs(s), 2) << ")" << std::endl;

    g.delete_out(decomp);
    delete[] decomp_flat;
    delete[] gadget_vector;
    delete[] poly;
    delete[] result; 
    std::cout << "gadget_sampling_correctness_test: OK" << std::endl;  
}

int main(){
  
    gadget_sampling_correctness_test(100, 64, 512, 8, 0.0, signed_decomposition_gadget);
    gadget_sampling_correctness_test(100, 64, 512, 8, 15, discrete_gaussian_gadget);
    // discrete Gaussian Gadget test with prime modulus
    gadget_sampling_correctness_test(100, 2048, 21001, 8, 15, discrete_gaussian_gadget);
    // NTT prime smaller than 2**32
    gadget_sampling_correctness_test(100, 2048, 4294955009, 256, 15, discrete_gaussian_gadget);
    // NTT prime smaller than 2**33
    gadget_sampling_correctness_test(100, 2048, 8589905921, 1024, 15, discrete_gaussian_gadget);
    // NTT prime smaller than 2**36
    gadget_sampling_correctness_test(100, 2048, 68719464449, 16, 15, discrete_gaussian_gadget); 

    gadget_sampling_correctness_test(100, 2048, 35184372088831, 16, 0, discrete_gaussian_gadget); 

    // Testing Power of base. Q = 2**48 = 256**6
    gadget_sampling_correctness_test(100, 1000, 281474976710656, 256, 225812, discrete_gaussian_gadget); 
 
 
    // Param set rlwe_hom_acc_scheme_C_11_hexl_ntt: 
    printing_outcome(100, 1000, 281474976694273, 256, 225812, discrete_gaussian_gadget); 
        
    
    printing_outcome(100, 1000, 281474976710656, 256, 225812, discrete_gaussian_gadget); 

}