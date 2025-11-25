 
#ifndef SAMPLE_H
#define SAMPLE_H



/**
 * @file sample.h
 */

#include "global_headers.h"
#include "math/polynomial.h"
 
namespace FHEDeck{
 
class Distribution{

    public: 
    virtual int64_t next() = 0;
      
    void fill(std::vector<int64_t>& in); 
    
    void fill(VectorArray& in); 

    void fill(VectorView& in); 

};
 
class StandardUniformIntegerDistribution : public Distribution{

    public: 
    std::uniform_int_distribution<int64_t> dist;
    std::mt19937_64 e;

    StandardUniformIntegerDistribution(int64_t from, int64_t to);
  
    int64_t next(); 
};


class StandardRoundedGaussianDistribution : public Distribution{

    public: 
    std::normal_distribution<double> dist;
    std::mt19937_64 e;

    StandardRoundedGaussianDistribution(double expectation, double stddev);
  
    int64_t next(); 
};
 
} /// End of namespace FHEDeck

#endif