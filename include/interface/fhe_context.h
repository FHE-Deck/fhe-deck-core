#ifndef FHE_CONTEXT_H
#define FHE_CONTEXT_H


/**
 * @file fhe_context.h
 */
#include "global_headers.h"

//#include "interface/ciphertext.h" 
#include "interface/plaintext_encoding.h" 
#include "fhe/fhe_configuration.h"
#include "common/enums.h" 
   
namespace fhe_deck{

/// @brief Forward Declaration of the Ciphertext class which is defined in interface/ciphertext.h.
class Ciphertext;
/// @brief Forward Declaration of the DigitInteger and CRTInteger class which are defined in interface/integers.h.
class DigitInteger;
class CRTInteger;


/**
 * @brief This is the main class of the high level API. It is used to generate the FHE public keys, encrypt and decrypt messages, run functional bootstrapping, and serialize.
 *  The class hides all keys etc. from the user. No need to worry about the details of the underlying scheme.
 */
class FHEContext{

    public:
    /// @brief The FHE configuration
    std::shared_ptr<FHEConfiguration> config;  
 
    FHEContext(FHENamedParams name); 

    FHEContext(); 
  
    FHEContext(const FHEContext& other);

    FHEContext& operator=(const FHEContext& other);

    /// @brief Generates the FHE context given the named parameters.
    /// @param name The named parameters.
    void generate_context(FHENamedParams name);
 
    /// @brief Encrypts a message. Requires the secret key.
    /// @param message The message to be encrypted
    /// @param type Use this encoding type instead of the default one.
    /// @return Returns a new Ciphertext object.
    Ciphertext encrypt(int64_t message, PlaintextEncodingType type)const;  

    /// @brief Encrypts a message. Requires the secret key.
    /// @param message The message to be encrypted
    /// @param plaintext_space Use this plaintext space instead of the default one.
    /// @return Returns a new Ciphertext object.
    Ciphertext encrypt(int64_t message, int64_t plaintext_space)const;
 
    /// @brief Encrypts a message. Requires the secret key.
    /// @param message The message to be encrypted
    /// @param type Use this encoding type instead of the default one.
    /// @param plaintext_space Use this plaintext space instead of the default one.
    /// @return Returns a new Ciphertext object.
    Ciphertext encrypt(int64_t message, PlaintextEncodingType type, int64_t plaintext_space)const;

    /// @brief Encrypts a message. Requires the secret key.
    /// @param message The message to be encrypted
    /// @param encoding Use this plaintext encoding instead of the default one. 
    /// @return Returns a new Ciphertext object.
    Ciphertext encrypt(int64_t message, PlaintextEncoding encoding)const; 

    /// @brief Encrypts a message using the default plaintext encoding. Requires the secret key.
    /// @param message The message to be encrypted 
    /// @return Returns a new Ciphertext object.
    Ciphertext encrypt(int64_t message)const;

    /// @brief Encrypts a message using the default plaintext encoding. Requires the public key.
    /// @param message The message to be encrypted 
    /// @return Returns a new Ciphertext object.
    Ciphertext encrypt_public(int64_t message, PlaintextEncodingType type)const;  

    /// @brief Encrypts a message. Requires the public key.
    /// @param message The message to be encrypted
    /// @param plaintext_space Use this plaintext space instead of the default one.
    /// @return Returns a new Ciphertext object.
    Ciphertext encrypt_public(int64_t message, int64_t plaintext_space)const;
 
    /// @brief Encrypts a message. Requires the public key.
    /// @param message The message to be encrypted
    /// @param type Use this encoding type instead of the default one.
    /// @param plaintext_space Use this plaintext space instead of the default one.
    /// @return Returns a new Ciphertext object.
    Ciphertext encrypt_public(int64_t message, PlaintextEncodingType type, int64_t plaintext_space)const;

    /// @brief Encrypts a message. Requires the public key.
    /// @param message The message to be encrypted
    /// @param encoding Use this plaintext encoding instead of the default one. 
    /// @return Returns a new Ciphertext object.
    Ciphertext encrypt_public(int64_t message, PlaintextEncoding encoding)const; 

    /// @brief Encrypts a message using the default plaintext encoding. Requires the public key.
    /// @param message The message to be encrypted 
    /// @return Returns a new Ciphertext object.
    Ciphertext encrypt_public(int64_t message)const;
    
