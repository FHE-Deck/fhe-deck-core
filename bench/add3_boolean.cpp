#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_add3_boolean(FHEContext& ctx, uint8_t a = 0, uint8_t b = 0)
{
    Ciphertext ct_a0 = ctx.encrypt_public((a >> 0) & 1);
    Ciphertext ct_a1 = ctx.encrypt_public((a >> 1) & 1);
    Ciphertext ct_a2 = ctx.encrypt_public((a >> 2) & 1);
    Ciphertext ct_b0 = ctx.encrypt_public((b >> 0) & 1);
    Ciphertext ct_b1 = ctx.encrypt_public((b >> 1) & 1);
    Ciphertext ct_b2 = ctx.encrypt_public((b >> 2) & 1);

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
    Ciphertext gin0 = 2 * ct_a0 + ct_b0;
    Ciphertext gout0 = ctx.eval_lut(&gin0, xor2);
    std::cerr << "\rLUT1   ";
    Ciphertext gin1 = 2 * ct_a2 + ct_b2;
    Ciphertext gout1 = ctx.eval_lut(&gin1, nand2);
    std::cerr << "\rLUT2   ";
    Ciphertext gin2 = 2 * ct_a2 + ct_b2;
    Ciphertext gout2 = ctx.eval_lut(&gin2, xor2);
    std::cerr << "\rLUT3   ";
    Ciphertext gin3 = 2 * ct_a1 + ct_b1;
    Ciphertext gout3 = ctx.eval_lut(&gin3, xor2);
    std::cerr << "\rLUT4   ";
    Ciphertext gin4 = 2 * ct_a0 + ct_b0;
    Ciphertext gout4 = ctx.eval_lut(&gin4, and2);
    std::cerr << "\rLUT5   ";
    Ciphertext gin5 = 2 * ct_a1 + ct_b1;
    Ciphertext gout5 = ctx.eval_lut(&gin5, nand2);
    std::cerr << "\rLUT6   ";
    Ciphertext gin6 = 2 * gout4 + gout3;
    Ciphertext gout6 = ctx.eval_lut(&gin6, nand2);
    std::cerr << "\rLUT7   ";
    Ciphertext gin7 = 2 * gout4 + gout3;
    Ciphertext gout7 = ctx.eval_lut(&gin7, xor2);
    std::cerr << "\rLUT8   ";
    Ciphertext gin8 = 2 * gout5 + gout6;
    Ciphertext gout8 = ctx.eval_lut(&gin8, nand2);
    std::cerr << "\rLUT9   ";
    Ciphertext gin9 = 2 * gout8 + gout2;
    Ciphertext gout9 = ctx.eval_lut(&gin9, xor2);
    std::cerr << "\rLUT10   ";
    Ciphertext gin10 = 2 * gout8 + gout2;
    Ciphertext gout10 = ctx.eval_lut(&gin10, nand2);
    std::cerr << "\rLUT11   ";
    Ciphertext gin11 = 2 * gout1 + gout10;
    Ciphertext gout11 = ctx.eval_lut(&gin11, nand2);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(ctx.decrypt(&gout0)); /* out0 */
    test_out.push_back(ctx.decrypt(&gout7)); /* out1 */
    test_out.push_back(ctx.decrypt(&gout9)); /* out2 */
    test_out.push_back(ctx.decrypt(&gout11)); /* out3 */
    return test_out;
}

static void
BM_add3_boolean(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(tfhe_11_NTT);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(4);

    for (auto _ : state) {
        test_add3_boolean(ctx);
    }
}

BENCHMARK(BM_add3_boolean)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
