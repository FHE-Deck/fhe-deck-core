#include "fhe_context.h"

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
    encoding.type = type;
    return FHEContext::encrypt(message, encoding);
}

Ciphertext FHEContext::encrypt(int64_t message, int64_t plaintext_space){
    if(!config->is_secret_key_set){
        throw std::logic_error("No Secret Key Initialized!");
    }
    PlaintextEncoding encoding = current_encoding;
    encoding.plaintext_space = plaintext_space;
    return FHEContext::encrypt(message, encoding);
}
 
Ciphertext FHEContext::encrypt(int64_t message, PlaintextEncodingType type, int64_t plaintext_space){
    if(!config->is_secret_key_set){
        throw std::logic_error("No Secret Key Initialized!");
    }
    PlaintextEncoding encoding = current_encoding;
    encoding.type = type;
    encoding.plaintext_space = plaintext_space;
    return FHEContext::encrypt(message, encoding);
}
 
Ciphertext FHEContext::encrypt(int64_t message, PlaintextEncoding encoding){  
    if(!config->is_secret_key_set){
        throw std::logic_error("No Secret Key Initialized!");
    }        
    std::shared_ptr<LWECT> c(config->secret_key->encrypt(encoding.encode_message(message)));
    return Ciphertext(c, encoding, this); 
}

Ciphertext FHEContext::encrypt(int64_t message){
    if(!config->is_secret_key_set){
        throw std::logic_error("No Secret Key!");
    }
    return FHEContext::encrypt(message, current_encoding);
}

Ciphertext FHEContext::encrypt_public(int64_t message, PlaintextEncodingType type){  
    if(!config->eval_key.is_encrypt_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }
    PlaintextEncoding encoding = current_encoding;
    encoding.type = type;
    return FHEContext::encrypt_public(message, encoding);
}

Ciphertext FHEContext::encrypt_public(int64_t message, int64_t plaintext_space){
    if(!config->eval_key.is_encrypt_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }
    PlaintextEncoding encoding = current_encoding;
    encoding.plaintext_space = plaintext_space;
    return FHEContext::encrypt_public(message, encoding);
}

Ciphertext FHEContext::encrypt_public(int64_t message, PlaintextEncodingType type, int64_t plaintext_space){
    if(!config->eval_key.is_encrypt_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }
    PlaintextEncoding encoding = current_encoding;
    encoding.type = type;
    encoding.plaintext_space = plaintext_space;
    return FHEContext::encrypt_public(message, encoding);
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
    return FHEContext::encrypt_public(message, current_encoding);
}

int64_t FHEContext::decrypt(Ciphertext& c_in){
    if(!config->is_secret_key_set){
        throw std::logic_error("No Secret Key Initialized!");
    }  
    return config->secret_key->decrypt(c_in.lwe_c.get(), c_in.encoding);
}
 
PlaintextEncoding FHEContext::get_default_plaintext_encoding(){
    return current_encoding;
}

void FHEContext::set_default_plaintext_encoding(PlaintextEncodingType type, int64_t plaintext_space){
    this->current_encoding = PlaintextEncoding(type, plaintext_space, current_encoding.ciphertext_modulus); 
}
 
int64_t  FHEContext::get_default_plaintext_space(){
    return current_encoding.plaintext_space;
}

void FHEContext::set_default_plaintext_space(int64_t plaintext_space){
    this->current_encoding = PlaintextEncoding(current_encoding.type, plaintext_space, current_encoding.ciphertext_modulus);  
}

PlaintextEncodingType FHEContext::get_default_message_encoding(){
    return this->current_encoding.type;
}

void FHEContext::set_default_message_encoding_type(PlaintextEncodingType type){ 
    this->current_encoding = PlaintextEncoding(type, current_encoding.plaintext_space, current_encoding.ciphertext_modulus);  
}
 
