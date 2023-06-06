#include "../include/fhe_context.h"

 

 fhe_context::~fhe_context(){ 
    if(is_ntrunium){
        // Do Nothing
    }else if(is_tfhe){
        //if(is_pk_init){
        //    delete tfhe_boot_pk;
        //}
        //if(is_sk_init){
        //    delete tfhe_boot_sk;
        //} 
    }
 }

void fhe_context::generate_context(ntrunium_named_param name){  
        ntrunium_par = ntrunium_named_param_generator(name);  
        ntrunium_par.generate_bootstapping_keys();   
        is_ntrunium = true;
}
 

void fhe_context::generate_context(rlwe_hom_acc_scheme_named_param name){  
    rlwe_hom_acc_scheme_named_param_generator rlwe_hom_acc_par = rlwe_hom_acc_scheme_named_param_generator(name); 
    tfhe_boot_sk = rlwe_hom_acc_par.generate_secret_key();  
    tfhe_boot_pk = tfhe_boot_sk.get_public_param();  
    // TODO: Need to rewrite rlwe_hom_acc_scheme_named_param_generator to generate parameters, return a copy of them, and then free resources. 
    default_encoding = rlwe_hom_acc_par.default_encoding;
    is_tfhe = true;
    is_sk_init = true;
    is_pk_init = true;
}


ciphertext fhe_context::encrypt(long message, plaintext_encoding_type type){  
    if(!is_sk_init){
        throw 0;
    }
    plaintext_encoding encoding = default_encoding;
    encoding.type = type;
    return fhe_context::encrypt(message, encoding);
}

ciphertext fhe_context::encrypt(long message, long plaintext_space){
    if(!is_sk_init){
        throw 0;
    }
    plaintext_encoding encoding = default_encoding;
    encoding.plaintext_space = plaintext_space;
    return fhe_context::encrypt(message, encoding);
}
 
ciphertext fhe_context::encrypt(long message, plaintext_encoding_type type, long plaintext_space){
    if(!is_sk_init){
        throw 0;
    }
    plaintext_encoding encoding = default_encoding;
    encoding.type = type;
    encoding.plaintext_space = plaintext_space;
    return fhe_context::encrypt(message, encoding);
}
 

ciphertext fhe_context::encrypt(long message, plaintext_encoding encoding){  
    if(!is_sk_init){
        throw 0;
    }
    if(is_ntrunium){
        std::cout << "TODO: NTRUnium not supported yet!" << std::endl;
        throw 0;
    }else if(is_tfhe){       
       lwe_ct c(tfhe_boot_sk.extract_lwe.encrypt_ct(encoding.encode_message(message))); 
       return ciphertext(c, encoding, this);
    }else{
        std::cout << "Scheme not set" << std::endl;
        throw 0;
    } 
}

ciphertext fhe_context::encrypt(long message){
    if(!is_sk_init){
        throw 0;
    }
    return fhe_context::encrypt(message, default_encoding);
}




ciphertext fhe_context::encrypt_public(long message, plaintext_encoding_type type){  
    if(!is_pk_init){
        throw 0;
    }
    plaintext_encoding encoding = default_encoding;
    encoding.type = type;
    return fhe_context::encrypt_public(message, encoding);
}

ciphertext fhe_context::encrypt_public(long message, long plaintext_space){
    if(!is_pk_init){
        throw 0;
    }
    plaintext_encoding encoding = default_encoding;
    encoding.plaintext_space = plaintext_space;
    return fhe_context::encrypt_public(message, encoding);
}
 
ciphertext fhe_context::encrypt_public(long message, plaintext_encoding_type type, long plaintext_space){
    if(!is_pk_init){
        throw 0;
    }
    plaintext_encoding encoding = default_encoding;
    encoding.type = type;
    encoding.plaintext_space = plaintext_space;
    return fhe_context::encrypt_public(message, encoding);
}
 

