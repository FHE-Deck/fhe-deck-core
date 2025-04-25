#ifndef MATH_H
#define MATH_H
 

#include "math/polynomial_inversion_engine_builder.h"
#include "math/euclidean_inversion_engine.h"
#include "math/polynomial_multiplication_engine_builder.h"
#include "math/polynomial.h"
#include "math/vector.h" 
#include "math/naive_multiplication_engine.h" 
 
#if defined(USE_NTL)
#include "math/ntl_inversion_engine.h"
#endif 


#if defined(USE_IntelHexl)
#include "math/intel_hexl_engine.h"
#endif 

#if defined(USE_FFTW)
#include "math/fftw_engine.h"
#endif 

#if defined(USE_FFTWL)
#include "math/fftw_long_engine.h"
#endif 


#endif 