#include <bitset>
#include <cassert>
#include <iostream>

#include "fhe_context.h"

using namespace fhe_deck;

void
test_lut3(FHEContext& ctx)
{
    std::cout << "[+] Testing LUT3" << std::endl;

    auto bit0 = [](long m) -> long {
        return m & 1;
    };
    auto bit1 = [](long m) -> long {
        return (m >> 1) & 1;
    };
    auto bit2 = [](long m) -> long {
        return (m >> 2) & 1;
    };

    std::vector<HomomorphicAccumulator> lut;
    lut.push_back(ctx.genrate_lut(bit0));
    lut.push_back(ctx.genrate_lut(bit1));
    lut.push_back(ctx.genrate_lut(bit2));

    Ciphertext ct0 = ctx.encrypt_public(0);
    Ciphertext ct1 = ctx.encrypt_public(1);
    Ciphertext ct2 = ctx.encrypt_public(2);
    Ciphertext ct3 = ctx.encrypt_public(3);
    Ciphertext ct4 = ctx.encrypt_public(4);
    Ciphertext ct5 = ctx.encrypt_public(5);
    Ciphertext ct6 = ctx.encrypt_public(6);
    Ciphertext ct7 = ctx.encrypt_public(7);

    std::vector<Ciphertext> out = ctx.eval_lut_amortized(&ct0, lut);
    assert(ctx.decrypt(&out[0]) == 0);
    assert(ctx.decrypt(&out[1]) == 0);
    assert(ctx.decrypt(&out[2]) == 0);
    std::cout << "LUT3(0): OK." << std::endl;

    out = ctx.eval_lut_amortized(&ct1, lut);
    assert(ctx.decrypt(&out[0]) == 1);
    assert(ctx.decrypt(&out[1]) == 0);
    assert(ctx.decrypt(&out[2]) == 0);
    std::cout << "LUT3(1): OK." << std::endl;

    out = ctx.eval_lut_amortized(&ct2, lut);
    assert(ctx.decrypt(&out[0]) == 0);
    assert(ctx.decrypt(&out[1]) == 1);
    assert(ctx.decrypt(&out[2]) == 0);
    std::cout << "LUT3(2): OK." << std::endl;

    out = ctx.eval_lut_amortized(&ct3, lut);
    assert(ctx.decrypt(&out[0]) == 1);
    assert(ctx.decrypt(&out[1]) == 1);
    assert(ctx.decrypt(&out[2]) == 0);
    std::cout << "LUT3(3): OK." << std::endl;

    out = ctx.eval_lut_amortized(&ct4, lut);
    assert(ctx.decrypt(&out[0]) == 0);
    assert(ctx.decrypt(&out[1]) == 0);
    assert(ctx.decrypt(&out[2]) == 1);
    std::cout << "LUT3(4): OK." << std::endl;

    out = ctx.eval_lut_amortized(&ct5, lut);
    assert(ctx.decrypt(&out[0]) == 1);
    assert(ctx.decrypt(&out[1]) == 0);
    assert(ctx.decrypt(&out[2]) == 1);
    std::cout << "LUT3(5): OK." << std::endl;

    out = ctx.eval_lut_amortized(&ct6, lut);
    assert(ctx.decrypt(&out[0]) == 0);
    assert(ctx.decrypt(&out[1]) == 1);
    assert(ctx.decrypt(&out[2]) == 1);
    std::cout << "LUT3(6): OK." << std::endl;

    out = ctx.eval_lut_amortized(&ct7, lut);
    assert(ctx.decrypt(&out[0]) == 1);
    assert(ctx.decrypt(&out[1]) == 1);
    assert(ctx.decrypt(&out[2]) == 1);
    std::cout << "LUT3(7): OK." << std::endl;
}

