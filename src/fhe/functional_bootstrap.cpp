#include "functional_bootstrap.h"

using namespace fhe_deck;
  
  
FunctionalBootstrapPublicKey::~FunctionalBootstrapPublicKey(){    
    //delete[] acc_msb;
    //delete[] acc_one;  
}
  

FunctionalBootstrapPublicKey::FunctionalBootstrapPublicKey(const FunctionalBootstrapPublicKey &other){
    this->blind_rotation_key = other.blind_rotation_key;
    this->key_switch_key  = other.key_switch_key;
    this->masking_public_key = other.masking_public_key;
    this->lwe_par = other.lwe_par;
    this->lwe_par_tiny= other.lwe_par_tiny;

    this->fdfb_alg = other.fdfb_alg;
 
    // Initialize BlindRotateOutput 
    this->br_out = this->blind_rotation_key->init_blind_rotate_output();
    this->br_temp = this->blind_rotation_key->init_blind_rotate_output(); 
    
    //this->rotation_poly_size = this->blind_rotation_key->actual_rotation_size;
    this->acc_msb = this->blind_rotation_key->get_acc_msb(); 
 
    // Set the LWE modulus swichers
    // Mod Switch from Extracted Q to 2 * N
    this->ms_from_gadget_to_par = LWEModSwitcher(this->key_switch_key->destination.lwe_param, this->blind_rotation_key->lwe_par);
    // Mod Switch from Extracted Q to N
    this->ms_from_gadget_to_tiny_par = LWEModSwitcher(this->key_switch_key->destination.lwe_param, this->lwe_par_tiny);
    
}
 


FunctionalBootstrapPublicKey& FunctionalBootstrapPublicKey::operator=(const FunctionalBootstrapPublicKey other){ 
    this->blind_rotation_key = other.blind_rotation_key;
    this->key_switch_key  = other.key_switch_key;
    this->masking_public_key = other.masking_public_key;
    this->lwe_par = other.lwe_par;
    this->lwe_par_tiny= other.lwe_par_tiny;

    this->fdfb_alg = other.fdfb_alg;

    // Initialize BlindRotateOutput 
    this->br_out = this->blind_rotation_key->init_blind_rotate_output();
    this->br_temp = this->blind_rotation_key->init_blind_rotate_output(); 
  
 
    //this->rotation_poly_size = this->blind_rotation_key->actual_rotation_size;
    this->acc_msb = this->blind_rotation_key->get_acc_msb(); 
 
    // Set the LWE modulus swicher   
    // Mod Switch from Extracted Q to 2 * N
    this->ms_from_gadget_to_par = LWEModSwitcher(this->key_switch_key->destination.lwe_param, this->blind_rotation_key->lwe_par);
    // Mod Switch from Extracted Q to N
    this->ms_from_gadget_to_tiny_par = LWEModSwitcher(this->key_switch_key->destination.lwe_param, this->lwe_par_tiny);
    return *this;
}

 
FunctionalBootstrapPublicKey::FunctionalBootstrapPublicKey(BlindRotationPublicKey *blind_rotation_key, LWEToLWEKeySwitchKey *key_switch_key, LWEPublicKey *masking_public_key, FullDomainBootstrappingAlgorithm fdfb_alg){ 
    this->blind_rotation_key = std::shared_ptr<BlindRotationPublicKey>(blind_rotation_key);
    this->key_switch_key = std::shared_ptr<LWEToLWEKeySwitchKey>(key_switch_key);
    this->masking_public_key = std::shared_ptr<LWEPublicKey>(masking_public_key);
   
    this->fdfb_alg = fdfb_alg;
 
    // Initialize LWE_par_tiny for Full Domain Functiona Bootstrapping  
    this->lwe_par = this->blind_rotation_key->lwe_par;  
    this->lwe_par_tiny = this->blind_rotation_key->actual_lwe_par; 


    // Initialize BlindRotateOutput 
    this->br_out = this->blind_rotation_key->init_blind_rotate_output();
    this->br_temp = this->blind_rotation_key->init_blind_rotate_output(); 
  

    // TODO: This needs to change to accumulators, and not rotation polynomials (pointers to long even worse) 
    //this->rotation_poly_size = this->blind_rotation_key->actual_rotation_size; 
    this->acc_msb = this->blind_rotation_key->get_acc_msb();  
 
    // Set the LWE modulus swicher   
    // Mod Switch from Extracted Q to 2 * N
    this->ms_from_gadget_to_par = LWEModSwitcher(this->key_switch_key->destination.lwe_param, this->lwe_par);
    // Mod Switch from Extracted Q to N
    this->ms_from_gadget_to_tiny_par = LWEModSwitcher(this->key_switch_key->destination.lwe_param, this->lwe_par_tiny);
  
}
  

