#include "ntru.h" 
using namespace fhe_deck;

 
ntru_sk::~ntru_sk(){  
}
 
ntru_sk::ntru_sk(){}

ntru_sk::ntru_sk(ntru_param param){
    this->param = param; 
    key_gen();
}

ntru_sk::ntru_sk(ntru_param param, long *f, long *inv_f){
    this->param = param;  
    this->f = f; 
    this->inv_f = inv_f; 
}


ntru_sk::ntru_sk(ntru_param param, long *f, long *inv_f, ntru_param higher_mod_param){
    this->param = param;  
    this->f = f; 
    this->inv_f = inv_f; 
    this->modulus_switched = true;
    this->higher_mod_param = higher_mod_param;
} 


ntru_sk& ntru_sk::operator=(const ntru_sk other){
    this->param = other.param;  
    this->modulus_switched = other.modulus_switched;
    if(modulus_switched){
        this->higher_mod_param = other.higher_mod_param;
    }
    f = param.init_poly();
    inv_f = param.init_poly();
    Utils::cp(f, other.f, param.N);
    Utils::cp(inv_f, other.inv_f, param.N);
    return *this;
}

void ntru_sk::ternary_poly(NTL::ZZ_pX &temp_f,  ntru_param &param){ 
    NTL::ZZ_p coef; 
    coef.init(NTL::ZZ(param.Q)); 
    for(int i = 0; i < param.N; ++i){ 
        coef = param.rand.ternary(); 
        NTL::SetCoeff(temp_f, i, coef); 
    } 
}

void ntru_sk::gaussian_poly(NTL::ZZ_pX &temp_f, ntru_param &param){ 
    NTL::ZZ_p coef;
    coef.init(NTL::ZZ(param.Q));
    for(int i = 0; i < param.N; ++i){
        coef = param.rand.ternary();
        NTL::SetCoeff(temp_f, i, coef);
    } 
}



void ntru_sk::key_gen(){ 
    f = param.init_poly();
    inv_f = param.init_poly();
    ntru_sk::key_gen(f, inv_f, param);
}


void ntru_sk::key_gen(long *f, long *inv_f, ntru_param &param){ 
    int status = 1;   
    NTL::ZZ_pX temp_f;
    NTL::ZZ_pX temp_inv_f;
    do{ 
        ntru_sk::ternary_poly(temp_f, param); 
        status = NTL::InvModStatus(temp_inv_f, temp_f, Utils::get_ring_poly(param.ring, param.N, param.Q));  
    }while(status == 1); 
    Utils::set_array_from_polynomial(f,  param.N, temp_f); 
    Utils::set_array_from_polynomial(inv_f, param.N, temp_inv_f);    
    Utils::array_signed_form(f, f, param.N, param.Q);
}  


 

ntru_ct ntru_sk::encrypt(long* msg){    
   ntru_ct ct_ntru(param); 
   naive_encrypt(&ct_ntru, msg);
   return ct_ntru;
} 


void ntru_sk::kdm_scale_and_encrypt(ntru_ct *ct_out, long* msg, int t){
    long scale;
    if(modulus_switched){
        // We only use a diffrent scale in this case
        // The different algorithm and modulus will be handled by the encryption algorithm.
       scale = higher_mod_param.Q/t; 
    }else{
        scale = param.Q/t; 
    }
    long* msg_scaled = param.init_poly(); 
    Utils::mul_scalar(msg_scaled, msg, param.N, scale); 
    kdm_encrypt(ct_out, msg_scaled);

    delete[] msg_scaled; 
}

ntru_ct ntru_sk::kdm_scale_and_encrypt(long* msg, int t){ 
    ntru_ct ct_ntru(param);
    kdm_scale_and_encrypt(&ct_ntru, msg, t);
    return ct_ntru;
}


ntru_ct ntru_sk::kdm_encrypt(long* msg){   
   ntru_ct ct_ntru(param);
   kdm_encrypt(&ct_ntru, msg);
   return ct_ntru;
}
 
void ntru_sk::kdm_encrypt(ntru_ct *ct_out, long* msg){    
    long* kdm_msg = param.init_poly();  
    if(modulus_switched){   
        Utils::mul_mod(kdm_msg, msg, param.N, inv_f, param.N, higher_mod_param.N, higher_mod_param.Q, higher_mod_param.ring);  
        ntru_sk higher_mod_ntru(higher_mod_param, f, inv_f); 
        ntru_ct new_ct;
        new_ct = higher_mod_ntru.encrypt(kdm_msg);
        new_ct = new_ct.mod_switch(param); 
        if(param.engine->long_arithmetic == true){
            // TODO: Copy when long arithmetic (If that is even necessary..... Maybe its only needed for gadget mul? - Lets check)
        }else{
            Utils::cp(ct_out->c, new_ct.c, param.N);  
        } 
    }else{ 
        Utils::mul_mod(kdm_msg, msg, param.N, inv_f, param.N, param.N, param.Q, param.ring);  
        encrypt(ct_out, kdm_msg); 
    }  
    delete(kdm_msg);
}

 


