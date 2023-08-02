#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


static void
BM_lut_pt4_identity(benchmark::State &state)
{
    FHEContext ctx;
    ctx.generate_context(rlwe_hom_acc_scheme_C_11_NTT);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(4);

    RotationPoly identity = ctx.genrate_lut([](long I) -> long {
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 2;
            case  3: return 3;
            default: assert(0);
        };
    });

    for (auto _ : state) {
        state.PauseTiming();
        Ciphertext ct = ctx.encrypt_public(0);

        state.ResumeTiming();
        auto eval = ctx.eval_lut(&ct, identity);
    }
}

static void
BM_lut_pt4_decomp(benchmark::State &state)
{
    FHEContext ctx;
    ctx.generate_context(rlwe_hom_acc_scheme_C_11_NTT);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(4);

    RotationPoly decomp0 = ctx.genrate_lut([](long I) -> long {
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    });
    RotationPoly decomp1 = ctx.genrate_lut([](long I) -> long {
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            default: assert(0);
        };
    });

    for (auto _ : state) {
        state.PauseTiming();
        Ciphertext ct = ctx.encrypt_public(0);

        state.ResumeTiming();
        auto eval0 = ctx.eval_lut(&ct, decomp0);
        auto eval1 = ctx.eval_lut(&ct, decomp0);
    }
}

static void
BM_lut_amortized_pt4_identity(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(rlwe_hom_acc_scheme_C_11_NTT);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(4);

    std::vector<RotationPoly> identity;
    identity.push_back(ctx.genrate_lut([](long I) -> long {
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 2;
            case  3: return 3;
            default: assert(0);
        };
    }));

    for (auto _ : state) {
        state.PauseTiming();
        Ciphertext ct = ctx.encrypt_public(0);

        state.ResumeTiming();
        auto eval = ctx.eval_lut_amortized(&ct, identity);
    }
}

static void
BM_lut_amortized_pt4_decomp(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(rlwe_hom_acc_scheme_C_11_NTT);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(4);

    std::vector<RotationPoly> decomp;
    decomp.push_back(ctx.genrate_lut([](long I) -> long {
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            default: assert(0);
        };
    }));
    decomp.push_back(ctx.genrate_lut([](long I) -> long {
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            default: assert(0);
        };
    }));

    for (auto _ : state) {
        state.PauseTiming();
        Ciphertext ct = ctx.encrypt_public(0);

        state.ResumeTiming();
        auto eval = ctx.eval_lut_amortized(&ct, decomp);
    }
}

static void
BM_lut_amortized_pt8_identity(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(rlwe_hom_acc_scheme_C_11_NTT);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(8);

    std::vector<RotationPoly> identity;
    identity.push_back(ctx.genrate_lut([](long I) -> long {
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 2;
            case  3: return 3;
            case  4: return 4;
            case  5: return 5;
            case  6: return 6;
            case  7: return 7;
            default: assert(0);
        };
    }));

    for (auto _ : state) {
        state.PauseTiming();
        Ciphertext ct = ctx.encrypt_public(0);

        state.ResumeTiming();
        auto eval = ctx.eval_lut_amortized(&ct, identity);
    }
}

static void
BM_lut_amortized_pt8_decomp(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(rlwe_hom_acc_scheme_C_11_NTT);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(8);

    std::vector<RotationPoly> decomp;
    decomp.push_back(ctx.genrate_lut([](long I) -> long {
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
    }));
    decomp.push_back(ctx.genrate_lut([](long I) -> long {
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
    }));
    #if 0
    decomp.push_back(ctx.genrate_lut([](long I) -> long {
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
    }));
    #endif

    for (auto _ : state) {
        state.PauseTiming();
        Ciphertext ct = ctx.encrypt_public(0);

        state.ResumeTiming();
        auto eval = ctx.eval_lut_amortized(&ct, decomp);
    }
}

BENCHMARK(BM_lut_pt4_identity)->Unit(benchmark::kSecond);
BENCHMARK(BM_lut_pt4_decomp)->Unit(benchmark::kSecond);
BENCHMARK(BM_lut_amortized_pt4_identity)->Unit(benchmark::kSecond);
BENCHMARK(BM_lut_amortized_pt4_decomp)->Unit(benchmark::kSecond);
BENCHMARK(BM_lut_amortized_pt8_identity)->Unit(benchmark::kSecond);
BENCHMARK(BM_lut_amortized_pt8_decomp)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
