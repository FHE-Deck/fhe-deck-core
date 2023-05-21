
#include "../include/rlwe.h"
#include "../include/utils.h"


rlwe_sk::rlwe_sk(){}

   
rlwe_sk::rlwe_sk(rlwe_param param, polynomial_arithmetic arithmetic){
    this->param = param;
    s = new long[param.N];
    this->arithmetic = arithmetic;
    if(param.key_type == uniform){
        param.rand.uniform_array(s, param.N, param.Q);
    }else if(param.key_type == ternary){
        param.rand.ternary_array(s, param.N);
    }else if(param.key_type == ternary){
        param.rand.binary_array(s, param.N);
    } 
    set_arithmetic_specific_variables(); 
}
 
rlwe_sk::rlwe_sk(rlwe_param param, long *s, polynomial_arithmetic arithmetic){
    this->param = param;
    this->s = s;
    this->arithmetic = arithmetic; 
    set_arithmetic_specific_variables(); 
}
 
void rlwe_sk::set_arithmetic_specific_variables(){
    if(arithmetic == double_fft){
        eval_s = new fftw_complex[param.engine->plan_size]; 
        param.engine->to_eval_form_scale(eval_s, s, 2.0);
    }else if(arithmetic == hexl_ntt){ 
        ntt = intel::hexl::NTT(param.N, param.Q);
        eval_s_ntt = param.init_poly(); 
        long* s_mod_form = new long[param.N];
        utils::array_mod_form(s_mod_form, s, param.N, param.Q);
        ntt.ComputeForward((uint64_t*) eval_s_ntt, (uint64_t*) s_mod_form, 1, 1); 
        delete[] s_mod_form;
    }else if(arithmetic == ntl){
        // Do nothing
    }else{
        std::cout << "Arithmetic not Supported" << std::endl;
    }
}

rlwe_ct rlwe_sk::encrypt(long* m){ 
    rlwe_ct out(&param);  
    param.rand.uniform_array(out.a, param.N, param.Q); 
    long* e = new long[param.N];
    param.rand.gaussian_array(e, param.N, 0.0, param.stddev);    
    if(arithmetic == double_fft){ 
        fftw_complex *eval_b = new fftw_complex[param.engine->plan_size];  
        param.engine->to_eval_form(eval_b, out.a); 
        param.engine->mul_eval_form(eval_b, eval_s, eval_b); 
        param.engine->to_coef_form(out.b, eval_b);    
        for(int i = 0; i < param.N; ++i){
            out.b[i] = utils::integer_mod_form(out.b[i] + e[i] + m[i], param.Q);
        } 
        delete[] e;
        delete[] eval_b;
    }else if(arithmetic == hexl_ntt){ 
        long* eval_b_ntt = param.init_poly();  
        ntt.ComputeForward((uint64_t*) eval_b_ntt, (uint64_t*) out.a, 1, 1); 
        intel::hexl::EltwiseMultMod((uint64_t*) eval_b_ntt, (uint64_t*) eval_b_ntt, (uint64_t*) eval_s_ntt, param.N, param.Q, 1);
        ntt.ComputeInverse((uint64_t*) out.b, (uint64_t*)  eval_b_ntt, 1, 1); 

        utils::add_mod(out.b, out.b, param.N, e, param.N, param.N, param.Q);
        utils::add_mod(out.b, out.b, param.N, m, param.N, param.N, param.Q); 
        delete[] eval_b_ntt;
    }else if(arithmetic == ntl){  
        utils::mul_mod(out.b, out.a, param.N, s, param.N, param.N, param.Q, negacyclic);
        utils::add_mod(out.b, out.b, param.N, e, param.N, param.N, param.Q);
        utils::add_mod(out.b, out.b, param.N, m, param.N, param.N, param.Q);
    }else{
        std::cout << "Arithmetic not Supported" << std::endl;
    }
 
    return out;
}

rlwe_ct rlwe_sk::scale_and_encrypt(long* m, int t){ 
    double scale = (double)param.Q/t;
    long* m_scaled = new long[param.N];
    for(int i = 0; i < param.N; ++i){
        m_scaled[i] = (long)round((double)m[i]*scale);
    }
    rlwe_ct out = encrypt(m_scaled);
    delete[] m_scaled;
    return out;
}


