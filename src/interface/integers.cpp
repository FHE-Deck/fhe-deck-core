
#include "interface/integers.h"
#include "interface/fhe_context.h"

using namespace FHEDeck;
 
DigitConfig::DigitConfig(FHEContext& context, int32_t base, int32_t size){
    this->context = context; 
    this->base = base; 
    this->size = size;
    init();
}
 
void DigitConfig::init(){ 
    bits_base = Utils::power_times(base, 2); 
    bits_in_plaintext_space = bits_base+1;
    digit_plaintext_encoding = context.get_default_plaintext_encoding();
    digit_plaintext_encoding.set_plaintext_space(2 * base);
    digit_plaintext_encoding.set_type(PlaintextEncodingType::full_domain);

    /// Compute hte max that can be handled with base and the number of digits.
    max = (base-1);
    int64_t temp_base = 1;
    for(int32_t i = 1; i < size; ++i){
        temp_base = temp_base * (int64_t)base;
        max += (int64_t)(base-1) * temp_base;
    }
}
 
DigitInteger DigitConfig::encrypt(int64_t message){
    return DigitInteger(message, *this);
}


int64_t DigitConfig::decrypt(const DigitInteger& ciphertext){
    return context.decrypt(ciphertext);
}


DigitInteger::DigitInteger(int64_t message, const DigitConfig& config){
    this->config = config;
 
    std::vector<int64_t> digits_message = int_decomp(message); 
    if(this->config.size < digits_message.size()){
        throw std::logic_error("The target siye of the DigitInteger is smaller than the number of digits of the message!");
    } 
    encrypted_digits.reserve(this->config.size);
    if(this->config.context.config->is_secret_key_set){
        for(int64_t digit: digits_message){
            encrypted_digits.push_back(this->config.context.encrypt(digit, this->config.digit_plaintext_encoding));
        } 
    }else{
        for(int64_t digit: digits_message){
            encrypted_digits.push_back(this->config.context.encrypt_public(digit, this->config.digit_plaintext_encoding));
        } 
    } 
    /// NOTE: Here we padd the encrypted digits with zeros.
    for(int32_t i = digits_message.size(); i < this->config.size; i++){
        encrypted_digits.push_back(this->config.context.encrypt(0, this->config.digit_plaintext_encoding));
    }
}
 
DigitInteger::DigitInteger(const DigitConfig& config, const std::vector<Ciphertext>& encrypted_digits){ 
    this->config = config; 
    this->encrypted_digits = encrypted_digits;
}
 
DigitInteger::DigitInteger(const DigitInteger& other){
    this->config = other.config;
    this->encrypted_digits = other.encrypted_digits; 
}

DigitInteger& DigitInteger::operator=(const DigitInteger& other){
    if(this == &other){
        return *this;
    }
    this->config = other.config;
    this->encrypted_digits = other.encrypted_digits; 
    return *this;
}

DigitInteger::DigitInteger(const DigitConfig& config, const RNSInteger& other){
    /// (I don't want to handle overflow there because in practice it should rarely happen, but handling it will cost another digit in subtraction)
    if(config.max < 2*(other.base.modulus-1)) throw std::logic_error("DigitInteger(const DigitConfig& config, const CRTInteger& other): DigitConfig max should be larger than or equal 2*(other.base.modulus-1).");
   
    this->config = config;
    this->encrypted_digits = decompose_rns_element(
        other.encrypted_digits[0], 
        other.base.modulus,  
        other.base.cofactors[0]); 
 
    for(int32_t i = 1; i < other.base.size; ++i){ 
        DigitInteger next_to_sum(config, decompose_rns_element(
            other.encrypted_digits[i], 
            other.base.modulus,  
            other.base.cofactors[i]));

        /// Add the digit to out
        next_to_sum = next_to_sum.addition_with_carry(this->encrypted_digits);
        next_to_sum.resisze();
        /// NOTE: This number may be bigger than the modulus. We are going to test this with the subtraction later.
        /// Modulus reduction: next_to_sum = next_to_sum - modulus. 
        // If next_to_sum < 0, then no modulus reduction required because next_to_sum smaller thean the Modulus.
        // If next_to_sum >= 0, then we take next_to_sum without the carry digit.   
        DigitInteger mod_subtracted = next_to_sum.subtract_with_carry(other.base.modulus);
        Ciphertext is_smaller_than_zero = 1 - mod_subtracted.encrypted_digits.back();
        mod_subtracted.resisze();  
        this->encrypted_digits = choose_digits(next_to_sum.encrypted_digits, mod_subtracted.encrypted_digits, is_smaller_than_zero);
    } 
}
 
