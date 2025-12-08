#include "ciphertexts/ntru.h" 

using namespace FHEDeck;
 
NTRUParam::NTRUParam(RingType ring, int32_t ring_degree, uint64_t coef_modulus, PolynomialArithmetic arithmetic){
    m_coef_modulus = coef_modulus; 
    m_size = ring_degree;  
    m_ring = ring;  
    m_arithmetic = arithmetic;   
    init_mul_engine();
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
    mul_engine_builder.set_coef_modulus(m_coef_modulus); 
    mul_engine_builder.set_degree(m_size);
    mul_engine_builder.set_polynomial_arithmetic(m_arithmetic);
    mul_engine_builder.set_ring_type(m_ring); 
    m_mul_engine = mul_engine_builder.build();  
}
 
std::shared_ptr<VectorCT> NTRUParam::init_ct(std::shared_ptr<VectorCTParam> param){
    return std::make_shared<NTRUCT>(std::static_pointer_cast<NTRUParam>(param));
} 

uint64_t NTRUParam::modulus()const{
    return m_coef_modulus;
}

std::shared_ptr<PolynomialMultiplicationEngine> NTRUParam::mul_engine()const{
    return m_mul_engine;
}

RingType NTRUParam::ring()const{
    return m_ring;
}
  
NTRUCT::NTRUCT(std::shared_ptr<NTRUParam> param){
    m_param = param; 
    m_ct_poly = Polynomial(param->size(), param->modulus());  
    m_ct_poly.set_multiplication_engine(param->mul_engine());
}
 
NTRUCT::NTRUCT(std::shared_ptr<NTRUParam> param, const Polynomial& ct_poly){
    m_param = param;
    m_ct_poly = ct_poly;
    m_ct_poly.set_multiplication_engine(param->mul_engine());
}

NTRUCT::NTRUCT(std::shared_ptr<NTRUParam> param, Polynomial&& ct_poly){
    m_param = param;
    m_ct_poly = std::move(ct_poly);
    m_ct_poly.set_multiplication_engine(param->mul_engine());
}

NTRUCT::NTRUCT(const NTRUCT &other){ 
    m_param = other.m_param;
    m_ct_poly = other.m_ct_poly; 
}
 
NTRUCT& NTRUCT::operator=(const NTRUCT other){  
    m_param = other.m_param;
    m_ct_poly = other.m_ct_poly; 
    return *this;
}
  
void NTRUCT::negacyclic_rotate(NTRUCT &out, int32_t rot)const{   
    m_ct_poly.negacyclic_rotate(out.m_ct_poly, rot);  
}

void NTRUCT::cyclic_rotate(NTRUCT &out, int32_t rot)const{  
    NTRUCT &out_ptr = static_cast<NTRUCT&>(out); 
    m_ct_poly.cyclic_rotate(out_ptr.m_ct_poly, rot); 
}

void NTRUCT::homomorphic_rotate(VectorCT &out, int32_t rot)const{ 
    /// NOTE: What we do here, is realy multiplication with a monomial.
    if(m_param->ring() == RingType::negacyclic){ 
        negacyclic_rotate(static_cast<NTRUCT&>(out), rot);
    }else if(m_param->ring() == RingType::cyclic){
        cyclic_rotate(static_cast<NTRUCT&>(out), rot);
    }else{
        throw std::logic_error("NTRUCT::homomorphic_rotate(VectorCT *out, int rot): this->param->ring currently not supported.");
    }
}
 
void NTRUCT::add(VectorCT& out, const VectorCT &ct)const{  
    NTRUCT &out_ptr = static_cast<NTRUCT&>(out); 
    const NTRUCT &ct_ptr = static_cast<const NTRUCT&>(ct);
    ct_ptr.m_ct_poly.add(out_ptr.m_ct_poly, m_ct_poly); 
}
  
void NTRUCT::add(NTRUCT &out, const Polynomial &x)const{
    m_ct_poly.add(out.m_ct_poly, x); 
}
 
