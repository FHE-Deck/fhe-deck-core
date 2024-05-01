#include "ntru.h" 

using namespace fhe_deck;

 


NTRUParam::NTRUParam(RingType ring, int ring_degree, long coef_modulus, ModulusType mod_type, PolynomialArithmetic arithmetic){
    this->coef_modulus = coef_modulus;
    this->mod_type = mod_type; 
    this->size = ring_degree;  
    this->ring = ring;  
    this->arithmetic = arithmetic;   
    init_mul_engine();
}
        
NTRUParam::NTRUParam(int degree, long ring_degree, ModulusType mod_type, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine){
    this->size = ring_degree;
    this->coef_modulus = coef_modulus;
    this->mod_type = mod_type; 
    this->mul_engine = mul_engine; 
    this->arithmetic = mul_engine->type;
    this->is_mul_engine_init = true;
}

NTRUParam::NTRUParam(NTRUParam &other){ 
    throw std::runtime_error("RLWEParam::RLWEParam(RLWEParam &other)"); 
}

NTRUParam& NTRUParam::operator=(const NTRUParam other){ 
    throw std::runtime_error("RLWEParam& RLWEParam::operator=(const RLWEParam other)"); 
    return *this;
}

void NTRUParam::init_mul_engine(){ 
    // Build PolynomialMultiplicationEngine
    PolynomialMultiplicationEngineBuilder mul_engine_builder;
    mul_engine_builder.set_coef_modulus(coef_modulus); 
    mul_engine_builder.set_degree(size);
    mul_engine_builder.set_polynomial_arithmetic(arithmetic);
    mul_engine_builder.set_ring_type(ring);
    mul_engine_builder.set_modulus_type(mod_type);
    this->mul_engine = mul_engine_builder.build(); 
    this->is_mul_engine_init = true;
}

VectorCT* NTRUParam::init_ct(){
    return new NTRUCT(std::shared_ptr<NTRUParam>(this));
}

Polynomial NTRUParam::init_poly(){ 
    return Polynomial(size, coef_modulus, mul_engine); 
}
 
Polynomial NTRUParam::init_zero_poly(){
    Polynomial out(this->size, coef_modulus, mul_engine);
    for(int i = 0; i < this->size; ++i){
        out.coefs[i] = 0;
    }
    return out;
}
 



NTRUCT::NTRUCT(std::shared_ptr<NTRUParam> param){
    this->param = param; 
    c = this->param->init_poly();  
}
 
NTRUCT::NTRUCT(const NTRUCT &other){ 
    this->param = other.param;
    this->c = other.c; 
}
 
NTRUCT& NTRUCT::operator=(const NTRUCT other){  
    this->param = other.param;
    this->c = other.c; 
    return *this;
}
  
void NTRUCT::negacyclic_rotate(NTRUCT *out, int rot){  
    NTRUCT *out_ptr = static_cast<NTRUCT*>(out); 
    c.negacyclic_rotate(&out_ptr->c, rot);  
}

void NTRUCT::cyclic_rotate(NTRUCT *out, int rot){  
    NTRUCT *out_ptr = static_cast<NTRUCT*>(out); 
    c.cyclic_rotate(&out_ptr->c, rot); 
}

void NTRUCT::homomorphic_rotate(VectorCT *out, int rot){ 
    // zWhat we do here, is realy multiplication with a monomial.
    if(this->param->ring == negacyclic){ 
        negacyclic_rotate(static_cast<NTRUCT*>(out), rot);
    }else if(this->param->ring == cyclic){
        cyclic_rotate(static_cast<NTRUCT*>(out), rot);
    }else{
        throw std::logic_error("NTRUCT::homomorphic_rotate(VectorCT *out, int rot): this->param->ring currently not supported.");
    }
}
 
void NTRUCT::add(VectorCT* out, VectorCT *ct){  
    NTRUCT *out_ptr = static_cast<NTRUCT*>(out); 
    NTRUCT *ct_ptr = static_cast<NTRUCT*>(ct);
    ct_ptr->c.add(&out_ptr->c, &c); 
}
  
