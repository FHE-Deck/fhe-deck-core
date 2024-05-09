#include "gadget.h"
 
using namespace fhe_deck;

 
SignedDecompositionGadget::SignedDecompositionGadget(int degree, long modulus, long base){
    this->degree = degree;
    this->modulus = modulus;
    this->base = base;
    this->bits_base = Utils::power_times(base, 2);  
    this->digits = Utils::power_times(modulus, base);  
    /// TODO: Check if bits_base is a power of two.
}

void SignedDecompositionGadget::sample(long** out, long *poly){  
    long* signed_poly = new long[degree];
    int* sign = new int[degree];
    Utils::array_signed_form(signed_poly, poly, degree, modulus); 
    long half = modulus/2;
    // Extracting the signs
    for(int i = 0; i < degree; ++i){  
        if(poly[i] <= half){
            signed_poly[i] = poly[i];
            sign[i] = 1;
        }else{
            signed_poly[i] = abs(poly[i]-modulus);
            sign[i] = -1;
        }
    }
    // Decomposition
    decomp(out, signed_poly);
    // Adding the signs
    for(int j = 0; j < digits; ++j){
        for(int i = 0; i < degree; ++i){
            out[j][i] = out[j][i] * sign[i];
        }
    }
    delete[] signed_poly;
    delete[] sign;
}
 
void SignedDecompositionGadget::decomp(long **d_ct, long* poly){
    long mask = base-1;
    long shift;
    for(int i = 0; i < digits; ++i){
        shift = bits_base*i;
        for(int j=0; j < degree; ++j){
            // The jth coefficients of the ith (decomposed) polynomial
            d_ct[i][j] = (poly[j] & mask) >> shift;
        }
        mask = mask << bits_base;
    }
}
  
