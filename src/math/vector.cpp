#include "math/vector.h"

using namespace FHEDeck;


VectorView::VectorView(int64_t* vec, int64_t size, int64_t modulus): m_vec(vec), m_size(size), m_modulus(modulus){}

int64_t& VectorView::operator[](int32_t index){
    return m_vec[index];
}

int64_t VectorView::operator[](int32_t index) const {
    return m_vec[index];
}

bool VectorView::operator==(const VectorView& other) const {
    if(m_size != other.m_size){ return false; }

    if(m_modulus != other.m_modulus){ return false; }

    if(m_modulus != other.m_modulus){ return false; }

     for(int32_t i = 0; i < m_size; ++i){
        if(m_vec[i] != other[i]){
            return false;
        }
    }
    return true;
}

bool VectorView::operator!=(const VectorView& other) const { 
    return !(*this == other); 
}
 
void VectorView::add(VectorView &out, const VectorView &other) const{
    for(int32_t i = 0; i < m_size; ++i){
        out.m_vec[i] = m_vec[i] + other.m_vec[i];
        out.m_vec[i] %= m_modulus; 
    }
}
  
void VectorView::sub(VectorView &out, const VectorView &other) const{ 
    for(int32_t i = 0; i < m_size; ++i){
        out.m_vec[i] =  Utils::integer_mod_form(m_vec[i] - other.m_vec[i], m_modulus);      
    } 
}
  
void VectorView::neg(VectorView &out)const{
    for(int32_t i = 0; i < m_size; ++i){
        out.m_vec[i] = m_modulus - m_vec[i];   
    }  
}

std::string VectorView::to_string(int32_t size_of_string)const{
    if(size_of_string==0){
        return "[]";
    }
    if(size_of_string==1){
        return "[" + std::to_string(m_vec[0]) + "]" ;
    }
    std::string str = "[";
    for(int32_t i = 0; i < size_of_string-1; ++i){
        str += std::to_string(m_vec[i]) + ", ";
    }
    str += std::to_string(m_vec[size_of_string-1]) + "]";
    return str;
}

void VectorView::array_signed_form(VectorView& out, const VectorView& in){
    if(out.m_size != in.m_size){ throw std::logic_error("Utils::array_signed_form(Vector& out, Vector& in): Vector sizes do not match."); }

    if(out.m_modulus != in.m_modulus){ throw std::logic_error("Utils::array_signed_form(Vector& out, Vector& in): Vector sizes do not match."); }

    for(int32_t i = 0; i < out.m_size; ++i){ 
        out[i] =  Utils::integer_signed_form(out[i], out.m_modulus);
    }
}

int64_t* VectorView::get() const{
    return m_vec;
}

int64_t VectorView::size() const{
    return m_size;
}

int64_t VectorView::modulus() const{
    return m_modulus;
}
  
void VectorView::zeroize(){
    for(int32_t i = 0; i < m_size; ++i){
        m_vec[i] = 0;
    }
}

void VectorView::normalize(){
    for(int32_t i = 0; i < m_size; ++i){ 
        m_vec[i] = Utils::integer_mod_form(m_vec[i], m_modulus);
    }
}
  
void VectorView::signed_form(){
        for(int32_t i = 0; i < m_size; ++i){ 
        m_vec[i] =  Utils::integer_signed_form(m_vec[i], m_modulus);
    }
}
  
Vector::Vector(int64_t size, int64_t modulus): VectorView(nullptr, size, modulus){ 
    init();
}

Vector::Vector(const std::vector<int64_t>& in_vec, int64_t size, int64_t modulus): VectorView(nullptr, size, modulus){
    init();
    std::size_t min_size = in_vec.size();
    if(min_size > size){ min_size = size ;}

    for(std::size_t i=0; i < min_size; ++i){
        m_vec[i] = in_vec[i];
    } 
    normalize();
}