std::vector<Ciphertext> DigitInteger::decompose_rns_element(const Ciphertext& in, int64_t modulus, int64_t rns_coef)const{
    auto digit_extract = [](int64_t m, int64_t rns_coef, int64_t modulus, int32_t base, int32_t digit_index) -> int64_t{
        int64_t message = (m * rns_coef) % modulus;
        if(digit_index==0){
            return message % base;
        }
        int64_t pow_base = Utils::pow(digit_index, base); 
        return ((int32_t)(message / pow_base)) % base;
    };
   
    std::vector<HomomorphicAccumulator> digit_extractions;
    digit_extractions.reserve(config.size); 
    for(int32_t i = 0; i < config.size; ++i){ 
       digit_extractions.push_back(config.context.setup_function(
            std::bind(digit_extract, std::placeholders::_1, rns_coef, modulus, this->config.base, i),
            in.encoding, 
            config.digit_plaintext_encoding));
    }  
    std::vector<Ciphertext> out = config.context.eval(in, digit_extractions);
 
    return out;
}   


std::vector<int64_t> DigitInteger::int_decomp(int64_t x)const{ 
    std::vector<int64_t> out;
    int32_t digits = Utils::number_of_digits(x, config.base); 
    int64_t shift = 0;
    int64_t mask = config.base - 1; 
    out.resize(digits);
    for(int32_t i = 0; i < digits; i++){
        shift = config.bits_base * i;
        out[i] = (x & mask) >> shift;  
        mask = mask << config.bits_base;
    }
    return out;
}

int64_t DigitInteger::int_comp(const std::vector<int64_t>& in)const{
    int64_t composed = 0;
    int64_t curr = 1;
    for(int32_t i = 0; i < in.size(); i++){
        composed += curr * in[i];
        curr *= config.base;
    } 
    return composed;
}

void DigitInteger::verify_ciphertext_vector(const std::vector<Ciphertext>& digits){
    for(Ciphertext ct: digits){
        if(ct.encoding.get_plaintext_space() != config.digit_plaintext_encoding.get_plaintext_space()){
            throw std::logic_error("Plaintext space of the input digits does not match the expected plaintext space!");
        }
    }
}


template<typename DigitType>
DigitInteger DigitInteger::addition_with_carry(const std::vector<DigitType> digits)const{
    /// TODO: These homomorphic accumulators etc. can be actually precomputed in the constructor.
    /// Problem sort of is that each DigitInteger has its own set of homomorphic accumulators...
    auto digit_extract_0 = [](int32_t m, int32_t bits_base) -> int32_t{
        return m & ((1 << bits_base)-1);
    };
    std::function<int64_t(int64_t)> digit_extract = std::bind(digit_extract_0, std::placeholders::_1, config.bits_base);
    auto msb_extract_0 = [](int32_t m, int32_t bits_base) -> int32_t{
        return (m >> bits_base) & ((1 << bits_base)-1);
    };
    std::function<int64_t(int64_t)> msb_extract = std::bind(msb_extract_0, std::placeholders::_1, config.bits_base);
 
    std::vector<HomomorphicAccumulator> func_spec;
    func_spec.push_back(config.context.setup_function(digit_extract, config.digit_plaintext_encoding));
    func_spec.push_back(config.context.setup_function(msb_extract, config.digit_plaintext_encoding));

    std::vector<Ciphertext> out;
    out.reserve(this->encrypted_digits.size()+1);
    std::vector<Ciphertext> carries;
    carries.reserve(this->encrypted_digits.size());
    std::vector<Ciphertext> temp = config.context.eval(encrypted_digits[0]+digits[0], func_spec);
    out.push_back(temp[0]);
    carries.push_back(temp[1]);
    for(int32_t i = 1; i < encrypted_digits.size(); ++i){
        std::vector<Ciphertext> temp = config.context.eval(encrypted_digits[i]+digits[i]+ carries[i-1], func_spec); 
        carries.push_back(temp[1]);
        out.push_back(temp[0] );
    }
    out.push_back(carries[encrypted_digits.size()-1]);
    DigitInteger out_digit(config, out);
    return out_digit;
}