    /// @brief Decrypt the input Ciphertext (requires public key)
    /// @param ct The input ciphertext
    /// @return Return the decrypted integer.
    int64_t decrypt(const Ciphertext& ct)const;

    /// @brief Decrypt the input Ciphertext  
    /// @param ct The input ciphertext
    /// @return Return the decrypted integer.
    int64_t decrypt(const DigitInteger& ct)const;

    /// @brief Decrypt the input Ciphertext  
    /// @param ct The input ciphertext
    /// @return Return the decrypted integer.
    int64_t decrypt(const CRTInteger& ct)const;

    // Getters and setter for default plaintext encoding (requires either secret kor public key)

    /// @brief Get the currently used default plaintext encoding
    /// @return Returns the default plaintext encoding.
    PlaintextEncoding get_default_plaintext_encoding()const;

    /// @brief Sets the default plaintext encoding
    /// @param type The enum type of the encoding
    /// @param plaintext_space The sizez of the plaintext space
    //void set_default_plaintext_encoding(PlaintextEncodingType type, int64_t plaintext_space);
  
    /// @brief Returns the curently set default plaintext space
    /// @return The default plaintext space
    int64_t get_default_plaintext_space()const;

    /// @brief Set the default plaintext space
    /// @param plaintext_space The size of the plaintext space
    //void set_default_plaintext_space(int64_t plaintext_space);
  
    /// @brief Get the currently used default message encoding
    /// @return The default message encoding
    PlaintextEncodingType get_default_plaintext_encoding_type()const;

    /// @brief Set the default message encoding
    /// @param type The enum type of the encoding
    //void set_default_message_encoding_type(PlaintextEncodingType type);
    
    /// @brief Generates a homomoprhic Accumulator that embedds the function f
    /// @param f The function to be embedded
    /// @param input_encoding The encoding of the plaintext space for the ciphertext input to a function
    /// @param output_encoding The encoding of the plaintext space for the ciphertext output from a function
    /// @return The homomorphic accumulator
    /// @note Use this function if the intended input and output encodings are different from the current context default.
    HomomorphicAccumulator setup_function(std::function<int64_t(int64_t)> f, PlaintextEncoding input_encoding, PlaintextEncoding output_encoding)const;
 
    /// @brief Generates a homomoprhic Accumulator that embedds the function f
    /// @param f The function to be embedded
    /// @param encoding The encoding of the plaintext space for the ciphertext input and output to a function
    /// @return The homomorphic accumulator
    /// @note Use this function if the intended input and output encoding is different from the current context default.
    HomomorphicAccumulator setup_function(std::function<int64_t(int64_t)> f, PlaintextEncoding encoding)const;

    /// @brief Generates a homomoprhic Accumulator that embedds the function f
    /// @param f The function to be embedded 
    /// @return The homomorphic accumulator
    /// @note The the fuction uses the default plaintext encoding for both input and output encoding.
    HomomorphicAccumulator setup_function(std::function<int64_t(int64_t)> f)const;

    /// @brief Evaluate the homomoprhic accumulator on the input ciphertext. This runs the function bootstrapping algorithm.
    /// @param ct_in The input ciphertext to be bootstrapped.
    /// @param lut The homomorphic accumulator
    /// @return The bootstrapped ciphertext
    /// TODO: input and output encoding should be defined already in HomomorphicAccumulator!
    //Ciphertext eval(const Ciphertext& ct_in, const HomomorphicAccumulator& lut, PlaintextEncoding output_encoding)const;

    /// @brief Evaluate the homomoprhic accumulator on the input ciphertext. This runs the function bootstrapping algorithm.
    /// @param ct_in The input ciphertext to be bootstrapped.
    /// @param lut The homomorphic accumulator
    /// @return The bootstrapped ciphertext
    Ciphertext eval(const Ciphertext& ct_in, const HomomorphicAccumulator& lut)const;
    
    /// @brief Evaluate the function on the input ciphertext. This runs the function bootstrapping algorithm.
    /// @param ct_in The input ciphertext to be bootstrapped.
    /// @param output_encoding The plaintext encoding (if different from the default one). Input encoding is defined in ct_in
    /// @return The bootstrapped ciphertext
    Ciphertext eval(const Ciphertext& ct_in, std::function<int64_t(int64_t)> f, PlaintextEncoding output_encoding)const;
  
