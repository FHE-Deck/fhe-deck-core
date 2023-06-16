#include "gadget.h"
 
using namespace fhe_deck;

Gadget::~Gadget(){
    if(is_precomputed){
        delete[] q_decomp;
        delete[] sigmas;
        delete[] l;
        delete[] h;
        delete[] d;
        delete[] inv_l;
        delete[] rand_sigmas;
        // Free the temporary tables:
        delete[] p;
        delete[] c;
        delete[] u; 
        delete[] z;

        delete[] c_pert;
        delete[] z_pert; 
    }
    if(is_deter_temp_init){
        delete[] signed_poly; 
        delete[] sign;
    }
    if(is_power_of_basis_gaussian_temp_init){
        delete[] gaussians;
    }
}

Gadget::Gadget(int N, long Q, int basis, GadgetType type){
    this->type = type;
    this->N = N;
    this->Q = Q;
    this->basis = basis; 
    setup_type_specific_parameters(); 
}
 

Gadget::Gadget(int N, long Q, int basis, double stddev, GadgetType type){
    this->type = type;
    this->stddev = stddev;
    this->N = N;
    this->Q = Q;
    this->basis = basis; 
    setup_type_specific_parameters(); 
}


Gadget::Gadget(const Gadget &other){ 
    this->type = other.type; 
    this->stddev = other.stddev; 
    this->N = other.N; 
    this->Q = other.Q;
    this->basis = other.basis; 
    setup_type_specific_parameters();  
} 
Gadget& Gadget::operator=(const Gadget other){
    if (this == &other)
    {
        return *this;
    } 
    this->type = other.type;
    this->stddev = other.stddev;
    this->N = other.N;
    this->Q = other.Q;
    this->basis = other.basis;  
    setup_type_specific_parameters();  
    return *this;
} 

void Gadget::setup_type_specific_parameters(){
    if(this->type == signed_decomposition_gadget){
        this->k = 1;
        // Compute the k, parameter (remind k is such that 2**k = basis)  
        // meaning that for now we support only power of two basis
        // TODO: Compute these values with functions from utils
        long temp = 2;
        while(temp < basis){
            temp *= 2;
            this->k++;
        }
        this->ell = 1;
        temp = basis; 
        while(temp < Q){
            temp *= basis;
            this->ell++;
        }  
        // Initialize temporary arrays:
        signed_poly = new long[N]; 
        sign = new long[N]; 
        is_deter_temp_init = true;
    }else if(this->type == discrete_gaussian_gadget){ 
        this->rand = Sampler(0.0, this->stddev); 
        if(!Utils::is_power_of(basis, 2)){
            std::cout << "WARNING: Currently only power of two base is supported" << std::endl;
        }
        this->k = Utils::power_times(basis, 2);
        this->ell = Utils::power_times(Q, basis);
        if(Utils::is_power_of(Q, basis)){
            is_power_of_base_modulus = true;
            precompute_constants_for_power_of_base_gaussian_sampling();
        }else{ 
            is_power_of_base_modulus = false;
            precompute_constants_for_general_modulus_gaussian_sampling();
        }  
    }else{
        throw std::logic_error("Most likely wrong gadget type!");
    }
}



void Gadget::sample(long** out, long *in){ 
    if(type == signed_decomposition_gadget){
        signed_decomp(out, in);
    }else if(type == discrete_gaussian_gadget){ 
        gaussian_sample(out, in);
    }else{
        std::cout << "Not Supported Gadget type." << std::endl;
    }
}
 

long** Gadget::sample(long *in){  
    long** decomposed = init_out(); 
    sample(decomposed, in); 
    return decomposed;
}


long* Gadget::get_gadget_vector(){
    long* gadget_vector = new long[ell];
    int powers_of_basis = 1;
    for(int i = 0; i < ell; ++i){
        gadget_vector[i] = powers_of_basis;
        powers_of_basis *= basis;
    }
    return gadget_vector;
}

 
long** Gadget::init_out(){
    long **decomposed = new long*[ell]; 
    for(int i = 0; i < ell; ++i){  
        decomposed[i] = new long[N];
        for(int j = 0; j < N; ++j){
            decomposed[i][j] = 0;
        }
    }   
    return decomposed;
}

void Gadget::delete_out(long** out){
    for(int i = 0; i < ell; ++i){  
        delete[] out[i]; 
    }  
    delete[] out; 
}


