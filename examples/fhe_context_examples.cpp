#include <iostream>
#include <cassert>
#include <chrono>
#include "fhe_deck.h" 


#define assertm(exp, msg) assert(((void)msg, exp))
 
using namespace FHEDeck;

void test_for_default_full_domain_encoding(FHENamedParams param_set){

    std::cout << "=========== test_for_default_full_domain_encoding =============" << std::endl;

    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl;
    
    context.generate_context(param_set); 
    //context.set_default_message_encoding_type(PlaintextEncodingType::full_domain);
    int32_t modulus = context.get_default_plaintext_space();
    PlaintextEncoding encoding = context.get_default_plaintext_encoding();
    encoding.set_type(PlaintextEncodingType::full_domain);
     
    int32_t c1_plain = 1;
    Ciphertext c1  = context.encrypt(c1_plain, encoding);  
    int32_t c2_plain = 2;
    Ciphertext c2  = context.encrypt(2, encoding);  
 
    assertm(context.decrypt(c1) == c1_plain, "Decrypt(c1) == 1");
    std::cout << "Decrypt(c1) == 1: OK" << std::endl; 
    
    assertm(context.decrypt(c2) == c2_plain, "Decrypt(c2) == 2");
    std::cout << "Decrypt(c2) == 2: OK" << std::endl; 
 
    int32_t c3_plain = 0;
    Ciphertext c3 = context.encrypt(c3_plain, encoding);
    c3.add(c3, c1); 
    c3_plain = (c3_plain + c1_plain) % modulus;
    
    assertm(context.decrypt(c3) == c3_plain, "Decrypt(c3+c1) == 1");
    std::cout << "Decrypt(c3+c1): OK" << std::endl;
    c3.add(c3, c2); 
    c3_plain = (c3_plain + c2_plain) % modulus;
    assertm(context.decrypt(c3) == c3_plain, "Decrypt(c3+c1+c2) == 3");
    std::cout << "Decrypt(c3+c1+c2): OK" << std::endl;
    c3.add(c3, c2); 
    c3_plain = (c3_plain + c2_plain) % modulus;
    std::cout << "context.decrypt(c3): " << context.decrypt(c3) << std::endl;
    assertm(context.decrypt(c3) == c3_plain, "Decrypt(c3+c1+c2+c2) == 1");
    std::cout << "Decrypt(c3+c1+c2+c2) OK" << std::endl;
 
    c3.mul(c3, 3); 
    c3_plain = (c3_plain * 3) % modulus;
    assertm(context.decrypt(c3) == c3_plain, "Decrypt((c3+c1+c2+c2) * 3) == 3");
    std::cout << "Decrypt((c3+c1+c2+c2) * 3): OK"  << std::endl; 
 
    std::cout << "Copying to LWE ct objects" << std::endl;
    Ciphertext ct1 = c1;
  
    Ciphertext ct2 = c2;
    assertm(context.decrypt(ct1) == c1_plain, "context.decrypt(&ct1) == 1");
    std::cout << "context.decrypt(&ct1) == 1: OK"  << std::endl;

    assertm(context.decrypt(ct2) == c2_plain, "context.decrypt(&ct2) == 2");
    std::cout << "context.decrypt(&ct2) == 2: OK"  << std::endl;
    Ciphertext ct3 = ct1 + 1;  
    c3_plain = (c1_plain + 1) % modulus;
    assertm(context.decrypt(ct3) == c3_plain, "context.decrypt(&(ct1 + 1)) == 2");
    std::cout << "context.decrypt(&(ct1 + 1)) == 2: OK"  << std::endl;

    ct3 = 1 + ct1;  
    c3_plain = (1 + c1_plain) % modulus;
    assertm(context.decrypt(ct3) == c3_plain, "context.decrypt(&(1+ ct1)) == 2");
    std::cout << "context.decrypt(&(1+ ct1)) == 2: OK"  << std::endl;

    ct3 = ct1 - 2; 
    c3_plain = Utils::integer_mod_form(c1_plain - 2, modulus);
    assertm(context.decrypt(ct3) == c3_plain, "context.decrypt(&(ct1 - 2)) == 3");
    std::cout << "context.decrypt(&(ct1 - 2)) == 3: OK"  << std::endl;

    ct3 = 2 - ct1; 
    c3_plain = Utils::integer_mod_form(2 - c1_plain, modulus);
    assertm(context.decrypt(ct3) == c3_plain, "context.decrypt(&(2 - ct1)) == 1");
    std::cout << "context.decrypt(&(2 - ct1)) == 1: OK"  << std::endl;
 
    ct3 = ct1 * 2; 
    c3_plain = (c1_plain * 2) % modulus;
    assertm(context.decrypt(ct3) == c3_plain, "context.decrypt(&(ct1 * 2)) == 2");
    std::cout << "context.decrypt(&(ct1 * 2)) == 2: "  << std::endl;

    ct3 = 2 * ct1; 
    c3_plain = (2 * c1_plain) % modulus;
    assertm(context.decrypt(ct3) == c3_plain, "context.decrypt(&(2 * ct1)) == 2");
    std::cout << "context.decrypt(&(2 * ct1)) == 2: OK"   << std::endl;

    ct3 = ct1 + ct2; 
    c3_plain = (c1_plain + c2_plain) % modulus;
    assertm(context.decrypt(ct3) == c3_plain, "context.decrypt(&(ct1 + ct2)) == 3");
    std::cout << "context.decrypt(&(ct1 + ct2)) == 3: OK"  << std::endl;

    ct3 = ct2 - ct1; 
    c3_plain = Utils::integer_mod_form(c2_plain - c1_plain, modulus);
    
    assertm(context.decrypt(ct3) == c3_plain, "context.decrypt(&(ct2 - ct1)) == 1");
    std::cout << "context.decrypt(&(ct2 - ct1)) == 1: OK"   << std::endl;

    assertm(context.decrypt(ct1) == c1_plain, "context.decrypt(&ct1) == 1"); 
    std::cout << "context.decrypt(&ct1) == 1: OK" << std::endl;

    ct3 = - ct1; 
    c3_plain = Utils::integer_mod_form(-c1_plain, modulus);
    assertm(context.decrypt(ct3) == c3_plain, "context.decrypt(&(ct3 = - ct1))) == 3"); 
    std::cout << "context.decrypt(&(ct3 = - ct1))) == 3: OK" << std::endl;


    assertm(context.decrypt(ct1) == c1_plain, "context.decrypt(&ct1) == 1"); 
    std::cout << "context.decrypt(&ct1) == 1: OK" << std::endl;
     
    Ciphertext ct4 = ct1;
    int32_t c4_plain = c1_plain;
    assertm(context.decrypt(ct4) == c4_plain, "context.decrypt(&(ct4 = ct1))) == 1"); 
    std::cout << "context.decrypt(&(ct4 = ct1))) == 1: OK"   << std::endl;
    ct4 = ct1;
    c4_plain = c1_plain;
    assertm(context.decrypt(ct4) == c4_plain, "context.decrypt(&(ct4 = ct1))) == 1"); 
    std::cout << "context.decrypt(&(ct4 = ct1))) == 1: OK"   << std::endl; 
    ct4 = ct2;
    c4_plain = c2_plain;
    assertm(context.decrypt(ct4) == c4_plain, "context.decrypt(&(ct4 = ct2))) == 2"); 
    std::cout << "context.decrypt(&(ct4 = ct2))) == 2: OK"   << std::endl;
 
 
    std::vector<Ciphertext> v;
    v.push_back(ct1);
    v.push_back(ct2);

    std::vector<int64_t> scalars;
    scalars.push_back(2);
    scalars.push_back(1);
    int64_t scalar = 3;
    ct4 = context.eval_affine_function(v, scalars, scalar);  

    c4_plain = Utils::integer_mod_form(c1_plain * 2 + c2_plain * 1 + 3, modulus);
    // The outcome should be 3, because (2 * 1 + 1 * 2 + 3) % 4 = 3
    assertm(context.decrypt(ct4) == c4_plain, "context.decrypt(&((2 * 1 + 1 * 2 + 3) % 4 = 3))) == 3"); 
    std::cout << "context.decrypt(&((2 * 1 + 1 * 2 + 3) % 4 = 3))) == 3: OK"   << std::endl; 
  
    auto id = [](int64_t m) -> int64_t {
        return m;
    }; 
  
    HomomorphicAccumulator lut_identity = context.setup_function(id, encoding); 
  
    
    int64_t elapsed = 0;   
    int32_t num_of_evals = 0;
    std::chrono::_V2::system_clock::time_point start;
    std::chrono::_V2::system_clock::time_point stop;

    start = std::chrono::high_resolution_clock::now(); 
    ct4 = context.eval(ct1, lut_identity);  
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;

    c4_plain = c1_plain;
    assertm(context.decrypt(ct4) == c4_plain, "context.decrypt(context.eval_lut(&ct1, lut_identity)) == 1"); 
    std::cout << "context.decrypt(context.eval_lut(&ct1, lut_identity)) == 1: OK"  << std::endl;
 
    auto id_plus = [](int64_t m) -> int64_t {
        return (m+1);
    }; 

    HomomorphicAccumulator lut_id_plus = context.setup_function(id_plus, encoding); 

    start = std::chrono::high_resolution_clock::now(); 
    ct4 = context.eval(ct1, lut_id_plus); 
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;

    c4_plain = Utils::integer_mod_form(id_plus(c1_plain), modulus);
    assertm(context.decrypt(ct4) == c4_plain, "context.decrypt(context.eval_lut(&ct1, lut_id_plus)) == 2"); 
    std::cout << "context.decrypt(context.eval_lut(&ct1, lut_id_plus)) == 2: OK"  << std::endl;
 
    start = std::chrono::high_resolution_clock::now(); 
    ct4 = context.eval(ct4, lut_id_plus);
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;

    c4_plain = Utils::integer_mod_form(id_plus(c4_plain), modulus);
    assertm(context.decrypt(ct4) == c4_plain, "context.decrypt(context.eval_lut(&ct4, lut_id_plus)) == 3"); 
    std::cout << "context.decrypt(context.eval_lut(&ct4, lut_id_plus)) == 3: OK"  << std::endl;

    start = std::chrono::high_resolution_clock::now(); 
    ct4 = context.eval(ct4, lut_id_plus); 
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;

    c4_plain = Utils::integer_mod_form(id_plus(c4_plain), modulus);
    assertm(context.decrypt(ct4) == c4_plain, "context.decrypt(context.eval_lut(&ct4, lut_id_plus)) == 0"); 
    std::cout << "context.decrypt(context.eval_lut(&ct4, lut_id_plus)) == 0: OK"  << std::endl;

    std::function<int64_t(int64_t,int64_t)> fun_msb = [](int64_t m, int64_t t) -> int64_t {
        if(m < t/2){
            return 0;
        }else{
            return 1;
        } 
    }; 
    std::function<int64_t(int64_t)> fun_msb_t = std::bind(fun_msb, std::placeholders::_1, modulus);
    HomomorphicAccumulator lut_fun_msb = context.setup_function(fun_msb_t, encoding); 

    start = std::chrono::high_resolution_clock::now(); 
    ct4 = context.eval(ct1, lut_fun_msb); 
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;

    c4_plain = fun_msb_t(c1_plain);
    assertm(context.decrypt(ct4) == c4_plain, "context.decrypt(context.eval_lut(&ct1, lut_fun_msb)) == 0"); 
    std::cout << "context.decrypt(context.eval_lut(&ct1, lut_fun_msb)) == 0: OK"  << std::endl;
    
    std::cout << "Time elapsed:  " << elapsed << " ms, " << (double)elapsed/1000.0 << " s" << std::endl; 
    std::cout << "Time per eval:  " << (double)elapsed/num_of_evals << " ms, " << ((double)elapsed/num_of_evals)/1000.0 << " s" << std::endl; 
}


