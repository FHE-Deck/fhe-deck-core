#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_image_gaussian_lut3fa(FHEContext& ctx, std::vector<uint64_t> window = { 0 })
{
    Ciphertext ct_window0 = ctx.encrypt_public((window[0] >> 0) & 1);
    Ciphertext ct_window1 = ctx.encrypt_public((window[0] >> 1) & 1);
    Ciphertext ct_window2 = ctx.encrypt_public((window[0] >> 2) & 1);
    Ciphertext ct_window3 = ctx.encrypt_public((window[0] >> 3) & 1);
    Ciphertext ct_window4 = ctx.encrypt_public((window[0] >> 4) & 1);
    Ciphertext ct_window5 = ctx.encrypt_public((window[0] >> 5) & 1);
    Ciphertext ct_window6 = ctx.encrypt_public((window[0] >> 6) & 1);
    Ciphertext ct_window7 = ctx.encrypt_public((window[0] >> 7) & 1);
    Ciphertext ct_window8 = ctx.encrypt_public((window[0] >> 8) & 1);
    Ciphertext ct_window9 = ctx.encrypt_public((window[0] >> 9) & 1);
    Ciphertext ct_window10 = ctx.encrypt_public((window[0] >> 10) & 1);
    Ciphertext ct_window11 = ctx.encrypt_public((window[0] >> 11) & 1);
    Ciphertext ct_window12 = ctx.encrypt_public((window[0] >> 12) & 1);
    Ciphertext ct_window13 = ctx.encrypt_public((window[0] >> 13) & 1);
    Ciphertext ct_window14 = ctx.encrypt_public((window[0] >> 14) & 1);
    Ciphertext ct_window15 = ctx.encrypt_public((window[0] >> 15) & 1);
    Ciphertext ct_window16 = ctx.encrypt_public((window[0] >> 16) & 1);
    Ciphertext ct_window17 = ctx.encrypt_public((window[0] >> 17) & 1);
    Ciphertext ct_window18 = ctx.encrypt_public((window[0] >> 18) & 1);
    Ciphertext ct_window19 = ctx.encrypt_public((window[0] >> 19) & 1);
    Ciphertext ct_window20 = ctx.encrypt_public((window[0] >> 20) & 1);
    Ciphertext ct_window21 = ctx.encrypt_public((window[0] >> 21) & 1);
    Ciphertext ct_window22 = ctx.encrypt_public((window[0] >> 22) & 1);
    Ciphertext ct_window23 = ctx.encrypt_public((window[0] >> 23) & 1);
    Ciphertext ct_window24 = ctx.encrypt_public((window[0] >> 24) & 1);
    Ciphertext ct_window25 = ctx.encrypt_public((window[0] >> 25) & 1);
    Ciphertext ct_window26 = ctx.encrypt_public((window[0] >> 26) & 1);
    Ciphertext ct_window27 = ctx.encrypt_public((window[0] >> 27) & 1);
    Ciphertext ct_window28 = ctx.encrypt_public((window[0] >> 28) & 1);
    Ciphertext ct_window29 = ctx.encrypt_public((window[0] >> 29) & 1);
    Ciphertext ct_window30 = ctx.encrypt_public((window[0] >> 30) & 1);
    Ciphertext ct_window31 = ctx.encrypt_public((window[0] >> 31) & 1);
    Ciphertext ct_window32 = ctx.encrypt_public((window[0] >> 32) & 1);
    Ciphertext ct_window33 = ctx.encrypt_public((window[0] >> 33) & 1);
    Ciphertext ct_window34 = ctx.encrypt_public((window[0] >> 34) & 1);
    Ciphertext ct_window35 = ctx.encrypt_public((window[0] >> 35) & 1);
    Ciphertext ct_window36 = ctx.encrypt_public((window[0] >> 36) & 1);
    Ciphertext ct_window37 = ctx.encrypt_public((window[0] >> 37) & 1);
    Ciphertext ct_window38 = ctx.encrypt_public((window[0] >> 38) & 1);
    Ciphertext ct_window39 = ctx.encrypt_public((window[0] >> 39) & 1);
    Ciphertext ct_window40 = ctx.encrypt_public((window[0] >> 40) & 1);
    Ciphertext ct_window41 = ctx.encrypt_public((window[0] >> 41) & 1);
    Ciphertext ct_window42 = ctx.encrypt_public((window[0] >> 42) & 1);
    Ciphertext ct_window43 = ctx.encrypt_public((window[0] >> 43) & 1);
    Ciphertext ct_window44 = ctx.encrypt_public((window[0] >> 44) & 1);
    Ciphertext ct_window45 = ctx.encrypt_public((window[0] >> 45) & 1);
    Ciphertext ct_window46 = ctx.encrypt_public((window[0] >> 46) & 1);
    Ciphertext ct_window47 = ctx.encrypt_public((window[0] >> 47) & 1);
    Ciphertext ct_window48 = ctx.encrypt_public((window[0] >> 48) & 1);
    Ciphertext ct_window49 = ctx.encrypt_public((window[0] >> 49) & 1);
    Ciphertext ct_window50 = ctx.encrypt_public((window[0] >> 50) & 1);
    Ciphertext ct_window51 = ctx.encrypt_public((window[0] >> 51) & 1);
    Ciphertext ct_window52 = ctx.encrypt_public((window[0] >> 52) & 1);
    Ciphertext ct_window53 = ctx.encrypt_public((window[0] >> 53) & 1);
    Ciphertext ct_window54 = ctx.encrypt_public((window[0] >> 54) & 1);
    Ciphertext ct_window55 = ctx.encrypt_public((window[0] >> 55) & 1);
    Ciphertext ct_window56 = ctx.encrypt_public((window[0] >> 56) & 1);
    Ciphertext ct_window57 = ctx.encrypt_public((window[0] >> 57) & 1);
    Ciphertext ct_window58 = ctx.encrypt_public((window[0] >> 58) & 1);
    Ciphertext ct_window59 = ctx.encrypt_public((window[0] >> 59) & 1);
    Ciphertext ct_window60 = ctx.encrypt_public((window[0] >> 60) & 1);
    Ciphertext ct_window61 = ctx.encrypt_public((window[0] >> 61) & 1);
    Ciphertext ct_window62 = ctx.encrypt_public((window[0] >> 62) & 1);
    Ciphertext ct_window63 = ctx.encrypt_public((window[0] >> 63) & 1);
    Ciphertext ct_window64 = ctx.encrypt_public((window[1] >> 0) & 1);
    Ciphertext ct_window65 = ctx.encrypt_public((window[1] >> 1) & 1);
    Ciphertext ct_window66 = ctx.encrypt_public((window[1] >> 2) & 1);
    Ciphertext ct_window67 = ctx.encrypt_public((window[1] >> 3) & 1);
    Ciphertext ct_window68 = ctx.encrypt_public((window[1] >> 4) & 1);
    Ciphertext ct_window69 = ctx.encrypt_public((window[1] >> 5) & 1);
    Ciphertext ct_window70 = ctx.encrypt_public((window[1] >> 6) & 1);
    Ciphertext ct_window71 = ctx.encrypt_public((window[1] >> 7) & 1);

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
    Ciphertext gin0 = 0 + 1 * ct_window56 + 2 * ct_window57 + 1 * ct_window65 + 2 * ct_window66;
    std::vector<Ciphertext> gout0 = ctx.eval_lut_amortized(&gin0, decomp);

    std::cerr << "\rFA1    ";
    Ciphertext gin1 = gout0[2] + 1 * ct_window58 + 2 * ct_window59 + 1 * ct_window67 + 2 * ct_window68;
    std::vector<Ciphertext> gout1 = ctx.eval_lut_amortized(&gin1, decomp);

    std::cerr << "\rFA2    ";
    Ciphertext gin2 = 0 + 1 * ct_window1 + 2 * ct_window2 + 1 * ct_window8 + 2 * ct_window9;
    std::vector<Ciphertext> gout2 = ctx.eval_lut_amortized(&gin2, decomp);

    std::cerr << "\rFA3    ";
    Ciphertext gin3 = 0 + 1 * ct_window40 + 2 * ct_window41 + 1 * ct_window49 + 2 * ct_window50;
    std::vector<Ciphertext> gout3 = ctx.eval_lut_amortized(&gin3, decomp);

    std::cerr << "\rFA4    ";
    Ciphertext gin4 = gout2[2] + 1 * ct_window3 + 2 * ct_window4 + 1 * ct_window10 + 2 * ct_window11;
    std::vector<Ciphertext> gout4 = ctx.eval_lut_amortized(&gin4, decomp);

    std::cerr << "\rFA5    ";
    Ciphertext gin5 = gout4[2] + 1 * ct_window5 + 2 * ct_window6 + 1 * ct_window12 + 2 * ct_window13;
    std::vector<Ciphertext> gout5 = ctx.eval_lut_amortized(&gin5, decomp);

    std::cerr << "\rFA6    ";
    Ciphertext gin6 = 0 + 1 * ct_window48 + 2 * gout3[0] + 1 * ct_window64 + 2 * gout0[0];
    std::vector<Ciphertext> gout6 = ctx.eval_lut_amortized(&gin6, decomp);

    std::cerr << "\rFA7    ";
    Ciphertext gin7 = 0 + 1 * ct_window0 + 2 * gout2[0] + 1 * ct_window16 + 2 * ct_window17;
    std::vector<Ciphertext> gout7 = ctx.eval_lut_amortized(&gin7, decomp);

    std::cerr << "\rFA8    ";
    Ciphertext gin8 = gout3[2] + 1 * ct_window42 + 2 * ct_window43 + 1 * ct_window51 + 2 * ct_window52;
    std::vector<Ciphertext> gout8 = ctx.eval_lut_amortized(&gin8, decomp);

    std::cerr << "\rFA9    ";
    Ciphertext gin9 = 0 + 1 * ct_window25 + 2 * ct_window26 + 1 * ct_window32 + 2 * ct_window33;
    std::vector<Ciphertext> gout9 = ctx.eval_lut_amortized(&gin9, decomp);

    std::cerr << "\rFA10    ";
    Ciphertext gin10 = gout7[2] + 1 * gout2[1] + 2 * gout4[0] + 1 * ct_window18 + 2 * ct_window19;
    std::vector<Ciphertext> gout10 = ctx.eval_lut_amortized(&gin10, decomp);

    std::cerr << "\rFA11    ";
    Ciphertext gin11 = gout1[2] + 1 * ct_window60 + 2 * ct_window61 + 1 * ct_window69 + 2 * ct_window70;
    std::vector<Ciphertext> gout11 = ctx.eval_lut_amortized(&gin11, decomp);

    std::cerr << "\rFA12    ";
    Ciphertext gin12 = gout10[2] + 1 * gout4[1] + 2 * gout5[0] + 1 * ct_window20 + 2 * ct_window21;
    std::vector<Ciphertext> gout12 = ctx.eval_lut_amortized(&gin12, decomp);

    std::cerr << "\rFA13    ";
    Ciphertext gin13 = gout9[2] + 1 * ct_window27 + 2 * ct_window28 + 1 * ct_window34 + 2 * ct_window35;
    std::vector<Ciphertext> gout13 = ctx.eval_lut_amortized(&gin13, decomp);

    std::cerr << "\rFA14    ";
    Ciphertext gin14 = gout13[2] + 1 * ct_window29 + 2 * ct_window30 + 1 * ct_window36 + 2 * ct_window37;
    std::vector<Ciphertext> gout14 = ctx.eval_lut_amortized(&gin14, decomp);

    std::cerr << "\rFA15    ";
    Ciphertext gin15 = gout14[2] + 1 * ct_window31 + 2 * 0 + 1 * ct_window38 + 2 * ct_window39;
    std::vector<Ciphertext> gout15 = ctx.eval_lut_amortized(&gin15, decomp);

    std::cerr << "\rFA16    ";
    Ciphertext gin16 = gout8[2] + 1 * ct_window44 + 2 * ct_window45 + 1 * ct_window53 + 2 * ct_window54;
    std::vector<Ciphertext> gout16 = ctx.eval_lut_amortized(&gin16, decomp);

    std::cerr << "\rFA17    ";
    Ciphertext gin17 = gout6[2] + 1 * gout3[1] + 2 * gout8[0] + 1 * gout0[1] + 2 * gout1[0];
    std::vector<Ciphertext> gout17 = ctx.eval_lut_amortized(&gin17, decomp);

    std::cerr << "\rFA18    ";
    Ciphertext gin18 = gout5[2] + 1 * ct_window7 + 2 * 0 + 1 * ct_window14 + 2 * ct_window15;
    std::vector<Ciphertext> gout18 = ctx.eval_lut_amortized(&gin18, decomp);

    std::cerr << "\rFA19    ";
    Ciphertext gin19 = gout16[2] + 1 * ct_window46 + 2 * ct_window47 + 1 * ct_window55 + 2 * 0;
    std::vector<Ciphertext> gout19 = ctx.eval_lut_amortized(&gin19, decomp);

    std::cerr << "\rFA20    ";
    Ciphertext gin20 = gout17[2] + 1 * gout8[1] + 2 * gout16[0] + 1 * gout1[1] + 2 * gout11[0];
    std::vector<Ciphertext> gout20 = ctx.eval_lut_amortized(&gin20, decomp);

    std::cerr << "\rFA21    ";
    Ciphertext gin21 = 0 + 1 * gout7[1] + 2 * gout10[0] + 1 * ct_window24 + 2 * gout9[0];
    std::vector<Ciphertext> gout21 = ctx.eval_lut_amortized(&gin21, decomp);

    std::cerr << "\rFA22    ";
    Ciphertext gin22 = gout11[2] + 1 * ct_window62 + 2 * ct_window63 + 1 * ct_window71 + 2 * 0;
    std::vector<Ciphertext> gout22 = ctx.eval_lut_amortized(&gin22, decomp);

    std::cerr << "\rFA23    ";
    Ciphertext gin23 = gout12[2] + 1 * gout5[1] + 2 * gout18[0] + 1 * ct_window22 + 2 * ct_window23;
    std::vector<Ciphertext> gout23 = ctx.eval_lut_amortized(&gin23, decomp);

    std::cerr << "\rFA24    ";
    Ciphertext gin24 = gout21[2] + 1 * gout10[1] + 2 * gout12[0] + 1 * gout9[1] + 2 * gout13[0];
    std::vector<Ciphertext> gout24 = ctx.eval_lut_amortized(&gin24, decomp);

    std::cerr << "\rFA25    ";
    Ciphertext gin25 = gout23[2] + 1 * gout18[1] + 2 * gout18[2] + 1 * 0 + 2 * 0;
    std::vector<Ciphertext> gout25 = ctx.eval_lut_amortized(&gin25, decomp);

    std::cerr << "\rFA26    ";
    Ciphertext gin26 = gout24[2] + 1 * gout12[1] + 2 * gout23[0] + 1 * gout13[1] + 2 * gout14[0];
    std::vector<Ciphertext> gout26 = ctx.eval_lut_amortized(&gin26, decomp);

    std::cerr << "\rFA27    ";
    Ciphertext gin27 = 0 + 1 * gout7[0] + 2 * gout21[0] + 1 * gout6[0] + 2 * gout6[1];
    std::vector<Ciphertext> gout27 = ctx.eval_lut_amortized(&gin27, decomp);

    std::cerr << "\rFA28    ";
    Ciphertext gin28 = gout20[2] + 1 * gout16[1] + 2 * gout19[0] + 1 * gout11[1] + 2 * gout22[0];
    std::vector<Ciphertext> gout28 = ctx.eval_lut_amortized(&gin28, decomp);

    std::cerr << "\rFA29    ";
    Ciphertext gin29 = gout27[2] + 1 * gout21[1] + 2 * gout24[0] + 1 * gout17[0] + 2 * gout17[1];
    std::vector<Ciphertext> gout29 = ctx.eval_lut_amortized(&gin29, decomp);

    std::cerr << "\rFA30    ";
    Ciphertext gin30 = gout26[2] + 1 * gout23[1] + 2 * gout25[0] + 1 * gout14[1] + 2 * gout15[0];
    std::vector<Ciphertext> gout30 = ctx.eval_lut_amortized(&gin30, decomp);

    std::cerr << "\rFA31    ";
    Ciphertext gin31 = gout30[2] + 1 * gout25[1] + 2 * gout25[2] + 1 * gout15[1] + 2 * gout15[2];
    std::vector<Ciphertext> gout31 = ctx.eval_lut_amortized(&gin31, decomp);

    std::cerr << "\rFA32    ";
    Ciphertext gin32 = gout29[2] + 1 * gout24[1] + 2 * gout26[0] + 1 * gout20[0] + 2 * gout20[1];
    std::vector<Ciphertext> gout32 = ctx.eval_lut_amortized(&gin32, decomp);

    std::cerr << "\rFA33    ";
    Ciphertext gin33 = gout28[2] + 1 * gout19[1] + 2 * gout19[2] + 1 * gout22[1] + 2 * gout22[2];
    std::vector<Ciphertext> gout33 = ctx.eval_lut_amortized(&gin33, decomp);

    std::cerr << "\rFA34    ";
    Ciphertext gin34 = gout32[2] + 1 * gout26[1] + 2 * gout30[0] + 1 * gout28[0] + 2 * gout28[1];
    std::vector<Ciphertext> gout34 = ctx.eval_lut_amortized(&gin34, decomp);

    std::cerr << "\rFA35    ";
    Ciphertext gin35 = gout34[2] + 1 * gout30[1] + 2 * gout31[0] + 1 * gout33[0] + 2 * gout33[1];
    std::vector<Ciphertext> gout35 = ctx.eval_lut_amortized(&gin35, decomp);

    std::cerr << "\rFA36    ";
    Ciphertext gin36 = gout35[2] + 1 * gout31[1] + 2 * gout31[2] + 1 * gout33[2] + 2 * 0;
    std::vector<Ciphertext> gout36 = ctx.eval_lut_amortized(&gin36, decomp);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(ctx.decrypt(&gout32[0])); /* out0 */
    test_out.push_back(ctx.decrypt(&gout32[1])); /* out1 */
    test_out.push_back(ctx.decrypt(&gout34[0])); /* out2 */
    test_out.push_back(ctx.decrypt(&gout34[1])); /* out3 */
    test_out.push_back(ctx.decrypt(&gout35[0])); /* out4 */
    test_out.push_back(ctx.decrypt(&gout35[1])); /* out5 */
    test_out.push_back(ctx.decrypt(&gout36[0])); /* out6 */
    test_out.push_back(ctx.decrypt(&gout36[1])); /* out7 */
    return test_out;
}

static void
BM_image_gaussian_lut3fa(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(tfhe_11_NTT_amortized);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(8);

    for (auto _ : state) {
        test_image_gaussian_lut3fa(ctx);
    }
}

BENCHMARK(BM_image_gaussian_lut3fa)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
