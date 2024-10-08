#include "rlwe.h"

using namespace fhe_deck;

RLWECT::RLWECT(std::shared_ptr<RLWEParam> param){
    this->param = param;   
    this->a = Polynomial(param->size, param->coef_modulus); 
    this->b = Polynomial(param->size, param->coef_modulus);   
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
  
void RLWECT::negacyclic_rotate(RLWECT &out, int32_t rot){  
    //RLWECT &out_ptr = static_cast<RLWECT&>(out); 
    a.negacyclic_rotate(out.a, rot);
    b.negacyclic_rotate(out.b, rot); 
}

void RLWECT::cyclic_rotate(RLWECT &out, int32_t rot){  
    //RLWECT &out_ptr = static_cast<RLWECT&>(out); 
    a.cyclic_rotate(out.a, rot);
    b.cyclic_rotate(out.b, rot); 
}

void RLWECT::homomorphic_rotate(VectorCT &out, int32_t rot){ 
    // What we do here, is realy multiplication with a monomial.
    if(this->param->ring == negacyclic){ 
        negacyclic_rotate(static_cast<RLWECT&>(out), rot);
    }else if(this->param->ring == cyclic){
        cyclic_rotate(static_cast<RLWECT&>(out), rot);
    }else{
        throw std::logic_error("RLWECT::homomorphic_rotate(VectorCT *out, int32_t rot): this->param->ring currently not supported.");
    }
}
 
void RLWECT::add(VectorCT& out, const VectorCT &ct){  
    RLWECT &out_ptr = static_cast<RLWECT&>(out); 
    const RLWECT &ct_ptr = static_cast<const RLWECT&>(ct);
    ct_ptr.a.add(out_ptr.a, a);
    ct_ptr.b.add(out_ptr.b, b);  
}
  
void RLWECT::add(RLWECT &out, const Polynomial &x){
    b.add(out.b, x); 
}
 
void RLWECT::sub(VectorCT &out, const VectorCT &ct){  
    RLWECT &out_ptr = static_cast<RLWECT&>(out);
    const RLWECT &ct_ptr = static_cast<const RLWECT&>(ct);
    a.sub(out_ptr.a, ct_ptr.a);
    b.sub(out_ptr.b, ct_ptr.b); 
}
  
void RLWECT::sub(RLWECT &out, const Polynomial &x){
    b.sub(out.b, x);  
}

void RLWECT::neg(VectorCT &out){
    RLWECT &out_ptr = static_cast<RLWECT&>(out); 
    a.neg(out_ptr.a);
    b.neg(out_ptr.b); 
}
  
void RLWECT::mul(RLWECT &out, const Polynomial &x){ 
    this->a.mul(out.a, x, param->mul_engine);
    this->b.mul(out.b, x, param->mul_engine); 
}

void RLWECT::mul(RLWECT &out, int64_t x){ 
    this->a.mul(out.a, x);
    this->b.mul(out.b, x); 
}
 
std::string RLWECT::to_string(){
    std::string out = "[" + Utils::to_string(b.coefs, param->size) + ", " + Utils::to_string(a.coefs, param->size) + "]";
    return out;
}
 
void RLWECT::extract_lwe(LWECT &lwe_ct_out){
    lwe_ct_out.ct[0] = this->b.coefs[0];
    lwe_ct_out.ct[1] = this->a.coefs[0];
    for(int32_t i = 1; i < this->param->size; ++i){
        lwe_ct_out.ct[i+1] = -this->a.coefs[this->param->size - i];
    } 
}

void RLWECT::extract_lwe(LWECT &lwe_ct_out, uint32_t position){ 
    RLWECT tmp(*this);
    tmp.negacyclic_rotate(tmp, (a.degree - position) % a.degree);
    tmp.neg(tmp); 
    tmp.extract_lwe(lwe_ct_out);
}

  
RLWEParam::RLWEParam(RingType ring, int32_t ring_degree, uint64_t coef_modulus,  PolynomialArithmetic arithmetic){
    this->coef_modulus = coef_modulus; 
    this->size = ring_degree;  
    this->ring = ring;  
    this->arithmetic = arithmetic;   
    init_mul_engine();
}
        
RLWEParam::RLWEParam(int32_t degree, uint64_t ring_degree,  std::shared_ptr<PolynomialMultiplicationEngine> mul_engine){
    this->size = ring_degree;
    this->coef_modulus = coef_modulus; 
    this->mul_engine = mul_engine; 
    this->arithmetic = mul_engine->type; 
}
 
RLWEParam::RLWEParam(RLWEParam &other){ 
    throw std::runtime_error("RLWEParam::RLWEParam(RLWEParam &other)"); 
}

RLWEParam& RLWEParam::operator=(const RLWEParam other){ 
    throw std::runtime_error("RLWEParam& RLWEParam::operator=(const RLWEParam other)"); 
    return *this;
}

void RLWEParam::init_mul_engine(){  
    // Build PolynomialMultiplicationEngine
    PolynomialMultiplicationEngineBuilder mul_engine_builder;
    mul_engine_builder.set_coef_modulus(coef_modulus); 
    mul_engine_builder.set_degree(size);
    mul_engine_builder.set_polynomial_arithmetic(arithmetic);
    mul_engine_builder.set_ring_type(ring); 
    this->mul_engine = mul_engine_builder.build();  
}
 
VectorCT* RLWEParam::init_ct(std::shared_ptr<VectorCTParam> param){ 
    return new RLWECT(std::static_pointer_cast<RLWEParam>(param));
}
 
ExtendedRLWECT::ExtendedRLWECT(std::shared_ptr<RLWEParam> rlwe_param, std::shared_ptr<Gadget> gadget, std::vector<std::unique_ptr<RLWECT>> &gadget_ct){
    this->rlwe_param = rlwe_param;
    this->gadget = gadget;
    this->init(gadget_ct);
}

void ExtendedRLWECT::init(std::vector<std::unique_ptr<RLWECT>> &gadget_ct){     
    PolynomialArrayCoefForm array_coef(rlwe_param->size,  
                                            rlwe_param->coef_modulus,  
                                            gadget->digits);  
  
    this->array_eval_a = std::unique_ptr<PolynomialArrayEvalForm>(rlwe_param->mul_engine->init_polynomial_array_eval_form(gadget->digits));                             
    this->array_eval_b = std::unique_ptr<PolynomialArrayEvalForm>(rlwe_param->mul_engine->init_polynomial_array_eval_form(gadget->digits));    
 
    for(int32_t i = 0; i < gadget->digits; ++i){ 
        array_coef.set_polynomial_at(i, gadget_ct[i]->a);
    }  
     
    rlwe_param->mul_engine->to_eval(*array_eval_a.get(), array_coef);  
  
    for(int32_t i = 0; i < gadget->digits; ++i){
        array_coef.set_polynomial_at(i, gadget_ct[i]->b);
    } 
    rlwe_param->mul_engine->to_eval(*array_eval_b.get(), array_coef); 
      
    this->is_init = true;  
}

ExtendedRLWECT::~ExtendedRLWECT(){     
    if(is_init == false){
        return;
    }         
}
   
void ExtendedRLWECT::mul(VectorCT &out, const Polynomial &ct){ 
    RLWECT& out_ptr = static_cast<RLWECT&>(out);    
    std::shared_ptr<PolynomialArrayEvalForm> poly_decomp_eval_form = std::shared_ptr<PolynomialArrayEvalForm>(rlwe_param->mul_engine->init_polynomial_array_eval_form(gadget->digits));  
    PolynomialArrayCoefForm poly_decomp_coef_form(rlwe_param->size, rlwe_param->coef_modulus, gadget->digits);
    gadget->sample(poly_decomp_coef_form, ct.coefs);   
    rlwe_param->mul_engine->multisum(out_ptr.b, *poly_decomp_eval_form.get(), poly_decomp_coef_form, *array_eval_b.get());  
    rlwe_param->mul_engine->multisum(out_ptr.a, *poly_decomp_eval_form.get(), *array_eval_a.get());  
}
   
RLWEGadgetCT::RLWEGadgetCT(std::shared_ptr<RLWEParam> rlwe_param, std::shared_ptr<Gadget> gadget, std::vector<std::unique_ptr<RLWECT>> &gadget_ct, std::vector<std::unique_ptr<RLWECT>> &gadget_ct_sk){
    this->rlwe_param = rlwe_param;
    this->gadget = gadget;
    this->init(gadget_ct, gadget_ct_sk);
}

void RLWEGadgetCT::init(std::vector<std::unique_ptr<RLWECT>> &gadget_ct, std::vector<std::unique_ptr<RLWECT>> &gadget_ct_sk){     
    PolynomialArrayCoefForm array_coef(rlwe_param->size,  
                                            rlwe_param->coef_modulus,  
                                            gadget->digits);  
  
    this->array_eval_a = std::unique_ptr<PolynomialArrayEvalForm>(rlwe_param->mul_engine->init_polynomial_array_eval_form(gadget->digits));                             
    this->array_eval_b = std::unique_ptr<PolynomialArrayEvalForm>(rlwe_param->mul_engine->init_polynomial_array_eval_form(gadget->digits));   
    this->array_eval_a_sk = std::unique_ptr<PolynomialArrayEvalForm>(rlwe_param->mul_engine->init_polynomial_array_eval_form(gadget->digits));    
    this->array_eval_b_sk = std::unique_ptr<PolynomialArrayEvalForm>(rlwe_param->mul_engine->init_polynomial_array_eval_form(gadget->digits));  
 
    for(int32_t i = 0; i < gadget->digits; ++i){ 
        array_coef.set_polynomial_at(i, gadget_ct[i]->a);
    }  
     
    rlwe_param->mul_engine->to_eval(*array_eval_a.get(), array_coef);  
  
    for(int32_t i = 0; i < gadget->digits; ++i){
        array_coef.set_polynomial_at(i, gadget_ct[i]->b);
    } 
    rlwe_param->mul_engine->to_eval(*array_eval_b.get(), array_coef); 
  
    for(int32_t i = 0; i < gadget->digits; ++i){
        array_coef.set_polynomial_at(i, gadget_ct_sk[i]->a);
    } 
    rlwe_param->mul_engine->to_eval(*array_eval_a_sk.get(), array_coef);  
   
    for(int32_t i = 0; i < gadget->digits; ++i){
        array_coef.set_polynomial_at(i, gadget_ct_sk[i]->b);
    } 
    rlwe_param->mul_engine->to_eval(*array_eval_b_sk.get(), array_coef);  
    
    this->is_init = true;  
}
 
RLWEGadgetCT::RLWEGadgetCT(const RLWEGadgetCT& other){    
    throw std::runtime_error("RLWEGadgetCT::RLWEGadgetCT(const RLWEGadgetCT& other)");
}

RLWEGadgetCT& RLWEGadgetCT::operator=(RLWEGadgetCT other){  
    throw std::runtime_error("RLWEGadgetCT& RLWEGadgetCT::operator=(RLWEGadgetCT other)");
    return *this;
}
  
void RLWEGadgetCT::mul(VectorCT &out, const VectorCT &ct){ 
    RLWECT& out_ptr = static_cast<RLWECT&>(out);
    const RLWECT& ct_ptr = static_cast<const RLWECT&>(ct); 
    PolynomialArrayCoefForm poly_decomp_coef_form(rlwe_param->size, rlwe_param->coef_modulus, gadget->digits);
    gadget->sample(poly_decomp_coef_form, ct_ptr.a.coefs);   
    RLWECT out_minus(rlwe_param); 
    std::shared_ptr<PolynomialArrayEvalForm> poly_decomp_eval_form(rlwe_param->mul_engine->init_polynomial_array_eval_form(gadget->digits));
    rlwe_param->mul_engine->multisum(out_minus.b, *poly_decomp_eval_form.get(), poly_decomp_coef_form, *array_eval_b_sk.get());  
    rlwe_param->mul_engine->multisum(out_minus.a, *poly_decomp_eval_form.get(), *array_eval_a_sk.get());  
   
    gadget->sample(poly_decomp_coef_form, ct_ptr.b.coefs);  
    rlwe_param->mul_engine->multisum(out_ptr.b, *poly_decomp_eval_form.get(), poly_decomp_coef_form, *array_eval_b.get());  
    rlwe_param->mul_engine->multisum(out_ptr.a, *poly_decomp_eval_form.get(), *array_eval_a.get()); 
    out.add(out, out_minus);  
}
   
RLWESK::RLWESK(std::shared_ptr<RLWEParam> param, KeyDistribution key_type, double noise_stddev){ 
    this->param = param;
    this->key_type = key_type;
    this->noise_stddev = noise_stddev;
    init();
    key_gen(); 
}

void RLWESK::init(){ 
    this->unif_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, param->coef_modulus));
    this->error_dist = std::shared_ptr<Distribution>(new StandardRoundedGaussianDistribution(0, noise_stddev));
}