/*
This encryption algorithm is deprecated!!!
The reason is that the fft induces errors already at this stage which are greatly amplified when gadget multiplying
Currently we are using naive encrypt via NTL.
In the future, I plan to use NTT (if paramteres satisfy the NTT conditions), 
and the naive encrypt for params that don't satisfy these conditions.
*/
void ntru_sk::encrypt(ntru_ct *ct_out, long* msg){    
    if(param.engine->long_arithmetic){  
        long* g = param.init_poly();
        param.rand.ternary_array(g, param.N);

        long* e = param.init_poly();
        param.rand.gaussian_array(e, param.N, 0, param.stddev);

        long* s = param.init_poly();
        param.rand.ternary_array(s, param.N);
        
        fftwl_complex *g_fft = new fftwl_complex[param.engine->plan_size]; 
        fftwl_complex *e_fft = new fftwl_complex[param.engine->plan_size]; 
        fftwl_complex *c_fft = new fftwl_complex[param.engine->plan_size];  
        fftwl_complex *s_fft = new fftwl_complex[param.engine->plan_size];  

        param.engine->to_eval_form_l(g_fft, g);  
        param.engine->to_eval_form_scale_l(e_fft, g);  
        param.engine->to_eval_form_l(s_fft, s); 
        
        // TODO: This has to be precomputed
        fftwl_complex *inv_f_fft = new fftwl_complex[param.engine->plan_size];  
        param.engine->to_eval_form_scale_l(inv_f_fft, inv_f); 
        // inv_f * g
        param.engine->mul_eval_form_l(c_fft, g_fft, inv_f_fft); 
        // c_fft * s
        //param.engine->mul_eval_form_l(c_fft, c_fft, s_fft);
    
        fftwl_complex *msg_fft = new fftwl_complex[param.engine->plan_size];    
        param.engine->to_eval_form_scale_l(msg_fft, msg);  
        // inv_f * g + msg
        param.engine->add_eval_form_l(c_fft, c_fft, msg_fft);
        param.engine->add_eval_form_l(c_fft, c_fft, e_fft);

        // To coef form and mod reduce
        long* result = new long[param.engine->plan_size];
        param.engine->to_coef_form_l(result, c_fft);  
        Utils::mod_reduce(ct_out->c, result, param.Q, param.N);  
        delete(g);
        delete(g_fft);
        delete(e);
        delete(e_fft);
        delete(s); 
        delete(s_fft); 
        delete(c_fft);
        delete(inv_f_fft); 
        delete(msg_fft); 
        delete(result); 
    }else{ 
        long* g = param.init_poly();
        param.rand.ternary_array(g, param.N); 
        long* e = param.init_poly();
        param.rand.gaussian_array(e, param.N, 0, param.stddev);  
        
        fftw_complex *g_fft = new fftw_complex[param.engine->plan_size]; 
        fftw_complex *e_fft = new fftw_complex[param.engine->plan_size];  
        fftw_complex *c_fft = new fftw_complex[param.engine->plan_size]; 
        //fftw_complex *s_fft = new fftw_complex[param.engine->plan_size];   
         
        param.engine->to_eval_form(g_fft, g); 
        param.engine->to_eval_form_scale(e_fft, e);   
        //param.engine->to_eval_form(s_fft, s); 
         
        fftw_complex *inv_f_fft = new fftw_complex[param.engine->plan_size]; 
        // Remember that when you don't scale the ciphertext, then you may end up with rubish 
        param.engine->to_eval_form_scale(inv_f_fft, inv_f);  
        // inv_f * g
        param.engine->mul_eval_form(c_fft, g_fft, inv_f_fft); 
        // c_fft * s
        //param.engine->mul_eval_form(c_fft, c_fft, s_fft); 
    
        fftw_complex *msg_fft = new fftw_complex[param.engine->plan_size];    
        param.engine->to_eval_form_scale(msg_fft, msg);  
        // inv_f * g + msg
        param.engine->add_eval_form(c_fft, c_fft, msg_fft);
        param.engine->add_eval_form(c_fft, c_fft, e_fft);

        // To coef form and mod reduce
        long* result = new long[param.engine->plan_size];
        param.engine->to_coef_form(result, c_fft);  
        Utils::mod_reduce(ct_out->c, result, param.Q, param.N);  

         
        delete(c_fft); 
        delete(g); 
        delete(g_fft); 
        delete(e); 
        delete(e_fft);
        //delete(s); 
        //delete(s_fft); 
        delete(inv_f_fft);  
        delete(msg_fft);  
        delete(result);  
    }
} 





