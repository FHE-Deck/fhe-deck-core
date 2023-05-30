#include "../include/rlwe_param.h"
#include "../include/utils.h"

rlwe_ct::rlwe_ct(){}

rlwe_ct::rlwe_ct(rlwe_param param){
    this->param = param; 
    a = this->param.init_poly();
    b = this->param.init_poly(); 
    mask = param.Q - 1;
    is_init = true;
}

rlwe_ct::rlwe_ct(rlwe_param param, long *b, long *a){
    this->param = param; 
    this->a = a;
    this->b = b; 
    mask = param.Q - 1;
    is_init = true;
}
  
  
rlwe_ct::~rlwe_ct(){    
    if(!is_init){ 
        return;
    }   
    delete[] a;  
    delete[] b;   
}
 
rlwe_ct::rlwe_ct(const rlwe_ct &other){ 
    this->param = other.param;
    a = param.init_poly();
    b = param.init_poly();
    for(int i = 0; i < param.N; ++i){
        a[i] = other.a[i];
        b[i] = other.b[i];
    }
    this->is_init = true;
}
 
rlwe_ct& rlwe_ct::operator=(const rlwe_ct other){  
    if (this == &other)
    {
        return *this;
    }  
    if(is_init && (this->param.N == other.param.N)){ 
        for(int i = 0; i < param.N; ++i){
            a[i] = other.a[i];
            b[i] = other.b[i];
        }
    }else if(is_init==false){  
        param = other.param; 
        a = param.init_poly();
        b = param.init_poly();
        for(int i = 0; i < param.N; ++i){
            a[i] = other.a[i];
            b[i] = other.b[i];
        }
        this->is_init = true;
    }else{
        throw 0;
    }
    return *this;
}

void rlwe_ct::negacyclic_rotate(rlwe_ct *out, int rot){
    // Like rotate by the first rot coefficients change their sign.  
    utils::negacyclic_rotate_poly(out->a, a, param.N, rot);
    utils::negacyclic_rotate_poly(out->b, b, param.N, rot);  
}


void rlwe_ct::add(rlwe_ct *out, const rlwe_ct *ct){ 
    add(out->a, a, ct->a);
    add(out->b, b, ct->b); 
}


void rlwe_ct::add(rlwe_ct *out, long* x){ 
    add(out->b, b, x); 
}


void rlwe_ct::sub(rlwe_ct *out, const rlwe_ct *ct){  
    sub(out->a, a, ct->a);
    sub(out->b, b, ct->b);  
}

void rlwe_ct::sub(rlwe_ct *out, long* x){  
    sub(out->b, b, x); 
}


void rlwe_ct::neg(rlwe_ct *out){ 
    neg(out->a, a);
    neg(out->b, b); 
}


void rlwe_ct::mul(rlwe_ct *out,  long *x){
    mul(out->a, this->a, x);
    mul(out->b, this->b, x); 
}


std::string rlwe_ct::to_string(){
    std::string out = "[" + utils::to_string(b, param.N) + ", " + utils::to_string(a, param.N) + "]";
    return out;
}
 
 
void rlwe_ct::add(long *out, long *in_1, long *in_2){
      for(int i = 0; i < param.N; ++i){
            out[i] = (in_1[i] + in_2[i]) % param.Q; 
      }
      utils::array_signed_form(out, out, param.N, param.Q);
}

long* rlwe_ct::add(long *in_1, long *in_2){
      long* out = param.init_poly();
      add(out, in_1, in_2);
      return out;
}


void rlwe_ct::sub(long *out, long *in_1, long *in_2){
      for(int i = 0; i < param.N; ++i){
            out[i] = (in_1[i] - in_2[i]) % param.Q; 
      }
      utils::array_signed_form(out, out, param.N, param.Q);
}

long* rlwe_ct::sub(long *in_1, long *in_2){
      long* out = param.init_poly();
      sub(out, in_1, in_2);
      return out;
}


void rlwe_ct::neg(long *out, long *in){
      for(int i = 0; i < param.N; ++i){
            out[i] =  (-in[i]) % param.Q; 
      } 
      utils::array_signed_form(out, out, param.N, param.Q);
}

