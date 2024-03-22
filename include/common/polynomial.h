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

    virtual void to_eval(Polynomial *in) = 0;
 
    virtual void to_coef(Polynomial *in) = 0;

    virtual void to_eval(PolynomialEvalForm *out, Polynomial *in) = 0;

    virtual void to_eval(Polynomial *out, Polynomial *in) = 0;

    virtual void to_eval(PolynomialArrayEvalForm *out, PolynomialArrayCoefForm *in) = 0;
  
    virtual void to_coef(Polynomial *out, PolynomialEvalForm *in) = 0;

    virtual void to_coef(Polynomial *out, Polynomial *in) = 0;

    virtual void to_coef(PolynomialArrayCoefForm *out, PolynomialArrayEvalForm *in) = 0;

    virtual void mul(PolynomialEvalForm *out, PolynomialEvalForm *in_1, PolynomialEvalForm *in_2) = 0;

    virtual void mul(Polynomial *out, Polynomial *in_1,  Polynomial *in_2) = 0;

    virtual Polynomial mul(Polynomial *in_1, Polynomial *in_2) = 0;
   
    virtual void multisum(Polynomial *out, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2, bool coef_form = true) = 0;
 
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


    void to_eval(Polynomial *in);

    void to_coef(Polynomial *in);
 
    void to_eval(PolynomialEvalForm *out, Polynomial *in);

    void to_eval(Polynomial *out, Polynomial *in);

    void to_eval(PolynomialArrayEvalForm *out, PolynomialArrayCoefForm *in);

    void to_coef(Polynomial *out, PolynomialEvalForm *in);
 
    void to_coef(Polynomial *out, Polynomial *in);

    void to_coef(PolynomialArrayCoefForm *out, PolynomialArrayEvalForm *in);
 
    void mul(PolynomialEvalForm *out, PolynomialEvalForm *in_1, PolynomialEvalForm *in_2);

    void mul(Polynomial *out, Polynomial *in_1, Polynomial *in_2);

    Polynomial mul(Polynomial *in_1, Polynomial *in_2);

    void multisum(Polynomial *out, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2, bool coef_form = true);
 

};


class FFTWNegacyclicEngine : public PolynomialMultiplicationEngine{

    public:
 
    FFTPlan engine; 

    int degree;
    long coef_modulus;

    FFTWNegacyclicEngine(int degree, long coef_modulus); 
   
    void to_eval(Polynomial *in);

    void to_coef(Polynomial *in);

    void to_eval(PolynomialEvalForm *out, Polynomial *in);

    void to_eval(Polynomial *out, Polynomial *in);

    void to_eval(PolynomialArrayEvalForm *out, PolynomialArrayCoefForm *in);

    void to_coef(Polynomial *out, PolynomialEvalForm *in);
 
    void to_coef(Polynomial *out, Polynomial *in);

    void to_coef(PolynomialArrayCoefForm *out, PolynomialArrayEvalForm *in);
  
    void mul(PolynomialEvalForm *out, PolynomialEvalForm *in_1, PolynomialEvalForm *in_2);

    void mul(Polynomial *out, Polynomial *in_1, Polynomial *in_2);

    Polynomial mul(Polynomial *in_1, Polynomial *in_2); 

    void multisum(Polynomial *out, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2, bool coef_form = true);

};


class FFTWLongNegacyclicEngine : public PolynomialMultiplicationEngine{

    public:
 
    FFTPlan engine; 

    int degree;
    long coef_modulus;

    FFTWLongNegacyclicEngine(int degree, long coef_modulus); 
  
    void to_eval(Polynomial *in);

    void to_coef(Polynomial *in);

    void to_eval(PolynomialEvalForm *out, Polynomial *in);

    void to_eval(Polynomial *out, Polynomial *in);

    void to_eval(PolynomialArrayEvalForm *out, PolynomialArrayCoefForm *in);

    void to_coef(Polynomial *out, PolynomialEvalForm *in);
 
    void to_coef(Polynomial *out, Polynomial *in);

    void to_coef(PolynomialArrayCoefForm *out, PolynomialArrayEvalForm *in);
  
    void mul(PolynomialEvalForm *out, PolynomialEvalForm *in_1, PolynomialEvalForm *in_2);

    void mul(Polynomial *out, Polynomial *in_1, Polynomial *in_2);

    Polynomial mul(Polynomial *in_1, Polynomial *in_2);

    void multisum(Polynomial *out, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2, bool coef_form = true);

};



class NTLMultiplicationEngine : public PolynomialMultiplicationEngine{

    public:
 
    int degree;
    long coef_modulus;

    NTL::ZZ_pX ring;

    NTLMultiplicationEngine(int degree, long coef_modulus, RingType ring); 
  
    void to_eval(Polynomial *in);

    void to_coef(Polynomial *in);

    void to_eval(PolynomialEvalForm *out, Polynomial *in);

