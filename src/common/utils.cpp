#include "utils.h"

 
using namespace fhe_deck;

void Utils::set_polynomial_from_array(NTL::ZZ_pX &poly, long *f, int sizeof_f, long Q){
    NTL::ZZ_p coef;
    coef.init(NTL::ZZ(Q));
    for(int i = 0; i < sizeof_f; ++i){
        coef = f[i];
        NTL::SetCoeff(poly, i, coef);
    } 
}

void Utils::set_array_from_polynomial(long *f, int sizeof_array, NTL::ZZ_pX poly){ 
    for(int i = 0; i < sizeof_array; ++i){
        f[i] = 0;
    }
    long deg = NTL::deg(poly);
    for(int i = 0; i <= deg; ++i){
         f[i] = NTL::conv<long>(poly[i]);
    } 
}


void Utils::add_polynomials(long *out, long *in_1, long *in_2, int sizeof_in_1, int sizeof_in_2){
    if(sizeof_in_1 < sizeof_in_2){
        for(int i = 0; i < sizeof_in_1; ++i){
            out[i] = in_1[i] + in_2[i];
        }
        for(int i = sizeof_in_1; i < sizeof_in_2; ++i){
            out[i] = in_2[i];
        }
    }else{
        for(int i = 0; i < sizeof_in_2; ++i){
            out[i] = in_1[i] + in_2[i];
        }
        for(int i = sizeof_in_2; i < sizeof_in_1; ++i){
            out[i] = in_2[i];
        }
    }
}


void Utils::mod_polynomial(long *out, long *in, int sizeof_in, long modulus){
    for(int i = 0; i < sizeof_in; +i){
        out[i] = in[i] % modulus;
    }
}


void Utils::mul_scalar(long *out, long *in, int sizeof_in, long scalar){
    for(int i = 0; i < sizeof_in; ++i){
        out[i] = in[i] * scalar;
    }
}


void Utils::mul_mod(long *out, long *in_1, int sizeof_in_1, long *in_2, int sizeof_in_2, long N, long modulus, RingType ring){
   NTL::ZZ_pX in_1_poly;
   Utils::set_polynomial_from_array(in_1_poly, in_1, sizeof_in_1, modulus);
   NTL::ZZ_pX in_2_poly;
   Utils::set_polynomial_from_array(in_2_poly, in_2, sizeof_in_2, modulus);
   NTL::ZZ_pX res = NTL::MulMod(in_1_poly, in_2_poly, get_ring_poly(ring, N, modulus)); 
   Utils::set_array_from_polynomial(out, N, res);
}


void Utils::add_mod(long *out, long *in_1, int sizeof_in_1, long *in_2, int sizeof_in_2, long N, long modulus){
   NTL::ZZ_pX in_1_poly;
   Utils::set_polynomial_from_array(in_1_poly, in_1, sizeof_in_1, modulus);
   NTL::ZZ_pX in_2_poly;
   Utils::set_polynomial_from_array(in_2_poly, in_2, sizeof_in_2, modulus);
   NTL::ZZ_pX res = in_1_poly + in_2_poly;
   Utils::set_array_from_polynomial(out, N, res);
}

void Utils::sub_mod(long *out, long *in_1, int sizeof_in_1, long *in_2, int sizeof_in_2, long N, long modulus){
   NTL::ZZ_pX in_1_poly;
   Utils::set_polynomial_from_array(in_1_poly, in_1, sizeof_in_1, modulus);
   NTL::ZZ_pX in_2_poly;
   Utils::set_polynomial_from_array(in_2_poly, in_2, sizeof_in_2, modulus);
   NTL::ZZ_pX res = in_1_poly - in_2_poly;
   Utils::set_array_from_polynomial(out, N, res);
}


void Utils::neg_mod(long *out, long *in, int size, long modulus){
    for(int i = 0; i < size; ++i){
        out[i] = Utils::integer_mod_form(-in[i], modulus);
    }

}