ciphertext fhe_context::encrypt_public(long message, plaintext_encoding encoding){  
    if(!is_pk_init){
        throw 0;
    }
    if(is_ntrunium){
        std::cout << "TODO: NTRUnium not supported yet!" << std::endl;
        throw 0;
    }else if(is_tfhe){        
       lwe_ct c = tfhe_boot_pk->encrypt(encoding.encode_message(message));
       return ciphertext(c, encoding, this);
    }else{
        std::cout << "Scheme not set" << std::endl;
        throw 0;
    } 
}

ciphertext fhe_context::encrypt_public(long message){
    if(!is_pk_init){
        throw 0;
    }
    return fhe_context::encrypt_public(message, default_encoding);
}



long fhe_context::decrypt(ciphertext *c_in){
    if(!is_sk_init){
        throw 0;
    }
    if(is_ntrunium){
        std::cout << "TODO: NTRUnium not supported yet!" << std::endl;
        throw 0;
    }else if(is_tfhe){  
        long phase = tfhe_boot_sk.extract_lwe.phase(c_in->lwe_c->ct);   
        return c_in->encoding.decode_message(phase); 
    }else{
        std::cout << "Scheme not set" << std::endl;
        throw 0;
    }  
}
 

plaintext_encoding fhe_context::get_default_plaintext_encoding(){
    return default_encoding;
}

void fhe_context::set_default_plaintext_encoding(plaintext_encoding_type type, long plaintext_space){
    default_encoding.type = type;
    default_encoding.plaintext_space = plaintext_space;
}

// Return the plaintext space for FDFB or for native TFHE (minus one bit)
long  fhe_context::get_default_plaintext_space(){
    return default_encoding.plaintext_space;
}

 
void fhe_context::set_default_plaintext_space(long plaintext_space){
    this->default_encoding.plaintext_space = plaintext_space;
}


plaintext_encoding_type fhe_context::get_default_message_encoding(){
    return this->default_encoding.type;
}


void fhe_context::set_default_message_encoding_type(plaintext_encoding_type type){
    this->default_encoding.type = type;
}
 


// Take a pointer to a function
/*
- Note that in case of fhe_context the LUT is going to be a rotation_poly
- But in the context of NTRUNIUM it may be a rotation poly, or a encryption of a roation poly, or something....
- So... what do we do?
*/   
rotation_poly fhe_context::genrate_lut(long (*f)(long message, long plaintext_space), plaintext_encoding encoding){
    if(!is_pk_init){
        throw 0;
    }
    if(is_ntrunium){
        std::cout << "TODO: NTRUnium not supported yet!" << std::endl;
        throw 0;
    }else if(is_tfhe){   
        long ct_modulus;
        if(encoding.type == full_domain){
            ct_modulus = tfhe_boot_pk->rlwe_gadget_par.param.Q;
            return rotation_poly(f, encoding.plaintext_space, tfhe_boot_pk->rlwe_gadget_par.param.N, ct_modulus);
        }else if(encoding.type ==  partial_domain){
            ct_modulus = tfhe_boot_pk->rlwe_gadget_par.param.Q/2;
            return rotation_poly(f, encoding.plaintext_space, tfhe_boot_pk->rlwe_gadget_par.param.N, ct_modulus);
        }else if(encoding.type == signed_limied_short_int){
            return fhe_context::generate_rotation_poly_for_signed_limied_short_int_encoding(f);

        }else{
            throw 0;
        } 
    }else{
        std::cout << "Scheme not set" << std::endl;
        throw 0;
    }  
}



rotation_poly fhe_context::genrate_lut(long (*f)(long message, long plaintext_space)){
    if(!is_pk_init){
        throw 0;
    }
    return genrate_lut(f, this->default_encoding);
}


