#include "ciphertexts/ntru.h" 

using namespace FHEDeck;
 
NTRUParam::NTRUParam(RingType ring, int32_t ring_degree, uint64_t coef_modulus, PolynomialArithmetic arithmetic){
    this->coef_modulus = coef_modulus; 
    this->size = ring_degree;  
    this->ring = ring;  
    this->arithmetic = arithmetic;   
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
    mul_engine_builder.set_coef_modulus(coef_modulus); 
    mul_engine_builder.set_degree(size);
    mul_engine_builder.set_polynomial_arithmetic(arithmetic);
    mul_engine_builder.set_ring_type(ring); 
    this->mul_engine = mul_engine_builder.build(); 
    this->is_mul_engine_init = true;
}
 
std::shared_ptr<VectorCT> NTRUParam::init_ct(std::shared_ptr<VectorCTParam> param){
    return std::make_shared<NTRUCT>(std::static_pointer_cast<NTRUParam>(param));
} 
  
NTRUCT::NTRUCT(std::shared_ptr<NTRUParam> param){
    this->param = param; 
    this->ct_poly = Polynomial(param->size, param->coef_modulus);  
    this->ct_poly.set_multiplication_engine(param->mul_engine);
}
 
NTRUCT::NTRUCT(const NTRUCT &other){ 
    this->param = other.param;
    this->ct_poly = other.ct_poly; 
}
 
NTRUCT& NTRUCT::operator=(const NTRUCT other){  
    this->param = other.param;
    this->ct_poly = other.ct_poly; 
    return *this;
}
  
void NTRUCT::negacyclic_rotate(NTRUCT &out, int32_t rot){   
    ct_poly.negacyclic_rotate(out.ct_poly, rot);  
}

void NTRUCT::cyclic_rotate(NTRUCT &out, int32_t rot){  
    NTRUCT &out_ptr = static_cast<NTRUCT&>(out); 
    ct_poly.cyclic_rotate(out_ptr.ct_poly, rot); 
}

void NTRUCT::homomorphic_rotate(VectorCT &out, int32_t rot){ 
    /// NOTE: What we do here, is realy multiplication with a monomial.
    if(this->param->ring == RingType::negacyclic){ 
        negacyclic_rotate(static_cast<NTRUCT&>(out), rot);
    }else if(this->param->ring == RingType::cyclic){
        cyclic_rotate(static_cast<NTRUCT&>(out), rot);
    }else{
        throw std::logic_error("NTRUCT::homomorphic_rotate(VectorCT *out, int rot): this->param->ring currently not supported.");
    }
}
 
void NTRUCT::add(VectorCT& out, const VectorCT &ct){  
    NTRUCT &out_ptr = static_cast<NTRUCT&>(out); 
    const NTRUCT &ct_ptr = static_cast<const NTRUCT&>(ct);
    ct_ptr.ct_poly.add(out_ptr.ct_poly, ct_poly); 
}
  
void NTRUCT::add(NTRUCT &out, const Polynomial &x){
    ct_poly.add(out.ct_poly, x); 
}
 
void NTRUCT::sub(VectorCT &out, const VectorCT &ct){  
    NTRUCT &out_ptr = static_cast<NTRUCT&>(out);
    const NTRUCT &ct_ptr = static_cast<const NTRUCT&>(ct);
    ct_poly.sub(out_ptr.ct_poly, ct_ptr.ct_poly); 
}
  
void NTRUCT::sub(NTRUCT &out, const Polynomial &x){
    ct_poly.sub(out.ct_poly, x);  
}

void NTRUCT::neg(VectorCT &out){
    NTRUCT &out_ptr = static_cast<NTRUCT&>(out); 
    ct_poly.neg(out_ptr.ct_poly); 
}
  
void NTRUCT::mul(NTRUCT &out, const Polynomial &x){ 
    param->mul_engine->mul(out.ct_poly, ct_poly, x); 
}
 
std::string NTRUCT::to_string(){
    std::string out = "[" + ct_poly.to_string(ct_poly.size) + "]";
    return out;
}
  
void NTRUCT::extract_lwe(LWECT &out){
    out.ct[0] = 0; 
    for(int32_t i = 1; i < out.param->dim+1; ++i){
        out.ct[i] = ct_poly[i-1];
    } 
}
      
NTRUGadgetCT::NTRUGadgetCT(std::shared_ptr<NTRUParam> ntru_param, std::shared_ptr<Gadget> gadget, std::vector<std::shared_ptr<NTRUCT>> &gadget_ct){
    this->ntru_param = ntru_param;
    this->gadget = gadget;
    this->init(gadget_ct);
}

