#include "../include/rotation_poly.h"
 

rotation_poly::~rotation_poly(){
    delete[] this->lookup_polynomial;
}



rotation_poly::rotation_poly(const rotation_poly &poly){ 
    this->lookup_polynomial = new long[poly.N];
    this->t = poly.t;
    this->N = poly.N;
    this->Q = poly.Q;
    for(int i = 0; i < this->N; ++i){   
        this->lookup_polynomial[i] = poly.lookup_polynomial[i]; 
    } 
}

rotation_poly::rotation_poly(long* lookup_polynomial, long t, long N, long Q){
    this->lookup_polynomial = new long[N];
    this->t = t;
    this->N = N;
    this->Q = Q;
    for(int i = 0; i < N; ++i){   
        this->lookup_polynomial[i] = lookup_polynomial[i]; 
    } 
}


rotation_poly::rotation_poly(long (*f)(long message, long plaintext_space), long t, long N, long Q){
    this->t = t;
    this->N = N;
    this->Q = Q;
    lookup_polynomial = new long[N];
    long delta_Q_t = (long)round((double)Q/(double)t); 
    double scale = (double)t/N;
    long arg;
    for(int i = 0; i < N; ++i){  
            // Compute  your function here
        arg = f(round(scale * i), t); 
        lookup_polynomial[N-i-1] = utils::integer_mod_form(-delta_Q_t *  arg, Q); 
    } 
}


rotation_poly::rotation_poly(long (*f)(long message), long t, long N, long Q){
    this->t = t;
    this->N = N;
    this->Q = Q;
    lookup_polynomial = new long[N];
    set_polynomial(lookup_polynomial, f, t, N, Q);
    /*
    long delta_Q_t = (long)round((double)Q/(double)t); 
    double scale = (double)t/N;
    long arg; 
    for(int i = 0; i < N; ++i){  
            // Compute  your function here
        arg = f(round(scale * i)); 
        lookup_polynomial[N-i-1] = utils::integer_mod_form(-delta_Q_t *  arg, Q); 
    } 
    */
}

void rotation_poly::set_polynomial(long* lookup_polynomial, long (*f)(long message), long t, long N, long Q){
    long delta_Q_t = (long)round((double)Q/(double)t);  
    double scale = (double)t/N;
    long arg; 
    for(int i = 0; i < N; ++i){  
            // Compute  your function here
        arg = f(round(scale * i)); 
        lookup_polynomial[N-i-1] = utils::integer_mod_form(-delta_Q_t *  arg, Q); 
    } 
}


 
long* rotation_poly::rot_identity(int t, long N, long Q){
    auto id = [](long m) -> long {
        return m;
    }; 
    long* acc = new long[N]; 
    set_polynomial(acc, id, t, N, Q);
    return acc; 
}
  

void rotation_poly::flip_scale(){
    if(is_scaled){
        double scale = (double)t/Q; 
        for(int i = 0; i < N; ++i){   
            lookup_polynomial[i] = utils::integer_mod_form(scale * lookup_polynomial[i], t); 
        }
        is_scaled = false; 
    }else{
        double scale = (long)round((double)Q/(double)t); 
        for(int i = 0; i < N; ++i){   
            lookup_polynomial[i] = utils::integer_mod_form(round(scale * lookup_polynomial[i]), Q); 
        }
        is_scaled = true;
    }
}


/* Note: this doesn't realy compute the sign function. For zero for example it computes 1
*/
long* rotation_poly::rot_msb(int t, long N, long Q){
    long delta_Q_t = (long)round((double)Q/(double)t); 
    long* acc = new long[N]; 
    for(int i = 0; i < N; ++i){
        acc[i] =  utils::integer_mod_form(delta_Q_t * -1, Q); 
    } 
    return acc;
}

long* rotation_poly::rot_one(long N){
    long* acc = new long[N]; 
    for(int i = 0; i < N; ++i){
        acc[i] =  0;
    }  
    return acc;
}


