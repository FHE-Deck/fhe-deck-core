
#include "cassert"

#include "fhe_context.h"
#include "lwe_to_rlwe_keyswitch.h"

#include <chrono>

#define assertm(exp, msg) assert(((void)msg, exp))

using namespace fhe_deck;
using namespace std::chrono;

int main(int argc, char** argv) {

    FHEContext ctx;
    ctx.generate_context(FHENamedParams::tfhe_11_KS);
    std::cout << "FHE Parameters Generated" << std::endl;

    std::shared_ptr<KSFunctionalBootstrapPublicKey> ks_pk = std::dynamic_pointer_cast<KSFunctionalBootstrapPublicKey>(ctx.config->eval_key.bootstrap_pk);

    PlaintextEncoding encoding = ctx.get_default_plaintext_encoding();
    int64_t t = encoding.plaintext_space;
    Ciphertext lwe_out = ctx.encrypt(0);
    int64_t N = lwe_out.lwe_c->param->dim;
    int64_t Q = lwe_out.lwe_c->param->modulus;

    // some function
    FunctionalAccumulator::BootFunction F_in = [](long a, long b) { return  ((a*a ^ 0x41) + a * 3 + 7 * (a & 0xa)) % b;};


    std::shared_ptr<VectorCTAccumulator> acc = std::make_shared<FunctionalAccumulator>(F_in, N, Q, encoding);
    std::shared_ptr<HomomorphicAccumulator> hom_acc = std::make_shared<HomomorphicAccumulator>(acc);

    // check every case
    int64_t correct = 0;
    int64_t delta = Q / t;
    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();
    int64_t elapsed = 0; 
    for (int32_t i = 0; i < t; i++) {
        int32_t message = i;
        Ciphertext lwe_in = ctx.encrypt(message, encoding);
 
        start = high_resolution_clock::now();
        ks_pk->full_domain_bootstrap(lwe_out.lwe_c.get(), acc, lwe_in.lwe_c.get(), encoding); 
        stop = high_resolution_clock::now();
        elapsed = elapsed + duration_cast<milliseconds>(stop-start).count();

        int64_t dec = ctx.config->secret_key->partial_decrypt(lwe_out.lwe_c.get());
        dec = dec % Q;

        // safe decode
        int64_t round_floor = dec - dec % delta;
        int64_t round_ceil = round_floor + delta;
        int64_t dec_pt = (round_ceil - dec) < (dec - round_floor) ? round_ceil / delta : round_floor / delta;

        int64_t target = F_in(message, t);
        long double expected_target = target * delta;
        long double actual = dec;
        long double relative_error = (std::abs(actual - expected_target)) / expected_target;

        //std::cout << i << " " << dec << " " << dec_pt << " " << target << " " << relative_error << std::endl;

        correct += (target == dec_pt);
    }
    
    //auto elapsed = duration_cast<milliseconds>(stop-start).count();
    std::cout << "[KS] Correctly mapped " << correct << "/" << t << " values." << std::endl;
    if (correct == t) {
        std::cout << "[KS] Bootstrap OK. Took " << elapsed << "ms in total and " << elapsed/t << " ms per bootstrap." << std::endl; 
    }
}