void NTRUCT::sub(VectorCT &out, const VectorCT &ct)const{  
    NTRUCT &out_ptr = static_cast<NTRUCT&>(out);
    const NTRUCT &ct_ptr = static_cast<const NTRUCT&>(ct);
    m_ct_poly.sub(out_ptr.m_ct_poly, ct_ptr.m_ct_poly); 
}
  
void NTRUCT::sub(NTRUCT &out, const Polynomial &x)const{
    m_ct_poly.sub(out.m_ct_poly, x);  
}

void NTRUCT::neg(VectorCT &out)const{
    NTRUCT &out_ptr = static_cast<NTRUCT&>(out); 
    m_ct_poly.neg(out_ptr.m_ct_poly); 
}
  
void NTRUCT::mul(NTRUCT &out, const Polynomial &x)const{ 
    m_param->mul_engine()->mul(out.m_ct_poly, m_ct_poly, x); 
}
 
std::string NTRUCT::to_string()const{
    std::string out = "[" + m_ct_poly.to_string(m_ct_poly.size()) + "]";
    return out;
}

const Polynomial& NTRUCT::ct_poly()const{
    return m_ct_poly;
}
  
void NTRUCT::extract_lwe(LWECT &out)const{
    out[0] = 0; 
    for(int32_t i = 1; i < out.param()->dim()+1; ++i){
        out[i] = m_ct_poly[i-1];
    } 
}
      
NTRUGadgetCT::NTRUGadgetCT(std::shared_ptr<NTRUParam> ntru_param, std::shared_ptr<Gadget> gadget, std::vector<std::shared_ptr<NTRUCT>> &gadget_ct){
    m_ntru_param = ntru_param;
    m_gadget = gadget;
    init(gadget_ct);
}

void NTRUGadgetCT::init(std::vector<std::shared_ptr<NTRUCT>> &gadget_ct){     
    PolynomialArray array_coef(m_ntru_param->size(),  
                                            m_ntru_param->modulus(),  
                                            m_gadget->digits);  
  

    m_array_eval_a = std::shared_ptr<PolynomialArrayEvalForm>(m_ntru_param->mul_engine()->init_polynomial_array_eval_form(m_gadget->digits)); 

    for(int32_t i = 0; i < m_gadget->digits; ++i){ 
        array_coef.set_polynomial_at(i, gadget_ct[i]->ct_poly());
    }  
    m_ntru_param->mul_engine()->to_eval(*m_array_eval_a, array_coef);   
}
  
void NTRUGadgetCT::mul(VectorCT &out, const VectorCT &ct){
    NTRUCT& out_ptr = static_cast<NTRUCT&>(out);
    const NTRUCT& ct_ptr = static_cast<const NTRUCT&>(ct); 
    PolynomialArray deter_ct_a_dec_poly(m_ntru_param->size(), m_ntru_param->modulus(), m_gadget->digits); 
    m_gadget->sample(deter_ct_a_dec_poly, ct_ptr.ct_poly());
    Polynomial ct_poly(m_ntru_param->size(), m_ntru_param->modulus());
    m_ntru_param->mul_engine()->multisum(ct_poly, deter_ct_a_dec_poly, *m_array_eval_a);
    out_ptr = NTRUCT(m_ntru_param, std::move(ct_poly));
}

void NTRUGadgetCT::mul(VectorCT &out, const Vector &scalar){
    NTRUCT& out_ptr = static_cast<NTRUCT&>(out);  
    PolynomialArray deter_ct_a_dec_poly(m_ntru_param->size(), m_ntru_param->modulus(), m_gadget->digits); 
    m_gadget->sample(deter_ct_a_dec_poly, scalar);
    Polynomial ct_poly(m_ntru_param->size(), m_ntru_param->modulus());
    m_ntru_param->mul_engine()->multisum(ct_poly, deter_ct_a_dec_poly, *m_array_eval_a);
    out_ptr = NTRUCT(m_ntru_param, std::move(ct_poly));
}
 
