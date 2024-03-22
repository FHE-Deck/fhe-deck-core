#include "rlwe.h"

using namespace fhe_deck;

 


RLWECT::RLWECT(std::shared_ptr<RLWEParam> param){
    this->param = param; 
    a = this->param->init_poly();
    b = this->param->init_poly();  
    is_init = true;
}
 
  
RLWECT::~RLWECT(){    
    if(!is_init){ 
        return;
    }   
    //delete[] a;  
    //delete[] b;   
}
 
RLWECT::RLWECT(const RLWECT &other){ 
    this->param = other.param;
    this->a = other.a;
    this->b = other.b; 
    this->is_init = true;
    if(other.is_engine_set){
        set_computing_engine();
    } 
}
 
RLWECT& RLWECT::operator=(const RLWECT other){  
    if (this == &other)
    {
        return *this;
    }  
    // TODO Eventualy this if, else will not be necessary after throwing out the computing from RLWECT.
    if(is_init && (this->param->N == other.param->N)){ 
        this->a = other.a;
        this->b = other.b; 
    }else if(is_init==false){  
        param = other.param; 
        this->a = other.a;
        this->b = other.b; 
        this->is_init = true;  
    }else{
        throw std::logic_error("Wrong case in rlwe_ct::operator=");
    }
    if(other.is_engine_set){
        set_computing_engine();
    }
    return *this;
}



void RLWECT::set_computing_engine(){
    if(param->arithmetic == double_fft){ 
        engine = FFTPlan(param->ring, param->N, false);   
    }else if(param->arithmetic == long_double_fft){
        engine = FFTPlan(param->ring, param->N, true);   
    }
    else if(param->arithmetic == hexl_ntt){
        ntt = intel::hexl::NTT(param->N, param->Q);
    }else if(param->arithmetic == ntl){
        // Do nothing here
    }else{
        throw std::logic_error("Non existent polynomial multiplication engine!");
    }
    is_engine_set = true;
}


void RLWECT::negacyclic_rotate(RLWECT *out, int rot){   
    a.negacyclic_rotate(&out->a, rot);
    b.negacyclic_rotate(&out->b, rot); 
}


void RLWECT::add(RLWECT *out, RLWECT *ct){ 
    ct->a.add(&out->a, &a);
    ct->b.add(&out->b, &b);  
}
 
 

void RLWECT::add(RLWECT *out, Polynomial *x){
    b.add(&out->b, x); 
}


void RLWECT::sub(RLWECT *out, RLWECT *ct){  
    a.sub(&out->a, &ct->a);
    b.sub(&out->b, &ct->b); 
}
 

void RLWECT::sub(RLWECT *out, Polynomial *x){
    b.sub(&out->b, x);  
}

void RLWECT::neg(RLWECT *out){ 
    a.neg(&out->a);
    b.neg(&out->b); 
}
 

  

void RLWECT::mul(RLWECT *out, Polynomial *x){ 
    this->a.mul(&out->a, x, param->mul_engine);
    this->b.mul(&out->b, x, param->mul_engine); 
}


std::string RLWECT::to_string(){
    std::string out = "[" + Utils::to_string(b.coefs, param->N) + ", " + Utils::to_string(a.coefs, param->N) + "]";
    return out;
}
 
  
void RLWECT::add(long *out, long *in_1, long *in_2){
    // Assert in_1 and in_2 are in mod form
      for(int i = 0; i < param->N; ++i){
            out[i] = (in_1[i] + in_2[i]) % param->Q; 
      } 
}

long* RLWECT::add(long *in_1, long *in_2){
    // Assert in_1 and in_2 are in mod form
    long* out = new long[param->N];
    add(out, in_1, in_2);
    return out;
}


void RLWECT::sub(long *out, long *in_1, long *in_2){
      for(int i = 0; i < param->N; ++i){
            out[i] = in_1[i] - in_2[i]; 
      }
      Utils::array_mod_form(out, out, param->N, param->Q);
}

long* RLWECT::sub(long *in_1, long *in_2){
      long* out = new long[param->N];
      sub(out, in_1, in_2);
      return out;
}


void RLWECT::neg(long *out, long *in){
    // Assert array in mod form (Assert 0 <= in[i] < Q)
      for(int i = 0; i < param->N; ++i){
            out[i] =  param->Q-in[i]; 
      }  
}

long* RLWECT::neg(long *in){
      long* out = new long[param->N];
      neg(out, in);
      return out;
} 
  

void RLWECT::mul(long *out, long *in_1, long *in_2){
    if(param->arithmetic == ntl){
        Utils::mul_mod(out, in_1, param->N, in_2, param->N, param->N, param->Q, negacyclic);
    }else if(param->arithmetic == double_fft){
        mul_fft(out, in_1, in_2);
    }else if(param->arithmetic == hexl_ntt){ 
        mul_ntt(out, in_1, in_2);
    }else if(param->arithmetic == long_double_fft){
        throw std::logic_error("Long Double Arithmetic not supported Yet!");
    }else{
        throw std::logic_error("Non existent polynomial multiplication engine!"); 
    } 
}

void RLWECT::mul_fft(long *out, long* in_1, long *in_2){  
    fftw_complex *eval_in_1 = new fftw_complex[engine.plan_size];  
    fftw_complex *eval_in_2 = new fftw_complex[engine.plan_size];  
    fftw_complex *eval_out = new fftw_complex[engine.plan_size];
    engine.to_eval_form(eval_in_1, in_1); 
    engine.to_eval_form_scale(eval_in_2, in_2, 2.0); 
    engine.mul_eval_form(eval_out, eval_in_1, eval_in_2); 
    engine.to_coef_form(out, eval_out);    
    delete[] eval_in_1;
    delete[] eval_in_2;
    delete[] eval_out;  
}


void RLWECT::mul_ntt(long *out, long *in_1, long *in_2){ 
    long* eval_in_1 = new long[param->N]; 
    long* eval_in_2 = new long[param->N]; 
    long* eval_out = new long[param->N]; 
    ntt.ComputeForward((uint64_t*) eval_in_1, (uint64_t*) in_1, 1, 1);  
    ntt.ComputeForward((uint64_t*) eval_in_2, (uint64_t*) in_2, 1, 1);   
    intel::hexl::EltwiseMultMod((uint64_t*) eval_out, (uint64_t*) eval_in_1, (uint64_t*) eval_in_2, param->N, param->Q, 1); 
    ntt.ComputeInverse((uint64_t*) out, (uint64_t*)  eval_out, 1, 1);  
    delete[] eval_in_1; 
    delete[] eval_in_2; 
    delete[] eval_out; 
}
  

void RLWECT::extract_lwe(long *lwe_ct_out){
    lwe_ct_out[0] = this->b.coefs[0];
    lwe_ct_out[1] = this->a.coefs[0];
    for(int i = 1; i < this->param->N; ++i){
        lwe_ct_out[i+1] = -this->a.coefs[this->param->N - i];
    } 
}

LWECT RLWECT::extract_lwe(std::shared_ptr<LWEParam> lwe_par){ 
    LWECT out(lwe_par);
    this->extract_lwe(out.ct);
    return out; 
}
     
  
RLWEParam::RLWEParam(RingType ring, int N, long Q, KeyDistribution key_type, ModulusType mod_type, double stddev, PolynomialArithmetic arithmetic){
    this->Q = Q;
    this->mod_type = mod_type;
    this->key_type = key_type; 
    this->N = N; 
    this->stddev = stddev; 
    this->ring = ring;  
    this->arithmetic = arithmetic;   
    init_mul_engine();
}
        
RLWEParam::RLWEParam(RLWEParam &other){
    this->Q = other.Q;
    this->mod_type = other.mod_type;
    this->key_type = other.key_type;  
    this->N = other.N; 
    this->stddev = other.stddev; 
    this->ring = other.ring;  
    this->arithmetic = other.arithmetic;   
    // TODO: Need to initialize the multiplication engine here. 
    init_mul_engine();
}

RLWEParam::RLWEParam(int N, long Q, KeyDistribution key_type, ModulusType mod_type, double stddev, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine){
    this->N = N;
    this->Q = Q;
    this->mod_type = mod_type;
    this->key_type = key_type;  
    this->stddev = stddev; 
    this->mul_engine = mul_engine; 
    this->is_mul_engine_init = true;
}


