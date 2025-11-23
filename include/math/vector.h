#ifndef VECTOR_H
#define VECTOR_H
 
/**
 * @file vector.h
 */

#include "global_headers.h" 
#include "common/utils.h"  
  
namespace FHEDeck{
 
/// Define a new class Vector that derives from VectorView
class VectorView{
    
    public:
  

    int64_t size = 0;
    int64_t modulus = 0;

    VectorView() = default;
      
    /// @brief Takes pointer to external memory, size and the modulus of the vector, and defines a vector intervace that acts on the memory.
    /// @param vec The raw pointer to external memory. This class doesn't own that memory, and is not responsible for freeing it. 
    /// @param size The size of the memory block pointed by vec
    /// @param modulus the modulus of the arithmetic operation that we can perfom on that vector
    VectorView(int64_t* vec, int64_t size, int64_t modulus);
     
    /// @brief Overload the [] operator to write access to the vector
    /// @param index Index to be accessed. 
    /// @return The reference to the accessed element
    int64_t& operator[](int32_t index);

    /// @brief Overload the [] operator for read only acccess to the vector
    /// @param index Index to be accessed. 
    /// @return The reference to the accessed element
    const int64_t& operator[](int32_t index) const;

    bool operator==(const VectorView& other) const;

    bool operator!=(const VectorView& other) const;

    int64_t* get() const;

    /// @brief Zero all vector elements  
    void zeroize();

    /// @brief Computes all vector element modulo the modulus. This is used, when for instance, setting the coefficient vector to positive and negative integers.
    void normalize();

    void signed_form();
 
    /// @brief Adds other to this vector and stores the output in out.
    /// @param out The output vector
    /// @param other The input vector 
    void add(VectorView &out, const VectorView &other) const;
  
    /// @brief Subtracts other from this vector and stores the output in out.
    /// @param out The output vector
    /// @param other The input vector 
    void sub(VectorView &out, const VectorView &other) const;
  
    /// @brief Negates the coefficients of this vector and stores the output in out. 
    /// @param out The output vector
    void neg(VectorView &out);
 
    std::string to_string(int32_t size_of_string);
 
    static void array_signed_form(VectorView& out, const VectorView& in);

    protected:
 
    /// @brief The coefficients of the polynomial
    int64_t* vec = nullptr;  
 
};


class Vector : public VectorView{
    
    public:

    std::unique_ptr<int64_t[]> vec_memory;
 
    Vector() = default;

    Vector(int64_t size, int64_t modulus);

    Vector(const std::vector<int64_t>& in_vec, int64_t size, int64_t modulus);
 
    /// @brief Copy constructor
    /// @param other The Vector to copy
    Vector(const VectorView &other);

    /// @brief Copy constructor where however only size of the input vector is copied (this vector will be of this size) and vector elements are reduced modulo modulus.
    /// @param other The Vector to copy
    /// @note If size is bigger then other.size then the remaining vector elements are set to zero.
    Vector(const VectorView &other, int64_t size, int64_t modulus);

    /// @brief This is the copy assignment operator
    /// @param other The Vector to copy
    /// @return Return a reference to the copied Vector
    Vector& operator=(const VectorView other);


    /// @brief Called by the constructors to initialize the vector 
    void init();

    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const

    { 
        ar(size, modulus);   
        ar(cereal::binary_data(vec, sizeof(int64_t) * size));   
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
        ar(this->size, this->modulus); 
        init();
        ar(cereal::binary_data(vec, sizeof(int64_t) * size));    
    }  
    #endif 
 

};

/**
 * @brief Stores an array of Vectors in a continuous block of memory, but gives a two dimensional view of the data.
 */
class VectorArray{

    public:
    /// @brief The continuous block of memory that stores the vectors. 
    std::unique_ptr<int64_t[]> vec_array; 

    /// @brief Size of a single vector in the array
    int64_t size;
    /// @brief The modulus
    int64_t modulus;  
    /// @brief Size of the array
    int32_t array_size; 
    /// @brief full_size = degree * array_size. Initialized in the constructors. 
    int32_t full_size;
  
    VectorArray() = default;

    VectorArray(int32_t size, int64_t modulus, int32_t array_size);

    void init(int32_t size, int64_t modulus, int32_t array_size);
 
    VectorView operator[](int32_t index);

    const VectorView operator[](int32_t index)const;

    bool operator==(const VectorArray& other);

    bool operator!=(const VectorArray& other);

    /// @brief Coordinate wise addition of vector arrays
    /// @param out The resulting vector array
    /// @param other The input vector array
    void add(VectorArray &out, const VectorArray &other);
  
    /// @brief Coordinate wise subtraction of vectors arrays
    /// @param out The resulting vector array
    /// @param other The input vector array
    void sub(VectorArray &out, const VectorArray &other);
  
    /// @brief Coordinate negation of vectors in this arrays
    /// @param out The resulting vector array 
    void neg(VectorArray &out);
  
    /// @brief Coordinate wise scalar multiplication of polynomials in thie arrays
    /// @param out The resulting polynomial array
    /// @param other The input polynomial array
    void mul(VectorArray &out, int64_t scalar);

    /// @brief Computes all vector elements modulo the modulus. This is used, when for instance, setting the coefficient vector to positive and negative integers.
    void normalize();

    #if defined(USE_CEREAL)
    template <class Archive>
    void save( Archive & ar ) const
    { 
        ar(size, modulus, array_size);   
        ar(cereal::binary_data(vec_array, sizeof(int64_t) * size));  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
        ar(size, modulus, array_size);   
        init(size, modulus, array_size);   
        ar(cereal::binary_data(vec_array, sizeof(int64_t) * size));   
    }  
    #endif 

};

} /// End of namespace FHEDeck


#endif 