void test_for_partial_domain_encoding(FHENamedParams param_set){

    std::cout << "=========== test_for_partial_domain_encoding =============" << std::endl;

    int64_t elapsed = 0;   
    int32_t num_of_evals = 0;
    std::chrono::_V2::system_clock::time_point start;
    std::chrono::_V2::system_clock::time_point stop;

    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl;
    context.generate_context(param_set);
    
    //  The default encoding for this is actually full domain.  
    //context.set_default_message_encoding_type(PlaintextEncodingType::partial_domain); 
    PlaintextEncoding encoding = context.get_default_plaintext_encoding();
    encoding.set_type(PlaintextEncodingType::partial_domain);
 
    #if defined(USE_CEREAL)
    {
        /// Serialize and Deserialize LWEGadgetSK  
        std::ofstream os_glwe_ct("fhe_context_test", std::ios::binary); 
        
        cereal::BinaryOutputArchive oarchive_glwe_ct(os_glwe_ct); 
        oarchive_glwe_ct(context.config->secret_key); 
        os_glwe_ct.close();  
    }
    std::shared_ptr<FHESecretKey> secret_key;
    {
        std::ifstream is_glwe_ct("fhe_context_test", std::ios::binary);
        cereal::BinaryInputArchive iarchive_glwe_ct(is_glwe_ct);  
        iarchive_glwe_ct(secret_key);   
        std::remove("fhe_context_test"); 
    }
    context.config->secret_key = secret_key;
    {
        /// Serialize and Deserialize LWEGadgetSK  
        std::ofstream os_glwe_ct("fhe_context_test", std::ios::binary); 
        cereal::BinaryOutputArchive oarchive_glwe_ct(os_glwe_ct); 
        oarchive_glwe_ct(context.config->eval_key.bootstrap_pk); 
        os_glwe_ct.close();  
    }
    std::shared_ptr<FunctionalBootstrapPublicKey> bootstrap_pk;
    {
        std::ifstream is_glwe_ct("fhe_context_test", std::ios::binary);
        cereal::BinaryInputArchive iarchive_glwe_ct(is_glwe_ct);  
        iarchive_glwe_ct(bootstrap_pk);   
        std::remove("fhe_context_test"); 
    }
    context.config->eval_key.bootstrap_pk = bootstrap_pk;
    {
        std::ofstream os_glwe_ct("fhe_context_test", std::ios::binary); 
        cereal::BinaryOutputArchive oarchive_glwe_ct(os_glwe_ct); 
        oarchive_glwe_ct(context.config->eval_key.boot_acc_builder); 
        os_glwe_ct.close();  
    }
    std::shared_ptr<VectorCTAccumulatorBuilder> boot_acc_builder;
    {
        std::ifstream is_glwe_ct("fhe_context_test", std::ios::binary);
        cereal::BinaryInputArchive iarchive_glwe_ct(is_glwe_ct);  
        iarchive_glwe_ct(boot_acc_builder);   
        std::remove("fhe_context_test"); 
    }
    context.config->eval_key.boot_acc_builder = boot_acc_builder; 

    {
        std::ofstream os_glwe_ct("fhe_context_test", std::ios::binary); 
        cereal::BinaryOutputArchive oarchive_glwe_ct(os_glwe_ct); 
        oarchive_glwe_ct(context.config->eval_key.encrypt_pk); 
        os_glwe_ct.close();  
    }
    std::shared_ptr<LWEPublicKey> encrypt_pk; 
    {
        std::ifstream is_glwe_ct("fhe_context_test", std::ios::binary);
        cereal::BinaryInputArchive iarchive_glwe_ct(is_glwe_ct);  
        iarchive_glwe_ct(encrypt_pk);   
        std::remove("fhe_context_test"); 
    }
    context.config->eval_key.encrypt_pk = encrypt_pk; 
    {
        std::ofstream os_glwe_ct("fhe_context_test", std::ios::binary); 
        cereal::BinaryOutputArchive oarchive_glwe_ct(os_glwe_ct); 
        oarchive_glwe_ct(context.config->eval_key.sanitization_pk); 
        os_glwe_ct.close();  
    }
    std::shared_ptr<SanitizationKey> sanitization_pk;
    {
        std::ifstream is_glwe_ct("fhe_context_test", std::ios::binary);
        cereal::BinaryInputArchive iarchive_glwe_ct(is_glwe_ct);  
        iarchive_glwe_ct(sanitization_pk);   
        std::remove("fhe_context_test"); 
    }
    context.config->eval_key.sanitization_pk = sanitization_pk; 
    #endif
 

    Ciphertext c0  = context.encrypt(0, encoding);  
    Ciphertext c1  = context.encrypt(1, encoding);    
    Ciphertext c2  = context.encrypt(2, encoding);  
    Ciphertext c3  = context.encrypt(3, encoding);  
   
    assertm(context.decrypt(c0) == 0, "Decrypt(c0) == 0");
    std::cout << "Decrypt(c0) == 0: OK" << std::endl; 
    assertm(context.decrypt(c1) == 1, "Decrypt(c1) == 1");
    std::cout << "Decrypt(c1) == 1: OK" << std::endl; 
    assertm(context.decrypt(c2) == 2, "Decrypt(c2) == 2");
    std::cout << "Decrypt(c2) == 2: OK" << std::endl; 
    assertm(context.decrypt(c3) == 3, "Decrypt(c3) == 3");
    std::cout << "Decrypt(c3) == 3: OK" << std::endl; 
 

    auto fun_ham = [](int64_t m) -> int64_t {
        switch(m){
            case 0: 
                return 0;
                break;
            case 1: 
                return 1; 
                break;
            case 2: 
                return 1;   
                break; 
            case 3: 
                return 2;  
            default:
                return 0;
        }
    }; 
     
    std::cout << "genrate_lut" << std::endl;
    HomomorphicAccumulator lut_fun_ham = context.setup_function(fun_ham, encoding); 

     
    Ciphertext ct4;
    start = std::chrono::high_resolution_clock::now(); 
    ct4 = context.eval(c0, lut_fun_ham);
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    std::cout << "context.decrypt(&ct4): " << context.decrypt(ct4) << std::endl; 
    assertm(context.decrypt(ct4) == 0, "context.eval_lut(c0, lut_fun_ham) == 0");
    std::cout << "context.eval_lut(c0, lut_fun_ham) == 0: OK" << std::endl;  
 
    start = std::chrono::high_resolution_clock::now(); 
    ct4 = context.eval(c1, lut_fun_ham);
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    
    assertm(context.decrypt(ct4) == 1, "context.eval_lut(c1, lut_fun_ham) == 1");
    std::cout << "context.eval_lut(c1, lut_fun_ham) == 1: OK" << std::endl;  

    start = std::chrono::high_resolution_clock::now(); 
    ct4 = context.eval(c2, lut_fun_ham);
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    assertm(context.decrypt(ct4) == 1, "context.eval_lut(c2, lut_fun_ham) == 1");
    std::cout << "context.eval_lut(c2, lut_fun_ham) == 1: OK" << std::endl;  

    start = std::chrono::high_resolution_clock::now();
    ct4 = context.eval(c3, lut_fun_ham);
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;

    assertm(context.decrypt(ct4) == 2, "context.eval_lut(c3, lut_fun_ham) == 2");
    std::cout << "context.eval_lut(c3, lut_fun_ham) == 2: OK" << std::endl;  



    auto fun_nand = [](int64_t m) -> int64_t {
        switch(m){
            case 0: 
                return 1;
                break;
            case 1: 
                return 1; 
                break;
            case 2: 
                return 1;   
                break; 
            case 3: 
                return 0;  
            default:
                return 2;
        }
    }; 
    HomomorphicAccumulator lut_fun_nand = context.setup_function(fun_nand, encoding); 

    Ciphertext ct0 = context.encrypt(1, encoding);  
    Ciphertext ct1 = context.encrypt(0, encoding);   
    Ciphertext combined = ct0 + (ct1 * 2);  
    start = std::chrono::high_resolution_clock::now(); 
    Ciphertext ct_nand = context.eval(combined, lut_fun_nand);
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    assertm(context.decrypt(ct_nand) == 1, "ct_nand(0, 0) == 1"); 


    ct0 = context.encrypt(1, encoding);  
    ct1 = context.encrypt(0, encoding);  
    combined = ct0 + (ct1 * 2); 
    start = std::chrono::high_resolution_clock::now(); 
    ct_nand = context.eval(combined, lut_fun_nand);
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    assertm(context.decrypt(ct_nand) == 1, "ct_nand(0, 1) == 1");
    std::cout << "ct_nand(0, 1) = 1: OK"  << std::endl; 

    ct0 = context.encrypt(0, encoding);  
    ct1 = context.encrypt(1, encoding);  
    combined = ct0 + (ct1 * 2); 
    start = std::chrono::high_resolution_clock::now(); 
    ct_nand = context.eval(combined, lut_fun_nand);
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    assertm(context.decrypt(ct_nand) == 1, "ct_nand(1, 0) == 1");
    std::cout << "ct_nand(1, 0) = 1: OK"   << std::endl; 


    ct0 = context.encrypt(1, encoding);  
    ct1 = context.encrypt(1, encoding);  
    combined = ct0 + (ct1 * 2); 
    start = std::chrono::high_resolution_clock::now(); 
    ct_nand = context.eval(combined, lut_fun_nand);
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    assertm(context.decrypt(ct_nand) == 0, "ct_nand(1, 1) == 0");
    std::cout << "ct_nand(1, 1) = 0: OK"   << std::endl; 
 
    Ciphertext sanitized = context.sanitize(ct_nand);
    assertm(context.decrypt(sanitized) == 0, "sanitised == 0");
    std::cout << "sanitized = ct_nand = 0: OK"   << std::endl;  

    std::cout << "Time elapsed:  " << elapsed << " ms, " << (double)elapsed/1000.0 << " s" << std::endl; 
    std::cout << "Time per eval:  " << (double)elapsed/num_of_evals << " ms, " << ((double)elapsed/num_of_evals)/1000.0 << " s" << std::endl; 
}




