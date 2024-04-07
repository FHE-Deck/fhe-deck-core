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
    a.negacyclic_rotate(&out->a, rot);
    b.negacyclic_rotate(&out->b, rot); 
}
 
void RLWECT::add(RLWECT *out, RLWECT *ct){ 
    ct->a.add(&out->a, &a);
    ct->b.add(&out->b, &b);  
}
  
void RLWECT::add(RLWECT *out, Polynomial *x){
    b.add(&out->b, x); 
}
 
void RLWECT::sub(RLWECT *out, RLWECT *ct){  
    a.sub(&out->a, &ct->a);
    b.sub(&out->b, &ct->b); 
}
  
void RLWECT::sub(RLWECT *out, Polynomial *x){
    b.sub(&out->b, x);  
}

void RLWECT::neg(RLWECT *out){ 
    a.neg(&out->a);
    b.neg(&out->b); 
}
  
void RLWECT::mul(RLWECT *out, Polynomial *x){ 
    this->a.mul(&out->a, x, param->mul_engine);
    this->b.mul(&out->b, x, param->mul_engine); 
}
 
std::string RLWECT::to_string(){
    std::string out = "[" + Utils::to_string(b.coefs, param->degree) + ", " + Utils::to_string(a.coefs, param->degree) + "]";
    return out;
}
  
 
   
void RLWECT::extract_lwe(long *lwe_ct_out){
    lwe_ct_out[0] = this->b.coefs[0];
    lwe_ct_out[1] = this->a.coefs[0];
    for(int i = 1; i < this->param->degree; ++i){
        lwe_ct_out[i+1] = -this->a.coefs[this->param->degree - i];
    } 
}

LWECT RLWECT::extract_lwe(std::shared_ptr<LWEParam> lwe_par){ 
    LWECT out(lwe_par);
    this->extract_lwe(out.ct);
    return out; 
}
     
RLWEParam::RLWEParam(RingType ring, int degree, long coef_modulus, KeyDistribution key_type, ModulusType mod_type, double stddev, PolynomialArithmetic arithmetic){
    this->coef_modulus = coef_modulus;
    this->mod_type = mod_type;
    this->key_type = key_type; 
    this->degree = degree; 
    this->stddev = stddev; 
    this->ring = ring;  
    this->arithmetic = arithmetic;   
    init_mul_engine();
}
        
RLWEParam::RLWEParam(int degree, long coef_modulus, KeyDistribution key_type, ModulusType mod_type, double stddev, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine){
    this->degree = degree;
    this->coef_modulus = coef_modulus;
    this->mod_type = mod_type;
    this->key_type = key_type;  
    this->stddev = stddev; 
    this->mul_engine = mul_engine; 
    this->is_mul_engine_init = true;
}

RLWEParam::RLWEParam(RLWEParam &other){ 
    this->coef_modulus = other.coef_modulus;
    this->mod_type = other.mod_type;
    this->key_type = other.key_type;  
    this->degree = other.degree; 
    this->stddev = other.stddev; 
    this->ring = other.ring;  
    this->arithmetic = other.arithmetic;   
    init_mul_engine();
}

RLWEParam& RLWEParam::operator=(const RLWEParam other){ 
    this->coef_modulus = other.coef_modulus;
    this->mod_type = other.mod_type;
    this->key_type = other.key_type;  
    this->degree = other.degree; 
    this->stddev = other.stddev; 
    this->ring = other.ring;  
    this->arithmetic = other.arithmetic; 
    init_mul_engine();
    return *this;
}

void RLWEParam::init_mul_engine(){ 
    // Build PolynomialMultiplicationEngine
    PolynomialMultiplicationEngineBuilder mul_engine_builder;
    mul_engine_builder.set_coef_modulus(coef_modulus); 
    mul_engine_builder.set_degree(degree);
    mul_engine_builder.set_polynomial_arithmetic(arithmetic);
    mul_engine_builder.set_ring_type(ring);
    mul_engine_builder.set_modulus_type(mod_type);
    this->mul_engine = mul_engine_builder.build(); 
    this->is_mul_engine_init = true;
}

