
#include "math/polynomial_multiplication_engine_builder.h"

#include "math/naive_multiplication_engine.h"

#if defined(USE_IntelHexl)
#include "math/intel_hexl_engine.h"
#endif

#if defined(USE_FFTW)
#include "math/fftw_engine.h"
#endif

#if defined(USE_FFTWL)
#include "math/fftw_long_engine.h"
#endif 

using namespace FHEDeck; 

void PolynomialMultiplicationEngineBuilder::set_coef_modulus(const int64_t coef_modulus){
    m_coef_modulus = coef_modulus;
}

void PolynomialMultiplicationEngineBuilder::set_degree(const int64_t degree){
    m_degree = degree;
}

void PolynomialMultiplicationEngineBuilder::set_ring_type(const RingType ring){
    m_ring = ring;
}

void PolynomialMultiplicationEngineBuilder::set_polynomial_arithmetic(const PolynomialArithmetic arithmetic){
    m_arithmetic = arithmetic; 
}

void PolynomialMultiplicationEngineBuilder::set_modulus_type(const ModulusType mod_type){
    m_mod_type = mod_type;
}

std::shared_ptr<PolynomialMultiplicationEngine> PolynomialMultiplicationEngineBuilder::build(){ 
    if(m_arithmetic == PolynomialArithmetic::naive){ 
        return std::shared_ptr<PolynomialMultiplicationEngine>(new NaiveNegacyclicMultiplicationEngine(m_degree, m_coef_modulus)); 
    }
    if(m_arithmetic == PolynomialArithmetic::ntt64){
        #if defined(USE_IntelHexl)
            return std::shared_ptr<PolynomialMultiplicationEngine>(new IntelHexlNTTEngine(m_degree, m_coef_modulus));
        #else 
            std::cout << "WARNING: No NTT engine available. Using NaiveNegacyclicMultiplicationEngine." << std::endl;
            return std::shared_ptr<PolynomialMultiplicationEngine>(new NaiveNegacyclicMultiplicationEngine(degree, coef_modulus));
        #endif
    }
    if(m_arithmetic == PolynomialArithmetic::double_fft){ 
        #if defined(USE_FFTW)
            return std::shared_ptr<PolynomialMultiplicationEngine>(new FFTWNegacyclicEngine(m_degree, m_coef_modulus));
        #else 
            std::cout << "WARNING: No FFT for double precision engine available. Using NaiveNegacyclicMultiplicationEngine." << std::endl;
            return std::shared_ptr<PolynomialMultiplicationEngine>(new NaiveNegacyclicMultiplicationEngine(degree, coef_modulus));
        #endif
    }
    if(m_arithmetic == PolynomialArithmetic::long_double_fft){
        #if defined(USE_FFTWL)
            return std::shared_ptr<PolynomialMultiplicationEngine>(new FFTWLongNegacyclicEngine(m_degree, m_coef_modulus));
        #else 
            std::cout << "WARNING: No FFT for quadruple precision engine available. Using NaiveNegacyclicMultiplicationEngine." << std::endl;
            return std::shared_ptr<PolynomialMultiplicationEngine>(new NaiveNegacyclicMultiplicationEngine(degree, coef_modulus));
        #endif  
    } 
    throw std::logic_error("PolynomialMultiplicationEngineBuilder::build(): Polynomial arithmetic not supported!");
}
