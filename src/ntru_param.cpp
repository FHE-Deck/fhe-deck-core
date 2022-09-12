/*
PLEASE DO NOT DISTRIBUTE!!! This version is for review only. 
*/

#include "../include/ntru_param.h"
#include "../include/utils.h"

ntru_param::~ntru_param(){
      // TODO: Need to delete the fft_plan I guess.
} 

ntru_param::ntru_param(){} 

ntru_param::ntru_param(ring_type ring, int N, long Q, double stddev){ 
      this->Q = Q; 
      this->N = N; 
      this->stddev = stddev; 
      this->ring = ring; 
      engine = new fft_plan(ring, N);    
} 



ntru_param::ntru_param(ring_type ring, int N, long Q, double stddev, bool extended_arithmetic){ 
      this->Q = Q; 
      this->N = N; 
      this->stddev = stddev; 
      this->ring = ring; 
      engine = new fft_plan(ring, N, extended_arithmetic);   
} 
  


long* ntru_param::init_poly(){
       return new long[this->N]; 
}

long* ntru_param::init_zero_poly(){
      long *out = new long[this->N];
      for(int i = 0; i < this->N; ++i){
            out[i] = 0;
      }
      return out;
}


ntru_param ntru_param::mod_switch(long new_modulus){ 
      return ntru_param(ring, N, new_modulus, stddev, engine->long_arithmetic);
}

fftw_complex* ntru_param::init_fft_poly(){
      return new fftw_complex[engine->plan_size]; 
}


fftwl_complex* ntru_param::init_fft_poly_l(){
      return new fftwl_complex[engine->plan_size]; 
}




ntru_ct::ntru_ct(){}


ntru_ct::ntru_ct(ntru_param &param){ 
      this->param = param;
      this->c = param.init_poly(); 
      this->init=true;
}


ntru_ct::ntru_ct(ntru_param &param, long *c){ 
      this->param = param;
      this->c = c; 
      this->init=true;
}

ntru_ct::ntru_ct(const ntru_ct &other){ 
      param = other.param;
      c = param.init_poly(); 
      this->init=true;
      for(int i = 0; i < param.N; ++i){
        c[i] = other.c[i]; 
    } 
}

ntru_ct::~ntru_ct(){ 
      delete[] c;
}



ntru_ct& ntru_ct::operator=(const ntru_ct other){ 
      param = other.param;
      if(this->init==false){
            c = param.init_poly(); 
      }
      for(int i = 0; i < param.N; ++i){
        c[i] = other.c[i]; 
    } 
      return *this;
}


ntru_ct ntru_ct::negacyclic_rotate(int rot){
    ntru_ct out(param);
    // TODO: For now I implement cyclic rotation because I first need to change the ring!!!
    // WTF!!!???? I think this is no longer used (delete from here)
    utils::rotate_poly(out.c, c, param.N, rot); 
    return out;
}


ntru_ct ntru_ct::add(const ntru_ct *ct){
      ntru_ct out(param);
      add(out.c, c, ct->c);
      return out;
}


ntru_ct ntru_ct::sub(const ntru_ct *ct){ 
      ntru_ct out(param);
      sub(out.c, c, ct->c);
      return out;
}


ntru_ct ntru_ct::neg(){
      ntru_ct out(param);
      neg(out.c, c);
      return out;
}

 
void ntru_ct::add(long *out, long *in_1, long *in_2){
      for(int i = 0; i < param.N; ++i){
            out[i] = (in_1[i] + in_2[i]) % param.Q;
      }
      utils::array_signed_form(out, out, param.N, param.Q);
}
 

void ntru_ct::sub(long *out, long *in_1, long *in_2){
      for(int i = 0; i < param.N; ++i){
            out[i] = (in_1[i] - in_2[i]) % param.Q;
      }
      utils::array_signed_form(out, out, param.N, param.Q);
}
  

void ntru_ct::neg(long *out, long *in){
      for(int i = 0; i < param.N; ++i){
            out[i] =  (-in[i]) % param.Q;
      } 
      utils::array_signed_form(out, out, param.N, param.Q);
}
 
 

ntru_ct ntru_ct::mod_switch(long new_modulus){
      ntru_param out_param = param.mod_switch(new_modulus);
      ntru_ct out(out_param);
      double temp;
      for(int i = 0; i < param.N; ++i){
        temp = (double)new_modulus * (double)c[i]; 
        out.c[i] = (long)round(temp/param.Q); 
      } 
      return out;
}


ntru_ct ntru_ct::mod_switch(ntru_param new_param){
      ntru_ct out(new_param);
      double temp;
      for(int i = 0; i < param.N; ++i){
        temp = (double)new_param.Q * (double)c[i]; 
        out.c[i] = (long)round(temp/param.Q); 
      } 
      return out;
}


