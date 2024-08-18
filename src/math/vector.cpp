#include "vector.h"

using namespace fhe_deck;

 
Vector::~Vector(){
    if(is_init){ 
        delete[] vec; 
    }
}

Vector::Vector(int64_t size, int64_t modulus){
    init(size, modulus);
}

void Vector::init(int32_t size, int64_t modulus){
    this->size = size;
    this->modulus = modulus;
    vec = new int64_t[size];
    is_init = true;
}

void Vector::add(Vector *out, const Vector *other) const{
    for(int32_t i = 0; i < size; ++i){
        out->vec[i] = vec[i] + other->vec[i];
        out->vec[i] %= this->modulus; 
    }
}
  
void Vector::sub(Vector *out, const Vector *other) const{ 
    for(int32_t i = 0; i < size; ++i){
        out->vec[i] =  Utils::integer_mod_form(this->vec[i] - other->vec[i], this->modulus);      
    } 
}
  
void Vector::neg(Vector *out){
    for(int32_t i = 0; i < size; ++i){
        out->vec[i] = this->modulus - this->vec[i];   
    }  
}
 
VectorArray::~VectorArray(){
    if(is_init){ 
        delete[] vec_array; 
    }
}
 
VectorArray::VectorArray(int32_t size, int64_t modulus, int32_t array_size){
    init(size, modulus, array_size);  
}

void VectorArray::init(int32_t size, int64_t modulus, int32_t array_size){ 
    this->size = size;
    this->modulus = modulus;
    this->array_size = array_size; 
    this->full_size = this->array_size * this->size; 
    this->vec_array = new int64_t[full_size];
    this->is_init = true; 
    init_two_dim_array();
}

void VectorArray::init_two_dim_array(){
    vec_array_2d = new int64_t*[array_size];  
    // Point the polynomials to the uint64_t tables. 
    for(int32_t i = 0; i < array_size; ++i){ 
        vec_array_2d[i] = &vec_array[i * size];
    } 
}


void VectorArray::add(VectorArray *out, const VectorArray *other){
    for(int32_t i = 0; i < full_size; ++i){
        out->vec_array[i] = vec_array[i] + other->vec_array[i];
        out->vec_array[i] %= this->modulus;
    }
}
  
void VectorArray::sub(VectorArray *out, const VectorArray *other){
    for(int32_t i = 0; i < full_size; ++i){
        out->vec_array[i] = Utils::integer_mod_form(this->vec_array[i] - other->vec_array[i], this->modulus);     
    } 
}
  
void VectorArray::neg(VectorArray *out){
    for(int32_t i = 0; i < full_size; ++i){
        out->vec_array[i] = this->modulus - this->vec_array[i];
    } 
}
  
void VectorArray::mul(VectorArray *out, int64_t scalar){
    for(int32_t i = 0; i < full_size; ++i){
        out->vec_array[i] = Utils::integer_mod_form(vec_array[i] * scalar, this->modulus); 
    }
}