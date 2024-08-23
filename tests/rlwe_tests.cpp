#include <iostream> 
#include "rlwe.h"
#include "utils.h" 
#include <fstream>

using namespace fhe_deck;

enum GadgetMulMode {simul, deter};

void rlwe_test(int test_num, long N, long Q, PolynomialArithmetic arithmetic){
    std::cout << "=========== rlwe_test (N = " << N << ", Q = " << Q << ") ========= " << std::endl;
  
    int t = 13;
    //Sampler rand;
    std::shared_ptr<Distribution> rand = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, t-1)); 
    KeyDistribution rlwe_key_type = binary;
    std::shared_ptr<RLWEParam> rlwe_par(new RLWEParam(negacyclic, N, Q, arithmetic));


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
            std::cout << "RLWE Param Serialization Test: Fail" << std::endl;   
        }else{
            std::cout << "RLWE Param Serialization Test: OK" << std::endl;  
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
        if(sk->sk_poly.degree != sk_poly.degree || 
        sk->sk_poly.coef_modulus != sk_poly.coef_modulus ||
        !Utils::is_eq_poly(sk->sk_poly.coefs, sk_poly.coefs, sk->sk_poly.degree)){
            std::cout << "Polynomial Serialization Test: Fail" << std::endl;   
        }else{
            std::cout << "Polynomial Serialization Test: OK" << std::endl;  
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
        !Utils::is_eq_poly(sk->sk_poly.coefs, rlwe_sk_2->sk_poly.coefs, sk->sk_poly.degree)){
            std::cout << "RLWE SK Serialization Test: Fail" << std::endl;   
            std::cout << "sk->sk_poly:        " << Utils::to_string(sk->sk_poly.coefs, 10) << std::endl;   
            std::cout << "rlwe_sk_2->sk_poly: " << Utils::to_string(rlwe_sk_2->sk_poly.coefs, 10) << std::endl;   
        }else{
            std::cout << "RLWE SK Serialization Test: OK" << std::endl;  
        }  
        std::remove("rlwe_sk_test"); 
    }


    Polynomial m(rlwe_par->size, rlwe_par->coef_modulus);   
    m.zeroize();
    //rand.uniform_array(m.coefs, N, t); 
    rand->fill_array(m.coefs, N);
    
    PlaintextEncoding encoding(full_domain, t, Q);
    //RLWECT ct = sk->scale_and_encrypt(&m, t); 
    std::shared_ptr<RLWECT> ct(sk->encode_and_encrypt(&m, encoding)); 

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
        !Utils::is_eq_poly(ct->a.coefs, ct_test->a.coefs, sk->sk_poly.degree) ||
        !Utils::is_eq_poly(ct->b.coefs, ct_test->b.coefs, sk->sk_poly.degree)){
            std::cout << "RLWECT Serialization Test: Fail" << std::endl;   
        }else{
            std::cout << "RLWECT Serialization Test: OK" << std::endl;  
        }  
        std::remove("ct_test"); 
    }


    Polynomial out(rlwe_par->size, rlwe_par->coef_modulus);

    std::cout << "Start" << std::endl;
    bool test = true;
    for(int i = 0; i < test_num; ++i){ 
        rand->fill_array(m.coefs, N); 
        ct = std::shared_ptr<RLWECT>(sk->encode_and_encrypt(&m, encoding));  
        sk->decrypt(&out, ct.get(), encoding);  
        if(!Utils::is_eq_poly(out.coefs, m.coefs, N)){
            std::cout << "rlwe_test: Fail at " << i << std::endl;
            std::cout << "out: " << Utils::to_string(out.coefs, rlwe_par->size) << std::endl;  
            std::cout << "m: " << Utils::to_string(m.coefs, rlwe_par->size) << std::endl;  
            test = false;
            return;
        }
    }
    if(test){
        std::cout << "rlwe_test: OK" << std::endl;
    }else{ 
        throw std::logic_error("rlwe_test: Fail");
    }
 
    bool add_test = true;
    Polynomial m_1(rlwe_par->size, rlwe_par->coef_modulus);
    m_1.zeroize();
    Polynomial m_2(rlwe_par->size, rlwe_par->coef_modulus);
    m_2.zeroize();
    Polynomial exp(rlwe_par->size, rlwe_par->coef_modulus);
    exp.zeroize();
    for(int i = 0; i < test_num; ++i){   
        //rand.uniform_array(m_1.coefs, rlwe_par->size, t); 
        rand->fill_array(m_1.coefs, rlwe_par->size); 

        //rand.uniform_array(m_2.coefs, rlwe_par->size, t); 
        rand->fill_array(m_2.coefs, rlwe_par->size); 
        for(int j = 0; j < rlwe_par->size; ++j){
            //exp[j] = Utils::integer_mod_form(m_1[j] + m_2[j],  t);
            exp.coefs[j] = (m_1.coefs[j] + m_2.coefs[j]) % t;
        }  
          
        //RLWECT ct_1 = sk->scale_and_encrypt(&m_1, t);
        //RLWECT ct_2 = sk->scale_and_encrypt(&m_2, t);  
        std::shared_ptr<RLWECT> ct_1(sk->encode_and_encrypt(&m_1, encoding));
        std::shared_ptr<RLWECT> ct_2(sk->encode_and_encrypt(&m_2, encoding));  
        RLWECT ct_3(rlwe_par); 
         
        ct_1->add(&ct_3, ct_2.get());   
        sk->decrypt(&out, &ct_3, encoding);    
          
        Utils::array_mod_form(out.coefs, out.coefs, N, t);    
        if(!Utils::is_eq_poly(out.coefs, exp.coefs, N)){
            std::cout << "rlwe ADD test: Fail" << std::endl;
            std::cout << "out: " << Utils::to_string(out.coefs, rlwe_par->size) << std::endl;  
            std::cout << "exp: " << Utils::to_string(exp.coefs, rlwe_par->size) << std::endl;  
            std::cout << "m_1: " << Utils::to_string(m_1.coefs, rlwe_par->size) << std::endl;  
            std::cout << "m_2: " << Utils::to_string(m_2.coefs, rlwe_par->size) << std::endl;  
            add_test = false;
            return;
        }
    }
    if(add_test){
        std::cout << "rlwe ADD test: OK" << std::endl;
    }else{ 
        throw std::logic_error("rlwe ADD test: Fail");
    }


    bool sub_test = true; 
    for(int i = 0; i < test_num; ++i){   
        //rand.uniform_array(m_1.coefs, rlwe_par->size, t);  
        rand->fill_array(m_1.coefs, rlwe_par->size); 
        //rand.uniform_array(m_2.coefs, rlwe_par->size, t);   
        rand->fill_array(m_2.coefs, rlwe_par->size); 
        for(int j = 0; j < rlwe_par->size; ++j){ 
            exp.coefs[j] = Utils::integer_mod_form(m_1.coefs[j] - m_2.coefs[j], t);
        }   
        std::shared_ptr<RLWECT> ct_1(sk->encode_and_encrypt(&m_1, encoding));
        std::shared_ptr<RLWECT> ct_2(sk->encode_and_encrypt(&m_2, encoding));  
        std::shared_ptr<RLWECT> ct_3(new RLWECT(rlwe_par));  
        ct_1->sub(ct_3.get(), ct_2.get());   
        sk->decrypt(&out, ct_3.get(), encoding);     
        Utils::array_mod_form(out.coefs, out.coefs, N, t);    
        if(!Utils::is_eq_poly(out.coefs, exp.coefs, N)){
            std::cout << "rlwe SUB test: Fail" << std::endl;
            std::cout << "out: " << Utils::to_string(out.coefs, rlwe_par->size) << std::endl;  
            std::cout << "exp: " << Utils::to_string(exp.coefs, rlwe_par->size) << std::endl;  
            std::cout << "m_1: " << Utils::to_string(m_1.coefs, rlwe_par->size) << std::endl;  
            std::cout << "m_2: " << Utils::to_string(m_2.coefs, rlwe_par->size) << std::endl;  
            sub_test = false;
            return;
        }
    }
    if(sub_test){
        std::cout << "rlwe SUB test: OK" << std::endl;
    }else{ 
        throw std::logic_error("rlwe SUB test: Fail");
    }
 
    bool neg_test = true; 
    for(int i = 0; i < test_num; ++i){   
        //rand.uniform_array(m_1.coefs, rlwe_par->size, t);   
        rand->fill_array(m_1.coefs, rlwe_par->size);  
        for(int j = 0; j < rlwe_par->size; ++j){ 
            exp.coefs[j] = Utils::integer_mod_form(-m_1.coefs[j], t);
        }   
        std::shared_ptr<RLWECT> ct_1(sk->encode_and_encrypt(&m_1, encoding)); 
        RLWECT ct_3(rlwe_par); 
        ct_1->neg(&ct_3);
        sk->decrypt(&out, &ct_3, encoding);     
        Utils::array_mod_form(out.coefs, out.coefs, N, t);    
        if(!Utils::is_eq_poly(out.coefs, exp.coefs, N)){
            std::cout << "rlwe NEG test: Fail" << std::endl;
            std::cout << "out: " << Utils::to_string(out.coefs, rlwe_par->size) << std::endl;  
            std::cout << "exp: " << Utils::to_string(exp.coefs, rlwe_par->size) << std::endl;  
            std::cout << "m_1: " << Utils::to_string(m_1.coefs, rlwe_par->size) << std::endl;   
            neg_test = false;
            return;
        }
    }
    if(neg_test){
        std::cout << "rlwe NEG test: OK" << std::endl;
    }else{ 
        throw std::logic_error("rlwe NEG test: Fail");
    }

    std::shared_ptr<Distribution> rot_rand = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, 2*N)); 
    bool negacyclic_rotate_test = true; 
    long rot;
    for(int i = 0; i < test_num; ++i){   
        //rand.uniform_array(m_1.coefs, rlwe_par->size, t);    
        rand->fill_array(m_1.coefs, rlwe_par->size); 
        //rot = rand.uniform(2 * N);
        rot = rot_rand->next();
        Utils::negacyclic_rotate_poly(exp.coefs, m_1.coefs, N, rot);
        Utils::array_mod_form(exp.coefs, exp.coefs, N, t);
        std::shared_ptr<RLWECT> ct_1(sk->encode_and_encrypt(&m_1, encoding)); 
        RLWECT ct_3(rlwe_par); 
        ct_1->negacyclic_rotate(&ct_3, rot);
        sk->decrypt(&out, &ct_3, encoding);     
        Utils::array_mod_form(out.coefs, out.coefs, N, t);    
        if(!Utils::is_eq_poly(out.coefs, exp.coefs, N)){
            std::cout << "rlwe Negacyclic Rotate test: Fail" << std::endl;
            std::cout << "out: " << Utils::to_string(out.coefs, rlwe_par->size) << std::endl;  
            std::cout << "exp: " << Utils::to_string(exp.coefs, rlwe_par->size) << std::endl;  
            std::cout << "m_1: " << Utils::to_string(m_1.coefs, rlwe_par->size) << std::endl;   
            neg_test = false;
            return;
        }
    }
    if(negacyclic_rotate_test){
        std::cout << "rlwe Negacyclic Rotate test: OK" << std::endl;
    }else{ 
        throw std::logic_error("rrlwe Negacyclic Rotate test: Fail");
    }

 
    bool mul_test = true;
    Polynomial scalar(rlwe_par->size, rlwe_par->coef_modulus);
    scalar.zeroize(); 
    for(int i = 0; i < test_num; ++i){
       //rand.uniform_array(m_1.coefs, N, t);   
        rand->fill_array(m_1.coefs, rlwe_par->size); 
        // NOTE: We are doing a quite sparse polynomial here, because the error may blow up and the test will fail
        //rand.uniform_array(scalar.coefs, N/64, t);
        rand->fill_array(scalar.coefs, N/64); 
        Utils::mul_mod(exp.coefs, m_1.coefs, N, scalar.coefs, N, N, t, negacyclic);
        std::shared_ptr<RLWECT> ct_1(sk->encode_and_encrypt(&m_1, encoding)); 
        RLWECT ct_3(rlwe_par);
        ct_1->mul(&ct_3, &scalar); 
        sk->decrypt(&out, &ct_3, encoding); 
        Utils::array_mod_form(out.coefs, out.coefs, N, t); 
        if(!Utils::is_eq_poly(out.coefs, exp.coefs, N)){
            std::cout << "rlwe MUL test: Fail" << std::endl;
            std::cout << "out: " << Utils::to_string(out.coefs, rlwe_par->size) << std::endl;  
            std::cout << "exp: " << Utils::to_string(exp.coefs, rlwe_par->size) << std::endl;  
            mul_test = false;
            return;
        }
    }
    if(mul_test){
        std::cout << "rlwe MUL test: OK" << std::endl;
    }else{ 
        throw std::logic_error("rlwe MUL test: Fail");
    } 
 
}
  

