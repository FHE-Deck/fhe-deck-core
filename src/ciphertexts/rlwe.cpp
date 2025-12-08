#include "ciphertexts/rlwe.h"

using namespace FHEDeck;

RLWECT::RLWECT(std::shared_ptr<RLWEParam> param){
    m_param = param;   
    m_a = Polynomial(param->size(), param->modulus()); 
    m_b = Polynomial(param->size(), param->modulus());   
}

RLWECT::RLWECT(std::shared_ptr<RLWEParam> param, const Polynomial& a, const Polynomial& b){
    m_param = param;   
    m_a = a; 
    m_b = b;   
}

RLWECT::RLWECT(std::shared_ptr<RLWEParam> param, Polynomial&& a, Polynomial&& b): 
    m_param(std::move(param)), m_a(std::move(a)), m_b(std::move(b))
{ 
}
 
RLWECT::RLWECT(const RLWECT &other){ 
    m_param = other.m_param;
    m_a = other.m_a;
    m_b = other.m_b; 
}
 
 
RLWECT& RLWECT::operator=(const RLWECT other){  
    m_param = other.m_param;
    m_a = other.m_a;
    m_b = other.m_b;   
    return *this;
}
  
void RLWECT::negacyclic_rotate(RLWECT &out, int32_t rot)const{   
    m_a.negacyclic_rotate(out.m_a, rot);
    m_b.negacyclic_rotate(out.m_b, rot); 
}

void RLWECT::cyclic_rotate(RLWECT &out, int32_t rot)const{   
    m_a.cyclic_rotate(out.m_a, rot);
    m_b.cyclic_rotate(out.m_b, rot); 
}

void RLWECT::homomorphic_rotate(VectorCT &out, int32_t rot)const{ 
    // What we do here, is realy multiplication with a monomial.
    if(m_param->ring() == RingType::negacyclic){  
        negacyclic_rotate(static_cast<RLWECT&>(out), rot);
    }else if(m_param->ring() == RingType::cyclic){
        cyclic_rotate(static_cast<RLWECT&>(out), rot);
    }else{
        throw std::logic_error("RLWECT::homomorphic_rotate(VectorCT *out, int32_t rot): this->param->ring currently not supported.");
    }
}
 
void RLWECT::add(VectorCT& out, const VectorCT &ct)const{  
    RLWECT &out_ptr = static_cast<RLWECT&>(out); 
    const RLWECT &ct_ptr = static_cast<const RLWECT&>(ct);
    ct_ptr.m_a.add(out_ptr.m_a, m_a);
    ct_ptr.m_b.add(out_ptr.m_b, m_b);  
}
  
void RLWECT::add(RLWECT &out, const Polynomial &x)const{
    m_b.add(out.m_b, x); 
}
 
void RLWECT::sub(VectorCT &out, const VectorCT &ct)const{  
    RLWECT &out_ptr = static_cast<RLWECT&>(out);
    const RLWECT &ct_ptr = static_cast<const RLWECT&>(ct);
    m_a.sub(out_ptr.m_a, ct_ptr.m_a);
    m_b.sub(out_ptr.m_b, ct_ptr.m_b); 
}
  
void RLWECT::sub(RLWECT &out, const Polynomial &x)const{
    m_b.sub(out.m_b, x);  
}

void RLWECT::neg(VectorCT &out)const{
    RLWECT &out_ptr = static_cast<RLWECT&>(out); 
    m_a.neg(out_ptr.m_a);
    m_b.neg(out_ptr.m_b); 
}
  
void RLWECT::mul(RLWECT &out, const Polynomial &x)const{ 
    m_a.mul(out.m_a, x, m_param->mul_engine());
    m_b.mul(out.m_b, x, m_param->mul_engine()); 
}

void RLWECT::mul(RLWECT &out, int64_t x)const{ 
    m_a.mul(out.m_a, x);
    m_b.mul(out.m_b, x); 
}
 
std::string RLWECT::to_string()const{
    std::string out = "[" +  m_b.to_string(m_b.size()) + ", " + m_a.to_string(m_a.size()) + "]";
    return out;
}

const RLWEParam& RLWECT::param()const{
    return *m_param;
}
 
const Polynomial& RLWECT::a()const{
    return m_a;
}

