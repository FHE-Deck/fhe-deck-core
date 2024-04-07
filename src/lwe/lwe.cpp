#include "lwe.h"

using namespace fhe_deck;
 

LWEParam::LWEParam(int dim, long modulus, KeyDistribution key_d, double stddev){
    this->dim = dim;
    this->modulus = modulus;
    this->key_d = key_d;
    this->stddev = stddev;
}
 

LWEParam LWEParam::modulus_switch(long new_modulus){  
    double new_stddev = (new_modulus * this->stddev)/this->modulus;
    // TODO: Stddev in LWEParam has to disapear anyway.
    if(new_stddev < 3.2){
        // TODO: This is a sort of hack solution.
        // Actually we should choose it based on the key distribution, and the expected rounding error for the key distribution.
        // But to do this, perhaps the key_d parameter should be a more complex struct with hamming weight etc.  
        // Note: that this is needed only when making an encryption w.r.t. the modullus switched LWE. Fortunately, it's not used in the high level ingterface so I leave it for later.
        new_stddev = 3.2;
    } 
    LWEParam new_param(this->dim, new_modulus, this->key_d, new_stddev); 
    return new_param;
}


long* LWEParam::init_ct(){ 
    long* ct = new long[this->dim+1]; 
    for(int i = 0; i < dim+1; ++i){
        ct[i] = 0;
    }
    return ct;
}
  
 
void LWEParam::scalar_mul(long *out, long *ct, long scalar){
    for(int i = 0; i <= dim; ++i){
        out[i] = (ct[i] * scalar) % modulus;
    }
}

void LWEParam::scalar_mul_lazy(long *out, long *ct, long scalar){
    for(int i = 0; i <= dim; ++i){
        out[i] = (ct[i] * scalar);
    }
}

void LWEParam::add(long *out, long *ct_1, long *ct_2){
    for(int i = 0; i <= dim; ++i){
        out[i] = (ct_1[i] + ct_2[i]) % modulus;
    }
}

void LWEParam::add_lazy(long *out, long *ct_1, long *ct_2){
    for(int i = 0; i <= dim; ++i){
        out[i] = (ct_1[i] + ct_2[i]);
    }
}


void LWEParam::switch_modulus(long *out_ct, long *in_ct, LWEParam &new_param){ 
    // TODO: There is a bug here. If arithmetic is too big, then double will not be enough. Furthermore, the errors will actually be much higher then they should.
    double temp; 
    for(int i = 0; i < dim+1; ++i){
        temp =  new_param.modulus *  in_ct[i];
        out_ct[i] = (long)round(temp/(double)modulus); 
    }
}


// Deprecated
void LWEParam::switch_modulus(long *out_ct, long *in_ct, std::shared_ptr<LWEParam> new_param){ 
    // TODO: There is a bug here. If arithmetic is too big, then double will not be enough. Furthermore, the errors will actually be much higher then they should. 
    double temp; 
    for(int i = 0; i < dim+1; ++i){
        temp =  new_param->modulus * in_ct[i];
        out_ct[i] = (long)round(temp/(double)this->modulus); 
    }
}

  

LWECT::LWECT(std::shared_ptr<LWEParam> lwe_param){
    this->param = lwe_param;
    this->ct = param->init_ct();
    this->init = true; 
}

LWECT::LWECT(std::shared_ptr<LWEParam> lwe_param, long* ct){
    this->param = lwe_param;
    this->ct = param->init_ct();
    this->init = true;
    for(int i = 0; i < param->dim+1; ++i){
        this->ct[i] = ct[i];
    }
}


LWECT::LWECT(const LWECT &c){  
    this->param = c.param;
    this->ct = param->init_ct();
    //this->pe = c.pe;
    for(int i = 0; i < param->dim+1; ++i){
        this->ct[i] = c.ct[i];
    }
    this->init = true;
}




LWECT::LWECT(LWECT &c){  
    this->param = c.param;
    this->ct = param->init_ct(); 
    for(int i = 0; i < param->dim+1; ++i){
        this->ct[i] = c.ct[i];
    }
    this->init = true;
}


