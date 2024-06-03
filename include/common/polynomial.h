#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <memory> 
#include "enums.h"
#include "utils.h"  


#include <NTL/ZZX.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_p.h>

#include "fft_plan.h"
#include "hexl/hexl.hpp"  
#include <cereal/archives/binary.hpp>

namespace fhe_deck{
      
// Forward declaration if the Polynomial class and PolynomialEvalForm class that used by all other classes.
// Both are defined in this file.
class Polynomial; 
class PolynomialEvalForm;

// Forward declarations of PolynomialArrayCoefForm and PolynomialArrayEvalForm classes, as these classes refer to each other.
class PolynomialArrayCoefForm;
class PolynomialArrayEvalForm;


class PolynomialMultiplicationEngine{

    public: 

    PolynomialArithmetic type;

    virtual PolynomialEvalForm* init_polynomial_eval_form() = 0;

    virtual PolynomialArrayEvalForm* init_polynomial_array_eval_form(int array_size) = 0;
  
    virtual void to_eval(PolynomialEvalForm *out, Polynomial *in) = 0; 

    virtual void to_eval(PolynomialArrayEvalForm *out, PolynomialArrayCoefForm *in) = 0;
  
    virtual void to_coef(Polynomial *out, PolynomialEvalForm *in) = 0; 

    virtual void to_coef(PolynomialArrayCoefForm *out, PolynomialArrayEvalForm *in) = 0;

    virtual void mul(PolynomialEvalForm *out, PolynomialEvalForm *in_1, PolynomialEvalForm *in_2) = 0;
 
    virtual void mul(Polynomial *out, Polynomial *in_1,  Polynomial *in_2); 
   
    virtual void multisum(Polynomial *out, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2) = 0;

    virtual void multisum(Polynomial *out, PolynomialArrayEvalForm *in_1, PolynomialArrayEvalForm *in_2) = 0;
 
    virtual void multisum(Polynomial *out_multisum, PolynomialArrayEvalForm *out_in_1_eval, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2) = 0;

    /// TODO: I need a Multisum that Has two outputs - Polynomial *out, and Polynomial PolynomialArrayEvalForm of the first PolynomialArrayCoefForm
    /// TODO: Then I need another multisum that takes a Gadget.
};




class PolynomialMultiplicationEngineBuilder{

    public:
    long coef_modulus;
    long degree;
    RingType ring;
    PolynomialArithmetic arithmetic;
    ModulusType mod_type;

    bool is_init = false;

    PolynomialMultiplicationEngineBuilder() = default;

    void set_coef_modulus(long coef_modulus);

    void set_degree(long degree);

    void set_ring_type(RingType ring);

    void set_polynomial_arithmetic(PolynomialArithmetic arithmetic);

    void set_modulus_type(ModulusType mod_type);

    std::shared_ptr<PolynomialMultiplicationEngine> build(); 
};



class IntelHexlNTTEngine : public PolynomialMultiplicationEngine{

    public:

    intel::hexl::NTT ntt; 
    int degree;
    long coef_modulus;

    IntelHexlNTTEngine(int degree, long coef_modulus);

    PolynomialEvalForm* init_polynomial_eval_form(); 

    PolynomialArrayEvalForm* init_polynomial_array_eval_form(int array_size);
 
    void to_eval(PolynomialEvalForm *out, Polynomial *in); 

    void to_eval(PolynomialArrayEvalForm *out, PolynomialArrayCoefForm *in);

    void to_coef(Polynomial *out, PolynomialEvalForm *in);

    void to_coef(PolynomialArrayCoefForm *out, PolynomialArrayEvalForm *in);
 
    void mul(PolynomialEvalForm *out, PolynomialEvalForm *in_1, PolynomialEvalForm *in_2);
    
    void multisum(Polynomial *out, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2);

    void multisum(Polynomial *out, PolynomialArrayEvalForm *in_1, PolynomialArrayEvalForm *in_2);

    void multisum(Polynomial *out_multisum, PolynomialArrayEvalForm *out_in_1_eval, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2);
};


class FFTWNegacyclicEngine : public PolynomialMultiplicationEngine{

    public:
 
    FFTPlan engine; 

    int degree;
    long coef_modulus;

    FFTWNegacyclicEngine(int degree, long coef_modulus); 
    
    PolynomialEvalForm* init_polynomial_eval_form(); 

    PolynomialArrayEvalForm* init_polynomial_array_eval_form(int array_size);

    void to_eval(PolynomialEvalForm *out, Polynomial *in);
    
    void to_eval(PolynomialArrayEvalForm *out, PolynomialArrayCoefForm *in);

    void to_coef(Polynomial *out, PolynomialEvalForm *in);
 
    void to_coef(PolynomialArrayCoefForm *out, PolynomialArrayEvalForm *in);
  
