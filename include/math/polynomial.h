#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

/**
 * @file polynomial.h
 */

#include <memory> 
#include "common/enums.h"
#include "common/utils.h"  
#include "math/vector.h"
   

#include <cereal/archives/binary.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>


typedef double Complex[2];
typedef long double LongComplex[2];

namespace fhe_deck{
      
/// Forward declaration if the Polynomial class and PolynomialEvalForm class that used by all other classes.
/// Both are defined in this file.
class Polynomial; 
class PolynomialEvalForm;

/// Forward declarations of PolynomialArrayCoefForm and PolynomialArrayEvalForm classes, as these classes refer to each other.
class PolynomialArrayCoefForm;
class PolynomialArrayEvalForm;
 
/**
 * @brief Interface that handles polynomial multiplication. 
 */
class PolynomialMultiplicationEngine{

    public: 
    /// @brief Type of the polynomial arithmetic
    PolynomialArithmetic type;

    /// @brief Initialialilzes a new PolynomialEvalForm object
    /// @return A pointer to the new PolynomialEvalForm object
    virtual std::shared_ptr<PolynomialEvalForm> init_polynomial_eval_form() = 0;

    /// @brief Initialliases a new PolynomialArrayCoefForm object
    /// @param array_size The array size
    /// @return A pointer to the new PolynomialArrayCoefForm object
    virtual std::shared_ptr<PolynomialArrayEvalForm> init_polynomial_array_eval_form(int32_t array_size) = 0;
  
    /// @brief Computes the evaluation form of a polynomial
    /// @param in Output in evaluation form
    /// @param out The input polyniomial in coefficient form
    virtual void to_eval(PolynomialEvalForm &out, const  Polynomial &in)= 0; 

    /// @brief Compute the evaluation for of a polynomial array
    /// @param in The output polynomial array in evaluation form 
    /// @param out The input polynomial array in coefficient form
    virtual void to_eval(PolynomialArrayEvalForm &out, const PolynomialArrayCoefForm &in) = 0;
  
    /// @brief Computes the coefficient form from the evaluation form of a polynomial
    /// @param in The input polynomial in evaluation form
    /// @param out The output polynomial in coefficient form
    virtual void to_coef(Polynomial &out, const PolynomialEvalForm &in) = 0; 

    /// @brief Computes the coefficient form from the evaluation form of an array of polynomials
    /// @param in The input polynomial array in evaluation form
    /// @param out The output polynomial array in coefficient form
    virtual void to_coef(PolynomialArrayCoefForm &out, const PolynomialArrayEvalForm &in) = 0;

    /// @brief Multiplies two polynomials that are given in evaluation form.
    /// @param out The output polynomial in evaluation form
    /// @param in_1 The first input polynomial in evaluation form
    /// @param in_2 The second input polynomial in evaluation form
    virtual void mul(PolynomialEvalForm &out, const PolynomialEvalForm &in_1, const PolynomialEvalForm &in_2) = 0;
 
    /// @brief Multiplies polynomials given in coefficient form
    /// @param out The output polynomial in coefficient form
    /// @param in_1 The first input polynomial in coefficient form
    /// @param in_2 The second input polynomial in coefficient form
    virtual void mul(Polynomial &out, const Polynomial &in_1,  const Polynomial &in_2); 
   
    /// @brief Computes the inner product or the given polynomial arrays. That is, it computes the sum of the element-wise products of the polynomials in the given arrays.
    /// @param out The output polynomial in coefficient form
    /// @param in_1 The first input polynomial array in coefficient form
    /// @param in_2 The second input polynomial array in evaluation form
    virtual void multisum(Polynomial &out, const PolynomialArrayCoefForm &in_1, const PolynomialArrayEvalForm &in_2) = 0;

    /// @brief Computes the inner product or the given polynomial arrays. That is, it computes the sum of the element-wise products of the polynomials in the given arrays.
    /// @param out The output polynomial in coefficient form
    /// @param in_1 The first input polynomial array in evalulation form
    /// @param in_2 The second input polynomial array in evaluation form
    virtual void multisum(Polynomial &out, const PolynomialArrayEvalForm &in_1, const PolynomialArrayEvalForm &in_2) = 0;
 