RLWEParam& RLWEParam::operator=(const RLWEParam other){
    this->Q = other.Q;
    this->mod_type = other.mod_type;
    this->key_type = other.key_type;  
    this->N = other.N; 
    this->stddev = other.stddev; 
    this->ring = other.ring;  
    this->arithmetic = other.arithmetic; 
    init_mul_engine();
    return *this;
}


void RLWEParam::init_mul_engine(){ 
    // Build PolynomialMultiplicationEngine
    PolynomialMultiplicationEngineBuilder mul_engine_builder;
    mul_engine_builder.set_coef_modulus(Q); 
    mul_engine_builder.set_degree(N);
    mul_engine_builder.set_polynomial_arithmetic(arithmetic);
    mul_engine_builder.set_ring_type(ring);
    mul_engine_builder.set_modulus_type(mod_type);
    this->mul_engine = mul_engine_builder.build(); 
    this->is_mul_engine_init = true;
}

 

Polynomial RLWEParam::init_poly(){ 
    return Polynomial(N,  Q, mul_engine);; 
}
 

Polynomial RLWEParam::init_zero_poly(){
    Polynomial out(N,  Q, mul_engine);
    for(int i = 0; i < this->N; ++i){
        out.coefs[i] = 0;
    }
    return out;
}
 
 


RLWEGadgetCT::RLWEGadgetCT(std::shared_ptr<RLWEGadgetParam> gadget_param, std::vector<RLWECT> gadget_ct, std::vector<RLWECT> gadget_ct_sk){
    this->gadget_param = gadget_param; 
    //this->gadget_ct = new RLWECT[gadget_param->ell_max];
    //this->gadget_ct_sk = new RLWECT[gadget_param->ell_max];  
    this->gadget_ct = gadget_ct;
    this->gadget_ct_sk = gadget_ct_sk;
    /*
    for(int i = 0; i < gadget_param->ell_max; ++i){ 
        this->gadget_ct[i] = gadget_ct[i];
        this->gadget_ct_sk[i] = gadget_ct_sk[i];
    }   
    */ 
    this->init();
}

void RLWEGadgetCT::init(){   
  
    this->out_minus = RLWECT(gadget_param->rlwe_param); 
    set_computing_engine(); 
    if(gadget_param->rlwe_param->arithmetic == double_fft){
        init_fft_eval(); 
    }else if(gadget_param->rlwe_param->arithmetic == hexl_ntt){ 
        init_ntt_eval(); 
    }else{  
        throw std::logic_error("RLWEGadgetCT::RLWEGadgetCT(std::shared_ptr<RLWEGadgetParam> gadget_param): Non existent polynomial multiplication engine!"); 
    }
    this->to_eval(); 
    
    init_gadget_decomp_tables();  
    set_gadget_decomp_arrays();
 
    // TODO: Set the degree and coef_modulus lokally for readability. 
    // Now Lets initialize here the eval forms. 
    PolynomialArrayCoefForm array_coef(gadget_param->rlwe_param->N,  
                                            gadget_param->rlwe_param->Q,  
                                            gadget_param->ell_any, 
                                            gadget_param->rlwe_param->mul_engine);  
 
    this->array_eval_a = PolynomialArrayEvalForm(gadget_param->rlwe_param->mul_engine, 
                                                gadget_param->ell_any);                                        
    this->array_eval_b = PolynomialArrayEvalForm(gadget_param->rlwe_param->mul_engine, 
                                                gadget_param->ell_any);
    this->array_eval_a_sk = PolynomialArrayEvalForm(gadget_param->rlwe_param->mul_engine, 
                                                gadget_param->ell_any);
    this->array_eval_b_sk = PolynomialArrayEvalForm(gadget_param->rlwe_param->mul_engine, 
                                                gadget_param->ell_any);
 
    for(int i = 0; i < gadget_param->ell_any; ++i){
        array_coef.set_polynomial_at(i, &gadget_ct[i * gadget_param->w_any].a);
    }  
    gadget_param->rlwe_param->mul_engine->to_eval(&this->array_eval_a, &array_coef); 
  
    for(int i = 0; i < gadget_param->ell_any; ++i){
        array_coef.set_polynomial_at(i, &gadget_ct[i * gadget_param->w_any].b);
    }
    gadget_param->rlwe_param->mul_engine->to_eval(&this->array_eval_b, &array_coef); 
  
    for(int i = 0; i < gadget_param->ell_any; ++i){
        array_coef.set_polynomial_at(i, &gadget_ct_sk[i * gadget_param->w_any].a);
    }
    gadget_param->rlwe_param->mul_engine->to_eval(&this->array_eval_a_sk, &array_coef);  
 
    for(int i = 0; i < gadget_param->ell_any; ++i){
        array_coef.set_polynomial_at(i, &gadget_ct_sk[i * gadget_param->w_any].b);
    }
    gadget_param->rlwe_param->mul_engine->to_eval(&this->array_eval_b_sk, &array_coef);  
  
/*
    std::cout << "in init(): verify_eval_forms();" << std::endl;
    
    if(!is_complex_arry_eq(eval_b[0], &array_eval_b.eval_fftw[0],  array_eval_b.size)){
        std::cout << "array_eval_b.size: " << array_eval_b.size << std::endl;
        std::cout << "engine.plan_size: " << engine.plan_size << std::endl;
        std::cout << "&array_eval_b.eval_fftw[2048]: " <<  complex_to_string(&array_eval_b.eval_fftw[2048], 8) << std::endl; 
        std::cout << "eval_b[2048]: " <<  complex_to_string(eval_b[2048], 8) << std::endl; 
        std::cout << "engine.ring: " << engine.ring << std::endl;
        throw std::logic_error("is_complex_arry_eq(&array_eval_b.eval_fftw[2048], eval_b[2048], array_eval_b.size): Fail");
    } 
*/
    //verify_eval_forms();
 
    this->is_init = true; 
}