void rlwe_sk::phase(long *phase, const rlwe_ct *ct){  
    if(arithmetic == double_fft){   
        fftw_complex *eval_a = new fftw_complex[param.engine->plan_size]; 
        param.engine->to_eval_form(eval_a, ct->a);
        param.engine->mul_eval_form(eval_a, eval_s, eval_a);
        long *as = new long[param.N];
        param.engine->to_coef_form(as, eval_a);
        for(int i = 0; i < param.N; ++i){
            phase[i] = (ct->b[i] - as[i]) % param.Q;
        }  
        delete[] eval_a;
        delete[] as; 
    }else if(arithmetic == hexl_ntt){    
        long* eval_a_ntt = param.init_poly(); 
        long* a_mod_form = param.init_poly();
        utils::array_mod_form(a_mod_form, ct->a, param.N, param.Q);
        ntt.ComputeForward((uint64_t*) eval_a_ntt, (uint64_t*) a_mod_form, 1, 1);   
        intel::hexl::EltwiseMultMod((uint64_t*) eval_a_ntt, (uint64_t*) eval_a_ntt, (uint64_t*) eval_s_ntt, param.N, param.Q, 1);
        ntt.ComputeInverse((uint64_t*) eval_a_ntt, (uint64_t*)  eval_a_ntt, 1, 1);  
        utils::sub_mod(phase, ct->b, param.N, eval_a_ntt, param.N, param.N, param.Q); 
        delete[] eval_a_ntt;   
        delete[] a_mod_form;
    }else if(arithmetic == ntl){  
        utils::mul_mod(phase, ct->a, param.N, s, param.N, param.N, param.Q, negacyclic);
        utils::sub_mod(phase, ct->b, param.N, phase, param.N, param.N, param.Q);
    }else{
        std::cout << "Arithmetic not Supported" << std::endl;
    } 
}

// Uses SK
long* rlwe_sk::decrypt(const rlwe_ct *ct, int t){
    long *out = new long[param.N];
    decrypt(out, ct, t);  
    return out;
}

// Uses SK
void rlwe_sk::decrypt(long *out, const rlwe_ct *ct, int t){ 
    long *phase = new long[param.N]; 
    this->phase(phase, ct); 
    utils::array_rounding(out, phase, param.N, param.Q, t);
    //delete phase;
}



gadget_rlwe_sk::gadget_rlwe_sk(){}



gadget_rlwe_sk::gadget_rlwe_sk(const gadget_rlwe_sk &other){
    std::cout << "Copy constructor for gadget_rlwe_sk" << std::endl;
}

gadget_rlwe_sk::gadget_rlwe_sk(rlwe_gadget_param gadget_param, rlwe_sk sk){
    this->gadget_param = gadget_param;
    this->sk = sk;
}

rlwe_gadget_ct gadget_rlwe_sk::gadget_encrypt(long* msg){ 
    rlwe_gadget_ct out(gadget_param);  
   long* msg_cpy = gadget_param.param.init_zero_poly();
   for(int i = 0; i < gadget_param.param.N; ++i){
       msg_cpy[i] = msg[i];
   }  
   long* msg_x_sk = gadget_param.param.init_poly();
    utils::mul_mod(msg_x_sk, msg, gadget_param.param.N, sk.s, gadget_param.param.N, gadget_param.param.N, gadget_param.param.Q, gadget_param.param.ring); 
    utils::neg_mod(msg_x_sk, msg_x_sk, gadget_param.param.N, gadget_param.param.Q); 
      
    out.gadget_ct[0] = sk.encrypt(msg_cpy); 
    for(int i = 1; i < gadget_param.ell_max; ++i){
        // Multiply msg by basis
        for(int j=0; j < gadget_param.param.N; ++j){
            msg_cpy[j] = (msg_cpy[j] * gadget_param.basis) % gadget_param.param.Q;
        } 
        // Encrypt msg * basis**i 
        out.gadget_ct[i] = sk.encrypt(msg_cpy); 
    } 
    // Encryption of - msg * sk * basis**i 
    out.gadget_ct_sk[0]  = sk.encrypt(msg_x_sk); 
    for(int i = 1; i < gadget_param.ell_max; ++i){
        // Multiply msg by basis
        for(int j=0; j < gadget_param.param.N; ++j){
            msg_x_sk[j] = (msg_x_sk[j] * gadget_param.basis) % gadget_param.param.Q;
        } 
        // Encrypt - msg * sk * basis**i 
 
        out.gadget_ct_sk[i] = sk.encrypt(msg_x_sk);  
    } 
    delete(msg_cpy);
    delete(msg_x_sk); 
    out.to_eval(); 
    return out;
}
 