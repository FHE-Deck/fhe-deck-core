#include "ciphertexts/lwe.h"

using namespace FHEDeck;
  
LWEParam::LWEParam(int32_t dim, int64_t modulus){
    this->dim = dim;
    this->modulus = modulus;
}
  
LWECT::LWECT(std::shared_ptr<LWEParam> lwe_param){
    this->param = lwe_param;
    this->ct = new int64_t[param->dim+1];
}
   
LWECT::LWECT(const LWECT &c){  
    this->param = c.param;
    this->ct = new int64_t[param->dim+1]; 
    for(int32_t i = 0; i < param->dim+1; ++i){
        this->ct[i] = c.ct[i];
    }
}
 
LWECT::~LWECT(){    
    delete[] ct; 
}
 
void LWECT::mul(LWECT &out, int64_t scalar)const{
    for(int32_t i = 0; i <= param->dim; ++i){
        out.ct[i] = (ct[i] * scalar) % param->modulus;
    }
}

void LWECT::mul_lazy(LWECT& out, int64_t scalar)const{
    for(int32_t i = 0; i <= param->dim; ++i){
        out.ct[i] = (ct[i] * scalar);
    }
}
 
void LWECT::add(LWECT& out, const LWECT& in)const{
    for(int32_t i = 0; i <= this->param->dim; ++i){
        out.ct[i] = (this->ct[i] + in.ct[i]) % this->param->modulus;
    }
}
 
void LWECT::sub(LWECT& out, const LWECT& in)const{
    for(int32_t i = 0; i <= this->param->dim; ++i){
        out.ct[i] = Utils::integer_mod_form(this->ct[i] - in.ct[i], this->param->modulus);
    }
}
  
void LWECT::add_lazy(LWECT& out, const LWECT& in)const{
    for(int32_t i = 0; i <= this->param->dim; ++i){
        out.ct[i] = this->ct[i] + in.ct[i];
    }
}
  
void LWECT::add(LWECT& out, int64_t b)const{ 
    out.ct[0] = (this->ct[0] + b) % this->param->modulus;
    for(int32_t i = 1; i <= param->dim; ++i){
        out.ct[i] = this->ct[i];
    } 
}
  
void LWECT::sub(LWECT& out, int64_t b)const{
    out.ct[0] = Utils::integer_mod_form(this->ct[0] - b, this->param->modulus);
    for(int32_t i = 1; i <= param->dim; ++i){
        out.ct[i] = this->ct[i];
    } 
}

void LWECT::neg(LWECT& out)const{   
    for(int32_t i = 0; i < param->dim+1; ++i){
        out.ct[i] = Utils::integer_mod_form(-this->ct[i], param->modulus);
    }  
}
 
LWECT& LWECT::operator=(const LWECT other){  
    if (this == &other)
    {
        return *this;
    }   
    this->param = other.param;
    this->ct = new int64_t[param->dim+1]; 
    for(int32_t i = 0; i < param->dim+1; ++i){
        this->ct[i] = other.ct[i];
    } 
    return *this;
} 

std::unique_ptr<LWECT> LWECT::clone()const{
    std::unique_ptr<LWECT> out = std::make_unique<LWECT>(param);
    for(int32_t i = 0; i < param->dim+1; ++i){
        out->ct[i] = this->ct[i];
    } 
    return out;
} 

LWEModSwitcher::LWEModSwitcher(std::shared_ptr<LWEParam> from, std::shared_ptr<LWEParam> to){
    this->from = from;
    this->to = to; 
    /// Check if we need int64_t arithmetic.
    int32_t bits_from = Utils::number_of_bits(from->modulus);
    int32_t bits_to = Utils::number_of_bits(to->modulus); 
    if(from->dim != to->dim){
        throw std::logic_error("LWEModSwitcher::LWEModSwitcher: Dimension of the from and to LWE parametrs must the the same.");
    }
    ct_size = from->dim+1;
    if(bits_from+bits_to <= 52){
        long_arithmetic = false;
        Q_from = from->modulus;
        Q_to = to->modulus; 
    }else if(bits_from+bits_to <= 112){
        long_arithmetic = true;
        long_Q_from = (long double)from->modulus;
        long_Q_to = (long double)to->modulus; 
    }else{
        throw std::logic_error("LWEModSwitcher::LWEModSwitcher: Too large moduli.");
    }
}
  
