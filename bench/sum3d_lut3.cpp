#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_sum3d_lut3(FHEContext& ctx, std::vector<uint64_t> out = { 0 })
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
        /* GATE 295 (LUT3 _1469_ INIT 0x17 PERM 012) */
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
    lut0.push_back(ctx.genrate_lut(lut0idx0));
    flut0.push_back(lut0idx0);
    auto lut0idx1 = [](long I) -> long {
        /* GATE 251 (LUT3 _1425_ INIT 0x96 PERM 012) */
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
    lut0.push_back(ctx.genrate_lut(lut0idx1));
    flut0.push_back(lut0idx1);
    auto fvec0 = [flut0](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut0[i](I));
        return ret;
    };

    std::cerr << "\rLUT0   ";
    Ciphertext gin0 = 1 * ct_out166 + 2 * ct_out150 + 4 * ct_out158;
    std::vector<Ciphertext> gout0 = ctx.eval_lut_amortized(&gin0, lut0);

    std::vector<RotationPoly> lut1;
    std::vector<long (*)(long)> flut1;
    auto lut1idx0 = [](long I) -> long {
        /* GATE 65 (LUT3 _1239_ INIT 0x96 PERM 012) */
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
        /* GATE 133 (LUT3 _1307_ INIT 0x17 PERM 012) */
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
    Ciphertext gin1 = 1 * ct_out138 + 2 * ct_out122 + 4 * ct_out130;
    std::vector<Ciphertext> gout1 = ctx.eval_lut_amortized(&gin1, lut1);

    std::vector<RotationPoly> lut2;
    std::vector<long (*)(long)> flut2;
    auto lut2idx0 = [](long I) -> long {
        /* GATE 177 (LUT3 _1351_ INIT 0x17 PERM 012) */
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
    lut2.push_back(ctx.genrate_lut(lut2idx0));
    flut2.push_back(lut2idx0);
    auto lut2idx1 = [](long I) -> long {
        /* GATE 113 (LUT3 _1287_ INIT 0x96 PERM 012) */
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
    lut2.push_back(ctx.genrate_lut(lut2idx1));
    flut2.push_back(lut2idx1);
    auto fvec2 = [flut2](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut2[i](I));
        return ret;
    };

    std::cerr << "\rLUT2   ";
    Ciphertext gin2 = 1 * ct_out67 + 2 * ct_out51 + 4 * ct_out59;
    std::vector<Ciphertext> gout2 = ctx.eval_lut_amortized(&gin2, lut2);

    std::vector<RotationPoly> lut3;
    std::vector<long (*)(long)> flut3;
    auto lut3idx0 = [](long I) -> long {
        /* GATE 355 (LUT3 _1529_ INIT 0x17 PERM 012) */
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
    lut3.push_back(ctx.genrate_lut(lut3idx0));
    flut3.push_back(lut3idx0);
    auto lut3idx1 = [](long I) -> long {
        /* GATE 317 (LUT3 _1491_ INIT 0x96 PERM 012) */
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
    lut3.push_back(ctx.genrate_lut(lut3idx1));
    flut3.push_back(lut3idx1);
    auto fvec3 = [flut3](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut3[i](I));
        return ret;
    };

    std::cerr << "\rLUT3   ";
    Ciphertext gin3 = 1 * ct_out95 + 2 * ct_out79 + 4 * ct_out87;
    std::vector<Ciphertext> gout3 = ctx.eval_lut_amortized(&gin3, lut3);

    std::vector<RotationPoly> lut4;
    std::vector<long (*)(long)> flut4;
    auto lut4idx0 = [](long I) -> long {
        /* GATE 292 (LUT3 _1466_ INIT 0x96 PERM 012) */
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
    lut4.push_back(ctx.genrate_lut(lut4idx0));
    flut4.push_back(lut4idx0);
    auto lut4idx1 = [](long I) -> long {
        /* GATE 332 (LUT3 _1506_ INIT 0x17 PERM 012) */
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
    lut4.push_back(ctx.genrate_lut(lut4idx1));
    flut4.push_back(lut4idx1);
    auto fvec4 = [flut4](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut4[i](I));
        return ret;
    };

    std::cerr << "\rLUT4   ";
    Ciphertext gin4 = 1 * ct_out119 + 2 * ct_out103 + 4 * ct_out111;
    std::vector<Ciphertext> gout4 = ctx.eval_lut_amortized(&gin4, lut4);

    std::vector<RotationPoly> lut5;
    std::vector<long (*)(long)> flut5;
    auto lut5idx0 = [](long I) -> long {
        /* GATE 48 (LUT3 _1222_ INIT 0x96 PERM 012) */
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
    lut5.push_back(ctx.genrate_lut(lut5idx0));
    flut5.push_back(lut5idx0);
    auto lut5idx1 = [](long I) -> long {
        /* GATE 93 (LUT3 _1267_ INIT 0x17 PERM 012) */
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
    lut5.push_back(ctx.genrate_lut(lut5idx1));
    flut5.push_back(lut5idx1);
    auto fvec5 = [flut5](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut5[i](I));
        return ret;
    };

    std::cerr << "\rLUT5   ";
    Ciphertext gin5 = 1 * ct_out89 + 2 * ct_out73 + 4 * ct_out81;
    std::vector<Ciphertext> gout5 = ctx.eval_lut_amortized(&gin5, lut5);

    std::vector<RotationPoly> lut6;
    std::vector<long (*)(long)> flut6;
    auto lut6idx0 = [](long I) -> long {
        /* GATE 126 (LUT3 _1300_ INIT 0x96 PERM 012) */
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
    lut6.push_back(ctx.genrate_lut(lut6idx0));
    flut6.push_back(lut6idx0);
    auto lut6idx1 = [](long I) -> long {
        /* GATE 174 (LUT3 _1348_ INIT 0x17 PERM 012) */
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
    lut6.push_back(ctx.genrate_lut(lut6idx1));
    flut6.push_back(lut6idx1);
    auto fvec6 = [flut6](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut6[i](I));
        return ret;
    };

    std::cerr << "\rLUT6   ";
    Ciphertext gin6 = 1 * ct_out19 + 2 * ct_out3 + 4 * ct_out11;
    std::vector<Ciphertext> gout6 = ctx.eval_lut_amortized(&gin6, lut6);

    std::vector<RotationPoly> lut7;
    std::vector<long (*)(long)> flut7;
    auto lut7idx0 = [](long I) -> long {
        /* GATE 47 (LUT3 _1221_ INIT 0x96 PERM 012) */
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
        /* GATE 87 (LUT3 _1261_ INIT 0x17 PERM 012) */
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
    Ciphertext gin7 = 1 * ct_out65 + 2 * ct_out49 + 4 * ct_out57;
    std::vector<Ciphertext> gout7 = ctx.eval_lut_amortized(&gin7, lut7);

    std::vector<RotationPoly> lut8;
    std::vector<long (*)(long)> flut8;
    auto lut8idx0 = [](long I) -> long {
        /* GATE 266 (LUT3 _1440_ INIT 0x17 PERM 012) */
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
    lut8.push_back(ctx.genrate_lut(lut8idx0));
    flut8.push_back(lut8idx0);
    auto lut8idx1 = [](long I) -> long {
        /* GATE 212 (LUT3 _1386_ INIT 0x96 PERM 012) */
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
    lut8.push_back(ctx.genrate_lut(lut8idx1));
    flut8.push_back(lut8idx1);
    auto fvec8 = [flut8](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut8[i](I));
        return ret;
    };

    std::cerr << "\rLUT8   ";
    Ciphertext gin8 = 1 * ct_out21 + 2 * ct_out5 + 4 * ct_out13;
    std::vector<Ciphertext> gout8 = ctx.eval_lut_amortized(&gin8, lut8);

    std::vector<RotationPoly> lut9;
    std::vector<long (*)(long)> flut9;
    auto lut9idx0 = [](long I) -> long {
        /* GATE 104 (LUT3 _1278_ INIT 0x17 PERM 012) */
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
    lut9.push_back(ctx.genrate_lut(lut9idx0));
    flut9.push_back(lut9idx0);
    auto lut9idx1 = [](long I) -> long {
        /* GATE 89 (LUT3 _1263_ INIT 0x96 PERM 012) */
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
    lut9.push_back(ctx.genrate_lut(lut9idx1));
    flut9.push_back(lut9idx1);
    auto fvec9 = [flut9](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut9[i](I));
        return ret;
    };

    std::cerr << "\rLUT9   ";
    Ciphertext gin9 = 1 * ct_out90 + 2 * ct_out74 + 4 * ct_out82;
    std::vector<Ciphertext> gout9 = ctx.eval_lut_amortized(&gin9, lut9);

    std::vector<RotationPoly> lut10;
    std::vector<long (*)(long)> flut10;
    auto lut10idx0 = [](long I) -> long {
        /* GATE 229 (LUT3 _1403_ INIT 0x17 PERM 012) */
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
    lut10.push_back(ctx.genrate_lut(lut10idx0));
    flut10.push_back(lut10idx0);
    auto lut10idx1 = [](long I) -> long {
        /* GATE 179 (LUT3 _1353_ INIT 0x96 PERM 012) */
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
    lut10.push_back(ctx.genrate_lut(lut10idx1));
    flut10.push_back(lut10idx1);
    auto fvec10 = [flut10](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut10[i](I));
        return ret;
    };

    std::cerr << "\rLUT10   ";
    Ciphertext gin10 = 1 * ct_out92 + 2 * ct_out76 + 4 * ct_out84;
    std::vector<Ciphertext> gout10 = ctx.eval_lut_amortized(&gin10, lut10);

    std::vector<RotationPoly> lut11;
    std::vector<long (*)(long)> flut11;
    auto lut11idx0 = [](long I) -> long {
        /* GATE 118 (LUT3 _1292_ INIT 0x17 PERM 012) */
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
    lut11.push_back(ctx.genrate_lut(lut11idx0));
    flut11.push_back(lut11idx0);
    auto lut11idx1 = [](long I) -> long {
        /* GATE 76 (LUT3 _1250_ INIT 0x96 PERM 012) */
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
    lut11.push_back(ctx.genrate_lut(lut11idx1));
    flut11.push_back(lut11idx1);
    auto fvec11 = [flut11](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut11[i](I));
        return ret;
    };

    std::cerr << "\rLUT11   ";
    Ciphertext gin11 = 1 * ct_out18 + 2 * ct_out2 + 4 * ct_out10;
    std::vector<Ciphertext> gout11 = ctx.eval_lut_amortized(&gin11, lut11);

    std::vector<RotationPoly> lut12;
    std::vector<long (*)(long)> flut12;
    auto lut12idx0 = [](long I) -> long {
        /* GATE 199 (LUT3 _1373_ INIT 0x17 PERM 012) */
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
    lut12.push_back(ctx.genrate_lut(lut12idx0));
    flut12.push_back(lut12idx0);
    auto lut12idx1 = [](long I) -> long {
        /* GATE 154 (LUT3 _1328_ INIT 0x96 PERM 012) */
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
    lut12.push_back(ctx.genrate_lut(lut12idx1));
    flut12.push_back(lut12idx1);
    auto fvec12 = [flut12](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut12[i](I));
        return ret;
    };

    std::cerr << "\rLUT12   ";
    Ciphertext gin12 = 1 * ct_out116 + 2 * ct_out100 + 4 * ct_out108;
    std::vector<Ciphertext> gout12 = ctx.eval_lut_amortized(&gin12, lut12);

    std::vector<RotationPoly> lut13;
    std::vector<long (*)(long)> flut13;
    auto lut13idx0 = [](long I) -> long {
        /* GATE 247 (LUT3 _1421_ INIT 0x96 PERM 012) */
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
    lut13.push_back(ctx.genrate_lut(lut13idx0));
    flut13.push_back(lut13idx0);
    auto lut13idx1 = [](long I) -> long {
        /* GATE 296 (LUT3 _1470_ INIT 0x17 PERM 012) */
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
    lut13.push_back(ctx.genrate_lut(lut13idx1));
    flut13.push_back(lut13idx1);
    auto fvec13 = [flut13](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut13[i](I));
        return ret;
    };

    std::cerr << "\rLUT13   ";
    Ciphertext gin13 = 1 * ct_out142 + 2 * ct_out126 + 4 * ct_out134;
    std::vector<Ciphertext> gout13 = ctx.eval_lut_amortized(&gin13, lut13);

    std::vector<RotationPoly> lut14;
    std::vector<long (*)(long)> flut14;
    auto lut14idx0 = [](long I) -> long {
        /* GATE 205 (LUT3 _1379_ INIT 0x96 PERM 012) */
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
    lut14.push_back(ctx.genrate_lut(lut14idx0));
    flut14.push_back(lut14idx0);
    auto lut14idx1 = [](long I) -> long {
        /* GATE 249 (LUT3 _1423_ INIT 0x17 PERM 012) */
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
    lut14.push_back(ctx.genrate_lut(lut14idx1));
    flut14.push_back(lut14idx1);
    auto fvec14 = [flut14](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut14[i](I));
        return ret;
    };

    std::cerr << "\rLUT14   ";
    Ciphertext gin14 = 1 * ct_out165 + 2 * ct_out149 + 4 * ct_out157;
    std::vector<Ciphertext> gout14 = ctx.eval_lut_amortized(&gin14, lut14);

    std::vector<RotationPoly> lut15;
    std::vector<long (*)(long)> flut15;
    auto lut15idx0 = [](long I) -> long {
        /* GATE 271 (LUT3 _1445_ INIT 0x96 PERM 012) */
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
    lut15.push_back(ctx.genrate_lut(lut15idx0));
    flut15.push_back(lut15idx0);
    auto lut15idx1 = [](long I) -> long {
        /* GATE 321 (LUT3 _1495_ INIT 0x17 PERM 012) */
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
    lut15.push_back(ctx.genrate_lut(lut15idx1));
    flut15.push_back(lut15idx1);
    auto fvec15 = [flut15](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut15[i](I));
        return ret;
    };

    std::cerr << "\rLUT15   ";
    Ciphertext gin15 = 1 * ct_out94 + 2 * ct_out78 + 4 * ct_out86;
    std::vector<Ciphertext> gout15 = ctx.eval_lut_amortized(&gin15, lut15);

    std::vector<RotationPoly> lut16;
    std::vector<long (*)(long)> flut16;
    auto lut16idx0 = [](long I) -> long {
        /* GATE 69 (LUT3 _1243_ INIT 0x96 PERM 012) */
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
    lut16.push_back(ctx.genrate_lut(lut16idx0));
    flut16.push_back(lut16idx0);
    auto lut16idx1 = [](long I) -> long {
        /* GATE 132 (LUT3 _1306_ INIT 0x17 PERM 012) */
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
    lut16.push_back(ctx.genrate_lut(lut16idx1));
    flut16.push_back(lut16idx1);
    auto fvec16 = [flut16](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut16[i](I));
        return ret;
    };

    std::cerr << "\rLUT16   ";
    Ciphertext gin16 = 1 * ct_out162 + 2 * ct_out146 + 4 * ct_out154;
    std::vector<Ciphertext> gout16 = ctx.eval_lut_amortized(&gin16, lut16);

    std::vector<RotationPoly> lut17;
    std::vector<long (*)(long)> flut17;
    auto lut17idx0 = [](long I) -> long {
        /* GATE 25 (LUT3 _1199_ INIT 0x17 PERM 012) */
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
    lut17.push_back(ctx.genrate_lut(lut17idx0));
    flut17.push_back(lut17idx0);
    auto lut17idx1 = [](long I) -> long {
        /* GATE 5 (LUT3 _1179_ INIT 0x96 PERM 012) */
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
    lut17.push_back(ctx.genrate_lut(lut17idx1));
    flut17.push_back(lut17idx1);
    auto fvec17 = [flut17](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut17[i](I));
        return ret;
    };

    std::cerr << "\rLUT17   ";
    Ciphertext gin17 = 1 * ct_out112 + 2 * ct_out96 + 4 * ct_out104;
    std::vector<Ciphertext> gout17 = ctx.eval_lut_amortized(&gin17, lut17);

    std::vector<RotationPoly> lut18;
    std::vector<long (*)(long)> flut18;
    auto lut18idx0 = [](long I) -> long {
        /* GATE 153 (LUT3 _1327_ INIT 0x17 PERM 012) */
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
    lut18.push_back(ctx.genrate_lut(lut18idx0));
    flut18.push_back(lut18idx0);
    auto lut18idx1 = [](long I) -> long {
        /* GATE 139 (LUT3 _1313_ INIT 0x96 PERM 012) */
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
    lut18.push_back(ctx.genrate_lut(lut18idx1));
    flut18.push_back(lut18idx1);
    auto fvec18 = [flut18](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut18[i](I));
        return ret;
    };

    std::cerr << "\rLUT18   ";
    Ciphertext gin18 = 1 * ct_out115 + 2 * ct_out99 + 4 * ct_out107;
    std::vector<Ciphertext> gout18 = ctx.eval_lut_amortized(&gin18, lut18);

    std::vector<RotationPoly> lut19;
    std::vector<long (*)(long)> flut19;
    auto lut19idx0 = [](long I) -> long {
        /* GATE 43 (LUT3 _1217_ INIT 0x17 PERM 012) */
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
    lut19.push_back(ctx.genrate_lut(lut19idx0));
    flut19.push_back(lut19idx0);
    auto lut19idx1 = [](long I) -> long {
        /* GATE 10 (LUT3 _1184_ INIT 0x96 PERM 012) */
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
    lut19.push_back(ctx.genrate_lut(lut19idx1));
    flut19.push_back(lut19idx1);
    auto fvec19 = [flut19](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut19[i](I));
        return ret;
    };

    std::cerr << "\rLUT19   ";
    Ciphertext gin19 = 1 * ct_out16 + 2 * ct_out0 + 4 * ct_out8;
    std::vector<Ciphertext> gout19 = ctx.eval_lut_amortized(&gin19, lut19);

    std::vector<RotationPoly> lut20;
    std::vector<long (*)(long)> flut20;
    auto lut20idx0 = [](long I) -> long {
        /* GATE 159 (LUT3 _1333_ INIT 0x96 PERM 012) */
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
    lut20.push_back(ctx.genrate_lut(lut20idx0));
    flut20.push_back(lut20idx0);
    auto lut20idx1 = [](long I) -> long {
        /* GATE 203 (LUT3 _1377_ INIT 0x17 PERM 012) */
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
    lut20.push_back(ctx.genrate_lut(lut20idx1));
    flut20.push_back(lut20idx1);
    auto fvec20 = [flut20](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut20[i](I));
        return ret;
    };

    std::cerr << "\rLUT20   ";
    Ciphertext gin20 = 1 * ct_out164 + 2 * ct_out148 + 4 * ct_out156;
    std::vector<Ciphertext> gout20 = ctx.eval_lut_amortized(&gin20, lut20);

    std::vector<RotationPoly> lut21;
    std::vector<long (*)(long)> flut21;
    auto lut21idx0 = [](long I) -> long {
        /* GATE 311 (LUT3 _1485_ INIT 0x17 PERM 012) */
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
    lut21.push_back(ctx.genrate_lut(lut21idx0));
    flut21.push_back(lut21idx0);
    auto lut21idx1 = [](long I) -> long {
        /* GATE 267 (LUT3 _1441_ INIT 0x96 PERM 012) */
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
    lut21.push_back(ctx.genrate_lut(lut21idx1));
    flut21.push_back(lut21idx1);
    auto fvec21 = [flut21](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut21[i](I));
        return ret;
    };

    std::cerr << "\rLUT21   ";
    Ciphertext gin21 = 1 * ct_out46 + 2 * ct_out30 + 4 * ct_out38;
    std::vector<Ciphertext> gout21 = ctx.eval_lut_amortized(&gin21, lut21);

    std::vector<RotationPoly> lut22;
    std::vector<long (*)(long)> flut22;
    auto lut22idx0 = [](long I) -> long {
        /* GATE 7 (LUT3 _1181_ INIT 0x96 PERM 012) */
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
    lut22.push_back(ctx.genrate_lut(lut22idx0));
    flut22.push_back(lut22idx0);
    auto lut22idx1 = [](long I) -> long {
        /* GATE 29 (LUT3 _1203_ INIT 0x17 PERM 012) */
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
    lut22.push_back(ctx.genrate_lut(lut22idx1));
    flut22.push_back(lut22idx1);
    auto fvec22 = [flut22](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut22[i](I));
        return ret;
    };

    std::cerr << "\rLUT22   ";
    Ciphertext gin22 = 1 * ct_out160 + 2 * ct_out144 + 4 * ct_out152;
    std::vector<Ciphertext> gout22 = ctx.eval_lut_amortized(&gin22, lut22);

    std::vector<RotationPoly> lut23;
    std::vector<long (*)(long)> flut23;
    auto lut23idx0 = [](long I) -> long {
        /* GATE 293 (LUT3 _1467_ INIT 0x96 PERM 012) */
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
    lut23.push_back(ctx.genrate_lut(lut23idx0));
    flut23.push_back(lut23idx0);
    auto lut23idx1 = [](long I) -> long {
        /* GATE 334 (LUT3 _1508_ INIT 0x17 PERM 012) */
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
    lut23.push_back(ctx.genrate_lut(lut23idx1));
    flut23.push_back(lut23idx1);
    auto fvec23 = [flut23](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut23[i](I));
        return ret;
    };

    std::cerr << "\rLUT23   ";
    Ciphertext gin23 = 1 * ct_out143 + 2 * ct_out127 + 4 * ct_out135;
    std::vector<Ciphertext> gout23 = ctx.eval_lut_amortized(&gin23, lut23);

    std::vector<RotationPoly> lut24;
    std::vector<long (*)(long)> flut24;
    auto lut24idx0 = [](long I) -> long {
        /* GATE 265 (LUT3 _1439_ INIT 0x17 PERM 012) */
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
    lut24.push_back(ctx.genrate_lut(lut24idx0));
    flut24.push_back(lut24idx0);
    auto lut24idx1 = [](long I) -> long {
        /* GATE 221 (LUT3 _1395_ INIT 0x96 PERM 012) */
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
    lut24.push_back(ctx.genrate_lut(lut24idx1));
    flut24.push_back(lut24idx1);
    auto fvec24 = [flut24](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut24[i](I));
        return ret;
    };

    std::cerr << "\rLUT24   ";
    Ciphertext gin24 = 1 * ct_out45 + 2 * ct_out29 + 4 * ct_out37;
    std::vector<Ciphertext> gout24 = ctx.eval_lut_amortized(&gin24, lut24);

    std::vector<RotationPoly> lut25;
    std::vector<long (*)(long)> flut25;
    auto lut25idx0 = [](long I) -> long {
        /* GATE 44 (LUT3 _1218_ INIT 0x96 PERM 012) */
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
    lut25.push_back(ctx.genrate_lut(lut25idx0));
    flut25.push_back(lut25idx0);
    auto lut25idx1 = [](long I) -> long {
        /* GATE 83 (LUT3 _1257_ INIT 0x17 PERM 012) */
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
    lut25.push_back(ctx.genrate_lut(lut25idx1));
    flut25.push_back(lut25idx1);
    auto fvec25 = [flut25](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut25[i](I));
        return ret;
    };

    std::cerr << "\rLUT25   ";
    Ciphertext gin25 = 1 * ct_out41 + 2 * ct_out25 + 4 * ct_out33;
    std::vector<Ciphertext> gout25 = ctx.eval_lut_amortized(&gin25, lut25);

    std::vector<RotationPoly> lut26;
    std::vector<long (*)(long)> flut26;
    auto lut26idx0 = [](long I) -> long {
        /* GATE 88 (LUT3 _1262_ INIT 0x96 PERM 012) */
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
    lut26.push_back(ctx.genrate_lut(lut26idx0));
    flut26.push_back(lut26idx0);
    auto lut26idx1 = [](long I) -> long {
        /* GATE 112 (LUT3 _1286_ INIT 0x17 PERM 012) */
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
    lut26.push_back(ctx.genrate_lut(lut26idx1));
    flut26.push_back(lut26idx1);
    auto fvec26 = [flut26](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut26[i](I));
        return ret;
    };

    std::cerr << "\rLUT26   ";
    Ciphertext gin26 = 1 * ct_out66 + 2 * ct_out50 + 4 * ct_out58;
    std::vector<Ciphertext> gout26 = ctx.eval_lut_amortized(&gin26, lut26);

    std::vector<RotationPoly> lut27;
    std::vector<long (*)(long)> flut27;
    auto lut27idx0 = [](long I) -> long {
        /* GATE 137 (LUT3 _1311_ INIT 0x96 PERM 012) */
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
    lut27.push_back(ctx.genrate_lut(lut27idx0));
    flut27.push_back(lut27idx0);
    auto lut27idx1 = [](long I) -> long {
        /* GATE 158 (LUT3 _1332_ INIT 0x17 PERM 012) */
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
    lut27.push_back(ctx.genrate_lut(lut27idx1));
    flut27.push_back(lut27idx1);
    auto fvec27 = [flut27](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut27[i](I));
        return ret;
    };

    std::cerr << "\rLUT27   ";
    Ciphertext gin27 = 1 * ct_out139 + 2 * ct_out123 + 4 * ct_out131;
    std::vector<Ciphertext> gout27 = ctx.eval_lut_amortized(&gin27, lut27);

    std::vector<RotationPoly> lut28;
    std::vector<long (*)(long)> flut28;
    auto lut28idx0 = [](long I) -> long {
        /* GATE 303 (LUT3 _1477_ INIT 0x96 PERM 012) */
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
    lut28.push_back(ctx.genrate_lut(lut28idx0));
    flut28.push_back(lut28idx0);
    auto lut28idx1 = [](long I) -> long {
        /* GATE 340 (LUT3 _1514_ INIT 0x17 PERM 012) */
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
    lut28.push_back(ctx.genrate_lut(lut28idx1));
    flut28.push_back(lut28idx1);
    auto fvec28 = [flut28](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut28[i](I));
        return ret;
    };

    std::cerr << "\rLUT28   ";
    Ciphertext gin28 = 1 * ct_out191 + 2 * ct_out175 + 4 * ct_out183;
    std::vector<Ciphertext> gout28 = ctx.eval_lut_amortized(&gin28, lut28);

    std::vector<RotationPoly> lut29;
    std::vector<long (*)(long)> flut29;
    auto lut29idx0 = [](long I) -> long {
        /* GATE 302 (LUT3 _1476_ INIT 0x17 PERM 012) */
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
    lut29.push_back(ctx.genrate_lut(lut29idx0));
    flut29.push_back(lut29idx0);
    auto lut29idx1 = [](long I) -> long {
        /* GATE 257 (LUT3 _1431_ INIT 0x96 PERM 012) */
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
    lut29.push_back(ctx.genrate_lut(lut29idx1));
    flut29.push_back(lut29idx1);
    auto fvec29 = [flut29](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut29[i](I));
        return ret;
    };

    std::cerr << "\rLUT29   ";
    Ciphertext gin29 = 1 * ct_out190 + 2 * ct_out174 + 4 * ct_out182;
    std::vector<Ciphertext> gout29 = ctx.eval_lut_amortized(&gin29, lut29);

    std::vector<RotationPoly> lut30;
    std::vector<long (*)(long)> flut30;
    auto lut30idx0 = [](long I) -> long {
        /* GATE 114 (LUT3 _1288_ INIT 0x96 PERM 012) */
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
    lut30.push_back(ctx.genrate_lut(lut30idx0));
    flut30.push_back(lut30idx0);
    auto lut30idx1 = [](long I) -> long {
        /* GATE 183 (LUT3 _1357_ INIT 0x17 PERM 012) */
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
    lut30.push_back(ctx.genrate_lut(lut30idx1));
    flut30.push_back(lut30idx1);
    auto fvec30 = [flut30](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut30[i](I));
        return ret;
    };

    std::cerr << "\rLUT30   ";
    Ciphertext gin30 = 1 * ct_out91 + 2 * ct_out75 + 4 * ct_out83;
    std::vector<Ciphertext> gout30 = ctx.eval_lut_amortized(&gin30, lut30);

    std::vector<RotationPoly> lut31;
    std::vector<long (*)(long)> flut31;
    auto lut31idx0 = [](long I) -> long {
        /* GATE 119 (LUT3 _1293_ INIT 0x96 PERM 012) */
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
    lut31.push_back(ctx.genrate_lut(lut31idx0));
    flut31.push_back(lut31idx0);
    auto lut31idx1 = [](long I) -> long {
        /* GATE 173 (LUT3 _1347_ INIT 0x17 PERM 012) */
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
    lut31.push_back(ctx.genrate_lut(lut31idx1));
    flut31.push_back(lut31idx1);
    auto fvec31 = [flut31](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut31[i](I));
        return ret;
    };

    std::cerr << "\rLUT31   ";
    Ciphertext gin31 = 1 * ct_out43 + 2 * ct_out27 + 4 * ct_out35;
    std::vector<Ciphertext> gout31 = ctx.eval_lut_amortized(&gin31, lut31);

    std::vector<RotationPoly> lut32;
    std::vector<long (*)(long)> flut32;
    auto lut32idx0 = [](long I) -> long {
        /* GATE 258 (LUT3 _1432_ INIT 0x96 PERM 012) */
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
    lut32.push_back(ctx.genrate_lut(lut32idx0));
    flut32.push_back(lut32idx0);
    auto lut32idx1 = [](long I) -> long {
        /* GATE 312 (LUT3 _1486_ INIT 0x17 PERM 012) */
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
    lut32.push_back(ctx.genrate_lut(lut32idx1));
    flut32.push_back(lut32idx1);
    auto fvec32 = [flut32](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut32[i](I));
        return ret;
    };

    std::cerr << "\rLUT32   ";
    Ciphertext gin32 = 1 * ct_out22 + 2 * ct_out6 + 4 * ct_out14;
    std::vector<Ciphertext> gout32 = ctx.eval_lut_amortized(&gin32, lut32);

    std::vector<RotationPoly> lut33;
    std::vector<long (*)(long)> flut33;
    auto lut33idx0 = [](long I) -> long {
        /* GATE 211 (LUT3 _1385_ INIT 0x96 PERM 012) */
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
    lut33.push_back(ctx.genrate_lut(lut33idx0));
    flut33.push_back(lut33idx0);
    auto lut33idx1 = [](long I) -> long {
        /* GATE 256 (LUT3 _1430_ INIT 0x17 PERM 012) */
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
    lut33.push_back(ctx.genrate_lut(lut33idx1));
    flut33.push_back(lut33idx1);
    auto fvec33 = [flut33](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut33[i](I));
        return ret;
    };

    std::cerr << "\rLUT33   ";
    Ciphertext gin33 = 1 * ct_out189 + 2 * ct_out173 + 4 * ct_out181;
    std::vector<Ciphertext> gout33 = ctx.eval_lut_amortized(&gin33, lut33);

    std::vector<RotationPoly> lut34;
    std::vector<long (*)(long)> flut34;
    auto lut34idx0 = [](long I) -> long {
        /* GATE 15 (LUT3 _1189_ INIT 0x96 PERM 012) */
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
    lut34.push_back(ctx.genrate_lut(lut34idx0));
    flut34.push_back(lut34idx0);
    auto lut34idx1 = [](long I) -> long {
        /* GATE 42 (LUT3 _1216_ INIT 0x17 PERM 012) */
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
    lut34.push_back(ctx.genrate_lut(lut34idx1));
    flut34.push_back(lut34idx1);
    auto fvec34 = [flut34](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut34[i](I));
        return ret;
    };

    std::cerr << "\rLUT34   ";
    Ciphertext gin34 = 1 * ct_out40 + 2 * ct_out24 + 4 * ct_out32;
    std::vector<Ciphertext> gout34 = ctx.eval_lut_amortized(&gin34, lut34);

    std::vector<RotationPoly> lut35;
    std::vector<long (*)(long)> flut35;
    auto lut35idx0 = [](long I) -> long {
        /* GATE 250 (LUT3 _1424_ INIT 0x17 PERM 012) */
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
    lut35.push_back(ctx.genrate_lut(lut35idx0));
    flut35.push_back(lut35idx0);
    auto lut35idx1 = [](long I) -> long {
        /* GATE 201 (LUT3 _1375_ INIT 0x96 PERM 012) */
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
    lut35.push_back(ctx.genrate_lut(lut35idx1));
    flut35.push_back(lut35idx1);
    auto fvec35 = [flut35](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut35[i](I));
        return ret;
    };

    std::cerr << "\rLUT35   ";
    Ciphertext gin35 = 1 * ct_out141 + 2 * ct_out125 + 4 * ct_out133;
    std::vector<Ciphertext> gout35 = ctx.eval_lut_amortized(&gin35, lut35);

    std::vector<RotationPoly> lut36;
    std::vector<long (*)(long)> flut36;
    auto lut36idx0 = [](long I) -> long {
        /* GATE 204 (LUT3 _1378_ INIT 0x17 PERM 012) */
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
    lut36.push_back(ctx.genrate_lut(lut36idx0));
    flut36.push_back(lut36idx0);
    auto lut36idx1 = [](long I) -> long {
        /* GATE 155 (LUT3 _1329_ INIT 0x96 PERM 012) */
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
    lut36.push_back(ctx.genrate_lut(lut36idx1));
    flut36.push_back(lut36idx1);
    auto fvec36 = [flut36](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut36[i](I));
        return ret;
    };

    std::cerr << "\rLUT36   ";
    Ciphertext gin36 = 1 * ct_out140 + 2 * ct_out124 + 4 * ct_out132;
    std::vector<Ciphertext> gout36 = ctx.eval_lut_amortized(&gin36, lut36);

    std::vector<RotationPoly> lut37;
    std::vector<long (*)(long)> flut37;
    auto lut37idx0 = [](long I) -> long {
        /* GATE 26 (LUT3 _1200_ INIT 0x96 PERM 012) */
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
    lut37.push_back(ctx.genrate_lut(lut37idx0));
    flut37.push_back(lut37idx0);
    auto lut37idx1 = [](long I) -> long {
        /* GATE 63 (LUT3 _1237_ INIT 0x17 PERM 012) */
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
    lut37.push_back(ctx.genrate_lut(lut37idx1));
    flut37.push_back(lut37idx1);
    auto fvec37 = [flut37](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut37[i](I));
        return ret;
    };

    std::cerr << "\rLUT37   ";
    Ciphertext gin37 = 1 * ct_out113 + 2 * ct_out97 + 4 * ct_out105;
    std::vector<Ciphertext> gout37 = ctx.eval_lut_amortized(&gin37, lut37);

    std::vector<RotationPoly> lut38;
    std::vector<long (*)(long)> flut38;
    auto lut38idx0 = [](long I) -> long {
        /* GATE 164 (LUT3 _1338_ INIT 0x17 PERM 012) */
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
    lut38.push_back(ctx.genrate_lut(lut38idx0));
    flut38.push_back(lut38idx0);
    auto lut38idx1 = [](long I) -> long {
        /* GATE 128 (LUT3 _1302_ INIT 0x96 PERM 012) */
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
    lut38.push_back(ctx.genrate_lut(lut38idx1));
    flut38.push_back(lut38idx1);
    auto fvec38 = [flut38](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut38[i](I));
        return ret;
    };

    std::cerr << "\rLUT38   ";
    Ciphertext gin38 = 1 * ct_out187 + 2 * ct_out171 + 4 * ct_out179;
    std::vector<Ciphertext> gout38 = ctx.eval_lut_amortized(&gin38, lut38);

    std::vector<RotationPoly> lut39;
    std::vector<long (*)(long)> flut39;
    auto lut39idx0 = [](long I) -> long {
        /* GATE 27 (LUT3 _1201_ INIT 0x96 PERM 012) */
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
    lut39.push_back(ctx.genrate_lut(lut39idx0));
    flut39.push_back(lut39idx0);
    auto lut39idx1 = [](long I) -> long {
        /* GATE 68 (LUT3 _1242_ INIT 0x17 PERM 012) */
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
    lut39.push_back(ctx.genrate_lut(lut39idx1));
    flut39.push_back(lut39idx1);
    auto fvec39 = [flut39](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut39[i](I));
        return ret;
    };

    std::cerr << "\rLUT39   ";
    Ciphertext gin39 = 1 * ct_out137 + 2 * ct_out121 + 4 * ct_out129;
    std::vector<Ciphertext> gout39 = ctx.eval_lut_amortized(&gin39, lut39);

    std::vector<RotationPoly> lut40;
    std::vector<long (*)(long)> flut40;
    auto lut40idx0 = [](long I) -> long {
        /* GATE 178 (LUT3 _1352_ INIT 0x96 PERM 012) */
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
    lut40.push_back(ctx.genrate_lut(lut40idx0));
    flut40.push_back(lut40idx0);
    auto lut40idx1 = [](long I) -> long {
        /* GATE 223 (LUT3 _1397_ INIT 0x17 PERM 012) */
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
    lut40.push_back(ctx.genrate_lut(lut40idx1));
    flut40.push_back(lut40idx1);
    auto fvec40 = [flut40](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut40[i](I));
        return ret;
    };

    std::cerr << "\rLUT40   ";
    Ciphertext gin40 = 1 * ct_out68 + 2 * ct_out52 + 4 * ct_out60;
    std::vector<Ciphertext> gout40 = ctx.eval_lut_amortized(&gin40, lut40);

    std::vector<RotationPoly> lut41;
    std::vector<long (*)(long)> flut41;
    auto lut41idx0 = [](long I) -> long {
        /* GATE 51 (LUT3 _1225_ INIT 0x17 PERM 012) */
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
    lut41.push_back(ctx.genrate_lut(lut41idx0));
    flut41.push_back(lut41idx0);
    auto lut41idx1 = [](long I) -> long {
        /* GATE 14 (LUT3 _1188_ INIT 0x96 PERM 012) */
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
    lut41.push_back(ctx.genrate_lut(lut41idx1));
    flut41.push_back(lut41idx1);
    auto fvec41 = [flut41](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut41[i](I));
        return ret;
    };

    std::cerr << "\rLUT41   ";
    Ciphertext gin41 = 1 * ct_out88 + 2 * ct_out72 + 4 * ct_out80;
    std::vector<Ciphertext> gout41 = ctx.eval_lut_amortized(&gin41, lut41);

    std::vector<RotationPoly> lut42;
    std::vector<long (*)(long)> flut42;
    auto lut42idx0 = [](long I) -> long {
        /* GATE 30 (LUT3 _1204_ INIT 0x17 PERM 012) */
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
    lut42.push_back(ctx.genrate_lut(lut42idx0));
    flut42.push_back(lut42idx0);
    auto lut42idx1 = [](long I) -> long {
        /* GATE 6 (LUT3 _1180_ INIT 0x96 PERM 012) */
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
    lut42.push_back(ctx.genrate_lut(lut42idx1));
    flut42.push_back(lut42idx1);
    auto fvec42 = [flut42](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut42[i](I));
        return ret;
    };

    std::cerr << "\rLUT42   ";
    Ciphertext gin42 = 1 * ct_out136 + 2 * ct_out120 + 4 * ct_out128;
    std::vector<Ciphertext> gout42 = ctx.eval_lut_amortized(&gin42, lut42);

    std::vector<RotationPoly> lut43;
    std::vector<long (*)(long)> flut43;
    auto lut43idx0 = [](long I) -> long {
        /* GATE 248 (LUT3 _1422_ INIT 0x96 PERM 012) */
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
    lut43.push_back(ctx.genrate_lut(lut43idx0));
    flut43.push_back(lut43idx0);
    auto lut43idx1 = [](long I) -> long {
        /* GATE 300 (LUT3 _1474_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
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
    Ciphertext gin43 = 1 * gout14[1] + 2 * gout35[0] + 4 * gout0[1];
    std::vector<Ciphertext> gout43 = ctx.eval_lut_amortized(&gin43, lut43);

    std::vector<RotationPoly> lut44;
    std::vector<long (*)(long)> flut44;
    auto lut44idx0 = [](long I) -> long {
        /* GATE 157 (LUT3 _1331_ INIT 0x17 PERM 012) */
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
    lut44.push_back(ctx.genrate_lut(lut44idx0));
    flut44.push_back(lut44idx0);
    auto lut44idx1 = [](long I) -> long {
        /* GATE 134 (LUT3 _1308_ INIT 0x96 PERM 012) */
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
    lut44.push_back(ctx.genrate_lut(lut44idx1));
    flut44.push_back(lut44idx1);
    auto fvec44 = [flut44](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut44[i](I));
        return ret;
    };

    std::cerr << "\rLUT44   ";
    Ciphertext gin44 = 1 * ct_out163 + 2 * ct_out147 + 4 * ct_out155;
    std::vector<Ciphertext> gout44 = ctx.eval_lut_amortized(&gin44, lut44);

    std::vector<RotationPoly> lut45;
    std::vector<long (*)(long)> flut45;
    auto lut45idx0 = [](long I) -> long {
        /* GATE 111 (LUT3 _1285_ INIT 0x69 PERM 012) */
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
    lut45.push_back(ctx.genrate_lut(lut45idx0));
    flut45.push_back(lut45idx0);
    auto lut45idx1 = [](long I) -> long {
        /* GATE 182 (LUT3 _1356_ INIT 0x2b PERM 012) */
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
    lut45.push_back(ctx.genrate_lut(lut45idx1));
    flut45.push_back(lut45idx1);
    auto fvec45 = [flut45](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut45[i](I));
        return ret;
    };

    std::cerr << "\rLUT45   ";
    Ciphertext gin45 = 1 * gout26[1] + 2 * gout2[1] + 4 * gout30[0];
    std::vector<Ciphertext> gout45 = ctx.eval_lut_amortized(&gin45, lut45);

    std::vector<RotationPoly> lut46;
    std::vector<long (*)(long)> flut46;
    auto lut46idx0 = [](long I) -> long {
        /* GATE 304 (LUT3 _1478_ INIT 0x96 PERM 012) */
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
    lut46.push_back(ctx.genrate_lut(lut46idx0));
    flut46.push_back(lut46idx0);
    auto lut46idx1 = [](long I) -> long {
        /* GATE 348 (LUT3 _1522_ INIT 0x17 PERM 012) */
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
    lut46.push_back(ctx.genrate_lut(lut46idx1));
    flut46.push_back(lut46idx1);
    auto fvec46 = [flut46](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut46[i](I));
        return ret;
    };

    std::cerr << "\rLUT46   ";
    Ciphertext gin46 = 1 * ct_out23 + 2 * ct_out7 + 4 * ct_out15;
    std::vector<Ciphertext> gout46 = ctx.eval_lut_amortized(&gin46, lut46);

    std::vector<RotationPoly> lut47;
    std::vector<long (*)(long)> flut47;
    auto lut47idx0 = [](long I) -> long {
        /* GATE 41 (LUT3 _1215_ INIT 0x96 PERM 012) */
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
    lut47.push_back(ctx.genrate_lut(lut47idx0));
    flut47.push_back(lut47idx0);
    auto lut47idx1 = [](long I) -> long {
        /* GATE 81 (LUT3 _1255_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
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
    Ciphertext gin47 = 1 * gout34[1] + 2 * gout19[0] + 4 * gout25[0];
    std::vector<Ciphertext> gout47 = ctx.eval_lut_amortized(&gin47, lut47);

    std::vector<RotationPoly> lut48;
    std::vector<long (*)(long)> flut48;
    auto lut48idx0 = [](long I) -> long {
        /* GATE 210 (LUT3 _1384_ INIT 0x17 PERM 012) */
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
    lut48.push_back(ctx.genrate_lut(lut48idx0));
    flut48.push_back(lut48idx0);
    auto lut48idx1 = [](long I) -> long {
        /* GATE 165 (LUT3 _1339_ INIT 0x96 PERM 012) */
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
    lut48.push_back(ctx.genrate_lut(lut48idx1));
    flut48.push_back(lut48idx1);
    auto fvec48 = [flut48](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut48[i](I));
        return ret;
    };

    std::cerr << "\rLUT48   ";
    Ciphertext gin48 = 1 * ct_out188 + 2 * ct_out172 + 4 * ct_out180;
    std::vector<Ciphertext> gout48 = ctx.eval_lut_amortized(&gin48, lut48);

    std::vector<RotationPoly> lut49;
    std::vector<long (*)(long)> flut49;
    auto lut49idx0 = [](long I) -> long {
        /* GATE 85 (LUT3 _1259_ INIT 0x96 PERM 012) */
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
    lut49.push_back(ctx.genrate_lut(lut49idx0));
    flut49.push_back(lut49idx0);
    auto lut49idx1 = [](long I) -> long {
        /* GATE 117 (LUT3 _1291_ INIT 0x17 PERM 012) */
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
    lut49.push_back(ctx.genrate_lut(lut49idx1));
    flut49.push_back(lut49idx1);
    auto fvec49 = [flut49](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut49[i](I));
        return ret;
    };

    std::cerr << "\rLUT49   ";
    Ciphertext gin49 = 1 * ct_out42 + 2 * ct_out26 + 4 * ct_out34;
    std::vector<Ciphertext> gout49 = ctx.eval_lut_amortized(&gin49, lut49);

    std::vector<RotationPoly> lut50;
    std::vector<long (*)(long)> flut50;
    auto lut50idx0 = [](long I) -> long {
        /* GATE 275 (LUT3 _1449_ INIT 0x17 PERM 012) */
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
    lut50.push_back(ctx.genrate_lut(lut50idx0));
    flut50.push_back(lut50idx0);
    auto lut50idx1 = [](long I) -> long {
        /* GATE 225 (LUT3 _1399_ INIT 0x96 PERM 012) */
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
    lut50.push_back(ctx.genrate_lut(lut50idx1));
    flut50.push_back(lut50idx1);
    auto fvec50 = [flut50](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut50[i](I));
        return ret;
    };

    std::cerr << "\rLUT50   ";
    Ciphertext gin50 = 1 * ct_out93 + 2 * ct_out77 + 4 * ct_out85;
    std::vector<Ciphertext> gout50 = ctx.eval_lut_amortized(&gin50, lut50);

    std::vector<RotationPoly> lut51;
    std::vector<long (*)(long)> flut51;
    auto lut51idx0 = [](long I) -> long {
        /* GATE 116 (LUT3 _1290_ INIT 0x96 PERM 012) */
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
    lut51.push_back(ctx.genrate_lut(lut51idx0));
    flut51.push_back(lut51idx0);
    auto lut51idx1 = [](long I) -> long {
        /* GATE 171 (LUT3 _1345_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
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
    Ciphertext gin51 = 1 * gout49[1] + 2 * gout11[0] + 4 * gout31[0];
    std::vector<Ciphertext> gout51 = ctx.eval_lut_amortized(&gin51, lut51);

    std::vector<RotationPoly> lut52;
    std::vector<long (*)(long)> flut52;
    auto lut52idx0 = [](long I) -> long {
        /* GATE 138 (LUT3 _1312_ INIT 0x17 PERM 012) */
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
    lut52.push_back(ctx.genrate_lut(lut52idx0));
    flut52.push_back(lut52idx0);
    auto lut52idx1 = [](long I) -> long {
        /* GATE 64 (LUT3 _1238_ INIT 0x96 PERM 012) */
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
    lut52.push_back(ctx.genrate_lut(lut52idx1));
    flut52.push_back(lut52idx1);
    auto fvec52 = [flut52](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut52[i](I));
        return ret;
    };

    std::cerr << "\rLUT52   ";
    Ciphertext gin52 = 1 * ct_out114 + 2 * ct_out98 + 4 * ct_out106;
    std::vector<Ciphertext> gout52 = ctx.eval_lut_amortized(&gin52, lut52);

    std::vector<RotationPoly> lut53;
    std::vector<long (*)(long)> flut53;
    auto lut53idx0 = [](long I) -> long {
        /* GATE 35 (LUT3 _1209_ INIT 0x17 PERM 012) */
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
    lut53.push_back(ctx.genrate_lut(lut53idx0));
    flut53.push_back(lut53idx0);
    auto lut53idx1 = [](long I) -> long {
        /* GATE 9 (LUT3 _1183_ INIT 0x96 PERM 012) */
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
    lut53.push_back(ctx.genrate_lut(lut53idx1));
    flut53.push_back(lut53idx1);
    auto fvec53 = [flut53](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut53[i](I));
        return ret;
    };

    std::cerr << "\rLUT53   ";
    Ciphertext gin53 = 1 * ct_out184 + 2 * ct_out168 + 4 * ct_out176;
    std::vector<Ciphertext> gout53 = ctx.eval_lut_amortized(&gin53, lut53);

    std::vector<RotationPoly> lut54;
    std::vector<long (*)(long)> flut54;
    auto lut54idx0 = [](long I) -> long {
        /* GATE 8 (LUT2 _1182_ INIT 0x6 PERM 01) */
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
    lut54.push_back(ctx.genrate_lut(lut54idx0));
    flut54.push_back(lut54idx0);
    auto lut54idx1 = [](long I) -> long {
        /* GATE 33 (LUT2 _1207_ INIT 0x8 PERM 01) */
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
    lut54.push_back(ctx.genrate_lut(lut54idx1));
    flut54.push_back(lut54idx1);
    auto fvec54 = [flut54](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut54[i](I));
        return ret;
    };

    std::cerr << "\rLUT54   ";
    Ciphertext gin54 = 1 * gout53[1] + 2 * gout19[1];
    std::vector<Ciphertext> gout54 = ctx.eval_lut_amortized(&gin54, lut54);

    std::vector<RotationPoly> lut55;
    std::vector<long (*)(long)> flut55;
    auto lut55idx0 = [](long I) -> long {
        /* GATE 151 (LUT3 _1325_ INIT 0x71 PERM 021) */
        switch (I) {
            case  0: return 1;
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
    lut55.push_back(ctx.genrate_lut(lut55idx0));
    flut55.push_back(lut55idx0);
    auto lut55idx1 = [](long I) -> long {
        /* GATE 136 (LUT3 _1310_ INIT 0x69 PERM 012) */
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
    lut55.push_back(ctx.genrate_lut(lut55idx1));
    flut55.push_back(lut55idx1);
    auto fvec55 = [flut55](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut55[i](I));
        return ret;
    };

    std::cerr << "\rLUT55   ";
    Ciphertext gin55 = 1 * gout27[0] + 2 * gout52[0] + 4 * gout18[1];
    std::vector<Ciphertext> gout55 = ctx.eval_lut_amortized(&gin55, lut55);

    std::vector<RotationPoly> lut56;
    std::vector<long (*)(long)> flut56;
    auto lut56idx0 = [](long I) -> long {
        /* GATE 349 (LUT3 _1523_ INIT 0x17 PERM 012) */
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
    lut56.push_back(ctx.genrate_lut(lut56idx0));
    flut56.push_back(lut56idx0);
    auto lut56idx1 = [](long I) -> long {
        /* GATE 313 (LUT3 _1487_ INIT 0x96 PERM 012) */
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
    lut56.push_back(ctx.genrate_lut(lut56idx1));
    flut56.push_back(lut56idx1);
    auto fvec56 = [flut56](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut56[i](I));
        return ret;
    };

    std::cerr << "\rLUT56   ";
    Ciphertext gin56 = 1 * ct_out47 + 2 * ct_out31 + 4 * ct_out39;
    std::vector<Ciphertext> gout56 = ctx.eval_lut_amortized(&gin56, lut56);

    std::vector<RotationPoly> lut57;
    std::vector<long (*)(long)> flut57;
    auto lut57idx0 = [](long I) -> long {
        /* GATE 316 (LUT3 _1490_ INIT 0x96 PERM 012) */
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
    lut57.push_back(ctx.genrate_lut(lut57idx0));
    flut57.push_back(lut57idx0);
    auto lut57idx1 = [](long I) -> long {
        /* GATE 350 (LUT3 _1524_ INIT 0x17 PERM 012) */
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
    lut57.push_back(ctx.genrate_lut(lut57idx1));
    flut57.push_back(lut57idx1);
    auto fvec57 = [flut57](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut57[i](I));
        return ret;
    };

    std::cerr << "\rLUT57   ";
    Ciphertext gin57 = 1 * ct_out71 + 2 * ct_out55 + 4 * ct_out63;
    std::vector<Ciphertext> gout57 = ctx.eval_lut_amortized(&gin57, lut57);

    std::vector<RotationPoly> lut58;
    std::vector<long (*)(long)> flut58;
    auto lut58idx0 = [](long I) -> long {
        /* GATE 220 (LUT3 _1394_ INIT 0x17 PERM 012) */
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
    lut58.push_back(ctx.genrate_lut(lut58idx0));
    flut58.push_back(lut58idx0);
    auto lut58idx1 = [](long I) -> long {
        /* GATE 166 (LUT3 _1340_ INIT 0x96 PERM 012) */
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
    lut58.push_back(ctx.genrate_lut(lut58idx1));
    flut58.push_back(lut58idx1);
    auto fvec58 = [flut58](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut58[i](I));
        return ret;
    };

    std::cerr << "\rLUT58   ";
    Ciphertext gin58 = 1 * ct_out20 + 2 * ct_out4 + 4 * ct_out12;
    std::vector<Ciphertext> gout58 = ctx.eval_lut_amortized(&gin58, lut58);

    std::vector<RotationPoly> lut59;
    std::vector<long (*)(long)> flut59;
    auto lut59idx0 = [](long I) -> long {
        /* GATE 297 (LUT3 _1471_ INIT 0x96 PERM 012) */
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
    lut59.push_back(ctx.genrate_lut(lut59idx0));
    flut59.push_back(lut59idx0);
    auto lut59idx1 = [](long I) -> long {
        /* GATE 335 (LUT3 _1509_ INIT 0x17 PERM 012) */
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
    lut59.push_back(ctx.genrate_lut(lut59idx1));
    flut59.push_back(lut59idx1);
    auto fvec59 = [flut59](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut59[i](I));
        return ret;
    };

    std::cerr << "\rLUT59   ";
    Ciphertext gin59 = 1 * ct_out167 + 2 * ct_out151 + 4 * ct_out159;
    std::vector<Ciphertext> gout59 = ctx.eval_lut_amortized(&gin59, lut59);

    std::vector<RotationPoly> lut60;
    std::vector<long (*)(long)> flut60;
    auto lut60idx0 = [](long I) -> long {
        /* GATE 291 (LUT3 _1465_ INIT 0x17 PERM 012) */
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
    lut60.push_back(ctx.genrate_lut(lut60idx0));
    flut60.push_back(lut60idx0);
    auto lut60idx1 = [](long I) -> long {
        /* GATE 246 (LUT3 _1420_ INIT 0x96 PERM 012) */
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
    lut60.push_back(ctx.genrate_lut(lut60idx1));
    flut60.push_back(lut60idx1);
    auto fvec60 = [flut60](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut60[i](I));
        return ret;
    };

    std::cerr << "\rLUT60   ";
    Ciphertext gin60 = 1 * ct_out118 + 2 * ct_out102 + 4 * ct_out110;
    std::vector<Ciphertext> gout60 = ctx.eval_lut_amortized(&gin60, lut60);

    std::vector<RotationPoly> lut61;
    std::vector<long (*)(long)> flut61;
    auto lut61idx0 = [](long I) -> long {
        /* GATE 301 (LUT3 _1475_ INIT 0x69 PERM 012) */
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
    lut61.push_back(ctx.genrate_lut(lut61idx0));
    flut61.push_back(lut61idx0);
    auto lut61idx1 = [](long I) -> long {
        /* GATE 338 (LUT3 _1512_ INIT 0x2b PERM 012) */
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
    lut61.push_back(ctx.genrate_lut(lut61idx1));
    flut61.push_back(lut61idx1);
    auto fvec61 = [flut61](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut61[i](I));
        return ret;
    };

    std::cerr << "\rLUT61   ";
    Ciphertext gin61 = 1 * gout29[0] + 2 * gout28[0] + 4 * gout46[0];
    std::vector<Ciphertext> gout61 = ctx.eval_lut_amortized(&gin61, lut61);

    std::vector<RotationPoly> lut62;
    std::vector<long (*)(long)> flut62;
    auto lut62idx0 = [](long I) -> long {
        /* GATE 84 (LUT3 _1258_ INIT 0x17 PERM 012) */
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
    lut62.push_back(ctx.genrate_lut(lut62idx0));
    flut62.push_back(lut62idx0);
    auto lut62idx1 = [](long I) -> long {
        /* GATE 37 (LUT3 _1211_ INIT 0x96 PERM 012) */
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
    lut62.push_back(ctx.genrate_lut(lut62idx1));
    flut62.push_back(lut62idx1);
    auto fvec62 = [flut62](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut62[i](I));
        return ret;
    };

    std::cerr << "\rLUT62   ";
    Ciphertext gin62 = 1 * ct_out17 + 2 * ct_out1 + 4 * ct_out9;
    std::vector<Ciphertext> gout62 = ctx.eval_lut_amortized(&gin62, lut62);

    std::vector<RotationPoly> lut63;
    std::vector<long (*)(long)> flut63;
    auto lut63idx0 = [](long I) -> long {
        /* GATE 31 (LUT3 _1205_ INIT 0x96 PERM 012) */
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
    lut63.push_back(ctx.genrate_lut(lut63idx0));
    flut63.push_back(lut63idx0);
    auto lut63idx1 = [](long I) -> long {
        /* GATE 67 (LUT3 _1241_ INIT 0x17 PERM 012) */
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
    lut63.push_back(ctx.genrate_lut(lut63idx1));
    flut63.push_back(lut63idx1);
    auto fvec63 = [flut63](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut63[i](I));
        return ret;
    };

    std::cerr << "\rLUT63   ";
    Ciphertext gin63 = 1 * ct_out161 + 2 * ct_out145 + 4 * ct_out153;
    std::vector<Ciphertext> gout63 = ctx.eval_lut_amortized(&gin63, lut63);

    std::vector<RotationPoly> lut64;
    std::vector<long (*)(long)> flut64;
    auto lut64idx0 = [](long I) -> long {
        /* GATE 36 (LUT3 _1210_ INIT 0x96 PERM 012) */
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
    lut64.push_back(ctx.genrate_lut(lut64idx0));
    flut64.push_back(lut64idx0);
    auto lut64idx1 = [](long I) -> long {
        /* GATE 74 (LUT3 _1248_ INIT 0x17 PERM 012) */
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
    lut64.push_back(ctx.genrate_lut(lut64idx1));
    flut64.push_back(lut64idx1);
    auto fvec64 = [flut64](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut64[i](I));
        return ret;
    };

    std::cerr << "\rLUT64   ";
    Ciphertext gin64 = 1 * ct_out185 + 2 * ct_out169 + 4 * ct_out177;
    std::vector<Ciphertext> gout64 = ctx.eval_lut_amortized(&gin64, lut64);

    std::vector<RotationPoly> lut65;
    std::vector<long (*)(long)> flut65;
    auto lut65idx0 = [](long I) -> long {
        /* GATE 315 (LUT3 _1489_ INIT 0x17 PERM 012) */
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
    lut65.push_back(ctx.genrate_lut(lut65idx0));
    flut65.push_back(lut65idx0);
    auto lut65idx1 = [](long I) -> long {
        /* GATE 270 (LUT3 _1444_ INIT 0x96 PERM 012) */
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
    lut65.push_back(ctx.genrate_lut(lut65idx1));
    flut65.push_back(lut65idx1);
    auto fvec65 = [flut65](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut65[i](I));
        return ret;
    };

    std::cerr << "\rLUT65   ";
    Ciphertext gin65 = 1 * ct_out70 + 2 * ct_out54 + 4 * ct_out62;
    std::vector<Ciphertext> gout65 = ctx.eval_lut_amortized(&gin65, lut65);

    std::vector<RotationPoly> lut66;
    std::vector<long (*)(long)> flut66;
    auto lut66idx0 = [](long I) -> long {
        /* GATE 200 (LUT3 _1374_ INIT 0x96 PERM 012) */
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
    lut66.push_back(ctx.genrate_lut(lut66idx0));
    flut66.push_back(lut66idx0);
    auto lut66idx1 = [](long I) -> long {
        /* GATE 245 (LUT3 _1419_ INIT 0x17 PERM 012) */
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
    lut66.push_back(ctx.genrate_lut(lut66idx1));
    flut66.push_back(lut66idx1);
    auto fvec66 = [flut66](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut66[i](I));
        return ret;
    };

    std::cerr << "\rLUT66   ";
    Ciphertext gin66 = 1 * ct_out117 + 2 * ct_out101 + 4 * ct_out109;
    std::vector<Ciphertext> gout66 = ctx.eval_lut_amortized(&gin66, lut66);

    std::vector<RotationPoly> lut67;
    std::vector<long (*)(long)> flut67;
    auto lut67idx0 = [](long I) -> long {
        /* GATE 75 (LUT3 _1249_ INIT 0x96 PERM 012) */
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
    lut67.push_back(ctx.genrate_lut(lut67idx0));
    flut67.push_back(lut67idx0);
    auto lut67idx1 = [](long I) -> long {
        /* GATE 127 (LUT3 _1301_ INIT 0x17 PERM 012) */
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
    lut67.push_back(ctx.genrate_lut(lut67idx1));
    flut67.push_back(lut67idx1);
    auto fvec67 = [flut67](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut67[i](I));
        return ret;
    };

    std::cerr << "\rLUT67   ";
    Ciphertext gin67 = 1 * ct_out186 + 2 * ct_out170 + 4 * ct_out178;
    std::vector<Ciphertext> gout67 = ctx.eval_lut_amortized(&gin67, lut67);

    std::vector<RotationPoly> lut68;
    std::vector<long (*)(long)> flut68;
    auto lut68idx0 = [](long I) -> long {
        /* GATE 13 (LUT3 _1187_ INIT 0x96 PERM 012) */
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
    lut68.push_back(ctx.genrate_lut(lut68idx0));
    flut68.push_back(lut68idx0);
    auto lut68idx1 = [](long I) -> long {
        /* GATE 46 (LUT3 _1220_ INIT 0x17 PERM 012) */
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
    lut68.push_back(ctx.genrate_lut(lut68idx1));
    flut68.push_back(lut68idx1);
    auto fvec68 = [flut68](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut68[i](I));
        return ret;
    };

    std::cerr << "\rLUT68   ";
    Ciphertext gin68 = 1 * ct_out64 + 2 * ct_out48 + 4 * ct_out56;
    std::vector<Ciphertext> gout68 = ctx.eval_lut_amortized(&gin68, lut68);

    std::vector<RotationPoly> lut69;
    std::vector<long (*)(long)> flut69;
    auto lut69idx0 = [](long I) -> long {
        /* GATE 61 (LUT3 _1235_ INIT 0x2b PERM 012) */
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
    lut69.push_back(ctx.genrate_lut(lut69idx0));
    flut69.push_back(lut69idx0);
    auto lut69idx1 = [](long I) -> long {
        /* GATE 24 (LUT3 _1198_ INIT 0x69 PERM 012) */
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
    lut69.push_back(ctx.genrate_lut(lut69idx1));
    flut69.push_back(lut69idx1);
    auto fvec69 = [flut69](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut69[i](I));
        return ret;
    };

    std::cerr << "\rLUT69   ";
    Ciphertext gin69 = 1 * gout17[0] + 2 * gout37[0] + 4 * gout39[0];
    std::vector<Ciphertext> gout69 = ctx.eval_lut_amortized(&gin69, lut69);

    std::vector<RotationPoly> lut70;
    std::vector<long (*)(long)> flut70;
    auto lut70idx0 = [](long I) -> long {
        /* GATE 253 (LUT3 _1427_ INIT 0x2b PERM 012) */
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
    lut70.push_back(ctx.genrate_lut(lut70idx0));
    flut70.push_back(lut70idx0);
    auto lut70idx1 = [](long I) -> long {
        /* GATE 209 (LUT3 _1383_ INIT 0x69 PERM 012) */
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
    lut70.push_back(ctx.genrate_lut(lut70idx1));
    flut70.push_back(lut70idx1);
    auto fvec70 = [flut70](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut70[i](I));
        return ret;
    };

    std::cerr << "\rLUT70   ";
    Ciphertext gin70 = 1 * gout48[0] + 2 * gout33[0] + 4 * gout8[1];
    std::vector<Ciphertext> gout70 = ctx.eval_lut_amortized(&gin70, lut70);

    std::vector<RotationPoly> lut71;
    std::vector<long (*)(long)> flut71;
    auto lut71idx0 = [](long I) -> long {
        /* GATE 219 (LUT3 _1393_ INIT 0x17 PERM 012) */
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
    lut71.push_back(ctx.genrate_lut(lut71idx0));
    flut71.push_back(lut71idx0);
    auto lut71idx1 = [](long I) -> long {
        /* GATE 175 (LUT3 _1349_ INIT 0x96 PERM 012) */
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
    lut71.push_back(ctx.genrate_lut(lut71idx1));
    flut71.push_back(lut71idx1);
    auto fvec71 = [flut71](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut71[i](I));
        return ret;
    };

    std::cerr << "\rLUT71   ";
    Ciphertext gin71 = 1 * ct_out44 + 2 * ct_out28 + 4 * ct_out36;
    std::vector<Ciphertext> gout71 = ctx.eval_lut_amortized(&gin71, lut71);

    std::vector<RotationPoly> lut72;
    std::vector<long (*)(long)> flut72;
    auto lut72idx0 = [](long I) -> long {
        /* GATE 82 (LUT3 _1256_ INIT 0x96 PERM 012) */
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
    lut72.push_back(ctx.genrate_lut(lut72idx0));
    flut72.push_back(lut72idx0);
    auto lut72idx1 = [](long I) -> long {
        /* GATE 115 (LUT3 _1289_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
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
    Ciphertext gin72 = 1 * gout25[1] + 2 * gout62[0] + 4 * gout49[0];
    std::vector<Ciphertext> gout72 = ctx.eval_lut_amortized(&gin72, lut72);

    std::vector<RotationPoly> lut73;
    std::vector<long (*)(long)> flut73;
    auto lut73idx0 = [](long I) -> long {
        /* GATE 224 (LUT3 _1398_ INIT 0x96 PERM 012) */
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
    lut73.push_back(ctx.genrate_lut(lut73idx0));
    flut73.push_back(lut73idx0);
    auto lut73idx1 = [](long I) -> long {
        /* GATE 269 (LUT3 _1443_ INIT 0x17 PERM 012) */
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
    lut73.push_back(ctx.genrate_lut(lut73idx1));
    flut73.push_back(lut73idx1);
    auto fvec73 = [flut73](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut73[i](I));
        return ret;
    };

    std::cerr << "\rLUT73   ";
    Ciphertext gin73 = 1 * ct_out69 + 2 * ct_out53 + 4 * ct_out61;
    std::vector<Ciphertext> gout73 = ctx.eval_lut_amortized(&gin73, lut73);

    std::vector<RotationPoly> lut74;
    std::vector<long (*)(long)> flut74;
    auto lut74idx0 = [](long I) -> long {
        /* GATE 320 (LUT3 _1494_ INIT 0x2b PERM 012) */
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
    lut74.push_back(ctx.genrate_lut(lut74idx0));
    flut74.push_back(lut74idx0);
    auto lut74idx1 = [](long I) -> long {
        /* GATE 268 (LUT3 _1442_ INIT 0x69 PERM 012) */
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
    lut74.push_back(ctx.genrate_lut(lut74idx1));
    flut74.push_back(lut74idx1);
    auto fvec74 = [flut74](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut74[i](I));
        return ret;
    };

    std::cerr << "\rLUT74   ";
    Ciphertext gin74 = 1 * gout73[1] + 2 * gout65[1] + 4 * gout15[0];
    std::vector<Ciphertext> gout74 = ctx.eval_lut_amortized(&gin74, lut74);

    std::vector<RotationPoly> lut75;
    std::vector<long (*)(long)> flut75;
    auto lut75idx0 = [](long I) -> long {
        /* GATE 354 (LUT3 _1528_ INIT 0x2b PERM 012) */
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
    lut75.push_back(ctx.genrate_lut(lut75idx0));
    flut75.push_back(lut75idx0);
    auto lut75idx1 = [](long I) -> long {
        /* GATE 314 (LUT3 _1488_ INIT 0x69 PERM 012) */
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
    lut75.push_back(ctx.genrate_lut(lut75idx1));
    flut75.push_back(lut75idx1);
    auto fvec75 = [flut75](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut75[i](I));
        return ret;
    };

    std::cerr << "\rLUT75   ";
    Ciphertext gin75 = 1 * gout65[0] + 2 * gout57[0] + 4 * gout3[1];
    std::vector<Ciphertext> gout75 = ctx.eval_lut_amortized(&gin75, lut75);

    std::vector<RotationPoly> lut76;
    std::vector<long (*)(long)> flut76;
    auto lut76idx0 = [](long I) -> long {
        /* GATE 290 (LUT3 _1464_ INIT 0x69 PERM 012) */
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
    lut76.push_back(ctx.genrate_lut(lut76idx0));
    flut76.push_back(lut76idx0);
    auto lut76idx1 = [](long I) -> long {
        /* GATE 331 (LUT3 _1505_ INIT 0x2b PERM 012) */
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
    lut76.push_back(ctx.genrate_lut(lut76idx1));
    flut76.push_back(lut76idx1);
    auto fvec76 = [flut76](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut76[i](I));
        return ret;
    };

    std::cerr << "\rLUT76   ";
    Ciphertext gin76 = 1 * gout60[0] + 2 * gout4[0] + 4 * gout23[0];
    std::vector<Ciphertext> gout76 = ctx.eval_lut_amortized(&gin76, lut76);

    std::vector<RotationPoly> lut77;
    std::vector<long (*)(long)> flut77;
    auto lut77idx0 = [](long I) -> long {
        /* GATE 50 (LUT2 _1224_ INIT 0x8 PERM 01) */
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
    auto lut77idx1 = [](long I) -> long {
        /* GATE 12 (LUT2 _1186_ INIT 0x6 PERM 01) */
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
    lut77.push_back(ctx.genrate_lut(lut77idx1));
    flut77.push_back(lut77idx1);
    auto fvec77 = [flut77](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut77[i](I));
        return ret;
    };

    std::cerr << "\rLUT77   ";
    Ciphertext gin77 = 1 * gout68[0] + 2 * gout41[1];
    std::vector<Ciphertext> gout77 = ctx.eval_lut_amortized(&gin77, lut77);

    std::vector<RotationPoly> lut78;
    std::vector<long (*)(long)> flut78;
    auto lut78idx0 = [](long I) -> long {
        /* GATE 254 (LUT3 _1428_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut78.push_back(ctx.genrate_lut(lut78idx0));
    flut78.push_back(lut78idx0);
    auto lut78idx1 = [](long I) -> long {
        /* GATE 202 (LUT3 _1376_ INIT 0x96 PERM 012) */
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
    lut78.push_back(ctx.genrate_lut(lut78idx1));
    flut78.push_back(lut78idx1);
    auto fvec78 = [flut78](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut78[i](I));
        return ret;
    };

    std::cerr << "\rLUT78   ";
    Ciphertext gin78 = 1 * gout20[1] + 2 * gout36[0] + 4 * gout14[0];
    std::vector<Ciphertext> gout78 = ctx.eval_lut_amortized(&gin78, lut78);

    std::vector<RotationPoly> lut79;
    std::vector<long (*)(long)> flut79;
    auto lut79idx0 = [](long I) -> long {
        /* GATE 294 (LUT3 _1468_ INIT 0x96 PERM 012) */
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
    lut79.push_back(ctx.genrate_lut(lut79idx0));
    flut79.push_back(lut79idx0);
    auto lut79idx1 = [](long I) -> long {
        /* GATE 339 (LUT3 _1513_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut79.push_back(ctx.genrate_lut(lut79idx1));
    flut79.push_back(lut79idx1);
    auto fvec79 = [flut79](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut79[i](I));
        return ret;
    };

    std::cerr << "\rLUT79   ";
    Ciphertext gin79 = 1 * gout0[0] + 2 * gout13[1] + 4 * gout59[0];
    std::vector<Ciphertext> gout79 = ctx.eval_lut_amortized(&gin79, lut79);

    std::vector<RotationPoly> lut80;
    std::vector<long (*)(long)> flut80;
    auto lut80idx0 = [](long I) -> long {
        /* GATE 228 (LUT3 _1402_ INIT 0x2b PERM 012) */
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
    lut80.push_back(ctx.genrate_lut(lut80idx0));
    flut80.push_back(lut80idx0);
    auto lut80idx1 = [](long I) -> long {
        /* GATE 176 (LUT3 _1350_ INIT 0x69 PERM 012) */
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
    lut80.push_back(ctx.genrate_lut(lut80idx1));
    flut80.push_back(lut80idx1);
    auto fvec80 = [flut80](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut80[i](I));
        return ret;
    };

    std::cerr << "\rLUT80   ";
    Ciphertext gin80 = 1 * gout2[0] + 2 * gout40[0] + 4 * gout10[1];
    std::vector<Ciphertext> gout80 = ctx.eval_lut_amortized(&gin80, lut80);

    std::vector<RotationPoly> lut81;
    std::vector<long (*)(long)> flut81;
    auto lut81idx0 = [](long I) -> long {
        /* GATE 39 (LUT2 _1213_ INIT 0x8 PERM 01) */
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
    lut81.push_back(ctx.genrate_lut(lut81idx0));
    flut81.push_back(lut81idx0);
    auto lut81idx1 = [](long I) -> long {
        /* GATE 11 (LUT2 _1185_ INIT 0x6 PERM 01) */
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
    lut81.push_back(ctx.genrate_lut(lut81idx1));
    flut81.push_back(lut81idx1);
    auto fvec81 = [flut81](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut81[i](I));
        return ret;
    };

    std::cerr << "\rLUT81   ";
    Ciphertext gin81 = 1 * gout77[1] + 2 * gout34[0];
    std::vector<Ciphertext> gout81 = ctx.eval_lut_amortized(&gin81, lut81);

    std::vector<RotationPoly> lut82;
    std::vector<long (*)(long)> flut82;
    auto lut82idx0 = [](long I) -> long {
        /* GATE 156 (LUT3 _1330_ INIT 0x96 PERM 012) */
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
    lut82.push_back(ctx.genrate_lut(lut82idx0));
    flut82.push_back(lut82idx0);
    auto lut82idx1 = [](long I) -> long {
        /* GATE 208 (LUT3 _1382_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
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
    Ciphertext gin82 = 1 * gout44[0] + 2 * gout27[1] + 4 * gout20[0];
    std::vector<Ciphertext> gout82 = ctx.eval_lut_amortized(&gin82, lut82);

    std::vector<RotationPoly> lut83;
    std::vector<long (*)(long)> flut83;
    auto lut83idx0 = [](long I) -> long {
        /* GATE 62 (LUT3 _1236_ INIT 0x69 PERM 012) */
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
    lut83.push_back(ctx.genrate_lut(lut83idx0));
    flut83.push_back(lut83idx0);
    auto lut83idx1 = [](long I) -> long {
        /* GATE 135 (LUT3 _1309_ INIT 0x2b PERM 012) */
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
    lut83.push_back(ctx.genrate_lut(lut83idx1));
    flut83.push_back(lut83idx1);
    auto fvec83 = [flut83](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut83[i](I));
        return ret;
    };

    std::cerr << "\rLUT83   ";
    Ciphertext gin83 = 1 * gout37[1] + 2 * gout52[1] + 4 * gout1[0];
    std::vector<Ciphertext> gout83 = ctx.eval_lut_amortized(&gin83, lut83);

    std::vector<RotationPoly> lut84;
    std::vector<long (*)(long)> flut84;
    auto lut84idx0 = [](long I) -> long {
        /* GATE 255 (LUT3 _1429_ INIT 0x69 PERM 012) */
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
    lut84.push_back(ctx.genrate_lut(lut84idx0));
    flut84.push_back(lut84idx0);
    auto lut84idx1 = [](long I) -> long {
        /* GATE 299 (LUT3 _1473_ INIT 0x2b PERM 012) */
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
    lut84.push_back(ctx.genrate_lut(lut84idx1));
    flut84.push_back(lut84idx1);
    auto fvec84 = [flut84](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut84[i](I));
        return ret;
    };

    std::cerr << "\rLUT84   ";
    Ciphertext gin84 = 1 * gout33[1] + 2 * gout29[1] + 4 * gout32[0];
    std::vector<Ciphertext> gout84 = ctx.eval_lut_amortized(&gin84, lut84);

    std::vector<RotationPoly> lut85;
    std::vector<long (*)(long)> flut85;
    auto lut85idx0 = [](long I) -> long {
        /* GATE 4 (LUT2 _1178_ INIT 0x6 PERM 01) */
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
    lut85.push_back(ctx.genrate_lut(lut85idx0));
    flut85.push_back(lut85idx0);
    auto lut85idx1 = [](long I) -> long {
        /* GATE 23 (LUT2 _1197_ INIT 0x8 PERM 01) */
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
    Ciphertext gin85 = 1 * gout17[1] + 2 * gout42[1];
    std::vector<Ciphertext> gout85 = ctx.eval_lut_amortized(&gin85, lut85);

    std::vector<RotationPoly> lut86;
    std::vector<long (*)(long)> flut86;
    auto lut86idx0 = [](long I) -> long {
        /* GATE 73 (LUT3 _1247_ INIT 0x69 PERM 012) */
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
    lut86.push_back(ctx.genrate_lut(lut86idx0));
    flut86.push_back(lut86idx0);
    auto lut86idx1 = [](long I) -> long {
        /* GATE 123 (LUT3 _1297_ INIT 0x2b PERM 012) */
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
    lut86.push_back(ctx.genrate_lut(lut86idx1));
    flut86.push_back(lut86idx1);
    auto fvec86 = [flut86](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut86[i](I));
        return ret;
    };

    std::cerr << "\rLUT86   ";
    Ciphertext gin86 = 1 * gout64[1] + 2 * gout67[0] + 4 * gout11[1];
    std::vector<Ciphertext> gout86 = ctx.eval_lut_amortized(&gin86, lut86);

    std::vector<RotationPoly> lut87;
    std::vector<long (*)(long)> flut87;
    auto lut87idx0 = [](long I) -> long {
        /* GATE 103 (LUT3 _1277_ INIT 0x2b PERM 012) */
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
    lut87.push_back(ctx.genrate_lut(lut87idx0));
    flut87.push_back(lut87idx0);
    auto lut87idx1 = [](long I) -> long {
        /* GATE 86 (LUT3 _1260_ INIT 0x69 PERM 012) */
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
    lut87.push_back(ctx.genrate_lut(lut87idx1));
    flut87.push_back(lut87idx1);
    auto fvec87 = [flut87](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut87[i](I));
        return ret;
    };

    std::cerr << "\rLUT87   ";
    Ciphertext gin87 = 1 * gout7[1] + 2 * gout26[0] + 4 * gout9[1];
    std::vector<Ciphertext> gout87 = ctx.eval_lut_amortized(&gin87, lut87);

    std::vector<RotationPoly> lut88;
    std::vector<long (*)(long)> flut88;
    auto lut88idx0 = [](long I) -> long {
        /* GATE 244 (LUT3 _1418_ INIT 0x69 PERM 012) */
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
    lut88.push_back(ctx.genrate_lut(lut88idx0));
    flut88.push_back(lut88idx0);
    auto lut88idx1 = [](long I) -> long {
        /* GATE 289 (LUT3 _1463_ INIT 0x2b PERM 012) */
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
    lut88.push_back(ctx.genrate_lut(lut88idx1));
    flut88.push_back(lut88idx1);
    auto fvec88 = [flut88](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut88[i](I));
        return ret;
    };

    std::cerr << "\rLUT88   ";
    Ciphertext gin88 = 1 * gout66[1] + 2 * gout60[1] + 4 * gout13[0];
    std::vector<Ciphertext> gout88 = ctx.eval_lut_amortized(&gin88, lut88);

    std::vector<RotationPoly> lut89;
    std::vector<long (*)(long)> flut89;
    auto lut89idx0 = [](long I) -> long {
        /* GATE 162 (LUT3 _1336_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut89.push_back(ctx.genrate_lut(lut89idx0));
    flut89.push_back(lut89idx0);
    auto lut89idx1 = [](long I) -> long {
        /* GATE 131 (LUT3 _1305_ INIT 0x96 PERM 012) */
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
    lut89.push_back(ctx.genrate_lut(lut89idx1));
    flut89.push_back(lut89idx1);
    auto fvec89 = [flut89](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut89[i](I));
        return ret;
    };

    std::cerr << "\rLUT89   ";
    Ciphertext gin89 = 1 * gout16[1] + 2 * gout1[1] + 4 * gout44[1];
    std::vector<Ciphertext> gout89 = ctx.eval_lut_amortized(&gin89, lut89);

    std::vector<RotationPoly> lut90;
    std::vector<long (*)(long)> flut90;
    auto lut90idx0 = [](long I) -> long {
        /* GATE 45 (LUT3 _1219_ INIT 0x69 PERM 012) */
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
    lut90.push_back(ctx.genrate_lut(lut90idx0));
    flut90.push_back(lut90idx0);
    auto lut90idx1 = [](long I) -> long {
        /* GATE 92 (LUT3 _1266_ INIT 0x2b PERM 012) */
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
    lut90.push_back(ctx.genrate_lut(lut90idx1));
    flut90.push_back(lut90idx1);
    auto fvec90 = [flut90](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut90[i](I));
        return ret;
    };

    std::cerr << "\rLUT90   ";
    Ciphertext gin90 = 1 * gout68[1] + 2 * gout7[0] + 4 * gout5[0];
    std::vector<Ciphertext> gout90 = ctx.eval_lut_amortized(&gin90, lut90);

    std::vector<RotationPoly> lut91;
    std::vector<long (*)(long)> flut91;
    auto lut91idx0 = [](long I) -> long {
        /* GATE 264 (LUT3 _1438_ INIT 0x96 PERM 012) */
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
    lut91.push_back(ctx.genrate_lut(lut91idx0));
    flut91.push_back(lut91idx0);
    auto lut91idx1 = [](long I) -> long {
        /* GATE 309 (LUT3 _1483_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
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
    Ciphertext gin91 = 1 * gout24[0] + 2 * gout8[0] + 4 * gout21[1];
    std::vector<Ciphertext> gout91 = ctx.eval_lut_amortized(&gin91, lut91);

    std::vector<RotationPoly> lut92;
    std::vector<long (*)(long)> flut92;
    auto lut92idx0 = [](long I) -> long {
        /* GATE 218 (LUT3 _1392_ INIT 0x96 PERM 012) */
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
    lut92.push_back(ctx.genrate_lut(lut92idx0));
    flut92.push_back(lut92idx0);
    auto lut92idx1 = [](long I) -> long {
        /* GATE 263 (LUT3 _1437_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
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
    Ciphertext gin92 = 1 * gout71[0] + 2 * gout58[0] + 4 * gout24[1];
    std::vector<Ciphertext> gout92 = ctx.eval_lut_amortized(&gin92, lut92);

    std::vector<RotationPoly> lut93;
    std::vector<long (*)(long)> flut93;
    auto lut93idx0 = [](long I) -> long {
        /* GATE 252 (LUT3 _1426_ INIT 0x96 PERM 012) */
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
    lut93.push_back(ctx.genrate_lut(lut93idx0));
    flut93.push_back(lut93idx0);
    auto lut93idx1 = [](long I) -> long {
        /* GATE 307 (LUT3 _1481_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut93.push_back(ctx.genrate_lut(lut93idx1));
    flut93.push_back(lut93idx1);
    auto fvec93 = [flut93](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut93[i](I));
        return ret;
    };

    std::cerr << "\rLUT93   ";
    Ciphertext gin93 = 1 * gout70[0] + 2 * gout78[0] + 4 * gout84[0];
    std::vector<Ciphertext> gout93 = ctx.eval_lut_amortized(&gin93, lut93);

    std::vector<RotationPoly> lut94;
    std::vector<long (*)(long)> flut94;
    auto lut94idx0 = [](long I) -> long {
        /* GATE 298 (LUT3 _1472_ INIT 0x96 PERM 012) */
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
    lut94.push_back(ctx.genrate_lut(lut94idx0));
    flut94.push_back(lut94idx0);
    auto lut94idx1 = [](long I) -> long {
        /* GATE 344 (LUT3 _1518_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
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
    Ciphertext gin94 = 1 * gout84[1] + 2 * gout43[1] + 4 * gout61[0];
    std::vector<Ciphertext> gout94 = ctx.eval_lut_amortized(&gin94, lut94);

    std::vector<RotationPoly> lut95;
    std::vector<long (*)(long)> flut95;
    auto lut95idx0 = [](long I) -> long {
        /* GATE 21 (LUT2 _1195_ INIT 0x8 PERM 01) */
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
    lut95.push_back(ctx.genrate_lut(lut95idx0));
    flut95.push_back(lut95idx0);
    auto lut95idx1 = [](long I) -> long {
        /* GATE 3 (LUT2 _1177_ INIT 0x6 PERM 01) */
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
    lut95.push_back(ctx.genrate_lut(lut95idx1));
    flut95.push_back(lut95idx1);
    auto fvec95 = [flut95](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut95[i](I));
        return ret;
    };

    std::cerr << "\rLUT95   ";
    Ciphertext gin95 = 1 * gout85[0] + 2 * gout22[0];
    std::vector<Ciphertext> gout95 = ctx.eval_lut_amortized(&gin95, lut95);

    std::vector<RotationPoly> lut96;
    std::vector<long (*)(long)> flut96;
    auto lut96idx0 = [](long I) -> long {
        /* GATE 243 (LUT3 _1417_ INIT 0x2b PERM 012) */
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
    lut96.push_back(ctx.genrate_lut(lut96idx0));
    flut96.push_back(lut96idx0);
    auto lut96idx1 = [](long I) -> long {
        /* GATE 198 (LUT3 _1372_ INIT 0x69 PERM 012) */
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
    lut96.push_back(ctx.genrate_lut(lut96idx1));
    flut96.push_back(lut96idx1);
    auto fvec96 = [flut96](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut96[i](I));
        return ret;
    };

    std::cerr << "\rLUT96   ";
    Ciphertext gin96 = 1 * gout12[0] + 2 * gout66[0] + 4 * gout35[1];
    std::vector<Ciphertext> gout96 = ctx.eval_lut_amortized(&gin96, lut96);

    std::vector<RotationPoly> lut97;
    std::vector<long (*)(long)> flut97;
    auto lut97idx0 = [](long I) -> long {
        /* GATE 197 (LUT3 _1371_ INIT 0x2b PERM 012) */
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
    lut97.push_back(ctx.genrate_lut(lut97idx0));
    flut97.push_back(lut97idx0);
    auto lut97idx1 = [](long I) -> long {
        /* GATE 152 (LUT3 _1326_ INIT 0x69 PERM 012) */
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
    lut97.push_back(ctx.genrate_lut(lut97idx1));
    flut97.push_back(lut97idx1);
    auto fvec97 = [flut97](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut97[i](I));
        return ret;
    };

    std::cerr << "\rLUT97   ";
    Ciphertext gin97 = 1 * gout18[0] + 2 * gout12[1] + 4 * gout36[1];
    std::vector<Ciphertext> gout97 = ctx.eval_lut_amortized(&gin97, lut97);

    std::vector<RotationPoly> lut98;
    std::vector<long (*)(long)> flut98;
    auto lut98idx0 = [](long I) -> long {
        /* GATE 71 (LUT3 _1245_ INIT 0x2b PERM 012) */
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
    lut98.push_back(ctx.genrate_lut(lut98idx0));
    flut98.push_back(lut98idx0);
    auto lut98idx1 = [](long I) -> long {
        /* GATE 34 (LUT3 _1208_ INIT 0x69 PERM 012) */
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
    lut98.push_back(ctx.genrate_lut(lut98idx1));
    flut98.push_back(lut98idx1);
    auto fvec98 = [flut98](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut98[i](I));
        return ret;
    };

    std::cerr << "\rLUT98   ";
    Ciphertext gin98 = 1 * gout53[0] + 2 * gout64[0] + 4 * gout62[1];
    std::vector<Ciphertext> gout98 = ctx.eval_lut_amortized(&gin98, lut98);

    std::vector<RotationPoly> lut99;
    std::vector<long (*)(long)> flut99;
    auto lut99idx0 = [](long I) -> long {
        /* GATE 49 (LUT2 _1223_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut99.push_back(ctx.genrate_lut(lut99idx0));
    flut99.push_back(lut99idx0);
    auto lut99idx1 = [](long I) -> long {
        /* GATE 94 (LUT2 _1268_ INIT 0x4 PERM 10) */
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
    lut99.push_back(ctx.genrate_lut(lut99idx1));
    flut99.push_back(lut99idx1);
    auto fvec99 = [flut99](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut99[i](I));
        return ret;
    };

    std::cerr << "\rLUT99   ";
    Ciphertext gin99 = 1 * gout77[0] + 2 * gout41[0];
    std::vector<Ciphertext> gout99 = ctx.eval_lut_amortized(&gin99, lut99);

    std::vector<RotationPoly> lut100;
    std::vector<long (*)(long)> flut100;
    auto lut100idx0 = [](long I) -> long {
        /* GATE 110 (LUT3 _1284_ INIT 0x69 PERM 012) */
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
    lut100.push_back(ctx.genrate_lut(lut100idx0));
    flut100.push_back(lut100idx0);
    auto lut100idx1 = [](long I) -> long {
        /* GATE 168 (LUT3 _1342_ INIT 0x71 PERM 021) */
        switch (I) {
            case  0: return 1;
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
    lut100.push_back(ctx.genrate_lut(lut100idx1));
    flut100.push_back(lut100idx1);
    auto fvec100 = [flut100](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut100[i](I));
        return ret;
    };

    std::cerr << "\rLUT100   ";
    Ciphertext gin100 = 1 * gout45[0] + 2 * gout72[1] + 4 * gout51[0];
    std::vector<Ciphertext> gout100 = ctx.eval_lut_amortized(&gin100, lut100);

    std::vector<RotationPoly> lut101;
    std::vector<long (*)(long)> flut101;
    auto lut101idx0 = [](long I) -> long {
        /* GATE 310 (LUT3 _1484_ INIT 0x96 PERM 012) */
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
    lut101.push_back(ctx.genrate_lut(lut101idx0));
    flut101.push_back(lut101idx0);
    auto lut101idx1 = [](long I) -> long {
        /* GATE 346 (LUT3 _1520_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut101.push_back(ctx.genrate_lut(lut101idx1));
    flut101.push_back(lut101idx1);
    auto fvec101 = [flut101](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut101[i](I));
        return ret;
    };

    std::cerr << "\rLUT101   ";
    Ciphertext gin101 = 1 * gout21[0] + 2 * gout32[1] + 4 * gout56[1];
    std::vector<Ciphertext> gout101 = ctx.eval_lut_amortized(&gin101, lut101);

    std::vector<RotationPoly> lut102;
    std::vector<long (*)(long)> flut102;
    auto lut102idx0 = [](long I) -> long {
        /* GATE 330 (LUT2 _1504_ INIT 0x6 PERM 01) */
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
    lut102.push_back(ctx.genrate_lut(lut102idx0));
    flut102.push_back(lut102idx0);
    auto lut102idx1 = [](long I) -> long {
        /* GATE 371 (LUT2 _1545_ INIT 0x1 PERM 01) */
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
    lut102.push_back(ctx.genrate_lut(lut102idx1));
    flut102.push_back(lut102idx1);
    auto fvec102 = [flut102](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut102[i](I));
        return ret;
    };

    std::cerr << "\rLUT102   ";
    Ciphertext gin102 = 1 * gout76[1] + 2 * gout4[1];
    std::vector<Ciphertext> gout102 = ctx.eval_lut_amortized(&gin102, lut102);

    std::vector<RotationPoly> lut103;
    std::vector<long (*)(long)> flut103;
    auto lut103idx0 = [](long I) -> long {
        /* GATE 376 (LUT2 _1550_ INIT 0x1 PERM 01) */
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
    lut103.push_back(ctx.genrate_lut(lut103idx0));
    flut103.push_back(lut103idx0);
    auto lut103idx1 = [](long I) -> long {
        /* GATE 347 (LUT2 _1521_ INIT 0x6 PERM 01) */
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
    lut103.push_back(ctx.genrate_lut(lut103idx1));
    flut103.push_back(lut103idx1);
    auto fvec103 = [flut103](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut103[i](I));
        return ret;
    };

    std::cerr << "\rLUT103   ";
    Ciphertext gin103 = 1 * gout46[1] + 2 * gout56[0];
    std::vector<Ciphertext> gout103 = ctx.eval_lut_amortized(&gin103, lut103);

    std::vector<RotationPoly> lut104;
    std::vector<long (*)(long)> flut104;
    auto lut104idx0 = [](long I) -> long {
        /* GATE 242 (LUT3 _1416_ INIT 0x69 PERM 012) */
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
    lut104.push_back(ctx.genrate_lut(lut104idx0));
    flut104.push_back(lut104idx0);
    auto lut104idx1 = [](long I) -> long {
        /* GATE 287 (LUT3 _1461_ INIT 0x2b PERM 012) */
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
    lut104.push_back(ctx.genrate_lut(lut104idx1));
    flut104.push_back(lut104idx1);
    auto fvec104 = [flut104](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut104[i](I));
        return ret;
    };

    std::cerr << "\rLUT104   ";
    Ciphertext gin104 = 1 * gout96[0] + 2 * gout88[0] + 4 * gout43[0];
    std::vector<Ciphertext> gout104 = ctx.eval_lut_amortized(&gin104, lut104);

    std::vector<RotationPoly> lut105;
    std::vector<long (*)(long)> flut105;
    auto lut105idx0 = [](long I) -> long {
        /* GATE 372 (LUT2 _1546_ INIT 0x1 PERM 01) */
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
    lut105.push_back(ctx.genrate_lut(lut105idx0));
    flut105.push_back(lut105idx0);
    auto lut105idx1 = [](long I) -> long {
        /* GATE 333 (LUT2 _1507_ INIT 0x6 PERM 01) */
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
    lut105.push_back(ctx.genrate_lut(lut105idx1));
    flut105.push_back(lut105idx1);
    auto fvec105 = [flut105](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut105[i](I));
        return ret;
    };

    std::cerr << "\rLUT105   ";
    Ciphertext gin105 = 1 * gout23[1] + 2 * gout59[1];
    std::vector<Ciphertext> gout105 = ctx.eval_lut_amortized(&gin105, lut105);

    std::vector<RotationPoly> lut106;
    std::vector<long (*)(long)> flut106;
    auto lut106idx0 = [](long I) -> long {
        /* GATE 66 (LUT3 _1240_ INIT 0x96 PERM 012) */
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
    lut106.push_back(ctx.genrate_lut(lut106idx0));
    flut106.push_back(lut106idx0);
    auto lut106idx1 = [](long I) -> long {
        /* GATE 124 (LUT3 _1298_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
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
    Ciphertext gin106 = 1 * gout63[1] + 2 * gout39[1] + 4 * gout16[0];
    std::vector<Ciphertext> gout106 = ctx.eval_lut_amortized(&gin106, lut106);

    std::vector<RotationPoly> lut107;
    std::vector<long (*)(long)> flut107;
    auto lut107idx0 = [](long I) -> long {
        /* GATE 125 (LUT3 _1299_ INIT 0x69 PERM 012) */
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
    lut107.push_back(ctx.genrate_lut(lut107idx0));
    flut107.push_back(lut107idx0);
    auto lut107idx1 = [](long I) -> long {
        /* GATE 161 (LUT3 _1335_ INIT 0x71 PERM 021) */
        switch (I) {
            case  0: return 1;
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
    lut107.push_back(ctx.genrate_lut(lut107idx1));
    flut107.push_back(lut107idx1);
    auto fvec107 = [flut107](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut107[i](I));
        return ret;
    };

    std::cerr << "\rLUT107   ";
    Ciphertext gin107 = 1 * gout6[0] + 2 * gout67[1] + 4 * gout38[1];
    std::vector<Ciphertext> gout107 = ctx.eval_lut_amortized(&gin107, lut107);

    std::vector<RotationPoly> lut108;
    std::vector<long (*)(long)> flut108;
    auto lut108idx0 = [](long I) -> long {
        /* GATE 60 (LUT3 _1234_ INIT 0x69 PERM 012) */
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
    lut108.push_back(ctx.genrate_lut(lut108idx0));
    flut108.push_back(lut108idx0);
    auto lut108idx1 = [](long I) -> long {
        /* GATE 129 (LUT3 _1303_ INIT 0x2b PERM 012) */
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
    lut108.push_back(ctx.genrate_lut(lut108idx1));
    flut108.push_back(lut108idx1);
    auto fvec108 = [flut108](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut108[i](I));
        return ret;
    };

    std::cerr << "\rLUT108   ";
    Ciphertext gin108 = 1 * gout69[0] + 2 * gout83[0] + 4 * gout106[0];
    std::vector<Ciphertext> gout108 = ctx.eval_lut_amortized(&gin108, lut108);

    std::vector<RotationPoly> lut109;
    std::vector<long (*)(long)> flut109;
    auto lut109idx0 = [](long I) -> long {
        /* GATE 122 (LUT3 _1296_ INIT 0x96 PERM 012) */
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
    lut109.push_back(ctx.genrate_lut(lut109idx0));
    flut109.push_back(lut109idx0);
    auto lut109idx1 = [](long I) -> long {
        /* GATE 169 (LUT3 _1343_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
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
    Ciphertext gin109 = 1 * gout86[1] + 2 * gout106[1] + 4 * gout107[0];
    std::vector<Ciphertext> gout109 = ctx.eval_lut_amortized(&gin109, lut109);

    std::vector<RotationPoly> lut110;
    std::vector<long (*)(long)> flut110;
    auto lut110idx0 = [](long I) -> long {
        /* GATE 80 (LUT3 _1254_ INIT 0x69 PERM 012) */
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
    lut110.push_back(ctx.genrate_lut(lut110idx0));
    flut110.push_back(lut110idx0);
    auto lut110idx1 = [](long I) -> long {
        /* GATE 108 (LUT3 _1282_ INIT 0x2b PERM 012) */
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
    lut110.push_back(ctx.genrate_lut(lut110idx1));
    flut110.push_back(lut110idx1);
    auto fvec110 = [flut110](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut110[i](I));
        return ret;
    };

    std::cerr << "\rLUT110   ";
    Ciphertext gin110 = 1 * gout47[1] + 2 * gout72[0] + 4 * gout87[1];
    std::vector<Ciphertext> gout110 = ctx.eval_lut_amortized(&gin110, lut110);

    std::vector<RotationPoly> lut111;
    std::vector<long (*)(long)> flut111;
    auto lut111idx0 = [](long I) -> long {
        /* GATE 163 (LUT3 _1337_ INIT 0x69 PERM 012) */
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
    lut111.push_back(ctx.genrate_lut(lut111idx0));
    flut111.push_back(lut111idx0);
    auto lut111idx1 = [](long I) -> long {
        /* GATE 207 (LUT3 _1381_ INIT 0x2b PERM 012) */
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
    lut111.push_back(ctx.genrate_lut(lut111idx1));
    flut111.push_back(lut111idx1);
    auto fvec111 = [flut111](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut111[i](I));
        return ret;
    };

    std::cerr << "\rLUT111   ";
    Ciphertext gin111 = 1 * gout38[0] + 2 * gout48[1] + 4 * gout58[1];
    std::vector<Ciphertext> gout111 = ctx.eval_lut_amortized(&gin111, lut111);

    std::vector<RotationPoly> lut112;
    std::vector<long (*)(long)> flut112;
    auto lut112idx0 = [](long I) -> long {
        /* GATE 337 (LUT3 _1511_ INIT 0x69 PERM 012) */
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
    lut112.push_back(ctx.genrate_lut(lut112idx0));
    flut112.push_back(lut112idx0);
    auto lut112idx1 = [](long I) -> long {
        /* GATE 375 (LUT3 _1549_ INIT 0xe8 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
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
    Ciphertext gin112 = 1 * gout61[1] + 2 * gout79[1] + 4 * gout28[1];
    std::vector<Ciphertext> gout112 = ctx.eval_lut_amortized(&gin112, lut112);

    std::vector<RotationPoly> lut113;
    std::vector<long (*)(long)> flut113;
    auto lut113idx0 = [](long I) -> long {
        /* GATE 2 (LUT2 _1176_ INIT 0x6 PERM 01) */
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
    lut113.push_back(ctx.genrate_lut(lut113idx0));
    flut113.push_back(lut113idx0);
    auto lut113idx1 = [](long I) -> long {
        /* GATE 19 (LUT2 _1193_ INIT 0x8 PERM 01) */
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
    lut113.push_back(ctx.genrate_lut(lut113idx1));
    flut113.push_back(lut113idx1);
    auto fvec113 = [flut113](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut113[i](I));
        return ret;
    };

    std::cerr << "\rLUT113   ";
    Ciphertext gin113 = 1 * gout95[1] + 2 * gout54[0];
    std::vector<Ciphertext> gout113 = ctx.eval_lut_amortized(&gin113, lut113);

    std::vector<RotationPoly> lut114;
    std::vector<long (*)(long)> flut114;
    auto lut114idx0 = [](long I) -> long {
        /* GATE 28 (LUT3 _1202_ INIT 0x96 PERM 012) */
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
    lut114.push_back(ctx.genrate_lut(lut114idx0));
    flut114.push_back(lut114idx0);
    auto lut114idx1 = [](long I) -> long {
        /* GATE 72 (LUT3 _1246_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
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
    Ciphertext gin114 = 1 * gout22[1] + 2 * gout42[0] + 4 * gout63[0];
    std::vector<Ciphertext> gout114 = ctx.eval_lut_amortized(&gin114, lut114);

    std::vector<RotationPoly> lut115;
    std::vector<long (*)(long)> flut115;
    auto lut115idx0 = [](long I) -> long {
        /* GATE 32 (LUT2 _1206_ INIT 0x6 PERM 01) */
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
    lut115.push_back(ctx.genrate_lut(lut115idx0));
    flut115.push_back(lut115idx0);
    auto lut115idx1 = [](long I) -> long {
        /* GATE 78 (LUT2 _1252_ INIT 0x8 PERM 01) */
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
    lut115.push_back(ctx.genrate_lut(lut115idx1));
    flut115.push_back(lut115idx1);
    auto fvec115 = [flut115](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut115[i](I));
        return ret;
    };

    std::cerr << "\rLUT115   ";
    Ciphertext gin115 = 1 * gout54[1] + 2 * gout98[1];
    std::vector<Ciphertext> gout115 = ctx.eval_lut_amortized(&gin115, lut115);

    std::vector<RotationPoly> lut116;
    std::vector<long (*)(long)> flut116;
    auto lut116idx0 = [](long I) -> long {
        /* GATE 288 (LUT3 _1462_ INIT 0x69 PERM 012) */
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
    lut116.push_back(ctx.genrate_lut(lut116idx0));
    flut116.push_back(lut116idx0);
    auto lut116idx1 = [](long I) -> long {
        /* GATE 336 (LUT3 _1510_ INIT 0x2b PERM 012) */
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
    lut116.push_back(ctx.genrate_lut(lut116idx1));
    flut116.push_back(lut116idx1);
    auto fvec116 = [flut116](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut116[i](I));
        return ret;
    };

    std::cerr << "\rLUT116   ";
    Ciphertext gin116 = 1 * gout88[1] + 2 * gout76[0] + 4 * gout79[0];
    std::vector<Ciphertext> gout116 = ctx.eval_lut_amortized(&gin116, lut116);

    std::vector<RotationPoly> lut117;
    std::vector<long (*)(long)> flut117;
    auto lut117idx0 = [](long I) -> long {
        /* GATE 59 (LUT3 _1233_ INIT 0x17 PERM 012) */
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
    lut117.push_back(ctx.genrate_lut(lut117idx0));
    flut117.push_back(lut117idx0);
    auto lut117idx1 = [](long I) -> long {
        /* GATE 22 (LUT3 _1196_ INIT 0x96 PERM 012) */
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
    lut117.push_back(ctx.genrate_lut(lut117idx1));
    flut117.push_back(lut117idx1);
    auto fvec117 = [flut117](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut117[i](I));
        return ret;
    };

    std::cerr << "\rLUT117   ";
    Ciphertext gin117 = 1 * gout85[1] + 2 * gout69[1] + 4 * gout114[0];
    std::vector<Ciphertext> gout117 = ctx.eval_lut_amortized(&gin117, lut117);

    std::vector<RotationPoly> lut118;
    std::vector<long (*)(long)> flut118;
    auto lut118idx0 = [](long I) -> long {
        /* GATE 262 (LUT3 _1436_ INIT 0x69 PERM 012) */
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
    lut118.push_back(ctx.genrate_lut(lut118idx0));
    flut118.push_back(lut118idx0);
    auto lut118idx1 = [](long I) -> long {
        /* GATE 306 (LUT3 _1480_ INIT 0x2b PERM 012) */
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
    lut118.push_back(ctx.genrate_lut(lut118idx1));
    flut118.push_back(lut118idx1);
    auto fvec118 = [flut118](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut118[i](I));
        return ret;
    };

    std::cerr << "\rLUT118   ";
    Ciphertext gin118 = 1 * gout92[1] + 2 * gout91[0] + 4 * gout74[1];
    std::vector<Ciphertext> gout118 = ctx.eval_lut_amortized(&gin118, lut118);

    std::vector<RotationPoly> lut119;
    std::vector<long (*)(long)> flut119;
    auto lut119idx0 = [](long I) -> long {
        /* GATE 172 (LUT3 _1346_ INIT 0x96 PERM 012) */
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
    lut119.push_back(ctx.genrate_lut(lut119idx0));
    flut119.push_back(lut119idx0);
    auto lut119idx1 = [](long I) -> long {
        /* GATE 217 (LUT3 _1391_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
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
    Ciphertext gin119 = 1 * gout31[1] + 2 * gout6[1] + 4 * gout71[1];
    std::vector<Ciphertext> gout119 = ctx.eval_lut_amortized(&gin119, lut119);

    std::vector<RotationPoly> lut120;
    std::vector<long (*)(long)> flut120;
    auto lut120idx0 = [](long I) -> long {
        /* GATE 222 (LUT3 _1396_ INIT 0x69 PERM 012) */
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
    lut120.push_back(ctx.genrate_lut(lut120idx0));
    flut120.push_back(lut120idx0);
    auto lut120idx1 = [](long I) -> long {
        /* GATE 274 (LUT3 _1448_ INIT 0x2b PERM 012) */
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
    lut120.push_back(ctx.genrate_lut(lut120idx1));
    flut120.push_back(lut120idx1);
    auto fvec120 = [flut120](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut120[i](I));
        return ret;
    };

    std::cerr << "\rLUT120   ";
    Ciphertext gin120 = 1 * gout40[1] + 2 * gout73[0] + 4 * gout50[1];
    std::vector<Ciphertext> gout120 = ctx.eval_lut_amortized(&gin120, lut120);

    std::vector<RotationPoly> lut121;
    std::vector<long (*)(long)> flut121;
    auto lut121idx0 = [](long I) -> long {
        /* GATE 160 (LUT3 _1334_ INIT 0x96 PERM 012) */
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
    lut121.push_back(ctx.genrate_lut(lut121idx0));
    flut121.push_back(lut121idx0);
    auto lut121idx1 = [](long I) -> long {
        /* GATE 215 (LUT3 _1389_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut121.push_back(ctx.genrate_lut(lut121idx1));
    flut121.push_back(lut121idx1);
    auto fvec121 = [flut121](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut121[i](I));
        return ret;
    };

    std::cerr << "\rLUT121   ";
    Ciphertext gin121 = 1 * gout107[1] + 2 * gout89[0] + 4 * gout111[0];
    std::vector<Ciphertext> gout121 = ctx.eval_lut_amortized(&gin121, lut121);

    std::vector<RotationPoly> lut122;
    std::vector<long (*)(long)> flut122;
    auto lut122idx0 = [](long I) -> long {
        /* GATE 387 (LUT2 _1561_ INIT 0x8 PERM 01) */
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
    lut122.push_back(ctx.genrate_lut(lut122idx0));
    flut122.push_back(lut122idx0);
    auto fvec122 = [flut122](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut122[i](I));
        return ret;
    };

    std::cerr << "\rLUT122   ";
    Ciphertext gin122 = 1 * gout102[1] + 2 * gout105[0];
    std::vector<Ciphertext> gout122 = ctx.eval_lut_amortized(&gin122, lut122);

    std::vector<RotationPoly> lut123;
    std::vector<long (*)(long)> flut123;
    auto lut123idx0 = [](long I) -> long {
        /* GATE 308 (LUT3 _1482_ INIT 0x69 PERM 012) */
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
    lut123.push_back(ctx.genrate_lut(lut123idx0));
    flut123.push_back(lut123idx0);
    auto lut123idx1 = [](long I) -> long {
        /* GATE 343 (LUT3 _1517_ INIT 0x2b PERM 012) */
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
    lut123.push_back(ctx.genrate_lut(lut123idx1));
    flut123.push_back(lut123idx1);
    auto fvec123 = [flut123](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut123[i](I));
        return ret;
    };

    std::cerr << "\rLUT123   ";
    Ciphertext gin123 = 1 * gout91[1] + 2 * gout101[0] + 4 * gout75[1];
    std::vector<Ciphertext> gout123 = ctx.eval_lut_amortized(&gin123, lut123);

    std::vector<RotationPoly> lut124;
    std::vector<long (*)(long)> flut124;
    auto lut124idx0 = [](long I) -> long {
        /* GATE 370 (LUT2 _1544_ INIT 0x8 PERM 01) */
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
    lut124.push_back(ctx.genrate_lut(lut124idx0));
    flut124.push_back(lut124idx0);
    auto lut124idx1 = [](long I) -> long {
        /* GATE 329 (LUT2 _1503_ INIT 0x6 PERM 01) */
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
    lut124.push_back(ctx.genrate_lut(lut124idx1));
    flut124.push_back(lut124idx1);
    auto fvec124 = [flut124](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut124[i](I));
        return ret;
    };

    std::cerr << "\rLUT124   ";
    Ciphertext gin124 = 1 * gout102[0] + 2 * gout105[1];
    std::vector<Ciphertext> gout124 = ctx.eval_lut_amortized(&gin124, lut124);

    std::vector<RotationPoly> lut125;
    std::vector<long (*)(long)> flut125;
    auto lut125idx0 = [](long I) -> long {
        /* GATE 149 (LUT3 _1323_ INIT 0x71 PERM 021) */
        switch (I) {
            case  0: return 1;
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
    lut125.push_back(ctx.genrate_lut(lut125idx0));
    flut125.push_back(lut125idx0);
    auto lut125idx1 = [](long I) -> long {
        /* GATE 130 (LUT3 _1304_ INIT 0x69 PERM 012) */
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
    lut125.push_back(ctx.genrate_lut(lut125idx1));
    flut125.push_back(lut125idx1);
    auto fvec125 = [flut125](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut125[i](I));
        return ret;
    };

    std::cerr << "\rLUT125   ";
    Ciphertext gin125 = 1 * gout89[1] + 2 * gout83[1] + 4 * gout55[1];
    std::vector<Ciphertext> gout125 = ctx.eval_lut_amortized(&gin125, lut125);

    std::vector<RotationPoly> lut126;
    std::vector<long (*)(long)> flut126;
    auto lut126idx0 = [](long I) -> long {
        /* GATE 79 (LUT2 _1253_ INIT 0x8 PERM 01) */
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
    lut126.push_back(ctx.genrate_lut(lut126idx0));
    flut126.push_back(lut126idx0);
    auto lut126idx1 = [](long I) -> long {
        /* GATE 40 (LUT2 _1214_ INIT 0x6 PERM 01) */
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
    lut126.push_back(ctx.genrate_lut(lut126idx1));
    flut126.push_back(lut126idx1);
    auto fvec126 = [flut126](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut126[i](I));
        return ret;
    };

    std::cerr << "\rLUT126   ";
    Ciphertext gin126 = 1 * gout47[0] + 2 * gout90[0];
    std::vector<Ciphertext> gout126 = ctx.eval_lut_amortized(&gin126, lut126);

    std::vector<RotationPoly> lut127;
    std::vector<long (*)(long)> flut127;
    auto lut127idx0 = [](long I) -> long {
        /* GATE 196 (LUT3 _1370_ INIT 0x69 PERM 012) */
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
    lut127.push_back(ctx.genrate_lut(lut127idx0));
    flut127.push_back(lut127idx0);
    auto lut127idx1 = [](long I) -> long {
        /* GATE 241 (LUT3 _1415_ INIT 0x2b PERM 012) */
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
    lut127.push_back(ctx.genrate_lut(lut127idx1));
    flut127.push_back(lut127idx1);
    auto fvec127 = [flut127](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut127[i](I));
        return ret;
    };

    std::cerr << "\rLUT127   ";
    Ciphertext gin127 = 1 * gout97[0] + 2 * gout96[1] + 4 * gout78[1];
    std::vector<Ciphertext> gout127 = ctx.eval_lut_amortized(&gin127, lut127);

    std::vector<RotationPoly> lut128;
    std::vector<long (*)(long)> flut128;
    auto lut128idx0 = [](long I) -> long {
        /* GATE 150 (LUT3 _1324_ INIT 0x69 PERM 012) */
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
    lut128.push_back(ctx.genrate_lut(lut128idx0));
    flut128.push_back(lut128idx0);
    auto lut128idx1 = [](long I) -> long {
        /* GATE 195 (LUT3 _1369_ INIT 0x2b PERM 012) */
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
    lut128.push_back(ctx.genrate_lut(lut128idx1));
    flut128.push_back(lut128idx1);
    auto fvec128 = [flut128](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut128[i](I));
        return ret;
    };

    std::cerr << "\rLUT128   ";
    Ciphertext gin128 = 1 * gout55[0] + 2 * gout97[1] + 4 * gout82[0];
    std::vector<Ciphertext> gout128 = ctx.eval_lut_amortized(&gin128, lut128);

    std::vector<RotationPoly> lut129;
    std::vector<long (*)(long)> flut129;
    auto lut129idx0 = [](long I) -> long {
        /* GATE 260 (LUT3 _1434_ INIT 0x2b PERM 012) */
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
    lut129.push_back(ctx.genrate_lut(lut129idx0));
    flut129.push_back(lut129idx0);
    auto lut129idx1 = [](long I) -> long {
        /* GATE 216 (LUT3 _1390_ INIT 0x69 PERM 012) */
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
    lut129.push_back(ctx.genrate_lut(lut129idx1));
    flut129.push_back(lut129idx1);
    auto fvec129 = [flut129](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut129[i](I));
        return ret;
    };

    std::cerr << "\rLUT129   ";
    Ciphertext gin129 = 1 * gout119[1] + 2 * gout92[0] + 4 * gout120[0];
    std::vector<Ciphertext> gout129 = ctx.eval_lut_amortized(&gin129, lut129);

    std::vector<RotationPoly> lut130;
    std::vector<long (*)(long)> flut130;
    auto lut130idx0 = [](long I) -> long {
        /* GATE 38 (LUT2 _1212_ INIT 0x6 PERM 01) */
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
    lut130.push_back(ctx.genrate_lut(lut130idx0));
    flut130.push_back(lut130idx0);
    auto lut130idx1 = [](long I) -> long {
        /* GATE 91 (LUT2 _1265_ INIT 0x8 PERM 01) */
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
    lut130.push_back(ctx.genrate_lut(lut130idx1));
    flut130.push_back(lut130idx1);
    auto fvec130 = [flut130](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut130[i](I));
        return ret;
    };

    std::cerr << "\rLUT130   ";
    Ciphertext gin130 = 1 * gout81[0] + 2 * gout126[1];
    std::vector<Ciphertext> gout130 = ctx.eval_lut_amortized(&gin130, lut130);

    std::vector<RotationPoly> lut131;
    std::vector<long (*)(long)> flut131;
    auto lut131idx0 = [](long I) -> long {
        /* GATE 148 (LUT3 _1322_ INIT 0x69 PERM 012) */
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
    lut131.push_back(ctx.genrate_lut(lut131idx0));
    flut131.push_back(lut131idx0);
    auto lut131idx1 = [](long I) -> long {
        /* GATE 193 (LUT3 _1367_ INIT 0x2b PERM 012) */
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
    lut131.push_back(ctx.genrate_lut(lut131idx1));
    flut131.push_back(lut131idx1);
    auto fvec131 = [flut131](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut131[i](I));
        return ret;
    };

    std::cerr << "\rLUT131   ";
    Ciphertext gin131 = 1 * gout125[0] + 2 * gout128[0] + 4 * gout121[0];
    std::vector<Ciphertext> gout131 = ctx.eval_lut_amortized(&gin131, lut131);

    std::vector<RotationPoly> lut132;
    std::vector<long (*)(long)> flut132;
    auto lut132idx0 = [](long I) -> long {
        /* GATE 70 (LUT3 _1244_ INIT 0x96 PERM 012) */
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
    lut132.push_back(ctx.genrate_lut(lut132idx0));
    flut132.push_back(lut132idx0);
    auto lut132idx1 = [](long I) -> long {
        /* GATE 109 (LUT3 _1283_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
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
    Ciphertext gin132 = 1 * gout98[0] + 2 * gout114[1] + 4 * gout86[0];
    std::vector<Ciphertext> gout132 = ctx.eval_lut_amortized(&gin132, lut132);

    std::vector<RotationPoly> lut133;
    std::vector<long (*)(long)> flut133;
    auto lut133idx0 = [](long I) -> long {
        /* GATE 374 (LUT3 _1548_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
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
    lut133.push_back(ctx.genrate_lut(lut133idx0));
    flut133.push_back(lut133idx0);
    auto lut133idx1 = [](long I) -> long {
        /* GATE 345 (LUT3 _1519_ INIT 0x96 PERM 012) */
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
    lut133.push_back(ctx.genrate_lut(lut133idx1));
    flut133.push_back(lut133idx1);
    auto fvec133 = [flut133](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut133[i](I));
        return ret;
    };

    std::cerr << "\rLUT133   ";
    Ciphertext gin133 = 1 * gout101[1] + 2 * gout103[1] + 4 * gout57[1];
    std::vector<Ciphertext> gout133 = ctx.eval_lut_amortized(&gin133, lut133);

    std::vector<RotationPoly> lut134;
    std::vector<long (*)(long)> flut134;
    auto lut134idx0 = [](long I) -> long {
        /* GATE 206 (LUT3 _1380_ INIT 0x96 PERM 012) */
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
    lut134.push_back(ctx.genrate_lut(lut134idx0));
    flut134.push_back(lut134idx0);
    auto lut134idx1 = [](long I) -> long {
        /* GATE 261 (LUT3 _1435_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
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
    Ciphertext gin134 = 1 * gout111[1] + 2 * gout82[1] + 4 * gout70[1];
    std::vector<Ciphertext> gout134 = ctx.eval_lut_amortized(&gin134, lut134);

    std::vector<RotationPoly> lut135;
    std::vector<long (*)(long)> flut135;
    auto lut135idx0 = [](long I) -> long {
        /* GATE 90 (LUT3 _1264_ INIT 0x96 PERM 012) */
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
    lut135.push_back(ctx.genrate_lut(lut135idx0));
    flut135.push_back(lut135idx0);
    auto lut135idx1 = [](long I) -> long {
        /* GATE 140 (LUT3 _1314_ INIT 0xd4 PERM 012) */
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
    lut135.push_back(ctx.genrate_lut(lut135idx1));
    flut135.push_back(lut135idx1);
    auto fvec135 = [flut135](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut135[i](I));
        return ret;
    };

    std::cerr << "\rLUT135   ";
    Ciphertext gin135 = 1 * gout130[1] + 2 * gout90[1] + 4 * gout5[1];
    std::vector<Ciphertext> gout135 = ctx.eval_lut_amortized(&gin135, lut135);

    std::vector<RotationPoly> lut136;
    std::vector<long (*)(long)> flut136;
    auto lut136idx0 = [](long I) -> long {
        /* GATE 305 (LUT3 _1479_ INIT 0x96 PERM 012) */
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
    lut136.push_back(ctx.genrate_lut(lut136idx0));
    flut136.push_back(lut136idx0);
    auto lut136idx1 = [](long I) -> long {
        /* GATE 353 (LUT3 _1527_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
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
    Ciphertext gin136 = 1 * gout118[1] + 2 * gout93[1] + 4 * gout123[0];
    std::vector<Ciphertext> gout136 = ctx.eval_lut_amortized(&gin136, lut136);

    std::vector<RotationPoly> lut137;
    std::vector<long (*)(long)> flut137;
    auto lut137idx0 = [](long I) -> long {
        /* GATE 328 (LUT3 _1502_ INIT 0x69 PERM 012) */
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
    lut137.push_back(ctx.genrate_lut(lut137idx0));
    flut137.push_back(lut137idx0);
    auto lut137idx1 = [](long I) -> long {
        /* GATE 368 (LUT3 _1542_ INIT 0x71 PERM 021) */
        switch (I) {
            case  0: return 1;
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
    lut137.push_back(ctx.genrate_lut(lut137idx1));
    flut137.push_back(lut137idx1);
    auto fvec137 = [flut137](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut137[i](I));
        return ret;
    };

    std::cerr << "\rLUT137   ";
    Ciphertext gin137 = 1 * gout124[1] + 2 * gout116[1] + 4 * gout112[0];
    std::vector<Ciphertext> gout137 = ctx.eval_lut_amortized(&gin137, lut137);

    std::vector<RotationPoly> lut138;
    std::vector<long (*)(long)> flut138;
    auto lut138idx0 = [](long I) -> long {
        /* GATE 319 (LUT3 _1493_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut138.push_back(ctx.genrate_lut(lut138idx0));
    flut138.push_back(lut138idx0);
    auto lut138idx1 = [](long I) -> long {
        /* GATE 259 (LUT3 _1433_ INIT 0x96 PERM 012) */
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
    lut138.push_back(ctx.genrate_lut(lut138idx1));
    flut138.push_back(lut138idx1);
    auto fvec138 = [flut138](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut138[i](I));
        return ret;
    };

    std::cerr << "\rLUT138   ";
    Ciphertext gin138 = 1 * gout129[0] + 2 * gout134[1] + 4 * gout118[0];
    std::vector<Ciphertext> gout138 = ctx.eval_lut_amortized(&gin138, lut138);

    std::vector<RotationPoly> lut139;
    std::vector<long (*)(long)> flut139;
    auto lut139idx0 = [](long I) -> long {
        /* GATE 17 (LUT2 _1191_ INIT 0x8 PERM 01) */
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
    lut139.push_back(ctx.genrate_lut(lut139idx0));
    flut139.push_back(lut139idx0);
    auto lut139idx1 = [](long I) -> long {
        /* GATE 1 (LUT2 _1175_ INIT 0x6 PERM 01) */
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
    lut139.push_back(ctx.genrate_lut(lut139idx1));
    flut139.push_back(lut139idx1);
    auto fvec139 = [flut139](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut139[i](I));
        return ret;
    };

    std::cerr << "\rLUT139   ";
    Ciphertext gin139 = 1 * gout113[0] + 2 * gout81[1];
    std::vector<Ciphertext> gout139 = ctx.eval_lut_amortized(&gin139, lut139);

    std::vector<RotationPoly> lut140;
    std::vector<long (*)(long)> flut140;
    auto lut140idx0 = [](long I) -> long {
        /* GATE 147 (LUT3 _1321_ INIT 0x71 PERM 021) */
        switch (I) {
            case  0: return 1;
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
    lut140.push_back(ctx.genrate_lut(lut140idx0));
    flut140.push_back(lut140idx0);
    auto lut140idx1 = [](long I) -> long {
        /* GATE 121 (LUT3 _1295_ INIT 0x69 PERM 012) */
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
    lut140.push_back(ctx.genrate_lut(lut140idx1));
    flut140.push_back(lut140idx1);
    auto fvec140 = [flut140](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut140[i](I));
        return ret;
    };

    std::cerr << "\rLUT140   ";
    Ciphertext gin140 = 1 * gout109[0] + 2 * gout108[1] + 4 * gout125[1];
    std::vector<Ciphertext> gout140 = ctx.eval_lut_amortized(&gin140, lut140);

    std::vector<RotationPoly> lut141;
    std::vector<long (*)(long)> flut141;
    auto lut141idx0 = [](long I) -> long {
        /* GATE 240 (LUT3 _1414_ INIT 0x69 PERM 012) */
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
    lut141.push_back(ctx.genrate_lut(lut141idx0));
    flut141.push_back(lut141idx0);
    auto lut141idx1 = [](long I) -> long {
        /* GATE 285 (LUT3 _1459_ INIT 0x2b PERM 012) */
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
    lut141.push_back(ctx.genrate_lut(lut141idx1));
    flut141.push_back(lut141idx1);
    auto fvec141 = [flut141](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut141[i](I));
        return ret;
    };

    std::cerr << "\rLUT141   ";
    Ciphertext gin141 = 1 * gout127[1] + 2 * gout104[0] + 4 * gout93[0];
    std::vector<Ciphertext> gout141 = ctx.eval_lut_amortized(&gin141, lut141);

    std::vector<RotationPoly> lut142;
    std::vector<long (*)(long)> flut142;
    auto lut142idx0 = [](long I) -> long {
        /* GATE 57 (LUT3 _1231_ INIT 0x17 PERM 012) */
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
    lut142.push_back(ctx.genrate_lut(lut142idx0));
    flut142.push_back(lut142idx0);
    auto lut142idx1 = [](long I) -> long {
        /* GATE 20 (LUT3 _1194_ INIT 0x96 PERM 012) */
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
    lut142.push_back(ctx.genrate_lut(lut142idx1));
    flut142.push_back(lut142idx1);
    auto fvec142 = [flut142](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut142[i](I));
        return ret;
    };

    std::cerr << "\rLUT142   ";
    Ciphertext gin142 = 1 * gout95[0] + 2 * gout117[1] + 4 * gout115[0];
    std::vector<Ciphertext> gout142 = ctx.eval_lut_amortized(&gin142, lut142);

    std::vector<RotationPoly> lut143;
    std::vector<long (*)(long)> flut143;
    auto lut143idx0 = [](long I) -> long {
        /* GATE 286 (LUT3 _1460_ INIT 0x69 PERM 012) */
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
    lut143.push_back(ctx.genrate_lut(lut143idx0));
    flut143.push_back(lut143idx0);
    auto lut143idx1 = [](long I) -> long {
        /* GATE 341 (LUT3 _1515_ INIT 0x2b PERM 012) */
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
    lut143.push_back(ctx.genrate_lut(lut143idx1));
    flut143.push_back(lut143idx1);
    auto fvec143 = [flut143](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut143[i](I));
        return ret;
    };

    std::cerr << "\rLUT143   ";
    Ciphertext gin143 = 1 * gout104[1] + 2 * gout116[0] + 4 * gout94[0];
    std::vector<Ciphertext> gout143 = ctx.eval_lut_amortized(&gin143, lut143);

    std::vector<RotationPoly> lut144;
    std::vector<long (*)(long)> flut144;
    auto lut144idx0 = [](long I) -> long {
        /* GATE 369 (LUT3 _1543_ INIT 0x41 PERM 012) */
        switch (I) {
            case  0: return 1;
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
    lut144.push_back(ctx.genrate_lut(lut144idx0));
    flut144.push_back(lut144idx0);
    auto fvec144 = [flut144](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut144[i](I));
        return ret;
    };

    std::cerr << "\rLUT144   ";
    Ciphertext gin144 = 1 * gout124[0] + 2 * gout102[1] + 4 * gout105[0];
    std::vector<Ciphertext> gout144 = ctx.eval_lut_amortized(&gin144, lut144);

    std::vector<RotationPoly> lut145;
    std::vector<long (*)(long)> flut145;
    auto lut145idx0 = [](long I) -> long {
        /* GATE 214 (LUT3 _1388_ INIT 0x2b PERM 012) */
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
    lut145.push_back(ctx.genrate_lut(lut145idx0));
    flut145.push_back(lut145idx0);
    auto lut145idx1 = [](long I) -> long {
        /* GATE 170 (LUT3 _1344_ INIT 0x69 PERM 012) */
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
    lut145.push_back(ctx.genrate_lut(lut145idx1));
    flut145.push_back(lut145idx1);
    auto fvec145 = [flut145](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut145[i](I));
        return ret;
    };

    std::cerr << "\rLUT145   ";
    Ciphertext gin145 = 1 * gout51[1] + 2 * gout119[0] + 4 * gout80[1];
    std::vector<Ciphertext> gout145 = ctx.eval_lut_amortized(&gin145, lut145);

    std::vector<RotationPoly> lut146;
    std::vector<long (*)(long)> flut146;
    auto lut146idx0 = [](long I) -> long {
        /* GATE 77 (LUT3 _1251_ INIT 0x96 PERM 012) */
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
    lut146.push_back(ctx.genrate_lut(lut146idx0));
    flut146.push_back(lut146idx0);
    auto lut146idx1 = [](long I) -> long {
        /* GATE 102 (LUT3 _1276_ INIT 0x17 PERM 012) */
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
    lut146.push_back(ctx.genrate_lut(lut146idx1));
    flut146.push_back(lut146idx1);
    auto fvec146 = [flut146](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut146[i](I));
        return ret;
    };

    std::cerr << "\rLUT146   ";
    Ciphertext gin146 = 1 * gout115[1] + 2 * gout126[0] + 4 * gout110[0];
    std::vector<Ciphertext> gout146 = ctx.eval_lut_amortized(&gin146, lut146);

    std::vector<RotationPoly> lut147;
    std::vector<long (*)(long)> flut147;
    auto lut147idx0 = [](long I) -> long {
        /* GATE 273 (LUT3 _1447_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
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
    lut147.push_back(ctx.genrate_lut(lut147idx0));
    flut147.push_back(lut147idx0);
    auto lut147idx1 = [](long I) -> long {
        /* GATE 213 (LUT3 _1387_ INIT 0x96 PERM 021) */
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
    lut147.push_back(ctx.genrate_lut(lut147idx1));
    flut147.push_back(lut147idx1);
    auto fvec147 = [flut147](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut147[i](I));
        return ret;
    };

    std::cerr << "\rLUT147   ";
    Ciphertext gin147 = 1 * gout145[0] + 2 * gout129[1] + 4 * gout121[1];
    std::vector<Ciphertext> gout147 = ctx.eval_lut_amortized(&gin147, lut147);

    std::vector<RotationPoly> lut148;
    std::vector<long (*)(long)> flut148;
    auto lut148idx0 = [](long I) -> long {
        /* GATE 107 (LUT3 _1281_ INIT 0x96 PERM 012) */
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
    lut148.push_back(ctx.genrate_lut(lut148idx0));
    flut148.push_back(lut148idx0);
    auto lut148idx1 = [](long I) -> long {
        /* GATE 181 (LUT3 _1355_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
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
    Ciphertext gin148 = 1 * gout110[1] + 2 * gout132[1] + 4 * gout100[0];
    std::vector<Ciphertext> gout148 = ctx.eval_lut_amortized(&gin148, lut148);

    std::vector<RotationPoly> lut149;
    std::vector<long (*)(long)> flut149;
    auto lut149idx0 = [](long I) -> long {
        /* GATE 167 (LUT3 _1341_ INIT 0x96 PERM 012) */
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
    lut149.push_back(ctx.genrate_lut(lut149idx0));
    flut149.push_back(lut149idx0);
    auto lut149idx1 = [](long I) -> long {
        /* GATE 227 (LUT3 _1401_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut149.push_back(ctx.genrate_lut(lut149idx1));
    flut149.push_back(lut149idx1);
    auto fvec149 = [flut149](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut149[i](I));
        return ret;
    };

    std::cerr << "\rLUT149   ";
    Ciphertext gin149 = 1 * gout100[1] + 2 * gout109[1] + 4 * gout145[1];
    std::vector<Ciphertext> gout149 = ctx.eval_lut_amortized(&gin149, lut149);

    std::vector<RotationPoly> lut150;
    std::vector<long (*)(long)> flut150;
    auto lut150idx0 = [](long I) -> long {
        /* GATE 18 (LUT3 _1192_ INIT 0x96 PERM 012) */
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
    lut150.push_back(ctx.genrate_lut(lut150idx0));
    flut150.push_back(lut150idx0);
    auto lut150idx1 = [](long I) -> long {
        /* GATE 55 (LUT3 _1229_ INIT 0x17 PERM 012) */
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
    lut150.push_back(ctx.genrate_lut(lut150idx1));
    flut150.push_back(lut150idx1);
    auto fvec150 = [flut150](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut150[i](I));
        return ret;
    };

    std::cerr << "\rLUT150   ";
    Ciphertext gin150 = 1 * gout113[1] + 2 * gout142[1] + 4 * gout130[0];
    std::vector<Ciphertext> gout150 = ctx.eval_lut_amortized(&gin150, lut150);

    std::vector<RotationPoly> lut151;
    std::vector<long (*)(long)> flut151;
    auto lut151idx0 = [](long I) -> long {
        /* GATE 284 (LUT3 _1458_ INIT 0x69 PERM 012) */
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
    lut151.push_back(ctx.genrate_lut(lut151idx0));
    flut151.push_back(lut151idx0);
    auto lut151idx1 = [](long I) -> long {
        /* GATE 351 (LUT3 _1525_ INIT 0x2b PERM 012) */
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
    lut151.push_back(ctx.genrate_lut(lut151idx1));
    flut151.push_back(lut151idx1);
    auto fvec151 = [flut151](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut151[i](I));
        return ret;
    };

    std::cerr << "\rLUT151   ";
    Ciphertext gin151 = 1 * gout141[1] + 2 * gout143[0] + 4 * gout136[0];
    std::vector<Ciphertext> gout151 = ctx.eval_lut_amortized(&gin151, lut151);

    std::vector<RotationPoly> lut152;
    std::vector<long (*)(long)> flut152;
    auto lut152idx0 = [](long I) -> long {
        /* GATE 101 (LUT3 _1275_ INIT 0x69 PERM 012) */
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
    lut152.push_back(ctx.genrate_lut(lut152idx0));
    flut152.push_back(lut152idx0);
    auto lut152idx1 = [](long I) -> long {
        /* GATE 184 (LUT3 _1358_ INIT 0xe8 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut152.push_back(ctx.genrate_lut(lut152idx1));
    flut152.push_back(lut152idx1);
    auto fvec152 = [flut152](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut152[i](I));
        return ret;
    };

    std::cerr << "\rLUT152   ";
    Ciphertext gin152 = 1 * gout146[1] + 2 * gout87[0] + 4 * gout9[0];
    std::vector<Ciphertext> gout152 = ctx.eval_lut_amortized(&gin152, lut152);

    std::vector<RotationPoly> lut153;
    std::vector<long (*)(long)> flut153;
    auto lut153idx0 = [](long I) -> long {
        /* GATE 58 (LUT3 _1232_ INIT 0x69 PERM 012) */
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
    lut153.push_back(ctx.genrate_lut(lut153idx0));
    flut153.push_back(lut153idx0);
    auto lut153idx1 = [](long I) -> long {
        /* GATE 120 (LUT3 _1294_ INIT 0x2b PERM 012) */
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
    lut153.push_back(ctx.genrate_lut(lut153idx1));
    flut153.push_back(lut153idx1);
    auto fvec153 = [flut153](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut153[i](I));
        return ret;
    };

    std::cerr << "\rLUT153   ";
    Ciphertext gin153 = 1 * gout117[0] + 2 * gout108[0] + 4 * gout132[0];
    std::vector<Ciphertext> gout153 = ctx.eval_lut_amortized(&gin153, lut153);

    std::vector<RotationPoly> lut154;
    std::vector<long (*)(long)> flut154;
    auto lut154idx0 = [](long I) -> long {
        /* GATE 357 (LUT3 _1531_ INIT 0xe8 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut154.push_back(ctx.genrate_lut(lut154idx0));
    flut154.push_back(lut154idx0);
    auto lut154idx1 = [](long I) -> long {
        /* GATE 318 (LUT3 _1492_ INIT 0x69 PERM 012) */
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
    lut154.push_back(ctx.genrate_lut(lut154idx1));
    flut154.push_back(lut154idx1);
    auto fvec154 = [flut154](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut154[i](I));
        return ret;
    };

    std::cerr << "\rLUT154   ";
    Ciphertext gin154 = 1 * gout138[0] + 2 * gout74[0] + 4 * gout15[1];
    std::vector<Ciphertext> gout154 = ctx.eval_lut_amortized(&gin154, lut154);

    std::vector<RotationPoly> lut155;
    std::vector<long (*)(long)> flut155;
    auto lut155idx0 = [](long I) -> long {
        /* GATE 377 (LUT3 _1551_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
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
    lut155.push_back(ctx.genrate_lut(lut155idx0));
    flut155.push_back(lut155idx0);
    auto lut155idx1 = [](long I) -> long {
        /* GATE 342 (LUT3 _1516_ INIT 0x96 PERM 021) */
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
    lut155.push_back(ctx.genrate_lut(lut155idx1));
    flut155.push_back(lut155idx1);
    auto fvec155 = [flut155](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut155[i](I));
        return ret;
    };

    std::cerr << "\rLUT155   ";
    Ciphertext gin155 = 1 * gout123[1] + 2 * gout133[1] + 4 * gout94[1];
    std::vector<Ciphertext> gout155 = ctx.eval_lut_amortized(&gin155, lut155);

    std::vector<RotationPoly> lut156;
    std::vector<long (*)(long)> flut156;
    auto lut156idx0 = [](long I) -> long {
        /* GATE 373 (LUT3 _1547_ INIT 0x96 PERM 021) */
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
    lut156.push_back(ctx.genrate_lut(lut156idx0));
    flut156.push_back(lut156idx0);
    auto lut156idx1 = [](long I) -> long {
        /* GATE 388 (LUT3 _1562_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
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
    lut156.push_back(ctx.genrate_lut(lut156idx1));
    flut156.push_back(lut156idx1);
    auto fvec156 = [flut156](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut156[i](I));
        return ret;
    };

    std::cerr << "\rLUT156   ";
    Ciphertext gin156 = 1 * gout133[0] + 2 * gout103[0] + 4 * gout112[1];
    std::vector<Ciphertext> gout156 = ctx.eval_lut_amortized(&gin156, lut156);

    std::vector<RotationPoly> lut157;
    std::vector<long (*)(long)> flut157;
    auto lut157idx0 = [](long I) -> long {
        /* GATE 194 (LUT3 _1368_ INIT 0x69 PERM 012) */
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
    lut157.push_back(ctx.genrate_lut(lut157idx0));
    flut157.push_back(lut157idx0);
    auto lut157idx1 = [](long I) -> long {
        /* GATE 239 (LUT3 _1413_ INIT 0x2b PERM 012) */
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
    lut157.push_back(ctx.genrate_lut(lut157idx1));
    flut157.push_back(lut157idx1);
    auto fvec157 = [flut157](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut157[i](I));
        return ret;
    };

    std::cerr << "\rLUT157   ";
    Ciphertext gin157 = 1 * gout128[1] + 2 * gout127[0] + 4 * gout134[0];
    std::vector<Ciphertext> gout157 = ctx.eval_lut_amortized(&gin157, lut157);

    std::vector<RotationPoly> lut158;
    std::vector<long (*)(long)> flut158;
    auto lut158idx0 = [](long I) -> long {
        /* GATE 352 (LUT3 _1526_ INIT 0x69 PERM 012) */
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
    lut158.push_back(ctx.genrate_lut(lut158idx0));
    flut158.push_back(lut158idx0);
    auto lut158idx1 = [](long I) -> long {
        /* GATE 378 (LUT3 _1552_ INIT 0xe8 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut158.push_back(ctx.genrate_lut(lut158idx1));
    flut158.push_back(lut158idx1);
    auto fvec158 = [flut158](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut158[i](I));
        return ret;
    };

    std::cerr << "\rLUT158   ";
    Ciphertext gin158 = 1 * gout136[1] + 2 * gout75[0] + 4 * gout3[0];
    std::vector<Ciphertext> gout158 = ctx.eval_lut_amortized(&gin158, lut158);

    std::vector<RotationPoly> lut159;
    std::vector<long (*)(long)> flut159;
    auto lut159idx0 = [](long I) -> long {
        /* GATE 192 (LUT3 _1366_ INIT 0x69 PERM 012) */
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
    lut159.push_back(ctx.genrate_lut(lut159idx0));
    flut159.push_back(lut159idx0);
    auto lut159idx1 = [](long I) -> long {
        /* GATE 237 (LUT3 _1411_ INIT 0x2b PERM 012) */
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
    lut159.push_back(ctx.genrate_lut(lut159idx1));
    flut159.push_back(lut159idx1);
    auto fvec159 = [flut159](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut159[i](I));
        return ret;
    };

    std::cerr << "\rLUT159   ";
    Ciphertext gin159 = 1 * gout131[1] + 2 * gout157[0] + 4 * gout147[1];
    std::vector<Ciphertext> gout159 = ctx.eval_lut_amortized(&gin159, lut159);

    std::vector<RotationPoly> lut160;
    std::vector<long (*)(long)> flut160;
    auto lut160idx0 = [](long I) -> long {
        /* GATE 146 (LUT3 _1320_ INIT 0x69 PERM 012) */
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
    lut160.push_back(ctx.genrate_lut(lut160idx0));
    flut160.push_back(lut160idx0);
    auto lut160idx1 = [](long I) -> long {
        /* GATE 191 (LUT3 _1365_ INIT 0x2b PERM 012) */
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
    lut160.push_back(ctx.genrate_lut(lut160idx1));
    flut160.push_back(lut160idx1);
    auto fvec160 = [flut160](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut160[i](I));
        return ret;
    };

    std::cerr << "\rLUT160   ";
    Ciphertext gin160 = 1 * gout140[0] + 2 * gout131[0] + 4 * gout149[0];
    std::vector<Ciphertext> gout160 = ctx.eval_lut_amortized(&gin160, lut160);

    std::vector<RotationPoly> lut161;
    std::vector<long (*)(long)> flut161;
    auto lut161idx0 = [](long I) -> long {
        /* GATE 272 (LUT3 _1446_ INIT 0x69 PERM 012) */
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
    lut161.push_back(ctx.genrate_lut(lut161idx0));
    flut161.push_back(lut161idx0);
    auto lut161idx1 = [](long I) -> long {
        /* GATE 322 (LUT3 _1496_ INIT 0xe8 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut161.push_back(ctx.genrate_lut(lut161idx1));
    flut161.push_back(lut161idx1);
    auto fvec161 = [flut161](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut161[i](I));
        return ret;
    };

    std::cerr << "\rLUT161   ";
    Ciphertext gin161 = 1 * gout147[0] + 2 * gout120[1] + 4 * gout50[0];
    std::vector<Ciphertext> gout161 = ctx.eval_lut_amortized(&gin161, lut161);

    std::vector<RotationPoly> lut162;
    std::vector<long (*)(long)> flut162;
    auto lut162idx0 = [](long I) -> long {
        /* GATE 180 (LUT3 _1354_ INIT 0x69 PERM 012) */
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
    lut162.push_back(ctx.genrate_lut(lut162idx0));
    flut162.push_back(lut162idx0);
    auto lut162idx1 = [](long I) -> long {
        /* GATE 230 (LUT3 _1404_ INIT 0xe8 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
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
    Ciphertext gin162 = 1 * gout148[1] + 2 * gout45[1] + 4 * gout30[1];
    std::vector<Ciphertext> gout162 = ctx.eval_lut_amortized(&gin162, lut162);

    std::vector<RotationPoly> lut163;
    std::vector<long (*)(long)> flut163;
    auto lut163idx0 = [](long I) -> long {
        /* GATE 283 (LUT3 _1457_ INIT 0x2b PERM 012) */
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
    lut163.push_back(ctx.genrate_lut(lut163idx0));
    flut163.push_back(lut163idx0);
    auto lut163idx1 = [](long I) -> long {
        /* GATE 238 (LUT3 _1412_ INIT 0x69 PERM 012) */
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
    lut163.push_back(ctx.genrate_lut(lut163idx1));
    flut163.push_back(lut163idx1);
    auto fvec163 = [flut163](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut163[i](I));
        return ret;
    };

    std::cerr << "\rLUT163   ";
    Ciphertext gin163 = 1 * gout157[1] + 2 * gout141[0] + 4 * gout138[1];
    std::vector<Ciphertext> gout163 = ctx.eval_lut_amortized(&gin163, lut163);

    std::vector<RotationPoly> lut164;
    std::vector<long (*)(long)> flut164;
    auto lut164idx0 = [](long I) -> long {
        /* GATE 327 (LUT3 _1501_ INIT 0x69 PERM 012) */
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
    lut164.push_back(ctx.genrate_lut(lut164idx0));
    flut164.push_back(lut164idx0);
    auto lut164idx1 = [](long I) -> long {
        /* GATE 366 (LUT3 _1540_ INIT 0x71 PERM 021) */
        switch (I) {
            case  0: return 1;
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
    lut164.push_back(ctx.genrate_lut(lut164idx1));
    flut164.push_back(lut164idx1);
    auto fvec164 = [flut164](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut164[i](I));
        return ret;
    };

    std::cerr << "\rLUT164   ";
    Ciphertext gin164 = 1 * gout137[0] + 2 * gout143[1] + 4 * gout155[1];
    std::vector<Ciphertext> gout164 = ctx.eval_lut_amortized(&gin164, lut164);

    std::vector<RotationPoly> lut165;
    std::vector<long (*)(long)> flut165;
    auto lut165idx0 = [](long I) -> long {
        /* GATE 56 (LUT3 _1230_ INIT 0x69 PERM 012) */
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
    lut165.push_back(ctx.genrate_lut(lut165idx0));
    flut165.push_back(lut165idx0);
    auto lut165idx1 = [](long I) -> long {
        /* GATE 105 (LUT3 _1279_ INIT 0x2b PERM 012) */
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
    lut165.push_back(ctx.genrate_lut(lut165idx1));
    flut165.push_back(lut165idx1);
    auto fvec165 = [flut165](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut165[i](I));
        return ret;
    };

    std::cerr << "\rLUT165   ";
    Ciphertext gin165 = 1 * gout142[0] + 2 * gout153[0] + 4 * gout146[0];
    std::vector<Ciphertext> gout165 = ctx.eval_lut_amortized(&gin165, lut165);

    std::vector<RotationPoly> lut166;
    std::vector<long (*)(long)> flut166;
    auto lut166idx0 = [](long I) -> long {
        /* GATE 53 (LUT3 _1227_ INIT 0x17 PERM 012) */
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
    lut166.push_back(ctx.genrate_lut(lut166idx0));
    flut166.push_back(lut166idx0);
    auto lut166idx1 = [](long I) -> long {
        /* GATE 16 (LUT3 _1190_ INIT 0x96 PERM 012) */
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
    lut166.push_back(ctx.genrate_lut(lut166idx1));
    flut166.push_back(lut166idx1);
    auto fvec166 = [flut166](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut166[i](I));
        return ret;
    };

    std::cerr << "\rLUT166   ";
    Ciphertext gin166 = 1 * gout139[0] + 2 * gout150[0] + 4 * gout99[0];
    std::vector<Ciphertext> gout166 = ctx.eval_lut_amortized(&gin166, lut166);

    std::vector<RotationPoly> lut167;
    std::vector<long (*)(long)> flut167;
    auto lut167idx0 = [](long I) -> long {
        /* GATE 282 (LUT3 _1456_ INIT 0x69 PERM 012) */
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
    lut167.push_back(ctx.genrate_lut(lut167idx0));
    flut167.push_back(lut167idx0);
    auto lut167idx1 = [](long I) -> long {
        /* GATE 356 (LUT3 _1530_ INIT 0x2b PERM 012) */
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
    lut167.push_back(ctx.genrate_lut(lut167idx1));
    flut167.push_back(lut167idx1);
    auto fvec167 = [flut167](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut167[i](I));
        return ret;
    };

    std::cerr << "\rLUT167   ";
    Ciphertext gin167 = 1 * gout163[0] + 2 * gout151[0] + 4 * gout154[1];
    std::vector<Ciphertext> gout167 = ctx.eval_lut_amortized(&gin167, lut167);

    std::vector<RotationPoly> lut168;
    std::vector<long (*)(long)> flut168;
    auto lut168idx0 = [](long I) -> long {
        /* GATE 226 (LUT3 _1400_ INIT 0x69 PERM 012) */
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
    lut168.push_back(ctx.genrate_lut(lut168idx0));
    flut168.push_back(lut168idx0);
    auto lut168idx1 = [](long I) -> long {
        /* GATE 276 (LUT3 _1450_ INIT 0xe8 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
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
    Ciphertext gin168 = 1 * gout149[1] + 2 * gout80[0] + 4 * gout10[0];
    std::vector<Ciphertext> gout168 = ctx.eval_lut_amortized(&gin168, lut168);

    std::vector<RotationPoly> lut169;
    std::vector<long (*)(long)> flut169;
    auto lut169idx0 = [](long I) -> long {
        /* GATE 236 (LUT3 _1410_ INIT 0x69 PERM 012) */
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
    lut169.push_back(ctx.genrate_lut(lut169idx0));
    flut169.push_back(lut169idx0);
    auto lut169idx1 = [](long I) -> long {
        /* GATE 281 (LUT3 _1455_ INIT 0x2b PERM 012) */
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
    lut169.push_back(ctx.genrate_lut(lut169idx1));
    flut169.push_back(lut169idx1);
    auto fvec169 = [flut169](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut169[i](I));
        return ret;
    };

    std::cerr << "\rLUT169   ";
    Ciphertext gin169 = 1 * gout159[1] + 2 * gout163[1] + 4 * gout161[0];
    std::vector<Ciphertext> gout169 = ctx.eval_lut_amortized(&gin169, lut169);

    std::vector<RotationPoly> lut170;
    std::vector<long (*)(long)> flut170;
    auto lut170idx0 = [](long I) -> long {
        /* GATE 54 (LUT3 _1228_ INIT 0x69 PERM 012) */
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
    lut170.push_back(ctx.genrate_lut(lut170idx0));
    flut170.push_back(lut170idx0);
    auto lut170idx1 = [](long I) -> long {
        /* GATE 99 (LUT3 _1273_ INIT 0x2b PERM 012) */
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
    lut170.push_back(ctx.genrate_lut(lut170idx1));
    flut170.push_back(lut170idx1);
    auto fvec170 = [flut170](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut170[i](I));
        return ret;
    };

    std::cerr << "\rLUT170   ";
    Ciphertext gin170 = 1 * gout150[1] + 2 * gout165[0] + 4 * gout135[0];
    std::vector<Ciphertext> gout170 = ctx.eval_lut_amortized(&gin170, lut170);

    std::vector<RotationPoly> lut171;
    std::vector<long (*)(long)> flut171;
    auto lut171idx0 = [](long I) -> long {
        /* GATE 145 (LUT3 _1319_ INIT 0x71 PERM 021) */
        switch (I) {
            case  0: return 1;
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
    lut171.push_back(ctx.genrate_lut(lut171idx0));
    flut171.push_back(lut171idx0);
    auto lut171idx1 = [](long I) -> long {
        /* GATE 106 (LUT3 _1280_ INIT 0x69 PERM 012) */
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
    lut171.push_back(ctx.genrate_lut(lut171idx1));
    flut171.push_back(lut171idx1);
    auto fvec171 = [flut171](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut171[i](I));
        return ret;
    };

    std::cerr << "\rLUT171   ";
    Ciphertext gin171 = 1 * gout148[0] + 2 * gout153[1] + 4 * gout140[1];
    std::vector<Ciphertext> gout171 = ctx.eval_lut_amortized(&gin171, lut171);

    std::vector<RotationPoly> lut172;
    std::vector<long (*)(long)> flut172;
    auto lut172idx0 = [](long I) -> long {
        /* GATE 386 (LUT3 _1560_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut172.push_back(ctx.genrate_lut(lut172idx0));
    flut172.push_back(lut172idx0);
    auto lut172idx1 = [](long I) -> long {
        /* GATE 367 (LUT3 _1541_ INIT 0x96 PERM 012) */
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
    lut172.push_back(ctx.genrate_lut(lut172idx1));
    flut172.push_back(lut172idx1);
    auto fvec172 = [flut172](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut172[i](I));
        return ret;
    };

    std::cerr << "\rLUT172   ";
    Ciphertext gin172 = 1 * gout137[1] + 2 * gout144[0] + 4 * gout156[0];
    std::vector<Ciphertext> gout172 = ctx.eval_lut_amortized(&gin172, lut172);

    std::vector<RotationPoly> lut173;
    std::vector<long (*)(long)> flut173;
    auto lut173idx0 = [](long I) -> long {
        /* GATE 384 (LUT3 _1558_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
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
    lut173.push_back(ctx.genrate_lut(lut173idx0));
    flut173.push_back(lut173idx0);
    auto lut173idx1 = [](long I) -> long {
        /* GATE 365 (LUT3 _1539_ INIT 0x96 PERM 012) */
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
    lut173.push_back(ctx.genrate_lut(lut173idx1));
    flut173.push_back(lut173idx1);
    auto fvec173 = [flut173](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut173[i](I));
        return ret;
    };

    std::cerr << "\rLUT173   ";
    Ciphertext gin173 = 1 * gout164[1] + 2 * gout172[1] + 4 * gout155[0];
    std::vector<Ciphertext> gout173 = ctx.eval_lut_amortized(&gin173, lut173);

    std::vector<RotationPoly> lut174;
    std::vector<long (*)(long)> flut174;
    auto lut174idx0 = [](long I) -> long {
        /* GATE 326 (LUT3 _1500_ INIT 0x69 PERM 012) */
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
    lut174.push_back(ctx.genrate_lut(lut174idx0));
    flut174.push_back(lut174idx0);
    auto lut174idx1 = [](long I) -> long {
        /* GATE 364 (LUT3 _1538_ INIT 0x71 PERM 021) */
        switch (I) {
            case  0: return 1;
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
    lut174.push_back(ctx.genrate_lut(lut174idx1));
    flut174.push_back(lut174idx1);
    auto fvec174 = [flut174](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut174[i](I));
        return ret;
    };

    std::cerr << "\rLUT174   ";
    Ciphertext gin174 = 1 * gout164[0] + 2 * gout151[1] + 4 * gout158[0];
    std::vector<Ciphertext> gout174 = ctx.eval_lut_amortized(&gin174, lut174);

    std::vector<RotationPoly> lut175;
    std::vector<long (*)(long)> flut175;
    auto lut175idx0 = [](long I) -> long {
        /* GATE 394 (LUT3 _1568_ INIT 0x41 PERM 021) */
        switch (I) {
            case  0: return 1;
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
    lut175.push_back(ctx.genrate_lut(lut175idx0));
    flut175.push_back(lut175idx0);
    auto fvec175 = [flut175](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut175[i](I));
        return ret;
    };

    std::cerr << "\rLUT175   ";
    Ciphertext gin175 = 1 * gout156[1] + 2 * gout172[0] + 4 * gout122[0];
    std::vector<Ciphertext> gout175 = ctx.eval_lut_amortized(&gin175, lut175);

    std::vector<RotationPoly> lut176;
    std::vector<long (*)(long)> flut176;
    auto lut176idx0 = [](long I) -> long {
        /* GATE 325 (LUT3 _1499_ INIT 0x96 PERM 012) */
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
    lut176.push_back(ctx.genrate_lut(lut176idx0));
    flut176.push_back(lut176idx0);
    auto lut176idx1 = [](long I) -> long {
        /* GATE 362 (LUT3 _1536_ INIT 0xd4 PERM 012) */
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
    lut176.push_back(ctx.genrate_lut(lut176idx1));
    flut176.push_back(lut176idx1);
    auto fvec176 = [flut176](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut176[i](I));
        return ret;
    };

    std::cerr << "\rLUT176   ";
    Ciphertext gin176 = 1 * gout174[0] + 2 * gout167[1] + 4 * gout154[0];
    std::vector<Ciphertext> gout176 = ctx.eval_lut_amortized(&gin176, lut176);

    std::vector<RotationPoly> lut177;
    std::vector<long (*)(long)> flut177;
    auto lut177idx0 = [](long I) -> long {
        /* GATE 190 (LUT3 _1364_ INIT 0x69 PERM 012) */
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
    lut177.push_back(ctx.genrate_lut(lut177idx0));
    flut177.push_back(lut177idx0);
    auto lut177idx1 = [](long I) -> long {
        /* GATE 235 (LUT3 _1409_ INIT 0x2b PERM 012) */
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
    lut177.push_back(ctx.genrate_lut(lut177idx1));
    flut177.push_back(lut177idx1);
    auto fvec177 = [flut177](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut177[i](I));
        return ret;
    };

    std::cerr << "\rLUT177   ";
    Ciphertext gin177 = 1 * gout160[1] + 2 * gout159[0] + 4 * gout168[0];
    std::vector<Ciphertext> gout177 = ctx.eval_lut_amortized(&gin177, lut177);

    std::vector<RotationPoly> lut178;
    std::vector<long (*)(long)> flut178;
    auto lut178idx0 = [](long I) -> long {
        /* GATE 144 (LUT3 _1318_ INIT 0x69 PERM 012) */
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
    lut178.push_back(ctx.genrate_lut(lut178idx0));
    flut178.push_back(lut178idx0);
    auto lut178idx1 = [](long I) -> long {
        /* GATE 189 (LUT3 _1363_ INIT 0x2b PERM 012) */
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
    lut178.push_back(ctx.genrate_lut(lut178idx1));
    flut178.push_back(lut178idx1);
    auto fvec178 = [flut178](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut178[i](I));
        return ret;
    };

    std::cerr << "\rLUT178   ";
    Ciphertext gin178 = 1 * gout171[0] + 2 * gout160[0] + 4 * gout162[0];
    std::vector<Ciphertext> gout178 = ctx.eval_lut_amortized(&gin178, lut178);

    std::vector<RotationPoly> lut179;
    std::vector<long (*)(long)> flut179;
    auto lut179idx0 = [](long I) -> long {
        /* GATE 280 (LUT3 _1454_ INIT 0x96 PERM 012) */
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
    lut179.push_back(ctx.genrate_lut(lut179idx0));
    flut179.push_back(lut179idx0);
    auto lut179idx1 = [](long I) -> long {
        /* GATE 358 (LUT3 _1532_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
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
    lut179.push_back(ctx.genrate_lut(lut179idx1));
    flut179.push_back(lut179idx1);
    auto fvec179 = [flut179](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut179[i](I));
        return ret;
    };

    std::cerr << "\rLUT179   ";
    Ciphertext gin179 = 1 * gout169[1] + 2 * gout167[0] + 4 * gout161[1];
    std::vector<Ciphertext> gout179 = ctx.eval_lut_amortized(&gin179, lut179);

    std::vector<RotationPoly> lut180;
    std::vector<long (*)(long)> flut180;
    auto lut180idx0 = [](long I) -> long {
        /* GATE 100 (LUT3 _1274_ INIT 0x69 PERM 012) */
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
    lut180.push_back(ctx.genrate_lut(lut180idx0));
    flut180.push_back(lut180idx0);
    auto lut180idx1 = [](long I) -> long {
        /* GATE 143 (LUT3 _1317_ INIT 0x71 PERM 021) */
        switch (I) {
            case  0: return 1;
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
    lut180.push_back(ctx.genrate_lut(lut180idx1));
    flut180.push_back(lut180idx1);
    auto fvec180 = [flut180](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut180[i](I));
        return ret;
    };

    std::cerr << "\rLUT180   ";
    Ciphertext gin180 = 1 * gout152[0] + 2 * gout165[1] + 4 * gout171[1];
    std::vector<Ciphertext> gout180 = ctx.eval_lut_amortized(&gin180, lut180);

    std::vector<RotationPoly> lut181;
    std::vector<long (*)(long)> flut181;
    auto lut181idx0 = [](long I) -> long {
        /* GATE 188 (LUT3 _1362_ INIT 0x96 PERM 012) */
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
    lut181.push_back(ctx.genrate_lut(lut181idx0));
    flut181.push_back(lut181idx0);
    auto lut181idx1 = [](long I) -> long {
        /* GATE 233 (LUT3 _1407_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
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
    lut181.push_back(ctx.genrate_lut(lut181idx1));
    flut181.push_back(lut181idx1);
    auto fvec181 = [flut181](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut181[i](I));
        return ret;
    };

    std::cerr << "\rLUT181   ";
    Ciphertext gin181 = 1 * gout178[1] + 2 * gout177[0] + 4 * gout162[1];
    std::vector<Ciphertext> gout181 = ctx.eval_lut_amortized(&gin181, lut181);

    std::vector<RotationPoly> lut182;
    std::vector<long (*)(long)> flut182;
    auto lut182idx0 = [](long I) -> long {
        /* GATE 142 (LUT3 _1316_ INIT 0x96 PERM 012) */
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
    lut182.push_back(ctx.genrate_lut(lut182idx0));
    flut182.push_back(lut182idx0);
    auto lut182idx1 = [](long I) -> long {
        /* GATE 187 (LUT3 _1361_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
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
    lut182.push_back(ctx.genrate_lut(lut182idx1));
    flut182.push_back(lut182idx1);
    auto fvec182 = [flut182](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut182[i](I));
        return ret;
    };

    std::cerr << "\rLUT182   ";
    Ciphertext gin182 = 1 * gout180[1] + 2 * gout178[0] + 4 * gout152[1];
    std::vector<Ciphertext> gout182 = ctx.eval_lut_amortized(&gin182, lut182);

    std::vector<RotationPoly> lut183;
    std::vector<long (*)(long)> flut183;
    auto lut183idx0 = [](long I) -> long {
        /* GATE 385 (LUT3 _1559_ INIT 0x96 PERM 120) */
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
    lut183.push_back(ctx.genrate_lut(lut183idx0));
    flut183.push_back(lut183idx0);
    auto lut183idx1 = [](long I) -> long {
        /* GATE 393 (LUT2 _1567_ INIT 0x4 PERM 12) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
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
    Ciphertext gin183 = 1 * gout156[1] + 2 * gout172[0] + 4 * gout122[0];
    std::vector<Ciphertext> gout183 = ctx.eval_lut_amortized(&gin183, lut183);

    std::vector<RotationPoly> lut184;
    std::vector<long (*)(long)> flut184;
    auto lut184idx0 = [](long I) -> long {
        /* GATE 52 (LUT3 _1226_ INIT 0x69 PERM 012) */
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
    lut184.push_back(ctx.genrate_lut(lut184idx0));
    flut184.push_back(lut184idx0);
    auto lut184idx1 = [](long I) -> long {
        /* GATE 97 (LUT3 _1271_ INIT 0x2b PERM 012) */
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
    lut184.push_back(ctx.genrate_lut(lut184idx1));
    flut184.push_back(lut184idx1);
    auto fvec184 = [flut184](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut184[i](I));
        return ret;
    };

    std::cerr << "\rLUT184   ";
    Ciphertext gin184 = 1 * gout166[0] + 2 * gout170[0] + 4 * gout99[1];
    std::vector<Ciphertext> gout184 = ctx.eval_lut_amortized(&gin184, lut184);

    std::vector<RotationPoly> lut185;
    std::vector<long (*)(long)> flut185;
    auto lut185idx0 = [](long I) -> long {
        /* GATE 234 (LUT3 _1408_ INIT 0x96 PERM 012) */
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
    lut185.push_back(ctx.genrate_lut(lut185idx0));
    flut185.push_back(lut185idx0);
    auto lut185idx1 = [](long I) -> long {
        /* GATE 279 (LUT3 _1453_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
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
    lut185.push_back(ctx.genrate_lut(lut185idx1));
    flut185.push_back(lut185idx1);
    auto fvec185 = [flut185](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut185[i](I));
        return ret;
    };

    std::cerr << "\rLUT185   ";
    Ciphertext gin185 = 1 * gout177[1] + 2 * gout169[0] + 4 * gout168[1];
    std::vector<Ciphertext> gout185 = ctx.eval_lut_amortized(&gin185, lut185);

    std::vector<RotationPoly> lut186;
    std::vector<long (*)(long)> flut186;
    auto lut186idx0 = [](long I) -> long {
        /* GATE 363 (LUT3 _1537_ INIT 0x96 PERM 012) */
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
    lut186.push_back(ctx.genrate_lut(lut186idx0));
    flut186.push_back(lut186idx0);
    auto lut186idx1 = [](long I) -> long {
        /* GATE 382 (LUT3 _1556_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
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
    lut186.push_back(ctx.genrate_lut(lut186idx1));
    flut186.push_back(lut186idx1);
    auto fvec186 = [flut186](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut186[i](I));
        return ret;
    };

    std::cerr << "\rLUT186   ";
    Ciphertext gin186 = 1 * gout174[1] + 2 * gout173[1] + 4 * gout158[1];
    std::vector<Ciphertext> gout186 = ctx.eval_lut_amortized(&gin186, lut186);

    std::vector<RotationPoly> lut187;
    std::vector<long (*)(long)> flut187;
    auto lut187idx0 = [](long I) -> long {
        /* GATE 141 (LUT3 _1315_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
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
    lut187.push_back(ctx.genrate_lut(lut187idx0));
    flut187.push_back(lut187idx0);
    auto lut187idx1 = [](long I) -> long {
        /* GATE 98 (LUT3 _1272_ INIT 0x96 PERM 012) */
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
    lut187.push_back(ctx.genrate_lut(lut187idx1));
    flut187.push_back(lut187idx1);
    auto fvec187 = [flut187](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut187[i](I));
        return ret;
    };

    std::cerr << "\rLUT187   ";
    Ciphertext gin187 = 1 * gout170[1] + 2 * gout180[0] + 4 * gout135[1];
    std::vector<Ciphertext> gout187 = ctx.eval_lut_amortized(&gin187, lut187);

    std::vector<RotationPoly> lut188;
    std::vector<long (*)(long)> flut188;
    auto lut188idx0 = [](long I) -> long {
        /* GATE 392 (LUT3 _1566_ INIT 0xd PERM 210) */
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
    lut188.push_back(ctx.genrate_lut(lut188idx0));
    flut188.push_back(lut188idx0);
    auto lut188idx1 = [](long I) -> long {
        /* GATE 383 (LUT2 _1557_ INIT 0x9 PERM 12) */
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
    lut188.push_back(ctx.genrate_lut(lut188idx1));
    flut188.push_back(lut188idx1);
    auto fvec188 = [flut188](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut188[i](I));
        return ret;
    };

    std::cerr << "\rLUT188   ";
    Ciphertext gin188 = 1 * gout183[1] + 2 * gout173[0] + 4 * gout183[0];
    std::vector<Ciphertext> gout188 = ctx.eval_lut_amortized(&gin188, lut188);

    std::vector<RotationPoly> lut189;
    std::vector<long (*)(long)> flut189;
    auto lut189idx0 = [](long I) -> long {
        /* GATE 379 (LUT2 _1553_ INIT 0x4 PERM 10) */
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
    lut189.push_back(ctx.genrate_lut(lut189idx0));
    flut189.push_back(lut189idx0);
    auto lut189idx1 = [](long I) -> long {
        /* GATE 361 (LUT2 _1535_ INIT 0x4 PERM 01) */
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
    lut189.push_back(ctx.genrate_lut(lut189idx1));
    flut189.push_back(lut189idx1);
    auto fvec189 = [flut189](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut189[i](I));
        return ret;
    };

    std::cerr << "\rLUT189   ";
    Ciphertext gin189 = 1 * gout176[1] + 2 * gout186[0];
    std::vector<Ciphertext> gout189 = ctx.eval_lut_amortized(&gin189, lut189);

    std::vector<RotationPoly> lut190;
    std::vector<long (*)(long)> flut190;
    auto lut190idx0 = [](long I) -> long {
        /* GATE 96 (LUT2 _1270_ INIT 0x4 PERM 01) */
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
    lut190.push_back(ctx.genrate_lut(lut190idx0));
    flut190.push_back(lut190idx0);
    auto lut190idx1 = [](long I) -> long {
        /* GATE 395 (LUT2 _1569_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
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
    Ciphertext gin190 = 1 * gout184[1] + 2 * gout187[1];
    std::vector<Ciphertext> gout190 = ctx.eval_lut_amortized(&gin190, lut190);

    std::vector<RotationPoly> lut191;
    std::vector<long (*)(long)> flut191;
    auto lut191idx0 = [](long I) -> long {
        /* GATE 391 (LUT2 _1565_ INIT 0x4 PERM 01) */
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
    lut191.push_back(ctx.genrate_lut(lut191idx0));
    flut191.push_back(lut191idx0);
    auto fvec191 = [flut191](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut191[i](I));
        return ret;
    };

    std::cerr << "\rLUT191   ";
    Ciphertext gin191 = 1 * gout175[0] + 2 * gout188[0];
    std::vector<Ciphertext> gout191 = ctx.eval_lut_amortized(&gin191, lut191);

    std::vector<RotationPoly> lut192;
    std::vector<long (*)(long)> flut192;
    auto lut192idx0 = [](long I) -> long {
        /* GATE 95 (LUT3 _1269_ INIT 0x69 PERM 012) */
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
    lut192.push_back(ctx.genrate_lut(lut192idx0));
    flut192.push_back(lut192idx0);
    auto lut192idx1 = [](long I) -> long {
        /* GATE 186 (LUT3 _1360_ INIT 0x71 PERM 021) */
        switch (I) {
            case  0: return 1;
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
    lut192.push_back(ctx.genrate_lut(lut192idx1));
    flut192.push_back(lut192idx1);
    auto fvec192 = [flut192](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut192[i](I));
        return ret;
    };

    std::cerr << "\rLUT192   ";
    Ciphertext gin192 = 1 * gout190[0] + 2 * gout187[0] + 4 * gout182[0];
    std::vector<Ciphertext> gout192 = ctx.eval_lut_amortized(&gin192, lut192);

    std::vector<RotationPoly> lut193;
    std::vector<long (*)(long)> flut193;
    auto lut193idx0 = [](long I) -> long {
        /* GATE 185 (LUT3 _1359_ INIT 0x96 PERM 012) */
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
    lut193.push_back(ctx.genrate_lut(lut193idx0));
    flut193.push_back(lut193idx0);
    auto lut193idx1 = [](long I) -> long {
        /* GATE 232 (LUT3 _1406_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
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
    Ciphertext gin193 = 1 * gout192[1] + 2 * gout182[1] + 4 * gout181[0];
    std::vector<Ciphertext> gout193 = ctx.eval_lut_amortized(&gin193, lut193);

    std::vector<RotationPoly> lut194;
    std::vector<long (*)(long)> flut194;
    auto lut194idx0 = [](long I) -> long {
        /* GATE 231 (LUT3 _1405_ INIT 0x96 PERM 012) */
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
    lut194.push_back(ctx.genrate_lut(lut194idx0));
    flut194.push_back(lut194idx0);
    auto lut194idx1 = [](long I) -> long {
        /* GATE 278 (LUT3 _1452_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
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
    Ciphertext gin194 = 1 * gout193[1] + 2 * gout181[1] + 4 * gout185[0];
    std::vector<Ciphertext> gout194 = ctx.eval_lut_amortized(&gin194, lut194);

    std::vector<RotationPoly> lut195;
    std::vector<long (*)(long)> flut195;
    auto lut195idx0 = [](long I) -> long {
        /* GATE 324 (LUT3 _1498_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut195.push_back(ctx.genrate_lut(lut195idx0));
    flut195.push_back(lut195idx0);
    auto lut195idx1 = [](long I) -> long {
        /* GATE 277 (LUT3 _1451_ INIT 0x96 PERM 012) */
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
    lut195.push_back(ctx.genrate_lut(lut195idx1));
    flut195.push_back(lut195idx1);
    auto fvec195 = [flut195](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut195[i](I));
        return ret;
    };

    std::cerr << "\rLUT195   ";
    Ciphertext gin195 = 1 * gout194[1] + 2 * gout185[1] + 4 * gout179[0];
    std::vector<Ciphertext> gout195 = ctx.eval_lut_amortized(&gin195, lut195);

    std::vector<RotationPoly> lut196;
    std::vector<long (*)(long)> flut196;
    auto lut196idx0 = [](long I) -> long {
        /* GATE 323 (LUT3 _1497_ INIT 0x96 PERM 012) */
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
    lut196.push_back(ctx.genrate_lut(lut196idx0));
    flut196.push_back(lut196idx0);
    auto lut196idx1 = [](long I) -> long {
        /* GATE 360 (LUT3 _1534_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
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
    lut196.push_back(ctx.genrate_lut(lut196idx1));
    flut196.push_back(lut196idx1);
    auto fvec196 = [flut196](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut196[i](I));
        return ret;
    };

    std::cerr << "\rLUT196   ";
    Ciphertext gin196 = 1 * gout195[0] + 2 * gout176[0] + 4 * gout179[1];
    std::vector<Ciphertext> gout196 = ctx.eval_lut_amortized(&gin196, lut196);

    std::vector<RotationPoly> lut197;
    std::vector<long (*)(long)> flut197;
    auto lut197idx0 = [](long I) -> long {
        /* GATE 359 (LUT3 _1533_ INIT 0x1e PERM 012) */
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
    lut197.push_back(ctx.genrate_lut(lut197idx0));
    flut197.push_back(lut197idx0);
    auto lut197idx1 = [](long I) -> long {
        /* GATE 381 (LUT3 _1555_ INIT 0xb PERM 021) */
        switch (I) {
            case  0: return 1;
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
    lut197.push_back(ctx.genrate_lut(lut197idx1));
    flut197.push_back(lut197idx1);
    auto fvec197 = [flut197](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut197[i](I));
        return ret;
    };

    std::cerr << "\rLUT197   ";
    Ciphertext gin197 = 1 * gout189[1] + 2 * gout189[0] + 4 * gout196[1];
    std::vector<Ciphertext> gout197 = ctx.eval_lut_amortized(&gin197, lut197);

    std::vector<RotationPoly> lut198;
    std::vector<long (*)(long)> flut198;
    auto lut198idx0 = [](long I) -> long {
        /* GATE 380 (LUT3 _1554_ INIT 0x69 PERM 012) */
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
    lut198.push_back(ctx.genrate_lut(lut198idx0));
    flut198.push_back(lut198idx0);
    auto lut198idx1 = [](long I) -> long {
        /* GATE 390 (LUT3 _1564_ INIT 0x71 PERM 021) */
        switch (I) {
            case  0: return 1;
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
    lut198.push_back(ctx.genrate_lut(lut198idx1));
    flut198.push_back(lut198idx1);
    auto fvec198 = [flut198](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut198[i](I));
        return ret;
    };

    std::cerr << "\rLUT198   ";
    Ciphertext gin198 = 1 * gout197[1] + 2 * gout186[1] + 4 * gout188[1];
    std::vector<Ciphertext> gout198 = ctx.eval_lut_amortized(&gin198, lut198);

    std::vector<RotationPoly> lut199;
    std::vector<long (*)(long)> flut199;
    auto lut199idx0 = [](long I) -> long {
        /* GATE 396 (LUT2 _1570_ INIT 0x1 PERM 01) */
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
    lut199.push_back(ctx.genrate_lut(lut199idx0));
    flut199.push_back(lut199idx0);
    auto lut199idx1 = [](long I) -> long {
        /* GATE 389 (LUT2 _1563_ INIT 0x6 PERM 01) */
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
    lut199.push_back(ctx.genrate_lut(lut199idx1));
    flut199.push_back(lut199idx1);
    auto fvec199 = [flut199](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut199[i](I));
        return ret;
    };

    std::cerr << "\rLUT199   ";
    Ciphertext gin199 = 1 * gout198[1] + 2 * gout191[0];
    std::vector<Ciphertext> gout199 = ctx.eval_lut_amortized(&gin199, lut199);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(ctx.decrypt(&gout139[1])); /* out192 */
    test_out.push_back(ctx.decrypt(&gout166[1])); /* out193 */
    test_out.push_back(ctx.decrypt(&gout184[0])); /* out194 */
    test_out.push_back(ctx.decrypt(&gout190[1])); /* out195 */
    test_out.push_back(ctx.decrypt(&gout192[0])); /* out196 */
    test_out.push_back(ctx.decrypt(&gout193[0])); /* out197 */
    test_out.push_back(ctx.decrypt(&gout194[0])); /* out198 */
    test_out.push_back(ctx.decrypt(&gout195[1])); /* out199 */
    test_out.push_back(ctx.decrypt(&gout196[0])); /* out200 */
    test_out.push_back(ctx.decrypt(&gout197[0])); /* out201 */
    test_out.push_back(ctx.decrypt(&gout198[0])); /* out202 */
    test_out.push_back(ctx.decrypt(&gout199[1])); /* out203 */
    test_out.push_back(ctx.decrypt(&gout199[0])); /* out204 */
    return test_out;
}

static void
BM_sum3d_lut3(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(rlwe_hom_acc_scheme_C_11_NTT);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(8);

    for (auto _ : state) {
        test_sum3d_lut3(ctx);
    }
}

BENCHMARK(BM_sum3d_lut3)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
