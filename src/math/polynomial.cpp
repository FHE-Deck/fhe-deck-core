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

int32_t PolynomialEvalForm::size() const{ 
    return m_size;
}

PolynomialEvalFormLongInteger::PolynomialEvalFormLongInteger(int64_t* eval_long, int32_t size, int64_t coef_modulus){
    this->eval_long = eval_long;
    this->coef_modulus = coef_modulus;
    this->is_init = true; 
    this->m_size = size;
}

void PolynomialEvalFormLongInteger::zeroize(){ 
    for(int32_t i = 0; i < m_size; ++i){
        this->eval_long[i] = 0;
    }
}

void PolynomialEvalFormLongInteger::add(PolynomialEvalForm &out, const PolynomialEvalForm &other)const{ 
    const PolynomialEvalFormLongInteger& other_cast = static_cast<const PolynomialEvalFormLongInteger&>(other);
    PolynomialEvalFormLongInteger& out_cast = static_cast<PolynomialEvalFormLongInteger&>(out);
    for(int32_t i = 0; i < m_size; ++i){
        out_cast.eval_long[i] = this->eval_long[i] + other_cast.eval_long[i];
    }
}

void PolynomialEvalFormLongInteger::sub(PolynomialEvalForm &out, const PolynomialEvalForm &other)const{
    const PolynomialEvalFormLongInteger& other_cast = static_cast<const PolynomialEvalFormLongInteger&>(other);
    PolynomialEvalFormLongInteger& out_cast = static_cast<PolynomialEvalFormLongInteger&>(out);
    for(int32_t i = 0; i < m_size; ++i){
        out_cast.eval_long[i] = this->eval_long[i] - other_cast.eval_long[i];
    }  
}

void PolynomialEvalFormLongInteger::mul(PolynomialEvalForm &out, int64_t scalar)const{
    PolynomialEvalFormLongInteger& out_cast = static_cast<PolynomialEvalFormLongInteger&>(out);
    for(int32_t i = 0; i < m_size; ++i){
        out_cast.eval_long[i] = this->eval_long[i] * scalar;
    } 
}
 
