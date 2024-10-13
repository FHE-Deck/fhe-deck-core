#include "utils.h"
 
using namespace fhe_deck;

void Utils::set_polynomial_from_array(NTL::ZZ_pX &poly, int64_t *f, int32_t sizeof_f, int64_t Q){
    NTL::ZZ_p coef;
    coef.init(NTL::ZZ(Q));
    for(int32_t i = 0; i < sizeof_f; ++i){
        coef = f[i];
        NTL::SetCoeff(poly, i, coef);
    } 
}

void Utils::set_array_from_polynomial(int64_t *f, int32_t sizeof_array, NTL::ZZ_pX poly){ 
    for(int32_t i = 0; i < sizeof_array; ++i){
        f[i] = 0;
    }
    int64_t deg = NTL::deg(poly);
    for(int32_t i = 0; i <= deg; ++i){
         f[i] = NTL::conv<long>(poly[i]);
    } 
}


void Utils::add_polynomials(int64_t *out, int64_t *in_1, int64_t *in_2, int32_t sizeof_in_1, int32_t sizeof_in_2){
    if(sizeof_in_1 < sizeof_in_2){
        for(int32_t i = 0; i < sizeof_in_1; ++i){
            out[i] = in_1[i] + in_2[i];
        }
        for(int32_t i = sizeof_in_1; i < sizeof_in_2; ++i){
            out[i] = in_2[i];
        }
    }else{
        for(int32_t i = 0; i < sizeof_in_2; ++i){
            out[i] = in_1[i] + in_2[i];
        }
        for(int32_t i = sizeof_in_2; i < sizeof_in_1; ++i){
            out[i] = in_2[i];
        }
    }
}


void Utils::mod_polynomial(int64_t *out, int64_t *in, int32_t sizeof_in, int64_t modulus){
    for(int32_t i = 0; i < sizeof_in; +i){
        out[i] = in[i] % modulus;
    }
}


void Utils::mul_scalar(int64_t *out, int64_t *in, int32_t sizeof_in, int64_t scalar){
    for(int32_t i = 0; i < sizeof_in; ++i){
        out[i] = in[i] * scalar;
    }
}


void Utils::mul_mod(int64_t *out, int64_t *in_1, int32_t sizeof_in_1, int64_t *in_2, int32_t sizeof_in_2, int64_t N, int64_t modulus, RingType ring){
   NTL::ZZ_pX in_1_poly;
   Utils::set_polynomial_from_array(in_1_poly, in_1, sizeof_in_1, modulus);
   NTL::ZZ_pX in_2_poly;
   Utils::set_polynomial_from_array(in_2_poly, in_2, sizeof_in_2, modulus);
   NTL::ZZ_pX res = NTL::MulMod(in_1_poly, in_2_poly, get_ring_poly(ring, N, modulus)); 
   Utils::set_array_from_polynomial(out, N, res);
}


void Utils::add_mod(int64_t *out, int64_t *in_1, int32_t sizeof_in_1, int64_t *in_2, int32_t sizeof_in_2, int64_t N, int64_t modulus){
   NTL::ZZ_pX in_1_poly;
   Utils::set_polynomial_from_array(in_1_poly, in_1, sizeof_in_1, modulus);
   NTL::ZZ_pX in_2_poly;
   Utils::set_polynomial_from_array(in_2_poly, in_2, sizeof_in_2, modulus);
   NTL::ZZ_pX res = in_1_poly + in_2_poly;
   Utils::set_array_from_polynomial(out, N, res);
}

void Utils::sub_mod(int64_t *out, int64_t *in_1, int32_t sizeof_in_1, int64_t *in_2, int32_t sizeof_in_2, int64_t N, int64_t modulus){
   NTL::ZZ_pX in_1_poly;
   Utils::set_polynomial_from_array(in_1_poly, in_1, sizeof_in_1, modulus);
   NTL::ZZ_pX in_2_poly;
   Utils::set_polynomial_from_array(in_2_poly, in_2, sizeof_in_2, modulus);
   NTL::ZZ_pX res = in_1_poly - in_2_poly;
   Utils::set_array_from_polynomial(out, N, res);
}


