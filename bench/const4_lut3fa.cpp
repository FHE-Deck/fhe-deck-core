#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_const4_lut3fa(FHEContext& ctx, uint8_t a = 0)
{
    Ciphertext ct_a1 = ctx.encrypt_public((a >> 0) & 1);
    Ciphertext ct_a2 = ctx.encrypt_public((a >> 1) & 1);
    Ciphertext ct_a3 = ctx.encrypt_public((a >> 2) & 1);

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

    std::vector<RotationPoly> lut0;
    std::vector<long (*)(long)> flut0;
    auto lut0idx0 = [](long I) -> long {
        /* GATE 3 (LUT3 _10_ INIT 0x87 PERM 201) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut0.push_back(ctx.genrate_lut(lut0idx0));
    flut0.push_back(lut0idx0);
    auto lut0idx1 = [](long I) -> long {
        /* GATE 1 (LUT3 _08_ INIT 0xf8 PERM 201) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut0.push_back(ctx.genrate_lut(lut0idx1));
    flut0.push_back(lut0idx1);
    auto lut0idx2 = [](long I) -> long {
        /* GATE 2 (LUT2 _09_ INIT 0x6 PERM 20) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut0.push_back(ctx.genrate_lut(lut0idx2));
    flut0.push_back(lut0idx2);
    auto fvec0 = [flut0](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 3; ++i)
            ret.push_back(flut0[i](I));
        return ret;
    };

    std::cerr << "\rLUT0   ";
    Ciphertext gin0 = 1 * ct_a2 + 2 * ct_a3 + 4 * ct_a1;
    std::vector<Ciphertext> gout0 = ctx.eval_lut_amortized(&gin0, lut0);

    std::cerr << "\rINV1   ";
    std::vector<Ciphertext> gout1;
    gout1.push_back(1 - ct_a1);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(ctx.decrypt(&gout1[0])); /* out1 */
    test_out.push_back(ctx.decrypt(&gout0[2])); /* out2 */
    test_out.push_back(ctx.decrypt(&gout0[0])); /* out3 */
    test_out.push_back(ctx.decrypt(&gout0[1])); /* out4 */
    return test_out;
}

static void
BM_const4_lut3fa(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(tfhe_11_NTT_amortized);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(8);

    for (auto _ : state) {
        test_const4_lut3fa(ctx);
    }
}

BENCHMARK(BM_const4_lut3fa)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
