
#ifndef GADGET_H
#define GADGET_H

#include "utils.h" 
#include "sample.h"

class gadget{


    public: 

    gadget_type type;

    int basis;
    int ell;
    int k;  
    bool is_power_of_base_modulus;

    int N;
    long Q;
  
    sampler rand;
    double stddev;


    // Tables/values precomputed for genralized Gaussian sampling from [EC:GenMic18]. We are use the smae notation as in the paper, except that I use q_decomp instead of q ofor the decomposition of the modulus Q.
    long* q_decomp;
    double sigma;
    sampler rand_sigma;
    double* sigmas;
    sampler* rand_sigmas;
    long r;
    double* l;
    double* h;
    double* d;
    double d_stddev;
    sampler rand_d_stddev;
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


    
 
    ~gadget();

    gadget() = default;

    gadget(int N, long Q, int basis, gadget_type type);

    gadget(int N, long Q, int basis, double stddev, gadget_type type);

   gadget(const gadget &other);

    gadget& operator=(const gadget other);
 

    void setup_type_specific_parameters(); 

    void sample(long** out, long *in);

    long** sample(long *in);

    long* get_gadget_vector();

    long** init_out();

    void delete_out(long** out);

    private:

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



    template <class Archive>
    void save( Archive & ar ) const
    { 
        ar(type, N, Q, basis);   
        if(type == discrete_gaussian_gadget){
            ar(stddev);
        } 
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
        ar(type, N, Q, basis);
        if(type == discrete_gaussian_gadget){
            ar(stddev);
            this->rand = sampler(0.0, stddev);
        } 
    } 


};

#endif