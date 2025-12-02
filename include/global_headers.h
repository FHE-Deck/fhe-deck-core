#ifndef GLOBAL_HEADERS_H
#define GLOBAL_HEADERS_H
 
/**
 * Standard library headers
 */

#include <random>
#include <iostream>  
#include <memory>
#include <stdexcept> 
#include <functional>
#include <cinttypes>
#include <random>
#include <fstream> 
#include <string> 
#include <math.h>    
#include <complex>
#include <span>

/**
 * Third party headers 
 */
 

/// NOTE: Cereal is optional.
#if defined(USE_CEREAL)
#include "cereal/archives/binary.hpp"
#include "cereal/types/memory.hpp"
#include "cereal/types/vector.hpp" 
#include "cereal/types/base_class.hpp" 
#include "cereal/types/polymorphic.hpp"
#endif


#endif