LWECT FunctionalBootstrapPublicKey::encrypt(long message){  
    return this->masking_public_key->encrypt(message); 
}

 
 
void FunctionalBootstrapPublicKey::bootstrap(long *lwe_ct_out, std::shared_ptr<AbstractAccumulator> acc_in, long *lwe_ct_in, GadgetMulMode mode){     

    // 1) Key switch to \ZZ_Q^{n+1} 
    long *lwe_c = ms_from_gadget_to_par.from->init_ct();     
    key_switch_key->lwe_to_lwe_key_switch(lwe_c, lwe_ct_in); 
 
    // 2) Mod switch to \ZZ_2N^{n+1}  
    ms_from_gadget_to_par.switch_modulus(lwe_c, lwe_c);
  
    // 3) Blind rotate    
    blind_rotation_key->blind_rotate(br_out, lwe_c, acc_in, mode);
    // 4) Sample Extract    
    br_out->extract_lwe(lwe_ct_out);

    // 5) If simulation mode, then rerandomize the ciphertext   
    if(mode == simul){     
        masking_public_key->mask_ciphertext(lwe_ct_out); 
    }   
    delete[] lwe_c; 
      
}



void FunctionalBootstrapPublicKey::full_domain_bootstrap(long *lwe_ct_out, std::shared_ptr<AbstractAccumulator> acc_in, long *lwe_ct_in, GadgetMulMode mode, int t){    
    if(fdfb_alg == liu_micciancio_polyakov){
        liu_micciancio_polyakov_bootstrap(lwe_ct_out, acc_in, lwe_ct_in, mode, t);
    }else{
        throw std::logic_error("FunctionalBootstrapPublicKey::full_domain_bootstrap: No such full domain bootstrapping algorithm!");
    }
}
 
 


