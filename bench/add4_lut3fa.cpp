#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_add4_lut3fa(FHEContext& ctx, uint8_t a = 0, uint8_t b = 0)
{
    Ciphertext ct_a0 = ctx.encrypt_public((a >> 0) & 1);
    Ciphertext ct_a1 = ctx.encrypt_public((a >> 1) & 1);
    Ciphertext ct_a2 = ctx.encrypt_public((a >> 2) & 1);
    Ciphertext ct_a3 = ctx.encrypt_public((a >> 3) & 1);
    Ciphertext ct_b0 = ctx.encrypt_public((b >> 0) & 1);
    Ciphertext ct_b1 = ctx.encrypt_public((b >> 1) & 1);
    Ciphertext ct_b2 = ctx.encrypt_public((b >> 2) & 1);
    Ciphertext ct_b3 = ctx.encrypt_public((b >> 3) & 1);

    std::vector<RotationPoly> decomp;
    std::vector<long (*)(long)> fdecomp;
    auto decomp0 = [](long I) -> long {
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    decomp.push_back(ctx.genrate_lut(decomp0));
    fdecomp.push_back(decomp0);
    auto decomp1 = [](long I) -> long {
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    decomp.push_back(ctx.genrate_lut(decomp1));
    fdecomp.push_back(decomp1);
    auto decomp2 = [](long I) -> long {
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    decomp.push_back(ctx.genrate_lut(decomp2));
    fdecomp.push_back(decomp2);
    auto vdecomp = [fdecomp](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 3; ++i)
            ret.push_back(fdecomp[i](I));
        return ret;
    };

    std::cerr << "\rFA0    ";
    Ciphertext gin0 = 0 + 1 * ct_a0 + 2 * ct_a1 + 1 * ct_b0 + 2 * ct_b1;
    std::vector<Ciphertext> gout0 = ctx.eval_lut_amortized(&gin0, decomp);

    std::cerr << "\rFA1    ";
    Ciphertext gin1 = gout0[2] + 1 * ct_a2 + 2 * ct_a3 + 1 * ct_b2 + 2 * ct_b3;
    std::vector<Ciphertext> gout1 = ctx.eval_lut_amortized(&gin1, decomp);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(ctx.decrypt(&gout0[0])); /* out0 */
    test_out.push_back(ctx.decrypt(&gout0[1])); /* out1 */
    test_out.push_back(ctx.decrypt(&gout1[0])); /* out2 */
    test_out.push_back(ctx.decrypt(&gout1[1])); /* out3 */
    test_out.push_back(ctx.decrypt(&gout1[2])); /* out4 */
    return test_out;
}

static void
BM_add4_lut3fa(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(rlwe_hom_acc_scheme_C_11_NTT);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(8);

    for (auto _ : state) {
        test_add4_lut3fa(ctx);
    }
}

BENCHMARK(BM_add4_lut3fa)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
