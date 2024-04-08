#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_structs_3d_lut3fa(FHEContext& ctx, std::vector<uint64_t> data = { 0 })
{
    Ciphertext ct_data0 = ctx.encrypt_public((data[0] >> 0) & 1);
    Ciphertext ct_data1 = ctx.encrypt_public((data[0] >> 1) & 1);
    Ciphertext ct_data2 = ctx.encrypt_public((data[0] >> 2) & 1);
    Ciphertext ct_data3 = ctx.encrypt_public((data[0] >> 3) & 1);
    Ciphertext ct_data4 = ctx.encrypt_public((data[0] >> 4) & 1);
    Ciphertext ct_data5 = ctx.encrypt_public((data[0] >> 5) & 1);
    Ciphertext ct_data6 = ctx.encrypt_public((data[0] >> 6) & 1);
    Ciphertext ct_data7 = ctx.encrypt_public((data[0] >> 7) & 1);
    Ciphertext ct_data8 = ctx.encrypt_public((data[0] >> 8) & 1);
    Ciphertext ct_data9 = ctx.encrypt_public((data[0] >> 9) & 1);
    Ciphertext ct_data10 = ctx.encrypt_public((data[0] >> 10) & 1);
    Ciphertext ct_data11 = ctx.encrypt_public((data[0] >> 11) & 1);
    Ciphertext ct_data12 = ctx.encrypt_public((data[0] >> 12) & 1);
    Ciphertext ct_data13 = ctx.encrypt_public((data[0] >> 13) & 1);
    Ciphertext ct_data14 = ctx.encrypt_public((data[0] >> 14) & 1);
    Ciphertext ct_data15 = ctx.encrypt_public((data[0] >> 15) & 1);
    Ciphertext ct_data16 = ctx.encrypt_public((data[0] >> 16) & 1);
    Ciphertext ct_data17 = ctx.encrypt_public((data[0] >> 17) & 1);
    Ciphertext ct_data18 = ctx.encrypt_public((data[0] >> 18) & 1);
    Ciphertext ct_data19 = ctx.encrypt_public((data[0] >> 19) & 1);
    Ciphertext ct_data20 = ctx.encrypt_public((data[0] >> 20) & 1);
    Ciphertext ct_data21 = ctx.encrypt_public((data[0] >> 21) & 1);
    Ciphertext ct_data22 = ctx.encrypt_public((data[0] >> 22) & 1);
    Ciphertext ct_data23 = ctx.encrypt_public((data[0] >> 23) & 1);
    Ciphertext ct_data24 = ctx.encrypt_public((data[0] >> 24) & 1);
    Ciphertext ct_data25 = ctx.encrypt_public((data[0] >> 25) & 1);
    Ciphertext ct_data26 = ctx.encrypt_public((data[0] >> 26) & 1);
    Ciphertext ct_data27 = ctx.encrypt_public((data[0] >> 27) & 1);
    Ciphertext ct_data28 = ctx.encrypt_public((data[0] >> 28) & 1);
    Ciphertext ct_data29 = ctx.encrypt_public((data[0] >> 29) & 1);
    Ciphertext ct_data30 = ctx.encrypt_public((data[0] >> 30) & 1);
    Ciphertext ct_data32 = ctx.encrypt_public((data[0] >> 31) & 1);
    Ciphertext ct_data33 = ctx.encrypt_public((data[0] >> 32) & 1);
    Ciphertext ct_data34 = ctx.encrypt_public((data[0] >> 33) & 1);
    Ciphertext ct_data35 = ctx.encrypt_public((data[0] >> 34) & 1);
    Ciphertext ct_data36 = ctx.encrypt_public((data[0] >> 35) & 1);
    Ciphertext ct_data37 = ctx.encrypt_public((data[0] >> 36) & 1);
    Ciphertext ct_data38 = ctx.encrypt_public((data[0] >> 37) & 1);
    Ciphertext ct_data39 = ctx.encrypt_public((data[0] >> 38) & 1);
    Ciphertext ct_data40 = ctx.encrypt_public((data[0] >> 39) & 1);
    Ciphertext ct_data41 = ctx.encrypt_public((data[0] >> 40) & 1);
    Ciphertext ct_data42 = ctx.encrypt_public((data[0] >> 41) & 1);
    Ciphertext ct_data43 = ctx.encrypt_public((data[0] >> 42) & 1);
    Ciphertext ct_data44 = ctx.encrypt_public((data[0] >> 43) & 1);
    Ciphertext ct_data45 = ctx.encrypt_public((data[0] >> 44) & 1);
    Ciphertext ct_data46 = ctx.encrypt_public((data[0] >> 45) & 1);
    Ciphertext ct_data47 = ctx.encrypt_public((data[0] >> 46) & 1);
    Ciphertext ct_data48 = ctx.encrypt_public((data[0] >> 47) & 1);
    Ciphertext ct_data49 = ctx.encrypt_public((data[0] >> 48) & 1);
    Ciphertext ct_data50 = ctx.encrypt_public((data[0] >> 49) & 1);
    Ciphertext ct_data51 = ctx.encrypt_public((data[0] >> 50) & 1);
    Ciphertext ct_data52 = ctx.encrypt_public((data[0] >> 51) & 1);
    Ciphertext ct_data53 = ctx.encrypt_public((data[0] >> 52) & 1);
    Ciphertext ct_data54 = ctx.encrypt_public((data[0] >> 53) & 1);
    Ciphertext ct_data55 = ctx.encrypt_public((data[0] >> 54) & 1);
    Ciphertext ct_data56 = ctx.encrypt_public((data[0] >> 55) & 1);
    Ciphertext ct_data57 = ctx.encrypt_public((data[0] >> 56) & 1);
    Ciphertext ct_data58 = ctx.encrypt_public((data[0] >> 57) & 1);
    Ciphertext ct_data59 = ctx.encrypt_public((data[0] >> 58) & 1);
    Ciphertext ct_data60 = ctx.encrypt_public((data[0] >> 59) & 1);
    Ciphertext ct_data61 = ctx.encrypt_public((data[0] >> 60) & 1);
    Ciphertext ct_data62 = ctx.encrypt_public((data[0] >> 61) & 1);
    Ciphertext ct_data64 = ctx.encrypt_public((data[0] >> 62) & 1);
    Ciphertext ct_data65 = ctx.encrypt_public((data[0] >> 63) & 1);
    Ciphertext ct_data66 = ctx.encrypt_public((data[1] >> 0) & 1);
    Ciphertext ct_data67 = ctx.encrypt_public((data[1] >> 1) & 1);
    Ciphertext ct_data68 = ctx.encrypt_public((data[1] >> 2) & 1);
    Ciphertext ct_data69 = ctx.encrypt_public((data[1] >> 3) & 1);
    Ciphertext ct_data70 = ctx.encrypt_public((data[1] >> 4) & 1);
    Ciphertext ct_data71 = ctx.encrypt_public((data[1] >> 5) & 1);
    Ciphertext ct_data72 = ctx.encrypt_public((data[1] >> 6) & 1);
    Ciphertext ct_data73 = ctx.encrypt_public((data[1] >> 7) & 1);
    Ciphertext ct_data74 = ctx.encrypt_public((data[1] >> 8) & 1);
    Ciphertext ct_data75 = ctx.encrypt_public((data[1] >> 9) & 1);
    Ciphertext ct_data76 = ctx.encrypt_public((data[1] >> 10) & 1);
    Ciphertext ct_data77 = ctx.encrypt_public((data[1] >> 11) & 1);
    Ciphertext ct_data78 = ctx.encrypt_public((data[1] >> 12) & 1);
    Ciphertext ct_data79 = ctx.encrypt_public((data[1] >> 13) & 1);
    Ciphertext ct_data80 = ctx.encrypt_public((data[1] >> 14) & 1);
    Ciphertext ct_data81 = ctx.encrypt_public((data[1] >> 15) & 1);
    Ciphertext ct_data82 = ctx.encrypt_public((data[1] >> 16) & 1);
    Ciphertext ct_data83 = ctx.encrypt_public((data[1] >> 17) & 1);
    Ciphertext ct_data84 = ctx.encrypt_public((data[1] >> 18) & 1);
    Ciphertext ct_data85 = ctx.encrypt_public((data[1] >> 19) & 1);
    Ciphertext ct_data86 = ctx.encrypt_public((data[1] >> 20) & 1);
    Ciphertext ct_data87 = ctx.encrypt_public((data[1] >> 21) & 1);
    Ciphertext ct_data88 = ctx.encrypt_public((data[1] >> 22) & 1);
    Ciphertext ct_data89 = ctx.encrypt_public((data[1] >> 23) & 1);
    Ciphertext ct_data90 = ctx.encrypt_public((data[1] >> 24) & 1);
    Ciphertext ct_data91 = ctx.encrypt_public((data[1] >> 25) & 1);
    Ciphertext ct_data92 = ctx.encrypt_public((data[1] >> 26) & 1);
    Ciphertext ct_data93 = ctx.encrypt_public((data[1] >> 27) & 1);
    Ciphertext ct_data94 = ctx.encrypt_public((data[1] >> 28) & 1);
    Ciphertext ct_data96 = ctx.encrypt_public((data[1] >> 29) & 1);
    Ciphertext ct_data97 = ctx.encrypt_public((data[1] >> 30) & 1);
    Ciphertext ct_data98 = ctx.encrypt_public((data[1] >> 31) & 1);
    Ciphertext ct_data99 = ctx.encrypt_public((data[1] >> 32) & 1);
    Ciphertext ct_data100 = ctx.encrypt_public((data[1] >> 33) & 1);
    Ciphertext ct_data101 = ctx.encrypt_public((data[1] >> 34) & 1);
    Ciphertext ct_data102 = ctx.encrypt_public((data[1] >> 35) & 1);
    Ciphertext ct_data103 = ctx.encrypt_public((data[1] >> 36) & 1);
    Ciphertext ct_data104 = ctx.encrypt_public((data[1] >> 37) & 1);
    Ciphertext ct_data105 = ctx.encrypt_public((data[1] >> 38) & 1);
    Ciphertext ct_data106 = ctx.encrypt_public((data[1] >> 39) & 1);
    Ciphertext ct_data107 = ctx.encrypt_public((data[1] >> 40) & 1);
    Ciphertext ct_data108 = ctx.encrypt_public((data[1] >> 41) & 1);
    Ciphertext ct_data109 = ctx.encrypt_public((data[1] >> 42) & 1);
    Ciphertext ct_data110 = ctx.encrypt_public((data[1] >> 43) & 1);
    Ciphertext ct_data111 = ctx.encrypt_public((data[1] >> 44) & 1);
    Ciphertext ct_data112 = ctx.encrypt_public((data[1] >> 45) & 1);
    Ciphertext ct_data113 = ctx.encrypt_public((data[1] >> 46) & 1);
    Ciphertext ct_data114 = ctx.encrypt_public((data[1] >> 47) & 1);
    Ciphertext ct_data115 = ctx.encrypt_public((data[1] >> 48) & 1);
    Ciphertext ct_data116 = ctx.encrypt_public((data[1] >> 49) & 1);
    Ciphertext ct_data117 = ctx.encrypt_public((data[1] >> 50) & 1);
    Ciphertext ct_data118 = ctx.encrypt_public((data[1] >> 51) & 1);
    Ciphertext ct_data119 = ctx.encrypt_public((data[1] >> 52) & 1);
    Ciphertext ct_data120 = ctx.encrypt_public((data[1] >> 53) & 1);
    Ciphertext ct_data121 = ctx.encrypt_public((data[1] >> 54) & 1);
    Ciphertext ct_data122 = ctx.encrypt_public((data[1] >> 55) & 1);
    Ciphertext ct_data123 = ctx.encrypt_public((data[1] >> 56) & 1);
    Ciphertext ct_data124 = ctx.encrypt_public((data[1] >> 57) & 1);
    Ciphertext ct_data125 = ctx.encrypt_public((data[1] >> 58) & 1);
    Ciphertext ct_data126 = ctx.encrypt_public((data[1] >> 59) & 1);
    Ciphertext ct_data128 = ctx.encrypt_public((data[1] >> 60) & 1);
    Ciphertext ct_data129 = ctx.encrypt_public((data[1] >> 61) & 1);
    Ciphertext ct_data130 = ctx.encrypt_public((data[1] >> 62) & 1);
    Ciphertext ct_data131 = ctx.encrypt_public((data[1] >> 63) & 1);
    Ciphertext ct_data132 = ctx.encrypt_public((data[2] >> 0) & 1);
    Ciphertext ct_data133 = ctx.encrypt_public((data[2] >> 1) & 1);
    Ciphertext ct_data134 = ctx.encrypt_public((data[2] >> 2) & 1);
    Ciphertext ct_data135 = ctx.encrypt_public((data[2] >> 3) & 1);
    Ciphertext ct_data136 = ctx.encrypt_public((data[2] >> 4) & 1);
    Ciphertext ct_data137 = ctx.encrypt_public((data[2] >> 5) & 1);
    Ciphertext ct_data138 = ctx.encrypt_public((data[2] >> 6) & 1);
    Ciphertext ct_data139 = ctx.encrypt_public((data[2] >> 7) & 1);
    Ciphertext ct_data140 = ctx.encrypt_public((data[2] >> 8) & 1);
    Ciphertext ct_data141 = ctx.encrypt_public((data[2] >> 9) & 1);
    Ciphertext ct_data142 = ctx.encrypt_public((data[2] >> 10) & 1);
    Ciphertext ct_data143 = ctx.encrypt_public((data[2] >> 11) & 1);
    Ciphertext ct_data144 = ctx.encrypt_public((data[2] >> 12) & 1);
    Ciphertext ct_data145 = ctx.encrypt_public((data[2] >> 13) & 1);
    Ciphertext ct_data146 = ctx.encrypt_public((data[2] >> 14) & 1);
    Ciphertext ct_data147 = ctx.encrypt_public((data[2] >> 15) & 1);
    Ciphertext ct_data148 = ctx.encrypt_public((data[2] >> 16) & 1);
    Ciphertext ct_data149 = ctx.encrypt_public((data[2] >> 17) & 1);
    Ciphertext ct_data150 = ctx.encrypt_public((data[2] >> 18) & 1);
    Ciphertext ct_data151 = ctx.encrypt_public((data[2] >> 19) & 1);
    Ciphertext ct_data152 = ctx.encrypt_public((data[2] >> 20) & 1);
    Ciphertext ct_data153 = ctx.encrypt_public((data[2] >> 21) & 1);
    Ciphertext ct_data154 = ctx.encrypt_public((data[2] >> 22) & 1);
    Ciphertext ct_data155 = ctx.encrypt_public((data[2] >> 23) & 1);
    Ciphertext ct_data156 = ctx.encrypt_public((data[2] >> 24) & 1);
    Ciphertext ct_data157 = ctx.encrypt_public((data[2] >> 25) & 1);
    Ciphertext ct_data158 = ctx.encrypt_public((data[2] >> 26) & 1);
    Ciphertext ct_data160 = ctx.encrypt_public((data[2] >> 27) & 1);
    Ciphertext ct_data161 = ctx.encrypt_public((data[2] >> 28) & 1);
    Ciphertext ct_data162 = ctx.encrypt_public((data[2] >> 29) & 1);
    Ciphertext ct_data163 = ctx.encrypt_public((data[2] >> 30) & 1);
    Ciphertext ct_data164 = ctx.encrypt_public((data[2] >> 31) & 1);
    Ciphertext ct_data165 = ctx.encrypt_public((data[2] >> 32) & 1);
    Ciphertext ct_data166 = ctx.encrypt_public((data[2] >> 33) & 1);
    Ciphertext ct_data167 = ctx.encrypt_public((data[2] >> 34) & 1);
    Ciphertext ct_data168 = ctx.encrypt_public((data[2] >> 35) & 1);
    Ciphertext ct_data169 = ctx.encrypt_public((data[2] >> 36) & 1);
    Ciphertext ct_data170 = ctx.encrypt_public((data[2] >> 37) & 1);
    Ciphertext ct_data171 = ctx.encrypt_public((data[2] >> 38) & 1);
    Ciphertext ct_data172 = ctx.encrypt_public((data[2] >> 39) & 1);
    Ciphertext ct_data173 = ctx.encrypt_public((data[2] >> 40) & 1);
    Ciphertext ct_data174 = ctx.encrypt_public((data[2] >> 41) & 1);
    Ciphertext ct_data175 = ctx.encrypt_public((data[2] >> 42) & 1);
    Ciphertext ct_data176 = ctx.encrypt_public((data[2] >> 43) & 1);
    Ciphertext ct_data177 = ctx.encrypt_public((data[2] >> 44) & 1);
    Ciphertext ct_data178 = ctx.encrypt_public((data[2] >> 45) & 1);
    Ciphertext ct_data179 = ctx.encrypt_public((data[2] >> 46) & 1);
    Ciphertext ct_data180 = ctx.encrypt_public((data[2] >> 47) & 1);
    Ciphertext ct_data181 = ctx.encrypt_public((data[2] >> 48) & 1);
    Ciphertext ct_data182 = ctx.encrypt_public((data[2] >> 49) & 1);
    Ciphertext ct_data183 = ctx.encrypt_public((data[2] >> 50) & 1);
    Ciphertext ct_data184 = ctx.encrypt_public((data[2] >> 51) & 1);
    Ciphertext ct_data185 = ctx.encrypt_public((data[2] >> 52) & 1);
    Ciphertext ct_data186 = ctx.encrypt_public((data[2] >> 53) & 1);
    Ciphertext ct_data187 = ctx.encrypt_public((data[2] >> 54) & 1);
    Ciphertext ct_data188 = ctx.encrypt_public((data[2] >> 55) & 1);
    Ciphertext ct_data189 = ctx.encrypt_public((data[2] >> 56) & 1);
    Ciphertext ct_data190 = ctx.encrypt_public((data[2] >> 57) & 1);
    Ciphertext ct_data192 = ctx.encrypt_public((data[2] >> 58) & 1);
    Ciphertext ct_data193 = ctx.encrypt_public((data[2] >> 59) & 1);
    Ciphertext ct_data194 = ctx.encrypt_public((data[2] >> 60) & 1);
    Ciphertext ct_data195 = ctx.encrypt_public((data[2] >> 61) & 1);
    Ciphertext ct_data196 = ctx.encrypt_public((data[2] >> 62) & 1);
    Ciphertext ct_data197 = ctx.encrypt_public((data[2] >> 63) & 1);
    Ciphertext ct_data198 = ctx.encrypt_public((data[3] >> 0) & 1);
    Ciphertext ct_data199 = ctx.encrypt_public((data[3] >> 1) & 1);
    Ciphertext ct_data200 = ctx.encrypt_public((data[3] >> 2) & 1);
    Ciphertext ct_data201 = ctx.encrypt_public((data[3] >> 3) & 1);
    Ciphertext ct_data202 = ctx.encrypt_public((data[3] >> 4) & 1);
    Ciphertext ct_data203 = ctx.encrypt_public((data[3] >> 5) & 1);
    Ciphertext ct_data204 = ctx.encrypt_public((data[3] >> 6) & 1);
    Ciphertext ct_data205 = ctx.encrypt_public((data[3] >> 7) & 1);
    Ciphertext ct_data206 = ctx.encrypt_public((data[3] >> 8) & 1);
    Ciphertext ct_data207 = ctx.encrypt_public((data[3] >> 9) & 1);
    Ciphertext ct_data208 = ctx.encrypt_public((data[3] >> 10) & 1);
    Ciphertext ct_data209 = ctx.encrypt_public((data[3] >> 11) & 1);
    Ciphertext ct_data210 = ctx.encrypt_public((data[3] >> 12) & 1);
    Ciphertext ct_data211 = ctx.encrypt_public((data[3] >> 13) & 1);
    Ciphertext ct_data212 = ctx.encrypt_public((data[3] >> 14) & 1);
    Ciphertext ct_data213 = ctx.encrypt_public((data[3] >> 15) & 1);
    Ciphertext ct_data214 = ctx.encrypt_public((data[3] >> 16) & 1);
    Ciphertext ct_data215 = ctx.encrypt_public((data[3] >> 17) & 1);
    Ciphertext ct_data216 = ctx.encrypt_public((data[3] >> 18) & 1);
    Ciphertext ct_data217 = ctx.encrypt_public((data[3] >> 19) & 1);
    Ciphertext ct_data218 = ctx.encrypt_public((data[3] >> 20) & 1);
    Ciphertext ct_data219 = ctx.encrypt_public((data[3] >> 21) & 1);
    Ciphertext ct_data220 = ctx.encrypt_public((data[3] >> 22) & 1);
    Ciphertext ct_data221 = ctx.encrypt_public((data[3] >> 23) & 1);
    Ciphertext ct_data222 = ctx.encrypt_public((data[3] >> 24) & 1);
    Ciphertext ct_data224 = ctx.encrypt_public((data[3] >> 25) & 1);
    Ciphertext ct_data225 = ctx.encrypt_public((data[3] >> 26) & 1);
    Ciphertext ct_data226 = ctx.encrypt_public((data[3] >> 27) & 1);
    Ciphertext ct_data227 = ctx.encrypt_public((data[3] >> 28) & 1);
    Ciphertext ct_data228 = ctx.encrypt_public((data[3] >> 29) & 1);
    Ciphertext ct_data229 = ctx.encrypt_public((data[3] >> 30) & 1);
    Ciphertext ct_data230 = ctx.encrypt_public((data[3] >> 31) & 1);
    Ciphertext ct_data231 = ctx.encrypt_public((data[3] >> 32) & 1);
    Ciphertext ct_data232 = ctx.encrypt_public((data[3] >> 33) & 1);
    Ciphertext ct_data233 = ctx.encrypt_public((data[3] >> 34) & 1);
    Ciphertext ct_data234 = ctx.encrypt_public((data[3] >> 35) & 1);
    Ciphertext ct_data235 = ctx.encrypt_public((data[3] >> 36) & 1);
    Ciphertext ct_data236 = ctx.encrypt_public((data[3] >> 37) & 1);
    Ciphertext ct_data237 = ctx.encrypt_public((data[3] >> 38) & 1);
    Ciphertext ct_data238 = ctx.encrypt_public((data[3] >> 39) & 1);
    Ciphertext ct_data239 = ctx.encrypt_public((data[3] >> 40) & 1);
    Ciphertext ct_data240 = ctx.encrypt_public((data[3] >> 41) & 1);
    Ciphertext ct_data241 = ctx.encrypt_public((data[3] >> 42) & 1);
    Ciphertext ct_data242 = ctx.encrypt_public((data[3] >> 43) & 1);
    Ciphertext ct_data243 = ctx.encrypt_public((data[3] >> 44) & 1);
    Ciphertext ct_data244 = ctx.encrypt_public((data[3] >> 45) & 1);
    Ciphertext ct_data245 = ctx.encrypt_public((data[3] >> 46) & 1);
    Ciphertext ct_data246 = ctx.encrypt_public((data[3] >> 47) & 1);
    Ciphertext ct_data247 = ctx.encrypt_public((data[3] >> 48) & 1);
    Ciphertext ct_data248 = ctx.encrypt_public((data[3] >> 49) & 1);
    Ciphertext ct_data249 = ctx.encrypt_public((data[3] >> 50) & 1);
    Ciphertext ct_data250 = ctx.encrypt_public((data[3] >> 51) & 1);
    Ciphertext ct_data251 = ctx.encrypt_public((data[3] >> 52) & 1);
    Ciphertext ct_data252 = ctx.encrypt_public((data[3] >> 53) & 1);
    Ciphertext ct_data253 = ctx.encrypt_public((data[3] >> 54) & 1);
    Ciphertext ct_data254 = ctx.encrypt_public((data[3] >> 55) & 1);

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
    Ciphertext gin0 = 0 + 1 * ct_data128 + 2 * ct_data129 + 1 * ct_data160 + 2 * ct_data161;
    std::vector<Ciphertext> gout0 = ctx.eval_lut_amortized(&gin0, decomp);

    std::cerr << "\rFA1    ";
    Ciphertext gin1 = 0 + 1 * ct_data192 + 2 * ct_data193 + 1 * ct_data224 + 2 * ct_data225;
    std::vector<Ciphertext> gout1 = ctx.eval_lut_amortized(&gin1, decomp);

    std::cerr << "\rFA2    ";
    Ciphertext gin2 = 0 + 1 * ct_data64 + 2 * ct_data65 + 1 * ct_data96 + 2 * ct_data97;
    std::vector<Ciphertext> gout2 = ctx.eval_lut_amortized(&gin2, decomp);

    std::cerr << "\rFA3    ";
    Ciphertext gin3 = gout0[2] + 1 * ct_data130 + 2 * ct_data131 + 1 * ct_data162 + 2 * ct_data163;
    std::vector<Ciphertext> gout3 = ctx.eval_lut_amortized(&gin3, decomp);

    std::cerr << "\rFA4    ";
    Ciphertext gin4 = 0 + 1 * ct_data0 + 2 * ct_data1 + 1 * ct_data32 + 2 * ct_data33;
    std::vector<Ciphertext> gout4 = ctx.eval_lut_amortized(&gin4, decomp);

    std::cerr << "\rFA5    ";
    Ciphertext gin5 = 0 + 1 * gout0[0] + 2 * gout0[1] + 1 * gout1[0] + 2 * gout1[1];
    std::vector<Ciphertext> gout5 = ctx.eval_lut_amortized(&gin5, decomp);

    std::cerr << "\rFA6    ";
    Ciphertext gin6 = gout1[2] + 1 * ct_data194 + 2 * ct_data195 + 1 * ct_data226 + 2 * ct_data227;
    std::vector<Ciphertext> gout6 = ctx.eval_lut_amortized(&gin6, decomp);

    std::cerr << "\rFA7    ";
    Ciphertext gin7 = gout4[2] + 1 * ct_data2 + 2 * ct_data3 + 1 * ct_data34 + 2 * ct_data35;
    std::vector<Ciphertext> gout7 = ctx.eval_lut_amortized(&gin7, decomp);

    std::cerr << "\rFA8    ";
    Ciphertext gin8 = gout5[2] + 1 * gout3[0] + 2 * gout3[1] + 1 * gout6[0] + 2 * gout6[1];
    std::vector<Ciphertext> gout8 = ctx.eval_lut_amortized(&gin8, decomp);

    std::cerr << "\rFA9    ";
    Ciphertext gin9 = gout2[2] + 1 * ct_data66 + 2 * ct_data67 + 1 * ct_data98 + 2 * ct_data99;
    std::vector<Ciphertext> gout9 = ctx.eval_lut_amortized(&gin9, decomp);

    std::cerr << "\rFA10    ";
    Ciphertext gin10 = gout3[2] + 1 * ct_data132 + 2 * ct_data133 + 1 * ct_data164 + 2 * ct_data165;
    std::vector<Ciphertext> gout10 = ctx.eval_lut_amortized(&gin10, decomp);

    std::cerr << "\rFA11    ";
    Ciphertext gin11 = gout9[2] + 1 * ct_data68 + 2 * ct_data69 + 1 * ct_data100 + 2 * ct_data101;
    std::vector<Ciphertext> gout11 = ctx.eval_lut_amortized(&gin11, decomp);

    std::cerr << "\rFA12    ";
    Ciphertext gin12 = 0 + 1 * gout4[0] + 2 * gout4[1] + 1 * gout2[0] + 2 * gout2[1];
    std::vector<Ciphertext> gout12 = ctx.eval_lut_amortized(&gin12, decomp);

    std::cerr << "\rFA13    ";
    Ciphertext gin13 = gout6[2] + 1 * ct_data196 + 2 * ct_data197 + 1 * ct_data228 + 2 * ct_data229;
    std::vector<Ciphertext> gout13 = ctx.eval_lut_amortized(&gin13, decomp);

    std::cerr << "\rFA14    ";
    Ciphertext gin14 = gout10[2] + 1 * ct_data134 + 2 * ct_data135 + 1 * ct_data166 + 2 * ct_data167;
    std::vector<Ciphertext> gout14 = ctx.eval_lut_amortized(&gin14, decomp);

    std::cerr << "\rFA15    ";
    Ciphertext gin15 = gout13[2] + 1 * ct_data198 + 2 * ct_data199 + 1 * ct_data230 + 2 * ct_data231;
    std::vector<Ciphertext> gout15 = ctx.eval_lut_amortized(&gin15, decomp);

    std::cerr << "\rFA16    ";
    Ciphertext gin16 = gout14[2] + 1 * ct_data136 + 2 * ct_data137 + 1 * ct_data168 + 2 * ct_data169;
    std::vector<Ciphertext> gout16 = ctx.eval_lut_amortized(&gin16, decomp);

    std::cerr << "\rFA17    ";
    Ciphertext gin17 = gout12[2] + 1 * gout7[0] + 2 * gout7[1] + 1 * gout9[0] + 2 * gout9[1];
    std::vector<Ciphertext> gout17 = ctx.eval_lut_amortized(&gin17, decomp);

    std::cerr << "\rFA18    ";
    Ciphertext gin18 = gout15[2] + 1 * ct_data200 + 2 * ct_data201 + 1 * ct_data232 + 2 * ct_data233;
    std::vector<Ciphertext> gout18 = ctx.eval_lut_amortized(&gin18, decomp);

    std::cerr << "\rFA19    ";
    Ciphertext gin19 = gout16[2] + 1 * ct_data138 + 2 * ct_data139 + 1 * ct_data170 + 2 * ct_data171;
    std::vector<Ciphertext> gout19 = ctx.eval_lut_amortized(&gin19, decomp);

    std::cerr << "\rFA20    ";
    Ciphertext gin20 = gout11[2] + 1 * ct_data70 + 2 * ct_data71 + 1 * ct_data102 + 2 * ct_data103;
    std::vector<Ciphertext> gout20 = ctx.eval_lut_amortized(&gin20, decomp);

    std::cerr << "\rFA21    ";
    Ciphertext gin21 = 0 + 1 * gout12[0] + 2 * gout12[1] + 1 * gout5[0] + 2 * gout5[1];
    std::vector<Ciphertext> gout21 = ctx.eval_lut_amortized(&gin21, decomp);

    std::cerr << "\rFA22    ";
    Ciphertext gin22 = gout8[2] + 1 * gout10[0] + 2 * gout10[1] + 1 * gout13[0] + 2 * gout13[1];
    std::vector<Ciphertext> gout22 = ctx.eval_lut_amortized(&gin22, decomp);

    std::cerr << "\rFA23    ";
    Ciphertext gin23 = gout18[2] + 1 * ct_data202 + 2 * ct_data203 + 1 * ct_data234 + 2 * ct_data235;
    std::vector<Ciphertext> gout23 = ctx.eval_lut_amortized(&gin23, decomp);

    std::cerr << "\rFA24    ";
    Ciphertext gin24 = gout20[2] + 1 * ct_data72 + 2 * ct_data73 + 1 * ct_data104 + 2 * ct_data105;
    std::vector<Ciphertext> gout24 = ctx.eval_lut_amortized(&gin24, decomp);

    std::cerr << "\rFA25    ";
    Ciphertext gin25 = gout23[2] + 1 * ct_data204 + 2 * ct_data205 + 1 * ct_data236 + 2 * ct_data237;
    std::vector<Ciphertext> gout25 = ctx.eval_lut_amortized(&gin25, decomp);

    std::cerr << "\rFA26    ";
    Ciphertext gin26 = gout7[2] + 1 * ct_data4 + 2 * ct_data5 + 1 * ct_data36 + 2 * ct_data37;
    std::vector<Ciphertext> gout26 = ctx.eval_lut_amortized(&gin26, decomp);

    std::cerr << "\rFA27    ";
    Ciphertext gin27 = gout21[2] + 1 * gout17[0] + 2 * gout17[1] + 1 * gout8[0] + 2 * gout8[1];
    std::vector<Ciphertext> gout27 = ctx.eval_lut_amortized(&gin27, decomp);

    std::cerr << "\rFA28    ";
    Ciphertext gin28 = gout19[2] + 1 * ct_data140 + 2 * ct_data141 + 1 * ct_data172 + 2 * ct_data173;
    std::vector<Ciphertext> gout28 = ctx.eval_lut_amortized(&gin28, decomp);

    std::cerr << "\rFA29    ";
    Ciphertext gin29 = gout22[2] + 1 * gout14[0] + 2 * gout14[1] + 1 * gout15[0] + 2 * gout15[1];
    std::vector<Ciphertext> gout29 = ctx.eval_lut_amortized(&gin29, decomp);

    std::cerr << "\rFA30    ";
    Ciphertext gin30 = gout24[2] + 1 * ct_data74 + 2 * ct_data75 + 1 * ct_data106 + 2 * ct_data107;
    std::vector<Ciphertext> gout30 = ctx.eval_lut_amortized(&gin30, decomp);

    std::cerr << "\rFA31    ";
    Ciphertext gin31 = gout26[2] + 1 * ct_data6 + 2 * ct_data7 + 1 * ct_data38 + 2 * ct_data39;
    std::vector<Ciphertext> gout31 = ctx.eval_lut_amortized(&gin31, decomp);

    std::cerr << "\rFA32    ";
    Ciphertext gin32 = gout25[2] + 1 * ct_data206 + 2 * ct_data207 + 1 * ct_data238 + 2 * ct_data239;
    std::vector<Ciphertext> gout32 = ctx.eval_lut_amortized(&gin32, decomp);

    std::cerr << "\rFA33    ";
    Ciphertext gin33 = gout28[2] + 1 * ct_data142 + 2 * ct_data143 + 1 * ct_data174 + 2 * ct_data175;
    std::vector<Ciphertext> gout33 = ctx.eval_lut_amortized(&gin33, decomp);

    std::cerr << "\rFA34    ";
    Ciphertext gin34 = gout29[2] + 1 * gout16[0] + 2 * gout16[1] + 1 * gout18[0] + 2 * gout18[1];
    std::vector<Ciphertext> gout34 = ctx.eval_lut_amortized(&gin34, decomp);

    std::cerr << "\rFA35    ";
    Ciphertext gin35 = gout31[2] + 1 * ct_data8 + 2 * ct_data9 + 1 * ct_data40 + 2 * ct_data41;
    std::vector<Ciphertext> gout35 = ctx.eval_lut_amortized(&gin35, decomp);

    std::cerr << "\rFA36    ";
    Ciphertext gin36 = gout35[2] + 1 * ct_data10 + 2 * ct_data11 + 1 * ct_data42 + 2 * ct_data43;
    std::vector<Ciphertext> gout36 = ctx.eval_lut_amortized(&gin36, decomp);

    std::cerr << "\rFA37    ";
    Ciphertext gin37 = gout17[2] + 1 * gout26[0] + 2 * gout26[1] + 1 * gout11[0] + 2 * gout11[1];
    std::vector<Ciphertext> gout37 = ctx.eval_lut_amortized(&gin37, decomp);

    std::cerr << "\rFA38    ";
    Ciphertext gin38 = gout32[2] + 1 * ct_data208 + 2 * ct_data209 + 1 * ct_data240 + 2 * ct_data241;
    std::vector<Ciphertext> gout38 = ctx.eval_lut_amortized(&gin38, decomp);

    std::cerr << "\rFA39    ";
    Ciphertext gin39 = gout30[2] + 1 * ct_data76 + 2 * ct_data77 + 1 * ct_data108 + 2 * ct_data109;
    std::vector<Ciphertext> gout39 = ctx.eval_lut_amortized(&gin39, decomp);

    std::cerr << "\rFA40    ";
    Ciphertext gin40 = gout38[2] + 1 * ct_data210 + 2 * ct_data211 + 1 * ct_data242 + 2 * ct_data243;
    std::vector<Ciphertext> gout40 = ctx.eval_lut_amortized(&gin40, decomp);

    std::cerr << "\rFA41    ";
    Ciphertext gin41 = gout39[2] + 1 * ct_data78 + 2 * ct_data79 + 1 * ct_data110 + 2 * ct_data111;
    std::vector<Ciphertext> gout41 = ctx.eval_lut_amortized(&gin41, decomp);

    std::cerr << "\rFA42    ";
    Ciphertext gin42 = gout34[2] + 1 * gout19[0] + 2 * gout19[1] + 1 * gout23[0] + 2 * gout23[1];
    std::vector<Ciphertext> gout42 = ctx.eval_lut_amortized(&gin42, decomp);

    std::cerr << "\rFA43    ";
    Ciphertext gin43 = gout33[2] + 1 * ct_data144 + 2 * ct_data145 + 1 * ct_data176 + 2 * ct_data177;
    std::vector<Ciphertext> gout43 = ctx.eval_lut_amortized(&gin43, decomp);

    std::cerr << "\rFA44    ";
    Ciphertext gin44 = gout37[2] + 1 * gout31[0] + 2 * gout31[1] + 1 * gout20[0] + 2 * gout20[1];
    std::vector<Ciphertext> gout44 = ctx.eval_lut_amortized(&gin44, decomp);

    std::cerr << "\rFA45    ";
    Ciphertext gin45 = gout43[2] + 1 * ct_data146 + 2 * ct_data147 + 1 * ct_data178 + 2 * ct_data179;
    std::vector<Ciphertext> gout45 = ctx.eval_lut_amortized(&gin45, decomp);

    std::cerr << "\rFA46    ";
    Ciphertext gin46 = gout36[2] + 1 * ct_data12 + 2 * ct_data13 + 1 * ct_data44 + 2 * ct_data45;
    std::vector<Ciphertext> gout46 = ctx.eval_lut_amortized(&gin46, decomp);

    std::cerr << "\rFA47    ";
    Ciphertext gin47 = gout41[2] + 1 * ct_data80 + 2 * ct_data81 + 1 * ct_data112 + 2 * ct_data113;
    std::vector<Ciphertext> gout47 = ctx.eval_lut_amortized(&gin47, decomp);

    std::cerr << "\rFA48    ";
    Ciphertext gin48 = gout44[2] + 1 * gout35[0] + 2 * gout35[1] + 1 * gout24[0] + 2 * gout24[1];
    std::vector<Ciphertext> gout48 = ctx.eval_lut_amortized(&gin48, decomp);

    std::cerr << "\rFA49    ";
    Ciphertext gin49 = gout48[2] + 1 * gout36[0] + 2 * gout36[1] + 1 * gout30[0] + 2 * gout30[1];
    std::vector<Ciphertext> gout49 = ctx.eval_lut_amortized(&gin49, decomp);

    std::cerr << "\rFA50    ";
    Ciphertext gin50 = gout27[2] + 1 * gout37[0] + 2 * gout37[1] + 1 * gout22[0] + 2 * gout22[1];
    std::vector<Ciphertext> gout50 = ctx.eval_lut_amortized(&gin50, decomp);

    std::cerr << "\rFA51    ";
    Ciphertext gin51 = gout40[2] + 1 * ct_data212 + 2 * ct_data213 + 1 * ct_data244 + 2 * ct_data245;
    std::vector<Ciphertext> gout51 = ctx.eval_lut_amortized(&gin51, decomp);

    std::cerr << "\rFA52    ";
    Ciphertext gin52 = gout49[2] + 1 * gout46[0] + 2 * gout46[1] + 1 * gout39[0] + 2 * gout39[1];
    std::vector<Ciphertext> gout52 = ctx.eval_lut_amortized(&gin52, decomp);

    std::cerr << "\rFA53    ";
    Ciphertext gin53 = gout50[2] + 1 * gout44[0] + 2 * gout44[1] + 1 * gout29[0] + 2 * gout29[1];
    std::vector<Ciphertext> gout53 = ctx.eval_lut_amortized(&gin53, decomp);

    std::cerr << "\rFA54    ";
    Ciphertext gin54 = gout51[2] + 1 * ct_data214 + 2 * ct_data215 + 1 * ct_data246 + 2 * ct_data247;
    std::vector<Ciphertext> gout54 = ctx.eval_lut_amortized(&gin54, decomp);

    std::cerr << "\rFA55    ";
    Ciphertext gin55 = gout42[2] + 1 * gout28[0] + 2 * gout28[1] + 1 * gout25[0] + 2 * gout25[1];
    std::vector<Ciphertext> gout55 = ctx.eval_lut_amortized(&gin55, decomp);

    std::cerr << "\rFA56    ";
    Ciphertext gin56 = gout55[2] + 1 * gout33[0] + 2 * gout33[1] + 1 * gout32[0] + 2 * gout32[1];
    std::vector<Ciphertext> gout56 = ctx.eval_lut_amortized(&gin56, decomp);

    std::cerr << "\rFA57    ";
    Ciphertext gin57 = gout46[2] + 1 * ct_data14 + 2 * ct_data15 + 1 * ct_data46 + 2 * ct_data47;
    std::vector<Ciphertext> gout57 = ctx.eval_lut_amortized(&gin57, decomp);

    std::cerr << "\rFA58    ";
    Ciphertext gin58 = gout47[2] + 1 * ct_data82 + 2 * ct_data83 + 1 * ct_data114 + 2 * ct_data115;
    std::vector<Ciphertext> gout58 = ctx.eval_lut_amortized(&gin58, decomp);

    std::cerr << "\rFA59    ";
    Ciphertext gin59 = gout57[2] + 1 * ct_data16 + 2 * ct_data17 + 1 * ct_data48 + 2 * ct_data49;
    std::vector<Ciphertext> gout59 = ctx.eval_lut_amortized(&gin59, decomp);

    std::cerr << "\rFA60    ";
    Ciphertext gin60 = gout45[2] + 1 * ct_data148 + 2 * ct_data149 + 1 * ct_data180 + 2 * ct_data181;
    std::vector<Ciphertext> gout60 = ctx.eval_lut_amortized(&gin60, decomp);

    std::cerr << "\rFA61    ";
    Ciphertext gin61 = gout56[2] + 1 * gout43[0] + 2 * gout43[1] + 1 * gout38[0] + 2 * gout38[1];
    std::vector<Ciphertext> gout61 = ctx.eval_lut_amortized(&gin61, decomp);

    std::cerr << "\rFA62    ";
    Ciphertext gin62 = gout53[2] + 1 * gout48[0] + 2 * gout48[1] + 1 * gout34[0] + 2 * gout34[1];
    std::vector<Ciphertext> gout62 = ctx.eval_lut_amortized(&gin62, decomp);

    std::cerr << "\rFA63    ";
    Ciphertext gin63 = gout59[2] + 1 * ct_data18 + 2 * ct_data19 + 1 * ct_data50 + 2 * ct_data51;
    std::vector<Ciphertext> gout63 = ctx.eval_lut_amortized(&gin63, decomp);

    std::cerr << "\rFA64    ";
    Ciphertext gin64 = gout60[2] + 1 * ct_data150 + 2 * ct_data151 + 1 * ct_data182 + 2 * ct_data183;
    std::vector<Ciphertext> gout64 = ctx.eval_lut_amortized(&gin64, decomp);

    std::cerr << "\rFA65    ";
    Ciphertext gin65 = gout64[2] + 1 * ct_data152 + 2 * ct_data153 + 1 * ct_data184 + 2 * ct_data185;
    std::vector<Ciphertext> gout65 = ctx.eval_lut_amortized(&gin65, decomp);

    std::cerr << "\rFA66    ";
    Ciphertext gin66 = gout54[2] + 1 * ct_data216 + 2 * ct_data217 + 1 * ct_data248 + 2 * ct_data249;
    std::vector<Ciphertext> gout66 = ctx.eval_lut_amortized(&gin66, decomp);

    std::cerr << "\rFA67    ";
    Ciphertext gin67 = gout65[2] + 1 * ct_data154 + 2 * ct_data155 + 1 * ct_data186 + 2 * ct_data187;
    std::vector<Ciphertext> gout67 = ctx.eval_lut_amortized(&gin67, decomp);

    std::cerr << "\rFA68    ";
    Ciphertext gin68 = gout58[2] + 1 * ct_data84 + 2 * ct_data85 + 1 * ct_data116 + 2 * ct_data117;
    std::vector<Ciphertext> gout68 = ctx.eval_lut_amortized(&gin68, decomp);

    std::cerr << "\rFA69    ";
    Ciphertext gin69 = gout67[2] + 1 * ct_data156 + 2 * ct_data157 + 1 * ct_data188 + 2 * ct_data189;
    std::vector<Ciphertext> gout69 = ctx.eval_lut_amortized(&gin69, decomp);

    std::cerr << "\rFA70    ";
    Ciphertext gin70 = gout62[2] + 1 * gout49[0] + 2 * gout49[1] + 1 * gout42[0] + 2 * gout42[1];
    std::vector<Ciphertext> gout70 = ctx.eval_lut_amortized(&gin70, decomp);

    std::cerr << "\rFA71    ";
    Ciphertext gin71 = gout52[2] + 1 * gout57[0] + 2 * gout57[1] + 1 * gout41[0] + 2 * gout41[1];
    std::vector<Ciphertext> gout71 = ctx.eval_lut_amortized(&gin71, decomp);

    std::cerr << "\rFA72    ";
    Ciphertext gin72 = gout63[2] + 1 * ct_data20 + 2 * ct_data21 + 1 * ct_data52 + 2 * ct_data53;
    std::vector<Ciphertext> gout72 = ctx.eval_lut_amortized(&gin72, decomp);

    std::cerr << "\rFA73    ";
    Ciphertext gin73 = gout61[2] + 1 * gout45[0] + 2 * gout45[1] + 1 * gout40[0] + 2 * gout40[1];
    std::vector<Ciphertext> gout73 = ctx.eval_lut_amortized(&gin73, decomp);

    std::cerr << "\rFA74    ";
    Ciphertext gin74 = gout70[2] + 1 * gout52[0] + 2 * gout52[1] + 1 * gout55[0] + 2 * gout55[1];
    std::vector<Ciphertext> gout74 = ctx.eval_lut_amortized(&gin74, decomp);

    std::cerr << "\rFA75    ";
    Ciphertext gin75 = gout68[2] + 1 * ct_data86 + 2 * ct_data87 + 1 * ct_data118 + 2 * ct_data119;
    std::vector<Ciphertext> gout75 = ctx.eval_lut_amortized(&gin75, decomp);

    std::cerr << "\rFA76    ";
    Ciphertext gin76 = gout69[2] + 1 * ct_data158 + 1 * ct_data190;
    std::vector<Ciphertext> gout76 = ctx.eval_lut_amortized(&gin76, decomp);

    std::cerr << "\rFA77    ";
    Ciphertext gin77 = gout73[2] + 1 * gout60[0] + 2 * gout60[1] + 1 * gout51[0] + 2 * gout51[1];
    std::vector<Ciphertext> gout77 = ctx.eval_lut_amortized(&gin77, decomp);

    std::cerr << "\rFA78    ";
    Ciphertext gin78 = gout71[2] + 1 * gout59[0] + 2 * gout59[1] + 1 * gout47[0] + 2 * gout47[1];
    std::vector<Ciphertext> gout78 = ctx.eval_lut_amortized(&gin78, decomp);

    std::cerr << "\rFA79    ";
    Ciphertext gin79 = gout66[2] + 1 * ct_data218 + 2 * ct_data219 + 1 * ct_data250 + 2 * ct_data251;
    std::vector<Ciphertext> gout79 = ctx.eval_lut_amortized(&gin79, decomp);

    std::cerr << "\rFA80    ";
    Ciphertext gin80 = gout78[2] + 1 * gout63[0] + 2 * gout63[1] + 1 * gout58[0] + 2 * gout58[1];
    std::vector<Ciphertext> gout80 = ctx.eval_lut_amortized(&gin80, decomp);

    std::cerr << "\rFA81    ";
    Ciphertext gin81 = gout72[2] + 1 * ct_data22 + 2 * ct_data23 + 1 * ct_data54 + 2 * ct_data55;
    std::vector<Ciphertext> gout81 = ctx.eval_lut_amortized(&gin81, decomp);

    std::cerr << "\rFA82    ";
    Ciphertext gin82 = gout74[2] + 1 * gout71[0] + 2 * gout71[1] + 1 * gout56[0] + 2 * gout56[1];
    std::vector<Ciphertext> gout82 = ctx.eval_lut_amortized(&gin82, decomp);

    std::cerr << "\rFA83    ";
    Ciphertext gin83 = gout82[2] + 1 * gout78[0] + 2 * gout78[1] + 1 * gout61[0] + 2 * gout61[1];
    std::vector<Ciphertext> gout83 = ctx.eval_lut_amortized(&gin83, decomp);

    std::cerr << "\rFA84    ";
    Ciphertext gin84 = gout75[2] + 1 * ct_data88 + 2 * ct_data89 + 1 * ct_data120 + 2 * ct_data121;
    std::vector<Ciphertext> gout84 = ctx.eval_lut_amortized(&gin84, decomp);

    std::cerr << "\rFA85    ";
    Ciphertext gin85 = gout77[2] + 1 * gout64[0] + 2 * gout64[1] + 1 * gout54[0] + 2 * gout54[1];
    std::vector<Ciphertext> gout85 = ctx.eval_lut_amortized(&gin85, decomp);

    std::cerr << "\rFA86    ";
    Ciphertext gin86 = gout83[2] + 1 * gout80[0] + 2 * gout80[1] + 1 * gout73[0] + 2 * gout73[1];
    std::vector<Ciphertext> gout86 = ctx.eval_lut_amortized(&gin86, decomp);

    std::cerr << "\rFA87    ";
    Ciphertext gin87 = gout81[2] + 1 * ct_data24 + 2 * ct_data25 + 1 * ct_data56 + 2 * ct_data57;
    std::vector<Ciphertext> gout87 = ctx.eval_lut_amortized(&gin87, decomp);

    std::cerr << "\rFA88    ";
    Ciphertext gin88 = gout85[2] + 1 * gout65[0] + 2 * gout65[1] + 1 * gout66[0] + 2 * gout66[1];
    std::vector<Ciphertext> gout88 = ctx.eval_lut_amortized(&gin88, decomp);

    std::cerr << "\rFA89    ";
    Ciphertext gin89 = gout80[2] + 1 * gout72[0] + 2 * gout72[1] + 1 * gout68[0] + 2 * gout68[1];
    std::vector<Ciphertext> gout89 = ctx.eval_lut_amortized(&gin89, decomp);

    std::cerr << "\rFA90    ";
    Ciphertext gin90 = gout79[2] + 1 * ct_data220 + 2 * ct_data221 + 1 * ct_data252 + 2 * ct_data253;
    std::vector<Ciphertext> gout90 = ctx.eval_lut_amortized(&gin90, decomp);

    std::cerr << "\rFA91    ";
    Ciphertext gin91 = gout90[2] + 1 * ct_data222 + 1 * ct_data254;
    std::vector<Ciphertext> gout91 = ctx.eval_lut_amortized(&gin91, decomp);

    std::cerr << "\rFA92    ";
    Ciphertext gin92 = gout84[2] + 1 * ct_data90 + 2 * ct_data91 + 1 * ct_data122 + 2 * ct_data123;
    std::vector<Ciphertext> gout92 = ctx.eval_lut_amortized(&gin92, decomp);

    std::cerr << "\rFA93    ";
    Ciphertext gin93 = gout88[2] + 1 * gout67[0] + 2 * gout67[1] + 1 * gout79[0] + 2 * gout79[1];
    std::vector<Ciphertext> gout93 = ctx.eval_lut_amortized(&gin93, decomp);

    std::cerr << "\rFA94    ";
    Ciphertext gin94 = gout87[2] + 1 * ct_data26 + 2 * ct_data27 + 1 * ct_data58 + 2 * ct_data59;
    std::vector<Ciphertext> gout94 = ctx.eval_lut_amortized(&gin94, decomp);

    std::cerr << "\rFA95    ";
    Ciphertext gin95 = gout89[2] + 1 * gout81[0] + 2 * gout81[1] + 1 * gout75[0] + 2 * gout75[1];
    std::vector<Ciphertext> gout95 = ctx.eval_lut_amortized(&gin95, decomp);

    std::cerr << "\rFA96    ";
    Ciphertext gin96 = gout86[2] + 1 * gout89[0] + 2 * gout89[1] + 1 * gout77[0] + 2 * gout77[1];
    std::vector<Ciphertext> gout96 = ctx.eval_lut_amortized(&gin96, decomp);

    std::cerr << "\rFA97    ";
    Ciphertext gin97 = gout94[2] + 1 * ct_data28 + 2 * ct_data29 + 1 * ct_data60 + 2 * ct_data61;
    std::vector<Ciphertext> gout97 = ctx.eval_lut_amortized(&gin97, decomp);

    std::cerr << "\rFA98    ";
    Ciphertext gin98 = gout93[2] + 1 * gout69[0] + 2 * gout69[1] + 1 * gout90[0] + 2 * gout90[1];
    std::vector<Ciphertext> gout98 = ctx.eval_lut_amortized(&gin98, decomp);

    std::cerr << "\rFA99    ";
    Ciphertext gin99 = gout92[2] + 1 * ct_data92 + 2 * ct_data93 + 1 * ct_data124 + 2 * ct_data125;
    std::vector<Ciphertext> gout99 = ctx.eval_lut_amortized(&gin99, decomp);

    std::cerr << "\rFA100    ";
    Ciphertext gin100 = gout97[2] + 1 * ct_data30 + 1 * ct_data62;
    std::vector<Ciphertext> gout100 = ctx.eval_lut_amortized(&gin100, decomp);

    std::cerr << "\rFA101    ";
    Ciphertext gin101 = gout95[2] + 1 * gout87[0] + 2 * gout87[1] + 1 * gout84[0] + 2 * gout84[1];
    std::vector<Ciphertext> gout101 = ctx.eval_lut_amortized(&gin101, decomp);

    std::cerr << "\rFA102    ";
    Ciphertext gin102 = gout99[2] + 1 * ct_data94 + 1 * ct_data126;
    std::vector<Ciphertext> gout102 = ctx.eval_lut_amortized(&gin102, decomp);

    std::cerr << "\rFA103    ";
    Ciphertext gin103 = gout98[2] + 1 * gout76[0] + 1 * gout91[0];
    std::vector<Ciphertext> gout103 = ctx.eval_lut_amortized(&gin103, decomp);

    std::cerr << "\rFA104    ";
    Ciphertext gin104 = gout96[2] + 1 * gout95[0] + 2 * gout95[1] + 1 * gout85[0] + 2 * gout85[1];
    std::vector<Ciphertext> gout104 = ctx.eval_lut_amortized(&gin104, decomp);

    std::cerr << "\rFA105    ";
    Ciphertext gin105 = gout101[2] + 1 * gout94[0] + 2 * gout94[1] + 1 * gout92[0] + 2 * gout92[1];
    std::vector<Ciphertext> gout105 = ctx.eval_lut_amortized(&gin105, decomp);

    std::cerr << "\rFA106    ";
    Ciphertext gin106 = gout105[2] + 1 * gout97[0] + 2 * gout97[1] + 1 * gout99[0] + 2 * gout99[1];
    std::vector<Ciphertext> gout106 = ctx.eval_lut_amortized(&gin106, decomp);

    std::cerr << "\rFA107    ";
    Ciphertext gin107 = gout104[2] + 1 * gout101[0] + 2 * gout101[1] + 1 * gout88[0] + 2 * gout88[1];
    std::vector<Ciphertext> gout107 = ctx.eval_lut_amortized(&gin107, decomp);

    std::cerr << "\rFA108    ";
    Ciphertext gin108 = gout106[2] + 1 * gout100[0] + 1 * gout102[0];
    std::vector<Ciphertext> gout108 = ctx.eval_lut_amortized(&gin108, decomp);

    std::cerr << "\rFA109    ";
    Ciphertext gin109 = gout107[2] + 1 * gout105[0] + 2 * gout105[1] + 1 * gout93[0] + 2 * gout93[1];
    std::vector<Ciphertext> gout109 = ctx.eval_lut_amortized(&gin109, decomp);

    std::cerr << "\rFA110    ";
    Ciphertext gin110 = gout109[2] + 1 * gout106[0] + 2 * gout106[1] + 1 * gout98[0] + 2 * gout98[1];
    std::vector<Ciphertext> gout110 = ctx.eval_lut_amortized(&gin110, decomp);

    std::cerr << "\rFA111    ";
    Ciphertext gin111 = gout110[2] + 1 * gout108[0] + 1 * gout103[0];
    std::vector<Ciphertext> gout111 = ctx.eval_lut_amortized(&gin111, decomp);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(0); /* out0 */
    test_out.push_back(ctx.decrypt(&gout21[0])); /* out1 */
    test_out.push_back(ctx.decrypt(&gout21[1])); /* out2 */
    test_out.push_back(ctx.decrypt(&gout27[0])); /* out3 */
    test_out.push_back(ctx.decrypt(&gout27[1])); /* out4 */
    test_out.push_back(ctx.decrypt(&gout50[0])); /* out5 */
    test_out.push_back(ctx.decrypt(&gout50[1])); /* out6 */
    test_out.push_back(ctx.decrypt(&gout53[0])); /* out7 */
    test_out.push_back(ctx.decrypt(&gout53[1])); /* out8 */
    test_out.push_back(ctx.decrypt(&gout62[0])); /* out9 */
    test_out.push_back(ctx.decrypt(&gout62[1])); /* out10 */
    test_out.push_back(ctx.decrypt(&gout70[0])); /* out11 */
    test_out.push_back(ctx.decrypt(&gout70[1])); /* out12 */
    test_out.push_back(ctx.decrypt(&gout74[0])); /* out13 */
    test_out.push_back(ctx.decrypt(&gout74[1])); /* out14 */
    test_out.push_back(ctx.decrypt(&gout82[0])); /* out15 */
    test_out.push_back(ctx.decrypt(&gout82[1])); /* out16 */
    test_out.push_back(ctx.decrypt(&gout83[0])); /* out17 */
    test_out.push_back(ctx.decrypt(&gout83[1])); /* out18 */
    test_out.push_back(ctx.decrypt(&gout86[0])); /* out19 */
    test_out.push_back(ctx.decrypt(&gout86[1])); /* out20 */
    test_out.push_back(ctx.decrypt(&gout96[0])); /* out21 */
    test_out.push_back(ctx.decrypt(&gout96[1])); /* out22 */
    test_out.push_back(ctx.decrypt(&gout104[0])); /* out23 */
    test_out.push_back(ctx.decrypt(&gout104[1])); /* out24 */
    test_out.push_back(ctx.decrypt(&gout107[0])); /* out25 */
    test_out.push_back(ctx.decrypt(&gout107[1])); /* out26 */
    test_out.push_back(ctx.decrypt(&gout109[0])); /* out27 */
    test_out.push_back(ctx.decrypt(&gout109[1])); /* out28 */
    test_out.push_back(ctx.decrypt(&gout110[0])); /* out29 */
    test_out.push_back(ctx.decrypt(&gout110[1])); /* out30 */
    test_out.push_back(ctx.decrypt(&gout111[0])); /* out31 */
    return test_out;
}

static void
BM_structs_3d_lut3fa(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(tfhe_11_NTT_amortized);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(8);

    for (auto _ : state) {
        test_structs_3d_lut3fa(ctx);
    }
}

BENCHMARK(BM_structs_3d_lut3fa)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
