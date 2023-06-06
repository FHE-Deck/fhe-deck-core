
#include "../include/rlwe_hom_acc_scheme.h"

 
rlwe_hom_acc_scheme::~rlwe_hom_acc_scheme(){  
    if(is_init == false){
        return;
    } 
    delete[] u;
    delete[] acc_msb;
    delete[] acc_one; 
    for(int i = 0; i < rlwe_gadget_par.param.N; ++i){ 
        for(int j = 0; j < lwe_gadget_par.ell; ++j){ 
            delete[] ksk[i][j];
        }
        delete[] ksk[i];
    } 
    delete[] ksk;  
    for(int i = 0; i < masking_size; ++i){
        delete[] masking_key[i];
    }
    delete[] masking_key; 
    delete[] bk; 
}
 
 

rlwe_hom_acc_scheme::rlwe_hom_acc_scheme(const rlwe_hom_acc_scheme &other){
    this->rlwe_gadget_par = other.rlwe_gadget_par;
    this->lwe_gadget_par = other.lwe_gadget_par;
    this->lwe_par = other.lwe_par; 
    this->masking_size = other.masking_size; 
    this->stddev_masking = other.stddev_masking;
    this->default_encoding = other.default_encoding;
 

    // Sets other variables
    this->lwe_par_tiny = lwe_par.modulus_switch(rlwe_gadget_par.param.N);
    this->rand_masking = sampler(0.0, stddev_masking);
    this->extract_lwe_par = lwe_param(rlwe_gadget_par.param.N, rlwe_gadget_par.param.Q, lwe_par.key_d, lwe_par.stddev);  
    this->temp_ct = rlwe_ct(rlwe_gadget_par.param);
    this->next_acc = rlwe_ct(rlwe_gadget_par.param);
    this->out_ct = rlwe_ct(rlwe_gadget_par.param); 
    this->out_ct.set_computing_engine();
    this->key_d = lwe_par.key_d;
    if(this->key_d == binary){  
        init_binary_key(); 
    }else{ 
        init_ternary_key();
    } 
    set_key_switch_type();
    this->acc_msb = rotation_poly::rot_msb(4, rlwe_gadget_par.param.N, rlwe_gadget_par.param.Q); 
    this->acc_one  = rotation_poly::rot_one(rlwe_gadget_par.param.N);
  
    copy_blind_rotation_key(other.bk);
    copy_key_switching_key(other.ksk);
    copy_masking_key(other.masking_key);
    is_init = true;
}

 


rlwe_hom_acc_scheme& rlwe_hom_acc_scheme::operator=(const rlwe_hom_acc_scheme other){
    this->rlwe_gadget_par = other.rlwe_gadget_par;
    this->lwe_gadget_par = other.lwe_gadget_par;
    this->lwe_par = other.lwe_par; 
    this->masking_size = other.masking_size; 
    this->stddev_masking = other.stddev_masking;
    this->default_encoding = other.default_encoding;
 

    // Sets other variables
    this->lwe_par_tiny = lwe_par.modulus_switch(rlwe_gadget_par.param.N);
    this->rand_masking = sampler(0.0, stddev_masking);
    this->extract_lwe_par = lwe_param(rlwe_gadget_par.param.N, rlwe_gadget_par.param.Q, lwe_par.key_d, lwe_par.stddev);  
    this->temp_ct = rlwe_ct(rlwe_gadget_par.param);
    this->next_acc = rlwe_ct(rlwe_gadget_par.param);
    this->out_ct = rlwe_ct(rlwe_gadget_par.param); 
    this->out_ct.set_computing_engine();
    this->key_d = lwe_par.key_d;
    if(this->key_d == binary){  
        init_binary_key(); 
    }else{ 
        init_ternary_key();
    } 
    set_key_switch_type();
    this->acc_msb = rotation_poly::rot_msb(4, rlwe_gadget_par.param.N, rlwe_gadget_par.param.Q); 
    this->acc_one  = rotation_poly::rot_one(rlwe_gadget_par.param.N);
  
    copy_blind_rotation_key(other.bk);
    copy_key_switching_key(other.ksk);
    copy_masking_key(other.masking_key);
    is_init = true;
    return *this;
}