void NTRUCT::add(NTRUCT *out, Polynomial *x){
    c.add(&out->c, x); 
}
 
void NTRUCT::sub(VectorCT *out, VectorCT *ct){  
    NTRUCT *out_ptr = static_cast<NTRUCT*>(out);
    NTRUCT *ct_ptr = static_cast<NTRUCT*>(ct);
    c.sub(&out_ptr->c, &ct_ptr->c);
    c.sub(&out_ptr->c, &ct_ptr->c); 
}
  
void NTRUCT::sub(NTRUCT *out, Polynomial *x){
    c.sub(&out->c, x);  
}

void NTRUCT::neg(VectorCT *out){
    NTRUCT *out_ptr = static_cast<NTRUCT*>(out); 
    c.neg(&out_ptr->c); 
}
  
void NTRUCT::mul(NTRUCT *out, Polynomial *x){ 
    this->c.mul(&out->c, x, param->mul_engine);
    this->c.mul(&out->c, x, param->mul_engine); 
}
 
std::string NTRUCT::to_string(){
    std::string out = "[" + Utils::to_string(c.coefs, param->size) + "]";
    return out;
}
  
void NTRUCT::extract_lwe(long *lwe_ct_out){
    /// TODO: Need to test this. 
    lwe_ct_out[0] = this->c.coefs[0]; 
    for(int i = 1; i < this->param->size; ++i){
        lwe_ct_out[i+1] = -this->c.coefs[this->param->size - i];
    } 
}

LWECT NTRUCT::extract_lwe(std::shared_ptr<LWEParam> lwe_par){ 
    LWECT out(lwe_par);
    this->extract_lwe(out.ct);
    return out; 
}
     
 
NTRUGadgetCT::NTRUGadgetCT(std::shared_ptr<NTRUParam> ntru_param, std::shared_ptr<Gadget> gadget, std::vector<NTRUCT> &gadget_ct){
    this->ntru_param = ntru_param;
    this->gadget = gadget;
    this->init(gadget_ct);
}

void NTRUGadgetCT::init(std::vector<NTRUCT> &gadget_ct){     
    PolynomialArrayCoefForm array_coef(ntru_param->size,  
                                            ntru_param->coef_modulus,  
                                            gadget->digits);  
 
    this->array_eval_a = PolynomialArrayEvalForm(ntru_param->mul_engine, 
                                                gadget->digits);   
    for(int i = 0; i < gadget->digits; ++i){ 
        array_coef.set_polynomial_at(i, &gadget_ct[i].c);
    }  
    ntru_param->mul_engine->to_eval(&array_eval_a, &array_coef);  
    
    init_gadget_decomp_tables();  
    set_gadget_decomp_arrays();
    this->is_init = true; 
}

NTRUGadgetCT::~NTRUGadgetCT(){     
    if(is_init == false){
        return;
    }       
    delete[] deter_ct_a_dec;
}
 
NTRUGadgetCT::NTRUGadgetCT(const NTRUGadgetCT& other){    
    throw std::runtime_error("NTRUGadgetCT::NTRUGadgetCT(const RLWEGadgetCT& other)");
}

NTRUGadgetCT& NTRUGadgetCT::operator=(NTRUGadgetCT other){  
    throw std::runtime_error("NTRUGadgetCT& NTRUGadgetCT::operator=(NTRUGadgetCT other)");
    return *this;
}
  
void NTRUGadgetCT::mul(VectorCT *out, const VectorCT *ct){
    NTRUCT* out_ptr = static_cast<NTRUCT*>(out);
    const NTRUCT* ct_ptr = static_cast<const NTRUCT*>(ct);
    gadget->sample(deter_ct_a_dec, ct_ptr->c.coefs); 
    ntru_param->mul_engine->multisum(&out_ptr->c, &deter_ct_a_dec_poly, &array_eval_a);
}
  
void NTRUGadgetCT::init_gadget_decomp_tables(){
    // Set up also precomputed arrays for gadget decomposition   
    deter_ct_a_dec = new long*[gadget->digits]; 
}

