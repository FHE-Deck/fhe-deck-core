
#include "interface/integers.h"
#include "interface/fhe_context.h"

using namespace fhe_deck;


DigitConfig::DigitConfig(FHEContext* context, int32_t base, int32_t size){
    this->context = context; 
    this->base = base; 
    this->size = size;
    init();
}


void DigitConfig::init(){ 
    bits_base = Utils::power_times(base, 2); 
    bits_in_plaintext_space = bits_base+1;
    digit_plaintext_encoding = context->get_default_plaintext_encoding();
    digit_plaintext_encoding.set_plaintext_space(2 * base);
    digit_plaintext_encoding.set_type(PlaintextEncodingType::full_domain);
}

void DigitInteger::init(){ 
    bits_base = Utils::power_times(base, 2); 
    bits_in_plaintext_space = bits_base+1;
    digit_plaintext_encoding = context->get_default_plaintext_encoding();
    digit_plaintext_encoding.set_plaintext_space(2 * base);
    digit_plaintext_encoding.set_type(PlaintextEncodingType::full_domain);
}


DigitInteger::DigitInteger(const DigitConfig& config, int64_t message){
    this->context = config.context;
    this->base = config.base;
    this->size = config.size;
    this->bits_base = config.bits_base;
    this->bits_in_plaintext_space = config.bits_in_plaintext_space;
    this->digit_plaintext_encoding = config.digit_plaintext_encoding; 
    std::vector<int64_t> digits_message = int_decomp(message); 
    if(size < digits_message.size()){
        throw std::logic_error("The target siye of the DigitInteger is smaller than the number of digits of the message!");
    }
    this->size = size;
    encrypted_digits.reserve(size);
    if(context->config->is_secret_key_set){
        for(int64_t digit: digits_message){
            encrypted_digits.push_back(context->encrypt(digit, digit_plaintext_encoding));
        } 
    }else{
        for(int64_t digit: digits_message){
            encrypted_digits.push_back(context->encrypt_public(digit, digit_plaintext_encoding));
        } 
    } 
    /// NOTE: Here we padd the encrypted digits with zeros.
    for(int32_t i = digits_message.size(); i < size; i++){
        encrypted_digits.push_back(context->encrypt(0, digit_plaintext_encoding));
    }
}

DigitInteger::DigitInteger(FHEContext* context, std::vector<Ciphertext> encrypted_digits, int32_t base){
    this->context = context;
    this->encrypted_digits = encrypted_digits;
    this->base = base; 
    this->size = encrypted_digits.size();
    init();
    /// TODO: Verify whether plaintext space in encrypted digits is correct.
}

DigitInteger::DigitInteger(FHEContext* context, int64_t message, int32_t base, int32_t size){ 
    this->context = context;
    this->base = base;
    init();
    std::vector<int64_t> digits_message = int_decomp(message); 
    if(size < digits_message.size()){
        throw std::logic_error("The target siye of the DigitInteger is smaller than the number of digits of the message!");
    }
    this->size = size;
    encrypted_digits.reserve(size);
    if(context->config->is_secret_key_set){
        for(int64_t digit: digits_message){
            encrypted_digits.push_back(context->encrypt(digit, digit_plaintext_encoding));
        } 
    }else{
        for(int64_t digit: digits_message){
            encrypted_digits.push_back(context->encrypt_public(digit, digit_plaintext_encoding));
        } 
    } 
    /// NOTE: Here we padd the encrypted digits with zeros.
    for(int32_t i = digits_message.size(); i < size; i++){
        encrypted_digits.push_back(context->encrypt(0, digit_plaintext_encoding));
    }
}


std::vector<int64_t> DigitInteger::int_decomp(int64_t x)const{ 
    std::vector<int64_t> out;
    int32_t digits = Utils::number_of_digits(x, base); 
    int64_t shift = 0;
    int64_t mask = base - 1; 
    out.resize(digits);
    for(int32_t i = 0; i < digits; i++){
        shift = bits_base * i;
        out[i] = (x & mask) >> shift;  
        mask = mask << bits_base;
    }
    return out;
}

int64_t DigitInteger::int_comp(const std::vector<int64_t>& in)const{
    int64_t composed = 0;
    int64_t curr = 1;
    for(int32_t i = 0; i < in.size(); i++){
        composed += curr * in[i];
        curr *= base;
    } 
    return composed;
}

