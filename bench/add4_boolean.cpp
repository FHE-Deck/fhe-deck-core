#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_add4_boolean(FHEContext& ctx, uint8_t a = 0, uint8_t b = 0)
{
    Ciphertext ct_a0 = ctx.encrypt_public((a >> 0) & 1);
    Ciphertext ct_a1 = ctx.encrypt_public((a >> 1) & 1);
    Ciphertext ct_a2 = ctx.encrypt_public((a >> 2) & 1);
    Ciphertext ct_a3 = ctx.encrypt_public((a >> 3) & 1);
    Ciphertext ct_b0 = ctx.encrypt_public((b >> 0) & 1);
    Ciphertext ct_b1 = ctx.encrypt_public((b >> 1) & 1);
    Ciphertext ct_b2 = ctx.encrypt_public((b >> 2) & 1);
    Ciphertext ct_b3 = ctx.encrypt_public((b >> 3) & 1);

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
    Ciphertext gin0 = 2 * ct_a1 + ct_b1;
    Ciphertext gout0 = ctx.eval_lut(&gin0, xor2);
    std::cerr << "\rLUT1   ";
    Ciphertext gin1 = 2 * ct_a3 + ct_b3;
    Ciphertext gout1 = ctx.eval_lut(&gin1, xor2);
    std::cerr << "\rLUT2   ";
    Ciphertext gin2 = 2 * ct_a0 + ct_b0;
    Ciphertext gout2 = ctx.eval_lut(&gin2, and2);
    std::cerr << "\rLUT3   ";
    Ciphertext gin3 = 2 * ct_a3 + ct_b3;
    Ciphertext gout3 = ctx.eval_lut(&gin3, nand2);
    std::cerr << "\rLUT4   ";
    Ciphertext gin4 = 2 * ct_a2 + ct_b2;
    Ciphertext gout4 = ctx.eval_lut(&gin4, nand2);
    std::cerr << "\rLUT5   ";
    Ciphertext gin5 = 2 * ct_a0 + ct_b0;
    Ciphertext gout5 = ctx.eval_lut(&gin5, xor2);
    std::cerr << "\rLUT6   ";
    Ciphertext gin6 = 2 * gout2 + gout0;
    Ciphertext gout6 = ctx.eval_lut(&gin6, xor2);
    std::cerr << "\rLUT7   ";
    Ciphertext gin7 = 2 * ct_a1 + ct_b1;
    Ciphertext gout7 = ctx.eval_lut(&gin7, nand2);
    std::cerr << "\rLUT8   ";
    Ciphertext gin8 = 2 * gout2 + gout0;
    Ciphertext gout8 = ctx.eval_lut(&gin8, nand2);
    std::cerr << "\rLUT9   ";
    Ciphertext gin9 = 2 * ct_a2 + ct_b2;
    Ciphertext gout9 = ctx.eval_lut(&gin9, xor2);
    std::cerr << "\rLUT10   ";
    Ciphertext gin10 = 2 * gout7 + gout8;
    Ciphertext gout10 = ctx.eval_lut(&gin10, nand2);
    std::cerr << "\rLUT11   ";
    Ciphertext gin11 = 2 * gout10 + gout9;
    Ciphertext gout11 = ctx.eval_lut(&gin11, nand2);
    std::cerr << "\rLUT12   ";
    Ciphertext gin12 = 2 * gout10 + gout9;
    Ciphertext gout12 = ctx.eval_lut(&gin12, xor2);
    std::cerr << "\rLUT13   ";
    Ciphertext gin13 = 2 * gout4 + gout11;
    Ciphertext gout13 = ctx.eval_lut(&gin13, nand2);
    std::cerr << "\rLUT14   ";
    Ciphertext gin14 = 2 * gout13 + gout1;
    Ciphertext gout14 = ctx.eval_lut(&gin14, nand2);
    std::cerr << "\rLUT15   ";
    Ciphertext gin15 = 2 * gout13 + gout1;
    Ciphertext gout15 = ctx.eval_lut(&gin15, xor2);
    std::cerr << "\rLUT16   ";
    Ciphertext gin16 = 2 * gout3 + gout14;
    Ciphertext gout16 = ctx.eval_lut(&gin16, nand2);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(ctx.decrypt(&gout5)); /* out0 */
    test_out.push_back(ctx.decrypt(&gout6)); /* out1 */
    test_out.push_back(ctx.decrypt(&gout12)); /* out2 */
    test_out.push_back(ctx.decrypt(&gout15)); /* out3 */
    test_out.push_back(ctx.decrypt(&gout16)); /* out4 */
    return test_out;
}

static void
BM_add4_boolean(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(tfhe_11_NTT);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(4);

    for (auto _ : state) {
        test_add4_boolean(ctx);
    }
}

BENCHMARK(BM_add4_boolean)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