void test_for_signed_limied_short_int(FHENamedParams param_set){
    
    std::cout << "=========== test_for_signed_limied_short_int =============" << std::endl;

    int64_t elapsed = 0;   
    int32_t num_of_evals = 0;
    std::chrono::_V2::system_clock::time_point start;
    std::chrono::_V2::system_clock::time_point stop;

    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl;
    // NOTE: tfhe_11_NTT can still handle a plaintext space equal to 4, but if you test with tfhe_11_B teh test will most likely fail
    context.generate_context(param_set);
    //context.set_default_message_encoding_type(PlaintextEncodingType::signed_limied_short_int);
    PlaintextEncoding encoding = context.get_default_plaintext_encoding();
    encoding.set_type(PlaintextEncodingType::signed_limied_short_int);
      
    Ciphertext ct0 = context.encrypt(0, encoding);   
    Ciphertext ct1 = context.encrypt(1, encoding); 
    Ciphertext ct2 = context.encrypt(2, encoding);    
    Ciphertext ct3 = context.encrypt(3, encoding); 
     
    Ciphertext mct1 = context.encrypt(-1, encoding); 
    Ciphertext mct2 = context.encrypt(-2, encoding);    
    Ciphertext mct3 = context.encrypt(-3, encoding); 
  
    Ciphertext ct4 = context.encrypt(4, encoding);  
   
    Ciphertext mct4 = context.encrypt(-4, encoding); 

    assertm(context.decrypt(ct0) == 0, "context.decrypt(&ct0) == 0");
    std::cout << "context.decrypt(&ct0) == 0: OK"   << std::endl;
    assertm(context.decrypt(ct1) == 1, "context.decrypt(&ct1) == 1");
    std::cout << "context.decrypt(&ct1) == 1: OK"   << std::endl;
    assertm(context.decrypt(ct2) == 2, "context.decrypt(&ct2) == 2");
    std::cout << "context.decrypt(&ct2) == 2: OK"   << std::endl;
    assertm(context.decrypt(ct3) == 3, "context.decrypt(&ct3) == 3");
    std::cout << "context.decrypt(&ct3) == 3: OK"   << std::endl;
    
    assertm(context.decrypt(mct1) == -1, "context.decrypt(&mct1) == -1");
    std::cout << "context.decrypt(&mct1) == -1: OK"   << std::endl;
    assertm(context.decrypt(mct2) == -2, "context.decrypt(&mct1) == -2");
    std::cout << "context.decrypt(&mct2) == -2: OK"   << std::endl;
    assertm(context.decrypt(mct3) == -3, "context.decrypt(&mct1) == -3");
    std::cout << "context.decrypt(&mct3) == -3: OK"   << std::endl;

 
    std::cout << "Decrypt(ct4): " << context.decrypt(ct4) << std::endl; 
 
    std::cout << "Decrypt(mct4): " << context.decrypt(mct4) << std::endl;
 
    Ciphertext ct_add = ct1 + mct1;
    assertm(context.decrypt(ct_add) == 0, "context.decrypt(&ct1 + mct1) == 0");
    std::cout << "Decrypt(ct_add = ct1 + mct1): OK"  << std::endl; 
    ct_add = ct2 + mct2;
    assertm(context.decrypt(ct_add) == 0, "context.decrypt(&ct_add) == 0");
    std::cout << "Decrypt(ct_add = ct2 + mct2): OK"   << std::endl;  
    ct_add = ct3 + mct3;
    assertm(context.decrypt(ct_add) == 0, "context.decrypt(&ct_add) == 0");
    std::cout << "Decrypt(ct_add = ct3 + mct3): OK"  << std::endl; 
    ct_add = ct1 + mct2;
    assertm(context.decrypt(ct_add) == -1, "context.decrypt(&ct_add) == -1");
    std::cout << "Decrypt(ct_add = ct1 + mct2): OK"  << std::endl; 
    ct_add = ct2 + mct3;
    assertm(context.decrypt(ct_add) == -1, "context.decrypt(&ct_add) == -1");
    std::cout << "Decrypt(ct_add = ct2 + mct3): OK"  << std::endl; 
    ct_add = ct1 + mct3;
    assertm(context.decrypt(ct_add) == -2, "context.decrypt(&ct_add) == -1");
    std::cout << "Decrypt(ct_add = ct1 + mct3): OK"  << std::endl; 
    ct_add = ct3 + mct1;
    assertm(context.decrypt(ct_add) == 2, "context.decrypt(&ct_add) == 2");
    std::cout << "Decrypt(ct_add = ct3 + mct1): OK"  << std::endl; 

  
 
    auto fun_identity = [](int64_t m) -> int64_t {
        return m; 
    };    
   
    HomomorphicAccumulator lut_fun_identity = context.setup_function(fun_identity, encoding);  
   
    Ciphertext ct_id = context.eval(mct1, lut_fun_identity); 
    start = std::chrono::high_resolution_clock::now(); 
    ct_id = context.eval(ct_id, lut_fun_identity);
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    assertm(context.decrypt(ct_id) == -1, "context.eval_lut(&mct1, lut_fun_identity) == -1");
    std::cout << "context.eval_lut(&mct1, lut_fun_identity) == -1: OK"  << std::endl; 

    start = std::chrono::high_resolution_clock::now(); 
    ct_id = context.eval(mct2, lut_fun_identity); 
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    start = std::chrono::high_resolution_clock::now(); 
    ct_id = context.eval(ct_id, lut_fun_identity);
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    assertm(context.decrypt(ct_id) == -2, "context.eval_lut(&mct2, lut_fun_identity) == -2");
    std::cout << "context.eval_lut(&mct2, lut_fun_identity) == -2: OK"  << std::endl;  

    start = std::chrono::high_resolution_clock::now(); 
    ct_id = context.eval(mct3, lut_fun_identity); 
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    start = std::chrono::high_resolution_clock::now(); 
    ct_id = context.eval(ct_id, lut_fun_identity);
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    assertm(context.decrypt(ct_id) == -3, "context.eval_lut(&mct3, lut_fun_identity) == -3");
    std::cout << "context.eval_lut(&mct3, lut_fun_identity) == -3: OK"  << std::endl;  
    start = std::chrono::high_resolution_clock::now(); 
    ct_id = context.eval(ct0, lut_fun_identity); 
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    start = std::chrono::high_resolution_clock::now(); 
    ct_id = context.eval(ct_id, lut_fun_identity);
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    assertm(context.decrypt(ct_id) == 0, "context.eval_lut(&ct0, lut_fun_identity) == 0");
    std::cout << "context.eval_lut(&ct0, lut_fun_identity) == 0: OK"  << std::endl;  
    start = std::chrono::high_resolution_clock::now(); 
    ct_id = context.eval(ct1, lut_fun_identity); 
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    start = std::chrono::high_resolution_clock::now(); 
    ct_id = context.eval(ct_id, lut_fun_identity);
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    assertm(context.decrypt(ct_id) == 1, "context.eval_lut(&ct1, lut_fun_identity) == 1");
    std::cout << "context.eval_lut(&ct1, lut_fun_identity) == 1: OK"  << std::endl;  
    start = std::chrono::high_resolution_clock::now(); 
    ct_id = context.eval(ct2, lut_fun_identity); 
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    start = std::chrono::high_resolution_clock::now(); 
    ct_id = context.eval(ct_id, lut_fun_identity);
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    assertm(context.decrypt(ct_id) == 2, "context.eval_lut(&ct2, lut_fun_identity) == 2");
    std::cout << "context.eval_lut(&ct2, lut_fun_identity) == 2: OK"  << std::endl;  

    start = std::chrono::high_resolution_clock::now(); 
    ct_id = context.eval(ct3, lut_fun_identity); 
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    start = std::chrono::high_resolution_clock::now(); 
    ct_id = context.eval(ct_id, lut_fun_identity);
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    assertm(context.decrypt(ct_id) == 3, "context.eval_lut(&ct3, lut_fun_identity) == 3");
    std::cout << "context.eval_lut(&ct3, lut_fun_identity) == 3: OK"  << std::endl;  

 

    auto fun_relu = [](int64_t m) -> int64_t {
        if(m >= 0){
            return m; 
        }else{
            return 0;
        }
    };  
 
    start = std::chrono::high_resolution_clock::now(); 
    Ciphertext ct_relu = context.eval(ct2, fun_relu);  
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    assertm(context.decrypt(ct_relu) == 2, "context.eval_lut(&ct2, fun_relu) == 2");
    std::cout << "context.eval_lut(&ct2, fun_relu) == 2: OK" << std::endl; 

    start = std::chrono::high_resolution_clock::now(); 
    ct_relu = context.eval(mct3, fun_relu);  
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    assertm(context.decrypt(ct_relu) == 0, "context.eval_lut(&mct3, fun_relu) == 0");
    std::cout << "context.eval_lut(&mct0, fun_relu) == 0: OK" << std::endl; 
   
    start = std::chrono::high_resolution_clock::now(); 
    ct_relu = context.eval(ct1, fun_relu); 
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    assertm(context.decrypt(ct_relu) == 1, "context.eval_lut(&ct1, fun_relu) == 1");
    std::cout << "context.eval_lut(&ct1, fun_relu) == 1: OK" << std::endl; 

    start = std::chrono::high_resolution_clock::now(); 
    ct_relu = context.eval(ct2, fun_relu); 
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    assertm(context.decrypt(ct_relu) == 2, "context.eval_lut(&ct2, fun_relu) == 2");
    std::cout << "context.eval_lut(&ct2, fun_relu) == 2: OK" << std::endl; 

    start = std::chrono::high_resolution_clock::now(); 
    ct_relu = context.eval(ct3, fun_relu); 
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    assertm(context.decrypt(ct_relu) == 3, "context.eval_lut(&ct3, fun_relu) == 3");
    std::cout << "context.eval_lut(&ct3, fun_relu) == 3: OK" << std::endl; 
    
    start = std::chrono::high_resolution_clock::now(); 
    ct_relu = context.eval(mct1, fun_relu); 
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    assertm(context.decrypt(ct_relu) == 0, "context.eval_lut(&mct1, fun_relu) == 0");
    std::cout << "context.eval_lut(&mct1, fun_relu) == 0: OK" << std::endl; 

    start = std::chrono::high_resolution_clock::now(); 
    ct_relu = context.eval(mct2, fun_relu); 
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    assertm(context.decrypt(ct_relu) == 0, "context.eval_lut(&mct2, fun_relu) == 0");
    std::cout << "context.eval_lut(&mct2, fun_relu) == 0: OK" << std::endl; 

    start = std::chrono::high_resolution_clock::now(); 
    ct_relu = context.eval(mct3, fun_relu); 
    stop = std::chrono::high_resolution_clock::now(); 
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    num_of_evals++;
    assertm(context.decrypt(ct_relu) == 0, "context.eval_lut(&mct3, fun_relu) == 0");
    std::cout << "context.eval_lut(&mct3, fun_relu) == 0: OK" << std::endl; 
   
    std::cout << "Time elapsed:  " << elapsed << " ms, " << (double)elapsed/1000.0 << " s" << std::endl; 
    std::cout << "Time per eval:  " << (double)elapsed/num_of_evals << " ms, " << ((double)elapsed/num_of_evals)/1000.0 << " s" << std::endl; 
}
 

