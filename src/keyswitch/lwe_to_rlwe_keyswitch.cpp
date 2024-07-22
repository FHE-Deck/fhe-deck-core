#include "lwe_to_rlwe_keyswitch.h"

using namespace fhe_deck;

LWEToRLWEKeySwitchKey::LWEToRLWEKeySwitchKey(std::shared_ptr<LWESK> sk_origin, std::shared_ptr<RLWEGadgetSK> sk_dest) {
    //origin = sk_origin->param;
    destination = sk_dest->gadget;
    destination_param = sk_dest->rlwe_sk->param;
    degree_inv = Utils::mod_inv(destination->degree, destination->modulus); 
    bits_degree = Utils::number_of_bits(destination->degree) - 1;
    mask2 = destination_param->size * 2 - 1;
    mask = destination_param->size - 1;
    this->gadget = SignedDecompositionGadget(destination->degree, destination->modulus, destination->base); 
    key_switching_key_gen(sk_origin, sk_dest);
}

LWEToRLWEKeySwitchKey::LWEToRLWEKeySwitchKey(const LWEToRLWEKeySwitchKey &other){
    throw std::runtime_error("LWEToRLWEKeySwitchKey::LWEToRLWEKeySwitchKey(const LWEToRLWEKeySwitchKey &other)");
}

LWEToRLWEKeySwitchKey& LWEToRLWEKeySwitchKey::operator=(const LWEToRLWEKeySwitchKey other){
    throw std::runtime_error("LWEToRLWEKeySwitchKey& LWEToRLWEKeySwitchKey::operator=(const LWEToRLWEKeySwitchKey other)");
    return *this;
}

void
LWEToRLWEKeySwitchKey::key_switching_key_gen(std::shared_ptr<LWESK> sk_origin, std::shared_ptr<RLWEGadgetSK> sk_dest) { 
 
    //Polynomial sk_auto = sk_dest->rlwe_sk->sk_poly;
    Polynomial sk_auto(sk_dest->rlwe_sk->sk_poly.degree, sk_dest->rlwe_sk->sk_poly.coef_modulus); 
    for(int i = 2; i <= destination->degree; i *= 2) {
        eval_auto_poly(&sk_auto, &sk_dest->rlwe_sk->sk_poly, i+1);
        std::vector<std::unique_ptr<RLWECT>> row;
        for(int j = 0; j < destination->digits; j++) {
            row.push_back(std::unique_ptr<RLWECT>(sk_dest->rlwe_sk->encrypt(&sk_auto)));
            sk_auto.mul(&sk_auto, destination->base);
        }
        key_content.push_back(std::move(row));
    }
}

void quick_vector_modmul(Polynomial* out, Polynomial* in, long scalar) {

    int64_t modulus = out->coef_modulus;
    int32_t N = out->degree;
    /*
    uint32_t mod_bits = 2 * (Utils::number_of_bits(out->coef_modulus)) + 1;


    // Precomp
    __int128_t mu = 1;
    mu <<= (mod_bits);
    mu /= modulus;
    */
    int64_t scal = scalar;

    __int128_t x, y;
    for(int32_t i = 0; i < N; i++) {
        /*
        long v_i = in->coefs[i];
        x = __int128_t(v_i) * scal;
        y = (x * mu) >> (mod_bits);
        y = y * modulus;
        x -= y; */
        // TODO: temporary solution til we debug barret
        /// NOTE: Why do we add modulus here again?? 
        out->coefs[i] = ((__int128_t(in->coefs[i]) * scal) % modulus + modulus) % modulus;
    }
}

void LWEToRLWEKeySwitchKey::lwe_to_rlwe_key_switch(RLWECT *rlwe_ct_out, LWECT *lwe_ct_in) {


    rlwe_ct_out->b.zeroize(); 
    rlwe_ct_out->b.coefs[0] = lwe_ct_in->ct[0];
   
    // set up a
    Utils::array_mod_form(lwe_ct_in->ct, lwe_ct_in->ct, destination->degree + 1, destination->modulus);
    rlwe_ct_out->a.coefs[0] = (destination->modulus - lwe_ct_in->ct[1]) % destination->modulus;
    for(int i = 1; i < destination->degree; ++i){
        rlwe_ct_out->a.coefs[destination->degree - i] = lwe_ct_in->ct[i+1];
    }
    
    quick_vector_modmul(&rlwe_ct_out->b, &rlwe_ct_out->b, degree_inv);
    quick_vector_modmul(&rlwe_ct_out->a, &rlwe_ct_out->a, degree_inv); 

    RLWECT buf(destination_param);
    for(int i = bits_degree; i >= 1; i--) {
        eval_auto(&buf, rlwe_ct_out, i);
        rlwe_ct_out->add(rlwe_ct_out, &buf);
    }
}

void LWEToRLWEKeySwitchKey::eval_auto(fhe_deck::RLWECT *rlwe_ct_out, fhe_deck::RLWECT *rlwe_ct_in, uint32_t log2_idx) {
    int64_t idx = (1 << log2_idx);
    Polynomial auto_a(rlwe_ct_in->a);

    rlwe_ct_out->a.zeroize();
    rlwe_ct_out->b.zeroize();
    
    eval_auto_poly(&auto_a, &rlwe_ct_in->a, idx + 1);
    eval_auto_poly(&rlwe_ct_out->b, &rlwe_ct_in->b, idx + 1);
 
    int64_t** buffer = gadget.init_out();
    gadget.sample(buffer, auto_a.coefs);  
    std::vector<std::unique_ptr<fhe_deck::RLWECT>>& auto_key = key_content[log2_idx - 1];
    RLWECT tmp(destination_param); 
    for(int i = 0; i < destination->digits; i++) {
        /// TODO: Generally need to have gadget sample return a vector of Polynomials instead of this two dimensional array.
        Utils::cp(auto_a.coefs, buffer[i], destination->degree); 
        /// TODO: Clearly need to precompute the eval form of the automorphism keys here. 
        auto_key[i]->mul(&tmp, &auto_a);
        rlwe_ct_out->sub(rlwe_ct_out, &tmp);
    }
    gadget.delete_out(buffer); 
}

void LWEToRLWEKeySwitchKey::eval_auto_poly(fhe_deck::Polynomial* out_poly,
                                           fhe_deck::Polynomial* in_poly, uint32_t idx) {
    // we know the degree is a power of 2 
 
    if (idx == out_poly->degree + 1) {
        // N + 1 automorphism just negates odd entries
        for(uint32_t i = 0; i < out_poly->degree; i+=2) {
            out_poly->coefs[i] = in_poly->coefs[i];
            out_poly->coefs[i+1] = (in_poly->coef_modulus - in_poly->coefs[i+1]) % in_poly->coef_modulus;
        }
    } else {
        Polynomial tmp = *in_poly;
        for (uint32_t i = 0; i < out_poly->degree; i++) {
            int64_t v_i = tmp.coefs[i];
            uint32_t perm = (i * idx) & mask2;
            uint32_t new_idx = perm & mask;
            out_poly->coefs[new_idx] = (perm == new_idx) ? v_i : (in_poly->coef_modulus - v_i) % in_poly->coef_modulus;
        }
    }
} 