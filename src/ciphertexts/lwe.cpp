#include "ciphertexts/lwe.h"

using namespace FHEDeck;
  
LWEParam::LWEParam(int32_t dim, int64_t modulus){
    m_dim = dim;
    m_modulus = modulus;
}

int32_t LWEParam::dim()const{
    return m_dim;
}

int64_t LWEParam::modulus()const{
    return m_modulus;
}
  
LWECT::LWECT(std::shared_ptr<LWEParam> lwe_param){
    m_param = lwe_param; 
    m_ct = Vector(m_param->dim()+1, m_param->modulus());
}
   
LWECT::LWECT(const LWECT &c){  
    m_param = c.m_param; 
    m_ct = Vector(m_param->dim()+1, m_param->modulus());
    for(int32_t i = 0; i < m_param->dim()+1; ++i){
        m_ct[i] = c.m_ct[i];
    }
} 

void LWECT::mul(LWECT &out, int64_t scalar)const{
    for(int32_t i = 0; i <= m_param->dim(); ++i){
        out.m_ct[i] = (m_ct[i] * scalar) % m_param->modulus();
    }
}

void LWECT::mul_lazy(LWECT& out, int64_t scalar)const{
    for(int32_t i = 0; i <= m_param->dim(); ++i){
        out.m_ct[i] = (m_ct[i] * scalar);
    }
}
 
void LWECT::add(LWECT& out, const LWECT& in)const{
    for(int32_t i = 0; i <= m_param->dim(); ++i){
        out.m_ct[i] = (m_ct[i] + in.m_ct[i]) % m_param->modulus();
    }
}
 
void LWECT::sub(LWECT& out, const LWECT& in)const{
    for(int32_t i = 0; i <= m_param->dim(); ++i){
        out.m_ct[i] = Utils::integer_mod_form(m_ct[i] - in.m_ct[i], m_param->modulus());
    }
}
  
void LWECT::add_lazy(LWECT& out, const LWECT& in)const{
    for(int32_t i = 0; i <= m_param->dim(); ++i){
        out.m_ct[i] = m_ct[i] + in.m_ct[i];
    }
}
  
void LWECT::add(LWECT& out, int64_t b)const{ 
    out.m_ct[0] = (m_ct[0] + b) % m_param->modulus();
    for(int32_t i = 1; i <= m_param->dim(); ++i){
        out.m_ct[i] = m_ct[i];
    } 
}
  
void LWECT::sub(LWECT& out, int64_t b)const{
    out.m_ct[0] = Utils::integer_mod_form(m_ct[0] - b, m_param->modulus());
    for(int32_t i = 1; i <= m_param->dim(); ++i){
        out.m_ct[i] = m_ct[i];
    } 
}

void LWECT::neg(LWECT& out)const{   
    for(int32_t i = 0; i < m_param->dim()+1; ++i){
        out.m_ct[i] = Utils::integer_mod_form(-m_ct[i], m_param->modulus());
    }  
}
 
LWECT& LWECT::operator=(const LWECT other){  
    if (this == &other)
    {
        return *this;
    }   
    m_param = other.m_param; 
    m_ct = Vector(m_param->dim()+1, m_param->modulus());
    for(int32_t i = 0; i < m_param->dim()+1; ++i){
        m_ct[i] = other.m_ct[i];
    } 
    return *this;
} 

int64_t& LWECT::operator[](int32_t index){
    return m_ct[index];
}

int64_t LWECT::operator[](int32_t index)const{
    return m_ct[index];
}

std::shared_ptr<LWEParam> LWECT::param()const{
    return m_param;
}

std::unique_ptr<LWECT> LWECT::clone()const{
    std::unique_ptr<LWECT> out = std::make_unique<LWECT>(m_param);
    for(int32_t i = 0; i < m_param->dim()+1; ++i){
        out->m_ct[i] = m_ct[i];
    } 
    return out;
} 

Vector& LWECT::ct_vec(){
    return m_ct;
}

const Vector& LWECT::ct_vec()const{
    return m_ct;
}

LWEModSwitcher::LWEModSwitcher(std::shared_ptr<LWEParam> from, std::shared_ptr<LWEParam> to){
    m_from = from;
    m_to = to; 
    /// Check if we need int64_t arithmetic.
    int32_t bits_from = Utils::number_of_bits(from->modulus());
    int32_t bits_to = Utils::number_of_bits(to->modulus()); 
    if(from->dim() != to->dim()){
        throw std::logic_error("LWEModSwitcher::LWEModSwitcher: Dimension of the from and to LWE parametrs must the the same.");
    }
    ct_size = from->dim()+1;
    if(bits_from+bits_to <= 52){
        m_is_long_arithmetic = false;
        Q_from = from->modulus();
        Q_to = to->modulus(); 
    }else if(bits_from+bits_to <= 112){
        m_is_long_arithmetic = true;
        long_Q_from = (long double)from->modulus();
        long_Q_to = (long double)to->modulus(); 
    }else{
        throw std::logic_error("LWEModSwitcher::LWEModSwitcher: Too large moduli.");
    }
}
  