rlwe_hom_acc_scheme::rlwe_hom_acc_scheme(rlwe_gadget_param rlwe_gadget_par, 
                lwe_gadget_param lwe_gadget_par, 
                lwe_param lwe_par, 
                rlwe_gadget_ct *bk, 
                long ***ksk, 
                long **masking_key, 
                int masking_size,
                double stddev_masking,
                plaintext_encoding default_encoding){

    this->rlwe_gadget_par = rlwe_gadget_par;
    this->lwe_gadget_par = lwe_gadget_par;
    this->lwe_par = lwe_par;
    this->masking_size = masking_size; 
    this->stddev_masking = stddev_masking;
    this->default_encoding = default_encoding;
     
    // Sets other variables 
    this->lwe_par_tiny = lwe_par.modulus_switch(rlwe_gadget_par.param.N);
    this->rand_masking = sampler(0.0, stddev_masking);
    this->extract_lwe_par = lwe_param(rlwe_gadget_par.param.N, rlwe_gadget_par.param.Q, lwe_par.key_d, lwe_par.stddev);  
    this->temp_ct = rlwe_ct(rlwe_gadget_par.param);
    this->next_acc = rlwe_ct(rlwe_gadget_par.param);
    this->out_ct = rlwe_ct(rlwe_gadget_par.param);
    this->out_ct.set_computing_engine();

    this->key_d = lwe_par.key_d;
    if(this->key_d == binary){  
        init_binary_key(); 
    }else{ 
        init_ternary_key();
    } 
    set_key_switch_type();
    this->acc_msb = rotation_poly::rot_msb(4, rlwe_gadget_par.param.N, rlwe_gadget_par.param.Q); 
    this->acc_one  = rotation_poly::rot_one(rlwe_gadget_par.param.N);
 
    // Set the key switching, bilind rotation and masking keys
    this->bk = bk;
    //copy_blind_rotation_key(bk);
    this->ksk = ksk;  
    this->masking_key = masking_key;
    is_init = true;
}




void rlwe_hom_acc_scheme::set_key_switch_type(){ 
    long bits_Q = utils::power_times(lwe_gadget_par.lwe_par.Q, 2);
    long bits_base = utils::power_times(lwe_gadget_par.basis, 2);
    long bits_N = utils::power_times(rlwe_gadget_par.param.N, 2); 
    lwe_gadget_par.ell;
    long sum_lazy_bits = bits_Q + bits_base + lwe_gadget_par.ell + bits_N;
    long sum_partial_lazy_bits = bits_Q + bits_base + lwe_gadget_par.ell + 1;
    if(sum_lazy_bits < 64){
        std::cout << "rlwe_hom_acc_scheme: Using Lazy Key Switch" << std::endl;
        ks_type = lazy_key_switch;
    }else if(sum_partial_lazy_bits < 64){
        std::cout << "rlwe_hom_acc_scheme: Using Partial Lazy Key Switch" << std::endl;
        ks_type = partial_lazy_key_switch;
    }else{
        std::cout << "Using Standard Key Switch" << std::endl;
        ks_type = standard_key_switch;
    }
}

void rlwe_hom_acc_scheme::init_binary_key(){
        sizeof_u = 1;
        this->u = new long[sizeof_u];
        u[0] = 1;
        sizeof_ext_s = lwe_par.n;
}

void rlwe_hom_acc_scheme::init_ternary_key(){
        sizeof_u = 2;
        this->u = new long[sizeof_u];
        u[0] = -1;
        u[1] = 1;
        sizeof_ext_s = 2*lwe_par.n; 
}


void rlwe_hom_acc_scheme::copy_blind_rotation_key(rlwe_gadget_ct *bk){
    this->bk = new rlwe_gadget_ct[this->sizeof_ext_s];
    for(int i = 0; i < this->sizeof_ext_s; ++i){
        this->bk[i] = bk[i];
    }
}
  