void Gadget::decomp(long **d_ct, long* poly){
    long mask = basis-1;
    long shift;
    for(int i = 0; i < ell; ++i){
        shift = k*i;
        for(int j=0; j < N; ++j){
            // The jth coefficients of the ith (decomposed) polynomial
            d_ct[i][j] = (poly[j] & mask) >> shift;
        }
        mask = mask << k;
    }
}


 
void Gadget::signed_decomp(long **d_ct, long* poly){ 
    Utils::array_signed_form(signed_poly, poly, N, Q); 
    long half = Q/2;
    for(int i = 0; i < N; ++i){  
        if(poly[i] <= half){
            signed_poly[i] = poly[i];
            sign[i] = 1;
        }else{
            signed_poly[i] = abs(poly[i]-Q);
            sign[i] = -1;
        }
    }
    decomp(d_ct, signed_poly);
    for(int j = 0; j < ell; ++j){
        for(int i = 0; i < N; ++i){
            d_ct[j][i] = d_ct[j][i] * sign[i];
        }
    } 
}

 
void Gadget::gaussian_sample(long **out, long* in){
    if(is_power_of_base_modulus){ 
        gaussian_sample_modulus_power_of_base(out, in);
    }else{
        gaussian_sample_general_modulus(out, in);
    }
}
 



void Gadget::gaussian_sample_modulus_power_of_base(long **out, long* in){
    mask = basis-1;  
    for(long j = 0; j < N; ++j){
        gaussians[j] = 0;
    }  
    for(long i = 0; i < ell; ++i){
        shift = k*i;
        for(long j=0; j < N; ++j){
            prev_gauss = gaussians[j];
            // Here we sample the new gaussian  
            //gaussians[j] = rand.gaussian(basis);
            gaussians[j] =   (long)rand.normal_dist(rand.e1) << k;
            // The jth coefficients of the ith (decomposed) polynomial 
            out[i][j] = (in[j] & mask) >> shift; 
            out[i][j] += gaussians[j] - prev_gauss; 
            gaussians[j] = gaussians[j] >> k;
        }
        mask = mask << k;
    }
}

/*
// Old gaussian_sample_general_modulus. Inefficient. But, lets leave it for now. 
void gadget::gaussian_sample_general_modulus(long **out, long* in){ 
    long* decomp = new long[ell];
    for(int i = 0; i < N; ++i){ 
        sample_G(decomp, in[i]);
        for(int j = 0; j < ell; ++j){
            out[j][i] = decomp[j];
        }
    }
    delete[] decomp;
} 
*/

  
void Gadget::gaussian_sample_general_modulus(long **out, long* in){   
  
    long beta;
 
    long integer;
    double floating=0.0;

    // Additional stuff for perturb_D
    double temp;

    for(int k = 0; k < N; ++k){ 
        // Start of perturb_B(p)
        z_pert[0] = (long)(rand_sigmas[0].normal_dist(rand_sigmas[0].e1)); 
        //beta = 0;
        beta = -(z_pert[0] * h[0]); 
        for(int i = 1; i < ell; ++i){  
            c_pert[i] = beta * inv_l[i]; 
            integer = c_pert[i];
            floating = c_pert[i] - integer; 
            z_pert[i] = integer + (long)(rand_sigmas[i].normal_dist(rand_sigmas[i].e1) + floating); 
            beta = -(z_pert[i] * h[i]); 
        }
        z_pert[ell] = 0;
        p[0] = two_times_basis_plus_one * z_pert[0] + basis * z_pert[1]; 
        for(int i = 1; i < ell; ++i){
            p[i] = basis * (z_pert[i-1] + 2*z_pert[i] + z_pert[i+1]); 
        } 
        // End of perturb_B(p)

 
        // Additional stuff for base decompositon
        // TODO: The masks and shifts can be precomputed
        long mask = basis-1; 
        long shift; 
        // Start base_decomposition(u, in[k]);  
        for(long i = 0; i < ell; ++i){
            shift = this->k*i; 
            u[i] = (in[k] & mask) >> shift; 
            mask = mask << this->k;
        } 
        // End base_decomposition(u, in[k]);  


        // Computing the c values
        c[0] = (u[0] - p[0]) * inv_basis;  
        for(int i = 1; i < ell; ++i){ 
            c[i] = (c[i-1] + (double)(u[i] - p[i])) * inv_basis;
        }  

 
        // Start of sample_D(z, c);  
        temp = -c[ell-1]/d[ell-1]; 
        integer = temp;
        floating = temp - integer; 
        z[ell-1] = integer + (long)(rand_d_stddev.normal_dist(rand_d_stddev.e1) + floating);
        double out_ell_minus_one = (double)z[ell-1];
        for(int i = 0; i < ell-1; ++i){ 
            temp =  -(c[i] - out_ell_minus_one * d[i]); 
            integer = temp;
            floating = temp - integer; 
            z[i] = integer + (long)(rand_sigma.normal_dist(rand_sigma.e1) + floating);
        } 
        // End of sample_D(z, c); 
  
        out[0][k] = basis * z[0] + q_decomp[0] * out_ell_minus_one + u[0]; 
        for(int i = 1; i < ell-1; ++i){ 
            out[i][k] = basis * z[i] - z[i-1] + q_decomp[i] * out_ell_minus_one + u[i];  
        } 
        out[ell-1][k] =  q_decomp[ell-1] * out_ell_minus_one -  z[ell-2] + u[ell-1];  
    } 
 
} 


