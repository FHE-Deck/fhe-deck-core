#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_sum3d_lut2fa(FHEContext& ctx, std::vector<uint64_t> out = { 0 })
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

    std::cerr << "\rFA0    ";
    Ciphertext gin0 = 0 + 1 * ct_out144 + 1 * ct_out48;
    std::vector<Ciphertext> gout0 = ctx.eval_lut_amortized(&gin0, decomp);

    std::cerr << "\rFA1    ";
    Ciphertext gin1 = 0 + 1 * ct_out176 + 1 * ct_out80;
    std::vector<Ciphertext> gout1 = ctx.eval_lut_amortized(&gin1, decomp);

    std::cerr << "\rFA2    ";
    Ciphertext gin2 = 0 + 1 * ct_out152 + 1 * ct_out56;
    std::vector<Ciphertext> gout2 = ctx.eval_lut_amortized(&gin2, decomp);

    std::cerr << "\rFA3    ";
    Ciphertext gin3 = 0 + 1 * gout0[0] + 1 * gout2[0];
    std::vector<Ciphertext> gout3 = ctx.eval_lut_amortized(&gin3, decomp);

    std::cerr << "\rFA4    ";
    Ciphertext gin4 = 0 + 1 * ct_out96 + 1 * ct_out0;
    std::vector<Ciphertext> gout4 = ctx.eval_lut_amortized(&gin4, decomp);

    std::cerr << "\rFA5    ";
    Ciphertext gin5 = 0 + 1 * ct_out136 + 1 * ct_out40;
    std::vector<Ciphertext> gout5 = ctx.eval_lut_amortized(&gin5, decomp);

    std::cerr << "\rFA6    ";
    Ciphertext gin6 = 0 + 1 * ct_out160 + 1 * ct_out64;
    std::vector<Ciphertext> gout6 = ctx.eval_lut_amortized(&gin6, decomp);

    std::cerr << "\rFA7    ";
    Ciphertext gin7 = gout2[1] + 1 * ct_out153 + 1 * ct_out57;
    std::vector<Ciphertext> gout7 = ctx.eval_lut_amortized(&gin7, decomp);

    std::cerr << "\rFA8    ";
    Ciphertext gin8 = gout5[1] + 1 * ct_out137 + 1 * ct_out41;
    std::vector<Ciphertext> gout8 = ctx.eval_lut_amortized(&gin8, decomp);

    std::cerr << "\rFA9    ";
    Ciphertext gin9 = 0 + 1 * ct_out184 + 1 * ct_out88;
    std::vector<Ciphertext> gout9 = ctx.eval_lut_amortized(&gin9, decomp);

    std::cerr << "\rFA10    ";
    Ciphertext gin10 = 0 + 1 * ct_out168 + 1 * ct_out72;
    std::vector<Ciphertext> gout10 = ctx.eval_lut_amortized(&gin10, decomp);

    std::cerr << "\rFA11    ";
    Ciphertext gin11 = 0 + 1 * gout6[0] + 1 * gout10[0];
    std::vector<Ciphertext> gout11 = ctx.eval_lut_amortized(&gin11, decomp);

    std::cerr << "\rFA12    ";
    Ciphertext gin12 = gout4[1] + 1 * ct_out97 + 1 * ct_out1;
    std::vector<Ciphertext> gout12 = ctx.eval_lut_amortized(&gin12, decomp);

    std::cerr << "\rFA13    ";
    Ciphertext gin13 = gout7[1] + 1 * ct_out154 + 1 * ct_out58;
    std::vector<Ciphertext> gout13 = ctx.eval_lut_amortized(&gin13, decomp);

    std::cerr << "\rFA14    ";
    Ciphertext gin14 = gout8[1] + 1 * ct_out138 + 1 * ct_out42;
    std::vector<Ciphertext> gout14 = ctx.eval_lut_amortized(&gin14, decomp);

    std::cerr << "\rFA15    ";
    Ciphertext gin15 = gout10[1] + 1 * ct_out169 + 1 * ct_out73;
    std::vector<Ciphertext> gout15 = ctx.eval_lut_amortized(&gin15, decomp);

    std::cerr << "\rFA16    ";
    Ciphertext gin16 = gout1[1] + 1 * ct_out177 + 1 * ct_out81;
    std::vector<Ciphertext> gout16 = ctx.eval_lut_amortized(&gin16, decomp);

    std::cerr << "\rFA17    ";
    Ciphertext gin17 = 0 + 1 * ct_out112 + 1 * ct_out16;
    std::vector<Ciphertext> gout17 = ctx.eval_lut_amortized(&gin17, decomp);

    std::cerr << "\rFA18    ";
    Ciphertext gin18 = gout6[1] + 1 * ct_out161 + 1 * ct_out65;
    std::vector<Ciphertext> gout18 = ctx.eval_lut_amortized(&gin18, decomp);

    std::cerr << "\rFA19    ";
    Ciphertext gin19 = 0 + 1 * ct_out128 + 1 * ct_out32;
    std::vector<Ciphertext> gout19 = ctx.eval_lut_amortized(&gin19, decomp);

    std::cerr << "\rFA20    ";
    Ciphertext gin20 = gout9[1] + 1 * ct_out185 + 1 * ct_out89;
    std::vector<Ciphertext> gout20 = ctx.eval_lut_amortized(&gin20, decomp);

    std::cerr << "\rFA21    ";
    Ciphertext gin21 = 0 + 1 * ct_out104 + 1 * ct_out8;
    std::vector<Ciphertext> gout21 = ctx.eval_lut_amortized(&gin21, decomp);

    std::cerr << "\rFA22    ";
    Ciphertext gin22 = 0 + 1 * ct_out120 + 1 * ct_out24;
    std::vector<Ciphertext> gout22 = ctx.eval_lut_amortized(&gin22, decomp);

    std::cerr << "\rFA23    ";
    Ciphertext gin23 = 0 + 1 * gout1[0] + 1 * gout9[0];
    std::vector<Ciphertext> gout23 = ctx.eval_lut_amortized(&gin23, decomp);

    std::cerr << "\rFA24    ";
    Ciphertext gin24 = gout11[1] + 1 * gout18[0] + 1 * gout15[0];
    std::vector<Ciphertext> gout24 = ctx.eval_lut_amortized(&gin24, decomp);

    std::cerr << "\rFA25    ";
    Ciphertext gin25 = gout14[1] + 1 * ct_out139 + 1 * ct_out43;
    std::vector<Ciphertext> gout25 = ctx.eval_lut_amortized(&gin25, decomp);

    std::cerr << "\rFA26    ";
    Ciphertext gin26 = gout13[1] + 1 * ct_out155 + 1 * ct_out59;
    std::vector<Ciphertext> gout26 = ctx.eval_lut_amortized(&gin26, decomp);

    std::cerr << "\rFA27    ";
    Ciphertext gin27 = gout16[1] + 1 * ct_out178 + 1 * ct_out82;
    std::vector<Ciphertext> gout27 = ctx.eval_lut_amortized(&gin27, decomp);

    std::cerr << "\rFA28    ";
    Ciphertext gin28 = gout19[1] + 1 * ct_out129 + 1 * ct_out33;
    std::vector<Ciphertext> gout28 = ctx.eval_lut_amortized(&gin28, decomp);

    std::cerr << "\rFA29    ";
    Ciphertext gin29 = gout17[1] + 1 * ct_out113 + 1 * ct_out17;
    std::vector<Ciphertext> gout29 = ctx.eval_lut_amortized(&gin29, decomp);

    std::cerr << "\rFA30    ";
    Ciphertext gin30 = gout15[1] + 1 * ct_out170 + 1 * ct_out74;
    std::vector<Ciphertext> gout30 = ctx.eval_lut_amortized(&gin30, decomp);

    std::cerr << "\rFA31    ";
    Ciphertext gin31 = gout21[1] + 1 * ct_out105 + 1 * ct_out9;
    std::vector<Ciphertext> gout31 = ctx.eval_lut_amortized(&gin31, decomp);

    std::cerr << "\rFA32    ";
    Ciphertext gin32 = gout0[1] + 1 * ct_out145 + 1 * ct_out49;
    std::vector<Ciphertext> gout32 = ctx.eval_lut_amortized(&gin32, decomp);

    std::cerr << "\rFA33    ";
    Ciphertext gin33 = gout28[1] + 1 * ct_out130 + 1 * ct_out34;
    std::vector<Ciphertext> gout33 = ctx.eval_lut_amortized(&gin33, decomp);

    std::cerr << "\rFA34    ";
    Ciphertext gin34 = gout27[1] + 1 * ct_out179 + 1 * ct_out83;
    std::vector<Ciphertext> gout34 = ctx.eval_lut_amortized(&gin34, decomp);

    std::cerr << "\rFA35    ";
    Ciphertext gin35 = 0 + 1 * gout4[0] + 1 * gout21[0];
    std::vector<Ciphertext> gout35 = ctx.eval_lut_amortized(&gin35, decomp);

    std::cerr << "\rFA36    ";
    Ciphertext gin36 = gout20[1] + 1 * ct_out186 + 1 * ct_out90;
    std::vector<Ciphertext> gout36 = ctx.eval_lut_amortized(&gin36, decomp);

    std::cerr << "\rFA37    ";
    Ciphertext gin37 = gout18[1] + 1 * ct_out162 + 1 * ct_out66;
    std::vector<Ciphertext> gout37 = ctx.eval_lut_amortized(&gin37, decomp);

    std::cerr << "\rFA38    ";
    Ciphertext gin38 = gout22[1] + 1 * ct_out121 + 1 * ct_out25;
    std::vector<Ciphertext> gout38 = ctx.eval_lut_amortized(&gin38, decomp);

    std::cerr << "\rFA39    ";
    Ciphertext gin39 = 0 + 1 * gout17[0] + 1 * gout22[0];
    std::vector<Ciphertext> gout39 = ctx.eval_lut_amortized(&gin39, decomp);

    std::cerr << "\rFA40    ";
    Ciphertext gin40 = gout34[1] + 1 * ct_out180 + 1 * ct_out84;
    std::vector<Ciphertext> gout40 = ctx.eval_lut_amortized(&gin40, decomp);

    std::cerr << "\rFA41    ";
    Ciphertext gin41 = gout23[1] + 1 * gout16[0] + 1 * gout20[0];
    std::vector<Ciphertext> gout41 = ctx.eval_lut_amortized(&gin41, decomp);

    std::cerr << "\rFA42    ";
    Ciphertext gin42 = gout26[1] + 1 * ct_out156 + 1 * ct_out60;
    std::vector<Ciphertext> gout42 = ctx.eval_lut_amortized(&gin42, decomp);

    std::cerr << "\rFA43    ";
    Ciphertext gin43 = gout3[1] + 1 * gout32[0] + 1 * gout7[0];
    std::vector<Ciphertext> gout43 = ctx.eval_lut_amortized(&gin43, decomp);

    std::cerr << "\rFA44    ";
    Ciphertext gin44 = 0 + 1 * gout11[0] + 1 * gout23[0];
    std::vector<Ciphertext> gout44 = ctx.eval_lut_amortized(&gin44, decomp);

    std::cerr << "\rFA45    ";
    Ciphertext gin45 = gout25[1] + 1 * ct_out140 + 1 * ct_out44;
    std::vector<Ciphertext> gout45 = ctx.eval_lut_amortized(&gin45, decomp);

    std::cerr << "\rFA46    ";
    Ciphertext gin46 = gout31[1] + 1 * ct_out106 + 1 * ct_out10;
    std::vector<Ciphertext> gout46 = ctx.eval_lut_amortized(&gin46, decomp);

    std::cerr << "\rFA47    ";
    Ciphertext gin47 = gout30[1] + 1 * ct_out171 + 1 * ct_out75;
    std::vector<Ciphertext> gout47 = ctx.eval_lut_amortized(&gin47, decomp);

    std::cerr << "\rFA48    ";
    Ciphertext gin48 = gout12[1] + 1 * ct_out98 + 1 * ct_out2;
    std::vector<Ciphertext> gout48 = ctx.eval_lut_amortized(&gin48, decomp);

    std::cerr << "\rFA49    ";
    Ciphertext gin49 = gout29[1] + 1 * ct_out114 + 1 * ct_out18;
    std::vector<Ciphertext> gout49 = ctx.eval_lut_amortized(&gin49, decomp);

    std::cerr << "\rFA50    ";
    Ciphertext gin50 = 0 + 1 * gout19[0] + 1 * gout5[0];
    std::vector<Ciphertext> gout50 = ctx.eval_lut_amortized(&gin50, decomp);

    std::cerr << "\rFA51    ";
    Ciphertext gin51 = gout32[1] + 1 * ct_out146 + 1 * ct_out50;
    std::vector<Ciphertext> gout51 = ctx.eval_lut_amortized(&gin51, decomp);

    std::cerr << "\rFA52    ";
    Ciphertext gin52 = 0 + 1 * gout50[0] + 1 * gout3[0];
    std::vector<Ciphertext> gout52 = ctx.eval_lut_amortized(&gin52, decomp);

    std::cerr << "\rFA53    ";
    Ciphertext gin53 = gout33[1] + 1 * ct_out131 + 1 * ct_out35;
    std::vector<Ciphertext> gout53 = ctx.eval_lut_amortized(&gin53, decomp);

    std::cerr << "\rFA54    ";
    Ciphertext gin54 = 0 + 1 * gout35[0] + 1 * gout39[0];
    std::vector<Ciphertext> gout54 = ctx.eval_lut_amortized(&gin54, decomp);

    std::cerr << "\rFA55    ";
    Ciphertext gin55 = gout24[1] + 1 * gout37[0] + 1 * gout30[0];
    std::vector<Ciphertext> gout55 = ctx.eval_lut_amortized(&gin55, decomp);

    std::cerr << "\rFA56    ";
    Ciphertext gin56 = gout35[1] + 1 * gout12[0] + 1 * gout31[0];
    std::vector<Ciphertext> gout56 = ctx.eval_lut_amortized(&gin56, decomp);

    std::cerr << "\rFA57    ";
    Ciphertext gin57 = 0 + 1 * gout54[0] + 1 * gout52[0];
    std::vector<Ciphertext> gout57 = ctx.eval_lut_amortized(&gin57, decomp);

    std::cerr << "\rFA58    ";
    Ciphertext gin58 = gout36[1] + 1 * ct_out187 + 1 * ct_out91;
    std::vector<Ciphertext> gout58 = ctx.eval_lut_amortized(&gin58, decomp);

    std::cerr << "\rFA59    ";
    Ciphertext gin59 = gout37[1] + 1 * ct_out163 + 1 * ct_out67;
    std::vector<Ciphertext> gout59 = ctx.eval_lut_amortized(&gin59, decomp);

    std::cerr << "\rFA60    ";
    Ciphertext gin60 = gout38[1] + 1 * ct_out122 + 1 * ct_out26;
    std::vector<Ciphertext> gout60 = ctx.eval_lut_amortized(&gin60, decomp);

    std::cerr << "\rFA61    ";
    Ciphertext gin61 = gout58[1] + 1 * ct_out188 + 1 * ct_out92;
    std::vector<Ciphertext> gout61 = ctx.eval_lut_amortized(&gin61, decomp);

    std::cerr << "\rFA62    ";
    Ciphertext gin62 = gout41[1] + 1 * gout27[0] + 1 * gout36[0];
    std::vector<Ciphertext> gout62 = ctx.eval_lut_amortized(&gin62, decomp);

    std::cerr << "\rFA63    ";
    Ciphertext gin63 = gout39[1] + 1 * gout29[0] + 1 * gout38[0];
    std::vector<Ciphertext> gout63 = ctx.eval_lut_amortized(&gin63, decomp);

    std::cerr << "\rFA64    ";
    Ciphertext gin64 = gout42[1] + 1 * ct_out157 + 1 * ct_out61;
    std::vector<Ciphertext> gout64 = ctx.eval_lut_amortized(&gin64, decomp);

    std::cerr << "\rFA65    ";
    Ciphertext gin65 = gout44[1] + 1 * gout24[0] + 1 * gout41[0];
    std::vector<Ciphertext> gout65 = ctx.eval_lut_amortized(&gin65, decomp);

    std::cerr << "\rFA66    ";
    Ciphertext gin66 = gout43[1] + 1 * gout51[0] + 1 * gout13[0];
    std::vector<Ciphertext> gout66 = ctx.eval_lut_amortized(&gin66, decomp);

    std::cerr << "\rFA67    ";
    Ciphertext gin67 = gout45[1] + 1 * ct_out141 + 1 * ct_out45;
    std::vector<Ciphertext> gout67 = ctx.eval_lut_amortized(&gin67, decomp);

    std::cerr << "\rFA68    ";
    Ciphertext gin68 = gout47[1] + 1 * ct_out172 + 1 * ct_out76;
    std::vector<Ciphertext> gout68 = ctx.eval_lut_amortized(&gin68, decomp);

    std::cerr << "\rFA69    ";
    Ciphertext gin69 = gout46[1] + 1 * ct_out107 + 1 * ct_out11;
    std::vector<Ciphertext> gout69 = ctx.eval_lut_amortized(&gin69, decomp);

    std::cerr << "\rFA70    ";
    Ciphertext gin70 = gout49[1] + 1 * ct_out115 + 1 * ct_out19;
    std::vector<Ciphertext> gout70 = ctx.eval_lut_amortized(&gin70, decomp);

    std::cerr << "\rFA71    ";
    Ciphertext gin71 = gout51[1] + 1 * ct_out147 + 1 * ct_out51;
    std::vector<Ciphertext> gout71 = ctx.eval_lut_amortized(&gin71, decomp);

    std::cerr << "\rFA72    ";
    Ciphertext gin72 = gout50[1] + 1 * gout28[0] + 1 * gout8[0];
    std::vector<Ciphertext> gout72 = ctx.eval_lut_amortized(&gin72, decomp);

    std::cerr << "\rFA73    ";
    Ciphertext gin73 = gout52[1] + 1 * gout72[0] + 1 * gout43[0];
    std::vector<Ciphertext> gout73 = ctx.eval_lut_amortized(&gin73, decomp);

    std::cerr << "\rFA74    ";
    Ciphertext gin74 = 0 + 1 * gout57[0] + 1 * gout44[0];
    std::vector<Ciphertext> gout74 = ctx.eval_lut_amortized(&gin74, decomp);

    std::cerr << "\rFA75    ";
    Ciphertext gin75 = gout40[1] + 1 * ct_out181 + 1 * ct_out85;
    std::vector<Ciphertext> gout75 = ctx.eval_lut_amortized(&gin75, decomp);

    std::cerr << "\rFA76    ";
    Ciphertext gin76 = gout53[1] + 1 * ct_out132 + 1 * ct_out36;
    std::vector<Ciphertext> gout76 = ctx.eval_lut_amortized(&gin76, decomp);

    std::cerr << "\rFA77    ";
    Ciphertext gin77 = gout54[1] + 1 * gout56[0] + 1 * gout63[0];
    std::vector<Ciphertext> gout77 = ctx.eval_lut_amortized(&gin77, decomp);

    std::cerr << "\rFA78    ";
    Ciphertext gin78 = gout48[1] + 1 * ct_out99 + 1 * ct_out3;
    std::vector<Ciphertext> gout78 = ctx.eval_lut_amortized(&gin78, decomp);

    std::cerr << "\rFA79    ";
    Ciphertext gin79 = gout55[1] + 1 * gout59[0] + 1 * gout47[0];
    std::vector<Ciphertext> gout79 = ctx.eval_lut_amortized(&gin79, decomp);

    std::cerr << "\rFA80    ";
    Ciphertext gin80 = gout56[1] + 1 * gout48[0] + 1 * gout46[0];
    std::vector<Ciphertext> gout80 = ctx.eval_lut_amortized(&gin80, decomp);

    std::cerr << "\rFA81    ";
    Ciphertext gin81 = gout59[1] + 1 * ct_out164 + 1 * ct_out68;
    std::vector<Ciphertext> gout81 = ctx.eval_lut_amortized(&gin81, decomp);

    std::cerr << "\rFA82    ";
    Ciphertext gin82 = gout61[1] + 1 * ct_out189 + 1 * ct_out93;
    std::vector<Ciphertext> gout82 = ctx.eval_lut_amortized(&gin82, decomp);

    std::cerr << "\rFA83    ";
    Ciphertext gin83 = gout60[1] + 1 * ct_out123 + 1 * ct_out27;
    std::vector<Ciphertext> gout83 = ctx.eval_lut_amortized(&gin83, decomp);

    std::cerr << "\rFA84    ";
    Ciphertext gin84 = gout62[1] + 1 * gout34[0] + 1 * gout58[0];
    std::vector<Ciphertext> gout84 = ctx.eval_lut_amortized(&gin84, decomp);

    std::cerr << "\rFA85    ";
    Ciphertext gin85 = gout63[1] + 1 * gout49[0] + 1 * gout60[0];
    std::vector<Ciphertext> gout85 = ctx.eval_lut_amortized(&gin85, decomp);

    std::cerr << "\rFA86    ";
    Ciphertext gin86 = gout66[1] + 1 * gout71[0] + 1 * gout26[0];
    std::vector<Ciphertext> gout86 = ctx.eval_lut_amortized(&gin86, decomp);

    std::cerr << "\rFA87    ";
    Ciphertext gin87 = gout67[1] + 1 * ct_out142 + 1 * ct_out46;
    std::vector<Ciphertext> gout87 = ctx.eval_lut_amortized(&gin87, decomp);

    std::cerr << "\rFA88    ";
    Ciphertext gin88 = gout64[1] + 1 * ct_out158 + 1 * ct_out62;
    std::vector<Ciphertext> gout88 = ctx.eval_lut_amortized(&gin88, decomp);

    std::cerr << "\rFA89    ";
    Ciphertext gin89 = gout65[1] + 1 * gout55[0] + 1 * gout62[0];
    std::vector<Ciphertext> gout89 = ctx.eval_lut_amortized(&gin89, decomp);

    std::cerr << "\rFA90    ";
    Ciphertext gin90 = gout69[1] + 1 * ct_out108 + 1 * ct_out12;
    std::vector<Ciphertext> gout90 = ctx.eval_lut_amortized(&gin90, decomp);

    std::cerr << "\rFA91    ";
    Ciphertext gin91 = gout68[1] + 1 * ct_out173 + 1 * ct_out77;
    std::vector<Ciphertext> gout91 = ctx.eval_lut_amortized(&gin91, decomp);

    std::cerr << "\rFA92    ";
    Ciphertext gin92 = gout70[1] + 1 * ct_out116 + 1 * ct_out20;
    std::vector<Ciphertext> gout92 = ctx.eval_lut_amortized(&gin92, decomp);

    std::cerr << "\rFA93    ";
    Ciphertext gin93 = gout78[1] + 1 * ct_out100 + 1 * ct_out4;
    std::vector<Ciphertext> gout93 = ctx.eval_lut_amortized(&gin93, decomp);

    std::cerr << "\rFA94    ";
    Ciphertext gin94 = gout71[1] + 1 * ct_out148 + 1 * ct_out52;
    std::vector<Ciphertext> gout94 = ctx.eval_lut_amortized(&gin94, decomp);

    std::cerr << "\rFA95    ";
    Ciphertext gin95 = gout72[1] + 1 * gout33[0] + 1 * gout14[0];
    std::vector<Ciphertext> gout95 = ctx.eval_lut_amortized(&gin95, decomp);

    std::cerr << "\rFA96    ";
    Ciphertext gin96 = gout73[1] + 1 * gout95[0] + 1 * gout66[0];
    std::vector<Ciphertext> gout96 = ctx.eval_lut_amortized(&gin96, decomp);

    std::cerr << "\rFA97    ";
    Ciphertext gin97 = gout76[1] + 1 * ct_out133 + 1 * ct_out37;
    std::vector<Ciphertext> gout97 = ctx.eval_lut_amortized(&gin97, decomp);

    std::cerr << "\rFA98    ";
    Ciphertext gin98 = gout75[1] + 1 * ct_out182 + 1 * ct_out86;
    std::vector<Ciphertext> gout98 = ctx.eval_lut_amortized(&gin98, decomp);

    std::cerr << "\rFA99    ";
    Ciphertext gin99 = gout77[1] + 1 * gout80[0] + 1 * gout85[0];
    std::vector<Ciphertext> gout99 = ctx.eval_lut_amortized(&gin99, decomp);

    std::cerr << "\rFA100    ";
    Ciphertext gin100 = gout80[1] + 1 * gout78[0] + 1 * gout69[0];
    std::vector<Ciphertext> gout100 = ctx.eval_lut_amortized(&gin100, decomp);

    std::cerr << "\rFA101    ";
    Ciphertext gin101 = gout57[1] + 1 * gout77[0] + 1 * gout73[0];
    std::vector<Ciphertext> gout101 = ctx.eval_lut_amortized(&gin101, decomp);

    std::cerr << "\rFA102    ";
    Ciphertext gin102 = gout79[1] + 1 * gout81[0] + 1 * gout68[0];
    std::vector<Ciphertext> gout102 = ctx.eval_lut_amortized(&gin102, decomp);

    std::cerr << "\rFA103    ";
    Ciphertext gin103 = gout74[1] + 1 * gout101[0] + 1 * gout65[0];
    std::vector<Ciphertext> gout103 = ctx.eval_lut_amortized(&gin103, decomp);

    std::cerr << "\rFA104    ";
    Ciphertext gin104 = gout81[1] + 1 * ct_out165 + 1 * ct_out69;
    std::vector<Ciphertext> gout104 = ctx.eval_lut_amortized(&gin104, decomp);

    std::cerr << "\rFA105    ";
    Ciphertext gin105 = gout82[1] + 1 * ct_out190 + 1 * ct_out94;
    std::vector<Ciphertext> gout105 = ctx.eval_lut_amortized(&gin105, decomp);

    std::cerr << "\rFA106    ";
    Ciphertext gin106 = gout83[1] + 1 * ct_out124 + 1 * ct_out28;
    std::vector<Ciphertext> gout106 = ctx.eval_lut_amortized(&gin106, decomp);

    std::cerr << "\rFA107    ";
    Ciphertext gin107 = gout85[1] + 1 * gout70[0] + 1 * gout83[0];
    std::vector<Ciphertext> gout107 = ctx.eval_lut_amortized(&gin107, decomp);

    std::cerr << "\rFA108    ";
    Ciphertext gin108 = gout84[1] + 1 * gout40[0] + 1 * gout61[0];
    std::vector<Ciphertext> gout108 = ctx.eval_lut_amortized(&gin108, decomp);

    std::cerr << "\rFA109    ";
    Ciphertext gin109 = gout88[1] + 1 * ct_out159 + 1 * ct_out63;
    std::vector<Ciphertext> gout109 = ctx.eval_lut_amortized(&gin109, decomp);

    std::cerr << "\rFA110    ";
    Ciphertext gin110 = gout86[1] + 1 * gout94[0] + 1 * gout42[0];
    std::vector<Ciphertext> gout110 = ctx.eval_lut_amortized(&gin110, decomp);

    std::cerr << "\rFA111    ";
    Ciphertext gin111 = gout89[1] + 1 * gout79[0] + 1 * gout84[0];
    std::vector<Ciphertext> gout111 = ctx.eval_lut_amortized(&gin111, decomp);

    std::cerr << "\rFA112    ";
    Ciphertext gin112 = gout87[1] + 1 * ct_out143 + 1 * ct_out47;
    std::vector<Ciphertext> gout112 = ctx.eval_lut_amortized(&gin112, decomp);

    std::cerr << "\rFA113    ";
    Ciphertext gin113 = gout90[1] + 1 * ct_out109 + 1 * ct_out13;
    std::vector<Ciphertext> gout113 = ctx.eval_lut_amortized(&gin113, decomp);

    std::cerr << "\rFA114    ";
    Ciphertext gin114 = gout91[1] + 1 * ct_out174 + 1 * ct_out78;
    std::vector<Ciphertext> gout114 = ctx.eval_lut_amortized(&gin114, decomp);

    std::cerr << "\rFA115    ";
    Ciphertext gin115 = gout93[1] + 1 * ct_out101 + 1 * ct_out5;
    std::vector<Ciphertext> gout115 = ctx.eval_lut_amortized(&gin115, decomp);

    std::cerr << "\rFA116    ";
    Ciphertext gin116 = gout95[1] + 1 * gout53[0] + 1 * gout25[0];
    std::vector<Ciphertext> gout116 = ctx.eval_lut_amortized(&gin116, decomp);

    std::cerr << "\rFA117    ";
    Ciphertext gin117 = gout92[1] + 1 * ct_out117 + 1 * ct_out21;
    std::vector<Ciphertext> gout117 = ctx.eval_lut_amortized(&gin117, decomp);

    std::cerr << "\rFA118    ";
    Ciphertext gin118 = gout115[1] + 1 * ct_out102 + 1 * ct_out6;
    std::vector<Ciphertext> gout118 = ctx.eval_lut_amortized(&gin118, decomp);

    std::cerr << "\rFA119    ";
    Ciphertext gin119 = gout94[1] + 1 * ct_out149 + 1 * ct_out53;
    std::vector<Ciphertext> gout119 = ctx.eval_lut_amortized(&gin119, decomp);

    std::cerr << "\rFA120    ";
    Ciphertext gin120 = gout96[1] + 1 * gout116[0] + 1 * gout86[0];
    std::vector<Ciphertext> gout120 = ctx.eval_lut_amortized(&gin120, decomp);

    std::cerr << "\rFA121    ";
    Ciphertext gin121 = gout97[1] + 1 * ct_out134 + 1 * ct_out38;
    std::vector<Ciphertext> gout121 = ctx.eval_lut_amortized(&gin121, decomp);

    std::cerr << "\rFA122    ";
    Ciphertext gin122 = gout98[1] + 1 * ct_out183 + 1 * ct_out87;
    std::vector<Ciphertext> gout122 = ctx.eval_lut_amortized(&gin122, decomp);

    std::cerr << "\rFA123    ";
    Ciphertext gin123 = gout99[1] + 1 * gout100[0] + 1 * gout107[0];
    std::vector<Ciphertext> gout123 = ctx.eval_lut_amortized(&gin123, decomp);

    std::cerr << "\rFA124    ";
    Ciphertext gin124 = gout101[1] + 1 * gout99[0] + 1 * gout96[0];
    std::vector<Ciphertext> gout124 = ctx.eval_lut_amortized(&gin124, decomp);

    std::cerr << "\rFA125    ";
    Ciphertext gin125 = gout102[1] + 1 * gout104[0] + 1 * gout91[0];
    std::vector<Ciphertext> gout125 = ctx.eval_lut_amortized(&gin125, decomp);

    std::cerr << "\rFA126    ";
    Ciphertext gin126 = gout100[1] + 1 * gout93[0] + 1 * gout90[0];
    std::vector<Ciphertext> gout126 = ctx.eval_lut_amortized(&gin126, decomp);

    std::cerr << "\rFA127    ";
    Ciphertext gin127 = gout104[1] + 1 * ct_out166 + 1 * ct_out70;
    std::vector<Ciphertext> gout127 = ctx.eval_lut_amortized(&gin127, decomp);

    std::cerr << "\rFA128    ";
    Ciphertext gin128 = gout105[1] + 1 * ct_out191 + 1 * ct_out95;
    std::vector<Ciphertext> gout128 = ctx.eval_lut_amortized(&gin128, decomp);

    std::cerr << "\rFA129    ";
    Ciphertext gin129 = gout106[1] + 1 * ct_out125 + 1 * ct_out29;
    std::vector<Ciphertext> gout129 = ctx.eval_lut_amortized(&gin129, decomp);

    std::cerr << "\rFA130    ";
    Ciphertext gin130 = gout103[1] + 1 * gout124[0] + 1 * gout89[0];
    std::vector<Ciphertext> gout130 = ctx.eval_lut_amortized(&gin130, decomp);

    std::cerr << "\rFA131    ";
    Ciphertext gin131 = gout108[1] + 1 * gout75[0] + 1 * gout82[0];
    std::vector<Ciphertext> gout131 = ctx.eval_lut_amortized(&gin131, decomp);

    std::cerr << "\rFA132    ";
    Ciphertext gin132 = gout107[1] + 1 * gout92[0] + 1 * gout106[0];
    std::vector<Ciphertext> gout132 = ctx.eval_lut_amortized(&gin132, decomp);

    std::cerr << "\rFA133    ";
    Ciphertext gin133 = gout111[1] + 1 * gout102[0] + 1 * gout108[0];
    std::vector<Ciphertext> gout133 = ctx.eval_lut_amortized(&gin133, decomp);

    std::cerr << "\rFA134    ";
    Ciphertext gin134 = gout110[1] + 1 * gout119[0] + 1 * gout64[0];
    std::vector<Ciphertext> gout134 = ctx.eval_lut_amortized(&gin134, decomp);

    std::cerr << "\rFA135    ";
    Ciphertext gin135 = gout114[1] + 1 * ct_out175 + 1 * ct_out79;
    std::vector<Ciphertext> gout135 = ctx.eval_lut_amortized(&gin135, decomp);

    std::cerr << "\rFA136    ";
    Ciphertext gin136 = gout113[1] + 1 * ct_out110 + 1 * ct_out14;
    std::vector<Ciphertext> gout136 = ctx.eval_lut_amortized(&gin136, decomp);

    std::cerr << "\rFA137    ";
    Ciphertext gin137 = gout117[1] + 1 * ct_out118 + 1 * ct_out22;
    std::vector<Ciphertext> gout137 = ctx.eval_lut_amortized(&gin137, decomp);

    std::cerr << "\rFA138    ";
    Ciphertext gin138 = gout119[1] + 1 * ct_out150 + 1 * ct_out54;
    std::vector<Ciphertext> gout138 = ctx.eval_lut_amortized(&gin138, decomp);

    std::cerr << "\rFA139    ";
    Ciphertext gin139 = gout116[1] + 1 * gout76[0] + 1 * gout45[0];
    std::vector<Ciphertext> gout139 = ctx.eval_lut_amortized(&gin139, decomp);

    std::cerr << "\rFA140    ";
    Ciphertext gin140 = gout120[1] + 1 * gout139[0] + 1 * gout110[0];
    std::vector<Ciphertext> gout140 = ctx.eval_lut_amortized(&gin140, decomp);

    std::cerr << "\rFA141    ";
    Ciphertext gin141 = gout121[1] + 1 * ct_out135 + 1 * ct_out39;
    std::vector<Ciphertext> gout141 = ctx.eval_lut_amortized(&gin141, decomp);

    std::cerr << "\rFA142    ";
    Ciphertext gin142 = gout118[1] + 1 * ct_out103 + 1 * ct_out7;
    std::vector<Ciphertext> gout142 = ctx.eval_lut_amortized(&gin142, decomp);

    std::cerr << "\rFA143    ";
    Ciphertext gin143 = gout123[1] + 1 * gout126[0] + 1 * gout132[0];
    std::vector<Ciphertext> gout143 = ctx.eval_lut_amortized(&gin143, decomp);

    std::cerr << "\rFA144    ";
    Ciphertext gin144 = gout125[1] + 1 * gout127[0] + 1 * gout114[0];
    std::vector<Ciphertext> gout144 = ctx.eval_lut_amortized(&gin144, decomp);

    std::cerr << "\rFA145    ";
    Ciphertext gin145 = gout126[1] + 1 * gout115[0] + 1 * gout113[0];
    std::vector<Ciphertext> gout145 = ctx.eval_lut_amortized(&gin145, decomp);

    std::cerr << "\rFA146    ";
    Ciphertext gin146 = gout124[1] + 1 * gout123[0] + 1 * gout120[0];
    std::vector<Ciphertext> gout146 = ctx.eval_lut_amortized(&gin146, decomp);

    std::cerr << "\rFA147    ";
    Ciphertext gin147 = gout130[1] + 1 * gout146[0] + 1 * gout111[0];
    std::vector<Ciphertext> gout147 = ctx.eval_lut_amortized(&gin147, decomp);

    std::cerr << "\rFA148    ";
    Ciphertext gin148 = gout127[1] + 1 * ct_out167 + 1 * ct_out71;
    std::vector<Ciphertext> gout148 = ctx.eval_lut_amortized(&gin148, decomp);

    std::cerr << "\rFA149    ";
    Ciphertext gin149 = gout129[1] + 1 * ct_out126 + 1 * ct_out30;
    std::vector<Ciphertext> gout149 = ctx.eval_lut_amortized(&gin149, decomp);

    std::cerr << "\rFA150    ";
    Ciphertext gin150 = gout131[1] + 1 * gout98[0] + 1 * gout105[0];
    std::vector<Ciphertext> gout150 = ctx.eval_lut_amortized(&gin150, decomp);

    std::cerr << "\rFA151    ";
    Ciphertext gin151 = gout132[1] + 1 * gout117[0] + 1 * gout129[0];
    std::vector<Ciphertext> gout151 = ctx.eval_lut_amortized(&gin151, decomp);

    std::cerr << "\rFA152    ";
    Ciphertext gin152 = gout134[1] + 1 * gout138[0] + 1 * gout88[0];
    std::vector<Ciphertext> gout152 = ctx.eval_lut_amortized(&gin152, decomp);

    std::cerr << "\rFA153    ";
    Ciphertext gin153 = gout133[1] + 1 * gout125[0] + 1 * gout131[0];
    std::vector<Ciphertext> gout153 = ctx.eval_lut_amortized(&gin153, decomp);

    std::cerr << "\rFA154    ";
    Ciphertext gin154 = gout136[1] + 1 * ct_out111 + 1 * ct_out15;
    std::vector<Ciphertext> gout154 = ctx.eval_lut_amortized(&gin154, decomp);

    std::cerr << "\rFA155    ";
    Ciphertext gin155 = gout137[1] + 1 * ct_out119 + 1 * ct_out23;
    std::vector<Ciphertext> gout155 = ctx.eval_lut_amortized(&gin155, decomp);

    std::cerr << "\rFA156    ";
    Ciphertext gin156 = gout138[1] + 1 * ct_out151 + 1 * ct_out55;
    std::vector<Ciphertext> gout156 = ctx.eval_lut_amortized(&gin156, decomp);

    std::cerr << "\rFA157    ";
    Ciphertext gin157 = gout139[1] + 1 * gout97[0] + 1 * gout67[0];
    std::vector<Ciphertext> gout157 = ctx.eval_lut_amortized(&gin157, decomp);

    std::cerr << "\rFA158    ";
    Ciphertext gin158 = gout140[1] + 1 * gout157[0] + 1 * gout134[0];
    std::vector<Ciphertext> gout158 = ctx.eval_lut_amortized(&gin158, decomp);

    std::cerr << "\rFA159    ";
    Ciphertext gin159 = gout143[1] + 1 * gout145[0] + 1 * gout151[0];
    std::vector<Ciphertext> gout159 = ctx.eval_lut_amortized(&gin159, decomp);

    std::cerr << "\rFA160    ";
    Ciphertext gin160 = gout145[1] + 1 * gout118[0] + 1 * gout136[0];
    std::vector<Ciphertext> gout160 = ctx.eval_lut_amortized(&gin160, decomp);

    std::cerr << "\rFA161    ";
    Ciphertext gin161 = gout146[1] + 1 * gout143[0] + 1 * gout140[0];
    std::vector<Ciphertext> gout161 = ctx.eval_lut_amortized(&gin161, decomp);

    std::cerr << "\rFA162    ";
    Ciphertext gin162 = gout144[1] + 1 * gout148[0] + 1 * gout135[0];
    std::vector<Ciphertext> gout162 = ctx.eval_lut_amortized(&gin162, decomp);

    std::cerr << "\rFA163    ";
    Ciphertext gin163 = gout147[1] + 1 * gout161[0] + 1 * gout133[0];
    std::vector<Ciphertext> gout163 = ctx.eval_lut_amortized(&gin163, decomp);

    std::cerr << "\rFA164    ";
    Ciphertext gin164 = gout149[1] + 1 * ct_out127 + 1 * ct_out31;
    std::vector<Ciphertext> gout164 = ctx.eval_lut_amortized(&gin164, decomp);

    std::cerr << "\rFA165    ";
    Ciphertext gin165 = gout151[1] + 1 * gout137[0] + 1 * gout149[0];
    std::vector<Ciphertext> gout165 = ctx.eval_lut_amortized(&gin165, decomp);

    std::cerr << "\rFA166    ";
    Ciphertext gin166 = gout150[1] + 1 * gout122[0] + 1 * gout128[0];
    std::vector<Ciphertext> gout166 = ctx.eval_lut_amortized(&gin166, decomp);

    std::cerr << "\rFA167    ";
    Ciphertext gin167 = gout153[1] + 1 * gout144[0] + 1 * gout150[0];
    std::vector<Ciphertext> gout167 = ctx.eval_lut_amortized(&gin167, decomp);

    std::cerr << "\rFA168    ";
    Ciphertext gin168 = gout152[1] + 1 * gout156[0] + 1 * gout109[0];
    std::vector<Ciphertext> gout168 = ctx.eval_lut_amortized(&gin168, decomp);

    std::cerr << "\rFA169    ";
    Ciphertext gin169 = gout157[1] + 1 * gout121[0] + 1 * gout87[0];
    std::vector<Ciphertext> gout169 = ctx.eval_lut_amortized(&gin169, decomp);

    std::cerr << "\rFA170    ";
    Ciphertext gin170 = gout158[1] + 1 * gout169[0] + 1 * gout152[0];
    std::vector<Ciphertext> gout170 = ctx.eval_lut_amortized(&gin170, decomp);

    std::cerr << "\rFA171    ";
    Ciphertext gin171 = gout159[1] + 1 * gout160[0] + 1 * gout165[0];
    std::vector<Ciphertext> gout171 = ctx.eval_lut_amortized(&gin171, decomp);

    std::cerr << "\rFA172    ";
    Ciphertext gin172 = gout161[1] + 1 * gout159[0] + 1 * gout158[0];
    std::vector<Ciphertext> gout172 = ctx.eval_lut_amortized(&gin172, decomp);

    std::cerr << "\rFA173    ";
    Ciphertext gin173 = gout162[1] + 1 * gout148[1] + 1 * gout135[1];
    std::vector<Ciphertext> gout173 = ctx.eval_lut_amortized(&gin173, decomp);

    std::cerr << "\rFA174    ";
    Ciphertext gin174 = gout160[1] + 1 * gout142[0] + 1 * gout154[0];
    std::vector<Ciphertext> gout174 = ctx.eval_lut_amortized(&gin174, decomp);

    std::cerr << "\rFA175    ";
    Ciphertext gin175 = gout163[1] + 1 * gout172[0] + 1 * gout153[0];
    std::vector<Ciphertext> gout175 = ctx.eval_lut_amortized(&gin175, decomp);

    std::cerr << "\rFA176    ";
    Ciphertext gin176 = gout166[1] + 1 * gout122[1] + 1 * gout128[1];
    std::vector<Ciphertext> gout176 = ctx.eval_lut_amortized(&gin176, decomp);

    std::cerr << "\rFA177    ";
    Ciphertext gin177 = gout165[1] + 1 * gout155[0] + 1 * gout164[0];
    std::vector<Ciphertext> gout177 = ctx.eval_lut_amortized(&gin177, decomp);

    std::cerr << "\rFA178    ";
    Ciphertext gin178 = gout167[1] + 1 * gout162[0] + 1 * gout166[0];
    std::vector<Ciphertext> gout178 = ctx.eval_lut_amortized(&gin178, decomp);

    std::cerr << "\rFA179    ";
    Ciphertext gin179 = gout168[1] + 1 * gout156[1] + 1 * gout109[1];
    std::vector<Ciphertext> gout179 = ctx.eval_lut_amortized(&gin179, decomp);

    std::cerr << "\rFA180    ";
    Ciphertext gin180 = gout169[1] + 1 * gout141[0] + 1 * gout112[0];
    std::vector<Ciphertext> gout180 = ctx.eval_lut_amortized(&gin180, decomp);

    std::cerr << "\rFA181    ";
    Ciphertext gin181 = gout170[1] + 1 * gout180[0] + 1 * gout168[0];
    std::vector<Ciphertext> gout181 = ctx.eval_lut_amortized(&gin181, decomp);

    std::cerr << "\rFA182    ";
    Ciphertext gin182 = gout171[1] + 1 * gout174[0] + 1 * gout177[0];
    std::vector<Ciphertext> gout182 = ctx.eval_lut_amortized(&gin182, decomp);

    std::cerr << "\rFA183    ";
    Ciphertext gin183 = gout174[1] + 1 * gout142[1] + 1 * gout154[1];
    std::vector<Ciphertext> gout183 = ctx.eval_lut_amortized(&gin183, decomp);

    std::cerr << "\rFA184    ";
    Ciphertext gin184 = gout172[1] + 1 * gout171[0] + 1 * gout170[0];
    std::vector<Ciphertext> gout184 = ctx.eval_lut_amortized(&gin184, decomp);

    std::cerr << "\rFA185    ";
    Ciphertext gin185 = gout178[1] + 1 * gout173[0] + 1 * gout176[0];
    std::vector<Ciphertext> gout185 = ctx.eval_lut_amortized(&gin185, decomp);

    std::cerr << "\rFA186    ";
    Ciphertext gin186 = gout175[1] + 1 * gout184[0] + 1 * gout167[0];
    std::vector<Ciphertext> gout186 = ctx.eval_lut_amortized(&gin186, decomp);

    std::cerr << "\rFA187    ";
    Ciphertext gin187 = gout180[1] + 1 * gout141[1] + 1 * gout112[1];
    std::vector<Ciphertext> gout187 = ctx.eval_lut_amortized(&gin187, decomp);

    std::cerr << "\rFA188    ";
    Ciphertext gin188 = gout177[1] + 1 * gout155[1] + 1 * gout164[1];
    std::vector<Ciphertext> gout188 = ctx.eval_lut_amortized(&gin188, decomp);

    std::cerr << "\rFA189    ";
    Ciphertext gin189 = gout184[1] + 1 * gout182[0] + 1 * gout181[0];
    std::vector<Ciphertext> gout189 = ctx.eval_lut_amortized(&gin189, decomp);

    std::cerr << "\rFA190    ";
    Ciphertext gin190 = gout185[1] + 1 * gout173[1] + 1 * gout176[1];
    std::vector<Ciphertext> gout190 = ctx.eval_lut_amortized(&gin190, decomp);

    std::cerr << "\rFA191    ";
    Ciphertext gin191 = gout181[1] + 1 * gout187[0] + 1 * gout179[0];
    std::vector<Ciphertext> gout191 = ctx.eval_lut_amortized(&gin191, decomp);

    std::cerr << "\rFA192    ";
    Ciphertext gin192 = gout186[1] + 1 * gout189[0] + 1 * gout178[0];
    std::vector<Ciphertext> gout192 = ctx.eval_lut_amortized(&gin192, decomp);

    std::cerr << "\rFA193    ";
    Ciphertext gin193 = gout182[1] + 1 * gout183[0] + 1 * gout188[0];
    std::vector<Ciphertext> gout193 = ctx.eval_lut_amortized(&gin193, decomp);

    std::cerr << "\rFA194    ";
    Ciphertext gin194 = gout189[1] + 1 * gout193[0] + 1 * gout191[0];
    std::vector<Ciphertext> gout194 = ctx.eval_lut_amortized(&gin194, decomp);

    std::cerr << "\rFA195    ";
    Ciphertext gin195 = gout191[1] + 1 * gout187[1] + 1 * gout179[1];
    std::vector<Ciphertext> gout195 = ctx.eval_lut_amortized(&gin195, decomp);

    std::cerr << "\rFA196    ";
    Ciphertext gin196 = gout192[1] + 1 * gout194[0] + 1 * gout185[0];
    std::vector<Ciphertext> gout196 = ctx.eval_lut_amortized(&gin196, decomp);

    std::cerr << "\rFA197    ";
    Ciphertext gin197 = gout193[1] + 1 * gout183[1] + 1 * gout188[1];
    std::vector<Ciphertext> gout197 = ctx.eval_lut_amortized(&gin197, decomp);

    std::cerr << "\rFA198    ";
    Ciphertext gin198 = gout194[1] + 1 * gout197[0] + 1 * gout195[0];
    std::vector<Ciphertext> gout198 = ctx.eval_lut_amortized(&gin198, decomp);

    std::cerr << "\rFA199    ";
    Ciphertext gin199 = gout198[1] + 1 * gout197[1] + 1 * gout195[1];
    std::vector<Ciphertext> gout199 = ctx.eval_lut_amortized(&gin199, decomp);

    std::cerr << "\rFA200    ";
    Ciphertext gin200 = gout196[1] + 1 * gout198[0] + 1 * gout190[0];
    std::vector<Ciphertext> gout200 = ctx.eval_lut_amortized(&gin200, decomp);

    std::cerr << "\rFA201    ";
    Ciphertext gin201 = gout200[1] + 1 * gout199[0] + 1 * gout190[1];
    std::vector<Ciphertext> gout201 = ctx.eval_lut_amortized(&gin201, decomp);

    std::cerr << "\rFA202    ";
    Ciphertext gin202 = gout201[1] + 1 * gout199[1] + 1 * 0;
    std::vector<Ciphertext> gout202 = ctx.eval_lut_amortized(&gin202, decomp);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(ctx.decrypt(&gout74[0])); /* out192 */
    test_out.push_back(ctx.decrypt(&gout103[0])); /* out193 */
    test_out.push_back(ctx.decrypt(&gout130[0])); /* out194 */
    test_out.push_back(ctx.decrypt(&gout147[0])); /* out195 */
    test_out.push_back(ctx.decrypt(&gout163[0])); /* out196 */
    test_out.push_back(ctx.decrypt(&gout175[0])); /* out197 */
    test_out.push_back(ctx.decrypt(&gout186[0])); /* out198 */
    test_out.push_back(ctx.decrypt(&gout192[0])); /* out199 */
    test_out.push_back(ctx.decrypt(&gout196[0])); /* out200 */
    test_out.push_back(ctx.decrypt(&gout200[0])); /* out201 */
    test_out.push_back(ctx.decrypt(&gout201[0])); /* out202 */
    test_out.push_back(ctx.decrypt(&gout202[0])); /* out203 */
    test_out.push_back(ctx.decrypt(&gout202[1])); /* out204 */
    test_out.push_back(0); /* out223 */
    return test_out;
}

static void
BM_sum3d_lut2fa(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(tfhe_11_NTT);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(4);

    for (auto _ : state) {
        test_sum3d_lut2fa(ctx);
    }
}

BENCHMARK(BM_sum3d_lut2fa)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
