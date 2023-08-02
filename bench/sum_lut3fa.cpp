#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_sum_lut3fa(FHEContext& ctx, uint32_t a = 0, uint32_t b = 0)
{
    Ciphertext ct_a0 = ctx.encrypt_public((a >> 0) & 1);
    Ciphertext ct_a1 = ctx.encrypt_public((a >> 1) & 1);
    Ciphertext ct_a2 = ctx.encrypt_public((a >> 2) & 1);
    Ciphertext ct_a3 = ctx.encrypt_public((a >> 3) & 1);
    Ciphertext ct_a4 = ctx.encrypt_public((a >> 4) & 1);
    Ciphertext ct_a5 = ctx.encrypt_public((a >> 5) & 1);
    Ciphertext ct_a6 = ctx.encrypt_public((a >> 6) & 1);
    Ciphertext ct_a7 = ctx.encrypt_public((a >> 7) & 1);
    Ciphertext ct_a8 = ctx.encrypt_public((a >> 8) & 1);
    Ciphertext ct_a9 = ctx.encrypt_public((a >> 9) & 1);
    Ciphertext ct_a10 = ctx.encrypt_public((a >> 10) & 1);
    Ciphertext ct_a11 = ctx.encrypt_public((a >> 11) & 1);
    Ciphertext ct_a12 = ctx.encrypt_public((a >> 12) & 1);
    Ciphertext ct_a13 = ctx.encrypt_public((a >> 13) & 1);
    Ciphertext ct_a14 = ctx.encrypt_public((a >> 14) & 1);
    Ciphertext ct_a15 = ctx.encrypt_public((a >> 15) & 1);
    Ciphertext ct_a16 = ctx.encrypt_public((a >> 16) & 1);
    Ciphertext ct_a17 = ctx.encrypt_public((a >> 17) & 1);
    Ciphertext ct_a18 = ctx.encrypt_public((a >> 18) & 1);
    Ciphertext ct_a19 = ctx.encrypt_public((a >> 19) & 1);
    Ciphertext ct_a20 = ctx.encrypt_public((a >> 20) & 1);
    Ciphertext ct_a21 = ctx.encrypt_public((a >> 21) & 1);
    Ciphertext ct_a22 = ctx.encrypt_public((a >> 22) & 1);
    Ciphertext ct_a23 = ctx.encrypt_public((a >> 23) & 1);
    Ciphertext ct_a24 = ctx.encrypt_public((a >> 24) & 1);
    Ciphertext ct_a25 = ctx.encrypt_public((a >> 25) & 1);
    Ciphertext ct_a26 = ctx.encrypt_public((a >> 26) & 1);
    Ciphertext ct_a27 = ctx.encrypt_public((a >> 27) & 1);
    Ciphertext ct_a28 = ctx.encrypt_public((a >> 28) & 1);
    Ciphertext ct_a29 = ctx.encrypt_public((a >> 29) & 1);
    Ciphertext ct_a30 = ctx.encrypt_public((a >> 30) & 1);
    Ciphertext ct_a31 = ctx.encrypt_public((a >> 31) & 1);
    Ciphertext ct_b0 = ctx.encrypt_public((b >> 0) & 1);
    Ciphertext ct_b1 = ctx.encrypt_public((b >> 1) & 1);
    Ciphertext ct_b2 = ctx.encrypt_public((b >> 2) & 1);
    Ciphertext ct_b3 = ctx.encrypt_public((b >> 3) & 1);
    Ciphertext ct_b4 = ctx.encrypt_public((b >> 4) & 1);
    Ciphertext ct_b5 = ctx.encrypt_public((b >> 5) & 1);
    Ciphertext ct_b6 = ctx.encrypt_public((b >> 6) & 1);
    Ciphertext ct_b7 = ctx.encrypt_public((b >> 7) & 1);
    Ciphertext ct_b8 = ctx.encrypt_public((b >> 8) & 1);
    Ciphertext ct_b9 = ctx.encrypt_public((b >> 9) & 1);
    Ciphertext ct_b10 = ctx.encrypt_public((b >> 10) & 1);
    Ciphertext ct_b11 = ctx.encrypt_public((b >> 11) & 1);
    Ciphertext ct_b12 = ctx.encrypt_public((b >> 12) & 1);
    Ciphertext ct_b13 = ctx.encrypt_public((b >> 13) & 1);
    Ciphertext ct_b14 = ctx.encrypt_public((b >> 14) & 1);
    Ciphertext ct_b15 = ctx.encrypt_public((b >> 15) & 1);
    Ciphertext ct_b16 = ctx.encrypt_public((b >> 16) & 1);
    Ciphertext ct_b17 = ctx.encrypt_public((b >> 17) & 1);
    Ciphertext ct_b18 = ctx.encrypt_public((b >> 18) & 1);
    Ciphertext ct_b19 = ctx.encrypt_public((b >> 19) & 1);
    Ciphertext ct_b20 = ctx.encrypt_public((b >> 20) & 1);
    Ciphertext ct_b21 = ctx.encrypt_public((b >> 21) & 1);
    Ciphertext ct_b22 = ctx.encrypt_public((b >> 22) & 1);
    Ciphertext ct_b23 = ctx.encrypt_public((b >> 23) & 1);
    Ciphertext ct_b24 = ctx.encrypt_public((b >> 24) & 1);
    Ciphertext ct_b25 = ctx.encrypt_public((b >> 25) & 1);
    Ciphertext ct_b26 = ctx.encrypt_public((b >> 26) & 1);
    Ciphertext ct_b27 = ctx.encrypt_public((b >> 27) & 1);
    Ciphertext ct_b28 = ctx.encrypt_public((b >> 28) & 1);
    Ciphertext ct_b29 = ctx.encrypt_public((b >> 29) & 1);
    Ciphertext ct_b30 = ctx.encrypt_public((b >> 30) & 1);
    Ciphertext ct_b31 = ctx.encrypt_public((b >> 31) & 1);

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

    std::cerr << "\rFA2    ";
    Ciphertext gin2 = gout1[2] + 1 * ct_a4 + 2 * ct_a5 + 1 * ct_b4 + 2 * ct_b5;
    std::vector<Ciphertext> gout2 = ctx.eval_lut_amortized(&gin2, decomp);

    std::cerr << "\rFA3    ";
    Ciphertext gin3 = gout2[2] + 1 * ct_a6 + 2 * ct_a7 + 1 * ct_b6 + 2 * ct_b7;
    std::vector<Ciphertext> gout3 = ctx.eval_lut_amortized(&gin3, decomp);

    std::cerr << "\rFA4    ";
    Ciphertext gin4 = gout3[2] + 1 * ct_a8 + 2 * ct_a9 + 1 * ct_b8 + 2 * ct_b9;
    std::vector<Ciphertext> gout4 = ctx.eval_lut_amortized(&gin4, decomp);

    std::cerr << "\rFA5    ";
    Ciphertext gin5 = gout4[2] + 1 * ct_a10 + 2 * ct_a11 + 1 * ct_b10 + 2 * ct_b11;
    std::vector<Ciphertext> gout5 = ctx.eval_lut_amortized(&gin5, decomp);

    std::cerr << "\rFA6    ";
    Ciphertext gin6 = gout5[2] + 1 * ct_a12 + 2 * ct_a13 + 1 * ct_b12 + 2 * ct_b13;
    std::vector<Ciphertext> gout6 = ctx.eval_lut_amortized(&gin6, decomp);

    std::cerr << "\rFA7    ";
    Ciphertext gin7 = gout6[2] + 1 * ct_a14 + 2 * ct_a15 + 1 * ct_b14 + 2 * ct_b15;
    std::vector<Ciphertext> gout7 = ctx.eval_lut_amortized(&gin7, decomp);

    std::cerr << "\rFA8    ";
    Ciphertext gin8 = gout7[2] + 1 * ct_a16 + 2 * ct_a17 + 1 * ct_b16 + 2 * ct_b17;
    std::vector<Ciphertext> gout8 = ctx.eval_lut_amortized(&gin8, decomp);

    std::cerr << "\rFA9    ";
    Ciphertext gin9 = gout8[2] + 1 * ct_a18 + 2 * ct_a19 + 1 * ct_b18 + 2 * ct_b19;
    std::vector<Ciphertext> gout9 = ctx.eval_lut_amortized(&gin9, decomp);

    std::cerr << "\rFA10    ";
    Ciphertext gin10 = gout9[2] + 1 * ct_a20 + 2 * ct_a21 + 1 * ct_b20 + 2 * ct_b21;
    std::vector<Ciphertext> gout10 = ctx.eval_lut_amortized(&gin10, decomp);

    std::cerr << "\rFA11    ";
    Ciphertext gin11 = gout10[2] + 1 * ct_a22 + 2 * ct_a23 + 1 * ct_b22 + 2 * ct_b23;
    std::vector<Ciphertext> gout11 = ctx.eval_lut_amortized(&gin11, decomp);

    std::cerr << "\rFA12    ";
    Ciphertext gin12 = gout11[2] + 1 * ct_a24 + 2 * ct_a25 + 1 * ct_b24 + 2 * ct_b25;
    std::vector<Ciphertext> gout12 = ctx.eval_lut_amortized(&gin12, decomp);

    std::cerr << "\rFA13    ";
    Ciphertext gin13 = gout12[2] + 1 * ct_a26 + 2 * ct_a27 + 1 * ct_b26 + 2 * ct_b27;
    std::vector<Ciphertext> gout13 = ctx.eval_lut_amortized(&gin13, decomp);

    std::cerr << "\rFA14    ";
    Ciphertext gin14 = gout13[2] + 1 * ct_a28 + 2 * ct_a29 + 1 * ct_b28 + 2 * ct_b29;
    std::vector<Ciphertext> gout14 = ctx.eval_lut_amortized(&gin14, decomp);

    std::cerr << "\rFA15    ";
    Ciphertext gin15 = gout14[2] + 1 * ct_a30 + 2 * ct_a31 + 1 * ct_b30 + 2 * ct_b31;
    std::vector<Ciphertext> gout15 = ctx.eval_lut_amortized(&gin15, decomp);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(ctx.decrypt(&gout0[0])); /* out0 */
    test_out.push_back(ctx.decrypt(&gout0[1])); /* out1 */
    test_out.push_back(ctx.decrypt(&gout1[0])); /* out2 */
    test_out.push_back(ctx.decrypt(&gout1[1])); /* out3 */
    test_out.push_back(ctx.decrypt(&gout2[0])); /* out4 */
    test_out.push_back(ctx.decrypt(&gout2[1])); /* out5 */
    test_out.push_back(ctx.decrypt(&gout3[0])); /* out6 */
    test_out.push_back(ctx.decrypt(&gout3[1])); /* out7 */
    test_out.push_back(ctx.decrypt(&gout4[0])); /* out8 */
    test_out.push_back(ctx.decrypt(&gout4[1])); /* out9 */
    test_out.push_back(ctx.decrypt(&gout5[0])); /* out10 */
    test_out.push_back(ctx.decrypt(&gout5[1])); /* out11 */
    test_out.push_back(ctx.decrypt(&gout6[0])); /* out12 */
    test_out.push_back(ctx.decrypt(&gout6[1])); /* out13 */
    test_out.push_back(ctx.decrypt(&gout7[0])); /* out14 */
    test_out.push_back(ctx.decrypt(&gout7[1])); /* out15 */
    test_out.push_back(ctx.decrypt(&gout8[0])); /* out16 */
    test_out.push_back(ctx.decrypt(&gout8[1])); /* out17 */
    test_out.push_back(ctx.decrypt(&gout9[0])); /* out18 */
    test_out.push_back(ctx.decrypt(&gout9[1])); /* out19 */
    test_out.push_back(ctx.decrypt(&gout10[0])); /* out20 */
    test_out.push_back(ctx.decrypt(&gout10[1])); /* out21 */
    test_out.push_back(ctx.decrypt(&gout11[0])); /* out22 */
    test_out.push_back(ctx.decrypt(&gout11[1])); /* out23 */
    test_out.push_back(ctx.decrypt(&gout12[0])); /* out24 */
    test_out.push_back(ctx.decrypt(&gout12[1])); /* out25 */
    test_out.push_back(ctx.decrypt(&gout13[0])); /* out26 */
    test_out.push_back(ctx.decrypt(&gout13[1])); /* out27 */
    test_out.push_back(ctx.decrypt(&gout14[0])); /* out28 */
    test_out.push_back(ctx.decrypt(&gout14[1])); /* out29 */
    test_out.push_back(ctx.decrypt(&gout15[0])); /* out30 */
    test_out.push_back(ctx.decrypt(&gout15[1])); /* out31 */
    return test_out;
}

static void
BM_sum_lut3fa(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(tfhe_11_NTT_amortized);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(8);

    for (auto _ : state) {
        test_sum_lut3fa(ctx);
    }
}

BENCHMARK(BM_sum_lut3fa)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