    /// @brief Computes the inner product or the given polynomial arrays. That is, it computes the sum of the element-wise products of the polynomials in the given arrays.
    /// @param out The output polynomial in coefficient form
    /// @param out_in_1_eval Teh evaluation form of in_1
    /// @param in_1 The first input polynomial array in coefficient form
    /// @param in_2 The second input polynomial array in evaluation form
    virtual void multisum(Polynomial &out_multisum, PolynomialArrayEvalForm &out_in_1_eval, const PolynomialArrayCoefForm &in_1, const PolynomialArrayEvalForm &in_2) = 0;
 
};

/**
 * @brief Interface that handles polynomial inversion. 
 */
class PolynomialInversionEngine{

    public: 
      
    /// @brief Computes the multiplivative inverse of the given polynomial, if such inverse exists. 
    /// @param out The output polynomial
    /// @param in The input polynomial
    virtual bool inv(Polynomial &out, const Polynomial &in)const = 0;
 
};

 
/**
 * @brief Interface that handles evaluation forms of polynomials. These are polynomials after computing a Fast Fourier Transform (in the frequency domain).  
 */
class PolynomialEvalForm{

    public:
 
    /// @brief The size of the evaluation form (not that this may differ from the degree of the polynomial)
    int32_t size; 
 
    /// @brief Default destructor
    virtual ~PolynomialEvalForm() = default;

    /// @brief Zeroizes all entries of the evaluation form
    virtual void zeroize() = 0;
  
    /// @brief Adds other to this polynomial and stores the output in out.
    /// @param out The output polynomial
    /// @param other The input polynomial
    virtual void add(PolynomialEvalForm &out, const PolynomialEvalForm &other)const = 0;
    
    /// @brief Subtracts other to this polynomial and stores the output in out.
    /// @param out The output polynomial
    /// @param other The input polynomial
    virtual void sub(PolynomialEvalForm &out, const PolynomialEvalForm &other)const = 0;
    
    /// @brief Multiplies scalar with this polynomial and stores the output in out.
    /// @param out The output polynomial
    /// @param scalar The input scalar
    virtual void mul(PolynomialEvalForm &out, int64_t scalar)const = 0; 
    
    /// @brief Negates this polynomial and stores the output in out.
    /// @param out The output polynomial 
    virtual void neg(PolynomialEvalForm &out)const = 0; 
 
};

/**
 * @brief Implementation of PolynomialEvalForm that represents a polynomial in evaluation form where the entries int64_t integers. 
 */
class PolynomialEvalFormLongInteger : public PolynomialEvalForm{

    public:
    /// @brief The evaluation form of the polynomial
    int64_t* eval_long; 
    /// @brief Indicates if eval_long has been initialized
    bool is_init = false;
    /// @brief The coefficient modulus
    int64_t coef_modulus;

    /// @brief Default destructor
    ~PolynomialEvalFormLongInteger();

    /// @brief Constructor
    /// @param eval_long Takes the evaluation form of the polynomial. The constructed object is now the owner of eval_long.
    /// @param size The size of the evaluation form
    /// @param coef_modulus The coefficient modulus
    /// TODO: Check if eval_long can be initialized in the constructor (there may be no reason to init it from the outside)
    PolynomialEvalFormLongInteger(int64_t* eval_long, int32_t size, int64_t coef_modulus);

    void zeroize();

    void add(PolynomialEvalForm &out, const PolynomialEvalForm &other)const override;

    void sub(PolynomialEvalForm &out, const PolynomialEvalForm &other)const override;

    void mul(PolynomialEvalForm &out, int64_t scalar)const override;

    void neg(PolynomialEvalForm &out)const override;
 
};

/**
 * @brief Implementation of PolynomialEvalForm that represents a polynomial in evaluation form where the entries are fftw_complex (64-bit) numbers. 
 */
class PolynomialEvalFormFFTWComplex : public PolynomialEvalForm{

    public:
    
    /// @brief The evaluation form of the polynomial
    Complex* eval_fftw;
    /// @brief Indicates if eval_fftw has been initialized
    bool is_init = false;
    /// @brief Indicates current scale, that is used in to_coef
    double scale = 1.0;

