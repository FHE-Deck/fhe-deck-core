#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_strrev_lut3(FHEContext& ctx, uint64_t my_string = 0)
{
    Ciphertext ct_my_string0 = ctx.encrypt_public((my_string >> 0) & 1);
    Ciphertext ct_my_string1 = ctx.encrypt_public((my_string >> 1) & 1);
    Ciphertext ct_my_string2 = ctx.encrypt_public((my_string >> 2) & 1);
    Ciphertext ct_my_string3 = ctx.encrypt_public((my_string >> 3) & 1);
    Ciphertext ct_my_string4 = ctx.encrypt_public((my_string >> 4) & 1);
    Ciphertext ct_my_string5 = ctx.encrypt_public((my_string >> 5) & 1);
    Ciphertext ct_my_string6 = ctx.encrypt_public((my_string >> 6) & 1);
    Ciphertext ct_my_string7 = ctx.encrypt_public((my_string >> 7) & 1);
    Ciphertext ct_my_string8 = ctx.encrypt_public((my_string >> 8) & 1);
    Ciphertext ct_my_string9 = ctx.encrypt_public((my_string >> 9) & 1);
    Ciphertext ct_my_string10 = ctx.encrypt_public((my_string >> 10) & 1);
    Ciphertext ct_my_string11 = ctx.encrypt_public((my_string >> 11) & 1);
    Ciphertext ct_my_string12 = ctx.encrypt_public((my_string >> 12) & 1);
    Ciphertext ct_my_string13 = ctx.encrypt_public((my_string >> 13) & 1);
    Ciphertext ct_my_string14 = ctx.encrypt_public((my_string >> 14) & 1);
    Ciphertext ct_my_string15 = ctx.encrypt_public((my_string >> 15) & 1);
    Ciphertext ct_my_string16 = ctx.encrypt_public((my_string >> 16) & 1);
    Ciphertext ct_my_string17 = ctx.encrypt_public((my_string >> 17) & 1);
    Ciphertext ct_my_string18 = ctx.encrypt_public((my_string >> 18) & 1);
    Ciphertext ct_my_string19 = ctx.encrypt_public((my_string >> 19) & 1);
    Ciphertext ct_my_string20 = ctx.encrypt_public((my_string >> 20) & 1);
    Ciphertext ct_my_string21 = ctx.encrypt_public((my_string >> 21) & 1);
    Ciphertext ct_my_string22 = ctx.encrypt_public((my_string >> 22) & 1);
    Ciphertext ct_my_string23 = ctx.encrypt_public((my_string >> 23) & 1);
    Ciphertext ct_my_string24 = ctx.encrypt_public((my_string >> 24) & 1);
    Ciphertext ct_my_string25 = ctx.encrypt_public((my_string >> 25) & 1);
    Ciphertext ct_my_string26 = ctx.encrypt_public((my_string >> 26) & 1);
    Ciphertext ct_my_string27 = ctx.encrypt_public((my_string >> 27) & 1);
    Ciphertext ct_my_string28 = ctx.encrypt_public((my_string >> 28) & 1);
    Ciphertext ct_my_string29 = ctx.encrypt_public((my_string >> 29) & 1);
    Ciphertext ct_my_string30 = ctx.encrypt_public((my_string >> 30) & 1);
    Ciphertext ct_my_string31 = ctx.encrypt_public((my_string >> 31) & 1);
    Ciphertext ct_my_string32 = ctx.encrypt_public((my_string >> 32) & 1);
    Ciphertext ct_my_string33 = ctx.encrypt_public((my_string >> 33) & 1);
    Ciphertext ct_my_string34 = ctx.encrypt_public((my_string >> 34) & 1);
    Ciphertext ct_my_string35 = ctx.encrypt_public((my_string >> 35) & 1);
    Ciphertext ct_my_string36 = ctx.encrypt_public((my_string >> 36) & 1);
    Ciphertext ct_my_string37 = ctx.encrypt_public((my_string >> 37) & 1);
    Ciphertext ct_my_string38 = ctx.encrypt_public((my_string >> 38) & 1);
    Ciphertext ct_my_string39 = ctx.encrypt_public((my_string >> 39) & 1);
    Ciphertext ct_my_string40 = ctx.encrypt_public((my_string >> 40) & 1);
    Ciphertext ct_my_string41 = ctx.encrypt_public((my_string >> 41) & 1);
    Ciphertext ct_my_string42 = ctx.encrypt_public((my_string >> 42) & 1);
    Ciphertext ct_my_string43 = ctx.encrypt_public((my_string >> 43) & 1);
    Ciphertext ct_my_string44 = ctx.encrypt_public((my_string >> 44) & 1);
    Ciphertext ct_my_string45 = ctx.encrypt_public((my_string >> 45) & 1);
    Ciphertext ct_my_string46 = ctx.encrypt_public((my_string >> 46) & 1);
    Ciphertext ct_my_string47 = ctx.encrypt_public((my_string >> 47) & 1);
    Ciphertext ct_my_string48 = ctx.encrypt_public((my_string >> 48) & 1);
    Ciphertext ct_my_string49 = ctx.encrypt_public((my_string >> 49) & 1);
    Ciphertext ct_my_string50 = ctx.encrypt_public((my_string >> 50) & 1);
    Ciphertext ct_my_string51 = ctx.encrypt_public((my_string >> 51) & 1);
    Ciphertext ct_my_string52 = ctx.encrypt_public((my_string >> 52) & 1);
    Ciphertext ct_my_string53 = ctx.encrypt_public((my_string >> 53) & 1);
    Ciphertext ct_my_string54 = ctx.encrypt_public((my_string >> 54) & 1);
    Ciphertext ct_my_string55 = ctx.encrypt_public((my_string >> 55) & 1);
    Ciphertext ct_my_string56 = ctx.encrypt_public((my_string >> 56) & 1);
    Ciphertext ct_my_string57 = ctx.encrypt_public((my_string >> 57) & 1);
    Ciphertext ct_my_string58 = ctx.encrypt_public((my_string >> 58) & 1);
    Ciphertext ct_my_string59 = ctx.encrypt_public((my_string >> 59) & 1);
    Ciphertext ct_my_string60 = ctx.encrypt_public((my_string >> 60) & 1);
    Ciphertext ct_my_string61 = ctx.encrypt_public((my_string >> 61) & 1);
    Ciphertext ct_my_string62 = ctx.encrypt_public((my_string >> 62) & 1);
    Ciphertext ct_my_string63 = ctx.encrypt_public((my_string >> 63) & 1);

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
        /* GATE 22 (LUT2 _1049_ INIT 0x1 PERM 01) */
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
    lut0.push_back(ctx.genrate_lut(lut0idx0));
    flut0.push_back(lut0idx0);
    auto fvec0 = [flut0](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut0[i](I));
        return ret;
    };

    std::cerr << "\rLUT0   ";
    Ciphertext gin0 = 1 * ct_my_string61 + 2 * ct_my_string62;
    std::vector<Ciphertext> gout0 = ctx.eval_lut_amortized(&gin0, lut0);

    std::vector<RotationPoly> lut1;
    std::vector<long (*)(long)> flut1;
    auto lut1idx0 = [](long I) -> long {
        /* GATE 37 (LUT3 _1064_ INIT 0x1 PERM 102) */
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
    lut1.push_back(ctx.genrate_lut(lut1idx0));
    flut1.push_back(lut1idx0);
    auto fvec1 = [flut1](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut1[i](I));
        return ret;
    };

    std::cerr << "\rLUT1   ";
    Ciphertext gin1 = 1 * ct_my_string9 + 2 * ct_my_string8 + 4 * ct_my_string10;
    std::vector<Ciphertext> gout1 = ctx.eval_lut_amortized(&gin1, lut1);

    std::vector<RotationPoly> lut2;
    std::vector<long (*)(long)> flut2;
    auto lut2idx0 = [](long I) -> long {
        /* GATE 21 (LUT3 _1048_ INIT 0x10 PERM 120) */
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
    lut2.push_back(ctx.genrate_lut(lut2idx0));
    flut2.push_back(lut2idx0);
    auto fvec2 = [flut2](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut2[i](I));
        return ret;
    };

    std::cerr << "\rLUT2   ";
    Ciphertext gin2 = 1 * gout0[0] + 2 * ct_my_string60 + 4 * ct_my_string63;
    std::vector<Ciphertext> gout2 = ctx.eval_lut_amortized(&gin2, lut2);

    std::vector<RotationPoly> lut3;
    std::vector<long (*)(long)> flut3;
    auto lut3idx0 = [](long I) -> long {
        /* GATE 14 (LUT2 _1041_ INIT 0x1 PERM 10) */
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
    lut3.push_back(ctx.genrate_lut(lut3idx0));
    flut3.push_back(lut3idx0);
    auto fvec3 = [flut3](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut3[i](I));
        return ret;
    };

    std::cerr << "\rLUT3   ";
    Ciphertext gin3 = 1 * ct_my_string43 + 2 * ct_my_string42;
    std::vector<Ciphertext> gout3 = ctx.eval_lut_amortized(&gin3, lut3);

    std::vector<RotationPoly> lut4;
    std::vector<long (*)(long)> flut4;
    auto lut4idx0 = [](long I) -> long {
        /* GATE 17 (LUT2 _1044_ INIT 0x1 PERM 01) */
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
    lut4.push_back(ctx.genrate_lut(lut4idx0));
    flut4.push_back(lut4idx0);
    auto fvec4 = [flut4](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut4[i](I));
        return ret;
    };

    std::cerr << "\rLUT4   ";
    Ciphertext gin4 = 1 * ct_my_string53 + 2 * ct_my_string54;
    std::vector<Ciphertext> gout4 = ctx.eval_lut_amortized(&gin4, lut4);

    std::vector<RotationPoly> lut5;
    std::vector<long (*)(long)> flut5;
    auto lut5idx0 = [](long I) -> long {
        /* GATE 48 (LUT3 _1075_ INIT 0x1 PERM 012) */
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
    lut5.push_back(ctx.genrate_lut(lut5idx0));
    flut5.push_back(lut5idx0);
    auto fvec5 = [flut5](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut5[i](I));
        return ret;
    };

    std::cerr << "\rLUT5   ";
    Ciphertext gin5 = 1 * ct_my_string0 + 2 * ct_my_string1 + 4 * ct_my_string2;
    std::vector<Ciphertext> gout5 = ctx.eval_lut_amortized(&gin5, lut5);

    std::vector<RotationPoly> lut6;
    std::vector<long (*)(long)> flut6;
    auto lut6idx0 = [](long I) -> long {
        /* GATE 24 (LUT2 _1051_ INIT 0x1 PERM 01) */
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
    lut6.push_back(ctx.genrate_lut(lut6idx0));
    flut6.push_back(lut6idx0);
    auto fvec6 = [flut6](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut6[i](I));
        return ret;
    };

    std::cerr << "\rLUT6   ";
    Ciphertext gin6 = 1 * ct_my_string57 + 2 * ct_my_string58;
    std::vector<Ciphertext> gout6 = ctx.eval_lut_amortized(&gin6, lut6);

    std::vector<RotationPoly> lut7;
    std::vector<long (*)(long)> flut7;
    auto lut7idx0 = [](long I) -> long {
        /* GATE 40 (LUT2 _1067_ INIT 0x1 PERM 01) */
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
    lut7.push_back(ctx.genrate_lut(lut7idx0));
    flut7.push_back(lut7idx0);
    auto fvec7 = [flut7](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut7[i](I));
        return ret;
    };

    std::cerr << "\rLUT7   ";
    Ciphertext gin7 = 1 * ct_my_string21 + 2 * ct_my_string22;
    std::vector<Ciphertext> gout7 = ctx.eval_lut_amortized(&gin7, lut7);

    std::vector<RotationPoly> lut8;
    std::vector<long (*)(long)> flut8;
    auto lut8idx0 = [](long I) -> long {
        /* GATE 16 (LUT3 _1043_ INIT 0x10 PERM 210) */
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
    lut8.push_back(ctx.genrate_lut(lut8idx0));
    flut8.push_back(lut8idx0);
    auto fvec8 = [flut8](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut8[i](I));
        return ret;
    };

    std::cerr << "\rLUT8   ";
    Ciphertext gin8 = 1 * gout4[0] + 2 * ct_my_string55 + 4 * ct_my_string52;
    std::vector<Ciphertext> gout8 = ctx.eval_lut_amortized(&gin8, lut8);

    std::vector<RotationPoly> lut9;
    std::vector<long (*)(long)> flut9;
    auto lut9idx0 = [](long I) -> long {
        /* GATE 12 (LUT2 _1039_ INIT 0x1 PERM 10) */
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
    lut9.push_back(ctx.genrate_lut(lut9idx0));
    flut9.push_back(lut9idx0);
    auto fvec9 = [flut9](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut9[i](I));
        return ret;
    };

    std::cerr << "\rLUT9   ";
    Ciphertext gin9 = 1 * ct_my_string47 + 2 * ct_my_string46;
    std::vector<Ciphertext> gout9 = ctx.eval_lut_amortized(&gin9, lut9);

    std::vector<RotationPoly> lut10;
    std::vector<long (*)(long)> flut10;
    auto lut10idx0 = [](long I) -> long {
        /* GATE 31 (LUT2 _1058_ INIT 0x1 PERM 10) */
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
    lut10.push_back(ctx.genrate_lut(lut10idx0));
    flut10.push_back(lut10idx0);
    auto fvec10 = [flut10](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut10[i](I));
        return ret;
    };

    std::cerr << "\rLUT10   ";
    Ciphertext gin10 = 1 * ct_my_string38 + 2 * ct_my_string37;
    std::vector<Ciphertext> gout10 = ctx.eval_lut_amortized(&gin10, lut10);

    std::vector<RotationPoly> lut11;
    std::vector<long (*)(long)> flut11;
    auto lut11idx0 = [](long I) -> long {
        /* GATE 28 (LUT3 _1055_ INIT 0x1 PERM 021) */
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
    lut11.push_back(ctx.genrate_lut(lut11idx0));
    flut11.push_back(lut11idx0);
    auto fvec11 = [flut11](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut11[i](I));
        return ret;
    };

    std::cerr << "\rLUT11   ";
    Ciphertext gin11 = 1 * ct_my_string24 + 2 * ct_my_string26 + 4 * ct_my_string25;
    std::vector<Ciphertext> gout11 = ctx.eval_lut_amortized(&gin11, lut11);

    std::vector<RotationPoly> lut12;
    std::vector<long (*)(long)> flut12;
    auto lut12idx0 = [](long I) -> long {
        /* GATE 33 (LUT2 _1060_ INIT 0x1 PERM 01) */
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
    lut12.push_back(ctx.genrate_lut(lut12idx0));
    flut12.push_back(lut12idx0);
    auto fvec12 = [flut12](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut12[i](I));
        return ret;
    };

    std::cerr << "\rLUT12   ";
    Ciphertext gin12 = 1 * ct_my_string34 + 2 * ct_my_string35;
    std::vector<Ciphertext> gout12 = ctx.eval_lut_amortized(&gin12, lut12);

    std::vector<RotationPoly> lut13;
    std::vector<long (*)(long)> flut13;
    auto lut13idx0 = [](long I) -> long {
        /* GATE 23 (LUT3 _1050_ INIT 0x10 PERM 210) */
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
    lut13.push_back(ctx.genrate_lut(lut13idx0));
    flut13.push_back(lut13idx0);
    auto fvec13 = [flut13](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut13[i](I));
        return ret;
    };

    std::cerr << "\rLUT13   ";
    Ciphertext gin13 = 1 * gout6[0] + 2 * ct_my_string59 + 4 * ct_my_string56;
    std::vector<Ciphertext> gout13 = ctx.eval_lut_amortized(&gin13, lut13);

    std::vector<RotationPoly> lut14;
    std::vector<long (*)(long)> flut14;
    auto lut14idx0 = [](long I) -> long {
        /* GATE 47 (LUT2 _1074_ INIT 0x1 PERM 01) */
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
    lut14.push_back(ctx.genrate_lut(lut14idx0));
    flut14.push_back(lut14idx0);
    auto fvec14 = [flut14](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut14[i](I));
        return ret;
    };

    std::cerr << "\rLUT14   ";
    Ciphertext gin14 = 1 * ct_my_string5 + 2 * ct_my_string6;
    std::vector<Ciphertext> gout14 = ctx.eval_lut_amortized(&gin14, lut14);

    std::vector<RotationPoly> lut15;
    std::vector<long (*)(long)> flut15;
    auto lut15idx0 = [](long I) -> long {
        /* GATE 39 (LUT3 _1066_ INIT 0x10 PERM 120) */
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
    lut15.push_back(ctx.genrate_lut(lut15idx0));
    flut15.push_back(lut15idx0);
    auto fvec15 = [flut15](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut15[i](I));
        return ret;
    };

    std::cerr << "\rLUT15   ";
    Ciphertext gin15 = 1 * gout7[0] + 2 * ct_my_string20 + 4 * ct_my_string23;
    std::vector<Ciphertext> gout15 = ctx.eval_lut_amortized(&gin15, lut15);

    std::vector<RotationPoly> lut16;
    std::vector<long (*)(long)> flut16;
    auto lut16idx0 = [](long I) -> long {
        /* GATE 27 (LUT2 _1054_ INIT 0x1 PERM 01) */
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
    lut16.push_back(ctx.genrate_lut(lut16idx0));
    flut16.push_back(lut16idx0);
    auto fvec16 = [flut16](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut16[i](I));
        return ret;
    };

    std::cerr << "\rLUT16   ";
    Ciphertext gin16 = 1 * ct_my_string30 + 2 * ct_my_string31;
    std::vector<Ciphertext> gout16 = ctx.eval_lut_amortized(&gin16, lut16);

    std::vector<RotationPoly> lut17;
    std::vector<long (*)(long)> flut17;
    auto lut17idx0 = [](long I) -> long {
        /* GATE 11 (LUT3 _1038_ INIT 0x10 PERM 210) */
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
    lut17.push_back(ctx.genrate_lut(lut17idx0));
    flut17.push_back(lut17idx0);
    auto fvec17 = [flut17](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut17[i](I));
        return ret;
    };

    std::cerr << "\rLUT17   ";
    Ciphertext gin17 = 1 * gout9[0] + 2 * ct_my_string45 + 4 * ct_my_string44;
    std::vector<Ciphertext> gout17 = ctx.eval_lut_amortized(&gin17, lut17);

    std::vector<RotationPoly> lut18;
    std::vector<long (*)(long)> flut18;
    auto lut18idx0 = [](long I) -> long {
        /* GATE 19 (LUT2 _1046_ INIT 0x1 PERM 01) */
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
    lut18.push_back(ctx.genrate_lut(lut18idx0));
    flut18.push_back(lut18idx0);
    auto fvec18 = [flut18](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut18[i](I));
        return ret;
    };

    std::cerr << "\rLUT18   ";
    Ciphertext gin18 = 1 * ct_my_string49 + 2 * ct_my_string50;
    std::vector<Ciphertext> gout18 = ctx.eval_lut_amortized(&gin18, lut18);

    std::vector<RotationPoly> lut19;
    std::vector<long (*)(long)> flut19;
    auto lut19idx0 = [](long I) -> long {
        /* GATE 30 (LUT3 _1057_ INIT 0x10 PERM 120) */
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
    lut19.push_back(ctx.genrate_lut(lut19idx0));
    flut19.push_back(lut19idx0);
    auto fvec19 = [flut19](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut19[i](I));
        return ret;
    };

    std::cerr << "\rLUT19   ";
    Ciphertext gin19 = 1 * gout10[0] + 2 * ct_my_string36 + 4 * ct_my_string39;
    std::vector<Ciphertext> gout19 = ctx.eval_lut_amortized(&gin19, lut19);

    std::vector<RotationPoly> lut20;
    std::vector<long (*)(long)> flut20;
    auto lut20idx0 = [](long I) -> long {
        /* GATE 13 (LUT3 _1040_ INIT 0x10 PERM 210) */
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
    lut20.push_back(ctx.genrate_lut(lut20idx0));
    flut20.push_back(lut20idx0);
    auto fvec20 = [flut20](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut20[i](I));
        return ret;
    };

    std::cerr << "\rLUT20   ";
    Ciphertext gin20 = 1 * gout3[0] + 2 * ct_my_string41 + 4 * ct_my_string40;
    std::vector<Ciphertext> gout20 = ctx.eval_lut_amortized(&gin20, lut20);

    std::vector<RotationPoly> lut21;
    std::vector<long (*)(long)> flut21;
    auto lut21idx0 = [](long I) -> long {
        /* GATE 41 (LUT3 _1068_ INIT 0x1 PERM 102) */
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
    lut21.push_back(ctx.genrate_lut(lut21idx0));
    flut21.push_back(lut21idx0);
    auto fvec21 = [flut21](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut21[i](I));
        return ret;
    };

    std::cerr << "\rLUT21   ";
    Ciphertext gin21 = 1 * ct_my_string17 + 2 * ct_my_string16 + 4 * ct_my_string18;
    std::vector<Ciphertext> gout21 = ctx.eval_lut_amortized(&gin21, lut21);

    std::vector<RotationPoly> lut22;
    std::vector<long (*)(long)> flut22;
    auto lut22idx0 = [](long I) -> long {
        /* GATE 36 (LUT2 _1063_ INIT 0x1 PERM 01) */
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
    lut22.push_back(ctx.genrate_lut(lut22idx0));
    flut22.push_back(lut22idx0);
    auto fvec22 = [flut22](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut22[i](I));
        return ret;
    };

    std::cerr << "\rLUT22   ";
    Ciphertext gin22 = 1 * ct_my_string13 + 2 * ct_my_string14;
    std::vector<Ciphertext> gout22 = ctx.eval_lut_amortized(&gin22, lut22);

    std::vector<RotationPoly> lut23;
    std::vector<long (*)(long)> flut23;
    auto lut23idx0 = [](long I) -> long {
        /* GATE 32 (LUT3 _1059_ INIT 0x10 PERM 210) */
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
    lut23.push_back(ctx.genrate_lut(lut23idx0));
    flut23.push_back(lut23idx0);
    auto fvec23 = [flut23](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut23[i](I));
        return ret;
    };

    std::cerr << "\rLUT23   ";
    Ciphertext gin23 = 1 * gout12[0] + 2 * ct_my_string33 + 4 * ct_my_string32;
    std::vector<Ciphertext> gout23 = ctx.eval_lut_amortized(&gin23, lut23);

    std::vector<RotationPoly> lut24;
    std::vector<long (*)(long)> flut24;
    auto lut24idx0 = [](long I) -> long {
        /* GATE 46 (LUT3 _1073_ INIT 0x10 PERM 120) */
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
    lut24.push_back(ctx.genrate_lut(lut24idx0));
    flut24.push_back(lut24idx0);
    auto fvec24 = [flut24](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut24[i](I));
        return ret;
    };

    std::cerr << "\rLUT24   ";
    Ciphertext gin24 = 1 * gout14[0] + 2 * ct_my_string4 + 4 * ct_my_string7;
    std::vector<Ciphertext> gout24 = ctx.eval_lut_amortized(&gin24, lut24);

    std::vector<RotationPoly> lut25;
    std::vector<long (*)(long)> flut25;
    auto lut25idx0 = [](long I) -> long {
        /* GATE 38 (LUT3 _1065_ INIT 0x40 PERM 201) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut25.push_back(ctx.genrate_lut(lut25idx0));
    flut25.push_back(lut25idx0);
    auto fvec25 = [flut25](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut25[i](I));
        return ret;
    };

    std::cerr << "\rLUT25   ";
    Ciphertext gin25 = 1 * gout21[0] + 2 * gout15[0] + 4 * ct_my_string19;
    std::vector<Ciphertext> gout25 = ctx.eval_lut_amortized(&gin25, lut25);

    std::vector<RotationPoly> lut26;
    std::vector<long (*)(long)> flut26;
    auto lut26idx0 = [](long I) -> long {
        /* GATE 18 (LUT3 _1045_ INIT 0x10 PERM 120) */
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
    lut26.push_back(ctx.genrate_lut(lut26idx0));
    flut26.push_back(lut26idx0);
    auto fvec26 = [flut26](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut26[i](I));
        return ret;
    };

    std::cerr << "\rLUT26   ";
    Ciphertext gin26 = 1 * gout18[0] + 2 * ct_my_string48 + 4 * ct_my_string51;
    std::vector<Ciphertext> gout26 = ctx.eval_lut_amortized(&gin26, lut26);

    std::vector<RotationPoly> lut27;
    std::vector<long (*)(long)> flut27;
    auto lut27idx0 = [](long I) -> long {
        /* GATE 26 (LUT3 _1053_ INIT 0x10 PERM 120) */
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
    lut27.push_back(ctx.genrate_lut(lut27idx0));
    flut27.push_back(lut27idx0);
    auto fvec27 = [flut27](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut27[i](I));
        return ret;
    };

    std::cerr << "\rLUT27   ";
    Ciphertext gin27 = 1 * gout16[0] + 2 * ct_my_string28 + 4 * ct_my_string29;
    std::vector<Ciphertext> gout27 = ctx.eval_lut_amortized(&gin27, lut27);

    std::vector<RotationPoly> lut28;
    std::vector<long (*)(long)> flut28;
    auto lut28idx0 = [](long I) -> long {
        /* GATE 20 (LUT2 _1047_ INIT 0x8 PERM 01) */
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
    lut28.push_back(ctx.genrate_lut(lut28idx0));
    flut28.push_back(lut28idx0);
    auto fvec28 = [flut28](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut28[i](I));
        return ret;
    };

    std::cerr << "\rLUT28   ";
    Ciphertext gin28 = 1 * gout2[0] + 2 * gout13[0];
    std::vector<Ciphertext> gout28 = ctx.eval_lut_amortized(&gin28, lut28);

    std::vector<RotationPoly> lut29;
    std::vector<long (*)(long)> flut29;
    auto lut29idx0 = [](long I) -> long {
        /* GATE 35 (LUT3 _1062_ INIT 0x10 PERM 210) */
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
    lut29.push_back(ctx.genrate_lut(lut29idx0));
    flut29.push_back(lut29idx0);
    auto fvec29 = [flut29](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut29[i](I));
        return ret;
    };

    std::cerr << "\rLUT29   ";
    Ciphertext gin29 = 1 * gout22[0] + 2 * ct_my_string15 + 4 * ct_my_string12;
    std::vector<Ciphertext> gout29 = ctx.eval_lut_amortized(&gin29, lut29);

    std::vector<RotationPoly> lut30;
    std::vector<long (*)(long)> flut30;
    auto lut30idx0 = [](long I) -> long {
        /* GATE 45 (LUT3 _1072_ INIT 0x40 PERM 201) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut30.push_back(ctx.genrate_lut(lut30idx0));
    flut30.push_back(lut30idx0);
    auto fvec30 = [flut30](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut30[i](I));
        return ret;
    };

    std::cerr << "\rLUT30   ";
    Ciphertext gin30 = 1 * gout5[0] + 2 * gout24[0] + 4 * ct_my_string3;
    std::vector<Ciphertext> gout30 = ctx.eval_lut_amortized(&gin30, lut30);

    std::vector<RotationPoly> lut31;
    std::vector<long (*)(long)> flut31;
    auto lut31idx0 = [](long I) -> long {
        /* GATE 25 (LUT3 _1052_ INIT 0x40 PERM 201) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
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
    Ciphertext gin31 = 1 * gout11[0] + 2 * gout27[0] + 4 * ct_my_string27;
    std::vector<Ciphertext> gout31 = ctx.eval_lut_amortized(&gin31, lut31);

    std::vector<RotationPoly> lut32;
    std::vector<long (*)(long)> flut32;
    auto lut32idx0 = [](long I) -> long {
        /* GATE 10 (LUT2 _1037_ INIT 0x8 PERM 01) */
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
    lut32.push_back(ctx.genrate_lut(lut32idx0));
    flut32.push_back(lut32idx0);
    auto fvec32 = [flut32](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut32[i](I));
        return ret;
    };

    std::cerr << "\rLUT32   ";
    Ciphertext gin32 = 1 * gout17[0] + 2 * gout20[0];
    std::vector<Ciphertext> gout32 = ctx.eval_lut_amortized(&gin32, lut32);

    std::vector<RotationPoly> lut33;
    std::vector<long (*)(long)> flut33;
    auto lut33idx0 = [](long I) -> long {
        /* GATE 29 (LUT2 _1056_ INIT 0x8 PERM 01) */
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
    lut33.push_back(ctx.genrate_lut(lut33idx0));
    flut33.push_back(lut33idx0);
    auto fvec33 = [flut33](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut33[i](I));
        return ret;
    };

    std::cerr << "\rLUT33   ";
    Ciphertext gin33 = 1 * gout19[0] + 2 * gout23[0];
    std::vector<Ciphertext> gout33 = ctx.eval_lut_amortized(&gin33, lut33);

    std::vector<RotationPoly> lut34;
    std::vector<long (*)(long)> flut34;
    auto lut34idx0 = [](long I) -> long {
        /* GATE 34 (LUT3 _1061_ INIT 0x40 PERM 201) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut34.push_back(ctx.genrate_lut(lut34idx0));
    flut34.push_back(lut34idx0);
    auto fvec34 = [flut34](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut34[i](I));
        return ret;
    };

    std::cerr << "\rLUT34   ";
    Ciphertext gin34 = 1 * gout1[0] + 2 * gout29[0] + 4 * ct_my_string11;
    std::vector<Ciphertext> gout34 = ctx.eval_lut_amortized(&gin34, lut34);

    std::vector<RotationPoly> lut35;
    std::vector<long (*)(long)> flut35;
    auto lut35idx0 = [](long I) -> long {
        /* GATE 15 (LUT2 _1042_ INIT 0x8 PERM 01) */
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
    lut35.push_back(ctx.genrate_lut(lut35idx0));
    flut35.push_back(lut35idx0);
    auto fvec35 = [flut35](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut35[i](I));
        return ret;
    };

    std::cerr << "\rLUT35   ";
    Ciphertext gin35 = 1 * gout8[0] + 2 * gout26[0];
    std::vector<Ciphertext> gout35 = ctx.eval_lut_amortized(&gin35, lut35);

    std::vector<RotationPoly> lut36;
    std::vector<long (*)(long)> flut36;
    auto lut36idx0 = [](long I) -> long {
        /* GATE 51 (LUT2 _1078_ INIT 0x1 PERM 01) */
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
    lut36.push_back(ctx.genrate_lut(lut36idx0));
    flut36.push_back(lut36idx0);
    auto fvec36 = [flut36](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut36[i](I));
        return ret;
    };

    std::cerr << "\rLUT36   ";
    Ciphertext gin36 = 1 * gout35[0] + 2 * gout28[0];
    std::vector<Ciphertext> gout36 = ctx.eval_lut_amortized(&gin36, lut36);

    std::vector<RotationPoly> lut37;
    std::vector<long (*)(long)> flut37;
    auto lut37idx0 = [](long I) -> long {
        /* GATE 9 (LUT3 _1036_ INIT 0xd PERM 210) */
        switch (I) {
            case  0: return 1;
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
    lut37.push_back(ctx.genrate_lut(lut37idx0));
    flut37.push_back(lut37idx0);
    auto fvec37 = [flut37](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut37[i](I));
        return ret;
    };

    std::cerr << "\rLUT37   ";
    Ciphertext gin37 = 1 * gout32[0] + 2 * gout35[0] + 4 * gout28[0];
    std::vector<Ciphertext> gout37 = ctx.eval_lut_amortized(&gin37, lut37);

    std::vector<RotationPoly> lut38;
    std::vector<long (*)(long)> flut38;
    auto lut38idx0 = [](long I) -> long {
        /* GATE 50 (LUT2 _1077_ INIT 0x1 PERM 01) */
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
    lut38.push_back(ctx.genrate_lut(lut38idx0));
    flut38.push_back(lut38idx0);
    auto fvec38 = [flut38](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut38[i](I));
        return ret;
    };

    std::cerr << "\rLUT38   ";
    Ciphertext gin38 = 1 * gout33[0] + 2 * gout32[0];
    std::vector<Ciphertext> gout38 = ctx.eval_lut_amortized(&gin38, lut38);

    std::vector<RotationPoly> lut39;
    std::vector<long (*)(long)> flut39;
    auto lut39idx0 = [](long I) -> long {
        /* GATE 49 (LUT2 _1076_ INIT 0x1 PERM 01) */
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
    lut39.push_back(ctx.genrate_lut(lut39idx0));
    flut39.push_back(lut39idx0);
    auto fvec39 = [flut39](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut39[i](I));
        return ret;
    };

    std::cerr << "\rLUT39   ";
    Ciphertext gin39 = 1 * gout25[0] + 2 * gout31[0];
    std::vector<Ciphertext> gout39 = ctx.eval_lut_amortized(&gin39, lut39);

    std::vector<RotationPoly> lut40;
    std::vector<long (*)(long)> flut40;
    auto lut40idx0 = [](long I) -> long {
        /* GATE 53 (LUT3 _1080_ INIT 0xd0 PERM 120) */
        switch (I) {
            case  0: return 0;
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
    Ciphertext gin40 = 1 * gout39[0] + 2 * gout38[0] + 4 * gout36[0];
    std::vector<Ciphertext> gout40 = ctx.eval_lut_amortized(&gin40, lut40);

    std::vector<RotationPoly> lut41;
    std::vector<long (*)(long)> flut41;
    auto lut41idx0 = [](long I) -> long {
        /* GATE 44 (LUT2 _1071_ INIT 0x1 PERM 01) */
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
    Ciphertext gin41 = 1 * gout30[0] + 2 * gout34[0];
    std::vector<Ciphertext> gout41 = ctx.eval_lut_amortized(&gin41, lut41);

    std::vector<RotationPoly> lut42;
    std::vector<long (*)(long)> flut42;
    auto lut42idx0 = [](long I) -> long {
        /* GATE 8 (LUT3 _1035_ INIT 0xe PERM 102) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
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
    Ciphertext gin42 = 1 * gout37[0] + 2 * gout33[0] + 4 * gout31[0];
    std::vector<Ciphertext> gout42 = ctx.eval_lut_amortized(&gin42, lut42);

    std::vector<RotationPoly> lut43;
    std::vector<long (*)(long)> flut43;
    auto lut43idx0 = [](long I) -> long {
        /* GATE 52 (LUT2 _1079_ INIT 0x4 PERM 01) */
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
    lut43.push_back(ctx.genrate_lut(lut43idx0));
    flut43.push_back(lut43idx0);
    auto fvec43 = [flut43](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut43[i](I));
        return ret;
    };

    std::cerr << "\rLUT43   ";
    Ciphertext gin43 = 1 * gout40[0] + 2 * gout41[0];
    std::vector<Ciphertext> gout43 = ctx.eval_lut_amortized(&gin43, lut43);

    std::vector<RotationPoly> lut44;
    std::vector<long (*)(long)> flut44;
    auto lut44idx0 = [](long I) -> long {
        /* GATE 7 (LUT3 _1034_ INIT 0xe PERM 102) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
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
    Ciphertext gin44 = 1 * gout42[0] + 2 * gout25[0] + 4 * gout34[0];
    std::vector<Ciphertext> gout44 = ctx.eval_lut_amortized(&gin44, lut44);

    std::vector<RotationPoly> lut45;
    std::vector<long (*)(long)> flut45;
    auto lut45idx0 = [](long I) -> long {
        /* GATE 170 (LUT2 _1197_ INIT 0x4 PERM 01) */
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
    lut45.push_back(ctx.genrate_lut(lut45idx0));
    flut45.push_back(lut45idx0);
    auto fvec45 = [flut45](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut45[i](I));
        return ret;
    };

    std::cerr << "\rLUT45   ";
    Ciphertext gin45 = 1 * gout41[0] + 2 * ct_my_string61;
    std::vector<Ciphertext> gout45 = ctx.eval_lut_amortized(&gin45, lut45);

    std::vector<RotationPoly> lut46;
    std::vector<long (*)(long)> flut46;
    auto lut46idx0 = [](long I) -> long {
        /* GATE 75 (LUT2 _1102_ INIT 0x1 PERM 01) */
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
    lut46.push_back(ctx.genrate_lut(lut46idx0));
    flut46.push_back(lut46idx0);
    auto fvec46 = [flut46](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut46[i](I));
        return ret;
    };

    std::cerr << "\rLUT46   ";
    Ciphertext gin46 = 1 * gout41[0] + 2 * ct_my_string1;
    std::vector<Ciphertext> gout46 = ctx.eval_lut_amortized(&gin46, lut46);

    std::vector<RotationPoly> lut47;
    std::vector<long (*)(long)> flut47;
    auto lut47idx0 = [](long I) -> long {
        /* GATE 147 (LUT2 _1174_ INIT 0x4 PERM 01) */
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
    lut47.push_back(ctx.genrate_lut(lut47idx0));
    flut47.push_back(lut47idx0);
    auto fvec47 = [flut47](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut47[i](I));
        return ret;
    };

    std::cerr << "\rLUT47   ";
    Ciphertext gin47 = 1 * gout41[0] + 2 * ct_my_string58;
    std::vector<Ciphertext> gout47 = ctx.eval_lut_amortized(&gin47, lut47);

    std::vector<RotationPoly> lut48;
    std::vector<long (*)(long)> flut48;
    auto lut48idx0 = [](long I) -> long {
        /* GATE 43 (LUT3 _1070_ INIT 0x80 PERM 201) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
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
    Ciphertext gin48 = 1 * gout39[0] + 2 * gout38[0] + 4 * gout41[0];
    std::vector<Ciphertext> gout48 = ctx.eval_lut_amortized(&gin48, lut48);

    std::vector<RotationPoly> lut49;
    std::vector<long (*)(long)> flut49;
    auto lut49idx0 = [](long I) -> long {
        /* GATE 138 (LUT2 _1165_ INIT 0x4 PERM 01) */
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
    lut49.push_back(ctx.genrate_lut(lut49idx0));
    flut49.push_back(lut49idx0);
    auto fvec49 = [flut49](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut49[i](I));
        return ret;
    };

    std::cerr << "\rLUT49   ";
    Ciphertext gin49 = 1 * gout41[0] + 2 * ct_my_string57;
    std::vector<Ciphertext> gout49 = ctx.eval_lut_amortized(&gin49, lut49);

    std::vector<RotationPoly> lut50;
    std::vector<long (*)(long)> flut50;
    auto lut50idx0 = [](long I) -> long {
        /* GATE 100 (LUT2 _1127_ INIT 0x4 PERM 01) */
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
    lut50.push_back(ctx.genrate_lut(lut50idx0));
    flut50.push_back(lut50idx0);
    auto fvec50 = [flut50](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut50[i](I));
        return ret;
    };

    std::cerr << "\rLUT50   ";
    Ciphertext gin50 = 1 * gout41[0] + 2 * ct_my_string4;
    std::vector<Ciphertext> gout50 = ctx.eval_lut_amortized(&gin50, lut50);

    std::vector<RotationPoly> lut51;
    std::vector<long (*)(long)> flut51;
    auto lut51idx0 = [](long I) -> long {
        /* GATE 115 (LUT2 _1142_ INIT 0x1 PERM 01) */
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
    lut51.push_back(ctx.genrate_lut(lut51idx0));
    flut51.push_back(lut51idx0);
    auto fvec51 = [flut51](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut51[i](I));
        return ret;
    };

    std::cerr << "\rLUT51   ";
    Ciphertext gin51 = 1 * gout41[0] + 2 * ct_my_string6;
    std::vector<Ciphertext> gout51 = ctx.eval_lut_amortized(&gin51, lut51);

    std::vector<RotationPoly> lut52;
    std::vector<long (*)(long)> flut52;
    auto lut52idx0 = [](long I) -> long {
        /* GATE 62 (LUT3 _1089_ INIT 0x1 PERM 210) */
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
    lut52.push_back(ctx.genrate_lut(lut52idx0));
    flut52.push_back(lut52idx0);
    auto fvec52 = [flut52](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut52[i](I));
        return ret;
    };

    std::cerr << "\rLUT52   ";
    Ciphertext gin52 = 1 * gout30[0] + 2 * gout43[0] + 4 * gout44[0];
    std::vector<Ciphertext> gout52 = ctx.eval_lut_amortized(&gin52, lut52);

    std::vector<RotationPoly> lut53;
    std::vector<long (*)(long)> flut53;
    auto lut53idx0 = [](long I) -> long {
        /* GATE 63 (LUT3 _1090_ INIT 0x10 PERM 021) */
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
    lut53.push_back(ctx.genrate_lut(lut53idx0));
    flut53.push_back(lut53idx0);
    auto fvec53 = [flut53](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut53[i](I));
        return ret;
    };

    std::cerr << "\rLUT53   ";
    Ciphertext gin53 = 1 * gout31[0] + 2 * gout43[0] + 4 * gout44[0];
    std::vector<Ciphertext> gout53 = ctx.eval_lut_amortized(&gin53, lut53);

    std::vector<RotationPoly> lut54;
    std::vector<long (*)(long)> flut54;
    auto lut54idx0 = [](long I) -> long {
        /* GATE 54 (LUT2 _1081_ INIT 0x8 PERM 10) */
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
    lut54.push_back(ctx.genrate_lut(lut54idx0));
    flut54.push_back(lut54idx0);
    auto lut54idx1 = [](long I) -> long {
        /* GATE 58 (LUT2 _1085_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut54.push_back(ctx.genrate_lut(lut54idx1));
    flut54.push_back(lut54idx1);
    auto fvec54 = [flut54](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut54[i](I));
        return ret;
    };

    std::cerr << "\rLUT54   ";
    Ciphertext gin54 = 1 * gout43[0] + 2 * gout44[0];
    std::vector<Ciphertext> gout54 = ctx.eval_lut_amortized(&gin54, lut54);

    std::vector<RotationPoly> lut55;
    std::vector<long (*)(long)> flut55;
    auto lut55idx0 = [](long I) -> long {
        /* GATE 56 (LUT2 _1083_ INIT 0x8 PERM 10) */
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
    lut55.push_back(ctx.genrate_lut(lut55idx0));
    flut55.push_back(lut55idx0);
    auto fvec55 = [flut55](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut55[i](I));
        return ret;
    };

    std::cerr << "\rLUT55   ";
    Ciphertext gin55 = 1 * gout39[0] + 2 * gout41[0];
    std::vector<Ciphertext> gout55 = ctx.eval_lut_amortized(&gin55, lut55);

    std::vector<RotationPoly> lut56;
    std::vector<long (*)(long)> flut56;
    auto lut56idx0 = [](long I) -> long {
        /* GATE 42 (LUT3 _1069_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut56.push_back(ctx.genrate_lut(lut56idx0));
    flut56.push_back(lut56idx0);
    auto lut56idx1 = [](long I) -> long {
        /* GATE 68 (LUT2 _1095_ INIT 0x8 PERM 21) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut56.push_back(ctx.genrate_lut(lut56idx1));
    flut56.push_back(lut56idx1);
    auto fvec56 = [flut56](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut56[i](I));
        return ret;
    };

    std::cerr << "\rLUT56   ";
    Ciphertext gin56 = 1 * gout30[0] + 2 * gout36[0] + 4 * gout48[0];
    std::vector<Ciphertext> gout56 = ctx.eval_lut_amortized(&gin56, lut56);

    std::vector<RotationPoly> lut57;
    std::vector<long (*)(long)> flut57;
    auto lut57idx0 = [](long I) -> long {
        /* GATE 112 (LUT3 _1139_ INIT 0x70 PERM 120) */
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
    lut57.push_back(ctx.genrate_lut(lut57idx0));
    flut57.push_back(lut57idx0);
    auto fvec57 = [flut57](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut57[i](I));
        return ret;
    };

    std::cerr << "\rLUT57   ";
    Ciphertext gin57 = 1 * gout41[0] + 2 * ct_my_string62 + 4 * gout56[1];
    std::vector<Ciphertext> gout57 = ctx.eval_lut_amortized(&gin57, lut57);

    std::vector<RotationPoly> lut58;
    std::vector<long (*)(long)> flut58;
    auto lut58idx0 = [](long I) -> long {
        /* GATE 346 (LUT3 _1373_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut58.push_back(ctx.genrate_lut(lut58idx0));
    flut58.push_back(lut58idx0);
    auto fvec58 = [flut58](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut58[i](I));
        return ret;
    };

    std::cerr << "\rLUT58   ";
    Ciphertext gin58 = 1 * ct_my_string62 + 2 * ct_my_string6 + 4 * gout56[1];
    std::vector<Ciphertext> gout58 = ctx.eval_lut_amortized(&gin58, lut58);

    std::vector<RotationPoly> lut59;
    std::vector<long (*)(long)> flut59;
    auto lut59idx0 = [](long I) -> long {
        /* GATE 344 (LUT3 _1371_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
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
    Ciphertext gin59 = 1 * ct_my_string60 + 2 * ct_my_string4 + 4 * gout56[1];
    std::vector<Ciphertext> gout59 = ctx.eval_lut_amortized(&gin59, lut59);

    std::vector<RotationPoly> lut60;
    std::vector<long (*)(long)> flut60;
    auto lut60idx0 = [](long I) -> long {
        /* GATE 186 (LUT2 _1213_ INIT 0x8 PERM 10) */
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
    lut60.push_back(ctx.genrate_lut(lut60idx0));
    flut60.push_back(lut60idx0);
    auto fvec60 = [flut60](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut60[i](I));
        return ret;
    };

    std::cerr << "\rLUT60   ";
    Ciphertext gin60 = 1 * ct_my_string55 + 2 * gout56[1];
    std::vector<Ciphertext> gout60 = ctx.eval_lut_amortized(&gin60, lut60);

    std::vector<RotationPoly> lut61;
    std::vector<long (*)(long)> flut61;
    auto lut61idx0 = [](long I) -> long {
        /* GATE 343 (LUT3 _1370_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
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
    Ciphertext gin61 = 1 * ct_my_string59 + 2 * ct_my_string3 + 4 * gout56[1];
    std::vector<Ciphertext> gout61 = ctx.eval_lut_amortized(&gin61, lut61);

    std::vector<RotationPoly> lut62;
    std::vector<long (*)(long)> flut62;
    auto lut62idx0 = [](long I) -> long {
        /* GATE 55 (LUT2 _1082_ INIT 0x1 PERM 10) */
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
    lut62.push_back(ctx.genrate_lut(lut62idx0));
    flut62.push_back(lut62idx0);
    auto fvec62 = [flut62](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut62[i](I));
        return ret;
    };

    std::cerr << "\rLUT62   ";
    Ciphertext gin62 = 1 * gout30[0] + 2 * gout55[0];
    std::vector<Ciphertext> gout62 = ctx.eval_lut_amortized(&gin62, lut62);

    std::vector<RotationPoly> lut63;
    std::vector<long (*)(long)> flut63;
    auto lut63idx0 = [](long I) -> long {
        /* GATE 340 (LUT3 _1367_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
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
    Ciphertext gin63 = 1 * ct_my_string56 + 2 * ct_my_string0 + 4 * gout56[1];
    std::vector<Ciphertext> gout63 = ctx.eval_lut_amortized(&gin63, lut63);

    std::vector<RotationPoly> lut64;
    std::vector<long (*)(long)> flut64;
    auto lut64idx0 = [](long I) -> long {
        /* GATE 67 (LUT3 _1094_ INIT 0x70 PERM 120) */
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
    lut64.push_back(ctx.genrate_lut(lut64idx0));
    flut64.push_back(lut64idx0);
    auto fvec64 = [flut64](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut64[i](I));
        return ret;
    };

    std::cerr << "\rLUT64   ";
    Ciphertext gin64 = 1 * gout41[0] + 2 * ct_my_string56 + 4 * gout56[1];
    std::vector<Ciphertext> gout64 = ctx.eval_lut_amortized(&gin64, lut64);

    std::vector<RotationPoly> lut65;
    std::vector<long (*)(long)> flut65;
    auto lut65idx0 = [](long I) -> long {
        /* GATE 97 (LUT2 _1124_ INIT 0x8 PERM 10) */
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
    lut65.push_back(ctx.genrate_lut(lut65idx0));
    flut65.push_back(lut65idx0);
    auto fvec65 = [flut65](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut65[i](I));
        return ret;
    };

    std::cerr << "\rLUT65   ";
    Ciphertext gin65 = 1 * ct_my_string60 + 2 * gout56[1];
    std::vector<Ciphertext> gout65 = ctx.eval_lut_amortized(&gin65, lut65);

    std::vector<RotationPoly> lut66;
    std::vector<long (*)(long)> flut66;
    auto lut66idx0 = [](long I) -> long {
        /* GATE 6 (LUT3 _1033_ INIT 0x40 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
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
    Ciphertext gin66 = 1 * gout43[0] + 2 * gout44[0] + 4 * gout56[0];
    std::vector<Ciphertext> gout66 = ctx.eval_lut_amortized(&gin66, lut66);

    std::vector<RotationPoly> lut67;
    std::vector<long (*)(long)> flut67;
    auto lut67idx0 = [](long I) -> long {
        /* GATE 131 (LUT2 _1158_ INIT 0x8 PERM 10) */
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
    lut67.push_back(ctx.genrate_lut(lut67idx0));
    flut67.push_back(lut67idx0);
    auto fvec67 = [flut67](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut67[i](I));
        return ret;
    };

    std::cerr << "\rLUT67   ";
    Ciphertext gin67 = 1 * ct_my_string48 + 2 * gout56[1];
    std::vector<Ciphertext> gout67 = ctx.eval_lut_amortized(&gin67, lut67);

    std::vector<RotationPoly> lut68;
    std::vector<long (*)(long)> flut68;
    auto lut68idx0 = [](long I) -> long {
        /* GATE 137 (LUT3 _1164_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
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
    Ciphertext gin68 = 1 * gout49[0] + 2 * ct_my_string49 + 4 * gout56[1];
    std::vector<Ciphertext> gout68 = ctx.eval_lut_amortized(&gin68, lut68);

    std::vector<RotationPoly> lut69;
    std::vector<long (*)(long)> flut69;
    auto lut69idx0 = [](long I) -> long {
        /* GATE 341 (LUT3 _1368_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
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
    Ciphertext gin69 = 1 * ct_my_string57 + 2 * ct_my_string1 + 4 * gout56[1];
    std::vector<Ciphertext> gout69 = ctx.eval_lut_amortized(&gin69, lut69);

    std::vector<RotationPoly> lut70;
    std::vector<long (*)(long)> flut70;
    auto lut70idx0 = [](long I) -> long {
        /* GATE 243 (LUT3 _1270_ INIT 0xca PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
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
    Ciphertext gin70 = 1 * ct_my_string25 + 2 * gout66[0] + 4 * ct_my_string1;
    std::vector<Ciphertext> gout70 = ctx.eval_lut_amortized(&gin70, lut70);

    std::vector<RotationPoly> lut71;
    std::vector<long (*)(long)> flut71;
    auto lut71idx0 = [](long I) -> long {
        /* GATE 71 (LUT3 _1098_ INIT 0x70 PERM 120) */
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
    lut71.push_back(ctx.genrate_lut(lut71idx0));
    flut71.push_back(lut71idx0);
    auto fvec71 = [flut71](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut71[i](I));
        return ret;
    };

    std::cerr << "\rLUT71   ";
    Ciphertext gin71 = 1 * gout41[0] + 2 * ct_my_string57 + 4 * gout56[1];
    std::vector<Ciphertext> gout71 = ctx.eval_lut_amortized(&gin71, lut71);

    std::vector<RotationPoly> lut72;
    std::vector<long (*)(long)> flut72;
    auto lut72idx0 = [](long I) -> long {
        /* GATE 185 (LUT3 _1212_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
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
    Ciphertext gin72 = 1 * gout60[0] + 2 * ct_my_string23 + 4 * gout66[0];
    std::vector<Ciphertext> gout72 = ctx.eval_lut_amortized(&gin72, lut72);

    std::vector<RotationPoly> lut73;
    std::vector<long (*)(long)> flut73;
    auto lut73idx0 = [](long I) -> long {
        /* GATE 90 (LUT2 _1117_ INIT 0x4 PERM 01) */
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
    lut73.push_back(ctx.genrate_lut(lut73idx0));
    flut73.push_back(lut73idx0);
    auto fvec73 = [flut73](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut73[i](I));
        return ret;
    };

    std::cerr << "\rLUT73   ";
    Ciphertext gin73 = 1 * gout56[0] + 2 * ct_my_string59;
    std::vector<Ciphertext> gout73 = ctx.eval_lut_amortized(&gin73, lut73);

    std::vector<RotationPoly> lut74;
    std::vector<long (*)(long)> flut74;
    auto lut74idx0 = [](long I) -> long {
        /* GATE 263 (LUT3 _1290_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut74.push_back(ctx.genrate_lut(lut74idx0));
    flut74.push_back(lut74idx0);
    auto fvec74 = [flut74](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut74[i](I));
        return ret;
    };

    std::cerr << "\rLUT74   ";
    Ciphertext gin74 = 1 * ct_my_string30 + 2 * gout66[0] + 4 * ct_my_string6;
    std::vector<Ciphertext> gout74 = ctx.eval_lut_amortized(&gin74, lut74);

    std::vector<RotationPoly> lut75;
    std::vector<long (*)(long)> flut75;
    auto lut75idx0 = [](long I) -> long {
        /* GATE 178 (LUT2 _1205_ INIT 0x8 PERM 10) */
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
    lut75.push_back(ctx.genrate_lut(lut75idx0));
    flut75.push_back(lut75idx0);
    auto fvec75 = [flut75](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut75[i](I));
        return ret;
    };

    std::cerr << "\rLUT75   ";
    Ciphertext gin75 = 1 * ct_my_string54 + 2 * gout56[1];
    std::vector<Ciphertext> gout75 = ctx.eval_lut_amortized(&gin75, lut75);

    std::vector<RotationPoly> lut76;
    std::vector<long (*)(long)> flut76;
    auto lut76idx0 = [](long I) -> long {
        /* GATE 74 (LUT2 _1101_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut76.push_back(ctx.genrate_lut(lut76idx0));
    flut76.push_back(lut76idx0);
    auto lut76idx1 = [](long I) -> long {
        /* GATE 57 (LUT2 _1084_ INIT 0x8 PERM 10) */
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
    lut76.push_back(ctx.genrate_lut(lut76idx1));
    flut76.push_back(lut76idx1);
    auto fvec76 = [flut76](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut76[i](I));
        return ret;
    };

    std::cerr << "\rLUT76   ";
    Ciphertext gin76 = 1 * gout54[1] + 2 * gout62[0];
    std::vector<Ciphertext> gout76 = ctx.eval_lut_amortized(&gin76, lut76);

    std::vector<RotationPoly> lut77;
    std::vector<long (*)(long)> flut77;
    auto lut77idx0 = [](long I) -> long {
        /* GATE 189 (LUT2 _1216_ INIT 0x8 PERM 10) */
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
    lut77.push_back(ctx.genrate_lut(lut77idx0));
    flut77.push_back(lut77idx0);
    auto fvec77 = [flut77](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut77[i](I));
        return ret;
    };

    std::cerr << "\rLUT77   ";
    Ciphertext gin77 = 1 * ct_my_string47 + 2 * gout76[0];
    std::vector<Ciphertext> gout77 = ctx.eval_lut_amortized(&gin77, lut77);

    std::vector<RotationPoly> lut78;
    std::vector<long (*)(long)> flut78;
    auto lut78idx0 = [](long I) -> long {
        /* GATE 109 (LUT3 _1136_ INIT 0x70 PERM 120) */
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
    lut78.push_back(ctx.genrate_lut(lut78idx0));
    flut78.push_back(lut78idx0);
    auto fvec78 = [flut78](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut78[i](I));
        return ret;
    };

    std::cerr << "\rLUT78   ";
    Ciphertext gin78 = 1 * gout41[0] + 2 * ct_my_string61 + 4 * gout56[1];
    std::vector<Ciphertext> gout78 = ctx.eval_lut_amortized(&gin78, lut78);

    std::vector<RotationPoly> lut79;
    std::vector<long (*)(long)> flut79;
    auto lut79idx0 = [](long I) -> long {
        /* GATE 255 (LUT3 _1282_ INIT 0xca PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut79.push_back(ctx.genrate_lut(lut79idx0));
    flut79.push_back(lut79idx0);
    auto fvec79 = [flut79](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut79[i](I));
        return ret;
    };

    std::cerr << "\rLUT79   ";
    Ciphertext gin79 = 1 * ct_my_string28 + 2 * gout66[0] + 4 * ct_my_string4;
    std::vector<Ciphertext> gout79 = ctx.eval_lut_amortized(&gin79, lut79);

    std::vector<RotationPoly> lut80;
    std::vector<long (*)(long)> flut80;
    auto lut80idx0 = [](long I) -> long {
        /* GATE 159 (LUT2 _1186_ INIT 0x8 PERM 10) */
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
    lut80.push_back(ctx.genrate_lut(lut80idx0));
    flut80.push_back(lut80idx0);
    auto fvec80 = [flut80](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut80[i](I));
        return ret;
    };

    std::cerr << "\rLUT80   ";
    Ciphertext gin80 = 1 * ct_my_string19 + 2 * gout66[0];
    std::vector<Ciphertext> gout80 = ctx.eval_lut_amortized(&gin80, lut80);

    std::vector<RotationPoly> lut81;
    std::vector<long (*)(long)> flut81;
    auto lut81idx0 = [](long I) -> long {
        /* GATE 339 (LUT3 _1366_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut81.push_back(ctx.genrate_lut(lut81idx0));
    flut81.push_back(lut81idx0);
    auto fvec81 = [flut81](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut81[i](I));
        return ret;
    };

    std::cerr << "\rLUT81   ";
    Ciphertext gin81 = 1 * ct_my_string55 + 2 * ct_my_string7 + 4 * gout76[0];
    std::vector<Ciphertext> gout81 = ctx.eval_lut_amortized(&gin81, lut81);

    std::vector<RotationPoly> lut82;
    std::vector<long (*)(long)> flut82;
    auto lut82idx0 = [](long I) -> long {
        /* GATE 247 (LUT3 _1274_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut82.push_back(ctx.genrate_lut(lut82idx0));
    flut82.push_back(lut82idx0);
    auto fvec82 = [flut82](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut82[i](I));
        return ret;
    };

    std::cerr << "\rLUT82   ";
    Ciphertext gin82 = 1 * ct_my_string26 + 2 * gout66[0] + 4 * ct_my_string2;
    std::vector<Ciphertext> gout82 = ctx.eval_lut_amortized(&gin82, lut82);

    std::vector<RotationPoly> lut83;
    std::vector<long (*)(long)> flut83;
    auto lut83idx0 = [](long I) -> long {
        /* GATE 348 (LUT3 _1375_ INIT 0xca PERM 102) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut83.push_back(ctx.genrate_lut(lut83idx0));
    flut83.push_back(lut83idx0);
    auto fvec83 = [flut83](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut83[i](I));
        return ret;
    };

    std::cerr << "\rLUT83   ";
    Ciphertext gin83 = 1 * ct_my_string9 + 2 * ct_my_string41 + 4 * gout62[0];
    std::vector<Ciphertext> gout83 = ctx.eval_lut_amortized(&gin83, lut83);

    std::vector<RotationPoly> lut84;
    std::vector<long (*)(long)> flut84;
    auto lut84idx0 = [](long I) -> long {
        /* GATE 168 (LUT2 _1195_ INIT 0x8 PERM 10) */
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
    lut84.push_back(ctx.genrate_lut(lut84idx0));
    flut84.push_back(lut84idx0);
    auto fvec84 = [flut84](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut84[i](I));
        return ret;
    };

    std::cerr << "\rLUT84   ";
    Ciphertext gin84 = 1 * ct_my_string21 + 2 * gout66[0];
    std::vector<Ciphertext> gout84 = ctx.eval_lut_amortized(&gin84, lut84);

    std::vector<RotationPoly> lut85;
    std::vector<long (*)(long)> flut85;
    auto lut85idx0 = [](long I) -> long {
        /* GATE 217 (LUT3 _1244_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut85.push_back(ctx.genrate_lut(lut85idx0));
    flut85.push_back(lut85idx0);
    auto lut85idx1 = [](long I) -> long {
        /* GATE 94 (LUT2 _1121_ INIT 0x8 PERM 10) */
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
    lut85.push_back(ctx.genrate_lut(lut85idx1));
    flut85.push_back(lut85idx1);
    auto fvec85 = [flut85](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut85[i](I));
        return ret;
    };

    std::cerr << "\rLUT85   ";
    Ciphertext gin85 = 1 * ct_my_string20 + 2 * gout76[1] + 4 * ct_my_string4;
    std::vector<Ciphertext> gout85 = ctx.eval_lut_amortized(&gin85, lut85);

    std::vector<RotationPoly> lut86;
    std::vector<long (*)(long)> flut86;
    auto lut86idx0 = [](long I) -> long {
        /* GATE 127 (LUT2 _1154_ INIT 0x8 PERM 10) */
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
    lut86.push_back(ctx.genrate_lut(lut86idx0));
    flut86.push_back(lut86idx0);
    auto fvec86 = [flut86](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut86[i](I));
        return ret;
    };

    std::cerr << "\rLUT86   ";
    Ciphertext gin86 = 1 * ct_my_string16 + 2 * gout66[0];
    std::vector<Ciphertext> gout86 = ctx.eval_lut_amortized(&gin86, lut86);

    std::vector<RotationPoly> lut87;
    std::vector<long (*)(long)> flut87;
    auto lut87idx0 = [](long I) -> long {
        /* GATE 136 (LUT3 _1163_ INIT 0x70 PERM 120) */
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
    lut87.push_back(ctx.genrate_lut(lut87idx0));
    flut87.push_back(lut87idx0);
    auto fvec87 = [flut87](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut87[i](I));
        return ret;
    };

    std::cerr << "\rLUT87   ";
    Ciphertext gin87 = 1 * gout68[0] + 2 * ct_my_string17 + 4 * gout66[0];
    std::vector<Ciphertext> gout87 = ctx.eval_lut_amortized(&gin87, lut87);

    std::vector<RotationPoly> lut88;
    std::vector<long (*)(long)> flut88;
    auto lut88idx0 = [](long I) -> long {
        /* GATE 70 (LUT3 _1097_ INIT 0x70 PERM 120) */
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
    lut88.push_back(ctx.genrate_lut(lut88idx0));
    flut88.push_back(lut88idx0);
    auto fvec88 = [flut88](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut88[i](I));
        return ret;
    };

    std::cerr << "\rLUT88   ";
    Ciphertext gin88 = 1 * gout71[0] + 2 * ct_my_string25 + 4 * gout66[0];
    std::vector<Ciphertext> gout88 = ctx.eval_lut_amortized(&gin88, lut88);

    std::vector<RotationPoly> lut89;
    std::vector<long (*)(long)> flut89;
    auto lut89idx0 = [](long I) -> long {
        /* GATE 331 (LUT3 _1358_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut89.push_back(ctx.genrate_lut(lut89idx0));
    flut89.push_back(lut89idx0);
    auto fvec89 = [flut89](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut89[i](I));
        return ret;
    };

    std::cerr << "\rLUT89   ";
    Ciphertext gin89 = 1 * ct_my_string51 + 2 * ct_my_string3 + 4 * gout76[0];
    std::vector<Ciphertext> gout89 = ctx.eval_lut_amortized(&gin89, lut89);

    std::vector<RotationPoly> lut90;
    std::vector<long (*)(long)> flut90;
    auto lut90idx0 = [](long I) -> long {
        /* GATE 89 (LUT3 _1116_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut90.push_back(ctx.genrate_lut(lut90idx0));
    flut90.push_back(lut90idx0);
    auto fvec90 = [flut90](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut90[i](I));
        return ret;
    };

    std::cerr << "\rLUT90   ";
    Ciphertext gin90 = 1 * gout73[0] + 2 * ct_my_string27 + 4 * gout66[0];
    std::vector<Ciphertext> gout90 = ctx.eval_lut_amortized(&gin90, lut90);

    std::vector<RotationPoly> lut91;
    std::vector<long (*)(long)> flut91;
    auto lut91idx0 = [](long I) -> long {
        /* GATE 193 (LUT3 _1220_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut91.push_back(ctx.genrate_lut(lut91idx0));
    flut91.push_back(lut91idx0);
    auto fvec91 = [flut91](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut91[i](I));
        return ret;
    };

    std::cerr << "\rLUT91   ";
    Ciphertext gin91 = 1 * ct_my_string16 + 2 * gout76[1] + 4 * ct_my_string0;
    std::vector<Ciphertext> gout91 = ctx.eval_lut_amortized(&gin91, lut91);

    std::vector<RotationPoly> lut92;
    std::vector<long (*)(long)> flut92;
    auto lut92idx0 = [](long I) -> long {
        /* GATE 325 (LUT3 _1352_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut92.push_back(ctx.genrate_lut(lut92idx0));
    flut92.push_back(lut92idx0);
    auto fvec92 = [flut92](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut92[i](I));
        return ret;
    };

    std::cerr << "\rLUT92   ";
    Ciphertext gin92 = 1 * ct_my_string48 + 2 * ct_my_string0 + 4 * gout76[0];
    std::vector<Ciphertext> gout92 = ctx.eval_lut_amortized(&gin92, lut92);

    std::vector<RotationPoly> lut93;
    std::vector<long (*)(long)> flut93;
    auto lut93idx0 = [](long I) -> long {
        /* GATE 251 (LUT3 _1278_ INIT 0xca PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut93.push_back(ctx.genrate_lut(lut93idx0));
    flut93.push_back(lut93idx0);
    auto fvec93 = [flut93](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut93[i](I));
        return ret;
    };

    std::cerr << "\rLUT93   ";
    Ciphertext gin93 = 1 * ct_my_string27 + 2 * gout66[0] + 4 * ct_my_string3;
    std::vector<Ciphertext> gout93 = ctx.eval_lut_amortized(&gin93, lut93);

    std::vector<RotationPoly> lut94;
    std::vector<long (*)(long)> flut94;
    auto lut94idx0 = [](long I) -> long {
        /* GATE 108 (LUT3 _1135_ INIT 0x70 PERM 120) */
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
    lut94.push_back(ctx.genrate_lut(lut94idx0));
    flut94.push_back(lut94idx0);
    auto fvec94 = [flut94](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut94[i](I));
        return ret;
    };

    std::cerr << "\rLUT94   ";
    Ciphertext gin94 = 1 * gout78[0] + 2 * ct_my_string29 + 4 * gout66[0];
    std::vector<Ciphertext> gout94 = ctx.eval_lut_amortized(&gin94, lut94);

    std::vector<RotationPoly> lut95;
    std::vector<long (*)(long)> flut95;
    auto lut95idx0 = [](long I) -> long {
        /* GATE 345 (LUT3 _1372_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut95.push_back(ctx.genrate_lut(lut95idx0));
    flut95.push_back(lut95idx0);
    auto fvec95 = [flut95](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut95[i](I));
        return ret;
    };

    std::cerr << "\rLUT95   ";
    Ciphertext gin95 = 1 * ct_my_string61 + 2 * ct_my_string5 + 4 * gout56[1];
    std::vector<Ciphertext> gout95 = ctx.eval_lut_amortized(&gin95, lut95);

    std::vector<RotationPoly> lut96;
    std::vector<long (*)(long)> flut96;
    auto lut96idx0 = [](long I) -> long {
        /* GATE 347 (LUT3 _1374_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut96.push_back(ctx.genrate_lut(lut96idx0));
    flut96.push_back(lut96idx0);
    auto fvec96 = [flut96](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut96[i](I));
        return ret;
    };

    std::cerr << "\rLUT96   ";
    Ciphertext gin96 = 1 * ct_my_string63 + 2 * ct_my_string7 + 4 * gout56[1];
    std::vector<Ciphertext> gout96 = ctx.eval_lut_amortized(&gin96, lut96);

    std::vector<RotationPoly> lut97;
    std::vector<long (*)(long)> flut97;
    auto lut97idx0 = [](long I) -> long {
        /* GATE 111 (LUT3 _1138_ INIT 0x70 PERM 120) */
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
    lut97.push_back(ctx.genrate_lut(lut97idx0));
    flut97.push_back(lut97idx0);
    auto fvec97 = [flut97](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut97[i](I));
        return ret;
    };

    std::cerr << "\rLUT97   ";
    Ciphertext gin97 = 1 * gout57[0] + 2 * ct_my_string30 + 4 * gout66[0];
    std::vector<Ciphertext> gout97 = ctx.eval_lut_amortized(&gin97, lut97);

    std::vector<RotationPoly> lut98;
    std::vector<long (*)(long)> flut98;
    auto lut98idx0 = [](long I) -> long {
        /* GATE 267 (LUT3 _1294_ INIT 0xca PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut98.push_back(ctx.genrate_lut(lut98idx0));
    flut98.push_back(lut98idx0);
    auto fvec98 = [flut98](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut98[i](I));
        return ret;
    };

    std::cerr << "\rLUT98   ";
    Ciphertext gin98 = 1 * ct_my_string31 + 2 * gout66[0] + 4 * ct_my_string7;
    std::vector<Ciphertext> gout98 = ctx.eval_lut_amortized(&gin98, lut98);

    std::vector<RotationPoly> lut99;
    std::vector<long (*)(long)> flut99;
    auto lut99idx0 = [](long I) -> long {
        /* GATE 163 (LUT2 _1190_ INIT 0x8 PERM 01) */
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
    lut99.push_back(ctx.genrate_lut(lut99idx0));
    flut99.push_back(lut99idx0);
    auto fvec99 = [flut99](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut99[i](I));
        return ret;
    };

    std::cerr << "\rLUT99   ";
    Ciphertext gin99 = 1 * gout76[0] + 2 * ct_my_string44;
    std::vector<Ciphertext> gout99 = ctx.eval_lut_amortized(&gin99, lut99);

    std::vector<RotationPoly> lut100;
    std::vector<long (*)(long)> flut100;
    auto lut100idx0 = [](long I) -> long {
        /* GATE 146 (LUT3 _1173_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut100.push_back(ctx.genrate_lut(lut100idx0));
    flut100.push_back(lut100idx0);
    auto fvec100 = [flut100](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut100[i](I));
        return ret;
    };

    std::cerr << "\rLUT100   ";
    Ciphertext gin100 = 1 * gout47[0] + 2 * ct_my_string50 + 4 * gout56[1];
    std::vector<Ciphertext> gout100 = ctx.eval_lut_amortized(&gin100, lut100);

    std::vector<RotationPoly> lut101;
    std::vector<long (*)(long)> flut101;
    auto lut101idx0 = [](long I) -> long {
        /* GATE 124 (LUT2 _1151_ INIT 0x8 PERM 10) */
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
    lut101.push_back(ctx.genrate_lut(lut101idx0));
    flut101.push_back(lut101idx0);
    auto fvec101 = [flut101](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut101[i](I));
        return ret;
    };

    std::cerr << "\rLUT101   ";
    Ciphertext gin101 = 1 * ct_my_string63 + 2 * gout56[1];
    std::vector<Ciphertext> gout101 = ctx.eval_lut_amortized(&gin101, lut101);

    std::vector<RotationPoly> lut102;
    std::vector<long (*)(long)> flut102;
    auto lut102idx0 = [](long I) -> long {
        /* GATE 160 (LUT2 _1187_ INIT 0x8 PERM 10) */
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
    lut102.push_back(ctx.genrate_lut(lut102idx0));
    flut102.push_back(lut102idx0);
    auto fvec102 = [flut102](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut102[i](I));
        return ret;
    };

    std::cerr << "\rLUT102   ";
    Ciphertext gin102 = 1 * ct_my_string20 + 2 * gout66[0];
    std::vector<Ciphertext> gout102 = ctx.eval_lut_amortized(&gin102, lut102);

    std::vector<RotationPoly> lut103;
    std::vector<long (*)(long)> flut103;
    auto lut103idx0 = [](long I) -> long {
        /* GATE 235 (LUT3 _1262_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut103.push_back(ctx.genrate_lut(lut103idx0));
    flut103.push_back(lut103idx0);
    auto fvec103 = [flut103](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut103[i](I));
        return ret;
    };

    std::cerr << "\rLUT103   ";
    Ciphertext gin103 = 1 * ct_my_string23 + 2 * gout76[1] + 4 * ct_my_string7;
    std::vector<Ciphertext> gout103 = ctx.eval_lut_amortized(&gin103, lut103);

    std::vector<RotationPoly> lut104;
    std::vector<long (*)(long)> flut104;
    auto lut104idx0 = [](long I) -> long {
        /* GATE 342 (LUT3 _1369_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut104.push_back(ctx.genrate_lut(lut104idx0));
    flut104.push_back(lut104idx0);
    auto fvec104 = [flut104](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut104[i](I));
        return ret;
    };

    std::cerr << "\rLUT104   ";
    Ciphertext gin104 = 1 * ct_my_string58 + 2 * ct_my_string2 + 4 * gout56[1];
    std::vector<Ciphertext> gout104 = ctx.eval_lut_amortized(&gin104, lut104);

    std::vector<RotationPoly> lut105;
    std::vector<long (*)(long)> flut105;
    auto lut105idx0 = [](long I) -> long {
        /* GATE 169 (LUT2 _1196_ INIT 0x8 PERM 10) */
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
    lut105.push_back(ctx.genrate_lut(lut105idx0));
    flut105.push_back(lut105idx0);
    auto fvec105 = [flut105](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut105[i](I));
        return ret;
    };

    std::cerr << "\rLUT105   ";
    Ciphertext gin105 = 1 * ct_my_string53 + 2 * gout56[1];
    std::vector<Ciphertext> gout105 = ctx.eval_lut_amortized(&gin105, lut105);

    std::vector<RotationPoly> lut106;
    std::vector<long (*)(long)> flut106;
    auto lut106idx0 = [](long I) -> long {
        /* GATE 5 (LUT2 _1032_ INIT 0x8 PERM 01) */
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
    lut106.push_back(ctx.genrate_lut(lut106idx0));
    flut106.push_back(lut106idx0);
    auto lut106idx1 = [](long I) -> long {
        /* GATE 65 (LUT2 _1092_ INIT 0x4 PERM 01) */
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
    lut106.push_back(ctx.genrate_lut(lut106idx1));
    flut106.push_back(lut106idx1);
    auto fvec106 = [flut106](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut106[i](I));
        return ret;
    };

    std::cerr << "\rLUT106   ";
    Ciphertext gin106 = 1 * gout62[0] + 2 * gout54[0];
    std::vector<Ciphertext> gout106 = ctx.eval_lut_amortized(&gin106, lut106);

    std::vector<RotationPoly> lut107;
    std::vector<long (*)(long)> flut107;
    auto lut107idx0 = [](long I) -> long {
        /* GATE 229 (LUT3 _1256_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut107.push_back(ctx.genrate_lut(lut107idx0));
    flut107.push_back(lut107idx0);
    auto fvec107 = [flut107](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut107[i](I));
        return ret;
    };

    std::cerr << "\rLUT107   ";
    Ciphertext gin107 = 1 * ct_my_string22 + 2 * gout76[1] + 4 * ct_my_string6;
    std::vector<Ciphertext> gout107 = ctx.eval_lut_amortized(&gin107, lut107);

    std::vector<RotationPoly> lut108;
    std::vector<long (*)(long)> flut108;
    auto lut108idx0 = [](long I) -> long {
        /* GATE 302 (LUT3 _1329_ INIT 0x35 PERM 210) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut108.push_back(ctx.genrate_lut(lut108idx0));
    flut108.push_back(lut108idx0);
    auto fvec108 = [flut108](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut108[i](I));
        return ret;
    };

    std::cerr << "\rLUT108   ";
    Ciphertext gin108 = 1 * gout106[1] + 2 * ct_my_string0 + 4 * ct_my_string40;
    std::vector<Ciphertext> gout108 = ctx.eval_lut_amortized(&gin108, lut108);

    std::vector<RotationPoly> lut109;
    std::vector<long (*)(long)> flut109;
    auto lut109idx0 = [](long I) -> long {
        /* GATE 66 (LUT3 _1093_ INIT 0x70 PERM 120) */
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
    lut109.push_back(ctx.genrate_lut(lut109idx0));
    flut109.push_back(lut109idx0);
    auto fvec109 = [flut109](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut109[i](I));
        return ret;
    };

    std::cerr << "\rLUT109   ";
    Ciphertext gin109 = 1 * gout64[0] + 2 * ct_my_string24 + 4 * gout66[0];
    std::vector<Ciphertext> gout109 = ctx.eval_lut_amortized(&gin109, lut109);

    std::vector<RotationPoly> lut110;
    std::vector<long (*)(long)> flut110;
    auto lut110idx0 = [](long I) -> long {
        /* GATE 305 (LUT3 _1332_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut110.push_back(ctx.genrate_lut(lut110idx0));
    flut110.push_back(lut110idx0);
    auto fvec110 = [flut110](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut110[i](I));
        return ret;
    };

    std::cerr << "\rLUT110   ";
    Ciphertext gin110 = 1 * ct_my_string41 + 2 * gout106[1] + 4 * ct_my_string1;
    std::vector<Ciphertext> gout110 = ctx.eval_lut_amortized(&gin110, lut110);

    std::vector<RotationPoly> lut111;
    std::vector<long (*)(long)> flut111;
    auto lut111idx0 = [](long I) -> long {
        /* GATE 308 (LUT3 _1335_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut111.push_back(ctx.genrate_lut(lut111idx0));
    flut111.push_back(lut111idx0);
    auto fvec111 = [flut111](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut111[i](I));
        return ret;
    };

    std::cerr << "\rLUT111   ";
    Ciphertext gin111 = 1 * ct_my_string42 + 2 * gout106[1] + 4 * ct_my_string2;
    std::vector<Ciphertext> gout111 = ctx.eval_lut_amortized(&gin111, lut111);

    std::vector<RotationPoly> lut112;
    std::vector<long (*)(long)> flut112;
    auto lut112idx0 = [](long I) -> long {
        /* GATE 164 (LUT3 _1191_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut112.push_back(ctx.genrate_lut(lut112idx0));
    flut112.push_back(lut112idx0);
    auto lut112idx1 = [](long I) -> long {
        /* GATE 95 (LUT2 _1122_ INIT 0x8 PERM 10) */
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
    lut112.push_back(ctx.genrate_lut(lut112idx1));
    flut112.push_back(lut112idx1);
    auto fvec112 = [flut112](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut112[i](I));
        return ret;
    };

    std::cerr << "\rLUT112   ";
    Ciphertext gin112 = 1 * ct_my_string12 + 2 * gout106[0] + 4 * ct_my_string4;
    std::vector<Ciphertext> gout112 = ctx.eval_lut_amortized(&gin112, lut112);

    std::vector<RotationPoly> lut113;
    std::vector<long (*)(long)> flut113;
    auto lut113idx0 = [](long I) -> long {
        /* GATE 96 (LUT3 _1123_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut113.push_back(ctx.genrate_lut(lut113idx0));
    flut113.push_back(lut113idx0);
    auto fvec113 = [flut113](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut113[i](I));
        return ret;
    };

    std::cerr << "\rLUT113   ";
    Ciphertext gin113 = 1 * gout65[0] + 2 * ct_my_string28 + 4 * gout66[0];
    std::vector<Ciphertext> gout113 = ctx.eval_lut_amortized(&gin113, lut113);

    std::vector<RotationPoly> lut114;
    std::vector<long (*)(long)> flut114;
    auto lut114idx0 = [](long I) -> long {
        /* GATE 82 (LUT3 _1109_ INIT 0x70 PERM 120) */
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
    lut114.push_back(ctx.genrate_lut(lut114idx0));
    flut114.push_back(lut114idx0);
    auto fvec114 = [flut114](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut114[i](I));
        return ret;
    };

    std::cerr << "\rLUT114   ";
    Ciphertext gin114 = 1 * gout41[0] + 2 * ct_my_string26 + 4 * gout66[0];
    std::vector<Ciphertext> gout114 = ctx.eval_lut_amortized(&gin114, lut114);

    std::vector<RotationPoly> lut115;
    std::vector<long (*)(long)> flut115;
    auto lut115idx0 = [](long I) -> long {
        /* GATE 354 (LUT3 _1381_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut115.push_back(ctx.genrate_lut(lut115idx0));
    flut115.push_back(lut115idx0);
    auto fvec115 = [flut115](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut115[i](I));
        return ret;
    };

    std::cerr << "\rLUT115   ";
    Ciphertext gin115 = 1 * ct_my_string46 + 2 * ct_my_string14 + 4 * gout62[0];
    std::vector<Ciphertext> gout115 = ctx.eval_lut_amortized(&gin115, lut115);

    std::vector<RotationPoly> lut116;
    std::vector<long (*)(long)> flut116;
    auto lut116idx0 = [](long I) -> long {
        /* GATE 155 (LUT2 _1182_ INIT 0x8 PERM 10) */
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
    lut116.push_back(ctx.genrate_lut(lut116idx0));
    flut116.push_back(lut116idx0);
    auto fvec116 = [flut116](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut116[i](I));
        return ret;
    };

    std::cerr << "\rLUT116   ";
    Ciphertext gin116 = 1 * ct_my_string35 + 2 * gout106[1];
    std::vector<Ciphertext> gout116 = ctx.eval_lut_amortized(&gin116, lut116);

    std::vector<RotationPoly> lut117;
    std::vector<long (*)(long)> flut117;
    auto lut117idx0 = [](long I) -> long {
        /* GATE 208 (LUT3 _1235_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut117.push_back(ctx.genrate_lut(lut117idx0));
    flut117.push_back(lut117idx0);
    auto fvec117 = [flut117](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut117[i](I));
        return ret;
    };

    std::cerr << "\rLUT117   ";
    Ciphertext gin117 = 1 * gout80[0] + 2 * ct_my_string43 + 4 * gout56[1];
    std::vector<Ciphertext> gout117 = ctx.eval_lut_amortized(&gin117, lut117);

    std::vector<RotationPoly> lut118;
    std::vector<long (*)(long)> flut118;
    auto lut118idx0 = [](long I) -> long {
        /* GATE 130 (LUT3 _1157_ INIT 0x7 PERM 210) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut118.push_back(ctx.genrate_lut(lut118idx0));
    flut118.push_back(lut118idx0);
    auto fvec118 = [flut118](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut118[i](I));
        return ret;
    };

    std::cerr << "\rLUT118   ";
    Ciphertext gin118 = 1 * gout67[0] + 2 * gout106[1] + 4 * ct_my_string32;
    std::vector<Ciphertext> gout118 = ctx.eval_lut_amortized(&gin118, lut118);

    std::vector<RotationPoly> lut119;
    std::vector<long (*)(long)> flut119;
    auto lut119idx0 = [](long I) -> long {
        /* GATE 205 (LUT3 _1232_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut119.push_back(ctx.genrate_lut(lut119idx0));
    flut119.push_back(lut119idx0);
    auto lut119idx1 = [](long I) -> long {
        /* GATE 79 (LUT2 _1106_ INIT 0x8 PERM 10) */
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
    lut119.push_back(ctx.genrate_lut(lut119idx1));
    flut119.push_back(lut119idx1);
    auto fvec119 = [flut119](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut119[i](I));
        return ret;
    };

    std::cerr << "\rLUT119   ";
    Ciphertext gin119 = 1 * ct_my_string18 + 2 * gout76[1] + 4 * ct_my_string2;
    std::vector<Ciphertext> gout119 = ctx.eval_lut_amortized(&gin119, lut119);

    std::vector<RotationPoly> lut120;
    std::vector<long (*)(long)> flut120;
    auto lut120idx0 = [](long I) -> long {
        /* GATE 203 (LUT2 _1230_ INIT 0x8 PERM 10) */
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
    lut120.push_back(ctx.genrate_lut(lut120idx0));
    flut120.push_back(lut120idx0);
    auto fvec120 = [flut120](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut120[i](I));
        return ret;
    };

    std::cerr << "\rLUT120   ";
    Ciphertext gin120 = 1 * ct_my_string26 + 2 * gout106[1];
    std::vector<Ciphertext> gout120 = ctx.eval_lut_amortized(&gin120, lut120);

    std::vector<RotationPoly> lut121;
    std::vector<long (*)(long)> flut121;
    auto lut121idx0 = [](long I) -> long {
        /* GATE 213 (LUT3 _1240_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut121.push_back(ctx.genrate_lut(lut121idx0));
    flut121.push_back(lut121idx0);
    auto fvec121 = [flut121](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut121[i](I));
        return ret;
    };

    std::cerr << "\rLUT121   ";
    Ciphertext gin121 = 1 * ct_my_string19 + 2 * gout76[1] + 4 * ct_my_string3;
    std::vector<Ciphertext> gout121 = ctx.eval_lut_amortized(&gin121, lut121);

    std::vector<RotationPoly> lut122;
    std::vector<long (*)(long)> flut122;
    auto lut122idx0 = [](long I) -> long {
        /* GATE 259 (LUT3 _1286_ INIT 0xca PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut122.push_back(ctx.genrate_lut(lut122idx0));
    flut122.push_back(lut122idx0);
    auto fvec122 = [flut122](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut122[i](I));
        return ret;
    };

    std::cerr << "\rLUT122   ";
    Ciphertext gin122 = 1 * ct_my_string29 + 2 * gout66[0] + 4 * ct_my_string5;
    std::vector<Ciphertext> gout122 = ctx.eval_lut_amortized(&gin122, lut122);

    std::vector<RotationPoly> lut123;
    std::vector<long (*)(long)> flut123;
    auto lut123idx0 = [](long I) -> long {
        /* GATE 190 (LUT3 _1217_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut123.push_back(ctx.genrate_lut(lut123idx0));
    flut123.push_back(lut123idx0);
    auto lut123idx1 = [](long I) -> long {
        /* GATE 121 (LUT2 _1148_ INIT 0x8 PERM 10) */
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
    lut123.push_back(ctx.genrate_lut(lut123idx1));
    flut123.push_back(lut123idx1);
    auto fvec123 = [flut123](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut123[i](I));
        return ret;
    };

    std::cerr << "\rLUT123   ";
    Ciphertext gin123 = 1 * ct_my_string15 + 2 * gout106[0] + 4 * ct_my_string7;
    std::vector<Ciphertext> gout123 = ctx.eval_lut_amortized(&gin123, lut123);

    std::vector<RotationPoly> lut124;
    std::vector<long (*)(long)> flut124;
    auto lut124idx0 = [](long I) -> long {
        /* GATE 239 (LUT3 _1266_ INIT 0xca PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut124.push_back(ctx.genrate_lut(lut124idx0));
    flut124.push_back(lut124idx0);
    auto fvec124 = [flut124](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut124[i](I));
        return ret;
    };

    std::cerr << "\rLUT124   ";
    Ciphertext gin124 = 1 * ct_my_string24 + 2 * gout66[0] + 4 * ct_my_string0;
    std::vector<Ciphertext> gout124 = ctx.eval_lut_amortized(&gin124, lut124);

    std::vector<RotationPoly> lut125;
    std::vector<long (*)(long)> flut125;
    auto lut125idx0 = [](long I) -> long {
        /* GATE 153 (LUT3 _1180_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut125.push_back(ctx.genrate_lut(lut125idx0));
    flut125.push_back(lut125idx0);
    auto fvec125 = [flut125](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut125[i](I));
        return ret;
    };

    std::cerr << "\rLUT125   ";
    Ciphertext gin125 = 1 * ct_my_string11 + 2 * gout106[0] + 4 * ct_my_string3;
    std::vector<Ciphertext> gout125 = ctx.eval_lut_amortized(&gin125, lut125);

    std::vector<RotationPoly> lut126;
    std::vector<long (*)(long)> flut126;
    auto lut126idx0 = [](long I) -> long {
        /* GATE 223 (LUT3 _1250_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut126.push_back(ctx.genrate_lut(lut126idx0));
    flut126.push_back(lut126idx0);
    auto fvec126 = [flut126](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut126[i](I));
        return ret;
    };

    std::cerr << "\rLUT126   ";
    Ciphertext gin126 = 1 * ct_my_string21 + 2 * gout76[1] + 4 * ct_my_string5;
    std::vector<Ciphertext> gout126 = ctx.eval_lut_amortized(&gin126, lut126);

    std::vector<RotationPoly> lut127;
    std::vector<long (*)(long)> flut127;
    auto lut127idx0 = [](long I) -> long {
        /* GATE 158 (LUT3 _1185_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut127.push_back(ctx.genrate_lut(lut127idx0));
    flut127.push_back(lut127idx0);
    auto fvec127 = [flut127](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut127[i](I));
        return ret;
    };

    std::cerr << "\rLUT127   ";
    Ciphertext gin127 = 1 * gout80[0] + 2 * ct_my_string51 + 4 * gout56[1];
    std::vector<Ciphertext> gout127 = ctx.eval_lut_amortized(&gin127, lut127);

    std::vector<RotationPoly> lut128;
    std::vector<long (*)(long)> flut128;
    auto lut128idx0 = [](long I) -> long {
        /* GATE 152 (LUT2 _1179_ INIT 0x1 PERM 01) */
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
    lut128.push_back(ctx.genrate_lut(lut128idx0));
    flut128.push_back(lut128idx0);
    auto fvec128 = [flut128](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut128[i](I));
        return ret;
    };

    std::cerr << "\rLUT128   ";
    Ciphertext gin128 = 1 * gout125[0] + 2 * gout55[0];
    std::vector<Ciphertext> gout128 = ctx.eval_lut_amortized(&gin128, lut128);

    std::vector<RotationPoly> lut129;
    std::vector<long (*)(long)> flut129;
    auto lut129idx0 = [](long I) -> long {
        /* GATE 233 (LUT2 _1260_ INIT 0x8 PERM 10) */
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
    lut129.push_back(ctx.genrate_lut(lut129idx0));
    flut129.push_back(lut129idx0);
    auto fvec129 = [flut129](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut129[i](I));
        return ret;
    };

    std::cerr << "\rLUT129   ";
    Ciphertext gin129 = 1 * ct_my_string31 + 2 * gout106[1];
    std::vector<Ciphertext> gout129 = ctx.eval_lut_amortized(&gin129, lut129);

    std::vector<RotationPoly> lut130;
    std::vector<long (*)(long)> flut130;
    auto lut130idx0 = [](long I) -> long {
        /* GATE 335 (LUT3 _1362_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut130.push_back(ctx.genrate_lut(lut130idx0));
    flut130.push_back(lut130idx0);
    auto lut130idx1 = [](long I) -> long {
        /* GATE 106 (LUT2 _1133_ INIT 0x8 PERM 20) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut130.push_back(ctx.genrate_lut(lut130idx1));
    flut130.push_back(lut130idx1);
    auto fvec130 = [flut130](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut130[i](I));
        return ret;
    };

    std::cerr << "\rLUT130   ";
    Ciphertext gin130 = 1 * ct_my_string53 + 2 * ct_my_string5 + 4 * gout76[0];
    std::vector<Ciphertext> gout130 = ctx.eval_lut_amortized(&gin130, lut130);

    std::vector<RotationPoly> lut131;
    std::vector<long (*)(long)> flut131;
    auto lut131idx0 = [](long I) -> long {
        /* GATE 211 (LUT3 _1238_ INIT 0x10 PERM 120) */
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
    lut131.push_back(ctx.genrate_lut(lut131idx0));
    flut131.push_back(lut131idx0);
    auto fvec131 = [flut131](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut131[i](I));
        return ret;
    };

    std::cerr << "\rLUT131   ";
    Ciphertext gin131 = 1 * ct_my_string59 + 2 * gout76[1] + 4 * gout55[0];
    std::vector<Ciphertext> gout131 = ctx.eval_lut_amortized(&gin131, lut131);

    std::vector<RotationPoly> lut132;
    std::vector<long (*)(long)> flut132;
    auto lut132idx0 = [](long I) -> long {
        /* GATE 323 (LUT3 _1350_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut132.push_back(ctx.genrate_lut(lut132idx0));
    flut132.push_back(lut132idx0);
    auto fvec132 = [flut132](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut132[i](I));
        return ret;
    };

    std::cerr << "\rLUT132   ";
    Ciphertext gin132 = 1 * ct_my_string47 + 2 * gout106[1] + 4 * ct_my_string7;
    std::vector<Ciphertext> gout132 = ctx.eval_lut_amortized(&gin132, lut132);

    std::vector<RotationPoly> lut133;
    std::vector<long (*)(long)> flut133;
    auto lut133idx0 = [](long I) -> long {
        /* GATE 216 (LUT3 _1243_ INIT 0xca PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut133.push_back(ctx.genrate_lut(lut133idx0));
    flut133.push_back(lut133idx0);
    auto fvec133 = [flut133](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut133[i](I));
        return ret;
    };

    std::cerr << "\rLUT133   ";
    Ciphertext gin133 = 1 * gout85[0] + 2 * gout66[0] + 4 * gout112[0];
    std::vector<Ciphertext> gout133 = ctx.eval_lut_amortized(&gin133, lut133);

    std::vector<RotationPoly> lut134;
    std::vector<long (*)(long)> flut134;
    auto lut134idx0 = [](long I) -> long {
        /* GATE 157 (LUT2 _1184_ INIT 0x8 PERM 10) */
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
    lut134.push_back(ctx.genrate_lut(lut134idx0));
    flut134.push_back(lut134idx0);
    auto fvec134 = [flut134](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut134[i](I));
        return ret;
    };

    std::cerr << "\rLUT134   ";
    Ciphertext gin134 = 1 * ct_my_string43 + 2 * gout76[0];
    std::vector<Ciphertext> gout134 = ctx.eval_lut_amortized(&gin134, lut134);

    std::vector<RotationPoly> lut135;
    std::vector<long (*)(long)> flut135;
    auto lut135idx0 = [](long I) -> long {
        /* GATE 135 (LUT3 _1162_ INIT 0x70 PERM 120) */
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
    lut135.push_back(ctx.genrate_lut(lut135idx0));
    flut135.push_back(lut135idx0);
    auto fvec135 = [flut135](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut135[i](I));
        return ret;
    };

    std::cerr << "\rLUT135   ";
    Ciphertext gin135 = 1 * gout87[0] + 2 * ct_my_string33 + 4 * gout106[1];
    std::vector<Ciphertext> gout135 = ctx.eval_lut_amortized(&gin135, lut135);

    std::vector<RotationPoly> lut136;
    std::vector<long (*)(long)> flut136;
    auto lut136idx0 = [](long I) -> long {
        /* GATE 227 (LUT2 _1254_ INIT 0x8 PERM 10) */
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
    lut136.push_back(ctx.genrate_lut(lut136idx0));
    flut136.push_back(lut136idx0);
    auto fvec136 = [flut136](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut136[i](I));
        return ret;
    };

    std::cerr << "\rLUT136   ";
    Ciphertext gin136 = 1 * ct_my_string30 + 2 * gout106[1];
    std::vector<Ciphertext> gout136 = ctx.eval_lut_amortized(&gin136, lut136);

    std::vector<RotationPoly> lut137;
    std::vector<long (*)(long)> flut137;
    auto lut137idx0 = [](long I) -> long {
        /* GATE 141 (LUT3 _1168_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut137.push_back(ctx.genrate_lut(lut137idx0));
    flut137.push_back(lut137idx0);
    auto fvec137 = [flut137](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut137[i](I));
        return ret;
    };

    std::cerr << "\rLUT137   ";
    Ciphertext gin137 = 1 * ct_my_string9 + 2 * gout106[0] + 4 * ct_my_string1;
    std::vector<Ciphertext> gout137 = ctx.eval_lut_amortized(&gin137, lut137);

    std::vector<RotationPoly> lut138;
    std::vector<long (*)(long)> flut138;
    auto lut138idx0 = [](long I) -> long {
        /* GATE 88 (LUT3 _1115_ INIT 0x70 PERM 120) */
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
    lut138.push_back(ctx.genrate_lut(lut138idx0));
    flut138.push_back(lut138idx0);
    auto fvec138 = [flut138](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut138[i](I));
        return ret;
    };

    std::cerr << "\rLUT138   ";
    Ciphertext gin138 = 1 * gout90[0] + 2 * ct_my_string19 + 4 * gout76[1];
    std::vector<Ciphertext> gout138 = ctx.eval_lut_amortized(&gin138, lut138);

    std::vector<RotationPoly> lut139;
    std::vector<long (*)(long)> flut139;
    auto lut139idx0 = [](long I) -> long {
        /* GATE 314 (LUT3 _1341_ INIT 0xca PERM 210) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut139.push_back(ctx.genrate_lut(lut139idx0));
    flut139.push_back(lut139idx0);
    auto fvec139 = [flut139](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut139[i](I));
        return ret;
    };

    std::cerr << "\rLUT139   ";
    Ciphertext gin139 = 1 * gout106[1] + 2 * ct_my_string4 + 4 * ct_my_string44;
    std::vector<Ciphertext> gout139 = ctx.eval_lut_amortized(&gin139, lut139);

    std::vector<RotationPoly> lut140;
    std::vector<long (*)(long)> flut140;
    auto lut140idx0 = [](long I) -> long {
        /* GATE 317 (LUT3 _1344_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut140.push_back(ctx.genrate_lut(lut140idx0));
    flut140.push_back(lut140idx0);
    auto fvec140 = [flut140](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut140[i](I));
        return ret;
    };

    std::cerr << "\rLUT140   ";
    Ciphertext gin140 = 1 * ct_my_string45 + 2 * gout106[1] + 4 * ct_my_string5;
    std::vector<Ciphertext> gout140 = ctx.eval_lut_amortized(&gin140, lut140);

    std::vector<RotationPoly> lut141;
    std::vector<long (*)(long)> flut141;
    auto lut141idx0 = [](long I) -> long {
        /* GATE 320 (LUT3 _1347_ INIT 0x35 PERM 210) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut141.push_back(ctx.genrate_lut(lut141idx0));
    flut141.push_back(lut141idx0);
    auto fvec141 = [flut141](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut141[i](I));
        return ret;
    };

    std::cerr << "\rLUT141   ";
    Ciphertext gin141 = 1 * gout106[1] + 2 * ct_my_string6 + 4 * ct_my_string46;
    std::vector<Ciphertext> gout141 = ctx.eval_lut_amortized(&gin141, lut141);

    std::vector<RotationPoly> lut142;
    std::vector<long (*)(long)> flut142;
    auto lut142idx0 = [](long I) -> long {
        /* GATE 93 (LUT3 _1120_ INIT 0x7 PERM 210) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut142.push_back(ctx.genrate_lut(lut142idx0));
    flut142.push_back(lut142idx0);
    auto fvec142 = [flut142](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut142[i](I));
        return ret;
    };

    std::cerr << "\rLUT142   ";
    Ciphertext gin142 = 1 * gout85[1] + 2 * gout106[1] + 4 * ct_my_string44;
    std::vector<Ciphertext> gout142 = ctx.eval_lut_amortized(&gin142, lut142);

    std::vector<RotationPoly> lut143;
    std::vector<long (*)(long)> flut143;
    auto lut143idx0 = [](long I) -> long {
        /* GATE 145 (LUT3 _1172_ INIT 0x70 PERM 120) */
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
    lut143.push_back(ctx.genrate_lut(lut143idx0));
    flut143.push_back(lut143idx0);
    auto fvec143 = [flut143](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut143[i](I));
        return ret;
    };

    std::cerr << "\rLUT143   ";
    Ciphertext gin143 = 1 * gout100[0] + 2 * ct_my_string18 + 4 * gout66[0];
    std::vector<Ciphertext> gout143 = ctx.eval_lut_amortized(&gin143, lut143);

    std::vector<RotationPoly> lut144;
    std::vector<long (*)(long)> flut144;
    auto lut144idx0 = [](long I) -> long {
        /* GATE 173 (LUT2 _1200_ INIT 0x8 PERM 10) */
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
    lut144.push_back(ctx.genrate_lut(lut144idx0));
    flut144.push_back(lut144idx0);
    auto fvec144 = [flut144](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut144[i](I));
        return ret;
    };

    std::cerr << "\rLUT144   ";
    Ciphertext gin144 = 1 * ct_my_string37 + 2 * gout106[1];
    std::vector<Ciphertext> gout144 = ctx.eval_lut_amortized(&gin144, lut144);

    std::vector<RotationPoly> lut145;
    std::vector<long (*)(long)> flut145;
    auto lut145idx0 = [](long I) -> long {
        /* GATE 181 (LUT2 _1208_ INIT 0x8 PERM 10) */
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
    lut145.push_back(ctx.genrate_lut(lut145idx0));
    flut145.push_back(lut145idx0);
    auto fvec145 = [flut145](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut145[i](I));
        return ret;
    };

    std::cerr << "\rLUT145   ";
    Ciphertext gin145 = 1 * ct_my_string38 + 2 * gout106[1];
    std::vector<Ciphertext> gout145 = ctx.eval_lut_amortized(&gin145, lut145);

    std::vector<RotationPoly> lut146;
    std::vector<long (*)(long)> flut146;
    auto lut146idx0 = [](long I) -> long {
        /* GATE 338 (LUT3 _1365_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut146.push_back(ctx.genrate_lut(lut146idx0));
    flut146.push_back(lut146idx0);
    auto fvec146 = [flut146](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut146[i](I));
        return ret;
    };

    std::cerr << "\rLUT146   ";
    Ciphertext gin146 = 1 * gout81[0] + 2 * gout123[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout146 = ctx.eval_lut_amortized(&gin146, lut146);

    std::vector<RotationPoly> lut147;
    std::vector<long (*)(long)> flut147;
    auto lut147idx0 = [](long I) -> long {
        /* GATE 105 (LUT3 _1132_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut147.push_back(ctx.genrate_lut(lut147idx0));
    flut147.push_back(lut147idx0);
    auto fvec147 = [flut147](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut147[i](I));
        return ret;
    };

    std::cerr << "\rLUT147   ";
    Ciphertext gin147 = 1 * gout130[1] + 2 * ct_my_string45 + 4 * gout106[1];
    std::vector<Ciphertext> gout147 = ctx.eval_lut_amortized(&gin147, lut147);

    std::vector<RotationPoly> lut148;
    std::vector<long (*)(long)> flut148;
    auto lut148idx0 = [](long I) -> long {
        /* GATE 174 (LUT3 _1201_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut148.push_back(ctx.genrate_lut(lut148idx0));
    flut148.push_back(lut148idx0);
    auto lut148idx1 = [](long I) -> long {
        /* GATE 104 (LUT2 _1131_ INIT 0x8 PERM 10) */
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
    lut148.push_back(ctx.genrate_lut(lut148idx1));
    flut148.push_back(lut148idx1);
    auto fvec148 = [flut148](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut148[i](I));
        return ret;
    };

    std::cerr << "\rLUT148   ";
    Ciphertext gin148 = 1 * ct_my_string13 + 2 * gout106[0] + 4 * ct_my_string5;
    std::vector<Ciphertext> gout148 = ctx.eval_lut_amortized(&gin148, lut148);

    std::vector<RotationPoly> lut149;
    std::vector<long (*)(long)> flut149;
    auto lut149idx0 = [](long I) -> long {
        /* GATE 330 (LUT3 _1357_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut149.push_back(ctx.genrate_lut(lut149idx0));
    flut149.push_back(lut149idx0);
    auto fvec149 = [flut149](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut149[i](I));
        return ret;
    };

    std::cerr << "\rLUT149   ";
    Ciphertext gin149 = 1 * gout89[0] + 2 * gout125[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout149 = ctx.eval_lut_amortized(&gin149, lut149);

    std::vector<RotationPoly> lut150;
    std::vector<long (*)(long)> flut150;
    auto lut150idx0 = [](long I) -> long {
        /* GATE 316 (LUT3 _1343_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut150.push_back(ctx.genrate_lut(lut150idx0));
    flut150.push_back(lut150idx0);
    auto fvec150 = [flut150](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut150[i](I));
        return ret;
    };

    std::cerr << "\rLUT150   ";
    Ciphertext gin150 = 1 * gout140[0] + 2 * gout148[0] + 4 * gout76[0];
    std::vector<Ciphertext> gout150 = ctx.eval_lut_amortized(&gin150, lut150);

    std::vector<RotationPoly> lut151;
    std::vector<long (*)(long)> flut151;
    auto lut151idx0 = [](long I) -> long {
        /* GATE 167 (LUT3 _1194_ INIT 0x1 PERM 012) */
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
    lut151.push_back(ctx.genrate_lut(lut151idx0));
    flut151.push_back(lut151idx0);
    auto fvec151 = [flut151](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut151[i](I));
        return ret;
    };

    std::cerr << "\rLUT151   ";
    Ciphertext gin151 = 1 * gout84[0] + 2 * gout105[0] + 4 * gout45[0];
    std::vector<Ciphertext> gout151 = ctx.eval_lut_amortized(&gin151, lut151);

    std::vector<RotationPoly> lut152;
    std::vector<long (*)(long)> flut152;
    auto lut152idx0 = [](long I) -> long {
        /* GATE 322 (LUT3 _1349_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut152.push_back(ctx.genrate_lut(lut152idx0));
    flut152.push_back(lut152idx0);
    auto fvec152 = [flut152](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut152[i](I));
        return ret;
    };

    std::cerr << "\rLUT152   ";
    Ciphertext gin152 = 1 * gout132[0] + 2 * gout123[0] + 4 * gout76[0];
    std::vector<Ciphertext> gout152 = ctx.eval_lut_amortized(&gin152, lut152);

    std::vector<RotationPoly> lut153;
    std::vector<long (*)(long)> flut153;
    auto lut153idx0 = [](long I) -> long {
        /* GATE 103 (LUT3 _1130_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut153.push_back(ctx.genrate_lut(lut153idx0));
    flut153.push_back(lut153idx0);
    auto fvec153 = [flut153](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut153[i](I));
        return ret;
    };

    std::cerr << "\rLUT153   ";
    Ciphertext gin153 = 1 * gout148[1] + 2 * ct_my_string21 + 4 * gout76[1];
    std::vector<Ciphertext> gout153 = ctx.eval_lut_amortized(&gin153, lut153);

    std::vector<RotationPoly> lut154;
    std::vector<long (*)(long)> flut154;
    auto lut154idx0 = [](long I) -> long {
        /* GATE 313 (LUT3 _1340_ INIT 0x3a PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut154.push_back(ctx.genrate_lut(lut154idx0));
    flut154.push_back(lut154idx0);
    auto fvec154 = [flut154](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut154[i](I));
        return ret;
    };

    std::cerr << "\rLUT154   ";
    Ciphertext gin154 = 1 * gout139[0] + 2 * gout112[0] + 4 * gout76[0];
    std::vector<Ciphertext> gout154 = ctx.eval_lut_amortized(&gin154, lut154);

    std::vector<RotationPoly> lut155;
    std::vector<long (*)(long)> flut155;
    auto lut155idx0 = [](long I) -> long {
        /* GATE 150 (LUT3 _1177_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut155.push_back(ctx.genrate_lut(lut155idx0));
    flut155.push_back(lut155idx0);
    auto fvec155 = [flut155](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut155[i](I));
        return ret;
    };

    std::cerr << "\rLUT155   ";
    Ciphertext gin155 = 1 * ct_my_string10 + 2 * gout106[0] + 4 * ct_my_string2;
    std::vector<Ciphertext> gout155 = ctx.eval_lut_amortized(&gin155, lut155);

    std::vector<RotationPoly> lut156;
    std::vector<long (*)(long)> flut156;
    auto lut156idx0 = [](long I) -> long {
        /* GATE 351 (LUT3 _1378_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut156.push_back(ctx.genrate_lut(lut156idx0));
    flut156.push_back(lut156idx0);
    auto fvec156 = [flut156](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut156[i](I));
        return ret;
    };

    std::cerr << "\rLUT156   ";
    Ciphertext gin156 = 1 * ct_my_string43 + 2 * ct_my_string11 + 4 * gout62[0];
    std::vector<Ciphertext> gout156 = ctx.eval_lut_amortized(&gin156, lut156);

    std::vector<RotationPoly> lut157;
    std::vector<long (*)(long)> flut157;
    auto lut157idx0 = [](long I) -> long {
        /* GATE 333 (LUT3 _1360_ INIT 0x35 PERM 102) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut157.push_back(ctx.genrate_lut(lut157idx0));
    flut157.push_back(lut157idx0);
    auto fvec157 = [flut157](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut157[i](I));
        return ret;
    };

    std::cerr << "\rLUT157   ";
    Ciphertext gin157 = 1 * ct_my_string4 + 2 * ct_my_string52 + 4 * gout76[0];
    std::vector<Ciphertext> gout157 = ctx.eval_lut_amortized(&gin157, lut157);

    std::vector<RotationPoly> lut158;
    std::vector<long (*)(long)> flut158;
    auto lut158idx0 = [](long I) -> long {
        /* GATE 311 (LUT3 _1338_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut158.push_back(ctx.genrate_lut(lut158idx0));
    flut158.push_back(lut158idx0);
    auto fvec158 = [flut158](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut158[i](I));
        return ret;
    };

    std::cerr << "\rLUT158   ";
    Ciphertext gin158 = 1 * ct_my_string43 + 2 * gout106[1] + 4 * ct_my_string3;
    std::vector<Ciphertext> gout158 = ctx.eval_lut_amortized(&gin158, lut158);

    std::vector<RotationPoly> lut159;
    std::vector<long (*)(long)> flut159;
    auto lut159idx0 = [](long I) -> long {
        /* GATE 327 (LUT3 _1354_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut159.push_back(ctx.genrate_lut(lut159idx0));
    flut159.push_back(lut159idx0);
    auto fvec159 = [flut159](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut159[i](I));
        return ret;
    };

    std::cerr << "\rLUT159   ";
    Ciphertext gin159 = 1 * ct_my_string49 + 2 * ct_my_string1 + 4 * gout76[0];
    std::vector<Ciphertext> gout159 = ctx.eval_lut_amortized(&gin159, lut159);

    std::vector<RotationPoly> lut160;
    std::vector<long (*)(long)> flut160;
    auto lut160idx0 = [](long I) -> long {
        /* GATE 110 (LUT3 _1137_ INIT 0x70 PERM 120) */
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
    lut160.push_back(ctx.genrate_lut(lut160idx0));
    flut160.push_back(lut160idx0);
    auto fvec160 = [flut160](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut160[i](I));
        return ret;
    };

    std::cerr << "\rLUT160   ";
    Ciphertext gin160 = 1 * gout97[0] + 2 * ct_my_string22 + 4 * gout76[1];
    std::vector<Ciphertext> gout160 = ctx.eval_lut_amortized(&gin160, lut160);

    std::vector<RotationPoly> lut161;
    std::vector<long (*)(long)> flut161;
    auto lut161idx0 = [](long I) -> long {
        /* GATE 182 (LUT3 _1209_ INIT 0x35 PERM 210) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut161.push_back(ctx.genrate_lut(lut161idx0));
    flut161.push_back(lut161idx0);
    auto fvec161 = [flut161](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut161[i](I));
        return ret;
    };

    std::cerr << "\rLUT161   ";
    Ciphertext gin161 = 1 * gout106[0] + 2 * ct_my_string6 + 4 * ct_my_string14;
    std::vector<Ciphertext> gout161 = ctx.eval_lut_amortized(&gin161, lut161);

    std::vector<RotationPoly> lut162;
    std::vector<long (*)(long)> flut162;
    auto lut162idx0 = [](long I) -> long {
        /* GATE 337 (LUT3 _1364_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut162.push_back(ctx.genrate_lut(lut162idx0));
    flut162.push_back(lut162idx0);
    auto fvec162 = [flut162](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut162[i](I));
        return ret;
    };

    std::cerr << "\rLUT162   ";
    Ciphertext gin162 = 1 * ct_my_string54 + 2 * ct_my_string6 + 4 * gout76[0];
    std::vector<Ciphertext> gout162 = ctx.eval_lut_amortized(&gin162, lut162);

    std::vector<RotationPoly> lut163;
    std::vector<long (*)(long)> flut163;
    auto lut163idx0 = [](long I) -> long {
        /* GATE 349 (LUT3 _1376_ INIT 0x70 PERM 201) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut163.push_back(ctx.genrate_lut(lut163idx0));
    flut163.push_back(lut163idx0);
    auto fvec163 = [flut163](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut163[i](I));
        return ret;
    };

    std::cerr << "\rLUT163   ";
    Ciphertext gin163 = 1 * ct_my_string17 + 2 * gout88[0] + 4 * gout76[1];
    std::vector<Ciphertext> gout163 = ctx.eval_lut_amortized(&gin163, lut163);

    std::vector<RotationPoly> lut164;
    std::vector<long (*)(long)> flut164;
    auto lut164idx0 = [](long I) -> long {
        /* GATE 177 (LUT3 _1204_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut164.push_back(ctx.genrate_lut(lut164idx0));
    flut164.push_back(lut164idx0);
    auto fvec164 = [flut164](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut164[i](I));
        return ret;
    };

    std::cerr << "\rLUT164   ";
    Ciphertext gin164 = 1 * gout75[0] + 2 * ct_my_string22 + 4 * gout66[0];
    std::vector<Ciphertext> gout164 = ctx.eval_lut_amortized(&gin164, lut164);

    std::vector<RotationPoly> lut165;
    std::vector<long (*)(long)> flut165;
    auto lut165idx0 = [](long I) -> long {
        /* GATE 123 (LUT3 _1150_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut165.push_back(ctx.genrate_lut(lut165idx0));
    flut165.push_back(lut165idx0);
    auto fvec165 = [flut165](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut165[i](I));
        return ret;
    };

    std::cerr << "\rLUT165   ";
    Ciphertext gin165 = 1 * gout101[0] + 2 * ct_my_string31 + 4 * gout66[0];
    std::vector<Ciphertext> gout165 = ctx.eval_lut_amortized(&gin165, lut165);

    std::vector<RotationPoly> lut166;
    std::vector<long (*)(long)> flut166;
    auto lut166idx0 = [](long I) -> long {
        /* GATE 334 (LUT3 _1361_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut166.push_back(ctx.genrate_lut(lut166idx0));
    flut166.push_back(lut166idx0);
    auto fvec166 = [flut166](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut166[i](I));
        return ret;
    };

    std::cerr << "\rLUT166   ";
    Ciphertext gin166 = 1 * gout130[0] + 2 * gout148[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout166 = ctx.eval_lut_amortized(&gin166, lut166);

    std::vector<RotationPoly> lut167;
    std::vector<long (*)(long)> flut167;
    auto lut167idx0 = [](long I) -> long {
        /* GATE 61 (LUT2 _1088_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut167.push_back(ctx.genrate_lut(lut167idx0));
    flut167.push_back(lut167idx0);
    auto fvec167 = [flut167](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut167[i](I));
        return ret;
    };

    std::cerr << "\rLUT167   ";
    Ciphertext gin167 = 1 * gout52[0] + 2 * gout62[0];
    std::vector<Ciphertext> gout167 = ctx.eval_lut_amortized(&gin167, lut167);

    std::vector<RotationPoly> lut168;
    std::vector<long (*)(long)> flut168;
    auto lut168idx0 = [](long I) -> long {
        /* GATE 4 (LUT2 _1031_ INIT 0x8 PERM 10) */
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
    lut168.push_back(ctx.genrate_lut(lut168idx0));
    flut168.push_back(lut168idx0);
    auto fvec168 = [flut168](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut168[i](I));
        return ret;
    };

    std::cerr << "\rLUT168   ";
    Ciphertext gin168 = 1 * ct_my_string8 + 2 * gout106[0];
    std::vector<Ciphertext> gout168 = ctx.eval_lut_amortized(&gin168, lut168);

    std::vector<RotationPoly> lut169;
    std::vector<long (*)(long)> flut169;
    auto lut169idx0 = [](long I) -> long {
        /* GATE 332 (LUT3 _1359_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut169.push_back(ctx.genrate_lut(lut169idx0));
    flut169.push_back(lut169idx0);
    auto fvec169 = [flut169](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut169[i](I));
        return ret;
    };

    std::cerr << "\rLUT169   ";
    Ciphertext gin169 = 1 * gout157[0] + 2 * gout56[1] + 4 * gout112[0];
    std::vector<Ciphertext> gout169 = ctx.eval_lut_amortized(&gin169, lut169);

    std::vector<RotationPoly> lut170;
    std::vector<long (*)(long)> flut170;
    auto lut170idx0 = [](long I) -> long {
        /* GATE 172 (LUT2 _1199_ INIT 0x8 PERM 10) */
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
    lut170.push_back(ctx.genrate_lut(lut170idx0));
    flut170.push_back(lut170idx0);
    auto fvec170 = [flut170](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut170[i](I));
        return ret;
    };

    std::cerr << "\rLUT170   ";
    Ciphertext gin170 = 1 * ct_my_string29 + 2 * gout167[0];
    std::vector<Ciphertext> gout170 = ctx.eval_lut_amortized(&gin170, lut170);

    std::vector<RotationPoly> lut171;
    std::vector<long (*)(long)> flut171;
    auto lut171idx0 = [](long I) -> long {
        /* GATE 197 (LUT2 _1224_ INIT 0x8 PERM 10) */
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
    lut171.push_back(ctx.genrate_lut(lut171idx0));
    flut171.push_back(lut171idx0);
    auto fvec171 = [flut171](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut171[i](I));
        return ret;
    };

    std::cerr << "\rLUT171   ";
    Ciphertext gin171 = 1 * ct_my_string25 + 2 * gout106[1];
    std::vector<Ciphertext> gout171 = ctx.eval_lut_amortized(&gin171, lut171);

    std::vector<RotationPoly> lut172;
    std::vector<long (*)(long)> flut172;
    auto lut172idx0 = [](long I) -> long {
        /* GATE 329 (LUT3 _1356_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut172.push_back(ctx.genrate_lut(lut172idx0));
    flut172.push_back(lut172idx0);
    auto fvec172 = [flut172](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut172[i](I));
        return ret;
    };

    std::cerr << "\rLUT172   ";
    Ciphertext gin172 = 1 * ct_my_string50 + 2 * ct_my_string2 + 4 * gout76[0];
    std::vector<Ciphertext> gout172 = ctx.eval_lut_amortized(&gin172, lut172);

    std::vector<RotationPoly> lut173;
    std::vector<long (*)(long)> flut173;
    auto lut173idx0 = [](long I) -> long {
        /* GATE 180 (LUT2 _1207_ INIT 0x8 PERM 10) */
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
    lut173.push_back(ctx.genrate_lut(lut173idx0));
    flut173.push_back(lut173idx0);
    auto fvec173 = [flut173](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut173[i](I));
        return ret;
    };

    std::cerr << "\rLUT173   ";
    Ciphertext gin173 = 1 * ct_my_string30 + 2 * gout167[0];
    std::vector<Ciphertext> gout173 = ctx.eval_lut_amortized(&gin173, lut173);

    std::vector<RotationPoly> lut174;
    std::vector<long (*)(long)> flut174;
    auto lut174idx0 = [](long I) -> long {
        /* GATE 326 (LUT3 _1353_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut174.push_back(ctx.genrate_lut(lut174idx0));
    flut174.push_back(lut174idx0);
    auto fvec174 = [flut174](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut174[i](I));
        return ret;
    };

    std::cerr << "\rLUT174   ";
    Ciphertext gin174 = 1 * gout159[0] + 2 * gout137[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout174 = ctx.eval_lut_amortized(&gin174, lut174);

    std::vector<RotationPoly> lut175;
    std::vector<long (*)(long)> flut175;
    auto lut175idx0 = [](long I) -> long {
        /* GATE 202 (LUT3 _1229_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut175.push_back(ctx.genrate_lut(lut175idx0));
    flut175.push_back(lut175idx0);
    auto fvec175 = [flut175](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut175[i](I));
        return ret;
    };

    std::cerr << "\rLUT175   ";
    Ciphertext gin175 = 1 * gout120[0] + 2 * ct_my_string34 + 4 * gout76[0];
    std::vector<Ciphertext> gout175 = ctx.eval_lut_amortized(&gin175, lut175);

    std::vector<RotationPoly> lut176;
    std::vector<long (*)(long)> flut176;
    auto lut176idx0 = [](long I) -> long {
        /* GATE 215 (LUT2 _1242_ INIT 0x8 PERM 10) */
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
    lut176.push_back(ctx.genrate_lut(lut176idx0));
    flut176.push_back(lut176idx0);
    auto fvec176 = [flut176](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut176[i](I));
        return ret;
    };

    std::cerr << "\rLUT176   ";
    Ciphertext gin176 = 1 * ct_my_string28 + 2 * gout106[1];
    std::vector<Ciphertext> gout176 = ctx.eval_lut_amortized(&gin176, lut176);

    std::vector<RotationPoly> lut177;
    std::vector<long (*)(long)> flut177;
    auto lut177idx0 = [](long I) -> long {
        /* GATE 122 (LUT3 _1149_ INIT 0x70 PERM 120) */
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
    lut177.push_back(ctx.genrate_lut(lut177idx0));
    flut177.push_back(lut177idx0);
    auto fvec177 = [flut177](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut177[i](I));
        return ret;
    };

    std::cerr << "\rLUT177   ";
    Ciphertext gin177 = 1 * gout165[0] + 2 * ct_my_string47 + 4 * gout106[1];
    std::vector<Ciphertext> gout177 = ctx.eval_lut_amortized(&gin177, lut177);

    std::vector<RotationPoly> lut178;
    std::vector<long (*)(long)> flut178;
    auto lut178idx0 = [](long I) -> long {
        /* GATE 191 (LUT2 _1218_ INIT 0x7 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut178.push_back(ctx.genrate_lut(lut178idx0));
    flut178.push_back(lut178idx0);
    auto fvec178 = [flut178](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut178[i](I));
        return ret;
    };

    std::cerr << "\rLUT178   ";
    Ciphertext gin178 = 1 * ct_my_string24 + 2 * gout106[1];
    std::vector<Ciphertext> gout178 = ctx.eval_lut_amortized(&gin178, lut178);

    std::vector<RotationPoly> lut179;
    std::vector<long (*)(long)> flut179;
    auto lut179idx0 = [](long I) -> long {
        /* GATE 357 (LUT3 _1384_ INIT 0x7 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut179.push_back(ctx.genrate_lut(lut179idx0));
    flut179.push_back(lut179idx0);
    auto fvec179 = [flut179](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut179[i](I));
        return ret;
    };

    std::cerr << "\rLUT179   ";
    Ciphertext gin179 = 1 * gout56[1] + 2 * ct_my_string52 + 4 * gout102[0];
    std::vector<Ciphertext> gout179 = ctx.eval_lut_amortized(&gin179, lut179);

    std::vector<RotationPoly> lut180;
    std::vector<long (*)(long)> flut180;
    auto lut180idx0 = [](long I) -> long {
        /* GATE 212 (LUT3 _1239_ INIT 0xca PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut180.push_back(ctx.genrate_lut(lut180idx0));
    flut180.push_back(lut180idx0);
    auto fvec180 = [flut180](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut180[i](I));
        return ret;
    };

    std::cerr << "\rLUT180   ";
    Ciphertext gin180 = 1 * gout121[0] + 2 * gout66[0] + 4 * gout125[0];
    std::vector<Ciphertext> gout180 = ctx.eval_lut_amortized(&gin180, lut180);

    std::vector<RotationPoly> lut181;
    std::vector<long (*)(long)> flut181;
    auto lut181idx0 = [](long I) -> long {
        /* GATE 336 (LUT3 _1363_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut181.push_back(ctx.genrate_lut(lut181idx0));
    flut181.push_back(lut181idx0);
    auto fvec181 = [flut181](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut181[i](I));
        return ret;
    };

    std::cerr << "\rLUT181   ";
    Ciphertext gin181 = 1 * gout162[0] + 2 * gout161[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout181 = ctx.eval_lut_amortized(&gin181, lut181);

    std::vector<RotationPoly> lut182;
    std::vector<long (*)(long)> flut182;
    auto lut182idx0 = [](long I) -> long {
        /* GATE 360 (LUT3 _1387_ INIT 0x70 PERM 201) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut182.push_back(ctx.genrate_lut(lut182idx0));
    flut182.push_back(lut182idx0);
    auto fvec182 = [flut182](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut182[i](I));
        return ret;
    };

    std::cerr << "\rLUT182   ";
    Ciphertext gin182 = 1 * ct_my_string40 + 2 * gout178[0] + 4 * gout36[0];
    std::vector<Ciphertext> gout182 = ctx.eval_lut_amortized(&gin182, lut182);

    std::vector<RotationPoly> lut183;
    std::vector<long (*)(long)> flut183;
    auto lut183idx0 = [](long I) -> long {
        /* GATE 132 (LUT3 _1159_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut183.push_back(ctx.genrate_lut(lut183idx0));
    flut183.push_back(lut183idx0);
    auto fvec183 = [flut183](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut183[i](I));
        return ret;
    };

    std::cerr << "\rLUT183   ";
    Ciphertext gin183 = 1 * ct_my_string8 + 2 * gout106[0] + 4 * ct_my_string0;
    std::vector<Ciphertext> gout183 = ctx.eval_lut_amortized(&gin183, lut183);

    std::vector<RotationPoly> lut184;
    std::vector<long (*)(long)> flut184;
    auto lut184idx0 = [](long I) -> long {
        /* GATE 275 (LUT3 _1302_ INIT 0xca PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut184.push_back(ctx.genrate_lut(lut184idx0));
    flut184.push_back(lut184idx0);
    auto fvec184 = [flut184](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut184[i](I));
        return ret;
    };

    std::cerr << "\rLUT184   ";
    Ciphertext gin184 = 1 * ct_my_string33 + 2 * gout167[0] + 4 * ct_my_string1;
    std::vector<Ciphertext> gout184 = ctx.eval_lut_amortized(&gin184, lut184);

    std::vector<RotationPoly> lut185;
    std::vector<long (*)(long)> flut185;
    auto lut185idx0 = [](long I) -> long {
        /* GATE 78 (LUT3 _1105_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut185.push_back(ctx.genrate_lut(lut185idx0));
    flut185.push_back(lut185idx0);
    auto fvec185 = [flut185](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut185[i](I));
        return ret;
    };

    std::cerr << "\rLUT185   ";
    Ciphertext gin185 = 1 * gout119[1] + 2 * ct_my_string50 + 4 * gout76[0];
    std::vector<Ciphertext> gout185 = ctx.eval_lut_amortized(&gin185, lut185);

    std::vector<RotationPoly> lut186;
    std::vector<long (*)(long)> flut186;
    auto lut186idx0 = [](long I) -> long {
        /* GATE 73 (LUT2 _1100_ INIT 0x8 PERM 10) */
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
    lut186.push_back(ctx.genrate_lut(lut186idx0));
    flut186.push_back(lut186idx0);
    auto fvec186 = [flut186](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut186[i](I));
        return ret;
    };

    std::cerr << "\rLUT186   ";
    Ciphertext gin186 = 1 * ct_my_string33 + 2 * gout167[0];
    std::vector<Ciphertext> gout186 = ctx.eval_lut_amortized(&gin186, lut186);

    std::vector<RotationPoly> lut187;
    std::vector<long (*)(long)> flut187;
    auto lut187idx0 = [](long I) -> long {
        /* GATE 64 (LUT3 _1091_ INIT 0x70 PERM 210) */
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
    lut187.push_back(ctx.genrate_lut(lut187idx0));
    flut187.push_back(lut187idx0);
    auto fvec187 = [flut187](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut187[i](I));
        return ret;
    };

    std::cerr << "\rLUT187   ";
    Ciphertext gin187 = 1 * gout109[0] + 2 * gout106[1] + 4 * ct_my_string40;
    std::vector<Ciphertext> gout187 = ctx.eval_lut_amortized(&gin187, lut187);

    std::vector<RotationPoly> lut188;
    std::vector<long (*)(long)> flut188;
    auto lut188idx0 = [](long I) -> long {
        /* GATE 352 (LUT3 _1379_ INIT 0x70 PERM 201) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut188.push_back(ctx.genrate_lut(lut188idx0));
    flut188.push_back(lut188idx0);
    auto fvec188 = [flut188](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut188[i](I));
        return ret;
    };

    std::cerr << "\rLUT188   ";
    Ciphertext gin188 = 1 * gout156[0] + 2 * gout138[0] + 4 * gout54[0];
    std::vector<Ciphertext> gout188 = ctx.eval_lut_amortized(&gin188, lut188);

    std::vector<RotationPoly> lut189;
    std::vector<long (*)(long)> flut189;
    auto lut189idx0 = [](long I) -> long {
        /* GATE 355 (LUT3 _1382_ INIT 0x70 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut189.push_back(ctx.genrate_lut(lut189idx0));
    flut189.push_back(lut189idx0);
    auto fvec189 = [flut189](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut189[i](I));
        return ret;
    };

    std::cerr << "\rLUT189   ";
    Ciphertext gin189 = 1 * gout54[0] + 2 * gout115[0] + 4 * gout160[0];
    std::vector<Ciphertext> gout189 = ctx.eval_lut_amortized(&gin189, lut189);

    std::vector<RotationPoly> lut190;
    std::vector<long (*)(long)> flut190;
    auto lut190idx0 = [](long I) -> long {
        /* GATE 221 (LUT2 _1248_ INIT 0x8 PERM 10) */
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
    lut190.push_back(ctx.genrate_lut(lut190idx0));
    flut190.push_back(lut190idx0);
    auto fvec190 = [flut190](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut190[i](I));
        return ret;
    };

    std::cerr << "\rLUT190   ";
    Ciphertext gin190 = 1 * ct_my_string29 + 2 * gout106[1];
    std::vector<Ciphertext> gout190 = ctx.eval_lut_amortized(&gin190, lut190);

    std::vector<RotationPoly> lut191;
    std::vector<long (*)(long)> flut191;
    auto lut191idx0 = [](long I) -> long {
        /* GATE 361 (LUT3 _1388_ INIT 0x70 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut191.push_back(ctx.genrate_lut(lut191idx0));
    flut191.push_back(lut191idx0);
    auto fvec191 = [flut191](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut191[i](I));
        return ret;
    };

    std::cerr << "\rLUT191   ";
    Ciphertext gin191 = 1 * gout76[0] + 2 * ct_my_string32 + 4 * gout182[0];
    std::vector<Ciphertext> gout191 = ctx.eval_lut_amortized(&gin191, lut191);

    std::vector<RotationPoly> lut192;
    std::vector<long (*)(long)> flut192;
    auto lut192idx0 = [](long I) -> long {
        /* GATE 226 (LUT3 _1253_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut192.push_back(ctx.genrate_lut(lut192idx0));
    flut192.push_back(lut192idx0);
    auto fvec192 = [flut192](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut192[i](I));
        return ret;
    };

    std::cerr << "\rLUT192   ";
    Ciphertext gin192 = 1 * gout136[0] + 2 * ct_my_string38 + 4 * gout76[0];
    std::vector<Ciphertext> gout192 = ctx.eval_lut_amortized(&gin192, lut192);

    std::vector<RotationPoly> lut193;
    std::vector<long (*)(long)> flut193;
    auto lut193idx0 = [](long I) -> long {
        /* GATE 196 (LUT3 _1223_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut193.push_back(ctx.genrate_lut(lut193idx0));
    flut193.push_back(lut193idx0);
    auto fvec193 = [flut193](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut193[i](I));
        return ret;
    };

    std::cerr << "\rLUT193   ";
    Ciphertext gin193 = 1 * gout171[0] + 2 * ct_my_string33 + 4 * gout76[0];
    std::vector<Ciphertext> gout193 = ctx.eval_lut_amortized(&gin193, lut193);

    std::vector<RotationPoly> lut194;
    std::vector<long (*)(long)> flut194;
    auto lut194idx0 = [](long I) -> long {
        /* GATE 210 (LUT2 _1237_ INIT 0x8 PERM 10) */
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
    lut194.push_back(ctx.genrate_lut(lut194idx0));
    flut194.push_back(lut194idx0);
    auto fvec194 = [flut194](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut194[i](I));
        return ret;
    };

    std::cerr << "\rLUT194   ";
    Ciphertext gin194 = 1 * ct_my_string27 + 2 * gout106[1];
    std::vector<Ciphertext> gout194 = ctx.eval_lut_amortized(&gin194, lut194);

    std::vector<RotationPoly> lut195;
    std::vector<long (*)(long)> flut195;
    auto lut195idx0 = [](long I) -> long {
        /* GATE 258 (LUT3 _1285_ INIT 0x3a PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut195.push_back(ctx.genrate_lut(lut195idx0));
    flut195.push_back(lut195idx0);
    auto fvec195 = [flut195](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut195[i](I));
        return ret;
    };

    std::cerr << "\rLUT195   ";
    Ciphertext gin195 = 1 * gout122[0] + 2 * gout167[0] + 4 * gout148[0];
    std::vector<Ciphertext> gout195 = ctx.eval_lut_amortized(&gin195, lut195);

    std::vector<RotationPoly> lut196;
    std::vector<long (*)(long)> flut196;
    auto lut196idx0 = [](long I) -> long {
        /* GATE 201 (LUT3 _1228_ INIT 0x8f PERM 210) */
        switch (I) {
            case  0: return 1;
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
    lut196.push_back(ctx.genrate_lut(lut196idx0));
    flut196.push_back(lut196idx0);
    auto fvec196 = [flut196](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut196[i](I));
        return ret;
    };

    std::cerr << "\rLUT196   ";
    Ciphertext gin196 = 1 * gout175[0] + 2 * ct_my_string42 + 4 * gout56[1];
    std::vector<Ciphertext> gout196 = ctx.eval_lut_amortized(&gin196, lut196);

    std::vector<RotationPoly> lut197;
    std::vector<long (*)(long)> flut197;
    auto lut197idx0 = [](long I) -> long {
        /* GATE 214 (LUT3 _1241_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut197.push_back(ctx.genrate_lut(lut197idx0));
    flut197.push_back(lut197idx0);
    auto fvec197 = [flut197](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut197[i](I));
        return ret;
    };

    std::cerr << "\rLUT197   ";
    Ciphertext gin197 = 1 * gout176[0] + 2 * ct_my_string36 + 4 * gout76[0];
    std::vector<Ciphertext> gout197 = ctx.eval_lut_amortized(&gin197, lut197);

    std::vector<RotationPoly> lut198;
    std::vector<long (*)(long)> flut198;
    auto lut198idx0 = [](long I) -> long {
        /* GATE 350 (LUT3 _1377_ INIT 0x70 PERM 201) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut198.push_back(ctx.genrate_lut(lut198idx0));
    flut198.push_back(lut198idx0);
    auto fvec198 = [flut198](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut198[i](I));
        return ret;
    };

    std::cerr << "\rLUT198   ";
    Ciphertext gin198 = 1 * gout83[0] + 2 * gout163[0] + 4 * gout54[0];
    std::vector<Ciphertext> gout198 = ctx.eval_lut_amortized(&gin198, lut198);

    std::vector<RotationPoly> lut199;
    std::vector<long (*)(long)> flut199;
    auto lut199idx0 = [](long I) -> long {
        /* GATE 81 (LUT3 _1108_ INIT 0x70 PERM 120) */
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
    lut199.push_back(ctx.genrate_lut(lut199idx0));
    flut199.push_back(lut199idx0);
    auto fvec199 = [flut199](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut199[i](I));
        return ret;
    };

    std::cerr << "\rLUT199   ";
    Ciphertext gin199 = 1 * gout114[0] + 2 * ct_my_string58 + 4 * gout56[1];
    std::vector<Ciphertext> gout199 = ctx.eval_lut_amortized(&gin199, lut199);

    std::vector<RotationPoly> lut200;
    std::vector<long (*)(long)> flut200;
    auto lut200idx0 = [](long I) -> long {
        /* GATE 92 (LUT3 _1119_ INIT 0x40 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut200.push_back(ctx.genrate_lut(lut200idx0));
    flut200.push_back(lut200idx0);
    auto fvec200 = [flut200](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut200[i](I));
        return ret;
    };

    std::cerr << "\rLUT200   ";
    Ciphertext gin200 = 1 * gout112[1] + 2 * gout142[0] + 4 * gout113[0];
    std::vector<Ciphertext> gout200 = ctx.eval_lut_amortized(&gin200, lut200);

    std::vector<RotationPoly> lut201;
    std::vector<long (*)(long)> flut201;
    auto lut201idx0 = [](long I) -> long {
        /* GATE 199 (LUT3 _1226_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut201.push_back(ctx.genrate_lut(lut201idx0));
    flut201.push_back(lut201idx0);
    auto fvec201 = [flut201](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut201[i](I));
        return ret;
    };

    std::cerr << "\rLUT201   ";
    Ciphertext gin201 = 1 * ct_my_string17 + 2 * gout76[1] + 4 * ct_my_string1;
    std::vector<Ciphertext> gout201 = ctx.eval_lut_amortized(&gin201, lut201);

    std::vector<RotationPoly> lut202;
    std::vector<long (*)(long)> flut202;
    auto lut202idx0 = [](long I) -> long {
        /* GATE 72 (LUT3 _1099_ INIT 0x7 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut202.push_back(ctx.genrate_lut(lut202idx0));
    flut202.push_back(lut202idx0);
    auto fvec202 = [flut202](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut202[i](I));
        return ret;
    };

    std::cerr << "\rLUT202   ";
    Ciphertext gin202 = 1 * ct_my_string49 + 2 * gout186[0] + 4 * gout76[0];
    std::vector<Ciphertext> gout202 = ctx.eval_lut_amortized(&gin202, lut202);

    std::vector<RotationPoly> lut203;
    std::vector<long (*)(long)> flut203;
    auto lut203idx0 = [](long I) -> long {
        /* GATE 279 (LUT3 _1306_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut203.push_back(ctx.genrate_lut(lut203idx0));
    flut203.push_back(lut203idx0);
    auto lut203idx1 = [](long I) -> long {
        /* GATE 84 (LUT2 _1111_ INIT 0x8 PERM 10) */
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
    lut203.push_back(ctx.genrate_lut(lut203idx1));
    flut203.push_back(lut203idx1);
    auto fvec203 = [flut203](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut203[i](I));
        return ret;
    };

    std::cerr << "\rLUT203   ";
    Ciphertext gin203 = 1 * ct_my_string34 + 2 * gout167[0] + 4 * ct_my_string2;
    std::vector<Ciphertext> gout203 = ctx.eval_lut_amortized(&gin203, lut203);

    std::vector<RotationPoly> lut204;
    std::vector<long (*)(long)> flut204;
    auto lut204idx0 = [](long I) -> long {
        /* GATE 232 (LUT3 _1259_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut204.push_back(ctx.genrate_lut(lut204idx0));
    flut204.push_back(lut204idx0);
    auto fvec204 = [flut204](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut204[i](I));
        return ret;
    };

    std::cerr << "\rLUT204   ";
    Ciphertext gin204 = 1 * gout129[0] + 2 * ct_my_string39 + 4 * gout76[0];
    std::vector<Ciphertext> gout204 = ctx.eval_lut_amortized(&gin204, lut204);

    std::vector<RotationPoly> lut205;
    std::vector<long (*)(long)> flut205;
    auto lut205idx0 = [](long I) -> long {
        /* GATE 120 (LUT3 _1147_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut205.push_back(ctx.genrate_lut(lut205idx0));
    flut205.push_back(lut205idx0);
    auto fvec205 = [flut205](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut205[i](I));
        return ret;
    };

    std::cerr << "\rLUT205   ";
    Ciphertext gin205 = 1 * gout123[1] + 2 * ct_my_string23 + 4 * gout76[1];
    std::vector<Ciphertext> gout205 = ctx.eval_lut_amortized(&gin205, lut205);

    std::vector<RotationPoly> lut206;
    std::vector<long (*)(long)> flut206;
    auto lut206idx0 = [](long I) -> long {
        /* GATE 204 (LUT3 _1231_ INIT 0xca PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut206.push_back(ctx.genrate_lut(lut206idx0));
    flut206.push_back(lut206idx0);
    auto fvec206 = [flut206](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut206[i](I));
        return ret;
    };

    std::cerr << "\rLUT206   ";
    Ciphertext gin206 = 1 * gout119[0] + 2 * gout66[0] + 4 * gout155[0];
    std::vector<Ciphertext> gout206 = ctx.eval_lut_amortized(&gin206, lut206);

    std::vector<RotationPoly> lut207;
    std::vector<long (*)(long)> flut207;
    auto lut207idx0 = [](long I) -> long {
        /* GATE 287 (LUT3 _1314_ INIT 0xca PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut207.push_back(ctx.genrate_lut(lut207idx0));
    flut207.push_back(lut207idx0);
    auto fvec207 = [flut207](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut207[i](I));
        return ret;
    };

    std::cerr << "\rLUT207   ";
    Ciphertext gin207 = 1 * ct_my_string36 + 2 * gout167[0] + 4 * ct_my_string4;
    std::vector<Ciphertext> gout207 = ctx.eval_lut_amortized(&gin207, lut207);

    std::vector<RotationPoly> lut208;
    std::vector<long (*)(long)> flut208;
    auto lut208idx0 = [](long I) -> long {
        /* GATE 274 (LUT3 _1301_ INIT 0x3a PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut208.push_back(ctx.genrate_lut(lut208idx0));
    flut208.push_back(lut208idx0);
    auto fvec208 = [flut208](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut208[i](I));
        return ret;
    };

    std::cerr << "\rLUT208   ";
    Ciphertext gin208 = 1 * gout184[0] + 2 * gout106[1] + 4 * gout137[0];
    std::vector<Ciphertext> gout208 = ctx.eval_lut_amortized(&gin208, lut208);

    std::vector<RotationPoly> lut209;
    std::vector<long (*)(long)> flut209;
    auto lut209idx0 = [](long I) -> long {
        /* GATE 363 (LUT3 _1390_ INIT 0x70 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut209.push_back(ctx.genrate_lut(lut209idx0));
    flut209.push_back(lut209idx0);
    auto fvec209 = [flut209](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut209[i](I));
        return ret;
    };

    std::cerr << "\rLUT209   ";
    Ciphertext gin209 = 1 * gout36[0] + 2 * ct_my_string44 + 4 * gout197[0];
    std::vector<Ciphertext> gout209 = ctx.eval_lut_amortized(&gin209, lut209);

    std::vector<RotationPoly> lut210;
    std::vector<long (*)(long)> flut210;
    auto lut210idx0 = [](long I) -> long {
        /* GATE 220 (LUT3 _1247_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut210.push_back(ctx.genrate_lut(lut210idx0));
    flut210.push_back(lut210idx0);
    auto fvec210 = [flut210](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut210[i](I));
        return ret;
    };

    std::cerr << "\rLUT210   ";
    Ciphertext gin210 = 1 * gout190[0] + 2 * ct_my_string37 + 4 * gout76[0];
    std::vector<Ciphertext> gout210 = ctx.eval_lut_amortized(&gin210, lut210);

    std::vector<RotationPoly> lut211;
    std::vector<long (*)(long)> flut211;
    auto lut211idx0 = [](long I) -> long {
        /* GATE 140 (LUT2 _1167_ INIT 0x8 PERM 10) */
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
    lut211.push_back(ctx.genrate_lut(lut211idx0));
    flut211.push_back(lut211idx0);
    auto fvec211 = [flut211](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut211[i](I));
        return ret;
    };

    std::cerr << "\rLUT211   ";
    Ciphertext gin211 = 1 * ct_my_string25 + 2 * gout167[0];
    std::vector<Ciphertext> gout211 = ctx.eval_lut_amortized(&gin211, lut211);

    std::vector<RotationPoly> lut212;
    std::vector<long (*)(long)> flut212;
    auto lut212idx0 = [](long I) -> long {
        /* GATE 200 (LUT3 _1227_ INIT 0xf1 PERM 120) */
        switch (I) {
            case  0: return 1;
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
    lut212.push_back(ctx.genrate_lut(lut212idx0));
    flut212.push_back(lut212idx0);
    auto fvec212 = [flut212](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut212[i](I));
        return ret;
    };

    std::cerr << "\rLUT212   ";
    Ciphertext gin212 = 1 * gout196[0] + 2 * gout206[0] + 4 * gout48[0];
    std::vector<Ciphertext> gout212 = ctx.eval_lut_amortized(&gin212, lut212);

    std::vector<RotationPoly> lut213;
    std::vector<long (*)(long)> flut213;
    auto lut213idx0 = [](long I) -> long {
        /* GATE 209 (LUT3 _1236_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut213.push_back(ctx.genrate_lut(lut213idx0));
    flut213.push_back(lut213idx0);
    auto fvec213 = [flut213](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut213[i](I));
        return ret;
    };

    std::cerr << "\rLUT213   ";
    Ciphertext gin213 = 1 * gout194[0] + 2 * ct_my_string35 + 4 * gout76[0];
    std::vector<Ciphertext> gout213 = ctx.eval_lut_amortized(&gin213, lut213);

    std::vector<RotationPoly> lut214;
    std::vector<long (*)(long)> flut214;
    auto lut214idx0 = [](long I) -> long {
        /* GATE 291 (LUT3 _1318_ INIT 0xca PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut214.push_back(ctx.genrate_lut(lut214idx0));
    flut214.push_back(lut214idx0);
    auto fvec214 = [flut214](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut214[i](I));
        return ret;
    };

    std::cerr << "\rLUT214   ";
    Ciphertext gin214 = 1 * ct_my_string37 + 2 * gout167[0] + 4 * ct_my_string5;
    std::vector<Ciphertext> gout214 = ctx.eval_lut_amortized(&gin214, lut214);

    std::vector<RotationPoly> lut215;
    std::vector<long (*)(long)> flut215;
    auto lut215idx0 = [](long I) -> long {
        /* GATE 129 (LUT2 _1156_ INIT 0x8 PERM 10) */
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
    lut215.push_back(ctx.genrate_lut(lut215idx0));
    flut215.push_back(lut215idx0);
    auto fvec215 = [flut215](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut215[i](I));
        return ret;
    };

    std::cerr << "\rLUT215   ";
    Ciphertext gin215 = 1 * ct_my_string24 + 2 * gout167[0];
    std::vector<Ciphertext> gout215 = ctx.eval_lut_amortized(&gin215, lut215);

    std::vector<RotationPoly> lut216;
    std::vector<long (*)(long)> flut216;
    auto lut216idx0 = [](long I) -> long {
        /* GATE 278 (LUT3 _1305_ INIT 0xca PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut216.push_back(ctx.genrate_lut(lut216idx0));
    flut216.push_back(lut216idx0);
    auto fvec216 = [flut216](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut216[i](I));
        return ret;
    };

    std::cerr << "\rLUT216   ";
    Ciphertext gin216 = 1 * gout203[0] + 2 * gout106[1] + 4 * gout155[0];
    std::vector<Ciphertext> gout216 = ctx.eval_lut_amortized(&gin216, lut216);

    std::vector<RotationPoly> lut217;
    std::vector<long (*)(long)> flut217;
    auto lut217idx0 = [](long I) -> long {
        /* GATE 234 (LUT3 _1261_ INIT 0xca PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut217.push_back(ctx.genrate_lut(lut217idx0));
    flut217.push_back(lut217idx0);
    auto fvec217 = [flut217](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut217[i](I));
        return ret;
    };

    std::cerr << "\rLUT217   ";
    Ciphertext gin217 = 1 * gout103[0] + 2 * gout66[0] + 4 * gout123[0];
    std::vector<Ciphertext> gout217 = ctx.eval_lut_amortized(&gin217, lut217);

    std::vector<RotationPoly> lut218;
    std::vector<long (*)(long)> flut218;
    auto lut218idx0 = [](long I) -> long {
        /* GATE 262 (LUT3 _1289_ INIT 0xca PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut218.push_back(ctx.genrate_lut(lut218idx0));
    flut218.push_back(lut218idx0);
    auto fvec218 = [flut218](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut218[i](I));
        return ret;
    };

    std::cerr << "\rLUT218   ";
    Ciphertext gin218 = 1 * gout74[0] + 2 * gout167[0] + 4 * gout161[0];
    std::vector<Ciphertext> gout218 = ctx.eval_lut_amortized(&gin218, lut218);

    std::vector<RotationPoly> lut219;
    std::vector<long (*)(long)> flut219;
    auto lut219idx0 = [](long I) -> long {
        /* GATE 271 (LUT3 _1298_ INIT 0xca PERM 210) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut219.push_back(ctx.genrate_lut(lut219idx0));
    flut219.push_back(lut219idx0);
    auto lut219idx1 = [](long I) -> long {
        /* GATE 60 (LUT2 _1087_ INIT 0x8 PERM 02) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut219.push_back(ctx.genrate_lut(lut219idx1));
    flut219.push_back(lut219idx1);
    auto fvec219 = [flut219](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut219[i](I));
        return ret;
    };

    std::cerr << "\rLUT219   ";
    Ciphertext gin219 = 1 * gout167[0] + 2 * ct_my_string0 + 4 * ct_my_string32;
    std::vector<Ciphertext> gout219 = ctx.eval_lut_amortized(&gin219, lut219);

    std::vector<RotationPoly> lut220;
    std::vector<long (*)(long)> flut220;
    auto lut220idx0 = [](long I) -> long {
        /* GATE 80 (LUT3 _1107_ INIT 0x70 PERM 120) */
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
    lut220.push_back(ctx.genrate_lut(lut220idx0));
    flut220.push_back(lut220idx0);
    auto fvec220 = [flut220](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut220[i](I));
        return ret;
    };

    std::cerr << "\rLUT220   ";
    Ciphertext gin220 = 1 * gout199[0] + 2 * ct_my_string10 + 4 * gout106[0];
    std::vector<Ciphertext> gout220 = ctx.eval_lut_amortized(&gin220, lut220);

    std::vector<RotationPoly> lut221;
    std::vector<long (*)(long)> flut221;
    auto lut221idx0 = [](long I) -> long {
        /* GATE 83 (LUT3 _1110_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut221.push_back(ctx.genrate_lut(lut221idx0));
    flut221.push_back(lut221idx0);
    auto fvec221 = [flut221](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut221[i](I));
        return ret;
    };

    std::cerr << "\rLUT221   ";
    Ciphertext gin221 = 1 * gout203[1] + 2 * ct_my_string42 + 4 * gout106[1];
    std::vector<Ciphertext> gout221 = ctx.eval_lut_amortized(&gin221, lut221);

    std::vector<RotationPoly> lut222;
    std::vector<long (*)(long)> flut222;
    auto lut222idx0 = [](long I) -> long {
        /* GATE 3 (LUT3 _1030_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut222.push_back(ctx.genrate_lut(lut222idx0));
    flut222.push_back(lut222idx0);
    auto fvec222 = [flut222](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut222[i](I));
        return ret;
    };

    std::cerr << "\rLUT222   ";
    Ciphertext gin222 = 1 * gout168[0] + 2 * ct_my_string16 + 4 * gout76[1];
    std::vector<Ciphertext> gout222 = ctx.eval_lut_amortized(&gin222, lut222);

    std::vector<RotationPoly> lut223;
    std::vector<long (*)(long)> flut223;
    auto lut223idx0 = [](long I) -> long {
        /* GATE 304 (LUT3 _1331_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut223.push_back(ctx.genrate_lut(lut223idx0));
    flut223.push_back(lut223idx0);
    auto fvec223 = [flut223](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut223[i](I));
        return ret;
    };

    std::cerr << "\rLUT223   ";
    Ciphertext gin223 = 1 * gout110[0] + 2 * gout137[0] + 4 * gout76[0];
    std::vector<Ciphertext> gout223 = ctx.eval_lut_amortized(&gin223, lut223);

    std::vector<RotationPoly> lut224;
    std::vector<long (*)(long)> flut224;
    auto lut224idx0 = [](long I) -> long {
        /* GATE 307 (LUT3 _1334_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut224.push_back(ctx.genrate_lut(lut224idx0));
    flut224.push_back(lut224idx0);
    auto fvec224 = [flut224](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut224[i](I));
        return ret;
    };

    std::cerr << "\rLUT224   ";
    Ciphertext gin224 = 1 * gout111[0] + 2 * gout155[0] + 4 * gout76[0];
    std::vector<Ciphertext> gout224 = ctx.eval_lut_amortized(&gin224, lut224);

    std::vector<RotationPoly> lut225;
    std::vector<long (*)(long)> flut225;
    auto lut225idx0 = [](long I) -> long {
        /* GATE 246 (LUT3 _1273_ INIT 0xca PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut225.push_back(ctx.genrate_lut(lut225idx0));
    flut225.push_back(lut225idx0);
    auto fvec225 = [flut225](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut225[i](I));
        return ret;
    };

    std::cerr << "\rLUT225   ";
    Ciphertext gin225 = 1 * gout82[0] + 2 * gout167[0] + 4 * gout155[0];
    std::vector<Ciphertext> gout225 = ctx.eval_lut_amortized(&gin225, lut225);

    std::vector<RotationPoly> lut226;
    std::vector<long (*)(long)> flut226;
    auto lut226idx0 = [](long I) -> long {
        /* GATE 310 (LUT3 _1337_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut226.push_back(ctx.genrate_lut(lut226idx0));
    flut226.push_back(lut226idx0);
    auto fvec226 = [flut226](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut226[i](I));
        return ret;
    };

    std::cerr << "\rLUT226   ";
    Ciphertext gin226 = 1 * gout158[0] + 2 * gout125[0] + 4 * gout76[0];
    std::vector<Ciphertext> gout226 = ctx.eval_lut_amortized(&gin226, lut226);

    std::vector<RotationPoly> lut227;
    std::vector<long (*)(long)> flut227;
    auto lut227idx0 = [](long I) -> long {
        /* GATE 228 (LUT3 _1255_ INIT 0xca PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut227.push_back(ctx.genrate_lut(lut227idx0));
    flut227.push_back(lut227idx0);
    auto fvec227 = [flut227](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut227[i](I));
        return ret;
    };

    std::cerr << "\rLUT227   ";
    Ciphertext gin227 = 1 * gout107[0] + 2 * gout66[0] + 4 * gout161[0];
    std::vector<Ciphertext> gout227 = ctx.eval_lut_amortized(&gin227, lut227);

    std::vector<RotationPoly> lut228;
    std::vector<long (*)(long)> flut228;
    auto lut228idx0 = [](long I) -> long {
        /* GATE 283 (LUT3 _1310_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut228.push_back(ctx.genrate_lut(lut228idx0));
    flut228.push_back(lut228idx0);
    auto lut228idx1 = [](long I) -> long {
        /* GATE 87 (LUT2 _1114_ INIT 0x8 PERM 10) */
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
    lut228.push_back(ctx.genrate_lut(lut228idx1));
    flut228.push_back(lut228idx1);
    auto fvec228 = [flut228](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut228[i](I));
        return ret;
    };

    std::cerr << "\rLUT228   ";
    Ciphertext gin228 = 1 * ct_my_string35 + 2 * gout167[0] + 4 * ct_my_string3;
    std::vector<Ciphertext> gout228 = ctx.eval_lut_amortized(&gin228, lut228);

    std::vector<RotationPoly> lut229;
    std::vector<long (*)(long)> flut229;
    auto lut229idx0 = [](long I) -> long {
        /* GATE 301 (LUT3 _1328_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut229.push_back(ctx.genrate_lut(lut229idx0));
    flut229.push_back(lut229idx0);
    auto fvec229 = [flut229](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut229[i](I));
        return ret;
    };

    std::cerr << "\rLUT229   ";
    Ciphertext gin229 = 1 * gout108[0] + 2 * gout183[0] + 4 * gout76[0];
    std::vector<Ciphertext> gout229 = ctx.eval_lut_amortized(&gin229, lut229);

    std::vector<RotationPoly> lut230;
    std::vector<long (*)(long)> flut230;
    auto lut230idx0 = [](long I) -> long {
        /* GATE 231 (LUT3 _1258_ INIT 0x8f PERM 210) */
        switch (I) {
            case  0: return 1;
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
    lut230.push_back(ctx.genrate_lut(lut230idx0));
    flut230.push_back(lut230idx0);
    auto fvec230 = [flut230](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut230[i](I));
        return ret;
    };

    std::cerr << "\rLUT230   ";
    Ciphertext gin230 = 1 * gout204[0] + 2 * ct_my_string47 + 4 * gout56[1];
    std::vector<Ciphertext> gout230 = ctx.eval_lut_amortized(&gin230, lut230);

    std::vector<RotationPoly> lut231;
    std::vector<long (*)(long)> flut231;
    auto lut231idx0 = [](long I) -> long {
        /* GATE 266 (LUT3 _1293_ INIT 0x3a PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut231.push_back(ctx.genrate_lut(lut231idx0));
    flut231.push_back(lut231idx0);
    auto fvec231 = [flut231](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut231[i](I));
        return ret;
    };

    std::cerr << "\rLUT231   ";
    Ciphertext gin231 = 1 * gout98[0] + 2 * gout167[0] + 4 * gout123[0];
    std::vector<Ciphertext> gout231 = ctx.eval_lut_amortized(&gin231, lut231);

    std::vector<RotationPoly> lut232;
    std::vector<long (*)(long)> flut232;
    auto lut232idx0 = [](long I) -> long {
        /* GATE 282 (LUT3 _1309_ INIT 0xca PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut232.push_back(ctx.genrate_lut(lut232idx0));
    flut232.push_back(lut232idx0);
    auto fvec232 = [flut232](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut232[i](I));
        return ret;
    };

    std::cerr << "\rLUT232   ";
    Ciphertext gin232 = 1 * gout228[0] + 2 * gout106[1] + 4 * gout125[0];
    std::vector<Ciphertext> gout232 = ctx.eval_lut_amortized(&gin232, lut232);

    std::vector<RotationPoly> lut233;
    std::vector<long (*)(long)> flut233;
    auto lut233idx0 = [](long I) -> long {
        /* GATE 219 (LUT3 _1246_ INIT 0x8f PERM 210) */
        switch (I) {
            case  0: return 1;
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
    lut233.push_back(ctx.genrate_lut(lut233idx0));
    flut233.push_back(lut233idx0);
    auto fvec233 = [flut233](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut233[i](I));
        return ret;
    };

    std::cerr << "\rLUT233   ";
    Ciphertext gin233 = 1 * gout210[0] + 2 * ct_my_string45 + 4 * gout56[1];
    std::vector<Ciphertext> gout233 = ctx.eval_lut_amortized(&gin233, lut233);

    std::vector<RotationPoly> lut234;
    std::vector<long (*)(long)> flut234;
    auto lut234idx0 = [](long I) -> long {
        /* GATE 162 (LUT2 _1189_ INIT 0x8 PERM 10) */
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
    lut234.push_back(ctx.genrate_lut(lut234idx0));
    flut234.push_back(lut234idx0);
    auto fvec234 = [flut234](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut234[i](I));
        return ret;
    };

    std::cerr << "\rLUT234   ";
    Ciphertext gin234 = 1 * ct_my_string28 + 2 * gout167[0];
    std::vector<Ciphertext> gout234 = ctx.eval_lut_amortized(&gin234, lut234);

    std::vector<RotationPoly> lut235;
    std::vector<long (*)(long)> flut235;
    auto lut235idx0 = [](long I) -> long {
        /* GATE 139 (LUT3 _1166_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut235.push_back(ctx.genrate_lut(lut235idx0));
    flut235.push_back(lut235idx0);
    auto fvec235 = [flut235](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut235[i](I));
        return ret;
    };

    std::cerr << "\rLUT235   ";
    Ciphertext gin235 = 1 * gout211[0] + 2 * ct_my_string41 + 4 * gout76[0];
    std::vector<Ciphertext> gout235 = ctx.eval_lut_amortized(&gin235, lut235);

    std::vector<RotationPoly> lut236;
    std::vector<long (*)(long)> flut236;
    auto lut236idx0 = [](long I) -> long {
        /* GATE 86 (LUT3 _1113_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut236.push_back(ctx.genrate_lut(lut236idx0));
    flut236.push_back(lut236idx0);
    auto fvec236 = [flut236](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut236[i](I));
        return ret;
    };

    std::cerr << "\rLUT236   ";
    Ciphertext gin236 = 1 * gout228[1] + 2 * ct_my_string51 + 4 * gout76[0];
    std::vector<Ciphertext> gout236 = ctx.eval_lut_amortized(&gin236, lut236);

    std::vector<RotationPoly> lut237;
    std::vector<long (*)(long)> flut237;
    auto lut237idx0 = [](long I) -> long {
        /* GATE 144 (LUT3 _1171_ INIT 0x70 PERM 120) */
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
    lut237.push_back(ctx.genrate_lut(lut237idx0));
    flut237.push_back(lut237idx0);
    auto fvec237 = [flut237](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut237[i](I));
        return ret;
    };

    std::cerr << "\rLUT237   ";
    Ciphertext gin237 = 1 * gout143[0] + 2 * ct_my_string34 + 4 * gout106[1];
    std::vector<Ciphertext> gout237 = ctx.eval_lut_amortized(&gin237, lut237);

    std::vector<RotationPoly> lut238;
    std::vector<long (*)(long)> flut238;
    auto lut238idx0 = [](long I) -> long {
        /* GATE 299 (LUT3 _1326_ INIT 0xca PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut238.push_back(ctx.genrate_lut(lut238idx0));
    flut238.push_back(lut238idx0);
    auto fvec238 = [flut238](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut238[i](I));
        return ret;
    };

    std::cerr << "\rLUT238   ";
    Ciphertext gin238 = 1 * ct_my_string39 + 2 * gout167[0] + 4 * ct_my_string7;
    std::vector<Ciphertext> gout238 = ctx.eval_lut_amortized(&gin238, lut238);

    std::vector<RotationPoly> lut239;
    std::vector<long (*)(long)> flut239;
    auto lut239idx0 = [](long I) -> long {
        /* GATE 290 (LUT3 _1317_ INIT 0x3a PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut239.push_back(ctx.genrate_lut(lut239idx0));
    flut239.push_back(lut239idx0);
    auto fvec239 = [flut239](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut239[i](I));
        return ret;
    };

    std::cerr << "\rLUT239   ";
    Ciphertext gin239 = 1 * gout214[0] + 2 * gout106[1] + 4 * gout148[0];
    std::vector<Ciphertext> gout239 = ctx.eval_lut_amortized(&gin239, lut239);

    std::vector<RotationPoly> lut240;
    std::vector<long (*)(long)> flut240;
    auto lut240idx0 = [](long I) -> long {
        /* GATE 250 (LUT3 _1277_ INIT 0x3a PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut240.push_back(ctx.genrate_lut(lut240idx0));
    flut240.push_back(lut240idx0);
    auto fvec240 = [flut240](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut240[i](I));
        return ret;
    };

    std::cerr << "\rLUT240   ";
    Ciphertext gin240 = 1 * gout93[0] + 2 * gout167[0] + 4 * gout125[0];
    std::vector<Ciphertext> gout240 = ctx.eval_lut_amortized(&gin240, lut240);

    std::vector<RotationPoly> lut241;
    std::vector<long (*)(long)> flut241;
    auto lut241idx0 = [](long I) -> long {
        /* GATE 134 (LUT2 _1161_ INIT 0x8 PERM 01) */
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
    lut241.push_back(ctx.genrate_lut(lut241idx0));
    flut241.push_back(lut241idx0);
    auto fvec241 = [flut241](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut241[i](I));
        return ret;
    };

    std::cerr << "\rLUT241   ";
    Ciphertext gin241 = 1 * gout135[0] + 2 * gout235[0];
    std::vector<Ciphertext> gout241 = ctx.eval_lut_amortized(&gin241, lut241);

    std::vector<RotationPoly> lut242;
    std::vector<long (*)(long)> flut242;
    auto lut242idx0 = [](long I) -> long {
        /* GATE 149 (LUT2 _1176_ INIT 0x8 PERM 10) */
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
    lut242.push_back(ctx.genrate_lut(lut242idx0));
    flut242.push_back(lut242idx0);
    auto fvec242 = [flut242](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut242[i](I));
        return ret;
    };

    std::cerr << "\rLUT242   ";
    Ciphertext gin242 = 1 * ct_my_string26 + 2 * gout167[0];
    std::vector<Ciphertext> gout242 = ctx.eval_lut_amortized(&gin242, lut242);

    std::vector<RotationPoly> lut243;
    std::vector<long (*)(long)> flut243;
    auto lut243idx0 = [](long I) -> long {
        /* GATE 222 (LUT3 _1249_ INIT 0xca PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut243.push_back(ctx.genrate_lut(lut243idx0));
    flut243.push_back(lut243idx0);
    auto fvec243 = [flut243](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut243[i](I));
        return ret;
    };

    std::cerr << "\rLUT243   ";
    Ciphertext gin243 = 1 * gout126[0] + 2 * gout66[0] + 4 * gout148[0];
    std::vector<Ciphertext> gout243 = ctx.eval_lut_amortized(&gin243, lut243);

    std::vector<RotationPoly> lut244;
    std::vector<long (*)(long)> flut244;
    auto lut244idx0 = [](long I) -> long {
        /* GATE 225 (LUT3 _1252_ INIT 0x8f PERM 210) */
        switch (I) {
            case  0: return 1;
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
    lut244.push_back(ctx.genrate_lut(lut244idx0));
    flut244.push_back(lut244idx0);
    auto fvec244 = [flut244](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut244[i](I));
        return ret;
    };

    std::cerr << "\rLUT244   ";
    Ciphertext gin244 = 1 * gout192[0] + 2 * ct_my_string46 + 4 * gout56[1];
    std::vector<Ciphertext> gout244 = ctx.eval_lut_amortized(&gin244, lut244);

    std::vector<RotationPoly> lut245;
    std::vector<long (*)(long)> flut245;
    auto lut245idx0 = [](long I) -> long {
        /* GATE 230 (LUT3 _1257_ INIT 0xf1 PERM 120) */
        switch (I) {
            case  0: return 1;
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
    lut245.push_back(ctx.genrate_lut(lut245idx0));
    flut245.push_back(lut245idx0);
    auto fvec245 = [flut245](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut245[i](I));
        return ret;
    };

    std::cerr << "\rLUT245   ";
    Ciphertext gin245 = 1 * gout230[0] + 2 * gout217[0] + 4 * gout48[0];
    std::vector<Ciphertext> gout245 = ctx.eval_lut_amortized(&gin245, lut245);

    std::vector<RotationPoly> lut246;
    std::vector<long (*)(long)> flut246;
    auto lut246idx0 = [](long I) -> long {
        /* GATE 306 (LUT3 _1333_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut246.push_back(ctx.genrate_lut(lut246idx0));
    flut246.push_back(lut246idx0);
    auto fvec246 = [flut246](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut246[i](I));
        return ret;
    };

    std::cerr << "\rLUT246   ";
    Ciphertext gin246 = 1 * gout224[0] + 2 * gout206[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout246 = ctx.eval_lut_amortized(&gin246, lut246);

    std::vector<RotationPoly> lut247;
    std::vector<long (*)(long)> flut247;
    auto lut247idx0 = [](long I) -> long {
        /* GATE 245 (LUT3 _1272_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut247.push_back(ctx.genrate_lut(lut247idx0));
    flut247.push_back(lut247idx0);
    auto fvec247 = [flut247](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut247[i](I));
        return ret;
    };

    std::cerr << "\rLUT247   ";
    Ciphertext gin247 = 1 * gout225[0] + 2 * gout206[0] + 4 * gout106[1];
    std::vector<Ciphertext> gout247 = ctx.eval_lut_amortized(&gin247, lut247);

    std::vector<RotationPoly> lut248;
    std::vector<long (*)(long)> flut248;
    auto lut248idx0 = [](long I) -> long {
        /* GATE 312 (LUT3 _1339_ INIT 0x3a PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut248.push_back(ctx.genrate_lut(lut248idx0));
    flut248.push_back(lut248idx0);
    auto fvec248 = [flut248](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut248[i](I));
        return ret;
    };

    std::cerr << "\rLUT248   ";
    Ciphertext gin248 = 1 * gout154[0] + 2 * gout56[1] + 4 * gout133[0];
    std::vector<Ciphertext> gout248 = ctx.eval_lut_amortized(&gin248, lut248);

    std::vector<RotationPoly> lut249;
    std::vector<long (*)(long)> flut249;
    auto lut249idx0 = [](long I) -> long {
        /* GATE 309 (LUT3 _1336_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut249.push_back(ctx.genrate_lut(lut249idx0));
    flut249.push_back(lut249idx0);
    auto fvec249 = [flut249](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut249[i](I));
        return ret;
    };

    std::cerr << "\rLUT249   ";
    Ciphertext gin249 = 1 * gout226[0] + 2 * gout180[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout249 = ctx.eval_lut_amortized(&gin249, lut249);

    std::vector<RotationPoly> lut250;
    std::vector<long (*)(long)> flut250;
    auto lut250idx0 = [](long I) -> long {
        /* GATE 171 (LUT3 _1198_ INIT 0x7 PERM 201) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut250.push_back(ctx.genrate_lut(lut250idx0));
    flut250.push_back(lut250idx0);
    auto fvec250 = [flut250](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut250[i](I));
        return ret;
    };

    std::cerr << "\rLUT250   ";
    Ciphertext gin250 = 1 * gout53[0] + 2 * gout170[0] + 4 * ct_my_string45;
    std::vector<Ciphertext> gout250 = ctx.eval_lut_amortized(&gin250, lut250);

    std::vector<RotationPoly> lut251;
    std::vector<long (*)(long)> flut251;
    auto lut251idx0 = [](long I) -> long {
        /* GATE 328 (LUT3 _1355_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut251.push_back(ctx.genrate_lut(lut251idx0));
    flut251.push_back(lut251idx0);
    auto fvec251 = [flut251](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut251[i](I));
        return ret;
    };

    std::cerr << "\rLUT251   ";
    Ciphertext gin251 = 1 * gout172[0] + 2 * gout155[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout251 = ctx.eval_lut_amortized(&gin251, lut251);

    std::vector<RotationPoly> lut252;
    std::vector<long (*)(long)> flut252;
    auto lut252idx0 = [](long I) -> long {
        /* GATE 179 (LUT3 _1206_ INIT 0x7 PERM 210) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut252.push_back(ctx.genrate_lut(lut252idx0));
    flut252.push_back(lut252idx0);
    auto fvec252 = [flut252](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut252[i](I));
        return ret;
    };

    std::cerr << "\rLUT252   ";
    Ciphertext gin252 = 1 * gout173[0] + 2 * gout53[0] + 4 * ct_my_string46;
    std::vector<Ciphertext> gout252 = ctx.eval_lut_amortized(&gin252, lut252);

    std::vector<RotationPoly> lut253;
    std::vector<long (*)(long)> flut253;
    auto lut253idx0 = [](long I) -> long {
        /* GATE 99 (LUT2 _1126_ INIT 0x8 PERM 10) */
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
    lut253.push_back(ctx.genrate_lut(lut253idx0));
    flut253.push_back(lut253idx0);
    auto fvec253 = [flut253](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut253[i](I));
        return ret;
    };

    std::cerr << "\rLUT253   ";
    Ciphertext gin253 = 1 * ct_my_string36 + 2 * gout167[0];
    std::vector<Ciphertext> gout253 = ctx.eval_lut_amortized(&gin253, lut253);

    std::vector<RotationPoly> lut254;
    std::vector<long (*)(long)> flut254;
    auto lut254idx0 = [](long I) -> long {
        /* GATE 254 (LUT3 _1281_ INIT 0x3a PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut254.push_back(ctx.genrate_lut(lut254idx0));
    flut254.push_back(lut254idx0);
    auto fvec254 = [flut254](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut254[i](I));
        return ret;
    };

    std::cerr << "\rLUT254   ";
    Ciphertext gin254 = 1 * gout79[0] + 2 * gout167[0] + 4 * gout112[0];
    std::vector<Ciphertext> gout254 = ctx.eval_lut_amortized(&gin254, lut254);

    std::vector<RotationPoly> lut255;
    std::vector<long (*)(long)> flut255;
    auto lut255idx0 = [](long I) -> long {
        /* GATE 319 (LUT3 _1346_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut255.push_back(ctx.genrate_lut(lut255idx0));
    flut255.push_back(lut255idx0);
    auto fvec255 = [flut255](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut255[i](I));
        return ret;
    };

    std::cerr << "\rLUT255   ";
    Ciphertext gin255 = 1 * gout141[0] + 2 * gout161[0] + 4 * gout76[0];
    std::vector<Ciphertext> gout255 = ctx.eval_lut_amortized(&gin255, lut255);

    std::vector<RotationPoly> lut256;
    std::vector<long (*)(long)> flut256;
    auto lut256idx0 = [](long I) -> long {
        /* GATE 238 (LUT3 _1265_ INIT 0x3a PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut256.push_back(ctx.genrate_lut(lut256idx0));
    flut256.push_back(lut256idx0);
    auto fvec256 = [flut256](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut256[i](I));
        return ret;
    };

    std::cerr << "\rLUT256   ";
    Ciphertext gin256 = 1 * gout124[0] + 2 * gout167[0] + 4 * gout183[0];
    std::vector<Ciphertext> gout256 = ctx.eval_lut_amortized(&gin256, lut256);

    std::vector<RotationPoly> lut257;
    std::vector<long (*)(long)> flut257;
    auto lut257idx0 = [](long I) -> long {
        /* GATE 249 (LUT3 _1276_ INIT 0x3a PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut257.push_back(ctx.genrate_lut(lut257idx0));
    flut257.push_back(lut257idx0);
    auto fvec257 = [flut257](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut257[i](I));
        return ret;
    };

    std::cerr << "\rLUT257   ";
    Ciphertext gin257 = 1 * gout240[0] + 2 * gout180[0] + 4 * gout106[1];
    std::vector<Ciphertext> gout257 = ctx.eval_lut_amortized(&gin257, lut257);

    std::vector<RotationPoly> lut258;
    std::vector<long (*)(long)> flut258;
    auto lut258idx0 = [](long I) -> long {
        /* GATE 244 (LUT3 _1271_ INIT 0xa3 PERM 012) */
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
    lut258.push_back(ctx.genrate_lut(lut258idx0));
    flut258.push_back(lut258idx0);
    auto fvec258 = [flut258](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut258[i](I));
        return ret;
    };

    std::cerr << "\rLUT258   ";
    Ciphertext gin258 = 1 * ct_my_string34 + 2 * gout247[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout258 = ctx.eval_lut_amortized(&gin258, lut258);

    std::vector<RotationPoly> lut259;
    std::vector<long (*)(long)> flut259;
    auto lut259idx0 = [](long I) -> long {
        /* GATE 188 (LUT2 _1215_ INIT 0x8 PERM 10) */
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
    lut259.push_back(ctx.genrate_lut(lut259idx0));
    flut259.push_back(lut259idx0);
    auto fvec259 = [flut259](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut259[i](I));
        return ret;
    };

    std::cerr << "\rLUT259   ";
    Ciphertext gin259 = 1 * ct_my_string31 + 2 * gout167[0];
    std::vector<Ciphertext> gout259 = ctx.eval_lut_amortized(&gin259, lut259);

    std::vector<RotationPoly> lut260;
    std::vector<long (*)(long)> flut260;
    auto lut260idx0 = [](long I) -> long {
        /* GATE 119 (LUT2 _1146_ INIT 0x8 PERM 10) */
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
    lut260.push_back(ctx.genrate_lut(lut260idx0));
    flut260.push_back(lut260idx0);
    auto fvec260 = [flut260](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut260[i](I));
        return ret;
    };

    std::cerr << "\rLUT260   ";
    Ciphertext gin260 = 1 * ct_my_string39 + 2 * gout167[0];
    std::vector<Ciphertext> gout260 = ctx.eval_lut_amortized(&gin260, lut260);

    std::vector<RotationPoly> lut261;
    std::vector<long (*)(long)> flut261;
    auto lut261idx0 = [](long I) -> long {
        /* GATE 295 (LUT3 _1322_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut261.push_back(ctx.genrate_lut(lut261idx0));
    flut261.push_back(lut261idx0);
    auto lut261idx1 = [](long I) -> long {
        /* GATE 114 (LUT2 _1141_ INIT 0x8 PERM 10) */
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
    lut261.push_back(ctx.genrate_lut(lut261idx1));
    flut261.push_back(lut261idx1);
    auto fvec261 = [flut261](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut261[i](I));
        return ret;
    };

    std::cerr << "\rLUT261   ";
    Ciphertext gin261 = 1 * ct_my_string38 + 2 * gout167[0] + 4 * ct_my_string6;
    std::vector<Ciphertext> gout261 = ctx.eval_lut_amortized(&gin261, lut261);

    std::vector<RotationPoly> lut262;
    std::vector<long (*)(long)> flut262;
    auto lut262idx0 = [](long I) -> long {
        /* GATE 113 (LUT3 _1140_ INIT 0x7 PERM 210) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut262.push_back(ctx.genrate_lut(lut262idx0));
    flut262.push_back(lut262idx0);
    auto fvec262 = [flut262](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut262[i](I));
        return ret;
    };

    std::cerr << "\rLUT262   ";
    Ciphertext gin262 = 1 * gout261[1] + 2 * gout53[0] + 4 * ct_my_string54;
    std::vector<Ciphertext> gout262 = ctx.eval_lut_amortized(&gin262, lut262);

    std::vector<RotationPoly> lut263;
    std::vector<long (*)(long)> flut263;
    auto lut263idx0 = [](long I) -> long {
        /* GATE 156 (LUT2 _1183_ INIT 0x8 PERM 10) */
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
    lut263.push_back(ctx.genrate_lut(lut263idx0));
    flut263.push_back(lut263idx0);
    auto fvec263 = [flut263](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut263[i](I));
        return ret;
    };

    std::cerr << "\rLUT263   ";
    Ciphertext gin263 = 1 * ct_my_string27 + 2 * gout167[0];
    std::vector<Ciphertext> gout263 = ctx.eval_lut_amortized(&gin263, lut263);

    std::vector<RotationPoly> lut264;
    std::vector<long (*)(long)> flut264;
    auto lut264idx0 = [](long I) -> long {
        /* GATE 107 (LUT3 _1134_ INIT 0x70 PERM 120) */
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
    lut264.push_back(ctx.genrate_lut(lut264idx0));
    flut264.push_back(lut264idx0);
    auto fvec264 = [flut264](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut264[i](I));
        return ret;
    };

    std::cerr << "\rLUT264   ";
    Ciphertext gin264 = 1 * gout94[0] + 2 * ct_my_string37 + 4 * gout167[0];
    std::vector<Ciphertext> gout264 = ctx.eval_lut_amortized(&gin264, lut264);

    std::vector<RotationPoly> lut265;
    std::vector<long (*)(long)> flut265;
    auto lut265idx0 = [](long I) -> long {
        /* GATE 324 (LUT3 _1351_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut265.push_back(ctx.genrate_lut(lut265idx0));
    flut265.push_back(lut265idx0);
    auto fvec265 = [flut265](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut265[i](I));
        return ret;
    };

    std::cerr << "\rLUT265   ";
    Ciphertext gin265 = 1 * gout92[0] + 2 * gout183[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout265 = ctx.eval_lut_amortized(&gin265, lut265);

    std::vector<RotationPoly> lut266;
    std::vector<long (*)(long)> flut266;
    auto lut266idx0 = [](long I) -> long {
        /* GATE 242 (LUT3 _1269_ INIT 0x3a PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut266.push_back(ctx.genrate_lut(lut266idx0));
    flut266.push_back(lut266idx0);
    auto fvec266 = [flut266](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut266[i](I));
        return ret;
    };

    std::cerr << "\rLUT266   ";
    Ciphertext gin266 = 1 * gout70[0] + 2 * gout167[0] + 4 * gout137[0];
    std::vector<Ciphertext> gout266 = ctx.eval_lut_amortized(&gin266, lut266);

    std::vector<RotationPoly> lut267;
    std::vector<long (*)(long)> flut267;
    auto lut267idx0 = [](long I) -> long {
        /* GATE 253 (LUT3 _1280_ INIT 0x3a PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut267.push_back(ctx.genrate_lut(lut267idx0));
    flut267.push_back(lut267idx0);
    auto fvec267 = [flut267](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut267[i](I));
        return ret;
    };

    std::cerr << "\rLUT267   ";
    Ciphertext gin267 = 1 * gout254[0] + 2 * gout106[1] + 4 * gout133[0];
    std::vector<Ciphertext> gout267 = ctx.eval_lut_amortized(&gin267, lut267);

    std::vector<RotationPoly> lut268;
    std::vector<long (*)(long)> flut268;
    auto lut268idx0 = [](long I) -> long {
        /* GATE 166 (LUT3 _1193_ INIT 0x40 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut268.push_back(ctx.genrate_lut(lut268idx0));
    flut268.push_back(lut268idx0);
    auto fvec268 = [flut268](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut268[i](I));
        return ret;
    };

    std::cerr << "\rLUT268   ";
    Ciphertext gin268 = 1 * gout144[0] + 2 * gout250[0] + 4 * gout151[0];
    std::vector<Ciphertext> gout268 = ctx.eval_lut_amortized(&gin268, lut268);

    std::vector<RotationPoly> lut269;
    std::vector<long (*)(long)> flut269;
    auto lut269idx0 = [](long I) -> long {
        /* GATE 321 (LUT3 _1348_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut269.push_back(ctx.genrate_lut(lut269idx0));
    flut269.push_back(lut269idx0);
    auto fvec269 = [flut269](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut269[i](I));
        return ret;
    };

    std::cerr << "\rLUT269   ";
    Ciphertext gin269 = 1 * gout152[0] + 2 * gout217[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout269 = ctx.eval_lut_amortized(&gin269, lut269);

    std::vector<RotationPoly> lut270;
    std::vector<long (*)(long)> flut270;
    auto lut270idx0 = [](long I) -> long {
        /* GATE 318 (LUT3 _1345_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut270.push_back(ctx.genrate_lut(lut270idx0));
    flut270.push_back(lut270idx0);
    auto fvec270 = [flut270](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut270[i](I));
        return ret;
    };

    std::cerr << "\rLUT270   ";
    Ciphertext gin270 = 1 * gout255[0] + 2 * gout227[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout270 = ctx.eval_lut_amortized(&gin270, lut270);

    std::vector<RotationPoly> lut271;
    std::vector<long (*)(long)> flut271;
    auto lut271idx0 = [](long I) -> long {
        /* GATE 248 (LUT3 _1275_ INIT 0xac PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut271.push_back(ctx.genrate_lut(lut271idx0));
    flut271.push_back(lut271idx0);
    auto fvec271 = [flut271](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut271[i](I));
        return ret;
    };

    std::cerr << "\rLUT271   ";
    Ciphertext gin271 = 1 * ct_my_string35 + 2 * gout257[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout271 = ctx.eval_lut_amortized(&gin271, lut271);

    std::vector<RotationPoly> lut272;
    std::vector<long (*)(long)> flut272;
    auto lut272idx0 = [](long I) -> long {
        /* GATE 198 (LUT3 _1225_ INIT 0xca PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut272.push_back(ctx.genrate_lut(lut272idx0));
    flut272.push_back(lut272idx0);
    auto fvec272 = [flut272](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut272[i](I));
        return ret;
    };

    std::cerr << "\rLUT272   ";
    Ciphertext gin272 = 1 * gout201[0] + 2 * gout66[0] + 4 * gout137[0];
    std::vector<Ciphertext> gout272 = ctx.eval_lut_amortized(&gin272, lut272);

    std::vector<RotationPoly> lut273;
    std::vector<long (*)(long)> flut273;
    auto lut273idx0 = [](long I) -> long {
        /* GATE 353 (LUT3 _1380_ INIT 0x70 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut273.push_back(ctx.genrate_lut(lut273idx0));
    flut273.push_back(lut273idx0);
    auto fvec273 = [flut273](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut273[i](I));
        return ret;
    };

    std::cerr << "\rLUT273   ";
    Ciphertext gin273 = 1 * gout236[0] + 2 * gout188[0] + 4 * gout41[0];
    std::vector<Ciphertext> gout273 = ctx.eval_lut_amortized(&gin273, lut273);

    std::vector<RotationPoly> lut274;
    std::vector<long (*)(long)> flut274;
    auto lut274idx0 = [](long I) -> long {
        /* GATE 192 (LUT3 _1219_ INIT 0xca PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut274.push_back(ctx.genrate_lut(lut274idx0));
    flut274.push_back(lut274idx0);
    auto fvec274 = [flut274](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut274[i](I));
        return ret;
    };

    std::cerr << "\rLUT274   ";
    Ciphertext gin274 = 1 * gout91[0] + 2 * gout66[0] + 4 * gout183[0];
    std::vector<Ciphertext> gout274 = ctx.eval_lut_amortized(&gin274, lut274);

    std::vector<RotationPoly> lut275;
    std::vector<long (*)(long)> flut275;
    auto lut275idx0 = [](long I) -> long {
        /* GATE 362 (LUT3 _1389_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut275.push_back(ctx.genrate_lut(lut275idx0));
    flut275.push_back(lut275idx0);
    auto fvec275 = [flut275](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut275[i](I));
        return ret;
    };

    std::cerr << "\rLUT275   ";
    Ciphertext gin275 = 1 * gout274[0] + 2 * gout191[0] + 4 * gout48[0];
    std::vector<Ciphertext> gout275 = ctx.eval_lut_amortized(&gin275, lut275);

    std::vector<RotationPoly> lut276;
    std::vector<long (*)(long)> flut276;
    auto lut276idx0 = [](long I) -> long {
        /* GATE 118 (LUT3 _1145_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut276.push_back(ctx.genrate_lut(lut276idx0));
    flut276.push_back(lut276idx0);
    auto fvec276 = [flut276](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut276[i](I));
        return ret;
    };

    std::cerr << "\rLUT276   ";
    Ciphertext gin276 = 1 * gout260[0] + 2 * ct_my_string55 + 4 * gout76[0];
    std::vector<Ciphertext> gout276 = ctx.eval_lut_amortized(&gin276, lut276);

    std::vector<RotationPoly> lut277;
    std::vector<long (*)(long)> flut277;
    auto lut277idx0 = [](long I) -> long {
        /* GATE 207 (LUT3 _1234_ INIT 0x40 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut277.push_back(ctx.genrate_lut(lut277idx0));
    flut277.push_back(lut277idx0);
    auto fvec277 = [flut277](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut277[i](I));
        return ret;
    };

    std::cerr << "\rLUT277   ";
    Ciphertext gin277 = 1 * gout131[0] + 2 * gout213[0] + 4 * gout117[0];
    std::vector<Ciphertext> gout277 = ctx.eval_lut_amortized(&gin277, lut277);

    std::vector<RotationPoly> lut278;
    std::vector<long (*)(long)> flut278;
    auto lut278idx0 = [](long I) -> long {
        /* GATE 176 (LUT3 _1203_ INIT 0x40 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut278.push_back(ctx.genrate_lut(lut278idx0));
    flut278.push_back(lut278idx0);
    auto fvec278 = [flut278](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut278[i](I));
        return ret;
    };

    std::cerr << "\rLUT278   ";
    Ciphertext gin278 = 1 * gout145[0] + 2 * gout252[0] + 4 * gout164[0];
    std::vector<Ciphertext> gout278 = ctx.eval_lut_amortized(&gin278, lut278);

    std::vector<RotationPoly> lut279;
    std::vector<long (*)(long)> flut279;
    auto lut279idx0 = [](long I) -> long {
        /* GATE 195 (LUT3 _1222_ INIT 0x8f PERM 201) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut279.push_back(ctx.genrate_lut(lut279idx0));
    flut279.push_back(lut279idx0);
    auto fvec279 = [flut279](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut279[i](I));
        return ret;
    };

    std::cerr << "\rLUT279   ";
    Ciphertext gin279 = 1 * ct_my_string41 + 2 * gout193[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout279 = ctx.eval_lut_amortized(&gin279, lut279);

    std::vector<RotationPoly> lut280;
    std::vector<long (*)(long)> flut280;
    auto lut280idx0 = [](long I) -> long {
        /* GATE 128 (LUT3 _1155_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut280.push_back(ctx.genrate_lut(lut280idx0));
    flut280.push_back(lut280idx0);
    auto fvec280 = [flut280](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut280[i](I));
        return ret;
    };

    std::cerr << "\rLUT280   ";
    Ciphertext gin280 = 1 * gout215[0] + 2 * ct_my_string40 + 4 * gout76[0];
    std::vector<Ciphertext> gout280 = ctx.eval_lut_amortized(&gin280, lut280);

    std::vector<RotationPoly> lut281;
    std::vector<long (*)(long)> flut281;
    auto lut281idx0 = [](long I) -> long {
        /* GATE 364 (LUT3 _1391_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut281.push_back(ctx.genrate_lut(lut281idx0));
    flut281.push_back(lut281idx0);
    auto fvec281 = [flut281](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut281[i](I));
        return ret;
    };

    std::cerr << "\rLUT281   ";
    Ciphertext gin281 = 1 * gout133[0] + 2 * gout209[0] + 4 * gout48[0];
    std::vector<Ciphertext> gout281 = ctx.eval_lut_amortized(&gin281, lut281);

    std::vector<RotationPoly> lut282;
    std::vector<long (*)(long)> flut282;
    auto lut282idx0 = [](long I) -> long {
        /* GATE 294 (LUT3 _1321_ INIT 0xca PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut282.push_back(ctx.genrate_lut(lut282idx0));
    flut282.push_back(lut282idx0);
    auto fvec282 = [flut282](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut282[i](I));
        return ret;
    };

    std::cerr << "\rLUT282   ";
    Ciphertext gin282 = 1 * gout261[0] + 2 * gout106[1] + 4 * gout161[0];
    std::vector<Ciphertext> gout282 = ctx.eval_lut_amortized(&gin282, lut282);

    std::vector<RotationPoly> lut283;
    std::vector<long (*)(long)> flut283;
    auto lut283idx0 = [](long I) -> long {
        /* GATE 218 (LUT3 _1245_ INIT 0xf1 PERM 120) */
        switch (I) {
            case  0: return 1;
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
    lut283.push_back(ctx.genrate_lut(lut283idx0));
    flut283.push_back(lut283idx0);
    auto fvec283 = [flut283](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut283[i](I));
        return ret;
    };

    std::cerr << "\rLUT283   ";
    Ciphertext gin283 = 1 * gout233[0] + 2 * gout243[0] + 4 * gout48[0];
    std::vector<Ciphertext> gout283 = ctx.eval_lut_amortized(&gin283, lut283);

    std::vector<RotationPoly> lut284;
    std::vector<long (*)(long)> flut284;
    auto lut284idx0 = [](long I) -> long {
        /* GATE 117 (LUT3 _1144_ INIT 0x80 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut284.push_back(ctx.genrate_lut(lut284idx0));
    flut284.push_back(lut284idx0);
    auto fvec284 = [flut284](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut284[i](I));
        return ret;
    };

    std::cerr << "\rLUT284   ";
    Ciphertext gin284 = 1 * gout276[0] + 2 * gout205[0] + 4 * gout177[0];
    std::vector<Ciphertext> gout284 = ctx.eval_lut_amortized(&gin284, lut284);

    std::vector<RotationPoly> lut285;
    std::vector<long (*)(long)> flut285;
    auto lut285idx0 = [](long I) -> long {
        /* GATE 59 (LUT3 _1086_ INIT 0x7 PERM 210) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut285.push_back(ctx.genrate_lut(lut285idx0));
    flut285.push_back(lut285idx0);
    auto fvec285 = [flut285](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut285[i](I));
        return ret;
    };

    std::cerr << "\rLUT285   ";
    Ciphertext gin285 = 1 * gout219[1] + 2 * gout53[0] + 4 * ct_my_string48;
    std::vector<Ciphertext> gout285 = ctx.eval_lut_amortized(&gin285, lut285);

    std::vector<RotationPoly> lut286;
    std::vector<long (*)(long)> flut286;
    auto lut286idx0 = [](long I) -> long {
        /* GATE 270 (LUT3 _1297_ INIT 0x3a PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut286.push_back(ctx.genrate_lut(lut286idx0));
    flut286.push_back(lut286idx0);
    auto fvec286 = [flut286](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut286[i](I));
        return ret;
    };

    std::cerr << "\rLUT286   ";
    Ciphertext gin286 = 1 * gout219[0] + 2 * gout106[1] + 4 * gout183[0];
    std::vector<Ciphertext> gout286 = ctx.eval_lut_amortized(&gin286, lut286);

    std::vector<RotationPoly> lut287;
    std::vector<long (*)(long)> flut287;
    auto lut287idx0 = [](long I) -> long {
        /* GATE 286 (LUT3 _1313_ INIT 0x3a PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut287.push_back(ctx.genrate_lut(lut287idx0));
    flut287.push_back(lut287idx0);
    auto fvec287 = [flut287](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut287[i](I));
        return ret;
    };

    std::cerr << "\rLUT287   ";
    Ciphertext gin287 = 1 * gout207[0] + 2 * gout106[1] + 4 * gout112[0];
    std::vector<Ciphertext> gout287 = ctx.eval_lut_amortized(&gin287, lut287);

    std::vector<RotationPoly> lut288;
    std::vector<long (*)(long)> flut288;
    auto lut288idx0 = [](long I) -> long {
        /* GATE 298 (LUT3 _1325_ INIT 0x3a PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut288.push_back(ctx.genrate_lut(lut288idx0));
    flut288.push_back(lut288idx0);
    auto fvec288 = [flut288](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut288[i](I));
        return ret;
    };

    std::cerr << "\rLUT288   ";
    Ciphertext gin288 = 1 * gout238[0] + 2 * gout106[1] + 4 * gout123[0];
    std::vector<Ciphertext> gout288 = ctx.eval_lut_amortized(&gin288, lut288);

    std::vector<RotationPoly> lut289;
    std::vector<long (*)(long)> flut289;
    auto lut289idx0 = [](long I) -> long {
        /* GATE 356 (LUT3 _1383_ INIT 0x7 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut289.push_back(ctx.genrate_lut(lut289idx0));
    flut289.push_back(lut289idx0);
    auto fvec289 = [flut289](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut289[i](I));
        return ret;
    };

    std::cerr << "\rLUT289   ";
    Ciphertext gin289 = 1 * gout262[0] + 2 * gout189[0] + 4 * gout51[0];
    std::vector<Ciphertext> gout289 = ctx.eval_lut_amortized(&gin289, lut289);

    std::vector<RotationPoly> lut290;
    std::vector<long (*)(long)> flut290;
    auto lut290idx0 = [](long I) -> long {
        /* GATE 273 (LUT3 _1300_ INIT 0x3a PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut290.push_back(ctx.genrate_lut(lut290idx0));
    flut290.push_back(lut290idx0);
    auto fvec290 = [flut290](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut290[i](I));
        return ret;
    };

    std::cerr << "\rLUT290   ";
    Ciphertext gin290 = 1 * gout208[0] + 2 * gout272[0] + 4 * gout76[0];
    std::vector<Ciphertext> gout290 = ctx.eval_lut_amortized(&gin290, lut290);

    std::vector<RotationPoly> lut291;
    std::vector<long (*)(long)> flut291;
    auto lut291idx0 = [](long I) -> long {
        /* GATE 224 (LUT3 _1251_ INIT 0xf1 PERM 120) */
        switch (I) {
            case  0: return 1;
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
    lut291.push_back(ctx.genrate_lut(lut291idx0));
    flut291.push_back(lut291idx0);
    auto fvec291 = [flut291](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut291[i](I));
        return ret;
    };

    std::cerr << "\rLUT291   ";
    Ciphertext gin291 = 1 * gout244[0] + 2 * gout227[0] + 4 * gout48[0];
    std::vector<Ciphertext> gout291 = ctx.eval_lut_amortized(&gin291, lut291);

    std::vector<RotationPoly> lut292;
    std::vector<long (*)(long)> flut292;
    auto lut292idx0 = [](long I) -> long {
        /* GATE 69 (LUT3 _1096_ INIT 0x7 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut292.push_back(ctx.genrate_lut(lut292idx0));
    flut292.push_back(lut292idx0);
    auto fvec292 = [flut292](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut292[i](I));
        return ret;
    };

    std::cerr << "\rLUT292   ";
    Ciphertext gin292 = 1 * gout202[0] + 2 * gout198[0] + 4 * gout46[0];
    std::vector<Ciphertext> gout292 = ctx.eval_lut_amortized(&gin292, lut292);

    std::vector<RotationPoly> lut293;
    std::vector<long (*)(long)> flut293;
    auto lut293idx0 = [](long I) -> long {
        /* GATE 77 (LUT3 _1104_ INIT 0x80 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut293.push_back(ctx.genrate_lut(lut293idx0));
    flut293.push_back(lut293idx0);
    auto fvec293 = [flut293](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut293[i](I));
        return ret;
    };

    std::cerr << "\rLUT293   ";
    Ciphertext gin293 = 1 * gout185[0] + 2 * gout220[0] + 4 * gout221[0];
    std::vector<Ciphertext> gout293 = ctx.eval_lut_amortized(&gin293, lut293);

    std::vector<RotationPoly> lut294;
    std::vector<long (*)(long)> flut294;
    auto lut294idx0 = [](long I) -> long {
        /* GATE 277 (LUT3 _1304_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut294.push_back(ctx.genrate_lut(lut294idx0));
    flut294.push_back(lut294idx0);
    auto fvec294 = [flut294](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut294[i](I));
        return ret;
    };

    std::cerr << "\rLUT294   ";
    Ciphertext gin294 = 1 * gout216[0] + 2 * gout206[0] + 4 * gout76[0];
    std::vector<Ciphertext> gout294 = ctx.eval_lut_amortized(&gin294, lut294);

    std::vector<RotationPoly> lut295;
    std::vector<long (*)(long)> flut295;
    auto lut295idx0 = [](long I) -> long {
        /* GATE 98 (LUT3 _1125_ INIT 0x7 PERM 210) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut295.push_back(ctx.genrate_lut(lut295idx0));
    flut295.push_back(lut295idx0);
    auto fvec295 = [flut295](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut295[i](I));
        return ret;
    };

    std::cerr << "\rLUT295   ";
    Ciphertext gin295 = 1 * gout253[0] + 2 * gout53[0] + 4 * ct_my_string52;
    std::vector<Ciphertext> gout295 = ctx.eval_lut_amortized(&gin295, lut295);

    std::vector<RotationPoly> lut296;
    std::vector<long (*)(long)> flut296;
    auto lut296idx0 = [](long I) -> long {
        /* GATE 300 (LUT3 _1327_ INIT 0x35 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut296.push_back(ctx.genrate_lut(lut296idx0));
    flut296.push_back(lut296idx0);
    auto fvec296 = [flut296](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut296[i](I));
        return ret;
    };

    std::cerr << "\rLUT296   ";
    Ciphertext gin296 = 1 * gout229[0] + 2 * gout56[1] + 4 * gout274[0];
    std::vector<Ciphertext> gout296 = ctx.eval_lut_amortized(&gin296, lut296);

    std::vector<RotationPoly> lut297;
    std::vector<long (*)(long)> flut297;
    auto lut297idx0 = [](long I) -> long {
        /* GATE 102 (LUT3 _1129_ INIT 0x80 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut297.push_back(ctx.genrate_lut(lut297idx0));
    flut297.push_back(lut297idx0);
    auto fvec297 = [flut297](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut297[i](I));
        return ret;
    };

    std::cerr << "\rLUT297   ";
    Ciphertext gin297 = 1 * gout153[0] + 2 * gout147[0] + 4 * gout264[0];
    std::vector<Ciphertext> gout297 = ctx.eval_lut_amortized(&gin297, lut297);

    std::vector<RotationPoly> lut298;
    std::vector<long (*)(long)> flut298;
    auto lut298idx0 = [](long I) -> long {
        /* GATE 281 (LUT3 _1308_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut298.push_back(ctx.genrate_lut(lut298idx0));
    flut298.push_back(lut298idx0);
    auto fvec298 = [flut298](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut298[i](I));
        return ret;
    };

    std::cerr << "\rLUT298   ";
    Ciphertext gin298 = 1 * gout232[0] + 2 * gout180[0] + 4 * gout76[0];
    std::vector<Ciphertext> gout298 = ctx.eval_lut_amortized(&gin298, lut298);

    std::vector<RotationPoly> lut299;
    std::vector<long (*)(long)> flut299;
    auto lut299idx0 = [](long I) -> long {
        /* GATE 315 (LUT3 _1342_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut299.push_back(ctx.genrate_lut(lut299idx0));
    flut299.push_back(lut299idx0);
    auto fvec299 = [flut299](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut299[i](I));
        return ret;
    };

    std::cerr << "\rLUT299   ";
    Ciphertext gin299 = 1 * gout150[0] + 2 * gout243[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout299 = ctx.eval_lut_amortized(&gin299, lut299);

    std::vector<RotationPoly> lut300;
    std::vector<long (*)(long)> flut300;
    auto lut300idx0 = [](long I) -> long {
        /* GATE 257 (LUT3 _1284_ INIT 0x3a PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut300.push_back(ctx.genrate_lut(lut300idx0));
    flut300.push_back(lut300idx0);
    auto fvec300 = [flut300](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut300[i](I));
        return ret;
    };

    std::cerr << "\rLUT300   ";
    Ciphertext gin300 = 1 * gout195[0] + 2 * gout243[0] + 4 * gout106[1];
    std::vector<Ciphertext> gout300 = ctx.eval_lut_amortized(&gin300, lut300);

    std::vector<RotationPoly> lut301;
    std::vector<long (*)(long)> flut301;
    auto lut301idx0 = [](long I) -> long {
        /* GATE 285 (LUT3 _1312_ INIT 0x3a PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut301.push_back(ctx.genrate_lut(lut301idx0));
    flut301.push_back(lut301idx0);
    auto fvec301 = [flut301](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut301[i](I));
        return ret;
    };

    std::cerr << "\rLUT301   ";
    Ciphertext gin301 = 1 * gout287[0] + 2 * gout76[0] + 4 * gout133[0];
    std::vector<Ciphertext> gout301 = ctx.eval_lut_amortized(&gin301, lut301);

    std::vector<RotationPoly> lut302;
    std::vector<long (*)(long)> flut302;
    auto lut302idx0 = [](long I) -> long {
        /* GATE 237 (LUT3 _1264_ INIT 0x3a PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut302.push_back(ctx.genrate_lut(lut302idx0));
    flut302.push_back(lut302idx0);
    auto fvec302 = [flut302](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut302[i](I));
        return ret;
    };

    std::cerr << "\rLUT302   ";
    Ciphertext gin302 = 1 * gout256[0] + 2 * gout106[1] + 4 * gout274[0];
    std::vector<Ciphertext> gout302 = ctx.eval_lut_amortized(&gin302, lut302);

    std::vector<RotationPoly> lut303;
    std::vector<long (*)(long)> flut303;
    auto lut303idx0 = [](long I) -> long {
        /* GATE 91 (LUT3 _1118_ INIT 0xbf PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut303.push_back(ctx.genrate_lut(lut303idx0));
    flut303.push_back(lut303idx0);
    auto fvec303 = [flut303](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut303[i](I));
        return ret;
    };

    std::cerr << "\rLUT303   ";
    Ciphertext gin303 = 1 * gout50[0] + 2 * gout295[0] + 4 * gout200[0];
    std::vector<Ciphertext> gout303 = ctx.eval_lut_amortized(&gin303, lut303);

    std::vector<RotationPoly> lut304;
    std::vector<long (*)(long)> flut304;
    auto lut304idx0 = [](long I) -> long {
        /* GATE 161 (LUT3 _1188_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut304.push_back(ctx.genrate_lut(lut304idx0));
    flut304.push_back(lut304idx0);
    auto fvec304 = [flut304](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut304[i](I));
        return ret;
    };

    std::cerr << "\rLUT304   ";
    Ciphertext gin304 = 1 * gout234[0] + 2 * ct_my_string36 + 4 * gout106[1];
    std::vector<Ciphertext> gout304 = ctx.eval_lut_amortized(&gin304, lut304);

    std::vector<RotationPoly> lut305;
    std::vector<long (*)(long)> flut305;
    auto lut305idx0 = [](long I) -> long {
        /* GATE 85 (LUT3 _1112_ INIT 0xf8 PERM 021) */
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
    lut305.push_back(ctx.genrate_lut(lut305idx0));
    flut305.push_back(lut305idx0);
    auto fvec305 = [flut305](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut305[i](I));
        return ret;
    };

    std::cerr << "\rLUT305   ";
    Ciphertext gin305 = 1 * gout34[0] + 2 * gout273[0] + 4 * ct_my_string3;
    std::vector<Ciphertext> gout305 = ctx.eval_lut_amortized(&gin305, lut305);

    std::vector<RotationPoly> lut306;
    std::vector<long (*)(long)> flut306;
    auto lut306idx0 = [](long I) -> long {
        /* GATE 261 (LUT3 _1288_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut306.push_back(ctx.genrate_lut(lut306idx0));
    flut306.push_back(lut306idx0);
    auto fvec306 = [flut306](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut306[i](I));
        return ret;
    };

    std::cerr << "\rLUT306   ";
    Ciphertext gin306 = 1 * gout218[0] + 2 * gout227[0] + 4 * gout106[1];
    std::vector<Ciphertext> gout306 = ctx.eval_lut_amortized(&gin306, lut306);

    std::vector<RotationPoly> lut307;
    std::vector<long (*)(long)> flut307;
    auto lut307idx0 = [](long I) -> long {
        /* GATE 265 (LUT3 _1292_ INIT 0x3a PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut307.push_back(ctx.genrate_lut(lut307idx0));
    flut307.push_back(lut307idx0);
    auto fvec307 = [flut307](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut307[i](I));
        return ret;
    };

    std::cerr << "\rLUT307   ";
    Ciphertext gin307 = 1 * gout231[0] + 2 * gout106[1] + 4 * gout217[0];
    std::vector<Ciphertext> gout307 = ctx.eval_lut_amortized(&gin307, lut307);

    std::vector<RotationPoly> lut308;
    std::vector<long (*)(long)> flut308;
    auto lut308idx0 = [](long I) -> long {
        /* GATE 76 (LUT3 _1103_ INIT 0xe PERM 210) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut308.push_back(ctx.genrate_lut(lut308idx0));
    flut308.push_back(lut308idx0);
    auto fvec308 = [flut308](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut308[i](I));
        return ret;
    };

    std::cerr << "\rLUT308   ";
    Ciphertext gin308 = 1 * gout293[0] + 2 * gout41[0] + 4 * ct_my_string2;
    std::vector<Ciphertext> gout308 = ctx.eval_lut_amortized(&gin308, lut308);

    std::vector<RotationPoly> lut309;
    std::vector<long (*)(long)> flut309;
    auto lut309idx0 = [](long I) -> long {
        /* GATE 289 (LUT3 _1316_ INIT 0x3a PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut309.push_back(ctx.genrate_lut(lut309idx0));
    flut309.push_back(lut309idx0);
    auto fvec309 = [flut309](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut309[i](I));
        return ret;
    };

    std::cerr << "\rLUT309   ";
    Ciphertext gin309 = 1 * gout239[0] + 2 * gout243[0] + 4 * gout76[0];
    std::vector<Ciphertext> gout309 = ctx.eval_lut_amortized(&gin309, lut309);

    std::vector<RotationPoly> lut310;
    std::vector<long (*)(long)> flut310;
    auto lut310idx0 = [](long I) -> long {
        /* GATE 133 (LUT3 _1160_ INIT 0x35 PERM 102) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut310.push_back(ctx.genrate_lut(lut310idx0));
    flut310.push_back(lut310idx0);
    auto fvec310 = [flut310](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut310[i](I));
        return ret;
    };

    std::cerr << "\rLUT310   ";
    Ciphertext gin310 = 1 * gout241[0] + 2 * gout137[0] + 4 * gout55[0];
    std::vector<Ciphertext> gout310 = ctx.eval_lut_amortized(&gin310, lut310);

    std::vector<RotationPoly> lut311;
    std::vector<long (*)(long)> flut311;
    auto lut311idx0 = [](long I) -> long {
        /* GATE 260 (LUT3 _1287_ INIT 0xa3 PERM 012) */
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
    lut311.push_back(ctx.genrate_lut(lut311idx0));
    flut311.push_back(lut311idx0);
    auto fvec311 = [flut311](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut311[i](I));
        return ret;
    };

    std::cerr << "\rLUT311   ";
    Ciphertext gin311 = 1 * ct_my_string38 + 2 * gout306[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout311 = ctx.eval_lut_amortized(&gin311, lut311);

    std::vector<RotationPoly> lut312;
    std::vector<long (*)(long)> flut312;
    auto lut312idx0 = [](long I) -> long {
        /* GATE 154 (LUT3 _1181_ INIT 0x1 PERM 012) */
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
    lut312.push_back(ctx.genrate_lut(lut312idx0));
    flut312.push_back(lut312idx0);
    auto fvec312 = [flut312](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut312[i](I));
        return ret;
    };

    std::cerr << "\rLUT312   ";
    Ciphertext gin312 = 1 * gout116[0] + 2 * gout263[0] + 4 * gout134[0];
    std::vector<Ciphertext> gout312 = ctx.eval_lut_amortized(&gin312, lut312);

    std::vector<RotationPoly> lut313;
    std::vector<long (*)(long)> flut313;
    auto lut313idx0 = [](long I) -> long {
        /* GATE 148 (LUT3 _1175_ INIT 0x7 PERM 210) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut313.push_back(ctx.genrate_lut(lut313idx0));
    flut313.push_back(lut313idx0);
    auto fvec313 = [flut313](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut313[i](I));
        return ret;
    };

    std::cerr << "\rLUT313   ";
    Ciphertext gin313 = 1 * gout242[0] + 2 * gout53[0] + 4 * ct_my_string42;
    std::vector<Ciphertext> gout313 = ctx.eval_lut_amortized(&gin313, lut313);

    std::vector<RotationPoly> lut314;
    std::vector<long (*)(long)> flut314;
    auto lut314idx0 = [](long I) -> long {
        /* GATE 252 (LUT3 _1279_ INIT 0xac PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut314.push_back(ctx.genrate_lut(lut314idx0));
    flut314.push_back(lut314idx0);
    auto fvec314 = [flut314](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut314[i](I));
        return ret;
    };

    std::cerr << "\rLUT314   ";
    Ciphertext gin314 = 1 * ct_my_string36 + 2 * gout267[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout314 = ctx.eval_lut_amortized(&gin314, lut314);

    std::vector<RotationPoly> lut315;
    std::vector<long (*)(long)> flut315;
    auto lut315idx0 = [](long I) -> long {
        /* GATE 241 (LUT3 _1268_ INIT 0x3a PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut315.push_back(ctx.genrate_lut(lut315idx0));
    flut315.push_back(lut315idx0);
    auto fvec315 = [flut315](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut315[i](I));
        return ret;
    };

    std::cerr << "\rLUT315   ";
    Ciphertext gin315 = 1 * gout266[0] + 2 * gout272[0] + 4 * gout106[1];
    std::vector<Ciphertext> gout315 = ctx.eval_lut_amortized(&gin315, lut315);

    std::vector<RotationPoly> lut316;
    std::vector<long (*)(long)> flut316;
    auto lut316idx0 = [](long I) -> long {
        /* GATE 165 (LUT3 _1192_ INIT 0x35 PERM 102) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut316.push_back(ctx.genrate_lut(lut316idx0));
    flut316.push_back(lut316idx0);
    auto fvec316 = [flut316](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut316[i](I));
        return ret;
    };

    std::cerr << "\rLUT316   ";
    Ciphertext gin316 = 1 * gout268[0] + 2 * gout148[0] + 4 * gout55[0];
    std::vector<Ciphertext> gout316 = ctx.eval_lut_amortized(&gin316, lut316);

    std::vector<RotationPoly> lut317;
    std::vector<long (*)(long)> flut317;
    auto lut317idx0 = [](long I) -> long {
        /* GATE 101 (LUT3 _1128_ INIT 0xe PERM 210) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut317.push_back(ctx.genrate_lut(lut317idx0));
    flut317.push_back(lut317idx0);
    auto fvec317 = [flut317](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut317[i](I));
        return ret;
    };

    std::cerr << "\rLUT317   ";
    Ciphertext gin317 = 1 * gout297[0] + 2 * gout41[0] + 4 * ct_my_string5;
    std::vector<Ciphertext> gout317 = ctx.eval_lut_amortized(&gin317, lut317);

    std::vector<RotationPoly> lut318;
    std::vector<long (*)(long)> flut318;
    auto lut318idx0 = [](long I) -> long {
        /* GATE 293 (LUT3 _1320_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut318.push_back(ctx.genrate_lut(lut318idx0));
    flut318.push_back(lut318idx0);
    auto fvec318 = [flut318](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut318[i](I));
        return ret;
    };

    std::cerr << "\rLUT318   ";
    Ciphertext gin318 = 1 * gout282[0] + 2 * gout227[0] + 4 * gout76[0];
    std::vector<Ciphertext> gout318 = ctx.eval_lut_amortized(&gin318, lut318);

    std::vector<RotationPoly> lut319;
    std::vector<long (*)(long)> flut319;
    auto lut319idx0 = [](long I) -> long {
        /* GATE 236 (LUT3 _1263_ INIT 0xac PERM 201) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut319.push_back(ctx.genrate_lut(lut319idx0));
    flut319.push_back(lut319idx0);
    auto fvec319 = [flut319](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut319[i](I));
        return ret;
    };

    std::cerr << "\rLUT319   ";
    Ciphertext gin319 = 1 * gout302[0] + 2 * gout56[1] + 4 * ct_my_string32;
    std::vector<Ciphertext> gout319 = ctx.eval_lut_amortized(&gin319, lut319);

    std::vector<RotationPoly> lut320;
    std::vector<long (*)(long)> flut320;
    auto lut320idx0 = [](long I) -> long {
        /* GATE 240 (LUT3 _1267_ INIT 0xac PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut320.push_back(ctx.genrate_lut(lut320idx0));
    flut320.push_back(lut320idx0);
    auto fvec320 = [flut320](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut320[i](I));
        return ret;
    };

    std::cerr << "\rLUT320   ";
    Ciphertext gin320 = 1 * ct_my_string33 + 2 * gout315[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout320 = ctx.eval_lut_amortized(&gin320, lut320);

    std::vector<RotationPoly> lut321;
    std::vector<long (*)(long)> flut321;
    auto lut321idx0 = [](long I) -> long {
        /* GATE 151 (LUT3 _1178_ INIT 0xbf PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut321.push_back(ctx.genrate_lut(lut321idx0));
    flut321.push_back(lut321idx0);
    auto fvec321 = [flut321](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut321[i](I));
        return ret;
    };

    std::cerr << "\rLUT321   ";
    Ciphertext gin321 = 1 * gout128[0] + 2 * gout312[0] + 4 * gout127[0];
    std::vector<Ciphertext> gout321 = ctx.eval_lut_amortized(&gin321, lut321);

    std::vector<RotationPoly> lut322;
    std::vector<long (*)(long)> flut322;
    auto lut322idx0 = [](long I) -> long {
        /* GATE 303 (LUT3 _1330_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut322.push_back(ctx.genrate_lut(lut322idx0));
    flut322.push_back(lut322idx0);
    auto fvec322 = [flut322](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut322[i](I));
        return ret;
    };

    std::cerr << "\rLUT322   ";
    Ciphertext gin322 = 1 * gout223[0] + 2 * gout272[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout322 = ctx.eval_lut_amortized(&gin322, lut322);

    std::vector<RotationPoly> lut323;
    std::vector<long (*)(long)> flut323;
    auto lut323idx0 = [](long I) -> long {
        /* GATE 297 (LUT3 _1324_ INIT 0x3a PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut323.push_back(ctx.genrate_lut(lut323idx0));
    flut323.push_back(lut323idx0);
    auto fvec323 = [flut323](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut323[i](I));
        return ret;
    };

    std::cerr << "\rLUT323   ";
    Ciphertext gin323 = 1 * gout288[0] + 2 * gout217[0] + 4 * gout76[0];
    std::vector<Ciphertext> gout323 = ctx.eval_lut_amortized(&gin323, lut323);

    std::vector<RotationPoly> lut324;
    std::vector<long (*)(long)> flut324;
    auto lut324idx0 = [](long I) -> long {
        /* GATE 175 (LUT3 _1202_ INIT 0x35 PERM 102) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut324.push_back(ctx.genrate_lut(lut324idx0));
    flut324.push_back(lut324idx0);
    auto fvec324 = [flut324](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut324[i](I));
        return ret;
    };

    std::cerr << "\rLUT324   ";
    Ciphertext gin324 = 1 * gout278[0] + 2 * gout161[0] + 4 * gout55[0];
    std::vector<Ciphertext> gout324 = ctx.eval_lut_amortized(&gin324, lut324);

    std::vector<RotationPoly> lut325;
    std::vector<long (*)(long)> flut325;
    auto lut325idx0 = [](long I) -> long {
        /* GATE 187 (LUT3 _1214_ INIT 0x7 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut325.push_back(ctx.genrate_lut(lut325idx0));
    flut325.push_back(lut325idx0);
    auto fvec325 = [flut325](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut325[i](I));
        return ret;
    };

    std::cerr << "\rLUT325   ";
    Ciphertext gin325 = 1 * gout259[0] + 2 * ct_my_string39 + 4 * gout106[1];
    std::vector<Ciphertext> gout325 = ctx.eval_lut_amortized(&gin325, lut325);

    std::vector<RotationPoly> lut326;
    std::vector<long (*)(long)> flut326;
    auto lut326idx0 = [](long I) -> long {
        /* GATE 116 (LUT3 _1143_ INIT 0x4f PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut326.push_back(ctx.genrate_lut(lut326idx0));
    flut326.push_back(lut326idx0);
    auto fvec326 = [flut326](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut326[i](I));
        return ret;
    };

    std::cerr << "\rLUT326   ";
    Ciphertext gin326 = 1 * gout41[0] + 2 * gout284[0] + 4 * ct_my_string7;
    std::vector<Ciphertext> gout326 = ctx.eval_lut_amortized(&gin326, lut326);

    std::vector<RotationPoly> lut327;
    std::vector<long (*)(long)> flut327;
    auto lut327idx0 = [](long I) -> long {
        /* GATE 269 (LUT3 _1296_ INIT 0x3a PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut327.push_back(ctx.genrate_lut(lut327idx0));
    flut327.push_back(lut327idx0);
    auto fvec327 = [flut327](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut327[i](I));
        return ret;
    };

    std::cerr << "\rLUT327   ";
    Ciphertext gin327 = 1 * gout286[0] + 2 * gout76[0] + 4 * gout274[0];
    std::vector<Ciphertext> gout327 = ctx.eval_lut_amortized(&gin327, lut327);

    std::vector<RotationPoly> lut328;
    std::vector<long (*)(long)> flut328;
    auto lut328idx0 = [](long I) -> long {
        /* GATE 272 (LUT3 _1299_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut328.push_back(ctx.genrate_lut(lut328idx0));
    flut328.push_back(lut328idx0);
    auto fvec328 = [flut328](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut328[i](I));
        return ret;
    };

    std::cerr << "\rLUT328   ";
    Ciphertext gin328 = 1 * gout290[0] + 2 * gout315[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout328 = ctx.eval_lut_amortized(&gin328, lut328);

    std::vector<RotationPoly> lut329;
    std::vector<long (*)(long)> flut329;
    auto lut329idx0 = [](long I) -> long {
        /* GATE 358 (LUT3 _1385_ INIT 0x40 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut329.push_back(ctx.genrate_lut(lut329idx0));
    flut329.push_back(lut329idx0);
    auto fvec329 = [flut329](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut329[i](I));
        return ret;
    };

    std::cerr << "\rLUT329   ";
    Ciphertext gin329 = 1 * gout99[0] + 2 * gout304[0] + 4 * gout179[0];
    std::vector<Ciphertext> gout329 = ctx.eval_lut_amortized(&gin329, lut329);

    std::vector<RotationPoly> lut330;
    std::vector<long (*)(long)> flut330;
    auto lut330idx0 = [](long I) -> long {
        /* GATE 256 (LUT3 _1283_ INIT 0xac PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut330.push_back(ctx.genrate_lut(lut330idx0));
    flut330.push_back(lut330idx0);
    auto fvec330 = [flut330](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut330[i](I));
        return ret;
    };

    std::cerr << "\rLUT330   ";
    Ciphertext gin330 = 1 * ct_my_string37 + 2 * gout300[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout330 = ctx.eval_lut_amortized(&gin330, lut330);

    std::vector<RotationPoly> lut331;
    std::vector<long (*)(long)> flut331;
    auto lut331idx0 = [](long I) -> long {
        /* GATE 276 (LUT3 _1303_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut331.push_back(ctx.genrate_lut(lut331idx0));
    flut331.push_back(lut331idx0);
    auto fvec331 = [flut331](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut331[i](I));
        return ret;
    };

    std::cerr << "\rLUT331   ";
    Ciphertext gin331 = 1 * gout294[0] + 2 * gout247[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout331 = ctx.eval_lut_amortized(&gin331, lut331);

    std::vector<RotationPoly> lut332;
    std::vector<long (*)(long)> flut332;
    auto lut332idx0 = [](long I) -> long {
        /* GATE 206 (LUT3 _1233_ INIT 0x35 PERM 102) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut332.push_back(ctx.genrate_lut(lut332idx0));
    flut332.push_back(lut332idx0);
    auto fvec332 = [flut332](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut332[i](I));
        return ret;
    };

    std::cerr << "\rLUT332   ";
    Ciphertext gin332 = 1 * gout277[0] + 2 * gout180[0] + 4 * gout48[0];
    std::vector<Ciphertext> gout332 = ctx.eval_lut_amortized(&gin332, lut332);

    std::vector<RotationPoly> lut333;
    std::vector<long (*)(long)> flut333;
    auto lut333idx0 = [](long I) -> long {
        /* GATE 194 (LUT3 _1221_ INIT 0xf1 PERM 120) */
        switch (I) {
            case  0: return 1;
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
    lut333.push_back(ctx.genrate_lut(lut333idx0));
    flut333.push_back(lut333idx0);
    auto fvec333 = [flut333](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut333[i](I));
        return ret;
    };

    std::cerr << "\rLUT333   ";
    Ciphertext gin333 = 1 * gout279[0] + 2 * gout272[0] + 4 * gout48[0];
    std::vector<Ciphertext> gout333 = ctx.eval_lut_amortized(&gin333, lut333);

    std::vector<RotationPoly> lut334;
    std::vector<long (*)(long)> flut334;
    auto lut334idx0 = [](long I) -> long {
        /* GATE 2 (LUT3 _1029_ INIT 0x80 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut334.push_back(ctx.genrate_lut(lut334idx0));
    flut334.push_back(lut334idx0);
    auto fvec334 = [flut334](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut334[i](I));
        return ret;
    };

    std::cerr << "\rLUT334   ";
    Ciphertext gin334 = 1 * gout222[0] + 2 * gout285[0] + 4 * gout187[0];
    std::vector<Ciphertext> gout334 = ctx.eval_lut_amortized(&gin334, lut334);

    std::vector<RotationPoly> lut335;
    std::vector<long (*)(long)> flut335;
    auto lut335idx0 = [](long I) -> long {
        /* GATE 126 (LUT3 _1153_ INIT 0x40 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut335.push_back(ctx.genrate_lut(lut335idx0));
    flut335.push_back(lut335idx0);
    auto fvec335 = [flut335](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut335[i](I));
        return ret;
    };

    std::cerr << "\rLUT335   ";
    Ciphertext gin335 = 1 * gout86[0] + 2 * gout118[0] + 4 * gout280[0];
    std::vector<Ciphertext> gout335 = ctx.eval_lut_amortized(&gin335, lut335);

    std::vector<RotationPoly> lut336;
    std::vector<long (*)(long)> flut336;
    auto lut336idx0 = [](long I) -> long {
        /* GATE 280 (LUT3 _1307_ INIT 0xc5 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut336.push_back(ctx.genrate_lut(lut336idx0));
    flut336.push_back(lut336idx0);
    auto fvec336 = [flut336](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut336[i](I));
        return ret;
    };

    std::cerr << "\rLUT336   ";
    Ciphertext gin336 = 1 * gout298[0] + 2 * gout257[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout336 = ctx.eval_lut_amortized(&gin336, lut336);

    std::vector<RotationPoly> lut337;
    std::vector<long (*)(long)> flut337;
    auto lut337idx0 = [](long I) -> long {
        /* GATE 268 (LUT3 _1295_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut337.push_back(ctx.genrate_lut(lut337idx0));
    flut337.push_back(lut337idx0);
    auto fvec337 = [flut337](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut337[i](I));
        return ret;
    };

    std::cerr << "\rLUT337   ";
    Ciphertext gin337 = 1 * gout327[0] + 2 * gout302[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout337 = ctx.eval_lut_amortized(&gin337, lut337);

    std::vector<RotationPoly> lut338;
    std::vector<long (*)(long)> flut338;
    auto lut338idx0 = [](long I) -> long {
        /* GATE 264 (LUT3 _1291_ INIT 0xac PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut338.push_back(ctx.genrate_lut(lut338idx0));
    flut338.push_back(lut338idx0);
    auto fvec338 = [flut338](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut338[i](I));
        return ret;
    };

    std::cerr << "\rLUT338   ";
    Ciphertext gin338 = 1 * ct_my_string39 + 2 * gout307[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout338 = ctx.eval_lut_amortized(&gin338, lut338);

    std::vector<RotationPoly> lut339;
    std::vector<long (*)(long)> flut339;
    auto lut339idx0 = [](long I) -> long {
        /* GATE 284 (LUT3 _1311_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut339.push_back(ctx.genrate_lut(lut339idx0));
    flut339.push_back(lut339idx0);
    auto fvec339 = [flut339](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut339[i](I));
        return ret;
    };

    std::cerr << "\rLUT339   ";
    Ciphertext gin339 = 1 * gout301[0] + 2 * gout267[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout339 = ctx.eval_lut_amortized(&gin339, lut339);

    std::vector<RotationPoly> lut340;
    std::vector<long (*)(long)> flut340;
    auto lut340idx0 = [](long I) -> long {
        /* GATE 288 (LUT3 _1315_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut340.push_back(ctx.genrate_lut(lut340idx0));
    flut340.push_back(lut340idx0);
    auto fvec340 = [flut340](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut340[i](I));
        return ret;
    };

    std::cerr << "\rLUT340   ";
    Ciphertext gin340 = 1 * gout309[0] + 2 * gout300[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout340 = ctx.eval_lut_amortized(&gin340, lut340);

    std::vector<RotationPoly> lut341;
    std::vector<long (*)(long)> flut341;
    auto lut341idx0 = [](long I) -> long {
        /* GATE 184 (LUT3 _1211_ INIT 0x40 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut341.push_back(ctx.genrate_lut(lut341idx0));
    flut341.push_back(lut341idx0);
    auto fvec341 = [flut341](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut341[i](I));
        return ret;
    };

    std::cerr << "\rLUT341   ";
    Ciphertext gin341 = 1 * gout77[0] + 2 * gout325[0] + 4 * gout72[0];
    std::vector<Ciphertext> gout341 = ctx.eval_lut_amortized(&gin341, lut341);

    std::vector<RotationPoly> lut342;
    std::vector<long (*)(long)> flut342;
    auto lut342idx0 = [](long I) -> long {
        /* GATE 125 (LUT3 _1152_ INIT 0x35 PERM 102) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut342.push_back(ctx.genrate_lut(lut342idx0));
    flut342.push_back(lut342idx0);
    auto fvec342 = [flut342](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut342[i](I));
        return ret;
    };

    std::cerr << "\rLUT342   ";
    Ciphertext gin342 = 1 * gout335[0] + 2 * gout183[0] + 4 * gout55[0];
    std::vector<Ciphertext> gout342 = ctx.eval_lut_amortized(&gin342, lut342);

    std::vector<RotationPoly> lut343;
    std::vector<long (*)(long)> flut343;
    auto lut343idx0 = [](long I) -> long {
        /* GATE 292 (LUT3 _1319_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut343.push_back(ctx.genrate_lut(lut343idx0));
    flut343.push_back(lut343idx0);
    auto fvec343 = [flut343](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut343[i](I));
        return ret;
    };

    std::cerr << "\rLUT343   ";
    Ciphertext gin343 = 1 * gout318[0] + 2 * gout306[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout343 = ctx.eval_lut_amortized(&gin343, lut343);

    std::vector<RotationPoly> lut344;
    std::vector<long (*)(long)> flut344;
    auto lut344idx0 = [](long I) -> long {
        /* GATE 359 (LUT3 _1386_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut344.push_back(ctx.genrate_lut(lut344idx0));
    flut344.push_back(lut344idx0);
    auto fvec344 = [flut344](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut344[i](I));
        return ret;
    };

    std::cerr << "\rLUT344   ";
    Ciphertext gin344 = 1 * gout112[0] + 2 * gout329[0] + 4 * gout55[0];
    std::vector<Ciphertext> gout344 = ctx.eval_lut_amortized(&gin344, lut344);

    std::vector<RotationPoly> lut345;
    std::vector<long (*)(long)> flut345;
    auto lut345idx0 = [](long I) -> long {
        /* GATE 296 (LUT3 _1323_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut345.push_back(ctx.genrate_lut(lut345idx0));
    flut345.push_back(lut345idx0);
    auto fvec345 = [flut345](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut345[i](I));
        return ret;
    };

    std::cerr << "\rLUT345   ";
    Ciphertext gin345 = 1 * gout323[0] + 2 * gout307[0] + 4 * gout56[1];
    std::vector<Ciphertext> gout345 = ctx.eval_lut_amortized(&gin345, lut345);

    std::vector<RotationPoly> lut346;
    std::vector<long (*)(long)> flut346;
    auto lut346idx0 = [](long I) -> long {
        /* GATE 1 (LUT3 _1028_ INIT 0xe PERM 210) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut346.push_back(ctx.genrate_lut(lut346idx0));
    flut346.push_back(lut346idx0);
    auto fvec346 = [flut346](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut346[i](I));
        return ret;
    };

    std::cerr << "\rLUT346   ";
    Ciphertext gin346 = 1 * gout334[0] + 2 * gout41[0] + 4 * ct_my_string0;
    std::vector<Ciphertext> gout346 = ctx.eval_lut_amortized(&gin346, lut346);

    std::vector<RotationPoly> lut347;
    std::vector<long (*)(long)> flut347;
    auto lut347idx0 = [](long I) -> long {
        /* GATE 143 (LUT3 _1170_ INIT 0x70 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut347.push_back(ctx.genrate_lut(lut347idx0));
    flut347.push_back(lut347idx0);
    auto fvec347 = [flut347](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut347[i](I));
        return ret;
    };

    std::cerr << "\rLUT347   ";
    Ciphertext gin347 = 1 * gout313[0] + 2 * gout237[0] + 4 * gout55[0];
    std::vector<Ciphertext> gout347 = ctx.eval_lut_amortized(&gin347, lut347);

    std::vector<RotationPoly> lut348;
    std::vector<long (*)(long)> flut348;
    auto lut348idx0 = [](long I) -> long {
        /* GATE 142 (LUT3 _1169_ INIT 0xf1 PERM 120) */
        switch (I) {
            case  0: return 1;
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
    lut348.push_back(ctx.genrate_lut(lut348idx0));
    flut348.push_back(lut348idx0);
    auto fvec348 = [flut348](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut348[i](I));
        return ret;
    };

    std::cerr << "\rLUT348   ";
    Ciphertext gin348 = 1 * gout347[0] + 2 * gout155[0] + 4 * gout55[0];
    std::vector<Ciphertext> gout348 = ctx.eval_lut_amortized(&gin348, lut348);

    std::vector<RotationPoly> lut349;
    std::vector<long (*)(long)> flut349;
    auto lut349idx0 = [](long I) -> long {
        /* GATE 183 (LUT3 _1210_ INIT 0x35 PERM 102) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut349.push_back(ctx.genrate_lut(lut349idx0));
    flut349.push_back(lut349idx0);
    auto fvec349 = [flut349](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut349[i](I));
        return ret;
    };

    std::cerr << "\rLUT349   ";
    Ciphertext gin349 = 1 * gout341[0] + 2 * gout123[0] + 4 * gout55[0];
    std::vector<Ciphertext> gout349 = ctx.eval_lut_amortized(&gin349, lut349);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(ctx.decrypt(&gout346[0])); /* out0 */
    test_out.push_back(ctx.decrypt(&gout292[0])); /* out1 */
    test_out.push_back(ctx.decrypt(&gout308[0])); /* out2 */
    test_out.push_back(ctx.decrypt(&gout305[0])); /* out3 */
    test_out.push_back(ctx.decrypt(&gout303[0])); /* out4 */
    test_out.push_back(ctx.decrypt(&gout317[0])); /* out5 */
    test_out.push_back(ctx.decrypt(&gout289[0])); /* out6 */
    test_out.push_back(ctx.decrypt(&gout326[0])); /* out7 */
    test_out.push_back(ctx.decrypt(&gout342[0])); /* out8 */
    test_out.push_back(ctx.decrypt(&gout310[0])); /* out9 */
    test_out.push_back(ctx.decrypt(&gout348[0])); /* out10 */
    test_out.push_back(ctx.decrypt(&gout321[0])); /* out11 */
    test_out.push_back(ctx.decrypt(&gout344[0])); /* out12 */
    test_out.push_back(ctx.decrypt(&gout316[0])); /* out13 */
    test_out.push_back(ctx.decrypt(&gout324[0])); /* out14 */
    test_out.push_back(ctx.decrypt(&gout349[0])); /* out15 */
    test_out.push_back(ctx.decrypt(&gout275[0])); /* out16 */
    test_out.push_back(ctx.decrypt(&gout333[0])); /* out17 */
    test_out.push_back(ctx.decrypt(&gout212[0])); /* out18 */
    test_out.push_back(ctx.decrypt(&gout332[0])); /* out19 */
    test_out.push_back(ctx.decrypt(&gout281[0])); /* out20 */
    test_out.push_back(ctx.decrypt(&gout283[0])); /* out21 */
    test_out.push_back(ctx.decrypt(&gout291[0])); /* out22 */
    test_out.push_back(ctx.decrypt(&gout245[0])); /* out23 */
    test_out.push_back(ctx.decrypt(&gout319[0])); /* out24 */
    test_out.push_back(ctx.decrypt(&gout320[0])); /* out25 */
    test_out.push_back(ctx.decrypt(&gout258[0])); /* out26 */
    test_out.push_back(ctx.decrypt(&gout271[0])); /* out27 */
    test_out.push_back(ctx.decrypt(&gout314[0])); /* out28 */
    test_out.push_back(ctx.decrypt(&gout330[0])); /* out29 */
    test_out.push_back(ctx.decrypt(&gout311[0])); /* out30 */
    test_out.push_back(ctx.decrypt(&gout338[0])); /* out31 */
    test_out.push_back(ctx.decrypt(&gout337[0])); /* out32 */
    test_out.push_back(ctx.decrypt(&gout328[0])); /* out33 */
    test_out.push_back(ctx.decrypt(&gout331[0])); /* out34 */
    test_out.push_back(ctx.decrypt(&gout336[0])); /* out35 */
    test_out.push_back(ctx.decrypt(&gout339[0])); /* out36 */
    test_out.push_back(ctx.decrypt(&gout340[0])); /* out37 */
    test_out.push_back(ctx.decrypt(&gout343[0])); /* out38 */
    test_out.push_back(ctx.decrypt(&gout345[0])); /* out39 */
    test_out.push_back(ctx.decrypt(&gout296[0])); /* out40 */
    test_out.push_back(ctx.decrypt(&gout322[0])); /* out41 */
    test_out.push_back(ctx.decrypt(&gout246[0])); /* out42 */
    test_out.push_back(ctx.decrypt(&gout249[0])); /* out43 */
    test_out.push_back(ctx.decrypt(&gout248[0])); /* out44 */
    test_out.push_back(ctx.decrypt(&gout299[0])); /* out45 */
    test_out.push_back(ctx.decrypt(&gout270[0])); /* out46 */
    test_out.push_back(ctx.decrypt(&gout269[0])); /* out47 */
    test_out.push_back(ctx.decrypt(&gout265[0])); /* out48 */
    test_out.push_back(ctx.decrypt(&gout174[0])); /* out49 */
    test_out.push_back(ctx.decrypt(&gout251[0])); /* out50 */
    test_out.push_back(ctx.decrypt(&gout149[0])); /* out51 */
    test_out.push_back(ctx.decrypt(&gout169[0])); /* out52 */
    test_out.push_back(ctx.decrypt(&gout166[0])); /* out53 */
    test_out.push_back(ctx.decrypt(&gout181[0])); /* out54 */
    test_out.push_back(ctx.decrypt(&gout146[0])); /* out55 */
    test_out.push_back(ctx.decrypt(&gout63[0])); /* out56 */
    test_out.push_back(ctx.decrypt(&gout69[0])); /* out57 */
    test_out.push_back(ctx.decrypt(&gout104[0])); /* out58 */
    test_out.push_back(ctx.decrypt(&gout61[0])); /* out59 */
    test_out.push_back(ctx.decrypt(&gout59[0])); /* out60 */
    test_out.push_back(ctx.decrypt(&gout95[0])); /* out61 */
    test_out.push_back(ctx.decrypt(&gout58[0])); /* out62 */
    test_out.push_back(ctx.decrypt(&gout96[0])); /* out63 */
    return test_out;
}

static void
BM_strrev_lut3(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(rlwe_hom_acc_scheme_C_11_NTT);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(8);

    for (auto _ : state) {
        test_strrev_lut3(ctx);
    }
}

BENCHMARK(BM_strrev_lut3)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();