void NTRUGadgetCT::init(std::vector<std::shared_ptr<NTRUCT>> &gadget_ct){     
    PolynomialArrayCoefForm array_coef(ntru_param->size,  
                                            ntru_param->coef_modulus,  
                                            gadget->digits);  
  

     this->array_eval_a = std::shared_ptr<PolynomialArrayEvalForm>(ntru_param->mul_engine->init_polynomial_array_eval_form(gadget->digits)); 

    for(int32_t i = 0; i < gadget->digits; ++i){ 
        array_coef.set_polynomial_at(i, gadget_ct[i]->ct_poly);
    }  
    ntru_param->mul_engine->to_eval(*array_eval_a, array_coef);  
     
    this->is_init = true; 
}

NTRUGadgetCT::~NTRUGadgetCT(){     
    if(is_init == false){
        return;
    }        
}
 
NTRUGadgetCT::NTRUGadgetCT(const NTRUGadgetCT& other){    
    throw std::runtime_error("NTRUGadgetCT::NTRUGadgetCT(const RLWEGadgetCT& other)");
}

NTRUGadgetCT& NTRUGadgetCT::operator=(NTRUGadgetCT other){  
    throw std::runtime_error("NTRUGadgetCT& NTRUGadgetCT::operator=(NTRUGadgetCT other)");
    return *this;
}
  
void NTRUGadgetCT::mul(VectorCT &out, const VectorCT &ct){
    NTRUCT& out_ptr = static_cast<NTRUCT&>(out);
    const NTRUCT& ct_ptr = static_cast<const NTRUCT&>(ct); 
    PolynomialArrayCoefForm deter_ct_a_dec_poly(ntru_param->size, ntru_param->coef_modulus, gadget->digits); 
    gadget->sample(deter_ct_a_dec_poly, ct_ptr.ct_poly.vec);
    ntru_param->mul_engine->multisum(out_ptr.ct_poly, deter_ct_a_dec_poly, *array_eval_a);
}

void NTRUGadgetCT::mul(VectorCT &out, const Polynomial &scalar){
    NTRUCT& out_ptr = static_cast<NTRUCT&>(out);  
    PolynomialArrayCoefForm deter_ct_a_dec_poly(ntru_param->size, ntru_param->coef_modulus, gadget->digits); 
    gadget->sample(deter_ct_a_dec_poly, scalar.vec);
    ntru_param->mul_engine->multisum(out_ptr.ct_poly, deter_ct_a_dec_poly, *array_eval_a);
}
 
NTRUSK::NTRUSK(std::shared_ptr<NTRUParam> param, double noise_stddev){ 
    this->param = param; 
    this->noise_stddev = noise_stddev; 
    init();
    key_gen(); 
}
 
void NTRUSK::init(){
    this->vector_ct_param = this->param;
    this->error_dist = std::shared_ptr<Distribution>(new StandardRoundedGaussianDistribution(0, noise_stddev));
    this->sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(-1, 1)); 
}

void NTRUSK::key_gen(){   
    this->sk = Polynomial(param->size, param->coef_modulus); 
    this->inv_sk = Polynomial(param->size, param->coef_modulus);    
    PolynomialInversionEngineBuilder inv_engine_builder(param->size, param->coef_modulus);  
    std::shared_ptr<PolynomialInversionEngine> inv_engine = inv_engine_builder.build();
    bool has_inverse = false; 
    do{  
        sk_dist->fill_array(this->sk.vec, param->size);    
        Utils::array_mod_form(this->sk.vec, this->sk.vec, param->size, param->coef_modulus);   
        has_inverse = inv_engine->inv(this->inv_sk, this->sk);  
    }while(!has_inverse);      
}  
   
void NTRUSK::encrypt(VectorCT &out, const Vector &m){  
    NTRUCT& out_cast = static_cast<NTRUCT&>(out);
    if(m.size < param->size){
        throw std::logic_error("NTRUSK::encrypt(Polynomial *m): Input polynomial m, degree is too big!");
    }
    if(m.modulus < param->coef_modulus){
        throw std::logic_error("NTRUSK::encrypt(Polynomial *m): Input polynomial m, coefficient codulus is too big!");
    }
    if(!m.is_init){
        throw std::logic_error("NTRUSK::encrypt(Polynomial *m): Input polynomial m is not initialized!");
    }  
    /// NOTE: We compute inv_sk * g + e + msg
    Polynomial g = Polynomial(param->size, param->coef_modulus);
    sk_dist->fill_array(g.vec, g.size);
    Polynomial e = Polynomial(param->size, param->coef_modulus);
    error_dist->fill_array(e.vec, e.size); 
    inv_sk.mul(out_cast.ct_poly, g, param->mul_engine);
    out_cast.ct_poly.add(out_cast.ct_poly, e);
    out_cast.ct_poly.add(out_cast.ct_poly, m);
}

