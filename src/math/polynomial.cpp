#include "math/polynomial.h"
 
using namespace fhe_deck;
 

void PolynomialMultiplicationEngine::mul(Polynomial &out, const Polynomial &in_1, const Polynomial &in_2){   
    std::shared_ptr<PolynomialEvalForm> eval_in_1 = init_polynomial_eval_form();
    to_eval(*eval_in_1, in_1);  
    std::shared_ptr<PolynomialEvalForm> eval_in_2 = init_polynomial_eval_form();
    to_eval(*eval_in_2, in_2); 
    std::shared_ptr<PolynomialEvalForm> eval_out = init_polynomial_eval_form(); 
    mul(*eval_out, *eval_in_1, *eval_in_2);  
    to_coef(out, *eval_out);  
}
   
PolynomialEvalFormLongInteger::~PolynomialEvalFormLongInteger(){
    if(is_init){
        delete[] eval_long;
    }
}

PolynomialEvalFormLongInteger::PolynomialEvalFormLongInteger(int64_t* eval_long, int32_t size, int64_t coef_modulus){
    this->eval_long = eval_long;
    this->coef_modulus = coef_modulus;
    this->is_init = true; 
    this->size = size;
}

void PolynomialEvalFormLongInteger::zeroize(){ 
    for(int32_t i = 0; i < size; ++i){
        this->eval_long[i] = 0;
    }
}

void PolynomialEvalFormLongInteger::add(PolynomialEvalForm &out, const PolynomialEvalForm &other)const{ 
    const PolynomialEvalFormLongInteger& other_cast = static_cast<const PolynomialEvalFormLongInteger&>(other);
    PolynomialEvalFormLongInteger& out_cast = static_cast<PolynomialEvalFormLongInteger&>(out);
    for(int32_t i = 0; i < size; ++i){
        out_cast.eval_long[i] = this->eval_long[i] + other_cast.eval_long[i];
    }
}

void PolynomialEvalFormLongInteger::sub(PolynomialEvalForm &out, const PolynomialEvalForm &other)const{
    const PolynomialEvalFormLongInteger& other_cast = static_cast<const PolynomialEvalFormLongInteger&>(other);
    PolynomialEvalFormLongInteger& out_cast = static_cast<PolynomialEvalFormLongInteger&>(out);
    for(int32_t i = 0; i < size; ++i){
        out_cast.eval_long[i] = this->eval_long[i] - other_cast.eval_long[i];
    }  
}

void PolynomialEvalFormLongInteger::mul(PolynomialEvalForm &out, int64_t scalar)const{
    PolynomialEvalFormLongInteger& out_cast = static_cast<PolynomialEvalFormLongInteger&>(out);
    for(int32_t i = 0; i < size; ++i){
        out_cast.eval_long[i] = this->eval_long[i] * scalar;
    } 
}
 
void PolynomialEvalFormLongInteger::neg(PolynomialEvalForm &out)const{
    PolynomialEvalFormLongInteger& out_cast = static_cast<PolynomialEvalFormLongInteger&>(out);
    for(int32_t i = 0; i < size; ++i){
        out_cast.eval_long[i] = -this->eval_long[i];
    } 
}
  

PolynomialEvalFormFFTWComplex::~PolynomialEvalFormFFTWComplex(){
    if(is_init){
        delete[] eval_fftw;
    }
}
 
PolynomialEvalFormFFTWComplex::PolynomialEvalFormFFTWComplex(Complex* eval_fftw, int32_t size){
    this->eval_fftw = eval_fftw; 
    this->is_init = true; 
    this->size = size; 
}

void PolynomialEvalFormFFTWComplex::zeroize(){
    for(int32_t i = 0; i < size; ++i){
        this->eval_fftw[i][0] = 0;
        this->eval_fftw[i][1] = 0;
    }
}

void PolynomialEvalFormFFTWComplex::add(PolynomialEvalForm &out, const PolynomialEvalForm &other)const{
    const PolynomialEvalFormFFTWComplex& other_cast = static_cast<const PolynomialEvalFormFFTWComplex&>(other);
    const PolynomialEvalFormFFTWComplex& out_cast = static_cast<const PolynomialEvalFormFFTWComplex&>(out);
    for(int32_t i = 0; i < size; ++i){
        out_cast.eval_fftw[i][0] = this->eval_fftw[i][0] + other_cast.eval_fftw[i][0];
        out_cast.eval_fftw[i][1] = this->eval_fftw[i][1] + other_cast.eval_fftw[i][1];
    } 
}