long* rlwe_ct::neg(long *in){
      long* out = param.init_poly();
      neg(out, in);
      return out;
}
  
void rlwe_ct::mul(long *out, long *in_1, long *in_2){
    if(param.arithmetic == ntl){
        utils::mul_mod(out, in_1, param.N, in_2, param.N, param.N, param.Q, negacyclic);
    }else if(param.arithmetic == double_fft){
        mul_fft(out, in_1, in_2);
    }else if(param.arithmetic == hexl_ntt){ 
        mul_ntt(out, in_1, in_2);
    }else if(param.arithmetic == long_double_fft){
        throw std::exception();
    }else{
        throw std::exception();
    } 
}

void rlwe_ct::mul_fft(long *out, long* in_1, long *in_2){
    fftw_complex *eval_in_1 = new fftw_complex[param.engine.plan_size];  
    fftw_complex *eval_in_2 = new fftw_complex[param.engine.plan_size];  
    fftw_complex *eval_out = new fftw_complex[param.engine.plan_size];
    param.engine.to_eval_form(eval_in_1, in_1); 
    param.engine.to_eval_form_scale(eval_in_2, in_2, 2.0); 
    param.engine.mul_eval_form(eval_out, eval_in_1, eval_in_2); 
    param.engine.to_coef_form(out, eval_out);    
    delete[] eval_in_1;
    delete[] eval_in_2;
    delete[] eval_out;
}


void rlwe_ct::mul_ntt(long *out, long *in_1, long *in_2){
   
    long* eval_in_1 = param.init_poly();  
    long* eval_in_2 = param.init_poly();  
    long* eval_out = param.init_poly();  
    param.ntt.ComputeForward((uint64_t*) eval_in_1, (uint64_t*) in_1, 1, 1); 
    param.ntt.ComputeForward((uint64_t*) eval_in_2, (uint64_t*) in_2, 1, 1); 
    intel::hexl::EltwiseMultMod((uint64_t*) eval_out, (uint64_t*) eval_in_1, (uint64_t*) eval_in_2, param.N, param.Q, 1);
    param.ntt.ComputeInverse((uint64_t*) out, (uint64_t*)  eval_out, 1, 1); 
    delete[] eval_in_1;
    delete[] eval_in_2;
    delete[] eval_out;
    
}
 
 
     
  
rlwe_param::rlwe_param(ring_type ring, int N, long Q, key_dist key_type, modulus_type mod_type, double stddev, polynomial_arithmetic arithmetic){
    this->Q = Q;
    this->mod_type = mod_type;
    this->key_type = key_type;
    // TODO: Actually the mask is useless when Q is not a power of two
    this->mask = Q-1;
    this->N = N; 
    this->stddev = stddev; 
    this->ring = ring;  
    this->arithmetic = arithmetic;
    set_computing_engine(); 
}
        

rlwe_param::rlwe_param(const rlwe_param &other){
    this->Q = other.Q;
    this->mod_type = other.mod_type;
    this->key_type = other.key_type; 
    this->mask = other.Q-1;
    this->N = other.N; 
    this->stddev = other.stddev; 
    this->ring = other.ring;  
    this->arithmetic = other.arithmetic;
    set_computing_engine(); 
}

rlwe_param& rlwe_param::operator=(const rlwe_param other){
    this->Q = other.Q;
    this->mod_type = other.mod_type;
    this->key_type = other.key_type; 
    this->mask = other.Q-1;
    this->N = other.N; 
    this->stddev = other.stddev; 
    this->ring = other.ring;  
    this->arithmetic = other.arithmetic;
    set_computing_engine();
    return *this;
}


long* rlwe_param::init_poly(){
    return new long[this->N]; 
}

long* rlwe_param::init_zero_poly(){
    long *out = new long[this->N];
      for(int i = 0; i < this->N; ++i){
            out[i] = 0;
      }
      return out;
}

void rlwe_param::set_computing_engine(){
    if(arithmetic == double_fft){ 
        engine = fft_plan(ring, N, false);   
    }else if(arithmetic == long_double_fft){
        engine = fft_plan(ring, N, true);   
    }
    else if(arithmetic == hexl_ntt){
        ntt = intel::hexl::NTT(N, Q);
    }else if(arithmetic == ntl){
        // Do nothing here
    }else{
        throw std::exception();
    }
}

