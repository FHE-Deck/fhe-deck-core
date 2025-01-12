#include "interface/fhe_context.h"

using namespace fhe_deck;
 
FHEContext::FHEContext(){
    config = std::shared_ptr<FHEConfiguration>(new FHEConfiguration());
} 
  
void FHEContext::generate_context(FHENamedParams name){    
    config = std::shared_ptr<FHEConfiguration>(new FHEConfiguration(name));
    config->generate_keys(); 
    current_encoding = config->eval_key.default_encoding;  
}

Ciphertext FHEContext::encrypt(int64_t message, PlaintextEncodingType type){  
    if(!config->is_secret_key_set){
        throw std::logic_error("No Secret Key Initialized!");
    }
    PlaintextEncoding encoding = current_encoding;
    encoding.set_type(type);
    return encrypt(message, encoding);
}

Ciphertext FHEContext::encrypt(int64_t message, int64_t plaintext_space){
    if(!config->is_secret_key_set){
        throw std::logic_error("No Secret Key Initialized!");
    }
    PlaintextEncoding encoding = current_encoding;
    encoding.set_plaintext_space(plaintext_space);
    return encrypt(message, encoding);
}
 
Ciphertext FHEContext::encrypt(int64_t message, PlaintextEncodingType type, int64_t plaintext_space){
    if(!config->is_secret_key_set){
        throw std::logic_error("No Secret Key Initialized!");
    }
    PlaintextEncoding encoding = current_encoding;
    encoding.set_type(type);
    encoding.set_plaintext_space(plaintext_space);
    return encrypt(message, encoding);
}
 
Ciphertext FHEContext::encrypt(int64_t message, PlaintextEncoding encoding){  
    if(!config->is_secret_key_set){
        throw std::logic_error("No Secret Key Initialized!");
    }        
    std::shared_ptr<LWECT> c(config->secret_key->lwe_sk->encrypt(encoding.encode_message(message)));
    return Ciphertext(c, encoding, this); 
}

Ciphertext FHEContext::encrypt(int64_t message){
    if(!config->is_secret_key_set){
        throw std::logic_error("No Secret Key!");
    }
    return encrypt(message, current_encoding);
}

Ciphertext FHEContext::encrypt_public(int64_t message, PlaintextEncodingType type){  
    if(!config->eval_key.is_encrypt_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }
    PlaintextEncoding encoding = current_encoding;
    encoding.set_type(type);
    return encrypt_public(message, encoding);
}

Ciphertext FHEContext::encrypt_public(int64_t message, int64_t plaintext_space){
    if(!config->eval_key.is_encrypt_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }
    PlaintextEncoding encoding = current_encoding;
    encoding.set_plaintext_space(plaintext_space);
    return encrypt_public(message, encoding);
}

Ciphertext FHEContext::encrypt_public(int64_t message, PlaintextEncodingType type, int64_t plaintext_space){
    if(!config->eval_key.is_encrypt_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }
    PlaintextEncoding encoding = current_encoding;
    encoding.set_type(type);
    encoding.set_plaintext_space(plaintext_space);
    return encrypt_public(message, encoding);
}

Ciphertext FHEContext::encrypt_public(int64_t message, PlaintextEncoding encoding){  
    if(!config->eval_key.is_encrypt_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    } 
    std::shared_ptr<LWECT> c(config->eval_key.encrypt_pk->encrypt(encoding.encode_message(message))); 
    return Ciphertext(c, encoding, this);
}

Ciphertext FHEContext::encrypt_public(int64_t message){
    if(!config->eval_key.is_encrypt_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }
    return encrypt_public(message, current_encoding);
}

int64_t FHEContext::decrypt(const Ciphertext& c_in){
    if(!config->is_secret_key_set){
        throw std::logic_error("No Secret Key Initialized!");
    }  
    return config->secret_key->lwe_sk->decrypt(*c_in.lwe_c, c_in.encoding);
}
 
PlaintextEncoding FHEContext::get_default_plaintext_encoding(){
    return current_encoding;
}

void FHEContext::set_default_plaintext_encoding(PlaintextEncodingType type, int64_t plaintext_space){
    this->current_encoding = PlaintextEncoding(type, plaintext_space, current_encoding.get_ciphertext_modulus()); 
}
 