const Polynomial& RLWECT::b()const{
    return m_b;
} 

void RLWECT::a(const Polynomial& in){
    m_a = in;
}

void RLWECT::b(const Polynomial& in){
    m_b = in;
}

void RLWECT::a(Polynomial&& in){
    m_a = std::move(in);
}

void RLWECT::b(Polynomial&& in){
    m_b = std::move(in);
}
 
void RLWECT::extract_lwe(LWECT &lwe_ct_out)const{
    lwe_ct_out[0] = m_b[0];
    lwe_ct_out[1] = m_a[0];
    for(int32_t i = 1; i < m_param->size(); ++i){
        lwe_ct_out[i+1] = -m_a[m_param->size() - i];
    } 
}

void RLWECT::extract_lwe(LWECT &lwe_ct_out, uint32_t position)const{ 
    RLWECT tmp(*this);
    tmp.negacyclic_rotate(tmp, (m_a.size() - position) % m_a.size());
    tmp.neg(tmp); 
    tmp.extract_lwe(lwe_ct_out);
}

  
RLWEParam::RLWEParam(RingType ring, int32_t ring_degree, uint64_t coef_modulus,  PolynomialArithmetic arithmetic){
    m_coef_modulus = coef_modulus; 
    m_size = ring_degree;  
    m_ring = ring;  
    m_arithmetic = arithmetic;   
    init_mul_engine(); 
}
       
void RLWEParam::init_mul_engine(){  
    // Build PolynomialMultiplicationEngine
    PolynomialMultiplicationEngineBuilder mul_engine_builder;
    mul_engine_builder.set_coef_modulus(m_coef_modulus); 
    mul_engine_builder.set_degree(m_size);
    mul_engine_builder.set_polynomial_arithmetic(m_arithmetic);
    mul_engine_builder.set_ring_type(m_ring); 
    m_mul_engine = mul_engine_builder.build();  
}
 
std::shared_ptr<VectorCT> RLWEParam::init_ct(std::shared_ptr<VectorCTParam> param){ 
    return std::make_shared<RLWECT>(std::static_pointer_cast<RLWEParam>(param)); 
}

uint64_t RLWEParam::modulus()const{
    return m_coef_modulus;
}

std::shared_ptr<PolynomialMultiplicationEngine> RLWEParam::mul_engine()const{
    return m_mul_engine;
}
 
RingType RLWEParam::ring()const{
    return m_ring;
}

ExtendedRLWECT::ExtendedRLWECT(std::shared_ptr<RLWEParam> rlwe_param, std::shared_ptr<Gadget> gadget, std::vector<std::shared_ptr<RLWECT>> &gadget_ct){
    m_rlwe_param = rlwe_param;
    m_gadget = gadget;
    this->init(gadget_ct);
}

void ExtendedRLWECT::init(std::vector<std::shared_ptr<RLWECT>> &gadget_ct){     
    PolynomialArray array_coef(m_rlwe_param->size(),  
                                            m_rlwe_param->modulus(),  
                                            m_gadget->digits);  
  
    m_array_eval_a = std::shared_ptr<PolynomialArrayEvalForm>(m_rlwe_param->mul_engine()->init_polynomial_array_eval_form(m_gadget->digits));                             
    m_array_eval_b = std::shared_ptr<PolynomialArrayEvalForm>(m_rlwe_param->mul_engine()->init_polynomial_array_eval_form(m_gadget->digits));    
 
    for(int32_t i = 0; i < m_gadget->digits; ++i){ 
        array_coef.set_polynomial_at(i, gadget_ct[i]->a());
    }  
     
    m_rlwe_param->mul_engine()->to_eval(*m_array_eval_a, array_coef);  
  
    for(int32_t i = 0; i < m_gadget->digits; ++i){
        array_coef.set_polynomial_at(i, gadget_ct[i]->b());
    } 
    m_rlwe_param->mul_engine()->to_eval(*m_array_eval_b, array_coef);  
}
  
