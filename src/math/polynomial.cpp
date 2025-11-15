#include "math/polynomial.h"

 
using namespace FHEDeck;
 
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
   
PolynomialEvalFormComplex::~PolynomialEvalFormComplex(){
    if(is_init){
        delete[] eval;
    }
}
 
PolynomialEvalFormComplex::PolynomialEvalFormComplex(Complex* eval, int32_t size){
    this->eval = eval; 
    this->is_init = true; 
    this->size = size; 
}

void PolynomialEvalFormComplex::zeroize(){
    for(int32_t i = 0; i < size; ++i){
        this->eval[i][0] = 0;
        this->eval[i][1] = 0;
    }
}

void PolynomialEvalFormComplex::add(PolynomialEvalForm &out, const PolynomialEvalForm &other)const{
    const PolynomialEvalFormComplex& other_cast = static_cast<const PolynomialEvalFormComplex&>(other);
    const PolynomialEvalFormComplex& out_cast = static_cast<const PolynomialEvalFormComplex&>(out);
    for(int32_t i = 0; i < size; ++i){
        out_cast.eval[i][0] = this->eval[i][0] + other_cast.eval[i][0];
        out_cast.eval[i][1] = this->eval[i][1] + other_cast.eval[i][1];
    } 
}

void PolynomialEvalFormComplex::sub(PolynomialEvalForm &out, const PolynomialEvalForm &other)const{
    const PolynomialEvalFormComplex& other_cast = static_cast<const PolynomialEvalFormComplex&>(other);
    const PolynomialEvalFormComplex& out_cast = static_cast<const PolynomialEvalFormComplex&>(out);
    for(int32_t i = 0; i < size; ++i){
        out_cast.eval[i][0] = this->eval[i][0] - other_cast.eval[i][0];
        out_cast.eval[i][1] = this->eval[i][1] - other_cast.eval[i][1];
    } 
}

void PolynomialEvalFormComplex::mul(PolynomialEvalForm &out, int64_t scalar)const{
    PolynomialEvalFormComplex& out_cast = static_cast<PolynomialEvalFormComplex&>(out);
    for(int32_t i = 0; i < size; ++i){
        out_cast.eval[i][0] = this->eval[i][0] * scalar;
        out_cast.eval[i][1] = this->eval[i][1] * scalar;
    }  
}
 
void PolynomialEvalFormComplex::neg(PolynomialEvalForm &out)const{ 
    PolynomialEvalFormComplex& out_cast = static_cast<PolynomialEvalFormComplex&>(out);
    for(int32_t i = 0; i < size; ++i){
        out_cast.eval[i][0] = -this->eval[i][0];
        out_cast.eval[i][1] = -this->eval[i][1];
    } 
}
 

PolynomialEvalFormLongComplex::~PolynomialEvalFormLongComplex(){
    if(is_init){
        delete[] eval;
    }
}
  
PolynomialEvalFormLongComplex::PolynomialEvalFormLongComplex(LongComplex* eval, int32_t size){
    this->eval = eval; 
    this->is_init = true; 
    this->size = size; 
}

void PolynomialEvalFormLongComplex::zeroize(){
    for(int32_t i = 0; i < size; ++i){
        this->eval[i][0] = 0;
        this->eval[i][1] = 0;
    }
}

void PolynomialEvalFormLongComplex::add(PolynomialEvalForm &out, const PolynomialEvalForm &other)const{
    const PolynomialEvalFormLongComplex& other_cast = static_cast<const PolynomialEvalFormLongComplex&>(other);
    PolynomialEvalFormLongComplex& out_cast = static_cast<PolynomialEvalFormLongComplex&>(out);
    for(int32_t i = 0; i < size; ++ i){
        out_cast.eval[i][0] = this->eval[i][0] + other_cast.eval[i][0];
        out_cast.eval[i][1] = this->eval[i][1] + other_cast.eval[i][1];
    }       
}
 
