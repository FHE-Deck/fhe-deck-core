#include "interface/fhe_context.h"
#include "interface/integers.h"
#include "interface/ciphertext.h"

using namespace FHEDeck;
 
FHEContext::FHEContext(){
    config = std::shared_ptr<FHEConfiguration>(new FHEConfiguration());
} 

FHEContext::FHEContext(FHENamedParams name){
    config = std::shared_ptr<FHEConfiguration>(new FHEConfiguration());
    generate_context(name);
}

FHEContext::FHEContext(const FHEContext& other){
    config = other.config; 
}

FHEContext& FHEContext::operator=(const FHEContext& other){
    if(this == &other){
        return *this;
    }   
    this->config = other.config;
    return *this;
}
  
void FHEContext::generate_context(FHENamedParams name){    
    config = std::shared_ptr<FHEConfiguration>(new FHEConfiguration(name));
    config->generate_keys();  
}
 
Ciphertext FHEContext::encrypt(int64_t message, const PlaintextEncoding& encoding)const{  
    if(!config->is_secret_key_set){
        throw std::logic_error("No Secret Key Initialized!");
    }        
    std::shared_ptr<LWECT> c(config->secret_key->lwe_sk->encrypt(encoding.encode_message(message)));
    return Ciphertext(c, encoding, *this); 
}
 
Ciphertext FHEContext::encrypt_public(int64_t message, const PlaintextEncoding& encoding)const{  
    if(!config->eval_key.is_encrypt_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    } 
    std::shared_ptr<LWECT> c(config->eval_key.encrypt_pk->encrypt(encoding.encode_message(message))); 
    return Ciphertext(c, encoding, *this);
}
 
int64_t FHEContext::decrypt(const Ciphertext& c_in)const{
    if(!config->is_secret_key_set){
        throw std::logic_error("No Secret Key Initialized!");
    }  
    return config->secret_key->lwe_sk->decrypt(*c_in.lwe_c, c_in.encoding);
}
 
int64_t FHEContext::decrypt(const DigitInteger& ct)const{
    std::vector<int64_t> digits;
    for(Ciphertext c: ct.encrypted_digits){
        digits.push_back(decrypt(c));
    }
    return ct.int_comp(digits);
}

int64_t FHEContext::decrypt(const RNSInteger& ct)const{
    std::vector<int32_t> digits;
    for(Ciphertext c: ct.encrypted_digits){
         digits.push_back(decrypt(c));
    }
    return ct.base.compose(digits);
}
 
PlaintextEncoding FHEContext::get_default_plaintext_encoding()const{
    return config->eval_key.default_encoding;
}
 
int64_t FHEContext::get_default_plaintext_space()const{
    return config->eval_key.default_encoding.get_plaintext_space();
}
 
PlaintextEncodingType FHEContext::get_default_plaintext_encoding_type()const{
    return config->eval_key.default_encoding.get_type();
}
  
HomomorphicAccumulator FHEContext::setup_function(
    const std::function<int64_t(int64_t)>& f, 
    const PlaintextEncoding& input_encoding, 
    const PlaintextEncoding& output_encoding)const{

    if(!config->eval_key.is_bootstrap_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }  
    auto boot_acc = config->eval_key.boot_acc_builder->prepare_specification(f, input_encoding, output_encoding); 
    auto func_spec = config->eval_key.func_boot_acc_builder->prepare_specification(f, input_encoding, output_encoding);
    auto multival_spec = config->eval_key.multivalue_acc_builder->prepare_specification(f, input_encoding, output_encoding);
    HomomorphicAccumulator out(boot_acc, func_spec, multival_spec, input_encoding, output_encoding);
    return out;  
}

HomomorphicAccumulator FHEContext::setup_function(const std::function<int64_t(int64_t)>& f, const PlaintextEncoding& encoding)const{ 
    return setup_function(f, encoding, encoding);  
}
  
HomomorphicAccumulator FHEContext::setup_function(const std::function<int64_t(int64_t)>& f)const{    
    return setup_function(f, config->eval_key.default_encoding, config->eval_key.default_encoding);
}