fftw_complex* rlwe_param::init_fft_poly(){
    return new fftw_complex[engine.plan_size]; 
}

fftwl_complex* rlwe_param::init_fft_poly_l(){
    return new fftwl_complex[engine.plan_size]; 
}
 
 

rlwe_gadget_ct::rlwe_gadget_ct(rlwe_gadget_param gadget_param){  
    this->gadget_param = gadget_param; 
    gadget_ct = new rlwe_ct[gadget_param.ell_max];
    gadget_ct_sk = new rlwe_ct[gadget_param.ell_max]; 
    for(int i = 0; i < gadget_param.ell_max; ++i){
        gadget_ct[i] = rlwe_ct(gadget_param.param);
        gadget_ct_sk[i] = rlwe_ct(gadget_param.param);
    }    
    out_minus = rlwe_ct(gadget_param.param);
    if(gadget_param.param.arithmetic == double_fft){
        init_fft_eval();
    }else if(gadget_param.param.arithmetic == hexl_ntt){ 
        init_ntt_eval();
        this->ntt = intel::hexl::NTT(gadget_param.param.N, gadget_param.param.Q);
    }else{
        // TODO: Actually NTL Should work.... Check that later
        std::cout << "Arithmetic Currently Not Supported" << std::endl;
    }
    this->is_init = true;
}

rlwe_gadget_ct::~rlwe_gadget_ct(){     
    if(is_init == false){
        return;
    }  
    delete[] gadget_ct;  
    delete[] gadget_ct_sk;    
    if(gadget_param.param.arithmetic == double_fft){ 
        delete_fft_eval(); 
    }else if(gadget_param.param.arithmetic == hexl_ntt){ 
        delete_ntt_eval();
    }else{
        std::cout << "Arithmetic Currently Not Supported" << std::endl;
    }  
}



rlwe_gadget_ct::rlwe_gadget_ct(const rlwe_gadget_ct& other){  
    this->gadget_param = other.gadget_param;
    this->mask = other.mask;  
    out_minus = rlwe_ct(gadget_param.param);
    if(is_init == false){ 
        gadget_ct = new rlwe_ct[gadget_param.ell_max];
        gadget_ct_sk = new rlwe_ct[gadget_param.ell_max];
        if(gadget_param.param.arithmetic == double_fft){
            init_fft_eval();
        }else if(gadget_param.param.arithmetic == hexl_ntt){
            init_ntt_eval();
            this->ntt = intel::hexl::NTT(gadget_param.param.N, gadget_param.param.Q);
        }else{
            std::cout << "Arithmetic Currently Not Supported" << std::endl;
        }
        is_init = true;  
    }  
    for(int i = 0; i < gadget_param.ell_max; ++i){ 
        gadget_ct[i] = other.gadget_ct[i];
        gadget_ct_sk[i] =  other.gadget_ct_sk[i]; 
        if(gadget_param.param.arithmetic == double_fft){
            for(int j = 0; j < gadget_param.param.engine.plan_size; ++j){
                eval_a[i][j][0] = other.eval_a[i][j][0];
                eval_a[i][j][1] = other.eval_a[i][j][1];
                eval_b[i][j][0] = other.eval_b[i][j][0];
                eval_b[i][j][1] = other.eval_b[i][j][1];
                eval_a_sk[i][j][0] = other.eval_a_sk[i][j][0];
                eval_a_sk[i][j][1] = other.eval_a_sk[i][j][1];
                eval_b_sk[i][j][0] = other.eval_b_sk[i][j][0];
                eval_b_sk[i][j][1] = other.eval_b_sk[i][j][1];
            }
        }else if(gadget_param.param.arithmetic == hexl_ntt){ 
            utils::cp(ntt_eval_a[i], other.ntt_eval_a[i], gadget_param.param.N);
            utils::cp(ntt_eval_b[i], other.ntt_eval_b[i], gadget_param.param.N);
            utils::cp(ntt_eval_a_sk[i], other.ntt_eval_a_sk[i], gadget_param.param.N);
            utils::cp(ntt_eval_b_sk[i], other.ntt_eval_b_sk[i], gadget_param.param.N);
        }else{
            std::cout << "Arithmetic Currently Not Supported" << std::endl;
        } 
    } 
}


