#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_image_sharpen_lut2fa(FHEContext& ctx, uint64_t window = 0)
{
    Ciphertext ct_window8 = ctx.encrypt_public((window >> 0) & 1);
    Ciphertext ct_window9 = ctx.encrypt_public((window >> 1) & 1);
    Ciphertext ct_window10 = ctx.encrypt_public((window >> 2) & 1);
    Ciphertext ct_window11 = ctx.encrypt_public((window >> 3) & 1);
    Ciphertext ct_window12 = ctx.encrypt_public((window >> 4) & 1);
    Ciphertext ct_window13 = ctx.encrypt_public((window >> 5) & 1);
    Ciphertext ct_window14 = ctx.encrypt_public((window >> 6) & 1);
    Ciphertext ct_window15 = ctx.encrypt_public((window >> 7) & 1);
    Ciphertext ct_window24 = ctx.encrypt_public((window >> 8) & 1);
    Ciphertext ct_window25 = ctx.encrypt_public((window >> 9) & 1);
    Ciphertext ct_window26 = ctx.encrypt_public((window >> 10) & 1);
    Ciphertext ct_window27 = ctx.encrypt_public((window >> 11) & 1);
    Ciphertext ct_window28 = ctx.encrypt_public((window >> 12) & 1);
    Ciphertext ct_window29 = ctx.encrypt_public((window >> 13) & 1);
    Ciphertext ct_window30 = ctx.encrypt_public((window >> 14) & 1);
    Ciphertext ct_window31 = ctx.encrypt_public((window >> 15) & 1);
    Ciphertext ct_window32 = ctx.encrypt_public((window >> 16) & 1);
    Ciphertext ct_window33 = ctx.encrypt_public((window >> 17) & 1);
    Ciphertext ct_window34 = ctx.encrypt_public((window >> 18) & 1);
    Ciphertext ct_window35 = ctx.encrypt_public((window >> 19) & 1);
    Ciphertext ct_window36 = ctx.encrypt_public((window >> 20) & 1);
    Ciphertext ct_window37 = ctx.encrypt_public((window >> 21) & 1);
    Ciphertext ct_window38 = ctx.encrypt_public((window >> 22) & 1);
    Ciphertext ct_window39 = ctx.encrypt_public((window >> 23) & 1);
    Ciphertext ct_window40 = ctx.encrypt_public((window >> 24) & 1);
    Ciphertext ct_window41 = ctx.encrypt_public((window >> 25) & 1);
    Ciphertext ct_window42 = ctx.encrypt_public((window >> 26) & 1);
    Ciphertext ct_window43 = ctx.encrypt_public((window >> 27) & 1);
    Ciphertext ct_window44 = ctx.encrypt_public((window >> 28) & 1);
    Ciphertext ct_window45 = ctx.encrypt_public((window >> 29) & 1);
    Ciphertext ct_window46 = ctx.encrypt_public((window >> 30) & 1);
    Ciphertext ct_window47 = ctx.encrypt_public((window >> 31) & 1);
    Ciphertext ct_window56 = ctx.encrypt_public((window >> 32) & 1);
    Ciphertext ct_window57 = ctx.encrypt_public((window >> 33) & 1);
    Ciphertext ct_window58 = ctx.encrypt_public((window >> 34) & 1);
    Ciphertext ct_window59 = ctx.encrypt_public((window >> 35) & 1);
    Ciphertext ct_window60 = ctx.encrypt_public((window >> 36) & 1);
    Ciphertext ct_window61 = ctx.encrypt_public((window >> 37) & 1);
    Ciphertext ct_window62 = ctx.encrypt_public((window >> 38) & 1);
    Ciphertext ct_window63 = ctx.encrypt_public((window >> 39) & 1);

    std::vector<RotationPoly> decomp;
    std::vector<long (*)(long)> fdecomp;
    auto decomp0 = [](long I) -> long {
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
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
            default: assert(0);
        };
    };
    decomp.push_back(ctx.genrate_lut(decomp1));
    fdecomp.push_back(decomp1);
    auto vdecomp = [fdecomp](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(fdecomp[i](I));
        return ret;
    };

    std::vector<RotationPoly> lut0;
    std::vector<long (*)(long)> flut0;
    auto lut0idx0 = [](long I) -> long {
        /* GATE 36 (LUT2 _162_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut0.push_back(ctx.genrate_lut(lut0idx0));
    flut0.push_back(lut0idx0);
    auto lut0idx1 = [](long I) -> long {
        /* GATE 42 (LUT2 _168_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin0 = 1 * ct_window36 + 2 * ct_window38;
    std::vector<Ciphertext> gout0 = ctx.eval_lut_amortized(&gin0, lut0);

    std::vector<RotationPoly> lut1;
    std::vector<long (*)(long)> flut1;
    auto lut1idx0 = [](long I) -> long {
        /* GATE 43 (LUT2 _169_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut1.push_back(ctx.genrate_lut(lut1idx0));
    flut1.push_back(lut1idx0);
    auto fvec1 = [flut1](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut1[i](I));
        return ret;
    };

    std::cerr << "\rLUT1   ";
    Ciphertext gin1 = 1 * ct_window39 + 2 * ct_window37;
    std::vector<Ciphertext> gout1 = ctx.eval_lut_amortized(&gin1, lut1);

    std::cerr << "\rFA2    ";
    Ciphertext gin2 = 0 + 1 * ct_window40 + 1 * ct_window56;
    std::vector<Ciphertext> gout2 = ctx.eval_lut_amortized(&gin2, decomp);

    std::cerr << "\rFA3    ";
    Ciphertext gin3 = 0 + 1 * ct_window8 + 1 * ct_window24;
    std::vector<Ciphertext> gout3 = ctx.eval_lut_amortized(&gin3, decomp);

    std::vector<RotationPoly> lut4;
    std::vector<long (*)(long)> flut4;
    auto lut4idx0 = [](long I) -> long {
        /* GATE 28 (LUT2 _154_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut4.push_back(ctx.genrate_lut(lut4idx0));
    flut4.push_back(lut4idx0);
    auto lut4idx1 = [](long I) -> long {
        /* GATE 24 (LUT2 _150_ INIT 0x6 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut4.push_back(ctx.genrate_lut(lut4idx1));
    flut4.push_back(lut4idx1);
    auto fvec4 = [flut4](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut4[i](I));
        return ret;
    };

    std::cerr << "\rLUT4   ";
    Ciphertext gin4 = 1 * ct_window36 + 2 * ct_window34;
    std::vector<Ciphertext> gout4 = ctx.eval_lut_amortized(&gin4, lut4);

    std::vector<RotationPoly> lut5;
    std::vector<long (*)(long)> flut5;
    auto lut5idx0 = [](long I) -> long {
        /* GATE 35 (LUT2 _161_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut5.push_back(ctx.genrate_lut(lut5idx0));
    flut5.push_back(lut5idx0);
    auto lut5idx1 = [](long I) -> long {
        /* GATE 29 (LUT2 _155_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut5.push_back(ctx.genrate_lut(lut5idx1));
    flut5.push_back(lut5idx1);
    auto fvec5 = [flut5](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut5[i](I));
        return ret;
    };

    std::cerr << "\rLUT5   ";
    Ciphertext gin5 = 1 * ct_window35 + 2 * ct_window37;
    std::vector<Ciphertext> gout5 = ctx.eval_lut_amortized(&gin5, lut5);

    std::vector<RotationPoly> lut6;
    std::vector<long (*)(long)> flut6;
    auto lut6idx0 = [](long I) -> long {
        /* GATE 41 (LUT2 _167_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut6.push_back(ctx.genrate_lut(lut6idx0));
    flut6.push_back(lut6idx0);
    auto fvec6 = [flut6](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut6[i](I));
        return ret;
    };

    std::cerr << "\rLUT6   ";
    Ciphertext gin6 = 1 * gout0[1] + 2 * gout1[0];
    std::vector<Ciphertext> gout6 = ctx.eval_lut_amortized(&gin6, lut6);

    std::vector<RotationPoly> lut7;
    std::vector<long (*)(long)> flut7;
    auto lut7idx0 = [](long I) -> long {
        /* GATE 44 (LUT2 _170_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut7.push_back(ctx.genrate_lut(lut7idx0));
    flut7.push_back(lut7idx0);
    auto lut7idx1 = [](long I) -> long {
        /* GATE 18 (LUT2 _144_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut7.push_back(ctx.genrate_lut(lut7idx1));
    flut7.push_back(lut7idx1);
    auto fvec7 = [flut7](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut7[i](I));
        return ret;
    };

    std::cerr << "\rLUT7   ";
    Ciphertext gin7 = 1 * ct_window32 + 2 * ct_window34;
    std::vector<Ciphertext> gout7 = ctx.eval_lut_amortized(&gin7, lut7);

    std::vector<RotationPoly> lut8;
    std::vector<long (*)(long)> flut8;
    auto lut8idx0 = [](long I) -> long {
        /* GATE 23 (LUT2 _149_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut8.push_back(ctx.genrate_lut(lut8idx0));
    flut8.push_back(lut8idx0);
    auto lut8idx1 = [](long I) -> long {
        /* GATE 19 (LUT2 _145_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut8.push_back(ctx.genrate_lut(lut8idx1));
    flut8.push_back(lut8idx1);
    auto fvec8 = [flut8](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut8[i](I));
        return ret;
    };

    std::cerr << "\rLUT8   ";
    Ciphertext gin8 = 1 * ct_window33 + 2 * ct_window35;
    std::vector<Ciphertext> gout8 = ctx.eval_lut_amortized(&gin8, lut8);

    std::cerr << "\rFA9    ";
    Ciphertext gin9 = 0 + 1 * gout2[0] + 1 * gout3[0];
    std::vector<Ciphertext> gout9 = ctx.eval_lut_amortized(&gin9, decomp);

    std::cerr << "\rFA10    ";
    Ciphertext gin10 = gout2[1] + 1 * ct_window41 + 1 * ct_window57;
    std::vector<Ciphertext> gout10 = ctx.eval_lut_amortized(&gin10, decomp);

    std::cerr << "\rFA11    ";
    Ciphertext gin11 = gout3[1] + 1 * ct_window9 + 1 * ct_window25;
    std::vector<Ciphertext> gout11 = ctx.eval_lut_amortized(&gin11, decomp);

    std::cerr << "\rFA12    ";
    Ciphertext gin12 = gout9[1] + 1 * gout10[0] + 1 * gout11[0];
    std::vector<Ciphertext> gout12 = ctx.eval_lut_amortized(&gin12, decomp);

    std::vector<RotationPoly> lut13;
    std::vector<long (*)(long)> flut13;
    auto lut13idx0 = [](long I) -> long {
        /* GATE 17 (LUT2 _143_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut13.push_back(ctx.genrate_lut(lut13idx0));
    flut13.push_back(lut13idx0);
    auto lut13idx1 = [](long I) -> long {
        /* GATE 22 (LUT2 _148_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut13.push_back(ctx.genrate_lut(lut13idx1));
    flut13.push_back(lut13idx1);
    auto fvec13 = [flut13](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut13[i](I));
        return ret;
    };

    std::cerr << "\rLUT13   ";
    Ciphertext gin13 = 1 * gout7[1] + 2 * gout8[1];
    std::vector<Ciphertext> gout13 = ctx.eval_lut_amortized(&gin13, lut13);

    std::vector<RotationPoly> lut14;
    std::vector<long (*)(long)> flut14;
    auto lut14idx0 = [](long I) -> long {
        /* GATE 34 (LUT2 _160_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut14.push_back(ctx.genrate_lut(lut14idx0));
    flut14.push_back(lut14idx0);
    auto lut14idx1 = [](long I) -> long {
        /* GATE 40 (LUT2 _166_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut14.push_back(ctx.genrate_lut(lut14idx1));
    flut14.push_back(lut14idx1);
    auto fvec14 = [flut14](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut14[i](I));
        return ret;
    };

    std::cerr << "\rLUT14   ";
    Ciphertext gin14 = 1 * gout5[0] + 2 * gout0[0];
    std::vector<Ciphertext> gout14 = ctx.eval_lut_amortized(&gin14, lut14);

    std::vector<RotationPoly> lut15;
    std::vector<long (*)(long)> flut15;
    auto lut15idx0 = [](long I) -> long {
        /* GATE 27 (LUT2 _153_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut15.push_back(ctx.genrate_lut(lut15idx0));
    flut15.push_back(lut15idx0);
    auto lut15idx1 = [](long I) -> long {
        /* GATE 33 (LUT2 _159_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut15.push_back(ctx.genrate_lut(lut15idx1));
    flut15.push_back(lut15idx1);
    auto fvec15 = [flut15](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut15[i](I));
        return ret;
    };

    std::cerr << "\rLUT15   ";
    Ciphertext gin15 = 1 * gout4[0] + 2 * gout5[1];
    std::vector<Ciphertext> gout15 = ctx.eval_lut_amortized(&gin15, lut15);

    std::cerr << "\rFA16    ";
    Ciphertext gin16 = gout11[1] + 1 * ct_window10 + 1 * ct_window26;
    std::vector<Ciphertext> gout16 = ctx.eval_lut_amortized(&gin16, decomp);

    std::cerr << "\rINV17   ";
    std::vector<Ciphertext> gout17;
    gout17.push_back(1 - gout12[0]);

    std::cerr << "\rINV18   ";
    std::vector<Ciphertext> gout18;
    gout18.push_back(1 - gout9[0]);

    std::cerr << "\rFA19    ";
    Ciphertext gin19 = gout10[1] + 1 * ct_window42 + 1 * ct_window58;
    std::vector<Ciphertext> gout19 = ctx.eval_lut_amortized(&gin19, decomp);

    std::cerr << "\rFA20    ";
    Ciphertext gin20 = 1 + 1 * ct_window32 + 1 * gout18[0];
    std::vector<Ciphertext> gout20 = ctx.eval_lut_amortized(&gin20, decomp);

    std::cerr << "\rFA21    ";
    Ciphertext gin21 = gout20[1] + 1 * ct_window33 + 1 * gout17[0];
    std::vector<Ciphertext> gout21 = ctx.eval_lut_amortized(&gin21, decomp);

    std::cerr << "\rFA22    ";
    Ciphertext gin22 = gout12[1] + 1 * gout19[0] + 1 * gout16[0];
    std::vector<Ciphertext> gout22 = ctx.eval_lut_amortized(&gin22, decomp);

    std::vector<RotationPoly> lut23;
    std::vector<long (*)(long)> flut23;
    auto lut23idx0 = [](long I) -> long {
        /* GATE 21 (LUT2 _147_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut23.push_back(ctx.genrate_lut(lut23idx0));
    flut23.push_back(lut23idx0);
    auto fvec23 = [flut23](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut23[i](I));
        return ret;
    };

    std::cerr << "\rLUT23   ";
    Ciphertext gin23 = 1 * gout13[1] + 2 * gout8[0];
    std::vector<Ciphertext> gout23 = ctx.eval_lut_amortized(&gin23, lut23);

    std::cerr << "\rFA24    ";
    Ciphertext gin24 = gout19[1] + 1 * ct_window43 + 1 * ct_window59;
    std::vector<Ciphertext> gout24 = ctx.eval_lut_amortized(&gin24, decomp);

    std::cerr << "\rFA25    ";
    Ciphertext gin25 = gout16[1] + 1 * ct_window11 + 1 * ct_window27;
    std::vector<Ciphertext> gout25 = ctx.eval_lut_amortized(&gin25, decomp);

    std::cerr << "\rINV26   ";
    std::vector<Ciphertext> gout26;
    gout26.push_back(1 - gout22[0]);

    std::cerr << "\rFA27    ";
    Ciphertext gin27 = gout21[1] + 1 * gout7[0] + 1 * gout26[0];
    std::vector<Ciphertext> gout27 = ctx.eval_lut_amortized(&gin27, decomp);

    std::cerr << "\rFA28    ";
    Ciphertext gin28 = gout22[1] + 1 * gout24[0] + 1 * gout25[0];
    std::vector<Ciphertext> gout28 = ctx.eval_lut_amortized(&gin28, decomp);

    std::cerr << "\rFA29    ";
    Ciphertext gin29 = gout24[1] + 1 * ct_window44 + 1 * ct_window60;
    std::vector<Ciphertext> gout29 = ctx.eval_lut_amortized(&gin29, decomp);

    std::cerr << "\rFA30    ";
    Ciphertext gin30 = gout25[1] + 1 * ct_window12 + 1 * ct_window28;
    std::vector<Ciphertext> gout30 = ctx.eval_lut_amortized(&gin30, decomp);

    std::vector<RotationPoly> lut31;
    std::vector<long (*)(long)> flut31;
    auto lut31idx0 = [](long I) -> long {
        /* GATE 26 (LUT2 _152_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut31.push_back(ctx.genrate_lut(lut31idx0));
    flut31.push_back(lut31idx0);
    auto lut31idx1 = [](long I) -> long {
        /* GATE 20 (LUT2 _146_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut31.push_back(ctx.genrate_lut(lut31idx1));
    flut31.push_back(lut31idx1);
    auto fvec31 = [flut31](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut31[i](I));
        return ret;
    };

    std::cerr << "\rLUT31   ";
    Ciphertext gin31 = 1 * gout23[0] + 2 * gout4[1];
    std::vector<Ciphertext> gout31 = ctx.eval_lut_amortized(&gin31, lut31);

    std::cerr << "\rINV32   ";
    std::vector<Ciphertext> gout32;
    gout32.push_back(1 - gout28[0]);

    std::cerr << "\rFA33    ";
    Ciphertext gin33 = gout28[1] + 1 * gout29[0] + 1 * gout30[0];
    std::vector<Ciphertext> gout33 = ctx.eval_lut_amortized(&gin33, decomp);

    std::cerr << "\rFA34    ";
    Ciphertext gin34 = gout30[1] + 1 * ct_window13 + 1 * ct_window29;
    std::vector<Ciphertext> gout34 = ctx.eval_lut_amortized(&gin34, decomp);

    std::cerr << "\rFA35    ";
    Ciphertext gin35 = gout27[1] + 1 * gout13[0] + 1 * gout32[0];
    std::vector<Ciphertext> gout35 = ctx.eval_lut_amortized(&gin35, decomp);

    std::cerr << "\rFA36    ";
    Ciphertext gin36 = gout29[1] + 1 * ct_window45 + 1 * ct_window61;
    std::vector<Ciphertext> gout36 = ctx.eval_lut_amortized(&gin36, decomp);

    std::vector<RotationPoly> lut37;
    std::vector<long (*)(long)> flut37;
    auto lut37idx0 = [](long I) -> long {
        /* GATE 32 (LUT2 _158_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut37.push_back(ctx.genrate_lut(lut37idx0));
    flut37.push_back(lut37idx0);
    auto lut37idx1 = [](long I) -> long {
        /* GATE 25 (LUT2 _151_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin37 = 1 * gout31[0] + 2 * gout15[0];
    std::vector<Ciphertext> gout37 = ctx.eval_lut_amortized(&gin37, lut37);

    std::cerr << "\rFA38    ";
    Ciphertext gin38 = gout33[1] + 1 * gout36[0] + 1 * gout34[0];
    std::vector<Ciphertext> gout38 = ctx.eval_lut_amortized(&gin38, decomp);

    std::cerr << "\rINV39   ";
    std::vector<Ciphertext> gout39;
    gout39.push_back(1 - gout33[0]);

    std::vector<RotationPoly> lut40;
    std::vector<long (*)(long)> flut40;
    auto lut40idx0 = [](long I) -> long {
        /* GATE 7 (LUT2 _133_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin40 = 1 * gout35[0] + 2 * gout27[0];
    std::vector<Ciphertext> gout40 = ctx.eval_lut_amortized(&gin40, lut40);

    std::cerr << "\rFA41    ";
    Ciphertext gin41 = gout36[1] + 1 * ct_window46 + 1 * ct_window62;
    std::vector<Ciphertext> gout41 = ctx.eval_lut_amortized(&gin41, decomp);

    std::cerr << "\rFA42    ";
    Ciphertext gin42 = gout34[1] + 1 * ct_window14 + 1 * ct_window30;
    std::vector<Ciphertext> gout42 = ctx.eval_lut_amortized(&gin42, decomp);

    std::cerr << "\rFA43    ";
    Ciphertext gin43 = gout35[1] + 1 * gout31[1] + 1 * gout39[0];
    std::vector<Ciphertext> gout43 = ctx.eval_lut_amortized(&gin43, decomp);

    std::vector<RotationPoly> lut44;
    std::vector<long (*)(long)> flut44;
    auto lut44idx0 = [](long I) -> long {
        /* GATE 31 (LUT2 _157_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin44 = 1 * gout37[0] + 2 * gout15[1];
    std::vector<Ciphertext> gout44 = ctx.eval_lut_amortized(&gin44, lut44);

    std::cerr << "\rINV45   ";
    std::vector<Ciphertext> gout45;
    gout45.push_back(1 - gout38[0]);

    std::cerr << "\rFA46    ";
    Ciphertext gin46 = gout38[1] + 1 * gout41[0] + 1 * gout42[0];
    std::vector<Ciphertext> gout46 = ctx.eval_lut_amortized(&gin46, decomp);

    std::cerr << "\rFA47    ";
    Ciphertext gin47 = gout41[1] + 1 * ct_window47 + 1 * ct_window63;
    std::vector<Ciphertext> gout47 = ctx.eval_lut_amortized(&gin47, decomp);

    std::cerr << "\rFA48    ";
    Ciphertext gin48 = gout42[1] + 1 * ct_window15 + 1 * ct_window31;
    std::vector<Ciphertext> gout48 = ctx.eval_lut_amortized(&gin48, decomp);

    std::cerr << "\rINV49   ";
    std::vector<Ciphertext> gout49;
    gout49.push_back(1 - gout46[0]);

    std::vector<RotationPoly> lut50;
    std::vector<long (*)(long)> flut50;
    auto lut50idx0 = [](long I) -> long {
        /* GATE 39 (LUT2 _165_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut50.push_back(ctx.genrate_lut(lut50idx0));
    flut50.push_back(lut50idx0);
    auto lut50idx1 = [](long I) -> long {
        /* GATE 30 (LUT2 _156_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut50.push_back(ctx.genrate_lut(lut50idx1));
    flut50.push_back(lut50idx1);
    auto fvec50 = [flut50](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut50[i](I));
        return ret;
    };

    std::cerr << "\rLUT50   ";
    Ciphertext gin50 = 1 * gout44[0] + 2 * gout14[0];
    std::vector<Ciphertext> gout50 = ctx.eval_lut_amortized(&gin50, lut50);

    std::cerr << "\rFA51    ";
    Ciphertext gin51 = gout43[1] + 1 * gout37[1] + 1 * gout45[0];
    std::vector<Ciphertext> gout51 = ctx.eval_lut_amortized(&gin51, decomp);

    std::cerr << "\rFA52    ";
    Ciphertext gin52 = gout46[1] + 1 * gout47[0] + 1 * gout48[0];
    std::vector<Ciphertext> gout52 = ctx.eval_lut_amortized(&gin52, decomp);

    std::vector<RotationPoly> lut53;
    std::vector<long (*)(long)> flut53;
    auto lut53idx0 = [](long I) -> long {
        /* GATE 6 (LUT2 _132_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin53 = 1 * gout43[0] + 2 * gout51[0];
    std::vector<Ciphertext> gout53 = ctx.eval_lut_amortized(&gin53, lut53);

    std::vector<RotationPoly> lut54;
    std::vector<long (*)(long)> flut54;
    auto lut54idx0 = [](long I) -> long {
        /* GATE 38 (LUT2 _164_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut54.push_back(ctx.genrate_lut(lut54idx0));
    flut54.push_back(lut54idx0);
    auto fvec54 = [flut54](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut54[i](I));
        return ret;
    };

    std::cerr << "\rLUT54   ";
    Ciphertext gin54 = 1 * gout50[0] + 2 * gout14[1];
    std::vector<Ciphertext> gout54 = ctx.eval_lut_amortized(&gin54, lut54);

    std::cerr << "\rINV55   ";
    std::vector<Ciphertext> gout55;
    gout55.push_back(1 - gout52[0]);

    std::vector<RotationPoly> lut56;
    std::vector<long (*)(long)> flut56;
    auto lut56idx0 = [](long I) -> long {
        /* GATE 37 (LUT2 _163_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut56.push_back(ctx.genrate_lut(lut56idx0));
    flut56.push_back(lut56idx0);
    auto fvec56 = [flut56](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut56[i](I));
        return ret;
    };

    std::cerr << "\rLUT56   ";
    Ciphertext gin56 = 1 * gout54[0] + 2 * gout6[0];
    std::vector<Ciphertext> gout56 = ctx.eval_lut_amortized(&gin56, lut56);

    std::cerr << "\rFA57    ";
    Ciphertext gin57 = gout51[1] + 1 * gout50[1] + 1 * gout49[0];
    std::vector<Ciphertext> gout57 = ctx.eval_lut_amortized(&gin57, decomp);

    std::cerr << "\rFA58    ";
    Ciphertext gin58 = gout57[1] + 1 * gout56[0] + 1 * gout55[0];
    std::vector<Ciphertext> gout58 = ctx.eval_lut_amortized(&gin58, decomp);

    std::vector<RotationPoly> lut59;
    std::vector<long (*)(long)> flut59;
    auto lut59idx0 = [](long I) -> long {
        /* GATE 5 (LUT2 _131_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut59.push_back(ctx.genrate_lut(lut59idx0));
    flut59.push_back(lut59idx0);
    auto fvec59 = [flut59](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut59[i](I));
        return ret;
    };

    std::cerr << "\rLUT59   ";
    Ciphertext gin59 = 1 * gout53[0] + 2 * gout58[0];
    std::vector<Ciphertext> gout59 = ctx.eval_lut_amortized(&gin59, lut59);

    std::vector<RotationPoly> lut60;
    std::vector<long (*)(long)> flut60;
    auto lut60idx0 = [](long I) -> long {
        /* GATE 4 (LUT2 _130_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut60.push_back(ctx.genrate_lut(lut60idx0));
    flut60.push_back(lut60idx0);
    auto fvec60 = [flut60](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut60[i](I));
        return ret;
    };

    std::cerr << "\rLUT60   ";
    Ciphertext gin60 = 1 * gout40[0] + 2 * gout59[0];
    std::vector<Ciphertext> gout60 = ctx.eval_lut_amortized(&gin60, lut60);

    std::vector<RotationPoly> lut61;
    std::vector<long (*)(long)> flut61;
    auto lut61idx0 = [](long I) -> long {
        /* GATE 8 (LUT2 _134_ INIT 0x1 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut61.push_back(ctx.genrate_lut(lut61idx0));
    flut61.push_back(lut61idx0);
    auto fvec61 = [flut61](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut61[i](I));
        return ret;
    };

    std::cerr << "\rLUT61   ";
    Ciphertext gin61 = 1 * gout58[0] + 2 * gout57[0];
    std::vector<Ciphertext> gout61 = ctx.eval_lut_amortized(&gin61, lut61);

    std::vector<RotationPoly> lut62;
    std::vector<long (*)(long)> flut62;
    auto lut62idx0 = [](long I) -> long {
        /* GATE 9 (LUT2 _135_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut62.push_back(ctx.genrate_lut(lut62idx0));
    flut62.push_back(lut62idx0);
    auto fvec62 = [flut62](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut62[i](I));
        return ret;
    };

    std::cerr << "\rLUT62   ";
    Ciphertext gin62 = 1 * gout57[0] + 2 * gout59[0];
    std::vector<Ciphertext> gout62 = ctx.eval_lut_amortized(&gin62, lut62);

    std::vector<RotationPoly> lut63;
    std::vector<long (*)(long)> flut63;
    auto lut63idx0 = [](long I) -> long {
        /* GATE 10 (LUT2 _136_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut63.push_back(ctx.genrate_lut(lut63idx0));
    flut63.push_back(lut63idx0);
    auto fvec63 = [flut63](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut63[i](I));
        return ret;
    };

    std::cerr << "\rLUT63   ";
    Ciphertext gin63 = 1 * gout62[0] + 2 * gout20[0];
    std::vector<Ciphertext> gout63 = ctx.eval_lut_amortized(&gin63, lut63);

    std::vector<RotationPoly> lut64;
    std::vector<long (*)(long)> flut64;
    auto lut64idx0 = [](long I) -> long {
        /* GATE 16 (LUT2 _142_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut64.push_back(ctx.genrate_lut(lut64idx0));
    flut64.push_back(lut64idx0);
    auto fvec64 = [flut64](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut64[i](I));
        return ret;
    };

    std::cerr << "\rLUT64   ";
    Ciphertext gin64 = 1 * gout35[0] + 2 * gout62[0];
    std::vector<Ciphertext> gout64 = ctx.eval_lut_amortized(&gin64, lut64);

    std::vector<RotationPoly> lut65;
    std::vector<long (*)(long)> flut65;
    auto lut65idx0 = [](long I) -> long {
        /* GATE 14 (LUT2 _140_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut65.push_back(ctx.genrate_lut(lut65idx0));
    flut65.push_back(lut65idx0);
    auto fvec65 = [flut65](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut65[i](I));
        return ret;
    };

    std::cerr << "\rLUT65   ";
    Ciphertext gin65 = 1 * gout27[0] + 2 * gout62[0];
    std::vector<Ciphertext> gout65 = ctx.eval_lut_amortized(&gin65, lut65);

    std::vector<RotationPoly> lut66;
    std::vector<long (*)(long)> flut66;
    auto lut66idx0 = [](long I) -> long {
        /* GATE 3 (LUT2 _129_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut66.push_back(ctx.genrate_lut(lut66idx0));
    flut66.push_back(lut66idx0);
    auto fvec66 = [flut66](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut66[i](I));
        return ret;
    };

    std::cerr << "\rLUT66   ";
    Ciphertext gin66 = 1 * gout60[0] + 2 * gout61[0];
    std::vector<Ciphertext> gout66 = ctx.eval_lut_amortized(&gin66, lut66);

    std::vector<RotationPoly> lut67;
    std::vector<long (*)(long)> flut67;
    auto lut67idx0 = [](long I) -> long {
        /* GATE 12 (LUT2 _138_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut67.push_back(ctx.genrate_lut(lut67idx0));
    flut67.push_back(lut67idx0);
    auto fvec67 = [flut67](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut67[i](I));
        return ret;
    };

    std::cerr << "\rLUT67   ";
    Ciphertext gin67 = 1 * gout21[0] + 2 * gout62[0];
    std::vector<Ciphertext> gout67 = ctx.eval_lut_amortized(&gin67, lut67);

    std::vector<RotationPoly> lut68;
    std::vector<long (*)(long)> flut68;
    auto lut68idx0 = [](long I) -> long {
        /* GATE 2 (LUT2 _128_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut68.push_back(ctx.genrate_lut(lut68idx0));
    flut68.push_back(lut68idx0);
    auto fvec68 = [flut68](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut68[i](I));
        return ret;
    };

    std::cerr << "\rLUT68   ";
    Ciphertext gin68 = 1 * gout66[0] + 2 * gout62[0];
    std::vector<Ciphertext> gout68 = ctx.eval_lut_amortized(&gin68, lut68);

    std::vector<RotationPoly> lut69;
    std::vector<long (*)(long)> flut69;
    auto lut69idx0 = [](long I) -> long {
        /* GATE 11 (LUT2 _137_ INIT 0xe PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut69.push_back(ctx.genrate_lut(lut69idx0));
    flut69.push_back(lut69idx0);
    auto fvec69 = [flut69](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut69[i](I));
        return ret;
    };

    std::cerr << "\rLUT69   ";
    Ciphertext gin69 = 1 * gout68[0] + 2 * gout67[0];
    std::vector<Ciphertext> gout69 = ctx.eval_lut_amortized(&gin69, lut69);

    std::vector<RotationPoly> lut70;
    std::vector<long (*)(long)> flut70;
    auto lut70idx0 = [](long I) -> long {
        /* GATE 13 (LUT2 _139_ INIT 0xe PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut70.push_back(ctx.genrate_lut(lut70idx0));
    flut70.push_back(lut70idx0);
    auto fvec70 = [flut70](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut70[i](I));
        return ret;
    };

    std::cerr << "\rLUT70   ";
    Ciphertext gin70 = 1 * gout65[0] + 2 * gout68[0];
    std::vector<Ciphertext> gout70 = ctx.eval_lut_amortized(&gin70, lut70);

    std::vector<RotationPoly> lut71;
    std::vector<long (*)(long)> flut71;
    auto lut71idx0 = [](long I) -> long {
        /* GATE 15 (LUT2 _141_ INIT 0xe PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut71.push_back(ctx.genrate_lut(lut71idx0));
    flut71.push_back(lut71idx0);
    auto fvec71 = [flut71](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut71[i](I));
        return ret;
    };

    std::cerr << "\rLUT71   ";
    Ciphertext gin71 = 1 * gout64[0] + 2 * gout68[0];
    std::vector<Ciphertext> gout71 = ctx.eval_lut_amortized(&gin71, lut71);

    std::vector<RotationPoly> lut72;
    std::vector<long (*)(long)> flut72;
    auto lut72idx0 = [](long I) -> long {
        /* GATE 1 (LUT2 _127_ INIT 0xe PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut72.push_back(ctx.genrate_lut(lut72idx0));
    flut72.push_back(lut72idx0);
    auto fvec72 = [flut72](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut72[i](I));
        return ret;
    };

    std::cerr << "\rLUT72   ";
    Ciphertext gin72 = 1 * gout63[0] + 2 * gout68[0];
    std::vector<Ciphertext> gout72 = ctx.eval_lut_amortized(&gin72, lut72);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(ctx.decrypt(&gout72[0])); /* out0 */
    test_out.push_back(ctx.decrypt(&gout69[0])); /* out1 */
    test_out.push_back(ctx.decrypt(&gout70[0])); /* out2 */
    test_out.push_back(ctx.decrypt(&gout71[0])); /* out3 */
    test_out.push_back(0); /* out7 */
    return test_out;
}

static void
BM_image_sharpen_lut2fa(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(tfhe_11_NTT);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(4);

    for (auto _ : state) {
        test_image_sharpen_lut2fa(ctx);
    }
}

BENCHMARK(BM_image_sharpen_lut2fa)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
