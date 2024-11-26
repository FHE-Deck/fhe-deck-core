
#include "math/polynomial_multiplication_engine_builder.h"

#include "math/naive_multiplication_engine.h"
#include "math/intel_hexl_engine.h"
#include "math/fftw_engines.h"

using namespace fhe_deck; 

void PolynomialMultiplicationEngineBuilder::set_coef_modulus(const int64_t coef_modulus){
    this->coef_modulus = coef_modulus;
}

void PolynomialMultiplicationEngineBuilder::set_degree(const int64_t degree){
    this->degree = degree;
}

void PolynomialMultiplicationEngineBuilder::set_ring_type(const RingType ring){
    this->ring = ring;
}

void PolynomialMultiplicationEngineBuilder::set_polynomial_arithmetic(const PolynomialArithmetic arithmetic){
    this->arithmetic = arithmetic;
    this->is_init = true;
}

void PolynomialMultiplicationEngineBuilder::set_modulus_type(const ModulusType mod_type){
    this->mod_type = mod_type;
}

std::shared_ptr<PolynomialMultiplicationEngine> PolynomialMultiplicationEngineBuilder::build(){
    if(!is_init){
        throw std::logic_error("PolynomialMultiplicationEngineBuilder::build(): No polynomial arithmetic type set!");
    } 
    if(arithmetic == PolynomialArithmetic::ntt64){
        #if defined(USE_IntelHexl)
            return std::shared_ptr<PolynomialMultiplicationEngine>(new IntelHexlNTTEngine(degree, coef_modulus));
        #else 
            std::cout << "WARNING: No NTT engine available. Using NaiveNegacyclicMultiplicationEngine." << std::endl;
            return std::shared_ptr<PolynomialMultiplicationEngine>(new NaiveNegacyclicMultiplicationEngine(degree, coef_modulus));
        #endif
    }
    if(arithmetic == PolynomialArithmetic::double_fft){ 
        #if defined(USE_FFTW)
            return std::shared_ptr<PolynomialMultiplicationEngine>(new FFTWNegacyclicEngine(degree, coef_modulus));
        #else 
            std::cout << "WARNING: No FFT for double precision engine available. Using NaiveNegacyclicMultiplicationEngine." << std::endl;
            return std::shared_ptr<PolynomialMultiplicationEngine>(new NaiveNegacyclicMultiplicationEngine(degree, coef_modulus));
        #endif
    }
    if(arithmetic == PolynomialArithmetic::long_double_fft){
        #if defined(USE_FFTWL)
            return std::shared_ptr<PolynomialMultiplicationEngine>(new FFTWLongNegacyclicEngine(degree, coef_modulus));
        #else 
            std::cout << "WARNING: No FFT for quadruple precision engine available. Using NaiveNegacyclicMultiplicationEngine." << std::endl;
            return std::shared_ptr<PolynomialMultiplicationEngine>(new NaiveNegacyclicMultiplicationEngine(degree, coef_modulus));
        #endif 
    } 
    throw std::logic_error("PolynomialMultiplicationEngineBuilder::build(): Polynomial arithmetic not supported!");
}
