 
#include "../include/sample.h"
 

sampler::sampler(){ 
    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937_64 e(seed);
    e1 = e; 
}

sampler::sampler(double expectation, double stddev){ 
    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937_64 e(seed);  
    e1 = e; 
    this->expectation = expectation;
    this->stddev = stddev;
    this->normal_dist = std::normal_distribution<double>(expectation, stddev);
}

 

long sampler::binary(){
    std::uniform_int_distribution<long> binary_uniform(0, 1);
    return binary_uniform(e1);
}



long sampler::ternary(){
    std::uniform_int_distribution<long> binary_uniform(0, 2);
    long result = binary_uniform(e1);
    if(result == 2){
        result = -1;
    }
    return result;
}

long sampler::gaussian(double expectation, double stddev){
    // Bloddy hell!!! new instantiation (new object every iteration!!! Bloddy Hell!)
    std::normal_distribution<double> normal_dist(expectation, stddev);
    return (long)normal_dist(e1);
}


long sampler::gaussian(long q, double expectation, double stddev){
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


long sampler::gaussian(long q){  
    long u = (long)round(normal_dist(e1));
    return q * u; 
    // Round to nearest multiple of q
    // q is a power of two so we mask
    /*
    long r = u & (q-1);
    if(r < (q>>2)){
        return u - r;
    } 
    return (u - r) + q;
    */
}
  


long sampler::uniform(long Q){
    std::uniform_int_distribution<long> binary_uniform(0, Q-1);
    return binary_uniform(e1);
}

void sampler::binary_array(long *a, int n){
    for(int i = 0; i < n; ++i){
        a[i] = binary();
    }
}

void sampler::ternary_array(long *a, int n){
    for(int i = 0; i < n; ++i){
        a[i] = ternary();
    }
}

void sampler::gaussian_array(long *a, int n, double expectation, double stddev){
    for(int i = 0; i < n; ++i){
        a[i] = gaussian(expectation, stddev);
    }
}

void sampler::uniform_array(long *a, int n, long Q){
    for(int i = 0; i < n; ++i){
        a[i] = uniform(Q);
    }
}