void RLWESK::key_gen(){
    this->sk_poly = Polynomial(param->size, param->coef_modulus);  
    std::shared_ptr<Distribution> sk_dist;
    if(key_type == uniform){ 
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, param->coef_modulus));
    }else if(key_type == ternary){ 
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(-1, 1));
    }else if(key_type == binary){ 
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, 1));
    }  
    sk_dist->fill_array(this->sk_poly.coefs, param->size);   
    Utils::array_mod_form(this->sk_poly.coefs, this->sk_poly.coefs, param->size, param->coef_modulus);
    /// TODO: sk_poly_eval isn't actually used yet. Need to include it in the implementation of encrypt! 
    this->sk_poly_eval = std::unique_ptr<PolynomialEvalForm>(param->mul_engine->init_polynomial_eval_form());  
    this->sk_poly.to_eval(*this->sk_poly_eval.get(), param->mul_engine); 
}

RLWESK::RLWESK(const RLWESK &other){
    throw std::runtime_error("RLWESK::RLWESK(const RLWESK &other): Don't copy the secret key!"); 
}

RLWESK& RLWESK::operator=(const RLWESK other){  
    throw std::runtime_error("RLWESK::operator=(const RLWESK other): Don't copy the secret key!"); 
    return *this;
}
  
void RLWESK::encrypt(RLWECT &out, const Polynomial &m){  
    if(m.degree < param->size){
        throw std::logic_error("RLWESK::encrypt(Polynomial *m): Input polynomial m, degree is too big!");
    }
    if(m.coef_modulus < param->coef_modulus){
        throw std::logic_error("RLWESK::encrypt(Polynomial *m): Input polynomial m, coefficient codulus is too big!");
    }
    if(!m.is_init){
        throw std::logic_error("RLWESK::encrypt(Polynomial *m): Input polynomial m is not initialized!");
    } 
    unif_dist->fill_array(out.a.coefs, param->size); 
    Polynomial noise(param->size, param->coef_modulus);
    error_dist->fill_array(noise.coefs, param->size); 
    Polynomial message(param->size, param->coef_modulus);
    Utils::cp(message.coefs, m.coefs, param->size); 
    // Now just need to compute: b = a * s + e + m
    // First we need a poolynomial s in eval form.    
    out.a.mul(out.b, sk_poly, param->mul_engine); 
    out.b.neg(out.b);
    out.b.add(out.b, noise);
    out.b.add(out.b, message);   
}

