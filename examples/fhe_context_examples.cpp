#include <iostream>
#include "fhe_context.h" 
#include <cassert>
#define assertm(exp, msg) assert(((void)msg, exp))
 
using namespace fhe_deck;

void test_for_default_full_domain_encoding(FHENamedParams param_set){

    std::cout << "=========== test_for_default_full_domain_encoding =============" << std::endl;

    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl;
    
    context.generate_context(param_set); 

    
    std::cout << "Encrypt..." << std::endl;
    Ciphertext c1  = context.encrypt(1);  
 
    std::cout << "Encrypt..." << std::endl;
    Ciphertext c2  = context.encrypt(2);  

    std::cout << "Decrypt..." << std::endl;
    assertm(context.decrypt(&c1) == 1, "Decrypt(c1) == 1");
    std::cout << "Decrypt(c1) == 1: OK" << std::endl; 
    
    assertm(context.decrypt(&c2) == 2, "Decrypt(c2) == 2");
    std::cout << "Decrypt(c2) == 2: OK" << std::endl; 
 
     
    Ciphertext c3 = context.encrypt(0);
    c3.add(&c1); 
    
    assertm(context.decrypt(&c3) == 1, "Decrypt(c3+c1) == 1");
    std::cout << "Decrypt(c3+c1): OK" << std::endl;
    c3.add(&c2); 
    assertm(context.decrypt(&c3) == 3, "Decrypt(c3+c1+c2) == 3");
    std::cout << "Decrypt(c3+c1+c2): OK" << std::endl;
    c3.add(&c2); 
    assertm(context.decrypt(&c3) == 1, "Decrypt(c3+c1+c2+c2) == 1");
    std::cout << "Decrypt(c3+c1+c2+c2) OK" << std::endl;


    c3.mul(3); 
    assertm(context.decrypt(&c3) == 3, "Decrypt((c3+c1+c2+c2) * 3) == 3");
    std::cout << "Decrypt((c3+c1+c2+c2) * 3): OK"  << std::endl; 
 
    std::cout << "Copying to LWE ct objects" << std::endl;
    Ciphertext ct1 = c1;
 

    Ciphertext ct2 = c2;
    assertm(context.decrypt(&ct1) == 1, "context.decrypt(&ct1) == 1");
    std::cout << "context.decrypt(&ct1) == 1: OK"  << std::endl;

    assertm(context.decrypt(&ct2) == 2, "context.decrypt(&ct2) == 2");
    std::cout << "context.decrypt(&ct2) == 2: OK"  << std::endl;
    Ciphertext ct3 = ct1 + 1;  
    assertm(context.decrypt(&ct3) == 2, "context.decrypt(&(ct1 + 1)) == 2");
    std::cout << "context.decrypt(&(ct1 + 1)) == 2: OK"  << std::endl;

    ct3 = 1 + ct1;  
    assertm(context.decrypt(&ct3) == 2, "context.decrypt(&(1+ ct1)) == 2");
    std::cout << "context.decrypt(&(1+ ct1)) == 2: OK"  << std::endl;

    ct3 = ct1 - 2; 
    assertm(context.decrypt(&ct3) == 3, "context.decrypt(&(ct1 - 2)) == 3");
    std::cout << "context.decrypt(&(ct1 - 2)) == 3: OK"  << std::endl;

    ct3 = 2 - ct1; 
    assertm(context.decrypt(&ct3) == 1, "context.decrypt(&(2 - ct1)) == 1");
    std::cout << "context.decrypt(&(2 - ct1)) == 1: OK"  << std::endl;
 
    ct3 = ct1 * 2; 
    assertm(context.decrypt(&ct3) == 2, "context.decrypt(&(ct1 * 2)) == 2");
    std::cout << "context.decrypt(&(ct1 * 2)) == 2: "  << std::endl;

    ct3 = 2 * ct1; 
    assertm(context.decrypt(&ct3) == 2, "context.decrypt(&(2 * ct1)) == 2");
    std::cout << "context.decrypt(&(2 * ct1)) == 2: OK"   << std::endl;

    ct3 = ct1 + ct2; 
    assertm(context.decrypt(&ct3) == 3, "context.decrypt(&(ct1 + ct2)) == 3");
    std::cout << "context.decrypt(&(ct1 + ct2)) == 3: OK"  << std::endl;

    ct3 = ct2 - ct1; 
    assertm(context.decrypt(&ct3) == 1, "context.decrypt(&(ct2 - ct1)) == 1");
    std::cout << "context.decrypt(&(ct2 - ct1)) == 1: OK"   << std::endl;

    assertm(context.decrypt(&ct1) == 1, "context.decrypt(&ct1) == 1"); 
    std::cout << "context.decrypt(&ct1) == 1: OK" << std::endl;
    ct3 = - ct1; 
    assertm(context.decrypt(&ct3) == 3, "context.decrypt(&(ct3 = - ct1))) == 3"); 
    std::cout << "context.decrypt(&(ct3 = - ct1))) == 3: OK" << std::endl;
    assertm(context.decrypt(&ct1) == 1, "context.decrypt(&ct1) == 1"); 
    std::cout << "context.decrypt(&ct1) == 1: OK" << std::endl;
     
    Ciphertext ct4 = ct1;
    assertm(context.decrypt(&ct4) == 1, "context.decrypt(&(ct4 = ct1))) == 1"); 
    std::cout << "context.decrypt(&(ct4 = ct1))) == 1: OK"   << std::endl;
    ct4 = ct1;
    assertm(context.decrypt(&ct4) == 1, "context.decrypt(&(ct4 = ct1))) == 1"); 
    std::cout << "context.decrypt(&(ct4 = ct1))) == 1: OK"   << std::endl; 
    ct4 = ct2;
    assertm(context.decrypt(&ct4) == 2, "context.decrypt(&(ct4 = ct2))) == 2"); 
    std::cout << "context.decrypt(&(ct4 = ct2))) == 2: OK"   << std::endl;
 
 
    std::vector<Ciphertext> v;
    v.push_back(ct1);
    v.push_back(ct2);

    std::vector<int64_t> scalars;
    scalars.push_back(2);
    scalars.push_back(1);
    int64_t scalar = 3;
    ct4 = context.eval_affine_function(v, scalars, scalar);  
    // The outcome should be 3, because (2 * 1 + 1 * 2 + 3) % 4 = 3
    assertm(context.decrypt(&ct4) == 3, "context.decrypt(&((2 * 1 + 1 * 2 + 3) % 4 = 3))) == 3"); 
    std::cout << "context.decrypt(&((2 * 1 + 1 * 2 + 3) % 4 = 3))) == 3: OK"   << std::endl; 
  
    auto id = [](int64_t m) -> int64_t {
        return m;
    }; 
  
    HomomorphicAccumulator lut_identity = context.genrate_lut(id); 
  
    ct4 = context.eval_lut(&ct1, lut_identity);
    std::cout << "context.decrypt(&ct4): " << context.decrypt(&ct4) << std::endl;
    assertm(context.decrypt(&ct4) == 1, "context.decrypt(context.eval_lut(&ct1, lut_identity)) == 1"); 
    std::cout << "context.decrypt(context.eval_lut(&ct1, lut_identity)) == 1: OK"  << std::endl;
 
    auto id_plus = [](int64_t m) -> int64_t {
        return (m+1);
    }; 

    HomomorphicAccumulator lut_id_plus = context.genrate_lut(id_plus); 
    ct4 = context.eval_lut(&ct1, lut_id_plus);
    assertm(context.decrypt(&ct4) == 2, "context.decrypt(context.eval_lut(&ct1, lut_id_plus)) == 2"); 
    std::cout << "context.decrypt(context.eval_lut(&ct1, lut_id_plus)) == 2: OK"  << std::endl;
 
    ct4 = context.eval_lut(&ct4, lut_id_plus);
    assertm(context.decrypt(&ct4) == 3, "context.decrypt(context.eval_lut(&ct4, lut_id_plus)) == 3"); 
    std::cout << "context.decrypt(context.eval_lut(&ct4, lut_id_plus)) == 3: OK"  << std::endl;

    ct4 = context.eval_lut(&ct4, lut_id_plus);
    assertm(context.decrypt(&ct4) == 0, "context.decrypt(context.eval_lut(&ct4, lut_id_plus)) == 0"); 
    std::cout << "context.decrypt(context.eval_lut(&ct4, lut_id_plus)) == 0: OK"  << std::endl;

    auto fun_msb = [](int64_t m, int64_t t = 5) -> int64_t {
        if(m < t/2){
            return 0;
        }else{
            return 1;
        } 
    }; 
    HomomorphicAccumulator lut_fun_msb = context.genrate_lut(fun_msb); 
    ct4 = context.eval_lut(&ct1, lut_fun_msb);

    assertm(context.decrypt(&ct4) == 0, "context.decrypt(context.eval_lut(&ct1, lut_fun_msb)) == 0"); 
    std::cout << "context.decrypt(context.eval_lut(&ct1, lut_fun_msb)) == 0: OK"  << std::endl;
   
    std::cout << "Done. See you....." << std::endl;
}


