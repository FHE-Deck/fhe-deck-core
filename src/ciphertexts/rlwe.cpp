#include "ciphertexts/rlwe.h"

using namespace FHEDeck;

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
    a.negacyclic_rotate(out.a, rot);
    b.negacyclic_rotate(out.b, rot); 
}

void RLWECT::cyclic_rotate(RLWECT &out, int32_t rot){   
    a.cyclic_rotate(out.a, rot);
    b.cyclic_rotate(out.b, rot); 
}

void RLWECT::homomorphic_rotate(VectorCT &out, int32_t rot){ 
    // What we do here, is realy multiplication with a monomial.
    if(this->param->ring == RingType::negacyclic){  
        negacyclic_rotate(static_cast<RLWECT&>(out), rot);
    }else if(this->param->ring == RingType::cyclic){
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
    std::string out = "[" +  b.to_string(b.size) + ", " + a.to_string(a.size) + "]";
    return out;
}
 
void RLWECT::extract_lwe(LWECT &lwe_ct_out){
    lwe_ct_out.ct[0] = this->b[0];
    lwe_ct_out.ct[1] = this->a[0];
    for(int32_t i = 1; i < this->param->size; ++i){
        lwe_ct_out.ct[i+1] = -this->a[this->param->size - i];
    } 
}

void RLWECT::extract_lwe(LWECT &lwe_ct_out, uint32_t position){ 
    RLWECT tmp(*this);
    tmp.negacyclic_rotate(tmp, (a.size - position) % a.size);
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
   
void RLWEParam::init_mul_engine(){  
    // Build PolynomialMultiplicationEngine
    PolynomialMultiplicationEngineBuilder mul_engine_builder;
    mul_engine_builder.set_coef_modulus(coef_modulus); 
    mul_engine_builder.set_degree(size);
    mul_engine_builder.set_polynomial_arithmetic(arithmetic);
    mul_engine_builder.set_ring_type(ring); 
    this->mul_engine = mul_engine_builder.build();  
}
 
std::shared_ptr<VectorCT> RLWEParam::init_ct(std::shared_ptr<VectorCTParam> param){ 
    return std::make_shared<RLWECT>(std::static_pointer_cast<RLWEParam>(param)); 
}
 
ExtendedRLWECT::ExtendedRLWECT(std::shared_ptr<RLWEParam> rlwe_param, std::shared_ptr<Gadget> gadget, std::vector<std::shared_ptr<RLWECT>> &gadget_ct){
    this->rlwe_param = rlwe_param;
    this->gadget = gadget;
    this->init(gadget_ct);
}

void ExtendedRLWECT::init(std::vector<std::shared_ptr<RLWECT>> &gadget_ct){     
    PolynomialArray array_coef(rlwe_param->size,  
                                            rlwe_param->coef_modulus,  
                                            gadget->digits);  
  
    this->array_eval_a = std::shared_ptr<PolynomialArrayEvalForm>(rlwe_param->mul_engine->init_polynomial_array_eval_form(gadget->digits));                             
    this->array_eval_b = std::shared_ptr<PolynomialArrayEvalForm>(rlwe_param->mul_engine->init_polynomial_array_eval_form(gadget->digits));    
 
    for(int32_t i = 0; i < gadget->digits; ++i){ 
        array_coef.set_polynomial_at(i, gadget_ct[i]->a);
    }  
     
    rlwe_param->mul_engine->to_eval(*array_eval_a, array_coef);  
  
    for(int32_t i = 0; i < gadget->digits; ++i){
        array_coef.set_polynomial_at(i, gadget_ct[i]->b);
    } 
    rlwe_param->mul_engine->to_eval(*array_eval_b, array_coef);  
}
  
void ExtendedRLWECT::mul(VectorCT &out, const Vector &msg){ 
     if(msg.modulus > rlwe_param->coef_modulus){ throw std::logic_error("ExtendedRLWECT::mul(VectorCT &out, const Vector &msg): modulus bigger"); }

    if(msg.size != rlwe_param->size){ throw std::logic_error("ExtendedRLWECT::mul(VectorCT &out, const Vector &msg): size different"); }

    RLWECT& out_ptr = static_cast<RLWECT&>(out);    
    /// TODO: Assert what size of OK, and msg modulus isn't bigger, then use copy constructor.
    //Polynomial msg_in(msg.vec, rlwe_param->size, rlwe_param->coef_modulus);
    Polynomial msg_in(msg, rlwe_param->size, rlwe_param->coef_modulus);

    std::shared_ptr<PolynomialArrayEvalForm> poly_decomp_eval_form = std::shared_ptr<PolynomialArrayEvalForm>(rlwe_param->mul_engine->init_polynomial_array_eval_form(gadget->digits));  
    PolynomialArray poly_decomp_coef_form(rlwe_param->size, rlwe_param->coef_modulus, gadget->digits);
    gadget->sample(poly_decomp_coef_form, msg_in);   
    rlwe_param->mul_engine->multisum(out_ptr.b, *poly_decomp_eval_form, poly_decomp_coef_form, *array_eval_b);  
    rlwe_param->mul_engine->multisum(out_ptr.a, *poly_decomp_eval_form, *array_eval_a);  
}
   
RLWEGadgetCT::RLWEGadgetCT(std::shared_ptr<RLWEParam> rlwe_param, std::shared_ptr<Gadget> gadget, std::vector<std::shared_ptr<RLWECT>> &gadget_ct, std::vector<std::shared_ptr<RLWECT>> &gadget_ct_sk){
    this->rlwe_param = rlwe_param;
    this->gadget = gadget;
    this->init(gadget_ct, gadget_ct_sk);
}

void RLWEGadgetCT::init(std::vector<std::shared_ptr<RLWECT>> &gadget_ct, std::vector<std::shared_ptr<RLWECT>> &gadget_ct_sk){     
    PolynomialArray array_coef(rlwe_param->size,  
                                            rlwe_param->coef_modulus,  
                                            gadget->digits);  
  
    this->array_eval_a = std::shared_ptr<PolynomialArrayEvalForm>(rlwe_param->mul_engine->init_polynomial_array_eval_form(gadget->digits));                             
    this->array_eval_b = std::shared_ptr<PolynomialArrayEvalForm>(rlwe_param->mul_engine->init_polynomial_array_eval_form(gadget->digits));   
    this->array_eval_a_sk = std::shared_ptr<PolynomialArrayEvalForm>(rlwe_param->mul_engine->init_polynomial_array_eval_form(gadget->digits));    
    this->array_eval_b_sk = std::shared_ptr<PolynomialArrayEvalForm>(rlwe_param->mul_engine->init_polynomial_array_eval_form(gadget->digits));  
 
    for(int32_t i = 0; i < gadget->digits; ++i){ 
        array_coef.set_polynomial_at(i, gadget_ct[i]->a);
    }  
     
    rlwe_param->mul_engine->to_eval(*array_eval_a, array_coef);  
  
    for(int32_t i = 0; i < gadget->digits; ++i){
        array_coef.set_polynomial_at(i, gadget_ct[i]->b);
    } 
    rlwe_param->mul_engine->to_eval(*array_eval_b, array_coef); 
  
    for(int32_t i = 0; i < gadget->digits; ++i){
        array_coef.set_polynomial_at(i, gadget_ct_sk[i]->a);
    } 
    rlwe_param->mul_engine->to_eval(*array_eval_a_sk, array_coef);  
   
    for(int32_t i = 0; i < gadget->digits; ++i){
        array_coef.set_polynomial_at(i, gadget_ct_sk[i]->b);
    } 
    rlwe_param->mul_engine->to_eval(*array_eval_b_sk, array_coef);   
}
  
void RLWEGadgetCT::mul(VectorCT &out, const VectorCT &ct){ 
    RLWECT& out_ptr = static_cast<RLWECT&>(out);
    const RLWECT& ct_ptr = static_cast<const RLWECT&>(ct); 
    PolynomialArray poly_decomp_coef_form(rlwe_param->size, rlwe_param->coef_modulus, gadget->digits);
    gadget->sample(poly_decomp_coef_form, ct_ptr.a);   
    RLWECT out_minus(rlwe_param); 
    std::shared_ptr<PolynomialArrayEvalForm> poly_decomp_eval_form(rlwe_param->mul_engine->init_polynomial_array_eval_form(gadget->digits));
    rlwe_param->mul_engine->multisum(out_minus.b, *poly_decomp_eval_form, poly_decomp_coef_form, *array_eval_b_sk);  
    rlwe_param->mul_engine->multisum(out_minus.a, *poly_decomp_eval_form, *array_eval_a_sk);  
   
    gadget->sample(poly_decomp_coef_form, ct_ptr.b);  
    rlwe_param->mul_engine->multisum(out_ptr.b, *poly_decomp_eval_form, poly_decomp_coef_form, *array_eval_b);  
    rlwe_param->mul_engine->multisum(out_ptr.a, *poly_decomp_eval_form, *array_eval_a); 
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
    this->vector_ct_param = this->param;
    this->unif_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, param->coef_modulus));
    this->error_dist = std::shared_ptr<Distribution>(new StandardRoundedGaussianDistribution(0, noise_stddev));
}