void NTRUGadgetCT::set_gadget_decomp_arrays(){  
    deter_ct_a_dec_poly = PolynomialArrayCoefForm(ntru_param->size, ntru_param->coef_modulus, gadget->digits); 
    // Point the polynomials to the long tables. 
    for(int i = 0; i < gadget->digits; ++i){ 
        deter_ct_a_dec[i] = &deter_ct_a_dec_poly.poly_array[i * deter_ct_a_dec_poly.degree];  
    } 
}


 
NTRUSK::NTRUSK(std::shared_ptr<NTRUParam> param, double noise_stddev){ 
    this->param = param; 
    this->noise_stddev = noise_stddev; 
    this->error_dist = std::shared_ptr<Distribution>(new StandardRoundedGaussianDistribution(0, noise_stddev));
    sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(-1, 1)); 
    key_gen(); 
}
 
void NTRUSK::key_gen(){ 
    int status = 1;   
    NTL::ZZ_pX temp_f;
    NTL::ZZ_pX temp_inv_f;
    this->sk = Polynomial(param->size, param->coef_modulus); 
    do{  
        sk_dist->fill_array(this->sk.coefs, param->size);   
        Utils::set_polynomial_from_array(temp_f, this->sk.coefs, param->size, param->coef_modulus);
        status = NTL::InvModStatus(temp_inv_f, temp_f, Utils::get_ring_poly(negacyclic, param->size, param->coef_modulus));  
    }while(status == 1); 
    this->inv_sk = Polynomial(param->size, param->coef_modulus); 
    Utils::set_array_from_polynomial(this->sk.coefs, param->size, temp_f); 
    Utils::set_array_from_polynomial(this->inv_sk.coefs, param->size, temp_inv_f);     
}  
  
NTRUSK::NTRUSK(const NTRUSK &other){
    throw std::runtime_error("NTRUSK::NTRUSK(const NTRUSK &other): Don't copy the secret key!"); 
}

NTRUSK& NTRUSK::operator=(const NTRUSK other){  
    throw std::runtime_error("NTRUSK::operator=(const NTRUSK other): Don't copy the secret key!"); 
    return *this;
}
  
void NTRUSK::encrypt(NTRUCT *out, Polynomial *m){  
    if(m->degree < param->size){
        throw std::logic_error("NTRUSK::encrypt(Polynomial *m): Input polynomial m, degree is too big!");
    }
    if(m->coef_modulus < param->coef_modulus){
        throw std::logic_error("NTRUSK::encrypt(Polynomial *m): Input polynomial m, coefficient codulus is too big!");
    }
    if(!m->is_init){
        throw std::logic_error("NTRUSK::encrypt(Polynomial *m): Input polynomial m is not initialized!");
    }  
    /// NOTE: We compute inv_sk * g + e + msg
    Polynomial g = param->init_poly();
    sk_dist->fill_array(g.coefs, g.degree);
    Polynomial e = param->init_poly();
    error_dist->fill_array(e.coefs, e.degree); 
    inv_sk.mul(&out->c, &g, param->mul_engine);
    out->c.add(&out->c, &e);
    out->c.add(&out->c, m);
}

NTRUCT NTRUSK::encrypt(Polynomial *m){   
    NTRUCT out(param);  
    this->encrypt(&out, m);
    return out;
}

NTRUCT NTRUSK::encode_and_encrypt(Polynomial* m, PlaintextEncoding encoding){ 
    Polynomial m_scaled(param->size, param->coef_modulus); 
    for(int i = 0; i < param->size; ++i){ 
        m_scaled.coefs[i] = encoding.encode_message(m->coefs[i]);
    }
    NTRUCT out = encrypt(&m_scaled); 
    return out;
}

 
void NTRUSK::partial_decrypt(Polynomial *phase, NTRUCT *ct){   
    if(phase->degree != param->size){
        throw std::logic_error("NTRUSK::phase(Polynomial *phase, RLWECT *ct): Dimension of the input polynomial differs from the the RLWE polynomials.");
    }
    if(phase->coef_modulus != param->coef_modulus){
        throw std::logic_error("NTRUSK::phase(Polynomial *phase, RLWECT *ct): Coefficient modulus of the input polynomial differs from the the RLWE polynomials.");
    }
    if(!phase->is_init){
        throw std::logic_error("NTRUSK::phase(Polynomial *phase, RLWECT *ct): Input polynomial is not initialized.");
    } 
    sk.mul(phase, &ct->c, param->mul_engine); 
}