void test_for_partial_domain_encoding(FHENamedParams param_set){

    std::cout << "=========== test_for_partial_domain_encoding =============" << std::endl;

    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl;
    context.generate_context(param_set);
    //context.generate_context(FHENamedParams::tfhe_11_NTT);
    //  The default encoding for this is actually full domain.  
    context.set_default_message_encoding_type(partial_domain);
    //context.set_default_plaintext_space(4);


    {
        /// Serialize and Deserialize LWEGadgetSK  
        std::ofstream os_glwe_ct("fhe_context_test", std::ios::binary); 
        cereal::BinaryOutputArchive oarchive_glwe_ct(os_glwe_ct); 
        oarchive_glwe_ct(context.config->secret_key); 
        os_glwe_ct.close();  
    }
    std::shared_ptr<LWESK> secret_key;
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
        oarchive_glwe_ct(context.config->eval_key.accumulator_builder); 
        os_glwe_ct.close();  
    }
    std::shared_ptr<AbstractAccumulatorBuilder> accumulator_builder;
    {
        std::ifstream is_glwe_ct("fhe_context_test", std::ios::binary);
        cereal::BinaryInputArchive iarchive_glwe_ct(is_glwe_ct);  
        iarchive_glwe_ct(accumulator_builder);   
        std::remove("fhe_context_test"); 
    }
    context.config->eval_key.accumulator_builder = accumulator_builder; 

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

 

    Ciphertext c0  = context.encrypt(0);  
    Ciphertext c1  = context.encrypt(1);    
    Ciphertext c2  = context.encrypt(2);  
    Ciphertext c3  = context.encrypt(3);  
   
    assertm(context.decrypt(&c0) == 0, "Decrypt(c0) == 0");
    std::cout << "Decrypt(c0) == 0: OK" << std::endl; 
    assertm(context.decrypt(&c1) == 1, "Decrypt(c1) == 1");
    std::cout << "Decrypt(c1) == 1: OK" << std::endl; 
    assertm(context.decrypt(&c2) == 2, "Decrypt(c2) == 2");
    std::cout << "Decrypt(c2) == 2: OK" << std::endl; 
    assertm(context.decrypt(&c3) == 3, "Decrypt(c3) == 3");
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
    HomomorphicAccumulator lut_fun_ham = context.genrate_lut(fun_ham); 

     
    Ciphertext ct4;
    ct4 = context.eval_lut(&c0, lut_fun_ham);
    std::cout << "context.decrypt(&ct4): " << context.decrypt(&ct4) << std::endl; 
    assertm(context.decrypt(&ct4) == 0, "context.eval_lut(c0, lut_fun_ham) == 0");
    std::cout << "context.eval_lut(c0, lut_fun_ham) == 0: OK" << std::endl;  
 

    ct4 = context.eval_lut(&c1, lut_fun_ham);
    assertm(context.decrypt(&ct4) == 1, "context.eval_lut(c1, lut_fun_ham) == 1");
    std::cout << "context.eval_lut(c1, lut_fun_ham) == 1: OK" << std::endl;  

    ct4 = context.eval_lut(&c2, lut_fun_ham);
    assertm(context.decrypt(&ct4) == 1, "context.eval_lut(c2, lut_fun_ham) == 1");
    std::cout << "context.eval_lut(c2, lut_fun_ham) == 1: OK" << std::endl;  

    ct4 = context.eval_lut(&c3, lut_fun_ham);
    assertm(context.decrypt(&ct4) == 2, "context.eval_lut(c3, lut_fun_ham) == 2");
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
    HomomorphicAccumulator lut_fun_nand = context.genrate_lut(fun_nand); 

    Ciphertext ct0 = context.encrypt(1);  
    Ciphertext ct1 = context.encrypt(0);   
    Ciphertext combined = ct0 + (ct1 * 2);  
    Ciphertext ct_nand = context.eval_lut(&combined, lut_fun_nand);
    assertm(context.decrypt(&ct_nand) == 1, "ct_nand(0, 0) == 1"); 


    ct0 = context.encrypt(1);  
    ct1 = context.encrypt(0);  
    combined = ct0 + (ct1 * 2); 
    ct_nand = context.eval_lut(&combined, lut_fun_nand);
    assertm(context.decrypt(&ct_nand) == 1, "ct_nand(0, 1) == 1");
    std::cout << "ct_nand(0, 1) = 1: OK"  << std::endl; 

    ct0 = context.encrypt(0);  
    ct1 = context.encrypt(1);  
    combined = ct0 + (ct1 * 2); 
    ct_nand = context.eval_lut(&combined, lut_fun_nand);
    assertm(context.decrypt(&ct_nand) == 1, "ct_nand(1, 0) == 1");
    std::cout << "ct_nand(1, 0) = 1: OK"   << std::endl; 


    ct0 = context.encrypt(1);  
    ct1 = context.encrypt(1);  
    combined = ct0 + (ct1 * 2); 
    ct_nand = context.eval_lut(&combined, lut_fun_nand);
    assertm(context.decrypt(&ct_nand) == 0, "ct_nand(1, 1) == 0");
    std::cout << "ct_nand(1, 1) = 0: OK"   << std::endl; 

    Ciphertext sanitized = context.sanitize(&ct_nand);
    assertm(context.decrypt(&sanitized) == 0, "sanitised == 0");
    std::cout << "sanitized = ct_nand = 0: OK"   << std::endl; 
}