rlwe_gadget_ct& rlwe_gadget_ct::operator=(const rlwe_gadget_ct other){    
    this->gadget_param = other.gadget_param;
    this->mask = other.mask;  
    out_minus = rlwe_ct(gadget_param.param);
    if(is_init == false){ 
        gadget_ct = new rlwe_ct[gadget_param.ell_max];
        gadget_ct_sk = new rlwe_ct[gadget_param.ell_max];
        if(gadget_param.param.arithmetic == double_fft){
            init_fft_eval();
        }else if(gadget_param.param.arithmetic == hexl_ntt){
            init_ntt_eval();
            this->ntt = intel::hexl::NTT(gadget_param.param.N, gadget_param.param.Q);
        }else{
            std::cout << "Arithmetic Currently Not Supported" << std::endl;
        }
        is_init = true;  
    }  
    for(int i = 0; i < gadget_param.ell_max; ++i){  
        gadget_ct[i] = other.gadget_ct[i];
        gadget_ct_sk[i] =  other.gadget_ct_sk[i]; 
        if(gadget_param.param.arithmetic == double_fft){
            for(int j = 0; j < gadget_param.param.engine.plan_size; ++j){
                eval_a[i][j][0] = other.eval_a[i][j][0];
                eval_a[i][j][1] = other.eval_a[i][j][1];
                eval_b[i][j][0] = other.eval_b[i][j][0];
                eval_b[i][j][1] = other.eval_b[i][j][1];
                eval_a_sk[i][j][0] = other.eval_a_sk[i][j][0];
                eval_a_sk[i][j][1] = other.eval_a_sk[i][j][1];
                eval_b_sk[i][j][0] = other.eval_b_sk[i][j][0];
                eval_b_sk[i][j][1] = other.eval_b_sk[i][j][1];
            }
        }else if(gadget_param.param.arithmetic == hexl_ntt){ 
            utils::cp(ntt_eval_a[i], other.ntt_eval_a[i], gadget_param.param.N);
            utils::cp(ntt_eval_b[i], other.ntt_eval_b[i], gadget_param.param.N);
            utils::cp(ntt_eval_a_sk[i], other.ntt_eval_a_sk[i], gadget_param.param.N);
            utils::cp(ntt_eval_b_sk[i], other.ntt_eval_b_sk[i], gadget_param.param.N);
        }else{
            std::cout << "Arithmetic Currently Not Supported" << std::endl;
        } 
    }  
    return *this;
}
 

void rlwe_gadget_ct::to_eval(){ 
    if(gadget_param.param.arithmetic == double_fft){
        to_eval_fft();
    }else if(gadget_param.param.arithmetic == hexl_ntt){
        to_eval_ntt();
    }else{
        std::cout << "Arithmetic Currently Not Supported" << std::endl;
    } 
}

void rlwe_gadget_ct::to_coef(){
    if(gadget_param.param.arithmetic == double_fft){
        to_coef_fft();
    }else if(gadget_param.param.arithmetic == hexl_ntt){
        to_coef_ntt();
    }else{
        std::cout << "Arithmetic Currently Not Supported" << std::endl;
    } 
}

 
 
