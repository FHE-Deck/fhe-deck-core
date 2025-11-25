#include <gtest/gtest.h>

#include <iostream> 
#include "verbose_stream.hpp"
#include "fhe_deck.h" 
#include <fstream> 

/// @brief  This flag is defined in test_main.cpp
extern bool verbose;

using namespace FHEDeck;

enum GadgetMulMode {simul, deter};

void rlwe_test(int test_num, long N, long Q, PolynomialArithmetic arithmetic){

    print_out << "============== rlwe_test (N = " << N << ", Q = "<< Q << ") ==================" << std::endl;

    #if defined(USE_CEREAL) 
    int64_t plaintext_mod = 13; 

    std::shared_ptr<Distribution> rand = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, plaintext_mod-1)); 
    KeyDistribution rlwe_key_type = KeyDistribution::binary;
    std::shared_ptr<RLWEParam> rlwe_par(new RLWEParam(RingType::negacyclic, N, Q, arithmetic));
 
    {
        /// Serialize and Deserialize  RLWE Param 
        std::ofstream os_rlwe_param("rlweParam_test", std::ios::binary); 
        cereal::BinaryOutputArchive oarchive_rlwe_param(os_rlwe_param); 
        oarchive_rlwe_param(rlwe_par); 
        os_rlwe_param.close();   
    }  
    {
        std::shared_ptr<RLWEParam> rlwe_par_2;
        std::ifstream is_rlwe_param("rlweParam_test", std::ios::binary);
        cereal::BinaryInputArchive iarchive_rlwe_param(is_rlwe_param);  
        iarchive_rlwe_param(rlwe_par_2);  
        if(rlwe_par->size != rlwe_par_2->size || rlwe_par->coef_modulus != rlwe_par_2->coef_modulus){
            FAIL();  
        } 
        std::remove("rlweParam_test"); 
    }
 
    std::shared_ptr<RLWESK> sk = std::shared_ptr<RLWESK>(new RLWESK(rlwe_par, rlwe_key_type, 3.2)); 
 
    {
        /// Serialize and Deserialize  RLWE Param 
        std::ofstream os("poly_test", std::ios::binary); 
        cereal::BinaryOutputArchive oarchive(os); 
        oarchive(sk->sk_poly); 
        os.close();   
    }  
    {
        Polynomial sk_poly;
        std::ifstream is("poly_test", std::ios::binary);
        cereal::BinaryInputArchive iarchive(is);  
        iarchive(sk_poly);  
        if(sk->sk_poly.size() != sk_poly.size() || 
        sk->sk_poly.modulus() != sk_poly.modulus() ||
        sk->sk_poly!=sk_poly){
            FAIL(); 
        } 
        std::remove("poly_test"); 
    }
 
    {
        /// Serialize and Deserialize  RLWE Param 
        std::ofstream os_rlwe_sk("rlwe_sk_test", std::ios::binary); 
        cereal::BinaryOutputArchive oarchive_rlwe_sk(os_rlwe_sk); 
        oarchive_rlwe_sk(sk); 
        os_rlwe_sk.close();   
    }  
    {
        std::shared_ptr<RLWESK> rlwe_sk_2;
        std::ifstream is_rlwe_sk("rlwe_sk_test", std::ios::binary);
        cereal::BinaryInputArchive iarchive_rlwe_sk(is_rlwe_sk);  
        iarchive_rlwe_sk(rlwe_sk_2);  
        if(sk->param->size != rlwe_sk_2->param->size || 
        sk->param->coef_modulus != rlwe_sk_2->param->coef_modulus ||
        sk->sk_poly != rlwe_sk_2->sk_poly){
            FAIL();  
        } 
        std::remove("rlwe_sk_test"); 
    }
 
    Polynomial m(rlwe_par->size, plaintext_mod);   
    //m.zeroize(); 
    //rand->fill_array(m.vec, N);
    rand->fill(m);
    
    PlaintextEncoding encoding(PlaintextEncodingType::full_domain, plaintext_mod, Q); 
    std::shared_ptr<RLWECT> ct = std::static_pointer_cast<RLWECT>(sk->encode_and_encrypt(m, encoding));  
    {
        /// Serialize and Deserialize  RLWE Param 
        std::ofstream os("ct_test", std::ios::binary); 
        cereal::BinaryOutputArchive oarchive(os); 
        oarchive(ct); 
        os.close();   
    }  
    {
        std::shared_ptr<RLWECT> ct_test;
        std::ifstream is("ct_test", std::ios::binary);
        cereal::BinaryInputArchive iarchive(is);  
        iarchive(ct_test);  
        if(ct->param->size != ct_test->param->size || 
        ct->param->coef_modulus != ct_test->param->coef_modulus ||
        ct->a != ct_test->a ||
        ct->b != ct_test->b){
            FAIL(); 
        } 
        std::remove("ct_test"); 
    }
 
    Polynomial out(rlwe_par->size, plaintext_mod);
  
    for(int i = 0; i < test_num; ++i){ 
        //rand->fill_array(m.vec, N); 
        rand->fill(m);
        ct = std::static_pointer_cast<RLWECT>(sk->encode_and_encrypt(m, encoding));  
        sk->decrypt(out, *ct.get(), encoding);  
        if(out != m){
            FAIL(); 
        }
    } 
  
    PolynomialMultiplicationEngineBuilder builder = PolynomialMultiplicationEngineBuilder();
    builder.set_degree(rlwe_par->size);
    builder.set_coef_modulus(plaintext_mod);
    builder.set_polynomial_arithmetic(PolynomialArithmetic::naive);
    std::shared_ptr<PolynomialMultiplicationEngine> ntt_engine = builder.build();
 
    Polynomial m_1(rlwe_par->size, plaintext_mod);
    m_1.set_multiplication_engine(ntt_engine);
    m_1.zeroize();
    Polynomial m_2(rlwe_par->size, plaintext_mod);
    m_2.set_multiplication_engine(ntt_engine);
    m_2.zeroize();
    Polynomial exp(rlwe_par->size, plaintext_mod);
    exp.set_multiplication_engine(ntt_engine);
    exp.zeroize();
    for(int i = 0; i < test_num; ++i){    
        //rand->fill_array(m_1.vec, rlwe_par->size); 
        rand->fill(m_1);
        //rand->fill_array(m_2.vec, rlwe_par->size); 
        rand->fill(m_2);
        for(int j = 0; j < rlwe_par->size; ++j){ 
            exp[j] = (m_1[j] + m_2[j]) % plaintext_mod;
        }  
           
        std::shared_ptr<RLWECT> ct_1 = std::static_pointer_cast<RLWECT>(sk->encode_and_encrypt(m_1, encoding));
        std::shared_ptr<RLWECT> ct_2 = std::static_pointer_cast<RLWECT>(sk->encode_and_encrypt(m_2, encoding));  
        RLWECT ct_3(rlwe_par); 
         
        ct_1->add(ct_3, *ct_2.get());   
        sk->decrypt(out, ct_3, encoding);    
          
        //Utils::array_mod_form(out.vec, out.vec, N, plaintext_mod);    
        if(out != exp){
            FAIL(); 
        }
    }  
 
    for(int i = 0; i < test_num; ++i){    
        //rand->fill_array(m_1.vec, rlwe_par->size);    
        rand->fill(m_1);
        //rand->fill_array(m_2.vec, rlwe_par->size);
        rand->fill(m_2); 
        for(int j = 0; j < rlwe_par->size; ++j){ 
            exp[j] = Utils::integer_mod_form(m_1[j] - m_2[j], plaintext_mod);
        }   
        std::shared_ptr<RLWECT> ct_1 = std::static_pointer_cast<RLWECT>(sk->encode_and_encrypt(m_1, encoding));
        std::shared_ptr<RLWECT> ct_2 = std::static_pointer_cast<RLWECT>(sk->encode_and_encrypt(m_2, encoding));  
        std::shared_ptr<RLWECT> ct_3(new RLWECT(rlwe_par));  
        ct_1->sub(*ct_3.get(), *ct_2.get());   
        sk->decrypt(out, *ct_3.get(), encoding);     
        //Utils::array_mod_form(out.vec, out.vec, N, plaintext_mod);    
        if(out != exp){
            FAIL(); 
        }
    } 
  
    for(int i = 0; i < test_num; ++i){    
        //rand->fill_array(m_1.vec, rlwe_par->size);  
        rand->fill(m_1);
        for(int j = 0; j < rlwe_par->size; ++j){ 
            exp[j] = Utils::integer_mod_form(-m_1[j], plaintext_mod);
        }   
        std::shared_ptr<RLWECT> ct_1 = std::static_pointer_cast<RLWECT>(sk->encode_and_encrypt(m_1, encoding)); 
        RLWECT ct_3(rlwe_par); 
        ct_1->neg(ct_3);
        sk->decrypt(out, ct_3, encoding);     
        //Utils::array_mod_form(out.vec, out.vec, N, plaintext_mod);    
        if(out != exp){
            FAIL(); 
        }
    } 

    std::shared_ptr<Distribution> rot_rand = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, 2*N));  
    long rot;
    for(int i = 0; i < test_num; ++i){    
        //rand->fill_array(m_1.vec, rlwe_par->size);  
        rand->fill(m_1);
        rot = 2;  
        m_1.negacyclic_rotate(exp, rot);  
        //Utils::array_mod_form(exp.vec, exp.vec, N, plaintext_mod);
        std::shared_ptr<RLWECT> ct_1 = std::static_pointer_cast<RLWECT>(sk->encode_and_encrypt(m_1, encoding)); 
        RLWECT ct_3(rlwe_par); 
        ct_1->negacyclic_rotate(ct_3, rot);
        sk->decrypt(out, ct_3, encoding);      
        if(out != exp){ 
            print_out << "out: " << out.to_string(15) << std::endl;  
            print_out << "exp: " << exp.to_string(15) << std::endl;  
            print_out << "m_1: " << m_1.to_string(15) << std::endl;    
            FAIL();
        }
    } 

 
    bool mul_test = true;
    Polynomial scalar(rlwe_par->size, plaintext_mod);
    scalar.set_multiplication_engine(ntt_engine);
    scalar.zeroize(); 
    for(int i = 0; i < test_num; ++i){ 
        //rand->fill_array(m_1.vec, N); 
        rand->fill(m_1);
        // NOTE: We are doing a quite sparse polynomial here, because the error may blow up and the test will fail 
        //rand->fill_array(scalar.vec, N/64);   
        rand->fill(scalar);
        m_1.mul(exp, scalar); 
        std::shared_ptr<RLWECT> ct_1 = std::static_pointer_cast<RLWECT>(sk->encode_and_encrypt(m_1, encoding)); 
        RLWECT ct_3(rlwe_par);
        ct_1->mul(ct_3, scalar); 
        sk->decrypt(out, ct_3, encoding); 
        //Utils::array_mod_form(out.vec, out.vec, N, plaintext_mod); 
        if(out != exp){
            FAIL(); 
            print_out << "out: " << out.to_string(15) << std::endl;  
            print_out << "exp: " << exp.to_string(15) << std::endl;   
        }
    }  
    #endif 
}
  

