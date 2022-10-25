 

#include "../include/lwe_param.h"
#include <iostream>
 
lwe_param::lwe_param(){}

lwe_param::lwe_param(int n, long Q, key_dist key_d, double stddev){
    this->n = n;
    this->Q = Q;
    this->key_d = key_d;
    this->stddev = stddev;
}
 

lwe_param lwe_param::modulus_switch(long new_modulus){ 
    lwe_param new_param(this->n, new_modulus, this->key_d, this->stddev); 
    return new_param;
}

long* lwe_param::init_ct(){
    return new long[this->n+1]; 
}
  
 
void lwe_param::scalar_mul(long *out, long *ct, long scalar){
    for(int i = 0; i <= n; ++i){
        out[i] = (ct[i] * scalar) % Q;
    }
}

void lwe_param::scalar_mul_lazy(long *out, long *ct, long scalar){
    for(int i = 0; i <= n; ++i){
        out[i] = (ct[i] * scalar);
    }
}

void lwe_param::add(long *out, long *ct_1, long *ct_2){
    for(int i = 0; i <= n; ++i){
        out[i] = (ct_1[i] + ct_2[i]) % Q;
    }
}

void lwe_param::add_lazy(long *out, long *ct_1, long *ct_2){
    for(int i = 0; i <= n; ++i){
        out[i] = (ct_1[i] + ct_2[i]);
    }
}



void lwe_param::switch_modulus(long *out_ct, long *in_ct, lwe_param &new_param){ 
    double temp; 
    for(int i = 0; i < n+1; ++i){
        temp =  new_param.Q *  in_ct[i];
        out_ct[i] = (long)round(temp/(double)Q); 
    }
}

 lwe_gadget_param::lwe_gadget_param(){}

lwe_gadget_param::lwe_gadget_param(lwe_param lwe_par, int basis){
      this->lwe_par = lwe_par;
      this->basis = basis; 
      // Note that for now, we accept only power of two basis (because our decomposition is written this way)
      this->k = 1;
      long temp = 2;
      while(temp < basis){
            temp *= 2;
            this->k++;
      }
      this->ell = 1;
      temp = basis;
       
      while(temp < this->lwe_par.Q){
            temp *= basis;
            this->ell++;
      }
}


long** lwe_gadget_param::init_gadget_ct(){
    long **gadget_ct = new long*[this->ell];
    for(int i = 0; i < this->ell; ++i){
        gadget_ct[i] = this->lwe_par.init_ct();
    } 
    return gadget_ct;
}



void lwe_gadget_param::gadget_mul(long *out_ct, long** gadget_ct, long scalar){
    for(int i = 0; i < lwe_par.n+1; ++i){
        out_ct[i] = 0;
    }
    long *scalar_decomposed = new long[ell]; 
    utils::integer_decomp(scalar_decomposed, scalar, basis, k, ell);
    long *temp_ct = new long[lwe_par.n+1];
    for(int i = 0; i < ell; ++i){
        lwe_par.scalar_mul(temp_ct, gadget_ct[i], scalar_decomposed[i]);
        lwe_par.add(out_ct, out_ct, temp_ct);
    }
    delete[] scalar_decomposed;
    delete[] temp_ct;
}



void lwe_gadget_param::gadget_mul_lazy(long *out_ct, long** gadget_ct, long scalar){  
    for(int i = 0; i < lwe_par.n+1; ++i){
        out_ct[i] = 0;
    }
    long *scalar_decomposed = new long[ell]; 
    utils::integer_decomp(scalar_decomposed, scalar, basis, k, ell);
    if(basis==2){
        for(int i = 0; i < ell; ++i){
            if(scalar_decomposed[i]==1){
                lwe_par.add_lazy(out_ct, out_ct, gadget_ct[i]);
            }
        }
    }else{
        long *temp_ct = new long[lwe_par.n+1];
        for(int i = 0; i < ell; ++i){
            lwe_par.scalar_mul_lazy(temp_ct, gadget_ct[i], scalar_decomposed[i]);
            lwe_par.add_lazy(out_ct, out_ct, temp_ct);
        } 
        delete[] temp_ct;
    } 
    // Modulus reduction only at the  end
    utils::array_mod_form(out_ct, out_ct, lwe_par.n+1, lwe_par.Q); 
    delete[] scalar_decomposed;
}