void RLWEGadgetCT::verify_eval_forms(){

    if(gadget_param->rlwe_param->arithmetic == hexl_ntt){ 
        // TODO: OK lets check first whether the eval forms are actually the same.
        for(int i = 0; i < gadget_param->ell_any; ++i){
            if(!Utils::is_eq_poly(ntt_eval_a[i * gadget_param->w_any], &array_eval_a.eval_long[i * array_eval_a.size], array_eval_a.size)){
                throw std::logic_error("!Utils::is_eq_poly(ntt_eval_a[i], &array_eval_a.eval_long[i * array_eval_a.size], array_eval_a.size): Fail!!!");
            }
        }
        for(int i = 0; i < gadget_param->ell_any; ++i){
            if(!Utils::is_eq_poly(ntt_eval_b[i * gadget_param->w_any], &array_eval_b.eval_long[i * array_eval_b.size], array_eval_b.size)){
                throw std::logic_error("!Utils::is_eq_poly(ntt_eval_b[i], &array_eval_b.eval_long[i * array_eval_b.size], array_eval_b.size): Fail!!!");
            }
        }
        for(int i = 0; i < gadget_param->ell_any; ++i){
            if(!Utils::is_eq_poly(ntt_eval_a_sk[i * gadget_param->w_any], &array_eval_a_sk.eval_long[i * array_eval_a_sk.size], array_eval_a_sk.size)){
                throw std::logic_error("!Utils::is_eq_poly(ntt_eval_a_sk[i], &array_eval_a_sk.eval_long[i * array_eval_a_sk.size], array_eval_a_sk.size): Fail!!!");
            }
        }
        for(int i = 0; i < gadget_param->ell_any; ++i){
            if(!Utils::is_eq_poly(ntt_eval_b_sk[i * gadget_param->w_any], &array_eval_b_sk.eval_long[i * array_eval_b_sk.size], array_eval_b_sk.size)){
                throw std::logic_error("!Utils::is_eq_poly(ntt_eval_b_sk[i], &array_eval_b_sk.eval_long[i * array_eval_b_sk.size], array_eval_b_sk.size): Fail!!!");
            }
        } 
    }
 

    if(gadget_param->rlwe_param->arithmetic == double_fft){ 
        // TODO: OK lets check first whether the eval forms are actually the same.   
        for(int i = 0; i < gadget_param->ell_any; ++i){
            
            if(!is_complex_arry_eq(eval_a[i * gadget_param->w_any], &array_eval_a.eval_fftw[i * array_eval_a.size], array_eval_a.size)){
                throw std::logic_error("!Utils::is_eq_poly(ntt_eval_a[i], &array_eval_a.eval_long[i * array_eval_a.size], array_eval_a.size): Fail!!!");
            }
        }
        for(int i = 0; i < gadget_param->ell_any; ++i){

            if(i == 0){
                std::cout << "now checking for i: 0" << std::endl;
                std::cout << "i * gadget_param->w_any: " << i * gadget_param->w_any << std::endl;
                std::cout << "i * array_eval_b.size: " << i * array_eval_b.size << std::endl;

                if(is_complex_arry_eq(eval_b[i * gadget_param->w_any], &array_eval_b.eval_fftw[i * array_eval_b.size], array_eval_b.size)){
                    std::cout << "Somehow here its equal" << std::endl;
                }
                std::cout << "eval_b[i * gadget_param->w_any]: " << this->complex_to_string(eval_b[i * gadget_param->w_any], 5) << std::endl;
                std::cout << "ev&array_eval_b.eval_fftw[i * array_eval_b.size]: " << this->complex_to_string(&array_eval_b.eval_fftw[i * array_eval_b.size], 5) << std::endl;
            }

            if(!is_complex_arry_eq(eval_b[i * gadget_param->w_any], &array_eval_b.eval_fftw[i * array_eval_b.size], array_eval_b.size)){
                throw std::logic_error("!Utils::is_eq_poly(ntt_eval_b[i], &array_eval_b.eval_long[i * array_eval_b.size], array_eval_b.size): Fail!!!");
            }

            if(i ==0 ){
                std::cout << "For i: no exception. HOW?" << std::endl;
            }
        }
        for(int i = 0; i < gadget_param->ell_any; ++i){
            if(!is_complex_arry_eq(eval_a_sk[i * gadget_param->w_any], &array_eval_a_sk.eval_fftw[i * array_eval_a_sk.size], array_eval_a_sk.size)){
                throw std::logic_error("!Utils::is_eq_poly(ntt_eval_a_sk[i], &array_eval_a_sk.eval_long[i * array_eval_a_sk.size], array_eval_a_sk.size): Fail!!!");
            }
        }
        for(int i = 0; i < gadget_param->ell_any; ++i){
            if(!is_complex_arry_eq(eval_b_sk[i * gadget_param->w_any], &array_eval_b_sk.eval_fftw[i * array_eval_b_sk.size], array_eval_b_sk.size)){
                throw std::logic_error("!Utils::is_eq_poly(ntt_eval_b_sk[i], &array_eval_b_sk.eval_long[i * array_eval_b_sk.size], array_eval_b_sk.size): Fail!!!");
            }
        } 
    }
}


RLWEGadgetCT::~RLWEGadgetCT(){     
    if(is_init == false){
        return;
    }      
    if(gadget_param->rlwe_param->arithmetic == double_fft){ 
        delete_fft_eval(); 
    }else if(gadget_param->rlwe_param->arithmetic == hexl_ntt){ 
        delete_ntt_eval();
    }else{
        // Do nothing
    }  

    // Delete the temporary arrays for gadget decomposition
   
    delete[] simul_ct_a_dec;
    delete[] simul_ct_b_dec;
    delete[] deter_ct_a_dec;
    delete[] deter_ct_b_dec;  
 
}



RLWEGadgetCT::RLWEGadgetCT(const RLWEGadgetCT& other){    
    this->gadget_param = other.gadget_param;
    this->mask = other.mask;  
    out_minus = RLWECT(gadget_param->rlwe_param); 
    gadget_ct = other.gadget_ct;
    gadget_ct_sk = other.gadget_ct_sk;
    if(is_init == false){  
        this->init(); 
    }else{ 
        this->simul_ct_a_dec_poly = other.simul_ct_a_dec_poly;
        this->simul_ct_b_dec_poly = other.simul_ct_b_dec_poly;
        this->deter_ct_a_dec_poly = other.deter_ct_a_dec_poly;
        this->deter_ct_b_dec_poly = other.deter_ct_b_dec_poly;

        init_gadget_decomp_tables(); 
        set_gadget_decomp_arrays();

        for(int i = 0; i < gadget_param->ell_max; ++i){  
            gadget_ct[i] = other.gadget_ct[i];
            gadget_ct_sk[i] =  other.gadget_ct_sk[i]; 
            if(gadget_param->rlwe_param->arithmetic == double_fft){
                for(int j = 0; j < engine.plan_size; ++j){
                    eval_a[i][j][0] = other.eval_a[i][j][0];
                    eval_a[i][j][1] = other.eval_a[i][j][1];
                    eval_b[i][j][0] = other.eval_b[i][j][0];
                    eval_b[i][j][1] = other.eval_b[i][j][1];
                    eval_a_sk[i][j][0] = other.eval_a_sk[i][j][0];
                    eval_a_sk[i][j][1] = other.eval_a_sk[i][j][1];
                    eval_b_sk[i][j][0] = other.eval_b_sk[i][j][0];
                    eval_b_sk[i][j][1] = other.eval_b_sk[i][j][1];
                }
            }else if(gadget_param->rlwe_param->arithmetic == hexl_ntt){ 
                Utils::cp(ntt_eval_a[i], other.ntt_eval_a[i], gadget_param->rlwe_param->N);
                Utils::cp(ntt_eval_b[i], other.ntt_eval_b[i], gadget_param->rlwe_param->N);
                Utils::cp(ntt_eval_a_sk[i], other.ntt_eval_a_sk[i], gadget_param->rlwe_param->N);
                Utils::cp(ntt_eval_b_sk[i], other.ntt_eval_b_sk[i], gadget_param->rlwe_param->N);
            }else{
                throw std::logic_error("Non existent polynomial multiplication engine!"); 
            } 
        }  
    }  
}


RLWEGadgetCT& RLWEGadgetCT::operator=(const RLWEGadgetCT other){  
    this->gadget_param = other.gadget_param;
    this->mask = other.mask;  
    out_minus = RLWECT(gadget_param->rlwe_param); 
    gadget_ct = other.gadget_ct;
    gadget_ct_sk = other.gadget_ct_sk;
    if(is_init == false){ 
        this->init(); 
    }else{ 
        this->array_eval_a = other.array_eval_a;
        this->array_eval_b = other.array_eval_b;
        this->array_eval_a_sk = other.array_eval_a_sk;
        this->array_eval_b_sk = other.array_eval_b_sk;  
 
        init_gadget_decomp_tables(); 
        set_gadget_decomp_arrays();

        for(int i = 0; i < gadget_param->ell_max; ++i){  
            gadget_ct[i] = other.gadget_ct[i];
            gadget_ct_sk[i] =  other.gadget_ct_sk[i]; 
            if(gadget_param->rlwe_param->arithmetic == double_fft){
                for(int j = 0; j < engine.plan_size; ++j){
                    eval_a[i][j][0] = other.eval_a[i][j][0];
                    eval_a[i][j][1] = other.eval_a[i][j][1];
                    eval_b[i][j][0] = other.eval_b[i][j][0];
                    eval_b[i][j][1] = other.eval_b[i][j][1];
                    eval_a_sk[i][j][0] = other.eval_a_sk[i][j][0];
                    eval_a_sk[i][j][1] = other.eval_a_sk[i][j][1];
                    eval_b_sk[i][j][0] = other.eval_b_sk[i][j][0];
                    eval_b_sk[i][j][1] = other.eval_b_sk[i][j][1];
                }
            }else if(gadget_param->rlwe_param->arithmetic == hexl_ntt){ 
                Utils::cp(ntt_eval_a[i], other.ntt_eval_a[i], gadget_param->rlwe_param->N);
                Utils::cp(ntt_eval_b[i], other.ntt_eval_b[i], gadget_param->rlwe_param->N);
                Utils::cp(ntt_eval_a_sk[i], other.ntt_eval_a_sk[i], gadget_param->rlwe_param->N);
                Utils::cp(ntt_eval_b_sk[i], other.ntt_eval_b_sk[i], gadget_param->rlwe_param->N);
            }else{
                throw std::logic_error("Non existent polynomial multiplication engine!"); 
            } 
        }  
    }   
    return *this;
}
 

