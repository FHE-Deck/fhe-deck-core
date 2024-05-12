#include "lwe.h"

using namespace fhe_deck;
  
LWEParam::LWEParam(int dim, long modulus){
    this->dim = dim;
    this->modulus = modulus;
}
  
LWECT::LWECT(std::shared_ptr<LWEParam> lwe_param){
    this->param = lwe_param;
    this->ct = new long[param->dim+1];
    this->init = true; 
}
   
LWECT::LWECT(const LWECT &c){  
    this->param = c.param;
    this->ct = new long[param->dim+1]; 
    for(int i = 0; i < param->dim+1; ++i){
        this->ct[i] = c.ct[i];
    }
    this->init = true;
}
 
LWECT::~LWECT(){     
    if(init){  
        delete[] ct; 
    } 
}
 
void LWECT::mul(LWECT *out, long scalar){
    for(int i = 0; i <= param->dim; ++i){
        out->ct[i] = (ct[i] * scalar) % param->modulus;
    }
}

void LWECT::mul_lazy(LWECT *out, long scalar){
    for(int i = 0; i <= param->dim; ++i){
        out->ct[i] = (ct[i] * scalar);
    }
}
 
void LWECT::add(LWECT *out, LWECT *in){
    for(int i = 0; i <= this->param->dim; ++i){
        out->ct[i] = (this->ct[i] + in->ct[i]) % this->param->modulus;
    }
}
 
void LWECT::sub(LWECT* out, LWECT *in){
    for(int i = 0; i <= this->param->dim; ++i){
        out->ct[i] = Utils::integer_mod_form(this->ct[i] - in->ct[i], this->param->modulus);
    }
}
  
void LWECT::add_lazy(LWECT* out, LWECT *in){
    for(int i = 0; i <= this->param->dim; ++i){
        out->ct[i] = this->ct[i] + in->ct[i];
    }
}
  
void LWECT::add(LWECT* out, long b){ 
    out->ct[0] = (this->ct[0] + b) % this->param->modulus;
    for(int i = 1; i < param->dim+1; ++i){
        out->ct[i] = this->ct[i];
    } 
}
  
void LWECT::sub(LWECT* out, long b){
    out->ct[0] = Utils::integer_mod_form(this->ct[0] - b, this->param->modulus);
    for(int i = 1; i < param->dim+1; ++i){
        out->ct[i] = this->ct[i];
    } 
}

void LWECT::neg(LWECT* out){   
    for(int i = 0; i < param->dim+1; ++i){
        out->ct[i] = Utils::integer_mod_form(-this->ct[i], param->modulus);
    }  
}
 
LWECT& LWECT::operator=(const LWECT other){  
    if (this == &other)
    {
        return *this;
    }   
    if(init==false){
        this->param = other.param;
        this->ct = new long[param->dim+1]; 
        for(int i = 0; i < param->dim+1; ++i){
            this->ct[i] = other.ct[i];
        }
        this->init = true;
    }
    else if(init && (param->dim == other.param->dim)){ 
        param = other.param;
        for(int i = 0; i < param->dim+1; ++i){
            ct[i] = other.ct[i];
        }
    }else{
        throw std::logic_error("Wrong case in lwe_ct::operator=");
    } 
    return *this;
} 

LWECT* LWECT::clone(){
    LWECT* out = new LWECT(param);
    for(int i = 0; i < param->dim+1; ++i){
        out->ct[i] = this->ct[i];
    }
    out->init = true;
    return out;
} 