void rlwe_gadget_ct::mul(rlwe_ct *out, const rlwe_ct *ct, gadget_mul_mode mode){    
    long** ct_a_dec;
    long** ct_b_dec;
    int ell_delete;
    // Depending on whether we do randomized or deterministic:
    // We use either decompose, or gaussian sample.
    if(mode == simul){   
        ell_delete = gadget_param.ell;
        ct_a_dec = gadget_param.rand_gadget.sample(ct->a);
        ct_b_dec = gadget_param.rand_gadget.sample(ct->b); 
        if(gadget_param.param.arithmetic == double_fft){ 
            multisum_fft(out->b, ct_b_dec, eval_b, gadget_param.ell, gadget_param.w);
            multisum_fft(out->a, ct_b_dec, eval_a, gadget_param.ell, gadget_param.w);
            multisum_fft(out_minus.b, ct_a_dec, eval_b_sk, gadget_param.ell, gadget_param.w);
            multisum_fft(out_minus.a, ct_a_dec, eval_a_sk, gadget_param.ell, gadget_param.w);
        }else if(gadget_param.param.arithmetic == hexl_ntt){ 
            multisum_ntt(out->b, ct_b_dec, ntt_eval_b, gadget_param.ell, gadget_param.w);
            multisum_ntt(out->a, ct_b_dec, ntt_eval_a, gadget_param.ell, gadget_param.w);
            multisum_ntt(out_minus.b, ct_a_dec, ntt_eval_b_sk, gadget_param.ell, gadget_param.w);
            multisum_ntt(out_minus.a, ct_a_dec, ntt_eval_a_sk, gadget_param.ell, gadget_param.w);
        }else{
            std::cout << "Arithmetic not supported." << std::endl;
        }
        
    }else if(mode == deter){ 
        ell_delete = gadget_param.ell_any;
        // Signed decomposition
        ct_a_dec = gadget_param.deter_gadget.sample(ct->a);
        ct_b_dec = gadget_param.deter_gadget.sample(ct->b); 
        if(gadget_param.param.arithmetic == double_fft){  
            multisum_fft(out->b, ct_b_dec, eval_b, gadget_param.ell_any, gadget_param.w_any);
            multisum_fft(out->a, ct_b_dec, eval_a, gadget_param.ell_any, gadget_param.w_any);
            multisum_fft(out_minus.b, ct_a_dec, eval_b_sk, gadget_param.ell_any, gadget_param.w_any);
            multisum_fft(out_minus.a, ct_a_dec, eval_a_sk, gadget_param.ell_any, gadget_param.w_any); 
        }else if(gadget_param.param.arithmetic == hexl_ntt){  
            multisum_ntt(out->b, ct_b_dec, ntt_eval_b, gadget_param.ell_any, gadget_param.w_any);
            multisum_ntt(out->a, ct_b_dec, ntt_eval_a, gadget_param.ell_any, gadget_param.w_any);
            multisum_ntt(out_minus.b, ct_a_dec, ntt_eval_b_sk, gadget_param.ell_any, gadget_param.w_any);
            multisum_ntt(out_minus.a, ct_a_dec, ntt_eval_a_sk, gadget_param.ell_any, gadget_param.w_any); 
 
        }else{
            std::cout << "Arithmetic not supported." << std::endl;
        } 
    }  
    out->add(out, &out_minus);
 
    for(int i = 0; i < ell_delete; ++i){  
        delete[] ct_a_dec[i];
        delete[] ct_b_dec[i];
    }  
    delete[] ct_a_dec;
    delete[] ct_b_dec;  
}

 
 
 
// Currently multisum_fft is lazy - modulus reduction happends only at the end.
void rlwe_gadget_ct::multisum_fft(long *out, long** arr, fftw_complex **c_arr, int ell, int w){
    fftw_complex *multisum_eval = new fftw_complex[gadget_param.param.engine.plan_size]; 
    fftw_complex *prod = new fftw_complex[gadget_param.param.engine.plan_size];    
    
    gadget_param.param.engine.to_eval_form(multisum_eval, arr[0]);   
    gadget_param.param.engine.mul_eval_form(multisum_eval, multisum_eval, c_arr[0]);  
  
    for(int i = 1; i < ell; ++i){ 
        gadget_param.param.engine.to_eval_form(prod, arr[i]);     
        gadget_param.param.engine.mul_eval_form(prod, prod, c_arr[w*i]); 
        gadget_param.param.engine.add_eval_form(multisum_eval, multisum_eval, prod); 
 
    } 

    gadget_param.param.engine.to_coef_form(out, multisum_eval);  
    mod_reduce(out, out); 
    delete[] multisum_eval;
    delete[] prod; 
 
}
   