NTRUSK::NTRUSK(std::shared_ptr<NTRUParam> param, double noise_stddev){ 
    m_param = param; 
    m_noise_stddev = noise_stddev; 
    init();
    key_gen(); 
}
 
void NTRUSK::init(){
    m_vector_ct_param = m_param;
    m_error_dist = std::shared_ptr<Distribution>(new StandardRoundedGaussianDistribution(0, m_noise_stddev));
    m_sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(-1, 1)); 
}

void NTRUSK::key_gen(){   
    m_sk = Polynomial(m_param->size(), m_param->modulus()); 
    m_inv_sk = Polynomial(m_param->size(), m_param->modulus());    
    PolynomialInversionEngineBuilder inv_engine_builder(m_param->size(), m_param->modulus());  
    std::shared_ptr<PolynomialInversionEngine> inv_engine = inv_engine_builder.build();
    bool has_inverse = false; 
    do{   
        m_sk_dist->fill(m_sk);     
        has_inverse = inv_engine->inv(m_inv_sk, m_sk);  
    }while(!has_inverse);      
}  
   
void NTRUSK::encrypt(VectorCT &out, const Vector &m){  
    NTRUCT& out_cast = static_cast<NTRUCT&>(out);
    if(m.size() != m_param->size()){
        throw std::logic_error("NTRUSK::encrypt(VectorCT &out, const Vector &m): Input Vector m, size is too big!");
    }
    if(m.modulus() > m_param->modulus()){
        throw std::logic_error("NTRUSK::encrypt(VectorCT &out, const Vector &m): Input polynomial m, coefficient modulus is too big!");
    }  
    /// NOTE: We compute inv_sk * g + e + msg
    Polynomial g = Polynomial(m_param->size(), m_param->modulus()); 
    m_sk_dist->fill(g);
    Polynomial e = Polynomial(m_param->size(), m_param->modulus()); 
    m_error_dist->fill(e); 
    Polynomial ct_poly(m_param->size(), m_param->modulus());
    m_inv_sk.mul(ct_poly, g, m_param->mul_engine());
    ct_poly.add(ct_poly, e);
    ct_poly.add(ct_poly, m);
    out_cast = NTRUCT(m_param, ct_poly);
}

std::shared_ptr<VectorCT> NTRUSK::encrypt(const Vector &m){   
    std::shared_ptr<NTRUCT> out = std::make_shared<NTRUCT>(m_param);  
    this->encrypt(*out, m);
    return out;
}

std::shared_ptr<VectorCT> NTRUSK::encode_and_encrypt(const Vector &m, PlaintextEncoding encoding){ 
    std::shared_ptr<NTRUCT> out = std::make_shared<NTRUCT>(m_param);  
    this->encode_and_encrypt(*out, m, encoding);
    return out;
}

void NTRUSK::encode_and_encrypt(VectorCT& out, const Vector &m, PlaintextEncoding encoding){ 
    Polynomial m_scaled(m_param->size(), m_param->modulus()); 
    for(int32_t i = 0; i < m_param->size(); ++i){ 
        m_scaled[i] = encoding.encode_message(m[i]);
    }
    encrypt(out, m_scaled); 
}
 
void NTRUSK::partial_decrypt(Polynomial &phase, const NTRUCT &ct){   
    if(phase.size() != m_param->size()){
        throw std::logic_error("NTRUSK::phase(Polynomial *phase, RLWECT *ct): Dimension of the input polynomial differs from the the RLWE polynomials.");
    }
    if(phase.modulus() != m_param->modulus()){
        throw std::logic_error("NTRUSK::phase(Polynomial *phase, RLWECT *ct): Coefficient modulus of the input polynomial differs from the the RLWE polynomials.");
    } 
    m_sk.mul(phase, ct.ct_poly(), m_param->mul_engine()); 
}

std::shared_ptr<Vector> NTRUSK::decrypt(const VectorCT &ct, PlaintextEncoding encoding){ 
    std::shared_ptr<Polynomial> out = std::make_shared<Polynomial>(m_param->size(), m_param->modulus());
    decrypt(*out, ct, encoding);  
    return out;
}