std::shared_ptr<VectorCT> NTRUSK::encrypt(const Vector &m){   
    std::shared_ptr<NTRUCT> out = std::make_shared<NTRUCT>(param);  
    this->encrypt(*out, m);
    return out;
}

std::shared_ptr<VectorCT> NTRUSK::encode_and_encrypt(const Vector &m, PlaintextEncoding encoding){ 
    std::shared_ptr<NTRUCT> out = std::make_shared<NTRUCT>(param);  
    this->encode_and_encrypt(*out, m, encoding);
    return out;
}

void NTRUSK::encode_and_encrypt(VectorCT& out, const Vector &m, PlaintextEncoding encoding){ 
    Polynomial m_scaled(param->size, param->coef_modulus); 
    for(int32_t i = 0; i < param->size; ++i){ 
        m_scaled[i] = encoding.encode_message(m.vec[i]);
    }
    encrypt(out, m_scaled); 
}
 
void NTRUSK::partial_decrypt(Polynomial &phase, const NTRUCT &ct){   
    if(phase.size != param->size){
        throw std::logic_error("NTRUSK::phase(Polynomial *phase, RLWECT *ct): Dimension of the input polynomial differs from the the RLWE polynomials.");
    }
    if(phase.modulus != param->coef_modulus){
        throw std::logic_error("NTRUSK::phase(Polynomial *phase, RLWECT *ct): Coefficient modulus of the input polynomial differs from the the RLWE polynomials.");
    }
    if(!phase.is_init){
        throw std::logic_error("NTRUSK::phase(Polynomial *phase, RLWECT *ct): Input polynomial is not initialized.");
    } 
    sk.mul(phase, ct.ct_poly, param->mul_engine); 
}

std::shared_ptr<Vector> NTRUSK::decrypt(const VectorCT &ct, PlaintextEncoding encoding){ 
    std::shared_ptr<Polynomial> out = std::make_shared<Polynomial>(param->size, param->coef_modulus);
    decrypt(*out, ct, encoding);  
    return out;
}

void NTRUSK::decrypt(Vector &out, const VectorCT &ct, PlaintextEncoding encoding){   
    const NTRUCT& ct_cast = static_cast<const NTRUCT&>(ct);
    Polynomial& out_cast =  static_cast<Polynomial&>(out);
    Polynomial phase(this->param->size, this->param->coef_modulus);
    this->partial_decrypt(phase, ct_cast);  
    for(int32_t i = 0; i < out_cast.size; ++i){
        out_cast.vec[i] = encoding.decode_message(phase.vec[i]);
    } 
}
 
std::shared_ptr<NTRUCT> NTRUSK::kdm_encrypt(const Polynomial& msg){
    std::shared_ptr<NTRUCT> out = std::make_shared<NTRUCT>(param);
    kdm_encrypt(*out, msg);
    return out;
} 

void NTRUSK::kdm_encrypt(NTRUCT &out, const Polynomial& msg){
    Polynomial kdm_msg(param->size, param->coef_modulus);
    inv_sk.mul(kdm_msg, msg, param->mul_engine);
    encrypt(out, kdm_msg);
}
 
void NTRUSK::kdm_encode_and_encrypt(NTRUCT &out, const Polynomial& msg, PlaintextEncoding encoding){
    Polynomial m_scaled(param->size, param->coef_modulus); 
    for(int32_t i = 0; i < param->size; ++i){ 
        m_scaled[i] = encoding.encode_message(msg[i]);
    }
    kdm_encrypt(out, m_scaled);  
}
 
std::shared_ptr<NTRUCT> NTRUSK::kdm_encode_and_encrypt(const Polynomial& msg, PlaintextEncoding encoding){
    Polynomial m_scaled(param->size, param->coef_modulus); 
    for(int32_t i = 0; i < param->size; ++i){ 
        m_scaled[i] = encoding.encode_message(msg[i]);
    }
    std::shared_ptr<NTRUCT> out = std::make_shared<NTRUCT>(param);
    kdm_encrypt(*out, m_scaled);  
    return out;
}
 
