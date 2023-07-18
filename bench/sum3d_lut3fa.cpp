#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_sum3d_lut3fa(FHEContext& ctx, std::vector<uint64_t> out = { 0 })
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

    std::cerr << "\rFA0    ";
    Ciphertext gin0 = 0 + 1 * ct_out184 + 2 * ct_out185 + 1 * ct_out88 + 2 * ct_out89;
    std::vector<Ciphertext> gout0 = ctx.eval_lut_amortized(&gin0, decomp);

    std::cerr << "\rFA1    ";
    Ciphertext gin1 = 0 + 1 * ct_out168 + 2 * ct_out169 + 1 * ct_out72 + 2 * ct_out73;
    std::vector<Ciphertext> gout1 = ctx.eval_lut_amortized(&gin1, decomp);

    std::cerr << "\rFA2    ";
    Ciphertext gin2 = 0 + 1 * ct_out128 + 2 * ct_out129 + 1 * ct_out32 + 2 * ct_out33;
    std::vector<Ciphertext> gout2 = ctx.eval_lut_amortized(&gin2, decomp);

    std::cerr << "\rFA3    ";
    Ciphertext gin3 = 0 + 1 * ct_out152 + 2 * ct_out153 + 1 * ct_out56 + 2 * ct_out57;
    std::vector<Ciphertext> gout3 = ctx.eval_lut_amortized(&gin3, decomp);

    std::cerr << "\rFA4    ";
    Ciphertext gin4 = gout0[2] + 1 * ct_out186 + 2 * ct_out187 + 1 * ct_out90 + 2 * ct_out91;
    std::vector<Ciphertext> gout4 = ctx.eval_lut_amortized(&gin4, decomp);

    std::cerr << "\rFA5    ";
    Ciphertext gin5 = gout1[2] + 1 * ct_out170 + 2 * ct_out171 + 1 * ct_out74 + 2 * ct_out75;
    std::vector<Ciphertext> gout5 = ctx.eval_lut_amortized(&gin5, decomp);

    std::cerr << "\rFA6    ";
    Ciphertext gin6 = 0 + 1 * ct_out144 + 2 * ct_out145 + 1 * ct_out48 + 2 * ct_out49;
    std::vector<Ciphertext> gout6 = ctx.eval_lut_amortized(&gin6, decomp);

    std::cerr << "\rFA7    ";
    Ciphertext gin7 = 0 + 1 * ct_out112 + 2 * ct_out113 + 1 * ct_out16 + 2 * ct_out17;
    std::vector<Ciphertext> gout7 = ctx.eval_lut_amortized(&gin7, decomp);

    std::cerr << "\rFA8    ";
    Ciphertext gin8 = 0 + 1 * ct_out104 + 2 * ct_out105 + 1 * ct_out8 + 2 * ct_out9;
    std::vector<Ciphertext> gout8 = ctx.eval_lut_amortized(&gin8, decomp);

    std::cerr << "\rFA9    ";
    Ciphertext gin9 = gout4[2] + 1 * ct_out188 + 2 * ct_out189 + 1 * ct_out92 + 2 * ct_out93;
    std::vector<Ciphertext> gout9 = ctx.eval_lut_amortized(&gin9, decomp);

    std::cerr << "\rFA10    ";
    Ciphertext gin10 = 0 + 1 * ct_out136 + 2 * ct_out137 + 1 * ct_out40 + 2 * ct_out41;
    std::vector<Ciphertext> gout10 = ctx.eval_lut_amortized(&gin10, decomp);

    std::cerr << "\rFA11    ";
    Ciphertext gin11 = gout5[2] + 1 * ct_out172 + 2 * ct_out173 + 1 * ct_out76 + 2 * ct_out77;
    std::vector<Ciphertext> gout11 = ctx.eval_lut_amortized(&gin11, decomp);

    std::cerr << "\rFA12    ";
    Ciphertext gin12 = gout10[2] + 1 * ct_out138 + 2 * ct_out139 + 1 * ct_out42 + 2 * ct_out43;
    std::vector<Ciphertext> gout12 = ctx.eval_lut_amortized(&gin12, decomp);

    std::cerr << "\rFA13    ";
    Ciphertext gin13 = 0 + 1 * gout2[0] + 2 * gout2[1] + 1 * gout10[0] + 2 * gout10[1];
    std::vector<Ciphertext> gout13 = ctx.eval_lut_amortized(&gin13, decomp);

    std::cerr << "\rFA14    ";
    Ciphertext gin14 = 0 + 1 * ct_out176 + 2 * ct_out177 + 1 * ct_out80 + 2 * ct_out81;
    std::vector<Ciphertext> gout14 = ctx.eval_lut_amortized(&gin14, decomp);

    std::cerr << "\rFA15    ";
    Ciphertext gin15 = 0 + 1 * ct_out120 + 2 * ct_out121 + 1 * ct_out24 + 2 * ct_out25;
    std::vector<Ciphertext> gout15 = ctx.eval_lut_amortized(&gin15, decomp);

    std::cerr << "\rFA16    ";
    Ciphertext gin16 = gout9[2] + 1 * ct_out190 + 2 * ct_out191 + 1 * ct_out94 + 2 * ct_out95;
    std::vector<Ciphertext> gout16 = ctx.eval_lut_amortized(&gin16, decomp);

    std::cerr << "\rFA17    ";
    Ciphertext gin17 = gout6[2] + 1 * ct_out146 + 2 * ct_out147 + 1 * ct_out50 + 2 * ct_out51;
    std::vector<Ciphertext> gout17 = ctx.eval_lut_amortized(&gin17, decomp);

    std::cerr << "\rFA18    ";
    Ciphertext gin18 = gout8[2] + 1 * ct_out106 + 2 * ct_out107 + 1 * ct_out10 + 2 * ct_out11;
    std::vector<Ciphertext> gout18 = ctx.eval_lut_amortized(&gin18, decomp);

    std::cerr << "\rFA19    ";
    Ciphertext gin19 = gout2[2] + 1 * ct_out130 + 2 * ct_out131 + 1 * ct_out34 + 2 * ct_out35;
    std::vector<Ciphertext> gout19 = ctx.eval_lut_amortized(&gin19, decomp);

    std::cerr << "\rFA20    ";
    Ciphertext gin20 = 0 + 1 * ct_out160 + 2 * ct_out161 + 1 * ct_out64 + 2 * ct_out65;
    std::vector<Ciphertext> gout20 = ctx.eval_lut_amortized(&gin20, decomp);

    std::cerr << "\rFA21    ";
    Ciphertext gin21 = 0 + 1 * gout6[0] + 2 * gout6[1] + 1 * gout3[0] + 2 * gout3[1];
    std::vector<Ciphertext> gout21 = ctx.eval_lut_amortized(&gin21, decomp);

    std::cerr << "\rFA22    ";
    Ciphertext gin22 = gout3[2] + 1 * ct_out154 + 2 * ct_out155 + 1 * ct_out58 + 2 * ct_out59;
    std::vector<Ciphertext> gout22 = ctx.eval_lut_amortized(&gin22, decomp);

    std::cerr << "\rFA23    ";
    Ciphertext gin23 = gout7[2] + 1 * ct_out114 + 2 * ct_out115 + 1 * ct_out18 + 2 * ct_out19;
    std::vector<Ciphertext> gout23 = ctx.eval_lut_amortized(&gin23, decomp);

    std::cerr << "\rFA24    ";
    Ciphertext gin24 = gout12[2] + 1 * ct_out140 + 2 * ct_out141 + 1 * ct_out44 + 2 * ct_out45;
    std::vector<Ciphertext> gout24 = ctx.eval_lut_amortized(&gin24, decomp);

    std::cerr << "\rFA25    ";
    Ciphertext gin25 = 0 + 1 * gout13[0] + 2 * gout13[1] + 1 * gout21[0] + 2 * gout21[1];
    std::vector<Ciphertext> gout25 = ctx.eval_lut_amortized(&gin25, decomp);

    std::cerr << "\rFA26    ";
    Ciphertext gin26 = 0 + 1 * ct_out96 + 2 * ct_out97 + 1 * ct_out0 + 2 * ct_out1;
    std::vector<Ciphertext> gout26 = ctx.eval_lut_amortized(&gin26, decomp);

    std::cerr << "\rFA27    ";
    Ciphertext gin27 = 0 + 1 * gout14[0] + 2 * gout14[1] + 1 * gout0[0] + 2 * gout0[1];
    std::vector<Ciphertext> gout27 = ctx.eval_lut_amortized(&gin27, decomp);

    std::cerr << "\rFA28    ";
    Ciphertext gin28 = gout11[2] + 1 * ct_out174 + 2 * ct_out175 + 1 * ct_out78 + 2 * ct_out79;
    std::vector<Ciphertext> gout28 = ctx.eval_lut_amortized(&gin28, decomp);

    std::cerr << "\rFA29    ";
    Ciphertext gin29 = gout14[2] + 1 * ct_out178 + 2 * ct_out179 + 1 * ct_out82 + 2 * ct_out83;
    std::vector<Ciphertext> gout29 = ctx.eval_lut_amortized(&gin29, decomp);

    std::cerr << "\rFA30    ";
    Ciphertext gin30 = gout15[2] + 1 * ct_out122 + 2 * ct_out123 + 1 * ct_out26 + 2 * ct_out27;
    std::vector<Ciphertext> gout30 = ctx.eval_lut_amortized(&gin30, decomp);

    std::cerr << "\rFA31    ";
    Ciphertext gin31 = gout17[2] + 1 * ct_out148 + 2 * ct_out149 + 1 * ct_out52 + 2 * ct_out53;
    std::vector<Ciphertext> gout31 = ctx.eval_lut_amortized(&gin31, decomp);

    std::cerr << "\rFA32    ";
    Ciphertext gin32 = gout18[2] + 1 * ct_out108 + 2 * ct_out109 + 1 * ct_out12 + 2 * ct_out13;
    std::vector<Ciphertext> gout32 = ctx.eval_lut_amortized(&gin32, decomp);

    std::cerr << "\rFA33    ";
    Ciphertext gin33 = gout23[2] + 1 * ct_out116 + 2 * ct_out117 + 1 * ct_out20 + 2 * ct_out21;
    std::vector<Ciphertext> gout33 = ctx.eval_lut_amortized(&gin33, decomp);

    std::cerr << "\rFA34    ";
    Ciphertext gin34 = gout19[2] + 1 * ct_out132 + 2 * ct_out133 + 1 * ct_out36 + 2 * ct_out37;
    std::vector<Ciphertext> gout34 = ctx.eval_lut_amortized(&gin34, decomp);

    std::cerr << "\rFA35    ";
    Ciphertext gin35 = gout31[2] + 1 * ct_out150 + 2 * ct_out151 + 1 * ct_out54 + 2 * ct_out55;
    std::vector<Ciphertext> gout35 = ctx.eval_lut_amortized(&gin35, decomp);

    std::cerr << "\rFA36    ";
    Ciphertext gin36 = gout13[2] + 1 * gout19[0] + 2 * gout19[1] + 1 * gout12[0] + 2 * gout12[1];
    std::vector<Ciphertext> gout36 = ctx.eval_lut_amortized(&gin36, decomp);

    std::cerr << "\rFA37    ";
    Ciphertext gin37 = gout29[2] + 1 * ct_out180 + 2 * ct_out181 + 1 * ct_out84 + 2 * ct_out85;
    std::vector<Ciphertext> gout37 = ctx.eval_lut_amortized(&gin37, decomp);

    std::cerr << "\rFA38    ";
    Ciphertext gin38 = 0 + 1 * gout7[0] + 2 * gout7[1] + 1 * gout15[0] + 2 * gout15[1];
    std::vector<Ciphertext> gout38 = ctx.eval_lut_amortized(&gin38, decomp);

    std::cerr << "\rFA39    ";
    Ciphertext gin39 = gout24[2] + 1 * ct_out142 + 2 * ct_out143 + 1 * ct_out46 + 2 * ct_out47;
    std::vector<Ciphertext> gout39 = ctx.eval_lut_amortized(&gin39, decomp);

    std::cerr << "\rFA40    ";
    Ciphertext gin40 = 0 + 1 * gout26[0] + 2 * gout26[1] + 1 * gout8[0] + 2 * gout8[1];
    std::vector<Ciphertext> gout40 = ctx.eval_lut_amortized(&gin40, decomp);

    std::cerr << "\rFA41    ";
    Ciphertext gin41 = gout27[2] + 1 * gout29[0] + 2 * gout29[1] + 1 * gout4[0] + 2 * gout4[1];
    std::vector<Ciphertext> gout41 = ctx.eval_lut_amortized(&gin41, decomp);

    std::cerr << "\rFA42    ";
    Ciphertext gin42 = gout20[2] + 1 * ct_out162 + 2 * ct_out163 + 1 * ct_out66 + 2 * ct_out67;
    std::vector<Ciphertext> gout42 = ctx.eval_lut_amortized(&gin42, decomp);

    std::cerr << "\rFA43    ";
    Ciphertext gin43 = gout22[2] + 1 * ct_out156 + 2 * ct_out157 + 1 * ct_out60 + 2 * ct_out61;
    std::vector<Ciphertext> gout43 = ctx.eval_lut_amortized(&gin43, decomp);

    std::cerr << "\rFA44    ";
    Ciphertext gin44 = gout21[2] + 1 * gout17[0] + 2 * gout17[1] + 1 * gout22[0] + 2 * gout22[1];
    std::vector<Ciphertext> gout44 = ctx.eval_lut_amortized(&gin44, decomp);

    std::cerr << "\rFA45    ";
    Ciphertext gin45 = 0 + 1 * gout20[0] + 2 * gout20[1] + 1 * gout1[0] + 2 * gout1[1];
    std::vector<Ciphertext> gout45 = ctx.eval_lut_amortized(&gin45, decomp);

    std::cerr << "\rFA46    ";
    Ciphertext gin46 = gout30[2] + 1 * ct_out124 + 2 * ct_out125 + 1 * ct_out28 + 2 * ct_out29;
    std::vector<Ciphertext> gout46 = ctx.eval_lut_amortized(&gin46, decomp);

    std::cerr << "\rFA47    ";
    Ciphertext gin47 = gout32[2] + 1 * ct_out110 + 2 * ct_out111 + 1 * ct_out14 + 2 * ct_out15;
    std::vector<Ciphertext> gout47 = ctx.eval_lut_amortized(&gin47, decomp);

    std::cerr << "\rFA48    ";
    Ciphertext gin48 = gout34[2] + 1 * ct_out134 + 2 * ct_out135 + 1 * ct_out38 + 2 * ct_out39;
    std::vector<Ciphertext> gout48 = ctx.eval_lut_amortized(&gin48, decomp);

    std::cerr << "\rFA49    ";
    Ciphertext gin49 = gout36[2] + 1 * gout34[0] + 2 * gout34[1] + 1 * gout24[0] + 2 * gout24[1];
    std::vector<Ciphertext> gout49 = ctx.eval_lut_amortized(&gin49, decomp);

    std::cerr << "\rFA50    ";
    Ciphertext gin50 = gout26[2] + 1 * ct_out98 + 2 * ct_out99 + 1 * ct_out2 + 2 * ct_out3;
    std::vector<Ciphertext> gout50 = ctx.eval_lut_amortized(&gin50, decomp);

    std::cerr << "\rFA51    ";
    Ciphertext gin51 = gout42[2] + 1 * ct_out164 + 2 * ct_out165 + 1 * ct_out68 + 2 * ct_out69;
    std::vector<Ciphertext> gout51 = ctx.eval_lut_amortized(&gin51, decomp);

    std::cerr << "\rFA52    ";
    Ciphertext gin52 = gout43[2] + 1 * ct_out158 + 2 * ct_out159 + 1 * ct_out62 + 2 * ct_out63;
    std::vector<Ciphertext> gout52 = ctx.eval_lut_amortized(&gin52, decomp);

    std::cerr << "\rFA53    ";
    Ciphertext gin53 = gout44[2] + 1 * gout31[0] + 2 * gout31[1] + 1 * gout43[0] + 2 * gout43[1];
    std::vector<Ciphertext> gout53 = ctx.eval_lut_amortized(&gin53, decomp);

    std::cerr << "\rFA54    ";
    Ciphertext gin54 = gout33[2] + 1 * ct_out118 + 2 * ct_out119 + 1 * ct_out22 + 2 * ct_out23;
    std::vector<Ciphertext> gout54 = ctx.eval_lut_amortized(&gin54, decomp);

    std::cerr << "\rFA55    ";
    Ciphertext gin55 = 0 + 1 * gout40[0] + 2 * gout40[1] + 1 * gout38[0] + 2 * gout38[1];
    std::vector<Ciphertext> gout55 = ctx.eval_lut_amortized(&gin55, decomp);

    std::cerr << "\rFA56    ";
    Ciphertext gin56 = 0 + 1 * gout55[0] + 2 * gout55[1] + 1 * gout25[0] + 2 * gout25[1];
    std::vector<Ciphertext> gout56 = ctx.eval_lut_amortized(&gin56, decomp);

    std::cerr << "\rFA57    ";
    Ciphertext gin57 = gout41[2] + 1 * gout37[0] + 2 * gout37[1] + 1 * gout9[0] + 2 * gout9[1];
    std::vector<Ciphertext> gout57 = ctx.eval_lut_amortized(&gin57, decomp);

    std::cerr << "\rFA58    ";
    Ciphertext gin58 = gout46[2] + 1 * ct_out126 + 2 * ct_out127 + 1 * ct_out30 + 2 * ct_out31;
    std::vector<Ciphertext> gout58 = ctx.eval_lut_amortized(&gin58, decomp);

    std::cerr << "\rFA59    ";
    Ciphertext gin59 = gout37[2] + 1 * ct_out182 + 2 * ct_out183 + 1 * ct_out86 + 2 * ct_out87;
    std::vector<Ciphertext> gout59 = ctx.eval_lut_amortized(&gin59, decomp);

    std::cerr << "\rFA60    ";
    Ciphertext gin60 = gout38[2] + 1 * gout23[0] + 2 * gout23[1] + 1 * gout30[0] + 2 * gout30[1];
    std::vector<Ciphertext> gout60 = ctx.eval_lut_amortized(&gin60, decomp);

    std::cerr << "\rFA61    ";
    Ciphertext gin61 = gout40[2] + 1 * gout50[0] + 2 * gout50[1] + 1 * gout18[0] + 2 * gout18[1];
    std::vector<Ciphertext> gout61 = ctx.eval_lut_amortized(&gin61, decomp);

    std::cerr << "\rFA62    ";
    Ciphertext gin62 = gout49[2] + 1 * gout48[0] + 2 * gout48[1] + 1 * gout39[0] + 2 * gout39[1];
    std::vector<Ciphertext> gout62 = ctx.eval_lut_amortized(&gin62, decomp);

    std::cerr << "\rFA63    ";
    Ciphertext gin63 = gout57[2] + 1 * gout59[0] + 2 * gout59[1] + 1 * gout16[0] + 2 * gout16[1];
    std::vector<Ciphertext> gout63 = ctx.eval_lut_amortized(&gin63, decomp);

    std::cerr << "\rFA64    ";
    Ciphertext gin64 = gout25[2] + 1 * gout36[0] + 2 * gout36[1] + 1 * gout44[0] + 2 * gout44[1];
    std::vector<Ciphertext> gout64 = ctx.eval_lut_amortized(&gin64, decomp);

    std::cerr << "\rFA65    ";
    Ciphertext gin65 = gout51[2] + 1 * ct_out166 + 2 * ct_out167 + 1 * ct_out70 + 2 * ct_out71;
    std::vector<Ciphertext> gout65 = ctx.eval_lut_amortized(&gin65, decomp);

    std::cerr << "\rFA66    ";
    Ciphertext gin66 = gout53[2] + 1 * gout35[0] + 2 * gout35[1] + 1 * gout52[0] + 2 * gout52[1];
    std::vector<Ciphertext> gout66 = ctx.eval_lut_amortized(&gin66, decomp);

    std::cerr << "\rFA67    ";
    Ciphertext gin67 = 0 + 1 * gout45[0] + 2 * gout45[1] + 1 * gout27[0] + 2 * gout27[1];
    std::vector<Ciphertext> gout67 = ctx.eval_lut_amortized(&gin67, decomp);

    std::cerr << "\rFA68    ";
    Ciphertext gin68 = gout45[2] + 1 * gout42[0] + 2 * gout42[1] + 1 * gout5[0] + 2 * gout5[1];
    std::vector<Ciphertext> gout68 = ctx.eval_lut_amortized(&gin68, decomp);

    std::cerr << "\rFA69    ";
    Ciphertext gin69 = gout63[2] + 1 * gout59[2] + 1 * gout16[2];
    std::vector<Ciphertext> gout69 = ctx.eval_lut_amortized(&gin69, decomp);

    std::cerr << "\rFA70    ";
    Ciphertext gin70 = gout66[2] + 1 * gout35[2] + 1 * gout52[2];
    std::vector<Ciphertext> gout70 = ctx.eval_lut_amortized(&gin70, decomp);

    std::cerr << "\rFA71    ";
    Ciphertext gin71 = gout50[2] + 1 * ct_out100 + 2 * ct_out101 + 1 * ct_out4 + 2 * ct_out5;
    std::vector<Ciphertext> gout71 = ctx.eval_lut_amortized(&gin71, decomp);

    std::cerr << "\rFA72    ";
    Ciphertext gin72 = gout60[2] + 1 * gout33[0] + 2 * gout33[1] + 1 * gout46[0] + 2 * gout46[1];
    std::vector<Ciphertext> gout72 = ctx.eval_lut_amortized(&gin72, decomp);

    std::cerr << "\rFA73    ";
    Ciphertext gin73 = gout61[2] + 1 * gout71[0] + 2 * gout71[1] + 1 * gout32[0] + 2 * gout32[1];
    std::vector<Ciphertext> gout73 = ctx.eval_lut_amortized(&gin73, decomp);

    std::cerr << "\rFA74    ";
    Ciphertext gin74 = gout55[2] + 1 * gout61[0] + 2 * gout61[1] + 1 * gout60[0] + 2 * gout60[1];
    std::vector<Ciphertext> gout74 = ctx.eval_lut_amortized(&gin74, decomp);

    std::cerr << "\rFA75    ";
    Ciphertext gin75 = gout64[2] + 1 * gout49[0] + 2 * gout49[1] + 1 * gout53[0] + 2 * gout53[1];
    std::vector<Ciphertext> gout75 = ctx.eval_lut_amortized(&gin75, decomp);

    std::cerr << "\rFA76    ";
    Ciphertext gin76 = 0 + 1 * gout56[0] + 2 * gout56[1] + 1 * gout67[0] + 2 * gout67[1];
    std::vector<Ciphertext> gout76 = ctx.eval_lut_amortized(&gin76, decomp);

    std::cerr << "\rFA77    ";
    Ciphertext gin77 = gout68[2] + 1 * gout51[0] + 2 * gout51[1] + 1 * gout11[0] + 2 * gout11[1];
    std::vector<Ciphertext> gout77 = ctx.eval_lut_amortized(&gin77, decomp);

    std::cerr << "\rFA78    ";
    Ciphertext gin78 = gout67[2] + 1 * gout68[0] + 2 * gout68[1] + 1 * gout41[0] + 2 * gout41[1];
    std::vector<Ciphertext> gout78 = ctx.eval_lut_amortized(&gin78, decomp);

    std::cerr << "\rFA79    ";
    Ciphertext gin79 = gout72[2] + 1 * gout54[0] + 2 * gout54[1] + 1 * gout58[0] + 2 * gout58[1];
    std::vector<Ciphertext> gout79 = ctx.eval_lut_amortized(&gin79, decomp);

    std::cerr << "\rFA80    ";
    Ciphertext gin80 = gout77[2] + 1 * gout65[0] + 2 * gout65[1] + 1 * gout28[0] + 2 * gout28[1];
    std::vector<Ciphertext> gout80 = ctx.eval_lut_amortized(&gin80, decomp);

    std::cerr << "\rFA81    ";
    Ciphertext gin81 = gout62[2] + 1 * gout48[2] + 1 * gout39[2];
    std::vector<Ciphertext> gout81 = ctx.eval_lut_amortized(&gin81, decomp);

    std::cerr << "\rFA82    ";
    Ciphertext gin82 = gout56[2] + 1 * gout74[0] + 2 * gout74[1] + 1 * gout64[0] + 2 * gout64[1];
    std::vector<Ciphertext> gout82 = ctx.eval_lut_amortized(&gin82, decomp);

    std::cerr << "\rFA83    ";
    Ciphertext gin83 = gout74[2] + 1 * gout73[0] + 2 * gout73[1] + 1 * gout72[0] + 2 * gout72[1];
    std::vector<Ciphertext> gout83 = ctx.eval_lut_amortized(&gin83, decomp);

    std::cerr << "\rFA84    ";
    Ciphertext gin84 = gout71[2] + 1 * ct_out102 + 2 * ct_out103 + 1 * ct_out6 + 2 * ct_out7;
    std::vector<Ciphertext> gout84 = ctx.eval_lut_amortized(&gin84, decomp);

    std::cerr << "\rFA85    ";
    Ciphertext gin85 = gout78[2] + 1 * gout77[0] + 2 * gout77[1] + 1 * gout57[0] + 2 * gout57[1];
    std::vector<Ciphertext> gout85 = ctx.eval_lut_amortized(&gin85, decomp);

    std::cerr << "\rFA86    ";
    Ciphertext gin86 = gout76[2] + 1 * gout82[0] + 2 * gout82[1] + 1 * gout78[0] + 2 * gout78[1];
    std::vector<Ciphertext> gout86 = ctx.eval_lut_amortized(&gin86, decomp);

    std::cerr << "\rFA87    ";
    Ciphertext gin87 = gout75[2] + 1 * gout62[0] + 2 * gout62[1] + 1 * gout66[0] + 2 * gout66[1];
    std::vector<Ciphertext> gout87 = ctx.eval_lut_amortized(&gin87, decomp);

    std::cerr << "\rFA88    ";
    Ciphertext gin88 = gout82[2] + 1 * gout83[0] + 2 * gout83[1] + 1 * gout75[0] + 2 * gout75[1];
    std::vector<Ciphertext> gout88 = ctx.eval_lut_amortized(&gin88, decomp);

    std::cerr << "\rFA89    ";
    Ciphertext gin89 = gout79[2] + 1 * gout54[2] + 1 * gout58[2];
    std::vector<Ciphertext> gout89 = ctx.eval_lut_amortized(&gin89, decomp);

    std::cerr << "\rFA90    ";
    Ciphertext gin90 = gout73[2] + 1 * gout84[0] + 2 * gout84[1] + 1 * gout47[0] + 2 * gout47[1];
    std::vector<Ciphertext> gout90 = ctx.eval_lut_amortized(&gin90, decomp);

    std::cerr << "\rFA91    ";
    Ciphertext gin91 = gout86[2] + 1 * gout88[0] + 2 * gout88[1] + 1 * gout85[0] + 2 * gout85[1];
    std::vector<Ciphertext> gout91 = ctx.eval_lut_amortized(&gin91, decomp);

    std::cerr << "\rFA92    ";
    Ciphertext gin92 = gout87[2] + 1 * gout81[0] + 2 * gout81[1] + 1 * gout70[0] + 2 * gout70[1];
    std::vector<Ciphertext> gout92 = ctx.eval_lut_amortized(&gin92, decomp);

    std::cerr << "\rFA93    ";
    Ciphertext gin93 = gout85[2] + 1 * gout80[0] + 2 * gout80[1] + 1 * gout63[0] + 2 * gout63[1];
    std::vector<Ciphertext> gout93 = ctx.eval_lut_amortized(&gin93, decomp);

    std::cerr << "\rFA94    ";
    Ciphertext gin94 = gout80[2] + 1 * gout65[2] + 1 * gout28[2];
    std::vector<Ciphertext> gout94 = ctx.eval_lut_amortized(&gin94, decomp);

    std::cerr << "\rFA95    ";
    Ciphertext gin95 = gout90[2] + 1 * gout84[2] + 1 * gout47[2];
    std::vector<Ciphertext> gout95 = ctx.eval_lut_amortized(&gin95, decomp);

    std::cerr << "\rFA96    ";
    Ciphertext gin96 = gout93[2] + 1 * gout94[0] + 2 * gout94[1] + 1 * gout69[0] + 2 * gout69[1];
    std::vector<Ciphertext> gout96 = ctx.eval_lut_amortized(&gin96, decomp);

    std::cerr << "\rFA97    ";
    Ciphertext gin97 = gout83[2] + 1 * gout90[0] + 2 * gout90[1] + 1 * gout79[0] + 2 * gout79[1];
    std::vector<Ciphertext> gout97 = ctx.eval_lut_amortized(&gin97, decomp);

    std::cerr << "\rFA98    ";
    Ciphertext gin98 = gout97[2] + 1 * gout95[0] + 2 * gout95[1] + 1 * gout89[0] + 2 * gout89[1];
    std::vector<Ciphertext> gout98 = ctx.eval_lut_amortized(&gin98, decomp);

    std::cerr << "\rFA99    ";
    Ciphertext gin99 = gout88[2] + 1 * gout97[0] + 2 * gout97[1] + 1 * gout87[0] + 2 * gout87[1];
    std::vector<Ciphertext> gout99 = ctx.eval_lut_amortized(&gin99, decomp);

    std::cerr << "\rFA100    ";
    Ciphertext gin100 = gout91[2] + 1 * gout99[0] + 2 * gout99[1] + 1 * gout93[0] + 2 * gout93[1];
    std::vector<Ciphertext> gout100 = ctx.eval_lut_amortized(&gin100, decomp);

    std::cerr << "\rFA101    ";
    Ciphertext gin101 = gout99[2] + 1 * gout98[0] + 2 * gout98[1] + 1 * gout92[0] + 2 * gout92[1];
    std::vector<Ciphertext> gout101 = ctx.eval_lut_amortized(&gin101, decomp);

    std::cerr << "\rFA102    ";
    Ciphertext gin102 = gout101[2] + 1 * gout98[2] + 1 * gout92[2];
    std::vector<Ciphertext> gout102 = ctx.eval_lut_amortized(&gin102, decomp);

    std::cerr << "\rFA103    ";
    Ciphertext gin103 = gout100[2] + 1 * gout101[0] + 2 * gout101[1] + 1 * gout96[0] + 2 * gout96[1];
    std::vector<Ciphertext> gout103 = ctx.eval_lut_amortized(&gin103, decomp);

    std::cerr << "\rFA104    ";
    Ciphertext gin104 = gout103[2] + 1 * gout102[0] + 2 * gout102[1] + 1 * gout96[2] + 2 * 0;
    std::vector<Ciphertext> gout104 = ctx.eval_lut_amortized(&gin104, decomp);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(ctx.decrypt(&gout76[0])); /* out192 */
    test_out.push_back(ctx.decrypt(&gout76[1])); /* out193 */
    test_out.push_back(ctx.decrypt(&gout86[0])); /* out194 */
    test_out.push_back(ctx.decrypt(&gout86[1])); /* out195 */
    test_out.push_back(ctx.decrypt(&gout91[0])); /* out196 */
    test_out.push_back(ctx.decrypt(&gout91[1])); /* out197 */
    test_out.push_back(ctx.decrypt(&gout100[0])); /* out198 */
    test_out.push_back(ctx.decrypt(&gout100[1])); /* out199 */
    test_out.push_back(ctx.decrypt(&gout103[0])); /* out200 */
    test_out.push_back(ctx.decrypt(&gout103[1])); /* out201 */
    test_out.push_back(ctx.decrypt(&gout104[0])); /* out202 */
    test_out.push_back(ctx.decrypt(&gout104[1])); /* out203 */
    test_out.push_back(ctx.decrypt(&gout104[2])); /* out204 */
    test_out.push_back(0); /* out223 */
    return test_out;
}

static void
BM_sum3d_lut3fa(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(rlwe_hom_acc_scheme_C_11_NTT);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(8);

    for (auto _ : state) {
        test_sum3d_lut3fa(ctx);
    }
}

BENCHMARK(BM_sum3d_lut3fa)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