LWECT::LWECT(LWECT *c){  
    this->param = c->param;
    this->ct = param->init_ct(); 
    for(int i = 0; i < param->dim+1; ++i){
        this->ct[i] = c->ct[i];
    }
    this->init = true;
}
 


LWECT::~LWECT(){    
    delete[] ct;
}

void LWECT::scalar_mul(long scalar){
    for(int i = 0; i <= param->dim; ++i){
        ct[i] = (ct[i] * scalar) % param->modulus;
    }
}

void LWECT::mul(long scalar){
    for(int i = 0; i <= param->dim; ++i){
        ct[i] = (ct[i] * scalar) % param->modulus;
    }
}

void LWECT::scalar_mul_lazy(long scalar){
    for(int i = 0; i <= param->dim; ++i){
        ct[i] = (ct[i] * scalar);
    }
}

void LWECT::add(LWECT *in){ 
    for(int i = 0; i <= param->dim; ++i){
        this->ct[i] = (this->ct[i] + in->ct[i]) % param->modulus;
    }
}

void LWECT::add(LWECT *out, LWECT *in){
    for(int i = 0; i <= this->param->dim; ++i){
        out->ct[i] = (this->ct[i] + in->ct[i]) % this->param->modulus;
    }
}

void LWECT::sub(LWECT *c){
    for(int i = 0; i <= this->param->dim; ++i){
        this->ct[i] = Utils::integer_mod_form(this->ct[i] - c->ct[i], this->param->modulus);
    }
}

void LWECT::sub(LWECT* out, LWECT *in){
    for(int i = 0; i <= this->param->dim; ++i){
        out->ct[i] = Utils::integer_mod_form(this->ct[i] - in->ct[i], this->param->modulus);
    }
}

void LWECT::add_lazy(LWECT *c){
    for(int i = 0; i <= this->param->dim; ++i){
        this->ct[i] = this->ct[i] + c->ct[i] ;
    }
}

void LWECT::add_lazy(LWECT* out, LWECT *in){
    for(int i = 0; i <= this->param->dim; ++i){
        out->ct[i] = this->ct[i] + in->ct[i];
    }
}
 
void LWECT::add(long b){ 
    this->ct[0] = (this->ct[0] + b) % this->param->modulus;
}

void LWECT::add(LWECT* out, long b){ 
    out->ct[0] = (this->ct[0] + b) % this->param->modulus;
}

void LWECT::sub(long b){
    this->ct[0] = Utils::integer_mod_form(this->ct[0] - b, this->param->modulus);
}

void LWECT::sub(LWECT* out, long b){
    out->ct[0] = Utils::integer_mod_form(this->ct[0] - b, this->param->modulus);
}