int64_t  FHEContext::get_default_plaintext_space(){
    return current_encoding.get_plaintext_space();
}

void FHEContext::set_default_plaintext_space(int64_t plaintext_space){
    this->current_encoding = PlaintextEncoding(current_encoding.get_type(), plaintext_space, current_encoding.get_ciphertext_modulus());  
}

PlaintextEncodingType FHEContext::get_default_message_encoding(){
    return this->current_encoding.get_type();
}

void FHEContext::set_default_message_encoding_type(PlaintextEncodingType type){ 
    this->current_encoding = PlaintextEncoding(type, current_encoding.get_plaintext_space(), current_encoding.get_ciphertext_modulus());  
}
   
HomomorphicAccumulator FHEContext::setup_function(std::function<int64_t(int64_t)> f, PlaintextEncoding input_encoding, PlaintextEncoding output_encoding){
    if(!config->eval_key.is_bootstrap_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }  
    auto boot_acc = config->eval_key.boot_acc_builder->prepare_specification(f, input_encoding, output_encoding); 
    auto func_spec = config->eval_key.func_boot_acc_builder->prepare_specification(f, input_encoding, output_encoding);
    auto multival_spec = config->eval_key.multivalue_acc_builder->prepare_specification(f, input_encoding, output_encoding);
    HomomorphicAccumulator out(boot_acc, func_spec, multival_spec, input_encoding, output_encoding);
    return out;  
}
 
  
HomomorphicAccumulator FHEContext::setup_function(std::function<int64_t(int64_t)> f){    
    return setup_function(f, current_encoding, current_encoding);
}

Ciphertext FHEContext::eval(const Ciphertext& ct_in, const HomomorphicAccumulator& lut, PlaintextEncoding output_encoding){
    if(!config->eval_key.is_bootstrap_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }   
    if(lut.input_encoding != ct_in.encoding){
        throw std::logic_error("Input encoding of the accumulator does not match the encoding of the input ciphertext!");
    }
    if(lut.output_encoding != output_encoding){
        throw std::logic_error("Output encoding of the accumulator does not match the output encoding!");
    }
    std::shared_ptr<LWECT> ct_out(new LWECT(ct_in.lwe_c->param));  
    if(ct_in.encoding.get_type() == PlaintextEncodingType::full_domain){     
        config->eval_key.bootstrap_pk->full_domain_bootstrap(*ct_out, lut.func_boot_acc, *ct_in.lwe_c, ct_in.encoding, output_encoding);
    }else if(ct_in.encoding.get_type() == PlaintextEncodingType::partial_domain){   
        config->eval_key.bootstrap_pk->bootstrap(*ct_out,  lut.boot_acc, *ct_in.lwe_c); 
    }else if(ct_in.encoding.get_type() == PlaintextEncodingType::signed_limied_short_int){    
        LWECT c_in_copy(ct_in.lwe_c->param);
        ct_in.lwe_c->add(c_in_copy, ct_in.encoding.encode_message(ct_in.encoding.get_plaintext_space()));
        config->eval_key.bootstrap_pk->bootstrap(*ct_out, lut.boot_acc, c_in_copy);   
    } 
    else{
        throw std::logic_error("Non existend encoding type!");
    }   
    return Ciphertext(ct_out, output_encoding, this); 
}
  
Ciphertext FHEContext::eval(const Ciphertext& ct_in, const HomomorphicAccumulator& lut){  
    return this->eval(ct_in, lut, ct_in.encoding); 
}
   
std::vector<Ciphertext> FHEContext::eval(const Ciphertext& ct_in, std::vector<HomomorphicAccumulator> lut_vec){  
    return this->eval(ct_in, lut_vec, ct_in.encoding);
}