void basic_Ciphertext_tests(FHENamedParams param_set){

    std::cout << "=========== basic_Ciphertext_tests =============" << std::endl;

    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl;
    context.generate_context(param_set);
    
    std::cout << "Encrypt..." << std::endl;
    std::cout << "Testing: lwe_ct c1  = context.encrypt_temp(1);  " << std::endl;

    Ciphertext c1  = context.encrypt(1);  
 
    assertm(context.decrypt(c1) == 1, "Decrypt(c1) == 1");
    std::cout << "context.decrypt(&c1) == 1: OK" << std::endl; 
      
    std::cout << "Testing: lwe_ct::lwe_ct(lwe_ct &c)" << std::endl;
    Ciphertext c2  = c1;   
    assertm(context.decrypt(c2) == 1, "Decrypt(c2) == 1");
    std::cout << "context.decrypt(&c2) == 1: OK" << std::endl; 
 
    std::cout << "Testing: lwe_ct& lwe_ct::operator=(const lwe_ct other)" << std::endl;
    c1 = c2;
    assertm(context.decrypt(c1) == 1, "Decrypt(c1) == 1");
    std::cout << "context.decrypt(&c1) == 1: OK" << std::endl;  
}



void amortized_full_domain_bootstrap_test(FHENamedParams param_set){
    std::cout << "=========== amortized_full_domain_bootstrap_test =============" << std::endl;


    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl; 
    context.generate_context(param_set); 
    //context.set_default_message_encoding_type(PlaintextEncodingType::full_domain);
    PlaintextEncoding encoding = context.get_default_plaintext_encoding();
    encoding.set_type(PlaintextEncodingType::full_domain);

    auto id = [](int64_t m) -> int64_t {
        return m;
    }; 
  
    HomomorphicAccumulator lut_identity = context.setup_function(id, encoding); 

    std::vector<HomomorphicAccumulator> luts;
    luts.push_back(lut_identity);
    luts.push_back(lut_identity);
 
    Ciphertext ct1 = context.encrypt_public(1, encoding); 

    std::vector<Ciphertext> out_cts = context.eval(ct1, luts);

    std::cout << "context.decrypt(&out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    assertm(context.decrypt(out_cts[0]) == 1, "context.decrypt(context.eval_lut(&out_cts[0], lut_identity)) == 1"); 
    std::cout << "context.decrypt(context.eval_lut(&out_cts[0], lut_identity)) == 1: OK"  << std::endl;

    std::cout << "context.decrypt(&out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    assertm(context.decrypt(out_cts[1]) == 1, "context.decrypt(context.eval_lut(&out_cts[1], lut_identity)) == 1"); 
    std::cout << "context.decrypt(context.eval_lut(&out_cts[1], lut_identity)) == 1: OK"  << std::endl;
 
    out_cts = context.eval(ct1, luts);

    std::cout << "context.decrypt(&out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    assertm(context.decrypt(out_cts[0]) == 1, "context.decrypt(context.eval_lut(&out_cts[0], lut_identity)) == 1"); 
    std::cout << "context.decrypt(context.eval_lut(&out_cts[0], lut_identity)) == 1: OK"  << std::endl;

    std::cout << "context.decrypt(&out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    assertm(context.decrypt(out_cts[1]) == 1, "context.decrypt(context.eval_lut(&out_cts[1], lut_identity)) == 1"); 
    std::cout << "context.decrypt(context.eval_lut(&out_cts[1], lut_identity)) == 1: OK"  << std::endl;
 

    auto first_bit = [](int64_t m) -> int64_t {
        return m % 2;
    };  
  
    auto second_bit = [](int64_t m) -> int64_t {
        return (m % 4)/2;
    };  

    auto third_bit = [](int64_t m) -> int64_t {
        return (m % 8)/4; 
    };  

    std::vector<HomomorphicAccumulator> bit_decomp_luts;
    bit_decomp_luts.push_back(context.setup_function(first_bit, encoding));
    bit_decomp_luts.push_back(context.setup_function(second_bit, encoding));
    bit_decomp_luts.push_back(context.setup_function(third_bit, encoding));

    Ciphertext ct0 = context.encrypt_public(0, encoding);
    Ciphertext ct2 = context.encrypt_public(2, encoding);
    Ciphertext ct3 = context.encrypt_public(3, encoding);
    Ciphertext ct4 = context.encrypt_public(4, encoding);
    Ciphertext ct5 = context.encrypt_public(5, encoding);
    Ciphertext ct6 = context.encrypt_public(6, encoding);
    Ciphertext ct7 = context.encrypt_public(7, encoding);


    out_cts = context.eval(ct0, bit_decomp_luts);
    std::cout << "context.decrypt(out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    std::cout << "context.decrypt(out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    std::cout << "context.decrypt(out_cts[2]): " << context.decrypt(out_cts[2]) << std::endl;
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 0); 
    std::cout << "Test Bin Decomp 0: OK" << std::endl;

    out_cts = context.eval(ct1, bit_decomp_luts);
    std::cout << "context.decrypt(out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    std::cout << "context.decrypt(out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    std::cout << "context.decrypt(out_cts[2]): " << context.decrypt(out_cts[2]) << std::endl;
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 0); 
    std::cout << "Test Bin Decomp 1: OK" << std::endl;

    out_cts = context.eval(ct2, bit_decomp_luts);
    std::cout << "context.decrypt(out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    std::cout << "context.decrypt(out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    std::cout << "context.decrypt(out_cts[2]): " << context.decrypt(out_cts[2]) << std::endl;
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 0); 
    std::cout << "Test Bin Decomp 2: OK" << std::endl;

    out_cts = context.eval(ct3, bit_decomp_luts);
    std::cout << "context.decrypt(out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    std::cout << "context.decrypt(out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    std::cout << "context.decrypt(out_cts[2]): " << context.decrypt(out_cts[2]) << std::endl;
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 0); 
    std::cout << "Test Bin Decomp 3: OK" << std::endl;

    out_cts = context.eval(ct4, bit_decomp_luts);
    std::cout << "context.decrypt(out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    std::cout << "context.decrypt(out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    std::cout << "context.decrypt(out_cts[2]): " << context.decrypt(out_cts[2]) << std::endl;
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 1); 
    std::cout << "Test Bin Decomp 4: OK" << std::endl;


    out_cts = context.eval(ct5, bit_decomp_luts);
    std::cout << "context.decrypt(out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    std::cout << "context.decrypt(out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    std::cout << "context.decrypt(out_cts[2]): " << context.decrypt(out_cts[2]) << std::endl;
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 1); 
    std::cout << "Test Bin Decomp 5: OK" << std::endl;


    out_cts = context.eval(ct6, bit_decomp_luts);
    std::cout << "context.decrypt(out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    std::cout << "context.decrypt(out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    std::cout << "context.decrypt(out_cts[2]): " << context.decrypt(out_cts[2]) << std::endl;
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 1); 
    std::cout << "Test Bin Decomp 6: OK" << std::endl;


    out_cts = context.eval(ct7, bit_decomp_luts);
    std::cout << "context.decrypt(out_cts[0]): " << context.decrypt(out_cts[0]) << std::endl;
    std::cout << "context.decrypt(out_cts[1]): " << context.decrypt(out_cts[1]) << std::endl;
    std::cout << "context.decrypt(out_cts[2]): " << context.decrypt(out_cts[2]) << std::endl;
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 1); 
    std::cout << "Test Bin Decomp 7: OK" << std::endl;

}
 
