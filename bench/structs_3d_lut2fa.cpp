#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_structs_3d_lut2fa(FHEContext& ctx, std::vector<uint64_t> data = { 0 })
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

    std::cerr << "\rFA0    ";
    Ciphertext gin0 = 0 + 1 * ct_data0 + 1 * ct_data32;
    std::vector<Ciphertext> gout0 = ctx.eval_lut_amortized(&gin0, decomp);

    std::cerr << "\rFA1    ";
    Ciphertext gin1 = 0 + 1 * ct_data192 + 1 * ct_data224;
    std::vector<Ciphertext> gout1 = ctx.eval_lut_amortized(&gin1, decomp);

    std::cerr << "\rFA2    ";
    Ciphertext gin2 = gout1[1] + 1 * ct_data193 + 1 * ct_data225;
    std::vector<Ciphertext> gout2 = ctx.eval_lut_amortized(&gin2, decomp);

    std::cerr << "\rFA3    ";
    Ciphertext gin3 = 0 + 1 * ct_data128 + 1 * ct_data160;
    std::vector<Ciphertext> gout3 = ctx.eval_lut_amortized(&gin3, decomp);

    std::cerr << "\rFA4    ";
    Ciphertext gin4 = gout2[1] + 1 * ct_data194 + 1 * ct_data226;
    std::vector<Ciphertext> gout4 = ctx.eval_lut_amortized(&gin4, decomp);

    std::cerr << "\rFA5    ";
    Ciphertext gin5 = gout0[1] + 1 * ct_data1 + 1 * ct_data33;
    std::vector<Ciphertext> gout5 = ctx.eval_lut_amortized(&gin5, decomp);

    std::cerr << "\rFA6    ";
    Ciphertext gin6 = gout3[1] + 1 * ct_data129 + 1 * ct_data161;
    std::vector<Ciphertext> gout6 = ctx.eval_lut_amortized(&gin6, decomp);

    std::cerr << "\rFA7    ";
    Ciphertext gin7 = 0 + 1 * ct_data64 + 1 * ct_data96;
    std::vector<Ciphertext> gout7 = ctx.eval_lut_amortized(&gin7, decomp);

    std::cerr << "\rFA8    ";
    Ciphertext gin8 = 0 + 1 * gout3[0] + 1 * gout1[0];
    std::vector<Ciphertext> gout8 = ctx.eval_lut_amortized(&gin8, decomp);

    std::cerr << "\rFA9    ";
    Ciphertext gin9 = gout5[1] + 1 * ct_data2 + 1 * ct_data34;
    std::vector<Ciphertext> gout9 = ctx.eval_lut_amortized(&gin9, decomp);

    std::cerr << "\rFA10    ";
    Ciphertext gin10 = gout9[1] + 1 * ct_data3 + 1 * ct_data35;
    std::vector<Ciphertext> gout10 = ctx.eval_lut_amortized(&gin10, decomp);

    std::cerr << "\rFA11    ";
    Ciphertext gin11 = gout4[1] + 1 * ct_data195 + 1 * ct_data227;
    std::vector<Ciphertext> gout11 = ctx.eval_lut_amortized(&gin11, decomp);

    std::cerr << "\rFA12    ";
    Ciphertext gin12 = gout6[1] + 1 * ct_data130 + 1 * ct_data162;
    std::vector<Ciphertext> gout12 = ctx.eval_lut_amortized(&gin12, decomp);

    std::cerr << "\rFA13    ";
    Ciphertext gin13 = gout7[1] + 1 * ct_data65 + 1 * ct_data97;
    std::vector<Ciphertext> gout13 = ctx.eval_lut_amortized(&gin13, decomp);

    std::cerr << "\rFA14    ";
    Ciphertext gin14 = gout10[1] + 1 * ct_data4 + 1 * ct_data36;
    std::vector<Ciphertext> gout14 = ctx.eval_lut_amortized(&gin14, decomp);

    std::cerr << "\rFA15    ";
    Ciphertext gin15 = gout8[1] + 1 * gout6[0] + 1 * gout2[0];
    std::vector<Ciphertext> gout15 = ctx.eval_lut_amortized(&gin15, decomp);

    std::cerr << "\rFA16    ";
    Ciphertext gin16 = 0 + 1 * gout0[0] + 1 * gout7[0];
    std::vector<Ciphertext> gout16 = ctx.eval_lut_amortized(&gin16, decomp);

    std::cerr << "\rFA17    ";
    Ciphertext gin17 = gout12[1] + 1 * ct_data131 + 1 * ct_data163;
    std::vector<Ciphertext> gout17 = ctx.eval_lut_amortized(&gin17, decomp);

    std::cerr << "\rFA18    ";
    Ciphertext gin18 = 0 + 1 * gout16[0] + 1 * gout8[0];
    std::vector<Ciphertext> gout18 = ctx.eval_lut_amortized(&gin18, decomp);

    std::cerr << "\rFA19    ";
    Ciphertext gin19 = gout13[1] + 1 * ct_data66 + 1 * ct_data98;
    std::vector<Ciphertext> gout19 = ctx.eval_lut_amortized(&gin19, decomp);

    std::cerr << "\rFA20    ";
    Ciphertext gin20 = gout15[1] + 1 * gout12[0] + 1 * gout4[0];
    std::vector<Ciphertext> gout20 = ctx.eval_lut_amortized(&gin20, decomp);

    std::cerr << "\rFA21    ";
    Ciphertext gin21 = gout11[1] + 1 * ct_data196 + 1 * ct_data228;
    std::vector<Ciphertext> gout21 = ctx.eval_lut_amortized(&gin21, decomp);

    std::cerr << "\rFA22    ";
    Ciphertext gin22 = gout16[1] + 1 * gout5[0] + 1 * gout13[0];
    std::vector<Ciphertext> gout22 = ctx.eval_lut_amortized(&gin22, decomp);

    std::cerr << "\rFA23    ";
    Ciphertext gin23 = gout18[1] + 1 * gout22[0] + 1 * gout15[0];
    std::vector<Ciphertext> gout23 = ctx.eval_lut_amortized(&gin23, decomp);

    std::cerr << "\rFA24    ";
    Ciphertext gin24 = gout19[1] + 1 * ct_data67 + 1 * ct_data99;
    std::vector<Ciphertext> gout24 = ctx.eval_lut_amortized(&gin24, decomp);

    std::cerr << "\rFA25    ";
    Ciphertext gin25 = gout20[1] + 1 * gout17[0] + 1 * gout11[0];
    std::vector<Ciphertext> gout25 = ctx.eval_lut_amortized(&gin25, decomp);

    std::cerr << "\rFA26    ";
    Ciphertext gin26 = gout22[1] + 1 * gout9[0] + 1 * gout19[0];
    std::vector<Ciphertext> gout26 = ctx.eval_lut_amortized(&gin26, decomp);

    std::cerr << "\rFA27    ";
    Ciphertext gin27 = gout14[1] + 1 * ct_data5 + 1 * ct_data37;
    std::vector<Ciphertext> gout27 = ctx.eval_lut_amortized(&gin27, decomp);

    std::cerr << "\rFA28    ";
    Ciphertext gin28 = gout17[1] + 1 * ct_data132 + 1 * ct_data164;
    std::vector<Ciphertext> gout28 = ctx.eval_lut_amortized(&gin28, decomp);

    std::cerr << "\rFA29    ";
    Ciphertext gin29 = gout21[1] + 1 * ct_data197 + 1 * ct_data229;
    std::vector<Ciphertext> gout29 = ctx.eval_lut_amortized(&gin29, decomp);

    std::cerr << "\rFA30    ";
    Ciphertext gin30 = gout26[1] + 1 * gout10[0] + 1 * gout24[0];
    std::vector<Ciphertext> gout30 = ctx.eval_lut_amortized(&gin30, decomp);

    std::cerr << "\rFA31    ";
    Ciphertext gin31 = gout27[1] + 1 * ct_data6 + 1 * ct_data38;
    std::vector<Ciphertext> gout31 = ctx.eval_lut_amortized(&gin31, decomp);

    std::cerr << "\rFA32    ";
    Ciphertext gin32 = gout24[1] + 1 * ct_data68 + 1 * ct_data100;
    std::vector<Ciphertext> gout32 = ctx.eval_lut_amortized(&gin32, decomp);

    std::cerr << "\rFA33    ";
    Ciphertext gin33 = gout25[1] + 1 * gout28[0] + 1 * gout21[0];
    std::vector<Ciphertext> gout33 = ctx.eval_lut_amortized(&gin33, decomp);

    std::cerr << "\rFA34    ";
    Ciphertext gin34 = gout23[1] + 1 * gout26[0] + 1 * gout20[0];
    std::vector<Ciphertext> gout34 = ctx.eval_lut_amortized(&gin34, decomp);

    std::cerr << "\rFA35    ";
    Ciphertext gin35 = gout28[1] + 1 * ct_data133 + 1 * ct_data165;
    std::vector<Ciphertext> gout35 = ctx.eval_lut_amortized(&gin35, decomp);

    std::cerr << "\rFA36    ";
    Ciphertext gin36 = gout30[1] + 1 * gout14[0] + 1 * gout32[0];
    std::vector<Ciphertext> gout36 = ctx.eval_lut_amortized(&gin36, decomp);

    std::cerr << "\rFA37    ";
    Ciphertext gin37 = gout29[1] + 1 * ct_data198 + 1 * ct_data230;
    std::vector<Ciphertext> gout37 = ctx.eval_lut_amortized(&gin37, decomp);

    std::cerr << "\rFA38    ";
    Ciphertext gin38 = gout32[1] + 1 * ct_data69 + 1 * ct_data101;
    std::vector<Ciphertext> gout38 = ctx.eval_lut_amortized(&gin38, decomp);

    std::cerr << "\rFA39    ";
    Ciphertext gin39 = gout31[1] + 1 * ct_data7 + 1 * ct_data39;
    std::vector<Ciphertext> gout39 = ctx.eval_lut_amortized(&gin39, decomp);

    std::cerr << "\rFA40    ";
    Ciphertext gin40 = gout33[1] + 1 * gout35[0] + 1 * gout29[0];
    std::vector<Ciphertext> gout40 = ctx.eval_lut_amortized(&gin40, decomp);

    std::cerr << "\rFA41    ";
    Ciphertext gin41 = gout35[1] + 1 * ct_data134 + 1 * ct_data166;
    std::vector<Ciphertext> gout41 = ctx.eval_lut_amortized(&gin41, decomp);

    std::cerr << "\rFA42    ";
    Ciphertext gin42 = gout34[1] + 1 * gout30[0] + 1 * gout25[0];
    std::vector<Ciphertext> gout42 = ctx.eval_lut_amortized(&gin42, decomp);

    std::cerr << "\rFA43    ";
    Ciphertext gin43 = gout37[1] + 1 * ct_data199 + 1 * ct_data231;
    std::vector<Ciphertext> gout43 = ctx.eval_lut_amortized(&gin43, decomp);

    std::cerr << "\rFA44    ";
    Ciphertext gin44 = gout38[1] + 1 * ct_data70 + 1 * ct_data102;
    std::vector<Ciphertext> gout44 = ctx.eval_lut_amortized(&gin44, decomp);

    std::cerr << "\rFA45    ";
    Ciphertext gin45 = gout36[1] + 1 * gout27[0] + 1 * gout38[0];
    std::vector<Ciphertext> gout45 = ctx.eval_lut_amortized(&gin45, decomp);

    std::cerr << "\rFA46    ";
    Ciphertext gin46 = gout40[1] + 1 * gout41[0] + 1 * gout37[0];
    std::vector<Ciphertext> gout46 = ctx.eval_lut_amortized(&gin46, decomp);

    std::cerr << "\rFA47    ";
    Ciphertext gin47 = gout42[1] + 1 * gout36[0] + 1 * gout33[0];
    std::vector<Ciphertext> gout47 = ctx.eval_lut_amortized(&gin47, decomp);

    std::cerr << "\rFA48    ";
    Ciphertext gin48 = gout39[1] + 1 * ct_data8 + 1 * ct_data40;
    std::vector<Ciphertext> gout48 = ctx.eval_lut_amortized(&gin48, decomp);

    std::cerr << "\rFA49    ";
    Ciphertext gin49 = gout41[1] + 1 * ct_data135 + 1 * ct_data167;
    std::vector<Ciphertext> gout49 = ctx.eval_lut_amortized(&gin49, decomp);

    std::cerr << "\rFA50    ";
    Ciphertext gin50 = gout43[1] + 1 * ct_data200 + 1 * ct_data232;
    std::vector<Ciphertext> gout50 = ctx.eval_lut_amortized(&gin50, decomp);

    std::cerr << "\rFA51    ";
    Ciphertext gin51 = gout45[1] + 1 * gout31[0] + 1 * gout44[0];
    std::vector<Ciphertext> gout51 = ctx.eval_lut_amortized(&gin51, decomp);

    std::cerr << "\rFA52    ";
    Ciphertext gin52 = gout48[1] + 1 * ct_data9 + 1 * ct_data41;
    std::vector<Ciphertext> gout52 = ctx.eval_lut_amortized(&gin52, decomp);

    std::cerr << "\rFA53    ";
    Ciphertext gin53 = gout44[1] + 1 * ct_data71 + 1 * ct_data103;
    std::vector<Ciphertext> gout53 = ctx.eval_lut_amortized(&gin53, decomp);

    std::cerr << "\rFA54    ";
    Ciphertext gin54 = gout46[1] + 1 * gout49[0] + 1 * gout43[0];
    std::vector<Ciphertext> gout54 = ctx.eval_lut_amortized(&gin54, decomp);

    std::cerr << "\rFA55    ";
    Ciphertext gin55 = gout47[1] + 1 * gout45[0] + 1 * gout40[0];
    std::vector<Ciphertext> gout55 = ctx.eval_lut_amortized(&gin55, decomp);

    std::cerr << "\rFA56    ";
    Ciphertext gin56 = gout49[1] + 1 * ct_data136 + 1 * ct_data168;
    std::vector<Ciphertext> gout56 = ctx.eval_lut_amortized(&gin56, decomp);

    std::cerr << "\rFA57    ";
    Ciphertext gin57 = gout51[1] + 1 * gout39[0] + 1 * gout53[0];
    std::vector<Ciphertext> gout57 = ctx.eval_lut_amortized(&gin57, decomp);

    std::cerr << "\rFA58    ";
    Ciphertext gin58 = gout50[1] + 1 * ct_data201 + 1 * ct_data233;
    std::vector<Ciphertext> gout58 = ctx.eval_lut_amortized(&gin58, decomp);

    std::cerr << "\rFA59    ";
    Ciphertext gin59 = gout53[1] + 1 * ct_data72 + 1 * ct_data104;
    std::vector<Ciphertext> gout59 = ctx.eval_lut_amortized(&gin59, decomp);

    std::cerr << "\rFA60    ";
    Ciphertext gin60 = gout54[1] + 1 * gout56[0] + 1 * gout50[0];
    std::vector<Ciphertext> gout60 = ctx.eval_lut_amortized(&gin60, decomp);

    std::cerr << "\rFA61    ";
    Ciphertext gin61 = gout55[1] + 1 * gout51[0] + 1 * gout46[0];
    std::vector<Ciphertext> gout61 = ctx.eval_lut_amortized(&gin61, decomp);

    std::cerr << "\rFA62    ";
    Ciphertext gin62 = gout52[1] + 1 * ct_data10 + 1 * ct_data42;
    std::vector<Ciphertext> gout62 = ctx.eval_lut_amortized(&gin62, decomp);

    std::cerr << "\rFA63    ";
    Ciphertext gin63 = gout56[1] + 1 * ct_data137 + 1 * ct_data169;
    std::vector<Ciphertext> gout63 = ctx.eval_lut_amortized(&gin63, decomp);

    std::cerr << "\rFA64    ";
    Ciphertext gin64 = gout63[1] + 1 * ct_data138 + 1 * ct_data170;
    std::vector<Ciphertext> gout64 = ctx.eval_lut_amortized(&gin64, decomp);

    std::cerr << "\rFA65    ";
    Ciphertext gin65 = gout59[1] + 1 * ct_data73 + 1 * ct_data105;
    std::vector<Ciphertext> gout65 = ctx.eval_lut_amortized(&gin65, decomp);

    std::cerr << "\rFA66    ";
    Ciphertext gin66 = gout57[1] + 1 * gout48[0] + 1 * gout59[0];
    std::vector<Ciphertext> gout66 = ctx.eval_lut_amortized(&gin66, decomp);

    std::cerr << "\rFA67    ";
    Ciphertext gin67 = gout58[1] + 1 * ct_data202 + 1 * ct_data234;
    std::vector<Ciphertext> gout67 = ctx.eval_lut_amortized(&gin67, decomp);

    std::cerr << "\rFA68    ";
    Ciphertext gin68 = gout65[1] + 1 * ct_data74 + 1 * ct_data106;
    std::vector<Ciphertext> gout68 = ctx.eval_lut_amortized(&gin68, decomp);

    std::cerr << "\rFA69    ";
    Ciphertext gin69 = gout60[1] + 1 * gout63[0] + 1 * gout58[0];
    std::vector<Ciphertext> gout69 = ctx.eval_lut_amortized(&gin69, decomp);

    std::cerr << "\rFA70    ";
    Ciphertext gin70 = gout61[1] + 1 * gout57[0] + 1 * gout54[0];
    std::vector<Ciphertext> gout70 = ctx.eval_lut_amortized(&gin70, decomp);

    std::cerr << "\rFA71    ";
    Ciphertext gin71 = gout69[1] + 1 * gout64[0] + 1 * gout67[0];
    std::vector<Ciphertext> gout71 = ctx.eval_lut_amortized(&gin71, decomp);

    std::cerr << "\rFA72    ";
    Ciphertext gin72 = gout64[1] + 1 * ct_data139 + 1 * ct_data171;
    std::vector<Ciphertext> gout72 = ctx.eval_lut_amortized(&gin72, decomp);

    std::cerr << "\rFA73    ";
    Ciphertext gin73 = gout62[1] + 1 * ct_data11 + 1 * ct_data43;
    std::vector<Ciphertext> gout73 = ctx.eval_lut_amortized(&gin73, decomp);

    std::cerr << "\rFA74    ";
    Ciphertext gin74 = gout66[1] + 1 * gout52[0] + 1 * gout65[0];
    std::vector<Ciphertext> gout74 = ctx.eval_lut_amortized(&gin74, decomp);

    std::cerr << "\rFA75    ";
    Ciphertext gin75 = gout67[1] + 1 * ct_data203 + 1 * ct_data235;
    std::vector<Ciphertext> gout75 = ctx.eval_lut_amortized(&gin75, decomp);

    std::cerr << "\rFA76    ";
    Ciphertext gin76 = gout68[1] + 1 * ct_data75 + 1 * ct_data107;
    std::vector<Ciphertext> gout76 = ctx.eval_lut_amortized(&gin76, decomp);

    std::cerr << "\rFA77    ";
    Ciphertext gin77 = gout71[1] + 1 * gout72[0] + 1 * gout75[0];
    std::vector<Ciphertext> gout77 = ctx.eval_lut_amortized(&gin77, decomp);

    std::cerr << "\rFA78    ";
    Ciphertext gin78 = gout70[1] + 1 * gout66[0] + 1 * gout60[0];
    std::vector<Ciphertext> gout78 = ctx.eval_lut_amortized(&gin78, decomp);

    std::cerr << "\rFA79    ";
    Ciphertext gin79 = gout72[1] + 1 * ct_data140 + 1 * ct_data172;
    std::vector<Ciphertext> gout79 = ctx.eval_lut_amortized(&gin79, decomp);

    std::cerr << "\rFA80    ";
    Ciphertext gin80 = gout74[1] + 1 * gout62[0] + 1 * gout68[0];
    std::vector<Ciphertext> gout80 = ctx.eval_lut_amortized(&gin80, decomp);

    std::cerr << "\rFA81    ";
    Ciphertext gin81 = gout73[1] + 1 * ct_data12 + 1 * ct_data44;
    std::vector<Ciphertext> gout81 = ctx.eval_lut_amortized(&gin81, decomp);

    std::cerr << "\rFA82    ";
    Ciphertext gin82 = gout76[1] + 1 * ct_data76 + 1 * ct_data108;
    std::vector<Ciphertext> gout82 = ctx.eval_lut_amortized(&gin82, decomp);

    std::cerr << "\rFA83    ";
    Ciphertext gin83 = gout75[1] + 1 * ct_data204 + 1 * ct_data236;
    std::vector<Ciphertext> gout83 = ctx.eval_lut_amortized(&gin83, decomp);

    std::cerr << "\rFA84    ";
    Ciphertext gin84 = gout78[1] + 1 * gout74[0] + 1 * gout69[0];
    std::vector<Ciphertext> gout84 = ctx.eval_lut_amortized(&gin84, decomp);

    std::cerr << "\rFA85    ";
    Ciphertext gin85 = gout79[1] + 1 * ct_data141 + 1 * ct_data173;
    std::vector<Ciphertext> gout85 = ctx.eval_lut_amortized(&gin85, decomp);

    std::cerr << "\rFA86    ";
    Ciphertext gin86 = gout81[1] + 1 * ct_data13 + 1 * ct_data45;
    std::vector<Ciphertext> gout86 = ctx.eval_lut_amortized(&gin86, decomp);

    std::cerr << "\rFA87    ";
    Ciphertext gin87 = gout80[1] + 1 * gout73[0] + 1 * gout76[0];
    std::vector<Ciphertext> gout87 = ctx.eval_lut_amortized(&gin87, decomp);

    std::cerr << "\rFA88    ";
    Ciphertext gin88 = gout83[1] + 1 * ct_data205 + 1 * ct_data237;
    std::vector<Ciphertext> gout88 = ctx.eval_lut_amortized(&gin88, decomp);

    std::cerr << "\rFA89    ";
    Ciphertext gin89 = gout82[1] + 1 * ct_data77 + 1 * ct_data109;
    std::vector<Ciphertext> gout89 = ctx.eval_lut_amortized(&gin89, decomp);

    std::cerr << "\rFA90    ";
    Ciphertext gin90 = gout86[1] + 1 * ct_data14 + 1 * ct_data46;
    std::vector<Ciphertext> gout90 = ctx.eval_lut_amortized(&gin90, decomp);

    std::cerr << "\rFA91    ";
    Ciphertext gin91 = gout77[1] + 1 * gout79[0] + 1 * gout83[0];
    std::vector<Ciphertext> gout91 = ctx.eval_lut_amortized(&gin91, decomp);

    std::cerr << "\rFA92    ";
    Ciphertext gin92 = gout84[1] + 1 * gout80[0] + 1 * gout71[0];
    std::vector<Ciphertext> gout92 = ctx.eval_lut_amortized(&gin92, decomp);

    std::cerr << "\rFA93    ";
    Ciphertext gin93 = gout85[1] + 1 * ct_data142 + 1 * ct_data174;
    std::vector<Ciphertext> gout93 = ctx.eval_lut_amortized(&gin93, decomp);

    std::cerr << "\rFA94    ";
    Ciphertext gin94 = gout87[1] + 1 * gout81[0] + 1 * gout82[0];
    std::vector<Ciphertext> gout94 = ctx.eval_lut_amortized(&gin94, decomp);

    std::cerr << "\rFA95    ";
    Ciphertext gin95 = gout90[1] + 1 * ct_data15 + 1 * ct_data47;
    std::vector<Ciphertext> gout95 = ctx.eval_lut_amortized(&gin95, decomp);

    std::cerr << "\rFA96    ";
    Ciphertext gin96 = gout95[1] + 1 * ct_data16 + 1 * ct_data48;
    std::vector<Ciphertext> gout96 = ctx.eval_lut_amortized(&gin96, decomp);

    std::cerr << "\rFA97    ";
    Ciphertext gin97 = gout88[1] + 1 * ct_data206 + 1 * ct_data238;
    std::vector<Ciphertext> gout97 = ctx.eval_lut_amortized(&gin97, decomp);

    std::cerr << "\rFA98    ";
    Ciphertext gin98 = gout89[1] + 1 * ct_data78 + 1 * ct_data110;
    std::vector<Ciphertext> gout98 = ctx.eval_lut_amortized(&gin98, decomp);

    std::cerr << "\rFA99    ";
    Ciphertext gin99 = gout94[1] + 1 * gout86[0] + 1 * gout89[0];
    std::vector<Ciphertext> gout99 = ctx.eval_lut_amortized(&gin99, decomp);

    std::cerr << "\rFA100    ";
    Ciphertext gin100 = gout93[1] + 1 * ct_data143 + 1 * ct_data175;
    std::vector<Ciphertext> gout100 = ctx.eval_lut_amortized(&gin100, decomp);

    std::cerr << "\rFA101    ";
    Ciphertext gin101 = gout91[1] + 1 * gout85[0] + 1 * gout88[0];
    std::vector<Ciphertext> gout101 = ctx.eval_lut_amortized(&gin101, decomp);

    std::cerr << "\rFA102    ";
    Ciphertext gin102 = gout92[1] + 1 * gout87[0] + 1 * gout77[0];
    std::vector<Ciphertext> gout102 = ctx.eval_lut_amortized(&gin102, decomp);

    std::cerr << "\rFA103    ";
    Ciphertext gin103 = gout98[1] + 1 * ct_data79 + 1 * ct_data111;
    std::vector<Ciphertext> gout103 = ctx.eval_lut_amortized(&gin103, decomp);

    std::cerr << "\rFA104    ";
    Ciphertext gin104 = gout99[1] + 1 * gout90[0] + 1 * gout98[0];
    std::vector<Ciphertext> gout104 = ctx.eval_lut_amortized(&gin104, decomp);

    std::cerr << "\rFA105    ";
    Ciphertext gin105 = gout96[1] + 1 * ct_data17 + 1 * ct_data49;
    std::vector<Ciphertext> gout105 = ctx.eval_lut_amortized(&gin105, decomp);

    std::cerr << "\rFA106    ";
    Ciphertext gin106 = gout97[1] + 1 * ct_data207 + 1 * ct_data239;
    std::vector<Ciphertext> gout106 = ctx.eval_lut_amortized(&gin106, decomp);

    std::cerr << "\rFA107    ";
    Ciphertext gin107 = gout101[1] + 1 * gout93[0] + 1 * gout97[0];
    std::vector<Ciphertext> gout107 = ctx.eval_lut_amortized(&gin107, decomp);

    std::cerr << "\rFA108    ";
    Ciphertext gin108 = gout100[1] + 1 * ct_data144 + 1 * ct_data176;
    std::vector<Ciphertext> gout108 = ctx.eval_lut_amortized(&gin108, decomp);

    std::cerr << "\rFA109    ";
    Ciphertext gin109 = gout104[1] + 1 * gout95[0] + 1 * gout103[0];
    std::vector<Ciphertext> gout109 = ctx.eval_lut_amortized(&gin109, decomp);

    std::cerr << "\rFA110    ";
    Ciphertext gin110 = gout105[1] + 1 * ct_data18 + 1 * ct_data50;
    std::vector<Ciphertext> gout110 = ctx.eval_lut_amortized(&gin110, decomp);

    std::cerr << "\rFA111    ";
    Ciphertext gin111 = gout106[1] + 1 * ct_data208 + 1 * ct_data240;
    std::vector<Ciphertext> gout111 = ctx.eval_lut_amortized(&gin111, decomp);

    std::cerr << "\rFA112    ";
    Ciphertext gin112 = gout103[1] + 1 * ct_data80 + 1 * ct_data112;
    std::vector<Ciphertext> gout112 = ctx.eval_lut_amortized(&gin112, decomp);

    std::cerr << "\rFA113    ";
    Ciphertext gin113 = gout107[1] + 1 * gout100[0] + 1 * gout106[0];
    std::vector<Ciphertext> gout113 = ctx.eval_lut_amortized(&gin113, decomp);

    std::cerr << "\rFA114    ";
    Ciphertext gin114 = gout108[1] + 1 * ct_data145 + 1 * ct_data177;
    std::vector<Ciphertext> gout114 = ctx.eval_lut_amortized(&gin114, decomp);

    std::cerr << "\rFA115    ";
    Ciphertext gin115 = gout109[1] + 1 * gout96[0] + 1 * gout112[0];
    std::vector<Ciphertext> gout115 = ctx.eval_lut_amortized(&gin115, decomp);

    std::cerr << "\rFA116    ";
    Ciphertext gin116 = gout102[1] + 1 * gout94[0] + 1 * gout91[0];
    std::vector<Ciphertext> gout116 = ctx.eval_lut_amortized(&gin116, decomp);

    std::cerr << "\rFA117    ";
    Ciphertext gin117 = gout111[1] + 1 * ct_data209 + 1 * ct_data241;
    std::vector<Ciphertext> gout117 = ctx.eval_lut_amortized(&gin117, decomp);

    std::cerr << "\rFA118    ";
    Ciphertext gin118 = gout112[1] + 1 * ct_data81 + 1 * ct_data113;
    std::vector<Ciphertext> gout118 = ctx.eval_lut_amortized(&gin118, decomp);

    std::cerr << "\rFA119    ";
    Ciphertext gin119 = gout110[1] + 1 * ct_data19 + 1 * ct_data51;
    std::vector<Ciphertext> gout119 = ctx.eval_lut_amortized(&gin119, decomp);

    std::cerr << "\rFA120    ";
    Ciphertext gin120 = gout114[1] + 1 * ct_data146 + 1 * ct_data178;
    std::vector<Ciphertext> gout120 = ctx.eval_lut_amortized(&gin120, decomp);

    std::cerr << "\rFA121    ";
    Ciphertext gin121 = gout117[1] + 1 * ct_data210 + 1 * ct_data242;
    std::vector<Ciphertext> gout121 = ctx.eval_lut_amortized(&gin121, decomp);

    std::cerr << "\rFA122    ";
    Ciphertext gin122 = gout113[1] + 1 * gout108[0] + 1 * gout111[0];
    std::vector<Ciphertext> gout122 = ctx.eval_lut_amortized(&gin122, decomp);

    std::cerr << "\rFA123    ";
    Ciphertext gin123 = gout119[1] + 1 * ct_data20 + 1 * ct_data52;
    std::vector<Ciphertext> gout123 = ctx.eval_lut_amortized(&gin123, decomp);

    std::cerr << "\rFA124    ";
    Ciphertext gin124 = gout116[1] + 1 * gout99[0] + 1 * gout101[0];
    std::vector<Ciphertext> gout124 = ctx.eval_lut_amortized(&gin124, decomp);

    std::cerr << "\rFA125    ";
    Ciphertext gin125 = gout121[1] + 1 * ct_data211 + 1 * ct_data243;
    std::vector<Ciphertext> gout125 = ctx.eval_lut_amortized(&gin125, decomp);

    std::cerr << "\rFA126    ";
    Ciphertext gin126 = gout118[1] + 1 * ct_data82 + 1 * ct_data114;
    std::vector<Ciphertext> gout126 = ctx.eval_lut_amortized(&gin126, decomp);

    std::cerr << "\rFA127    ";
    Ciphertext gin127 = gout115[1] + 1 * gout105[0] + 1 * gout118[0];
    std::vector<Ciphertext> gout127 = ctx.eval_lut_amortized(&gin127, decomp);

    std::cerr << "\rFA128    ";
    Ciphertext gin128 = gout122[1] + 1 * gout114[0] + 1 * gout117[0];
    std::vector<Ciphertext> gout128 = ctx.eval_lut_amortized(&gin128, decomp);

    std::cerr << "\rFA129    ";
    Ciphertext gin129 = gout120[1] + 1 * ct_data147 + 1 * ct_data179;
    std::vector<Ciphertext> gout129 = ctx.eval_lut_amortized(&gin129, decomp);

    std::cerr << "\rFA130    ";
    Ciphertext gin130 = gout125[1] + 1 * ct_data212 + 1 * ct_data244;
    std::vector<Ciphertext> gout130 = ctx.eval_lut_amortized(&gin130, decomp);

    std::cerr << "\rFA131    ";
    Ciphertext gin131 = gout123[1] + 1 * ct_data21 + 1 * ct_data53;
    std::vector<Ciphertext> gout131 = ctx.eval_lut_amortized(&gin131, decomp);

    std::cerr << "\rFA132    ";
    Ciphertext gin132 = gout127[1] + 1 * gout110[0] + 1 * gout126[0];
    std::vector<Ciphertext> gout132 = ctx.eval_lut_amortized(&gin132, decomp);

    std::cerr << "\rFA133    ";
    Ciphertext gin133 = gout124[1] + 1 * gout104[0] + 1 * gout107[0];
    std::vector<Ciphertext> gout133 = ctx.eval_lut_amortized(&gin133, decomp);

    std::cerr << "\rFA134    ";
    Ciphertext gin134 = gout129[1] + 1 * ct_data148 + 1 * ct_data180;
    std::vector<Ciphertext> gout134 = ctx.eval_lut_amortized(&gin134, decomp);

    std::cerr << "\rFA135    ";
    Ciphertext gin135 = gout126[1] + 1 * ct_data83 + 1 * ct_data115;
    std::vector<Ciphertext> gout135 = ctx.eval_lut_amortized(&gin135, decomp);

    std::cerr << "\rFA136    ";
    Ciphertext gin136 = gout128[1] + 1 * gout120[0] + 1 * gout121[0];
    std::vector<Ciphertext> gout136 = ctx.eval_lut_amortized(&gin136, decomp);

    std::cerr << "\rFA137    ";
    Ciphertext gin137 = gout130[1] + 1 * ct_data213 + 1 * ct_data245;
    std::vector<Ciphertext> gout137 = ctx.eval_lut_amortized(&gin137, decomp);

    std::cerr << "\rFA138    ";
    Ciphertext gin138 = gout135[1] + 1 * ct_data84 + 1 * ct_data116;
    std::vector<Ciphertext> gout138 = ctx.eval_lut_amortized(&gin138, decomp);

    std::cerr << "\rFA139    ";
    Ciphertext gin139 = gout131[1] + 1 * ct_data22 + 1 * ct_data54;
    std::vector<Ciphertext> gout139 = ctx.eval_lut_amortized(&gin139, decomp);

    std::cerr << "\rFA140    ";
    Ciphertext gin140 = gout132[1] + 1 * gout119[0] + 1 * gout135[0];
    std::vector<Ciphertext> gout140 = ctx.eval_lut_amortized(&gin140, decomp);

    std::cerr << "\rFA141    ";
    Ciphertext gin141 = gout133[1] + 1 * gout109[0] + 1 * gout113[0];
    std::vector<Ciphertext> gout141 = ctx.eval_lut_amortized(&gin141, decomp);

    std::cerr << "\rFA142    ";
    Ciphertext gin142 = gout134[1] + 1 * ct_data149 + 1 * ct_data181;
    std::vector<Ciphertext> gout142 = ctx.eval_lut_amortized(&gin142, decomp);

    std::cerr << "\rFA143    ";
    Ciphertext gin143 = gout137[1] + 1 * ct_data214 + 1 * ct_data246;
    std::vector<Ciphertext> gout143 = ctx.eval_lut_amortized(&gin143, decomp);

    std::cerr << "\rFA144    ";
    Ciphertext gin144 = gout140[1] + 1 * gout123[0] + 1 * gout138[0];
    std::vector<Ciphertext> gout144 = ctx.eval_lut_amortized(&gin144, decomp);

    std::cerr << "\rFA145    ";
    Ciphertext gin145 = gout136[1] + 1 * gout129[0] + 1 * gout125[0];
    std::vector<Ciphertext> gout145 = ctx.eval_lut_amortized(&gin145, decomp);

    std::cerr << "\rFA146    ";
    Ciphertext gin146 = gout139[1] + 1 * ct_data23 + 1 * ct_data55;
    std::vector<Ciphertext> gout146 = ctx.eval_lut_amortized(&gin146, decomp);

    std::cerr << "\rFA147    ";
    Ciphertext gin147 = gout141[1] + 1 * gout115[0] + 1 * gout122[0];
    std::vector<Ciphertext> gout147 = ctx.eval_lut_amortized(&gin147, decomp);

    std::cerr << "\rFA148    ";
    Ciphertext gin148 = gout138[1] + 1 * ct_data85 + 1 * ct_data117;
    std::vector<Ciphertext> gout148 = ctx.eval_lut_amortized(&gin148, decomp);

    std::cerr << "\rFA149    ";
    Ciphertext gin149 = gout142[1] + 1 * ct_data150 + 1 * ct_data182;
    std::vector<Ciphertext> gout149 = ctx.eval_lut_amortized(&gin149, decomp);

    std::cerr << "\rFA150    ";
    Ciphertext gin150 = gout145[1] + 1 * gout134[0] + 1 * gout130[0];
    std::vector<Ciphertext> gout150 = ctx.eval_lut_amortized(&gin150, decomp);

    std::cerr << "\rFA151    ";
    Ciphertext gin151 = gout144[1] + 1 * gout131[0] + 1 * gout148[0];
    std::vector<Ciphertext> gout151 = ctx.eval_lut_amortized(&gin151, decomp);

    std::cerr << "\rFA152    ";
    Ciphertext gin152 = gout143[1] + 1 * ct_data215 + 1 * ct_data247;
    std::vector<Ciphertext> gout152 = ctx.eval_lut_amortized(&gin152, decomp);

    std::cerr << "\rFA153    ";
    Ciphertext gin153 = gout148[1] + 1 * ct_data86 + 1 * ct_data118;
    std::vector<Ciphertext> gout153 = ctx.eval_lut_amortized(&gin153, decomp);

    std::cerr << "\rFA154    ";
    Ciphertext gin154 = gout146[1] + 1 * ct_data24 + 1 * ct_data56;
    std::vector<Ciphertext> gout154 = ctx.eval_lut_amortized(&gin154, decomp);

    std::cerr << "\rFA155    ";
    Ciphertext gin155 = gout154[1] + 1 * ct_data25 + 1 * ct_data57;
    std::vector<Ciphertext> gout155 = ctx.eval_lut_amortized(&gin155, decomp);

    std::cerr << "\rFA156    ";
    Ciphertext gin156 = gout147[1] + 1 * gout127[0] + 1 * gout128[0];
    std::vector<Ciphertext> gout156 = ctx.eval_lut_amortized(&gin156, decomp);

    std::cerr << "\rFA157    ";
    Ciphertext gin157 = gout149[1] + 1 * ct_data151 + 1 * ct_data183;
    std::vector<Ciphertext> gout157 = ctx.eval_lut_amortized(&gin157, decomp);

    std::cerr << "\rFA158    ";
    Ciphertext gin158 = gout150[1] + 1 * gout142[0] + 1 * gout137[0];
    std::vector<Ciphertext> gout158 = ctx.eval_lut_amortized(&gin158, decomp);

    std::cerr << "\rFA159    ";
    Ciphertext gin159 = gout152[1] + 1 * ct_data216 + 1 * ct_data248;
    std::vector<Ciphertext> gout159 = ctx.eval_lut_amortized(&gin159, decomp);

    std::cerr << "\rFA160    ";
    Ciphertext gin160 = gout153[1] + 1 * ct_data87 + 1 * ct_data119;
    std::vector<Ciphertext> gout160 = ctx.eval_lut_amortized(&gin160, decomp);

    std::cerr << "\rFA161    ";
    Ciphertext gin161 = gout151[1] + 1 * gout139[0] + 1 * gout153[0];
    std::vector<Ciphertext> gout161 = ctx.eval_lut_amortized(&gin161, decomp);

    std::cerr << "\rFA162    ";
    Ciphertext gin162 = gout155[1] + 1 * ct_data26 + 1 * ct_data58;
    std::vector<Ciphertext> gout162 = ctx.eval_lut_amortized(&gin162, decomp);

    std::cerr << "\rFA163    ";
    Ciphertext gin163 = gout156[1] + 1 * gout132[0] + 1 * gout136[0];
    std::vector<Ciphertext> gout163 = ctx.eval_lut_amortized(&gin163, decomp);

    std::cerr << "\rFA164    ";
    Ciphertext gin164 = gout158[1] + 1 * gout149[0] + 1 * gout143[0];
    std::vector<Ciphertext> gout164 = ctx.eval_lut_amortized(&gin164, decomp);

    std::cerr << "\rFA165    ";
    Ciphertext gin165 = gout157[1] + 1 * ct_data152 + 1 * ct_data184;
    std::vector<Ciphertext> gout165 = ctx.eval_lut_amortized(&gin165, decomp);

    std::cerr << "\rFA166    ";
    Ciphertext gin166 = gout162[1] + 1 * ct_data27 + 1 * ct_data59;
    std::vector<Ciphertext> gout166 = ctx.eval_lut_amortized(&gin166, decomp);

    std::cerr << "\rFA167    ";
    Ciphertext gin167 = gout159[1] + 1 * ct_data217 + 1 * ct_data249;
    std::vector<Ciphertext> gout167 = ctx.eval_lut_amortized(&gin167, decomp);

    std::cerr << "\rFA168    ";
    Ciphertext gin168 = gout161[1] + 1 * gout146[0] + 1 * gout160[0];
    std::vector<Ciphertext> gout168 = ctx.eval_lut_amortized(&gin168, decomp);

    std::cerr << "\rFA169    ";
    Ciphertext gin169 = gout163[1] + 1 * gout140[0] + 1 * gout145[0];
    std::vector<Ciphertext> gout169 = ctx.eval_lut_amortized(&gin169, decomp);

    std::cerr << "\rFA170    ";
    Ciphertext gin170 = gout160[1] + 1 * ct_data88 + 1 * ct_data120;
    std::vector<Ciphertext> gout170 = ctx.eval_lut_amortized(&gin170, decomp);

    std::cerr << "\rFA171    ";
    Ciphertext gin171 = gout169[1] + 1 * gout144[0] + 1 * gout150[0];
    std::vector<Ciphertext> gout171 = ctx.eval_lut_amortized(&gin171, decomp);

    std::cerr << "\rFA172    ";
    Ciphertext gin172 = gout164[1] + 1 * gout157[0] + 1 * gout152[0];
    std::vector<Ciphertext> gout172 = ctx.eval_lut_amortized(&gin172, decomp);

    std::cerr << "\rFA173    ";
    Ciphertext gin173 = gout165[1] + 1 * ct_data153 + 1 * ct_data185;
    std::vector<Ciphertext> gout173 = ctx.eval_lut_amortized(&gin173, decomp);

    std::cerr << "\rFA174    ";
    Ciphertext gin174 = gout171[1] + 1 * gout151[0] + 1 * gout158[0];
    std::vector<Ciphertext> gout174 = ctx.eval_lut_amortized(&gin174, decomp);

    std::cerr << "\rFA175    ";
    Ciphertext gin175 = gout167[1] + 1 * ct_data218 + 1 * ct_data250;
    std::vector<Ciphertext> gout175 = ctx.eval_lut_amortized(&gin175, decomp);

    std::cerr << "\rFA176    ";
    Ciphertext gin176 = gout168[1] + 1 * gout154[0] + 1 * gout170[0];
    std::vector<Ciphertext> gout176 = ctx.eval_lut_amortized(&gin176, decomp);

    std::cerr << "\rFA177    ";
    Ciphertext gin177 = gout166[1] + 1 * ct_data28 + 1 * ct_data60;
    std::vector<Ciphertext> gout177 = ctx.eval_lut_amortized(&gin177, decomp);

    std::cerr << "\rFA178    ";
    Ciphertext gin178 = gout170[1] + 1 * ct_data89 + 1 * ct_data121;
    std::vector<Ciphertext> gout178 = ctx.eval_lut_amortized(&gin178, decomp);

    std::cerr << "\rFA179    ";
    Ciphertext gin179 = gout173[1] + 1 * ct_data154 + 1 * ct_data186;
    std::vector<Ciphertext> gout179 = ctx.eval_lut_amortized(&gin179, decomp);

    std::cerr << "\rFA180    ";
    Ciphertext gin180 = gout172[1] + 1 * gout165[0] + 1 * gout159[0];
    std::vector<Ciphertext> gout180 = ctx.eval_lut_amortized(&gin180, decomp);

    std::cerr << "\rFA181    ";
    Ciphertext gin181 = gout174[1] + 1 * gout161[0] + 1 * gout164[0];
    std::vector<Ciphertext> gout181 = ctx.eval_lut_amortized(&gin181, decomp);

    std::cerr << "\rFA182    ";
    Ciphertext gin182 = gout177[1] + 1 * ct_data29 + 1 * ct_data61;
    std::vector<Ciphertext> gout182 = ctx.eval_lut_amortized(&gin182, decomp);

    std::cerr << "\rFA183    ";
    Ciphertext gin183 = gout175[1] + 1 * ct_data219 + 1 * ct_data251;
    std::vector<Ciphertext> gout183 = ctx.eval_lut_amortized(&gin183, decomp);

    std::cerr << "\rFA184    ";
    Ciphertext gin184 = gout178[1] + 1 * ct_data90 + 1 * ct_data122;
    std::vector<Ciphertext> gout184 = ctx.eval_lut_amortized(&gin184, decomp);

    std::cerr << "\rFA185    ";
    Ciphertext gin185 = gout176[1] + 1 * gout155[0] + 1 * gout178[0];
    std::vector<Ciphertext> gout185 = ctx.eval_lut_amortized(&gin185, decomp);

    std::cerr << "\rFA186    ";
    Ciphertext gin186 = gout180[1] + 1 * gout173[0] + 1 * gout167[0];
    std::vector<Ciphertext> gout186 = ctx.eval_lut_amortized(&gin186, decomp);

    std::cerr << "\rFA187    ";
    Ciphertext gin187 = gout179[1] + 1 * ct_data155 + 1 * ct_data187;
    std::vector<Ciphertext> gout187 = ctx.eval_lut_amortized(&gin187, decomp);

    std::cerr << "\rFA188    ";
    Ciphertext gin188 = gout181[1] + 1 * gout168[0] + 1 * gout172[0];
    std::vector<Ciphertext> gout188 = ctx.eval_lut_amortized(&gin188, decomp);

    std::cerr << "\rFA189    ";
    Ciphertext gin189 = gout182[1] + 1 * ct_data30 + 1 * ct_data62;
    std::vector<Ciphertext> gout189 = ctx.eval_lut_amortized(&gin189, decomp);

    std::cerr << "\rFA190    ";
    Ciphertext gin190 = gout183[1] + 1 * ct_data220 + 1 * ct_data252;
    std::vector<Ciphertext> gout190 = ctx.eval_lut_amortized(&gin190, decomp);

    std::cerr << "\rFA191    ";
    Ciphertext gin191 = gout185[1] + 1 * gout162[0] + 1 * gout184[0];
    std::vector<Ciphertext> gout191 = ctx.eval_lut_amortized(&gin191, decomp);

    std::cerr << "\rFA192    ";
    Ciphertext gin192 = gout184[1] + 1 * ct_data91 + 1 * ct_data123;
    std::vector<Ciphertext> gout192 = ctx.eval_lut_amortized(&gin192, decomp);

    std::cerr << "\rFA193    ";
    Ciphertext gin193 = gout188[1] + 1 * gout176[0] + 1 * gout180[0];
    std::vector<Ciphertext> gout193 = ctx.eval_lut_amortized(&gin193, decomp);

    std::cerr << "\rFA194    ";
    Ciphertext gin194 = gout186[1] + 1 * gout179[0] + 1 * gout175[0];
    std::vector<Ciphertext> gout194 = ctx.eval_lut_amortized(&gin194, decomp);

    std::cerr << "\rFA195    ";
    Ciphertext gin195 = gout187[1] + 1 * ct_data156 + 1 * ct_data188;
    std::vector<Ciphertext> gout195 = ctx.eval_lut_amortized(&gin195, decomp);

    std::cerr << "\rFA196    ";
    Ciphertext gin196 = gout191[1] + 1 * gout166[0] + 1 * gout192[0];
    std::vector<Ciphertext> gout196 = ctx.eval_lut_amortized(&gin196, decomp);

    std::cerr << "\rFA197    ";
    Ciphertext gin197 = gout190[1] + 1 * ct_data221 + 1 * ct_data253;
    std::vector<Ciphertext> gout197 = ctx.eval_lut_amortized(&gin197, decomp);

    std::cerr << "\rFA198    ";
    Ciphertext gin198 = gout192[1] + 1 * ct_data92 + 1 * ct_data124;
    std::vector<Ciphertext> gout198 = ctx.eval_lut_amortized(&gin198, decomp);

    std::cerr << "\rFA199    ";
    Ciphertext gin199 = gout195[1] + 1 * ct_data157 + 1 * ct_data189;
    std::vector<Ciphertext> gout199 = ctx.eval_lut_amortized(&gin199, decomp);

    std::cerr << "\rFA200    ";
    Ciphertext gin200 = gout197[1] + 1 * ct_data222 + 1 * ct_data254;
    std::vector<Ciphertext> gout200 = ctx.eval_lut_amortized(&gin200, decomp);

    std::cerr << "\rFA201    ";
    Ciphertext gin201 = gout194[1] + 1 * gout187[0] + 1 * gout183[0];
    std::vector<Ciphertext> gout201 = ctx.eval_lut_amortized(&gin201, decomp);

    std::cerr << "\rFA202    ";
    Ciphertext gin202 = gout193[1] + 1 * gout185[0] + 1 * gout186[0];
    std::vector<Ciphertext> gout202 = ctx.eval_lut_amortized(&gin202, decomp);

    std::cerr << "\rFA203    ";
    Ciphertext gin203 = gout198[1] + 1 * ct_data93 + 1 * ct_data125;
    std::vector<Ciphertext> gout203 = ctx.eval_lut_amortized(&gin203, decomp);

    std::cerr << "\rFA204    ";
    Ciphertext gin204 = gout196[1] + 1 * gout177[0] + 1 * gout198[0];
    std::vector<Ciphertext> gout204 = ctx.eval_lut_amortized(&gin204, decomp);

    std::cerr << "\rFA205    ";
    Ciphertext gin205 = gout199[1] + 1 * ct_data158 + 1 * ct_data190;
    std::vector<Ciphertext> gout205 = ctx.eval_lut_amortized(&gin205, decomp);

    std::cerr << "\rFA206    ";
    Ciphertext gin206 = gout201[1] + 1 * gout195[0] + 1 * gout190[0];
    std::vector<Ciphertext> gout206 = ctx.eval_lut_amortized(&gin206, decomp);

    std::cerr << "\rFA207    ";
    Ciphertext gin207 = gout202[1] + 1 * gout191[0] + 1 * gout194[0];
    std::vector<Ciphertext> gout207 = ctx.eval_lut_amortized(&gin207, decomp);

    std::cerr << "\rFA208    ";
    Ciphertext gin208 = gout203[1] + 1 * ct_data94 + 1 * ct_data126;
    std::vector<Ciphertext> gout208 = ctx.eval_lut_amortized(&gin208, decomp);

    std::cerr << "\rFA209    ";
    Ciphertext gin209 = gout204[1] + 1 * gout182[0] + 1 * gout203[0];
    std::vector<Ciphertext> gout209 = ctx.eval_lut_amortized(&gin209, decomp);

    std::cerr << "\rFA210    ";
    Ciphertext gin210 = gout206[1] + 1 * gout199[0] + 1 * gout197[0];
    std::vector<Ciphertext> gout210 = ctx.eval_lut_amortized(&gin210, decomp);

    std::cerr << "\rFA211    ";
    Ciphertext gin211 = gout207[1] + 1 * gout196[0] + 1 * gout201[0];
    std::vector<Ciphertext> gout211 = ctx.eval_lut_amortized(&gin211, decomp);

    std::cerr << "\rFA212    ";
    Ciphertext gin212 = gout209[1] + 1 * gout189[0] + 1 * gout208[0];
    std::vector<Ciphertext> gout212 = ctx.eval_lut_amortized(&gin212, decomp);

    std::cerr << "\rFA213    ";
    Ciphertext gin213 = gout210[1] + 1 * gout205[0] + 1 * gout200[0];
    std::vector<Ciphertext> gout213 = ctx.eval_lut_amortized(&gin213, decomp);

    std::cerr << "\rFA214    ";
    Ciphertext gin214 = gout211[1] + 1 * gout204[0] + 1 * gout206[0];
    std::vector<Ciphertext> gout214 = ctx.eval_lut_amortized(&gin214, decomp);

    std::cerr << "\rFA215    ";
    Ciphertext gin215 = gout214[1] + 1 * gout209[0] + 1 * gout210[0];
    std::vector<Ciphertext> gout215 = ctx.eval_lut_amortized(&gin215, decomp);

    std::cerr << "\rFA216    ";
    Ciphertext gin216 = gout215[1] + 1 * gout212[0] + 1 * gout213[0];
    std::vector<Ciphertext> gout216 = ctx.eval_lut_amortized(&gin216, decomp);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(0); /* out0 */
    test_out.push_back(ctx.decrypt(&gout18[0])); /* out1 */
    test_out.push_back(ctx.decrypt(&gout23[0])); /* out2 */
    test_out.push_back(ctx.decrypt(&gout34[0])); /* out3 */
    test_out.push_back(ctx.decrypt(&gout42[0])); /* out4 */
    test_out.push_back(ctx.decrypt(&gout47[0])); /* out5 */
    test_out.push_back(ctx.decrypt(&gout55[0])); /* out6 */
    test_out.push_back(ctx.decrypt(&gout61[0])); /* out7 */
    test_out.push_back(ctx.decrypt(&gout70[0])); /* out8 */
    test_out.push_back(ctx.decrypt(&gout78[0])); /* out9 */
    test_out.push_back(ctx.decrypt(&gout84[0])); /* out10 */
    test_out.push_back(ctx.decrypt(&gout92[0])); /* out11 */
    test_out.push_back(ctx.decrypt(&gout102[0])); /* out12 */
    test_out.push_back(ctx.decrypt(&gout116[0])); /* out13 */
    test_out.push_back(ctx.decrypt(&gout124[0])); /* out14 */
    test_out.push_back(ctx.decrypt(&gout133[0])); /* out15 */
    test_out.push_back(ctx.decrypt(&gout141[0])); /* out16 */
    test_out.push_back(ctx.decrypt(&gout147[0])); /* out17 */
    test_out.push_back(ctx.decrypt(&gout156[0])); /* out18 */
    test_out.push_back(ctx.decrypt(&gout163[0])); /* out19 */
    test_out.push_back(ctx.decrypt(&gout169[0])); /* out20 */
    test_out.push_back(ctx.decrypt(&gout171[0])); /* out21 */
    test_out.push_back(ctx.decrypt(&gout174[0])); /* out22 */
    test_out.push_back(ctx.decrypt(&gout181[0])); /* out23 */
    test_out.push_back(ctx.decrypt(&gout188[0])); /* out24 */
    test_out.push_back(ctx.decrypt(&gout193[0])); /* out25 */
    test_out.push_back(ctx.decrypt(&gout202[0])); /* out26 */
    test_out.push_back(ctx.decrypt(&gout207[0])); /* out27 */
    test_out.push_back(ctx.decrypt(&gout211[0])); /* out28 */
    test_out.push_back(ctx.decrypt(&gout214[0])); /* out29 */
    test_out.push_back(ctx.decrypt(&gout215[0])); /* out30 */
    test_out.push_back(ctx.decrypt(&gout216[0])); /* out31 */
    return test_out;
}

static void
BM_structs_3d_lut2fa(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(tfhe_11_NTT);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(4);

    for (auto _ : state) {
        test_structs_3d_lut2fa(ctx);
    }
}

BENCHMARK(BM_structs_3d_lut2fa)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
