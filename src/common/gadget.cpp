#include "common/gadget.h"
 
using namespace FHEDeck;

 
SignedDecompositionGadget::SignedDecompositionGadget(int32_t degree, int64_t modulus, int64_t base){
    this->degree = degree;
    this->modulus = modulus;
    this->base = base;
    init();
}

void SignedDecompositionGadget::init(){ 
    /// TODO: Check if bits_base is a power of two.
    this->bits_base = Utils::power_times(base, 2);  
    this->digits = Utils::power_times(modulus, base);  
}
  
void SignedDecompositionGadget::sample(VectorArray& out, const std::vector<int64_t>& in){ 
    std::vector<int64_t> signed_poly;
    signed_poly.resize(degree); 
    std::vector<int64_t> sign;
    sign.resize(degree);
    Utils::array_signed_form(signed_poly, in, degree, modulus); 
    int64_t half = modulus/2;
    // Extracting the signs
    for(int32_t i = 0; i < degree; ++i){  
        if(in[i] <= half){
            signed_poly[i] = in[i];
            sign[i] = 1;
        }else{
            signed_poly[i] = std::abs<int64_t>(in[i]-modulus);
            sign[i] = -1;
        }
    }
    // Decomposition
    decomp(out, signed_poly);
    // Adding the signs
    for(int32_t j = 0; j < digits; ++j){
        for(int32_t i = 0; i < degree; ++i){ 
            out[j][i] = out[j][i] * sign[i];
        }
        Utils::array_mod_form(out[j], out[j], degree, modulus);
    } 
}
 
void SignedDecompositionGadget::decomp(VectorArray& out, const std::vector<int64_t>& poly){
    int64_t mask = base-1;
    int64_t shift;
    for(int32_t i = 0; i < digits; ++i){
        shift = bits_base*i;
        for(int32_t j=0; j < degree; ++j){
            // The jth coefficients of the ith (decomposed) polynomial
            out[i][j] = (poly[j] & mask) >> shift;
        }
        mask = mask << bits_base;
    }
}
  
DiscreteGaussianSamplingGadget::DiscreteGaussianSamplingGadget(int32_t degree, int64_t modulus, int64_t base, double stddev){  
    this->stddev = stddev;
    this->degree = degree;
    this->modulus = modulus;
    this->base = base; 
    setup_type_specific_parameters(); 
}
 

