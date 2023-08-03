#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_image_sharpen_lut3fa(FHEContext& ctx, uint64_t window = 0)
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
        /* GATE 26 (LUT2 _101_ INIT 0x8 PERM 10) */
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
    lut0.push_back(ctx.genrate_lut(lut0idx0));
    flut0.push_back(lut0idx0);
    auto fvec0 = [flut0](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut0[i](I));
        return ret;
    };

    std::cerr << "\rLUT0   ";
    Ciphertext gin0 = 1 * ct_window38 + 2 * ct_window36;
    std::vector<Ciphertext> gout0 = ctx.eval_lut_amortized(&gin0, lut0);

    std::cerr << "\rFA1    ";
    Ciphertext gin1 = 0 + 1 * ct_window40 + 2 * ct_window41 + 1 * ct_window56 + 2 * ct_window57;
    std::vector<Ciphertext> gout1 = ctx.eval_lut_amortized(&gin1, decomp);

    std::cerr << "\rFA2    ";
    Ciphertext gin2 = 0 + 1 * ct_window8 + 2 * ct_window9 + 1 * ct_window24 + 2 * ct_window25;
    std::vector<Ciphertext> gout2 = ctx.eval_lut_amortized(&gin2, decomp);

    std::cerr << "\rFA3    ";
    Ciphertext gin3 = 0 + 1 * gout1[0] + 2 * gout1[1] + 1 * gout2[0] + 2 * gout2[1];
    std::vector<Ciphertext> gout3 = ctx.eval_lut_amortized(&gin3, decomp);

    std::vector<RotationPoly> lut4;
    std::vector<long (*)(long)> flut4;
    auto lut4idx0 = [](long I) -> long {
        /* GATE 25 (LUT3 _100_ INIT 0x69 PERM 021) */
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
    lut4.push_back(ctx.genrate_lut(lut4idx0));
    flut4.push_back(lut4idx0);
    auto fvec4 = [flut4](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut4[i](I));
        return ret;
    };

    std::cerr << "\rLUT4   ";
    Ciphertext gin4 = 1 * gout0[0] + 2 * ct_window39 + 4 * ct_window37;
    std::vector<Ciphertext> gout4 = ctx.eval_lut_amortized(&gin4, lut4);

    std::cerr << "\rINV5   ";
    std::vector<Ciphertext> gout5;
    gout5.push_back(1 - gout3[0]);

    std::vector<RotationPoly> lut6;
    std::vector<long (*)(long)> flut6;
    auto lut6idx0 = [](long I) -> long {
        /* GATE 27 (LUT2 _102_ INIT 0x6 PERM 01) */
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
    lut6.push_back(ctx.genrate_lut(lut6idx0));
    flut6.push_back(lut6idx0);
    auto lut6idx1 = [](long I) -> long {
        /* GATE 10 (LUT2 _085_ INIT 0x8 PERM 01) */
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
    lut6.push_back(ctx.genrate_lut(lut6idx1));
    flut6.push_back(lut6idx1);
    auto fvec6 = [flut6](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut6[i](I));
        return ret;
    };

    std::cerr << "\rLUT6   ";
    Ciphertext gin6 = 1 * ct_window34 + 2 * ct_window32;
    std::vector<Ciphertext> gout6 = ctx.eval_lut_amortized(&gin6, lut6);

    std::vector<RotationPoly> lut7;
    std::vector<long (*)(long)> flut7;
    auto lut7idx0 = [](long I) -> long {
        /* GATE 9 (LUT3 _084_ INIT 0x96 PERM 012) */
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
    lut7.push_back(ctx.genrate_lut(lut7idx0));
    flut7.push_back(lut7idx0);
    auto lut7idx1 = [](long I) -> long {
        /* GATE 12 (LUT3 _087_ INIT 0x17 PERM 012) */
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
    lut7.push_back(ctx.genrate_lut(lut7idx1));
    flut7.push_back(lut7idx1);
    auto fvec7 = [flut7](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut7[i](I));
        return ret;
    };

    std::cerr << "\rLUT7   ";
    Ciphertext gin7 = 1 * gout6[1] + 2 * ct_window35 + 4 * ct_window33;
    std::vector<Ciphertext> gout7 = ctx.eval_lut_amortized(&gin7, lut7);

    std::vector<RotationPoly> lut8;
    std::vector<long (*)(long)> flut8;
    auto lut8idx0 = [](long I) -> long {
        /* GATE 21 (LUT2 _096_ INIT 0x8 PERM 10) */
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
    lut8.push_back(ctx.genrate_lut(lut8idx0));
    flut8.push_back(lut8idx0);
    auto fvec8 = [flut8](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut8[i](I));
        return ret;
    };

    std::cerr << "\rLUT8   ";
    Ciphertext gin8 = 1 * ct_window37 + 2 * ct_window35;
    std::vector<Ciphertext> gout8 = ctx.eval_lut_amortized(&gin8, lut8);

    std::vector<RotationPoly> lut9;
    std::vector<long (*)(long)> flut9;
    auto lut9idx0 = [](long I) -> long {
        /* GATE 13 (LUT2 _088_ INIT 0x6 PERM 10) */
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
    lut9.push_back(ctx.genrate_lut(lut9idx0));
    flut9.push_back(lut9idx0);
    auto lut9idx1 = [](long I) -> long {
        /* GATE 16 (LUT2 _091_ INIT 0x8 PERM 10) */
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
    lut9.push_back(ctx.genrate_lut(lut9idx1));
    flut9.push_back(lut9idx1);
    auto fvec9 = [flut9](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut9[i](I));
        return ret;
    };

    std::cerr << "\rLUT9   ";
    Ciphertext gin9 = 1 * ct_window36 + 2 * ct_window34;
    std::vector<Ciphertext> gout9 = ctx.eval_lut_amortized(&gin9, lut9);

    std::vector<RotationPoly> lut10;
    std::vector<long (*)(long)> flut10;
    auto lut10idx0 = [](long I) -> long {
        /* GATE 15 (LUT3 _090_ INIT 0x96 PERM 120) */
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
    lut10.push_back(ctx.genrate_lut(lut10idx0));
    flut10.push_back(lut10idx0);
    auto lut10idx1 = [](long I) -> long {
        /* GATE 19 (LUT3 _094_ INIT 0x60 PERM 201) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut10.push_back(ctx.genrate_lut(lut10idx1));
    flut10.push_back(lut10idx1);
    auto fvec10 = [flut10](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut10[i](I));
        return ret;
    };

    std::cerr << "\rLUT10   ";
    Ciphertext gin10 = 1 * ct_window37 + 2 * gout9[1] + 4 * ct_window35;
    std::vector<Ciphertext> gout10 = ctx.eval_lut_amortized(&gin10, lut10);

    std::cerr << "\rFA11    ";
    Ciphertext gin11 = gout2[2] + 1 * ct_window10 + 2 * ct_window11 + 1 * ct_window26 + 2 * ct_window27;
    std::vector<Ciphertext> gout11 = ctx.eval_lut_amortized(&gin11, decomp);

    std::cerr << "\rFA12    ";
    Ciphertext gin12 = gout1[2] + 1 * ct_window42 + 2 * ct_window43 + 1 * ct_window58 + 2 * ct_window59;
    std::vector<Ciphertext> gout12 = ctx.eval_lut_amortized(&gin12, decomp);

    std::cerr << "\rFA13    ";
    Ciphertext gin13 = gout11[2] + 1 * ct_window12 + 2 * ct_window13 + 1 * ct_window28 + 2 * ct_window29;
    std::vector<Ciphertext> gout13 = ctx.eval_lut_amortized(&gin13, decomp);

    std::cerr << "\rINV14   ";
    std::vector<Ciphertext> gout14;
    gout14.push_back(1 - gout3[1]);

    std::vector<RotationPoly> lut15;
    std::vector<long (*)(long)> flut15;
    auto lut15idx0 = [](long I) -> long {
        /* GATE 24 (LUT3 _099_ INIT 0x60 PERM 201) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut15.push_back(ctx.genrate_lut(lut15idx0));
    flut15.push_back(lut15idx0);
    auto lut15idx1 = [](long I) -> long {
        /* GATE 20 (LUT3 _095_ INIT 0x96 PERM 120) */
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
    lut15.push_back(ctx.genrate_lut(lut15idx1));
    flut15.push_back(lut15idx1);
    auto fvec15 = [flut15](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut15[i](I));
        return ret;
    };

    std::cerr << "\rLUT15   ";
    Ciphertext gin15 = 1 * ct_window38 + 2 * gout8[0] + 4 * ct_window36;
    std::vector<Ciphertext> gout15 = ctx.eval_lut_amortized(&gin15, lut15);

    std::vector<RotationPoly> lut16;
    std::vector<long (*)(long)> flut16;
    auto lut16idx0 = [](long I) -> long {
        /* GATE 14 (LUT3 _089_ INIT 0xb4 PERM 120) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut16.push_back(ctx.genrate_lut(lut16idx0));
    flut16.push_back(lut16idx0);
    auto lut16idx1 = [](long I) -> long {
        /* GATE 18 (LUT3 _093_ INIT 0x40 PERM 102) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut16.push_back(ctx.genrate_lut(lut16idx1));
    flut16.push_back(lut16idx1);
    auto lut16idx2 = [](long I) -> long {
        /* GATE 11 (LUT2 _086_ INIT 0x9 PERM 12) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut16.push_back(ctx.genrate_lut(lut16idx2));
    flut16.push_back(lut16idx2);
    auto fvec16 = [flut16](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 3; ++i)
            ret.push_back(flut16[i](I));
        return ret;
    };

    std::cerr << "\rLUT16   ";
    Ciphertext gin16 = 1 * gout10[0] + 2 * gout7[1] + 4 * gout9[0];
    std::vector<Ciphertext> gout16 = ctx.eval_lut_amortized(&gin16, lut16);

    std::cerr << "\rFA17    ";
    Ciphertext gin17 = 1 + 1 * ct_window32 + 2 * ct_window33 + 1 * gout5[0] + 2 * gout14[0];
    std::vector<Ciphertext> gout17 = ctx.eval_lut_amortized(&gin17, decomp);

    std::cerr << "\rFA18    ";
    Ciphertext gin18 = gout12[2] + 1 * ct_window44 + 2 * ct_window45 + 1 * ct_window60 + 2 * ct_window61;
    std::vector<Ciphertext> gout18 = ctx.eval_lut_amortized(&gin18, decomp);

    std::cerr << "\rFA19    ";
    Ciphertext gin19 = gout13[2] + 1 * ct_window14 + 2 * ct_window15 + 1 * ct_window30 + 2 * ct_window31;
    std::vector<Ciphertext> gout19 = ctx.eval_lut_amortized(&gin19, decomp);

    std::cerr << "\rFA20    ";
    Ciphertext gin20 = gout3[2] + 1 * gout12[0] + 2 * gout12[1] + 1 * gout11[0] + 2 * gout11[1];
    std::vector<Ciphertext> gout20 = ctx.eval_lut_amortized(&gin20, decomp);

    std::cerr << "\rFA21    ";
    Ciphertext gin21 = gout18[2] + 1 * ct_window46 + 2 * ct_window47 + 1 * ct_window62 + 2 * ct_window63;
    std::vector<Ciphertext> gout21 = ctx.eval_lut_amortized(&gin21, decomp);

    std::cerr << "\rINV22   ";
    std::vector<Ciphertext> gout22;
    gout22.push_back(1 - gout20[1]);

    std::cerr << "\rINV23   ";
    std::vector<Ciphertext> gout23;
    gout23.push_back(1 - gout20[0]);

    std::cerr << "\rFA24    ";
    Ciphertext gin24 = gout17[2] + 1 * gout6[0] + 2 * gout7[0] + 1 * gout23[0] + 2 * gout22[0];
    std::vector<Ciphertext> gout24 = ctx.eval_lut_amortized(&gin24, decomp);

    std::cerr << "\rFA25    ";
    Ciphertext gin25 = gout20[2] + 1 * gout18[0] + 2 * gout18[1] + 1 * gout13[0] + 2 * gout13[1];
    std::vector<Ciphertext> gout25 = ctx.eval_lut_amortized(&gin25, decomp);

    std::cerr << "\rINV26   ";
    std::vector<Ciphertext> gout26;
    gout26.push_back(1 - gout25[1]);

    std::vector<RotationPoly> lut27;
    std::vector<long (*)(long)> flut27;
    auto lut27idx0 = [](long I) -> long {
        /* GATE 17 (LUT3 _092_ INIT 0x1e PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut27.push_back(ctx.genrate_lut(lut27idx0));
    flut27.push_back(lut27idx0);
    auto lut27idx1 = [](long I) -> long {
        /* GATE 23 (LUT3 _098_ INIT 0xe0 PERM 102) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut27.push_back(ctx.genrate_lut(lut27idx1));
    flut27.push_back(lut27idx1);
    auto fvec27 = [flut27](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut27[i](I));
        return ret;
    };

    std::cerr << "\rLUT27   ";
    Ciphertext gin27 = 1 * gout16[1] + 2 * gout10[1] + 4 * gout15[1];
    std::vector<Ciphertext> gout27 = ctx.eval_lut_amortized(&gin27, lut27);

    std::cerr << "\rFA28    ";
    Ciphertext gin28 = gout25[2] + 1 * gout21[0] + 2 * gout21[1] + 1 * gout19[0] + 2 * gout19[1];
    std::vector<Ciphertext> gout28 = ctx.eval_lut_amortized(&gin28, decomp);

    std::vector<RotationPoly> lut29;
    std::vector<long (*)(long)> flut29;
    auto lut29idx0 = [](long I) -> long {
        /* GATE 22 (LUT3 _097_ INIT 0xe1 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut29.push_back(ctx.genrate_lut(lut29idx0));
    flut29.push_back(lut29idx0);
    auto fvec29 = [flut29](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut29[i](I));
        return ret;
    };

    std::cerr << "\rLUT29   ";
    Ciphertext gin29 = 1 * gout27[1] + 2 * gout15[0] + 4 * gout4[0];
    std::vector<Ciphertext> gout29 = ctx.eval_lut_amortized(&gin29, lut29);

    std::cerr << "\rINV30   ";
    std::vector<Ciphertext> gout30;
    gout30.push_back(1 - gout25[0]);

    std::cerr << "\rINV31   ";
    std::vector<Ciphertext> gout31;
    gout31.push_back(1 - gout28[1]);

    std::cerr << "\rINV32   ";
    std::vector<Ciphertext> gout32;
    gout32.push_back(1 - gout28[0]);

    std::cerr << "\rFA33    ";
    Ciphertext gin33 = gout24[2] + 1 * gout16[2] + 2 * gout16[0] + 1 * gout30[0] + 2 * gout26[0];
    std::vector<Ciphertext> gout33 = ctx.eval_lut_amortized(&gin33, decomp);

    std::cerr << "\rFA34    ";
    Ciphertext gin34 = gout33[2] + 1 * gout27[0] + 2 * gout29[0] + 1 * gout32[0] + 2 * gout31[0];
    std::vector<Ciphertext> gout34 = ctx.eval_lut_amortized(&gin34, decomp);

    std::vector<RotationPoly> lut35;
    std::vector<long (*)(long)> flut35;
    auto lut35idx0 = [](long I) -> long {
        /* GATE 4 (LUT3 _079_ INIT 0x1 PERM 012) */
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
    lut35.push_back(ctx.genrate_lut(lut35idx0));
    flut35.push_back(lut35idx0);
    auto fvec35 = [flut35](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut35[i](I));
        return ret;
    };

    std::cerr << "\rLUT35   ";
    Ciphertext gin35 = 1 * gout33[0] + 2 * gout33[1] + 4 * gout34[1];
    std::vector<Ciphertext> gout35 = ctx.eval_lut_amortized(&gin35, lut35);

    std::vector<RotationPoly> lut36;
    std::vector<long (*)(long)> flut36;
    auto lut36idx0 = [](long I) -> long {
        /* GATE 5 (LUT2 _080_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut36.push_back(ctx.genrate_lut(lut36idx0));
    flut36.push_back(lut36idx0);
    auto fvec36 = [flut36](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut36[i](I));
        return ret;
    };

    std::cerr << "\rLUT36   ";
    Ciphertext gin36 = 1 * gout34[0] + 2 * gout35[0];
    std::vector<Ciphertext> gout36 = ctx.eval_lut_amortized(&gin36, lut36);

    std::vector<RotationPoly> lut37;
    std::vector<long (*)(long)> flut37;
    auto lut37idx0 = [](long I) -> long {
        /* GATE 3 (LUT3 _078_ INIT 0x70 PERM 120) */
        switch (I) {
            case  0: return 0;
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
    lut37.push_back(ctx.genrate_lut(lut37idx0));
    flut37.push_back(lut37idx0);
    auto fvec37 = [flut37](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut37[i](I));
        return ret;
    };

    std::cerr << "\rLUT37   ";
    Ciphertext gin37 = 1 * gout35[0] + 2 * gout24[1] + 4 * gout24[0];
    std::vector<Ciphertext> gout37 = ctx.eval_lut_amortized(&gin37, lut37);

    std::vector<RotationPoly> lut38;
    std::vector<long (*)(long)> flut38;
    auto lut38idx0 = [](long I) -> long {
        /* GATE 2 (LUT3 _077_ INIT 0xe PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
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
    Ciphertext gin38 = 1 * gout34[1] + 2 * gout37[0] + 4 * gout34[0];
    std::vector<Ciphertext> gout38 = ctx.eval_lut_amortized(&gin38, lut38);

    std::vector<RotationPoly> lut39;
    std::vector<long (*)(long)> flut39;
    auto lut39idx0 = [](long I) -> long {
        /* GATE 7 (LUT3 _082_ INIT 0xa3 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
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
    Ciphertext gin39 = 1 * gout24[0] + 2 * gout38[0] + 4 * gout36[0];
    std::vector<Ciphertext> gout39 = ctx.eval_lut_amortized(&gin39, lut39);

    std::vector<RotationPoly> lut40;
    std::vector<long (*)(long)> flut40;
    auto lut40idx0 = [](long I) -> long {
        /* GATE 6 (LUT3 _081_ INIT 0xa3 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
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
    Ciphertext gin40 = 1 * gout17[1] + 2 * gout38[0] + 4 * gout36[0];
    std::vector<Ciphertext> gout40 = ctx.eval_lut_amortized(&gin40, lut40);

    std::vector<RotationPoly> lut41;
    std::vector<long (*)(long)> flut41;
    auto lut41idx0 = [](long I) -> long {
        /* GATE 1 (LUT3 _076_ INIT 0xa3 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
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
    Ciphertext gin41 = 1 * gout17[0] + 2 * gout38[0] + 4 * gout36[0];
    std::vector<Ciphertext> gout41 = ctx.eval_lut_amortized(&gin41, lut41);

    std::vector<RotationPoly> lut42;
    std::vector<long (*)(long)> flut42;
    auto lut42idx0 = [](long I) -> long {
        /* GATE 8 (LUT3 _083_ INIT 0xa3 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
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
    Ciphertext gin42 = 1 * gout24[1] + 2 * gout38[0] + 4 * gout36[0];
    std::vector<Ciphertext> gout42 = ctx.eval_lut_amortized(&gin42, lut42);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(ctx.decrypt(&gout41[0])); /* out0 */
    test_out.push_back(ctx.decrypt(&gout40[0])); /* out1 */
    test_out.push_back(ctx.decrypt(&gout39[0])); /* out2 */
    test_out.push_back(ctx.decrypt(&gout42[0])); /* out3 */
    test_out.push_back(0); /* out7 */
    return test_out;
}

static void
BM_image_sharpen_lut3fa(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(tfhe_11_NTT_amortized);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(8);

    for (auto _ : state) {
        test_image_sharpen_lut3fa(ctx);
    }
}

BENCHMARK(BM_image_sharpen_lut3fa)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