void amortized_partial_domain_bootstrap_test(FHENamedParams param_set){
    std::cout << "=========== amortized_11_partial_domain_bootstrap_test =============" << std::endl;
 
    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl;
    context.generate_context(param_set);
    //context.set_default_message_encoding_type(PlaintextEncodingType::partial_domain); 
    PlaintextEncoding encoding = context.get_default_plaintext_encoding();
    encoding.set_type(PlaintextEncodingType::partial_domain);
  
    auto first_bit = [](int64_t m) -> int64_t {
        return m % 2;
    };  
  
    auto second_bit = [](int64_t m) -> int64_t {
        return (m % 4)/2;
    };  

    auto third_bit = [](int64_t m) -> int64_t {
        return (m % 8)/4; 
    };  

    std::vector<HomomorphicAccumulator> bit_decomp_luts;
    bit_decomp_luts.push_back(context.setup_function(first_bit, encoding));
    bit_decomp_luts.push_back(context.setup_function(second_bit, encoding));
    bit_decomp_luts.push_back(context.setup_function(third_bit, encoding));

    Ciphertext ct0 = context.encrypt_public(0, encoding); 
    Ciphertext ct1 = context.encrypt_public(1, encoding); 
    Ciphertext ct2 = context.encrypt_public(2, encoding);
    Ciphertext ct3 = context.encrypt_public(3, encoding);
    Ciphertext ct4 = context.encrypt_public(4, encoding);
    Ciphertext ct5 = context.encrypt_public(5, encoding);
    Ciphertext ct6 = context.encrypt_public(6, encoding);
    Ciphertext ct7 = context.encrypt_public(7, encoding);


    std::vector<Ciphertext> out_cts = context.eval(ct0, bit_decomp_luts);
 

    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 0); 
    std::cout << "Test Bin Decomp 0: OK" << std::endl;

    out_cts = context.eval(ct1, bit_decomp_luts);
  
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 0); 
    std::cout << "Test Bin Decomp 1: OK" << std::endl;
 
    out_cts = context.eval(ct2, bit_decomp_luts);
 
      
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 0); 
    std::cout << "Test Bin Decomp 2: OK" << std::endl;

    out_cts = context.eval(ct3, bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 0); 
    std::cout << "Test Bin Decomp 3: OK" << std::endl;

    out_cts = context.eval(ct4, bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 1); 
    std::cout << "Test Bin Decomp 4: OK" << std::endl;


    out_cts = context.eval(ct5, bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 1); 
    std::cout << "Test Bin Decomp 5: OK" << std::endl;


    out_cts = context.eval(ct6, bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 1); 
    std::cout << "Test Bin Decomp 6: OK" << std::endl;


    out_cts = context.eval(ct7, bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 1); 
    std::cout << "Test Bin Decomp 7: OK" << std::endl;

}

 

