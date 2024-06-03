#include "fhe_context.h"

using namespace fhe_deck;
  
void FHEContext::generate_context(FHENamedParams name){    
    config = std::unique_ptr<FHEConfiguration>(new FHEConfiguration(name));
    config->generate_keys(); 
    default_encoding = config->default_encoding;  
}

Ciphertext FHEContext::encrypt(long message, PlaintextEncodingType type){  
    if(!config->is_secret_key_set){
        throw std::logic_error("No Secret Key Initialized!");
    }
    PlaintextEncoding encoding = default_encoding;
    encoding.type = type;
    return FHEContext::encrypt(message, encoding);
}

Ciphertext FHEContext::encrypt(long message, long plaintext_space){
    if(!config->is_secret_key_set){
        throw std::logic_error("No Secret Key Initialized!");
    }
    PlaintextEncoding encoding = default_encoding;
    encoding.plaintext_space = plaintext_space;
    return FHEContext::encrypt(message, encoding);
}
 
Ciphertext FHEContext::encrypt(long message, PlaintextEncodingType type, long plaintext_space){
    if(!config->is_secret_key_set){
        throw std::logic_error("No Secret Key Initialized!");
    }
    PlaintextEncoding encoding = default_encoding;
    encoding.type = type;
    encoding.plaintext_space = plaintext_space;
    return FHEContext::encrypt(message, encoding);
}
 
Ciphertext FHEContext::encrypt(long message, PlaintextEncoding encoding){  
    if(!config->is_secret_key_set){
        throw std::logic_error("No Secret Key Initialized!");
    }        
    std::shared_ptr<LWECT> c(config->secret_key->encrypt(encoding.encode_message(message)));
    return Ciphertext(c, encoding, this); 
}

Ciphertext FHEContext::encrypt(long message){
    if(!config->is_secret_key_set){
        throw std::logic_error("No Secret Key!");
    }
    return FHEContext::encrypt(message, default_encoding);
}

Ciphertext FHEContext::encrypt_public(long message, PlaintextEncodingType type){  
    if(!config->is_encrypt_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }
    PlaintextEncoding encoding = default_encoding;
    encoding.type = type;
    return FHEContext::encrypt_public(message, encoding);
}

Ciphertext FHEContext::encrypt_public(long message, long plaintext_space){
    if(!config->is_encrypt_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }
    PlaintextEncoding encoding = default_encoding;
    encoding.plaintext_space = plaintext_space;
    return FHEContext::encrypt_public(message, encoding);
}

Ciphertext FHEContext::encrypt_public(long message, PlaintextEncodingType type, long plaintext_space){
    if(!config->is_encrypt_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }
    PlaintextEncoding encoding = default_encoding;
    encoding.type = type;
    encoding.plaintext_space = plaintext_space;
    return FHEContext::encrypt_public(message, encoding);
}

Ciphertext FHEContext::encrypt_public(long message, PlaintextEncoding encoding){  
    if(!config->is_encrypt_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    } 
    std::shared_ptr<LWECT> c(config->encrypt_pk->encrypt(encoding.encode_message(message))); 
    return Ciphertext(c, encoding, this);
}

Ciphertext FHEContext::encrypt_public(long message){
    if(!config->is_encrypt_pk_set){
        throw 0;
    }
    return FHEContext::encrypt_public(message, default_encoding);
}

long FHEContext::decrypt(Ciphertext *c_in){
    if(!config->is_secret_key_set){
        throw std::logic_error("No Secret Key Initialized!");
    }  
    return config->secret_key->decrypt(c_in->lwe_c.get(), c_in->encoding);
}
 
PlaintextEncoding FHEContext::get_default_plaintext_encoding(){
    return default_encoding;
}

void FHEContext::set_default_plaintext_encoding(PlaintextEncodingType type, long plaintext_space){
    this->default_encoding = PlaintextEncoding(type, plaintext_space, default_encoding.ciphertext_modulus); 
}
 
long  FHEContext::get_default_plaintext_space(){
    return default_encoding.plaintext_space;
}

void FHEContext::set_default_plaintext_space(long plaintext_space){
    this->default_encoding = PlaintextEncoding(default_encoding.type, plaintext_space, default_encoding.ciphertext_modulus);  
}

PlaintextEncodingType FHEContext::get_default_message_encoding(){
    return this->default_encoding.type;
}

void FHEContext::set_default_message_encoding_type(PlaintextEncodingType type){ 
    this->default_encoding = PlaintextEncoding(type, default_encoding.plaintext_space, default_encoding.ciphertext_modulus);  
}
 