void
test_lut4(FHEContext& ctx)
{
    std::cout << "[+] Testing LUT4" << std::endl;

    auto bit0 = [](long m) -> long {
        return m & 1;
    };
    auto bit1 = [](long m) -> long {
        return (m >> 1) & 1;
    };
    auto bit2 = [](long m) -> long {
        return (m >> 2) & 1;
    };
    auto bit3 = [](long m) -> long {
        return (m >> 3) & 1;
    };

    std::vector<HomomorphicAccumulator> lut;
    lut.push_back(ctx.genrate_lut(bit0));
    lut.push_back(ctx.genrate_lut(bit1));
    lut.push_back(ctx.genrate_lut(bit2));
    lut.push_back(ctx.genrate_lut(bit3));

    Ciphertext ct0 = ctx.encrypt_public(0);
    Ciphertext ct1 = ctx.encrypt_public(1);
    Ciphertext ct2 = ctx.encrypt_public(2);
    Ciphertext ct3 = ctx.encrypt_public(3);
    Ciphertext ct4 = ctx.encrypt_public(4);
    Ciphertext ct5 = ctx.encrypt_public(5);
    Ciphertext ct6 = ctx.encrypt_public(6);
    Ciphertext ct7 = ctx.encrypt_public(7);
    Ciphertext ct8 = ctx.encrypt_public(8);
    Ciphertext ct9 = ctx.encrypt_public(9);
    Ciphertext ctA = ctx.encrypt_public(10);
    Ciphertext ctB = ctx.encrypt_public(11);
    Ciphertext ctC = ctx.encrypt_public(12);
    Ciphertext ctD = ctx.encrypt_public(13);
    Ciphertext ctE = ctx.encrypt_public(14);
    Ciphertext ctF = ctx.encrypt_public(15);

    std::vector<Ciphertext> out = ctx.eval_lut_amortized(&ct0, lut);
    assert(ctx.decrypt(&out[0]) == 0);
    assert(ctx.decrypt(&out[1]) == 0);
    assert(ctx.decrypt(&out[2]) == 0);
    assert(ctx.decrypt(&out[3]) == 0);
    std::cout << "LUT4(0): OK." << std::endl;

    out = ctx.eval_lut_amortized(&ct1, lut);
    assert(ctx.decrypt(&out[0]) == 1);
    assert(ctx.decrypt(&out[1]) == 0);
    assert(ctx.decrypt(&out[2]) == 0);
    assert(ctx.decrypt(&out[3]) == 0);
    std::cout << "LUT4(1): OK." << std::endl;

    out = ctx.eval_lut_amortized(&ct2, lut);
    assert(ctx.decrypt(&out[0]) == 0);
    assert(ctx.decrypt(&out[1]) == 1);
    assert(ctx.decrypt(&out[2]) == 0);
    assert(ctx.decrypt(&out[3]) == 0);
    std::cout << "LUT4(2): OK." << std::endl;

    out = ctx.eval_lut_amortized(&ct3, lut);
    assert(ctx.decrypt(&out[0]) == 1);
    assert(ctx.decrypt(&out[1]) == 1);
    assert(ctx.decrypt(&out[2]) == 0);
    assert(ctx.decrypt(&out[3]) == 0);
    std::cout << "LUT4(3): OK." << std::endl;

    out = ctx.eval_lut_amortized(&ct4, lut);
    assert(ctx.decrypt(&out[0]) == 0);
    assert(ctx.decrypt(&out[1]) == 0);
    assert(ctx.decrypt(&out[2]) == 1);
    assert(ctx.decrypt(&out[3]) == 0);
    std::cout << "LUT4(4): OK." << std::endl;

    out = ctx.eval_lut_amortized(&ct5, lut);
    assert(ctx.decrypt(&out[0]) == 1);
    assert(ctx.decrypt(&out[1]) == 0);
    assert(ctx.decrypt(&out[2]) == 1);
    assert(ctx.decrypt(&out[3]) == 0);
    std::cout << "LUT4(5): OK." << std::endl;

    out = ctx.eval_lut_amortized(&ct6, lut);
    assert(ctx.decrypt(&out[0]) == 0);
    assert(ctx.decrypt(&out[1]) == 1);
    assert(ctx.decrypt(&out[2]) == 1);
    assert(ctx.decrypt(&out[3]) == 0);
    std::cout << "LUT4(6): OK." << std::endl;

    out = ctx.eval_lut_amortized(&ct7, lut);
    assert(ctx.decrypt(&out[0]) == 1);
    assert(ctx.decrypt(&out[1]) == 1);
    assert(ctx.decrypt(&out[2]) == 1);
    assert(ctx.decrypt(&out[3]) == 0);
    std::cout << "LUT4(7): OK." << std::endl;

    out = ctx.eval_lut_amortized(&ct8, lut);
    assert(ctx.decrypt(&out[0]) == 0);
    assert(ctx.decrypt(&out[1]) == 0);
    assert(ctx.decrypt(&out[2]) == 0);
    assert(ctx.decrypt(&out[3]) == 1);
    std::cout << "LUT4(8): OK." << std::endl;

    out = ctx.eval_lut_amortized(&ct9, lut);
    assert(ctx.decrypt(&out[0]) == 1);
    assert(ctx.decrypt(&out[1]) == 0);
    assert(ctx.decrypt(&out[2]) == 0);
    assert(ctx.decrypt(&out[3]) == 1);
    std::cout << "LUT4(9): OK." << std::endl;

    out = ctx.eval_lut_amortized(&ctA, lut);
    assert(ctx.decrypt(&out[0]) == 0);
    assert(ctx.decrypt(&out[1]) == 1);
    assert(ctx.decrypt(&out[2]) == 0);
    assert(ctx.decrypt(&out[3]) == 1);
    std::cout << "LUT4(A): OK." << std::endl;

    out = ctx.eval_lut_amortized(&ctB, lut);
    assert(ctx.decrypt(&out[0]) == 1);
    assert(ctx.decrypt(&out[1]) == 1);
    assert(ctx.decrypt(&out[2]) == 0);
    assert(ctx.decrypt(&out[3]) == 1);
    std::cout << "LUT4(B): OK." << std::endl;

    out = ctx.eval_lut_amortized(&ctC, lut);
    assert(ctx.decrypt(&out[0]) == 0);
    assert(ctx.decrypt(&out[1]) == 0);
    assert(ctx.decrypt(&out[2]) == 1);
    assert(ctx.decrypt(&out[3]) == 1);
    std::cout << "LUT4(C): OK." << std::endl;

    out = ctx.eval_lut_amortized(&ctD, lut);
    assert(ctx.decrypt(&out[0]) == 1);
    assert(ctx.decrypt(&out[1]) == 0);
    assert(ctx.decrypt(&out[2]) == 1);
    assert(ctx.decrypt(&out[3]) == 1);
    std::cout << "LUT4(D): OK." << std::endl;

    out = ctx.eval_lut_amortized(&ctE, lut);
    assert(ctx.decrypt(&out[0]) == 0);
    assert(ctx.decrypt(&out[1]) == 1);
    assert(ctx.decrypt(&out[2]) == 1);
    assert(ctx.decrypt(&out[3]) == 1);
    std::cout << "LUT4(E): OK." << std::endl;

    out = ctx.eval_lut_amortized(&ctF, lut);
    assert(ctx.decrypt(&out[0]) == 1);
    assert(ctx.decrypt(&out[1]) == 1);
    assert(ctx.decrypt(&out[2]) == 1);
    assert(ctx.decrypt(&out[3]) == 1);
    std::cout << "LUT4(F): OK." << std::endl;
}