void ntru_sk::naive_encrypt(ntru_ct *ct_out, long* msg){     
        long* g = param.init_poly();
        param.rand.ternary_array(g, param.N); 
        long* e = param.init_poly();
        param.rand.gaussian_array(e, param.N, 0, param.stddev); 
        long* s = param.init_poly();
        param.rand.ternary_array(s, param.N); 
        Utils::mul_mod(ct_out->c, inv_f, param.N, g, param.N, param.N, param.Q, param.ring);
        Utils::mul_mod(ct_out->c, ct_out->c, param.N, s, param.N, param.N, param.Q, param.ring);
        Utils::add_mod(ct_out->c, ct_out->c, param.N, e, param.N, param.N, param.Q);
        Utils::add_mod(ct_out->c, ct_out->c, param.N, msg, param.N, param.N, param.Q); 
        delete[] g;
        delete[] e;
        delete[] s;
} 

// Only computes ct * f
void ntru_sk::phase(long *phase, ntru_ct *ct){
    NTL::ZZ_pX ct_poly;
    Utils::set_polynomial_from_array(ct_poly, ct->c, param.N, param.Q); 
    NTL::ZZ_pX f_poly;
    Utils::set_polynomial_from_array(f_poly, f, param.N, param.Q); 
    NTL::ZZ_pX phase_poly = NTL::MulMod(ct_poly, f_poly, Utils::get_ring_poly(param.ring, param.N, param.Q));  
    Utils::set_array_from_polynomial(phase, param.N, phase_poly); 
    Utils::array_signed_form(phase, phase, param.N, param.Q);
}


void ntru_sk::error(long *err, ntru_ct *ct, long* msg){
    phase(err, ct); 
    for(int i = 0; i < param.N; ++i){
            err[i] = (err[i] - msg[i]) % param.Q;
      }
      Utils::array_signed_form(err, err, param.N, param.Q);
}
 
long* ntru_sk::decrypt(ntru_ct *ct, int t){  
   long *out_msg = param.init_poly();
   decrypt(out_msg, ct, t);
   return out_msg;
}


void ntru_sk::decrypt(long* out, ntru_ct *ct, int t){  
    long* phase = param.init_poly(); 
    ntru_sk::phase(phase, ct);  
    Utils::array_rounding(out, phase, param.N, param.Q, t);
    delete(phase); 
}

 

/*
Eventually should decrypt the 0 coef, but for now I will focus only on the first coefficent. 
*/
long ntru_sk::decrypt_coef(ntru_ct *ct, int t){
    long ret = ct->c[0] * f[0];
    for(int i=1; i < param.N; ++i){
        ret -= ct->c[i] * f[param.N-i];
        ret = ret % param.Q;
    }  
    ret =  Utils::integer_rounding(ret, param.Q, t); 
    return Utils::integer_signed_form(ret, param.Q);
}

 

ntru_sk ntru_sk::mod_switch(long new_modulus){ 
    ntru_param new_param = param.mod_switch(new_modulus); 
    return ntru_sk(new_param, f, inv_f, param);  
} 

  


gadget_ntru::gadget_ntru(){}


gadget_ntru::gadget_ntru(ntru_gadget_param gadget_param, ntru_sk ntru){
    this->gadget_param = gadget_param;
    this->ntru = ntru;
}


ntru_gadget_ct gadget_ntru::gadget_encrypt(long* msg){  
   ntru_gadget_ct out = ntru_gadget_ct(gadget_param.param, gadget_param.basis, gadget_param.arithmetic);    
   gadget_encrypt(out.gadget_ct, msg);  
   out.to_eval();   
   return out; 
}



void gadget_ntru::gadget_encrypt(long** gadget_ct, long* msg){ 
   for(int i = 0; i < gadget_param.ell; ++i){
      gadget_ct[i] = gadget_param.param.init_poly();
   }
   long* msg_cpy = gadget_param.param.init_zero_poly();
   for(int i = 0; i < gadget_param.param.N; ++i){
       msg_cpy[i] = msg[i];
   } 
    
   ntru_ct temp_ct = ntru.encrypt(msg_cpy);
    //Encrypt msg * 1 
    Utils::cp(gadget_ct[0], temp_ct.c, gadget_param.param.N); 
    for(int i = 1; i < gadget_param.ell; ++i){
        // Multiply msg by basis
        for(int j=0; j < gadget_param.param.N; ++j){
            msg_cpy[j] = (msg_cpy[j] * gadget_param.basis) % gadget_param.param.Q;
        } 
        // Encrypt msg * basis**i 
        temp_ct = ntru.encrypt(msg_cpy);
        Utils::cp(gadget_ct[i], temp_ct.c, gadget_param.param.N); 
    }
    delete[] msg_cpy;
}

 