HomomorphicAccumulator FHEContext::genrate_lut(int64_t (*f)(int64_t message, int64_t plaintext_space), PlaintextEncoding encoding){
    if(!config->eval_key.is_bootstrap_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }  
    HomomorphicAccumulator out(std::shared_ptr<VectorCTAccumulator>(config->eval_key.accumulator_builder->prepare_accumulator(f, encoding))); 
    return out; 
}

HomomorphicAccumulator FHEContext::genrate_lut(int64_t (*f)(int64_t message, int64_t plaintext_space)){
    if(!config->eval_key.is_bootstrap_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    } 
    return HomomorphicAccumulator(std::shared_ptr<VectorCTAccumulator>(config->eval_key.accumulator_builder->prepare_accumulator(f, current_encoding))); 
}

HomomorphicAccumulator FHEContext::genrate_lut(int64_t (*f)(int64_t message), PlaintextEncoding encoding){ 
    if(!config->eval_key.is_bootstrap_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }  
    return HomomorphicAccumulator(std::shared_ptr<VectorCTAccumulator>(config->eval_key.accumulator_builder->prepare_accumulator(f, encoding))); 
}
 

HomomorphicAccumulator FHEContext::genrate_lut(int64_t (*f)(int64_t message)){   
    return HomomorphicAccumulator(std::shared_ptr<VectorCTAccumulator>(config->eval_key.accumulator_builder->prepare_accumulator(f, current_encoding))); 
}
  
Ciphertext FHEContext::eval_lut(Ciphertext& ct_in, HomomorphicAccumulator lut){  
    if(!config->eval_key.is_bootstrap_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }  
    std::shared_ptr<LWECT> ct_out(new LWECT(ct_in.lwe_c->param));  
    if(ct_in.encoding.type == full_domain){    
        config->eval_key.bootstrap_pk->full_domain_bootstrap(ct_out.get(), lut.accumulator, ct_in.lwe_c.get(), ct_in.encoding);
    }else if(ct_in.encoding.type == partial_domain){  
        config->eval_key.bootstrap_pk->bootstrap(ct_out.get(),  lut.accumulator, ct_in.lwe_c.get()); 
    }else if(ct_in.encoding.type == signed_limied_short_int){    
        LWECT c_in_copy(ct_in.lwe_c->param);
        ct_in.lwe_c->add(&c_in_copy, ct_in.encoding.encode_message(ct_in.encoding.plaintext_space));
        config->eval_key.bootstrap_pk->bootstrap(ct_out.get(), lut.accumulator, &c_in_copy);   
    } 
    else{
        throw std::logic_error("Non existend encoding type!");
    }   
    return Ciphertext(ct_out, ct_in.encoding, this); 
}
   
std::vector<Ciphertext> FHEContext::eval_lut_amortized(Ciphertext& ct_in, std::vector<HomomorphicAccumulator> lut_vec){ 
    if(!config->eval_key.is_bootstrap_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }    
    // We need to get the VectorCTAccumulator's out of the HomomorphicAccumulator wrapper. 
    std::vector<std::shared_ptr<VectorCTAccumulator>> accumulator_vec;
    for(HomomorphicAccumulator i: lut_vec){
        accumulator_vec.push_back(std::static_pointer_cast<VectorCTAccumulator>(i.accumulator)); 
    } 
    // The output vector of LWECT 
    std::vector<LWECT> out_vec_lwe;   
    if((ct_in.encoding.type == full_domain) && !config->eval_key.bootstrap_pk->is_full_domain_bootstrap_function_amortizable){
        // Amortization is not supported so lets run sequentially.
        for(std::shared_ptr<VectorCTAccumulator> acc: accumulator_vec){
            LWECT ct_out(ct_in.lwe_c->param);  
            config->eval_key.bootstrap_pk->full_domain_bootstrap(&ct_out, acc, ct_in.lwe_c.get(), ct_in.encoding);
            out_vec_lwe.push_back(ct_out);
        }
    // Otherwise we run the amortized procedures. 
    }else if(ct_in.encoding.type == full_domain){ 
        out_vec_lwe = config->eval_key.bootstrap_pk->full_domain_bootstrap(accumulator_vec, ct_in.lwe_c.get(), ct_in.encoding);
    }else if(ct_in.encoding.type == partial_domain){ 
        out_vec_lwe = config->eval_key.bootstrap_pk->bootstrap(accumulator_vec, ct_in.lwe_c.get(), ct_in.encoding);
    }else if(ct_in.encoding.type == signed_limied_short_int){  
        LWECT ct_cast(ct_in.lwe_c->param);
        ct_in.lwe_c->add(&ct_cast, ct_in.encoding.encode_message(ct_in.encoding.plaintext_space));
        out_vec_lwe = config->eval_key.bootstrap_pk->bootstrap(accumulator_vec, &ct_cast, ct_in.encoding); 
    } 
    else{
        throw std::logic_error("Non existend encoding type!");
    }
    // Load the LWECT's into the Ciphertext wrapper
    std::vector<Ciphertext> out_vec;
    for(LWECT ct: out_vec_lwe){
        out_vec.push_back(Ciphertext(std::shared_ptr<LWECT>(ct.clone()), ct_in.encoding, this));
    }  
    return out_vec;
}