void PolynomialEvalFormFFTWComplex::sub(PolynomialEvalForm &out, const PolynomialEvalForm &other)const{
    const PolynomialEvalFormFFTWComplex& other_cast = static_cast<const PolynomialEvalFormFFTWComplex&>(other);
    const PolynomialEvalFormFFTWComplex& out_cast = static_cast<const PolynomialEvalFormFFTWComplex&>(out);
    for(int32_t i = 0; i < size; ++i){
        out_cast.eval_fftw[i][0] = this->eval_fftw[i][0] - other_cast.eval_fftw[i][0];
        out_cast.eval_fftw[i][1] = this->eval_fftw[i][1] - other_cast.eval_fftw[i][1];
    } 
}

void PolynomialEvalFormFFTWComplex::mul(PolynomialEvalForm &out, int64_t scalar)const{
    PolynomialEvalFormFFTWComplex& out_cast = static_cast<PolynomialEvalFormFFTWComplex&>(out);
    for(int32_t i = 0; i < size; ++i){
        out_cast.eval_fftw[i][0] = this->eval_fftw[i][0] * scalar;
        out_cast.eval_fftw[i][1] = this->eval_fftw[i][1] * scalar;
    }  
}
 
void PolynomialEvalFormFFTWComplex::neg(PolynomialEvalForm &out)const{ 
    PolynomialEvalFormFFTWComplex& out_cast = static_cast<PolynomialEvalFormFFTWComplex&>(out);
    for(int32_t i = 0; i < size; ++i){
        out_cast.eval_fftw[i][0] = -this->eval_fftw[i][0];
        out_cast.eval_fftw[i][1] = -this->eval_fftw[i][1];
    } 
}
 

PolynomialEvalFormFFTWLongComplex::~PolynomialEvalFormFFTWLongComplex(){
    if(is_init){
        delete[] eval_fftwl;
    }
}
  
PolynomialEvalFormFFTWLongComplex::PolynomialEvalFormFFTWLongComplex(LongComplex* eval_fftwl, int32_t size){
    this->eval_fftwl = eval_fftwl; 
    this->is_init = true; 
    this->size = size; 
}

void PolynomialEvalFormFFTWLongComplex::zeroize(){
    for(int32_t i = 0; i < size; ++i){
        this->eval_fftwl[i][0] = 0;
        this->eval_fftwl[i][1] = 0;
    }
}

void PolynomialEvalFormFFTWLongComplex::add(PolynomialEvalForm &out, const PolynomialEvalForm &other)const{
    const PolynomialEvalFormFFTWLongComplex& other_cast = static_cast<const PolynomialEvalFormFFTWLongComplex&>(other);
    PolynomialEvalFormFFTWLongComplex& out_cast = static_cast<PolynomialEvalFormFFTWLongComplex&>(out);
    for(int32_t i = 0; i < size; ++ i){
        out_cast.eval_fftwl[i][0] = this->eval_fftwl[i][0] + other_cast.eval_fftwl[i][0];
        out_cast.eval_fftwl[i][1] = this->eval_fftwl[i][1] + other_cast.eval_fftwl[i][1];
    }       
}
 
void PolynomialEvalFormFFTWLongComplex::sub(PolynomialEvalForm &out, const PolynomialEvalForm &other)const{
    const PolynomialEvalFormFFTWLongComplex& other_cast = static_cast<const PolynomialEvalFormFFTWLongComplex&>(other);
    PolynomialEvalFormFFTWLongComplex& out_cast = static_cast<PolynomialEvalFormFFTWLongComplex&>(out);
    for(int32_t i = 0; i < size; ++i){
        out_cast.eval_fftwl[i][0] = this->eval_fftwl[i][0] - other_cast.eval_fftwl[i][0];
        out_cast.eval_fftwl[i][1] = this->eval_fftwl[i][1] - other_cast.eval_fftwl[i][1];
    } 
}

void PolynomialEvalFormFFTWLongComplex::mul(PolynomialEvalForm &out, int64_t scalar)const{
    PolynomialEvalFormFFTWLongComplex& out_cast = static_cast<PolynomialEvalFormFFTWLongComplex&>(out);
    for(int32_t i = 0; i < size; ++i){
            out_cast.eval_fftwl[i][0] = this->eval_fftwl[i][0] * scalar;
            out_cast.eval_fftwl[i][1] = this->eval_fftwl[i][1] * scalar;
        } 
}
 