std::string ntru_ct::to_string(){
      return utils::to_string(c, param.N);
}


 
ntru_gadget_param::ntru_gadget_param(){}


ntru_gadget_param::ntru_gadget_param(ntru_param &ntru_par, int basis, polynomial_arithmetic arithmetic){
      this->param = ntru_par;
      this->basis = basis; 
      // TODO: Note that for now, we accept only power of two basis (because our decomposition is written this way)
      this->k = 1;
      long temp = 2;
      this->arithmetic = arithmetic;
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
} 

ntru_gadget_ct::~ntru_gadget_ct(){   
      if(init==false)
      {
            return;
      }
      delete[] gadget_ct;
      if(arithmetic == long_double_fft){
            for(int i = 0; i < ell; ++i){
                  delete[] gadget_ct_eval_l[i];
            }
             delete[] gadget_ct_eval_l;
      }else if(arithmetic == double_fft){
            for(int i = 0; i < ell; ++i){
                  delete[] gadget_ct_eval[i];
            }
             delete[] gadget_ct_eval;
      }else if(arithmetic == hexl_ntt){
            for(int i = 0; i < ell; ++i){
                  delete[] gadget_ct_ntt_eval[i];
            }
             delete[] gadget_ct_ntt_eval;
      }else{
            std::cout << "Not Supported Arithmetic" << std::endl;
      }
}

ntru_gadget_ct::ntru_gadget_ct(){}



ntru_gadget_ct::ntru_gadget_ct(ntru_param &ntru_par, int basis, polynomial_arithmetic arithmetic){ 
      this->param = ntru_par;
      this->basis = basis; 
      // TODO: Note that for now, we accept only power of two basis (because our decomposition is written this way)
      this->k = 1;
      long temp = 2;
      while(temp < basis){
            temp *= 2;
            this->k++;
      }
      this->ell = 1;
      temp = basis; 
      while(temp <  this->param.Q){
            temp *= basis;
            this->ell++;
      }
      init_gadget_ct();
      this->arithmetic = arithmetic;
      if(arithmetic == long_double_fft){
            init_gadget_ct_fft_l(); 
      }else if(arithmetic == double_fft){ 
            init_gadget_ct_fft(); 
      }else if(arithmetic == hexl_ntt){ 
            init_gadget_ct_ntt();
            this->ntt = intel::hexl::NTT(param.N, param.Q);
      }else{
            std::cout << "Not Supported Arithmetic" << std::endl;
      } 
      to_eval(); 
      init = true;
}
 

ntru_gadget_ct::ntru_gadget_ct(const ntru_gadget_ct &other){   
      param = other.param; 
      ell = other.ell;
      k = other.k;
      basis = other.basis; 
      init_gadget_ct();
      arithmetic = other.arithmetic;
      if(arithmetic == long_double_fft){
            init_gadget_ct_fft_l(); 
      }else if(arithmetic == double_fft){
            init_gadget_ct_fft(); 
      }else if(arithmetic == hexl_ntt){
            init_gadget_ct_ntt();
            this->ntt = intel::hexl::NTT(param.N, param.Q); 
      }else{
            std::cout << "Not Supported Arithmetic" << std::endl;
      }   
      for(int i = 0; i < ell; ++i){
            utils::cp(gadget_ct[i], other.gadget_ct[i], param.N); 
      } 
      to_eval(); 
      init = true;
}
  
 
ntru_gadget_ct& ntru_gadget_ct::operator=(const ntru_gadget_ct other){    
      param = other.param;
      ell = other.ell;
      k = other.k;
      basis = other.basis; 
      if(init==false){ 
            init_gadget_ct();
      }
      arithmetic = other.arithmetic;
      if(arithmetic == long_double_fft){
            init_gadget_ct_fft_l(); 
      }else if(arithmetic == double_fft){
            init_gadget_ct_fft(); 
      }else if(arithmetic == hexl_ntt){
            init_gadget_ct_ntt();
            this->ntt = intel::hexl::NTT(param.N, param.Q); 
      }else{
            std::cout << "Not Supported Arithmetic" << std::endl;
      } 
      for(int i = 0; i < ell; ++i){
            utils::cp(gadget_ct[i], other.gadget_ct[i], param.N); 
      }
      to_eval();
    return *this;
}  
 
void ntru_gadget_ct::init_gadget_ct(){ 
    gadget_ct = new long*[ell];
    for(int i = 0; i < ell; ++i){
      gadget_ct[i] = param.init_poly();
   }  
}
  
void ntru_gadget_ct::init_gadget_ct_fft(){ 
    gadget_ct_eval = new fftw_complex*[ell];
    for(int i = 0; i < ell; ++i){ 
      gadget_ct_eval[i] = param.init_fft_poly();
   } 
}
 