void rlwe_hom_acc_scheme::copy_key_switching_key(long ***ksk){
    // Initialize the key switching key
    this->ksk = new long**[rlwe_gadget_par.param.N]; 
    for(int i = 0; i < rlwe_gadget_par.param.N; ++i){
        this->ksk[i] = new long*[lwe_gadget_par.ell];
        for(int j = 0; j < lwe_gadget_par.ell; ++j){ 
            this->ksk[i][j] = lwe_gadget_par.lwe_par.init_ct();
        }
    } 
    for(int i = 0; i < rlwe_gadget_par.param.N; ++i){  
        for(int j = 0; j < lwe_gadget_par.ell; ++j){ 
            utils::cp(this->ksk[i][j], ksk[i][j], lwe_gadget_par.lwe_par.n+1); 
        }
    }  
}


void rlwe_hom_acc_scheme::copy_masking_key(long **masking_key){
    // Initialize the key switching key
    this->masking_key = new long*[masking_size]; 
    for(int i = 0; i < masking_size; ++i){ 
        this->masking_key[i] = extract_lwe_par.init_ct();
        utils::cp(this->masking_key[i], masking_key[i], extract_lwe_par.n+1); 
    } 
}


void rlwe_hom_acc_scheme::blind_rotate(rlwe_ct *out, long* lwe_ct_in, long *acc_msg, gadget_mul_mode mode){     
    // Set curr_acc.a to zero
    for(int i = 0; i < rlwe_gadget_par.param.N; ++i){
        out->a[i] = 0;
    }   
    utils::negacyclic_rotate_poly(out->b, acc_msg, rlwe_gadget_par.param.N, lwe_ct_in[0]);   
      
    if(key_d==binary){    
        for(int i = 0; i < lwe_par.n; ++i){    
            out->negacyclic_rotate(&next_acc, lwe_ct_in[i+1]);   
            next_acc.sub(&next_acc, out);      
            bk[i].mul(&next_acc, &next_acc, mode);    
            next_acc.add(out, out); 
        } 
    } 
    else if(key_d==ternary){  
        // Rotatate back (multipliation by X^{-ct[i+1]}) and mul with bk_eval[i]
        long back_rotations;
         for(int i = 0; i < lwe_par.n; ++i){  
            back_rotations = utils::integer_mod_form(-lwe_ct_in[i+1], lwe_par.Q); 
            out->negacyclic_rotate(&next_acc, back_rotations);
            next_acc.sub(&next_acc, out);  
            bk[i].mul(out, &next_acc, mode);
            out->add(out, out);  
        } 
        // Rotatate forward (multipliation by X^{ct[i+1]}) and mul with bk_eval[lwe_par.n+i]
         for(int i = 0; i < lwe_par.n; ++i){ 
            out->negacyclic_rotate(&next_acc, back_rotations);
            next_acc.sub(&next_acc, out);  
            bk[lwe_par.n+i].mul(out, &next_acc, mode);
            out->add(out, out);   
        }
    }    
    utils::array_mod_form(out->a, out->a, rlwe_gadget_par.param.N, rlwe_gadget_par.param.Q); 
    utils::array_mod_form(out->b, out->b, rlwe_gadget_par.param.N, rlwe_gadget_par.param.Q);
}

void rlwe_hom_acc_scheme::extract_lwe_from_rlwe(long *lwe_ct_out, const rlwe_ct *rlwe_ct_in){
    lwe_ct_out[0] = rlwe_ct_in->b[0];
    lwe_ct_out[1] = rlwe_ct_in->a[0];
    for(int i = 1; i < rlwe_gadget_par.param.N; ++i){
        lwe_ct_out[i+1] = -rlwe_ct_in->a[rlwe_gadget_par.param.N - i];
    }
}


void rlwe_hom_acc_scheme::lwe_to_lwe_key_switch_lazy(long *lwe_ct_out, long *lwe_ct_in){
    lwe_gadget_par.gadget_mul_lazy(lwe_ct_out, ksk[0], lwe_ct_in[1]); 
    long *temp_lwe_ct = lwe_gadget_par.lwe_par.init_ct(); 
    for(int i=2; i < rlwe_gadget_par.param.N+1; ++i){  
        lwe_gadget_par.gadget_mul_lazy(temp_lwe_ct, ksk[i-1], lwe_ct_in[i]); 
        lwe_gadget_par.lwe_par.add_lazy(lwe_ct_out, lwe_ct_out, temp_lwe_ct); 
    }  
    lwe_ct_out[0] = lwe_ct_in[0] + lwe_ct_out[0];
    utils::array_mod_form(lwe_ct_out, lwe_ct_out, lwe_gadget_par.lwe_par.n+1, lwe_gadget_par.lwe_par.Q); 
    delete[] temp_lwe_ct;
}


