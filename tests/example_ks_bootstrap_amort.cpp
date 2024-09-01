
#include "cassert"

#include "fhe_context.h"
#include "lwe_to_rlwe_keyswitch.h"

#define assertm(exp, msg) assert(((void)msg, exp))

using namespace fhe_deck;

int main(int argc, char** argv) {

    FHEContext ctx;
    ctx.generate_context(FHENamedParams::tfhe_11_KS_amortized); 
     
    std::shared_ptr<KSFunctionalBootstrapPublicKey> ks_pk = std::dynamic_pointer_cast<KSFunctionalBootstrapPublicKey>(ctx.config->eval_key.bootstrap_pk);

    auto encoding = ctx.get_default_plaintext_encoding();
    auto t = encoding.plaintext_space;
    auto lwe_out = ctx.encrypt(0);
    long N = lwe_out.lwe_c->param->dim;
    long Q = lwe_out.lwe_c->param->modulus;

    // some function
    std::function<long(long,long)> F_1 = [](long a, long b) { return  (a) % b;};
    std::function<long(long,long)> F_2 = [](long a, long b) { return  (a % 2) % b;};
    std::function<long(long,long)> F_3 = [](long a, long b) { return  ((a*a ^ 0x41) + a * 3 + 7 * (a & 0xa)) % b;};
    std::function<long(long,long)> F_4 = [](long a, long b) { return  (4 * (a / 4)) % b;};
    std::function<long(long,long)> F_5 = [](long a, long b) { return  (a + (a << 1) + (a >> 1)) % b;};

    std::vector<std::function<long(long,long)>> F_vec = {F_1, F_2, F_3, F_4, F_5};

    std::vector<std::shared_ptr<VectorCTAccumulator>> acc_vec;
    for(auto& F: F_vec) {
        acc_vec.push_back(std::make_shared<FunctionalAccumulator>(F, N, Q, encoding));
    }

    long delta = Q / t;
    auto message = rand() % encoding.plaintext_space;
    auto lwe_in = ctx.encrypt(message, encoding);

    auto start = std::chrono::high_resolution_clock::now();
    auto results = ks_pk->full_domain_bootstrap(acc_vec, lwe_in.lwe_c.get(), encoding); 
    auto stop = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    long correct = 0;
    for (int i = 0; i < F_vec.size(); i++) {

        long dec = ctx.config->secret_key->partial_decrypt(&results.at(i)) % Q;
        dec = dec % Q;

        // safe decode
        auto round_floor = dec - dec % delta;
        auto round_ceil = round_floor + delta;
        long dec_pt = (round_ceil - dec) < (dec - round_floor) ? round_ceil / delta : round_floor / delta;

        long target = F_vec[i](message, t);

        long double expected_target = target * delta;
        long double actual = dec;
        long double relative_error = (std::abs(actual - expected_target)) / expected_target;

        std::cout << i << " " << dec_pt << " " << target << " " << relative_error << std::endl;
        correct += dec_pt == target;
    }

    std::cout << "[Amort-KS] Mapped " << correct << " / " << F_vec.size() << " correctly " << std::endl;
    if (correct == F_vec.size()) {
        std::cout << "[Amort-KS] Amortized bootstrap OK" << std::endl;
    }
    std::cout << "Elapsed " << elapsed << " [ms]"  << std::endl;

}