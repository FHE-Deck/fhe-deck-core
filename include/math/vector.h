#ifndef VECTOR_H
#define VECTOR_H
 
/**
 * @file vector.h
 */

#include <memory> 
#include <cinttypes>

 
#include "common/utils.h"  
 
#include <cereal/archives/binary.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>

namespace fhe_deck{

class Vector{
    
    public:

    ~Vector();

    /// @brief The coefficients of the polynomial
    int64_t* vec; 
    /// @brief Indicates if the polynomial has been initialized
    bool is_init = false;

    int64_t size;
    int64_t modulus;
    
    Vector() = default;

    Vector(int64_t size, int64_t modulus);
 
    
    /// @brief Called by the constructors to initialize the vector
    /// @param size The size of the vector
    /// @param modulus The modulus
    void init(int32_t size, int64_t modulus);

    /// @brief Adds other to this vector and stores the output in out.
    /// @param out The output vector
    /// @param other The input vector 
    void add(Vector &out, const Vector &other) const;
  
    /// @brief Subtracts other from this vector and stores the output in out.
    /// @param out The output vector
    /// @param other The input vector 
    void sub(Vector &out, const Vector &other) const;
  
    /// @brief Negates the coefficients of this vector and stores the output in out. 
    /// @param out The output vector
    void neg(Vector &out);

    template <class Archive>
    void save( Archive & ar ) const

    { 
        ar(size, modulus);   
        ar(cereal::binary_data(vec, sizeof(int64_t) * size));  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
        ar(size, modulus); 
        init(size, modulus);   
        ar(cereal::binary_data(vec, sizeof(int64_t) * size));   
    }  

};

/**
 * @brief Stores an array of Vectors in a continuous block of memory, but gives a two dimensional view of the data.
 */
class VectorArray{

    public:
    /// @brief The continuous block of memory that stores the vectors.
    int64_t* vec_array;  
    /// @brief The coefficients of the polynomial
    int64_t** vec_array_2d; 
    /// @brief Indicates if the polynomial has been initialized
    bool is_init = false;

    /// @brief Size of a single vector in the array
    int64_t size;
    /// @brief The modulus
    int64_t modulus;  
    /// @brief Size of the array
    int32_t array_size; 
    /// @brief full_size = degree * array_size. Initialized in the constructors. 
    int32_t full_size;

    ~VectorArray();

    VectorArray() = default;

    VectorArray(int32_t size, int64_t modulus, int32_t array_size);

    void init(int32_t size, int64_t modulus, int32_t array_size);

    void init_two_dim_array();

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

};

}


#endif 