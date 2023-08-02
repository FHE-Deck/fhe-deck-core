#include <bitset>
#include <cassert>
#include <iostream>

#include "fhe_context.h"

using namespace fhe_deck;

long
compose(const std::vector<long>& bits)
{
    long out = 0;
    for (int i = 0; i < bits.size(); ++i)
        out = (out << 1) | bits[bits.size() - i - 1];
    return out;
}

void
test_lut4(FHEContext& ctx)
{
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

    std::vector<RotationPoly> lut;
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
    std::cerr << "\rLUT4(0)";

    out = ctx.eval_lut_amortized(&ct1, lut);
    assert(ctx.decrypt(&out[0]) == 1);
    assert(ctx.decrypt(&out[1]) == 0);
    assert(ctx.decrypt(&out[2]) == 0);
    assert(ctx.decrypt(&out[3]) == 0);
    std::cerr << "\rLUT4(1)";

    out = ctx.eval_lut_amortized(&ct2, lut);
    assert(ctx.decrypt(&out[0]) == 0);
    assert(ctx.decrypt(&out[1]) == 1);
    assert(ctx.decrypt(&out[2]) == 0);
    assert(ctx.decrypt(&out[3]) == 0);
    std::cerr << "\rLUT4(2)";

    out = ctx.eval_lut_amortized(&ct3, lut);
    assert(ctx.decrypt(&out[0]) == 1);
    assert(ctx.decrypt(&out[1]) == 1);
    assert(ctx.decrypt(&out[2]) == 0);
    assert(ctx.decrypt(&out[3]) == 0);
    std::cerr << "\rLUT4(3)";

    out = ctx.eval_lut_amortized(&ct4, lut);
    assert(ctx.decrypt(&out[0]) == 0);
    assert(ctx.decrypt(&out[1]) == 0);
    assert(ctx.decrypt(&out[2]) == 1);
    assert(ctx.decrypt(&out[3]) == 0);
    std::cerr << "\rLUT4(4)";

    out = ctx.eval_lut_amortized(&ct5, lut);
    assert(ctx.decrypt(&out[0]) == 1);
    assert(ctx.decrypt(&out[1]) == 0);
    assert(ctx.decrypt(&out[2]) == 1);
    assert(ctx.decrypt(&out[3]) == 0);
    std::cerr << "\rLUT4(5)";

    out = ctx.eval_lut_amortized(&ct6, lut);
    assert(ctx.decrypt(&out[0]) == 0);
    assert(ctx.decrypt(&out[1]) == 1);
    assert(ctx.decrypt(&out[2]) == 1);
    assert(ctx.decrypt(&out[3]) == 0);
    std::cerr << "\rLUT4(6)";

    out = ctx.eval_lut_amortized(&ct7, lut);
    assert(ctx.decrypt(&out[0]) == 1);
    assert(ctx.decrypt(&out[1]) == 1);
    assert(ctx.decrypt(&out[2]) == 1);
    assert(ctx.decrypt(&out[3]) == 0);
    std::cerr << "\rLUT4(7)";

    out = ctx.eval_lut_amortized(&ct8, lut);
    assert(ctx.decrypt(&out[0]) == 0);
    assert(ctx.decrypt(&out[1]) == 0);
    assert(ctx.decrypt(&out[2]) == 0);
    assert(ctx.decrypt(&out[3]) == 1);
    std::cerr << "\rLUT4(8)";

    out = ctx.eval_lut_amortized(&ct9, lut);
    assert(ctx.decrypt(&out[0]) == 1);
    assert(ctx.decrypt(&out[1]) == 0);
    assert(ctx.decrypt(&out[2]) == 0);
    assert(ctx.decrypt(&out[3]) == 1);
    std::cerr << "\rLUT4(9)";

    out = ctx.eval_lut_amortized(&ctA, lut);
    assert(ctx.decrypt(&out[0]) == 0);
    assert(ctx.decrypt(&out[1]) == 1);
    assert(ctx.decrypt(&out[2]) == 0);
    assert(ctx.decrypt(&out[3]) == 1);
    std::cerr << "\rLUT4(A)";

    out = ctx.eval_lut_amortized(&ctB, lut);
    assert(ctx.decrypt(&out[0]) == 1);
    assert(ctx.decrypt(&out[1]) == 1);
    assert(ctx.decrypt(&out[2]) == 0);
    assert(ctx.decrypt(&out[3]) == 1);
    std::cerr << "\rLUT4(B)";

    out = ctx.eval_lut_amortized(&ctC, lut);
    assert(ctx.decrypt(&out[0]) == 0);
    assert(ctx.decrypt(&out[1]) == 0);
    assert(ctx.decrypt(&out[2]) == 1);
    assert(ctx.decrypt(&out[3]) == 1);
    std::cerr << "\rLUT4(C)";

    out = ctx.eval_lut_amortized(&ctD, lut);
    assert(ctx.decrypt(&out[0]) == 1);
    assert(ctx.decrypt(&out[1]) == 0);
    assert(ctx.decrypt(&out[2]) == 1);
    assert(ctx.decrypt(&out[3]) == 1);
    std::cerr << "\rLUT4(D)";

    out = ctx.eval_lut_amortized(&ctE, lut);
    assert(ctx.decrypt(&out[0]) == 0);
    assert(ctx.decrypt(&out[1]) == 1);
    assert(ctx.decrypt(&out[2]) == 1);
    assert(ctx.decrypt(&out[3]) == 1);
    std::cerr << "\rLUT4(E)";

    out = ctx.eval_lut_amortized(&ctF, lut);
    assert(ctx.decrypt(&out[0]) == 1);
    assert(ctx.decrypt(&out[1]) == 1);
    assert(ctx.decrypt(&out[2]) == 1);
    assert(ctx.decrypt(&out[3]) == 1);
    std::cerr << "\rLUT4(F)" << std::endl;

    std::cerr << "\r";
}