void RLWEGadgetCT::to_eval(){ 
    if(gadget_param->rlwe_param->arithmetic == double_fft){
        to_eval_fft();
    }else if(gadget_param->rlwe_param->arithmetic == hexl_ntt){
        to_eval_ntt();
    }else{
        throw std::logic_error("Non existent polynomial multiplication engine!"); 
    } 
    /*
    for(int i = 0; i < gadget_param->ell_max; ++i){ 
        gadget_ct[i].a.to_eval();
        gadget_ct[i].b.to_eval();
        gadget_ct_sk[i].a.to_eval();
        gadget_ct_sk[i].b.to_eval(); 
    }
    */
}

void RLWEGadgetCT::to_coef(){
    // TODO: In general to_coef is bulshit.
    // NOTE: That I will never compute on gadget ciphertets themselfev.
    // I will never modify them, so the coefficient form actually always corresponds to the eval.  
    if(gadget_param->rlwe_param->arithmetic == double_fft){
        to_coef_fft();
    }else if(gadget_param->rlwe_param->arithmetic == hexl_ntt){
        to_coef_ntt();
    }else{
        throw std::logic_error("Non existent polynomial multiplication engine!"); 
    } 
    /*
    for(int i = 0; i < gadget_param->ell_max; ++i){ 
        gadget_ct[i].a.to_coef();
        gadget_ct[i].b.to_coef();
        gadget_ct_sk[i].a.to_coef();
        gadget_ct_sk[i].b.to_coef(); 
    }
    */
}
 
void RLWEGadgetCT::mul(RLWECT *out, const RLWECT *ct, GadgetMulMode mode){     
 
    // Compute the multisum here.

    // Depending on whether we do randomized or deterministic:
    // We use either decompose, or gaussian sample.
    if(mode == simul){     
        //simul_ell_delete = gadget_param.ell;
        gadget_param->rand_gadget.sample(simul_ct_a_dec, ct->a.coefs);
        gadget_param->rand_gadget.sample(simul_ct_b_dec, ct->b.coefs); 

        // TODO: Multisum on Polynomials   
        if(gadget_param->rlwe_param->arithmetic == double_fft){ 
            multisum_fft(out->b.coefs, simul_ct_b_dec, eval_b, gadget_param->ell, gadget_param->w);
            multisum_fft(out->a.coefs, simul_ct_b_dec, eval_a, gadget_param->ell, gadget_param->w);
            multisum_fft(out_minus.b.coefs, simul_ct_a_dec, eval_b_sk, gadget_param->ell, gadget_param->w);
            multisum_fft(out_minus.a.coefs, simul_ct_a_dec, eval_a_sk, gadget_param->ell, gadget_param->w);
        }else if(gadget_param->rlwe_param->arithmetic == hexl_ntt){ 
            multisum_ntt(out->b.coefs, simul_ct_b_dec, ntt_eval_b, gadget_param->ell, gadget_param->w);
            multisum_ntt(out->a.coefs, simul_ct_b_dec, ntt_eval_a, gadget_param->ell, gadget_param->w);
            multisum_ntt(out_minus.b.coefs, simul_ct_a_dec, ntt_eval_b_sk, gadget_param->ell, gadget_param->w);
            multisum_ntt(out_minus.a.coefs, simul_ct_a_dec, ntt_eval_a_sk, gadget_param->ell, gadget_param->w);
        }else{
            throw std::logic_error("Non existent polynomial multiplication engine!"); 
        }  
    }else if(mode == deter){   
        // Signed decomposition 
        gadget_param->deter_gadget.sample(deter_ct_a_dec, ct->a.coefs); 
        gadget_param->deter_gadget.sample(deter_ct_b_dec, ct->b.coefs);
          
        //Polynomial::multisum(out->b, deter_ct_b_dec_poly, gadget_ct, gadget_param->ell_any, gadget_param->w_any, gadget_param->rlwe_param->mul_engine);

        // TODO: Multisum on Polynomials    
        /*
        gadget_param->rlwe_param->mul_engine->multisum(&out->b, &deter_ct_b_dec_poly, &array_eval_b);
        gadget_param->rlwe_param->mul_engine->multisum(&out->a, &deter_ct_b_dec_poly, &array_eval_a);
        gadget_param->rlwe_param->mul_engine->multisum(&out_minus.b, &deter_ct_a_dec_poly, &array_eval_b_sk);
        gadget_param->rlwe_param->mul_engine->multisum(&out_minus.a, &deter_ct_a_dec_poly, &array_eval_a_sk);   
        */
        
        if(gadget_param->rlwe_param->arithmetic == double_fft){  
            multisum_fft(out->b.coefs, deter_ct_b_dec, eval_b, gadget_param->ell_any, gadget_param->w_any);
            multisum_fft(out->a.coefs, deter_ct_b_dec, eval_a, gadget_param->ell_any, gadget_param->w_any);
            multisum_fft(out_minus.b.coefs, deter_ct_a_dec, eval_b_sk, gadget_param->ell_any, gadget_param->w_any);
            multisum_fft(out_minus.a.coefs, deter_ct_a_dec, eval_a_sk, gadget_param->ell_any, gadget_param->w_any);

            /*
            std::cout << "In Mul for double_fft: verify_eval_forms(); " << std::endl;
            verify_eval_forms();

            if(!is_complex_arry_eq(eval_b[0], &array_eval_b.eval_fftw[0],  array_eval_b.size)){
                std::cout << "&array_eval_b.eval_fftw[0]: " <<  complex_to_string(&array_eval_b.eval_fftw[0], 5) << std::endl; 
                std::cout << "eval_b[0]: " <<  complex_to_string(eval_b[0], 5) << std::endl; 
                throw std::logic_error("is_complex_arry_eq(&array_eval_b.eval_fftw[0], eval_b[0], array_eval_b.size): Fail");
            }

            multisum_fft_test(out->b.coefs, deter_ct_b_dec, eval_b, gadget_param->ell_any, gadget_param->w_any, &deter_ct_b_dec_poly, &array_eval_b);
            multisum_fft_test(out->a.coefs, deter_ct_b_dec, eval_a, gadget_param->ell_any, gadget_param->w_any, &deter_ct_b_dec_poly, &array_eval_a);
            multisum_fft_test(out_minus.b.coefs, deter_ct_a_dec, eval_b_sk, gadget_param->ell_any, gadget_param->w_any, &deter_ct_a_dec_poly, &array_eval_b_sk);
            multisum_fft_test(out_minus.a.coefs, deter_ct_a_dec, eval_a_sk, gadget_param->ell_any, gadget_param->w_any, &deter_ct_a_dec_poly, &array_eval_a_sk); 
            */
        }else if(gadget_param->rlwe_param->arithmetic == hexl_ntt){  
            
            //multisum_ntt(out->b.coefs, deter_ct_b_dec, ntt_eval_b, gadget_param->ell_any, gadget_param->w_any);
            //multisum_ntt(out->a.coefs, deter_ct_b_dec, ntt_eval_a, gadget_param->ell_any, gadget_param->w_any);
            //multisum_ntt(out_minus.b.coefs, deter_ct_a_dec, ntt_eval_b_sk, gadget_param->ell_any, gadget_param->w_any);
            //multisum_ntt(out_minus.a.coefs, deter_ct_a_dec, ntt_eval_a_sk, gadget_param->ell_any, gadget_param->w_any); 
             

            multisum_ntt_test(out->b.coefs, deter_ct_b_dec, ntt_eval_b, gadget_param->ell_any, gadget_param->w_any, &deter_ct_b_dec_poly, &array_eval_b);
            multisum_ntt_test(out->a.coefs, deter_ct_b_dec, ntt_eval_a, gadget_param->ell_any, gadget_param->w_any, &deter_ct_b_dec_poly, &array_eval_a);
            multisum_ntt_test(out_minus.b.coefs, deter_ct_a_dec, ntt_eval_b_sk, gadget_param->ell_any, gadget_param->w_any, &deter_ct_a_dec_poly, &array_eval_b_sk);
            multisum_ntt_test(out_minus.a.coefs, deter_ct_a_dec, ntt_eval_a_sk, gadget_param->ell_any, gadget_param->w_any, &deter_ct_a_dec_poly, &array_eval_a_sk);  
        }else{
            throw std::logic_error("Non existent polynomial multiplication engine!"); 
        }      
    }  
    out->add(out, &out_minus); 
}
 

