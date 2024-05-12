 
#ifndef LWE_H
#define LWE_H

#include <random>
#include <iostream> 
#include "utils.h"
#include "plaintext_encoding.h"
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>

namespace fhe_deck{

class LWEParam{

  public:  

  // LWE Dimension
  int dim;
  // LWE Modulus
  long modulus; 
  /// NOTE: Never explicitely used in FHE-Deck, but cereal serialization fails to compile without it.
  LWEParam() = default;
 
  LWEParam(int dim, long modulus); 
    
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(dim, modulus);
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(dim, modulus);
    } 
};

class LWECT{
 
  public:
 
    std::shared_ptr<LWEParam> param;

    bool init = false;
 
    long *ct;

    /// NOTE: Never explicitely used in FHE-Deck, but cereal serialization fails to compile without it.
    LWECT() = default;

    ~LWECT();

    // Initializes the ciphertext with zeros (the actual initialization will be done in some encrypt)
    LWECT(std::shared_ptr<LWEParam> lwe_par);
  
    LWECT(const LWECT &c);
  
    LWECT& operator=(const LWECT other); 

    LWECT* clone();

    void mul(LWECT *out, long scalar);

    void mul_lazy(LWECT *out, long scalar); 

    void add(LWECT *out, LWECT *in); 

    void sub(LWECT *out, LWECT *in); 

    void add_lazy(LWECT* out, LWECT *in);  

    void add(LWECT* out, long b); 

    void sub(LWECT* out, long b);

    void neg(LWECT* out);
  
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(param); 

      std::vector<long> ct_arr; 
      for(int i = 0; i < param->dim+1; ++i){
        ct_arr.push_back(ct[i]);
      }
      ar(ct_arr) ;
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(param);
      std::vector<long> ct_arr;
      ar(ct_arr);
      ct = new long[param->dim+1];
      for(int i = 0; i < param->dim+1; ++i){
        ct[i] = ct_arr[i];
      }
      this->init = true;
    } 
};
 
class LWEModSwitcher{

  public:
  std::shared_ptr<LWEParam> from;
  std::shared_ptr<LWEParam> to;

  bool long_arithmetic = false;

  // Some precomputation
  int ct_size;
  double Q_from;
  double Q_to;
  double temp; 
  // If we need larger precision
  long double long_Q_from;
  long double long_Q_to;
  long double long_temp; 

  LWEModSwitcher() = default;

  // Initializes the ciphertext with zeros (the actual initialization will be done in some encrypt)
  LWEModSwitcher(std::shared_ptr<LWEParam> from, std::shared_ptr<LWEParam> to);
   
  void switch_modulus(LWECT *out_ct, LWECT *in_ct);
};
 
class LWESK {
 
    public:  
    std::shared_ptr<LWEParam> param;
  
    std::shared_ptr<Distribution> unif_dist;
    std::shared_ptr<Distribution> error_dist;
    std::shared_ptr<Distribution> sk_dist;
    KeyDistribution key_type;
    double stddev;
    // Initialized in the constructors and freed in the destructor.
    long *key; 

    std::unique_ptr<LongIntegerMultipler> multiplier;
    
    ~LWESK();
    /// NOTE: Never explicitely used in FHE-Deck, but cereal serialization fails to compile without it.
    LWESK() = default;
  
    LWESK(std::shared_ptr<LWEParam> lwe_par, double stddev, KeyDistribution key_type);
  
    LWESK(std::shared_ptr<LWEParam> lwe_par, long* key, double stddev, KeyDistribution key_type);
 
    LWESK(const LWESK &other);

    LWESK& operator=(const LWESK other);
 
    LWECT* encrypt(long m);

    void encrypt(LWECT* ct, long m); 
    
    LWECT* encode_and_encrypt(long m, PlaintextEncoding encoding); 
    
    void encode_and_encrypt(LWECT* in, long m, PlaintextEncoding encoding);
  
    long partial_decrypt(LWECT *in); 

    long decrypt(LWECT *ct, PlaintextEncoding encoding); 
   
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(param);  
      std::vector<long> s_arr; 
      for(int i = 0; i < param->dim; ++i){
        s_arr.push_back(key[i]);
      }
      ar(s_arr);
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(param);
      std::vector<long> s_arr;
      ar(s_arr);
      this->key = new long[param->dim];
      for(int i = 0; i < param->dim; ++i){
        this->key[i] = s_arr[i];
      } 
    } 
};
    
class LWEGadgetCT{

  public: 
  std::shared_ptr<LWESK> lwe; 
  long base;
  int digits;
  int bits_base;  
  std::shared_ptr<LWEParam> lwe_param;
   
  std::unique_ptr<std::unique_ptr<LWECT>[]> ct_content;
  
  LWEGadgetCT(std::shared_ptr<LWEParam> lwe_par, long base);
  
  void gadget_mul(LWECT *out_ct, long scalar); 

  void gadget_mul_lazy(LWECT *out_ct, long scalar); 
};

class LWEGadgetSK{

  public: 
  
    std::shared_ptr<LWESK> lwe;

    long base;
    int digits;
    int bits_base;  
    /// NOTE: Never explicitely used in FHE-Deck, but cereal serialization fails to compile without it.
    LWEGadgetSK() = default;
  
    LWEGadgetSK(std::shared_ptr<LWESK> lwe, long base);
  
    LWEGadgetSK(const LWEGadgetSK& other);

    LWEGadgetSK& operator=(const LWEGadgetSK other); 

    LWEGadgetCT* gadget_encrypt(long m); 

    void gadget_encrypt(LWEGadgetCT*, long m);
  
    template <class Archive>
    void save( Archive & ar ) const
    { 
      ar(lwe, base);  
    }
        
    template <class Archive>
    void load( Archive & ar )
    {  
      ar(lwe, base);  
    }    
};


class LWEPublicKey{

  public:
 
    /// TODO: Change this stddev stuff to uniform. 
    double stddev; 
    Sampler rand_masking;
   
    std::unique_ptr<std::unique_ptr<LWECT>[]> public_key_ptr;
    int size; 

    std::shared_ptr<LWEParam> param;
 
    LWEPublicKey(std::shared_ptr<LWESK> lwe_sk, int key_size, double stddev);

    LWEPublicKey(const LWEPublicKey &other);
   
    LWEPublicKey& operator=(const LWEPublicKey other);
 
    void mask_ciphertext(LWECT *ct);
  
    LWECT* encrypt(long message);

    LWECT* ciphertext_of_zero();
};

}

#endif