void gadget_rlwe_basic_test(int test_num, GadgetMulMode mode, long N, long Q, long base, PolynomialArithmetic arithmetic){
    std::cout << "========== gadget_rlwe_basic_test ==========" << std::endl;
   
    int t = 13; 
    PlaintextEncoding encoding(full_domain, t, Q);
    //Sampler rand;
    std::shared_ptr<Distribution> rand = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, t)); 
    KeyDistribution rlwe_key_type = ternary;
    std::shared_ptr<RLWEParam> rlwe_par(new RLWEParam(negacyclic, N, Q, ntt64));
    std::shared_ptr<RLWESK> sk = std::shared_ptr<RLWESK>(new RLWESK(rlwe_par, rlwe_key_type, 3.2)); 

    std::shared_ptr<Gadget> deter_gadget;
    if(mode == deter){
        deter_gadget = std::shared_ptr<Gadget>(new SignedDecompositionGadget(N, Q, base)); 
    }else if(mode == simul){
        deter_gadget = std::shared_ptr<Gadget>(new DiscreteGaussianSamplingGadget(N, Q, base, base+1));  
    }else{
        throw std::logic_error("mode can either be deter or simul.");
    }  

    //RLWEGadgetParam gadget_rlwe_par(rlwe_par, base, deter_gadget, rand_gadget);
    //std::shared_ptr<RLWEGadgetParam> gadget_rlwe_par = std::shared_ptr<RLWEGadgetParam>(new RLWEGadgetParam(rlwe_par, deter_gadget)); 
    RLWEGadgetSK gadget_sk(deter_gadget, sk);
  

    Polynomial m = Polynomial(rlwe_par->size, rlwe_par->coef_modulus);
    m.zeroize(); 
    Polynomial out = Polynomial(rlwe_par->size, rlwe_par->coef_modulus);
    out.zeroize();
    Polynomial gadget_m = Polynomial(rlwe_par->size, rlwe_par->coef_modulus);
    gadget_m.zeroize();
    Polynomial exp_poly = Polynomial(rlwe_par->size, rlwe_par->coef_modulus);
    exp_poly.zeroize();

    bool test = true;
    std::cerr << "Test: " << 0 ;
    for(int i = 0; i < test_num; ++i){
        std::cerr << "\rTest: " << i ;
        //rand.uniform_array(m.coefs, N, t);
        rand->fill_array(m.coefs, N);
        //rand.uniform_array(gadget_m.coefs, N, t); 
        rand->fill_array(gadget_m.coefs, N); 
        Utils::mul_mod(exp_poly.coefs, m.coefs, N, gadget_m.coefs, N, N, t, negacyclic);
        std::shared_ptr<RLWECT> ct(sk->encode_and_encrypt(&m, encoding));
        std::shared_ptr<RLWEGadgetCT> g_ct = std::static_pointer_cast<RLWEGadgetCT>(std::shared_ptr<GadgetVectorCT>(gadget_sk.gadget_encrypt(&gadget_m))); 
        
        RLWECT ct_prod(rlwe_par);
        g_ct->mul(&ct_prod, ct.get());  

        sk->decrypt(&out, &ct_prod, encoding);
        Utils::array_mod_form(out.coefs, out.coefs, N, t);
        if(!Utils::is_eq_poly(out.coefs, exp_poly.coefs, N)){
            std::cerr << "Fail at: " << i << std::endl;
            std::cerr << "gadget rlwe test: Fail" << std::endl;
            std::cerr << "out: " << Utils::to_string(out.coefs, rlwe_par->size) << std::endl;  
            std::cerr << "exp_poly: " << Utils::to_string(exp_poly.coefs, rlwe_par->size) << std::endl;  
            test = false;
            break;
        } 
    } 
    std::cerr << "\rTest: " << 100 << std::endl; 
    if(test){
        std::cerr << "gadget rlwe test: OK" << std::endl;
    }else{ 
        throw std::logic_error("gadget rlwe test: Fail");
    }  
}