void Utils::neg_mod(int64_t *out, int64_t *in, int32_t size, int64_t modulus){
    for(int32_t i = 0; i < size; ++i){
        out[i] = Utils::integer_mod_form(-in[i], modulus);
    }

}

NTL::ZZ_pX Utils::get_ring_poly(RingType ring, int64_t N, int64_t modulus){
    NTL::ZZ_pX out;
    int64_t *psi_arr = new long[N+1]; 
    psi_arr[N] = 1;
    for(int32_t i=1; i < N; ++i){
            psi_arr[i] = 0;
    } 
    if(ring==RingType::cyclic){
        psi_arr[0] = modulus-1;
    }else{
        psi_arr[0] = 1;
    }
    Utils::set_polynomial_from_array(out, psi_arr, N+1, modulus); 
    delete[] psi_arr;
    return out;
}


void Utils::cp(int64_t *out, int64_t *in, int32_t size){
    for(int32_t i =0; i < size; ++i){
        out[i] = in[i];
    }
}


int32_t Utils::power_times(int64_t x, int64_t base){ 
    int64_t base_bits = ceil(log2(base)); 
    int64_t x_bits = ceil(log2(x));  
    int32_t k = ceil((double)x_bits/(double)base_bits);
    return k; 
}


bool Utils::is_power_of(int64_t x, int64_t base){
    int64_t temp = base; 
    int32_t k = 1;
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

int64_t Utils::pow(int64_t x, int64_t base){
    int64_t out = 1;
    for(int32_t i= 0; i < x; ++i){
        out *= base;
    }
    return out;
 }


int64_t Utils::abs(int64_t x){
    if(x >= 0){
        return x;
    }
    return -x;
}


int32_t Utils::number_of_bits(int64_t x){ 
    int64_t power_of_two = 2;
    for(int32_t m = 1; m < 63; ++m){
        if(x < power_of_two){
            return m;
        }
        power_of_two = power_of_two << 1;
    } 
    return 64;
}

int64_t Utils::mod_inv(int64_t in, int64_t modulus){
    return NTL::InvMod(in, modulus);
}

int64_t Utils::square_and_div_by_4(int64_t in, int64_t modulus){
    int64_t square = NTL::MulMod(in, in, modulus);
    int64_t inv_four = NTL::InvMod(4, modulus);
    return NTL::MulMod(square, inv_four, modulus);
}


int64_t Utils::eval_poly_mod(int64_t in, int* poly, int32_t poly_size, int64_t modulus){
    int64_t ret = poly[0];
    int64_t powers_of_in = 1;
    int64_t term = 0;
    for(int32_t i = 1; i < poly_size; ++i){
        powers_of_in = NTL::MulMod(powers_of_in, in, modulus);
        term =  NTL::MulMod(powers_of_in, poly[i], modulus);
        ret = NTL::AddMod(ret, term, modulus);
    }
    return ret;
}



bool Utils::is_eq_poly(int64_t *in_1, int64_t *in_2, int32_t sizeof_in){
    for(int32_t i = 0; i < sizeof_in; ++i){
        if(in_1[i] != in_2[i]){
            return false;
        }
    }
    return true;
}


void Utils::rotate_poly(int64_t *out_poly, int64_t *in_poly, int32_t poly_size, int32_t rot){
    int32_t overflow= poly_size - rot ;  
      for(int32_t i = 0; i < overflow; ++i){   
            out_poly[i+rot] = in_poly[i];
            
      }
      for(int32_t i = 0; i < rot; ++i){ 
            out_poly[i] = in_poly[overflow + i];
      }
}



void Utils::negacyclic_rotate_poly(int64_t *out_poly, int64_t *in_poly, int32_t poly_size, int32_t rot){

    long* temp = new long[poly_size];
    if(rot >= poly_size){
        for(int32_t i = 0; i < poly_size; ++i){
            temp[i] = -in_poly[i];
        }
        rot = rot - poly_size;
    }else{
        for(int32_t i = 0; i < poly_size; ++i){
            temp[i] = in_poly[i];
        }
    } 
    // NOTE We implement negacyclic rotate actually -> it changes the sign of rot first coefficients
    int32_t overflow=poly_size - rot ;  
    for(int32_t i = 0; i < overflow; ++i){   
        out_poly[i+rot] = temp[i];
    }
    for(int32_t i = 0; i < rot; ++i){ 
        out_poly[i] = -temp[overflow + i];
    }
    delete[] temp;
}



int64_t Utils::integer_rounding(int64_t in, int64_t Q, int64_t t){
    int64_t signed_in = Utils::integer_signed_form(in, Q);
    double scale = (double)t/(double)Q; 
    return (long)std::round(scale * (double)signed_in);
}

void Utils::array_rounding(int64_t *out, int64_t *in, int32_t sizeof_in, int64_t Q, int64_t t){
    for(int32_t i = 0; i < sizeof_in; ++i){
        out[i] = Utils::integer_rounding(in[i], Q, t);
    }  
}
 
int64_t Utils::integer_signed_form(int64_t in, int64_t Q){
    int64_t half = Q/2;
    int64_t minus_half = -half;
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
 
void Utils::array_signed_form(int64_t *out, int64_t *in, int32_t sizeof_in, int64_t Q){ 
    for(int32_t i = 0; i < sizeof_in; ++i){ 
        out[i] =  Utils::integer_signed_form(in[i], Q);
    }
}


int64_t Utils::integer_mod_form(int64_t in, int64_t Q){ 
    if(in >= 0){
        return in % Q;
    }else{
        int64_t temp = in % Q; 
        return (Q + temp) % Q; 
    }
}

void Utils::array_mod_form(int64_t *out, int64_t *in, int32_t sizeof_in, int64_t Q){ 
    for(int32_t i = 0; i < sizeof_in; ++i){ 
        out[i] = Utils::integer_mod_form(in[i], Q);
    }
}

 

void Utils::round_and_mod_reduce(int64_t *out_poly, double *in_poly, int64_t modulus, int32_t sizeof_in_poly){ 
      for(int32_t i = 0; i < sizeof_in_poly; ++i){
            out_poly[i] = (long)round(in_poly[i]) % modulus;
            
      }  
}


void Utils::round_and_mod_reduce(int64_t *out_poly, long double *in_poly_l, int64_t modulus, int32_t sizeof_in_poly){ 
      long double Q_l = (long double) modulus;
      for(int32_t i = 0; i < sizeof_in_poly; ++i){
            
            out_poly[i] = round(fmodl(in_poly_l[i], Q_l)); 
      }  
}

void Utils::round_and_mod_reduce_power_of_two(int64_t *out_poly, double *in_poly, int64_t mask, int32_t sizeof_in_poly){
      for(int32_t i = 0; i < sizeof_in_poly; ++i){
            
            out_poly[i] = ((long)in_poly[i]) & mask; 
      }
}

void Utils::round_and_mod_reduce_power_of_two(int64_t *out_poly, long double *in_poly, int64_t mask, int32_t sizeof_in_poly){
      for(int32_t i = 0; i < sizeof_in_poly; ++i){ 
            out_poly[i] = ((long)in_poly[i]) & mask;
            
      }
}

void Utils::mod_reduce_power_of_two(int64_t *out_poly, int64_t *in_poly, int64_t mask, int32_t sizeof_in_poly){
      for(int32_t i = 0; i < sizeof_in_poly; ++i){
            out_poly[i] = in_poly[i] & mask; 
      }
} 


void Utils::mod_reduce(int64_t *out_poly, int64_t *in_poly, int64_t modulus, int32_t sizeof_in_poly){
      for(int32_t i = 0; i < sizeof_in_poly; ++i){  
      out_poly[i] = in_poly[i] % modulus;
   }
} 


void Utils::mod_reduce(int64_t *out_poly, long double *in_poly_l, int64_t modulus, int32_t sizeof_in_poly){
      //long double coef;
      long double Q_l = (long double) modulus;
      for(int32_t i = 0; i < sizeof_in_poly; ++i){  
      out_poly[i] = round(fmodl(in_poly_l[i], Q_l));  
    }
}  

 


std::string Utils::to_string(int64_t *poly, int32_t sizeof_poly){
    if(sizeof_poly==0){
        return "[]";
    }
    if(sizeof_poly==1){
        return "[" + std::to_string(poly[0]) + "]" ;
    }
    std::string str = "[";
    for(int32_t i = 0; i < sizeof_poly-1; ++i){
        str += std::to_string(poly[i]) + ", ";
    }
    str += std::to_string(poly[sizeof_poly-1]) + "]";
    return str;
}

std::string Utils::to_string(double *poly, int32_t sizeof_poly){
    if(sizeof_poly==0){
        return "[]";
    }
    if(sizeof_poly==1){
        return "[" + std::to_string(poly[0]) + "]" ;
    }
    std::string str = "[";
    for(int32_t i = 0; i < sizeof_poly-1; ++i){
        str += std::to_string(poly[i]) + ", ";
    }
    str += std::to_string(poly[sizeof_poly-1]) + "]";
    return str;
}


std::string Utils::to_string(int32_t *poly, int32_t sizeof_poly){
    if(sizeof_poly==0){
        return "[]";
    }
    if(sizeof_poly==1){
        return "[" + std::to_string(poly[0]) + "]" ;
    }
    std::string str = "[";
    for(int32_t i = 0; i < sizeof_poly-1; ++i){
        str += std::to_string(poly[i]) + ", ";
    }
    str += std::to_string(poly[sizeof_poly-1]) + "]";
    return str;
}


std::string Utils::complex_to_string(fftw_complex* in, int32_t from, int32_t size){
    std::string out = "";
    for(int32_t i = from; i < size; ++i){
        out += "(";
        out += std::to_string(in[i][0])  ;
        out += ", " ;
        out +=  std::to_string(in[i][1]) ;
        out += ")";
    }
    return out;
}

void Utils::set(long* out, long* in, int32_t sizeof_in){
    for(int32_t i = 0; i < sizeof_in; ++i){
        out[i] = in[i];
    }
}


void Utils::integer_decomp(int64_t *dec_out, int64_t in , int32_t basis, int32_t k, int32_t ell){
    int64_t mask = basis-1;
    int64_t shift;
    for(int32_t i = 0; i < ell; ++i){
        shift = k*i; 
        dec_out[i] = (in & mask) >> shift; 
        mask = mask << k;
    }
}

int64_t Utils::integer_compose(int64_t *dec_in, int32_t basis, int32_t ell){
    int64_t out = dec_in[0];
    int64_t temp_basis = 1;
    for(int32_t i = 1; i < ell; ++i){
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
void Utils::decomp(int64_t **d_ct, long* poly, int32_t sizeof_poly, int32_t basis, int32_t k, int32_t ell){
    int64_t mask = basis-1;
    int64_t shift;
    for(int32_t i = 0; i < ell; ++i){
        // TODO: Change and test for shift += k (starting from shift = -k) - should give a mini speedup
        shift = k*i;
        for(int32_t j=0; j < sizeof_poly; ++j){
            // The jth coefficients of the ith (decomposed) polynomial
            d_ct[i][j] = (poly[j] & mask) >> shift;
        }
        mask = mask << k;
    }
}

/*
Note that we assume the input polynomial has coefficients in [0, Q-1]
*/
void Utils::signed_decomp(int64_t **d_ct, long* poly, int32_t sizeof_poly, int32_t basis, int32_t k, int32_t ell, int64_t Q){
    long* signed_poly = new long[sizeof_poly]; 
    long* sign = new long[sizeof_poly];
    Utils::array_signed_form(signed_poly, poly, sizeof_poly, Q); 
    int64_t half = Q/2;
    for(int32_t i = 0; i < sizeof_poly; ++i){ 
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
    for(int32_t j = 0; j < ell; ++j){
        for(int32_t i = 0; i < sizeof_poly; ++i){
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
void Utils::decomp(int32_t **d_ct, long* poly, int32_t sizeof_poly, int32_t basis, int32_t k, int32_t ell){
    int32_t mask = basis-1;
    int32_t shift;
    for(int32_t i = 0; i < ell; ++i){
        shift = k*i;
        for(int32_t j=0; j < sizeof_poly; ++j){
            // The jth coefficients of the ith (decomposed) polynomial
            d_ct[i][j] = (poly[j] & mask) >> shift;
        }
        mask = mask << k;
    }
} 


void Utils::compose(int64_t *out, int64_t **d_ct, int32_t sizeof_poly, int32_t basis, int32_t ell){
    Utils::set(out, d_ct[0], sizeof_poly);
    //std::cout << "In the loop: " << std::endl;
    int32_t temp_basis = 1; 
    long* temp_array = new long[sizeof_poly];
    for(int32_t i=1; i < ell; ++i){
        temp_basis = temp_basis * basis;
        //std::cout << "d_ct[" << i << "]: " << utils::to_string(d_ct[i], sizeof_poly) << std::endl;
        Utils::mul_scalar(temp_array, d_ct[i], sizeof_poly, temp_basis);
        //std::cout << "temp_array: " << utils::to_string(temp_array, sizeof_poly) << std::endl;
        Utils::add_polynomials(out, out, temp_array, sizeof_poly, sizeof_poly); 
    } 
    delete[] temp_array;
}
  

int64_t Utils::max(long* in, int32_t N){
    int64_t max = in[0];
    for(int32_t i = 1; i < N; ++i){
        if(max < in[i]){
            max = in[i];
        }
    }
    return max;
}

int64_t Utils::min(long* in, int32_t N){
    int64_t max = in[0];
    for(int32_t i = 1; i < N; ++i){
        if(max > in[i]){
            max = in[i];
        }
    }
    return max;
}

double Utils::mean(long* in, int32_t N){
    double sum = 0;
    for(int32_t i = 0; i < N; ++i){
        sum += (double)in[i];
    }
    return sum / (double)N;
}

double Utils::variance(long* in, int32_t N){
    double m = mean(in, N); 
    double sum = 0.0;
    double square = 0.0;
    for(int32_t i = 0; i < N; ++i){
        square = in[i] - m;
        square *= square;
        sum += square;
    } 
    return sum/(double)N;
}

double Utils::variance(long* in, int32_t N, double mean){
    double m = mean;
    double sum = 0.0;
    double square = 0.0;
    for(int32_t i = 0; i < N; ++i){
        square = in[i] - m;
        square *= square;
        sum += square;
    } 
    return sum/(double)N;
}

double Utils::standard_deviation(long* in, int32_t N){ 
    return sqrt(Utils::variance(in, N)); 
}

 
double Utils::standard_deviation(long* in, int32_t N, double mean){ 
    return sqrt(Utils::variance(in, N, mean)); 
}

int64_t Utils::infinity_norm(long* in, int32_t N){
    int64_t out = 0 ;
    int64_t curr;
    for(int32_t i = 0; i < N; ++i){
        curr = Utils::abs(in[i]);
        if(curr > out){
            out = curr;
        }
    }
    return out;
}

long* Utils::count_occurences(long* in, int32_t N){
    int64_t max = Utils::max(in, N);
    int64_t min = Utils::min(in, N);
    int32_t size = max - min + 1;
    long* occurences = new long[size];
    for(int32_t i = 0; i < size; ++i){
        occurences[i] = 0;
    }
    for(int32_t i = 0; i < N; ++i){ 
        occurences[in[i]-min] += 1;
    } 
    return occurences;
}

int64_t Utils::count_positive(long* in, int32_t N){
    int64_t out = 0;
    for(int32_t i = 0; i < N; ++i){
        if(in[i] > 0){
            out++;
        }
    }
    return out;
}

int64_t Utils::count_negative(long* in, int32_t N){
    int64_t out = 0;
    for(int32_t i = 0; i < N; ++i){
        if(in[i] < 0){
            out++;
        }
    }
    return out;
}


LongIntegerMultipler::LongIntegerMultipler(unsigned long modulus){ 
    this->modulus = modulus;
    unsigned long bits_modulus = Utils::power_times(modulus, 2);  
    this->bits_base = 63 - bits_modulus; 
    this->base = Utils::pow(bits_base, 2); 
    this->modulus_log_base = Utils::power_times(modulus, base);  
    this->decomp = std::unique_ptr<long[]>(new long[modulus_log_base]); 
}

unsigned long LongIntegerMultipler::mul(unsigned long in_1, unsigned long in_2){  
    Utils::integer_decomp(decomp.get(), in_2, base, bits_base, modulus_log_base);   
    unsigned long out = (in_1 * decomp[modulus_log_base - 1]) % modulus;   
    for(int32_t i = 1; i < modulus_log_base; ++i){  
        out = (out * base) % modulus; 
        out = (out +  (decomp[modulus_log_base - i - 1] * in_1)) % modulus;  
    } 
    return out;
}