DigitInteger DigitInteger::operator+(const DigitInteger& other)const{  
    if(!is_compatible(other)){
        throw std::logic_error("The two DigitIntegers are not compatible! Either different size or base.");
    } 
    DigitInteger out = addition_with_carry(other.encrypted_digits);
    out.resisze();
    return out; 
}
 
DigitInteger DigitInteger::operator+(const int64_t scalar)const{  
    std::vector<int64_t> scalar_decomp = int_decomp(scalar);
    if(this->config.size < scalar_decomp.size()){
        throw std::logic_error("The target size of the DigitInteger is smaller than the number of digits of the scalar!");
    }
    for(int32_t i = scalar_decomp.size(); i < config.size; i++){
        scalar_decomp.push_back(0);
    }
    DigitInteger out = addition_with_carry(scalar_decomp);
    out.resisze();
    return out; 
}

DigitInteger DigitInteger::add_with_carry(const DigitInteger& other)const{
    if(!is_compatible(other)){
        throw std::logic_error("The two DigitIntegers are not compatible! Either different size or base.");
    } 
    return addition_with_carry(other.encrypted_digits); 
}
  
DigitInteger DigitInteger::add_with_carry(const int64_t scalar)const{
    std::vector<int64_t> scalar_decomp = int_decomp(scalar);
    if(this->config.size < scalar_decomp.size()){
        throw std::logic_error("The target size of the DigitInteger is smaller than the number of digits of the scalar!");
    }
    for(int32_t i = scalar_decomp.size(); i < config.size; i++){
        scalar_decomp.push_back(0);
    }
    return addition_with_carry(scalar_decomp); 
}

template<typename DigitType>
DigitInteger DigitInteger::subtraction_with_carry(const std::vector<DigitType> digits)const{
 
    auto digit_extract_0 = [](int32_t m, int32_t bits_base) -> int32_t{
        if(m >= (1<<bits_base)){
            int32_t num = m - (1<<(bits_base+1));
            return num + (1<<bits_base);
        }else{
            return m;
        }
    };
    std::function<int64_t(int64_t)> digit_extract = std::bind(digit_extract_0, std::placeholders::_1, config.bits_base);
    auto msb_extract_0 = [](int32_t m, int32_t bits_base) -> int32_t{
        if(m >= (1<<bits_base)){
            return 1;
        }else{
            return 0;
        }
    };
    std::function<int64_t(int64_t)> msb_extract = std::bind(msb_extract_0, std::placeholders::_1, config.bits_base);

    std::vector<HomomorphicAccumulator> func_spec;
    func_spec.push_back(config.context.setup_function(digit_extract, config.digit_plaintext_encoding));
    func_spec.push_back(config.context.setup_function(msb_extract, config.digit_plaintext_encoding));

    std::vector<Ciphertext> out;
    out.reserve(this->encrypted_digits.size()+1);
    std::vector<Ciphertext> carries;
    carries.reserve(this->encrypted_digits.size());

    std::vector<Ciphertext> temp = config.context.eval(encrypted_digits[0]-digits[0], func_spec);
    out.push_back(temp[0]);
    carries.push_back(temp[1]);
    for(int32_t i = 1; i < encrypted_digits.size(); ++i){
        std::vector<Ciphertext> temp = config.context.eval(encrypted_digits[i]-digits[i]-carries[i-1], func_spec);
        carries.push_back(temp[1]);
        out.push_back(temp[0]);
    }
    out.push_back(carries[encrypted_digits.size()-1]);
    DigitInteger out_digit(config, out);
    return out_digit;
}