void rlwe_hom_acc_scheme::lwe_to_lwe_key_switch_partial_lazy(long *lwe_ct_out, long *lwe_ct_in){
    lwe_gadget_par.gadget_mul_lazy(lwe_ct_out, ksk[0], lwe_ct_in[1]); 
    long *temp_lwe_ct = lwe_gadget_par.lwe_par.init_ct(); 
    for(int i=2; i < rlwe_gadget_par.param.N+1; ++i){  
        lwe_gadget_par.gadget_mul_lazy(temp_lwe_ct, ksk[i-1], lwe_ct_in[i]); 
        lwe_gadget_par.lwe_par.add_lazy(lwe_ct_out, lwe_ct_out, temp_lwe_ct); 
        utils::array_mod_form(lwe_ct_out, lwe_ct_out, lwe_gadget_par.lwe_par.n+1, lwe_gadget_par.lwe_par.Q);
    } 
    // Add the ``b'' term
    lwe_ct_out[0] = lwe_ct_in[0] + lwe_ct_out[0]; 
    utils::array_mod_form(lwe_ct_out, lwe_ct_out, lwe_gadget_par.lwe_par.n+1, lwe_gadget_par.lwe_par.Q);
    delete[] temp_lwe_ct;
}

 
void rlwe_hom_acc_scheme::lwe_to_lwe_key_switch(long *lwe_ct_out, long *lwe_ct_in){
    lwe_gadget_par.gadget_mul(lwe_ct_out, ksk[0], lwe_ct_in[1]); 
    long *temp_lwe_ct = lwe_gadget_par.lwe_par.init_ct(); 
    for(int i=2; i < rlwe_gadget_par.param.N+1; ++i){  
        lwe_gadget_par.gadget_mul(temp_lwe_ct, ksk[i-1], lwe_ct_in[i]); 
        lwe_gadget_par.lwe_par.add(lwe_ct_out, lwe_ct_out, temp_lwe_ct); 
    }  
    lwe_ct_out[0] = lwe_ct_in[0] + lwe_ct_out[0];
    utils::array_mod_form(lwe_ct_out, lwe_ct_out, lwe_gadget_par.lwe_par.n+1, lwe_gadget_par.lwe_par.Q);
    delete[] temp_lwe_ct;
}


lwe_ct rlwe_hom_acc_scheme::encrypt(long message){
    lwe_ct out(this->extract_lwe_par, masking_key[0]);
    long* temp = extract_lwe_par.init_ct();
    long noise;
    for(int i = 1; i < masking_size; ++i){
        noise = rand_masking.normal_dist(rand_masking.e1); 
        extract_lwe_par.scalar_mul(temp, masking_key[i], noise);
        extract_lwe_par.add(out.ct, out.ct, temp);
    }
    out = out + message;
    delete[] temp;
    return out;
}

 
void rlwe_hom_acc_scheme::mask_ciphertext(long *lwe_ct_out){
    long* random_lwe = extract_lwe_par.init_ct();
    long* temp = extract_lwe_par.init_ct();
    long noise;
    for(int i  = 0; i < masking_size; ++i){
        noise = rand_masking.normal_dist(rand_masking.e1); 
        extract_lwe_par.scalar_mul(temp, masking_key[i], noise);
        extract_lwe_par.add(lwe_ct_out, lwe_ct_out, temp);
    }
    delete[] random_lwe;
    delete[] temp;
}

