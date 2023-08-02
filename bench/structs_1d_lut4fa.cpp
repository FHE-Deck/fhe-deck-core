#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_structs_1d_lut4fa(FHEContext& ctx, uint64_t data = 0)
{
    Ciphertext ct_data0 = ctx.encrypt_public((data >> 0) & 1);
    Ciphertext ct_data1 = ctx.encrypt_public((data >> 1) & 1);
    Ciphertext ct_data2 = ctx.encrypt_public((data >> 2) & 1);
    Ciphertext ct_data3 = ctx.encrypt_public((data >> 3) & 1);
    Ciphertext ct_data4 = ctx.encrypt_public((data >> 4) & 1);
    Ciphertext ct_data5 = ctx.encrypt_public((data >> 5) & 1);
    Ciphertext ct_data6 = ctx.encrypt_public((data >> 6) & 1);
    Ciphertext ct_data7 = ctx.encrypt_public((data >> 7) & 1);
    Ciphertext ct_data8 = ctx.encrypt_public((data >> 8) & 1);
    Ciphertext ct_data9 = ctx.encrypt_public((data >> 9) & 1);
    Ciphertext ct_data10 = ctx.encrypt_public((data >> 10) & 1);
    Ciphertext ct_data11 = ctx.encrypt_public((data >> 11) & 1);
    Ciphertext ct_data12 = ctx.encrypt_public((data >> 12) & 1);
    Ciphertext ct_data13 = ctx.encrypt_public((data >> 13) & 1);
    Ciphertext ct_data14 = ctx.encrypt_public((data >> 14) & 1);
    Ciphertext ct_data15 = ctx.encrypt_public((data >> 15) & 1);
    Ciphertext ct_data16 = ctx.encrypt_public((data >> 16) & 1);
    Ciphertext ct_data17 = ctx.encrypt_public((data >> 17) & 1);
    Ciphertext ct_data18 = ctx.encrypt_public((data >> 18) & 1);
    Ciphertext ct_data19 = ctx.encrypt_public((data >> 19) & 1);
    Ciphertext ct_data20 = ctx.encrypt_public((data >> 20) & 1);
    Ciphertext ct_data21 = ctx.encrypt_public((data >> 21) & 1);
    Ciphertext ct_data22 = ctx.encrypt_public((data >> 22) & 1);
    Ciphertext ct_data23 = ctx.encrypt_public((data >> 23) & 1);
    Ciphertext ct_data24 = ctx.encrypt_public((data >> 24) & 1);
    Ciphertext ct_data25 = ctx.encrypt_public((data >> 25) & 1);
    Ciphertext ct_data26 = ctx.encrypt_public((data >> 26) & 1);
    Ciphertext ct_data27 = ctx.encrypt_public((data >> 27) & 1);
    Ciphertext ct_data28 = ctx.encrypt_public((data >> 28) & 1);
    Ciphertext ct_data29 = ctx.encrypt_public((data >> 29) & 1);
    Ciphertext ct_data30 = ctx.encrypt_public((data >> 30) & 1);
    Ciphertext ct_data32 = ctx.encrypt_public((data >> 31) & 1);
    Ciphertext ct_data33 = ctx.encrypt_public((data >> 32) & 1);
    Ciphertext ct_data34 = ctx.encrypt_public((data >> 33) & 1);
    Ciphertext ct_data35 = ctx.encrypt_public((data >> 34) & 1);
    Ciphertext ct_data36 = ctx.encrypt_public((data >> 35) & 1);
    Ciphertext ct_data37 = ctx.encrypt_public((data >> 36) & 1);
    Ciphertext ct_data38 = ctx.encrypt_public((data >> 37) & 1);
    Ciphertext ct_data39 = ctx.encrypt_public((data >> 38) & 1);
    Ciphertext ct_data40 = ctx.encrypt_public((data >> 39) & 1);
    Ciphertext ct_data41 = ctx.encrypt_public((data >> 40) & 1);
    Ciphertext ct_data42 = ctx.encrypt_public((data >> 41) & 1);
    Ciphertext ct_data43 = ctx.encrypt_public((data >> 42) & 1);
    Ciphertext ct_data44 = ctx.encrypt_public((data >> 43) & 1);
    Ciphertext ct_data45 = ctx.encrypt_public((data >> 44) & 1);
    Ciphertext ct_data46 = ctx.encrypt_public((data >> 45) & 1);
    Ciphertext ct_data47 = ctx.encrypt_public((data >> 46) & 1);
    Ciphertext ct_data48 = ctx.encrypt_public((data >> 47) & 1);
    Ciphertext ct_data49 = ctx.encrypt_public((data >> 48) & 1);
    Ciphertext ct_data50 = ctx.encrypt_public((data >> 49) & 1);
    Ciphertext ct_data51 = ctx.encrypt_public((data >> 50) & 1);
    Ciphertext ct_data52 = ctx.encrypt_public((data >> 51) & 1);
    Ciphertext ct_data53 = ctx.encrypt_public((data >> 52) & 1);
    Ciphertext ct_data54 = ctx.encrypt_public((data >> 53) & 1);
    Ciphertext ct_data55 = ctx.encrypt_public((data >> 54) & 1);
    Ciphertext ct_data56 = ctx.encrypt_public((data >> 55) & 1);
    Ciphertext ct_data57 = ctx.encrypt_public((data >> 56) & 1);
    Ciphertext ct_data58 = ctx.encrypt_public((data >> 57) & 1);
    Ciphertext ct_data59 = ctx.encrypt_public((data >> 58) & 1);
    Ciphertext ct_data60 = ctx.encrypt_public((data >> 59) & 1);
    Ciphertext ct_data61 = ctx.encrypt_public((data >> 60) & 1);
    Ciphertext ct_data62 = ctx.encrypt_public((data >> 61) & 1);

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
    Ciphertext gin0 = 0 + 1 * ct_data0 + 2 * ct_data1 + 4 * ct_data2 + 1 * ct_data32 + 2 * ct_data33 + 4 * ct_data34;
    std::vector<Ciphertext> gout0 = ctx.eval_lut_amortized(&gin0, decomp);

    std::cerr << "\rFA1    ";
    Ciphertext gin1 = gout0[3] + 1 * ct_data3 + 2 * ct_data4 + 4 * ct_data5 + 1 * ct_data35 + 2 * ct_data36 + 4 * ct_data37;
    std::vector<Ciphertext> gout1 = ctx.eval_lut_amortized(&gin1, decomp);

    std::cerr << "\rFA2    ";
    Ciphertext gin2 = gout1[3] + 1 * ct_data6 + 2 * ct_data7 + 4 * ct_data8 + 1 * ct_data38 + 2 * ct_data39 + 4 * ct_data40;
    std::vector<Ciphertext> gout2 = ctx.eval_lut_amortized(&gin2, decomp);

    std::cerr << "\rFA3    ";
    Ciphertext gin3 = gout2[3] + 1 * ct_data9 + 2 * ct_data10 + 4 * ct_data11 + 1 * ct_data41 + 2 * ct_data42 + 4 * ct_data43;
    std::vector<Ciphertext> gout3 = ctx.eval_lut_amortized(&gin3, decomp);

    std::cerr << "\rFA4    ";
    Ciphertext gin4 = gout3[3] + 1 * ct_data12 + 2 * ct_data13 + 4 * ct_data14 + 1 * ct_data44 + 2 * ct_data45 + 4 * ct_data46;
    std::vector<Ciphertext> gout4 = ctx.eval_lut_amortized(&gin4, decomp);

    std::cerr << "\rFA5    ";
    Ciphertext gin5 = gout4[3] + 1 * ct_data15 + 2 * ct_data16 + 4 * ct_data17 + 1 * ct_data47 + 2 * ct_data48 + 4 * ct_data49;
    std::vector<Ciphertext> gout5 = ctx.eval_lut_amortized(&gin5, decomp);

    std::cerr << "\rFA6    ";
    Ciphertext gin6 = gout5[3] + 1 * ct_data18 + 2 * ct_data19 + 4 * ct_data20 + 1 * ct_data50 + 2 * ct_data51 + 4 * ct_data52;
    std::vector<Ciphertext> gout6 = ctx.eval_lut_amortized(&gin6, decomp);

    std::cerr << "\rFA7    ";
    Ciphertext gin7 = gout6[3] + 1 * ct_data21 + 2 * ct_data22 + 4 * ct_data23 + 1 * ct_data53 + 2 * ct_data54 + 4 * ct_data55;
    std::vector<Ciphertext> gout7 = ctx.eval_lut_amortized(&gin7, decomp);

    std::cerr << "\rFA8    ";
    Ciphertext gin8 = gout7[3] + 1 * ct_data24 + 2 * ct_data25 + 4 * ct_data26 + 1 * ct_data56 + 2 * ct_data57 + 4 * ct_data58;
    std::vector<Ciphertext> gout8 = ctx.eval_lut_amortized(&gin8, decomp);

    std::cerr << "\rFA9    ";
    Ciphertext gin9 = gout8[3] + 1 * ct_data27 + 2 * ct_data28 + 4 * ct_data29 + 1 * ct_data59 + 2 * ct_data60 + 4 * ct_data61;
    std::vector<Ciphertext> gout9 = ctx.eval_lut_amortized(&gin9, decomp);

    std::cerr << "\rFA10    ";
    Ciphertext gin10 = gout9[3] + 1 * ct_data30 + 1 * ct_data62;
    std::vector<Ciphertext> gout10 = ctx.eval_lut_amortized(&gin10, decomp);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(0); /* out0 */
    test_out.push_back(ctx.decrypt(&gout0[0])); /* out1 */
    test_out.push_back(ctx.decrypt(&gout0[1])); /* out2 */
    test_out.push_back(ctx.decrypt(&gout0[2])); /* out3 */
    test_out.push_back(ctx.decrypt(&gout1[0])); /* out4 */
    test_out.push_back(ctx.decrypt(&gout1[1])); /* out5 */
    test_out.push_back(ctx.decrypt(&gout1[2])); /* out6 */
    test_out.push_back(ctx.decrypt(&gout2[0])); /* out7 */
    test_out.push_back(ctx.decrypt(&gout2[1])); /* out8 */
    test_out.push_back(ctx.decrypt(&gout2[2])); /* out9 */
    test_out.push_back(ctx.decrypt(&gout3[0])); /* out10 */
    test_out.push_back(ctx.decrypt(&gout3[1])); /* out11 */
    test_out.push_back(ctx.decrypt(&gout3[2])); /* out12 */
    test_out.push_back(ctx.decrypt(&gout4[0])); /* out13 */
    test_out.push_back(ctx.decrypt(&gout4[1])); /* out14 */
    test_out.push_back(ctx.decrypt(&gout4[2])); /* out15 */
    test_out.push_back(ctx.decrypt(&gout5[0])); /* out16 */
    test_out.push_back(ctx.decrypt(&gout5[1])); /* out17 */
    test_out.push_back(ctx.decrypt(&gout5[2])); /* out18 */
    test_out.push_back(ctx.decrypt(&gout6[0])); /* out19 */
    test_out.push_back(ctx.decrypt(&gout6[1])); /* out20 */
    test_out.push_back(ctx.decrypt(&gout6[2])); /* out21 */
    test_out.push_back(ctx.decrypt(&gout7[0])); /* out22 */
    test_out.push_back(ctx.decrypt(&gout7[1])); /* out23 */
    test_out.push_back(ctx.decrypt(&gout7[2])); /* out24 */
    test_out.push_back(ctx.decrypt(&gout8[0])); /* out25 */
    test_out.push_back(ctx.decrypt(&gout8[1])); /* out26 */
    test_out.push_back(ctx.decrypt(&gout8[2])); /* out27 */
    test_out.push_back(ctx.decrypt(&gout9[0])); /* out28 */
    test_out.push_back(ctx.decrypt(&gout9[1])); /* out29 */
    test_out.push_back(ctx.decrypt(&gout9[2])); /* out30 */
    test_out.push_back(ctx.decrypt(&gout10[0])); /* out31 */
    return test_out;
}

static void
BM_structs_1d_lut4fa(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(tfhe_12_NTT_amortized);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(16);

    for (auto _ : state) {
        test_structs_1d_lut4fa(ctx);
    }
}

BENCHMARK(BM_structs_1d_lut4fa)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