// Multisum any multiplies every second ciphertext
void rlwe_gadget_ct::multisum_any_fft(long *out, long** arr, fftw_complex **c_arr){
    fftw_complex *multisum_eval = new fftw_complex[gadget_param.param.engine.plan_size]; 
    fftw_complex *prod = new fftw_complex[gadget_param.param.engine.plan_size];    
    
    gadget_param.param.engine.to_eval_form(multisum_eval, arr[0]);   
    gadget_param.param.engine.mul_eval_form(multisum_eval, multisum_eval, c_arr[0]);  
  
    for(int i = 1; i < gadget_param.ell_any; ++i){ 
        gadget_param.param.engine.to_eval_form(prod, arr[i]);     
        gadget_param.param.engine.mul_eval_form(prod, prod, c_arr[2*i]); 
        gadget_param.param.engine.add_eval_form(multisum_eval, multisum_eval, prod); 
 
    } 

    gadget_param.param.engine.to_coef_form(out, multisum_eval);  
    mod_reduce(out, out); 
    delete[] multisum_eval;
    delete[] prod; 
}



void rlwe_gadget_ct::multisum_ntt(long *out, long** arr, long **c_arr, int ell, int w){
    long *multisum_eval = new long[gadget_param.param.N]; 
    long *prod = new long[gadget_param.param.N];   
    utils::array_mod_form(arr[0], arr[0], gadget_param.param.N, gadget_param.param.Q); 
    ntt.ComputeForward((uint64_t*) multisum_eval, (uint64_t*) arr[0], 1, 1);
    intel::hexl::EltwiseMultMod((uint64_t*) multisum_eval, (uint64_t*) multisum_eval, (uint64_t*) c_arr[0], gadget_param.param.N, gadget_param.param.Q, 1);
   
    for(int i = 1; i < ell; ++i){ 
        utils::array_mod_form(arr[i], arr[i], gadget_param.param.N, gadget_param.param.Q); 
        ntt.ComputeForward((uint64_t*) prod, (uint64_t*) arr[i], 1, 1);  
        intel::hexl::EltwiseMultMod((uint64_t*) prod, (uint64_t*) prod, (uint64_t*) c_arr[w*i], gadget_param.param.N, gadget_param.param.Q, 1); 
        intel::hexl::EltwiseAddMod((uint64_t*) multisum_eval, (uint64_t*) multisum_eval, (uint64_t*) prod, gadget_param.param.N, gadget_param.param.Q);   
    }  
    ntt.ComputeInverse((uint64_t*) out, (uint64_t*)  multisum_eval, 1, 1);
    delete[] multisum_eval;
    delete[] prod;   
}


 
void rlwe_gadget_ct::multisum_any_ntt(long *out, long** arr, long **c_arr){
    long *multisum_eval = new long[gadget_param.param.N]; 
    long *prod = new long[gadget_param.param.N];   
    utils::array_mod_form(arr[0], arr[0], gadget_param.param.N, gadget_param.param.Q); 
    ntt.ComputeForward((uint64_t*) multisum_eval, (uint64_t*) arr[0], 1, 1);
    intel::hexl::EltwiseMultMod((uint64_t*) multisum_eval, (uint64_t*) multisum_eval, (uint64_t*) c_arr[0], gadget_param.param.N, gadget_param.param.Q, 1);
   
    for(int i = 1; i < gadget_param.ell_any; ++i){ 
        utils::array_mod_form(arr[i], arr[i], gadget_param.param.N, gadget_param.param.Q); 
        ntt.ComputeForward((uint64_t*) prod, (uint64_t*) arr[i], 1, 1);  
        intel::hexl::EltwiseMultMod((uint64_t*) prod, (uint64_t*) prod, (uint64_t*) c_arr[2*i], gadget_param.param.N, gadget_param.param.Q, 1); 
        intel::hexl::EltwiseAddMod((uint64_t*) multisum_eval, (uint64_t*) multisum_eval, (uint64_t*) prod, gadget_param.param.N, gadget_param.param.Q);   
    }  
    ntt.ComputeInverse((uint64_t*) out, (uint64_t*)  multisum_eval, 1, 1);
    delete[] multisum_eval;
    delete[] prod;  
}



 void rlwe_gadget_ct::init_fft_eval(){
    eval_a = new fftw_complex*[gadget_param.ell_max];
    eval_b = new fftw_complex*[gadget_param.ell_max];  
    eval_a_sk = new fftw_complex*[gadget_param.ell_max];
    eval_b_sk = new fftw_complex*[gadget_param.ell_max];   
    mask = gadget_param.param.Q-1; 
    for(int i = 0; i < gadget_param.ell_max; ++i){  
        eval_a[i] = gadget_param.param.init_fft_poly();
        eval_b[i] = gadget_param.param.init_fft_poly();
        eval_a_sk[i] = gadget_param.param.init_fft_poly();
        eval_b_sk[i] = gadget_param.param.init_fft_poly();
    }
}