void PolynomialEvalFormLongComplex::sub(PolynomialEvalForm &out, const PolynomialEvalForm &other)const{
    const PolynomialEvalFormLongComplex& other_cast = static_cast<const PolynomialEvalFormLongComplex&>(other);
    PolynomialEvalFormLongComplex& out_cast = static_cast<PolynomialEvalFormLongComplex&>(out);
    for(int32_t i = 0; i < size; ++i){
        out_cast.eval[i][0] = this->eval[i][0] - other_cast.eval[i][0];
        out_cast.eval[i][1] = this->eval[i][1] - other_cast.eval[i][1];
    } 
}

void PolynomialEvalFormLongComplex::mul(PolynomialEvalForm &out, int64_t scalar)const{
    PolynomialEvalFormLongComplex& out_cast = static_cast<PolynomialEvalFormLongComplex&>(out);
    for(int32_t i = 0; i < size; ++i){
            out_cast.eval[i][0] = this->eval[i][0] * scalar;
            out_cast.eval[i][1] = this->eval[i][1] * scalar;
        } 
}
 
void PolynomialEvalFormLongComplex::neg(PolynomialEvalForm &out)const{
    PolynomialEvalFormLongComplex& out_cast = static_cast<PolynomialEvalFormLongComplex&>(out);
    for(int32_t i = 0; i < size; ++i){
            out_cast.eval[i][0] = -this->eval[i][0];
            out_cast.eval[i][1] = -this->eval[i][1];
        } 
}
    
Polynomial::Polynomial(int32_t degree, int64_t coef_modulus): Vector(degree, coef_modulus){ 
    this->init_from_vec();
}
 
Polynomial::Polynomial(const std::vector<int64_t>& in_vec, int32_t degree, int64_t coef_modulus): Vector(in_vec, degree, coef_modulus){
    this->init_from_vec(); 
}
 
Polynomial::Polynomial(const Polynomial &other, int64_t degree, int64_t coef_modulus): Vector(other, degree, coef_modulus){
    this->init_from_vec(); 
}
 
Polynomial& Polynomial::operator=(const Vector& other){ 
    this->size = other.size;
    this->modulus = other.modulus;
    init();
    this->init_from_vec();
    Utils::cp(this->vec, other.vec, this->size);  
    return *this;
}


Polynomial::Polynomial(const Vector& other): Vector(other){ 
    this->init_from_vec(); 
    Utils::cp(this->vec, other.vec, this->size);
}

void Polynomial::init_from_vec(){ 
    this->coef_modulus_bit_size = Utils::power_times(modulus, 2); 
}
 
Polynomial::Polynomial(const Polynomial &other): Vector(other.size, other.modulus){ 
    this->init_from_vec();
    Utils::cp(this->vec, other.vec, this->size);  
    this->mul_engine = other.mul_engine;
    this->is_mul_engine_set = other.is_mul_engine_set; 
    this->inv_engine = other.inv_engine;
    this->is_inv_engine_set = other.is_inv_engine_set;
} 
  
Polynomial& Polynomial::operator=(const Polynomial& other){ 
    this->size = other.size;
    this->modulus = other.modulus;
    init(); 
    this->init_from_vec(); 
    Utils::cp(this->vec, other.vec, this->size);  
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
    int32_t overflow= this->size - rotation ;  
      for(int32_t i = 0; i < overflow; ++i){   
            out.vec[i+rotation] = this->vec[i];
            
      }
      for(int32_t i = 0; i < rotation; ++i){ 
            out.vec[i] = this->vec[overflow + i];
      } 
}

void Polynomial::negacyclic_rotate(Polynomial &out, int64_t rotation)const{   
    /// TODO: That implementation is not the best.   

    long* temp = new long[this->size];
    if(rotation >= this->size){
        for(int32_t i = 0; i < this->size; ++i){
            temp[i] = -this->vec[i];
        }
        rotation = rotation - this->size;
    }else{
        for(int32_t i = 0; i < this->size; ++i){
            temp[i] = this->vec[i];
        }
    } 
    // NOTE We implement negacyclic rotate actually -> it changes the sign of rot first coefficients
    int32_t overflow=this->size - rotation ;  
    for(int32_t i = 0; i < overflow; ++i){   
        out.vec[i+rotation] = temp[i];
    }
    for(int32_t i = 0; i < rotation; ++i){ 
        out.vec[i] = -temp[overflow + i];
    }
    delete[] temp;
    out.normalize(); 
}
 