DigitInteger DigitInteger::operator-(const DigitInteger& other)const{ 
    if(!is_compatible(other)){
        throw std::logic_error("The two DigitIntegers are not compatible! Either different size or base.");
    }  
    DigitInteger out = subtraction_with_carry(other.encrypted_digits);  
    out.resisze(); 
    return out; 
}

 
DigitInteger DigitInteger::operator-(const int64_t scalar)const{  
    std::vector<int64_t> scalar_decomp = int_decomp(scalar); 
    if(this->config.size < scalar_decomp.size()){
        throw std::logic_error("The target size of the DigitInteger is smaller than the number of digits of the scalar!");
    }
    /// Padd with zeros.
    for(int32_t i = scalar_decomp.size(); i < config.size; i++){
        scalar_decomp.push_back(0);
    }
    DigitInteger out = subtraction_with_carry(scalar_decomp); 
    out.resisze();
    return out; 
}

DigitInteger DigitInteger::subtract_with_carry(const DigitInteger& other)const{
    if(!is_compatible(other)){
        throw std::logic_error("The two DigitIntegers are not compatible! Either different size or base.");
    } 
    return subtraction_with_carry(other.encrypted_digits);  
}

DigitInteger DigitInteger::subtract_with_carry(const int64_t scalar)const{
    std::vector<int64_t> scalar_decomp = int_decomp(scalar); 
    if(this->config.size < scalar_decomp.size()){
        throw std::logic_error("The target size of the DigitInteger is smaller than the number of digits of the scalar!");
    }
    /// Padd with zeros.
    for(int32_t i = scalar_decomp.size(); i < config.size; i++){
        scalar_decomp.push_back(0);
    }
    return subtraction_with_carry(scalar_decomp);  
}


DigitInteger DigitInteger::operator*(const int64_t scalar)const{
    throw std::logic_error("Not implemented yet!");
}

DigitInteger DigitInteger::operator*(const DigitInteger& other)const{
    throw std::logic_error("Not implemented yet!");
}

void DigitInteger::resisze(){ 
    int32_t size = encrypted_digits.size();
    if(size == config.size){
        return;
    }else if(size > config.size){
        encrypted_digits.resize(config.size); 
    }else if(config.context.config->is_secret_key_set){
        for(int32_t i = this->config.size; i < size; i++){
            encrypted_digits.push_back(config.context.encrypt(0, config.digit_plaintext_encoding));
        }
    }else{
        for(int32_t i = this->config.size; i < size; i++){
            encrypted_digits.push_back(config.context.encrypt_public(0, config.digit_plaintext_encoding));
        }
    } 
}

bool DigitInteger::is_compatible(const DigitInteger& other)const{
    if(this->config.size != other.config.size){
        return false;
    }
    if(this->config.base != other.config.base){
        return false;
    }
    return true;
}
 
std::vector<Ciphertext> DigitInteger::choose_digits(const std::vector<Ciphertext>& in_1, const std::vector<Ciphertext>& in_2, Ciphertext& bit){
    if(in_1.size() != in_2.size()){
        throw std::logic_error("Input vectors have to have the same size.");
    }
    std::vector<Ciphertext> out; 
    for(int32_t i = 0; i < in_1.size(); ++i){
        out.push_back(choose_digit(in_1[i], in_2[i], bit));
    }
    return out;
}

Ciphertext DigitInteger::choose_digit(const Ciphertext& in_0, const Ciphertext& in_1, const Ciphertext& bit){
    Ciphertext neg_bit = 1 - bit; 
    auto choise = [](int32_t m) -> int32_t {
        int32_t bit = m & 1;
        if(bit == 0){
            return 0;
        }else{
            return m >> 1;
        }
    };

    HomomorphicAccumulator acc = config.context.setup_function(choise, config.digit_plaintext_encoding);
    Ciphertext ct_0_shift = in_0;
    ct_0_shift = ct_0_shift * 2;
    ct_0_shift = ct_0_shift + neg_bit;
    Ciphertext ct_1_shift = in_1;
    ct_1_shift = ct_1_shift * 2;
    ct_1_shift = ct_1_shift + bit;
    Ciphertext choise_0 = config.context.eval(ct_0_shift, acc);
    Ciphertext choise_1 = config.context.eval(ct_1_shift, acc);
    return choise_0 + choise_1;

}


