#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_image_ricker_lut4fa(FHEContext& ctx, std::vector<uint64_t> window = { 0 })
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
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 1;
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
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
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
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    };
    decomp.push_back(ctx.genrate_lut(decomp2));
    fdecomp.push_back(decomp2);
    auto decomp3 = [](long I) -> long {
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 1;
            case 11: return 1;
            case 12: return 1;
            case 13: return 1;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    };
    decomp.push_back(ctx.genrate_lut(decomp3));
    fdecomp.push_back(decomp3);
    auto vdecomp = [fdecomp](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 4; ++i)
            ret.push_back(fdecomp[i](I));
        return ret;
    };

    std::cerr << "\rFA0    ";
    Ciphertext gin0 = 0 + 1 * ct_window40 + 2 * ct_window41 + 4 * ct_window42 + 1 * ct_window48 + 2 * ct_window49 + 4 * ct_window50;
    std::vector<Ciphertext> gout0 = ctx.eval_lut_amortized(&gin0, decomp);

    std::cerr << "\rFA1    ";
    Ciphertext gin1 = 0 + 1 * ct_window56 + 2 * ct_window57 + 4 * ct_window58 + 1 * ct_window64 + 2 * ct_window65 + 4 * ct_window66;
    std::vector<Ciphertext> gout1 = ctx.eval_lut_amortized(&gin1, decomp);

    std::cerr << "\rFA2    ";
    Ciphertext gin2 = 0 + 1 * ct_window16 + 2 * ct_window17 + 4 * ct_window18 + 1 * ct_window24 + 2 * ct_window25 + 4 * ct_window26;
    std::vector<Ciphertext> gout2 = ctx.eval_lut_amortized(&gin2, decomp);

    std::cerr << "\rFA3    ";
    Ciphertext gin3 = 0 + 1 * ct_window0 + 2 * ct_window1 + 4 * ct_window2 + 1 * ct_window8 + 2 * ct_window9 + 4 * ct_window10;
    std::vector<Ciphertext> gout3 = ctx.eval_lut_amortized(&gin3, decomp);

    std::cerr << "\rFA4    ";
    Ciphertext gin4 = gout0[3] + 1 * ct_window43 + 2 * ct_window44 + 4 * ct_window45 + 1 * ct_window51 + 2 * ct_window52 + 4 * ct_window53;
    std::vector<Ciphertext> gout4 = ctx.eval_lut_amortized(&gin4, decomp);

    std::cerr << "\rFA5    ";
    Ciphertext gin5 = gout3[3] + 1 * ct_window3 + 2 * ct_window4 + 4 * ct_window5 + 1 * ct_window11 + 2 * ct_window12 + 4 * ct_window13;
    std::vector<Ciphertext> gout5 = ctx.eval_lut_amortized(&gin5, decomp);

    std::cerr << "\rFA6    ";
    Ciphertext gin6 = gout5[3] + 1 * ct_window6 + 2 * ct_window7 + 1 * ct_window14 + 2 * ct_window15;
    std::vector<Ciphertext> gout6 = ctx.eval_lut_amortized(&gin6, decomp);

    std::cerr << "\rFA7    ";
    Ciphertext gin7 = 0 + 1 * gout0[0] + 2 * gout0[1] + 4 * gout0[2] + 1 * gout1[0] + 2 * gout1[1] + 4 * gout1[2];
    std::vector<Ciphertext> gout7 = ctx.eval_lut_amortized(&gin7, decomp);

    std::cerr << "\rFA8    ";
    Ciphertext gin8 = gout1[3] + 1 * ct_window59 + 2 * ct_window60 + 4 * ct_window61 + 1 * ct_window67 + 2 * ct_window68 + 4 * ct_window69;
    std::vector<Ciphertext> gout8 = ctx.eval_lut_amortized(&gin8, decomp);

    std::cerr << "\rFA9    ";
    Ciphertext gin9 = gout2[3] + 1 * ct_window19 + 2 * ct_window20 + 4 * ct_window21 + 1 * ct_window27 + 2 * ct_window28 + 4 * ct_window29;
    std::vector<Ciphertext> gout9 = ctx.eval_lut_amortized(&gin9, decomp);

    std::cerr << "\rFA10    ";
    Ciphertext gin10 = 0 + 1 * gout3[0] + 2 * gout3[1] + 4 * gout3[2] + 1 * gout2[0] + 2 * gout2[1] + 4 * gout2[2];
    std::vector<Ciphertext> gout10 = ctx.eval_lut_amortized(&gin10, decomp);

    std::cerr << "\rFA11    ";
    Ciphertext gin11 = gout9[3] + 1 * ct_window22 + 2 * ct_window23 + 1 * ct_window30 + 2 * ct_window31;
    std::vector<Ciphertext> gout11 = ctx.eval_lut_amortized(&gin11, decomp);

    std::cerr << "\rFA12    ";
    Ciphertext gin12 = gout8[3] + 1 * ct_window62 + 2 * ct_window63 + 1 * ct_window70 + 2 * ct_window71;
    std::vector<Ciphertext> gout12 = ctx.eval_lut_amortized(&gin12, decomp);

    std::cerr << "\rFA13    ";
    Ciphertext gin13 = gout4[3] + 1 * ct_window46 + 2 * ct_window47 + 1 * ct_window54 + 2 * ct_window55;
    std::vector<Ciphertext> gout13 = ctx.eval_lut_amortized(&gin13, decomp);

    std::cerr << "\rFA14    ";
    Ciphertext gin14 = gout10[3] + 1 * gout5[0] + 2 * gout5[1] + 4 * gout5[2] + 1 * gout9[0] + 2 * gout9[1] + 4 * gout9[2];
    std::vector<Ciphertext> gout14 = ctx.eval_lut_amortized(&gin14, decomp);

    std::cerr << "\rFA15    ";
    Ciphertext gin15 = gout7[3] + 1 * gout4[0] + 2 * gout4[1] + 4 * gout4[2] + 1 * gout8[0] + 2 * gout8[1] + 4 * gout8[2];
    std::vector<Ciphertext> gout15 = ctx.eval_lut_amortized(&gin15, decomp);

    std::cerr << "\rFA16    ";
    Ciphertext gin16 = 0 + 1 * gout10[0] + 2 * gout10[1] + 4 * gout10[2] + 1 * gout7[0] + 2 * gout7[1] + 4 * gout7[2];
    std::vector<Ciphertext> gout16 = ctx.eval_lut_amortized(&gin16, decomp);

    std::cerr << "\rFA17    ";
    Ciphertext gin17 = gout15[3] + 1 * gout13[0] + 2 * gout13[1] + 4 * gout13[2] + 1 * gout12[0] + 2 * gout12[1] + 4 * gout12[2];
    std::vector<Ciphertext> gout17 = ctx.eval_lut_amortized(&gin17, decomp);

    std::cerr << "\rFA18    ";
    Ciphertext gin18 = gout14[3] + 1 * gout6[0] + 2 * gout6[1] + 4 * gout6[2] + 1 * gout11[0] + 2 * gout11[1] + 4 * gout11[2];
    std::vector<Ciphertext> gout18 = ctx.eval_lut_amortized(&gin18, decomp);

    std::cerr << "\rFA19    ";
    Ciphertext gin19 = gout16[3] + 1 * gout14[0] + 2 * gout14[1] + 4 * gout14[2] + 1 * gout15[0] + 2 * gout15[1] + 4 * gout15[2];
    std::vector<Ciphertext> gout19 = ctx.eval_lut_amortized(&gin19, decomp);

    std::cerr << "\rFA20    ";
    Ciphertext gin20 = gout19[3] + 1 * gout18[0] + 2 * gout18[1] + 4 * gout18[2] + 1 * gout17[0] + 2 * gout17[1] + 4 * gout17[2];
    std::vector<Ciphertext> gout20 = ctx.eval_lut_amortized(&gin20, decomp);

    std::cerr << "\rINV21   ";
    std::vector<Ciphertext> gout21;
    gout21.push_back(1 - gout19[2]);

    std::cerr << "\rINV22   ";
    std::vector<Ciphertext> gout22;
    gout22.push_back(1 - gout19[0]);

    std::cerr << "\rINV23   ";
    std::vector<Ciphertext> gout23;
    gout23.push_back(1 - gout20[1]);

    std::cerr << "\rINV24   ";
    std::vector<Ciphertext> gout24;
    gout24.push_back(1 - gout19[1]);

    std::cerr << "\rINV25   ";
    std::vector<Ciphertext> gout25;
    gout25.push_back(1 - gout20[0]);

    std::cerr << "\rINV26   ";
    std::vector<Ciphertext> gout26;
    gout26.push_back(1 - gout20[2]);

    std::cerr << "\rFA27    ";
    Ciphertext gin27 = 1 + 1 * ct_window32 + 2 * ct_window33 + 4 * ct_window34 + 1 * gout22[0] + 2 * gout24[0] + 4 * gout21[0];
    std::vector<Ciphertext> gout27 = ctx.eval_lut_amortized(&gin27, decomp);

    std::cerr << "\rFA28    ";
    Ciphertext gin28 = gout20[3] + 1 * gout18[3] + 1 * gout17[3];
    std::vector<Ciphertext> gout28 = ctx.eval_lut_amortized(&gin28, decomp);

    std::cerr << "\rINV29   ";
    std::vector<Ciphertext> gout29;
    gout29.push_back(1 - gout28[1]);

    std::cerr << "\rFA30    ";
    Ciphertext gin30 = gout27[3] + 1 * ct_window35 + 2 * ct_window36 + 4 * ct_window37 + 1 * gout25[0] + 2 * gout23[0] + 4 * gout26[0];
    std::vector<Ciphertext> gout30 = ctx.eval_lut_amortized(&gin30, decomp);

    std::vector<RotationPoly> lut31;
    std::vector<long (*)(long)> flut31;
    auto lut31idx0 = [](long I) -> long {
        /* GATE 3 (LUT4 _046_ INIT 0x1 PERM 3012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    };
    lut31.push_back(ctx.genrate_lut(lut31idx0));
    flut31.push_back(lut31idx0);
    auto fvec31 = [flut31](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut31[i](I));
        return ret;
    };

    std::cerr << "\rLUT31   ";
    Ciphertext gin31 = 1 * gout27[2] + 2 * gout30[0] + 4 * gout27[0] + 8 * gout27[1];
    std::vector<Ciphertext> gout31 = ctx.eval_lut_amortized(&gin31, lut31);

    std::vector<RotationPoly> lut32;
    std::vector<long (*)(long)> flut32;
    auto lut32idx0 = [](long I) -> long {
        /* GATE 12 (LUT2 _055_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    };
    lut32.push_back(ctx.genrate_lut(lut32idx0));
    flut32.push_back(lut32idx0);
    auto fvec32 = [flut32](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut32[i](I));
        return ret;
    };

    std::cerr << "\rLUT32   ";
    Ciphertext gin32 = 1 * gout31[0] + 2 * gout30[1];
    std::vector<Ciphertext> gout32 = ctx.eval_lut_amortized(&gin32, lut32);

    std::cerr << "\rINV33   ";
    std::vector<Ciphertext> gout33;
    gout33.push_back(1 - gout28[0]);

    std::cerr << "\rFA34    ";
    Ciphertext gin34 = gout30[3] + 1 * ct_window38 + 2 * ct_window39 + 1 * gout33[0] + 2 * gout29[0];
    std::vector<Ciphertext> gout34 = ctx.eval_lut_amortized(&gin34, decomp);

    std::vector<RotationPoly> lut35;
    std::vector<long (*)(long)> flut35;
    auto lut35idx0 = [](long I) -> long {
        /* GATE 2 (LUT4 _045_ INIT 0x100 PERM 1230) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    };
    lut35.push_back(ctx.genrate_lut(lut35idx0));
    flut35.push_back(lut35idx0);
    auto fvec35 = [flut35](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut35[i](I));
        return ret;
    };

    std::cerr << "\rLUT35   ";
    Ciphertext gin35 = 1 * gout31[0] + 2 * gout30[1] + 4 * gout30[2] + 8 * gout34[0];
    std::vector<Ciphertext> gout35 = ctx.eval_lut_amortized(&gin35, lut35);

    std::vector<RotationPoly> lut36;
    std::vector<long (*)(long)> flut36;
    auto lut36idx0 = [](long I) -> long {
        /* GATE 4 (LUT4 _047_ INIT 0x1fe0 PERM 2130) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    };
    lut36.push_back(ctx.genrate_lut(lut36idx0));
    flut36.push_back(lut36idx0);
    auto lut36idx1 = [](long I) -> long {
        /* GATE 1 (LUT3 _044_ INIT 0x78 PERM 312) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    };
    lut36.push_back(ctx.genrate_lut(lut36idx1));
    flut36.push_back(lut36idx1);
    auto fvec36 = [flut36](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut36[i](I));
        return ret;
    };

    std::cerr << "\rLUT36   ";
    Ciphertext gin36 = 1 * gout27[2] + 2 * gout27[0] + 4 * gout27[1] + 8 * gout34[2];
    std::vector<Ciphertext> gout36 = ctx.eval_lut_amortized(&gin36, lut36);

    std::vector<RotationPoly> lut37;
    std::vector<long (*)(long)> flut37;
    auto lut37idx0 = [](long I) -> long {
        /* GATE 13 (LUT4 _056_ INIT 0x4fb0 PERM 0132) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    };
    lut37.push_back(ctx.genrate_lut(lut37idx0));
    flut37.push_back(lut37idx0);
    auto lut37idx1 = [](long I) -> long {
        /* GATE 11 (LUT2 _054_ INIT 0x4 PERM 13) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    };
    lut37.push_back(ctx.genrate_lut(lut37idx1));
    flut37.push_back(lut37idx1);
    auto fvec37 = [flut37](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut37[i](I));
        return ret;
    };

    std::cerr << "\rLUT37   ";
    Ciphertext gin37 = 1 * gout30[2] + 2 * gout32[0] + 4 * gout34[0] + 8 * gout34[2];
    std::vector<Ciphertext> gout37 = ctx.eval_lut_amortized(&gin37, lut37);

    std::vector<RotationPoly> lut38;
    std::vector<long (*)(long)> flut38;
    auto lut38idx0 = [](long I) -> long {
        /* GATE 7 (LUT3 _050_ INIT 0x1 PERM 201) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    };
    lut38.push_back(ctx.genrate_lut(lut38idx0));
    flut38.push_back(lut38idx0);
    auto fvec38 = [flut38](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut38[i](I));
        return ret;
    };

    std::cerr << "\rLUT38   ";
    Ciphertext gin38 = 1 * gout27[2] + 2 * gout27[0] + 4 * gout27[1];
    std::vector<Ciphertext> gout38 = ctx.eval_lut_amortized(&gin38, lut38);

    std::vector<RotationPoly> lut39;
    std::vector<long (*)(long)> flut39;
    auto lut39idx0 = [](long I) -> long {
        /* GATE 14 (LUT3 _057_ INIT 0xb4 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    };
    lut39.push_back(ctx.genrate_lut(lut39idx0));
    flut39.push_back(lut39idx0);
    auto fvec39 = [flut39](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut39[i](I));
        return ret;
    };

    std::cerr << "\rLUT39   ";
    Ciphertext gin39 = 1 * gout35[0] + 2 * gout34[2] + 4 * gout34[1];
    std::vector<Ciphertext> gout39 = ctx.eval_lut_amortized(&gin39, lut39);

    std::vector<RotationPoly> lut40;
    std::vector<long (*)(long)> flut40;
    auto lut40idx0 = [](long I) -> long {
        /* GATE 10 (LUT2 _053_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    };
    lut40.push_back(ctx.genrate_lut(lut40idx0));
    flut40.push_back(lut40idx0);
    auto fvec40 = [flut40](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut40[i](I));
        return ret;
    };

    std::cerr << "\rLUT40   ";
    Ciphertext gin40 = 1 * gout37[1] + 2 * gout30[2];
    std::vector<Ciphertext> gout40 = ctx.eval_lut_amortized(&gin40, lut40);

    std::vector<RotationPoly> lut41;
    std::vector<long (*)(long)> flut41;
    auto lut41idx0 = [](long I) -> long {
        /* GATE 6 (LUT2 _049_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
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
    Ciphertext gin41 = 1 * gout38[0] + 2 * gout34[2];
    std::vector<Ciphertext> gout41 = ctx.eval_lut_amortized(&gin41, lut41);

    std::vector<RotationPoly> lut42;
    std::vector<long (*)(long)> flut42;
    auto lut42idx0 = [](long I) -> long {
        /* GATE 9 (LUT2 _052_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    };
    lut42.push_back(ctx.genrate_lut(lut42idx0));
    flut42.push_back(lut42idx0);
    auto fvec42 = [flut42](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut42[i](I));
        return ret;
    };

    std::cerr << "\rLUT42   ";
    Ciphertext gin42 = 1 * gout31[0] + 2 * gout34[2];
    std::vector<Ciphertext> gout42 = ctx.eval_lut_amortized(&gin42, lut42);

    std::vector<RotationPoly> lut43;
    std::vector<long (*)(long)> flut43;
    auto lut43idx0 = [](long I) -> long {
        /* GATE 5 (LUT2 _048_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
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
    Ciphertext gin43 = 1 * gout41[0] + 2 * gout30[0];
    std::vector<Ciphertext> gout43 = ctx.eval_lut_amortized(&gin43, lut43);

    std::vector<RotationPoly> lut44;
    std::vector<long (*)(long)> flut44;
    auto lut44idx0 = [](long I) -> long {
        /* GATE 8 (LUT2 _051_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    };
    lut44.push_back(ctx.genrate_lut(lut44idx0));
    flut44.push_back(lut44idx0);
    auto fvec44 = [flut44](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut44[i](I));
        return ret;
    };

    std::cerr << "\rLUT44   ";
    Ciphertext gin44 = 1 * gout42[0] + 2 * gout30[1];
    std::vector<Ciphertext> gout44 = ctx.eval_lut_amortized(&gin44, lut44);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(ctx.decrypt(&gout27[0])); /* out0 */
    test_out.push_back(ctx.decrypt(&gout36[1])); /* out1 */
    test_out.push_back(ctx.decrypt(&gout36[0])); /* out2 */
    test_out.push_back(ctx.decrypt(&gout43[0])); /* out3 */
    test_out.push_back(ctx.decrypt(&gout44[0])); /* out4 */
    test_out.push_back(ctx.decrypt(&gout40[0])); /* out5 */
    test_out.push_back(ctx.decrypt(&gout37[0])); /* out6 */
    test_out.push_back(ctx.decrypt(&gout39[0])); /* out7 */
    return test_out;
}

static void
BM_image_ricker_lut4fa(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(tfhe_12_NTT_amortized);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(16);

    for (auto _ : state) {
        test_image_ricker_lut4fa(ctx);
    }
}

BENCHMARK(BM_image_ricker_lut4fa)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