void LWEModSwitcher::switch_modulus(LWECT& out_ct, const LWECT& in_ct){  
    if(m_is_long_arithmetic){ 
        long double long_temp; 
        for(int32_t i = 0; i < ct_size; ++i){
            long_temp = long_Q_to * (long double)in_ct[i];
            out_ct[i] = (int64_t)roundl(long_temp/long_Q_from); 
        } 
    }else{  
        double temp; 
        for(int32_t i = 0; i < ct_size; ++i){
            // Compute multiplicaiton on integers, and then convert to double
            temp = m_to->modulus() * in_ct[i];
            // Divide and round to closest integer
            out_ct[i] = (int64_t)round(temp/Q_from); 
        } 
    }   
}

LWECT LWEModSwitcher::switch_modulus(const LWECT& in_ct){
    LWECT out(m_to);
    switch_modulus(out, in_ct);
    return out;
}

std::shared_ptr<LWEParam> LWEModSwitcher::from_param()const{
    return m_from;
}

std::shared_ptr<LWEParam> LWEModSwitcher::to_param()const{
    return m_to;
}
   
LWEGadgetCT::LWEGadgetCT(std::shared_ptr<LWEParam> lwe_param, int64_t base){
    m_lwe_param = lwe_param;
    m_base = base;  
    /// TODO:  Add check: Note that for now, we accept only power of two basis (because our decomposition is written this way)
    m_bits_base = Utils::power_times(base, 2);  
    m_digits = Utils::power_times(lwe_param->modulus(), base);   
    m_ct_content = std::unique_ptr<std::unique_ptr<LWECT>[]>(new std::unique_ptr<LWECT>[m_digits]);  
}

void LWEGadgetCT::gadget_mul(LWECT& out_ct, int64_t scalar){  
    std::vector<int64_t> scalar_decomposed = Utils::integer_decomp(scalar, m_base, m_bits_base, m_digits);
    LWECT temp_ct(m_lwe_param); 
    m_ct_content[0]->mul(out_ct, scalar_decomposed[0]);
    for(int32_t i = 1; i < m_digits; ++i){
        m_ct_content[i]->mul(temp_ct, scalar_decomposed[i]);
        out_ct.add(out_ct, temp_ct);  
    } 
} 
    
void LWEGadgetCT::gadget_mul_lazy(LWECT& out_ct, int64_t scalar){  
    std::vector<int64_t> scalar_decomposed = Utils::integer_decomp(scalar, m_base, m_bits_base, m_digits);
    LWECT temp_ct(m_lwe_param); 
    m_ct_content[0]->mul_lazy(out_ct, scalar_decomposed[0]);
    for(int32_t i = 1; i < m_digits; ++i){
        m_ct_content[i]->mul_lazy(temp_ct, scalar_decomposed[i]);
        out_ct.add_lazy(out_ct, temp_ct);  
    } 
} 

int64_t LWEGadgetCT::base()const{
    return m_base;
}
    
int32_t LWEGadgetCT::digits()const{
    return m_digits;
}
  
LWESK::LWESK(std::shared_ptr<LWEParam> lwe_par, double stddev, KeyDistribution key_type){
    m_param = lwe_par;  
    m_stddev  = stddev;
    m_key_type = key_type; 
    init();
    init_key(); 
}

LWESK::LWESK(std::shared_ptr<LWEParam> lwe_par, int64_t* key, double stddev, KeyDistribution key_type){
    m_param = lwe_par;  
    m_stddev  = stddev;
    m_key_type = key_type;  
    init(); 
    for(int32_t i = 0; i < lwe_par->dim(); ++i){
        m_key[i] = key[i];
    }    
}

void LWESK::init(){ 
    m_key = Vector(m_param->dim(), m_param->modulus());
    m_unif_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, m_param->modulus()));
    m_error_dist = std::shared_ptr<Distribution>(new StandardRoundedGaussianDistribution(0, m_stddev));  
    m_multiplier = std::unique_ptr<LongIntegerMultipler>(new LongIntegerMultipler(m_param->modulus())); 
}

void LWESK::init_key(){
    std::shared_ptr<Distribution> sk_dist;
    if(m_key_type == KeyDistribution::binary){  
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, 1));
    }else{ 
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(-1, 1));
    } 
    sk_dist->fill(m_key);  
}
 
std::unique_ptr<LWECT> LWESK::encrypt(int64_t m){
    std::unique_ptr<LWECT> out = std::make_unique<LWECT>(m_param);
    encrypt(*out, m);
    return out;
}
 
void LWESK::encrypt(LWECT& out, int64_t m){     
    out[0] = Utils::integer_mod_form(m_error_dist->next() + m, m_param->modulus()); 
    for(int32_t i=1; i < m_param->dim()+1; ++i){       
        out[i] = m_unif_dist->next(); 
        int64_t k = m_key[i-1]; 
        out[0] -= m_multiplier->mul(k,  out[i]); 
        out[0] = Utils::integer_mod_form(out[0], m_param->modulus()); 
    }   
}
  
