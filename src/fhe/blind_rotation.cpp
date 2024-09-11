#include "blind_rotation.h"

using namespace fhe_deck;
  
VectorCTAccumulator::VectorCTAccumulator(std::shared_ptr<VectorCT> acc_content, RotationPoly rot_poly, bool amortization){  
    this->acc_content = acc_content;
    this->rot_poly = rot_poly;
    this->rot_poly_amortized = rot_poly; 
    this->amortization = amortization;
    if(this->amortization){
        this->rot_poly_amortized.to_amortization_form();
    }
}
 
VectorCTAccumulator::VectorCTAccumulator(std::shared_ptr<VectorCT> acc_content, bool amortization){
    this->acc_content = acc_content;
    this->amortization = amortization; 
}

VectorCTAccumulator::VectorCTAccumulator(VectorCTAccumulator &other){
    this->acc_content = other.acc_content;
    this->rot_poly = other.rot_poly;
    this->rot_poly_amortized = other.rot_poly_amortized;
    this->amortization = other.amortization;
}

VectorCTAccumulator& VectorCTAccumulator::operator=(const VectorCTAccumulator other){
    this->acc_content = other.acc_content;
    this->rot_poly = other.rot_poly;
    this->rot_poly_amortized = other.rot_poly_amortized;
    this->amortization = other.amortization;
    return *this;
}
  

 /// TODO: Check what this exactly does, and whether we can implement it with existing accumulators.
 FunctionalAccumulator::FunctionalAccumulator(const BootFunction& boot_F, long dim,
                                              long coef_modulus, PlaintextEncoding encoding) : VectorCTAccumulator(
         nullptr /* DANGER */, false) {
    // TODO: for now we assume that this accumulator is only used for FDFB-2
  
    int32_t skip = 2*(dim/encoding.plaintext_space);
    int32_t half_plaintext_space = encoding.plaintext_space / 2;
    Polynomial a_prim(dim, coef_modulus);
    poly_msb_0 = Polynomial(dim, coef_modulus);
    a_prim.zeroize();
    poly_msb_0.zeroize();
    Polynomial b_prim(dim, coef_modulus);
    poly_msb_1 = Polynomial(dim, coef_modulus);
    poly_msb_1.zeroize();
    b_prim.zeroize();
    for(long i = 0; i < half_plaintext_space; i++) {   
        poly_msb_0.coefs[skip * i] = -boot_F(half_plaintext_space - i - 1, encoding.plaintext_space);
        poly_msb_1.coefs[skip * i] = boot_F(encoding.plaintext_space - i - 1, encoding.plaintext_space);
    }
    Utils::array_mod_form(poly_msb_0.coefs, poly_msb_0.coefs, dim, coef_modulus);
    Utils::array_mod_form(poly_msb_1.coefs, poly_msb_1.coefs, dim, coef_modulus); 

 
}
  
FunctionalAccumulator::FunctionalAccumulator(long (*f)(long message, long plaintext_space), long dim,
                                             long coef_modulus, PlaintextEncoding encoding) : VectorCTAccumulator(
        nullptr, false) {
    // TODO: for now we assume that this accumulator is only used for FDFB-2

    int32_t skip = 2*(dim/encoding.plaintext_space);
    int32_t half_plaintext_space = encoding.plaintext_space / 2;
    Polynomial a_prim(dim, coef_modulus);
    poly_msb_0 = Polynomial(dim, coef_modulus);
    a_prim.zeroize();
    poly_msb_0.zeroize();
    Polynomial b_prim(dim, coef_modulus);
    poly_msb_1 = Polynomial(dim, coef_modulus);
    poly_msb_1.zeroize();
    b_prim.zeroize();
    for(long i = 0; i < half_plaintext_space; i++) {   
        poly_msb_0.coefs[skip * i] = -f(half_plaintext_space - i - 1, encoding.plaintext_space);
        poly_msb_1.coefs[skip * i] = f(encoding.plaintext_space - i - 1, encoding.plaintext_space);
    }
    Utils::array_mod_form(poly_msb_0.coefs, poly_msb_0.coefs, dim, coef_modulus);
    Utils::array_mod_form(poly_msb_1.coefs, poly_msb_1.coefs, dim, coef_modulus); 
 
}
 

RLWEAccumulatorBuilder::RLWEAccumulatorBuilder(std::shared_ptr<RLWEParam> param){
    this->param = param;
}

