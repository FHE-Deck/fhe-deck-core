
#include "../include/rlwe_hom_acc_scheme.h"

 
rlwe_hom_acc_scheme::~rlwe_hom_acc_scheme(){ 
    delete[] u;
    delete[] acc_msb;
    for(int i = 0; i < rlwe_gadget_par.param.N; ++i){ 
        for(int j = 0; j < lwe_gadget_par.ell; ++j){ 
            delete[] ksk[i][j];
        }
        delete[] ksk[i];
    } 
    delete[] ksk; 
    delete[] bk;
}

rlwe_hom_acc_scheme::rlwe_hom_acc_scheme(){}


rlwe_hom_acc_scheme::rlwe_hom_acc_scheme(rlwe_gadget_param rlwe_gadget_par, 
                lwe_gadget_param lwe_gadget_par, 
                lwe_param lwe_par, 
                rlwe_gadget_ct *bk, 
                long ***ksk, 
                long **masking_key, 
                int masking_size,
                double stddev_masking){

    this->rlwe_gadget_par = rlwe_gadget_par;
    this->lwe_gadget_par = lwe_gadget_par;
    this->lwe_par = lwe_par;
    this->lwe_par_tiny = lwe_par.modulus_switch(rlwe_gadget_par.param.N);
    this->masking_key = masking_key;
    this->masking_size = masking_size; 
    this->stddev_masking = stddev_masking;
    this->rand_masking = sampler(0.0, stddev_masking);
    extract_lwe_par = lwe_param(rlwe_gadget_par.param.N, rlwe_gadget_par.param.Q, lwe_par.key_d, lwe_par.stddev); 
    key_d = lwe_par.key_d;
    if(key_d == binary){  
        init_binary_key(); 
    }else{ 
        init_ternary_key();
    } 
    this->ksk = ksk;
    this->bk = bk;  
    this->acc_msb = rotation_poly::rot_msb(4, rlwe_gadget_par.param.N, rlwe_gadget_par.param.Q); 
    set_key_switch_type();
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



void rlwe_hom_acc_scheme::blind_rotate(rlwe_ct *out, long* lwe_ct_in, long *acc_msg, gadget_mul_mode mode){   
    // Set curr_acc.a to zero
    for(int i = 0; i < rlwe_gadget_par.param.N; ++i){
        out->a[i] = 0;
    }  
    utils::negacyclic_rotate_poly(out->b, acc_msg, rlwe_gadget_par.param.N, lwe_ct_in[0]);  
    rlwe_ct next_acc(&rlwe_gadget_par.param); 
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
    rlwe_ct out_ct(&rlwe_gadget_par.param); 
    blind_rotate(&out_ct, lwe_c, acc_in, mode);  
    // 4) Sample Extract  
    extract_lwe_from_rlwe(lwe_ct_out, &out_ct);
    // 5) If simulation mode, then rerandomize the ciphertext  
    if(mode == simul){  
        mask_ciphertext(lwe_ct_out); 
    } 
    delete[] lwe_c; 
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

/*
This bootstrapping assumes that the input ciphertext is mod 2N, but with message < N
*/
void rlwe_hom_acc_scheme::functional_bootstrap_initial(long *lwe_ct_out, long *acc_in, long *lwe_ct_in, gadget_mul_mode mode){   
    // 3) Blind rotate
    rlwe_ct out_ct(&rlwe_gadget_par.param);
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
    lwe_to_lwe_key_switch_lazy(lwe_c_N, lwe_ct_in);
  
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
    rlwe_ct out_ct(&rlwe_gadget_par.param); 
    blind_rotate(&out_ct, lwe_c, acc_msb, deter);  

    // 4) Sample Extract (I can perform it oon the lwe_ct_out because it should have the right dimension)
    extract_lwe_from_rlwe(lwe_ct_out, &out_ct);  
  
    // And again:
    lwe_to_lwe_key_switch_lazy(lwe_c, lwe_ct_out); 
    
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
    // lwe_c should have its phase witin (0, N)  
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
 



 