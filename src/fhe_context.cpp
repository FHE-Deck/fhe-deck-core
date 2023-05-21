#include "../include/fhe_context.h"

 

void fhe_context::generate_context(ntrunium_named_param name){ 
        scheme_type = NTRUNIUM;
        ntrunium_par = ntrunium_named_param_generator(name);  
        ntrunium_par.generate_bootstapping_keys();  
        // TODO: Actually the parameter set should have a hardcoded value for the plaintext space
        default_encoding = rlwe_hom_acc_par.default_encoding;
}
 

void fhe_context::generate_context(rlwe_hom_acc_scheme_named_param name){ 
        scheme_type = FHEW;
        rlwe_hom_acc_par = rlwe_hom_acc_scheme_named_param_generator(name);
        rlwe_hom_acc_par.generate_bootstapping_keys(); 
        default_encoding = rlwe_hom_acc_par.default_encoding;
}


ciphertext fhe_context::encrypt(long message, plaintext_encoding_type type){  
    plaintext_encoding encoding = default_encoding;
    encoding.type = type;
    return fhe_context::encrypt(message, encoding);
}

ciphertext fhe_context::encrypt(long message, long plaintext_space){
    plaintext_encoding encoding = default_encoding;
    encoding.plaintext_space = plaintext_space;
    return fhe_context::encrypt(message, encoding);
}
 
ciphertext fhe_context::encrypt(long message, plaintext_encoding_type type, long plaintext_space){
    plaintext_encoding encoding = default_encoding;
    encoding.type = type;
    encoding.plaintext_space = plaintext_space;
    return fhe_context::encrypt(message, encoding);
}
 

ciphertext fhe_context::encrypt(long message, plaintext_encoding encoding){  
    if(scheme_type == NTRUNIUM){
        std::cout << "TODO: NTRUnium not supported yet!" << std::endl;
    }else if(scheme_type == FHEW){       
       lwe_ct c(rlwe_hom_acc_par.boot_sk->extract_lwe.encrypt_ct(encoding.encode_message(message))); 
       return ciphertext(c, encoding);
    }else{
        std::cout << "Scheme not set" << std::endl;
        throw 0;
    } 
}

ciphertext fhe_context::encrypt(long message){
    return fhe_context::encrypt(message, default_encoding);
}




ciphertext fhe_context::encrypt_public(long message, plaintext_encoding_type type){  
    plaintext_encoding encoding = default_encoding;
    encoding.type = type;
    return fhe_context::encrypt_public(message, encoding);
}

ciphertext fhe_context::encrypt_public(long message, long plaintext_space){
    plaintext_encoding encoding = default_encoding;
    encoding.plaintext_space = plaintext_space;
    return fhe_context::encrypt_public(message, encoding);
}
 
ciphertext fhe_context::encrypt_public(long message, plaintext_encoding_type type, long plaintext_space){
    plaintext_encoding encoding = default_encoding;
    encoding.type = type;
    encoding.plaintext_space = plaintext_space;
    return fhe_context::encrypt_public(message, encoding);
}
 

ciphertext fhe_context::encrypt_public(long message, plaintext_encoding encoding){  
    if(scheme_type == NTRUNIUM){
        std::cout << "TODO: NTRUnium not supported yet!" << std::endl;
    }else if(scheme_type == FHEW){        
       lwe_ct c = rlwe_hom_acc_par.boot->encrypt(encoding.encode_message(message));
       return ciphertext(c, encoding);
    }else{
        std::cout << "Scheme not set" << std::endl;
        throw 0;
    } 
}

ciphertext fhe_context::encrypt_public(long message){
    return fhe_context::encrypt_public(message, default_encoding);
}



long fhe_context::decrypt(ciphertext *c_in){
    if(scheme_type == NTRUNIUM){
        std::cout << "TODO: NTRUnium not supported yet!" << std::endl;
    }else if(scheme_type == FHEW){  
        long phase = rlwe_hom_acc_par.boot_sk->extract_lwe.phase(c_in->lwe_c->ct);   
        return c_in->encoding.decode_message(phase); 
    }else{
        std::cout << "Scheme not set" << std::endl;
        return 0;
    }  
}