VectorCTAccumulator* RLWEAccumulatorBuilder::prepare_accumulator(int64_t (*f)(int64_t message), PlaintextEncoding output_encoding){ 
    RotationPoly poly(f, this->param->size, output_encoding);   
    std::shared_ptr<RLWECT> acc_ptr = std::shared_ptr<RLWECT>(new RLWECT(param)); 
    acc_ptr->a.zeroize();
    acc_ptr->b = poly;  
    return new VectorCTAccumulator(acc_ptr, poly);
}

VectorCTAccumulator* RLWEAccumulatorBuilder::prepare_accumulator(int64_t (*f)(int64_t message, int64_t plaintext_space), PlaintextEncoding output_encoding){
    RotationPoly poly(f, this->param->size, output_encoding);  
    std::shared_ptr<RLWECT> acc_ptr = std::shared_ptr<RLWECT>(new RLWECT(param)); 
    acc_ptr->a.zeroize();
    acc_ptr->b = poly;  
    return  new VectorCTAccumulator(acc_ptr, poly);
}

VectorCTAccumulator* RLWEAccumulatorBuilder::get_acc_sgn(PlaintextEncoding output_encoding){     
    RotationPoly poly = RotationPoly::rot_sgn(output_encoding.plaintext_space, this->param->size, this->param->coef_modulus);    
    std::shared_ptr<RLWECT> acc_ptr(new RLWECT(param)); 
    acc_ptr->a.zeroize();
    acc_ptr->b = poly;  
    return new VectorCTAccumulator(acc_ptr, poly, false); 
}

VectorCTAccumulator* RLWEAccumulatorBuilder::get_acc_msb(PlaintextEncoding output_encoding){     
    RotationPoly poly = RotationPoly::rot_msb(output_encoding.plaintext_space, this->param->size, this->param->coef_modulus);    
    std::shared_ptr<RLWECT> acc_ptr(new RLWECT(param)); 
    acc_ptr->a.zeroize();
    acc_ptr->b = poly;  
    return new VectorCTAccumulator(acc_ptr, poly, false); 
}

VectorCTAccumulator* RLWEAccumulatorBuilder::get_acc_one(PlaintextEncoding output_encoding){
    RotationPoly poly = RotationPoly::rot_one(this->param->size, output_encoding.ciphertext_modulus);
    poly.coefs[1] = output_encoding.encode_message(1); 
    std::shared_ptr<RLWEParam> rlwe_param = std::static_pointer_cast<RLWEParam>(this->param); 
    std::shared_ptr<RLWECT> acc_ptr(new RLWECT(param)); 
    acc_ptr->a.zeroize();
    acc_ptr->b = poly;  
    return new VectorCTAccumulator(acc_ptr, poly, false);
}

NTRUAccumulatorBuilder::NTRUAccumulatorBuilder(std::shared_ptr<NTRUSK> sk){
    this->sk = sk;
    this->param = this->sk->param;
    this->is_sk_set = true;
}

VectorCTAccumulator* NTRUAccumulatorBuilder::prepare_accumulator(int64_t (*f)(int64_t message), PlaintextEncoding output_encoding){  
    if(is_sk_set){
        RotationPoly poly = RotationPoly(f, this->param->size, output_encoding);   
        std::shared_ptr<NTRUCT> acc(new NTRUCT(param)); 
        sk->kdm_encrypt(*acc.get(), poly);
        return new VectorCTAccumulator(acc, poly);
    }else{
        throw std::logic_error("NTRUAccumulatorBuilder::prepare_accumulator(int64_t (*f)(int64_t message), PlaintextEncoding output_encoding): sk must be set.");
    } 
}

VectorCTAccumulator* NTRUAccumulatorBuilder::prepare_accumulator(int64_t (*f)(int64_t message, int64_t plaintext_space), PlaintextEncoding output_encoding){
    if(is_sk_set){
        RotationPoly poly = RotationPoly(f, this->param->size, output_encoding);   
        std::shared_ptr<NTRUCT> acc = std::shared_ptr<NTRUCT>(new NTRUCT(param)); 
        sk->kdm_encrypt(*acc.get(), poly);
        return new VectorCTAccumulator(acc, poly);
    }else{
        throw std::logic_error("NTRUAccumulatorBuilder::prepare_accumulator(int64_t (*f)(int64_t message), PlaintextEncoding output_encoding): sk must be set.");
    } 
}

VectorCTAccumulator* NTRUAccumulatorBuilder::get_acc_sgn(PlaintextEncoding output_encoding){     
    RotationPoly poly = RotationPoly::rot_sgn(output_encoding.plaintext_space, this->param->size, this->param->coef_modulus);   
    if(is_sk_set){   
        std::shared_ptr<NTRUCT> acc(new NTRUCT(param));  
        sk->kdm_encrypt(*acc.get(), poly); 
        return new VectorCTAccumulator(acc, poly, false);
    }else{
        throw std::logic_error("NTRUAccumulatorBuilder::prepare_accumulator(int64_t (*f)(int64_t message), PlaintextEncoding output_encoding): sk must be set.");
    } 
}