void ExtendedRLWECT::mul(VectorCT &out, const Vector &msg){ 
     if(msg.modulus() > m_rlwe_param->modulus()){ throw std::logic_error("ExtendedRLWECT::mul(VectorCT &out, const Vector &msg): modulus bigger"); }

    if(msg.size() != m_rlwe_param->size()){ throw std::logic_error("ExtendedRLWECT::mul(VectorCT &out, const Vector &msg): size different"); }

    RLWECT& out_ptr = static_cast<RLWECT&>(out);     
    Polynomial msg_in(msg, m_rlwe_param->size(), m_rlwe_param->modulus());

    std::shared_ptr<PolynomialArrayEvalForm> poly_decomp_eval_form = std::shared_ptr<PolynomialArrayEvalForm>(m_rlwe_param->mul_engine()->init_polynomial_array_eval_form(m_gadget->digits));  
    PolynomialArray poly_decomp_coef_form(m_rlwe_param->size(), m_rlwe_param->modulus(), m_gadget->digits);
    m_gadget->sample(poly_decomp_coef_form, msg_in);   
    Polynomial b(m_rlwe_param->size(), m_rlwe_param->modulus());
    m_rlwe_param->mul_engine()->multisum(b, *poly_decomp_eval_form, poly_decomp_coef_form, *m_array_eval_b);  
    Polynomial a(m_rlwe_param->size(), m_rlwe_param->modulus());
    m_rlwe_param->mul_engine()->multisum(a, *poly_decomp_eval_form, *m_array_eval_a);   
    out_ptr = RLWECT(m_rlwe_param, std::move(a), std::move(b));
}
   
RLWEGadgetCT::RLWEGadgetCT(std::shared_ptr<RLWEParam> rlwe_param, std::shared_ptr<Gadget> gadget, std::vector<std::shared_ptr<RLWECT>> &gadget_ct, std::vector<std::shared_ptr<RLWECT>> &gadget_ct_sk){
    m_rlwe_param = rlwe_param;
    m_gadget = gadget;
    this->init(gadget_ct, gadget_ct_sk);
}

void RLWEGadgetCT::init(std::vector<std::shared_ptr<RLWECT>> &gadget_ct, std::vector<std::shared_ptr<RLWECT>> &gadget_ct_sk){     
    PolynomialArray array_coef(m_rlwe_param->size(),  
                                            m_rlwe_param->modulus(),  
                                            m_gadget->digits);  
  
    m_array_eval_a = std::shared_ptr<PolynomialArrayEvalForm>(m_rlwe_param->mul_engine()->init_polynomial_array_eval_form(m_gadget->digits));                             
    m_array_eval_b = std::shared_ptr<PolynomialArrayEvalForm>(m_rlwe_param->mul_engine()->init_polynomial_array_eval_form(m_gadget->digits));   
    m_array_eval_a_sk = std::shared_ptr<PolynomialArrayEvalForm>(m_rlwe_param->mul_engine()->init_polynomial_array_eval_form(m_gadget->digits));    
    m_array_eval_b_sk = std::shared_ptr<PolynomialArrayEvalForm>(m_rlwe_param->mul_engine()->init_polynomial_array_eval_form(m_gadget->digits));  
 
    for(int32_t i = 0; i < m_gadget->digits; ++i){ 
        array_coef.set_polynomial_at(i, gadget_ct[i]->a());
    }  
     
    m_rlwe_param->mul_engine()->to_eval(*m_array_eval_a, array_coef);  
  
    for(int32_t i = 0; i < m_gadget->digits; ++i){
        array_coef.set_polynomial_at(i, gadget_ct[i]->b());
    } 
    m_rlwe_param->mul_engine()->to_eval(*m_array_eval_b, array_coef); 
  
    for(int32_t i = 0; i < m_gadget->digits; ++i){
        array_coef.set_polynomial_at(i, gadget_ct_sk[i]->a());
    } 
    m_rlwe_param->mul_engine()->to_eval(*m_array_eval_a_sk, array_coef);  
   
    for(int32_t i = 0; i < m_gadget->digits; ++i){
        array_coef.set_polynomial_at(i, gadget_ct_sk[i]->b());
    } 
    m_rlwe_param->mul_engine()->to_eval(*m_array_eval_b_sk, array_coef);   
}
  