    /// @brief Default destructor
    ~PolynomialEvalFormFFTWComplex();	

    /// @brief Constructor
    /// @param eval_fftw Takes the evaluation form of the polynomial. The constructed object is now the owner of eval_fftw.
    /// @param size The size of the evaluation form
    /// @param coef_modulus The coefficient modulus
    PolynomialEvalFormFFTWComplex(Complex* eval_fftw, int32_t size);

    void zeroize();

    void add(PolynomialEvalForm &out, const PolynomialEvalForm &other)const override;

    void sub(PolynomialEvalForm &out, const PolynomialEvalForm &other)const override;

    void mul(PolynomialEvalForm &out, int64_t scalar)const override;

    void neg(PolynomialEvalForm &out)const override;
 
};

/**
 * @brief Implementation of PolynomialEvalForm that represents a polynomial in evaluation form where the entries are fftwl_complex (128-bit) numbers. 
 */
class PolynomialEvalFormFFTWLongComplex : public PolynomialEvalForm{

    public:
 
    /// @brief The evaluation form of the polynomial
    LongComplex* eval_fftwl;
    /// @brief Indicates if eval_fftwl has been initialized
    bool is_init = false;

    long double scale = 1.0;

    /// @brief Default destructor
    ~PolynomialEvalFormFFTWLongComplex();	

    /// @brief Constructor
    /// @param eval_fftwl Takes the evaluation form of the polynomial. The constructed object is now the owner of eval_fftwl.
    /// @param size The size of the evaluation form
    /// @param coef_modulus The coefficient modulus
    PolynomialEvalFormFFTWLongComplex(LongComplex* eval_fftwl, int32_t size);

    void zeroize();

    void add(PolynomialEvalForm &out, const PolynomialEvalForm &other)const override;

    void sub(PolynomialEvalForm &out, const PolynomialEvalForm &other)const override;

    void mul(PolynomialEvalForm &out, int64_t scalar)const override;

    void neg(PolynomialEvalForm &out)const override;
 
};

/**
 * @brief The Polynomials class. Holds an array of int64_t coefficients. Implement basic operations on polynomials modulo a coefficient modulus.
 */
class Polynomial: public Vector{

    public:

    /// @brief The coefficients of the polynomial (points to the vec array in the Vector class)
    int64_t* coefs; 
    /// @brief Indicates if the polynomial has been initialized
    //bool is_init = false;

    /// @brief The coefficient modulus
    int64_t coef_modulus;
    /// @brief The bit size of the coefficient modulus
    int32_t coef_modulus_bit_size;
    /// @brief The degree of the polynomial
    int32_t degree;
    /// @brief The polynomial multiplication engine (optional)
    std::shared_ptr<PolynomialMultiplicationEngine> mul_engine;
    /// @brief Indicates if the polynomial multiplication engine has been set
    bool is_mul_engine_set = false;
    /// @brief The polynomial inversion engine (optional)
    std::shared_ptr<PolynomialInversionEngine> inv_engine;
    /// @brief Indicates if the polynomial inversion engine has been set
    bool is_inv_engine_set = false;
  
    /// @brief Default constructor
    Polynomial() = default;

    /// @brief Constructs the polynomial, and allocates memory for the coefs array.
    /// @param degree The degree of the polynomial (size of the coefs array)
    /// @param coef_modulus The coefficient modulus
    Polynomial(int32_t degree, int64_t coef_modulus);

    /// @brief Constructs the polynomial, and allocates memory for the coefs array.
    /// @param coefs The coefs array which is going to be copied.
    /// @param degree The degree of the polynomial (size of the coefs array)
    /// @param coef_modulus The coefficient modulus
    Polynomial(int64_t* coefs, int32_t degree, int64_t coef_modulus);

    void init_from_vec();
  
    /// @brief Copy constructor
    /// @param other The polynomail to copy
    Polynomial(const Polynomial &other);

    /// @brief This is the copy assignment operator
    /// @param other The polynomial to copy
    /// @return Return a reference to the copied polynomial
    Polynomial& operator=(const Polynomial other);