rotation_poly fhe_context::genrate_lut(long (*f)(long message), plaintext_encoding encoding){
    if(!is_pk_init){
        throw 0;
    }
    if(is_ntrunium){
        std::cout << "TODO: NTRUnium not supported yet!" << std::endl;
        throw 0;
    }else if(is_tfhe){  
        long ct_modulus;
        if(encoding.type == full_domain){
            ct_modulus = tfhe_boot_pk->rlwe_gadget_par.param.Q;
            return rotation_poly(f, encoding.plaintext_space, tfhe_boot_pk->rlwe_gadget_par.param.N, ct_modulus);
        }else if(encoding.type ==  partial_domain){
            ct_modulus = tfhe_boot_pk->rlwe_gadget_par.param.Q/2;
            return rotation_poly(f, encoding.plaintext_space, tfhe_boot_pk->rlwe_gadget_par.param.N, ct_modulus);
        }else if(encoding.type == signed_limied_short_int){
            return fhe_context::generate_rotation_poly_for_signed_limied_short_int_encoding(f);

        }else{
            throw 0;
        } 
    }else{
        std::cout << "Scheme not set" << std::endl;
        throw 0;
    }  
}
 

rotation_poly fhe_context::genrate_lut(long (*f)(long message)){
    return genrate_lut(f, this->default_encoding);
}
 


// Run functional bootstrapping
ciphertext fhe_context::eval_lut(ciphertext *ct_in, rotation_poly lut, gadget_mul_mode mode){ 
    if(!is_pk_init){
        throw 0;
    }
    if(is_ntrunium){
        std::cout << "TODO: NTRUnium not supported yet!" << std::endl;
        throw 0;
    }else if(is_tfhe && ct_in->is_lwe_ct){      
        lwe_ct ct_out(tfhe_boot_pk->extract_lwe_par); 
        if(ct_in->encoding.type == full_domain){  
            tfhe_boot_pk->functional_bootstrap(ct_out.ct,  lut.lookup_polynomial, ct_in->lwe_c->ct, deter, ct_in->encoding.plaintext_space);
        }else if(ct_in->encoding.type == partial_domain){ 
            tfhe_boot_pk->bootstrap(ct_out.ct,  lut.lookup_polynomial, ct_in->lwe_c->ct, deter);
        }else if(ct_in->encoding.type == signed_limied_short_int){   
            lwe_ct c_in(ct_in->lwe_c); 
            c_in = c_in + ct_in->encoding.encode_message(ct_in->encoding.plaintext_space);
            tfhe_boot_pk->bootstrap(ct_out.ct,  lut.lookup_polynomial, c_in.ct, deter); 
        } 
        else{
            throw 0;
        }   
        return ciphertext(ct_out, ct_in->encoding, this);
    }else{
        throw 0;
    }  
}
 

std::vector<ciphertext> fhe_context::eval_lut_amortized(ciphertext *ct_in, std::vector<rotation_poly> lut_vec, gadget_mul_mode mode){ 
    if(!is_pk_init){
        throw 0;
    }
    for(int i = 0; i < lut_vec.size(); ++i){
        lut_vec[i].flip_scale();
    }  
    std::vector<ciphertext> out_vec;
    if(is_ntrunium){
        std::cout << "TODO: NTRUnium not supported yet!" << std::endl;
        throw 0;
    }else if(is_tfhe){  
        std::vector<lwe_ct> out_vec_lwe;  
        if(ct_in->encoding.type == full_domain){ 
            out_vec_lwe = tfhe_boot_pk->functional_bootstrap(lut_vec, ct_in->lwe_c->ct, mode, ct_in->encoding.plaintext_space);
        }else if(ct_in->encoding.type == partial_domain){
            out_vec_lwe = tfhe_boot_pk->bootstrap(lut_vec, ct_in->lwe_c->ct, mode, ct_in->encoding.plaintext_space*2);
        }else if(ct_in->encoding.type == signed_limied_short_int){ 
            lwe_ct ct_cast = ct_in->lwe_c;
            ct_cast = ct_cast + ct_in->encoding.encode_message(ct_in->encoding.plaintext_space);
            out_vec_lwe = tfhe_boot_pk->bootstrap(lut_vec, ct_cast.ct, mode, ct_in->encoding.plaintext_space*4); 
        } 
        else{
            throw 0;
        }
        for(lwe_ct ct: out_vec_lwe){
            out_vec.push_back(ciphertext(ct, ct_in->encoding, this));
        } 
    }else{
        std::cout << "Scheme not set" << std::endl;
        throw 0;
    }  
    return out_vec;
}



