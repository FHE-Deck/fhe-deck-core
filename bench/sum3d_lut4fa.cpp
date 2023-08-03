#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_sum3d_lut4fa(FHEContext& ctx, std::vector<uint64_t> out = { 0 })
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
    Ciphertext gin0 = 0 + 1 * ct_out144 + 2 * ct_out145 + 4 * ct_out146 + 1 * ct_out48 + 2 * ct_out49 + 4 * ct_out50;
    std::vector<Ciphertext> gout0 = ctx.eval_lut_amortized(&gin0, decomp);

    std::cerr << "\rFA1    ";
    Ciphertext gin1 = 0 + 1 * ct_out168 + 2 * ct_out169 + 4 * ct_out170 + 1 * ct_out72 + 2 * ct_out73 + 4 * ct_out74;
    std::vector<Ciphertext> gout1 = ctx.eval_lut_amortized(&gin1, decomp);

    std::cerr << "\rFA2    ";
    Ciphertext gin2 = 0 + 1 * ct_out128 + 2 * ct_out129 + 4 * ct_out130 + 1 * ct_out32 + 2 * ct_out33 + 4 * ct_out34;
    std::vector<Ciphertext> gout2 = ctx.eval_lut_amortized(&gin2, decomp);

    std::cerr << "\rFA3    ";
    Ciphertext gin3 = 0 + 1 * ct_out152 + 2 * ct_out153 + 4 * ct_out154 + 1 * ct_out56 + 2 * ct_out57 + 4 * ct_out58;
    std::vector<Ciphertext> gout3 = ctx.eval_lut_amortized(&gin3, decomp);

    std::cerr << "\rFA4    ";
    Ciphertext gin4 = gout1[3] + 1 * ct_out171 + 2 * ct_out172 + 4 * ct_out173 + 1 * ct_out75 + 2 * ct_out76 + 4 * ct_out77;
    std::vector<Ciphertext> gout4 = ctx.eval_lut_amortized(&gin4, decomp);

    std::cerr << "\rFA5    ";
    Ciphertext gin5 = 0 + 1 * ct_out120 + 2 * ct_out121 + 4 * ct_out122 + 1 * ct_out24 + 2 * ct_out25 + 4 * ct_out26;
    std::vector<Ciphertext> gout5 = ctx.eval_lut_amortized(&gin5, decomp);

    std::cerr << "\rFA6    ";
    Ciphertext gin6 = 0 + 1 * ct_out184 + 2 * ct_out185 + 4 * ct_out186 + 1 * ct_out88 + 2 * ct_out89 + 4 * ct_out90;
    std::vector<Ciphertext> gout6 = ctx.eval_lut_amortized(&gin6, decomp);

    std::cerr << "\rFA7    ";
    Ciphertext gin7 = 0 + 1 * ct_out160 + 2 * ct_out161 + 4 * ct_out162 + 1 * ct_out64 + 2 * ct_out65 + 4 * ct_out66;
    std::vector<Ciphertext> gout7 = ctx.eval_lut_amortized(&gin7, decomp);

    std::cerr << "\rFA8    ";
    Ciphertext gin8 = 0 + 1 * ct_out96 + 2 * ct_out97 + 4 * ct_out98 + 1 * ct_out0 + 2 * ct_out1 + 4 * ct_out2;
    std::vector<Ciphertext> gout8 = ctx.eval_lut_amortized(&gin8, decomp);

    std::cerr << "\rFA9    ";
    Ciphertext gin9 = 0 + 1 * ct_out176 + 2 * ct_out177 + 4 * ct_out178 + 1 * ct_out80 + 2 * ct_out81 + 4 * ct_out82;
    std::vector<Ciphertext> gout9 = ctx.eval_lut_amortized(&gin9, decomp);

    std::cerr << "\rFA10    ";
    Ciphertext gin10 = gout2[3] + 1 * ct_out131 + 2 * ct_out132 + 4 * ct_out133 + 1 * ct_out35 + 2 * ct_out36 + 4 * ct_out37;
    std::vector<Ciphertext> gout10 = ctx.eval_lut_amortized(&gin10, decomp);

    std::cerr << "\rFA11    ";
    Ciphertext gin11 = gout8[3] + 1 * ct_out99 + 2 * ct_out100 + 4 * ct_out101 + 1 * ct_out3 + 2 * ct_out4 + 4 * ct_out5;
    std::vector<Ciphertext> gout11 = ctx.eval_lut_amortized(&gin11, decomp);

    std::cerr << "\rFA12    ";
    Ciphertext gin12 = gout5[3] + 1 * ct_out123 + 2 * ct_out124 + 4 * ct_out125 + 1 * ct_out27 + 2 * ct_out28 + 4 * ct_out29;
    std::vector<Ciphertext> gout12 = ctx.eval_lut_amortized(&gin12, decomp);

    std::cerr << "\rFA13    ";
    Ciphertext gin13 = gout10[3] + 1 * ct_out134 + 2 * ct_out135 + 1 * ct_out38 + 2 * ct_out39;
    std::vector<Ciphertext> gout13 = ctx.eval_lut_amortized(&gin13, decomp);

    std::cerr << "\rFA14    ";
    Ciphertext gin14 = 0 + 1 * ct_out104 + 2 * ct_out105 + 4 * ct_out106 + 1 * ct_out8 + 2 * ct_out9 + 4 * ct_out10;
    std::vector<Ciphertext> gout14 = ctx.eval_lut_amortized(&gin14, decomp);

    std::cerr << "\rFA15    ";
    Ciphertext gin15 = gout0[3] + 1 * ct_out147 + 2 * ct_out148 + 4 * ct_out149 + 1 * ct_out51 + 2 * ct_out52 + 4 * ct_out53;
    std::vector<Ciphertext> gout15 = ctx.eval_lut_amortized(&gin15, decomp);

    std::cerr << "\rFA16    ";
    Ciphertext gin16 = 0 + 1 * gout9[0] + 2 * gout9[1] + 4 * gout9[2] + 1 * gout6[0] + 2 * gout6[1] + 4 * gout6[2];
    std::vector<Ciphertext> gout16 = ctx.eval_lut_amortized(&gin16, decomp);

    std::cerr << "\rFA17    ";
    Ciphertext gin17 = gout15[3] + 1 * ct_out150 + 2 * ct_out151 + 1 * ct_out54 + 2 * ct_out55;
    std::vector<Ciphertext> gout17 = ctx.eval_lut_amortized(&gin17, decomp);

    std::cerr << "\rFA18    ";
    Ciphertext gin18 = gout11[3] + 1 * ct_out102 + 2 * ct_out103 + 1 * ct_out6 + 2 * ct_out7;
    std::vector<Ciphertext> gout18 = ctx.eval_lut_amortized(&gin18, decomp);

    std::cerr << "\rFA19    ";
    Ciphertext gin19 = gout4[3] + 1 * ct_out174 + 2 * ct_out175 + 1 * ct_out78 + 2 * ct_out79;
    std::vector<Ciphertext> gout19 = ctx.eval_lut_amortized(&gin19, decomp);

    std::cerr << "\rFA20    ";
    Ciphertext gin20 = 0 + 1 * gout7[0] + 2 * gout7[1] + 4 * gout7[2] + 1 * gout1[0] + 2 * gout1[1] + 4 * gout1[2];
    std::vector<Ciphertext> gout20 = ctx.eval_lut_amortized(&gin20, decomp);

    std::cerr << "\rFA21    ";
    Ciphertext gin21 = gout6[3] + 1 * ct_out187 + 2 * ct_out188 + 4 * ct_out189 + 1 * ct_out91 + 2 * ct_out92 + 4 * ct_out93;
    std::vector<Ciphertext> gout21 = ctx.eval_lut_amortized(&gin21, decomp);

    std::cerr << "\rFA22    ";
    Ciphertext gin22 = 0 + 1 * gout0[0] + 2 * gout0[1] + 4 * gout0[2] + 1 * gout3[0] + 2 * gout3[1] + 4 * gout3[2];
    std::vector<Ciphertext> gout22 = ctx.eval_lut_amortized(&gin22, decomp);

    std::cerr << "\rFA23    ";
    Ciphertext gin23 = gout9[3] + 1 * ct_out179 + 2 * ct_out180 + 4 * ct_out181 + 1 * ct_out83 + 2 * ct_out84 + 4 * ct_out85;
    std::vector<Ciphertext> gout23 = ctx.eval_lut_amortized(&gin23, decomp);

    std::cerr << "\rFA24    ";
    Ciphertext gin24 = gout23[3] + 1 * ct_out182 + 2 * ct_out183 + 1 * ct_out86 + 2 * ct_out87;
    std::vector<Ciphertext> gout24 = ctx.eval_lut_amortized(&gin24, decomp);

    std::cerr << "\rFA25    ";
    Ciphertext gin25 = 0 + 1 * ct_out136 + 2 * ct_out137 + 4 * ct_out138 + 1 * ct_out40 + 2 * ct_out41 + 4 * ct_out42;
    std::vector<Ciphertext> gout25 = ctx.eval_lut_amortized(&gin25, decomp);

    std::cerr << "\rFA26    ";
    Ciphertext gin26 = 0 + 1 * gout2[0] + 2 * gout2[1] + 4 * gout2[2] + 1 * gout25[0] + 2 * gout25[1] + 4 * gout25[2];
    std::vector<Ciphertext> gout26 = ctx.eval_lut_amortized(&gin26, decomp);

    std::cerr << "\rFA27    ";
    Ciphertext gin27 = gout12[3] + 1 * ct_out126 + 2 * ct_out127 + 1 * ct_out30 + 2 * ct_out31;
    std::vector<Ciphertext> gout27 = ctx.eval_lut_amortized(&gin27, decomp);

    std::cerr << "\rFA28    ";
    Ciphertext gin28 = gout14[3] + 1 * ct_out107 + 2 * ct_out108 + 4 * ct_out109 + 1 * ct_out11 + 2 * ct_out12 + 4 * ct_out13;
    std::vector<Ciphertext> gout28 = ctx.eval_lut_amortized(&gin28, decomp);

    std::cerr << "\rFA29    ";
    Ciphertext gin29 = 0 + 1 * gout26[0] + 2 * gout26[1] + 4 * gout26[2] + 1 * gout22[0] + 2 * gout22[1] + 4 * gout22[2];
    std::vector<Ciphertext> gout29 = ctx.eval_lut_amortized(&gin29, decomp);

    std::cerr << "\rFA30    ";
    Ciphertext gin30 = 0 + 1 * ct_out112 + 2 * ct_out113 + 4 * ct_out114 + 1 * ct_out16 + 2 * ct_out17 + 4 * ct_out18;
    std::vector<Ciphertext> gout30 = ctx.eval_lut_amortized(&gin30, decomp);

    std::cerr << "\rFA31    ";
    Ciphertext gin31 = gout7[3] + 1 * ct_out163 + 2 * ct_out164 + 4 * ct_out165 + 1 * ct_out67 + 2 * ct_out68 + 4 * ct_out69;
    std::vector<Ciphertext> gout31 = ctx.eval_lut_amortized(&gin31, decomp);

    std::cerr << "\rFA32    ";
    Ciphertext gin32 = gout16[3] + 1 * gout23[0] + 2 * gout23[1] + 4 * gout23[2] + 1 * gout21[0] + 2 * gout21[1] + 4 * gout21[2];
    std::vector<Ciphertext> gout32 = ctx.eval_lut_amortized(&gin32, decomp);

    std::cerr << "\rFA33    ";
    Ciphertext gin33 = gout3[3] + 1 * ct_out155 + 2 * ct_out156 + 4 * ct_out157 + 1 * ct_out59 + 2 * ct_out60 + 4 * ct_out61;
    std::vector<Ciphertext> gout33 = ctx.eval_lut_amortized(&gin33, decomp);

    std::cerr << "\rFA34    ";
    Ciphertext gin34 = 0 + 1 * gout8[0] + 2 * gout8[1] + 4 * gout8[2] + 1 * gout14[0] + 2 * gout14[1] + 4 * gout14[2];
    std::vector<Ciphertext> gout34 = ctx.eval_lut_amortized(&gin34, decomp);

    std::cerr << "\rFA35    ";
    Ciphertext gin35 = gout31[3] + 1 * ct_out166 + 2 * ct_out167 + 1 * ct_out70 + 2 * ct_out71;
    std::vector<Ciphertext> gout35 = ctx.eval_lut_amortized(&gin35, decomp);

    std::cerr << "\rFA36    ";
    Ciphertext gin36 = gout28[3] + 1 * ct_out110 + 2 * ct_out111 + 1 * ct_out14 + 2 * ct_out15;
    std::vector<Ciphertext> gout36 = ctx.eval_lut_amortized(&gin36, decomp);

    std::cerr << "\rFA37    ";
    Ciphertext gin37 = gout25[3] + 1 * ct_out139 + 2 * ct_out140 + 4 * ct_out141 + 1 * ct_out43 + 2 * ct_out44 + 4 * ct_out45;
    std::vector<Ciphertext> gout37 = ctx.eval_lut_amortized(&gin37, decomp);

    std::cerr << "\rFA38    ";
    Ciphertext gin38 = 0 + 1 * gout20[0] + 2 * gout20[1] + 4 * gout20[2] + 1 * gout16[0] + 2 * gout16[1] + 4 * gout16[2];
    std::vector<Ciphertext> gout38 = ctx.eval_lut_amortized(&gin38, decomp);

    std::cerr << "\rFA39    ";
    Ciphertext gin39 = gout30[3] + 1 * ct_out115 + 2 * ct_out116 + 4 * ct_out117 + 1 * ct_out19 + 2 * ct_out20 + 4 * ct_out21;
    std::vector<Ciphertext> gout39 = ctx.eval_lut_amortized(&gin39, decomp);

    std::cerr << "\rFA40    ";
    Ciphertext gin40 = gout37[3] + 1 * ct_out142 + 2 * ct_out143 + 1 * ct_out46 + 2 * ct_out47;
    std::vector<Ciphertext> gout40 = ctx.eval_lut_amortized(&gin40, decomp);

    std::cerr << "\rFA41    ";
    Ciphertext gin41 = gout26[3] + 1 * gout10[0] + 2 * gout10[1] + 4 * gout10[2] + 1 * gout37[0] + 2 * gout37[1] + 4 * gout37[2];
    std::vector<Ciphertext> gout41 = ctx.eval_lut_amortized(&gin41, decomp);

    std::cerr << "\rFA42    ";
    Ciphertext gin42 = gout21[3] + 1 * ct_out190 + 2 * ct_out191 + 1 * ct_out94 + 2 * ct_out95;
    std::vector<Ciphertext> gout42 = ctx.eval_lut_amortized(&gin42, decomp);

    std::cerr << "\rFA43    ";
    Ciphertext gin43 = gout22[3] + 1 * gout15[0] + 2 * gout15[1] + 4 * gout15[2] + 1 * gout33[0] + 2 * gout33[1] + 4 * gout33[2];
    std::vector<Ciphertext> gout43 = ctx.eval_lut_amortized(&gin43, decomp);

    std::cerr << "\rFA44    ";
    Ciphertext gin44 = gout20[3] + 1 * gout31[0] + 2 * gout31[1] + 4 * gout31[2] + 1 * gout4[0] + 2 * gout4[1] + 4 * gout4[2];
    std::vector<Ciphertext> gout44 = ctx.eval_lut_amortized(&gin44, decomp);

    std::cerr << "\rFA45    ";
    Ciphertext gin45 = gout39[3] + 1 * ct_out118 + 2 * ct_out119 + 1 * ct_out22 + 2 * ct_out23;
    std::vector<Ciphertext> gout45 = ctx.eval_lut_amortized(&gin45, decomp);

    std::cerr << "\rFA46    ";
    Ciphertext gin46 = 0 + 1 * gout30[0] + 2 * gout30[1] + 4 * gout30[2] + 1 * gout5[0] + 2 * gout5[1] + 4 * gout5[2];
    std::vector<Ciphertext> gout46 = ctx.eval_lut_amortized(&gin46, decomp);

    std::cerr << "\rFA47    ";
    Ciphertext gin47 = gout29[3] + 1 * gout41[0] + 2 * gout41[1] + 4 * gout41[2] + 1 * gout43[0] + 2 * gout43[1] + 4 * gout43[2];
    std::vector<Ciphertext> gout47 = ctx.eval_lut_amortized(&gin47, decomp);

    std::cerr << "\rFA48    ";
    Ciphertext gin48 = gout33[3] + 1 * ct_out158 + 2 * ct_out159 + 1 * ct_out62 + 2 * ct_out63;
    std::vector<Ciphertext> gout48 = ctx.eval_lut_amortized(&gin48, decomp);

    std::cerr << "\rFA49    ";
    Ciphertext gin49 = gout38[3] + 1 * gout44[0] + 2 * gout44[1] + 4 * gout44[2] + 1 * gout32[0] + 2 * gout32[1] + 4 * gout32[2];
    std::vector<Ciphertext> gout49 = ctx.eval_lut_amortized(&gin49, decomp);

    std::cerr << "\rFA50    ";
    Ciphertext gin50 = gout34[3] + 1 * gout11[0] + 2 * gout11[1] + 4 * gout11[2] + 1 * gout28[0] + 2 * gout28[1] + 4 * gout28[2];
    std::vector<Ciphertext> gout50 = ctx.eval_lut_amortized(&gin50, decomp);

    std::cerr << "\rFA51    ";
    Ciphertext gin51 = 0 + 1 * gout34[0] + 2 * gout34[1] + 4 * gout34[2] + 1 * gout46[0] + 2 * gout46[1] + 4 * gout46[2];
    std::vector<Ciphertext> gout51 = ctx.eval_lut_amortized(&gin51, decomp);

    std::cerr << "\rFA52    ";
    Ciphertext gin52 = 0 + 1 * gout51[0] + 2 * gout51[1] + 4 * gout51[2] + 1 * gout29[0] + 2 * gout29[1] + 4 * gout29[2];
    std::vector<Ciphertext> gout52 = ctx.eval_lut_amortized(&gin52, decomp);

    std::cerr << "\rFA53    ";
    Ciphertext gin53 = gout43[3] + 1 * gout17[0] + 2 * gout17[1] + 4 * gout17[2] + 1 * gout48[0] + 2 * gout48[1] + 4 * gout48[2];
    std::vector<Ciphertext> gout53 = ctx.eval_lut_amortized(&gin53, decomp);

    std::cerr << "\rFA54    ";
    Ciphertext gin54 = gout32[3] + 1 * gout24[0] + 2 * gout24[1] + 4 * gout24[2] + 1 * gout42[0] + 2 * gout42[1] + 4 * gout42[2];
    std::vector<Ciphertext> gout54 = ctx.eval_lut_amortized(&gin54, decomp);

    std::cerr << "\rFA55    ";
    Ciphertext gin55 = 0 + 1 * gout52[0] + 2 * gout52[1] + 4 * gout52[2] + 1 * gout38[0] + 2 * gout38[1] + 4 * gout38[2];
    std::vector<Ciphertext> gout55 = ctx.eval_lut_amortized(&gin55, decomp);

    std::cerr << "\rFA56    ";
    Ciphertext gin56 = gout41[3] + 1 * gout13[0] + 2 * gout13[1] + 4 * gout13[2] + 1 * gout40[0] + 2 * gout40[1] + 4 * gout40[2];
    std::vector<Ciphertext> gout56 = ctx.eval_lut_amortized(&gin56, decomp);

    std::cerr << "\rFA57    ";
    Ciphertext gin57 = gout46[3] + 1 * gout39[0] + 2 * gout39[1] + 4 * gout39[2] + 1 * gout12[0] + 2 * gout12[1] + 4 * gout12[2];
    std::vector<Ciphertext> gout57 = ctx.eval_lut_amortized(&gin57, decomp);

    std::cerr << "\rFA58    ";
    Ciphertext gin58 = gout50[3] + 1 * gout18[0] + 2 * gout18[1] + 4 * gout18[2] + 1 * gout36[0] + 2 * gout36[1] + 4 * gout36[2];
    std::vector<Ciphertext> gout58 = ctx.eval_lut_amortized(&gin58, decomp);

    std::cerr << "\rFA59    ";
    Ciphertext gin59 = gout57[3] + 1 * gout45[0] + 2 * gout45[1] + 4 * gout45[2] + 1 * gout27[0] + 2 * gout27[1] + 4 * gout27[2];
    std::vector<Ciphertext> gout59 = ctx.eval_lut_amortized(&gin59, decomp);

    std::cerr << "\rFA60    ";
    Ciphertext gin60 = gout47[3] + 1 * gout56[0] + 2 * gout56[1] + 4 * gout56[2] + 1 * gout53[0] + 2 * gout53[1] + 4 * gout53[2];
    std::vector<Ciphertext> gout60 = ctx.eval_lut_amortized(&gin60, decomp);

    std::cerr << "\rFA61    ";
    Ciphertext gin61 = gout51[3] + 1 * gout50[0] + 2 * gout50[1] + 4 * gout50[2] + 1 * gout57[0] + 2 * gout57[1] + 4 * gout57[2];
    std::vector<Ciphertext> gout61 = ctx.eval_lut_amortized(&gin61, decomp);

    std::cerr << "\rFA62    ";
    Ciphertext gin62 = gout44[3] + 1 * gout35[0] + 2 * gout35[1] + 4 * gout35[2] + 1 * gout19[0] + 2 * gout19[1] + 4 * gout19[2];
    std::vector<Ciphertext> gout62 = ctx.eval_lut_amortized(&gin62, decomp);

    std::cerr << "\rFA63    ";
    Ciphertext gin63 = gout52[3] + 1 * gout61[0] + 2 * gout61[1] + 4 * gout61[2] + 1 * gout47[0] + 2 * gout47[1] + 4 * gout47[2];
    std::vector<Ciphertext> gout63 = ctx.eval_lut_amortized(&gin63, decomp);

    std::cerr << "\rFA64    ";
    Ciphertext gin64 = gout49[3] + 1 * gout62[0] + 2 * gout62[1] + 4 * gout62[2] + 1 * gout54[0] + 2 * gout54[1] + 4 * gout54[2];
    std::vector<Ciphertext> gout64 = ctx.eval_lut_amortized(&gin64, decomp);

    std::cerr << "\rFA65    ";
    Ciphertext gin65 = gout60[3] + 1 * gout56[3] + 1 * gout53[3];
    std::vector<Ciphertext> gout65 = ctx.eval_lut_amortized(&gin65, decomp);

    std::cerr << "\rFA66    ";
    Ciphertext gin66 = gout61[3] + 1 * gout58[0] + 2 * gout58[1] + 4 * gout58[2] + 1 * gout59[0] + 2 * gout59[1] + 4 * gout59[2];
    std::vector<Ciphertext> gout66 = ctx.eval_lut_amortized(&gin66, decomp);

    std::cerr << "\rFA67    ";
    Ciphertext gin67 = gout64[3] + 1 * gout62[3] + 1 * gout54[3];
    std::vector<Ciphertext> gout67 = ctx.eval_lut_amortized(&gin67, decomp);

    std::cerr << "\rFA68    ";
    Ciphertext gin68 = gout55[3] + 1 * gout63[0] + 2 * gout63[1] + 4 * gout63[2] + 1 * gout49[0] + 2 * gout49[1] + 4 * gout49[2];
    std::vector<Ciphertext> gout68 = ctx.eval_lut_amortized(&gin68, decomp);

    std::cerr << "\rFA69    ";
    Ciphertext gin69 = gout66[3] + 1 * gout58[3] + 1 * gout59[3];
    std::vector<Ciphertext> gout69 = ctx.eval_lut_amortized(&gin69, decomp);

    std::cerr << "\rFA70    ";
    Ciphertext gin70 = gout63[3] + 1 * gout66[0] + 2 * gout66[1] + 4 * gout66[2] + 1 * gout60[0] + 2 * gout60[1] + 4 * gout60[2];
    std::vector<Ciphertext> gout70 = ctx.eval_lut_amortized(&gin70, decomp);

    std::cerr << "\rFA71    ";
    Ciphertext gin71 = gout68[3] + 1 * gout70[0] + 2 * gout70[1] + 4 * gout70[2] + 1 * gout64[0] + 2 * gout64[1] + 4 * gout64[2];
    std::vector<Ciphertext> gout71 = ctx.eval_lut_amortized(&gin71, decomp);

    std::cerr << "\rFA72    ";
    Ciphertext gin72 = gout70[3] + 1 * gout69[0] + 2 * gout69[1] + 1 * gout65[0] + 2 * gout65[1];
    std::vector<Ciphertext> gout72 = ctx.eval_lut_amortized(&gin72, decomp);

    std::cerr << "\rFA73    ";
    Ciphertext gin73 = gout71[3] + 1 * gout72[0] + 2 * gout72[1] + 4 * gout72[2] + 1 * gout67[0] + 2 * gout67[1] + 4 * 0;
    std::vector<Ciphertext> gout73 = ctx.eval_lut_amortized(&gin73, decomp);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(ctx.decrypt(&gout55[0])); /* out192 */
    test_out.push_back(ctx.decrypt(&gout55[1])); /* out193 */
    test_out.push_back(ctx.decrypt(&gout55[2])); /* out194 */
    test_out.push_back(ctx.decrypt(&gout68[0])); /* out195 */
    test_out.push_back(ctx.decrypt(&gout68[1])); /* out196 */
    test_out.push_back(ctx.decrypt(&gout68[2])); /* out197 */
    test_out.push_back(ctx.decrypt(&gout71[0])); /* out198 */
    test_out.push_back(ctx.decrypt(&gout71[1])); /* out199 */
    test_out.push_back(ctx.decrypt(&gout71[2])); /* out200 */
    test_out.push_back(ctx.decrypt(&gout73[0])); /* out201 */
    test_out.push_back(ctx.decrypt(&gout73[1])); /* out202 */
    test_out.push_back(ctx.decrypt(&gout73[2])); /* out203 */
    test_out.push_back(ctx.decrypt(&gout73[3])); /* out204 */
    test_out.push_back(0); /* out223 */
    return test_out;
}

static void
BM_sum3d_lut4fa(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(tfhe_12_NTT_amortized);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(16);

    for (auto _ : state) {
        test_sum3d_lut4fa(ctx);
    }
}

BENCHMARK(BM_sum3d_lut4fa)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