void amortized_12_partial_domain_bootstrap_test(FHENamedParams param_set){
    std::cout << "=========== amortized_12_partial_domain_bootstrap_test =============" << std::endl;
 
    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl;
    context.generate_context(param_set); 
  
    auto first_bit = [](int64_t m) -> int64_t {
        return m % 2;
    };  
  
    auto second_bit = [](int64_t m) -> int64_t {
        return (m % 4)/2;
    };  

    auto third_bit = [](int64_t m) -> int64_t {
        return (m % 8)/4; 
    };  

    auto fourth_bit = [](int64_t m) -> int64_t {
        return (m % 16)/8; 
    };  

    std::vector<HomomorphicAccumulator> bit_decomp_luts;
    bit_decomp_luts.push_back(context.setup_function(first_bit));
    bit_decomp_luts.push_back(context.setup_function(second_bit));
    bit_decomp_luts.push_back(context.setup_function(third_bit));
    bit_decomp_luts.push_back(context.setup_function(fourth_bit));

    Ciphertext ct0 = context.encrypt_public(0); 
    Ciphertext ct1 = context.encrypt_public(1); 
    Ciphertext ct2 = context.encrypt_public(2);
    Ciphertext ct3 = context.encrypt_public(3);
    Ciphertext ct4 = context.encrypt_public(4);
    Ciphertext ct5 = context.encrypt_public(5);
    Ciphertext ct6 = context.encrypt_public(6);
    Ciphertext ct7 = context.encrypt_public(7);
    Ciphertext ct8 = context.encrypt_public(8);
    Ciphertext ct9 = context.encrypt_public(9);
    Ciphertext ct10 = context.encrypt_public(10);
    Ciphertext ct11 = context.encrypt_public(11);
    Ciphertext ct12 = context.encrypt_public(12);
    Ciphertext ct13 = context.encrypt_public(13);
    Ciphertext ct14 = context.encrypt_public(14);
    Ciphertext ct15 = context.encrypt_public(15);


    int64_t elapsed = 0; 
    std::chrono::_V2::system_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::vector<Ciphertext> out_cts = context.eval(ct0, bit_decomp_luts);
    std::chrono::_V2::system_clock::time_point stop = std::chrono::high_resolution_clock::now();
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
  
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 0); 
    assert(context.decrypt(out_cts[3]) == 0); 
    std::cout << "Test Bin Decomp 0: OK" << std::endl;
    std::cout << "Time elapsed:  " << elapsed << "ms" << std::endl; 
  
    out_cts = context.eval(ct1, bit_decomp_luts); 
     
    

    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 0); 
    assert(context.decrypt(out_cts[3]) == 0); 
    std::cout << "Test Bin Decomp 1: OK" << std::endl;
 
    out_cts = context.eval(ct2, bit_decomp_luts); 

      
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 0); 
    assert(context.decrypt(out_cts[3]) == 0); 
    std::cout << "Test Bin Decomp 2: OK" << std::endl;

    out_cts = context.eval(ct3, bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 0); 
    assert(context.decrypt(out_cts[3]) == 0); 
    std::cout << "Test Bin Decomp 3: OK" << std::endl;

    out_cts = context.eval(ct4, bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 1); 
    assert(context.decrypt(out_cts[3]) == 0); 
    std::cout << "Test Bin Decomp 4: OK" << std::endl;


    out_cts = context.eval(ct5, bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 1); 
    assert(context.decrypt(out_cts[3]) == 0); 
    std::cout << "Test Bin Decomp 5: OK" << std::endl;


    out_cts = context.eval(ct6, bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 1); 
    assert(context.decrypt(out_cts[3]) == 0); 
    std::cout << "Test Bin Decomp 6: OK" << std::endl;


    out_cts = context.eval(ct7, bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 1); 
    assert(context.decrypt(out_cts[3]) == 0); 
    std::cout << "Test Bin Decomp 7: OK" << std::endl;


    out_cts = context.eval(ct8, bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 0); 
    assert(context.decrypt(out_cts[3]) == 1); 
    std::cout << "Test Bin Decomp 8: OK" << std::endl;


    out_cts = context.eval(ct9, bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 0); 
    assert(context.decrypt(out_cts[3]) == 1); 
    std::cout << "Test Bin Decomp 9: OK" << std::endl;


    out_cts = context.eval(ct10, bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 0); 
    assert(context.decrypt(out_cts[3]) == 1); 
    std::cout << "Test Bin Decomp 10: OK" << std::endl;


    out_cts = context.eval(ct11, bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 0); 
    assert(context.decrypt(out_cts[3]) == 1); 
    std::cout << "Test Bin Decomp 11: OK" << std::endl;


    out_cts = context.eval(ct12, bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 1); 
    assert(context.decrypt(out_cts[3]) == 1); 
    std::cout << "Test Bin Decomp 12: OK" << std::endl;


    out_cts = context.eval(ct13, bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 0); 
    assert(context.decrypt(out_cts[2]) == 1); 
    assert(context.decrypt(out_cts[3]) == 1); 
    std::cout << "Test Bin Decomp 13: OK" << std::endl;


    out_cts = context.eval(ct14, bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 0); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 1); 
    assert(context.decrypt(out_cts[3]) == 1); 
    std::cout << "Test Bin Decomp 14: OK" << std::endl;


    out_cts = context.eval(ct15, bit_decomp_luts);
    assert(context.decrypt(out_cts[0]) == 1); 
    assert(context.decrypt(out_cts[1]) == 1); 
    assert(context.decrypt(out_cts[2]) == 1); 
    assert(context.decrypt(out_cts[3]) == 1); 
    std::cout << "Test Bin Decomp 15: OK" << std::endl;

}