void gadget_rlwe_basic_test(int test_num, GadgetMulMode mode, long N, long Q, long base, PolynomialArithmetic arithmetic){
    print_out << "========== gadget_rlwe_basic_test ==========" << std::endl;
   
    int plaintext_mod = 13; 
    PlaintextEncoding encoding(PlaintextEncodingType::full_domain, plaintext_mod, Q);
    //Sampler rand;
    std::shared_ptr<Distribution> rand = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, plaintext_mod-1)); 
    KeyDistribution rlwe_key_type = KeyDistribution::ternary;
    std::shared_ptr<RLWEParam> rlwe_par(new RLWEParam(RingType::negacyclic, N, Q, PolynomialArithmetic::ntt64));
    std::shared_ptr<RLWESK> sk = std::shared_ptr<RLWESK>(new RLWESK(rlwe_par, rlwe_key_type, 3.2)); 

    std::shared_ptr<Gadget> deter_gadget;
    if(mode == deter){
        deter_gadget = std::shared_ptr<Gadget>(new SignedDecompositionGadget(N, Q, base)); 
    }else if(mode == simul){
        deter_gadget = std::shared_ptr<Gadget>(new DiscreteGaussianSamplingGadget(N, Q, base, base+1));  
    }else{
        FAIL(); 
    }  
 
    RLWEGadgetSK gadget_sk(deter_gadget, sk);
   
    PolynomialMultiplicationEngineBuilder builder = PolynomialMultiplicationEngineBuilder();
    builder.set_degree(rlwe_par->size);
    builder.set_coef_modulus(plaintext_mod);
    builder.set_polynomial_arithmetic(PolynomialArithmetic::naive);
    std::shared_ptr<PolynomialMultiplicationEngine> ntt_engine = builder.build();

    Polynomial m = Polynomial(rlwe_par->size, plaintext_mod);
    m.set_multiplication_engine(ntt_engine);
    m.zeroize(); 
    Polynomial out = Polynomial(rlwe_par->size, plaintext_mod);
    out.set_multiplication_engine(ntt_engine);
    out.zeroize();
    Polynomial gadget_m = Polynomial(rlwe_par->size, plaintext_mod);
    gadget_m.set_multiplication_engine(ntt_engine);
    gadget_m.zeroize();
    Polynomial exp_poly = Polynomial(rlwe_par->size, plaintext_mod);
    exp_poly.set_multiplication_engine(ntt_engine);
    exp_poly.zeroize();
 
    for(int i = 0; i < test_num; ++i){ 
        //rand->fill_array(m.vec, rlwe_par->size); 
        rand->fill(m);
        //rand->fill_array(gadget_m.vec, rlwe_par->size);  
        rand->fill(gadget_m);
        m.mul(exp_poly, gadget_m);
        std::shared_ptr<RLWECT> ct = std::static_pointer_cast<RLWECT>(sk->encode_and_encrypt(m, encoding));
        std::shared_ptr<RLWEGadgetCT> g_ct = std::static_pointer_cast<RLWEGadgetCT>(std::shared_ptr<GadgetVectorCT>(gadget_sk.gadget_encrypt(gadget_m))); 
        
        RLWECT ct_prod(rlwe_par);
        g_ct->mul(ct_prod, *ct.get());  

        sk->decrypt(out, ct_prod, encoding);
        //Utils::array_mod_form(out.vec, out.vec, N, plaintext_mod);
        if(out != exp_poly){
            print_out << "Fail at: " << i << std::endl;
            print_out << "gadget rlwe test: Fail" << std::endl;
            print_out << "out: " << out.to_string(15) << std::endl;  
            print_out << "exp_poly: " << exp_poly.to_string(15) << std::endl;   
            FAIL();
        } 
    }  
}
 