RLWECT* RLWESK::encrypt(const Polynomial &m){   
    RLWECT* out = new RLWECT(param);  
    this->encrypt(*out, m);
    return out;
}
 
RLWECT* RLWESK::encode_and_encrypt(Polynomial& m, PlaintextEncoding encoding){
    Polynomial m_scaled(param->size, param->coef_modulus); 
    for(int32_t i = 0; i < param->size; ++i){ 
        m_scaled.coefs[i] = encoding.encode_message(m.coefs[i]);
    }
    RLWECT* out = encrypt(m_scaled); 
    return out;
}

void RLWESK::partial_decrypt(Polynomial &phase, const RLWECT &ct){   
    if(phase.degree != param->size){
        throw std::logic_error("RLWESK::phase(Polynomial *phase, RLWECT *ct): Dimension of the input polynomial differs from the the RLWE polynomials.");
    }
    if(phase.coef_modulus != param->coef_modulus){
        throw std::logic_error("RLWESK::phase(Polynomial *phase, RLWECT *ct): Coefficient modulus of the input polynomial differs from the the RLWE polynomials.");
    }
    if(!phase.is_init){
        throw std::logic_error("RLWESK::phase(Polynomial *phase, RLWECT *ct): Input polynomial is not initialized.");
    } 
    ct.a.mul(phase, sk_poly, param->mul_engine);   
    ct.b.add(phase, phase);  
}
  
