#include "fhe/blind_rotation.h"

using namespace FHEDeck;
    
VectorCTAccumulator::VectorCTAccumulator(std::shared_ptr<VectorCT> acc_content){
    this->acc_content = acc_content; 
}

VectorCTAccumulator::VectorCTAccumulator(VectorCTAccumulator &other){
    this->acc_content = other.acc_content; 
}

VectorCTAccumulator& VectorCTAccumulator::operator=(const VectorCTAccumulator other){
    this->acc_content = other.acc_content; 
    return *this;
}
  
PolynomialSpecification::PolynomialSpecification(RotationPoly rot_poly){ 
    this->rot_poly = rot_poly;
    this->rot_poly.to_amortization_form(); 
}
  

KSFunctionSpecification::KSFunctionSpecification(const std::function<long(long, long)> f, long dim,
                                              long coef_modulus, PlaintextEncoding input_encoding){  
 
    poly_msb_0 = Polynomial(dim, coef_modulus); 
    poly_msb_0.zeroize(); 
    poly_msb_1 = Polynomial(dim, coef_modulus);
    poly_msb_1.zeroize();  
    int32_t two_dim = 2 * dim;             

    if(input_encoding.get_plaintext_space() % 2 == 0){
        int32_t skip = (int32_t)round(2*(dim/input_encoding.get_plaintext_space()));
        int32_t half_plaintext_space = input_encoding.get_plaintext_space() / 2;  
        for(long i = 0; i < half_plaintext_space; ++i) {    
            poly_msb_0.coefs[dim - (int32_t)round((double)(two_dim * i)/(double)input_encoding.get_plaintext_space()) - skip] = -f(i, input_encoding.get_plaintext_space());  
        }   
        for(long i = half_plaintext_space; i < input_encoding.get_plaintext_space(); ++i) {          
            poly_msb_1.coefs[two_dim - (int32_t)round((double)(two_dim * i)/(double)input_encoding.get_plaintext_space()) - skip] = f(i, input_encoding.get_plaintext_space()); 
        }   
    }else{ 
        int32_t skip = (int32_t)round(dim/input_encoding.get_plaintext_space()); 
        int32_t two_skip = 2 * skip; 
        /// NOTE: this is the floor of the half of the plaintext space, actually. (One tick is missing)
        int32_t half_plaintext_space = (input_encoding.get_plaintext_space()-1)/2;  
        for(long i = 0; i < half_plaintext_space; ++i) {    
            poly_msb_0.coefs[dim - (int32_t)round((double)(two_dim * i)/(double)input_encoding.get_plaintext_space()) - skip] = -f(i, input_encoding.get_plaintext_space()); 
            poly_msb_0.coefs[dim - (int32_t)round((double)(two_dim * i)/(double)input_encoding.get_plaintext_space()) - two_skip] = -f(i, input_encoding.get_plaintext_space()); 
        }
           
        poly_msb_0.coefs[0] = -f(half_plaintext_space, input_encoding.get_plaintext_space());  
        poly_msb_1.coefs[dim - skip] = f(half_plaintext_space, input_encoding.get_plaintext_space()); 

        for(long i = half_plaintext_space+1; i < input_encoding.get_plaintext_space(); ++i) {        
            poly_msb_1.coefs[two_dim - (int32_t)round((double)(two_dim * i)/(double)input_encoding.get_plaintext_space()) - skip] = f(i, input_encoding.get_plaintext_space());
            poly_msb_1.coefs[two_dim - (int32_t)round((double)(two_dim * i)/(double)input_encoding.get_plaintext_space()) - two_skip] = f(i, input_encoding.get_plaintext_space()); 
        }   
    }
    Utils::array_mod_form(poly_msb_0.coefs, poly_msb_0.coefs, dim, coef_modulus);
    Utils::array_mod_form(poly_msb_1.coefs, poly_msb_1.coefs, dim, coef_modulus);  
}  
 
PolynomialSpecificationBuilder::PolynomialSpecificationBuilder(int32_t degree){
    this->degree = degree;
}

std::shared_ptr<FunctionSpecification> PolynomialSpecificationBuilder::prepare_specification(
    std::function<int64_t(int64_t)> f, 
    PlaintextEncoding input_encoding,
    PlaintextEncoding output_encoding){
    RotationPoly poly(f, this->degree, input_encoding, output_encoding);    
    return std::make_shared<PolynomialSpecification>(poly);
}
 
KSFunctionSpecificationBuilder::KSFunctionSpecificationBuilder(int32_t degree, int64_t coef_modulus){
    this->degree = degree;
    this->coef_modulus = coef_modulus;
}

std::shared_ptr<FunctionSpecification> KSFunctionSpecificationBuilder::prepare_specification(std::function<int64_t(int64_t)> f, PlaintextEncoding input_encoding, PlaintextEncoding output_encoding){
    std::function<int64_t(int64_t, int64_t)> f_2 = [f](int64_t x, int64_t p) {
        return f(Utils::integer_mod_form(x, p));
    };
    return std::make_shared<KSFunctionSpecification>(f_2, degree, coef_modulus, input_encoding);
}
  
RLWEAccumulatorBuilder::RLWEAccumulatorBuilder(std::shared_ptr<RLWEParam> param){
    this->param = param;
}

std::shared_ptr<FunctionSpecification> RLWEAccumulatorBuilder::prepare_specification(std::function<int64_t(int64_t)> f, PlaintextEncoding input_encoding, PlaintextEncoding output_encoding){
    RotationPoly poly(f, this->param->size, input_encoding, output_encoding);   
    std::shared_ptr<RLWECT> acc_ptr = std::shared_ptr<RLWECT>(new RLWECT(std::static_pointer_cast<RLWEParam>(param))); 
    acc_ptr->a.zeroize();
    acc_ptr->b = poly;   
    return std::make_shared<VectorCTAccumulator>(acc_ptr);
}
 
