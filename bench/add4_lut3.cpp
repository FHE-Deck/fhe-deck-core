#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_add4_lut3(FHEContext& ctx, uint8_t a = 0, uint8_t b = 0)
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

    std::vector<RotationPoly> lut0;
    std::vector<long (*)(long)> flut0;
    auto lut0idx0 = [](long I) -> long {
        /* GATE 8 (LUT2 _26_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut0.push_back(ctx.genrate_lut(lut0idx0));
    flut0.push_back(lut0idx0);
    auto lut0idx1 = [](long I) -> long {
        /* GATE 4 (LUT2 _22_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut0.push_back(ctx.genrate_lut(lut0idx1));
    flut0.push_back(lut0idx1);
    auto fvec0 = [flut0](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut0[i](I));
        return ret;
    };

    std::cerr << "\rLUT0   ";
    Ciphertext gin0 = 1 * ct_a0 + 2 * ct_b0;
    std::vector<Ciphertext> gout0 = ctx.eval_lut_amortized(&gin0, lut0);

    std::vector<RotationPoly> lut1;
    std::vector<long (*)(long)> flut1;
    auto lut1idx0 = [](long I) -> long {
        /* GATE 5 (LUT3 _23_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut1.push_back(ctx.genrate_lut(lut1idx0));
    flut1.push_back(lut1idx0);
    auto lut1idx1 = [](long I) -> long {
        /* GATE 3 (LUT3 _21_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut1.push_back(ctx.genrate_lut(lut1idx1));
    flut1.push_back(lut1idx1);
    auto fvec1 = [flut1](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut1[i](I));
        return ret;
    };

    std::cerr << "\rLUT1   ";
    Ciphertext gin1 = 1 * gout0[1] + 2 * ct_a1 + 4 * ct_b1;
    std::vector<Ciphertext> gout1 = ctx.eval_lut_amortized(&gin1, lut1);

    std::vector<RotationPoly> lut2;
    std::vector<long (*)(long)> flut2;
    auto lut2idx0 = [](long I) -> long {
        /* GATE 6 (LUT3 _24_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut2.push_back(ctx.genrate_lut(lut2idx0));
    flut2.push_back(lut2idx0);
    auto lut2idx1 = [](long I) -> long {
        /* GATE 2 (LUT3 _20_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut2.push_back(ctx.genrate_lut(lut2idx1));
    flut2.push_back(lut2idx1);
    auto fvec2 = [flut2](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut2[i](I));
        return ret;
    };

    std::cerr << "\rLUT2   ";
    Ciphertext gin2 = 1 * gout1[1] + 2 * ct_a2 + 4 * ct_b2;
    std::vector<Ciphertext> gout2 = ctx.eval_lut_amortized(&gin2, lut2);

    std::vector<RotationPoly> lut3;
    std::vector<long (*)(long)> flut3;
    auto lut3idx0 = [](long I) -> long {
        /* GATE 1 (LUT3 _19_ INIT 0xd4 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut3.push_back(ctx.genrate_lut(lut3idx0));
    flut3.push_back(lut3idx0);
    auto lut3idx1 = [](long I) -> long {
        /* GATE 7 (LUT3 _25_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut3.push_back(ctx.genrate_lut(lut3idx1));
    flut3.push_back(lut3idx1);
    auto fvec3 = [flut3](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut3[i](I));
        return ret;
    };

    std::cerr << "\rLUT3   ";
    Ciphertext gin3 = 1 * gout2[1] + 2 * ct_a3 + 4 * ct_b3;
    std::vector<Ciphertext> gout3 = ctx.eval_lut_amortized(&gin3, lut3);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(ctx.decrypt(&gout0[0])); /* out0 */
    test_out.push_back(ctx.decrypt(&gout1[0])); /* out1 */
    test_out.push_back(ctx.decrypt(&gout2[0])); /* out2 */
    test_out.push_back(ctx.decrypt(&gout3[1])); /* out3 */
    test_out.push_back(ctx.decrypt(&gout3[0])); /* out4 */
    return test_out;
}

static void
BM_add4_lut3(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(rlwe_hom_acc_scheme_C_11_NTT);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(8);

    for (auto _ : state) {
        test_add4_lut3(ctx);
    }
}

BENCHMARK(BM_add4_lut3)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();