void PolynomialEvalFormFFTWLongComplex::neg(PolynomialEvalForm &out)const{
    PolynomialEvalFormFFTWLongComplex& out_cast = static_cast<PolynomialEvalFormFFTWLongComplex&>(out);
    for(int32_t i = 0; i < size; ++i){
            out_cast.eval_fftwl[i][0] = -this->eval_fftwl[i][0];
            out_cast.eval_fftwl[i][1] = -this->eval_fftwl[i][1];
        } 
}
    
Polynomial::Polynomial(int32_t degree, int64_t coef_modulus){
    this->init(degree, coef_modulus);
    this->init_from_vec();
}

Polynomial::Polynomial(int64_t* coefs, int32_t degree, int64_t coef_modulus){
    this->init(degree, coef_modulus);
    this->init_from_vec();
    Utils::cp(this->coefs, coefs, degree);
}
 

void Polynomial::init_from_vec(){
    this->degree = size;
    this->coef_modulus = modulus;
    this->coef_modulus_bit_size = Utils::power_times(coef_modulus, 2);
    this->coefs = this->vec;
    this->is_init = true;
}
 
Polynomial::Polynomial(const Polynomial &other){
    this->init(other.degree, other.coef_modulus); 
    this->init_from_vec();
    Utils::cp(this->coefs, other.coefs, this->degree);  
    this->mul_engine = other.mul_engine;
    this->is_mul_engine_set = other.is_mul_engine_set; 
    this->inv_engine = other.inv_engine;
    this->is_inv_engine_set = other.is_inv_engine_set;
} 
  
Polynomial& Polynomial::operator=(const Polynomial other){
    if(!this->is_init){ 
        this->init(other.degree, other.coef_modulus);
        this->init_from_vec();
    }
    Utils::cp(this->coefs, other.coefs, this->degree);  
    this->mul_engine = other.mul_engine;
    this->is_mul_engine_set = other.is_mul_engine_set; 
    this->inv_engine = other.inv_engine;
    this->is_inv_engine_set = other.is_inv_engine_set;
    return *this;
}
 
void Polynomial::set_multiplication_engine(std::shared_ptr<PolynomialMultiplicationEngine> mul_engine){
    this->mul_engine = mul_engine;
    this->is_mul_engine_set = true; 
}

void Polynomial::set_inversion_engine(std::shared_ptr<PolynomialInversionEngine> inv_engine){
    this->inv_engine = inv_engine;
    this->is_inv_engine_set = true; 
}

void Polynomial::cyclic_rotate(Polynomial &out, int64_t rotation)const{
    int32_t overflow= this->degree - rotation ;  
      for(int32_t i = 0; i < overflow; ++i){   
            out.coefs[i+rotation] = this->coefs[i];
            
      }
      for(int32_t i = 0; i < rotation; ++i){ 
            out.coefs[i] = this->coefs[overflow + i];
      } 
}

void Polynomial::negacyclic_rotate(Polynomial &out, int64_t rotation)const{   
    /// TODO: That implementation is not the best.   

    long* temp = new long[this->degree];
    if(rotation >= this->degree){
        for(int32_t i = 0; i < this->degree; ++i){
            temp[i] = -this->coefs[i];
        }
        rotation = rotation - this->degree;
    }else{
        for(int32_t i = 0; i < this->degree; ++i){
            temp[i] = this->coefs[i];
        }
    } 
    // NOTE We implement negacyclic rotate actually -> it changes the sign of rot first coefficients
    int32_t overflow=this->degree - rotation ;  
    for(int32_t i = 0; i < overflow; ++i){   
        out.coefs[i+rotation] = temp[i];
    }
    for(int32_t i = 0; i < rotation; ++i){ 
        out.coefs[i] = -temp[overflow + i];
    }
    delete[] temp;

    Utils::array_mod_form(out.coefs, out.coefs, this->degree, this->coef_modulus);
}
 
void Polynomial::to_eval(PolynomialEvalForm &out){ 
    mul_engine->to_eval(out, *this);
}

void Polynomial::to_eval(PolynomialEvalForm &out, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine){ 
    mul_engine->to_eval(out, *this);
}
 
void Polynomial::zeroize(){
    for(int32_t i = 0; i < degree; ++i){
        coefs[i] = 0;
    }
}
 
