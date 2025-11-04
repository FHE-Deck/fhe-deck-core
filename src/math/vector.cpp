#include "math/vector.h"

using namespace FHEDeck;

 
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

int64_t& Vector::operator[](int32_t index){
    return vec[index];
}

const int64_t& Vector::operator[](int32_t index) const {
    return vec[index];
}

bool Vector::operator==(const Vector& other) const {
    if(size != other.size){ return false; }

    if(modulus != other.modulus){ return false; }

    if(modulus != other.modulus){ return false; }

     for(int32_t i = 0; i < size; ++i){
        if(vec[i] != other[i]){
            return false;
        }
    }
    return true;
}

bool Vector::operator!=(const Vector& other) const { 
    return !(*this == other); 
}


void Vector::add(Vector &out, const Vector &other) const{
    for(int32_t i = 0; i < size; ++i){
        out.vec[i] = vec[i] + other.vec[i];
        out.vec[i] %= this->modulus; 
    }
}
  
void Vector::sub(Vector &out, const Vector &other) const{ 
    for(int32_t i = 0; i < size; ++i){
        out.vec[i] =  Utils::integer_mod_form(this->vec[i] - other.vec[i], this->modulus);      
    } 
}
  
void Vector::neg(Vector &out){
    for(int32_t i = 0; i < size; ++i){
        out.vec[i] = this->modulus - this->vec[i];   
    }  
}

std::string Vector::to_string(int32_t size_of_string){
    if(size_of_string==0){
        return "[]";
    }
    if(size_of_string==1){
        return "[" + std::to_string(vec[0]) + "]" ;
    }
    std::string str = "[";
    for(int32_t i = 0; i < size_of_string-1; ++i){
        str += std::to_string(vec[i]) + ", ";
    }
    str += std::to_string(vec[size_of_string-1]) + "]";
    return str;
}
 
VectorArray::~VectorArray(){
    if(is_init){ 
        delete[] vec_array; 
        delete[] vec_array_2d; 
    }
}
 
VectorArray::VectorArray(int32_t size, int64_t modulus, int32_t array_size){
    init(size, modulus, array_size);  
}

void VectorArray::init(const int32_t size, const int64_t modulus, const int32_t array_size){ 
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


void VectorArray::add(VectorArray &out, const VectorArray &other){
    for(int32_t i = 0; i < full_size; ++i){
        out.vec_array[i] = vec_array[i] + other.vec_array[i];
        out.vec_array[i] %= this->modulus;
    }
}
  
void VectorArray::sub(VectorArray &out, const VectorArray &other){
    for(int32_t i = 0; i < full_size; ++i){
        out.vec_array[i] = Utils::integer_mod_form(this->vec_array[i] - other.vec_array[i], this->modulus);     
    } 
}
  
void VectorArray::neg(VectorArray &out){
    for(int32_t i = 0; i < full_size; ++i){
        out.vec_array[i] = this->modulus - this->vec_array[i];
    } 
}
  
void VectorArray::mul(VectorArray &out, const int64_t scalar){
    for(int32_t i = 0; i < full_size; ++i){
        out.vec_array[i] = Utils::integer_mod_form(vec_array[i] * scalar, this->modulus); 
    }
}