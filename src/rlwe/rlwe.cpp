#include "rlwe.h"

using namespace fhe_deck;

RLWECT::RLWECT(std::shared_ptr<RLWEParam> param){
    this->param = param; 
    a = this->param->init_poly();
    b = this->param->init_poly();   
}
 
RLWECT::RLWECT(const RLWECT &other){ 
    this->param = other.param;
    this->a = other.a;
    this->b = other.b; 
}
 
RLWECT& RLWECT::operator=(const RLWECT other){  
    this->param = other.param;
    this->a = other.a;
    this->b = other.b;   
    return *this;
}
  
void RLWECT::negacyclic_rotate(RLWECT *out, int rot){  
    RLWECT *out_ptr = static_cast<RLWECT*>(out); 
    a.negacyclic_rotate(&out_ptr->a, rot);
    b.negacyclic_rotate(&out_ptr->b, rot); 
}

void RLWECT::cyclic_rotate(RLWECT *out, int rot){  
    RLWECT *out_ptr = static_cast<RLWECT*>(out); 
    a.cyclic_rotate(&out_ptr->a, rot);
    b.cyclic_rotate(&out_ptr->b, rot); 
}

void RLWECT::homomorphic_rotate(VectorCT *out, int rot){ 
    // zWhat we do here, is realy multiplication with a monomial.
    if(this->param->ring == negacyclic){ 
        negacyclic_rotate(static_cast<RLWECT*>(out), rot);
    }else if(this->param->ring == cyclic){
        cyclic_rotate(static_cast<RLWECT*>(out), rot);
    }else{
        throw std::logic_error("RLWECT::homomorphic_rotate(VectorCT *out, int rot): this->param->ring currently not supported.");
    }
}
 
void RLWECT::add(VectorCT* out, VectorCT *ct){  
    RLWECT *out_ptr = static_cast<RLWECT*>(out); 
    RLWECT *ct_ptr = static_cast<RLWECT*>(ct);
    ct_ptr->a.add(&out_ptr->a, &a);
    ct_ptr->b.add(&out_ptr->b, &b);  
}
  
void RLWECT::add(RLWECT *out, Polynomial *x){
    b.add(&out->b, x); 
}
 
void RLWECT::sub(VectorCT *out, VectorCT *ct){  
    RLWECT *out_ptr = static_cast<RLWECT*>(out);
    RLWECT *ct_ptr = static_cast<RLWECT*>(ct);
    a.sub(&out_ptr->a, &ct_ptr->a);
    b.sub(&out_ptr->b, &ct_ptr->b); 
}
  
void RLWECT::sub(RLWECT *out, Polynomial *x){
    b.sub(&out->b, x);  
}

void RLWECT::neg(VectorCT *out){
    RLWECT *out_ptr = static_cast<RLWECT*>(out); 
    a.neg(&out_ptr->a);
    b.neg(&out_ptr->b); 
}
  
void RLWECT::mul(RLWECT *out, Polynomial *x){ 
    this->a.mul(&out->a, x, param->mul_engine);
    this->b.mul(&out->b, x, param->mul_engine); 
}
 
std::string RLWECT::to_string(){
    std::string out = "[" + Utils::to_string(b.coefs, param->size) + ", " + Utils::to_string(a.coefs, param->size) + "]";
    return out;
}
  
void RLWECT::extract_lwe(long *lwe_ct_out){
    lwe_ct_out[0] = this->b.coefs[0];
    lwe_ct_out[1] = this->a.coefs[0];
    for(int i = 1; i < this->param->size; ++i){
        lwe_ct_out[i+1] = -this->a.coefs[this->param->size - i];
    } 
}

LWECT RLWECT::extract_lwe(std::shared_ptr<LWEParam> lwe_par){ 
    LWECT out(lwe_par);
    this->extract_lwe(out.ct);
    return out; 
}
     
RLWEParam::RLWEParam(RingType ring, int ring_degree, long coef_modulus, ModulusType mod_type, PolynomialArithmetic arithmetic){
    this->coef_modulus = coef_modulus;
    this->mod_type = mod_type; 
    this->size = ring_degree;  
    this->ring = ring;  
    this->arithmetic = arithmetic;   
    init_mul_engine();
}
        
RLWEParam::RLWEParam(int degree, long ring_degree, ModulusType mod_type, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine){
    this->size = ring_degree;
    this->coef_modulus = coef_modulus;
    this->mod_type = mod_type; 
    this->mul_engine = mul_engine; 
    this->arithmetic = mul_engine->type;
    this->is_mul_engine_init = true;
}