void ntru_gadget_ct::init_gadget_ct_fft_l(){ 
    gadget_ct_eval_l = new fftwl_complex*[ell];
    for(int i = 0; i < ell; ++i){
      gadget_ct_eval_l[i] = param.init_fft_poly_l();
   } 
}


void ntru_gadget_ct::init_gadget_ct_ntt(){ 
    gadget_ct_ntt_eval = new long*[ell];
    for(int i = 0; i < ell; ++i){ 
      gadget_ct_ntt_eval[i] = param.init_zero_poly();
   } 
}

void ntru_gadget_ct::delete_gadget_ct(long** ct){
      for(int i = 0; i < ell; ++i){
            delete[] ct[i];
      }
      delete[] ct;
}

void ntru_gadget_ct::delete_gadget_ct_fft(fftw_complex** ct){
      for(int i = 0; i < ell; ++i){
            delete[] ct[i];
      }
      delete[] ct;
}

void ntru_gadget_ct::delete_gadget_ct_fft(fftwl_complex** ct){
      for(int i = 0; i < ell; ++i){
            delete[] ct[i];
      }
      delete[] ct;
}

 
void ntru_gadget_ct:: gadget_mul(ntru_ct *out, ntru_ct *c_1){
      gadget_mul(out->c, c_1->c); 
}


void ntru_gadget_ct::gadget_mul(ntru_ct *out, long *scalar){
      gadget_mul(out->c, scalar); 
}

void ntru_gadget_ct::gadget_mul(long *out, long *c_1){ 
      if(arithmetic == long_double_fft)
      {
            gadget_mul_fft(out, c_1, gadget_ct_eval_l);
      }else if(arithmetic == double_fft){ 
            gadget_mul_fft(out, c_1, gadget_ct_eval);
      }else if(arithmetic == hexl_ntt){ 
            gadget_mul_hexl_ntt(out, c_1, gadget_ct_ntt_eval);
      }else{
            std::cout << "Not Supported Arithmetic" << std::endl; 
      }
}
   

void ntru_gadget_ct::gadget_mul_fft(long *out, long *ct_1, fftw_complex **c_2){  
    // Decomp c_1. 
    long **ct_1_decomposed = new long*[ell]; 
    for(int i = 0; i < ell; ++i){  
        ct_1_decomposed[i] = param.init_zero_poly(); 
    }         
    utils::signed_decomp(ct_1_decomposed, ct_1, param.N, basis, k, ell, param.Q);
 
    fftw_complex *multisum_eval = new fftw_complex[param.engine->plan_size]; 
    fftw_complex *prod = new fftw_complex[param.engine->plan_size];  
 
    // FFT Decomposed c_1:   
    param.engine->to_eval_form(multisum_eval, ct_1_decomposed[0]);   
    param.engine->mul_eval_form(multisum_eval, multisum_eval, c_2[0]);  
  
      // let get the multisum_eval back and see whether its OK.   
    for(int i = 1; i < ell; ++i){   
        param.engine->to_eval_form(prod, ct_1_decomposed[i]);    
        param.engine->mul_eval_form(prod, prod, c_2[i]); 
        param.engine->add_eval_form(multisum_eval, multisum_eval, prod); 
    } 
  
    long* coef_form = new long[param.engine->plan_size]; 
    param.engine->to_coef_form(coef_form, multisum_eval);  
    utils::mod_reduce(out, coef_form, param.Q, param.engine->N);  

      for(int i = 0; i < ell; ++i){
      delete[] ct_1_decomposed[i];
    }
    delete[] ct_1_decomposed;
    delete[] multisum_eval;
    delete[] prod;
    delete[] coef_form; 
} 
 

void ntru_gadget_ct::gadget_mul_fft(long *out, long *ct_1, fftwl_complex **c_2){ 
    // Decomp c_1. 
    long **ct_1_decomposed = new long*[ell]; 
    for(int i = 0; i < ell; ++i){  
        ct_1_decomposed[i] = param.init_zero_poly(); 
    }     
    utils::signed_decomp(ct_1_decomposed, ct_1, param.N, basis, k, ell, param.Q);
 
    fftwl_complex *multisum_eval = new fftwl_complex[param.engine->plan_size]; 
    fftwl_complex *prod = new fftwl_complex[param.engine->plan_size];  
    // FFT Decomposed c_1:  
    param.engine->to_eval_form_l(multisum_eval, ct_1_decomposed[0]);   
    param.engine->mul_eval_form_l(multisum_eval, multisum_eval, c_2[0]);  
      // let get the multisum_eval back and see whether its OK.   
    for(int i = 1; i < ell; ++i){ 
        param.engine->to_eval_form_l(prod, ct_1_decomposed[i]);    
        param.engine->mul_eval_form_l(prod, prod, c_2[i]); 
        param.engine->add_eval_form_l(multisum_eval, multisum_eval, prod); 
    } 
  
    long double* coef_form = new long double[param.engine->plan_size];  
    param.engine->to_coef_form_l(coef_form, multisum_eval);    
    utils::mod_reduce(out, coef_form, param.Q, param.engine->N); 
    
    for(int i = 0; i < ell; ++i){
      delete[] ct_1_decomposed[i];
    }
    delete[] ct_1_decomposed;
    delete[] multisum_eval;
    delete[] prod;
    delete[] coef_form;  
} 