std::vector<long>
test_add4_lut4(FHEContext& ctx, uint8_t a, uint8_t b)
{
    Ciphertext ct_a0 = ctx.encrypt_public((a >> 0) & 1);
    Ciphertext ct_a1 = ctx.encrypt_public((a >> 1) & 1);
    Ciphertext ct_a2 = ctx.encrypt_public((a >> 2) & 1);
    Ciphertext ct_a3 = ctx.encrypt_public((a >> 3) & 1);
    Ciphertext ct_b0 = ctx.encrypt_public((b >> 0) & 1);
    Ciphertext ct_b1 = ctx.encrypt_public((b >> 1) & 1);
    Ciphertext ct_b2 = ctx.encrypt_public((b >> 2) & 1);
    Ciphertext ct_b3 = ctx.encrypt_public((b >> 3) & 1);

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
    }));
    decomp.push_back(ctx.genrate_lut([](long I) -> long {
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
    }));

    std::vector<RotationPoly> lut0;
    lut0.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 7 (LUT2 _22_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT0   ";
    Ciphertext gin0 = 1 * ct_a0 + 2 * ct_b0;
    std::vector<Ciphertext> gout0 = ctx.eval_lut_amortized(&gin0, lut0);

    std::vector<RotationPoly> lut1;
    lut1.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 4 (LUT4 _19_ INIT 0x8778 PERM 2301) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut1.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 3 (LUT4 _18_ INIT 0x1777 PERM 0123) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT1   ";
    Ciphertext gin1 = 1 * ct_a1 + 2 * ct_b1 + 4 * ct_a0 + 8 * ct_b0;
    std::vector<Ciphertext> gout1 = ctx.eval_lut_amortized(&gin1, lut1);

    std::vector<RotationPoly> lut2;
    lut2.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 5 (LUT3 _20_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut2.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 2 (LUT3 _17_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT2   ";
    Ciphertext gin2 = 1 * gout1[1] + 2 * ct_a2 + 4 * ct_b2;
    std::vector<Ciphertext> gout2 = ctx.eval_lut_amortized(&gin2, lut2);

    std::vector<RotationPoly> lut3;
    lut3.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 6 (LUT3 _21_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut3.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 1 (LUT3 _16_ INIT 0xd4 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT3   ";
    Ciphertext gin3 = 1 * gout2[1] + 2 * ct_a3 + 4 * ct_b3;
    std::vector<Ciphertext> gout3 = ctx.eval_lut_amortized(&gin3, lut3);

    std::cerr << "\r          \r";
    std::vector<long> out;
    out.push_back(ctx.decrypt(&gout0[0])); /* out0 */
    out.push_back(ctx.decrypt(&gout1[0])); /* out1 */
    out.push_back(ctx.decrypt(&gout2[0])); /* out2 */
    out.push_back(ctx.decrypt(&gout3[0])); /* out3 */
    out.push_back(ctx.decrypt(&gout3[1])); /* out4 */
    return out;
}

std::vector<long>
test_calculator_lut4(FHEContext& ctx, uint8_t op, uint16_t x, uint16_t y)
{
    Ciphertext ct_op0 = ctx.encrypt_public((op >> 0) & 1);
    Ciphertext ct_op1 = ctx.encrypt_public((op >> 1) & 1);
    Ciphertext ct_op2 = ctx.encrypt_public((op >> 2) & 1);
    Ciphertext ct_op3 = ctx.encrypt_public((op >> 3) & 1);
    Ciphertext ct_op4 = ctx.encrypt_public((op >> 4) & 1);
    Ciphertext ct_op5 = ctx.encrypt_public((op >> 5) & 1);
    Ciphertext ct_op6 = ctx.encrypt_public((op >> 6) & 1);
    Ciphertext ct_op7 = ctx.encrypt_public((op >> 7) & 1);
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
    Ciphertext ct_y0 = ctx.encrypt_public((y >> 0) & 1);
    Ciphertext ct_y1 = ctx.encrypt_public((y >> 1) & 1);
    Ciphertext ct_y2 = ctx.encrypt_public((y >> 2) & 1);
    Ciphertext ct_y3 = ctx.encrypt_public((y >> 3) & 1);
    Ciphertext ct_y4 = ctx.encrypt_public((y >> 4) & 1);
    Ciphertext ct_y5 = ctx.encrypt_public((y >> 5) & 1);
    Ciphertext ct_y6 = ctx.encrypt_public((y >> 6) & 1);
    Ciphertext ct_y7 = ctx.encrypt_public((y >> 7) & 1);
    Ciphertext ct_y8 = ctx.encrypt_public((y >> 8) & 1);
    Ciphertext ct_y9 = ctx.encrypt_public((y >> 9) & 1);
    Ciphertext ct_y10 = ctx.encrypt_public((y >> 10) & 1);
    Ciphertext ct_y11 = ctx.encrypt_public((y >> 11) & 1);
    Ciphertext ct_y12 = ctx.encrypt_public((y >> 12) & 1);
    Ciphertext ct_y13 = ctx.encrypt_public((y >> 13) & 1);
    Ciphertext ct_y14 = ctx.encrypt_public((y >> 14) & 1);
    Ciphertext ct_y15 = ctx.encrypt_public((y >> 15) & 1);

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
    }));
    decomp.push_back(ctx.genrate_lut([](long I) -> long {
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
    }));

    std::vector<RotationPoly> lut0;
    lut0.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 77 (LUT4 _1281_ INIT 0x7888 PERM 1320) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut0.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 98 (LUT4 _1302_ INIT 0x8000 PERM 1230) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT0   ";
    Ciphertext gin0 = 1 * ct_x6 + 2 * ct_y1 + 4 * ct_y0 + 8 * ct_x5;
    std::vector<Ciphertext> gout0 = ctx.eval_lut_amortized(&gin0, lut0);

    std::vector<RotationPoly> lut1;
    lut1.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 310 (LUT4 _1514_ INIT 0x7888 PERM 1320) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut1.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 342 (LUT4 _1546_ INIT 0x8000 PERM 1230) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT1   ";
    Ciphertext gin1 = 1 * ct_x13 + 2 * ct_y1 + 4 * ct_y0 + 8 * ct_x12;
    std::vector<Ciphertext> gout1 = ctx.eval_lut_amortized(&gin1, lut1);

    std::vector<RotationPoly> lut2;
    lut2.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 63 (LUT4 _1267_ INIT 0x8000 PERM 1032) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut2.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 45 (LUT4 _1249_ INIT 0x7888 PERM 1203) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT2   ";
    Ciphertext gin2 = 1 * ct_y4 + 2 * ct_y3 + 4 * ct_x1 + 8 * ct_x0;
    std::vector<Ciphertext> gout2 = ctx.eval_lut_amortized(&gin2, lut2);

    std::vector<RotationPoly> lut3;
    lut3.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 353 (LUT4 _1557_ INIT 0x7888 PERM 0213) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut3.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 388 (LUT4 _1592_ INIT 0x8000 PERM 0132) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT3   ";
    Ciphertext gin3 = 1 * ct_y6 + 2 * ct_y7 + 4 * ct_x8 + 8 * ct_x7;
    std::vector<Ciphertext> gout3 = ctx.eval_lut_amortized(&gin3, lut3);

    std::vector<RotationPoly> lut4;
    lut4.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 273 (LUT4 _1477_ INIT 0x8000 PERM 0132) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut4.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 236 (LUT4 _1440_ INIT 0x7888 PERM 0213) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT4   ";
    Ciphertext gin4 = 1 * ct_y6 + 2 * ct_y7 + 4 * ct_x5 + 8 * ct_x4;
    std::vector<Ciphertext> gout4 = ctx.eval_lut_amortized(&gin4, lut4);

    std::vector<RotationPoly> lut5;
    lut5.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 317 (LUT4 _1521_ INIT 0x8000 PERM 3021) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut5.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 270 (LUT4 _1474_ INIT 0x7888 PERM 3102) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT5   ";
    Ciphertext gin5 = 1 * ct_y4 + 2 * ct_x9 + 4 * ct_x8 + 8 * ct_y3;
    std::vector<Ciphertext> gout5 = ctx.eval_lut_amortized(&gin5, lut5);

    std::vector<RotationPoly> lut6;
    lut6.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 202 (LUT2 _1406_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT6   ";
    Ciphertext gin6 = 1 * ct_y9 + 2 * ct_x1;
    std::vector<Ciphertext> gout6 = ctx.eval_lut_amortized(&gin6, lut6);

    std::vector<RotationPoly> lut7;
    lut7.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 106 (LUT2 _1310_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT7   ";
    Ciphertext gin7 = 1 * ct_y6 + 2 * ct_x1;
    std::vector<Ciphertext> gout7 = ctx.eval_lut_amortized(&gin7, lut7);

    std::vector<RotationPoly> lut8;
    lut8.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 127 (LUT4 _1331_ INIT 0x8000 PERM 1302) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut8.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 100 (LUT4 _1304_ INIT 0x7888 PERM 1032) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 1;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT8   ";
    Ciphertext gin8 = 1 * ct_x6 + 2 * ct_y1 + 4 * ct_x7 + 8 * ct_y0;
    std::vector<Ciphertext> gout8 = ctx.eval_lut_amortized(&gin8, lut8);

    std::vector<RotationPoly> lut9;
    lut9.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 135 (LUT4 _1339_ INIT 0x8000 PERM 2013) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut9.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 102 (LUT4 _1306_ INIT 0x7888 PERM 2301) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 1;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT9   ";
    Ciphertext gin9 = 1 * ct_y4 + 2 * ct_x3 + 4 * ct_y3 + 8 * ct_x4;
    std::vector<Ciphertext> gout9 = ctx.eval_lut_amortized(&gin9, lut9);

    std::vector<RotationPoly> lut10;
    lut10.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 165 (LUT4 _1369_ INIT 0x8000 PERM 1032) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut10.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 131 (LUT4 _1335_ INIT 0x7888 PERM 1203) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT10   ";
    Ciphertext gin10 = 1 * ct_y4 + 2 * ct_y3 + 4 * ct_x5 + 8 * ct_x4;
    std::vector<Ciphertext> gout10 = ctx.eval_lut_amortized(&gin10, lut10);

    std::vector<RotationPoly> lut11;
    lut11.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 82 (LUT2 _1286_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT11   ";
    Ciphertext gin11 = 1 * ct_y6 + 2 * ct_x0;
    std::vector<Ciphertext> gout11 = ctx.eval_lut_amortized(&gin11, lut11);

    std::vector<RotationPoly> lut12;
    lut12.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 60 (LUT4 _1264_ INIT 0x7888 PERM 0312) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut12.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 75 (LUT4 _1279_ INIT 0x8000 PERM 0132) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT12   ";
    Ciphertext gin12 = 1 * ct_y1 + 2 * ct_y0 + 4 * ct_x5 + 8 * ct_x4;
    std::vector<Ciphertext> gout12 = ctx.eval_lut_amortized(&gin12, lut12);

    std::vector<RotationPoly> lut13;
    lut13.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 406 (LUT4 _1610_ INIT 0x7877 PERM 0231) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 1;
            case 10: return 1;
            case 11: return 1;
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT13   ";
    Ciphertext gin13 = 1 * ct_y14 + 2 * ct_y15 + 4 * ct_x1 + 8 * ct_x0;
    std::vector<Ciphertext> gout13 = ctx.eval_lut_amortized(&gin13, lut13);

    std::vector<RotationPoly> lut14;
    lut14.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 386 (LUT4 _1590_ INIT 0x8000 PERM 3021) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut14.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 346 (LUT4 _1550_ INIT 0x7888 PERM 3102) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT14   ";
    Ciphertext gin14 = 1 * ct_y4 + 2 * ct_x11 + 4 * ct_x10 + 8 * ct_y3;
    std::vector<Ciphertext> gout14 = ctx.eval_lut_amortized(&gin14, lut14);

    std::vector<RotationPoly> lut15;
    lut15.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 384 (LUT4 _1588_ INIT 0x8000 PERM 2301) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut15.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 344 (LUT4 _1548_ INIT 0x7888 PERM 2031) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT15   ";
    Ciphertext gin15 = 1 * ct_x13 + 2 * ct_x14 + 4 * ct_y1 + 8 * ct_y0;
    std::vector<Ciphertext> gout15 = ctx.eval_lut_amortized(&gin15, lut15);

    std::vector<RotationPoly> lut16;
    lut16.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 402 (LUT4 _1606_ INIT 0x8777 PERM 2013) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT16   ";
    Ciphertext gin16 = 1 * ct_x13 + 2 * ct_y3 + 4 * ct_y2 + 8 * ct_x12;
    std::vector<Ciphertext> gout16 = ctx.eval_lut_amortized(&gin16, lut16);

    std::vector<RotationPoly> lut17;
    lut17.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 256 (LUT3 _1460_ INIT 0x80 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT17   ";
    Ciphertext gin17 = 1 * gout6[0] + 2 * ct_y10 + 4 * ct_x2;
    std::vector<Ciphertext> gout17 = ctx.eval_lut_amortized(&gin17, lut17);

    std::vector<RotationPoly> lut18;
    lut18.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 11 (LUT4 _1215_ INIT 0x7888 PERM 0231) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut18.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 17 (LUT4 _1221_ INIT 0x8000 PERM 0231) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT18   ";
    Ciphertext gin18 = 1 * ct_y1 + 2 * ct_x1 + 4 * ct_x0 + 8 * ct_y0;
    std::vector<Ciphertext> gout18 = ctx.eval_lut_amortized(&gin18, lut18);

    std::vector<RotationPoly> lut19;
    lut19.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 190 (LUT4 _1394_ INIT 0x7888 PERM 2130) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut19.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 225 (LUT4 _1429_ INIT 0x8000 PERM 2310) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT19   ";
    Ciphertext gin19 = 1 * ct_x10 + 2 * ct_x9 + 4 * ct_y1 + 8 * ct_y0;
    std::vector<Ciphertext> gout19 = ctx.eval_lut_amortized(&gin19, lut19);

    std::vector<RotationPoly> lut20;
    lut20.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 394 (LUT4 _1598_ INIT 0x8000 PERM 0132) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut20.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 361 (LUT4 _1565_ INIT 0x7888 PERM 0213) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT20   ";
    Ciphertext gin20 = 1 * ct_y9 + 2 * ct_y10 + 4 * ct_x5 + 8 * ct_x4;
    std::vector<Ciphertext> gout20 = ctx.eval_lut_amortized(&gin20, lut20);

    std::vector<RotationPoly> lut21;
    lut21.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 62 (LUT4 _1266_ INIT 0x7888 PERM 1203) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut21.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 81 (LUT4 _1285_ INIT 0x8000 PERM 1032) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT21   ";
    Ciphertext gin21 = 1 * ct_y4 + 2 * ct_y3 + 4 * ct_x2 + 8 * ct_x1;
    std::vector<Ciphertext> gout21 = ctx.eval_lut_amortized(&gin21, lut21);

    std::vector<RotationPoly> lut22;
    lut22.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 197 (LUT4 _1401_ INIT 0x8000 PERM 2031) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut22.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 160 (LUT4 _1364_ INIT 0x7888 PERM 2103) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT22   ";
    Ciphertext gin22 = 1 * ct_y4 + 2 * ct_x6 + 4 * ct_y3 + 8 * ct_x5;
    std::vector<Ciphertext> gout22 = ctx.eval_lut_amortized(&gin22, lut22);

    std::vector<RotationPoly> lut23;
    lut23.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 158 (LUT4 _1362_ INIT 0x7888 PERM 2130) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut23.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 188 (LUT4 _1392_ INIT 0x8000 PERM 2310) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT23   ";
    Ciphertext gin23 = 1 * ct_x9 + 2 * ct_x8 + 4 * ct_y1 + 8 * ct_y0;
    std::vector<Ciphertext> gout23 = ctx.eval_lut_amortized(&gin23, lut23);

    std::vector<RotationPoly> lut24;
    lut24.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 23 (LUT3 _1227_ INIT 0x1 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT24   ";
    Ciphertext gin24 = 1 * ct_y1 + 2 * ct_y2 + 4 * ct_y0;
    std::vector<Ciphertext> gout24 = ctx.eval_lut_amortized(&gin24, lut24);

    std::vector<RotationPoly> lut25;
    lut25.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 316 (LUT4 _1520_ INIT 0x7f PERM 3120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut25.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 269 (LUT3 _1473_ INIT 0x78 PERM 231) */
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
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT25   ";
    Ciphertext gin25 = 1 * gout5[0] + 2 * gout5[1] + 4 * ct_y5 + 8 * ct_x7;
    std::vector<Ciphertext> gout25 = ctx.eval_lut_amortized(&gin25, lut25);

    std::vector<RotationPoly> lut26;
    lut26.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 234 (LUT4 _1438_ INIT 0x8000 PERM 2013) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut26.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 192 (LUT4 _1396_ INIT 0x7888 PERM 2301) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 1;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT26   ";
    Ciphertext gin26 = 1 * ct_y4 + 2 * ct_x6 + 4 * ct_y3 + 8 * ct_x7;
    std::vector<Ciphertext> gout26 = ctx.eval_lut_amortized(&gin26, lut26);

    std::vector<RotationPoly> lut27;
    lut27.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 42 (LUT4 _1246_ INIT 0x8000 PERM 1320) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut27.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 28 (LUT4 _1232_ INIT 0x7888 PERM 1230) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT27   ";
    Ciphertext gin27 = 1 * ct_x3 + 2 * ct_y1 + 4 * ct_x2 + 8 * ct_y0;
    std::vector<Ciphertext> gout27 = ctx.eval_lut_amortized(&gin27, lut27);

    std::vector<RotationPoly> lut28;
    lut28.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 134 (LUT4 _1338_ INIT 0x7f PERM 3120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut28.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 101 (LUT3 _1305_ INIT 0x78 PERM 231) */
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
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT28   ";
    Ciphertext gin28 = 1 * gout9[0] + 2 * gout9[1] + 4 * ct_y5 + 8 * ct_x2;
    std::vector<Ciphertext> gout28 = ctx.eval_lut_amortized(&gin28, lut28);

    std::vector<RotationPoly> lut29;
    lut29.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 301 (LUT4 _1505_ INIT 0x7888 PERM 1320) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut29.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 359 (LUT4 _1563_ INIT 0x8000 PERM 1203) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT29   ";
    Ciphertext gin29 = 1 * ct_x3 + 2 * ct_y9 + 4 * ct_y10 + 8 * ct_x4;
    std::vector<Ciphertext> gout29 = ctx.eval_lut_amortized(&gin29, lut29);

    std::vector<RotationPoly> lut30;
    lut30.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 300 (LUT3 _1504_ INIT 0x78 PERM 120) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT30   ";
    Ciphertext gin30 = 1 * gout29[0] + 2 * ct_y11 + 4 * ct_x2;
    std::vector<Ciphertext> gout30 = ctx.eval_lut_amortized(&gin30, lut30);

    std::vector<RotationPoly> lut31;
    lut31.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 97 (LUT4 _1301_ INIT 0x7f PERM 3120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut31.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 76 (LUT3 _1280_ INIT 0x78 PERM 231) */
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
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT31   ";
    Ciphertext gin31 = 1 * gout0[1] + 2 * gout0[0] + 4 * ct_y2 + 8 * ct_x4;
    std::vector<Ciphertext> gout31 = ctx.eval_lut_amortized(&gin31, lut31);

    std::vector<RotationPoly> lut32;
    lut32.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 79 (LUT4 _1283_ INIT 0x7888 PERM 2103) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut32.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 105 (LUT4 _1309_ INIT 0x8000 PERM 2031) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT32   ";
    Ciphertext gin32 = 1 * ct_y4 + 2 * ct_x3 + 4 * ct_y3 + 8 * ct_x2;
    std::vector<Ciphertext> gout32 = ctx.eval_lut_amortized(&gin32, lut32);

    std::vector<RotationPoly> lut33;
    lut33.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 78 (LUT3 _1282_ INIT 0x78 PERM 120) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT33   ";
    Ciphertext gin33 = 1 * gout32[0] + 2 * ct_y5 + 4 * ct_x1;
    std::vector<Ciphertext> gout33 = ctx.eval_lut_amortized(&gin33, lut33);

    std::vector<RotationPoly> lut34;
    lut34.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 224 (LUT4 _1428_ INIT 0x7f PERM 2031) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut34.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 189 (LUT3 _1393_ INIT 0x78 PERM 320) */
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
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT34   ";
    Ciphertext gin34 = 1 * gout19[0] + 2 * gout19[1] + 4 * ct_x8 + 8 * ct_y2;
    std::vector<Ciphertext> gout34 = ctx.eval_lut_amortized(&gin34, lut34);

    std::vector<RotationPoly> lut35;
    lut35.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 58 (LUT4 _1262_ INIT 0x8000 PERM 1203) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut35.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 44 (LUT4 _1248_ INIT 0x7888 PERM 1023) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 1;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT35   ";
    Ciphertext gin35 = 1 * ct_x3 + 2 * ct_y1 + 4 * ct_y0 + 8 * ct_x4;
    std::vector<Ciphertext> gout35 = ctx.eval_lut_amortized(&gin35, lut35);

    std::vector<RotationPoly> lut36;
    lut36.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 229 (LUT4 _1433_ INIT 0x7888 PERM 2103) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut36.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 275 (LUT4 _1479_ INIT 0x8000 PERM 2031) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT36   ";
    Ciphertext gin36 = 1 * ct_y4 + 2 * ct_x8 + 4 * ct_y3 + 8 * ct_x7;
    std::vector<Ciphertext> gout36 = ctx.eval_lut_amortized(&gin36, lut36);

    std::vector<RotationPoly> lut37;
    lut37.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 228 (LUT3 _1432_ INIT 0x78 PERM 120) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT37   ";
    Ciphertext gin37 = 1 * gout36[0] + 2 * ct_y5 + 4 * ct_x6;
    std::vector<Ciphertext> gout37 = ctx.eval_lut_amortized(&gin37, lut37);

    std::vector<RotationPoly> lut38;
    lut38.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 351 (LUT4 _1555_ INIT 0x8000 PERM 3021) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut38.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 312 (LUT4 _1516_ INIT 0x7888 PERM 3102) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT38   ";
    Ciphertext gin38 = 1 * ct_y4 + 2 * ct_x10 + 4 * ct_x9 + 8 * ct_y3;
    std::vector<Ciphertext> gout38 = ctx.eval_lut_amortized(&gin38, lut38);

    std::vector<RotationPoly> lut39;
    lut39.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 36 (LUT2 _1240_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT39   ";
    Ciphertext gin39 = 1 * gout24[0] + 2 * ct_y3;
    std::vector<Ciphertext> gout39 = ctx.eval_lut_amortized(&gin39, lut39);

    std::vector<RotationPoly> lut40;
    lut40.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 233 (LUT4 _1437_ INIT 0x7f PERM 3021) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut40.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 191 (LUT3 _1395_ INIT 0x78 PERM 230) */
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
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT40   ";
    Ciphertext gin40 = 1 * gout26[1] + 2 * gout26[0] + 4 * ct_y5 + 8 * ct_x5;
    std::vector<Ciphertext> gout40 = ctx.eval_lut_amortized(&gin40, lut40);

    std::vector<RotationPoly> lut41;
    lut41.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 5 (LUT4 _1209_ INIT 0x4000 PERM 1302) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT41   ";
    Ciphertext gin41 = 1 * ct_op2 + 2 * ct_op1 + 4 * ct_op3 + 8 * ct_op0;
    std::vector<Ciphertext> gout41 = ctx.eval_lut_amortized(&gin41, lut41);

    std::vector<RotationPoly> lut42;
    lut42.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 360 (LUT3 _1564_ INIT 0x78 PERM 120) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT42   ";
    Ciphertext gin42 = 1 * gout20[1] + 2 * ct_y11 + 4 * ct_x3;
    std::vector<Ciphertext> gout42 = ctx.eval_lut_amortized(&gin42, lut42);

    std::vector<RotationPoly> lut43;
    lut43.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 187 (LUT4 _1391_ INIT 0x7f PERM 3021) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut43.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 157 (LUT3 _1361_ INIT 0x78 PERM 230) */
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
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT43   ";
    Ciphertext gin43 = 1 * gout23[0] + 2 * gout23[1] + 4 * ct_y2 + 8 * ct_x7;
    std::vector<Ciphertext> gout43 = ctx.eval_lut_amortized(&gin43, lut43);

    std::vector<RotationPoly> lut44;
    lut44.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 129 (LUT4 _1333_ INIT 0x7888 PERM 1230) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut44.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 156 (LUT4 _1360_ INIT 0x8000 PERM 1320) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT44   ";
    Ciphertext gin44 = 1 * ct_x8 + 2 * ct_y1 + 4 * ct_x7 + 8 * ct_y0;
    std::vector<Ciphertext> gout44 = ctx.eval_lut_amortized(&gin44, lut44);

    std::vector<RotationPoly> lut45;
    lut45.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 128 (LUT3 _1332_ INIT 0x78 PERM 210) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT45   ";
    Ciphertext gin45 = 1 * gout44[0] + 2 * ct_x6 + 4 * ct_y2;
    std::vector<Ciphertext> gout45 = ctx.eval_lut_amortized(&gin45, lut45);

    std::vector<RotationPoly> lut46;
    lut46.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 341 (LUT4 _1545_ INIT 0x7f PERM 2031) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut46.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 309 (LUT3 _1513_ INIT 0x78 PERM 320) */
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
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT46   ";
    Ciphertext gin46 = 1 * gout1[0] + 2 * gout1[1] + 4 * ct_x11 + 8 * ct_y2;
    std::vector<Ciphertext> gout46 = ctx.eval_lut_amortized(&gin46, lut46);

    std::vector<RotationPoly> lut47;
    lut47.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 186 (LUT3 _1390_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut47.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 222 (LUT3 _1426_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT47   ";
    Ciphertext gin47 = 1 * gout43[0] + 2 * gout34[1] + 4 * gout40[1];
    std::vector<Ciphertext> gout47 = ctx.eval_lut_amortized(&gin47, lut47);

    std::vector<RotationPoly> lut48;
    lut48.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 385 (LUT4 _1589_ INIT 0x7f PERM 3021) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut48.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 345 (LUT3 _1549_ INIT 0x78 PERM 230) */
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
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT48   ";
    Ciphertext gin48 = 1 * gout14[1] + 2 * gout14[0] + 4 * ct_y5 + 8 * ct_x9;
    std::vector<Ciphertext> gout48 = ctx.eval_lut_amortized(&gin48, lut48);

    std::vector<RotationPoly> lut49;
    lut49.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 277 (LUT4 _1481_ INIT 0x7888 PERM 0213) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut49.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 315 (LUT4 _1519_ INIT 0x8000 PERM 0132) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT49   ";
    Ciphertext gin49 = 1 * ct_y6 + 2 * ct_y7 + 4 * ct_x6 + 8 * ct_x5;
    std::vector<Ciphertext> gout49 = ctx.eval_lut_amortized(&gin49, lut49);

    std::vector<RotationPoly> lut50;
    lut50.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 276 (LUT3 _1480_ INIT 0x78 PERM 120) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT50   ";
    Ciphertext gin50 = 1 * gout49[0] + 2 * ct_y8 + 4 * ct_x4;
    std::vector<Ciphertext> gout50 = ctx.eval_lut_amortized(&gin50, lut50);

    std::vector<RotationPoly> lut51;
    lut51.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 258 (LUT4 _1462_ INIT 0x7888 PERM 1023) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 1;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut51.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 299 (LUT4 _1503_ INIT 0x8000 PERM 1230) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT51   ";
    Ciphertext gin51 = 1 * ct_x3 + 2 * ct_y9 + 4 * ct_y10 + 8 * ct_x2;
    std::vector<Ciphertext> gout51 = ctx.eval_lut_amortized(&gin51, lut51);

    std::vector<RotationPoly> lut52;
    lut52.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 257 (LUT3 _1461_ INIT 0x78 PERM 120) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT52   ";
    Ciphertext gin52 = 1 * gout51[0] + 2 * ct_y11 + 4 * ct_x1;
    std::vector<Ciphertext> gout52 = ctx.eval_lut_amortized(&gin52, lut52);

    std::vector<RotationPoly> lut53;
    lut53.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 397 (LUT4 _1601_ INIT 0x8777 PERM 0312) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT53   ";
    Ciphertext gin53 = 1 * ct_y8 + 2 * ct_y9 + 4 * ct_x6 + 8 * ct_x7;
    std::vector<Ciphertext> gout53 = ctx.eval_lut_amortized(&gin53, lut53);

    std::vector<RotationPoly> lut54;
    lut54.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 195 (LUT4 _1399_ INIT 0x8000 PERM 0132) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut54.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 167 (LUT4 _1371_ INIT 0x7888 PERM 0213) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT54   ";
    Ciphertext gin54 = 1 * ct_y6 + 2 * ct_y7 + 4 * ct_x3 + 8 * ct_x2;
    std::vector<Ciphertext> gout54 = ctx.eval_lut_amortized(&gin54, lut54);

    std::vector<RotationPoly> lut55;
    lut55.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 308 (LUT4 _1512_ INIT 0x8000 PERM 1203) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut55.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 268 (LUT4 _1472_ INIT 0x7888 PERM 1023) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 1;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT55   ";
    Ciphertext gin55 = 1 * ct_x11 + 2 * ct_y1 + 4 * ct_y0 + 8 * ct_x12;
    std::vector<Ciphertext> gout55 = ctx.eval_lut_amortized(&gin55, lut55);

    std::vector<RotationPoly> lut56;
    lut56.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 405 (LUT4 _1609_ INIT 0x8000 PERM 0132) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut56.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 363 (LUT4 _1567_ INIT 0x7888 PERM 0213) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT56   ";
    Ciphertext gin56 = 1 * ct_y12 + 2 * ct_y13 + 4 * ct_x2 + 8 * ct_x1;
    std::vector<Ciphertext> gout56 = ctx.eval_lut_amortized(&gin56, lut56);

    std::vector<RotationPoly> lut57;
    lut57.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 240 (LUT3 _1444_ INIT 0x80 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT57   ";
    Ciphertext gin57 = 1 * gout6[0] + 2 * ct_y10 + 4 * ct_x0;
    std::vector<Ciphertext> gout57 = ctx.eval_lut_amortized(&gin57, lut57);

    std::vector<RotationPoly> lut58;
    lut58.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 232 (LUT4 _1436_ INIT 0x8000 PERM 0123) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut58.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 199 (LUT4 _1403_ INIT 0x7888 PERM 0312) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT58   ";
    Ciphertext gin58 = 1 * ct_y6 + 2 * ct_y7 + 4 * ct_x3 + 8 * ct_x4;
    std::vector<Ciphertext> gout58 = ctx.eval_lut_amortized(&gin58, lut58);

    std::vector<RotationPoly> lut59;
    lut59.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 41 (LUT4 _1245_ INIT 0x7f PERM 3120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut59.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 27 (LUT3 _1231_ INIT 0x78 PERM 231) */
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
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT59   ";
    Ciphertext gin59 = 1 * gout27[0] + 2 * gout27[1] + 4 * ct_y2 + 8 * ct_x1;
    std::vector<Ciphertext> gout59 = ctx.eval_lut_amortized(&gin59, lut59);

    std::vector<RotationPoly> lut60;
    lut60.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 112 (LUT4 _1316_ INIT 0x100 PERM 1230) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT60   ";
    Ciphertext gin60 = 1 * gout39[0] + 2 * ct_y4 + 4 * ct_y5 + 8 * ct_y6;
    std::vector<Ciphertext> gout60 = ctx.eval_lut_amortized(&gin60, lut60);

    std::vector<RotationPoly> lut61;
    lut61.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 208 (LUT4 _1412_ INIT 0x100 PERM 1230) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT61   ";
    Ciphertext gin61 = 1 * gout60[0] + 2 * ct_y7 + 4 * ct_y8 + 8 * ct_y9;
    std::vector<Ciphertext> gout61 = ctx.eval_lut_amortized(&gin61, lut61);

    std::vector<RotationPoly> lut62;
    lut62.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 130 (LUT3 _1334_ INIT 0x78 PERM 120) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT62   ";
    Ciphertext gin62 = 1 * gout10[1] + 2 * ct_y5 + 4 * ct_x3;
    std::vector<Ciphertext> gout62 = ctx.eval_lut_amortized(&gin62, lut62);

    std::vector<RotationPoly> lut63;
    lut63.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 59 (LUT3 _1263_ INIT 0x78 PERM 210) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT63   ";
    Ciphertext gin63 = 1 * gout12[0] + 2 * ct_x3 + 4 * ct_y2;
    std::vector<Ciphertext> gout63 = ctx.eval_lut_amortized(&gin63, lut63);

    std::vector<RotationPoly> lut64;
    lut64.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 163 (LUT4 _1367_ INIT 0x8000 PERM 0132) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut64.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 137 (LUT4 _1341_ INIT 0x7888 PERM 0213) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT64   ";
    Ciphertext gin64 = 1 * ct_y6 + 2 * ct_y7 + 4 * ct_x2 + 8 * ct_x1;
    std::vector<Ciphertext> gout64 = ctx.eval_lut_amortized(&gin64, lut64);

    std::vector<RotationPoly> lut65;
    lut65.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 74 (LUT4 _1278_ INIT 0x7f PERM 2130) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT65   ";
    Ciphertext gin65 = 1 * gout12[1] + 2 * gout12[0] + 4 * ct_x3 + 8 * ct_y2;
    std::vector<Ciphertext> gout65 = ctx.eval_lut_amortized(&gin65, lut65);

    std::vector<RotationPoly> lut66;
    lut66.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 73 (LUT3 _1277_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut66.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 95 (LUT3 _1299_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT66   ";
    Ciphertext gin66 = 1 * gout65[0] + 2 * gout31[1] + 4 * gout33[0];
    std::vector<Ciphertext> gout66 = ctx.eval_lut_amortized(&gin66, lut66);

    std::vector<RotationPoly> lut67;
    lut67.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 57 (LUT4 _1261_ INIT 0x7f PERM 3120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut67.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 43 (LUT3 _1247_ INIT 0x78 PERM 231) */
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
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT67   ";
    Ciphertext gin67 = 1 * gout35[0] + 2 * gout35[1] + 4 * ct_y2 + 8 * ct_x2;
    std::vector<Ciphertext> gout67 = ctx.eval_lut_amortized(&gin67, lut67);

    std::vector<RotationPoly> lut68;
    lut68.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 4 (LUT4 _1208_ INIT 0x100 PERM 0123) */
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
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT68   ";
    Ciphertext gin68 = 1 * ct_op4 + 2 * ct_op6 + 4 * ct_op7 + 8 * ct_op5;
    std::vector<Ciphertext> gout68 = ctx.eval_lut_amortized(&gin68, lut68);

    std::vector<RotationPoly> lut69;
    lut69.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 10 (LUT4 _1214_ INIT 0x807f PERM 1032) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut69.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 3 (LUT2 _1207_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT69   ";
    Ciphertext gin69 = 1 * gout41[0] + 2 * gout68[0] + 4 * ct_y1 + 8 * ct_y0;
    std::vector<Ciphertext> gout69 = ctx.eval_lut_amortized(&gin69, lut69);

    std::vector<RotationPoly> lut70;
    lut70.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 9 (LUT4 _1213_ INIT 0x7887 PERM 2301) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut70.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 14 (LUT4 _1218_ INIT 0x2bbb PERM 0132) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT70   ";
    Ciphertext gin70 = 1 * gout69[0] + 2 * ct_x1 + 4 * ct_x0 + 8 * ct_y0;
    std::vector<Ciphertext> gout70 = ctx.eval_lut_amortized(&gin70, lut70);

    std::vector<RotationPoly> lut71;
    lut71.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 6 (LUT4 _1210_ INIT 0x4000 PERM 0123) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT71   ";
    Ciphertext gin71 = 1 * ct_op2 + 2 * ct_op1 + 4 * gout68[0] + 8 * ct_op3;
    std::vector<Ciphertext> gout71 = ctx.eval_lut_amortized(&gin71, lut71);

    std::vector<RotationPoly> lut72;
    lut72.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 7 (LUT2 _1211_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT72   ";
    Ciphertext gin72 = 1 * ct_op0 + 2 * gout71[0];
    std::vector<Ciphertext> gout72 = ctx.eval_lut_amortized(&gin72, lut72);

    std::vector<RotationPoly> lut73;
    lut73.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 246 (LUT3 _1450_ INIT 0xb0 PERM 201) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut73.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 207 (LUT2 _1411_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT73   ";
    Ciphertext gin73 = 1 * gout61[0] + 2 * gout69[1] + 4 * ct_y10;
    std::vector<Ciphertext> gout73 = ctx.eval_lut_amortized(&gin73, lut73);

    std::vector<RotationPoly> lut74;
    lut74.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 286 (LUT3 _1490_ INIT 0x7 PERM 210) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT74   ";
    Ciphertext gin74 = 1 * gout73[0] + 2 * gout69[1] + 4 * ct_y11;
    std::vector<Ciphertext> gout74 = ctx.eval_lut_amortized(&gin74, lut74);

    std::vector<RotationPoly> lut75;
    lut75.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 323 (LUT3 _1527_ INIT 0xb0 PERM 201) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut75.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 285 (LUT2 _1489_ INIT 0x9 PERM 02) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT75   ";
    Ciphertext gin75 = 1 * gout74[0] + 2 * gout69[1] + 4 * ct_y12;
    std::vector<Ciphertext> gout75 = ctx.eval_lut_amortized(&gin75, lut75);

    std::vector<RotationPoly> lut76;
    lut76.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 322 (LUT3 _1526_ INIT 0x96 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut76.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 368 (LUT3 _1572_ INIT 0x60 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT76   ";
    Ciphertext gin76 = 1 * gout75[0] + 2 * ct_x13 + 4 * ct_y13;
    std::vector<Ciphertext> gout76 = ctx.eval_lut_amortized(&gin76, lut76);

    std::vector<RotationPoly> lut77;
    lut77.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 173 (LUT4 _1377_ INIT 0xef00 PERM 2301) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
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
    }));
    lut77.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 111 (LUT3 _1315_ INIT 0xb4 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut77.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 141 (LUT3 _1345_ INIT 0xb0 PERM 201) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT77   ";
    Ciphertext gin77 = 1 * gout60[0] + 2 * gout69[1] + 4 * ct_y7 + 8 * ct_y8;
    std::vector<Ciphertext> gout77 = ctx.eval_lut_amortized(&gin77, lut77);

    std::vector<RotationPoly> lut78;
    lut78.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 172 (LUT3 _1376_ INIT 0x96 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT78   ";
    Ciphertext gin78 = 1 * gout77[0] + 2 * ct_x9 + 4 * ct_y9;
    std::vector<Ciphertext> gout78 = ctx.eval_lut_amortized(&gin78, lut78);

    std::vector<RotationPoly> lut79;
    lut79.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 85 (LUT4 _1289_ INIT 0xef00 PERM 2301) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
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
    }));
    lut79.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 35 (LUT3 _1239_ INIT 0xb4 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT79   ";
    Ciphertext gin79 = 1 * gout39[0] + 2 * gout69[1] + 4 * ct_y4 + 8 * ct_y5;
    std::vector<Ciphertext> gout79 = ctx.eval_lut_amortized(&gin79, lut79);

    std::vector<RotationPoly> lut80;
    lut80.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 113 (LUT3 _1317_ INIT 0x60 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut80.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 84 (LUT3 _1288_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT80   ";
    Ciphertext gin80 = 1 * gout79[0] + 2 * ct_y6 + 4 * ct_x6;
    std::vector<Ciphertext> gout80 = ctx.eval_lut_amortized(&gin80, lut80);

    std::vector<RotationPoly> lut81;
    lut81.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 34 (LUT4 _1238_ INIT 0xb400 PERM 0132) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut81.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 22 (LUT4 _1226_ INIT 0x4bb4 PERM 0132) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT81   ";
    Ciphertext gin81 = 1 * gout24[0] + 2 * gout69[1] + 4 * ct_x3 + 8 * ct_y3;
    std::vector<Ciphertext> gout81 = ctx.eval_lut_amortized(&gin81, lut81);

    std::vector<RotationPoly> lut82;
    lut82.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 15 (LUT4 _1219_ INIT 0x1fe0 PERM 1302) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT82   ";
    Ciphertext gin82 = 1 * gout69[1] + 2 * ct_y1 + 4 * ct_y2 + 8 * ct_y0;
    std::vector<Ciphertext> gout82 = ctx.eval_lut_amortized(&gin82, lut82);

    std::vector<RotationPoly> lut83;
    lut83.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 133 (LUT3 _1337_ INIT 0x80 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT83   ";
    Ciphertext gin83 = 1 * gout7[0] + 2 * ct_y7 + 4 * ct_x0;
    std::vector<Ciphertext> gout83 = ctx.eval_lut_amortized(&gin83, lut83);

    std::vector<RotationPoly> lut84;
    lut84.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 104 (LUT4 _1308_ INIT 0x7f PERM 3120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT84   ";
    Ciphertext gin84 = 1 * gout32[1] + 2 * gout32[0] + 4 * ct_y5 + 8 * ct_x1;
    std::vector<Ciphertext> gout84 = ctx.eval_lut_amortized(&gin84, lut84);

    std::vector<RotationPoly> lut85;
    lut85.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 138 (LUT4 _1342_ INIT 0x708 PERM 2301) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut85.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 103 (LUT4 _1307_ INIT 0x7887 PERM 2301) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT85   ";
    Ciphertext gin85 = 1 * gout84[0] + 2 * gout7[0] + 4 * ct_y7 + 8 * ct_x0;
    std::vector<Ciphertext> gout85 = ctx.eval_lut_amortized(&gin85, lut85);

    std::vector<RotationPoly> lut86;
    lut86.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 50 (LUT4 _1254_ INIT 0x4fb0 PERM 2013) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT86   ";
    Ciphertext gin86 = 1 * gout39[0] + 2 * gout69[1] + 4 * ct_y4 + 8 * ct_y5;
    std::vector<Ciphertext> gout86 = ctx.eval_lut_amortized(&gin86, lut86);

    std::vector<RotationPoly> lut87;
    lut87.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 18 (LUT4 _1222_ INIT 0x7888 PERM 0231) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut87.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 26 (LUT4 _1230_ INIT 0x8000 PERM 0321) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT87   ";
    Ciphertext gin87 = 1 * ct_y1 + 2 * ct_x2 + 4 * ct_x1 + 8 * ct_y0;
    std::vector<Ciphertext> gout87 = ctx.eval_lut_amortized(&gin87, lut87);

    std::vector<RotationPoly> lut88;
    lut88.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 319 (LUT4 _1523_ INIT 0x7888 PERM 0312) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut88.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 349 (LUT4 _1553_ INIT 0x8000 PERM 0123) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT88   ";
    Ciphertext gin88 = 1 * ct_y6 + 2 * ct_y7 + 4 * ct_x6 + 8 * ct_x7;
    std::vector<Ciphertext> gout88 = ctx.eval_lut_amortized(&gin88, lut88);

    std::vector<RotationPoly> lut89;
    lut89.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 227 (LUT4 _1431_ INIT 0x7888 PERM 2130) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut89.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 266 (LUT4 _1470_ INIT 0x8000 PERM 2310) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT89   ";
    Ciphertext gin89 = 1 * ct_x11 + 2 * ct_x10 + 4 * ct_y1 + 8 * ct_y0;
    std::vector<Ciphertext> gout89 = ctx.eval_lut_amortized(&gin89, lut89);

    std::vector<RotationPoly> lut90;
    lut90.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 226 (LUT3 _1430_ INIT 0x78 PERM 210) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT90   ";
    Ciphertext gin90 = 1 * gout89[0] + 2 * ct_x9 + 4 * ct_y2;
    std::vector<Ciphertext> gout90 = ctx.eval_lut_amortized(&gin90, lut90);

    std::vector<RotationPoly> lut91;
    lut91.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 263 (LUT3 _1467_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut91.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 223 (LUT3 _1427_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT91   ";
    Ciphertext gin91 = 1 * gout34[0] + 2 * gout90[0] + 4 * gout37[0];
    std::vector<Ciphertext> gout91 = ctx.eval_lut_amortized(&gin91, lut91);

    std::vector<RotationPoly> lut92;
    lut92.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 110 (LUT2 _1314_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT92   ";
    Ciphertext gin92 = 1 * gout77[1] + 2 * ct_x7;
    std::vector<Ciphertext> gout92 = ctx.eval_lut_amortized(&gin92, lut92);

    std::vector<RotationPoly> lut93;
    lut93.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 80 (LUT4 _1284_ INIT 0x7f PERM 3120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut93.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 61 (LUT3 _1265_ INIT 0x78 PERM 231) */
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
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT93   ";
    Ciphertext gin93 = 1 * gout21[1] + 2 * gout21[0] + 4 * ct_y5 + 8 * ct_x0;
    std::vector<Ciphertext> gout93 = ctx.eval_lut_amortized(&gin93, lut93);

    std::vector<RotationPoly> lut94;
    lut94.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 107 (LUT2 _1311_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT94   ";
    Ciphertext gin94 = 1 * gout93[0] + 2 * gout11[0];
    std::vector<Ciphertext> gout94 = ctx.eval_lut_amortized(&gin94, lut94);

    std::vector<RotationPoly> lut95;
    lut95.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 196 (LUT4 _1400_ INIT 0x7f PERM 3120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut95.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 159 (LUT3 _1363_ INIT 0x78 PERM 231) */
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
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT95   ";
    Ciphertext gin95 = 1 * gout22[0] + 2 * gout22[1] + 4 * ct_y5 + 8 * ct_x4;
    std::vector<Ciphertext> gout95 = ctx.eval_lut_amortized(&gin95, lut95);

    std::vector<RotationPoly> lut96;
    lut96.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 16 (LUT4 _1220_ INIT 0x8778 PERM 0312) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut96.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 29 (LUT3 _1233_ INIT 0x60 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT96   ";
    Ciphertext gin96 = 1 * ct_y2 + 2 * gout18[1] + 4 * gout87[0] + 8 * ct_x0;
    std::vector<Ciphertext> gout96 = ctx.eval_lut_amortized(&gin96, lut96);

    std::vector<RotationPoly> lut97;
    lut97.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 155 (LUT4 _1359_ INIT 0x7f PERM 2130) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT97   ";
    Ciphertext gin97 = 1 * gout44[1] + 2 * gout44[0] + 4 * ct_x6 + 8 * ct_y2;
    std::vector<Ciphertext> gout97 = ctx.eval_lut_amortized(&gin97, lut97);

    std::vector<RotationPoly> lut98;
    lut98.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 404 (LUT4 _1608_ INIT 0x7f PERM 3021) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut98.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 362 (LUT3 _1566_ INIT 0x78 PERM 230) */
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
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT98   ";
    Ciphertext gin98 = 1 * gout56[1] + 2 * gout56[0] + 4 * ct_y14 + 8 * ct_x0;
    std::vector<Ciphertext> gout98 = ctx.eval_lut_amortized(&gin98, lut98);

    std::vector<RotationPoly> lut99;
    lut99.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 55 (LUT3 _1259_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut99.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 40 (LUT3 _1244_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT99   ";
    Ciphertext gin99 = 1 * gout59[0] + 2 * gout67[1] + 4 * gout2[1];
    std::vector<Ciphertext> gout99 = ctx.eval_lut_amortized(&gin99, lut99);

    std::vector<RotationPoly> lut100;
    lut100.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 185 (LUT3 _1389_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut100.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 154 (LUT3 _1358_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT100   ";
    Ciphertext gin100 = 1 * gout97[0] + 2 * gout43[1] + 4 * gout95[1];
    std::vector<Ciphertext> gout100 = ctx.eval_lut_amortized(&gin100, lut100);

    std::vector<RotationPoly> lut101;
    lut101.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 25 (LUT4 _1229_ INIT 0x7f PERM 3210) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT101   ";
    Ciphertext gin101 = 1 * gout87[1] + 2 * ct_y2 + 4 * gout87[0] + 8 * ct_x0;
    std::vector<Ciphertext> gout101 = ctx.eval_lut_amortized(&gin101, lut101);

    std::vector<RotationPoly> lut102;
    lut102.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 39 (LUT4 _1243_ INIT 0x2bbb PERM 0123) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut102.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 24 (LUT4 _1228_ INIT 0x7887 PERM 2301) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT102   ";
    Ciphertext gin102 = 1 * gout101[0] + 2 * gout59[1] + 4 * ct_y3 + 8 * ct_x0;
    std::vector<Ciphertext> gout102 = ctx.eval_lut_amortized(&gin102, lut102);

    std::vector<RotationPoly> lut103;
    lut103.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 53 (LUT2 _1257_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut103.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 38 (LUT2 _1242_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT103   ";
    Ciphertext gin103 = 1 * gout102[0] + 2 * gout99[1];
    std::vector<Ciphertext> gout103 = ctx.eval_lut_amortized(&gin103, lut103);

    std::vector<RotationPoly> lut104;
    lut104.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 335 (LUT4 _1539_ INIT 0x8000 PERM 0132) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut104.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 302 (LUT4 _1506_ INIT 0x7888 PERM 0213) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT104   ";
    Ciphertext gin104 = 1 * ct_y12 + 2 * ct_y13 + 4 * ct_x1 + 8 * ct_x0;
    std::vector<Ciphertext> gout104 = ctx.eval_lut_amortized(&gin104, lut104);

    std::vector<RotationPoly> lut105;
    lut105.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 390 (LUT4 _1594_ INIT 0x8777 PERM 0123) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT105   ";
    Ciphertext gin105 = 1 * ct_y5 + 2 * ct_x10 + 4 * ct_y6 + 8 * ct_x9;
    std::vector<Ciphertext> gout105 = ctx.eval_lut_amortized(&gin105, lut105);

    std::vector<RotationPoly> lut106;
    lut106.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 389 (LUT3 _1593_ INIT 0x78 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 1;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT106   ";
    Ciphertext gin106 = 1 * ct_y7 + 2 * ct_x8 + 4 * gout105[0];
    std::vector<Ciphertext> gout106 = ctx.eval_lut_amortized(&gin106, lut106);

    std::vector<RotationPoly> lut107;
    lut107.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 367 (LUT3 _1571_ INIT 0xf8 PERM 120) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT107   ";
    Ciphertext gin107 = 1 * gout75[0] + 2 * gout69[1] + 4 * ct_y13;
    std::vector<Ciphertext> gout107 = ctx.eval_lut_amortized(&gin107, lut107);

    std::vector<RotationPoly> lut108;
    lut108.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 374 (LUT3 _1578_ INIT 0xe0 PERM 201) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut108.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 366 (LUT2 _1570_ INIT 0x6 PERM 02) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT108   ";
    Ciphertext gin108 = 1 * gout107[0] + 2 * gout69[1] + 4 * ct_y14;
    std::vector<Ciphertext> gout108 = ctx.eval_lut_amortized(&gin108, lut108);

    std::vector<RotationPoly> lut109;
    lut109.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 373 (LUT3 _1577_ INIT 0x96 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT109   ";
    Ciphertext gin109 = 1 * gout108[0] + 2 * ct_x15 + 4 * ct_y15;
    std::vector<Ciphertext> gout109 = ctx.eval_lut_amortized(&gin109, lut109);

    std::vector<RotationPoly> lut110;
    lut110.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 318 (LUT3 _1522_ INIT 0x78 PERM 120) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT110   ";
    Ciphertext gin110 = 1 * gout88[0] + 2 * ct_y8 + 4 * ct_x5;
    std::vector<Ciphertext> gout110 = ctx.eval_lut_amortized(&gin110, lut110);

    std::vector<RotationPoly> lut111;
    lut111.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 298 (LUT4 _1502_ INIT 0x7f PERM 3120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT111   ";
    Ciphertext gin111 = 1 * gout51[1] + 2 * gout51[0] + 4 * ct_y11 + 8 * ct_x1;
    std::vector<Ciphertext> gout111 = ctx.eval_lut_amortized(&gin111, lut111);

    std::vector<RotationPoly> lut112;
    lut112.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 231 (LUT4 _1435_ INIT 0x7f PERM 3021) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut112.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 198 (LUT3 _1402_ INIT 0x78 PERM 230) */
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
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT112   ";
    Ciphertext gin112 = 1 * gout58[1] + 2 * gout58[0] + 4 * ct_y8 + 8 * ct_x2;
    std::vector<Ciphertext> gout112 = ctx.eval_lut_amortized(&gin112, lut112);

    std::vector<RotationPoly> lut113;
    lut113.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 13 (LUT3 _1217_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT113   ";
    Ciphertext gin113 = 1 * gout70[1] + 2 * gout82[0] + 4 * ct_x2;
    std::vector<Ciphertext> gout113 = ctx.eval_lut_amortized(&gin113, lut113);

    std::vector<RotationPoly> lut114;
    lut114.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 33 (LUT4 _1237_ INIT 0xd400 PERM 0123) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut114.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 21 (LUT4 _1225_ INIT 0x2bd4 PERM 0123) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT114   ";
    Ciphertext gin114 = 1 * gout70[1] + 2 * gout82[0] + 4 * ct_x2 + 8 * gout81[1];
    std::vector<Ciphertext> gout114 = ctx.eval_lut_amortized(&gin114, lut114);

    std::vector<RotationPoly> lut115;
    lut115.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 32 (LUT4 _1236_ INIT 0xe11e PERM 0123) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut115.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 49 (LUT4 _1253_ INIT 0x1117 PERM 2301) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT115   ";
    Ciphertext gin115 = 1 * gout114[0] + 2 * gout81[0] + 4 * gout79[1] + 8 * ct_x4;
    std::vector<Ciphertext> gout115 = ctx.eval_lut_amortized(&gin115, lut115);

    std::vector<RotationPoly> lut116;
    lut116.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 350 (LUT4 _1554_ INIT 0x7f PERM 3021) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut116.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 311 (LUT3 _1515_ INIT 0x78 PERM 230) */
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
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT116   ";
    Ciphertext gin116 = 1 * gout38[1] + 2 * gout38[0] + 4 * ct_y5 + 8 * ct_x8;
    std::vector<Ciphertext> gout116 = ctx.eval_lut_amortized(&gin116, lut116);

    std::vector<RotationPoly> lut117;
    lut117.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 355 (LUT3 _1559_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut117.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 297 (LUT3 _1501_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT117   ";
    Ciphertext gin117 = 1 * gout111[0] + 2 * gout30[0] + 4 * gout104[1];
    std::vector<Ciphertext> gout117 = ctx.eval_lut_amortized(&gin117, lut117);

    std::vector<RotationPoly> lut118;
    lut118.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 194 (LUT4 _1398_ INIT 0x7f PERM 3120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut118.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 166 (LUT3 _1370_ INIT 0x78 PERM 231) */
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
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT118   ";
    Ciphertext gin118 = 1 * gout54[0] + 2 * gout54[1] + 4 * ct_y8 + 8 * ct_x1;
    std::vector<Ciphertext> gout118 = ctx.eval_lut_amortized(&gin118, lut118);

    std::vector<RotationPoly> lut119;
    lut119.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 238 (LUT3 _1442_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut119.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 193 (LUT3 _1397_ INIT 0x96 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT119   ";
    Ciphertext gin119 = 1 * gout118[0] + 2 * gout112[1] + 4 * gout95[0];
    std::vector<Ciphertext> gout119 = ctx.eval_lut_amortized(&gin119, lut119);

    std::vector<RotationPoly> lut120;
    lut120.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 220 (LUT3 _1424_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut120.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 184 (LUT3 _1388_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT120   ";
    Ciphertext gin120 = 1 * gout100[0] + 2 * gout47[0] + 4 * gout119[1];
    std::vector<Ciphertext> gout120 = ctx.eval_lut_amortized(&gin120, lut120);

    std::vector<RotationPoly> lut121;
    lut121.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 352 (LUT3 _1556_ INIT 0x78 PERM 120) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT121   ";
    Ciphertext gin121 = 1 * gout3[0] + 2 * ct_y8 + 4 * ct_x6;
    std::vector<Ciphertext> gout121 = ctx.eval_lut_amortized(&gin121, lut121);

    std::vector<RotationPoly> lut122;
    lut122.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 358 (LUT4 _1562_ INIT 0x7f PERM 3021) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT122   ";
    Ciphertext gin122 = 1 * gout29[0] + 2 * gout29[1] + 4 * ct_y11 + 8 * ct_x2;
    std::vector<Ciphertext> gout122 = ctx.eval_lut_amortized(&gin122, lut122);

    std::vector<RotationPoly> lut123;
    lut123.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 396 (LUT4 _1600_ INIT 0x8777 PERM 0321) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT123   ";
    Ciphertext gin123 = 1 * ct_y11 + 2 * ct_x3 + 4 * ct_y12 + 8 * ct_x4;
    std::vector<Ciphertext> gout123 = ctx.eval_lut_amortized(&gin123, lut123);

    std::vector<RotationPoly> lut124;
    lut124.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 395 (LUT4 _1599_ INIT 0x7887 PERM 0312) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT124   ";
    Ciphertext gin124 = 1 * ct_y10 + 2 * gout123[0] + 4 * gout53[0] + 8 * ct_x5;
    std::vector<Ciphertext> gout124 = ctx.eval_lut_amortized(&gin124, lut124);

    std::vector<RotationPoly> lut125;
    lut125.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 162 (LUT4 _1366_ INIT 0x7f PERM 3120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut125.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 136 (LUT3 _1340_ INIT 0x78 PERM 231) */
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
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT125   ";
    Ciphertext gin125 = 1 * gout64[0] + 2 * gout64[1] + 4 * ct_y8 + 8 * ct_x0;
    std::vector<Ciphertext> gout125 = ctx.eval_lut_amortized(&gin125, lut125);

    std::vector<RotationPoly> lut126;
    lut126.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 169 (LUT3 _1373_ INIT 0x71 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut126.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 132 (LUT3 _1336_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT126   ";
    Ciphertext gin126 = 1 * gout83[0] + 2 * gout28[0] + 4 * gout125[1];
    std::vector<Ciphertext> gout126 = ctx.eval_lut_amortized(&gin126, lut126);

    std::vector<RotationPoly> lut127;
    lut127.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 203 (LUT3 _1407_ INIT 0x40 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut127.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 168 (LUT3 _1372_ INIT 0x87 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT127   ";
    Ciphertext gin127 = 1 * gout126[0] + 2 * ct_y9 + 4 * ct_x0;
    std::vector<Ciphertext> gout127 = ctx.eval_lut_amortized(&gin127, lut127);

    std::vector<RotationPoly> lut128;
    lut128.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 72 (LUT3 _1276_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut128.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 56 (LUT3 _1260_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT128   ";
    Ciphertext gin128 = 1 * gout67[0] + 2 * gout63[0] + 4 * gout93[1];
    std::vector<Ciphertext> gout128 = ctx.eval_lut_amortized(&gin128, lut128);

    std::vector<RotationPoly> lut129;
    lut129.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 93 (LUT4 _1297_ INIT 0x2bb2 PERM 0123) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut129.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 71 (LUT4 _1275_ INIT 0x6996 PERM 0123) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT129   ";
    Ciphertext gin129 = 1 * gout128[0] + 2 * gout66[0] + 4 * gout93[0] + 8 * gout11[0];
    std::vector<Ciphertext> gout129 = ctx.eval_lut_amortized(&gin129, lut129);

    std::vector<RotationPoly> lut130;
    lut130.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 70 (LUT3 _1274_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut130.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 54 (LUT3 _1258_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT130   ";
    Ciphertext gin130 = 1 * gout99[0] + 2 * gout128[1] + 4 * gout2[0];
    std::vector<Ciphertext> gout130 = ctx.eval_lut_amortized(&gin130, lut130);

    std::vector<RotationPoly> lut131;
    lut131.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 91 (LUT2 _1295_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut131.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 69 (LUT2 _1273_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT131   ";
    Ciphertext gin131 = 1 * gout130[0] + 2 * gout129[1];
    std::vector<Ciphertext> gout131 = ctx.eval_lut_amortized(&gin131, lut131);

    std::vector<RotationPoly> lut132;
    lut132.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 68 (LUT2 _1272_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut132.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 52 (LUT2 _1256_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT132   ";
    Ciphertext gin132 = 1 * gout103[0] + 2 * gout130[1];
    std::vector<Ciphertext> gout132 = ctx.eval_lut_amortized(&gin132, lut132);

    std::vector<RotationPoly> lut133;
    lut133.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 89 (LUT2 _1293_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut133.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 67 (LUT2 _1271_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT133   ";
    Ciphertext gin133 = 1 * gout132[0] + 2 * gout131[1];
    std::vector<Ciphertext> gout133 = ctx.eval_lut_amortized(&gin133, lut133);

    std::vector<RotationPoly> lut134;
    lut134.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 265 (LUT4 _1469_ INIT 0x7f PERM 2130) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT134   ";
    Ciphertext gin134 = 1 * gout89[1] + 2 * gout89[0] + 4 * ct_x9 + 8 * ct_y2;
    std::vector<Ciphertext> gout134 = ctx.eval_lut_amortized(&gin134, lut134);

    std::vector<RotationPoly> lut135;
    lut135.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 383 (LUT4 _1587_ INIT 0x7f PERM 3021) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut135.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 343 (LUT3 _1547_ INIT 0x78 PERM 230) */
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
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT135   ";
    Ciphertext gin135 = 1 * gout15[1] + 2 * gout15[0] + 4 * ct_y2 + 8 * ct_x12;
    std::vector<Ciphertext> gout135 = ctx.eval_lut_amortized(&gin135, lut135);

    std::vector<RotationPoly> lut136;
    lut136.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 382 (LUT3 _1586_ INIT 0x87 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT136   ";
    Ciphertext gin136 = 1 * gout135[0] + 2 * ct_y4 + 4 * ct_x11;
    std::vector<Ciphertext> gout136 = ctx.eval_lut_amortized(&gin136, lut136);

    std::vector<RotationPoly> lut137;
    lut137.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 340 (LUT3 _1544_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT137   ";
    Ciphertext gin137 = 1 * gout46[0] + 2 * gout135[1] + 4 * gout48[1];
    std::vector<Ciphertext> gout137 = ctx.eval_lut_amortized(&gin137, lut137);

    std::vector<RotationPoly> lut138;
    lut138.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 241 (LUT4 _1445_ INIT 0x7888 PERM 0213) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT138   ";
    Ciphertext gin138 = 1 * ct_y9 + 2 * ct_y10 + 4 * ct_x2 + 8 * ct_x1;
    std::vector<Ciphertext> gout138 = ctx.eval_lut_amortized(&gin138, lut138);

    std::vector<RotationPoly> lut139;
    lut139.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 259 (LUT3 _1463_ INIT 0x60 PERM 201) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT139   ";
    Ciphertext gin139 = 1 * gout138[0] + 2 * gout57[0] + 4 * ct_y11;
    std::vector<Ciphertext> gout139 = ctx.eval_lut_amortized(&gin139, lut139);

    std::vector<RotationPoly> lut140;
    lut140.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 255 (LUT4 _1459_ INIT 0x7f PERM 3120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT140   ";
    Ciphertext gin140 = 1 * gout17[0] + 2 * gout138[0] + 4 * ct_y11 + 8 * ct_x0;
    std::vector<Ciphertext> gout140 = ctx.eval_lut_amortized(&gin140, lut140);

    std::vector<RotationPoly> lut141;
    lut141.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 295 (LUT4 _1499_ INIT 0x2bbb PERM 0123) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut141.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 254 (LUT4 _1458_ INIT 0x7887 PERM 2301) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT141   ";
    Ciphertext gin141 = 1 * gout140[0] + 2 * gout52[0] + 4 * ct_y12 + 8 * ct_x0;
    std::vector<Ciphertext> gout141 = ctx.eval_lut_amortized(&gin141, lut141);

    std::vector<RotationPoly> lut142;
    lut142.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 239 (LUT4 _1443_ INIT 0x8778 PERM 2310) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT142   ";
    Ciphertext gin142 = 1 * gout138[0] + 2 * gout57[0] + 4 * ct_y11 + 8 * ct_x0;
    std::vector<Ciphertext> gout142 = ctx.eval_lut_amortized(&gin142, lut142);

    std::vector<RotationPoly> lut143;
    lut143.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 279 (LUT2 _1483_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut143.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 237 (LUT2 _1441_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT143   ";
    Ciphertext gin143 = 1 * gout119[0] + 2 * gout142[0];
    std::vector<Ciphertext> gout143 = ctx.eval_lut_amortized(&gin143, lut143);

    std::vector<RotationPoly> lut144;
    lut144.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 171 (LUT3 _1375_ INIT 0x60 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut144.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 140 (LUT3 _1344_ INIT 0x96 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT144   ";
    Ciphertext gin144 = 1 * gout77[2] + 2 * ct_x8 + 4 * ct_y8;
    std::vector<Ciphertext> gout144 = ctx.eval_lut_amortized(&gin144, lut144);

    std::vector<RotationPoly> lut145;
    lut145.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 205 (LUT4 _1409_ INIT 0x8ee8 PERM 3102) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 1;
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT145   ";
    Ciphertext gin145 = 1 * gout77[0] + 2 * ct_x9 + 4 * ct_y9 + 8 * gout144[0];
    std::vector<Ciphertext> gout145 = ctx.eval_lut_amortized(&gin145, lut145);

    std::vector<RotationPoly> lut146;
    lut146.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 307 (LUT4 _1511_ INIT 0x7f PERM 2031) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut146.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 267 (LUT3 _1471_ INIT 0x78 PERM 320) */
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
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT146   ";
    Ciphertext gin146 = 1 * gout55[1] + 2 * gout55[0] + 4 * ct_x10 + 8 * ct_y2;
    std::vector<Ciphertext> gout146 = ctx.eval_lut_amortized(&gin146, lut146);

    std::vector<RotationPoly> lut147;
    lut147.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 339 (LUT3 _1543_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut147.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 306 (LUT3 _1510_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT147   ";
    Ciphertext gin147 = 1 * gout146[0] + 2 * gout46[1] + 4 * gout116[1];
    std::vector<Ciphertext> gout147 = ctx.eval_lut_amortized(&gin147, lut147);

    std::vector<RotationPoly> lut148;
    lut148.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 305 (LUT3 _1509_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut148.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 264 (LUT3 _1468_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT148   ";
    Ciphertext gin148 = 1 * gout134[0] + 2 * gout146[1] + 4 * gout25[1];
    std::vector<Ciphertext> gout148 = ctx.eval_lut_amortized(&gin148, lut148);

    std::vector<RotationPoly> lut149;
    lut149.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 244 (LUT3 _1448_ INIT 0x60 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut149.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 206 (LUT3 _1410_ INIT 0x96 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT149   ";
    Ciphertext gin149 = 1 * gout73[1] + 2 * ct_x10 + 4 * ct_y10;
    std::vector<Ciphertext> gout149 = ctx.eval_lut_amortized(&gin149, lut149);

    std::vector<RotationPoly> lut150;
    lut150.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 284 (LUT4 _1488_ INIT 0x8ee8 PERM 3102) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 1;
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut150.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 245 (LUT3 _1449_ INIT 0x96 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT150   ";
    Ciphertext gin150 = 1 * gout73[0] + 2 * ct_x11 + 4 * ct_y11 + 8 * gout149[0];
    std::vector<Ciphertext> gout150 = ctx.eval_lut_amortized(&gin150, lut150);

    std::vector<RotationPoly> lut151;
    lut151.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 164 (LUT4 _1368_ INIT 0x7f PERM 3120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT151   ";
    Ciphertext gin151 = 1 * gout10[0] + 2 * gout10[1] + 4 * ct_y5 + 8 * ct_x3;
    std::vector<Ciphertext> gout151 = ctx.eval_lut_amortized(&gin151, lut151);

    std::vector<RotationPoly> lut152;
    lut152.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 161 (LUT3 _1365_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut152.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 201 (LUT3 _1405_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT152   ";
    Ciphertext gin152 = 1 * gout125[0] + 2 * gout151[0] + 4 * gout118[1];
    std::vector<Ciphertext> gout152 = ctx.eval_lut_amortized(&gin152, lut152);

    std::vector<RotationPoly> lut153;
    lut153.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 401 (LUT4 _1605_ INIT 0x8778 PERM 3012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT153   ";
    Ciphertext gin153 = 1 * ct_x15 + 2 * gout16[0] + 4 * ct_y15 + 8 * ct_y0;
    std::vector<Ciphertext> gout153 = ctx.eval_lut_amortized(&gin153, lut153);

    std::vector<RotationPoly> lut154;
    lut154.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 400 (LUT3 _1604_ INIT 0x87 PERM 201) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT154   ";
    Ciphertext gin154 = 1 * ct_x14 + 2 * gout153[0] + 4 * ct_y1;
    std::vector<Ciphertext> gout154 = ctx.eval_lut_amortized(&gin154, lut154);

    std::vector<RotationPoly> lut155;
    lut155.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 399 (LUT4 _1603_ INIT 0xd42b PERM 0123) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT155   ";
    Ciphertext gin155 = 1 * gout46[0] + 2 * gout135[1] + 4 * gout48[1] + 8 * gout154[0];
    std::vector<Ciphertext> gout155 = ctx.eval_lut_amortized(&gin155, lut155);

    std::vector<RotationPoly> lut156;
    lut156.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 387 (LUT4 _1591_ INIT 0x7f PERM 3021) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT156   ";
    Ciphertext gin156 = 1 * gout3[0] + 2 * gout3[1] + 4 * ct_y8 + 8 * ct_x6;
    std::vector<Ciphertext> gout156 = ctx.eval_lut_amortized(&gin156, lut156);

    std::vector<RotationPoly> lut157;
    lut157.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 381 (LUT4 _1585_ INIT 0x6996 PERM 0123) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT157   ";
    Ciphertext gin157 = 1 * gout136[0] + 2 * gout48[0] + 4 * gout156[0] + 8 * gout106[0];
    std::vector<Ciphertext> gout157 = ctx.eval_lut_amortized(&gin157, lut157);

    std::vector<RotationPoly> lut158;
    lut158.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 109 (LUT4 _1313_ INIT 0xd400 PERM 1230) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut158.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 83 (LUT4 _1287_ INIT 0x2bd4 PERM 1230) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut158.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 48 (LUT3 _1252_ INIT 0x69 PERM 123) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT158   ";
    Ciphertext gin158 = 1 * gout80[1] + 2 * gout115[1] + 4 * gout86[0] + 8 * ct_x5;
    std::vector<Ciphertext> gout158 = ctx.eval_lut_amortized(&gin158, lut158);

    std::vector<RotationPoly> lut159;
    lut159.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 139 (LUT4 _1343_ INIT 0x1117 PERM 0123) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT159   ";
    Ciphertext gin159 = 1 * gout77[1] + 2 * ct_x7 + 4 * gout158[0] + 8 * gout80[0];
    std::vector<Ciphertext> gout159 = ctx.eval_lut_amortized(&gin159, lut159);

    std::vector<RotationPoly> lut160;
    lut160.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 204 (LUT4 _1408_ INIT 0xbf PERM 2310) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT160   ";
    Ciphertext gin160 = 1 * gout145[0] + 2 * gout78[0] + 4 * gout159[0] + 8 * gout144[1];
    std::vector<Ciphertext> gout160 = ctx.eval_lut_amortized(&gin160, lut160);

    std::vector<RotationPoly> lut161;
    lut161.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 170 (LUT4 _1374_ INIT 0xbf4 PERM 2301) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT161   ";
    Ciphertext gin161 = 1 * gout144[0] + 2 * gout78[0] + 4 * gout159[0] + 8 * gout144[1];
    std::vector<Ciphertext> gout161 = ctx.eval_lut_amortized(&gin161, lut161);

    std::vector<RotationPoly> lut162;
    lut162.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 37 (LUT2 _1241_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT162   ";
    Ciphertext gin162 = 1 * gout102[1] + 2 * gout96[1];
    std::vector<Ciphertext> gout162 = ctx.eval_lut_amortized(&gin162, lut162);

    std::vector<RotationPoly> lut163;
    lut163.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 51 (LUT2 _1255_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT163   ";
    Ciphertext gin163 = 1 * gout162[0] + 2 * gout103[1];
    std::vector<Ciphertext> gout163 = ctx.eval_lut_amortized(&gin163, lut163);

    std::vector<RotationPoly> lut164;
    lut164.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 66 (LUT2 _1270_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT164   ";
    Ciphertext gin164 = 1 * gout163[0] + 2 * gout132[1];
    std::vector<Ciphertext> gout164 = ctx.eval_lut_amortized(&gin164, lut164);

    std::vector<RotationPoly> lut165;
    lut165.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 88 (LUT2 _1292_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT165   ";
    Ciphertext gin165 = 1 * gout164[0] + 2 * gout133[1];
    std::vector<Ciphertext> gout165 = ctx.eval_lut_amortized(&gin165, lut165);

    std::vector<RotationPoly> lut166;
    lut166.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 65 (LUT4 _1269_ INIT 0x3caa PERM 0123) */
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
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT166   ";
    Ciphertext gin166 = 1 * gout158[1] + 2 * gout164[0] + 4 * gout133[1] + 8 * gout72[0];
    std::vector<Ciphertext> gout166 = ctx.eval_lut_amortized(&gin166, lut166);

    std::vector<RotationPoly> lut167;
    lut167.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 47 (LUT4 _1251_ INIT 0x3caa PERM 0123) */
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
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT167   ";
    Ciphertext gin167 = 1 * gout158[2] + 2 * gout163[0] + 4 * gout132[1] + 8 * gout72[0];
    std::vector<Ciphertext> gout167 = ctx.eval_lut_amortized(&gin167, lut167);

    std::vector<RotationPoly> lut168;
    lut168.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 31 (LUT4 _1235_ INIT 0x3caa PERM 0123) */
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
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT168   ";
    Ciphertext gin168 = 1 * gout115[0] + 2 * gout162[0] + 4 * gout103[1] + 8 * gout72[0];
    std::vector<Ciphertext> gout168 = ctx.eval_lut_amortized(&gin168, lut168);

    std::vector<RotationPoly> lut169;
    lut169.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 20 (LUT4 _1224_ INIT 0x3caa PERM 0123) */
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
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT169   ";
    Ciphertext gin169 = 1 * gout114[1] + 2 * gout102[1] + 4 * gout96[1] + 8 * gout72[0];
    std::vector<Ciphertext> gout169 = ctx.eval_lut_amortized(&gin169, lut169);

    std::vector<RotationPoly> lut170;
    lut170.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 380 (LUT4 _1584_ INIT 0xd42b PERM 0123) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut170.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 357 (LUT3 _1561_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT170   ";
    Ciphertext gin170 = 1 * gout122[0] + 2 * gout42[0] + 4 * gout98[1] + 8 * gout157[0];
    std::vector<Ciphertext> gout170 = ctx.eval_lut_amortized(&gin170, lut170);

    std::vector<RotationPoly> lut171;
    lut171.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 272 (LUT4 _1476_ INIT 0x7f PERM 2031) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut171.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 235 (LUT3 _1439_ INIT 0x78 PERM 320) */
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
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT171   ";
    Ciphertext gin171 = 1 * gout4[1] + 2 * gout4[0] + 4 * ct_x3 + 8 * ct_y8;
    std::vector<Ciphertext> gout171 = ctx.eval_lut_amortized(&gin171, lut171);

    std::vector<RotationPoly> lut172;
    lut172.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 260 (LUT3 _1464_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut172.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 230 (LUT3 _1434_ INIT 0x96 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT172   ";
    Ciphertext gin172 = 1 * gout112[0] + 2 * gout171[1] + 4 * gout40[0];
    std::vector<Ciphertext> gout172 = ctx.eval_lut_amortized(&gin172, lut172);

    std::vector<RotationPoly> lut173;
    lut173.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 320 (LUT3 _1524_ INIT 0x71 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut173.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 253 (LUT3 _1457_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT173   ";
    Ciphertext gin173 = 1 * gout141[1] + 2 * gout139[0] + 4 * gout172[0];
    std::vector<Ciphertext> gout173 = ctx.eval_lut_amortized(&gin173, lut173);

    std::vector<RotationPoly> lut174;
    lut174.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 261 (LUT3 _1465_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut174.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 221 (LUT3 _1425_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT174   ";
    Ciphertext gin174 = 1 * gout47[1] + 2 * gout91[1] + 4 * gout172[1];
    std::vector<Ciphertext> gout174 = ctx.eval_lut_amortized(&gin174, lut174);

    std::vector<RotationPoly> lut175;
    lut175.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 278 (LUT3 _1482_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut175.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 219 (LUT3 _1423_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT175   ";
    Ciphertext gin175 = 1 * gout120[0] + 2 * gout174[1] + 4 * gout143[1];
    std::vector<Ciphertext> gout175 = ctx.eval_lut_amortized(&gin175, lut175);

    std::vector<RotationPoly> lut176;
    lut176.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 108 (LUT3 _1312_ INIT 0x1e PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 1;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT176   ";
    Ciphertext gin176 = 1 * gout158[0] + 2 * gout80[0] + 4 * gout92[0];
    std::vector<Ciphertext> gout176 = ctx.eval_lut_amortized(&gin176, lut176);

    std::vector<RotationPoly> lut177;
    lut177.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 126 (LUT4 _1330_ INIT 0x7f PERM 3120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut177.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 99 (LUT3 _1303_ INIT 0x78 PERM 231) */
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
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT177   ";
    Ciphertext gin177 = 1 * gout8[0] + 2 * gout8[1] + 4 * ct_y2 + 8 * ct_x5;
    std::vector<Ciphertext> gout177 = ctx.eval_lut_amortized(&gin177, lut177);

    std::vector<RotationPoly> lut178;
    lut178.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 153 (LUT3 _1357_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut178.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 125 (LUT3 _1329_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT178   ";
    Ciphertext gin178 = 1 * gout177[0] + 2 * gout45[0] + 4 * gout62[0];
    std::vector<Ciphertext> gout178 = ctx.eval_lut_amortized(&gin178, lut178);

    std::vector<RotationPoly> lut179;
    lut179.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 183 (LUT3 _1387_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut179.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 152 (LUT3 _1356_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT179   ";
    Ciphertext gin179 = 1 * gout178[0] + 2 * gout100[1] + 4 * gout152[0];
    std::vector<Ciphertext> gout179 = ctx.eval_lut_amortized(&gin179, lut179);

    std::vector<RotationPoly> lut180;
    lut180.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 124 (LUT3 _1328_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut180.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 96 (LUT3 _1300_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT180   ";
    Ciphertext gin180 = 1 * gout31[0] + 2 * gout177[1] + 4 * gout28[1];
    std::vector<Ciphertext> gout180 = ctx.eval_lut_amortized(&gin180, lut180);

    std::vector<RotationPoly> lut181;
    lut181.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 151 (LUT3 _1355_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut181.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 123 (LUT3 _1327_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT181   ";
    Ciphertext gin181 = 1 * gout180[0] + 2 * gout178[1] + 4 * gout126[1];
    std::vector<Ciphertext> gout181 = ctx.eval_lut_amortized(&gin181, lut181);

    std::vector<RotationPoly> lut182;
    lut182.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 181 (LUT3 _1385_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut182.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 150 (LUT3 _1354_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT182   ";
    Ciphertext gin182 = 1 * gout181[0] + 2 * gout179[1] + 4 * gout127[1];
    std::vector<Ciphertext> gout182 = ctx.eval_lut_amortized(&gin182, lut182);

    std::vector<RotationPoly> lut183;
    lut183.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 122 (LUT3 _1326_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut183.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 94 (LUT3 _1298_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT183   ";
    Ciphertext gin183 = 1 * gout66[1] + 2 * gout180[1] + 4 * gout85[1];
    std::vector<Ciphertext> gout183 = ctx.eval_lut_amortized(&gin183, lut183);

    std::vector<RotationPoly> lut184;
    lut184.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 149 (LUT3 _1353_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut184.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 121 (LUT3 _1325_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT184   ";
    Ciphertext gin184 = 1 * gout183[0] + 2 * gout181[1] + 4 * gout85[0];
    std::vector<Ciphertext> gout184 = ctx.eval_lut_amortized(&gin184, lut184);

    std::vector<RotationPoly> lut185;
    lut185.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 179 (LUT2 _1383_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut185.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 148 (LUT2 _1352_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT185   ";
    Ciphertext gin185 = 1 * gout184[0] + 2 * gout182[1];
    std::vector<Ciphertext> gout185 = ctx.eval_lut_amortized(&gin185, lut185);

    std::vector<RotationPoly> lut186;
    lut186.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 120 (LUT3 _1324_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut186.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 92 (LUT3 _1296_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT186   ";
    Ciphertext gin186 = 1 * gout129[0] + 2 * gout183[1] + 4 * gout94[0];
    std::vector<Ciphertext> gout186 = ctx.eval_lut_amortized(&gin186, lut186);

    std::vector<RotationPoly> lut187;
    lut187.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 147 (LUT2 _1351_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut187.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 119 (LUT2 _1323_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT187   ";
    Ciphertext gin187 = 1 * gout186[0] + 2 * gout184[1];
    std::vector<Ciphertext> gout187 = ctx.eval_lut_amortized(&gin187, lut187);

    std::vector<RotationPoly> lut188;
    lut188.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 178 (LUT2 _1382_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut188.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 146 (LUT2 _1350_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT188   ";
    Ciphertext gin188 = 1 * gout187[0] + 2 * gout185[1];
    std::vector<Ciphertext> gout188 = ctx.eval_lut_amortized(&gin188, lut188);

    std::vector<RotationPoly> lut189;
    lut189.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 118 (LUT2 _1322_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut189.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 90 (LUT2 _1294_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT189   ";
    Ciphertext gin189 = 1 * gout131[0] + 2 * gout186[1];
    std::vector<Ciphertext> gout189 = ctx.eval_lut_amortized(&gin189, lut189);

    std::vector<RotationPoly> lut190;
    lut190.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 145 (LUT2 _1349_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut190.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 117 (LUT2 _1321_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT190   ";
    Ciphertext gin190 = 1 * gout189[0] + 2 * gout187[1];
    std::vector<Ciphertext> gout190 = ctx.eval_lut_amortized(&gin190, lut190);

    std::vector<RotationPoly> lut191;
    lut191.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 144 (LUT4 _1348_ INIT 0x17ff PERM 1023) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            case  8: return 1;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut191.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 116 (LUT4 _1320_ INIT 0xd728 PERM 3120) */
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
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut191.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 87 (LUT3 _1291_ INIT 0x1e PERM 123) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT191   ";
    Ciphertext gin191 = 1 * gout190[1] + 2 * gout165[0] + 4 * gout133[0] + 8 * gout189[1];
    std::vector<Ciphertext> gout191 = ctx.eval_lut_amortized(&gin191, lut191);

    std::vector<RotationPoly> lut192;
    lut192.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 143 (LUT4 _1347_ INIT 0x6900 PERM 0123) */
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
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT192   ";
    Ciphertext gin192 = 1 * gout191[0] + 2 * gout190[0] + 4 * gout188[1] + 8 * gout72[0];
    std::vector<Ciphertext> gout192 = ctx.eval_lut_amortized(&gin192, lut192);

    std::vector<RotationPoly> lut193;
    lut193.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 115 (LUT4 _1319_ INIT 0xaac3 PERM 0123) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
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
    }));

    std::cerr << "\rLUT193   ";
    Ciphertext gin193 = 1 * gout191[1] + 2 * gout159[0] + 4 * gout144[1] + 8 * gout72[0];
    std::vector<Ciphertext> gout193 = ctx.eval_lut_amortized(&gin193, lut193);

    std::vector<RotationPoly> lut194;
    lut194.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 393 (LUT4 _1597_ INIT 0x7f PERM 3021) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT194   ";
    Ciphertext gin194 = 1 * gout20[1] + 2 * gout20[0] + 4 * ct_y11 + 8 * ct_x3;
    std::vector<Ciphertext> gout194 = ctx.eval_lut_amortized(&gin194, lut194);

    std::vector<RotationPoly> lut195;
    lut195.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 392 (LUT3 _1596_ INIT 0x87 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT195   ";
    Ciphertext gin195 = 1 * gout194[0] + 2 * ct_y13 + 4 * ct_x2;
    std::vector<Ciphertext> gout195 = ctx.eval_lut_amortized(&gin195, lut195);

    std::vector<RotationPoly> lut196;
    lut196.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 348 (LUT4 _1552_ INIT 0x7f PERM 3021) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT196   ";
    Ciphertext gin196 = 1 * gout88[0] + 2 * gout88[1] + 4 * ct_y8 + 8 * ct_x5;
    std::vector<Ciphertext> gout196 = ctx.eval_lut_amortized(&gin196, lut196);

    std::vector<RotationPoly> lut197;
    lut197.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 391 (LUT3 _1595_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut197.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 347 (LUT3 _1551_ INIT 0x96 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT197   ";
    Ciphertext gin197 = 1 * gout196[0] + 2 * gout121[0] + 4 * gout116[0];
    std::vector<Ciphertext> gout197 = ctx.eval_lut_amortized(&gin197, lut197);

    std::vector<RotationPoly> lut198;
    lut198.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 379 (LUT4 _1583_ INIT 0x9669 PERM 0123) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT198   ";
    Ciphertext gin198 = 1 * gout170[0] + 2 * gout197[0] + 4 * gout195[0] + 8 * gout124[0];
    std::vector<Ciphertext> gout198 = ctx.eval_lut_amortized(&gin198, lut198);

    std::vector<RotationPoly> lut199;
    lut199.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 398 (LUT4 _1602_ INIT 0xd42b PERM 0123) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut199.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 338 (LUT3 _1542_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT199   ";
    Ciphertext gin199 = 1 * gout147[0] + 2 * gout137[0] + 4 * gout197[1] + 8 * gout155[0];
    std::vector<Ciphertext> gout199 = ctx.eval_lut_amortized(&gin199, lut199);

    std::vector<RotationPoly> lut200;
    lut200.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 314 (LUT4 _1518_ INIT 0x7f PERM 3120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT200   ";
    Ciphertext gin200 = 1 * gout49[1] + 2 * gout49[0] + 4 * ct_y8 + 8 * ct_x4;
    std::vector<Ciphertext> gout200 = ctx.eval_lut_amortized(&gin200, lut200);

    std::vector<RotationPoly> lut201;
    lut201.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 356 (LUT3 _1560_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut201.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 313 (LUT3 _1517_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT201   ";
    Ciphertext gin201 = 1 * gout200[0] + 2 * gout25[0] + 4 * gout110[0];
    std::vector<Ciphertext> gout201 = ctx.eval_lut_amortized(&gin201, lut201);

    std::vector<RotationPoly> lut202;
    lut202.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 403 (LUT4 _1607_ INIT 0x718e PERM 0123) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut202.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 354 (LUT3 _1558_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT202   ";
    Ciphertext gin202 = 1 * gout117[0] + 2 * gout201[0] + 4 * gout170[1] + 8 * gout98[0];
    std::vector<Ciphertext> gout202 = ctx.eval_lut_amortized(&gin202, lut202);

    std::vector<RotationPoly> lut203;
    lut203.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 337 (LUT3 _1541_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut203.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 304 (LUT3 _1508_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT203   ";
    Ciphertext gin203 = 1 * gout148[0] + 2 * gout147[1] + 4 * gout201[1];
    std::vector<Ciphertext> gout203 = ctx.eval_lut_amortized(&gin203, lut203);

    std::vector<RotationPoly> lut204;
    lut204.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 378 (LUT4 _1582_ INIT 0xd42b PERM 0123) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut204.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 336 (LUT3 _1540_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT204   ";
    Ciphertext gin204 = 1 * gout203[0] + 2 * gout199[1] + 4 * gout202[1] + 8 * gout198[0];
    std::vector<Ciphertext> gout204 = ctx.eval_lut_amortized(&gin204, lut204);

    std::vector<RotationPoly> lut205;
    lut205.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 377 (LUT4 _1581_ INIT 0x6996 PERM 0123) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT205   ";
    Ciphertext gin205 = 1 * gout204[0] + 2 * gout199[0] + 4 * gout202[0] + 8 * gout13[0];
    std::vector<Ciphertext> gout205 = ctx.eval_lut_amortized(&gin205, lut205);

    std::vector<RotationPoly> lut206;
    lut206.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 274 (LUT4 _1478_ INIT 0x7f PERM 3021) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT206   ";
    Ciphertext gin206 = 1 * gout36[0] + 2 * gout36[1] + 4 * ct_y5 + 8 * ct_x6;
    std::vector<Ciphertext> gout206 = ctx.eval_lut_amortized(&gin206, lut206);

    std::vector<RotationPoly> lut207;
    lut207.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 296 (LUT3 _1500_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut207.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 271 (LUT3 _1475_ INIT 0x96 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT207   ";
    Ciphertext gin207 = 1 * gout171[0] + 2 * gout50[0] + 4 * gout206[0];
    std::vector<Ciphertext> gout207 = ctx.eval_lut_amortized(&gin207, lut207);

    std::vector<RotationPoly> lut208;
    lut208.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 334 (LUT3 _1538_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut208.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 294 (LUT3 _1498_ INIT 0x96 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT208   ";
    Ciphertext gin208 = 1 * gout141[0] + 2 * gout117[1] + 4 * gout207[0];
    std::vector<Ciphertext> gout208 = ctx.eval_lut_amortized(&gin208, lut208);

    std::vector<RotationPoly> lut209;
    lut209.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 333 (LUT2 _1537_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT209   ";
    Ciphertext gin209 = 1 * gout208[0] + 2 * gout104[0];
    std::vector<Ciphertext> gout209 = ctx.eval_lut_amortized(&gin209, lut209);

    std::vector<RotationPoly> lut210;
    lut210.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 303 (LUT3 _1507_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut210.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 262 (LUT3 _1466_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT210   ";
    Ciphertext gin210 = 1 * gout91[0] + 2 * gout148[1] + 4 * gout207[1];
    std::vector<Ciphertext> gout210 = ctx.eval_lut_amortized(&gin210, lut210);

    std::vector<RotationPoly> lut211;
    lut211.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 332 (LUT3 _1536_ INIT 0x71 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut211.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 293 (LUT3 _1497_ INIT 0x69 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT211   ";
    Ciphertext gin211 = 1 * gout208[1] + 2 * gout203[1] + 4 * gout210[0];
    std::vector<Ciphertext> gout211 = ctx.eval_lut_amortized(&gin211, lut211);

    std::vector<RotationPoly> lut212;
    lut212.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 376 (LUT4 _1580_ INIT 0x2bd4 PERM 0123) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut212.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 331 (LUT3 _1535_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT212   ";
    Ciphertext gin212 = 1 * gout211[0] + 2 * gout209[0] + 4 * gout204[1] + 8 * gout205[0];
    std::vector<Ciphertext> gout212 = ctx.eval_lut_amortized(&gin212, lut212);

    std::vector<RotationPoly> lut213;
    lut213.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 292 (LUT3 _1496_ INIT 0x71 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut213.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 252 (LUT3 _1456_ INIT 0x69 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT213   ";
    Ciphertext gin213 = 1 * gout173[1] + 2 * gout210[1] + 4 * gout174[0];
    std::vector<Ciphertext> gout213 = ctx.eval_lut_amortized(&gin213, lut213);

    std::vector<RotationPoly> lut214;
    lut214.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 330 (LUT3 _1534_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut214.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 291 (LUT3 _1495_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT214   ";
    Ciphertext gin214 = 1 * gout213[0] + 2 * gout211[1] + 4 * gout173[0];
    std::vector<Ciphertext> gout214 = ctx.eval_lut_amortized(&gin214, lut214);

    std::vector<RotationPoly> lut215;
    lut215.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 407 (LUT4 _1611_ INIT 0x9caf PERM 0123) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut215.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 329 (LUT2 _1533_ INIT 0x9 PERM 02) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT215   ";
    Ciphertext gin215 = 1 * gout214[0] + 2 * gout208[0] + 4 * gout212[1] + 8 * gout104[0];
    std::vector<Ciphertext> gout215 = ctx.eval_lut_amortized(&gin215, lut215);

    std::vector<RotationPoly> lut216;
    lut216.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 375 (LUT2 _1579_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT216   ";
    Ciphertext gin216 = 1 * gout212[0] + 2 * gout215[0];
    std::vector<Ciphertext> gout216 = ctx.eval_lut_amortized(&gin216, lut216);

    std::vector<RotationPoly> lut217;
    lut217.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 290 (LUT3 _1494_ INIT 0x71 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut217.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 251 (LUT3 _1455_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT217   ";
    Ciphertext gin217 = 1 * gout213[1] + 2 * gout175[0] + 4 * gout143[0];
    std::vector<Ciphertext> gout217 = ctx.eval_lut_amortized(&gin217, lut217);

    std::vector<RotationPoly> lut218;
    lut218.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 327 (LUT2 _1531_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT218   ";
    Ciphertext gin218 = 1 * gout217[0] + 2 * gout214[1];
    std::vector<Ciphertext> gout218 = ctx.eval_lut_amortized(&gin218, lut218);

    std::vector<RotationPoly> lut219;
    lut219.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 2 (LUT2 _1206_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT219   ";
    Ciphertext gin219 = 1 * gout69[1] + 2 * gout71[0];
    std::vector<Ciphertext> gout219 = ctx.eval_lut_amortized(&gin219, lut219);

    std::vector<RotationPoly> lut220;
    lut220.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 142 (LUT4 _1346_ INIT 0xfff4 PERM 2031) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
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
    }));

    std::cerr << "\rLUT220   ";
    Ciphertext gin220 = 1 * gout161[0] + 2 * gout192[0] + 4 * gout72[0] + 8 * gout219[0];
    std::vector<Ciphertext> gout220 = ctx.eval_lut_amortized(&gin220, lut220);

    std::vector<RotationPoly> lut221;
    lut221.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 114 (LUT2 _1318_ INIT 0xe PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT221   ";
    Ciphertext gin221 = 1 * gout193[0] + 2 * gout219[0];
    std::vector<Ciphertext> gout221 = ctx.eval_lut_amortized(&gin221, lut221);

    std::vector<RotationPoly> lut222;
    lut222.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 86 (LUT4 _1290_ INIT 0xfcfa PERM 0132) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
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
    }));

    std::cerr << "\rLUT222   ";
    Ciphertext gin222 = 1 * gout176[0] + 2 * gout191[2] + 4 * gout72[0] + 8 * gout219[0];
    std::vector<Ciphertext> gout222 = ctx.eval_lut_amortized(&gin222, lut222);

    std::vector<RotationPoly> lut223;
    lut223.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 64 (LUT2 _1268_ INIT 0xe PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT223   ";
    Ciphertext gin223 = 1 * gout166[0] + 2 * gout219[0];
    std::vector<Ciphertext> gout223 = ctx.eval_lut_amortized(&gin223, lut223);

    std::vector<RotationPoly> lut224;
    lut224.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 46 (LUT2 _1250_ INIT 0xe PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT224   ";
    Ciphertext gin224 = 1 * gout167[0] + 2 * gout219[0];
    std::vector<Ciphertext> gout224 = ctx.eval_lut_amortized(&gin224, lut224);

    std::vector<RotationPoly> lut225;
    lut225.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 30 (LUT2 _1234_ INIT 0xe PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT225   ";
    Ciphertext gin225 = 1 * gout168[0] + 2 * gout219[0];
    std::vector<Ciphertext> gout225 = ctx.eval_lut_amortized(&gin225, lut225);

    std::vector<RotationPoly> lut226;
    lut226.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 19 (LUT2 _1223_ INIT 0xe PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT226   ";
    Ciphertext gin226 = 1 * gout169[0] + 2 * gout219[0];
    std::vector<Ciphertext> gout226 = ctx.eval_lut_amortized(&gin226, lut226);

    std::vector<RotationPoly> lut227;
    lut227.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 12 (LUT4 _1216_ INIT 0xfafc PERM 0132) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
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
    }));

    std::cerr << "\rLUT227   ";
    Ciphertext gin227 = 1 * gout96[0] + 2 * gout113[0] + 4 * gout72[0] + 8 * gout219[0];
    std::vector<Ciphertext> gout227 = ctx.eval_lut_amortized(&gin227, lut227);

    std::vector<RotationPoly> lut228;
    lut228.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 8 (LUT4 _1212_ INIT 0xfcfa PERM 0132) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
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
    }));

    std::cerr << "\rLUT228   ";
    Ciphertext gin228 = 1 * gout70[0] + 2 * gout18[0] + 4 * gout72[0] + 8 * gout219[0];
    std::vector<Ciphertext> gout228 = ctx.eval_lut_amortized(&gin228, lut228);

    std::vector<RotationPoly> lut229;
    lut229.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 1 (LUT4 _1205_ INIT 0xebba PERM 3201) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
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
    }));

    std::cerr << "\rLUT229   ";
    Ciphertext gin229 = 1 * ct_x0 + 2 * ct_y0 + 4 * gout72[0] + 8 * gout219[0];
    std::vector<Ciphertext> gout229 = ctx.eval_lut_amortized(&gin229, lut229);

    std::vector<RotationPoly> lut230;
    lut230.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 283 (LUT4 _1487_ INIT 0xbf PERM 1230) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT230   ";
    Ciphertext gin230 = 1 * gout150[0] + 2 * gout160[0] + 4 * gout149[1] + 8 * gout150[1];
    std::vector<Ciphertext> gout230 = ctx.eval_lut_amortized(&gin230, lut230);

    std::vector<RotationPoly> lut231;
    lut231.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 365 (LUT4 _1569_ INIT 0xd400 PERM 1230) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut231.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 321 (LUT4 _1525_ INIT 0x2bd4 PERM 1230) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut231.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 282 (LUT3 _1486_ INIT 0x69 PERM 123) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT231   ";
    Ciphertext gin231 = 1 * gout76[0] + 2 * gout230[0] + 4 * gout75[1] + 8 * ct_x12;
    std::vector<Ciphertext> gout231 = ctx.eval_lut_amortized(&gin231, lut231);

    std::vector<RotationPoly> lut232;
    lut232.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 372 (LUT4 _1576_ INIT 0x1117 PERM 0312) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut232.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 364 (LUT4 _1568_ INIT 0xe11e PERM 2103) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT232   ";
    Ciphertext gin232 = 1 * gout108[1] + 2 * gout76[1] + 4 * gout231[0] + 8 * ct_x14;
    std::vector<Ciphertext> gout232 = ctx.eval_lut_amortized(&gin232, lut232);

    std::vector<RotationPoly> lut233;
    lut233.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 371 (LUT4 _1575_ INIT 0xbe PERM 2013) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT233   ";
    Ciphertext gin233 = 1 * gout232[0] + 2 * gout109[0] + 4 * gout72[0] + 8 * gout219[0];
    std::vector<Ciphertext> gout233 = ctx.eval_lut_amortized(&gin233, lut233);

    std::vector<RotationPoly> lut234;
    lut234.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 243 (LUT4 _1447_ INIT 0xbf4 PERM 0123) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT234   ";
    Ciphertext gin234 = 1 * gout160[0] + 2 * gout149[1] + 4 * gout149[0] + 8 * gout150[1];
    std::vector<Ciphertext> gout234 = ctx.eval_lut_amortized(&gin234, lut234);

    std::vector<RotationPoly> lut235;
    lut235.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 242 (LUT4 _1446_ INIT 0x708 PERM 2301) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut235.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 200 (LUT4 _1404_ INIT 0x7887 PERM 2301) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT235   ";
    Ciphertext gin235 = 1 * gout152[1] + 2 * gout6[0] + 4 * ct_y10 + 8 * ct_x0;
    std::vector<Ciphertext> gout235 = ctx.eval_lut_amortized(&gin235, lut235);

    std::vector<RotationPoly> lut236;
    lut236.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 218 (LUT3 _1422_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut236.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 182 (LUT3 _1386_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT236   ";
    Ciphertext gin236 = 1 * gout179[0] + 2 * gout120[1] + 4 * gout235[1];
    std::vector<Ciphertext> gout236 = ctx.eval_lut_amortized(&gin236, lut236);

    std::vector<RotationPoly> lut237;
    lut237.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 280 (LUT3 _1484_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut237.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 217 (LUT3 _1421_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT237   ";
    Ciphertext gin237 = 1 * gout236[0] + 2 * gout175[1] + 4 * gout235[0];
    std::vector<Ciphertext> gout237 = ctx.eval_lut_amortized(&gin237, lut237);

    std::vector<RotationPoly> lut238;
    lut238.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 328 (LUT4 _1532_ INIT 0x4100 PERM 0123) */
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
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut238.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 289 (LUT4 _1493_ INIT 0xb44b PERM 0312) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut238.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 250 (LUT2 _1454_ INIT 0x9 PERM 30) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
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
    }));

    std::cerr << "\rLUT238   ";
    Ciphertext gin238 = 1 * gout237[0] + 2 * gout217[0] + 4 * gout214[1] + 8 * gout217[1];
    std::vector<Ciphertext> gout238 = ctx.eval_lut_amortized(&gin238, lut238);

    std::vector<RotationPoly> lut239;
    lut239.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 216 (LUT3 _1420_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut239.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 180 (LUT3 _1384_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT239   ";
    Ciphertext gin239 = 1 * gout182[0] + 2 * gout236[1] + 4 * gout127[0];
    std::vector<Ciphertext> gout239 = ctx.eval_lut_amortized(&gin239, lut239);

    std::vector<RotationPoly> lut240;
    lut240.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 281 (LUT2 _1485_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut240.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 215 (LUT2 _1419_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT240   ";
    Ciphertext gin240 = 1 * gout239[0] + 2 * gout237[1];
    std::vector<Ciphertext> gout240 = ctx.eval_lut_amortized(&gin240, lut240);

    std::vector<RotationPoly> lut241;
    lut241.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 214 (LUT2 _1418_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT241   ";
    Ciphertext gin241 = 1 * gout185[0] + 2 * gout239[1];
    std::vector<Ciphertext> gout241 = ctx.eval_lut_amortized(&gin241, lut241);

    std::vector<RotationPoly> lut242;
    lut242.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 213 (LUT2 _1417_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT242   ";
    Ciphertext gin242 = 1 * gout241[0] + 2 * gout240[1];
    std::vector<Ciphertext> gout242 = ctx.eval_lut_amortized(&gin242, lut242);

    std::vector<RotationPoly> lut243;
    lut243.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 212 (LUT2 _1416_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT243   ";
    Ciphertext gin243 = 1 * gout188[0] + 2 * gout239[1];
    std::vector<Ciphertext> gout243 = ctx.eval_lut_amortized(&gin243, lut243);

    std::vector<RotationPoly> lut244;
    lut244.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 177 (LUT3 _1381_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT244   ";
    Ciphertext gin244 = 1 * gout188[0] + 2 * gout185[0] + 4 * gout239[1];
    std::vector<Ciphertext> gout244 = ctx.eval_lut_amortized(&gin244, lut244);

    std::vector<RotationPoly> lut245;
    lut245.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 211 (LUT4 _1415_ INIT 0xd400 PERM 1230) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut245.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 176 (LUT4 _1380_ INIT 0x2bd4 PERM 1230) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT245   ";
    Ciphertext gin245 = 1 * gout244[0] + 2 * gout191[0] + 4 * gout190[0] + 8 * gout188[1];
    std::vector<Ciphertext> gout245 = ctx.eval_lut_amortized(&gin245, lut245);

    std::vector<RotationPoly> lut246;
    lut246.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 249 (LUT4 _1453_ INIT 0x1117 PERM 0123) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT246   ";
    Ciphertext gin246 = 1 * gout241[0] + 2 * gout240[1] + 4 * gout245[0] + 8 * gout243[0];
    std::vector<Ciphertext> gout246 = ctx.eval_lut_amortized(&gin246, lut246);

    std::vector<RotationPoly> lut247;
    lut247.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 326 (LUT4 _1530_ INIT 0xd400 PERM 1230) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    }));
    lut247.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 288 (LUT4 _1492_ INIT 0x2bd4 PERM 1230) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut247.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 248 (LUT3 _1452_ INIT 0x69 PERM 123) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT247   ";
    Ciphertext gin247 = 1 * gout238[1] + 2 * gout246[0] + 4 * gout238[2] + 8 * gout240[0];
    std::vector<Ciphertext> gout247 = ctx.eval_lut_amortized(&gin247, lut247);

    std::vector<RotationPoly> lut248;
    lut248.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 370 (LUT4 _1574_ INIT 0x1117 PERM 2310) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));
    lut248.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 325 (LUT4 _1529_ INIT 0xe11e PERM 0123) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT248   ";
    Ciphertext gin248 = 1 * gout247[0] + 2 * gout238[0] + 4 * gout218[0] + 8 * gout215[1];
    std::vector<Ciphertext> gout248 = ctx.eval_lut_amortized(&gin248, lut248);

    std::vector<RotationPoly> lut249;
    lut249.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 369 (LUT4 _1573_ INIT 0x7d55 PERM 0123) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 1;
            case 13: return 1;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT249   ";
    Ciphertext gin249 = 1 * gout233[0] + 2 * gout248[0] + 4 * gout216[0] + 8 * gout72[0];
    std::vector<Ciphertext> gout249 = ctx.eval_lut_amortized(&gin249, lut249);

    std::vector<RotationPoly> lut250;
    lut250.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 324 (LUT4 _1528_ INIT 0xfcfa PERM 0132) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
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
    }));

    std::cerr << "\rLUT250   ";
    Ciphertext gin250 = 1 * gout232[1] + 2 * gout248[1] + 4 * gout72[0] + 8 * gout219[0];
    std::vector<Ciphertext> gout250 = ctx.eval_lut_amortized(&gin250, lut250);

    std::vector<RotationPoly> lut251;
    lut251.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 287 (LUT4 _1491_ INIT 0xfcfa PERM 0132) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
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
    }));

    std::cerr << "\rLUT251   ";
    Ciphertext gin251 = 1 * gout231[1] + 2 * gout247[1] + 4 * gout72[0] + 8 * gout219[0];
    std::vector<Ciphertext> gout251 = ctx.eval_lut_amortized(&gin251, lut251);

    std::vector<RotationPoly> lut252;
    lut252.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 247 (LUT4 _1451_ INIT 0xfcfa PERM 0132) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
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
    }));

    std::cerr << "\rLUT252   ";
    Ciphertext gin252 = 1 * gout231[2] + 2 * gout247[2] + 4 * gout72[0] + 8 * gout219[0];
    std::vector<Ciphertext> gout252 = ctx.eval_lut_amortized(&gin252, lut252);

    std::vector<RotationPoly> lut253;
    lut253.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 210 (LUT4 _1414_ INIT 0x1e00 PERM 0123) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 1;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT253   ";
    Ciphertext gin253 = 1 * gout245[0] + 2 * gout243[0] + 4 * gout242[0] + 8 * gout72[0];
    std::vector<Ciphertext> gout253 = ctx.eval_lut_amortized(&gin253, lut253);

    std::vector<RotationPoly> lut254;
    lut254.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 209 (LUT4 _1413_ INIT 0xfff4 PERM 2031) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
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
    }));

    std::cerr << "\rLUT254   ";
    Ciphertext gin254 = 1 * gout234[0] + 2 * gout253[0] + 4 * gout72[0] + 8 * gout219[0];
    std::vector<Ciphertext> gout254 = ctx.eval_lut_amortized(&gin254, lut254);

    std::vector<RotationPoly> lut255;
    lut255.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 175 (LUT4 _1379_ INIT 0xaac3 PERM 0123) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
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
    }));

    std::cerr << "\rLUT255   ";
    Ciphertext gin255 = 1 * gout245[1] + 2 * gout160[0] + 4 * gout149[1] + 8 * gout72[0];
    std::vector<Ciphertext> gout255 = ctx.eval_lut_amortized(&gin255, lut255);

    std::vector<RotationPoly> lut256;
    lut256.push_back(ctx.genrate_lut([](long I) -> long {
        /* GATE 174 (LUT2 _1378_ INIT 0xe PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    }));

    std::cerr << "\rLUT256   ";
    Ciphertext gin256 = 1 * gout255[0] + 2 * gout219[0];
    std::vector<Ciphertext> gout256 = ctx.eval_lut_amortized(&gin256, lut256);

    std::cerr << "\r          \r";
    std::vector<long> out;
    out.push_back(ctx.decrypt(&gout229[0])); /* out0 */
    out.push_back(ctx.decrypt(&gout228[0])); /* out1 */
    out.push_back(ctx.decrypt(&gout227[0])); /* out2 */
    out.push_back(ctx.decrypt(&gout226[0])); /* out3 */
    out.push_back(ctx.decrypt(&gout225[0])); /* out4 */
    out.push_back(ctx.decrypt(&gout224[0])); /* out5 */
    out.push_back(ctx.decrypt(&gout223[0])); /* out6 */
    out.push_back(ctx.decrypt(&gout222[0])); /* out7 */
    out.push_back(ctx.decrypt(&gout221[0])); /* out8 */
    out.push_back(ctx.decrypt(&gout220[0])); /* out9 */
    out.push_back(ctx.decrypt(&gout256[0])); /* out10 */
    out.push_back(ctx.decrypt(&gout254[0])); /* out11 */
    out.push_back(ctx.decrypt(&gout252[0])); /* out12 */
    out.push_back(ctx.decrypt(&gout251[0])); /* out13 */
    out.push_back(ctx.decrypt(&gout250[0])); /* out14 */
    out.push_back(ctx.decrypt(&gout249[0])); /* out15 */
    return out;
}

int
main(void)
{
    /* setup */
    FHEContext ctx;
    long out;

    std::cout << "[+] ";
    ctx.generate_context(tfhe_12_NTT_amortized);
    ctx.set_default_message_encoding_type(partial_domain);

    /* LUT tests */
    std::cout << "[+] Testing LUT4" << std::endl;
    test_lut4(ctx);

    /* add4 tests */
    std::cout << "[+] Testing add4" << std::endl;
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            std::cerr << i << " + " << j;
            out = compose(test_add4_lut4(ctx, i, j));
            assert(out == i + j);
        }
    }

    /* calculator tests */
    std::cout << "[+] Testing calculator" << std::endl;
    std::cout << "[>] 0 0 0" << std::endl;
    std::cout << "exp:    1111111111111111" << std::endl;
    out = compose(test_calculator_lut4(ctx, 0, 0, 0));
    std::cout << "lut4:   " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 6 + 7" << std::endl;
    std::cout << "exp:    0000000000001101" << std::endl;
    out = compose(test_calculator_lut4(ctx, '+', 6, 7));
    std::cout << "lut4:   " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 6 - 7" << std::endl;
    std::cout << "exp:    1111111111111111" << std::endl;
    out = compose(test_calculator_lut4(ctx, '-', 6, 7));
    std::cout << "lut4:   " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 6 * 7" << std::endl;
    std::cout << "exp:    0000000000101010" << std::endl;
    out = compose(test_calculator_lut4(ctx, '*', 6, 7));
    std::cout << "lut4:   " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 0xba + 0xbe" << std::endl;
    std::cout << "exp:    0000000101111000" << std::endl;
    out = compose(test_calculator_lut4(ctx, '+', 0xba, 0xbe));
    std::cout << "lut4:   " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 0xba - 0xbe" << std::endl;
    std::cout << "exp:    1111111111111100" << std::endl;
    out = compose(test_calculator_lut4(ctx, '-', 0xba, 0xbe));
    std::cout << "lut4:   " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 0xba * 0xbe" << std::endl;
    std::cout << "exp:    1000101000001100" << std::endl;
    out = compose(test_calculator_lut4(ctx, '*', 0xba, 0xbe));
    std::cout << "lut4:   " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 0xffff + 0xffff" << std::endl;
    std::cout << "exp:    1111111111111110" << std::endl;
    out = compose(test_calculator_lut4(ctx, '+', 0xffff, 0xffff));
    std::cout << "lut4:   " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 0xffff - 0xffff" << std::endl;
    std::cout << "exp:    0000000000000000" << std::endl;
    out = compose(test_calculator_lut4(ctx, '-', 0xffff, 0xffff));
    std::cout << "lut4:   " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 0xffff * 0xffff" << std::endl;
    std::cout << "exp:    0000000000000001" << std::endl;
    out = compose(test_calculator_lut4(ctx, '*', 0xffff, 0xffff));
    std::cout << "lut4:   " << std::bitset<16>(out) << std::endl;

    return 0;
}
