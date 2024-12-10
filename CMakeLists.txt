cmake_minimum_required(VERSION 3.13)
 
project(fhe_deck)
message("------- Configuring FHE-Deck ")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 
 
if(NOT DEFINED CMAKE_BUILD_TYPE)  
    message("--- CMAKE_BUILD_TYPE not defined. Set to detault Release type.")
    set(CMAKE_BUILD_TYPE "Release") 
elseif(NOT (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "Release"))
    message("--- CMAKE_BUILD_TYPE not defined. Set to detault Release type.")
    set(CMAKE_BUILD_TYPE "Release") 
endif()

message("--- CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})

if(CMAKE_BUILD_TYPE STREQUAL "Release")  
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -funroll-loops")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -funroll-loops -fsanitize=address -static-libasan -g")
else()
    set(CMAKE_BUILD_TYPE "Release") 
    message("CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE}) 
endif()

message("--- CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS})
message("--- CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})
  
file(GLOB SRC_MATH ${CMAKE_CURRENT_SOURCE_DIR}/src/math/*.cpp) 
file(GLOB SRC_CIPHERTEXTS ${CMAKE_CURRENT_SOURCE_DIR}/src/ciphertexts/*.cpp)
file(GLOB SRC_KEYSWITCH ${CMAKE_CURRENT_SOURCE_DIR}/src/keyswitch/*.cpp)
file(GLOB SRC_COMMON ${CMAKE_CURRENT_SOURCE_DIR}/src/common/*.cpp)
file(GLOB SRC_INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/interface/*.cpp)
file(GLOB SRC_FHE ${CMAKE_CURRENT_SOURCE_DIR}/src/fhe/*.cpp)

add_library(fhe_deck STATIC)
   

target_include_directories(fhe_deck
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include> 
)

### Setting External Depandencies for Inversion Engines

if(NOT DEFINED INV_ENGINE)  
    set(INV_ENGINE "BUILDIN") 
endif()
message("--- Use " ${INV_ENGINE} " Inversion Engine")
if(INV_ENGINE STREQUAL "NTL") 
    add_definitions(-DUSE_NTL)
    set(ntl_link ntl)
elseif(INV_ENGINE STREQUAL "BUILDIN") 
    set(ntl_link "")
    list(REMOVE_ITEM SRC_MATH ${CMAKE_CURRENT_SOURCE_DIR}/src/math/ntl_inversion_engine.cpp)
else()
    message(WARNING "Unrecognized inversion engine name " ${INV_ENGINE} " using DEFAULT (Build-in) inversion engine")
    set(ntl_link "") 
    list(REMOVE_ITEM SRC_MATH ${CMAKE_CURRENT_SOURCE_DIR}/src/math/ntl_inversion_engine.cpp)
endif() 

### Now we will download, configure and compile other external libraries. 
#Set folder for third_party libraries. 
set(third_party "${PROJECT_SOURCE_DIR}/build/third_party")
message("--- third_party: " ${third_party})

# Set Intel Hexl
if(NOT DEFINED NTT_ENGINE)  
    set(NTT_ENGINE "Hexl") 
endif()
message("--- Use " ${NTT_ENGINE} " NTT Engine")
if(NTT_ENGINE STREQUAL "Hexl")
    
    add_dependencies(fhe_deck intel_hexl)
    add_definitions(-DUSE_IntelHexl) 
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

    
    target_include_directories(fhe_deck PUBLIC  $<BUILD_INTERFACE:${third_party}/intel_hexl/include>)

    add_library(intel_hexl_lib STATIC IMPORTED)
    set_target_properties(intel_hexl_lib PROPERTIES 
        IMPORTED_LOCATION ${third_party}/intel_hexl/lib/libhexl.a
    ) 
    set(intelhexl_link intel_hexl_lib) 
elseif(NTT_ENGINE STREQUAL "BUILDIN")
    set(intelhexl_link "")  
    list(REMOVE_ITEM SRC_MATH ${CMAKE_CURRENT_SOURCE_DIR}/src/math/intel_hexl_engine.cpp)
else()
    message(WARNING "Unrecognized NTT engine name " ${NTT_ENGINE} " using  Build-in NTT engine")
    set(intelhexl_link "")  
    list(REMOVE_ITEM SRC_MATH ${CMAKE_CURRENT_SOURCE_DIR}/src/math/intel_hexl_engine.cpp)
endif() 

# Set FFTW 
if(NOT DEFINED FFT_ENGINE)  
    set(FFT_ENGINE "FFTW") 
endif() 
message("--- Use " ${FFT_ENGINE} " FFT Engine") 
if(FFT_ENGINE STREQUAL "FFTW")
    
    add_dependencies(fhe_deck fftw_lib)
    add_definitions(-DUSE_FFTW)  
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
    target_include_directories(fhe_deck PUBLIC  $<BUILD_INTERFACE:${third_party}/fftw3/include>)
    add_library(fftw3_lib SHARED IMPORTED)
    set_target_properties(fftw3_lib PROPERTIES 
        IMPORTED_LOCATION ${third_party}/fftw3/lib/libfftw3.so
    )  
    set(fftw_link fftw3_lib)
elseif(FFT_ENGINE STREQUAL "BUILDIN")
    set(fftw_link "") 
    list(REMOVE_ITEM SRC_MATH ${CMAKE_CURRENT_SOURCE_DIR}/src/math/fftw_engine.cpp)
else()
message(WARNING "Unrecognized FFT engine name " ${FFT_ENGINE} " using  Build-in FFT engine")
    set(fftw_link "") 
    list(REMOVE_ITEM SRC_MATH ${CMAKE_CURRENT_SOURCE_DIR}/src/math/fftw_engine.cpp)
endif() 


# Set FFTWL  
if(NOT DEFINED FFT_LONG_DOUBLE_ENGINE)  
    set(FFT_LONG_DOUBLE_ENGINE "FFTW") 
endif() 
message("--- Use " ${FFT_LONG_DOUBLE_ENGINE} " FFT LONG DOUBLE Engine") 
if(FFT_LONG_DOUBLE_ENGINE STREQUAL "FFTW")
    add_dependencies(fhe_deck fftwl_lib)
    add_definitions(-DUSE_FFTWL) 
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
    target_include_directories(fhe_deck PUBLIC  $<BUILD_INTERFACE:${third_party}/fftwl3/include>)

    add_library(fftwl3_lib SHARED IMPORTED)
    set_target_properties(fftwl3_lib PROPERTIES 
        IMPORTED_LOCATION ${third_party}/fftwl3/lib/libfftw3l.so
    )
    set(fftwl_link fftwl3_lib)
elseif(FFT_LONG_DOUBLE_ENGINE STREQUAL "BUILDIN")
    set(fftwl_link "") 
    list(REMOVE_ITEM SRC_MATH ${CMAKE_CURRENT_SOURCE_DIR}/src/math/fftw_long_engine.cpp)
else()
    message(WARNING "Unrecognized FFT LONG DOUBLE engine name " ${FFT_LONG_DOUBLE_ENGINE} " using  Build-in FFT LONG DOUBLE engine")
    set(fftwl_link "") 
    list(REMOVE_ITEM SRC_MATH ${CMAKE_CURRENT_SOURCE_DIR}/src/math/fftw_long_engine.cpp)
endif() 


# Set CEREAL
if(NOT DEFINED USE_CEREAL)  
    set(USE_CEREAL TRUE)
endif() 
message("--- USE_CEREAL: " ${USE_CEREAL}) 
if(USE_CEREAL) 
    add_dependencies(fhe_deck cereal_lib)
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
    target_include_directories(fhe_deck PUBLIC  $<BUILD_INTERFACE:${third_party}/fftwl3/include>) 
endif() 

##### Finished to configure dependencies.




message("--- CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR})

target_sources(fhe_deck PRIVATE 
    ${SRC_CIPHERTEXTS}
    ${SRC_MATH}
    ${SRC_KEYSWITCH}
    ${SRC_INTERFACE}
    ${SRC_COMMON} 
    ${SRC_FHE}
)

# Target Link libraries 
target_link_libraries(fhe_deck PUBLIC ${ntl_link} ${fftw_link} ${fftwl_link} ${intelhexl_link})

get_target_property(deps fhe_deck INTERFACE_LINK_LIBRARIES)
message(STATUS "Used dependencies for fhe_deck: ${deps}")
 

### Add Subdirectories

add_subdirectory(examples) 

# Optionally compile tests from the tests directory (Caution: This directory is not on Github!)
if(NOT DEFINED USE_TESTS)  
    set(USE_TESTS FALSE) 
endif()
message("--- USE_TESTS: " ${USE_TESTS})
if(USE_TESTS)
    add_subdirectory(tests) 
endif()
 
### Install instructions
 
# Install fhe_deck library
install(TARGETS fhe_deck 
    EXPORT fhe_deck_targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# Install export file
install(EXPORT fhe_deck_targets
    FILE FHEDeckConfig.cmake
    DESTINATION lib/cmake
)

# Install include directory
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION include
)
 