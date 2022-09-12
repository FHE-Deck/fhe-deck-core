#include "../include/rlwe_param.h"
#include "../include/utils.h"

rlwe_ct::rlwe_ct(){}

rlwe_ct::rlwe_ct(rlwe_param *param){
    this->param = param; 
    a = this->param->init_poly();
    b = this->param->init_poly(); 
    mask = param->Q - 1;
    init = true;
}

rlwe_ct::rlwe_ct(rlwe_param *param, long *b, long *a){
    this->param = param; 
    this->a = a;
    this->b = b; 
    mask = param->Q - 1;
    init = true;
}
 
 

rlwe_ct::~rlwe_ct(){   
    delete[] a;
    delete[] b; 
}
 
rlwe_ct& rlwe_ct::operator=(const rlwe_ct other){ 
    param = other.param;
    // TODO: check if already initialized
    if(init==false){ 
        a = param->init_poly();
        b = param->init_poly();
    }
    for(int i = 0; i < param->N; ++i){
        a[i] = other.a[i];
        b[i] = other.b[i];
    }
    return *this;
}

void rlwe_ct::negacyclic_rotate(rlwe_ct *out, int rot){
    // Like rotate by the first rot coefficients change their sign. 
    //rlwe_ct out(param);
    utils::negacyclic_rotate_poly(out->a, a, param->N, rot);
    utils::negacyclic_rotate_poly(out->b, b, param->N, rot); 
    //return out;
}


void rlwe_ct::add(rlwe_ct *out, const rlwe_ct *ct){
    //rlwe_ct out(param);
    add(out->a, a, ct->a);
    add(out->b, b, ct->b);
    //return out;
}

void rlwe_ct::sub(rlwe_ct *out, const rlwe_ct *ct){ 
    //rlwe_ct out(param);
    sub(out->a, a, ct->a);
    sub(out->b, b, ct->b); 
    //return out;
}

void rlwe_ct::neg(rlwe_ct *out){
    //rlwe_ct out(param);
    neg(out->a, a);
    neg(out->b, b);
    //return out;
}

std::string rlwe_ct::to_string(){
    std::string out = "[" + utils::to_string(b, param->N) + ", " + utils::to_string(a, param->N) + "]";
    return out;
}
 
 
void rlwe_ct::add(long *out, long *in_1, long *in_2){
      for(int i = 0; i < param->N; ++i){
            out[i] = (in_1[i] + in_2[i]) % param->Q;
            //out[i] = (in_1[i] + in_2[i]) & this->mask;
      }
      utils::array_signed_form(out, out, param->N, param->Q);
}

long* rlwe_ct::add(long *in_1, long *in_2){
      long* out = param->init_poly();
      add(out, in_1, in_2);
      return out;
}


void rlwe_ct::sub(long *out, long *in_1, long *in_2){
      for(int i = 0; i < param->N; ++i){
            out[i] = (in_1[i] - in_2[i]) % param->Q;
            //out[i] = (in_1[i] - in_2[i]) & this->mask;
      }
      utils::array_signed_form(out, out, param->N, param->Q);
}

long* rlwe_ct::sub(long *in_1, long *in_2){
      long* out = param->init_poly();
      sub(out, in_1, in_2);
      return out;
}


void rlwe_ct::neg(long *out, long *in){
      for(int i = 0; i < param->N; ++i){
            out[i] =  (-in[i]) % param->Q;
            //out[i] = (-in[i]) & this->mask;
      } 
      utils::array_signed_form(out, out, param->N, param->Q);
}

long* rlwe_ct::neg(long *in){
      long* out = param->init_poly();
      neg(out, in);
      return out;
}
  


rlwe_param::~rlwe_param(){} 

rlwe_param::rlwe_param(){} 
     
rlwe_param::rlwe_param(ring_type ring, int N, long Q, key_dist key_type, modulus_type mod_type, double stddev){
    this->Q = Q;
    this->mod_type = mod_type;
    this->key_type = key_type;
    // TODO: Note that we neve check whether Q is in its power of two mode. 
    // If its not, but we will do modulus reduction by masking then we end up with rubish
    // So be carefull, and fix this later.
    this->mask = Q-1;
    this->N = N; 
    this->stddev = stddev; 
    this->ring = ring;  
    engine = new fft_plan(ring, N);  
    init = true; 
}