std::shared_ptr<Polynomial> Polynomial::clone() const{
    if(!is_init){
        throw std::logic_error("Polynomial::clone: Polynomial is not initialized!");
    }
    std::shared_ptr<Polynomial> out = std::make_shared<Polynomial>(degree, coef_modulus);
    if(is_mul_engine_set){
        out->set_multiplication_engine(mul_engine);
    }
    if(is_inv_engine_set){
        out->set_inversion_engine(inv_engine);
    } 
    Utils::cp(out->coefs, coefs, degree);
    out->is_init = true;
    return out;
} 
   
void Polynomial::mul(Polynomial &out, int64_t scalar)const{ 
    if(this->degree != out.degree){
        throw std::logic_error("Polynomial::mul(Polynomial *out, int64_t scalar): Degrees of polynomials don't match!");
    }
    if(this->coef_modulus != out.coef_modulus){
        throw std::logic_error("Polynomial::mul(Polynomial *out, int64_t scalar): Coefficient moduli of polynomials don't match!");
    } 
    
    for(int32_t j=0; j < this->degree; ++j){ 
        out.coefs[j] = (int64_t)((__int128_t(coefs[j]) * __int128_t(scalar)) % __int128_t(coef_modulus)); 
    } 
}

void Polynomial::mul(Polynomial &out, const Polynomial &other)const{   
    if(this->is_mul_engine_set){ 
        this->mul(out, other, this->mul_engine); 
    }else{
        throw std::logic_error("Polynomial::mul(Polynomial *out, Polynomial *other): No multiplication engin set!");
    }
}

void Polynomial::mul(Polynomial &out, const Polynomial &other, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine)const{  
    mul_engine->mul(out, *this, other); 
}
  
void Polynomial::inv(Polynomial &out)const{
    this->inv_engine->inv(out, *this);
}

void Polynomial::inv(Polynomial &out, std::shared_ptr<PolynomialInversionEngine> inv_engine)const{
    inv_engine->inv(out, *this);
}
   
PolynomialArrayCoefForm::PolynomialArrayCoefForm(int32_t degree, int64_t coef_modulus, int32_t array_size){ 
    init(degree, coef_modulus, array_size);
    init_from_vector(); 
}
 
PolynomialArrayCoefForm::PolynomialArrayCoefForm(int32_t degree, int64_t coef_modulus, int32_t array_size, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine){ 
    init(degree, coef_modulus, array_size);
    init_from_vector();
    this->mul_engine = mul_engine;
    is_mul_engine_set = true; 
}
 
void PolynomialArrayCoefForm::init_from_vector(){ 
    this->poly_array = this->vec_array;
    this->degree = this->size;
    this->coef_modulus = this->modulus; 
}
 
PolynomialArrayCoefForm::PolynomialArrayCoefForm(const PolynomialArrayCoefForm &other){
    this->init(other.degree, other.coef_modulus, other.array_size); 
    this->init_from_vector();
    Utils::cp(this->poly_array, other.poly_array, this->full_size);  
    this->mul_engine = other.mul_engine;
    this->is_mul_engine_set = other.is_mul_engine_set;  
} 
  
PolynomialArrayCoefForm& PolynomialArrayCoefForm::operator=(const PolynomialArrayCoefForm other){
    this->init(other.degree, other.coef_modulus, other.array_size);
    this->init_from_vector();
    Utils::cp(this->poly_array, other.poly_array, this->full_size);  
    this->mul_engine = other.mul_engine;
    this->is_mul_engine_set = other.is_mul_engine_set;  
    return *this;
}

void PolynomialArrayCoefForm::set_polynomial_at(int32_t i, const Polynomial &poly){
    if(poly.degree != this->degree){
        throw std::logic_error("PolynomialArrayCoefForm::set_polynomial_at(int32_t i, Polynomial *poly): degrees are inconsistent.");
    }
    if(poly.coef_modulus != this->coef_modulus){
        throw std::logic_error("PolynomialArrayCoefForm::set_polynomial_at(int32_t i, Polynomial *poly): coef_moduli are inconsistent.");
    }
    for(int32_t j = 0; j < this->degree; ++j){
        this->poly_array[i * degree + j] = poly.coefs[j];
    }
}
  
void PolynomialArrayCoefForm::set_multiplication_engine(std::shared_ptr<PolynomialMultiplicationEngine> mul_engine){
    this->mul_engine = mul_engine;
}
    
