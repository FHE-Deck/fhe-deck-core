
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
                long ***ksk){

    this->rlwe_gadget_par =   rlwe_gadget_par;
    this->lwe_gadget_par = lwe_gadget_par;
    this->lwe_par = lwe_par;
    this->lwe_par_tiny = lwe_par.modulus_switch(rlwe_gadget_par.param.N);
    extract_lwe_par = lwe_param(rlwe_gadget_par.param.N, rlwe_gadget_par.param.Q, lwe_par.key_d, lwe_par.stddev); 
    key_d = lwe_par.key_d;
    if(key_d == binary){  
        init_binary_key(); 
    }else{ 
        init_ternary_key();
    } 
    this->ksk = ksk;
    this->bk = bk;  
    this->acc_msb = rlwe_hom_acc_scheme::rot_msb(4, rlwe_gadget_par.param.N, rlwe_gadget_par.param.Q); 
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
    //rlwe_ct curr_acc(rlwe_gadget_par.param);
    //curr_acc.a = rlwe_gadget_par.param.init_zero_poly();   
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
    //return out;
}

void rlwe_hom_acc_scheme::extract_lwe_from_rlwe(long *lwe_ct_out, const rlwe_ct *rlwe_ct_in){
    lwe_ct_out[0] = rlwe_ct_in->b[0];
    lwe_ct_out[1] = rlwe_ct_in->a[0];
    for(int i = 1; i < rlwe_gadget_par.param.N; ++i){
        lwe_ct_out[i+1] = -rlwe_ct_in->a[rlwe_gadget_par.param.N - i];
    }
}

void rlwe_hom_acc_scheme::lwe_to_lwe_key_switch(long *lwe_ct_out, long *lwe_ct_in){
    lwe_gadget_par.gadget_mul_no_mod_reduction(lwe_ct_out, ksk[0], lwe_ct_in[1]); 
    long *temp_lwe_ct = lwe_gadget_par.lwe_par.init_ct(); 
    for(int i=2; i < rlwe_gadget_par.param.N+1; ++i){ 
        // NOTE: I already assume that the negacyclicity and everything is handled earlier 
        // (after extraction and within the key switch procedure
        // Now I only need to make sure that I encode the secret key in the ksk correctly (coefs of the sk, negated)
        lwe_gadget_par.gadget_mul_no_mod_reduction(temp_lwe_ct, ksk[i-1], lwe_ct_in[i]); 
        lwe_gadget_par.lwe_par.add_no_mod_reduction(lwe_ct_out, lwe_ct_out, temp_lwe_ct); 
    } 
    // Add the ``b'' term
    lwe_ct_out[0] =  (lwe_ct_in[0] + lwe_ct_out[0]) % lwe_gadget_par.lwe_par.Q;
    // Modulus reduction only at the very end
    for(int i = 1; i < lwe_gadget_par.lwe_par.n+1; ++i){
        lwe_ct_out[i] = lwe_ct_out[i] % lwe_gadget_par.lwe_par.Q;
    } 
    delete(temp_lwe_ct);
}


void rlwe_hom_acc_scheme::bootstrap(long *lwe_ct_out, long *acc_in, long *lwe_ct_in, gadget_mul_mode mode){  
    // 1) Key switch to \ZZ_Q^{n+1}
    long *lwe_c = lwe_gadget_par.lwe_par.init_ct();
    lwe_to_lwe_key_switch(lwe_c, lwe_ct_in);  
    // 2) Mod switch to \ZZ_2N^{n+1}
    lwe_gadget_par.lwe_par.switch_modulus(lwe_c, lwe_c, lwe_par);  
    // 3) Blind rotate 
    rlwe_ct out_ct(&rlwe_gadget_par.param);
    blind_rotate(&out_ct, lwe_c, acc_in, mode);  
    // 4) Sample Extract
    extract_lwe_from_rlwe(lwe_ct_out, &out_ct);
    delete[] lwe_c;
}
 


/*
This bootstrapping assumes that the input ciphertext is mod 2N, but with message scale N/t (instead of 2N/t)
*/
void rlwe_hom_acc_scheme::functional_bootstrap_initial(long *lwe_ct_out, long *acc_in, long *lwe_ct_in, gadget_mul_mode mode){   
    // 3) Blind rotate
    rlwe_ct out_ct(&rlwe_gadget_par.param);
    blind_rotate(&out_ct, lwe_ct_in, acc_in, mode); 
    // 4) Sample Extract
    extract_lwe_from_rlwe(lwe_ct_out, &out_ct);
}


 
void rlwe_hom_acc_scheme::functional_bootstrap(long *lwe_ct_out, long *acc_in, long *lwe_ct_in, gadget_mul_mode mode, int t){  
    // 1) Key switch to \ZZ_Q^{n+1}
    long *lwe_c_N = lwe_gadget_par.lwe_par.init_ct();
    long *lwe_c = lwe_gadget_par.lwe_par.init_ct();
    lwe_to_lwe_key_switch(lwe_c_N, lwe_ct_in);
  
    // 2) Mod switch to \ZZ_2N^{n+1} Note that this should actually modulus switch to N not to 2N!
    lwe_gadget_par.lwe_par.switch_modulus(lwe_c_N, lwe_c_N, lwe_par_tiny); 

    // Shifting to have the ``payload'' withing (0, N) 
    // - otherwise for message 0, we could have negative noise and the phase could be also in (N, 2N) 
    lwe_c[0] = lwe_c_N[0] + round((double)lwe_par_tiny.Q/(2 *t)); 

    // TODO: I think I don't realy need this modulus_reduction_event kindof stuff - just add and then blind rotate lwe_c_N instead of copying everything to lwe_c.
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
    blind_rotate(&out_ct, lwe_c, acc_msb, signed_decomp);  

    // 4) Sample Extract (I can perform it oon the lwe_ct_out because it should have the right dimension)
    extract_lwe_from_rlwe(lwe_ct_out, &out_ct);  
  
    // And again:
    lwe_to_lwe_key_switch(lwe_c, lwe_ct_out); 
    
    // 2) Mod switch to \ZZ_2N^{n+1} Note that this should actually modulus switch to N not to 2N!
    lwe_gadget_par.lwe_par.switch_modulus(lwe_c, lwe_c, lwe_par);  

    // Add lwe_c + lwe_c_N (this should eliminate the msb in lwe_c_N)
    // Actually, adding (long)round((double)lwe_par_tiny.Q/2*t) isn't that important anymore, provided that I choose acc_in accordingly
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

    delete[] lwe_c_N;
    delete[] lwe_c;
}
  