    void mul(PolynomialEvalForm *out, PolynomialEvalForm *in_1, PolynomialEvalForm *in_2);

    void multisum(Polynomial *out, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2);

    void multisum(Polynomial *out, PolynomialArrayEvalForm *in_1, PolynomialArrayEvalForm *in_2);
 
    void multisum(Polynomial *out_multisum, PolynomialArrayEvalForm *out_in_1_eval, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2);
};


class FFTWLongNegacyclicEngine : public PolynomialMultiplicationEngine{

    public:
 
    FFTPlan engine; 

    int degree;
    long coef_modulus;

    FFTWLongNegacyclicEngine(int degree, long coef_modulus); 
  
    PolynomialEvalForm* init_polynomial_eval_form();

    PolynomialArrayEvalForm* init_polynomial_array_eval_form(int array_size);
 
    void to_eval(PolynomialEvalForm *out, Polynomial *in);
 
    void to_eval(PolynomialArrayEvalForm *out, PolynomialArrayCoefForm *in);

    void to_coef(Polynomial *out, PolynomialEvalForm *in);
  
    void to_coef(PolynomialArrayCoefForm *out, PolynomialArrayEvalForm *in);
  
    void mul(PolynomialEvalForm *out, PolynomialEvalForm *in_1, PolynomialEvalForm *in_2);
 
    void multisum(Polynomial *out, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2);

    void multisum(Polynomial *out, PolynomialArrayEvalForm *in_1, PolynomialArrayEvalForm *in_2);

    void multisum(Polynomial *out_multisum, PolynomialArrayEvalForm *out_in_1_eval, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2);

};
 
 
class PolynomialEvalForm{

    public:
 
    int size;
    long coef_modulus;
 
    virtual ~PolynomialEvalForm() = default;

    virtual void zeroize() = 0;

    /// TODO: The thing with this modulus reduction is weird and not necessarily true. In NTT there is modulus reduction.

    /// NOTE: There is no modulus reduction here
    virtual void add(PolynomialEvalForm *out, PolynomialEvalForm *other) = 0;
    /// NOTE: There is no modulus reduction here
    virtual void sub(PolynomialEvalForm *out, PolynomialEvalForm *other) = 0;
    /// NOTE: There is no modulus reduction here
    virtual void mul(PolynomialEvalForm *out, long scalar) = 0; 
    /// NOTE: There is no modulus reduction here
    virtual void neg(PolynomialEvalForm *out) = 0; 

    /// TODO: Annother issue with this mod_reduce is its inconsistent, with the style as it should have on output.
    virtual void mod_reduce(long Q) = 0;
};

class PolynomialEvalFormLongInteger : public PolynomialEvalForm{

    public:
  
    long* eval_long; 
    bool is_init = false;

    ~PolynomialEvalFormLongInteger();

    PolynomialEvalFormLongInteger(long* eval_long, int size, long coef_modulus);

    void zeroize();

    void add(PolynomialEvalForm *out, PolynomialEvalForm *other);

    void sub(PolynomialEvalForm *out, PolynomialEvalForm *other);

    void mul(PolynomialEvalForm *out, long scalar);

    void neg(PolynomialEvalForm *out);

    void mod_reduce(long Q); 
};

class PolynomialEvalFormFFTWComplex : public PolynomialEvalForm{

    public:
 
    fftw_complex* eval_fftw;
    bool is_init = false;

    ~PolynomialEvalFormFFTWComplex();	

    PolynomialEvalFormFFTWComplex(fftw_complex* eval_fftw, int size, long coef_modulus);

    void zeroize();

    void add(PolynomialEvalForm *out, PolynomialEvalForm *other);

    void sub(PolynomialEvalForm *out, PolynomialEvalForm *other);

    void mul(PolynomialEvalForm *out, long scalar);

    void neg(PolynomialEvalForm *out);

    void mod_reduce(long Q); 
};

class PolynomialEvalFormFFTWLongComplex : public PolynomialEvalForm{

    public:
 
    fftwl_complex* eval_fftwl;
    bool is_init = false;

    ~PolynomialEvalFormFFTWLongComplex();	

    PolynomialEvalFormFFTWLongComplex(fftwl_complex* eval_fftwl, int size, long coef_modulus);

    void zeroize();

    void add(PolynomialEvalForm *out, PolynomialEvalForm *other);

    void sub(PolynomialEvalForm *out, PolynomialEvalForm *other);

    void mul(PolynomialEvalForm *out, long scalar);

    void neg(PolynomialEvalForm *out);

    void mod_reduce(long Q); 
};

class PolynomialInversionEngine{

    public: 
    
    PolynomialInversionEngineType type;

    virtual void inv(Polynomial *out, Polynomial &in) = 0;
 
};
 
class Polynomial{