Ciphertext FHEContext::eval(const Ciphertext& ct_in, const HomomorphicAccumulator& lut)const{
    if(!config->eval_key.is_bootstrap_pk_set){
        throw std::logic_error("No Public Key Initialized!");
    }   
    if(lut.input_encoding != ct_in.encoding){ 
        throw std::logic_error("Input encoding of the accumulator does not match the encoding of the input ciphertext!");
    } 
    std::shared_ptr<LWECT> ct_out(new LWECT(ct_in.lwe_c->param));  
    if(ct_in.encoding.get_type() == PlaintextEncodingType::full_domain){      
        config->eval_key.bootstrap_pk->full_domain_bootstrap(*ct_out, lut.func_boot_acc, *ct_in.lwe_c, ct_in.encoding, lut.output_encoding);
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
    return Ciphertext(ct_out, lut.output_encoding, *this); 
}
 
std::vector<Ciphertext> FHEContext::eval(const Ciphertext& ct_in, const std::vector<HomomorphicAccumulator>& lut_vec)const{
    if(lut_vec.empty()) throw std::logic_error("FHEContext::eval(const Ciphertext& ct_in, std::vector<HomomorphicAccumulator> lut_vec)const: Empty HomomorphicAccumulator Vector!");
    if(!config->eval_key.is_bootstrap_pk_set) throw std::logic_error("FHEContext::eval(const Ciphertext& ct_in, std::vector<HomomorphicAccumulator> lut_vec)const: No Public Key Initialized!");  
     
    /// NOTE: We are guaranteed that at least one element exists
    PlaintextEncoding output_encoding = lut_vec[0].output_encoding;
    for(const HomomorphicAccumulator& lut: lut_vec){ 
        if(lut.input_encoding != ct_in.encoding){
            throw std::logic_error("FHEContext::eval(const Ciphertext& ct_in, std::vector<HomomorphicAccumulator> lut_vec)const: Input encoding of the accumulator does not match the encoding of the input ciphertext!");
        } 
        if(lut.output_encoding != output_encoding){
           throw std::logic_error("config->eval_key.bootstrap_pk->full_domain_bootstrap(ct_out, acc.func_boot_acc, *ct_in.lwe_c, ct_in.encoding, output_encoding);");
        }  
    }  

    // The output vector of LWECT 
    std::vector<LWECT> out_vec_lwe;   
    if((ct_in.encoding.get_type() == PlaintextEncodingType::full_domain) && !config->eval_key.bootstrap_pk->is_full_domain_bootstrap_function_amortizable){ 
        // Amortization is not supported so lets run sequentially.
        for(const HomomorphicAccumulator& lut: lut_vec){ 
            LWECT ct_out(ct_in.lwe_c->param);  
            config->eval_key.bootstrap_pk->full_domain_bootstrap(ct_out, lut.func_boot_acc, *ct_in.lwe_c, ct_in.encoding, output_encoding);
            out_vec_lwe.push_back(ct_out);
        }
    // Otherwise we run the amortized procedures. 
    } else{ 
        // We need to get the VectorCTAccumulator's out of the HomomorphicAccumulator wrapper. 
        std::vector<std::shared_ptr<FunctionSpecification>> accumulator_vec;
        for(const HomomorphicAccumulator& lut: lut_vec){  
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
        out_vec.push_back(Ciphertext(std::shared_ptr<LWECT>(ct.clone()), output_encoding, *this));
    }  
    return out_vec;
}
 
Ciphertext FHEContext::eval(
    const Ciphertext& ct_in, 
    const std::function<int64_t(int64_t)>& f, 
    const PlaintextEncoding& output_encoding)const{

    HomomorphicAccumulator lut = this->setup_function(f, ct_in.encoding, output_encoding);
    return eval(ct_in, lut);
}

Ciphertext FHEContext::eval(const Ciphertext& ct_in, const std::function<int64_t(int64_t)>& f)const{
    HomomorphicAccumulator lut = this->setup_function(f, ct_in.encoding, ct_in.encoding);
    return eval(ct_in, lut);
}
 
Ciphertext FHEContext::sanitize(const Ciphertext& ct)const{
    if(!config->eval_key.is_sanitization_supported){
        throw std::logic_error("Sanitization is not supported, or sanitization key is not loaded!");
    }
    std::shared_ptr<LWECT> ct_out(new LWECT(ct.lwe_c->param));  
    config->eval_key.sanitization_pk->sanitize(*ct_out, *ct.lwe_c, ct.encoding);
    return Ciphertext(ct_out, ct.encoding, *this); 
}

Ciphertext FHEContext::eval_affine_function(
        const std::vector<Ciphertext>& ct_vec, 
        const std::vector<int64_t>& scalars, 
        const int64_t& scalar)const{    
    
    Ciphertext ct_out =  ct_vec[0] * scalars[0]; 
    for(int32_t i = 1; i < ct_vec.size(); ++i){ 
            ct_out = ct_out + (ct_vec[i] * scalars[i]); 
    }
    ct_out = ct_out + scalar;
    return ct_out; 
}

void FHEContext::send_secret_key(std::ofstream &os)const{
    if(!config->is_secret_key_set) throw std::logic_error("FHEContext::send_secret_key(std::ofstream &os): No Secret Key Initialized!"); 
    #if defined(USE_CEREAL) 
    cereal::BinaryOutputArchive oarchive(os); 
    oarchive(config->secret_key); 
    #else
    throw std::logic_error("Serialization not supported. If you want to use serialization compile FHE-Deck with CEREAL (see the README.md file).");
    #endif
}

void FHEContext::read_secret_key(std::ifstream &is){   
    if(config->is_secret_key_set) throw std::logic_error("FHEContext::read_secret_key(std::ifstream &is): The secret key is already set.");
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
 
void FHEContext::save_secret_key(std::string file_name)const{ 
    if(!config->is_secret_key_set) throw std::logic_error("FHEContext::save_secret_key(std::string file_name): No secret key set.");
    #if defined(USE_CEREAL) 
    std::ofstream os(file_name, std::ios::binary); 
    send_secret_key(os);
    os.close();  
    #else
    throw std::logic_error("Serialization not supported. If you want to use serialization compile FHE-Deck with CEREAL (see the README.md file).");
    #endif
}

void FHEContext::load_secret_key(std::string file_name){ 
    if(config->is_secret_key_set) throw std::logic_error("FHEContext::load_secret_key(std::string file_name): The secret key is already set.");
    #if defined(USE_CEREAL) 
    std::ifstream is(file_name, std::ios::binary);
    read_secret_key(is); 
    #else
    throw std::logic_error("Serialization not supported. If you want to use serialization compile FHE-Deck with CEREAL (see the README.md file).");
    #endif 
}

void FHEContext::send_public_key(std::ofstream &os)const{ 
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
    config->is_eval_key_set = true;
    #else
    throw std::logic_error("Serialization not supported. If you want to use serialization compile FHE-Deck with CEREAL (see the README.md file).");
    #endif
}
 
void FHEContext::save_public_key(std::string file_name)const{
    if(!config->is_secret_key_set) throw std::logic_error("FHEContext::save_public_key(std::string file_name): No Public Key Initialized!");
    #if defined(USE_CEREAL)
    std::ofstream os(file_name, std::ios::binary); 
    send_public_key(os);
    os.close();
    #else
    throw std::logic_error("Serialization not supported. If you want to use serialization compile FHE-Deck with CEREAL (see the README.md file).");
    #endif 
}

void FHEContext::load_public_key(std::string file_name){
    if(config->is_eval_key_set) throw std::logic_error("FHEContext::load_public_key(std::string file_name): The public key is already set.");
    #if defined(USE_CEREAL)
    std::ifstream is(file_name, std::ios::binary);
    read_public_key(is);
    #else
    throw std::logic_error("Serialization not supported. If you want to use serialization compile FHE-Deck with CEREAL (see the README.md file).");
    #endif  
}

void FHEContext::send_Ciphertext(std::ostream &os, const Ciphertext &ct)const{ 
    if(!config->eval_key.is_encrypt_pk_set) throw std::logic_error("FHEContext::send_Ciphertext(std::ostream &os, Ciphertext &ct): No Public Key Initialized!"); 
    #if defined(USE_CEREAL) 
    cereal::BinaryOutputArchive oarchive(os);   
    oarchive(ct); 
    #else
    throw std::logic_error("Serialization not supported. If you want to use serialization compile FHE-Deck with CEREAL (see the README.md file).");
    #endif
}

Ciphertext FHEContext::read_Ciphertext(std::ifstream &is)const{ 
    #if defined(USE_CEREAL) 
    cereal::BinaryInputArchive iarchive(is);  
    Ciphertext ct;
    iarchive(ct);
    ct.context = this;
    return ct; 
    #else
    throw std::logic_error("Serialization not supported. If you want to use serialization compile FHE-Deck with CEREAL (see the README.md file).");
    #endif
}
 
void FHEContext::save_Ciphertext(const std::string file_name, const Ciphertext &ct)const{
    #if defined(USE_CEREAL)
    std::ofstream os(file_name, std::ios::binary);   
    send_Ciphertext(os, ct);
    #else
    throw std::logic_error("Serialization not supported. If you want to use serialization compile FHE-Deck with CEREAL (see the README.md file).");
    #endif   
}

Ciphertext FHEContext::load_Ciphertext(std::string file_name)const{
    #if defined(USE_CEREAL) 
    std::ifstream is(file_name, std::ios::binary);
    return read_Ciphertext(is);
    #else
    throw std::logic_error("Serialization not supported. If you want to use serialization compile FHE-Deck with CEREAL (see the README.md file).");
    #endif    
}
 
