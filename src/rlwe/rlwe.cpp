#include "rlwe.h"
#include "utils.h"

using namespace fhe_deck;



RLWESK::~RLWESK(){
    if(is_init){
        delete[] s; 
    }
    if(is_fft_init){ 
        fftw_free(eval_s);
    }
    if(is_ntt_init){ 
        delete[] eval_s_ntt;
    }
}
  
RLWESK::RLWESK(std::shared_ptr<RLWEParam> param, PolynomialArithmetic sk_arithmetic){
    this->param = param;
    s = new long[param->N];
    this->sk_arithmetic = sk_arithmetic;

    if(param->key_type == uniform){
        rand.uniform_array(s, param->N, param->Q);
    }else if(param->key_type == ternary){
        rand.ternary_array(s, param->N);
    }else if(param->key_type == ternary){
        rand.binary_array(s, param->N);
    } 
    set_arithmetic_specific_variables(); 
    this->is_init = true;
}
 
RLWESK::RLWESK(std::shared_ptr<RLWEParam> param, long *s, PolynomialArithmetic sk_arithmetic){
    this->param = param;
    this->s = s;
    this->sk_arithmetic = sk_arithmetic; 
    set_arithmetic_specific_variables(); 
    this->is_init = true;
}


RLWESK::RLWESK(const RLWESK &other){
    this->param = other.param;
    this->s = new long[param->N];
    this->sk_arithmetic = other.sk_arithmetic;
    for(int i = 0; i < param->N; ++i){
        this->s[i] = other.s[i];
    }
    set_arithmetic_specific_variables(); 
    this->is_init = true;
}

RLWESK& RLWESK::operator=(const RLWESK other){  
    if (this == &other)
    {
        return *this;
    }   
    if(this->is_init && (param->N == other.param->N)){  
        this->param = other.param;
        for(int i = 0; i < this->param->N; ++i){
            s[i] = other.s[i];
        }
        this->sk_arithmetic = other.sk_arithmetic;
        set_arithmetic_specific_variables(); 
    }else if(this->is_init == false){ 
        this->param = other.param;
        this->s = new long[param->N];
        for(int i = 0; i < this->param->N; ++i){
            s[i] = other.s[i];
        }
        this->sk_arithmetic = other.sk_arithmetic;
        set_arithmetic_specific_variables(); 
        this->is_init = true;
    }else{ 
        throw std::logic_error("Wrong case in rlwe_sk::operator=");
    } 
    return *this;
}
 
void RLWESK::set_arithmetic_specific_variables(){ 
    if(sk_arithmetic == double_fft){
        engine = FFTPlan(param->ring, param->N, false);  
        eval_s = new fftw_complex[engine.plan_size]; 
        engine.to_eval_form_scale(eval_s, s, 2.0);
        this->is_fft_init = true;
    }else if(sk_arithmetic == hexl_ntt){ 
        ntt = intel::hexl::NTT(param->N, param->Q);
        eval_s_ntt = param->init_poly(); 
        long* s_mod_form = new long[param->N];
        Utils::array_mod_form(s_mod_form, s, param->N, param->Q);
        ntt.ComputeForward((uint64_t*) eval_s_ntt, (uint64_t*) s_mod_form, 1, 1); 
        delete[] s_mod_form;
        this->is_ntt_init = true; 
    }else if(sk_arithmetic == ntl){
        // Do nothing
    }else{
        throw std::logic_error("Non existent polynomial multiplication engine!"); 
    }
}

RLWECT RLWESK::encrypt(long* m){  
    RLWECT out(param);  
    rand.uniform_array(out.a, param->N, param->Q); 
    long* e = new long[param->N];
    rand.gaussian_array(e, param->N, 0.0, param->stddev);    
    if(sk_arithmetic == double_fft){ 
        fftw_complex *eval_b = new fftw_complex[engine.plan_size];  
        engine.to_eval_form(eval_b, out.a); 
        engine.mul_eval_form(eval_b, eval_s, eval_b); 
        engine.to_coef_form(out.b, eval_b);    
        for(int i = 0; i < param->N; ++i){
            out.b[i] = Utils::integer_mod_form(out.b[i] + e[i] + m[i], param->Q);
        } 
        delete[] eval_b;
    }else if(sk_arithmetic == hexl_ntt){ 
        long* eval_b_ntt = param->init_poly();  
        ntt.ComputeForward((uint64_t*) eval_b_ntt, (uint64_t*) out.a, 1, 1); 
        intel::hexl::EltwiseMultMod((uint64_t*) eval_b_ntt, (uint64_t*) eval_b_ntt, (uint64_t*) eval_s_ntt, param->N, param->Q, 1);
        ntt.ComputeInverse((uint64_t*) out.b, (uint64_t*)  eval_b_ntt, 1, 1); 

        Utils::add_mod(out.b, out.b, param->N, e, param->N, param->N, param->Q);
        Utils::add_mod(out.b, out.b, param->N, m, param->N, param->N, param->Q); 
        delete[] eval_b_ntt;
    }else if(sk_arithmetic == ntl){  
        Utils::mul_mod(out.b, out.a, param->N, s, param->N, param->N, param->Q, negacyclic);
        Utils::add_mod(out.b, out.b, param->N, e, param->N, param->N, param->Q);
        Utils::add_mod(out.b, out.b, param->N, m, param->N, param->N, param->Q);
    }else{
        throw std::logic_error("Non existent polynomial multiplication engine!"); 
    }
    delete[] e; 
    return out;
}