Polynomial RLWEParam::init_poly(){ 
    return Polynomial(degree, coef_modulus, mul_engine); 
}
 
Polynomial RLWEParam::init_zero_poly(){
    Polynomial out(degree, coef_modulus, mul_engine);
    for(int i = 0; i < this->degree; ++i){
        out.coefs[i] = 0;
    }
    return out;
}
 
RLWEGadgetCT::RLWEGadgetCT(std::shared_ptr<RLWEGadgetParam> gadget_param, std::vector<RLWECT> &gadget_ct, std::vector<RLWECT> &gadget_ct_sk){
    this->gadget_param = gadget_param;   
    this->init(gadget_ct, gadget_ct_sk);
}

void RLWEGadgetCT::init(std::vector<RLWECT> &gadget_ct, std::vector<RLWECT> &gadget_ct_sk){     
    PolynomialArrayCoefForm array_coef(gadget_param->rlwe_param->degree,  
                                            gadget_param->rlwe_param->coef_modulus,  
                                            gadget_param->deter_gadget->digits);  
 
    this->array_eval_a = PolynomialArrayEvalForm(gadget_param->rlwe_param->mul_engine, 
                                                gadget_param->deter_gadget->digits);                                    
    this->array_eval_b = PolynomialArrayEvalForm(gadget_param->rlwe_param->mul_engine, 
                                                gadget_param->deter_gadget->digits);
    this->array_eval_a_sk = PolynomialArrayEvalForm(gadget_param->rlwe_param->mul_engine, 
                                                gadget_param->deter_gadget->digits);
    this->array_eval_b_sk = PolynomialArrayEvalForm(gadget_param->rlwe_param->mul_engine, 
                                                gadget_param->deter_gadget->digits);
 
    for(int i = 0; i < gadget_param->deter_gadget->digits; ++i){ 
        array_coef.set_polynomial_at(i, &gadget_ct[i].a);
    }  
    gadget_param->rlwe_param->mul_engine->to_eval(&array_eval_a, &array_coef);  
  
    for(int i = 0; i < gadget_param->deter_gadget->digits; ++i){
        array_coef.set_polynomial_at(i, &gadget_ct[i].b);
    }
    gadget_param->rlwe_param->mul_engine->to_eval(&array_eval_b, &array_coef); 
  
    for(int i = 0; i < gadget_param->deter_gadget->digits; ++i){
        array_coef.set_polynomial_at(i, &gadget_ct_sk[i].a);
    }
    gadget_param->rlwe_param->mul_engine->to_eval(&array_eval_a_sk, &array_coef);  
   
    for(int i = 0; i < gadget_param->deter_gadget->digits; ++i){
        array_coef.set_polynomial_at(i, &gadget_ct_sk[i].b);
    }
    gadget_param->rlwe_param->mul_engine->to_eval(&array_eval_b_sk, &array_coef);  
 
    this->out_minus = RLWECT(gadget_param->rlwe_param); 
 
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
    this->gadget_param = other.gadget_param; 
    out_minus = RLWECT(gadget_param->rlwe_param);  
    this->deter_ct_a_dec_poly = other.deter_ct_a_dec_poly;
    this->deter_ct_b_dec_poly = other.deter_ct_b_dec_poly;
    if(!is_init){ 
        init_gadget_decomp_tables(); 
        set_gadget_decomp_arrays(); 
        this->is_init = true; 
    } 
}

RLWEGadgetCT& RLWEGadgetCT::operator=(RLWEGadgetCT other){  
    this->gadget_param = other.gadget_param; 
    out_minus = RLWECT(gadget_param->rlwe_param);  
    this->array_eval_a = other.array_eval_a;
    this->array_eval_b = other.array_eval_b;
    this->array_eval_a_sk = other.array_eval_a_sk;
    this->array_eval_b_sk = other.array_eval_b_sk;  
    if(!is_init){ 
        init_gadget_decomp_tables(); 
        set_gadget_decomp_arrays(); 
        this->is_init = true; 
    }  
    return *this;
}
  
