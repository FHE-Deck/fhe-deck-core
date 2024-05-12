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
  
    //std::shared_ptr<fhe_deck::LWESK> lwe_sk; 
    //std::shared_ptr<FunctionalBootstrapPublicKey> bootstrap_pk;  
    //std::shared_ptr<LWEPublicKey> encrypt_pk; 
    //std::shared_ptr<AbstractAccumulatorBuilder> accumulator_builder;
    //std::shared_ptr<SanitizationKey> sanitization_pk;

    std::unique_ptr<FHEConfiguration> config;

    // Flags to check whether the sk or pk are initialized.
    //bool is_sk_init = false;
    //bool is_pk_init = false;
  
    PlaintextEncoding default_encoding; 
  
    FHEContext() = default; 
  
    void generate_context(FHENamedParams name);
 
    // Return a LWE Ciphertext (requires secret key)
    Ciphertext encrypt(long message, PlaintextEncodingType type);  

    Ciphertext encrypt(long message, long plaintext_space);
 
    Ciphertext encrypt(long message, PlaintextEncodingType type, long plaintext_space);

    Ciphertext encrypt(long message, PlaintextEncoding encoding); 

    Ciphertext encrypt(long message);

    // Return a LWE Ciphertext (requires public key)
    Ciphertext encrypt_public(long message, PlaintextEncodingType type);  

    Ciphertext encrypt_public(long message, long plaintext_space);
 
    Ciphertext encrypt_public(long message, PlaintextEncodingType type, long plaintext_space);

    Ciphertext encrypt_public(long message, PlaintextEncoding encoding); 

    Ciphertext encrypt_public(long message);
  
    // Decrypt an LWE Ciphertext (requires secret key)
    long decrypt(Ciphertext *ct);

    // Getters and setter for default plaintext encoding (requires either secret kor public key)
    PlaintextEncoding get_default_plaintext_encoding();

    void set_default_plaintext_encoding(PlaintextEncodingType type, long plaintext_space);
  
    // Return the plaintext space for FDFB or for native TFHE (minus one bit)
    long get_default_plaintext_space();

    // Set a custom plaintext space
    void set_default_plaintext_space(long plaintext_space);

    // Return the currently set default message encoding
    PlaintextEncodingType get_default_message_encoding();

    // Set the message encoding
    void set_default_message_encoding_type(PlaintextEncodingType type);

    // Take a pointer to a function  (requires public key) 
    HomomorphicAccumulator genrate_lut(long (*f)(long message, long plaintext_space), PlaintextEncoding encoding);

    HomomorphicAccumulator genrate_lut(long (*f)(long message, long plaintext_space));
  
    HomomorphicAccumulator genrate_lut(long (*f)(long message), PlaintextEncoding encoding);

    HomomorphicAccumulator genrate_lut(long (*f)(long message));

    // Run functional bootstrapping (requires public key)
    Ciphertext eval_lut(Ciphertext *ct_in, HomomorphicAccumulator lut);
   
    // Generate rotation_poly and run LUT
    Ciphertext eval_lut(Ciphertext *ct_in, long (*f)(long message, long plaintext_space), PlaintextEncoding encoding);
  
    Ciphertext eval_lut(Ciphertext *ct_in, long (*f)(long message, long plaintext_space));
  
    Ciphertext eval_lut(Ciphertext *ct_in, long (*f)(long message), PlaintextEncoding encoding);
  
    Ciphertext eval_lut(Ciphertext *ct_in, long (*f)(long message));

    Ciphertext sanitize(Ciphertext *ct_in);
  
    std::vector<Ciphertext> eval_lut_amortized(Ciphertext *ct_in, std::vector<HomomorphicAccumulator> luts);
  
    // Evaluates scalar + Sum_i(scalars[i] * ct_vec[i]) 
    Ciphertext eval_affine_function(std::vector<Ciphertext> ct_vec, std::vector<long> scalars, long scalar);
    
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