void RLWESK::key_gen(){
    this->sk_poly = Polynomial(param->size, param->coef_modulus);  
    std::shared_ptr<Distribution> sk_dist;
    if(key_type == KeyDistribution::uniform){ 
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, param->coef_modulus));
    }else if(key_type == KeyDistribution::ternary){ 
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(-1, 1));
    }else if(key_type == KeyDistribution::binary){ 
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, 1));
    }   
    sk_dist->fill(this->sk_poly);   
    /// TODO: sk_poly_eval isn't actually used yet. Need to include it in the implementation of encrypt!  
    this->sk_poly_eval = param->mul_engine->init_polynomial_eval_form();  
    this->sk_poly.to_eval(*this->sk_poly_eval, param->mul_engine); 
}
 
void RLWESK::encrypt(VectorCT &out, const Vector &m){  
    RLWECT& out_cast = static_cast<RLWECT&>(out);
    if(m.size != param->size){
        throw std::logic_error("RLWESK::encrypt(VectorCT &out, const Vector &m): Input polynomial m, degree different!");
    }
    if(m.modulus > param->coef_modulus){
        throw std::logic_error("RLWESK::encrypt(VectorCT &out, const Vector &m): Input polynomial m, coefficient modulus is too big!");
    } 
    unif_dist->fill(out_cast.a); 
    Polynomial noise(param->size, param->coef_modulus); 
    error_dist->fill(noise); 
    Polynomial message(m, param->size, param->coef_modulus);
    //Utils::cp(message.vec, m.vec, param->size); 
    // Now just need to compute: b = a * s + e + m
    // First we need a poolynomial s in eval form.    
    out_cast.a.mul(out_cast.b, sk_poly, param->mul_engine); 
    out_cast.b.neg(out_cast.b);
    out_cast.b.add(out_cast.b, noise);
    out_cast.b.add(out_cast.b, message);   
}

