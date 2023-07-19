cmake_minimum_required(VERSION 3.13)

project(fhe_deck)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -funroll-loops")

# source files
file(GLOB INC_COMMON include/common/*.h)
file(GLOB SRC_COMMON src/common/*.cpp)
include_directories(include/common)

file(GLOB INC_RLWE include/rlwe/*.cpp)
file(GLOB SRC_RLWE src/rlwe/*.cpp)
include_directories(include/rlwe)

file(GLOB INC_NTRU include/ntru/*.cpp)
file(GLOB SRC_NTRU src/ntru/*.cpp)
include_directories(include/ntru)

add_library(fhe_deck STATIC
	${INC_COMMON} ${SRC_COMMON}
	${INC_RLWE} ${SRC_RLWE}
	${INC_NTRU} ${SRC_NTRU})
target_link_libraries(fhe_deck PRIVATE ntl fftw3 fftw3l hexl)

add_subdirectory(examples)
add_subdirectory(bench)