// Computes the a univariate polynomial (should be used only with functional bootstrapping, for the negacyclic bootstrap this will output some nonsense)
long* rotation_poly::rot_uni_poly(int* poly, int poly_size, int t, long N, long Q){ 
    long delta_Q_t = (long)round((double)Q/(double)t);
    long delta_N_t = (long)round((double)N/(double)t);
    long* acc = new long[N];
    double scale = (double)t/N;
    long arg;
    for(int i = 0; i < N; ++i){ 
        arg = utils::integer_mod_form((long)round(((double)t * i /N)), t);  
        // Compute your function on arg
        // TODO: I think the alg never (or almost never) enters this if, and actually the code in the else is enough
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



long* rotation_poly::rot_is_zero_of_poly(int* poly, int poly_size, int t, long N, long Q, int t_out){ 
    // I need a different scale to encode the output of this bootstrap
    // That is, the polynomial is scaled with N/t, but the output (0 or 1) will be encoded with t_out
    long delta_Q_t = (long)round((double)Q/(double)t_out); 
    long* acc = new long[N];
    double scale = (double)t/N;
    long arg;
    for(int i = 0; i < N; ++i){
        arg = utils::integer_mod_form((long)round(((double)t * i /N)), t);  
        // Compute your function on arg
        // TODO: I think the alg never (or almost never) enters this if, and actually the code in the else is enough
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
// NOTE: The function returns 1 on input 0, and 0 otherwise
long* rotation_poly::rot_is_zero(int t, long N, long Q){
    //std::cout << "======= In rot_uni_poly" << std::endl;
    long delta_Q_t = (long)round((double)Q/(double)t);
    long delta_N_t = (long)round((double)N/(double)t);
    long* acc = new long[N];
    double scale = (double)t/N;
    long arg;
    for(int i = 0; i < N; ++i){
        arg = utils::integer_mod_form((long)round(((double)t * i /N)), t);  
        // Compute your function on arg
        // TODO Shouldn't this be || instead of &&?
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


// Return a rotation polynomial for the functional bootstrapping that computes the modular inverse
long* rotation_poly::rot_inv_mod(int t, long N, long Q){
    long delta_Q_t = (long)round((double)Q/(double)t);
    long delta_N_t = (long)round((double)N/(double)t);
    long* acc = new long[N];
    double scale = (double)t/N;
    long arg;
 
    for(int i = 0; i < N; ++i){

        arg = utils::integer_mod_form((long)round(((double)t * i /N)), t);  
        // Compute your function on arg
        if(arg == 0){
            acc[N-i-1] = 0;
        } 
        else{
            // Compute  your function here
            arg = utils::mod_inv(arg, t);
            acc[N-i-1] = -delta_Q_t * arg;
            acc[N-i-1] = acc[N-i-1] % Q;

        } 
    }
    return acc;
}


 
long* rotation_poly::rot_square_and_div_by_4(int t, long N, long Q){
    long delta_Q_t = (long)round((double)Q/(double)t);
    long delta_N_t = (long)round((double)N/(double)t);
    long* acc = new long[N];
    double scale = (double)t/N;
    long arg;
    for(int i = 0; i < N; ++i){
        arg = utils::integer_mod_form((long)round(((double)t * i /N)), t);  
        arg = utils::square_and_div_by_4(arg, t);
            acc[N-i-1] = -delta_Q_t * arg;
            acc[N-i-1] = acc[N-i-1] % Q; 
    }
    return acc;
}







// Function returns the rotation polynomial
// The input t is the plaintext modulus
// Also we have the dimension N of the polynomial and the modulus Q
long* rotation_poly::cyclic_rot_identity(int t, long N, long Q){
    long delta_Q_t = (long)round((double)Q/(double)t);
    long delta_N_t = (long)round((double)N/(double)t);
    long* acc = new long[N];
    double scale = (double)t/N;
    for(int i = 0; i < N; ++i){
        acc[N-i-1] =  delta_Q_t * round(scale * i) ;
        acc[N-i-1] = acc[N-i-1] % Q;
    }
    return acc;
}


long* rotation_poly::cyclic_rot_inv_mod(int t, long N, long Q){
    long delta_Q_t = (long)round((double)Q/(double)t);
    long delta_N_t = (long)round((double)N/(double)t);
    long* acc = new long[N];
    double scale = (double)t/N;
    long arg;
    for(int i = 0; i < N; ++i){
        arg = (long) round(((double)t/N) * i) % t;
        // Compute your function on arg 
        if(arg == 0){
            arg = 0;
        }else{
            arg = utils::mod_inv(arg, t);
        } 
        acc[N-i-1] =  delta_Q_t * arg;
        acc[N-i-1] = acc[N-i-1] % Q;
    }
    return acc;
}

long* rotation_poly::cyclic_rot_square_and_div_by_4(int t, long N, long Q){
    long delta_Q_t = (long)round((double)Q/(double)t);
    long delta_N_t = (long)round((double)N/(double)t);
    long* acc = new long[N];
    double scale = (double)t/N;
    long arg;
    for(int i = 0; i < N; ++i){
        arg = (long) round(((double)t/N) * i);
        // Compute your function on arg
        arg = utils::square_and_div_by_4(arg, t);
        acc[N-i-1] =  delta_Q_t * arg;
        acc[N-i-1] = acc[N-i-1] % Q;
    }
    return acc;
}
 


long* rotation_poly::cyclic_rot_uni_poly(int* poly, int poly_size, int t, long N, long Q){
    long delta_Q_t = (long)round((double)Q/(double)t);
    long delta_N_t = (long)round((double)N/(double)t);
    long* acc = new long[N];
    double scale = (double)t/N;
    long arg;
    for(int i = 0; i < N; ++i){
        arg = (long) round(((double)t/N) * i);
        // Compute your function on arg
        arg = utils::eval_poly_mod(arg, poly, poly_size, t);
        acc[N-i-1] =  delta_Q_t * arg;
        acc[N-i-1] = acc[N-i-1] % Q;
    }
    return acc;
}