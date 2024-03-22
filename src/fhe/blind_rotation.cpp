#include "blind_rotation.h"

using namespace fhe_deck;




RotationPolyAccumulator::RotationPolyAccumulator(RotationPoly rot_poly){
    this->rot_poly = rot_poly;
    this->rot_poly_amortized = rot_poly;
}

void RotationPolyAccumulator::setup_amortization(){ 
    if(this->rot_poly_amortized.is_amortized_form){
        return;
    }else{
        this->rot_poly_amortized.to_amortization_form();
    } 
}






BlindRotateOutput::~BlindRotateOutput(){
    if(this->type == bro_rlwe){
        delete rlwe_ct;
    } 
}

BlindRotateOutput::BlindRotateOutput(RLWECT* rlwe_ct){
    this->type = bro_rlwe;
    this->rlwe_ct = rlwe_ct;
}


void BlindRotateOutput::extract_lwe(long* lwe_ct){
    if(type == bro_rlwe){
        this->rlwe_ct->extract_lwe(lwe_ct);
    }else{
        throw std::logic_error("BlindRotateOutput::~BlindRotateOutput: BlindRotationOutputType not recognized!");
    }
}

void BlindRotateOutput::post_rotation(std::shared_ptr<BlindRotateOutput> bl_out, std::shared_ptr<AbstractAccumulator> acc){
    if(type == bro_rlwe){ 
        std::shared_ptr<RotationPolyAccumulator> acc_msg = std::static_pointer_cast<RotationPolyAccumulator>(acc);
        this->rlwe_ct->mul(bl_out->rlwe_ct, &acc_msg->rot_poly_amortized);
    }else{
        throw std::logic_error("BlindRotateOutput::~BlindRotateOutput: BlindRotationOutputType not recognized!");
    }
}