void rlwe_gadget_ct::delete_fft_eval(){
    for(int i = 0; i < gadget_param.ell_max; ++i){ 
        delete[] eval_a[i];
        delete[] eval_b[i];
        delete[] eval_a_sk[i];
        delete[] eval_b_sk[i]; 
    }
    delete[] eval_a;
    delete[] eval_b;
    delete[] eval_a_sk;
    delete[] eval_b_sk;  
}

 void rlwe_gadget_ct::init_ntt_eval(){ 
    ntt_eval_a = new long*[gadget_param.ell_max];
    ntt_eval_b = new long*[gadget_param.ell_max];  
    ntt_eval_a_sk = new long*[gadget_param.ell_max];
    ntt_eval_b_sk = new long*[gadget_param.ell_max];   
    for(int i = 0; i < gadget_param.ell_max; ++i){   
        ntt_eval_a[i] = gadget_param.param.init_poly(); 
        ntt_eval_b[i] = gadget_param.param.init_poly(); 
        ntt_eval_a_sk[i] = gadget_param.param.init_poly(); 
        ntt_eval_b_sk[i] = gadget_param.param.init_poly(); 
    }
}

 void rlwe_gadget_ct::delete_ntt_eval(){
    for(int i = 0; i < gadget_param.ell_max; ++i){ 
        delete[] ntt_eval_a[i];
        delete[] ntt_eval_b[i];
        delete[] ntt_eval_a_sk[i];
        delete[] ntt_eval_b_sk[i]; 
    }
    delete[] ntt_eval_a;
    delete[] ntt_eval_b;
    delete[] ntt_eval_a_sk;
    delete[] ntt_eval_b_sk;  
}


void rlwe_gadget_ct::to_eval_fft(){
    for(int i = 0; i < gadget_param.ell_max; ++i){
        // Note: we scale this one up, because we prepare the gadget ciphertext for multiplication
        gadget_param.param.engine.to_eval_form_scale(eval_a[i], gadget_ct[i].a, 2.0); 
        gadget_param.param.engine.to_eval_form_scale(eval_b[i], gadget_ct[i].b, 2.0); 
        gadget_param.param.engine.to_eval_form_scale(eval_a_sk[i], gadget_ct_sk[i].a, 2.0); 
        gadget_param.param.engine.to_eval_form_scale(eval_b_sk[i], gadget_ct_sk[i].b, 2.0); 
    }   
} 

void rlwe_gadget_ct::to_coef_fft(){
    for(int i = 0; i < gadget_param.ell_max; ++i){ 
        gadget_param.param.engine.to_coef_form(gadget_ct[i].a, eval_a[i]);
        gadget_param.param.engine.to_coef_form(gadget_ct[i].b, eval_b[i]);
        gadget_param.param.engine.to_coef_form(gadget_ct_sk[i].a, eval_a_sk[i]);
        gadget_param.param.engine.to_coef_form(gadget_ct_sk[i].b, eval_b_sk[i]);
    }    
} 

void rlwe_gadget_ct::to_eval_ntt(){ 
    for(int i = 0; i < gadget_param.ell_max; ++i){ 
        ntt.ComputeForward((uint64_t*) ntt_eval_a[i], (uint64_t*) gadget_ct[i].a, 1, 1); 
        ntt.ComputeForward((uint64_t*) ntt_eval_b[i], (uint64_t*) gadget_ct[i].b, 1, 1); 
        ntt.ComputeForward((uint64_t*) ntt_eval_a_sk[i], (uint64_t*) gadget_ct_sk[i].a, 1, 1); 
        ntt.ComputeForward((uint64_t*) ntt_eval_b_sk[i], (uint64_t*) gadget_ct_sk[i].b, 1, 1);
    }
} 

