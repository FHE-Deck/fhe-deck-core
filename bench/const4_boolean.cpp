#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_const4_boolean(FHEContext& ctx, uint8_t a = 0)
{
    Ciphertext ct_a1 = ctx.encrypt_public((a >> 0) & 1);
    Ciphertext ct_a2 = ctx.encrypt_public((a >> 1) & 1);
    Ciphertext ct_a3 = ctx.encrypt_public((a >> 2) & 1);

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

    std::cerr << "\rINV0   ";
    Ciphertext gout0 = 1 - ct_a1;

    std::cerr << "\rLUT1   ";
    Ciphertext gin1 = 2 * ct_a1 + ct_a2;
    Ciphertext gout1 = ctx.eval_lut(&gin1, nand2);
    std::cerr << "\rINV2   ";
    Ciphertext gout2 = 1 - ct_a3;

    std::cerr << "\rLUT3   ";
    Ciphertext gin3 = 2 * ct_a1 + ct_a2;
    Ciphertext gout3 = ctx.eval_lut(&gin3, xor2);
    std::cerr << "\rLUT4   ";
    Ciphertext gin4 = 2 * gout2 + gout1;
    Ciphertext gout4 = ctx.eval_lut(&gin4, xnor2);
    std::cerr << "\rLUT5   ";
    Ciphertext gin5 = 2 * gout2 + gout1;
    Ciphertext gout5 = ctx.eval_lut(&gin5, nand2);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(ctx.decrypt(&gout0)); /* out1 */
    test_out.push_back(ctx.decrypt(&gout3)); /* out2 */
    test_out.push_back(ctx.decrypt(&gout4)); /* out3 */
    test_out.push_back(ctx.decrypt(&gout5)); /* out4 */
    return test_out;
}

static void
BM_const4_boolean(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(tfhe_11_NTT);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(4);

    for (auto _ : state) {
        test_const4_boolean(ctx);
    }
}

BENCHMARK(BM_const4_boolean)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