// Uses SK
Polynomial NTRUSK::decrypt(NTRUCT *ct, PlaintextEncoding encoding){ 
    Polynomial out(param->size, param->coef_modulus);
    decrypt(&out, ct, encoding);  
    return out;
}

// Uses SK
void NTRUSK::decrypt(Polynomial *out, NTRUCT *ct, PlaintextEncoding encoding){   
    this->partial_decrypt(out, ct);  
    for(int i = 0; i < out->degree; ++i){
        out->coefs[i] = encoding.decode_message(out->coefs[i]);
    } 
}


NTRUCT NTRUSK::kdm_encrypt(Polynomial* msg){
    NTRUCT out(param);
    kdm_encrypt(&out, msg);
    return out;
} 

void NTRUSK::kdm_encrypt(NTRUCT *out, Polynomial* msg){
    Polynomial kdm_msg(param->size, param->coef_modulus);
    inv_sk.mul(&kdm_msg, msg, param->mul_engine);
    encrypt(out, &kdm_msg);
}


void NTRUSK::kdm_encode_and_encrypt(NTRUCT *out, Polynomial* msg, PlaintextEncoding encoding){
    Polynomial m_scaled(param->size, param->coef_modulus); 
    for(int i = 0; i < param->size; ++i){ 
        m_scaled.coefs[i] = encoding.encode_message(msg->coefs[i]);
    }
    kdm_encrypt(out, &m_scaled);  
}


NTRUCT NTRUSK::kdm_encode_and_encrypt(Polynomial* msg, PlaintextEncoding encoding){
    Polynomial m_scaled(param->size, param->coef_modulus); 
    for(int i = 0; i < param->size; ++i){ 
        m_scaled.coefs[i] = encoding.encode_message(msg->coefs[i]);
    }
    NTRUCT out(param);
    kdm_encrypt(&out, &m_scaled);  
    return out;
}

 

void NTRUSK::extract_lwe_key(long* lwe_key){  
    for(int i = 0; i <  param->size; ++i){ 
        lwe_key[i] = -this->sk.coefs[i]; 
    } 
}

LWESK* NTRUSK::extract_lwe_key(){
    long* extract_key = new long[param->size]; 
    std::shared_ptr<LWEParam> lwe_param = std::shared_ptr<LWEParam>(new LWEParam(param->size, param->coef_modulus));
    for(int i = 0; i <  param->size; ++i){ 
        extract_key[i] = -this->sk.coefs[i]; 
    } 
    LWESK* key = new LWESK(lwe_param, extract_key, this->noise_stddev, ternary);
    delete[] extract_key;
    return key;
}





 
NTRUGadgetSK::NTRUGadgetSK(std::shared_ptr<Gadget> gadget, std::shared_ptr<NTRUSK> sk){ 
    this->gadget = gadget; 
    this->vector_ct_param = sk->param;
    this->sk = sk; 
}

NTRUGadgetSK& NTRUGadgetSK::operator=(const NTRUGadgetSK other){  
    throw std::runtime_error("NTRUGadgetSK::operator=(const NTRUGadgetSK other): Don't copy the secret key!");
    return *this;
}
 
NTRUGadgetSK::NTRUGadgetSK(const NTRUGadgetSK &other){ 
    throw std::runtime_error("NTRUGadgetSK::NTRUGadgetSK(const NTRUGadgetSK &other): Don't copy the secret key!");  
}
  
GadgetVectorCT* NTRUGadgetSK::gadget_encrypt(Polynomial *msg){     
    std::vector<NTRUCT> gadget_ct;     
    int digits = gadget->digits;
    long base = gadget->base;   
    // Encryptions of - msg* base**i    
    gadget_ct.push_back(sk->encrypt(msg));
    for(int i = 1; i < digits; ++i){
        // Multiply msg by base
        msg->mul(msg, base); 
        // Encrypt msg * base**i   
        gadget_ct.push_back(sk->encrypt(msg)); 
    }   
    return new NTRUGadgetCT(sk->param, gadget, gadget_ct);
}


