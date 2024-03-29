#include "rotation_poly.h"
 
using namespace fhe_deck;

RotationPoly::~RotationPoly(){
    delete[] this->lookup_polynomial;
}

RotationPoly::RotationPoly(const RotationPoly &poly){ 
    this->lookup_polynomial = new long[poly.N];
    this->output_encoding = poly.output_encoding;
    this->N = poly.N; 
    for(int i = 0; i < this->N; ++i){   
        this->lookup_polynomial[i] = poly.lookup_polynomial[i]; 
    } 
}
 

RotationPoly::RotationPoly(long (*f)(long message, long plaintext_space), long N, PlaintextEncoding output_encoding, bool is_amortized_form){ 
    this->N = N; 
    this->output_encoding = output_encoding;
    this->is_amortized_form = is_amortized_form;
    lookup_polynomial = new long[N]; 
    PlaintextEncoding input_encoding; 
    if(output_encoding.type == full_domain){ 
        input_encoding = PlaintextEncoding(output_encoding.type, output_encoding.plaintext_space, N);
    }else if(output_encoding.type == partial_domain){ 
        input_encoding = PlaintextEncoding(output_encoding.type, output_encoding.plaintext_space, 2*N);
    }else if(output_encoding.type == signed_limied_short_int){
        // Actually I need to have some sort of special encoding here. 
        input_encoding = PlaintextEncoding(signed_limied_short_int_bl, output_encoding.plaintext_space, 2*N);
    }else{
         throw std::logic_error("Non existend encoding type!");
    }

    long arg;
    int i = N-1; 
    while(input_encoding.decode_message(i) == 0){ 
            arg = f(input_encoding.decode_message(i), input_encoding.plaintext_space); 
            lookup_polynomial[N-i-1] = output_encoding.encode_message(arg); 
            i--;
    }
    while(i >= 0){ 
        arg = f(input_encoding.decode_message(i), input_encoding.plaintext_space); 
        lookup_polynomial[N-i-1] = output_encoding.encode_message(-arg);  
        i--;
    } 
}


RotationPoly::RotationPoly(long (*f)(long message), long N, PlaintextEncoding output_encoding, bool is_amortized_form){
    this->N = N; 
    this->output_encoding = output_encoding;
    this->is_amortized_form = is_amortized_form;
    lookup_polynomial = new long[N];
     
    PlaintextEncoding input_encoding; 
    if(output_encoding.type == full_domain){ 
        input_encoding = PlaintextEncoding(output_encoding.type, output_encoding.plaintext_space, N);
    }else if(output_encoding.type == partial_domain){ 
        input_encoding = PlaintextEncoding(output_encoding.type, output_encoding.plaintext_space, 2*N);
    }else if(output_encoding.type == signed_limied_short_int){ 
        input_encoding = PlaintextEncoding(signed_limied_short_int_bl, output_encoding.plaintext_space, 2*N);
    }
 
    long arg;
    int i = N-1;  
    long last_decoded = 0;
    while(input_encoding.decode_message(i) == 0){  
            arg = f(input_encoding.decode_message(i));  
 
            lookup_polynomial[N-i-1] = output_encoding.encode_message(arg) ; 
            i--;
    }
    while(i >= 0){  
        arg = f(input_encoding.decode_message(i));
     
        lookup_polynomial[N-i-1] = output_encoding.encode_message(-arg);  
        i--;
    } 
}
 

RotationPoly::RotationPoly(long* lookup_polynomial, long N, PlaintextEncoding output_encoding, bool is_amortized_form){
    this->N = N; 
    this->output_encoding = output_encoding;
    this->is_amortized_form = is_amortized_form;
    this->lookup_polynomial = new long[N];
    for(int i = 0; i < N; ++i){  
         this->lookup_polynomial[i] = lookup_polynomial[i];
    } 
}
 
void RotationPoly::encode(){
    if(is_encoded){
        return;
    } 
    PlaintextEncoding input_encoding(output_encoding.type, output_encoding.plaintext_space, 2*N);
    int i = N-1; 
    while(input_encoding.decode_message(i) == 0){  
            lookup_polynomial[N-i-1] = output_encoding.encode_message(lookup_polynomial[N-i-1]); 
            i--;
    }
    while(i >= 0){ 
        lookup_polynomial[N-i-1] = output_encoding.encode_message(lookup_polynomial[N-i-1]); 
        i--;
    } 
    is_encoded = true;
}

 void RotationPoly::decode(){
    if(!is_encoded){
        return;
    }
    for(int i = 0; i < N; ++i){  
         this->lookup_polynomial[i] = output_encoding.decode_message(lookup_polynomial[i]);
    } 
    is_encoded = false;
}