void PolynomialEvalFormLongInteger::neg(PolynomialEvalForm &out)const{
    PolynomialEvalFormLongInteger& out_cast = static_cast<PolynomialEvalFormLongInteger&>(out);
    for(int32_t i = 0; i < m_size; ++i){
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
    this->m_size = size; 
}

void PolynomialEvalFormComplex::zeroize(){
    for(int32_t i = 0; i < m_size; ++i){
        this->eval[i][0] = 0;
        this->eval[i][1] = 0;
    }
}

void PolynomialEvalFormComplex::add(PolynomialEvalForm &out, const PolynomialEvalForm &other)const{
    const PolynomialEvalFormComplex& other_cast = static_cast<const PolynomialEvalFormComplex&>(other);
    const PolynomialEvalFormComplex& out_cast = static_cast<const PolynomialEvalFormComplex&>(out);
    for(int32_t i = 0; i < m_size; ++i){
        out_cast.eval[i][0] = this->eval[i][0] + other_cast.eval[i][0];
        out_cast.eval[i][1] = this->eval[i][1] + other_cast.eval[i][1];
    } 
}

void PolynomialEvalFormComplex::sub(PolynomialEvalForm &out, const PolynomialEvalForm &other)const{
    const PolynomialEvalFormComplex& other_cast = static_cast<const PolynomialEvalFormComplex&>(other);
    const PolynomialEvalFormComplex& out_cast = static_cast<const PolynomialEvalFormComplex&>(out);
    for(int32_t i = 0; i < m_size; ++i){
        out_cast.eval[i][0] = this->eval[i][0] - other_cast.eval[i][0];
        out_cast.eval[i][1] = this->eval[i][1] - other_cast.eval[i][1];
    } 
}

void PolynomialEvalFormComplex::mul(PolynomialEvalForm &out, int64_t scalar)const{
    PolynomialEvalFormComplex& out_cast = static_cast<PolynomialEvalFormComplex&>(out);
    for(int32_t i = 0; i < m_size; ++i){
        out_cast.eval[i][0] = this->eval[i][0] * scalar;
        out_cast.eval[i][1] = this->eval[i][1] * scalar;
    }  
}
 
void PolynomialEvalFormComplex::neg(PolynomialEvalForm &out)const{ 
    PolynomialEvalFormComplex& out_cast = static_cast<PolynomialEvalFormComplex&>(out);
    for(int32_t i = 0; i < m_size; ++i){
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
    this->m_size = size; 
}

void PolynomialEvalFormLongComplex::zeroize(){
    for(int32_t i = 0; i < m_size; ++i){
        this->eval[i][0] = 0;
        this->eval[i][1] = 0;
    }
}

void PolynomialEvalFormLongComplex::add(PolynomialEvalForm &out, const PolynomialEvalForm &other)const{
    const PolynomialEvalFormLongComplex& other_cast = static_cast<const PolynomialEvalFormLongComplex&>(other);
    PolynomialEvalFormLongComplex& out_cast = static_cast<PolynomialEvalFormLongComplex&>(out);
    for(int32_t i = 0; i < m_size; ++ i){
        out_cast.eval[i][0] = this->eval[i][0] + other_cast.eval[i][0];
        out_cast.eval[i][1] = this->eval[i][1] + other_cast.eval[i][1];
    }       
}
 
void PolynomialEvalFormLongComplex::sub(PolynomialEvalForm &out, const PolynomialEvalForm &other)const{
    const PolynomialEvalFormLongComplex& other_cast = static_cast<const PolynomialEvalFormLongComplex&>(other);
    PolynomialEvalFormLongComplex& out_cast = static_cast<PolynomialEvalFormLongComplex&>(out);
    for(int32_t i = 0; i < m_size; ++i){
        out_cast.eval[i][0] = this->eval[i][0] - other_cast.eval[i][0];
        out_cast.eval[i][1] = this->eval[i][1] - other_cast.eval[i][1];
    } 
}

void PolynomialEvalFormLongComplex::mul(PolynomialEvalForm &out, int64_t scalar)const{
    PolynomialEvalFormLongComplex& out_cast = static_cast<PolynomialEvalFormLongComplex&>(out);
    for(int32_t i = 0; i < m_size; ++i){
            out_cast.eval[i][0] = this->eval[i][0] * scalar;
            out_cast.eval[i][1] = this->eval[i][1] * scalar;
        } 
}
 
void PolynomialEvalFormLongComplex::neg(PolynomialEvalForm &out)const{
    PolynomialEvalFormLongComplex& out_cast = static_cast<PolynomialEvalFormLongComplex&>(out);
    for(int32_t i = 0; i < m_size; ++i){
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
 
Polynomial& Polynomial::operator=(const VectorView& other){ 
    m_size = other.size();
    m_modulus = other.modulus();
    init();
    this->init_from_vec();
    Utils::cp(m_vec, other.get(), m_size);  
    return *this;
}


Polynomial::Polynomial(const VectorView& other): Vector(other){ 
    this->init_from_vec();  
}

void Polynomial::init_from_vec(){ 
    this->coef_modulus_bit_size = Utils::power_times(m_modulus, 2); 
}
 
Polynomial::Polynomial(const Polynomial &other): Vector(other.size(), other.modulus()){ 
    this->init_from_vec();
    Utils::cp(m_vec, other.m_vec, m_size);  
    this->mul_engine = other.mul_engine;
    this->is_mul_engine_set = other.is_mul_engine_set; 
    this->inv_engine = other.inv_engine;
    this->is_inv_engine_set = other.is_inv_engine_set;
} 
  
Polynomial& Polynomial::operator=(const Polynomial& other){ 
    m_size = other.size();
    m_modulus = other.modulus();
    init(); 
    this->init_from_vec(); 
    Utils::cp(m_vec, other.m_vec, m_size);  
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
    int32_t overflow= m_size - rotation ;  
      for(int32_t i = 0; i < overflow; ++i){   
            out.m_vec[i+rotation] = m_vec[i];
            
      }
      for(int32_t i = 0; i < rotation; ++i){ 
            out.m_vec[i] = m_vec[overflow + i];
      } 
}

void Polynomial::negacyclic_rotate(Polynomial &out, int64_t rotation)const{   
    /// TODO: That implementation is not the best.    
    long* temp = new long[m_size];
    if(rotation >= m_size){
        for(int32_t i = 0; i < m_size; ++i){
            temp[i] = -m_vec[i];
        }
        rotation = rotation - m_size;
    }else{
        for(int32_t i = 0; i < m_size; ++i){
            temp[i] = m_vec[i];
        }
    } 
    // NOTE We implement negacyclic rotate actually -> it changes the sign of rot first coefficients
    int32_t overflow=m_size - rotation ;  
    for(int32_t i = 0; i < overflow; ++i){   
        out.m_vec[i+rotation] = temp[i];
    }
    for(int32_t i = 0; i < rotation; ++i){ 
        out.m_vec[i] = -temp[overflow + i];
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
    std::shared_ptr<Polynomial> out = std::make_shared<Polynomial>(m_size, m_modulus);
    if(is_mul_engine_set){
        out->set_multiplication_engine(mul_engine);
    }
    if(is_inv_engine_set){
        out->set_inversion_engine(inv_engine);
    } 
    Utils::cp(out->m_vec, m_vec, m_size); 
    return out;
} 
   
void Polynomial::mul(Polynomial &out, int64_t scalar)const{ 
    if(m_size != out.size()){
        throw std::logic_error("Polynomial::mul(Polynomial *out, int64_t scalar): Degrees of polynomials don't match!");
    }
    if(m_modulus != out.modulus()){
        throw std::logic_error("Polynomial::mul(Polynomial *out, int64_t scalar): Coefficient moduli of polynomials don't match!");
    } 
    
    for(int32_t j=0; j < m_size; ++j){ 
        out.m_vec[j] = (int64_t)((__int128_t(m_vec[j]) * __int128_t(scalar)) % __int128_t(m_modulus)); 
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
 
PolynomialArray::PolynomialArray(int32_t degree, int64_t coef_modulus, int32_t array_size){ 
    init(degree, coef_modulus, array_size); 
}
 
PolynomialArray::PolynomialArray(int32_t degree, int64_t coef_modulus, int32_t array_size, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine){ 
    init(degree, coef_modulus, array_size); 
    this->mul_engine = mul_engine;
    is_mul_engine_set = true; 
}
  
PolynomialArray::PolynomialArray(const PolynomialArray &other){
    this->init(other.m_vector_size, other.m_modulus, other.m_array_size);  
    Utils::cp(m_vec_array.get(), other.m_vec_array.get(), this->m_full_size);  
    this->mul_engine = other.mul_engine;
    this->is_mul_engine_set = other.is_mul_engine_set;  
} 
  
PolynomialArray& PolynomialArray::operator=(const PolynomialArray other){
    this->init(other.m_vector_size, other.m_modulus, other.m_array_size); 
    Utils::cp(this->m_vec_array.get(), other.m_vec_array.get(), this->m_full_size);  
    this->mul_engine = other.mul_engine;
    this->is_mul_engine_set = other.is_mul_engine_set;  
    return *this;
}

void PolynomialArray::set_polynomial_at(int32_t i, const Polynomial &poly){
    if(poly.size() != this->m_vector_size){
        throw std::logic_error("PolynomialArray::set_polynomial_at(int32_t i, Polynomial *poly): degrees are inconsistent.");
    }
    if(poly.modulus() != m_modulus){
        throw std::logic_error("PolynomialArray::set_polynomial_at(int32_t i, Polynomial *poly): coef_moduli are inconsistent.");
    }
    for(int32_t j = 0; j < m_vector_size; ++j){
        m_vec_array[i * m_vector_size + j] = poly[j];
    }
}
 
void PolynomialArray::set_multiplication_engine(std::shared_ptr<PolynomialMultiplicationEngine> mul_engine){
    this->mul_engine = mul_engine;
}
     
PolynomialArrayEvalFormLong::PolynomialArrayEvalFormLong(int32_t array_size, int64_t degree, int64_t coef_modulus){
    this->array_size = array_size;
    this->size = degree;
    this->coef_modulus = coef_modulus;
    this->full_size = array_size * this->size; 
    this->eval_long = std::make_unique<int64_t[]>(full_size); 
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
 
Observer<int64_t[]> PolynomialArrayEvalFormLong::operator[](std::size_t i){
    return Observer<int64_t[]>(&eval_long[i * size], size);
}

const Observer<int64_t[]> PolynomialArrayEvalFormLong::operator[](std::size_t i) const{
    return Observer<int64_t[]>(&eval_long[i * size], size);
}
   
PolynomialArrayEvalFormComplex::PolynomialArrayEvalFormComplex(int32_t size, int32_t array_size){ 
    this->array_size = array_size; 
    this->size = size; 
    this->full_size = this->size * array_size;   
    this->eval = std::make_unique<Complex[]>(full_size); 
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

Observer<Complex[]> PolynomialArrayEvalFormComplex::operator[](std::size_t i){
    return Observer<Complex[]>(&eval[i * size], size);
}

const Observer<Complex[]> PolynomialArrayEvalFormComplex::operator[](std::size_t i) const{
    return Observer<Complex[]>(&eval[i * size], size);
}
   
PolynomialArrayEvalFormLongComplex::PolynomialArrayEvalFormLongComplex(int32_t size, int32_t array_size){ 
    this->array_size = array_size; 
    this->size = size; 
    this->full_size = this->size * array_size;  
    this->eval = std::make_unique<LongComplex[]>(full_size); 
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
 
Observer<LongComplex[]> PolynomialArrayEvalFormLongComplex::operator[](std::size_t i){
    return Observer<LongComplex[]>(&eval[i * size], size);
}

const Observer<LongComplex[]> PolynomialArrayEvalFormLongComplex::operator[](std::size_t i) const{
    return Observer<LongComplex[]>(&eval[i * size], size);
}


 