void DiscreteGaussianSamplingGadget::setup_type_specific_parameters(){ 
        if(this->stddev < base){ 
            throw std::logic_error("Gadget::setup_type_specific_parameters(): stddev < basis!");
        }  
        if(!Utils::is_power_of(base, 2)){
            throw std::logic_error("Gadget::setup_type_specific_parameters(): Currently only power of two base is supported!");
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
}
   

void DiscreteGaussianSamplingGadget::sample(VectorArray& out, const std::vector<int64_t>& in){
    gaussian_sample(out, in);
}
  
void DiscreteGaussianSamplingGadget::decomp(VectorArray& out, const std::vector<int64_t>& in){
    int64_t mask = base-1;
    int64_t shift;
    for(int32_t i = 0; i < digits; ++i){
        shift = bits_base*i;
        for(int32_t j=0; j < degree; ++j){
            // The jth coefficients of the ith (decomposed) polynomial
            out[i][j] = (in[j] & mask) >> shift;
        }
        mask = mask << bits_base;
    }
}
 
void DiscreteGaussianSamplingGadget::signed_decomp(VectorArray& out, const std::vector<int64_t>& in){ 
    Utils::array_signed_form(signed_poly, in, degree, modulus); 
    int64_t half = modulus/2;
    // Extracting the signs
    for(int32_t i = 0; i < degree; ++i){  
        if(in[i] <= half){
            signed_poly[i] = in[i];
            sign[i] = 1;
        }else{
            signed_poly[i] = abs(in[i]-modulus);
            sign[i] = -1;
        }
    }
    // Decomposition
    decomp(out, signed_poly);
    // Adding the signs
    for(int32_t j = 0; j < digits; ++j){
        for(int32_t i = 0; i < degree; ++i){
            out[j][i] = out[j][i] * sign[i];
        }
    } 
}

 
void DiscreteGaussianSamplingGadget::gaussian_sample(VectorArray& out, const std::vector<int64_t>& in){ 
    if(is_power_of_base_modulus){  
        gaussian_sample_modulus_power_of_base(out, in);
    }else{ 
        gaussian_sample_general_modulus(out, in);
    }
    for(int32_t j = 0; j < digits; ++j){ 
        Utils::array_mod_form(out[j], out[j], degree, modulus);
    }
}
 
  
void DiscreteGaussianSamplingGadget::gaussian_sample_modulus_power_of_base(VectorArray& out, const std::vector<int64_t>& in){
    mask = base-1;  
    for(int64_t j = 0; j < degree; ++j){
        gaussians[j] = 0;
    }  
    for(int64_t i = 0; i < digits; ++i){
        shift = bits_base*i;
        for(int64_t j=0; j < degree; ++j){
            prev_gauss = gaussians[j];
            // Here we sample the new gaussian    
            //gaussians[j] = (int64_t)(gen_gaussian() * sigma) << k;
            gaussians[j] = gen_discrete_gauss(0.0f) << bits_base;
            // The jth coefficients of the ith (decomposed) polynomial 
            out[i][j] = (in[j] & mask) >> shift; 
            out[i][j] += gaussians[j] - prev_gauss; 
            gaussians[j] = gaussians[j] >> bits_base;
        }
        mask = mask << bits_base;
    }
}
 

void DiscreteGaussianSamplingGadget::gaussian_sample_general_modulus(VectorArray& out, const std::vector<int64_t>& in){   
  
    int64_t beta;

    int64_t integer;
    double floating=0.0; 
    // Additional stuff for perturb_D
    double temp;

    for(int32_t k = 0; k < degree; ++k){  
        // Additional stuff for base decompositon 
        int64_t mask = base-1; 
        int64_t shift; 
        // Start base_decomposition(u, in[k]);  
        for(int64_t i = 0; i < digits; ++i){
            shift = this->bits_base*i; 
            u[i] = (in[k] & mask) >> shift; 
            mask = mask << this->bits_base;
        } 
        // End base_decomposition(u, in[k]);  
 
        // Start of perturb_B(p) 
        z_pert[0] =  gen_gaussian(); 
        beta = -(z_pert[0] * h[0]); 
        for(int32_t i = 1; i < digits; ++i){  
            c_pert[i] = beta * inv_l[i]; 
            integer = c_pert[i];
            floating = c_pert[i] - integer;   
            z_pert[i] = integer + (int64_t)(gen_gaussian() * sigmas[i]  + floating);   
            beta = -(z_pert[i] * h[i]); 
        }
        z_pert[digits] = 0;
        p[0] = two_times_basis_plus_one * z_pert[0] + base * z_pert[1]; 
        for(int32_t i = 1; i < digits; ++i){
            p[i] = base * (z_pert[i-1] + 2*z_pert[i] + z_pert[i+1]); 
        } 
        // End of perturb_B(p)
 
        // Computing the c values
        c[0] = (u[0] - p[0]) * inv_basis;  
        for(int32_t i = 1; i < digits; ++i){ 
            c[i] = (c[i-1] + (double)(u[i] - p[i])) * inv_basis;
        }   
        // Start of sample_D(z, c);  
        temp = -c[ell_minus_one]/d[ell_minus_one]; 
        integer = temp;
        floating = temp - integer;   
        z[ell_minus_one] = integer + gen_discrete_gauss(floating);
        double out_ell_minus_one = (double)z[ell_minus_one];
        for(int32_t i = 0; i < ell_minus_one; ++i){ 
            temp =  -(c[i] - out_ell_minus_one * d[i]); 
            integer = temp;
            floating = temp - integer;   
            z[i] = integer + gen_discrete_gauss(floating);
        } 
        // End of sample_D(z, c);   
        out[0][k] = base * z[0] + q_decomp[0] * out_ell_minus_one + u[0]; 
        for(int32_t i = 1; i < ell_minus_one; ++i){ 
            out[i][k] = base * z[i] - z[i-1] + q_decomp[i] * out_ell_minus_one + u[i];  
        } 
        out[ell_minus_one][k] =  q_decomp[ell_minus_one] * out_ell_minus_one -  z[digits-2] + u[ell_minus_one];  
    }  
} 
   
void DiscreteGaussianSamplingGadget::precompute_constants_for_power_of_base_gaussian_sampling(){
    is_power_of_basis_gaussian_temp_init = true;
    mask = base-1;   
    gaussians = std::vector<int64_t>();
    gaussians.resize(degree);
    for(int64_t j = 0; j < degree; ++j){
        gaussians[j] = 0;
    }   
    sigma  = stddev;
    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937_64 e(seed);
    std::uniform_int_distribution<uint64_t> uniform(0, 0xffffffffffffffff);  
    xorshift_s = uniform(e);
    hasSpare = false; 
}

void DiscreteGaussianSamplingGadget::precompute_constants_for_general_modulus_gaussian_sampling(){    
    q_decomp = std::vector<int64_t>();
    q_decomp.resize(digits);
    DiscreteGaussianSamplingGadget::base_decomposition(q_decomp, modulus);  
    sigma = stddev/(double)(base + 1);  
    sigmas = std::vector<double>();
    sigmas.resize(digits); 

    r = base + 1; 
    l = std::vector<double>();
    l.resize(digits); 
    inv_l = std::vector<double>();
    inv_l.resize(digits);
    l[0] = sqrt(base  + (double)base/(double)digits + 1.0); 
    h = std::vector<double>();
    h.resize(digits);
    h[0] = 0;  
    d = std::vector<double>();
    d.resize(digits);
    d[0] = (double)q_decomp[0]/(double)base;
 

    for(int32_t i = 1; i < digits; ++i){
        l[i] = sqrt(base + (double)base/(double)(digits-i)); 
        h[i] = sqrt(base - (double)base/(double)(digits-i));
        d[i] = (d[i-1] + (double)q_decomp[i])/(double)base;
        inv_l[i] = 1.0/l[i];
         
        sigmas[i] = sigma/l[i];   
   
    }

 
    d_stddev = sigma / d[digits-1];    
     
    inv_basis = (double)1.0/base; 
    two_times_basis_plus_one = 2 * base + 1;


    // Temporary variables: 
    p = std::vector<int64_t>();
    p.resize(digits); 
    c = std::vector<double>();
    c.resize(digits); 
    u = std::vector<int64_t>();
    u.resize(digits); 
    z = std::vector<int64_t>();
    z.resize(digits);
    // Stuff for perturb_B 
    c_pert = std::vector<double>();
    c_pert.resize(digits); 
    z_pert = std::vector<int64_t>();
    z_pert.resize(digits+1);

   

   // Initiate xoshiro256 state
    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937_64 e(seed);
    std::uniform_int_distribution<uint64_t> uniform(0, 0xffffffffffffffff); 
    xoshiro256_s = std::array<int64_t, 4>();
    xoshiro256_s[0] = uniform(e);
    xoshiro256_s[1] = uniform(e);
    xoshiro256_s[2] = uniform(e);
    xoshiro256_s[3] = uniform(e);
 
    xorshift_s = uniform(e);
    hasSpare = false; 
    is_precomputed = true;
}


void DiscreteGaussianSamplingGadget::base_decomposition(std::vector<int64_t>& out, int64_t in){
    int64_t mask = base-1;
    int64_t shift; 
    for(int64_t i = 0; i < digits; ++i){
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
 
int32_t DiscreteGaussianSamplingGadget::xorshift25(){ 
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
  
int64_t DiscreteGaussianSamplingGadget::gen_discrete_gauss(float c){

    int32_t sigma = this->sigma;
    int32_t k;
    int32_t s;
    float tmp;
    int32_t i0; 
    float x;
    int32_t j; 
    float exp_inp; 
    uint32_t bias; 
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


int32_t DiscreteGaussianSamplingGadget::d1_d2_of_karney(){
    int32_t k ;
    bool reject;   
    int32_t k_times_k_minus_one;
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
        for(int32_t i = 0; i < k_times_k_minus_one; ++i){ 
            if(xorshift25() >= 20351791){
                reject = true;
                break;
            }
        }  
    }while(reject);  
    return k; 
}