void RotationPoly::to_amortization_form(){
    if(is_amortized_form){
        return;
    }
    if(is_encoded){
        decode();   
    }
    Utils::array_mod_form(this->lookup_polynomial, this->lookup_polynomial, N, output_encoding.ciphertext_modulus); 
    is_amortized_form = true;
}

void RotationPoly::to_non_amortized_form(){
    if(!is_amortized_form){
        return;
    }
    Utils::array_signed_form(this->lookup_polynomial, this->lookup_polynomial, N, output_encoding.ciphertext_modulus); 
    if(!is_encoded){
        encode();   
    }
    is_amortized_form = false;
}
 

void RotationPoly::set_polynomial(long* lookup_polynomial, long (*f)(long message), long t, long N, long Q){
    long delta_Q_t = (long)round((double)Q/(double)t);  
    double scale = (double)t/N;
    long arg; 
    for(int i = 0; i < N; ++i){  
            // Compute  your function here
        arg = f(round(scale * i)); 
        lookup_polynomial[N-i-1] = Utils::integer_mod_form(-delta_Q_t *  arg, Q); 
    } 
}

 
long* RotationPoly::rot_identity(int t, long N, long Q){
    auto id = [](long m) -> long {
        return m;
    }; 
    long* acc = new long[N]; 
    set_polynomial(acc, id, t, N, Q);
    return acc; 
}
   

/* Note: this doesn't realy compute the sign function. For zero for example it computes 1
*/
long* RotationPoly::rot_msb(int t, long N, long Q){
    long delta_Q_t = (long)round((double)Q/(double)t); 
    long* acc = new long[N]; 
    for(int i = 0; i < N; ++i){
        acc[i] =  Utils::integer_mod_form(delta_Q_t * -1, Q); 
    } 
    return acc;
}

long* RotationPoly::rot_one(long N){
    long* acc = new long[N]; 
    for(int i = 0; i < N; ++i){
        acc[i] =  0;
    }  
    return acc;
}


// Computes the a univariate polynomial (should be used only with functional bootstrapping, for the negacyclic bootstrap this will output some nonsense)
long* RotationPoly::rot_uni_poly(int* poly, int poly_size, int t, long N, long Q){ 
    long delta_Q_t = (long)round((double)Q/(double)t);
    long delta_N_t = (long)round((double)N/(double)t);
    long* acc = new long[N];
    double scale = (double)t/N;
    long arg;
    for(int i = 0; i < N; ++i){ 
        arg = Utils::integer_mod_form((long)round(((double)t * i /N)), t);  
        // Compute your function on arg
        // TODO: I think the alg never (or almost never) enters this if, and actually the code in the else is enough
        if(arg == 0 && i > N/2){   
            // Compute  your function here
            arg = Utils::eval_poly_mod(arg, poly, poly_size, t); 
            acc[N-i-1] = delta_Q_t * arg;
            acc[N-i-1] = acc[N-i-1] % Q; 
        }else{
            // Compute  your function here
            arg = Utils::eval_poly_mod(arg, poly, poly_size, t);
            acc[N-i-1] = -delta_Q_t * arg;
            acc[N-i-1] = acc[N-i-1] % Q;

        }
    }
    return acc;
}
 