RNSInteger::RNSInteger(int64_t message, const RNSConfig& base){
    this->base = base; 
    std::vector<int32_t> digits_message = base.decompose(message);
    this->encrypted_digits.reserve(digits_message.size()); 
    if(this->base.context.config->is_secret_key_set){
        for(int32_t i = 0; i < digits_message.size(); ++i){ 
            encrypted_digits.push_back(this->base.context.encrypt(digits_message[i], base.plaintext_encodings[i]));
        }
    }else if(this->base.context.config->is_secret_key_set){
        for(int32_t i = 0; i < digits_message.size(); ++i){ 
            encrypted_digits.push_back(this->base.context.encrypt_public(digits_message[i], base.plaintext_encodings[i]));
        }
    }else{
        throw std::logic_error("No keys initialized!");
    }
}

RNSInteger::RNSInteger(std::vector<Ciphertext> cts, const RNSConfig& base){
    this->encrypted_digits = cts; 
    this->base = base;
}

RNSInteger::RNSInteger(const RNSInteger& other){
    this->encrypted_digits = other.encrypted_digits;
    this->base = other.base;
}

RNSInteger::RNSInteger(const DigitInteger& other, const RNSConfig& base){ 
    this->base = base;   
    auto rns_digit_extract = [](int64_t digit, DigitConfig& config, int64_t modulus, int32_t index) -> int64_t{ 
        return (digit * Utils::pow(index, config.base)) % modulus; 
    };
  
    this->encrypted_digits.reserve(base.size);
    for(int j = 0; j < base.size; ++j){
        HomomorphicAccumulator rns_digit_extract_acc = base.context.setup_function(
            std::bind(rns_digit_extract, std::placeholders::_1, other.config, base.crt_base[j], 0),
            other.config.digit_plaintext_encoding,
            base.plaintext_encodings[j]); 
        encrypted_digits.push_back(base.context.eval(other.encrypted_digits[0], rns_digit_extract_acc));
    }
     
    for(int32_t i = 1; i < other.config.size; ++i){ 
        for(int j = 0; j < base.size; ++j){
            HomomorphicAccumulator rns_digit_extract_acc = base.context.setup_function(
                std::bind(rns_digit_extract, std::placeholders::_1, other.config, base.crt_base[j], i),
                other.config.digit_plaintext_encoding,
                base.plaintext_encodings[j]); 
                encrypted_digits[j] = encrypted_digits[j] + base.context.eval(other.encrypted_digits[i], rns_digit_extract_acc);
        }

    }
  
}

RNSInteger RNSInteger::operator+(const RNSInteger& other){
    if(this->base.modulus  != other.base.modulus){
        throw std::logic_error("Modulus of the CRTIntegers do not match!");
    } 
    std::vector<Ciphertext> out;
    out.reserve(this->base.crt_base.size());
    for(int32_t i = 0; i < base.crt_base.size(); ++i){
        out.push_back(this->encrypted_digits[i] + other.encrypted_digits[i]);
    }
    return RNSInteger(out, base);
}

RNSInteger RNSInteger::operator+(const int64_t scalar){
    std::vector<int32_t> scalar_decomp =  base.decompose(scalar); 
    std::vector<Ciphertext> out;
    out.reserve(base.crt_base.size());
    for(int32_t i = 0; i < base.crt_base.size(); ++i){
        out.push_back(this->encrypted_digits[i] + scalar_decomp[i]);
    }
    return RNSInteger(out, base);
}

RNSInteger RNSInteger::operator-(const RNSInteger& other){
    if(this->base.modulus != other.base.modulus){
        throw std::logic_error("Modulus of the CRTIntegers do not match!");
    } 
    std::vector<Ciphertext> out;
    out.reserve(base.crt_base.size());
    for(int32_t i = 0; i < base.crt_base.size(); ++i){
        out.push_back(this->encrypted_digits[i] - other.encrypted_digits[i]);
    }
    return RNSInteger(out, base);
}

RNSInteger RNSInteger::operator-(const int64_t scalar){
    std::vector<int32_t> scalar_decomp =  base.decompose(scalar); 
    std::vector<Ciphertext> out;
    out.reserve(base.crt_base.size());
    for(int32_t i = 0; i < base.crt_base.size(); ++i){
        out.push_back(this->encrypted_digits[i] - scalar_decomp[i]);
    }
    return RNSInteger(out, base);
}