bool RLWEGadgetCT::is_complex_arry_eq(fftw_complex* in_1, fftw_complex* in_2, int size){
    for(int i = 0; i < size; ++i){
        if(in_1[i][0] != in_2[i][0]){
            std::cout << ":is_complex_arry_eq fail at: " << i << std::endl;
            return false;
        }
        if(in_1[i][1] != in_2[i][1]){
            std::cout << ":is_complex_arry_eq fail at: " << i << std::endl;
            return false;
        }
    }
    return true;
}

std::string RLWEGadgetCT::complex_to_string(fftw_complex* in, int size){
    if(size == 0){
        return "[]";
    }
    if(size == 1){
        return "[" + std::to_string(in[0][0]) + ", " + std::to_string(in[0][1]) + "]";
    }
    std::string out = "[";
    for(int i = 0; i < size-1; ++i){
        out += "[" + std::to_string(in[i][0]) + ", " + std::to_string(in[i][1]) + "], "; 
    } 
    out += "[" + std::to_string(in[size-1][0]) + ", " + std::to_string(in[size-1][1]) + "]";
    return out;
}
 

void RLWEGadgetCT::multisum_fft_test(long *out, long** arr, fftw_complex **c_arr, int ell, int w, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2){ 
    
    long* in_1_temp = &in_1->poly_array[0];
    fftw_complex* in_2_temp = &in_2->eval_fftw[0];
    fftw_complex* fft_prod_new = new fftw_complex[in_2->size]; 
    fftw_complex* fft_multisum_eval_new = new fftw_complex[in_2->size]; 
    long* out_new = new long[in_1->degree];

    if(in_2->array_size != ell){ 
        throw std::logic_error("in_2->array_size != ell: Fail");
    } 
    verify_eval_forms();

    if(!Utils::is_eq_poly(in_1_temp, arr[0], in_1->degree)){
        throw std::logic_error("!Utils::is_eq_poly(in_1_temp, arr[0], in_1->degree): Fail");
    }
  
    if(!is_complex_arry_eq(in_2_temp, c_arr[0], in_2->size)){ 
        throw std::logic_error("!is_complex_arry_eq(in_2_temp, c_arr[0], in_2->size): Fail");
    }

    // New
    engine.to_eval_form(fft_multisum_eval_new, in_1_temp);   
    engine.mul_eval_form(fft_multisum_eval_new, fft_multisum_eval_new, in_2_temp);  
    
    // Old
    engine.to_eval_form(fft_multisum_eval, arr[0]);   
    engine.mul_eval_form(fft_multisum_eval, fft_multisum_eval, c_arr[0]);  
  
    if(!is_complex_arry_eq(fft_multisum_eval_new, fft_multisum_eval, in_2->size)){
        throw std::logic_error("!is_complex_arry_eq(fft_multisum_eval_new, fft_multisum_eval, in_2->size): Fail");
    }

    for(int i = 1; i < ell; ++i){ 
        // new
        in_1_temp = &in_1->poly_array[i * in_1->degree];
        in_2_temp = &in_2->eval_fftw[i * in_2->size]; 
        engine.to_eval_form(fft_prod_new, in_1_temp);  
        engine.mul_eval_form(fft_prod_new, fft_prod_new, in_2_temp); 
        engine.add_eval_form(fft_multisum_eval_new, fft_multisum_eval_new, fft_prod_new);

        // New
        engine.to_eval_form(fft_prod, arr[i]);     
        engine.mul_eval_form(fft_prod, fft_prod, c_arr[w*i]); 
        engine.add_eval_form(fft_multisum_eval, fft_multisum_eval, fft_prod); 
    } 
    engine.to_coef_form(out, fft_multisum_eval);  
    mod_reduce(out, out);  


    engine.to_coef_form(out_new, fft_multisum_eval_new);
    Utils::array_mod_form(out_new, out_new, in_1->degree, in_1->coef_modulus);

    delete[] fft_prod_new; 
    delete[] fft_multisum_eval_new;
    delete[] out_new;
}


// Currently multisum_fft is lazy - modulus reduction happends only at the end.
void RLWEGadgetCT::multisum_fft(long *out, long** arr, fftw_complex **c_arr, int ell, int w){ 
    // TODO: Note that we may get the arr polynomials in signed form
    // Meaning, that the outcome of the evaluation may also be in some weird signed form.
    // I think that this mod reduce isn't written to handle somehting like this.
    engine.to_eval_form(fft_multisum_eval, arr[0]);   
    engine.mul_eval_form(fft_multisum_eval, fft_multisum_eval, c_arr[0]);  
  
    for(int i = 1; i < ell; ++i){ 
        engine.to_eval_form(fft_prod, arr[i]);     
        engine.mul_eval_form(fft_prod, fft_prod, c_arr[w*i]); 
        engine.add_eval_form(fft_multisum_eval, fft_multisum_eval, fft_prod); 
    } 
    engine.to_coef_form(out, fft_multisum_eval);  
    mod_reduce(out, out);  
}
   
// Multisum any multiplies every second ciphertext
void RLWEGadgetCT::multisum_any_fft(long *out, long** arr, fftw_complex **c_arr){ 
    // TODO: Note that we may get the arr polynomials in signed form
    // Meaning, that the outcome of the evaluation may also be in some weird signed form.
    // I think that this mod reduce isn't written to handle somehting like this.
    engine.to_eval_form(fft_multisum_eval, arr[0]);   
    engine.mul_eval_form(fft_multisum_eval, fft_multisum_eval, c_arr[0]);  
  
    for(int i = 1; i < gadget_param->ell_any; ++i){ 
        engine.to_eval_form(fft_prod, arr[i]);     
        engine.mul_eval_form(fft_prod, fft_prod, c_arr[2*i]); 
        engine.add_eval_form(fft_multisum_eval, fft_multisum_eval, fft_prod); 
    }  
    engine.to_coef_form(out, fft_multisum_eval);  
    mod_reduce(out, out);  
}