void RLWEGadgetCT::mul(VectorCT &out, const VectorCT &ct){ 
    //RLWECT& out_ptr = static_cast<RLWECT&>(out);
    const RLWECT& ct_ptr = static_cast<const RLWECT&>(ct); 
    PolynomialArray poly_decomp_coef_form(m_rlwe_param->size(), m_rlwe_param->modulus(), m_gadget->digits);
    m_gadget->sample(poly_decomp_coef_form, ct_ptr.a());   
    std::shared_ptr<PolynomialArrayEvalForm> poly_decomp_eval_form(m_rlwe_param->mul_engine()->init_polynomial_array_eval_form(m_gadget->digits));
    Polynomial b_minus(m_rlwe_param->size(), m_rlwe_param->modulus());
    m_rlwe_param->mul_engine()->multisum(b_minus, *poly_decomp_eval_form, poly_decomp_coef_form, *m_array_eval_b_sk);  
    Polynomial a_minus(m_rlwe_param->size(), m_rlwe_param->modulus());
    m_rlwe_param->mul_engine()->multisum(a_minus, *poly_decomp_eval_form, *m_array_eval_a_sk);   
    RLWECT out_minus(m_rlwe_param, std::move(a_minus), std::move(b_minus)); 
   
    m_gadget->sample(poly_decomp_coef_form, ct_ptr.b());  
    Polynomial b_plus(m_rlwe_param->size(), m_rlwe_param->modulus());
    m_rlwe_param->mul_engine()->multisum(b_plus, *poly_decomp_eval_form, poly_decomp_coef_form, *m_array_eval_b);  
    Polynomial a_plus(m_rlwe_param->size(), m_rlwe_param->modulus());
    m_rlwe_param->mul_engine()->multisum(a_plus, *poly_decomp_eval_form, *m_array_eval_a); 
    RLWECT out_plus(m_rlwe_param, std::move(a_plus), std::move(b_plus)); 
    out_plus.add(out, out_minus);  
}
   
RLWESK::RLWESK(std::shared_ptr<RLWEParam> param, KeyDistribution key_type, double noise_stddev){ 
    m_param = param;
    m_key_type = key_type;
    m_noise_stddev = noise_stddev;
    init();
    key_gen(); 
}

void RLWESK::init(){ 
    m_vector_ct_param = m_param;
    m_unif_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, m_param->modulus()));
    m_error_dist = std::shared_ptr<Distribution>(new StandardRoundedGaussianDistribution(0, m_noise_stddev));
}

void RLWESK::key_gen(){
    m_sk_poly = Polynomial(m_param->size(), m_param->modulus());  
    std::shared_ptr<Distribution> sk_dist;
    if(m_key_type == KeyDistribution::uniform){ 
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, m_param->modulus()));
    }else if(m_key_type == KeyDistribution::ternary){ 
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(-1, 1));
    }else if(m_key_type == KeyDistribution::binary){ 
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, 1));
    }   
    sk_dist->fill(m_sk_poly);   
    /// TODO: sk_poly_eval isn't actually used yet. Need to include it in the implementation of encrypt!  
    m_sk_poly_eval = m_param->mul_engine()->init_polynomial_eval_form();  
    m_sk_poly.to_eval(*m_sk_poly_eval, m_param->mul_engine()); 
}
 
void RLWESK::encrypt(VectorCT &out, const Vector &m){  
    RLWECT& out_cast = static_cast<RLWECT&>(out);
    if(m.size() != m_param->size()){
        throw std::logic_error("RLWESK::encrypt(VectorCT &out, const Vector &m): Input polynomial m, degree different!");
    }
    if(m.modulus() > m_param->modulus()){
        throw std::logic_error("RLWESK::encrypt(VectorCT &out, const Vector &m): Input polynomial m, coefficient modulus is too big!");
    } 
    Polynomial a(m_param->size(),  m_param->modulus());
    m_unif_dist->fill(a); 
    Polynomial noise(m_param->size(), m_param->modulus()); 
    m_error_dist->fill(noise); 
    Polynomial message(m, m_param->size(), m_param->modulus()); 
    // Now just need to compute: b = a * s + e + m
    // First we need a poolynomial s in eval form.    
    Polynomial b(m_param->size(), m_param->modulus());
    a.mul(b, m_sk_poly, m_param->mul_engine()); 
    b.neg(b);
    b.add(b, noise);
    b.add(b, message);   
    out_cast = RLWECT(m_param, std::move(a), std::move(b));
}