void RLWEGadgetCT::mul(RLWECT *out, const RLWECT *ct){
    gadget_param->deter_gadget->sample(deter_ct_a_dec, ct->a.coefs); 
    gadget_param->deter_gadget->sample(deter_ct_b_dec, ct->b.coefs); 
    gadget_param->rlwe_param->mul_engine->multisum(&out_minus.b, &deter_ct_a_dec_poly, &array_eval_b_sk);
    gadget_param->rlwe_param->mul_engine->multisum(&out_minus.a, &deter_ct_a_dec_poly, &array_eval_a_sk);   
    gadget_param->rlwe_param->mul_engine->multisum(&out->b, &deter_ct_b_dec_poly, &array_eval_b);
    gadget_param->rlwe_param->mul_engine->multisum(&out->a, &deter_ct_b_dec_poly, &array_eval_a);
    out->add(out, &out_minus); 
}
  
void RLWEGadgetCT::init_gadget_decomp_tables(){
    // Set up also precomputed arrays for gadget decomposition   
    deter_ct_a_dec = new long*[gadget_param->deter_gadget->digits];
    deter_ct_b_dec = new long*[gadget_param->deter_gadget->digits]; 
}

void RLWEGadgetCT::set_gadget_decomp_arrays(){  
    deter_ct_a_dec_poly = PolynomialArrayCoefForm(gadget_param->rlwe_param->degree, gadget_param->rlwe_param->coef_modulus, gadget_param->deter_gadget->digits);
    deter_ct_b_dec_poly = PolynomialArrayCoefForm(gadget_param->rlwe_param->degree, gadget_param->rlwe_param->coef_modulus, gadget_param->deter_gadget->digits); 
    // Point the polynomials to the long tables. 
    for(int i = 0; i < gadget_param->deter_gadget->digits; ++i){ 
        deter_ct_a_dec[i] = &deter_ct_a_dec_poly.poly_array[i * deter_ct_a_dec_poly.degree]; 
        deter_ct_b_dec[i] = &deter_ct_b_dec_poly.poly_array[i * deter_ct_b_dec_poly.degree]; 
    } 
}
 
RLWEGadgetParam::RLWEGadgetParam(std::shared_ptr<RLWEParam> rlwe_param, int basis, std::shared_ptr<Gadget> deter_gadget){  
    this->rlwe_param = rlwe_param;  
    this->deter_gadget = deter_gadget;  
}

RLWEGadgetParam::RLWEGadgetParam(const RLWEGadgetParam &other){
    this->rlwe_param = other.rlwe_param; 
    this->deter_gadget = other.deter_gadget;  
}

RLWEGadgetParam& RLWEGadgetParam::operator=(const RLWEGadgetParam other){
    if (this == &other)
    {
        return *this;
    } 
    this->rlwe_param = other.rlwe_param; 
    this->deter_gadget = other.deter_gadget;  
    return *this;
}
    
RLWESK::RLWESK(std::shared_ptr<RLWEParam> param){ 
    this->param = param;
    this->unif_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, param->coef_modulus));
    this->error_dist = std::shared_ptr<Distribution>(new StandardRoundedGaussianDistribution(0, param->stddev));
    if(param->key_type == uniform){ 
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, param->coef_modulus));
    }else if(param->key_type == ternary){ 
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(-1, 1));
    }else if(param->key_type == binary){ 
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, 1));
    }  
    this->sk = Polynomial(param->degree, param->coef_modulus, param->mul_engine);  
    sk_dist->fill_array(this->sk.coefs, param->degree);   
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
    if(m->degree < param->degree){
        throw std::logic_error("RLWESK::encrypt(Polynomial *m): Input polynomial m, degree is too big!");
    }
    if(m->coef_modulus < param->coef_modulus){
        throw std::logic_error("RLWESK::encrypt(Polynomial *m): Input polynomial m, coefficient codulus is too big!");
    }
    if(!m->is_init){
        throw std::logic_error("RLWESK::encrypt(Polynomial *m): Input polynomial m is not initialized!");
    } 
    unif_dist->fill_array(out->a.coefs, param->degree); 
    Polynomial noise(param->degree, param->coef_modulus);
    error_dist->fill_array(noise.coefs, param->degree); 
    Polynomial message(param->degree, param->coef_modulus);
    Utils::cp(message.coefs, m->coefs, param->degree); 
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