void DigitInteger::verify_ciphertext_vector(const std::vector<Ciphertext>& digits){
    for(Ciphertext ct: digits){
        if(ct.encoding.get_plaintext_space() != digit_plaintext_encoding.get_plaintext_space()){
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
    std::function<int64_t(int64_t)> digit_extract = std::bind(digit_extract_0, std::placeholders::_1, bits_base);
    auto msb_extract_0 = [](int32_t m, int32_t bits_base) -> int32_t{
        return (m >> bits_base) & ((1 << bits_base)-1);
    };
    std::function<int64_t(int64_t)> msb_extract = std::bind(msb_extract_0, std::placeholders::_1, bits_base);
 
    std::vector<HomomorphicAccumulator> func_spec;
    func_spec.push_back(context->setup_function(digit_extract, digit_plaintext_encoding));
    func_spec.push_back(context->setup_function(msb_extract, digit_plaintext_encoding));

    std::vector<Ciphertext> out;
    out.reserve(this->encrypted_digits.size()+1);
    std::vector<Ciphertext> carries;
    carries.reserve(this->encrypted_digits.size());
    std::vector<Ciphertext> temp = context->eval(encrypted_digits[0]+digits[0], func_spec);
    out.push_back(temp[0]);
    carries.push_back(temp[1]);
    for(int32_t i = 1; i < encrypted_digits.size(); ++i){
        std::vector<Ciphertext> temp = context->eval(encrypted_digits[i]+digits[i], func_spec); 
        carries.push_back(temp[1]);
        out.push_back(temp[0] + carries[i-1]);
    }
    out.push_back(carries[encrypted_digits.size()-1]);
    DigitInteger out_digit(context, out, base);
    return out_digit;
}

DigitInteger DigitInteger::operator+(const DigitInteger& other)const{  
    if(!is_compatible(other)){
        throw std::logic_error("The two DigitIntegers are not compatible! Either different size or base.");
    } 
    DigitInteger out = addition_with_carry(other.encrypted_digits);
    out.resisze(size);
    return out; 
}
 
DigitInteger DigitInteger::operator+(const int64_t scalar)const{  
    std::vector<int64_t> scalar_decomp = int_decomp(scalar);
    if(this->size < scalar_decomp.size()){
        throw std::logic_error("The target size of the DigitInteger is smaller than the number of digits of the scalar!");
    }
    for(int32_t i = scalar_decomp.size(); i < size; i++){
        scalar_decomp.push_back(0);
    }
    DigitInteger out = addition_with_carry(scalar_decomp);
    out.resisze(size);
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
    if(this->size < scalar_decomp.size()){
        throw std::logic_error("The target size of the DigitInteger is smaller than the number of digits of the scalar!");
    }
    for(int32_t i = scalar_decomp.size(); i < size; i++){
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
    std::function<int64_t(int64_t)> digit_extract = std::bind(digit_extract_0, std::placeholders::_1, bits_base);
    auto msb_extract_0 = [](int32_t m, int32_t bits_base) -> int32_t{
        if(m >= (1<<bits_base)){
            return 1;
        }else{
            return 0;
        }
    };
    std::function<int64_t(int64_t)> msb_extract = std::bind(msb_extract_0, std::placeholders::_1, bits_base);

    std::vector<HomomorphicAccumulator> func_spec;
    func_spec.push_back(context->setup_function(digit_extract, digit_plaintext_encoding));
    func_spec.push_back(context->setup_function(msb_extract, digit_plaintext_encoding));

    std::vector<Ciphertext> out;
    out.reserve(this->encrypted_digits.size()+1);
    std::vector<Ciphertext> carries;
    carries.reserve(this->encrypted_digits.size());

    std::vector<Ciphertext> temp = context->eval(encrypted_digits[0]-digits[0], func_spec);
    out.push_back(temp[0]);
    carries.push_back(temp[1]);
    for(int32_t i = 1; i < encrypted_digits.size(); ++i){
        std::vector<Ciphertext> temp = context->eval(encrypted_digits[i]-digits[i]-carries[i-1], func_spec);
        carries.push_back(temp[1]);
        out.push_back(temp[0]);
    }
    out.push_back(carries[encrypted_digits.size()-1]);
    DigitInteger out_digit(context, out, base);
    return out_digit;
}

DigitInteger DigitInteger::operator-(const DigitInteger& other)const{ 
    if(!is_compatible(other)){
        throw std::logic_error("The two DigitIntegers are not compatible! Either different size or base.");
    } 
    DigitInteger out = subtraction_with_carry(other.encrypted_digits); 
    out.resisze(size);
    return out; 
}



DigitInteger DigitInteger::operator-(const int64_t scalar)const{  
    std::vector<int64_t> scalar_decomp = int_decomp(scalar); 
    if(this->size < scalar_decomp.size()){
        throw std::logic_error("The target size of the DigitInteger is smaller than the number of digits of the scalar!");
    }
    /// Padd with zeros.
    for(int32_t i = scalar_decomp.size(); i < size; i++){
        scalar_decomp.push_back(0);
    }
    DigitInteger out = subtraction_with_carry(scalar_decomp); 
    out.resisze(size);
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
    if(this->size < scalar_decomp.size()){
        throw std::logic_error("The target size of the DigitInteger is smaller than the number of digits of the scalar!");
    }
    /// Padd with zeros.
    for(int32_t i = scalar_decomp.size(); i < size; i++){
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

void DigitInteger::resisze(int32_t size){
    if(this->size == size) return;
    if (size < 0) throw std::logic_error("Size cannot be negative!"); 
    if(size < this->size){
        encrypted_digits.resize(size);
    }else if(context->config->is_secret_key_set){
        for(int32_t i = this->size; i < size; i++){
            encrypted_digits.push_back(context->encrypt(0, digit_plaintext_encoding));
        }
    }else{
        for(int32_t i = this->size; i < size; i++){
            encrypted_digits.push_back(context->encrypt_public(0, digit_plaintext_encoding));
        }
    }
    for(int32_t i = this->size; i < size; i++){
        encrypted_digits.push_back(context->encrypt(0, digit_plaintext_encoding));
    }
    this->size = size;
}

bool DigitInteger::is_compatible(const DigitInteger& other)const{
    if(this->size != other.size){
        return false;
    }
    if(this->base != other.base){
        return false;
    }
    return true;
}

CRTInteger::CRTInteger(int64_t message, const RNSBase& base){
    this->base = base;
    /// TODO: Values computed in init are computed every tiime I create a CRTInteger.
    /// Would be better to make a small class that computes these values and stores them.
    /// For instance we can name the class: RNSBase. Then we initialize a RNSInteger with the RNSBase. 
    std::vector<int32_t> digits_message = base.decompose(message);
    this->encrypted_digits.reserve(digits_message.size());
    /// TODO: CRT base may have partial domain encoding!!!
    if(this->base.context->config->is_secret_key_set){
        for(int32_t i = 0; i < digits_message.size(); ++i){
            PlaintextEncoding encoding = this->base.context->get_default_plaintext_encoding();
            encoding.set_plaintext_space(base.crt_base[i]);
            encoding.set_type(PlaintextEncodingType::full_domain);
            encrypted_digits.push_back(this->base.context->encrypt(digits_message[i], encoding));
        }
    }else if(this->base.context->config->is_secret_key_set){
        for(int32_t i = 0; i < digits_message.size(); ++i){
            PlaintextEncoding encoding = this->base.context->get_default_plaintext_encoding();
            encoding.set_plaintext_space(base.crt_base[i]);
            encoding.set_type(PlaintextEncodingType::full_domain);
            encrypted_digits.push_back(this->base.context->encrypt_public(digits_message[i], encoding));
        }
    }else{
        throw std::logic_error("No keys initialized!");
    }
}

CRTInteger::CRTInteger(std::vector<Ciphertext> cts, const RNSBase& base){
    this->encrypted_digits = cts; 
    this->base = base; 
    /// TODO: Perhaps check if the ciphertexts are correct with regard to the base.
}


CRTInteger CRTInteger::operator+(const CRTInteger& other){
    if(this->base.modulus  != other.base.modulus){
        throw std::logic_error("Modulus of the CRTIntegers do not match!");
    } 
    std::vector<Ciphertext> out;
    out.reserve(this->base.crt_base.size());
    for(int32_t i = 0; i < base.crt_base.size(); ++i){
        out.push_back(this->encrypted_digits[i] + other.encrypted_digits[i]);
    }
    return CRTInteger(out, base);
}

CRTInteger CRTInteger::operator+(const int64_t scalar){
    std::vector<int32_t> scalar_decomp =  base.decompose(scalar); 
    std::vector<Ciphertext> out;
    out.reserve(base.crt_base.size());
    for(int32_t i = 0; i < base.crt_base.size(); ++i){
        out.push_back(this->encrypted_digits[i] + scalar_decomp[i]);
    }
    return CRTInteger(out, base);
}

CRTInteger CRTInteger::operator-(const CRTInteger& other){
    if(this->base.modulus != other.base.modulus){
        throw std::logic_error("Modulus of the CRTIntegers do not match!");
    } 
    std::vector<Ciphertext> out;
    out.reserve(base.crt_base.size());
    for(int32_t i = 0; i < base.crt_base.size(); ++i){
        out.push_back(this->encrypted_digits[i] - other.encrypted_digits[i]);
    }
    return CRTInteger(out, base);
}

CRTInteger CRTInteger::operator-(const int64_t scalar){
    std::vector<int32_t> scalar_decomp =  base.decompose(scalar); 
    std::vector<Ciphertext> out;
    out.reserve(base.crt_base.size());
    for(int32_t i = 0; i < base.crt_base.size(); ++i){
        out.push_back(this->encrypted_digits[i] - scalar_decomp[i]);
    }
    return CRTInteger(out, base);
}

CRTInteger CRTInteger::operator*(const int64_t scalar){
    std::vector<int32_t> scalar_decomp =  base.decompose(scalar); 
    std::vector<Ciphertext> out;
    out.reserve(base.crt_base.size());
    for(int32_t i = 0; i < base.crt_base.size(); ++i){
        out.push_back(this->encrypted_digits[i] * scalar_decomp[i]);
    }
    return CRTInteger(out, base);
}

CRTInteger CRTInteger::operator*(const CRTInteger& other){ 
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
     
    /// TODO: Perhaps this should also be in base already? 
    for(int32_t i = 0; i < base.crt_base.size(); ++i){
        std::function<int64_t(int64_t)> function = std::bind(times_in_two_and_square, std::placeholders::_1, base.crt_base[i]);
        PlaintextEncoding encoding = this->base.context->get_default_plaintext_encoding();
        encoding.set_plaintext_space(base.crt_base[i]);
        encoding.set_type(PlaintextEncodingType::full_domain);  
        func_specs.push_back(this->base.context->setup_function(function, encoding));  
    }   
    out.reserve(base.crt_base.size());
    for(int32_t i = 0; i < base.crt_base.size(); ++i){
        /// TODO: This was for some testing. Remove before committing. 
        /*
        Ciphertext plus = this->encrypted_digits[i] + other.encrypted_digits[i];
        Ciphertext minus = this->encrypted_digits[i] - other.encrypted_digits[i]; 
        Ciphertext plus_square_inv = context->eval(plus, func_specs[i]);
        Ciphertext minus_square_inv = context->eval(minus, func_specs[i]);
        out.push_back(plus_square_inv - minus_square_inv);
        */ 
        out.push_back(this->base.context->eval(this->encrypted_digits[i] + other.encrypted_digits[i], func_specs[i]) - 
                      this->base.context->eval(this->encrypted_digits[i] - other.encrypted_digits[i], func_specs[i]));
    }
    CRTInteger out_integer(out, base);
    return out_integer;
}
  
void RNSBase::init(){
    modulus = 1;
    for(int32_t i = 0; i < crt_base.size(); i++){
        modulus *= crt_base[i];
    }
    factors.resize(crt_base.size());
    m_list.resize(crt_base.size());
    cofactors.resize(crt_base.size());
    for(int32_t i = 0; i < crt_base.size(); i++){
        factors[i] = modulus / crt_base[i];
        std::pair<int64_t, std::pair<int64_t, int64_t>> crt_base_tuple = Utils::extended_euclidean_algorithm(factors[i], crt_base[i]);
        m_list[i] = crt_base_tuple.second.first;
        cofactors[i] = factors[i] * m_list[i];
    }
}

RNSBase::RNSBase(FHEContext* context, std::vector<int32_t> crt_base){
    this->context = context;
    this->crt_base = crt_base;
    init();
}

std::vector<int32_t> RNSBase::decompose(int64_t x)const{
    std::vector<int32_t> out;
    out.resize(crt_base.size());
    for(int32_t i = 0; i < crt_base.size(); i++){
        out[i] = (int32_t)(x % crt_base[i]);
    }
    return out;
}

int64_t RNSBase::compose(const std::vector<int32_t>& digits)const{
    int64_t composed = 0;
    for(int32_t i = 0; i < crt_base.size(); i++){
        composed += Utils::integer_mod_form(digits[i] * cofactors[i], modulus);
    }
    return Utils::integer_mod_form(composed, modulus);
}

 