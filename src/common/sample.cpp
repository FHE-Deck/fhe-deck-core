#include "sample.h"
 

using namespace fhe_deck;

Sampler::Sampler(){ 
    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937_64 e(seed);
    e1 = e; 
}

Sampler::Sampler(double expectation, double stddev){ 
    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937_64 e(seed);  
    e1 = e; 
    this->expectation = expectation;
    this->stddev = stddev;
    this->normal_dist = std::normal_distribution<double>(expectation, stddev);
}

 

long Sampler::binary(){
    std::uniform_int_distribution<long> binary_uniform(0, 1);
    return binary_uniform(e1);
}



long Sampler::ternary(){
    std::uniform_int_distribution<long> binary_uniform(0, 2);
    long result = binary_uniform(e1);
    if(result == 2){
        result = -1;
    }
    return result;
}

long Sampler::gaussian(double expectation, double stddev){
    // Bloddy hell!!! new instantiation (new object every iteration!!! Bloddy Hell!)
    std::normal_distribution<double> normal_dist(expectation, stddev);
    return (long)normal_dist(e1);
}


long Sampler::gaussian(long q, double expectation, double stddev){
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


long Sampler::gaussian(long q){  
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
  


long Sampler::uniform(long Q){
    std::uniform_int_distribution<long> binary_uniform(0, Q-1);
    return binary_uniform(e1);
}

void Sampler::binary_array(long *a, int n){
    for(int i = 0; i < n; ++i){
        a[i] = binary();
    }
}

void Sampler::ternary_array(long *a, int n){
    for(int i = 0; i < n; ++i){
        a[i] = ternary();
    }
}

void Sampler::gaussian_array(long *a, int n, double expectation, double stddev){
    for(int i = 0; i < n; ++i){
        a[i] = gaussian(expectation, stddev);
    }
}

void Sampler::uniform_array(long *a, int n, long Q){
    for(int i = 0; i < n; ++i){
        a[i] = uniform(Q);
    }
     
}


void Distribution::fill_array(long *in, int length){
    for(int i = 0; i < length; ++i){
        in[i] = this->next();
    }
}

StandardUniformIntegerDistribution::StandardUniformIntegerDistribution(long from, long to){ 
    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r()};
    e = std::mt19937_64(seed);  
    dist = std::uniform_int_distribution<long>(from, to);
}

long StandardUniformIntegerDistribution::next(){
    return dist(e);
}

StandardRoundedGaussianDistribution::StandardRoundedGaussianDistribution(double expectation, double stddev){ 
    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r()};
    e = std::mt19937_64(seed);  
    dist = std::normal_distribution<double>(expectation, stddev);
}


long StandardRoundedGaussianDistribution::next(){
    return (long)round(dist(e));
}