RLWEParam::RLWEParam(RLWEParam &other){ 
    throw std::runtime_error("RLWEParam::RLWEParam(RLWEParam &other)");
    /*
    this->coef_modulus = other.coef_modulus;
    this->mod_type = other.mod_type; 
    this->size = other.size;  
    this->ring = other.ring;  
    this->arithmetic = other.arithmetic;   
    init_mul_engine();
    */
}

RLWEParam& RLWEParam::operator=(const RLWEParam other){ 
    throw std::runtime_error("RLWEParam& RLWEParam::operator=(const RLWEParam other)");
    /*
    this->coef_modulus = other.coef_modulus;
    this->mod_type = other.mod_type;  
    this->size = other.size;  
    this->ring = other.ring;  
    this->arithmetic = other.arithmetic; 
    init_mul_engine();
    */
    return *this;
}

void RLWEParam::init_mul_engine(){ 
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

VectorCT* RLWEParam::init_ct(){
    return new RLWECT(std::shared_ptr<RLWEParam>(this));
}

Polynomial RLWEParam::init_poly(){ 
    return Polynomial(size, coef_modulus, mul_engine); 
}
 
Polynomial RLWEParam::init_zero_poly(){
    Polynomial out(this->size, coef_modulus, mul_engine);
    for(int i = 0; i < this->size; ++i){
        out.coefs[i] = 0;
    }
    return out;
}
 
RLWEGadgetCT::RLWEGadgetCT(std::shared_ptr<RLWEParam> rlwe_param, std::shared_ptr<Gadget> gadget, std::vector<RLWECT> &gadget_ct, std::vector<RLWECT> &gadget_ct_sk){
    this->rlwe_param = rlwe_param;
    this->gadget = gadget;
    this->init(gadget_ct, gadget_ct_sk);
}

void RLWEGadgetCT::init(std::vector<RLWECT> &gadget_ct, std::vector<RLWECT> &gadget_ct_sk){     
    PolynomialArrayCoefForm array_coef(rlwe_param->size,  
                                            rlwe_param->coef_modulus,  
                                            gadget->digits);  
 
    this->array_eval_a = PolynomialArrayEvalForm(rlwe_param->mul_engine, 
                                                gadget->digits);                                    
    this->array_eval_b = PolynomialArrayEvalForm(rlwe_param->mul_engine, 
                                                gadget->digits);
    this->array_eval_a_sk = PolynomialArrayEvalForm(rlwe_param->mul_engine, 
                                                gadget->digits);
    this->array_eval_b_sk = PolynomialArrayEvalForm(rlwe_param->mul_engine, 
                                                gadget->digits);
 
    for(int i = 0; i < gadget->digits; ++i){ 
        array_coef.set_polynomial_at(i, &gadget_ct[i].a);
    }  
    rlwe_param->mul_engine->to_eval(&array_eval_a, &array_coef);  
  
    for(int i = 0; i < gadget->digits; ++i){
        array_coef.set_polynomial_at(i, &gadget_ct[i].b);
    }
    rlwe_param->mul_engine->to_eval(&array_eval_b, &array_coef); 
  
    for(int i = 0; i < gadget->digits; ++i){
        array_coef.set_polynomial_at(i, &gadget_ct_sk[i].a);
    }
    rlwe_param->mul_engine->to_eval(&array_eval_a_sk, &array_coef);  
   
    for(int i = 0; i < gadget->digits; ++i){
        array_coef.set_polynomial_at(i, &gadget_ct_sk[i].b);
    }
    rlwe_param->mul_engine->to_eval(&array_eval_b_sk, &array_coef);  
 
    this->out_minus = RLWECT(rlwe_param); 
 
    init_gadget_decomp_tables();  
    set_gadget_decomp_arrays();
 
    this->is_init = true; 
}

RLWEGadgetCT::~RLWEGadgetCT(){     
    if(is_init == false){
        return;
    }       
    delete[] deter_ct_a_dec;
    delete[] deter_ct_b_dec;   
}
 
RLWEGadgetCT::RLWEGadgetCT(const RLWEGadgetCT& other){    
    throw std::runtime_error("RLWEGadgetCT::RLWEGadgetCT(const RLWEGadgetCT& other)");
}

RLWEGadgetCT& RLWEGadgetCT::operator=(RLWEGadgetCT other){  
    throw std::runtime_error("RLWEGadgetCT& RLWEGadgetCT::operator=(RLWEGadgetCT other)");
    return *this;
}
  
void RLWEGadgetCT::mul(VectorCT *out, const VectorCT *ct){
    RLWECT* out_ptr = static_cast<RLWECT*>(out);
    const RLWECT* ct_ptr = static_cast<const RLWECT*>(ct);
    gadget->sample(deter_ct_a_dec, ct_ptr->a.coefs); 
    /// TODO: Note that I may unintentionally compute twice as many FFT/NTTs her because I use deter_ct_a_dec_poly and deter_ct_b_dec_poly twice. 
    /// I should get the EvalForm of deter_ct_a_dec_poly and deter_ct_b_dec_poly, and then compute a inner product between them.
    rlwe_param->mul_engine->multisum(&out_minus.b, &deter_ct_a_dec_poly, &array_eval_b_sk);
    rlwe_param->mul_engine->multisum(&out_minus.a, &deter_ct_a_dec_poly, &array_eval_a_sk);  
    gadget->sample(deter_ct_b_dec, ct_ptr->b.coefs);  
    rlwe_param->mul_engine->multisum(&out_ptr->b, &deter_ct_b_dec_poly, &array_eval_b);
    rlwe_param->mul_engine->multisum(&out_ptr->a, &deter_ct_b_dec_poly, &array_eval_a);
    out->add(out, &out_minus); 
}
  
void RLWEGadgetCT::init_gadget_decomp_tables(){
    // Set up also precomputed arrays for gadget decomposition   
    deter_ct_a_dec = new long*[gadget->digits];
    deter_ct_b_dec = new long*[gadget->digits]; 
}

void RLWEGadgetCT::set_gadget_decomp_arrays(){  
    deter_ct_a_dec_poly = PolynomialArrayCoefForm(rlwe_param->size, rlwe_param->coef_modulus, gadget->digits);
    deter_ct_b_dec_poly = PolynomialArrayCoefForm(rlwe_param->size, rlwe_param->coef_modulus, gadget->digits); 
    // Point the polynomials to the long tables. 
    for(int i = 0; i < gadget->digits; ++i){ 
        deter_ct_a_dec[i] = &deter_ct_a_dec_poly.poly_array[i * deter_ct_a_dec_poly.degree]; 
        deter_ct_b_dec[i] = &deter_ct_b_dec_poly.poly_array[i * deter_ct_b_dec_poly.degree]; 
    } 
}
 
RLWESK::RLWESK(std::shared_ptr<RLWEParam> param, KeyDistribution key_type, double noise_stddev){ 
    this->param = param;
    this->key_type = key_type;
    this->noise_stddev = noise_stddev;
    this->unif_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, param->coef_modulus));
    this->error_dist = std::shared_ptr<Distribution>(new StandardRoundedGaussianDistribution(0, noise_stddev));
    if(key_type == uniform){ 
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, param->coef_modulus));
    }else if(key_type == ternary){ 
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(-1, 1));
    }else if(key_type == binary){ 
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, 1));
    }  
    this->sk = Polynomial(param->size, param->coef_modulus, param->mul_engine);  
    sk_dist->fill_array(this->sk.coefs, param->size);   
    this->sk.to_eval();   
}