void gadget_rlwe_test(int test_num, GadgetMulMode mode, long N, long Q, long base, PolynomialArithmetic arithmetic){
    
    #if defined(USE_CEREAL)
    print_out << "============== gadget_rlwe_test (N = " << N << ", Q = "<< Q << ", base: " << base << ") ==================" << std::endl;
  
    int plaintext_modulus = 5; 
    PlaintextEncoding encoding(PlaintextEncodingType::full_domain, plaintext_modulus, Q); 
    std::shared_ptr<Distribution> rand = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, plaintext_modulus-1)); 
    KeyDistribution rlwe_key_type = KeyDistribution::ternary;
    std::shared_ptr<RLWEParam> rlwe_par(new RLWEParam(RingType::negacyclic, N, Q, arithmetic)); 
    std::shared_ptr<RLWESK> sk = std::shared_ptr<RLWESK>(new RLWESK(rlwe_par, rlwe_key_type, 3.2));  
    
    std::shared_ptr<Gadget> deter_gadget;
    if(mode == deter){
        deter_gadget = std::shared_ptr<Gadget>(new SignedDecompositionGadget(N, Q, base)); 
    }else if(mode == simul){
        deter_gadget = std::shared_ptr<Gadget>(new DiscreteGaussianSamplingGadget(N, Q, base, base+1));  
    }else{
        FAIL(); 
    }
  
    {
        /// Serialize and Deserialize  Gadget
        std::ofstream os("gadget_serialization_test", std::ios::binary); 
        cereal::BinaryOutputArchive oarchive(os); 
        oarchive(deter_gadget); 
        os.close();   
    }  
    {
        std::shared_ptr<Gadget> deter_gadget_test;
        std::ifstream is("gadget_serialization_test", std::ios::binary);
        cereal::BinaryInputArchive iarchive(is);  
        iarchive(deter_gadget_test);   
        if(deter_gadget->degree != deter_gadget_test->degree ||
            deter_gadget->modulus != deter_gadget_test->modulus ||
            deter_gadget->base != deter_gadget_test->base ||
            deter_gadget->bits_base != deter_gadget_test->bits_base){
                FAIL(); 
        } 
        std::remove("gadget_serialization_test"); 
    }
 
        print_out << "Serialization of gadget SK" << std::endl;
    RLWEGadgetSK gadget_sk_test(deter_gadget, sk);
    RLWEGadgetSK gadget_sk(deter_gadget, sk); 
    {
        /// Serialize and Deserialize  RLWEGadgetSK
        std::ofstream os("gadget_sk_serialization_test", std::ios::binary); 
        cereal::BinaryOutputArchive oarchive(os); 
        oarchive(gadget_sk_test); 
        os.close();   
    }  
    { 
        std::ifstream is("gadget_sk_serialization_test", std::ios::binary);
        cereal::BinaryInputArchive iarchive(is);  
        iarchive(gadget_sk);    
        std::remove("gadget_sk_serialization_test"); 
    } 
 
    PolynomialMultiplicationEngineBuilder builder = PolynomialMultiplicationEngineBuilder();
    builder.set_degree(rlwe_par->size);
    builder.set_coef_modulus(plaintext_modulus);
    builder.set_polynomial_arithmetic(PolynomialArithmetic::naive);
    std::shared_ptr<PolynomialMultiplicationEngine> ntt_engine = builder.build();

    Polynomial m = Polynomial(rlwe_par->size, plaintext_modulus); 
    m.set_multiplication_engine(ntt_engine);
    m.zeroize();
    Polynomial out = Polynomial(rlwe_par->size, plaintext_modulus);
    out.set_multiplication_engine(ntt_engine);
    Polynomial gadget_m = Polynomial(rlwe_par->size, plaintext_modulus);
    gadget_m.set_multiplication_engine(ntt_engine);
    gadget_m.zeroize();
    gadget_m[0] = 1;
    Polynomial exp_poly = Polynomial(rlwe_par->size, plaintext_modulus);
    exp_poly.zeroize();
    exp_poly.set_multiplication_engine(ntt_engine);
    
    bool test = true; 
    for(int i = 0; i < test_num; ++i){ 
        //rand->fill_array(m.vec, N); 
        rand->fill(m);
        //rand->fill_array(gadget_m.vec, N); 
        rand->fill(gadget_m);
        m.mul(exp_poly, gadget_m); 
        std::shared_ptr<RLWECT> ct = std::static_pointer_cast<RLWECT>(sk->encode_and_encrypt(m, encoding));
        std::shared_ptr<RLWEGadgetCT> g_ct_test = std::static_pointer_cast<RLWEGadgetCT>(std::shared_ptr<GadgetVectorCT>(gadget_sk.gadget_encrypt(gadget_m)));   
        {
            /// Serialize and Deserialize  RLWEGadgetSK
            std::ofstream os("gadget_ct_serialization_test", std::ios::binary); 
            cereal::BinaryOutputArchive oarchive(os); 
            oarchive(g_ct_test); 
            os.close();   
        }  
        std::shared_ptr<RLWEGadgetCT> g_ct;
        { 
            std::ifstream is("gadget_ct_serialization_test", std::ios::binary);
            cereal::BinaryInputArchive iarchive(is);  
            iarchive(g_ct);    
            std::remove("gadget_ct_serialization_test");  
        } 

        RLWECT ct_prod(rlwe_par); 
        g_ct->mul(ct_prod, *ct.get()); 
        sk->decrypt(out, ct_prod, encoding);
        //Utils::array_mod_form(out.vec, out.vec, N, plaintext_modulus);
        if(out != exp_poly){ 
            FAIL();
            print_out << "\rFail at: " << i << std::endl;
            print_out << "gadget rlwe test: Fail" << std::endl;
            print_out << "out: " << out.to_string(15) << std::endl;  
            print_out << "exp_poly: " << exp_poly.to_string(15) << std::endl;  
            print_out << "m: " << m.to_string(15) << std::endl;   
        } 
    }  
 

    test = true; 
    for(int i = 0; i < test_num; ++i){ 
        //rand->fill_array(m.vec, N); 
        rand->fill(m);
        //rand->fill_array(gadget_m.vec, N); 
        rand->fill(gadget_m);
        m.mul(exp_poly, gadget_m);
        for(int j = 0; j < N; ++j){
            m[j] = encoding.encode_message(m[j]);
        }
         
        std::shared_ptr<ExtendedRLWECT> ext_ct_test = std::static_pointer_cast<ExtendedRLWECT>(std::shared_ptr<ExtendedPolynomialCT>(gadget_sk.extended_encrypt(gadget_m)));   
         
        RLWECT ct_prod(rlwe_par);  
        ext_ct_test->mul(ct_prod, m);  
        sk->decrypt(out, ct_prod, encoding);
        //Utils::array_mod_form(out.vec, out.vec, N, plaintext_modulus);
        if(out != exp_poly){ 
            print_out << "\rFail at: " << i << std::endl;
            print_out << "Extended rlwe test: Fail" << std::endl;
            print_out << "out: " << out.to_string(15) << std::endl;  
            print_out << "exp_poly: " << exp_poly.to_string(15) << std::endl;  
            print_out << "m: " <<  m.to_string(15) << std::endl;    
            FAIL();
        } 
    } 

    #endif
}

 
// ==============================================
// RLWE Test Suite
// ==============================================
 