rlwe_param::rlwe_param(ring_type ring, int N, long Q, key_dist key_type, modulus_type mod_type, double stddev, bool long_arithmetic){
    this->Q = Q;
    this->mod_type = mod_type;
    this->key_type = key_type;
    // TODO: Note that we neve check whether Q is in its power of two mode. 
    // If its not, but we will do modulus reduction by masking then we end up with rubish
    // So be carefull, and fix this later.
    this->mask = Q-1;
    this->N = N; 
    this->stddev = stddev; 
    this->ring = ring;  
    engine = new fft_plan(ring, N, long_arithmetic);  
    init = true;
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

fftw_complex* rlwe_param::init_fft_poly(){
    return new fftw_complex[engine->plan_size]; 
}

fftwl_complex* rlwe_param::init_fft_poly_l(){
    return new fftwl_complex[engine->plan_size]; 
}




rlwe_gadget_ct::rlwe_gadget_ct(){}

rlwe_gadget_ct::rlwe_gadget_ct(rlwe_gadget_param gadget_param){
    this->gadget_param = gadget_param;

    gadget_ct = new rlwe_ct[gadget_param.ell_max];
    gadget_ct_sk = new rlwe_ct[gadget_param.ell_max];
    eval_a = new fftw_complex*[gadget_param.ell_max];
    eval_b = new fftw_complex*[gadget_param.ell_max];  
    eval_a_sk = new fftw_complex*[gadget_param.ell_max];
    eval_b_sk = new fftw_complex*[gadget_param.ell_max];  
    
    mask = gadget_param.param.Q-1;

    for(int i = 0; i < gadget_param.ell_max; ++i){ 
        gadget_ct[i] = rlwe_ct(&gadget_param.param);
        gadget_ct_sk[i] = rlwe_ct(&gadget_param.param);
        eval_a[i] = gadget_param.param.init_fft_poly();
        eval_b[i] = gadget_param.param.init_fft_poly();
        eval_a_sk[i] = gadget_param.param.init_fft_poly();
        eval_b_sk[i] = gadget_param.param.init_fft_poly();
    }
}

rlwe_gadget_ct::~rlwe_gadget_ct(){    
    delete[] gadget_ct;
    delete[] gadget_ct_sk; 
    // Need to free these differently!!
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


rlwe_gadget_ct& rlwe_gadget_ct::operator=(const rlwe_gadget_ct other){ 
    this->gadget_param = other.gadget_param;
    this->mask = other.mask; 
    if(init == false){
        gadget_ct = new rlwe_ct[gadget_param.ell_max];
        gadget_ct_sk = new rlwe_ct[gadget_param.ell_max];
        eval_a = new fftw_complex*[gadget_param.ell_max];
        eval_b = new fftw_complex*[gadget_param.ell_max];  
        eval_a_sk = new fftw_complex*[gadget_param.ell_max];
        eval_b_sk = new fftw_complex*[gadget_param.ell_max];   
    } 
    for(int i = 0; i < gadget_param.ell_max; ++i){ 
        gadget_ct[i] = rlwe_ct(&gadget_param.param);
        gadget_ct_sk[i] = rlwe_ct(&gadget_param.param);
        eval_a[i] = gadget_param.param.init_fft_poly();
        eval_b[i] = gadget_param.param.init_fft_poly();
        eval_a_sk[i] = gadget_param.param.init_fft_poly();
        eval_b_sk[i] = gadget_param.param.init_fft_poly();
        for(int j = 0; j < gadget_param.param.engine->plan_size; ++j){
            eval_a[i][j][0] = other.eval_a[i][j][0];
            eval_a[i][j][1] = other.eval_a[i][j][1];
            eval_b[i][j][0] = other.eval_b[i][j][0];
            eval_b[i][j][1] = other.eval_b[i][j][1];
            eval_a_sk[i][j][0] = other.eval_a_sk[i][j][0];
            eval_a_sk[i][j][1] = other.eval_a_sk[i][j][1];
            eval_b_sk[i][j][0] = other.eval_b_sk[i][j][0];
            eval_b_sk[i][j][1] = other.eval_b_sk[i][j][1];
        }
    }
    return *this;
}
 

void rlwe_gadget_ct::to_eval(){ 
    for(int i = 0; i < gadget_param.ell_max; ++i){
        // Note: we scale this one up, because we prepare the gadget ciphertext for multiplication
        gadget_param.param.engine->to_eval_form_scale(eval_a[i], gadget_ct[i].a, 2.0); 
        gadget_param.param.engine->to_eval_form_scale(eval_b[i], gadget_ct[i].b, 2.0); 
        gadget_param.param.engine->to_eval_form_scale(eval_a_sk[i], gadget_ct_sk[i].a, 2.0); 
        gadget_param.param.engine->to_eval_form_scale(eval_b_sk[i], gadget_ct_sk[i].b, 2.0); 
    }  
    eval = true;
}

void rlwe_gadget_ct::to_coef(){
    for(int i = 0; i < gadget_param.ell_max; ++i){
        // Note: we scale this one up, because we prepare the gadget ciphertext for multiplication
        gadget_param.param.engine->to_coef_form(gadget_ct[i].a, eval_a[i]);
        gadget_param.param.engine->to_coef_form(gadget_ct[i].b, eval_b[i]);
        gadget_param.param.engine->to_coef_form(gadget_ct_sk[i].a, eval_a_sk[i]);
        gadget_param.param.engine->to_coef_form(gadget_ct_sk[i].b, eval_b_sk[i]);
    }  
    eval = false;
}

 
 
void rlwe_gadget_ct::mul(rlwe_ct *out, const rlwe_ct *ct, gadget_mul_mode mode){   
    //rlwe_ct out(gadget_param.param);
    rlwe_ct out_minus(&gadget_param.param); 
    long** ct_a_dec;
    long** ct_b_dec;
    int ell_delete;
    // Depending on whether we do randomized or deterministic:
    // We use either decompose, or gaussian sample.
    if(mode == simul){  
        ell_delete = gadget_param.ell;
        ct_a_dec = gaussian_sample(ct->a);
        ct_b_dec = gaussian_sample(ct->b);

        multisum(out->b, ct_b_dec, eval_b);
        multisum(out->a, ct_b_dec, eval_a);
        multisum(out_minus.b, ct_a_dec, eval_b_sk);
        multisum(out_minus.a, ct_a_dec, eval_a_sk);
    }else if(mode == signed_decomp){
        ell_delete = gadget_param.ell_any;
        // Signed decomposition
        ct_a_dec = decompose(ct->a);
        ct_b_dec = decompose(ct->b); 
        multisum_any(out->b, ct_b_dec, eval_b);
        multisum_any(out->a, ct_b_dec, eval_a);
        multisum_any(out_minus.b, ct_a_dec, eval_b_sk);
        multisum_any(out_minus.a, ct_a_dec, eval_a_sk);
    } 
    //rlwe_ct ret(gadget_param.param); 
    out->add(out, &out_minus);
 
    for(int i = 0; i < ell_delete; ++i){  
        delete[] ct_a_dec[i];
        delete[] ct_b_dec[i];
    }  
    delete[] ct_a_dec;
    delete[] ct_b_dec; 
    //return ret;
}


// Will take ell (because its always the smaller)
long** rlwe_gadget_ct::gaussian_sample(long *in){ 
    // Decomp c_1. 
    long **decomposed = new long*[gadget_param.ell]; 
    for(int i = 0; i < gadget_param.ell; ++i){  
        decomposed[i] = gadget_param.param.init_zero_poly();  
    }  
    // If I want binomial, then do it here.....
    utils::gaussian_sample(decomposed, in, gadget_param.param.N, gadget_param.basis, gadget_param.k, gadget_param.ell, gadget_param.gadget_rand);
    //gaussian_sample(decomposed, in); 
    return decomposed;
}

 
// Will take ell_max, and basis any (but should it be until max?)
long** rlwe_gadget_ct::decompose(long *in){
    // Decomp c_1. 
    long **decomposed = new long*[gadget_param.ell_any]; 
    for(int i = 0; i < gadget_param.ell_any; ++i){  
        decomposed[i] = gadget_param.param.init_zero_poly(); 
    }     
    utils::signed_decomp(decomposed, in, gadget_param.param.N, gadget_param.basis_any, gadget_param.k_any, gadget_param.ell_any, gadget_param.param.Q);
    return decomposed;
}
 
 
void rlwe_gadget_ct::multisum(long *out, long** arr, fftw_complex **c_arr){
     fftw_complex *multisum_eval = new fftw_complex[gadget_param.param.engine->plan_size]; 
    fftw_complex *prod = new fftw_complex[gadget_param.param.engine->plan_size];  
    // FFT Decomposed c_1: 
    //double scale = 2.0 * param.N;
    gadget_param.param.engine->to_eval_form(multisum_eval, arr[0]);   
    gadget_param.param.engine->mul_eval_form(multisum_eval, multisum_eval, c_arr[0]);  
    // let get the multisum_eval back and see whether its OK.   
    for(int i = 1; i < gadget_param.ell; ++i){ 
        gadget_param.param.engine->to_eval_form(prod, arr[i]);    
        gadget_param.param.engine->mul_eval_form(prod, prod, c_arr[i]); 
        gadget_param.param.engine->add_eval_form(multisum_eval, multisum_eval, prod); 
    } 

    long* coef_form = new long[gadget_param.param.engine->plan_size]; 
    gadget_param.param.engine->to_coef_form(coef_form, multisum_eval);  
    mod_reduce(out, coef_form);
 
    delete[] multisum_eval;
    delete[] prod;
    delete[] coef_form;
}
   

void rlwe_gadget_ct::multisum_any(long *out, long** arr, fftw_complex **c_arr){
     fftw_complex *multisum_eval = new fftw_complex[gadget_param.param.engine->plan_size]; 
    fftw_complex *prod = new fftw_complex[gadget_param.param.engine->plan_size];  
    // FFT Decomposed c_1: 
    //double scale = 2.0 * param.N;
    gadget_param.param.engine->to_eval_form(multisum_eval, arr[0]);   
    gadget_param.param.engine->mul_eval_form(multisum_eval, multisum_eval, c_arr[0]);  
    // let get the multisum_eval back and see whether its OK.   
    for(int i = 1; i < gadget_param.ell_any; ++i){ 
        gadget_param.param.engine->to_eval_form(prod, arr[i]);    
        gadget_param.param.engine->mul_eval_form(prod, prod, c_arr[2*i]); 
        gadget_param.param.engine->add_eval_form(multisum_eval, multisum_eval, prod); 
    } 

    long* coef_form = new long[gadget_param.param.engine->plan_size]; 
    gadget_param.param.engine->to_coef_form(coef_form, multisum_eval);  
    mod_reduce(out, coef_form);
 
    delete[] multisum_eval;
    delete[] prod;
    delete[] coef_form;
}



void rlwe_gadget_ct::mod_reduce(long *out_poly, long *in_poly){
    for(int i = 0; i < gadget_param.param.engine->N; ++i){  
          // TODO Power of two modulus reduction!!!
      //out_poly[i] = in_poly[i] % gadget_param.param.Q;
      out_poly[i] = in_poly[i] & this->mask; 
   }
}

 
void rlwe_gadget_ct::mod_reduce(long *out_poly, long double *in_poly_l){
      //long double coef;
      long double Q_l = (long double) gadget_param.param.Q;
      for(int i = 0; i < gadget_param.param.engine->N; ++i){  
      out_poly[i] = round(fmodl(in_poly_l[i], Q_l));  
   }
}

 


rlwe_gadget_param::rlwe_gadget_param(){}
    
rlwe_gadget_param::rlwe_gadget_param(rlwe_param &rlwe_par, int basis, double stddev_simul){
    this->param = rlwe_par;

    // This basis is for simul (its smaller than basis_any, and when using this one, blind rotation is less efficient)
    this->basis = basis;
    this->k = 1;
    // Compute the k, parameter (remind k is such that basis**k = Q)
    this->stddev_simul = stddev_simul;
    gadget_rand = sample(0.0, stddev_simul);
    long temp = 2;
    while(temp < basis){
        temp *= 2;
        this->k++;
    }
    this->ell = 1;
    temp = basis; 
    while(temp < this->param.Q){
        temp *= basis;
        this->ell++;
    }

    // Set the parameters for any
    this->basis_any = basis * basis;
    this->k_any = k*2; 
    this->ell_any = 1;
    temp = basis_any; 
    while(temp < this->param.Q){
        temp *= basis_any;
        this->ell_any++;
    }

    if(2 * ell_any >= ell){
        this->ell_max = 2 * ell_any;
    }else{
        this->ell_max = ell;
    }

    std::cout << "basis: " << basis << std::endl;
    std::cout << "ell: " << ell << std::endl;
    std::cout << "k: " << k << std::endl;
    std::cout << "basis_any: " << basis_any << std::endl;
    std::cout << "ell_any: " << ell_any << std::endl;
    std::cout << "k_any: " << k_any << std::endl;
    std::cout << "ell_max: " << ell_max << std::endl;
  
}