void rlwe_hom_acc_scheme::bootstrap(long *lwe_ct_out, long *acc_in, long *lwe_ct_in, gadget_mul_mode mode){  
    // 1) Key switch to \ZZ_Q^{n+1}
    long *lwe_c = lwe_gadget_par.lwe_par.init_ct(); 
    if(ks_type == lazy_key_switch){ 
        lwe_to_lwe_key_switch_lazy(lwe_c, lwe_ct_in);  
    }else if(ks_type == partial_lazy_key_switch){
        lwe_to_lwe_key_switch_partial_lazy(lwe_c, lwe_ct_in);  
    }else{
        lwe_to_lwe_key_switch(lwe_c, lwe_ct_in);  
    }
    // 2) Mod switch to \ZZ_2N^{n+1} 
    lwe_gadget_par.lwe_par.switch_modulus(lwe_c, lwe_c, lwe_par);  
    // 3) Blind rotate  
    blind_rotate(&out_ct, lwe_c, acc_in, mode);  
    // 4) Sample Extract  
    extract_lwe_from_rlwe(lwe_ct_out, &out_ct);
    // 5) If simulation mode, then rerandomize the ciphertext   
    if(mode == simul){   
        mask_ciphertext(lwe_ct_out); 
    }  
    delete[] lwe_c; 
}


/*
This bootstrapping assumes that the input ciphertext is mod 2N, but with message < N
*/
void rlwe_hom_acc_scheme::functional_bootstrap_initial(long *lwe_ct_out, long *acc_in, long *lwe_ct_in, gadget_mul_mode mode){   
    // 3) Blind rotate 
    blind_rotate(&out_ct, lwe_ct_in, acc_in, mode); 
    // 4) Sample Extract
    extract_lwe_from_rlwe(lwe_ct_out, &out_ct);
    if(mode == simul){  
        mask_ciphertext(lwe_ct_out); 
    } 
}


void rlwe_hom_acc_scheme::functional_bootstrap(long *lwe_ct_out, long *acc_in, long *lwe_ct_in, gadget_mul_mode mode, int t){   
    // 1) Key switch to \ZZ_Q^{n+1}
    long *lwe_c_N = lwe_gadget_par.lwe_par.init_ct();
    long *lwe_c = lwe_gadget_par.lwe_par.init_ct();
 
    if(ks_type == lazy_key_switch){ 
        lwe_to_lwe_key_switch_lazy(lwe_c_N, lwe_ct_in);  
    }else if(ks_type == partial_lazy_key_switch){
        lwe_to_lwe_key_switch_partial_lazy(lwe_c_N, lwe_ct_in);  
    }else{
        lwe_to_lwe_key_switch(lwe_c_N, lwe_ct_in);  
    }   
    
    // 2) Mod switch to \ZZ_2N^{n+1} Note that this should actually modulus switch to N not to 2N!
    lwe_gadget_par.lwe_par.switch_modulus(lwe_c_N, lwe_c_N, lwe_par_tiny); 

    // Shifting to have the ``payload'' withing (0, N) 
    // - otherwise for message 0, we could have negative noise and the phase could be also in (N, 2N) 
    lwe_c[0] = lwe_c_N[0] + round((double)lwe_par_tiny.Q/(2 *t)); 
 
    // In case modulus reduction happens here, we need to flip the extracted MSB
    bool modulus_reduction_event = false;
    if(lwe_c[0] >= lwe_par_tiny.Q){  
        lwe_c[0] = lwe_c[0] % lwe_par_tiny.Q; 
        modulus_reduction_event = true;
    }
    // Copy  
    for(int i = 1; i < lwe_par_tiny.n+1; ++i){
        lwe_c[i] = lwe_c_N[i];
    }    
  
    // 3) Blind rotate (Compute the sign, but with scale 2N/2 = N!)  
    blind_rotate(&out_ct, lwe_c, acc_msb, deter);  
 
    // 4) Sample Extract (I can perform it oon the lwe_ct_out because it should have the right dimension)
    extract_lwe_from_rlwe(lwe_ct_out, &out_ct);  
  
    // And again:
    if(ks_type == lazy_key_switch){ 
        lwe_to_lwe_key_switch_lazy(lwe_c, lwe_ct_out);  
    }else if(ks_type == partial_lazy_key_switch){
        lwe_to_lwe_key_switch_partial_lazy(lwe_c, lwe_ct_out);  
    }else{
        lwe_to_lwe_key_switch(lwe_c, lwe_ct_out);  
    }   
    
    // 2) Mod switch to \ZZ_2N^{n+1} Note that this should actually modulus switch to N not to 2N!
    lwe_gadget_par.lwe_par.switch_modulus(lwe_c, lwe_c, lwe_par);  

    // Add lwe_c + lwe_c_N (this should eliminate the msb in lwe_c_N) 
    for(int i = 0; i < lwe_par.n+1; ++i){
        lwe_c[i] = (lwe_c[i] + lwe_c_N[i]) % lwe_par.Q;
    }  
    if(modulus_reduction_event){ 
        lwe_c[0] = utils::integer_mod_form(lwe_c[0] - (long)round((double)(3 * lwe_par.Q)/4), lwe_par.Q);
    }else{
        lwe_c[0] = utils::integer_mod_form(lwe_c[0] - (long)round((double)lwe_par.Q/4), lwe_par.Q);
    }  
      
    // 3) Blind rotate
    blind_rotate(&out_ct, lwe_c, acc_in, mode);
  
    // 4) Sample Extract
    extract_lwe_from_rlwe(lwe_ct_out, &out_ct);

    // 5) If simulation mode, then rerandomize the ciphertext 
    if(mode == simul){  
        mask_ciphertext(lwe_ct_out);
        
    } 
    delete[] lwe_c_N;
    delete[] lwe_c;
} 
 



 
std::vector<lwe_ct> rlwe_hom_acc_scheme::bootstrap(std::vector<rotation_poly> acc_in_vec, long *lwe_ct_in, gadget_mul_mode mode, int t){  
     
    // 1) Key switch to \ZZ_Q^{n+1}
    long *lwe_c = lwe_gadget_par.lwe_par.init_ct(); 
    if(ks_type == lazy_key_switch){ 
        lwe_to_lwe_key_switch_lazy(lwe_c, lwe_ct_in);  
    }else if(ks_type == partial_lazy_key_switch){
        lwe_to_lwe_key_switch_partial_lazy(lwe_c, lwe_ct_in);  
    }else{
        lwe_to_lwe_key_switch(lwe_c, lwe_ct_in);  
    }
    // 2) Mod switch to \ZZ_2N^{n+1} 
    lwe_gadget_par.lwe_par.switch_modulus(lwe_c, lwe_c, lwe_par);  
    // 3) Blind rotate  
    
    acc_one[1] = (long)round((double)rlwe_gadget_par.param.Q/(double)t); 
     
    blind_rotate(&out_ct, lwe_c, acc_one, mode);   
  
    std::vector<lwe_ct> out_vec; 
  
    long* lwe_ct_out = extract_lwe_par.init_ct();
    for(rotation_poly i:  acc_in_vec){   
        out_ct.mul(&temp_ct, i.lookup_polynomial);  
        extract_lwe_from_rlwe(lwe_ct_out, &temp_ct);  
        if(mode == simul){   
            mask_ciphertext(lwe_ct_out); 
        }   
        out_vec.push_back(lwe_ct(extract_lwe_par, lwe_ct_out));  
    } 
    delete[] lwe_c;  
    delete[] lwe_ct_out;
    return out_vec;
}