void gadget_rlwe_test(int test_num, GadgetMulMode mode, long N, long Q, long base, PolynomialArithmetic arithmetic){
    std::cout << "============== gadget_rlwe_test (N = " << N << ", Q = "<< Q << ", base: " << base << ") ==================" << std::endl;
  
    int t = 5; 
    PlaintextEncoding encoding(full_domain, t, Q);
    //Sampler rand; 
    std::shared_ptr<Distribution> rand = std::shared_ptr<Distribution>(new StandardUniformIntegerDistribution(0, t)); 
    KeyDistribution rlwe_key_type = ternary;
    std::shared_ptr<RLWEParam> rlwe_par(new RLWEParam(negacyclic, N, Q, arithmetic)); 
    std::shared_ptr<RLWESK> sk = std::shared_ptr<RLWESK>(new RLWESK(rlwe_par, rlwe_key_type, 3.2));  
    //Gadget deter_gadget;
    std::shared_ptr<Gadget> deter_gadget;
    if(mode == deter){
        deter_gadget = std::shared_ptr<Gadget>(new SignedDecompositionGadget(N, Q, base)); 
    }else if(mode == simul){
        deter_gadget = std::shared_ptr<Gadget>(new DiscreteGaussianSamplingGadget(N, Q, base, base+1));  
    }else{
        throw std::logic_error("mode can either be deter or simul.");
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
            std::cout << "Gadget Serialization Test: Fail" << std::endl;   
        }else{
            std::cout << "Gadget Serialization Test: OK" << std::endl;  
        }  
        std::remove("gadget_serialization_test"); 
    }

    
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


    Polynomial m = Polynomial(rlwe_par->size, rlwe_par->coef_modulus);
    m.zeroize();
    Polynomial out = Polynomial(rlwe_par->size, rlwe_par->coef_modulus);
    Polynomial gadget_m = Polynomial(rlwe_par->size, rlwe_par->coef_modulus);
    gadget_m.zeroize();
    gadget_m.coefs[0] = 1;
    Polynomial exp_poly = Polynomial(rlwe_par->size, rlwe_par->coef_modulus);
   
    bool test = true;
    std::cerr << "Gadget Test: " << 0 ;
    for(int i = 0; i < test_num; ++i){
        //rand.uniform_array(m.coefs, N, t); 
        rand->fill_array(m.coefs, N);
        //rand.uniform_array(gadget_m.coefs, N, t); 
        rand->fill_array(gadget_m.coefs, N);
        Utils::mul_mod(exp_poly.coefs, m.coefs, N, gadget_m.coefs, N, N, t, negacyclic);
        std::shared_ptr<RLWECT> ct(sk->encode_and_encrypt(&m, encoding));
        std::shared_ptr<RLWEGadgetCT> g_ct_test = std::static_pointer_cast<RLWEGadgetCT>(std::shared_ptr<GadgetVectorCT>(gadget_sk.gadget_encrypt(&gadget_m)));   
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
        std::cerr << "\rGadget Test: " << i ;
        g_ct->mul(&ct_prod, ct.get()); 
        sk->decrypt(&out, &ct_prod, encoding);
        Utils::array_mod_form(out.coefs, out.coefs, N, t);
        if(!Utils::is_eq_poly(out.coefs, exp_poly.coefs, N)){ 
            std::cerr << "\rFail at: " << i << std::endl;
            std::cerr << "gadget rlwe test: Fail" << std::endl;
            std::cerr << "out: " << Utils::to_string(out.coefs, rlwe_par->size) << std::endl;  
            std::cerr << "exp_poly: " << Utils::to_string(exp_poly.coefs, rlwe_par->size) << std::endl;  
            std::cerr << "m: " << Utils::to_string(m.coefs, rlwe_par->size) << std::endl;  
            test = false;
            break;
        } 
    }
    std::cerr << "\rGadget Test: " << 100 << std::endl; 
    if(test){
        std::cerr << "gadget rlwe test: OK" << std::endl;
    }else{ 
        throw std::logic_error("gadget rlwe test: Fail");
    }    


    test = true;
    std::cerr << "Extended Test: " << 0 ;
    for(int i = 0; i < test_num; ++i){
        //rand.uniform_array(m.coefs, N, t); 
        rand->fill_array(m.coefs, N);
        //rand.uniform_array(gadget_m.coefs, N, t); 
        rand->fill_array(gadget_m.coefs, N);
        Utils::mul_mod(exp_poly.coefs, m.coefs, N, gadget_m.coefs, N, N, t, negacyclic); 
        for(int j = 0; j < N; ++j){
            m.coefs[j] = encoding.encode_message(m.coefs[j]);
        }
        std::shared_ptr<ExtendedRLWECT> ext_ct_test = std::static_pointer_cast<ExtendedRLWECT>(std::shared_ptr<ExtendedPolynomialCT>(gadget_sk.extended_encrypt(&gadget_m)));   
         
        RLWECT ct_prod(rlwe_par);
        std::cerr << "\rExtended Test: " << i ;
        ext_ct_test->mul(&ct_prod, &m); 
        sk->decrypt(&out, &ct_prod, encoding);
        Utils::array_mod_form(out.coefs, out.coefs, N, t);
        if(!Utils::is_eq_poly(out.coefs, exp_poly.coefs, N)){ 
            std::cerr << "\rFail at: " << i << std::endl;
            std::cerr << "Extended rlwe test: Fail" << std::endl;
            std::cerr << "out: " << Utils::to_string(out.coefs, rlwe_par->size) << std::endl;  
            std::cerr << "exp_poly: " << Utils::to_string(exp_poly.coefs, rlwe_par->size) << std::endl;  
            std::cerr << "m: " << Utils::to_string(m.coefs, rlwe_par->size) << std::endl;  
            test = false;
            break;
        } 
    }
    std::cerr << "\rExtended Test: " << 100 << std::endl; 
    if(test){
        std::cerr << "Extended rlwe test: OK" << std::endl;
    }else{ 
        throw std::logic_error("Extended rlwe test: Fail");
    }    


}
  