long* RotationPoly::rot_is_zero_of_poly(int* poly, int poly_size, int t, long N, long Q, int t_out){ 
    // I need a different scale to encode the output of this bootstrap
    // That is, the polynomial is scaled with N/t, but the output (0 or 1) will be encoded with t_out
    long delta_Q_t = (long)round((double)Q/(double)t_out); 
    long* acc = new long[N];
    double scale = (double)t/N;
    long arg;
    for(int i = 0; i < N; ++i){
        arg = Utils::integer_mod_form((long)round(((double)t * i /N)), t);  
        // Compute your function on arg
        // TODO: I think the alg never (or almost never) enters this if, and actually the code in the else is enough
        if(arg == 0 && i > N/2){   
            // Compute  your function here
            arg = Utils::eval_poly_mod(arg, poly, poly_size, t); 
            if(arg == 0){
                acc[N-i-1] =  0; 
            }else{
                acc[N-i-1] = delta_Q_t * 1; 
            }
            acc[N-i-1] = acc[N-i-1] % Q; 
        }else{ 
            // Compute  your function here
            arg = Utils::eval_poly_mod(arg, poly, poly_size, t);

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
long* RotationPoly::rot_is_zero(int t, long N, long Q){
    //std::cout << "======= In rot_uni_poly" << std::endl;
    long delta_Q_t = (long)round((double)Q/(double)t);
    long delta_N_t = (long)round((double)N/(double)t);
    long* acc = new long[N];
    double scale = (double)t/N;
    long arg;
    for(int i = 0; i < N; ++i){
        arg = Utils::integer_mod_form((long)round(((double)t * i /N)), t);  
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
long* RotationPoly::rot_inv_mod(int t, long N, long Q){
    long delta_Q_t = (long)round((double)Q/(double)t);
    long delta_N_t = (long)round((double)N/(double)t);
    long* acc = new long[N];
    double scale = (double)t/N;
    long arg;
 
    for(int i = 0; i < N; ++i){

        arg = Utils::integer_mod_form((long)round(((double)t * i /N)), t);  
        // Compute your function on arg
        if(arg == 0){
            acc[N-i-1] = 0;
        } 
        else{
            // Compute  your function here
            arg = Utils::mod_inv(arg, t);
            acc[N-i-1] = -delta_Q_t * arg;
            acc[N-i-1] = acc[N-i-1] % Q;

        } 
    }
    return acc;
}


 
long* RotationPoly::rot_square_and_div_by_4(int t, long N, long Q){
    long delta_Q_t = (long)round((double)Q/(double)t);
    long delta_N_t = (long)round((double)N/(double)t);
    long* acc = new long[N];
    double scale = (double)t/N;
    long arg;
    for(int i = 0; i < N; ++i){
        arg = Utils::integer_mod_form((long)round(((double)t * i /N)), t);  
        arg = Utils::square_and_div_by_4(arg, t);
            acc[N-i-1] = -delta_Q_t * arg;
            acc[N-i-1] = acc[N-i-1] % Q; 
    }
    return acc;
}







// Function returns the rotation polynomial
// The input t is the plaintext modulus
// Also we have the dimension N of the polynomial and the modulus Q
long* RotationPoly::cyclic_rot_identity(int t, long N, long Q){
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


long* RotationPoly::cyclic_rot_inv_mod(int t, long N, long Q){
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
            arg = Utils::mod_inv(arg, t);
        } 
        acc[N-i-1] =  delta_Q_t * arg;
        acc[N-i-1] = acc[N-i-1] % Q;
    }
    return acc;
}

long* RotationPoly::cyclic_rot_square_and_div_by_4(int t, long N, long Q){
    long delta_Q_t = (long)round((double)Q/(double)t);
    long delta_N_t = (long)round((double)N/(double)t);
    long* acc = new long[N];
    double scale = (double)t/N;
    long arg;
    for(int i = 0; i < N; ++i){
        arg = (long) round(((double)t/N) * i);
        // Compute your function on arg
        arg = Utils::square_and_div_by_4(arg, t);
        acc[N-i-1] =  delta_Q_t * arg;
        acc[N-i-1] = acc[N-i-1] % Q;
    }
    return acc;
}
 


long* RotationPoly::cyclic_rot_uni_poly(int* poly, int poly_size, int t, long N, long Q){
    long delta_Q_t = (long)round((double)Q/(double)t);
    long delta_N_t = (long)round((double)N/(double)t);
    long* acc = new long[N];
    double scale = (double)t/N;
    long arg;
    for(int i = 0; i < N; ++i){
        arg = (long) round(((double)t/N) * i);
        // Compute your function on arg
        arg = Utils::eval_poly_mod(arg, poly, poly_size, t);
        acc[N-i-1] =  delta_Q_t * arg;
        acc[N-i-1] = acc[N-i-1] % Q;
    }
    return acc;
}