void RLWEGadgetCT::multisum_ntt_test(long *out, long** arr, long **c_arr, int ell, int w, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2){  
    // Initialize some tables for the new multisum
    long* in_1_temp = in_1->poly_array;
    long* in_2_temp = in_2->eval_long;
    long* temp = new long[in_2->size];    
    long* out_coefs = new long[in_1->degree];

    // Check after array mod are OK 
    if(!Utils::is_eq_poly(in_1_temp, arr[0], in_1->degree)){
            throw std::logic_error("!Utils::is_eq_poly(in_1_temp, arr[0], in_1->degree): First Check Fail!");
    }

    // Quick check if sizes agree
    if(ell != in_2->array_size){ 
        throw std::logic_error("ell != in_2->array_size: Fail!");
    }
    if(in_1->degree != gadget_param->rlwe_param->N){ 
        throw std::logic_error("in_1->degree != gadget_param->rlwe_param->N: Fail!");
    }
    if(in_2->size != gadget_param->rlwe_param->N){ 
        throw std::logic_error("in_2->size != gadget_param->rlwe_param->N: Fail!");
    }
    if(in_2->coef_modulus != gadget_param->rlwe_param->Q){ 
        throw std::logic_error("in_2->coef_modulus != gadget_param->rlwe_param->Q: Fail!");
    }

    // From From new 
    Utils::array_mod_form(in_1_temp, in_1_temp, in_1->degree, in_1->coef_modulus); 
    ntt.ComputeForward((uint64_t*) temp, (uint64_t*) in_1_temp, 1, 1);  
    intel::hexl::EltwiseMultMod((uint64_t*) temp, (uint64_t*) temp, (uint64_t*) in_2_temp, in_2->size, in_2->coef_modulus, 1);

    // From Old
    Utils::array_mod_form(arr[0], arr[0], gadget_param->rlwe_param->N, gadget_param->rlwe_param->Q); 
    ntt.ComputeForward((uint64_t*) ntt_multisum_eval, (uint64_t*) arr[0], 1, 1);
    intel::hexl::EltwiseMultMod((uint64_t*) ntt_multisum_eval, (uint64_t*) ntt_multisum_eval, (uint64_t*) c_arr[0], gadget_param->rlwe_param->N, gadget_param->rlwe_param->Q, 1);
   

    // Check after array mod are OK 
    if(!Utils::is_eq_poly(in_1_temp, arr[0], in_1->degree)){ 
            throw std::logic_error("!!Utils::is_eq_poly(in_1_temp, arr[0], in_1->degree): Fail!");
    }
    if(!Utils::is_eq_poly(in_2_temp, c_arr[0], in_2->size)){ 
            throw std::logic_error("!Utils::is_eq_poly(in_2_temp, c_arr[0], in_2->size): Fail!");
    }
    // Check if the result of ElewiseMultMod are the same
    if(!Utils::is_eq_poly(temp, ntt_multisum_eval, in_2->size)){ 
            throw std::logic_error("!Utils::is_eq_poly(out_coefs, ntt_multisum_eval, in_2->size): Fail!");
    }

    for(int i = 1; i < in_2->array_size; ++i){
         
        // from New
        in_1_temp = &in_1->poly_array[i * in_1->degree];
        in_2_temp = &in_2->eval_long[i * in_2->size];
        Utils::array_mod_form(in_1_temp, in_1_temp, in_1->degree, in_1->coef_modulus); 
        ntt.ComputeForward((uint64_t*) temp, (uint64_t*) in_1_temp, 1, 1);  
        intel::hexl::EltwiseMultMod((uint64_t*) temp, (uint64_t*) temp, (uint64_t*) in_2_temp, in_2->size, in_2->coef_modulus, 1);
        intel::hexl::EltwiseAddMod((uint64_t*) out_coefs, (uint64_t*) temp, (uint64_t*) out_coefs, in_2->size, in_2->coef_modulus);

        // From Old
        Utils::array_mod_form(arr[i], arr[i], gadget_param->rlwe_param->N, gadget_param->rlwe_param->Q); 
        ntt.ComputeForward((uint64_t*) ntt_prod, (uint64_t*) arr[i], 1, 1);  
        intel::hexl::EltwiseMultMod((uint64_t*) ntt_prod, (uint64_t*) ntt_prod, (uint64_t*) c_arr[w*i], gadget_param->rlwe_param->N, gadget_param->rlwe_param->Q, 1); 
        intel::hexl::EltwiseAddMod((uint64_t*) ntt_multisum_eval, (uint64_t*) ntt_multisum_eval, (uint64_t*) ntt_prod, gadget_param->rlwe_param->N, gadget_param->rlwe_param->Q);   
    } 

    // From new
    ntt.ComputeInverse((uint64_t*) out_coefs, (uint64_t*) out_coefs, 1, 1);   
    delete[] temp;
 
    // From Old
    ntt.ComputeInverse((uint64_t*) out, (uint64_t*)  ntt_multisum_eval, 1, 1); 
}


void RLWEGadgetCT::multisum_ntt(long *out, long** arr, long **c_arr, int ell, int w){ 
    Utils::array_mod_form(arr[0], arr[0], gadget_param->rlwe_param->N, gadget_param->rlwe_param->Q); 
    ntt.ComputeForward((uint64_t*) ntt_multisum_eval, (uint64_t*) arr[0], 1, 1);
    intel::hexl::EltwiseMultMod((uint64_t*) ntt_multisum_eval, (uint64_t*) ntt_multisum_eval, (uint64_t*) c_arr[0], gadget_param->rlwe_param->N, gadget_param->rlwe_param->Q, 1);
   
    for(int i = 1; i < ell; ++i){ 
        Utils::array_mod_form(arr[i], arr[i], gadget_param->rlwe_param->N, gadget_param->rlwe_param->Q); 
        ntt.ComputeForward((uint64_t*) ntt_prod, (uint64_t*) arr[i], 1, 1);  
        intel::hexl::EltwiseMultMod((uint64_t*) ntt_prod, (uint64_t*) ntt_prod, (uint64_t*) c_arr[w*i], gadget_param->rlwe_param->N, gadget_param->rlwe_param->Q, 1); 
        intel::hexl::EltwiseAddMod((uint64_t*) ntt_multisum_eval, (uint64_t*) ntt_multisum_eval, (uint64_t*) ntt_prod, gadget_param->rlwe_param->N, gadget_param->rlwe_param->Q);   
    }  
    ntt.ComputeInverse((uint64_t*) out, (uint64_t*)  ntt_multisum_eval, 1, 1); 
}


 
void RLWEGadgetCT::multisum_any_ntt(long *out, long** arr, long **c_arr){ 
    Utils::array_mod_form(arr[0], arr[0], gadget_param->rlwe_param->N, gadget_param->rlwe_param->Q); 
    ntt.ComputeForward((uint64_t*) ntt_multisum_eval, (uint64_t*) arr[0], 1, 1);
    intel::hexl::EltwiseMultMod((uint64_t*) ntt_multisum_eval, (uint64_t*) ntt_multisum_eval, (uint64_t*) c_arr[0], gadget_param->rlwe_param->N, gadget_param->rlwe_param->Q, 1);
   
    for(int i = 1; i < gadget_param->ell_any; ++i){ 
        Utils::array_mod_form(arr[i], arr[i], gadget_param->rlwe_param->N, gadget_param->rlwe_param->Q); 
        ntt.ComputeForward((uint64_t*) ntt_prod, (uint64_t*) arr[i], 1, 1);  
        intel::hexl::EltwiseMultMod((uint64_t*) ntt_prod, (uint64_t*) ntt_prod, (uint64_t*) c_arr[2*i], gadget_param->rlwe_param->N, gadget_param->rlwe_param->Q, 1); 
        intel::hexl::EltwiseAddMod((uint64_t*) ntt_multisum_eval, (uint64_t*) ntt_multisum_eval, (uint64_t*) ntt_prod, gadget_param->rlwe_param->N, gadget_param->rlwe_param->Q);   
    }  
    ntt.ComputeInverse((uint64_t*) out, (uint64_t*)  ntt_multisum_eval, 1, 1); 
}



void RLWEGadgetCT::set_computing_engine(){
    if(gadget_param->rlwe_param->arithmetic == double_fft){ 
        engine = FFTPlan(gadget_param->rlwe_param->ring, gadget_param->rlwe_param->N, false);  
        fft_multisum_eval = new fftw_complex[engine.plan_size]; 
        fft_prod = new fftw_complex[engine.plan_size];     
    }else if(gadget_param->rlwe_param->arithmetic == long_double_fft){
        engine = FFTPlan(gadget_param->rlwe_param->ring, gadget_param->rlwe_param->N, true);   
    }
    else if(gadget_param->rlwe_param->arithmetic == hexl_ntt){
        ntt = intel::hexl::NTT(gadget_param->rlwe_param->N, gadget_param->rlwe_param->Q);
        ntt_multisum_eval = new long[gadget_param->rlwe_param->N]; 
        ntt_prod = new long[gadget_param->rlwe_param->N];  
    }else if(gadget_param->rlwe_param->arithmetic == ntl){
        // Do nothing here
    }else{
        throw std::logic_error("Non existent polynomial multiplication engine!");
    } 
}


void RLWEGadgetCT::init_gadget_decomp_tables(){
    // Set up also precomputed arrays for gadget decomposition  
    simul_ct_a_dec = new long*[gadget_param->rand_gadget.ell];
    simul_ct_b_dec = new long*[gadget_param->rand_gadget.ell];
    deter_ct_a_dec = new long*[gadget_param->deter_gadget.ell];
    deter_ct_b_dec = new long*[gadget_param->deter_gadget.ell];
 
}