int main(){

    // RLWE Tests 
    rlwe_test(100, 4096, 288230376151130113, ntt64);
  
    rlwe_test(100, 4096, 1152921504606830593, ntt64);
    rlwe_test(100, 4096, 2305843009213554689, ntt64);
    rlwe_test(100, 4096, 4611686018427322369, ntt64); 
 
    // Gadget RLWE tests 
    gadget_rlwe_basic_test(1, deter, 4096, 288230376151130113, 8, ntt64);

    
    gadget_rlwe_test(100, deter, 512, 67104769, 8, ntt64);
 
    gadget_rlwe_test(100, deter, 512, 67104769, 8, double_fft);  
 
  
    //gadget_rlwe_test(100, simul, 512, 67104769, 8, hexl_ntt);

    //gadget_rlwe_test(100, deter, 4096, 35184371884033, hexl_ntt);
    // 50 bit
    //gadget_rlwe_test(100, deter, 4096, 1125899906826241, 8, hexl_ntt);
    // 51 bit
    //gadget_rlwe_test(100, deter, 4096, 2251799813554177, 8, hexl_ntt);



    // 52 bit  
    gadget_rlwe_test(100, deter, 4096, 4503599627149313, 8, ntt64);
    // 53 bit 
    gadget_rlwe_test(100, deter, 4096, 9007199254429697, 8, ntt64);
    // 54 bit 
    gadget_rlwe_test(100, deter, 4096, 18014398509309953, 8, ntt64);

    // 57 bit
    gadget_rlwe_test(100, deter, 4096, 288230376151130113, 8, ntt64);
    // 60 bit
    gadget_rlwe_test(100, deter, 4096, 1152921504606830593, 8, ntt64);
    // 61 bit (May fail actually because we have basis = 8 decomposition, which is 3 bits, giving us 61+3 = 64 bits.)
    gadget_rlwe_test(10, deter, 4096, 2305843009213554689, 4, ntt64);
    // 62 bit
    //gadget_rlwe_test(10, deter, 4096, 4611686018427322369, hexl_ntt);
    // 63 bit
    //gadget_rlwe_test(10, deter, 4096, 9223372036854497281, hexl_ntt);
    
    return 0;
}