void LWEModSwitcher::switch_modulus(LWECT& out_ct, const LWECT& in_ct){  
    if(long_arithmetic){ 
        long double long_temp; 
        for(int32_t i = 0; i < ct_size; ++i){
            long_temp = long_Q_to * (long double)in_ct.ct[i];
            out_ct.ct[i] = (int64_t)roundl(long_temp/long_Q_from); 
        } 
    }else{  
        double temp; 
        for(int32_t i = 0; i < ct_size; ++i){
            // Compute multiplicaiton on integers, and then convert to double
            temp = to->modulus * in_ct.ct[i];
            // Divide and round to closest integer
            out_ct.ct[i] = (int64_t)round(temp/Q_from); 
        } 
    }   
}
   
LWEGadgetCT::LWEGadgetCT(std::shared_ptr<LWEParam> lwe_param, int64_t base){
    this->lwe_param = lwe_param;
    this->base = base;  
    /// TODO:  Add check: Note that for now, we accept only power of two basis (because our decomposition is written this way)
    this->bits_base = Utils::power_times(base, 2);  
    this->digits = Utils::power_times(lwe_param->modulus, base);   
    this->ct_content = std::unique_ptr<std::unique_ptr<LWECT>[]>(new std::unique_ptr<LWECT>[digits]);  
}

void LWEGadgetCT::gadget_mul(LWECT& out_ct, int64_t scalar){ 
    int64_t *scalar_decomposed = new int64_t[digits]; 
    Utils::integer_decomp(scalar_decomposed, scalar, base, bits_base, digits);
    LWECT temp_ct(lwe_param); 
    ct_content[0]->mul(out_ct, scalar_decomposed[0]);
    for(int32_t i = 1; i < digits; ++i){
        ct_content[i]->mul(temp_ct, scalar_decomposed[i]);
        out_ct.add(out_ct, temp_ct);  
    }
    delete[] scalar_decomposed;  
} 
    
void LWEGadgetCT::gadget_mul_lazy(LWECT& out_ct, int64_t scalar){ 
    int64_t *scalar_decomposed = new int64_t[digits]; 
    Utils::integer_decomp(scalar_decomposed, scalar, base, bits_base, digits);
    LWECT temp_ct(lwe_param); 
    ct_content[0]->mul_lazy(out_ct, scalar_decomposed[0]);
    for(int32_t i = 1; i < digits; ++i){
        ct_content[i]->mul_lazy(temp_ct, scalar_decomposed[i]);
        out_ct.add_lazy(out_ct, temp_ct);  
    }
    delete[] scalar_decomposed;  
}
  
LWESK::~LWESK(){ 
    delete[] key; 
}
  
LWESK::LWESK(std::shared_ptr<LWEParam> lwe_par, double stddev, KeyDistribution key_type){
    this->param = lwe_par;  
    this->stddev  = stddev;
    this->key_type = key_type; 
    init();
    init_key(); 
}

LWESK::LWESK(std::shared_ptr<LWEParam> lwe_par, int64_t* key, double stddev, KeyDistribution key_type){
    this->param = lwe_par;  
    this->stddev  = stddev;
    this->key_type = key_type;  
    init(); 
    for(int32_t i = 0; i < lwe_par->dim; ++i){
        this->key[i] = key[i];
    }    
}

void LWESK::init(){
    this->key = new int64_t[param->dim];  
    unif_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, param->modulus));
    error_dist = std::shared_ptr<Distribution>(new StandardRoundedGaussianDistribution(0, stddev));  
    multiplier = std::unique_ptr<LongIntegerMultipler>(new LongIntegerMultipler(param->modulus)); 
}

void LWESK::init_key(){
    std::shared_ptr<Distribution> sk_dist;
    if(this->key_type == KeyDistribution::binary){  
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, 1));
    }else{ 
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(-1, 1));
    }
    sk_dist->fill_array(key, param->dim); 
    Utils::array_mod_form(this->key, this->key, param->dim, param->modulus); 
}
 
std::unique_ptr<LWECT> LWESK::encrypt(int64_t m){
    std::unique_ptr<LWECT> out = std::make_unique<LWECT>(param);
    encrypt(*out, m);
    return out;
}
 
void LWESK::encrypt(LWECT& out, int64_t m){     
    out.ct[0] = Utils::integer_mod_form(error_dist->next() + m, param->modulus); 
    for(int32_t i=1; i < param->dim+1; ++i){       
        out.ct[i] = unif_dist->next(); 
        int64_t k = key[i-1]; 
        out.ct[0] -= multiplier->mul(k,  out.ct[i]); 
        out.ct[0] = Utils::integer_mod_form(out.ct[0], param->modulus); 
    }   
}
  