std::shared_ptr<VectorCTAccumulator> RLWEAccumulatorBuilder::prepare_accumulator(Vector& vec){
    Polynomial vec_cast = static_cast<Polynomial&>(vec);
    std::shared_ptr<RLWECT> acc_ptr = std::shared_ptr<RLWECT>(new RLWECT(std::static_pointer_cast<RLWEParam>(param))); 
    acc_ptr->a.zeroize();
    acc_ptr->b = vec_cast;  
    return std::make_shared<VectorCTAccumulator>(acc_ptr);
}
  
NTRUAccumulatorBuilder::NTRUAccumulatorBuilder(std::shared_ptr<NTRUSK> sk){
    this->sk = sk;
    this->param = this->sk->param;
    this->is_sk_set = true;
}

std::shared_ptr<FunctionSpecification> NTRUAccumulatorBuilder::prepare_specification(std::function<int64_t(int64_t)> f, PlaintextEncoding input_encoding, PlaintextEncoding output_encoding){
    if(is_sk_set){
        RotationPoly poly = RotationPoly(f, this->param->size, input_encoding, output_encoding);   
        std::shared_ptr<NTRUCT> acc(new NTRUCT(std::static_pointer_cast<NTRUParam>(param))); 
        sk->kdm_encrypt(*acc, poly); 
        return std::make_shared<VectorCTAccumulator>(acc);
    }else{
        throw std::logic_error("NTRUAccumulatorBuilder::prepare_accumulator(int64_t (*f)(int64_t message), PlaintextEncoding output_encoding): sk must be set.");
    } 
}
  
std::shared_ptr<VectorCTAccumulator> NTRUAccumulatorBuilder::prepare_accumulator(Vector& vec){
    Polynomial vec_cast = static_cast<Polynomial&>(vec);
    if(is_sk_set){  
        std::shared_ptr<NTRUCT> acc = std::shared_ptr<NTRUCT>(new NTRUCT(std::static_pointer_cast<NTRUParam>(param))); 
        sk->kdm_encrypt(*acc, vec_cast);
        return std::make_shared<VectorCTAccumulator>(acc);
    }else{
        throw std::logic_error("NTRUAccumulatorBuilder::prepare_accumulator(int64_t (*f)(int64_t message), PlaintextEncoding output_encoding): sk must be set.");
    } 
}
  
PreparedVectorCTAccumulators::PreparedVectorCTAccumulators(std::shared_ptr<VectorCTAccumulatorBuilder> builder){
    this->builder = builder;
}

std::shared_ptr<VectorCTAccumulator> PreparedVectorCTAccumulators::get_acc_sgn(PlaintextEncoding output_encoding){
    RotationPoly poly = RotationPoly::rot_sgn(output_encoding.get_plaintext_space(), builder->param->size, output_encoding.get_ciphertext_modulus());   
    return builder->prepare_accumulator(poly);
}

std::shared_ptr<VectorCTAccumulator> PreparedVectorCTAccumulators::get_acc_msb(PlaintextEncoding output_encoding){
    RotationPoly poly = RotationPoly::rot_msb(output_encoding.get_plaintext_space(), builder->param->size, output_encoding.get_ciphertext_modulus());  
    return builder->prepare_accumulator(poly);
}
  
std::shared_ptr<VectorCTAccumulator> PreparedVectorCTAccumulators::get_acc_one(PlaintextEncoding output_encoding){ 
    RotationPoly poly = RotationPoly::rot_one(builder->param->size, output_encoding.get_ciphertext_modulus());
    poly.coefs[1] = output_encoding.encode_message(1);  
    return builder->prepare_accumulator(poly);
}

std::shared_ptr<VectorCTAccumulator> PreparedVectorCTAccumulators::get_pad_poly(PlaintextEncoding output_encoding){
    Polynomial pad_poly(builder->param->size, output_encoding.get_ciphertext_modulus());
    pad_poly.zeroize();
    uint64_t scal = output_encoding.get_ciphertext_modulus() / (2 * output_encoding.get_plaintext_space());
    uint64_t skip = 2 * (builder->param->size / (output_encoding.get_plaintext_space()));
    /// NOTE: This is the same as pad poly, but encoded with double the plaintext space... In the paper its \frac{h} 
    for(long i = 0; i < skip; i++) {
        pad_poly.coefs[i] = scal;
    } 
    return builder->prepare_accumulator(pad_poly);
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

void RLWEBlindRotateOutput::post_rotation(std::shared_ptr<BlindRotateOutput> bl_out, std::shared_ptr<FunctionSpecification> acc){ 
    std::shared_ptr<PolynomialSpecification> acc_cast = std::static_pointer_cast<PolynomialSpecification>(acc);
    std::shared_ptr<RLWEBlindRotateOutput> out_ptr = std::static_pointer_cast<RLWEBlindRotateOutput>(bl_out);  
    this->accumulator_ptr->mul(*out_ptr->accumulator_ptr, acc_cast->rot_poly);
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

void NTRUBlindRotateOutput::post_rotation(std::shared_ptr<BlindRotateOutput> bl_out, std::shared_ptr<FunctionSpecification> acc){ 
    std::shared_ptr<PolynomialSpecification> acc_cast = std::static_pointer_cast<PolynomialSpecification>(acc);
    std::shared_ptr<NTRUBlindRotateOutput> out_ptr = std::static_pointer_cast<NTRUBlindRotateOutput>(bl_out); 
    this->accumulator_ptr->mul(*out_ptr->accumulator_ptr, acc_cast->rot_poly);
}

 