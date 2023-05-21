 

CC = g++
 
OPTIMIZATION = -std=c++2a -fconcepts -O3 -funroll-loops -march=native 

NTL = -lntl 
FFTW = -lfftw3 -lfftw3l 
PTHREAD = -pthread
EXTERN = $(NTL) $(FFTW) $(PTHREAD) -lhexl -fconcepts 

COMMON_FILES = fft_plan.o utils.o sample.o lwe.o lwe_param.o rotation_poly.o gadget.o fhe_context.o plaintext_encoding.o ciphertext.o
RLWE_FILES = rlwe_hom_acc_scheme.o rlwe_hom_acc_scheme_gen.o rlwe_lib.a rlwe.o rlwe_param.o
NTRU_FILES = ntrunium_lib.a ntrunium.o ntrunium_gen.o ntru_param.o ntru.o
TEST_FILES = fhe_context_test rlwe_hom_acc_scheme_tests error_tests performance_tests fft_mul_tests ntrunium_tests ntru_tests lwe_tests type_tests rlwe_tests hexl_test gadget_tests rotation_poly_test


all: clean rlwe_lib.a ntrunium_lib.a tests 

 
tests: $(TEST_FILES) 


clean:
	$(RM) $(TEST_FILES) $(COMMON_FILES)  $(RLWE_FILES)  $(NTRU_FILES) 



# Libraries
rlwe_lib.a: rlwe_hom_acc_scheme.o rlwe_hom_acc_scheme_gen.o rlwe_param.o rlwe.o utils.o fft_plan.o sample.o rotation_poly.o gadget.o fhe_context.o plaintext_encoding.o ciphertext.o
	$(AR) -q rlwe_lib.a rlwe_hom_acc_scheme.o rlwe_hom_acc_scheme_gen.o rlwe_param.o rlwe.o utils.o fft_plan.o sample.o rotation_poly.o gadget.o fhe_context.o plaintext_encoding.o ciphertext.o

ntrunium_lib.a: sample.o fft_plan.o ntrunium.o ntrunium_gen.o ntru_param.o utils.o rotation_poly.o ntru.o lwe_param.o lwe.o gadget.o fhe_context.o plaintext_encoding.o ciphertext.o
	$(AR) -q ntrunium_lib.a sample.o fft_plan.o ntrunium.o ntrunium_gen.o ntru_param.o utils.o rotation_poly.o ntru.o lwe_param.o lwe.o gadget.o fhe_context.o plaintext_encoding.o ciphertext.o
 

# Tests
fhe_context_test: fhe_context.o plaintext_encoding.o ciphertext.o rlwe_lib.a ntrunium_lib.a
	$(CC) -o fhe_context_test tests/fhe_context_test.cpp fhe_context.o plaintext_encoding.o ciphertext.o rlwe_lib.a ntrunium_lib.a  $(EXTERN) 

gadget_tests: sample.o gadget.o utils.o
	$(CC) -o gadget_tests tests/gadget_tests.cpp gadget.o sample.o utils.o $(EXTERN) 

hexl_test: utils.o sample.o
	$(CC) -o hexl_test tests/hexl_test.cpp utils.o sample.o $(EXTERN) 

rlwe_hom_acc_scheme_tests: rlwe_lib.a lwe.o lwe_param.o 
	$(CC) -o rlwe_hom_acc_scheme_tests tests/rlwe_hom_acc_scheme_tests.cpp rlwe_lib.a lwe.o lwe_param.o ciphertext.o $(EXTERN)  

rlwe_tests: rlwe_lib.a 
	$(CC) -o rlwe_tests tests/rlwe_tests.cpp rlwe_lib.a $(EXTERN)  


error_tests: lwe_param.o lwe.o  ntru_param.o  ntru.o  
	$(CC) -o error_tests tests/error_tests.cpp ntrunium_lib.a $(EXTERN)   


performance_tests: ntrunium_lib.a rlwe_lib.a sample.o fft_plan.o rotation_poly.o ntrunium.o ntrunium_gen.o ntru_param.o ntru.o lwe_param.o lwe.o utils.o  
	$(CC) -o performance_tests tests/performance_tests.cpp ntrunium_lib.a rlwe_lib.a $(EXTERN)   
 
 