Vector::Vector(const VectorView &other, int64_t size, int64_t modulus): VectorView(nullptr, size, modulus){  
    init();
    std::size_t min_size = other.size();
    if(min_size > size){ min_size = size ;}

    for(std::size_t i=0; i < min_size; ++i){
        m_vec[i] = other[i];
    } 
    normalize();  
}
 
Vector::Vector(const VectorView &other) : VectorView(nullptr, other.size(), other.modulus()){  
    init();
    for(std::size_t i{0}; i < m_size; ++i){
        m_vec[i] = other[i];
    }  
}
 
Vector& Vector::operator=(const VectorView other) { 
    m_size = other.size();
    m_modulus = other.modulus(); 
    this->init();  
    for(std::size_t i{0}; i < m_size; ++i){
        m_vec[i] = other[i];
    }
    return *this;
}
 
void Vector::init(){ 
    m_vec_memory = std::make_unique<int64_t[]>(m_size);
    m_vec = m_vec_memory.get(); 
    zeroize();
}
  
VectorArray::VectorArray(int32_t size, int64_t modulus, int32_t array_size){
    init(size, modulus, array_size);  
}
   
void VectorArray::init(const int32_t size, const int64_t modulus, const int32_t array_size){ 
    m_vector_size = size;
    m_modulus = modulus;
    m_array_size = array_size; 
    m_full_size = m_array_size * m_vector_size;  
    m_vec_array = std::make_unique<int64_t[]>(m_full_size); 
}
  
VectorView VectorArray::operator[](int32_t index){
    int64_t* observer_ptr = m_vec_array.get(); 
    return VectorView(&observer_ptr[index * m_vector_size], m_vector_size, m_modulus);
}

const VectorView VectorArray::operator[](int32_t index)const{
    int64_t* observer_ptr = m_vec_array.get(); 
    return VectorView(&observer_ptr[index * m_vector_size], m_vector_size, m_modulus);
}

bool VectorArray::operator==(const VectorArray& other)const{
    if(m_vector_size != other.m_vector_size){ return false; }

    if(m_full_size != other.m_full_size){ return false; }

    if(m_modulus != other.m_modulus){ return false; }

    for(int32_t i = 0; i < m_full_size; ++i){
        if(m_vec_array[i] != other.m_vec_array[i]){
            return false;
        }
    }
    return true;
}

bool VectorArray::operator!=(const VectorArray& other)const{
    return !this->operator==(other);
}
 
void VectorArray::add(VectorArray &out, const VectorArray &other)const{
    for(int32_t i = 0; i < m_full_size; ++i){
        out.m_vec_array[i] = m_vec_array[i] + other.m_vec_array[i];
        out.m_vec_array[i] %= m_modulus;
    }
}
  
void VectorArray::sub(VectorArray &out, const VectorArray &other)const{
    for(int32_t i = 0; i < m_full_size; ++i){
        out.m_vec_array[i] = Utils::integer_mod_form(m_vec_array[i] - other.m_vec_array[i], m_modulus);     
    } 
}
  
void VectorArray::neg(VectorArray &out)const{
    for(int32_t i = 0; i < m_full_size; ++i){
        out.m_vec_array[i] = m_modulus - m_vec_array[i];
    } 
}
  
void VectorArray::mul(VectorArray &out, const int64_t scalar)const{
    for(int32_t i = 0; i < m_full_size; ++i){
        out.m_vec_array[i] = Utils::integer_mod_form(m_vec_array[i] * scalar, m_modulus); 
    }
}
 
void VectorArray::normalize(){
    for(int32_t i = 0; i < m_full_size; ++i){ 
        m_vec_array[i] = Utils::integer_mod_form(m_vec_array[i], m_modulus);
    }
}

int32_t VectorArray::size() const {
    return m_array_size;
}

int64_t VectorArray::vector_size() const{
    return m_vector_size;
}
  
int32_t VectorArray::full_size() const{
    return m_full_size;
}