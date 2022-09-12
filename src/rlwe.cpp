
#include "../include/rlwe.h"
#include "../include/utils.h"


rlwe_sk::rlwe_sk(){}

 
/*
rlwe_sk& rlwe_sk::operator=(const rlwe_sk other){
    std::cout << "Copy operator for rlwe_sk" << std::endl;
    param = other.param;
    s = new long[param.N];
    for(int i = 0; i < param.N; ++i){
        s[i] = other.s[i];
    }
    eval_s = new fftw_complex[param.engine->plan_size]; 
    param.engine->to_eval_form_scale(eval_s, s, 2.0);
    return *this;
}
*/

rlwe_sk::rlwe_sk(rlwe_param param){
    this->param = param;
    s = new long[param.N];

    if(param.key_type == uniform){
        param.rand.uniform_array(s, param.N, param.Q);
    }else if(param.key_type == ternary){
        param.rand.ternary_array(s, param.N);
    }else if(param.key_type == ternary){
        param.rand.binary_array(s, param.N);
    } 
    
    eval_s = new fftw_complex[param.engine->plan_size]; 
    param.engine->to_eval_form_scale(eval_s, s, 2.0);
}

rlwe_sk::rlwe_sk(rlwe_param param, long *s){
    this->param = param;
    this->s = s;
    eval_s = new fftw_complex[param.engine->plan_size]; 
    param.engine->to_eval_form_scale(eval_s, s, 2.0);
}
 

