#include <iostream>
#include <cassert> 
#include "fhe_deck.h" 


using namespace FHEDeck;

/// @brief The function that demonstrates the serializing, saving and loading secret/public key, and ciphertexts. 
void serialization_example();

int main(){
    serialization_example(); 
}

void serialization_example(){
    std::cout << "=========== Run serialization_example =============" << std::endl;

    
    std::cout << "Generate Keys..." << std::endl;
    FHEContext first_context(FHENamedParams::tfhe_11_NTT); 
    /// Get the plaintext encoding algorithm. 
    PlaintextEncoding encoding = first_context.get_default_plaintext_encoding();
    try{
        std::cout << "Save the Secret Key" << std::endl; 
        first_context.save_secret_key("z_sk.cereal"); 
        std::cout << "Save the Public Key" << std::endl;
        first_context.save_public_key("z_pk.cereal");
    
        /// Now we will load the keys to a new context.
        FHEContext context;  
        std::cout << "Load secret Key..." << std::endl; 
        context.load_secret_key("z_sk.cereal"); 
        std::cout << "Load Public Key..." << std::endl; 
        context.load_public_key("z_pk.cereal");
        /// Delete the files.
        std::cout << "Delete The Files..." << std::endl; 
        std::remove("z_sk.cereal"); 
        std::remove("z_pk.cereal"); 

        /// Lets encrypt something with the new context. 
        Ciphertext ct0 = context.encrypt_public(1, encoding);   
        /// Check if correct
        assert(context.decrypt(ct0) == 1);
         
        /// Now we will evaluate a function on the ciphertext to check if the public evaluation key works.
        auto id_0 = [](int64_t m, int64_t t) -> int64_t {
            return m % t;
        }; 
        std::function<int64_t(int64_t)> id = std::bind(id_0, std::placeholders::_1, context.get_default_plaintext_space());
        ct0 = context.eval(ct0, id);  
    
        /// Now we will save the ciphertext and load it again. 
        std::cout << "Save Ciphertext..." << std::endl; 
        context.save_Ciphertext("z_ct.cereal", ct0);  
        std::cout << "Load Ciphertext..." << std::endl; 
        Ciphertext ct_out = context.load_Ciphertext("z_ct.cereal"); 
        /// Check if the loaded ciphertext is correct. 
        assert(context.decrypt(ct_out) == 1);
        std::cout << "Test Eval-Lut/Save and Load Ciphertext: OK" << std::endl;
        
        /// Another way to save and load ciphertexts if via the << and >> operators.
        std::cout << "Save Ciphertext..." << std::endl; 
        std::ofstream os("z_rlwe_ct.cereal", std::ios::binary);
        os << ct_out; 
        os.close();

        std::cout << "Load Ciphertext..." << std::endl; 
        Ciphertext ct_from_stream = context.load_Ciphertext("z_rlwe_ct.cereal");
        assert(context.decrypt(ct_from_stream) == 1);

        std::cout << "Test Write and Save from Stream: OK" << std::endl; 

        /// Delete the files.
        std::remove("z_ct.cereal"); 
        std::remove("z_rlwe_ct.cereal");
        
    }catch (std::logic_error& e) {
        std::cerr << "Serialization_test Error: " << e.what() << std::endl;
    }
}