// -----------------------------
// Struct: RLWETestParam
// -----------------------------
struct RLWETestParam {
    int32_t test_num;
    int64_t N;
    int64_t Q;
    PolynomialArithmetic arithmetic;
};

// -----------------------------
// Class: BasicRLWE
// -----------------------------
class BasicRLWE : public ::testing::TestWithParam<RLWETestParam> { };

TEST_P(BasicRLWE, BasicRLWETest) {
    RLWETestParam param_set = GetParam();
    rlwe_test(param_set.test_num, param_set.N, param_set.Q, param_set.arithmetic);
}

// Parameter registration
INSTANTIATE_TEST_SUITE_P(
    BasicRLWETest,
    BasicRLWE,
    ::testing::Values(
        RLWETestParam{100, 4096, 35184371884033, PolynomialArithmetic::ntt64},
        RLWETestParam{100, 4096, 288230376151130113, PolynomialArithmetic::ntt64},
        RLWETestParam{100, 4096, 1152921504606830593, PolynomialArithmetic::ntt64},
        RLWETestParam{100, 4096, 2305843009213554689, PolynomialArithmetic::ntt64},
        RLWETestParam{100, 4096, 4611686018427322369, PolynomialArithmetic::ntt64}
    )
);


// -----------------------------
// Struct: GadgetRLWETestParam
// -----------------------------
struct GadgetRLWETestParam {
    int32_t test_num;
    GadgetMulMode mode;
    int64_t N;
    int64_t Q;
    int64_t base;
    PolynomialArithmetic arithmetic;
};