RLWESK::RLWESK(const RLWESK &other){
    throw std::runtime_error("RLWESK::RLWESK(const RLWESK &other): Don't copy the secret key!"); 
}

RLWESK& RLWESK::operator=(const RLWESK other){  
    throw std::runtime_error("RLWESK::operator=(const RLWESK other): Don't copy the secret key!"); 
    return *this;
}
  
void RLWESK::encrypt(RLWECT *out, Polynomial *m){  
    if(m->degree < param->size){
        throw std::logic_error("RLWESK::encrypt(Polynomial *m): Input polynomial m, degree is too big!");
    }
    if(m->coef_modulus < param->coef_modulus){
        throw std::logic_error("RLWESK::encrypt(Polynomial *m): Input polynomial m, coefficient codulus is too big!");
    }
    if(!m->is_init){
        throw std::logic_error("RLWESK::encrypt(Polynomial *m): Input polynomial m is not initialized!");
    } 
    unif_dist->fill_array(out->a.coefs, param->size); 
    Polynomial noise(param->size, param->coef_modulus);
    error_dist->fill_array(noise.coefs, param->size); 
    Polynomial message(param->size, param->coef_modulus);
    Utils::cp(message.coefs, m->coefs, param->size); 
    // Now just need to compute: b = a * s + e + m
    // First we need a poolynomial s in eval form.   
    out->a.mul(&out->b, &sk, param->mul_engine);
    out->b.add(&out->b, &noise);
    out->b.add(&out->b, &message);  
}

RLWECT RLWESK::encrypt(Polynomial *m){   
    RLWECT out(param);  
    this->encrypt(&out, m);
    return out;
}
 
RLWECT RLWESK::encode_and_encrypt(Polynomial* m, PlaintextEncoding encoding){
    Polynomial m_scaled(param->size, param->coef_modulus); 
    for(int i = 0; i < param->size; ++i){ 
        m_scaled.coefs[i] = encoding.encode_message(m->coefs[i]);
    }
    RLWECT out = encrypt(&m_scaled); 
    return out;
}