std::shared_ptr<VectorCT> RLWESK::encrypt(const Vector &m){   
    std::shared_ptr<RLWECT> out = std::make_shared<RLWECT>(param);  
    this->encrypt(*out, m);
    return out;
}
 
std::shared_ptr<VectorCT> RLWESK::encode_and_encrypt(const Vector& m, PlaintextEncoding encoding){ 
    std::shared_ptr<RLWECT> out = std::make_shared<RLWECT>(param); 
    encode_and_encrypt(*out, m, encoding);
    return out;
}

void RLWESK::encode_and_encrypt(VectorCT& out, const Vector& m, PlaintextEncoding encoding){
    Polynomial m_scaled(param->size, param->coef_modulus); 
    for(int32_t i = 0; i < param->size; ++i){ 
        m_scaled[i] = encoding.encode_message(m[i]);
    }
    encrypt(out, m_scaled);  
}

void RLWESK::partial_decrypt(Polynomial &phase, const RLWECT &ct){   
    if(phase.size != param->size){
        throw std::logic_error("RLWESK::partial_decrypt(Polynomial &phase, const RLWECT &ct): Dimension of the input polynomial differs from the the RLWE polynomials.");
    }
    if(phase.modulus != param->coef_modulus){
        throw std::logic_error("RRLWESK::partial_decrypt(Polynomial &phase, const RLWECT &ct): Coefficient modulus of the input polynomial differs from the the RLWE polynomials.");
    } 
    ct.a.mul(phase, sk_poly, param->mul_engine);   
    ct.b.add(phase, phase);  
}
  
std::shared_ptr<Vector> RLWESK::decrypt(const VectorCT &ct, PlaintextEncoding encoding){
    std::shared_ptr<Polynomial> out = std::make_shared<Polynomial>(param->size, param->coef_modulus);
    decrypt(*out, ct, encoding);  
    return out;
}
 
void RLWESK::decrypt(Vector &out, const VectorCT &ct, PlaintextEncoding encoding){
    Polynomial& out_cast = static_cast<Polynomial&>(out);
    const RLWECT& ct_cast = static_cast<const RLWECT&>(ct);
    Polynomial partial_dec(this->param->size, this->param->coef_modulus);
    this->partial_decrypt(partial_dec, ct_cast);   
    for(int32_t i = 0; i < out.size; ++i){
        out_cast[i] = encoding.decode_message(partial_dec[i]);
    }  
}
 

std::shared_ptr<LWESK> RLWESK::extract_lwe_key(){
    std::unique_ptr<int64_t[]> extract_key(new int64_t[param->size]);   
    for(int32_t i = 0; i < param->size; ++i){  
        extract_key[i] = this->sk_poly[i]; 
    }  
    std::shared_ptr<LWEParam> lwe_param(new LWEParam(param->size, param->coef_modulus));
    return std::make_shared<LWESK>(lwe_param, extract_key.get(), this->noise_stddev, this->key_type);
}
 