//long fhe_context::decrypt(ciphertext c_in){
//    return decrypt(&c_in);
//}
 

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
    if(scheme_type == NTRUNIUM){
        std::cout << "TODO: NTRUnium not supported yet!" << std::endl;
    }else if(scheme_type == FHEW){   
        long ct_modulus;
        if(encoding.type == full_domain){
            ct_modulus = rlwe_hom_acc_par.boot->rlwe_gadget_par.param.Q;
            return rotation_poly(f, encoding.plaintext_space, rlwe_hom_acc_par.boot->rlwe_gadget_par.param.N, ct_modulus);
        }else if(encoding.type ==  partial_domain){
            ct_modulus = rlwe_hom_acc_par.boot->rlwe_gadget_par.param.Q/2;
            return rotation_poly(f, encoding.plaintext_space, rlwe_hom_acc_par.boot->rlwe_gadget_par.param.N, ct_modulus);
        }else if(encoding.type == signed_limied_short_int){
            return fhe_context::generate_rotation_poly_for_signed_limied_short_int_encoding(f);

        }else{
            throw 0;
        } 
    }else{
        std::cout << "Scheme not set" << std::endl;
    }  
}



rotation_poly fhe_context::genrate_lut(long (*f)(long message, long plaintext_space)){
    return genrate_lut(f, this->default_encoding);
}


rotation_poly fhe_context::genrate_lut(long (*f)(long message), plaintext_encoding encoding){
    if(scheme_type == NTRUNIUM){
        std::cout << "TODO: NTRUnium not supported yet!" << std::endl;
    }else if(scheme_type == FHEW){  
        long ct_modulus;
        if(encoding.type == full_domain){
            ct_modulus = rlwe_hom_acc_par.boot->rlwe_gadget_par.param.Q;
            return rotation_poly(f, encoding.plaintext_space, rlwe_hom_acc_par.boot->rlwe_gadget_par.param.N, ct_modulus);
        }else if(encoding.type ==  partial_domain){
            ct_modulus = rlwe_hom_acc_par.boot->rlwe_gadget_par.param.Q/2;
            return rotation_poly(f, encoding.plaintext_space, rlwe_hom_acc_par.boot->rlwe_gadget_par.param.N, ct_modulus);
        }else if(encoding.type == signed_limied_short_int){
            return fhe_context::generate_rotation_poly_for_signed_limied_short_int_encoding(f);

        }else{
            throw 0;
        } 
    }else{
        std::cout << "Scheme not set" << std::endl;
    }  
}
 

rotation_poly fhe_context::genrate_lut(long (*f)(long message)){
    return genrate_lut(f, this->default_encoding);
}
 


// Run functional bootstrapping
ciphertext fhe_context::eval_lut(ciphertext *ct_in, rotation_poly lut){ 
    if(scheme_type == NTRUNIUM){
        std::cout << "TODO: NTRUnium not supported yet!" << std::endl;
    }else if(scheme_type == FHEW && ct_in->is_lwe_ct){   
        //lwe_ct ct_cast(dynamic_cast<lwe_ct*>(ciphertext)); 
        lwe_ct ct_out(rlwe_hom_acc_par.boot->extract_lwe_par);
        //ct_out->pe = ciphertext->pe; 
        if(ct_in->encoding.type == full_domain){ 
            rlwe_hom_acc_par.boot->functional_bootstrap(ct_out.ct,  lut.lookup_polynomial, ct_in->lwe_c->ct, deter, ct_in->encoding.plaintext_space);
        }else if(ct_in->encoding.type == partial_domain){
            rlwe_hom_acc_par.boot->bootstrap(ct_out.ct,  lut.lookup_polynomial, ct_in->lwe_c->ct, deter);
        }else if(ct_in->encoding.type == signed_limied_short_int){  
            lwe_ct c_in(ct_in->lwe_c); 
            c_in = c_in + ct_in->encoding.encode_message(ct_in->encoding.plaintext_space);
            rlwe_hom_acc_par.boot->bootstrap(ct_out.ct,  lut.lookup_polynomial, c_in.ct, deter); 
        } 
        else{
            throw 0;
        }  
        return ciphertext(ct_out, ct_in->encoding);
    }else{
        throw 0;
    }  
}
 