void demo(){
    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl;
    context.generate_context(FHENamedParams::tfhe_11_NTT);
    context.set_default_message_encoding_type(signed_limied_short_int);

    Ciphertext c0  = context.encrypt(0);  
    Ciphertext c1  = context.encrypt(1);    
    Ciphertext ct = c0 - c1;

    auto fun_relu = [](int64_t m) -> int64_t {
        if(m >= 0){
            return m; 
        }else{
            return 0;
        }
    };  
    Ciphertext ct_out = context.eval_lut(&ct, fun_relu); 
    std::cout << "decrypt(&ct_out): "  << context.decrypt(&ct_out) << std::endl;

    std::ofstream os("ct_out.cereal", std::ios::binary);
    os << ct_out; 
}

void test_for_signed_limied_short_int(FHENamedParams param_set){
    
    std::cout << "=========== test_for_signed_limied_short_int =============" << std::endl;

    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl;
    // NOTE: tfhe_11_NTT can still handle a plaintext space equal to 4, but if you test with tfhe_11_B teh test will most likely fail
    context.generate_context(param_set);
    context.set_default_message_encoding_type(signed_limied_short_int);
     

    Ciphertext ct0 = context.encrypt(0);   
    Ciphertext ct1 = context.encrypt(1); 
    Ciphertext ct2 = context.encrypt(2);    
    Ciphertext ct3 = context.encrypt(3); 
     
    Ciphertext mct1 = context.encrypt(-1); 
    Ciphertext mct2 = context.encrypt(-2);    
    Ciphertext mct3 = context.encrypt(-3); 



    Ciphertext ct4 = context.encrypt(4);  
   
    Ciphertext mct4 = context.encrypt(-4); 

    assertm(context.decrypt(&ct0) == 0, "context.decrypt(&ct0) == 0");
    std::cout << "context.decrypt(&ct0) == 0: OK"   << std::endl;
    assertm(context.decrypt(&ct1) == 1, "context.decrypt(&ct1) == 1");
    std::cout << "context.decrypt(&ct1) == 1: OK"   << std::endl;
    assertm(context.decrypt(&ct2) == 2, "context.decrypt(&ct2) == 2");
    std::cout << "context.decrypt(&ct2) == 2: OK"   << std::endl;
    assertm(context.decrypt(&ct3) == 3, "context.decrypt(&ct3) == 3");
    std::cout << "context.decrypt(&ct3) == 3: OK"   << std::endl;
    
    assertm(context.decrypt(&mct1) == -1, "context.decrypt(&mct1) == -1");
    std::cout << "context.decrypt(&mct1) == -1: OK"   << std::endl;
    assertm(context.decrypt(&mct2) == -2, "context.decrypt(&mct1) == -2");
    std::cout << "context.decrypt(&mct2) == -2: OK"   << std::endl;
    assertm(context.decrypt(&mct3) == -3, "context.decrypt(&mct1) == -3");
    std::cout << "context.decrypt(&mct3) == -3: OK"   << std::endl;

 
    std::cout << "Decrypt(ct4): " << context.decrypt(&ct4) << std::endl; 
 
    std::cout << "Decrypt(mct4): " << context.decrypt(&mct4) << std::endl;
 
    Ciphertext ct_add = ct1 + mct1;
    assertm(context.decrypt(&ct_add) == 0, "context.decrypt(&ct1 + mct1) == 0");
    std::cout << "Decrypt(ct_add = ct1 + mct1): OK"  << std::endl; 
    ct_add = ct2 + mct2;
    assertm(context.decrypt(&ct_add) == 0, "context.decrypt(&ct_add) == 0");
    std::cout << "Decrypt(ct_add = ct2 + mct2): OK"   << std::endl;  
    ct_add = ct3 + mct3;
    assertm(context.decrypt(&ct_add) == 0, "context.decrypt(&ct_add) == 0");
    std::cout << "Decrypt(ct_add = ct3 + mct3): OK"  << std::endl; 
    ct_add = ct1 + mct2;
    assertm(context.decrypt(&ct_add) == -1, "context.decrypt(&ct_add) == -1");
    std::cout << "Decrypt(ct_add = ct1 + mct2): OK"  << std::endl; 
    ct_add = ct2 + mct3;
    assertm(context.decrypt(&ct_add) == -1, "context.decrypt(&ct_add) == -1");
    std::cout << "Decrypt(ct_add = ct2 + mct3): OK"  << std::endl; 
    ct_add = ct1 + mct3;
    assertm(context.decrypt(&ct_add) == -2, "context.decrypt(&ct_add) == -1");
    std::cout << "Decrypt(ct_add = ct1 + mct3): OK"  << std::endl; 
    ct_add = ct3 + mct1;
    assertm(context.decrypt(&ct_add) == 2, "context.decrypt(&ct_add) == 2");
    std::cout << "Decrypt(ct_add = ct3 + mct1): OK"  << std::endl; 

  
 
    auto fun_identity = [](int64_t m) -> int64_t {
        return m; 
    };    
   
    HomomorphicAccumulator lut_fun_identity = context.genrate_lut(fun_identity);  
 
   
    Ciphertext ct_id = context.eval_lut(&mct1, lut_fun_identity); 
    ct_id = context.eval_lut(&ct_id, lut_fun_identity);
    assertm(context.decrypt(&ct_id) == -1, "context.eval_lut(&mct1, lut_fun_identity) == -1");
    std::cout << "context.eval_lut(&mct1, lut_fun_identity) == -1: OK"  << std::endl; 

    ct_id = context.eval_lut(&mct2, lut_fun_identity); 
    ct_id = context.eval_lut(&ct_id, lut_fun_identity);
    assertm(context.decrypt(&ct_id) == -2, "context.eval_lut(&mct2, lut_fun_identity) == -2");
    std::cout << "context.eval_lut(&mct2, lut_fun_identity) == -2: OK"  << std::endl;  

    ct_id = context.eval_lut(&mct3, lut_fun_identity); 
    ct_id = context.eval_lut(&ct_id, lut_fun_identity);
    assertm(context.decrypt(&ct_id) == -3, "context.eval_lut(&mct3, lut_fun_identity) == -3");
    std::cout << "context.eval_lut(&mct3, lut_fun_identity) == -3: OK"  << std::endl;  

    ct_id = context.eval_lut(&ct0, lut_fun_identity); 
    ct_id = context.eval_lut(&ct_id, lut_fun_identity);
    assertm(context.decrypt(&ct_id) == 0, "context.eval_lut(&ct0, lut_fun_identity) == 0");
    std::cout << "context.eval_lut(&ct0, lut_fun_identity) == 0: OK"  << std::endl;  

    ct_id = context.eval_lut(&ct1, lut_fun_identity); 
    ct_id = context.eval_lut(&ct_id, lut_fun_identity);
    assertm(context.decrypt(&ct_id) == 1, "context.eval_lut(&ct1, lut_fun_identity) == 1");
    std::cout << "context.eval_lut(&ct1, lut_fun_identity) == 1: OK"  << std::endl;  

    ct_id = context.eval_lut(&ct2, lut_fun_identity); 
    ct_id = context.eval_lut(&ct_id, lut_fun_identity);
    assertm(context.decrypt(&ct_id) == 2, "context.eval_lut(&ct2, lut_fun_identity) == 2");
    std::cout << "context.eval_lut(&ct2, lut_fun_identity) == 2: OK"  << std::endl;  


    ct_id = context.eval_lut(&ct3, lut_fun_identity); 
    ct_id = context.eval_lut(&ct_id, lut_fun_identity);
    assertm(context.decrypt(&ct_id) == 3, "context.eval_lut(&ct3, lut_fun_identity) == 3");
    std::cout << "context.eval_lut(&ct3, lut_fun_identity) == 3: OK"  << std::endl;  

 

    auto fun_relu = [](int64_t m) -> int64_t {
        if(m >= 0){
            return m; 
        }else{
            return 0;
        }
    };  
 

    Ciphertext ct_relu = context.eval_lut(&ct2, fun_relu);  
    assertm(context.decrypt(&ct_relu) == 2, "context.eval_lut(&ct2, fun_relu) == 2");
    std::cout << "context.eval_lut(&ct2, fun_relu) == 2: OK" << std::endl; 


    ct_relu = context.eval_lut(&mct3, fun_relu);  
    assertm(context.decrypt(&ct_relu) == 0, "context.eval_lut(&mct3, fun_relu) == 0");
    std::cout << "context.eval_lut(&mct0, fun_relu) == 0: OK" << std::endl; 
   
    ct_relu = context.eval_lut(&ct1, fun_relu); 
    assertm(context.decrypt(&ct_relu) == 1, "context.eval_lut(&ct1, fun_relu) == 1");
    std::cout << "context.eval_lut(&ct1, fun_relu) == 1: OK" << std::endl; 

    ct_relu = context.eval_lut(&ct2, fun_relu); 
    assertm(context.decrypt(&ct_relu) == 2, "context.eval_lut(&ct2, fun_relu) == 2");
    std::cout << "context.eval_lut(&ct2, fun_relu) == 2: OK" << std::endl; 

    ct_relu = context.eval_lut(&ct3, fun_relu); 
    assertm(context.decrypt(&ct_relu) == 3, "context.eval_lut(&ct3, fun_relu) == 3");
    std::cout << "context.eval_lut(&ct3, fun_relu) == 3: OK" << std::endl; 
    
    ct_relu = context.eval_lut(&mct1, fun_relu); 
    assertm(context.decrypt(&ct_relu) == 0, "context.eval_lut(&mct1, fun_relu) == 0");
    std::cout << "context.eval_lut(&mct1, fun_relu) == 0: OK" << std::endl; 


    ct_relu = context.eval_lut(&mct2, fun_relu); 
    assertm(context.decrypt(&ct_relu) == 0, "context.eval_lut(&mct2, fun_relu) == 0");
    std::cout << "context.eval_lut(&mct2, fun_relu) == 0: OK" << std::endl; 

    ct_relu = context.eval_lut(&mct3, fun_relu); 
    assertm(context.decrypt(&ct_relu) == 0, "context.eval_lut(&mct3, fun_relu) == 0");
    std::cout << "context.eval_lut(&mct3, fun_relu) == 0: OK" << std::endl; 
   
}
 