std::vector<long>
test_add4_lut3(FHEContext& ctx, uint8_t a, uint8_t b)
{
    Ciphertext ct_a0 = ctx.encrypt_public((a >> 0) & 1);
    Ciphertext ct_a1 = ctx.encrypt_public((a >> 1) & 1);
    Ciphertext ct_a2 = ctx.encrypt_public((a >> 2) & 1);
    Ciphertext ct_a3 = ctx.encrypt_public((a >> 3) & 1);
    Ciphertext ct_b0 = ctx.encrypt_public((b >> 0) & 1);
    Ciphertext ct_b1 = ctx.encrypt_public((b >> 1) & 1);
    Ciphertext ct_b2 = ctx.encrypt_public((b >> 2) & 1);
    Ciphertext ct_b3 = ctx.encrypt_public((b >> 3) & 1);

    std::vector<HomomorphicAccumulator> decomp;
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
            default: return 0;
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
            default: return 0;
        };
    }));
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
            default: return 0;
        };
    }));
    std::vector<HomomorphicAccumulator> lut1;
    lut1.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 4 (LUT2 _22_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            default: return 0;
        };
    }));
    lut1.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 8 (LUT2 _26_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            default: return 0;
        };
    }));

    std::vector<HomomorphicAccumulator> lut2;
    lut2.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 3 (LUT3 _21_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: return 0;
        };
    }));
    lut2.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 5 (LUT3 _23_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: return 0;
        };
    }));

    std::vector<HomomorphicAccumulator> lut3;
    lut3.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 6 (LUT3 _24_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: return 0;
        };
    }));
    lut3.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 2 (LUT3 _20_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: return 0;
        };
    }));

    std::vector<HomomorphicAccumulator> lut4;
    lut4.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 7 (LUT3 _25_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: return 0;
        };
    }));
    lut4.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 1 (LUT3 _19_ INIT 0xd4 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: return 0;
        };
    }));

    Ciphertext gin1 = 1 * ct_a0 + 2 * ct_b0;
    std::vector<Ciphertext> gout1 = ctx.eval_lut_amortized(&gin1, lut1);

    Ciphertext gin2 = 1 * gout1[0] + 2 * ct_a1 + 4 * ct_b1;
    std::vector<Ciphertext> gout2 = ctx.eval_lut_amortized(&gin2, lut2);

    Ciphertext gin3 = 1 * gout2[0] + 2 * ct_a2 + 4 * ct_b2;
    std::vector<Ciphertext> gout3 = ctx.eval_lut_amortized(&gin3, lut3);

    Ciphertext gin4 = 1 * gout3[1] + 2 * ct_a3 + 4 * ct_b3;
    std::vector<Ciphertext> gout4 = ctx.eval_lut_amortized(&gin4, lut4);

    std::vector<long> dec;
    dec.push_back(ctx.decrypt(&gout1[1]));
    dec.push_back(ctx.decrypt(&gout2[1]));
    dec.push_back(ctx.decrypt(&gout3[0]));
    dec.push_back(ctx.decrypt(&gout4[0]));
    dec.push_back(ctx.decrypt(&gout4[1]));
    return dec;
}

