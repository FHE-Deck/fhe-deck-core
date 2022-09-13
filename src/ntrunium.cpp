 
#include "../include/ntrunium.h"


ntrunium::~ntrunium(){ 
    for(int i = 0; i < ntru_g_par.param.N; ++i){ 
        for(int j = 0; j < lwe_g_par.ell; ++j){ 
            delete[] ksk[i][j];  
        }
        delete[] ksk[i];
    }
    delete[] ksk;
    delete[] bk_gadget;
    delete[] u;
} 

ntrunium::ntrunium(){ 
} 


ntrunium::ntrunium(ntru_gadget_param ntru_g_par, ntru_param ntru_par, lwe_gadget_param lwe_g_par, lwe_param lwe_par,  long ***ksk, ntru_gadget_ct* bk){ 
    this->ntru_g_par = ntru_g_par;
    this->ntru_par = ntru_par;
    this->lwe_g_par = lwe_g_par;
    this-> lwe_par = lwe_par; 
    // Init the params of the LWE secret key encoding
    this->key_d = lwe_par.key_d;
    if(key_d == binary){  
        init_binary_key(); 
    }else{ 
        init_ternary_key();
    }
    // NOTE: We have lwe_par_tiny lwe_par.Q/2, because in the functional_bootstrap we use the negacyclic ring
    lwe_par_tiny = lwe_param(lwe_par.n, lwe_par.Q/2, lwe_par.key_d, lwe_par.stddev);
    // Set the key switching and blind rotation keys
    this->ksk = ksk; 
    this->bk_gadget = bk;      
}
 

void ntrunium::init_binary_key(){
        sizeof_u = 1;
        this->u = new long[sizeof_u];
        u[0] = 1;
        sizeof_ext_s = lwe_par.n;
}

void ntrunium::init_ternary_key(){
        sizeof_u = 2;
        this->u = new long[sizeof_u];
        u[0] = -1;
        u[1] = 1;
        sizeof_ext_s = 2*lwe_par.n; 
}



void ntrunium::ntru_to_lwe_key_switch(long *lwe_ct, ntru_ct *ct){ 
    lwe_g_par.gadget_mul_no_mod_reduction(lwe_ct, ksk[0], ct->c[0]);  
    long *temp_lwe_ct = lwe_g_par.lwe_par.init_ct(); 
    for(int i=1; i < ntru_g_par.param.N; ++i){ 
        lwe_g_par.gadget_mul_no_mod_reduction(temp_lwe_ct, ksk[i], ct->c[i]); 
        lwe_g_par.lwe_par.add_no_mod_reduction(lwe_ct, lwe_ct, temp_lwe_ct); 
    } 
    // Modulus reduction only at the very end
    for(int i = 0; i < lwe_g_par.lwe_par.n+1; ++i){
        lwe_ct[i] = lwe_ct[i] % lwe_g_par.lwe_par.Q;
    } 
    delete(temp_lwe_ct);
}

    

void ntrunium::ntru_to_lwe_key_switch_delete(){
    for(int i = 0; i < ntru_g_par.param.N; ++i){ 
        for(int j = 0; j < lwe_g_par.ell; ++j){ 
            delete(ksk[i][j]);  
        }
        delete(ksk[i]);
    }
    delete(ksk);
}