NTL::ZZ_pX Utils::get_ring_poly(RingType ring, long N, long modulus){
    NTL::ZZ_pX out;
    long *psi_arr = new long[N+1]; 
    psi_arr[N] = 1;
    for(int i=1; i < N; ++i){
            psi_arr[i] = 0;
    } 
    if(ring==cyclic){
        psi_arr[0] = modulus-1;
    }else{
        psi_arr[0] = 1;
    }
    Utils::set_polynomial_from_array(out, psi_arr, N+1, modulus); 
    return out;
}


void Utils::cp(long *out, long *in, int size){
    for(int i =0; i < size; ++i){
        out[i] = in[i];
    }
}


int Utils::power_times(long x, long base){ 
    long base_bits = ceil(log2(base)); 
    long x_bits = ceil(log2(x));  
    int k = ceil((double)x_bits/(double)base_bits);
    return k; 
}


bool Utils::is_power_of(long x, long base){
    long temp = base; 
    int k = 1;
    while(temp < x){
        temp *= base;
        k++;
    }
    if(temp == x){
        return true;
    }else{
        return false;
    }
}


long Utils::abs(long x){
    if(x >= 0){
        return x;
    }
    return -x;
}


int Utils::number_of_bits(long x){ 
    long power_of_two = 2;
    for(int m = 1; m < 63; ++m){
        if(x < power_of_two){
            return m;
        }
        power_of_two = power_of_two << 1;
    } 
    return 64;
}

long Utils::mod_inv(long in, long modulus){
    return NTL::InvMod(in, modulus);
}

long Utils::square_and_div_by_4(long in, long modulus){
    long square = NTL::MulMod(in, in, modulus);
    long inv_four = NTL::InvMod(4, modulus);
    return NTL::MulMod(square, inv_four, modulus);
}


long Utils::eval_poly_mod(long in, int* poly, int poly_size, long modulus){
    long ret = poly[0];
    long powers_of_in = 1;
    long term = 0;
    for(int i = 1; i < poly_size; ++i){
        powers_of_in = NTL::MulMod(powers_of_in, in, modulus);
        term =  NTL::MulMod(powers_of_in, poly[i], modulus);
        ret = NTL::AddMod(ret, term, modulus);
    }
    return ret;
}



bool Utils::is_eq_poly(long *in_1, long *in_2, int sizeof_in){
    for(int i = 0; i < sizeof_in; ++i){
        if(in_1[i] != in_2[i]){
            return false;
        }
    }
    return true;
}


void Utils::rotate_poly(long *out_poly, long *in_poly, int poly_size, int rot){
    int overflow= poly_size - rot ;  
      for(int i = 0; i < overflow; ++i){   
            out_poly[i+rot] = in_poly[i];
            
      }
      for(int i = 0; i < rot; ++i){ 
            out_poly[i] = in_poly[overflow + i];
      }
}



void Utils::negacyclic_rotate_poly(long *out_poly, long *in_poly, int poly_size, int rot){

    long* temp = new long[poly_size];
    if(rot >= poly_size){
        for(int i = 0; i < poly_size; ++i){
            temp[i] = -in_poly[i];
        }
        rot = rot - poly_size;
    }else{
        for(int i = 0; i < poly_size; ++i){
            temp[i] = in_poly[i];
        }
    } 
    // NOTE We implement negacyclic rotate actually -> it changes the sign of rot first coefficients
    int overflow=poly_size - rot ;  
    for(int i = 0; i < overflow; ++i){   
        out_poly[i+rot] = temp[i];
    }
    for(int i = 0; i < rot; ++i){ 
        out_poly[i] = -temp[overflow + i];
    }
    delete[] temp;
}



long Utils::integer_rounding(long in, long Q, long t){
    long signed_in = Utils::integer_signed_form(in, Q);
    double scale = (double)t/(double)Q; 
    return (long)std::round(scale * (double)signed_in);
}

void Utils::array_rounding(long *out, long *in, int sizeof_in, long Q, long t){
    for(int i = 0; i < sizeof_in; ++i){
        out[i] = Utils::integer_rounding(in[i], Q, t);
    }  
}
 