void ntru_gadget_ct::gadget_mul_hexl_ntt(long *out, long *ct_1, long **c_2){   
    // Decomp c_1. 
    long **ct_1_decomposed = new long*[ell]; 
    for(int i = 0; i < ell; ++i){  
        ct_1_decomposed[i] = param.init_zero_poly(); 
    }     
    utils::signed_decomp(ct_1_decomposed, ct_1, param.N, basis, k, ell, param.Q);
      for(int i = 0; i < ell; ++i){  
       utils::array_mod_form(ct_1_decomposed[i], ct_1_decomposed[i], param.N, param.Q);
    }  
 
      long* multisum_eval = param.init_zero_poly();
      long* prod = param.init_zero_poly();
 
      ntt.ComputeForward((uint64_t*) prod, (uint64_t*) ct_1_decomposed[0], 1, 1);
      intel::hexl::EltwiseMultMod((uint64_t*) multisum_eval, (uint64_t*) prod, (uint64_t*) c_2[0], param.N, param.Q, 1); 
 

    for(int i = 1; i < ell; ++i){  
      ntt.ComputeForward((uint64_t*) prod, (uint64_t*) ct_1_decomposed[i], 1, 1);
      intel::hexl::EltwiseMultMod((uint64_t*) prod, (uint64_t*) prod, (uint64_t*) c_2[i], param.N, param.Q, 1);
      intel::hexl::EltwiseAddMod((uint64_t*) multisum_eval, (uint64_t*) multisum_eval, (uint64_t*) prod, param.N, param.Q);
 
    }    
    ntt.ComputeInverse((uint64_t*) out, (uint64_t*) multisum_eval, 1, 1); 
    for(int i = 0; i < ell; ++i){
      delete[] ct_1_decomposed[i];
    }
    delete[] ct_1_decomposed;
    delete[] multisum_eval;
    delete[] prod;   
} 
 
void ntru_gadget_ct::to_eval(){
      if(arithmetic == long_double_fft){
            for(int i = 0; i < ell; ++i){ 
                  param.engine->to_eval_form_scale_l(gadget_ct_eval_l[i], gadget_ct[i], 2.0); 
            }    
      }else if(arithmetic == double_fft){ 
            for(int i = 0; i < ell; ++i){  
                  param.engine->to_eval_form_scale(gadget_ct_eval[i], gadget_ct[i], 2.0); 
            }    
      }else if(arithmetic == hexl_ntt){ 
            for(int i = 0; i < ell; ++i){ 
                  ntt.ComputeForward((uint64_t*) gadget_ct_ntt_eval[i], (uint64_t*) gadget_ct[i], 1, 1);
            }  
      }else{
            std::cout << "Not Supported Arithmetic" << std::endl;
      }
}
   

void ntru_gadget_ct::to_coef(){
      if(arithmetic == long_double_fft){
            long double** g_ct_coef = new long double*[ell]; 
            for(int i = 0; i < ell; ++i){
                  g_ct_coef[i] = new long double[param.engine->plan_size];
                  param.engine->to_coef_form_l(g_ct_coef[i], gadget_ct_eval_l[i]); 
                  utils::mod_reduce(gadget_ct[i], g_ct_coef[i], param.Q, param.engine->N); 
            }
            for(int i = 0; i < ell; ++i)
                  delete[] g_ct_coef[i];
            delete[] g_ct_coef; 
      }else if(arithmetic == double_fft){
            long** g_ct_coef = new long*[ell]; 
            for(int i = 0; i < ell; ++i){
                  g_ct_coef[i] = new long[param.engine->plan_size];
                  param.engine->to_coef_form(g_ct_coef[i], gadget_ct_eval[i]); 
                  utils::mod_reduce(gadget_ct[i], g_ct_coef[i], param.Q, param.engine->N); 
            }
            for(int i = 0; i < ell; ++i)
                  delete[] g_ct_coef[i];
            delete[] g_ct_coef; 
      }else if(arithmetic == hexl_ntt){
            for(int i = 0; i < ell; ++i){ 
                  ntt.ComputeInverse((uint64_t*) gadget_ct[i], (uint64_t*)  gadget_ct_ntt_eval[i], 1, 1);
            }  
      }else{
            std::cout << "Not Supported Arithmetic" << std::endl;
      }
}

 
