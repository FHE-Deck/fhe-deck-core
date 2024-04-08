#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_sum3d_lut2(FHEContext& ctx, std::vector<uint64_t> out = { 0 })
{
    Ciphertext ct_out0 = ctx.encrypt_public((out[0] >> 0) & 1);
    Ciphertext ct_out1 = ctx.encrypt_public((out[0] >> 1) & 1);
    Ciphertext ct_out2 = ctx.encrypt_public((out[0] >> 2) & 1);
    Ciphertext ct_out3 = ctx.encrypt_public((out[0] >> 3) & 1);
    Ciphertext ct_out4 = ctx.encrypt_public((out[0] >> 4) & 1);
    Ciphertext ct_out5 = ctx.encrypt_public((out[0] >> 5) & 1);
    Ciphertext ct_out6 = ctx.encrypt_public((out[0] >> 6) & 1);
    Ciphertext ct_out7 = ctx.encrypt_public((out[0] >> 7) & 1);
    Ciphertext ct_out8 = ctx.encrypt_public((out[0] >> 8) & 1);
    Ciphertext ct_out9 = ctx.encrypt_public((out[0] >> 9) & 1);
    Ciphertext ct_out10 = ctx.encrypt_public((out[0] >> 10) & 1);
    Ciphertext ct_out11 = ctx.encrypt_public((out[0] >> 11) & 1);
    Ciphertext ct_out12 = ctx.encrypt_public((out[0] >> 12) & 1);
    Ciphertext ct_out13 = ctx.encrypt_public((out[0] >> 13) & 1);
    Ciphertext ct_out14 = ctx.encrypt_public((out[0] >> 14) & 1);
    Ciphertext ct_out15 = ctx.encrypt_public((out[0] >> 15) & 1);
    Ciphertext ct_out16 = ctx.encrypt_public((out[0] >> 16) & 1);
    Ciphertext ct_out17 = ctx.encrypt_public((out[0] >> 17) & 1);
    Ciphertext ct_out18 = ctx.encrypt_public((out[0] >> 18) & 1);
    Ciphertext ct_out19 = ctx.encrypt_public((out[0] >> 19) & 1);
    Ciphertext ct_out20 = ctx.encrypt_public((out[0] >> 20) & 1);
    Ciphertext ct_out21 = ctx.encrypt_public((out[0] >> 21) & 1);
    Ciphertext ct_out22 = ctx.encrypt_public((out[0] >> 22) & 1);
    Ciphertext ct_out23 = ctx.encrypt_public((out[0] >> 23) & 1);
    Ciphertext ct_out24 = ctx.encrypt_public((out[0] >> 24) & 1);
    Ciphertext ct_out25 = ctx.encrypt_public((out[0] >> 25) & 1);
    Ciphertext ct_out26 = ctx.encrypt_public((out[0] >> 26) & 1);
    Ciphertext ct_out27 = ctx.encrypt_public((out[0] >> 27) & 1);
    Ciphertext ct_out28 = ctx.encrypt_public((out[0] >> 28) & 1);
    Ciphertext ct_out29 = ctx.encrypt_public((out[0] >> 29) & 1);
    Ciphertext ct_out30 = ctx.encrypt_public((out[0] >> 30) & 1);
    Ciphertext ct_out31 = ctx.encrypt_public((out[0] >> 31) & 1);
    Ciphertext ct_out32 = ctx.encrypt_public((out[0] >> 32) & 1);
    Ciphertext ct_out33 = ctx.encrypt_public((out[0] >> 33) & 1);
    Ciphertext ct_out34 = ctx.encrypt_public((out[0] >> 34) & 1);
    Ciphertext ct_out35 = ctx.encrypt_public((out[0] >> 35) & 1);
    Ciphertext ct_out36 = ctx.encrypt_public((out[0] >> 36) & 1);
    Ciphertext ct_out37 = ctx.encrypt_public((out[0] >> 37) & 1);
    Ciphertext ct_out38 = ctx.encrypt_public((out[0] >> 38) & 1);
    Ciphertext ct_out39 = ctx.encrypt_public((out[0] >> 39) & 1);
    Ciphertext ct_out40 = ctx.encrypt_public((out[0] >> 40) & 1);
    Ciphertext ct_out41 = ctx.encrypt_public((out[0] >> 41) & 1);
    Ciphertext ct_out42 = ctx.encrypt_public((out[0] >> 42) & 1);
    Ciphertext ct_out43 = ctx.encrypt_public((out[0] >> 43) & 1);
    Ciphertext ct_out44 = ctx.encrypt_public((out[0] >> 44) & 1);
    Ciphertext ct_out45 = ctx.encrypt_public((out[0] >> 45) & 1);
    Ciphertext ct_out46 = ctx.encrypt_public((out[0] >> 46) & 1);
    Ciphertext ct_out47 = ctx.encrypt_public((out[0] >> 47) & 1);
    Ciphertext ct_out48 = ctx.encrypt_public((out[0] >> 48) & 1);
    Ciphertext ct_out49 = ctx.encrypt_public((out[0] >> 49) & 1);
    Ciphertext ct_out50 = ctx.encrypt_public((out[0] >> 50) & 1);
    Ciphertext ct_out51 = ctx.encrypt_public((out[0] >> 51) & 1);
    Ciphertext ct_out52 = ctx.encrypt_public((out[0] >> 52) & 1);
    Ciphertext ct_out53 = ctx.encrypt_public((out[0] >> 53) & 1);
    Ciphertext ct_out54 = ctx.encrypt_public((out[0] >> 54) & 1);
    Ciphertext ct_out55 = ctx.encrypt_public((out[0] >> 55) & 1);
    Ciphertext ct_out56 = ctx.encrypt_public((out[0] >> 56) & 1);
    Ciphertext ct_out57 = ctx.encrypt_public((out[0] >> 57) & 1);
    Ciphertext ct_out58 = ctx.encrypt_public((out[0] >> 58) & 1);
    Ciphertext ct_out59 = ctx.encrypt_public((out[0] >> 59) & 1);
    Ciphertext ct_out60 = ctx.encrypt_public((out[0] >> 60) & 1);
    Ciphertext ct_out61 = ctx.encrypt_public((out[0] >> 61) & 1);
    Ciphertext ct_out62 = ctx.encrypt_public((out[0] >> 62) & 1);
    Ciphertext ct_out63 = ctx.encrypt_public((out[0] >> 63) & 1);
    Ciphertext ct_out64 = ctx.encrypt_public((out[1] >> 0) & 1);
    Ciphertext ct_out65 = ctx.encrypt_public((out[1] >> 1) & 1);
    Ciphertext ct_out66 = ctx.encrypt_public((out[1] >> 2) & 1);
    Ciphertext ct_out67 = ctx.encrypt_public((out[1] >> 3) & 1);
    Ciphertext ct_out68 = ctx.encrypt_public((out[1] >> 4) & 1);
    Ciphertext ct_out69 = ctx.encrypt_public((out[1] >> 5) & 1);
    Ciphertext ct_out70 = ctx.encrypt_public((out[1] >> 6) & 1);
    Ciphertext ct_out71 = ctx.encrypt_public((out[1] >> 7) & 1);
    Ciphertext ct_out72 = ctx.encrypt_public((out[1] >> 8) & 1);
    Ciphertext ct_out73 = ctx.encrypt_public((out[1] >> 9) & 1);
    Ciphertext ct_out74 = ctx.encrypt_public((out[1] >> 10) & 1);
    Ciphertext ct_out75 = ctx.encrypt_public((out[1] >> 11) & 1);
    Ciphertext ct_out76 = ctx.encrypt_public((out[1] >> 12) & 1);
    Ciphertext ct_out77 = ctx.encrypt_public((out[1] >> 13) & 1);
    Ciphertext ct_out78 = ctx.encrypt_public((out[1] >> 14) & 1);
    Ciphertext ct_out79 = ctx.encrypt_public((out[1] >> 15) & 1);
    Ciphertext ct_out80 = ctx.encrypt_public((out[1] >> 16) & 1);
    Ciphertext ct_out81 = ctx.encrypt_public((out[1] >> 17) & 1);
    Ciphertext ct_out82 = ctx.encrypt_public((out[1] >> 18) & 1);
    Ciphertext ct_out83 = ctx.encrypt_public((out[1] >> 19) & 1);
    Ciphertext ct_out84 = ctx.encrypt_public((out[1] >> 20) & 1);
    Ciphertext ct_out85 = ctx.encrypt_public((out[1] >> 21) & 1);
    Ciphertext ct_out86 = ctx.encrypt_public((out[1] >> 22) & 1);
    Ciphertext ct_out87 = ctx.encrypt_public((out[1] >> 23) & 1);
    Ciphertext ct_out88 = ctx.encrypt_public((out[1] >> 24) & 1);
    Ciphertext ct_out89 = ctx.encrypt_public((out[1] >> 25) & 1);
    Ciphertext ct_out90 = ctx.encrypt_public((out[1] >> 26) & 1);
    Ciphertext ct_out91 = ctx.encrypt_public((out[1] >> 27) & 1);
    Ciphertext ct_out92 = ctx.encrypt_public((out[1] >> 28) & 1);
    Ciphertext ct_out93 = ctx.encrypt_public((out[1] >> 29) & 1);
    Ciphertext ct_out94 = ctx.encrypt_public((out[1] >> 30) & 1);
    Ciphertext ct_out95 = ctx.encrypt_public((out[1] >> 31) & 1);
    Ciphertext ct_out96 = ctx.encrypt_public((out[1] >> 32) & 1);
    Ciphertext ct_out97 = ctx.encrypt_public((out[1] >> 33) & 1);
    Ciphertext ct_out98 = ctx.encrypt_public((out[1] >> 34) & 1);
    Ciphertext ct_out99 = ctx.encrypt_public((out[1] >> 35) & 1);
    Ciphertext ct_out100 = ctx.encrypt_public((out[1] >> 36) & 1);
    Ciphertext ct_out101 = ctx.encrypt_public((out[1] >> 37) & 1);
    Ciphertext ct_out102 = ctx.encrypt_public((out[1] >> 38) & 1);
    Ciphertext ct_out103 = ctx.encrypt_public((out[1] >> 39) & 1);
    Ciphertext ct_out104 = ctx.encrypt_public((out[1] >> 40) & 1);
    Ciphertext ct_out105 = ctx.encrypt_public((out[1] >> 41) & 1);
    Ciphertext ct_out106 = ctx.encrypt_public((out[1] >> 42) & 1);
    Ciphertext ct_out107 = ctx.encrypt_public((out[1] >> 43) & 1);
    Ciphertext ct_out108 = ctx.encrypt_public((out[1] >> 44) & 1);
    Ciphertext ct_out109 = ctx.encrypt_public((out[1] >> 45) & 1);
    Ciphertext ct_out110 = ctx.encrypt_public((out[1] >> 46) & 1);
    Ciphertext ct_out111 = ctx.encrypt_public((out[1] >> 47) & 1);
    Ciphertext ct_out112 = ctx.encrypt_public((out[1] >> 48) & 1);
    Ciphertext ct_out113 = ctx.encrypt_public((out[1] >> 49) & 1);
    Ciphertext ct_out114 = ctx.encrypt_public((out[1] >> 50) & 1);
    Ciphertext ct_out115 = ctx.encrypt_public((out[1] >> 51) & 1);
    Ciphertext ct_out116 = ctx.encrypt_public((out[1] >> 52) & 1);
    Ciphertext ct_out117 = ctx.encrypt_public((out[1] >> 53) & 1);
    Ciphertext ct_out118 = ctx.encrypt_public((out[1] >> 54) & 1);
    Ciphertext ct_out119 = ctx.encrypt_public((out[1] >> 55) & 1);
    Ciphertext ct_out120 = ctx.encrypt_public((out[1] >> 56) & 1);
    Ciphertext ct_out121 = ctx.encrypt_public((out[1] >> 57) & 1);
    Ciphertext ct_out122 = ctx.encrypt_public((out[1] >> 58) & 1);
    Ciphertext ct_out123 = ctx.encrypt_public((out[1] >> 59) & 1);
    Ciphertext ct_out124 = ctx.encrypt_public((out[1] >> 60) & 1);
    Ciphertext ct_out125 = ctx.encrypt_public((out[1] >> 61) & 1);
    Ciphertext ct_out126 = ctx.encrypt_public((out[1] >> 62) & 1);
    Ciphertext ct_out127 = ctx.encrypt_public((out[1] >> 63) & 1);
    Ciphertext ct_out128 = ctx.encrypt_public((out[2] >> 0) & 1);
    Ciphertext ct_out129 = ctx.encrypt_public((out[2] >> 1) & 1);
    Ciphertext ct_out130 = ctx.encrypt_public((out[2] >> 2) & 1);
    Ciphertext ct_out131 = ctx.encrypt_public((out[2] >> 3) & 1);
    Ciphertext ct_out132 = ctx.encrypt_public((out[2] >> 4) & 1);
    Ciphertext ct_out133 = ctx.encrypt_public((out[2] >> 5) & 1);
    Ciphertext ct_out134 = ctx.encrypt_public((out[2] >> 6) & 1);
    Ciphertext ct_out135 = ctx.encrypt_public((out[2] >> 7) & 1);
    Ciphertext ct_out136 = ctx.encrypt_public((out[2] >> 8) & 1);
    Ciphertext ct_out137 = ctx.encrypt_public((out[2] >> 9) & 1);
    Ciphertext ct_out138 = ctx.encrypt_public((out[2] >> 10) & 1);
    Ciphertext ct_out139 = ctx.encrypt_public((out[2] >> 11) & 1);
    Ciphertext ct_out140 = ctx.encrypt_public((out[2] >> 12) & 1);
    Ciphertext ct_out141 = ctx.encrypt_public((out[2] >> 13) & 1);
    Ciphertext ct_out142 = ctx.encrypt_public((out[2] >> 14) & 1);
    Ciphertext ct_out143 = ctx.encrypt_public((out[2] >> 15) & 1);
    Ciphertext ct_out144 = ctx.encrypt_public((out[2] >> 16) & 1);
    Ciphertext ct_out145 = ctx.encrypt_public((out[2] >> 17) & 1);
    Ciphertext ct_out146 = ctx.encrypt_public((out[2] >> 18) & 1);
    Ciphertext ct_out147 = ctx.encrypt_public((out[2] >> 19) & 1);
    Ciphertext ct_out148 = ctx.encrypt_public((out[2] >> 20) & 1);
    Ciphertext ct_out149 = ctx.encrypt_public((out[2] >> 21) & 1);
    Ciphertext ct_out150 = ctx.encrypt_public((out[2] >> 22) & 1);
    Ciphertext ct_out151 = ctx.encrypt_public((out[2] >> 23) & 1);
    Ciphertext ct_out152 = ctx.encrypt_public((out[2] >> 24) & 1);
    Ciphertext ct_out153 = ctx.encrypt_public((out[2] >> 25) & 1);
    Ciphertext ct_out154 = ctx.encrypt_public((out[2] >> 26) & 1);
    Ciphertext ct_out155 = ctx.encrypt_public((out[2] >> 27) & 1);
    Ciphertext ct_out156 = ctx.encrypt_public((out[2] >> 28) & 1);
    Ciphertext ct_out157 = ctx.encrypt_public((out[2] >> 29) & 1);
    Ciphertext ct_out158 = ctx.encrypt_public((out[2] >> 30) & 1);
    Ciphertext ct_out159 = ctx.encrypt_public((out[2] >> 31) & 1);
    Ciphertext ct_out160 = ctx.encrypt_public((out[2] >> 32) & 1);
    Ciphertext ct_out161 = ctx.encrypt_public((out[2] >> 33) & 1);
    Ciphertext ct_out162 = ctx.encrypt_public((out[2] >> 34) & 1);
    Ciphertext ct_out163 = ctx.encrypt_public((out[2] >> 35) & 1);
    Ciphertext ct_out164 = ctx.encrypt_public((out[2] >> 36) & 1);
    Ciphertext ct_out165 = ctx.encrypt_public((out[2] >> 37) & 1);
    Ciphertext ct_out166 = ctx.encrypt_public((out[2] >> 38) & 1);
    Ciphertext ct_out167 = ctx.encrypt_public((out[2] >> 39) & 1);
    Ciphertext ct_out168 = ctx.encrypt_public((out[2] >> 40) & 1);
    Ciphertext ct_out169 = ctx.encrypt_public((out[2] >> 41) & 1);
    Ciphertext ct_out170 = ctx.encrypt_public((out[2] >> 42) & 1);
    Ciphertext ct_out171 = ctx.encrypt_public((out[2] >> 43) & 1);
    Ciphertext ct_out172 = ctx.encrypt_public((out[2] >> 44) & 1);
    Ciphertext ct_out173 = ctx.encrypt_public((out[2] >> 45) & 1);
    Ciphertext ct_out174 = ctx.encrypt_public((out[2] >> 46) & 1);
    Ciphertext ct_out175 = ctx.encrypt_public((out[2] >> 47) & 1);
    Ciphertext ct_out176 = ctx.encrypt_public((out[2] >> 48) & 1);
    Ciphertext ct_out177 = ctx.encrypt_public((out[2] >> 49) & 1);
    Ciphertext ct_out178 = ctx.encrypt_public((out[2] >> 50) & 1);
    Ciphertext ct_out179 = ctx.encrypt_public((out[2] >> 51) & 1);
    Ciphertext ct_out180 = ctx.encrypt_public((out[2] >> 52) & 1);
    Ciphertext ct_out181 = ctx.encrypt_public((out[2] >> 53) & 1);
    Ciphertext ct_out182 = ctx.encrypt_public((out[2] >> 54) & 1);
    Ciphertext ct_out183 = ctx.encrypt_public((out[2] >> 55) & 1);
    Ciphertext ct_out184 = ctx.encrypt_public((out[2] >> 56) & 1);
    Ciphertext ct_out185 = ctx.encrypt_public((out[2] >> 57) & 1);
    Ciphertext ct_out186 = ctx.encrypt_public((out[2] >> 58) & 1);
    Ciphertext ct_out187 = ctx.encrypt_public((out[2] >> 59) & 1);
    Ciphertext ct_out188 = ctx.encrypt_public((out[2] >> 60) & 1);
    Ciphertext ct_out189 = ctx.encrypt_public((out[2] >> 61) & 1);
    Ciphertext ct_out190 = ctx.encrypt_public((out[2] >> 62) & 1);
    Ciphertext ct_out191 = ctx.encrypt_public((out[2] >> 63) & 1);

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
        /* GATE 136 (LUT2 _2900_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut0.push_back(ctx.genrate_lut(lut0idx0));
    flut0.push_back(lut0idx0);
    auto lut0idx1 = [](long I) -> long {
        /* GATE 48 (LUT2 _2812_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin0 = 1 * ct_out145 + 2 * ct_out153;
    std::vector<Ciphertext> gout0 = ctx.eval_lut_amortized(&gin0, lut0);

    std::vector<RotationPoly> lut1;
    std::vector<long (*)(long)> flut1;
    auto lut1idx0 = [](long I) -> long {
        /* GATE 691 (LUT2 _3455_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut1.push_back(ctx.genrate_lut(lut1idx0));
    flut1.push_back(lut1idx0);
    auto lut1idx1 = [](long I) -> long {
        /* GATE 571 (LUT2 _3335_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin1 = 1 * ct_out126 + 2 * ct_out134;
    std::vector<Ciphertext> gout1 = ctx.eval_lut_amortized(&gin1, lut1);

    std::vector<RotationPoly> lut2;
    std::vector<long (*)(long)> flut2;
    auto lut2idx0 = [](long I) -> long {
        /* GATE 248 (LUT2 _3012_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut2.push_back(ctx.genrate_lut(lut2idx0));
    flut2.push_back(lut2idx0);
    auto lut2idx1 = [](long I) -> long {
        /* GATE 148 (LUT2 _2912_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin2 = 1 * ct_out170 + 2 * ct_out178;
    std::vector<Ciphertext> gout2 = ctx.eval_lut_amortized(&gin2, lut2);

    std::vector<RotationPoly> lut3;
    std::vector<long (*)(long)> flut3;
    auto lut3idx0 = [](long I) -> long {
        /* GATE 126 (LUT2 _2890_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut3.push_back(ctx.genrate_lut(lut3idx0));
    flut3.push_back(lut3idx0);
    auto lut3idx1 = [](long I) -> long {
        /* GATE 233 (LUT2 _2997_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin3 = 1 * ct_out122 + 2 * ct_out130;
    std::vector<Ciphertext> gout3 = ctx.eval_lut_amortized(&gin3, lut3);

    std::vector<RotationPoly> lut4;
    std::vector<long (*)(long)> flut4;
    auto lut4idx0 = [](long I) -> long {
        /* GATE 512 (LUT2 _3276_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut4.push_back(ctx.genrate_lut(lut4idx0));
    flut4.push_back(lut4idx0);
    auto lut4idx1 = [](long I) -> long {
        /* GATE 641 (LUT2 _3405_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin4 = 1 * ct_out77 + 2 * ct_out85;
    std::vector<Ciphertext> gout4 = ctx.eval_lut_amortized(&gin4, lut4);

    std::vector<RotationPoly> lut5;
    std::vector<long (*)(long)> flut5;
    auto lut5idx0 = [](long I) -> long {
        /* GATE 392 (LUT2 _3156_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut5.push_back(ctx.genrate_lut(lut5idx0));
    flut5.push_back(lut5idx0);
    auto lut5idx1 = [](long I) -> long {
        /* GATE 526 (LUT2 _3290_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin5 = 1 * ct_out76 + 2 * ct_out84;
    std::vector<Ciphertext> gout5 = ctx.eval_lut_amortized(&gin5, lut5);

    std::vector<RotationPoly> lut6;
    std::vector<long (*)(long)> flut6;
    auto lut6idx0 = [](long I) -> long {
        /* GATE 383 (LUT2 _3147_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut6.push_back(ctx.genrate_lut(lut6idx0));
    flut6.push_back(lut6idx0);
    auto lut6idx1 = [](long I) -> long {
        /* GATE 272 (LUT2 _3036_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin6 = 1 * ct_out27 + 2 * ct_out35;
    std::vector<Ciphertext> gout6 = ctx.eval_lut_amortized(&gin6, lut6);

    std::vector<RotationPoly> lut7;
    std::vector<long (*)(long)> flut7;
    auto lut7idx0 = [](long I) -> long {
        /* GATE 358 (LUT2 _3122_ INIT 0x6 PERM 01) */
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
        /* GATE 476 (LUT2 _3240_ INIT 0x8 PERM 01) */
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
    Ciphertext gin7 = 1 * ct_out172 + 2 * ct_out180;
    std::vector<Ciphertext> gout7 = ctx.eval_lut_amortized(&gin7, lut7);

    std::vector<RotationPoly> lut8;
    std::vector<long (*)(long)> flut8;
    auto lut8idx0 = [](long I) -> long {
        /* GATE 147 (LUT2 _2911_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut8.push_back(ctx.genrate_lut(lut8idx0));
    flut8.push_back(lut8idx0);
    auto lut8idx1 = [](long I) -> long {
        /* GATE 247 (LUT2 _3011_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin8 = 1 * gout2[1] + 2 * ct_out186;
    std::vector<Ciphertext> gout8 = ctx.eval_lut_amortized(&gin8, lut8);

    std::vector<RotationPoly> lut9;
    std::vector<long (*)(long)> flut9;
    auto lut9idx0 = [](long I) -> long {
        /* GATE 595 (LUT2 _3359_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut9.push_back(ctx.genrate_lut(lut9idx0));
    flut9.push_back(lut9idx0);
    auto lut9idx1 = [](long I) -> long {
        /* GATE 728 (LUT2 _3492_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin9 = 1 * ct_out6 + 2 * ct_out14;
    std::vector<Ciphertext> gout9 = ctx.eval_lut_amortized(&gin9, lut9);

    std::vector<RotationPoly> lut10;
    std::vector<long (*)(long)> flut10;
    auto lut10idx0 = [](long I) -> long {
        /* GATE 623 (LUT2 _3387_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut10.push_back(ctx.genrate_lut(lut10idx0));
    flut10.push_back(lut10idx0);
    auto lut10idx1 = [](long I) -> long {
        /* GATE 510 (LUT2 _3274_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin10 = 1 * ct_out53 + 2 * ct_out61;
    std::vector<Ciphertext> gout10 = ctx.eval_lut_amortized(&gin10, lut10);

    std::vector<RotationPoly> lut11;
    std::vector<long (*)(long)> flut11;
    auto lut11idx0 = [](long I) -> long {
        /* GATE 235 (LUT2 _2999_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut11.push_back(ctx.genrate_lut(lut11idx0));
    flut11.push_back(lut11idx0);
    auto lut11idx1 = [](long I) -> long {
        /* GATE 346 (LUT2 _3110_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut11.push_back(ctx.genrate_lut(lut11idx1));
    flut11.push_back(lut11idx1);
    auto fvec11 = [flut11](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut11[i](I));
        return ret;
    };

    std::cerr << "\rLUT11   ";
    Ciphertext gin11 = 1 * ct_out147 + 2 * ct_out155;
    std::vector<Ciphertext> gout11 = ctx.eval_lut_amortized(&gin11, lut11);

    std::vector<RotationPoly> lut12;
    std::vector<long (*)(long)> flut12;
    auto lut12idx0 = [](long I) -> long {
        /* GATE 19 (LUT2 _2783_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut12.push_back(ctx.genrate_lut(lut12idx0));
    flut12.push_back(lut12idx0);
    auto lut12idx1 = [](long I) -> long {
        /* GATE 81 (LUT2 _2845_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut12.push_back(ctx.genrate_lut(lut12idx1));
    flut12.push_back(lut12idx1);
    auto fvec12 = [flut12](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut12[i](I));
        return ret;
    };

    std::cerr << "\rLUT12   ";
    Ciphertext gin12 = 1 * ct_out48 + 2 * ct_out56;
    std::vector<Ciphertext> gout12 = ctx.eval_lut_amortized(&gin12, lut12);

    std::vector<RotationPoly> lut13;
    std::vector<long (*)(long)> flut13;
    auto lut13idx0 = [](long I) -> long {
        /* GATE 13 (LUT2 _2777_ INIT 0x6 PERM 01) */
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
        /* GATE 58 (LUT2 _2822_ INIT 0x8 PERM 01) */
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
    Ciphertext gin13 = 1 * ct_out168 + 2 * ct_out176;
    std::vector<Ciphertext> gout13 = ctx.eval_lut_amortized(&gin13, lut13);

    std::vector<RotationPoly> lut14;
    std::vector<long (*)(long)> flut14;
    auto lut14idx0 = [](long I) -> long {
        /* GATE 454 (LUT2 _3218_ INIT 0x6 PERM 01) */
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
        /* GATE 567 (LUT2 _3331_ INIT 0x8 PERM 01) */
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
    Ciphertext gin14 = 1 * ct_out101 + 2 * ct_out109;
    std::vector<Ciphertext> gout14 = ctx.eval_lut_amortized(&gin14, lut14);

    std::vector<RotationPoly> lut15;
    std::vector<long (*)(long)> flut15;
    auto lut15idx0 = [](long I) -> long {
        /* GATE 125 (LUT2 _2889_ INIT 0x6 PERM 01) */
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
        /* GATE 232 (LUT2 _2996_ INIT 0x8 PERM 01) */
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
    Ciphertext gin15 = 1 * gout3[0] + 2 * ct_out138;
    std::vector<Ciphertext> gout15 = ctx.eval_lut_amortized(&gin15, lut15);

    std::vector<RotationPoly> lut16;
    std::vector<long (*)(long)> flut16;
    auto lut16idx0 = [](long I) -> long {
        /* GATE 6 (LUT2 _2770_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut16.push_back(ctx.genrate_lut(lut16idx0));
    flut16.push_back(lut16idx0);
    auto lut16idx1 = [](long I) -> long {
        /* GATE 36 (LUT2 _2800_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut16.push_back(ctx.genrate_lut(lut16idx1));
    flut16.push_back(lut16idx1);
    auto fvec16 = [flut16](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut16[i](I));
        return ret;
    };

    std::cerr << "\rLUT16   ";
    Ciphertext gin16 = 1 * ct_out96 + 2 * ct_out104;
    std::vector<Ciphertext> gout16 = ctx.eval_lut_amortized(&gin16, lut16);

    std::vector<RotationPoly> lut17;
    std::vector<long (*)(long)> flut17;
    auto lut17idx0 = [](long I) -> long {
        /* GATE 456 (LUT2 _3220_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut17.push_back(ctx.genrate_lut(lut17idx0));
    flut17.push_back(lut17idx0);
    auto lut17idx1 = [](long I) -> long {
        /* GATE 576 (LUT2 _3340_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut17.push_back(ctx.genrate_lut(lut17idx1));
    flut17.push_back(lut17idx1);
    auto fvec17 = [flut17](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut17[i](I));
        return ret;
    };

    std::cerr << "\rLUT17   ";
    Ciphertext gin17 = 1 * ct_out125 + 2 * ct_out133;
    std::vector<Ciphertext> gout17 = ctx.eval_lut_amortized(&gin17, lut17);

    std::vector<RotationPoly> lut18;
    std::vector<long (*)(long)> flut18;
    auto lut18idx0 = [](long I) -> long {
        /* GATE 131 (LUT2 _2895_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut18.push_back(ctx.genrate_lut(lut18idx0));
    flut18.push_back(lut18idx0);
    auto lut18idx1 = [](long I) -> long {
        /* GATE 40 (LUT2 _2804_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut18.push_back(ctx.genrate_lut(lut18idx1));
    flut18.push_back(lut18idx1);
    auto fvec18 = [flut18](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut18[i](I));
        return ret;
    };

    std::cerr << "\rLUT18   ";
    Ciphertext gin18 = 1 * ct_out121 + 2 * ct_out129;
    std::vector<Ciphertext> gout18 = ctx.eval_lut_amortized(&gin18, lut18);

    std::vector<RotationPoly> lut19;
    std::vector<long (*)(long)> flut19;
    auto lut19idx0 = [](long I) -> long {
        /* GATE 8 (LUT2 _2772_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut19.push_back(ctx.genrate_lut(lut19idx0));
    flut19.push_back(lut19idx0);
    auto lut19idx1 = [](long I) -> long {
        /* GATE 46 (LUT2 _2810_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut19.push_back(ctx.genrate_lut(lut19idx1));
    flut19.push_back(lut19idx1);
    auto fvec19 = [flut19](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut19[i](I));
        return ret;
    };

    std::cerr << "\rLUT19   ";
    Ciphertext gin19 = 1 * ct_out120 + 2 * ct_out128;
    std::vector<Ciphertext> gout19 = ctx.eval_lut_amortized(&gin19, lut19);

    std::vector<RotationPoly> lut20;
    std::vector<long (*)(long)> flut20;
    auto lut20idx0 = [](long I) -> long {
        /* GATE 569 (LUT2 _3333_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut20.push_back(ctx.genrate_lut(lut20idx0));
    flut20.push_back(lut20idx0);
    auto lut20idx1 = [](long I) -> long {
        /* GATE 682 (LUT2 _3446_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut20.push_back(ctx.genrate_lut(lut20idx1));
    flut20.push_back(lut20idx1);
    auto fvec20 = [flut20](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut20[i](I));
        return ret;
    };

    std::cerr << "\rLUT20   ";
    Ciphertext gin20 = 1 * ct_out102 + 2 * ct_out110;
    std::vector<Ciphertext> gout20 = ctx.eval_lut_amortized(&gin20, lut20);

    std::vector<RotationPoly> lut21;
    std::vector<long (*)(long)> flut21;
    auto lut21idx0 = [](long I) -> long {
        /* GATE 60 (LUT2 _2824_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut21.push_back(ctx.genrate_lut(lut21idx0));
    flut21.push_back(lut21idx0);
    auto lut21idx1 = [](long I) -> long {
        /* GATE 146 (LUT2 _2910_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut21.push_back(ctx.genrate_lut(lut21idx1));
    flut21.push_back(lut21idx1);
    auto fvec21 = [flut21](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut21[i](I));
        return ret;
    };

    std::cerr << "\rLUT21   ";
    Ciphertext gin21 = 1 * ct_out169 + 2 * ct_out177;
    std::vector<Ciphertext> gout21 = ctx.eval_lut_amortized(&gin21, lut21);

    std::vector<RotationPoly> lut22;
    std::vector<long (*)(long)> flut22;
    auto lut22idx0 = [](long I) -> long {
        /* GATE 833 (LUT2 _3597_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut22.push_back(ctx.genrate_lut(lut22idx0));
    flut22.push_back(lut22idx0);
    auto lut22idx1 = [](long I) -> long {
        /* GATE 740 (LUT2 _3504_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut22.push_back(ctx.genrate_lut(lut22idx1));
    flut22.push_back(lut22idx1);
    auto fvec22 = [flut22](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut22[i](I));
        return ret;
    };

    std::cerr << "\rLUT22   ";
    Ciphertext gin22 = 1 * ct_out55 + 2 * ct_out63;
    std::vector<Ciphertext> gout22 = ctx.eval_lut_amortized(&gin22, lut22);

    std::vector<RotationPoly> lut23;
    std::vector<long (*)(long)> flut23;
    auto lut23idx0 = [](long I) -> long {
        /* GATE 570 (LUT2 _3334_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut23.push_back(ctx.genrate_lut(lut23idx0));
    flut23.push_back(lut23idx0);
    auto lut23idx1 = [](long I) -> long {
        /* GATE 690 (LUT2 _3454_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut23.push_back(ctx.genrate_lut(lut23idx1));
    flut23.push_back(lut23idx1);
    auto fvec23 = [flut23](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut23[i](I));
        return ret;
    };

    std::cerr << "\rLUT23   ";
    Ciphertext gin23 = 1 * gout1[1] + 2 * ct_out142;
    std::vector<Ciphertext> gout23 = ctx.eval_lut_amortized(&gin23, lut23);

    std::vector<RotationPoly> lut24;
    std::vector<long (*)(long)> flut24;
    auto lut24idx0 = [](long I) -> long {
        /* GATE 135 (LUT2 _2899_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut24.push_back(ctx.genrate_lut(lut24idx0));
    flut24.push_back(lut24idx0);
    auto lut24idx1 = [](long I) -> long {
        /* GATE 47 (LUT2 _2811_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut24.push_back(ctx.genrate_lut(lut24idx1));
    flut24.push_back(lut24idx1);
    auto fvec24 = [flut24](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut24[i](I));
        return ret;
    };

    std::cerr << "\rLUT24   ";
    Ciphertext gin24 = 1 * gout0[1] + 2 * ct_out161;
    std::vector<Ciphertext> gout24 = ctx.eval_lut_amortized(&gin24, lut24);

    std::vector<RotationPoly> lut25;
    std::vector<long (*)(long)> flut25;
    auto lut25idx0 = [](long I) -> long {
        /* GATE 503 (LUT2 _3267_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut25.push_back(ctx.genrate_lut(lut25idx0));
    flut25.push_back(lut25idx0);
    auto lut25idx1 = [](long I) -> long {
        /* GATE 380 (LUT2 _3144_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut25.push_back(ctx.genrate_lut(lut25idx1));
    flut25.push_back(lut25idx1);
    auto fvec25 = [flut25](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut25[i](I));
        return ret;
    };

    std::cerr << "\rLUT25   ";
    Ciphertext gin25 = 1 * ct_out28 + 2 * ct_out36;
    std::vector<Ciphertext> gout25 = ctx.eval_lut_amortized(&gin25, lut25);

    std::vector<RotationPoly> lut26;
    std::vector<long (*)(long)> flut26;
    auto lut26idx0 = [](long I) -> long {
        /* GATE 742 (LUT2 _3506_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut26.push_back(ctx.genrate_lut(lut26idx0));
    flut26.push_back(lut26idx0);
    auto lut26idx1 = [](long I) -> long {
        /* GATE 847 (LUT2 _3611_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut26.push_back(ctx.genrate_lut(lut26idx1));
    flut26.push_back(lut26idx1);
    auto fvec26 = [flut26](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut26[i](I));
        return ret;
    };

    std::cerr << "\rLUT26   ";
    Ciphertext gin26 = 1 * ct_out79 + 2 * ct_out87;
    std::vector<Ciphertext> gout26 = ctx.eval_lut_amortized(&gin26, lut26);

    std::vector<RotationPoly> lut27;
    std::vector<long (*)(long)> flut27;
    auto lut27idx0 = [](long I) -> long {
        /* GATE 10 (LUT2 _2774_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut27.push_back(ctx.genrate_lut(lut27idx0));
    flut27.push_back(lut27idx0);
    auto lut27idx1 = [](long I) -> long {
        /* GATE 51 (LUT2 _2815_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin27 = 1 * ct_out144 + 2 * ct_out152;
    std::vector<Ciphertext> gout27 = ctx.eval_lut_amortized(&gin27, lut27);

    std::vector<RotationPoly> lut28;
    std::vector<long (*)(long)> flut28;
    auto lut28idx0 = [](long I) -> long {
        /* GATE 525 (LUT2 _3289_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut28.push_back(ctx.genrate_lut(lut28idx0));
    flut28.push_back(lut28idx0);
    auto lut28idx1 = [](long I) -> long {
        /* GATE 391 (LUT2 _3155_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut28.push_back(ctx.genrate_lut(lut28idx1));
    flut28.push_back(lut28idx1);
    auto fvec28 = [flut28](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut28[i](I));
        return ret;
    };

    std::cerr << "\rLUT28   ";
    Ciphertext gin28 = 1 * gout5[0] + 2 * ct_out92;
    std::vector<Ciphertext> gout28 = ctx.eval_lut_amortized(&gin28, lut28);

    std::vector<RotationPoly> lut29;
    std::vector<long (*)(long)> flut29;
    auto lut29idx0 = [](long I) -> long {
        /* GATE 124 (LUT2 _2888_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut29.push_back(ctx.genrate_lut(lut29idx0));
    flut29.push_back(lut29idx0);
    auto lut29idx1 = [](long I) -> long {
        /* GATE 224 (LUT2 _2988_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut29.push_back(ctx.genrate_lut(lut29idx1));
    flut29.push_back(lut29idx1);
    auto fvec29 = [flut29](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut29[i](I));
        return ret;
    };

    std::cerr << "\rLUT29   ";
    Ciphertext gin29 = 1 * ct_out98 + 2 * ct_out106;
    std::vector<Ciphertext> gout29 = ctx.eval_lut_amortized(&gin29, lut29);

    std::vector<RotationPoly> lut30;
    std::vector<long (*)(long)> flut30;
    auto lut30idx0 = [](long I) -> long {
        /* GATE 357 (LUT2 _3121_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut30.push_back(ctx.genrate_lut(lut30idx0));
    flut30.push_back(lut30idx0);
    auto lut30idx1 = [](long I) -> long {
        /* GATE 475 (LUT2 _3239_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut30.push_back(ctx.genrate_lut(lut30idx1));
    flut30.push_back(lut30idx1);
    auto fvec30 = [flut30](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut30[i](I));
        return ret;
    };

    std::cerr << "\rLUT30   ";
    Ciphertext gin30 = 1 * gout7[0] + 2 * ct_out188;
    std::vector<Ciphertext> gout30 = ctx.eval_lut_amortized(&gin30, lut30);

    std::vector<RotationPoly> lut31;
    std::vector<long (*)(long)> flut31;
    auto lut31idx0 = [](long I) -> long {
        /* GATE 453 (LUT2 _3217_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut31.push_back(ctx.genrate_lut(lut31idx0));
    flut31.push_back(lut31idx0);
    auto lut31idx1 = [](long I) -> long {
        /* GATE 566 (LUT2 _3330_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
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
    Ciphertext gin31 = 1 * gout14[0] + 2 * ct_out117;
    std::vector<Ciphertext> gout31 = ctx.eval_lut_amortized(&gin31, lut31);

    std::vector<RotationPoly> lut32;
    std::vector<long (*)(long)> flut32;
    auto lut32idx0 = [](long I) -> long {
        /* GATE 85 (LUT2 _2849_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut32.push_back(ctx.genrate_lut(lut32idx0));
    flut32.push_back(lut32idx0);
    auto lut32idx1 = [](long I) -> long {
        /* GATE 190 (LUT2 _2954_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut32.push_back(ctx.genrate_lut(lut32idx1));
    flut32.push_back(lut32idx1);
    auto fvec32 = [flut32](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut32[i](I));
        return ret;
    };

    std::cerr << "\rLUT32   ";
    Ciphertext gin32 = 1 * ct_out73 + 2 * ct_out81;
    std::vector<Ciphertext> gout32 = ctx.eval_lut_amortized(&gin32, lut32);

    std::vector<RotationPoly> lut33;
    std::vector<long (*)(long)> flut33;
    auto lut33idx0 = [](long I) -> long {
        /* GATE 7 (LUT2 _2771_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut33.push_back(ctx.genrate_lut(lut33idx0));
    flut33.push_back(lut33idx0);
    auto lut33idx1 = [](long I) -> long {
        /* GATE 45 (LUT2 _2809_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut33.push_back(ctx.genrate_lut(lut33idx1));
    flut33.push_back(lut33idx1);
    auto fvec33 = [flut33](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut33[i](I));
        return ret;
    };

    std::cerr << "\rLUT33   ";
    Ciphertext gin33 = 1 * gout19[0] + 2 * ct_out136;
    std::vector<Ciphertext> gout33 = ctx.eval_lut_amortized(&gin33, lut33);

    std::vector<RotationPoly> lut34;
    std::vector<long (*)(long)> flut34;
    auto lut34idx0 = [](long I) -> long {
        /* GATE 336 (LUT2 _3100_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut34.push_back(ctx.genrate_lut(lut34idx0));
    flut34.push_back(lut34idx0);
    auto lut34idx1 = [](long I) -> long {
        /* GATE 461 (LUT2 _3225_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut34.push_back(ctx.genrate_lut(lut34idx1));
    flut34.push_back(lut34idx1);
    auto fvec34 = [flut34](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut34[i](I));
        return ret;
    };

    std::cerr << "\rLUT34   ";
    Ciphertext gin34 = 1 * ct_out124 + 2 * ct_out132;
    std::vector<Ciphertext> gout34 = ctx.eval_lut_amortized(&gin34, lut34);

    std::vector<RotationPoly> lut35;
    std::vector<long (*)(long)> flut35;
    auto lut35idx0 = [](long I) -> long {
        /* GATE 727 (LUT2 _3491_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut35.push_back(ctx.genrate_lut(lut35idx0));
    flut35.push_back(lut35idx0);
    auto lut35idx1 = [](long I) -> long {
        /* GATE 594 (LUT2 _3358_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut35.push_back(ctx.genrate_lut(lut35idx1));
    flut35.push_back(lut35idx1);
    auto fvec35 = [flut35](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut35[i](I));
        return ret;
    };

    std::cerr << "\rLUT35   ";
    Ciphertext gin35 = 1 * gout9[0] + 2 * ct_out22;
    std::vector<Ciphertext> gout35 = ctx.eval_lut_amortized(&gin35, lut35);

    std::vector<RotationPoly> lut36;
    std::vector<long (*)(long)> flut36;
    auto lut36idx0 = [](long I) -> long {
        /* GATE 524 (LUT2 _3288_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin36 = 1 * gout28[0] + 2 * gout5[1];
    std::vector<Ciphertext> gout36 = ctx.eval_lut_amortized(&gin36, lut36);

    std::vector<RotationPoly> lut37;
    std::vector<long (*)(long)> flut37;
    auto lut37idx0 = [](long I) -> long {
        /* GATE 133 (LUT2 _2897_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut37.push_back(ctx.genrate_lut(lut37idx0));
    flut37.push_back(lut37idx0);
    auto lut37idx1 = [](long I) -> long {
        /* GATE 238 (LUT2 _3002_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin37 = 1 * ct_out146 + 2 * ct_out154;
    std::vector<Ciphertext> gout37 = ctx.eval_lut_amortized(&gin37, lut37);

    std::vector<RotationPoly> lut38;
    std::vector<long (*)(long)> flut38;
    auto lut38idx0 = [](long I) -> long {
        /* GATE 627 (LUT2 _3391_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut38.push_back(ctx.genrate_lut(lut38idx0));
    flut38.push_back(lut38idx0);
    auto lut38idx1 = [](long I) -> long {
        /* GATE 756 (LUT2 _3520_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut38.push_back(ctx.genrate_lut(lut38idx1));
    flut38.push_back(lut38idx1);
    auto fvec38 = [flut38](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut38[i](I));
        return ret;
    };

    std::cerr << "\rLUT38   ";
    Ciphertext gin38 = 1 * ct_out78 + 2 * ct_out86;
    std::vector<Ciphertext> gout38 = ctx.eval_lut_amortized(&gin38, lut38);

    std::vector<RotationPoly> lut39;
    std::vector<long (*)(long)> flut39;
    auto lut39idx0 = [](long I) -> long {
        /* GATE 452 (LUT2 _3216_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut39.push_back(ctx.genrate_lut(lut39idx0));
    flut39.push_back(lut39idx0);
    auto lut39idx1 = [](long I) -> long {
        /* GATE 334 (LUT2 _3098_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut39.push_back(ctx.genrate_lut(lut39idx1));
    flut39.push_back(lut39idx1);
    auto fvec39 = [flut39](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut39[i](I));
        return ret;
    };

    std::cerr << "\rLUT39   ";
    Ciphertext gin39 = 1 * ct_out100 + 2 * ct_out108;
    std::vector<Ciphertext> gout39 = ctx.eval_lut_amortized(&gin39, lut39);

    std::vector<RotationPoly> lut40;
    std::vector<long (*)(long)> flut40;
    auto lut40idx0 = [](long I) -> long {
        /* GATE 388 (LUT2 _3152_ INIT 0x8 PERM 01) */
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
    auto lut40idx1 = [](long I) -> long {
        /* GATE 282 (LUT2 _3046_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut40.push_back(ctx.genrate_lut(lut40idx1));
    flut40.push_back(lut40idx1);
    auto fvec40 = [flut40](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut40[i](I));
        return ret;
    };

    std::cerr << "\rLUT40   ";
    Ciphertext gin40 = 1 * ct_out51 + 2 * ct_out59;
    std::vector<Ciphertext> gout40 = ctx.eval_lut_amortized(&gin40, lut40);

    std::vector<RotationPoly> lut41;
    std::vector<long (*)(long)> flut41;
    auto lut41idx0 = [](long I) -> long {
        /* GATE 686 (LUT2 _3450_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut41.push_back(ctx.genrate_lut(lut41idx0));
    flut41.push_back(lut41idx0);
    auto lut41idx1 = [](long I) -> long {
        /* GATE 799 (LUT2 _3563_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut41.push_back(ctx.genrate_lut(lut41idx1));
    flut41.push_back(lut41idx1);
    auto fvec41 = [flut41](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut41[i](I));
        return ret;
    };

    std::cerr << "\rLUT41   ";
    Ciphertext gin41 = 1 * ct_out127 + 2 * ct_out135;
    std::vector<Ciphertext> gout41 = ctx.eval_lut_amortized(&gin41, lut41);

    std::vector<RotationPoly> lut42;
    std::vector<long (*)(long)> flut42;
    auto lut42idx0 = [](long I) -> long {
        /* GATE 795 (LUT2 _3559_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut42.push_back(ctx.genrate_lut(lut42idx0));
    flut42.push_back(lut42idx0);
    auto lut42idx1 = [](long I) -> long {
        /* GATE 684 (LUT2 _3448_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut42.push_back(ctx.genrate_lut(lut42idx1));
    flut42.push_back(lut42idx1);
    auto fvec42 = [flut42](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut42[i](I));
        return ret;
    };

    std::cerr << "\rLUT42   ";
    Ciphertext gin42 = 1 * ct_out103 + 2 * ct_out111;
    std::vector<Ciphertext> gout42 = ctx.eval_lut_amortized(&gin42, lut42);

    std::vector<RotationPoly> lut43;
    std::vector<long (*)(long)> flut43;
    auto lut43idx0 = [](long I) -> long {
        /* GATE 270 (LUT2 _3034_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut43.push_back(ctx.genrate_lut(lut43idx0));
    flut43.push_back(lut43idx0);
    auto lut43idx1 = [](long I) -> long {
        /* GATE 150 (LUT2 _2914_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut43.push_back(ctx.genrate_lut(lut43idx1));
    flut43.push_back(lut43idx1);
    auto fvec43 = [flut43](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut43[i](I));
        return ret;
    };

    std::cerr << "\rLUT43   ";
    Ciphertext gin43 = 1 * ct_out2 + 2 * ct_out10;
    std::vector<Ciphertext> gout43 = ctx.eval_lut_amortized(&gin43, lut43);

    std::vector<RotationPoly> lut44;
    std::vector<long (*)(long)> flut44;
    auto lut44idx0 = [](long I) -> long {
        /* GATE 502 (LUT2 _3266_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut44.push_back(ctx.genrate_lut(lut44idx0));
    flut44.push_back(lut44idx0);
    auto lut44idx1 = [](long I) -> long {
        /* GATE 379 (LUT2 _3143_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut44.push_back(ctx.genrate_lut(lut44idx1));
    flut44.push_back(lut44idx1);
    auto fvec44 = [flut44](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut44[i](I));
        return ret;
    };

    std::cerr << "\rLUT44   ";
    Ciphertext gin44 = 1 * gout25[1] + 2 * ct_out44;
    std::vector<Ciphertext> gout44 = ctx.eval_lut_amortized(&gin44, lut44);

    std::vector<RotationPoly> lut45;
    std::vector<long (*)(long)> flut45;
    auto lut45idx0 = [](long I) -> long {
        /* GATE 466 (LUT2 _3230_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut45.push_back(ctx.genrate_lut(lut45idx0));
    flut45.push_back(lut45idx0);
    auto lut45idx1 = [](long I) -> long {
        /* GATE 343 (LUT2 _3107_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut45.push_back(ctx.genrate_lut(lut45idx1));
    flut45.push_back(lut45idx1);
    auto fvec45 = [flut45](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut45[i](I));
        return ret;
    };

    std::cerr << "\rLUT45   ";
    Ciphertext gin45 = 1 * ct_out148 + 2 * ct_out156;
    std::vector<Ciphertext> gout45 = ctx.eval_lut_amortized(&gin45, lut45);

    std::vector<RotationPoly> lut46;
    std::vector<long (*)(long)> flut46;
    auto lut46idx0 = [](long I) -> long {
        /* GATE 23 (LUT2 _2787_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut46.push_back(ctx.genrate_lut(lut46idx0));
    flut46.push_back(lut46idx0);
    auto lut46idx1 = [](long I) -> long {
        /* GATE 76 (LUT2 _2840_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut46.push_back(ctx.genrate_lut(lut46idx1));
    flut46.push_back(lut46idx1);
    auto fvec46 = [flut46](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut46[i](I));
        return ret;
    };

    std::cerr << "\rLUT46   ";
    Ciphertext gin46 = 1 * ct_out24 + 2 * ct_out32;
    std::vector<Ciphertext> gout46 = ctx.eval_lut_amortized(&gin46, lut46);

    std::vector<RotationPoly> lut47;
    std::vector<long (*)(long)> flut47;
    auto lut47idx0 = [](long I) -> long {
        /* GATE 509 (LUT2 _3273_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut47.push_back(ctx.genrate_lut(lut47idx0));
    flut47.push_back(lut47idx0);
    auto lut47idx1 = [](long I) -> long {
        /* GATE 622 (LUT2 _3386_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin47 = 1 * gout10[1] + 2 * ct_out69;
    std::vector<Ciphertext> gout47 = ctx.eval_lut_amortized(&gin47, lut47);

    std::vector<RotationPoly> lut48;
    std::vector<long (*)(long)> flut48;
    auto lut48idx0 = [](long I) -> long {
        /* GATE 177 (LUT2 _2941_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut48.push_back(ctx.genrate_lut(lut48idx0));
    flut48.push_back(lut48idx0);
    auto lut48idx1 = [](long I) -> long {
        /* GATE 280 (LUT2 _3044_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut48.push_back(ctx.genrate_lut(lut48idx1));
    flut48.push_back(lut48idx1);
    auto fvec48 = [flut48](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut48[i](I));
        return ret;
    };

    std::cerr << "\rLUT48   ";
    Ciphertext gin48 = 1 * ct_out50 + 2 * ct_out58;
    std::vector<Ciphertext> gout48 = ctx.eval_lut_amortized(&gin48, lut48);

    std::vector<RotationPoly> lut49;
    std::vector<long (*)(long)> flut49;
    auto lut49idx0 = [](long I) -> long {
        /* GATE 71 (LUT2 _2835_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut49.push_back(ctx.genrate_lut(lut49idx0));
    flut49.push_back(lut49idx0);
    auto lut49idx1 = [](long I) -> long {
        /* GATE 15 (LUT2 _2779_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin49 = 1 * ct_out0 + 2 * ct_out8;
    std::vector<Ciphertext> gout49 = ctx.eval_lut_amortized(&gin49, lut49);

    std::vector<RotationPoly> lut50;
    std::vector<long (*)(long)> flut50;
    auto lut50idx0 = [](long I) -> long {
        /* GATE 478 (LUT2 _3242_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut50.push_back(ctx.genrate_lut(lut50idx0));
    flut50.push_back(lut50idx0);
    auto lut50idx1 = [](long I) -> long {
        /* GATE 591 (LUT2 _3355_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
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
    Ciphertext gin50 = 1 * ct_out173 + 2 * ct_out181;
    std::vector<Ciphertext> gout50 = ctx.eval_lut_amortized(&gin50, lut50);

    std::vector<RotationPoly> lut51;
    std::vector<long (*)(long)> flut51;
    auto lut51idx0 = [](long I) -> long {
        /* GATE 21 (LUT2 _2785_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut51.push_back(ctx.genrate_lut(lut51idx0));
    flut51.push_back(lut51idx0);
    auto lut51idx1 = [](long I) -> long {
        /* GATE 92 (LUT2 _2856_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut51.push_back(ctx.genrate_lut(lut51idx1));
    flut51.push_back(lut51idx1);
    auto fvec51 = [flut51](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut51[i](I));
        return ret;
    };

    std::cerr << "\rLUT51   ";
    Ciphertext gin51 = 1 * ct_out72 + 2 * ct_out80;
    std::vector<Ciphertext> gout51 = ctx.eval_lut_amortized(&gin51, lut51);

    std::vector<RotationPoly> lut52;
    std::vector<long (*)(long)> flut52;
    auto lut52idx0 = [](long I) -> long {
        /* GATE 39 (LUT2 _2803_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut52.push_back(ctx.genrate_lut(lut52idx0));
    flut52.push_back(lut52idx0);
    auto lut52idx1 = [](long I) -> long {
        /* GATE 130 (LUT2 _2894_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut52.push_back(ctx.genrate_lut(lut52idx1));
    flut52.push_back(lut52idx1);
    auto fvec52 = [flut52](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut52[i](I));
        return ret;
    };

    std::cerr << "\rLUT52   ";
    Ciphertext gin52 = 1 * gout18[1] + 2 * ct_out137;
    std::vector<Ciphertext> gout52 = ctx.eval_lut_amortized(&gin52, lut52);

    std::vector<RotationPoly> lut53;
    std::vector<long (*)(long)> flut53;
    auto lut53idx0 = [](long I) -> long {
        /* GATE 689 (LUT2 _3453_ INIT 0x1 PERM 01) */
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
    Ciphertext gin53 = 1 * gout23[1] + 2 * gout1[0];
    std::vector<Ciphertext> gout53 = ctx.eval_lut_amortized(&gin53, lut53);

    std::vector<RotationPoly> lut54;
    std::vector<long (*)(long)> flut54;
    auto lut54idx0 = [](long I) -> long {
        /* GATE 726 (LUT2 _3490_ INIT 0x1 PERM 01) */
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
    Ciphertext gin54 = 1 * gout35[0] + 2 * gout9[1];
    std::vector<Ciphertext> gout54 = ctx.eval_lut_amortized(&gin54, lut54);

    std::vector<RotationPoly> lut55;
    std::vector<long (*)(long)> flut55;
    auto lut55idx0 = [](long I) -> long {
        /* GATE 830 (LUT2 _3594_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut55.push_back(ctx.genrate_lut(lut55idx0));
    flut55.push_back(lut55idx0);
    auto lut55idx1 = [](long I) -> long {
        /* GATE 730 (LUT2 _3494_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut55.push_back(ctx.genrate_lut(lut55idx1));
    flut55.push_back(lut55idx1);
    auto fvec55 = [flut55](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut55[i](I));
        return ret;
    };

    std::cerr << "\rLUT55   ";
    Ciphertext gin55 = 1 * ct_out31 + 2 * ct_out39;
    std::vector<Ciphertext> gout55 = ctx.eval_lut_amortized(&gin55, lut55);

    std::vector<RotationPoly> lut56;
    std::vector<long (*)(long)> flut56;
    auto lut56idx0 = [](long I) -> long {
        /* GATE 356 (LUT2 _3120_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut56.push_back(ctx.genrate_lut(lut56idx0));
    flut56.push_back(lut56idx0);
    auto lut56idx1 = [](long I) -> long {
        /* GATE 250 (LUT2 _3014_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin56 = 1 * ct_out171 + 2 * ct_out179;
    std::vector<Ciphertext> gout56 = ctx.eval_lut_amortized(&gin56, lut56);

    std::vector<RotationPoly> lut57;
    std::vector<long (*)(long)> flut57;
    auto lut57idx0 = [](long I) -> long {
        /* GATE 738 (LUT2 _3502_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut57.push_back(ctx.genrate_lut(lut57idx0));
    flut57.push_back(lut57idx0);
    auto lut57idx1 = [](long I) -> long {
        /* GATE 625 (LUT2 _3389_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut57.push_back(ctx.genrate_lut(lut57idx1));
    flut57.push_back(lut57idx1);
    auto fvec57 = [flut57](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut57[i](I));
        return ret;
    };

    std::cerr << "\rLUT57   ";
    Ciphertext gin57 = 1 * ct_out54 + 2 * ct_out62;
    std::vector<Ciphertext> gout57 = ctx.eval_lut_amortized(&gin57, lut57);

    std::vector<RotationPoly> lut58;
    std::vector<long (*)(long)> flut58;
    auto lut58idx0 = [](long I) -> long {
        /* GATE 681 (LUT2 _3445_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut58.push_back(ctx.genrate_lut(lut58idx0));
    flut58.push_back(lut58idx0);
    auto lut58idx1 = [](long I) -> long {
        /* GATE 568 (LUT2 _3332_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut58.push_back(ctx.genrate_lut(lut58idx1));
    flut58.push_back(lut58idx1);
    auto fvec58 = [flut58](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut58[i](I));
        return ret;
    };

    std::cerr << "\rLUT58   ";
    Ciphertext gin58 = 1 * gout20[0] + 2 * ct_out118;
    std::vector<Ciphertext> gout58 = ctx.eval_lut_amortized(&gin58, lut58);

    std::vector<RotationPoly> lut59;
    std::vector<long (*)(long)> flut59;
    auto lut59idx0 = [](long I) -> long {
        /* GATE 18 (LUT2 _2782_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut59.push_back(ctx.genrate_lut(lut59idx0));
    flut59.push_back(lut59idx0);
    auto lut59idx1 = [](long I) -> long {
        /* GATE 80 (LUT2 _2844_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut59.push_back(ctx.genrate_lut(lut59idx1));
    flut59.push_back(lut59idx1);
    auto fvec59 = [flut59](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut59[i](I));
        return ret;
    };

    std::cerr << "\rLUT59   ";
    Ciphertext gin59 = 1 * gout12[0] + 2 * ct_out64;
    std::vector<Ciphertext> gout59 = ctx.eval_lut_amortized(&gin59, lut59);

    std::vector<RotationPoly> lut60;
    std::vector<long (*)(long)> flut60;
    auto lut60idx0 = [](long I) -> long {
        /* GATE 167 (LUT2 _2931_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut60.push_back(ctx.genrate_lut(lut60idx0));
    flut60.push_back(lut60idx0);
    auto lut60idx1 = [](long I) -> long {
        /* GATE 275 (LUT2 _3039_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut60.push_back(ctx.genrate_lut(lut60idx1));
    flut60.push_back(lut60idx1);
    auto fvec60 = [flut60](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut60[i](I));
        return ret;
    };

    std::cerr << "\rLUT60   ";
    Ciphertext gin60 = 1 * ct_out26 + 2 * ct_out34;
    std::vector<Ciphertext> gout60 = ctx.eval_lut_amortized(&gin60, lut60);

    std::vector<RotationPoly> lut61;
    std::vector<long (*)(long)> flut61;
    auto lut61idx0 = [](long I) -> long {
        /* GATE 335 (LUT2 _3099_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut61.push_back(ctx.genrate_lut(lut61idx0));
    flut61.push_back(lut61idx0);
    auto lut61idx1 = [](long I) -> long {
        /* GATE 460 (LUT2 _3224_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut61.push_back(ctx.genrate_lut(lut61idx1));
    flut61.push_back(lut61idx1);
    auto fvec61 = [flut61](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut61[i](I));
        return ret;
    };

    std::cerr << "\rLUT61   ";
    Ciphertext gin61 = 1 * gout34[0] + 2 * ct_out140;
    std::vector<Ciphertext> gout61 = ctx.eval_lut_amortized(&gin61, lut61);

    std::vector<RotationPoly> lut62;
    std::vector<long (*)(long)> flut62;
    auto lut62idx0 = [](long I) -> long {
        /* GATE 378 (LUT2 _3142_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut62.push_back(ctx.genrate_lut(lut62idx0));
    flut62.push_back(lut62idx0);
    auto lut62idx1 = [](long I) -> long {
        /* GATE 252 (LUT2 _3016_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut62.push_back(ctx.genrate_lut(lut62idx1));
    flut62.push_back(lut62idx1);
    auto fvec62 = [flut62](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut62[i](I));
        return ret;
    };

    std::cerr << "\rLUT62   ";
    Ciphertext gin62 = 1 * ct_out3 + 2 * ct_out11;
    std::vector<Ciphertext> gout62 = ctx.eval_lut_amortized(&gin62, lut62);

    std::vector<RotationPoly> lut63;
    std::vector<long (*)(long)> flut63;
    auto lut63idx0 = [](long I) -> long {
        /* GATE 626 (LUT2 _3390_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut63.push_back(ctx.genrate_lut(lut63idx0));
    flut63.push_back(lut63idx0);
    auto lut63idx1 = [](long I) -> long {
        /* GATE 755 (LUT2 _3519_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut63.push_back(ctx.genrate_lut(lut63idx1));
    flut63.push_back(lut63idx1);
    auto fvec63 = [flut63](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut63[i](I));
        return ret;
    };

    std::cerr << "\rLUT63   ";
    Ciphertext gin63 = 1 * gout38[0] + 2 * ct_out94;
    std::vector<Ciphertext> gout63 = ctx.eval_lut_amortized(&gin63, lut63);

    std::vector<RotationPoly> lut64;
    std::vector<long (*)(long)> flut64;
    auto lut64idx0 = [](long I) -> long {
        /* GATE 79 (LUT2 _2843_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin64 = 1 * gout59[1] + 2 * gout12[1];
    std::vector<Ciphertext> gout64 = ctx.eval_lut_amortized(&gin64, lut64);

    std::vector<RotationPoly> lut65;
    std::vector<long (*)(long)> flut65;
    auto lut65idx0 = [](long I) -> long {
        /* GATE 5 (LUT2 _2769_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut65.push_back(ctx.genrate_lut(lut65idx0));
    flut65.push_back(lut65idx0);
    auto lut65idx1 = [](long I) -> long {
        /* GATE 35 (LUT2 _2799_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut65.push_back(ctx.genrate_lut(lut65idx1));
    flut65.push_back(lut65idx1);
    auto fvec65 = [flut65](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut65[i](I));
        return ret;
    };

    std::cerr << "\rLUT65   ";
    Ciphertext gin65 = 1 * gout16[0] + 2 * ct_out112;
    std::vector<Ciphertext> gout65 = ctx.eval_lut_amortized(&gin65, lut65);

    std::vector<RotationPoly> lut66;
    std::vector<long (*)(long)> flut66;
    auto lut66idx0 = [](long I) -> long {
        /* GATE 62 (LUT2 _2826_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut66.push_back(ctx.genrate_lut(lut66idx0));
    flut66.push_back(lut66idx0);
    auto lut66idx1 = [](long I) -> long {
        /* GATE 165 (LUT2 _2929_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut66.push_back(ctx.genrate_lut(lut66idx1));
    flut66.push_back(lut66idx1);
    auto fvec66 = [flut66](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut66[i](I));
        return ret;
    };

    std::cerr << "\rLUT66   ";
    Ciphertext gin66 = 1 * ct_out1 + 2 * ct_out9;
    std::vector<Ciphertext> gout66 = ctx.eval_lut_amortized(&gin66, lut66);

    std::vector<RotationPoly> lut67;
    std::vector<long (*)(long)> flut67;
    auto lut67idx0 = [](long I) -> long {
        /* GATE 729 (LUT2 _3493_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut67.push_back(ctx.genrate_lut(lut67idx0));
    flut67.push_back(lut67idx0);
    auto lut67idx1 = [](long I) -> long {
        /* GATE 829 (LUT2 _3593_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut67.push_back(ctx.genrate_lut(lut67idx1));
    flut67.push_back(lut67idx1);
    auto fvec67 = [flut67](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut67[i](I));
        return ret;
    };

    std::cerr << "\rLUT67   ";
    Ciphertext gin67 = 1 * gout55[1] + 2 * ct_out47;
    std::vector<Ciphertext> gout67 = ctx.eval_lut_amortized(&gin67, lut67);

    std::vector<RotationPoly> lut68;
    std::vector<long (*)(long)> flut68;
    auto lut68idx0 = [](long I) -> long {
        /* GATE 59 (LUT2 _2823_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut68.push_back(ctx.genrate_lut(lut68idx0));
    flut68.push_back(lut68idx0);
    auto lut68idx1 = [](long I) -> long {
        /* GATE 145 (LUT2 _2909_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut68.push_back(ctx.genrate_lut(lut68idx1));
    flut68.push_back(lut68idx1);
    auto fvec68 = [flut68](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut68[i](I));
        return ret;
    };

    std::cerr << "\rLUT68   ";
    Ciphertext gin68 = 1 * gout21[0] + 2 * ct_out185;
    std::vector<Ciphertext> gout68 = ctx.eval_lut_amortized(&gin68, lut68);

    std::vector<RotationPoly> lut69;
    std::vector<long (*)(long)> flut69;
    auto lut69idx0 = [](long I) -> long {
        /* GATE 91 (LUT2 _2855_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut69.push_back(ctx.genrate_lut(lut69idx0));
    flut69.push_back(lut69idx0);
    auto lut69idx1 = [](long I) -> long {
        /* GATE 20 (LUT2 _2784_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut69.push_back(ctx.genrate_lut(lut69idx1));
    flut69.push_back(lut69idx1);
    auto fvec69 = [flut69](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut69[i](I));
        return ret;
    };

    std::cerr << "\rLUT69   ";
    Ciphertext gin69 = 1 * gout51[0] + 2 * ct_out88;
    std::vector<Ciphertext> gout69 = ctx.eval_lut_amortized(&gin69, lut69);

    std::vector<RotationPoly> lut70;
    std::vector<long (*)(long)> flut70;
    auto lut70idx0 = [](long I) -> long {
        /* GATE 298 (LUT2 _3062_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut70.push_back(ctx.genrate_lut(lut70idx0));
    flut70.push_back(lut70idx0);
    auto lut70idx1 = [](long I) -> long {
        /* GATE 179 (LUT2 _2943_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut70.push_back(ctx.genrate_lut(lut70idx1));
    flut70.push_back(lut70idx1);
    auto fvec70 = [flut70](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut70[i](I));
        return ret;
    };

    std::cerr << "\rLUT70   ";
    Ciphertext gin70 = 1 * ct_out74 + 2 * ct_out82;
    std::vector<Ciphertext> gout70 = ctx.eval_lut_amortized(&gin70, lut70);

    std::vector<RotationPoly> lut71;
    std::vector<long (*)(long)> flut71;
    auto lut71idx0 = [](long I) -> long {
        /* GATE 57 (LUT2 _2821_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut71.push_back(ctx.genrate_lut(lut71idx0));
    flut71.push_back(lut71idx0);
    auto lut71idx1 = [](long I) -> long {
        /* GATE 12 (LUT2 _2776_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut71.push_back(ctx.genrate_lut(lut71idx1));
    flut71.push_back(lut71idx1);
    auto fvec71 = [flut71](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut71[i](I));
        return ret;
    };

    std::cerr << "\rLUT71   ";
    Ciphertext gin71 = 1 * gout13[0] + 2 * ct_out184;
    std::vector<Ciphertext> gout71 = ctx.eval_lut_amortized(&gin71, lut71);

    std::vector<RotationPoly> lut72;
    std::vector<long (*)(long)> flut72;
    auto lut72idx0 = [](long I) -> long {
        /* GATE 38 (LUT2 _2802_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut72.push_back(ctx.genrate_lut(lut72idx0));
    flut72.push_back(lut72idx0);
    auto lut72idx1 = [](long I) -> long {
        /* GATE 122 (LUT2 _2886_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut72.push_back(ctx.genrate_lut(lut72idx1));
    flut72.push_back(lut72idx1);
    auto fvec72 = [flut72](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut72[i](I));
        return ret;
    };

    std::cerr << "\rLUT72   ";
    Ciphertext gin72 = 1 * ct_out97 + 2 * ct_out105;
    std::vector<Ciphertext> gout72 = ctx.eval_lut_amortized(&gin72, lut72);

    std::vector<RotationPoly> lut73;
    std::vector<long (*)(long)> flut73;
    auto lut73idx0 = [](long I) -> long {
        /* GATE 575 (LUT2 _3339_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut73.push_back(ctx.genrate_lut(lut73idx0));
    flut73.push_back(lut73idx0);
    auto lut73idx1 = [](long I) -> long {
        /* GATE 455 (LUT2 _3219_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut73.push_back(ctx.genrate_lut(lut73idx1));
    flut73.push_back(lut73idx1);
    auto fvec73 = [flut73](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut73[i](I));
        return ret;
    };

    std::cerr << "\rLUT73   ";
    Ciphertext gin73 = 1 * gout17[0] + 2 * ct_out141;
    std::vector<Ciphertext> gout73 = ctx.eval_lut_amortized(&gin73, lut73);

    std::vector<RotationPoly> lut74;
    std::vector<long (*)(long)> flut74;
    auto lut74idx0 = [](long I) -> long {
        /* GATE 693 (LUT2 _3457_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut74.push_back(ctx.genrate_lut(lut74idx0));
    flut74.push_back(lut74idx0);
    auto lut74idx1 = [](long I) -> long {
        /* GATE 802 (LUT2 _3566_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut74.push_back(ctx.genrate_lut(lut74idx1));
    flut74.push_back(lut74idx1);
    auto fvec74 = [flut74](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut74[i](I));
        return ret;
    };

    std::cerr << "\rLUT74   ";
    Ciphertext gin74 = 1 * ct_out151 + 2 * ct_out159;
    std::vector<Ciphertext> gout74 = ctx.eval_lut_amortized(&gin74, lut74);

    std::vector<RotationPoly> lut75;
    std::vector<long (*)(long)> flut75;
    auto lut75idx0 = [](long I) -> long {
        /* GATE 477 (LUT2 _3241_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut75.push_back(ctx.genrate_lut(lut75idx0));
    flut75.push_back(lut75idx0);
    auto lut75idx1 = [](long I) -> long {
        /* GATE 590 (LUT2 _3354_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut75.push_back(ctx.genrate_lut(lut75idx1));
    flut75.push_back(lut75idx1);
    auto fvec75 = [flut75](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut75[i](I));
        return ret;
    };

    std::cerr << "\rLUT75   ";
    Ciphertext gin75 = 1 * gout50[0] + 2 * ct_out189;
    std::vector<Ciphertext> gout75 = ctx.eval_lut_amortized(&gin75, lut75);

    std::vector<RotationPoly> lut76;
    std::vector<long (*)(long)> flut76;
    auto lut76idx0 = [](long I) -> long {
        /* GATE 733 (LUT2 _3497_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut76.push_back(ctx.genrate_lut(lut76idx0));
    flut76.push_back(lut76idx0);
    auto lut76idx1 = [](long I) -> long {
        /* GATE 615 (LUT2 _3379_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin76 = 1 * ct_out30 + 2 * ct_out38;
    std::vector<Ciphertext> gout76 = ctx.eval_lut_amortized(&gin76, lut76);

    std::vector<RotationPoly> lut77;
    std::vector<long (*)(long)> flut77;
    auto lut77idx0 = [](long I) -> long {
        /* GATE 390 (LUT2 _3154_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut77.push_back(ctx.genrate_lut(lut77idx0));
    flut77.push_back(lut77idx0);
    auto lut77idx1 = [](long I) -> long {
        /* GATE 508 (LUT2 _3272_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut77.push_back(ctx.genrate_lut(lut77idx1));
    flut77.push_back(lut77idx1);
    auto fvec77 = [flut77](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut77[i](I));
        return ret;
    };

    std::cerr << "\rLUT77   ";
    Ciphertext gin77 = 1 * ct_out52 + 2 * ct_out60;
    std::vector<Ciphertext> gout77 = ctx.eval_lut_amortized(&gin77, lut77);

    std::vector<RotationPoly> lut78;
    std::vector<long (*)(long)> flut78;
    auto lut78idx0 = [](long I) -> long {
        /* GATE 640 (LUT2 _3404_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut78.push_back(ctx.genrate_lut(lut78idx0));
    flut78.push_back(lut78idx0);
    auto lut78idx1 = [](long I) -> long {
        /* GATE 511 (LUT2 _3275_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut78.push_back(ctx.genrate_lut(lut78idx1));
    flut78.push_back(lut78idx1);
    auto fvec78 = [flut78](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut78[i](I));
        return ret;
    };

    std::cerr << "\rLUT78   ";
    Ciphertext gin78 = 1 * gout4[0] + 2 * ct_out93;
    std::vector<Ciphertext> gout78 = ctx.eval_lut_amortized(&gin78, lut78);

    std::vector<RotationPoly> lut79;
    std::vector<long (*)(long)> flut79;
    auto lut79idx0 = [](long I) -> long {
        /* GATE 129 (LUT2 _2893_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin79 = 1 * gout52[1] + 2 * gout18[0];
    std::vector<Ciphertext> gout79 = ctx.eval_lut_amortized(&gin79, lut79);

    std::vector<RotationPoly> lut80;
    std::vector<long (*)(long)> flut80;
    auto lut80idx0 = [](long I) -> long {
        /* GATE 565 (LUT2 _3329_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin80 = 1 * gout31[1] + 2 * gout14[1];
    std::vector<Ciphertext> gout80 = ctx.eval_lut_amortized(&gin80, lut80);

    std::vector<RotationPoly> lut81;
    std::vector<long (*)(long)> flut81;
    auto lut81idx0 = [](long I) -> long {
        /* GATE 123 (LUT2 _2887_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut81.push_back(ctx.genrate_lut(lut81idx0));
    flut81.push_back(lut81idx0);
    auto lut81idx1 = [](long I) -> long {
        /* GATE 223 (LUT2 _2987_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut81.push_back(ctx.genrate_lut(lut81idx1));
    flut81.push_back(lut81idx1);
    auto fvec81 = [flut81](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut81[i](I));
        return ret;
    };

    std::cerr << "\rLUT81   ";
    Ciphertext gin81 = 1 * gout29[0] + 2 * ct_out114;
    std::vector<Ciphertext> gout81 = ctx.eval_lut_amortized(&gin81, lut81);

    std::vector<RotationPoly> lut82;
    std::vector<long (*)(long)> flut82;
    auto lut82idx0 = [](long I) -> long {
        /* GATE 846 (LUT2 _3610_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut82.push_back(ctx.genrate_lut(lut82idx0));
    flut82.push_back(lut82idx0);
    auto lut82idx1 = [](long I) -> long {
        /* GATE 741 (LUT2 _3505_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut82.push_back(ctx.genrate_lut(lut82idx1));
    flut82.push_back(lut82idx1);
    auto fvec82 = [flut82](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut82[i](I));
        return ret;
    };

    std::cerr << "\rLUT82   ";
    Ciphertext gin82 = 1 * gout26[0] + 2 * ct_out95;
    std::vector<Ciphertext> gout82 = ctx.eval_lut_amortized(&gin82, lut82);

    std::vector<RotationPoly> lut83;
    std::vector<long (*)(long)> flut83;
    auto lut83idx0 = [](long I) -> long {
        /* GATE 231 (LUT2 _2995_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin83 = 1 * gout15[1] + 2 * gout3[1];
    std::vector<Ciphertext> gout83 = ctx.eval_lut_amortized(&gin83, lut83);

    std::vector<RotationPoly> lut84;
    std::vector<long (*)(long)> flut84;
    auto lut84idx0 = [](long I) -> long {
        /* GATE 17 (LUT2 _2781_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut84.push_back(ctx.genrate_lut(lut84idx0));
    flut84.push_back(lut84idx0);
    auto lut84idx1 = [](long I) -> long {
        /* GATE 89 (LUT2 _2853_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut84.push_back(ctx.genrate_lut(lut84idx1));
    flut84.push_back(lut84idx1);
    auto fvec84 = [flut84](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut84[i](I));
        return ret;
    };

    std::cerr << "\rLUT84   ";
    Ciphertext gin84 = 1 * gout59[0] + 2 * gout69[1];
    std::vector<Ciphertext> gout84 = ctx.eval_lut_amortized(&gin84, lut84);

    std::vector<RotationPoly> lut85;
    std::vector<long (*)(long)> flut85;
    auto lut85idx0 = [](long I) -> long {
        /* GATE 574 (LUT2 _3338_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut85.push_back(ctx.genrate_lut(lut85idx0));
    flut85.push_back(lut85idx0);
    auto fvec85 = [flut85](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut85[i](I));
        return ret;
    };

    std::cerr << "\rLUT85   ";
    Ciphertext gin85 = 1 * gout73[0] + 2 * gout17[1];
    std::vector<Ciphertext> gout85 = ctx.eval_lut_amortized(&gin85, lut85);

    std::vector<RotationPoly> lut86;
    std::vector<long (*)(long)> flut86;
    auto lut86idx0 = [](long I) -> long {
        /* GATE 754 (LUT2 _3518_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin86 = 1 * gout63[1] + 2 * gout38[1];
    std::vector<Ciphertext> gout86 = ctx.eval_lut_amortized(&gin86, lut86);

    std::vector<RotationPoly> lut87;
    std::vector<long (*)(long)> flut87;
    auto lut87idx0 = [](long I) -> long {
        /* GATE 355 (LUT2 _3119_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut87.push_back(ctx.genrate_lut(lut87idx0));
    flut87.push_back(lut87idx0);
    auto lut87idx1 = [](long I) -> long {
        /* GATE 249 (LUT2 _3013_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut87.push_back(ctx.genrate_lut(lut87idx1));
    flut87.push_back(lut87idx1);
    auto fvec87 = [flut87](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut87[i](I));
        return ret;
    };

    std::cerr << "\rLUT87   ";
    Ciphertext gin87 = 1 * gout56[1] + 2 * ct_out187;
    std::vector<Ciphertext> gout87 = ctx.eval_lut_amortized(&gin87, lut87);

    std::vector<RotationPoly> lut88;
    std::vector<long (*)(long)> flut88;
    auto lut88idx0 = [](long I) -> long {
        /* GATE 613 (LUT2 _3377_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut88.push_back(ctx.genrate_lut(lut88idx0));
    flut88.push_back(lut88idx0);
    auto lut88idx1 = [](long I) -> long {
        /* GATE 480 (LUT2 _3244_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut88.push_back(ctx.genrate_lut(lut88idx1));
    flut88.push_back(lut88idx1);
    auto fvec88 = [flut88](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut88[i](I));
        return ret;
    };

    std::cerr << "\rLUT88   ";
    Ciphertext gin88 = 1 * ct_out5 + 2 * ct_out13;
    std::vector<Ciphertext> gout88 = ctx.eval_lut_amortized(&gin88, lut88);

    std::vector<RotationPoly> lut89;
    std::vector<long (*)(long)> flut89;
    auto lut89idx0 = [](long I) -> long {
        /* GATE 284 (LUT2 _3048_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut89.push_back(ctx.genrate_lut(lut89idx0));
    flut89.push_back(lut89idx0);
    auto lut89idx1 = [](long I) -> long {
        /* GATE 406 (LUT2 _3170_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut89.push_back(ctx.genrate_lut(lut89idx1));
    flut89.push_back(lut89idx1);
    auto fvec89 = [flut89](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut89[i](I));
        return ret;
    };

    std::cerr << "\rLUT89   ";
    Ciphertext gin89 = 1 * ct_out75 + 2 * ct_out83;
    std::vector<Ciphertext> gout89 = ctx.eval_lut_amortized(&gin89, lut89);

    std::vector<RotationPoly> lut90;
    std::vector<long (*)(long)> flut90;
    auto lut90idx0 = [](long I) -> long {
        /* GATE 332 (LUT2 _3096_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut90.push_back(ctx.genrate_lut(lut90idx0));
    flut90.push_back(lut90idx0);
    auto lut90idx1 = [](long I) -> long {
        /* GATE 226 (LUT2 _2990_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut90.push_back(ctx.genrate_lut(lut90idx1));
    flut90.push_back(lut90idx1);
    auto fvec90 = [flut90](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut90[i](I));
        return ret;
    };

    std::cerr << "\rLUT90   ";
    Ciphertext gin90 = 1 * ct_out99 + 2 * ct_out107;
    std::vector<Ciphertext> gout90 = ctx.eval_lut_amortized(&gin90, lut90);

    std::vector<RotationPoly> lut91;
    std::vector<long (*)(long)> flut91;
    auto lut91idx0 = [](long I) -> long {
        /* GATE 405 (LUT2 _3169_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut91.push_back(ctx.genrate_lut(lut91idx0));
    flut91.push_back(lut91idx0);
    auto lut91idx1 = [](long I) -> long {
        /* GATE 283 (LUT2 _3047_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut91.push_back(ctx.genrate_lut(lut91idx1));
    flut91.push_back(lut91idx1);
    auto fvec91 = [flut91](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut91[i](I));
        return ret;
    };

    std::cerr << "\rLUT91   ";
    Ciphertext gin91 = 1 * gout89[0] + 2 * ct_out91;
    std::vector<Ciphertext> gout91 = ctx.eval_lut_amortized(&gin91, lut91);

    std::vector<RotationPoly> lut92;
    std::vector<long (*)(long)> flut92;
    auto lut92idx0 = [](long I) -> long {
        /* GATE 84 (LUT2 _2848_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut92.push_back(ctx.genrate_lut(lut92idx0));
    flut92.push_back(lut92idx0);
    auto lut92idx1 = [](long I) -> long {
        /* GATE 189 (LUT2 _2953_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut92.push_back(ctx.genrate_lut(lut92idx1));
    flut92.push_back(lut92idx1);
    auto fvec92 = [flut92](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut92[i](I));
        return ret;
    };

    std::cerr << "\rLUT92   ";
    Ciphertext gin92 = 1 * gout32[0] + 2 * ct_out89;
    std::vector<Ciphertext> gout92 = ctx.eval_lut_amortized(&gin92, lut92);

    std::vector<RotationPoly> lut93;
    std::vector<long (*)(long)> flut93;
    auto lut93idx0 = [](long I) -> long {
        /* GATE 144 (LUT2 _2908_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin93 = 1 * gout68[1] + 2 * gout21[1];
    std::vector<Ciphertext> gout93 = ctx.eval_lut_amortized(&gin93, lut93);

    std::vector<RotationPoly> lut94;
    std::vector<long (*)(long)> flut94;
    auto lut94idx0 = [](long I) -> long {
        /* GATE 593 (LUT2 _3357_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut94.push_back(ctx.genrate_lut(lut94idx0));
    flut94.push_back(lut94idx0);
    auto lut94idx1 = [](long I) -> long {
        /* GATE 706 (LUT2 _3470_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut94.push_back(ctx.genrate_lut(lut94idx1));
    flut94.push_back(lut94idx1);
    auto fvec94 = [flut94](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut94[i](I));
        return ret;
    };

    std::cerr << "\rLUT94   ";
    Ciphertext gin94 = 1 * ct_out174 + 2 * ct_out182;
    std::vector<Ciphertext> gout94 = ctx.eval_lut_amortized(&gin94, lut94);

    std::vector<RotationPoly> lut95;
    std::vector<long (*)(long)> flut95;
    auto lut95idx0 = [](long I) -> long {
        /* GATE 134 (LUT2 _2898_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin95 = 1 * gout24[0] + 2 * gout0[0];
    std::vector<Ciphertext> gout95 = ctx.eval_lut_amortized(&gin95, lut95);

    std::vector<RotationPoly> lut96;
    std::vector<long (*)(long)> flut96;
    auto lut96idx0 = [](long I) -> long {
        /* GATE 801 (LUT2 _3565_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut96.push_back(ctx.genrate_lut(lut96idx0));
    flut96.push_back(lut96idx0);
    auto lut96idx1 = [](long I) -> long {
        /* GATE 692 (LUT2 _3456_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut96.push_back(ctx.genrate_lut(lut96idx1));
    flut96.push_back(lut96idx1);
    auto fvec96 = [flut96](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut96[i](I));
        return ret;
    };

    std::cerr << "\rLUT96   ";
    Ciphertext gin96 = 1 * gout74[0] + 2 * ct_out167;
    std::vector<Ciphertext> gout96 = ctx.eval_lut_amortized(&gin96, lut96);

    std::vector<RotationPoly> lut97;
    std::vector<long (*)(long)> flut97;
    auto lut97idx0 = [](long I) -> long {
        /* GATE 708 (LUT2 _3472_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut97.push_back(ctx.genrate_lut(lut97idx0));
    flut97.push_back(lut97idx0);
    auto lut97idx1 = [](long I) -> long {
        /* GATE 810 (LUT2 _3574_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut97.push_back(ctx.genrate_lut(lut97idx1));
    flut97.push_back(lut97idx1);
    auto fvec97 = [flut97](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut97[i](I));
        return ret;
    };

    std::cerr << "\rLUT97   ";
    Ciphertext gin97 = 1 * ct_out175 + 2 * ct_out183;
    std::vector<Ciphertext> gout97 = ctx.eval_lut_amortized(&gin97, lut97);

    std::vector<RotationPoly> lut98;
    std::vector<long (*)(long)> flut98;
    auto lut98idx0 = [](long I) -> long {
        /* GATE 132 (LUT2 _2896_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut98.push_back(ctx.genrate_lut(lut98idx0));
    flut98.push_back(lut98idx0);
    auto lut98idx1 = [](long I) -> long {
        /* GATE 237 (LUT2 _3001_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut98.push_back(ctx.genrate_lut(lut98idx1));
    flut98.push_back(lut98idx1);
    auto fvec98 = [flut98](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut98[i](I));
        return ret;
    };

    std::cerr << "\rLUT98   ";
    Ciphertext gin98 = 1 * gout37[0] + 2 * ct_out162;
    std::vector<Ciphertext> gout98 = ctx.eval_lut_amortized(&gin98, lut98);

    std::vector<RotationPoly> lut99;
    std::vector<long (*)(long)> flut99;
    auto lut99idx0 = [](long I) -> long {
        /* GATE 246 (LUT2 _3010_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin99 = 1 * gout8[1] + 2 * gout2[0];
    std::vector<Ciphertext> gout99 = ctx.eval_lut_amortized(&gin99, lut99);

    std::vector<RotationPoly> lut100;
    std::vector<long (*)(long)> flut100;
    auto lut100idx0 = [](long I) -> long {
        /* GATE 269 (LUT2 _3033_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut100.push_back(ctx.genrate_lut(lut100idx0));
    flut100.push_back(lut100idx0);
    auto lut100idx1 = [](long I) -> long {
        /* GATE 149 (LUT2 _2913_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut100.push_back(ctx.genrate_lut(lut100idx1));
    flut100.push_back(lut100idx1);
    auto fvec100 = [flut100](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut100[i](I));
        return ret;
    };

    std::cerr << "\rLUT100   ";
    Ciphertext gin100 = 1 * gout43[1] + 2 * ct_out18;
    std::vector<Ciphertext> gout100 = ctx.eval_lut_amortized(&gin100, lut100);

    std::vector<RotationPoly> lut101;
    std::vector<long (*)(long)> flut101;
    auto lut101idx0 = [](long I) -> long {
        /* GATE 589 (LUT2 _3353_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin101 = 1 * gout75[1] + 2 * gout50[1];
    std::vector<Ciphertext> gout101 = ctx.eval_lut_amortized(&gin101, lut101);

    std::vector<RotationPoly> lut102;
    std::vector<long (*)(long)> flut102;
    auto lut102idx0 = [](long I) -> long {
        /* GATE 170 (LUT2 _2934_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut102.push_back(ctx.genrate_lut(lut102idx0));
    flut102.push_back(lut102idx0);
    auto lut102idx1 = [](long I) -> long {
        /* GATE 73 (LUT2 _2837_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut102.push_back(ctx.genrate_lut(lut102idx1));
    flut102.push_back(lut102idx1);
    auto fvec102 = [flut102](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut102[i](I));
        return ret;
    };

    std::cerr << "\rLUT102   ";
    Ciphertext gin102 = 1 * ct_out25 + 2 * ct_out33;
    std::vector<Ciphertext> gout102 = ctx.eval_lut_amortized(&gin102, lut102);

    std::vector<RotationPoly> lut103;
    std::vector<long (*)(long)> flut103;
    auto lut103idx0 = [](long I) -> long {
        /* GATE 618 (LUT2 _3382_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut103.push_back(ctx.genrate_lut(lut103idx0));
    flut103.push_back(lut103idx0);
    auto lut103idx1 = [](long I) -> long {
        /* GATE 500 (LUT2 _3264_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut103.push_back(ctx.genrate_lut(lut103idx1));
    flut103.push_back(lut103idx1);
    auto fvec103 = [flut103](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut103[i](I));
        return ret;
    };

    std::cerr << "\rLUT103   ";
    Ciphertext gin103 = 1 * ct_out29 + 2 * ct_out37;
    std::vector<Ciphertext> gout103 = ctx.eval_lut_amortized(&gin103, lut103);

    std::vector<RotationPoly> lut104;
    std::vector<long (*)(long)> flut104;
    auto lut104idx0 = [](long I) -> long {
        /* GATE 581 (LUT2 _3345_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut104.push_back(ctx.genrate_lut(lut104idx0));
    flut104.push_back(lut104idx0);
    auto lut104idx1 = [](long I) -> long {
        /* GATE 463 (LUT2 _3227_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut104.push_back(ctx.genrate_lut(lut104idx1));
    flut104.push_back(lut104idx1);
    auto fvec104 = [flut104](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut104[i](I));
        return ret;
    };

    std::cerr << "\rLUT104   ";
    Ciphertext gin104 = 1 * ct_out149 + 2 * ct_out157;
    std::vector<Ciphertext> gout104 = ctx.eval_lut_amortized(&gin104, lut104);

    std::vector<RotationPoly> lut105;
    std::vector<long (*)(long)> flut105;
    auto lut105idx0 = [](long I) -> long {
        /* GATE 479 (LUT2 _3243_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut105.push_back(ctx.genrate_lut(lut105idx0));
    flut105.push_back(lut105idx0);
    auto lut105idx1 = [](long I) -> long {
        /* GATE 612 (LUT2 _3376_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut105.push_back(ctx.genrate_lut(lut105idx1));
    flut105.push_back(lut105idx1);
    auto fvec105 = [flut105](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut105[i](I));
        return ret;
    };

    std::cerr << "\rLUT105   ";
    Ciphertext gin105 = 1 * gout88[1] + 2 * ct_out21;
    std::vector<Ciphertext> gout105 = ctx.eval_lut_amortized(&gin105, lut105);

    std::vector<RotationPoly> lut106;
    std::vector<long (*)(long)> flut106;
    auto lut106idx0 = [](long I) -> long {
        /* GATE 360 (LUT2 _3124_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut106.push_back(ctx.genrate_lut(lut106idx0));
    flut106.push_back(lut106idx0);
    auto lut106idx1 = [](long I) -> long {
        /* GATE 498 (LUT2 _3262_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin106 = 1 * ct_out4 + 2 * ct_out12;
    std::vector<Ciphertext> gout106 = ctx.eval_lut_amortized(&gin106, lut106);

    std::vector<RotationPoly> lut107;
    std::vector<long (*)(long)> flut107;
    auto lut107idx0 = [](long I) -> long {
        /* GATE 83 (LUT2 _2847_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut107.push_back(ctx.genrate_lut(lut107idx0));
    flut107.push_back(lut107idx0);
    auto lut107idx1 = [](long I) -> long {
        /* GATE 175 (LUT2 _2939_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut107.push_back(ctx.genrate_lut(lut107idx1));
    flut107.push_back(lut107idx1);
    auto fvec107 = [flut107](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut107[i](I));
        return ret;
    };

    std::cerr << "\rLUT107   ";
    Ciphertext gin107 = 1 * ct_out49 + 2 * ct_out57;
    std::vector<Ciphertext> gout107 = ctx.eval_lut_amortized(&gin107, lut107);

    std::vector<RotationPoly> lut108;
    std::vector<long (*)(long)> flut108;
    auto lut108idx0 = [](long I) -> long {
        /* GATE 75 (LUT2 _2839_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut108.push_back(ctx.genrate_lut(lut108idx0));
    flut108.push_back(lut108idx0);
    auto lut108idx1 = [](long I) -> long {
        /* GATE 22 (LUT2 _2786_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut108.push_back(ctx.genrate_lut(lut108idx1));
    flut108.push_back(lut108idx1);
    auto fvec108 = [flut108](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut108[i](I));
        return ret;
    };

    std::cerr << "\rLUT108   ";
    Ciphertext gin108 = 1 * gout46[0] + 2 * ct_out40;
    std::vector<Ciphertext> gout108 = ctx.eval_lut_amortized(&gin108, lut108);

    std::vector<RotationPoly> lut109;
    std::vector<long (*)(long)> flut109;
    auto lut109idx0 = [](long I) -> long {
        /* GATE 578 (LUT2 _3342_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut109.push_back(ctx.genrate_lut(lut109idx0));
    flut109.push_back(lut109idx0);
    auto lut109idx1 = [](long I) -> long {
        /* GATE 696 (LUT2 _3460_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut109.push_back(ctx.genrate_lut(lut109idx1));
    flut109.push_back(lut109idx1);
    auto fvec109 = [flut109](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut109[i](I));
        return ret;
    };

    std::cerr << "\rLUT109   ";
    Ciphertext gin109 = 1 * ct_out150 + 2 * ct_out158;
    std::vector<Ciphertext> gout109 = ctx.eval_lut_amortized(&gin109, lut109);

    std::vector<RotationPoly> lut110;
    std::vector<long (*)(long)> flut110;
    auto lut110idx0 = [](long I) -> long {
        /* GATE 465 (LUT2 _3229_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut110.push_back(ctx.genrate_lut(lut110idx0));
    flut110.push_back(lut110idx0);
    auto lut110idx1 = [](long I) -> long {
        /* GATE 342 (LUT2 _3106_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut110.push_back(ctx.genrate_lut(lut110idx1));
    flut110.push_back(lut110idx1);
    auto fvec110 = [flut110](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut110[i](I));
        return ret;
    };

    std::cerr << "\rLUT110   ";
    Ciphertext gin110 = 1 * gout45[1] + 2 * ct_out164;
    std::vector<Ciphertext> gout110 = ctx.eval_lut_amortized(&gin110, lut110);

    std::vector<RotationPoly> lut111;
    std::vector<long (*)(long)> flut111;
    auto lut111idx0 = [](long I) -> long {
        /* GATE 827 (LUT2 _3591_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut111.push_back(ctx.genrate_lut(lut111idx0));
    flut111.push_back(lut111idx0);
    auto lut111idx1 = [](long I) -> long {
        /* GATE 710 (LUT2 _3474_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut111.push_back(ctx.genrate_lut(lut111idx1));
    flut111.push_back(lut111idx1);
    auto fvec111 = [flut111](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut111[i](I));
        return ret;
    };

    std::cerr << "\rLUT111   ";
    Ciphertext gin111 = 1 * ct_out7 + 2 * ct_out15;
    std::vector<Ciphertext> gout111 = ctx.eval_lut_amortized(&gin111, lut111);

    std::vector<RotationPoly> lut112;
    std::vector<long (*)(long)> flut112;
    auto lut112idx0 = [](long I) -> long {
        /* GATE 464 (LUT2 _3228_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut112.push_back(ctx.genrate_lut(lut112idx0));
    flut112.push_back(lut112idx0);
    auto fvec112 = [flut112](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut112[i](I));
        return ret;
    };

    std::cerr << "\rLUT112   ";
    Ciphertext gin112 = 1 * gout110[0] + 2 * gout45[0];
    std::vector<Ciphertext> gout112 = ctx.eval_lut_amortized(&gin112, lut112);

    std::vector<RotationPoly> lut113;
    std::vector<long (*)(long)> flut113;
    auto lut113idx0 = [](long I) -> long {
        /* GATE 341 (LUT2 _3105_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut113.push_back(ctx.genrate_lut(lut113idx0));
    flut113.push_back(lut113idx0);
    auto lut113idx1 = [](long I) -> long {
        /* GATE 228 (LUT2 _2992_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut113.push_back(ctx.genrate_lut(lut113idx1));
    flut113.push_back(lut113idx1);
    auto fvec113 = [flut113](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut113[i](I));
        return ret;
    };

    std::cerr << "\rLUT113   ";
    Ciphertext gin113 = 1 * ct_out123 + 2 * ct_out131;
    std::vector<Ciphertext> gout113 = ctx.eval_lut_amortized(&gin113, lut113);

    std::vector<RotationPoly> lut114;
    std::vector<long (*)(long)> flut114;
    auto lut114idx0 = [](long I) -> long {
        /* GATE 382 (LUT2 _3146_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut114.push_back(ctx.genrate_lut(lut114idx0));
    flut114.push_back(lut114idx0);
    auto lut114idx1 = [](long I) -> long {
        /* GATE 271 (LUT2 _3035_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut114.push_back(ctx.genrate_lut(lut114idx1));
    flut114.push_back(lut114idx1);
    auto fvec114 = [flut114](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut114[i](I));
        return ret;
    };

    std::cerr << "\rLUT114   ";
    Ciphertext gin114 = 1 * gout6[1] + 2 * ct_out43;
    std::vector<Ciphertext> gout114 = ctx.eval_lut_amortized(&gin114, lut114);

    std::vector<RotationPoly> lut115;
    std::vector<long (*)(long)> flut115;
    auto lut115idx0 = [](long I) -> long {
        /* GATE 178 (LUT2 _2942_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut115.push_back(ctx.genrate_lut(lut115idx0));
    flut115.push_back(lut115idx0);
    auto lut115idx1 = [](long I) -> long {
        /* GATE 297 (LUT2 _3061_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut115.push_back(ctx.genrate_lut(lut115idx1));
    flut115.push_back(lut115idx1);
    auto fvec115 = [flut115](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut115[i](I));
        return ret;
    };

    std::cerr << "\rLUT115   ";
    Ciphertext gin115 = 1 * gout70[1] + 2 * ct_out90;
    std::vector<Ciphertext> gout115 = ctx.eval_lut_amortized(&gin115, lut115);

    std::vector<RotationPoly> lut116;
    std::vector<long (*)(long)> flut116;
    auto lut116idx0 = [](long I) -> long {
        /* GATE 14 (LUT2 _2778_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut116.push_back(ctx.genrate_lut(lut116idx0));
    flut116.push_back(lut116idx0);
    auto lut116idx1 = [](long I) -> long {
        /* GATE 70 (LUT2 _2834_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut116.push_back(ctx.genrate_lut(lut116idx1));
    flut116.push_back(lut116idx1);
    auto fvec116 = [flut116](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut116[i](I));
        return ret;
    };

    std::cerr << "\rLUT116   ";
    Ciphertext gin116 = 1 * gout49[1] + 2 * ct_out16;
    std::vector<Ciphertext> gout116 = ctx.eval_lut_amortized(&gin116, lut116);

    std::vector<RotationPoly> lut117;
    std::vector<long (*)(long)> flut117;
    auto lut117idx0 = [](long I) -> long {
        /* GATE 737 (LUT2 _3501_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut117.push_back(ctx.genrate_lut(lut117idx0));
    flut117.push_back(lut117idx0);
    auto lut117idx1 = [](long I) -> long {
        /* GATE 624 (LUT2 _3388_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut117.push_back(ctx.genrate_lut(lut117idx1));
    flut117.push_back(lut117idx1);
    auto fvec117 = [flut117](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut117[i](I));
        return ret;
    };

    std::cerr << "\rLUT117   ";
    Ciphertext gin117 = 1 * gout57[1] + 2 * ct_out70;
    std::vector<Ciphertext> gout117 = ctx.eval_lut_amortized(&gin117, lut117);

    std::vector<RotationPoly> lut118;
    std::vector<long (*)(long)> flut118;
    auto lut118idx0 = [](long I) -> long {
        /* GATE 227 (LUT2 _2991_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut118.push_back(ctx.genrate_lut(lut118idx0));
    flut118.push_back(lut118idx0);
    auto lut118idx1 = [](long I) -> long {
        /* GATE 340 (LUT2 _3104_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut118.push_back(ctx.genrate_lut(lut118idx1));
    flut118.push_back(lut118idx1);
    auto fvec118 = [flut118](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut118[i](I));
        return ret;
    };

    std::cerr << "\rLUT118   ";
    Ciphertext gin118 = 1 * gout113[1] + 2 * ct_out139;
    std::vector<Ciphertext> gout118 = ctx.eval_lut_amortized(&gin118, lut118);

    std::vector<RotationPoly> lut119;
    std::vector<long (*)(long)> flut119;
    auto lut119idx0 = [](long I) -> long {
        /* GATE 234 (LUT2 _2998_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut119.push_back(ctx.genrate_lut(lut119idx0));
    flut119.push_back(lut119idx0);
    auto lut119idx1 = [](long I) -> long {
        /* GATE 345 (LUT2 _3109_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin119 = 1 * gout11[0] + 2 * ct_out163;
    std::vector<Ciphertext> gout119 = ctx.eval_lut_amortized(&gin119, lut119);

    std::vector<RotationPoly> lut120;
    std::vector<long (*)(long)> flut120;
    auto lut120idx0 = [](long I) -> long {
        /* GATE 268 (LUT2 _3032_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin120 = 1 * gout100[0] + 2 * gout43[0];
    std::vector<Ciphertext> gout120 = ctx.eval_lut_amortized(&gin120, lut120);

    std::vector<RotationPoly> lut121;
    std::vector<long (*)(long)> flut121;
    auto lut121idx0 = [](long I) -> long {
        /* GATE 800 (LUT2 _3564_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin121 = 1 * gout96[0] + 2 * gout74[1];
    std::vector<Ciphertext> gout121 = ctx.eval_lut_amortized(&gin121, lut121);

    std::vector<RotationPoly> lut122;
    std::vector<long (*)(long)> flut122;
    auto lut122idx0 = [](long I) -> long {
        /* GATE 281 (LUT2 _3045_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut122.push_back(ctx.genrate_lut(lut122idx0));
    flut122.push_back(lut122idx0);
    auto lut122idx1 = [](long I) -> long {
        /* GATE 387 (LUT2 _3151_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut122.push_back(ctx.genrate_lut(lut122idx1));
    flut122.push_back(lut122idx1);
    auto fvec122 = [flut122](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut122[i](I));
        return ret;
    };

    std::cerr << "\rLUT122   ";
    Ciphertext gin122 = 1 * gout40[1] + 2 * ct_out67;
    std::vector<Ciphertext> gout122 = ctx.eval_lut_amortized(&gin122, lut122);

    std::vector<RotationPoly> lut123;
    std::vector<long (*)(long)> flut123;
    auto lut123idx0 = [](long I) -> long {
        /* GATE 621 (LUT2 _3385_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut123.push_back(ctx.genrate_lut(lut123idx0));
    flut123.push_back(lut123idx0);
    auto fvec123 = [flut123](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut123[i](I));
        return ret;
    };

    std::cerr << "\rLUT123   ";
    Ciphertext gin123 = 1 * gout47[1] + 2 * gout10[0];
    std::vector<Ciphertext> gout123 = ctx.eval_lut_amortized(&gin123, lut123);

    std::vector<RotationPoly> lut124;
    std::vector<long (*)(long)> flut124;
    auto lut124idx0 = [](long I) -> long {
        /* GATE 739 (LUT2 _3503_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut124.push_back(ctx.genrate_lut(lut124idx0));
    flut124.push_back(lut124idx0);
    auto lut124idx1 = [](long I) -> long {
        /* GATE 832 (LUT2 _3596_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut124.push_back(ctx.genrate_lut(lut124idx1));
    flut124.push_back(lut124idx1);
    auto fvec124 = [flut124](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut124[i](I));
        return ret;
    };

    std::cerr << "\rLUT124   ";
    Ciphertext gin124 = 1 * gout22[1] + 2 * ct_out71;
    std::vector<Ciphertext> gout124 = ctx.eval_lut_amortized(&gin124, lut124);

    std::vector<RotationPoly> lut125;
    std::vector<long (*)(long)> flut125;
    auto lut125idx0 = [](long I) -> long {
        /* GATE 331 (LUT2 _3095_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut125.push_back(ctx.genrate_lut(lut125idx0));
    flut125.push_back(lut125idx0);
    auto lut125idx1 = [](long I) -> long {
        /* GATE 225 (LUT2 _2989_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut125.push_back(ctx.genrate_lut(lut125idx1));
    flut125.push_back(lut125idx1);
    auto fvec125 = [flut125](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut125[i](I));
        return ret;
    };

    std::cerr << "\rLUT125   ";
    Ciphertext gin125 = 1 * gout90[1] + 2 * ct_out115;
    std::vector<Ciphertext> gout125 = ctx.eval_lut_amortized(&gin125, lut125);

    std::vector<RotationPoly> lut126;
    std::vector<long (*)(long)> flut126;
    auto lut126idx0 = [](long I) -> long {
        /* GATE 50 (LUT2 _2814_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut126.push_back(ctx.genrate_lut(lut126idx0));
    flut126.push_back(lut126idx0);
    auto lut126idx1 = [](long I) -> long {
        /* GATE 9 (LUT2 _2773_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut126.push_back(ctx.genrate_lut(lut126idx1));
    flut126.push_back(lut126idx1);
    auto fvec126 = [flut126](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut126[i](I));
        return ret;
    };

    std::cerr << "\rLUT126   ";
    Ciphertext gin126 = 1 * gout27[0] + 2 * ct_out160;
    std::vector<Ciphertext> gout126 = ctx.eval_lut_amortized(&gin126, lut126);

    std::vector<RotationPoly> lut127;
    std::vector<long (*)(long)> flut127;
    auto lut127idx0 = [](long I) -> long {
        /* GATE 639 (LUT2 _3403_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin127 = 1 * gout78[0] + 2 * gout4[1];
    std::vector<Ciphertext> gout127 = ctx.eval_lut_amortized(&gin127, lut127);

    std::vector<RotationPoly> lut128;
    std::vector<long (*)(long)> flut128;
    auto lut128idx0 = [](long I) -> long {
        /* GATE 611 (LUT2 _3375_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin128 = 1 * gout105[1] + 2 * gout88[0];
    std::vector<Ciphertext> gout128 = ctx.eval_lut_amortized(&gin128, lut128);

    std::vector<RotationPoly> lut129;
    std::vector<long (*)(long)> flut129;
    auto lut129idx0 = [](long I) -> long {
        /* GATE 459 (LUT2 _3223_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin129 = 1 * gout61[1] + 2 * gout34[1];
    std::vector<Ciphertext> gout129 = ctx.eval_lut_amortized(&gin129, lut129);

    std::vector<RotationPoly> lut130;
    std::vector<long (*)(long)> flut130;
    auto lut130idx0 = [](long I) -> long {
        /* GATE 794 (LUT2 _3558_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut130.push_back(ctx.genrate_lut(lut130idx0));
    flut130.push_back(lut130idx0);
    auto lut130idx1 = [](long I) -> long {
        /* GATE 683 (LUT2 _3447_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin130 = 1 * gout42[1] + 2 * ct_out119;
    std::vector<Ciphertext> gout130 = ctx.eval_lut_amortized(&gin130, lut130);

    std::vector<RotationPoly> lut131;
    std::vector<long (*)(long)> flut131;
    auto lut131idx0 = [](long I) -> long {
        /* GATE 166 (LUT2 _2930_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut131.push_back(ctx.genrate_lut(lut131idx0));
    flut131.push_back(lut131idx0);
    auto lut131idx1 = [](long I) -> long {
        /* GATE 274 (LUT2 _3038_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut131.push_back(ctx.genrate_lut(lut131idx1));
    flut131.push_back(lut131idx1);
    auto fvec131 = [flut131](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut131[i](I));
        return ret;
    };

    std::cerr << "\rLUT131   ";
    Ciphertext gin131 = 1 * gout60[0] + 2 * ct_out42;
    std::vector<Ciphertext> gout131 = ctx.eval_lut_amortized(&gin131, lut131);

    std::vector<RotationPoly> lut132;
    std::vector<long (*)(long)> flut132;
    auto lut132idx0 = [](long I) -> long {
        /* GATE 4 (LUT2 _2768_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut132.push_back(ctx.genrate_lut(lut132idx0));
    flut132.push_back(lut132idx0);
    auto lut132idx1 = [](long I) -> long {
        /* GATE 41 (LUT2 _2805_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut132.push_back(ctx.genrate_lut(lut132idx1));
    flut132.push_back(lut132idx1);
    auto fvec132 = [flut132](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut132[i](I));
        return ret;
    };

    std::cerr << "\rLUT132   ";
    Ciphertext gin132 = 1 * gout65[0] + 2 * gout33[0];
    std::vector<Ciphertext> gout132 = ctx.eval_lut_amortized(&gin132, lut132);

    std::vector<RotationPoly> lut133;
    std::vector<long (*)(long)> flut133;
    auto lut133idx0 = [](long I) -> long {
        /* GATE 677 (LUT2 _3441_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut133.push_back(ctx.genrate_lut(lut133idx0));
    flut133.push_back(lut133idx0);
    auto lut133idx1 = [](long I) -> long {
        /* GATE 564 (LUT2 _3328_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut133.push_back(ctx.genrate_lut(lut133idx1));
    flut133.push_back(lut133idx1);
    auto fvec133 = [flut133](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut133[i](I));
        return ret;
    };

    std::cerr << "\rLUT133   ";
    Ciphertext gin133 = 1 * gout80[0] + 2 * gout58[1];
    std::vector<Ciphertext> gout133 = ctx.eval_lut_amortized(&gin133, lut133);

    std::vector<RotationPoly> lut134;
    std::vector<long (*)(long)> flut134;
    auto lut134idx0 = [](long I) -> long {
        /* GATE 563 (LUT2 _3327_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut134.push_back(ctx.genrate_lut(lut134idx0));
    flut134.push_back(lut134idx0);
    auto lut134idx1 = [](long I) -> long {
        /* GATE 676 (LUT2 _3440_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut134.push_back(ctx.genrate_lut(lut134idx1));
    flut134.push_back(lut134idx1);
    auto fvec134 = [flut134](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut134[i](I));
        return ret;
    };

    std::cerr << "\rLUT134   ";
    Ciphertext gin134 = 1 * gout133[1] + 2 * gout23[0];
    std::vector<Ciphertext> gout134 = ctx.eval_lut_amortized(&gin134, lut134);

    std::vector<RotationPoly> lut135;
    std::vector<long (*)(long)> flut135;
    auto lut135idx0 = [](long I) -> long {
        /* GATE 296 (LUT2 _3060_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin135 = 1 * gout115[1] + 2 * gout70[0];
    std::vector<Ciphertext> gout135 = ctx.eval_lut_amortized(&gin135, lut135);

    std::vector<RotationPoly> lut136;
    std::vector<long (*)(long)> flut136;
    auto lut136idx0 = [](long I) -> long {
        /* GATE 732 (LUT2 _3496_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut136.push_back(ctx.genrate_lut(lut136idx0));
    flut136.push_back(lut136idx0);
    auto lut136idx1 = [](long I) -> long {
        /* GATE 614 (LUT2 _3378_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut136.push_back(ctx.genrate_lut(lut136idx1));
    flut136.push_back(lut136idx1);
    auto fvec136 = [flut136](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut136[i](I));
        return ret;
    };

    std::cerr << "\rLUT136   ";
    Ciphertext gin136 = 1 * gout76[1] + 2 * ct_out46;
    std::vector<Ciphertext> gout136 = ctx.eval_lut_amortized(&gin136, lut136);

    std::vector<RotationPoly> lut137;
    std::vector<long (*)(long)> flut137;
    auto lut137idx0 = [](long I) -> long {
        /* GATE 807 (LUT2 _3571_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut137.push_back(ctx.genrate_lut(lut137idx0));
    flut137.push_back(lut137idx0);
    auto lut137idx1 = [](long I) -> long {
        /* GATE 688 (LUT2 _3452_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut137.push_back(ctx.genrate_lut(lut137idx1));
    flut137.push_back(lut137idx1);
    auto fvec137 = [flut137](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut137[i](I));
        return ret;
    };

    std::cerr << "\rLUT137   ";
    Ciphertext gin137 = 1 * gout53[0] + 2 * gout96[1];
    std::vector<Ciphertext> gout137 = ctx.eval_lut_amortized(&gin137, lut137);

    std::vector<RotationPoly> lut138;
    std::vector<long (*)(long)> flut138;
    auto lut138idx0 = [](long I) -> long {
        /* GATE 685 (LUT2 _3449_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut138.push_back(ctx.genrate_lut(lut138idx0));
    flut138.push_back(lut138idx0);
    auto lut138idx1 = [](long I) -> long {
        /* GATE 798 (LUT2 _3562_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut138.push_back(ctx.genrate_lut(lut138idx1));
    flut138.push_back(lut138idx1);
    auto fvec138 = [flut138](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut138[i](I));
        return ret;
    };

    std::cerr << "\rLUT138   ";
    Ciphertext gin138 = 1 * gout41[0] + 2 * ct_out143;
    std::vector<Ciphertext> gout138 = ctx.eval_lut_amortized(&gin138, lut138);

    std::vector<RotationPoly> lut139;
    std::vector<long (*)(long)> flut139;
    auto lut139idx0 = [](long I) -> long {
        /* GATE 831 (LUT2 _3595_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin139 = 1 * gout124[1] + 2 * gout22[0];
    std::vector<Ciphertext> gout139 = ctx.eval_lut_amortized(&gin139, lut139);

    std::vector<RotationPoly> lut140;
    std::vector<long (*)(long)> flut140;
    auto lut140idx0 = [](long I) -> long {
        /* GATE 188 (LUT2 _2952_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin140 = 1 * gout92[1] + 2 * gout32[1];
    std::vector<Ciphertext> gout140 = ctx.eval_lut_amortized(&gin140, lut140);

    std::vector<RotationPoly> lut141;
    std::vector<long (*)(long)> flut141;
    auto lut141idx0 = [](long I) -> long {
        /* GATE 474 (LUT2 _3238_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin141 = 1 * gout30[1] + 2 * gout7[1];
    std::vector<Ciphertext> gout141 = ctx.eval_lut_amortized(&gin141, lut141);

    std::vector<RotationPoly> lut142;
    std::vector<long (*)(long)> flut142;
    auto lut142idx0 = [](long I) -> long {
        /* GATE 143 (LUT2 _2907_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut142.push_back(ctx.genrate_lut(lut142idx0));
    flut142.push_back(lut142idx0);
    auto lut142idx1 = [](long I) -> long {
        /* GATE 255 (LUT2 _3019_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut142.push_back(ctx.genrate_lut(lut142idx1));
    flut142.push_back(lut142idx1);
    auto fvec142 = [flut142](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut142[i](I));
        return ret;
    };

    std::cerr << "\rLUT142   ";
    Ciphertext gin142 = 1 * gout93[0] + 2 * gout8[0];
    std::vector<Ciphertext> gout142 = ctx.eval_lut_amortized(&gin142, lut142);

    std::vector<RotationPoly> lut143;
    std::vector<long (*)(long)> flut143;
    auto lut143idx0 = [](long I) -> long {
        /* GATE 330 (LUT2 _3094_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin143 = 1 * gout125[0] + 2 * gout90[0];
    std::vector<Ciphertext> gout143 = ctx.eval_lut_amortized(&gin143, lut143);

    std::vector<RotationPoly> lut144;
    std::vector<long (*)(long)> flut144;
    auto lut144idx0 = [](long I) -> long {
        /* GATE 501 (LUT2 _3265_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin144 = 1 * gout44[0] + 2 * gout25[0];
    std::vector<Ciphertext> gout144 = ctx.eval_lut_amortized(&gin144, lut144);

    std::vector<RotationPoly> lut145;
    std::vector<long (*)(long)> flut145;
    auto lut145idx0 = [](long I) -> long {
        /* GATE 507 (LUT2 _3271_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut145.push_back(ctx.genrate_lut(lut145idx0));
    flut145.push_back(lut145idx0);
    auto lut145idx1 = [](long I) -> long {
        /* GATE 389 (LUT2 _3153_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut145.push_back(ctx.genrate_lut(lut145idx1));
    flut145.push_back(lut145idx1);
    auto fvec145 = [flut145](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut145[i](I));
        return ret;
    };

    std::cerr << "\rLUT145   ";
    Ciphertext gin145 = 1 * gout77[0] + 2 * ct_out68;
    std::vector<Ciphertext> gout145 = ctx.eval_lut_amortized(&gin145, lut145);

    std::vector<RotationPoly> lut146;
    std::vector<long (*)(long)> flut146;
    auto lut146idx0 = [](long I) -> long {
        /* GATE 44 (LUT2 _2808_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin146 = 1 * gout33[1] + 2 * gout19[1];
    std::vector<Ciphertext> gout146 = ctx.eval_lut_amortized(&gin146, lut146);

    std::vector<RotationPoly> lut147;
    std::vector<long (*)(long)> flut147;
    auto lut147idx0 = [](long I) -> long {
        /* GATE 34 (LUT2 _2798_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin147 = 1 * gout65[1] + 2 * gout16[1];
    std::vector<Ciphertext> gout147 = ctx.eval_lut_amortized(&gin147, lut147);

    std::vector<RotationPoly> lut148;
    std::vector<long (*)(long)> flut148;
    auto lut148idx0 = [](long I) -> long {
        /* GATE 333 (LUT2 _3097_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut148.push_back(ctx.genrate_lut(lut148idx0));
    flut148.push_back(lut148idx0);
    auto lut148idx1 = [](long I) -> long {
        /* GATE 451 (LUT2 _3215_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin148 = 1 * gout39[1] + 2 * ct_out116;
    std::vector<Ciphertext> gout148 = ctx.eval_lut_amortized(&gin148, lut148);

    std::vector<RotationPoly> lut149;
    std::vector<long (*)(long)> flut149;
    auto lut149idx0 = [](long I) -> long {
        /* GATE 339 (LUT2 _3103_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin149 = 1 * gout118[1] + 2 * gout113[0];
    std::vector<Ciphertext> gout149 = ctx.eval_lut_amortized(&gin149, lut149);

    std::vector<RotationPoly> lut150;
    std::vector<long (*)(long)> flut150;
    auto lut150idx0 = [](long I) -> long {
        /* GATE 828 (LUT2 _3592_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin150 = 1 * gout67[1] + 2 * gout55[0];
    std::vector<Ciphertext> gout150 = ctx.eval_lut_amortized(&gin150, lut150);

    std::vector<RotationPoly> lut151;
    std::vector<long (*)(long)> flut151;
    auto lut151idx0 = [](long I) -> long {
        /* GATE 620 (LUT2 _3384_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut151.push_back(ctx.genrate_lut(lut151idx0));
    flut151.push_back(lut151idx0);
    auto lut151idx1 = [](long I) -> long {
        /* GATE 753 (LUT2 _3517_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut151.push_back(ctx.genrate_lut(lut151idx1));
    flut151.push_back(lut151idx1);
    auto fvec151 = [flut151](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut151[i](I));
        return ret;
    };

    std::cerr << "\rLUT151   ";
    Ciphertext gin151 = 1 * gout123[0] + 2 * gout117[1];
    std::vector<Ciphertext> gout151 = ctx.eval_lut_amortized(&gin151, lut151);

    std::vector<RotationPoly> lut152;
    std::vector<long (*)(long)> flut152;
    auto lut152idx0 = [](long I) -> long {
        /* GATE 845 (LUT2 _3609_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin152 = 1 * gout82[0] + 2 * gout26[1];
    std::vector<Ciphertext> gout152 = ctx.eval_lut_amortized(&gin152, lut152);

    std::vector<RotationPoly> lut153;
    std::vector<long (*)(long)> flut153;
    auto lut153idx0 = [](long I) -> long {
        /* GATE 705 (LUT2 _3469_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut153.push_back(ctx.genrate_lut(lut153idx0));
    flut153.push_back(lut153idx0);
    auto lut153idx1 = [](long I) -> long {
        /* GATE 592 (LUT2 _3356_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut153.push_back(ctx.genrate_lut(lut153idx1));
    flut153.push_back(lut153idx1);
    auto fvec153 = [flut153](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut153[i](I));
        return ret;
    };

    std::cerr << "\rLUT153   ";
    Ciphertext gin153 = 1 * gout94[0] + 2 * ct_out190;
    std::vector<Ciphertext> gout153 = ctx.eval_lut_amortized(&gin153, lut153);

    std::vector<RotationPoly> lut154;
    std::vector<long (*)(long)> flut154;
    auto lut154idx0 = [](long I) -> long {
        /* GATE 243 (LUT2 _3007_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut154.push_back(ctx.genrate_lut(lut154idx0));
    flut154.push_back(lut154idx0);
    auto lut154idx1 = [](long I) -> long {
        /* GATE 128 (LUT2 _2892_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut154.push_back(ctx.genrate_lut(lut154idx1));
    flut154.push_back(lut154idx1);
    auto fvec154 = [flut154](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut154[i](I));
        return ret;
    };

    std::cerr << "\rLUT154   ";
    Ciphertext gin154 = 1 * gout79[0] + 2 * gout98[0];
    std::vector<Ciphertext> gout154 = ctx.eval_lut_amortized(&gin154, lut154);

    std::vector<RotationPoly> lut155;
    std::vector<long (*)(long)> flut155;
    auto lut155idx0 = [](long I) -> long {
        /* GATE 752 (LUT2 _3516_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut155.push_back(ctx.genrate_lut(lut155idx0));
    flut155.push_back(lut155idx0);
    auto lut155idx1 = [](long I) -> long {
        /* GATE 619 (LUT2 _3383_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut155.push_back(ctx.genrate_lut(lut155idx1));
    flut155.push_back(lut155idx1);
    auto fvec155 = [flut155](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut155[i](I));
        return ret;
    };

    std::cerr << "\rLUT155   ";
    Ciphertext gin155 = 1 * gout151[0] + 2 * gout63[0];
    std::vector<Ciphertext> gout155 = ctx.eval_lut_amortized(&gin155, lut155);

    std::vector<RotationPoly> lut156;
    std::vector<long (*)(long)> flut156;
    auto lut156idx0 = [](long I) -> long {
        /* GATE 377 (LUT2 _3141_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut156.push_back(ctx.genrate_lut(lut156idx0));
    flut156.push_back(lut156idx0);
    auto lut156idx1 = [](long I) -> long {
        /* GATE 251 (LUT2 _3015_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut156.push_back(ctx.genrate_lut(lut156idx1));
    flut156.push_back(lut156idx1);
    auto fvec156 = [flut156](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut156[i](I));
        return ret;
    };

    std::cerr << "\rLUT156   ";
    Ciphertext gin156 = 1 * gout62[1] + 2 * ct_out19;
    std::vector<Ciphertext> gout156 = ctx.eval_lut_amortized(&gin156, lut156);

    std::vector<RotationPoly> lut157;
    std::vector<long (*)(long)> flut157;
    auto lut157idx0 = [](long I) -> long {
        /* GATE 121 (LUT2 _2885_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut157.push_back(ctx.genrate_lut(lut157idx0));
    flut157.push_back(lut157idx0);
    auto lut157idx1 = [](long I) -> long {
        /* GATE 37 (LUT2 _2801_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut157.push_back(ctx.genrate_lut(lut157idx1));
    flut157.push_back(lut157idx1);
    auto fvec157 = [flut157](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut157[i](I));
        return ret;
    };

    std::cerr << "\rLUT157   ";
    Ciphertext gin157 = 1 * gout72[0] + 2 * ct_out113;
    std::vector<Ciphertext> gout157 = ctx.eval_lut_amortized(&gin157, lut157);

    std::vector<RotationPoly> lut158;
    std::vector<long (*)(long)> flut158;
    auto lut158idx0 = [](long I) -> long {
        /* GATE 69 (LUT2 _2833_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin158 = 1 * gout116[1] + 2 * gout49[0];
    std::vector<Ciphertext> gout158 = ctx.eval_lut_amortized(&gin158, lut158);

    std::vector<RotationPoly> lut159;
    std::vector<long (*)(long)> flut159;
    auto lut159idx0 = [](long I) -> long {
        /* GATE 675 (LUT2 _3439_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin159 = 1 * gout134[1] + 2 * gout133[0];
    std::vector<Ciphertext> gout159 = ctx.eval_lut_amortized(&gin159, lut159);

    std::vector<RotationPoly> lut160;
    std::vector<long (*)(long)> flut160;
    auto lut160idx0 = [](long I) -> long {
        /* GATE 506 (LUT2 _3270_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin160 = 1 * gout145[0] + 2 * gout77[1];
    std::vector<Ciphertext> gout160 = ctx.eval_lut_amortized(&gin160, lut160);

    std::vector<RotationPoly> lut161;
    std::vector<long (*)(long)> flut161;
    auto lut161idx0 = [](long I) -> long {
        /* GATE 354 (LUT2 _3118_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin161 = 1 * gout87[0] + 2 * gout56[0];
    std::vector<Ciphertext> gout161 = ctx.eval_lut_amortized(&gin161, lut161);

    std::vector<RotationPoly> lut162;
    std::vector<long (*)(long)> flut162;
    auto lut162idx0 = [](long I) -> long {
        /* GATE 63 (LUT2 _2827_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut162.push_back(ctx.genrate_lut(lut162idx0));
    flut162.push_back(lut162idx0);
    auto lut162idx1 = [](long I) -> long {
        /* GATE 11 (LUT2 _2775_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut162.push_back(ctx.genrate_lut(lut162idx1));
    flut162.push_back(lut162idx1);
    auto fvec162 = [flut162](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut162[i](I));
        return ret;
    };

    std::cerr << "\rLUT162   ";
    Ciphertext gin162 = 1 * gout71[1] + 2 * gout116[0];
    std::vector<Ciphertext> gout162 = ctx.eval_lut_amortized(&gin162, lut162);

    std::vector<RotationPoly> lut163;
    std::vector<long (*)(long)> flut163;
    auto lut163idx0 = [](long I) -> long {
        /* GATE 363 (LUT2 _3127_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut163.push_back(ctx.genrate_lut(lut163idx0));
    flut163.push_back(lut163idx0);
    auto lut163idx1 = [](long I) -> long {
        /* GATE 245 (LUT2 _3009_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut163.push_back(ctx.genrate_lut(lut163idx1));
    flut163.push_back(lut163idx1);
    auto fvec163 = [flut163](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut163[i](I));
        return ret;
    };

    std::cerr << "\rLUT163   ";
    Ciphertext gin163 = 1 * gout99[0] + 2 * gout87[1];
    std::vector<Ciphertext> gout163 = ctx.eval_lut_amortized(&gin163, lut163);

    std::vector<RotationPoly> lut164;
    std::vector<long (*)(long)> flut164;
    auto lut164idx0 = [](long I) -> long {
        /* GATE 16 (LUT2 _2780_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut164.push_back(ctx.genrate_lut(lut164idx0));
    flut164.push_back(lut164idx0);
    auto lut164idx1 = [](long I) -> long {
        /* GATE 86 (LUT2 _2850_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut164.push_back(ctx.genrate_lut(lut164idx1));
    flut164.push_back(lut164idx1);
    auto fvec164 = [flut164](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut164[i](I));
        return ret;
    };

    std::cerr << "\rLUT164   ";
    Ciphertext gin164 = 1 * gout84[0] + 2 * gout108[1];
    std::vector<Ciphertext> gout164 = ctx.eval_lut_amortized(&gin164, lut164);

    std::vector<RotationPoly> lut165;
    std::vector<long (*)(long)> flut165;
    auto lut165idx0 = [](long I) -> long {
        /* GATE 49 (LUT2 _2813_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin165 = 1 * gout126[0] + 2 * gout27[1];
    std::vector<Ciphertext> gout165 = ctx.eval_lut_amortized(&gin165, lut165);

    std::vector<RotationPoly> lut166;
    std::vector<long (*)(long)> flut166;
    auto lut166idx0 = [](long I) -> long {
        /* GATE 344 (LUT2 _3108_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin166 = 1 * gout119[1] + 2 * gout11[1];
    std::vector<Ciphertext> gout166 = ctx.eval_lut_amortized(&gin166, lut166);

    std::vector<RotationPoly> lut167;
    std::vector<long (*)(long)> flut167;
    auto lut167idx0 = [](long I) -> long {
        /* GATE 279 (LUT2 _3043_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut167.push_back(ctx.genrate_lut(lut167idx0));
    flut167.push_back(lut167idx0);
    auto lut167idx1 = [](long I) -> long {
        /* GATE 176 (LUT2 _2940_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut167.push_back(ctx.genrate_lut(lut167idx1));
    flut167.push_back(lut167idx1);
    auto fvec167 = [flut167](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut167[i](I));
        return ret;
    };

    std::cerr << "\rLUT167   ";
    Ciphertext gin167 = 1 * gout48[0] + 2 * ct_out66;
    std::vector<Ciphertext> gout167 = ctx.eval_lut_amortized(&gin167, lut167);

    std::vector<RotationPoly> lut168;
    std::vector<long (*)(long)> flut168;
    auto lut168idx0 = [](long I) -> long {
        /* GATE 169 (LUT2 _2933_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut168.push_back(ctx.genrate_lut(lut168idx0));
    flut168.push_back(lut168idx0);
    auto lut168idx1 = [](long I) -> long {
        /* GATE 72 (LUT2 _2836_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut168.push_back(ctx.genrate_lut(lut168idx1));
    flut168.push_back(lut168idx1);
    auto fvec168 = [flut168](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut168[i](I));
        return ret;
    };

    std::cerr << "\rLUT168   ";
    Ciphertext gin168 = 1 * gout102[1] + 2 * ct_out41;
    std::vector<Ciphertext> gout168 = ctx.eval_lut_amortized(&gin168, lut168);

    std::vector<RotationPoly> lut169;
    std::vector<long (*)(long)> flut169;
    auto lut169idx0 = [](long I) -> long {
        /* GATE 56 (LUT2 _2820_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin169 = 1 * gout71[0] + 2 * gout13[1];
    std::vector<Ciphertext> gout169 = ctx.eval_lut_amortized(&gin169, lut169);

    std::vector<RotationPoly> lut170;
    std::vector<long (*)(long)> flut170;
    auto lut170idx0 = [](long I) -> long {
        /* GATE 826 (LUT2 _3590_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut170.push_back(ctx.genrate_lut(lut170idx0));
    flut170.push_back(lut170idx0);
    auto lut170idx1 = [](long I) -> long {
        /* GATE 709 (LUT2 _3473_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut170.push_back(ctx.genrate_lut(lut170idx1));
    flut170.push_back(lut170idx1);
    auto fvec170 = [flut170](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut170[i](I));
        return ret;
    };

    std::cerr << "\rLUT170   ";
    Ciphertext gin170 = 1 * gout111[1] + 2 * ct_out23;
    std::vector<Ciphertext> gout170 = ctx.eval_lut_amortized(&gin170, lut170);

    std::vector<RotationPoly> lut171;
    std::vector<long (*)(long)> flut171;
    auto lut171idx0 = [](long I) -> long {
        /* GATE 725 (LUT2 _3489_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut171.push_back(ctx.genrate_lut(lut171idx0));
    flut171.push_back(lut171idx0);
    auto lut171idx1 = [](long I) -> long {
        /* GATE 823 (LUT2 _3587_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut171.push_back(ctx.genrate_lut(lut171idx1));
    flut171.push_back(lut171idx1);
    auto fvec171 = [flut171](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut171[i](I));
        return ret;
    };

    std::cerr << "\rLUT171   ";
    Ciphertext gin171 = 1 * gout54[0] + 2 * gout67[0];
    std::vector<Ciphertext> gout171 = ctx.eval_lut_amortized(&gin171, lut171);

    std::vector<RotationPoly> lut172;
    std::vector<long (*)(long)> flut172;
    auto lut172idx0 = [](long I) -> long {
        /* GATE 359 (LUT2 _3123_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut172.push_back(ctx.genrate_lut(lut172idx0));
    flut172.push_back(lut172idx0);
    auto lut172idx1 = [](long I) -> long {
        /* GATE 497 (LUT2 _3261_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut172.push_back(ctx.genrate_lut(lut172idx1));
    flut172.push_back(lut172idx1);
    auto fvec172 = [flut172](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut172[i](I));
        return ret;
    };

    std::cerr << "\rLUT172   ";
    Ciphertext gin172 = 1 * gout106[0] + 2 * ct_out20;
    std::vector<Ciphertext> gout172 = ctx.eval_lut_amortized(&gin172, lut172);

    std::vector<RotationPoly> lut173;
    std::vector<long (*)(long)> flut173;
    auto lut173idx0 = [](long I) -> long {
        /* GATE 82 (LUT2 _2846_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut173.push_back(ctx.genrate_lut(lut173idx0));
    flut173.push_back(lut173idx0);
    auto lut173idx1 = [](long I) -> long {
        /* GATE 174 (LUT2 _2938_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut173.push_back(ctx.genrate_lut(lut173idx1));
    flut173.push_back(lut173idx1);
    auto fvec173 = [flut173](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut173[i](I));
        return ret;
    };

    std::cerr << "\rLUT173   ";
    Ciphertext gin173 = 1 * gout107[0] + 2 * ct_out65;
    std::vector<Ciphertext> gout173 = ctx.eval_lut_amortized(&gin173, lut173);

    std::vector<RotationPoly> lut174;
    std::vector<long (*)(long)> flut174;
    auto lut174idx0 = [](long I) -> long {
        /* GATE 74 (LUT2 _2838_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin174 = 1 * gout108[0] + 2 * gout46[1];
    std::vector<Ciphertext> gout174 = ctx.eval_lut_amortized(&gin174, lut174);

    std::vector<RotationPoly> lut175;
    std::vector<long (*)(long)> flut175;
    auto lut175idx0 = [](long I) -> long {
        /* GATE 680 (LUT2 _3444_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin175 = 1 * gout58[0] + 2 * gout20[1];
    std::vector<Ciphertext> gout175 = ctx.eval_lut_amortized(&gin175, lut175);

    std::vector<RotationPoly> lut176;
    std::vector<long (*)(long)> flut176;
    auto lut176idx0 = [](long I) -> long {
        /* GATE 809 (LUT2 _3573_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut176.push_back(ctx.genrate_lut(lut176idx0));
    flut176.push_back(lut176idx0);
    auto lut176idx1 = [](long I) -> long {
        /* GATE 707 (LUT2 _3471_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut176.push_back(ctx.genrate_lut(lut176idx1));
    flut176.push_back(lut176idx1);
    auto fvec176 = [flut176](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut176[i](I));
        return ret;
    };

    std::cerr << "\rLUT176   ";
    Ciphertext gin176 = 1 * gout97[0] + 2 * ct_out191;
    std::vector<Ciphertext> gout176 = ctx.eval_lut_amortized(&gin176, lut176);

    std::vector<RotationPoly> lut177;
    std::vector<long (*)(long)> flut177;
    auto lut177idx0 = [](long I) -> long {
        /* GATE 141 (LUT2 _2905_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut177.push_back(ctx.genrate_lut(lut177idx0));
    flut177.push_back(lut177idx0);
    auto lut177idx1 = [](long I) -> long {
        /* GATE 43 (LUT2 _2807_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut177.push_back(ctx.genrate_lut(lut177idx1));
    flut177.push_back(lut177idx1);
    auto fvec177 = [flut177](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut177[i](I));
        return ret;
    };

    std::cerr << "\rLUT177   ";
    Ciphertext gin177 = 1 * gout146[0] + 2 * gout24[1];
    std::vector<Ciphertext> gout177 = ctx.eval_lut_amortized(&gin177, lut177);

    std::vector<RotationPoly> lut178;
    std::vector<long (*)(long)> flut178;
    auto lut178idx0 = [](long I) -> long {
        /* GATE 164 (LUT2 _2928_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut178.push_back(ctx.genrate_lut(lut178idx0));
    flut178.push_back(lut178idx0);
    auto lut178idx1 = [](long I) -> long {
        /* GATE 61 (LUT2 _2825_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut178.push_back(ctx.genrate_lut(lut178idx1));
    flut178.push_back(lut178idx1);
    auto fvec178 = [flut178](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut178[i](I));
        return ret;
    };

    std::cerr << "\rLUT178   ";
    Ciphertext gin178 = 1 * gout66[0] + 2 * ct_out17;
    std::vector<Ciphertext> gout178 = ctx.eval_lut_amortized(&gin178, lut178);

    std::vector<RotationPoly> lut179;
    std::vector<long (*)(long)> flut179;
    auto lut179idx0 = [](long I) -> long {
        /* GATE 386 (LUT2 _3150_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin179 = 1 * gout122[1] + 2 * gout40[0];
    std::vector<Ciphertext> gout179 = ctx.eval_lut_amortized(&gin179, lut179);

    std::vector<RotationPoly> lut180;
    std::vector<long (*)(long)> flut180;
    auto lut180idx0 = [](long I) -> long {
        /* GATE 90 (LUT2 _2854_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin180 = 1 * gout69[0] + 2 * gout51[1];
    std::vector<Ciphertext> gout180 = ctx.eval_lut_amortized(&gin180, lut180);

    std::vector<RotationPoly> lut181;
    std::vector<long (*)(long)> flut181;
    auto lut181idx0 = [](long I) -> long {
        /* GATE 376 (LUT2 _3140_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin181 = 1 * gout156[0] + 2 * gout62[0];
    std::vector<Ciphertext> gout181 = ctx.eval_lut_amortized(&gin181, lut181);

    std::vector<RotationPoly> lut182;
    std::vector<long (*)(long)> flut182;
    auto lut182idx0 = [](long I) -> long {
        /* GATE 362 (LUT2 _3126_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut182.push_back(ctx.genrate_lut(lut182idx0));
    flut182.push_back(lut182idx0);
    auto lut182idx1 = [](long I) -> long {
        /* GATE 244 (LUT2 _3008_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut182.push_back(ctx.genrate_lut(lut182idx1));
    flut182.push_back(lut182idx1);
    auto fvec182 = [flut182](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut182[i](I));
        return ret;
    };

    std::cerr << "\rLUT182   ";
    Ciphertext gin182 = 1 * gout163[1] + 2 * gout156[1];
    std::vector<Ciphertext> gout182 = ctx.eval_lut_amortized(&gin182, lut182);

    std::vector<RotationPoly> lut183;
    std::vector<long (*)(long)> flut183;
    auto lut183idx0 = [](long I) -> long {
        /* GATE 638 (LUT2 _3402_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut183.push_back(ctx.genrate_lut(lut183idx0));
    flut183.push_back(lut183idx0);
    auto lut183idx1 = [](long I) -> long {
        /* GATE 505 (LUT2 _3269_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut183.push_back(ctx.genrate_lut(lut183idx1));
    flut183.push_back(lut183idx1);
    auto fvec183 = [flut183](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut183[i](I));
        return ret;
    };

    std::cerr << "\rLUT183   ";
    Ciphertext gin183 = 1 * gout160[0] + 2 * gout47[0];
    std::vector<Ciphertext> gout183 = ctx.eval_lut_amortized(&gin183, lut183);

    std::vector<RotationPoly> lut184;
    std::vector<long (*)(long)> flut184;
    auto lut184idx0 = [](long I) -> long {
        /* GATE 598 (LUT2 _3362_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut184.push_back(ctx.genrate_lut(lut184idx0));
    flut184.push_back(lut184idx0);
    auto lut184idx1 = [](long I) -> long {
        /* GATE 473 (LUT2 _3237_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut184.push_back(ctx.genrate_lut(lut184idx1));
    flut184.push_back(lut184idx1);
    auto fvec184 = [flut184](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut184[i](I));
        return ret;
    };

    std::cerr << "\rLUT184   ";
    Ciphertext gin184 = 1 * gout141[0] + 2 * gout75[0];
    std::vector<Ciphertext> gout184 = ctx.eval_lut_amortized(&gin184, lut184);

    std::vector<RotationPoly> lut185;
    std::vector<long (*)(long)> flut185;
    auto lut185idx0 = [](long I) -> long {
        /* GATE 338 (LUT2 _3102_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut185.push_back(ctx.genrate_lut(lut185idx0));
    flut185.push_back(lut185idx0);
    auto lut185idx1 = [](long I) -> long {
        /* GATE 471 (LUT2 _3235_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut185.push_back(ctx.genrate_lut(lut185idx1));
    flut185.push_back(lut185idx1);
    auto fvec185 = [flut185](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut185[i](I));
        return ret;
    };

    std::cerr << "\rLUT185   ";
    Ciphertext gin185 = 1 * gout149[0] + 2 * gout110[1];
    std::vector<Ciphertext> gout185 = ctx.eval_lut_amortized(&gin185, lut185);

    std::vector<RotationPoly> lut186;
    std::vector<long (*)(long)> flut186;
    auto lut186idx0 = [](long I) -> long {
        /* GATE 447 (LUT2 _3211_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut186.push_back(ctx.genrate_lut(lut186idx0));
    flut186.push_back(lut186idx0);
    auto lut186idx1 = [](long I) -> long {
        /* GATE 329 (LUT2 _3093_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut186.push_back(ctx.genrate_lut(lut186idx1));
    flut186.push_back(lut186idx1);
    auto fvec186 = [flut186](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut186[i](I));
        return ret;
    };

    std::cerr << "\rLUT186   ";
    Ciphertext gin186 = 1 * gout143[0] + 2 * gout148[0];
    std::vector<Ciphertext> gout186 = ctx.eval_lut_amortized(&gin186, lut186);

    std::vector<RotationPoly> lut187;
    std::vector<long (*)(long)> flut187;
    auto lut187idx0 = [](long I) -> long {
        /* GATE 704 (LUT2 _3468_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin187 = 1 * gout153[0] + 2 * gout94[1];
    std::vector<Ciphertext> gout187 = ctx.eval_lut_amortized(&gin187, lut187);

    std::vector<RotationPoly> lut188;
    std::vector<long (*)(long)> flut188;
    auto lut188idx0 = [](long I) -> long {
        /* GATE 236 (LUT2 _3000_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin188 = 1 * gout98[1] + 2 * gout37[1];
    std::vector<Ciphertext> gout188 = ctx.eval_lut_amortized(&gin188, lut188);

    std::vector<RotationPoly> lut189;
    std::vector<long (*)(long)> flut189;
    auto lut189idx0 = [](long I) -> long {
        /* GATE 580 (LUT2 _3344_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut189.push_back(ctx.genrate_lut(lut189idx0));
    flut189.push_back(lut189idx0);
    auto lut189idx1 = [](long I) -> long {
        /* GATE 462 (LUT2 _3226_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut189.push_back(ctx.genrate_lut(lut189idx1));
    flut189.push_back(lut189idx1);
    auto fvec189 = [flut189](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut189[i](I));
        return ret;
    };

    std::cerr << "\rLUT189   ";
    Ciphertext gin189 = 1 * gout104[1] + 2 * ct_out165;
    std::vector<Ciphertext> gout189 = ctx.eval_lut_amortized(&gin189, lut189);

    std::vector<RotationPoly> lut190;
    std::vector<long (*)(long)> flut190;
    auto lut190idx0 = [](long I) -> long {
        /* GATE 586 (LUT2 _3350_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut190.push_back(ctx.genrate_lut(lut190idx0));
    flut190.push_back(lut190idx0);
    auto lut190idx1 = [](long I) -> long {
        /* GATE 458 (LUT2 _3222_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut190.push_back(ctx.genrate_lut(lut190idx1));
    flut190.push_back(lut190idx1);
    auto fvec190 = [flut190](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut190[i](I));
        return ret;
    };

    std::cerr << "\rLUT190   ";
    Ciphertext gin190 = 1 * gout129[0] + 2 * gout189[1];
    std::vector<Ciphertext> gout190 = ctx.eval_lut_amortized(&gin190, lut190);

    std::vector<RotationPoly> lut191;
    std::vector<long (*)(long)> flut191;
    auto lut191idx0 = [](long I) -> long {
        /* GATE 731 (LUT2 _3495_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin191 = 1 * gout136[0] + 2 * gout76[0];
    std::vector<Ciphertext> gout191 = ctx.eval_lut_amortized(&gin191, lut191);

    std::vector<RotationPoly> lut192;
    std::vector<long (*)(long)> flut192;
    auto lut192idx0 = [](long I) -> long {
        /* GATE 381 (LUT2 _3145_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin192 = 1 * gout114[0] + 2 * gout6[0];
    std::vector<Ciphertext> gout192 = ctx.eval_lut_amortized(&gin192, lut192);

    std::vector<RotationPoly> lut193;
    std::vector<long (*)(long)> flut193;
    auto lut193idx0 = [](long I) -> long {
        /* GATE 724 (LUT2 _3488_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut193.push_back(ctx.genrate_lut(lut193idx0));
    flut193.push_back(lut193idx0);
    auto lut193idx1 = [](long I) -> long {
        /* GATE 822 (LUT2 _3586_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut193.push_back(ctx.genrate_lut(lut193idx1));
    flut193.push_back(lut193idx1);
    auto fvec193 = [flut193](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut193[i](I));
        return ret;
    };

    std::cerr << "\rLUT193   ";
    Ciphertext gin193 = 1 * gout171[0] + 2 * gout191[0];
    std::vector<Ciphertext> gout193 = ctx.eval_lut_amortized(&gin193, lut193);

    std::vector<RotationPoly> lut194;
    std::vector<long (*)(long)> flut194;
    auto lut194idx0 = [](long I) -> long {
        /* GATE 695 (LUT2 _3459_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut194.push_back(ctx.genrate_lut(lut194idx0));
    flut194.push_back(lut194idx0);
    auto lut194idx1 = [](long I) -> long {
        /* GATE 577 (LUT2 _3341_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut194.push_back(ctx.genrate_lut(lut194idx1));
    flut194.push_back(lut194idx1);
    auto fvec194 = [flut194](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut194[i](I));
        return ret;
    };

    std::cerr << "\rLUT194   ";
    Ciphertext gin194 = 1 * gout109[0] + 2 * ct_out166;
    std::vector<Ciphertext> gout194 = ctx.eval_lut_amortized(&gin194, lut194);

    std::vector<RotationPoly> lut195;
    std::vector<long (*)(long)> flut195;
    auto lut195idx0 = [](long I) -> long {
        /* GATE 52 (LUT2 _2816_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut195.push_back(ctx.genrate_lut(lut195idx0));
    flut195.push_back(lut195idx0);
    auto lut195idx1 = [](long I) -> long {
        /* GATE 3 (LUT2 _2767_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut195.push_back(ctx.genrate_lut(lut195idx1));
    flut195.push_back(lut195idx1);
    auto fvec195 = [flut195](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut195[i](I));
        return ret;
    };

    std::cerr << "\rLUT195   ";
    Ciphertext gin195 = 1 * gout132[0] + 2 * gout126[1];
    std::vector<Ciphertext> gout195 = ctx.eval_lut_amortized(&gin195, lut195);

    std::vector<RotationPoly> lut196;
    std::vector<long (*)(long)> flut196;
    auto lut196idx0 = [](long I) -> long {
        /* GATE 78 (LUT2 _2842_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut196.push_back(ctx.genrate_lut(lut196idx0));
    flut196.push_back(lut196idx0);
    auto lut196idx1 = [](long I) -> long {
        /* GATE 187 (LUT2 _2951_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut196.push_back(ctx.genrate_lut(lut196idx1));
    flut196.push_back(lut196idx1);
    auto fvec196 = [flut196](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut196[i](I));
        return ret;
    };

    std::cerr << "\rLUT196   ";
    Ciphertext gin196 = 1 * gout64[0] + 2 * gout173[0];
    std::vector<Ciphertext> gout196 = ctx.eval_lut_amortized(&gin196, lut196);

    std::vector<RotationPoly> lut197;
    std::vector<long (*)(long)> flut197;
    auto lut197idx0 = [](long I) -> long {
        /* GATE 222 (LUT2 _2986_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin197 = 1 * gout81[1] + 2 * gout29[1];
    std::vector<Ciphertext> gout197 = ctx.eval_lut_amortized(&gin197, lut197);

    std::vector<RotationPoly> lut198;
    std::vector<long (*)(long)> flut198;
    auto lut198idx0 = [](long I) -> long {
        /* GATE 120 (LUT2 _2884_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin198 = 1 * gout157[0] + 2 * gout72[1];
    std::vector<Ciphertext> gout198 = ctx.eval_lut_amortized(&gin198, lut198);

    std::vector<RotationPoly> lut199;
    std::vector<long (*)(long)> flut199;
    auto lut199idx0 = [](long I) -> long {
        /* GATE 736 (LUT2 _3500_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin199 = 1 * gout117[0] + 2 * gout57[0];
    std::vector<Ciphertext> gout199 = ctx.eval_lut_amortized(&gin199, lut199);

    std::vector<RotationPoly> lut200;
    std::vector<long (*)(long)> flut200;
    auto lut200idx0 = [](long I) -> long {
        /* GATE 404 (LUT2 _3168_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin200 = 1 * gout91[0] + 2 * gout89[1];
    std::vector<Ciphertext> gout200 = ctx.eval_lut_amortized(&gin200, lut200);

    std::vector<RotationPoly> lut201;
    std::vector<long (*)(long)> flut201;
    auto lut201idx0 = [](long I) -> long {
        /* GATE 483 (LUT2 _3247_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut201.push_back(ctx.genrate_lut(lut201idx0));
    flut201.push_back(lut201idx0);
    auto lut201idx1 = [](long I) -> long {
        /* GATE 353 (LUT2 _3117_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut201.push_back(ctx.genrate_lut(lut201idx1));
    flut201.push_back(lut201idx1);
    auto fvec201 = [flut201](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut201[i](I));
        return ret;
    };

    std::cerr << "\rLUT201   ";
    Ciphertext gin201 = 1 * gout161[0] + 2 * gout30[0];
    std::vector<Ciphertext> gout201 = ctx.eval_lut_amortized(&gin201, lut201);

    std::vector<RotationPoly> lut202;
    std::vector<long (*)(long)> flut202;
    auto lut202idx0 = [](long I) -> long {
        /* GATE 337 (LUT2 _3101_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut202.push_back(ctx.genrate_lut(lut202idx0));
    flut202.push_back(lut202idx0);
    auto lut202idx1 = [](long I) -> long {
        /* GATE 470 (LUT2 _3234_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut202.push_back(ctx.genrate_lut(lut202idx1));
    flut202.push_back(lut202idx1);
    auto fvec202 = [flut202](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut202[i](I));
        return ret;
    };

    std::cerr << "\rLUT202   ";
    Ciphertext gin202 = 1 * gout166[0] + 2 * gout185[0];
    std::vector<Ciphertext> gout202 = ctx.eval_lut_amortized(&gin202, lut202);

    std::vector<RotationPoly> lut203;
    std::vector<long (*)(long)> flut203;
    auto lut203idx0 = [](long I) -> long {
        /* GATE 617 (LUT2 _3381_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut203.push_back(ctx.genrate_lut(lut203idx0));
    flut203.push_back(lut203idx0);
    auto lut203idx1 = [](long I) -> long {
        /* GATE 499 (LUT2 _3263_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin203 = 1 * gout103[1] + 2 * ct_out45;
    std::vector<Ciphertext> gout203 = ctx.eval_lut_amortized(&gin203, lut203);

    std::vector<RotationPoly> lut204;
    std::vector<long (*)(long)> flut204;
    auto lut204idx0 = [](long I) -> long {
        /* GATE 844 (LUT2 _3608_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut204.push_back(ctx.genrate_lut(lut204idx0));
    flut204.push_back(lut204idx0);
    auto lut204idx1 = [](long I) -> long {
        /* GATE 735 (LUT2 _3499_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut204.push_back(ctx.genrate_lut(lut204idx1));
    flut204.push_back(lut204idx1);
    auto fvec204 = [flut204](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut204[i](I));
        return ret;
    };

    std::cerr << "\rLUT204   ";
    Ciphertext gin204 = 1 * gout199[0] + 2 * gout124[0];
    std::vector<Ciphertext> gout204 = ctx.eval_lut_amortized(&gin204, lut204);

    std::vector<RotationPoly> lut205;
    std::vector<long (*)(long)> flut205;
    auto lut205idx0 = [](long I) -> long {
        /* GATE 751 (LUT2 _3515_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin205 = 1 * gout155[0] + 2 * gout151[1];
    std::vector<Ciphertext> gout205 = ctx.eval_lut_amortized(&gin205, lut205);

    std::vector<RotationPoly> lut206;
    std::vector<long (*)(long)> flut206;
    auto lut206idx0 = [](long I) -> long {
        /* GATE 373 (LUT2 _3137_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut206.push_back(ctx.genrate_lut(lut206idx0));
    flut206.push_back(lut206idx0);
    auto lut206idx1 = [](long I) -> long {
        /* GATE 267 (LUT2 _3031_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut206.push_back(ctx.genrate_lut(lut206idx1));
    flut206.push_back(lut206idx1);
    auto fvec206 = [flut206](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut206[i](I));
        return ret;
    };

    std::cerr << "\rLUT206   ";
    Ciphertext gin206 = 1 * gout120[0] + 2 * gout114[1];
    std::vector<Ciphertext> gout206 = ctx.eval_lut_amortized(&gin206, lut206);

    std::vector<RotationPoly> lut207;
    std::vector<long (*)(long)> flut207;
    auto lut207idx0 = [](long I) -> long {
        /* GATE 585 (LUT2 _3349_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut207.push_back(ctx.genrate_lut(lut207idx0));
    flut207.push_back(lut207idx0);
    auto lut207idx1 = [](long I) -> long {
        /* GATE 457 (LUT2 _3221_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut207.push_back(ctx.genrate_lut(lut207idx1));
    flut207.push_back(lut207idx1);
    auto fvec207 = [flut207](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut207[i](I));
        return ret;
    };

    std::cerr << "\rLUT207   ";
    Ciphertext gin207 = 1 * gout112[0] + 2 * gout190[1];
    std::vector<Ciphertext> gout207 = ctx.eval_lut_amortized(&gin207, lut207);

    std::vector<RotationPoly> lut208;
    std::vector<long (*)(long)> flut208;
    auto lut208idx0 = [](long I) -> long {
        /* GATE 579 (LUT2 _3343_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin208 = 1 * gout189[0] + 2 * gout104[0];
    std::vector<Ciphertext> gout208 = ctx.eval_lut_amortized(&gin208, lut208);

    std::vector<RotationPoly> lut209;
    std::vector<long (*)(long)> flut209;
    auto lut209idx0 = [](long I) -> long {
        /* GATE 385 (LUT2 _3149_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut209.push_back(ctx.genrate_lut(lut209idx0));
    flut209.push_back(lut209idx0);
    auto lut209idx1 = [](long I) -> long {
        /* GATE 523 (LUT2 _3287_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut209.push_back(ctx.genrate_lut(lut209idx1));
    flut209.push_back(lut209idx1);
    auto fvec209 = [flut209](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut209[i](I));
        return ret;
    };

    std::cerr << "\rLUT209   ";
    Ciphertext gin209 = 1 * gout179[0] + 2 * gout145[1];
    std::vector<Ciphertext> gout209 = ctx.eval_lut_amortized(&gin209, lut209);

    std::vector<RotationPoly> lut210;
    std::vector<long (*)(long)> flut210;
    auto lut210idx0 = [](long I) -> long {
        /* GATE 616 (LUT2 _3380_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin210 = 1 * gout203[0] + 2 * gout103[0];
    std::vector<Ciphertext> gout210 = ctx.eval_lut_amortized(&gin210, lut210);

    std::vector<RotationPoly> lut211;
    std::vector<long (*)(long)> flut211;
    auto lut211idx0 = [](long I) -> long {
        /* GATE 168 (LUT2 _2932_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin211 = 1 * gout168[0] + 2 * gout102[0];
    std::vector<Ciphertext> gout211 = ctx.eval_lut_amortized(&gin211, lut211);

    std::vector<RotationPoly> lut212;
    std::vector<long (*)(long)> flut212;
    auto lut212idx0 = [](long I) -> long {
        /* GATE 230 (LUT2 _2994_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut212.push_back(ctx.genrate_lut(lut212idx0));
    flut212.push_back(lut212idx0);
    auto lut212idx1 = [](long I) -> long {
        /* GATE 351 (LUT2 _3115_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut212.push_back(ctx.genrate_lut(lut212idx1));
    flut212.push_back(lut212idx1);
    auto fvec212 = [flut212](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut212[i](I));
        return ret;
    };

    std::cerr << "\rLUT212   ";
    Ciphertext gin212 = 1 * gout83[0] + 2 * gout119[0];
    std::vector<Ciphertext> gout212 = ctx.eval_lut_amortized(&gin212, lut212);

    std::vector<RotationPoly> lut213;
    std::vector<long (*)(long)> flut213;
    auto lut213idx0 = [](long I) -> long {
        /* GATE 186 (LUT2 _2950_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut213.push_back(ctx.genrate_lut(lut213idx0));
    flut213.push_back(lut213idx0);
    auto lut213idx1 = [](long I) -> long {
        /* GATE 77 (LUT2 _2841_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut213.push_back(ctx.genrate_lut(lut213idx1));
    flut213.push_back(lut213idx1);
    auto fvec213 = [flut213](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut213[i](I));
        return ret;
    };

    std::cerr << "\rLUT213   ";
    Ciphertext gin213 = 1 * gout196[0] + 2 * gout92[0];
    std::vector<Ciphertext> gout213 = ctx.eval_lut_amortized(&gin213, lut213);

    std::vector<RotationPoly> lut214;
    std::vector<long (*)(long)> flut214;
    auto lut214idx0 = [](long I) -> long {
        /* GATE 793 (LUT2 _3557_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin214 = 1 * gout130[0] + 2 * gout42[0];
    std::vector<Ciphertext> gout214 = ctx.eval_lut_amortized(&gin214, lut214);

    std::vector<RotationPoly> lut215;
    std::vector<long (*)(long)> flut215;
    auto lut215idx0 = [](long I) -> long {
        /* GATE 254 (LUT2 _3018_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut215.push_back(ctx.genrate_lut(lut215idx0));
    flut215.push_back(lut215idx0);
    auto lut215idx1 = [](long I) -> long {
        /* GATE 142 (LUT2 _2906_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut215.push_back(ctx.genrate_lut(lut215idx1));
    flut215.push_back(lut215idx1);
    auto fvec215 = [flut215](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut215[i](I));
        return ret;
    };

    std::cerr << "\rLUT215   ";
    Ciphertext gin215 = 1 * gout142[0] + 2 * gout100[1];
    std::vector<Ciphertext> gout215 = ctx.eval_lut_amortized(&gin215, lut215);

    std::vector<RotationPoly> lut216;
    std::vector<long (*)(long)> flut216;
    auto lut216idx0 = [](long I) -> long {
        /* GATE 273 (LUT2 _3037_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin216 = 1 * gout131[1] + 2 * gout60[1];
    std::vector<Ciphertext> gout216 = ctx.eval_lut_amortized(&gin216, lut216);

    std::vector<RotationPoly> lut217;
    std::vector<long (*)(long)> flut217;
    auto lut217idx0 = [](long I) -> long {
        /* GATE 637 (LUT2 _3401_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut217.push_back(ctx.genrate_lut(lut217idx0));
    flut217.push_back(lut217idx0);
    auto lut217idx1 = [](long I) -> long {
        /* GATE 504 (LUT2 _3268_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut217.push_back(ctx.genrate_lut(lut217idx1));
    flut217.push_back(lut217idx1);
    auto fvec217 = [flut217](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut217[i](I));
        return ret;
    };

    std::cerr << "\rLUT217   ";
    Ciphertext gin217 = 1 * gout183[1] + 2 * gout78[1];
    std::vector<Ciphertext> gout217 = ctx.eval_lut_amortized(&gin217, lut217);

    std::vector<RotationPoly> lut218;
    std::vector<long (*)(long)> flut218;
    auto lut218idx0 = [](long I) -> long {
        /* GATE 242 (LUT2 _3006_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut218.push_back(ctx.genrate_lut(lut218idx0));
    flut218.push_back(lut218idx0);
    auto lut218idx1 = [](long I) -> long {
        /* GATE 127 (LUT2 _2891_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut218.push_back(ctx.genrate_lut(lut218idx1));
    flut218.push_back(lut218idx1);
    auto fvec218 = [flut218](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut218[i](I));
        return ret;
    };

    std::cerr << "\rLUT218   ";
    Ciphertext gin218 = 1 * gout95[0] + 2 * gout154[1];
    std::vector<Ciphertext> gout218 = ctx.eval_lut_amortized(&gin218, lut218);

    std::vector<RotationPoly> lut219;
    std::vector<long (*)(long)> flut219;
    auto lut219idx0 = [](long I) -> long {
        /* GATE 723 (LUT2 _3487_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut219.push_back(ctx.genrate_lut(lut219idx0));
    flut219.push_back(lut219idx0);
    auto lut219idx1 = [](long I) -> long {
        /* GATE 610 (LUT2 _3374_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin219 = 1 * gout128[0] + 2 * gout136[1];
    std::vector<Ciphertext> gout219 = ctx.eval_lut_amortized(&gin219, lut219);

    std::vector<RotationPoly> lut220;
    std::vector<long (*)(long)> flut220;
    auto lut220idx0 = [](long I) -> long {
        /* GATE 42 (LUT2 _2806_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut220.push_back(ctx.genrate_lut(lut220idx0));
    flut220.push_back(lut220idx0);
    auto lut220idx1 = [](long I) -> long {
        /* GATE 140 (LUT2 _2904_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut220.push_back(ctx.genrate_lut(lut220idx1));
    flut220.push_back(lut220idx1);
    auto fvec220 = [flut220](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut220[i](I));
        return ret;
    };

    std::cerr << "\rLUT220   ";
    Ciphertext gin220 = 1 * gout165[0] + 2 * gout177[1];
    std::vector<Ciphertext> gout220 = ctx.eval_lut_amortized(&gin220, lut220);

    std::vector<RotationPoly> lut221;
    std::vector<long (*)(long)> flut221;
    auto lut221idx0 = [](long I) -> long {
        /* GATE 597 (LUT2 _3361_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut221.push_back(ctx.genrate_lut(lut221idx0));
    flut221.push_back(lut221idx0);
    auto lut221idx1 = [](long I) -> long {
        /* GATE 472 (LUT2 _3236_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut221.push_back(ctx.genrate_lut(lut221idx1));
    flut221.push_back(lut221idx1);
    auto fvec221 = [flut221](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut221[i](I));
        return ret;
    };

    std::cerr << "\rLUT221   ";
    Ciphertext gin221 = 1 * gout184[1] + 2 * gout105[0];
    std::vector<Ciphertext> gout221 = ctx.eval_lut_amortized(&gin221, lut221);

    std::vector<RotationPoly> lut222;
    std::vector<long (*)(long)> flut222;
    auto lut222idx0 = [](long I) -> long {
        /* GATE 522 (LUT2 _3286_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut222.push_back(ctx.genrate_lut(lut222idx0));
    flut222.push_back(lut222idx0);
    auto lut222idx1 = [](long I) -> long {
        /* GATE 384 (LUT2 _3148_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut222.push_back(ctx.genrate_lut(lut222idx1));
    flut222.push_back(lut222idx1);
    auto fvec222 = [flut222](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut222[i](I));
        return ret;
    };

    std::cerr << "\rLUT222   ";
    Ciphertext gin222 = 1 * gout209[0] + 2 * gout28[1];
    std::vector<Ciphertext> gout222 = ctx.eval_lut_amortized(&gin222, lut222);

    std::vector<RotationPoly> lut223;
    std::vector<long (*)(long)> flut223;
    auto lut223idx0 = [](long I) -> long {
        /* GATE 450 (LUT2 _3214_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin223 = 1 * gout148[1] + 2 * gout39[0];
    std::vector<Ciphertext> gout223 = ctx.eval_lut_amortized(&gin223, lut223);

    std::vector<RotationPoly> lut224;
    std::vector<long (*)(long)> flut224;
    auto lut224idx0 = [](long I) -> long {
        /* GATE 808 (LUT2 _3572_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin224 = 1 * gout176[0] + 2 * gout97[1];
    std::vector<Ciphertext> gout224 = ctx.eval_lut_amortized(&gin224, lut224);

    std::vector<RotationPoly> lut225;
    std::vector<long (*)(long)> flut225;
    auto lut225idx0 = [](long I) -> long {
        /* GATE 446 (LUT2 _3210_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut225.push_back(ctx.genrate_lut(lut225idx0));
    flut225.push_back(lut225idx0);
    auto lut225idx1 = [](long I) -> long {
        /* GATE 328 (LUT2 _3092_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut225.push_back(ctx.genrate_lut(lut225idx1));
    flut225.push_back(lut225idx1);
    auto fvec225 = [flut225](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut225[i](I));
        return ret;
    };

    std::cerr << "\rLUT225   ";
    Ciphertext gin225 = 1 * gout186[1] + 2 * gout61[0];
    std::vector<Ciphertext> gout225 = ctx.eval_lut_amortized(&gin225, lut225);

    std::vector<RotationPoly> lut226;
    std::vector<long (*)(long)> flut226;
    auto lut226idx0 = [](long I) -> long {
        /* GATE 469 (LUT2 _3233_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin226 = 1 * gout202[1] + 2 * gout185[1];
    std::vector<Ciphertext> gout226 = ctx.eval_lut_amortized(&gin226, lut226);

    std::vector<RotationPoly> lut227;
    std::vector<long (*)(long)> flut227;
    auto lut227idx0 = [](long I) -> long {
        /* GATE 117 (LUT2 _2881_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut227.push_back(ctx.genrate_lut(lut227idx0));
    flut227.push_back(lut227idx0);
    auto lut227idx1 = [](long I) -> long {
        /* GATE 33 (LUT2 _2797_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut227.push_back(ctx.genrate_lut(lut227idx1));
    flut227.push_back(lut227idx1);
    auto fvec227 = [flut227](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut227[i](I));
        return ret;
    };

    std::cerr << "\rLUT227   ";
    Ciphertext gin227 = 1 * gout147[0] + 2 * gout157[1];
    std::vector<Ciphertext> gout227 = ctx.eval_lut_amortized(&gin227, lut227);

    std::vector<RotationPoly> lut228;
    std::vector<long (*)(long)> flut228;
    auto lut228idx0 = [](long I) -> long {
        /* GATE 173 (LUT2 _2937_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut228.push_back(ctx.genrate_lut(lut228idx0));
    flut228.push_back(lut228idx0);
    auto fvec228 = [flut228](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut228[i](I));
        return ret;
    };

    std::cerr << "\rLUT228   ";
    Ciphertext gin228 = 1 * gout173[1] + 2 * gout107[1];
    std::vector<Ciphertext> gout228 = ctx.eval_lut_amortized(&gin228, lut228);

    std::vector<RotationPoly> lut229;
    std::vector<long (*)(long)> flut229;
    auto lut229idx0 = [](long I) -> long {
        /* GATE 219 (LUT2 _2983_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut229.push_back(ctx.genrate_lut(lut229idx0));
    flut229.push_back(lut229idx0);
    auto lut229idx1 = [](long I) -> long {
        /* GATE 119 (LUT2 _2883_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut229.push_back(ctx.genrate_lut(lut229idx1));
    flut229.push_back(lut229idx1);
    auto fvec229 = [flut229](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut229[i](I));
        return ret;
    };

    std::cerr << "\rLUT229   ";
    Ciphertext gin229 = 1 * gout198[0] + 2 * gout81[0];
    std::vector<Ciphertext> gout229 = ctx.eval_lut_amortized(&gin229, lut229);

    std::vector<RotationPoly> lut230;
    std::vector<long (*)(long)> flut230;
    auto lut230idx0 = [](long I) -> long {
        /* GATE 825 (LUT2 _3589_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin230 = 1 * gout170[0] + 2 * gout111[0];
    std::vector<Ciphertext> gout230 = ctx.eval_lut_amortized(&gin230, lut230);

    std::vector<RotationPoly> lut231;
    std::vector<long (*)(long)> flut231;
    auto lut231idx0 = [](long I) -> long {
        /* GATE 327 (LUT2 _3091_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut231.push_back(ctx.genrate_lut(lut231idx0));
    flut231.push_back(lut231idx0);
    auto lut231idx1 = [](long I) -> long {
        /* GATE 221 (LUT2 _2985_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut231.push_back(ctx.genrate_lut(lut231idx1));
    flut231.push_back(lut231idx1);
    auto fvec231 = [flut231](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut231[i](I));
        return ret;
    };

    std::cerr << "\rLUT231   ";
    Ciphertext gin231 = 1 * gout197[0] + 2 * gout125[1];
    std::vector<Ciphertext> gout231 = ctx.eval_lut_amortized(&gin231, lut231);

    std::vector<RotationPoly> lut232;
    std::vector<long (*)(long)> flut232;
    auto lut232idx0 = [](long I) -> long {
        /* GATE 163 (LUT2 _2927_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin232 = 1 * gout178[0] + 2 * gout66[1];
    std::vector<Ciphertext> gout232 = ctx.eval_lut_amortized(&gin232, lut232);

    std::vector<RotationPoly> lut233;
    std::vector<long (*)(long)> flut233;
    auto lut233idx0 = [](long I) -> long {
        /* GATE 496 (LUT2 _3260_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin233 = 1 * gout172[1] + 2 * gout106[1];
    std::vector<Ciphertext> gout233 = ctx.eval_lut_amortized(&gin233, lut233);

    std::vector<RotationPoly> lut234;
    std::vector<long (*)(long)> flut234;
    auto lut234idx0 = [](long I) -> long {
        /* GATE 797 (LUT2 _3561_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin234 = 1 * gout138[1] + 2 * gout41[1];
    std::vector<Ciphertext> gout234 = ctx.eval_lut_amortized(&gin234, lut234);

    std::vector<RotationPoly> lut235;
    std::vector<long (*)(long)> flut235;
    auto lut235idx0 = [](long I) -> long {
        /* GATE 278 (LUT2 _3042_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin235 = 1 * gout167[0] + 2 * gout48[1];
    std::vector<Ciphertext> gout235 = ctx.eval_lut_amortized(&gin235, lut235);

    std::vector<RotationPoly> lut236;
    std::vector<long (*)(long)> flut236;
    auto lut236idx0 = [](long I) -> long {
        /* GATE 792 (LUT2 _3556_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut236.push_back(ctx.genrate_lut(lut236idx0));
    flut236.push_back(lut236idx0);
    auto lut236idx1 = [](long I) -> long {
        /* GATE 679 (LUT2 _3443_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut236.push_back(ctx.genrate_lut(lut236idx1));
    flut236.push_back(lut236idx1);
    auto fvec236 = [flut236](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut236[i](I));
        return ret;
    };

    std::cerr << "\rLUT236   ";
    Ciphertext gin236 = 1 * gout175[0] + 2 * gout130[1];
    std::vector<Ciphertext> gout236 = ctx.eval_lut_amortized(&gin236, lut236);

    std::vector<RotationPoly> lut237;
    std::vector<long (*)(long)> flut237;
    auto lut237idx0 = [](long I) -> long {
        /* GATE 636 (LUT2 _3400_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin237 = 1 * gout217[0] + 2 * gout183[0];
    std::vector<Ciphertext> gout237 = ctx.eval_lut_amortized(&gin237, lut237);

    std::vector<RotationPoly> lut238;
    std::vector<long (*)(long)> flut238;
    auto lut238idx0 = [](long I) -> long {
        /* GATE 191 (LUT2 _2955_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut238.push_back(ctx.genrate_lut(lut238idx0));
    flut238.push_back(lut238idx0);
    auto lut238idx1 = [](long I) -> long {
        /* GATE 88 (LUT2 _2852_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut238.push_back(ctx.genrate_lut(lut238idx1));
    flut238.push_back(lut238idx1);
    auto fvec238 = [flut238](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut238[i](I));
        return ret;
    };

    std::cerr << "\rLUT238   ";
    Ciphertext gin238 = 1 * gout180[0] + 2 * gout84[1];
    std::vector<Ciphertext> gout238 = ctx.eval_lut_amortized(&gin238, lut238);

    std::vector<RotationPoly> lut239;
    std::vector<long (*)(long)> flut239;
    auto lut239idx0 = [](long I) -> long {
        /* GATE 821 (LUT2 _3585_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin239 = 1 * gout193[1] + 2 * gout171[1];
    std::vector<Ciphertext> gout239 = ctx.eval_lut_amortized(&gin239, lut239);

    std::vector<RotationPoly> lut240;
    std::vector<long (*)(long)> flut240;
    auto lut240idx0 = [](long I) -> long {
        /* GATE 153 (LUT2 _2917_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut240.push_back(ctx.genrate_lut(lut240idx0));
    flut240.push_back(lut240idx0);
    auto lut240idx1 = [](long I) -> long {
        /* GATE 55 (LUT2 _2819_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut240.push_back(ctx.genrate_lut(lut240idx1));
    flut240.push_back(lut240idx1);
    auto fvec240 = [flut240](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut240[i](I));
        return ret;
    };

    std::cerr << "\rLUT240   ";
    Ciphertext gin240 = 1 * gout169[0] + 2 * gout68[0];
    std::vector<Ciphertext> gout240 = ctx.eval_lut_amortized(&gin240, lut240);

    std::vector<RotationPoly> lut241;
    std::vector<long (*)(long)> flut241;
    auto lut241idx0 = [](long I) -> long {
        /* GATE 588 (LUT2 _3352_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut241.push_back(ctx.genrate_lut(lut241idx0));
    flut241.push_back(lut241idx0);
    auto lut241idx1 = [](long I) -> long {
        /* GATE 713 (LUT2 _3477_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut241.push_back(ctx.genrate_lut(lut241idx1));
    flut241.push_back(lut241idx1);
    auto fvec241 = [flut241](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut241[i](I));
        return ret;
    };

    std::cerr << "\rLUT241   ";
    Ciphertext gin241 = 1 * gout101[0] + 2 * gout153[1];
    std::vector<Ciphertext> gout241 = ctx.eval_lut_amortized(&gin241, lut241);

    std::vector<RotationPoly> lut242;
    std::vector<long (*)(long)> flut242;
    auto lut242idx0 = [](long I) -> long {
        /* GATE 185 (LUT2 _2949_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin242 = 1 * gout213[0] + 2 * gout196[1];
    std::vector<Ciphertext> gout242 = ctx.eval_lut_amortized(&gin242, lut242);

    std::vector<RotationPoly> lut243;
    std::vector<long (*)(long)> flut243;
    auto lut243idx0 = [](long I) -> long {
        /* GATE 878 (LUT2 _3642_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut243.push_back(ctx.genrate_lut(lut243idx0));
    flut243.push_back(lut243idx0);
    auto lut243idx1 = [](long I) -> long {
        /* GATE 796 (LUT2 _3560_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut243.push_back(ctx.genrate_lut(lut243idx1));
    flut243.push_back(lut243idx1);
    auto fvec243 = [flut243](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut243[i](I));
        return ret;
    };

    std::cerr << "\rLUT243   ";
    Ciphertext gin243 = 1 * gout234[0] + 2 * gout121[0];
    std::vector<Ciphertext> gout243 = ctx.eval_lut_amortized(&gin243, lut243);

    std::vector<RotationPoly> lut244;
    std::vector<long (*)(long)> flut244;
    auto lut244idx0 = [](long I) -> long {
        /* GATE 160 (LUT2 _2924_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut244.push_back(ctx.genrate_lut(lut244idx0));
    flut244.push_back(lut244idx0);
    auto lut244idx1 = [](long I) -> long {
        /* GATE 68 (LUT2 _2832_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut244.push_back(ctx.genrate_lut(lut244idx1));
    flut244.push_back(lut244idx1);
    auto fvec244 = [flut244](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut244[i](I));
        return ret;
    };

    std::cerr << "\rLUT244   ";
    Ciphertext gin244 = 1 * gout158[0] + 2 * gout168[1];
    std::vector<Ciphertext> gout244 = ctx.eval_lut_amortized(&gin244, lut244);

    std::vector<RotationPoly> lut245;
    std::vector<long (*)(long)> flut245;
    auto lut245idx0 = [](long I) -> long {
        /* GATE 562 (LUT2 _3326_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut245.push_back(ctx.genrate_lut(lut245idx0));
    flut245.push_back(lut245idx0);
    auto lut245idx1 = [](long I) -> long {
        /* GATE 449 (LUT2 _3213_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut245.push_back(ctx.genrate_lut(lut245idx1));
    flut245.push_back(lut245idx1);
    auto fvec245 = [flut245](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut245[i](I));
        return ret;
    };

    std::cerr << "\rLUT245   ";
    Ciphertext gin245 = 1 * gout223[0] + 2 * gout31[0];
    std::vector<Ciphertext> gout245 = ctx.eval_lut_amortized(&gin245, lut245);

    std::vector<RotationPoly> lut246;
    std::vector<long (*)(long)> flut246;
    auto lut246idx0 = [](long I) -> long {
        /* GATE 603 (LUT2 _3367_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut246.push_back(ctx.genrate_lut(lut246idx0));
    flut246.push_back(lut246idx0);
    auto lut246idx1 = [](long I) -> long {
        /* GATE 468 (LUT2 _3232_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut246.push_back(ctx.genrate_lut(lut246idx1));
    flut246.push_back(lut246idx1);
    auto fvec246 = [flut246](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut246[i](I));
        return ret;
    };

    std::cerr << "\rLUT246   ";
    Ciphertext gin246 = 1 * gout226[0] + 2 * gout221[1];
    std::vector<Ciphertext> gout246 = ctx.eval_lut_amortized(&gin246, lut246);

    std::vector<RotationPoly> lut247;
    std::vector<long (*)(long)> flut247;
    auto lut247idx0 = [](long I) -> long {
        /* GATE 694 (LUT2 _3458_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin247 = 1 * gout194[0] + 2 * gout109[1];
    std::vector<Ciphertext> gout247 = ctx.eval_lut_amortized(&gin247, lut247);

    std::vector<RotationPoly> lut248;
    std::vector<long (*)(long)> flut248;
    auto lut248idx0 = [](long I) -> long {
        /* GATE 64 (LUT2 _2828_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut248.push_back(ctx.genrate_lut(lut248idx0));
    flut248.push_back(lut248idx0);
    auto lut248idx1 = [](long I) -> long {
        /* GATE 2 (LUT2 _2766_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut248.push_back(ctx.genrate_lut(lut248idx1));
    flut248.push_back(lut248idx1);
    auto fvec248 = [flut248](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut248[i](I));
        return ret;
    };

    std::cerr << "\rLUT248   ";
    Ciphertext gin248 = 1 * gout195[1] + 2 * gout162[1];
    std::vector<Ciphertext> gout248 = ctx.eval_lut_amortized(&gin248, lut248);

    std::vector<RotationPoly> lut249;
    std::vector<long (*)(long)> flut249;
    auto lut249idx0 = [](long I) -> long {
        /* GATE 118 (LUT2 _2882_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut249.push_back(ctx.genrate_lut(lut249idx0));
    flut249.push_back(lut249idx0);
    auto lut249idx1 = [](long I) -> long {
        /* GATE 218 (LUT2 _2982_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut249.push_back(ctx.genrate_lut(lut249idx1));
    flut249.push_back(lut249idx1);
    auto fvec249 = [flut249](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut249[i](I));
        return ret;
    };

    std::cerr << "\rLUT249   ";
    Ciphertext gin249 = 1 * gout229[1] + 2 * gout15[0];
    std::vector<Ciphertext> gout249 = ctx.eval_lut_amortized(&gin249, lut249);

    std::vector<RotationPoly> lut250;
    std::vector<long (*)(long)> flut250;
    auto lut250idx0 = [](long I) -> long {
        /* GATE 372 (LUT2 _3136_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut250.push_back(ctx.genrate_lut(lut250idx0));
    flut250.push_back(lut250idx0);
    auto lut250idx1 = [](long I) -> long {
        /* GATE 266 (LUT2 _3030_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut250.push_back(ctx.genrate_lut(lut250idx1));
    flut250.push_back(lut250idx1);
    auto fvec250 = [flut250](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut250[i](I));
        return ret;
    };

    std::cerr << "\rLUT250   ";
    Ciphertext gin250 = 1 * gout206[1] + 2 * gout216[0];
    std::vector<Ciphertext> gout250 = ctx.eval_lut_amortized(&gin250, lut250);

    std::vector<RotationPoly> lut251;
    std::vector<long (*)(long)> flut251;
    auto lut251idx0 = [](long I) -> long {
        /* GATE 521 (LUT2 _3285_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin251 = 1 * gout222[0] + 2 * gout209[1];
    std::vector<Ciphertext> gout251 = ctx.eval_lut_amortized(&gin251, lut251);

    std::vector<RotationPoly> lut252;
    std::vector<long (*)(long)> flut252;
    auto lut252idx0 = [](long I) -> long {
        /* GATE 361 (LUT2 _3125_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin252 = 1 * gout182[0] + 2 * gout163[0];
    std::vector<Ciphertext> gout252 = ctx.eval_lut_amortized(&gin252, lut252);

    std::vector<RotationPoly> lut253;
    std::vector<long (*)(long)> flut253;
    auto lut253idx0 = [](long I) -> long {
        /* GATE 701 (LUT2 _3465_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut253.push_back(ctx.genrate_lut(lut253idx0));
    flut253.push_back(lut253idx0);
    auto lut253idx1 = [](long I) -> long {
        /* GATE 573 (LUT2 _3337_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut253.push_back(ctx.genrate_lut(lut253idx1));
    flut253.push_back(lut253idx1);
    auto fvec253 = [flut253](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut253[i](I));
        return ret;
    };

    std::cerr << "\rLUT253   ";
    Ciphertext gin253 = 1 * gout85[0] + 2 * gout194[1];
    std::vector<Ciphertext> gout253 = ctx.eval_lut_amortized(&gin253, lut253);

    std::vector<RotationPoly> lut254;
    std::vector<long (*)(long)> flut254;
    auto lut254idx0 = [](long I) -> long {
        /* GATE 375 (LUT2 _3139_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut254.push_back(ctx.genrate_lut(lut254idx0));
    flut254.push_back(lut254idx0);
    auto lut254idx1 = [](long I) -> long {
        /* GATE 493 (LUT2 _3257_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut254.push_back(ctx.genrate_lut(lut254idx1));
    flut254.push_back(lut254idx1);
    auto fvec254 = [flut254](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut254[i](I));
        return ret;
    };

    std::cerr << "\rLUT254   ";
    Ciphertext gin254 = 1 * gout181[0] + 2 * gout44[1];
    std::vector<Ciphertext> gout254 = ctx.eval_lut_amortized(&gin254, lut254);

    std::vector<RotationPoly> lut255;
    std::vector<long (*)(long)> flut255;
    auto lut255idx0 = [](long I) -> long {
        /* GATE 813 (LUT2 _3577_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut255.push_back(ctx.genrate_lut(lut255idx0));
    flut255.push_back(lut255idx0);
    auto lut255idx1 = [](long I) -> long {
        /* GATE 703 (LUT2 _3467_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut255.push_back(ctx.genrate_lut(lut255idx1));
    flut255.push_back(lut255idx1);
    auto fvec255 = [flut255](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut255[i](I));
        return ret;
    };

    std::cerr << "\rLUT255   ";
    Ciphertext gin255 = 1 * gout187[0] + 2 * gout176[1];
    std::vector<Ciphertext> gout255 = ctx.eval_lut_amortized(&gin255, lut255);

    std::vector<RotationPoly> lut256;
    std::vector<long (*)(long)> flut256;
    auto lut256idx0 = [](long I) -> long {
        /* GATE 482 (LUT2 _3246_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut256.push_back(ctx.genrate_lut(lut256idx0));
    flut256.push_back(lut256idx0);
    auto lut256idx1 = [](long I) -> long {
        /* GATE 352 (LUT2 _3116_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut256.push_back(ctx.genrate_lut(lut256idx1));
    flut256.push_back(lut256idx1);
    auto fvec256 = [flut256](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut256[i](I));
        return ret;
    };

    std::cerr << "\rLUT256   ";
    Ciphertext gin256 = 1 * gout201[1] + 2 * gout172[0];
    std::vector<Ciphertext> gout256 = ctx.eval_lut_amortized(&gin256, lut256);

    std::vector<RotationPoly> lut257;
    std::vector<long (*)(long)> flut257;
    auto lut257idx0 = [](long I) -> long {
        /* GATE 116 (LUT2 _2880_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut257.push_back(ctx.genrate_lut(lut257idx0));
    flut257.push_back(lut257idx0);
    auto lut257idx1 = [](long I) -> long {
        /* GATE 32 (LUT2 _2796_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut257.push_back(ctx.genrate_lut(lut257idx1));
    flut257.push_back(lut257idx1);
    auto fvec257 = [flut257](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut257[i](I));
        return ret;
    };

    std::cerr << "\rLUT257   ";
    Ciphertext gin257 = 1 * gout227[1] + 2 * gout52[0];
    std::vector<Ciphertext> gout257 = ctx.eval_lut_amortized(&gin257, lut257);

    std::vector<RotationPoly> lut258;
    std::vector<long (*)(long)> flut258;
    auto lut258idx0 = [](long I) -> long {
        /* GATE 843 (LUT2 _3607_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut258.push_back(ctx.genrate_lut(lut258idx0));
    flut258.push_back(lut258idx0);
    auto lut258idx1 = [](long I) -> long {
        /* GATE 734 (LUT2 _3498_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut258.push_back(ctx.genrate_lut(lut258idx1));
    flut258.push_back(lut258idx1);
    auto fvec258 = [flut258](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut258[i](I));
        return ret;
    };

    std::cerr << "\rLUT258   ";
    Ciphertext gin258 = 1 * gout204[1] + 2 * gout82[1];
    std::vector<Ciphertext> gout258 = ctx.eval_lut_amortized(&gin258, lut258);

    std::vector<RotationPoly> lut259;
    std::vector<long (*)(long)> flut259;
    auto lut259idx0 = [](long I) -> long {
        /* GATE 217 (LUT2 _2981_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin259 = 1 * gout249[1] + 2 * gout229[0];
    std::vector<Ciphertext> gout259 = ctx.eval_lut_amortized(&gin259, lut259);

    std::vector<RotationPoly> lut260;
    std::vector<long (*)(long)> flut260;
    auto lut260idx0 = [](long I) -> long {
        /* GATE 115 (LUT2 _2879_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin260 = 1 * gout257[0] + 2 * gout227[0];
    std::vector<Ciphertext> gout260 = ctx.eval_lut_amortized(&gin260, lut260);

    std::vector<RotationPoly> lut261;
    std::vector<long (*)(long)> flut261;
    auto lut261idx0 = [](long I) -> long {
        /* GATE 403 (LUT2 _3167_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut261.push_back(ctx.genrate_lut(lut261idx0));
    flut261.push_back(lut261idx0);
    auto lut261idx1 = [](long I) -> long {
        /* GATE 277 (LUT2 _3041_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin261 = 1 * gout235[0] + 2 * gout122[0];
    std::vector<Ciphertext> gout261 = ctx.eval_lut_amortized(&gin261, lut261);

    std::vector<RotationPoly> lut262;
    std::vector<long (*)(long)> flut262;
    auto lut262idx0 = [](long I) -> long {
        /* GATE 172 (LUT2 _2936_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut262.push_back(ctx.genrate_lut(lut262idx0));
    flut262.push_back(lut262idx0);
    auto lut262idx1 = [](long I) -> long {
        /* GATE 295 (LUT2 _3059_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut262.push_back(ctx.genrate_lut(lut262idx1));
    flut262.push_back(lut262idx1);
    auto fvec262 = [flut262](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut262[i](I));
        return ret;
    };

    std::cerr << "\rLUT262   ";
    Ciphertext gin262 = 1 * gout228[0] + 2 * gout167[1];
    std::vector<Ciphertext> gout262 = ctx.eval_lut_amortized(&gin262, lut262);

    std::vector<RotationPoly> lut263;
    std::vector<long (*)(long)> flut263;
    auto lut263idx0 = [](long I) -> long {
        /* GATE 294 (LUT2 _3058_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut263.push_back(ctx.genrate_lut(lut263idx0));
    flut263.push_back(lut263idx0);
    auto lut263idx1 = [](long I) -> long {
        /* GATE 171 (LUT2 _2935_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut263.push_back(ctx.genrate_lut(lut263idx1));
    flut263.push_back(lut263idx1);
    auto fvec263 = [flut263](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut263[i](I));
        return ret;
    };

    std::cerr << "\rLUT263   ";
    Ciphertext gin263 = 1 * gout262[0] + 2 * gout115[0];
    std::vector<Ciphertext> gout263 = ctx.eval_lut_amortized(&gin263, lut263);

    std::vector<RotationPoly> lut264;
    std::vector<long (*)(long)> flut264;
    auto lut264idx0 = [](long I) -> long {
        /* GATE 702 (LUT2 _3466_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut264.push_back(ctx.genrate_lut(lut264idx0));
    flut264.push_back(lut264idx0);
    auto lut264idx1 = [](long I) -> long {
        /* GATE 812 (LUT2 _3576_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut264.push_back(ctx.genrate_lut(lut264idx1));
    flut264.push_back(lut264idx1);
    auto fvec264 = [flut264](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut264[i](I));
        return ret;
    };

    std::cerr << "\rLUT264   ";
    Ciphertext gin264 = 1 * gout255[1] + 2 * gout170[1];
    std::vector<Ciphertext> gout264 = ctx.eval_lut_amortized(&gin264, lut264);

    std::vector<RotationPoly> lut265;
    std::vector<long (*)(long)> flut265;
    auto lut265idx0 = [](long I) -> long {
        /* GATE 253 (LUT2 _3017_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin265 = 1 * gout215[0] + 2 * gout142[1];
    std::vector<Ciphertext> gout265 = ctx.eval_lut_amortized(&gin265, lut265);

    std::vector<RotationPoly> lut266;
    std::vector<long (*)(long)> flut266;
    auto lut266idx0 = [](long I) -> long {
        /* GATE 884 (LUT2 _3648_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut266.push_back(ctx.genrate_lut(lut266idx0));
    flut266.push_back(lut266idx0);
    auto lut266idx1 = [](long I) -> long {
        /* GATE 824 (LUT2 _3588_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut266.push_back(ctx.genrate_lut(lut266idx1));
    flut266.push_back(lut266idx1);
    auto fvec266 = [flut266](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut266[i](I));
        return ret;
    };

    std::cerr << "\rLUT266   ";
    Ciphertext gin266 = 1 * gout230[0] + 2 * gout150[0];
    std::vector<Ciphertext> gout266 = ctx.eval_lut_amortized(&gin266, lut266);

    std::vector<RotationPoly> lut267;
    std::vector<long (*)(long)> flut267;
    auto lut267idx0 = [](long I) -> long {
        /* GATE 114 (LUT2 _2878_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut267.push_back(ctx.genrate_lut(lut267idx0));
    flut267.push_back(lut267idx0);
    auto lut267idx1 = [](long I) -> long {
        /* GATE 214 (LUT2 _2978_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut267.push_back(ctx.genrate_lut(lut267idx1));
    flut267.push_back(lut267idx1);
    auto fvec267 = [flut267](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut267[i](I));
        return ret;
    };

    std::cerr << "\rLUT267   ";
    Ciphertext gin267 = 1 * gout260[0] + 2 * gout249[0];
    std::vector<Ciphertext> gout267 = ctx.eval_lut_amortized(&gin267, lut267);

    std::vector<RotationPoly> lut268;
    std::vector<long (*)(long)> flut268;
    auto lut268idx0 = [](long I) -> long {
        /* GATE 374 (LUT2 _3138_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut268.push_back(ctx.genrate_lut(lut268idx0));
    flut268.push_back(lut268idx0);
    auto lut268idx1 = [](long I) -> long {
        /* GATE 492 (LUT2 _3256_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut268.push_back(ctx.genrate_lut(lut268idx1));
    flut268.push_back(lut268idx1);
    auto fvec268 = [flut268](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut268[i](I));
        return ret;
    };

    std::cerr << "\rLUT268   ";
    Ciphertext gin268 = 1 * gout254[0] + 2 * gout192[0];
    std::vector<Ciphertext> gout268 = ctx.eval_lut_amortized(&gin268, lut268);

    std::vector<RotationPoly> lut269;
    std::vector<long (*)(long)> flut269;
    auto lut269idx0 = [](long I) -> long {
        /* GATE 241 (LUT2 _3005_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin269 = 1 * gout218[0] + 2 * gout154[0];
    std::vector<Ciphertext> gout269 = ctx.eval_lut_amortized(&gin269, lut269);

    std::vector<RotationPoly> lut270;
    std::vector<long (*)(long)> flut270;
    auto lut270idx0 = [](long I) -> long {
        /* GATE 722 (LUT2 _3486_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut270.push_back(ctx.genrate_lut(lut270idx0));
    flut270.push_back(lut270idx0);
    auto lut270idx1 = [](long I) -> long {
        /* GATE 609 (LUT2 _3373_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut270.push_back(ctx.genrate_lut(lut270idx1));
    flut270.push_back(lut270idx1);
    auto fvec270 = [flut270](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut270[i](I));
        return ret;
    };

    std::cerr << "\rLUT270   ";
    Ciphertext gin270 = 1 * gout219[1] + 2 * gout210[0];
    std::vector<Ciphertext> gout270 = ctx.eval_lut_amortized(&gin270, lut270);

    std::vector<RotationPoly> lut271;
    std::vector<long (*)(long)> flut271;
    auto lut271idx0 = [](long I) -> long {
        /* GATE 584 (LUT2 _3348_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin271 = 1 * gout207[0] + 2 * gout190[0];
    std::vector<Ciphertext> gout271 = ctx.eval_lut_amortized(&gin271, lut271);

    std::vector<RotationPoly> lut272;
    std::vector<long (*)(long)> flut272;
    auto lut272idx0 = [](long I) -> long {
        /* GATE 587 (LUT2 _3351_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut272.push_back(ctx.genrate_lut(lut272idx0));
    flut272.push_back(lut272idx0);
    auto lut272idx1 = [](long I) -> long {
        /* GATE 712 (LUT2 _3476_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut272.push_back(ctx.genrate_lut(lut272idx1));
    flut272.push_back(lut272idx1);
    auto fvec272 = [flut272](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut272[i](I));
        return ret;
    };

    std::cerr << "\rLUT272   ";
    Ciphertext gin272 = 1 * gout241[0] + 2 * gout35[1];
    std::vector<Ciphertext> gout272 = ctx.eval_lut_amortized(&gin272, lut272);

    std::vector<RotationPoly> lut273;
    std::vector<long (*)(long)> flut273;
    auto lut273idx0 = [](long I) -> long {
        /* GATE 54 (LUT2 _2818_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut273.push_back(ctx.genrate_lut(lut273idx0));
    flut273.push_back(lut273idx0);
    auto lut273idx1 = [](long I) -> long {
        /* GATE 152 (LUT2 _2916_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut273.push_back(ctx.genrate_lut(lut273idx1));
    flut273.push_back(lut273idx1);
    auto fvec273 = [flut273](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut273[i](I));
        return ret;
    };

    std::cerr << "\rLUT273   ";
    Ciphertext gin273 = 1 * gout240[1] + 2 * gout178[1];
    std::vector<Ciphertext> gout273 = ctx.eval_lut_amortized(&gin273, lut273);

    std::vector<RotationPoly> lut274;
    std::vector<long (*)(long)> flut274;
    auto lut274idx0 = [](long I) -> long {
        /* GATE 31 (LUT2 _2795_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut274.push_back(ctx.genrate_lut(lut274idx0));
    flut274.push_back(lut274idx0);
    auto lut274idx1 = [](long I) -> long {
        /* GATE 112 (LUT2 _2876_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut274.push_back(ctx.genrate_lut(lut274idx1));
    flut274.push_back(lut274idx1);
    auto fvec274 = [flut274](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut274[i](I));
        return ret;
    };

    std::cerr << "\rLUT274   ";
    Ciphertext gin274 = 1 * gout257[1] + 2 * gout132[1];
    std::vector<Ciphertext> gout274 = ctx.eval_lut_amortized(&gin274, lut274);

    std::vector<RotationPoly> lut275;
    std::vector<long (*)(long)> flut275;
    auto lut275idx0 = [](long I) -> long {
        /* GATE 561 (LUT2 _3325_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut275.push_back(ctx.genrate_lut(lut275idx0));
    flut275.push_back(lut275idx0);
    auto lut275idx1 = [](long I) -> long {
        /* GATE 448 (LUT2 _3212_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut275.push_back(ctx.genrate_lut(lut275idx1));
    flut275.push_back(lut275idx1);
    auto fvec275 = [flut275](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut275[i](I));
        return ret;
    };

    std::cerr << "\rLUT275   ";
    Ciphertext gin275 = 1 * gout245[1] + 2 * gout73[1];
    std::vector<Ciphertext> gout275 = ctx.eval_lut_amortized(&gin275, lut275);

    std::vector<RotationPoly> lut276;
    std::vector<long (*)(long)> flut276;
    auto lut276idx0 = [](long I) -> long {
        /* GATE 596 (LUT2 _3360_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin276 = 1 * gout221[0] + 2 * gout184[0];
    std::vector<Ciphertext> gout276 = ctx.eval_lut_amortized(&gin276, lut276);

    std::vector<RotationPoly> lut277;
    std::vector<long (*)(long)> flut277;
    auto lut277idx0 = [](long I) -> long {
        /* GATE 368 (LUT2 _3132_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut277.push_back(ctx.genrate_lut(lut277idx0));
    flut277.push_back(lut277idx0);
    auto lut277idx1 = [](long I) -> long {
        /* GATE 240 (LUT2 _3004_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut277.push_back(ctx.genrate_lut(lut277idx1));
    flut277.push_back(lut277idx1);
    auto fvec277 = [flut277](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut277[i](I));
        return ret;
    };

    std::cerr << "\rLUT277   ";
    Ciphertext gin277 = 1 * gout269[0] + 2 * gout182[1];
    std::vector<Ciphertext> gout277 = ctx.eval_lut_amortized(&gin277, lut277);

    std::vector<RotationPoly> lut278;
    std::vector<long (*)(long)> flut278;
    auto lut278idx0 = [](long I) -> long {
        /* GATE 791 (LUT2 _3555_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut278.push_back(ctx.genrate_lut(lut278idx0));
    flut278.push_back(lut278idx0);
    auto lut278idx1 = [](long I) -> long {
        /* GATE 678 (LUT2 _3442_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut278.push_back(ctx.genrate_lut(lut278idx1));
    flut278.push_back(lut278idx1);
    auto fvec278 = [flut278](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut278[i](I));
        return ret;
    };

    std::cerr << "\rLUT278   ";
    Ciphertext gin278 = 1 * gout236[1] + 2 * gout138[0];
    std::vector<Ciphertext> gout278 = ctx.eval_lut_amortized(&gin278, lut278);

    std::vector<RotationPoly> lut279;
    std::vector<long (*)(long)> flut279;
    auto lut279idx0 = [](long I) -> long {
        /* GATE 350 (LUT2 _3114_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut279.push_back(ctx.genrate_lut(lut279idx0));
    flut279.push_back(lut279idx0);
    auto lut279idx1 = [](long I) -> long {
        /* GATE 229 (LUT2 _2993_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut279.push_back(ctx.genrate_lut(lut279idx1));
    flut279.push_back(lut279idx1);
    auto fvec279 = [flut279](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut279[i](I));
        return ret;
    };

    std::cerr << "\rLUT279   ";
    Ciphertext gin279 = 1 * gout188[0] + 2 * gout212[0];
    std::vector<Ciphertext> gout279 = ctx.eval_lut_amortized(&gin279, lut279);

    std::vector<RotationPoly> lut280;
    std::vector<long (*)(long)> flut280;
    auto lut280idx0 = [](long I) -> long {
        /* GATE 674 (LUT2 _3438_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut280.push_back(ctx.genrate_lut(lut280idx0));
    flut280.push_back(lut280idx0);
    auto lut280idx1 = [](long I) -> long {
        /* GATE 787 (LUT2 _3551_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut280.push_back(ctx.genrate_lut(lut280idx1));
    flut280.push_back(lut280idx1);
    auto fvec280 = [flut280](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut280[i](I));
        return ret;
    };

    std::cerr << "\rLUT280   ";
    Ciphertext gin280 = 1 * gout159[0] + 2 * gout278[1];
    std::vector<Ciphertext> gout280 = ctx.eval_lut_amortized(&gin280, lut280);

    std::vector<RotationPoly> lut281;
    std::vector<long (*)(long)> flut281;
    auto lut281idx0 = [](long I) -> long {
        /* GATE 151 (LUT2 _2915_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin281 = 1 * gout273[1] + 2 * gout240[0];
    std::vector<Ciphertext> gout281 = ctx.eval_lut_amortized(&gin281, lut281);

    std::vector<RotationPoly> lut282;
    std::vector<long (*)(long)> flut282;
    auto lut282idx0 = [](long I) -> long {
        /* GATE 687 (LUT2 _3451_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut282.push_back(ctx.genrate_lut(lut282idx0));
    flut282.push_back(lut282idx0);
    auto lut282idx1 = [](long I) -> long {
        /* GATE 806 (LUT2 _3570_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut282.push_back(ctx.genrate_lut(lut282idx1));
    flut282.push_back(lut282idx1);
    auto fvec282 = [flut282](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut282[i](I));
        return ret;
    };

    std::cerr << "\rLUT282   ";
    Ciphertext gin282 = 1 * gout247[0] + 2 * gout137[1];
    std::vector<Ciphertext> gout282 = ctx.eval_lut_amortized(&gin282, lut282);

    std::vector<RotationPoly> lut283;
    std::vector<long (*)(long)> flut283;
    auto lut283idx0 = [](long I) -> long {
        /* GATE 445 (LUT2 _3209_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin283 = 1 * gout225[0] + 2 * gout186[0];
    std::vector<Ciphertext> gout283 = ctx.eval_lut_amortized(&gin283, lut283);

    std::vector<RotationPoly> lut284;
    std::vector<long (*)(long)> flut284;
    auto lut284idx0 = [](long I) -> long {
        /* GATE 87 (LUT2 _2851_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut284.push_back(ctx.genrate_lut(lut284idx0));
    flut284.push_back(lut284idx0);
    auto lut284idx1 = [](long I) -> long {
        /* GATE 1 (LUT2 _2765_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut284.push_back(ctx.genrate_lut(lut284idx1));
    flut284.push_back(lut284idx1);
    auto fvec284 = [flut284](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut284[i](I));
        return ret;
    };

    std::cerr << "\rLUT284   ";
    Ciphertext gin284 = 1 * gout248[1] + 2 * gout164[0];
    std::vector<Ciphertext> gout284 = ctx.eval_lut_amortized(&gin284, lut284);

    std::vector<RotationPoly> lut285;
    std::vector<long (*)(long)> flut285;
    auto lut285idx0 = [](long I) -> long {
        /* GATE 220 (LUT2 _2984_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut285.push_back(ctx.genrate_lut(lut285idx0));
    flut285.push_back(lut285idx0);
    auto lut285idx1 = [](long I) -> long {
        /* GATE 326 (LUT2 _3090_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut285.push_back(ctx.genrate_lut(lut285idx1));
    flut285.push_back(lut285idx1);
    auto fvec285 = [flut285](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut285[i](I));
        return ret;
    };

    std::cerr << "\rLUT285   ";
    Ciphertext gin285 = 1 * gout231[1] + 2 * gout118[0];
    std::vector<Ciphertext> gout285 = ctx.eval_lut_amortized(&gin285, lut285);

    std::vector<RotationPoly> lut286;
    std::vector<long (*)(long)> flut286;
    auto lut286idx0 = [](long I) -> long {
        /* GATE 811 (LUT2 _3575_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin286 = 1 * gout264[1] + 2 * gout255[0];
    std::vector<Ciphertext> gout286 = ctx.eval_lut_amortized(&gin286, lut286);

    std::vector<RotationPoly> lut287;
    std::vector<long (*)(long)> flut287;
    auto lut287idx0 = [](long I) -> long {
        /* GATE 139 (LUT2 _2903_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin287 = 1 * gout220[1] + 2 * gout177[0];
    std::vector<Ciphertext> gout287 = ctx.eval_lut_amortized(&gin287, lut287);

    std::vector<RotationPoly> lut288;
    std::vector<long (*)(long)> flut288;
    auto lut288idx0 = [](long I) -> long {
        /* GATE 293 (LUT2 _3057_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin288 = 1 * gout263[0] + 2 * gout262[1];
    std::vector<Ciphertext> gout288 = ctx.eval_lut_amortized(&gin288, lut288);

    std::vector<RotationPoly> lut289;
    std::vector<long (*)(long)> flut289;
    auto lut289idx0 = [](long I) -> long {
        /* GATE 481 (LUT2 _3245_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin289 = 1 * gout256[0] + 2 * gout201[0];
    std::vector<Ciphertext> gout289 = ctx.eval_lut_amortized(&gin289, lut289);

    std::vector<RotationPoly> lut290;
    std::vector<long (*)(long)> flut290;
    auto lut290idx0 = [](long I) -> long {
        /* GATE 162 (LUT2 _2926_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut290.push_back(ctx.genrate_lut(lut290idx0));
    flut290.push_back(lut290idx0);
    auto lut290idx1 = [](long I) -> long {
        /* GATE 265 (LUT2 _3029_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut290.push_back(ctx.genrate_lut(lut290idx1));
    flut290.push_back(lut290idx1);
    auto fvec290 = [flut290](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut290[i](I));
        return ret;
    };

    std::cerr << "\rLUT290   ";
    Ciphertext gin290 = 1 * gout232[0] + 2 * gout131[0];
    std::vector<Ciphertext> gout290 = ctx.eval_lut_amortized(&gin290, lut290);

    std::vector<RotationPoly> lut291;
    std::vector<long (*)(long)> flut291;
    auto lut291idx0 = [](long I) -> long {
        /* GATE 608 (LUT2 _3372_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut291.push_back(ctx.genrate_lut(lut291idx0));
    flut291.push_back(lut291idx0);
    auto lut291idx1 = [](long I) -> long {
        /* GATE 495 (LUT2 _3259_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut291.push_back(ctx.genrate_lut(lut291idx1));
    flut291.push_back(lut291idx1);
    auto fvec291 = [flut291](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut291[i](I));
        return ret;
    };

    std::cerr << "\rLUT291   ";
    Ciphertext gin291 = 1 * gout233[0] + 2 * gout203[1];
    std::vector<Ciphertext> gout291 = ctx.eval_lut_amortized(&gin291, lut291);

    std::vector<RotationPoly> lut292;
    std::vector<long (*)(long)> flut292;
    auto lut292idx0 = [](long I) -> long {
        /* GATE 159 (LUT2 _2923_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut292.push_back(ctx.genrate_lut(lut292idx0));
    flut292.push_back(lut292idx0);
    auto lut292idx1 = [](long I) -> long {
        /* GATE 67 (LUT2 _2831_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut292.push_back(ctx.genrate_lut(lut292idx1));
    flut292.push_back(lut292idx1);
    auto fvec292 = [flut292](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut292[i](I));
        return ret;
    };

    std::cerr << "\rLUT292   ";
    Ciphertext gin292 = 1 * gout244[1] + 2 * gout174[0];
    std::vector<Ciphertext> gout292 = ctx.eval_lut_amortized(&gin292, lut292);

    std::vector<RotationPoly> lut293;
    std::vector<long (*)(long)> flut293;
    auto lut293idx0 = [](long I) -> long {
        /* GATE 161 (LUT2 _2925_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut293.push_back(ctx.genrate_lut(lut293idx0));
    flut293.push_back(lut293idx0);
    auto lut293idx1 = [](long I) -> long {
        /* GATE 264 (LUT2 _3028_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut293.push_back(ctx.genrate_lut(lut293idx1));
    flut293.push_back(lut293idx1);
    auto fvec293 = [flut293](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut293[i](I));
        return ret;
    };

    std::cerr << "\rLUT293   ";
    Ciphertext gin293 = 1 * gout290[0] + 2 * gout211[0];
    std::vector<Ciphertext> gout293 = ctx.eval_lut_amortized(&gin293, lut293);

    std::vector<RotationPoly> lut294;
    std::vector<long (*)(long)> flut294;
    auto lut294idx0 = [](long I) -> long {
        /* GATE 30 (LUT2 _2794_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut294.push_back(ctx.genrate_lut(lut294idx0));
    flut294.push_back(lut294idx0);
    auto lut294idx1 = [](long I) -> long {
        /* GATE 111 (LUT2 _2875_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut294.push_back(ctx.genrate_lut(lut294idx1));
    flut294.push_back(lut294idx1);
    auto fvec294 = [flut294](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut294[i](I));
        return ret;
    };

    std::cerr << "\rLUT294   ";
    Ciphertext gin294 = 1 * gout274[0] + 2 * gout220[0];
    std::vector<Ciphertext> gout294 = ctx.eval_lut_amortized(&gin294, lut294);

    std::vector<RotationPoly> lut295;
    std::vector<long (*)(long)> flut295;
    auto lut295idx0 = [](long I) -> long {
        /* GATE 790 (LUT2 _3554_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin295 = 1 * gout278[0] + 2 * gout236[0];
    std::vector<Ciphertext> gout295 = ctx.eval_lut_amortized(&gin295, lut295);

    std::vector<RotationPoly> lut296;
    std::vector<long (*)(long)> flut296;
    auto lut296idx0 = [](long I) -> long {
        /* GATE 239 (LUT2 _3003_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut296.push_back(ctx.genrate_lut(lut296idx0));
    flut296.push_back(lut296idx0);
    auto lut296idx1 = [](long I) -> long {
        /* GATE 367 (LUT2 _3131_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut296.push_back(ctx.genrate_lut(lut296idx1));
    flut296.push_back(lut296idx1);
    auto fvec296 = [flut296](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut296[i](I));
        return ret;
    };

    std::cerr << "\rLUT296   ";
    Ciphertext gin296 = 1 * gout265[0] + 2 * gout277[1];
    std::vector<Ciphertext> gout296 = ctx.eval_lut_amortized(&gin296, lut296);

    std::vector<RotationPoly> lut297;
    std::vector<long (*)(long)> flut297;
    auto lut297idx0 = [](long I) -> long {
        /* GATE 322 (LUT2 _3086_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut297.push_back(ctx.genrate_lut(lut297idx0));
    flut297.push_back(lut297idx0);
    auto lut297idx1 = [](long I) -> long {
        /* GATE 216 (LUT2 _2980_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut297.push_back(ctx.genrate_lut(lut297idx1));
    flut297.push_back(lut297idx1);
    auto fvec297 = [flut297](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut297[i](I));
        return ret;
    };

    std::cerr << "\rLUT297   ";
    Ciphertext gin297 = 1 * gout259[0] + 2 * gout285[0];
    std::vector<Ciphertext> gout297 = ctx.eval_lut_amortized(&gin297, lut297);

    std::vector<RotationPoly> lut298;
    std::vector<long (*)(long)> flut298;
    auto lut298idx0 = [](long I) -> long {
        /* GATE 260 (LUT2 _3024_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut298.push_back(ctx.genrate_lut(lut298idx0));
    flut298.push_back(lut298idx0);
    auto lut298idx1 = [](long I) -> long {
        /* GATE 138 (LUT2 _2902_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut298.push_back(ctx.genrate_lut(lut298idx1));
    flut298.push_back(lut298idx1);
    auto fvec298 = [flut298](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut298[i](I));
        return ret;
    };

    std::cerr << "\rLUT298   ";
    Ciphertext gin298 = 1 * gout287[0] + 2 * gout215[1];
    std::vector<Ciphertext> gout298 = ctx.eval_lut_amortized(&gin298, lut298);

    std::vector<RotationPoly> lut299;
    std::vector<long (*)(long)> flut299;
    auto lut299idx0 = [](long I) -> long {
        /* GATE 718 (LUT2 _3482_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut299.push_back(ctx.genrate_lut(lut299idx0));
    flut299.push_back(lut299idx0);
    auto lut299idx1 = [](long I) -> long {
        /* GATE 583 (LUT2 _3347_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut299.push_back(ctx.genrate_lut(lut299idx1));
    flut299.push_back(lut299idx1);
    auto fvec299 = [flut299](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut299[i](I));
        return ret;
    };

    std::cerr << "\rLUT299   ";
    Ciphertext gin299 = 1 * gout271[0] + 2 * gout272[0];
    std::vector<Ciphertext> gout299 = ctx.eval_lut_amortized(&gin299, lut299);

    std::vector<RotationPoly> lut300;
    std::vector<long (*)(long)> flut300;
    auto lut300idx0 = [](long I) -> long {
        /* GATE 805 (LUT2 _3569_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin300 = 1 * gout282[1] + 2 * gout137[0];
    std::vector<Ciphertext> gout300 = ctx.eval_lut_amortized(&gin300, lut300);

    std::vector<RotationPoly> lut301;
    std::vector<long (*)(long)> flut301;
    auto lut301idx0 = [](long I) -> long {
        /* GATE 700 (LUT2 _3464_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut301.push_back(ctx.genrate_lut(lut301idx0));
    flut301.push_back(lut301idx0);
    auto lut301idx1 = [](long I) -> long {
        /* GATE 572 (LUT2 _3336_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut301.push_back(ctx.genrate_lut(lut301idx1));
    flut301.push_back(lut301idx1);
    auto fvec301 = [flut301](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut301[i](I));
        return ret;
    };

    std::cerr << "\rLUT301   ";
    Ciphertext gin301 = 1 * gout208[0] + 2 * gout253[1];
    std::vector<Ciphertext> gout301 = ctx.eval_lut_amortized(&gin301, lut301);

    std::vector<RotationPoly> lut302;
    std::vector<long (*)(long)> flut302;
    auto lut302idx0 = [](long I) -> long {
        /* GATE 820 (LUT2 _3584_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut302.push_back(ctx.genrate_lut(lut302idx0));
    flut302.push_back(lut302idx0);
    auto lut302idx1 = [](long I) -> long {
        /* GATE 887 (LUT2 _3651_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut302.push_back(ctx.genrate_lut(lut302idx1));
    flut302.push_back(lut302idx1);
    auto fvec302 = [flut302](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut302[i](I));
        return ret;
    };

    std::cerr << "\rLUT302   ";
    Ciphertext gin302 = 1 * gout239[0] + 2 * gout266[1];
    std::vector<Ciphertext> gout302 = ctx.eval_lut_amortized(&gin302, lut302);

    std::vector<RotationPoly> lut303;
    std::vector<long (*)(long)> flut303;
    auto lut303idx0 = [](long I) -> long {
        /* GATE 494 (LUT2 _3258_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut303.push_back(ctx.genrate_lut(lut303idx0));
    flut303.push_back(lut303idx0);
    auto lut303idx1 = [](long I) -> long {
        /* GATE 607 (LUT2 _3371_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut303.push_back(ctx.genrate_lut(lut303idx1));
    flut303.push_back(lut303idx1);
    auto fvec303 = [flut303](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut303[i](I));
        return ret;
    };

    std::cerr << "\rLUT303   ";
    Ciphertext gin303 = 1 * gout291[1] + 2 * gout144[0];
    std::vector<Ciphertext> gout303 = ctx.eval_lut_amortized(&gin303, lut303);

    std::vector<RotationPoly> lut304;
    std::vector<long (*)(long)> flut304;
    auto lut304idx0 = [](long I) -> long {
        /* GATE 883 (LUT2 _3647_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut304.push_back(ctx.genrate_lut(lut304idx0));
    flut304.push_back(lut304idx0);
    auto lut304idx1 = [](long I) -> long {
        /* GATE 804 (LUT2 _3568_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut304.push_back(ctx.genrate_lut(lut304idx1));
    flut304.push_back(lut304idx1);
    auto fvec304 = [flut304](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut304[i](I));
        return ret;
    };

    std::cerr << "\rLUT304   ";
    Ciphertext gin304 = 1 * gout300[0] + 2 * gout224[0];
    std::vector<Ciphertext> gout304 = ctx.eval_lut_amortized(&gin304, lut304);

    std::vector<RotationPoly> lut305;
    std::vector<long (*)(long)> flut305;
    auto lut305idx0 = [](long I) -> long {
        /* GATE 491 (LUT2 _3255_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin305 = 1 * gout268[1] + 2 * gout254[1];
    std::vector<Ciphertext> gout305 = ctx.eval_lut_amortized(&gin305, lut305);

    std::vector<RotationPoly> lut306;
    std::vector<long (*)(long)> flut306;
    auto lut306idx0 = [](long I) -> long {
        /* GATE 276 (LUT2 _3040_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut306.push_back(ctx.genrate_lut(lut306idx0));
    flut306.push_back(lut306idx0);
    auto lut306idx1 = [](long I) -> long {
        /* GATE 402 (LUT2 _3166_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut306.push_back(ctx.genrate_lut(lut306idx1));
    flut306.push_back(lut306idx1);
    auto fvec306 = [flut306](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut306[i](I));
        return ret;
    };

    std::cerr << "\rLUT306   ";
    Ciphertext gin306 = 1 * gout261[1] + 2 * gout91[1];
    std::vector<Ciphertext> gout306 = ctx.eval_lut_amortized(&gin306, lut306);

    std::vector<RotationPoly> lut307;
    std::vector<long (*)(long)> flut307;
    auto lut307idx0 = [](long I) -> long {
        /* GATE 557 (LUT2 _3321_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut307.push_back(ctx.genrate_lut(lut307idx0));
    flut307.push_back(lut307idx0);
    auto lut307idx1 = [](long I) -> long {
        /* GATE 444 (LUT2 _3208_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut307.push_back(ctx.genrate_lut(lut307idx1));
    flut307.push_back(lut307idx1);
    auto fvec307 = [flut307](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut307[i](I));
        return ret;
    };

    std::cerr << "\rLUT307   ";
    Ciphertext gin307 = 1 * gout283[0] + 2 * gout275[1];
    std::vector<Ciphertext> gout307 = ctx.eval_lut_amortized(&gin307, lut307);

    std::vector<RotationPoly> lut308;
    std::vector<long (*)(long)> flut308;
    auto lut308idx0 = [](long I) -> long {
        /* GATE 325 (LUT2 _3089_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin308 = 1 * gout285[1] + 2 * gout231[0];
    std::vector<Ciphertext> gout308 = ctx.eval_lut_amortized(&gin308, lut308);

    std::vector<RotationPoly> lut309;
    std::vector<long (*)(long)> flut309;
    auto lut309idx0 = [](long I) -> long {
        /* GATE 842 (LUT2 _3606_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin309 = 1 * gout258[0] + 2 * gout204[0];
    std::vector<Ciphertext> gout309 = ctx.eval_lut_amortized(&gin309, lut309);

    std::vector<RotationPoly> lut310;
    std::vector<long (*)(long)> flut310;
    auto lut310idx0 = [](long I) -> long {
        /* GATE 467 (LUT2 _3231_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut310.push_back(ctx.genrate_lut(lut310idx0));
    flut310.push_back(lut310idx0);
    auto lut310idx1 = [](long I) -> long {
        /* GATE 602 (LUT2 _3366_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut310.push_back(ctx.genrate_lut(lut310idx1));
    flut310.push_back(lut310idx1);
    auto fvec310 = [flut310](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut310[i](I));
        return ret;
    };

    std::cerr << "\rLUT310   ";
    Ciphertext gin310 = 1 * gout289[0] + 2 * gout246[1];
    std::vector<Ciphertext> gout310 = ctx.eval_lut_amortized(&gin310, lut310);

    std::vector<RotationPoly> lut311;
    std::vector<long (*)(long)> flut311;
    auto lut311idx0 = [](long I) -> long {
        /* GATE 180 (LUT2 _2944_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut311.push_back(ctx.genrate_lut(lut311idx0));
    flut311.push_back(lut311idx0);
    auto lut311idx1 = [](long I) -> long {
        /* GATE 53 (LUT2 _2817_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut311.push_back(ctx.genrate_lut(lut311idx1));
    flut311.push_back(lut311idx1);
    auto fvec311 = [flut311](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut311[i](I));
        return ret;
    };

    std::cerr << "\rLUT311   ";
    Ciphertext gin311 = 1 * gout273[0] + 2 * gout162[0];
    std::vector<Ciphertext> gout311 = ctx.eval_lut_amortized(&gin311, lut311);

    std::vector<RotationPoly> lut312;
    std::vector<long (*)(long)> flut312;
    auto lut312idx0 = [](long I) -> long {
        /* GATE 107 (LUT2 _2871_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut312.push_back(ctx.genrate_lut(lut312idx0));
    flut312.push_back(lut312idx0);
    auto lut312idx1 = [](long I) -> long {
        /* GATE 29 (LUT2 _2793_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut312.push_back(ctx.genrate_lut(lut312idx1));
    flut312.push_back(lut312idx1);
    auto fvec312 = [flut312](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut312[i](I));
        return ret;
    };

    std::cerr << "\rLUT312   ";
    Ciphertext gin312 = 1 * gout294[0] + 2 * gout195[0];
    std::vector<Ciphertext> gout312 = ctx.eval_lut_amortized(&gin312, lut312);

    std::vector<RotationPoly> lut313;
    std::vector<long (*)(long)> flut313;
    auto lut313idx0 = [](long I) -> long {
        /* GATE 371 (LUT2 _3135_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin313 = 1 * gout250[0] + 2 * gout206[0];
    std::vector<Ciphertext> gout313 = ctx.eval_lut_amortized(&gin313, lut313);

    std::vector<RotationPoly> lut314;
    std::vector<long (*)(long)> flut314;
    auto lut314idx0 = [](long I) -> long {
        /* GATE 711 (LUT2 _3475_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin314 = 1 * gout272[1] + 2 * gout241[1];
    std::vector<Ciphertext> gout314 = ctx.eval_lut_amortized(&gin314, lut314);

    std::vector<RotationPoly> lut315;
    std::vector<long (*)(long)> flut315;
    auto lut315idx0 = [](long I) -> long {
        /* GATE 699 (LUT2 _3463_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin315 = 1 * gout301[0] + 2 * gout253[0];
    std::vector<Ciphertext> gout315 = ctx.eval_lut_amortized(&gin315, lut315);

    std::vector<RotationPoly> lut316;
    std::vector<long (*)(long)> flut316;
    auto lut316idx0 = [](long I) -> long {
        /* GATE 349 (LUT2 _3113_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin316 = 1 * gout279[0] + 2 * gout212[1];
    std::vector<Ciphertext> gout316 = ctx.eval_lut_amortized(&gin316, lut316);

    std::vector<RotationPoly> lut317;
    std::vector<long (*)(long)> flut317;
    auto lut317idx0 = [](long I) -> long {
        /* GATE 137 (LUT2 _2901_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut317.push_back(ctx.genrate_lut(lut317idx0));
    flut317.push_back(lut317idx0);
    auto lut317idx1 = [](long I) -> long {
        /* GATE 259 (LUT2 _3023_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut317.push_back(ctx.genrate_lut(lut317idx1));
    flut317.push_back(lut317idx1);
    auto fvec317 = [flut317](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut317[i](I));
        return ret;
    };

    std::cerr << "\rLUT317   ";
    Ciphertext gin317 = 1 * gout281[0] + 2 * gout298[1];
    std::vector<Ciphertext> gout317 = ctx.eval_lut_amortized(&gin317, lut317);

    std::vector<RotationPoly> lut318;
    std::vector<long (*)(long)> flut318;
    auto lut318idx0 = [](long I) -> long {
        /* GATE 213 (LUT2 _2977_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut318.push_back(ctx.genrate_lut(lut318idx0));
    flut318.push_back(lut318idx0);
    auto lut318idx1 = [](long I) -> long {
        /* GATE 113 (LUT2 _2877_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut318.push_back(ctx.genrate_lut(lut318idx1));
    flut318.push_back(lut318idx1);
    auto fvec318 = [flut318](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut318[i](I));
        return ret;
    };

    std::cerr << "\rLUT318   ";
    Ciphertext gin318 = 1 * gout267[0] + 2 * gout218[1];
    std::vector<Ciphertext> gout318 = ctx.eval_lut_amortized(&gin318, lut318);

    std::vector<RotationPoly> lut319;
    std::vector<long (*)(long)> flut319;
    auto lut319idx0 = [](long I) -> long {
        /* GATE 366 (LUT2 _3130_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin319 = 1 * gout296[1] + 2 * gout277[0];
    std::vector<Ciphertext> gout319 = ctx.eval_lut_amortized(&gin319, lut319);

    std::vector<RotationPoly> lut320;
    std::vector<long (*)(long)> flut320;
    auto lut320idx0 = [](long I) -> long {
        /* GATE 401 (LUT2 _3165_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin320 = 1 * gout306[1] + 2 * gout261[0];
    std::vector<Ciphertext> gout320 = ctx.eval_lut_amortized(&gin320, lut320);

    std::vector<RotationPoly> lut321;
    std::vector<long (*)(long)> flut321;
    auto lut321idx0 = [](long I) -> long {
        /* GATE 560 (LUT2 _3324_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin321 = 1 * gout275[0] + 2 * gout245[0];
    std::vector<Ciphertext> gout321 = ctx.eval_lut_amortized(&gin321, lut321);

    std::vector<RotationPoly> lut322;
    std::vector<long (*)(long)> flut322;
    auto lut322idx0 = [](long I) -> long {
        /* GATE 886 (LUT2 _3650_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut322.push_back(ctx.genrate_lut(lut322idx0));
    flut322.push_back(lut322idx0);
    auto lut322idx1 = [](long I) -> long {
        /* GATE 819 (LUT2 _3583_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut322.push_back(ctx.genrate_lut(lut322idx1));
    flut322.push_back(lut322idx1);
    auto fvec322 = [flut322](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut322[i](I));
        return ret;
    };

    std::cerr << "\rLUT322   ";
    Ciphertext gin322 = 1 * gout302[0] + 2 * gout139[0];
    std::vector<Ciphertext> gout322 = ctx.eval_lut_amortized(&gin322, lut322);

    std::vector<RotationPoly> lut323;
    std::vector<long (*)(long)> flut323;
    auto lut323idx0 = [](long I) -> long {
        /* GATE 882 (LUT2 _3646_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut323.push_back(ctx.genrate_lut(lut323idx0));
    flut323.push_back(lut323idx0);
    auto lut323idx1 = [](long I) -> long {
        /* GATE 803 (LUT2 _3567_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut323.push_back(ctx.genrate_lut(lut323idx1));
    flut323.push_back(lut323idx1);
    auto fvec323 = [flut323](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut323[i](I));
        return ret;
    };

    std::cerr << "\rLUT323   ";
    Ciphertext gin323 = 1 * gout286[0] + 2 * gout304[1];
    std::vector<Ciphertext> gout323 = ctx.eval_lut_amortized(&gin323, lut323);

    std::vector<RotationPoly> lut324;
    std::vector<long (*)(long)> flut324;
    auto lut324idx0 = [](long I) -> long {
        /* GATE 721 (LUT2 _3485_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin324 = 1 * gout270[0] + 2 * gout219[0];
    std::vector<Ciphertext> gout324 = ctx.eval_lut_amortized(&gin324, lut324);

    std::vector<RotationPoly> lut325;
    std::vector<long (*)(long)> flut325;
    auto lut325idx0 = [](long I) -> long {
        /* GATE 877 (LUT2 _3641_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut325.push_back(ctx.genrate_lut(lut325idx0));
    flut325.push_back(lut325idx0);
    auto lut325idx1 = [](long I) -> long {
        /* GATE 789 (LUT2 _3553_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut325.push_back(ctx.genrate_lut(lut325idx1));
    flut325.push_back(lut325idx1);
    auto fvec325 = [flut325](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut325[i](I));
        return ret;
    };

    std::cerr << "\rLUT325   ";
    Ciphertext gin325 = 1 * gout295[0] + 2 * gout214[0];
    std::vector<Ciphertext> gout325 = ctx.eval_lut_amortized(&gin325, lut325);

    std::vector<RotationPoly> lut326;
    std::vector<long (*)(long)> flut326;
    auto lut326idx0 = [](long I) -> long {
        /* GATE 110 (LUT2 _2874_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin326 = 1 * gout294[1] + 2 * gout274[1];
    std::vector<Ciphertext> gout326 = ctx.eval_lut_amortized(&gin326, lut326);

    std::vector<RotationPoly> lut327;
    std::vector<long (*)(long)> flut327;
    auto lut327idx0 = [](long I) -> long {
        /* GATE 258 (LUT2 _3022_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin327 = 1 * gout317[1] + 2 * gout298[0];
    std::vector<Ciphertext> gout327 = ctx.eval_lut_amortized(&gin327, lut327);

    std::vector<RotationPoly> lut328;
    std::vector<long (*)(long)> flut328;
    auto lut328idx0 = [](long I) -> long {
        /* GATE 442 (LUT2 _3206_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut328.push_back(ctx.genrate_lut(lut328idx0));
    flut328.push_back(lut328idx0);
    auto lut328idx1 = [](long I) -> long {
        /* GATE 324 (LUT2 _3088_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut328.push_back(ctx.genrate_lut(lut328idx1));
    flut328.push_back(lut328idx1);
    auto fvec328 = [flut328](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut328[i](I));
        return ret;
    };

    std::cerr << "\rLUT328   ";
    Ciphertext gin328 = 1 * gout308[0] + 2 * gout225[1];
    std::vector<Ciphertext> gout328 = ctx.eval_lut_amortized(&gin328, lut328);

    std::vector<RotationPoly> lut329;
    std::vector<long (*)(long)> flut329;
    auto lut329idx0 = [](long I) -> long {
        /* GATE 263 (LUT2 _3027_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin329 = 1 * gout293[1] + 2 * gout290[1];
    std::vector<Ciphertext> gout329 = ctx.eval_lut_amortized(&gin329, lut329);

    std::vector<RotationPoly> lut330;
    std::vector<long (*)(long)> flut330;
    auto lut330idx0 = [](long I) -> long {
        /* GATE 321 (LUT2 _3085_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut330.push_back(ctx.genrate_lut(lut330idx0));
    flut330.push_back(lut330idx0);
    auto lut330idx1 = [](long I) -> long {
        /* GATE 215 (LUT2 _2979_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut330.push_back(ctx.genrate_lut(lut330idx1));
    flut330.push_back(lut330idx1);
    auto fvec330 = [flut330](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut330[i](I));
        return ret;
    };

    std::cerr << "\rLUT330   ";
    Ciphertext gin330 = 1 * gout297[1] + 2 * gout279[1];
    std::vector<Ciphertext> gout330 = ctx.eval_lut_amortized(&gin330, lut330);

    std::vector<RotationPoly> lut331;
    std::vector<long (*)(long)> flut331;
    auto lut331idx0 = [](long I) -> long {
        /* GATE 601 (LUT2 _3365_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin331 = 1 * gout310[1] + 2 * gout246[0];
    std::vector<Ciphertext> gout331 = ctx.eval_lut_amortized(&gin331, lut331);

    std::vector<RotationPoly> lut332;
    std::vector<long (*)(long)> flut332;
    auto lut332idx0 = [](long I) -> long {
        /* GATE 559 (LUT2 _3323_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut332.push_back(ctx.genrate_lut(lut332idx0));
    flut332.push_back(lut332idx0);
    auto lut332idx1 = [](long I) -> long {
        /* GATE 672 (LUT2 _3436_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut332.push_back(ctx.genrate_lut(lut332idx1));
    flut332.push_back(lut332idx1);
    auto fvec332 = [flut332](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut332[i](I));
        return ret;
    };

    std::cerr << "\rLUT332   ";
    Ciphertext gin332 = 1 * gout321[0] + 2 * gout134[0];
    std::vector<Ciphertext> gout332 = ctx.eval_lut_amortized(&gin332, lut332);

    std::vector<RotationPoly> lut333;
    std::vector<long (*)(long)> flut333;
    auto lut333idx0 = [](long I) -> long {
        /* GATE 181 (LUT2 _2945_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut333.push_back(ctx.genrate_lut(lut333idx0));
    flut333.push_back(lut333idx0);
    auto lut333idx1 = [](long I) -> long {
        /* GATE 66 (LUT2 _2830_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut333.push_back(ctx.genrate_lut(lut333idx1));
    flut333.push_back(lut333idx1);
    auto fvec333 = [flut333](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut333[i](I));
        return ret;
    };

    std::cerr << "\rLUT333   ";
    Ciphertext gin333 = 1 * gout292[1] + 2 * gout213[1];
    std::vector<Ciphertext> gout333 = ctx.eval_lut_amortized(&gin333, lut333);

    std::vector<RotationPoly> lut334;
    std::vector<long (*)(long)> flut334;
    auto lut334idx0 = [](long I) -> long {
        /* GATE 786 (LUT2 _3550_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut334.push_back(ctx.genrate_lut(lut334idx0));
    flut334.push_back(lut334idx0);
    auto lut334idx1 = [](long I) -> long {
        /* GATE 673 (LUT2 _3437_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut334.push_back(ctx.genrate_lut(lut334idx1));
    flut334.push_back(lut334idx1);
    auto fvec334 = [flut334](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut334[i](I));
        return ret;
    };

    std::cerr << "\rLUT334   ";
    Ciphertext gin334 = 1 * gout280[0] + 2 * gout282[0];
    std::vector<Ciphertext> gout334 = ctx.eval_lut_amortized(&gin334, lut334);

    std::vector<RotationPoly> lut335;
    std::vector<long (*)(long)> flut335;
    auto lut335idx0 = [](long I) -> long {
        /* GATE 556 (LUT2 _3320_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut335.push_back(ctx.genrate_lut(lut335idx0));
    flut335.push_back(lut335idx0);
    auto lut335idx1 = [](long I) -> long {
        /* GATE 443 (LUT2 _3207_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut335.push_back(ctx.genrate_lut(lut335idx1));
    flut335.push_back(lut335idx1);
    auto fvec335 = [flut335](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut335[i](I));
        return ret;
    };

    std::cerr << "\rLUT335   ";
    Ciphertext gin335 = 1 * gout307[1] + 2 * gout207[1];
    std::vector<Ciphertext> gout335 = ctx.eval_lut_amortized(&gin335, lut335);

    std::vector<RotationPoly> lut336;
    std::vector<long (*)(long)> flut336;
    auto lut336idx0 = [](long I) -> long {
        /* GATE 106 (LUT2 _2870_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut336.push_back(ctx.genrate_lut(lut336idx0));
    flut336.push_back(lut336idx0);
    auto lut336idx1 = [](long I) -> long {
        /* GATE 28 (LUT2 _2792_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut336.push_back(ctx.genrate_lut(lut336idx1));
    flut336.push_back(lut336idx1);
    auto fvec336 = [flut336](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut336[i](I));
        return ret;
    };

    std::cerr << "\rLUT336   ";
    Ciphertext gin336 = 1 * gout312[1] + 2 * gout311[1];
    std::vector<Ciphertext> gout336 = ctx.eval_lut_amortized(&gin336, lut336);

    std::vector<RotationPoly> lut337;
    std::vector<long (*)(long)> flut337;
    auto lut337idx0 = [](long I) -> long {
        /* GATE 109 (LUT2 _2873_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut337.push_back(ctx.genrate_lut(lut337idx0));
    flut337.push_back(lut337idx0);
    auto lut337idx1 = [](long I) -> long {
        /* GATE 209 (LUT2 _2973_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut337.push_back(ctx.genrate_lut(lut337idx1));
    flut337.push_back(lut337idx1);
    auto fvec337 = [flut337](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut337[i](I));
        return ret;
    };

    std::cerr << "\rLUT337   ";
    Ciphertext gin337 = 1 * gout326[0] + 2 * gout318[1];
    std::vector<Ciphertext> gout337 = ctx.eval_lut_amortized(&gin337, lut337);

    std::vector<RotationPoly> lut338;
    std::vector<long (*)(long)> flut338;
    auto lut338idx0 = [](long I) -> long {
        /* GATE 606 (LUT2 _3370_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin338 = 1 * gout303[1] + 2 * gout291[0];
    std::vector<Ciphertext> gout338 = ctx.eval_lut_amortized(&gin338, lut338);

    std::vector<RotationPoly> lut339;
    std::vector<long (*)(long)> flut339;
    auto lut339idx0 = [](long I) -> long {
        /* GATE 785 (LUT2 _3549_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin339 = 1 * gout334[0] + 2 * gout280[1];
    std::vector<Ciphertext> gout339 = ctx.eval_lut_amortized(&gin339, lut339);

    std::vector<RotationPoly> lut340;
    std::vector<long (*)(long)> flut340;
    auto lut340idx0 = [](long I) -> long {
        /* GATE 158 (LUT2 _2922_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin340 = 1 * gout292[0] + 2 * gout244[0];
    std::vector<Ciphertext> gout340 = ctx.eval_lut_amortized(&gin340, lut340);

    std::vector<RotationPoly> lut341;
    std::vector<long (*)(long)> flut341;
    auto lut341idx0 = [](long I) -> long {
        /* GATE 582 (LUT2 _3346_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut341.push_back(ctx.genrate_lut(lut341idx0));
    flut341.push_back(lut341idx0);
    auto lut341idx1 = [](long I) -> long {
        /* GATE 717 (LUT2 _3481_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut341.push_back(ctx.genrate_lut(lut341idx1));
    flut341.push_back(lut341idx1);
    auto fvec341 = [flut341](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut341[i](I));
        return ret;
    };

    std::cerr << "\rLUT341   ";
    Ciphertext gin341 = 1 * gout276[0] + 2 * gout299[1];
    std::vector<Ciphertext> gout341 = ctx.eval_lut_amortized(&gin341, lut341);

    std::vector<RotationPoly> lut342;
    std::vector<long (*)(long)> flut342;
    auto lut342idx0 = [](long I) -> long {
        /* GATE 27 (LUT2 _2791_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut342.push_back(ctx.genrate_lut(lut342idx0));
    flut342.push_back(lut342idx0);
    auto lut342idx1 = [](long I) -> long {
        /* GATE 102 (LUT2 _2866_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut342.push_back(ctx.genrate_lut(lut342idx1));
    flut342.push_back(lut342idx1);
    auto fvec342 = [flut342](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut342[i](I));
        return ret;
    };

    std::cerr << "\rLUT342   ";
    Ciphertext gin342 = 1 * gout336[1] + 2 * gout248[0];
    std::vector<Ciphertext> gout342 = ctx.eval_lut_amortized(&gin342, lut342);

    std::vector<RotationPoly> lut343;
    std::vector<long (*)(long)> flut343;
    auto lut343idx0 = [](long I) -> long {
        /* GATE 441 (LUT2 _3205_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut343.push_back(ctx.genrate_lut(lut343idx0));
    flut343.push_back(lut343idx0);
    auto lut343idx1 = [](long I) -> long {
        /* GATE 323 (LUT2 _3087_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut343.push_back(ctx.genrate_lut(lut343idx1));
    flut343.push_back(lut343idx1);
    auto fvec343 = [flut343](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut343[i](I));
        return ret;
    };

    std::cerr << "\rLUT343   ";
    Ciphertext gin343 = 1 * gout328[1] + 2 * gout202[0];
    std::vector<Ciphertext> gout343 = ctx.eval_lut_amortized(&gin343, lut343);

    std::vector<RotationPoly> lut344;
    std::vector<long (*)(long)> flut344;
    auto lut344idx0 = [](long I) -> long {
        /* GATE 555 (LUT2 _3319_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin344 = 1 * gout335[0] + 2 * gout307[0];
    std::vector<Ciphertext> gout344 = ctx.eval_lut_amortized(&gin344, lut344);

    std::vector<RotationPoly> lut345;
    std::vector<long (*)(long)> flut345;
    auto lut345idx0 = [](long I) -> long {
        /* GATE 370 (LUT2 _3134_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut345.push_back(ctx.genrate_lut(lut345idx0));
    flut345.push_back(lut345idx0);
    auto lut345idx1 = [](long I) -> long {
        /* GATE 515 (LUT2 _3279_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut345.push_back(ctx.genrate_lut(lut345idx1));
    flut345.push_back(lut345idx1);
    auto fvec345 = [flut345](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut345[i](I));
        return ret;
    };

    std::cerr << "\rLUT345   ";
    Ciphertext gin345 = 1 * gout313[0] + 2 * gout268[0];
    std::vector<Ciphertext> gout345 = ctx.eval_lut_amortized(&gin345, lut345);

    std::vector<RotationPoly> lut346;
    std::vector<long (*)(long)> flut346;
    auto lut346idx0 = [](long I) -> long {
        /* GATE 630 (LUT2 _3394_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut346.push_back(ctx.genrate_lut(lut346idx0));
    flut346.push_back(lut346idx0);
    auto lut346idx1 = [](long I) -> long {
        /* GATE 490 (LUT2 _3254_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut346.push_back(ctx.genrate_lut(lut346idx1));
    flut346.push_back(lut346idx1);
    auto fvec346 = [flut346](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut346[i](I));
        return ret;
    };

    std::cerr << "\rLUT346   ";
    Ciphertext gin346 = 1 * gout305[0] + 2 * gout303[0];
    std::vector<Ciphertext> gout346 = ctx.eval_lut_amortized(&gin346, lut346);

    std::vector<RotationPoly> lut347;
    std::vector<long (*)(long)> flut347;
    auto lut347idx0 = [](long I) -> long {
        /* GATE 157 (LUT2 _2921_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut347.push_back(ctx.genrate_lut(lut347idx0));
    flut347.push_back(lut347idx0);
    auto lut347idx1 = [](long I) -> long {
        /* GATE 287 (LUT2 _3051_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut347.push_back(ctx.genrate_lut(lut347idx1));
    flut347.push_back(lut347idx1);
    auto fvec347 = [flut347](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut347[i](I));
        return ret;
    };

    std::cerr << "\rLUT347   ";
    Ciphertext gin347 = 1 * gout340[0] + 2 * gout293[0];
    std::vector<Ciphertext> gout347 = ctx.eval_lut_amortized(&gin347, lut347);

    std::vector<RotationPoly> lut348;
    std::vector<long (*)(long)> flut348;
    auto lut348idx0 = [](long I) -> long {
        /* GATE 320 (LUT2 _3084_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin348 = 1 * gout330[0] + 2 * gout297[0];
    std::vector<Ciphertext> gout348 = ctx.eval_lut_amortized(&gin348, lut348);

    std::vector<RotationPoly> lut349;
    std::vector<long (*)(long)> flut349;
    auto lut349idx0 = [](long I) -> long {
        /* GATE 65 (LUT2 _2829_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut349.push_back(ctx.genrate_lut(lut349idx0));
    flut349.push_back(lut349idx0);
    auto lut349idx1 = [](long I) -> long {
        /* GATE 184 (LUT2 _2948_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut349.push_back(ctx.genrate_lut(lut349idx1));
    flut349.push_back(lut349idx1);
    auto fvec349 = [flut349](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut349[i](I));
        return ret;
    };

    std::cerr << "\rLUT349   ";
    Ciphertext gin349 = 1 * gout333[1] + 2 * gout164[1];
    std::vector<Ciphertext> gout349 = ctx.eval_lut_amortized(&gin349, lut349);

    std::vector<RotationPoly> lut350;
    std::vector<long (*)(long)> flut350;
    auto lut350idx0 = [](long I) -> long {
        /* GATE 101 (LUT2 _2865_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut350.push_back(ctx.genrate_lut(lut350idx0));
    flut350.push_back(lut350idx0);
    auto lut350idx1 = [](long I) -> long {
        /* GATE 26 (LUT2 _2790_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut350.push_back(ctx.genrate_lut(lut350idx1));
    flut350.push_back(lut350idx1);
    auto fvec350 = [flut350](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut350[i](I));
        return ret;
    };

    std::cerr << "\rLUT350   ";
    Ciphertext gin350 = 1 * gout342[0] + 2 * gout349[0];
    std::vector<Ciphertext> gout350 = ctx.eval_lut_amortized(&gin350, lut350);

    std::vector<RotationPoly> lut351;
    std::vector<long (*)(long)> flut351;
    auto lut351idx0 = [](long I) -> long {
        /* GATE 698 (LUT2 _3462_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut351.push_back(ctx.genrate_lut(lut351idx0));
    flut351.push_back(lut351idx0);
    auto lut351idx1 = [](long I) -> long {
        /* GATE 818 (LUT2 _3582_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut351.push_back(ctx.genrate_lut(lut351idx1));
    flut351.push_back(lut351idx1);
    auto fvec351 = [flut351](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut351[i](I));
        return ret;
    };

    std::cerr << "\rLUT351   ";
    Ciphertext gin351 = 1 * gout315[0] + 2 * gout264[0];
    std::vector<Ciphertext> gout351 = ctx.eval_lut_amortized(&gin351, lut351);

    std::vector<RotationPoly> lut352;
    std::vector<long (*)(long)> flut352;
    auto lut352idx0 = [](long I) -> long {
        /* GATE 348 (LUT2 _3112_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut352.push_back(ctx.genrate_lut(lut352idx0));
    flut352.push_back(lut352idx0);
    auto lut352idx1 = [](long I) -> long {
        /* GATE 488 (LUT2 _3252_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut352.push_back(ctx.genrate_lut(lut352idx1));
    flut352.push_back(lut352idx1);
    auto fvec352 = [flut352](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut352[i](I));
        return ret;
    };

    std::cerr << "\rLUT352   ";
    Ciphertext gin352 = 1 * gout316[0] + 2 * gout256[1];
    std::vector<Ciphertext> gout352 = ctx.eval_lut_amortized(&gin352, lut352);

    std::vector<RotationPoly> lut353;
    std::vector<long (*)(long)> flut353;
    auto lut353idx0 = [](long I) -> long {
        /* GATE 885 (LUT2 _3649_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut353.push_back(ctx.genrate_lut(lut353idx0));
    flut353.push_back(lut353idx0);
    auto fvec353 = [flut353](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut353[i](I));
        return ret;
    };

    std::cerr << "\rLUT353   ";
    Ciphertext gin353 = 1 * gout322[0] + 2 * gout302[1];
    std::vector<Ciphertext> gout353 = ctx.eval_lut_amortized(&gin353, lut353);

    std::vector<RotationPoly> lut354;
    std::vector<long (*)(long)> flut354;
    auto lut354idx0 = [](long I) -> long {
        /* GATE 817 (LUT2 _3581_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut354.push_back(ctx.genrate_lut(lut354idx0));
    flut354.push_back(lut354idx0);
    auto lut354idx1 = [](long I) -> long {
        /* GATE 697 (LUT2 _3461_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut354.push_back(ctx.genrate_lut(lut354idx1));
    flut354.push_back(lut354idx1);
    auto fvec354 = [flut354](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut354[i](I));
        return ret;
    };

    std::cerr << "\rLUT354   ";
    Ciphertext gin354 = 1 * gout314[0] + 2 * gout351[0];
    std::vector<Ciphertext> gout354 = ctx.eval_lut_amortized(&gin354, lut354);

    std::vector<RotationPoly> lut355;
    std::vector<long (*)(long)> flut355;
    auto lut355idx0 = [](long I) -> long {
        /* GATE 745 (LUT2 _3509_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut355.push_back(ctx.genrate_lut(lut355idx0));
    flut355.push_back(lut355idx0);
    auto lut355idx1 = [](long I) -> long {
        /* GATE 605 (LUT2 _3369_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut355.push_back(ctx.genrate_lut(lut355idx1));
    flut355.push_back(lut355idx1);
    auto fvec355 = [flut355](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut355[i](I));
        return ret;
    };

    std::cerr << "\rLUT355   ";
    Ciphertext gin355 = 1 * gout338[0] + 2 * gout270[1];
    std::vector<Ciphertext> gout355 = ctx.eval_lut_amortized(&gin355, lut355);

    std::vector<RotationPoly> lut356;
    std::vector<long (*)(long)> flut356;
    auto lut356idx0 = [](long I) -> long {
        /* GATE 156 (LUT2 _2920_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut356.push_back(ctx.genrate_lut(lut356idx0));
    flut356.push_back(lut356idx0);
    auto lut356idx1 = [](long I) -> long {
        /* GATE 286 (LUT2 _3050_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut356.push_back(ctx.genrate_lut(lut356idx1));
    flut356.push_back(lut356idx1);
    auto fvec356 = [flut356](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut356[i](I));
        return ret;
    };

    std::cerr << "\rLUT356   ";
    Ciphertext gin356 = 1 * gout347[0] + 2 * gout263[1];
    std::vector<Ciphertext> gout356 = ctx.eval_lut_amortized(&gin356, lut356);

    std::vector<RotationPoly> lut357;
    std::vector<long (*)(long)> flut357;
    auto lut357idx0 = [](long I) -> long {
        /* GATE 212 (LUT2 _2976_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut357.push_back(ctx.genrate_lut(lut357idx0));
    flut357.push_back(lut357idx0);
    auto fvec357 = [flut357](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut357[i](I));
        return ret;
    };

    std::cerr << "\rLUT357   ";
    Ciphertext gin357 = 1 * gout318[0] + 2 * gout267[1];
    std::vector<Ciphertext> gout357 = ctx.eval_lut_amortized(&gin357, lut357);

    std::vector<RotationPoly> lut358;
    std::vector<long (*)(long)> flut358;
    auto lut358idx0 = [](long I) -> long {
        /* GATE 100 (LUT2 _2864_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut358.push_back(ctx.genrate_lut(lut358idx0));
    flut358.push_back(lut358idx0);
    auto fvec358 = [flut358](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut358[i](I));
        return ret;
    };

    std::cerr << "\rLUT358   ";
    Ciphertext gin358 = 1 * gout350[0] + 2 * gout342[1];
    std::vector<Ciphertext> gout358 = ctx.eval_lut_amortized(&gin358, lut358);

    std::vector<RotationPoly> lut359;
    std::vector<long (*)(long)> flut359;
    auto lut359idx0 = [](long I) -> long {
        /* GATE 716 (LUT2 _3480_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut359.push_back(ctx.genrate_lut(lut359idx0));
    flut359.push_back(lut359idx0);
    auto fvec359 = [flut359](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut359[i](I));
        return ret;
    };

    std::cerr << "\rLUT359   ";
    Ciphertext gin359 = 1 * gout341[1] + 2 * gout299[0];
    std::vector<Ciphertext> gout359 = ctx.eval_lut_amortized(&gin359, lut359);

    std::vector<RotationPoly> lut360;
    std::vector<long (*)(long)> flut360;
    auto lut360idx0 = [](long I) -> long {
        /* GATE 881 (LUT2 _3645_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut360.push_back(ctx.genrate_lut(lut360idx0));
    flut360.push_back(lut360idx0);
    auto fvec360 = [flut360](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut360[i](I));
        return ret;
    };

    std::cerr << "\rLUT360   ";
    Ciphertext gin360 = 1 * gout323[0] + 2 * gout304[0];
    std::vector<Ciphertext> gout360 = ctx.eval_lut_amortized(&gin360, lut360);

    std::vector<RotationPoly> lut361;
    std::vector<long (*)(long)> flut361;
    auto lut361idx0 = [](long I) -> long {
        /* GATE 875 (LUT2 _3639_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut361.push_back(ctx.genrate_lut(lut361idx0));
    flut361.push_back(lut361idx0);
    auto lut361idx1 = [](long I) -> long {
        /* GATE 788 (LUT2 _3552_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut361.push_back(ctx.genrate_lut(lut361idx1));
    flut361.push_back(lut361idx1);
    auto fvec361 = [flut361](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut361[i](I));
        return ret;
    };

    std::cerr << "\rLUT361   ";
    Ciphertext gin361 = 1 * gout325[1] + 2 * gout243[1];
    std::vector<Ciphertext> gout361 = ctx.eval_lut_amortized(&gin361, lut361);

    std::vector<RotationPoly> lut362;
    std::vector<long (*)(long)> flut362;
    auto lut362idx0 = [](long I) -> long {
        /* GATE 912 (LUT2 _3676_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut362.push_back(ctx.genrate_lut(lut362idx0));
    flut362.push_back(lut362idx0);
    auto lut362idx1 = [](long I) -> long {
        /* GATE 876 (LUT2 _3640_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut362.push_back(ctx.genrate_lut(lut362idx1));
    flut362.push_back(lut362idx1);
    auto fvec362 = [flut362](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut362[i](I));
        return ret;
    };

    std::cerr << "\rLUT362   ";
    Ciphertext gin362 = 1 * gout325[0] + 2 * gout243[0];
    std::vector<Ciphertext> gout362 = ctx.eval_lut_amortized(&gin362, lut362);

    std::vector<RotationPoly> lut363;
    std::vector<long (*)(long)> flut363;
    auto lut363idx0 = [](long I) -> long {
        /* GATE 720 (LUT2 _3484_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut363.push_back(ctx.genrate_lut(lut363idx0));
    flut363.push_back(lut363idx0);
    auto lut363idx1 = [](long I) -> long {
        /* GATE 836 (LUT2 _3600_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut363.push_back(ctx.genrate_lut(lut363idx1));
    flut363.push_back(lut363idx1);
    auto fvec363 = [flut363](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut363[i](I));
        return ret;
    };

    std::cerr << "\rLUT363   ";
    Ciphertext gin363 = 1 * gout324[0] + 2 * gout193[0];
    std::vector<Ciphertext> gout363 = ctx.eval_lut_amortized(&gin363, lut363);

    std::vector<RotationPoly> lut364;
    std::vector<long (*)(long)> flut364;
    auto lut364idx0 = [](long I) -> long {
        /* GATE 105 (LUT2 _2869_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut364.push_back(ctx.genrate_lut(lut364idx0));
    flut364.push_back(lut364idx0);
    auto fvec364 = [flut364](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut364[i](I));
        return ret;
    };

    std::cerr << "\rLUT364   ";
    Ciphertext gin364 = 1 * gout336[0] + 2 * gout312[0];
    std::vector<Ciphertext> gout364 = ctx.eval_lut_amortized(&gin364, lut364);

    std::vector<RotationPoly> lut365;
    std::vector<long (*)(long)> flut365;
    auto lut365idx0 = [](long I) -> long {
        /* GATE 784 (LUT2 _3548_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut365.push_back(ctx.genrate_lut(lut365idx0));
    flut365.push_back(lut365idx0);
    auto lut365idx1 = [](long I) -> long {
        /* GATE 873 (LUT2 _3637_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut365.push_back(ctx.genrate_lut(lut365idx1));
    flut365.push_back(lut365idx1);
    auto fvec365 = [flut365](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut365[i](I));
        return ret;
    };

    std::cerr << "\rLUT365   ";
    Ciphertext gin365 = 1 * gout339[0] + 2 * gout361[1];
    std::vector<Ciphertext> gout365 = ctx.eval_lut_amortized(&gin365, lut365);

    std::vector<RotationPoly> lut366;
    std::vector<long (*)(long)> flut366;
    auto lut366idx0 = [](long I) -> long {
        /* GATE 262 (LUT2 _3026_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut366.push_back(ctx.genrate_lut(lut366idx0));
    flut366.push_back(lut366idx0);
    auto lut366idx1 = [](long I) -> long {
        /* GATE 395 (LUT2 _3159_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut366.push_back(ctx.genrate_lut(lut366idx1));
    flut366.push_back(lut366idx1);
    auto fvec366 = [flut366](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut366[i](I));
        return ret;
    };

    std::cerr << "\rLUT366   ";
    Ciphertext gin366 = 1 * gout329[0] + 2 * gout250[1];
    std::vector<Ciphertext> gout366 = ctx.eval_lut_amortized(&gin366, lut366);

    std::vector<RotationPoly> lut367;
    std::vector<long (*)(long)> flut367;
    auto lut367idx0 = [](long I) -> long {
        /* GATE 319 (LUT2 _3083_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut367.push_back(ctx.genrate_lut(lut367idx0));
    flut367.push_back(lut367idx0);
    auto lut367idx1 = [](long I) -> long {
        /* GATE 437 (LUT2 _3201_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut367.push_back(ctx.genrate_lut(lut367idx1));
    flut367.push_back(lut367idx1);
    auto fvec367 = [flut367](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut367[i](I));
        return ret;
    };

    std::cerr << "\rLUT367   ";
    Ciphertext gin367 = 1 * gout348[0] + 2 * gout343[1];
    std::vector<Ciphertext> gout367 = ctx.eval_lut_amortized(&gin367, lut367);

    std::vector<RotationPoly> lut368;
    std::vector<long (*)(long)> flut368;
    auto lut368idx0 = [](long I) -> long {
        /* GATE 208 (LUT2 _2972_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut368.push_back(ctx.genrate_lut(lut368idx0));
    flut368.push_back(lut368idx0);
    auto lut368idx1 = [](long I) -> long {
        /* GATE 108 (LUT2 _2872_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut368.push_back(ctx.genrate_lut(lut368idx1));
    flut368.push_back(lut368idx1);
    auto fvec368 = [flut368](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut368[i](I));
        return ret;
    };

    std::cerr << "\rLUT368   ";
    Ciphertext gin368 = 1 * gout337[0] + 2 * gout317[0];
    std::vector<Ciphertext> gout368 = ctx.eval_lut_amortized(&gin368, lut368);

    std::vector<RotationPoly> lut369;
    std::vector<long (*)(long)> flut369;
    auto lut369idx0 = [](long I) -> long {
        /* GATE 204 (LUT2 _2968_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut369.push_back(ctx.genrate_lut(lut369idx0));
    flut369.push_back(lut369idx0);
    auto lut369idx1 = [](long I) -> long {
        /* GATE 104 (LUT2 _2868_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut369.push_back(ctx.genrate_lut(lut369idx1));
    flut369.push_back(lut369idx1);
    auto fvec369 = [flut369](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut369[i](I));
        return ret;
    };

    std::cerr << "\rLUT369   ";
    Ciphertext gin369 = 1 * gout364[0] + 2 * gout368[1];
    std::vector<Ciphertext> gout369 = ctx.eval_lut_amortized(&gin369, lut369);

    std::vector<RotationPoly> lut370;
    std::vector<long (*)(long)> flut370;
    auto lut370idx0 = [](long I) -> long {
        /* GATE 183 (LUT2 _2947_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut370.push_back(ctx.genrate_lut(lut370idx0));
    flut370.push_back(lut370idx0);
    auto lut370idx1 = [](long I) -> long {
        /* GATE 301 (LUT2 _3065_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut370.push_back(ctx.genrate_lut(lut370idx1));
    flut370.push_back(lut370idx1);
    auto fvec370 = [flut370](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut370[i](I));
        return ret;
    };

    std::cerr << "\rLUT370   ";
    Ciphertext gin370 = 1 * gout242[0] + 2 * gout349[1];
    std::vector<Ciphertext> gout370 = ctx.eval_lut_amortized(&gin370, lut370);

    std::vector<RotationPoly> lut371;
    std::vector<long (*)(long)> flut371;
    auto lut371idx0 = [](long I) -> long {
        /* GATE 514 (LUT2 _3278_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut371.push_back(ctx.genrate_lut(lut371idx0));
    flut371.push_back(lut371idx0);
    auto lut371idx1 = [](long I) -> long {
        /* GATE 369 (LUT2 _3133_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut371.push_back(ctx.genrate_lut(lut371idx1));
    flut371.push_back(lut371idx1);
    auto fvec371 = [flut371](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut371[i](I));
        return ret;
    };

    std::cerr << "\rLUT371   ";
    Ciphertext gin371 = 1 * gout345[0] + 2 * gout222[1];
    std::vector<Ciphertext> gout371 = ctx.eval_lut_amortized(&gin371, lut371);

    std::vector<RotationPoly> lut372;
    std::vector<long (*)(long)> flut372;
    auto lut372idx0 = [](long I) -> long {
        /* GATE 440 (LUT2 _3204_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut372.push_back(ctx.genrate_lut(lut372idx0));
    flut372.push_back(lut372idx0);
    auto fvec372 = [flut372](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut372[i](I));
        return ret;
    };

    std::cerr << "\rLUT372   ";
    Ciphertext gin372 = 1 * gout343[0] + 2 * gout328[0];
    std::vector<Ciphertext> gout372 = ctx.eval_lut_amortized(&gin372, lut372);

    std::vector<RotationPoly> lut373;
    std::vector<long (*)(long)> flut373;
    auto lut373idx0 = [](long I) -> long {
        /* GATE 671 (LUT2 _3435_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut373.push_back(ctx.genrate_lut(lut373idx0));
    flut373.push_back(lut373idx0);
    auto lut373idx1 = [](long I) -> long {
        /* GATE 558 (LUT2 _3322_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut373.push_back(ctx.genrate_lut(lut373idx1));
    flut373.push_back(lut373idx1);
    auto fvec373 = [flut373](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut373[i](I));
        return ret;
    };

    std::cerr << "\rLUT373   ";
    Ciphertext gin373 = 1 * gout332[0] + 2 * gout301[1];
    std::vector<Ciphertext> gout373 = ctx.eval_lut_amortized(&gin373, lut373);

    std::vector<RotationPoly> lut374;
    std::vector<long (*)(long)> flut374;
    auto lut374idx0 = [](long I) -> long {
        /* GATE 667 (LUT2 _3431_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut374.push_back(ctx.genrate_lut(lut374idx0));
    flut374.push_back(lut374idx0);
    auto lut374idx1 = [](long I) -> long {
        /* GATE 554 (LUT2 _3318_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut374.push_back(ctx.genrate_lut(lut374idx1));
    flut374.push_back(lut374idx1);
    auto fvec374 = [flut374](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut374[i](I));
        return ret;
    };

    std::cerr << "\rLUT374   ";
    Ciphertext gin374 = 1 * gout344[0] + 2 * gout373[1];
    std::vector<Ciphertext> gout374 = ctx.eval_lut_amortized(&gin374, lut374);

    std::vector<RotationPoly> lut375;
    std::vector<long (*)(long)> flut375;
    auto lut375idx0 = [](long I) -> long {
        /* GATE 211 (LUT2 _2975_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut375.push_back(ctx.genrate_lut(lut375idx0));
    flut375.push_back(lut375idx0);
    auto lut375idx1 = [](long I) -> long {
        /* GATE 317 (LUT2 _3081_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut375.push_back(ctx.genrate_lut(lut375idx1));
    flut375.push_back(lut375idx1);
    auto fvec375 = [flut375](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut375[i](I));
        return ret;
    };

    std::cerr << "\rLUT375   ";
    Ciphertext gin375 = 1 * gout357[0] + 2 * gout330[1];
    std::vector<Ciphertext> gout375 = ctx.eval_lut_amortized(&gin375, lut375);

    std::vector<RotationPoly> lut376;
    std::vector<long (*)(long)> flut376;
    auto lut376idx0 = [](long I) -> long {
        /* GATE 285 (LUT2 _3049_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut376.push_back(ctx.genrate_lut(lut376idx0));
    flut376.push_back(lut376idx0);
    auto fvec376 = [flut376](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut376[i](I));
        return ret;
    };

    std::cerr << "\rLUT376   ";
    Ciphertext gin376 = 1 * gout356[1] + 2 * gout347[1];
    std::vector<Ciphertext> gout376 = ctx.eval_lut_amortized(&gin376, lut376);

    std::vector<RotationPoly> lut377;
    std::vector<long (*)(long)> flut377;
    auto lut377idx0 = [](long I) -> long {
        /* GATE 835 (LUT2 _3599_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut377.push_back(ctx.genrate_lut(lut377idx0));
    flut377.push_back(lut377idx0);
    auto lut377idx1 = [](long I) -> long {
        /* GATE 719 (LUT2 _3483_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut377.push_back(ctx.genrate_lut(lut377idx1));
    flut377.push_back(lut377idx1);
    auto fvec377 = [flut377](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut377[i](I));
        return ret;
    };

    std::cerr << "\rLUT377   ";
    Ciphertext gin377 = 1 * gout363[0] + 2 * gout258[1];
    std::vector<Ciphertext> gout377 = ctx.eval_lut_amortized(&gin377, lut377);

    std::vector<RotationPoly> lut378;
    std::vector<long (*)(long)> flut378;
    auto lut378idx0 = [](long I) -> long {
        /* GATE 97 (LUT2 _2861_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut378.push_back(ctx.genrate_lut(lut378idx0));
    flut378.push_back(lut378idx0);
    auto lut378idx1 = [](long I) -> long {
        /* GATE 25 (LUT2 _2789_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut378.push_back(ctx.genrate_lut(lut378idx1));
    flut378.push_back(lut378idx1);
    auto fvec378 = [flut378](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut378[i](I));
        return ret;
    };

    std::cerr << "\rLUT378   ";
    Ciphertext gin378 = 1 * gout350[1] + 2 * gout284[0];
    std::vector<Ciphertext> gout378 = ctx.eval_lut_amortized(&gin378, lut378);

    std::vector<RotationPoly> lut379;
    std::vector<long (*)(long)> flut379;
    auto lut379idx0 = [](long I) -> long {
        /* GATE 489 (LUT2 _3253_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut379.push_back(ctx.genrate_lut(lut379idx0));
    flut379.push_back(lut379idx0);
    auto lut379idx1 = [](long I) -> long {
        /* GATE 629 (LUT2 _3393_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut379.push_back(ctx.genrate_lut(lut379idx1));
    flut379.push_back(lut379idx1);
    auto fvec379 = [flut379](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut379[i](I));
        return ret;
    };

    std::cerr << "\rLUT379   ";
    Ciphertext gin379 = 1 * gout346[1] + 2 * gout217[1];
    std::vector<Ciphertext> gout379 = ctx.eval_lut_amortized(&gin379, lut379);

    std::vector<RotationPoly> lut380;
    std::vector<long (*)(long)> flut380;
    auto lut380idx0 = [](long I) -> long {
        /* GATE 841 (LUT2 _3605_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut380.push_back(ctx.genrate_lut(lut380idx0));
    flut380.push_back(lut380idx0);
    auto lut380idx1 = [](long I) -> long {
        /* GATE 715 (LUT2 _3479_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut380.push_back(ctx.genrate_lut(lut380idx1));
    flut380.push_back(lut380idx1);
    auto fvec380 = [flut380](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut380[i](I));
        return ret;
    };

    std::cerr << "\rLUT380   ";
    Ciphertext gin380 = 1 * gout359[0] + 2 * gout377[1];
    std::vector<Ciphertext> gout380 = ctx.eval_lut_amortized(&gin380, lut380);

    std::vector<RotationPoly> lut381;
    std::vector<long (*)(long)> flut381;
    auto lut381idx0 = [](long I) -> long {
        /* GATE 487 (LUT2 _3251_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut381.push_back(ctx.genrate_lut(lut381idx0));
    flut381.push_back(lut381idx0);
    auto lut381idx1 = [](long I) -> long {
        /* GATE 347 (LUT2 _3111_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut381.push_back(ctx.genrate_lut(lut381idx1));
    flut381.push_back(lut381idx1);
    auto fvec381 = [flut381](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut381[i](I));
        return ret;
    };

    std::cerr << "\rLUT381   ";
    Ciphertext gin381 = 1 * gout252[0] + 2 * gout352[0];
    std::vector<Ciphertext> gout381 = ctx.eval_lut_amortized(&gin381, lut381);

    std::vector<RotationPoly> lut382;
    std::vector<long (*)(long)> flut382;
    auto lut382idx0 = [](long I) -> long {
        /* GATE 155 (LUT2 _2919_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut382.push_back(ctx.genrate_lut(lut382idx0));
    flut382.push_back(lut382idx0);
    auto lut382idx1 = [](long I) -> long {
        /* GATE 292 (LUT2 _3056_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut382.push_back(ctx.genrate_lut(lut382idx1));
    flut382.push_back(lut382idx1);
    auto fvec382 = [flut382](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut382[i](I));
        return ret;
    };

    std::cerr << "\rLUT382   ";
    Ciphertext gin382 = 1 * gout356[0] + 2 * gout311[0];
    std::vector<Ciphertext> gout382 = ctx.eval_lut_amortized(&gin382, lut382);

    std::vector<RotationPoly> lut383;
    std::vector<long (*)(long)> flut383;
    auto lut383idx0 = [](long I) -> long {
        /* GATE 816 (LUT2 _3580_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut383.push_back(ctx.genrate_lut(lut383idx0));
    flut383.push_back(lut383idx0);
    auto fvec383 = [flut383](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut383[i](I));
        return ret;
    };

    std::cerr << "\rLUT383   ";
    Ciphertext gin383 = 1 * gout354[0] + 2 * gout351[1];
    std::vector<Ciphertext> gout383 = ctx.eval_lut_amortized(&gin383, lut383);

    std::vector<RotationPoly> lut384;
    std::vector<long (*)(long)> flut384;
    auto lut384idx0 = [](long I) -> long {
        /* GATE 486 (LUT2 _3250_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut384.push_back(ctx.genrate_lut(lut384idx0));
    flut384.push_back(lut384idx0);
    auto fvec384 = [flut384](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut384[i](I));
        return ret;
    };

    std::cerr << "\rLUT384   ";
    Ciphertext gin384 = 1 * gout381[0] + 2 * gout352[1];
    std::vector<Ciphertext> gout384 = ctx.eval_lut_amortized(&gin384, lut384);

    std::vector<RotationPoly> lut385;
    std::vector<long (*)(long)> flut385;
    auto lut385idx0 = [](long I) -> long {
        /* GATE 628 (LUT2 _3392_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut385.push_back(ctx.genrate_lut(lut385idx0));
    flut385.push_back(lut385idx0);
    auto fvec385 = [flut385](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut385[i](I));
        return ret;
    };

    std::cerr << "\rLUT385   ";
    Ciphertext gin385 = 1 * gout379[1] + 2 * gout346[0];
    std::vector<Ciphertext> gout385 = ctx.eval_lut_amortized(&gin385, lut385);

    std::vector<RotationPoly> lut386;
    std::vector<long (*)(long)> flut386;
    auto lut386idx0 = [](long I) -> long {
        /* GATE 207 (LUT2 _2971_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut386.push_back(ctx.genrate_lut(lut386idx0));
    flut386.push_back(lut386idx0);
    auto fvec386 = [flut386](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut386[i](I));
        return ret;
    };

    std::cerr << "\rLUT386   ";
    Ciphertext gin386 = 1 * gout368[0] + 2 * gout337[1];
    std::vector<Ciphertext> gout386 = ctx.eval_lut_amortized(&gin386, lut386);

    std::vector<RotationPoly> lut387;
    std::vector<long (*)(long)> flut387;
    auto lut387idx0 = [](long I) -> long {
        /* GATE 670 (LUT2 _3434_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut387.push_back(ctx.genrate_lut(lut387idx0));
    flut387.push_back(lut387idx0);
    auto fvec387 = [flut387](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut387[i](I));
        return ret;
    };

    std::cerr << "\rLUT387   ";
    Ciphertext gin387 = 1 * gout373[0] + 2 * gout332[1];
    std::vector<Ciphertext> gout387 = ctx.eval_lut_amortized(&gin387, lut387);

    std::vector<RotationPoly> lut388;
    std::vector<long (*)(long)> flut388;
    auto lut388idx0 = [](long I) -> long {
        /* GATE 436 (LUT2 _3200_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut388.push_back(ctx.genrate_lut(lut388idx0));
    flut388.push_back(lut388idx0);
    auto lut388idx1 = [](long I) -> long {
        /* GATE 318 (LUT2 _3082_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut388.push_back(ctx.genrate_lut(lut388idx1));
    flut388.push_back(lut388idx1);
    auto fvec388 = [flut388](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut388[i](I));
        return ret;
    };

    std::cerr << "\rLUT388   ";
    Ciphertext gin388 = 1 * gout367[0] + 2 * gout381[1];
    std::vector<Ciphertext> gout388 = ctx.eval_lut_amortized(&gin388, lut388);

    std::vector<RotationPoly> lut389;
    std::vector<long (*)(long)> flut389;
    auto lut389idx0 = [](long I) -> long {
        /* GATE 783 (LUT2 _3547_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut389.push_back(ctx.genrate_lut(lut389idx0));
    flut389.push_back(lut389idx0);
    auto lut389idx1 = [](long I) -> long {
        /* GATE 872 (LUT2 _3636_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut389.push_back(ctx.genrate_lut(lut389idx1));
    flut389.push_back(lut389idx1);
    auto fvec389 = [flut389](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut389[i](I));
        return ret;
    };

    std::cerr << "\rLUT389   ";
    Ciphertext gin389 = 1 * gout365[0] + 2 * gout323[1];
    std::vector<Ciphertext> gout389 = ctx.eval_lut_amortized(&gin389, lut389);

    std::vector<RotationPoly> lut390;
    std::vector<long (*)(long)> flut390;
    auto lut390idx0 = [](long I) -> long {
        /* GATE 880 (LUT2 _3644_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut390.push_back(ctx.genrate_lut(lut390idx0));
    flut390.push_back(lut390idx0);
    auto lut390idx1 = [](long I) -> long {
        /* GATE 915 (LUT2 _3679_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut390.push_back(ctx.genrate_lut(lut390idx1));
    flut390.push_back(lut390idx1);
    auto fvec390 = [flut390](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut390[i](I));
        return ret;
    };

    std::cerr << "\rLUT390   ";
    Ciphertext gin390 = 1 * gout360[0] + 2 * gout266[0];
    std::vector<Ciphertext> gout390 = ctx.eval_lut_amortized(&gin390, lut390);

    std::vector<RotationPoly> lut391;
    std::vector<long (*)(long)> flut391;
    auto lut391idx0 = [](long I) -> long {
        /* GATE 291 (LUT2 _3055_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut391.push_back(ctx.genrate_lut(lut391idx0));
    flut391.push_back(lut391idx0);
    auto lut391idx1 = [](long I) -> long {
        /* GATE 154 (LUT2 _2918_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut391.push_back(ctx.genrate_lut(lut391idx1));
    flut391.push_back(lut391idx1);
    auto fvec391 = [flut391](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut391[i](I));
        return ret;
    };

    std::cerr << "\rLUT391   ";
    Ciphertext gin391 = 1 * gout382[0] + 2 * gout333[0];
    std::vector<Ciphertext> gout391 = ctx.eval_lut_amortized(&gin391, lut391);

    std::vector<RotationPoly> lut392;
    std::vector<long (*)(long)> flut392;
    auto lut392idx0 = [](long I) -> long {
        /* GATE 871 (LUT2 _3635_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut392.push_back(ctx.genrate_lut(lut392idx0));
    flut392.push_back(lut392idx0);
    auto fvec392 = [flut392](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut392[i](I));
        return ret;
    };

    std::cerr << "\rLUT392   ";
    Ciphertext gin392 = 1 * gout389[1] + 2 * gout365[1];
    std::vector<Ciphertext> gout392 = ctx.eval_lut_amortized(&gin392, lut392);

    std::vector<RotationPoly> lut393;
    std::vector<long (*)(long)> flut393;
    auto lut393idx0 = [](long I) -> long {
        /* GATE 834 (LUT2 _3598_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut393.push_back(ctx.genrate_lut(lut393idx0));
    flut393.push_back(lut393idx0);
    auto fvec393 = [flut393](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut393[i](I));
        return ret;
    };

    std::cerr << "\rLUT393   ";
    Ciphertext gin393 = 1 * gout377[0] + 2 * gout363[1];
    std::vector<Ciphertext> gout393 = ctx.eval_lut_amortized(&gin393, lut393);

    std::vector<RotationPoly> lut394;
    std::vector<long (*)(long)> flut394;
    auto lut394idx0 = [](long I) -> long {
        /* GATE 604 (LUT2 _3368_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut394.push_back(ctx.genrate_lut(lut394idx0));
    flut394.push_back(lut394idx0);
    auto lut394idx1 = [](long I) -> long {
        /* GATE 744 (LUT2 _3508_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut394.push_back(ctx.genrate_lut(lut394idx1));
    flut394.push_back(lut394idx1);
    auto fvec394 = [flut394](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut394[i](I));
        return ret;
    };

    std::cerr << "\rLUT394   ";
    Ciphertext gin394 = 1 * gout355[1] + 2 * gout155[1];
    std::vector<Ciphertext> gout394 = ctx.eval_lut_amortized(&gin394, lut394);

    std::vector<RotationPoly> lut395;
    std::vector<long (*)(long)> flut395;
    auto lut395idx0 = [](long I) -> long {
        /* GATE 890 (LUT2 _3654_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut395.push_back(ctx.genrate_lut(lut395idx0));
    flut395.push_back(lut395idx0);
    auto lut395idx1 = [](long I) -> long {
        /* GATE 815 (LUT2 _3579_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut395.push_back(ctx.genrate_lut(lut395idx1));
    flut395.push_back(lut395idx1);
    auto fvec395 = [flut395](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut395[i](I));
        return ret;
    };

    std::cerr << "\rLUT395   ";
    Ciphertext gin395 = 1 * gout383[0] + 2 * gout322[1];
    std::vector<Ciphertext> gout395 = ctx.eval_lut_amortized(&gin395, lut395);

    std::vector<RotationPoly> lut396;
    std::vector<long (*)(long)> flut396;
    auto lut396idx0 = [](long I) -> long {
        /* GATE 513 (LUT2 _3277_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut396.push_back(ctx.genrate_lut(lut396idx0));
    flut396.push_back(lut396idx0);
    auto fvec396 = [flut396](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut396[i](I));
        return ret;
    };

    std::cerr << "\rLUT396   ";
    Ciphertext gin396 = 1 * gout371[0] + 2 * gout345[1];
    std::vector<Ciphertext> gout396 = ctx.eval_lut_amortized(&gin396, lut396);

    std::vector<RotationPoly> lut397;
    std::vector<long (*)(long)> flut397;
    auto lut397idx0 = [](long I) -> long {
        /* GATE 485 (LUT2 _3249_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut397.push_back(ctx.genrate_lut(lut397idx0));
    flut397.push_back(lut397idx0);
    auto lut397idx1 = [](long I) -> long {
        /* GATE 635 (LUT2 _3399_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut397.push_back(ctx.genrate_lut(lut397idx1));
    flut397.push_back(lut397idx1);
    auto fvec397 = [flut397](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut397[i](I));
        return ret;
    };

    std::cerr << "\rLUT397   ";
    Ciphertext gin397 = 1 * gout384[0] + 2 * gout379[0];
    std::vector<Ciphertext> gout397 = ctx.eval_lut_amortized(&gin397, lut397);

    std::vector<RotationPoly> lut398;
    std::vector<long (*)(long)> flut398;
    auto lut398idx0 = [](long I) -> long {
        /* GATE 96 (LUT2 _2860_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut398.push_back(ctx.genrate_lut(lut398idx0));
    flut398.push_back(lut398idx0);
    auto lut398idx1 = [](long I) -> long {
        /* GATE 24 (LUT2 _2788_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut398.push_back(ctx.genrate_lut(lut398idx1));
    flut398.push_back(lut398idx1);
    auto fvec398 = [flut398](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut398[i](I));
        return ret;
    };

    std::cerr << "\rLUT398   ";
    Ciphertext gin398 = 1 * gout378[1] + 2 * gout238[1];
    std::vector<Ciphertext> gout398 = ctx.eval_lut_amortized(&gin398, lut398);

    std::vector<RotationPoly> lut399;
    std::vector<long (*)(long)> flut399;
    auto lut399idx0 = [](long I) -> long {
        /* GATE 874 (LUT2 _3638_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut399.push_back(ctx.genrate_lut(lut399idx0));
    flut399.push_back(lut399idx0);
    auto fvec399 = [flut399](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut399[i](I));
        return ret;
    };

    std::cerr << "\rLUT399   ";
    Ciphertext gin399 = 1 * gout361[0] + 2 * gout362[1];
    std::vector<Ciphertext> gout399 = ctx.eval_lut_amortized(&gin399, lut399);

    std::vector<RotationPoly> lut400;
    std::vector<long (*)(long)> flut400;
    auto lut400idx0 = [](long I) -> long {
        /* GATE 553 (LUT2 _3317_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut400.push_back(ctx.genrate_lut(lut400idx0));
    flut400.push_back(lut400idx0);
    auto lut400idx1 = [](long I) -> long {
        /* GATE 666 (LUT2 _3430_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut400.push_back(ctx.genrate_lut(lut400idx1));
    flut400.push_back(lut400idx1);
    auto fvec400 = [flut400](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut400[i](I));
        return ret;
    };

    std::cerr << "\rLUT400   ";
    Ciphertext gin400 = 1 * gout374[1] + 2 * gout341[0];
    std::vector<Ciphertext> gout400 = ctx.eval_lut_amortized(&gin400, lut400);

    std::vector<RotationPoly> lut401;
    std::vector<long (*)(long)> flut401;
    auto lut401idx0 = [](long I) -> long {
        /* GATE 439 (LUT2 _3203_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut401.push_back(ctx.genrate_lut(lut401idx0));
    flut401.push_back(lut401idx0);
    auto lut401idx1 = [](long I) -> long {
        /* GATE 552 (LUT2 _3316_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut401.push_back(ctx.genrate_lut(lut401idx1));
    flut401.push_back(lut401idx1);
    auto fvec401 = [flut401](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut401[i](I));
        return ret;
    };

    std::cerr << "\rLUT401   ";
    Ciphertext gin401 = 1 * gout372[0] + 2 * gout335[1];
    std::vector<Ciphertext> gout401 = ctx.eval_lut_amortized(&gin401, lut401);

    std::vector<RotationPoly> lut402;
    std::vector<long (*)(long)> flut402;
    auto lut402idx0 = [](long I) -> long {
        /* GATE 743 (LUT2 _3507_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut402.push_back(ctx.genrate_lut(lut402idx0));
    flut402.push_back(lut402idx0);
    auto fvec402 = [flut402](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut402[i](I));
        return ret;
    };

    std::cerr << "\rLUT402   ";
    Ciphertext gin402 = 1 * gout394[1] + 2 * gout355[0];
    std::vector<Ciphertext> gout402 = ctx.eval_lut_amortized(&gin402, lut402);

    std::vector<RotationPoly> lut403;
    std::vector<long (*)(long)> flut403;
    auto lut403idx0 = [](long I) -> long {
        /* GATE 520 (LUT2 _3284_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut403.push_back(ctx.genrate_lut(lut403idx0));
    flut403.push_back(lut403idx0);
    auto lut403idx1 = [](long I) -> long {
        /* GATE 365 (LUT2 _3129_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut403.push_back(ctx.genrate_lut(lut403idx1));
    flut403.push_back(lut403idx1);
    auto fvec403 = [flut403](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut403[i](I));
        return ret;
    };

    std::cerr << "\rLUT403   ";
    Ciphertext gin403 = 1 * gout319[0] + 2 * gout371[1];
    std::vector<Ciphertext> gout403 = ctx.eval_lut_amortized(&gin403, lut403);

    std::vector<RotationPoly> lut404;
    std::vector<long (*)(long)> flut404;
    auto lut404idx0 = [](long I) -> long {
        /* GATE 870 (LUT2 _3634_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut404.push_back(ctx.genrate_lut(lut404idx0));
    flut404.push_back(lut404idx0);
    auto lut404idx1 = [](long I) -> long {
        /* GATE 911 (LUT2 _3675_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut404.push_back(ctx.genrate_lut(lut404idx1));
    flut404.push_back(lut404idx1);
    auto fvec404 = [flut404](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut404[i](I));
        return ret;
    };

    std::cerr << "\rLUT404   ";
    Ciphertext gin404 = 1 * gout392[0] + 2 * gout399[0];
    std::vector<Ciphertext> gout404 = ctx.eval_lut_amortized(&gin404, lut404);

    std::vector<RotationPoly> lut405;
    std::vector<long (*)(long)> flut405;
    auto lut405idx0 = [](long I) -> long {
        /* GATE 95 (LUT2 _2859_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut405.push_back(ctx.genrate_lut(lut405idx0));
    flut405.push_back(lut405idx0);
    auto fvec405 = [flut405](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut405[i](I));
        return ret;
    };

    std::cerr << "\rLUT405   ";
    Ciphertext gin405 = 1 * gout398[0] + 2 * gout378[0];
    std::vector<Ciphertext> gout405 = ctx.eval_lut_amortized(&gin405, lut405);

    std::vector<RotationPoly> lut406;
    std::vector<long (*)(long)> flut406;
    auto lut406idx0 = [](long I) -> long {
        /* GATE 300 (LUT2 _3064_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut406.push_back(ctx.genrate_lut(lut406idx0));
    flut406.push_back(lut406idx0);
    auto lut406idx1 = [](long I) -> long {
        /* GATE 182 (LUT2 _2946_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut406.push_back(ctx.genrate_lut(lut406idx1));
    flut406.push_back(lut406idx1);
    auto fvec406 = [flut406](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut406[i](I));
        return ret;
    };

    std::cerr << "\rLUT406   ";
    Ciphertext gin406 = 1 * gout140[0] + 2 * gout370[0];
    std::vector<Ciphertext> gout406 = ctx.eval_lut_amortized(&gin406, lut406);

    std::vector<RotationPoly> lut407;
    std::vector<long (*)(long)> flut407;
    auto lut407idx0 = [](long I) -> long {
        /* GATE 394 (LUT2 _3158_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut407.push_back(ctx.genrate_lut(lut407idx0));
    flut407.push_back(lut407idx0);
    auto lut407idx1 = [](long I) -> long {
        /* GATE 261 (LUT2 _3025_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut407.push_back(ctx.genrate_lut(lut407idx1));
    flut407.push_back(lut407idx1);
    auto fvec407 = [flut407](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut407[i](I));
        return ret;
    };

    std::cerr << "\rLUT407   ";
    Ciphertext gin407 = 1 * gout366[0] + 2 * gout306[0];
    std::vector<Ciphertext> gout407 = ctx.eval_lut_amortized(&gin407, lut407);

    std::vector<RotationPoly> lut408;
    std::vector<long (*)(long)> flut408;
    auto lut408idx0 = [](long I) -> long {
        /* GATE 814 (LUT2 _3578_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut408.push_back(ctx.genrate_lut(lut408idx0));
    flut408.push_back(lut408idx0);
    auto lut408idx1 = [](long I) -> long {
        /* GATE 889 (LUT2 _3653_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut408.push_back(ctx.genrate_lut(lut408idx1));
    flut408.push_back(lut408idx1);
    auto fvec408 = [flut408](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut408[i](I));
        return ret;
    };

    std::cerr << "\rLUT408   ";
    Ciphertext gin408 = 1 * gout393[0] + 2 * gout395[1];
    std::vector<Ciphertext> gout408 = ctx.eval_lut_amortized(&gin408, lut408);

    std::vector<RotationPoly> lut409;
    std::vector<long (*)(long)> flut409;
    auto lut409idx0 = [](long I) -> long {
        /* GATE 316 (LUT2 _3080_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut409.push_back(ctx.genrate_lut(lut409idx0));
    flut409.push_back(lut409idx0);
    auto lut409idx1 = [](long I) -> long {
        /* GATE 210 (LUT2 _2974_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut409.push_back(ctx.genrate_lut(lut409idx1));
    flut409.push_back(lut409idx1);
    auto fvec409 = [flut409](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut409[i](I));
        return ret;
    };

    std::cerr << "\rLUT409   ";
    Ciphertext gin409 = 1 * gout375[0] + 2 * gout296[0];
    std::vector<Ciphertext> gout409 = ctx.eval_lut_amortized(&gin409, lut409);

    std::vector<RotationPoly> lut410;
    std::vector<long (*)(long)> flut410;
    auto lut410idx0 = [](long I) -> long {
        /* GATE 914 (LUT2 _3678_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut410.push_back(ctx.genrate_lut(lut410idx0));
    flut410.push_back(lut410idx0);
    auto lut410idx1 = [](long I) -> long {
        /* GATE 879 (LUT2 _3643_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut410.push_back(ctx.genrate_lut(lut410idx1));
    flut410.push_back(lut410idx1);
    auto fvec410 = [flut410](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut410[i](I));
        return ret;
    };

    std::cerr << "\rLUT410   ";
    Ciphertext gin410 = 1 * gout353[0] + 2 * gout390[0];
    std::vector<Ciphertext> gout410 = ctx.eval_lut_amortized(&gin410, lut410);

    std::vector<RotationPoly> lut411;
    std::vector<long (*)(long)> flut411;
    auto lut411idx0 = [](long I) -> long {
        /* GATE 669 (LUT2 _3433_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut411.push_back(ctx.genrate_lut(lut411idx0));
    flut411.push_back(lut411idx0);
    auto lut411idx1 = [](long I) -> long {
        /* GATE 782 (LUT2 _3546_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut411.push_back(ctx.genrate_lut(lut411idx1));
    flut411.push_back(lut411idx1);
    auto fvec411 = [flut411](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut411[i](I));
        return ret;
    };

    std::cerr << "\rLUT411   ";
    Ciphertext gin411 = 1 * gout387[0] + 2 * gout334[1];
    std::vector<Ciphertext> gout411 = ctx.eval_lut_amortized(&gin411, lut411);

    std::vector<RotationPoly> lut412;
    std::vector<long (*)(long)> flut412;
    auto lut412idx0 = [](long I) -> long {
        /* GATE 435 (LUT2 _3199_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut412.push_back(ctx.genrate_lut(lut412idx0));
    flut412.push_back(lut412idx0);
    auto fvec412 = [flut412](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut412[i](I));
        return ret;
    };

    std::cerr << "\rLUT412   ";
    Ciphertext gin412 = 1 * gout388[0] + 2 * gout367[1];
    std::vector<Ciphertext> gout412 = ctx.eval_lut_amortized(&gin412, lut412);

    std::vector<RotationPoly> lut413;
    std::vector<long (*)(long)> flut413;
    auto lut413idx0 = [](long I) -> long {
        /* GATE 910 (LUT2 _3674_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut413.push_back(ctx.genrate_lut(lut413idx0));
    flut413.push_back(lut413idx0);
    auto lut413idx1 = [](long I) -> long {
        /* GATE 869 (LUT2 _3633_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut413.push_back(ctx.genrate_lut(lut413idx1));
    flut413.push_back(lut413idx1);
    auto fvec413 = [flut413](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut413[i](I));
        return ret;
    };

    std::cerr << "\rLUT413   ";
    Ciphertext gin413 = 1 * gout404[0] + 2 * gout410[1];
    std::vector<Ciphertext> gout413 = ctx.eval_lut_amortized(&gin413, lut413);

    std::vector<RotationPoly> lut414;
    std::vector<long (*)(long)> flut414;
    auto lut414idx0 = [](long I) -> long {
        /* GATE 484 (LUT2 _3248_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut414.push_back(ctx.genrate_lut(lut414idx0));
    flut414.push_back(lut414idx0);
    auto lut414idx1 = [](long I) -> long {
        /* GATE 634 (LUT2 _3398_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut414.push_back(ctx.genrate_lut(lut414idx1));
    flut414.push_back(lut414idx1);
    auto fvec414 = [flut414](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut414[i](I));
        return ret;
    };

    std::cerr << "\rLUT414   ";
    Ciphertext gin414 = 1 * gout396[0] + 2 * gout397[0];
    std::vector<Ciphertext> gout414 = ctx.eval_lut_amortized(&gin414, lut414);

    std::vector<RotationPoly> lut415;
    std::vector<long (*)(long)> flut415;
    auto lut415idx0 = [](long I) -> long {
        /* GATE 299 (LUT2 _3063_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut415.push_back(ctx.genrate_lut(lut415idx0));
    flut415.push_back(lut415idx0);
    auto fvec415 = [flut415](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut415[i](I));
        return ret;
    };

    std::cerr << "\rLUT415   ";
    Ciphertext gin415 = 1 * gout406[0] + 2 * gout370[1];
    std::vector<Ciphertext> gout415 = ctx.eval_lut_amortized(&gin415, lut415);

    std::vector<RotationPoly> lut416;
    std::vector<long (*)(long)> flut416;
    auto lut416idx0 = [](long I) -> long {
        /* GATE 600 (LUT2 _3364_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut416.push_back(ctx.genrate_lut(lut416idx0));
    flut416.push_back(lut416idx0);
    auto lut416idx1 = [](long I) -> long {
        /* GATE 750 (LUT2 _3514_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut416.push_back(ctx.genrate_lut(lut416idx1));
    flut416.push_back(lut416idx1);
    auto fvec416 = [flut416](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut416[i](I));
        return ret;
    };

    std::cerr << "\rLUT416   ";
    Ciphertext gin416 = 1 * gout331[0] + 2 * gout394[0];
    std::vector<Ciphertext> gout416 = ctx.eval_lut_amortized(&gin416, lut416);

    std::vector<RotationPoly> lut417;
    std::vector<long (*)(long)> flut417;
    auto lut417idx0 = [](long I) -> long {
        /* GATE 290 (LUT2 _3054_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut417.push_back(ctx.genrate_lut(lut417idx0));
    flut417.push_back(lut417idx0);
    auto fvec417 = [flut417](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut417[i](I));
        return ret;
    };

    std::cerr << "\rLUT417   ";
    Ciphertext gin417 = 1 * gout391[0] + 2 * gout382[1];
    std::vector<Ciphertext> gout417 = ctx.eval_lut_amortized(&gin417, lut417);

    std::vector<RotationPoly> lut418;
    std::vector<long (*)(long)> flut418;
    auto lut418idx0 = [](long I) -> long {
        /* GATE 400 (LUT2 _3164_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut418.push_back(ctx.genrate_lut(lut418idx0));
    flut418.push_back(lut418idx0);
    auto lut418idx1 = [](long I) -> long {
        /* GATE 257 (LUT2 _3021_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut418.push_back(ctx.genrate_lut(lut418idx1));
    flut418.push_back(lut418idx1);
    auto fvec418 = [flut418](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut418[i](I));
        return ret;
    };

    std::cerr << "\rLUT418   ";
    Ciphertext gin418 = 1 * gout327[0] + 2 * gout407[1];
    std::vector<Ciphertext> gout418 = ctx.eval_lut_amortized(&gin418, lut418);

    std::vector<RotationPoly> lut419;
    std::vector<long (*)(long)> flut419;
    auto lut419idx0 = [](long I) -> long {
        /* GATE 888 (LUT2 _3652_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut419.push_back(ctx.genrate_lut(lut419idx0));
    flut419.push_back(lut419idx0);
    auto fvec419 = [flut419](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut419[i](I));
        return ret;
    };

    std::cerr << "\rLUT419   ";
    Ciphertext gin419 = 1 * gout408[1] + 2 * gout395[0];
    std::vector<Ciphertext> gout419 = ctx.eval_lut_amortized(&gin419, lut419);

    std::vector<RotationPoly> lut420;
    std::vector<long (*)(long)> flut420;
    auto lut420idx0 = [](long I) -> long {
        /* GATE 289 (LUT2 _3053_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut420.push_back(ctx.genrate_lut(lut420idx0));
    flut420.push_back(lut420idx0);
    auto lut420idx1 = [](long I) -> long {
        /* GATE 409 (LUT2 _3173_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut420.push_back(ctx.genrate_lut(lut420idx1));
    flut420.push_back(lut420idx1);
    auto fvec420 = [flut420](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut420[i](I));
        return ret;
    };

    std::cerr << "\rLUT420   ";
    Ciphertext gin420 = 1 * gout417[0] + 2 * gout288[0];
    std::vector<Ciphertext> gout420 = ctx.eval_lut_amortized(&gin420, lut420);

    std::vector<RotationPoly> lut421;
    std::vector<long (*)(long)> flut421;
    auto lut421idx0 = [](long I) -> long {
        /* GATE 393 (LUT2 _3157_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut421.push_back(ctx.genrate_lut(lut421idx0));
    flut421.push_back(lut421idx0);
    auto fvec421 = [flut421](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut421[i](I));
        return ret;
    };

    std::cerr << "\rLUT421   ";
    Ciphertext gin421 = 1 * gout407[0] + 2 * gout366[1];
    std::vector<Ciphertext> gout421 = ctx.eval_lut_amortized(&gin421, lut421);

    std::vector<RotationPoly> lut422;
    std::vector<long (*)(long)> flut422;
    auto lut422idx0 = [](long I) -> long {
        /* GATE 312 (LUT2 _3076_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut422.push_back(ctx.genrate_lut(lut422idx0));
    flut422.push_back(lut422idx0);
    auto lut422idx1 = [](long I) -> long {
        /* GATE 206 (LUT2 _2970_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut422.push_back(ctx.genrate_lut(lut422idx1));
    flut422.push_back(lut422idx1);
    auto fvec422 = [flut422](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut422[i](I));
        return ret;
    };

    std::cerr << "\rLUT422   ";
    Ciphertext gin422 = 1 * gout386[0] + 2 * gout409[1];
    std::vector<Ciphertext> gout422 = ctx.eval_lut_amortized(&gin422, lut422);

    std::vector<RotationPoly> lut423;
    std::vector<long (*)(long)> flut423;
    auto lut423idx0 = [](long I) -> long {
        /* GATE 599 (LUT2 _3363_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut423.push_back(ctx.genrate_lut(lut423idx0));
    flut423.push_back(lut423idx0);
    auto lut423idx1 = [](long I) -> long {
        /* GATE 749 (LUT2 _3513_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut423.push_back(ctx.genrate_lut(lut423idx1));
    flut423.push_back(lut423idx1);
    auto fvec423 = [flut423](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut423[i](I));
        return ret;
    };

    std::cerr << "\rLUT423   ";
    Ciphertext gin423 = 1 * gout385[0] + 2 * gout416[0];
    std::vector<Ciphertext> gout423 = ctx.eval_lut_amortized(&gin423, lut423);

    std::vector<RotationPoly> lut424;
    std::vector<long (*)(long)> flut424;
    auto lut424idx0 = [](long I) -> long {
        /* GATE 633 (LUT2 _3397_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut424.push_back(ctx.genrate_lut(lut424idx0));
    flut424.push_back(lut424idx0);
    auto fvec424 = [flut424](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut424[i](I));
        return ret;
    };

    std::cerr << "\rLUT424   ";
    Ciphertext gin424 = 1 * gout414[1] + 2 * gout397[1];
    std::vector<Ciphertext> gout424 = ctx.eval_lut_amortized(&gin424, lut424);

    std::vector<RotationPoly> lut425;
    std::vector<long (*)(long)> flut425;
    auto lut425idx0 = [](long I) -> long {
        /* GATE 315 (LUT2 _3079_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut425.push_back(ctx.genrate_lut(lut425idx0));
    flut425.push_back(lut425idx0);
    auto fvec425 = [flut425](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut425[i](I));
        return ret;
    };

    std::cerr << "\rLUT425   ";
    Ciphertext gin425 = 1 * gout409[0] + 2 * gout375[1];
    std::vector<Ciphertext> gout425 = ctx.eval_lut_amortized(&gin425, lut425);

    std::vector<RotationPoly> lut426;
    std::vector<long (*)(long)> flut426;
    auto lut426idx0 = [](long I) -> long {
        /* GATE 665 (LUT2 _3429_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut426.push_back(ctx.genrate_lut(lut426idx0));
    flut426.push_back(lut426idx0);
    auto fvec426 = [flut426](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut426[i](I));
        return ret;
    };

    std::cerr << "\rLUT426   ";
    Ciphertext gin426 = 1 * gout400[1] + 2 * gout374[0];
    std::vector<Ciphertext> gout426 = ctx.eval_lut_amortized(&gin426, lut426);

    std::vector<RotationPoly> lut427;
    std::vector<long (*)(long)> flut427;
    auto lut427idx0 = [](long I) -> long {
        /* GATE 909 (LUT2 _3673_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut427.push_back(ctx.genrate_lut(lut427idx0));
    flut427.push_back(lut427idx0);
    auto fvec427 = [flut427](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut427[i](I));
        return ret;
    };

    std::cerr << "\rLUT427   ";
    Ciphertext gin427 = 1 * gout413[0] + 2 * gout404[1];
    std::vector<Ciphertext> gout427 = ctx.eval_lut_amortized(&gin427, lut427);

    std::vector<RotationPoly> lut428;
    std::vector<long (*)(long)> flut428;
    auto lut428idx0 = [](long I) -> long {
        /* GATE 103 (LUT2 _2867_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut428.push_back(ctx.genrate_lut(lut428idx0));
    flut428.push_back(lut428idx0);
    auto lut428idx1 = [](long I) -> long {
        /* GATE 203 (LUT2 _2967_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut428.push_back(ctx.genrate_lut(lut428idx1));
    flut428.push_back(lut428idx1);
    auto fvec428 = [flut428](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut428[i](I));
        return ret;
    };

    std::cerr << "\rLUT428   ";
    Ciphertext gin428 = 1 * gout369[1] + 2 * gout391[1];
    std::vector<Ciphertext> gout428 = ctx.eval_lut_amortized(&gin428, lut428);

    std::vector<RotationPoly> lut429;
    std::vector<long (*)(long)> flut429;
    auto lut429idx0 = [](long I) -> long {
        /* GATE 913 (LUT2 _3677_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut429.push_back(ctx.genrate_lut(lut429idx0));
    flut429.push_back(lut429idx0);
    auto fvec429 = [flut429](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut429[i](I));
        return ret;
    };

    std::cerr << "\rLUT429   ";
    Ciphertext gin429 = 1 * gout410[0] + 2 * gout390[1];
    std::vector<Ciphertext> gout429 = ctx.eval_lut_amortized(&gin429, lut429);

    std::vector<RotationPoly> lut430;
    std::vector<long (*)(long)> flut430;
    auto lut430idx0 = [](long I) -> long {
        /* GATE 668 (LUT2 _3432_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut430.push_back(ctx.genrate_lut(lut430idx0));
    flut430.push_back(lut430idx0);
    auto lut430idx1 = [](long I) -> long {
        /* GATE 781 (LUT2 _3545_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut430.push_back(ctx.genrate_lut(lut430idx1));
    flut430.push_back(lut430idx1);
    auto fvec430 = [flut430](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut430[i](I));
        return ret;
    };

    std::cerr << "\rLUT430   ";
    Ciphertext gin430 = 1 * gout411[0] + 2 * gout354[1];
    std::vector<Ciphertext> gout430 = ctx.eval_lut_amortized(&gin430, lut430);

    std::vector<RotationPoly> lut431;
    std::vector<long (*)(long)> flut431;
    auto lut431idx0 = [](long I) -> long {
        /* GATE 777 (LUT2 _3541_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut431.push_back(ctx.genrate_lut(lut431idx0));
    flut431.push_back(lut431idx0);
    auto lut431idx1 = [](long I) -> long {
        /* GATE 664 (LUT2 _3428_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut431.push_back(ctx.genrate_lut(lut431idx1));
    flut431.push_back(lut431idx1);
    auto fvec431 = [flut431](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut431[i](I));
        return ret;
    };

    std::cerr << "\rLUT431   ";
    Ciphertext gin431 = 1 * gout426[0] + 2 * gout430[0];
    std::vector<Ciphertext> gout431 = ctx.eval_lut_amortized(&gin431, lut431);

    std::vector<RotationPoly> lut432;
    std::vector<long (*)(long)> flut432;
    auto lut432idx0 = [](long I) -> long {
        /* GATE 199 (LUT2 _2963_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut432.push_back(ctx.genrate_lut(lut432idx0));
    flut432.push_back(lut432idx0);
    auto lut432idx1 = [](long I) -> long {
        /* GATE 99 (LUT2 _2863_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut432.push_back(ctx.genrate_lut(lut432idx1));
    flut432.push_back(lut432idx1);
    auto fvec432 = [flut432](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut432[i](I));
        return ret;
    };

    std::cerr << "\rLUT432   ";
    Ciphertext gin432 = 1 * gout358[0] + 2 * gout428[0];
    std::vector<Ciphertext> gout432 = ctx.eval_lut_amortized(&gin432, lut432);

    std::vector<RotationPoly> lut433;
    std::vector<long (*)(long)> flut433;
    auto lut433idx0 = [](long I) -> long {
        /* GATE 408 (LUT2 _3172_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut433.push_back(ctx.genrate_lut(lut433idx0));
    flut433.push_back(lut433idx0);
    auto lut433idx1 = [](long I) -> long {
        /* GATE 288 (LUT2 _3052_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut433.push_back(ctx.genrate_lut(lut433idx1));
    flut433.push_back(lut433idx1);
    auto fvec433 = [flut433](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut433[i](I));
        return ret;
    };

    std::cerr << "\rLUT433   ";
    Ciphertext gin433 = 1 * gout135[0] + 2 * gout420[0];
    std::vector<Ciphertext> gout433 = ctx.eval_lut_amortized(&gin433, lut433);

    std::vector<RotationPoly> lut434;
    std::vector<long (*)(long)> flut434;
    auto lut434idx0 = [](long I) -> long {
        /* GATE 714 (LUT2 _3478_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut434.push_back(ctx.genrate_lut(lut434idx0));
    flut434.push_back(lut434idx0);
    auto lut434idx1 = [](long I) -> long {
        /* GATE 840 (LUT2 _3604_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut434.push_back(ctx.genrate_lut(lut434idx1));
    flut434.push_back(lut434idx1);
    auto fvec434 = [flut434](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut434[i](I));
        return ret;
    };

    std::cerr << "\rLUT434   ";
    Ciphertext gin434 = 1 * gout402[0] + 2 * gout380[1];
    std::vector<Ciphertext> gout434 = ctx.eval_lut_amortized(&gin434, lut434);

    std::vector<RotationPoly> lut435;
    std::vector<long (*)(long)> flut435;
    auto lut435idx0 = [](long I) -> long {
        /* GATE 256 (LUT2 _3020_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut435.push_back(ctx.genrate_lut(lut435idx0));
    flut435.push_back(lut435idx0);
    auto lut435idx1 = [](long I) -> long {
        /* GATE 399 (LUT2 _3163_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut435.push_back(ctx.genrate_lut(lut435idx1));
    flut435.push_back(lut435idx1);
    auto fvec435 = [flut435](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut435[i](I));
        return ret;
    };

    std::cerr << "\rLUT435   ";
    Ciphertext gin435 = 1 * gout376[0] + 2 * gout418[1];
    std::vector<Ciphertext> gout435 = ctx.eval_lut_amortized(&gin435, lut435);

    std::vector<RotationPoly> lut436;
    std::vector<long (*)(long)> flut436;
    auto lut436idx0 = [](long I) -> long {
        /* GATE 632 (LUT2 _3396_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut436.push_back(ctx.genrate_lut(lut436idx0));
    flut436.push_back(lut436idx0);
    auto lut436idx1 = [](long I) -> long {
        /* GATE 759 (LUT2 _3523_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut436.push_back(ctx.genrate_lut(lut436idx1));
    flut436.push_back(lut436idx1);
    auto fvec436 = [flut436](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut436[i](I));
        return ret;
    };

    std::cerr << "\rLUT436   ";
    Ciphertext gin436 = 1 * gout424[0] + 2 * gout237[0];
    std::vector<Ciphertext> gout436 = ctx.eval_lut_amortized(&gin436, lut436);

    std::vector<RotationPoly> lut437;
    std::vector<long (*)(long)> flut437;
    auto lut437idx0 = [](long I) -> long {
        /* GATE 438 (LUT2 _3202_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut437.push_back(ctx.genrate_lut(lut437idx0));
    flut437.push_back(lut437idx0);
    auto lut437idx1 = [](long I) -> long {
        /* GATE 551 (LUT2 _3315_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut437.push_back(ctx.genrate_lut(lut437idx1));
    flut437.push_back(lut437idx1);
    auto fvec437 = [flut437](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut437[i](I));
        return ret;
    };

    std::cerr << "\rLUT437   ";
    Ciphertext gin437 = 1 * gout401[0] + 2 * gout310[0];
    std::vector<Ciphertext> gout437 = ctx.eval_lut_amortized(&gin437, lut437);

    std::vector<RotationPoly> lut438;
    std::vector<long (*)(long)> flut438;
    auto lut438idx0 = [](long I) -> long {
        /* GATE 908 (LUT2 _3672_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut438.push_back(ctx.genrate_lut(lut438idx0));
    flut438.push_back(lut438idx0);
    auto lut438idx1 = [](long I) -> long {
        /* GATE 924 (LUT2 _3688_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut438.push_back(ctx.genrate_lut(lut438idx1));
    flut438.push_back(lut438idx1);
    auto fvec438 = [flut438](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut438[i](I));
        return ret;
    };

    std::cerr << "\rLUT438   ";
    Ciphertext gin438 = 1 * gout427[0] + 2 * gout362[0];
    std::vector<Ciphertext> gout438 = ctx.eval_lut_amortized(&gin438, lut438);

    std::vector<RotationPoly> lut439;
    std::vector<long (*)(long)> flut439;
    auto lut439idx0 = [](long I) -> long {
        /* GATE 519 (LUT2 _3283_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut439.push_back(ctx.genrate_lut(lut439idx0));
    flut439.push_back(lut439idx0);
    auto lut439idx1 = [](long I) -> long {
        /* GATE 364 (LUT2 _3128_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut439.push_back(ctx.genrate_lut(lut439idx1));
    flut439.push_back(lut439idx1);
    auto fvec439 = [flut439](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut439[i](I));
        return ret;
    };

    std::cerr << "\rLUT439   ";
    Ciphertext gin439 = 1 * gout421[0] + 2 * gout403[1];
    std::vector<Ciphertext> gout439 = ctx.eval_lut_amortized(&gin439, lut439);

    std::vector<RotationPoly> lut440;
    std::vector<long (*)(long)> flut440;
    auto lut440idx0 = [](long I) -> long {
        /* GATE 202 (LUT2 _2966_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut440.push_back(ctx.genrate_lut(lut440idx0));
    flut440.push_back(lut440idx0);
    auto fvec440 = [flut440](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut440[i](I));
        return ret;
    };

    std::cerr << "\rLUT440   ";
    Ciphertext gin440 = 1 * gout428[1] + 2 * gout369[0];
    std::vector<Ciphertext> gout440 = ctx.eval_lut_amortized(&gin440, lut440);

    std::vector<RotationPoly> lut441;
    std::vector<long (*)(long)> flut441;
    auto lut441idx0 = [](long I) -> long {
        /* GATE 550 (LUT2 _3314_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut441.push_back(ctx.genrate_lut(lut441idx0));
    flut441.push_back(lut441idx0);
    auto fvec441 = [flut441](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut441[i](I));
        return ret;
    };

    std::cerr << "\rLUT441   ";
    Ciphertext gin441 = 1 * gout437[1] + 2 * gout401[1];
    std::vector<Ciphertext> gout441 = ctx.eval_lut_amortized(&gin441, lut441);

    std::vector<RotationPoly> lut442;
    std::vector<long (*)(long)> flut442;
    auto lut442idx0 = [](long I) -> long {
        /* GATE 780 (LUT2 _3544_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut442.push_back(ctx.genrate_lut(lut442idx0));
    flut442.push_back(lut442idx0);
    auto fvec442 = [flut442](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut442[i](I));
        return ret;
    };

    std::cerr << "\rLUT442   ";
    Ciphertext gin442 = 1 * gout430[1] + 2 * gout411[1];
    std::vector<Ciphertext> gout442 = ctx.eval_lut_amortized(&gin442, lut442);

    std::vector<RotationPoly> lut443;
    std::vector<long (*)(long)> flut443;
    auto lut443idx0 = [](long I) -> long {
        /* GATE 839 (LUT2 _3603_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut443.push_back(ctx.genrate_lut(lut443idx0));
    flut443.push_back(lut443idx0);
    auto fvec443 = [flut443](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut443[i](I));
        return ret;
    };

    std::cerr << "\rLUT443   ";
    Ciphertext gin443 = 1 * gout434[1] + 2 * gout380[0];
    std::vector<Ciphertext> gout443 = ctx.eval_lut_amortized(&gin443, lut443);

    std::vector<RotationPoly> lut444;
    std::vector<long (*)(long)> flut444;
    auto lut444idx0 = [](long I) -> long {
        /* GATE 407 (LUT2 _3171_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut444.push_back(ctx.genrate_lut(lut444idx0));
    flut444.push_back(lut444idx0);
    auto fvec444 = [flut444](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut444[i](I));
        return ret;
    };

    std::cerr << "\rLUT444   ";
    Ciphertext gin444 = 1 * gout433[0] + 2 * gout420[1];
    std::vector<Ciphertext> gout444 = ctx.eval_lut_amortized(&gin444, lut444);

    std::vector<RotationPoly> lut445;
    std::vector<long (*)(long)> flut445;
    auto lut445idx0 = [](long I) -> long {
        /* GATE 776 (LUT2 _3540_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut445.push_back(ctx.genrate_lut(lut445idx0));
    flut445.push_back(lut445idx0);
    auto lut445idx1 = [](long I) -> long {
        /* GATE 663 (LUT2 _3427_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut445.push_back(ctx.genrate_lut(lut445idx1));
    flut445.push_back(lut445idx1);
    auto fvec445 = [flut445](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut445[i](I));
        return ret;
    };

    std::cerr << "\rLUT445   ";
    Ciphertext gin445 = 1 * gout431[1] + 2 * gout434[0];
    std::vector<Ciphertext> gout445 = ctx.eval_lut_amortized(&gin445, lut445);

    std::vector<RotationPoly> lut446;
    std::vector<long (*)(long)> flut446;
    auto lut446idx0 = [](long I) -> long {
        /* GATE 748 (LUT2 _3512_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut446.push_back(ctx.genrate_lut(lut446idx0));
    flut446.push_back(lut446idx0);
    auto fvec446 = [flut446](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut446[i](I));
        return ret;
    };

    std::cerr << "\rLUT446   ";
    Ciphertext gin446 = 1 * gout423[1] + 2 * gout416[1];
    std::vector<Ciphertext> gout446 = ctx.eval_lut_amortized(&gin446, lut446);

    std::vector<RotationPoly> lut447;
    std::vector<long (*)(long)> flut447;
    auto lut447idx0 = [](long I) -> long {
        /* GATE 432 (LUT2 _3196_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut447.push_back(ctx.genrate_lut(lut447idx0));
    flut447.push_back(lut447idx0);
    auto lut447idx1 = [](long I) -> long {
        /* GATE 314 (LUT2 _3078_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut447.push_back(ctx.genrate_lut(lut447idx1));
    flut447.push_back(lut447idx1);
    auto fvec447 = [flut447](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut447[i](I));
        return ret;
    };

    std::cerr << "\rLUT447   ";
    Ciphertext gin447 = 1 * gout425[0] + 2 * gout388[1];
    std::vector<Ciphertext> gout447 = ctx.eval_lut_amortized(&gin447, lut447);

    std::vector<RotationPoly> lut448;
    std::vector<long (*)(long)> flut448;
    auto lut448idx0 = [](long I) -> long {
        /* GATE 775 (LUT2 _3539_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut448.push_back(ctx.genrate_lut(lut448idx0));
    flut448.push_back(lut448idx0);
    auto fvec448 = [flut448](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut448[i](I));
        return ret;
    };

    std::cerr << "\rLUT448   ";
    Ciphertext gin448 = 1 * gout445[0] + 2 * gout431[0];
    std::vector<Ciphertext> gout448 = ctx.eval_lut_amortized(&gin448, lut448);

    std::vector<RotationPoly> lut449;
    std::vector<long (*)(long)> flut449;
    auto lut449idx0 = [](long I) -> long {
        /* GATE 779 (LUT2 _3543_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut449.push_back(ctx.genrate_lut(lut449idx0));
    flut449.push_back(lut449idx0);
    auto lut449idx1 = [](long I) -> long {
        /* GATE 868 (LUT2 _3632_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut449.push_back(ctx.genrate_lut(lut449idx1));
    flut449.push_back(lut449idx1);
    auto fvec449 = [flut449](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut449[i](I));
        return ret;
    };

    std::cerr << "\rLUT449   ";
    Ciphertext gin449 = 1 * gout442[0] + 2 * gout389[0];
    std::vector<Ciphertext> gout449 = ctx.eval_lut_amortized(&gin449, lut449);

    std::vector<RotationPoly> lut450;
    std::vector<long (*)(long)> flut450;
    auto lut450idx0 = [](long I) -> long {
        /* GATE 398 (LUT2 _3162_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut450.push_back(ctx.genrate_lut(lut450idx0));
    flut450.push_back(lut450idx0);
    auto fvec450 = [flut450](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut450[i](I));
        return ret;
    };

    std::cerr << "\rLUT450   ";
    Ciphertext gin450 = 1 * gout435[1] + 2 * gout418[0];
    std::vector<Ciphertext> gout450 = ctx.eval_lut_amortized(&gin450, lut450);

    std::vector<RotationPoly> lut451;
    std::vector<long (*)(long)> flut451;
    auto lut451idx0 = [](long I) -> long {
        /* GATE 838 (LUT2 _3602_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut451.push_back(ctx.genrate_lut(lut451idx0));
    flut451.push_back(lut451idx0);
    auto lut451idx1 = [](long I) -> long {
        /* GATE 893 (LUT2 _3657_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut451.push_back(ctx.genrate_lut(lut451idx1));
    flut451.push_back(lut451idx1);
    auto fvec451 = [flut451](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut451[i](I));
        return ret;
    };

    std::cerr << "\rLUT451   ";
    Ciphertext gin451 = 1 * gout443[0] + 2 * gout309[0];
    std::vector<Ciphertext> gout451 = ctx.eval_lut_amortized(&gin451, lut451);

    std::vector<RotationPoly> lut452;
    std::vector<long (*)(long)> flut452;
    auto lut452idx0 = [](long I) -> long {
        /* GATE 892 (LUT2 _3656_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut452.push_back(ctx.genrate_lut(lut452idx0));
    flut452.push_back(lut452idx0);
    auto lut452idx1 = [](long I) -> long {
        /* GATE 837 (LUT2 _3601_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut452.push_back(ctx.genrate_lut(lut452idx1));
    flut452.push_back(lut452idx1);
    auto fvec452 = [flut452](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut452[i](I));
        return ret;
    };

    std::cerr << "\rLUT452   ";
    Ciphertext gin452 = 1 * gout152[0] + 2 * gout451[0];
    std::vector<Ciphertext> gout452 = ctx.eval_lut_amortized(&gin452, lut452);

    std::vector<RotationPoly> lut453;
    std::vector<long (*)(long)> flut453;
    auto lut453idx0 = [](long I) -> long {
        /* GATE 518 (LUT2 _3282_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut453.push_back(ctx.genrate_lut(lut453idx0));
    flut453.push_back(lut453idx0);
    auto fvec453 = [flut453](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut453[i](I));
        return ret;
    };

    std::cerr << "\rLUT453   ";
    Ciphertext gin453 = 1 * gout439[0] + 2 * gout403[0];
    std::vector<Ciphertext> gout453 = ctx.eval_lut_amortized(&gin453, lut453);

    std::vector<RotationPoly> lut454;
    std::vector<long (*)(long)> flut454;
    auto lut454idx0 = [](long I) -> long {
        /* GATE 891 (LUT2 _3655_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut454.push_back(ctx.genrate_lut(lut454idx0));
    flut454.push_back(lut454idx0);
    auto fvec454 = [flut454](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut454[i](I));
        return ret;
    };

    std::cerr << "\rLUT454   ";
    Ciphertext gin454 = 1 * gout452[0] + 2 * gout451[1];
    std::vector<Ciphertext> gout454 = ctx.eval_lut_amortized(&gin454, lut454);

    std::vector<RotationPoly> lut455;
    std::vector<long (*)(long)> flut455;
    auto lut455idx0 = [](long I) -> long {
        /* GATE 923 (LUT2 _3687_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut455.push_back(ctx.genrate_lut(lut455idx0));
    flut455.push_back(lut455idx0);
    auto lut455idx1 = [](long I) -> long {
        /* GATE 907 (LUT2 _3671_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut455.push_back(ctx.genrate_lut(lut455idx1));
    flut455.push_back(lut455idx1);
    auto fvec455 = [flut455](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut455[i](I));
        return ret;
    };

    std::cerr << "\rLUT455   ";
    Ciphertext gin455 = 1 * gout438[0] + 2 * gout429[0];
    std::vector<Ciphertext> gout455 = ctx.eval_lut_amortized(&gin455, lut455);

    std::vector<RotationPoly> lut456;
    std::vector<long (*)(long)> flut456;
    auto lut456idx0 = [](long I) -> long {
        /* GATE 98 (LUT2 _2862_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut456.push_back(ctx.genrate_lut(lut456idx0));
    flut456.push_back(lut456idx0);
    auto lut456idx1 = [](long I) -> long {
        /* GATE 198 (LUT2 _2962_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut456.push_back(ctx.genrate_lut(lut456idx1));
    flut456.push_back(lut456idx1);
    auto fvec456 = [flut456](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut456[i](I));
        return ret;
    };

    std::cerr << "\rLUT456   ";
    Ciphertext gin456 = 1 * gout432[1] + 2 * gout406[1];
    std::vector<Ciphertext> gout456 = ctx.eval_lut_amortized(&gin456, lut456);

    std::vector<RotationPoly> lut457;
    std::vector<long (*)(long)> flut457;
    auto lut457idx0 = [](long I) -> long {
        /* GATE 758 (LUT2 _3522_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut457.push_back(ctx.genrate_lut(lut457idx0));
    flut457.push_back(lut457idx0);
    auto lut457idx1 = [](long I) -> long {
        /* GATE 631 (LUT2 _3395_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut457.push_back(ctx.genrate_lut(lut457idx1));
    flut457.push_back(lut457idx1);
    auto fvec457 = [flut457](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut457[i](I));
        return ret;
    };

    std::cerr << "\rLUT457   ";
    Ciphertext gin457 = 1 * gout127[0] + 2 * gout436[0];
    std::vector<Ciphertext> gout457 = ctx.eval_lut_amortized(&gin457, lut457);

    std::vector<RotationPoly> lut458;
    std::vector<long (*)(long)> flut458;
    auto lut458idx0 = [](long I) -> long {
        /* GATE 867 (LUT2 _3631_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut458.push_back(ctx.genrate_lut(lut458idx0));
    flut458.push_back(lut458idx0);
    auto lut458idx1 = [](long I) -> long {
        /* GATE 778 (LUT2 _3542_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut458.push_back(ctx.genrate_lut(lut458idx1));
    flut458.push_back(lut458idx1);
    auto fvec458 = [flut458](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut458[i](I));
        return ret;
    };

    std::cerr << "\rLUT458   ";
    Ciphertext gin458 = 1 * gout449[0] + 2 * gout408[0];
    std::vector<Ciphertext> gout458 = ctx.eval_lut_amortized(&gin458, lut458);

    std::vector<RotationPoly> lut459;
    std::vector<long (*)(long)> flut459;
    auto lut459idx0 = [](long I) -> long {
        /* GATE 922 (LUT2 _3686_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut459.push_back(ctx.genrate_lut(lut459idx0));
    flut459.push_back(lut459idx0);
    auto fvec459 = [flut459](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut459[i](I));
        return ret;
    };

    std::cerr << "\rLUT459   ";
    Ciphertext gin459 = 1 * gout455[0] + 2 * gout438[1];
    std::vector<Ciphertext> gout459 = ctx.eval_lut_amortized(&gin459, lut459);

    std::vector<RotationPoly> lut460;
    std::vector<long (*)(long)> flut460;
    auto lut460idx0 = [](long I) -> long {
        /* GATE 662 (LUT2 _3426_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut460.push_back(ctx.genrate_lut(lut460idx0));
    flut460.push_back(lut460idx0);
    auto lut460idx1 = [](long I) -> long {
        /* GATE 549 (LUT2 _3313_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut460.push_back(ctx.genrate_lut(lut460idx1));
    flut460.push_back(lut460idx1);
    auto fvec460 = [flut460](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut460[i](I));
        return ret;
    };

    std::cerr << "\rLUT460   ";
    Ciphertext gin460 = 1 * gout441[0] + 2 * gout400[0];
    std::vector<Ciphertext> gout460 = ctx.eval_lut_amortized(&gin460, lut460);

    std::vector<RotationPoly> lut461;
    std::vector<long (*)(long)> flut461;
    auto lut461idx0 = [](long I) -> long {
        /* GATE 547 (LUT2 _3311_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut461.push_back(ctx.genrate_lut(lut461idx0));
    flut461.push_back(lut461idx0);
    auto lut461idx1 = [](long I) -> long {
        /* GATE 434 (LUT2 _3198_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut461.push_back(ctx.genrate_lut(lut461idx1));
    flut461.push_back(lut461idx1);
    auto fvec461 = [flut461](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut461[i](I));
        return ret;
    };

    std::cerr << "\rLUT461   ";
    Ciphertext gin461 = 1 * gout412[0] + 2 * gout437[0];
    std::vector<Ciphertext> gout461 = ctx.eval_lut_amortized(&gin461, lut461);

    std::vector<RotationPoly> lut462;
    std::vector<long (*)(long)> flut462;
    auto lut462idx0 = [](long I) -> long {
        /* GATE 644 (LUT2 _3408_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut462.push_back(ctx.genrate_lut(lut462idx0));
    flut462.push_back(lut462idx0);
    auto lut462idx1 = [](long I) -> long {
        /* GATE 517 (LUT2 _3281_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut462.push_back(ctx.genrate_lut(lut462idx1));
    flut462.push_back(lut462idx1);
    auto fvec462 = [flut462](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut462[i](I));
        return ret;
    };

    std::cerr << "\rLUT462   ";
    Ciphertext gin462 = 1 * gout453[0] + 2 * gout251[0];
    std::vector<Ciphertext> gout462 = ctx.eval_lut_amortized(&gin462, lut462);

    std::vector<RotationPoly> lut463;
    std::vector<long (*)(long)> flut463;
    auto lut463idx0 = [](long I) -> long {
        /* GATE 866 (LUT2 _3630_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut463.push_back(ctx.genrate_lut(lut463idx0));
    flut463.push_back(lut463idx0);
    auto fvec463 = [flut463](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut463[i](I));
        return ret;
    };

    std::cerr << "\rLUT463   ";
    Ciphertext gin463 = 1 * gout458[0] + 2 * gout449[1];
    std::vector<Ciphertext> gout463 = ctx.eval_lut_amortized(&gin463, lut463);

    std::vector<RotationPoly> lut464;
    std::vector<long (*)(long)> flut464;
    auto lut464idx0 = [](long I) -> long {
        /* GATE 431 (LUT2 _3195_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut464.push_back(ctx.genrate_lut(lut464idx0));
    flut464.push_back(lut464idx0);
    auto lut464idx1 = [](long I) -> long {
        /* GATE 313 (LUT2 _3077_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut464.push_back(ctx.genrate_lut(lut464idx1));
    flut464.push_back(lut464idx1);
    auto fvec464 = [flut464](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut464[i](I));
        return ret;
    };

    std::cerr << "\rLUT464   ";
    Ciphertext gin464 = 1 * gout447[1] + 2 * gout439[1];
    std::vector<Ciphertext> gout464 = ctx.eval_lut_amortized(&gin464, lut464);

    std::vector<RotationPoly> lut465;
    std::vector<long (*)(long)> flut465;
    auto lut465idx0 = [](long I) -> long {
        /* GATE 757 (LUT2 _3521_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut465.push_back(ctx.genrate_lut(lut465idx0));
    flut465.push_back(lut465idx0);
    auto fvec465 = [flut465](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut465[i](I));
        return ret;
    };

    std::cerr << "\rLUT465   ";
    Ciphertext gin465 = 1 * gout457[0] + 2 * gout436[1];
    std::vector<Ciphertext> gout465 = ctx.eval_lut_amortized(&gin465, lut465);

    std::vector<RotationPoly> lut466;
    std::vector<long (*)(long)> flut466;
    auto lut466idx0 = [](long I) -> long {
        /* GATE 197 (LUT2 _2961_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut466.push_back(ctx.genrate_lut(lut466idx0));
    flut466.push_back(lut466idx0);
    auto fvec466 = [flut466](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut466[i](I));
        return ret;
    };

    std::cerr << "\rLUT466   ";
    Ciphertext gin466 = 1 * gout456[1] + 2 * gout432[0];
    std::vector<Ciphertext> gout466 = ctx.eval_lut_amortized(&gin466, lut466);

    std::vector<RotationPoly> lut467;
    std::vector<long (*)(long)> flut467;
    auto lut467idx0 = [](long I) -> long {
        /* GATE 747 (LUT2 _3511_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut467.push_back(ctx.genrate_lut(lut467idx0));
    flut467.push_back(lut467idx0);
    auto lut467idx1 = [](long I) -> long {
        /* GATE 850 (LUT2 _3614_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut467.push_back(ctx.genrate_lut(lut467idx1));
    flut467.push_back(lut467idx1);
    auto fvec467 = [flut467](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut467[i](I));
        return ret;
    };

    std::cerr << "\rLUT467   ";
    Ciphertext gin467 = 1 * gout446[0] + 2 * gout205[0];
    std::vector<Ciphertext> gout467 = ctx.eval_lut_amortized(&gin467, lut467);

    std::vector<RotationPoly> lut468;
    std::vector<long (*)(long)> flut468;
    auto lut468idx0 = [](long I) -> long {
        /* GATE 430 (LUT2 _3194_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut468.push_back(ctx.genrate_lut(lut468idx0));
    flut468.push_back(lut468idx0);
    auto fvec468 = [flut468](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut468[i](I));
        return ret;
    };

    std::cerr << "\rLUT468   ";
    Ciphertext gin468 = 1 * gout464[0] + 2 * gout447[0];
    std::vector<Ciphertext> gout468 = ctx.eval_lut_amortized(&gin468, lut468);

    std::vector<RotationPoly> lut469;
    std::vector<long (*)(long)> flut469;
    auto lut469idx0 = [](long I) -> long {
        /* GATE 311 (LUT2 _3075_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut469.push_back(ctx.genrate_lut(lut469idx0));
    flut469.push_back(lut469idx0);
    auto lut469idx1 = [](long I) -> long {
        /* GATE 205 (LUT2 _2969_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut469.push_back(ctx.genrate_lut(lut469idx1));
    flut469.push_back(lut469idx1);
    auto fvec469 = [flut469](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut469[i](I));
        return ret;
    };

    std::cerr << "\rLUT469   ";
    Ciphertext gin469 = 1 * gout422[1] + 2 * gout435[0];
    std::vector<Ciphertext> gout469 = ctx.eval_lut_amortized(&gin469, lut469);

    std::vector<RotationPoly> lut470;
    std::vector<long (*)(long)> flut470;
    auto lut470idx0 = [](long I) -> long {
        /* GATE 529 (LUT2 _3293_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut470.push_back(ctx.genrate_lut(lut470idx0));
    flut470.push_back(lut470idx0);
    auto lut470idx1 = [](long I) -> long {
        /* GATE 397 (LUT2 _3161_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut470.push_back(ctx.genrate_lut(lut470idx1));
    flut470.push_back(lut470idx1);
    auto fvec470 = [flut470](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut470[i](I));
        return ret;
    };

    std::cerr << "\rLUT470   ";
    Ciphertext gin470 = 1 * gout450[0] + 2 * gout320[0];
    std::vector<Ciphertext> gout470 = ctx.eval_lut_amortized(&gin470, lut470);

    std::vector<RotationPoly> lut471;
    std::vector<long (*)(long)> flut471;
    auto lut471idx0 = [](long I) -> long {
        /* GATE 774 (LUT2 _3538_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut471.push_back(ctx.genrate_lut(lut471idx0));
    flut471.push_back(lut471idx0);
    auto lut471idx1 = [](long I) -> long {
        /* GATE 863 (LUT2 _3627_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut471.push_back(ctx.genrate_lut(lut471idx1));
    flut471.push_back(lut471idx1);
    auto fvec471 = [flut471](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut471[i](I));
        return ret;
    };

    std::cerr << "\rLUT471   ";
    Ciphertext gin471 = 1 * gout448[0] + 2 * gout458[1];
    std::vector<Ciphertext> gout471 = ctx.eval_lut_amortized(&gin471, lut471);

    std::vector<RotationPoly> lut472;
    std::vector<long (*)(long)> flut472;
    auto lut472idx0 = [](long I) -> long {
        /* GATE 849 (LUT2 _3613_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut472.push_back(ctx.genrate_lut(lut472idx0));
    flut472.push_back(lut472idx0);
    auto lut472idx1 = [](long I) -> long {
        /* GATE 746 (LUT2 _3510_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut472.push_back(ctx.genrate_lut(lut472idx1));
    flut472.push_back(lut472idx1);
    auto fvec472 = [flut472](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut472[i](I));
        return ret;
    };

    std::cerr << "\rLUT472   ";
    Ciphertext gin472 = 1 * gout86[0] + 2 * gout467[0];
    std::vector<Ciphertext> gout472 = ctx.eval_lut_amortized(&gin472, lut472);

    std::vector<RotationPoly> lut473;
    std::vector<long (*)(long)> flut473;
    auto lut473idx0 = [](long I) -> long {
        /* GATE 906 (LUT2 _3670_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut473.push_back(ctx.genrate_lut(lut473idx0));
    flut473.push_back(lut473idx0);
    auto lut473idx1 = [](long I) -> long {
        /* GATE 865 (LUT2 _3629_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut473.push_back(ctx.genrate_lut(lut473idx1));
    flut473.push_back(lut473idx1);
    auto fvec473 = [flut473](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut473[i](I));
        return ret;
    };

    std::cerr << "\rLUT473   ";
    Ciphertext gin473 = 1 * gout463[0] + 2 * gout413[1];
    std::vector<Ciphertext> gout473 = ctx.eval_lut_amortized(&gin473, lut473);

    std::vector<RotationPoly> lut474;
    std::vector<long (*)(long)> flut474;
    auto lut474idx0 = [](long I) -> long {
        /* GATE 94 (LUT2 _2858_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut474.push_back(ctx.genrate_lut(lut474idx0));
    flut474.push_back(lut474idx0);
    auto lut474idx1 = [](long I) -> long {
        /* GATE 413 (LUT2 _3177_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut474.push_back(ctx.genrate_lut(lut474idx1));
    flut474.push_back(lut474idx1);
    auto fvec474 = [flut474](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut474[i](I));
        return ret;
    };

    std::cerr << "\rLUT474   ";
    Ciphertext gin474 = 1 * gout405[0] + 2 * gout456[0];
    std::vector<Ciphertext> gout474 = ctx.eval_lut_amortized(&gin474, lut474);

    std::vector<RotationPoly> lut475;
    std::vector<long (*)(long)> flut475;
    auto lut475idx0 = [](long I) -> long {
        /* GATE 201 (LUT2 _2965_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut475.push_back(ctx.genrate_lut(lut475idx0));
    flut475.push_back(lut475idx0);
    auto lut475idx1 = [](long I) -> long {
        /* GATE 307 (LUT2 _3071_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut475.push_back(ctx.genrate_lut(lut475idx1));
    flut475.push_back(lut475idx1);
    auto fvec475 = [flut475](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut475[i](I));
        return ret;
    };

    std::cerr << "\rLUT475   ";
    Ciphertext gin475 = 1 * gout440[0] + 2 * gout469[1];
    std::vector<Ciphertext> gout475 = ctx.eval_lut_amortized(&gin475, lut475);

    std::vector<RotationPoly> lut476;
    std::vector<long (*)(long)> flut476;
    auto lut476idx0 = [](long I) -> long {
        /* GATE 862 (LUT2 _3626_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut476.push_back(ctx.genrate_lut(lut476idx0));
    flut476.push_back(lut476idx0);
    auto lut476idx1 = [](long I) -> long {
        /* GATE 773 (LUT2 _3537_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut476.push_back(ctx.genrate_lut(lut476idx1));
    flut476.push_back(lut476idx1);
    auto fvec476 = [flut476](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut476[i](I));
        return ret;
    };

    std::cerr << "\rLUT476   ";
    Ciphertext gin476 = 1 * gout471[0] + 2 * gout452[1];
    std::vector<Ciphertext> gout476 = ctx.eval_lut_amortized(&gin476, lut476);

    std::vector<RotationPoly> lut477;
    std::vector<long (*)(long)> flut477;
    auto lut477idx0 = [](long I) -> long {
        /* GATE 310 (LUT2 _3074_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut477.push_back(ctx.genrate_lut(lut477idx0));
    flut477.push_back(lut477idx0);
    auto fvec477 = [flut477](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut477[i](I));
        return ret;
    };

    std::cerr << "\rLUT477   ";
    Ciphertext gin477 = 1 * gout469[0] + 2 * gout422[0];
    std::vector<Ciphertext> gout477 = ctx.eval_lut_amortized(&gin477, lut477);

    std::vector<RotationPoly> lut478;
    std::vector<long (*)(long)> flut478;
    auto lut478idx0 = [](long I) -> long {
        /* GATE 661 (LUT2 _3425_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut478.push_back(ctx.genrate_lut(lut478idx0));
    flut478.push_back(lut478idx0);
    auto lut478idx1 = [](long I) -> long {
        /* GATE 548 (LUT2 _3312_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut478.push_back(ctx.genrate_lut(lut478idx1));
    flut478.push_back(lut478idx1);
    auto fvec478 = [flut478](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut478[i](I));
        return ret;
    };

    std::cerr << "\rLUT478   ";
    Ciphertext gin478 = 1 * gout460[1] + 2 * gout423[0];
    std::vector<Ciphertext> gout478 = ctx.eval_lut_amortized(&gin478, lut478);

    std::vector<RotationPoly> lut479;
    std::vector<long (*)(long)> flut479;
    auto lut479idx0 = [](long I) -> long {
        /* GATE 433 (LUT2 _3197_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut479.push_back(ctx.genrate_lut(lut479idx0));
    flut479.push_back(lut479idx0);
    auto lut479idx1 = [](long I) -> long {
        /* GATE 546 (LUT2 _3310_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut479.push_back(ctx.genrate_lut(lut479idx1));
    flut479.push_back(lut479idx1);
    auto fvec479 = [flut479](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut479[i](I));
        return ret;
    };

    std::cerr << "\rLUT479   ";
    Ciphertext gin479 = 1 * gout461[1] + 2 * gout414[0];
    std::vector<Ciphertext> gout479 = ctx.eval_lut_amortized(&gin479, lut479);

    std::vector<RotationPoly> lut480;
    std::vector<long (*)(long)> flut480;
    auto lut480idx0 = [](long I) -> long {
        /* GATE 516 (LUT2 _3280_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut480.push_back(ctx.genrate_lut(lut480idx0));
    flut480.push_back(lut480idx0);
    auto lut480idx1 = [](long I) -> long {
        /* GATE 643 (LUT2 _3407_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut480.push_back(ctx.genrate_lut(lut480idx1));
    flut480.push_back(lut480idx1);
    auto fvec480 = [flut480](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut480[i](I));
        return ret;
    };

    std::cerr << "\rLUT480   ";
    Ciphertext gin480 = 1 * gout36[0] + 2 * gout462[1];
    std::vector<Ciphertext> gout480 = ctx.eval_lut_amortized(&gin480, lut480);

    std::vector<RotationPoly> lut481;
    std::vector<long (*)(long)> flut481;
    auto lut481idx0 = [](long I) -> long {
        /* GATE 200 (LUT2 _2964_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut481.push_back(ctx.genrate_lut(lut481idx0));
    flut481.push_back(lut481idx0);
    auto lut481idx1 = [](long I) -> long {
        /* GATE 306 (LUT2 _3070_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut481.push_back(ctx.genrate_lut(lut481idx1));
    flut481.push_back(lut481idx1);
    auto fvec481 = [flut481](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut481[i](I));
        return ret;
    };

    std::cerr << "\rLUT481   ";
    Ciphertext gin481 = 1 * gout475[0] + 2 * gout433[1];
    std::vector<Ciphertext> gout481 = ctx.eval_lut_amortized(&gin481, lut481);

    std::vector<RotationPoly> lut482;
    std::vector<long (*)(long)> flut482;
    auto lut482idx0 = [](long I) -> long {
        /* GATE 429 (LUT2 _3193_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut482.push_back(ctx.genrate_lut(lut482idx0));
    flut482.push_back(lut482idx0);
    auto lut482idx1 = [](long I) -> long {
        /* GATE 542 (LUT2 _3306_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut482.push_back(ctx.genrate_lut(lut482idx1));
    flut482.push_back(lut482idx1);
    auto fvec482 = [flut482](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut482[i](I));
        return ret;
    };

    std::cerr << "\rLUT482   ";
    Ciphertext gin482 = 1 * gout468[0] + 2 * gout479[0];
    std::vector<Ciphertext> gout482 = ctx.eval_lut_amortized(&gin482, lut482);

    std::vector<RotationPoly> lut483;
    std::vector<long (*)(long)> flut483;
    auto lut483idx0 = [](long I) -> long {
        /* GATE 427 (LUT2 _3191_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut483.push_back(ctx.genrate_lut(lut483idx0));
    flut483.push_back(lut483idx0);
    auto lut483idx1 = [](long I) -> long {
        /* GATE 309 (LUT2 _3073_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut483.push_back(ctx.genrate_lut(lut483idx1));
    flut483.push_back(lut483idx1);
    auto fvec483 = [flut483](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut483[i](I));
        return ret;
    };

    std::cerr << "\rLUT483   ";
    Ciphertext gin483 = 1 * gout477[0] + 2 * gout464[1];
    std::vector<Ciphertext> gout483 = ctx.eval_lut_amortized(&gin483, lut483);

    std::vector<RotationPoly> lut484;
    std::vector<long (*)(long)> flut484;
    auto lut484idx0 = [](long I) -> long {
        /* GATE 528 (LUT2 _3292_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut484.push_back(ctx.genrate_lut(lut484idx0));
    flut484.push_back(lut484idx0);
    auto lut484idx1 = [](long I) -> long {
        /* GATE 396 (LUT2 _3160_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut484.push_back(ctx.genrate_lut(lut484idx1));
    flut484.push_back(lut484idx1);
    auto fvec484 = [flut484](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut484[i](I));
        return ret;
    };

    std::cerr << "\rLUT484   ";
    Ciphertext gin484 = 1 * gout200[0] + 2 * gout470[1];
    std::vector<Ciphertext> gout484 = ctx.eval_lut_amortized(&gin484, lut484);

    std::vector<RotationPoly> lut485;
    std::vector<long (*)(long)> flut485;
    auto lut485idx0 = [](long I) -> long {
        /* GATE 848 (LUT2 _3612_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut485.push_back(ctx.genrate_lut(lut485idx0));
    flut485.push_back(lut485idx0);
    auto fvec485 = [flut485](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut485[i](I));
        return ret;
    };

    std::cerr << "\rLUT485   ";
    Ciphertext gin485 = 1 * gout472[0] + 2 * gout467[1];
    std::vector<Ciphertext> gout485 = ctx.eval_lut_amortized(&gin485, lut485);

    std::vector<RotationPoly> lut486;
    std::vector<long (*)(long)> flut486;
    auto lut486idx0 = [](long I) -> long {
        /* GATE 864 (LUT2 _3628_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut486.push_back(ctx.genrate_lut(lut486idx0));
    flut486.push_back(lut486idx0);
    auto lut486idx1 = [](long I) -> long {
        /* GATE 905 (LUT2 _3669_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut486.push_back(ctx.genrate_lut(lut486idx1));
    flut486.push_back(lut486idx1);
    auto fvec486 = [flut486](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut486[i](I));
        return ret;
    };

    std::cerr << "\rLUT486   ";
    Ciphertext gin486 = 1 * gout473[1] + 2 * gout419[0];
    std::vector<Ciphertext> gout486 = ctx.eval_lut_amortized(&gin486, lut486);

    std::vector<RotationPoly> lut487;
    std::vector<long (*)(long)> flut487;
    auto lut487idx0 = [](long I) -> long {
        /* GATE 545 (LUT2 _3309_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut487.push_back(ctx.genrate_lut(lut487idx0));
    flut487.push_back(lut487idx0);
    auto fvec487 = [flut487](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut487[i](I));
        return ret;
    };

    std::cerr << "\rLUT487   ";
    Ciphertext gin487 = 1 * gout479[1] + 2 * gout461[0];
    std::vector<Ciphertext> gout487 = ctx.eval_lut_amortized(&gin487, lut487);

    std::vector<RotationPoly> lut488;
    std::vector<long (*)(long)> flut488;
    auto lut488idx0 = [](long I) -> long {
        /* GATE 861 (LUT2 _3625_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut488.push_back(ctx.genrate_lut(lut488idx0));
    flut488.push_back(lut488idx0);
    auto fvec488 = [flut488](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut488[i](I));
        return ret;
    };

    std::cerr << "\rLUT488   ";
    Ciphertext gin488 = 1 * gout476[0] + 2 * gout471[1];
    std::vector<Ciphertext> gout488 = ctx.eval_lut_amortized(&gin488, lut488);

    std::vector<RotationPoly> lut489;
    std::vector<long (*)(long)> flut489;
    auto lut489idx0 = [](long I) -> long {
        /* GATE 541 (LUT2 _3305_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut489.push_back(ctx.genrate_lut(lut489idx0));
    flut489.push_back(lut489idx0);
    auto lut489idx1 = [](long I) -> long {
        /* GATE 428 (LUT2 _3192_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut489.push_back(ctx.genrate_lut(lut489idx1));
    flut489.push_back(lut489idx1);
    auto fvec489 = [flut489](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut489[i](I));
        return ret;
    };

    std::cerr << "\rLUT489   ";
    Ciphertext gin489 = 1 * gout482[0] + 2 * gout480[0];
    std::vector<Ciphertext> gout489 = ctx.eval_lut_amortized(&gin489, lut489);

    std::vector<RotationPoly> lut490;
    std::vector<long (*)(long)> flut490;
    auto lut490idx0 = [](long I) -> long {
        /* GATE 642 (LUT2 _3406_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut490.push_back(ctx.genrate_lut(lut490idx0));
    flut490.push_back(lut490idx0);
    auto fvec490 = [flut490](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut490[i](I));
        return ret;
    };

    std::cerr << "\rLUT490   ";
    Ciphertext gin490 = 1 * gout480[1] + 2 * gout462[0];
    std::vector<Ciphertext> gout490 = ctx.eval_lut_amortized(&gin490, lut490);

    std::vector<RotationPoly> lut491;
    std::vector<long (*)(long)> flut491;
    auto lut491idx0 = [](long I) -> long {
        /* GATE 93 (LUT2 _2857_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut491.push_back(ctx.genrate_lut(lut491idx0));
    flut491.push_back(lut491idx0);
    auto lut491idx1 = [](long I) -> long {
        /* GATE 412 (LUT2 _3176_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut491.push_back(ctx.genrate_lut(lut491idx1));
    flut491.push_back(lut491idx1);
    auto fvec491 = [flut491](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut491[i](I));
        return ret;
    };

    std::cerr << "\rLUT491   ";
    Ciphertext gin491 = 1 * gout474[0] + 2 * gout238[0];
    std::vector<Ciphertext> gout491 = ctx.eval_lut_amortized(&gin491, lut491);

    std::vector<RotationPoly> lut492;
    std::vector<long (*)(long)> flut492;
    auto lut492idx0 = [](long I) -> long {
        /* GATE 660 (LUT2 _3424_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut492.push_back(ctx.genrate_lut(lut492idx0));
    flut492.push_back(lut492idx0);
    auto fvec492 = [flut492](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut492[i](I));
        return ret;
    };

    std::cerr << "\rLUT492   ";
    Ciphertext gin492 = 1 * gout478[0] + 2 * gout460[0];
    std::vector<Ciphertext> gout492 = ctx.eval_lut_amortized(&gin492, lut492);

    std::vector<RotationPoly> lut493;
    std::vector<long (*)(long)> flut493;
    auto lut493idx0 = [](long I) -> long {
        /* GATE 527 (LUT2 _3291_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut493.push_back(ctx.genrate_lut(lut493idx0));
    flut493.push_back(lut493idx0);
    auto fvec493 = [flut493](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut493[i](I));
        return ret;
    };

    std::cerr << "\rLUT493   ";
    Ciphertext gin493 = 1 * gout484[0] + 2 * gout470[0];
    std::vector<Ciphertext> gout493 = ctx.eval_lut_amortized(&gin493, lut493);

    std::vector<RotationPoly> lut494;
    std::vector<long (*)(long)> flut494;
    auto lut494idx0 = [](long I) -> long {
        /* GATE 196 (LUT2 _2960_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut494.push_back(ctx.genrate_lut(lut494idx0));
    flut494.push_back(lut494idx0);
    auto lut494idx1 = [](long I) -> long {
        /* GATE 302 (LUT2 _3066_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut494.push_back(ctx.genrate_lut(lut494idx1));
    flut494.push_back(lut494idx1);
    auto fvec494 = [flut494](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut494[i](I));
        return ret;
    };

    std::cerr << "\rLUT494   ";
    Ciphertext gin494 = 1 * gout466[0] + 2 * gout481[0];
    std::vector<Ciphertext> gout494 = ctx.eval_lut_amortized(&gin494, lut494);

    std::vector<RotationPoly> lut495;
    std::vector<long (*)(long)> flut495;
    auto lut495idx0 = [](long I) -> long {
        /* GATE 195 (LUT2 _2959_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut495.push_back(ctx.genrate_lut(lut495idx0));
    flut495.push_back(lut495idx0);
    auto lut495idx1 = [](long I) -> long {
        /* GATE 414 (LUT2 _3178_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut495.push_back(ctx.genrate_lut(lut495idx1));
    flut495.push_back(lut495idx1);
    auto fvec495 = [flut495](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut495[i](I));
        return ret;
    };

    std::cerr << "\rLUT495   ";
    Ciphertext gin495 = 1 * gout494[0] + 2 * gout415[0];
    std::vector<Ciphertext> gout495 = ctx.eval_lut_amortized(&gin495, lut495);

    std::vector<RotationPoly> lut496;
    std::vector<long (*)(long)> flut496;
    auto lut496idx0 = [](long I) -> long {
        /* GATE 540 (LUT2 _3304_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut496.push_back(ctx.genrate_lut(lut496idx0));
    flut496.push_back(lut496idx0);
    auto fvec496 = [flut496](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut496[i](I));
        return ret;
    };

    std::cerr << "\rLUT496   ";
    Ciphertext gin496 = 1 * gout489[0] + 2 * gout482[1];
    std::vector<Ciphertext> gout496 = ctx.eval_lut_amortized(&gin496, lut496);

    std::vector<RotationPoly> lut497;
    std::vector<long (*)(long)> flut497;
    auto lut497idx0 = [](long I) -> long {
        /* GATE 305 (LUT2 _3069_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut497.push_back(ctx.genrate_lut(lut497idx0));
    flut497.push_back(lut497idx0);
    auto fvec497 = [flut497](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut497[i](I));
        return ret;
    };

    std::cerr << "\rLUT497   ";
    Ciphertext gin497 = 1 * gout481[1] + 2 * gout475[1];
    std::vector<Ciphertext> gout497 = ctx.eval_lut_amortized(&gin497, lut497);

    std::vector<RotationPoly> lut498;
    std::vector<long (*)(long)> flut498;
    auto lut498idx0 = [](long I) -> long {
        /* GATE 194 (LUT2 _2958_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut498.push_back(ctx.genrate_lut(lut498idx0));
    flut498.push_back(lut498idx0);
    auto fvec498 = [flut498](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut498[i](I));
        return ret;
    };

    std::cerr << "\rLUT498   ";
    Ciphertext gin498 = 1 * gout495[0] + 2 * gout494[1];
    std::vector<Ciphertext> gout498 = ctx.eval_lut_amortized(&gin498, lut498);

    std::vector<RotationPoly> lut499;
    std::vector<long (*)(long)> flut499;
    auto lut499idx0 = [](long I) -> long {
        /* GATE 657 (LUT2 _3421_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut499.push_back(ctx.genrate_lut(lut499idx0));
    flut499.push_back(lut499idx0);
    auto lut499idx1 = [](long I) -> long {
        /* GATE 544 (LUT2 _3308_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut499.push_back(ctx.genrate_lut(lut499idx1));
    flut499.push_back(lut499idx1);
    auto fvec499 = [flut499](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut499[i](I));
        return ret;
    };

    std::cerr << "\rLUT499   ";
    Ciphertext gin499 = 1 * gout487[0] + 2 * gout478[1];
    std::vector<Ciphertext> gout499 = ctx.eval_lut_amortized(&gin499, lut499);

    std::vector<RotationPoly> lut500;
    std::vector<long (*)(long)> flut500;
    auto lut500idx0 = [](long I) -> long {
        /* GATE 904 (LUT2 _3668_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut500.push_back(ctx.genrate_lut(lut500idx0));
    flut500.push_back(lut500idx0);
    auto fvec500 = [flut500](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut500[i](I));
        return ret;
    };

    std::cerr << "\rLUT500   ";
    Ciphertext gin500 = 1 * gout486[1] + 2 * gout473[0];
    std::vector<Ciphertext> gout500 = ctx.eval_lut_amortized(&gin500, lut500);

    std::vector<RotationPoly> lut501;
    std::vector<long (*)(long)> flut501;
    auto lut501idx0 = [](long I) -> long {
        /* GATE 426 (LUT2 _3190_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut501.push_back(ctx.genrate_lut(lut501idx0));
    flut501.push_back(lut501idx0);
    auto lut501idx1 = [](long I) -> long {
        /* GATE 308 (LUT2 _3072_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut501.push_back(ctx.genrate_lut(lut501idx1));
    flut501.push_back(lut501idx1);
    auto fvec501 = [flut501](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut501[i](I));
        return ret;
    };

    std::cerr << "\rLUT501   ";
    Ciphertext gin501 = 1 * gout483[1] + 2 * gout484[1];
    std::vector<Ciphertext> gout501 = ctx.eval_lut_amortized(&gin501, lut501);

    std::vector<RotationPoly> lut502;
    std::vector<long (*)(long)> flut502;
    auto lut502idx0 = [](long I) -> long {
        /* GATE 659 (LUT2 _3423_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut502.push_back(ctx.genrate_lut(lut502idx0));
    flut502.push_back(lut502idx0);
    auto lut502idx1 = [](long I) -> long {
        /* GATE 772 (LUT2 _3536_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut502.push_back(ctx.genrate_lut(lut502idx1));
    flut502.push_back(lut502idx1);
    auto fvec502 = [flut502](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut502[i](I));
        return ret;
    };

    std::cerr << "\rLUT502   ";
    Ciphertext gin502 = 1 * gout492[0] + 2 * gout445[1];
    std::vector<Ciphertext> gout502 = ctx.eval_lut_amortized(&gin502, lut502);

    std::vector<RotationPoly> lut503;
    std::vector<long (*)(long)> flut503;
    auto lut503idx0 = [](long I) -> long {
        /* GATE 860 (LUT2 _3624_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut503.push_back(ctx.genrate_lut(lut503idx0));
    flut503.push_back(lut503idx0);
    auto lut503idx1 = [](long I) -> long {
        /* GATE 902 (LUT2 _3666_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut503.push_back(ctx.genrate_lut(lut503idx1));
    flut503.push_back(lut503idx1);
    auto fvec503 = [flut503](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut503[i](I));
        return ret;
    };

    std::cerr << "\rLUT503   ";
    Ciphertext gin503 = 1 * gout488[0] + 2 * gout486[0];
    std::vector<Ciphertext> gout503 = ctx.eval_lut_amortized(&gin503, lut503);

    std::vector<RotationPoly> lut504;
    std::vector<long (*)(long)> flut504;
    auto lut504idx0 = [](long I) -> long {
        /* GATE 425 (LUT2 _3189_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut504.push_back(ctx.genrate_lut(lut504idx0));
    flut504.push_back(lut504idx0);
    auto fvec504 = [flut504](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut504[i](I));
        return ret;
    };

    std::cerr << "\rLUT504   ";
    Ciphertext gin504 = 1 * gout501[0] + 2 * gout483[0];
    std::vector<Ciphertext> gout504 = ctx.eval_lut_amortized(&gin504, lut504);

    std::vector<RotationPoly> lut505;
    std::vector<long (*)(long)> flut505;
    auto lut505idx0 = [](long I) -> long {
        /* GATE 543 (LUT2 _3307_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut505.push_back(ctx.genrate_lut(lut505idx0));
    flut505.push_back(lut505idx0);
    auto lut505idx1 = [](long I) -> long {
        /* GATE 656 (LUT2 _3420_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut505.push_back(ctx.genrate_lut(lut505idx1));
    flut505.push_back(lut505idx1);
    auto fvec505 = [flut505](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut505[i](I));
        return ret;
    };

    std::cerr << "\rLUT505   ";
    Ciphertext gin505 = 1 * gout499[1] + 2 * gout457[1];
    std::vector<Ciphertext> gout505 = ctx.eval_lut_amortized(&gin505, lut505);

    std::vector<RotationPoly> lut506;
    std::vector<long (*)(long)> flut506;
    auto lut506idx0 = [](long I) -> long {
        /* GATE 859 (LUT2 _3623_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut506.push_back(ctx.genrate_lut(lut506idx0));
    flut506.push_back(lut506idx0);
    auto lut506idx1 = [](long I) -> long {
        /* GATE 901 (LUT2 _3665_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut506.push_back(ctx.genrate_lut(lut506idx1));
    flut506.push_back(lut506idx1);
    auto fvec506 = [flut506](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut506[i](I));
        return ret;
    };

    std::cerr << "\rLUT506   ";
    Ciphertext gin506 = 1 * gout503[0] + 2 * gout454[0];
    std::vector<Ciphertext> gout506 = ctx.eval_lut_amortized(&gin506, lut506);

    std::vector<RotationPoly> lut507;
    std::vector<long (*)(long)> flut507;
    auto lut507idx0 = [](long I) -> long {
        /* GATE 411 (LUT2 _3175_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut507.push_back(ctx.genrate_lut(lut507idx0));
    flut507.push_back(lut507idx0);
    auto fvec507 = [flut507](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut507[i](I));
        return ret;
    };

    std::cerr << "\rLUT507   ";
    Ciphertext gin507 = 1 * gout491[1] + 2 * gout474[1];
    std::vector<Ciphertext> gout507 = ctx.eval_lut_amortized(&gin507, lut507);

    std::vector<RotationPoly> lut508;
    std::vector<long (*)(long)> flut508;
    auto lut508idx0 = [](long I) -> long {
        /* GATE 539 (LUT2 _3303_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut508.push_back(ctx.genrate_lut(lut508idx0));
    flut508.push_back(lut508idx0);
    auto lut508idx1 = [](long I) -> long {
        /* GATE 652 (LUT2 _3416_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut508.push_back(ctx.genrate_lut(lut508idx1));
    flut508.push_back(lut508idx1);
    auto fvec508 = [flut508](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut508[i](I));
        return ret;
    };

    std::cerr << "\rLUT508   ";
    Ciphertext gin508 = 1 * gout496[0] + 2 * gout505[0];
    std::vector<Ciphertext> gout508 = ctx.eval_lut_amortized(&gin508, lut508);

    std::vector<RotationPoly> lut509;
    std::vector<long (*)(long)> flut509;
    auto lut509idx0 = [](long I) -> long {
        /* GATE 903 (LUT2 _3667_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut509.push_back(ctx.genrate_lut(lut509idx0));
    flut509.push_back(lut509idx0);
    auto lut509idx1 = [](long I) -> long {
        /* GATE 921 (LUT2 _3685_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut509.push_back(ctx.genrate_lut(lut509idx1));
    flut509.push_back(lut509idx1);
    auto fvec509 = [flut509](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut509[i](I));
        return ret;
    };

    std::cerr << "\rLUT509   ";
    Ciphertext gin509 = 1 * gout500[0] + 2 * gout455[1];
    std::vector<Ciphertext> gout509 = ctx.eval_lut_amortized(&gin509, lut509);

    std::vector<RotationPoly> lut510;
    std::vector<long (*)(long)> flut510;
    auto lut510idx0 = [](long I) -> long {
        /* GATE 655 (LUT2 _3419_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut510.push_back(ctx.genrate_lut(lut510idx0));
    flut510.push_back(lut510idx0);
    auto fvec510 = [flut510](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut510[i](I));
        return ret;
    };

    std::cerr << "\rLUT510   ";
    Ciphertext gin510 = 1 * gout505[1] + 2 * gout499[0];
    std::vector<Ciphertext> gout510 = ctx.eval_lut_amortized(&gin510, lut510);

    std::vector<RotationPoly> lut511;
    std::vector<long (*)(long)> flut511;
    auto lut511idx0 = [](long I) -> long {
        /* GATE 410 (LUT2 _3174_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut511.push_back(ctx.genrate_lut(lut511idx0));
    flut511.push_back(lut511idx0);
    auto lut511idx1 = [](long I) -> long {
        /* GATE 925 (LUT2 _3689_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut511.push_back(ctx.genrate_lut(lut511idx1));
    flut511.push_back(lut511idx1);
    auto fvec511 = [flut511](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut511[i](I));
        return ret;
    };

    std::cerr << "\rLUT511   ";
    Ciphertext gin511 = 1 * gout507[0] + 2 * gout495[1];
    std::vector<Ciphertext> gout511 = ctx.eval_lut_amortized(&gin511, lut511);

    std::vector<RotationPoly> lut512;
    std::vector<long (*)(long)> flut512;
    auto lut512idx0 = [](long I) -> long {
        /* GATE 900 (LUT2 _3664_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut512.push_back(ctx.genrate_lut(lut512idx0));
    flut512.push_back(lut512idx0);
    auto fvec512 = [flut512](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut512[i](I));
        return ret;
    };

    std::cerr << "\rLUT512   ";
    Ciphertext gin512 = 1 * gout506[1] + 2 * gout503[1];
    std::vector<Ciphertext> gout512 = ctx.eval_lut_amortized(&gin512, lut512);

    std::vector<RotationPoly> lut513;
    std::vector<long (*)(long)> flut513;
    auto lut513idx0 = [](long I) -> long {
        /* GATE 304 (LUT2 _3068_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut513.push_back(ctx.genrate_lut(lut513idx0));
    flut513.push_back(lut513idx0);
    auto lut513idx1 = [](long I) -> long {
        /* GATE 422 (LUT2 _3186_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut513.push_back(ctx.genrate_lut(lut513idx1));
    flut513.push_back(lut513idx1);
    auto fvec513 = [flut513](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut513[i](I));
        return ret;
    };

    std::cerr << "\rLUT513   ";
    Ciphertext gin513 = 1 * gout497[0] + 2 * gout501[1];
    std::vector<Ciphertext> gout513 = ctx.eval_lut_amortized(&gin513, lut513);

    std::vector<RotationPoly> lut514;
    std::vector<long (*)(long)> flut514;
    auto lut514idx0 = [](long I) -> long {
        /* GATE 658 (LUT2 _3422_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut514.push_back(ctx.genrate_lut(lut514idx0));
    flut514.push_back(lut514idx0);
    auto lut514idx1 = [](long I) -> long {
        /* GATE 771 (LUT2 _3535_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut514.push_back(ctx.genrate_lut(lut514idx1));
    flut514.push_back(lut514idx1);
    auto fvec514 = [flut514](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut514[i](I));
        return ret;
    };

    std::cerr << "\rLUT514   ";
    Ciphertext gin514 = 1 * gout502[0] + 2 * gout472[1];
    std::vector<Ciphertext> gout514 = ctx.eval_lut_amortized(&gin514, lut514);

    std::vector<RotationPoly> lut515;
    std::vector<long (*)(long)> flut515;
    auto lut515idx0 = [](long I) -> long {
        /* GATE 654 (LUT2 _3418_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut515.push_back(ctx.genrate_lut(lut515idx0));
    flut515.push_back(lut515idx0);
    auto lut515idx1 = [](long I) -> long {
        /* GATE 767 (LUT2 _3531_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut515.push_back(ctx.genrate_lut(lut515idx1));
    flut515.push_back(lut515idx1);
    auto fvec515 = [flut515](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut515[i](I));
        return ret;
    };

    std::cerr << "\rLUT515   ";
    Ciphertext gin515 = 1 * gout510[0] + 2 * gout514[0];
    std::vector<Ciphertext> gout515 = ctx.eval_lut_amortized(&gin515, lut515);

    std::vector<RotationPoly> lut516;
    std::vector<long (*)(long)> flut516;
    auto lut516idx0 = [](long I) -> long {
        /* GATE 538 (LUT2 _3302_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut516.push_back(ctx.genrate_lut(lut516idx0));
    flut516.push_back(lut516idx0);
    auto lut516idx1 = [](long I) -> long {
        /* GATE 651 (LUT2 _3415_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut516.push_back(ctx.genrate_lut(lut516idx1));
    flut516.push_back(lut516idx1);
    auto fvec516 = [flut516](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut516[i](I));
        return ret;
    };

    std::cerr << "\rLUT516   ";
    Ciphertext gin516 = 1 * gout508[0] + 2 * gout490[0];
    std::vector<Ciphertext> gout516 = ctx.eval_lut_amortized(&gin516, lut516);

    std::vector<RotationPoly> lut517;
    std::vector<long (*)(long)> flut517;
    auto lut517idx0 = [](long I) -> long {
        /* GATE 920 (LUT2 _3684_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut517.push_back(ctx.genrate_lut(lut517idx0));
    flut517.push_back(lut517idx0);
    auto fvec517 = [flut517](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut517[i](I));
        return ret;
    };

    std::cerr << "\rLUT517   ";
    Ciphertext gin517 = 1 * gout509[1] + 2 * gout459[0];
    std::vector<Ciphertext> gout517 = ctx.eval_lut_amortized(&gin517, lut517);

    std::vector<RotationPoly> lut518;
    std::vector<long (*)(long)> flut518;
    auto lut518idx0 = [](long I) -> long {
        /* GATE 424 (LUT2 _3188_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut518.push_back(ctx.genrate_lut(lut518idx0));
    flut518.push_back(lut518idx0);
    auto lut518idx1 = [](long I) -> long {
        /* GATE 537 (LUT2 _3301_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut518.push_back(ctx.genrate_lut(lut518idx1));
    flut518.push_back(lut518idx1);
    auto fvec518 = [flut518](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut518[i](I));
        return ret;
    };

    std::cerr << "\rLUT518   ";
    Ciphertext gin518 = 1 * gout504[0] + 2 * gout489[1];
    std::vector<Ciphertext> gout518 = ctx.eval_lut_amortized(&gin518, lut518);

    std::vector<RotationPoly> lut519;
    std::vector<long (*)(long)> flut519;
    auto lut519idx0 = [](long I) -> long {
        /* GATE 766 (LUT2 _3530_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut519.push_back(ctx.genrate_lut(lut519idx0));
    flut519.push_back(lut519idx0);
    auto lut519idx1 = [](long I) -> long {
        /* GATE 653 (LUT2 _3417_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut519.push_back(ctx.genrate_lut(lut519idx1));
    flut519.push_back(lut519idx1);
    auto fvec519 = [flut519](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut519[i](I));
        return ret;
    };

    std::cerr << "\rLUT519   ";
    Ciphertext gin519 = 1 * gout515[0] + 2 * gout465[0];
    std::vector<Ciphertext> gout519 = ctx.eval_lut_amortized(&gin519, lut519);

    std::vector<RotationPoly> lut520;
    std::vector<long (*)(long)> flut520;
    auto lut520idx0 = [](long I) -> long {
        /* GATE 770 (LUT2 _3534_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut520.push_back(ctx.genrate_lut(lut520idx0));
    flut520.push_back(lut520idx0);
    auto fvec520 = [flut520](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut520[i](I));
        return ret;
    };

    std::cerr << "\rLUT520   ";
    Ciphertext gin520 = 1 * gout514[1] + 2 * gout502[1];
    std::vector<Ciphertext> gout520 = ctx.eval_lut_amortized(&gin520, lut520);

    std::vector<RotationPoly> lut521;
    std::vector<long (*)(long)> flut521;
    auto lut521idx0 = [](long I) -> long {
        /* GATE 919 (LUT2 _3683_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut521.push_back(ctx.genrate_lut(lut521idx0));
    flut521.push_back(lut521idx0);
    auto lut521idx1 = [](long I) -> long {
        /* GATE 899 (LUT2 _3663_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut521.push_back(ctx.genrate_lut(lut521idx1));
    flut521.push_back(lut521idx1);
    auto fvec521 = [flut521](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut521[i](I));
        return ret;
    };

    std::cerr << "\rLUT521   ";
    Ciphertext gin521 = 1 * gout512[0] + 2 * gout509[0];
    std::vector<Ciphertext> gout521 = ctx.eval_lut_amortized(&gin521, lut521);

    std::vector<RotationPoly> lut522;
    std::vector<long (*)(long)> flut522;
    auto lut522idx0 = [](long I) -> long {
        /* GATE 303 (LUT2 _3067_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut522.push_back(ctx.genrate_lut(lut522idx0));
    flut522.push_back(lut522idx0);
    auto lut522idx1 = [](long I) -> long {
        /* GATE 421 (LUT2 _3185_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut522.push_back(ctx.genrate_lut(lut522idx1));
    flut522.push_back(lut522idx1);
    auto fvec522 = [flut522](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut522[i](I));
        return ret;
    };

    std::cerr << "\rLUT522   ";
    Ciphertext gin522 = 1 * gout513[0] + 2 * gout444[0];
    std::vector<Ciphertext> gout522 = ctx.eval_lut_amortized(&gin522, lut522);

    std::vector<RotationPoly> lut523;
    std::vector<long (*)(long)> flut523;
    auto lut523idx0 = [](long I) -> long {
        /* GATE 650 (LUT2 _3414_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut523.push_back(ctx.genrate_lut(lut523idx0));
    flut523.push_back(lut523idx0);
    auto fvec523 = [flut523](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut523[i](I));
        return ret;
    };

    std::cerr << "\rLUT523   ";
    Ciphertext gin523 = 1 * gout516[1] + 2 * gout508[1];
    std::vector<Ciphertext> gout523 = ctx.eval_lut_amortized(&gin523, lut523);

    std::vector<RotationPoly> lut524;
    std::vector<long (*)(long)> flut524;
    auto lut524idx0 = [](long I) -> long {
        /* GATE 765 (LUT2 _3529_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut524.push_back(ctx.genrate_lut(lut524idx0));
    flut524.push_back(lut524idx0);
    auto fvec524 = [flut524](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut524[i](I));
        return ret;
    };

    std::cerr << "\rLUT524   ";
    Ciphertext gin524 = 1 * gout519[0] + 2 * gout515[1];
    std::vector<Ciphertext> gout524 = ctx.eval_lut_amortized(&gin524, lut524);

    std::vector<RotationPoly> lut525;
    std::vector<long (*)(long)> flut525;
    auto lut525idx0 = [](long I) -> long {
        /* GATE 536 (LUT2 _3300_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut525.push_back(ctx.genrate_lut(lut525idx0));
    flut525.push_back(lut525idx0);
    auto lut525idx1 = [](long I) -> long {
        /* GATE 423 (LUT2 _3187_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut525.push_back(ctx.genrate_lut(lut525idx1));
    flut525.push_back(lut525idx1);
    auto fvec525 = [flut525](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut525[i](I));
        return ret;
    };

    std::cerr << "\rLUT525   ";
    Ciphertext gin525 = 1 * gout518[0] + 2 * gout493[0];
    std::vector<Ciphertext> gout525 = ctx.eval_lut_amortized(&gin525, lut525);

    std::vector<RotationPoly> lut526;
    std::vector<long (*)(long)> flut526;
    auto lut526idx0 = [](long I) -> long {
        /* GATE 769 (LUT2 _3533_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut526.push_back(ctx.genrate_lut(lut526idx0));
    flut526.push_back(lut526idx0);
    auto lut526idx1 = [](long I) -> long {
        /* GATE 858 (LUT2 _3622_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut526.push_back(ctx.genrate_lut(lut526idx1));
    flut526.push_back(lut526idx1);
    auto fvec526 = [flut526](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut526[i](I));
        return ret;
    };

    std::cerr << "\rLUT526   ";
    Ciphertext gin526 = 1 * gout520[0] + 2 * gout476[1];
    std::vector<Ciphertext> gout526 = ctx.eval_lut_amortized(&gin526, lut526);

    std::vector<RotationPoly> lut527;
    std::vector<long (*)(long)> flut527;
    auto lut527idx0 = [](long I) -> long {
        /* GATE 649 (LUT2 _3413_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut527.push_back(ctx.genrate_lut(lut527idx0));
    flut527.push_back(lut527idx0);
    auto lut527idx1 = [](long I) -> long {
        /* GATE 763 (LUT2 _3527_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut527.push_back(ctx.genrate_lut(lut527idx1));
    flut527.push_back(lut527idx1);
    auto fvec527 = [flut527](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut527[i](I));
        return ret;
    };

    std::cerr << "\rLUT527   ";
    Ciphertext gin527 = 1 * gout523[0] + 2 * gout519[1];
    std::vector<Ciphertext> gout527 = ctx.eval_lut_amortized(&gin527, lut527);

    std::vector<RotationPoly> lut528;
    std::vector<long (*)(long)> flut528;
    auto lut528idx0 = [](long I) -> long {
        /* GATE 420 (LUT2 _3184_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut528.push_back(ctx.genrate_lut(lut528idx0));
    flut528.push_back(lut528idx0);
    auto fvec528 = [flut528](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut528[i](I));
        return ret;
    };

    std::cerr << "\rLUT528   ";
    Ciphertext gin528 = 1 * gout522[1] + 2 * gout513[1];
    std::vector<Ciphertext> gout528 = ctx.eval_lut_amortized(&gin528, lut528);

    std::vector<RotationPoly> lut529;
    std::vector<long (*)(long)> flut529;
    auto lut529idx0 = [](long I) -> long {
        /* GATE 193 (LUT2 _2957_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut529.push_back(ctx.genrate_lut(lut529idx0));
    flut529.push_back(lut529idx0);
    auto lut529idx1 = [](long I) -> long {
        /* GATE 418 (LUT2 _3182_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut529.push_back(ctx.genrate_lut(lut529idx1));
    flut529.push_back(lut529idx1);
    auto fvec529 = [flut529](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut529[i](I));
        return ret;
    };

    std::cerr << "\rLUT529   ";
    Ciphertext gin529 = 1 * gout498[0] + 2 * gout522[0];
    std::vector<Ciphertext> gout529 = ctx.eval_lut_amortized(&gin529, lut529);

    std::vector<RotationPoly> lut530;
    std::vector<long (*)(long)> flut530;
    auto lut530idx0 = [](long I) -> long {
        /* GATE 419 (LUT2 _3183_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut530.push_back(ctx.genrate_lut(lut530idx0));
    flut530.push_back(lut530idx0);
    auto lut530idx1 = [](long I) -> long {
        /* GATE 533 (LUT2 _3297_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut530.push_back(ctx.genrate_lut(lut530idx1));
    flut530.push_back(lut530idx1);
    auto fvec530 = [flut530](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut530[i](I));
        return ret;
    };

    std::cerr << "\rLUT530   ";
    Ciphertext gin530 = 1 * gout528[0] + 2 * gout525[1];
    std::vector<Ciphertext> gout530 = ctx.eval_lut_amortized(&gin530, lut530);

    std::vector<RotationPoly> lut531;
    std::vector<long (*)(long)> flut531;
    auto lut531idx0 = [](long I) -> long {
        /* GATE 857 (LUT2 _3621_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut531.push_back(ctx.genrate_lut(lut531idx0));
    flut531.push_back(lut531idx0);
    auto lut531idx1 = [](long I) -> long {
        /* GATE 768 (LUT2 _3532_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut531.push_back(ctx.genrate_lut(lut531idx1));
    flut531.push_back(lut531idx1);
    auto fvec531 = [flut531](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut531[i](I));
        return ret;
    };

    std::cerr << "\rLUT531   ";
    Ciphertext gin531 = 1 * gout526[0] + 2 * gout485[0];
    std::vector<Ciphertext> gout531 = ctx.eval_lut_amortized(&gin531, lut531);

    std::vector<RotationPoly> lut532;
    std::vector<long (*)(long)> flut532;
    auto lut532idx0 = [](long I) -> long {
        /* GATE 535 (LUT2 _3299_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut532.push_back(ctx.genrate_lut(lut532idx0));
    flut532.push_back(lut532idx0);
    auto fvec532 = [flut532](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut532[i](I));
        return ret;
    };

    std::cerr << "\rLUT532   ";
    Ciphertext gin532 = 1 * gout525[0] + 2 * gout518[1];
    std::vector<Ciphertext> gout532 = ctx.eval_lut_amortized(&gin532, lut532);

    std::vector<RotationPoly> lut533;
    std::vector<long (*)(long)> flut533;
    auto lut533idx0 = [](long I) -> long {
        /* GATE 192 (LUT2 _2956_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut533.push_back(ctx.genrate_lut(lut533idx0));
    flut533.push_back(lut533idx0);
    auto lut533idx1 = [](long I) -> long {
        /* GATE 417 (LUT2 _3181_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut533.push_back(ctx.genrate_lut(lut533idx1));
    flut533.push_back(lut533idx1);
    auto fvec533 = [flut533](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut533[i](I));
        return ret;
    };

    std::cerr << "\rLUT533   ";
    Ciphertext gin533 = 1 * gout529[0] + 2 * gout511[0];
    std::vector<Ciphertext> gout533 = ctx.eval_lut_amortized(&gin533, lut533);

    std::vector<RotationPoly> lut534;
    std::vector<long (*)(long)> flut534;
    auto lut534idx0 = [](long I) -> long {
        /* GATE 854 (LUT2 _3618_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut534.push_back(ctx.genrate_lut(lut534idx0));
    flut534.push_back(lut534idx0);
    auto lut534idx1 = [](long I) -> long {
        /* GATE 764 (LUT2 _3528_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut534.push_back(ctx.genrate_lut(lut534idx1));
    flut534.push_back(lut534idx1);
    auto fvec534 = [flut534](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut534[i](I));
        return ret;
    };

    std::cerr << "\rLUT534   ";
    Ciphertext gin534 = 1 * gout524[0] + 2 * gout531[1];
    std::vector<Ciphertext> gout534 = ctx.eval_lut_amortized(&gin534, lut534);

    std::vector<RotationPoly> lut535;
    std::vector<long (*)(long)> flut535;
    auto lut535idx0 = [](long I) -> long {
        /* GATE 416 (LUT2 _3180_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut535.push_back(ctx.genrate_lut(lut535idx0));
    flut535.push_back(lut535idx0);
    auto fvec535 = [flut535](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut535[i](I));
        return ret;
    };

    std::cerr << "\rLUT535   ";
    Ciphertext gin535 = 1 * gout533[1] + 2 * gout529[1];
    std::vector<Ciphertext> gout535 = ctx.eval_lut_amortized(&gin535, lut535);

    std::vector<RotationPoly> lut536;
    std::vector<long (*)(long)> flut536;
    auto lut536idx0 = [](long I) -> long {
        /* GATE 415 (LUT2 _3179_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut536.push_back(ctx.genrate_lut(lut536idx0));
    flut536.push_back(lut536idx0);
    auto lut536idx1 = [](long I) -> long {
        /* GATE 532 (LUT2 _3296_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut536.push_back(ctx.genrate_lut(lut536idx1));
    flut536.push_back(lut536idx1);
    auto fvec536 = [flut536](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut536[i](I));
        return ret;
    };

    std::cerr << "\rLUT536   ";
    Ciphertext gin536 = 1 * gout535[0] + 2 * gout530[0];
    std::vector<Ciphertext> gout536 = ctx.eval_lut_amortized(&gin536, lut536);

    std::vector<RotationPoly> lut537;
    std::vector<long (*)(long)> flut537;
    auto lut537idx0 = [](long I) -> long {
        /* GATE 648 (LUT2 _3412_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut537.push_back(ctx.genrate_lut(lut537idx0));
    flut537.push_back(lut537idx0);
    auto lut537idx1 = [](long I) -> long {
        /* GATE 534 (LUT2 _3298_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut537.push_back(ctx.genrate_lut(lut537idx1));
    flut537.push_back(lut537idx1);
    auto fvec537 = [flut537](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut537[i](I));
        return ret;
    };

    std::cerr << "\rLUT537   ";
    Ciphertext gin537 = 1 * gout532[0] + 2 * gout516[0];
    std::vector<Ciphertext> gout537 = ctx.eval_lut_amortized(&gin537, lut537);

    std::vector<RotationPoly> lut538;
    std::vector<long (*)(long)> flut538;
    auto lut538idx0 = [](long I) -> long {
        /* GATE 531 (LUT2 _3295_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut538.push_back(ctx.genrate_lut(lut538idx0));
    flut538.push_back(lut538idx0);
    auto fvec538 = [flut538](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut538[i](I));
        return ret;
    };

    std::cerr << "\rLUT538   ";
    Ciphertext gin538 = 1 * gout536[1] + 2 * gout530[1];
    std::vector<Ciphertext> gout538 = ctx.eval_lut_amortized(&gin538, lut538);

    std::vector<RotationPoly> lut539;
    std::vector<long (*)(long)> flut539;
    auto lut539idx0 = [](long I) -> long {
        /* GATE 856 (LUT2 _3620_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut539.push_back(ctx.genrate_lut(lut539idx0));
    flut539.push_back(lut539idx0);
    auto fvec539 = [flut539](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut539[i](I));
        return ret;
    };

    std::cerr << "\rLUT539   ";
    Ciphertext gin539 = 1 * gout531[0] + 2 * gout526[1];
    std::vector<Ciphertext> gout539 = ctx.eval_lut_amortized(&gin539, lut539);

    std::vector<RotationPoly> lut540;
    std::vector<long (*)(long)> flut540;
    auto lut540idx0 = [](long I) -> long {
        /* GATE 647 (LUT2 _3411_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut540.push_back(ctx.genrate_lut(lut540idx0));
    flut540.push_back(lut540idx0);
    auto lut540idx1 = [](long I) -> long {
        /* GATE 530 (LUT2 _3294_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut540.push_back(ctx.genrate_lut(lut540idx1));
    flut540.push_back(lut540idx1);
    auto fvec540 = [flut540](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut540[i](I));
        return ret;
    };

    std::cerr << "\rLUT540   ";
    Ciphertext gin540 = 1 * gout538[0] + 2 * gout537[1];
    std::vector<Ciphertext> gout540 = ctx.eval_lut_amortized(&gin540, lut540);

    std::vector<RotationPoly> lut541;
    std::vector<long (*)(long)> flut541;
    auto lut541idx0 = [](long I) -> long {
        /* GATE 855 (LUT2 _3619_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut541.push_back(ctx.genrate_lut(lut541idx0));
    flut541.push_back(lut541idx0);
    auto lut541idx1 = [](long I) -> long {
        /* GATE 897 (LUT2 _3661_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut541.push_back(ctx.genrate_lut(lut541idx1));
    flut541.push_back(lut541idx1);
    auto lut541idx2 = [](long I) -> long {
        /* GATE 898 (LUT2 _3662_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut541.push_back(ctx.genrate_lut(lut541idx2));
    flut541.push_back(lut541idx2);
    auto fvec541 = [flut541](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 3; ++i)
            ret.push_back(flut541[i](I));
        return ret;
    };

    std::cerr << "\rLUT541   ";
    Ciphertext gin541 = 1 * gout539[0] + 2 * gout506[0];
    std::vector<Ciphertext> gout541 = ctx.eval_lut_amortized(&gin541, lut541);

    std::vector<RotationPoly> lut542;
    std::vector<long (*)(long)> flut542;
    auto lut542idx0 = [](long I) -> long {
        /* GATE 646 (LUT2 _3410_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut542.push_back(ctx.genrate_lut(lut542idx0));
    flut542.push_back(lut542idx0);
    auto fvec542 = [flut542](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut542[i](I));
        return ret;
    };

    std::cerr << "\rLUT542   ";
    Ciphertext gin542 = 1 * gout540[0] + 2 * gout537[0];
    std::vector<Ciphertext> gout542 = ctx.eval_lut_amortized(&gin542, lut542);

    std::vector<RotationPoly> lut543;
    std::vector<long (*)(long)> flut543;
    auto lut543idx0 = [](long I) -> long {
        /* GATE 645 (LUT2 _3409_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut543.push_back(ctx.genrate_lut(lut543idx0));
    flut543.push_back(lut543idx0);
    auto lut543idx1 = [](long I) -> long {
        /* GATE 762 (LUT2 _3526_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut543.push_back(ctx.genrate_lut(lut543idx1));
    flut543.push_back(lut543idx1);
    auto fvec543 = [flut543](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut543[i](I));
        return ret;
    };

    std::cerr << "\rLUT543   ";
    Ciphertext gin543 = 1 * gout542[0] + 2 * gout527[0];
    std::vector<Ciphertext> gout543 = ctx.eval_lut_amortized(&gin543, lut543);

    std::vector<RotationPoly> lut544;
    std::vector<long (*)(long)> flut544;
    auto lut544idx0 = [](long I) -> long {
        /* GATE 761 (LUT2 _3525_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut544.push_back(ctx.genrate_lut(lut544idx0));
    flut544.push_back(lut544idx0);
    auto fvec544 = [flut544](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut544[i](I));
        return ret;
    };

    std::cerr << "\rLUT544   ";
    Ciphertext gin544 = 1 * gout543[1] + 2 * gout527[1];
    std::vector<Ciphertext> gout544 = ctx.eval_lut_amortized(&gin544, lut544);

    std::vector<RotationPoly> lut545;
    std::vector<long (*)(long)> flut545;
    auto lut545idx0 = [](long I) -> long {
        /* GATE 853 (LUT2 _3617_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut545.push_back(ctx.genrate_lut(lut545idx0));
    flut545.push_back(lut545idx0);
    auto lut545idx1 = [](long I) -> long {
        /* GATE 760 (LUT2 _3524_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut545.push_back(ctx.genrate_lut(lut545idx1));
    flut545.push_back(lut545idx1);
    auto fvec545 = [flut545](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut545[i](I));
        return ret;
    };

    std::cerr << "\rLUT545   ";
    Ciphertext gin545 = 1 * gout544[0] + 2 * gout534[1];
    std::vector<Ciphertext> gout545 = ctx.eval_lut_amortized(&gin545, lut545);

    std::vector<RotationPoly> lut546;
    std::vector<long (*)(long)> flut546;
    auto lut546idx0 = [](long I) -> long {
        /* GATE 852 (LUT2 _3616_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut546.push_back(ctx.genrate_lut(lut546idx0));
    flut546.push_back(lut546idx0);
    auto fvec546 = [flut546](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut546[i](I));
        return ret;
    };

    std::cerr << "\rLUT546   ";
    Ciphertext gin546 = 1 * gout545[0] + 2 * gout534[0];
    std::vector<Ciphertext> gout546 = ctx.eval_lut_amortized(&gin546, lut546);

    std::vector<RotationPoly> lut547;
    std::vector<long (*)(long)> flut547;
    auto lut547idx0 = [](long I) -> long {
        /* GATE 896 (LUT2 _3660_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut547.push_back(ctx.genrate_lut(lut547idx0));
    flut547.push_back(lut547idx0);
    auto fvec547 = [flut547](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut547[i](I));
        return ret;
    };

    std::cerr << "\rLUT547   ";
    Ciphertext gin547 = 1 * gout541[1] + 2 * gout546[0];
    std::vector<Ciphertext> gout547 = ctx.eval_lut_amortized(&gin547, lut547);

    std::vector<RotationPoly> lut548;
    std::vector<long (*)(long)> flut548;
    auto lut548idx0 = [](long I) -> long {
        /* GATE 851 (LUT2 _3615_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut548.push_back(ctx.genrate_lut(lut548idx0));
    flut548.push_back(lut548idx0);
    auto fvec548 = [flut548](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut548[i](I));
        return ret;
    };

    std::cerr << "\rLUT548   ";
    Ciphertext gin548 = 1 * gout546[0] + 2 * gout541[0];
    std::vector<Ciphertext> gout548 = ctx.eval_lut_amortized(&gin548, lut548);

    std::vector<RotationPoly> lut549;
    std::vector<long (*)(long)> flut549;
    auto lut549idx0 = [](long I) -> long {
        /* GATE 895 (LUT2 _3659_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut549.push_back(ctx.genrate_lut(lut549idx0));
    flut549.push_back(lut549idx0);
    auto fvec549 = [flut549](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut549[i](I));
        return ret;
    };

    std::cerr << "\rLUT549   ";
    Ciphertext gin549 = 1 * gout547[0] + 2 * gout541[2];
    std::vector<Ciphertext> gout549 = ctx.eval_lut_amortized(&gin549, lut549);

    std::vector<RotationPoly> lut550;
    std::vector<long (*)(long)> flut550;
    auto lut550idx0 = [](long I) -> long {
        /* GATE 918 (LUT2 _3682_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut550.push_back(ctx.genrate_lut(lut550idx0));
    flut550.push_back(lut550idx0);
    auto lut550idx1 = [](long I) -> long {
        /* GATE 894 (LUT2 _3658_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut550.push_back(ctx.genrate_lut(lut550idx1));
    flut550.push_back(lut550idx1);
    auto fvec550 = [flut550](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut550[i](I));
        return ret;
    };

    std::cerr << "\rLUT550   ";
    Ciphertext gin550 = 1 * gout549[0] + 2 * gout521[1];
    std::vector<Ciphertext> gout550 = ctx.eval_lut_amortized(&gin550, lut550);

    std::vector<RotationPoly> lut551;
    std::vector<long (*)(long)> flut551;
    auto lut551idx0 = [](long I) -> long {
        /* GATE 917 (LUT2 _3681_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut551.push_back(ctx.genrate_lut(lut551idx0));
    flut551.push_back(lut551idx0);
    auto fvec551 = [flut551](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut551[i](I));
        return ret;
    };

    std::cerr << "\rLUT551   ";
    Ciphertext gin551 = 1 * gout550[0] + 2 * gout521[0];
    std::vector<Ciphertext> gout551 = ctx.eval_lut_amortized(&gin551, lut551);

    std::vector<RotationPoly> lut552;
    std::vector<long (*)(long)> flut552;
    auto lut552idx0 = [](long I) -> long {
        /* GATE 916 (LUT2 _3680_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut552.push_back(ctx.genrate_lut(lut552idx0));
    flut552.push_back(lut552idx0);
    auto lut552idx1 = [](long I) -> long {
        /* GATE 926 (LUT2 _3690_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut552.push_back(ctx.genrate_lut(lut552idx1));
    flut552.push_back(lut552idx1);
    auto fvec552 = [flut552](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut552[i](I));
        return ret;
    };

    std::cerr << "\rLUT552   ";
    Ciphertext gin552 = 1 * gout551[0] + 2 * gout517[0];
    std::vector<Ciphertext> gout552 = ctx.eval_lut_amortized(&gin552, lut552);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(ctx.decrypt(&gout284[1])); /* out192 */
    test_out.push_back(ctx.decrypt(&gout398[1])); /* out193 */
    test_out.push_back(ctx.decrypt(&gout491[0])); /* out194 */
    test_out.push_back(ctx.decrypt(&gout511[1])); /* out195 */
    test_out.push_back(ctx.decrypt(&gout533[0])); /* out196 */
    test_out.push_back(ctx.decrypt(&gout536[0])); /* out197 */
    test_out.push_back(ctx.decrypt(&gout540[1])); /* out198 */
    test_out.push_back(ctx.decrypt(&gout543[0])); /* out199 */
    test_out.push_back(ctx.decrypt(&gout545[1])); /* out200 */
    test_out.push_back(ctx.decrypt(&gout548[0])); /* out201 */
    test_out.push_back(ctx.decrypt(&gout550[1])); /* out202 */
    test_out.push_back(ctx.decrypt(&gout552[0])); /* out203 */
    test_out.push_back(ctx.decrypt(&gout552[1])); /* out204 */
    return test_out;
}

static void
BM_sum3d_lut2(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(tfhe_11_NTT);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(4);

    for (auto _ : state) {
        test_sum3d_lut2(ctx);
    }
}

BENCHMARK(BM_sum3d_lut2)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