void RLWESK::partial_decrypt(Polynomial *phase, RLWECT *ct){   
    if(phase->degree != param->size){
        throw std::logic_error("RLWESK::phase(Polynomial *phase, RLWECT *ct): Dimension of the input polynomial differs from the the RLWE polynomials.");
    }
    if(phase->coef_modulus != param->coef_modulus){
        throw std::logic_error("RLWESK::phase(Polynomial *phase, RLWECT *ct): Coefficient modulus of the input polynomial differs from the the RLWE polynomials.");
    }
    if(!phase->is_init){
        throw std::logic_error("RLWESK::phase(Polynomial *phase, RLWECT *ct): Input polynomial is not initialized.");
    } 
    ct->a.mul(phase, &sk); 
    ct->b.sub(phase, phase); 
}
  
Polynomial RLWESK::decrypt(RLWECT *ct, PlaintextEncoding encoding){
    Polynomial out(param->size, param->coef_modulus);
    decrypt(&out, ct, encoding);  
    return out;
}
 
void RLWESK::decrypt(Polynomial *out, RLWECT *ct, PlaintextEncoding encoding){
    this->partial_decrypt(out, ct);  
    for(int i = 0; i < out->degree; ++i){
        out->coefs[i] = encoding.decode_message(out->coefs[i]);
    } 
}

void RLWESK::extract_lwe_key(long* lwe_key){  
    for(int i = 0; i <  param->size; ++i){ 
        lwe_key[i] = -this->sk.coefs[i]; 
    } 
}

LWESK* RLWESK::extract_lwe_key(){
    long* extract_key = new long[param->size]; 
    std::shared_ptr<LWEParam> lwe_param = std::shared_ptr<LWEParam>(new LWEParam(param->size, param->coef_modulus));
    for(int i = 0; i <  param->size; ++i){ 
        extract_key[i] = -this->sk.coefs[i]; 
    } 
    LWESK* key = new LWESK(lwe_param, extract_key, this->noise_stddev, this->key_type);
    delete[] extract_key;
    return key;
}
 
RLWEGadgetSK::RLWEGadgetSK(std::shared_ptr<Gadget> gadget, std::shared_ptr<RLWESK> sk){ 
    this->gadget = gadget; 
    this->vector_ct_param = sk->param;
    this->sk = sk; 
}

RLWEGadgetSK& RLWEGadgetSK::operator=(const RLWEGadgetSK other){  
    throw std::runtime_error("RLWEGadgetSK::operator=(const RLWEGadgetSK other): Don't copy the secret key!");
    return *this;
}
 
RLWEGadgetSK::RLWEGadgetSK(const RLWEGadgetSK &other){ 
    throw std::runtime_error("RLWEGadgetSK::RLWEGadgetSK(const RLWEGadgetSK &other): Don't copy the secret key!");  
}
  
GadgetVectorCT* RLWEGadgetSK::gadget_encrypt(Polynomial *msg){     
    std::vector<RLWECT> gadget_ct; 
    std::vector<RLWECT> gadget_ct_sk;    
    Polynomial msg_x_sk(sk->param->size, sk->param->coef_modulus); 
    int digits = gadget->digits;
    long base = gadget->base; 
    // Multiply msg with sk.s. Result is in msg_x_sk 
    msg->mul(&msg_x_sk, &sk->sk, sk->param->mul_engine);
    msg_x_sk.neg(&msg_x_sk); 
    // Encryptions of - msg* base**i    
    gadget_ct.push_back(sk->encrypt(msg));
    for(int i = 1; i < digits; ++i){
        // Multiply msg by base
        msg->mul(msg, base); 
        // Encrypt msg * base**i   
        gadget_ct.push_back(sk->encrypt(msg)); 
    }  
    // Encryptions of - msg * sk * base**i    
    gadget_ct_sk.push_back(sk->encrypt(&msg_x_sk));
    for(int i = 1; i < digits; ++i){ 
        // Multiply msg by base
        msg_x_sk.mul(&msg_x_sk, base); 
        // Encrypt - msg * sk * base**i   
        gadget_ct_sk.push_back(sk->encrypt(&msg_x_sk));  
    }     
    return new RLWEGadgetCT(sk->param, gadget, gadget_ct, gadget_ct_sk);
}


GadgetVectorCT* RLWEGadgetSK::gadget_encrypt(long *msg, int size){
    if(size > sk->param->size){
        throw std::logic_error("GadgetVectorCT* RLWEGadgetSK::gadget_encrypt(long *msg, int size): size of the message array too big.");
    }
    Polynomial msg_poly(sk->param->size, sk->param->coef_modulus); 
    msg_poly.zeroize();
    for(int i = 0; i < size; ++i){
        msg_poly.coefs[i] = msg[i];
    }
    return gadget_encrypt(&msg_poly);
}