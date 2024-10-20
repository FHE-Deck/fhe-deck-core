cmake_minimum_required(VERSION 3.13)
 
project(fhe_deck)

set(third_party "${PROJECT_SOURCE_DIR}/build/third_party/")

include(ExternalProject)  
ExternalProject_Add(
    intel_hexl
    GIT_REPOSITORY https://github.com/intel/hexl.git 
	GIT_TAG development
    PREFIX ${PROJECT_SOURCE_DIR}/external/intel_hexl
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${third_party}/intel_hexl 
)  
 
include_directories(${third_party}/intel_hexl/include)
link_directories(${third_party}/intel_hexl/lib) 

include(ExternalProject) 
set(FFTW fftw_lib)
ExternalProject_Add(
    fftw_lib
    URL https://www.fftw.org/fftw-3.3.10.tar.gz 
	URL_HASH MD5=8ccbf6a5ea78a16dbc3e1306e234cc5c
    PREFIX ${PROJECT_SOURCE_DIR}/external/${FFTW}
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${third_party}/fftw3 
)

include_directories(${third_party}/fftw3/include)
link_directories(${third_party}/fftw3/lib) 

include(ExternalProject) 
set(FFTWL fftwl_lib)
ExternalProject_Add(
    fftwl_lib
    URL https://www.fftw.org/fftw-3.3.10.tar.gz 
	URL_HASH MD5=8ccbf6a5ea78a16dbc3e1306e234cc5c
    PREFIX ${PROJECT_SOURCE_DIR}/external/${FFTWL}
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${third_party}/fftwl3 -DENABLE_LONG_DOUBLE=ON 
)

include_directories(${third_party}/fftwl3/include)
link_directories(${third_party}/fftwl3/lib) 


   
include(ExternalProject)  
ExternalProject_Add(
    cereal_lib
    GIT_REPOSITORY https://github.com/USCiLab/cereal.git
	GIT_TAG v1.3.2
    PREFIX ${PROJECT_SOURCE_DIR}/external/cereal_lib
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${third_party}/cereal  -DSKIP_PERFORMANCE_COMPARISON=ON -DBUILD_TESTS=OFF
)

include_directories(${third_party}/cereal/include)
link_directories(${third_party}/cereal/lib) 

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -funroll-loops")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -funroll-loops -fsanitize=address -static-libasan -g")

# source files 
file(GLOB INC_MATH include/math/*.cpp)
file(GLOB SRC_MATH src/math/*.cpp)
include_directories(include/math)

file(GLOB INC_CIPHERTEXTS include/ciphertexts/*.cpp)
file(GLOB SRC_CIPHERTEXTS src/ciphertexts/*.cpp)
include_directories(include/ciphertexts)

file(GLOB INC_KEYSWITCH include/keyswitch/*.cpp)
file(GLOB SRC_KEYSWITCH src/keyswitch/*.cpp)
include_directories(include/keyswitch)

file(GLOB INC_COMMON include/common/*.cpp)
file(GLOB SRC_COMMON src/common/*.cpp)
include_directories(include/common)

file(GLOB INC_INTERFACE include/interface/*.cpp)
file(GLOB SRC_INTERFACE src/interface/*.cpp)
include_directories(include/interface)

file(GLOB INC_FHE include/fhe/*.cpp)
file(GLOB SRC_FHE src/fhe/*.cpp)
include_directories(include/fhe)

add_library(fhe_deck STATIC
	${INC_CIPHERTEXTS} ${SRC_CIPHERTEXTS}
	${INC_MATH} ${SRC_MATH}
	${INC_KEYSWITCH} ${SRC_KEYSWITCH}
	${INC_INTERFACE} ${SRC_INTERFACE}
	${INC_COMMON} ${SRC_COMMON} 
	${INC_FHE} ${SRC_FHE}
)
   
target_link_libraries(fhe_deck PRIVATE ntl ${third_party}/fftw3/lib/libfftw3.so ${third_party}/fftwl3/lib/libfftw3l.so ${third_party}/intel_hexl/lib/libhexl.a)

add_subdirectory(examples) 
 
add_subdirectory(tests) 


install(
    TARGETS fhe_deck
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib 
)