GadgetVectorCT* NTRUGadgetSK::gadget_encrypt(long *msg, int size){
    if(size > sk->param->size){
        throw std::logic_error("GadgetVectorCT* NTRUGadgetSK::gadget_encrypt(long *msg, int size): size of the message array too big.");
    }
    Polynomial msg_poly(sk->param->size, sk->param->coef_modulus); 
    msg_poly.zeroize();
    for(int i = 0; i < size; ++i){
        msg_poly.coefs[i] = msg[i];
    }
    return gadget_encrypt(&msg_poly);
}


GadgetVectorCT* NTRUGadgetSK::kdm_gadget_encrypt(Polynomial *msg){
    std::vector<NTRUCT> gadget_ct;     
    int digits = gadget->digits;
    long base = gadget->base;   
    // Encryptions of - msg* base**i    
    gadget_ct.push_back(sk->kdm_encrypt(msg));
    for(int i = 1; i < digits; ++i){
        // Multiply msg by base
        msg->mul(msg, base); 
        // Encrypt msg * base**i   
        gadget_ct.push_back(sk->kdm_encrypt(msg)); 
    }   
    return new NTRUGadgetCT(sk->param, gadget, gadget_ct);
} 

GadgetVectorCT* NTRUGadgetSK::kdm_gadget_encrypt(long *msg, int size){
    if(size > sk->param->size){
        throw std::logic_error("GadgetVectorCT* NTRUGadgetSK::gadget_encrypt(long *msg, int size): size of the message array too big.");
    }
    Polynomial msg_poly(sk->param->size, sk->param->coef_modulus); 
    msg_poly.zeroize();
    for(int i = 0; i < size; ++i){
        msg_poly.coefs[i] = msg[i];
    }
    return kdm_gadget_encrypt(&msg_poly);
} 














ntru_sk::~ntru_sk(){  
}
 
ntru_sk::ntru_sk(){}

ntru_sk::ntru_sk(ntru_param param){
    this->param = param; 
    key_gen();
}

ntru_sk::ntru_sk(ntru_param param, long *f, long *inv_f){
    this->param = param;  
    this->f = f; 
    this->inv_f = inv_f; 
}


ntru_sk::ntru_sk(ntru_param param, long *f, long *inv_f, ntru_param higher_mod_param){
    this->param = param;  
    this->f = f; 
    this->inv_f = inv_f; 
    this->modulus_switched = true;
    this->higher_mod_param = higher_mod_param;
} 


ntru_sk& ntru_sk::operator=(const ntru_sk other){
    this->param = other.param;  
    this->modulus_switched = other.modulus_switched;
    if(modulus_switched){
        this->higher_mod_param = other.higher_mod_param;
    }
    f = param.init_poly();
    inv_f = param.init_poly();
    Utils::cp(f, other.f, param.N);
    Utils::cp(inv_f, other.inv_f, param.N);
    return *this;
}

void ntru_sk::ternary_poly(NTL::ZZ_pX &temp_f,  ntru_param &param){ 
    NTL::ZZ_p coef; 
    coef.init(NTL::ZZ(param.Q)); 
    for(int i = 0; i < param.N; ++i){ 
        coef = param.rand.ternary(); 
        NTL::SetCoeff(temp_f, i, coef); 
    } 
}

void ntru_sk::gaussian_poly(NTL::ZZ_pX &temp_f, ntru_param &param){ 
    NTL::ZZ_p coef;
    coef.init(NTL::ZZ(param.Q));
    for(int i = 0; i < param.N; ++i){
        coef = param.rand.ternary();
        NTL::SetCoeff(temp_f, i, coef);
    } 
}


void ntru_sk::key_gen(){ 
    f = param.init_poly();
    inv_f = param.init_poly();
    ntru_sk::key_gen(f, inv_f, param);
}