LWECT& LWECT::operator=(const LWECT other){  
    if (this == &other)
    {
        return *this;
    }   
    if(init==false){
        this->param = other.param;
        this->ct = param->init_ct(); 
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

LWECT LWECT::operator+(long b){   
    LWECT ct_out(this);    
    ct_out.ct[0] = Utils::integer_mod_form(ct_out.ct[0] + b, param->modulus);
    return ct_out; 
}

LWECT LWECT::operator+(LWECT b){  
    LWECT ct_out(this);  
    ct_out.add(&b); 
    return ct_out;
}
   

LWECT LWECT::operator+(LWECT *b){  
    LWECT ct_out(this);  
    ct_out.add(b); 
    return ct_out;
}


LWECT LWECT::operator-(long b){  
    LWECT ct_out(this);  
    ct_out.ct[0] = Utils::integer_mod_form(ct_out.ct[0] - b, param->modulus); 
    return ct_out; 
}
    
LWECT LWECT::operator-(LWECT b){  
    LWECT ct_out(this);  
    ct_out.sub(&b); 
    return ct_out;
}

LWECT LWECT::operator-(LWECT *b){  
    LWECT ct_out(this);  
    ct_out.sub(b); 
    return ct_out;
}

LWECT LWECT::operator-(){  
    LWECT ct_out(this);  
    for(int i = 0; i < param->dim+1; ++i){
        ct_out.ct[i] = Utils::integer_mod_form(-this->ct[i], param->modulus);
    } 
    return ct_out;
}

LWECT LWECT::operator*(long b){
    LWECT ct_out = new LWECT(this);  
    ct_out.mul(b);
    return ct_out; 
}  
    
LWECT operator+(long b, LWECT ct){ 
    LWECT ct_out(&ct);  
    ct_out.ct[0] = Utils::integer_mod_form(ct_out.ct[0] +  b, ct_out.param->modulus);
    return ct_out; 
}

LWECT operator-(long b, LWECT ct){
    LWECT temp = -ct;
    LWECT ct_out(&temp);
    ct_out.ct[0] = Utils::integer_mod_form(ct_out.ct[0] + b, ct_out.param->modulus);
    return ct_out; 
}

LWECT operator*(long b, LWECT ct){
    LWECT ct_out(&ct);  
    ct_out.mul(b);
    return ct_out; 
}
 

LWEModSwitcher::LWEModSwitcher(std::shared_ptr<LWEParam> from, std::shared_ptr<LWEParam> to){
    this->from = from;
    this->to = to;

    // Check if we need long arithmetic
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


void LWEModSwitcher::switch_modulus(long *out_ct, long *in_ct){  
    if(long_arithmetic){
        for(int i = 0; i < ct_size; ++i){
            long_temp =  long_Q_to * (long double)in_ct[i];
            out_ct[i] = (long)roundl(long_temp/long_Q_from); 
        } 
    }else{ 
        for(int i = 0; i < ct_size; ++i){
            // Compute multiplicaiton on integers, and then convert to double
            temp =  to->modulus * in_ct[i];
            // Divide and round to closest integer
            out_ct[i] = (long)round(temp/Q_from); 
        }
 
    }   
}




   

 
LWEGadgetParam::LWEGadgetParam(std::shared_ptr<LWEParam> lwe_par, long base){
      this->lwe_param = lwe_par;
      this->base = base; 
      // Note that for now, we accept only power of two basis (because our decomposition is written this way)
      this->k = 1;
      long temp = 2;
      while(temp < base){
            temp *= 2;
            this->k++;
      }
      this->ell = 1;
      temp = base;
       
      while(temp < this->lwe_param->modulus){
            temp *= base;
            this->ell++;
      }
}


long** LWEGadgetParam::init_gadget_ct(){
    long **gadget_ct = new long*[this->ell];
    for(int i = 0; i < this->ell; ++i){
        gadget_ct[i] = this->lwe_param->init_ct();
    } 
    return gadget_ct;
}



void LWEGadgetParam::gadget_mul(long *out_ct, long** gadget_ct, long scalar){
    for(int i = 0; i < lwe_param->dim+1; ++i){
        out_ct[i] = 0;
    }
    long *scalar_decomposed = new long[ell]; 
    Utils::integer_decomp(scalar_decomposed, scalar, base, k, ell);
    long *temp_ct = new long[lwe_param->dim+1];
    for(int i = 0; i < ell; ++i){
        lwe_param->scalar_mul(temp_ct, gadget_ct[i], scalar_decomposed[i]);
        lwe_param->add(out_ct, out_ct, temp_ct);
    }
    delete[] scalar_decomposed;
    delete[] temp_ct;
}



void LWEGadgetParam::gadget_mul_lazy(long *out_ct, long** gadget_ct, long scalar){  
    for(int i = 0; i < lwe_param->dim+1; ++i){
        out_ct[i] = 0;
    }
    long *scalar_decomposed = new long[ell]; 
    Utils::integer_decomp(scalar_decomposed, scalar, base, k, ell);
    if(base==2){
        for(int i = 0; i < ell; ++i){
            if(scalar_decomposed[i]==1){
                lwe_param->add_lazy(out_ct, out_ct, gadget_ct[i]);
            }
        }
    }else{
        long *temp_ct = new long[lwe_param->dim+1];
        for(int i = 0; i < ell; ++i){
            lwe_param->scalar_mul_lazy(temp_ct, gadget_ct[i], scalar_decomposed[i]);
            lwe_param->add_lazy(out_ct, out_ct, temp_ct);
        } 
        delete[] temp_ct;
    }  
    delete[] scalar_decomposed;
}


 


LWESK::~LWESK(){
    if(is_init){
        delete[] s;
    }
}


LWESK::LWESK(){}


LWESK::LWESK(int n, long Q,  double stddev, KeyDistribution key_d){ 
    this->param = std::shared_ptr<LWEParam>(new LWEParam(n, Q, key_d, stddev));  
    this->s = new long[param->dim];

    unif_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, Q));
    error_dist = std::shared_ptr<Distribution>(new StandardRoundedGaussianDistribution(0, stddev));

    if(key_d == binary){  
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, 1));
    }else{ 
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(-1, 1));
    }
    sk_dist->fill_array(this->s, param->dim);
    is_init = true;
}

