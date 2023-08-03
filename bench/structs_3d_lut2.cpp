#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_structs_3d_lut2(FHEContext& ctx, std::vector<uint64_t> data = { 0 })
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
        /* GATE 70 (LUT2 _3206_ INIT 0x6 PERM 01) */
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
        /* GATE 121 (LUT2 _3257_ INIT 0x8 PERM 01) */
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
    Ciphertext gin0 = 1 * ct_data99 + 2 * ct_data131;
    std::vector<Ciphertext> gout0 = ctx.eval_lut_amortized(&gin0, lut0);

    std::vector<RotationPoly> lut1;
    std::vector<long (*)(long)> flut1;
    auto lut1idx0 = [](long I) -> long {
        /* GATE 722 (LUT2 _3858_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut1.push_back(ctx.genrate_lut(lut1idx0));
    flut1.push_back(lut1idx0);
    auto lut1idx1 = [](long I) -> long {
        /* GATE 757 (LUT2 _3893_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin1 = 1 * ct_data21 + 2 * ct_data53;
    std::vector<Ciphertext> gout1 = ctx.eval_lut_amortized(&gin1, lut1);

    std::vector<RotationPoly> lut2;
    std::vector<long (*)(long)> flut2;
    auto lut2idx0 = [](long I) -> long {
        /* GATE 406 (LUT2 _3542_ INIT 0x8 PERM 01) */
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
        /* GATE 364 (LUT2 _3500_ INIT 0x6 PERM 01) */
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
    Ciphertext gin2 = 1 * ct_data107 + 2 * ct_data139;
    std::vector<Ciphertext> gout2 = ctx.eval_lut_amortized(&gin2, lut2);

    std::vector<RotationPoly> lut3;
    std::vector<long (*)(long)> flut3;
    auto lut3idx0 = [](long I) -> long {
        /* GATE 1006 (LUT2 _4142_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut3.push_back(ctx.genrate_lut(lut3idx0));
    flut3.push_back(lut3idx0);
    auto lut3idx1 = [](long I) -> long {
        /* GATE 973 (LUT2 _4109_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin3 = 1 * ct_data28 + 2 * ct_data60;
    std::vector<Ciphertext> gout3 = ctx.eval_lut_amortized(&gin3, lut3);

    std::vector<RotationPoly> lut4;
    std::vector<long (*)(long)> flut4;
    auto lut4idx0 = [](long I) -> long {
        /* GATE 149 (LUT2 _3285_ INIT 0x6 PERM 01) */
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
        /* GATE 182 (LUT2 _3318_ INIT 0x8 PERM 01) */
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
    Ciphertext gin4 = 1 * ct_data5 + 2 * ct_data37;
    std::vector<Ciphertext> gout4 = ctx.eval_lut_amortized(&gin4, lut4);

    std::vector<RotationPoly> lut5;
    std::vector<long (*)(long)> flut5;
    auto lut5idx0 = [](long I) -> long {
        /* GATE 1040 (LUT2 _4176_ INIT 0x8 PERM 01) */
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
        /* GATE 1010 (LUT2 _4146_ INIT 0x6 PERM 01) */
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
    Ciphertext gin5 = 1 * ct_data125 + 2 * ct_data157;
    std::vector<Ciphertext> gout5 = ctx.eval_lut_amortized(&gin5, lut5);

    std::vector<RotationPoly> lut6;
    std::vector<long (*)(long)> flut6;
    auto lut6idx0 = [](long I) -> long {
        /* GATE 47 (LUT2 _3183_ INIT 0x8 PERM 01) */
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
        /* GATE 18 (LUT2 _3154_ INIT 0x6 PERM 01) */
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
    Ciphertext gin6 = 1 * ct_data97 + 2 * ct_data129;
    std::vector<Ciphertext> gout6 = ctx.eval_lut_amortized(&gin6, lut6);

    std::vector<RotationPoly> lut7;
    std::vector<long (*)(long)> flut7;
    auto lut7idx0 = [](long I) -> long {
        /* GATE 972 (LUT2 _4108_ INIT 0x6 PERM 01) */
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
        /* GATE 1005 (LUT2 _4141_ INIT 0x8 PERM 01) */
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
    Ciphertext gin7 = 1 * gout3[1] + 2 * ct_data92;
    std::vector<Ciphertext> gout7 = ctx.eval_lut_amortized(&gin7, lut7);

    std::vector<RotationPoly> lut8;
    std::vector<long (*)(long)> flut8;
    auto lut8idx0 = [](long I) -> long {
        /* GATE 401 (LUT2 _3537_ INIT 0x6 PERM 01) */
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
        /* GATE 441 (LUT2 _3577_ INIT 0x8 PERM 01) */
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
    Ciphertext gin8 = 1 * ct_data108 + 2 * ct_data140;
    std::vector<Ciphertext> gout8 = ctx.eval_lut_amortized(&gin8, lut8);

    std::vector<RotationPoly> lut9;
    std::vector<long (*)(long)> flut9;
    auto lut9idx0 = [](long I) -> long {
        /* GATE 652 (LUT2 _3788_ INIT 0x6 PERM 01) */
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
        /* GATE 694 (LUT2 _3830_ INIT 0x8 PERM 01) */
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
    Ciphertext gin9 = 1 * ct_data115 + 2 * ct_data147;
    std::vector<Ciphertext> gout9 = ctx.eval_lut_amortized(&gin9, lut9);

    std::vector<RotationPoly> lut10;
    std::vector<long (*)(long)> flut10;
    auto lut10idx0 = [](long I) -> long {
        /* GATE 904 (LUT2 _4040_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut10.push_back(ctx.genrate_lut(lut10idx0));
    flut10.push_back(lut10idx0);
    auto lut10idx1 = [](long I) -> long {
        /* GATE 944 (LUT2 _4080_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin10 = 1 * ct_data122 + 2 * ct_data154;
    std::vector<Ciphertext> gout10 = ctx.eval_lut_amortized(&gin10, lut10);

    std::vector<RotationPoly> lut11;
    std::vector<long (*)(long)> flut11;
    auto lut11idx0 = [](long I) -> long {
        /* GATE 17 (LUT2 _3153_ INIT 0x6 PERM 01) */
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
        /* GATE 46 (LUT2 _3182_ INIT 0x8 PERM 01) */
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
    Ciphertext gin11 = 1 * gout6[1] + 2 * ct_data161;
    std::vector<Ciphertext> gout11 = ctx.eval_lut_amortized(&gin11, lut11);

    std::vector<RotationPoly> lut12;
    std::vector<long (*)(long)> flut12;
    auto lut12idx0 = [](long I) -> long {
        /* GATE 13 (LUT2 _3149_ INIT 0x6 PERM 01) */
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
        /* GATE 14 (LUT2 _3150_ INIT 0x8 PERM 01) */
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
    Ciphertext gin12 = 1 * ct_data0 + 2 * ct_data32;
    std::vector<Ciphertext> gout12 = ctx.eval_lut_amortized(&gin12, lut12);

    std::vector<RotationPoly> lut13;
    std::vector<long (*)(long)> flut13;
    auto lut13idx0 = [](long I) -> long {
        /* GATE 434 (LUT2 _3570_ INIT 0x6 PERM 01) */
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
        /* GATE 469 (LUT2 _3605_ INIT 0x8 PERM 01) */
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
    Ciphertext gin13 = 1 * ct_data13 + 2 * ct_data45;
    std::vector<Ciphertext> gout13 = ctx.eval_lut_amortized(&gin13, lut13);

    std::vector<RotationPoly> lut14;
    std::vector<long (*)(long)> flut14;
    auto lut14idx0 = [](long I) -> long {
        /* GATE 796 (LUT2 _3932_ INIT 0x6 PERM 01) */
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
        /* GATE 838 (LUT2 _3974_ INIT 0x8 PERM 01) */
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
    Ciphertext gin14 = 1 * ct_data119 + 2 * ct_data151;
    std::vector<Ciphertext> gout14 = ctx.eval_lut_amortized(&gin14, lut14);

    std::vector<RotationPoly> lut15;
    std::vector<long (*)(long)> flut15;
    auto lut15idx0 = [](long I) -> long {
        /* GATE 22 (LUT2 _3158_ INIT 0x6 PERM 01) */
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
        /* GATE 12 (LUT2 _3148_ INIT 0x8 PERM 01) */
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
    Ciphertext gin15 = 1 * gout12[0] + 2 * ct_data64;
    std::vector<Ciphertext> gout15 = ctx.eval_lut_amortized(&gin15, lut15);

    std::vector<RotationPoly> lut16;
    std::vector<long (*)(long)> flut16;
    auto lut16idx0 = [](long I) -> long {
        /* GATE 400 (LUT2 _3536_ INIT 0x6 PERM 01) */
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
        /* GATE 440 (LUT2 _3576_ INIT 0x8 PERM 01) */
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
    Ciphertext gin16 = 1 * gout8[0] + 2 * ct_data172;
    std::vector<Ciphertext> gout16 = ctx.eval_lut_amortized(&gin16, lut16);

    std::vector<RotationPoly> lut17;
    std::vector<long (*)(long)> flut17;
    auto lut17idx0 = [](long I) -> long {
        /* GATE 112 (LUT2 _3248_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut17.push_back(ctx.genrate_lut(lut17idx0));
    flut17.push_back(lut17idx0);
    auto lut17idx1 = [](long I) -> long {
        /* GATE 68 (LUT2 _3204_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin17 = 1 * ct_data3 + 2 * ct_data35;
    std::vector<Ciphertext> gout17 = ctx.eval_lut_amortized(&gin17, lut17);

    std::vector<RotationPoly> lut18;
    std::vector<long (*)(long)> flut18;
    auto lut18idx0 = [](long I) -> long {
        /* GATE 151 (LUT2 _3287_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut18.push_back(ctx.genrate_lut(lut18idx0));
    flut18.push_back(lut18idx0);
    auto lut18idx1 = [](long I) -> long {
        /* GATE 191 (LUT2 _3327_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin18 = 1 * ct_data101 + 2 * ct_data133;
    std::vector<Ciphertext> gout18 = ctx.eval_lut_amortized(&gin18, lut18);

    std::vector<RotationPoly> lut19;
    std::vector<long (*)(long)> flut19;
    auto lut19idx0 = [](long I) -> long {
        /* GATE 436 (LUT2 _3572_ INIT 0x6 PERM 01) */
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
        /* GATE 478 (LUT2 _3614_ INIT 0x8 PERM 01) */
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
    Ciphertext gin19 = 1 * ct_data109 + 2 * ct_data141;
    std::vector<Ciphertext> gout19 = ctx.eval_lut_amortized(&gin19, lut19);

    std::vector<RotationPoly> lut20;
    std::vector<long (*)(long)> flut20;
    auto lut20idx0 = [](long I) -> long {
        /* GATE 397 (LUT2 _3533_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut20.push_back(ctx.genrate_lut(lut20idx0));
    flut20.push_back(lut20idx0);
    auto lut20idx1 = [](long I) -> long {
        /* GATE 362 (LUT2 _3498_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin20 = 1 * ct_data11 + 2 * ct_data43;
    std::vector<Ciphertext> gout20 = ctx.eval_lut_amortized(&gin20, lut20);

    std::vector<RotationPoly> lut21;
    std::vector<long (*)(long)> flut21;
    auto lut21idx0 = [](long I) -> long {
        /* GATE 439 (LUT2 _3575_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin21 = 1 * gout16[1] + 2 * gout8[1];
    std::vector<Ciphertext> gout21 = ctx.eval_lut_amortized(&gin21, lut21);

    std::vector<RotationPoly> lut22;
    std::vector<long (*)(long)> flut22;
    auto lut22idx0 = [](long I) -> long {
        /* GATE 40 (LUT2 _3176_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut22.push_back(ctx.genrate_lut(lut22idx0));
    flut22.push_back(lut22idx0);
    auto lut22idx1 = [](long I) -> long {
        /* GATE 66 (LUT2 _3202_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin22 = 1 * ct_data2 + 2 * ct_data34;
    std::vector<Ciphertext> gout22 = ctx.eval_lut_amortized(&gin22, lut22);

    std::vector<RotationPoly> lut23;
    std::vector<long (*)(long)> flut23;
    auto lut23idx0 = [](long I) -> long {
        /* GATE 327 (LUT2 _3463_ INIT 0x6 PERM 01) */
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
        /* GATE 360 (LUT2 _3496_ INIT 0x8 PERM 01) */
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
    Ciphertext gin23 = 1 * ct_data10 + 2 * ct_data42;
    std::vector<Ciphertext> gout23 = ctx.eval_lut_amortized(&gin23, lut23);

    std::vector<RotationPoly> lut24;
    std::vector<long (*)(long)> flut24;
    auto lut24idx0 = [](long I) -> long {
        /* GATE 399 (LUT2 _3535_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut24.push_back(ctx.genrate_lut(lut24idx0));
    flut24.push_back(lut24idx0);
    auto lut24idx1 = [](long I) -> long {
        /* GATE 432 (LUT2 _3568_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin24 = 1 * ct_data12 + 2 * ct_data44;
    std::vector<Ciphertext> gout24 = ctx.eval_lut_amortized(&gin24, lut24);

    std::vector<RotationPoly> lut25;
    std::vector<long (*)(long)> flut25;
    auto lut25idx0 = [](long I) -> long {
        /* GATE 111 (LUT2 _3247_ INIT 0x8 PERM 01) */
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
        /* GATE 67 (LUT2 _3203_ INIT 0x6 PERM 01) */
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
    Ciphertext gin25 = 1 * gout17[1] + 2 * ct_data67;
    std::vector<Ciphertext> gout25 = ctx.eval_lut_amortized(&gin25, lut25);

    std::vector<RotationPoly> lut26;
    std::vector<long (*)(long)> flut26;
    auto lut26idx0 = [](long I) -> long {
        /* GATE 361 (LUT2 _3497_ INIT 0x6 PERM 01) */
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
        /* GATE 396 (LUT2 _3532_ INIT 0x8 PERM 01) */
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
    Ciphertext gin26 = 1 * gout20[1] + 2 * ct_data75;
    std::vector<Ciphertext> gout26 = ctx.eval_lut_amortized(&gin26, lut26);

    std::vector<RotationPoly> lut27;
    std::vector<long (*)(long)> flut27;
    auto lut27idx0 = [](long I) -> long {
        /* GATE 148 (LUT2 _3284_ INIT 0x6 PERM 01) */
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
        /* GATE 181 (LUT2 _3317_ INIT 0x8 PERM 01) */
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
    Ciphertext gin27 = 1 * gout4[0] + 2 * ct_data69;
    std::vector<Ciphertext> gout27 = ctx.eval_lut_amortized(&gin27, lut27);

    std::vector<RotationPoly> lut28;
    std::vector<long (*)(long)> flut28;
    auto lut28idx0 = [](long I) -> long {
        /* GATE 1046 (LUT2 _4182_ INIT 0x8 PERM 01) */
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
        /* GATE 1008 (LUT2 _4144_ INIT 0x6 PERM 01) */
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
    Ciphertext gin28 = 1 * ct_data29 + 2 * ct_data61;
    std::vector<Ciphertext> gout28 = ctx.eval_lut_amortized(&gin28, lut28);

    std::vector<RotationPoly> lut29;
    std::vector<long (*)(long)> flut29;
    auto lut29idx0 = [](long I) -> long {
        /* GATE 615 (LUT2 _3751_ INIT 0x6 PERM 01) */
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
        /* GATE 648 (LUT2 _3784_ INIT 0x8 PERM 01) */
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
    Ciphertext gin29 = 1 * ct_data18 + 2 * ct_data50;
    std::vector<Ciphertext> gout29 = ctx.eval_lut_amortized(&gin29, lut29);

    std::vector<RotationPoly> lut30;
    std::vector<long (*)(long)> flut30;
    auto lut30idx0 = [](long I) -> long {
        /* GATE 468 (LUT2 _3604_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut30.push_back(ctx.genrate_lut(lut30idx0));
    flut30.push_back(lut30idx0);
    auto lut30idx1 = [](long I) -> long {
        /* GATE 433 (LUT2 _3569_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin30 = 1 * gout13[0] + 2 * ct_data77;
    std::vector<Ciphertext> gout30 = ctx.eval_lut_amortized(&gin30, lut30);

    std::vector<RotationPoly> lut31;
    std::vector<long (*)(long)> flut31;
    auto lut31idx0 = [](long I) -> long {
        /* GATE 219 (LUT2 _3355_ INIT 0x6 PERM 01) */
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
        /* GATE 253 (LUT2 _3389_ INIT 0x8 PERM 01) */
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
    Ciphertext gin31 = 1 * ct_data7 + 2 * ct_data39;
    std::vector<Ciphertext> gout31 = ctx.eval_lut_amortized(&gin31, lut31);

    std::vector<RotationPoly> lut32;
    std::vector<long (*)(long)> flut32;
    auto lut32idx0 = [](long I) -> long {
        /* GATE 255 (LUT2 _3391_ INIT 0x6 PERM 01) */
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
        /* GATE 288 (LUT2 _3424_ INIT 0x8 PERM 01) */
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
    Ciphertext gin32 = 1 * ct_data8 + 2 * ct_data40;
    std::vector<Ciphertext> gout32 = ctx.eval_lut_amortized(&gin32, lut32);

    std::vector<RotationPoly> lut33;
    std::vector<long (*)(long)> flut33;
    auto lut33idx0 = [](long I) -> long {
        /* GATE 687 (LUT2 _3823_ INIT 0x6 PERM 01) */
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
        /* GATE 720 (LUT2 _3856_ INIT 0x8 PERM 01) */
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
    Ciphertext gin33 = 1 * ct_data20 + 2 * ct_data52;
    std::vector<Ciphertext> gout33 = ctx.eval_lut_amortized(&gin33, lut33);

    std::vector<RotationPoly> lut34;
    std::vector<long (*)(long)> flut34;
    auto lut34idx0 = [](long I) -> long {
        /* GATE 792 (LUT2 _3928_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut34.push_back(ctx.genrate_lut(lut34idx0));
    flut34.push_back(lut34idx0);
    auto lut34idx1 = [](long I) -> long {
        /* GATE 759 (LUT2 _3895_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin34 = 1 * ct_data22 + 2 * ct_data54;
    std::vector<Ciphertext> gout34 = ctx.eval_lut_amortized(&gin34, lut34);

    std::vector<RotationPoly> lut35;
    std::vector<long (*)(long)> flut35;
    auto lut35idx0 = [](long I) -> long {
        /* GATE 114 (LUT2 _3250_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut35.push_back(ctx.genrate_lut(lut35idx0));
    flut35.push_back(lut35idx0);
    auto lut35idx1 = [](long I) -> long {
        /* GATE 147 (LUT2 _3283_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin35 = 1 * ct_data4 + 2 * ct_data36;
    std::vector<Ciphertext> gout35 = ctx.eval_lut_amortized(&gin35, lut35);

    std::vector<RotationPoly> lut36;
    std::vector<long (*)(long)> flut36;
    auto lut36idx0 = [](long I) -> long {
        /* GATE 831 (LUT2 _3967_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut36.push_back(ctx.genrate_lut(lut36idx0));
    flut36.push_back(lut36idx0);
    auto lut36idx1 = [](long I) -> long {
        /* GATE 864 (LUT2 _4000_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin36 = 1 * ct_data24 + 2 * ct_data56;
    std::vector<Ciphertext> gout36 = ctx.eval_lut_amortized(&gin36, lut36);

    std::vector<RotationPoly> lut37;
    std::vector<long (*)(long)> flut37;
    auto lut37idx0 = [](long I) -> long {
        /* GATE 329 (LUT2 _3465_ INIT 0x6 PERM 01) */
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
        /* GATE 369 (LUT2 _3505_ INIT 0x8 PERM 01) */
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
    Ciphertext gin37 = 1 * ct_data106 + 2 * ct_data138;
    std::vector<Ciphertext> gout37 = ctx.eval_lut_amortized(&gin37, lut37);

    std::vector<RotationPoly> lut38;
    std::vector<long (*)(long)> flut38;
    auto lut38idx0 = [](long I) -> long {
        /* GATE 156 (LUT2 _3292_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut38.push_back(ctx.genrate_lut(lut38idx0));
    flut38.push_back(lut38idx0);
    auto lut38idx1 = [](long I) -> long {
        /* GATE 116 (LUT2 _3252_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin38 = 1 * ct_data100 + 2 * ct_data132;
    std::vector<Ciphertext> gout38 = ctx.eval_lut_amortized(&gin38, lut38);

    std::vector<RotationPoly> lut39;
    std::vector<long (*)(long)> flut39;
    auto lut39idx0 = [](long I) -> long {
        /* GATE 1004 (LUT2 _4140_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin39 = 1 * gout7[1] + 2 * gout3[0];
    std::vector<Ciphertext> gout39 = ctx.eval_lut_amortized(&gin39, lut39);

    std::vector<RotationPoly> lut40;
    std::vector<long (*)(long)> flut40;
    auto lut40idx0 = [](long I) -> long {
        /* GATE 937 (LUT2 _4073_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut40.push_back(ctx.genrate_lut(lut40idx0));
    flut40.push_back(lut40idx0);
    auto lut40idx1 = [](long I) -> long {
        /* GATE 971 (LUT2 _4107_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin40 = 1 * ct_data27 + 2 * ct_data59;
    std::vector<Ciphertext> gout40 = ctx.eval_lut_amortized(&gin40, lut40);

    std::vector<RotationPoly> lut41;
    std::vector<long (*)(long)> flut41;
    auto lut41idx0 = [](long I) -> long {
        /* GATE 180 (LUT2 _3316_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin41 = 1 * gout27[1] + 2 * gout4[1];
    std::vector<Ciphertext> gout41 = ctx.eval_lut_amortized(&gin41, lut41);

    std::vector<RotationPoly> lut42;
    std::vector<long (*)(long)> flut42;
    auto lut42idx0 = [](long I) -> long {
        /* GATE 1039 (LUT2 _4175_ INIT 0x8 PERM 01) */
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
        /* GATE 1009 (LUT2 _4145_ INIT 0x6 PERM 01) */
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
    Ciphertext gin42 = 1 * gout5[1] + 2 * ct_data189;
    std::vector<Ciphertext> gout42 = ctx.eval_lut_amortized(&gin42, lut42);

    std::vector<RotationPoly> lut43;
    std::vector<long (*)(long)> flut43;
    auto lut43idx0 = [](long I) -> long {
        /* GATE 471 (LUT2 _3607_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut43.push_back(ctx.genrate_lut(lut43idx0));
    flut43.push_back(lut43idx0);
    auto lut43idx1 = [](long I) -> long {
        /* GATE 504 (LUT2 _3640_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin43 = 1 * ct_data14 + 2 * ct_data46;
    std::vector<Ciphertext> gout43 = ctx.eval_lut_amortized(&gin43, lut43);

    std::vector<RotationPoly> lut44;
    std::vector<long (*)(long)> flut44;
    auto lut44idx0 = [](long I) -> long {
        /* GATE 11 (LUT2 _3147_ INIT 0x1 PERM 01) */
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
    Ciphertext gin44 = 1 * gout15[1] + 2 * gout12[1];
    std::vector<Ciphertext> gout44 = ctx.eval_lut_amortized(&gin44, lut44);

    std::vector<RotationPoly> lut45;
    std::vector<long (*)(long)> flut45;
    auto lut45idx0 = [](long I) -> long {
        /* GATE 297 (LUT2 _3433_ INIT 0x8 PERM 01) */
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
        /* GATE 257 (LUT2 _3393_ INIT 0x6 PERM 01) */
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
    Ciphertext gin45 = 1 * ct_data104 + 2 * ct_data136;
    std::vector<Ciphertext> gout45 = ctx.eval_lut_amortized(&gin45, lut45);

    std::vector<RotationPoly> lut46;
    std::vector<long (*)(long)> flut46;
    auto lut46idx0 = [](long I) -> long {
        /* GATE 756 (LUT2 _3892_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut46.push_back(ctx.genrate_lut(lut46idx0));
    flut46.push_back(lut46idx0);
    auto lut46idx1 = [](long I) -> long {
        /* GATE 721 (LUT2 _3857_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin46 = 1 * gout1[0] + 2 * ct_data85;
    std::vector<Ciphertext> gout46 = ctx.eval_lut_amortized(&gin46, lut46);

    std::vector<RotationPoly> lut47;
    std::vector<long (*)(long)> flut47;
    auto lut47idx0 = [](long I) -> long {
        /* GATE 801 (LUT2 _3937_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut47.push_back(ctx.genrate_lut(lut47idx0));
    flut47.push_back(lut47idx0);
    auto lut47idx1 = [](long I) -> long {
        /* GATE 761 (LUT2 _3897_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin47 = 1 * ct_data118 + 2 * ct_data150;
    std::vector<Ciphertext> gout47 = ctx.eval_lut_amortized(&gin47, lut47);

    std::vector<RotationPoly> lut48;
    std::vector<long (*)(long)> flut48;
    auto lut48idx0 = [](long I) -> long {
        /* GATE 184 (LUT2 _3320_ INIT 0x6 PERM 01) */
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
        /* GATE 217 (LUT2 _3353_ INIT 0x8 PERM 01) */
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
    Ciphertext gin48 = 1 * ct_data6 + 2 * ct_data38;
    std::vector<Ciphertext> gout48 = ctx.eval_lut_amortized(&gin48, lut48);

    std::vector<RotationPoly> lut49;
    std::vector<long (*)(long)> flut49;
    auto lut49idx0 = [](long I) -> long {
        /* GATE 795 (LUT2 _3931_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut49.push_back(ctx.genrate_lut(lut49idx0));
    flut49.push_back(lut49idx0);
    auto lut49idx1 = [](long I) -> long {
        /* GATE 837 (LUT2 _3973_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin49 = 1 * gout14[0] + 2 * ct_data183;
    std::vector<Ciphertext> gout49 = ctx.eval_lut_amortized(&gin49, lut49);

    std::vector<RotationPoly> lut50;
    std::vector<long (*)(long)> flut50;
    auto lut50idx0 = [](long I) -> long {
        /* GATE 87 (LUT2 _3223_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut50.push_back(ctx.genrate_lut(lut50idx0));
    flut50.push_back(lut50idx0);
    auto lut50idx1 = [](long I) -> long {
        /* GATE 86 (LUT2 _3222_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin50 = 1 * ct_data192 + 2 * ct_data224;
    std::vector<Ciphertext> gout50 = ctx.eval_lut_amortized(&gin50, lut50);

    std::vector<RotationPoly> lut51;
    std::vector<long (*)(long)> flut51;
    auto lut51idx0 = [](long I) -> long {
        /* GATE 1007 (LUT2 _4143_ INIT 0x6 PERM 01) */
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
        /* GATE 1045 (LUT2 _4181_ INIT 0x8 PERM 01) */
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
    Ciphertext gin51 = 1 * gout28[1] + 2 * ct_data93;
    std::vector<Ciphertext> gout51 = ctx.eval_lut_amortized(&gin51, lut51);

    std::vector<RotationPoly> lut52;
    std::vector<long (*)(long)> flut52;
    auto lut52idx0 = [](long I) -> long {
        /* GATE 585 (LUT2 _3721_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut52.push_back(ctx.genrate_lut(lut52idx0));
    flut52.push_back(lut52idx0);
    auto lut52idx1 = [](long I) -> long {
        /* GATE 545 (LUT2 _3681_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin52 = 1 * ct_data112 + 2 * ct_data144;
    std::vector<Ciphertext> gout52 = ctx.eval_lut_amortized(&gin52, lut52);

    std::vector<RotationPoly> lut53;
    std::vector<long (*)(long)> flut53;
    auto lut53idx0 = [](long I) -> long {
        /* GATE 363 (LUT2 _3499_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut53.push_back(ctx.genrate_lut(lut53idx0));
    flut53.push_back(lut53idx0);
    auto lut53idx1 = [](long I) -> long {
        /* GATE 405 (LUT2 _3541_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin53 = 1 * gout2[1] + 2 * ct_data171;
    std::vector<Ciphertext> gout53 = ctx.eval_lut_amortized(&gin53, lut53);

    std::vector<RotationPoly> lut54;
    std::vector<long (*)(long)> flut54;
    auto lut54idx0 = [](long I) -> long {
        /* GATE 45 (LUT2 _3181_ INIT 0x1 PERM 01) */
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
    Ciphertext gin54 = 1 * gout11[1] + 2 * gout6[0];
    std::vector<Ciphertext> gout54 = ctx.eval_lut_amortized(&gin54, lut54);

    std::vector<RotationPoly> lut55;
    std::vector<long (*)(long)> flut55;
    auto lut55idx0 = [](long I) -> long {
        /* GATE 150 (LUT2 _3286_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut55.push_back(ctx.genrate_lut(lut55idx0));
    flut55.push_back(lut55idx0);
    auto lut55idx1 = [](long I) -> long {
        /* GATE 190 (LUT2 _3326_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin55 = 1 * gout18[0] + 2 * ct_data165;
    std::vector<Ciphertext> gout55 = ctx.eval_lut_amortized(&gin55, lut55);

    std::vector<RotationPoly> lut56;
    std::vector<long (*)(long)> flut56;
    auto lut56idx0 = [](long I) -> long {
        /* GATE 221 (LUT2 _3357_ INIT 0x6 PERM 01) */
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
    auto lut56idx1 = [](long I) -> long {
        /* GATE 262 (LUT2 _3398_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin56 = 1 * ct_data103 + 2 * ct_data135;
    std::vector<Ciphertext> gout56 = ctx.eval_lut_amortized(&gin56, lut56);

    std::vector<RotationPoly> lut57;
    std::vector<long (*)(long)> flut57;
    auto lut57idx0 = [](long I) -> long {
        /* GATE 21 (LUT2 _3157_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut57.push_back(ctx.genrate_lut(lut57idx0));
    flut57.push_back(lut57idx0);
    auto lut57idx1 = [](long I) -> long {
        /* GATE 27 (LUT2 _3163_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin57 = 1 * ct_data96 + 2 * ct_data128;
    std::vector<Ciphertext> gout57 = ctx.eval_lut_amortized(&gin57, lut57);

    std::vector<RotationPoly> lut58;
    std::vector<long (*)(long)> flut58;
    auto lut58idx0 = [](long I) -> long {
        /* GATE 576 (LUT2 _3712_ INIT 0x8 PERM 01) */
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
        /* GATE 543 (LUT2 _3679_ INIT 0x6 PERM 01) */
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
    Ciphertext gin58 = 1 * ct_data16 + 2 * ct_data48;
    std::vector<Ciphertext> gout58 = ctx.eval_lut_amortized(&gin58, lut58);

    std::vector<RotationPoly> lut59;
    std::vector<long (*)(long)> flut59;
    auto lut59idx0 = [](long I) -> long {
        /* GATE 1041 (LUT2 _4177_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin59 = 1 * ct_data254 + 2 * ct_data222;
    std::vector<Ciphertext> gout59 = ctx.eval_lut_amortized(&gin59, lut59);

    std::vector<RotationPoly> lut60;
    std::vector<long (*)(long)> flut60;
    auto lut60idx0 = [](long I) -> long {
        /* GATE 120 (LUT2 _3256_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut60.push_back(ctx.genrate_lut(lut60idx0));
    flut60.push_back(lut60idx0);
    auto lut60idx1 = [](long I) -> long {
        /* GATE 69 (LUT2 _3205_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin60 = 1 * gout0[0] + 2 * ct_data163;
    std::vector<Ciphertext> gout60 = ctx.eval_lut_amortized(&gin60, lut60);

    std::vector<RotationPoly> lut61;
    std::vector<long (*)(long)> flut61;
    auto lut61idx0 = [](long I) -> long {
        /* GATE 617 (LUT2 _3753_ INIT 0x6 PERM 01) */
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
        /* GATE 657 (LUT2 _3793_ INIT 0x8 PERM 01) */
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
    Ciphertext gin61 = 1 * ct_data114 + 2 * ct_data146;
    std::vector<Ciphertext> gout61 = ctx.eval_lut_amortized(&gin61, lut61);

    std::vector<RotationPoly> lut62;
    std::vector<long (*)(long)> flut62;
    auto lut62idx0 = [](long I) -> long {
        /* GATE 693 (LUT2 _3829_ INIT 0x8 PERM 01) */
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
        /* GATE 651 (LUT2 _3787_ INIT 0x6 PERM 01) */
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
    Ciphertext gin62 = 1 * gout9[0] + 2 * ct_data179;
    std::vector<Ciphertext> gout62 = ctx.eval_lut_amortized(&gin62, lut62);

    std::vector<RotationPoly> lut63;
    std::vector<long (*)(long)> flut63;
    auto lut63idx0 = [](long I) -> long {
        /* GATE 1050 (LUT2 _4186_ INIT 0x6 PERM 01) */
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
    auto fvec63 = [flut63](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut63[i](I));
        return ret;
    };

    std::cerr << "\rLUT63   ";
    Ciphertext gin63 = 1 * ct_data30 + 2 * ct_data126;
    std::vector<Ciphertext> gout63 = ctx.eval_lut_amortized(&gin63, lut63);

    std::vector<RotationPoly> lut64;
    std::vector<long (*)(long)> flut64;
    auto lut64idx0 = [](long I) -> long {
        /* GATE 689 (LUT2 _3825_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut64.push_back(ctx.genrate_lut(lut64idx0));
    flut64.push_back(lut64idx0);
    auto lut64idx1 = [](long I) -> long {
        /* GATE 729 (LUT2 _3865_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin64 = 1 * ct_data116 + 2 * ct_data148;
    std::vector<Ciphertext> gout64 = ctx.eval_lut_amortized(&gin64, lut64);

    std::vector<RotationPoly> lut65;
    std::vector<long (*)(long)> flut65;
    auto lut65idx0 = [](long I) -> long {
        /* GATE 758 (LUT2 _3894_ INIT 0x6 PERM 01) */
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
        /* GATE 791 (LUT2 _3927_ INIT 0x8 PERM 01) */
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
    Ciphertext gin65 = 1 * gout34[1] + 2 * ct_data86;
    std::vector<Ciphertext> gout65 = ctx.eval_lut_amortized(&gin65, lut65);

    std::vector<RotationPoly> lut66;
    std::vector<long (*)(long)> flut66;
    auto lut66idx0 = [](long I) -> long {
        /* GATE 1049 (LUT2 _4185_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin66 = 1 * ct_data94 + 2 * ct_data62;
    std::vector<Ciphertext> gout66 = ctx.eval_lut_amortized(&gin66, lut66);

    std::vector<RotationPoly> lut67;
    std::vector<long (*)(long)> flut67;
    auto lut67idx0 = [](long I) -> long {
        /* GATE 692 (LUT2 _3828_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin67 = 1 * gout62[0] + 2 * gout9[1];
    std::vector<Ciphertext> gout67 = ctx.eval_lut_amortized(&gin67, lut67);

    std::vector<RotationPoly> lut68;
    std::vector<long (*)(long)> flut68;
    auto lut68idx0 = [](long I) -> long {
        /* GATE 1038 (LUT2 _4174_ INIT 0x1 PERM 01) */
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
    Ciphertext gin68 = 1 * gout42[0] + 2 * gout5[0];
    std::vector<Ciphertext> gout68 = ctx.eval_lut_amortized(&gin68, lut68);

    std::vector<RotationPoly> lut69;
    std::vector<long (*)(long)> flut69;
    auto lut69idx0 = [](long I) -> long {
        /* GATE 326 (LUT2 _3462_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut69.push_back(ctx.genrate_lut(lut69idx0));
    flut69.push_back(lut69idx0);
    auto lut69idx1 = [](long I) -> long {
        /* GATE 359 (LUT2 _3495_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin69 = 1 * gout23[0] + 2 * ct_data74;
    std::vector<Ciphertext> gout69 = ctx.eval_lut_amortized(&gin69, lut69);

    std::vector<RotationPoly> lut70;
    std::vector<long (*)(long)> flut70;
    auto lut70idx0 = [](long I) -> long {
        /* GATE 688 (LUT2 _3824_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut70.push_back(ctx.genrate_lut(lut70idx0));
    flut70.push_back(lut70idx0);
    auto lut70idx1 = [](long I) -> long {
        /* GATE 728 (LUT2 _3864_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin70 = 1 * gout64[0] + 2 * ct_data180;
    std::vector<Ciphertext> gout70 = ctx.eval_lut_amortized(&gin70, lut70);

    std::vector<RotationPoly> lut71;
    std::vector<long (*)(long)> flut71;
    auto lut71idx0 = [](long I) -> long {
        /* GATE 1048 (LUT2 _4184_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin71 = 1 * gout66[0] + 2 * ct_data158;
    std::vector<Ciphertext> gout71 = ctx.eval_lut_amortized(&gin71, lut71);

    std::vector<RotationPoly> lut72;
    std::vector<long (*)(long)> flut72;
    auto lut72idx0 = [](long I) -> long {
        /* GATE 794 (LUT2 _3930_ INIT 0x6 PERM 01) */
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
        /* GATE 829 (LUT2 _3965_ INIT 0x8 PERM 01) */
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
    Ciphertext gin72 = 1 * ct_data23 + 2 * ct_data55;
    std::vector<Ciphertext> gout72 = ctx.eval_lut_amortized(&gin72, lut72);

    std::vector<RotationPoly> lut73;
    std::vector<long (*)(long)> flut73;
    auto lut73idx0 = [](long I) -> long {
        /* GATE 1037 (LUT2 _4173_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin73 = 1 * gout68[0] + 2 * gout59[0];
    std::vector<Ciphertext> gout73 = ctx.eval_lut_amortized(&gin73, lut73);

    std::vector<RotationPoly> lut74;
    std::vector<long (*)(long)> flut74;
    auto lut74idx0 = [](long I) -> long {
        /* GATE 970 (LUT2 _4106_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut74.push_back(ctx.genrate_lut(lut74idx0));
    flut74.push_back(lut74idx0);
    auto lut74idx1 = [](long I) -> long {
        /* GATE 936 (LUT2 _4072_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin74 = 1 * gout40[0] + 2 * ct_data91;
    std::vector<Ciphertext> gout74 = ctx.eval_lut_amortized(&gin74, lut74);

    std::vector<RotationPoly> lut75;
    std::vector<long (*)(long)> flut75;
    auto lut75idx0 = [](long I) -> long {
        /* GATE 1047 (LUT2 _4183_ INIT 0x6 PERM 01) */
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
    auto fvec75 = [flut75](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut75[i](I));
        return ret;
    };

    std::cerr << "\rLUT75   ";
    Ciphertext gin75 = 1 * gout71[0] + 2 * gout63[0];
    std::vector<Ciphertext> gout75 = ctx.eval_lut_amortized(&gin75, lut75);

    std::vector<RotationPoly> lut76;
    std::vector<long (*)(long)> flut76;
    auto lut76idx0 = [](long I) -> long {
        /* GATE 727 (LUT2 _3863_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut76.push_back(ctx.genrate_lut(lut76idx0));
    flut76.push_back(lut76idx0);
    auto fvec76 = [flut76](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut76[i](I));
        return ret;
    };

    std::cerr << "\rLUT76   ";
    Ciphertext gin76 = 1 * gout70[1] + 2 * gout64[1];
    std::vector<Ciphertext> gout76 = ctx.eval_lut_amortized(&gin76, lut76);

    std::vector<RotationPoly> lut77;
    std::vector<long (*)(long)> flut77;
    auto lut77idx0 = [](long I) -> long {
        /* GATE 477 (LUT2 _3613_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut77.push_back(ctx.genrate_lut(lut77idx0));
    flut77.push_back(lut77idx0);
    auto lut77idx1 = [](long I) -> long {
        /* GATE 435 (LUT2 _3571_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin77 = 1 * gout19[0] + 2 * ct_data173;
    std::vector<Ciphertext> gout77 = ctx.eval_lut_amortized(&gin77, lut77);

    std::vector<RotationPoly> lut78;
    std::vector<long (*)(long)> flut78;
    auto lut78idx0 = [](long I) -> long {
        /* GATE 975 (LUT2 _4111_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut78.push_back(ctx.genrate_lut(lut78idx0));
    flut78.push_back(lut78idx0);
    auto lut78idx1 = [](long I) -> long {
        /* GATE 1015 (LUT2 _4151_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin78 = 1 * ct_data124 + 2 * ct_data156;
    std::vector<Ciphertext> gout78 = ctx.eval_lut_amortized(&gin78, lut78);

    std::vector<RotationPoly> lut79;
    std::vector<long (*)(long)> flut79;
    auto lut79idx0 = [](long I) -> long {
        /* GATE 830 (LUT2 _3966_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut79.push_back(ctx.genrate_lut(lut79idx0));
    flut79.push_back(lut79idx0);
    auto lut79idx1 = [](long I) -> long {
        /* GATE 863 (LUT2 _3999_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin79 = 1 * gout36[0] + 2 * ct_data88;
    std::vector<Ciphertext> gout79 = ctx.eval_lut_amortized(&gin79, lut79);

    std::vector<RotationPoly> lut80;
    std::vector<long (*)(long)> flut80;
    auto lut80idx0 = [](long I) -> long {
        /* GATE 939 (LUT2 _4075_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut80.push_back(ctx.genrate_lut(lut80idx0));
    flut80.push_back(lut80idx0);
    auto lut80idx1 = [](long I) -> long {
        /* GATE 980 (LUT2 _4116_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin80 = 1 * ct_data123 + 2 * ct_data155;
    std::vector<Ciphertext> gout80 = ctx.eval_lut_amortized(&gin80, lut80);

    std::vector<RotationPoly> lut81;
    std::vector<long (*)(long)> flut81;
    auto lut81idx0 = [](long I) -> long {
        /* GATE 508 (LUT2 _3644_ INIT 0x6 PERM 01) */
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
        /* GATE 550 (LUT2 _3686_ INIT 0x8 PERM 01) */
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
    Ciphertext gin81 = 1 * ct_data111 + 2 * ct_data143;
    std::vector<Ciphertext> gout81 = ctx.eval_lut_amortized(&gin81, lut81);

    std::vector<RotationPoly> lut82;
    std::vector<long (*)(long)> flut82;
    auto lut82idx0 = [](long I) -> long {
        /* GATE 685 (LUT2 _3821_ INIT 0x8 PERM 01) */
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
        /* GATE 650 (LUT2 _3786_ INIT 0x6 PERM 01) */
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
    Ciphertext gin82 = 1 * ct_data19 + 2 * ct_data51;
    std::vector<Ciphertext> gout82 = ctx.eval_lut_amortized(&gin82, lut82);

    std::vector<RotationPoly> lut83;
    std::vector<long (*)(long)> flut83;
    auto lut83idx0 = [](long I) -> long {
        /* GATE 613 (LUT2 _3749_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut83.push_back(ctx.genrate_lut(lut83idx0));
    flut83.push_back(lut83idx0);
    auto lut83idx1 = [](long I) -> long {
        /* GATE 578 (LUT2 _3714_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin83 = 1 * ct_data17 + 2 * ct_data49;
    std::vector<Ciphertext> gout83 = ctx.eval_lut_amortized(&gin83, lut83);

    std::vector<RotationPoly> lut84;
    std::vector<long (*)(long)> flut84;
    auto lut84idx0 = [](long I) -> long {
        /* GATE 541 (LUT2 _3677_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut84.push_back(ctx.genrate_lut(lut84idx0));
    flut84.push_back(lut84idx0);
    auto lut84idx1 = [](long I) -> long {
        /* GATE 506 (LUT2 _3642_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin84 = 1 * ct_data15 + 2 * ct_data47;
    std::vector<Ciphertext> gout84 = ctx.eval_lut_amortized(&gin84, lut84);

    std::vector<RotationPoly> lut85;
    std::vector<long (*)(long)> flut85;
    auto lut85idx0 = [](long I) -> long {
        /* GATE 226 (LUT2 _3362_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut85.push_back(ctx.genrate_lut(lut85idx0));
    flut85.push_back(lut85idx0);
    auto lut85idx1 = [](long I) -> long {
        /* GATE 186 (LUT2 _3322_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin85 = 1 * ct_data102 + 2 * ct_data134;
    std::vector<Ciphertext> gout85 = ctx.eval_lut_amortized(&gin85, lut85);

    std::vector<RotationPoly> lut86;
    std::vector<long (*)(long)> flut86;
    auto lut86idx0 = [](long I) -> long {
        /* GATE 903 (LUT2 _4039_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut86.push_back(ctx.genrate_lut(lut86idx0));
    flut86.push_back(lut86idx0);
    auto lut86idx1 = [](long I) -> long {
        /* GATE 943 (LUT2 _4079_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin86 = 1 * gout10[0] + 2 * ct_data186;
    std::vector<Ciphertext> gout86 = ctx.eval_lut_amortized(&gin86, lut86);

    std::vector<RotationPoly> lut87;
    std::vector<long (*)(long)> flut87;
    auto lut87idx0 = [](long I) -> long {
        /* GATE 909 (LUT2 _4045_ INIT 0x8 PERM 01) */
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
        /* GATE 868 (LUT2 _4004_ INIT 0x6 PERM 01) */
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
    Ciphertext gin87 = 1 * ct_data121 + 2 * ct_data153;
    std::vector<Ciphertext> gout87 = ctx.eval_lut_amortized(&gin87, lut87);

    std::vector<RotationPoly> lut88;
    std::vector<long (*)(long)> flut88;
    auto lut88idx0 = [](long I) -> long {
        /* GATE 1044 (LUT2 _4180_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin88 = 1 * gout51[1] + 2 * gout28[0];
    std::vector<Ciphertext> gout88 = ctx.eval_lut_amortized(&gin88, lut88);

    std::vector<RotationPoly> lut89;
    std::vector<long (*)(long)> flut89;
    auto lut89idx0 = [](long I) -> long {
        /* GATE 873 (LUT2 _4009_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut89.push_back(ctx.genrate_lut(lut89idx0));
    flut89.push_back(lut89idx0);
    auto lut89idx1 = [](long I) -> long {
        /* GATE 833 (LUT2 _3969_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin89 = 1 * ct_data120 + 2 * ct_data152;
    std::vector<Ciphertext> gout89 = ctx.eval_lut_amortized(&gin89, lut89);

    std::vector<RotationPoly> lut90;
    std::vector<long (*)(long)> flut90;
    auto lut90idx0 = [](long I) -> long {
        /* GATE 325 (LUT2 _3461_ INIT 0x8 PERM 01) */
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
        /* GATE 290 (LUT2 _3426_ INIT 0x6 PERM 01) */
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
    Ciphertext gin90 = 1 * ct_data9 + 2 * ct_data41;
    std::vector<Ciphertext> gout90 = ctx.eval_lut_amortized(&gin90, lut90);

    std::vector<RotationPoly> lut91;
    std::vector<long (*)(long)> flut91;
    auto lut91idx0 = [](long I) -> long {
        /* GATE 110 (LUT2 _3246_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin91 = 1 * gout25[0] + 2 * gout17[0];
    std::vector<Ciphertext> gout91 = ctx.eval_lut_amortized(&gin91, lut91);

    std::vector<RotationPoly> lut92;
    std::vector<long (*)(long)> flut92;
    auto lut92idx0 = [](long I) -> long {
        /* GATE 481 (LUT2 _3617_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut92.push_back(ctx.genrate_lut(lut92idx0));
    flut92.push_back(lut92idx0);
    auto lut92idx1 = [](long I) -> long {
        /* GATE 438 (LUT2 _3574_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
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
    Ciphertext gin92 = 1 * gout21[0] + 2 * ct_data205;
    std::vector<Ciphertext> gout92 = ctx.eval_lut_amortized(&gin92, lut92);

    std::vector<RotationPoly> lut93;
    std::vector<long (*)(long)> flut93;
    auto lut93idx0 = [](long I) -> long {
        /* GATE 542 (LUT2 _3678_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut93.push_back(ctx.genrate_lut(lut93idx0));
    flut93.push_back(lut93idx0);
    auto lut93idx1 = [](long I) -> long {
        /* GATE 575 (LUT2 _3711_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin93 = 1 * gout58[1] + 2 * ct_data80;
    std::vector<Ciphertext> gout93 = ctx.eval_lut_amortized(&gin93, lut93);

    std::vector<RotationPoly> lut94;
    std::vector<long (*)(long)> flut94;
    auto lut94idx0 = [](long I) -> long {
        /* GATE 719 (LUT2 _3855_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut94.push_back(ctx.genrate_lut(lut94idx0));
    flut94.push_back(lut94idx0);
    auto lut94idx1 = [](long I) -> long {
        /* GATE 686 (LUT2 _3822_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin94 = 1 * gout33[0] + 2 * ct_data84;
    std::vector<Ciphertext> gout94 = ctx.eval_lut_amortized(&gin94, lut94);

    std::vector<RotationPoly> lut95;
    std::vector<long (*)(long)> flut95;
    auto lut95idx0 = [](long I) -> long {
        /* GATE 614 (LUT2 _3750_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut95.push_back(ctx.genrate_lut(lut95idx0));
    flut95.push_back(lut95idx0);
    auto lut95idx1 = [](long I) -> long {
        /* GATE 647 (LUT2 _3783_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin95 = 1 * gout29[0] + 2 * ct_data82;
    std::vector<Ciphertext> gout95 = ctx.eval_lut_amortized(&gin95, lut95);

    std::vector<RotationPoly> lut96;
    std::vector<long (*)(long)> flut96;
    auto lut96idx0 = [](long I) -> long {
        /* GATE 75 (LUT2 _3211_ INIT 0x8 PERM 01) */
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
        /* GATE 42 (LUT2 _3178_ INIT 0x6 PERM 01) */
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
    Ciphertext gin96 = 1 * ct_data98 + 2 * ct_data130;
    std::vector<Ciphertext> gout96 = ctx.eval_lut_amortized(&gin96, lut96);

    std::vector<RotationPoly> lut97;
    std::vector<long (*)(long)> flut97;
    auto lut97idx0 = [](long I) -> long {
        /* GATE 513 (LUT2 _3649_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut97.push_back(ctx.genrate_lut(lut97idx0));
    flut97.push_back(lut97idx0);
    auto lut97idx1 = [](long I) -> long {
        /* GATE 473 (LUT2 _3609_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin97 = 1 * ct_data110 + 2 * ct_data142;
    std::vector<Ciphertext> gout97 = ctx.eval_lut_amortized(&gin97, lut97);

    std::vector<RotationPoly> lut98;
    std::vector<long (*)(long)> flut98;
    auto lut98idx0 = [](long I) -> long {
        /* GATE 119 (LUT2 _3255_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin98 = 1 * gout60[0] + 2 * gout0[1];
    std::vector<Ciphertext> gout98 = ctx.eval_lut_amortized(&gin98, lut98);

    std::vector<RotationPoly> lut99;
    std::vector<long (*)(long)> flut99;
    auto lut99idx0 = [](long I) -> long {
        /* GATE 431 (LUT2 _3567_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut99.push_back(ctx.genrate_lut(lut99idx0));
    flut99.push_back(lut99idx0);
    auto lut99idx1 = [](long I) -> long {
        /* GATE 398 (LUT2 _3534_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin99 = 1 * gout24[0] + 2 * ct_data76;
    std::vector<Ciphertext> gout99 = ctx.eval_lut_amortized(&gin99, lut99);

    std::vector<RotationPoly> lut100;
    std::vector<long (*)(long)> flut100;
    auto lut100idx0 = [](long I) -> long {
        /* GATE 252 (LUT2 _3388_ INIT 0x8 PERM 01) */
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
        /* GATE 218 (LUT2 _3354_ INIT 0x6 PERM 01) */
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
    Ciphertext gin100 = 1 * gout31[0] + 2 * ct_data71;
    std::vector<Ciphertext> gout100 = ctx.eval_lut_amortized(&gin100, lut100);

    std::vector<RotationPoly> lut101;
    std::vector<long (*)(long)> flut101;
    auto lut101idx0 = [](long I) -> long {
        /* GATE 254 (LUT2 _3390_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut101.push_back(ctx.genrate_lut(lut101idx0));
    flut101.push_back(lut101idx0);
    auto lut101idx1 = [](long I) -> long {
        /* GATE 287 (LUT2 _3423_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin101 = 1 * gout32[0] + 2 * ct_data72;
    std::vector<Ciphertext> gout101 = ctx.eval_lut_amortized(&gin101, lut101);

    std::vector<RotationPoly> lut102;
    std::vector<long (*)(long)> flut102;
    auto lut102idx0 = [](long I) -> long {
        /* GATE 766 (LUT2 _3902_ INIT 0x8 PERM 01) */
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
        /* GATE 724 (LUT2 _3860_ INIT 0x6 PERM 01) */
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
    Ciphertext gin102 = 1 * ct_data117 + 2 * ct_data149;
    std::vector<Ciphertext> gout102 = ctx.eval_lut_amortized(&gin102, lut102);

    std::vector<RotationPoly> lut103;
    std::vector<long (*)(long)> flut103;
    auto lut103idx0 = [](long I) -> long {
        /* GATE 503 (LUT2 _3639_ INIT 0x8 PERM 01) */
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
        /* GATE 470 (LUT2 _3606_ INIT 0x6 PERM 01) */
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
    Ciphertext gin103 = 1 * gout43[0] + 2 * ct_data78;
    std::vector<Ciphertext> gout103 = ctx.eval_lut_amortized(&gin103, lut103);

    std::vector<RotationPoly> lut104;
    std::vector<long (*)(long)> flut104;
    auto lut104idx0 = [](long I) -> long {
        /* GATE 580 (LUT2 _3716_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut104.push_back(ctx.genrate_lut(lut104idx0));
    flut104.push_back(lut104idx0);
    auto lut104idx1 = [](long I) -> long {
        /* GATE 622 (LUT2 _3758_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin104 = 1 * ct_data113 + 2 * ct_data145;
    std::vector<Ciphertext> gout104 = ctx.eval_lut_amortized(&gin104, lut104);

    std::vector<RotationPoly> lut105;
    std::vector<long (*)(long)> flut105;
    auto lut105idx0 = [](long I) -> long {
        /* GATE 902 (LUT2 _4038_ INIT 0x6 PERM 01) */
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
        /* GATE 935 (LUT2 _4071_ INIT 0x8 PERM 01) */
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
    Ciphertext gin105 = 1 * ct_data26 + 2 * ct_data58;
    std::vector<Ciphertext> gout105 = ctx.eval_lut_amortized(&gin105, lut105);

    std::vector<RotationPoly> lut106;
    std::vector<long (*)(long)> flut106;
    auto lut106idx0 = [](long I) -> long {
        /* GATE 577 (LUT2 _3713_ INIT 0x6 PERM 01) */
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
        /* GATE 612 (LUT2 _3748_ INIT 0x8 PERM 01) */
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
    Ciphertext gin106 = 1 * gout83[1] + 2 * ct_data81;
    std::vector<Ciphertext> gout106 = ctx.eval_lut_amortized(&gin106, lut106);

    std::vector<RotationPoly> lut107;
    std::vector<long (*)(long)> flut107;
    auto lut107idx0 = [](long I) -> long {
        /* GATE 866 (LUT2 _4002_ INIT 0x6 PERM 01) */
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
        /* GATE 900 (LUT2 _4036_ INIT 0x8 PERM 01) */
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
    Ciphertext gin107 = 1 * ct_data25 + 2 * ct_data57;
    std::vector<Ciphertext> gout107 = ctx.eval_lut_amortized(&gin107, lut107);

    std::vector<RotationPoly> lut108;
    std::vector<long (*)(long)> flut108;
    auto lut108idx0 = [](long I) -> long {
        /* GATE 334 (LUT2 _3470_ INIT 0x8 PERM 01) */
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
        /* GATE 292 (LUT2 _3428_ INIT 0x6 PERM 01) */
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
    Ciphertext gin108 = 1 * ct_data105 + 2 * ct_data137;
    std::vector<Ciphertext> gout108 = ctx.eval_lut_amortized(&gin108, lut108);

    std::vector<RotationPoly> lut109;
    std::vector<long (*)(long)> flut109;
    auto lut109idx0 = [](long I) -> long {
        /* GATE 16 (LUT2 _3152_ INIT 0x6 PERM 01) */
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
        /* GATE 38 (LUT2 _3174_ INIT 0x8 PERM 01) */
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
    Ciphertext gin109 = 1 * ct_data1 + 2 * ct_data33;
    std::vector<Ciphertext> gout109 = ctx.eval_lut_amortized(&gin109, lut109);

    std::vector<RotationPoly> lut110;
    std::vector<long (*)(long)> flut110;
    auto lut110idx0 = [](long I) -> long {
        /* GATE 113 (LUT2 _3249_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut110.push_back(ctx.genrate_lut(lut110idx0));
    flut110.push_back(lut110idx0);
    auto lut110idx1 = [](long I) -> long {
        /* GATE 146 (LUT2 _3282_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin110 = 1 * gout35[0] + 2 * ct_data68;
    std::vector<Ciphertext> gout110 = ctx.eval_lut_amortized(&gin110, lut110);

    std::vector<RotationPoly> lut111;
    std::vector<long (*)(long)> flut111;
    auto lut111idx0 = [](long I) -> long {
        /* GATE 65 (LUT2 _3201_ INIT 0x8 PERM 01) */
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
        /* GATE 39 (LUT2 _3175_ INIT 0x6 PERM 01) */
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
    Ciphertext gin111 = 1 * gout22[0] + 2 * ct_data66;
    std::vector<Ciphertext> gout111 = ctx.eval_lut_amortized(&gin111, lut111);

    std::vector<RotationPoly> lut112;
    std::vector<long (*)(long)> flut112;
    auto lut112idx0 = [](long I) -> long {
        /* GATE 159 (LUT2 _3295_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut112.push_back(ctx.genrate_lut(lut112idx0));
    flut112.push_back(lut112idx0);
    auto lut112idx1 = [](long I) -> long {
        /* GATE 118 (LUT2 _3254_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin112 = 1 * gout98[0] + 2 * ct_data196;
    std::vector<Ciphertext> gout112 = ctx.eval_lut_amortized(&gin112, lut112);

    std::vector<RotationPoly> lut113;
    std::vector<long (*)(long)> flut113;
    auto lut113idx0 = [](long I) -> long {
        /* GATE 760 (LUT2 _3896_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut113.push_back(ctx.genrate_lut(lut113idx0));
    flut113.push_back(lut113idx0);
    auto lut113idx1 = [](long I) -> long {
        /* GATE 800 (LUT2 _3936_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin113 = 1 * gout47[1] + 2 * ct_data182;
    std::vector<Ciphertext> gout113 = ctx.eval_lut_amortized(&gin113, lut113);

    std::vector<RotationPoly> lut114;
    std::vector<long (*)(long)> flut114;
    auto lut114idx0 = [](long I) -> long {
        /* GATE 395 (LUT2 _3531_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin114 = 1 * gout26[1] + 2 * gout20[0];
    std::vector<Ciphertext> gout114 = ctx.eval_lut_amortized(&gin114, lut114);

    std::vector<RotationPoly> lut115;
    std::vector<long (*)(long)> flut115;
    auto lut115idx0 = [](long I) -> long {
        /* GATE 480 (LUT2 _3616_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut115.push_back(ctx.genrate_lut(lut115idx0));
    flut115.push_back(lut115idx0);
    auto lut115idx1 = [](long I) -> long {
        /* GATE 437 (LUT2 _3573_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin115 = 1 * gout92[1] + 2 * ct_data237;
    std::vector<Ciphertext> gout115 = ctx.eval_lut_amortized(&gin115, lut115);

    std::vector<RotationPoly> lut116;
    std::vector<long (*)(long)> flut116;
    auto lut116idx0 = [](long I) -> long {
        /* GATE 368 (LUT2 _3504_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut116.push_back(ctx.genrate_lut(lut116idx0));
    flut116.push_back(lut116idx0);
    auto lut116idx1 = [](long I) -> long {
        /* GATE 328 (LUT2 _3464_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin116 = 1 * gout37[0] + 2 * ct_data170;
    std::vector<Ciphertext> gout116 = ctx.eval_lut_amortized(&gin116, lut116);

    std::vector<RotationPoly> lut117;
    std::vector<long (*)(long)> flut117;
    auto lut117idx0 = [](long I) -> long {
        /* GATE 574 (LUT2 _3710_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin117 = 1 * gout93[1] + 2 * gout58[0];
    std::vector<Ciphertext> gout117 = ctx.eval_lut_amortized(&gin117, lut117);

    std::vector<RotationPoly> lut118;
    std::vector<long (*)(long)> flut118;
    auto lut118idx0 = [](long I) -> long {
        /* GATE 404 (LUT2 _3540_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin118 = 1 * gout53[1] + 2 * gout2[0];
    std::vector<Ciphertext> gout118 = ctx.eval_lut_amortized(&gin118, lut118);

    std::vector<RotationPoly> lut119;
    std::vector<long (*)(long)> flut119;
    auto lut119idx0 = [](long I) -> long {
        /* GATE 512 (LUT2 _3648_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut119.push_back(ctx.genrate_lut(lut119idx0));
    flut119.push_back(lut119idx0);
    auto lut119idx1 = [](long I) -> long {
        /* GATE 472 (LUT2 _3608_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin119 = 1 * gout97[1] + 2 * ct_data174;
    std::vector<Ciphertext> gout119 = ctx.eval_lut_amortized(&gin119, lut119);

    std::vector<RotationPoly> lut120;
    std::vector<long (*)(long)> flut120;
    auto lut120idx0 = [](long I) -> long {
        /* GATE 183 (LUT2 _3319_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut120.push_back(ctx.genrate_lut(lut120idx0));
    flut120.push_back(lut120idx0);
    auto lut120idx1 = [](long I) -> long {
        /* GATE 216 (LUT2 _3352_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin120 = 1 * gout48[0] + 2 * ct_data70;
    std::vector<Ciphertext> gout120 = ctx.eval_lut_amortized(&gin120, lut120);

    std::vector<RotationPoly> lut121;
    std::vector<long (*)(long)> flut121;
    auto lut121idx0 = [](long I) -> long {
        /* GATE 430 (LUT2 _3566_ INIT 0x1 PERM 01) */
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
    Ciphertext gin121 = 1 * gout99[0] + 2 * gout24[1];
    std::vector<Ciphertext> gout121 = ctx.eval_lut_amortized(&gin121, lut121);

    std::vector<RotationPoly> lut122;
    std::vector<long (*)(long)> flut122;
    auto lut122idx0 = [](long I) -> long {
        /* GATE 942 (LUT2 _4078_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin122 = 1 * gout86[1] + 2 * gout10[1];
    std::vector<Ciphertext> gout122 = ctx.eval_lut_amortized(&gin122, lut122);

    std::vector<RotationPoly> lut123;
    std::vector<long (*)(long)> flut123;
    auto lut123idx0 = [](long I) -> long {
        /* GATE 251 (LUT2 _3387_ INIT 0x1 PERM 01) */
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
    Ciphertext gin123 = 1 * gout100[0] + 2 * gout31[1];
    std::vector<Ciphertext> gout123 = ctx.eval_lut_amortized(&gin123, lut123);

    std::vector<RotationPoly> lut124;
    std::vector<long (*)(long)> flut124;
    auto lut124idx0 = [](long I) -> long {
        /* GATE 464 (LUT2 _3600_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut124.push_back(ctx.genrate_lut(lut124idx0));
    flut124.push_back(lut124idx0);
    auto lut124idx1 = [](long I) -> long {
        /* GATE 429 (LUT2 _3565_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
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
    Ciphertext gin124 = 1 * gout121[0] + 2 * gout30[1];
    std::vector<Ciphertext> gout124 = ctx.eval_lut_amortized(&gin124, lut124);

    std::vector<RotationPoly> lut125;
    std::vector<long (*)(long)> flut125;
    auto lut125idx0 = [](long I) -> long {
        /* GATE 969 (LUT2 _4105_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin125 = 1 * gout74[0] + 2 * gout40[1];
    std::vector<Ciphertext> gout125 = ctx.eval_lut_amortized(&gin125, lut125);

    std::vector<RotationPoly> lut126;
    std::vector<long (*)(long)> flut126;
    auto lut126idx0 = [](long I) -> long {
        /* GATE 691 (LUT2 _3827_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut126.push_back(ctx.genrate_lut(lut126idx0));
    flut126.push_back(lut126idx0);
    auto lut126idx1 = [](long I) -> long {
        /* GATE 732 (LUT2 _3868_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
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
    Ciphertext gin126 = 1 * gout67[0] + 2 * ct_data212;
    std::vector<Ciphertext> gout126 = ctx.eval_lut_amortized(&gin126, lut126);

    std::vector<RotationPoly> lut127;
    std::vector<long (*)(long)> flut127;
    auto lut127idx0 = [](long I) -> long {
        /* GATE 145 (LUT2 _3281_ INIT 0x1 PERM 01) */
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
    Ciphertext gin127 = 1 * gout110[1] + 2 * gout35[1];
    std::vector<Ciphertext> gout127 = ctx.eval_lut_amortized(&gin127, lut127);

    std::vector<RotationPoly> lut128;
    std::vector<long (*)(long)> flut128;
    auto lut128idx0 = [](long I) -> long {
        /* GATE 755 (LUT2 _3891_ INIT 0x1 PERM 01) */
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
    Ciphertext gin128 = 1 * gout46[0] + 2 * gout1[1];
    std::vector<Ciphertext> gout128 = ctx.eval_lut_amortized(&gin128, lut128);

    std::vector<RotationPoly> lut129;
    std::vector<long (*)(long)> flut129;
    auto lut129idx0 = [](long I) -> long {
        /* GATE 220 (LUT2 _3356_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut129.push_back(ctx.genrate_lut(lut129idx0));
    flut129.push_back(lut129idx0);
    auto lut129idx1 = [](long I) -> long {
        /* GATE 261 (LUT2 _3397_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin129 = 1 * gout56[0] + 2 * ct_data167;
    std::vector<Ciphertext> gout129 = ctx.eval_lut_amortized(&gin129, lut129);

    std::vector<RotationPoly> lut130;
    std::vector<long (*)(long)> flut130;
    auto lut130idx0 = [](long I) -> long {
        /* GATE 283 (LUT2 _3419_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut130.push_back(ctx.genrate_lut(lut130idx0));
    flut130.push_back(lut130idx0);
    auto lut130idx1 = [](long I) -> long {
        /* GATE 250 (LUT2 _3386_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin130 = 1 * gout123[0] + 2 * gout101[0];
    std::vector<Ciphertext> gout130 = ctx.eval_lut_amortized(&gin130, lut130);

    std::vector<RotationPoly> lut131;
    std::vector<long (*)(long)> flut131;
    auto lut131idx0 = [](long I) -> long {
        /* GATE 260 (LUT2 _3396_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin131 = 1 * gout129[1] + 2 * gout56[1];
    std::vector<Ciphertext> gout131 = ctx.eval_lut_amortized(&gin131, lut131);

    std::vector<RotationPoly> lut132;
    std::vector<long (*)(long)> flut132;
    auto lut132idx0 = [](long I) -> long {
        /* GATE 573 (LUT2 _3709_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut132.push_back(ctx.genrate_lut(lut132idx0));
    flut132.push_back(lut132idx0);
    auto lut132idx1 = [](long I) -> long {
        /* GATE 608 (LUT2 _3744_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin132 = 1 * gout117[0] + 2 * gout106[0];
    std::vector<Ciphertext> gout132 = ctx.eval_lut_amortized(&gin132, lut132);

    std::vector<RotationPoly> lut133;
    std::vector<long (*)(long)> flut133;
    auto lut133idx0 = [](long I) -> long {
        /* GATE 611 (LUT2 _3747_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin133 = 1 * gout106[1] + 2 * gout83[0];
    std::vector<Ciphertext> gout133 = ctx.eval_lut_amortized(&gin133, lut133);

    std::vector<RotationPoly> lut134;
    std::vector<long (*)(long)> flut134;
    auto lut134idx0 = [](long I) -> long {
        /* GATE 78 (LUT2 _3214_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut134.push_back(ctx.genrate_lut(lut134idx0));
    flut134.push_back(lut134idx0);
    auto lut134idx1 = [](long I) -> long {
        /* GATE 44 (LUT2 _3180_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
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
    Ciphertext gin134 = 1 * gout54[0] + 2 * ct_data194;
    std::vector<Ciphertext> gout134 = ctx.eval_lut_amortized(&gin134, lut134);

    std::vector<RotationPoly> lut135;
    std::vector<long (*)(long)> flut135;
    auto lut135idx0 = [](long I) -> long {
        /* GATE 656 (LUT2 _3792_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut135.push_back(ctx.genrate_lut(lut135idx0));
    flut135.push_back(lut135idx0);
    auto lut135idx1 = [](long I) -> long {
        /* GATE 616 (LUT2 _3752_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin135 = 1 * gout61[0] + 2 * ct_data178;
    std::vector<Ciphertext> gout135 = ctx.eval_lut_amortized(&gin135, lut135);

    std::vector<RotationPoly> lut136;
    std::vector<long (*)(long)> flut136;
    auto lut136idx0 = [](long I) -> long {
        /* GATE 790 (LUT2 _3926_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin136 = 1 * gout65[1] + 2 * gout34[0];
    std::vector<Ciphertext> gout136 = ctx.eval_lut_amortized(&gin136, lut136);

    std::vector<RotationPoly> lut137;
    std::vector<long (*)(long)> flut137;
    auto lut137idx0 = [](long I) -> long {
        /* GATE 584 (LUT2 _3720_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut137.push_back(ctx.genrate_lut(lut137idx0));
    flut137.push_back(lut137idx0);
    auto lut137idx1 = [](long I) -> long {
        /* GATE 544 (LUT2 _3680_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin137 = 1 * gout52[1] + 2 * ct_data176;
    std::vector<Ciphertext> gout137 = ctx.eval_lut_amortized(&gin137, lut137);

    std::vector<RotationPoly> lut138;
    std::vector<long (*)(long)> flut138;
    auto lut138idx0 = [](long I) -> long {
        /* GATE 799 (LUT2 _3935_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin138 = 1 * gout113[1] + 2 * gout47[0];
    std::vector<Ciphertext> gout138 = ctx.eval_lut_amortized(&gin138, lut138);

    std::vector<RotationPoly> lut139;
    std::vector<long (*)(long)> flut139;
    auto lut139idx0 = [](long I) -> long {
        /* GATE 467 (LUT2 _3603_ INIT 0x1 PERM 01) */
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
    Ciphertext gin139 = 1 * gout30[0] + 2 * gout13[1];
    std::vector<Ciphertext> gout139 = ctx.eval_lut_amortized(&gin139, lut139);

    std::vector<RotationPoly> lut140;
    std::vector<long (*)(long)> flut140;
    auto lut140idx0 = [](long I) -> long {
        /* GATE 867 (LUT2 _4003_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut140.push_back(ctx.genrate_lut(lut140idx0));
    flut140.push_back(lut140idx0);
    auto lut140idx1 = [](long I) -> long {
        /* GATE 908 (LUT2 _4044_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin140 = 1 * gout87[1] + 2 * ct_data185;
    std::vector<Ciphertext> gout140 = ctx.eval_lut_amortized(&gin140, lut140);

    std::vector<RotationPoly> lut141;
    std::vector<long (*)(long)> flut141;
    auto lut141idx0 = [](long I) -> long {
        /* GATE 549 (LUT2 _3685_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut141.push_back(ctx.genrate_lut(lut141idx0));
    flut141.push_back(lut141idx0);
    auto lut141idx1 = [](long I) -> long {
        /* GATE 507 (LUT2 _3643_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin141 = 1 * gout81[0] + 2 * ct_data175;
    std::vector<Ciphertext> gout141 = ctx.eval_lut_amortized(&gin141, lut141);

    std::vector<RotationPoly> lut142;
    std::vector<long (*)(long)> flut142;
    auto lut142idx0 = [](long I) -> long {
        /* GATE 476 (LUT2 _3612_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin142 = 1 * gout77[0] + 2 * gout19[1];
    std::vector<Ciphertext> gout142 = ctx.eval_lut_amortized(&gin142, lut142);

    std::vector<RotationPoly> lut143;
    std::vector<long (*)(long)> flut143;
    auto lut143idx0 = [](long I) -> long {
        /* GATE 115 (LUT2 _3251_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut143.push_back(ctx.genrate_lut(lut143idx0));
    flut143.push_back(lut143idx0);
    auto lut143idx1 = [](long I) -> long {
        /* GATE 155 (LUT2 _3291_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin143 = 1 * gout38[1] + 2 * ct_data164;
    std::vector<Ciphertext> gout143 = ctx.eval_lut_amortized(&gin143, lut143);

    std::vector<RotationPoly> lut144;
    std::vector<long (*)(long)> flut144;
    auto lut144idx0 = [](long I) -> long {
        /* GATE 540 (LUT2 _3676_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut144.push_back(ctx.genrate_lut(lut144idx0));
    flut144.push_back(lut144idx0);
    auto lut144idx1 = [](long I) -> long {
        /* GATE 505 (LUT2 _3641_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut144.push_back(ctx.genrate_lut(lut144idx1));
    flut144.push_back(lut144idx1);
    auto fvec144 = [flut144](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut144[i](I));
        return ret;
    };

    std::cerr << "\rLUT144   ";
    Ciphertext gin144 = 1 * gout84[1] + 2 * ct_data79;
    std::vector<Ciphertext> gout144 = ctx.eval_lut_amortized(&gin144, lut144);

    std::vector<RotationPoly> lut145;
    std::vector<long (*)(long)> flut145;
    auto lut145idx0 = [](long I) -> long {
        /* GATE 832 (LUT2 _3968_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut145.push_back(ctx.genrate_lut(lut145idx0));
    flut145.push_back(lut145idx0);
    auto lut145idx1 = [](long I) -> long {
        /* GATE 872 (LUT2 _4008_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin145 = 1 * gout89[1] + 2 * ct_data184;
    std::vector<Ciphertext> gout145 = ctx.eval_lut_amortized(&gin145, lut145);

    std::vector<RotationPoly> lut146;
    std::vector<long (*)(long)> flut146;
    auto lut146idx0 = [](long I) -> long {
        /* GATE 144 (LUT2 _3280_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut146.push_back(ctx.genrate_lut(lut146idx0));
    flut146.push_back(lut146idx0);
    auto lut146idx1 = [](long I) -> long {
        /* GATE 177 (LUT2 _3313_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin146 = 1 * gout127[0] + 2 * gout27[0];
    std::vector<Ciphertext> gout146 = ctx.eval_lut_amortized(&gin146, lut146);

    std::vector<RotationPoly> lut147;
    std::vector<long (*)(long)> flut147;
    auto lut147idx0 = [](long I) -> long {
        /* GATE 296 (LUT2 _3432_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut147.push_back(ctx.genrate_lut(lut147idx0));
    flut147.push_back(lut147idx0);
    auto lut147idx1 = [](long I) -> long {
        /* GATE 256 (LUT2 _3392_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin147 = 1 * gout45[1] + 2 * ct_data168;
    std::vector<Ciphertext> gout147 = ctx.eval_lut_amortized(&gin147, lut147);

    std::vector<RotationPoly> lut148;
    std::vector<long (*)(long)> flut148;
    auto lut148idx0 = [](long I) -> long {
        /* GATE 938 (LUT2 _4074_ INIT 0x6 PERM 01) */
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
        /* GATE 979 (LUT2 _4115_ INIT 0x8 PERM 01) */
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
    Ciphertext gin148 = 1 * gout80[0] + 2 * ct_data187;
    std::vector<Ciphertext> gout148 = ctx.eval_lut_amortized(&gin148, lut148);

    std::vector<RotationPoly> lut149;
    std::vector<long (*)(long)> flut149;
    auto lut149idx0 = [](long I) -> long {
        /* GATE 828 (LUT2 _3964_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut149.push_back(ctx.genrate_lut(lut149idx0));
    flut149.push_back(lut149idx0);
    auto lut149idx1 = [](long I) -> long {
        /* GATE 793 (LUT2 _3929_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin149 = 1 * gout72[0] + 2 * ct_data87;
    std::vector<Ciphertext> gout149 = ctx.eval_lut_amortized(&gin149, lut149);

    std::vector<RotationPoly> lut150;
    std::vector<long (*)(long)> flut150;
    auto lut150idx0 = [](long I) -> long {
        /* GATE 1014 (LUT2 _4150_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut150.push_back(ctx.genrate_lut(lut150idx0));
    flut150.push_back(lut150idx0);
    auto lut150idx1 = [](long I) -> long {
        /* GATE 974 (LUT2 _4110_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin150 = 1 * gout78[0] + 2 * ct_data188;
    std::vector<Ciphertext> gout150 = ctx.eval_lut_amortized(&gin150, lut150);

    std::vector<RotationPoly> lut151;
    std::vector<long (*)(long)> flut151;
    auto lut151idx0 = [](long I) -> long {
        /* GATE 37 (LUT2 _3173_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut151.push_back(ctx.genrate_lut(lut151idx0));
    flut151.push_back(lut151idx0);
    auto lut151idx1 = [](long I) -> long {
        /* GATE 15 (LUT2 _3151_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
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
    Ciphertext gin151 = 1 * gout109[0] + 2 * ct_data65;
    std::vector<Ciphertext> gout151 = ctx.eval_lut_amortized(&gin151, lut151);

    std::vector<RotationPoly> lut152;
    std::vector<long (*)(long)> flut152;
    auto lut152idx0 = [](long I) -> long {
        /* GATE 827 (LUT2 _3963_ INIT 0x1 PERM 01) */
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
    Ciphertext gin152 = 1 * gout149[0] + 2 * gout72[1];
    std::vector<Ciphertext> gout152 = ctx.eval_lut_amortized(&gin152, lut152);

    std::vector<RotationPoly> lut153;
    std::vector<long (*)(long)> flut153;
    auto lut153idx0 = [](long I) -> long {
        /* GATE 836 (LUT2 _3972_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin153 = 1 * gout49[1] + 2 * gout14[1];
    std::vector<Ciphertext> gout153 = ctx.eval_lut_amortized(&gin153, lut153);

    std::vector<RotationPoly> lut154;
    std::vector<long (*)(long)> flut154;
    auto lut154idx0 = [](long I) -> long {
        /* GATE 185 (LUT2 _3321_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut154.push_back(ctx.genrate_lut(lut154idx0));
    flut154.push_back(lut154idx0);
    auto lut154idx1 = [](long I) -> long {
        /* GATE 225 (LUT2 _3361_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
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
    Ciphertext gin154 = 1 * gout85[1] + 2 * ct_data166;
    std::vector<Ciphertext> gout154 = ctx.eval_lut_amortized(&gin154, lut154);

    std::vector<RotationPoly> lut155;
    std::vector<long (*)(long)> flut155;
    auto lut155idx0 = [](long I) -> long {
        /* GATE 286 (LUT2 _3422_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin155 = 1 * gout101[1] + 2 * gout32[1];
    std::vector<Ciphertext> gout155 = ctx.eval_lut_amortized(&gin155, lut155);

    std::vector<RotationPoly> lut156;
    std::vector<long (*)(long)> flut156;
    auto lut156idx0 = [](long I) -> long {
        /* GATE 444 (LUT2 _3580_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut156.push_back(ctx.genrate_lut(lut156idx0));
    flut156.push_back(lut156idx0);
    auto lut156idx1 = [](long I) -> long {
        /* GATE 403 (LUT2 _3539_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin156 = 1 * gout118[0] + 2 * ct_data204;
    std::vector<Ciphertext> gout156 = ctx.eval_lut_amortized(&gin156, lut156);

    std::vector<RotationPoly> lut157;
    std::vector<long (*)(long)> flut157;
    auto lut157idx0 = [](long I) -> long {
        /* GATE 333 (LUT2 _3469_ INIT 0x8 PERM 01) */
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
        /* GATE 291 (LUT2 _3427_ INIT 0x6 PERM 01) */
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
    Ciphertext gin157 = 1 * gout108[1] + 2 * ct_data169;
    std::vector<Ciphertext> gout157 = ctx.eval_lut_amortized(&gin157, lut157);

    std::vector<RotationPoly> lut158;
    std::vector<long (*)(long)> flut158;
    auto lut158idx0 = [](long I) -> long {
        /* GATE 826 (LUT2 _3962_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut158.push_back(ctx.genrate_lut(lut158idx0));
    flut158.push_back(lut158idx0);
    auto lut158idx1 = [](long I) -> long {
        /* GATE 859 (LUT2 _3995_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin158 = 1 * gout152[0] + 2 * gout79[0];
    std::vector<Ciphertext> gout158 = ctx.eval_lut_amortized(&gin158, lut158);

    std::vector<RotationPoly> lut159;
    std::vector<long (*)(long)> flut159;
    auto lut159idx0 = [](long I) -> long {
        /* GATE 295 (LUT2 _3431_ INIT 0x1 PERM 01) */
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
    Ciphertext gin159 = 1 * gout147[0] + 2 * gout45[0];
    std::vector<Ciphertext> gout159 = ctx.eval_lut_amortized(&gin159, lut159);

    std::vector<RotationPoly> lut160;
    std::vector<long (*)(long)> flut160;
    auto lut160idx0 = [](long I) -> long {
        /* GATE 26 (LUT2 _3162_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut160.push_back(ctx.genrate_lut(lut160idx0));
    flut160.push_back(lut160idx0);
    auto lut160idx1 = [](long I) -> long {
        /* GATE 20 (LUT2 _3156_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin160 = 1 * gout57[0] + 2 * ct_data160;
    std::vector<Ciphertext> gout160 = ctx.eval_lut_amortized(&gin160, lut160);

    std::vector<RotationPoly> lut161;
    std::vector<long (*)(long)> flut161;
    auto lut161idx0 = [](long I) -> long {
        /* GATE 479 (LUT2 _3615_ INIT 0x1 PERM 01) */
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
    Ciphertext gin161 = 1 * gout115[0] + 2 * gout92[0];
    std::vector<Ciphertext> gout161 = ctx.eval_lut_amortized(&gin161, lut161);

    std::vector<RotationPoly> lut162;
    std::vector<long (*)(long)> flut162;
    auto lut162idx0 = [](long I) -> long {
        /* GATE 394 (LUT2 _3530_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut162.push_back(ctx.genrate_lut(lut162idx0));
    flut162.push_back(lut162idx0);
    auto lut162idx1 = [](long I) -> long {
        /* GATE 427 (LUT2 _3563_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
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
    Ciphertext gin162 = 1 * gout114[0] + 2 * gout99[1];
    std::vector<Ciphertext> gout162 = ctx.eval_lut_amortized(&gin162, lut162);

    std::vector<RotationPoly> lut163;
    std::vector<long (*)(long)> flut163;
    auto lut163idx0 = [](long I) -> long {
        /* GATE 294 (LUT2 _3430_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut163.push_back(ctx.genrate_lut(lut163idx0));
    flut163.push_back(lut163idx0);
    auto lut163idx1 = [](long I) -> long {
        /* GATE 337 (LUT2 _3473_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin163 = 1 * gout159[0] + 2 * ct_data201;
    std::vector<Ciphertext> gout163 = ctx.eval_lut_amortized(&gin163, lut163);

    std::vector<RotationPoly> lut164;
    std::vector<long (*)(long)> flut164;
    auto lut164idx0 = [](long I) -> long {
        /* GATE 117 (LUT2 _3253_ INIT 0x6 PERM 01) */
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
        /* GATE 158 (LUT2 _3294_ INIT 0x8 PERM 01) */
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
    Ciphertext gin164 = 1 * gout112[1] + 2 * ct_data228;
    std::vector<Ciphertext> gout164 = ctx.eval_lut_amortized(&gin164, lut164);

    std::vector<RotationPoly> lut165;
    std::vector<long (*)(long)> flut165;
    auto lut165idx0 = [](long I) -> long {
        /* GATE 466 (LUT2 _3602_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut165.push_back(ctx.genrate_lut(lut165idx0));
    flut165.push_back(lut165idx0);
    auto lut165idx1 = [](long I) -> long {
        /* GATE 499 (LUT2 _3635_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin165 = 1 * gout139[0] + 2 * gout103[1];
    std::vector<Ciphertext> gout165 = ctx.eval_lut_amortized(&gin165, lut165);

    std::vector<RotationPoly> lut166;
    std::vector<long (*)(long)> flut166;
    auto lut166idx0 = [](long I) -> long {
        /* GATE 579 (LUT2 _3715_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut166.push_back(ctx.genrate_lut(lut166idx0));
    flut166.push_back(lut166idx0);
    auto lut166idx1 = [](long I) -> long {
        /* GATE 621 (LUT2 _3757_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin166 = 1 * gout104[0] + 2 * ct_data177;
    std::vector<Ciphertext> gout166 = ctx.eval_lut_amortized(&gin166, lut166);

    std::vector<RotationPoly> lut167;
    std::vector<long (*)(long)> flut167;
    auto lut167idx0 = [](long I) -> long {
        /* GATE 1003 (LUT2 _4139_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut167.push_back(ctx.genrate_lut(lut167idx0));
    flut167.push_back(lut167idx0);
    auto lut167idx1 = [](long I) -> long {
        /* GATE 1053 (LUT2 _4189_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
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
    Ciphertext gin167 = 1 * gout39[0] + 2 * gout51[0];
    std::vector<Ciphertext> gout167 = ctx.eval_lut_amortized(&gin167, lut167);

    std::vector<RotationPoly> lut168;
    std::vector<long (*)(long)> flut168;
    auto lut168idx0 = [](long I) -> long {
        /* GATE 901 (LUT2 _4037_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut168.push_back(ctx.genrate_lut(lut168idx0));
    flut168.push_back(lut168idx0);
    auto lut168idx1 = [](long I) -> long {
        /* GATE 934 (LUT2 _4070_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin168 = 1 * gout105[0] + 2 * ct_data90;
    std::vector<Ciphertext> gout168 = ctx.eval_lut_amortized(&gin168, lut168);

    std::vector<RotationPoly> lut169;
    std::vector<long (*)(long)> flut169;
    auto lut169idx0 = [](long I) -> long {
        /* GATE 1013 (LUT2 _4149_ INIT 0x1 PERM 01) */
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
    Ciphertext gin169 = 1 * gout150[0] + 2 * gout78[1];
    std::vector<Ciphertext> gout169 = ctx.eval_lut_amortized(&gin169, lut169);

    std::vector<RotationPoly> lut170;
    std::vector<long (*)(long)> flut170;
    auto lut170idx0 = [](long I) -> long {
        /* GATE 189 (LUT2 _3325_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin170 = 1 * gout55[1] + 2 * gout18[1];
    std::vector<Ciphertext> gout170 = ctx.eval_lut_amortized(&gin170, lut170);

    std::vector<RotationPoly> lut171;
    std::vector<long (*)(long)> flut171;
    auto lut171idx0 = [](long I) -> long {
        /* GATE 402 (LUT2 _3538_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut171.push_back(ctx.genrate_lut(lut171idx0));
    flut171.push_back(lut171idx0);
    auto lut171idx1 = [](long I) -> long {
        /* GATE 443 (LUT2 _3579_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin171 = 1 * gout156[1] + 2 * ct_data236;
    std::vector<Ciphertext> gout171 = ctx.eval_lut_amortized(&gin171, lut171);

    std::vector<RotationPoly> lut172;
    std::vector<long (*)(long)> flut172;
    auto lut172idx0 = [](long I) -> long {
        /* GATE 684 (LUT2 _3820_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut172.push_back(ctx.genrate_lut(lut172idx0));
    flut172.push_back(lut172idx0);
    auto lut172idx1 = [](long I) -> long {
        /* GATE 649 (LUT2 _3785_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin172 = 1 * gout82[1] + 2 * ct_data83;
    std::vector<Ciphertext> gout172 = ctx.eval_lut_amortized(&gin172, lut172);

    std::vector<RotationPoly> lut173;
    std::vector<long (*)(long)> flut173;
    auto lut173idx0 = [](long I) -> long {
        /* GATE 646 (LUT2 _3782_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin173 = 1 * gout95[1] + 2 * gout29[1];
    std::vector<Ciphertext> gout173 = ctx.eval_lut_amortized(&gin173, lut173);

    std::vector<RotationPoly> lut174;
    std::vector<long (*)(long)> flut174;
    auto lut174idx0 = [](long I) -> long {
        /* GATE 769 (LUT2 _3905_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut174.push_back(ctx.genrate_lut(lut174idx0));
    flut174.push_back(lut174idx0);
    auto lut174idx1 = [](long I) -> long {
        /* GATE 726 (LUT2 _3862_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin174 = 1 * gout76[0] + 2 * ct_data213;
    std::vector<Ciphertext> gout174 = ctx.eval_lut_amortized(&gin174, lut174);

    std::vector<RotationPoly> lut175;
    std::vector<long (*)(long)> flut175;
    auto lut175idx0 = [](long I) -> long {
        /* GATE 142 (LUT2 _3278_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut175.push_back(ctx.genrate_lut(lut175idx0));
    flut175.push_back(lut175idx0);
    auto lut175idx1 = [](long I) -> long {
        /* GATE 109 (LUT2 _3245_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut175.push_back(ctx.genrate_lut(lut175idx1));
    flut175.push_back(lut175idx1);
    auto fvec175 = [flut175](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut175[i](I));
        return ret;
    };

    std::cerr << "\rLUT175   ";
    Ciphertext gin175 = 1 * gout91[0] + 2 * gout110[0];
    std::vector<Ciphertext> gout175 = ctx.eval_lut_amortized(&gin175, lut175);

    std::vector<RotationPoly> lut176;
    std::vector<long (*)(long)> flut176;
    auto lut176idx0 = [](long I) -> long {
        /* GATE 731 (LUT2 _3867_ INIT 0x8 PERM 01) */
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
        /* GATE 690 (LUT2 _3826_ INIT 0x6 PERM 01) */
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
    Ciphertext gin176 = 1 * gout126[0] + 2 * ct_data244;
    std::vector<Ciphertext> gout176 = ctx.eval_lut_amortized(&gin176, lut176);

    std::vector<RotationPoly> lut177;
    std::vector<long (*)(long)> flut177;
    auto lut177idx0 = [](long I) -> long {
        /* GATE 475 (LUT2 _3611_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut177.push_back(ctx.genrate_lut(lut177idx0));
    flut177.push_back(lut177idx0);
    auto lut177idx1 = [](long I) -> long {
        /* GATE 516 (LUT2 _3652_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin177 = 1 * gout142[0] + 2 * ct_data206;
    std::vector<Ciphertext> gout177 = ctx.eval_lut_amortized(&gin177, lut177);

    std::vector<RotationPoly> lut178;
    std::vector<long (*)(long)> flut178;
    auto lut178idx0 = [](long I) -> long {
        /* GATE 655 (LUT2 _3791_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin178 = 1 * gout135[0] + 2 * gout61[1];
    std::vector<Ciphertext> gout178 = ctx.eval_lut_amortized(&gin178, lut178);

    std::vector<RotationPoly> lut179;
    std::vector<long (*)(long)> flut179;
    auto lut179idx0 = [](long I) -> long {
        /* GATE 428 (LUT2 _3564_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut179.push_back(ctx.genrate_lut(lut179idx0));
    flut179.push_back(lut179idx0);
    auto lut179idx1 = [](long I) -> long {
        /* GATE 463 (LUT2 _3599_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin179 = 1 * gout124[1] + 2 * gout77[1];
    std::vector<Ciphertext> gout179 = ctx.eval_lut_amortized(&gin179, lut179);

    std::vector<RotationPoly> lut180;
    std::vector<long (*)(long)> flut180;
    auto lut180idx0 = [](long I) -> long {
        /* GATE 324 (LUT2 _3460_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut180.push_back(ctx.genrate_lut(lut180idx0));
    flut180.push_back(lut180idx0);
    auto lut180idx1 = [](long I) -> long {
        /* GATE 289 (LUT2 _3425_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin180 = 1 * gout90[1] + 2 * ct_data73;
    std::vector<Ciphertext> gout180 = ctx.eval_lut_amortized(&gin180, lut180);

    std::vector<RotationPoly> lut181;
    std::vector<long (*)(long)> flut181;
    auto lut181idx0 = [](long I) -> long {
        /* GATE 36 (LUT2 _3172_ INIT 0x1 PERM 01) */
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
    Ciphertext gin181 = 1 * gout151[0] + 2 * gout109[1];
    std::vector<Ciphertext> gout181 = ctx.eval_lut_amortized(&gin181, lut181);

    std::vector<RotationPoly> lut182;
    std::vector<long (*)(long)> flut182;
    auto lut182idx0 = [](long I) -> long {
        /* GATE 64 (LUT2 _3200_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin182 = 1 * gout111[0] + 2 * gout22[1];
    std::vector<Ciphertext> gout182 = ctx.eval_lut_amortized(&gin182, lut182);

    std::vector<RotationPoly> lut183;
    std::vector<long (*)(long)> flut183;
    auto lut183idx0 = [](long I) -> long {
        /* GATE 332 (LUT2 _3468_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin183 = 1 * gout157[0] + 2 * gout108[0];
    std::vector<Ciphertext> gout183 = ctx.eval_lut_amortized(&gin183, lut183);

    std::vector<RotationPoly> lut184;
    std::vector<long (*)(long)> flut184;
    auto lut184idx0 = [](long I) -> long {
        /* GATE 502 (LUT2 _3638_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin184 = 1 * gout103[0] + 2 * gout43[1];
    std::vector<Ciphertext> gout184 = ctx.eval_lut_amortized(&gin184, lut184);

    std::vector<RotationPoly> lut185;
    std::vector<long (*)(long)> flut185;
    auto lut185idx0 = [](long I) -> long {
        /* GATE 1043 (LUT2 _4179_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin185 = 1 * gout88[0] + 2 * ct_data190;
    std::vector<Ciphertext> gout185 = ctx.eval_lut_amortized(&gin185, lut185);

    std::vector<RotationPoly> lut186;
    std::vector<long (*)(long)> flut186;
    auto lut186idx0 = [](long I) -> long {
        /* GATE 1036 (LUT2 _4172_ INIT 0x4 PERM 01) */
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
        /* GATE 1012 (LUT2 _4148_ INIT 0x9 PERM 01) */
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
    Ciphertext gin186 = 1 * gout169[0] + 2 * ct_data221;
    std::vector<Ciphertext> gout186 = ctx.eval_lut_amortized(&gin186, lut186);

    std::vector<RotationPoly> lut187;
    std::vector<long (*)(long)> flut187;
    auto lut187idx0 = [](long I) -> long {
        /* GATE 229 (LUT2 _3365_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut187.push_back(ctx.genrate_lut(lut187idx0));
    flut187.push_back(lut187idx0);
    auto lut187idx1 = [](long I) -> long {
        /* GATE 188 (LUT2 _3324_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin187 = 1 * gout170[0] + 2 * ct_data198;
    std::vector<Ciphertext> gout187 = ctx.eval_lut_amortized(&gin187, lut187);

    std::vector<RotationPoly> lut188;
    std::vector<long (*)(long)> flut188;
    auto lut188idx0 = [](long I) -> long {
        /* GATE 74 (LUT2 _3210_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut188.push_back(ctx.genrate_lut(lut188idx0));
    flut188.push_back(lut188idx0);
    auto lut188idx1 = [](long I) -> long {
        /* GATE 41 (LUT2 _3177_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin188 = 1 * gout96[1] + 2 * ct_data162;
    std::vector<Ciphertext> gout188 = ctx.eval_lut_amortized(&gin188, lut188);

    std::vector<RotationPoly> lut189;
    std::vector<long (*)(long)> flut189;
    auto lut189idx0 = [](long I) -> long {
        /* GATE 511 (LUT2 _3647_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin189 = 1 * gout119[0] + 2 * gout97[0];
    std::vector<Ciphertext> gout189 = ctx.eval_lut_amortized(&gin189, lut189);

    std::vector<RotationPoly> lut190;
    std::vector<long (*)(long)> flut190;
    auto lut190idx0 = [](long I) -> long {
        /* GATE 1052 (LUT2 _4188_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut190.push_back(ctx.genrate_lut(lut190idx0));
    flut190.push_back(lut190idx0);
    auto lut190idx1 = [](long I) -> long {
        /* GATE 1002 (LUT2 _4138_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin190 = 1 * gout167[0] + 2 * gout42[1];
    std::vector<Ciphertext> gout190 = ctx.eval_lut_amortized(&gin190, lut190);

    std::vector<RotationPoly> lut191;
    std::vector<long (*)(long)> flut191;
    auto lut191idx0 = [](long I) -> long {
        /* GATE 1042 (LUT2 _4178_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin191 = 1 * gout185[0] + 2 * gout75[0];
    std::vector<Ciphertext> gout191 = ctx.eval_lut_amortized(&gin191, lut191);

    std::vector<RotationPoly> lut192;
    std::vector<long (*)(long)> flut192;
    auto lut192idx0 = [](long I) -> long {
        /* GATE 358 (LUT2 _3494_ INIT 0x1 PERM 01) */
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
    Ciphertext gin192 = 1 * gout69[1] + 2 * gout23[1];
    std::vector<Ciphertext> gout192 = ctx.eval_lut_amortized(&gin192, lut192);

    std::vector<RotationPoly> lut193;
    std::vector<long (*)(long)> flut193;
    auto lut193idx0 = [](long I) -> long {
        /* GATE 643 (LUT2 _3779_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut193.push_back(ctx.genrate_lut(lut193idx0));
    flut193.push_back(lut193idx0);
    auto lut193idx1 = [](long I) -> long {
        /* GATE 610 (LUT2 _3746_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin193 = 1 * gout133[0] + 2 * gout95[0];
    std::vector<Ciphertext> gout193 = ctx.eval_lut_amortized(&gin193, lut193);

    std::vector<RotationPoly> lut194;
    std::vector<long (*)(long)> flut194;
    auto lut194idx0 = [](long I) -> long {
        /* GATE 539 (LUT2 _3675_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin194 = 1 * gout144[0] + 2 * gout84[0];
    std::vector<Ciphertext> gout194 = ctx.eval_lut_amortized(&gin194, lut194);

    std::vector<RotationPoly> lut195;
    std::vector<long (*)(long)> flut195;
    auto lut195idx0 = [](long I) -> long {
        /* GATE 787 (LUT2 _3923_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut195.push_back(ctx.genrate_lut(lut195idx0));
    flut195.push_back(lut195idx0);
    auto lut195idx1 = [](long I) -> long {
        /* GATE 754 (LUT2 _3890_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin195 = 1 * gout128[0] + 2 * gout65[0];
    std::vector<Ciphertext> gout195 = ctx.eval_lut_amortized(&gin195, lut195);

    std::vector<RotationPoly> lut196;
    std::vector<long (*)(long)> flut196;
    auto lut196idx0 = [](long I) -> long {
        /* GATE 300 (LUT2 _3436_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut196.push_back(ctx.genrate_lut(lut196idx0));
    flut196.push_back(lut196idx0);
    auto lut196idx1 = [](long I) -> long {
        /* GATE 259 (LUT2 _3395_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin196 = 1 * gout131[0] + 2 * ct_data200;
    std::vector<Ciphertext> gout196 = ctx.eval_lut_amortized(&gin196, lut196);

    std::vector<RotationPoly> lut197;
    std::vector<long (*)(long)> flut197;
    auto lut197idx0 = [](long I) -> long {
        /* GATE 367 (LUT2 _3503_ INIT 0x1 PERM 01) */
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
    Ciphertext gin197 = 1 * gout116[0] + 2 * gout37[1];
    std::vector<Ciphertext> gout197 = ctx.eval_lut_amortized(&gin197, lut197);

    std::vector<RotationPoly> lut198;
    std::vector<long (*)(long)> flut198;
    auto lut198idx0 = [](long I) -> long {
        /* GATE 1051 (LUT2 _4187_ INIT 0x1 PERM 01) */
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
    Ciphertext gin198 = 1 * gout190[0] + 2 * gout167[1];
    std::vector<Ciphertext> gout198 = ctx.eval_lut_amortized(&gin198, lut198);

    std::vector<RotationPoly> lut199;
    std::vector<long (*)(long)> flut199;
    auto lut199idx0 = [](long I) -> long {
        /* GATE 77 (LUT2 _3213_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut199.push_back(ctx.genrate_lut(lut199idx0));
    flut199.push_back(lut199idx0);
    auto lut199idx1 = [](long I) -> long {
        /* GATE 43 (LUT2 _3179_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin199 = 1 * gout134[1] + 2 * ct_data226;
    std::vector<Ciphertext> gout199 = ctx.eval_lut_amortized(&gin199, lut199);

    std::vector<RotationPoly> lut200;
    std::vector<long (*)(long)> flut200;
    auto lut200idx0 = [](long I) -> long {
        /* GATE 765 (LUT2 _3901_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut200.push_back(ctx.genrate_lut(lut200idx0));
    flut200.push_back(lut200idx0);
    auto lut200idx1 = [](long I) -> long {
        /* GATE 723 (LUT2 _3859_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut200.push_back(ctx.genrate_lut(lut200idx1));
    flut200.push_back(lut200idx1);
    auto fvec200 = [flut200](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut200[i](I));
        return ret;
    };

    std::cerr << "\rLUT200   ";
    Ciphertext gin200 = 1 * gout102[1] + 2 * ct_data181;
    std::vector<Ciphertext> gout200 = ctx.eval_lut_amortized(&gin200, lut200);

    std::vector<RotationPoly> lut201;
    std::vector<long (*)(long)> flut201;
    auto lut201idx0 = [](long I) -> long {
        /* GATE 683 (LUT2 _3819_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin201 = 1 * gout172[0] + 2 * gout82[0];
    std::vector<Ciphertext> gout201 = ctx.eval_lut_amortized(&gin201, lut201);

    std::vector<RotationPoly> lut202;
    std::vector<long (*)(long)> flut202;
    auto lut202idx0 = [](long I) -> long {
        /* GATE 862 (LUT2 _3998_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin202 = 1 * gout79[1] + 2 * gout36[1];
    std::vector<Ciphertext> gout202 = ctx.eval_lut_amortized(&gin202, lut202);

    std::vector<RotationPoly> lut203;
    std::vector<long (*)(long)> flut203;
    auto lut203idx0 = [](long I) -> long {
        /* GATE 871 (LUT2 _4007_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut203.push_back(ctx.genrate_lut(lut203idx0));
    flut203.push_back(lut203idx0);
    auto fvec203 = [flut203](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut203[i](I));
        return ret;
    };

    std::cerr << "\rLUT203   ";
    Ciphertext gin203 = 1 * gout145[1] + 2 * gout89[0];
    std::vector<Ciphertext> gout203 = ctx.eval_lut_amortized(&gin203, lut203);

    std::vector<RotationPoly> lut204;
    std::vector<long (*)(long)> flut204;
    auto lut204idx0 = [](long I) -> long {
        /* GATE 607 (LUT2 _3743_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut204.push_back(ctx.genrate_lut(lut204idx0));
    flut204.push_back(lut204idx0);
    auto lut204idx1 = [](long I) -> long {
        /* GATE 572 (LUT2 _3708_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin204 = 1 * gout132[0] + 2 * gout166[0];
    std::vector<Ciphertext> gout204 = ctx.eval_lut_amortized(&gin204, lut204);

    std::vector<RotationPoly> lut205;
    std::vector<long (*)(long)> flut205;
    auto lut205idx0 = [](long I) -> long {
        /* GATE 718 (LUT2 _3854_ INIT 0x1 PERM 01) */
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
    Ciphertext gin205 = 1 * gout94[0] + 2 * gout33[1];
    std::vector<Ciphertext> gout205 = ctx.eval_lut_amortized(&gin205, lut205);

    std::vector<RotationPoly> lut206;
    std::vector<long (*)(long)> flut206;
    auto lut206idx0 = [](long I) -> long {
        /* GATE 61 (LUT2 _3197_ INIT 0x4 PERM 01) */
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
        /* GATE 35 (LUT2 _3171_ INIT 0x9 PERM 01) */
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
    Ciphertext gin206 = 1 * gout181[0] + 2 * gout111[1];
    std::vector<Ciphertext> gout206 = ctx.eval_lut_amortized(&gin206, lut206);

    std::vector<RotationPoly> lut207;
    std::vector<long (*)(long)> flut207;
    auto lut207idx0 = [](long I) -> long {
        /* GATE 968 (LUT2 _4104_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut207.push_back(ctx.genrate_lut(lut207idx0));
    flut207.push_back(lut207idx0);
    auto lut207idx1 = [](long I) -> long {
        /* GATE 1001 (LUT2 _4137_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin207 = 1 * gout125[0] + 2 * gout7[0];
    std::vector<Ciphertext> gout207 = ctx.eval_lut_amortized(&gin207, lut207);

    std::vector<RotationPoly> lut208;
    std::vector<long (*)(long)> flut208;
    auto lut208idx0 = [](long I) -> long {
        /* GATE 176 (LUT2 _3312_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut208.push_back(ctx.genrate_lut(lut208idx0));
    flut208.push_back(lut208idx0);
    auto lut208idx1 = [](long I) -> long {
        /* GATE 143 (LUT2 _3279_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut208.push_back(ctx.genrate_lut(lut208idx1));
    flut208.push_back(lut208idx1);
    auto fvec208 = [flut208](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut208[i](I));
        return ret;
    };

    std::cerr << "\rLUT208   ";
    Ciphertext gin208 = 1 * gout146[0] + 2 * gout55[0];
    std::vector<Ciphertext> gout208 = ctx.eval_lut_amortized(&gin208, lut208);

    std::vector<RotationPoly> lut209;
    std::vector<long (*)(long)> flut209;
    auto lut209idx0 = [](long I) -> long {
        /* GATE 907 (LUT2 _4043_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin209 = 1 * gout140[1] + 2 * gout87[0];
    std::vector<Ciphertext> gout209 = ctx.eval_lut_amortized(&gin209, lut209);

    std::vector<RotationPoly> lut210;
    std::vector<long (*)(long)> flut210;
    auto lut210idx0 = [](long I) -> long {
        /* GATE 76 (LUT2 _3212_ INIT 0x1 PERM 01) */
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
    Ciphertext gin210 = 1 * gout199[0] + 2 * gout134[0];
    std::vector<Ciphertext> gout210 = ctx.eval_lut_amortized(&gin210, lut210);

    std::vector<RotationPoly> lut211;
    std::vector<long (*)(long)> flut211;
    auto lut211idx0 = [](long I) -> long {
        /* GATE 212 (LUT2 _3348_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut211.push_back(ctx.genrate_lut(lut211idx0));
    flut211.push_back(lut211idx0);
    auto lut211idx1 = [](long I) -> long {
        /* GATE 179 (LUT2 _3315_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut211.push_back(ctx.genrate_lut(lut211idx1));
    flut211.push_back(lut211idx1);
    auto fvec211 = [flut211](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut211[i](I));
        return ret;
    };

    std::cerr << "\rLUT211   ";
    Ciphertext gin211 = 1 * gout41[0] + 2 * gout120[0];
    std::vector<Ciphertext> gout211 = ctx.eval_lut_amortized(&gin211, lut211);

    std::vector<RotationPoly> lut212;
    std::vector<long (*)(long)> flut212;
    auto lut212idx0 = [](long I) -> long {
        /* GATE 215 (LUT2 _3351_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin212 = 1 * gout120[1] + 2 * gout48[1];
    std::vector<Ciphertext> gout212 = ctx.eval_lut_amortized(&gin212, lut212);

    std::vector<RotationPoly> lut213;
    std::vector<long (*)(long)> flut213;
    auto lut213idx0 = [](long I) -> long {
        /* GATE 841 (LUT2 _3977_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut213.push_back(ctx.genrate_lut(lut213idx0));
    flut213.push_back(lut213idx0);
    auto lut213idx1 = [](long I) -> long {
        /* GATE 798 (LUT2 _3934_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin213 = 1 * gout138[0] + 2 * ct_data215;
    std::vector<Ciphertext> gout213 = ctx.eval_lut_amortized(&gin213, lut213);

    std::vector<RotationPoly> lut214;
    std::vector<long (*)(long)> flut214;
    auto lut214idx0 = [](long I) -> long {
        /* GATE 224 (LUT2 _3360_ INIT 0x1 PERM 01) */
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
    Ciphertext gin214 = 1 * gout154[1] + 2 * gout85[0];
    std::vector<Ciphertext> gout214 = ctx.eval_lut_amortized(&gin214, lut214);

    std::vector<RotationPoly> lut215;
    std::vector<long (*)(long)> flut215;
    auto lut215idx0 = [](long I) -> long {
        /* GATE 320 (LUT2 _3456_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut215.push_back(ctx.genrate_lut(lut215idx0));
    flut215.push_back(lut215idx0);
    auto lut215idx1 = [](long I) -> long {
        /* GATE 285 (LUT2 _3421_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin215 = 1 * gout155[0] + 2 * gout180[1];
    std::vector<Ciphertext> gout215 = ctx.eval_lut_amortized(&gin215, lut215);

    std::vector<RotationPoly> lut216;
    std::vector<long (*)(long)> flut216;
    auto lut216idx0 = [](long I) -> long {
        /* GATE 609 (LUT2 _3745_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut216.push_back(ctx.genrate_lut(lut216idx0));
    flut216.push_back(lut216idx0);
    auto lut216idx1 = [](long I) -> long {
        /* GATE 642 (LUT2 _3778_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut216.push_back(ctx.genrate_lut(lut216idx1));
    flut216.push_back(lut216idx1);
    auto fvec216 = [flut216](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut216[i](I));
        return ret;
    };

    std::cerr << "\rLUT216   ";
    Ciphertext gin216 = 1 * gout193[1] + 2 * gout135[1];
    std::vector<Ciphertext> gout216 = ctx.eval_lut_amortized(&gin216, lut216);

    std::vector<RotationPoly> lut217;
    std::vector<long (*)(long)> flut217;
    auto lut217idx0 = [](long I) -> long {
        /* GATE 282 (LUT2 _3418_ INIT 0x8 PERM 01) */
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
        /* GATE 249 (LUT2 _3385_ INIT 0x6 PERM 01) */
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
    Ciphertext gin217 = 1 * gout130[1] + 2 * gout147[1];
    std::vector<Ciphertext> gout217 = ctx.eval_lut_amortized(&gin217, lut217);

    std::vector<RotationPoly> lut218;
    std::vector<long (*)(long)> flut218;
    auto lut218idx0 = [](long I) -> long {
        /* GATE 947 (LUT2 _4083_ INIT 0x4 PERM 01) */
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
        /* GATE 906 (LUT2 _4042_ INIT 0x9 PERM 01) */
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
    Ciphertext gin218 = 1 * gout209[0] + 2 * ct_data218;
    std::vector<Ciphertext> gout218 = ctx.eval_lut_amortized(&gin218, lut218);

    std::vector<RotationPoly> lut219;
    std::vector<long (*)(long)> flut219;
    auto lut219idx0 = [](long I) -> long {
        /* GATE 645 (LUT2 _3781_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut219.push_back(ctx.genrate_lut(lut219idx0));
    flut219.push_back(lut219idx0);
    auto lut219idx1 = [](long I) -> long {
        /* GATE 680 (LUT2 _3816_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin219 = 1 * gout173[0] + 2 * gout172[1];
    std::vector<Ciphertext> gout219 = ctx.eval_lut_amortized(&gin219, lut219);

    std::vector<RotationPoly> lut220;
    std::vector<long (*)(long)> flut220;
    auto lut220idx0 = [](long I) -> long {
        /* GATE 941 (LUT2 _4077_ INIT 0x9 PERM 01) */
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
        /* GATE 983 (LUT2 _4119_ INIT 0x4 PERM 01) */
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
    Ciphertext gin220 = 1 * gout122[0] + 2 * ct_data219;
    std::vector<Ciphertext> gout220 = ctx.eval_lut_amortized(&gin220, lut220);

    std::vector<RotationPoly> lut221;
    std::vector<long (*)(long)> flut221;
    auto lut221idx0 = [](long I) -> long {
        /* GATE 730 (LUT2 _3866_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin221 = 1 * gout176[0] + 2 * gout126[1];
    std::vector<Ciphertext> gout221 = ctx.eval_lut_amortized(&gin221, lut221);

    std::vector<RotationPoly> lut222;
    std::vector<long (*)(long)> flut222;
    auto lut222idx0 = [](long I) -> long {
        /* GATE 899 (LUT2 _4035_ INIT 0x8 PERM 01) */
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
        /* GATE 865 (LUT2 _4001_ INIT 0x6 PERM 01) */
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
    Ciphertext gin222 = 1 * gout107[0] + 2 * ct_data89;
    std::vector<Ciphertext> gout222 = ctx.eval_lut_amortized(&gin222, lut222);

    std::vector<RotationPoly> lut223;
    std::vector<long (*)(long)> flut223;
    auto lut223idx0 = [](long I) -> long {
        /* GATE 825 (LUT2 _3961_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut223.push_back(ctx.genrate_lut(lut223idx0));
    flut223.push_back(lut223idx0);
    auto lut223idx1 = [](long I) -> long {
        /* GATE 858 (LUT2 _3994_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut223.push_back(ctx.genrate_lut(lut223idx1));
    flut223.push_back(lut223idx1);
    auto fvec223 = [flut223](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut223[i](I));
        return ret;
    };

    std::cerr << "\rLUT223   ";
    Ciphertext gin223 = 1 * gout158[0] + 2 * gout145[0];
    std::vector<Ciphertext> gout223 = ctx.eval_lut_amortized(&gin223, lut223);

    std::vector<RotationPoly> lut224;
    std::vector<long (*)(long)> flut224;
    auto lut224idx0 = [](long I) -> long {
        /* GATE 10 (LUT2 _3146_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut224.push_back(ctx.genrate_lut(lut224idx0));
    flut224.push_back(lut224idx0);
    auto lut224idx1 = [](long I) -> long {
        /* GATE 33 (LUT2 _3169_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut224.push_back(ctx.genrate_lut(lut224idx1));
    flut224.push_back(lut224idx1);
    auto fvec224 = [flut224](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut224[i](I));
        return ret;
    };

    std::cerr << "\rLUT224   ";
    Ciphertext gin224 = 1 * gout44[0] + 2 * gout151[1];
    std::vector<Ciphertext> gout224 = ctx.eval_lut_amortized(&gin224, lut224);

    std::vector<RotationPoly> lut225;
    std::vector<long (*)(long)> flut225;
    auto lut225idx0 = [](long I) -> long {
        /* GATE 717 (LUT2 _3853_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut225.push_back(ctx.genrate_lut(lut225idx0));
    flut225.push_back(lut225idx0);
    auto lut225idx1 = [](long I) -> long {
        /* GATE 752 (LUT2 _3888_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
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
    Ciphertext gin225 = 1 * gout205[0] + 2 * gout46[1];
    std::vector<Ciphertext> gout225 = ctx.eval_lut_amortized(&gin225, lut225);

    std::vector<RotationPoly> lut226;
    std::vector<long (*)(long)> flut226;
    auto lut226idx0 = [](long I) -> long {
        /* GATE 393 (LUT2 _3529_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut226.push_back(ctx.genrate_lut(lut226idx0));
    flut226.push_back(lut226idx0);
    auto lut226idx1 = [](long I) -> long {
        /* GATE 426 (LUT2 _3562_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut226.push_back(ctx.genrate_lut(lut226idx1));
    flut226.push_back(lut226idx1);
    auto fvec226 = [flut226](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut226[i](I));
        return ret;
    };

    std::cerr << "\rLUT226   ";
    Ciphertext gin226 = 1 * gout162[0] + 2 * gout16[0];
    std::vector<Ciphertext> gout226 = ctx.eval_lut_amortized(&gin226, lut226);

    std::vector<RotationPoly> lut227;
    std::vector<long (*)(long)> flut227;
    auto lut227idx0 = [](long I) -> long {
        /* GATE 905 (LUT2 _4041_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut227.push_back(ctx.genrate_lut(lut227idx0));
    flut227.push_back(lut227idx0);
    auto lut227idx1 = [](long I) -> long {
        /* GATE 946 (LUT2 _4082_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
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
    Ciphertext gin227 = 1 * gout218[1] + 2 * ct_data250;
    std::vector<Ciphertext> gout227 = ctx.eval_lut_amortized(&gin227, lut227);

    std::vector<RotationPoly> lut228;
    std::vector<long (*)(long)> flut228;
    auto lut228idx0 = [](long I) -> long {
        /* GATE 465 (LUT2 _3601_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut228.push_back(ctx.genrate_lut(lut228idx0));
    flut228.push_back(lut228idx0);
    auto lut228idx1 = [](long I) -> long {
        /* GATE 498 (LUT2 _3634_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin228 = 1 * gout165[0] + 2 * gout119[1];
    std::vector<Ciphertext> gout228 = ctx.eval_lut_amortized(&gin228, lut228);

    std::vector<RotationPoly> lut229;
    std::vector<long (*)(long)> flut229;
    auto lut229idx0 = [](long I) -> long {
        /* GATE 945 (LUT2 _4081_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin229 = 1 * gout227[1] + 2 * gout218[0];
    std::vector<Ciphertext> gout229 = ctx.eval_lut_amortized(&gin229, lut229);

    std::vector<RotationPoly> lut230;
    std::vector<long (*)(long)> flut230;
    auto lut230idx0 = [](long I) -> long {
        /* GATE 336 (LUT2 _3472_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut230.push_back(ctx.genrate_lut(lut230idx0));
    flut230.push_back(lut230idx0);
    auto lut230idx1 = [](long I) -> long {
        /* GATE 293 (LUT2 _3429_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut230.push_back(ctx.genrate_lut(lut230idx1));
    flut230.push_back(lut230idx1);
    auto fvec230 = [flut230](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut230[i](I));
        return ret;
    };

    std::cerr << "\rLUT230   ";
    Ciphertext gin230 = 1 * gout163[0] + 2 * ct_data233;
    std::vector<Ciphertext> gout230 = ctx.eval_lut_amortized(&gin230, lut230);

    std::vector<RotationPoly> lut231;
    std::vector<long (*)(long)> flut231;
    auto lut231idx0 = [](long I) -> long {
        /* GATE 797 (LUT2 _3933_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut231.push_back(ctx.genrate_lut(lut231idx0));
    flut231.push_back(lut231idx0);
    auto lut231idx1 = [](long I) -> long {
        /* GATE 840 (LUT2 _3976_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
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
    Ciphertext gin231 = 1 * gout213[1] + 2 * ct_data247;
    std::vector<Ciphertext> gout231 = ctx.eval_lut_amortized(&gin231, lut231);

    std::vector<RotationPoly> lut232;
    std::vector<long (*)(long)> flut232;
    auto lut232idx0 = [](long I) -> long {
        /* GATE 357 (LUT2 _3493_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut232.push_back(ctx.genrate_lut(lut232idx0));
    flut232.push_back(lut232idx0);
    auto lut232idx1 = [](long I) -> long {
        /* GATE 392 (LUT2 _3528_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut232.push_back(ctx.genrate_lut(lut232idx1));
    flut232.push_back(lut232idx1);
    auto fvec232 = [flut232](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut232[i](I));
        return ret;
    };

    std::cerr << "\rLUT232   ";
    Ciphertext gin232 = 1 * gout192[0] + 2 * gout26[0];
    std::vector<Ciphertext> gout232 = ctx.eval_lut_amortized(&gin232, lut232);

    std::vector<RotationPoly> lut233;
    std::vector<long (*)(long)> flut233;
    auto lut233idx0 = [](long I) -> long {
        /* GATE 223 (LUT2 _3359_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut233.push_back(ctx.genrate_lut(lut233idx0));
    flut233.push_back(lut233idx0);
    auto lut233idx1 = [](long I) -> long {
        /* GATE 265 (LUT2 _3401_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut233.push_back(ctx.genrate_lut(lut233idx1));
    flut233.push_back(lut233idx1);
    auto fvec233 = [flut233](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut233[i](I));
        return ret;
    };

    std::cerr << "\rLUT233   ";
    Ciphertext gin233 = 1 * gout214[0] + 2 * ct_data199;
    std::vector<Ciphertext> gout233 = ctx.eval_lut_amortized(&gin233, lut233);

    std::vector<RotationPoly> lut234;
    std::vector<long (*)(long)> flut234;
    auto lut234idx0 = [](long I) -> long {
        /* GATE 442 (LUT2 _3578_ INIT 0x1 PERM 01) */
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
    Ciphertext gin234 = 1 * gout171[1] + 2 * gout156[0];
    std::vector<Ciphertext> gout234 = ctx.eval_lut_amortized(&gin234, lut234);

    std::vector<RotationPoly> lut235;
    std::vector<long (*)(long)> flut235;
    auto lut235idx0 = [](long I) -> long {
        /* GATE 583 (LUT2 _3719_ INIT 0x1 PERM 01) */
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
    Ciphertext gin235 = 1 * gout137[0] + 2 * gout52[0];
    std::vector<Ciphertext> gout235 = ctx.eval_lut_amortized(&gin235, lut235);

    std::vector<RotationPoly> lut236;
    std::vector<long (*)(long)> flut236;
    auto lut236idx0 = [](long I) -> long {
        /* GATE 553 (LUT2 _3689_ INIT 0x4 PERM 01) */
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
        /* GATE 510 (LUT2 _3646_ INIT 0x9 PERM 01) */
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
    Ciphertext gin236 = 1 * gout189[0] + 2 * ct_data207;
    std::vector<Ciphertext> gout236 = ctx.eval_lut_amortized(&gin236, lut236);

    std::vector<RotationPoly> lut237;
    std::vector<long (*)(long)> flut237;
    auto lut237idx0 = [](long I) -> long {
        /* GATE 933 (LUT2 _4069_ INIT 0x1 PERM 01) */
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
    Ciphertext gin237 = 1 * gout168[1] + 2 * gout105[1];
    std::vector<Ciphertext> gout237 = ctx.eval_lut_amortized(&gin237, lut237);

    std::vector<RotationPoly> lut238;
    std::vector<long (*)(long)> flut238;
    auto lut238idx0 = [](long I) -> long {
        /* GATE 515 (LUT2 _3651_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut238.push_back(ctx.genrate_lut(lut238idx0));
    flut238.push_back(lut238idx0);
    auto lut238idx1 = [](long I) -> long {
        /* GATE 474 (LUT2 _3610_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin238 = 1 * gout177[0] + 2 * ct_data238;
    std::vector<Ciphertext> gout238 = ctx.eval_lut_amortized(&gin238, lut238);

    std::vector<RotationPoly> lut239;
    std::vector<long (*)(long)> flut239;
    auto lut239idx0 = [](long I) -> long {
        /* GATE 1011 (LUT2 _4147_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut239.push_back(ctx.genrate_lut(lut239idx0));
    flut239.push_back(lut239idx0);
    auto lut239idx1 = [](long I) -> long {
        /* GATE 1035 (LUT2 _4171_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut239.push_back(ctx.genrate_lut(lut239idx1));
    flut239.push_back(lut239idx1);
    auto fvec239 = [flut239](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut239[i](I));
        return ret;
    };

    std::cerr << "\rLUT239   ";
    Ciphertext gin239 = 1 * gout186[1] + 2 * ct_data253;
    std::vector<Ciphertext> gout239 = ctx.eval_lut_amortized(&gin239, lut239);

    std::vector<RotationPoly> lut240;
    std::vector<long (*)(long)> flut240;
    auto lut240idx0 = [](long I) -> long {
        /* GATE 536 (LUT2 _3672_ INIT 0x4 PERM 01) */
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
        /* GATE 501 (LUT2 _3637_ INIT 0x9 PERM 01) */
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
    Ciphertext gin240 = 1 * gout184[0] + 2 * gout144[1];
    std::vector<Ciphertext> gout240 = ctx.eval_lut_amortized(&gin240, lut240);

    std::vector<RotationPoly> lut241;
    std::vector<long (*)(long)> flut241;
    auto lut241idx0 = [](long I) -> long {
        /* GATE 372 (LUT2 _3508_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut241.push_back(ctx.genrate_lut(lut241idx0));
    flut241.push_back(lut241idx0);
    auto lut241idx1 = [](long I) -> long {
        /* GATE 331 (LUT2 _3467_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin241 = 1 * gout183[0] + 2 * ct_data202;
    std::vector<Ciphertext> gout241 = ctx.eval_lut_amortized(&gin241, lut241);

    std::vector<RotationPoly> lut242;
    std::vector<long (*)(long)> flut242;
    auto lut242idx0 = [](long I) -> long {
        /* GATE 548 (LUT2 _3684_ INIT 0x1 PERM 01) */
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
    Ciphertext gin242 = 1 * gout141[0] + 2 * gout81[1];
    std::vector<Ciphertext> gout242 = ctx.eval_lut_amortized(&gin242, lut242);

    std::vector<RotationPoly> lut243;
    std::vector<long (*)(long)> flut243;
    auto lut243idx0 = [](long I) -> long {
        /* GATE 978 (LUT2 _4114_ INIT 0x1 PERM 01) */
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
    auto fvec243 = [flut243](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut243[i](I));
        return ret;
    };

    std::cerr << "\rLUT243   ";
    Ciphertext gin243 = 1 * gout148[1] + 2 * gout80[1];
    std::vector<Ciphertext> gout243 = ctx.eval_lut_amortized(&gin243, lut243);

    std::vector<RotationPoly> lut244;
    std::vector<long (*)(long)> flut244;
    auto lut244idx0 = [](long I) -> long {
        /* GATE 786 (LUT2 _3922_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut244.push_back(ctx.genrate_lut(lut244idx0));
    flut244.push_back(lut244idx0);
    auto lut244idx1 = [](long I) -> long {
        /* GATE 753 (LUT2 _3889_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin244 = 1 * gout195[1] + 2 * gout113[0];
    std::vector<Ciphertext> gout244 = ctx.eval_lut_amortized(&gin244, lut244);

    std::vector<RotationPoly> lut245;
    std::vector<long (*)(long)> flut245;
    auto lut245idx0 = [](long I) -> long {
        /* GATE 154 (LUT2 _3290_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin245 = 1 * gout143[1] + 2 * gout38[0];
    std::vector<Ciphertext> gout245 = ctx.eval_lut_amortized(&gin245, lut245);

    std::vector<RotationPoly> lut246;
    std::vector<long (*)(long)> flut246;
    auto lut246idx0 = [](long I) -> long {
        /* GATE 876 (LUT2 _4012_ INIT 0x4 PERM 01) */
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
        /* GATE 835 (LUT2 _3971_ INIT 0x9 PERM 01) */
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
    Ciphertext gin246 = 1 * gout153[0] + 2 * ct_data216;
    std::vector<Ciphertext> gout246 = ctx.eval_lut_amortized(&gin246, lut246);

    std::vector<RotationPoly> lut247;
    std::vector<long (*)(long)> flut247;
    auto lut247idx0 = [](long I) -> long {
        /* GATE 330 (LUT2 _3466_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut247.push_back(ctx.genrate_lut(lut247idx0));
    flut247.push_back(lut247idx0);
    auto lut247idx1 = [](long I) -> long {
        /* GATE 371 (LUT2 _3507_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut247.push_back(ctx.genrate_lut(lut247idx1));
    flut247.push_back(lut247idx1);
    auto fvec247 = [flut247](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut247[i](I));
        return ret;
    };

    std::cerr << "\rLUT247   ";
    Ciphertext gin247 = 1 * gout241[1] + 2 * ct_data234;
    std::vector<Ciphertext> gout247 = ctx.eval_lut_amortized(&gin247, lut247);

    std::vector<RotationPoly> lut248;
    std::vector<long (*)(long)> flut248;
    auto lut248idx0 = [](long I) -> long {
        /* GATE 764 (LUT2 _3900_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin248 = 1 * gout200[0] + 2 * gout102[0];
    std::vector<Ciphertext> gout248 = ctx.eval_lut_amortized(&gin248, lut248);

    std::vector<RotationPoly> lut249;
    std::vector<long (*)(long)> flut249;
    auto lut249idx0 = [](long I) -> long {
        /* GATE 248 (LUT2 _3384_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut249.push_back(ctx.genrate_lut(lut249idx0));
    flut249.push_back(lut249idx0);
    auto lut249idx1 = [](long I) -> long {
        /* GATE 214 (LUT2 _3350_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
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
    Ciphertext gin249 = 1 * gout212[0] + 2 * gout100[1];
    std::vector<Ciphertext> gout249 = ctx.eval_lut_amortized(&gin249, lut249);

    std::vector<RotationPoly> lut250;
    std::vector<long (*)(long)> flut250;
    auto lut250idx0 = [](long I) -> long {
        /* GATE 60 (LUT2 _3196_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut250.push_back(ctx.genrate_lut(lut250idx0));
    flut250.push_back(lut250idx0);
    auto lut250idx1 = [](long I) -> long {
        /* GATE 34 (LUT2 _3170_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin250 = 1 * gout206[1] + 2 * gout188[1];
    std::vector<Ciphertext> gout250 = ctx.eval_lut_amortized(&gin250, lut250);

    std::vector<RotationPoly> lut251;
    std::vector<long (*)(long)> flut251;
    auto lut251idx0 = [](long I) -> long {
        /* GATE 620 (LUT2 _3756_ INIT 0x1 PERM 01) */
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
    Ciphertext gin251 = 1 * gout166[1] + 2 * gout104[1];
    std::vector<Ciphertext> gout251 = ctx.eval_lut_amortized(&gin251, lut251);

    std::vector<RotationPoly> lut252;
    std::vector<long (*)(long)> flut252;
    auto lut252idx0 = [](long I) -> long {
        /* GATE 966 (LUT2 _4102_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut252.push_back(ctx.genrate_lut(lut252idx0));
    flut252.push_back(lut252idx0);
    auto lut252idx1 = [](long I) -> long {
        /* GATE 932 (LUT2 _4068_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut252.push_back(ctx.genrate_lut(lut252idx1));
    flut252.push_back(lut252idx1);
    auto fvec252 = [flut252](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut252[i](I));
        return ret;
    };

    std::cerr << "\rLUT252   ";
    Ciphertext gin252 = 1 * gout237[0] + 2 * gout74[1];
    std::vector<Ciphertext> gout252 = ctx.eval_lut_amortized(&gin252, lut252);

    std::vector<RotationPoly> lut253;
    std::vector<long (*)(long)> flut253;
    auto lut253idx0 = [](long I) -> long {
        /* GATE 108 (LUT2 _3244_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut253.push_back(ctx.genrate_lut(lut253idx0));
    flut253.push_back(lut253idx0);
    auto lut253idx1 = [](long I) -> long {
        /* GATE 141 (LUT2 _3277_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
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
    Ciphertext gin253 = 1 * gout175[1] + 2 * gout143[0];
    std::vector<Ciphertext> gout253 = ctx.eval_lut_amortized(&gin253, lut253);

    std::vector<RotationPoly> lut254;
    std::vector<long (*)(long)> flut254;
    auto lut254idx0 = [](long I) -> long {
        /* GATE 500 (LUT2 _3636_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut254.push_back(ctx.genrate_lut(lut254idx0));
    flut254.push_back(lut254idx0);
    auto lut254idx1 = [](long I) -> long {
        /* GATE 535 (LUT2 _3671_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin254 = 1 * gout240[1] + 2 * gout141[1];
    std::vector<Ciphertext> gout254 = ctx.eval_lut_amortized(&gin254, lut254);

    std::vector<RotationPoly> lut255;
    std::vector<long (*)(long)> flut255;
    auto lut255idx0 = [](long I) -> long {
        /* GATE 85 (LUT2 _3221_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut255.push_back(ctx.genrate_lut(lut255idx0));
    flut255.push_back(lut255idx0);
    auto lut255idx1 = [](long I) -> long {
        /* GATE 19 (LUT2 _3155_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
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
    Ciphertext gin255 = 1 * gout160[1] + 2 * gout15[0];
    std::vector<Ciphertext> gout255 = ctx.eval_lut_amortized(&gin255, lut255);

    std::vector<RotationPoly> lut256;
    std::vector<long (*)(long)> flut256;
    auto lut256idx0 = [](long I) -> long {
        /* GATE 211 (LUT2 _3347_ INIT 0x8 PERM 01) */
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
        /* GATE 178 (LUT2 _3314_ INIT 0x6 PERM 01) */
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
    Ciphertext gin256 = 1 * gout211[1] + 2 * gout154[0];
    std::vector<Ciphertext> gout256 = ctx.eval_lut_amortized(&gin256, lut256);

    std::vector<RotationPoly> lut257;
    std::vector<long (*)(long)> flut257;
    auto lut257idx0 = [](long I) -> long {
        /* GATE 768 (LUT2 _3904_ INIT 0x8 PERM 01) */
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
        /* GATE 725 (LUT2 _3861_ INIT 0x6 PERM 01) */
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
    Ciphertext gin257 = 1 * gout174[1] + 2 * ct_data245;
    std::vector<Ciphertext> gout257 = ctx.eval_lut_amortized(&gin257, lut257);

    std::vector<RotationPoly> lut258;
    std::vector<long (*)(long)> flut258;
    auto lut258idx0 = [](long I) -> long {
        /* GATE 789 (LUT2 _3925_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut258.push_back(ctx.genrate_lut(lut258idx0));
    flut258.push_back(lut258idx0);
    auto lut258idx1 = [](long I) -> long {
        /* GATE 824 (LUT2 _3960_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
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
    Ciphertext gin258 = 1 * gout136[0] + 2 * gout149[1];
    std::vector<Ciphertext> gout258 = ctx.eval_lut_amortized(&gin258, lut258);

    std::vector<RotationPoly> lut259;
    std::vector<long (*)(long)> flut259;
    auto lut259idx0 = [](long I) -> long {
        /* GATE 107 (LUT2 _3243_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut259.push_back(ctx.genrate_lut(lut259idx0));
    flut259.push_back(lut259idx0);
    auto lut259idx1 = [](long I) -> long {
        /* GATE 63 (LUT2 _3199_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut259.push_back(ctx.genrate_lut(lut259idx1));
    flut259.push_back(lut259idx1);
    auto fvec259 = [flut259](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut259[i](I));
        return ret;
    };

    std::cerr << "\rLUT259   ";
    Ciphertext gin259 = 1 * gout182[0] + 2 * gout25[1];
    std::vector<Ciphertext> gout259 = ctx.eval_lut_amortized(&gin259, lut259);

    std::vector<RotationPoly> lut260;
    std::vector<long (*)(long)> flut260;
    auto lut260idx0 = [](long I) -> long {
        /* GATE 281 (LUT2 _3417_ INIT 0x1 PERM 01) */
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
    Ciphertext gin260 = 1 * gout217[0] + 2 * gout130[0];
    std::vector<Ciphertext> gout260 = ctx.eval_lut_amortized(&gin260, lut260);

    std::vector<RotationPoly> lut261;
    std::vector<long (*)(long)> flut261;
    auto lut261idx0 = [](long I) -> long {
        /* GATE 299 (LUT2 _3435_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut261.push_back(ctx.genrate_lut(lut261idx0));
    flut261.push_back(lut261idx0);
    auto lut261idx1 = [](long I) -> long {
        /* GATE 258 (LUT2 _3394_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin261 = 1 * gout196[1] + 2 * ct_data232;
    std::vector<Ciphertext> gout261 = ctx.eval_lut_amortized(&gin261, lut261);

    std::vector<RotationPoly> lut262;
    std::vector<long (*)(long)> flut262;
    auto lut262idx0 = [](long I) -> long {
        /* GATE 606 (LUT2 _3742_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin262 = 1 * gout204[0] + 2 * gout132[1];
    std::vector<Ciphertext> gout262 = ctx.eval_lut_amortized(&gin262, lut262);

    std::vector<RotationPoly> lut263;
    std::vector<long (*)(long)> flut263;
    auto lut263idx0 = [](long I) -> long {
        /* GATE 228 (LUT2 _3364_ INIT 0x8 PERM 01) */
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
        /* GATE 187 (LUT2 _3323_ INIT 0x6 PERM 01) */
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
    Ciphertext gin263 = 1 * gout187[1] + 2 * ct_data230;
    std::vector<Ciphertext> gout263 = ctx.eval_lut_amortized(&gin263, lut263);

    std::vector<RotationPoly> lut264;
    std::vector<long (*)(long)> flut264;
    auto lut264idx0 = [](long I) -> long {
        /* GATE 157 (LUT2 _3293_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin264 = 1 * gout164[1] + 2 * gout112[0];
    std::vector<Ciphertext> gout264 = ctx.eval_lut_amortized(&gin264, lut264);

    std::vector<RotationPoly> lut265;
    std::vector<long (*)(long)> flut265;
    auto lut265idx0 = [](long I) -> long {
        /* GATE 298 (LUT2 _3434_ INIT 0x1 PERM 01) */
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
    Ciphertext gin265 = 1 * gout261[0] + 2 * gout196[0];
    std::vector<Ciphertext> gout265 = ctx.eval_lut_amortized(&gin265, lut265);

    std::vector<RotationPoly> lut266;
    std::vector<long (*)(long)> flut266;
    auto lut266idx0 = [](long I) -> long {
        /* GATE 175 (LUT2 _3311_ INIT 0x1 PERM 01) */
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
    auto fvec266 = [flut266](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut266[i](I));
        return ret;
    };

    std::cerr << "\rLUT266   ";
    Ciphertext gin266 = 1 * gout208[0] + 2 * gout146[1];
    std::vector<Ciphertext> gout266 = ctx.eval_lut_amortized(&gin266, lut266);

    std::vector<RotationPoly> lut267;
    std::vector<long (*)(long)> flut267;
    auto lut267idx0 = [](long I) -> long {
        /* GATE 25 (LUT2 _3161_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin267 = 1 * gout160[0] + 2 * gout57[1];
    std::vector<Ciphertext> gout267 = ctx.eval_lut_amortized(&gin267, lut267);

    std::vector<RotationPoly> lut268;
    std::vector<long (*)(long)> flut268;
    auto lut268idx0 = [](long I) -> long {
        /* GATE 715 (LUT2 _3851_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut268.push_back(ctx.genrate_lut(lut268idx0));
    flut268.push_back(lut268idx0);
    auto lut268idx1 = [](long I) -> long {
        /* GATE 682 (LUT2 _3818_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin268 = 1 * gout201[0] + 2 * gout94[1];
    std::vector<Ciphertext> gout268 = ctx.eval_lut_amortized(&gin268, lut268);

    std::vector<RotationPoly> lut269;
    std::vector<long (*)(long)> flut269;
    auto lut269idx0 = [](long I) -> long {
        /* GATE 24 (LUT2 _3160_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut269.push_back(ctx.genrate_lut(lut269idx0));
    flut269.push_back(lut269idx0);
    auto lut269idx1 = [](long I) -> long {
        /* GATE 50 (LUT2 _3186_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut269.push_back(ctx.genrate_lut(lut269idx1));
    flut269.push_back(lut269idx1);
    auto fvec269 = [flut269](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut269[i](I));
        return ret;
    };

    std::cerr << "\rLUT269   ";
    Ciphertext gin269 = 1 * gout267[0] + 2 * ct_data193;
    std::vector<Ciphertext> gout269 = ctx.eval_lut_amortized(&gin269, lut269);

    std::vector<RotationPoly> lut270;
    std::vector<long (*)(long)> flut270;
    auto lut270idx0 = [](long I) -> long {
        /* GATE 462 (LUT2 _3598_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin270 = 1 * gout179[1] + 2 * gout124[0];
    std::vector<Ciphertext> gout270 = ctx.eval_lut_amortized(&gin270, lut270);

    std::vector<RotationPoly> lut271;
    std::vector<long (*)(long)> flut271;
    auto lut271idx0 = [](long I) -> long {
        /* GATE 641 (LUT2 _3777_ INIT 0x1 PERM 01) */
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
    Ciphertext gin271 = 1 * gout216[1] + 2 * gout193[0];
    std::vector<Ciphertext> gout271 = ctx.eval_lut_amortized(&gin271, lut271);

    std::vector<RotationPoly> lut272;
    std::vector<long (*)(long)> flut272;
    auto lut272idx0 = [](long I) -> long {
        /* GATE 982 (LUT2 _4118_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut272.push_back(ctx.genrate_lut(lut272idx0));
    flut272.push_back(lut272idx0);
    auto lut272idx1 = [](long I) -> long {
        /* GATE 940 (LUT2 _4076_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin272 = 1 * gout220[0] + 2 * ct_data251;
    std::vector<Ciphertext> gout272 = ctx.eval_lut_amortized(&gin272, lut272);

    std::vector<RotationPoly> lut273;
    std::vector<long (*)(long)> flut273;
    auto lut273idx0 = [](long I) -> long {
        /* GATE 538 (LUT2 _3674_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut273.push_back(ctx.genrate_lut(lut273idx0));
    flut273.push_back(lut273idx0);
    auto lut273idx1 = [](long I) -> long {
        /* GATE 571 (LUT2 _3707_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin273 = 1 * gout194[0] + 2 * gout93[0];
    std::vector<Ciphertext> gout273 = ctx.eval_lut_amortized(&gin273, lut273);

    std::vector<RotationPoly> lut274;
    std::vector<long (*)(long)> flut274;
    auto lut274idx0 = [](long I) -> long {
        /* GATE 1018 (LUT2 _4154_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut274.push_back(ctx.genrate_lut(lut274idx0));
    flut274.push_back(lut274idx0);
    auto lut274idx1 = [](long I) -> long {
        /* GATE 977 (LUT2 _4113_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
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
    Ciphertext gin274 = 1 * gout243[0] + 2 * ct_data220;
    std::vector<Ciphertext> gout274 = ctx.eval_lut_amortized(&gin274, lut274);

    std::vector<RotationPoly> lut275;
    std::vector<long (*)(long)> flut275;
    auto lut275idx0 = [](long I) -> long {
        /* GATE 210 (LUT2 _3346_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin275 = 1 * gout256[0] + 2 * gout211[0];
    std::vector<Ciphertext> gout275 = ctx.eval_lut_amortized(&gin275, lut275);

    std::vector<RotationPoly> lut276;
    std::vector<long (*)(long)> flut276;
    auto lut276idx0 = [](long I) -> long {
        /* GATE 654 (LUT2 _3790_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut276.push_back(ctx.genrate_lut(lut276idx0));
    flut276.push_back(lut276idx0);
    auto lut276idx1 = [](long I) -> long {
        /* GATE 697 (LUT2 _3833_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut276.push_back(ctx.genrate_lut(lut276idx1));
    flut276.push_back(lut276idx1);
    auto fvec276 = [flut276](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut276[i](I));
        return ret;
    };

    std::cerr << "\rLUT276   ";
    Ciphertext gin276 = 1 * gout178[0] + 2 * ct_data211;
    std::vector<Ciphertext> gout276 = ctx.eval_lut_amortized(&gin276, lut276);

    std::vector<RotationPoly> lut277;
    std::vector<long (*)(long)> flut277;
    auto lut277idx0 = [](long I) -> long {
        /* GATE 497 (LUT2 _3633_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin277 = 1 * gout228[1] + 2 * gout165[1];
    std::vector<Ciphertext> gout277 = ctx.eval_lut_amortized(&gin277, lut277);

    std::vector<RotationPoly> lut278;
    std::vector<long (*)(long)> flut278;
    auto lut278idx0 = [](long I) -> long {
        /* GATE 1000 (LUT2 _4136_ INIT 0x8 PERM 01) */
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
        /* GATE 967 (LUT2 _4103_ INIT 0x6 PERM 01) */
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
    Ciphertext gin278 = 1 * gout207[0] + 2 * gout150[1];
    std::vector<Ciphertext> gout278 = ctx.eval_lut_amortized(&gin278, lut278);

    std::vector<RotationPoly> lut279;
    std::vector<long (*)(long)> flut279;
    auto lut279idx0 = [](long I) -> long {
        /* GATE 335 (LUT2 _3471_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin279 = 1 * gout230[0] + 2 * gout163[1];
    std::vector<Ciphertext> gout279 = ctx.eval_lut_amortized(&gin279, lut279);

    std::vector<RotationPoly> lut280;
    std::vector<long (*)(long)> flut280;
    auto lut280idx0 = [](long I) -> long {
        /* GATE 976 (LUT2 _4112_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut280.push_back(ctx.genrate_lut(lut280idx0));
    flut280.push_back(lut280idx0);
    auto lut280idx1 = [](long I) -> long {
        /* GATE 1017 (LUT2 _4153_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin280 = 1 * gout274[1] + 2 * ct_data252;
    std::vector<Ciphertext> gout280 = ctx.eval_lut_amortized(&gin280, lut280);

    std::vector<RotationPoly> lut281;
    std::vector<long (*)(long)> flut281;
    auto lut281idx0 = [](long I) -> long {
        /* GATE 679 (LUT2 _3815_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut281.push_back(ctx.genrate_lut(lut281idx0));
    flut281.push_back(lut281idx0);
    auto lut281idx1 = [](long I) -> long {
        /* GATE 644 (LUT2 _3780_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut281.push_back(ctx.genrate_lut(lut281idx1));
    flut281.push_back(lut281idx1);
    auto fvec281 = [flut281](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut281[i](I));
        return ret;
    };

    std::cerr << "\rLUT281   ";
    Ciphertext gin281 = 1 * gout219[0] + 2 * gout62[1];
    std::vector<Ciphertext> gout281 = ctx.eval_lut_amortized(&gin281, lut281);

    std::vector<RotationPoly> lut282;
    std::vector<long (*)(long)> flut282;
    auto lut282idx0 = [](long I) -> long {
        /* GATE 552 (LUT2 _3688_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut282.push_back(ctx.genrate_lut(lut282idx0));
    flut282.push_back(lut282idx0);
    auto lut282idx1 = [](long I) -> long {
        /* GATE 509 (LUT2 _3645_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
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
    Ciphertext gin282 = 1 * gout236[1] + 2 * ct_data239;
    std::vector<Ciphertext> gout282 = ctx.eval_lut_amortized(&gin282, lut282);

    std::vector<RotationPoly> lut283;
    std::vector<long (*)(long)> flut283;
    auto lut283idx0 = [](long I) -> long {
        /* GATE 284 (LUT2 _3420_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut283.push_back(ctx.genrate_lut(lut283idx0));
    flut283.push_back(lut283idx0);
    auto lut283idx1 = [](long I) -> long {
        /* GATE 319 (LUT2 _3455_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut283.push_back(ctx.genrate_lut(lut283idx1));
    flut283.push_back(lut283idx1);
    auto fvec283 = [flut283](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut283[i](I));
        return ret;
    };

    std::cerr << "\rLUT283   ";
    Ciphertext gin283 = 1 * gout215[1] + 2 * gout157[1];
    std::vector<Ciphertext> gout283 = ctx.eval_lut_amortized(&gin283, lut283);

    std::vector<RotationPoly> lut284;
    std::vector<long (*)(long)> flut284;
    auto lut284idx0 = [](long I) -> long {
        /* GATE 678 (LUT2 _3814_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin284 = 1 * gout281[0] + 2 * gout219[1];
    std::vector<Ciphertext> gout284 = ctx.eval_lut_amortized(&gin284, lut284);

    std::vector<RotationPoly> lut285;
    std::vector<long (*)(long)> flut285;
    auto lut285idx0 = [](long I) -> long {
        /* GATE 323 (LUT2 _3459_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin285 = 1 * gout180[0] + 2 * gout90[0];
    std::vector<Ciphertext> gout285 = ctx.eval_lut_amortized(&gin285, lut285);

    std::vector<RotationPoly> lut286;
    std::vector<long (*)(long)> flut286;
    auto lut286idx0 = [](long I) -> long {
        /* GATE 1034 (LUT2 _4170_ INIT 0x1 PERM 01) */
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
    Ciphertext gin286 = 1 * gout239[1] + 2 * gout186[0];
    std::vector<Ciphertext> gout286 = ctx.eval_lut_amortized(&gin286, lut286);

    std::vector<RotationPoly> lut287;
    std::vector<long (*)(long)> flut287;
    auto lut287idx0 = [](long I) -> long {
        /* GATE 222 (LUT2 _3358_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut287.push_back(ctx.genrate_lut(lut287idx0));
    flut287.push_back(lut287idx0);
    auto lut287idx1 = [](long I) -> long {
        /* GATE 264 (LUT2 _3400_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut287.push_back(ctx.genrate_lut(lut287idx1));
    flut287.push_back(lut287idx1);
    auto fvec287 = [flut287](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut287[i](I));
        return ret;
    };

    std::cerr << "\rLUT287   ";
    Ciphertext gin287 = 1 * gout233[0] + 2 * ct_data231;
    std::vector<Ciphertext> gout287 = ctx.eval_lut_amortized(&gin287, lut287);

    std::vector<RotationPoly> lut288;
    std::vector<long (*)(long)> flut288;
    auto lut288idx0 = [](long I) -> long {
        /* GATE 839 (LUT2 _3975_ INIT 0x1 PERM 01) */
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
    Ciphertext gin288 = 1 * gout231[1] + 2 * gout213[0];
    std::vector<Ciphertext> gout288 = ctx.eval_lut_amortized(&gin288, lut288);

    std::vector<RotationPoly> lut289;
    std::vector<long (*)(long)> flut289;
    auto lut289idx0 = [](long I) -> long {
        /* GATE 857 (LUT2 _3993_ INIT 0x1 PERM 01) */
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
    Ciphertext gin289 = 1 * gout223[1] + 2 * gout158[1];
    std::vector<Ciphertext> gout289 = ctx.eval_lut_amortized(&gin289, lut289);

    std::vector<RotationPoly> lut290;
    std::vector<long (*)(long)> flut290;
    auto lut290idx0 = [](long I) -> long {
        /* GATE 409 (LUT2 _3545_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut290.push_back(ctx.genrate_lut(lut290idx0));
    flut290.push_back(lut290idx0);
    auto lut290idx1 = [](long I) -> long {
        /* GATE 366 (LUT2 _3502_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin290 = 1 * gout197[0] + 2 * ct_data203;
    std::vector<Ciphertext> gout290 = ctx.eval_lut_amortized(&gin290, lut290);

    std::vector<RotationPoly> lut291;
    std::vector<long (*)(long)> flut291;
    auto lut291idx0 = [](long I) -> long {
        /* GATE 1033 (LUT2 _4169_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin291 = 1 * gout286[0] + 2 * gout73[0];
    std::vector<Ciphertext> gout291 = ctx.eval_lut_amortized(&gin291, lut291);

    std::vector<RotationPoly> lut292;
    std::vector<long (*)(long)> flut292;
    auto lut292idx0 = [](long I) -> long {
        /* GATE 315 (LUT2 _3451_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut292.push_back(ctx.genrate_lut(lut292idx0));
    flut292.push_back(lut292idx0);
    auto lut292idx1 = [](long I) -> long {
        /* GATE 280 (LUT2 _3416_ INIT 0x9 PERM 01) */
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
    Ciphertext gin292 = 1 * gout260[0] + 2 * gout283[0];
    std::vector<Ciphertext> gout292 = ctx.eval_lut_amortized(&gin292, lut292);

    std::vector<RotationPoly> lut293;
    std::vector<long (*)(long)> flut293;
    auto lut293idx0 = [](long I) -> long {
        /* GATE 73 (LUT2 _3209_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin293 = 1 * gout188[0] + 2 * gout96[0];
    std::vector<Ciphertext> gout293 = ctx.eval_lut_amortized(&gin293, lut293);

    std::vector<RotationPoly> lut294;
    std::vector<long (*)(long)> flut294;
    auto lut294idx0 = [](long I) -> long {
        /* GATE 1032 (LUT2 _4168_ INIT 0x6 PERM 01) */
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
    auto fvec294 = [flut294](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut294[i](I));
        return ret;
    };

    std::cerr << "\rLUT294   ";
    Ciphertext gin294 = 1 * gout291[0] + 2 * gout191[0];
    std::vector<Ciphertext> gout294 = ctx.eval_lut_amortized(&gin294, lut294);

    std::vector<RotationPoly> lut295;
    std::vector<long (*)(long)> flut295;
    auto lut295idx0 = [](long I) -> long {
        /* GATE 875 (LUT2 _4011_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut295.push_back(ctx.genrate_lut(lut295idx0));
    flut295.push_back(lut295idx0);
    auto lut295idx1 = [](long I) -> long {
        /* GATE 834 (LUT2 _3970_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut295.push_back(ctx.genrate_lut(lut295idx1));
    flut295.push_back(lut295idx1);
    auto fvec295 = [flut295](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut295[i](I));
        return ret;
    };

    std::cerr << "\rLUT295   ";
    Ciphertext gin295 = 1 * gout246[1] + 2 * ct_data248;
    std::vector<Ciphertext> gout295 = ctx.eval_lut_amortized(&gin295, lut295);

    std::vector<RotationPoly> lut296;
    std::vector<long (*)(long)> flut296;
    auto lut296idx0 = [](long I) -> long {
        /* GATE 1031 (LUT2 _4167_ INIT 0x9 PERM 01) */
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
    auto fvec296 = [flut296](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut296[i](I));
        return ret;
    };

    std::cerr << "\rLUT296   ";
    Ciphertext gin296 = 1 * gout294[0] + 2 * gout198[0];
    std::vector<Ciphertext> gout296 = ctx.eval_lut_amortized(&gin296, lut296);

    std::vector<RotationPoly> lut297;
    std::vector<long (*)(long)> flut297;
    auto lut297idx0 = [](long I) -> long {
        /* GATE 874 (LUT2 _4010_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin297 = 1 * gout295[0] + 2 * gout246[0];
    std::vector<Ciphertext> gout297 = ctx.eval_lut_amortized(&gin297, lut297);

    std::vector<RotationPoly> lut298;
    std::vector<long (*)(long)> flut298;
    auto lut298idx0 = [](long I) -> long {
        /* GATE 322 (LUT2 _3458_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut298.push_back(ctx.genrate_lut(lut298idx0));
    flut298.push_back(lut298idx0);
    auto lut298idx1 = [](long I) -> long {
        /* GATE 355 (LUT2 _3491_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin298 = 1 * gout285[0] + 2 * gout69[0];
    std::vector<Ciphertext> gout298 = ctx.eval_lut_amortized(&gin298, lut298);

    std::vector<RotationPoly> lut299;
    std::vector<long (*)(long)> flut299;
    auto lut299idx0 = [](long I) -> long {
        /* GATE 870 (LUT2 _4006_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut299.push_back(ctx.genrate_lut(lut299idx0));
    flut299.push_back(lut299idx0);
    auto lut299idx1 = [](long I) -> long {
        /* GATE 912 (LUT2 _4048_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin299 = 1 * gout203[0] + 2 * ct_data217;
    std::vector<Ciphertext> gout299 = ctx.eval_lut_amortized(&gin299, lut299);

    std::vector<RotationPoly> lut300;
    std::vector<long (*)(long)> flut300;
    auto lut300idx0 = [](long I) -> long {
        /* GATE 72 (LUT2 _3208_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut300.push_back(ctx.genrate_lut(lut300idx0));
    flut300.push_back(lut300idx0);
    auto lut300idx1 = [](long I) -> long {
        /* GATE 124 (LUT2 _3260_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut300.push_back(ctx.genrate_lut(lut300idx1));
    flut300.push_back(lut300idx1);
    auto fvec300 = [flut300](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut300[i](I));
        return ret;
    };

    std::cerr << "\rLUT300   ";
    Ciphertext gin300 = 1 * gout293[0] + 2 * ct_data195;
    std::vector<Ciphertext> gout300 = ctx.eval_lut_amortized(&gin300, lut300);

    std::vector<RotationPoly> lut301;
    std::vector<long (*)(long)> flut301;
    auto lut301idx0 = [](long I) -> long {
        /* GATE 62 (LUT2 _3198_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut301.push_back(ctx.genrate_lut(lut301idx0));
    flut301.push_back(lut301idx0);
    auto lut301idx1 = [](long I) -> long {
        /* GATE 106 (LUT2 _3242_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
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
    Ciphertext gin301 = 1 * gout259[1] + 2 * gout60[1];
    std::vector<Ciphertext> gout301 = ctx.eval_lut_amortized(&gin301, lut301);

    std::vector<RotationPoly> lut302;
    std::vector<long (*)(long)> flut302;
    auto lut302idx0 = [](long I) -> long {
        /* GATE 895 (LUT2 _4031_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut302.push_back(ctx.genrate_lut(lut302idx0));
    flut302.push_back(lut302idx0);
    auto lut302idx1 = [](long I) -> long {
        /* GATE 861 (LUT2 _3997_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin302 = 1 * gout202[0] + 2 * gout222[1];
    std::vector<Ciphertext> gout302 = ctx.eval_lut_amortized(&gin302, lut302);

    std::vector<RotationPoly> lut303;
    std::vector<long (*)(long)> flut303;
    auto lut303idx0 = [](long I) -> long {
        /* GATE 59 (LUT2 _3195_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin303 = 1 * gout250[0] + 2 * gout206[0];
    std::vector<Ciphertext> gout303 = ctx.eval_lut_amortized(&gin303, lut303);

    std::vector<RotationPoly> lut304;
    std::vector<long (*)(long)> flut304;
    auto lut304idx0 = [](long I) -> long {
        /* GATE 625 (LUT2 _3761_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut304.push_back(ctx.genrate_lut(lut304idx0));
    flut304.push_back(lut304idx0);
    auto lut304idx1 = [](long I) -> long {
        /* GATE 582 (LUT2 _3718_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin304 = 1 * gout235[0] + 2 * ct_data209;
    std::vector<Ciphertext> gout304 = ctx.eval_lut_amortized(&gin304, lut304);

    std::vector<RotationPoly> lut305;
    std::vector<long (*)(long)> flut305;
    auto lut305idx0 = [](long I) -> long {
        /* GATE 547 (LUT2 _3683_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut305.push_back(ctx.genrate_lut(lut305idx0));
    flut305.push_back(lut305idx0);
    auto lut305idx1 = [](long I) -> long {
        /* GATE 588 (LUT2 _3724_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut305.push_back(ctx.genrate_lut(lut305idx1));
    flut305.push_back(lut305idx1);
    auto fvec305 = [flut305](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut305[i](I));
        return ret;
    };

    std::cerr << "\rLUT305   ";
    Ciphertext gin305 = 1 * gout242[0] + 2 * ct_data208;
    std::vector<Ciphertext> gout305 = ctx.eval_lut_amortized(&gin305, lut305);

    std::vector<RotationPoly> lut306;
    std::vector<long (*)(long)> flut306;
    auto lut306idx0 = [](long I) -> long {
        /* GATE 898 (LUT2 _4034_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin306 = 1 * gout222[0] + 2 * gout107[1];
    std::vector<Ciphertext> gout306 = ctx.eval_lut_amortized(&gin306, lut306);

    std::vector<RotationPoly> lut307;
    std::vector<long (*)(long)> flut307;
    auto lut307idx0 = [](long I) -> long {
        /* GATE 194 (LUT2 _3330_ INIT 0x4 PERM 01) */
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
        /* GATE 153 (LUT2 _3289_ INIT 0x9 PERM 01) */
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
    Ciphertext gin307 = 1 * gout245[0] + 2 * ct_data197;
    std::vector<Ciphertext> gout307 = ctx.eval_lut_amortized(&gin307, lut307);

    std::vector<RotationPoly> lut308;
    std::vector<long (*)(long)> flut308;
    auto lut308idx0 = [](long I) -> long {
        /* GATE 534 (LUT2 _3670_ INIT 0x1 PERM 01) */
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
    Ciphertext gin308 = 1 * gout254[1] + 2 * gout240[0];
    std::vector<Ciphertext> gout308 = ctx.eval_lut_amortized(&gin308, lut308);

    std::vector<RotationPoly> lut309;
    std::vector<long (*)(long)> flut309;
    auto lut309idx0 = [](long I) -> long {
        /* GATE 9 (LUT2 _3145_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut309.push_back(ctx.genrate_lut(lut309idx0));
    flut309.push_back(lut309idx0);
    auto lut309idx1 = [](long I) -> long {
        /* GATE 32 (LUT2 _3168_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut309.push_back(ctx.genrate_lut(lut309idx1));
    flut309.push_back(lut309idx1);
    auto fvec309 = [flut309](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut309[i](I));
        return ret;
    };

    std::cerr << "\rLUT309   ";
    Ciphertext gin309 = 1 * gout224[0] + 2 * gout11[0];
    std::vector<Ciphertext> gout309 = ctx.eval_lut_amortized(&gin309, lut309);

    std::vector<RotationPoly> lut310;
    std::vector<long (*)(long)> flut310;
    auto lut310idx0 = [](long I) -> long {
        /* GATE 314 (LUT2 _3450_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut310.push_back(ctx.genrate_lut(lut310idx0));
    flut310.push_back(lut310idx0);
    auto lut310idx1 = [](long I) -> long {
        /* GATE 279 (LUT2 _3415_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
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
    Ciphertext gin310 = 1 * gout292[1] + 2 * gout230[1];
    std::vector<Ciphertext> gout310 = ctx.eval_lut_amortized(&gin310, lut310);

    std::vector<RotationPoly> lut311;
    std::vector<long (*)(long)> flut311;
    auto lut311idx0 = [](long I) -> long {
        /* GATE 174 (LUT2 _3310_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut311.push_back(ctx.genrate_lut(lut311idx0));
    flut311.push_back(lut311idx0);
    auto lut311idx1 = [](long I) -> long {
        /* GATE 207 (LUT2 _3343_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
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
    Ciphertext gin311 = 1 * gout266[0] + 2 * gout256[1];
    std::vector<Ciphertext> gout311 = ctx.eval_lut_amortized(&gin311, lut311);

    std::vector<RotationPoly> lut312;
    std::vector<long (*)(long)> flut312;
    auto lut312idx0 = [](long I) -> long {
        /* GATE 365 (LUT2 _3501_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut312.push_back(ctx.genrate_lut(lut312idx0));
    flut312.push_back(lut312idx0);
    auto lut312idx1 = [](long I) -> long {
        /* GATE 408 (LUT2 _3544_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin312 = 1 * gout290[1] + 2 * ct_data235;
    std::vector<Ciphertext> gout312 = ctx.eval_lut_amortized(&gin312, lut312);

    std::vector<RotationPoly> lut313;
    std::vector<long (*)(long)> flut313;
    auto lut313idx0 = [](long I) -> long {
        /* GATE 751 (LUT2 _3887_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut313.push_back(ctx.genrate_lut(lut313idx0));
    flut313.push_back(lut313idx0);
    auto lut313idx1 = [](long I) -> long {
        /* GATE 716 (LUT2 _3852_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut313.push_back(ctx.genrate_lut(lut313idx1));
    flut313.push_back(lut313idx1);
    auto fvec313 = [flut313](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut313[i](I));
        return ret;
    };

    std::cerr << "\rLUT313   ";
    Ciphertext gin313 = 1 * gout225[0] + 2 * gout200[1];
    std::vector<Ciphertext> gout313 = ctx.eval_lut_amortized(&gin313, lut313);

    std::vector<RotationPoly> lut314;
    std::vector<long (*)(long)> flut314;
    auto lut314idx0 = [](long I) -> long {
        /* GATE 370 (LUT2 _3506_ INIT 0x1 PERM 01) */
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
    Ciphertext gin314 = 1 * gout247[1] + 2 * gout241[0];
    std::vector<Ciphertext> gout314 = ctx.eval_lut_amortized(&gin314, lut314);

    std::vector<RotationPoly> lut315;
    std::vector<long (*)(long)> flut315;
    auto lut315idx0 = [](long I) -> long {
        /* GATE 823 (LUT2 _3959_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut315.push_back(ctx.genrate_lut(lut315idx0));
    flut315.push_back(lut315idx0);
    auto lut315idx1 = [](long I) -> long {
        /* GATE 788 (LUT2 _3924_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut315.push_back(ctx.genrate_lut(lut315idx1));
    flut315.push_back(lut315idx1);
    auto fvec315 = [flut315](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut315[i](I));
        return ret;
    };

    std::cerr << "\rLUT315   ";
    Ciphertext gin315 = 1 * gout258[0] + 2 * gout49[0];
    std::vector<Ciphertext> gout315 = ctx.eval_lut_amortized(&gin315, lut315);

    std::vector<RotationPoly> lut316;
    std::vector<long (*)(long)> flut316;
    auto lut316idx0 = [](long I) -> long {
        /* GATE 638 (LUT2 _3774_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut316.push_back(ctx.genrate_lut(lut316idx0));
    flut316.push_back(lut316idx0);
    auto lut316idx1 = [](long I) -> long {
        /* GATE 605 (LUT2 _3741_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut316.push_back(ctx.genrate_lut(lut316idx1));
    flut316.push_back(lut316idx1);
    auto fvec316 = [flut316](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut316[i](I));
        return ret;
    };

    std::cerr << "\rLUT316   ";
    Ciphertext gin316 = 1 * gout262[0] + 2 * gout216[0];
    std::vector<Ciphertext> gout316 = ctx.eval_lut_amortized(&gin316, lut316);

    std::vector<RotationPoly> lut317;
    std::vector<long (*)(long)> flut317;
    auto lut317idx0 = [](long I) -> long {
        /* GATE 391 (LUT2 _3527_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut317.push_back(ctx.genrate_lut(lut317idx0));
    flut317.push_back(lut317idx0);
    auto lut317idx1 = [](long I) -> long {
        /* GATE 356 (LUT2 _3492_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
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
    Ciphertext gin317 = 1 * gout232[0] + 2 * gout53[0];
    std::vector<Ciphertext> gout317 = ctx.eval_lut_amortized(&gin317, lut317);

    std::vector<RotationPoly> lut318;
    std::vector<long (*)(long)> flut318;
    auto lut318idx0 = [](long I) -> long {
        /* GATE 911 (LUT2 _4047_ INIT 0x8 PERM 01) */
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
        /* GATE 869 (LUT2 _4005_ INIT 0x6 PERM 01) */
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
    Ciphertext gin318 = 1 * gout299[0] + 2 * ct_data249;
    std::vector<Ciphertext> gout318 = ctx.eval_lut_amortized(&gin318, lut318);

    std::vector<RotationPoly> lut319;
    std::vector<long (*)(long)> flut319;
    auto lut319idx0 = [](long I) -> long {
        /* GATE 23 (LUT2 _3159_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut319.push_back(ctx.genrate_lut(lut319idx0));
    flut319.push_back(lut319idx0);
    auto lut319idx1 = [](long I) -> long {
        /* GATE 49 (LUT2 _3185_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut319.push_back(ctx.genrate_lut(lut319idx1));
    flut319.push_back(lut319idx1);
    auto fvec319 = [flut319](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut319[i](I));
        return ret;
    };

    std::cerr << "\rLUT319   ";
    Ciphertext gin319 = 1 * gout269[0] + 2 * ct_data225;
    std::vector<Ciphertext> gout319 = ctx.eval_lut_amortized(&gin319, lut319);

    std::vector<RotationPoly> lut320;
    std::vector<long (*)(long)> flut320;
    auto lut320idx0 = [](long I) -> long {
        /* GATE 390 (LUT2 _3526_ INIT 0x1 PERM 01) */
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
    Ciphertext gin320 = 1 * gout317[0] + 2 * gout232[1];
    std::vector<Ciphertext> gout320 = ctx.eval_lut_amortized(&gin320, lut320);

    std::vector<RotationPoly> lut321;
    std::vector<long (*)(long)> flut321;
    auto lut321idx0 = [](long I) -> long {
        /* GATE 247 (LUT2 _3383_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut321.push_back(ctx.genrate_lut(lut321idx0));
    flut321.push_back(lut321idx0);
    auto lut321idx1 = [](long I) -> long {
        /* GATE 213 (LUT2 _3349_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut321.push_back(ctx.genrate_lut(lut321idx1));
    flut321.push_back(lut321idx1);
    auto fvec321 = [flut321](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut321[i](I));
        return ret;
    };

    std::cerr << "\rLUT321   ";
    Ciphertext gin321 = 1 * gout249[1] + 2 * gout129[0];
    std::vector<Ciphertext> gout321 = ctx.eval_lut_amortized(&gin321, lut321);

    std::vector<RotationPoly> lut322;
    std::vector<long (*)(long)> flut322;
    auto lut322idx0 = [](long I) -> long {
        /* GATE 910 (LUT2 _4046_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin322 = 1 * gout318[0] + 2 * gout299[1];
    std::vector<Ciphertext> gout322 = ctx.eval_lut_amortized(&gin322, lut322);

    std::vector<RotationPoly> lut323;
    std::vector<long (*)(long)> flut323;
    auto lut323idx0 = [](long I) -> long {
        /* GATE 537 (LUT2 _3673_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut323.push_back(ctx.genrate_lut(lut323idx0));
    flut323.push_back(lut323idx0);
    auto lut323idx1 = [](long I) -> long {
        /* GATE 570 (LUT2 _3706_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
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
    Ciphertext gin323 = 1 * gout273[0] + 2 * gout137[1];
    std::vector<Ciphertext> gout323 = ctx.eval_lut_amortized(&gin323, lut323);

    std::vector<RotationPoly> lut324;
    std::vector<long (*)(long)> flut324;
    auto lut324idx0 = [](long I) -> long {
        /* GATE 389 (LUT2 _3525_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut324.push_back(ctx.genrate_lut(lut324idx0));
    flut324.push_back(lut324idx0);
    auto lut324idx1 = [](long I) -> long {
        /* GATE 422 (LUT2 _3558_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut324.push_back(ctx.genrate_lut(lut324idx1));
    flut324.push_back(lut324idx1);
    auto fvec324 = [flut324](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut324[i](I));
        return ret;
    };

    std::cerr << "\rLUT324   ";
    Ciphertext gin324 = 1 * gout320[0] + 2 * gout226[0];
    std::vector<Ciphertext> gout324 = ctx.eval_lut_amortized(&gin324, lut324);

    std::vector<RotationPoly> lut325;
    std::vector<long (*)(long)> flut325;
    auto lut325idx0 = [](long I) -> long {
        /* GATE 407 (LUT2 _3543_ INIT 0x1 PERM 01) */
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
    auto fvec325 = [flut325](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut325[i](I));
        return ret;
    };

    std::cerr << "\rLUT325   ";
    Ciphertext gin325 = 1 * gout312[1] + 2 * gout290[0];
    std::vector<Ciphertext> gout325 = ctx.eval_lut_amortized(&gin325, lut325);

    std::vector<RotationPoly> lut326;
    std::vector<long (*)(long)> flut326;
    auto lut326idx0 = [](long I) -> long {
        /* GATE 494 (LUT2 _3630_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut326.push_back(ctx.genrate_lut(lut326idx0));
    flut326.push_back(lut326idx0);
    auto lut326idx1 = [](long I) -> long {
        /* GATE 461 (LUT2 _3597_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut326.push_back(ctx.genrate_lut(lut326idx1));
    flut326.push_back(lut326idx1);
    auto fvec326 = [flut326](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut326[i](I));
        return ret;
    };

    std::cerr << "\rLUT326   ";
    Ciphertext gin326 = 1 * gout270[0] + 2 * gout228[0];
    std::vector<Ciphertext> gout326 = ctx.eval_lut_amortized(&gin326, lut326);

    std::vector<RotationPoly> lut327;
    std::vector<long (*)(long)> flut327;
    auto lut327idx0 = [](long I) -> long {
        /* GATE 425 (LUT2 _3561_ INIT 0x1 PERM 01) */
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
    Ciphertext gin327 = 1 * gout226[1] + 2 * gout162[1];
    std::vector<Ciphertext> gout327 = ctx.eval_lut_amortized(&gin327, lut327);

    std::vector<RotationPoly> lut328;
    std::vector<long (*)(long)> flut328;
    auto lut328idx0 = [](long I) -> long {
        /* GATE 105 (LUT2 _3241_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin328 = 1 * gout301[1] + 2 * gout259[0];
    std::vector<Ciphertext> gout328 = ctx.eval_lut_amortized(&gin328, lut328);

    std::vector<RotationPoly> lut329;
    std::vector<long (*)(long)> flut329;
    auto lut329idx0 = [](long I) -> long {
        /* GATE 246 (LUT2 _3382_ INIT 0x1 PERM 01) */
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
    Ciphertext gin329 = 1 * gout321[0] + 2 * gout249[0];
    std::vector<Ciphertext> gout329 = ctx.eval_lut_amortized(&gin329, lut329);

    std::vector<RotationPoly> lut330;
    std::vector<long (*)(long)> flut330;
    auto lut330idx0 = [](long I) -> long {
        /* GATE 227 (LUT2 _3363_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin330 = 1 * gout263[0] + 2 * gout187[0];
    std::vector<Ciphertext> gout330 = ctx.eval_lut_amortized(&gin330, lut330);

    std::vector<RotationPoly> lut331;
    std::vector<long (*)(long)> flut331;
    auto lut331idx0 = [](long I) -> long {
        /* GATE 140 (LUT2 _3276_ INIT 0x1 PERM 01) */
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
    Ciphertext gin331 = 1 * gout253[1] + 2 * gout175[0];
    std::vector<Ciphertext> gout331 = ctx.eval_lut_amortized(&gin331, lut331);

    std::vector<RotationPoly> lut332;
    std::vector<long (*)(long)> flut332;
    auto lut332idx0 = [](long I) -> long {
        /* GATE 84 (LUT2 _3220_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut332.push_back(ctx.genrate_lut(lut332idx0));
    flut332.push_back(lut332idx0);
    auto lut332idx1 = [](long I) -> long {
        /* GATE 1055 (LUT2 _4191_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
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
    Ciphertext gin332 = 1 * gout255[0] + 2 * gout50[1];
    std::vector<Ciphertext> gout332 = ctx.eval_lut_amortized(&gin332, lut332);

    std::vector<RotationPoly> lut333;
    std::vector<long (*)(long)> flut333;
    auto lut333idx0 = [](long I) -> long {
        /* GATE 750 (LUT2 _3886_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin333 = 1 * gout313[0] + 2 * gout225[1];
    std::vector<Ciphertext> gout333 = ctx.eval_lut_amortized(&gin333, lut333);

    std::vector<RotationPoly> lut334;
    std::vector<long (*)(long)> flut334;
    auto lut334idx0 = [](long I) -> long {
        /* GATE 514 (LUT2 _3650_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin334 = 1 * gout238[0] + 2 * gout177[1];
    std::vector<Ciphertext> gout334 = ctx.eval_lut_amortized(&gin334, lut334);

    std::vector<RotationPoly> lut335;
    std::vector<long (*)(long)> flut335;
    auto lut335idx0 = [](long I) -> long {
        /* GATE 660 (LUT2 _3796_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut335.push_back(ctx.genrate_lut(lut335idx0));
    flut335.push_back(lut335idx0);
    auto lut335idx1 = [](long I) -> long {
        /* GATE 619 (LUT2 _3755_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin335 = 1 * gout251[0] + 2 * ct_data210;
    std::vector<Ciphertext> gout335 = ctx.eval_lut_amortized(&gin335, lut335);

    std::vector<RotationPoly> lut336;
    std::vector<long (*)(long)> flut336;
    auto lut336idx0 = [](long I) -> long {
        /* GATE 767 (LUT2 _3903_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin336 = 1 * gout257[0] + 2 * gout174[0];
    std::vector<Ciphertext> gout336 = ctx.eval_lut_amortized(&gin336, lut336);

    std::vector<RotationPoly> lut337;
    std::vector<long (*)(long)> flut337;
    auto lut337idx0 = [](long I) -> long {
        /* GATE 714 (LUT2 _3850_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut337.push_back(ctx.genrate_lut(lut337idx0));
    flut337.push_back(lut337idx0);
    auto lut337idx1 = [](long I) -> long {
        /* GATE 681 (LUT2 _3817_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
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
    Ciphertext gin337 = 1 * gout268[1] + 2 * gout70[0];
    std::vector<Ciphertext> gout337 = ctx.eval_lut_amortized(&gin337, lut337);

    std::vector<RotationPoly> lut338;
    std::vector<long (*)(long)> flut338;
    auto lut338idx0 = [](long I) -> long {
        /* GATE 263 (LUT2 _3399_ INIT 0x1 PERM 01) */
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
    Ciphertext gin338 = 1 * gout287[1] + 2 * gout233[1];
    std::vector<Ciphertext> gout338 = ctx.eval_lut_amortized(&gin338, lut338);

    std::vector<RotationPoly> lut339;
    std::vector<long (*)(long)> flut339;
    auto lut339idx0 = [](long I) -> long {
        /* GATE 785 (LUT2 _3921_ INIT 0x1 PERM 01) */
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
    Ciphertext gin339 = 1 * gout244[0] + 2 * gout195[0];
    std::vector<Ciphertext> gout339 = ctx.eval_lut_amortized(&gin339, lut339);

    std::vector<RotationPoly> lut340;
    std::vector<long (*)(long)> flut340;
    auto lut340idx0 = [](long I) -> long {
        /* GATE 531 (LUT2 _3667_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut340.push_back(ctx.genrate_lut(lut340idx0));
    flut340.push_back(lut340idx0);
    auto lut340idx1 = [](long I) -> long {
        /* GATE 496 (LUT2 _3632_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut340.push_back(ctx.genrate_lut(lut340idx1));
    flut340.push_back(lut340idx1);
    auto fvec340 = [flut340](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut340[i](I));
        return ret;
    };

    std::cerr << "\rLUT340   ";
    Ciphertext gin340 = 1 * gout277[0] + 2 * gout254[0];
    std::vector<Ciphertext> gout340 = ctx.eval_lut_amortized(&gin340, lut340);

    std::vector<RotationPoly> lut341;
    std::vector<long (*)(long)> flut341;
    auto lut341idx0 = [](long I) -> long {
        /* GATE 804 (LUT2 _3940_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut341.push_back(ctx.genrate_lut(lut341idx0));
    flut341.push_back(lut341idx0);
    auto lut341idx1 = [](long I) -> long {
        /* GATE 763 (LUT2 _3899_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin341 = 1 * gout248[0] + 2 * ct_data214;
    std::vector<Ciphertext> gout341 = ctx.eval_lut_amortized(&gin341, lut341);

    std::vector<RotationPoly> lut342;
    std::vector<long (*)(long)> flut342;
    auto lut342idx0 = [](long I) -> long {
        /* GATE 354 (LUT2 _3490_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut342.push_back(ctx.genrate_lut(lut342idx0));
    flut342.push_back(lut342idx0);
    auto lut342idx1 = [](long I) -> long {
        /* GATE 321 (LUT2 _3457_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin342 = 1 * gout298[0] + 2 * gout116[1];
    std::vector<Ciphertext> gout342 = ctx.eval_lut_amortized(&gin342, lut342);

    std::vector<RotationPoly> lut343;
    std::vector<long (*)(long)> flut343;
    auto lut343idx0 = [](long I) -> long {
        /* GATE 243 (LUT2 _3379_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut343.push_back(ctx.genrate_lut(lut343idx0));
    flut343.push_back(lut343idx0);
    auto lut343idx1 = [](long I) -> long {
        /* GATE 209 (LUT2 _3345_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin343 = 1 * gout275[0] + 2 * gout321[1];
    std::vector<Ciphertext> gout343 = ctx.eval_lut_amortized(&gin343, lut343);

    std::vector<RotationPoly> lut344;
    std::vector<long (*)(long)> flut344;
    auto lut344idx0 = [](long I) -> long {
        /* GATE 193 (LUT2 _3329_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut344.push_back(ctx.genrate_lut(lut344idx0));
    flut344.push_back(lut344idx0);
    auto lut344idx1 = [](long I) -> long {
        /* GATE 152 (LUT2 _3288_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut344.push_back(ctx.genrate_lut(lut344idx1));
    flut344.push_back(lut344idx1);
    auto fvec344 = [flut344](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut344[i](I));
        return ret;
    };

    std::cerr << "\rLUT344   ";
    Ciphertext gin344 = 1 * gout307[1] + 2 * ct_data229;
    std::vector<Ciphertext> gout344 = ctx.eval_lut_amortized(&gin344, lut344);

    std::vector<RotationPoly> lut345;
    std::vector<long (*)(long)> flut345;
    auto lut345idx0 = [](long I) -> long {
        /* GATE 931 (LUT2 _4067_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut345.push_back(ctx.genrate_lut(lut345idx0));
    flut345.push_back(lut345idx0);
    auto lut345idx1 = [](long I) -> long {
        /* GATE 965 (LUT2 _4101_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin345 = 1 * gout252[1] + 2 * gout148[0];
    std::vector<Ciphertext> gout345 = ctx.eval_lut_amortized(&gin345, lut345);

    std::vector<RotationPoly> lut346;
    std::vector<long (*)(long)> flut346;
    auto lut346idx0 = [](long I) -> long {
        /* GATE 897 (LUT2 _4033_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut346.push_back(ctx.genrate_lut(lut346idx0));
    flut346.push_back(lut346idx0);
    auto lut346idx1 = [](long I) -> long {
        /* GATE 930 (LUT2 _4066_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin346 = 1 * gout306[0] + 2 * gout168[0];
    std::vector<Ciphertext> gout346 = ctx.eval_lut_amortized(&gin346, lut346);

    std::vector<RotationPoly> lut347;
    std::vector<long (*)(long)> flut347;
    auto lut347idx0 = [](long I) -> long {
        /* GATE 206 (LUT2 _3342_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut347.push_back(ctx.genrate_lut(lut347idx0));
    flut347.push_back(lut347idx0);
    auto lut347idx1 = [](long I) -> long {
        /* GATE 173 (LUT2 _3309_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
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
    Ciphertext gin347 = 1 * gout311[0] + 2 * gout263[1];
    std::vector<Ciphertext> gout347 = ctx.eval_lut_amortized(&gin347, lut347);

    std::vector<RotationPoly> lut348;
    std::vector<long (*)(long)> flut348;
    auto lut348idx0 = [](long I) -> long {
        /* GATE 964 (LUT2 _4100_ INIT 0x1 PERM 01) */
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
    Ciphertext gin348 = 1 * gout345[1] + 2 * gout252[0];
    std::vector<Ciphertext> gout348 = ctx.eval_lut_amortized(&gin348, lut348);

    std::vector<RotationPoly> lut349;
    std::vector<long (*)(long)> flut349;
    auto lut349idx0 = [](long I) -> long {
        /* GATE 102 (LUT2 _3238_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut349.push_back(ctx.genrate_lut(lut349idx0));
    flut349.push_back(lut349idx0);
    auto lut349idx1 = [](long I) -> long {
        /* GATE 58 (LUT2 _3194_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
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
    Ciphertext gin349 = 1 * gout303[0] + 2 * gout301[0];
    std::vector<Ciphertext> gout349 = ctx.eval_lut_amortized(&gin349, lut349);

    std::vector<RotationPoly> lut350;
    std::vector<long (*)(long)> flut350;
    auto lut350idx0 = [](long I) -> long {
        /* GATE 139 (LUT2 _3275_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut350.push_back(ctx.genrate_lut(lut350idx0));
    flut350.push_back(lut350idx0);
    auto lut350idx1 = [](long I) -> long {
        /* GATE 172 (LUT2 _3308_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
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
    Ciphertext gin350 = 1 * gout331[0] + 2 * gout208[1];
    std::vector<Ciphertext> gout350 = ctx.eval_lut_amortized(&gin350, lut350);

    std::vector<RotationPoly> lut351;
    std::vector<long (*)(long)> flut351;
    auto lut351idx0 = [](long I) -> long {
        /* GATE 551 (LUT2 _3687_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut351.push_back(ctx.genrate_lut(lut351idx0));
    flut351.push_back(lut351idx0);
    auto fvec351 = [flut351](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut351[i](I));
        return ret;
    };

    std::cerr << "\rLUT351   ";
    Ciphertext gin351 = 1 * gout282[0] + 2 * gout236[0];
    std::vector<Ciphertext> gout351 = ctx.eval_lut_amortized(&gin351, lut351);

    std::vector<RotationPoly> lut352;
    std::vector<long (*)(long)> flut352;
    auto lut352idx0 = [](long I) -> long {
        /* GATE 424 (LUT2 _3560_ INIT 0x9 PERM 01) */
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
        /* GATE 459 (LUT2 _3595_ INIT 0x4 PERM 01) */
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
    Ciphertext gin352 = 1 * gout327[0] + 2 * gout179[0];
    std::vector<Ciphertext> gout352 = ctx.eval_lut_amortized(&gin352, lut352);

    std::vector<RotationPoly> lut353;
    std::vector<long (*)(long)> flut353;
    auto lut353idx0 = [](long I) -> long {
        /* GATE 28 (LUT2 _3164_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut353.push_back(ctx.genrate_lut(lut353idx0));
    flut353.push_back(lut353idx0);
    auto lut353idx1 = [](long I) -> long {
        /* GATE 8 (LUT2 _3144_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut353.push_back(ctx.genrate_lut(lut353idx1));
    flut353.push_back(lut353idx1);
    auto fvec353 = [flut353](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut353[i](I));
        return ret;
    };

    std::cerr << "\rLUT353   ";
    Ciphertext gin353 = 1 * gout309[0] + 2 * gout255[1];
    std::vector<Ciphertext> gout353 = ctx.eval_lut_amortized(&gin353, lut353);

    std::vector<RotationPoly> lut354;
    std::vector<long (*)(long)> flut354;
    auto lut354idx0 = [](long I) -> long {
        /* GATE 981 (LUT2 _4117_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut354.push_back(ctx.genrate_lut(lut354idx0));
    flut354.push_back(lut354idx0);
    auto fvec354 = [flut354](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut354[i](I));
        return ret;
    };

    std::cerr << "\rLUT354   ";
    Ciphertext gin354 = 1 * gout272[0] + 2 * gout220[1];
    std::vector<Ciphertext> gout354 = ctx.eval_lut_amortized(&gin354, lut354);

    std::vector<RotationPoly> lut355;
    std::vector<long (*)(long)> flut355;
    auto lut355idx0 = [](long I) -> long {
        /* GATE 999 (LUT2 _4135_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut355.push_back(ctx.genrate_lut(lut355idx0));
    flut355.push_back(lut355idx0);
    auto fvec355 = [flut355](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut355[i](I));
        return ret;
    };

    std::cerr << "\rLUT355   ";
    Ciphertext gin355 = 1 * gout278[0] + 2 * gout207[1];
    std::vector<Ciphertext> gout355 = ctx.eval_lut_amortized(&gin355, lut355);

    std::vector<RotationPoly> lut356;
    std::vector<long (*)(long)> flut356;
    auto lut356idx0 = [](long I) -> long {
        /* GATE 819 (LUT2 _3955_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut356.push_back(ctx.genrate_lut(lut356idx0));
    flut356.push_back(lut356idx0);
    auto lut356idx1 = [](long I) -> long {
        /* GATE 784 (LUT2 _3920_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
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
    Ciphertext gin356 = 1 * gout339[0] + 2 * gout315[1];
    std::vector<Ciphertext> gout356 = ctx.eval_lut_amortized(&gin356, lut356);

    std::vector<RotationPoly> lut357;
    std::vector<long (*)(long)> flut357;
    auto lut357idx0 = [](long I) -> long {
        /* GATE 618 (LUT2 _3754_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut357.push_back(ctx.genrate_lut(lut357idx0));
    flut357.push_back(lut357idx0);
    auto lut357idx1 = [](long I) -> long {
        /* GATE 659 (LUT2 _3795_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut357.push_back(ctx.genrate_lut(lut357idx1));
    flut357.push_back(lut357idx1);
    auto fvec357 = [flut357](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut357[i](I));
        return ret;
    };

    std::cerr << "\rLUT357   ";
    Ciphertext gin357 = 1 * gout335[1] + 2 * ct_data242;
    std::vector<Ciphertext> gout357 = ctx.eval_lut_amortized(&gin357, lut357);

    std::vector<RotationPoly> lut358;
    std::vector<long (*)(long)> flut358;
    auto lut358idx0 = [](long I) -> long {
        /* GATE 1016 (LUT2 _4152_ INIT 0x1 PERM 01) */
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
    Ciphertext gin358 = 1 * gout280[1] + 2 * gout274[0];
    std::vector<Ciphertext> gout358 = ctx.eval_lut_amortized(&gin358, lut358);

    std::vector<RotationPoly> lut359;
    std::vector<long (*)(long)> flut359;
    auto lut359idx0 = [](long I) -> long {
        /* GATE 696 (LUT2 _3832_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut359.push_back(ctx.genrate_lut(lut359idx0));
    flut359.push_back(lut359idx0);
    auto lut359idx1 = [](long I) -> long {
        /* GATE 653 (LUT2 _3789_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut359.push_back(ctx.genrate_lut(lut359idx1));
    flut359.push_back(lut359idx1);
    auto fvec359 = [flut359](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut359[i](I));
        return ret;
    };

    std::cerr << "\rLUT359   ";
    Ciphertext gin359 = 1 * gout276[0] + 2 * ct_data243;
    std::vector<Ciphertext> gout359 = ctx.eval_lut_amortized(&gin359, lut359);

    std::vector<RotationPoly> lut360;
    std::vector<long (*)(long)> flut360;
    auto lut360idx0 = [](long I) -> long {
        /* GATE 749 (LUT2 _3885_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut360.push_back(ctx.genrate_lut(lut360idx0));
    flut360.push_back(lut360idx0);
    auto lut360idx1 = [](long I) -> long {
        /* GATE 782 (LUT2 _3918_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut360.push_back(ctx.genrate_lut(lut360idx1));
    flut360.push_back(lut360idx1);
    auto fvec360 = [flut360](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut360[i](I));
        return ret;
    };

    std::cerr << "\rLUT360   ";
    Ciphertext gin360 = 1 * gout333[0] + 2 * gout244[1];
    std::vector<Ciphertext> gout360 = ctx.eval_lut_amortized(&gin360, lut360);

    std::vector<RotationPoly> lut361;
    std::vector<long (*)(long)> flut361;
    auto lut361idx0 = [](long I) -> long {
        /* GATE 533 (LUT2 _3669_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut361.push_back(ctx.genrate_lut(lut361idx0));
    flut361.push_back(lut361idx0);
    auto lut361idx1 = [](long I) -> long {
        /* GATE 566 (LUT2 _3702_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
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
    Ciphertext gin361 = 1 * gout308[0] + 2 * gout323[0];
    std::vector<Ciphertext> gout361 = ctx.eval_lut_amortized(&gin361, lut361);

    std::vector<RotationPoly> lut362;
    std::vector<long (*)(long)> flut362;
    auto lut362idx0 = [](long I) -> long {
        /* GATE 421 (LUT2 _3557_ INIT 0x8 PERM 01) */
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
        /* GATE 388 (LUT2 _3524_ INIT 0x6 PERM 01) */
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
    Ciphertext gin362 = 1 * gout324[0] + 2 * gout171[0];
    std::vector<Ciphertext> gout362 = ctx.eval_lut_amortized(&gin362, lut362);

    std::vector<RotationPoly> lut363;
    std::vector<long (*)(long)> flut363;
    auto lut363idx0 = [](long I) -> long {
        /* GATE 569 (LUT2 _3705_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut363.push_back(ctx.genrate_lut(lut363idx0));
    flut363.push_back(lut363idx0);
    auto fvec363 = [flut363](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut363[i](I));
        return ret;
    };

    std::cerr << "\rLUT363   ";
    Ciphertext gin363 = 1 * gout323[1] + 2 * gout273[1];
    std::vector<Ciphertext> gout363 = ctx.eval_lut_amortized(&gin363, lut363);

    std::vector<RotationPoly> lut364;
    std::vector<long (*)(long)> flut364;
    auto lut364idx0 = [](long I) -> long {
        /* GATE 278 (LUT2 _3414_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut364.push_back(ctx.genrate_lut(lut364idx0));
    flut364.push_back(lut364idx0);
    auto lut364idx1 = [](long I) -> long {
        /* GATE 245 (LUT2 _3381_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut364.push_back(ctx.genrate_lut(lut364idx1));
    flut364.push_back(lut364idx1);
    auto fvec364 = [flut364](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut364[i](I));
        return ret;
    };

    std::cerr << "\rLUT364   ";
    Ciphertext gin364 = 1 * gout329[0] + 2 * gout217[1];
    std::vector<Ciphertext> gout364 = ctx.eval_lut_amortized(&gin364, lut364);

    std::vector<RotationPoly> lut365;
    std::vector<long (*)(long)> flut365;
    auto lut365idx0 = [](long I) -> long {
        /* GATE 318 (LUT2 _3454_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut365.push_back(ctx.genrate_lut(lut365idx0));
    flut365.push_back(lut365idx0);
    auto fvec365 = [flut365](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut365[i](I));
        return ret;
    };

    std::cerr << "\rLUT365   ";
    Ciphertext gin365 = 1 * gout283[1] + 2 * gout215[0];
    std::vector<Ciphertext> gout365 = ctx.eval_lut_amortized(&gin365, lut365);

    std::vector<RotationPoly> lut366;
    std::vector<long (*)(long)> flut366;
    auto lut366idx0 = [](long I) -> long {
        /* GATE 894 (LUT2 _4030_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut366.push_back(ctx.genrate_lut(lut366idx0));
    flut366.push_back(lut366idx0);
    auto lut366idx1 = [](long I) -> long {
        /* GATE 860 (LUT2 _3996_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
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
    Ciphertext gin366 = 1 * gout302[1] + 2 * gout140[0];
    std::vector<Ciphertext> gout366 = ctx.eval_lut_amortized(&gin366, lut366);

    std::vector<RotationPoly> lut367;
    std::vector<long (*)(long)> flut367;
    auto lut367idx0 = [](long I) -> long {
        /* GATE 31 (LUT2 _3167_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut367.push_back(ctx.genrate_lut(lut367idx0));
    flut367.push_back(lut367idx0);
    auto fvec367 = [flut367](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut367[i](I));
        return ret;
    };

    std::cerr << "\rLUT367   ";
    Ciphertext gin367 = 1 * gout309[1] + 2 * gout224[1];
    std::vector<Ciphertext> gout367 = ctx.eval_lut_amortized(&gin367, lut367);

    std::vector<RotationPoly> lut368;
    std::vector<long (*)(long)> flut368;
    auto lut368idx0 = [](long I) -> long {
        /* GATE 658 (LUT2 _3794_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut368.push_back(ctx.genrate_lut(lut368idx0));
    flut368.push_back(lut368idx0);
    auto fvec368 = [flut368](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut368[i](I));
        return ret;
    };

    std::cerr << "\rLUT368   ";
    Ciphertext gin368 = 1 * gout357[1] + 2 * gout335[0];
    std::vector<Ciphertext> gout368 = ctx.eval_lut_amortized(&gin368, lut368);

    std::vector<RotationPoly> lut369;
    std::vector<long (*)(long)> flut369;
    auto lut369idx0 = [](long I) -> long {
        /* GATE 640 (LUT2 _3776_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut369.push_back(ctx.genrate_lut(lut369idx0));
    flut369.push_back(lut369idx0);
    auto lut369idx1 = [](long I) -> long {
        /* GATE 675 (LUT2 _3811_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin369 = 1 * gout271[0] + 2 * gout281[1];
    std::vector<Ciphertext> gout369 = ctx.eval_lut_amortized(&gin369, lut369);

    std::vector<RotationPoly> lut370;
    std::vector<long (*)(long)> flut370;
    auto lut370idx0 = [](long I) -> long {
        /* GATE 123 (LUT2 _3259_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut370.push_back(ctx.genrate_lut(lut370idx0));
    flut370.push_back(lut370idx0);
    auto lut370idx1 = [](long I) -> long {
        /* GATE 71 (LUT2 _3207_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
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
    Ciphertext gin370 = 1 * gout300[0] + 2 * ct_data227;
    std::vector<Ciphertext> gout370 = ctx.eval_lut_amortized(&gin370, lut370);

    std::vector<RotationPoly> lut371;
    std::vector<long (*)(long)> flut371;
    auto lut371idx0 = [](long I) -> long {
        /* GATE 929 (LUT2 _4065_ INIT 0x8 PERM 01) */
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
        /* GATE 896 (LUT2 _4032_ INIT 0x6 PERM 01) */
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
    Ciphertext gin371 = 1 * gout346[0] + 2 * gout86[0];
    std::vector<Ciphertext> gout371 = ctx.eval_lut_amortized(&gin371, lut371);

    std::vector<RotationPoly> lut372;
    std::vector<long (*)(long)> flut372;
    auto lut372idx0 = [](long I) -> long {
        /* GATE 963 (LUT2 _4099_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut372.push_back(ctx.genrate_lut(lut372idx0));
    flut372.push_back(lut372idx0);
    auto lut372idx1 = [](long I) -> long {
        /* GATE 996 (LUT2 _4132_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut372.push_back(ctx.genrate_lut(lut372idx1));
    flut372.push_back(lut372idx1);
    auto fvec372 = [flut372](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut372[i](I));
        return ret;
    };

    std::cerr << "\rLUT372   ";
    Ciphertext gin372 = 1 * gout348[0] + 2 * gout278[1];
    std::vector<Ciphertext> gout372 = ctx.eval_lut_amortized(&gin372, lut372);

    std::vector<RotationPoly> lut373;
    std::vector<long (*)(long)> flut373;
    auto lut373idx0 = [](long I) -> long {
        /* GATE 890 (LUT2 _4026_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut373.push_back(ctx.genrate_lut(lut373idx0));
    flut373.push_back(lut373idx0);
    auto lut373idx1 = [](long I) -> long {
        /* GATE 856 (LUT2 _3992_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin373 = 1 * gout289[0] + 2 * gout366[1];
    std::vector<Ciphertext> gout373 = ctx.eval_lut_amortized(&gin373, lut373);

    std::vector<RotationPoly> lut374;
    std::vector<long (*)(long)> flut374;
    auto lut374idx0 = [](long I) -> long {
        /* GATE 101 (LUT2 _3237_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut374.push_back(ctx.genrate_lut(lut374idx0));
    flut374.push_back(lut374idx0);
    auto lut374idx1 = [](long I) -> long {
        /* GATE 57 (LUT2 _3193_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin374 = 1 * gout349[1] + 2 * gout370[1];
    std::vector<Ciphertext> gout374 = ctx.eval_lut_amortized(&gin374, lut374);

    std::vector<RotationPoly> lut375;
    std::vector<long (*)(long)> flut375;
    auto lut375idx0 = [](long I) -> long {
        /* GATE 822 (LUT2 _3958_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut375.push_back(ctx.genrate_lut(lut375idx0));
    flut375.push_back(lut375idx0);
    auto fvec375 = [flut375](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut375[i](I));
        return ret;
    };

    std::cerr << "\rLUT375   ";
    Ciphertext gin375 = 1 * gout315[0] + 2 * gout258[1];
    std::vector<Ciphertext> gout375 = ctx.eval_lut_amortized(&gin375, lut375);

    std::vector<RotationPoly> lut376;
    std::vector<long (*)(long)> flut376;
    auto lut376idx0 = [](long I) -> long {
        /* GATE 48 (LUT2 _3184_ INIT 0x1 PERM 01) */
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
    Ciphertext gin376 = 1 * gout319[1] + 2 * gout269[1];
    std::vector<Ciphertext> gout376 = ctx.eval_lut_amortized(&gin376, lut376);

    std::vector<RotationPoly> lut377;
    std::vector<long (*)(long)> flut377;
    auto lut377idx0 = [](long I) -> long {
        /* GATE 674 (LUT2 _3810_ INIT 0x8 PERM 01) */
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
        /* GATE 639 (LUT2 _3775_ INIT 0x6 PERM 01) */
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
    Ciphertext gin377 = 1 * gout369[0] + 2 * gout359[1];
    std::vector<Ciphertext> gout377 = ctx.eval_lut_amortized(&gin377, lut377);

    std::vector<RotationPoly> lut378;
    std::vector<long (*)(long)> flut378;
    auto lut378idx0 = [](long I) -> long {
        /* GATE 137 (LUT2 _3273_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut378.push_back(ctx.genrate_lut(lut378idx0));
    flut378.push_back(lut378idx0);
    auto lut378idx1 = [](long I) -> long {
        /* GATE 104 (LUT2 _3240_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin378 = 1 * gout328[0] + 2 * gout253[0];
    std::vector<Ciphertext> gout378 = ctx.eval_lut_amortized(&gin378, lut378);

    std::vector<RotationPoly> lut379;
    std::vector<long (*)(long)> flut379;
    auto lut379idx0 = [](long I) -> long {
        /* GATE 122 (LUT2 _3258_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut379.push_back(ctx.genrate_lut(lut379idx0));
    flut379.push_back(lut379idx0);
    auto fvec379 = [flut379](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut379[i](I));
        return ret;
    };

    std::cerr << "\rLUT379   ";
    Ciphertext gin379 = 1 * gout370[0] + 2 * gout300[1];
    std::vector<Ciphertext> gout379 = ctx.eval_lut_amortized(&gin379, lut379);

    std::vector<RotationPoly> lut380;
    std::vector<long (*)(long)> flut380;
    auto lut380idx0 = [](long I) -> long {
        /* GATE 205 (LUT2 _3341_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut380.push_back(ctx.genrate_lut(lut380idx0));
    flut380.push_back(lut380idx0);
    auto fvec380 = [flut380](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut380[i](I));
        return ret;
    };

    std::cerr << "\rLUT380   ";
    Ciphertext gin380 = 1 * gout347[0] + 2 * gout311[1];
    std::vector<Ciphertext> gout380 = ctx.eval_lut_amortized(&gin380, lut380);

    std::vector<RotationPoly> lut381;
    std::vector<long (*)(long)> flut381;
    auto lut381idx0 = [](long I) -> long {
        /* GATE 313 (LUT2 _3449_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut381.push_back(ctx.genrate_lut(lut381idx0));
    flut381.push_back(lut381idx0);
    auto fvec381 = [flut381](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut381[i](I));
        return ret;
    };

    std::cerr << "\rLUT381   ";
    Ciphertext gin381 = 1 * gout310[0] + 2 * gout292[0];
    std::vector<Ciphertext> gout381 = ctx.eval_lut_amortized(&gin381, lut381);

    std::vector<RotationPoly> lut382;
    std::vector<long (*)(long)> flut382;
    auto lut382idx0 = [](long I) -> long {
        /* GATE 818 (LUT2 _3954_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut382.push_back(ctx.genrate_lut(lut382idx0));
    flut382.push_back(lut382idx0);
    auto lut382idx1 = [](long I) -> long {
        /* GATE 783 (LUT2 _3919_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin382 = 1 * gout356[1] + 2 * gout231[0];
    std::vector<Ciphertext> gout382 = ctx.eval_lut_amortized(&gin382, lut382);

    std::vector<RotationPoly> lut383;
    std::vector<long (*)(long)> flut383;
    auto lut383idx0 = [](long I) -> long {
        /* GATE 695 (LUT2 _3831_ INIT 0x1 PERM 01) */
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
    Ciphertext gin383 = 1 * gout359[0] + 2 * gout276[1];
    std::vector<Ciphertext> gout383 = ctx.eval_lut_amortized(&gin383, lut383);

    std::vector<RotationPoly> lut384;
    std::vector<long (*)(long)> flut384;
    auto lut384idx0 = [](long I) -> long {
        /* GATE 420 (LUT2 _3556_ INIT 0x1 PERM 01) */
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
    Ciphertext gin384 = 1 * gout362[0] + 2 * gout324[1];
    std::vector<Ciphertext> gout384 = ctx.eval_lut_amortized(&gin384, lut384);

    std::vector<RotationPoly> lut385;
    std::vector<long (*)(long)> flut385;
    auto lut385idx0 = [](long I) -> long {
        /* GATE 677 (LUT2 _3813_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut385.push_back(ctx.genrate_lut(lut385idx0));
    flut385.push_back(lut385idx0);
    auto lut385idx1 = [](long I) -> long {
        /* GATE 710 (LUT2 _3846_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut385.push_back(ctx.genrate_lut(lut385idx1));
    flut385.push_back(lut385idx1);
    auto fvec385 = [flut385](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut385[i](I));
        return ret;
    };

    std::cerr << "\rLUT385   ";
    Ciphertext gin385 = 1 * gout284[0] + 2 * gout337[1];
    std::vector<Ciphertext> gout385 = ctx.eval_lut_amortized(&gin385, lut385);

    std::vector<RotationPoly> lut386;
    std::vector<long (*)(long)> flut386;
    auto lut386idx0 = [](long I) -> long {
        /* GATE 458 (LUT2 _3594_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut386.push_back(ctx.genrate_lut(lut386idx0));
    flut386.push_back(lut386idx0);
    auto lut386idx1 = [](long I) -> long {
        /* GATE 423 (LUT2 _3559_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut386.push_back(ctx.genrate_lut(lut386idx1));
    flut386.push_back(lut386idx1);
    auto fvec386 = [flut386](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut386[i](I));
        return ret;
    };

    std::cerr << "\rLUT386   ";
    Ciphertext gin386 = 1 * gout352[0] + 2 * gout115[1];
    std::vector<Ciphertext> gout386 = ctx.eval_lut_amortized(&gin386, lut386);

    std::vector<RotationPoly> lut387;
    std::vector<long (*)(long)> flut387;
    auto lut387idx0 = [](long I) -> long {
        /* GATE 317 (LUT2 _3453_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut387.push_back(ctx.genrate_lut(lut387idx0));
    flut387.push_back(lut387idx0);
    auto lut387idx1 = [](long I) -> long {
        /* GATE 350 (LUT2 _3486_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut387.push_back(ctx.genrate_lut(lut387idx1));
    flut387.push_back(lut387idx1);
    auto fvec387 = [flut387](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut387[i](I));
        return ret;
    };

    std::cerr << "\rLUT387   ";
    Ciphertext gin387 = 1 * gout365[0] + 2 * gout342[1];
    std::vector<Ciphertext> gout387 = ctx.eval_lut_amortized(&gin387, lut387);

    std::vector<RotationPoly> lut388;
    std::vector<long (*)(long)> flut388;
    auto lut388idx0 = [](long I) -> long {
        /* GATE 277 (LUT2 _3413_ INIT 0x8 PERM 01) */
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
        /* GATE 244 (LUT2 _3380_ INIT 0x6 PERM 01) */
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
    Ciphertext gin388 = 1 * gout364[1] + 2 * gout261[1];
    std::vector<Ciphertext> gout388 = ctx.eval_lut_amortized(&gin388, lut388);

    std::vector<RotationPoly> lut389;
    std::vector<long (*)(long)> flut389;
    auto lut389idx0 = [](long I) -> long {
        /* GATE 581 (LUT2 _3717_ INIT 0x6 PERM 01) */
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
        /* GATE 624 (LUT2 _3760_ INIT 0x8 PERM 01) */
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
    Ciphertext gin389 = 1 * gout304[1] + 2 * ct_data241;
    std::vector<Ciphertext> gout389 = ctx.eval_lut_amortized(&gin389, lut389);

    std::vector<RotationPoly> lut390;
    std::vector<long (*)(long)> flut390;
    auto lut390idx0 = [](long I) -> long {
        /* GATE 568 (LUT2 _3704_ INIT 0x9 PERM 01) */
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
        /* GATE 603 (LUT2 _3739_ INIT 0x4 PERM 01) */
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
    Ciphertext gin390 = 1 * gout363[0] + 2 * gout204[1];
    std::vector<Ciphertext> gout390 = ctx.eval_lut_amortized(&gin390, lut390);

    std::vector<RotationPoly> lut391;
    std::vector<long (*)(long)> flut391;
    auto lut391idx0 = [](long I) -> long {
        /* GATE 83 (LUT2 _3219_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut391.push_back(ctx.genrate_lut(lut391idx0));
    flut391.push_back(lut391idx0);
    auto lut391idx1 = [](long I) -> long {
        /* GATE 7 (LUT2 _3143_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin391 = 1 * gout353[1] + 2 * gout319[0];
    std::vector<Ciphertext> gout391 = ctx.eval_lut_amortized(&gin391, lut391);

    std::vector<RotationPoly> lut392;
    std::vector<long (*)(long)> flut392;
    auto lut392idx0 = [](long I) -> long {
        /* GATE 995 (LUT2 _4131_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut392.push_back(ctx.genrate_lut(lut392idx0));
    flut392.push_back(lut392idx0);
    auto lut392idx1 = [](long I) -> long {
        /* GATE 962 (LUT2 _4098_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut392.push_back(ctx.genrate_lut(lut392idx1));
    flut392.push_back(lut392idx1);
    auto fvec392 = [flut392](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut392[i](I));
        return ret;
    };

    std::cerr << "\rLUT392   ";
    Ciphertext gin392 = 1 * gout372[0] + 2 * gout280[0];
    std::vector<Ciphertext> gout392 = ctx.eval_lut_amortized(&gin392, lut392);

    std::vector<RotationPoly> lut393;
    std::vector<long (*)(long)> flut393;
    auto lut393idx0 = [](long I) -> long {
        /* GATE 673 (LUT2 _3809_ INIT 0x1 PERM 01) */
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
    Ciphertext gin393 = 1 * gout377[0] + 2 * gout369[1];
    std::vector<Ciphertext> gout393 = ctx.eval_lut_amortized(&gin393, lut393);

    std::vector<RotationPoly> lut394;
    std::vector<long (*)(long)> flut394;
    auto lut394idx0 = [](long I) -> long {
        /* GATE 493 (LUT2 _3629_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut394.push_back(ctx.genrate_lut(lut394idx0));
    flut394.push_back(lut394idx0);
    auto lut394idx1 = [](long I) -> long {
        /* GATE 460 (LUT2 _3596_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin394 = 1 * gout326[1] + 2 * gout238[1];
    std::vector<Ciphertext> gout394 = ctx.eval_lut_amortized(&gin394, lut394);

    std::vector<RotationPoly> lut395;
    std::vector<long (*)(long)> flut395;
    auto lut395idx0 = [](long I) -> long {
        /* GATE 316 (LUT2 _3452_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut395.push_back(ctx.genrate_lut(lut395idx0));
    flut395.push_back(lut395idx0);
    auto lut395idx1 = [](long I) -> long {
        /* GATE 349 (LUT2 _3485_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
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
    Ciphertext gin395 = 1 * gout387[0] + 2 * gout247[0];
    std::vector<Ciphertext> gout395 = ctx.eval_lut_amortized(&gin395, lut395);

    std::vector<RotationPoly> lut396;
    std::vector<long (*)(long)> flut396;
    auto lut396idx0 = [](long I) -> long {
        /* GATE 546 (LUT2 _3682_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut396.push_back(ctx.genrate_lut(lut396idx0));
    flut396.push_back(lut396idx0);
    auto lut396idx1 = [](long I) -> long {
        /* GATE 587 (LUT2 _3723_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut396.push_back(ctx.genrate_lut(lut396idx1));
    flut396.push_back(lut396idx1);
    auto fvec396 = [flut396](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut396[i](I));
        return ret;
    };

    std::cerr << "\rLUT396   ";
    Ciphertext gin396 = 1 * gout305[0] + 2 * ct_data240;
    std::vector<Ciphertext> gout396 = ctx.eval_lut_amortized(&gin396, lut396);

    std::vector<RotationPoly> lut397;
    std::vector<long (*)(long)> flut397;
    auto lut397idx0 = [](long I) -> long {
        /* GATE 602 (LUT2 _3738_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut397.push_back(ctx.genrate_lut(lut397idx0));
    flut397.push_back(lut397idx0);
    auto lut397idx1 = [](long I) -> long {
        /* GATE 567 (LUT2 _3703_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
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
    Ciphertext gin397 = 1 * gout390[0] + 2 * gout389[0];
    std::vector<Ciphertext> gout397 = ctx.eval_lut_amortized(&gin397, lut397);

    std::vector<RotationPoly> lut398;
    std::vector<long (*)(long)> flut398;
    auto lut398idx0 = [](long I) -> long {
        /* GATE 6 (LUT2 _3142_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut398.push_back(ctx.genrate_lut(lut398idx0));
    flut398.push_back(lut398idx0);
    auto fvec398 = [flut398](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut398[i](I));
        return ret;
    };

    std::cerr << "\rLUT398   ";
    Ciphertext gin398 = 1 * gout391[1] + 2 * gout353[0];
    std::vector<Ciphertext> gout398 = ctx.eval_lut_amortized(&gin398, lut398);

    std::vector<RotationPoly> lut399;
    std::vector<long (*)(long)> flut399;
    auto lut399idx0 = [](long I) -> long {
        /* GATE 353 (LUT2 _3489_ INIT 0x1 PERM 01) */
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
    Ciphertext gin399 = 1 * gout342[0] + 2 * gout298[1];
    std::vector<Ciphertext> gout399 = ctx.eval_lut_amortized(&gin399, lut399);

    std::vector<RotationPoly> lut400;
    std::vector<long (*)(long)> flut400;
    auto lut400idx0 = [](long I) -> long {
        /* GATE 136 (LUT2 _3272_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut400.push_back(ctx.genrate_lut(lut400idx0));
    flut400.push_back(lut400idx0);
    auto lut400idx1 = [](long I) -> long {
        /* GATE 103 (LUT2 _3239_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin400 = 1 * gout378[1] + 2 * gout164[0];
    std::vector<Ciphertext> gout400 = ctx.eval_lut_amortized(&gin400, lut400);

    std::vector<RotationPoly> lut401;
    std::vector<long (*)(long)> flut401;
    auto lut401idx0 = [](long I) -> long {
        /* GATE 457 (LUT2 _3593_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut401.push_back(ctx.genrate_lut(lut401idx0));
    flut401.push_back(lut401idx0);
    auto fvec401 = [flut401](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut401[i](I));
        return ret;
    };

    std::cerr << "\rLUT401   ";
    Ciphertext gin401 = 1 * gout386[0] + 2 * gout352[1];
    std::vector<Ciphertext> gout401 = ctx.eval_lut_amortized(&gin401, lut401);

    std::vector<RotationPoly> lut402;
    std::vector<long (*)(long)> flut402;
    auto lut402idx0 = [](long I) -> long {
        /* GATE 1030 (LUT2 _4166_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut402.push_back(ctx.genrate_lut(lut402idx0));
    flut402.push_back(lut402idx0);
    auto lut402idx1 = [](long I) -> long {
        /* GATE 998 (LUT2 _4134_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut402.push_back(ctx.genrate_lut(lut402idx1));
    flut402.push_back(lut402idx1);
    auto fvec402 = [flut402](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut402[i](I));
        return ret;
    };

    std::cerr << "\rLUT402   ";
    Ciphertext gin402 = 1 * gout355[0] + 2 * gout190[1];
    std::vector<Ciphertext> gout402 = ctx.eval_lut_amortized(&gin402, lut402);

    std::vector<RotationPoly> lut403;
    std::vector<long (*)(long)> flut403;
    auto lut403idx0 = [](long I) -> long {
        /* GATE 530 (LUT2 _3666_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut403.push_back(ctx.genrate_lut(lut403idx0));
    flut403.push_back(lut403idx0);
    auto lut403idx1 = [](long I) -> long {
        /* GATE 495 (LUT2 _3631_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin403 = 1 * gout340[1] + 2 * gout282[1];
    std::vector<Ciphertext> gout403 = ctx.eval_lut_amortized(&gin403, lut403);

    std::vector<RotationPoly> lut404;
    std::vector<long (*)(long)> flut404;
    auto lut404idx0 = [](long I) -> long {
        /* GATE 803 (LUT2 _3939_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut404.push_back(ctx.genrate_lut(lut404idx0));
    flut404.push_back(lut404idx0);
    auto lut404idx1 = [](long I) -> long {
        /* GATE 762 (LUT2 _3898_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
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
    Ciphertext gin404 = 1 * gout341[1] + 2 * ct_data246;
    std::vector<Ciphertext> gout404 = ctx.eval_lut_amortized(&gin404, lut404);

    std::vector<RotationPoly> lut405;
    std::vector<long (*)(long)> flut405;
    auto lut405idx0 = [](long I) -> long {
        /* GATE 138 (LUT2 _3274_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut405.push_back(ctx.genrate_lut(lut405idx0));
    flut405.push_back(lut405idx0);
    auto lut405idx1 = [](long I) -> long {
        /* GATE 171 (LUT2 _3307_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut405.push_back(ctx.genrate_lut(lut405idx1));
    flut405.push_back(lut405idx1);
    auto fvec405 = [flut405](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut405[i](I));
        return ret;
    };

    std::cerr << "\rLUT405   ";
    Ciphertext gin405 = 1 * gout350[0] + 2 * gout344[1];
    std::vector<Ciphertext> gout405 = ctx.eval_lut_amortized(&gin405, lut405);

    std::vector<RotationPoly> lut406;
    std::vector<long (*)(long)> flut406;
    auto lut406idx0 = [](long I) -> long {
        /* GATE 492 (LUT2 _3628_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut406.push_back(ctx.genrate_lut(lut406idx0));
    flut406.push_back(lut406idx0);
    auto fvec406 = [flut406](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut406[i](I));
        return ret;
    };

    std::cerr << "\rLUT406   ";
    Ciphertext gin406 = 1 * gout394[0] + 2 * gout326[0];
    std::vector<Ciphertext> gout406 = ctx.eval_lut_amortized(&gin406, lut406);

    std::vector<RotationPoly> lut407;
    std::vector<long (*)(long)> flut407;
    auto lut407idx0 = [](long I) -> long {
        /* GATE 637 (LUT2 _3773_ INIT 0x8 PERM 01) */
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
        /* GATE 604 (LUT2 _3740_ INIT 0x6 PERM 01) */
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
    Ciphertext gin407 = 1 * gout316[1] + 2 * gout357[0];
    std::vector<Ciphertext> gout407 = ctx.eval_lut_amortized(&gin407, lut407);

    std::vector<RotationPoly> lut408;
    std::vector<long (*)(long)> flut408;
    auto lut408idx0 = [](long I) -> long {
        /* GATE 781 (LUT2 _3917_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut408.push_back(ctx.genrate_lut(lut408idx0));
    flut408.push_back(lut408idx0);
    auto lut408idx1 = [](long I) -> long {
        /* GATE 748 (LUT2 _3884_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
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
    Ciphertext gin408 = 1 * gout360[0] + 2 * gout404[1];
    std::vector<Ciphertext> gout408 = ctx.eval_lut_amortized(&gin408, lut408);

    std::vector<RotationPoly> lut409;
    std::vector<long (*)(long)> flut409;
    auto lut409idx0 = [](long I) -> long {
        /* GATE 242 (LUT2 _3378_ INIT 0x8 PERM 01) */
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
        /* GATE 208 (LUT2 _3344_ INIT 0x6 PERM 01) */
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
    Ciphertext gin409 = 1 * gout343[1] + 2 * gout287[0];
    std::vector<Ciphertext> gout409 = ctx.eval_lut_amortized(&gin409, lut409);

    std::vector<RotationPoly> lut410;
    std::vector<long (*)(long)> flut410;
    auto lut410idx0 = [](long I) -> long {
        /* GATE 100 (LUT2 _3236_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut410.push_back(ctx.genrate_lut(lut410idx0));
    flut410.push_back(lut410idx0);
    auto fvec410 = [flut410](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut410[i](I));
        return ret;
    };

    std::cerr << "\rLUT410   ";
    Ciphertext gin410 = 1 * gout374[0] + 2 * gout349[0];
    std::vector<Ciphertext> gout410 = ctx.eval_lut_amortized(&gin410, lut410);

    std::vector<RotationPoly> lut411;
    std::vector<long (*)(long)> flut411;
    auto lut411idx0 = [](long I) -> long {
        /* GATE 713 (LUT2 _3849_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut411.push_back(ctx.genrate_lut(lut411idx0));
    flut411.push_back(lut411idx0);
    auto fvec411 = [flut411](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut411[i](I));
        return ret;
    };

    std::cerr << "\rLUT411   ";
    Ciphertext gin411 = 1 * gout337[0] + 2 * gout268[0];
    std::vector<Ciphertext> gout411 = ctx.eval_lut_amortized(&gin411, lut411);

    std::vector<RotationPoly> lut412;
    std::vector<long (*)(long)> flut412;
    auto lut412idx0 = [](long I) -> long {
        /* GATE 817 (LUT2 _3953_ INIT 0x1 PERM 01) */
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
    Ciphertext gin412 = 1 * gout382[0] + 2 * gout356[0];
    std::vector<Ciphertext> gout412 = ctx.eval_lut_amortized(&gin412, lut412);

    std::vector<RotationPoly> lut413;
    std::vector<long (*)(long)> flut413;
    auto lut413idx0 = [](long I) -> long {
        /* GATE 893 (LUT2 _4029_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut413.push_back(ctx.genrate_lut(lut413idx0));
    flut413.push_back(lut413idx0);
    auto fvec413 = [flut413](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut413[i](I));
        return ret;
    };

    std::cerr << "\rLUT413   ";
    Ciphertext gin413 = 1 * gout366[0] + 2 * gout302[0];
    std::vector<Ciphertext> gout413 = ctx.eval_lut_amortized(&gin413, lut413);

    std::vector<RotationPoly> lut414;
    std::vector<long (*)(long)> flut414;
    auto lut414idx0 = [](long I) -> long {
        /* GATE 623 (LUT2 _3759_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut414.push_back(ctx.genrate_lut(lut414idx0));
    flut414.push_back(lut414idx0);
    auto fvec414 = [flut414](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut414[i](I));
        return ret;
    };

    std::cerr << "\rLUT414   ";
    Ciphertext gin414 = 1 * gout389[1] + 2 * gout304[0];
    std::vector<Ciphertext> gout414 = ctx.eval_lut_amortized(&gin414, lut414);

    std::vector<RotationPoly> lut415;
    std::vector<long (*)(long)> flut415;
    auto lut415idx0 = [](long I) -> long {
        /* GATE 30 (LUT2 _3166_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut415.push_back(ctx.genrate_lut(lut415idx0));
    flut415.push_back(lut415idx0);
    auto lut415idx1 = [](long I) -> long {
        /* GATE 56 (LUT2 _3192_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut415.push_back(ctx.genrate_lut(lut415idx1));
    flut415.push_back(lut415idx1);
    auto fvec415 = [flut415](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut415[i](I));
        return ret;
    };

    std::cerr << "\rLUT415   ";
    Ciphertext gin415 = 1 * gout367[0] + 2 * gout250[1];
    std::vector<Ciphertext> gout415 = ctx.eval_lut_amortized(&gin415, lut415);

    std::vector<RotationPoly> lut416;
    std::vector<long (*)(long)> flut416;
    auto lut416idx0 = [](long I) -> long {
        /* GATE 192 (LUT2 _3328_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut416.push_back(ctx.genrate_lut(lut416idx0));
    flut416.push_back(lut416idx0);
    auto fvec416 = [flut416](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut416[i](I));
        return ret;
    };

    std::cerr << "\rLUT416   ";
    Ciphertext gin416 = 1 * gout344[0] + 2 * gout307[0];
    std::vector<Ciphertext> gout416 = ctx.eval_lut_amortized(&gin416, lut416);

    std::vector<RotationPoly> lut417;
    std::vector<long (*)(long)> flut417;
    auto lut417idx0 = [](long I) -> long {
        /* GATE 802 (LUT2 _3938_ INIT 0x1 PERM 01) */
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
    Ciphertext gin417 = 1 * gout404[0] + 2 * gout341[0];
    std::vector<Ciphertext> gout417 = ctx.eval_lut_amortized(&gin417, lut417);

    std::vector<RotationPoly> lut418;
    std::vector<long (*)(long)> flut418;
    auto lut418idx0 = [](long I) -> long {
        /* GATE 889 (LUT2 _4025_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut418.push_back(ctx.genrate_lut(lut418idx0));
    flut418.push_back(lut418idx0);
    auto lut418idx1 = [](long I) -> long {
        /* GATE 855 (LUT2 _3991_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin418 = 1 * gout373[1] + 2 * gout318[1];
    std::vector<Ciphertext> gout418 = ctx.eval_lut_amortized(&gin418, lut418);

    std::vector<RotationPoly> lut419;
    std::vector<long (*)(long)> flut419;
    auto lut419idx0 = [](long I) -> long {
        /* GATE 925 (LUT2 _4061_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut419.push_back(ctx.genrate_lut(lut419idx0));
    flut419.push_back(lut419idx0);
    auto lut419idx1 = [](long I) -> long {
        /* GATE 892 (LUT2 _4028_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut419.push_back(ctx.genrate_lut(lut419idx1));
    flut419.push_back(lut419idx1);
    auto fvec419 = [flut419](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut419[i](I));
        return ret;
    };

    std::cerr << "\rLUT419   ";
    Ciphertext gin419 = 1 * gout413[0] + 2 * gout371[1];
    std::vector<Ciphertext> gout419 = ctx.eval_lut_amortized(&gin419, lut419);

    std::vector<RotationPoly> lut420;
    std::vector<long (*)(long)> flut420;
    auto lut420idx0 = [](long I) -> long {
        /* GATE 928 (LUT2 _4064_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut420.push_back(ctx.genrate_lut(lut420idx0));
    flut420.push_back(lut420idx0);
    auto fvec420 = [flut420](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut420[i](I));
        return ret;
    };

    std::cerr << "\rLUT420   ";
    Ciphertext gin420 = 1 * gout371[0] + 2 * gout346[1];
    std::vector<Ciphertext> gout420 = ctx.eval_lut_amortized(&gin420, lut420);

    std::vector<RotationPoly> lut421;
    std::vector<long (*)(long)> flut421;
    auto lut421idx0 = [](long I) -> long {
        /* GATE 821 (LUT2 _3957_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut421.push_back(ctx.genrate_lut(lut421idx0));
    flut421.push_back(lut421idx0);
    auto lut421idx1 = [](long I) -> long {
        /* GATE 854 (LUT2 _3990_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut421.push_back(ctx.genrate_lut(lut421idx1));
    flut421.push_back(lut421idx1);
    auto fvec421 = [flut421](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut421[i](I));
        return ret;
    };

    std::cerr << "\rLUT421   ";
    Ciphertext gin421 = 1 * gout375[0] + 2 * gout223[0];
    std::vector<Ciphertext> gout421 = ctx.eval_lut_amortized(&gin421, lut421);

    std::vector<RotationPoly> lut422;
    std::vector<long (*)(long)> flut422;
    auto lut422idx0 = [](long I) -> long {
        /* GATE 994 (LUT2 _4130_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut422.push_back(ctx.genrate_lut(lut422idx0));
    flut422.push_back(lut422idx0);
    auto fvec422 = [flut422](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut422[i](I));
        return ret;
    };

    std::cerr << "\rLUT422   ";
    Ciphertext gin422 = 1 * gout392[0] + 2 * gout372[1];
    std::vector<Ciphertext> gout422 = ctx.eval_lut_amortized(&gin422, lut422);

    std::vector<RotationPoly> lut423;
    std::vector<long (*)(long)> flut423;
    auto lut423idx0 = [](long I) -> long {
        /* GATE 88 (LUT2 _3224_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut423.push_back(ctx.genrate_lut(lut423idx0));
    flut423.push_back(lut423idx0);
    auto lut423idx1 = [](long I) -> long {
        /* GATE 82 (LUT2 _3218_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
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
    Ciphertext gin423 = 1 * gout391[0] + 2 * gout332[0];
    std::vector<Ciphertext> gout423 = ctx.eval_lut_amortized(&gin423, lut423);

    std::vector<RotationPoly> lut424;
    std::vector<long (*)(long)> flut424;
    auto lut424idx0 = [](long I) -> long {
        /* GATE 586 (LUT2 _3722_ INIT 0x1 PERM 01) */
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
    Ciphertext gin424 = 1 * gout396[1] + 2 * gout305[1];
    std::vector<Ciphertext> gout424 = ctx.eval_lut_amortized(&gin424, lut424);

    std::vector<RotationPoly> lut425;
    std::vector<long (*)(long)> flut425;
    auto lut425idx0 = [](long I) -> long {
        /* GATE 1029 (LUT2 _4165_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut425.push_back(ctx.genrate_lut(lut425idx0));
    flut425.push_back(lut425idx0);
    auto lut425idx1 = [](long I) -> long {
        /* GATE 997 (LUT2 _4133_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut425.push_back(ctx.genrate_lut(lut425idx1));
    flut425.push_back(lut425idx1);
    auto fvec425 = [flut425](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut425[i](I));
        return ret;
    };

    std::cerr << "\rLUT425   ";
    Ciphertext gin425 = 1 * gout402[1] + 2 * gout239[0];
    std::vector<Ciphertext> gout425 = ctx.eval_lut_amortized(&gin425, lut425);

    std::vector<RotationPoly> lut426;
    std::vector<long (*)(long)> flut426;
    auto lut426idx0 = [](long I) -> long {
        /* GATE 419 (LUT2 _3555_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut426.push_back(ctx.genrate_lut(lut426idx0));
    flut426.push_back(lut426idx0);
    auto lut426idx1 = [](long I) -> long {
        /* GATE 454 (LUT2 _3590_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut426.push_back(ctx.genrate_lut(lut426idx1));
    flut426.push_back(lut426idx1);
    auto fvec426 = [flut426](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut426[i](I));
        return ret;
    };

    std::cerr << "\rLUT426   ";
    Ciphertext gin426 = 1 * gout384[0] + 2 * gout386[1];
    std::vector<Ciphertext> gout426 = ctx.eval_lut_amortized(&gin426, lut426);

    std::vector<RotationPoly> lut427;
    std::vector<long (*)(long)> flut427;
    auto lut427idx0 = [](long I) -> long {
        /* GATE 1026 (LUT2 _4162_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut427.push_back(ctx.genrate_lut(lut427idx0));
    flut427.push_back(lut427idx0);
    auto lut427idx1 = [](long I) -> long {
        /* GATE 993 (LUT2 _4129_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut427.push_back(ctx.genrate_lut(lut427idx1));
    flut427.push_back(lut427idx1);
    auto fvec427 = [flut427](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut427[i](I));
        return ret;
    };

    std::cerr << "\rLUT427   ";
    Ciphertext gin427 = 1 * gout422[0] + 2 * gout425[1];
    std::vector<Ciphertext> gout427 = ctx.eval_lut_amortized(&gin427, lut427);

    std::vector<RotationPoly> lut428;
    std::vector<long (*)(long)> flut428;
    auto lut428idx0 = [](long I) -> long {
        /* GATE 709 (LUT2 _3845_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut428.push_back(ctx.genrate_lut(lut428idx0));
    flut428.push_back(lut428idx0);
    auto lut428idx1 = [](long I) -> long {
        /* GATE 676 (LUT2 _3812_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin428 = 1 * gout385[0] + 2 * gout176[1];
    std::vector<Ciphertext> gout428 = ctx.eval_lut_amortized(&gin428, lut428);

    std::vector<RotationPoly> lut429;
    std::vector<long (*)(long)> flut429;
    auto lut429idx0 = [](long I) -> long {
        /* GATE 705 (LUT2 _3841_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut429.push_back(ctx.genrate_lut(lut429idx0));
    flut429.push_back(lut429idx0);
    auto lut429idx1 = [](long I) -> long {
        /* GATE 672 (LUT2 _3808_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut429.push_back(ctx.genrate_lut(lut429idx1));
    flut429.push_back(lut429idx1);
    auto fvec429 = [flut429](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut429[i](I));
        return ret;
    };

    std::cerr << "\rLUT429   ";
    Ciphertext gin429 = 1 * gout393[0] + 2 * gout428[1];
    std::vector<Ciphertext> gout429 = ctx.eval_lut_amortized(&gin429, lut429);

    std::vector<RotationPoly> lut430;
    std::vector<long (*)(long)> flut430;
    auto lut430idx0 = [](long I) -> long {
        /* GATE 453 (LUT2 _3589_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut430.push_back(ctx.genrate_lut(lut430idx0));
    flut430.push_back(lut430idx0);
    auto lut430idx1 = [](long I) -> long {
        /* GATE 418 (LUT2 _3554_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
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
    Ciphertext gin430 = 1 * gout426[0] + 2 * gout234[0];
    std::vector<Ciphertext> gout430 = ctx.eval_lut_amortized(&gin430, lut430);

    std::vector<RotationPoly> lut431;
    std::vector<long (*)(long)> flut431;
    auto lut431idx0 = [](long I) -> long {
        /* GATE 348 (LUT2 _3484_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut431.push_back(ctx.genrate_lut(lut431idx0));
    flut431.push_back(lut431idx0);
    auto fvec431 = [flut431](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut431[i](I));
        return ret;
    };

    std::cerr << "\rLUT431   ";
    Ciphertext gin431 = 1 * gout395[1] + 2 * gout387[1];
    std::vector<Ciphertext> gout431 = ctx.eval_lut_amortized(&gin431, lut431);

    std::vector<RotationPoly> lut432;
    std::vector<long (*)(long)> flut432;
    auto lut432idx0 = [](long I) -> long {
        /* GATE 529 (LUT2 _3665_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut432.push_back(ctx.genrate_lut(lut432idx0));
    flut432.push_back(lut432idx0);
    auto fvec432 = [flut432](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut432[i](I));
        return ret;
    };

    std::cerr << "\rLUT432   ";
    Ciphertext gin432 = 1 * gout403[0] + 2 * gout340[0];
    std::vector<Ciphertext> gout432 = ctx.eval_lut_amortized(&gin432, lut432);

    std::vector<RotationPoly> lut433;
    std::vector<long (*)(long)> flut433;
    auto lut433idx0 = [](long I) -> long {
        /* GATE 452 (LUT2 _3588_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut433.push_back(ctx.genrate_lut(lut433idx0));
    flut433.push_back(lut433idx0);
    auto fvec433 = [flut433](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut433[i](I));
        return ret;
    };

    std::cerr << "\rLUT433   ";
    Ciphertext gin433 = 1 * gout430[0] + 2 * gout426[1];
    std::vector<Ciphertext> gout433 = ctx.eval_lut_amortized(&gin433, lut433);

    std::vector<RotationPoly> lut434;
    std::vector<long (*)(long)> flut434;
    auto lut434idx0 = [](long I) -> long {
        /* GATE 853 (LUT2 _3989_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut434.push_back(ctx.genrate_lut(lut434idx0));
    flut434.push_back(lut434idx0);
    auto lut434idx1 = [](long I) -> long {
        /* GATE 820 (LUT2 _3956_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
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
    Ciphertext gin434 = 1 * gout421[0] + 2 * gout295[1];
    std::vector<Ciphertext> gout434 = ctx.eval_lut_amortized(&gin434, lut434);

    std::vector<RotationPoly> lut435;
    std::vector<long (*)(long)> flut435;
    auto lut435idx0 = [](long I) -> long {
        /* GATE 135 (LUT2 _3271_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut435.push_back(ctx.genrate_lut(lut435idx0));
    flut435.push_back(lut435idx0);
    auto fvec435 = [flut435](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut435[i](I));
        return ret;
    };

    std::cerr << "\rLUT435   ";
    Ciphertext gin435 = 1 * gout400[0] + 2 * gout378[0];
    std::vector<Ciphertext> gout435 = ctx.eval_lut_amortized(&gin435, lut435);

    std::vector<RotationPoly> lut436;
    std::vector<long (*)(long)> flut436;
    auto lut436idx0 = [](long I) -> long {
        /* GATE 276 (LUT2 _3412_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut436.push_back(ctx.genrate_lut(lut436idx0));
    flut436.push_back(lut436idx0);
    auto fvec436 = [flut436](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut436[i](I));
        return ret;
    };

    std::cerr << "\rLUT436   ";
    Ciphertext gin436 = 1 * gout388[0] + 2 * gout364[0];
    std::vector<Ciphertext> gout436 = ctx.eval_lut_amortized(&gin436, lut436);

    std::vector<RotationPoly> lut437;
    std::vector<long (*)(long)> flut437;
    auto lut437idx0 = [](long I) -> long {
        /* GATE 532 (LUT2 _3668_ INIT 0x6 PERM 01) */
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
        /* GATE 565 (LUT2 _3701_ INIT 0x8 PERM 01) */
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
    Ciphertext gin437 = 1 * gout361[0] + 2 * gout396[0];
    std::vector<Ciphertext> gout437 = ctx.eval_lut_amortized(&gin437, lut437);

    std::vector<RotationPoly> lut438;
    std::vector<long (*)(long)> flut438;
    auto lut438idx0 = [](long I) -> long {
        /* GATE 345 (LUT2 _3481_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut438.push_back(ctx.genrate_lut(lut438idx0));
    flut438.push_back(lut438idx0);
    auto lut438idx1 = [](long I) -> long {
        /* GATE 312 (LUT2 _3448_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin438 = 1 * gout381[0] + 2 * gout395[0];
    std::vector<Ciphertext> gout438 = ctx.eval_lut_amortized(&gin438, lut438);

    std::vector<RotationPoly> lut439;
    std::vector<long (*)(long)> flut439;
    auto lut439idx0 = [](long I) -> long {
        /* GATE 924 (LUT2 _4060_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut439.push_back(ctx.genrate_lut(lut439idx0));
    flut439.push_back(lut439idx0);
    auto lut439idx1 = [](long I) -> long {
        /* GATE 891 (LUT2 _4027_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin439 = 1 * gout419[1] + 2 * gout227[0];
    std::vector<Ciphertext> gout439 = ctx.eval_lut_amortized(&gin439, lut439);

    std::vector<RotationPoly> lut440;
    std::vector<long (*)(long)> flut440;
    auto lut440idx0 = [](long I) -> long {
        /* GATE 99 (LUT2 _3235_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut440.push_back(ctx.genrate_lut(lut440idx0));
    flut440.push_back(lut440idx0);
    auto lut440idx1 = [](long I) -> long {
        /* GATE 132 (LUT2 _3268_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut440.push_back(ctx.genrate_lut(lut440idx1));
    flut440.push_back(lut440idx1);
    auto fvec440 = [flut440](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut440[i](I));
        return ret;
    };

    std::cerr << "\rLUT440   ";
    Ciphertext gin440 = 1 * gout410[0] + 2 * gout400[1];
    std::vector<Ciphertext> gout440 = ctx.eval_lut_amortized(&gin440, lut440);

    std::vector<RotationPoly> lut441;
    std::vector<long (*)(long)> flut441;
    auto lut441idx0 = [](long I) -> long {
        /* GATE 238 (LUT2 _3374_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut441.push_back(ctx.genrate_lut(lut441idx0));
    flut441.push_back(lut441idx0);
    auto lut441idx1 = [](long I) -> long {
        /* GATE 204 (LUT2 _3340_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut441.push_back(ctx.genrate_lut(lut441idx1));
    flut441.push_back(lut441idx1);
    auto fvec441 = [flut441](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut441[i](I));
        return ret;
    };

    std::cerr << "\rLUT441   ";
    Ciphertext gin441 = 1 * gout380[0] + 2 * gout409[1];
    std::vector<Ciphertext> gout441 = ctx.eval_lut_amortized(&gin441, lut441);

    std::vector<RotationPoly> lut442;
    std::vector<long (*)(long)> flut442;
    auto lut442idx0 = [](long I) -> long {
        /* GATE 816 (LUT2 _3952_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut442.push_back(ctx.genrate_lut(lut442idx0));
    flut442.push_back(lut442idx0);
    auto lut442idx1 = [](long I) -> long {
        /* GATE 849 (LUT2 _3985_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut442.push_back(ctx.genrate_lut(lut442idx1));
    flut442.push_back(lut442idx1);
    auto fvec442 = [flut442](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut442[i](I));
        return ret;
    };

    std::cerr << "\rLUT442   ";
    Ciphertext gin442 = 1 * gout412[0] + 2 * gout434[1];
    std::vector<Ciphertext> gout442 = ctx.eval_lut_amortized(&gin442, lut442);

    std::vector<RotationPoly> lut443;
    std::vector<long (*)(long)> flut443;
    auto lut443idx0 = [](long I) -> long {
        /* GATE 311 (LUT2 _3447_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut443.push_back(ctx.genrate_lut(lut443idx0));
    flut443.push_back(lut443idx0);
    auto lut443idx1 = [](long I) -> long {
        /* GATE 344 (LUT2 _3480_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut443.push_back(ctx.genrate_lut(lut443idx1));
    flut443.push_back(lut443idx1);
    auto fvec443 = [flut443](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut443[i](I));
        return ret;
    };

    std::cerr << "\rLUT443   ";
    Ciphertext gin443 = 1 * gout438[1] + 2 * gout279[0];
    std::vector<Ciphertext> gout443 = ctx.eval_lut_amortized(&gin443, lut443);

    std::vector<RotationPoly> lut444;
    std::vector<long (*)(long)> flut444;
    auto lut444idx0 = [](long I) -> long {
        /* GATE 601 (LUT2 _3737_ INIT 0x1 PERM 01) */
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
    Ciphertext gin444 = 1 * gout397[0] + 2 * gout390[1];
    std::vector<Ciphertext> gout444 = ctx.eval_lut_amortized(&gin444, lut444);

    std::vector<RotationPoly> lut445;
    std::vector<long (*)(long)> flut445;
    auto lut445idx0 = [](long I) -> long {
        /* GATE 961 (LUT2 _4097_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut445.push_back(ctx.genrate_lut(lut445idx0));
    flut445.push_back(lut445idx0);
    auto lut445idx1 = [](long I) -> long {
        /* GATE 927 (LUT2 _4063_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin445 = 1 * gout420[0] + 2 * gout345[0];
    std::vector<Ciphertext> gout445 = ctx.eval_lut_amortized(&gin445, lut445);

    std::vector<RotationPoly> lut446;
    std::vector<long (*)(long)> flut446;
    auto lut446idx0 = [](long I) -> long {
        /* GATE 98 (LUT2 _3234_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut446.push_back(ctx.genrate_lut(lut446idx0));
    flut446.push_back(lut446idx0);
    auto lut446idx1 = [](long I) -> long {
        /* GATE 131 (LUT2 _3267_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut446.push_back(ctx.genrate_lut(lut446idx1));
    flut446.push_back(lut446idx1);
    auto fvec446 = [flut446](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut446[i](I));
        return ret;
    };

    std::cerr << "\rLUT446   ";
    Ciphertext gin446 = 1 * gout440[0] + 2 * gout379[0];
    std::vector<Ciphertext> gout446 = ctx.eval_lut_amortized(&gin446, lut446);

    std::vector<RotationPoly> lut447;
    std::vector<long (*)(long)> flut447;
    auto lut447idx0 = [](long I) -> long {
        /* GATE 170 (LUT2 _3306_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut447.push_back(ctx.genrate_lut(lut447idx0));
    flut447.push_back(lut447idx0);
    auto fvec447 = [flut447](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut447[i](I));
        return ret;
    };

    std::cerr << "\rLUT447   ";
    Ciphertext gin447 = 1 * gout405[1] + 2 * gout350[1];
    std::vector<Ciphertext> gout447 = ctx.eval_lut_amortized(&gin447, lut447);

    std::vector<RotationPoly> lut448;
    std::vector<long (*)(long)> flut448;
    auto lut448idx0 = [](long I) -> long {
        /* GATE 489 (LUT2 _3625_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut448.push_back(ctx.genrate_lut(lut448idx0));
    flut448.push_back(lut448idx0);
    auto lut448idx1 = [](long I) -> long {
        /* GATE 456 (LUT2 _3592_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut448.push_back(ctx.genrate_lut(lut448idx1));
    flut448.push_back(lut448idx1);
    auto fvec448 = [flut448](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut448[i](I));
        return ret;
    };

    std::cerr << "\rLUT448   ";
    Ciphertext gin448 = 1 * gout401[0] + 2 * gout394[1];
    std::vector<Ciphertext> gout448 = ctx.eval_lut_amortized(&gin448, lut448);

    std::vector<RotationPoly> lut449;
    std::vector<long (*)(long)> flut449;
    auto lut449idx0 = [](long I) -> long {
        /* GATE 780 (LUT2 _3916_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut449.push_back(ctx.genrate_lut(lut449idx0));
    flut449.push_back(lut449idx0);
    auto fvec449 = [flut449](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut449[i](I));
        return ret;
    };

    std::cerr << "\rLUT449   ";
    Ciphertext gin449 = 1 * gout408[0] + 2 * gout360[1];
    std::vector<Ciphertext> gout449 = ctx.eval_lut_amortized(&gin449, lut449);

    std::vector<RotationPoly> lut450;
    std::vector<long (*)(long)> flut450;
    auto lut450idx0 = [](long I) -> long {
        /* GATE 352 (LUT2 _3488_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut450.push_back(ctx.genrate_lut(lut450idx0));
    flut450.push_back(lut450idx0);
    auto lut450idx1 = [](long I) -> long {
        /* GATE 387 (LUT2 _3523_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut450.push_back(ctx.genrate_lut(lut450idx1));
    flut450.push_back(lut450idx1);
    auto fvec450 = [flut450](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut450[i](I));
        return ret;
    };

    std::cerr << "\rLUT450   ";
    Ciphertext gin450 = 1 * gout399[0] + 2 * gout317[1];
    std::vector<Ciphertext> gout450 = ctx.eval_lut_amortized(&gin450, lut450);

    std::vector<RotationPoly> lut451;
    std::vector<long (*)(long)> flut451;
    auto lut451idx0 = [](long I) -> long {
        /* GATE 708 (LUT2 _3844_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut451.push_back(ctx.genrate_lut(lut451idx0));
    flut451.push_back(lut451idx0);
    auto fvec451 = [flut451](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut451[i](I));
        return ret;
    };

    std::cerr << "\rLUT451   ";
    Ciphertext gin451 = 1 * gout428[0] + 2 * gout385[1];
    std::vector<Ciphertext> gout451 = ctx.eval_lut_amortized(&gin451, lut451);

    std::vector<RotationPoly> lut452;
    std::vector<long (*)(long)> flut452;
    auto lut452idx0 = [](long I) -> long {
        /* GATE 888 (LUT2 _4024_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut452.push_back(ctx.genrate_lut(lut452idx0));
    flut452.push_back(lut452idx0);
    auto fvec452 = [flut452](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut452[i](I));
        return ret;
    };

    std::cerr << "\rLUT452   ";
    Ciphertext gin452 = 1 * gout418[0] + 2 * gout373[0];
    std::vector<Ciphertext> gout452 = ctx.eval_lut_amortized(&gin452, lut452);

    std::vector<RotationPoly> lut453;
    std::vector<long (*)(long)> flut453;
    auto lut453idx0 = [](long I) -> long {
        /* GATE 636 (LUT2 _3772_ INIT 0x1 PERM 01) */
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
    Ciphertext gin453 = 1 * gout407[0] + 2 * gout316[0];
    std::vector<Ciphertext> gout453 = ctx.eval_lut_amortized(&gin453, lut453);

    std::vector<RotationPoly> lut454;
    std::vector<long (*)(long)> flut454;
    auto lut454idx0 = [](long I) -> long {
        /* GATE 747 (LUT2 _3883_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut454.push_back(ctx.genrate_lut(lut454idx0));
    flut454.push_back(lut454idx0);
    auto lut454idx1 = [](long I) -> long {
        /* GATE 712 (LUT2 _3848_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut454.push_back(ctx.genrate_lut(lut454idx1));
    flut454.push_back(lut454idx1);
    auto fvec454 = [flut454](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut454[i](I));
        return ret;
    };

    std::cerr << "\rLUT454   ";
    Ciphertext gin454 = 1 * gout411[0] + 2 * gout313[1];
    std::vector<Ciphertext> gout454 = ctx.eval_lut_amortized(&gin454, lut454);

    std::vector<RotationPoly> lut455;
    std::vector<long (*)(long)> flut455;
    auto lut455idx0 = [](long I) -> long {
        /* GATE 167 (LUT2 _3303_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut455.push_back(ctx.genrate_lut(lut455idx0));
    flut455.push_back(lut455idx0);
    auto lut455idx1 = [](long I) -> long {
        /* GATE 134 (LUT2 _3270_ INIT 0x9 PERM 01) */
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
    Ciphertext gin455 = 1 * gout435[0] + 2 * gout405[0];
    std::vector<Ciphertext> gout455 = ctx.eval_lut_amortized(&gin455, lut455);

    std::vector<RotationPoly> lut456;
    std::vector<long (*)(long)> flut456;
    auto lut456idx0 = [](long I) -> long {
        /* GATE 746 (LUT2 _3882_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut456.push_back(ctx.genrate_lut(lut456idx0));
    flut456.push_back(lut456idx0);
    auto lut456idx1 = [](long I) -> long {
        /* GATE 711 (LUT2 _3847_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin456 = 1 * gout454[1] + 2 * gout257[1];
    std::vector<Ciphertext> gout456 = ctx.eval_lut_amortized(&gin456, lut456);

    std::vector<RotationPoly> lut457;
    std::vector<long (*)(long)> flut457;
    auto lut457idx0 = [](long I) -> long {
        /* GATE 526 (LUT2 _3662_ INIT 0x4 PERM 01) */
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
        /* GATE 491 (LUT2 _3627_ INIT 0x9 PERM 01) */
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
    Ciphertext gin457 = 1 * gout406[0] + 2 * gout403[1];
    std::vector<Ciphertext> gout457 = ctx.eval_lut_amortized(&gin457, lut457);

    std::vector<RotationPoly> lut458;
    std::vector<long (*)(long)> flut458;
    auto lut458idx0 = [](long I) -> long {
        /* GATE 923 (LUT2 _4059_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut458.push_back(ctx.genrate_lut(lut458idx0));
    flut458.push_back(lut458idx0);
    auto fvec458 = [flut458](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut458[i](I));
        return ret;
    };

    std::cerr << "\rLUT458   ";
    Ciphertext gin458 = 1 * gout439[0] + 2 * gout419[0];
    std::vector<Ciphertext> gout458 = ctx.eval_lut_amortized(&gin458, lut458);

    std::vector<RotationPoly> lut459;
    std::vector<long (*)(long)> flut459;
    auto lut459idx0 = [](long I) -> long {
        /* GATE 600 (LUT2 _3736_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut459.push_back(ctx.genrate_lut(lut459idx0));
    flut459.push_back(lut459idx0);
    auto lut459idx1 = [](long I) -> long {
        /* GATE 633 (LUT2 _3769_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut459.push_back(ctx.genrate_lut(lut459idx1));
    flut459.push_back(lut459idx1);
    auto fvec459 = [flut459](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut459[i](I));
        return ret;
    };

    std::cerr << "\rLUT459   ";
    Ciphertext gin459 = 1 * gout444[0] + 2 * gout407[1];
    std::vector<Ciphertext> gout459 = ctx.eval_lut_amortized(&gin459, lut459);

    std::vector<RotationPoly> lut460;
    std::vector<long (*)(long)> flut460;
    auto lut460idx0 = [](long I) -> long {
        /* GATE 386 (LUT2 _3522_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut460.push_back(ctx.genrate_lut(lut460idx0));
    flut460.push_back(lut460idx0);
    auto lut460idx1 = [](long I) -> long {
        /* GATE 351 (LUT2 _3487_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin460 = 1 * gout450[0] + 2 * gout312[0];
    std::vector<Ciphertext> gout460 = ctx.eval_lut_amortized(&gin460, lut460);

    std::vector<RotationPoly> lut461;
    std::vector<long (*)(long)> flut461;
    auto lut461idx0 = [](long I) -> long {
        /* GATE 241 (LUT2 _3377_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut461.push_back(ctx.genrate_lut(lut461idx0));
    flut461.push_back(lut461idx0);
    auto fvec461 = [flut461](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut461[i](I));
        return ret;
    };

    std::cerr << "\rLUT461   ";
    Ciphertext gin461 = 1 * gout409[0] + 2 * gout343[0];
    std::vector<Ciphertext> gout461 = ctx.eval_lut_amortized(&gin461, lut461);

    std::vector<RotationPoly> lut462;
    std::vector<long (*)(long)> flut462;
    auto lut462idx0 = [](long I) -> long {
        /* GATE 599 (LUT2 _3735_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut462.push_back(ctx.genrate_lut(lut462idx0));
    flut462.push_back(lut462idx0);
    auto lut462idx1 = [](long I) -> long {
        /* GATE 632 (LUT2 _3768_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
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
    Ciphertext gin462 = 1 * gout459[0] + 2 * gout414[0];
    std::vector<Ciphertext> gout462 = ctx.eval_lut_amortized(&gin462, lut462);

    std::vector<RotationPoly> lut463;
    std::vector<long (*)(long)> flut463;
    auto lut463idx0 = [](long I) -> long {
        /* GATE 29 (LUT2 _3165_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut463.push_back(ctx.genrate_lut(lut463idx0));
    flut463.push_back(lut463idx0);
    auto lut463idx1 = [](long I) -> long {
        /* GATE 55 (LUT2 _3191_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut463.push_back(ctx.genrate_lut(lut463idx1));
    flut463.push_back(lut463idx1);
    auto fvec463 = [flut463](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut463[i](I));
        return ret;
    };

    std::cerr << "\rLUT463   ";
    Ciphertext gin463 = 1 * gout415[0] + 2 * gout199[1];
    std::vector<Ciphertext> gout463 = ctx.eval_lut_amortized(&gin463, lut463);

    std::vector<RotationPoly> lut464;
    std::vector<long (*)(long)> flut464;
    auto lut464idx0 = [](long I) -> long {
        /* GATE 745 (LUT2 _3881_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut464.push_back(ctx.genrate_lut(lut464idx0));
    flut464.push_back(lut464idx0);
    auto fvec464 = [flut464](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut464[i](I));
        return ret;
    };

    std::cerr << "\rLUT464   ";
    Ciphertext gin464 = 1 * gout456[0] + 2 * gout454[0];
    std::vector<Ciphertext> gout464 = ctx.eval_lut_amortized(&gin464, lut464);

    std::vector<RotationPoly> lut465;
    std::vector<long (*)(long)> flut465;
    auto lut465idx0 = [](long I) -> long {
        /* GATE 528 (LUT2 _3664_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut465.push_back(ctx.genrate_lut(lut465idx0));
    flut465.push_back(lut465idx0);
    auto lut465idx1 = [](long I) -> long {
        /* GATE 561 (LUT2 _3697_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut465.push_back(ctx.genrate_lut(lut465idx1));
    flut465.push_back(lut465idx1);
    auto fvec465 = [flut465](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut465[i](I));
        return ret;
    };

    std::cerr << "\rLUT465   ";
    Ciphertext gin465 = 1 * gout432[0] + 2 * gout437[0];
    std::vector<Ciphertext> gout465 = ctx.eval_lut_amortized(&gin465, lut465);

    std::vector<RotationPoly> lut466;
    std::vector<long (*)(long)> flut466;
    auto lut466idx0 = [](long I) -> long {
        /* GATE 631 (LUT2 _3767_ INIT 0x1 PERM 01) */
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
    Ciphertext gin466 = 1 * gout462[1] + 2 * gout459[1];
    std::vector<Ciphertext> gout466 = ctx.eval_lut_amortized(&gin466, lut466);

    std::vector<RotationPoly> lut467;
    std::vector<long (*)(long)> flut467;
    auto lut467idx0 = [](long I) -> long {
        /* GATE 920 (LUT2 _4056_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut467.push_back(ctx.genrate_lut(lut467idx0));
    flut467.push_back(lut467idx0);
    auto lut467idx1 = [](long I) -> long {
        /* GATE 887 (LUT2 _4023_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin467 = 1 * gout452[0] + 2 * gout439[1];
    std::vector<Ciphertext> gout467 = ctx.eval_lut_amortized(&gin467, lut467);

    std::vector<RotationPoly> lut468;
    std::vector<long (*)(long)> flut468;
    auto lut468idx0 = [](long I) -> long {
        /* GATE 960 (LUT2 _4096_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut468.push_back(ctx.genrate_lut(lut468idx0));
    flut468.push_back(lut468idx0);
    auto lut468idx1 = [](long I) -> long {
        /* GATE 926 (LUT2 _4062_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut468.push_back(ctx.genrate_lut(lut468idx1));
    flut468.push_back(lut468idx1);
    auto fvec468 = [flut468](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut468[i](I));
        return ret;
    };

    std::cerr << "\rLUT468   ";
    Ciphertext gin468 = 1 * gout445[1] + 2 * gout272[1];
    std::vector<Ciphertext> gout468 = ctx.eval_lut_amortized(&gin468, lut468);

    std::vector<RotationPoly> lut469;
    std::vector<long (*)(long)> flut469;
    auto lut469idx0 = [](long I) -> long {
        /* GATE 852 (LUT2 _3988_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut469.push_back(ctx.genrate_lut(lut469idx0));
    flut469.push_back(lut469idx0);
    auto fvec469 = [flut469](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut469[i](I));
        return ret;
    };

    std::cerr << "\rLUT469   ";
    Ciphertext gin469 = 1 * gout434[0] + 2 * gout421[1];
    std::vector<Ciphertext> gout469 = ctx.eval_lut_amortized(&gin469, lut469);

    std::vector<RotationPoly> lut470;
    std::vector<long (*)(long)> flut470;
    auto lut470idx0 = [](long I) -> long {
        /* GATE 1056 (LUT2 _4192_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut470.push_back(ctx.genrate_lut(lut470idx0));
    flut470.push_back(lut470idx0);
    auto lut470idx1 = [](long I) -> long {
        /* GATE 81 (LUT2 _3217_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin470 = 1 * gout423[1] + 2 * gout50[0];
    std::vector<Ciphertext> gout470 = ctx.eval_lut_amortized(&gin470, lut470);

    std::vector<RotationPoly> lut471;
    std::vector<long (*)(long)> flut471;
    auto lut471idx0 = [](long I) -> long {
        /* GATE 635 (LUT2 _3771_ INIT 0x9 PERM 01) */
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
        /* GATE 670 (LUT2 _3806_ INIT 0x4 PERM 01) */
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
    Ciphertext gin471 = 1 * gout453[0] + 2 * gout377[1];
    std::vector<Ciphertext> gout471 = ctx.eval_lut_amortized(&gin471, lut471);

    std::vector<RotationPoly> lut472;
    std::vector<long (*)(long)> flut472;
    auto lut472idx0 = [](long I) -> long {
        /* GATE 779 (LUT2 _3915_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut472.push_back(ctx.genrate_lut(lut472idx0));
    flut472.push_back(lut472idx0);
    auto lut472idx1 = [](long I) -> long {
        /* GATE 814 (LUT2 _3950_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin472 = 1 * gout449[0] + 2 * gout382[1];
    std::vector<Ciphertext> gout472 = ctx.eval_lut_amortized(&gin472, lut472);

    std::vector<RotationPoly> lut473;
    std::vector<long (*)(long)> flut473;
    auto lut473idx0 = [](long I) -> long {
        /* GATE 1028 (LUT2 _4164_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut473.push_back(ctx.genrate_lut(lut473idx0));
    flut473.push_back(lut473idx0);
    auto fvec473 = [flut473](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut473[i](I));
        return ret;
    };

    std::cerr << "\rLUT473   ";
    Ciphertext gin473 = 1 * gout425[0] + 2 * gout402[0];
    std::vector<Ciphertext> gout473 = ctx.eval_lut_amortized(&gin473, lut473);

    std::vector<RotationPoly> lut474;
    std::vector<long (*)(long)> flut474;
    auto lut474idx0 = [](long I) -> long {
        /* GATE 922 (LUT2 _4058_ INIT 0x9 PERM 01) */
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
        /* GATE 956 (LUT2 _4092_ INIT 0x4 PERM 01) */
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
    Ciphertext gin474 = 1 * gout458[0] + 2 * gout468[1];
    std::vector<Ciphertext> gout474 = ctx.eval_lut_amortized(&gin474, lut474);

    std::vector<RotationPoly> lut475;
    std::vector<long (*)(long)> flut475;
    auto lut475idx0 = [](long I) -> long {
        /* GATE 885 (LUT2 _4021_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut475.push_back(ctx.genrate_lut(lut475idx0));
    flut475.push_back(lut475idx0);
    auto lut475idx1 = [](long I) -> long {
        /* GATE 851 (LUT2 _3987_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin475 = 1 * gout469[0] + 2 * gout418[1];
    std::vector<Ciphertext> gout475 = ctx.eval_lut_amortized(&gin475, lut475);

    std::vector<RotationPoly> lut476;
    std::vector<long (*)(long)> flut476;
    auto lut476idx0 = [](long I) -> long {
        /* GATE 560 (LUT2 _3696_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut476.push_back(ctx.genrate_lut(lut476idx0));
    flut476.push_back(lut476idx0);
    auto lut476idx1 = [](long I) -> long {
        /* GATE 527 (LUT2 _3663_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin476 = 1 * gout465[0] + 2 * gout351[0];
    std::vector<Ciphertext> gout476 = ctx.eval_lut_amortized(&gin476, lut476);

    std::vector<RotationPoly> lut477;
    std::vector<long (*)(long)> flut477;
    auto lut477idx0 = [](long I) -> long {
        /* GATE 1027 (LUT2 _4163_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin477 = 1 * gout473[0] + 2 * gout296[0];
    std::vector<Ciphertext> gout477 = ctx.eval_lut_amortized(&gin477, lut477);

    std::vector<RotationPoly> lut478;
    std::vector<long (*)(long)> flut478;
    auto lut478idx0 = [](long I) -> long {
        /* GATE 921 (LUT2 _4057_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut478.push_back(ctx.genrate_lut(lut478idx0));
    flut478.push_back(lut478idx0);
    auto lut478idx1 = [](long I) -> long {
        /* GATE 955 (LUT2 _4091_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
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
    Ciphertext gin478 = 1 * gout474[0] + 2 * gout229[0];
    std::vector<Ciphertext> gout478 = ctx.eval_lut_amortized(&gin478, lut478);

    std::vector<RotationPoly> lut479;
    std::vector<long (*)(long)> flut479;
    auto lut479idx0 = [](long I) -> long {
        /* GATE 669 (LUT2 _3805_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut479.push_back(ctx.genrate_lut(lut479idx0));
    flut479.push_back(lut479idx0);
    auto lut479idx1 = [](long I) -> long {
        /* GATE 634 (LUT2 _3770_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
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
    Ciphertext gin479 = 1 * gout471[0] + 2 * gout368[0];
    std::vector<Ciphertext> gout479 = ctx.eval_lut_amortized(&gin479, lut479);

    std::vector<RotationPoly> lut480;
    std::vector<long (*)(long)> flut480;
    auto lut480idx0 = [](long I) -> long {
        /* GATE 778 (LUT2 _3914_ INIT 0x9 PERM 01) */
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
        /* GATE 813 (LUT2 _3949_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
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
    Ciphertext gin480 = 1 * gout472[0] + 2 * gout417[0];
    std::vector<Ciphertext> gout480 = ctx.eval_lut_amortized(&gin480, lut480);

    std::vector<RotationPoly> lut481;
    std::vector<long (*)(long)> flut481;
    auto lut481idx0 = [](long I) -> long {
        /* GATE 343 (LUT2 _3479_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut481.push_back(ctx.genrate_lut(lut481idx0));
    flut481.push_back(lut481idx0);
    auto fvec481 = [flut481](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut481[i](I));
        return ret;
    };

    std::cerr << "\rLUT481   ";
    Ciphertext gin481 = 1 * gout443[1] + 2 * gout438[0];
    std::vector<Ciphertext> gout481 = ctx.eval_lut_amortized(&gin481, lut481);

    std::vector<RotationPoly> lut482;
    std::vector<long (*)(long)> flut482;
    auto lut482idx0 = [](long I) -> long {
        /* GATE 954 (LUT2 _4090_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut482.push_back(ctx.genrate_lut(lut482idx0));
    flut482.push_back(lut482idx0);
    auto fvec482 = [flut482](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut482[i](I));
        return ret;
    };

    std::cerr << "\rLUT482   ";
    Ciphertext gin482 = 1 * gout478[1] + 2 * gout474[1];
    std::vector<Ciphertext> gout482 = ctx.eval_lut_amortized(&gin482, lut482);

    std::vector<RotationPoly> lut483;
    std::vector<long (*)(long)> flut483;
    auto lut483idx0 = [](long I) -> long {
        /* GATE 130 (LUT2 _3266_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut483.push_back(ctx.genrate_lut(lut483idx0));
    flut483.push_back(lut483idx0);
    auto fvec483 = [flut483](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut483[i](I));
        return ret;
    };

    std::cerr << "\rLUT483   ";
    Ciphertext gin483 = 1 * gout446[1] + 2 * gout440[1];
    std::vector<Ciphertext> gout483 = ctx.eval_lut_amortized(&gin483, lut483);

    std::vector<RotationPoly> lut484;
    std::vector<long (*)(long)> flut484;
    auto lut484idx0 = [](long I) -> long {
        /* GATE 992 (LUT2 _4128_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut484.push_back(ctx.genrate_lut(lut484idx0));
    flut484.push_back(lut484idx0);
    auto lut484idx1 = [](long I) -> long {
        /* GATE 1025 (LUT2 _4161_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
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
    Ciphertext gin484 = 1 * gout427[1] + 2 * gout358[0];
    std::vector<Ciphertext> gout484 = ctx.eval_lut_amortized(&gin484, lut484);

    std::vector<RotationPoly> lut485;
    std::vector<long (*)(long)> flut485;
    auto lut485idx0 = [](long I) -> long {
        /* GATE 525 (LUT2 _3661_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut485.push_back(ctx.genrate_lut(lut485idx0));
    flut485.push_back(lut485idx0);
    auto lut485idx1 = [](long I) -> long {
        /* GATE 490 (LUT2 _3626_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut485.push_back(ctx.genrate_lut(lut485idx1));
    flut485.push_back(lut485idx1);
    auto fvec485 = [flut485](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut485[i](I));
        return ret;
    };

    std::cerr << "\rLUT485   ";
    Ciphertext gin485 = 1 * gout457[1] + 2 * gout334[0];
    std::vector<Ciphertext> gout485 = ctx.eval_lut_amortized(&gin485, lut485);

    std::vector<RotationPoly> lut486;
    std::vector<long (*)(long)> flut486;
    auto lut486idx0 = [](long I) -> long {
        /* GATE 133 (LUT2 _3269_ INIT 0x9 PERM 01) */
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
        /* GATE 166 (LUT2 _3302_ INIT 0x4 PERM 10) */
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
    Ciphertext gin486 = 1 * gout455[1] + 2 * gout264[0];
    std::vector<Ciphertext> gout486 = ctx.eval_lut_amortized(&gin486, lut486);

    std::vector<RotationPoly> lut487;
    std::vector<long (*)(long)> flut487;
    auto lut487idx0 = [](long I) -> long {
        /* GATE 666 (LUT2 _3802_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut487.push_back(ctx.genrate_lut(lut487idx0));
    flut487.push_back(lut487idx0);
    auto lut487idx1 = [](long I) -> long {
        /* GATE 630 (LUT2 _3766_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut487.push_back(ctx.genrate_lut(lut487idx1));
    flut487.push_back(lut487idx1);
    auto fvec487 = [flut487](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut487[i](I));
        return ret;
    };

    std::cerr << "\rLUT487   ";
    Ciphertext gin487 = 1 * gout466[0] + 2 * gout479[1];
    std::vector<Ciphertext> gout487 = ctx.eval_lut_amortized(&gin487, lut487);

    std::vector<RotationPoly> lut488;
    std::vector<long (*)(long)> flut488;
    auto lut488idx0 = [](long I) -> long {
        /* GATE 564 (LUT2 _3700_ INIT 0x1 PERM 01) */
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
    Ciphertext gin488 = 1 * gout437[1] + 2 * gout361[1];
    std::vector<Ciphertext> gout488 = ctx.eval_lut_amortized(&gin488, lut488);

    std::vector<RotationPoly> lut489;
    std::vector<long (*)(long)> flut489;
    auto lut489idx0 = [](long I) -> long {
        /* GATE 668 (LUT2 _3804_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut489.push_back(ctx.genrate_lut(lut489idx0));
    flut489.push_back(lut489idx0);
    auto fvec489 = [flut489](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut489[i](I));
        return ret;
    };

    std::cerr << "\rLUT489   ";
    Ciphertext gin489 = 1 * gout479[0] + 2 * gout471[1];
    std::vector<Ciphertext> gout489 = ctx.eval_lut_amortized(&gin489, lut489);

    std::vector<RotationPoly> lut490;
    std::vector<long (*)(long)> flut490;
    auto lut490idx0 = [](long I) -> long {
        /* GATE 202 (LUT2 _3338_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut490.push_back(ctx.genrate_lut(lut490idx0));
    flut490.push_back(lut490idx0);
    auto lut490idx1 = [](long I) -> long {
        /* GATE 169 (LUT2 _3305_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut490.push_back(ctx.genrate_lut(lut490idx1));
    flut490.push_back(lut490idx1);
    auto fvec490 = [flut490](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut490[i](I));
        return ret;
    };

    std::cerr << "\rLUT490   ";
    Ciphertext gin490 = 1 * gout447[0] + 2 * gout347[1];
    std::vector<Ciphertext> gout490 = ctx.eval_lut_amortized(&gin490, lut490);

    std::vector<RotationPoly> lut491;
    std::vector<long (*)(long)> flut491;
    auto lut491idx0 = [](long I) -> long {
        /* GATE 704 (LUT2 _3840_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut491.push_back(ctx.genrate_lut(lut491idx0));
    flut491.push_back(lut491idx0);
    auto lut491idx1 = [](long I) -> long {
        /* GATE 671 (LUT2 _3807_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
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
    Ciphertext gin491 = 1 * gout429[1] + 2 * gout383[0];
    std::vector<Ciphertext> gout491 = ctx.eval_lut_amortized(&gin491, lut491);

    std::vector<RotationPoly> lut492;
    std::vector<long (*)(long)> flut492;
    auto lut492idx0 = [](long I) -> long {
        /* GATE 168 (LUT2 _3304_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut492.push_back(ctx.genrate_lut(lut492idx0));
    flut492.push_back(lut492idx0);
    auto lut492idx1 = [](long I) -> long {
        /* GATE 201 (LUT2 _3337_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut492.push_back(ctx.genrate_lut(lut492idx1));
    flut492.push_back(lut492idx1);
    auto fvec492 = [flut492](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut492[i](I));
        return ret;
    };

    std::cerr << "\rLUT492   ";
    Ciphertext gin492 = 1 * gout490[1] + 2 * gout416[0];
    std::vector<Ciphertext> gout492 = ctx.eval_lut_amortized(&gin492, lut492);

    std::vector<RotationPoly> lut493;
    std::vector<long (*)(long)> flut493;
    auto lut493idx0 = [](long I) -> long {
        /* GATE 310 (LUT2 _3446_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut493.push_back(ctx.genrate_lut(lut493idx0));
    flut493.push_back(lut493idx0);
    auto lut493idx1 = [](long I) -> long {
        /* GATE 275 (LUT2 _3411_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut493.push_back(ctx.genrate_lut(lut493idx1));
    flut493.push_back(lut493idx1);
    auto fvec493 = [flut493](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut493[i](I));
        return ret;
    };

    std::cerr << "\rLUT493   ";
    Ciphertext gin493 = 1 * gout436[0] + 2 * gout310[1];
    std::vector<Ciphertext> gout493 = ctx.eval_lut_amortized(&gin493, lut493);

    std::vector<RotationPoly> lut494;
    std::vector<long (*)(long)> flut494;
    auto lut494idx0 = [](long I) -> long {
        /* GATE 54 (LUT2 _3190_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut494.push_back(ctx.genrate_lut(lut494idx0));
    flut494.push_back(lut494idx0);
    auto fvec494 = [flut494](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut494[i](I));
        return ret;
    };

    std::cerr << "\rLUT494   ";
    Ciphertext gin494 = 1 * gout463[1] + 2 * gout415[1];
    std::vector<Ciphertext> gout494 = ctx.eval_lut_amortized(&gin494, lut494);

    std::vector<RotationPoly> lut495;
    std::vector<long (*)(long)> flut495;
    auto lut495idx0 = [](long I) -> long {
        /* GATE 703 (LUT2 _3839_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut495.push_back(ctx.genrate_lut(lut495idx0));
    flut495.push_back(lut495idx0);
    auto fvec495 = [flut495](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut495[i](I));
        return ret;
    };

    std::cerr << "\rLUT495   ";
    Ciphertext gin495 = 1 * gout491[0] + 2 * gout429[0];
    std::vector<Ciphertext> gout495 = ctx.eval_lut_amortized(&gin495, lut495);

    std::vector<RotationPoly> lut496;
    std::vector<long (*)(long)> flut496;
    auto lut496idx0 = [](long I) -> long {
        /* GATE 129 (LUT2 _3265_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut496.push_back(ctx.genrate_lut(lut496idx0));
    flut496.push_back(lut496idx0);
    auto lut496idx1 = [](long I) -> long {
        /* GATE 163 (LUT2 _3299_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut496.push_back(ctx.genrate_lut(lut496idx1));
    flut496.push_back(lut496idx1);
    auto fvec496 = [flut496](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut496[i](I));
        return ret;
    };

    std::cerr << "\rLUT496   ";
    Ciphertext gin496 = 1 * gout483[0] + 2 * gout486[0];
    std::vector<Ciphertext> gout496 = ctx.eval_lut_amortized(&gin496, lut496);

    std::vector<RotationPoly> lut497;
    std::vector<long (*)(long)> flut497;
    auto lut497idx0 = [](long I) -> long {
        /* GATE 959 (LUT2 _4095_ INIT 0x1 PERM 01) */
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
    Ciphertext gin497 = 1 * gout468[0] + 2 * gout445[0];
    std::vector<Ciphertext> gout497 = ctx.eval_lut_amortized(&gin497, lut497);

    std::vector<RotationPoly> lut498;
    std::vector<long (*)(long)> flut498;
    auto lut498idx0 = [](long I) -> long {
        /* GATE 240 (LUT2 _3376_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut498.push_back(ctx.genrate_lut(lut498idx0));
    flut498.push_back(lut498idx0);
    auto lut498idx1 = [](long I) -> long {
        /* GATE 273 (LUT2 _3409_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut498.push_back(ctx.genrate_lut(lut498idx1));
    flut498.push_back(lut498idx1);
    auto fvec498 = [flut498](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut498[i](I));
        return ret;
    };

    std::cerr << "\rLUT498   ";
    Ciphertext gin498 = 1 * gout461[0] + 2 * gout388[1];
    std::vector<Ciphertext> gout498 = ctx.eval_lut_amortized(&gin498, lut498);

    std::vector<RotationPoly> lut499;
    std::vector<long (*)(long)> flut499;
    auto lut499idx0 = [](long I) -> long {
        /* GATE 848 (LUT2 _3984_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut499.push_back(ctx.genrate_lut(lut499idx0));
    flut499.push_back(lut499idx0);
    auto lut499idx1 = [](long I) -> long {
        /* GATE 815 (LUT2 _3951_ INIT 0x9 PERM 01) */
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
    Ciphertext gin499 = 1 * gout442[0] + 2 * gout288[0];
    std::vector<Ciphertext> gout499 = ctx.eval_lut_amortized(&gin499, lut499);

    std::vector<RotationPoly> lut500;
    std::vector<long (*)(long)> flut500;
    auto lut500idx0 = [](long I) -> long {
        /* GATE 237 (LUT2 _3373_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut500.push_back(ctx.genrate_lut(lut500idx0));
    flut500.push_back(lut500idx0);
    auto lut500idx1 = [](long I) -> long {
        /* GATE 203 (LUT2 _3339_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut500.push_back(ctx.genrate_lut(lut500idx1));
    flut500.push_back(lut500idx1);
    auto fvec500 = [flut500](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut500[i](I));
        return ret;
    };

    std::cerr << "\rLUT500   ";
    Ciphertext gin500 = 1 * gout441[1] + 2 * gout330[0];
    std::vector<Ciphertext> gout500 = ctx.eval_lut_amortized(&gin500, lut500);

    std::vector<RotationPoly> lut501;
    std::vector<long (*)(long)> flut501;
    auto lut501idx0 = [](long I) -> long {
        /* GATE 80 (LUT2 _3216_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut501.push_back(ctx.genrate_lut(lut501idx0));
    flut501.push_back(lut501idx0);
    auto fvec501 = [flut501](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut501[i](I));
        return ret;
    };

    std::cerr << "\rLUT501   ";
    Ciphertext gin501 = 1 * gout470[1] + 2 * gout423[0];
    std::vector<Ciphertext> gout501 = ctx.eval_lut_amortized(&gin501, lut501);

    std::vector<RotationPoly> lut502;
    std::vector<long (*)(long)> flut502;
    auto lut502idx0 = [](long I) -> long {
        /* GATE 919 (LUT2 _4055_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut502.push_back(ctx.genrate_lut(lut502idx0));
    flut502.push_back(lut502idx0);
    auto lut502idx1 = [](long I) -> long {
        /* GATE 886 (LUT2 _4022_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin502 = 1 * gout467[1] + 2 * gout322[0];
    std::vector<Ciphertext> gout502 = ctx.eval_lut_amortized(&gin502, lut502);

    std::vector<RotationPoly> lut503;
    std::vector<long (*)(long)> flut503;
    auto lut503idx0 = [](long I) -> long {
        /* GATE 239 (LUT2 _3375_ INIT 0x9 PERM 01) */
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
        /* GATE 272 (LUT2 _3408_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
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
    Ciphertext gin503 = 1 * gout498[0] + 2 * gout338[0];
    std::vector<Ciphertext> gout503 = ctx.eval_lut_amortized(&gin503, lut503);

    std::vector<RotationPoly> lut504;
    std::vector<long (*)(long)> flut504;
    auto lut504idx0 = [](long I) -> long {
        /* GATE 777 (LUT2 _3913_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut504.push_back(ctx.genrate_lut(lut504idx0));
    flut504.push_back(lut504idx0);
    auto lut504idx1 = [](long I) -> long {
        /* GATE 744 (LUT2 _3880_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut504.push_back(ctx.genrate_lut(lut504idx1));
    flut504.push_back(lut504idx1);
    auto fvec504 = [flut504](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut504[i](I));
        return ret;
    };

    std::cerr << "\rLUT504   ";
    Ciphertext gin504 = 1 * gout464[0] + 2 * gout408[1];
    std::vector<Ciphertext> gout504 = ctx.eval_lut_amortized(&gin504, lut504);

    std::vector<RotationPoly> lut505;
    std::vector<long (*)(long)> flut505;
    auto lut505idx0 = [](long I) -> long {
        /* GATE 488 (LUT2 _3624_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut505.push_back(ctx.genrate_lut(lut505idx0));
    flut505.push_back(lut505idx0);
    auto lut505idx1 = [](long I) -> long {
        /* GATE 455 (LUT2 _3591_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
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
    Ciphertext gin505 = 1 * gout448[1] + 2 * gout161[0];
    std::vector<Ciphertext> gout505 = ctx.eval_lut_amortized(&gin505, lut505);

    std::vector<RotationPoly> lut506;
    std::vector<long (*)(long)> flut506;
    auto lut506idx0 = [](long I) -> long {
        /* GATE 51 (LUT2 _3187_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut506.push_back(ctx.genrate_lut(lut506idx0));
    flut506.push_back(lut506idx0);
    auto lut506idx1 = [](long I) -> long {
        /* GATE 5 (LUT2 _3141_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin506 = 1 * gout398[0] + 2 * gout463[0];
    std::vector<Ciphertext> gout506 = ctx.eval_lut_amortized(&gin506, lut506);

    std::vector<RotationPoly> lut507;
    std::vector<long (*)(long)> flut507;
    auto lut507idx0 = [](long I) -> long {
        /* GATE 707 (LUT2 _3843_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut507.push_back(ctx.genrate_lut(lut507idx0));
    flut507.push_back(lut507idx0);
    auto lut507idx1 = [](long I) -> long {
        /* GATE 742 (LUT2 _3878_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut507.push_back(ctx.genrate_lut(lut507idx1));
    flut507.push_back(lut507idx1);
    auto fvec507 = [flut507](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut507[i](I));
        return ret;
    };

    std::cerr << "\rLUT507   ";
    Ciphertext gin507 = 1 * gout451[0] + 2 * gout456[1];
    std::vector<Ciphertext> gout507 = ctx.eval_lut_amortized(&gin507, lut507);

    std::vector<RotationPoly> lut508;
    std::vector<long (*)(long)> flut508;
    auto lut508idx0 = [](long I) -> long {
        /* GATE 991 (LUT2 _4127_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut508.push_back(ctx.genrate_lut(lut508idx0));
    flut508.push_back(lut508idx0);
    auto lut508idx1 = [](long I) -> long {
        /* GATE 958 (LUT2 _4094_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin508 = 1 * gout497[0] + 2 * gout392[1];
    std::vector<Ciphertext> gout508 = ctx.eval_lut_amortized(&gin508, lut508);

    std::vector<RotationPoly> lut509;
    std::vector<long (*)(long)> flut509;
    auto lut509idx0 = [](long I) -> long {
        /* GATE 812 (LUT2 _3948_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut509.push_back(ctx.genrate_lut(lut509idx0));
    flut509.push_back(lut509idx0);
    auto fvec509 = [flut509](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut509[i](I));
        return ret;
    };

    std::cerr << "\rLUT509   ";
    Ciphertext gin509 = 1 * gout480[1] + 2 * gout472[1];
    std::vector<Ciphertext> gout509 = ctx.eval_lut_amortized(&gin509, lut509);

    std::vector<RotationPoly> lut510;
    std::vector<long (*)(long)> flut510;
    auto lut510idx0 = [](long I) -> long {
        /* GATE 524 (LUT2 _3660_ INIT 0x1 PERM 01) */
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
    Ciphertext gin510 = 1 * gout485[0] + 2 * gout457[0];
    std::vector<Ciphertext> gout510 = ctx.eval_lut_amortized(&gin510, lut510);

    std::vector<RotationPoly> lut511;
    std::vector<long (*)(long)> flut511;
    auto lut511idx0 = [](long I) -> long {
        /* GATE 385 (LUT2 _3521_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut511.push_back(ctx.genrate_lut(lut511idx0));
    flut511.push_back(lut511idx0);
    auto fvec511 = [flut511](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut511[i](I));
        return ret;
    };

    std::cerr << "\rLUT511   ";
    Ciphertext gin511 = 1 * gout460[0] + 2 * gout450[1];
    std::vector<Ciphertext> gout511 = ctx.eval_lut_amortized(&gin511, lut511);

    std::vector<RotationPoly> lut512;
    std::vector<long (*)(long)> flut512;
    auto lut512idx0 = [](long I) -> long {
        /* GATE 741 (LUT2 _3877_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut512.push_back(ctx.genrate_lut(lut512idx0));
    flut512.push_back(lut512idx0);
    auto lut512idx1 = [](long I) -> long {
        /* GATE 706 (LUT2 _3842_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut512.push_back(ctx.genrate_lut(lut512idx1));
    flut512.push_back(lut512idx1);
    auto fvec512 = [flut512](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut512[i](I));
        return ret;
    };

    std::cerr << "\rLUT512   ";
    Ciphertext gin512 = 1 * gout507[0] + 2 * gout221[0];
    std::vector<Ciphertext> gout512 = ctx.eval_lut_amortized(&gin512, lut512);

    std::vector<RotationPoly> lut513;
    std::vector<long (*)(long)> flut513;
    auto lut513idx0 = [](long I) -> long {
        /* GATE 271 (LUT2 _3407_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut513.push_back(ctx.genrate_lut(lut513idx0));
    flut513.push_back(lut513idx0);
    auto fvec513 = [flut513](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut513[i](I));
        return ret;
    };

    std::cerr << "\rLUT513   ";
    Ciphertext gin513 = 1 * gout503[1] + 2 * gout498[1];
    std::vector<Ciphertext> gout513 = ctx.eval_lut_amortized(&gin513, lut513);

    std::vector<RotationPoly> lut514;
    std::vector<long (*)(long)> flut514;
    auto lut514idx0 = [](long I) -> long {
        /* GATE 4 (LUT2 _3140_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut514.push_back(ctx.genrate_lut(lut514idx0));
    flut514.push_back(lut514idx0);
    auto lut514idx1 = [](long I) -> long {
        /* GATE 89 (LUT2 _3225_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
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
    Ciphertext gin514 = 1 * gout376[0] + 2 * gout506[1];
    std::vector<Ciphertext> gout514 = ctx.eval_lut_amortized(&gin514, lut514);

    std::vector<RotationPoly> lut515;
    std::vector<long (*)(long)> flut515;
    auto lut515idx0 = [](long I) -> long {
        /* GATE 382 (LUT2 _3518_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut515.push_back(ctx.genrate_lut(lut515idx0));
    flut515.push_back(lut515idx0);
    auto lut515idx1 = [](long I) -> long {
        /* GATE 347 (LUT2 _3483_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin515 = 1 * gout431[0] + 2 * gout460[1];
    std::vector<Ciphertext> gout515 = ctx.eval_lut_amortized(&gin515, lut515);

    std::vector<RotationPoly> lut516;
    std::vector<long (*)(long)> flut516;
    auto lut516idx0 = [](long I) -> long {
        /* GATE 165 (LUT2 _3301_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut516.push_back(ctx.genrate_lut(lut516idx0));
    flut516.push_back(lut516idx0);
    auto fvec516 = [flut516](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut516[i](I));
        return ret;
    };

    std::cerr << "\rLUT516   ";
    Ciphertext gin516 = 1 * gout486[1] + 2 * gout455[0];
    std::vector<Ciphertext> gout516 = ctx.eval_lut_amortized(&gin516, lut516);

    std::vector<RotationPoly> lut517;
    std::vector<long (*)(long)> flut517;
    auto lut517idx0 = [](long I) -> long {
        /* GATE 563 (LUT2 _3699_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut517.push_back(ctx.genrate_lut(lut517idx0));
    flut517.push_back(lut517idx0);
    auto lut517idx1 = [](long I) -> long {
        /* GATE 598 (LUT2 _3734_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut517.push_back(ctx.genrate_lut(lut517idx1));
    flut517.push_back(lut517idx1);
    auto fvec517 = [flut517](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut517[i](I));
        return ret;
    };

    std::cerr << "\rLUT517   ";
    Ciphertext gin517 = 1 * gout488[0] + 2 * gout397[1];
    std::vector<Ciphertext> gout517 = ctx.eval_lut_amortized(&gin517, lut517);

    std::vector<RotationPoly> lut518;
    std::vector<long (*)(long)> flut518;
    auto lut518idx0 = [](long I) -> long {
        /* GATE 701 (LUT2 _3837_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut518.push_back(ctx.genrate_lut(lut518idx0));
    flut518.push_back(lut518idx0);
    auto lut518idx1 = [](long I) -> long {
        /* GATE 667 (LUT2 _3803_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin518 = 1 * gout489[0] + 2 * gout491[1];
    std::vector<Ciphertext> gout518 = ctx.eval_lut_amortized(&gin518, lut518);

    std::vector<RotationPoly> lut519;
    std::vector<long (*)(long)> flut519;
    auto lut519idx0 = [](long I) -> long {
        /* GATE 845 (LUT2 _3981_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut519.push_back(ctx.genrate_lut(lut519idx0));
    flut519.push_back(lut519idx0);
    auto lut519idx1 = [](long I) -> long {
        /* GATE 811 (LUT2 _3947_ INIT 0x9 PERM 01) */
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
    Ciphertext gin519 = 1 * gout509[0] + 2 * gout499[1];
    std::vector<Ciphertext> gout519 = ctx.eval_lut_amortized(&gin519, lut519);

    std::vector<RotationPoly> lut520;
    std::vector<long (*)(long)> flut520;
    auto lut520idx0 = [](long I) -> long {
        /* GATE 1024 (LUT2 _4160_ INIT 0x1 PERM 01) */
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
    Ciphertext gin520 = 1 * gout484[1] + 2 * gout427[0];
    std::vector<Ciphertext> gout520 = ctx.eval_lut_amortized(&gin520, lut520);

    std::vector<RotationPoly> lut521;
    std::vector<long (*)(long)> flut521;
    auto lut521idx0 = [](long I) -> long {
        /* GATE 884 (LUT2 _4020_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut521.push_back(ctx.genrate_lut(lut521idx0));
    flut521.push_back(lut521idx0);
    auto lut521idx1 = [](long I) -> long {
        /* GATE 850 (LUT2 _3986_ INIT 0x9 PERM 01) */
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
    Ciphertext gin521 = 1 * gout475[1] + 2 * gout297[0];
    std::vector<Ciphertext> gout521 = ctx.eval_lut_amortized(&gin521, lut521);

    std::vector<RotationPoly> lut522;
    std::vector<long (*)(long)> flut522;
    auto lut522idx0 = [](long I) -> long {
        /* GATE 559 (LUT2 _3695_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut522.push_back(ctx.genrate_lut(lut522idx0));
    flut522.push_back(lut522idx0);
    auto fvec522 = [flut522](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut522[i](I));
        return ret;
    };

    std::cerr << "\rLUT522   ";
    Ciphertext gin522 = 1 * gout476[0] + 2 * gout465[1];
    std::vector<Ciphertext> gout522 = ctx.eval_lut_amortized(&gin522, lut522);

    std::vector<RotationPoly> lut523;
    std::vector<long (*)(long)> flut523;
    auto lut523idx0 = [](long I) -> long {
        /* GATE 200 (LUT2 _3336_ INIT 0x1 PERM 01) */
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
    Ciphertext gin523 = 1 * gout492[1] + 2 * gout490[0];
    std::vector<Ciphertext> gout523 = ctx.eval_lut_amortized(&gin523, lut523);

    std::vector<RotationPoly> lut524;
    std::vector<long (*)(long)> flut524;
    auto lut524idx0 = [](long I) -> long {
        /* GATE 743 (LUT2 _3879_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut524.push_back(ctx.genrate_lut(lut524idx0));
    flut524.push_back(lut524idx0);
    auto lut524idx1 = [](long I) -> long {
        /* GATE 776 (LUT2 _3912_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut524.push_back(ctx.genrate_lut(lut524idx1));
    flut524.push_back(lut524idx1);
    auto fvec524 = [flut524](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut524[i](I));
        return ret;
    };

    std::cerr << "\rLUT524   ";
    Ciphertext gin524 = 1 * gout504[1] + 2 * gout336[0];
    std::vector<Ciphertext> gout524 = ctx.eval_lut_amortized(&gin524, lut524);

    std::vector<RotationPoly> lut525;
    std::vector<long (*)(long)> flut525;
    auto lut525idx0 = [](long I) -> long {
        /* GATE 417 (LUT2 _3553_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut525.push_back(ctx.genrate_lut(lut525idx0));
    flut525.push_back(lut525idx0);
    auto lut525idx1 = [](long I) -> long {
        /* GATE 384 (LUT2 _3520_ INIT 0x9 PERM 01) */
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
    Ciphertext gin525 = 1 * gout511[0] + 2 * gout362[1];
    std::vector<Ciphertext> gout525 = ctx.eval_lut_amortized(&gin525, lut525);

    std::vector<RotationPoly> lut526;
    std::vector<long (*)(long)> flut526;
    auto lut526idx0 = [](long I) -> long {
        /* GATE 1023 (LUT2 _4159_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut526.push_back(ctx.genrate_lut(lut526idx0));
    flut526.push_back(lut526idx0);
    auto fvec526 = [flut526](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut526[i](I));
        return ret;
    };

    std::cerr << "\rLUT526   ";
    Ciphertext gin526 = 1 * gout520[0] + 2 * gout477[0];
    std::vector<Ciphertext> gout526 = ctx.eval_lut_amortized(&gin526, lut526);

    std::vector<RotationPoly> lut527;
    std::vector<long (*)(long)> flut527;
    auto lut527idx0 = [](long I) -> long {
        /* GATE 557 (LUT2 _3693_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut527.push_back(ctx.genrate_lut(lut527idx0));
    flut527.push_back(lut527idx0);
    auto lut527idx1 = [](long I) -> long {
        /* GATE 523 (LUT2 _3659_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin527 = 1 * gout510[0] + 2 * gout476[1];
    std::vector<Ciphertext> gout527 = ctx.eval_lut_amortized(&gin527, lut527);

    std::vector<RotationPoly> lut528;
    std::vector<long (*)(long)> flut528;
    auto lut528idx0 = [](long I) -> long {
        /* GATE 918 (LUT2 _4054_ INIT 0x1 PERM 01) */
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
    Ciphertext gin528 = 1 * gout502[0] + 2 * gout467[0];
    std::vector<Ciphertext> gout528 = ctx.eval_lut_amortized(&gin528, lut528);

    std::vector<RotationPoly> lut529;
    std::vector<long (*)(long)> flut529;
    auto lut529idx0 = [](long I) -> long {
        /* GATE 97 (LUT2 _3233_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut529.push_back(ctx.genrate_lut(lut529idx0));
    flut529.push_back(lut529idx0);
    auto lut529idx1 = [](long I) -> long {
        /* GATE 53 (LUT2 _3189_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin529 = 1 * gout494[0] + 2 * gout374[1];
    std::vector<Ciphertext> gout529 = ctx.eval_lut_amortized(&gin529, lut529);

    std::vector<RotationPoly> lut530;
    std::vector<long (*)(long)> flut530;
    auto lut530idx0 = [](long I) -> long {
        /* GATE 383 (LUT2 _3519_ INIT 0x9 PERM 01) */
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
        /* GATE 416 (LUT2 _3552_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
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
    Ciphertext gin530 = 1 * gout525[1] + 2 * gout325[0];
    std::vector<Ciphertext> gout530 = ctx.eval_lut_amortized(&gin530, lut530);

    std::vector<RotationPoly> lut531;
    std::vector<long (*)(long)> flut531;
    auto lut531idx0 = [](long I) -> long {
        /* GATE 415 (LUT2 _3551_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut531.push_back(ctx.genrate_lut(lut531idx0));
    flut531.push_back(lut531idx0);
    auto fvec531 = [flut531](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut531[i](I));
        return ret;
    };

    std::cerr << "\rLUT531   ";
    Ciphertext gin531 = 1 * gout530[1] + 2 * gout525[0];
    std::vector<Ciphertext> gout531 = ctx.eval_lut_amortized(&gin531, lut531);

    std::vector<RotationPoly> lut532;
    std::vector<long (*)(long)> flut532;
    auto lut532idx0 = [](long I) -> long {
        /* GATE 485 (LUT2 _3621_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut532.push_back(ctx.genrate_lut(lut532idx0));
    flut532.push_back(lut532idx0);
    auto lut532idx1 = [](long I) -> long {
        /* GATE 451 (LUT2 _3587_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut532.push_back(ctx.genrate_lut(lut532idx1));
    flut532.push_back(lut532idx1);
    auto fvec532 = [flut532](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut532[i](I));
        return ret;
    };

    std::cerr << "\rLUT532   ";
    Ciphertext gin532 = 1 * gout433[0] + 2 * gout505[1];
    std::vector<Ciphertext> gout532 = ctx.eval_lut_amortized(&gin532, lut532);

    std::vector<RotationPoly> lut533;
    std::vector<long (*)(long)> flut533;
    auto lut533idx0 = [](long I) -> long {
        /* GATE 236 (LUT2 _3372_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut533.push_back(ctx.genrate_lut(lut533idx0));
    flut533.push_back(lut533idx0);
    auto fvec533 = [flut533](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut533[i](I));
        return ret;
    };

    std::cerr << "\rLUT533   ";
    Ciphertext gin533 = 1 * gout500[0] + 2 * gout441[0];
    std::vector<Ciphertext> gout533 = ctx.eval_lut_amortized(&gin533, lut533);

    std::vector<RotationPoly> lut534;
    std::vector<long (*)(long)> flut534;
    auto lut534idx0 = [](long I) -> long {
        /* GATE 164 (LUT2 _3300_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut534.push_back(ctx.genrate_lut(lut534idx0));
    flut534.push_back(lut534idx0);
    auto lut534idx1 = [](long I) -> long {
        /* GATE 198 (LUT2 _3334_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin534 = 1 * gout516[0] + 2 * gout492[0];
    std::vector<Ciphertext> gout534 = ctx.eval_lut_amortized(&gin534, lut534);

    std::vector<RotationPoly> lut535;
    std::vector<long (*)(long)> flut535;
    auto lut535idx0 = [](long I) -> long {
        /* GATE 740 (LUT2 _3876_ INIT 0x1 PERM 01) */
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
    Ciphertext gin535 = 1 * gout512[0] + 2 * gout507[1];
    std::vector<Ciphertext> gout535 = ctx.eval_lut_amortized(&gin535, lut535);

    std::vector<RotationPoly> lut536;
    std::vector<long (*)(long)> flut536;
    auto lut536idx0 = [](long I) -> long {
        /* GATE 346 (LUT2 _3482_ INIT 0x9 PERM 01) */
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
        /* GATE 381 (LUT2 _3517_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
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
    Ciphertext gin536 = 1 * gout515[1] + 2 * gout314[0];
    std::vector<Ciphertext> gout536 = ctx.eval_lut_amortized(&gin536, lut536);

    std::vector<RotationPoly> lut537;
    std::vector<long (*)(long)> flut537;
    auto lut537idx0 = [](long I) -> long {
        /* GATE 487 (LUT2 _3623_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut537.push_back(ctx.genrate_lut(lut537idx0));
    flut537.push_back(lut537idx0);
    auto fvec537 = [flut537](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut537[i](I));
        return ret;
    };

    std::cerr << "\rLUT537   ";
    Ciphertext gin537 = 1 * gout505[0] + 2 * gout448[0];
    std::vector<Ciphertext> gout537 = ctx.eval_lut_amortized(&gin537, lut537);

    std::vector<RotationPoly> lut538;
    std::vector<long (*)(long)> flut538;
    auto lut538idx0 = [](long I) -> long {
        /* GATE 309 (LUT2 _3445_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut538.push_back(ctx.genrate_lut(lut538idx0));
    flut538.push_back(lut538idx0);
    auto lut538idx1 = [](long I) -> long {
        /* GATE 274 (LUT2 _3410_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut538.push_back(ctx.genrate_lut(lut538idx1));
    flut538.push_back(lut538idx1);
    auto fvec538 = [flut538](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut538[i](I));
        return ret;
    };

    std::cerr << "\rLUT538   ";
    Ciphertext gin538 = 1 * gout493[1] + 2 * gout265[0];
    std::vector<Ciphertext> gout538 = ctx.eval_lut_amortized(&gin538, lut538);

    std::vector<RotationPoly> lut539;
    std::vector<long (*)(long)> flut539;
    auto lut539idx0 = [](long I) -> long {
        /* GATE 3 (LUT2 _3139_ INIT 0x1 PERM 01) */
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
    Ciphertext gin539 = 1 * gout514[0] + 2 * gout506[0];
    std::vector<Ciphertext> gout539 = ctx.eval_lut_amortized(&gin539, lut539);

    std::vector<RotationPoly> lut540;
    std::vector<long (*)(long)> flut540;
    auto lut540idx0 = [](long I) -> long {
        /* GATE 847 (LUT2 _3983_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut540.push_back(ctx.genrate_lut(lut540idx0));
    flut540.push_back(lut540idx0);
    auto fvec540 = [flut540](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut540[i](I));
        return ret;
    };

    std::cerr << "\rLUT540   ";
    Ciphertext gin540 = 1 * gout499[0] + 2 * gout442[1];
    std::vector<Ciphertext> gout540 = ctx.eval_lut_amortized(&gin540, lut540);

    std::vector<RotationPoly> lut541;
    std::vector<long (*)(long)> flut541;
    auto lut541idx0 = [](long I) -> long {
        /* GATE 775 (LUT2 _3911_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut541.push_back(ctx.genrate_lut(lut541idx0));
    flut541.push_back(lut541idx0);
    auto fvec541 = [flut541](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut541[i](I));
        return ret;
    };

    std::cerr << "\rLUT541   ";
    Ciphertext gin541 = 1 * gout524[1] + 2 * gout504[0];
    std::vector<Ciphertext> gout541 = ctx.eval_lut_amortized(&gin541, lut541);

    std::vector<RotationPoly> lut542;
    std::vector<long (*)(long)> flut542;
    auto lut542idx0 = [](long I) -> long {
        /* GATE 235 (LUT2 _3371_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut542.push_back(ctx.genrate_lut(lut542idx0));
    flut542.push_back(lut542idx0);
    auto lut542idx1 = [](long I) -> long {
        /* GATE 269 (LUT2 _3405_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut542.push_back(ctx.genrate_lut(lut542idx1));
    flut542.push_back(lut542idx1);
    auto fvec542 = [flut542](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut542[i](I));
        return ret;
    };

    std::cerr << "\rLUT542   ";
    Ciphertext gin542 = 1 * gout533[0] + 2 * gout503[0];
    std::vector<Ciphertext> gout542 = ctx.eval_lut_amortized(&gin542, lut542);

    std::vector<RotationPoly> lut543;
    std::vector<long (*)(long)> flut543;
    auto lut543idx0 = [](long I) -> long {
        /* GATE 883 (LUT2 _4019_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut543.push_back(ctx.genrate_lut(lut543idx0));
    flut543.push_back(lut543idx0);
    auto fvec543 = [flut543](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut543[i](I));
        return ret;
    };

    std::cerr << "\rLUT543   ";
    Ciphertext gin543 = 1 * gout521[0] + 2 * gout475[0];
    std::vector<Ciphertext> gout543 = ctx.eval_lut_amortized(&gin543, lut543);

    std::vector<RotationPoly> lut544;
    std::vector<long (*)(long)> flut544;
    auto lut544idx0 = [](long I) -> long {
        /* GATE 1054 (LUT2 _4190_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut544.push_back(ctx.genrate_lut(lut544idx0));
    flut544.push_back(lut544idx0);
    auto lut544idx1 = [](long I) -> long {
        /* GATE 79 (LUT2 _3215_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut544.push_back(ctx.genrate_lut(lut544idx1));
    flut544.push_back(lut544idx1);
    auto fvec544 = [flut544](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut544[i](I));
        return ret;
    };

    std::cerr << "\rLUT544   ";
    Ciphertext gin544 = 1 * gout501[0] + 2 * gout514[1];
    std::vector<Ciphertext> gout544 = ctx.eval_lut_amortized(&gin544, lut544);

    std::vector<RotationPoly> lut545;
    std::vector<long (*)(long)> flut545;
    auto lut545idx0 = [](long I) -> long {
        /* GATE 882 (LUT2 _4018_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut545.push_back(ctx.genrate_lut(lut545idx0));
    flut545.push_back(lut545idx0);
    auto lut545idx1 = [](long I) -> long {
        /* GATE 916 (LUT2 _4052_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
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
    Ciphertext gin545 = 1 * gout543[0] + 2 * gout502[1];
    std::vector<Ciphertext> gout545 = ctx.eval_lut_amortized(&gin545, lut545);

    std::vector<RotationPoly> lut546;
    std::vector<long (*)(long)> flut546;
    auto lut546idx0 = [](long I) -> long {
        /* GATE 990 (LUT2 _4126_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut546.push_back(ctx.genrate_lut(lut546idx0));
    flut546.push_back(lut546idx0);
    auto lut546idx1 = [](long I) -> long {
        /* GATE 957 (LUT2 _4093_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut546.push_back(ctx.genrate_lut(lut546idx1));
    flut546.push_back(lut546idx1);
    auto fvec546 = [flut546](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut546[i](I));
        return ret;
    };

    std::cerr << "\rLUT546   ";
    Ciphertext gin546 = 1 * gout508[1] + 2 * gout354[0];
    std::vector<Ciphertext> gout546 = ctx.eval_lut_amortized(&gin546, lut546);

    std::vector<RotationPoly> lut547;
    std::vector<long (*)(long)> flut547;
    auto lut547idx0 = [](long I) -> long {
        /* GATE 774 (LUT2 _3910_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut547.push_back(ctx.genrate_lut(lut547idx0));
    flut547.push_back(lut547idx0);
    auto lut547idx1 = [](long I) -> long {
        /* GATE 810 (LUT2 _3946_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut547.push_back(ctx.genrate_lut(lut547idx1));
    flut547.push_back(lut547idx1);
    auto fvec547 = [flut547](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut547[i](I));
        return ret;
    };

    std::cerr << "\rLUT547   ";
    Ciphertext gin547 = 1 * gout541[0] + 2 * gout480[0];
    std::vector<Ciphertext> gout547 = ctx.eval_lut_amortized(&gin547, lut547);

    std::vector<RotationPoly> lut548;
    std::vector<long (*)(long)> flut548;
    auto lut548idx0 = [](long I) -> long {
        /* GATE 270 (LUT2 _3406_ INIT 0x9 PERM 01) */
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
    auto lut548idx1 = [](long I) -> long {
        /* GATE 306 (LUT2 _3442_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut548.push_back(ctx.genrate_lut(lut548idx1));
    flut548.push_back(lut548idx1);
    auto fvec548 = [flut548](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut548[i](I));
        return ret;
    };

    std::cerr << "\rLUT548   ";
    Ciphertext gin548 = 1 * gout513[0] + 2 * gout538[1];
    std::vector<Ciphertext> gout548 = ctx.eval_lut_amortized(&gin548, lut548);

    std::vector<RotationPoly> lut549;
    std::vector<long (*)(long)> flut549;
    auto lut549idx0 = [](long I) -> long {
        /* GATE 702 (LUT2 _3838_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut549.push_back(ctx.genrate_lut(lut549idx0));
    flut549.push_back(lut549idx0);
    auto lut549idx1 = [](long I) -> long {
        /* GATE 738 (LUT2 _3874_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut549.push_back(ctx.genrate_lut(lut549idx1));
    flut549.push_back(lut549idx1);
    auto fvec549 = [flut549](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut549[i](I));
        return ret;
    };

    std::cerr << "\rLUT549   ";
    Ciphertext gin549 = 1 * gout495[0] + 2 * gout512[1];
    std::vector<Ciphertext> gout549 = ctx.eval_lut_amortized(&gin549, lut549);

    std::vector<RotationPoly> lut550;
    std::vector<long (*)(long)> flut550;
    auto lut550idx0 = [](long I) -> long {
        /* GATE 597 (LUT2 _3733_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut550.push_back(ctx.genrate_lut(lut550idx0));
    flut550.push_back(lut550idx0);
    auto lut550idx1 = [](long I) -> long {
        /* GATE 562 (LUT2 _3698_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin550 = 1 * gout517[0] + 2 * gout424[0];
    std::vector<Ciphertext> gout550 = ctx.eval_lut_amortized(&gin550, lut550);

    std::vector<RotationPoly> lut551;
    std::vector<long (*)(long)> flut551;
    auto lut551idx0 = [](long I) -> long {
        /* GATE 342 (LUT2 _3478_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut551.push_back(ctx.genrate_lut(lut551idx0));
    flut551.push_back(lut551idx0);
    auto lut551idx1 = [](long I) -> long {
        /* GATE 378 (LUT2 _3514_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut551.push_back(ctx.genrate_lut(lut551idx1));
    flut551.push_back(lut551idx1);
    auto fvec551 = [flut551](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut551[i](I));
        return ret;
    };

    std::cerr << "\rLUT551   ";
    Ciphertext gin551 = 1 * gout481[0] + 2 * gout536[0];
    std::vector<Ciphertext> gout551 = ctx.eval_lut_amortized(&gin551, lut551);

    std::vector<RotationPoly> lut552;
    std::vector<long (*)(long)> flut552;
    auto lut552idx0 = [](long I) -> long {
        /* GATE 594 (LUT2 _3730_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut552.push_back(ctx.genrate_lut(lut552idx0));
    flut552.push_back(lut552idx0);
    auto lut552idx1 = [](long I) -> long {
        /* GATE 558 (LUT2 _3694_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
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
    Ciphertext gin552 = 1 * gout522[0] + 2 * gout550[1];
    std::vector<Ciphertext> gout552 = ctx.eval_lut_amortized(&gin552, lut552);

    std::vector<RotationPoly> lut553;
    std::vector<long (*)(long)> flut553;
    auto lut553idx0 = [](long I) -> long {
        /* GATE 233 (LUT2 _3369_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut553.push_back(ctx.genrate_lut(lut553idx0));
    flut553.push_back(lut553idx0);
    auto lut553idx1 = [](long I) -> long {
        /* GATE 199 (LUT2 _3335_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut553.push_back(ctx.genrate_lut(lut553idx1));
    flut553.push_back(lut553idx1);
    auto lut553idx2 = [](long I) -> long {
        /* GATE 234 (LUT2 _3370_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut553.push_back(ctx.genrate_lut(lut553idx2));
    flut553.push_back(lut553idx2);
    auto fvec553 = [flut553](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 3; ++i)
            ret.push_back(flut553[i](I));
        return ret;
    };

    std::cerr << "\rLUT553   ";
    Ciphertext gin553 = 1 * gout523[0] + 2 * gout500[1];
    std::vector<Ciphertext> gout553 = ctx.eval_lut_amortized(&gin553, lut553);

    std::vector<RotationPoly> lut554;
    std::vector<long (*)(long)> flut554;
    auto lut554idx0 = [](long I) -> long {
        /* GATE 952 (LUT2 _4088_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut554.push_back(ctx.genrate_lut(lut554idx0));
    flut554.push_back(lut554idx0);
    auto lut554idx1 = [](long I) -> long {
        /* GATE 917 (LUT2 _4053_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut554.push_back(ctx.genrate_lut(lut554idx1));
    flut554.push_back(lut554idx1);
    auto lut554idx2 = [](long I) -> long {
        /* GATE 951 (LUT2 _4087_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut554.push_back(ctx.genrate_lut(lut554idx2));
    flut554.push_back(lut554idx2);
    auto fvec554 = [flut554](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 3; ++i)
            ret.push_back(flut554[i](I));
        return ret;
    };

    std::cerr << "\rLUT554   ";
    Ciphertext gin554 = 1 * gout528[0] + 2 * gout478[0];
    std::vector<Ciphertext> gout554 = ctx.eval_lut_amortized(&gin554, lut554);

    std::vector<RotationPoly> lut555;
    std::vector<long (*)(long)> flut555;
    auto lut555idx0 = [](long I) -> long {
        /* GATE 989 (LUT2 _4125_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut555.push_back(ctx.genrate_lut(lut555idx0));
    flut555.push_back(lut555idx0);
    auto fvec555 = [flut555](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut555[i](I));
        return ret;
    };

    std::cerr << "\rLUT555   ";
    Ciphertext gin555 = 1 * gout546[0] + 2 * gout508[0];
    std::vector<Ciphertext> gout555 = ctx.eval_lut_amortized(&gin555, lut555);

    std::vector<RotationPoly> lut556;
    std::vector<long (*)(long)> flut556;
    auto lut556idx0 = [](long I) -> long {
        /* GATE 739 (LUT2 _3875_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut556.push_back(ctx.genrate_lut(lut556idx0));
    flut556.push_back(lut556idx0);
    auto lut556idx1 = [](long I) -> long {
        /* GATE 773 (LUT2 _3909_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut556.push_back(ctx.genrate_lut(lut556idx1));
    flut556.push_back(lut556idx1);
    auto fvec556 = [flut556](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut556[i](I));
        return ret;
    };

    std::cerr << "\rLUT556   ";
    Ciphertext gin556 = 1 * gout535[0] + 2 * gout524[0];
    std::vector<Ciphertext> gout556 = ctx.eval_lut_amortized(&gin556, lut556);

    std::vector<RotationPoly> lut557;
    std::vector<long (*)(long)> flut557;
    auto lut557idx0 = [](long I) -> long {
        /* GATE 450 (LUT2 _3586_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut557.push_back(ctx.genrate_lut(lut557idx0));
    flut557.push_back(lut557idx0);
    auto lut557idx1 = [](long I) -> long {
        /* GATE 414 (LUT2 _3550_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut557.push_back(ctx.genrate_lut(lut557idx1));
    flut557.push_back(lut557idx1);
    auto fvec557 = [flut557](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut557[i](I));
        return ret;
    };

    std::cerr << "\rLUT557   ";
    Ciphertext gin557 = 1 * gout531[0] + 2 * gout430[1];
    std::vector<Ciphertext> gout557 = ctx.eval_lut_amortized(&gin557, lut557);

    std::vector<RotationPoly> lut558;
    std::vector<long (*)(long)> flut558;
    auto lut558idx0 = [](long I) -> long {
        /* GATE 305 (LUT2 _3441_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut558.push_back(ctx.genrate_lut(lut558idx0));
    flut558.push_back(lut558idx0);
    auto fvec558 = [flut558](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut558[i](I));
        return ret;
    };

    std::cerr << "\rLUT558   ";
    Ciphertext gin558 = 1 * gout542[1] + 2 * gout548[0];
    std::vector<Ciphertext> gout558 = ctx.eval_lut_amortized(&gin558, lut558);

    std::vector<RotationPoly> lut559;
    std::vector<long (*)(long)> flut559;
    auto lut559idx0 = [](long I) -> long {
        /* GATE 52 (LUT2 _3188_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut559.push_back(ctx.genrate_lut(lut559idx0));
    flut559.push_back(lut559idx0);
    auto lut559idx1 = [](long I) -> long {
        /* GATE 96 (LUT2 _3232_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut559.push_back(ctx.genrate_lut(lut559idx1));
    flut559.push_back(lut559idx1);
    auto fvec559 = [flut559](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut559[i](I));
        return ret;
    };

    std::cerr << "\rLUT559   ";
    Ciphertext gin559 = 1 * gout529[1] + 2 * gout210[0];
    std::vector<Ciphertext> gout559 = ctx.eval_lut_amortized(&gin559, lut559);

    std::vector<RotationPoly> lut560;
    std::vector<long (*)(long)> flut560;
    auto lut560idx0 = [](long I) -> long {
        /* GATE 380 (LUT2 _3516_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut560.push_back(ctx.genrate_lut(lut560idx0));
    flut560.push_back(lut560idx0);
    auto fvec560 = [flut560](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut560[i](I));
        return ret;
    };

    std::cerr << "\rLUT560   ";
    Ciphertext gin560 = 1 * gout536[1] + 2 * gout515[0];
    std::vector<Ciphertext> gout560 = ctx.eval_lut_amortized(&gin560, lut560);

    std::vector<RotationPoly> lut561;
    std::vector<long (*)(long)> flut561;
    auto lut561idx0 = [](long I) -> long {
        /* GATE 304 (LUT2 _3440_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut561.push_back(ctx.genrate_lut(lut561idx0));
    flut561.push_back(lut561idx0);
    auto fvec561 = [flut561](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut561[i](I));
        return ret;
    };

    std::cerr << "\rLUT561   ";
    Ciphertext gin561 = 1 * gout558[0] + 2 * gout548[1];
    std::vector<Ciphertext> gout561 = ctx.eval_lut_amortized(&gin561, lut561);

    std::vector<RotationPoly> lut562;
    std::vector<long (*)(long)> flut562;
    auto lut562idx0 = [](long I) -> long {
        /* GATE 486 (LUT2 _3622_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut562.push_back(ctx.genrate_lut(lut562idx0));
    flut562.push_back(lut562idx0);
    auto lut562idx1 = [](long I) -> long {
        /* GATE 522 (LUT2 _3658_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut562.push_back(ctx.genrate_lut(lut562idx1));
    flut562.push_back(lut562idx1);
    auto fvec562 = [flut562](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut562[i](I));
        return ret;
    };

    std::cerr << "\rLUT562   ";
    Ciphertext gin562 = 1 * gout537[0] + 2 * gout485[1];
    std::vector<Ciphertext> gout562 = ctx.eval_lut_amortized(&gin562, lut562);

    std::vector<RotationPoly> lut563;
    std::vector<long (*)(long)> flut563;
    auto lut563idx0 = [](long I) -> long {
        /* GATE 308 (LUT2 _3444_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut563.push_back(ctx.genrate_lut(lut563idx0));
    flut563.push_back(lut563idx0);
    auto fvec563 = [flut563](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut563[i](I));
        return ret;
    };

    std::cerr << "\rLUT563   ";
    Ciphertext gin563 = 1 * gout538[0] + 2 * gout493[0];
    std::vector<Ciphertext> gout563 = ctx.eval_lut_amortized(&gin563, lut563);

    std::vector<RotationPoly> lut564;
    std::vector<long (*)(long)> flut564;
    auto lut564idx0 = [](long I) -> long {
        /* GATE 809 (LUT2 _3945_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut564.push_back(ctx.genrate_lut(lut564idx0));
    flut564.push_back(lut564idx0);
    auto fvec564 = [flut564](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut564[i](I));
        return ret;
    };

    std::cerr << "\rLUT564   ";
    Ciphertext gin564 = 1 * gout556[1] + 2 * gout547[0];
    std::vector<Ciphertext> gout564 = ctx.eval_lut_amortized(&gin564, lut564);

    std::vector<RotationPoly> lut565;
    std::vector<long (*)(long)> flut565;
    auto lut565idx0 = [](long I) -> long {
        /* GATE 521 (LUT2 _3657_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut565.push_back(ctx.genrate_lut(lut565idx0));
    flut565.push_back(lut565idx0);
    auto fvec565 = [flut565](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut565[i](I));
        return ret;
    };

    std::cerr << "\rLUT565   ";
    Ciphertext gin565 = 1 * gout532[0] + 2 * gout562[0];
    std::vector<Ciphertext> gout565 = ctx.eval_lut_amortized(&gin565, lut565);

    std::vector<RotationPoly> lut566;
    std::vector<long (*)(long)> flut566;
    auto lut566idx0 = [](long I) -> long {
        /* GATE 93 (LUT2 _3229_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut566.push_back(ctx.genrate_lut(lut566idx0));
    flut566.push_back(lut566idx0);
    auto lut566idx1 = [](long I) -> long {
        /* GATE 2 (LUT2 _3138_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut566.push_back(ctx.genrate_lut(lut566idx1));
    flut566.push_back(lut566idx1);
    auto fvec566 = [flut566](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut566[i](I));
        return ret;
    };

    std::cerr << "\rLUT566   ";
    Ciphertext gin566 = 1 * gout539[0] + 2 * gout559[0];
    std::vector<Ciphertext> gout566 = ctx.eval_lut_amortized(&gin566, lut566);

    std::vector<RotationPoly> lut567;
    std::vector<long (*)(long)> flut567;
    auto lut567idx0 = [](long I) -> long {
        /* GATE 1022 (LUT2 _4158_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut567.push_back(ctx.genrate_lut(lut567idx0));
    flut567.push_back(lut567idx0);
    auto lut567idx1 = [](long I) -> long {
        /* GATE 988 (LUT2 _4124_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut567.push_back(ctx.genrate_lut(lut567idx1));
    flut567.push_back(lut567idx1);
    auto fvec567 = [flut567](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut567[i](I));
        return ret;
    };

    std::cerr << "\rLUT567   ";
    Ciphertext gin567 = 1 * gout555[0] + 2 * gout484[0];
    std::vector<Ciphertext> gout567 = ctx.eval_lut_amortized(&gin567, lut567);

    std::vector<RotationPoly> lut568;
    std::vector<long (*)(long)> flut568;
    auto lut568idx0 = [](long I) -> long {
        /* GATE 808 (LUT2 _3944_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut568.push_back(ctx.genrate_lut(lut568idx0));
    flut568.push_back(lut568idx0);
    auto fvec568 = [flut568](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut568[i](I));
        return ret;
    };

    std::cerr << "\rLUT568   ";
    Ciphertext gin568 = 1 * gout564[0] + 2 * gout547[1];
    std::vector<Ciphertext> gout568 = ctx.eval_lut_amortized(&gin568, lut568);

    std::vector<RotationPoly> lut569;
    std::vector<long (*)(long)> flut569;
    auto lut569idx0 = [](long I) -> long {
        /* GATE 92 (LUT2 _3228_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut569.push_back(ctx.genrate_lut(lut569idx0));
    flut569.push_back(lut569idx0);
    auto lut569idx1 = [](long I) -> long {
        /* GATE 1 (LUT2 _3137_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut569.push_back(ctx.genrate_lut(lut569idx1));
    flut569.push_back(lut569idx1);
    auto fvec569 = [flut569](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut569[i](I));
        return ret;
    };

    std::cerr << "\rLUT569   ";
    Ciphertext gin569 = 1 * gout566[1] + 2 * gout544[1];
    std::vector<Ciphertext> gout569 = ctx.eval_lut_amortized(&gin569, lut569);

    std::vector<RotationPoly> lut570;
    std::vector<long (*)(long)> flut570;
    auto lut570idx0 = [](long I) -> long {
        /* GATE 737 (LUT2 _3873_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut570.push_back(ctx.genrate_lut(lut570idx0));
    flut570.push_back(lut570idx0);
    auto fvec570 = [flut570](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut570[i](I));
        return ret;
    };

    std::cerr << "\rLUT570   ";
    Ciphertext gin570 = 1 * gout518[0] + 2 * gout549[0];
    std::vector<Ciphertext> gout570 = ctx.eval_lut_amortized(&gin570, lut570);

    std::vector<RotationPoly> lut571;
    std::vector<long (*)(long)> flut571;
    auto lut571idx0 = [](long I) -> long {
        /* GATE 95 (LUT2 _3231_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut571.push_back(ctx.genrate_lut(lut571idx0));
    flut571.push_back(lut571idx0);
    auto fvec571 = [flut571](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut571[i](I));
        return ret;
    };

    std::cerr << "\rLUT571   ";
    Ciphertext gin571 = 1 * gout559[1] + 2 * gout529[0];
    std::vector<Ciphertext> gout571 = ctx.eval_lut_amortized(&gin571, lut571);

    std::vector<RotationPoly> lut572;
    std::vector<long (*)(long)> flut572;
    auto lut572idx0 = [](long I) -> long {
        /* GATE 881 (LUT2 _4017_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut572.push_back(ctx.genrate_lut(lut572idx0));
    flut572.push_back(lut572idx0);
    auto lut572idx1 = [](long I) -> long {
        /* GATE 846 (LUT2 _3982_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut572.push_back(ctx.genrate_lut(lut572idx1));
    flut572.push_back(lut572idx1);
    auto lut572idx2 = [](long I) -> long {
        /* GATE 880 (LUT2 _4016_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut572.push_back(ctx.genrate_lut(lut572idx2));
    flut572.push_back(lut572idx2);
    auto fvec572 = [flut572](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 3; ++i)
            ret.push_back(flut572[i](I));
        return ret;
    };

    std::cerr << "\rLUT572   ";
    Ciphertext gin572 = 1 * gout540[0] + 2 * gout521[1];
    std::vector<Ciphertext> gout572 = ctx.eval_lut_amortized(&gin572, lut572);

    std::vector<RotationPoly> lut573;
    std::vector<long (*)(long)> flut573;
    auto lut573idx0 = [](long I) -> long {
        /* GATE 736 (LUT2 _3872_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut573.push_back(ctx.genrate_lut(lut573idx0));
    flut573.push_back(lut573idx0);
    auto fvec573 = [flut573](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut573[i](I));
        return ret;
    };

    std::cerr << "\rLUT573   ";
    Ciphertext gin573 = 1 * gout570[0] + 2 * gout549[1];
    std::vector<Ciphertext> gout573 = ctx.eval_lut_amortized(&gin573, lut573);

    std::vector<RotationPoly> lut574;
    std::vector<long (*)(long)> flut574;
    auto lut574idx0 = [](long I) -> long {
        /* GATE 307 (LUT2 _3443_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut574.push_back(ctx.genrate_lut(lut574idx0));
    flut574.push_back(lut574idx0);
    auto lut574idx1 = [](long I) -> long {
        /* GATE 341 (LUT2 _3477_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut574.push_back(ctx.genrate_lut(lut574idx1));
    flut574.push_back(lut574idx1);
    auto fvec574 = [flut574](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut574[i](I));
        return ret;
    };

    std::cerr << "\rLUT574   ";
    Ciphertext gin574 = 1 * gout563[0] + 2 * gout443[0];
    std::vector<Ciphertext> gout574 = ctx.eval_lut_amortized(&gin574, lut574);

    std::vector<RotationPoly> lut575;
    std::vector<long (*)(long)> flut575;
    auto lut575idx0 = [](long I) -> long {
        /* GATE 593 (LUT2 _3729_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut575.push_back(ctx.genrate_lut(lut575idx0));
    flut575.push_back(lut575idx0);
    auto fvec575 = [flut575](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut575[i](I));
        return ret;
    };

    std::cerr << "\rLUT575   ";
    Ciphertext gin575 = 1 * gout527[0] + 2 * gout552[1];
    std::vector<Ciphertext> gout575 = ctx.eval_lut_amortized(&gin575, lut575);

    std::vector<RotationPoly> lut576;
    std::vector<long (*)(long)> flut576;
    auto lut576idx0 = [](long I) -> long {
        /* GATE 520 (LUT2 _3656_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut576.push_back(ctx.genrate_lut(lut576idx0));
    flut576.push_back(lut576idx0);
    auto fvec576 = [flut576](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut576[i](I));
        return ret;
    };

    std::cerr << "\rLUT576   ";
    Ciphertext gin576 = 1 * gout565[0] + 2 * gout562[1];
    std::vector<Ciphertext> gout576 = ctx.eval_lut_amortized(&gin576, lut576);

    std::vector<RotationPoly> lut577;
    std::vector<long (*)(long)> flut577;
    auto lut577idx0 = [](long I) -> long {
        /* GATE 592 (LUT2 _3728_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut577.push_back(ctx.genrate_lut(lut577idx0));
    flut577.push_back(lut577idx0);
    auto fvec577 = [flut577](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut577[i](I));
        return ret;
    };

    std::cerr << "\rLUT577   ";
    Ciphertext gin577 = 1 * gout575[0] + 2 * gout552[0];
    std::vector<Ciphertext> gout577 = ctx.eval_lut_amortized(&gin577, lut577);

    std::vector<RotationPoly> lut578;
    std::vector<long (*)(long)> flut578;
    auto lut578idx0 = [](long I) -> long {
        /* GATE 413 (LUT2 _3549_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut578.push_back(ctx.genrate_lut(lut578idx0));
    flut578.push_back(lut578idx0);
    auto lut578idx1 = [](long I) -> long {
        /* GATE 379 (LUT2 _3515_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut578.push_back(ctx.genrate_lut(lut578idx1));
    flut578.push_back(lut578idx1);
    auto fvec578 = [flut578](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut578[i](I));
        return ret;
    };

    std::cerr << "\rLUT578   ";
    Ciphertext gin578 = 1 * gout560[0] + 2 * gout530[0];
    std::vector<Ciphertext> gout578 = ctx.eval_lut_amortized(&gin578, lut578);

    std::vector<RotationPoly> lut579;
    std::vector<long (*)(long)> flut579;
    auto lut579idx0 = [](long I) -> long {
        /* GATE 94 (LUT2 _3230_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut579.push_back(ctx.genrate_lut(lut579idx0));
    flut579.push_back(lut579idx0);
    auto lut579idx1 = [](long I) -> long {
        /* GATE 128 (LUT2 _3264_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut579.push_back(ctx.genrate_lut(lut579idx1));
    flut579.push_back(lut579idx1);
    auto fvec579 = [flut579](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut579[i](I));
        return ret;
    };

    std::cerr << "\rLUT579   ";
    Ciphertext gin579 = 1 * gout571[0] + 2 * gout446[0];
    std::vector<Ciphertext> gout579 = ctx.eval_lut_amortized(&gin579, lut579);

    std::vector<RotationPoly> lut580;
    std::vector<long (*)(long)> flut580;
    auto lut580idx0 = [](long I) -> long {
        /* GATE 987 (LUT2 _4123_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut580.push_back(ctx.genrate_lut(lut580idx0));
    flut580.push_back(lut580idx0);
    auto lut580idx1 = [](long I) -> long {
        /* GATE 953 (LUT2 _4089_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut580.push_back(ctx.genrate_lut(lut580idx1));
    flut580.push_back(lut580idx1);
    auto fvec580 = [flut580](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut580[i](I));
        return ret;
    };

    std::cerr << "\rLUT580   ";
    Ciphertext gin580 = 1 * gout482[0] + 2 * gout546[1];
    std::vector<Ciphertext> gout580 = ctx.eval_lut_amortized(&gin580, lut580);

    std::vector<RotationPoly> lut581;
    std::vector<long (*)(long)> flut581;
    auto lut581idx0 = [](long I) -> long {
        /* GATE 596 (LUT2 _3732_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut581.push_back(ctx.genrate_lut(lut581idx0));
    flut581.push_back(lut581idx0);
    auto fvec581 = [flut581](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut581[i](I));
        return ret;
    };

    std::cerr << "\rLUT581   ";
    Ciphertext gin581 = 1 * gout550[0] + 2 * gout517[1];
    std::vector<Ciphertext> gout581 = ctx.eval_lut_amortized(&gin581, lut581);

    std::vector<RotationPoly> lut582;
    std::vector<long (*)(long)> flut582;
    auto lut582idx0 = [](long I) -> long {
        /* GATE 449 (LUT2 _3585_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut582.push_back(ctx.genrate_lut(lut582idx0));
    flut582.push_back(lut582idx0);
    auto fvec582 = [flut582](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut582[i](I));
        return ret;
    };

    std::cerr << "\rLUT582   ";
    Ciphertext gin582 = 1 * gout578[0] + 2 * gout557[1];
    std::vector<Ciphertext> gout582 = ctx.eval_lut_amortized(&gin582, lut582);

    std::vector<RotationPoly> lut583;
    std::vector<long (*)(long)> flut583;
    auto lut583idx0 = [](long I) -> long {
        /* GATE 629 (LUT2 _3765_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut583.push_back(ctx.genrate_lut(lut583idx0));
    flut583.push_back(lut583idx0);
    auto lut583idx1 = [](long I) -> long {
        /* GATE 595 (LUT2 _3731_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut583.push_back(ctx.genrate_lut(lut583idx1));
    flut583.push_back(lut583idx1);
    auto fvec583 = [flut583](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut583[i](I));
        return ret;
    };

    std::cerr << "\rLUT583   ";
    Ciphertext gin583 = 1 * gout581[0] + 2 * gout462[0];
    std::vector<Ciphertext> gout583 = ctx.eval_lut_amortized(&gin583, lut583);

    std::vector<RotationPoly> lut584;
    std::vector<long (*)(long)> flut584;
    auto lut584idx0 = [](long I) -> long {
        /* GATE 91 (LUT2 _3227_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut584.push_back(ctx.genrate_lut(lut584idx0));
    flut584.push_back(lut584idx0);
    auto fvec584 = [flut584](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut584[i](I));
        return ret;
    };

    std::cerr << "\rLUT584   ";
    Ciphertext gin584 = 1 * gout569[0] + 2 * gout566[0];
    std::vector<Ciphertext> gout584 = ctx.eval_lut_amortized(&gin584, lut584);

    std::vector<RotationPoly> lut585;
    std::vector<long (*)(long)> flut585;
    auto lut585idx0 = [](long I) -> long {
        /* GATE 448 (LUT2 _3584_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut585.push_back(ctx.genrate_lut(lut585idx0));
    flut585.push_back(lut585idx0);
    auto fvec585 = [flut585](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut585[i](I));
        return ret;
    };

    std::cerr << "\rLUT585   ";
    Ciphertext gin585 = 1 * gout582[0] + 2 * gout557[0];
    std::vector<Ciphertext> gout585 = ctx.eval_lut_amortized(&gin585, lut585);

    std::vector<RotationPoly> lut586;
    std::vector<long (*)(long)> flut586;
    auto lut586idx0 = [](long I) -> long {
        /* GATE 377 (LUT2 _3513_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut586.push_back(ctx.genrate_lut(lut586idx0));
    flut586.push_back(lut586idx0);
    auto fvec586 = [flut586](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut586[i](I));
        return ret;
    };

    std::cerr << "\rLUT586   ";
    Ciphertext gin586 = 1 * gout574[1] + 2 * gout551[0];
    std::vector<Ciphertext> gout586 = ctx.eval_lut_amortized(&gin586, lut586);

    std::vector<RotationPoly> lut587;
    std::vector<long (*)(long)> flut587;
    auto lut587idx0 = [](long I) -> long {
        /* GATE 665 (LUT2 _3801_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut587.push_back(ctx.genrate_lut(lut587idx0));
    flut587.push_back(lut587idx0);
    auto fvec587 = [flut587](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut587[i](I));
        return ret;
    };

    std::cerr << "\rLUT587   ";
    Ciphertext gin587 = 1 * gout583[0] + 2 * gout487[1];
    std::vector<Ciphertext> gout587 = ctx.eval_lut_amortized(&gin587, lut587);

    std::vector<RotationPoly> lut588;
    std::vector<long (*)(long)> flut588;
    auto lut588idx0 = [](long I) -> long {
        /* GATE 376 (LUT2 _3512_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut588.push_back(ctx.genrate_lut(lut588idx0));
    flut588.push_back(lut588idx0);
    auto fvec588 = [flut588](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut588[i](I));
        return ret;
    };

    std::cerr << "\rLUT588   ";
    Ciphertext gin588 = 1 * gout586[0] + 2 * gout551[1];
    std::vector<Ciphertext> gout588 = ctx.eval_lut_amortized(&gin588, lut588);

    std::vector<RotationPoly> lut589;
    std::vector<long (*)(long)> flut589;
    auto lut589idx0 = [](long I) -> long {
        /* GATE 664 (LUT2 _3800_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut589.push_back(ctx.genrate_lut(lut589idx0));
    flut589.push_back(lut589idx0);
    auto fvec589 = [flut589](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut589[i](I));
        return ret;
    };

    std::cerr << "\rLUT589   ";
    Ciphertext gin589 = 1 * gout587[0] + 2 * gout487[0];
    std::vector<Ciphertext> gout589 = ctx.eval_lut_amortized(&gin589, lut589);

    std::vector<RotationPoly> lut590;
    std::vector<long (*)(long)> flut590;
    auto lut590idx0 = [](long I) -> long {
        /* GATE 90 (LUT2 _3226_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut590.push_back(ctx.genrate_lut(lut590idx0));
    flut590.push_back(lut590idx0);
    auto lut590idx1 = [](long I) -> long {
        /* GATE 127 (LUT2 _3263_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut590.push_back(ctx.genrate_lut(lut590idx1));
    flut590.push_back(lut590idx1);
    auto fvec590 = [flut590](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut590[i](I));
        return ret;
    };

    std::cerr << "\rLUT590   ";
    Ciphertext gin590 = 1 * gout584[0] + 2 * gout579[0];
    std::vector<Ciphertext> gout590 = ctx.eval_lut_amortized(&gin590, lut590);

    std::vector<RotationPoly> lut591;
    std::vector<long (*)(long)> flut591;
    auto lut591idx0 = [](long I) -> long {
        /* GATE 126 (LUT2 _3262_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut591.push_back(ctx.genrate_lut(lut591idx0));
    flut591.push_back(lut591idx0);
    auto fvec591 = [flut591](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut591[i](I));
        return ret;
    };

    std::cerr << "\rLUT591   ";
    Ciphertext gin591 = 1 * gout590[1] + 2 * gout579[1];
    std::vector<Ciphertext> gout591 = ctx.eval_lut_amortized(&gin591, lut591);

    std::vector<RotationPoly> lut592;
    std::vector<long (*)(long)> flut592;
    auto lut592idx0 = [](long I) -> long {
        /* GATE 162 (LUT2 _3298_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut592.push_back(ctx.genrate_lut(lut592idx0));
    flut592.push_back(lut592idx0);
    auto lut592idx1 = [](long I) -> long {
        /* GATE 125 (LUT2 _3261_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut592.push_back(ctx.genrate_lut(lut592idx1));
    flut592.push_back(lut592idx1);
    auto fvec592 = [flut592](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut592[i](I));
        return ret;
    };

    std::cerr << "\rLUT592   ";
    Ciphertext gin592 = 1 * gout591[0] + 2 * gout496[0];
    std::vector<Ciphertext> gout592 = ctx.eval_lut_amortized(&gin592, lut592);

    std::vector<RotationPoly> lut593;
    std::vector<long (*)(long)> flut593;
    auto lut593idx0 = [](long I) -> long {
        /* GATE 161 (LUT2 _3297_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut593.push_back(ctx.genrate_lut(lut593idx0));
    flut593.push_back(lut593idx0);
    auto fvec593 = [flut593](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut593[i](I));
        return ret;
    };

    std::cerr << "\rLUT593   ";
    Ciphertext gin593 = 1 * gout592[0] + 2 * gout496[1];
    std::vector<Ciphertext> gout593 = ctx.eval_lut_amortized(&gin593, lut593);

    std::vector<RotationPoly> lut594;
    std::vector<long (*)(long)> flut594;
    auto lut594idx0 = [](long I) -> long {
        /* GATE 197 (LUT2 _3333_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut594.push_back(ctx.genrate_lut(lut594idx0));
    flut594.push_back(lut594idx0);
    auto lut594idx1 = [](long I) -> long {
        /* GATE 160 (LUT2 _3296_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut594.push_back(ctx.genrate_lut(lut594idx1));
    flut594.push_back(lut594idx1);
    auto fvec594 = [flut594](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut594[i](I));
        return ret;
    };

    std::cerr << "\rLUT594   ";
    Ciphertext gin594 = 1 * gout593[0] + 2 * gout534[0];
    std::vector<Ciphertext> gout594 = ctx.eval_lut_amortized(&gin594, lut594);

    std::vector<RotationPoly> lut595;
    std::vector<long (*)(long)> flut595;
    auto lut595idx0 = [](long I) -> long {
        /* GATE 196 (LUT2 _3332_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut595.push_back(ctx.genrate_lut(lut595idx0));
    flut595.push_back(lut595idx0);
    auto fvec595 = [flut595](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut595[i](I));
        return ret;
    };

    std::cerr << "\rLUT595   ";
    Ciphertext gin595 = 1 * gout594[0] + 2 * gout534[1];
    std::vector<Ciphertext> gout595 = ctx.eval_lut_amortized(&gin595, lut595);

    std::vector<RotationPoly> lut596;
    std::vector<long (*)(long)> flut596;
    auto lut596idx0 = [](long I) -> long {
        /* GATE 195 (LUT2 _3331_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut596.push_back(ctx.genrate_lut(lut596idx0));
    flut596.push_back(lut596idx0);
    auto fvec596 = [flut596](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut596[i](I));
        return ret;
    };

    std::cerr << "\rLUT596   ";
    Ciphertext gin596 = 1 * gout595[0] + 2 * gout553[1];
    std::vector<Ciphertext> gout596 = ctx.eval_lut_amortized(&gin596, lut596);

    std::vector<RotationPoly> lut597;
    std::vector<long (*)(long)> flut597;
    auto lut597idx0 = [](long I) -> long {
        /* GATE 232 (LUT2 _3368_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut597.push_back(ctx.genrate_lut(lut597idx0));
    flut597.push_back(lut597idx0);
    auto fvec597 = [flut597](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut597[i](I));
        return ret;
    };

    std::cerr << "\rLUT597   ";
    Ciphertext gin597 = 1 * gout553[0] + 2 * gout595[0];
    std::vector<Ciphertext> gout597 = ctx.eval_lut_amortized(&gin597, lut597);

    std::vector<RotationPoly> lut598;
    std::vector<long (*)(long)> flut598;
    auto lut598idx0 = [](long I) -> long {
        /* GATE 231 (LUT2 _3367_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut598.push_back(ctx.genrate_lut(lut598idx0));
    flut598.push_back(lut598idx0);
    auto fvec598 = [flut598](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut598[i](I));
        return ret;
    };

    std::cerr << "\rLUT598   ";
    Ciphertext gin598 = 1 * gout597[0] + 2 * gout553[2];
    std::vector<Ciphertext> gout598 = ctx.eval_lut_amortized(&gin598, lut598);

    std::vector<RotationPoly> lut599;
    std::vector<long (*)(long)> flut599;
    auto lut599idx0 = [](long I) -> long {
        /* GATE 268 (LUT2 _3404_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut599.push_back(ctx.genrate_lut(lut599idx0));
    flut599.push_back(lut599idx0);
    auto lut599idx1 = [](long I) -> long {
        /* GATE 230 (LUT2 _3366_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut599.push_back(ctx.genrate_lut(lut599idx1));
    flut599.push_back(lut599idx1);
    auto fvec599 = [flut599](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut599[i](I));
        return ret;
    };

    std::cerr << "\rLUT599   ";
    Ciphertext gin599 = 1 * gout598[0] + 2 * gout542[0];
    std::vector<Ciphertext> gout599 = ctx.eval_lut_amortized(&gin599, lut599);

    std::vector<RotationPoly> lut600;
    std::vector<long (*)(long)> flut600;
    auto lut600idx0 = [](long I) -> long {
        /* GATE 303 (LUT2 _3439_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut600.push_back(ctx.genrate_lut(lut600idx0));
    flut600.push_back(lut600idx0);
    auto fvec600 = [flut600](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut600[i](I));
        return ret;
    };

    std::cerr << "\rLUT600   ";
    Ciphertext gin600 = 1 * gout599[0] + 2 * gout548[0];
    std::vector<Ciphertext> gout600 = ctx.eval_lut_amortized(&gin600, lut600);

    std::vector<RotationPoly> lut601;
    std::vector<long (*)(long)> flut601;
    auto lut601idx0 = [](long I) -> long {
        /* GATE 302 (LUT2 _3438_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut601.push_back(ctx.genrate_lut(lut601idx0));
    flut601.push_back(lut601idx0);
    auto fvec601 = [flut601](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut601[i](I));
        return ret;
    };

    std::cerr << "\rLUT601   ";
    Ciphertext gin601 = 1 * gout600[0] + 2 * gout561[0];
    std::vector<Ciphertext> gout601 = ctx.eval_lut_amortized(&gin601, lut601);

    std::vector<RotationPoly> lut602;
    std::vector<long (*)(long)> flut602;
    auto lut602idx0 = [](long I) -> long {
        /* GATE 301 (LUT2 _3437_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut602.push_back(ctx.genrate_lut(lut602idx0));
    flut602.push_back(lut602idx0);
    auto lut602idx1 = [](long I) -> long {
        /* GATE 340 (LUT2 _3476_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut602.push_back(ctx.genrate_lut(lut602idx1));
    flut602.push_back(lut602idx1);
    auto fvec602 = [flut602](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut602[i](I));
        return ret;
    };

    std::cerr << "\rLUT602   ";
    Ciphertext gin602 = 1 * gout601[0] + 2 * gout574[0];
    std::vector<Ciphertext> gout602 = ctx.eval_lut_amortized(&gin602, lut602);

    std::vector<RotationPoly> lut603;
    std::vector<long (*)(long)> flut603;
    auto lut603idx0 = [](long I) -> long {
        /* GATE 339 (LUT2 _3475_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut603.push_back(ctx.genrate_lut(lut603idx0));
    flut603.push_back(lut603idx0);
    auto fvec603 = [flut603](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut603[i](I));
        return ret;
    };

    std::cerr << "\rLUT603   ";
    Ciphertext gin603 = 1 * gout602[1] + 2 * gout574[1];
    std::vector<Ciphertext> gout603 = ctx.eval_lut_amortized(&gin603, lut603);

    std::vector<RotationPoly> lut604;
    std::vector<long (*)(long)> flut604;
    auto lut604idx0 = [](long I) -> long {
        /* GATE 267 (LUT2 _3403_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut604.push_back(ctx.genrate_lut(lut604idx0));
    flut604.push_back(lut604idx0);
    auto fvec604 = [flut604](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut604[i](I));
        return ret;
    };

    std::cerr << "\rLUT604   ";
    Ciphertext gin604 = 1 * gout599[0] + 2 * gout542[1];
    std::vector<Ciphertext> gout604 = ctx.eval_lut_amortized(&gin604, lut604);

    std::vector<RotationPoly> lut605;
    std::vector<long (*)(long)> flut605;
    auto lut605idx0 = [](long I) -> long {
        /* GATE 338 (LUT2 _3474_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut605.push_back(ctx.genrate_lut(lut605idx0));
    flut605.push_back(lut605idx0);
    auto fvec605 = [flut605](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut605[i](I));
        return ret;
    };

    std::cerr << "\rLUT605   ";
    Ciphertext gin605 = 1 * gout603[0] + 2 * gout551[0];
    std::vector<Ciphertext> gout605 = ctx.eval_lut_amortized(&gin605, lut605);

    std::vector<RotationPoly> lut606;
    std::vector<long (*)(long)> flut606;
    auto lut606idx0 = [](long I) -> long {
        /* GATE 375 (LUT2 _3511_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut606.push_back(ctx.genrate_lut(lut606idx0));
    flut606.push_back(lut606idx0);
    auto fvec606 = [flut606](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut606[i](I));
        return ret;
    };

    std::cerr << "\rLUT606   ";
    Ciphertext gin606 = 1 * gout602[1] + 2 * gout551[0];
    std::vector<Ciphertext> gout606 = ctx.eval_lut_amortized(&gin606, lut606);

    std::vector<RotationPoly> lut607;
    std::vector<long (*)(long)> flut607;
    auto lut607idx0 = [](long I) -> long {
        /* GATE 374 (LUT2 _3510_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut607.push_back(ctx.genrate_lut(lut607idx0));
    flut607.push_back(lut607idx0);
    auto fvec607 = [flut607](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut607[i](I));
        return ret;
    };

    std::cerr << "\rLUT607   ";
    Ciphertext gin607 = 1 * gout606[0] + 2 * gout588[0];
    std::vector<Ciphertext> gout607 = ctx.eval_lut_amortized(&gin607, lut607);

    std::vector<RotationPoly> lut608;
    std::vector<long (*)(long)> flut608;
    auto lut608idx0 = [](long I) -> long {
        /* GATE 412 (LUT2 _3548_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut608.push_back(ctx.genrate_lut(lut608idx0));
    flut608.push_back(lut608idx0);
    auto lut608idx1 = [](long I) -> long {
        /* GATE 373 (LUT2 _3509_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut608.push_back(ctx.genrate_lut(lut608idx1));
    flut608.push_back(lut608idx1);
    auto fvec608 = [flut608](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut608[i](I));
        return ret;
    };

    std::cerr << "\rLUT608   ";
    Ciphertext gin608 = 1 * gout607[0] + 2 * gout578[1];
    std::vector<Ciphertext> gout608 = ctx.eval_lut_amortized(&gin608, lut608);

    std::vector<RotationPoly> lut609;
    std::vector<long (*)(long)> flut609;
    auto lut609idx0 = [](long I) -> long {
        /* GATE 447 (LUT2 _3583_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut609.push_back(ctx.genrate_lut(lut609idx0));
    flut609.push_back(lut609idx0);
    auto fvec609 = [flut609](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut609[i](I));
        return ret;
    };

    std::cerr << "\rLUT609   ";
    Ciphertext gin609 = 1 * gout608[0] + 2 * gout557[1];
    std::vector<Ciphertext> gout609 = ctx.eval_lut_amortized(&gin609, lut609);

    std::vector<RotationPoly> lut610;
    std::vector<long (*)(long)> flut610;
    auto lut610idx0 = [](long I) -> long {
        /* GATE 266 (LUT2 _3402_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut610.push_back(ctx.genrate_lut(lut610idx0));
    flut610.push_back(lut610idx0);
    auto fvec610 = [flut610](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut610[i](I));
        return ret;
    };

    std::cerr << "\rLUT610   ";
    Ciphertext gin610 = 1 * gout604[0] + 2 * gout548[0];
    std::vector<Ciphertext> gout610 = ctx.eval_lut_amortized(&gin610, lut610);

    std::vector<RotationPoly> lut611;
    std::vector<long (*)(long)> flut611;
    auto lut611idx0 = [](long I) -> long {
        /* GATE 411 (LUT2 _3547_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut611.push_back(ctx.genrate_lut(lut611idx0));
    flut611.push_back(lut611idx0);
    auto fvec611 = [flut611](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut611[i](I));
        return ret;
    };

    std::cerr << "\rLUT611   ";
    Ciphertext gin611 = 1 * gout608[0] + 2 * gout578[0];
    std::vector<Ciphertext> gout611 = ctx.eval_lut_amortized(&gin611, lut611);

    std::vector<RotationPoly> lut612;
    std::vector<long (*)(long)> flut612;
    auto lut612idx0 = [](long I) -> long {
        /* GATE 446 (LUT2 _3582_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut612.push_back(ctx.genrate_lut(lut612idx0));
    flut612.push_back(lut612idx0);
    auto fvec612 = [flut612](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut612[i](I));
        return ret;
    };

    std::cerr << "\rLUT612   ";
    Ciphertext gin612 = 1 * gout609[0] + 2 * gout585[0];
    std::vector<Ciphertext> gout612 = ctx.eval_lut_amortized(&gin612, lut612);

    std::vector<RotationPoly> lut613;
    std::vector<long (*)(long)> flut613;
    auto lut613idx0 = [](long I) -> long {
        /* GATE 410 (LUT2 _3546_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut613.push_back(ctx.genrate_lut(lut613idx0));
    flut613.push_back(lut613idx0);
    auto fvec613 = [flut613](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut613[i](I));
        return ret;
    };

    std::cerr << "\rLUT613   ";
    Ciphertext gin613 = 1 * gout611[0] + 2 * gout557[1];
    std::vector<Ciphertext> gout613 = ctx.eval_lut_amortized(&gin613, lut613);

    std::vector<RotationPoly> lut614;
    std::vector<long (*)(long)> flut614;
    auto lut614idx0 = [](long I) -> long {
        /* GATE 445 (LUT2 _3581_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut614.push_back(ctx.genrate_lut(lut614idx0));
    flut614.push_back(lut614idx0);
    auto lut614idx1 = [](long I) -> long {
        /* GATE 484 (LUT2 _3620_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut614.push_back(ctx.genrate_lut(lut614idx1));
    flut614.push_back(lut614idx1);
    auto fvec614 = [flut614](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut614[i](I));
        return ret;
    };

    std::cerr << "\rLUT614   ";
    Ciphertext gin614 = 1 * gout612[0] + 2 * gout532[1];
    std::vector<Ciphertext> gout614 = ctx.eval_lut_amortized(&gin614, lut614);

    std::vector<RotationPoly> lut615;
    std::vector<long (*)(long)> flut615;
    auto lut615idx0 = [](long I) -> long {
        /* GATE 519 (LUT2 _3655_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut615.push_back(ctx.genrate_lut(lut615idx0));
    flut615.push_back(lut615idx0);
    auto fvec615 = [flut615](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut615[i](I));
        return ret;
    };

    std::cerr << "\rLUT615   ";
    Ciphertext gin615 = 1 * gout614[1] + 2 * gout562[0];
    std::vector<Ciphertext> gout615 = ctx.eval_lut_amortized(&gin615, lut615);

    std::vector<RotationPoly> lut616;
    std::vector<long (*)(long)> flut616;
    auto lut616idx0 = [](long I) -> long {
        /* GATE 483 (LUT2 _3619_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut616.push_back(ctx.genrate_lut(lut616idx0));
    flut616.push_back(lut616idx0);
    auto fvec616 = [flut616](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut616[i](I));
        return ret;
    };

    std::cerr << "\rLUT616   ";
    Ciphertext gin616 = 1 * gout614[1] + 2 * gout532[0];
    std::vector<Ciphertext> gout616 = ctx.eval_lut_amortized(&gin616, lut616);

    std::vector<RotationPoly> lut617;
    std::vector<long (*)(long)> flut617;
    auto lut617idx0 = [](long I) -> long {
        /* GATE 518 (LUT2 _3654_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut617.push_back(ctx.genrate_lut(lut617idx0));
    flut617.push_back(lut617idx0);
    auto fvec617 = [flut617](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut617[i](I));
        return ret;
    };

    std::cerr << "\rLUT617   ";
    Ciphertext gin617 = 1 * gout615[0] + 2 * gout576[0];
    std::vector<Ciphertext> gout617 = ctx.eval_lut_amortized(&gin617, lut617);

    std::vector<RotationPoly> lut618;
    std::vector<long (*)(long)> flut618;
    auto lut618idx0 = [](long I) -> long {
        /* GATE 482 (LUT2 _3618_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut618.push_back(ctx.genrate_lut(lut618idx0));
    flut618.push_back(lut618idx0);
    auto fvec618 = [flut618](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut618[i](I));
        return ret;
    };

    std::cerr << "\rLUT618   ";
    Ciphertext gin618 = 1 * gout616[0] + 2 * gout562[0];
    std::vector<Ciphertext> gout618 = ctx.eval_lut_amortized(&gin618, lut618);

    std::vector<RotationPoly> lut619;
    std::vector<long (*)(long)> flut619;
    auto lut619idx0 = [](long I) -> long {
        /* GATE 517 (LUT2 _3653_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut619.push_back(ctx.genrate_lut(lut619idx0));
    flut619.push_back(lut619idx0);
    auto lut619idx1 = [](long I) -> long {
        /* GATE 556 (LUT2 _3692_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut619.push_back(ctx.genrate_lut(lut619idx1));
    flut619.push_back(lut619idx1);
    auto fvec619 = [flut619](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut619[i](I));
        return ret;
    };

    std::cerr << "\rLUT619   ";
    Ciphertext gin619 = 1 * gout617[0] + 2 * gout527[1];
    std::vector<Ciphertext> gout619 = ctx.eval_lut_amortized(&gin619, lut619);

    std::vector<RotationPoly> lut620;
    std::vector<long (*)(long)> flut620;
    auto lut620idx0 = [](long I) -> long {
        /* GATE 591 (LUT2 _3727_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut620.push_back(ctx.genrate_lut(lut620idx0));
    flut620.push_back(lut620idx0);
    auto fvec620 = [flut620](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut620[i](I));
        return ret;
    };

    std::cerr << "\rLUT620   ";
    Ciphertext gin620 = 1 * gout619[1] + 2 * gout552[1];
    std::vector<Ciphertext> gout620 = ctx.eval_lut_amortized(&gin620, lut620);

    std::vector<RotationPoly> lut621;
    std::vector<long (*)(long)> flut621;
    auto lut621idx0 = [](long I) -> long {
        /* GATE 555 (LUT2 _3691_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut621.push_back(ctx.genrate_lut(lut621idx0));
    flut621.push_back(lut621idx0);
    auto fvec621 = [flut621](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut621[i](I));
        return ret;
    };

    std::cerr << "\rLUT621   ";
    Ciphertext gin621 = 1 * gout619[1] + 2 * gout527[0];
    std::vector<Ciphertext> gout621 = ctx.eval_lut_amortized(&gin621, lut621);

    std::vector<RotationPoly> lut622;
    std::vector<long (*)(long)> flut622;
    auto lut622idx0 = [](long I) -> long {
        /* GATE 590 (LUT2 _3726_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut622.push_back(ctx.genrate_lut(lut622idx0));
    flut622.push_back(lut622idx0);
    auto fvec622 = [flut622](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut622[i](I));
        return ret;
    };

    std::cerr << "\rLUT622   ";
    Ciphertext gin622 = 1 * gout620[0] + 2 * gout577[0];
    std::vector<Ciphertext> gout622 = ctx.eval_lut_amortized(&gin622, lut622);

    std::vector<RotationPoly> lut623;
    std::vector<long (*)(long)> flut623;
    auto lut623idx0 = [](long I) -> long {
        /* GATE 589 (LUT2 _3725_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut623.push_back(ctx.genrate_lut(lut623idx0));
    flut623.push_back(lut623idx0);
    auto lut623idx1 = [](long I) -> long {
        /* GATE 628 (LUT2 _3764_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut623.push_back(ctx.genrate_lut(lut623idx1));
    flut623.push_back(lut623idx1);
    auto fvec623 = [flut623](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut623[i](I));
        return ret;
    };

    std::cerr << "\rLUT623   ";
    Ciphertext gin623 = 1 * gout622[0] + 2 * gout583[1];
    std::vector<Ciphertext> gout623 = ctx.eval_lut_amortized(&gin623, lut623);

    std::vector<RotationPoly> lut624;
    std::vector<long (*)(long)> flut624;
    auto lut624idx0 = [](long I) -> long {
        /* GATE 663 (LUT2 _3799_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut624.push_back(ctx.genrate_lut(lut624idx0));
    flut624.push_back(lut624idx0);
    auto fvec624 = [flut624](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut624[i](I));
        return ret;
    };

    std::cerr << "\rLUT624   ";
    Ciphertext gin624 = 1 * gout623[1] + 2 * gout487[1];
    std::vector<Ciphertext> gout624 = ctx.eval_lut_amortized(&gin624, lut624);

    std::vector<RotationPoly> lut625;
    std::vector<long (*)(long)> flut625;
    auto lut625idx0 = [](long I) -> long {
        /* GATE 554 (LUT2 _3690_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut625.push_back(ctx.genrate_lut(lut625idx0));
    flut625.push_back(lut625idx0);
    auto fvec625 = [flut625](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut625[i](I));
        return ret;
    };

    std::cerr << "\rLUT625   ";
    Ciphertext gin625 = 1 * gout621[0] + 2 * gout552[1];
    std::vector<Ciphertext> gout625 = ctx.eval_lut_amortized(&gin625, lut625);

    std::vector<RotationPoly> lut626;
    std::vector<long (*)(long)> flut626;
    auto lut626idx0 = [](long I) -> long {
        /* GATE 627 (LUT2 _3763_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut626.push_back(ctx.genrate_lut(lut626idx0));
    flut626.push_back(lut626idx0);
    auto fvec626 = [flut626](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut626[i](I));
        return ret;
    };

    std::cerr << "\rLUT626   ";
    Ciphertext gin626 = 1 * gout623[1] + 2 * gout583[0];
    std::vector<Ciphertext> gout626 = ctx.eval_lut_amortized(&gin626, lut626);

    std::vector<RotationPoly> lut627;
    std::vector<long (*)(long)> flut627;
    auto lut627idx0 = [](long I) -> long {
        /* GATE 662 (LUT2 _3798_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut627.push_back(ctx.genrate_lut(lut627idx0));
    flut627.push_back(lut627idx0);
    auto fvec627 = [flut627](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut627[i](I));
        return ret;
    };

    std::cerr << "\rLUT627   ";
    Ciphertext gin627 = 1 * gout624[0] + 2 * gout589[0];
    std::vector<Ciphertext> gout627 = ctx.eval_lut_amortized(&gin627, lut627);

    std::vector<RotationPoly> lut628;
    std::vector<long (*)(long)> flut628;
    auto lut628idx0 = [](long I) -> long {
        /* GATE 626 (LUT2 _3762_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut628.push_back(ctx.genrate_lut(lut628idx0));
    flut628.push_back(lut628idx0);
    auto fvec628 = [flut628](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut628[i](I));
        return ret;
    };

    std::cerr << "\rLUT628   ";
    Ciphertext gin628 = 1 * gout626[0] + 2 * gout487[1];
    std::vector<Ciphertext> gout628 = ctx.eval_lut_amortized(&gin628, lut628);

    std::vector<RotationPoly> lut629;
    std::vector<long (*)(long)> flut629;
    auto lut629idx0 = [](long I) -> long {
        /* GATE 661 (LUT2 _3797_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut629.push_back(ctx.genrate_lut(lut629idx0));
    flut629.push_back(lut629idx0);
    auto lut629idx1 = [](long I) -> long {
        /* GATE 700 (LUT2 _3836_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut629.push_back(ctx.genrate_lut(lut629idx1));
    flut629.push_back(lut629idx1);
    auto fvec629 = [flut629](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut629[i](I));
        return ret;
    };

    std::cerr << "\rLUT629   ";
    Ciphertext gin629 = 1 * gout627[0] + 2 * gout518[1];
    std::vector<Ciphertext> gout629 = ctx.eval_lut_amortized(&gin629, lut629);

    std::vector<RotationPoly> lut630;
    std::vector<long (*)(long)> flut630;
    auto lut630idx0 = [](long I) -> long {
        /* GATE 699 (LUT2 _3835_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut630.push_back(ctx.genrate_lut(lut630idx0));
    flut630.push_back(lut630idx0);
    auto fvec630 = [flut630](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut630[i](I));
        return ret;
    };

    std::cerr << "\rLUT630   ";
    Ciphertext gin630 = 1 * gout629[1] + 2 * gout518[0];
    std::vector<Ciphertext> gout630 = ctx.eval_lut_amortized(&gin630, lut630);

    std::vector<RotationPoly> lut631;
    std::vector<long (*)(long)> flut631;
    auto lut631idx0 = [](long I) -> long {
        /* GATE 735 (LUT2 _3871_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut631.push_back(ctx.genrate_lut(lut631idx0));
    flut631.push_back(lut631idx0);
    auto fvec631 = [flut631](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut631[i](I));
        return ret;
    };

    std::cerr << "\rLUT631   ";
    Ciphertext gin631 = 1 * gout629[1] + 2 * gout549[0];
    std::vector<Ciphertext> gout631 = ctx.eval_lut_amortized(&gin631, lut631);

    std::vector<RotationPoly> lut632;
    std::vector<long (*)(long)> flut632;
    auto lut632idx0 = [](long I) -> long {
        /* GATE 698 (LUT2 _3834_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut632.push_back(ctx.genrate_lut(lut632idx0));
    flut632.push_back(lut632idx0);
    auto fvec632 = [flut632](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut632[i](I));
        return ret;
    };

    std::cerr << "\rLUT632   ";
    Ciphertext gin632 = 1 * gout630[0] + 2 * gout549[0];
    std::vector<Ciphertext> gout632 = ctx.eval_lut_amortized(&gin632, lut632);

    std::vector<RotationPoly> lut633;
    std::vector<long (*)(long)> flut633;
    auto lut633idx0 = [](long I) -> long {
        /* GATE 734 (LUT2 _3870_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut633.push_back(ctx.genrate_lut(lut633idx0));
    flut633.push_back(lut633idx0);
    auto fvec633 = [flut633](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut633[i](I));
        return ret;
    };

    std::cerr << "\rLUT633   ";
    Ciphertext gin633 = 1 * gout631[0] + 2 * gout573[0];
    std::vector<Ciphertext> gout633 = ctx.eval_lut_amortized(&gin633, lut633);

    std::vector<RotationPoly> lut634;
    std::vector<long (*)(long)> flut634;
    auto lut634idx0 = [](long I) -> long {
        /* GATE 733 (LUT2 _3869_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut634.push_back(ctx.genrate_lut(lut634idx0));
    flut634.push_back(lut634idx0);
    auto lut634idx1 = [](long I) -> long {
        /* GATE 772 (LUT2 _3908_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut634.push_back(ctx.genrate_lut(lut634idx1));
    flut634.push_back(lut634idx1);
    auto fvec634 = [flut634](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut634[i](I));
        return ret;
    };

    std::cerr << "\rLUT634   ";
    Ciphertext gin634 = 1 * gout633[0] + 2 * gout556[0];
    std::vector<Ciphertext> gout634 = ctx.eval_lut_amortized(&gin634, lut634);

    std::vector<RotationPoly> lut635;
    std::vector<long (*)(long)> flut635;
    auto lut635idx0 = [](long I) -> long {
        /* GATE 807 (LUT2 _3943_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut635.push_back(ctx.genrate_lut(lut635idx0));
    flut635.push_back(lut635idx0);
    auto fvec635 = [flut635](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut635[i](I));
        return ret;
    };

    std::cerr << "\rLUT635   ";
    Ciphertext gin635 = 1 * gout634[1] + 2 * gout547[0];
    std::vector<Ciphertext> gout635 = ctx.eval_lut_amortized(&gin635, lut635);

    std::vector<RotationPoly> lut636;
    std::vector<long (*)(long)> flut636;
    auto lut636idx0 = [](long I) -> long {
        /* GATE 771 (LUT2 _3907_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut636.push_back(ctx.genrate_lut(lut636idx0));
    flut636.push_back(lut636idx0);
    auto fvec636 = [flut636](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut636[i](I));
        return ret;
    };

    std::cerr << "\rLUT636   ";
    Ciphertext gin636 = 1 * gout634[1] + 2 * gout556[1];
    std::vector<Ciphertext> gout636 = ctx.eval_lut_amortized(&gin636, lut636);

    std::vector<RotationPoly> lut637;
    std::vector<long (*)(long)> flut637;
    auto lut637idx0 = [](long I) -> long {
        /* GATE 806 (LUT2 _3942_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut637.push_back(ctx.genrate_lut(lut637idx0));
    flut637.push_back(lut637idx0);
    auto fvec637 = [flut637](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut637[i](I));
        return ret;
    };

    std::cerr << "\rLUT637   ";
    Ciphertext gin637 = 1 * gout635[0] + 2 * gout568[0];
    std::vector<Ciphertext> gout637 = ctx.eval_lut_amortized(&gin637, lut637);

    std::vector<RotationPoly> lut638;
    std::vector<long (*)(long)> flut638;
    auto lut638idx0 = [](long I) -> long {
        /* GATE 770 (LUT2 _3906_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut638.push_back(ctx.genrate_lut(lut638idx0));
    flut638.push_back(lut638idx0);
    auto fvec638 = [flut638](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut638[i](I));
        return ret;
    };

    std::cerr << "\rLUT638   ";
    Ciphertext gin638 = 1 * gout636[0] + 2 * gout547[0];
    std::vector<Ciphertext> gout638 = ctx.eval_lut_amortized(&gin638, lut638);

    std::vector<RotationPoly> lut639;
    std::vector<long (*)(long)> flut639;
    auto lut639idx0 = [](long I) -> long {
        /* GATE 805 (LUT2 _3941_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut639.push_back(ctx.genrate_lut(lut639idx0));
    flut639.push_back(lut639idx0);
    auto lut639idx1 = [](long I) -> long {
        /* GATE 844 (LUT2 _3980_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut639.push_back(ctx.genrate_lut(lut639idx1));
    flut639.push_back(lut639idx1);
    auto fvec639 = [flut639](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut639[i](I));
        return ret;
    };

    std::cerr << "\rLUT639   ";
    Ciphertext gin639 = 1 * gout637[0] + 2 * gout519[1];
    std::vector<Ciphertext> gout639 = ctx.eval_lut_amortized(&gin639, lut639);

    std::vector<RotationPoly> lut640;
    std::vector<long (*)(long)> flut640;
    auto lut640idx0 = [](long I) -> long {
        /* GATE 843 (LUT2 _3979_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut640.push_back(ctx.genrate_lut(lut640idx0));
    flut640.push_back(lut640idx0);
    auto fvec640 = [flut640](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut640[i](I));
        return ret;
    };

    std::cerr << "\rLUT640   ";
    Ciphertext gin640 = 1 * gout639[1] + 2 * gout519[0];
    std::vector<Ciphertext> gout640 = ctx.eval_lut_amortized(&gin640, lut640);

    std::vector<RotationPoly> lut641;
    std::vector<long (*)(long)> flut641;
    auto lut641idx0 = [](long I) -> long {
        /* GATE 842 (LUT2 _3978_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut641.push_back(ctx.genrate_lut(lut641idx0));
    flut641.push_back(lut641idx0);
    auto fvec641 = [flut641](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut641[i](I));
        return ret;
    };

    std::cerr << "\rLUT641   ";
    Ciphertext gin641 = 1 * gout640[0] + 2 * gout572[1];
    std::vector<Ciphertext> gout641 = ctx.eval_lut_amortized(&gin641, lut641);

    std::vector<RotationPoly> lut642;
    std::vector<long (*)(long)> flut642;
    auto lut642idx0 = [](long I) -> long {
        /* GATE 879 (LUT2 _4015_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut642.push_back(ctx.genrate_lut(lut642idx0));
    flut642.push_back(lut642idx0);
    auto fvec642 = [flut642](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut642[i](I));
        return ret;
    };

    std::cerr << "\rLUT642   ";
    Ciphertext gin642 = 1 * gout572[2] + 2 * gout640[0];
    std::vector<Ciphertext> gout642 = ctx.eval_lut_amortized(&gin642, lut642);

    std::vector<RotationPoly> lut643;
    std::vector<long (*)(long)> flut643;
    auto lut643idx0 = [](long I) -> long {
        /* GATE 878 (LUT2 _4014_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut643.push_back(ctx.genrate_lut(lut643idx0));
    flut643.push_back(lut643idx0);
    auto fvec643 = [flut643](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut643[i](I));
        return ret;
    };

    std::cerr << "\rLUT643   ";
    Ciphertext gin643 = 1 * gout642[0] + 2 * gout572[0];
    std::vector<Ciphertext> gout643 = ctx.eval_lut_amortized(&gin643, lut643);

    std::vector<RotationPoly> lut644;
    std::vector<long (*)(long)> flut644;
    auto lut644idx0 = [](long I) -> long {
        /* GATE 915 (LUT2 _4051_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut644.push_back(ctx.genrate_lut(lut644idx0));
    flut644.push_back(lut644idx0);
    auto lut644idx1 = [](long I) -> long {
        /* GATE 877 (LUT2 _4013_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut644.push_back(ctx.genrate_lut(lut644idx1));
    flut644.push_back(lut644idx1);
    auto fvec644 = [flut644](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut644[i](I));
        return ret;
    };

    std::cerr << "\rLUT644   ";
    Ciphertext gin644 = 1 * gout643[0] + 2 * gout545[0];
    std::vector<Ciphertext> gout644 = ctx.eval_lut_amortized(&gin644, lut644);

    std::vector<RotationPoly> lut645;
    std::vector<long (*)(long)> flut645;
    auto lut645idx0 = [](long I) -> long {
        /* GATE 914 (LUT2 _4050_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut645.push_back(ctx.genrate_lut(lut645idx0));
    flut645.push_back(lut645idx0);
    auto fvec645 = [flut645](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut645[i](I));
        return ret;
    };

    std::cerr << "\rLUT645   ";
    Ciphertext gin645 = 1 * gout644[0] + 2 * gout545[1];
    std::vector<Ciphertext> gout645 = ctx.eval_lut_amortized(&gin645, lut645);

    std::vector<RotationPoly> lut646;
    std::vector<long (*)(long)> flut646;
    auto lut646idx0 = [](long I) -> long {
        /* GATE 913 (LUT2 _4049_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut646.push_back(ctx.genrate_lut(lut646idx0));
    flut646.push_back(lut646idx0);
    auto fvec646 = [flut646](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut646[i](I));
        return ret;
    };

    std::cerr << "\rLUT646   ";
    Ciphertext gin646 = 1 * gout645[0] + 2 * gout554[1];
    std::vector<Ciphertext> gout646 = ctx.eval_lut_amortized(&gin646, lut646);

    std::vector<RotationPoly> lut647;
    std::vector<long (*)(long)> flut647;
    auto lut647idx0 = [](long I) -> long {
        /* GATE 950 (LUT2 _4086_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut647.push_back(ctx.genrate_lut(lut647idx0));
    flut647.push_back(lut647idx0);
    auto fvec647 = [flut647](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut647[i](I));
        return ret;
    };

    std::cerr << "\rLUT647   ";
    Ciphertext gin647 = 1 * gout554[2] + 2 * gout645[0];
    std::vector<Ciphertext> gout647 = ctx.eval_lut_amortized(&gin647, lut647);

    std::vector<RotationPoly> lut648;
    std::vector<long (*)(long)> flut648;
    auto lut648idx0 = [](long I) -> long {
        /* GATE 949 (LUT2 _4085_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut648.push_back(ctx.genrate_lut(lut648idx0));
    flut648.push_back(lut648idx0);
    auto fvec648 = [flut648](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut648[i](I));
        return ret;
    };

    std::cerr << "\rLUT648   ";
    Ciphertext gin648 = 1 * gout647[0] + 2 * gout554[0];
    std::vector<Ciphertext> gout648 = ctx.eval_lut_amortized(&gin648, lut648);

    std::vector<RotationPoly> lut649;
    std::vector<long (*)(long)> flut649;
    auto lut649idx0 = [](long I) -> long {
        /* GATE 948 (LUT2 _4084_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut649.push_back(ctx.genrate_lut(lut649idx0));
    flut649.push_back(lut649idx0);
    auto lut649idx1 = [](long I) -> long {
        /* GATE 986 (LUT2 _4122_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut649.push_back(ctx.genrate_lut(lut649idx1));
    flut649.push_back(lut649idx1);
    auto fvec649 = [flut649](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut649[i](I));
        return ret;
    };

    std::cerr << "\rLUT649   ";
    Ciphertext gin649 = 1 * gout648[0] + 2 * gout580[1];
    std::vector<Ciphertext> gout649 = ctx.eval_lut_amortized(&gin649, lut649);

    std::vector<RotationPoly> lut650;
    std::vector<long (*)(long)> flut650;
    auto lut650idx0 = [](long I) -> long {
        /* GATE 985 (LUT2 _4121_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut650.push_back(ctx.genrate_lut(lut650idx0));
    flut650.push_back(lut650idx0);
    auto fvec650 = [flut650](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut650[i](I));
        return ret;
    };

    std::cerr << "\rLUT650   ";
    Ciphertext gin650 = 1 * gout649[1] + 2 * gout580[0];
    std::vector<Ciphertext> gout650 = ctx.eval_lut_amortized(&gin650, lut650);

    std::vector<RotationPoly> lut651;
    std::vector<long (*)(long)> flut651;
    auto lut651idx0 = [](long I) -> long {
        /* GATE 984 (LUT2 _4120_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut651.push_back(ctx.genrate_lut(lut651idx0));
    flut651.push_back(lut651idx0);
    auto lut651idx1 = [](long I) -> long {
        /* GATE 1021 (LUT2 _4157_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut651.push_back(ctx.genrate_lut(lut651idx1));
    flut651.push_back(lut651idx1);
    auto fvec651 = [flut651](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut651[i](I));
        return ret;
    };

    std::cerr << "\rLUT651   ";
    Ciphertext gin651 = 1 * gout650[0] + 2 * gout567[1];
    std::vector<Ciphertext> gout651 = ctx.eval_lut_amortized(&gin651, lut651);

    std::vector<RotationPoly> lut652;
    std::vector<long (*)(long)> flut652;
    auto lut652idx0 = [](long I) -> long {
        /* GATE 1020 (LUT2 _4156_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            default: assert(0);
        };
    };
    lut652.push_back(ctx.genrate_lut(lut652idx0));
    flut652.push_back(lut652idx0);
    auto fvec652 = [flut652](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut652[i](I));
        return ret;
    };

    std::cerr << "\rLUT652   ";
    Ciphertext gin652 = 1 * gout651[1] + 2 * gout567[0];
    std::vector<Ciphertext> gout652 = ctx.eval_lut_amortized(&gin652, lut652);

    std::vector<RotationPoly> lut653;
    std::vector<long (*)(long)> flut653;
    auto lut653idx0 = [](long I) -> long {
        /* GATE 1019 (LUT2 _4155_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    };
    lut653.push_back(ctx.genrate_lut(lut653idx0));
    flut653.push_back(lut653idx0);
    auto fvec653 = [flut653](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut653[i](I));
        return ret;
    };

    std::cerr << "\rLUT653   ";
    Ciphertext gin653 = 1 * gout652[0] + 2 * gout526[0];
    std::vector<Ciphertext> gout653 = ctx.eval_lut_amortized(&gin653, lut653);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(ctx.decrypt(&gout332[1])); /* out1 */
    test_out.push_back(ctx.decrypt(&gout470[0])); /* out2 */
    test_out.push_back(ctx.decrypt(&gout544[0])); /* out3 */
    test_out.push_back(ctx.decrypt(&gout569[1])); /* out4 */
    test_out.push_back(ctx.decrypt(&gout590[0])); /* out5 */
    test_out.push_back(ctx.decrypt(&gout592[1])); /* out6 */
    test_out.push_back(ctx.decrypt(&gout594[1])); /* out7 */
    test_out.push_back(ctx.decrypt(&gout596[0])); /* out8 */
    test_out.push_back(ctx.decrypt(&gout599[1])); /* out9 */
    test_out.push_back(ctx.decrypt(&gout610[0])); /* out10 */
    test_out.push_back(ctx.decrypt(&gout602[0])); /* out11 */
    test_out.push_back(ctx.decrypt(&gout605[0])); /* out12 */
    test_out.push_back(ctx.decrypt(&gout608[1])); /* out13 */
    test_out.push_back(ctx.decrypt(&gout613[0])); /* out14 */
    test_out.push_back(ctx.decrypt(&gout614[0])); /* out15 */
    test_out.push_back(ctx.decrypt(&gout618[0])); /* out16 */
    test_out.push_back(ctx.decrypt(&gout619[0])); /* out17 */
    test_out.push_back(ctx.decrypt(&gout625[0])); /* out18 */
    test_out.push_back(ctx.decrypt(&gout623[0])); /* out19 */
    test_out.push_back(ctx.decrypt(&gout628[0])); /* out20 */
    test_out.push_back(ctx.decrypt(&gout629[0])); /* out21 */
    test_out.push_back(ctx.decrypt(&gout632[0])); /* out22 */
    test_out.push_back(ctx.decrypt(&gout634[0])); /* out23 */
    test_out.push_back(ctx.decrypt(&gout638[0])); /* out24 */
    test_out.push_back(ctx.decrypt(&gout639[0])); /* out25 */
    test_out.push_back(ctx.decrypt(&gout641[0])); /* out26 */
    test_out.push_back(ctx.decrypt(&gout644[1])); /* out27 */
    test_out.push_back(ctx.decrypt(&gout646[0])); /* out28 */
    test_out.push_back(ctx.decrypt(&gout649[0])); /* out29 */
    test_out.push_back(ctx.decrypt(&gout651[0])); /* out30 */
    test_out.push_back(ctx.decrypt(&gout653[0])); /* out31 */
    return test_out;
}

static void
BM_structs_3d_lut2(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(tfhe_11_NTT);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(4);

    for (auto _ : state) {
        test_structs_3d_lut2(ctx);
    }
}

BENCHMARK(BM_structs_3d_lut2)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