void FunctionalBootstrapPublicKey::liu_micciancio_polyakov_bootstrap(long *lwe_ct_out, std::shared_ptr<AbstractAccumulator> acc_in, long *lwe_ct_in, GadgetMulMode mode, int t){    
    // 1) Key switch to \ZZ_Q^{n+1}  
    long *lwe_c_N = ms_from_gadget_to_par.from->init_ct();
    long *lwe_c = ms_from_gadget_to_par.from->init_ct();
 
    key_switch_key->lwe_to_lwe_key_switch(lwe_c_N, lwe_ct_in); 
  
    // 2) Mod switch to \ZZ_2N^{n+1} Note that this should actually modulus switch to N not to 2N!  
    ms_from_gadget_to_tiny_par.switch_modulus(lwe_c_N, lwe_c_N);

    // Shifting to have the ``payload'' withing (0, N) 
    // - otherwise for message 0, we could have negative noise and the phase could be also in (N, 2N) 
    lwe_c[0] = lwe_c_N[0] + round((double)lwe_par_tiny->Q/(2 *t)); 
 
    // In case modulus reduction happens here, we need to flip the extracted MSB
    bool modulus_reduction_event = false;
    if(lwe_c[0] >= lwe_par_tiny->Q){  
        lwe_c[0] = lwe_c[0] % lwe_par_tiny->Q; 
        modulus_reduction_event = true;
    }
    // Copy  
    for(int i = 1; i < lwe_par_tiny->n+1; ++i){
        lwe_c[i] = lwe_c_N[i];
    }    
  
    // 3) Blind rotate (Compute the sign, but with scale 2N/2 = N!)   
    blind_rotation_key->blind_rotate(br_out, lwe_c, acc_msb, deter);  
 
    // 4) Sample Extract (I can perform it oon the lwe_ct_out because it should have the right dimension)  
    br_out->extract_lwe(lwe_ct_out);
  
    // And again: 
    key_switch_key->lwe_to_lwe_key_switch(lwe_c, lwe_ct_out); 
      
    // 2) Mod switch to \ZZ_2N^{n+1} Note that this should actually modulus switch to N not to 2N!  
    ms_from_gadget_to_par.switch_modulus(lwe_c, lwe_c); 

    // Add lwe_c + lwe_c_N (this should eliminate the msb in lwe_c_N) 
    for(int i = 0; i < this->lwe_par->n+1; ++i){
        lwe_c[i] = (lwe_c[i] + lwe_c_N[i]) % lwe_par->Q;
    }  
    if(modulus_reduction_event){ 
        lwe_c[0] = Utils::integer_mod_form(lwe_c[0] - (long)round((double)(3 * lwe_par->Q)/4), lwe_par->Q);
    }else{
        lwe_c[0] = Utils::integer_mod_form(lwe_c[0] - (long)round((double)lwe_par->Q/4), lwe_par->Q);
    }  
      
    // 3) Blind rotate 
    blind_rotation_key->blind_rotate(br_out, lwe_c, acc_in, mode);
  
    // 4) Sample Extract   
    br_out->extract_lwe(lwe_ct_out);

    // 5) If simulation mode, then rerandomize the ciphertext 
    if(mode == simul){  
        masking_public_key->mask_ciphertext(lwe_ct_out);
        
    } 
    delete[] lwe_c_N;
    delete[] lwe_c;
} 
 



 
std::vector<LWECT> FunctionalBootstrapPublicKey::bootstrap(std::vector<std::shared_ptr<AbstractAccumulator>> acc_in_vec, long *lwe_ct_in, GadgetMulMode mode, PlaintextEncoding encoding){   
    // 1) Key switch to \ZZ_Q^{n+1} 
    long *lwe_c = ms_from_gadget_to_par.from->init_ct();
     
    key_switch_key->lwe_to_lwe_key_switch(lwe_c, lwe_ct_in); 

    // 2) Mod switch to \ZZ_2N^{n+1}  
    ms_from_gadget_to_par.switch_modulus(lwe_c, lwe_c);

    // 3) Blind rotate     
    acc_one = blind_rotation_key->get_acc_one(encoding);
 
    blind_rotation_key->blind_rotate(br_out, lwe_c, acc_one, mode);
  
    std::vector<LWECT> out_vec; 
    
    long* lwe_ct_out = key_switch_key->origin->init_ct();

    for(std::shared_ptr<AbstractAccumulator> i:  acc_in_vec){     
        i->setup_amortization();
        br_out->post_rotation(br_temp, i);   
        br_temp->extract_lwe(lwe_ct_out);
        if(mode == simul){   
            masking_public_key->mask_ciphertext(lwe_ct_out); 
        }    
        out_vec.push_back(LWECT(key_switch_key->origin, lwe_ct_out));  
    } 
    delete[] lwe_c;  
    delete[] lwe_ct_out;
    return out_vec;
}

 
std::vector<LWECT> FunctionalBootstrapPublicKey::full_domain_bootstrap(std::vector<std::shared_ptr<AbstractAccumulator>> acc_in_vec, long *lwe_ct_in, GadgetMulMode mode, PlaintextEncoding encoding){
    if(fdfb_alg == liu_micciancio_polyakov){
        return liu_micciancio_polyakov_bootstrap(acc_in_vec, lwe_ct_in, mode, encoding);
    }else{
        throw std::logic_error("FunctionalBootstrapPublicKey::full_domain_bootstrap: No such full domain bootstrapping algorithm!");
    }
}
 
 
std::vector<LWECT> FunctionalBootstrapPublicKey::liu_micciancio_polyakov_bootstrap(std::vector<std::shared_ptr<AbstractAccumulator>> acc_in_vec, long *lwe_ct_in, GadgetMulMode mode, PlaintextEncoding encoding){   
    // 1) Key switch to \ZZ_Q^{n+1} 
    long *lwe_c_N = ms_from_gadget_to_par.from->init_ct();
    long *lwe_c = ms_from_gadget_to_par.from->init_ct();
    long* lwe_ct_out = key_switch_key->origin->init_ct();

 
    key_switch_key->lwe_to_lwe_key_switch(lwe_c_N, lwe_ct_in);
  
    // 2) Mod switch to \ZZ_2N^{n+1} Note that this should actually modulus switch to N not to 2N! 
    ms_from_gadget_to_tiny_par.switch_modulus(lwe_c_N, lwe_c_N);

    // Shifting to have the ``payload'' withing (0, N) 
    // - otherwise for message 0, we could have negative noise and the phase could be also in (N, 2N) 
    lwe_c[0] = lwe_c_N[0] + round((double)lwe_par_tiny->Q/(2 * encoding.ticks)); 
 
    // In case modulus reduction happens here, we need to flip the extracted MSB
    bool modulus_reduction_event = false;
    if(lwe_c[0] >= lwe_par_tiny->Q){  
        lwe_c[0] = lwe_c[0] % lwe_par_tiny->Q; 
        modulus_reduction_event = true;
    }
    // Copy  
    for(int i = 1; i < lwe_par_tiny->n+1; ++i){
        lwe_c[i] = lwe_c_N[i];
    }    
    // 3) Blind rotate (Compute the sign, but with scale 2N/2 = N!)   
    blind_rotation_key->blind_rotate(br_out, lwe_c, acc_msb, deter);

    // 4) Sample Extract (I can perform it oon the lwe_ct_out because it should have the right dimension)  
    br_out->extract_lwe(lwe_ct_out);
   
    key_switch_key->lwe_to_lwe_key_switch(lwe_c_N, lwe_ct_in);
    
    // 2) Mod switch to \ZZ_2N^{n+1} Note that this should actually modulus switch to N not to 2N! 
    ms_from_gadget_to_par.switch_modulus(lwe_c, lwe_c);

    // Add lwe_c + lwe_c_N (this should eliminate the msb in lwe_c_N) 
    for(int i = 0; i < lwe_par->n+1; ++i){
        lwe_c[i] = (lwe_c[i] + lwe_c_N[i]) % lwe_par->Q;
    }  
    if(modulus_reduction_event){ 
        lwe_c[0] = Utils::integer_mod_form(lwe_c[0] - (long)round((double)(3 * lwe_par->Q)/4), lwe_par->Q);
    }else{
        lwe_c[0] = Utils::integer_mod_form(lwe_c[0] - (long)round((double)lwe_par->Q/4), lwe_par->Q);
    }  
      
    // 3) Blind rotate  
    acc_one = blind_rotation_key->get_acc_one(encoding);
  
    blind_rotation_key->blind_rotate(br_out, lwe_c, acc_one, mode);
       
    std::vector<LWECT> out_vec; 
    for(std::shared_ptr<AbstractAccumulator> i:  acc_in_vec){   
        i->setup_amortization();
        br_out->post_rotation(br_temp, i);   
        br_temp->extract_lwe(lwe_ct_out);

        // 5) If simulation mode, then rerandomize the ciphertext  
        if(mode == simul){  
            masking_public_key->mask_ciphertext(lwe_ct_out); 
        }   
        out_vec.push_back(LWECT(key_switch_key->origin, lwe_ct_out));  
    } 
    delete[] lwe_c_N;
    delete[] lwe_c; 
    delete[] lwe_ct_out;
    return out_vec;
} 







 
FunctionalBootstrapSecretKey::~FunctionalBootstrapSecretKey(){ 
    if(is_ext_init){  
        delete[] u;
        delete[] ext_s;
    } 
}

 
FunctionalBootstrapSecretKey::FunctionalBootstrapSecretKey(RLWEGadgetParam rlwe_gadget_par, LWEGadgetParam lwe_gadget_par, PolynomialArithmetic sk_arithmetic, int masking_size, double stddev_masking, PlaintextEncoding default_encoding, FullDomainBootstrappingAlgorithm fdfb_alg){   
    RLWESK rlwe(rlwe_gadget_par.rlwe_param, sk_arithmetic); 
    this->rlwe_gadget_sk =  RLWEGadgetSK(rlwe_gadget_par, rlwe);
    this->masking_size = masking_size;
    this->stddev_masking = stddev_masking;
    this->default_encoding = default_encoding;

    this->fdfb_alg = fdfb_alg;
 
    LWESK g_lwe = LWESK(lwe_gadget_par.lwe_param);
    this->lwe_gadget_sk = LWEGadgetSK(lwe_gadget_par, g_lwe); 
    long q = rlwe.param->N * 2; 
    this->lwe_sk = lwe_gadget_sk.lwe.modulus_switch(q);    
    long* extract_key = new long[rlwe.param->N];
    this->rlwe_gadget_sk.sk.extract_lwe_key(extract_key);
    extract_lwe_sk = LWESK(std::shared_ptr<LWEParam>(new LWEParam(rlwe.param->N, rlwe.param->Q, rlwe_gadget_par.rlwe_param->key_type, rlwe_gadget_par.rlwe_param->stddev)), extract_key); 
 
    if(lwe_gadget_sk.gadget_param.lwe_param->key_d == binary){   
        this->init_binary_key(); 
    }else{  
        this->init_ternary_key();
    }   
    delete[] extract_key;   
}