long Utils::integer_signed_form(long in, long Q){
    long half = Q/2;
    long minus_half = -half;
    // If its between 0, and -half, then return in
    // If its between half and Q, then return in-Q
    // If its between -half, -Q, then return Q+in - right?
     
    if(in <= half && in > minus_half){
        return in;
    }else if(in > half){
        return in-Q;
    }else{
        return in+Q;
    }
    //return in-Q ;
}
 
void Utils::array_signed_form(long *out, long *in, int sizeof_in, long Q){ 
    for(int i = 0; i < sizeof_in; ++i){ 
        out[i] =  Utils::integer_signed_form(in[i], Q);
    }
}


long Utils::integer_mod_form(long in, long Q){ 
    if(in >= 0){
        return in % Q;
    }else{
        long temp = in % Q; 
        return (Q + temp) % Q; 
    }
}

void Utils::array_mod_form(long *out, long *in, int sizeof_in, long Q){ 
    for(int i = 0; i < sizeof_in; ++i){ 
        out[i] = Utils::integer_mod_form(in[i], Q);
    }
}

 

void Utils::round_and_mod_reduce(long *out_poly, double *in_poly, long modulus, int sizeof_in_poly){ 
      for(int i = 0; i < sizeof_in_poly; ++i){
            out_poly[i] = (long)round(in_poly[i]) % modulus;
            
      }  
}


void Utils::round_and_mod_reduce(long *out_poly, long double *in_poly_l, long modulus, int sizeof_in_poly){ 
      long double Q_l = (long double) modulus;
      for(int i = 0; i < sizeof_in_poly; ++i){
            
            out_poly[i] = round(fmodl(in_poly_l[i], Q_l)); 
      }  
}

void Utils::round_and_mod_reduce_power_of_two(long *out_poly, double *in_poly, long mask, int sizeof_in_poly){
      for(int i = 0; i < sizeof_in_poly; ++i){
            
            out_poly[i] = ((long)in_poly[i]) & mask; 
      }
}

void Utils::round_and_mod_reduce_power_of_two(long *out_poly, long double *in_poly, long mask, int sizeof_in_poly){
      for(int i = 0; i < sizeof_in_poly; ++i){ 
            out_poly[i] = ((long)in_poly[i]) & mask;
            
      }
}

void Utils::mod_reduce_power_of_two(long *out_poly, long *in_poly, long mask, int sizeof_in_poly){
      for(int i = 0; i < sizeof_in_poly; ++i){
            out_poly[i] = in_poly[i] & mask; 
      }
} 


void Utils::mod_reduce(long *out_poly, long *in_poly, long modulus, int sizeof_in_poly){
      for(int i = 0; i < sizeof_in_poly; ++i){  
      out_poly[i] = in_poly[i] % modulus;
   }
} 


void Utils::mod_reduce(long *out_poly, long double *in_poly_l, long modulus, int sizeof_in_poly){
      //long double coef;
      long double Q_l = (long double) modulus;
      for(int i = 0; i < sizeof_in_poly; ++i){  
      out_poly[i] = round(fmodl(in_poly_l[i], Q_l));  
    }
}  













std::string Utils::to_string(long *poly, int sizeof_poly){
    if(sizeof_poly==0){
        return "[]";
    }
    if(sizeof_poly==1){
        return "[" + std::to_string(poly[0]) + "]" ;
    }
    std::string str = "[";
    for(int i = 0; i < sizeof_poly-1; ++i){
        str += std::to_string(poly[i]) + ", ";
    }
    str += std::to_string(poly[sizeof_poly-1]) + "]";
    return str;
}

std::string Utils::to_string(double *poly, int sizeof_poly){
    if(sizeof_poly==0){
        return "[]";
    }
    if(sizeof_poly==1){
        return "[" + std::to_string(poly[0]) + "]" ;
    }
    std::string str = "[";
    for(int i = 0; i < sizeof_poly-1; ++i){
        str += std::to_string(poly[i]) + ", ";
    }
    str += std::to_string(poly[sizeof_poly-1]) + "]";
    return str;
}