ciphertext fhe_context::eval_lut(ciphertext *ct_in, long (*f)(long message, long plaintext_space), plaintext_encoding encoding, gadget_mul_mode mode){
    if(!is_pk_init){
        throw 0;
    }
    rotation_poly lut = this->genrate_lut(f, encoding);
    return eval_lut(ct_in, lut, mode);
}
 
ciphertext fhe_context::eval_lut(ciphertext *ct_in, long (*f)(long message, long plaintext_space), gadget_mul_mode mode){
    if(!is_pk_init){
        throw 0;
    }
    rotation_poly lut = this->genrate_lut(f);
    return eval_lut(ct_in, lut, mode);
}

ciphertext fhe_context::eval_lut(ciphertext *ct_in, long (*f)(long message), plaintext_encoding encoding, gadget_mul_mode mode){
    if(!is_pk_init){
        throw 0;
    }
    rotation_poly lut = this->genrate_lut(f, encoding);
    return eval_lut(ct_in, lut, mode);
}

ciphertext fhe_context::eval_lut(ciphertext *ct_in, long (*f)(long message), gadget_mul_mode mode){
    if(!is_pk_init){
        throw 0;
    }
    rotation_poly lut = this->genrate_lut(f);
    return eval_lut(ct_in, lut, mode);
}
 
 

ciphertext fhe_context::eval_affine_function(std::vector<ciphertext> ct_vec, std::vector<long> scalars, long scalar){    
    if(!is_pk_init){
        throw 0;
    }
    ciphertext ct_out =  ct_vec[0] * scalars[0]; 
    for(int i = 1; i < ct_vec.size(); ++i){ 
            ct_out = ct_out + (ct_vec[i] * scalars[i]); 
        }
        ct_out = ct_out + scalar;
        return ct_out; 
}


  

rotation_poly fhe_context::generate_rotation_poly_for_signed_limied_short_int_encoding(long (*f)(long message)){
    long full_t = default_encoding.plaintext_space * 4;
    long delta_Q_t = (long)round((double)tfhe_boot_pk->rlwe_gadget_par.param.Q/(double)full_t); 
    long N = tfhe_boot_pk->rlwe_gadget_par.param.N;
    long* lookup_polynomial = new long[N];
    double scale = (double)full_t/(2*N);
    long arg; 
    for(int i = 0; i < N; ++i){  
        // Compute  your function here 
        arg = round(scale * i);
        if(arg >= default_encoding.plaintext_space){ 
            arg = f((arg % default_encoding.plaintext_space)); 
        }else{ 
            arg = default_encoding.plaintext_space - arg;
            arg = f(-arg); 
        }
        lookup_polynomial[N-i-1] = utils::integer_mod_form(-delta_Q_t *  arg, tfhe_boot_pk->rlwe_gadget_par.param.Q); 
    } 
    rotation_poly out(lookup_polynomial, full_t, N, tfhe_boot_pk->rlwe_gadget_par.param.Q);
    delete[] lookup_polynomial;
    return out;
}

 
rotation_poly fhe_context::generate_rotation_poly_for_signed_limied_short_int_encoding(long (*f)(long message, long plaintext_space)){
    long full_t = default_encoding.plaintext_space * 4;
    long delta_Q_t = (long)round((double)tfhe_boot_pk->rlwe_gadget_par.param.Q/(double)full_t); 
    long N = tfhe_boot_pk->rlwe_gadget_par.param.N;
    long* lookup_polynomial = new long[N];
    double scale = (double)full_t/(2*N);
    long arg; 
    for(int i = 0; i < N; ++i){  
        // Compute  your function here 
        if(arg >= default_encoding.plaintext_space){ 
            arg = f((arg % default_encoding.plaintext_space), default_encoding.plaintext_space); 
        }else{ 
            arg = default_encoding.plaintext_space - arg;
            arg = f(-arg, default_encoding.plaintext_space); 
        }
        lookup_polynomial[N-i-1] = utils::integer_mod_form(-delta_Q_t *  arg, tfhe_boot_pk->rlwe_gadget_par.param.Q); 
    } 
    rotation_poly out(lookup_polynomial, full_t, N, tfhe_boot_pk->rlwe_gadget_par.param.Q);
    delete[] lookup_polynomial;
    return out;
}
 


