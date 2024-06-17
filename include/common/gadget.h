
#ifndef GADGET_H
#define GADGET_H

#include "utils.h" 
#include "sample.h"

#include <complex>
#include <limits>
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>

namespace fhe_deck{


class Gadget{

    public: 
 
    // Decomposition Base
    long base;
    // Number of digits after decomposition
    int digits;
    // number of bits of the base (i.e. smallest k s.t. 2^k >= base) 
    int bits_base;  
    // Degree of the polynomial        
    int degree;
    // Coefficient Modulus
    long modulus;

    virtual void sample(long** out, long *in) = 0;

    long* get_gadget_vector();

    long** init_out();

    void delete_out(long** out);

    template <class Archive>
    void save( Archive & ar ) const
    {  
      ar(degree, modulus, base);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {    
        ar(degree, modulus, base);  
    }  
};

class SignedDecompositionGadget : public Gadget{

    public:
  
    SignedDecompositionGadget() = default;

    SignedDecompositionGadget(int degree, long modulus, long base);

    void sample(long** out, long *in);
 
    void decomp(long **d_ct, long* poly);

    void init();

    template <class Archive>
    void save( Archive & ar ) const
    {  
      ar(cereal::base_class<Gadget>(this));   
    }
        
    template <class Archive>
    void load( Archive & ar )
    {    
       ar(cereal::base_class<Gadget>(this));   
        init(); 
    }  
  
};


 

class DiscreteGaussianSamplingGadget : public Gadget{

    public: 

    bool is_power_of_base_modulus;

    //Sampler rand;
    double stddev;

    int ell_minus_one;

    // Tables/values precomputed for genralized Gaussian sampling from [EC:GenMic18]. We are use the smae notation as in the paper, except that I use q_decomp instead of q ofor the decomposition of the modulus Q.
    long* q_decomp;
    double sigma;
    
    double* sigmas;
    
    long r;
    double* l;
    double* h;
    double* d;
    double d_stddev;
    
    // Tail bound parameter
    // For the generalized Gaussian sampler we need to set this tail bound parameters (for now compute without tail bound)
    long tail_bound;
    double inv_basis;
    double* inv_l;
    long two_times_basis_plus_one;  
    // Precomputed temp variables for general modulus Gaussian Sampling
    long* p;
    double* c;
    long* u;
    long* z;
    // Stuff for perturb_B
    double* c_pert;
    long* z_pert;

    bool is_precomputed = false;
 
    // Precomputed temp arrays for determinitic decomp 
    bool is_deter_temp_init = false;
    long* signed_poly; 
    long* sign;
 
    // Precomputed temp variables for power_of_two Gaussian Sampling   
    bool is_power_of_basis_gaussian_temp_init = false;
    long* gaussians;
    long mask; 
    long shift; 
    long prev_gauss;

  
    /// xorshift state
    long xorshift_s;
    // The xoshiro256+ state
    long* xoshiro256_s;
    long xoshiro256_t;

    unsigned long xoshiro256_result;
    unsigned long xoshiro_mask = 0x1fffffffffffff;

    unsigned int xoshiro256_25_result_1;
    unsigned int xoshiro256_25_result_2;
   
 
    double u1;
    double u2;

    float u1_float;
    float u2_float;
    float spare_float;

    const float minus_half = -0.5;

    // Variable to compute the Gaussian 
    const double two_pi = 2.0 * M_PI;
    const double div_const_u1 = 1.0/9007199254740992.0;
    const double div_const_u2  = 1.0/9007199254740992.0 * 2.0 * M_PI;
    
    const float div_const_u1_float = 1.0f/33554432.0f;
    const float div_const_u2_float  = 1.0f/33554432.0f * 2.0f * (float)(M_PI);
 

    double spare;
    bool hasSpare = false;
 
 

    ~DiscreteGaussianSamplingGadget();

    DiscreteGaussianSamplingGadget() = default;

    DiscreteGaussianSamplingGadget(int degree, long modulus, long base, double stddev);

    void sample(long** out, long *in);
 

    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(cereal::base_class<Gadget>(this));   
      ar(stddev);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(cereal::base_class<Gadget>(this));   
      ar(stddev);  
       setup_type_specific_parameters(); 
    } 

  
    private:

    void setup_type_specific_parameters(); 

    void decomp(long **d_ct, long* poly);

    void signed_decomp(long **d_ct, long* poly);

    void gaussian_sample(long **out, long* in);
  
    void gaussian_sample_modulus_power_of_base(long **out, long* in);

    void gaussian_sample_general_modulus(long **out, long* in);

    void sample_G(long* out, long in);

    void perturb_B(long* p);

    void sample_D(long* out, double* c);

    long sample_Zt(double stddev, double center);

    void precompute_constants_for_power_of_base_gaussian_sampling();

    void precompute_constants_for_general_modulus_gaussian_sampling();

    void base_decomposition(long* out, long in);

    inline void xorshift64();
 
    int xorshift25();

    inline void xoshiro256p();
    
    inline double gen_gaussian();

    inline float gen_gaussian_float();
  
    /*
        Implements the Karney method
    */
    inline long gen_discrete_gauss(float c);
 
    inline int d1_d2_of_karney();
 
  
};
 
}/// End namespace fhe_deck
 
CEREAL_REGISTER_TYPE(fhe_deck::SignedDecompositionGadget)
CEREAL_REGISTER_TYPE(fhe_deck::DiscreteGaussianSamplingGadget) 



#endif