std::string Utils::to_string(int *poly, int sizeof_poly){
    if(sizeof_poly==0){
        return "[]";
    }
    if(sizeof_poly==1){
        return "[" + std::to_string(poly[0]) + "]" ;
    }
    std::string str = "[";
    for(int i = 0; i < sizeof_poly-1; ++i){
        str += std::to_string(poly[i]) + ", ";
    }
    str += std::to_string(poly[sizeof_poly-1]) + "]";
    return str;
}


void Utils::set(long* out, long* in, int sizeof_in){
    for(int i = 0; i < sizeof_in; ++i){
        out[i] = in[i];
    }
}


void Utils::integer_decomp(long *dec_out, long in , int basis, int k, int ell){
    long mask = basis-1;
    long shift;
    for(int i = 0; i < ell; ++i){
        shift = k*i; 
        dec_out[i] = (in & mask) >> shift; 
        mask = mask << k;
    }
}

long Utils::integer_compose(long *dec_in, int basis, int ell){
    long out = dec_in[0];
    long temp_basis = 1;
    for(int i = 1; i < ell; ++i){
        temp_basis *= basis;
        out += dec_in[i] * temp_basis;
    }
    return out;
}

/*
- d_ct is a two dimensional array, that holds polynomials.
- basis is the decomposition basis. We assume that its a power of two
- ell = log_basis(limit) (usually limit is the modulus)
- param are the ntru parameters
*/
void Utils::decomp(long **d_ct, long* poly, int sizeof_poly, int basis, int k, int ell){
    long mask = basis-1;
    long shift;
    for(int i = 0; i < ell; ++i){
        // TODO: Change and test for shift += k (starting from shift = -k) - should give a mini speedup
        shift = k*i;
        for(int j=0; j < sizeof_poly; ++j){
            // The jth coefficients of the ith (decomposed) polynomial
            d_ct[i][j] = (poly[j] & mask) >> shift;
        }
        mask = mask << k;
    }
}

/*
Note that we assume the input polynomial has coefficients in [0, Q-1]
*/
void Utils::signed_decomp(long **d_ct, long* poly, int sizeof_poly, int basis, int k, int ell, long Q){
    long* signed_poly = new long[sizeof_poly]; 
    long* sign = new long[sizeof_poly];
    Utils::array_signed_form(signed_poly, poly, sizeof_poly, Q); 
    long half = Q/2;
    for(int i = 0; i < sizeof_poly; ++i){ 
        //signed_poly[i] =  utils::integer_signed_form(poly[i], Q);
        if(poly[i] <= half){
            signed_poly[i] = poly[i];
            sign[i] = 1;
        }else{
            signed_poly[i] = abs(poly[i]-Q);
            sign[i] = -1;
        }
    }
    Utils::decomp(d_ct, signed_poly, sizeof_poly, basis, k, ell);
    for(int j = 0; j < ell; ++j){
        for(int i = 0; i < sizeof_poly; ++i){
            d_ct[j][i] = d_ct[j][i] * sign[i];
        }
    }
    delete[] sign;
    delete[] signed_poly;
}


 
/*
- d_ct is a two dimensional array, that holds polynomials.
- basis is the decomposition basis. We assume that its a power of two
- ell = log_basis(limit) (usually limit is the modulus)
- param are the ntru parameters
*/ 
void Utils::decomp(int **d_ct, long* poly, int sizeof_poly, int basis, int k, int ell){
    int mask = basis-1;
    int shift;
    for(int i = 0; i < ell; ++i){
        shift = k*i;
        for(int j=0; j < sizeof_poly; ++j){
            // The jth coefficients of the ith (decomposed) polynomial
            d_ct[i][j] = (poly[j] & mask) >> shift;
        }
        mask = mask << k;
    }
} 


