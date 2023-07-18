#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_image_ricker_lut3fa(FHEContext& ctx, std::vector<uint64_t> window = { 0 })
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
    Ciphertext gin0 = 0 + 1 * ct_window56 + 2 * ct_window57 + 1 * ct_window64 + 2 * ct_window65;
    std::vector<Ciphertext> gout0 = ctx.eval_lut_amortized(&gin0, decomp);

    std::cerr << "\rFA1    ";
    Ciphertext gin1 = 0 + 1 * ct_window0 + 2 * ct_window1 + 1 * ct_window8 + 2 * ct_window9;
    std::vector<Ciphertext> gout1 = ctx.eval_lut_amortized(&gin1, decomp);

    std::cerr << "\rFA2    ";
    Ciphertext gin2 = gout0[2] + 1 * ct_window58 + 2 * ct_window59 + 1 * ct_window66 + 2 * ct_window67;
    std::vector<Ciphertext> gout2 = ctx.eval_lut_amortized(&gin2, decomp);

    std::cerr << "\rFA3    ";
    Ciphertext gin3 = gout1[2] + 1 * ct_window2 + 2 * ct_window3 + 1 * ct_window10 + 2 * ct_window11;
    std::vector<Ciphertext> gout3 = ctx.eval_lut_amortized(&gin3, decomp);

    std::cerr << "\rFA4    ";
    Ciphertext gin4 = gout2[2] + 1 * ct_window60 + 2 * ct_window61 + 1 * ct_window68 + 2 * ct_window69;
    std::vector<Ciphertext> gout4 = ctx.eval_lut_amortized(&gin4, decomp);

    std::cerr << "\rFA5    ";
    Ciphertext gin5 = gout4[2] + 1 * ct_window62 + 2 * ct_window63 + 1 * ct_window70 + 2 * ct_window71;
    std::vector<Ciphertext> gout5 = ctx.eval_lut_amortized(&gin5, decomp);

    std::cerr << "\rFA6    ";
    Ciphertext gin6 = 0 + 1 * ct_window16 + 2 * ct_window17 + 1 * ct_window24 + 2 * ct_window25;
    std::vector<Ciphertext> gout6 = ctx.eval_lut_amortized(&gin6, decomp);

    std::cerr << "\rFA7    ";
    Ciphertext gin7 = 0 + 1 * ct_window40 + 2 * ct_window41 + 1 * ct_window48 + 2 * ct_window49;
    std::vector<Ciphertext> gout7 = ctx.eval_lut_amortized(&gin7, decomp);

    std::cerr << "\rFA8    ";
    Ciphertext gin8 = gout3[2] + 1 * ct_window4 + 2 * ct_window5 + 1 * ct_window12 + 2 * ct_window13;
    std::vector<Ciphertext> gout8 = ctx.eval_lut_amortized(&gin8, decomp);

    std::cerr << "\rFA9    ";
    Ciphertext gin9 = 0 + 1 * gout7[0] + 2 * gout7[1] + 1 * gout0[0] + 2 * gout0[1];
    std::vector<Ciphertext> gout9 = ctx.eval_lut_amortized(&gin9, decomp);

    std::cerr << "\rFA10    ";
    Ciphertext gin10 = 0 + 1 * gout1[0] + 2 * gout1[1] + 1 * gout6[0] + 2 * gout6[1];
    std::vector<Ciphertext> gout10 = ctx.eval_lut_amortized(&gin10, decomp);

    std::cerr << "\rFA11    ";
    Ciphertext gin11 = gout7[2] + 1 * ct_window42 + 2 * ct_window43 + 1 * ct_window50 + 2 * ct_window51;
    std::vector<Ciphertext> gout11 = ctx.eval_lut_amortized(&gin11, decomp);

    std::cerr << "\rFA12    ";
    Ciphertext gin12 = gout6[2] + 1 * ct_window18 + 2 * ct_window19 + 1 * ct_window26 + 2 * ct_window27;
    std::vector<Ciphertext> gout12 = ctx.eval_lut_amortized(&gin12, decomp);

    std::cerr << "\rFA13    ";
    Ciphertext gin13 = gout9[2] + 1 * gout11[0] + 2 * gout11[1] + 1 * gout2[0] + 2 * gout2[1];
    std::vector<Ciphertext> gout13 = ctx.eval_lut_amortized(&gin13, decomp);

    std::cerr << "\rFA14    ";
    Ciphertext gin14 = gout10[2] + 1 * gout3[0] + 2 * gout3[1] + 1 * gout12[0] + 2 * gout12[1];
    std::vector<Ciphertext> gout14 = ctx.eval_lut_amortized(&gin14, decomp);

    std::cerr << "\rFA15    ";
    Ciphertext gin15 = gout11[2] + 1 * ct_window44 + 2 * ct_window45 + 1 * ct_window52 + 2 * ct_window53;
    std::vector<Ciphertext> gout15 = ctx.eval_lut_amortized(&gin15, decomp);

    std::cerr << "\rFA16    ";
    Ciphertext gin16 = gout8[2] + 1 * ct_window6 + 2 * ct_window7 + 1 * ct_window14 + 2 * ct_window15;
    std::vector<Ciphertext> gout16 = ctx.eval_lut_amortized(&gin16, decomp);

    std::cerr << "\rFA17    ";
    Ciphertext gin17 = gout15[2] + 1 * ct_window46 + 2 * ct_window47 + 1 * ct_window54 + 2 * ct_window55;
    std::vector<Ciphertext> gout17 = ctx.eval_lut_amortized(&gin17, decomp);

    std::cerr << "\rFA18    ";
    Ciphertext gin18 = 0 + 1 * gout10[0] + 2 * gout10[1] + 1 * gout9[0] + 2 * gout9[1];
    std::vector<Ciphertext> gout18 = ctx.eval_lut_amortized(&gin18, decomp);

    std::cerr << "\rFA19    ";
    Ciphertext gin19 = gout12[2] + 1 * ct_window20 + 2 * ct_window21 + 1 * ct_window28 + 2 * ct_window29;
    std::vector<Ciphertext> gout19 = ctx.eval_lut_amortized(&gin19, decomp);

    std::cerr << "\rFA20    ";
    Ciphertext gin20 = gout13[2] + 1 * gout15[0] + 2 * gout15[1] + 1 * gout4[0] + 2 * gout4[1];
    std::vector<Ciphertext> gout20 = ctx.eval_lut_amortized(&gin20, decomp);

    std::cerr << "\rFA21    ";
    Ciphertext gin21 = gout14[2] + 1 * gout8[0] + 2 * gout8[1] + 1 * gout19[0] + 2 * gout19[1];
    std::vector<Ciphertext> gout21 = ctx.eval_lut_amortized(&gin21, decomp);

    std::cerr << "\rFA22    ";
    Ciphertext gin22 = gout19[2] + 1 * ct_window22 + 2 * ct_window23 + 1 * ct_window30 + 2 * ct_window31;
    std::vector<Ciphertext> gout22 = ctx.eval_lut_amortized(&gin22, decomp);

    std::cerr << "\rFA23    ";
    Ciphertext gin23 = gout18[2] + 1 * gout14[0] + 2 * gout14[1] + 1 * gout13[0] + 2 * gout13[1];
    std::vector<Ciphertext> gout23 = ctx.eval_lut_amortized(&gin23, decomp);

    std::cerr << "\rFA24    ";
    Ciphertext gin24 = gout21[2] + 1 * gout16[0] + 2 * gout16[1] + 1 * gout22[0] + 2 * gout22[1];
    std::vector<Ciphertext> gout24 = ctx.eval_lut_amortized(&gin24, decomp);

    std::cerr << "\rFA25    ";
    Ciphertext gin25 = gout20[2] + 1 * gout17[0] + 2 * gout17[1] + 1 * gout5[0] + 2 * gout5[1];
    std::vector<Ciphertext> gout25 = ctx.eval_lut_amortized(&gin25, decomp);

    std::cerr << "\rINV26   ";
    std::vector<Ciphertext> gout26;
    gout26.push_back(1 - gout23[1]);

    std::cerr << "\rFA27    ";
    Ciphertext gin27 = gout23[2] + 1 * gout21[0] + 2 * gout21[1] + 1 * gout20[0] + 2 * gout20[1];
    std::vector<Ciphertext> gout27 = ctx.eval_lut_amortized(&gin27, decomp);

    std::cerr << "\rFA28    ";
    Ciphertext gin28 = gout27[2] + 1 * gout24[0] + 2 * gout24[1] + 1 * gout25[0] + 2 * gout25[1];
    std::vector<Ciphertext> gout28 = ctx.eval_lut_amortized(&gin28, decomp);

    std::cerr << "\rFA29    ";
    Ciphertext gin29 = gout24[2] + 1 * gout16[2] + 1 * gout22[2];
    std::vector<Ciphertext> gout29 = ctx.eval_lut_amortized(&gin29, decomp);

    std::cerr << "\rFA30    ";
    Ciphertext gin30 = gout25[2] + 1 * gout17[2] + 1 * gout5[2];
    std::vector<Ciphertext> gout30 = ctx.eval_lut_amortized(&gin30, decomp);

    std::cerr << "\rINV31   ";
    std::vector<Ciphertext> gout31;
    gout31.push_back(1 - gout27[0]);

    std::cerr << "\rINV32   ";
    std::vector<Ciphertext> gout32;
    gout32.push_back(1 - gout27[1]);

    std::cerr << "\rINV33   ";
    std::vector<Ciphertext> gout33;
    gout33.push_back(1 - gout28[0]);

    std::cerr << "\rINV34   ";
    std::vector<Ciphertext> gout34;
    gout34.push_back(1 - gout28[1]);

    std::cerr << "\rFA35    ";
    Ciphertext gin35 = gout28[2] + 1 * gout29[0] + 2 * gout29[1] + 1 * gout30[0] + 2 * gout30[1];
    std::vector<Ciphertext> gout35 = ctx.eval_lut_amortized(&gin35, decomp);

    std::cerr << "\rFA36    ";
    Ciphertext gin36 = 1 + 1 * ct_window32 + 2 * ct_window33 + 1 * gout26[0] + 2 * gout31[0];
    std::vector<Ciphertext> gout36 = ctx.eval_lut_amortized(&gin36, decomp);

    std::cerr << "\rFA37    ";
    Ciphertext gin37 = gout36[2] + 1 * ct_window34 + 2 * ct_window35 + 1 * gout32[0] + 2 * gout33[0];
    std::vector<Ciphertext> gout37 = ctx.eval_lut_amortized(&gin37, decomp);

    std::cerr << "\rINV38   ";
    std::vector<Ciphertext> gout38;
    gout38.push_back(1 - gout35[2]);

    std::cerr << "\rINV39   ";
    std::vector<Ciphertext> gout39;
    gout39.push_back(1 - gout35[1]);

    std::cerr << "\rINV40   ";
    std::vector<Ciphertext> gout40;
    gout40.push_back(1 - gout35[0]);

    std::vector<RotationPoly> lut41;
    std::vector<long (*)(long)> flut41;
    auto lut41idx0 = [](long I) -> long {
        /* GATE 6 (LUT2 _046_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut41.push_back(ctx.genrate_lut(lut41idx0));
    flut41.push_back(lut41idx0);
    auto fvec41 = [flut41](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut41[i](I));
        return ret;
    };

    std::cerr << "\rLUT41   ";
    Ciphertext gin41 = 1 * gout36[1] + 2 * gout36[0];
    std::vector<Ciphertext> gout41 = ctx.eval_lut_amortized(&gin41, lut41);

    std::cerr << "\rFA42    ";
    Ciphertext gin42 = gout37[2] + 1 * ct_window36 + 2 * ct_window37 + 1 * gout34[0] + 2 * gout40[0];
    std::vector<Ciphertext> gout42 = ctx.eval_lut_amortized(&gin42, decomp);

    std::vector<RotationPoly> lut43;
    std::vector<long (*)(long)> flut43;
    auto lut43idx0 = [](long I) -> long {
        /* GATE 4 (LUT3 _044_ INIT 0x1 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut43.push_back(ctx.genrate_lut(lut43idx0));
    flut43.push_back(lut43idx0);
    auto fvec43 = [flut43](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut43[i](I));
        return ret;
    };

    std::cerr << "\rLUT43   ";
    Ciphertext gin43 = 1 * gout36[1] + 2 * gout36[0] + 4 * gout37[0];
    std::vector<Ciphertext> gout43 = ctx.eval_lut_amortized(&gin43, lut43);

    std::cerr << "\rFA44    ";
    Ciphertext gin44 = gout42[2] + 1 * ct_window38 + 2 * ct_window39 + 1 * gout39[0] + 2 * gout38[0];
    std::vector<Ciphertext> gout44 = ctx.eval_lut_amortized(&gin44, decomp);

    std::vector<RotationPoly> lut45;
    std::vector<long (*)(long)> flut45;
    auto lut45idx0 = [](long I) -> long {
        /* GATE 1 (LUT3 _041_ INIT 0x78 PERM 210) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut45.push_back(ctx.genrate_lut(lut45idx0));
    flut45.push_back(lut45idx0);
    auto fvec45 = [flut45](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut45[i](I));
        return ret;
    };

    std::cerr << "\rLUT45   ";
    Ciphertext gin45 = 1 * gout36[1] + 2 * gout36[0] + 4 * gout44[2];
    std::vector<Ciphertext> gout45 = ctx.eval_lut_amortized(&gin45, lut45);

    std::vector<RotationPoly> lut46;
    std::vector<long (*)(long)> flut46;
    auto lut46idx0 = [](long I) -> long {
        /* GATE 5 (LUT3 _045_ INIT 0xb4 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut46.push_back(ctx.genrate_lut(lut46idx0));
    flut46.push_back(lut46idx0);
    auto fvec46 = [flut46](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut46[i](I));
        return ret;
    };

    std::cerr << "\rLUT46   ";
    Ciphertext gin46 = 1 * gout41[0] + 2 * gout37[0] + 4 * gout44[2];
    std::vector<Ciphertext> gout46 = ctx.eval_lut_amortized(&gin46, lut46);

    std::vector<RotationPoly> lut47;
    std::vector<long (*)(long)> flut47;
    auto lut47idx0 = [](long I) -> long {
        /* GATE 3 (LUT3 _043_ INIT 0x10 PERM 201) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut47.push_back(ctx.genrate_lut(lut47idx0));
    flut47.push_back(lut47idx0);
    auto lut47idx1 = [](long I) -> long {
        /* GATE 9 (LUT2 _049_ INIT 0x4 PERM 21) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut47.push_back(ctx.genrate_lut(lut47idx1));
    flut47.push_back(lut47idx1);
    auto fvec47 = [flut47](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut47[i](I));
        return ret;
    };

    std::cerr << "\rLUT47   ";
    Ciphertext gin47 = 1 * gout42[0] + 2 * gout43[0] + 4 * gout37[1];
    std::vector<Ciphertext> gout47 = ctx.eval_lut_amortized(&gin47, lut47);

    std::vector<RotationPoly> lut48;
    std::vector<long (*)(long)> flut48;
    auto lut48idx0 = [](long I) -> long {
        /* GATE 7 (LUT3 _047_ INIT 0xb4 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut48.push_back(ctx.genrate_lut(lut48idx0));
    flut48.push_back(lut48idx0);
    auto fvec48 = [flut48](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut48[i](I));
        return ret;
    };

    std::cerr << "\rLUT48   ";
    Ciphertext gin48 = 1 * gout43[0] + 2 * gout37[1] + 4 * gout44[2];
    std::vector<Ciphertext> gout48 = ctx.eval_lut_amortized(&gin48, lut48);

    std::vector<RotationPoly> lut49;
    std::vector<long (*)(long)> flut49;
    auto lut49idx0 = [](long I) -> long {
        /* GATE 12 (LUT3 _052_ INIT 0xb0 PERM 102) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut49.push_back(ctx.genrate_lut(lut49idx0));
    flut49.push_back(lut49idx0);
    auto lut49idx1 = [](long I) -> long {
        /* GATE 10 (LUT3 _050_ INIT 0xb4 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut49.push_back(ctx.genrate_lut(lut49idx1));
    flut49.push_back(lut49idx1);
    auto fvec49 = [flut49](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut49[i](I));
        return ret;
    };

    std::cerr << "\rLUT49   ";
    Ciphertext gin49 = 1 * gout47[0] + 2 * gout42[1] + 4 * gout44[2];
    std::vector<Ciphertext> gout49 = ctx.eval_lut_amortized(&gin49, lut49);

    std::vector<RotationPoly> lut50;
    std::vector<long (*)(long)> flut50;
    auto lut50idx0 = [](long I) -> long {
        /* GATE 11 (LUT2 _051_ INIT 0x6 PERM 01) */
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
    lut50.push_back(ctx.genrate_lut(lut50idx0));
    flut50.push_back(lut50idx0);
    auto fvec50 = [flut50](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut50[i](I));
        return ret;
    };

    std::cerr << "\rLUT50   ";
    Ciphertext gin50 = 1 * gout49[0] + 2 * gout44[0];
    std::vector<Ciphertext> gout50 = ctx.eval_lut_amortized(&gin50, lut50);

    std::vector<RotationPoly> lut51;
    std::vector<long (*)(long)> flut51;
    auto lut51idx0 = [](long I) -> long {
        /* GATE 2 (LUT3 _042_ INIT 0x10 PERM 120) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut51.push_back(ctx.genrate_lut(lut51idx0));
    flut51.push_back(lut51idx0);
    auto fvec51 = [flut51](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut51[i](I));
        return ret;
    };

    std::cerr << "\rLUT51   ";
    Ciphertext gin51 = 1 * gout47[0] + 2 * gout42[1] + 4 * gout44[0];
    std::vector<Ciphertext> gout51 = ctx.eval_lut_amortized(&gin51, lut51);

    std::vector<RotationPoly> lut52;
    std::vector<long (*)(long)> flut52;
    auto lut52idx0 = [](long I) -> long {
        /* GATE 8 (LUT3 _048_ INIT 0xb4 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut52.push_back(ctx.genrate_lut(lut52idx0));
    flut52.push_back(lut52idx0);
    auto fvec52 = [flut52](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut52[i](I));
        return ret;
    };

    std::cerr << "\rLUT52   ";
    Ciphertext gin52 = 1 * gout47[1] + 2 * gout42[0] + 4 * gout44[2];
    std::vector<Ciphertext> gout52 = ctx.eval_lut_amortized(&gin52, lut52);

    std::vector<RotationPoly> lut53;
    std::vector<long (*)(long)> flut53;
    auto lut53idx0 = [](long I) -> long {
        /* GATE 13 (LUT3 _053_ INIT 0xb4 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut53.push_back(ctx.genrate_lut(lut53idx0));
    flut53.push_back(lut53idx0);
    auto fvec53 = [flut53](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut53[i](I));
        return ret;
    };

    std::cerr << "\rLUT53   ";
    Ciphertext gin53 = 1 * gout51[0] + 2 * gout44[2] + 4 * gout44[1];
    std::vector<Ciphertext> gout53 = ctx.eval_lut_amortized(&gin53, lut53);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(ctx.decrypt(&gout36[0])); /* out0 */
    test_out.push_back(ctx.decrypt(&gout45[0])); /* out1 */
    test_out.push_back(ctx.decrypt(&gout46[0])); /* out2 */
    test_out.push_back(ctx.decrypt(&gout48[0])); /* out3 */
    test_out.push_back(ctx.decrypt(&gout52[0])); /* out4 */
    test_out.push_back(ctx.decrypt(&gout49[1])); /* out5 */
    test_out.push_back(ctx.decrypt(&gout50[0])); /* out6 */
    test_out.push_back(ctx.decrypt(&gout53[0])); /* out7 */
    return test_out;
}

static void
BM_image_ricker_lut3fa(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(rlwe_hom_acc_scheme_C_11_NTT);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(8);

    for (auto _ : state) {
        test_image_ricker_lut3fa(ctx);
    }
}

BENCHMARK(BM_image_ricker_lut3fa)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