HomomorphicAccumulator FHEContext::genrate_lut(long (*f)(long message, long plaintext_space), PlaintextEncoding encoding){
    if(!config->is_bootstrap_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }  
    HomomorphicAccumulator out(std::shared_ptr<VectorCTAccumulator>(config->accumulator_builder->prepare_accumulator(f, encoding))); 
    return out; 
}

HomomorphicAccumulator FHEContext::genrate_lut(long (*f)(long message, long plaintext_space)){
    if(!config->is_bootstrap_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    } 
    return HomomorphicAccumulator(std::shared_ptr<VectorCTAccumulator>(config->accumulator_builder->prepare_accumulator(f, default_encoding))); 
}

HomomorphicAccumulator FHEContext::genrate_lut(long (*f)(long message), PlaintextEncoding encoding){ 
    if(!config->is_bootstrap_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }  
    return HomomorphicAccumulator(std::shared_ptr<VectorCTAccumulator>(config->accumulator_builder->prepare_accumulator(f, encoding))); 
}
 

HomomorphicAccumulator FHEContext::genrate_lut(long (*f)(long message)){   
    return HomomorphicAccumulator(std::shared_ptr<VectorCTAccumulator>(config->accumulator_builder->prepare_accumulator(f, default_encoding))); 
}
  
Ciphertext FHEContext::eval_lut(Ciphertext *ct_in, HomomorphicAccumulator lut){  
    if(!config->is_bootstrap_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }  
    std::shared_ptr<LWECT> ct_out(new LWECT(ct_in->lwe_c->param));  
    if(ct_in->encoding.type == full_domain){    
        config->bootstrap_pk->full_domain_bootstrap(ct_out.get(), lut.accumulator, ct_in->lwe_c.get(), ct_in->encoding);
    }else if(ct_in->encoding.type == partial_domain){  
        config->bootstrap_pk->bootstrap(ct_out.get(),  lut.accumulator, ct_in->lwe_c.get()); 
    }else if(ct_in->encoding.type == signed_limied_short_int){    
        LWECT c_in_copy(ct_in->lwe_c->param);
        ct_in->lwe_c->add(&c_in_copy, ct_in->encoding.encode_message(ct_in->encoding.plaintext_space));
        config->bootstrap_pk->bootstrap(ct_out.get(), lut.accumulator, &c_in_copy);   
    } 
    else{
        throw std::logic_error("Non existend encoding type!");
    }   
    return Ciphertext(ct_out, ct_in->encoding, this); 
}
   
std::vector<Ciphertext> FHEContext::eval_lut_amortized(Ciphertext *ct_in, std::vector<HomomorphicAccumulator> lut_vec){ 
    if(!config->is_bootstrap_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }    
    // We need to get the VectorCTAccumulator's out of the HomomorphicAccumulator wrapper. 
    std::vector<std::shared_ptr<VectorCTAccumulator>> accumulator_vec;
    for(HomomorphicAccumulator i: lut_vec){
        accumulator_vec.push_back(std::static_pointer_cast<VectorCTAccumulator>(i.accumulator)); 
    } 
    // The output vector of LWECT 
    std::vector<LWECT> out_vec_lwe;   
    if((ct_in->encoding.type == full_domain) && !config->bootstrap_pk->is_full_domain_bootstrap_function_amortizable){
    // Amortization is not supported so lets run sequentially.
    for(std::shared_ptr<VectorCTAccumulator> acc: accumulator_vec){
        LWECT ct_out(ct_in->lwe_c->param);  
        config->bootstrap_pk->full_domain_bootstrap(&ct_out, acc, ct_in->lwe_c.get(), ct_in->encoding);
        out_vec_lwe.push_back(ct_out);
    }
    // Otherwise we run the amortized procedures. 
    }else if(ct_in->encoding.type == full_domain){ 
        out_vec_lwe = config->bootstrap_pk->full_domain_bootstrap(accumulator_vec, ct_in->lwe_c.get(), ct_in->encoding);
    }else if(ct_in->encoding.type == partial_domain){ 
        out_vec_lwe = config->bootstrap_pk->bootstrap(accumulator_vec, ct_in->lwe_c.get(), ct_in->encoding);
    }else if(ct_in->encoding.type == signed_limied_short_int){  
        LWECT ct_cast(ct_in->lwe_c->param);
        ct_in->lwe_c->add(&ct_cast, ct_in->encoding.encode_message(ct_in->encoding.plaintext_space));
        out_vec_lwe = config->bootstrap_pk->bootstrap(accumulator_vec, &ct_cast, ct_in->encoding); 
    } 
    else{
        throw std::logic_error("Non existend encoding type!");
    }
    // Load the LWECT's into the Ciphertext wrapper
    std::vector<Ciphertext> out_vec;
    for(LWECT ct: out_vec_lwe){
        out_vec.push_back(Ciphertext(std::shared_ptr<LWECT>(ct.clone()), ct_in->encoding, this));
    }  
    return out_vec;
}