    /// @brief Evaluate the function on the input ciphertext. This runs the function bootstrapping algorithm.
    /// @param ct_in The input ciphertext to be bootstrapped. 
    /// @return The bootstrapped ciphertext
    //Ciphertext eval(const Ciphertext& ct_in, int64_t (*f)(int64_t message));
    Ciphertext eval(const Ciphertext& ct_in, std::function<int64_t(int64_t)> f)const;
    
    /// @brief Sanitize the input ciphertext.  
    /// @param ct_in The input ciphertext to be sanitized.
    /// @return A new sanitized ciphertext, which is inpedendent of the input ciphertext, but which encodes the same message.
    Ciphertext sanitize(const Ciphertext& ct_in)const;
  
    /// @brief Evaluates the set of homomorphic accumulators on the input ciphertext. This function bootstraps the input ciphertext. 
    /// @param ct_in The input ciphertext to be bootstrapped.
    /// @param luts The vector of homomorphic accumulators
    /// @return A vector of ciphertexts correspondng to the accumulator evaluations
    std::vector<Ciphertext> eval(const Ciphertext& ct_in, std::vector<HomomorphicAccumulator> luts)const;

    /// @brief Evaluates the set of homomorphic accumulators on the input ciphertext. This function bootstraps the input ciphertext. 
    /// @param ct_in The input ciphertext to be bootstrapped.
    /// @param luts The vector of homomorphic accumulators
    /// @param output_encopding Output encoding of a ciphertext. Input encoding is defined in ct_in
    /// @return A vector of ciphertexts correspondng to the accumulator evaluations
    //std::vector<Ciphertext> eval(const Ciphertext& ct_in, std::vector<HomomorphicAccumulator> luts, PlaintextEncoding output_encopding)const;
   
    /// @brief Evaluates scalar + Sum_i(scalars[i] * ct_vec[i])
    /// @param ct_vec In input ciphertexts
    /// @param scalars The vector of scalars
    /// @param scalar The scalar that is added to the inner product
    /// @return A new ciphertext encrypting the result of the computation. 
    Ciphertext eval_affine_function(std::vector<Ciphertext>& ct_vec, std::vector<int64_t> scalars, int64_t scalar)const;
    
    /// @brief Serialize the secret key to the output file stream
    /// @param os The output file stream
    void send_secret_key(std::ofstream &os);

    /// @brief Reads the secret key from the input file stream
    /// @param is The input file stream
    void read_secret_key(std::ifstream &is);
 
    /// @brief Store the secret key to the file
    /// @param file_name The name of the file
    void save_secret_key(std::string file_name);

    /// @brief Load the secret key from the file
    /// @param file_name The name of the file
    void load_secret_key(std::string file_name);
    
    /// @brief Serialize the public key to the output file stream
    /// @param os The output file stream
    void send_public_key(std::ofstream &os);

    /// @brief Reads the public key from the input file stream
    /// @param is The input file stream
    void read_public_key(std::ifstream &is);
 
    /// @brief Store the public key to the file
    /// @param file_name The name of the file
    void save_public_key(std::string file_name);

    /// @brief Reads the public key from the file
    /// @param file_name The name of the file
    void load_public_key(std::string file_name);

    /// @brief Serialize the ciphertext to the output file stream
    /// @param os The output file stream
    /// @param ct The input ciphertext
    void send_Ciphertext(std::ostream &os, Ciphertext &ct)const;

    /// @brief Read the ciphertext from the input file stream. The ciphertext points to this context.
    /// @param is The input file stream
    /// @return A new ciphertext object
    Ciphertext read_Ciphertext(std::ifstream &is);
 
    /// @brief Same the ciphertext to the file
    /// @param file_name The name of the file
    /// @param ct The input ciphertext
    void save_Ciphertext(std::string file_name, Ciphertext &ct);

    /// @brief Load a ciphertext from a file. The ciphertext points to this context.
    /// @param file_name The name of the file
    /// @return A new ciphertext object
    Ciphertext load_Ciphertext(std::string file_name); 
};
 
} /// End of namespace fhe_deck
 
/// @brief Overload the << operator for the Ciphertext class. Sents the ciphertext to the output stream.
/// @param out The output stream
/// @param c The input ciphertext
/// @return Reference to the output stream, after the ciphertext has been sent.
std::ostream& operator<<(std::ostream &out, fhe_deck::Ciphertext &c);

#endif