void Utils::compose(long *out, long **d_ct, int sizeof_poly, int basis, int ell){
    Utils::set(out, d_ct[0], sizeof_poly);
    //std::cout << "In the loop: " << std::endl;
    int temp_basis = 1; 
    long* temp_array = new long[sizeof_poly];
    for(int i=1; i < ell; ++i){
        temp_basis = temp_basis * basis;
        //std::cout << "d_ct[" << i << "]: " << utils::to_string(d_ct[i], sizeof_poly) << std::endl;
        Utils::mul_scalar(temp_array, d_ct[i], sizeof_poly, temp_basis);
        //std::cout << "temp_array: " << utils::to_string(temp_array, sizeof_poly) << std::endl;
        Utils::add_polynomials(out, out, temp_array, sizeof_poly, sizeof_poly); 
    } 
    delete[] temp_array;
}


/*
TODO: Deprecated: its implemented now in the gadget class
*/
void Utils::gaussian_sample(long **out, long* in, int sizeof_poly, int basis, int k, int ell, Sampler &rand){
    int mask = basis-1;
    int shift;  
    long* gaussians = new long[sizeof_poly];
    for(int j = 0; j < sizeof_poly; ++j){
        gaussians[j] = 0;
    }
    long prev_gauss;
    for(int i = 0; i < ell; ++i){
        shift = k*i;
        for(int j=0; j < sizeof_poly; ++j){
            prev_gauss = gaussians[j];
            // Here we sample the new gaussian  
            //gaussians[j] = rand.gaussian(basis, 0, stddev);
            gaussians[j] = rand.gaussian(basis);
            // The jth coefficients of the ith (decomposed) polynomial 
            out[i][j] = (in[j] & mask) >> shift; 
            out[i][j] += gaussians[j] - prev_gauss;
            // I think i can actually shift this by k, instead of dividing it by basis
            // gaussians[j] = gaussians[j]/basis;
            gaussians[j] = gaussians[j] >> k;
        }
        mask = mask << k;
    }
    delete[] gaussians; 
}
 


long Utils::max(long* in, int N){
    long max = in[0];
    for(int i = 1; i < N; ++i){
        if(max < in[i]){
            max = in[i];
        }
    }
    return max;
}

long Utils::min(long* in, int N){
    long max = in[0];
    for(int i = 1; i < N; ++i){
        if(max > in[i]){
            max = in[i];
        }
    }
    return max;
}

double Utils::mean(long* in, int N){
    double sum = 0;
    for(int i = 0; i < N; ++i){
        sum += (double)in[i];
    }
    return sum / (double)N;
}

double Utils::variance(long* in, int N){
    double m = mean(in, N); 
    double sum = 0.0;
    double square = 0.0;
    for(int i = 0; i < N; ++i){
        square = in[i] - m;
        square *= square;
        sum += square;
    } 
    return sum/(double)N;
}

double Utils::variance(long* in, int N, double mean){
    double m = mean;
    double sum = 0.0;
    double square = 0.0;
    for(int i = 0; i < N; ++i){
        square = in[i] - m;
        square *= square;
        sum += square;
    } 
    return sum/(double)N;
}

double Utils::standard_deviation(long* in, int N){ 
    return sqrt(Utils::variance(in, N)); 
}

 
double Utils::standard_deviation(long* in, int N, double mean){ 
    return sqrt(Utils::variance(in, N, mean)); 
}

long Utils::infinity_norm(long* in, int N){
    long out = 0 ;
    long curr;
    for(int i = 0; i < N; ++i){
        curr = Utils::abs(in[i]);
        if(curr > out){
            out = curr;
        }
    }
    return out;
}

long* Utils::count_occurences(long* in, int N){
    long max = Utils::max(in, N);
    long min = Utils::min(in, N);
    int size = max - min + 1;
    long* occurences = new long[size];
    for(int i = 0; i < size; ++i){
        occurences[i] = 0;
    }
    for(int i = 0; i < N; ++i){ 
        occurences[in[i]-min] += 1;
    } 
    return occurences;
}

long Utils::count_positive(long* in, int N){
    long out = 0;
    for(int i = 0; i < N; ++i){
        if(in[i] > 0){
            out++;
        }
    }
    return out;
}

long Utils::count_negative(long* in, int N){
    long out = 0;
    for(int i = 0; i < N; ++i){
        if(in[i] < 0){
            out++;
        }
    }
    return out;
}