rlwe_ct rlwe_sk::encrypt(long* m){ 
    rlwe_ct out(&param); 
     
    param.rand.uniform_array(out.a, param.N, param.Q); 
    long* e = new long[param.N];
    param.rand.gaussian_array(e, param.N, 0.0, param.stddev);   
    fftw_complex *eval_b = new fftw_complex[param.engine->plan_size];  
    param.engine->to_eval_form(eval_b, out.a); 
    param.engine->mul_eval_form(eval_b, eval_s, eval_b); 
    param.engine->to_coef_form(out.b, eval_b);    
    for(int i = 0; i < param.N; ++i){
        out.b[i] = (out.b[i] + e[i] + m[i]) % param.Q;
    }  
    long* p = param.init_poly();
    phase(p, &out); 
    delete[] e;
    delete[] eval_b;
 
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

// Uses SK
void rlwe_sk::phase(long *phase, const rlwe_ct *ct){
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
    //std::cout << "In gadget_rlwe_sk::gadget_encrypt" << std::endl;
    rlwe_gadget_ct out(gadget_param);  
   long* msg_cpy = gadget_param.param.init_zero_poly();
   for(int i = 0; i < gadget_param.param.N; ++i){
       msg_cpy[i] = msg[i];
   } 
   //std::cout << "msg: " << utils::to_string(msg, gadget_param.param.N) << std::endl;
   // Multiply the message with the secret key and negate (-msg * sk)
   long* msg_x_sk = gadget_param.param.init_poly();
    utils::mul_mod(msg_x_sk, msg, gadget_param.param.N, sk.s, gadget_param.param.N, gadget_param.param.N, gadget_param.param.Q, gadget_param.param.ring);
    //std::cout << "msg_x_sk: " << utils::to_string(msg_x_sk, gadget_param.param.N) << std::endl;
    utils::neg_mod(msg_x_sk, msg_x_sk, gadget_param.param.N, gadget_param.param.Q);
    //std::cout << "msg_x_sk: " << utils::to_string(msg_x_sk, gadget_param.param.N) << std::endl;
     
    // Encryption of msg * 2**i
    //Encrypt msg * 1 
    //std::cout << "gadget_ct["<< 0 <<"] = sk.encrypt("<< utils::to_string(msg_cpy, gadget_param.param.N) <<"): " <<  std::endl;
    //std::cout << "gadget_ct["<< 0 <<"] = sk.encrypt("<< utils::to_string(msg_cpy, gadget_param.param.N) <<"): " <<  std::endl;
 
    out.gadget_ct[0] = sk.encrypt(msg_cpy);
    //std::cout << "out.gadget_ct[0]: "<< out.gadget_ct[0].to_string() <<  std::endl;
    //long* phase = new long[gadget_param.param.N];
    //sk.phase(phase, &(out.gadget_ct[0]));
    //std::cout << "phase(gadget_ct["<< 0 <<"]): "<< utils::to_string(phase, gadget_param.param.N) <<  std::endl; 
    for(int i = 1; i < gadget_param.ell_max; ++i){
        // Multiply msg by basis
        for(int j=0; j < gadget_param.param.N; ++j){
            msg_cpy[j] = (msg_cpy[j] * gadget_param.basis) % gadget_param.param.Q;
        } 
        // Encrypt msg * basis**i
        //std::cout << "gadget_ct["<< i <<"] = sk.encrypt("<< utils::to_string(msg_cpy, gadget_param.param.N) <<"): " <<  std::endl;
 
        out.gadget_ct[i] = sk.encrypt(msg_cpy);
        //std::cout << "out.gadget_ct["<<i<<"]: "<< out.gadget_ct[i].to_string() <<  std::endl;
        //sk.phase(phase, &(out.gadget_ct[i]));
        //std::cout << "phase(gadget_ct["<< i <<"])"<< utils::to_string(phase, gadget_param.param.N) <<  std::endl;
    }
 
    // Encryption of - msg * sk * basis**i
    //std::cout << "gadget_ct_sk["<< 0 <<"] = sk.encrypt("<< utils::to_string(msg_x_sk, gadget_param.param.N) <<"): " <<  std::endl;
 
    out.gadget_ct_sk[0]  = sk.encrypt(msg_x_sk);
    //std::cout << "out.gadget_ct_sk["<<0<<"]: "<< out.gadget_ct_sk[0].to_string() <<  std::endl;
    //sk.phase(phase, &(out.gadget_ct_sk[0]));
    //std::cout << "phase(gadget_ct_sk["<< 0 <<"]): "<< utils::to_string(phase, gadget_param.param.N) <<  std::endl;
    for(int i = 1; i < gadget_param.ell_max; ++i){
        // Multiply msg by basis
        for(int j=0; j < gadget_param.param.N; ++j){
            msg_x_sk[j] = (msg_x_sk[j] * gadget_param.basis) % gadget_param.param.Q;
        } 
        // Encrypt - msg * sk * basis**i
        //std::cout << "gadget_ct_sk["<< i <<"] = sk.encrypt("<< utils::to_string(msg_x_sk, gadget_param.param.N) <<"): " <<  std::endl;
 
        out.gadget_ct_sk[i] = sk.encrypt(msg_x_sk); 
        //std::cout << "out.gadget_ct_sk["<<i<<"]: "<< out.gadget_ct_sk[i].to_string() <<  std::endl;
        //sk.phase(phase, &(out.gadget_ct_sk[i]));
        //std::cout << "phase(gadget_ct_sk["<< i <<"])"<< utils::to_string(phase, gadget_param.param.N) <<  std::endl;
    } 
    delete(msg_cpy);
    delete(msg_x_sk);
    return out;
}

rlwe_gadget_ct gadget_rlwe_sk::gadget_encrypt_fft(long* msg){
    //std::cout << "rlwe_gadget_ct gadget_rlwe_sk::gadget_encrypt_fft" << std::endl;
    rlwe_gadget_ct out = gadget_encrypt(msg);
    /*
    for(int i = 0; i < gadget_param.ell; ++i){
        std::cout << "out.gadget_ct[i].to_string("<<i<<"): "<< out.gadget_ct[i].to_string() <<  std::endl;
    }
    for(int i = 0; i < gadget_param.ell; ++i){
        std::cout << "out.gadget_ct_sk[i].to_string("<<i<<"): "<< out.gadget_ct_sk[i].to_string() <<  std::endl;
    }
    */
    out.to_eval();
    return out;
}