std::vector<ciphertext> fhe_context::eval_lut_amortized(ciphertext *ct_in, std::vector<rotation_poly> lut_vec){ 
    for(int i = 0; i < lut_vec.size(); ++i){
        lut_vec[i].flip_scale();
    }  
    std::vector<ciphertext> out_vec;
    if(scheme_type == NTRUNIUM){
        std::cout << "TODO: NTRUnium not supported yet!" << std::endl;
    }else if(scheme_type == FHEW){  
        std::vector<lwe_ct> out_vec_lwe;  
        if(ct_in->encoding.type == full_domain){ 
            out_vec_lwe = rlwe_hom_acc_par.boot->functional_bootstrap(lut_vec, ct_in->lwe_c->ct, deter, ct_in->encoding.plaintext_space);
        }else if(ct_in->encoding.type == partial_domain){
            out_vec_lwe = rlwe_hom_acc_par.boot->bootstrap(lut_vec, ct_in->lwe_c->ct, deter, ct_in->encoding.plaintext_space*2);
        }else if(ct_in->encoding.type == signed_limied_short_int){ 
            lwe_ct ct_cast = ct_in->lwe_c;
            ct_cast = ct_cast + ct_in->encoding.encode_message(ct_in->encoding.plaintext_space);
            out_vec_lwe = rlwe_hom_acc_par.boot->bootstrap(lut_vec, ct_cast.ct, deter, ct_in->encoding.plaintext_space*4); 
        } 
        else{
            throw 0;
        }
        for(lwe_ct ct: out_vec_lwe){
            out_vec.push_back(ciphertext(ct, ct_in->encoding));
        } 
    }else{
        std::cout << "Scheme not set" << std::endl;
    }  
    return out_vec;
}



ciphertext fhe_context::eval_lut(ciphertext *ct_in, long (*f)(long message, long plaintext_space), plaintext_encoding encoding){
    rotation_poly lut = this->genrate_lut(f, encoding);
    return eval_lut(ct_in, lut);
}
 
ciphertext fhe_context::eval_lut(ciphertext *ct_in, long (*f)(long message, long plaintext_space)){
    rotation_poly lut = this->genrate_lut(f);
    return eval_lut(ct_in, lut);
}

ciphertext fhe_context::eval_lut(ciphertext *ct_in, long (*f)(long message), plaintext_encoding encoding){
    rotation_poly lut = this->genrate_lut(f, encoding);
    return eval_lut(ct_in, lut);
}

ciphertext fhe_context::eval_lut(ciphertext *ct_in, long (*f)(long message)){
    rotation_poly lut = this->genrate_lut(f);
    return eval_lut(ct_in, lut);
}
 
 

ciphertext fhe_context::eval_affine_function(std::vector<ciphertext> ct_vec, std::vector<long> scalars, long scalar){   
    //ciphertext ct_cast = ct_vec[0];
    ciphertext ct_out =  ct_vec[0] * scalars[0]; 
    for(int i = 1; i < ct_vec.size(); ++i){ 
            ct_out = ct_out + (ct_vec[i] * scalars[i]); 
        }
        ct_out = ct_out + scalar;
        return ct_out; 
}


  

rotation_poly fhe_context::generate_rotation_poly_for_signed_limied_short_int_encoding(long (*f)(long message)){
    long full_t = default_encoding.plaintext_space * 4;
    long delta_Q_t = (long)round((double)rlwe_hom_acc_par.boot->rlwe_gadget_par.param.Q/(double)full_t); 
    long N = rlwe_hom_acc_par.boot->rlwe_gadget_par.param.N;
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
        lookup_polynomial[N-i-1] = utils::integer_mod_form(-delta_Q_t *  arg, rlwe_hom_acc_par.boot->rlwe_gadget_par.param.Q); 
    } 
    rotation_poly out(lookup_polynomial, full_t, N, rlwe_hom_acc_par.boot->rlwe_gadget_par.param.Q);
    delete[] lookup_polynomial;
    return out;
}

 
rotation_poly fhe_context::generate_rotation_poly_for_signed_limied_short_int_encoding(long (*f)(long message, long plaintext_space)){
    long full_t = default_encoding.plaintext_space * 4;
    long delta_Q_t = (long)round((double)rlwe_hom_acc_par.boot->rlwe_gadget_par.param.Q/(double)full_t); 
    long N = rlwe_hom_acc_par.boot->rlwe_gadget_par.param.N;
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
        lookup_polynomial[N-i-1] = utils::integer_mod_form(-delta_Q_t *  arg, rlwe_hom_acc_par.boot->rlwe_gadget_par.param.Q); 
    } 
    rotation_poly out(lookup_polynomial, full_t, N, rlwe_hom_acc_par.boot->rlwe_gadget_par.param.Q);
    delete[] lookup_polynomial;
    return out;
}
 