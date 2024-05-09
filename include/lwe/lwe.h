 
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

  long modulus; 
 
  LWEParam() = default;
 
  LWEParam(int dim, long modulus); 
   
  long* init_ct();
 
    // TODO: This is handled by a LWECT (to use it I need to have an array of LWECT's in GadgetCT, then I can switch the methods)
    void scalar_mul(long *out, long *ct, long scalar);
    // TODO: This is handled by a LWECT
    void scalar_mul_lazy(long *out, long *ct, long scalar);
    // TODO: This is handled by a LWECT
    void add(long *out, long *ct_1, long *ct_2);
    // TODO: This is handled by a LWECT
    void add_lazy(long *out, long *ct_1, long *ct_2); 
  
    // TODO: This is handled by a LWEModSwitcher
    //void switch_modulus(long *out_ct, long *in_ct, LWEParam &new_param);
    // TODO: This is handled by a LWEModSwitcher
    //void switch_modulus(long *out_ct, long *in_ct, std::shared_ptr<LWEParam> new_param);
 
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

    LWECT() = default;

    // Initializes the ciphertext with zeros (the actual initialization will be done in some encrypt)
    LWECT(std::shared_ptr<LWEParam> lwe_par);

    /// TODO: Delete this.
    /// Need to get rid of such things after refactoring GadgetLWE and LWE-TO-LWE KeySwitch 
    LWECT(std::shared_ptr<LWEParam> lwe_par, long* ct); 

    LWECT(const LWECT &c);
 
    LWECT(LWECT &c);

    LWECT(LWECT *c); 

    ~LWECT();

    LWECT& operator=(const LWECT other);
    /// TODO: Delete
    void scalar_mul(long scalar);
    /// TODO: Delete
    void scalar_mul_lazy(long scalar);
    /// TODO: Delete
    void mul(long b);

    void mul(LWECT *out, long scalar);

    void mul_lazy(LWECT *out, long scalar);
    /// TODO: Delete
    void add(LWECT *in);

    void add(LWECT *out, LWECT *in);
    /// TODO: Delete
    void sub(LWECT *ct);

    void sub(LWECT *out, LWECT *in);
    /// TODO: Delete
    void add_lazy(LWECT *in); 

    void add_lazy(LWECT* out, LWECT *in); 
    /// TODO: Delete
    void add(long b);

    void add(LWECT* out, long b);
    /// TODO: Delete
    void sub(long b);

    void sub(LWECT*, long b);
   
    LWECT operator+(long b);

    LWECT operator+(LWECT ct);

    LWECT operator+(LWECT *ct);

    LWECT operator-(long b);

    LWECT operator-(LWECT ct);

    LWECT operator-(LWECT *ct);

    LWECT operator-();
    
    LWECT operator*(long b);  

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

LWECT operator+(long b, LWECT ct);

LWECT operator-(long b, LWECT ct);

LWECT operator*(long b, LWECT ct);

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
  
  void switch_modulus(long *out_ct, long *in_ct);
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
    
    LWESK();
  
    LWESK(std::shared_ptr<LWEParam> lwe_par, double stddev, KeyDistribution key_type);
  
    LWESK(std::shared_ptr<LWEParam> lwe_par, long* key, double stddev, KeyDistribution key_type);
 
    LWESK(const LWESK &other);

    LWESK& operator=(const LWESK other);
 
    LWECT* encrypt(long m);

    /// TODO: Delete
    void encrypt(long* ct, long m); 

    void encrypt(LWECT* ct, long m); 
    
    LWECT* encode_and_encrypt(long m, PlaintextEncoding encoding); 
    /// TODO: Should take pointer to LWECT
    void encode_and_encrypt(long* ct, long m, PlaintextEncoding encoding);
    void encode_and_encrypt(LWECT* in, long m, PlaintextEncoding encoding);

    /// TODO: TODO Delete
    long partial_decrypt(long *ct);

    long partial_decrypt(LWECT *in);
    /// TODO: Delete this
    long error(long *ct, long m);
    /// TODO: Delete this
    long decrypt(long *ct, PlaintextEncoding encoding); 

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

  private:
  long** init_gadget_ct(); 
};

class LWEGadgetSK{

  public: 
  
    std::shared_ptr<LWESK> lwe;

    long base;
    int digits;
    int bits_base;  

    LWEGadgetSK() = default;
  
    LWEGadgetSK(std::shared_ptr<LWESK> lwe, long base);
  
    LWEGadgetSK(const LWEGadgetSK& other);

    LWEGadgetSK& operator=(const LWEGadgetSK other); 

    LWEGadgetCT* gadget_encrypt(long m); 

    void gadget_encrypt(LWEGadgetCT*, long m);

    //void gadget_encrypt(long** gadget_ct, long m);
 
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

    /// TODO: Delete
    //void mask_ciphertext(long *ct);

    LWECT encrypt(long message);

    LWECT ciphertext_of_zero();
};

}

#endif