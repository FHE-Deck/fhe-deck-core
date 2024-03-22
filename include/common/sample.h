 
#ifndef SAMPLE_H
#define SAMPLE_H

#include <random>


namespace fhe_deck{


// DEPRECATED 
class Sampler{
 
    //private: 
    public:

        std::mt19937_64 e1;  

        double expectation;
        double stddev;

        // TODO: Need to do some order here (neverhteless as sampling is done now its quite terrible because I instantiate a new object in each function)
        long n_binomial;
        double p_binomial;
        std::normal_distribution<double> normal_dist;
        std::binomial_distribution<long> binomial_dist;

     
        Sampler();

        Sampler(double expectation, double stddev);
  
        long binary(); 

        long ternary(); 

        long gaussian(double expectation, double stddev);

        // If the output Gaussian is supposed to be from q \mathbb{Z} - Gaussian distributed multiple of q
        long gaussian(long q, double expectation, double stddev);

        // Returns a multiple of q
        long gaussian(long q);
   
        long uniform(long Q);

        void binary_array(long *a, int n); 

        void ternary_array(long *a, int n); 

        void gaussian_array(long *a, int n, double expectation, double stddev);

        void uniform_array(long *a, int n, long Q); 
};


class Distribution{

    public: 
    virtual long next() = 0;
    
    void fill_array(long *in, int length); 

};


class StandardUniformIntegerDistribution : public Distribution{

    public: 
    std::uniform_int_distribution<long> dist;
    std::mt19937_64 e;

    StandardUniformIntegerDistribution(long from, long to);
  
    long next();

};


class StandardRoundedGaussianDistribution : public Distribution{

    public: 
    std::normal_distribution<double> dist;
    std::mt19937_64 e;

    StandardRoundedGaussianDistribution(double expectation, double stddev);
  
    long next();


};


}

#endif