std::vector<Ciphertext> FHEContext::eval(const Ciphertext& ct_in, std::vector<HomomorphicAccumulator> lut_vec, PlaintextEncoding output_encoding){
   if(!config->eval_key.is_bootstrap_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }     
    // The output vector of LWECT 
    std::vector<LWECT> out_vec_lwe;   
    if((ct_in.encoding.get_type() == PlaintextEncodingType::full_domain) && !config->eval_key.bootstrap_pk->is_full_domain_bootstrap_function_amortizable){ 
        // Amortization is not supported so lets run sequentially.
        for(HomomorphicAccumulator& acc: lut_vec){
            if(acc.input_encoding != ct_in.encoding){
                throw std::logic_error("Input encoding of the accumulator does not match the encoding of the input ciphertext!");
            }
            if(acc.output_encoding != output_encoding){
                throw std::logic_error("Output encoding of the accumulator does not match the output encoding!");
            }
            LWECT ct_out(ct_in.lwe_c->param);  
            config->eval_key.bootstrap_pk->full_domain_bootstrap(ct_out, acc.func_boot_acc, *ct_in.lwe_c, ct_in.encoding, output_encoding);
            out_vec_lwe.push_back(ct_out);
        }
    // Otherwise we run the amortized procedures. 
    } else{ 
        // We need to get the VectorCTAccumulator's out of the HomomorphicAccumulator wrapper. 
        std::vector<std::shared_ptr<FunctionSpecification>> accumulator_vec;
        for(HomomorphicAccumulator& lut: lut_vec){ 
            if(lut.input_encoding != ct_in.encoding){
                throw std::logic_error("Input encoding of the accumulator does not match the encoding of the input ciphertext!");
            }
            if(lut.output_encoding != output_encoding){
                throw std::logic_error("Output encoding of the accumulator does not match the output encoding!");
            }
            accumulator_vec.push_back(lut.multivalue_acc); 
        }  
        if(ct_in.encoding.get_type() == PlaintextEncodingType::full_domain){ 
            out_vec_lwe = config->eval_key.bootstrap_pk->full_domain_bootstrap(accumulator_vec, *ct_in.lwe_c, ct_in.encoding, output_encoding);
        }else if(ct_in.encoding.get_type() == PlaintextEncodingType::partial_domain){ 
            out_vec_lwe = config->eval_key.bootstrap_pk->bootstrap(accumulator_vec, *ct_in.lwe_c, output_encoding);
        }else if(ct_in.encoding.get_type() == PlaintextEncodingType::signed_limied_short_int){  
            LWECT ct_cast(ct_in.lwe_c->param);
            ct_in.lwe_c->add(ct_cast, ct_in.encoding.encode_message(ct_in.encoding.get_plaintext_space()));
            out_vec_lwe = config->eval_key.bootstrap_pk->bootstrap(accumulator_vec, ct_cast, output_encoding); 
        } 
        else{
            throw std::logic_error("Non existend encoding type!");
        }  
    } 
    // Load the LWECT's into the Ciphertext wrapper
    std::vector<Ciphertext> out_vec;
    for(LWECT ct: out_vec_lwe){
        out_vec.push_back(Ciphertext(std::shared_ptr<LWECT>(ct.clone()), output_encoding, this));
    }  
    return out_vec;
}
 
Ciphertext FHEContext::eval(const Ciphertext& ct_in, std::function<int64_t(int64_t)> f, PlaintextEncoding output_encoding){
    HomomorphicAccumulator lut = this->setup_function(f, ct_in.encoding, output_encoding);
    return eval(ct_in, lut, output_encoding);
}

Ciphertext FHEContext::eval(const Ciphertext& ct_in, std::function<int64_t(int64_t)> f){
    HomomorphicAccumulator lut = this->setup_function(f, ct_in.encoding, ct_in.encoding);
    return eval(ct_in, lut, ct_in.encoding);
}
 
Ciphertext FHEContext::sanitize(const Ciphertext& ct){
    if(!config->eval_key.is_sanitization_supported){
        throw std::logic_error("Sanitization is not supported, or sanitization key is not loaded!");
    }
    std::shared_ptr<LWECT> ct_out(new LWECT(ct.lwe_c->param));  
    config->eval_key.sanitization_pk->sanitize(*ct_out, *ct.lwe_c, ct.encoding);
    return Ciphertext(ct_out, ct.encoding, this); 
}

