#include <cstdint>
#include <iostream>
#include <vector>



#include "utils.h"
#include "sample.h"
#include "fft_plan.h"
#include "enums.h"

#include "hexl/hexl.hpp"

using namespace fhe_deck;

bool CheckEqual(const std::vector<uint64_t>& x,
                const std::vector<uint64_t>& y) {
  if (x.size() != y.size()) {
    std::cout << "Not equal in size\n";
    return false;
  }
  uint64_t N = x.size();
  bool is_match = true;
  for (size_t i = 0; i < N; ++i) {
    std::cout << "compare x["<< i << "] = " << x[i] << " with y["<< i << "] = " << y[i] << std::endl;
    if (x[i] != y[i]) {
      std::cout << "Not equal at index " << i << "\n";
      is_match = false;
    }
  }
  return is_match;
}

void ExampleEltwiseVectorVectorAddMod() {
  std::cout << "Running ExampleEltwiseVectorVectorAddMod...\n";

  std::vector<uint64_t> op1{1, 2, 3, 4, 5, 6, 7, 8};
  std::vector<uint64_t> op2{1, 3, 5, 7, 2, 4, 6, 8};
  uint64_t modulus = 10;
  std::vector<uint64_t> exp_out{2, 5, 8, 1, 7, 0, 3, 6};

  intel::hexl::EltwiseAddMod(op1.data(), op1.data(), op2.data(), op1.size(),
                             modulus);

  CheckEqual(op1, exp_out);
  std::cout << "Done running ExampleEltwiseVectorVectorAddMod\n";
}

void ExampleEltwiseVectorScalarAddMod() {
  std::cout << "Running ExampleEltwiseVectorScalarAddMod...\n";

  std::vector<uint64_t> op1{1, 2, 3, 4, 5, 6, 7, 8};
  uint64_t op2{3};
  uint64_t modulus = 10;
  std::vector<uint64_t> exp_out{4, 5, 6, 7, 8, 9, 0, 1};

  intel::hexl::EltwiseAddMod(op1.data(), op1.data(), op2, op1.size(), modulus);

  CheckEqual(op1, exp_out);
  std::cout << "Done running ExampleEltwiseVectorScalarAddMod\n";
}

void ExampleEltwiseCmpAdd() {
  std::cout << "Running ExampleEltwiseCmpAdd...\n";

  std::vector<uint64_t> op1{1, 2, 3, 4, 5, 6, 7, 8};
  uint64_t cmp = 3;
  uint64_t diff = 5;
  std::vector<uint64_t> exp_out{1, 2, 3, 9, 10, 11, 12, 13};

  intel::hexl::EltwiseCmpAdd(op1.data(), op1.data(), op1.size(),
                             intel::hexl::CMPINT::NLE, cmp, diff);

  CheckEqual(op1, exp_out);
  std::cout << "Done running ExampleEltwiseCmpAdd\n";
}

void ExampleEltwiseCmpSubMod() {
  std::cout << "Running ExampleEltwiseCmpSubMod...\n";

  std::vector<uint64_t> op1{1, 2, 3, 4, 5, 6, 7};
  uint64_t bound = 4;
  uint64_t diff = 5;
  std::vector<uint64_t> exp_out{1, 2, 3, 4, 0, 1, 2};

  uint64_t modulus = 10;

  intel::hexl::EltwiseCmpSubMod(op1.data(), op1.data(), op1.size(), modulus,
                                intel::hexl::CMPINT::NLE, bound, diff);
  CheckEqual(op1, exp_out);
  std::cout << "Done running ExampleEltwiseCmpSubMod\n";
}

void ExampleEltwiseFMAMod() {
  std::cout << "Running ExampleEltwiseFMAMod...\n";

  std::vector<uint64_t> arg1{1, 2, 3, 4, 5, 6, 7, 8, 9};
  uint64_t arg2 = 1;
  std::vector<uint64_t> exp_out{1, 2, 3, 4, 5, 6, 7, 8, 9};
  uint64_t modulus = 769;

  intel::hexl::EltwiseFMAMod(arg1.data(), arg1.data(), arg2, nullptr,
                             arg1.size(), modulus, 1);
  CheckEqual(arg1, exp_out);
  std::cout << "Done running ExampleEltwiseFMAMod\n";
}

void ExampleEltwiseMultMod() {
  std::cout << "Running ExampleEltwiseMultMod...\n";

  std::vector<uint64_t> op1{2, 4, 3, 2};
  std::vector<uint64_t> op2{2, 1, 2, 0};
  std::vector<uint64_t> exp_out{4, 4, 6, 0};

  uint64_t modulus = 769;

  intel::hexl::EltwiseMultMod(op1.data(), op1.data(), op2.data(), op1.size(),
                              modulus, 1);
  CheckEqual(op1, exp_out);
  std::cout << "Done running ExampleEltwiseMultMod\n";
}

