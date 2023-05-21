#include "../include/rotation_poly.h"
#include <iostream>



void test_rot_poly(){
    std::cout << "=============== test_rot_poly =================" << std::endl;
    long N = 16;
    long Q = 64;
    long t = 4;

    auto fp = [](long m, long t) -> long {
        return m % t;
    };


    long* poly_1 = rotation_poly::rot_identity(t, N, Q);
    rotation_poly poly_2(fp, t, N, Q);    

    std::cout << "poly_1: " << utils::to_string(poly_1, N) << std::endl ;
    std::cout << "poly_2: " << utils::to_string(poly_2.lookup_polynomial, N) << std::endl;
    std::cout << "flip_scale...." << std::endl;
    poly_2.flip_scale();
    std::cout << "poly_2: " << utils::to_string(poly_2.lookup_polynomial, N) << std::endl;
    std::cout << "flip_scale again...." << std::endl;
    poly_2.flip_scale();
    std::cout << "poly_2: " << utils::to_string(poly_2.lookup_polynomial, N) << std::endl;

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
    std::cout << "poly:    " << utils::to_string(poly, N) << std::endl ;

    long* rot_poly = new long[N];

    // Note that rot may be in [0, 2*N)!
    int rot = 16 + 4;
    utils::negacyclic_rotate_poly(rot_poly, poly, N, rot);
    std::cout << "rot_poly: " << utils::to_string(rot_poly, N) << std::endl ;
 
}



int main(){

    test_negacyclic_rotate_poly();
    test_rot_poly();
}