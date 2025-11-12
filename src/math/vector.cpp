#include "math/vector.h"

using namespace FHEDeck;


VectorView::VectorView(int64_t* vec, int64_t size, int64_t modulus): vec(vec), size(size), modulus(modulus){}

int64_t& VectorView::operator[](int32_t index){
    return vec[index];
}

const int64_t& VectorView::operator[](int32_t index) const {
    return vec[index];
}

bool VectorView::operator==(const VectorView& other) const {
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

bool VectorView::operator!=(const VectorView& other) const { 
    return !(*this == other); 
}


void VectorView::add(VectorView &out, const VectorView &other) const{
    for(int32_t i = 0; i < size; ++i){
        out.vec[i] = vec[i] + other.vec[i];
        out.vec[i] %= this->modulus; 
    }
}
  
void VectorView::sub(VectorView &out, const VectorView &other) const{ 
    for(int32_t i = 0; i < size; ++i){
        out.vec[i] =  Utils::integer_mod_form(this->vec[i] - other.vec[i], this->modulus);      
    } 
}
  
void VectorView::neg(VectorView &out){
    for(int32_t i = 0; i < size; ++i){
        out.vec[i] = this->modulus - this->vec[i];   
    }  
}

std::string VectorView::to_string(int32_t size_of_string){
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

void VectorView::array_signed_form(VectorView& out, const VectorView& in){
    if(out.size != in.size){ throw std::logic_error("Utils::array_signed_form(Vector& out, Vector& in): Vector sizes do not match."); }

    if(out.modulus != in.modulus){ throw std::logic_error("Utils::array_signed_form(Vector& out, Vector& in): Vector sizes do not match."); }

    for(int32_t i = 0; i < out.size; ++i){ 
        out[i] =  Utils::integer_signed_form(out[i], out.modulus);
    }
}
 

void VectorView::zeroize(){
    for(int32_t i = 0; i < size; ++i){
        vec[i] = 0;
    }
}

void VectorView::normalize(){
    for(int32_t i = 0; i < size; ++i){ 
        vec[i] = Utils::integer_mod_form(vec[i], modulus);
    }
}
  
Vector::Vector(int64_t size, int64_t modulus): VectorView(nullptr, size, modulus){ 
    init();
}
 
Vector::Vector(const Vector &other) : VectorView(nullptr, other.size, other.modulus){  
    init();
    Utils::cp(this->vec, other.vec, this->size);   
}
 
 
Vector& Vector::operator=(const Vector other) { 
    this->size = other.size;
    this->modulus = other.modulus;
    if(!this->is_init){  
        this->init(); 
    }
    Utils::cp(this->vec, other.vec, this->size);   
    return *this;
}
 
void Vector::init(){ 
    this->vec_memory = std::make_unique<int64_t[]>(size);
    this->vec = vec_memory.get();
    this->is_init = true;
}
 


VectorArray::VectorArray(int32_t size, int64_t modulus, int32_t array_size){
    init(size, modulus, array_size);  
}
 
VectorArray::~VectorArray(){
    if(is_init){ 
        delete[] vec_array; 
        delete[] vec_array_2d; 
    }
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

bool VectorArray::operator==(const VectorArray& other){
    if(this->size != other.size){ return false; }

    if(this->full_size != other.full_size){ return false; }

    if(this->modulus != other.modulus){ return false; }

    for(int32_t i = 0; i < full_size; ++i){
        if(vec_array[i] != other.vec_array[i]){
            return false;
        }
    }
    return true;
}

bool VectorArray::operator!=(const VectorArray& other){
    return !this->operator==(other);
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
 
void VectorArray::normalize(){
    for(int32_t i = 0; i < full_size; ++i){ 
        vec_array[i] = Utils::integer_mod_form(vec_array[i], modulus);
    }
}