    /// @brief Sets the polynomial multiplication engine
    void set_multiplication_engine(std::shared_ptr<PolynomialMultiplicationEngine> mul_engine);

    /// @brief Sets the polynomial inversion engine
    void set_inversion_engine(std::shared_ptr<PolynomialInversionEngine> inv_engine);
 
    /// @brief Converts the polynomial to evaluation form. Requires to have a polynomial multiplication engine set.
    /// @param out The output polynomial in evaluation form
    void to_eval(PolynomialEvalForm &out);

    /// @brief Converts the polynomial to evaluation form. Requires to have a polynomial multiplication engine set.
    /// @param out The output polynomial in evaluation form
    void to_eval(PolynomialEvalForm &out, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine);
   
    /// @brief Zero all coefficients of the polynomial
    void zeroize();

    /// @brief Clone this polynomial
    /// @return Return a clone of this polynomial
    std::shared_ptr<Polynomial> clone() const;

    /// @brief Cyclically rotates the coeefficients of this polynomial by rotation
    /// @param out The output polynomial
    /// @param rotation The rotation size
    void cyclic_rotate(Polynomial &out, int64_t rotation) const;

    /// @brief Negacyclicly rotates the coeefficients of this polynomial by rotation
    /// @param out The output polynomial
    /// @param rotation The rotation size
    void negacyclic_rotate(Polynomial &out, int64_t rotation) const;
  
    /// @brief Multiplies this polynomial by scalar and stores the output in out.
    /// @param out The output polynomial
    /// @param scalar The input scalar
    void mul(Polynomial &out, int64_t scalar) const;

    /// @brief Multiplies this polynomial by other and stores the output in out. Requires to have a polynomial multiplication engine set.
    /// @param out The output polynomial
    /// @param other The input polynomial
    void mul(Polynomial &out, const Polynomial &other) const;

    /// @brief Multiplies this polynomial by other and stores the output in out. Uses the given polynomial multiplication engine.
    /// @param out The output polynomial
    /// @param other The input polynomial
    /// @param mul_engine The polynomial multiplication engine
    void mul(Polynomial &out, const Polynomial &other, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine) const;

    /// @brief Computes the multiplicative inverse of this and stores the output in out. Requires to have a polynomial inversion engine set.
    /// @param out The output polynomial
    void inv(Polynomial &out)const;

    /// @brief Computes the multiplicative inverse of this and stores the output in out. Uses the given polynomial inversion engine.
    /// @param out The output polynomial
    /// @param inv_engine The polynomial inversion engine
    void inv(Polynomial &out, std::shared_ptr<PolynomialInversionEngine> inv_engine) const; 

    template <class Archive>
    void save( Archive & ar ) const
    { 
        ar(cereal::base_class<Vector>(this));   
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
        ar(cereal::base_class<Vector>(this));     
        init_from_vec(); 
    }  
};
   
class PolynomialArrayCoefForm : public VectorArray{

    public:
 
    /// @brief The array of polynomials. 
    /// @note This is a pointer to a 1d array of coefficients, that stores a 1d array of polynomials. The array will be initialized as new int64_t[size * degree].
    int64_t* poly_array; 
  
    /// @brief Coefficient Modulus Q
    int64_t coef_modulus;
    /// @brief Degree of the polynomials
    int32_t degree; 
 
    /// @brief The polynomial multiplication engine (optional)
    std::shared_ptr<PolynomialMultiplicationEngine> mul_engine;
    /// @brief Indicates if the polynomial multiplication engine has been set
    bool is_mul_engine_set = false;
      
    /// @brief Default constructor
    PolynomialArrayCoefForm() = default;

    /// @brief Constructs the polynomial array, and allocates memory for the poly_array.
    /// @param degree The degree of the polynomials
    /// @param coef_modulus The coefficient modulus
    /// @param array_size The size of the array
    PolynomialArrayCoefForm(int32_t degree, int64_t coef_modulus, int32_t array_size);
  
    /// @brief Constructs the polynomial array, and allocates memory for the poly_array.
    /// @param degree The degree of the polynomials
    /// @param coef_modulus The coefficient modulus
    /// @param array_size The size of the array
    /// @param mul_engine The polynomial multiplication engine
    PolynomialArrayCoefForm(int32_t degree, int64_t coef_modulus, int32_t array_size, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine);
  