Polynomial* RLWESK::decrypt(RLWECT &ct, PlaintextEncoding encoding){
    Polynomial* out = new Polynomial(param->size, param->coef_modulus);
    decrypt(*out, ct, encoding);  
    return out;
}
 
void RLWESK::decrypt(Polynomial &out, const RLWECT &ct, PlaintextEncoding encoding){
    this->partial_decrypt(out, ct);   
    for(int32_t i = 0; i < out.degree; ++i){
        out.coefs[i] = encoding.decode_message(out.coefs[i]);
    }  
}

void RLWESK::extract_lwe_key(int64_t* lwe_key){  
    for(int32_t i = 0; i < param->size; ++i){  
        lwe_key[i] = this->sk_poly.coefs[i]; 
    }  
}

LWESK* RLWESK::extract_lwe_key(){
    std::unique_ptr<int64_t[]> extract_key(new int64_t[param->size]);  
    extract_lwe_key(extract_key.get());
    std::shared_ptr<LWEParam> lwe_param(new LWEParam(param->size, param->coef_modulus));
    return new LWESK(lwe_param, extract_key.get(), this->noise_stddev, this->key_type);
}
 
RLWEGadgetSK::RLWEGadgetSK(std::shared_ptr<Gadget> gadget, std::shared_ptr<RLWESK> rlwe_sk){ 
    this->gadget = gadget; 
    this->vector_ct_param = rlwe_sk->param;
    this->rlwe_sk = rlwe_sk; 
}