void fhe_context::send_secret_key(std::ofstream &os){
    if(!is_sk_init){
        throw 0;
    }
    cereal::BinaryOutputArchive oarchive(os); 
    oarchive(tfhe_boot_sk); 
}

void fhe_context::read_secret_key(std::ifstream &is){ 
    rlwe_hom_acc_scheme_gen sk;  
    cereal::BinaryInputArchive iarchive(is); 
    iarchive(sk); 
    tfhe_boot_sk = sk;
    is_sk_init = true;
    default_encoding = tfhe_boot_sk.default_encoding;
    // TODO: For now support only for TFHE
    is_tfhe = true;
}
 
void fhe_context::save_secret_key(std::string file_name){
    std::ofstream os(file_name, std::ios::binary); 
    send_secret_key(os);
}

void fhe_context::load_secret_key(std::string file_name){
    std::ifstream is(file_name, std::ios::binary);
    read_secret_key(is);
}


void fhe_context::send_public_key(std::ofstream &os){
    if(!is_pk_init){
        throw 0;
    }
    cereal::BinaryOutputArchive oarchive(os); 
    oarchive(tfhe_boot_pk); 
}

void fhe_context::read_public_key(std::ifstream &is){
    cereal::BinaryInputArchive iarchive(is); 
    std::shared_ptr<rlwe_hom_acc_scheme> pk;  
    iarchive(pk);  
    tfhe_boot_pk = pk;
    is_pk_init = true;
    default_encoding = tfhe_boot_pk->default_encoding;
    // TODO: For now support only for TFHE
    is_tfhe = true;
}
 
void fhe_context::save_public_key(std::string file_name){
    std::ofstream os(file_name, std::ios::binary); 
    send_public_key(os);
}

void fhe_context::load_public_key(std::string file_name){
    std::ifstream is(file_name, std::ios::binary);
    read_public_key(is);
}



void fhe_context::send_ciphertext(std::ostream &os, ciphertext &ct){
    if(!is_pk_init){
        throw 0;
    }
    cereal::BinaryOutputArchive oarchive(os); 
    if(is_tfhe){
        lwe_ct out_ct(ct.lwe_c);
        oarchive(out_ct); 
    } 
}

ciphertext fhe_context::read_ciphertext(std::ifstream &is){
    cereal::BinaryInputArchive iarchive(is);  
    lwe_ct ct;
    iarchive(ct);
    ciphertext out(ct, this->default_encoding, this);
    return out;
}
 
void fhe_context::save_ciphertext(std::string file_name, ciphertext &ct){
    std::ofstream os(file_name, std::ios::binary);  
    auto id = [](long m, long t) -> long {
        return m % t;
    };    
    ciphertext out_ct = eval_lut(&ct, id, simul);  
    send_ciphertext(os, out_ct);
}

ciphertext fhe_context::load_ciphertext(std::string file_name){
    std::ifstream is(file_name, std::ios::binary);
    return read_ciphertext(is);
}

 

std::ostream& operator<<(std::ostream &out, const ciphertext &c){ 
    ciphertext ct_out(c);
    c.context->send_ciphertext(out, ct_out); 
    return out;
}
  