LWEModSwitcher::LWEModSwitcher(std::shared_ptr<LWEParam> from, std::shared_ptr<LWEParam> to){
    this->from = from;
    this->to = to; 
    /// Check if we need long arithmetic.
    int bits_from = Utils::number_of_bits(from->modulus);
    int bits_to = Utils::number_of_bits(to->modulus); 
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
  
void LWEModSwitcher::switch_modulus(LWECT *out_ct, LWECT *in_ct){  
    if(long_arithmetic){
        for(int i = 0; i < ct_size; ++i){
            long_temp = long_Q_to * (long double)in_ct->ct[i];
            out_ct->ct[i] = (long)roundl(long_temp/long_Q_from); 
        } 
    }else{ 
        for(int i = 0; i < ct_size; ++i){
            // Compute multiplicaiton on integers, and then convert to double
            temp = to->modulus * in_ct->ct[i];
            // Divide and round to closest integer
            out_ct->ct[i] = (long)round(temp/Q_from); 
        } 
    }   
}
   
LWEGadgetCT::LWEGadgetCT(std::shared_ptr<LWEParam> lwe_param, long base){
    this->lwe_param = lwe_param;
    this->base = base;  
    /// TODO:  Add check: Note that for now, we accept only power of two basis (because our decomposition is written this way)
    this->bits_base = Utils::power_times(base, 2);  
    this->digits = Utils::power_times(lwe_param->modulus, base);   
    this->ct_content = std::unique_ptr<std::unique_ptr<LWECT>[]>(new std::unique_ptr<LWECT>[digits]);  
}

void LWEGadgetCT::gadget_mul(LWECT *out_ct, long scalar){ 
    long *scalar_decomposed = new long[digits]; 
    Utils::integer_decomp(scalar_decomposed, scalar, base, bits_base, digits);
    LWECT temp_ct(lwe_param); 
    ct_content[0]->mul(out_ct, scalar_decomposed[0]);
    for(int i = 1; i < digits; ++i){
        ct_content[i]->mul(&temp_ct, scalar_decomposed[i]);
        out_ct->add(out_ct, &temp_ct);  
    }
    delete[] scalar_decomposed;  
} 
    
void LWEGadgetCT::gadget_mul_lazy(LWECT *out_ct, long scalar){ 
    long *scalar_decomposed = new long[digits]; 
    Utils::integer_decomp(scalar_decomposed, scalar, base, bits_base, digits);
    LWECT temp_ct(lwe_param); 
    ct_content[0]->mul_lazy(out_ct, scalar_decomposed[0]);
    for(int i = 1; i < digits; ++i){
        ct_content[i]->mul_lazy(&temp_ct, scalar_decomposed[i]);
        out_ct->add_lazy(out_ct, &temp_ct);  
    }
    delete[] scalar_decomposed;  
}
  
LWESK::~LWESK(){ 
    delete[] key; 
}
  
LWESK::LWESK(std::shared_ptr<LWEParam> lwe_par, double stddev, KeyDistribution key_type){
    this->param = lwe_par;  
    this->key = new long[param->dim];  
    this->stddev  = stddev;
    this->key_type = key_type;
    unif_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, param->modulus));
    error_dist = std::shared_ptr<Distribution>(new StandardRoundedGaussianDistribution(0, stddev)); 

    if(this->key_type == binary){  
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, 1));
    }else{ 
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(-1, 1));
    }
    sk_dist->fill_array(this->key, param->dim); 
    Utils::array_mod_form(this->key, this->key, param->dim, param->modulus);
    multiplier = std::unique_ptr<LongIntegerMultipler>(new LongIntegerMultipler(param->modulus));
}

LWESK::LWESK(std::shared_ptr<LWEParam> lwe_par, long* key, double stddev, KeyDistribution key_type){
    this->param = lwe_par;  
    this->key = new long[lwe_par->dim]; 
    this->stddev  = stddev;
    this->key_type = key_type;
    unif_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, param->modulus));
    error_dist = std::shared_ptr<Distribution>(new StandardRoundedGaussianDistribution(0, stddev));
    for(int i = 0; i < lwe_par->dim; ++i){
        this->key[i] = key[i];
    }   
    multiplier = std::unique_ptr<LongIntegerMultipler>(new LongIntegerMultipler(param->modulus));
}

LWESK::LWESK(const LWESK &other){
    std::runtime_error("LWESK::LWESK(const LWESK &other): Don't copy the secret key!"); 
}
 
LWESK& LWESK::operator=(const LWESK other){
    std::runtime_error("LWESK::operator=(const LWESK other): Don't copy the secret key!"); 
    return *this;
}
  
