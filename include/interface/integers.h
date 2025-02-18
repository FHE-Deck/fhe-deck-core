#ifndef INTEGERS
#define INTEGERS
 
#include "global_headers.h" 
#include "interface/fhe_context.h"
#include "interface/ciphertext.h"   


namespace FHEDeck{

/// @brief Forward Declaration of the FHEContext class which is defined in interface/fhe_context.h.
class FHEContext;

/// @brief This class is decalred in the file Integers.h after DigitInteger.
class RNSInteger;
/// @brief This class is decalred in the file Integers.h after DigitConfig.
class DigitInteger;

class DigitConfig{
    
    public:
 
        FHEContext context;

        int32_t base;
        int32_t size; 
        int32_t bits_base;
        int32_t bits_in_plaintext_space;
        PlaintextEncoding digit_plaintext_encoding;

        int64_t max;

        DigitConfig() = default;
  
        DigitConfig(FHEContext& context, int32_t base, int32_t size);
  
        void init();

        DigitInteger encrypt(int64_t message);

        int64_t decrypt(const DigitInteger& ciphertext);
};

class DigitInteger{

    public:
        
        std::vector<Ciphertext> encrypted_digits; 
        DigitConfig config;
 
        DigitInteger() = default;

        DigitInteger(int64_t message, const DigitConfig& config);

        DigitInteger(const DigitConfig& config, const std::vector<Ciphertext>& encrypted_digits);
  
        DigitInteger(const DigitConfig& config, const RNSInteger& other);

        DigitInteger(const DigitInteger& other); 

        DigitInteger& operator=(const DigitInteger& other);
  
        DigitInteger operator+(const DigitInteger& other)const;

        DigitInteger operator+(const int64_t scalar)const;

        DigitInteger add_with_carry(const DigitInteger& other)const;
  
        DigitInteger add_with_carry(const int64_t scalar)const;

        DigitInteger operator-(const DigitInteger& other)const;

        DigitInteger operator-(const int64_t scalar)const;

        DigitInteger subtract_with_carry(const DigitInteger& other)const;

        DigitInteger subtract_with_carry(const int64_t scalar)const;

        DigitInteger operator*(const int64_t scalar)const;

        DigitInteger operator*(const DigitInteger& other)const;
 
        std::vector<int64_t> int_decomp(int64_t x)const;

        int64_t int_comp(const std::vector<int64_t>& digits)const;

        bool is_compatible(const DigitInteger& other)const;

        /** 
         * @brief Adjusts the size to the config.size. So either fills encrypted_digits with zero encryptions or drops digits. 
         */
        void resisze();
   
        std::vector<Ciphertext> choose_digits(const std::vector<Ciphertext>& in_1, const std::vector<Ciphertext>& in_2, Ciphertext& bit);

        Ciphertext choose_digit(const Ciphertext& in_1, const Ciphertext& in_2, const Ciphertext& bit);

    private:


        void init();

        void verify_ciphertext_vector(const std::vector<Ciphertext>& digits);

        template<typename DigitType>
        DigitInteger addition_with_carry(const std::vector<DigitType> digits)const;

        template<typename DigitType>
        DigitInteger subtraction_with_carry(const std::vector<DigitType> digits)const;
 
        std::vector<Ciphertext> decompose_rns_element(const Ciphertext& in, int64_t modulus, int64_t rns_coef)const;


};  


class RNSConfig{

    public:
    
        int64_t modulus; 
        int64_t size;

        /// TODO: Revisit naming of these lists.
        std::vector<int32_t> crt_base;
        std::vector<int64_t> factors;
        std::vector<int64_t> m_list;
        std::vector<int64_t> cofactors;
 
        std::vector<PlaintextEncoding> plaintext_encodings;

        FHEContext context;
 
        RNSConfig() = default;

        RNSConfig(FHEContext& context, std::vector<int32_t> crt_base);

        std::vector<int32_t> decompose(int64_t x)const;

        int64_t compose(const std::vector<int32_t>& digits)const;

        RNSInteger encrypt(int64_t message);

        int64_t decrypt(const RNSInteger& ciphertext);

    private:
    
        void init();

};
 
class RNSInteger{
 
    public:

        std::vector<Ciphertext> encrypted_digits;
        RNSConfig base; 

        RNSInteger() = default;
 
        RNSInteger(int64_t message, const RNSConfig& base);
  
        RNSInteger(std::vector<Ciphertext> cts, const RNSConfig& base);
 
        RNSInteger(const DigitInteger& other, const RNSConfig& base);
  
        RNSInteger(const RNSInteger& other);

        RNSInteger operator+(const RNSInteger& other);

        RNSInteger operator+(const int64_t scalar);

        RNSInteger operator-(const RNSInteger& other);

        RNSInteger operator-(const int64_t scalar);

        RNSInteger operator*(const int64_t scalar);

        RNSInteger operator*(const RNSInteger& other);
 
};

}// End of namespace FHEDeck

 
#endif 