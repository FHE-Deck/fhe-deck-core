
#include "polynomial_multiplication_engine_builder.h"

#include "intel_hexl_engine.h"
#include "fftw_engines.h"

using namespace fhe_deck;




void PolynomialMultiplicationEngineBuilder::set_coef_modulus(int64_t coef_modulus){
    this->coef_modulus = coef_modulus;
}

void PolynomialMultiplicationEngineBuilder::set_degree(int64_t degree){
    this->degree = degree;
}

void PolynomialMultiplicationEngineBuilder::set_ring_type(RingType ring){
    this->ring = ring;
}

void PolynomialMultiplicationEngineBuilder::set_polynomial_arithmetic(PolynomialArithmetic arithmetic){
    this->arithmetic = arithmetic;
    this->is_init = true;
}

void PolynomialMultiplicationEngineBuilder::set_modulus_type(ModulusType mod_type){
    this->mod_type = mod_type;
}

std::shared_ptr<PolynomialMultiplicationEngine> PolynomialMultiplicationEngineBuilder::build(){
    if(!is_init){
        throw std::logic_error("PolynomialMultiplicationEngineBuilder::build(): No polynomial arithmetic type set!");
    }
    if(arithmetic == hexl_ntt){
        return std::shared_ptr<PolynomialMultiplicationEngine>(new IntelHexlNTTEngine(degree, coef_modulus));
    }
    if(arithmetic == double_fft){ 
        return std::shared_ptr<PolynomialMultiplicationEngine>(new FFTWNegacyclicEngine(degree, coef_modulus));
    }
    if(arithmetic == long_double_fft){
        return std::shared_ptr<PolynomialMultiplicationEngine>(new FFTWLongNegacyclicEngine(degree, coef_modulus));
    }
    if(arithmetic == ntl){
        throw std::logic_error("NTL Not Supported Yet.");
    }
    throw std::logic_error("PolynomialMultiplicationEngineBuilder::build(): Polynomial arithmetic not supported!");
}