    public:

    long* coefs;
    bool is_init = false;

    // Coefficient Modulus Q
    long coef_modulus;
    int coef_modulus_bit_size;
    // Degree
    int degree;

    std::shared_ptr<PolynomialMultiplicationEngine> mul_engine;
    bool is_mul_engine_set = false;
   
    std::shared_ptr<PolynomialInversionEngine> inv_engine;
    bool is_inv_engine_set = false;

    ~Polynomial();
    
    Polynomial() = default;

    Polynomial(int degree, long coef_modulus);
  
    Polynomial(int degree, long coef_modulus, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine);

    Polynomial(int degree, long coef_modulus, std::shared_ptr<PolynomialInversionEngine> inv_engine);

    Polynomial(int degree, long coef_modulus, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine, std::shared_ptr<PolynomialInversionEngine> inv_engine);

    void init(int degree, long coef_modulus);
  
    Polynomial(const Polynomial &other);

    Polynomial& operator=(const Polynomial other);

    void set_multiplication_engine(std::shared_ptr<PolynomialMultiplicationEngine> mul_engine);

    void set_inversion_engine(std::shared_ptr<PolynomialInversionEngine> inv_engine);
 
    void to_eval(PolynomialEvalForm *out);
   
    void zeroize();

    Polynomial clone();

    void cyclic_rotate(Polynomial *out, long rotation);

    void negacyclic_rotate(Polynomial *out, long rotation);

    void add(Polynomial *out, Polynomial *other);

    void add_coef(Polynomial *out, Polynomial *other);

    void sub(Polynomial *out, Polynomial *other);

    void sub_coef(Polynomial *out, Polynomial *other);

    void neg(Polynomial *out);

    void neg_coef(Polynomial *out);

    void mul(Polynomial *out, long scalar);

    void mul(Polynomial *out, Polynomial *other);

    void mul(Polynomial *out, Polynomial *other, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine);

    void inv(Polynomial *out);

    void inv(Polynomial *out, std::shared_ptr<PolynomialInversionEngine> inv_engine); 

    template <class Archive>
    void save( Archive & ar ) const
    { 
        ar(coef_modulus, degree);  
        ar(cereal::binary_data(coefs, sizeof(long) * degree));  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
        ar(coef_modulus, degree);   
        this->coef_modulus_bit_size = Utils::power_times(coef_modulus, 2);
        ar(cereal::binary_data(coefs, sizeof(long) * degree));  
    } 
      
};
   
class PolynomialArrayCoefForm{

    public:

    // This is a pointer to a 1d array of coefficients, that stores a 1d array of polynomials
    // The array will be initialized as new long[size * degree]
    long* poly_array;
    bool is_init = false;
  
    // Coefficient Modulus Q
    long coef_modulus;
    // Degree
    int degree;
    // Size of the array
    int array_size;

    // full_size = degree * array_size. Initialized in the constructors. 
    int full_size;
 
    std::shared_ptr<PolynomialMultiplicationEngine> mul_engine;
    bool is_mul_engine_set = false;
  
    ~PolynomialArrayCoefForm();

    PolynomialArrayCoefForm() = default;

    PolynomialArrayCoefForm(int degree, long coef_modulus, int array_size);
  
    PolynomialArrayCoefForm(int degree, long coef_modulus, int array_size, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine);
  
    void init(int degree, long coef_modulus, int array_size);
 
    PolynomialArrayCoefForm(const PolynomialArrayCoefForm &other);

    PolynomialArrayCoefForm& operator=(const PolynomialArrayCoefForm other);

    void set_multiplication_engine(std::shared_ptr<PolynomialMultiplicationEngine> mul_engine);
  
    void set_polynomial_at(int i, Polynomial *poly); 
 
    void add(PolynomialArrayCoefForm *out, PolynomialArrayCoefForm *other);
  
    void sub(PolynomialArrayCoefForm *out, PolynomialArrayCoefForm *other);
  
    void neg(PolynomialArrayCoefForm *out);
  
    void mul(PolynomialArrayCoefForm *out, long scalar);

    template <class Archive>
    void save( Archive & ar ) const
    { 
        ar(coef_modulus, degree, array_size);   
        ar(cereal::binary_data(poly_array, sizeof(long) * full_size));  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
        ar(coef_modulus, degree, array_size);   
        full_size = degree * array_size;
        ar(cereal::binary_data(poly_array, sizeof(long) * full_size));  
        is_init = true;
    } 
     
};


class PolynomialArrayEvalForm{

    public: 

    // Refers to the number of polynomials in the array
    int array_size;
    // Referse to the size of the evaluation form.
    // May differ from the degree of the polynomial (e.g. due to padding)
    int size;