ntru_ct ntrunium::blind_rotate(ntru_ct *acc_in, long *lwe_ct){    
    ntru_ct temp_acc(ntru_g_par.param);
    ntru_ct acc_out(ntru_g_par.param, ntru_g_par.param.init_zero_poly());  
    utils::negacyclic_rotate_poly(acc_out.c, acc_in->c, ntru_par.engine->N, lwe_ct[0]);  
    if(key_d==binary){   
        for(int i = 0; i < lwe_par.n; ++i){  
            // temp_acc <- rotate(acc, lwe_ct[i+1])  
            utils::negacyclic_rotate_poly(temp_acc.c, acc_out.c, ntru_par.engine->N, lwe_ct[i+1]);
            for(int j = 0; j < ntru_g_par.param.N; ++j){
                // temp_acc -= acc_out 
                temp_acc.c[j] = temp_acc.c[j] - acc_out.c[j];
                // temp_acc %= Q    
                temp_acc.c[j] = temp_acc.c[j] % ntru_g_par.param.Q;
            }    
            // temp_acc *= bk[i] 
            bk_gadget[i].gadget_mul(&temp_acc, &temp_acc);
            // temp_acc += acc
            for(int j = 0; j < ntru_g_par.param.N; ++j){
                temp_acc.c[j] = temp_acc.c[j] + acc_out.c[j]; 
                // Another modulus reduction 
                acc_out.c[j] = temp_acc.c[j] % ntru_g_par.param.Q;
            } 
        }
    } 
    else{  
        // Rotatate back (multipliation by X^{-ct[i+1]}) and mul with bk_eval[i]
        long back_rotations;
         for(int i = 0; i < lwe_par.n; ++i){ 
            // temp_acc <- rotate(acc, -lwe_ct[i+1]) 
            back_rotations = utils::integer_mod_form(-lwe_ct[i+1], lwe_par.Q);  
            utils::negacyclic_rotate_poly(temp_acc.c, acc_out.c, ntru_par.engine->N, back_rotations);
            for(int j = 0; j < ntru_g_par.param.N; ++j){
                // temp_acc -= acc_out 
                temp_acc.c[j] = temp_acc.c[j] - acc_out.c[j];
                // temp_acc %= Q    
                temp_acc.c[j] = temp_acc.c[j] % ntru_g_par.param.Q;
            }    
            // temp_acc *= bk[i] 
            bk_gadget[i].gadget_mul(&temp_acc, &temp_acc);
 
            // temp_acc += acc
            for(int j = 0; j < ntru_g_par.param.N; ++j){
                temp_acc.c[j] = temp_acc.c[j] + acc_out.c[j]; 
                // Another modulus reduction 
                acc_out.c[j] = temp_acc.c[j] % ntru_g_par.param.Q;
            } 
        } 
        // Rotatate forward (multipliation by X^{ct[i+1]}) and mul with bk_eval[lwe_par.n+i]
         for(int i = 0; i < lwe_par.n; ++i){ 
            // temp_acc <- rotate(acc, lwe_ct[i+1])  
            utils::negacyclic_rotate_poly(temp_acc.c, acc_out.c, ntru_par.engine->N, lwe_ct[i+1]);
            for(int j = 0; j < ntru_g_par.param.N; ++j){
                // temp_acc -= acc_out 
                temp_acc.c[j] = temp_acc.c[j] - acc_out.c[j];
                // temp_acc %= Q    
                temp_acc.c[j] = temp_acc.c[j] % ntru_g_par.param.Q;
            }   
            // temp_acc *= bk[i] 
            bk_gadget[lwe_par.n+i].gadget_mul(&temp_acc, &temp_acc);

            // temp_acc += acc
            for(int j = 0; j < ntru_g_par.param.N; ++j){
                temp_acc.c[j] = temp_acc.c[j] + acc_out.c[j]; 
                // Another modulus reduction  
                acc_out.c[j] = temp_acc.c[j] % ntru_g_par.param.Q;
            } 
        }
    }     
    return acc_out;
}
  

  
ntru_ct ntrunium::bootstrap(ntru_ct *acc_in, ntru_ct *ct, int t){ 
    // Key Switch (extract the dth coefficient) 
    long* lwe_ct = lwe_g_par.lwe_par.init_ct();
    ntru_to_lwe_key_switch(lwe_ct, ct); 
    // Modulus switch lwe_ct to ring size. 
    long* lwe_ct_small = lwe_g_par.lwe_par.init_ct(); 
    // Here we are already modulus switching to Z_2N
    lwe_g_par.lwe_par.switch_modulus(lwe_ct_small, lwe_ct, lwe_par);  
    lwe_ct_small[0] = lwe_ct_small[0] + round((double)lwe_par.Q/(2 * t)); 
    lwe_ct_small[0] %= lwe_par.Q;
    // Blind rotate  
    ntru_ct acc_rotated = blind_rotate(acc_in, lwe_ct_small);
    // Modulus switch to the smaller modulus NTRU ciphertext  
    delete[] lwe_ct;
    delete[] lwe_ct_small; 
    return acc_rotated.mod_switch(ntru_par);
}
 
 
ntru_ct ntrunium::functional_bootstrap(ntru_ct *acc_in, ntru_ct* acc_msb, ntru_ct *ct, int t){ 
    // Key Switch (extract the dth coefficient) 
    long* lwe_ct = lwe_g_par.lwe_par.init_ct();
    long *lwe_c_N = lwe_g_par.lwe_par.init_ct();
    ntru_to_lwe_key_switch(lwe_c_N, ct); 

    // Modulus switch lwe_ct to ring size.  
    // Here we are already modulus switching to Z_N
    lwe_g_par.lwe_par.switch_modulus(lwe_c_N, lwe_c_N, lwe_par_tiny);
  
    // Shifting to have the ``payload'' withing (0, N) 
    // - otherwise for message 0, we could have negative noise and the phase could be also in (N, 2N) 
    lwe_ct[0] = lwe_c_N[0] + round((double)lwe_par_tiny.Q/(2 * t));   

    // TODO: I think I don't realy need this modulus_reduction_event kindof stuff 
    // - just add and then blind rotate lwe_c_N instead of copying everything to lwe_c.
    // In case modulus reduction happens here, we need to flip the extracted MSB
    bool modulus_reduction_event = false;
    if(lwe_ct[0] >= lwe_par_tiny.Q){   
        lwe_ct[0] = lwe_ct[0] % lwe_par_tiny.Q; 
        modulus_reduction_event = true;
    }
    // Copy  
    for(int i = 1; i < lwe_par_tiny.n+1; ++i){
        lwe_ct[i] = lwe_c_N[i];
    }     
  

    // Blind rotate   
    ntru_ct acc_rotated = blind_rotate(acc_msb, lwe_ct); 
    acc_rotated = acc_rotated.mod_switch(ntru_par);

    ntru_to_lwe_key_switch(lwe_ct, &acc_rotated); 
    lwe_g_par.lwe_par.switch_modulus(lwe_ct, lwe_ct, lwe_par);  
 

    // Add lwe_c + lwe_c_N (this should eliminate the msb in lwe_c_N)
    // Actually, adding (long)round((double)lwe_par_tiny.Q/2*t) isn't that important anymore, 
    // provided that I choose acc_in accordingly
    for(int i = 0; i < lwe_par.n+1; ++i){
        lwe_ct[i] = (lwe_ct[i] + lwe_c_N[i]) % lwe_par.Q;
    }  
    if(modulus_reduction_event){ 
        lwe_ct[0] = utils::integer_mod_form(lwe_ct[0] - (long)round((double)(3 * lwe_par.Q)/4), lwe_par.Q);
    }else{
        lwe_ct[0] = utils::integer_mod_form(lwe_ct[0] - (long)round((double)lwe_par.Q/4), lwe_par.Q);
    } 
    // lwe_c should have its phase within (0, N)  
    // 3) Blind rotate
    acc_rotated = blind_rotate(acc_in, lwe_ct);
 
    delete[] lwe_ct;
    delete[] lwe_c_N; 
    // Modulus switch to the smaller modulus NTRU ciphertext   
    return acc_rotated.mod_switch(ntru_par);
}

  