DiscreteGaussianSamplingGadget::~DiscreteGaussianSamplingGadget(){
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
 

DiscreteGaussianSamplingGadget::DiscreteGaussianSamplingGadget(int degree, long Q, long base, double stddev){
    this->type = discrete_gaussian_gadget;
    this->stddev = stddev;
    this->degree = degree;
    this->modulus = modulus;
    this->base = base; 
    setup_type_specific_parameters(); 
}
 

void DiscreteGaussianSamplingGadget::setup_type_specific_parameters(){
    if(this->type == signed_decomposition_gadget){
        this->bits_base = 1;
        // Compute the k, parameter (remind k is such that 2**k = base)  
        // meaning that for now we support only power of two base
        // TODO: Compute these values with functions from utils 
        this->bits_base = Utils::power_times(base, 2);  
        this->digits = Utils::power_times(modulus, base);   
        this->ell_minus_one = this->digits-1;
 
        // Initialize temporary arrays:
        signed_poly = new long[degree]; 
        sign = new long[degree]; 
        is_deter_temp_init = true;
    }else if(this->type == discrete_gaussian_gadget){ 
        if(this->stddev < base){ 
            throw std::logic_error("Gadget::setup_type_specific_parameters(): stddev < basis!");
        } 
        this->rand = Sampler(0.0, this->stddev); 
        if(!Utils::is_power_of(base, 2)){
            std::cout << "WARNING: Currently only power of two base is supported" << std::endl;
        }
        this->bits_base = Utils::power_times(base, 2);
        this->digits = Utils::power_times(modulus, base);  
        this->ell_minus_one = this->digits-1;
        if(Utils::is_power_of(modulus, base)){
            is_power_of_base_modulus = true;
            precompute_constants_for_power_of_base_gaussian_sampling();
        }else{ 
            is_power_of_base_modulus = false;
            precompute_constants_for_general_modulus_gaussian_sampling();
        }  
    }else{
        throw std::logic_error("Gadget::setup_type_specific_parameters(): Most likely wrong gadget type!");
    } 
}
 



void DiscreteGaussianSamplingGadget::sample(long** out, long *in){ 
    if(type == signed_decomposition_gadget){
        signed_decomp(out, in);
    }else if(type == discrete_gaussian_gadget){   
        gaussian_sample(out, in); 
    }else{
        std::cout << "Not Supported Gadget type." << std::endl;
    }
}
  
 
long* Gadget::get_gadget_vector(){
    long* gadget_vector = new long[digits];
    int powers_of_basis = 1;
    for(int i = 0; i < digits; ++i){
        gadget_vector[i] = powers_of_basis;
        powers_of_basis *= base;
    }
    return gadget_vector;
}
 
long** Gadget::init_out(){
    long **decomposed = new long*[digits]; 
    for(int i = 0; i < digits; ++i){  
        decomposed[i] = new long[degree];
        for(int j = 0; j < degree; ++j){
            decomposed[i][j] = 0;
        }
    }   
    return decomposed;
}

void Gadget::delete_out(long** out){
    for(int i = 0; i < digits; ++i){  
        delete[] out[i]; 
    }  
    delete[] out; 
} 
 
void DiscreteGaussianSamplingGadget::decomp(long **d_ct, long* poly){
    long mask = base-1;
    long shift;
    for(int i = 0; i < digits; ++i){
        shift = bits_base*i;
        for(int j=0; j < degree; ++j){
            // The jth coefficients of the ith (decomposed) polynomial
            d_ct[i][j] = (poly[j] & mask) >> shift;
        }
        mask = mask << bits_base;
    }
}
 
void DiscreteGaussianSamplingGadget::signed_decomp(long **d_ct, long* poly){ 
    Utils::array_signed_form(signed_poly, poly, degree, modulus); 
    long half = modulus/2;
    // Extracting the signs
    for(int i = 0; i < degree; ++i){  
        if(poly[i] <= half){
            signed_poly[i] = poly[i];
            sign[i] = 1;
        }else{
            signed_poly[i] = abs(poly[i]-modulus);
            sign[i] = -1;
        }
    }
    // Decomposition
    decomp(d_ct, signed_poly);
    // Adding the signs
    for(int j = 0; j < digits; ++j){
        for(int i = 0; i < degree; ++i){
            d_ct[j][i] = d_ct[j][i] * sign[i];
        }
    } 
}

 
void DiscreteGaussianSamplingGadget::gaussian_sample(long **out, long* in){ 
    if(is_power_of_base_modulus){  
        gaussian_sample_modulus_power_of_base(out, in);
    }else{ 
        gaussian_sample_general_modulus(out, in);
    }
}
 
 

void DiscreteGaussianSamplingGadget::gaussian_sample_modulus_power_of_base(long **out, long* in){
    mask = base-1;  
    for(long j = 0; j < degree; ++j){
        gaussians[j] = 0;
    }  
    for(long i = 0; i < digits; ++i){
        shift = bits_base*i;
        for(long j=0; j < degree; ++j){
            prev_gauss = gaussians[j];
            // Here we sample the new gaussian    
            //gaussians[j] = (long)(gen_gaussian() * sigma) << k;
            gaussians[j] = gen_discrete_gauss(0.0f) << bits_base;
            // The jth coefficients of the ith (decomposed) polynomial 
            out[i][j] = (in[j] & mask) >> shift; 
            out[i][j] += gaussians[j] - prev_gauss; 
            gaussians[j] = gaussians[j] >> bits_base;
        }
        mask = mask << bits_base;
    }
}
 

void DiscreteGaussianSamplingGadget::gaussian_sample_general_modulus(long **out, long* in){   
  
    long beta;

    long integer;
    double floating=0.0; 
    // Additional stuff for perturb_D
    double temp;

    for(int k = 0; k < degree; ++k){  
        // Additional stuff for base decompositon
        // TODO: Perhaps I can make it faster by merging this into the previous for loop?
        long mask = base-1; 
        long shift; 
        // Start base_decomposition(u, in[k]);  
        for(long i = 0; i < digits; ++i){
            shift = this->bits_base*i; 
            u[i] = (in[k] & mask) >> shift; 
            mask = mask << this->bits_base;
        } 
        // End base_decomposition(u, in[k]);  
 
        // Start of perturb_B(p) 
        z_pert[0] =  gen_gaussian();
        //beta = 0;
        beta = -(z_pert[0] * h[0]); 
        for(int i = 1; i < digits; ++i){  
            c_pert[i] = beta * inv_l[i]; 
            integer = c_pert[i];
            floating = c_pert[i] - integer;   
            z_pert[i] = integer + (long)(gen_gaussian() * sigmas[i]  + floating);  
            //z_pert[i] = integer + (long)(gen_gaussian_float() * sigmas[i]  + floating); 
            beta = -(z_pert[i] * h[i]); 
        }
        z_pert[digits] = 0;
        p[0] = two_times_basis_plus_one * z_pert[0] + base * z_pert[1]; 
        for(int i = 1; i < digits; ++i){
            p[i] = base * (z_pert[i-1] + 2*z_pert[i] + z_pert[i+1]); 
        } 
        // End of perturb_B(p)
 
        // Computing the c values
        c[0] = (u[0] - p[0]) * inv_basis;  
        for(int i = 1; i < digits; ++i){ 
            c[i] = (c[i-1] + (double)(u[i] - p[i])) * inv_basis;
        }   
        // Start of sample_D(z, c);  
        temp = -c[ell_minus_one]/d[ell_minus_one]; 
        integer = temp;
        floating = temp - integer;  
        //z[ell_minus_one] = integer + (long)(gen_gaussian() * sigma + floating);
        z[ell_minus_one] = integer + gen_discrete_gauss(floating);
        double out_ell_minus_one = (double)z[ell_minus_one];
        for(int i = 0; i < ell_minus_one; ++i){ 
            temp =  -(c[i] - out_ell_minus_one * d[i]); 
            integer = temp;
            floating = temp - integer;  
            //z[i] = integer + (long)(gen_gaussian() * sigma + floating);
            z[i] = integer + gen_discrete_gauss(floating);
        } 
        // End of sample_D(z, c);   
        out[0][k] = base * z[0] + q_decomp[0] * out_ell_minus_one + u[0]; 
        for(int i = 1; i < ell_minus_one; ++i){ 
            out[i][k] = base * z[i] - z[i-1] + q_decomp[i] * out_ell_minus_one + u[i];  
        } 
        out[ell_minus_one][k] =  q_decomp[ell_minus_one] * out_ell_minus_one -  z[digits-2] + u[ell_minus_one];  
    }  
} 
  
 


void DiscreteGaussianSamplingGadget::sample_G(long* out, long in){ 
    long* p = new long[digits];
    double* c = new double[digits];
    long* u = new long[digits]; 
    long* z = new long[digits];
    perturb_B(p);
    base_decomposition(u, in);  
    c[0] = (u[0] - p[0]) * inv_basis;  
    for(int i = 1; i < digits; ++i){ 
        c[i] = (c[i-1] + (double)(u[i] - p[i])) * inv_basis;
    }  
    sample_D(z, c);  
    out[0] = base * z[0] + q_decomp[0] * z[digits-1] + u[0]; 
    for(int i = 1; i < digits-1; ++i){ 
        out[i] = base * z[i] - z[i-1] + q_decomp[i] * z[digits-1] + u[i];  
    } 
    out[digits-1] =  q_decomp[digits-1] * z[digits-1] -  z[digits-2] + u[digits-1];  
    delete[] p;
    delete[] c;
    delete[] u; 
    delete[] z;
}

void DiscreteGaussianSamplingGadget::perturb_B(long* p){  
    double* c = new double[digits];
    long* z = new long[digits+1];
    //long* p = new long[ell];
    long beta = 0;
    double integer;
    double floating;
    for(int i = 0; i < digits; ++i){  
        c[i] = beta * inv_l[i]; 
        floating = modf(c[i], &integer);
        z[i] = (long)integer + sample_Zt(sigmas[i], floating); 
        beta = -z[i] * h[i]; 
    }
    z[digits] = 0;
    p[0] = two_times_basis_plus_one * z[0] + base * z[1]; 
    for(int i = 1; i < digits; ++i){
        p[i] = base * (z[i-1] + 2*z[i] + z[i+1]); 
    } 
    delete[] c;
    delete[] z; 
    //return p;
}

void DiscreteGaussianSamplingGadget::sample_D(long* out, double* c){
    //long* out = new long[ell];
    double temp = -c[digits-1]/d[digits-1];
    double integer;
    double floating; 
    floating = modf(temp, &integer);
    out[digits-1] = (long)integer + sample_Zt(d_stddev, floating);
    double out_ell_minut_one = (double)out[digits-1];
    for(int i = 0; i < digits-1; ++i){ 
        temp =  c[i] - out_ell_minut_one * d[i]; 
        floating = modf(temp, &integer);
        out[i] =  (long)integer + sample_Zt(d_stddev, floating);
    } 
}


long DiscreteGaussianSamplingGadget::sample_Zt(double sigma, double center){
    // Implicitely takes as input stddev and tail_bound 
    return rand.gaussian(center, sigma);  
}

void DiscreteGaussianSamplingGadget::precompute_constants_for_power_of_base_gaussian_sampling(){
    is_power_of_basis_gaussian_temp_init = true;
    mask = base-1;  
    gaussians = new long[degree];
    for(long j = 0; j < degree; ++j){
        gaussians[j] = 0;
    }   
    sigma  = stddev;
    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937_64 e(seed);
    std::uniform_int_distribution<unsigned long> uniform(0, 0xffffffffffffffff);  
    xorshift_s = uniform(e);
    hasSpare = false; 
}

void DiscreteGaussianSamplingGadget::precompute_constants_for_general_modulus_gaussian_sampling(){  

    q_decomp = new long[digits];
    DiscreteGaussianSamplingGadget::base_decomposition(q_decomp, modulus);  
    sigma = stddev/(double)(base + 1); 
    rand_sigma = Sampler(0.0, stddev);  
    sigmas = new double[digits];
    rand_sigmas = new Sampler[digits];

    r = base + 1;
    l = new double[digits];
    inv_l = new double[digits];
    l[0] = sqrt(base  + (double)base/(double)digits + 1.0);
    h = new double[digits];
    h[0] = 0; 
    d = new double[digits];
    d[0] = (double)q_decomp[0]/(double)base;
 

    for(int i = 1; i < digits; ++i){
        l[i] = sqrt(base + (double)base/(double)(digits-i)); 
        h[i] = sqrt(base - (double)base/(double)(digits-i));
        d[i] = (d[i-1] + (double)q_decomp[i])/(double)base;
        inv_l[i] = 1.0/l[i];
         
        sigmas[i] = sigma/l[i];   
  
        rand_sigmas[i] = Sampler(0.0, sigmas[i]); 
    }

 
    d_stddev = sigma / d[digits-1];   
    rand_d_stddev = Sampler(0.0, d_stddev);   
     
    inv_basis = (double)1.0/base; 
    two_times_basis_plus_one = 2 * base + 1;


    // Temporary variables:
    p = new long[digits];
    c = new double[digits];
    u = new long[digits]; 
    z = new long[digits]; 
    // Stuff for perturb_B
    c_pert = new double[digits];
    z_pert = new long[digits+1];

   

   // Initiate xoshiro256 state
    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937_64 e(seed);
    std::uniform_int_distribution<unsigned long> uniform(0, 0xffffffffffffffff);
    xoshiro256_s = new long[4];
    xoshiro256_s[0] = uniform(e);
    xoshiro256_s[1] = uniform(e);
    xoshiro256_s[2] = uniform(e);
    xoshiro256_s[3] = uniform(e);
 
    xorshift_s = uniform(e);
    hasSpare = false; 
    is_precomputed = true;
}


void DiscreteGaussianSamplingGadget::base_decomposition(long* out, long in){
    long mask = base-1;
    long shift; 
    for(long i = 0; i < digits; ++i){
        shift = bits_base*i; 
        out[i] = (in & mask) >> shift; 
        mask = mask << bits_base;
    }
}
 
void DiscreteGaussianSamplingGadget::xorshift64(){ 
	xorshift_s ^= xorshift_s << 13;
	xorshift_s ^= xorshift_s >> 7;
	xorshift_s ^= xorshift_s << 17; 
    //I'm extracting only the upper 53 bits.  
	xoshiro256_result = xorshift_s & 0x1fffffffffffff;
}
 
int DiscreteGaussianSamplingGadget::xorshift25(){ 
    if(hasSpare){
        hasSpare = false;
        return xoshiro256_25_result_2;
    }
	xorshift_s ^= xorshift_s << 13;
	xorshift_s ^= xorshift_s >> 7;
	xorshift_s ^= xorshift_s << 17; 
    //I'm extracting only the upper 53 bits.  
	//xoshiro256_result = xorshift_s & 0x1fffffffffffff;
    xoshiro256_25_result_1 = xorshift_s & 0x1FFFFFF;
    xoshiro256_25_result_2 = (xorshift_s>>25) & 0x1FFFFFF;
    hasSpare  = true;
    return xoshiro256_25_result_1;
}
 
void DiscreteGaussianSamplingGadget::xoshiro256p(){
    //xoshiro256_result = 1212342353425;

    // Note: I'm extracting only the upper 53 bits. Hence the  
    xoshiro256_result = (xoshiro256_s[0] + xoshiro256_s[3]) & xoshiro_mask;

	xoshiro256_t = xoshiro256_s[1] << 17;
 
	xoshiro256_s[1] ^= (xoshiro256_s[2] ^ xoshiro256_s[0]);
	xoshiro256_s[3] ^= xoshiro256_s[1];
	xoshiro256_s[0] ^= xoshiro256_s[3];

	xoshiro256_s[2] ^= xoshiro256_t;
	xoshiro256_s[3] = (xoshiro256_s[3] << 45) | (xoshiro256_s[3] >> (64 - 45));
      
}
 
/*
Marsaglia polar method (Kindof Slow)
double Gadget::gen_gaussian(double mean, double stddev){
 
    if (hasSpare) {
        hasSpare = false;
        return spare * stddev + mean;
    } else {
        double u, v, s;
        do {
            //u = (xoshiro256p() / 9007199254740992) * 2.0 - 1.0;
            //v = (xoshiro256p() / 9007199254740992) * 2.0 - 1.0;
            // We multiply by 2 so lets precompute this and change the divisor.
            u = (xoshiro256p() / 4503599627370496) - 1.0;
            v = (xoshiro256p() / 4503599627370496) - 1.0;
            s = u * u + v * v;
        } while (s >= 1.0 || s == 0.0);
        //std::cout << "Are we comming out?" << std::endl;
        s = sqrt(-2.0 * log(s) / s);
        spare = v * s;
        hasSpare = true;
        return mean + stddev * u * s;
    }
} 

*/

  
  
/*
Box-Muller method
*/ 
double DiscreteGaussianSamplingGadget::gen_gaussian(){ 
    if (hasSpare) {
        hasSpare = false;
        return spare ;
    } else {       
        hasSpare = true;
        do
        {
            xorshift64();    
        }
        while(xoshiro256_result  <= 2);    
        u1 =  (double)xoshiro256_result * div_const_u1; 
        xorshift64(); 
        u2 = (double)xoshiro256_result * div_const_u2;  
        float u2_float = (float)u2;
        auto mag =  std::sqrt(-2.0f * std::log((float)u1)); 
        spare  = (double)(mag * std::sin(u2_float)); 
        return (double)(mag * std::cos(u2_float));
    } 
}  

/*
Box-Muller method, over floats. We don't need big precision here because we multiply by the standard deviation,
*/  
float DiscreteGaussianSamplingGadget::gen_gaussian_float(){ 
    if (hasSpare) {
        hasSpare = false;
        return spare_float ;
    } else {       
        hasSpare = true;
        do
        {
            xorshift64();    
        }
        while(xoshiro256_result  <= 2);   
  
        u1_float =  (float)(xoshiro256_result & 0x1FFFFFF) * div_const_u1_float; 
        xorshift64(); 
        u2_float = (float)(xoshiro256_result & 0x1FFFFFF) * div_const_u2_float;  
  
        auto mag =  std::sqrt(-2.0f * std::log(u1_float)); 
        spare_float  = mag * std::sin(u2_float); 
        return mag * std::cos(u2_float);
    } 
}  
  
long DiscreteGaussianSamplingGadget::gen_discrete_gauss(float c){

    int sigma = this->sigma;
    int k;
    int s;
    float tmp;
    int i0; 
    float x;
    int j; 
    float exp_inp; 
    unsigned int bias; 
    do{ 
        k = d1_d2_of_karney();   
   
        xorshift64(); 
        s = 1 * (-((xoshiro256_result>>52) & 1));
    
       
        j =((xoshiro256_result & 0x1FFFFFF) % sigma);
        tmp = k * sigma + s * c;
        i0 = (int)tmp + j; 
   
        x = (((float)i0 - tmp))/sigma; 

        if(x >= 1){  
            continue;
        }
        if(x == 0){
            if(k == 0 && s < 0){
                continue;
            } 
            else{ 
                return s * (i0);
            }
        }
        exp_inp = minus_half * x * (2 * k + x);
 
           
        exp_inp *= (5+exp_inp);
        exp_inp *= (20+exp_inp);
        exp_inp *= (60+exp_inp);
        exp_inp *= (120+exp_inp);
        exp_inp *= (120+exp_inp); 
        exp_inp *= 0.0013888888f; 
        bias = (unsigned int)(exp_inp * 33554431.0f);  
        if(((unsigned int)(xoshiro256_result>>25) & 0x1FFFFFF) <= bias){  
            return s * (i0) ;
        } 
    }while(true); 
}


int DiscreteGaussianSamplingGadget::d1_d2_of_karney(){
    int k ;
    bool reject;   
    int k_times_k_minus_one;
    do{ 
        k = -1;
        reject = false;
        do{ 
            ++k; 
            // 20351791 = exp(-0.5) * 2**25
        } while(xorshift25() < 20351791); 
        if(k < 2){ 
            return k;
        }
        k_times_k_minus_one = k * (k - 1); 
        for(int i = 0; i < k_times_k_minus_one; ++i){ 
            if(xorshift25() >= 20351791){
                reject = true;
                break;
            }
        }  
    }while(reject);  
    return k; 
}