void RLWEGadgetCT::set_gadget_decomp_arrays(){
    
    simul_ct_a_dec_poly = PolynomialArrayCoefForm(gadget_param->rlwe_param->N, gadget_param->rlwe_param->Q, gadget_param->rand_gadget.ell);
    simul_ct_b_dec_poly = PolynomialArrayCoefForm(gadget_param->rlwe_param->N, gadget_param->rlwe_param->Q, gadget_param->rand_gadget.ell);
    deter_ct_a_dec_poly = PolynomialArrayCoefForm(gadget_param->rlwe_param->N, gadget_param->rlwe_param->Q, gadget_param->deter_gadget.ell);
    deter_ct_b_dec_poly = PolynomialArrayCoefForm(gadget_param->rlwe_param->N, gadget_param->rlwe_param->Q, gadget_param->deter_gadget.ell);
  
    // Point the polynomials to the long tables.
    for(int i = 0; i < gadget_param->rand_gadget.ell; ++i){  
        simul_ct_a_dec[i] = &simul_ct_a_dec_poly.poly_array[i * simul_ct_a_dec_poly.degree]; 
        simul_ct_b_dec[i] = &simul_ct_b_dec_poly.poly_array[i * simul_ct_b_dec_poly.degree]; 
    } 
    for(int i = 0; i < gadget_param->deter_gadget.ell; ++i){ 
        deter_ct_a_dec[i] = &deter_ct_a_dec_poly.poly_array[i * deter_ct_a_dec_poly.degree]; 
        deter_ct_b_dec[i] = &deter_ct_b_dec_poly.poly_array[i * deter_ct_b_dec_poly.degree]; 
    } 
}

 void RLWEGadgetCT::init_fft_eval(){
    eval_a = new fftw_complex*[gadget_param->ell_max];
    eval_b = new fftw_complex*[gadget_param->ell_max];  
    eval_a_sk = new fftw_complex*[gadget_param->ell_max];
    eval_b_sk = new fftw_complex*[gadget_param->ell_max];   
    mask = gadget_param->rlwe_param->Q-1; 
    for(int i = 0; i < gadget_param->ell_max; ++i){  
        eval_a[i] = engine.init_fft_poly();
        eval_b[i] = engine.init_fft_poly();
        eval_a_sk[i] = engine.init_fft_poly();
        eval_b_sk[i] = engine.init_fft_poly();
    }
}


void RLWEGadgetCT::delete_fft_eval(){
    for(int i = 0; i < gadget_param->ell_max; ++i){ 
        delete[] eval_a[i];
        delete[] eval_b[i];
        delete[] eval_a_sk[i];
        delete[] eval_b_sk[i]; 
    }
    delete[] eval_a;
    delete[] eval_b;
    delete[] eval_a_sk;
    delete[] eval_b_sk;  
    // Delete temporary arrays:
    delete[] fft_multisum_eval; 
    delete[] fft_prod;    
}

 void RLWEGadgetCT::init_ntt_eval(){ 
    ntt_eval_a = new long*[gadget_param->ell_max];
    ntt_eval_b = new long*[gadget_param->ell_max];  
    ntt_eval_a_sk = new long*[gadget_param->ell_max];
    ntt_eval_b_sk = new long*[gadget_param->ell_max];   
    for(int i = 0; i < gadget_param->ell_max; ++i){     
        ntt_eval_a[i] = new long[gadget_param->rlwe_param->N]; 
        ntt_eval_b[i] = new long[gadget_param->rlwe_param->N]; 
        ntt_eval_a_sk[i] = new long[gadget_param->rlwe_param->N]; 
        ntt_eval_b_sk[i] = new long[gadget_param->rlwe_param->N]; 
    }
}

 void RLWEGadgetCT::delete_ntt_eval(){
    for(int i = 0; i < gadget_param->ell_max; ++i){ 
        delete[] ntt_eval_a[i];
        delete[] ntt_eval_b[i];
        delete[] ntt_eval_a_sk[i];
        delete[] ntt_eval_b_sk[i]; 
    }
    delete[] ntt_eval_a;
    delete[] ntt_eval_b;
    delete[] ntt_eval_a_sk;
    delete[] ntt_eval_b_sk;  
    // Delete the temporary arrays:
    delete[] ntt_multisum_eval;
    delete[] ntt_prod; 
}


void RLWEGadgetCT::to_eval_fft(){
    for(int i = 0; i < gadget_param->ell_max; ++i){
        // Note: we scale this one up, because we prepare the gadget ciphertext for multiplication
        engine.to_eval_form_scale(eval_a[i], gadget_ct[i].a.coefs, 2.0); 
        engine.to_eval_form_scale(eval_b[i], gadget_ct[i].b.coefs, 2.0); 
        engine.to_eval_form_scale(eval_a_sk[i], gadget_ct_sk[i].a.coefs, 2.0); 
        engine.to_eval_form_scale(eval_b_sk[i], gadget_ct_sk[i].b.coefs, 2.0); 
    }   
} 

void RLWEGadgetCT::to_coef_fft(){
    for(int i = 0; i < gadget_param->ell_max; ++i){ 
        engine.to_coef_form(gadget_ct[i].a.coefs, eval_a[i]);
        engine.to_coef_form(gadget_ct[i].b.coefs, eval_b[i]);
        engine.to_coef_form(gadget_ct_sk[i].a.coefs, eval_a_sk[i]);
        engine.to_coef_form(gadget_ct_sk[i].b.coefs, eval_b_sk[i]);
    }    
} 

void RLWEGadgetCT::to_eval_ntt(){ 
    for(int i = 0; i < gadget_param->ell_max; ++i){ 
        ntt.ComputeForward((uint64_t*) ntt_eval_a[i], (uint64_t*) gadget_ct[i].a.coefs, 1, 1); 
        ntt.ComputeForward((uint64_t*) ntt_eval_b[i], (uint64_t*) gadget_ct[i].b.coefs, 1, 1); 
        ntt.ComputeForward((uint64_t*) ntt_eval_a_sk[i], (uint64_t*) gadget_ct_sk[i].a.coefs, 1, 1); 
        ntt.ComputeForward((uint64_t*) ntt_eval_b_sk[i], (uint64_t*) gadget_ct_sk[i].b.coefs, 1, 1);
    }
} 

void RLWEGadgetCT::to_coef_ntt(){ 
    for(int i = 0; i < gadget_param->ell_max; ++i){
         ntt.ComputeInverse((uint64_t*) gadget_ct[i].a.coefs, (uint64_t*)  ntt_eval_a[i], 1, 1);
         ntt.ComputeInverse((uint64_t*) gadget_ct[i].b.coefs, (uint64_t*)  ntt_eval_b[i], 1, 1);
         ntt.ComputeInverse((uint64_t*) gadget_ct_sk[i].a.coefs, (uint64_t*)  ntt_eval_a_sk[i], 1, 1);
         ntt.ComputeInverse((uint64_t*) gadget_ct_sk[i].b.coefs, (uint64_t*)  ntt_eval_b_sk[i], 1, 1);
    }
} 


void RLWEGadgetCT::mod_reduce(long *out_poly, long *in_poly){
    if(gadget_param->rlwe_param->mod_type == power_of_two){
        for(int i = 0; i < gadget_param->rlwe_param->N; ++i){   
            out_poly[i] = in_poly[i] & this->mask; 
        }
    }else{
        for(int i = 0; i < gadget_param->rlwe_param->N; ++i){   
            out_poly[i] = in_poly[i] % gadget_param->rlwe_param->Q; 
        }
    } 
}

 
void RLWEGadgetCT::mod_reduce(long *out_poly, long double *in_poly_l){
      long double Q_l = (long double) gadget_param->rlwe_param->Q;
      for(int i = 0; i < gadget_param->rlwe_param->N; ++i){  
      out_poly[i] = round(fmodl(in_poly_l[i], Q_l));  
   }
}

  

RLWEGadgetParam::RLWEGadgetParam(std::shared_ptr<RLWEParam> rlwe_param, int basis, Gadget &deter_gadget, Gadget &rand_gadget){  
    this->rlwe_param = rlwe_param;  
    this->deter_gadget = deter_gadget; 
    this->rand_gadget = rand_gadget;  
    setup_the_other_parametrs(); 
}



RLWEGadgetParam::RLWEGadgetParam(const RLWEGadgetParam &other){
    this->rlwe_param = other.rlwe_param; 
    this->deter_gadget = other.deter_gadget; 
    this->rand_gadget = other.rand_gadget;  
    setup_the_other_parametrs(); 
}


