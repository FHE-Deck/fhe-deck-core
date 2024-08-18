#include "ntru.h" 

using namespace fhe_deck;
 
NTRUParam::NTRUParam(RingType ring, int32_t ring_degree, uint64_t coef_modulus, PolynomialArithmetic arithmetic){
    this->coef_modulus = coef_modulus;
    //this->mod_type = mod_type; 
    this->size = ring_degree;  
    this->ring = ring;  
    this->arithmetic = arithmetic;   
    init_mul_engine();
}
        
NTRUParam::NTRUParam(int32_t degree, uint64_t ring_degree, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine){
    this->size = ring_degree;
    this->coef_modulus = coef_modulus;
    //this->mod_type = mod_type; 
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
    //mul_engine_builder.set_modulus_type(mod_type);
    this->mul_engine = mul_engine_builder.build(); 
    this->is_mul_engine_init = true;
}
 
VectorCT* NTRUParam::init_ct(std::shared_ptr<VectorCTParam> param){
    return new NTRUCT(std::static_pointer_cast<NTRUParam>(param));
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
  
void NTRUCT::negacyclic_rotate(NTRUCT *out, int32_t rot){  
    NTRUCT *out_ptr = static_cast<NTRUCT*>(out); 
    ct_poly.negacyclic_rotate(&out_ptr->ct_poly, rot);  
}

void NTRUCT::cyclic_rotate(NTRUCT *out, int32_t rot){  
    NTRUCT *out_ptr = static_cast<NTRUCT*>(out); 
    ct_poly.cyclic_rotate(&out_ptr->ct_poly, rot); 
}

void NTRUCT::homomorphic_rotate(VectorCT *out, int32_t rot){ 
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
    ct_ptr->ct_poly.add(&out_ptr->ct_poly, &ct_poly); 
}
  
void NTRUCT::add(NTRUCT *out, Polynomial *x){
    ct_poly.add(&out->ct_poly, x); 
}
 
void NTRUCT::sub(VectorCT *out, VectorCT *ct){  
    NTRUCT *out_ptr = static_cast<NTRUCT*>(out);
    NTRUCT *ct_ptr = static_cast<NTRUCT*>(ct);
    ct_poly.sub(&out_ptr->ct_poly, &ct_ptr->ct_poly); 
}
  
void NTRUCT::sub(NTRUCT *out, Polynomial *x){
    ct_poly.sub(&out->ct_poly, x);  
}

void NTRUCT::neg(VectorCT *out){
    NTRUCT *out_ptr = static_cast<NTRUCT*>(out); 
    ct_poly.neg(&out_ptr->ct_poly); 
}
  
void NTRUCT::mul(NTRUCT *out, Polynomial *x){ 
    param->mul_engine->mul(&out->ct_poly, &ct_poly, x);
    //this->ct_poly.mul(&out->ct_poly, x, param->mul_engine); 
}
 
std::string NTRUCT::to_string(){
    std::string out = "[" + Utils::to_string(ct_poly.coefs, param->size) + "]";
    return out;
}
  
void NTRUCT::extract_lwe(LWECT *out){
    out->ct[0] = 0; 
    for(int32_t i = 1; i < out->param->dim+1; ++i){
        out->ct[i] = ct_poly.coefs[i-1];
    } 
}
      
NTRUGadgetCT::NTRUGadgetCT(std::shared_ptr<NTRUParam> ntru_param, std::shared_ptr<Gadget> gadget, std::vector<std::unique_ptr<NTRUCT>> &gadget_ct){
    this->ntru_param = ntru_param;
    this->gadget = gadget;
    this->init(gadget_ct);
}

void NTRUGadgetCT::init(std::vector<std::unique_ptr<NTRUCT>> &gadget_ct){     
    PolynomialArrayCoefForm array_coef(ntru_param->size,  
                                            ntru_param->coef_modulus,  
                                            gadget->digits);  
  

     this->array_eval_a = std::unique_ptr<PolynomialArrayEvalForm>(ntru_param->mul_engine->init_polynomial_array_eval_form(gadget->digits)); 

    for(int32_t i = 0; i < gadget->digits; ++i){ 
        array_coef.set_polynomial_at(i, &gadget_ct[i]->ct_poly);
    }  
    ntru_param->mul_engine->to_eval(array_eval_a.get(), &array_coef);  
    
    //init_gadget_decomp_tables();  
    //set_gadget_decomp_arrays();
    this->is_init = true; 
}

NTRUGadgetCT::~NTRUGadgetCT(){     
    if(is_init == false){
        return;
    }       
    //delete[] deter_ct_a_dec;
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
    PolynomialArrayCoefForm deter_ct_a_dec_poly(ntru_param->size, ntru_param->coef_modulus, gadget->digits); 
    gadget->sample(&deter_ct_a_dec_poly, ct_ptr->ct_poly.coefs);
    ntru_param->mul_engine->multisum(&out_ptr->ct_poly, &deter_ct_a_dec_poly, array_eval_a.get());
}

void NTRUGadgetCT::mul(VectorCT *out, const Polynomial *scalar){
    NTRUCT* out_ptr = static_cast<NTRUCT*>(out);  
    PolynomialArrayCoefForm deter_ct_a_dec_poly(ntru_param->size, ntru_param->coef_modulus, gadget->digits); 
    gadget->sample(&deter_ct_a_dec_poly, scalar->coefs);
    ntru_param->mul_engine->multisum(&out_ptr->ct_poly, &deter_ct_a_dec_poly, array_eval_a.get());
}
 
NTRUSK::NTRUSK(std::shared_ptr<NTRUParam> param, double noise_stddev){ 
    this->param = param; 
    this->noise_stddev = noise_stddev; 
    this->error_dist = std::shared_ptr<Distribution>(new StandardRoundedGaussianDistribution(0, noise_stddev));
    this->sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(-1, 1)); 
    key_gen(); 
}
 