RLWECT RLWESK::scale_and_encrypt(Polynomial* m, int t){ 
    // TODO: Potential problem if Q is too big. The scale may require to be a long double.
    double scale = (double)param->coef_modulus/t;
    Polynomial m_scaled(param->degree, param->coef_modulus); 
    for(int i = 0; i < param->degree; ++i){ 
        m_scaled.coefs[i] = (long)round((double)m->coefs[i]*scale);
    }
    RLWECT out = encrypt(&m_scaled); 
    return out;
}

void RLWESK::phase(Polynomial *phase, RLWECT *ct){   
    if(phase->degree != param->degree){
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

// Uses SK
Polynomial RLWESK::decrypt(RLWECT *ct, int t){ 
    Polynomial out(param->degree, param->coef_modulus);
    decrypt(&out, ct, t);  
    return out;
}

// Uses SK
void RLWESK::decrypt(Polynomial *out, RLWECT *ct, int t){   
    this->phase(out, ct);  
    Utils::array_rounding(out->coefs, out->coefs, param->degree, param->coef_modulus, t);  
}

void RLWESK::extract_lwe_key(long* lwe_key){  
    for(int i = 0; i <  param->degree; ++i){ 
        lwe_key[i] = -this->sk.coefs[i]; 
    } 
}

RLWEGadgetSK::RLWEGadgetSK(std::shared_ptr<RLWEGadgetParam> gadget_param, std::shared_ptr<RLWESK> sk){ 
    this->gadget_param = gadget_param; 
    this->sk = sk; 
}

RLWEGadgetSK& RLWEGadgetSK::operator=(const RLWEGadgetSK other){  
    throw std::runtime_error("RLWEGadgetSK::operator=(const RLWEGadgetSK other): Don't copy the secret key!");
    return *this;
}
 
RLWEGadgetSK::RLWEGadgetSK(const RLWEGadgetSK &other){ 
    throw std::runtime_error("RLWEGadgetSK::RLWEGadgetSK(const RLWEGadgetSK &other): Don't copy the secret key!");  
}

RLWEGadgetCT RLWEGadgetSK::gadget_encrypt(long* msg){     
    std::vector<RLWECT> gadget_ct; 
    std::vector<RLWECT> gadget_ct_sk;  
    Polynomial msg_cpy(gadget_param->rlwe_param->degree, gadget_param->rlwe_param->coef_modulus); 
    for(int i = 0; i < gadget_param->rlwe_param->degree; ++i){ 
        msg_cpy.coefs[i] = msg[i]; 
    }   
    Polynomial msg_x_sk(gadget_param->rlwe_param->degree, gadget_param->rlwe_param->coef_modulus); 
    int digits = gadget_param->deter_gadget->digits;
    long base = gadget_param->deter_gadget->base; 
    // Multiply msg with sk.s. Result is in msg_x_sk 
    msg_cpy.mul(&msg_x_sk, &sk->sk, gadget_param->rlwe_param->mul_engine);
    msg_x_sk.neg(&msg_x_sk); 
    // Encryptions of - msg* base**i    
    gadget_ct.push_back(sk->encrypt(&msg_cpy));
    for(int i = 1; i < digits; ++i){
        // Multiply msg by base
        msg_cpy.mul(&msg_cpy, base); 
        // Encrypt msg * base**i   
        gadget_ct.push_back(sk->encrypt(&msg_cpy)); 
    }  
    // Encryptions of - msg * sk * base**i    
    gadget_ct_sk.push_back(sk->encrypt(&msg_x_sk));
    for(int i = 1; i < digits; ++i){ 
        // Multiply msg by base
        msg_x_sk.mul(&msg_x_sk, base); 
        // Encrypt - msg * sk * base**i   
        gadget_ct_sk.push_back(sk->encrypt(&msg_x_sk));  
    }    
    RLWEGadgetCT out(gadget_param, gadget_ct, gadget_ct_sk);   
    return out; 
}
 