Ciphertext FHEContext::eval_lut(Ciphertext *ct_in, long (*f)(long message, long plaintext_space), PlaintextEncoding encoding){
    HomomorphicAccumulator lut = this->genrate_lut(f, encoding);
    return eval_lut(ct_in, lut);
}
 
Ciphertext FHEContext::eval_lut(Ciphertext *ct_in, long (*f)(long message, long plaintext_space)){
    HomomorphicAccumulator lut = this->genrate_lut(f);
    return eval_lut(ct_in, lut);
}

Ciphertext FHEContext::eval_lut(Ciphertext *ct_in, long (*f)(long message), PlaintextEncoding encoding){
    HomomorphicAccumulator lut = this->genrate_lut(f, encoding);
    return eval_lut(ct_in, lut);
}

Ciphertext FHEContext::eval_lut(Ciphertext *ct_in, long (*f)(long message)){
    HomomorphicAccumulator lut = this->genrate_lut(f);
    return eval_lut(ct_in, lut);
}
 
Ciphertext FHEContext::sanitize(Ciphertext *ct){
    if(!config->is_sanitization_supported){
        throw std::logic_error("Sanitization is not supported, or sanitization key is not loaded!");
    }
    std::shared_ptr<LWECT> ct_out(new LWECT(ct->lwe_c->param));  
    config->sanitization_pk->sanitize(ct_out.get(), ct->lwe_c.get(), ct->encoding);
    return Ciphertext(ct_out, ct->encoding, this); 
}

Ciphertext FHEContext::eval_affine_function(std::vector<Ciphertext> ct_vec, std::vector<long> scalars, long scalar){    
    Ciphertext ct_out =  ct_vec[0] * scalars[0]; 
    for(int i = 1; i < ct_vec.size(); ++i){ 
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
    std::shared_ptr<LWESK> sk;  
    cereal::BinaryInputArchive iarchive(is); 
    iarchive(sk); 
    config->secret_key = sk; 
    /// TODO: If we want to use a sk, we also need to have the FHE configuration.
    //default_encoding = tfhe_boot_sk->default_encoding; 
}
 
void FHEContext::save_secret_key(std::string file_name){
    std::ofstream os(file_name, std::ios::binary); 
    send_secret_key(os);
}

void FHEContext::load_secret_key(std::string file_name){
    std::ifstream is(file_name, std::ios::binary);
    read_secret_key(is);
}

void FHEContext::send_public_key(std::ofstream &os){
    if(!config->is_encrypt_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }
    cereal::BinaryOutputArchive oarchive(os); 
    oarchive(config->bootstrap_pk); 
}

void FHEContext::read_public_key(std::ifstream &is){
    cereal::BinaryInputArchive iarchive(is); 
    std::shared_ptr<FunctionalBootstrapPublicKey> pk;  
    iarchive(pk);  
    config->bootstrap_pk = pk; 
    /// TODO: Note that we will not have a default encoding (What to do about that?)
    //default_encoding = tfhe_boot_pk->default_encoding; 
}
 
void FHEContext::save_public_key(std::string file_name){
    std::ofstream os(file_name, std::ios::binary); 
    send_public_key(os);
}

void FHEContext::load_public_key(std::string file_name){
    std::ifstream is(file_name, std::ios::binary);
    read_public_key(is);
}

void FHEContext::send_Ciphertext(std::ostream &os, Ciphertext &ct){
    if(!config->is_encrypt_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }
    cereal::BinaryOutputArchive oarchive(os);  
    LWECT out_ct = *ct.lwe_c;
    oarchive(out_ct); 
}

Ciphertext FHEContext::read_Ciphertext(std::ifstream &is){
    cereal::BinaryInputArchive iarchive(is);  
    LWECT ct;
    iarchive(ct);
    Ciphertext out(std::shared_ptr<LWECT>(ct.clone()), this->default_encoding, this);
    return out;
}
 
void FHEContext::save_Ciphertext(std::string file_name, Ciphertext &ct){
    std::ofstream os(file_name, std::ios::binary);  
    auto id = [](long m, long t) -> long {
        return m % t;
    };    
    /// TODO: Need to reword sanitization completely
    Ciphertext out_ct = eval_lut(&ct, id);  
    send_Ciphertext(os, out_ct);
}

Ciphertext FHEContext::load_Ciphertext(std::string file_name){
    std::ifstream is(file_name, std::ios::binary);
    return read_Ciphertext(is);
}

std::ostream& operator<<(std::ostream &out, const Ciphertext &c){ 
    Ciphertext ct_out(c);
    c.context->send_Ciphertext(out, ct_out); 
    return out;
}
  
