#ifndef FHE_CONTEXT_H
#define FHE_CONTEXT_H

#include "ciphertext.h" 
#include "fhe_configuration.h"
#include "enums.h" 
#include "plaintext_encoding.h"
  
#include <cereal/archives/binary.hpp> 
#include <cereal/types/memory.hpp>
#include <fstream>


namespace fhe_deck{

class FHEContext{

    public:
   

    std::shared_ptr<FHEConfiguration> config; 
  
    PlaintextEncoding current_encoding; 
  
    FHEContext(); 
  
    void generate_context(FHENamedParams name);
 
    // Return a LWE Ciphertext (requires secret key)
    Ciphertext encrypt(int64_t message, PlaintextEncodingType type);  

    Ciphertext encrypt(int64_t message, int64_t plaintext_space);
 
    Ciphertext encrypt(int64_t message, PlaintextEncodingType type, int64_t plaintext_space);

    Ciphertext encrypt(int64_t message, PlaintextEncoding encoding); 

    Ciphertext encrypt(int64_t message);

    // Return a LWE Ciphertext (requires public key)
    Ciphertext encrypt_public(int64_t message, PlaintextEncodingType type);  

    Ciphertext encrypt_public(int64_t message, int64_t plaintext_space);
 
    Ciphertext encrypt_public(int64_t message, PlaintextEncodingType type, int64_t plaintext_space);

    Ciphertext encrypt_public(int64_t message, PlaintextEncoding encoding); 

    Ciphertext encrypt_public(int64_t message);
  
    // Decrypt an LWE Ciphertext (requires secret key)
    int64_t decrypt(Ciphertext *ct);

    // Getters and setter for default plaintext encoding (requires either secret kor public key)
    PlaintextEncoding get_default_plaintext_encoding();

    void set_default_plaintext_encoding(PlaintextEncodingType type, int64_t plaintext_space);
  
    // Return the plaintext space for FDFB or for native TFHE (minus one bit)
    int64_t get_default_plaintext_space();

    // Set a custom plaintext space
    void set_default_plaintext_space(int64_t plaintext_space);

    // Return the currently set default message encoding
    PlaintextEncodingType get_default_message_encoding();

    // Set the message encoding
    void set_default_message_encoding_type(PlaintextEncodingType type);

    // Take a pointer to a function  (requires public key) 
    HomomorphicAccumulator genrate_lut(int64_t (*f)(int64_t message, int64_t plaintext_space), PlaintextEncoding encoding);

    HomomorphicAccumulator genrate_lut(int64_t (*f)(int64_t message, int64_t plaintext_space));
  
    HomomorphicAccumulator genrate_lut(int64_t (*f)(int64_t message), PlaintextEncoding encoding);

    HomomorphicAccumulator genrate_lut(int64_t (*f)(int64_t message));

    // Run functional bootstrapping (requires public key)
    Ciphertext eval_lut(Ciphertext *ct_in, HomomorphicAccumulator lut);
   
    // Generate rotation_poly and run LUT
    Ciphertext eval_lut(Ciphertext *ct_in, int64_t (*f)(int64_t message, int64_t plaintext_space), PlaintextEncoding encoding);
  
    Ciphertext eval_lut(Ciphertext *ct_in, int64_t (*f)(int64_t message, int64_t plaintext_space));
  
    Ciphertext eval_lut(Ciphertext *ct_in, int64_t (*f)(int64_t message), PlaintextEncoding encoding);
  
    Ciphertext eval_lut(Ciphertext *ct_in, int64_t (*f)(int64_t message));

    Ciphertext sanitize(Ciphertext *ct_in);
  
    std::vector<Ciphertext> eval_lut_amortized(Ciphertext *ct_in, std::vector<HomomorphicAccumulator> luts);
  
    // Evaluates scalar + Sum_i(scalars[i] * ct_vec[i]) 
    Ciphertext eval_affine_function(std::vector<Ciphertext> ct_vec, std::vector<int64_t> scalars, int64_t scalar);
    
    void send_secret_key(std::ofstream &os);

    void read_secret_key(std::ifstream &is);
 
    void save_secret_key(std::string file_name);

    void load_secret_key(std::string file_name);
    
    void send_public_key(std::ofstream &os);

    void read_public_key(std::ifstream &is);
 
    void save_public_key(std::string file_name);

    void load_public_key(std::string file_name);

    void send_Ciphertext(std::ostream &os, Ciphertext &ct);

    Ciphertext read_Ciphertext(std::ifstream &is);
 
    void save_Ciphertext(std::string file_name, Ciphertext &ct);

    Ciphertext load_Ciphertext(std::string file_name); 
};
  
} /// End of namespace fhe_deck
 
std::ostream& operator<<(std::ostream &out, const fhe_deck::Ciphertext &c);

#endif