FunctionalBootstrapSecretKey::FunctionalBootstrapSecretKey(const FunctionalBootstrapSecretKey& other){
    this->rlwe_gadget_sk =  other.rlwe_gadget_sk;
    this->masking_size = other.masking_size;
    this->stddev_masking = other.stddev_masking;
    this->default_encoding = other.default_encoding;
 
    this->lwe_gadget_sk = other.lwe_gadget_sk;  
    this->lwe_sk = other.lwe_sk; 
 
    this->extract_lwe_sk = other.extract_lwe_sk;
 
    if(lwe_gadget_sk.gadget_param.lwe_param->key_d == binary){   
        this->init_binary_key(); 
    }else{  
        this->init_ternary_key();
    }     
}


FunctionalBootstrapSecretKey& FunctionalBootstrapSecretKey::operator=(const FunctionalBootstrapSecretKey other){ 
    if (this == &other)
    {
        return *this;
    } 
    this->masking_size = other.masking_size;  
    this->stddev_masking = other.stddev_masking;  
    this->default_encoding = other.default_encoding;  
    this->lwe_gadget_sk = other.lwe_gadget_sk;    
    this->lwe_sk = other.lwe_sk;   
    this->extract_lwe_sk = other.extract_lwe_sk;  

    this->rlwe_gadget_sk = other.rlwe_gadget_sk;  
    if(lwe_gadget_sk.gadget_param.lwe_param->key_d == binary){   
        this->init_binary_key(); 
    }else{  
        this->init_ternary_key();
    }     
    return *this;
}