void basic_Ciphertext_tests(FHENamedParams param_set){

    std::cout << "=========== basic_Ciphertext_tests =============" << std::endl;

    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl;
    context.generate_context(param_set);
    
    std::cout << "Encrypt..." << std::endl;
    std::cout << "Testing: lwe_ct c1  = context.encrypt_temp(1);  " << std::endl;

    Ciphertext c1  = context.encrypt(1);  
 
    assertm(context.decrypt(&c1) == 1, "Decrypt(c1) == 1");
    std::cout << "context.decrypt(&c1) == 1: OK" << std::endl; 
      
    std::cout << "Testing: lwe_ct::lwe_ct(lwe_ct &c)" << std::endl;
    Ciphertext c2  = c1;   
    assertm(context.decrypt(&c2) == 1, "Decrypt(c2) == 1");
    std::cout << "context.decrypt(&c2) == 1: OK" << std::endl; 
 
    std::cout << "Testing: lwe_ct& lwe_ct::operator=(const lwe_ct other)" << std::endl;
    c1 = c2;
    assertm(context.decrypt(&c1) == 1, "Decrypt(c1) == 1");
    std::cout << "context.decrypt(&c1) == 1: OK" << std::endl;  
}



void amortized_full_domain_bootstrap_test(FHENamedParams param_set){
    std::cout << "=========== amortized_full_domain_bootstrap_test =============" << std::endl;


    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl; 
    context.generate_context(param_set); 
    
    auto id = [](int64_t m) -> int64_t {
        return m;
    }; 
  
    HomomorphicAccumulator lut_identity = context.genrate_lut(id); 

    std::vector<HomomorphicAccumulator> luts;
    luts.push_back(lut_identity);
    luts.push_back(lut_identity);
 
    Ciphertext ct1 = context.encrypt_public(1); 

    std::vector<Ciphertext> out_cts = context.eval_lut_amortized(&ct1, luts);

    std::cout << "context.decrypt(&out_cts[0]): " << context.decrypt(&out_cts[0]) << std::endl;
    assertm(context.decrypt(&out_cts[0]) == 1, "context.decrypt(context.eval_lut(&out_cts[0], lut_identity)) == 1"); 
    std::cout << "context.decrypt(context.eval_lut(&out_cts[0], lut_identity)) == 1: OK"  << std::endl;

    std::cout << "context.decrypt(&out_cts[1]): " << context.decrypt(&out_cts[1]) << std::endl;
    assertm(context.decrypt(&out_cts[1]) == 1, "context.decrypt(context.eval_lut(&out_cts[1], lut_identity)) == 1"); 
    std::cout << "context.decrypt(context.eval_lut(&out_cts[1], lut_identity)) == 1: OK"  << std::endl;
 
    out_cts = context.eval_lut_amortized(&ct1, luts);

    std::cout << "context.decrypt(&out_cts[0]): " << context.decrypt(&out_cts[0]) << std::endl;
    assertm(context.decrypt(&out_cts[0]) == 1, "context.decrypt(context.eval_lut(&out_cts[0], lut_identity)) == 1"); 
    std::cout << "context.decrypt(context.eval_lut(&out_cts[0], lut_identity)) == 1: OK"  << std::endl;

    std::cout << "context.decrypt(&out_cts[1]): " << context.decrypt(&out_cts[1]) << std::endl;
    assertm(context.decrypt(&out_cts[1]) == 1, "context.decrypt(context.eval_lut(&out_cts[1], lut_identity)) == 1"); 
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
    bit_decomp_luts.push_back(context.genrate_lut(first_bit));
    bit_decomp_luts.push_back(context.genrate_lut(second_bit));
    bit_decomp_luts.push_back(context.genrate_lut(third_bit));

    Ciphertext ct0 = context.encrypt_public(0);
    Ciphertext ct2 = context.encrypt_public(2);
    Ciphertext ct3 = context.encrypt_public(3);
    Ciphertext ct4 = context.encrypt_public(4);
    Ciphertext ct5 = context.encrypt_public(5);
    Ciphertext ct6 = context.encrypt_public(6);
    Ciphertext ct7 = context.encrypt_public(7);


    out_cts = context.eval_lut_amortized(&ct0, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 0); 
    assert(context.decrypt(&out_cts[1]) == 0); 
    assert(context.decrypt(&out_cts[2]) == 0); 
    std::cout << "Test Bin Decomp 0: OK" << std::endl;

    out_cts = context.eval_lut_amortized(&ct1, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 1); 
    assert(context.decrypt(&out_cts[1]) == 0); 
    assert(context.decrypt(&out_cts[2]) == 0); 
    std::cout << "Test Bin Decomp 1: OK" << std::endl;

    out_cts = context.eval_lut_amortized(&ct2, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 0); 
    assert(context.decrypt(&out_cts[1]) == 1); 
    assert(context.decrypt(&out_cts[2]) == 0); 
    std::cout << "Test Bin Decomp 2: OK" << std::endl;

    out_cts = context.eval_lut_amortized(&ct3, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 1); 
    assert(context.decrypt(&out_cts[1]) == 1); 
    assert(context.decrypt(&out_cts[2]) == 0); 
    std::cout << "Test Bin Decomp 3: OK" << std::endl;

    out_cts = context.eval_lut_amortized(&ct4, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 0); 
    assert(context.decrypt(&out_cts[1]) == 0); 
    assert(context.decrypt(&out_cts[2]) == 1); 
    std::cout << "Test Bin Decomp 4: OK" << std::endl;


    out_cts = context.eval_lut_amortized(&ct5, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 1); 
    assert(context.decrypt(&out_cts[1]) == 0); 
    assert(context.decrypt(&out_cts[2]) == 1); 
    std::cout << "Test Bin Decomp 5: OK" << std::endl;


    out_cts = context.eval_lut_amortized(&ct6, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 0); 
    assert(context.decrypt(&out_cts[1]) == 1); 
    assert(context.decrypt(&out_cts[2]) == 1); 
    std::cout << "Test Bin Decomp 6: OK" << std::endl;


    out_cts = context.eval_lut_amortized(&ct7, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 1); 
    assert(context.decrypt(&out_cts[1]) == 1); 
    assert(context.decrypt(&out_cts[2]) == 1); 
    std::cout << "Test Bin Decomp 7: OK" << std::endl;

}