void serialization_test(){
    std::cout << "=========== serialization_test =============" << std::endl;

    FHEContext first_context; 
    std::cout << "Generate Keys..." << std::endl;
    try{
        
        first_context.generate_context(FHENamedParams::tfhe_11_NTT); 
        std::cout << "Save Secret Key" << std::endl; 
        first_context.save_secret_key("z_sk.cereal"); 
        std::cout << "Save Public Key" << std::endl;
        first_context.save_public_key("z_pk.cereal");
    
        FHEContext context; 
        std::cout << "Load secret Key..." << std::endl; 
        context.load_secret_key("z_sk.cereal"); 
        std::cout << "Load Public Key..." << std::endl; 
        context.load_public_key("z_pk.cereal");
        std::cout << "Delete The Files..." << std::endl; 
        std::remove("z_sk.cereal"); 
        std::remove("z_pk.cereal"); 


        Ciphertext ct0 = context.encrypt_public(1);   
        assert(context.decrypt(ct0) == 1);
        
    
        auto id_0 = [](int64_t m, int64_t t) -> int64_t {
            return m % t;
        }; 
        std::function<int64_t(int64_t)> id = std::bind(id_0, std::placeholders::_1, context.get_default_plaintext_space());
        ct0 = context.eval(ct0, id);  
    
        context.save_Ciphertext("z_ct.cereal", ct0);  
        Ciphertext ct_out = context.load_Ciphertext("z_ct.cereal"); 
        assert(context.decrypt(ct_out) == 1);
        std::cout << "Test Eval-Lut/Save and Load Ciphertext: OK" << std::endl;
        
        std::ofstream os("z_rlwe_ct.cereal", std::ios::binary);
        os << ct_out; 
        os.close();
        Ciphertext ct_from_stream = context.load_Ciphertext("z_rlwe_ct.cereal");
        assert(context.decrypt(ct_from_stream) == 1);
        std::cout << "Test Writa and Save from Stream: OK" << std::endl;

        std::remove("z_ct.cereal"); 
        std::remove("z_rlwe_ct.cereal");  
    }catch (std::logic_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}


void test_full_change_plaintext_space(FHENamedParams param_set){
    std::cout << "=========== test_full_change_plaintext  =============" << std::endl;
    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl; 
    context.generate_context(param_set); 
    //context.set_default_message_encoding_type(PlaintextEncodingType::full_domain); 
     
    int modulus_1 = 7;
    int modulus_2 = 13; 
    PlaintextEncoding encoding_1 = context.get_default_plaintext_encoding();
    encoding_1.set_type(PlaintextEncodingType::full_domain);
    encoding_1.set_plaintext_space(modulus_1);
    PlaintextEncoding encoding_2 = encoding_1;
    encoding_2.set_plaintext_space(modulus_2);
    
    Ciphertext ct_in  = context.encrypt(2, encoding_1); 
    
    assert(context.decrypt(ct_in) == 2);
    std::cout << "context.decrypt(ct_in) == 2: OK "   << std::endl; 
    assert(ct_in.encoding.get_plaintext_space() == modulus_1);
    std::cout << "ct_in.encoding.get_plaintext_space() == modulus_1: OK "   << std::endl;
    assert(ct_in.encoding.get_type() == PlaintextEncodingType::full_domain);
    std::cout << "ct_in.encoding.get_type() == PlaintextEncodingType::full_domain: OK "  << std::endl;

    auto id = [](int64_t m) -> int64_t {
        return m;
    }; 


    ct_in = context.eval(ct_in, id);  

    assert(context.decrypt(ct_in) == 2);
    std::cout << "context.decrypt(ct_in) == 2: OK "   << std::endl; 
    assert(ct_in.encoding.get_plaintext_space() == modulus_1);
    std::cout << "ct_in.encoding.get_plaintext_space() == modulus_1: OK "   << std::endl;
    assert(ct_in.encoding.get_type() == PlaintextEncodingType::full_domain);
    std::cout << "ct_in.encoding.get_type() == PlaintextEncodingType::full_domain: OK "  << std::endl;
 

    std::function<int64_t(int64_t)> fun_add = [](int64_t m) -> int64_t {
        return (m+8)%11;
    }; 
 
    
    assert(encoding_1.get_plaintext_space() == modulus_1);
    std::cout << "encoding_1.get_plaintext_space() == modulus_1: OK "   << std::endl; 
    assert(encoding_1.get_type() == PlaintextEncodingType::full_domain); 
    std::cout << "encoding_1.get_type() == PlaintextEncodingType::full_domain: OK "   << std::endl; 

    assert(encoding_2.get_plaintext_space() == modulus_2);
    std::cout << "encoding_2.get_plaintext_space() == modulus_1: OK "   << std::endl; 
    assert(encoding_2.get_type() == PlaintextEncodingType::full_domain); 
    std::cout << "encoding_2.get_type() == PlaintextEncodingType::full_domain: OK "   << std::endl; 
 

    HomomorphicAccumulator lut_fun_add = context.setup_function(fun_add, encoding_1, encoding_2); 
    Ciphertext ct_out = context.eval(ct_in, lut_fun_add);
  
    assert(ct_out.encoding.get_plaintext_space()  == modulus_2);
    std::cout << "ct_out.encoding.get_plaintext_space()  == modulus_1: OK "   << std::endl; 
    assert(ct_out.encoding.get_type() == PlaintextEncodingType::full_domain); 
    std::cout << "ct_out.encoding.get_type() == PlaintextEncodingType::full_domain: OK "   << std::endl; 
    assert(context.decrypt(ct_out) == 10);
    std::cout << "ct_out.encoding.get_plaintext_space() == modulus_1: OK "   << std::endl; 
}




void test_full_change_plaintext_space_amortized(FHENamedParams param_set){
    std::cout << "=========== test_full_change_plaintext_space_amortized =============" << std::endl;
    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl; 
    context.generate_context(param_set); 
    //context.set_default_message_encoding_type(PlaintextEncodingType::full_domain); 

    int modulus_1 = 7;
    int modulus_2 = 13; 
    PlaintextEncoding encoding_1 = context.get_default_plaintext_encoding();
    encoding_1.set_type(PlaintextEncodingType::full_domain);
    encoding_1.set_plaintext_space(modulus_1);
    PlaintextEncoding encoding_2 = encoding_1;
    encoding_2.set_plaintext_space(modulus_2);
    
    Ciphertext ct_in  = context.encrypt(2, encoding_1); 
    
    assert(context.decrypt(ct_in) == 2);
    std::cout << "context.decrypt(ct_in) == 2: OK "   << std::endl; 
    assert(ct_in.encoding.get_plaintext_space() == modulus_1);
    std::cout << "ct_in.encoding.get_plaintext_space() == modulus_1: OK "   << std::endl;
    assert(ct_in.encoding.get_type() == PlaintextEncodingType::full_domain);
    std::cout << "ct_in.encoding.get_type() == PlaintextEncodingType::full_domain: OK "  << std::endl;

    auto id = [](int64_t m) -> int64_t {
        return m;
    }; 

    std::vector<HomomorphicAccumulator> id_luts;
    id_luts.push_back(context.setup_function(id, ct_in.encoding, ct_in.encoding));
    id_luts.push_back(context.setup_function(id, ct_in.encoding, ct_in.encoding));
    
    /// TODO: Actually I need to check perhaps whether LUT where build with the same encoding as the input ciphertext for eval.
    /// If not, then need to throw an exeption, with instruction what to do, because its not always possible to recode a rotation poly to a different encoding.
    /// Well general problem now, because tthe HomomorphicAccumulator doesn't have a copy of a encoding...
    /// What options are there:
    /// 1) I just give the encoding copies, to the HomomorphicAccumulator. Then if input or output encodings don't work, then I throw an exception.
    /// 2) I only have setup functions that take input and output encoding explicitely (make the library harder to use if we have a non-trivial case)
    /// OK. I guess I will go with option 1. What bothers mee a bit, is the we cannot reuse LUTs for different encodings.
    /// But if I want flexibility then I can just pass a vector of functions, and generate the LUTs on the fly.
    std::vector<Ciphertext> cts = context.eval(ct_in, id_luts);  

    for(Ciphertext ct: cts){ 
        assert(ct.encoding.get_type() == PlaintextEncodingType::full_domain);
        std::cout << "ct.encoding.get_type() == PlaintextEncodingType::full_domain: OK "  << std::endl; 
        assert(ct.encoding.get_plaintext_space() == modulus_1);
        std::cout << "ct.encoding.get_plaintext_space() == modulus_1: OK "   << std::endl;
        assert(context.decrypt(ct) == 2);
        std::cout << "context.decrypt(ct_in) == 2: OK "   << std::endl; 
    } 
  
    //PlaintextEncoding encoding_1 = ct_in.encoding;
    //PlaintextEncoding encoding_2 = encoding_1;
    //encoding_2.set_plaintext_space(modulus_2);
    
    assert(encoding_1.get_plaintext_space() == modulus_1);
    std::cout << "encoding_1.get_plaintext_space() == modulus_1: OK "   << std::endl; 
    assert(encoding_1.get_type() == PlaintextEncodingType::full_domain); 
    std::cout << "encoding_1.get_type() == PlaintextEncodingType::full_domain: OK "   << std::endl; 

    assert(encoding_2.get_plaintext_space() == modulus_2);
    std::cout << "encoding_2.get_plaintext_space() == modulus_1: OK "   << std::endl; 
    assert(encoding_2.get_type() == PlaintextEncodingType::full_domain); 
    std::cout << "encoding_2.get_type() == PlaintextEncodingType::full_domain: OK "   << std::endl; 
 
    
    std::function<int64_t(int64_t)> fun_add = [](int64_t m) -> int64_t {
        return (m+8)%11;
    }; 

    std::vector<HomomorphicAccumulator> fun_luts;
    fun_luts.push_back(context.setup_function(fun_add, encoding_1, encoding_2));
    fun_luts.push_back(context.setup_function(fun_add, encoding_1, encoding_2));

    //HomomorphicAccumulator lut_fun_add = context.setup_function(fun_add, encoding_1, encoding_2); 
    std::vector<Ciphertext> ct_outs = context.eval(ct_in, fun_luts);
  
    for(Ciphertext ct_out: ct_outs){
        assert(ct_out.encoding.get_plaintext_space()  == modulus_2);
        std::cout << "ct_out.encoding.get_plaintext_space()  == modulus_1: OK "   << std::endl; 
        assert(ct_out.encoding.get_type() == PlaintextEncodingType::full_domain); 
        std::cout << "ct_out.encoding.get_type() == PlaintextEncodingType::full_domain: OK "   << std::endl; 
        assert(context.decrypt(ct_out) == 10);
        std::cout << "ct_out.encoding.get_plaintext_space() == modulus_1: OK "   << std::endl; 
    } 
}




void test_full_fdfb(FHENamedParams param_set){
    std::cout << "=========== test_full_fdfb  =============" << std::endl;
    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl; 
    context.generate_context(param_set); 

    int32_t modulus = 7; 
    int32_t input = 1;
 
    PlaintextEncoding encoding = context.get_default_plaintext_encoding();
    encoding.set_type(PlaintextEncodingType::full_domain);
    encoding.set_plaintext_space(modulus);

    
    auto times_in_two_and_square = [](int32_t m, int32_t modulus) -> int32_t{
        m = Utils::integer_mod_form(m * m, modulus);
        return Utils::integer_mod_form(m * Utils::mod_inv(4, modulus), modulus);
    }; 
    std::function<int64_t(int64_t)> function = std::bind(times_in_two_and_square, std::placeholders::_1, modulus);
    HomomorphicAccumulator acc = context.setup_function(function, encoding);

    Ciphertext ct_in  = context.encrypt(input, encoding); 
    
    Ciphertext ct_out = context.eval(ct_in, acc);
    if(context.decrypt(ct_out) == times_in_two_and_square(input, modulus)){
        std::cout << "Test Full Domain Function Bootstrapping: OK" << std::endl;
    }else{
        std::cout << "Test Full Domain Function Bootstrapping: Fail" << std::endl;
        std::cout << "Should be: " << times_in_two_and_square(input, modulus) << std::endl;
        std::cout << "Is: " << context.decrypt(ct_out) << std::endl;
    } 
}






int main(){  
  
    /*
   basic_Ciphertext_tests(FHENamedParams::tfhe_11_NTT);
 
   test_for_partial_domain_encoding(FHENamedParams::tfhe_11_NTT);
 
   test_for_partial_domain_encoding(FHENamedParams::tfhe_11_NTT_flood);
 
    test_for_signed_limied_short_int(FHENamedParams::tfhe_11_NTT);
 
    test_for_default_full_domain_encoding(FHENamedParams::tfhe_11_NTT);

    test_for_default_full_domain_encoding(FHENamedParams::tfhe_11_NTT_amortized);

    test_for_default_full_domain_encoding(FHENamedParams::tfhe_12_NTT_amortized);
    
    test_for_default_full_domain_encoding(FHENamedParams::ntrunium_12_NTT);
     
    amortized_partial_domain_bootstrap_test(FHENamedParams::tfhe_11_NTT_amortized);
 
    amortized_12_partial_domain_bootstrap_test(FHENamedParams::tfhe_12_NTT_amortized); 
   
    test_for_default_full_domain_encoding(FHENamedParams::tfhe_11_KS);
    
    amortized_full_domain_bootstrap_test(FHENamedParams::tfhe_11_KS_amortized); 
    
    amortized_partial_domain_bootstrap_test(FHENamedParams::tfhe_11_NTT_amortized);

    amortized_full_domain_bootstrap_test(FHENamedParams::tfhe_11_NTT_amortized); 

    serialization_test();  

    test_for_default_full_domain_encoding(FHENamedParams::tfhe_11_KS);
     
    amortized_full_domain_bootstrap_test(FHENamedParams::tfhe_11_KS_amortized); 

    */
    //test_full_change_plaintext_space(FHENamedParams::tfhe_11_NTT);

    //test_full_change_plaintext_space(FHENamedParams::tfhe_11_NTT_amortized);

    //test_full_change_plaintext_space(FHENamedParams::tfhe_11_KS);

    //test_full_change_plaintext_space(FHENamedParams::tfhe_11_KS_amortized); 

    //test_full_change_plaintext_space_amortized(FHENamedParams::tfhe_11_NTT_amortized);

    //test_full_change_plaintext_space_amortized(FHENamedParams::tfhe_11_KS_amortized);
     
   test_full_fdfb(FHENamedParams::tfhe_11_KS);
   test_full_fdfb(FHENamedParams::tfhe_11_NTT);
}