void rlwe_gadget_ct::to_coef_ntt(){ 
    for(int i = 0; i < gadget_param.ell_max; ++i){
         ntt.ComputeInverse((uint64_t*) gadget_ct[i].a, (uint64_t*)  ntt_eval_a[i], 1, 1);
         ntt.ComputeInverse((uint64_t*) gadget_ct[i].b, (uint64_t*)  ntt_eval_b[i], 1, 1);
         ntt.ComputeInverse((uint64_t*) gadget_ct_sk[i].a, (uint64_t*)  ntt_eval_a_sk[i], 1, 1);
         ntt.ComputeInverse((uint64_t*) gadget_ct_sk[i].b, (uint64_t*)  ntt_eval_b_sk[i], 1, 1);
    }
} 


void rlwe_gadget_ct::mod_reduce(long *out_poly, long *in_poly){
    if(gadget_param.param.mod_type == power_of_two){
        for(int i = 0; i < gadget_param.param.engine.N; ++i){   
            out_poly[i] = in_poly[i] & this->mask; 
        }
    }else{
        for(int i = 0; i < gadget_param.param.engine.N; ++i){   
            out_poly[i] = in_poly[i] % gadget_param.param.Q; 
        }
    } 
}

 
void rlwe_gadget_ct::mod_reduce(long *out_poly, long double *in_poly_l){
      long double Q_l = (long double) gadget_param.param.Q;
      for(int i = 0; i < gadget_param.param.engine.N; ++i){  
      out_poly[i] = round(fmodl(in_poly_l[i], Q_l));  
   }
}

 
 

rlwe_gadget_param::rlwe_gadget_param(rlwe_param &rlwe_par, int basis, gadget &deter_gadget, gadget &rand_gadget){ 
    this->param = rlwe_par; 
    this->deter_gadget = deter_gadget; 
    this->rand_gadget = rand_gadget;  
    setup_the_other_parametrs(); 
}



rlwe_gadget_param::rlwe_gadget_param(const rlwe_gadget_param &other){
    this->param = other.param; 
    this->deter_gadget = other.deter_gadget; 
    this->rand_gadget = other.rand_gadget;  
    setup_the_other_parametrs(); 
}


rlwe_gadget_param& rlwe_gadget_param::operator=(const rlwe_gadget_param other){
    if (this == &other)
    {
        return *this;
    } 
    this->param = other.param; 
    this->deter_gadget = other.deter_gadget; 
    this->rand_gadget = other.rand_gadget; 
    setup_the_other_parametrs(); 
    return *this;
}


void rlwe_gadget_param::setup_the_other_parametrs(){ 
    this->basis = rand_gadget.basis;
    this->k = rand_gadget.k;
    this->ell = rand_gadget.ell;  

    // Set the parameters for any 
    this->basis_any = deter_gadget.basis;
    this->k_any = deter_gadget.k;
    this->ell_any = deter_gadget.ell;
 
    if(basis_any == basis){
        w = 1;
        w_any = 1;
        this->ell_max = ell;
    }else if(basis_any < basis){ 
        w_any = 1;
        w = utils::power_times(basis, basis_any);
        if(!utils::is_power_of(basis, basis_any)){
            std::cout << "WARNING: basis is not a powr of basis_any!!!" << std::endl;
        }
        if(w * ell > ell_any){
            this->ell_max = w * ell;
        }else{
            this->ell_max = ell_any;
        } 
    }else{ 
        w = 1;
        w_any = utils::power_times(basis_any, basis);
        if(!utils::is_power_of(basis_any, basis)){
            std::cout << "WARNING: basis is not a powr of basis_any!!!" << std::endl;
        }
        if(w_any * ell_any > ell){
            this->ell_max = w_any * ell_any;
        }else{
            this->ell_max = ell;
        }
    }
}