PolynomialArrayEvalFormLong::~PolynomialArrayEvalFormLong(){
    if(this->is_init){
        delete[] eval_long;
    } 
}

PolynomialArrayEvalFormLong::PolynomialArrayEvalFormLong(int32_t array_size, int64_t degree, int64_t coef_modulus){
    this->array_size = array_size;
    this->size = degree;
    this->coef_modulus = coef_modulus;
    this->full_size = array_size * this->size;
    this->eval_long = new int64_t[full_size];
    this->is_init = true; 
}

void PolynomialArrayEvalFormLong::add(PolynomialArrayEvalForm &out, const PolynomialArrayEvalForm &other){
    const PolynomialArrayEvalFormLong& other_cast = static_cast<const PolynomialArrayEvalFormLong&>(other);
    const PolynomialArrayEvalFormLong& out_cast = static_cast<const PolynomialArrayEvalFormLong&>(out);
    for(int32_t i = 0; i < full_size; ++i){
         out_cast.eval_long[i] = this->eval_long[i] + other_cast.eval_long[i];
    }
}

void PolynomialArrayEvalFormLong::sub(PolynomialArrayEvalForm &out, const PolynomialArrayEvalForm &other){
    const PolynomialArrayEvalFormLong& other_cast = static_cast<const PolynomialArrayEvalFormLong&>(other);
    const PolynomialArrayEvalFormLong& out_cast = static_cast<const PolynomialArrayEvalFormLong&>(out);
    for(int32_t i = 0; i < full_size; ++i){
         out_cast.eval_long[i] = this->eval_long[i] - other_cast.eval_long[i];
    }
}
 
void PolynomialArrayEvalFormLong::mul(PolynomialArrayEvalForm &out, int64_t scalar){
    PolynomialArrayEvalFormLong& out_cast = static_cast<PolynomialArrayEvalFormLong&>(out); 
    for(int32_t i = 0; i < full_size; ++i){
        out_cast.eval_long[i] = this->eval_long[i] * scalar;
    }
}

void PolynomialArrayEvalFormLong::neg(PolynomialArrayEvalForm &out){
    PolynomialArrayEvalFormLong& out_cast = static_cast<PolynomialArrayEvalFormLong&>(out); 
    for(int32_t i = 0; i < full_size; ++i){
        out_cast.eval_long[i] = -this->eval_long[i];
    }
}

void PolynomialArrayEvalFormLong::mod_reduce(int64_t modulus){
    Utils::array_mod_form(this->eval_long, this->eval_long, full_size, modulus); 
}

PolynomialArrayEvalFormFFTWComplex::~PolynomialArrayEvalFormFFTWComplex(){
    if(this->is_init){
        delete[] eval_fftw;
    }
}   

PolynomialArrayEvalFormFFTWComplex::PolynomialArrayEvalFormFFTWComplex(int32_t size, int32_t array_size){ 
    this->array_size = array_size; 
    this->size = size; 
    this->full_size = this->size * array_size; 
    this->eval_fftw = new Complex[full_size];   
    this->is_init = true;
}

void PolynomialArrayEvalFormFFTWComplex::add(PolynomialArrayEvalForm &out, const PolynomialArrayEvalForm &other){
    const PolynomialArrayEvalFormFFTWComplex& other_cast = static_cast<const PolynomialArrayEvalFormFFTWComplex&>(other);
    const PolynomialArrayEvalFormFFTWComplex& out_cast = static_cast<const PolynomialArrayEvalFormFFTWComplex&>(out);
    for(int32_t i = 0; i < full_size; ++i){
            out_cast.eval_fftw[i][0] = this->eval_fftw[i][0] + other_cast.eval_fftw[i][0];
            out_cast.eval_fftw[i][1] = this->eval_fftw[i][1] + other_cast.eval_fftw[i][1];
        } 
}

void PolynomialArrayEvalFormFFTWComplex::sub(PolynomialArrayEvalForm &out, const PolynomialArrayEvalForm &other){
    const PolynomialArrayEvalFormFFTWComplex& other_cast = static_cast<const PolynomialArrayEvalFormFFTWComplex&>(other);
    const PolynomialArrayEvalFormFFTWComplex& out_cast = static_cast<const PolynomialArrayEvalFormFFTWComplex&>(out);
    for(int32_t i = 0; i < full_size; ++i){
            out_cast.eval_fftw[i][0] = this->eval_fftw[i][0] - other_cast.eval_fftw[i][0];
            out_cast.eval_fftw[i][1] = this->eval_fftw[i][1] - other_cast.eval_fftw[i][1];
        } 
}

