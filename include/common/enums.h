#ifndef ENUMS_H
#define ENUMS_H


/**
 * @file enums.h
 */


namespace fhe_deck{

enum class RingType {cyclic, negacyclic};

enum class ModulusType {any, power_of_two}; 

enum class KeyDistribution {binary, ternary, uniform};

enum class PolynomialArithmetic {naive, double_fft, long_double_fft, ntt64};

enum class PolynomialInversionEngineType {ntl_inv};
 
enum class GadgetType {signed_decomposition_gadget, discrete_gaussian_gadget};

enum class VectorEncryptionType {RLWE, NTRU};

enum class KeySwitchType {standard_key_switch, lazy_key_switch, partial_lazy_key_switch};
 
  
enum class PlaintextEncodingType {signed_limied_short_int, signed_limied_short_int_bl, full_domain, partial_domain};
 
enum class BlindRotationAlgorithm{
    cggi_binary
};

enum class FullDomainBootstrappingAlgorithm{
    liu_micciancio_polyakov, kluczniak_shield_fdfb2
};

enum class SanitizationAlgorithm{
    ducas_stehle, kluczniak 
};

}

#endif