std::unique_ptr<LWECT> LWESK::encode_and_encrypt(int64_t m, PlaintextEncoding encoding){  
    std::unique_ptr<LWECT> out = std::make_unique<LWECT>(m_param);
    encrypt(*out, encoding.encode_message(m)); 
    return out;
}
 
void LWESK::encode_and_encrypt(LWECT& in, int64_t m, PlaintextEncoding encoding){   
    encrypt(in, encoding.encode_message(m)); 
} 
 
int64_t LWESK::partial_decrypt(const LWECT& in){  
    int64_t phase  = in[0]; 
    for(int32_t i = 1; i < m_param->dim()+1; ++i){ 
        int64_t k = Utils::integer_mod_form(m_key[i-1], m_param->modulus());  
        int64_t c = Utils::integer_mod_form(in[i], m_param->modulus());  
        phase = (phase + m_multiplier->mul(c, k)) % m_param->modulus(); 
    }   
    return phase; 
}
 
int64_t LWESK::decrypt(LWECT& in, PlaintextEncoding encoding){
    return encoding.decode_message(partial_decrypt(in));
}

std::shared_ptr<LWEParam> LWESK::param()const{
    return m_param;
}

KeyDistribution LWESK::key_type()const{
    return m_key_type;
} 

double LWESK::stddev()const{
    return m_stddev;
}
 
LWEGadgetSK::LWEGadgetSK(std::shared_ptr<LWESK> lwe_sk, int64_t base){ 
    m_lwe_sk = lwe_sk;  
    m_base = base;  
    /// TODO: Add Check: Note that for now, we accept only power of two basis (because our decomposition is written this way)
    m_bits_base = Utils::power_times(base, 2);  
    m_digits = Utils::power_times(m_lwe_sk->param()->modulus(), base);   
    m_multiplier = std::make_unique<LongIntegerMultipler>(m_lwe_sk->param()->modulus());
}
 
std::shared_ptr<LWEGadgetCT> LWEGadgetSK::gadget_encrypt(int64_t m){ 
    std::shared_ptr<LWEGadgetCT> out = std::make_shared<LWEGadgetCT>(m_lwe_sk->param(), m_base); 
    gadget_encrypt(*out, m);
    return out;
}

void LWEGadgetSK::gadget_encrypt(LWEGadgetCT& gadget_ct, int64_t m){
    int64_t temp_base = 1;     
    int64_t message = m;  
    gadget_ct.m_ct_content[0] = m_lwe_sk->encrypt(message); 
    for(int32_t i = 1; i < m_digits; ++i){
        temp_base *= m_base;      
        gadget_ct.m_ct_content[i] = m_lwe_sk->encrypt(m_multiplier->mul(temp_base, message)); 
    } 
} 

std::shared_ptr<LWEParam> LWEGadgetSK::param()const{
    return m_lwe_sk->param();
}

int64_t LWEGadgetSK::base()const{
    return m_base;
}
    
int32_t LWEGadgetSK::digits()const{
    return m_digits;
}

LWEPublicKey::LWEPublicKey(std::shared_ptr<LWESK> lwe_sk, int32_t size, double stddev){
    m_size = size;
    m_stddev = stddev;
    m_param = lwe_sk->param(); 
    m_rand_masking = std::shared_ptr<Distribution>(new StandardRoundedGaussianDistribution(0, stddev));
    // Initialize the key switching key 
    m_public_key_ptr = std::unique_ptr<std::unique_ptr<LWECT>[]>(new std::unique_ptr<LWECT>[size]); 
    for(int32_t i = 0; i < m_size; ++i){   
        m_public_key_ptr[i] = std::unique_ptr<LWECT>(lwe_sk->encrypt(0));
    }   
}

LWEPublicKey::LWEPublicKey(const LWEPublicKey &other){
    throw std::runtime_error("LWEPublicKey::LWEPublicKey(const LWEPublicKey &other)"); 
}
   
LWEPublicKey& LWEPublicKey::operator=(const LWEPublicKey other){
    throw std::runtime_error("LWEPublicKey::LWEPublicKey(const LWEPublicKey &other)"); 
    return *this;
}
 
void LWEPublicKey::encrypt(LWECT& out, int64_t message){
    int64_t noise = m_rand_masking->next();
    m_public_key_ptr[0]->mul(out, noise); 
    LWECT temp(m_param);
    for(int32_t i = 1; i < m_size; ++i){
        noise = m_rand_masking->next();
        m_public_key_ptr[i]->mul(temp, noise); 
        out.add(out, temp); 
    }  
    out.add(out, message); 
}
  
std::unique_ptr<LWECT> LWEPublicKey::encrypt(int64_t message){
    std::unique_ptr<LWECT> out = std::make_unique<LWECT>(m_param);  
    encrypt(*out, message);
    return out;    
}
 
std::unique_ptr<LWECT> LWEPublicKey::ciphertext_of_zero(){
    return LWEPublicKey::encrypt(0);
}

std::shared_ptr<LWEParam> LWEPublicKey::param()const{
    return m_param;
}