void NTRUSK::decrypt(Vector &out, const VectorCT &ct, PlaintextEncoding encoding){   
    const NTRUCT& ct_cast = static_cast<const NTRUCT&>(ct);
    Polynomial& out_cast =  static_cast<Polynomial&>(out);
    Polynomial phase(m_param->size(), m_param->modulus());
    partial_decrypt(phase, ct_cast);  
    for(int32_t i = 0; i < out_cast.size(); ++i){
        out_cast[i] = encoding.decode_message(phase[i]);
    } 
}
 
std::shared_ptr<NTRUCT> NTRUSK::kdm_encrypt(const Polynomial& msg){
    std::shared_ptr<NTRUCT> out = std::make_shared<NTRUCT>(m_param);
    kdm_encrypt(*out, msg);
    return out;
} 

void NTRUSK::kdm_encrypt(NTRUCT &out, const Polynomial& msg){
    Polynomial kdm_msg(m_param->size(), m_param->modulus());
    m_inv_sk.mul(kdm_msg, msg, m_param->mul_engine());
    encrypt(out, kdm_msg);
}
 
void NTRUSK::kdm_encode_and_encrypt(NTRUCT &out, const Polynomial& msg, PlaintextEncoding encoding){
    Polynomial m_scaled(m_param->size(), m_param->modulus()); 
    for(int32_t i = 0; i < m_param->size(); ++i){ 
        m_scaled[i] = encoding.encode_message(msg[i]);
    }
    kdm_encrypt(out, m_scaled);  
}
 
std::shared_ptr<NTRUCT> NTRUSK::kdm_encode_and_encrypt(const Polynomial& msg, PlaintextEncoding encoding){
    Polynomial m_scaled(m_param->size(), m_param->modulus()); 
    for(int32_t i = 0; i < m_param->size(); ++i){ 
        m_scaled[i] = encoding.encode_message(msg[i]);
    }
    std::shared_ptr<NTRUCT> out = std::make_shared<NTRUCT>(m_param);
    kdm_encrypt(*out, m_scaled);  
    return out;
}
 
std::shared_ptr<LWESK> NTRUSK::extract_lwe_key(){
    std::shared_ptr<int64_t[]> extract_key(new int64_t[m_param->size()]); 
    std::shared_ptr<LWEParam> lwe_param(new LWEParam(m_param->size(), m_param->modulus())); 
    extract_key[0] = Utils::integer_mod_form(m_sk[0], m_param->modulus());
    for(int32_t i = 1; i <  m_param->size(); ++i){   
        extract_key[i] = m_param->modulus() - m_sk[m_param->size() - i];
    } 
    std::shared_ptr<LWESK> key = std::make_shared<LWESK>(lwe_param, extract_key.get(), m_noise_stddev, KeyDistribution::ternary); 
    return key;
}

std::shared_ptr<NTRUParam> NTRUSK::param()const{
    return m_param;
}
 
NTRUGadgetSK::NTRUGadgetSK(std::shared_ptr<Gadget> gadget, std::shared_ptr<NTRUSK> sk){ 
    m_gadget = gadget; 
    m_vector_ct_param = sk->vector_ct_param();
    m_sk = sk; 
    m_secret_key = sk;
}
 
std::shared_ptr<GadgetVectorCT> NTRUGadgetSK::gadget_encrypt(const Vector &msg)const{    
    if(msg.modulus() > m_sk->param()->modulus()){ throw std::logic_error("NTRUGadgetSK::gadget_encrypt(const Vector &msg): modulus bigger"); }

    if(msg.size() != m_sk->param()->size()){ throw std::logic_error("NTRUGadgetSK::gadget_encrypt(const Vector &msg): size different"); }

    Polynomial msg_poly(msg, m_sk->param()->size(), m_sk->param()->modulus());
    std::vector<std::shared_ptr<NTRUCT>> gadget_ct = ext_enc(msg_poly);   
    return std::make_shared<NTRUGadgetCT>(m_sk->param(), m_gadget, gadget_ct);
}
 
