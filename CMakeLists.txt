cmake_minimum_required(VERSION 3.13)

project(fhe_deck)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
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
	${INC_FHE} ${SRC_FHE})
target_link_libraries(fhe_deck PRIVATE ntl fftw3 fftw3l hexl)

add_subdirectory(examples) 

#add_subdirectory(tests) 