fft_mul_tests:  sample.o ntru_param.o ntru.o utils.o fft_plan.o
	$(CC) -o fft_mul_tests tests/fft_mul_tests.cpp  fft_plan.o sample.o ntru_param.o ntru.o utils.o $(EXTERN) 

type_tests:
	$(CC) -o type_tests tests/type_tests.cpp
 
ntrunium_tests: sample.o fft_plan.o ntrunium.o ntrunium_gen.o ntru_param.o utils.o rotation_poly.o ntru.o lwe_param.o lwe.o
	$(CC) -o ntrunium_tests tests/ntrunium_tests.cpp ntrunium.o ntrunium_gen.o fft_plan.o sample.o ntru_param.o utils.o rotation_poly.o ntru.o lwe_param.o lwe.o ciphertext.o plaintext_encoding.o $(EXTERN)  


ntru_tests: sample.o ntru_param.o utils.o ntru.o fft_plan.o
	$(CC) -o ntru_test tests/ntru_tests.cpp sample.o fft_plan.o ntru_param.o utils.o ntru.o $(EXTERN)

lwe_tests: sample.o utils.o lwe_param.o lwe.o  
	$(CC)  -o lwe_test tests/lwe_tests.cpp sample.o utils.o lwe_param.o lwe.o ciphertext.o plaintext_encoding.o $(NTL)


rotation_poly_test: rotation_poly.o sample.o utils.o
	$(CC)  -o rotation_poly_test tests/rotation_poly_test.cpp rotation_poly.o sample.o utils.o   $(NTL)



# Object files
ntru.o: include/ntru.h 
	$(CC) $(OPTIMIZATION) -c src/ntru.cpp
 
ntru_param.o: include/ntru_param.h
	$(CC) $(OPTIMIZATION) -c src/ntru_param.cpp 

lwe_param.o: include/lwe_param.h
	$(CC) $(OPTIMIZATION) -c src/lwe_param.cpp

lwe.o: include/lwe.h 
	$(CC) $(OPTIMIZATION) -c src/lwe.cpp

sample.o: include/sample.h 
	$(CC) $(OPTIMIZATION) -c src/sample.cpp

utils.o: include/utils.h
	$(CC) $(OPTIMIZATION) -c src/utils.cpp 

gadget.o: include/gadget.h
	$(CC) $(OPTIMIZATION) -c src/gadget.cpp 

ntrunium_gen.o: include/ntrunium_gen.h
	$(CC) $(OPTIMIZATION) -c src/ntrunium_gen.cpp 

ntrunium.o: include/ntrunium.h
	$(CC) $(OPTIMIZATION) -c src/ntrunium.cpp 

fft_plan.o: include/fft_plan.h
	$(CC) $(OPTIMIZATION) -c src/fft_plan.cpp
 
rlwe.o: include/rlwe.h
	$(CC) $(OPTIMIZATION) -c src/rlwe.cpp

rotation_poly.o: include/rotation_poly.h
	$(CC) $(OPTIMIZATION) -c src/rotation_poly.cpp

rlwe_param.o: include/rlwe_param.h
	$(CC) $(OPTIMIZATION) -c src/rlwe_param.cpp


rlwe_hom_acc_scheme.o: include/rlwe_hom_acc_scheme.h  
	$(CC) $(OPTIMIZATION) -c src/rlwe_hom_acc_scheme.cpp

rlwe_hom_acc_scheme_gen.o: include/rlwe_hom_acc_scheme_gen.h  
	$(CC) $(OPTIMIZATION) -c src/rlwe_hom_acc_scheme_gen.cpp

plaintext_encoding.o: include/plaintext_encoding.h  
	$(CC) $(OPTIMIZATION) -c src/plaintext_encoding.cpp

ciphertext.o: include/ciphertext.h  
	$(CC) $(OPTIMIZATION) -c src/ciphertext.cpp

fhe_context.o: include/fhe_context.h
	$(CC) $(OPTIMIZATION) -c src/fhe_context.cpp

