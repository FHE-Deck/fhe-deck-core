#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_relu_boolean(FHEContext& ctx, uint16_t x = 0)
{
    Ciphertext ct_x0 = ctx.encrypt_public((x >> 0) & 1);
    Ciphertext ct_x1 = ctx.encrypt_public((x >> 1) & 1);
    Ciphertext ct_x2 = ctx.encrypt_public((x >> 2) & 1);
    Ciphertext ct_x3 = ctx.encrypt_public((x >> 3) & 1);
    Ciphertext ct_x4 = ctx.encrypt_public((x >> 4) & 1);
    Ciphertext ct_x5 = ctx.encrypt_public((x >> 5) & 1);
    Ciphertext ct_x6 = ctx.encrypt_public((x >> 6) & 1);
    Ciphertext ct_x7 = ctx.encrypt_public((x >> 7) & 1);
    Ciphertext ct_x8 = ctx.encrypt_public((x >> 8) & 1);
    Ciphertext ct_x9 = ctx.encrypt_public((x >> 9) & 1);
    Ciphertext ct_x10 = ctx.encrypt_public((x >> 10) & 1);
    Ciphertext ct_x11 = ctx.encrypt_public((x >> 11) & 1);
    Ciphertext ct_x12 = ctx.encrypt_public((x >> 12) & 1);
    Ciphertext ct_x13 = ctx.encrypt_public((x >> 13) & 1);
    Ciphertext ct_x14 = ctx.encrypt_public((x >> 14) & 1);
    Ciphertext ct_x15 = ctx.encrypt_public((x >> 15) & 1);

    auto fand2 = [](long i, long t) -> long {
        switch (i) {
            case 0:  return 0;
            case 1:  return 0;
            case 2:  return 0;
            case 3:  return 1;
            default: assert(0);
        }
    };
    RotationPoly and2 = ctx.genrate_lut(fand2);

    auto fnand2 = [](long i, long t) -> long {
        switch (i) {
            case 0:  return 1;
            case 1:  return 1;
            case 2:  return 1;
            case 3:  return 0;
            default: assert(0);
        }
    };
    RotationPoly nand2 = ctx.genrate_lut(fnand2);

    auto for2 = [](long i, long t) -> long {
        switch (i) {
            case 0:  return 0;
            case 1:  return 1;
            case 2:  return 1;
            case 3:  return 1;
            default: assert(0);
        }
    };
    RotationPoly or2 = ctx.genrate_lut(for2);

    auto fnor2 = [](long i, long t) -> long {
        switch (i) {
            case 0:  return 1;
            case 1:  return 0;
            case 2:  return 0;
            case 3:  return 0;
            default: assert(0);
        }
    };
    RotationPoly nor2 = ctx.genrate_lut(fnor2);

    auto fxor2 = [](long i, long t) -> long {
        switch (i) {
            case 0:  return 0;
            case 1:  return 1;
            case 2:  return 1;
            case 3:  return 0;
            default: assert(0);
        }
    };
    RotationPoly xor2 = ctx.genrate_lut(fxor2);

    auto fxnor2 = [](long i, long t) -> long {
        switch (i) {
            case 0:  return 1;
            case 1:  return 0;
            case 2:  return 0;
            case 3:  return 1;
            default: assert(0);
        }
    };
    RotationPoly xnor2 = ctx.genrate_lut(fxnor2);

    std::cerr << "\rLUT0   ";
    Ciphertext gin0 = 2 * (1 - ct_x15) + ct_x0;
    Ciphertext gout0 = ctx.eval_lut(&gin0, and2);
    std::cerr << "\rINV1   ";
    Ciphertext gout1 = 1 - ct_x15;

    std::cerr << "\rLUT2   ";
    Ciphertext gin2 = 2 * ct_x5 + ct_x6;
    Ciphertext gout2 = ctx.eval_lut(&gin2, nor2);
    std::cerr << "\rLUT3   ";
    Ciphertext gin3 = 2 * (1 - ct_x15) + ct_x4;
    Ciphertext gout3 = ctx.eval_lut(&gin3, and2);
    std::cerr << "\rLUT4   ";
    Ciphertext gin4 = 2 * ct_x4 + ct_x7;
    Ciphertext gout4 = ctx.eval_lut(&gin4, nor2);
    std::cerr << "\rLUT5   ";
    Ciphertext gin5 = 2 * ct_x0 + ct_x3;
    Ciphertext gout5 = ctx.eval_lut(&gin5, nor2);
    std::cerr << "\rINV6   ";
    Ciphertext gout6 = 1 - ct_x9;

    std::cerr << "\rLUT7   ";
    Ciphertext gin7 = 2 * ct_x13 + ct_x14;
    Ciphertext gout7 = ctx.eval_lut(&gin7, nor2);
    std::cerr << "\rLUT8   ";
    Ciphertext gin8 = 2 * (1 - ct_x15) + ct_x5;
    Ciphertext gout8 = ctx.eval_lut(&gin8, and2);
    std::cerr << "\rLUT9   ";
    Ciphertext gin9 = 2 * (1 - ct_x15) + ct_x6;
    Ciphertext gout9 = ctx.eval_lut(&gin9, and2);
    std::cerr << "\rLUT10   ";
    Ciphertext gin10 = 2 * ct_x1 + ct_x2;
    Ciphertext gout10 = ctx.eval_lut(&gin10, nor2);
    std::cerr << "\rLUT11   ";
    Ciphertext gin11 = 2 * (1 - ct_x15) + ct_x12;
    Ciphertext gout11 = ctx.eval_lut(&gin11, and2);
    std::cerr << "\rLUT12   ";
    Ciphertext gin12 = 2 * ct_x11 + ct_x12;
    Ciphertext gout12 = ctx.eval_lut(&gin12, nor2);
    std::cerr << "\rLUT13   ";
    Ciphertext gin13 = 2 * (1 - ct_x15) + ct_x9;
    Ciphertext gout13 = ctx.eval_lut(&gin13, and2);
    std::cerr << "\rLUT14   ";
    Ciphertext gin14 = 2 * ct_x8 + ct_x10;
    Ciphertext gout14 = ctx.eval_lut(&gin14, nor2);
    std::cerr << "\rLUT15   ";
    Ciphertext gin15 = 2 * (1 - ct_x15) + ct_x7;
    Ciphertext gout15 = ctx.eval_lut(&gin15, and2);
    std::cerr << "\rLUT16   ";
    Ciphertext gin16 = 2 * gout10 + gout5;
    Ciphertext gout16 = ctx.eval_lut(&gin16, and2);
    std::cerr << "\rLUT17   ";
    Ciphertext gin17 = 2 * gout12 + gout7;
    Ciphertext gout17 = ctx.eval_lut(&gin17, and2);
    std::cerr << "\rLUT18   ";
    Ciphertext gin18 = 2 * gout6 + gout2;
    Ciphertext gout18 = ctx.eval_lut(&gin18, and2);
    std::cerr << "\rLUT19   ";
    Ciphertext gin19 = 2 * gout14 + gout4;
    Ciphertext gout19 = ctx.eval_lut(&gin19, and2);
    std::cerr << "\rLUT20   ";
    Ciphertext gin20 = 2 * gout17 + gout18;
    Ciphertext gout20 = ctx.eval_lut(&gin20, and2);
    std::cerr << "\rLUT21   ";
    Ciphertext gin21 = 2 * gout16 + gout19;
    Ciphertext gout21 = ctx.eval_lut(&gin21, and2);
    std::cerr << "\rLUT22   ";
    Ciphertext gin22 = 2 * gout20 + gout21;
    Ciphertext gout22 = ctx.eval_lut(&gin22, nand2);
    std::cerr << "\rLUT23   ";
    Ciphertext gin23 = 2 * gout1 + gout22;
    Ciphertext gout23 = ctx.eval_lut(&gin23, and2);
    std::cerr << "\rLUT24   ";
    Ciphertext gin24 = 2 * ct_x11 + gout23;
    Ciphertext gout24 = ctx.eval_lut(&gin24, and2);
    std::cerr << "\rLUT25   ";
    Ciphertext gin25 = 2 * ct_x8 + gout23;
    Ciphertext gout25 = ctx.eval_lut(&gin25, and2);
    std::cerr << "\rLUT26   ";
    Ciphertext gin26 = 2 * ct_x10 + gout23;
    Ciphertext gout26 = ctx.eval_lut(&gin26, and2);
    std::cerr << "\rLUT27   ";
    Ciphertext gin27 = 2 * ct_x13 + gout23;
    Ciphertext gout27 = ctx.eval_lut(&gin27, and2);
    std::cerr << "\rLUT28   ";
    Ciphertext gin28 = 2 * ct_x3 + gout23;
    Ciphertext gout28 = ctx.eval_lut(&gin28, and2);
    std::cerr << "\rLUT29   ";
    Ciphertext gin29 = 2 * ct_x1 + gout23;
    Ciphertext gout29 = ctx.eval_lut(&gin29, and2);
    std::cerr << "\rLUT30   ";
    Ciphertext gin30 = 2 * ct_x14 + gout23;
    Ciphertext gout30 = ctx.eval_lut(&gin30, and2);
    std::cerr << "\rLUT31   ";
    Ciphertext gin31 = 2 * ct_x2 + gout23;
    Ciphertext gout31 = ctx.eval_lut(&gin31, and2);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(ctx.decrypt(&gout0)); /* out0 */
    test_out.push_back(ctx.decrypt(&gout29)); /* out1 */
    test_out.push_back(ctx.decrypt(&gout31)); /* out2 */
    test_out.push_back(ctx.decrypt(&gout28)); /* out3 */
    test_out.push_back(ctx.decrypt(&gout3)); /* out4 */
    test_out.push_back(ctx.decrypt(&gout8)); /* out5 */
    test_out.push_back(ctx.decrypt(&gout9)); /* out6 */
    test_out.push_back(ctx.decrypt(&gout15)); /* out7 */
    test_out.push_back(ctx.decrypt(&gout25)); /* out8 */
    test_out.push_back(ctx.decrypt(&gout13)); /* out9 */
    test_out.push_back(ctx.decrypt(&gout26)); /* out10 */
    test_out.push_back(ctx.decrypt(&gout24)); /* out11 */
    test_out.push_back(ctx.decrypt(&gout11)); /* out12 */
    test_out.push_back(ctx.decrypt(&gout27)); /* out13 */
    test_out.push_back(ctx.decrypt(&gout30)); /* out14 */
    return test_out;
}

static void
BM_relu_boolean(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(tfhe_11_NTT);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(4);

    for (auto _ : state) {
        test_relu_boolean(ctx);
    }
}

BENCHMARK(BM_relu_boolean)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