// -----------------------------
// Class: GadgetRLWE
// -----------------------------
class GadgetRLWE : public ::testing::TestWithParam<GadgetRLWETestParam> { };

TEST_P(GadgetRLWE, GadgetRLWETest) {
    GadgetRLWETestParam param_set = GetParam();
    gadget_rlwe_test(param_set.test_num, param_set.mode, param_set.N, param_set.Q, param_set.base, param_set.arithmetic);
}


TEST_P(GadgetRLWE, GadgetBasicRLWETest) {
    GadgetRLWETestParam param_set = GetParam();
    gadget_rlwe_basic_test(param_set.test_num, param_set.mode, param_set.N, param_set.Q, param_set.base, param_set.arithmetic);
}

 
// Parameter registration
INSTANTIATE_TEST_SUITE_P(
    GadgetRLWETest,
    GadgetRLWE,
    ::testing::Values(
        GadgetRLWETestParam{100, deter, 512, 67104769, 8, PolynomialArithmetic::ntt64},
        GadgetRLWETestParam{100, deter, 512, 67104769, 8, PolynomialArithmetic::double_fft},
        GadgetRLWETestParam{100, deter, 4096, 4503599627149313, 8, PolynomialArithmetic::ntt64},
        GadgetRLWETestParam{100, deter, 4096, 9007199254429697, 8, PolynomialArithmetic::ntt64},
        GadgetRLWETestParam{100, deter, 4096, 18014398509309953, 8, PolynomialArithmetic::ntt64},
        GadgetRLWETestParam{100, deter, 4096, 288230376151130113, 8, PolynomialArithmetic::ntt64},
        GadgetRLWETestParam{100, deter, 4096, 1152921504606830593, 8, PolynomialArithmetic::ntt64},
        GadgetRLWETestParam{10,  deter, 4096, 2305843009213554689, 4, PolynomialArithmetic::ntt64} 
    )
); 
  