std::shared_ptr<FunctionalBootstrapPublicKey> FunctionalBootstrapSecretKey::get_public_param(){   
    // Key Switching Key Gen
    LWEToLWEKeySwitchKey *ks_public_key = new LWEToLWEKeySwitchKey(&extract_lwe_sk, &lwe_gadget_sk); 
    // Masking Key Gen
    LWEPublicKey *masking_public_key = new LWEPublicKey(&extract_lwe_sk, masking_size, stddev_masking);
    // The blind rotation key  
    BlindRotationPublicKey *blind_rotation_key = new GINXBlindRotationKey(&rlwe_gadget_sk, &lwe_sk); 
 
    std::shared_ptr<FunctionalBootstrapPublicKey> out(new FunctionalBootstrapPublicKey(blind_rotation_key, ks_public_key, masking_public_key, fdfb_alg));
    return out;   
}

   


void FunctionalBootstrapSecretKey::init_binary_key(){
        sizeof_u = 1;
        this->u = new long[sizeof_u];
        u[0] = 1;
        sizeof_ext_s = lwe_sk.param->n;
        this->ext_s = new long[sizeof_ext_s];
        for(int i = 0; i < lwe_sk.param->n; ++i){
            this->ext_s[i] = lwe_sk.s[i];
        }
        is_ext_init = true;
}

void FunctionalBootstrapSecretKey::init_ternary_key(){
        sizeof_u = 1;
        this->u = new long[sizeof_u];
        u[0] = 1;
        sizeof_ext_s = lwe_sk.param->n;
        this->ext_s = new long[sizeof_ext_s];
        for(int i = 0; i < lwe_sk.param->n; ++i){
            this->ext_s[i] = lwe_sk.s[i];
        }
        is_ext_init = true;
}
 

// This is a special way of encoding the lwe, so that we can immediately do a functional blind rotation
 long* FunctionalBootstrapSecretKey::scale_and_encrypt_initial_lwe(long m, int t){
     long* out = lwe_sk.param->init_ct();
     scale_and_encrypt_initial_lwe(out, m, t);
     return out;
 }
    
    // This is a special way of encoding the lwe, so that we can immediately do a functional blind rotation
 void FunctionalBootstrapSecretKey::scale_and_encrypt_initial_lwe(long* ct, long m, int t){ 
    double scale = (double)lwe_sk.param->Q/ (2 * t);
    long m_scaled =  (long)round((double)m * scale); 
    lwe_sk.encrypt(ct, m_scaled);
}
  