void ntru_sk::key_gen(long *f, long *inv_f, ntru_param &param){ 
    int status = 1;   
    NTL::ZZ_pX temp_f;
    NTL::ZZ_pX temp_inv_f;
    do{ 
        ntru_sk::ternary_poly(temp_f, param); 
        status = NTL::InvModStatus(temp_inv_f, temp_f, Utils::get_ring_poly(param.ring, param.N, param.Q));  
    }while(status == 1); 
    Utils::set_array_from_polynomial(f,  param.N, temp_f); 
    Utils::set_array_from_polynomial(inv_f, param.N, temp_inv_f);    
    Utils::array_signed_form(f, f, param.N, param.Q);
}  


 

ntru_ct ntru_sk::encrypt(long* msg){    
   ntru_ct ct_ntru(param); 
   naive_encrypt(&ct_ntru, msg);
   return ct_ntru;
} 


void ntru_sk::kdm_scale_and_encrypt(ntru_ct *ct_out, long* msg, int t){
    long scale;
    if(modulus_switched){
        // We only use a diffrent scale in this case
        // The different algorithm and modulus will be handled by the encryption algorithm.
       scale = higher_mod_param.Q/t; 
    }else{
        scale = param.Q/t; 
    }
    long* msg_scaled = param.init_poly(); 
    Utils::mul_scalar(msg_scaled, msg, param.N, scale); 
    kdm_encrypt(ct_out, msg_scaled);

    delete[] msg_scaled; 
}

ntru_ct ntru_sk::kdm_scale_and_encrypt(long* msg, int t){ 
    ntru_ct ct_ntru(param);
    kdm_scale_and_encrypt(&ct_ntru, msg, t);
    return ct_ntru;
}


ntru_ct ntru_sk::kdm_encrypt(long* msg){   
   ntru_ct ct_ntru(param);
   kdm_encrypt(&ct_ntru, msg);
   return ct_ntru;
}
 
void ntru_sk::kdm_encrypt(ntru_ct *ct_out, long* msg){    
    long* kdm_msg = param.init_poly();  
    if(modulus_switched){   
        Utils::mul_mod(kdm_msg, msg, param.N, inv_f, param.N, higher_mod_param.N, higher_mod_param.Q, higher_mod_param.ring);  
        ntru_sk higher_mod_ntru(higher_mod_param, f, inv_f); 
        ntru_ct new_ct;
        new_ct = higher_mod_ntru.encrypt(kdm_msg);
        new_ct = new_ct.mod_switch(param); 
        if(param.engine->long_arithmetic == true){
            // TODO: Copy when long arithmetic (If that is even necessary..... Maybe its only needed for gadget mul? - Lets check)
        }else{
            Utils::cp(ct_out->c, new_ct.c, param.N);  
        } 
    }else{ 
        Utils::mul_mod(kdm_msg, msg, param.N, inv_f, param.N, param.N, param.Q, param.ring);  
        encrypt(ct_out, kdm_msg); 
    }  
    delete(kdm_msg);
}

 


