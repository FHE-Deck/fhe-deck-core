#ifndef ENUMS_H
#define ENUMS_H


/**
 * @file enums.h
 */


namespace fhe_deck{

enum RingType {cyclic, negacyclic};

enum ModulusType {any, power_of_two}; 

enum KeyDistribution {binary, ternary, uniform};

enum PolynomialArithmetic {ntl, double_fft, long_double_fft, ntt64};

enum PolynomialInversionEngineType {ntl_inv};
 
enum GadgetType {signed_decomposition_gadget, discrete_gaussian_gadget};

enum KeySwitchType {standard_key_switch, lazy_key_switch, partial_lazy_key_switch};
  
enum PlaintextEncodingType {signed_limied_short_int, signed_limied_short_int_bl, full_domain, partial_domain};
 
enum FullDomainBootstrappingAlgorithm{
    liu_micciancio_polyakov 
};


}

#endif