void Polynomial::to_eval(PolynomialEvalForm &out){ 
    mul_engine->to_eval(out, *this);
}

void Polynomial::to_eval(PolynomialEvalForm &out, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine){ 
    mul_engine->to_eval(out, *this);
}
  
std::shared_ptr<Polynomial> Polynomial::clone() const{ 
    std::shared_ptr<Polynomial> out = std::make_shared<Polynomial>(size, modulus);
    if(is_mul_engine_set){
        out->set_multiplication_engine(mul_engine);
    }
    if(is_inv_engine_set){
        out->set_inversion_engine(inv_engine);
    } 
    Utils::cp(out->vec, vec, size); 
    return out;
} 
   
void Polynomial::mul(Polynomial &out, int64_t scalar)const{ 
    if(this->size != out.size){
        throw std::logic_error("Polynomial::mul(Polynomial *out, int64_t scalar): Degrees of polynomials don't match!");
    }
    if(this->modulus != out.modulus){
        throw std::logic_error("Polynomial::mul(Polynomial *out, int64_t scalar): Coefficient moduli of polynomials don't match!");
    } 
    
    for(int32_t j=0; j < this->size; ++j){ 
        out.vec[j] = (int64_t)((__int128_t(vec[j]) * __int128_t(scalar)) % __int128_t(modulus)); 
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
}
 
PolynomialArrayCoefForm::PolynomialArrayCoefForm(int32_t degree, int64_t coef_modulus, int32_t array_size, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine){ 
    init(degree, coef_modulus, array_size); 
    this->mul_engine = mul_engine;
    is_mul_engine_set = true; 
}
  
PolynomialArrayCoefForm::PolynomialArrayCoefForm(const PolynomialArrayCoefForm &other){
    this->init(other.size, other.modulus, other.array_size);  
    Utils::cp(this->vec_array, other.vec_array, this->full_size);  
    this->mul_engine = other.mul_engine;
    this->is_mul_engine_set = other.is_mul_engine_set;  
} 
  
PolynomialArrayCoefForm& PolynomialArrayCoefForm::operator=(const PolynomialArrayCoefForm other){
    this->init(other.size, other.modulus, other.array_size); 
    Utils::cp(this->vec_array, other.vec_array, this->full_size);  
    this->mul_engine = other.mul_engine;
    this->is_mul_engine_set = other.is_mul_engine_set;  
    return *this;
}

void PolynomialArrayCoefForm::set_polynomial_at(int32_t i, const Polynomial &poly){
    if(poly.size != this->size){
        throw std::logic_error("PolynomialArrayCoefForm::set_polynomial_at(int32_t i, Polynomial *poly): degrees are inconsistent.");
    }
    if(poly.modulus != this->modulus){
        throw std::logic_error("PolynomialArrayCoefForm::set_polynomial_at(int32_t i, Polynomial *poly): coef_moduli are inconsistent.");
    }
    for(int32_t j = 0; j < this->size; ++j){
        this->vec_array[i * size + j] = poly.vec[j];
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
  
PolynomialArrayEvalFormComplex::~PolynomialArrayEvalFormComplex(){
    if(this->is_init){
        delete[] eval;
    }
}   

PolynomialArrayEvalFormComplex::PolynomialArrayEvalFormComplex(int32_t size, int32_t array_size){ 
    this->array_size = array_size; 
    this->size = size; 
    this->full_size = this->size * array_size; 
    this->eval = new Complex[full_size];   
    this->is_init = true;
}

void PolynomialArrayEvalFormComplex::add(PolynomialArrayEvalForm &out, const PolynomialArrayEvalForm &other){
    const PolynomialArrayEvalFormComplex& other_cast = static_cast<const PolynomialArrayEvalFormComplex&>(other);
    const PolynomialArrayEvalFormComplex& out_cast = static_cast<const PolynomialArrayEvalFormComplex&>(out);
    for(int32_t i = 0; i < full_size; ++i){
            out_cast.eval[i][0] = this->eval[i][0] + other_cast.eval[i][0];
            out_cast.eval[i][1] = this->eval[i][1] + other_cast.eval[i][1];
        } 
}

void PolynomialArrayEvalFormComplex::sub(PolynomialArrayEvalForm &out, const PolynomialArrayEvalForm &other){
    const PolynomialArrayEvalFormComplex& other_cast = static_cast<const PolynomialArrayEvalFormComplex&>(other);
    const PolynomialArrayEvalFormComplex& out_cast = static_cast<const PolynomialArrayEvalFormComplex&>(out);
    for(int32_t i = 0; i < full_size; ++i){
            out_cast.eval[i][0] = this->eval[i][0] - other_cast.eval[i][0];
            out_cast.eval[i][1] = this->eval[i][1] - other_cast.eval[i][1];
        } 
}

void PolynomialArrayEvalFormComplex::mul(PolynomialArrayEvalForm &out, int64_t scalar){
    PolynomialArrayEvalFormComplex& out_cast = static_cast<PolynomialArrayEvalFormComplex&>(out);
     for(int32_t i = 0; i < full_size; ++i){
            out_cast.eval[i][0] = this->eval[i][0] * scalar;
            out_cast.eval[i][1] = this->eval[i][1] * scalar;
        } 
}

void PolynomialArrayEvalFormComplex::neg(PolynomialArrayEvalForm &out){
    PolynomialArrayEvalFormComplex& out_cast = static_cast<PolynomialArrayEvalFormComplex&>(out);
    for(int32_t i = 0; i < full_size; ++i){
            out_cast.eval[i][0] = -this->eval[i][0];
            out_cast.eval[i][1] = -this->eval[i][1];
        } 
}
  
PolynomialArrayEvalFormLongComplex::~PolynomialArrayEvalFormLongComplex(){
    if(this->is_init){
        delete[] eval;
    }
}

PolynomialArrayEvalFormLongComplex::PolynomialArrayEvalFormLongComplex(int32_t size, int32_t array_size){ 
    this->array_size = array_size; 
    this->size = size; 
    this->full_size = this->size * array_size; 
    this->eval = new LongComplex[full_size];  
    this->is_init = true;
}

void PolynomialArrayEvalFormLongComplex::add(PolynomialArrayEvalForm &out, const PolynomialArrayEvalForm &other){
    const PolynomialArrayEvalFormLongComplex& out_cast = static_cast<const PolynomialArrayEvalFormLongComplex&>(out);
    const PolynomialArrayEvalFormLongComplex& other_cast = static_cast<const PolynomialArrayEvalFormLongComplex&>(other);
    for(int32_t i = 0; i < full_size; ++i){
        out_cast.eval[i][0] = this->eval[i][0] + other_cast.eval[i][0];
        out_cast.eval[i][1] = this->eval[i][1] + other_cast.eval[i][1];
    } 
}

void PolynomialArrayEvalFormLongComplex::sub(PolynomialArrayEvalForm &out, const PolynomialArrayEvalForm &other){
    PolynomialArrayEvalFormLongComplex& out_cast = static_cast<PolynomialArrayEvalFormLongComplex&>(out);
    const PolynomialArrayEvalFormLongComplex& other_cast = static_cast<const PolynomialArrayEvalFormLongComplex&>(other);
    for(int32_t i = 0; i < full_size; ++i){
        out_cast.eval[i][0] = this->eval[i][0] - other_cast.eval[i][0];
        out_cast.eval[i][1] = this->eval[i][1] - other_cast.eval[i][1];
    } 
}

void PolynomialArrayEvalFormLongComplex::mul(PolynomialArrayEvalForm &out, int64_t scalar){
    PolynomialArrayEvalFormLongComplex& out_cast = static_cast<PolynomialArrayEvalFormLongComplex&>(out);
    for(int32_t i = 0; i < full_size; ++i){
        out_cast.eval[i][0] = this->eval[i][0] * scalar;
        out_cast.eval[i][1] = this->eval[i][1] * scalar;
    }
}

void PolynomialArrayEvalFormLongComplex::neg(PolynomialArrayEvalForm &out){
    PolynomialArrayEvalFormLongComplex& out_cast = static_cast<PolynomialArrayEvalFormLongComplex&>(out);
    for(int32_t i = 0; i < full_size; ++i){
        out_cast.eval[i][0] = -this->eval[i][0];
        out_cast.eval[i][1] = -this->eval[i][1];
    } 
}



 