Ciphertext FHEContext::eval_affine_function(std::vector<Ciphertext>& ct_vec, std::vector<int64_t> scalars, int64_t scalar){    
    Ciphertext ct_out =  ct_vec[0] * scalars[0]; 
    for(int32_t i = 1; i < ct_vec.size(); ++i){ 
            ct_out = ct_out + (ct_vec[i] * scalars[i]); 
    }
    ct_out = ct_out + scalar;
    return ct_out; 
}

void FHEContext::send_secret_key(std::ofstream &os){
    if(!config->is_secret_key_set){
        throw std::logic_error("No Secret Key Initialized!");
    }
    #if defined(USE_CEREAL)
    cereal::BinaryOutputArchive oarchive(os); 
    oarchive(config->secret_key); 
    #else
    throw std::logic_error("Serialization not supported. If you want to use serialization compile FHE-Deck with CEREAL (see the README.md file).");
    #endif
}

void FHEContext::read_secret_key(std::ifstream &is){   
    #if defined(USE_CEREAL)
    cereal::BinaryInputArchive iarchive(is); 
    std::shared_ptr<FHESecretKey> secret_key; 
    iarchive(secret_key);   
    config->secret_key = secret_key; 
    config->is_secret_key_set = true;
    #else
    throw std::logic_error("Serialization not supported. If you want to use serialization compile FHE-Deck with CEREAL (see the README.md file).");
    #endif
}
 
void FHEContext::save_secret_key(std::string file_name){
    std::ofstream os(file_name, std::ios::binary); 
    send_secret_key(os);
    os.close();  
}

void FHEContext::load_secret_key(std::string file_name){ 
    std::ifstream is(file_name, std::ios::binary);
    read_secret_key(is);
    
}

void FHEContext::send_public_key(std::ofstream &os){ 
    #if defined(USE_CEREAL)
    cereal::BinaryOutputArchive oarchive(os); 
    oarchive(config->eval_key);  
    #else
    throw std::logic_error("Serialization not supported. If you want to use serialization compile FHE-Deck with CEREAL (see the README.md file).");
    #endif
}

void FHEContext::read_public_key(std::ifstream &is){
    #if defined(USE_CEREAL)
    cereal::BinaryInputArchive iarchive(is);  
    iarchive(config->eval_key);    
    current_encoding = config->eval_key.default_encoding;
    #else
    throw std::logic_error("Serialization not supported. If you want to use serialization compile FHE-Deck with CEREAL (see the README.md file).");
    #endif
}
 
void FHEContext::save_public_key(std::string file_name){
    std::ofstream os(file_name, std::ios::binary); 
    send_public_key(os);
    os.close();
}

void FHEContext::load_public_key(std::string file_name){
    std::ifstream is(file_name, std::ios::binary);
    read_public_key(is);
}

void FHEContext::send_Ciphertext(std::ostream &os, Ciphertext &ct){
    if(!config->eval_key.is_encrypt_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }
    #if defined(USE_CEREAL)
    cereal::BinaryOutputArchive oarchive(os);   
    oarchive(ct.lwe_c); 
    #else
    throw std::logic_error("Serialization not supported. If you want to use serialization compile FHE-Deck with CEREAL (see the README.md file).");
    #endif
}

Ciphertext FHEContext::read_Ciphertext(std::ifstream &is){
    #if defined(USE_CEREAL)
    cereal::BinaryInputArchive iarchive(is);  
    std::shared_ptr<LWECT> ct;
    iarchive(ct);
    Ciphertext out(ct, this->current_encoding, this);
    return out;
    #else
    throw std::logic_error("Serialization not supported. If you want to use serialization compile FHE-Deck with CEREAL (see the README.md file).");
    #endif
}
 
void FHEContext::save_Ciphertext(std::string file_name, Ciphertext &ct){
    std::ofstream os(file_name, std::ios::binary);   
    send_Ciphertext(os, ct);
}

Ciphertext FHEContext::load_Ciphertext(std::string file_name){
    std::ifstream is(file_name, std::ios::binary);
    return read_Ciphertext(is);
}

std::ostream& operator<<(std::ostream &out, Ciphertext &c){ 
    Ciphertext ct_out(c);
    c.context->send_Ciphertext(out, ct_out); 
    return out;
}
  