void amortized_partial_domain_bootstrap_test(FHENamedParams param_set){
    std::cout << "=========== amortized_11_partial_domain_bootstrap_test =============" << std::endl;
 
    FHEContext context; 
    std::cout << "Generate Keys..." << std::endl;
    context.generate_context(param_set);
    context.set_default_message_encoding_type(partial_domain); 
  
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
    bit_decomp_luts.push_back(context.genrate_lut(first_bit));
    bit_decomp_luts.push_back(context.genrate_lut(second_bit));
    bit_decomp_luts.push_back(context.genrate_lut(third_bit));

    Ciphertext ct0 = context.encrypt_public(0); 
    Ciphertext ct1 = context.encrypt_public(1); 
    Ciphertext ct2 = context.encrypt_public(2);
    Ciphertext ct3 = context.encrypt_public(3);
    Ciphertext ct4 = context.encrypt_public(4);
    Ciphertext ct5 = context.encrypt_public(5);
    Ciphertext ct6 = context.encrypt_public(6);
    Ciphertext ct7 = context.encrypt_public(7);


    std::vector<Ciphertext> out_cts = context.eval_lut_amortized(&ct0, bit_decomp_luts);
 

    assert(context.decrypt(&out_cts[0]) == 0); 
    assert(context.decrypt(&out_cts[1]) == 0); 
    assert(context.decrypt(&out_cts[2]) == 0); 
    std::cout << "Test Bin Decomp 0: OK" << std::endl;


    out_cts = context.eval_lut_amortized(&ct1, bit_decomp_luts);
 

    assert(context.decrypt(&out_cts[0]) == 1); 
    assert(context.decrypt(&out_cts[1]) == 0); 
    assert(context.decrypt(&out_cts[2]) == 0); 
    std::cout << "Test Bin Decomp 1: OK" << std::endl;

 
    out_cts = context.eval_lut_amortized(&ct2, bit_decomp_luts);

      
    assert(context.decrypt(&out_cts[0]) == 0); 
    assert(context.decrypt(&out_cts[1]) == 1); 
    assert(context.decrypt(&out_cts[2]) == 0); 
    std::cout << "Test Bin Decomp 2: OK" << std::endl;

    out_cts = context.eval_lut_amortized(&ct3, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 1); 
    assert(context.decrypt(&out_cts[1]) == 1); 
    assert(context.decrypt(&out_cts[2]) == 0); 
    std::cout << "Test Bin Decomp 3: OK" << std::endl;

    out_cts = context.eval_lut_amortized(&ct4, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 0); 
    assert(context.decrypt(&out_cts[1]) == 0); 
    assert(context.decrypt(&out_cts[2]) == 1); 
    std::cout << "Test Bin Decomp 4: OK" << std::endl;


    out_cts = context.eval_lut_amortized(&ct5, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 1); 
    assert(context.decrypt(&out_cts[1]) == 0); 
    assert(context.decrypt(&out_cts[2]) == 1); 
    std::cout << "Test Bin Decomp 5: OK" << std::endl;


    out_cts = context.eval_lut_amortized(&ct6, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 0); 
    assert(context.decrypt(&out_cts[1]) == 1); 
    assert(context.decrypt(&out_cts[2]) == 1); 
    std::cout << "Test Bin Decomp 6: OK" << std::endl;


    out_cts = context.eval_lut_amortized(&ct7, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 1); 
    assert(context.decrypt(&out_cts[1]) == 1); 
    assert(context.decrypt(&out_cts[2]) == 1); 
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
    bit_decomp_luts.push_back(context.genrate_lut(first_bit));
    bit_decomp_luts.push_back(context.genrate_lut(second_bit));
    bit_decomp_luts.push_back(context.genrate_lut(third_bit));
    bit_decomp_luts.push_back(context.genrate_lut(fourth_bit));

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
    std::vector<Ciphertext> out_cts = context.eval_lut_amortized(&ct0, bit_decomp_luts);
    std::chrono::_V2::system_clock::time_point stop = std::chrono::high_resolution_clock::now();
    elapsed = elapsed + std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
  
    assert(context.decrypt(&out_cts[0]) == 0); 
    assert(context.decrypt(&out_cts[1]) == 0); 
    assert(context.decrypt(&out_cts[2]) == 0); 
    assert(context.decrypt(&out_cts[3]) == 0); 
    std::cout << "Test Bin Decomp 0: OK" << std::endl;
    std::cout << "Time elapsed:  " << elapsed << "ms" << std::endl; 
  
    out_cts = context.eval_lut_amortized(&ct1, bit_decomp_luts); 
     
    

    assert(context.decrypt(&out_cts[0]) == 1); 
    assert(context.decrypt(&out_cts[1]) == 0); 
    assert(context.decrypt(&out_cts[2]) == 0); 
    assert(context.decrypt(&out_cts[3]) == 0); 
    std::cout << "Test Bin Decomp 1: OK" << std::endl;
 
    out_cts = context.eval_lut_amortized(&ct2, bit_decomp_luts); 

      
    assert(context.decrypt(&out_cts[0]) == 0); 
    assert(context.decrypt(&out_cts[1]) == 1); 
    assert(context.decrypt(&out_cts[2]) == 0); 
    assert(context.decrypt(&out_cts[3]) == 0); 
    std::cout << "Test Bin Decomp 2: OK" << std::endl;

    out_cts = context.eval_lut_amortized(&ct3, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 1); 
    assert(context.decrypt(&out_cts[1]) == 1); 
    assert(context.decrypt(&out_cts[2]) == 0); 
    assert(context.decrypt(&out_cts[3]) == 0); 
    std::cout << "Test Bin Decomp 3: OK" << std::endl;

    out_cts = context.eval_lut_amortized(&ct4, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 0); 
    assert(context.decrypt(&out_cts[1]) == 0); 
    assert(context.decrypt(&out_cts[2]) == 1); 
    assert(context.decrypt(&out_cts[3]) == 0); 
    std::cout << "Test Bin Decomp 4: OK" << std::endl;


    out_cts = context.eval_lut_amortized(&ct5, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 1); 
    assert(context.decrypt(&out_cts[1]) == 0); 
    assert(context.decrypt(&out_cts[2]) == 1); 
    assert(context.decrypt(&out_cts[3]) == 0); 
    std::cout << "Test Bin Decomp 5: OK" << std::endl;


    out_cts = context.eval_lut_amortized(&ct6, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 0); 
    assert(context.decrypt(&out_cts[1]) == 1); 
    assert(context.decrypt(&out_cts[2]) == 1); 
    assert(context.decrypt(&out_cts[3]) == 0); 
    std::cout << "Test Bin Decomp 6: OK" << std::endl;


    out_cts = context.eval_lut_amortized(&ct7, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 1); 
    assert(context.decrypt(&out_cts[1]) == 1); 
    assert(context.decrypt(&out_cts[2]) == 1); 
    assert(context.decrypt(&out_cts[3]) == 0); 
    std::cout << "Test Bin Decomp 7: OK" << std::endl;


    out_cts = context.eval_lut_amortized(&ct8, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 0); 
    assert(context.decrypt(&out_cts[1]) == 0); 
    assert(context.decrypt(&out_cts[2]) == 0); 
    assert(context.decrypt(&out_cts[3]) == 1); 
    std::cout << "Test Bin Decomp 8: OK" << std::endl;


    out_cts = context.eval_lut_amortized(&ct9, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 1); 
    assert(context.decrypt(&out_cts[1]) == 0); 
    assert(context.decrypt(&out_cts[2]) == 0); 
    assert(context.decrypt(&out_cts[3]) == 1); 
    std::cout << "Test Bin Decomp 9: OK" << std::endl;


    out_cts = context.eval_lut_amortized(&ct10, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 0); 
    assert(context.decrypt(&out_cts[1]) == 1); 
    assert(context.decrypt(&out_cts[2]) == 0); 
    assert(context.decrypt(&out_cts[3]) == 1); 
    std::cout << "Test Bin Decomp 10: OK" << std::endl;


    out_cts = context.eval_lut_amortized(&ct11, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 1); 
    assert(context.decrypt(&out_cts[1]) == 1); 
    assert(context.decrypt(&out_cts[2]) == 0); 
    assert(context.decrypt(&out_cts[3]) == 1); 
    std::cout << "Test Bin Decomp 11: OK" << std::endl;


    out_cts = context.eval_lut_amortized(&ct12, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 0); 
    assert(context.decrypt(&out_cts[1]) == 0); 
    assert(context.decrypt(&out_cts[2]) == 1); 
    assert(context.decrypt(&out_cts[3]) == 1); 
    std::cout << "Test Bin Decomp 12: OK" << std::endl;


    out_cts = context.eval_lut_amortized(&ct13, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 1); 
    assert(context.decrypt(&out_cts[1]) == 0); 
    assert(context.decrypt(&out_cts[2]) == 1); 
    assert(context.decrypt(&out_cts[3]) == 1); 
    std::cout << "Test Bin Decomp 13: OK" << std::endl;


    out_cts = context.eval_lut_amortized(&ct14, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 0); 
    assert(context.decrypt(&out_cts[1]) == 1); 
    assert(context.decrypt(&out_cts[2]) == 1); 
    assert(context.decrypt(&out_cts[3]) == 1); 
    std::cout << "Test Bin Decomp 14: OK" << std::endl;


    out_cts = context.eval_lut_amortized(&ct15, bit_decomp_luts);
    assert(context.decrypt(&out_cts[0]) == 1); 
    assert(context.decrypt(&out_cts[1]) == 1); 
    assert(context.decrypt(&out_cts[2]) == 1); 
    assert(context.decrypt(&out_cts[3]) == 1); 
    std::cout << "Test Bin Decomp 15: OK" << std::endl;

}