void NTRUSK::key_gen(){ 
    int32_t status = 1;   
    NTL::ZZ_pX temp_f;
    NTL::ZZ_pX temp_inv_f;
    this->sk = Polynomial(param->size, param->coef_modulus); 
    do{  
        sk_dist->fill_array(this->sk.coefs, param->size);   
        Utils::array_mod_form(this->sk.coefs, this->sk.coefs, param->size, param->coef_modulus);
        Utils::set_polynomial_from_array(temp_f, this->sk.coefs, param->size, param->coef_modulus);
        status = NTL::InvModStatus(temp_inv_f, temp_f, Utils::get_ring_poly(negacyclic, param->size, param->coef_modulus));  
    }while(status == 1); 
    this->inv_sk = Polynomial(param->size, param->coef_modulus);  
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
    Polynomial g = Polynomial(param->size, param->coef_modulus);
    sk_dist->fill_array(g.coefs, g.degree);
    Polynomial e = Polynomial(param->size, param->coef_modulus);
    error_dist->fill_array(e.coefs, e.degree); 
    inv_sk.mul(&out->ct_poly, &g, param->mul_engine);
    out->ct_poly.add(&out->ct_poly, &e);
    out->ct_poly.add(&out->ct_poly, m);
}

NTRUCT* NTRUSK::encrypt(Polynomial *m){   
    NTRUCT* out = new NTRUCT(param);  
    this->encrypt(out, m);
    return out;
}

NTRUCT* NTRUSK::encode_and_encrypt(Polynomial* m, PlaintextEncoding encoding){ 
    Polynomial m_scaled(param->size, param->coef_modulus); 
    for(int32_t i = 0; i < param->size; ++i){ 
        m_scaled.coefs[i] = encoding.encode_message(m->coefs[i]);
    }
    return encrypt(&m_scaled); 
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
    sk.mul(phase, &ct->ct_poly, param->mul_engine); 
}

Polynomial* NTRUSK::decrypt(NTRUCT *ct, PlaintextEncoding encoding){ 
    Polynomial* out = new Polynomial(param->size, param->coef_modulus);
    decrypt(out, ct, encoding);  
    return out;
}

void NTRUSK::decrypt(Polynomial *out, NTRUCT *ct, PlaintextEncoding encoding){   
    this->partial_decrypt(out, ct);  
    for(int32_t i = 0; i < out->degree; ++i){
        out->coefs[i] = encoding.decode_message(out->coefs[i]);
    } 
}
 
NTRUCT* NTRUSK::kdm_encrypt(Polynomial* msg){
    NTRUCT* out = new NTRUCT(param);
    kdm_encrypt(out, msg);
    return out;
} 

void NTRUSK::kdm_encrypt(NTRUCT *out, Polynomial* msg){
    Polynomial kdm_msg(param->size, param->coef_modulus);
    inv_sk.mul(&kdm_msg, msg, param->mul_engine);
    encrypt(out, &kdm_msg);
}
 
void NTRUSK::kdm_encode_and_encrypt(NTRUCT *out, Polynomial* msg, PlaintextEncoding encoding){
    Polynomial m_scaled(param->size, param->coef_modulus); 
    for(int32_t i = 0; i < param->size; ++i){ 
        m_scaled.coefs[i] = encoding.encode_message(msg->coefs[i]);
    }
    kdm_encrypt(out, &m_scaled);  
}
 
