#include "math/euclidean_inversion_engine.h"
  
using namespace FHEDeck;

EuclideanInversionEngine::EuclideanInversionEngine(const int32_t degree, const int64_t coef_modulus){
    this->degree = degree;
    this->coef_modulus = coef_modulus;
    poly_mod = std::vector<int64_t>(degree+1, 0);
    poly_mod[0] = 1;
    poly_mod[degree] = 1;
}

bool EuclideanInversionEngine::inv(Polynomial &out, const Polynomial &in)const{ 
    std::vector<int64_t> a;
    a.resize(in.degree);
    for(int32_t i = 0; i < in.degree; ++i){
        a[i] = in[i];
    }
    /// Remove trailing zeros from the remainder
    while (!a.empty() && a.back() == 0) {
        a.pop_back();
    } 
    auto [g, u, v] = xgcd(a, poly_mod, coef_modulus);  
    out.zeroize();
    for(int i = 0; i < u.size(); ++i){
        out[i] = u[i];
    } 
    return !u.empty();
}
  
// Given polynomials a, b returns {r0, s0, t0} s.t. a*s0 + b*t0 = r0, where r0 is the gcd of polynomials,
// either s0 = 1, t0 = 0 or s0 = 0, t0 = 1 or
//  deg(u) < deg(b) - deg(g), deg(v) < deg(a) - deg(g) 
std::tuple<std::vector<int64_t>, std::vector<int64_t>, std::vector<int64_t>> EuclideanInversionEngine::xgcd(
        const std::vector<int64_t>& a, 
        const std::vector<int64_t>& b, 
        uint64_t p) const{

    std::vector<int64_t> r0 = a;
    std::vector<int64_t> r1 = b; 
    std::vector<int64_t> s0 = {1};
    std::vector<int64_t> s1 = {};
    std::vector<int64_t> t0 = {};
    std::vector<int64_t> t1 = {1};  
    /// NOTE: Actually you need to check if r1 is the zero poly.
    while (r1.size() != 0) { 
        std::vector<int64_t> r1_copy = r1;
        auto [q, r] = polynomial_division(r0, r1, p); 
        r1 = r; 
        std::vector<int64_t> s1_copy = s1; 
        std::vector<int64_t> t1_copy = t1;   
        //r1 = polynomial_subtraction(r0, polynomial_multiplication(q, r1, p), p); 
        s1 = polynomial_subtraction(s0, polynomial_multiplication(q, s1, p), p);   
        t1 = polynomial_subtraction(t0, polynomial_multiplication(q, t1, p), p);   
        r0 = r1_copy; 
        s0 = s1_copy; 
        t0 = t1_copy;
    }  
    int64_t inv_lead = modular_inverse(r0.back(), p);
    for(int i = 0; i < r0.size(); ++i){
        r0[i] = ((__int128)r0[i] * (__int128)inv_lead) % (__int128)p;
    }
    for(int i = 0; i < s0.size(); ++i){
        s0[i] = ((__int128)s0[i] * (__int128)inv_lead) % (__int128)p;
    }
    for(int i = 0; i < t0.size(); ++i){
        t0[i] = ((__int128)t0[i] * (__int128)inv_lead) % (__int128)p;
    }
    return {r0, s0, t0};
} 
   

std::pair<std::vector<int64_t>, std::vector<int64_t>> EuclideanInversionEngine::polynomial_division(
        const std::vector<int64_t>& a, 
        const std::vector<int64_t>& b, 
        uint64_t p)const {
    
    int32_t n = a.size();
    int32_t m = b.size(); 
    if (n < m) {
        return {std::vector<int64_t>(), a}; // Quotient is 0, remainder is a
    } 
    std::vector<int64_t> q(n - m + 1);
    std::vector<int64_t> r = a; 
    for (int32_t i = n - m; i >= 0; --i) {
        q[i] = ((__int128)r[i + m - 1] * (__int128)modular_inverse(b[m - 1], p)) % (__int128)p;  
        for (int32_t j = 0; j < m; ++j) {
            r[i + j] = Utils::integer_mod_form(r[i + j]  - (__int128)((__int128)q[i] * (__int128)b[j]) % (__int128)p, p);
        }
    } 
    // Remove trailing zeros from the remainder
    while (!r.empty() && r.back() == 0) {
        r.pop_back();
    } 
    return {q, r};
}
 

std::vector<int64_t> EuclideanInversionEngine::polynomial_multiplication(const std::vector<int64_t>& a, const std::vector<int64_t>& b, uint64_t p)const { 
    /// NOTE:  a.size() + b.size() - 1 can be -1, if a and b are zero polynomials....
    if(a.size() == 0){
        return {};
    }
    if(b.size() == 0){
        return {};
    } 
    std::vector<int64_t> result(a.size() + b.size() - 1, 0); 
    for (int32_t i = 0; i < a.size(); ++i) {
        for (int32_t j = 0; j < b.size(); ++j) {
            result[i + j] = (result[i + j] + ((__int128)a[i] * (__int128)b[j]) % (__int128)p) % p;
        }
    } 
    return result;
}

std::vector<int64_t> EuclideanInversionEngine::polynomial_subtraction(const std::vector<int64_t>& a, const std::vector<int64_t>& b, uint64_t p)const { 
    std::vector<int64_t> result; 
    if(a.size() > b.size()){ 
        result = a;
        for (int i = 0; i < b.size() ; ++i) {
            result[i] = (a[i] - b[i] + p) % p;
        } 
    }else{ 
        result = b;
        for (int i = 0; i < a.size() ; ++i) {
            result[i] = (a[i] - b[i] + p) % p;
        } 
        for (int i = a.size(); i < b.size() ; ++i) {
            result[i] = (-b[i] + p) % p;
        }
    }
    while (!result.empty() && result.back() == 0) {
        result.pop_back();
    } 
    return result;
}
  
 
std::pair<int64_t, std::pair<int64_t, int64_t>> EuclideanInversionEngine::extended_euclidean_algorithm(int64_t a, int64_t b) const{
    int64_t x0 = 0;    
    int64_t x1 = 1;
    int64_t y0 = 1;    
    int64_t y1 = 0;
    while(a != 0){ 
        auto dv = std::div(b, a);
        int64_t q = dv.quot; 
        b = a;
        a = dv.rem;
        int64_t temp = y0;
        y0 = y1;
        y1 = temp - q * y1;
        temp = x0;
        x0 = x1;
        x1 = temp - q * x1;
    }     
    int64_t gcd = b;
    int64_t x = x0;
    int64_t y = y0; 
    return {gcd, {x, y}};
}
  
int64_t EuclideanInversionEngine::modular_inverse(int64_t a, int64_t p)const {
    auto [gcd, coeffs] = extended_euclidean_algorithm(a, p); 
    return Utils::integer_mod_form(coeffs.first, p);
} 