    /// @brief Initializes the polynomial array. Its used in the constructors.
    /// @param degree The degree of the polynomials
    /// @param coef_modulus The coefficient modulus
    /// @param array_size The size of the array
    //void init(int32_t degree, int64_t coef_modulus, int32_t array_size);

    void init_from_vector();
 
    /// @brief Copy constructor
    /// @param other The polynomial array to copy
    PolynomialArrayCoefForm(const PolynomialArrayCoefForm &other);

    /// @brief The copy assignment operator
    /// @param other The polynomial array to copy
    /// @return The reference to the copied polynomial array
    PolynomialArrayCoefForm& operator=(const PolynomialArrayCoefForm other);

    /// @brief Sets the polynomial multiplication engine
    /// @param mul_engine The polynomial multiplication engine
    void set_multiplication_engine(std::shared_ptr<PolynomialMultiplicationEngine> mul_engine);
  
    /// @brief Sets the i'th polyniomal in the array to poly. It copies the coefficients of poly to the coefficients of the i'th polynomial in the array.
    /// @param i The index of the polynomial in the array
    /// @param poly The input polynomial
    void set_polynomial_at(const int32_t i, const Polynomial &poly); 
   
    template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(cereal::base_class<VectorArray>(this));   
        ar(cereal::binary_data(poly_array, sizeof(int64_t) * full_size));  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {   
        ar(cereal::base_class<VectorArray>(this));   
        init_from_vector();
        ar(cereal::binary_data(poly_array, sizeof(int64_t) * full_size));  
        is_init = true;
    } 
     
};

/**
 * @brief Interface that handles evaluation forms of polynomial arrays. These are polynomials after computing a Fast Fourier Transform (in the frequency domain).  
 */
class PolynomialArrayEvalForm{

    public: 

    /// @brief The number of polynomials in the array
    int32_t array_size;
    
    /// @brief The size of the evaluation form. May differ from the degree of the polynomial (e.g. due to padding)
    int32_t size;

    /// @brief  full_size = size * array_size
    int32_t full_size;
    
    /// @brief Default destructor
    virtual ~PolynomialArrayEvalForm() = default; 
  
    /// @brief Adds other to this polynomial array and stores the output in out.
    /// @param out The output polynomial array
    /// @param other The input polynomial array
    virtual void add(PolynomialArrayEvalForm &out, const PolynomialArrayEvalForm &other) = 0;
    
    /// @brief Subtracts other from this polynomial array and stores the output in out.
    /// @param out The output polynomial array
    /// @param other The input polynomial array
    virtual void sub(PolynomialArrayEvalForm &out, const PolynomialArrayEvalForm &other) = 0;
    
    /// @brief Scalar multiplication of polynomials in this array. 
    /// @param out The output polynomial array
    /// @param scalar The input polynomial array
    virtual void mul(PolynomialArrayEvalForm &out, int64_t scalar) = 0;
  
    /// @brief Negates the polynomials in this array. 
    /// @param out The output polynomial array
    virtual void neg(PolynomialArrayEvalForm &out) = 0; 
   
    template <class Archive>
    void save( Archive & ar ) const
    { 
        ar(size, array_size);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
        ar(size, array_size);   
        full_size = size * array_size;
    }    

};

/**
 * @brief Implementation of PolynomialArrayEvalForm, were entries are PolynomialEvalFormLongInteger
 */
class PolynomialArrayEvalFormLong: public PolynomialArrayEvalForm{

    public:
 
    int64_t* eval_long; 

    bool is_init = false; 

    int64_t coef_modulus;

    ~PolynomialArrayEvalFormLong();

    PolynomialArrayEvalFormLong() = default;
 
    PolynomialArrayEvalFormLong(int32_t array_size, int64_t degree, int64_t coef_modulus);
  
    void add(PolynomialArrayEvalForm &out, const PolynomialArrayEvalForm &other);
    
    void sub(PolynomialArrayEvalForm &out, const PolynomialArrayEvalForm &other);
    
    void mul(PolynomialArrayEvalForm &out, int64_t scalar); 
    