NTRUCT* NTRUSK::kdm_encode_and_encrypt(Polynomial* msg, PlaintextEncoding encoding){
    Polynomial m_scaled(param->size, param->coef_modulus); 
    for(int32_t i = 0; i < param->size; ++i){ 
        m_scaled.coefs[i] = encoding.encode_message(msg->coefs[i]);
    }
    NTRUCT* out = new NTRUCT(param);
    kdm_encrypt(out, &m_scaled);  
    return out;
}
 
LWESK* NTRUSK::extract_lwe_key(){
    std::unique_ptr<int64_t[]> extract_key(new int64_t[param->size]); 
    std::shared_ptr<LWEParam> lwe_param(new LWEParam(param->size, param->coef_modulus)); 
    extract_key[0] = Utils::integer_mod_form(this->sk.coefs[0], param->coef_modulus);
    for(int32_t i = 1; i <  param->size; ++i){   
        extract_key[i] = param->coef_modulus-this->sk.coefs[param->size - i];
    } 
    LWESK* key = new LWESK(lwe_param, extract_key.get(), this->noise_stddev, ternary); 
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
  
GadgetVectorCT* NTRUGadgetSK::gadget_encrypt(Vector *msg){     
    Polynomial msg_poly(msg->vec, sk->param->size, sk->param->coef_modulus);
    std::vector<std::unique_ptr<NTRUCT>> gadget_ct = ext_enc(&msg_poly);   
    return new NTRUGadgetCT(sk->param, gadget, gadget_ct);
}
 
GadgetVectorCT* NTRUGadgetSK::gadget_encrypt(uint64_t *msg, int32_t size){
    if(size > sk->param->size){
        throw std::logic_error("GadgetVectorCT* NTRUGadgetSK::gadget_encrypt(uint64_t *msg, int32_t size): size of the message array too big.");
    }
    Polynomial msg_poly(sk->param->size, sk->param->coef_modulus); 
    msg_poly.zeroize();
    for(int32_t i = 0; i < size; ++i){
        msg_poly.coefs[i] = msg[i];
    }
    return gadget_encrypt(&msg_poly);
}
 
GadgetVectorCT* NTRUGadgetSK::kdm_gadget_encrypt(Polynomial *msg){
    std::vector<std::unique_ptr<NTRUCT>> gadget_ct = ext_enc(msg);    
    return new NTRUGadgetCT(sk->param, gadget, gadget_ct);
} 

GadgetVectorCT* NTRUGadgetSK::kdm_gadget_encrypt(uint64_t *msg, int32_t size){
    if(size > sk->param->size){
        throw std::logic_error("GadgetVectorCT* NTRUGadgetSK::gadget_encrypt(uint64_t *msg, int32_t size): size of the message array too big.");
    }
    Polynomial msg_poly(sk->param->size, sk->param->coef_modulus); 
    msg_poly.zeroize();
    for(int32_t i = 0; i < size; ++i){
        msg_poly.coefs[i] = msg[i];
    }
    return kdm_gadget_encrypt(&msg_poly);
} 
 

ExtendedPolynomialCT* NTRUGadgetSK::extended_encrypt(Polynomial *msg){      
    std::vector<std::unique_ptr<NTRUCT>> gadget_ct = ext_enc(msg);     
    return new NTRUGadgetCT(sk->param, gadget, gadget_ct);
}
 
ExtendedPolynomialCT* NTRUGadgetSK::extended_encrypt(uint64_t *msg, int32_t size){
    if(size > sk->param->size){
        throw std::logic_error("GadgetVectorCT* NTRUGadgetSK::gadget_encrypt(uint64_t *msg, int32_t size): size of the message array too big.");
    }
    Polynomial msg_poly(sk->param->size, sk->param->coef_modulus); 
    msg_poly.zeroize();
    for(int32_t i = 0; i < size; ++i){
        msg_poly.coefs[i] = msg[i];
    }
    return extended_encrypt(&msg_poly);
}


std::vector<std::unique_ptr<NTRUCT>> NTRUGadgetSK::ext_enc(Polynomial *msg){
    std::vector<std::unique_ptr<NTRUCT>> gadget_ct;     
    std::shared_ptr<Polynomial> msg_cpy(msg->clone());  
    // Encryptions of - msg* base**i    
    gadget_ct.push_back(std::unique_ptr<NTRUCT>(sk->encrypt(msg)));
    for(int32_t i = 1; i < gadget->digits; ++i){
        // Multiply msg by base
        msg_cpy->mul(msg_cpy.get(), gadget->base); 
        // Encrypt msg * base**i   
        gadget_ct.push_back(std::unique_ptr<NTRUCT>(sk->encrypt(msg_cpy.get()))); 
    }    
    return gadget_ct;
}