LWECT* LWESK::encrypt(long m){
    LWECT* out = new LWECT(param);
    encrypt(out, m);
    return out;
}
 
void LWESK::encrypt(LWECT *in, long m){     
    in->ct[0] = error_dist->next() + (long)m; 
    for(int i=1; i < param->dim+1; ++i){      
        /// TODO: I should assume the ct and key are in modular form. Then doing it here is not necessary.
        in->ct[i] = Utils::integer_mod_form(unif_dist->next(), param->modulus); 
        long k = Utils::integer_mod_form(key[i-1], param->modulus);
        long c = Utils::integer_mod_form(in->ct[i], param->modulus);
        in->ct[0] -= multiplier->mul(k,  c); 
        in->ct[0] = Utils::integer_mod_form(in->ct[0], param->modulus); 
    }   
}
  
LWECT* LWESK::encode_and_encrypt(long m, PlaintextEncoding encoding){  
    LWECT* out = new LWECT(this->param);
    encrypt(out, encoding.encode_message(m)); 
    return out;
}
 
void LWESK::encode_and_encrypt(LWECT* in, long m, PlaintextEncoding encoding){   
    encrypt(in, encoding.encode_message(m)); 
} 
 
long LWESK::partial_decrypt(LWECT *in){
    long phase  = in->ct[0]; 
    for(int i = 1; i < param->dim+1; ++i){ 
        long k = Utils::integer_mod_form(key[i-1], param->modulus);  
        long c = Utils::integer_mod_form(in->ct[i], param->modulus);  
        phase = (phase + multiplier->mul(c, k)) % param->modulus; 
    }   
    return phase; 
}
 
long LWESK::decrypt(LWECT *in, PlaintextEncoding encoding){
    return encoding.decode_message(partial_decrypt(in));
} 
 
LWEGadgetSK::LWEGadgetSK(std::shared_ptr<LWESK> lwe, long base){ 
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
 
LWEGadgetCT* LWEGadgetSK::gadget_encrypt(long m){ 
    LWEGadgetCT* out = new LWEGadgetCT(lwe->param, this->base); 
    gadget_encrypt(out, m);
    return out;
}

void LWEGadgetSK::gadget_encrypt(LWEGadgetCT* gadget_ct, long m){
    long temp_base = 1;    
    gadget_ct->ct_content[0] = std::unique_ptr<LWECT>(lwe->encrypt(m)); 
    for(int i = 1; i < this->digits; ++i){
        temp_base *= this->base;    
        gadget_ct->ct_content[i] = std::unique_ptr<LWECT>(lwe->encrypt(m * temp_base));
    } 
} 

LWEPublicKey::LWEPublicKey(std::shared_ptr<LWESK> lwe_sk, int size, double stddev){
    this->size = size;
    this->stddev = stddev;
    this->param = lwe_sk->param;
    this->rand_masking = Sampler(0.0, stddev);
    // Initialize the key switching key 
    this->public_key_ptr = std::unique_ptr<std::unique_ptr<LWECT>[]>(new std::unique_ptr<LWECT>[size]); 
    for(int i = 0; i < size; ++i){   
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

void LWEPublicKey::mask_ciphertext(LWECT *ct){ 
    LWECT temp(param);
    long noise; 
    for(int i  = 0; i < size; ++i){
        noise = rand_masking.normal_dist(rand_masking.e1); 
        public_key_ptr[i]->mul(&temp, noise); 
        ct->add(ct, &temp); 
    } 
}
  
LWECT* LWEPublicKey::encrypt(long message){
    LWECT* out = new LWECT(param); 
    long noise;
    noise = rand_masking.normal_dist(rand_masking.e1); 
    public_key_ptr[0]->mul(out, noise); 
    LWECT temp(param);
    for(int i = 1; i < size; ++i){
        noise = rand_masking.normal_dist(rand_masking.e1); 
        public_key_ptr[i]->mul(&temp, noise); 
        out->add(out, &temp); 
    } 
    //out = out + message;
    out->add(out, message); 
    return out;    
}
 
LWECT* LWEPublicKey::ciphertext_of_zero(){
    return LWEPublicKey::encrypt(0);
}