    void neg(PolynomialArrayEvalForm &out);

    void mod_reduce(const int64_t modulus); 

    template <class Archive>
    void save( Archive & ar ) const
    { 
        ar(cereal::base_class<PolynomialArrayEvalForm>(this));    
        ar(coef_modulus); 
        ar(cereal::binary_data(eval_long, sizeof(int64_t) * full_size));  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
        ar(cereal::base_class<PolynomialArrayEvalForm>(this));  
        ar(coef_modulus); 
        full_size = size * array_size;
        this->eval_long = new int64_t[full_size];
        ar(cereal::binary_data(eval_long, sizeof(int64_t) * full_size));  
        is_init = true;
    }    

};


/**
 * @brief Implementation of PolynomialArrayEvalForm, were entries are PolynomialEvalFormFFTWComplex
 */
class PolynomialArrayEvalFormFFTWComplex: public PolynomialArrayEvalForm{

    public:
 
    //fftw_complex* eval_fftw; 
    Complex* eval_fftw; 

    bool is_init = false; 

    double scale = 1.0;
 
    ~PolynomialArrayEvalFormFFTWComplex();

    PolynomialArrayEvalFormFFTWComplex() = default;

    PolynomialArrayEvalFormFFTWComplex(int32_t size, int32_t array_size);
  
    void add(PolynomialArrayEvalForm &out, const PolynomialArrayEvalForm &other);
    
    void sub(PolynomialArrayEvalForm &out, const PolynomialArrayEvalForm &other);
    
    void mul(PolynomialArrayEvalForm &out, int64_t scalar); 
    
    void neg(PolynomialArrayEvalForm &out);
  
    template <class Archive>
    void save( Archive & ar ) const
    { 
        ar(cereal::base_class<PolynomialArrayEvalForm>(this));     
        ar(cereal::binary_data(eval_fftw, sizeof(Complex) * full_size));  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
        ar(cereal::base_class<PolynomialArrayEvalForm>(this));    
        full_size = size * array_size;
        eval_fftw = new Complex[full_size];
        ar(cereal::binary_data(eval_fftw, sizeof(Complex) * full_size));  
        is_init = true;
    }    

};

/**
 * @brief Implementation of PolynomialArrayEvalForm, were entries are PolynomialEvalFormFFTWComplex
 */
class PolynomialArrayEvalFormFFTWLongComplex: public PolynomialArrayEvalForm{

    public:
  
    //fftwl_complex* eval_fftwl; 
    LongComplex* eval_fftwl; 

    bool is_init = false; 

    long double scale = 1.0;

    ~PolynomialArrayEvalFormFFTWLongComplex();

    PolynomialArrayEvalFormFFTWLongComplex() = default;
 
    PolynomialArrayEvalFormFFTWLongComplex(int32_t size, int32_t array_size);
   
    void add(PolynomialArrayEvalForm &out, const PolynomialArrayEvalForm &other);
    
    void sub(PolynomialArrayEvalForm &out, const PolynomialArrayEvalForm &other);
    
    void mul(PolynomialArrayEvalForm &out, const int64_t scalar);
  
    void neg(PolynomialArrayEvalForm &out);
  
    template <class Archive>
    void save( Archive & ar ) const
    {  
        ar(cereal::base_class<PolynomialArrayEvalForm>(this));    
        ar(cereal::binary_data(eval_fftwl, sizeof(LongComplex) * full_size));  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
        ar(cereal::base_class<PolynomialArrayEvalForm>(this));    
        full_size = size * array_size;
        eval_fftwl = new LongComplex[full_size];
        ar(cereal::binary_data(eval_fftwl, sizeof(LongComplex) * full_size));  
        is_init = true;
    }    
};


}/// End of namespace fhe_deck

/// NOTE: The following lines are used to register the classes for serialization using the Cereal library.   
CEREAL_REGISTER_TYPE(fhe_deck::PolynomialArrayEvalFormLong)
CEREAL_REGISTER_TYPE(fhe_deck::PolynomialArrayEvalFormFFTWComplex)
CEREAL_REGISTER_TYPE(fhe_deck::PolynomialArrayEvalFormFFTWLongComplex)
 
  
#endif