void PolynomialArrayEvalFormFFTWComplex::mul(PolynomialArrayEvalForm &out, int64_t scalar){
    PolynomialArrayEvalFormFFTWComplex& out_cast = static_cast<PolynomialArrayEvalFormFFTWComplex&>(out);
     for(int32_t i = 0; i < full_size; ++i){
            out_cast.eval_fftw[i][0] = this->eval_fftw[i][0] * scalar;
            out_cast.eval_fftw[i][1] = this->eval_fftw[i][1] * scalar;
        } 
}

void PolynomialArrayEvalFormFFTWComplex::neg(PolynomialArrayEvalForm &out){
    PolynomialArrayEvalFormFFTWComplex& out_cast = static_cast<PolynomialArrayEvalFormFFTWComplex&>(out);
    for(int32_t i = 0; i < full_size; ++i){
            out_cast.eval_fftw[i][0] = -this->eval_fftw[i][0];
            out_cast.eval_fftw[i][1] = -this->eval_fftw[i][1];
        } 
}
  
PolynomialArrayEvalFormFFTWLongComplex::~PolynomialArrayEvalFormFFTWLongComplex(){
    if(this->is_init){
        delete[] eval_fftwl;
    }
}

PolynomialArrayEvalFormFFTWLongComplex::PolynomialArrayEvalFormFFTWLongComplex(int32_t size, int32_t array_size){ 
    this->array_size = array_size; 
    this->size = size; 
    this->full_size = this->size * array_size; 
    this->eval_fftwl = new LongComplex[full_size];  
    this->is_init = true;
}

void PolynomialArrayEvalFormFFTWLongComplex::add(PolynomialArrayEvalForm &out, const PolynomialArrayEvalForm &other){
    const PolynomialArrayEvalFormFFTWLongComplex& out_cast = static_cast<const PolynomialArrayEvalFormFFTWLongComplex&>(out);
    const PolynomialArrayEvalFormFFTWLongComplex& other_cast = static_cast<const PolynomialArrayEvalFormFFTWLongComplex&>(other);
    for(int32_t i = 0; i < full_size; ++i){
        out_cast.eval_fftwl[i][0] = this->eval_fftwl[i][0] + other_cast.eval_fftwl[i][0];
        out_cast.eval_fftwl[i][1] = this->eval_fftwl[i][1] + other_cast.eval_fftwl[i][1];
    } 
}

void PolynomialArrayEvalFormFFTWLongComplex::sub(PolynomialArrayEvalForm &out, const PolynomialArrayEvalForm &other){
    PolynomialArrayEvalFormFFTWLongComplex& out_cast = static_cast<PolynomialArrayEvalFormFFTWLongComplex&>(out);
    const PolynomialArrayEvalFormFFTWLongComplex& other_cast = static_cast<const PolynomialArrayEvalFormFFTWLongComplex&>(other);
    for(int32_t i = 0; i < full_size; ++i){
        out_cast.eval_fftwl[i][0] = this->eval_fftwl[i][0] - other_cast.eval_fftwl[i][0];
        out_cast.eval_fftwl[i][1] = this->eval_fftwl[i][1] - other_cast.eval_fftwl[i][1];
    } 
}

void PolynomialArrayEvalFormFFTWLongComplex::mul(PolynomialArrayEvalForm &out, int64_t scalar){
    PolynomialArrayEvalFormFFTWLongComplex& out_cast = static_cast<PolynomialArrayEvalFormFFTWLongComplex&>(out);
    for(int32_t i = 0; i < full_size; ++i){
        out_cast.eval_fftwl[i][0] = this->eval_fftwl[i][0] * scalar;
        out_cast.eval_fftwl[i][1] = this->eval_fftwl[i][1] * scalar;
    }
}

void PolynomialArrayEvalFormFFTWLongComplex::neg(PolynomialArrayEvalForm &out){
    PolynomialArrayEvalFormFFTWLongComplex& out_cast = static_cast<PolynomialArrayEvalFormFFTWLongComplex&>(out);
    for(int32_t i = 0; i < full_size; ++i){
        out_cast.eval_fftwl[i][0] = -this->eval_fftwl[i][0];
        out_cast.eval_fftwl[i][1] = -this->eval_fftwl[i][1];
    } 
}



 