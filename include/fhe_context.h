#ifndef FHE_CONTEXT_H
#define FHE_CONTEXT_H


#include "ciphertext.h"
#include "ntrunium_gen.h"
#include "rlwe_hom_acc_scheme_gen.h"
#include "enums.h" 
#include "plaintext_encoding.h"

class fhe_context{

    public:

    ntrunium_named_param_generator ntrunium_par;
    bool is_ntrunium = false;
 
    rlwe_hom_acc_scheme_gen tfhe_boot_sk; 
    std::unique_ptr<rlwe_hom_acc_scheme> tfhe_boot_pk;
    //rlwe_hom_acc_scheme tfhe_boot_pk;
    bool is_tfhe = false;

    // Flags to check whether the sk or pk are initialized.
    bool is_sk_init = false;
    bool is_pk_init = false;
  
    plaintext_encoding default_encoding; 

    ~fhe_context(); 

    fhe_context() = default; 
 
    void generate_context(ntrunium_named_param name);

    void generate_context(rlwe_hom_acc_scheme_named_param name);

    // This is going to generate both secret key and public key
    // In the future we may have, some read secret/public key from file
    // I also may have a function like: export public key, and export secret key. Right?
    // But for now, store the secret key, bootstrapping key etc. internally.
    void key_gen();

    // Return a LWE ciphertext
    ciphertext encrypt(long message, plaintext_encoding_type type);  

    ciphertext encrypt(long message, long plaintext_space);
 
    ciphertext encrypt(long message, plaintext_encoding_type type, long plaintext_space);

    ciphertext encrypt(long message, plaintext_encoding encoding); 

    ciphertext encrypt(long message);


    // Return a LWE ciphertext
    ciphertext encrypt_public(long message, plaintext_encoding_type type);  

    ciphertext encrypt_public(long message, long plaintext_space);
 
    ciphertext encrypt_public(long message, plaintext_encoding_type type, long plaintext_space);

    ciphertext encrypt_public(long message, plaintext_encoding encoding); 

    ciphertext encrypt_public(long message);
  
    // Decrypt an LWE ciphertext
    long decrypt(ciphertext *ct);
  

    plaintext_encoding get_default_plaintext_encoding();

    void set_default_plaintext_encoding(plaintext_encoding_type type, long plaintext_space);
  
    // Return the plaintext space for FDFB or for native TFHE (minus one bit)
    long get_default_plaintext_space();

    // Set a custom plaintext space
    void set_default_plaintext_space(long plaintext_space);

    // Return the currently set default message encoding
    plaintext_encoding_type get_default_message_encoding();

    // Set the message encoding
    void set_default_message_encoding_type(plaintext_encoding_type type);

    // Take a pointer to a function  
    rotation_poly genrate_lut(long (*f)(long message, long plaintext_space), plaintext_encoding encoding);

    rotation_poly genrate_lut(long (*f)(long message, long plaintext_space));
  
    rotation_poly genrate_lut(long (*f)(long message), plaintext_encoding encoding);

    rotation_poly genrate_lut(long (*f)(long message));


    // Run functional bootstrapping
    ciphertext eval_lut(ciphertext *ct_in, rotation_poly lut);
  

    // Generate rotation_poly and run LUT
    ciphertext eval_lut(ciphertext *ct_in, long (*f)(long message, long plaintext_space), plaintext_encoding encoding);
 

    ciphertext eval_lut(ciphertext *ct_in, long (*f)(long message, long plaintext_space));
 

    ciphertext eval_lut(ciphertext *ct_in, long (*f)(long message), plaintext_encoding encoding);
 

    ciphertext eval_lut(ciphertext *ct_in, long (*f)(long message));
 

    std::vector<ciphertext> eval_lut_amortized(ciphertext *ct_in, std::vector<rotation_poly> luts);
  
    // Evaluates scalar + Sum_i(scalars[i] * ct_vec[i]) 
    ciphertext eval_affine_function(std::vector<ciphertext> ct_vec, std::vector<long> scalars, long scalar);
   

private:
 
    rotation_poly generate_rotation_poly_for_signed_limied_short_int_encoding(long (*f)(long message));

    rotation_poly generate_rotation_poly_for_signed_limied_short_int_encoding(long (*f)(long message, long plaintext_space));


};

#endif