void ExampleNTT() {
  std::cout << "Running ExampleNTT...\n";

  uint64_t N = 8;
  uint64_t modulus = 769;
  std::vector<uint64_t> arg{1, 2, 3, 4, 5, 6, 7, 8};
  auto exp_out = arg;
  intel::hexl::NTT ntt(N, modulus);

  ntt.ComputeForward(arg.data(), arg.data(), 1, 1);

  std::cout << "arg: " ;
  for(size_t i = 0; i < N-1; ++i){
    std::cout <<  arg[i]  << ", " ;
  }
  std::cout << arg[N-1] << std::endl;

  ntt.ComputeInverse(arg.data(), arg.data(), 1, 1);

    std::cout << "arg: " ;
  for(size_t i = 0; i < N-1; ++i){
    std::cout <<  arg[i]  << ", " ;
  }
  std::cout << arg[N-1] << std::endl;

  CheckEqual(arg, exp_out);
  std::cout << "Done running ExampleNTT\n";
}

void ExampleReduceMod() {
  std::cout << "Running ExampleReduceMod...\n";

  uint64_t modulus = 5;
  std::vector<uint64_t> arg{1, 2, 3, 4, 5, 6, 7, 8};
  std::vector<uint64_t> exp_out{1, 2, 3, 4, 0, 1, 2, 3};
  std::vector<uint64_t> result{0, 0, 0, 0, 0, 0, 0, 0};
  intel::hexl::EltwiseReduceMod(result.data(), arg.data(), arg.size(), modulus,
                                2, 1);

  CheckEqual(result, exp_out);
  std::cout << "Done running ExampleReduceMod\n";
}



void simple_polynomial_mul(){
    std::cout << "Simple Polynomial Multiplication" << std::endl;

    uint64_t N = 4;
    uint64_t modulus = 13;
    std::vector<uint64_t> arg{1, 2, 3, 0};
    auto exp_out = arg;
    intel::hexl::NTT ntt(N, modulus);

    std::cout << "arg: " ;
    for(size_t i = 0; i < N-1; ++i){
    std::cout <<  arg[i]  << ", " ;
  }
  std::cout << arg[N-1] << std::endl;

  ntt.ComputeForward(arg.data(), arg.data(), 1, 1);
  std::cout << "arg: " ;
  for(size_t i = 0; i < N-1; ++i){
    std::cout <<  arg[i]  << ", " ;
  }
  std::cout << arg[N-1] << std::endl;
  ntt.ComputeInverse(arg.data(), arg.data(), 1, 1);
  std::cout << "arg: " ;
  for(size_t i = 0; i < N-1; ++i){
    std::cout <<  arg[i]  << ", " ;
  }
  std::cout << arg[N-1] << std::endl;
}


void simple_mul(){
     uint64_t N = 8;
  uint64_t modulus = 769;
  std::vector<uint64_t> x{1, 2, 3, 4, 5, 6, 7, 8};
  std::vector<uint64_t> y{0, 1, 0, 0, 0, 0, 0, 0}; 
  std::vector<uint64_t> z{0, 0, 0, 0, 0, 0, 0, 0}; 
  intel::hexl::NTT ntt(N, modulus);

  ntt.ComputeForward(x.data(), x.data(), 1, 1);
  ntt.ComputeForward(y.data(), y.data(), 1, 1);
 
    std::cout << "x: " ;
    for(size_t i = 0; i < N-1; ++i){
        std::cout <<  x[i]  << ", " ;
    }
    std::cout << x[N-1] << std::endl;

    std::cout << "y: " ;
    for(size_t i = 0; i < N-1; ++i){
        std::cout <<  y[i]  << ", " ;
    }
    std::cout << y[N-1] << std::endl;

    intel::hexl::EltwiseMultMod(z.data(), x.data(), y.data(), x.size(), modulus, 1);
   
    std::cout << "z: " ;
    for(size_t i = 0; i < N-1; ++i){
        std::cout <<  z[i]  << ", " ;
    }
    std::cout << z[N-1] << std::endl;

    ntt.ComputeInverse(z.data(), z.data(), 1, 1);
    std::cout << "z: " ;
    for(size_t i = 0; i < N-1; ++i){
        std::cout <<  z[i]  << ", " ;
    }
    std::cout << z[N-1] << std::endl;
}