/*
This bootstrapping assumes that the input ciphertext is mod 2N, but with message < N
*/
std::vector<lwe_ct> rlwe_hom_acc_scheme::functional_bootstrap_initial(std::vector<rotation_poly> acc_in_vec, long *lwe_ct_in, gadget_mul_mode mode, int t){   
    // 3) Blind rotate 
    acc_one[1] = (long)round((double)rlwe_gadget_par.param.Q/(double)t); 
    blind_rotate(&out_ct, lwe_ct_in, acc_one, mode); 
    
    std::vector<lwe_ct> out_vec; 
  
    long* lwe_ct_out = extract_lwe_par.init_ct();
    for(rotation_poly i:  acc_in_vec){   
        out_ct.mul(&temp_ct, i.lookup_polynomial);  
        extract_lwe_from_rlwe(lwe_ct_out, &temp_ct);  
        if(mode == simul){   
            mask_ciphertext(lwe_ct_out); 
        }   
        out_vec.push_back(lwe_ct(extract_lwe_par, lwe_ct_out));  
    }  
    
    delete[] lwe_ct_out;
    return out_vec;
}

 
std::vector<lwe_ct> rlwe_hom_acc_scheme::functional_bootstrap(std::vector<rotation_poly> acc_in_vec, long *lwe_ct_in, gadget_mul_mode mode, int t){  
    // 1) Key switch to \ZZ_Q^{n+1}
    long *lwe_c_N = lwe_gadget_par.lwe_par.init_ct();
    long *lwe_c = lwe_gadget_par.lwe_par.init_ct();
    long* lwe_ct_out = extract_lwe_par.init_ct();

    if(ks_type == lazy_key_switch){ 
        lwe_to_lwe_key_switch_lazy(lwe_c_N, lwe_ct_in);  
    }else if(ks_type == partial_lazy_key_switch){
        lwe_to_lwe_key_switch_partial_lazy(lwe_c_N, lwe_ct_in);  
    }else{
        lwe_to_lwe_key_switch(lwe_c_N, lwe_ct_in);  
    }   
  
    // 2) Mod switch to \ZZ_2N^{n+1} Note that this should actually modulus switch to N not to 2N!
    lwe_gadget_par.lwe_par.switch_modulus(lwe_c_N, lwe_c_N, lwe_par_tiny); 

    // Shifting to have the ``payload'' withing (0, N) 
    // - otherwise for message 0, we could have negative noise and the phase could be also in (N, 2N) 
    lwe_c[0] = lwe_c_N[0] + round((double)lwe_par_tiny.Q/(2 *t)); 
 
    // In case modulus reduction happens here, we need to flip the extracted MSB
    bool modulus_reduction_event = false;
    if(lwe_c[0] >= lwe_par_tiny.Q){  
        lwe_c[0] = lwe_c[0] % lwe_par_tiny.Q; 
        modulus_reduction_event = true;
    }
    // Copy  
    for(int i = 1; i < lwe_par_tiny.n+1; ++i){
        lwe_c[i] = lwe_c_N[i];
    }    
    // 3) Blind rotate (Compute the sign, but with scale 2N/2 = N!)  
    blind_rotate(&out_ct, lwe_c, acc_msb, deter);  

    // 4) Sample Extract (I can perform it oon the lwe_ct_out because it should have the right dimension)
    extract_lwe_from_rlwe(lwe_ct_out, &out_ct);  
  
    // And again: 
    if(ks_type == lazy_key_switch){ 
        lwe_to_lwe_key_switch_lazy(lwe_c, lwe_ct_out);  
    }else if(ks_type == partial_lazy_key_switch){
        lwe_to_lwe_key_switch_partial_lazy(lwe_c, lwe_ct_out);  
    }else{
        lwe_to_lwe_key_switch(lwe_c, lwe_ct_out);  
    }   
    
    // 2) Mod switch to \ZZ_2N^{n+1} Note that this should actually modulus switch to N not to 2N!
    lwe_gadget_par.lwe_par.switch_modulus(lwe_c, lwe_c, lwe_par);  

    // Add lwe_c + lwe_c_N (this should eliminate the msb in lwe_c_N) 
    for(int i = 0; i < lwe_par.n+1; ++i){
        lwe_c[i] = (lwe_c[i] + lwe_c_N[i]) % lwe_par.Q;
    }  
    if(modulus_reduction_event){ 
        lwe_c[0] = utils::integer_mod_form(lwe_c[0] - (long)round((double)(3 * lwe_par.Q)/4), lwe_par.Q);
    }else{
        lwe_c[0] = utils::integer_mod_form(lwe_c[0] - (long)round((double)lwe_par.Q/4), lwe_par.Q);
    }  
      
    // 3) Blind rotate
    acc_one[1] = (long)round((double)rlwe_gadget_par.param.Q/(double)t); 
    blind_rotate(&out_ct, lwe_c, acc_one, mode);
       
    std::vector<lwe_ct> out_vec; 
    for(rotation_poly i:  acc_in_vec){  
        out_ct.mul(&temp_ct, i.lookup_polynomial); 
        // 4) Sample Extract   
        extract_lwe_from_rlwe(lwe_ct_out, &temp_ct); 
        // 5) If simulation mode, then rerandomize the ciphertext  
        if(mode == simul){  
            mask_ciphertext(lwe_ct_out); 
        }  
        out_vec.push_back(lwe_ct(extract_lwe_par, lwe_ct_out)); 
    } 
    delete[] lwe_c_N;
    delete[] lwe_c; 
    delete[] lwe_ct_out;
    return out_vec;
} 