LWESK::LWESK(std::shared_ptr<LWEParam> lwe_par){
    this->param = lwe_par;  
    this->s = new long[param->dim];  
    unif_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, param->modulus));
    error_dist = std::shared_ptr<Distribution>(new StandardRoundedGaussianDistribution(0, param->stddev)); 
    if(param->key_d == binary){  
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, 1));
    }else{ 
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(-1, 1));
    }
    sk_dist->fill_array(this->s, param->dim);
    is_init = true;
}


LWESK::LWESK(std::shared_ptr<LWEParam> lwe_par, long* key){
    this->param = lwe_par;  
    this->s = new long[lwe_par->dim]; 
    unif_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, param->modulus));
    error_dist = std::shared_ptr<Distribution>(new StandardRoundedGaussianDistribution(0, param->stddev));
    for(int i = 0; i < lwe_par->dim; ++i){
        this->s[i] = key[i];
    } 
    is_init = true;
}


LWESK::LWESK(const LWESK &other){
    std::runtime_error("LWESK::LWESK(const LWESK &other): Don't copy the secret key!"); 
}
 

LWESK& LWESK::operator=(const LWESK other){
    std::runtime_error("LWESK::operator=(const LWESK other): Don't copy the secret key!"); 
    return *this;
}
 
std::shared_ptr<LWEParam> LWESK::get_lwe_param(){
    return param;
} 


long* LWESK::encrypt(long m){
    long *ct = param->init_ct(); 
    LWESK::encrypt(ct, m);
    return ct;
}

LWECT LWESK::encrypt_ct(long m){
    LWECT ct(param);
    encrypt(ct.ct, m);
    return ct;
}



void LWESK::encrypt(long *ct, long m){     
    ct[0] = error_dist->next() + (long)m; 
    for(int i=1; i < param->dim+1; ++i){    
        ct[i] = Utils::integer_mod_form(unif_dist->next(), param->modulus); 
        ct[0] -= s[i-1] * ct[i];
        ct[0] = Utils::integer_mod_form(ct[0] % param->modulus, param->modulus);
    }   
}


 long* LWESK::scale_and_encrypt(long m, int t){
    // TODO Potential problems when Q is too big. In this case should be long double
    double scale = (double)param->modulus/t;
    long m_scaled =  (long)round((double)m*scale); 
    return LWESK::encrypt(m_scaled);
 }
 
 void LWESK::scale_and_encrypt(long* ct, long m, int t){ 
    // TODO Potential problems when Q is too big. In this case should be long double
    double scale = (double)param->modulus/t;
    long m_scaled =  (long)round((double)m*scale); 
    encrypt(ct, m_scaled); 
} 



long LWESK::phase(long *ct){
    long phase  = ct[0]; 
    for(int i = 1; i < param->dim+1; ++i){ 
        phase += ct[i] * s[i-1];
        phase = phase % param->modulus; 
    }   
    return Utils::integer_mod_form(phase, param->modulus);
}


long LWESK::error(long *ct,  long m){   
    return Utils::integer_signed_form((LWESK::phase(ct) - m) % param->modulus, param->modulus); 
}


long LWESK::decrypt(long *ct, int t){ 
    long d_phase = LWESK::phase(ct);  
    // TODO Potential problems when Q is too big. In this case should be long double
    long out = round(((double)t/param->modulus) * d_phase); 
    return Utils::integer_mod_form(out, t);
}
   