// Computes the identity (should be used only with functional bootstrapping, for the negacyclic bootstrap this will output some nonsense)
long* rlwe_hom_acc_scheme::rot_identity(int t, long N, long Q){
    long delta_Q_t = (long)round((double)Q/(double)t); 
    long* acc = new long[N];  
    // The scale is right - in FB we rotate for phase [0, N)
    // And the message is also scaled with N/t
    double scale = (double)t/N;
    for(int i = 0; i < N; ++i){
        acc[N-i-1] = -delta_Q_t * round(scale * i) ;
        acc[N-i-1] = acc[N-i-1] % Q;
    }
    return acc;
}
  
/* Note: this doesn't realy compute the sign function. For zero for example it computes 1
*/
long* rlwe_hom_acc_scheme::rot_msb(int t, long N, long Q){
    long delta_Q_t = (long)round((double)Q/(double)t); 
    long* acc = new long[N]; 
    for(int i = 0; i < N; ++i){
        acc[i] =  utils::integer_mod_form(delta_Q_t * -1, Q); 
    } 
    return acc;
}


// Computes the a univariate polynomial (should be used only with functional bootstrapping, for the negacyclic bootstrap this will output some nonsense)
long* rlwe_hom_acc_scheme::rot_uni_poly(int* poly, int poly_size, int t, long N, long Q){
    //std::cout << "======= In rot_uni_poly" << std::endl;
    long delta_Q_t = (long)round((double)Q/(double)t);
    long delta_N_t = (long)round((double)N/(double)t);
    long* acc = new long[N];
    double scale = (double)t/N;
    long arg;
    for(int i = 0; i < N; ++i){
        arg = utils::integer_mod_form((long)round(((double)t * i /N)), t);  
        // Compute your function on arg
        if(arg == 0 && i > N/2){   
            // Compute  your function here
            arg = utils::eval_poly_mod(arg, poly, poly_size, t); 
            acc[N-i-1] = delta_Q_t * arg;
            acc[N-i-1] = acc[N-i-1] % Q; 
        }else{
            // Compute  your function here
            arg = utils::eval_poly_mod(arg, poly, poly_size, t);
            acc[N-i-1] = -delta_Q_t * arg;
            acc[N-i-1] = acc[N-i-1] % Q;

        }
        
    }
    return acc;
}



long* rlwe_hom_acc_scheme::rot_is_zero_of_poly(int* poly, int poly_size, int t, long N, long Q, int t_out){ 
    // I need a different sccale to encode the output of this bootstrap
    // That is, the polynomial is scaled with N/t, but the output (0 or 1) will be encoded with t_out
    long delta_Q_t = (long)round((double)Q/(double)t_out); 
    long* acc = new long[N];
    double scale = (double)t/N;
    long arg;
    for(int i = 0; i < N; ++i){
        arg = utils::integer_mod_form((long)round(((double)t * i /N)), t);  
        // Compute your function on arg
        if(arg == 0 && i > N/2){   
            // Compute  your function here
            arg = utils::eval_poly_mod(arg, poly, poly_size, t); 
            if(arg == 0){
                acc[N-i-1] =  0; 
            }else{
                acc[N-i-1] = delta_Q_t * 1; 
            }
            acc[N-i-1] = acc[N-i-1] % Q; 
        }else{ 
            // Compute  your function here
            arg = utils::eval_poly_mod(arg, poly, poly_size, t);

            if(arg == 0){
                acc[N-i-1] =  0; 
            }else{
                acc[N-i-1] = -delta_Q_t * 1;
            } 
            acc[N-i-1] = acc[N-i-1] % Q; 
        }
        
    }
    return acc;
}


// NOTE: I craft this polynomial to work with normal bootstrap assuming its message does not exceed t/2
// Meaning that I scale the input message with 
// NOTE: hte function returns 1 on input 0, and 0 otherwise
long* rlwe_hom_acc_scheme::rot_is_zero(int t, long N, long Q){
    //std::cout << "======= In rot_uni_poly" << std::endl;
    long delta_Q_t = (long)round((double)Q/(double)t);
    long delta_N_t = (long)round((double)N/(double)t);
    long* acc = new long[N];
    double scale = (double)t/N;
    long arg;
    for(int i = 0; i < N; ++i){
        arg = utils::integer_mod_form((long)round(((double)t * i /N)), t);  
        // Compute your function on arg
        if(arg == 0 && i > N/2){   
            // Compute  your function here 
            if(arg == 0){
                acc[N-i-1] = delta_Q_t * 1; 
            }else{
                acc[N-i-1] = 0; 
            }
            acc[N-i-1] = acc[N-i-1] % Q; 
        }else{ 
            // Compute  your function here 
            if(arg == 0){
                acc[N-i-1] = -delta_Q_t * 1;
            }else{
                acc[N-i-1] = 0; 
            } 
            acc[N-i-1] = acc[N-i-1] % Q; 
        } 
    }
    return acc;
}