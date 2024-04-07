#ifndef FHE_CONTEXT_H
#define FHE_CONTEXT_H

#include "ciphertext.h"
#include "ntrunium_gen.h"
#include "fhe_configuration.h"
#include "enums.h" 
#include "plaintext_encoding.h"
  
#include <cereal/archives/binary.hpp> 
#include <cereal/types/memory.hpp>
#include <fstream>


namespace fhe_deck{

class FHEContext{

    public:

    ntrunium_named_param_generator ntrunium_par;
    bool is_ntrunium = false;
 
    FunctionalBootstrapSecretKey tfhe_boot_sk; 
    std::shared_ptr<FunctionalBootstrapPublicKey> tfhe_boot_pk; 
    bool is_tfhe = false;

    // Flags to check whether the sk or pk are initialized.
    bool is_sk_init = false;
    bool is_pk_init = false;
  
    PlaintextEncoding default_encoding; 
  
    FHEContext() = default; 
 
    void generate_context(ntrunium_named_param name);

    void generate_context(FHENamedParams name);

    // This is going to generate both secret key and public key
    // In the future we may have, some read secret/public key from file
    // I also may have a function like: export public key, and export secret key. Right?
    // But for now, store the secret key, bootstrapping key etc. internally.
    void key_gen();

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
  
}
 
std::ostream& operator<<(std::ostream &out, const fhe_deck::Ciphertext &c);

#endif