std::unique_ptr<LWECT> LWESK::encode_and_encrypt(int64_t m, PlaintextEncoding encoding){  
    std::unique_ptr<LWECT> out = std::make_unique<LWECT>(this->param);
    encrypt(*out, encoding.encode_message(m)); 
    return out;
}
 
void LWESK::encode_and_encrypt(LWECT& in, int64_t m, PlaintextEncoding encoding){   
    encrypt(in, encoding.encode_message(m)); 
} 
 
int64_t LWESK::partial_decrypt(const LWECT& in){ 
    Utils::array_mod_form(key, key, param->dim, param->modulus); 
    int64_t phase  = in.ct[0]; 
    for(int32_t i = 1; i < param->dim+1; ++i){ 
        int64_t k = Utils::integer_mod_form(key[i-1], param->modulus);  
        int64_t c = Utils::integer_mod_form(in.ct[i], param->modulus);  
        phase = (phase + multiplier->mul(c, k)) % param->modulus; 
    }   
    return phase; 
}
 
int64_t LWESK::decrypt(LWECT& in, PlaintextEncoding encoding){
    return encoding.decode_message(partial_decrypt(in));
} 
 
LWEGadgetSK::LWEGadgetSK(std::shared_ptr<LWESK> lwe, int64_t base){ 
    this->lwe = lwe;  
    this->base = base;  
    /// TODO: Add Check: Note that for now, we accept only power of two basis (because our decomposition is written this way)
    this->bits_base = Utils::power_times(base, 2);  
    this->digits = Utils::power_times(lwe->param->modulus, base);   
}

LWEGadgetSK::LWEGadgetSK(const LWEGadgetSK &other){
    throw std::runtime_error("LWEGadgetSK::LWEGadgetSK(const LWEGadgetSK &other)"); 
}

LWEGadgetSK& LWEGadgetSK::operator=(const LWEGadgetSK other){
    throw std::runtime_error("LWEGadgetSK::operator=(const LWEGadgetSK other)"); 
    return *this;
}
 
std::shared_ptr<LWEGadgetCT> LWEGadgetSK::gadget_encrypt(int64_t m){ 
    std::shared_ptr<LWEGadgetCT> out = std::make_shared<LWEGadgetCT>(lwe->param, this->base); 
    gadget_encrypt(*out, m);
    return out;
}

void LWEGadgetSK::gadget_encrypt(LWEGadgetCT& gadget_ct, int64_t m){
    int64_t temp_base = 1;     
    int64_t message = m;  
    gadget_ct.ct_content[0] = std::unique_ptr<LWECT>(lwe->encrypt(message)); 
    for(int32_t i = 1; i < this->digits; ++i){
        temp_base *= this->base;      
        gadget_ct.ct_content[i] = std::unique_ptr<LWECT>(lwe->encrypt(lwe->multiplier->mul(temp_base, message))); 
    } 
} 

LWEPublicKey::LWEPublicKey(std::shared_ptr<LWESK> lwe_sk, int32_t size, double stddev){
    this->size = size;
    this->stddev = stddev;
    this->param = lwe_sk->param; 
    this->rand_masking = std::shared_ptr<Distribution>(new StandardRoundedGaussianDistribution(0, stddev));
    // Initialize the key switching key 
    this->public_key_ptr = std::unique_ptr<std::unique_ptr<LWECT>[]>(new std::unique_ptr<LWECT>[size]); 
    for(int32_t i = 0; i < this->size; ++i){   
        public_key_ptr[i] = std::unique_ptr<LWECT>(lwe_sk->encrypt(0));
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
    int64_t noise = rand_masking->next();
    public_key_ptr[0]->mul(out, noise); 
    LWECT temp(param);
    for(int32_t i = 1; i < size; ++i){
        noise = rand_masking->next();
        public_key_ptr[i]->mul(temp, noise); 
        out.add(out, temp); 
    }  
    out.add(out, message); 
}
  
std::unique_ptr<LWECT> LWEPublicKey::encrypt(int64_t message){
    std::unique_ptr<LWECT> out = std::make_unique<LWECT>(param);  
    encrypt(*out, message);
    return out;    
}
 
std::unique_ptr<LWECT> LWEPublicKey::ciphertext_of_zero(){
    return LWEPublicKey::encrypt(0);
}