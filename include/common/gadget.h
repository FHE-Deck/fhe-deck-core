
#ifndef GADGET_H
#define GADGET_H
 
/**
 * @file gadget.h
 */
 
#include "common/utils.h" 
#include "common/sample.h"
#include "math/vector.h"

#include <complex>
#include <limits>
#include <iostream>

#if defined(USE_CEREAL)
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>
#endif

namespace fhe_deck{


class Gadget{

    public: 
 
    // Decomposition Base
    int64_t base;
    // Number of digits after decomposition
    int32_t digits;
    // number of bits of the base (i.e. smallest k s.t. 2^k >= base) 
    int32_t bits_base;  
    // Degree of the polynomial        
    int32_t degree;
    // Coefficient Modulus
    int64_t modulus;

    /// @deprecated
    virtual void sample(int64_t** out, int64_t *in) = 0;

    virtual void sample(VectorArray& out, int64_t *in) = 0;

    int64_t* get_gadget_vector();

    int64_t** init_out();
   
    void delete_out(int64_t** out);

    #if defined(USE_CEREAL)
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
    #endif 
};

class SignedDecompositionGadget : public Gadget{

    public:
  
    SignedDecompositionGadget() = default;

    SignedDecompositionGadget(int32_t degree, int64_t modulus, int64_t base);

    void sample(int64_t** out, int64_t *in);

    void sample(VectorArray& out, int64_t *in);
 
    void decomp(int64_t **d_ct, int64_t* poly);

    void init();

  #if defined(USE_CEREAL)
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
  #endif 
  
};


 

class DiscreteGaussianSamplingGadget : public Gadget{

    public: 

    bool is_power_of_base_modulus;

    //Sampler rand;
    double stddev;

    int32_t ell_minus_one;

    // Tables/values precomputed for genralized Gaussian sampling from [EC:GenMic18]. We are use the smae notation as in the paper, except that I use q_decomp instead of q ofor the decomposition of the modulus Q.
    int64_t* q_decomp;
    double sigma;
    
    double* sigmas;
    
    int64_t r;
    double* l;
    double* h;
    double* d;
    double d_stddev;
    
    // Tail bound parameter
    // For the generalized Gaussian sampler we need to set this tail bound parameters (for now compute without tail bound)
    int64_t tail_bound;
    double inv_basis;
    double* inv_l;
    int64_t two_times_basis_plus_one;  
    // Precomputed temp variables for general modulus Gaussian Sampling
    int64_t* p;
    double* c;
    int64_t* u;
    int64_t* z;
    // Stuff for perturb_B
    double* c_pert;
    int64_t* z_pert;

    bool is_precomputed = false;
 
    // Precomputed temp arrays for determinitic decomp 
    bool is_deter_temp_init = false;
    int64_t* signed_poly; 
    int64_t* sign;
 
    // Precomputed temp variables for power_of_two Gaussian Sampling   
    bool is_power_of_basis_gaussian_temp_init = false;
    int64_t* gaussians;
    int64_t mask; 
    int64_t shift; 
    int64_t prev_gauss;

  
    /// xorshift state
    int64_t xorshift_s;
    // The xoshiro256+ state
    int64_t* xoshiro256_s;
    int64_t xoshiro256_t;

    uint64_t xoshiro256_result;
    uint64_t xoshiro_mask = 0x1fffffffffffff;

    uint32_t xoshiro256_25_result_1;
    uint32_t  xoshiro256_25_result_2;
   
 
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

    DiscreteGaussianSamplingGadget(int32_t degree, int64_t modulus, int64_t base, double stddev);

    void sample(int64_t** out, int64_t *in);
 
    void sample(VectorArray& out, int64_t *in);

  #if defined(USE_CEREAL)
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
    #endif 

  
    private:

    void setup_type_specific_parameters(); 

    void decomp(int64_t **d_ct, int64_t* poly);

    void signed_decomp(int64_t **d_ct, int64_t* poly);

    void gaussian_sample(int64_t **out, int64_t* in);
  
    void gaussian_sample_modulus_power_of_base(int64_t **out, int64_t* in);

    void gaussian_sample_general_modulus(int64_t **out, int64_t* in);

    void sample_G(int64_t* out, int64_t in);

    void perturb_B(int64_t* p);

    void sample_D(int64_t* out, double* c);

    int64_t sample_Zt(double stddev, double center);

    void precompute_constants_for_power_of_base_gaussian_sampling();

    void precompute_constants_for_general_modulus_gaussian_sampling();

    void base_decomposition(int64_t* out, int64_t in);

    inline void xorshift64();
 
    int32_t xorshift25();

    inline void xoshiro256p();
    
    inline double gen_gaussian();

    inline float gen_gaussian_float();
  
    /*
        Implements the Karney method
    */
    inline int64_t gen_discrete_gauss(float c);
 
    inline int32_t d1_d2_of_karney();
 
  
};
 
}/// End namespace fhe_deck
 
#if defined(USE_CEREAL)
CEREAL_REGISTER_TYPE(fhe_deck::SignedDecompositionGadget)
CEREAL_REGISTER_TYPE(fhe_deck::DiscreteGaussianSamplingGadget) 
#endif


#endif