/*
This encryption algorithm is deprecated!!!
The reason is that the fft induces errors already at this stage which are greatly amplified when gadget multiplying
Currently we are using naive encrypt via NTL.
In the future, I plan to use NTT (if paramteres satisfy the NTT conditions), 
and the naive encrypt for params that don't satisfy these conditions.
*/
void ntru_sk::encrypt(ntru_ct *ct_out, long* msg){    
    if(param.engine->long_arithmetic){  
        long* g = param.init_poly();
        param.rand.ternary_array(g, param.N);

        long* e = param.init_poly();
        param.rand.gaussian_array(e, param.N, 0, param.stddev);

        long* s = param.init_poly();
        param.rand.ternary_array(s, param.N);
        
        fftwl_complex *g_fft = new fftwl_complex[param.engine->plan_size]; 
        fftwl_complex *e_fft = new fftwl_complex[param.engine->plan_size]; 
        fftwl_complex *c_fft = new fftwl_complex[param.engine->plan_size];  
        fftwl_complex *s_fft = new fftwl_complex[param.engine->plan_size];  

        param.engine->to_eval_form_l(g_fft, g);  
        param.engine->to_eval_form_scale_l(e_fft, g);  
        param.engine->to_eval_form_l(s_fft, s); 
        
        // TODO: This has to be precomputed
        fftwl_complex *inv_f_fft = new fftwl_complex[param.engine->plan_size];  
        param.engine->to_eval_form_scale_l(inv_f_fft, inv_f); 
        // inv_f * g
        param.engine->mul_eval_form_l(c_fft, g_fft, inv_f_fft); 
        // c_fft * s
        //param.engine->mul_eval_form_l(c_fft, c_fft, s_fft);
    
        fftwl_complex *msg_fft = new fftwl_complex[param.engine->plan_size];    
        param.engine->to_eval_form_scale_l(msg_fft, msg);  
        // inv_f * g + msg
        param.engine->add_eval_form_l(c_fft, c_fft, msg_fft);
        param.engine->add_eval_form_l(c_fft, c_fft, e_fft);

        // To coef form and mod reduce
        long* result = new long[param.engine->plan_size];
        param.engine->to_coef_form_l(result, c_fft);  
        Utils::mod_reduce(ct_out->c, result, param.Q, param.N);  
        delete(g);
        delete(g_fft);
        delete(e);
        delete(e_fft);
        delete(s); 
        delete(s_fft); 
        delete(c_fft);
        delete(inv_f_fft); 
        delete(msg_fft); 
        delete(result); 
    }else{ 
        long* g = param.init_poly();
        param.rand.ternary_array(g, param.N); 
        long* e = param.init_poly();
        param.rand.gaussian_array(e, param.N, 0, param.stddev);  
        
        fftw_complex *g_fft = new fftw_complex[param.engine->plan_size]; 
        fftw_complex *e_fft = new fftw_complex[param.engine->plan_size];  
        fftw_complex *c_fft = new fftw_complex[param.engine->plan_size]; 
        //fftw_complex *s_fft = new fftw_complex[param.engine->plan_size];   
         
        param.engine->to_eval_form(g_fft, g); 
        param.engine->to_eval_form_scale(e_fft, e);   
        //param.engine->to_eval_form(s_fft, s); 
         
        fftw_complex *inv_f_fft = new fftw_complex[param.engine->plan_size]; 
        // Remember that when you don't scale the ciphertext, then you may end up with rubish 
        param.engine->to_eval_form_scale(inv_f_fft, inv_f);  
        // inv_f * g
        param.engine->mul_eval_form(c_fft, g_fft, inv_f_fft); 
        // c_fft * s
        //param.engine->mul_eval_form(c_fft, c_fft, s_fft); 
    
        fftw_complex *msg_fft = new fftw_complex[param.engine->plan_size];    
        param.engine->to_eval_form_scale(msg_fft, msg);  
        // inv_f * g + msg
        param.engine->add_eval_form(c_fft, c_fft, msg_fft);
        param.engine->add_eval_form(c_fft, c_fft, e_fft);

        // To coef form and mod reduce
        long* result = new long[param.engine->plan_size];
        param.engine->to_coef_form(result, c_fft);  
        Utils::mod_reduce(ct_out->c, result, param.Q, param.N);  

         
        delete(c_fft); 
        delete(g); 
        delete(g_fft); 
        delete(e); 
        delete(e_fft);
        //delete(s); 
        //delete(s_fft); 
        delete(inv_f_fft);  
        delete(msg_fft);  
        delete(result);  
    }
} 





void ntru_sk::naive_encrypt(ntru_ct *ct_out, long* msg){     
        long* g = param.init_poly();
        param.rand.ternary_array(g, param.N); 
        long* e = param.init_poly();
        param.rand.gaussian_array(e, param.N, 0, param.stddev); 
        long* s = param.init_poly();
        param.rand.ternary_array(s, param.N); 
        Utils::mul_mod(ct_out->c, inv_f, param.N, g, param.N, param.N, param.Q, param.ring);
        Utils::mul_mod(ct_out->c, ct_out->c, param.N, s, param.N, param.N, param.Q, param.ring);
        Utils::add_mod(ct_out->c, ct_out->c, param.N, e, param.N, param.N, param.Q);
        Utils::add_mod(ct_out->c, ct_out->c, param.N, msg, param.N, param.N, param.Q); 
        delete[] g;
        delete[] e;
        delete[] s;
} 