RNSInteger RNSInteger::operator*(const int64_t scalar){
    std::vector<int32_t> scalar_decomp =  base.decompose(scalar); 
    std::vector<Ciphertext> out;
    out.reserve(base.crt_base.size());
    for(int32_t i = 0; i < base.crt_base.size(); ++i){
        out.push_back(this->encrypted_digits[i] * scalar_decomp[i]);
    }
    return RNSInteger(out, base);
}

RNSInteger RNSInteger::operator*(const RNSInteger& other){ 
    if(this->base.modulus != other.base.modulus){
        throw std::logic_error("Modulus of the CRTIntegers do not match!");
    } 
    std::vector<Ciphertext> out;

    auto times_in_two_and_square = [](int32_t m, int32_t modulus) -> int32_t{
        m = Utils::integer_mod_form(m * m, modulus);
        return Utils::integer_mod_form(m * Utils::mod_inv(4, modulus), modulus);
    }; 
    
    std::vector<HomomorphicAccumulator> func_specs;
    func_specs.reserve(base.crt_base.size());
     
    /// TODO: Take the encodings from the base.
    for(int32_t i = 0; i < base.crt_base.size(); ++i){
        std::function<int64_t(int64_t)> function = std::bind(times_in_two_and_square, std::placeholders::_1, base.crt_base[i]);
        PlaintextEncoding encoding = this->base.context.get_default_plaintext_encoding();
        encoding.set_plaintext_space(base.crt_base[i]);
        encoding.set_type(PlaintextEncodingType::full_domain);  
        func_specs.push_back(this->base.context.setup_function(function, encoding));  
    }   
    out.reserve(base.crt_base.size());
    for(int32_t i = 0; i < base.crt_base.size(); ++i){ 
        out.push_back(this->base.context.eval(this->encrypted_digits[i] + other.encrypted_digits[i], func_specs[i]) - 
                      this->base.context.eval(this->encrypted_digits[i] - other.encrypted_digits[i], func_specs[i]));
    } 
    return RNSInteger(out, base);
}
  
void RNSConfig::init(){
    modulus = 1; 
    size = crt_base.size();
    for(int32_t i = 0; i < size; i++){
        modulus *= crt_base[i];
    }
    factors.resize(size);
    m_list.resize(size);
    cofactors.resize(size);
    plaintext_encodings.resize(size);
    for(int32_t i = 0; i < size; i++){
        factors[i] = modulus / crt_base[i];
        std::pair<int64_t, std::pair<int64_t, int64_t>> crt_base_tuple = Utils::extended_euclidean_algorithm(factors[i], crt_base[i]);
        m_list[i] = crt_base_tuple.second.first;
        cofactors[i] = factors[i] * m_list[i];

        plaintext_encodings[i] = context.get_default_plaintext_encoding();
        plaintext_encodings[i].set_plaintext_space(crt_base[i]);
        plaintext_encodings[i].set_type(PlaintextEncodingType::full_domain); 

    }
}

RNSConfig::RNSConfig(FHEContext& context, std::vector<int32_t> crt_base){
    this->context = context;
    this->crt_base = crt_base;
    init();
}

std::vector<int32_t> RNSConfig::decompose(int64_t x)const{
    std::vector<int32_t> out;
    out.resize(crt_base.size());
    for(int32_t i = 0; i < crt_base.size(); i++){
        out[i] = (int32_t)(x % crt_base[i]);
    }
    return out;
}

int64_t RNSConfig::compose(const std::vector<int32_t>& digits)const{
    int64_t composed = 0;
    for(int32_t i = 0; i < crt_base.size(); i++){
        composed += Utils::integer_mod_form(digits[i] * cofactors[i], modulus);
    }
    return Utils::integer_mod_form(composed, modulus);
}


RNSInteger RNSConfig::encrypt(int64_t message){
    return RNSInteger(message, *this);
}

int64_t RNSConfig::decrypt(const RNSInteger& ciphertext){
    return context.decrypt(ciphertext);
}
 