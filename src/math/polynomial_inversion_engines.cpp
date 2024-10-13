#include "polynomial_inversion_engines.h"

using namespace fhe_deck;

EuclideanInversionEngine::EuclideanInversionEngine(const Polynomial& poly_mod){
    this->poly_mod = poly_mod;
}

void EuclideanInversionEngine::inv(Polynomial &out, const Polynomial &in){
    Polynomial g(poly_mod.degree, poly_mod.coef_modulus); 
    Polynomial v(poly_mod.degree, poly_mod.coef_modulus); 
    euclid_alg(g, out, v, in, poly_mod); 
}

void EuclideanInversionEngine::euclid_alg(Polynomial& g, Polynomial& u, Polynomial& v, const Polynomial &a, const Polynomial &b){
    // r0 = a
    Polynomial r0 = a;
    // r1 = b
    Polynomial r1 = b;
    // s0 = 1
    Polynomial s0(poly_mod.degree, poly_mod.coef_modulus);
    s0.zeroize();
    s0.coefs[0] = 1;
    // s1 = 0
    Polynomial s1(poly_mod.degree, poly_mod.coef_modulus);
    s1.zeroize(); 
    // t0 = 0
    Polynomial t0 = s1;
    // t1 = 1
    Polynomial t1 = s0;
    // zero_poly = Poly([0])
    Polynomial zero_poly = s1;
    // while r1 != zero_poly:
    while(Utils::is_eq_poly(r1.coefs, zero_poly.coefs, zero_poly.degree)){
       
    //     # Compute the q the quotient and remainder of dividing r0 by r1 
    //    q = r0 // r1
    Polynomial q(poly_mod.degree, poly_mod.coef_modulus);
    Polynomial r(poly_mod.degree, poly_mod.coef_modulus);
    poly_division(q, r, r0, r1);
    //    r1copy = r1
    Polynomial r1_copy = r1;
    //    s1copy = s1
    Polynomial s1_copy = s1;
    //    t1copy = t1
    Polynomial t1_copy = t1;
    //    r1 = r0 - q * r1
    Polynomial temp(poly_mod.degree, poly_mod.coef_modulus);
    q.mul(temp, r1);
    //    s1 = s0 - q * s1
    //    t1 = t0 - q * t1
    //    r0 = r1copy
    //    s0 = s1copy
    //    t0 = t1copy  
     
    }
    //g = r0
    //u = s0
    //v = t0 
    //return [g, u, v]
}


/*
std::pair<std::vector<int>, std::pair<std::vector<int>, std::vector<int>>> extended_euclidean_algorithm_poly(const std::vector<int>& a, const std::vector<int>& b, int p) {
    if (b.empty()) {
        return {a, {{1}, {0}}};
    }

    std::pair<std::vector<int>, std::pair<std::vector<int>, std::vector<int>>> result = extended_euclidean_algorithm_poly(b, polynomial_division(a, b, p).second, p);
    std::vector<int> g = result.first;
    std::vector<int> s = result.second.first;
    std::vector<int> t = result.second.second;

    std::vector<int> q = polynomial_division(a, b, p).first;
    std::vector<int> s_prime = t;
    t = polynomial_subtraction(s, polynomial_multiplication(q, t, p), p);
    s = s_prime;

    return {g, {s, t}};
}

std::vector<int> polynomial_division(const std::vector<int>& dividend, const std::vector<int>& divisor, int p) {
    std::vector<int> quotient(dividend.size() - divisor.size() + 1, 0);
    std::vector<int> remainder = dividend;

    while (remainder.size() >= divisor.size() && !remainder.empty()) {
        int scale = remainder.front() / divisor.front();
        quotient[remainder.size() - divisor.size()] = scale;

        for (int i = 0; i < divisor.size(); ++i) {
            remainder[i + remainder.size() - divisor.size()] = (remainder[i + remainder.size() - divisor.size()] - scale * divisor[i] + p) % p;
        }

        while (!remainder.empty() && remainder.back() == 0) {
            remainder.pop_back();
        }
    }

    return quotient;
}
*/

std::vector<int> polynomial_multiplication(const std::vector<int>& a, const std::vector<int>& b, int p) {
    std::vector<int> result(a.size() + b.size() - 1, 0);

    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b.size(); ++j) {
            result[i + j] = (result[i + j] + a[i] * b[j]) % p;
        }
    }

    return result;
}

std::vector<int> polynomial_subtraction(const std::vector<int>& a, const std::vector<int>& b, int p) {
    std::vector<int> result(a.size(), 0); 
    for (int i = 0; i < a.size(); ++i) {
        result[i] = (a[i] - b[i] + p) % p;
    } 
    return result;
}


void EuclideanInversionEngine::poly_division(Polynomial& quotient, Polynomial& reminder, const Polynomial& divided, const Polynomial& divisor){

}


void EuclideanInversionEngine::trivial_poly_mul(Polynomial& out, Polynomial& in_1, Polynomial& in_2){

}

 
std::pair<int, std::pair<int, int>> EuclideanInversionEngine::extended_euclidean_algorithm(int a, int b) {
    int x = 1, y = 0, x1 = 0, y1 = 1;

    while (b != 0) {
        int q = a / b;
        int r = a % b;
        a = b;
        b = r;
        x = x1;
        y = y1;
        x1 = x - q * x1;
        y1 = y - q * y1;
    }

    return {a, {x, y}};
}

std::pair<std::vector<int>, std::vector<int>> polynomial_division(const std::vector<int>& dividend, const std::vector<int>& divisor) {
    std::vector<int> quotient(dividend.size() - divisor.size() + 1, 0);
    std::vector<int> remainder = dividend;

    while (remainder.size() >= divisor.size() && !remainder.empty()) {
        int scale = remainder.front() / divisor.front();
        quotient[remainder.size() - divisor.size()] = scale;

        for (int i = 0; i < divisor.size(); ++i) {
            remainder[i + remainder.size() - divisor.size()] -= scale * divisor[i];
        }

        while (!remainder.empty() && remainder.back() == 0) {
            remainder.pop_back();
        }
    }

    return {quotient, remainder};
}