std::shared_ptr<VectorCT> RLWESK::encrypt(const Vector &m){   
    std::shared_ptr<RLWECT> out = std::make_shared<RLWECT>(m_param);  
    this->encrypt(*out, m);
    return out;
}
 
std::shared_ptr<VectorCT> RLWESK::encode_and_encrypt(const Vector& m, PlaintextEncoding encoding){ 
    std::shared_ptr<RLWECT> out = std::make_shared<RLWECT>(m_param); 
    encode_and_encrypt(*out, m, encoding);
    return out;
}

void RLWESK::encode_and_encrypt(VectorCT& out, const Vector& m, PlaintextEncoding encoding){
    Polynomial m_scaled(m_param->size(), m_param->modulus()); 
    for(int32_t i = 0; i < m_param->size(); ++i){ 
        m_scaled[i] = encoding.encode_message(m[i]);
    }
    encrypt(out, m_scaled);  
}

void RLWESK::partial_decrypt(Polynomial &phase, const RLWECT &ct){   
    if(phase.size() != m_param->size()){
        throw std::logic_error("RLWESK::partial_decrypt(Polynomial &phase, const RLWECT &ct): Dimension of the input polynomial differs from the the RLWE polynomials.");
    }
    if(phase.modulus() != m_param->modulus()){
        throw std::logic_error("RRLWESK::partial_decrypt(Polynomial &phase, const RLWECT &ct): Coefficient modulus of the input polynomial differs from the the RLWE polynomials.");
    } 
    ct.a().mul(phase, m_sk_poly, m_param->mul_engine());   
    ct.b().add(phase, phase);  
}
  
std::shared_ptr<Vector> RLWESK::decrypt(const VectorCT &ct, PlaintextEncoding encoding){
    std::shared_ptr<Polynomial> out = std::make_shared<Polynomial>(param()->size(), param()->modulus());
    decrypt(*out, ct, encoding);  
    return out;
}
 
void RLWESK::decrypt(Vector &out, const VectorCT &ct, PlaintextEncoding encoding){
    Polynomial& out_cast = static_cast<Polynomial&>(out);
    const RLWECT& ct_cast = static_cast<const RLWECT&>(ct);
    Polynomial partial_dec(m_param->size(), m_param->modulus());
    partial_decrypt(partial_dec, ct_cast);   
    for(int32_t i = 0; i < out.size(); ++i){
        out_cast[i] = encoding.decode_message(partial_dec[i]);
    }  
}
 

std::shared_ptr<LWESK> RLWESK::extract_lwe_key(){
    std::unique_ptr<int64_t[]> extract_key(new int64_t[m_param->size()]);   
    for(int32_t i = 0; i < m_param->size(); ++i){  
        extract_key[i] = m_sk_poly[i]; 
    }  
    std::shared_ptr<LWEParam> lwe_param(new LWEParam(m_param->size(), m_param->modulus()));
    return std::make_shared<LWESK>(lwe_param, extract_key.get(), m_noise_stddev, m_key_type);
}

std::shared_ptr<RLWEParam> RLWESK::param()const{
    return m_param;
}

RLWEGadgetSK::RLWEGadgetSK(std::shared_ptr<Gadget> gadget, std::shared_ptr<RLWESK> rlwe_sk){ 
    m_gadget = gadget;  
    m_secret_key = rlwe_sk;
    m_vector_ct_param = rlwe_sk->param();
    m_rlwe_sk = rlwe_sk; 
}
 
std::vector<std::shared_ptr<RLWECT>> RLWEGadgetSK::ext_enc(Polynomial &msg)const{

    if(msg.modulus() != m_rlwe_sk->param()->modulus()){ throw std::logic_error("RLWEGadgetSK::ext_enc(Polynomial &msg): modulus differs"); }

    if(msg.size() != m_rlwe_sk->param()->size()){ throw std::logic_error("RLWEGadgetSK::ext_enc(Polynomial &msg): size differs"); }
 
    std::vector<std::shared_ptr<RLWECT>> ext_ct;   
    // Encryptions of - msg* base**i    
    ext_ct.push_back(std::static_pointer_cast<RLWECT>(m_rlwe_sk->encrypt(msg)));
    for(int32_t i = 1; i < m_gadget->digits; ++i){
        // Multiply msg by base
        msg.mul(msg, m_gadget->base); 
        // Encrypt msg * base**i   
        ext_ct.push_back(std::static_pointer_cast<RLWECT>(m_rlwe_sk->encrypt(msg))); 
    }  
    return ext_ct;
}
  