std::vector<long>
test_add4_lut3fa(FHEContext& ctx, uint8_t a, uint8_t b)
{
    Ciphertext ct_a0 = ctx.encrypt_public((a >> 0) & 1);
    Ciphertext ct_a1 = ctx.encrypt_public((a >> 1) & 1);
    Ciphertext ct_a2 = ctx.encrypt_public((a >> 2) & 1);
    Ciphertext ct_a3 = ctx.encrypt_public((a >> 3) & 1);
    Ciphertext ct_b0 = ctx.encrypt_public((b >> 0) & 1);
    Ciphertext ct_b1 = ctx.encrypt_public((b >> 1) & 1);
    Ciphertext ct_b2 = ctx.encrypt_public((b >> 2) & 1);
    Ciphertext ct_b3 = ctx.encrypt_public((b >> 3) & 1);

    std::vector<HomomorphicAccumulator> decomp;
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
            default: return 0;
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
            default: return 0;
        };
    }));
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
            default: return 0;
        };
    }));
    Ciphertext gin1 = 1 * ct_a0 + 2 * ct_a1 + 1 * ct_b0 + 2 * ct_b1;
    std::vector<Ciphertext> gout1 = ctx.eval_lut_amortized(&gin1, decomp);

    Ciphertext gin2 = 1 * ct_a2 + 2 * ct_a3 + 1 * ct_b2 + 2 * ct_b3 + gout1[2];
    std::vector<Ciphertext> gout2 = ctx.eval_lut_amortized(&gin2, decomp);

    std::vector<long> dec;
    dec.push_back(ctx.decrypt(&gout1[0]));
    dec.push_back(ctx.decrypt(&gout1[1]));
    dec.push_back(ctx.decrypt(&gout2[0]));
    dec.push_back(ctx.decrypt(&gout2[1]));
    dec.push_back(ctx.decrypt(&gout2[2]));
    return dec;
}

int
main(void)
{
    FHEContext ctx;
    std::cout << "[+] ";
    ctx.generate_context(FHENamedParams::tfhe_11_NTT_amortized);
    ctx.set_default_message_encoding_type(partial_domain);

    test_lut3(ctx);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            std::cout << "[+] Testing inputs " << i << ", " << j << std::endl;
            std::cout << "Expected: " << std::bitset<5>(i + j) << std::endl;

            int sum = 0;
            auto ret3 = test_add4_lut3(ctx, i, j);
            std::cout << "Actual (lut3): ";
            for (int k = 4; k > 0; --k) {
                sum = (sum << 1) | ret3[k];
                std::cout << ret3[k] << ", ";
            }
            std::cout << ret3[0] << std::endl;
            assert(sum | ret3[0] == i + j);

            sum = 0;
            auto ret3fa = test_add4_lut3fa(ctx, i, j);
            std::cout << "Actual (lut3fa): ";
            for (int k = 4; k > 0; --k) {
                sum = (sum << 1) | ret3fa[k];
                std::cout << ret3fa[k] << ", ";
            }
            std::cout << ret3fa[0] << std::endl;
            assert(sum | ret3[0] == i + j);
        }
    }

    return 0;
}
