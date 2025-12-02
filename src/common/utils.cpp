#include "common/utils.h"
 
using namespace FHEDeck;
  
int32_t Utils::power_times(int64_t x, int64_t base){ 
    if(x <= 1){
        return 1;
    }  
    int64_t base_bits = ceil(log2(base)); 
    int64_t x_bits = ceil(log2(x));  
    int32_t k = ceil((double)x_bits/(double)base_bits);   
    return k;  
}

int32_t Utils::number_of_digits(int64_t x, int64_t base){
    if(x == 0){
        return 1;
    }
    return floor(log2(x)/log2(base))+1;  
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
 
std::pair<int64_t, std::pair<int64_t, int64_t>> Utils::extended_euclidean_algorithm(int64_t a, int64_t b){
    int64_t x0 = 0;    
   int64_t x1 = 1;
   int64_t y0 = 1;    
   int64_t y1 = 0;
   while(a != 0){ 
        auto dv = std::div(b, a);
        int64_t q = dv.quot; 
        b = a;
        a = dv.rem;
        int64_t temp = y0;
        y0 = y1;
        y1 = temp - q * y1;
        temp = x0;
        x0 = x1;
        x1 = temp - q * x1;
   }     
    int64_t gcd = b;
    int64_t x = x0;
    int64_t y = y0; 
    return {gcd, {x, y}};
}
    
int64_t Utils::mod_inv(int64_t in, int64_t modulus){
    auto [gcd, coeffs] = extended_euclidean_algorithm(in, modulus); 
    return Utils::integer_mod_form(coeffs.first, modulus);
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
}
  
int64_t Utils::integer_mod_form(int64_t in, int64_t Q){ 
    if(in >= 0){
        return in % Q;
    }else{
        int64_t temp = in % Q; 
        return (Q + temp) % Q; 
    }
}
  
std::vector<int64_t> Utils::integer_decomp(int64_t in , int32_t basis, int32_t k, int32_t ell){
    std::vector<int64_t> dec_out;
    dec_out.resize(ell);
    int64_t mask = basis-1;
    int64_t shift;
    for(int32_t i = 0; i < ell; ++i){
        shift = k*i; 
        dec_out[i] = (in & mask) >> shift; 
        mask = mask << k;
    }
    return dec_out;
} 
 
int64_t Utils::integer_compose(const std::vector<int64_t>& dec_in, int32_t basis, int32_t ell){
    int64_t out = dec_in[0];
    int64_t temp_basis = 1;
    for(int32_t i = 1; i < ell; ++i){
        temp_basis *= basis;
        out += dec_in[i] * temp_basis;
    }
    return out;
}  
 
int64_t Utils::max(const std::vector<int64_t>& in){
    int64_t max = in[0];
    for(int32_t i = 1; i < in.size(); ++i){
        if(max < in[i]){
            max = in[i];
        }
    }
    return max;
}

int64_t Utils::min(const std::vector<int64_t>& in){
    int64_t max = in[0];
    for(int32_t i = 1; i < in.size(); ++i){
        if(max > in[i]){
            max = in[i];
        }
    }
    return max;
}

double Utils::mean(const std::vector<int64_t>& in){
    double sum = 0;
    for(int32_t i = 0; i < in.size(); ++i){
        sum += (double)in[i];
    }
    return sum / (double)in.size();
}

double Utils::variance(const std::vector<int64_t>& in){
    double m = mean(in); 
    double sum = 0.0;
    double square = 0.0;
    for(int32_t i = 0; i < in.size(); ++i){
        square = in[i] - m;
        square *= square;
        sum += square;
    } 
    return sum/(double)in.size();
}

double Utils::variance(const std::vector<int64_t>& in, double mean){
    double m = mean;
    double sum = 0.0;
    double square = 0.0;
    for(int32_t i = 0; i < in.size(); ++i){
        square = in[i] - m;
        square *= square;
        sum += square;
    } 
    return sum/(double)in.size();
}

double Utils::standard_deviation(const std::vector<int64_t>& in){ 
    return sqrt(Utils::variance(in, in.size())); 
}

 
double Utils::standard_deviation(const std::vector<int64_t>& in, double mean){ 
    return sqrt(Utils::variance(in, mean)); 
}

int64_t Utils::infinity_norm(const std::vector<int64_t>& in){
    int64_t out = 0 ;
    int64_t curr;
    for(int32_t i = 0; i < in.size(); ++i){
        curr = Utils::abs(in[i]);
        if(curr > out){
            out = curr;
        }
    }
    return out;
}

long* Utils::count_occurences(const std::vector<int64_t>& in){
    int64_t max = Utils::max(in);
    int64_t min = Utils::min(in);
    int32_t size = max - min + 1;
    long* occurences = new long[size];
    for(int32_t i = 0; i < size; ++i){
        occurences[i] = 0;
    }
    for(int32_t i = 0; i < in.size(); ++i){ 
        occurences[in[i]-min] += 1;
    } 
    return occurences;
}

int64_t Utils::count_positive(const std::vector<int64_t>& in){
    int64_t out = 0;
    for(int32_t i = 0; i < in.size(); ++i){
        if(in[i] > 0){
            out++;
        }
    }
    return out;
}

int64_t Utils::count_negative(const std::vector<int64_t>& in){
    int64_t out = 0;
    for(int32_t i = 0; i < in.size(); ++i){
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
}

unsigned long LongIntegerMultipler::mul(unsigned long in_1, unsigned long in_2){   
    std::vector<int64_t> decomp  = Utils::integer_decomp(in_2, base, bits_base, modulus_log_base);   
    unsigned long out = (in_1 * decomp[modulus_log_base - 1]) % modulus;   
    for(int32_t i = 1; i < modulus_log_base; ++i){  
        out = (out * base) % modulus; 
        out = (out +  (decomp[modulus_log_base - i - 1] * in_1)) % modulus;  
    } 
    return out;
}
 