RLWECT RLWESK::scale_and_encrypt(long* m, int t){ 
    double scale = (double)param->Q/t;
    long* m_scaled = new long[param->N];
    for(int i = 0; i < param->N; ++i){
        m_scaled[i] = (long)round((double)m[i]*scale);
    }
    RLWECT out = encrypt(m_scaled);
    delete[] m_scaled;
    return out;
}


void RLWESK::phase(long *phase, const RLWECT *ct){  
    if(sk_arithmetic == double_fft){   
        fftw_complex *eval_a = new fftw_complex[engine.plan_size]; 
        engine.to_eval_form(eval_a, ct->a);
        engine.mul_eval_form(eval_a, eval_s, eval_a);
        long *as = new long[param->N];
        engine.to_coef_form(as, eval_a);
        for(int i = 0; i < param->N; ++i){
            phase[i] = (ct->b[i] - as[i]) % param->Q;
        }  
        delete[] eval_a;
        delete[] as; 
    }else if(sk_arithmetic == hexl_ntt){    
        long* eval_a_ntt = param->init_poly(); 
        long* a_mod_form = param->init_poly();
        Utils::array_mod_form(a_mod_form, ct->a, param->N, param->Q);
        ntt.ComputeForward((uint64_t*) eval_a_ntt, (uint64_t*) a_mod_form, 1, 1);   
        intel::hexl::EltwiseMultMod((uint64_t*) eval_a_ntt, (uint64_t*) eval_a_ntt, (uint64_t*) eval_s_ntt, param->N, param->Q, 1);
        ntt.ComputeInverse((uint64_t*) eval_a_ntt, (uint64_t*)  eval_a_ntt, 1, 1);  
        Utils::sub_mod(phase, ct->b, param->N, eval_a_ntt, param->N, param->N, param->Q); 
        delete[] eval_a_ntt;   
        delete[] a_mod_form;
    }else if(sk_arithmetic == ntl){  
        Utils::mul_mod(phase, ct->a, param->N, s, param->N, param->N, param->Q, negacyclic);
        Utils::sub_mod(phase, ct->b, param->N, phase, param->N, param->N, param->Q);
    }else{
        throw std::logic_error("Non existent polynomial multiplication engine!"); 
    } 
}

// Uses SK
long* RLWESK::decrypt(const RLWECT *ct, int t){
    long *out = new long[param->N];
    decrypt(out, ct, t);  
    return out;
}

// Uses SK
void RLWESK::decrypt(long *out, const RLWECT *ct, int t){ 
    long *phase = new long[param->N]; 
    this->phase(phase, ct); 
    Utils::array_rounding(out, phase, param->N, param->Q, t);
    delete[] phase;
}

 


RLWEGadgetSK::RLWEGadgetSK(const RLWEGadgetSK &other){ 
    this->gadget_param = other.gadget_param; 
    this->sk = other.sk; 
}

RLWEGadgetSK::RLWEGadgetSK(RLWEGadgetParam gadget_param, RLWESK sk){ 
    this->gadget_param = gadget_param; 
    this->sk = sk; 
}

RLWEGadgetSK& RLWEGadgetSK::operator=(const RLWEGadgetSK other){  
    this->gadget_param = other.gadget_param;  
    this->sk = other.sk;  
    return *this;
}


RLWEGadgetCT RLWEGadgetSK::gadget_encrypt(long* msg){   
    RLWEGadgetCT out(gadget_param);  
   long* msg_cpy = gadget_param.rlwe_param->init_zero_poly();
   for(int i = 0; i < gadget_param.rlwe_param->N; ++i){
       msg_cpy[i] = msg[i];
   }  
   long* msg_x_sk = gadget_param.rlwe_param->init_poly();
    Utils::mul_mod(msg_x_sk, msg, gadget_param.rlwe_param->N, sk.s, gadget_param.rlwe_param->N, gadget_param.rlwe_param->N, gadget_param.rlwe_param->Q, gadget_param.rlwe_param->ring); 
    Utils::neg_mod(msg_x_sk, msg_x_sk, gadget_param.rlwe_param->N, gadget_param.rlwe_param->Q); 
      
    out.gadget_ct[0] = sk.encrypt(msg_cpy); 
    for(int i = 1; i < gadget_param.ell_max; ++i){
        // Multiply msg by basis
        for(int j=0; j < gadget_param.rlwe_param->N; ++j){
            msg_cpy[j] = (msg_cpy[j] * gadget_param.basis) % gadget_param.rlwe_param->Q;
        } 
        // Encrypt msg * basis**i 
        out.gadget_ct[i] = sk.encrypt(msg_cpy); 
    } 
    // Encryption of - msg * sk * basis**i 
    out.gadget_ct_sk[0]  = sk.encrypt(msg_x_sk); 
    for(int i = 1; i < gadget_param.ell_max; ++i){
        // Multiply msg by basis
        for(int j=0; j < gadget_param.rlwe_param->N; ++j){
            msg_x_sk[j] = (msg_x_sk[j] * gadget_param.basis) % gadget_param.rlwe_param->Q;
        } 
        // Encrypt - msg * sk * basis**i  
        out.gadget_ct_sk[i] = sk.encrypt(msg_x_sk);  
    } 
    delete(msg_cpy);
    delete(msg_x_sk); 
    out.to_eval();  
    return out;
}
 
