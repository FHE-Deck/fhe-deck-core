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

        DigitConfig() = default;
  
        DigitConfig(FHEContext& context, int32_t base, int32_t size);
  
        void init();
};

class DigitInteger{

    public:
        
        std::vector<Ciphertext> encrypted_digits; 
        DigitConfig config;


        //const FHEContext* context;
        //int32_t base; 
        //PlaintextEncoding digit_plaintext_encoding;
        //int32_t bits_in_plaintext_space; 
        //int32_t bits_base;
        //int32_t size; 

        DigitInteger() = default;

        DigitInteger(const DigitConfig& config, int64_t message);

        DigitInteger(const DigitConfig& config, const std::vector<Ciphertext>& encrypted_digits);

        //DigitInteger(const FHEContext& context, const std::vector<Ciphertext>& encrypted_digits, int32_t base);

        //DigitInteger(const FHEContext& context, int64_t message, int32_t base, int32_t size);
 
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

        void resisze(int32_t size);
 
        /// There are also operations like:
        /// Note that some of these operations should perhaps be provided in the Ciphertext class or file.
        /// Choose one ciphertext depending on the input bit. Choose digits
        /// Digit compare (basically returns the overflow digit from the subtraction)
        /// Swap (swap one vector of Ciphertext with another)

    private:


        void init();

        void verify_ciphertext_vector(const std::vector<Ciphertext>& digits);

        template<typename DigitType>
        DigitInteger addition_with_carry(const std::vector<DigitType> digits)const;

        template<typename DigitType>
        DigitInteger subtraction_with_carry(const std::vector<DigitType> digits)const;

};


class RNSBase{

    public:
    
        int64_t modulus; 
        std::vector<int32_t> crt_base;
        std::vector<int64_t> factors;
        std::vector<int64_t> m_list;
        std::vector<int64_t> cofactors;
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
        //FHEContext* context;
        //int64_t modulus;

        //std::vector<int64_t> factors;
        //std::vector<int64_t> m_list;
        //std::vector<int64_t> cofactors;

        CRTInteger() = default;
 
        CRTInteger(int64_t message, const RNSBase& base);
 
        CRTInteger(const DigitInteger& message, const RNSBase& base);

        CRTInteger(std::vector<Ciphertext> cts, const RNSBase& base);

        CRTInteger(const CRTInteger& other); 
  
        CRTInteger operator+(const CRTInteger& other);

        CRTInteger operator+(const int64_t scalar);

        CRTInteger operator-(const CRTInteger& other);

        CRTInteger operator-(const int64_t scalar);

        CRTInteger operator*(const int64_t scalar);

        CRTInteger operator*(const CRTInteger& other);


        /// There are also operations like:
        /// Note that some of these operations should perhaps be provided in the Ciphertext class or file.
        /// Choose one ciphertext depending on the input bit. Choose digits
        /// Digit compare (basically returns the overflow digit from the subtraction)
        /// Swap (swap one vector of Ciphertext with another)
 
 
};



}// End of namespace fhe_deck

 
#endif 