std::shared_ptr<GadgetVectorCT> NTRUGadgetSK::gadget_encrypt(const std::vector<int64_t>& msg)const{
    if(msg.size() > m_sk->param()->size()){
        throw std::logic_error("GadgetVectorCT* NTRUGadgetSK::gadget_encrypt(uint64_t *msg, int32_t size): size of the message array too big.");
    }
    Polynomial msg_poly(msg, m_sk->param()->size(), m_sk->param()->modulus()); 
    return gadget_encrypt(msg_poly);
}
 
std::shared_ptr<GadgetVectorCT> NTRUGadgetSK::kdm_gadget_encrypt(const Polynomial &msg)const{

    if(msg.modulus() > m_sk->param()->modulus()){ throw std::logic_error("NTRUGadgetSK::kdm_gadget_encrypt(const Polynomial &msg): modulus too big"); }

    if(msg.size() != m_sk->param()->size()){ throw std::logic_error("NTRUGadgetSK::kdm_gadget_encrypt(const Polynomial &msg): size different"); }
 
    std::vector<std::shared_ptr<NTRUCT>> gadget_ct = ext_enc(msg);    
    return std::make_shared<NTRUGadgetCT>(m_sk->param(), m_gadget, gadget_ct);
} 

std::shared_ptr<GadgetVectorCT> NTRUGadgetSK::kdm_gadget_encrypt(const std::vector<int64_t>& msg)const{
    if(msg.size() > m_sk->param()->size()){
        throw std::logic_error("GadgetVectorCT* NTRUGadgetSK::gadget_encrypt(uint64_t *msg, int32_t size): size of the message array too big.");
    }
    Polynomial msg_poly(msg, m_sk->param()->size(), m_sk->param()->modulus()); 
    return kdm_gadget_encrypt(msg_poly);
} 
  
std::shared_ptr<ExtendedPolynomialCT> NTRUGadgetSK::extended_encrypt(const Vector &msg)const{      
    if(msg.modulus() > m_sk->param()->modulus()){ throw std::logic_error("NTRUGadgetSK::extended_encrypt(const Polynomial &msg): modulus too big"); }

    if(msg.size() != m_sk->param()->size()){ throw std::logic_error("NTRUGadgetSK::extended_encrypt(const Polynomial &msg): size different"); }
 
    std::vector<std::shared_ptr<NTRUCT>> gadget_ct = ext_enc(msg);     
    return std::make_shared<NTRUGadgetCT>(m_sk->param(), m_gadget, gadget_ct);
}
 
std::shared_ptr<ExtendedPolynomialCT> NTRUGadgetSK::extended_encrypt(const std::vector<int64_t>& msg)const{
    if(msg.size() > m_sk->param()->size()){
        throw std::logic_error("GadgetVectorCT* NTRUGadgetSK::gadget_encrypt(uint64_t *msg, int32_t size): size of the message array too big.");
    } 
    Polynomial msg_poly(msg, m_sk->param()->size(), m_sk->param()->modulus()); 
    return extended_encrypt(msg_poly);
}
 
std::vector<std::shared_ptr<NTRUCT>> NTRUGadgetSK::ext_enc(const Vector &msg)const{
    std::vector<std::shared_ptr<NTRUCT>> gadget_ct;       
    Polynomial msg_cpy(msg);  
    // Encryptions of - msg* base**i     
    gadget_ct.push_back(std::static_pointer_cast<NTRUCT>(m_sk->encrypt(msg)));
    for(int32_t i = 1; i < m_gadget->digits; ++i){
        // Multiply msg by base
        msg_cpy.mul(msg_cpy, m_gadget->base); 
        // Encrypt msg * base**i   
        gadget_ct.push_back(std::static_pointer_cast<NTRUCT>(m_sk->encrypt(msg_cpy))); 
    }    
    return gadget_ct;
}