void Gadget::sample_G(long* out, long in){ 
    long* p = new long[ell];
    double* c = new double[ell];
    long* u = new long[ell]; 
    long* z = new long[ell];
    perturb_B(p);
    base_decomposition(u, in);  
    c[0] = (u[0] - p[0]) * inv_basis;  
    for(int i = 1; i < ell; ++i){ 
        c[i] = (c[i-1] + (double)(u[i] - p[i])) * inv_basis;
    }  
    sample_D(z, c);  
    out[0] = basis * z[0] + q_decomp[0] * z[ell-1] + u[0]; 
    for(int i = 1; i < ell-1; ++i){ 
        out[i] = basis * z[i] - z[i-1] + q_decomp[i] * z[ell-1] + u[i];  
    } 
    out[ell-1] =  q_decomp[ell-1] * z[ell-1] -  z[ell-2] + u[ell-1];  
    delete[] p;
    delete[] c;
    delete[] u; 
    delete[] z;
}

void Gadget::perturb_B(long* p){  
    double* c = new double[ell];
    long* z = new long[ell+1];
    //long* p = new long[ell];
    long beta = 0;
    double integer;
    double floating;
    for(int i = 0; i < ell; ++i){  
        c[i] = beta * inv_l[i]; 
        floating = modf(c[i], &integer);
        z[i] = (long)integer + sample_Zt(sigmas[i], floating); 
        beta = -z[i] * h[i]; 
    }
    z[ell] = 0;
    p[0] = two_times_basis_plus_one * z[0] + basis * z[1]; 
    for(int i = 1; i < ell; ++i){
        p[i] = basis * (z[i-1] + 2*z[i] + z[i+1]); 
    } 
    delete[] c;
    delete[] z; 
    //return p;
}

void Gadget::sample_D(long* out, double* c){
    //long* out = new long[ell];
    double temp = -c[ell-1]/d[ell-1];
    double integer;
    double floating; 
    floating = modf(temp, &integer);
    out[ell-1] = (long)integer + sample_Zt(d_stddev, floating);
    double out_ell_minut_one = (double)out[ell-1];
    for(int i = 0; i < ell-1; ++i){ 
        temp =  c[i] - out_ell_minut_one * d[i]; 
        floating = modf(temp, &integer);
        out[i] =  (long)integer + sample_Zt(d_stddev, floating);
    } 
}


long Gadget::sample_Zt(double sigma, double center){
    // Implicitely takes as input stddev and tail_bound 
    return rand.gaussian(center, sigma);  
}

void Gadget::precompute_constants_for_power_of_base_gaussian_sampling(){
    is_power_of_basis_gaussian_temp_init = true;
    mask = basis-1;  
    gaussians = new long[N];
    for(long j = 0; j < N; ++j){
        gaussians[j] = 0;
    }  
}

void Gadget::precompute_constants_for_general_modulus_gaussian_sampling(){ 
    q_decomp = new long[ell];
    Gadget::base_decomposition(q_decomp, Q); 
    sigma = stddev/(double)(basis + 1); 
    rand_sigma = Sampler(0.0, stddev);  
    sigmas = new double[ell];
    rand_sigmas = new Sampler[ell];

    r = basis + 1;
    l = new double[ell];
    inv_l = new double[ell];
    l[0] = sqrt(basis  + (double)basis/(double)ell + 1.0);
    h = new double[ell];
    h[0] = 0; 
    d = new double[ell];
    d[0] = (double)q_decomp[0]/(double)basis;

    for(int i = 1; i < ell; ++i){
        l[i] = sqrt(basis + (double)basis/(double)(ell-i)); 
        h[i] = sqrt(basis - (double)basis/(double)(ell-i));
        d[i] = (d[i-1] + (double)q_decomp[i])/(double)basis;
        inv_l[i] = 1.0/l[i];
         
        sigmas[i] = sigma/l[i];   
         
        rand_sigmas[i] = Sampler(0.0, sigmas[i]); 
    }

    d_stddev = sigma / d[ell-1];  
    rand_d_stddev = Sampler(0.0, d_stddev);   
     
    inv_basis = (double)1.0/basis; 
    two_times_basis_plus_one = 2 * basis + 1;


    // Temporary variables:
    p = new long[ell];
    c = new double[ell];
    u = new long[ell]; 
    z = new long[ell]; 
    // Stuff for perturb_B
    c_pert = new double[ell];
    z_pert = new long[ell+1];

    is_precomputed = true;
}


void Gadget::base_decomposition(long* out, long in){
    long mask = basis-1;
    long shift; 
    for(long i = 0; i < ell; ++i){
        shift = k*i; 
        out[i] = (in & mask) >> shift; 
        mask = mask << k;
    }
}