Ciphertext FHEContext::eval_lut(Ciphertext& ct_in, int64_t (*f)(int64_t message, int64_t plaintext_space), PlaintextEncoding encoding){
    HomomorphicAccumulator lut = this->genrate_lut(f, encoding);
    return eval_lut(ct_in, lut);
}
 
Ciphertext FHEContext::eval_lut(Ciphertext& ct_in, int64_t (*f)(int64_t message, int64_t plaintext_space)){
    HomomorphicAccumulator lut = this->genrate_lut(f);
    return eval_lut(ct_in, lut);
}

Ciphertext FHEContext::eval_lut(Ciphertext& ct_in, int64_t (*f)(int64_t message), PlaintextEncoding encoding){
    HomomorphicAccumulator lut = this->genrate_lut(f, encoding);
    return eval_lut(ct_in, lut);
}

Ciphertext FHEContext::eval_lut(Ciphertext& ct_in, int64_t (*f)(int64_t message)){
    HomomorphicAccumulator lut = this->genrate_lut(f);
    return eval_lut(ct_in, lut);
}
 
Ciphertext FHEContext::sanitize(Ciphertext& ct){
    if(!config->eval_key.is_sanitization_supported){
        throw std::logic_error("Sanitization is not supported, or sanitization key is not loaded!");
    }
    std::shared_ptr<LWECT> ct_out(new LWECT(ct.lwe_c->param));  
    config->eval_key.sanitization_pk->sanitize(ct_out.get(), ct.lwe_c.get(), ct.encoding);
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
    cereal::BinaryOutputArchive oarchive(os); 
    oarchive(config->secret_key); 
}

void FHEContext::read_secret_key(std::ifstream &is){   
    cereal::BinaryInputArchive iarchive(is); 
    std::shared_ptr<LWESK> secret_key; 
    iarchive(secret_key);   
    config->secret_key = secret_key; 
    config->is_secret_key_set = true;
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
    cereal::BinaryOutputArchive oarchive(os); 
    oarchive(config->eval_key); 
}

void FHEContext::read_public_key(std::ifstream &is){
    cereal::BinaryInputArchive iarchive(is);  
    iarchive(config->eval_key);    
    current_encoding = config->eval_key.default_encoding;
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
    cereal::BinaryOutputArchive oarchive(os);   
    oarchive(ct.lwe_c); 
}

Ciphertext FHEContext::read_Ciphertext(std::ifstream &is){
    cereal::BinaryInputArchive iarchive(is);  
    std::shared_ptr<LWECT> ct;
    iarchive(ct);
    Ciphertext out(ct, this->current_encoding, this);
    return out;
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
  
