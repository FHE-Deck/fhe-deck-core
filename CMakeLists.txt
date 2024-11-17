cmake_minimum_required(VERSION 3.13)
 
project(fhe_deck)
 
### Setting External Depandencies
 
# Set Variabled for the NTL library. The NTL library must be installed on the system. That is when linking we use -lntl.
if(NOT DEFINED USE_NTLLib)  
    set(USE_NTLLib TRUE) 
endif()

message("--- USE_NTLLib: " ${USE_NTLLib})

if(USE_NTLLib)
    add_definitions(-DUSE_NTL)
    set(ntl_link ntl)
else()
    set(ntl_link "")
endif() 

### Now we will download, configure and compile other external libraries. 
#Set folder for third_party libraries. 
set(third_party "${PROJECT_SOURCE_DIR}/build/third_party")


# Set Intel Hexl
if(NOT DEFINED USE_IntelHexl)  
    set(USE_IntelHexl TRUE)
endif()

message("--- USE_IntelHexl: " ${USE_IntelHexl})

if(USE_IntelHexl)
    add_definitions(-DUSE_IntelHexl)
    set(intelhexl_link ${third_party}/intel_hexl/lib/libhexl.a)
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
else()
    set(intelhexl_link "")
endif() 

# Set FFTW
if(NOT DEFINED USE_FFTW)  
    set(USE_FFTW TRUE)
endif() 
message("--- USE_FFTW: " ${USE_FFTW}) 
if(USE_FFTW)
    add_definitions(-DUSE_FFTW)
    set(fftw_link ${third_party}/fftw3/lib/libfftw3.so)
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
else()
    set(fftw_link "")
endif() 


# Set FFTW
if(NOT DEFINED USE_FFTWL)  
    set(USE_FFTWL TRUE)
endif() 
message("--- USE_FFTWL: " ${USE_FFTWL}) 
if(USE_FFTWL)
    add_definitions(-DUSE_FFTWL)
    set(fftwl_link ${third_party}/fftwl3/lib/libfftw3l.so)
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
else()
    set(fftwl_link "")
endif() 


# Set CEREAL
if(NOT DEFINED USE_CEREAL)  
    set(USE_CEREAL TRUE)
endif() 
message("--- USE_CEREAL: " ${USE_CEREAL}) 
if(USE_CEREAL)
    add_definitions(-DUSE_CEREAL)
    include(ExternalProject)  
    ExternalProject_Add(
        cereal_lib
        GIT_REPOSITORY https://github.com/USCiLab/cereal.git
        GIT_TAG v1.3.2
        PREFIX ${PROJECT_SOURCE_DIR}/external/cereal_lib
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${third_party}/cereal -DSKIP_PERFORMANCE_COMPARISON=ON -DBUILD_TESTS=OFF
    ) 
    include_directories(${third_party}/cereal/include)
    link_directories(${third_party}/cereal/lib) 
endif() 

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 
 
message("--- CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})

if(CMAKE_BUILD_TYPE STREQUAL "Release")  
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -funroll-loops")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -funroll-loops -fsanitize=address -static-libasan -g")
else()
    message("CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE}) 
endif()

message("--- CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS})

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
  
target_include_directories(fhe_deck PUBLIC include)  
target_link_libraries(fhe_deck PUBLIC ${ntl_link} ${fftw_link} ${fftwl_link} ${intelhexl_link})
 
add_subdirectory(examples) 

# Optionally compile tests from the tests directory (Caution: This directory is not on Github!)
if(NOT DEFINED USE_TESTS)  
    set(USE_TESTS FALSE) 
endif()
message("--- USE_TESTS: " ${USE_TESTS})
if(USE_TESTS)
    add_subdirectory(tests) 
endif()

install(
    TARGETS fhe_deck
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)

install(
    TARGETS fhe_deck
    EXPORT fhe_deck
)

install(
    DIRECTORY include
    DESTINATION ${CMAKE_INSTALL_PREFIX}
)