    void to_eval(Polynomial *out, Polynomial *in);

    void to_eval(PolynomialArrayEvalForm *out, PolynomialArrayCoefForm *in);
 
    void to_coef(Polynomial *out, PolynomialEvalForm *in);

    void to_coef(Polynomial *out, Polynomial *in);

    void to_coef(PolynomialArrayCoefForm *out, PolynomialArrayEvalForm *in);
  
    void mul(PolynomialEvalForm *out, PolynomialEvalForm *in_1, PolynomialEvalForm *in_2);

    void mul(Polynomial *out, Polynomial *in_1, Polynomial *in_2);

    Polynomial mul(Polynomial *in_1, Polynomial *in_2);

    void multisum(Polynomial *out, PolynomialArrayCoefForm *in_1, PolynomialArrayEvalForm *in_2, bool coef_form = true);

    private:
    NTL::ZZ_pX get_ring_poly(RingType ring);

    void set_polynomial_from_array(NTL::ZZ_pX &poly, long *f, int sizeof_f, long Q);

    void set_array_from_polynomial(long *array, int sizeof_array, NTL::ZZ_pX poly);

};




// Wrapper for the different types of arithmetics we could handle
class PolynomialEvalForm{

    public:
 
    int size;
    long coef_modulus;

    std::shared_ptr<PolynomialMultiplicationEngine> mul_engine;
    bool is_mul_engine_set = false;

    long* eval_long;
    bool is_eval_long = false;

    fftw_complex* eval_fftw;
    bool is_eval_fftw = false;

    fftwl_complex* eval_fftwl;
    bool is_eval_fftwl = false;

    bool is_init = false;

    ~PolynomialEvalForm();
 
    PolynomialEvalForm() = default;
  
    PolynomialEvalForm(long* eval_long, int size, long coef_modulus);

    PolynomialEvalForm(fftw_complex* eval_fftw, int size, long coef_modulus);

    PolynomialEvalForm(fftwl_complex* eval_fftwl, int size, long coef_modulus);

    PolynomialEvalForm(const PolynomialEvalForm &other);

    PolynomialEvalForm& operator=(const PolynomialEvalForm other);

    void zeroize();

    // NOTE: There is no modulus reduction here
    void add(PolynomialEvalForm *out, PolynomialEvalForm *other);
    // NOTE: There is no modulus reduction here
    void sub(PolynomialEvalForm *out, PolynomialEvalForm *other);
    // NOTE: There is no modulus reduction here
    void mul(PolynomialEvalForm *out, long scalar);

    // NOTE: There is no modulus reduction here
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
    // Degree
    int degree;

    std::shared_ptr<PolynomialMultiplicationEngine> mul_engine;
    bool is_mul_engine_set = false;
 
    PolynomialEvalForm poly_eval_form;
    bool is_eval_form = false;

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

    void to_eval();

    void to_eval(PolynomialEvalForm *out);

    void to_eval(Polynomial *out);

    void to_coef();

    void to_coef(Polynomial *out);

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
     
    static void to_eval(Polynomial *out, Polynomial *in, int size, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine);

    static void multisum(Polynomial *out, Polynomial *in_1, Polynomial *in_2, int size, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine);

    static void multisum(Polynomial *out, Polynomial *in_1, Polynomial *in_2, int size, int jump, std::shared_ptr<PolynomialMultiplicationEngine> mul_engine);
    
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

    // full_size = degree * array_size. Initialized in the constructors
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
  
    long* eval_long;
    bool is_eval_long = false;

    fftw_complex* eval_fftw;
    bool is_eval_fftw = false;

    fftwl_complex* eval_fftwl;
    bool is_eval_fftwl = false;
  

    // TODO: Most Likely we don't need the mul_engine anymore.
    std::shared_ptr<PolynomialMultiplicationEngine> mul_engine;
    bool is_init = false; 
     
    ~PolynomialArrayEvalForm();
 
    PolynomialArrayEvalForm() = default;

    PolynomialArrayEvalForm(std::shared_ptr<PolynomialMultiplicationEngine> mul_engine, int array_size);
 

    PolynomialArrayEvalForm(const PolynomialArrayEvalForm &other);

    PolynomialArrayEvalForm& operator=(const PolynomialArrayEvalForm other);
  

    // NOTE: There is no modulus reduction here
    void add(PolynomialArrayEvalForm &out, PolynomialArrayEvalForm &other);
    // NOTE: There is no modulus reduction here
    void sub(PolynomialArrayEvalForm &out, PolynomialArrayEvalForm &other);
    // NOTE: There is no modulus reduction here
    void mul(PolynomialArrayEvalForm &out, long scalar);
 
    // NOTE: There is no modulus reduction here
    void neg(PolynomialArrayEvalForm &out);

    void mod_reduce(long modulus);  
     
};



}


#endif