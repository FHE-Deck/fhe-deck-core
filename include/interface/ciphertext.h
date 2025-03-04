#ifndef CIPHERTEXT_H
#define CIPHERTEXT_H


/**
 * @file ciphertext.h
 */

#include "global_headers.h"
 
#include "ciphertexts/lwe.h"
#include "common/enums.h"  
#include "interface/plaintext_encoding.h"  
  
namespace FHEDeck{

/// @brief Forward Declaration of the FHEContext class which is defined in interface/fhe_context.h.
class FHEContext;
  
/**
 * @brief A class representing a ciphertext. This is used by the high level API, the FHEContext.
 * Its written such that using ciphertexts is as easy as using integers. 
 * So, importantly, iit has all the copy constructors, and operators overloaded.
 */
class Ciphertext{

    public: 
 
        /// @brief Pointer to a LWE Ciphertext.
        std::shared_ptr<LWECT> lwe_c;
        /// @brief Flag indicating whether lwe_c is initialized. 
        bool is_lwe_ct = false;
        /// @brief Flag whether this object is initialized. 
        bool is_init = false;
        /// @brief The encoding of the plaintext in the ciphertext.
        PlaintextEncoding encoding;
        /// @brief Pointer to the FHE context. Ciphertexts exist within a context. The context object then implements and controls bootstrapping, serialization, etc.
        
        const FHEContext* context;
  
        /// @brief default constructor
        Ciphertext() = default;
  
        /// @brief Constructs the object.
        /// @param lwe_c The input LWE Ciphertext 
        /// @param encoding The plaintext encoding
        /// @param context Pointer to the FHEContext, within which this ciphertext exists. 
        Ciphertext(std::shared_ptr<LWECT> lwe_c, const PlaintextEncoding& encoding, const FHEContext& context);
  
        /// @brief The copy constructor.
        /// @param c The input ciphertext to be copied. 
        Ciphertext(const Ciphertext& c);
  
        /// @brief The assignment operator.
        /// @param other The object to be copied. 
        /// @return reference to the copied object.
        Ciphertext& operator=(const Ciphertext& other);
 
        /// @brief Adds a ciphertext to this ciphertext. 
        /// @param ct The input ciphertext
        void add(Ciphertext& out, const Ciphertext& in) const;

        /// @brief Subtracts ct, from this ciphertext. 
        /// @param ct The input ciphertext
        void sub(Ciphertext& out, const Ciphertext& in) const;

        /// @brief Multiplies this ciphertext by a scalar.
        /// @param b The input scalar
        void mul(Ciphertext& out, const int64_t b) const;
  
        /// @brief Adds a scalar to this ciphertext.
        Ciphertext operator+(int64_t b) const;

        /// @brief Adds a ciphertext to this ciphertext.
        Ciphertext operator+(const Ciphertext& ct) const;

        /// @brief Subtracts a scalar from this ciphertext.
        Ciphertext operator-(int64_t b) const;

        /// @brief Subtracts a ciphertext from this ciphertext.
        Ciphertext operator-(const Ciphertext& ct) const;

        /// @brief Multiplies negates this ciphertext. 
        Ciphertext operator-() const;
    
        /// @brief Multiplies this ciphertext by a scalar.
        Ciphertext operator*(int64_t b) const; 
};
 
} /// End of namesapce FHEDeck
  
/// @brief Addition operator where we have the int64_t b on the left hand side.
/// @param b The input scalar
/// @param ct The input ciphertext
/// @return Returns a new ciphertext object.
FHEDeck::Ciphertext operator+(int64_t b, const FHEDeck::Ciphertext& ct);

/// @brief Subtraction operator where we have the int64_t b on the left hand side.
/// @param b The input scalar
/// @param ct The input ciphertext
/// @return Returns a new ciphertext object.
FHEDeck::Ciphertext operator-(int64_t b, const FHEDeck::Ciphertext& ct);

/// @brief Multiplication operator where we have the int64_t b on the left hand side.
/// @param b The input scalar
/// @param ct The input ciphertext
/// @return Returns a new ciphertext object.
FHEDeck::Ciphertext operator*(int64_t b, const FHEDeck::Ciphertext& ct);

#endif