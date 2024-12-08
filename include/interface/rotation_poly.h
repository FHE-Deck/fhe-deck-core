#ifndef ROTATION_POLY_H
#define ROTATION_POLY_H

/**
 * @file rotation_poly.h
 */
#include "global_headers.h"
 
#include "common/utils.h"
#include "interface/plaintext_encoding.h"
#include "math/polynomial.h"
 
namespace fhe_deck{


/// @brief A class for implementing rotation polynomials. Rotation polynomials are used as homomorphic accumulators in functional bootstrapping.
/// @details This class is as a builder, that that takes a function specification and constructs a polynomial that embedds the function and is ready to be used for functional bootstrapping.
class RotationPoly : public Polynomial{
 
public:

    /// @brief The plaintext encoding used to encode messages on the polynomial.
    PlaintextEncoding output_encoding;
    /// @brief Indicates whether the polynomial is encoded or decoded using the plaintext polynomials. 
    bool is_encoded = true; 
    /// @brief Indicates whether the polynomial is in amortized form (prepared for multi-value bootstraping) or not. 
    bool is_amortized_form = false;
    /// @brief Indicates whether the polynomial is initialized or not.
    bool is_init = false;

    /// @brief Frees the coefs array.
    ~RotationPoly();

    /// @brief Default constructor.
    RotationPoly() = default;
 
    /// @brief Constructs a rotation polynomial.
    /// @param f The function to be embedded in the polynomial.
    /// @param degree The degree of the polynomial.
    /// @param output_encoding The encoding used to encode messages on the polynomial.
    /// @param is_amortized_form Indicates whether the polynomial is in amortized form or not. By defaults is false.
    RotationPoly(std::function<int64_t(int64_t,int64_t)> f, int64_t degree, PlaintextEncoding output_encoding, bool is_amortized_form = false);

    /// @brief Constructs a rotation polynomial.
    /// @param f The function to be embedded in the polynomial.
    /// @param degree The degree of the polynomial.
    /// @param output_encoding The encoding used to encode messages on the polynomial.
    /// @param is_amortized_form Indicates whether the polynomial is in amortized form or not. By defaults is false.
    RotationPoly(std::function<int64_t(int64_t)> f, int64_t degree, PlaintextEncoding output_encoding, bool is_amortized_form = false); 
  
    /// @brief Copy constructor.
    /// @param poly The polynomial to be copied.
    RotationPoly(const RotationPoly &poly);

    /// @brief The assignment operator.
    /// @param other The polynomial to be assigned.
    /// @return The assigned polynomial.
    RotationPoly& operator=(const RotationPoly other);

    /// @brief Encodes the polynomial using the output_encoding.
    void encode();

    /// @brief Dencodes the polynomial using the output_encoding.
    void decode();

    /// @brief Converts the polynomial to amortized form.
    void to_amortization_form();

    /// @brief Converts the polynomial to non-amortized form.
    void to_non_amortized_form();
   
    /// @brief Constructs a specific rotation polynomial, that compute the sign of the intput and is used in various bootstrapping procedures.
    /// @param t The pleintext space.
    /// @param degree The degree of the polynomial.
    /// @param ciphertext_modulus The modulus of the ciphertext.
    /// @return The rotation polynomial.
    /// @details It sets all coefficients to -1, so that if a bootstrapped message is positive the constant term of the rotated poly is 1. If the bootstrapped message is negative the constant term of the rotated poly is -1.
    static RotationPoly rot_sgn(int32_t plaintext_space, int64_t degree, int64_t ciphertext_modulus); 

    /// @brief Constructs a specific rotation polynomial, that computes -1/2 for a positive number and 1/2 for a negative. After bootstraping if we add 1/2, we get the msb. It is used in various bootstrapping procedures.
    /// @param t The pleintext space.
    /// @param degree The degree of the polynomial.
    /// @param ciphertext_modulus The modulus of the ciphertext.
    /// @return The rotation polynomial. 
    static RotationPoly rot_msb(int32_t plaintext_space, int64_t degree, int64_t ciphertext_modulus); 

    /// @brief Constructs a specific rotation polynomial, that is used in various bootstrapping procedures.
    /// @param degree The degree of the polynomial.
    /// @param ciphertext_modulus The modulus of the ciphertext.
    /// @return The rotation polynomial.
    /// @details Sets all coefficients to 0. Its used for example in multivalue bootstrapping, where we change only the const term of this polynomial to an encoding of 1. 
    static RotationPoly rot_one(int64_t degree, int64_t ciphertext_modulus); 
   
};




}

#endif