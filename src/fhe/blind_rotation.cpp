#include "blind_rotation.h"

using namespace fhe_deck;

VectorCTAccumulator::VectorCTAccumulator(std::shared_ptr<RLWEParam> param, RotationPoly rot_poly, bool amortization){ 
    std::shared_ptr<RLWECT> acc_ptr = std::shared_ptr<RLWECT>(new RLWECT(param)); 
    acc_ptr->a.zeroize();
    acc_ptr->b = rot_poly;  
    acc = acc_ptr;
    this->rot_poly = rot_poly;
    this->rot_poly_amortized = rot_poly; 
    this->amortization = amortization;
    if(this->amortization){
        this->rot_poly_amortized.to_amortization_form();
    }
}

VectorCTAccumulator::VectorCTAccumulator(std::shared_ptr<VectorCT> acc, bool amortization){
    this->acc = acc;
    this->amortization = amortization; 
}

VectorCTAccumulator::VectorCTAccumulator(VectorCTAccumulator &other){
    this->acc = other.acc;
    this->rot_poly = other.rot_poly;
    this->rot_poly_amortized = other.rot_poly_amortized;
    this->amortization = other.amortization;
}

VectorCTAccumulator& VectorCTAccumulator::operator=(const VectorCTAccumulator other){
    this->acc = other.acc;
    this->rot_poly = other.rot_poly;
    this->rot_poly_amortized = other.rot_poly_amortized;
    this->amortization = other.amortization;
    return *this;
}
  
RLWEAccumulatorBuilder::RLWEAccumulatorBuilder(std::shared_ptr<RLWEParam> param){
    this->param = param;
}

VectorCTAccumulator* RLWEAccumulatorBuilder::prepare_accumulator(long (*f)(long message), PlaintextEncoding output_encoding){ 
    RotationPoly poly = RotationPoly(f, this->param->size, output_encoding);   
    return new VectorCTAccumulator(this->param, poly);
}

VectorCTAccumulator* RLWEAccumulatorBuilder::prepare_accumulator(long (*f)(long message, long plaintext_space), PlaintextEncoding output_encoding){
    RotationPoly poly = RotationPoly(f, this->param->size, output_encoding);  
    return  new VectorCTAccumulator(this->param, poly);
}

VectorCTAccumulator* RLWEAccumulatorBuilder::get_acc_msb(){    
    RotationPoly poly = RotationPoly::rot_msb(4, this->param->size, this->param->coef_modulus);   
    VectorCTAccumulator *acc = new VectorCTAccumulator(this->param, poly, false);   
    return new VectorCTAccumulator(this->param, poly, false); 
}

VectorCTAccumulator* RLWEAccumulatorBuilder::get_acc_one(PlaintextEncoding output_encoding){
    RotationPoly poly = RotationPoly::rot_one(this->param->size, output_encoding.ciphertext_modulus);
    poly.coefs[1] = output_encoding.encode_message(1); 
    std::shared_ptr<RLWEParam> rlwe_param = std::static_pointer_cast<RLWEParam>(this->param); 
    return new VectorCTAccumulator(rlwe_param, poly, false);
}


RLWEBlindRotateOutputBuilder::RLWEBlindRotateOutputBuilder(std::shared_ptr<RLWEParam> param){
    this->param = param;
}

BlindRotateOutput* RLWEBlindRotateOutputBuilder::build(){
    return new RLWEBlindRotateOutput(param);
}


RLWEBlindRotateOutput::~RLWEBlindRotateOutput(){ 
    delete accumulator; 
}

RLWEBlindRotateOutput::RLWEBlindRotateOutput(std::shared_ptr<RLWEParam> param){ 
    this->accumulator = param->init_ct();
    this->accumulator_ptr = static_cast<RLWECT*>(accumulator);
}
  
void RLWEBlindRotateOutput::extract_lwe(LWECT* out){ 
    accumulator_ptr->extract_lwe(out->ct);
}

void RLWEBlindRotateOutput::post_rotation(std::shared_ptr<BlindRotateOutput> bl_out, std::shared_ptr<VectorCTAccumulator> acc){ 
    std::shared_ptr<RLWEBlindRotateOutput> out_ptr = std::static_pointer_cast<RLWEBlindRotateOutput>(bl_out); 
    this->accumulator_ptr->mul(out_ptr->accumulator_ptr, &acc->rot_poly_amortized);
}