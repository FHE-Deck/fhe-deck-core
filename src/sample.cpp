/*
PLEASE DO NOT DISTRIBUTE!!! This version is for review only. 
*/

#include "../include/sample.h"
 

sample::sample(){ 
    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937_64 e(seed);
    e1 = e; 
}

sample::sample(double expectation, double stddev){ 
    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937_64 e(seed); 
    e1 = e; 
    this->expectation = expectation;
    this->stddev = stddev;
    this->normal_dist = std::normal_distribution<double>(expectation, stddev);
}

 

long sample::binary(){
    std::uniform_int_distribution<long> binary_uniform(0, 1);
    return binary_uniform(e1);
}



long sample::ternary(){
    std::uniform_int_distribution<long> binary_uniform(0, 2);
    long result = binary_uniform(e1);
    if(result == 2){
        result = -1;
    }
    return result;
}

long sample::gaussian(double expectation, double stddev){
    std::normal_distribution<double> normal_dist(expectation, stddev);
    return (long)round(normal_dist(e1));
}


long sample::gaussian(long q, double expectation, double stddev){
    std::normal_distribution<double> normal_dist(expectation, stddev);
    // TODO: Round to nearest multiple of q
    // For now -> Actually, this should be a propper Gaussian sampler!
    long u = (long)round(normal_dist(e1));
    // q is a power of two so we mask
    long r = u & (q-1);
    if(r < (q>>2)){
        return u - r;
    } 
    return u - r + q;
}


long sample::gaussian(long q){ 
    // TODO: Round to nearest multiple of q
    // For now -> Actually, this should be a propper Gaussian sampler!
    long u = (long)round(normal_dist(e1));
    // q is a power of two so we mask
    long r = u & (q-1);
    if(r < (q>>2)){
        return u - r;
    } 
    return (u - r) + q;
}
  


long sample::uniform(long Q){
    std::uniform_int_distribution<long> binary_uniform(0, Q-1);
    return binary_uniform(e1);
}

void sample::binary_array(long *a, int n){
    for(int i = 0; i < n; ++i){
        a[i] = binary();
    }
}

void sample::ternary_array(long *a, int n){
    for(int i = 0; i < n; ++i){
        a[i] = ternary();
    }
}

void sample::gaussian_array(long *a, int n, double expectation, double stddev){
    for(int i = 0; i < n; ++i){
        a[i] = gaussian(expectation, stddev);
    }
}

void sample::uniform_array(long *a, int n, long Q){
    for(int i = 0; i < n; ++i){
        a[i] = uniform(Q);
    }
}