VectorCTAccumulator* NTRUAccumulatorBuilder::get_acc_msb(PlaintextEncoding output_encoding){     
    RotationPoly poly = RotationPoly::rot_msb(output_encoding.plaintext_space, this->param->size, this->param->coef_modulus);   
    if(is_sk_set){   
        std::shared_ptr<NTRUCT> acc(new NTRUCT(param));  
        sk->kdm_encrypt(*acc.get(), poly); 
        return new VectorCTAccumulator(acc, poly, false);
    }else{
        throw std::logic_error("NTRUAccumulatorBuilder::prepare_accumulator(int64_t (*f)(int64_t message), PlaintextEncoding output_encoding): sk must be set.");
    } 
}

VectorCTAccumulator* NTRUAccumulatorBuilder::get_acc_one(PlaintextEncoding output_encoding){ 
    RotationPoly poly = RotationPoly::rot_one(this->param->size, output_encoding.ciphertext_modulus);
    poly.coefs[1] = output_encoding.encode_message(1); 
    if(is_sk_set){  
        std::shared_ptr<NTRUCT> acc(new NTRUCT(param)); 
        sk->kdm_encrypt(*acc.get(), poly);
        return new VectorCTAccumulator(acc, poly, false);
    }else{
        throw std::logic_error("NTRUAccumulatorBuilder::prepare_accumulator(int64_t (*f)(int64_t message), PlaintextEncoding output_encoding): sk must be set.");
    } 
}

RLWEBlindRotateOutputBuilder::RLWEBlindRotateOutputBuilder(std::shared_ptr<RLWEParam> param){
    this->rlwe_param = param;
}

LWEParam* RLWEBlindRotateOutputBuilder::build_extract_lwe_param(){
    return new LWEParam(rlwe_param->size, rlwe_param->coef_modulus);  
}

BlindRotateOutput* RLWEBlindRotateOutputBuilder::build(){
    return new RLWEBlindRotateOutput(rlwe_param); 
}
  
NTRUBlindRotateOutputBuilder::NTRUBlindRotateOutputBuilder(std::shared_ptr<NTRUParam> param){
    this->ntru_param = param;
}


LWEParam* NTRUBlindRotateOutputBuilder::build_extract_lwe_param(){
    return new LWEParam(ntru_param->size, ntru_param->coef_modulus);  
}

BlindRotateOutput* NTRUBlindRotateOutputBuilder::build(){
    return new NTRUBlindRotateOutput(ntru_param); 
}

RLWEBlindRotateOutput::~RLWEBlindRotateOutput(){  
    delete accumulator;  
}

RLWEBlindRotateOutput::RLWEBlindRotateOutput(std::shared_ptr<RLWEParam> param){  
    this->accumulator = new RLWECT(param);
    this->accumulator_ptr = static_cast<RLWECT*>(accumulator);
}
  
void RLWEBlindRotateOutput::extract_lwe(LWECT& out){ 
    accumulator_ptr->extract_lwe(out);
}

void RLWEBlindRotateOutput::post_rotation(std::shared_ptr<BlindRotateOutput> bl_out, std::shared_ptr<VectorCTAccumulator> acc){ 
    std::shared_ptr<RLWEBlindRotateOutput> out_ptr = std::static_pointer_cast<RLWEBlindRotateOutput>(bl_out); 
    this->accumulator_ptr->mul(*out_ptr->accumulator_ptr, acc->rot_poly_amortized);
}

NTRUBlindRotateOutput::~NTRUBlindRotateOutput(){ 
    delete accumulator; 
}

NTRUBlindRotateOutput::NTRUBlindRotateOutput(std::shared_ptr<NTRUParam> param){ 
    this->accumulator = new NTRUCT(param);
    this->accumulator_ptr = static_cast<NTRUCT*>(accumulator);
}
  
void NTRUBlindRotateOutput::extract_lwe(LWECT& out){ 
    accumulator_ptr->extract_lwe(out);
}

void NTRUBlindRotateOutput::post_rotation(std::shared_ptr<BlindRotateOutput> bl_out, std::shared_ptr<VectorCTAccumulator> acc){ 
    std::shared_ptr<NTRUBlindRotateOutput> out_ptr = std::static_pointer_cast<NTRUBlindRotateOutput>(bl_out); 
    this->accumulator_ptr->mul(*out_ptr->accumulator_ptr, acc->rot_poly_amortized);
}

 