void serialization_test(){
    std::cout << "=========== serialization_test =============" << std::endl;

    FHEContext first_context; 
    std::cout << "Generate Keys..." << std::endl;
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
    assert(context.decrypt(&ct0) == 1);
    

    auto id = [](int64_t m, int64_t t) -> int64_t {
        return m % t;
    }; 
      
    ct0 = context.eval_lut(&ct0, id);  
 
    context.save_Ciphertext("z_ct.cereal", ct0);  
    Ciphertext ct_out = context.load_Ciphertext("z_ct.cereal"); 
    assert(context.decrypt(&ct_out) == 1);
    std::cout << "Test Eval-Lut/Save and Load Ciphertext: OK" << std::endl;
     
    std::ofstream os("z_rlwe_ct.cereal", std::ios::binary);
    os << ct_out; 
    os.close();
    Ciphertext ct_from_stream = context.load_Ciphertext("z_rlwe_ct.cereal");
    assert(context.decrypt(&ct_from_stream) == 1);
    std::cout << "Test Writa and Save from Stream: OK" << std::endl;

    std::remove("z_ct.cereal"); 
    std::remove("z_rlwe_ct.cereal"); 
}


int main(){  

    #ifdef FOO
    std::cout << "Foo is defined" << std::endl;
    #endif
    #ifndef FOO
    std::cout << "Foo is not defined" << std::endl;
    #endif
         
   basic_Ciphertext_tests(FHENamedParams::tfhe_11_NTT);
 
   test_for_partial_domain_encoding(FHENamedParams::tfhe_11_NTT);

   test_for_partial_domain_encoding(FHENamedParams::tfhe_11_NTT_flood);
 
    test_for_signed_limied_short_int(FHENamedParams::tfhe_11_NTT);
 
    test_for_default_full_domain_encoding(FHENamedParams::tfhe_11_B);

    test_for_default_full_domain_encoding(FHENamedParams::ntrunium_12_NTT);
    
    amortized_full_domain_bootstrap_test(FHENamedParams::tfhe_11_NTT_amortized);
  
    amortized_partial_domain_bootstrap_test(FHENamedParams::tfhe_11_NTT_amortized);
  
    amortized_12_partial_domain_bootstrap_test(FHENamedParams::tfhe_12_NTT_amortized);   
 
    serialization_test();  
  
}