RLWEGadgetParam& RLWEGadgetParam::operator=(const RLWEGadgetParam other){
    if (this == &other)
    {
        return *this;
    } 
    this->rlwe_param = other.rlwe_param; 
    this->deter_gadget = other.deter_gadget; 
    this->rand_gadget = other.rand_gadget; 
    setup_the_other_parametrs(); 
    return *this;
}


void RLWEGadgetParam::setup_the_other_parametrs(){ 
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
        w = Utils::power_times(basis, basis_any);
        if(!Utils::is_power_of(basis, basis_any)){
            throw std::logic_error("RLWEGadgetParam::setup_the_other_parametrs(): basis_any is not a power of basis!");  
        }
        if(w * ell > ell_any){
            this->ell_max = w * ell;
        }else{
            this->ell_max = ell_any;
        } 
    }else{ 
        w = 1;
        w_any = Utils::power_times(basis_any, basis);
        if(!Utils::is_power_of(basis_any, basis)){
            throw std::logic_error("RLWEGadgetParam::setup_the_other_parametrs(): basis is not a power of basis_any!");  
        }
        if(w_any * ell_any > ell){
            this->ell_max = w_any * ell_any;
        }else{
            this->ell_max = ell;
        }
    }
}


  

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
  
RLWESK::RLWESK(std::shared_ptr<RLWEParam> param){ 
    this->param = param;
    s = new long[param->N]; 

    unif_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, param->Q));
    error_dist = std::shared_ptr<Distribution>(new StandardRoundedGaussianDistribution(0, param->stddev));
    if(param->key_type == uniform){ 
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, param->Q));
    }else if(param->key_type == ternary){ 
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(-1, 1));
    }else if(param->key_type == binary){ 
        sk_dist = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, 1));
    } 
    sk_dist->fill_array(this->s, param->N);
    
    // TODO: Should substitute the above. Simply delete the above (but need to make sure we don't use the s table anywere)
    this->sk = Polynomial(param->N, param->Q, param->mul_engine);  
    Utils::cp(this->sk.coefs, this->s, param->N);   
    this->sk.to_eval();  
    this->is_init = true; 
}
  
 
RLWESK::RLWESK(const RLWESK &other){
    throw std::runtime_error("RLWESK::RLWESK(const RLWESK &other): Don't copy the secret key!"); 
}

RLWESK& RLWESK::operator=(const RLWESK other){  
    throw std::runtime_error("RLWESK::operator=(const RLWESK other): Don't copy the secret key!"); 
    return *this;
}
 
 

void RLWESK::encrypt(RLWECT *out, Polynomial *m){ 

    if(m->degree < param->N){
        throw std::logic_error("RLWESK::encrypt(Polynomial *m): Input polynomial m, degree is too big!");
    }
    if(m->coef_modulus < param->Q){
        throw std::logic_error("RLWESK::encrypt(Polynomial *m): Input polynomial m, coefficient codulus is too big!");
    }
    if(!m->is_init){
        throw std::logic_error("RLWESK::encrypt(Polynomial *m): Input polynomial m is not initialized!");
    }
  
    unif_dist->fill_array(out->a.coefs, param->N);
 
    Polynomial noise(param->N, param->Q);
    error_dist->fill_array(noise.coefs, param->N);
 
    Polynomial message(param->N, param->Q);
    Utils::cp(message.coefs, m->coefs, param->N);
 
    // Now just need to compute: b = a * s + e + m
    // First we need a poolynomial s in eval form.  
    out->a.mul(&out->b, &sk, param->mul_engine);
    out->b.add(&out->b, &noise);
    out->b.add(&out->b, &message); 
  
}


RLWECT RLWESK::encrypt(Polynomial *m){   
    RLWECT out(param);  
    this->encrypt(&out, m);
    return out;
}


RLWECT RLWESK::scale_and_encrypt(Polynomial* m, int t){ 
    // TODO: Potential problem if Q is too big. The scale may require to be a long double.
    double scale = (double)param->Q/t;
    Polynomial m_scaled(param->N, param->Q); 
    for(int i = 0; i < param->N; ++i){ 
        m_scaled.coefs[i] = (long)round((double)m->coefs[i]*scale);
    }
    RLWECT out = encrypt(&m_scaled); 
    return out;
}


void RLWESK::phase(Polynomial *phase, RLWECT *ct){   

    if(phase->degree != param->N){
        throw std::logic_error("RLWESK::phase(Polynomial *phase, RLWECT *ct): Dimension of the input polynomial differs from the the RLWE polynomials.");
    }
    if(phase->coef_modulus != param->Q){
        throw std::logic_error("RLWESK::phase(Polynomial *phase, RLWECT *ct): Coefficient modulus of the input polynomial differs from the the RLWE polynomials.");
    }
    if(!phase->is_init){
        throw std::logic_error("RLWESK::phase(Polynomial *phase, RLWECT *ct): Input polynomial is not initialized.");
    }
 
    ct->a.mul(phase, &sk); 
    ct->b.sub(phase, phase); 
}

// Uses SK
Polynomial RLWESK::decrypt(RLWECT *ct, int t){ 
    Polynomial out(param->N, param->Q);
    decrypt(&out, ct, t);  
    return out;
}

// Uses SK
void RLWESK::decrypt(Polynomial *out, RLWECT *ct, int t){   
    this->phase(out, ct);  
    Utils::array_rounding(out->coefs, out->coefs, param->N, param->Q, t);  
}

 

void RLWESK::extract_lwe_key(long* lwe_key){  
    for(int i = 0; i <  param->N; ++i){
        lwe_key[i] = -s[i];
    } 
}


RLWEGadgetSK::RLWEGadgetSK(const RLWEGadgetSK &other){ 
    throw std::runtime_error("RLWEGadgetSK::RLWEGadgetSK(const RLWEGadgetSK &other): Don't copy the secret key!");  
}

RLWEGadgetSK::RLWEGadgetSK(std::shared_ptr<RLWEGadgetParam> gadget_param, std::shared_ptr<RLWESK> sk){ 
    this->gadget_param = gadget_param; 
    this->sk = sk; 
}

RLWEGadgetSK& RLWEGadgetSK::operator=(const RLWEGadgetSK other){  
    throw std::runtime_error("RLWEGadgetSK::operator=(const RLWEGadgetSK other): Don't copy the secret key!");
    return *this;
}
 

RLWEGadgetCT RLWEGadgetSK::gadget_encrypt(long* msg){   
       
   std::vector<RLWECT> gadget_ct; 
   std::vector<RLWECT> gadget_ct_sk; 
 
    Polynomial msg_cpy(gadget_param->rlwe_param->N, gadget_param->rlwe_param->Q); 
    for(int i = 0; i < gadget_param->rlwe_param->N; ++i){ 
        msg_cpy.coefs[i] = msg[i]; 
    }  
    
   Polynomial msg_x_sk(gadget_param->rlwe_param->N, gadget_param->rlwe_param->Q);
 
    // Multiply msg with sk.s. Result is in msg_x_sk 
    msg_cpy.mul(&msg_x_sk, &sk->sk, gadget_param->rlwe_param->mul_engine);
    msg_x_sk.neg(&msg_x_sk);
  
    gadget_ct.push_back(sk->encrypt(&msg_cpy));
    for(int i = 1; i < gadget_param->ell_max; ++i){
        // Multiply msg by basis

        msg_cpy.mul(&msg_cpy, gadget_param->basis); 
        // Encrypt msg * basis**i  
        gadget_ct.push_back(sk->encrypt(&msg_cpy));
    } 
    // Encryption of - msg * sk * basis**i  
    gadget_ct_sk.push_back(sk->encrypt(&msg_x_sk));
    for(int i = 1; i < gadget_param->ell_max; ++i){
        // Multiply msg by basis
        msg_x_sk.mul(&msg_x_sk, gadget_param->basis);
 
        // Encrypt - msg * sk * basis**i   
        gadget_ct_sk.push_back(sk->encrypt(&msg_x_sk)); 
    }   

    RLWEGadgetCT out(gadget_param, gadget_ct, gadget_ct_sk);   

   return out; 
}
 
