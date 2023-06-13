#include "../include/rotation_poly.h"
#include <iostream>

using namespace fhe_deck;


void test_rot_poly(){
    std::cout << "=============== test_rot_poly =================" << std::endl;
    long N = 16;
    long Q = 64;
    long t = 4;

    auto fp = [](long m, long t) -> long {
        return m % t;
    };


    long* poly_1 = RotationPoly::rot_identity(t, N, Q);
    PlaintextEncoding encoding(full_domain, t, Q);
    RotationPoly poly_2(fp, N, encoding);    

    std::cout << "poly_1: " << Utils::to_string(poly_1, N) << std::endl ;
    std::cout << "poly_2: " << Utils::to_string(poly_2.lookup_polynomial, N) << std::endl;  

}
 

/*
negacyclic rotate poly is used to verify correctness of blind rotation
*/
void test_negacyclic_rotate_poly(){
    std::cout << "=============== test_negacyclic_rotate_poly =================" << std::endl;
    int N = 16;
    long* poly = new long[N];
    for(int i = 0; i < N; ++i){
        poly[i] = i;
    }
    std::cout << "poly:    " << Utils::to_string(poly, N) << std::endl ;

    long* rot_poly = new long[N];

    // Note that rot may be in [0, 2*N)!
    int rot = 16 + 4;
    Utils::negacyclic_rotate_poly(rot_poly, poly, N, rot);
    std::cout << "rot_poly: " << Utils::to_string(rot_poly, N) << std::endl ;
 
}





void test_eval_poly(){
    std::cout << "=============== test_eval_poly =================" << std::endl;
    long N = 16;
    long Q = 64;
    long t = 4;

    auto fp = [](long m, long t) -> long {
        return (m+1) % t;
    };
 
    PlaintextEncoding encoding(partial_domain, t, Q);
    RotationPoly poly(fp, N, encoding);     

    std::cout << "Poly (Encoded): " << Utils::to_string(poly.lookup_polynomial, N) << std::endl;
    poly.decode();
    std::cout << "Poly (Decoded): " << Utils::to_string(poly.lookup_polynomial, N) << std::endl;
    poly.encode();
    std::cout << "Poly (Encoded): " << Utils::to_string(poly.lookup_polynomial, N) << std::endl;

    poly.to_amortization_form();
    std::cout << "Poly (Amortized Form): " << Utils::to_string(poly.lookup_polynomial, N) << std::endl;
    poly.to_non_amortized_form();
    std::cout << "Poly (Encoded): " << Utils::to_string(poly.lookup_polynomial, N) << std::endl;

    long* rot_poly = new long[N];
    std::cout << "Encrypting: 0" << std::endl;
    long phase = encoding.encode_message(0);
    // Modulus switch
    phase = round(((double)phase * (2*N))/Q);
    phase -= 1;
    std::cout << "phase: " << phase <<  std::endl;
    Utils::negacyclic_rotate_poly(rot_poly, poly.lookup_polynomial, N, phase); 
    std::cout << "Decoding: " << encoding.decode_message(rot_poly[0]) << std::endl; 
    std::cout << "rot_poly: " << Utils::to_string(rot_poly, N) << std::endl;  

    
    std::cout << "Encrypting: 1" << std::endl;
    phase = encoding.encode_message(1);
    phase = round(((double)phase * (2*N))/Q);
    Utils::negacyclic_rotate_poly(rot_poly, poly.lookup_polynomial, N, phase); 
    std::cout << "Decoding: " << encoding.decode_message(rot_poly[0]) << std::endl; 
    std::cout << "rot_poly: " << Utils::to_string(rot_poly, N) << std::endl;  

    std::cout << "Encrypting: 2" << std::endl;
    phase = encoding.encode_message(2);
    phase = round(((double)phase * (2*N))/Q);
    Utils::negacyclic_rotate_poly(rot_poly, poly.lookup_polynomial, N, phase); 
    std::cout << "Decoding: " << encoding.decode_message(rot_poly[0]) << std::endl; 
    std::cout << "rot_poly: " << Utils::to_string(rot_poly, N) << std::endl;  

    std::cout << "Encrypting: 3" << std::endl;
    phase = encoding.encode_message(3);
    phase = round(((double)phase * (2*N))/Q);
    Utils::negacyclic_rotate_poly(rot_poly, poly.lookup_polynomial, N, phase); 
    std::cout << "Decoding: " << encoding.decode_message(rot_poly[0]) << std::endl; 
    std::cout << "rot_poly: " << Utils::to_string(rot_poly, N) << std::endl;  

}


int main(){

    test_negacyclic_rotate_poly();
    test_rot_poly();
    test_eval_poly();
}