#include <cassert>
#include <iostream>
#include "fhe_context.h"

using namespace fhe_deck;

void
run_B(void)
{
    FHEContext context;

    context.generate_context(tfhe_11_B);
    std::cout << "[+] Parameters tfhe_11_B" << std::endl;

    auto ct = context.encrypt(0);
    assert(ct.is_lwe_ct);
    std::cout << "[>] LWE parameters (secret key)" << std::endl;
    std::cout << "n: " << ct.lwe_c->param->dim << std::endl;
    std::cout << "Q: " << ct.lwe_c->param->modulus << std::endl;
    std::cout << "dist: " << ct.lwe_c->param->key_d << std::endl;
    std::cout << "stddev: " << ct.lwe_c->param->stddev << std::endl;
    assert(ct.lwe_c->param->key_d == ternary);

    ct = context.encrypt_public(0);
    assert(ct.is_lwe_ct);
    std::cout << "[>] LWE parameters (public key)" << std::endl;
    std::cout << "n: " << ct.lwe_c->param->dim << std::endl;
    std::cout << "Q: " << ct.lwe_c->param->modulus << std::endl;
    std::cout << "dist: " << ct.lwe_c->param->key_d << std::endl;
    std::cout << "stddev: " << ct.lwe_c->param->stddev << std::endl;
    assert(ct.lwe_c->param->key_d == binary);
}

void
run_NTT(void)
{
    FHEContext context;

    context.generate_context(tfhe_11_NTT);
    std::cout << "[+] Parameters tfhe_11_NTT" << std::endl;

    auto ct = context.encrypt(0);
    assert(ct.is_lwe_ct);
    std::cout << "[>] LWE parameters (secret key)" << std::endl;
    std::cout << "n: " << ct.lwe_c->param->dim << std::endl;
    std::cout << "Q: " << ct.lwe_c->param->modulus << std::endl;
    std::cout << "dist: " << ct.lwe_c->param->key_d << std::endl;
    std::cout << "stddev: " << ct.lwe_c->param->stddev << std::endl;

    ct = context.encrypt_public(0);
    assert(ct.is_lwe_ct);
    std::cout << "[>] LWE parameters (public key)" << std::endl;
    std::cout << "n: " << ct.lwe_c->param->dim << std::endl;
    std::cout << "Q: " << ct.lwe_c->param->modulus << std::endl;
    std::cout << "dist: " << ct.lwe_c->param->key_d << std::endl;
    std::cout << "stddev: " << ct.lwe_c->param->stddev << std::endl;
}

int
main(void)
{

    run_B();
    run_NTT();

    return 0;
}