RLWEGadgetSK& RLWEGadgetSK::operator=(const RLWEGadgetSK other){  
    throw std::runtime_error("RLWEGadgetSK::operator=(const RLWEGadgetSK other): Don't copy the secret key!");
    return *this;
}
 
RLWEGadgetSK::RLWEGadgetSK(const RLWEGadgetSK &other){ 
    throw std::runtime_error("RLWEGadgetSK::RLWEGadgetSK(const RLWEGadgetSK &other): Don't copy the secret key!");  
}

std::vector<std::unique_ptr<RLWECT>> RLWEGadgetSK::ext_enc(const Polynomial &msg){
    std::vector<std::unique_ptr<RLWECT>> ext_ct; 
    std::shared_ptr<Polynomial> msg_cpy(msg.clone()); 
    // Encryptions of - msg* base**i    
    ext_ct.push_back(std::unique_ptr<RLWECT>(rlwe_sk->encrypt(*msg_cpy.get())));
    for(int32_t i = 1; i < gadget->digits; ++i){
        // Multiply msg by base
        msg_cpy->mul(*msg_cpy.get(), gadget->base); 
        // Encrypt msg * base**i   
        ext_ct.push_back(std::unique_ptr<RLWECT>(rlwe_sk->encrypt(*msg_cpy.get()))); 
    }  
    return ext_ct;
}
  
GadgetVectorCT* RLWEGadgetSK::gadget_encrypt(const Vector &msg){  
    Polynomial msg_poly(msg.vec, rlwe_sk->param->size, rlwe_sk->param->coef_modulus);    
    std::vector<std::unique_ptr<RLWECT>> gadget_ct = ext_enc(msg_poly); 
    // Encryptions of - msg * sk * base**i    
    Polynomial msg_x_sk(rlwe_sk->param->size, rlwe_sk->param->coef_modulus);  
    // Multiply msg with sk.s. Result is in msg_x_sk 
    msg_poly.mul(msg_x_sk, rlwe_sk->sk_poly, rlwe_sk->param->mul_engine);
    //msg_x_sk.neg(&msg_x_sk); 
    std::vector<std::unique_ptr<RLWECT>> gadget_ct_sk = ext_enc(msg_x_sk);   
    return new RLWEGadgetCT(rlwe_sk->param, gadget, gadget_ct, gadget_ct_sk);
}
 
GadgetVectorCT* RLWEGadgetSK::gadget_encrypt(const uint64_t *msg, int32_t size){
    if(size > rlwe_sk->param->size){
        throw std::logic_error("GadgetVectorCT* RLWEGadgetSK::gadget_encrypt(int64_t *msg, int32_t size): size of the message array too big.");
    }
    Polynomial msg_poly(rlwe_sk->param->size, rlwe_sk->param->coef_modulus); 
    msg_poly.zeroize();
    for(int32_t i = 0; i < size; ++i){
        msg_poly.coefs[i] = msg[i];
    }
    return gadget_encrypt(msg_poly);
}
 
ExtendedPolynomialCT* RLWEGadgetSK::extended_encrypt(const Polynomial &msg){      
    std::vector<std::unique_ptr<RLWECT>> gadget_ct = ext_enc(msg); 
    return new ExtendedRLWECT(rlwe_sk->param, gadget, gadget_ct);
}
 
ExtendedPolynomialCT* RLWEGadgetSK::extended_encrypt(const uint64_t *msg, int32_t size){
    if(size > rlwe_sk->param->size){
        throw std::logic_error("GadgetVectorCT* RLWEGadgetSK::gadget_encrypt(int64_t *msg, int32_t size): size of the message array too big.");
    }
    Polynomial msg_poly(rlwe_sk->param->size, rlwe_sk->param->coef_modulus); 
    /// TODO: This should be some sort of constructor. 
    msg_poly.zeroize();
    for(int32_t i = 0; i < size; ++i){
        msg_poly.coefs[i] = msg[i];
    }
    return extended_encrypt(msg_poly);
}