void random_mul_test(){ 
    std::cout << "random_mul_test: " ;
    //long N = 8;
    //long Q = 769;
    long Q = 35184371884033;
    long N = 4096;
    long *psi = new long[N+1];
    psi[0] = 1; 
    psi[N] = 1;
    for(int i=1; i < N; ++i){
        psi[i] = 0;
    } 
    //Sampler rand;
    std::shared_ptr<Distribution> rand = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, Q));
    NTL::ZZ_pX psi_poly;
    Utils::set_polynomial_from_array(psi_poly, psi, N+1, Q); 

    uint64_t poly_1[N];
    uint64_t poly_2[N]; 
    long *prod = new long[N]; 

    intel::hexl::NTT ntt(N, Q);    
    uint64_t x[N];
    uint64_t y[N]; 
    uint64_t z[N];
    
    bool test = true;

    for(int i = 0; i < 1000; ++i)
    {
        //rand.uniform_array((long*) poly_1, N, Q);
        rand->fill_array((long*) poly_1, N);
        //rand.uniform_array((long*) poly_2, N, Q); 
        rand->fill_array((long*) poly_2, N);
        Utils::mul_mod(prod, (long*) poly_1, N, (long*) poly_2, N, N, Q, negacyclic);  
        ntt.ComputeForward(x, poly_1, 1, 1);
        ntt.ComputeForward(y, poly_2, 1, 1);
        intel::hexl::EltwiseMultMod(z, x, y, N, Q, 1);
        ntt.ComputeInverse(z, z, 1, 1);
        for(int j = 0; j < N; ++j){
            if(z[j] != prod[j]){ 
                test = false;
                break;
            }
        } 
    } 
    if(test){
        std::cout << "OK" << std::endl;
    }else{
        std::cout << "Fail" << std::endl;
    } 
}




void random_multisum_test(long N, long Q){ 
    std::cout << "random_multisum_test: N = " << N << ", Q = " << Q << std::endl ; 
    //long Q = 35184371884033;
    //long N = 4096;
    long *psi = new long[N+1];
    psi[0] = 1; 
    psi[N] = 1;
    for(int i=1; i < N; ++i){
        psi[i] = 0;
    } 
    //Sampler rand;
    std::shared_ptr<Distribution> rand = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, Q));
    NTL::ZZ_pX psi_poly;
    Utils::set_polynomial_from_array(psi_poly, psi, N+1, Q); 

    uint64_t poly_1[N];
    uint64_t poly_2[N]; 
    long *prod = new long[N]; 

    intel::hexl::NTT ntt(N, Q);    
    uint64_t x[N];
    uint64_t y[N]; 
    uint64_t z[N];
    
    bool test = true;



    long* multisum_ntl = new long[N];
    long* multisum_hexl = new long[N];
    for(int j = 0; j < N; ++j){
        multisum_ntl[j] = 0;
        multisum_hexl[j] = 0;
    }

 
    std::chrono::high_resolution_clock::time_point start, end; 
    long total_time = 0;
    int test_num = 1000;
    for(int i = 0; i < test_num; ++i)
    {
       //rand.uniform_array((long*) poly_1, N, Q);
        rand->fill_array((long*) poly_1, N);
        //rand.uniform_array((long*) poly_2, N, Q); 
        rand->fill_array((long*) poly_2, N);
        Utils::array_signed_form((long*) poly_1, (long*) poly_1, N, Q);
        Utils::mul_mod(prod, (long*) poly_1, N, (long*) poly_2, N, N, Q, negacyclic);   
        Utils::add_mod(multisum_ntl, multisum_ntl,  N, prod, N, N, Q);
        Utils::array_mod_form((long*) multisum_ntl, (long*) multisum_ntl, N, Q);
        Utils::array_mod_form((long*) poly_1, (long*) poly_1, N, Q);

        ntt.ComputeForward(x, poly_1, 1, 1); 
        start = std::chrono::high_resolution_clock::now(); 
        ntt.ComputeForward(y, poly_2, 1, 1);
        intel::hexl::EltwiseMultMod(z, x, y, N, Q, 1);
        intel::hexl::EltwiseAddMod((uint64_t*) multisum_hexl, (uint64_t*) multisum_hexl, z, N, Q); 
        end = std::chrono::high_resolution_clock::now(); 
        total_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();   
    }  
    ntt.ComputeInverse((uint64_t*) multisum_hexl, (uint64_t*) multisum_hexl, 1, 1);

    for(int j = 0; j < N; ++j){
        if(multisum_hexl[j] != multisum_ntl[j]){ 
            test = false; 
        }
    }  
    if(test){
        std::cout << "OK" << std::endl;
    }else{
        std::cout << "Fail" << std::endl;
    }

    double avg_ms = total_time/ test_num ;
    std::cout << "Avg Time avg_ms: " << avg_ms/1000000 << " [ms], " << avg_ms/1000000000 << " [s]" << std::endl; 
}

int main() {
  //ExampleEltwiseVectorVectorAddMod();
  //ExampleEltwiseVectorScalarAddMod();
  //ExampleEltwiseCmpAdd();
  //ExampleEltwiseCmpSubMod();
  //ExampleEltwiseFMAMod();
  //ExampleEltwiseMultMod();
  ExampleNTT();
  //ExampleReduceMod();

  simple_polynomial_mul();
  simple_mul();
  random_mul_test();
  // 45 bit
  random_multisum_test(4096, 35184371884033);
  // 50 bit
  random_multisum_test(4096, 1125899906826241);
  // 51 bit
  random_multisum_test(4096, 2251799813554177);
  // 57 bit
  random_multisum_test(4096, 288230376151130113);
  // 61 bit
  random_multisum_test(4096, 2305843009213554689);
  // 62 bit
  random_multisum_test(4096, 4611686018427322369);
  // 63 bit
  random_multisum_test(4096, 9223372036854497281);
   

  return 0;
}