RLWEGadgetSK::RLWEGadgetSK(std::shared_ptr<Gadget> gadget, std::shared_ptr<RLWESK> rlwe_sk){ 
    this->gadget = gadget; 
    this->secret_key = rlwe_sk;
    this->vector_ct_param = rlwe_sk->param;
    this->rlwe_sk = rlwe_sk; 
}
 
std::vector<std::shared_ptr<RLWECT>> RLWEGadgetSK::ext_enc(Polynomial &msg){

    if(msg.modulus != rlwe_sk->param->coef_modulus){ throw std::logic_error("RLWEGadgetSK::ext_enc(Polynomial &msg): modulus differs"); }

    if(msg.size != rlwe_sk->param->size){ throw std::logic_error("RLWEGadgetSK::ext_enc(Polynomial &msg): size differs"); }
 
    std::vector<std::shared_ptr<RLWECT>> ext_ct;   
    // Encryptions of - msg* base**i    
    ext_ct.push_back(std::static_pointer_cast<RLWECT>(rlwe_sk->encrypt(msg)));
    for(int32_t i = 1; i < gadget->digits; ++i){
        // Multiply msg by base
        msg.mul(msg, gadget->base); 
        // Encrypt msg * base**i   
        ext_ct.push_back(std::static_pointer_cast<RLWECT>(rlwe_sk->encrypt(msg))); 
    }  
    return ext_ct;
}
  
std::shared_ptr<GadgetVectorCT> RLWEGadgetSK::gadget_encrypt(const Vector &msg){   
    if(msg.modulus > rlwe_sk->param->coef_modulus){ throw std::logic_error("RLWEGadgetSK::gadget_encrypt(const Vector &msg): modulus bigger"); }

    if(msg.size != rlwe_sk->param->size){ throw std::logic_error("RLWEGadgetSK::gadget_encrypt(const Vector &msg): size different"); }
 
    Polynomial msg_poly(msg, rlwe_sk->param->size, rlwe_sk->param->coef_modulus);     

    std::vector<std::shared_ptr<RLWECT>> gadget_ct = ext_enc(msg_poly); 
    // Encryptions of - msg * sk * base**i    
    Polynomial msg_x_sk(msg, rlwe_sk->param->size, rlwe_sk->param->coef_modulus);  
    // Multiply msg with sk.s. Result is in msg_x_sk  
    msg_x_sk.mul(msg_x_sk, rlwe_sk->sk_poly, rlwe_sk->param->mul_engine); 
    std::vector<std::shared_ptr<RLWECT>> gadget_ct_sk = ext_enc(msg_x_sk);   
    return std::make_shared<RLWEGadgetCT>(rlwe_sk->param, gadget, gadget_ct, gadget_ct_sk);
}
 
std::shared_ptr<GadgetVectorCT> RLWEGadgetSK::gadget_encrypt(const std::vector<int64_t>& msg){
    if(msg.size() > rlwe_sk->param->size){
        throw std::logic_error("GadgetVectorCT* RLWEGadgetSK::gadget_encrypt(int64_t *msg, int32_t size): size of the message array too big.");
    }
    
    Polynomial msg_poly(msg, rlwe_sk->param->size, rlwe_sk->param->coef_modulus); 
    return gadget_encrypt(msg_poly);
}
 
std::shared_ptr<ExtendedPolynomialCT> RLWEGadgetSK::extended_encrypt(const Vector &msg){    
    
    if(msg.modulus > rlwe_sk->param->coef_modulus){ throw std::logic_error("RLWEGadgetSK::extended_encrypt(const Vector &msg): modulus bigger"); }

    if(msg.size != rlwe_sk->param->size){ throw std::logic_error("RLWEGadgetSK::extended_encrypt(const Vector &msg): size different"); }

    Polynomial msg_poly(msg, rlwe_sk->param->size, rlwe_sk->param->coef_modulus);
    std::vector<std::shared_ptr<RLWECT>> gadget_ct = ext_enc(msg_poly); 
    return std::make_shared<ExtendedRLWECT>(rlwe_sk->param, gadget, gadget_ct);
}
 
std::shared_ptr<ExtendedPolynomialCT> RLWEGadgetSK::extended_encrypt(const std::vector<int64_t>& msg){
    if(msg.size() > rlwe_sk->param->size){
        throw std::logic_error("GadgetVectorCT* RLWEGadgetSK::gadget_encrypt(int64_t *msg, int32_t size): size of the message array too big.");
    }
    Polynomial msg_poly(msg, rlwe_sk->param->size, rlwe_sk->param->coef_modulus); 
    std::vector<std::shared_ptr<RLWECT>> gadget_ct = ext_enc(msg_poly); 
    return std::make_shared<ExtendedRLWECT>(rlwe_sk->param, gadget, gadget_ct); 
}

