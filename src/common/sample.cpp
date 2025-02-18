#include "common/sample.h"
 

using namespace FHEDeck;
 

void Distribution::fill_array(int64_t *in, int32_t length){
    for(int32_t i = 0; i < length; ++i){
        in[i] = this->next();
    }
}

StandardUniformIntegerDistribution::StandardUniformIntegerDistribution(int64_t from, int64_t to){ 
    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r()};
    e = std::mt19937_64(seed);  
    dist = std::uniform_int_distribution<int64_t>(from, to);
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


int64_t StandardRoundedGaussianDistribution::next(){
    return (int64_t)round(dist(e));
}