std::shared_ptr<LWESK> NTRUSK::extract_lwe_key(){
    std::shared_ptr<int64_t[]> extract_key(new int64_t[param->size]); 
    std::shared_ptr<LWEParam> lwe_param(new LWEParam(param->size, param->coef_modulus)); 
    extract_key[0] = Utils::integer_mod_form(this->sk[0], param->coef_modulus);
    for(int32_t i = 1; i <  param->size; ++i){   
        extract_key[i] = param->coef_modulus-this->sk[param->size - i];
    } 
    std::shared_ptr<LWESK> key = std::make_shared<LWESK>(lwe_param, extract_key.get(), this->noise_stddev, KeyDistribution::ternary); 
    return key;
}
 
NTRUGadgetSK::NTRUGadgetSK(std::shared_ptr<Gadget> gadget, std::shared_ptr<NTRUSK> sk){ 
    this->gadget = gadget; 
    this->vector_ct_param = sk->param;
    this->sk = sk; 
    this->secret_key = sk;
}
 
std::shared_ptr<GadgetVectorCT> NTRUGadgetSK::gadget_encrypt(const Vector &msg){     
    Polynomial msg_poly(msg.vec, sk->param->size, sk->param->coef_modulus);
    std::vector<std::shared_ptr<NTRUCT>> gadget_ct = ext_enc(msg_poly);   
    return std::make_shared<NTRUGadgetCT>(sk->param, gadget, gadget_ct);
}
 
std::shared_ptr<GadgetVectorCT> NTRUGadgetSK::gadget_encrypt(const uint64_t *msg, int32_t size){
    if(size > sk->param->size){
        throw std::logic_error("GadgetVectorCT* NTRUGadgetSK::gadget_encrypt(uint64_t *msg, int32_t size): size of the message array too big.");
    }
    Polynomial msg_poly(sk->param->size, sk->param->coef_modulus); 
    msg_poly.zeroize();
    for(int32_t i = 0; i < size; ++i){
        msg_poly[i] = msg[i];
    }
    return gadget_encrypt(msg_poly);
}
 
std::shared_ptr<GadgetVectorCT> NTRUGadgetSK::kdm_gadget_encrypt(const Polynomial &msg){
    std::vector<std::shared_ptr<NTRUCT>> gadget_ct = ext_enc(msg);    
    return std::make_shared<NTRUGadgetCT>(sk->param, gadget, gadget_ct);
} 

std::shared_ptr<GadgetVectorCT> NTRUGadgetSK::kdm_gadget_encrypt(const uint64_t *msg, int32_t size){
    if(size > sk->param->size){
        throw std::logic_error("GadgetVectorCT* NTRUGadgetSK::gadget_encrypt(uint64_t *msg, int32_t size): size of the message array too big.");
    }
    Polynomial msg_poly(sk->param->size, sk->param->coef_modulus); 
    msg_poly.zeroize();
    for(int32_t i = 0; i < size; ++i){
        msg_poly[i] = msg[i];
    }
    return kdm_gadget_encrypt(msg_poly);
} 
  
std::shared_ptr<ExtendedPolynomialCT> NTRUGadgetSK::extended_encrypt(const Polynomial &msg){      
    std::vector<std::shared_ptr<NTRUCT>> gadget_ct = ext_enc(msg);     
    return std::make_shared<NTRUGadgetCT>(sk->param, gadget, gadget_ct);
}
 
std::shared_ptr<ExtendedPolynomialCT> NTRUGadgetSK::extended_encrypt(const uint64_t *msg, int32_t size){
    if(size > sk->param->size){
        throw std::logic_error("GadgetVectorCT* NTRUGadgetSK::gadget_encrypt(uint64_t *msg, int32_t size): size of the message array too big.");
    }
    Polynomial msg_poly(sk->param->size, sk->param->coef_modulus); 
    msg_poly.zeroize();
    for(int32_t i = 0; i < size; ++i){
        msg_poly[i] = msg[i];
    }
    return extended_encrypt(msg_poly);
}
 
std::vector<std::shared_ptr<NTRUCT>> NTRUGadgetSK::ext_enc(const Polynomial &msg){
    std::vector<std::shared_ptr<NTRUCT>> gadget_ct;     
    std::shared_ptr<Polynomial> msg_cpy(msg.clone());  
    // Encryptions of - msg* base**i    
    std::dynamic_pointer_cast<NTRUCT>(sk->encrypt(msg));
    gadget_ct.push_back(std::static_pointer_cast<NTRUCT>(sk->encrypt(msg)));
    for(int32_t i = 1; i < gadget->digits; ++i){
        // Multiply msg by base
        msg_cpy->mul(*msg_cpy, gadget->base); 
        // Encrypt msg * base**i   
        gadget_ct.push_back(std::static_pointer_cast<NTRUCT>(sk->encrypt(*msg_cpy))); 
    }    
    return gadget_ct;
}