std::shared_ptr<LWESK> LWESK::modulus_switch(long new_modulus){
    LWEParam lwe_par = this->param->modulus_switch(new_modulus);
    LWESK *lwe = new LWESK(std::shared_ptr<LWEParam>(new LWEParam(lwe_par.dim, lwe_par.modulus, lwe_par.key_d, lwe_par.stddev)), this->s); 
    return std::shared_ptr<LWESK>(lwe);
}
 

LWEGadgetSK::LWEGadgetSK(){}


LWEGadgetSK::LWEGadgetSK(LWEGadgetParam lwe_g_par, std::shared_ptr<LWESK> lwe){
    this->lwe = lwe;
    this->gadget_param = lwe_g_par;
}

LWEGadgetSK::LWEGadgetSK(const LWEGadgetSK &other){
    this->gadget_param = other.gadget_param;
    this->lwe = other.lwe;
}


LWEGadgetSK& LWEGadgetSK::operator=(const LWEGadgetSK other){
    this->gadget_param = other.gadget_param;
    this->lwe = other.lwe;
    return *this;
}

long** LWEGadgetSK::gadget_encrypt(long m){ 
    long **gadget_ct = gadget_param.init_gadget_ct(); 
    gadget_encrypt(gadget_ct, m);
    return gadget_ct;
}

void LWEGadgetSK::gadget_encrypt(long** gadget_ct, long m){
    long temp_base = 1; 
    gadget_ct[0] = lwe->encrypt(m);
    for(int i = 1; i < gadget_param.ell; ++i){
        temp_base *= gadget_param.base; 
        gadget_ct[i] = lwe->encrypt(m * temp_base);
    } 
}
 

LWEPublicKey::~LWEPublicKey(){ 
    delete[] public_key; 
}

 
LWEPublicKey::LWEPublicKey(std::shared_ptr<LWESK> lwe_sk, int size, double stddev){
    this->size = size;
    this->stddev = stddev;
    this->param = lwe_sk->param;
    this->rand_masking = Sampler(0.0, stddev);
    // Initialize the key switching key
    public_key = new long*[size]; 
    for(int i = 0; i < size; ++i){ 
        public_key[i] = lwe_sk->encrypt(0);   
    }  
}



LWEPublicKey::LWEPublicKey(const LWEPublicKey &other){
    this->size = other.size;
    this->stddev = other.stddev;
    this->param = other.param;
    this->rand_masking = Sampler(0.0, stddev);
    // Initialize the key switching key
    public_key = new long*[size]; 
    for(int i = 0; i < size; ++i){ 
        this->public_key[i] = param->init_ct();
        Utils::cp(this->public_key[i], public_key[i], param->dim+1); 
    } 
}
   
LWEPublicKey& LWEPublicKey::operator=(const LWEPublicKey other){
    this->size = other.size;
    this->stddev = other.stddev;
    this->param = other.param;
    this->rand_masking = Sampler(0.0, stddev);
    // Initialize the key switching key
    public_key = new long*[size]; 
    for(int i = 0; i < size; ++i){ 
        this->public_key[i] = param->init_ct();
        Utils::cp(this->public_key[i], public_key[i], param->dim+1); 
    } 
    return *this;
}


void LWEPublicKey::mask_ciphertext(long *ct){
    long* random_lwe = param->init_ct();
    long* temp = param->init_ct();
    long noise;
    for(int i  = 0; i < size; ++i){
        noise = rand_masking.normal_dist(rand_masking.e1); 
        param->scalar_mul(temp, public_key[i], noise);
        param->add(ct, ct, temp);
    }
    delete[] random_lwe;
    delete[] temp;
}


LWECT LWEPublicKey::encrypt(long message){
    LWECT out(param, public_key[0]);
    long* temp = param->init_ct();
    long noise;
    for(int i = 1; i < size; ++i){
        noise = rand_masking.normal_dist(rand_masking.e1); 
        param->scalar_mul(temp, public_key[i], noise);
        param->add(out.ct, out.ct, temp);
    }
    out = out + message; 
    delete[] temp;
    return out;
}


LWECT LWEPublicKey::ciphertext_of_zero(){
    return LWEPublicKey::encrypt(0);
}