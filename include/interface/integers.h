#ifndef INTEGERS
#define INTEGERS
 
#include "global_headers.h" 
#include "interface/ciphertext.h" 

namespace fhe_deck{

/// @brief Forward Declaration of the FHEContext class which is defined in interface/fhe_context.h.
class FHEContext;

/// @brief This class is decalred in the file Integers.h after DigitInteger.
class CRTInteger;

class DigitConfig{
    
    public:

        const FHEContext* context;
        int32_t base;
        int32_t size; 
        int32_t bits_base;
        int32_t bits_in_plaintext_space;
        PlaintextEncoding digit_plaintext_encoding;

        int64_t max;

        DigitConfig() = default;
  
        DigitConfig(FHEContext& context, int32_t base, int32_t size);
  
        void init();
};

class DigitInteger{

    public:
        
        std::vector<Ciphertext> encrypted_digits; 
        DigitConfig config;
 
        DigitInteger() = default;

        DigitInteger(const DigitConfig& config, int64_t message);

        DigitInteger(const DigitConfig& config, const std::vector<Ciphertext>& encrypted_digits);
  
        DigitInteger(const DigitConfig& config, const CRTInteger& other);

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
 
        std::vector<Ciphertext> decompose_rns_element(const Ciphertext& in, int64_t modulus, int64_t rns_coef, int32_t size)const;


};  


class RNSBase{

    public:
    
        int64_t modulus; 
        int64_t size;
        std::vector<int32_t> crt_base;
        std::vector<int64_t> factors;
        std::vector<int64_t> m_list;
        std::vector<int64_t> cofactors;
        std::vector<PlaintextEncoding> plaintext_encodings;
        const FHEContext* context;
 
        RNSBase() = default;

        RNSBase(FHEContext& context, std::vector<int32_t> crt_base);

        std::vector<int32_t> decompose(int64_t x)const;

        int64_t compose(const std::vector<int32_t>& digits)const;


    private:
    
        void init();

};
 
class CRTInteger{
 
    public:

        std::vector<Ciphertext> encrypted_digits;
        RNSBase base; 

        CRTInteger() = default;
 
        CRTInteger(int64_t message, const RNSBase& base);
  
        CRTInteger(std::vector<Ciphertext> cts, const RNSBase& base);
 
        CRTInteger(const DigitInteger& other, const RNSBase& base);
  
        CRTInteger(const CRTInteger& other);

        CRTInteger operator+(const CRTInteger& other);

        CRTInteger operator+(const int64_t scalar);

        CRTInteger operator-(const CRTInteger& other);

        CRTInteger operator-(const int64_t scalar);

        CRTInteger operator*(const int64_t scalar);

        CRTInteger operator*(const CRTInteger& other);
 
};



}// End of namespace fhe_deck

 
#endif 