// Only computes ct * f
void ntru_sk::phase(long *phase, ntru_ct *ct){
    NTL::ZZ_pX ct_poly;
    Utils::set_polynomial_from_array(ct_poly, ct->c, param.N, param.Q); 
    NTL::ZZ_pX f_poly;
    Utils::set_polynomial_from_array(f_poly, f, param.N, param.Q); 
    NTL::ZZ_pX phase_poly = NTL::MulMod(ct_poly, f_poly, Utils::get_ring_poly(param.ring, param.N, param.Q));  
    Utils::set_array_from_polynomial(phase, param.N, phase_poly); 
    Utils::array_signed_form(phase, phase, param.N, param.Q);
}


void ntru_sk::error(long *err, ntru_ct *ct, long* msg){
    phase(err, ct); 
    for(int i = 0; i < param.N; ++i){
            err[i] = (err[i] - msg[i]) % param.Q;
      }
      Utils::array_signed_form(err, err, param.N, param.Q);
}
 
long* ntru_sk::decrypt(ntru_ct *ct, int t){  
   long *out_msg = param.init_poly();
   decrypt(out_msg, ct, t);
   return out_msg;
}


void ntru_sk::decrypt(long* out, ntru_ct *ct, int t){  
    long* phase = param.init_poly(); 
    ntru_sk::phase(phase, ct);  
    Utils::array_rounding(out, phase, param.N, param.Q, t);
    delete(phase); 
}

 

/*
Eventually should decrypt the 0 coef, but for now I will focus only on the first coefficent. 
*/
long ntru_sk::decrypt_coef(ntru_ct *ct, int t){
    long ret = ct->c[0] * f[0];
    for(int i=1; i < param.N; ++i){
        ret -= ct->c[i] * f[param.N-i];
        ret = ret % param.Q;
    }  
    ret =  Utils::integer_rounding(ret, param.Q, t); 
    return Utils::integer_signed_form(ret, param.Q);
}

 

ntru_sk ntru_sk::mod_switch(long new_modulus){ 
    ntru_param new_param = param.mod_switch(new_modulus); 
    return ntru_sk(new_param, f, inv_f, param);  
} 

  


gadget_ntru::gadget_ntru(){}


gadget_ntru::gadget_ntru(ntru_gadget_param gadget_param, ntru_sk ntru){
    this->gadget_param = gadget_param;
    this->ntru = ntru;
}


ntru_gadget_ct gadget_ntru::gadget_encrypt(long* msg){  
   ntru_gadget_ct out = ntru_gadget_ct(gadget_param.param, gadget_param.basis, gadget_param.arithmetic);    
   gadget_encrypt(out.gadget_ct, msg);  
   out.to_eval();   
   return out; 
}



void gadget_ntru::gadget_encrypt(long** gadget_ct, long* msg){ 
   for(int i = 0; i < gadget_param.ell; ++i){
      gadget_ct[i] = gadget_param.param.init_poly();
   }
   long* msg_cpy = gadget_param.param.init_zero_poly();
   for(int i = 0; i < gadget_param.param.N; ++i){
       msg_cpy[i] = msg[i];
   } 
    
   ntru_ct temp_ct = ntru.encrypt(msg_cpy);
    //Encrypt msg * 1 
    Utils::cp(gadget_ct[0], temp_ct.c, gadget_param.param.N); 
    for(int i = 1; i < gadget_param.ell; ++i){
        // Multiply msg by basis
        for(int j=0; j < gadget_param.param.N; ++j){
            msg_cpy[j] = (msg_cpy[j] * gadget_param.basis) % gadget_param.param.Q;
        } 
        // Encrypt msg * basis**i 
        temp_ct = ntru.encrypt(msg_cpy);
        Utils::cp(gadget_ct[i], temp_ct.c, gadget_param.param.N); 
    }
    delete[] msg_cpy;
}

 