    // full_size = size * array_size
    int full_size;

    long coef_modulus;
    
    virtual ~PolynomialArrayEvalForm() = default; 
  
    // NOTE: There is no modulus reduction here
    virtual void add(PolynomialArrayEvalForm *out, PolynomialArrayEvalForm *other) = 0;
    // NOTE: There is no modulus reduction here
    virtual void sub(PolynomialArrayEvalForm *out, PolynomialArrayEvalForm *other) = 0;
    // NOTE: There is no modulus reduction here
    virtual void mul(PolynomialArrayEvalForm *out, long scalar) = 0;
 
    // NOTE: There is no modulus reduction here
    virtual void neg(PolynomialArrayEvalForm *out) = 0;

    virtual void mod_reduce(long modulus) = 0;   
};


class PolynomialArrayEvalFormLong: public PolynomialArrayEvalForm{

    public:
 
    long* eval_long; 

    bool is_init = false; 

    ~PolynomialArrayEvalFormLong();
 
    PolynomialArrayEvalFormLong(int array_size, long degree, long coef_modulus);
  
    // NOTE: There is no modulus reduction here
    void add(PolynomialArrayEvalForm *out, PolynomialArrayEvalForm *other);
    // NOTE: There is no modulus reduction here
    void sub(PolynomialArrayEvalForm *out, PolynomialArrayEvalForm *other);
    // NOTE: There is no modulus reduction here
    void mul(PolynomialArrayEvalForm *out, long scalar); 
    // NOTE: There is no modulus reduction here
    void neg(PolynomialArrayEvalForm *out);

    void mod_reduce(long modulus); 

    template <class Archive>
    void save( Archive & ar ) const
    { 
        ar(coef_modulus, size, array_size);   
        ar(cereal::binary_data(eval_long, sizeof(long) * full_size));  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
        ar(coef_modulus, size, array_size);   
        full_size = size * array_size;
        ar(cereal::binary_data(eval_long, sizeof(long) * full_size));  
        is_init = true;
    }    

};

class PolynomialArrayEvalFormFFTWComplex: public PolynomialArrayEvalForm{

    public:
 
    fftw_complex* eval_fftw; 

    bool is_init = false; 
 
    ~PolynomialArrayEvalFormFFTWComplex();

    PolynomialArrayEvalFormFFTWComplex(FFTWNegacyclicEngine* mul_engine, int array_size);
  
    // NOTE: There is no modulus reduction here
    void add(PolynomialArrayEvalForm *out, PolynomialArrayEvalForm *other);
    // NOTE: There is no modulus reduction here
    void sub(PolynomialArrayEvalForm *out, PolynomialArrayEvalForm *other);
    // NOTE: There is no modulus reduction here
    void mul(PolynomialArrayEvalForm *out, long scalar); 
    // NOTE: There is no modulus reduction here
    void neg(PolynomialArrayEvalForm *out);

    void mod_reduce(long modulus); 

    template <class Archive>
    void save( Archive & ar ) const
    { 
        ar(coef_modulus, size, array_size);   
        ar(cereal::binary_data(eval_fftw, sizeof(fftw_complex) * full_size));  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
        ar(coef_modulus, size, array_size);   
        full_size = size * array_size;
        ar(cereal::binary_data(eval_fftw, sizeof(fftw_complex) * full_size));  
        is_init = true;
    }    

};

class PolynomialArrayEvalFormFFTWLongComplex: public PolynomialArrayEvalForm{

    public:
  
    fftwl_complex* eval_fftwl; 

    bool is_init = false; 

    ~PolynomialArrayEvalFormFFTWLongComplex();
 
    PolynomialArrayEvalFormFFTWLongComplex(FFTWLongNegacyclicEngine* mul_engine, int array_size);
  
    // NOTE: There is no modulus reduction here
    void add(PolynomialArrayEvalForm *out, PolynomialArrayEvalForm *other);
    // NOTE: There is no modulus reduction here
    void sub(PolynomialArrayEvalForm *out, PolynomialArrayEvalForm *other);
    // NOTE: There is no modulus reduction here
    void mul(PolynomialArrayEvalForm *out, long scalar);
 
    // NOTE: There is no modulus reduction here
    void neg(PolynomialArrayEvalForm *out);

    void mod_reduce(long modulus); 

    template <class Archive>
    void save( Archive & ar ) const
    { 
        ar(coef_modulus, size, array_size);   
        ar(cereal::binary_data(eval_fftwl, sizeof(fftwl_complex) * full_size));  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
        ar(coef_modulus, size, array_size);   
        full_size = size * array_size;
        ar(cereal::binary_data(eval_fftwl, sizeof(fftwl_complex) * full_size));  
        is_init = true;
    }    
};


}/// End of namespace fhe_deck


#endif