std::shared_ptr<GadgetVectorCT> RLWEGadgetSK::gadget_encrypt(const Vector &msg)const{   
    if(msg.modulus() > m_rlwe_sk->param()->modulus()){ throw std::logic_error("RLWEGadgetSK::gadget_encrypt(const Vector &msg): modulus bigger"); }

    if(msg.size() != m_rlwe_sk->param()->size()){ throw std::logic_error("RLWEGadgetSK::gadget_encrypt(const Vector &msg): size different"); }
 
    Polynomial msg_poly(msg, m_rlwe_sk->param()->size(), m_rlwe_sk->param()->modulus());     

    std::vector<std::shared_ptr<RLWECT>> gadget_ct = ext_enc(msg_poly); 
    // Encryptions of - msg * sk * base**i    
    Polynomial msg_x_sk(msg, m_rlwe_sk->param()->size(), m_rlwe_sk->param()->modulus());  
    // Multiply msg with sk.s. Result is in msg_x_sk  
    msg_x_sk.mul(msg_x_sk, m_rlwe_sk->m_sk_poly, m_rlwe_sk->param()->mul_engine()); 
    std::vector<std::shared_ptr<RLWECT>> gadget_ct_sk = ext_enc(msg_x_sk);   
    return std::make_shared<RLWEGadgetCT>(m_rlwe_sk->param(), m_gadget, gadget_ct, gadget_ct_sk);
}
 
std::shared_ptr<GadgetVectorCT> RLWEGadgetSK::gadget_encrypt(const std::vector<int64_t>& msg)const{
    if(msg.size() > m_rlwe_sk->param()->size()){
        throw std::logic_error("GadgetVectorCT* RLWEGadgetSK::gadget_encrypt(int64_t *msg, int32_t size): size of the message array too big.");
    }
    
    Polynomial msg_poly(msg, m_rlwe_sk->param()->size(), m_rlwe_sk->param()->modulus()); 
    return gadget_encrypt(msg_poly);
}
 
std::shared_ptr<ExtendedPolynomialCT> RLWEGadgetSK::extended_encrypt(const Vector &msg)const{    
    
    if(msg.modulus() > m_rlwe_sk->param()->modulus()){ throw std::logic_error("RLWEGadgetSK::extended_encrypt(const Vector &msg): modulus bigger"); }

    if(msg.size() != m_rlwe_sk->param()->size()){ throw std::logic_error("RLWEGadgetSK::extended_encrypt(const Vector &msg): size different"); }

    Polynomial msg_poly(msg, m_rlwe_sk->param()->size(), m_rlwe_sk->param()->modulus());
    std::vector<std::shared_ptr<RLWECT>> gadget_ct = ext_enc(msg_poly); 
    return std::make_shared<ExtendedRLWECT>(m_rlwe_sk->param(), m_gadget, gadget_ct);
}
 
std::shared_ptr<ExtendedPolynomialCT> RLWEGadgetSK::extended_encrypt(const std::vector<int64_t>& msg)const{
    if(msg.size() > m_rlwe_sk->param()->size()){
        throw std::logic_error("GadgetVectorCT* RLWEGadgetSK::gadget_encrypt(int64_t *msg, int32_t size): size of the message array too big.");
    }
    Polynomial msg_poly(msg, m_rlwe_sk->param()->size(), m_rlwe_sk->param()->modulus()); 
    std::vector<std::shared_ptr<RLWECT>> gadget_ct = ext_enc(msg_poly); 
    return std::make_shared<ExtendedRLWECT>(m_rlwe_sk->param(), m_gadget, gadget_ct); 
}


std::shared_ptr<RLWEParam> RLWEGadgetSK::param()const{
    return static_pointer_cast<RLWEParam>(m_vector_ct_param);
}

