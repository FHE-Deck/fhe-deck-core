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

std::vector<long>
test_add4_boolean(FHEContext& ctx, uint8_t a, uint8_t b)
{
    Ciphertext ct_a0 = ctx.encrypt_public((a >> 0) & 1);
    long ct_a0clear = (a >> 0) & 1;
    Ciphertext ct_a1 = ctx.encrypt_public((a >> 1) & 1);
    long ct_a1clear = (a >> 1) & 1;
    Ciphertext ct_a2 = ctx.encrypt_public((a >> 2) & 1);
    long ct_a2clear = (a >> 2) & 1;
    Ciphertext ct_a3 = ctx.encrypt_public((a >> 3) & 1);
    long ct_a3clear = (a >> 3) & 1;
    Ciphertext ct_b0 = ctx.encrypt_public((b >> 0) & 1);
    long ct_b0clear = (b >> 0) & 1;
    Ciphertext ct_b1 = ctx.encrypt_public((b >> 1) & 1);
    long ct_b1clear = (b >> 1) & 1;
    Ciphertext ct_b2 = ctx.encrypt_public((b >> 2) & 1);
    long ct_b2clear = (b >> 2) & 1;
    Ciphertext ct_b3 = ctx.encrypt_public((b >> 3) & 1);
    long ct_b3clear = (b >> 3) & 1;

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
    Ciphertext gin0 = 2 * ct_a3 + ct_b3;
    Ciphertext gout0 = ctx.eval_lut(&gin0, xor2);

    auto gin0clear = 2 * ct_a3clear + ct_b3clear;
    auto gout0clear = fxor2(gin0clear, 4);

    assert(ctx.decrypt(&gout0) == gout0clear);
    std::cerr << "\rLUT1   ";
    Ciphertext gin1 = 2 * ct_a2 + ct_b2;
    Ciphertext gout1 = ctx.eval_lut(&gin1, xor2);

    auto gin1clear = 2 * ct_a2clear + ct_b2clear;
    auto gout1clear = fxor2(gin1clear, 4);

    assert(ctx.decrypt(&gout1) == gout1clear);
    std::cerr << "\rLUT2   ";
    Ciphertext gin2 = 2 * ct_a2 + ct_b2;
    Ciphertext gout2 = ctx.eval_lut(&gin2, nand2);

    auto gin2clear = 2 * ct_a2clear + ct_b2clear;
    auto gout2clear = fnand2(gin2clear, 4);

    assert(ctx.decrypt(&gout2) == gout2clear);
    std::cerr << "\rLUT3   ";
    Ciphertext gin3 = 2 * ct_a0 + ct_b0;
    Ciphertext gout3 = ctx.eval_lut(&gin3, and2);

    auto gin3clear = 2 * ct_a0clear + ct_b0clear;
    auto gout3clear = fand2(gin3clear, 4);

    assert(ctx.decrypt(&gout3) == gout3clear);
    std::cerr << "\rLUT4   ";
    Ciphertext gin4 = 2 * ct_a0 + ct_b0;
    Ciphertext gout4 = ctx.eval_lut(&gin4, xor2);

    auto gin4clear = 2 * ct_a0clear + ct_b0clear;
    auto gout4clear = fxor2(gin4clear, 4);

    assert(ctx.decrypt(&gout4) == gout4clear);
    std::cerr << "\rLUT5   ";
    Ciphertext gin5 = 2 * ct_a1 + ct_b1;
    Ciphertext gout5 = ctx.eval_lut(&gin5, xor2);

    auto gin5clear = 2 * ct_a1clear + ct_b1clear;
    auto gout5clear = fxor2(gin5clear, 4);

    assert(ctx.decrypt(&gout5) == gout5clear);
    std::cerr << "\rLUT6   ";
    Ciphertext gin6 = 2 * gout3 + gout5;
    Ciphertext gout6 = ctx.eval_lut(&gin6, xor2);

    auto gin6clear = 2 * gout3clear + gout5clear;
    auto gout6clear = fxor2(gin6clear, 4);

    assert(ctx.decrypt(&gout6) == gout6clear);
    std::cerr << "\rLUT7   ";
    Ciphertext gin7 = 2 * gout3 + gout5;
    Ciphertext gout7 = ctx.eval_lut(&gin7, nand2);

    auto gin7clear = 2 * gout3clear + gout5clear;
    auto gout7clear = fnand2(gin7clear, 4);

    assert(ctx.decrypt(&gout7) == gout7clear);
    std::cerr << "\rLUT8   ";
    Ciphertext gin8 = 2 * ct_a1 + ct_b1;
    Ciphertext gout8 = ctx.eval_lut(&gin8, nand2);

    auto gin8clear = 2 * ct_a1clear + ct_b1clear;
    auto gout8clear = fnand2(gin8clear, 4);

    assert(ctx.decrypt(&gout8) == gout8clear);
    std::cerr << "\rLUT9   ";
    Ciphertext gin9 = 2 * gout8 + gout7;
    Ciphertext gout9 = ctx.eval_lut(&gin9, nand2);

    auto gin9clear = 2 * gout8clear + gout7clear;
    auto gout9clear = fnand2(gin9clear, 4);

    assert(ctx.decrypt(&gout9) == gout9clear);
    std::cerr << "\rLUT10   ";
    Ciphertext gin10 = 2 * gout9 + gout1;
    Ciphertext gout10 = ctx.eval_lut(&gin10, xor2);

    auto gin10clear = 2 * gout9clear + gout1clear;
    auto gout10clear = fxor2(gin10clear, 4);

    assert(ctx.decrypt(&gout10) == gout10clear);
    std::cerr << "\rLUT11   ";
    Ciphertext gin11 = 2 * gout9 + gout1;
    Ciphertext gout11 = ctx.eval_lut(&gin11, nand2);

    auto gin11clear = 2 * gout9clear + gout1clear;
    auto gout11clear = fnand2(gin11clear, 4);

    assert(ctx.decrypt(&gout11) == gout11clear);
    std::cerr << "\rLUT12   ";
    Ciphertext gin12 = 2 * gout2 + gout11;
    Ciphertext gout12 = ctx.eval_lut(&gin12, nand2);

    auto gin12clear = 2 * gout2clear + gout11clear;
    auto gout12clear = fnand2(gin12clear, 4);

    assert(ctx.decrypt(&gout12) == gout12clear);
    std::cerr << "\rLUT13   ";
    Ciphertext gin13 = 2 * gout12 + gout0;
    Ciphertext gout13 = ctx.eval_lut(&gin13, xor2);

    auto gin13clear = 2 * gout12clear + gout0clear;
    auto gout13clear = fxor2(gin13clear, 4);

    assert(ctx.decrypt(&gout13) == gout13clear);
    std::cerr << "\rLUT14   ";
    Ciphertext gin14 = 2 * gout12 + gout0;
    Ciphertext gout14 = ctx.eval_lut(&gin14, nand2);

    auto gin14clear = 2 * gout12clear + gout0clear;
    auto gout14clear = fnand2(gin14clear, 4);

    assert(ctx.decrypt(&gout14) == gout14clear);
    std::cerr << "\rLUT15   ";
    Ciphertext gin15 = 2 * ct_a3 + ct_b3;
    Ciphertext gout15 = ctx.eval_lut(&gin15, nand2);

    auto gin15clear = 2 * ct_a3clear + ct_b3clear;
    auto gout15clear = fnand2(gin15clear, 4);

    assert(ctx.decrypt(&gout15) == gout15clear);
    std::cerr << "\rLUT16   ";
    Ciphertext gin16 = 2 * gout15 + gout14;
    Ciphertext gout16 = ctx.eval_lut(&gin16, nand2);

    auto gin16clear = 2 * gout15clear + gout14clear;
    auto gout16clear = fnand2(gin16clear, 4);

    assert(ctx.decrypt(&gout16) == gout16clear);
    std::cerr << "\r          \r";
    std::vector<long> out;
    out.push_back(ctx.decrypt(&gout4)); /* out0 */
    assert(ctx.decrypt(&gout4) == gout4clear);
    out.push_back(ctx.decrypt(&gout6)); /* out1 */
    assert(ctx.decrypt(&gout6) == gout6clear);
    out.push_back(ctx.decrypt(&gout10)); /* out2 */
    assert(ctx.decrypt(&gout10) == gout10clear);
    out.push_back(ctx.decrypt(&gout13)); /* out3 */
    assert(ctx.decrypt(&gout13) == gout13clear);
    out.push_back(ctx.decrypt(&gout16)); /* out4 */
    assert(ctx.decrypt(&gout16) == gout16clear);
    return out;
}

std::vector<long>
test_calculator_boolean(FHEContext& ctx, uint8_t op, uint16_t x, uint16_t y)
{
    Ciphertext ct_op0 = ctx.encrypt_public((op >> 0) & 1);
    long ct_op0clear = (op >> 0) & 1;
    Ciphertext ct_op1 = ctx.encrypt_public((op >> 1) & 1);
    long ct_op1clear = (op >> 1) & 1;
    Ciphertext ct_op2 = ctx.encrypt_public((op >> 2) & 1);
    long ct_op2clear = (op >> 2) & 1;
    Ciphertext ct_op3 = ctx.encrypt_public((op >> 3) & 1);
    long ct_op3clear = (op >> 3) & 1;
    Ciphertext ct_op4 = ctx.encrypt_public((op >> 4) & 1);
    long ct_op4clear = (op >> 4) & 1;
    Ciphertext ct_op5 = ctx.encrypt_public((op >> 5) & 1);
    long ct_op5clear = (op >> 5) & 1;
    Ciphertext ct_op6 = ctx.encrypt_public((op >> 6) & 1);
    long ct_op6clear = (op >> 6) & 1;
    Ciphertext ct_op7 = ctx.encrypt_public((op >> 7) & 1);
    long ct_op7clear = (op >> 7) & 1;
    Ciphertext ct_x0 = ctx.encrypt_public((x >> 0) & 1);
    long ct_x0clear = (x >> 0) & 1;
    Ciphertext ct_x1 = ctx.encrypt_public((x >> 1) & 1);
    long ct_x1clear = (x >> 1) & 1;
    Ciphertext ct_x2 = ctx.encrypt_public((x >> 2) & 1);
    long ct_x2clear = (x >> 2) & 1;
    Ciphertext ct_x3 = ctx.encrypt_public((x >> 3) & 1);
    long ct_x3clear = (x >> 3) & 1;
    Ciphertext ct_x4 = ctx.encrypt_public((x >> 4) & 1);
    long ct_x4clear = (x >> 4) & 1;
    Ciphertext ct_x5 = ctx.encrypt_public((x >> 5) & 1);
    long ct_x5clear = (x >> 5) & 1;
    Ciphertext ct_x6 = ctx.encrypt_public((x >> 6) & 1);
    long ct_x6clear = (x >> 6) & 1;
    Ciphertext ct_x7 = ctx.encrypt_public((x >> 7) & 1);
    long ct_x7clear = (x >> 7) & 1;
    Ciphertext ct_x8 = ctx.encrypt_public((x >> 8) & 1);
    long ct_x8clear = (x >> 8) & 1;
    Ciphertext ct_x9 = ctx.encrypt_public((x >> 9) & 1);
    long ct_x9clear = (x >> 9) & 1;
    Ciphertext ct_x10 = ctx.encrypt_public((x >> 10) & 1);
    long ct_x10clear = (x >> 10) & 1;
    Ciphertext ct_x11 = ctx.encrypt_public((x >> 11) & 1);
    long ct_x11clear = (x >> 11) & 1;
    Ciphertext ct_x12 = ctx.encrypt_public((x >> 12) & 1);
    long ct_x12clear = (x >> 12) & 1;
    Ciphertext ct_x13 = ctx.encrypt_public((x >> 13) & 1);
    long ct_x13clear = (x >> 13) & 1;
    Ciphertext ct_x14 = ctx.encrypt_public((x >> 14) & 1);
    long ct_x14clear = (x >> 14) & 1;
    Ciphertext ct_x15 = ctx.encrypt_public((x >> 15) & 1);
    long ct_x15clear = (x >> 15) & 1;
    Ciphertext ct_y0 = ctx.encrypt_public((y >> 0) & 1);
    long ct_y0clear = (y >> 0) & 1;
    Ciphertext ct_y1 = ctx.encrypt_public((y >> 1) & 1);
    long ct_y1clear = (y >> 1) & 1;
    Ciphertext ct_y2 = ctx.encrypt_public((y >> 2) & 1);
    long ct_y2clear = (y >> 2) & 1;
    Ciphertext ct_y3 = ctx.encrypt_public((y >> 3) & 1);
    long ct_y3clear = (y >> 3) & 1;
    Ciphertext ct_y4 = ctx.encrypt_public((y >> 4) & 1);
    long ct_y4clear = (y >> 4) & 1;
    Ciphertext ct_y5 = ctx.encrypt_public((y >> 5) & 1);
    long ct_y5clear = (y >> 5) & 1;
    Ciphertext ct_y6 = ctx.encrypt_public((y >> 6) & 1);
    long ct_y6clear = (y >> 6) & 1;
    Ciphertext ct_y7 = ctx.encrypt_public((y >> 7) & 1);
    long ct_y7clear = (y >> 7) & 1;
    Ciphertext ct_y8 = ctx.encrypt_public((y >> 8) & 1);
    long ct_y8clear = (y >> 8) & 1;
    Ciphertext ct_y9 = ctx.encrypt_public((y >> 9) & 1);
    long ct_y9clear = (y >> 9) & 1;
    Ciphertext ct_y10 = ctx.encrypt_public((y >> 10) & 1);
    long ct_y10clear = (y >> 10) & 1;
    Ciphertext ct_y11 = ctx.encrypt_public((y >> 11) & 1);
    long ct_y11clear = (y >> 11) & 1;
    Ciphertext ct_y12 = ctx.encrypt_public((y >> 12) & 1);
    long ct_y12clear = (y >> 12) & 1;
    Ciphertext ct_y13 = ctx.encrypt_public((y >> 13) & 1);
    long ct_y13clear = (y >> 13) & 1;
    Ciphertext ct_y14 = ctx.encrypt_public((y >> 14) & 1);
    long ct_y14clear = (y >> 14) & 1;
    Ciphertext ct_y15 = ctx.encrypt_public((y >> 15) & 1);
    long ct_y15clear = (y >> 15) & 1;

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
    Ciphertext gin0 = 2 * ct_y9 + ct_x1;
    Ciphertext gout0 = ctx.eval_lut(&gin0, nand2);

    auto gin0clear = 2 * ct_y9clear + ct_x1clear;
    auto gout0clear = fnand2(gin0clear, 4);

    assert(ctx.decrypt(&gout0) == gout0clear);
    std::cerr << "\rLUT1   ";
    Ciphertext gin1 = 2 * ct_y10 + ct_x1;
    Ciphertext gout1 = ctx.eval_lut(&gin1, and2);

    auto gin1clear = 2 * ct_y10clear + ct_x1clear;
    auto gout1clear = fand2(gin1clear, 4);

    assert(ctx.decrypt(&gout1) == gout1clear);
    std::cerr << "\rLUT2   ";
    Ciphertext gin2 = 2 * ct_y5 + ct_x2;
    Ciphertext gout2 = ctx.eval_lut(&gin2, and2);

    auto gin2clear = 2 * ct_y5clear + ct_x2clear;
    auto gout2clear = fand2(gin2clear, 4);

    assert(ctx.decrypt(&gout2) == gout2clear);
    std::cerr << "\rLUT3   ";
    Ciphertext gin3 = 2 * ct_y5 + ct_x7;
    Ciphertext gout3 = ctx.eval_lut(&gin3, and2);

    auto gin3clear = 2 * ct_y5clear + ct_x7clear;
    auto gout3clear = fand2(gin3clear, 4);

    assert(ctx.decrypt(&gout3) == gout3clear);
    std::cerr << "\rLUT4   ";
    Ciphertext gin4 = 2 * ct_y2 + ct_x4;
    Ciphertext gout4 = ctx.eval_lut(&gin4, and2);

    auto gin4clear = 2 * ct_y2clear + ct_x4clear;
    auto gout4clear = fand2(gin4clear, 4);

    assert(ctx.decrypt(&gout4) == gout4clear);
    std::cerr << "\rINV5   ";
    Ciphertext gout5 = 1 - ct_op0;

    long gout5clear = 1 - ct_op0clear;

    assert(ctx.decrypt(&gout5) == gout5clear);
    std::cerr << "\rLUT6   ";
    Ciphertext gin6 = 2 * ct_y1 + ct_y0;
    Ciphertext gout6 = ctx.eval_lut(&gin6, nor2);

    auto gin6clear = 2 * ct_y1clear + ct_y0clear;
    auto gout6clear = fnor2(gin6clear, 4);

    assert(ctx.decrypt(&gout6) == gout6clear);
    std::cerr << "\rLUT7   ";
    Ciphertext gin7 = 2 * ct_y3 + ct_x8;
    Ciphertext gout7 = ctx.eval_lut(&gin7, and2);

    auto gin7clear = 2 * ct_y3clear + ct_x8clear;
    auto gout7clear = fand2(gin7clear, 4);

    assert(ctx.decrypt(&gout7) == gout7clear);
    std::cerr << "\rLUT8   ";
    Ciphertext gin8 = 2 * ct_y11 + ct_x2;
    Ciphertext gout8 = ctx.eval_lut(&gin8, and2);

    auto gin8clear = 2 * ct_y11clear + ct_x2clear;
    auto gout8clear = fand2(gin8clear, 4);

    assert(ctx.decrypt(&gout8) == gout8clear);
    std::cerr << "\rLUT9   ";
    Ciphertext gin9 = 2 * ct_y11 + ct_x1;
    Ciphertext gout9 = ctx.eval_lut(&gin9, and2);

    auto gin9clear = 2 * ct_y11clear + ct_x1clear;
    auto gout9clear = fand2(gin9clear, 4);

    assert(ctx.decrypt(&gout9) == gout9clear);
    std::cerr << "\rINV10   ";
    Ciphertext gout10 = 1 - gout6;

    long gout10clear = 1 - gout6clear;

    assert(ctx.decrypt(&gout10) == gout10clear);
    std::cerr << "\rLUT11   ";
    Ciphertext gin11 = 2 * ct_y0 + ct_x14;
    Ciphertext gout11 = ctx.eval_lut(&gin11, and2);

    auto gin11clear = 2 * ct_y0clear + ct_x14clear;
    auto gout11clear = fand2(gin11clear, 4);

    assert(ctx.decrypt(&gout11) == gout11clear);
    std::cerr << "\rLUT12   ";
    Ciphertext gin12 = 2 * ct_y9 + ct_x2;
    Ciphertext gout12 = ctx.eval_lut(&gin12, and2);

    auto gin12clear = 2 * ct_y9clear + ct_x2clear;
    auto gout12clear = fand2(gin12clear, 4);

    assert(ctx.decrypt(&gout12) == gout12clear);
    std::cerr << "\rLUT13   ";
    Ciphertext gin13 = 2 * ct_y1 + ct_x11;
    Ciphertext gout13 = ctx.eval_lut(&gin13, and2);

    auto gin13clear = 2 * ct_y1clear + ct_x11clear;
    auto gout13clear = fand2(gin13clear, 4);

    assert(ctx.decrypt(&gout13) == gout13clear);
    std::cerr << "\rLUT14   ";
    Ciphertext gin14 = 2 * ct_y3 + ct_x10;
    Ciphertext gout14 = ctx.eval_lut(&gin14, and2);

    auto gin14clear = 2 * ct_y3clear + ct_x10clear;
    auto gout14clear = fand2(gin14clear, 4);

    assert(ctx.decrypt(&gout14) == gout14clear);
    std::cerr << "\rLUT15   ";
    Ciphertext gin15 = 2 * ct_y7 + ct_x5;
    Ciphertext gout15 = ctx.eval_lut(&gin15, and2);

    auto gin15clear = 2 * ct_y7clear + ct_x5clear;
    auto gout15clear = fand2(gin15clear, 4);

    assert(ctx.decrypt(&gout15) == gout15clear);
    std::cerr << "\rLUT16   ";
    Ciphertext gin16 = 2 * ct_y3 + ct_x0;
    Ciphertext gout16 = ctx.eval_lut(&gin16, nand2);

    auto gin16clear = 2 * ct_y3clear + ct_x0clear;
    auto gout16clear = fnand2(gin16clear, 4);

    assert(ctx.decrypt(&gout16) == gout16clear);
    std::cerr << "\rLUT17   ";
    Ciphertext gin17 = 2 * ct_op2 + ct_op3;
    Ciphertext gout17 = ctx.eval_lut(&gin17, and2);

    auto gin17clear = 2 * ct_op2clear + ct_op3clear;
    auto gout17clear = fand2(gin17clear, 4);

    assert(ctx.decrypt(&gout17) == gout17clear);
    std::cerr << "\rLUT18   ";
    Ciphertext gin18 = 2 * ct_y5 + ct_x10;
    Ciphertext gout18 = ctx.eval_lut(&gin18, and2);

    auto gin18clear = 2 * ct_y5clear + ct_x10clear;
    auto gout18clear = fand2(gin18clear, 4);

    assert(ctx.decrypt(&gout18) == gout18clear);
    std::cerr << "\rLUT19   ";
    Ciphertext gin19 = 2 * ct_y1 + ct_x13;
    Ciphertext gout19 = ctx.eval_lut(&gin19, and2);

    auto gin19clear = 2 * ct_y1clear + ct_x13clear;
    auto gout19clear = fand2(gin19clear, 4);

    assert(ctx.decrypt(&gout19) == gout19clear);
    std::cerr << "\rINV20   ";
    Ciphertext gout20 = 1 - ct_y10;

    long gout20clear = 1 - ct_y10clear;

    assert(ctx.decrypt(&gout20) == gout20clear);
    std::cerr << "\rLUT21   ";
    Ciphertext gin21 = 2 * ct_y7 + ct_x7;
    Ciphertext gout21 = ctx.eval_lut(&gin21, nand2);

    auto gin21clear = 2 * ct_y7clear + ct_x7clear;
    auto gout21clear = fnand2(gin21clear, 4);

    assert(ctx.decrypt(&gout21) == gout21clear);
    std::cerr << "\rINV22   ";
    Ciphertext gout22 = 1 - ct_y15;

    long gout22clear = 1 - ct_y15clear;

    assert(ctx.decrypt(&gout22) == gout22clear);
    std::cerr << "\rLUT23   ";
    Ciphertext gin23 = 2 * ct_y15 + ct_x15;
    Ciphertext gout23 = ctx.eval_lut(&gin23, xor2);

    auto gin23clear = 2 * ct_y15clear + ct_x15clear;
    auto gout23clear = fxor2(gin23clear, 4);

    assert(ctx.decrypt(&gout23) == gout23clear);
    std::cerr << "\rINV24   ";
    Ciphertext gout24 = 1 - ct_x14;

    long gout24clear = 1 - ct_x14clear;

    assert(ctx.decrypt(&gout24) == gout24clear);
    std::cerr << "\rINV25   ";
    Ciphertext gout25 = 1 - ct_x4;

    long gout25clear = 1 - ct_x4clear;

    assert(ctx.decrypt(&gout25) == gout25clear);
    std::cerr << "\rINV26   ";
    Ciphertext gout26 = 1 - ct_x6;

    long gout26clear = 1 - ct_x6clear;

    assert(ctx.decrypt(&gout26) == gout26clear);
    std::cerr << "\rINV27   ";
    Ciphertext gout27 = 1 - ct_x8;

    long gout27clear = 1 - ct_x8clear;

    assert(ctx.decrypt(&gout27) == gout27clear);
    std::cerr << "\rLUT28   ";
    Ciphertext gin28 = 2 * ct_y2 + ct_x6;
    Ciphertext gout28 = ctx.eval_lut(&gin28, and2);

    auto gin28clear = 2 * ct_y2clear + ct_x6clear;
    auto gout28clear = fand2(gin28clear, 4);

    assert(ctx.decrypt(&gout28) == gout28clear);
    std::cerr << "\rLUT29   ";
    Ciphertext gin29 = 2 * ct_y8 + ct_x5;
    Ciphertext gout29 = ctx.eval_lut(&gin29, and2);

    auto gin29clear = 2 * ct_y8clear + ct_x5clear;
    auto gout29clear = fand2(gin29clear, 4);

    assert(ctx.decrypt(&gout29) == gout29clear);
    std::cerr << "\rLUT30   ";
    Ciphertext gin30 = 2 * ct_y0 + ct_x10;
    Ciphertext gout30 = ctx.eval_lut(&gin30, nand2);

    auto gin30clear = 2 * ct_y0clear + ct_x10clear;
    auto gout30clear = fnand2(gin30clear, 4);

    assert(ctx.decrypt(&gout30) == gout30clear);
    std::cerr << "\rINV31   ";
    Ciphertext gout31 = 1 - ct_x12;

    long gout31clear = 1 - ct_x12clear;

    assert(ctx.decrypt(&gout31) == gout31clear);
    std::cerr << "\rLUT32   ";
    Ciphertext gin32 = 2 * ct_y6 + ct_x4;
    Ciphertext gout32 = ctx.eval_lut(&gin32, and2);

    auto gin32clear = 2 * ct_y6clear + ct_x4clear;
    auto gout32clear = fand2(gin32clear, 4);

    assert(ctx.decrypt(&gout32) == gout32clear);
    std::cerr << "\rLUT33   ";
    Ciphertext gin33 = 2 * ct_y3 + ct_x1;
    Ciphertext gout33 = ctx.eval_lut(&gin33, nand2);

    auto gin33clear = 2 * ct_y3clear + ct_x1clear;
    auto gout33clear = fnand2(gin33clear, 4);

    assert(ctx.decrypt(&gout33) == gout33clear);
    std::cerr << "\rLUT34   ";
    Ciphertext gin34 = 2 * ct_y1 + ct_x6;
    Ciphertext gout34 = ctx.eval_lut(&gin34, and2);

    auto gin34clear = 2 * ct_y1clear + ct_x6clear;
    auto gout34clear = fand2(gin34clear, 4);

    assert(ctx.decrypt(&gout34) == gout34clear);
    std::cerr << "\rINV35   ";
    Ciphertext gout35 = 1 - ct_y5;

    long gout35clear = 1 - ct_y5clear;

    assert(ctx.decrypt(&gout35) == gout35clear);
    std::cerr << "\rLUT36   ";
    Ciphertext gin36 = 2 * ct_y0 + ct_x9;
    Ciphertext gout36 = ctx.eval_lut(&gin36, nand2);

    auto gin36clear = 2 * ct_y0clear + ct_x9clear;
    auto gout36clear = fnand2(gin36clear, 4);

    assert(ctx.decrypt(&gout36) == gout36clear);
    std::cerr << "\rINV37   ";
    Ciphertext gout37 = 1 - ct_y7;

    long gout37clear = 1 - ct_y7clear;

    assert(ctx.decrypt(&gout37) == gout37clear);
    std::cerr << "\rLUT38   ";
    Ciphertext gin38 = 2 * ct_y13 + ct_x2;
    Ciphertext gout38 = ctx.eval_lut(&gin38, and2);

    auto gin38clear = 2 * ct_y13clear + ct_x2clear;
    auto gout38clear = fand2(gin38clear, 4);

    assert(ctx.decrypt(&gout38) == gout38clear);
    std::cerr << "\rLUT39   ";
    Ciphertext gin39 = 2 * ct_y0 + ct_x6;
    Ciphertext gout39 = ctx.eval_lut(&gin39, nand2);

    auto gin39clear = 2 * ct_y0clear + ct_x6clear;
    auto gout39clear = fnand2(gin39clear, 4);

    assert(ctx.decrypt(&gout39) == gout39clear);
    std::cerr << "\rLUT40   ";
    Ciphertext gin40 = 2 * ct_y10 + ct_x4;
    Ciphertext gout40 = ctx.eval_lut(&gin40, nand2);

    auto gin40clear = 2 * ct_y10clear + ct_x4clear;
    auto gout40clear = fnand2(gin40clear, 4);

    assert(ctx.decrypt(&gout40) == gout40clear);
    std::cerr << "\rINV41   ";
    Ciphertext gout41 = 1 - ct_y1;

    long gout41clear = 1 - ct_y1clear;

    assert(ctx.decrypt(&gout41) == gout41clear);
    std::cerr << "\rLUT42   ";
    Ciphertext gin42 = 2 * ct_y2 + ct_x11;
    Ciphertext gout42 = ctx.eval_lut(&gin42, and2);

    auto gin42clear = 2 * ct_y2clear + ct_x11clear;
    auto gout42clear = fand2(gin42clear, 4);

    assert(ctx.decrypt(&gout42) == gout42clear);
    std::cerr << "\rLUT43   ";
    Ciphertext gin43 = 2 * ct_y7 + ct_x0;
    Ciphertext gout43 = ctx.eval_lut(&gin43, and2);

    auto gin43clear = 2 * ct_y7clear + ct_x0clear;
    auto gout43clear = fand2(gin43clear, 4);

    assert(ctx.decrypt(&gout43) == gout43clear);
    std::cerr << "\rLUT44   ";
    Ciphertext gin44 = 2 * ct_y4 + ct_x0;
    Ciphertext gout44 = ctx.eval_lut(&gin44, and2);

    auto gin44clear = 2 * ct_y4clear + ct_x0clear;
    auto gout44clear = fand2(gin44clear, 4);

    assert(ctx.decrypt(&gout44) == gout44clear);
    std::cerr << "\rLUT45   ";
    Ciphertext gin45 = 2 * ct_y3 + ct_x9;
    Ciphertext gout45 = ctx.eval_lut(&gin45, and2);

    auto gin45clear = 2 * ct_y3clear + ct_x9clear;
    auto gout45clear = fand2(gin45clear, 4);

    assert(ctx.decrypt(&gout45) == gout45clear);
    std::cerr << "\rLUT46   ";
    Ciphertext gin46 = 2 * ct_y5 + ct_x3;
    Ciphertext gout46 = ctx.eval_lut(&gin46, and2);

    auto gin46clear = 2 * ct_y5clear + ct_x3clear;
    auto gout46clear = fand2(gin46clear, 4);

    assert(ctx.decrypt(&gout46) == gout46clear);
    std::cerr << "\rLUT47   ";
    Ciphertext gin47 = 2 * ct_y0 + ct_x0;
    Ciphertext gout47 = ctx.eval_lut(&gin47, xnor2);

    auto gin47clear = 2 * ct_y0clear + ct_x0clear;
    auto gout47clear = fxnor2(gin47clear, 4);

    assert(ctx.decrypt(&gout47) == gout47clear);
    std::cerr << "\rLUT48   ";
    Ciphertext gin48 = 2 * ct_y7 + ct_x3;
    Ciphertext gout48 = ctx.eval_lut(&gin48, and2);

    auto gin48clear = 2 * ct_y7clear + ct_x3clear;
    auto gout48clear = fand2(gin48clear, 4);

    assert(ctx.decrypt(&gout48) == gout48clear);
    std::cerr << "\rLUT49   ";
    Ciphertext gin49 = 2 * gout48 + gout32;
    Ciphertext gout49 = ctx.eval_lut(&gin49, xor2);

    auto gin49clear = 2 * gout48clear + gout32clear;
    auto gout49clear = fxor2(gin49clear, 4);

    assert(ctx.decrypt(&gout49) == gout49clear);
    std::cerr << "\rLUT50   ";
    Ciphertext gin50 = 2 * gout48 + gout32;
    Ciphertext gout50 = ctx.eval_lut(&gin50, nand2);

    auto gin50clear = 2 * gout48clear + gout32clear;
    auto gout50clear = fnand2(gin50clear, 4);

    assert(ctx.decrypt(&gout50) == gout50clear);
    std::cerr << "\rLUT51   ";
    Ciphertext gin51 = 2 * ct_y14 + ct_x1;
    Ciphertext gout51 = ctx.eval_lut(&gin51, and2);

    auto gin51clear = 2 * ct_y14clear + ct_x1clear;
    auto gout51clear = fand2(gin51clear, 4);

    assert(ctx.decrypt(&gout51) == gout51clear);
    std::cerr << "\rLUT52   ";
    Ciphertext gin52 = 2 * ct_y3 + ct_x12;
    Ciphertext gout52 = ctx.eval_lut(&gin52, and2);

    auto gin52clear = 2 * ct_y3clear + ct_x12clear;
    auto gout52clear = fand2(gin52clear, 4);

    assert(ctx.decrypt(&gout52) == gout52clear);
    std::cerr << "\rLUT53   ";
    Ciphertext gin53 = 2 * gout22 + gout52;
    Ciphertext gout53 = ctx.eval_lut(&gin53, xnor2);

    auto gin53clear = 2 * gout22clear + gout52clear;
    auto gout53clear = fxnor2(gin53clear, 4);

    assert(ctx.decrypt(&gout53) == gout53clear);
    std::cerr << "\rLUT54   ";
    Ciphertext gin54 = 2 * gout42 + gout52;
    Ciphertext gout54 = ctx.eval_lut(&gin54, nand2);

    auto gin54clear = 2 * gout42clear + gout52clear;
    auto gout54clear = fnand2(gin54clear, 4);

    assert(ctx.decrypt(&gout54) == gout54clear);
    std::cerr << "\rLUT55   ";
    Ciphertext gin55 = 2 * ct_y4 + ct_x1;
    Ciphertext gout55 = ctx.eval_lut(&gin55, and2);

    auto gin55clear = 2 * ct_y4clear + ct_x1clear;
    auto gout55clear = fand2(gin55clear, 4);

    assert(ctx.decrypt(&gout55) == gout55clear);
    std::cerr << "\rLUT56   ";
    Ciphertext gin56 = 2 * ct_y1 + ct_x7;
    Ciphertext gout56 = ctx.eval_lut(&gin56, and2);

    auto gin56clear = 2 * ct_y1clear + ct_x7clear;
    auto gout56clear = fand2(gin56clear, 4);

    assert(ctx.decrypt(&gout56) == gout56clear);
    std::cerr << "\rLUT57   ";
    Ciphertext gin57 = 2 * ct_y1 + ct_x5;
    Ciphertext gout57 = ctx.eval_lut(&gin57, and2);

    auto gin57clear = 2 * ct_y1clear + ct_x5clear;
    auto gout57clear = fand2(gin57clear, 4);

    assert(ctx.decrypt(&gout57) == gout57clear);
    std::cerr << "\rLUT58   ";
    Ciphertext gin58 = 2 * ct_y2 + ct_x8;
    Ciphertext gout58 = ctx.eval_lut(&gin58, and2);

    auto gin58clear = 2 * ct_y2clear + ct_x8clear;
    auto gout58clear = fand2(gin58clear, 4);

    assert(ctx.decrypt(&gout58) == gout58clear);
    std::cerr << "\rLUT59   ";
    Ciphertext gin59 = 2 * ct_op6 + ct_op7;
    Ciphertext gout59 = ctx.eval_lut(&gin59, nor2);

    auto gin59clear = 2 * ct_op6clear + ct_op7clear;
    auto gout59clear = fnor2(gin59clear, 4);

    assert(ctx.decrypt(&gout59) == gout59clear);
    std::cerr << "\rLUT60   ";
    Ciphertext gin60 = 2 * ct_y10 + ct_x0;
    Ciphertext gout60 = ctx.eval_lut(&gin60, and2);

    auto gin60clear = 2 * ct_y10clear + ct_x0clear;
    auto gout60clear = fand2(gin60clear, 4);

    assert(ctx.decrypt(&gout60) == gout60clear);
    std::cerr << "\rLUT61   ";
    Ciphertext gin61 = 2 * ct_y1 + ct_x14;
    Ciphertext gout61 = ctx.eval_lut(&gin61, and2);

    auto gin61clear = 2 * ct_y1clear + ct_x14clear;
    auto gout61clear = fand2(gin61clear, 4);

    assert(ctx.decrypt(&gout61) == gout61clear);
    std::cerr << "\rLUT62   ";
    Ciphertext gin62 = 2 * ct_y12 + ct_x1;
    Ciphertext gout62 = ctx.eval_lut(&gin62, nand2);

    auto gin62clear = 2 * ct_y12clear + ct_x1clear;
    auto gout62clear = fnand2(gin62clear, 4);

    assert(ctx.decrypt(&gout62) == gout62clear);
    std::cerr << "\rLUT63   ";
    Ciphertext gin63 = 2 * ct_y4 + ct_x10;
    Ciphertext gout63 = ctx.eval_lut(&gin63, and2);

    auto gin63clear = 2 * ct_y4clear + ct_x10clear;
    auto gout63clear = fand2(gin63clear, 4);

    assert(ctx.decrypt(&gout63) == gout63clear);
    std::cerr << "\rLUT64   ";
    Ciphertext gin64 = 2 * gout39 + (1 - gout63);
    Ciphertext gout64 = ctx.eval_lut(&gin64, or2);

    auto gin64clear = 2 * gout39clear + (1 - gout63clear);
    auto gout64clear = for2(gin64clear, 4);

    assert(ctx.decrypt(&gout64) == gout64clear);
    std::cerr << "\rLUT65   ";
    Ciphertext gin65 = 2 * ct_y3 + ct_x3;
    Ciphertext gout65 = ctx.eval_lut(&gin65, and2);

    auto gin65clear = 2 * ct_y3clear + ct_x3clear;
    auto gout65clear = fand2(gin65clear, 4);

    assert(ctx.decrypt(&gout65) == gout65clear);
    std::cerr << "\rLUT66   ";
    Ciphertext gin66 = 2 * ct_y1 + ct_x4;
    Ciphertext gout66 = ctx.eval_lut(&gin66, and2);

    auto gin66clear = 2 * ct_y1clear + ct_x4clear;
    auto gout66clear = fand2(gin66clear, 4);

    assert(ctx.decrypt(&gout66) == gout66clear);
    std::cerr << "\rLUT67   ";
    Ciphertext gin67 = 2 * ct_y3 + ct_x5;
    Ciphertext gout67 = ctx.eval_lut(&gin67, and2);

    auto gin67clear = 2 * ct_y3clear + ct_x5clear;
    auto gout67clear = fand2(gin67clear, 4);

    assert(ctx.decrypt(&gout67) == gout67clear);
    std::cerr << "\rLUT68   ";
    Ciphertext gin68 = 2 * gout67 + gout28;
    Ciphertext gout68 = ctx.eval_lut(&gin68, xor2);

    auto gin68clear = 2 * gout67clear + gout28clear;
    auto gout68clear = fxor2(gin68clear, 4);

    assert(ctx.decrypt(&gout68) == gout68clear);
    std::cerr << "\rLUT69   ";
    Ciphertext gin69 = 2 * gout56 + gout68;
    Ciphertext gout69 = ctx.eval_lut(&gin69, xor2);

    auto gin69clear = 2 * gout56clear + gout68clear;
    auto gout69clear = fxor2(gin69clear, 4);

    assert(ctx.decrypt(&gout69) == gout69clear);
    std::cerr << "\rLUT70   ";
    Ciphertext gin70 = 2 * gout56 + gout68;
    Ciphertext gout70 = ctx.eval_lut(&gin70, nand2);

    auto gin70clear = 2 * gout56clear + gout68clear;
    auto gout70clear = fnand2(gin70clear, 4);

    assert(ctx.decrypt(&gout70) == gout70clear);
    std::cerr << "\rLUT71   ";
    Ciphertext gin71 = 2 * gout67 + gout28;
    Ciphertext gout71 = ctx.eval_lut(&gin71, nand2);

    auto gin71clear = 2 * gout67clear + gout28clear;
    auto gout71clear = fnand2(gin71clear, 4);

    assert(ctx.decrypt(&gout71) == gout71clear);
    std::cerr << "\rLUT72   ";
    Ciphertext gin72 = 2 * ct_y4 + ct_x4;
    Ciphertext gout72 = ctx.eval_lut(&gin72, and2);

    auto gin72clear = 2 * ct_y4clear + ct_x4clear;
    auto gout72clear = fand2(gin72clear, 4);

    assert(ctx.decrypt(&gout72) == gout72clear);
    std::cerr << "\rINV73   ";
    Ciphertext gout73 = 1 - ct_x11;

    long gout73clear = 1 - ct_x11clear;

    assert(ctx.decrypt(&gout73) == gout73clear);
    std::cerr << "\rINV74   ";
    Ciphertext gout74 = 1 - ct_y14;

    long gout74clear = 1 - ct_y14clear;

    assert(ctx.decrypt(&gout74) == gout74clear);
    std::cerr << "\rLUT75   ";
    Ciphertext gin75 = 2 * ct_y10 + ct_x2;
    Ciphertext gout75 = ctx.eval_lut(&gin75, and2);

    auto gin75clear = 2 * ct_y10clear + ct_x2clear;
    auto gout75clear = fand2(gin75clear, 4);

    assert(ctx.decrypt(&gout75) == gout75clear);
    std::cerr << "\rLUT76   ";
    Ciphertext gin76 = 2 * (1 - ct_op4) + ct_op5;
    Ciphertext gout76 = ctx.eval_lut(&gin76, and2);

    auto gin76clear = 2 * (1 - ct_op4clear) + ct_op5clear;
    auto gout76clear = fand2(gin76clear, 4);

    assert(ctx.decrypt(&gout76) == gout76clear);
    std::cerr << "\rLUT77   ";
    Ciphertext gin77 = 2 * gout76 + gout59;
    Ciphertext gout77 = ctx.eval_lut(&gin77, and2);

    auto gin77clear = 2 * gout76clear + gout59clear;
    auto gout77clear = fand2(gin77clear, 4);

    assert(ctx.decrypt(&gout77) == gout77clear);
    std::cerr << "\rLUT78   ";
    Ciphertext gin78 = 2 * ct_y10 + ct_x5;
    Ciphertext gout78 = ctx.eval_lut(&gin78, and2);

    auto gin78clear = 2 * ct_y10clear + ct_x5clear;
    auto gout78clear = fand2(gin78clear, 4);

    assert(ctx.decrypt(&gout78) == gout78clear);
    std::cerr << "\rINV79   ";
    Ciphertext gout79 = 1 - ct_x3;

    long gout79clear = 1 - ct_x3clear;

    assert(ctx.decrypt(&gout79) == gout79clear);
    std::cerr << "\rINV80   ";
    Ciphertext gout80 = 1 - ct_x7;

    long gout80clear = 1 - ct_x7clear;

    assert(ctx.decrypt(&gout80) == gout80clear);
    std::cerr << "\rLUT81   ";
    Ciphertext gin81 = 2 * ct_y4 + ct_x11;
    Ciphertext gout81 = ctx.eval_lut(&gin81, and2);

    auto gin81clear = 2 * ct_y4clear + ct_x11clear;
    auto gout81clear = fand2(gin81clear, 4);

    assert(ctx.decrypt(&gout81) == gout81clear);
    std::cerr << "\rLUT82   ";
    Ciphertext gin82 = 2 * ct_y6 + ct_x5;
    Ciphertext gout82 = ctx.eval_lut(&gin82, and2);

    auto gin82clear = 2 * ct_y6clear + ct_x5clear;
    auto gout82clear = fand2(gin82clear, 4);

    assert(ctx.decrypt(&gout82) == gout82clear);
    std::cerr << "\rLUT83   ";
    Ciphertext gin83 = 2 * ct_y5 + ct_x4;
    Ciphertext gout83 = ctx.eval_lut(&gin83, and2);

    auto gin83clear = 2 * ct_y5clear + ct_x4clear;
    auto gout83clear = fand2(gin83clear, 4);

    assert(ctx.decrypt(&gout83) == gout83clear);
    std::cerr << "\rLUT84   ";
    Ciphertext gin84 = 2 * gout63 + gout11;
    Ciphertext gout84 = ctx.eval_lut(&gin84, nand2);

    auto gin84clear = 2 * gout63clear + gout11clear;
    auto gout84clear = fnand2(gin84clear, 4);

    assert(ctx.decrypt(&gout84) == gout84clear);
    std::cerr << "\rLUT85   ";
    Ciphertext gin85 = 2 * ct_y5 + ct_x9;
    Ciphertext gout85 = ctx.eval_lut(&gin85, and2);

    auto gin85clear = 2 * ct_y5clear + ct_x9clear;
    auto gout85clear = fand2(gin85clear, 4);

    assert(ctx.decrypt(&gout85) == gout85clear);
    std::cerr << "\rLUT86   ";
    Ciphertext gin86 = 2 * ct_y11 + ct_x4;
    Ciphertext gout86 = ctx.eval_lut(&gin86, and2);

    auto gin86clear = 2 * ct_y11clear + ct_x4clear;
    auto gout86clear = fand2(gin86clear, 4);

    assert(ctx.decrypt(&gout86) == gout86clear);
    std::cerr << "\rLUT87   ";
    Ciphertext gin87 = 2 * ct_y0 + ct_x11;
    Ciphertext gout87 = ctx.eval_lut(&gin87, nand2);

    auto gin87clear = 2 * ct_y0clear + ct_x11clear;
    auto gout87clear = fnand2(gin87clear, 4);

    assert(ctx.decrypt(&gout87) == gout87clear);
    std::cerr << "\rINV88   ";
    Ciphertext gout88 = 1 - ct_y6;

    long gout88clear = 1 - ct_y6clear;

    assert(ctx.decrypt(&gout88) == gout88clear);
    std::cerr << "\rLUT89   ";
    Ciphertext gin89 = 2 * ct_y12 + ct_x3;
    Ciphertext gout89 = ctx.eval_lut(&gin89, and2);

    auto gin89clear = 2 * ct_y12clear + ct_x3clear;
    auto gout89clear = fand2(gin89clear, 4);

    assert(ctx.decrypt(&gout89) == gout89clear);
    std::cerr << "\rLUT90   ";
    Ciphertext gin90 = 2 * ct_y14 + ct_x0;
    Ciphertext gout90 = ctx.eval_lut(&gin90, and2);

    auto gin90clear = 2 * ct_y14clear + ct_x0clear;
    auto gout90clear = fand2(gin90clear, 4);

    assert(ctx.decrypt(&gout90) == gout90clear);
    std::cerr << "\rLUT91   ";
    Ciphertext gin91 = 2 * ct_y0 + ct_x3;
    Ciphertext gout91 = ctx.eval_lut(&gin91, and2);

    auto gin91clear = 2 * ct_y0clear + ct_x3clear;
    auto gout91clear = fand2(gin91clear, 4);

    assert(ctx.decrypt(&gout91) == gout91clear);
    std::cerr << "\rLUT92   ";
    Ciphertext gin92 = 2 * ct_y4 + ct_x2;
    Ciphertext gout92 = ctx.eval_lut(&gin92, and2);

    auto gin92clear = 2 * ct_y4clear + ct_x2clear;
    auto gout92clear = fand2(gin92clear, 4);

    assert(ctx.decrypt(&gout92) == gout92clear);
    std::cerr << "\rLUT93   ";
    Ciphertext gin93 = 2 * ct_y2 + ct_x3;
    Ciphertext gout93 = ctx.eval_lut(&gin93, and2);

    auto gin93clear = 2 * ct_y2clear + ct_x3clear;
    auto gout93clear = fand2(gin93clear, 4);

    assert(ctx.decrypt(&gout93) == gout93clear);
    std::cerr << "\rLUT94   ";
    Ciphertext gin94 = 2 * (1 - ct_op2) + ct_op1;
    Ciphertext gout94 = ctx.eval_lut(&gin94, and2);

    auto gin94clear = 2 * (1 - ct_op2clear) + ct_op1clear;
    auto gout94clear = fand2(gin94clear, 4);

    assert(ctx.decrypt(&gout94) == gout94clear);
    std::cerr << "\rLUT95   ";
    Ciphertext gin95 = 2 * ct_y2 + ct_x0;
    Ciphertext gout95 = ctx.eval_lut(&gin95, and2);

    auto gin95clear = 2 * ct_y2clear + ct_x0clear;
    auto gout95clear = fand2(gin95clear, 4);

    assert(ctx.decrypt(&gout95) == gout95clear);
    std::cerr << "\rLUT96   ";
    Ciphertext gin96 = 2 * gout62 + (1 - gout38);
    Ciphertext gout96 = ctx.eval_lut(&gin96, or2);

    auto gin96clear = 2 * gout62clear + (1 - gout38clear);
    auto gout96clear = for2(gin96clear, 4);

    assert(ctx.decrypt(&gout96) == gout96clear);
    std::cerr << "\rLUT97   ";
    Ciphertext gin97 = 2 * ct_y4 + ct_x3;
    Ciphertext gout97 = ctx.eval_lut(&gin97, and2);

    auto gin97clear = 2 * ct_y4clear + ct_x3clear;
    auto gout97clear = fand2(gin97clear, 4);

    assert(ctx.decrypt(&gout97) == gout97clear);
    std::cerr << "\rLUT98   ";
    Ciphertext gin98 = 2 * ct_op3 + gout94;
    Ciphertext gout98 = ctx.eval_lut(&gin98, and2);

    auto gin98clear = 2 * ct_op3clear + gout94clear;
    auto gout98clear = fand2(gin98clear, 4);

    assert(ctx.decrypt(&gout98) == gout98clear);
    std::cerr << "\rINV99   ";
    Ciphertext gout99 = 1 - ct_x2;

    long gout99clear = 1 - ct_x2clear;

    assert(ctx.decrypt(&gout99) == gout99clear);
    std::cerr << "\rLUT100   ";
    Ciphertext gin100 = 2 * gout77 + gout98;
    Ciphertext gout100 = ctx.eval_lut(&gin100, and2);

    auto gin100clear = 2 * gout77clear + gout98clear;
    auto gout100clear = fand2(gin100clear, 4);

    assert(ctx.decrypt(&gout100) == gout100clear);
    std::cerr << "\rLUT101   ";
    Ciphertext gin101 = 2 * ct_y1 + ct_x10;
    Ciphertext gout101 = ctx.eval_lut(&gin101, and2);

    auto gin101clear = 2 * ct_y1clear + ct_x10clear;
    auto gout101clear = fand2(gin101clear, 4);

    assert(ctx.decrypt(&gout101) == gout101clear);
    std::cerr << "\rLUT102   ";
    Ciphertext gin102 = 2 * ct_y7 + ct_x2;
    Ciphertext gout102 = ctx.eval_lut(&gin102, and2);

    auto gin102clear = 2 * ct_y7clear + ct_x2clear;
    auto gout102clear = fand2(gin102clear, 4);

    assert(ctx.decrypt(&gout102) == gout102clear);
    std::cerr << "\rLUT103   ";
    Ciphertext gin103 = 2 * ct_y8 + ct_x0;
    Ciphertext gout103 = ctx.eval_lut(&gin103, and2);

    auto gin103clear = 2 * ct_y8clear + ct_x0clear;
    auto gout103clear = fand2(gin103clear, 4);

    assert(ctx.decrypt(&gout103) == gout103clear);
    std::cerr << "\rLUT104   ";
    Ciphertext gin104 = 2 * gout5 + gout100;
    Ciphertext gout104 = ctx.eval_lut(&gin104, and2);

    auto gin104clear = 2 * gout5clear + gout100clear;
    auto gout104clear = fand2(gin104clear, 4);

    assert(ctx.decrypt(&gout104) == gout104clear);
    std::cerr << "\rINV105   ";
    Ciphertext gout105 = 1 - ct_y3;

    long gout105clear = 1 - ct_y3clear;

    assert(ctx.decrypt(&gout105) == gout105clear);
    std::cerr << "\rLUT106   ";
    Ciphertext gin106 = 2 * ct_y1 + ct_x3;
    Ciphertext gout106 = ctx.eval_lut(&gin106, and2);

    auto gin106clear = 2 * ct_y1clear + ct_x3clear;
    auto gout106clear = fand2(gin106clear, 4);

    assert(ctx.decrypt(&gout106) == gout106clear);
    std::cerr << "\rLUT107   ";
    Ciphertext gin107 = 2 * (1 - gout95) + gout33;
    Ciphertext gout107 = ctx.eval_lut(&gin107, or2);

    auto gin107clear = 2 * (1 - gout95clear) + gout33clear;
    auto gout107clear = for2(gin107clear, 4);

    assert(ctx.decrypt(&gout107) == gout107clear);
    std::cerr << "\rLUT108   ";
    Ciphertext gin108 = 2 * ct_y9 + ct_x5;
    Ciphertext gout108 = ctx.eval_lut(&gin108, and2);

    auto gin108clear = 2 * ct_y9clear + ct_x5clear;
    auto gout108clear = fand2(gin108clear, 4);

    assert(ctx.decrypt(&gout108) == gout108clear);
    std::cerr << "\rLUT109   ";
    Ciphertext gin109 = 2 * ct_y0 + ct_x15;
    Ciphertext gout109 = ctx.eval_lut(&gin109, and2);

    auto gin109clear = 2 * ct_y0clear + ct_x15clear;
    auto gout109clear = fand2(gin109clear, 4);

    assert(ctx.decrypt(&gout109) == gout109clear);
    std::cerr << "\rLUT110   ";
    Ciphertext gin110 = 2 * gout61 + gout109;
    Ciphertext gout110 = ctx.eval_lut(&gin110, xnor2);

    auto gin110clear = 2 * gout61clear + gout109clear;
    auto gout110clear = fxnor2(gin110clear, 4);

    assert(ctx.decrypt(&gout110) == gout110clear);
    std::cerr << "\rLUT111   ";
    Ciphertext gin111 = 2 * ct_y13 + ct_x0;
    Ciphertext gout111 = ctx.eval_lut(&gin111, and2);

    auto gin111clear = 2 * ct_y13clear + ct_x0clear;
    auto gout111clear = fand2(gin111clear, 4);

    assert(ctx.decrypt(&gout111) == gout111clear);
    std::cerr << "\rLUT112   ";
    Ciphertext gin112 = 2 * gout104 + gout47;
    Ciphertext gout112 = ctx.eval_lut(&gin112, or2);

    auto gin112clear = 2 * gout104clear + gout47clear;
    auto gout112clear = for2(gin112clear, 4);

    assert(ctx.decrypt(&gout112) == gout112clear);
    std::cerr << "\rLUT113   ";
    Ciphertext gin113 = 2 * ct_y1 + ct_x0;
    Ciphertext gout113 = ctx.eval_lut(&gin113, and2);

    auto gin113clear = 2 * ct_y1clear + ct_x0clear;
    auto gout113clear = fand2(gin113clear, 4);

    assert(ctx.decrypt(&gout113) == gout113clear);
    std::cerr << "\rLUT114   ";
    Ciphertext gin114 = 2 * gout71 + gout70;
    Ciphertext gout114 = ctx.eval_lut(&gin114, nand2);

    auto gin114clear = 2 * gout71clear + gout70clear;
    auto gout114clear = fnand2(gin114clear, 4);

    assert(ctx.decrypt(&gout114) == gout114clear);
    std::cerr << "\rINV115   ";
    Ciphertext gout115 = 1 - gout104;

    long gout115clear = 1 - gout104clear;

    assert(ctx.decrypt(&gout115) == gout115clear);
    std::cerr << "\rINV116   ";
    Ciphertext gout116 = 1 - ct_x10;

    long gout116clear = 1 - ct_x10clear;

    assert(ctx.decrypt(&gout116) == gout116clear);
    std::cerr << "\rLUT117   ";
    Ciphertext gin117 = 2 * ct_y4 + ct_x5;
    Ciphertext gout117 = ctx.eval_lut(&gin117, and2);

    auto gin117clear = 2 * ct_y4clear + ct_x5clear;
    auto gout117clear = fand2(gin117clear, 4);

    assert(ctx.decrypt(&gout117) == gout117clear);
    std::cerr << "\rLUT118   ";
    Ciphertext gin118 = 2 * gout117 + gout36;
    Ciphertext gout118 = ctx.eval_lut(&gin118, xnor2);

    auto gin118clear = 2 * gout117clear + gout36clear;
    auto gout118clear = fxnor2(gin118clear, 4);

    assert(ctx.decrypt(&gout118) == gout118clear);
    std::cerr << "\rLUT119   ";
    Ciphertext gin119 = 2 * gout83 + gout118;
    Ciphertext gout119 = ctx.eval_lut(&gin119, xor2);

    auto gin119clear = 2 * gout83clear + gout118clear;
    auto gout119clear = fxor2(gin119clear, 4);

    assert(ctx.decrypt(&gout119) == gout119clear);
    std::cerr << "\rLUT120   ";
    Ciphertext gin120 = 2 * gout83 + gout118;
    Ciphertext gout120 = ctx.eval_lut(&gin120, nand2);

    auto gin120clear = 2 * gout83clear + gout118clear;
    auto gout120clear = fnand2(gin120clear, 4);

    assert(ctx.decrypt(&gout120) == gout120clear);
    std::cerr << "\rLUT121   ";
    Ciphertext gin121 = 2 * ct_y8 + ct_x7;
    Ciphertext gout121 = ctx.eval_lut(&gin121, and2);

    auto gin121clear = 2 * ct_y8clear + ct_x7clear;
    auto gout121clear = fand2(gin121clear, 4);

    assert(ctx.decrypt(&gout121) == gout121clear);
    std::cerr << "\rLUT122   ";
    Ciphertext gin122 = 2 * gout63 + gout11;
    Ciphertext gout122 = ctx.eval_lut(&gin122, xor2);

    auto gin122clear = 2 * gout63clear + gout11clear;
    auto gout122clear = fxor2(gin122clear, 4);

    assert(ctx.decrypt(&gout122) == gout122clear);
    std::cerr << "\rLUT123   ";
    Ciphertext gin123 = 2 * ct_y9 + ct_x3;
    Ciphertext gout123 = ctx.eval_lut(&gin123, and2);

    auto gin123clear = 2 * ct_y9clear + ct_x3clear;
    auto gout123clear = fand2(gin123clear, 4);

    assert(ctx.decrypt(&gout123) == gout123clear);
    std::cerr << "\rLUT124   ";
    Ciphertext gin124 = 2 * gout75 + gout123;
    Ciphertext gout124 = ctx.eval_lut(&gin124, xor2);

    auto gin124clear = 2 * gout75clear + gout123clear;
    auto gout124clear = fxor2(gin124clear, 4);

    assert(ctx.decrypt(&gout124) == gout124clear);
    std::cerr << "\rLUT125   ";
    Ciphertext gin125 = 2 * gout75 + gout123;
    Ciphertext gout125 = ctx.eval_lut(&gin125, nand2);

    auto gin125clear = 2 * gout75clear + gout123clear;
    auto gout125clear = fnand2(gin125clear, 4);

    assert(ctx.decrypt(&gout125) == gout125clear);
    std::cerr << "\rLUT126   ";
    Ciphertext gin126 = 2 * ct_y1 + ct_x8;
    Ciphertext gout126 = ctx.eval_lut(&gin126, and2);

    auto gin126clear = 2 * ct_y1clear + ct_x8clear;
    auto gout126clear = fand2(gin126clear, 4);

    assert(ctx.decrypt(&gout126) == gout126clear);
    std::cerr << "\rLUT127   ";
    Ciphertext gin127 = 2 * ct_y13 + ct_x1;
    Ciphertext gout127 = ctx.eval_lut(&gin127, and2);

    auto gin127clear = 2 * ct_y13clear + ct_x1clear;
    auto gout127clear = fand2(gin127clear, 4);

    assert(ctx.decrypt(&gout127) == gout127clear);
    std::cerr << "\rLUT128   ";
    Ciphertext gin128 = 2 * gout1 + gout12;
    Ciphertext gout128 = ctx.eval_lut(&gin128, nand2);

    auto gin128clear = 2 * gout1clear + gout12clear;
    auto gout128clear = fnand2(gin128clear, 4);

    assert(ctx.decrypt(&gout128) == gout128clear);
    std::cerr << "\rLUT129   ";
    Ciphertext gin129 = 2 * gout86 + gout89;
    Ciphertext gout129 = ctx.eval_lut(&gin129, xnor2);

    auto gin129clear = 2 * gout86clear + gout89clear;
    auto gout129clear = fxnor2(gin129clear, 4);

    assert(ctx.decrypt(&gout129) == gout129clear);
    std::cerr << "\rLUT130   ";
    Ciphertext gin130 = 2 * ct_y0 + ct_x8;
    Ciphertext gout130 = ctx.eval_lut(&gin130, nand2);

    auto gin130clear = 2 * ct_y0clear + ct_x8clear;
    auto gout130clear = fnand2(gin130clear, 4);

    assert(ctx.decrypt(&gout130) == gout130clear);
    std::cerr << "\rLUT131   ";
    Ciphertext gin131 = 2 * gout72 + gout130;
    Ciphertext gout131 = ctx.eval_lut(&gin131, xnor2);

    auto gin131clear = 2 * gout72clear + gout130clear;
    auto gout131clear = fxnor2(gin131clear, 4);

    assert(ctx.decrypt(&gout131) == gout131clear);
    std::cerr << "\rLUT132   ";
    Ciphertext gin132 = 2 * gout46 + gout131;
    Ciphertext gout132 = ctx.eval_lut(&gin132, xor2);

    auto gin132clear = 2 * gout46clear + gout131clear;
    auto gout132clear = fxor2(gin132clear, 4);

    assert(ctx.decrypt(&gout132) == gout132clear);
    std::cerr << "\rLUT133   ";
    Ciphertext gin133 = 2 * gout46 + gout131;
    Ciphertext gout133 = ctx.eval_lut(&gin133, nand2);

    auto gin133clear = 2 * gout46clear + gout131clear;
    auto gout133clear = fnand2(gin133clear, 4);

    assert(ctx.decrypt(&gout133) == gout133clear);
    std::cerr << "\rLUT134   ";
    Ciphertext gin134 = 2 * ct_y4 + ct_x6;
    Ciphertext gout134 = ctx.eval_lut(&gin134, and2);

    auto gin134clear = 2 * ct_y4clear + ct_x6clear;
    auto gout134clear = fand2(gin134clear, 4);

    assert(ctx.decrypt(&gout134) == gout134clear);
    std::cerr << "\rLUT135   ";
    Ciphertext gin135 = 2 * ct_y5 + ct_x0;
    Ciphertext gout135 = ctx.eval_lut(&gin135, and2);

    auto gin135clear = 2 * ct_y5clear + ct_x0clear;
    auto gout135clear = fand2(gin135clear, 4);

    assert(ctx.decrypt(&gout135) == gout135clear);
    std::cerr << "\rINV136   ";
    Ciphertext gout136 = 1 - gout91;

    long gout136clear = 1 - gout91clear;

    assert(ctx.decrypt(&gout136) == gout136clear);
    std::cerr << "\rLUT137   ";
    Ciphertext gin137 = 2 * gout9 + gout124;
    Ciphertext gout137 = ctx.eval_lut(&gin137, nand2);

    auto gin137clear = 2 * gout9clear + gout124clear;
    auto gout137clear = fnand2(gin137clear, 4);

    assert(ctx.decrypt(&gout137) == gout137clear);
    std::cerr << "\rLUT138   ";
    Ciphertext gin138 = 2 * gout125 + gout137;
    Ciphertext gout138 = ctx.eval_lut(&gin138, nand2);

    auto gin138clear = 2 * gout125clear + gout137clear;
    auto gout138clear = fnand2(gin138clear, 4);

    assert(ctx.decrypt(&gout138) == gout138clear);
    std::cerr << "\rLUT139   ";
    Ciphertext gin139 = 2 * ct_y7 + ct_x6;
    Ciphertext gout139 = ctx.eval_lut(&gin139, and2);

    auto gin139clear = 2 * ct_y7clear + ct_x6clear;
    auto gout139clear = fand2(gin139clear, 4);

    assert(ctx.decrypt(&gout139) == gout139clear);
    std::cerr << "\rLUT140   ";
    Ciphertext gin140 = 2 * ct_y8 + ct_x4;
    Ciphertext gout140 = ctx.eval_lut(&gin140, and2);

    auto gin140clear = 2 * ct_y8clear + ct_x4clear;
    auto gout140clear = fand2(gin140clear, 4);

    assert(ctx.decrypt(&gout140) == gout140clear);
    std::cerr << "\rLUT141   ";
    Ciphertext gin141 = 2 * ct_y6 + ct_x3;
    Ciphertext gout141 = ctx.eval_lut(&gin141, and2);

    auto gin141clear = 2 * ct_y6clear + ct_x3clear;
    auto gout141clear = fand2(gin141clear, 4);

    assert(ctx.decrypt(&gout141) == gout141clear);
    std::cerr << "\rLUT142   ";
    Ciphertext gin142 = 2 * gout102 + gout141;
    Ciphertext gout142 = ctx.eval_lut(&gin142, xor2);

    auto gin142clear = 2 * gout102clear + gout141clear;
    auto gout142clear = fxor2(gin142clear, 4);

    assert(ctx.decrypt(&gout142) == gout142clear);
    std::cerr << "\rLUT143   ";
    Ciphertext gin143 = 2 * gout102 + gout141;
    Ciphertext gout143 = ctx.eval_lut(&gin143, nand2);

    auto gin143clear = 2 * gout102clear + gout141clear;
    auto gout143clear = fnand2(gin143clear, 4);

    assert(ctx.decrypt(&gout143) == gout143clear);
    std::cerr << "\rLUT144   ";
    Ciphertext gin144 = 2 * ct_y2 + ct_x1;
    Ciphertext gout144 = ctx.eval_lut(&gin144, and2);

    auto gin144clear = 2 * ct_y2clear + ct_x1clear;
    auto gout144clear = fand2(gin144clear, 4);

    assert(ctx.decrypt(&gout144) == gout144clear);
    std::cerr << "\rLUT145   ";
    Ciphertext gin145 = 2 * gout144 + gout16;
    Ciphertext gout145 = ctx.eval_lut(&gin145, xnor2);

    auto gin145clear = 2 * gout144clear + gout16clear;
    auto gout145clear = fxnor2(gin145clear, 4);

    assert(ctx.decrypt(&gout145) == gout145clear);
    std::cerr << "\rLUT146   ";
    Ciphertext gin146 = 2 * ct_y0 + ct_x2;
    Ciphertext gout146 = ctx.eval_lut(&gin146, and2);

    auto gin146clear = 2 * ct_y0clear + ct_x2clear;
    auto gout146clear = fand2(gin146clear, 4);

    assert(ctx.decrypt(&gout146) == gout146clear);
    std::cerr << "\rINV147   ";
    Ciphertext gout147 = 1 - gout146;

    long gout147clear = 1 - gout146clear;

    assert(ctx.decrypt(&gout147) == gout147clear);
    std::cerr << "\rLUT148   ";
    Ciphertext gin148 = 2 * ct_y3 + ct_x4;
    Ciphertext gout148 = ctx.eval_lut(&gin148, and2);

    auto gin148clear = 2 * ct_y3clear + ct_x4clear;
    auto gout148clear = fand2(gin148clear, 4);

    assert(ctx.decrypt(&gout148) == gout148clear);
    std::cerr << "\rLUT149   ";
    Ciphertext gin149 = 2 * ct_y5 + ct_x8;
    Ciphertext gout149 = ctx.eval_lut(&gin149, and2);

    auto gin149clear = 2 * ct_y5clear + ct_x8clear;
    auto gout149clear = fand2(gin149clear, 4);

    assert(ctx.decrypt(&gout149) == gout149clear);
    std::cerr << "\rLUT150   ";
    Ciphertext gin150 = 2 * ct_y2 + ct_x13;
    Ciphertext gout150 = ctx.eval_lut(&gin150, and2);

    auto gin150clear = 2 * ct_y2clear + ct_x13clear;
    auto gout150clear = fand2(gin150clear, 4);

    assert(ctx.decrypt(&gout150) == gout150clear);
    std::cerr << "\rLUT151   ";
    Ciphertext gin151 = 2 * gout150 + gout53;
    Ciphertext gout151 = ctx.eval_lut(&gin151, xnor2);

    auto gin151clear = 2 * gout150clear + gout53clear;
    auto gout151clear = fxnor2(gin151clear, 4);

    assert(ctx.decrypt(&gout151) == gout151clear);
    std::cerr << "\rLUT152   ";
    Ciphertext gin152 = 2 * gout110 + gout151;
    Ciphertext gout152 = ctx.eval_lut(&gin152, xnor2);

    auto gin152clear = 2 * gout110clear + gout151clear;
    auto gout152clear = fxnor2(gin152clear, 4);

    assert(ctx.decrypt(&gout152) == gout152clear);
    std::cerr << "\rLUT153   ";
    Ciphertext gin153 = 2 * gout9 + gout124;
    Ciphertext gout153 = ctx.eval_lut(&gin153, xor2);

    auto gin153clear = 2 * gout9clear + gout124clear;
    auto gout153clear = fxor2(gin153clear, 4);

    assert(ctx.decrypt(&gout153) == gout153clear);
    std::cerr << "\rLUT154   ";
    Ciphertext gin154 = 2 * ct_y0 + ct_x1;
    Ciphertext gout154 = ctx.eval_lut(&gin154, and2);

    auto gin154clear = 2 * ct_y0clear + ct_x1clear;
    auto gout154clear = fand2(gin154clear, 4);

    assert(ctx.decrypt(&gout154) == gout154clear);
    std::cerr << "\rLUT155   ";
    Ciphertext gin155 = 2 * gout113 + gout154;
    Ciphertext gout155 = ctx.eval_lut(&gin155, xor2);

    auto gin155clear = 2 * gout113clear + gout154clear;
    auto gout155clear = fxor2(gin155clear, 4);

    assert(ctx.decrypt(&gout155) == gout155clear);
    std::cerr << "\rLUT156   ";
    Ciphertext gin156 = 2 * gout104 + gout155;
    Ciphertext gout156 = ctx.eval_lut(&gin156, nand2);

    auto gin156clear = 2 * gout104clear + gout155clear;
    auto gout156clear = fnand2(gin156clear, 4);

    assert(ctx.decrypt(&gout156) == gout156clear);
    std::cerr << "\rLUT157   ";
    Ciphertext gin157 = 2 * ct_y3 + ct_x7;
    Ciphertext gout157 = ctx.eval_lut(&gin157, and2);

    auto gin157clear = 2 * ct_y3clear + ct_x7clear;
    auto gout157clear = fand2(gin157clear, 4);

    assert(ctx.decrypt(&gout157) == gout157clear);
    std::cerr << "\rLUT158   ";
    Ciphertext gin158 = 2 * ct_y7 + ct_x1;
    Ciphertext gout158 = ctx.eval_lut(&gin158, and2);

    auto gin158clear = 2 * ct_y7clear + ct_x1clear;
    auto gout158clear = fand2(gin158clear, 4);

    assert(ctx.decrypt(&gout158) == gout158clear);
    std::cerr << "\rLUT159   ";
    Ciphertext gin159 = 2 * gout134 + gout30;
    Ciphertext gout159 = ctx.eval_lut(&gin159, xnor2);

    auto gin159clear = 2 * gout134clear + gout30clear;
    auto gout159clear = fxnor2(gin159clear, 4);

    assert(ctx.decrypt(&gout159) == gout159clear);
    std::cerr << "\rINV160   ";
    Ciphertext gout160 = 1 - ct_y4;

    long gout160clear = 1 - ct_y4clear;

    assert(ctx.decrypt(&gout160) == gout160clear);
    std::cerr << "\rLUT161   ";
    Ciphertext gin161 = 2 * ct_y2 + ct_x10;
    Ciphertext gout161 = ctx.eval_lut(&gin161, and2);

    auto gin161clear = 2 * ct_y2clear + ct_x10clear;
    auto gout161clear = fand2(gin161clear, 4);

    assert(ctx.decrypt(&gout161) == gout161clear);
    std::cerr << "\rLUT162   ";
    Ciphertext gin162 = 2 * gout45 + gout161;
    Ciphertext gout162 = ctx.eval_lut(&gin162, xor2);

    auto gin162clear = 2 * gout45clear + gout161clear;
    auto gout162clear = fxor2(gin162clear, 4);

    assert(ctx.decrypt(&gout162) == gout162clear);
    std::cerr << "\rLUT163   ";
    Ciphertext gin163 = 2 * gout13 + gout162;
    Ciphertext gout163 = ctx.eval_lut(&gin163, xor2);

    auto gin163clear = 2 * gout13clear + gout162clear;
    auto gout163clear = fxor2(gin163clear, 4);

    assert(ctx.decrypt(&gout163) == gout163clear);
    std::cerr << "\rLUT164   ";
    Ciphertext gin164 = 2 * gout45 + gout161;
    Ciphertext gout164 = ctx.eval_lut(&gin164, nand2);

    auto gin164clear = 2 * gout45clear + gout161clear;
    auto gout164clear = fnand2(gin164clear, 4);

    assert(ctx.decrypt(&gout164) == gout164clear);
    std::cerr << "\rLUT165   ";
    Ciphertext gin165 = 2 * gout0 + gout60;
    Ciphertext gout165 = ctx.eval_lut(&gin165, xnor2);

    auto gin165clear = 2 * gout0clear + gout60clear;
    auto gout165clear = fxnor2(gin165clear, 4);

    assert(ctx.decrypt(&gout165) == gout165clear);
    std::cerr << "\rLUT166   ";
    Ciphertext gin166 = 2 * ct_y4 + ct_x7;
    Ciphertext gout166 = ctx.eval_lut(&gin166, and2);

    auto gin166clear = 2 * ct_y4clear + ct_x7clear;
    auto gout166clear = fand2(gin166clear, 4);

    assert(ctx.decrypt(&gout166) == gout166clear);
    std::cerr << "\rLUT167   ";
    Ciphertext gin167 = 2 * gout91 + gout166;
    Ciphertext gout167 = ctx.eval_lut(&gin167, nand2);

    auto gin167clear = 2 * gout91clear + gout166clear;
    auto gout167clear = fnand2(gin167clear, 4);

    assert(ctx.decrypt(&gout167) == gout167clear);
    std::cerr << "\rLUT168   ";
    Ciphertext gin168 = 2 * ct_y7 + ct_x8;
    Ciphertext gout168 = ctx.eval_lut(&gin168, and2);

    auto gin168clear = 2 * ct_y7clear + ct_x8clear;
    auto gout168clear = fand2(gin168clear, 4);

    assert(ctx.decrypt(&gout168) == gout168clear);
    std::cerr << "\rLUT169   ";
    Ciphertext gin169 = 2 * ct_y8 + ct_x6;
    Ciphertext gout169 = ctx.eval_lut(&gin169, and2);

    auto gin169clear = 2 * ct_y8clear + ct_x6clear;
    auto gout169clear = fand2(gin169clear, 4);

    assert(ctx.decrypt(&gout169) == gout169clear);
    std::cerr << "\rLUT170   ";
    Ciphertext gin170 = 2 * ct_y2 + ct_x2;
    Ciphertext gout170 = ctx.eval_lut(&gin170, and2);

    auto gin170clear = 2 * ct_y2clear + ct_x2clear;
    auto gout170clear = fand2(gin170clear, 4);

    assert(ctx.decrypt(&gout170) == gout170clear);
    std::cerr << "\rLUT171   ";
    Ciphertext gin171 = 2 * gout33 + gout170;
    Ciphertext gout171 = ctx.eval_lut(&gin171, xnor2);

    auto gin171clear = 2 * gout33clear + gout170clear;
    auto gout171clear = fxnor2(gin171clear, 4);

    assert(ctx.decrypt(&gout171) == gout171clear);
    std::cerr << "\rLUT172   ";
    Ciphertext gin172 = 2 * gout106 + gout171;
    Ciphertext gout172 = ctx.eval_lut(&gin172, xor2);

    auto gin172clear = 2 * gout106clear + gout171clear;
    auto gout172clear = fxor2(gin172clear, 4);

    assert(ctx.decrypt(&gout172) == gout172clear);
    std::cerr << "\rLUT173   ";
    Ciphertext gin173 = 2 * gout106 + gout171;
    Ciphertext gout173 = ctx.eval_lut(&gin173, nand2);

    auto gin173clear = 2 * gout106clear + gout171clear;
    auto gout173clear = fnand2(gin173clear, 4);

    assert(ctx.decrypt(&gout173) == gout173clear);
    std::cerr << "\rLUT174   ";
    Ciphertext gin174 = 2 * gout14 + gout42;
    Ciphertext gout174 = ctx.eval_lut(&gin174, nand2);

    auto gin174clear = 2 * gout14clear + gout42clear;
    auto gout174clear = fnand2(gin174clear, 4);

    assert(ctx.decrypt(&gout174) == gout174clear);
    std::cerr << "\rLUT175   ";
    Ciphertext gin175 = 2 * gout166 + gout87;
    Ciphertext gout175 = ctx.eval_lut(&gin175, xnor2);

    auto gin175clear = 2 * gout166clear + gout87clear;
    auto gout175clear = fxnor2(gin175clear, 4);

    assert(ctx.decrypt(&gout175) == gout175clear);
    std::cerr << "\rLUT176   ";
    Ciphertext gin176 = 2 * gout14 + gout42;
    Ciphertext gout176 = ctx.eval_lut(&gin176, xor2);

    auto gin176clear = 2 * gout14clear + gout42clear;
    auto gout176clear = fxor2(gin176clear, 4);

    assert(ctx.decrypt(&gout176) == gout176clear);
    std::cerr << "\rLUT177   ";
    Ciphertext gin177 = 2 * ct_y11 + ct_x3;
    Ciphertext gout177 = ctx.eval_lut(&gin177, and2);

    auto gin177clear = 2 * ct_y11clear + ct_x3clear;
    auto gout177clear = fand2(gin177clear, 4);

    assert(ctx.decrypt(&gout177) == gout177clear);
    std::cerr << "\rLUT178   ";
    Ciphertext gin178 = 2 * ct_y3 + ct_x2;
    Ciphertext gout178 = ctx.eval_lut(&gin178, and2);

    auto gin178clear = 2 * ct_y3clear + ct_x2clear;
    auto gout178clear = fand2(gin178clear, 4);

    assert(ctx.decrypt(&gout178) == gout178clear);
    std::cerr << "\rLUT179   ";
    Ciphertext gin179 = 2 * gout178 + gout93;
    Ciphertext gout179 = ctx.eval_lut(&gin179, nand2);

    auto gin179clear = 2 * gout178clear + gout93clear;
    auto gout179clear = fnand2(gin179clear, 4);

    assert(ctx.decrypt(&gout179) == gout179clear);
    std::cerr << "\rLUT180   ";
    Ciphertext gin180 = 2 * gout144 + gout178;
    Ciphertext gout180 = ctx.eval_lut(&gin180, nand2);

    auto gin180clear = 2 * gout144clear + gout178clear;
    auto gout180clear = fnand2(gin180clear, 4);

    assert(ctx.decrypt(&gout180) == gout180clear);
    std::cerr << "\rLUT181   ";
    Ciphertext gin181 = 2 * gout180 + gout173;
    Ciphertext gout181 = ctx.eval_lut(&gin181, nand2);

    auto gin181clear = 2 * gout180clear + gout173clear;
    auto gout181clear = fnand2(gin181clear, 4);

    assert(ctx.decrypt(&gout181) == gout181clear);
    std::cerr << "\rLUT182   ";
    Ciphertext gin182 = 2 * gout157 + gout58;
    Ciphertext gout182 = ctx.eval_lut(&gin182, nand2);

    auto gin182clear = 2 * gout157clear + gout58clear;
    auto gout182clear = fnand2(gin182clear, 4);

    assert(ctx.decrypt(&gout182) == gout182clear);
    std::cerr << "\rLUT183   ";
    Ciphertext gin183 = 2 * ct_y0 + ct_x7;
    Ciphertext gout183 = ctx.eval_lut(&gin183, nand2);

    auto gin183clear = 2 * ct_y0clear + ct_x7clear;
    auto gout183clear = fnand2(gin183clear, 4);

    assert(ctx.decrypt(&gout183) == gout183clear);
    std::cerr << "\rLUT184   ";
    Ciphertext gin184 = 2 * gout183 + gout97;
    Ciphertext gout184 = ctx.eval_lut(&gin184, xnor2);

    auto gin184clear = 2 * gout183clear + gout97clear;
    auto gout184clear = fxnor2(gin184clear, 4);

    assert(ctx.decrypt(&gout184) == gout184clear);
    std::cerr << "\rLUT185   ";
    Ciphertext gin185 = 2 * gout2 + gout184;
    Ciphertext gout185 = ctx.eval_lut(&gin185, xor2);

    auto gin185clear = 2 * gout2clear + gout184clear;
    auto gout185clear = fxor2(gin185clear, 4);

    assert(ctx.decrypt(&gout185) == gout185clear);
    std::cerr << "\rLUT186   ";
    Ciphertext gin186 = 2 * gout2 + gout184;
    Ciphertext gout186 = ctx.eval_lut(&gin186, nand2);

    auto gin186clear = 2 * gout2clear + gout184clear;
    auto gout186clear = fnand2(gin186clear, 4);

    assert(ctx.decrypt(&gout186) == gout186clear);
    std::cerr << "\rLUT187   ";
    Ciphertext gin187 = 2 * gout167 + gout186;
    Ciphertext gout187 = ctx.eval_lut(&gin187, nand2);

    auto gin187clear = 2 * gout167clear + gout186clear;
    auto gout187clear = fnand2(gin187clear, 4);

    assert(ctx.decrypt(&gout187) == gout187clear);
    std::cerr << "\rLUT188   ";
    Ciphertext gin188 = 2 * gout178 + gout93;
    Ciphertext gout188 = ctx.eval_lut(&gin188, xor2);

    auto gin188clear = 2 * gout178clear + gout93clear;
    auto gout188clear = fxor2(gin188clear, 4);

    assert(ctx.decrypt(&gout188) == gout188clear);
    std::cerr << "\rLUT189   ";
    Ciphertext gin189 = 2 * gout66 + gout188;
    Ciphertext gout189 = ctx.eval_lut(&gin189, xor2);

    auto gin189clear = 2 * gout66clear + gout188clear;
    auto gout189clear = fxor2(gin189clear, 4);

    assert(ctx.decrypt(&gout189) == gout189clear);
    std::cerr << "\rLUT190   ";
    Ciphertext gin190 = 2 * gout181 + gout189;
    Ciphertext gout190 = ctx.eval_lut(&gin190, xnor2);

    auto gin190clear = 2 * gout181clear + gout189clear;
    auto gout190clear = fxnor2(gin190clear, 4);

    assert(ctx.decrypt(&gout190) == gout190clear);
    std::cerr << "\rLUT191   ";
    Ciphertext gin191 = 2 * gout181 + gout189;
    Ciphertext gout191 = ctx.eval_lut(&gin191, and2);

    auto gin191clear = 2 * gout181clear + gout189clear;
    auto gout191clear = fand2(gin191clear, 4);

    assert(ctx.decrypt(&gout191) == gout191clear);
    std::cerr << "\rLUT192   ";
    Ciphertext gin192 = 2 * gout66 + gout188;
    Ciphertext gout192 = ctx.eval_lut(&gin192, nand2);

    auto gin192clear = 2 * gout66clear + gout188clear;
    auto gout192clear = fnand2(gin192clear, 4);

    assert(ctx.decrypt(&gout192) == gout192clear);
    std::cerr << "\rLUT193   ";
    Ciphertext gin193 = 2 * gout179 + gout192;
    Ciphertext gout193 = ctx.eval_lut(&gin193, nand2);

    auto gin193clear = 2 * gout179clear + gout192clear;
    auto gout193clear = fnand2(gin193clear, 4);

    assert(ctx.decrypt(&gout193) == gout193clear);
    std::cerr << "\rLUT194   ";
    Ciphertext gin194 = 2 * ct_y12 + ct_x0;
    Ciphertext gout194 = ctx.eval_lut(&gin194, and2);

    auto gin194clear = 2 * ct_y12clear + ct_x0clear;
    auto gout194clear = fand2(gin194clear, 4);

    assert(ctx.decrypt(&gout194) == gout194clear);
    std::cerr << "\rINV195   ";
    Ciphertext gout195 = 1 - ct_x5;

    long gout195clear = 1 - ct_x5clear;

    assert(ctx.decrypt(&gout195) == gout195clear);
    std::cerr << "\rLUT196   ";
    Ciphertext gin196 = 2 * gout157 + gout58;
    Ciphertext gout196 = ctx.eval_lut(&gin196, xor2);

    auto gin196clear = 2 * gout157clear + gout58clear;
    auto gout196clear = fxor2(gin196clear, 4);

    assert(ctx.decrypt(&gout196) == gout196clear);
    std::cerr << "\rINV197   ";
    Ciphertext gout197 = 1 - ct_x13;

    long gout197clear = 1 - ct_x13clear;

    assert(ctx.decrypt(&gout197) == gout197clear);
    std::cerr << "\rINV198   ";
    Ciphertext gout198 = 1 - ct_y9;

    long gout198clear = 1 - ct_y9clear;

    assert(ctx.decrypt(&gout198) == gout198clear);
    std::cerr << "\rINV199   ";
    Ciphertext gout199 = 1 - ct_y8;

    long gout199clear = 1 - ct_y8clear;

    assert(ctx.decrypt(&gout199) == gout199clear);
    std::cerr << "\rLUT200   ";
    Ciphertext gin200 = 2 * ct_y6 + ct_x1;
    Ciphertext gout200 = ctx.eval_lut(&gin200, nand2);

    auto gin200clear = 2 * ct_y6clear + ct_x1clear;
    auto gout200clear = fnand2(gin200clear, 4);

    assert(ctx.decrypt(&gout200) == gout200clear);
    std::cerr << "\rLUT201   ";
    Ciphertext gin201 = 2 * ct_y5 + ct_x1;
    Ciphertext gout201 = ctx.eval_lut(&gin201, and2);

    auto gin201clear = 2 * ct_y5clear + ct_x1clear;
    auto gout201clear = fand2(gin201clear, 4);

    assert(ctx.decrypt(&gout201) == gout201clear);
    std::cerr << "\rLUT202   ";
    Ciphertext gin202 = 2 * ct_y4 + ct_x9;
    Ciphertext gout202 = ctx.eval_lut(&gin202, and2);

    auto gin202clear = 2 * ct_y4clear + ct_x9clear;
    auto gout202clear = fand2(gin202clear, 4);

    assert(ctx.decrypt(&gout202) == gout202clear);
    std::cerr << "\rLUT203   ";
    Ciphertext gin203 = 2 * ct_y11 + ct_x0;
    Ciphertext gout203 = ctx.eval_lut(&gin203, and2);

    auto gin203clear = 2 * ct_y11clear + ct_x0clear;
    auto gout203clear = fand2(gin203clear, 4);

    assert(ctx.decrypt(&gout203) == gout203clear);
    std::cerr << "\rLUT204   ";
    Ciphertext gin204 = 2 * gout154 + gout117;
    Ciphertext gout204 = ctx.eval_lut(&gin204, nand2);

    auto gin204clear = 2 * gout154clear + gout117clear;
    auto gout204clear = fnand2(gin204clear, 4);

    assert(ctx.decrypt(&gout204) == gout204clear);
    std::cerr << "\rLUT205   ";
    Ciphertext gin205 = 2 * ct_y1 + ct_x1;
    Ciphertext gout205 = ctx.eval_lut(&gin205, nand2);

    auto gin205clear = 2 * ct_y1clear + ct_x1clear;
    auto gout205clear = fnand2(gin205clear, 4);

    assert(ctx.decrypt(&gout205) == gout205clear);
    std::cerr << "\rLUT206   ";
    Ciphertext gin206 = 2 * gout205 + gout95;
    Ciphertext gout206 = ctx.eval_lut(&gin206, xnor2);

    auto gin206clear = 2 * gout205clear + gout95clear;
    auto gout206clear = fxnor2(gin206clear, 4);

    assert(ctx.decrypt(&gout206) == gout206clear);
    std::cerr << "\rLUT207   ";
    Ciphertext gin207 = 2 * gout146 + gout206;
    Ciphertext gout207 = ctx.eval_lut(&gin207, and2);

    auto gin207clear = 2 * gout146clear + gout206clear;
    auto gout207clear = fand2(gin207clear, 4);

    assert(ctx.decrypt(&gout207) == gout207clear);
    std::cerr << "\rINV208   ";
    Ciphertext gout208 = 1 - gout207;

    long gout208clear = 1 - gout207clear;

    assert(ctx.decrypt(&gout208) == gout208clear);
    std::cerr << "\rLUT209   ";
    Ciphertext gin209 = 2 * (1 - ct_op1) + ct_op0;
    Ciphertext gout209 = ctx.eval_lut(&gin209, and2);

    auto gin209clear = 2 * (1 - ct_op1clear) + ct_op0clear;
    auto gout209clear = fand2(gin209clear, 4);

    assert(ctx.decrypt(&gout209) == gout209clear);
    std::cerr << "\rLUT210   ";
    Ciphertext gin210 = 2 * gout209 + gout17;
    Ciphertext gout210 = ctx.eval_lut(&gin210, and2);

    auto gin210clear = 2 * gout209clear + gout17clear;
    auto gout210clear = fand2(gin210clear, 4);

    assert(ctx.decrypt(&gout210) == gout210clear);
    std::cerr << "\rLUT211   ";
    Ciphertext gin211 = 2 * gout77 + gout210;
    Ciphertext gout211 = ctx.eval_lut(&gin211, and2);

    auto gin211clear = 2 * gout77clear + gout210clear;
    auto gout211clear = fand2(gin211clear, 4);

    assert(ctx.decrypt(&gout211) == gout211clear);
    std::cerr << "\rLUT212   ";
    Ciphertext gin212 = 2 * ct_y14 + gout211;
    Ciphertext gout212 = ctx.eval_lut(&gin212, and2);

    auto gin212clear = 2 * ct_y14clear + gout211clear;
    auto gout212clear = fand2(gin212clear, 4);

    assert(ctx.decrypt(&gout212) == gout212clear);
    std::cerr << "\rLUT213   ";
    Ciphertext gin213 = 2 * ct_y13 + gout211;
    Ciphertext gout213 = ctx.eval_lut(&gin213, and2);

    auto gin213clear = 2 * ct_y13clear + gout211clear;
    auto gout213clear = fand2(gin213clear, 4);

    assert(ctx.decrypt(&gout213) == gout213clear);
    std::cerr << "\rLUT214   ";
    Ciphertext gin214 = 2 * ct_y12 + gout211;
    Ciphertext gout214 = ctx.eval_lut(&gin214, nand2);

    auto gin214clear = 2 * ct_y12clear + gout211clear;
    auto gout214clear = fnand2(gin214clear, 4);

    assert(ctx.decrypt(&gout214) == gout214clear);
    std::cerr << "\rLUT215   ";
    Ciphertext gin215 = 2 * ct_y11 + gout211;
    Ciphertext gout215 = ctx.eval_lut(&gin215, nand2);

    auto gin215clear = 2 * ct_y11clear + gout211clear;
    auto gout215clear = fnand2(gin215clear, 4);

    assert(ctx.decrypt(&gout215) == gout215clear);
    std::cerr << "\rLUT216   ";
    Ciphertext gin216 = 2 * gout211 + gout10;
    Ciphertext gout216 = ctx.eval_lut(&gin216, and2);

    auto gin216clear = 2 * gout211clear + gout10clear;
    auto gout216clear = fand2(gin216clear, 4);

    assert(ctx.decrypt(&gout216) == gout216clear);
    std::cerr << "\rLUT217   ";
    Ciphertext gin217 = 2 * ct_y0 + gout211;
    Ciphertext gout217 = ctx.eval_lut(&gin217, and2);

    auto gin217clear = 2 * ct_y0clear + gout211clear;
    auto gout217clear = fand2(gin217clear, 4);

    assert(ctx.decrypt(&gout217) == gout217clear);
    std::cerr << "\rLUT218   ";
    Ciphertext gin218 = 2 * gout100 + gout211;
    Ciphertext gout218 = ctx.eval_lut(&gin218, or2);

    auto gin218clear = 2 * gout100clear + gout211clear;
    auto gout218clear = for2(gin218clear, 4);

    assert(ctx.decrypt(&gout218) == gout218clear);
    std::cerr << "\rLUT219   ";
    Ciphertext gin219 = 2 * gout218 + gout156;
    Ciphertext gout219 = ctx.eval_lut(&gin219, and2);

    auto gin219clear = 2 * gout218clear + gout156clear;
    auto gout219clear = fand2(gin219clear, 4);

    assert(ctx.decrypt(&gout219) == gout219clear);
    std::cerr << "\rLUT220   ";
    Ciphertext gin220 = 2 * gout218 + gout112;
    Ciphertext gout220 = ctx.eval_lut(&gin220, and2);

    auto gin220clear = 2 * gout218clear + gout112clear;
    auto gout220clear = fand2(gin220clear, 4);

    assert(ctx.decrypt(&gout220) == gout220clear);
    std::cerr << "\rLUT221   ";
    Ciphertext gin221 = 2 * ct_y12 + ct_x2;
    Ciphertext gout221 = ctx.eval_lut(&gin221, nand2);

    auto gin221clear = 2 * ct_y12clear + ct_x2clear;
    auto gout221clear = fnand2(gin221clear, 4);

    assert(ctx.decrypt(&gout221) == gout221clear);
    std::cerr << "\rLUT222   ";
    Ciphertext gin222 = 2 * gout127 + gout221;
    Ciphertext gout222 = ctx.eval_lut(&gin222, xnor2);

    auto gin222clear = 2 * gout127clear + gout221clear;
    auto gout222clear = fxnor2(gin222clear, 4);

    assert(ctx.decrypt(&gout222) == gout222clear);
    std::cerr << "\rLUT223   ";
    Ciphertext gin223 = 2 * gout90 + gout222;
    Ciphertext gout223 = ctx.eval_lut(&gin223, nand2);

    auto gin223clear = 2 * gout90clear + gout222clear;
    auto gout223clear = fnand2(gin223clear, 4);

    assert(ctx.decrypt(&gout223) == gout223clear);
    std::cerr << "\rLUT224   ";
    Ciphertext gin224 = 2 * gout13 + gout162;
    Ciphertext gout224 = ctx.eval_lut(&gin224, nand2);

    auto gin224clear = 2 * gout13clear + gout162clear;
    auto gout224clear = fnand2(gin224clear, 4);

    assert(ctx.decrypt(&gout224) == gout224clear);
    std::cerr << "\rLUT225   ";
    Ciphertext gin225 = 2 * ct_y6 + ct_x6;
    Ciphertext gout225 = ctx.eval_lut(&gin225, and2);

    auto gin225clear = 2 * ct_y6clear + ct_x6clear;
    auto gout225clear = fand2(gin225clear, 4);

    assert(ctx.decrypt(&gout225) == gout225clear);
    std::cerr << "\rLUT226   ";
    Ciphertext gin226 = 2 * gout15 + gout225;
    Ciphertext gout226 = ctx.eval_lut(&gin226, nand2);

    auto gin226clear = 2 * gout15clear + gout225clear;
    auto gout226clear = fnand2(gin226clear, 4);

    assert(ctx.decrypt(&gout226) == gout226clear);
    std::cerr << "\rLUT227   ";
    Ciphertext gin227 = 2 * ct_y9 + ct_x0;
    Ciphertext gout227 = ctx.eval_lut(&gin227, and2);

    auto gin227clear = 2 * ct_y9clear + ct_x0clear;
    auto gout227clear = fand2(gin227clear, 4);

    assert(ctx.decrypt(&gout227) == gout227clear);
    std::cerr << "\rLUT228   ";
    Ciphertext gin228 = 2 * gout227 + gout1;
    Ciphertext gout228 = ctx.eval_lut(&gin228, and2);

    auto gin228clear = 2 * gout227clear + gout1clear;
    auto gout228clear = fand2(gin228clear, 4);

    assert(ctx.decrypt(&gout228) == gout228clear);
    std::cerr << "\rINV229   ";
    Ciphertext gout229 = 1 - gout228;

    long gout229clear = 1 - gout228clear;

    assert(ctx.decrypt(&gout229) == gout229clear);
    std::cerr << "\rLUT230   ";
    Ciphertext gin230 = 2 * ct_y2 + ct_x5;
    Ciphertext gout230 = ctx.eval_lut(&gin230, and2);

    auto gin230clear = 2 * ct_y2clear + ct_x5clear;
    auto gout230clear = fand2(gin230clear, 4);

    assert(ctx.decrypt(&gout230) == gout230clear);
    std::cerr << "\rLUT231   ";
    Ciphertext gin231 = 2 * gout148 + gout230;
    Ciphertext gout231 = ctx.eval_lut(&gin231, xor2);

    auto gin231clear = 2 * gout148clear + gout230clear;
    auto gout231clear = fxor2(gin231clear, 4);

    assert(ctx.decrypt(&gout231) == gout231clear);
    std::cerr << "\rLUT232   ";
    Ciphertext gin232 = 2 * gout148 + gout230;
    Ciphertext gout232 = ctx.eval_lut(&gin232, nand2);

    auto gin232clear = 2 * gout148clear + gout230clear;
    auto gout232clear = fnand2(gin232clear, 4);

    assert(ctx.decrypt(&gout232) == gout232clear);
    std::cerr << "\rLUT233   ";
    Ciphertext gin233 = 2 * ct_y3 + ct_x11;
    Ciphertext gout233 = ctx.eval_lut(&gin233, nand2);

    auto gin233clear = 2 * ct_y3clear + ct_x11clear;
    auto gout233clear = fnand2(gin233clear, 4);

    assert(ctx.decrypt(&gout233) == gout233clear);
    std::cerr << "\rLUT234   ";
    Ciphertext gin234 = 2 * ct_y8 + ct_x1;
    Ciphertext gout234 = ctx.eval_lut(&gin234, and2);

    auto gin234clear = 2 * ct_y8clear + ct_x1clear;
    auto gout234clear = fand2(gin234clear, 4);

    assert(ctx.decrypt(&gout234) == gout234clear);
    std::cerr << "\rLUT235   ";
    Ciphertext gin235 = 2 * gout234 + gout142;
    Ciphertext gout235 = ctx.eval_lut(&gin235, xor2);

    auto gin235clear = 2 * gout234clear + gout142clear;
    auto gout235clear = fxor2(gin235clear, 4);

    assert(ctx.decrypt(&gout235) == gout235clear);
    std::cerr << "\rLUT236   ";
    Ciphertext gin236 = 2 * gout234 + gout142;
    Ciphertext gout236 = ctx.eval_lut(&gin236, nand2);

    auto gin236clear = 2 * gout234clear + gout142clear;
    auto gout236clear = fnand2(gin236clear, 4);

    assert(ctx.decrypt(&gout236) == gout236clear);
    std::cerr << "\rLUT237   ";
    Ciphertext gin237 = 2 * gout183 + (1 - gout81);
    Ciphertext gout237 = ctx.eval_lut(&gin237, or2);

    auto gin237clear = 2 * gout183clear + (1 - gout81clear);
    auto gout237clear = for2(gin237clear, 4);

    assert(ctx.decrypt(&gout237) == gout237clear);
    std::cerr << "\rLUT238   ";
    Ciphertext gin238 = 2 * gout96 + gout223;
    Ciphertext gout238 = ctx.eval_lut(&gin238, nand2);

    auto gin238clear = 2 * gout96clear + gout223clear;
    auto gout238clear = fnand2(gin238clear, 4);

    assert(ctx.decrypt(&gout238) == gout238clear);
    std::cerr << "\rLUT239   ";
    Ciphertext gin239 = 2 * gout113 + gout144;
    Ciphertext gout239 = ctx.eval_lut(&gin239, and2);

    auto gin239clear = 2 * gout113clear + gout144clear;
    auto gout239clear = fand2(gin239clear, 4);

    assert(ctx.decrypt(&gout239) == gout239clear);
    std::cerr << "\rLUT240   ";
    Ciphertext gin240 = 2 * gout15 + gout225;
    Ciphertext gout240 = ctx.eval_lut(&gin240, xor2);

    auto gin240clear = 2 * gout15clear + gout225clear;
    auto gout240clear = fxor2(gin240clear, 4);

    assert(ctx.decrypt(&gout240) == gout240clear);
    std::cerr << "\rLUT241   ";
    Ciphertext gin241 = 2 * gout140 + gout240;
    Ciphertext gout241 = ctx.eval_lut(&gin241, xor2);

    auto gin241clear = 2 * gout140clear + gout240clear;
    auto gout241clear = fxor2(gin241clear, 4);

    assert(ctx.decrypt(&gout241) == gout241clear);
    std::cerr << "\rLUT242   ";
    Ciphertext gin242 = 2 * gout140 + gout240;
    Ciphertext gout242 = ctx.eval_lut(&gin242, nand2);

    auto gin242clear = 2 * gout140clear + gout240clear;
    auto gout242clear = fnand2(gin242clear, 4);

    assert(ctx.decrypt(&gout242) == gout242clear);
    std::cerr << "\rLUT243   ";
    Ciphertext gin243 = 2 * gout226 + gout242;
    Ciphertext gout243 = ctx.eval_lut(&gin243, nand2);

    auto gin243clear = 2 * gout226clear + gout242clear;
    auto gout243clear = fnand2(gin243clear, 4);

    assert(ctx.decrypt(&gout243) == gout243clear);
    std::cerr << "\rLUT244   ";
    Ciphertext gin244 = 2 * ct_y6 + ct_x0;
    Ciphertext gout244 = ctx.eval_lut(&gin244, and2);

    auto gin244clear = 2 * ct_y6clear + ct_x0clear;
    auto gout244clear = fand2(gin244clear, 4);

    assert(ctx.decrypt(&gout244) == gout244clear);
    std::cerr << "\rLUT245   ";
    Ciphertext gin245 = 2 * (1 - ct_x0) + ct_y15;
    Ciphertext gout245 = ctx.eval_lut(&gin245, and2);

    auto gin245clear = 2 * (1 - ct_x0clear) + ct_y15clear;
    auto gout245clear = fand2(gin245clear, 4);

    assert(ctx.decrypt(&gout245) == gout245clear);
    std::cerr << "\rLUT246   ";
    Ciphertext gin246 = 2 * gout245 + gout51;
    Ciphertext gout246 = ctx.eval_lut(&gin246, xnor2);

    auto gin246clear = 2 * gout245clear + gout51clear;
    auto gout246clear = fxnor2(gin246clear, 4);

    assert(ctx.decrypt(&gout246) == gout246clear);
    std::cerr << "\rLUT247   ";
    Ciphertext gin247 = 2 * gout238 + gout246;
    Ciphertext gout247 = ctx.eval_lut(&gin247, xnor2);

    auto gin247clear = 2 * gout238clear + gout246clear;
    auto gout247clear = fxnor2(gin247clear, 4);

    assert(ctx.decrypt(&gout247) == gout247clear);
    std::cerr << "\rLUT248   ";
    Ciphertext gin248 = 2 * ct_y6 + ct_x8;
    Ciphertext gout248 = ctx.eval_lut(&gin248, and2);

    auto gin248clear = 2 * ct_y6clear + ct_x8clear;
    auto gout248clear = fand2(gin248clear, 4);

    assert(ctx.decrypt(&gout248) == gout248clear);
    std::cerr << "\rLUT249   ";
    Ciphertext gin249 = 2 * gout21 + gout248;
    Ciphertext gout249 = ctx.eval_lut(&gin249, xnor2);

    auto gin249clear = 2 * gout21clear + gout248clear;
    auto gout249clear = fxnor2(gin249clear, 4);

    assert(ctx.decrypt(&gout249) == gout249clear);
    std::cerr << "\rLUT250   ";
    Ciphertext gin250 = 2 * gout169 + gout249;
    Ciphertext gout250 = ctx.eval_lut(&gin250, xor2);

    auto gin250clear = 2 * gout169clear + gout249clear;
    auto gout250clear = fxor2(gin250clear, 4);

    assert(ctx.decrypt(&gout250) == gout250clear);
    std::cerr << "\rLUT251   ";
    Ciphertext gin251 = 2 * gout169 + gout249;
    Ciphertext gout251 = ctx.eval_lut(&gin251, nand2);

    auto gin251clear = 2 * gout169clear + gout249clear;
    auto gout251clear = fnand2(gin251clear, 4);

    assert(ctx.decrypt(&gout251) == gout251clear);
    std::cerr << "\rINV252   ";
    Ciphertext gout252 = 1 - gout194;

    long gout252clear = 1 - gout194clear;

    assert(ctx.decrypt(&gout252) == gout252clear);
    std::cerr << "\rLUT253   ";
    Ciphertext gin253 = 2 * ct_y0 + ct_x12;
    Ciphertext gout253 = ctx.eval_lut(&gin253, and2);

    auto gin253clear = 2 * ct_y0clear + ct_x12clear;
    auto gout253clear = fand2(gin253clear, 4);

    assert(ctx.decrypt(&gout253) == gout253clear);
    std::cerr << "\rLUT254   ";
    Ciphertext gin254 = 2 * ct_y0 + ct_x0;
    Ciphertext gout254 = ctx.eval_lut(&gin254, and2);

    auto gin254clear = 2 * ct_y0clear + ct_x0clear;
    auto gout254clear = fand2(gin254clear, 4);

    assert(ctx.decrypt(&gout254) == gout254clear);
    std::cerr << "\rLUT255   ";
    Ciphertext gin255 = 2 * gout254 + gout72;
    Ciphertext gout255 = ctx.eval_lut(&gin255, and2);

    auto gin255clear = 2 * gout254clear + gout72clear;
    auto gout255clear = fand2(gin255clear, 4);

    assert(ctx.decrypt(&gout255) == gout255clear);
    std::cerr << "\rINV256   ";
    Ciphertext gout256 = 1 - gout255;

    long gout256clear = 1 - gout255clear;

    assert(ctx.decrypt(&gout256) == gout256clear);
    std::cerr << "\rLUT257   ";
    Ciphertext gin257 = 2 * gout254 + (1 - gout205);
    Ciphertext gout257 = ctx.eval_lut(&gin257, and2);

    auto gin257clear = 2 * gout254clear + (1 - gout205clear);
    auto gout257clear = fand2(gin257clear, 4);

    assert(ctx.decrypt(&gout257) == gout257clear);
    std::cerr << "\rLUT258   ";
    Ciphertext gin258 = 2 * ct_y6 + ct_x2;
    Ciphertext gout258 = ctx.eval_lut(&gin258, and2);

    auto gin258clear = 2 * ct_y6clear + ct_x2clear;
    auto gout258clear = fand2(gin258clear, 4);

    assert(ctx.decrypt(&gout258) == gout258clear);
    std::cerr << "\rLUT259   ";
    Ciphertext gin259 = 2 * gout158 + gout258;
    Ciphertext gout259 = ctx.eval_lut(&gin259, nand2);

    auto gin259clear = 2 * gout158clear + gout258clear;
    auto gout259clear = fnand2(gin259clear, 4);

    assert(ctx.decrypt(&gout259) == gout259clear);
    std::cerr << "\rLUT260   ";
    Ciphertext gin260 = 2 * gout85 + gout122;
    Ciphertext gout260 = ctx.eval_lut(&gin260, nand2);

    auto gin260clear = 2 * gout85clear + gout122clear;
    auto gout260clear = fnand2(gin260clear, 4);

    assert(ctx.decrypt(&gout260) == gout260clear);
    std::cerr << "\rLUT261   ";
    Ciphertext gin261 = 2 * gout84 + gout260;
    Ciphertext gout261 = ctx.eval_lut(&gin261, and2);

    auto gin261clear = 2 * gout84clear + gout260clear;
    auto gout261clear = fand2(gin261clear, 4);

    assert(ctx.decrypt(&gout261) == gout261clear);
    std::cerr << "\rLUT262   ";
    Ciphertext gin262 = 2 * gout40 + gout108;
    Ciphertext gout262 = ctx.eval_lut(&gin262, xnor2);

    auto gin262clear = 2 * gout40clear + gout108clear;
    auto gout262clear = fxnor2(gin262clear, 4);

    assert(ctx.decrypt(&gout262) == gout262clear);
    std::cerr << "\rLUT263   ";
    Ciphertext gin263 = 2 * gout177 + gout262;
    Ciphertext gout263 = ctx.eval_lut(&gin263, nand2);

    auto gin263clear = 2 * gout177clear + gout262clear;
    auto gout263clear = fnand2(gin263clear, 4);

    assert(ctx.decrypt(&gout263) == gout263clear);
    std::cerr << "\rLUT264   ";
    Ciphertext gin264 = 2 * gout85 + gout122;
    Ciphertext gout264 = ctx.eval_lut(&gin264, xor2);

    auto gin264clear = 2 * gout85clear + gout122clear;
    auto gout264clear = fxor2(gin264clear, 4);

    assert(ctx.decrypt(&gout264) == gout264clear);
    std::cerr << "\rLUT265   ";
    Ciphertext gin265 = 2 * ct_y9 + ct_x4;
    Ciphertext gout265 = ctx.eval_lut(&gin265, and2);

    auto gin265clear = 2 * ct_y9clear + ct_x4clear;
    auto gout265clear = fand2(gin265clear, 4);

    assert(ctx.decrypt(&gout265) == gout265clear);
    std::cerr << "\rLUT266   ";
    Ciphertext gin266 = 2 * gout265 + gout78;
    Ciphertext gout266 = ctx.eval_lut(&gin266, nand2);

    auto gin266clear = 2 * gout265clear + gout78clear;
    auto gout266clear = fnand2(gin266clear, 4);

    assert(ctx.decrypt(&gout266) == gout266clear);
    std::cerr << "\rLUT267   ";
    Ciphertext gin267 = 2 * gout266 + gout263;
    Ciphertext gout267 = ctx.eval_lut(&gin267, and2);

    auto gin267clear = 2 * gout266clear + gout263clear;
    auto gout267clear = fand2(gin267clear, 4);

    assert(ctx.decrypt(&gout267) == gout267clear);
    std::cerr << "\rLUT268   ";
    Ciphertext gin268 = 2 * gout38 + gout267;
    Ciphertext gout268 = ctx.eval_lut(&gin268, xnor2);

    auto gin268clear = 2 * gout38clear + gout267clear;
    auto gout268clear = fxnor2(gin268clear, 4);

    assert(ctx.decrypt(&gout268) == gout268clear);
    std::cerr << "\rLUT269   ";
    Ciphertext gin269 = 2 * ct_y5 + ct_x5;
    Ciphertext gout269 = ctx.eval_lut(&gin269, and2);

    auto gin269clear = 2 * ct_y5clear + ct_x5clear;
    auto gout269clear = fand2(gin269clear, 4);

    assert(ctx.decrypt(&gout269) == gout269clear);
    std::cerr << "\rLUT270   ";
    Ciphertext gin270 = 2 * gout269 + gout159;
    Ciphertext gout270 = ctx.eval_lut(&gin270, xor2);

    auto gin270clear = 2 * gout269clear + gout159clear;
    auto gout270clear = fxor2(gin270clear, 4);

    assert(ctx.decrypt(&gout270) == gout270clear);
    std::cerr << "\rLUT271   ";
    Ciphertext gin271 = 2 * gout269 + gout159;
    Ciphertext gout271 = ctx.eval_lut(&gin271, nand2);

    auto gin271clear = 2 * gout269clear + gout159clear;
    auto gout271clear = fnand2(gin271clear, 4);

    assert(ctx.decrypt(&gout271) == gout271clear);
    std::cerr << "\rINV272   ";
    Ciphertext gout272 = 1 - gout254;

    long gout272clear = 1 - gout254clear;

    assert(ctx.decrypt(&gout272) == gout272clear);
    std::cerr << "\rLUT273   ";
    Ciphertext gin273 = 2 * gout90 + gout222;
    Ciphertext gout273 = ctx.eval_lut(&gin273, xor2);

    auto gin273clear = 2 * gout90clear + gout222clear;
    auto gout273clear = fxor2(gin273clear, 4);

    assert(ctx.decrypt(&gout273) == gout273clear);
    std::cerr << "\rLUT274   ";
    Ciphertext gin274 = 2 * ct_y5 + ct_x6;
    Ciphertext gout274 = ctx.eval_lut(&gin274, and2);

    auto gin274clear = 2 * ct_y5clear + ct_x6clear;
    auto gout274clear = fand2(gin274clear, 4);

    assert(ctx.decrypt(&gout274) == gout274clear);
    std::cerr << "\rLUT275   ";
    Ciphertext gin275 = 2 * gout274 + gout175;
    Ciphertext gout275 = ctx.eval_lut(&gin275, xor2);

    auto gin275clear = 2 * gout274clear + gout175clear;
    auto gout275clear = fxor2(gin275clear, 4);

    assert(ctx.decrypt(&gout275) == gout275clear);
    std::cerr << "\rLUT276   ";
    Ciphertext gin276 = 2 * gout274 + gout175;
    Ciphertext gout276 = ctx.eval_lut(&gin276, nand2);

    auto gin276clear = 2 * gout274clear + gout175clear;
    auto gout276clear = fnand2(gin276clear, 4);

    assert(ctx.decrypt(&gout276) == gout276clear);
    std::cerr << "\rLUT277   ";
    Ciphertext gin277 = 2 * gout237 + gout276;
    Ciphertext gout277 = ctx.eval_lut(&gin277, nand2);

    auto gin277clear = 2 * gout237clear + gout276clear;
    auto gout277clear = fnand2(gin277clear, 4);

    assert(ctx.decrypt(&gout277) == gout277clear);
    std::cerr << "\rLUT278   ";
    Ciphertext gin278 = 2 * gout277 + gout241;
    Ciphertext gout278 = ctx.eval_lut(&gin278, xor2);

    auto gin278clear = 2 * gout277clear + gout241clear;
    auto gout278clear = fxor2(gin278clear, 4);

    assert(ctx.decrypt(&gout278) == gout278clear);
    std::cerr << "\rLUT279   ";
    Ciphertext gin279 = 2 * gout277 + gout241;
    Ciphertext gout279 = ctx.eval_lut(&gin279, nand2);

    auto gin279clear = 2 * gout277clear + gout241clear;
    auto gout279clear = fnand2(gin279clear, 4);

    assert(ctx.decrypt(&gout279) == gout279clear);
    std::cerr << "\rLUT280   ";
    Ciphertext gin280 = 2 * gout143 + gout236;
    Ciphertext gout280 = ctx.eval_lut(&gin280, nand2);

    auto gin280clear = 2 * gout143clear + gout236clear;
    auto gout280clear = fnand2(gin280clear, 4);

    assert(ctx.decrypt(&gout280) == gout280clear);
    std::cerr << "\rLUT281   ";
    Ciphertext gin281 = 2 * gout147 + gout206;
    Ciphertext gout281 = ctx.eval_lut(&gin281, xnor2);

    auto gin281clear = 2 * gout147clear + gout206clear;
    auto gout281clear = fxnor2(gin281clear, 4);

    assert(ctx.decrypt(&gout281) == gout281clear);
    std::cerr << "\rLUT282   ";
    Ciphertext gin282 = 2 * ct_y9 + ct_x6;
    Ciphertext gout282 = ctx.eval_lut(&gin282, and2);

    auto gin282clear = 2 * ct_y9clear + ct_x6clear;
    auto gout282clear = fand2(gin282clear, 4);

    assert(ctx.decrypt(&gout282) == gout282clear);
    std::cerr << "\rLUT283   ";
    Ciphertext gin283 = 2 * gout121 + gout282;
    Ciphertext gout283 = ctx.eval_lut(&gin283, xnor2);

    auto gin283clear = 2 * gout121clear + gout282clear;
    auto gout283clear = fxnor2(gin283clear, 4);

    assert(ctx.decrypt(&gout283) == gout283clear);
    std::cerr << "\rLUT284   ";
    Ciphertext gin284 = 2 * gout283 + gout129;
    Ciphertext gout284 = ctx.eval_lut(&gin284, xnor2);

    auto gin284clear = 2 * gout283clear + gout129clear;
    auto gout284clear = fxnor2(gin284clear, 4);

    assert(ctx.decrypt(&gout284) == gout284clear);
    std::cerr << "\rLUT285   ";
    Ciphertext gin285 = 2 * gout78 + gout284;
    Ciphertext gout285 = ctx.eval_lut(&gin285, xnor2);

    auto gin285clear = 2 * gout78clear + gout284clear;
    auto gout285clear = fxnor2(gin285clear, 4);

    assert(ctx.decrypt(&gout285) == gout285clear);
    std::cerr << "\rLUT286   ";
    Ciphertext gin286 = 2 * gout285 + gout268;
    Ciphertext gout286 = ctx.eval_lut(&gin286, xnor2);

    auto gin286clear = 2 * gout285clear + gout268clear;
    auto gout286clear = fxnor2(gin286clear, 4);

    assert(ctx.decrypt(&gout286) == gout286clear);
    std::cerr << "\rLUT287   ";
    Ciphertext gin287 = 2 * gout177 + gout262;
    Ciphertext gout287 = ctx.eval_lut(&gin287, xor2);

    auto gin287clear = 2 * gout177clear + gout262clear;
    auto gout287clear = fxor2(gin287clear, 4);

    assert(ctx.decrypt(&gout287) == gout287clear);
    std::cerr << "\rLUT288   ";
    Ciphertext gin288 = 2 * gout1 + gout12;
    Ciphertext gout288 = ctx.eval_lut(&gin288, xor2);

    auto gin288clear = 2 * gout1clear + gout12clear;
    auto gout288clear = fxor2(gin288clear, 4);

    assert(ctx.decrypt(&gout288) == gout288clear);
    std::cerr << "\rLUT289   ";
    Ciphertext gin289 = 2 * gout203 + gout288;
    Ciphertext gout289 = ctx.eval_lut(&gin289, xor2);

    auto gin289clear = 2 * gout203clear + gout288clear;
    auto gout289clear = fxor2(gin289clear, 4);

    assert(ctx.decrypt(&gout289) == gout289clear);
    std::cerr << "\rLUT290   ";
    Ciphertext gin290 = 2 * gout229 + gout289;
    Ciphertext gout290 = ctx.eval_lut(&gin290, xnor2);

    auto gin290clear = 2 * gout229clear + gout289clear;
    auto gout290clear = fxnor2(gin290clear, 4);

    assert(ctx.decrypt(&gout290) == gout290clear);
    std::cerr << "\rLUT291   ";
    Ciphertext gin291 = 2 * gout228 + gout289;
    Ciphertext gout291 = ctx.eval_lut(&gin291, and2);

    auto gin291clear = 2 * gout228clear + gout289clear;
    auto gout291clear = fand2(gin291clear, 4);

    assert(ctx.decrypt(&gout291) == gout291clear);
    std::cerr << "\rLUT292   ";
    Ciphertext gin292 = 2 * ct_y2 + ct_x9;
    Ciphertext gout292 = ctx.eval_lut(&gin292, and2);

    auto gin292clear = 2 * ct_y2clear + ct_x9clear;
    auto gout292clear = fand2(gin292clear, 4);

    assert(ctx.decrypt(&gout292) == gout292clear);
    std::cerr << "\rLUT293   ";
    Ciphertext gin293 = 2 * gout7 + gout292;
    Ciphertext gout293 = ctx.eval_lut(&gin293, xor2);

    auto gin293clear = 2 * gout7clear + gout292clear;
    auto gout293clear = fxor2(gin293clear, 4);

    assert(ctx.decrypt(&gout293) == gout293clear);
    std::cerr << "\rLUT294   ";
    Ciphertext gin294 = 2 * gout101 + gout293;
    Ciphertext gout294 = ctx.eval_lut(&gin294, xor2);

    auto gin294clear = 2 * gout101clear + gout293clear;
    auto gout294clear = fxor2(gin294clear, 4);

    assert(ctx.decrypt(&gout294) == gout294clear);
    std::cerr << "\rLUT295   ";
    Ciphertext gin295 = 2 * gout101 + gout293;
    Ciphertext gout295 = ctx.eval_lut(&gin295, nand2);

    auto gin295clear = 2 * gout101clear + gout293clear;
    auto gout295clear = fnand2(gin295clear, 4);

    assert(ctx.decrypt(&gout295) == gout295clear);
    std::cerr << "\rLUT296   ";
    Ciphertext gin296 = 2 * gout7 + gout292;
    Ciphertext gout296 = ctx.eval_lut(&gin296, nand2);

    auto gin296clear = 2 * gout7clear + gout292clear;
    auto gout296clear = fnand2(gin296clear, 4);

    assert(ctx.decrypt(&gout296) == gout296clear);
    std::cerr << "\rLUT297   ";
    Ciphertext gin297 = 2 * gout296 + gout295;
    Ciphertext gout297 = ctx.eval_lut(&gin297, nand2);

    auto gin297clear = 2 * gout296clear + gout295clear;
    auto gout297clear = fnand2(gin297clear, 4);

    assert(ctx.decrypt(&gout297) == gout297clear);
    std::cerr << "\rLUT298   ";
    Ciphertext gin298 = 2 * gout297 + gout163;
    Ciphertext gout298 = ctx.eval_lut(&gin298, xnor2);

    auto gin298clear = 2 * gout297clear + gout163clear;
    auto gout298clear = fxnor2(gin298clear, 4);

    assert(ctx.decrypt(&gout298) == gout298clear);
    std::cerr << "\rLUT299   ";
    Ciphertext gin299 = 2 * gout297 + gout163;
    Ciphertext gout299 = ctx.eval_lut(&gin299, and2);

    auto gin299clear = 2 * gout297clear + gout163clear;
    auto gout299clear = fand2(gin299clear, 4);

    assert(ctx.decrypt(&gout299) == gout299clear);
    std::cerr << "\rLUT300   ";
    Ciphertext gin300 = 2 * gout164 + gout224;
    Ciphertext gout300 = ctx.eval_lut(&gin300, nand2);

    auto gin300clear = 2 * gout164clear + gout224clear;
    auto gout300clear = fnand2(gin300clear, 4);

    assert(ctx.decrypt(&gout300) == gout300clear);
    std::cerr << "\rLUT301   ";
    Ciphertext gin301 = 2 * ct_y7 + ct_x4;
    Ciphertext gout301 = ctx.eval_lut(&gin301, and2);

    auto gin301clear = 2 * ct_y7clear + ct_x4clear;
    auto gout301clear = fand2(gin301clear, 4);

    assert(ctx.decrypt(&gout301) == gout301clear);
    std::cerr << "\rLUT302   ";
    Ciphertext gin302 = 2 * gout301 + gout82;
    Ciphertext gout302 = ctx.eval_lut(&gin302, xor2);

    auto gin302clear = 2 * gout301clear + gout82clear;
    auto gout302clear = fxor2(gin302clear, 4);

    assert(ctx.decrypt(&gout302) == gout302clear);
    std::cerr << "\rLUT303   ";
    Ciphertext gin303 = 2 * gout301 + gout82;
    Ciphertext gout303 = ctx.eval_lut(&gin303, nand2);

    auto gin303clear = 2 * gout301clear + gout82clear;
    auto gout303clear = fnand2(gin303clear, 4);

    assert(ctx.decrypt(&gout303) == gout303clear);
    std::cerr << "\rLUT304   ";
    Ciphertext gin304 = 2 * ct_y8 + ct_x2;
    Ciphertext gout304 = ctx.eval_lut(&gin304, and2);

    auto gin304clear = 2 * ct_y8clear + ct_x2clear;
    auto gout304clear = fand2(gin304clear, 4);

    assert(ctx.decrypt(&gout304) == gout304clear);
    std::cerr << "\rLUT305   ";
    Ciphertext gin305 = 2 * gout304 + gout49;
    Ciphertext gout305 = ctx.eval_lut(&gin305, xor2);

    auto gin305clear = 2 * gout304clear + gout49clear;
    auto gout305clear = fxor2(gin305clear, 4);

    assert(ctx.decrypt(&gout305) == gout305clear);
    std::cerr << "\rLUT306   ";
    Ciphertext gin306 = 2 * gout304 + gout49;
    Ciphertext gout306 = ctx.eval_lut(&gin306, nand2);

    auto gin306clear = 2 * gout304clear + gout49clear;
    auto gout306clear = fnand2(gin306clear, 4);

    assert(ctx.decrypt(&gout306) == gout306clear);
    std::cerr << "\rLUT307   ";
    Ciphertext gin307 = 2 * gout50 + gout306;
    Ciphertext gout307 = ctx.eval_lut(&gin307, nand2);

    auto gin307clear = 2 * gout50clear + gout306clear;
    auto gout307clear = fnand2(gin307clear, 4);

    assert(ctx.decrypt(&gout307) == gout307clear);
    std::cerr << "\rLUT308   ";
    Ciphertext gin308 = 2 * ct_y0 + ct_x4;
    Ciphertext gout308 = ctx.eval_lut(&gin308, nand2);

    auto gin308clear = 2 * ct_y0clear + ct_x4clear;
    auto gout308clear = fnand2(gin308clear, 4);

    assert(ctx.decrypt(&gout308) == gout308clear);
    std::cerr << "\rLUT309   ";
    Ciphertext gin309 = 2 * gout308 + gout44;
    Ciphertext gout309 = ctx.eval_lut(&gin309, xnor2);

    auto gin309clear = 2 * gout308clear + gout44clear;
    auto gout309clear = fxnor2(gin309clear, 4);

    assert(ctx.decrypt(&gout309) == gout309clear);
    std::cerr << "\rINV310   ";
    Ciphertext gout310 = 1 - ct_x9;

    long gout310clear = 1 - ct_x9clear;

    assert(ctx.decrypt(&gout310) == gout310clear);
    std::cerr << "\rLUT311   ";
    Ciphertext gin311 = 2 * gout41 + gout217;
    Ciphertext gout311 = ctx.eval_lut(&gin311, xnor2);

    auto gin311clear = 2 * gout41clear + gout217clear;
    auto gout311clear = fxnor2(gin311clear, 4);

    assert(ctx.decrypt(&gout311) == gout311clear);
    std::cerr << "\rLUT312   ";
    Ciphertext gin312 = 2 * ct_y2 + ct_x12;
    Ciphertext gout312 = ctx.eval_lut(&gin312, and2);

    auto gin312clear = 2 * ct_y2clear + ct_x12clear;
    auto gout312clear = fand2(gin312clear, 4);

    assert(ctx.decrypt(&gout312) == gout312clear);
    std::cerr << "\rLUT313   ";
    Ciphertext gin313 = 2 * gout233 + gout312;
    Ciphertext gout313 = ctx.eval_lut(&gin313, xnor2);

    auto gin313clear = 2 * gout233clear + gout312clear;
    auto gout313clear = fxnor2(gin313clear, 4);

    assert(ctx.decrypt(&gout313) == gout313clear);
    std::cerr << "\rLUT314   ";
    Ciphertext gin314 = 2 * gout19 + gout313;
    Ciphertext gout314 = ctx.eval_lut(&gin314, xor2);

    auto gin314clear = 2 * gout19clear + gout313clear;
    auto gout314clear = fxor2(gin314clear, 4);

    assert(ctx.decrypt(&gout314) == gout314clear);
    std::cerr << "\rLUT315   ";
    Ciphertext gin315 = 2 * gout19 + gout313;
    Ciphertext gout315 = ctx.eval_lut(&gin315, nand2);

    auto gin315clear = 2 * gout19clear + gout313clear;
    auto gout315clear = fnand2(gin315clear, 4);

    assert(ctx.decrypt(&gout315) == gout315clear);
    std::cerr << "\rLUT316   ";
    Ciphertext gin316 = 2 * gout54 + gout315;
    Ciphertext gout316 = ctx.eval_lut(&gin316, and2);

    auto gin316clear = 2 * gout54clear + gout315clear;
    auto gout316clear = fand2(gin316clear, 4);

    assert(ctx.decrypt(&gout316) == gout316clear);
    std::cerr << "\rLUT317   ";
    Ciphertext gin317 = 2 * gout81 + gout316;
    Ciphertext gout317 = ctx.eval_lut(&gin317, xnor2);

    auto gin317clear = 2 * gout81clear + gout316clear;
    auto gout317clear = fxnor2(gin317clear, 4);

    assert(ctx.decrypt(&gout317) == gout317clear);
    std::cerr << "\rLUT318   ";
    Ciphertext gin318 = 2 * ct_y6 + ct_x9;
    Ciphertext gout318 = ctx.eval_lut(&gin318, and2);

    auto gin318clear = 2 * ct_y6clear + ct_x9clear;
    auto gout318clear = fand2(gin318clear, 4);

    assert(ctx.decrypt(&gout318) == gout318clear);
    std::cerr << "\rLUT319   ";
    Ciphertext gin319 = 2 * gout18 + gout318;
    Ciphertext gout319 = ctx.eval_lut(&gin319, xnor2);

    auto gin319clear = 2 * gout18clear + gout318clear;
    auto gout319clear = fxnor2(gin319clear, 4);

    assert(ctx.decrypt(&gout319) == gout319clear);
    std::cerr << "\rLUT320   ";
    Ciphertext gin320 = 2 * gout168 + gout319;
    Ciphertext gout320 = ctx.eval_lut(&gin320, xnor2);

    auto gin320clear = 2 * gout168clear + gout319clear;
    auto gout320clear = fxnor2(gin320clear, 4);

    assert(ctx.decrypt(&gout320) == gout320clear);
    std::cerr << "\rLUT321   ";
    Ciphertext gin321 = 2 * gout261 + gout320;
    Ciphertext gout321 = ctx.eval_lut(&gin321, xnor2);

    auto gin321clear = 2 * gout261clear + gout320clear;
    auto gout321clear = fxnor2(gin321clear, 4);

    assert(ctx.decrypt(&gout321) == gout321clear);
    std::cerr << "\rLUT322   ";
    Ciphertext gin322 = 2 * gout317 + gout321;
    Ciphertext gout322 = ctx.eval_lut(&gin322, xnor2);

    auto gin322clear = 2 * gout317clear + gout321clear;
    auto gout322clear = fxnor2(gin322clear, 4);

    assert(ctx.decrypt(&gout322) == gout322clear);
    std::cerr << "\rLUT323   ";
    Ciphertext gin323 = 2 * gout152 + gout322;
    Ciphertext gout323 = ctx.eval_lut(&gin323, xnor2);

    auto gin323clear = 2 * gout152clear + gout322clear;
    auto gout323clear = fxnor2(gin323clear, 4);

    assert(ctx.decrypt(&gout323) == gout323clear);
    std::cerr << "\rLUT324   ";
    Ciphertext gin324 = 2 * gout64 + gout271;
    Ciphertext gout324 = ctx.eval_lut(&gin324, nand2);

    auto gin324clear = 2 * gout64clear + gout271clear;
    auto gout324clear = fnand2(gin324clear, 4);

    assert(ctx.decrypt(&gout324) == gout324clear);
    std::cerr << "\rINV325   ";
    Ciphertext gout325 = 1 - ct_x1;

    long gout325clear = 1 - ct_x1clear;

    assert(ctx.decrypt(&gout325) == gout325clear);
    std::cerr << "\rLUT326   ";
    Ciphertext gin326 = 2 * gout325 + gout311;
    Ciphertext gout326 = ctx.eval_lut(&gin326, xnor2);

    auto gin326clear = 2 * gout325clear + gout311clear;
    auto gout326clear = fxnor2(gin326clear, 4);

    assert(ctx.decrypt(&gout326) == gout326clear);
    std::cerr << "\rLUT327   ";
    Ciphertext gin327 = 2 * gout272 + gout326;
    Ciphertext gout327 = ctx.eval_lut(&gin327, xnor2);

    auto gin327clear = 2 * gout272clear + gout326clear;
    auto gout327clear = fxnor2(gin327clear, 4);

    assert(ctx.decrypt(&gout327) == gout327clear);
    std::cerr << "\rLUT328   ";
    Ciphertext gin328 = 2 * gout115 + gout327;
    Ciphertext gout328 = ctx.eval_lut(&gin328, nand2);

    auto gin328clear = 2 * gout115clear + gout327clear;
    auto gout328clear = fnand2(gin328clear, 4);

    assert(ctx.decrypt(&gout328) == gout328clear);
    std::cerr << "\rLUT329   ";
    Ciphertext gin329 = 2 * gout328 + gout219;
    Ciphertext gout329 = ctx.eval_lut(&gin329, nand2);

    auto gin329clear = 2 * gout328clear + gout219clear;
    auto gout329clear = fnand2(gin329clear, 4);

    assert(ctx.decrypt(&gout329) == gout329clear);
    std::cerr << "\rLUT330   ";
    Ciphertext gin330 = 2 * gout254 + gout326;
    Ciphertext gout330 = ctx.eval_lut(&gin330, nand2);

    auto gin330clear = 2 * gout254clear + gout326clear;
    auto gout330clear = fnand2(gin330clear, 4);

    assert(ctx.decrypt(&gout330) == gout330clear);
    std::cerr << "\rLUT331   ";
    Ciphertext gin331 = 2 * ct_y8 + ct_x3;
    Ciphertext gout331 = ctx.eval_lut(&gin331, and2);

    auto gin331clear = 2 * ct_y8clear + ct_x3clear;
    auto gout331clear = fand2(gin331clear, 4);

    assert(ctx.decrypt(&gout331) == gout331clear);
    std::cerr << "\rLUT332   ";
    Ciphertext gin332 = 2 * gout331 + gout302;
    Ciphertext gout332 = ctx.eval_lut(&gin332, xor2);

    auto gin332clear = 2 * gout331clear + gout302clear;
    auto gout332clear = fxor2(gin332clear, 4);

    assert(ctx.decrypt(&gout332) == gout332clear);
    std::cerr << "\rLUT333   ";
    Ciphertext gin333 = 2 * gout324 + gout332;
    Ciphertext gout333 = ctx.eval_lut(&gin333, xor2);

    auto gin333clear = 2 * gout324clear + gout332clear;
    auto gout333clear = fxor2(gin333clear, 4);

    assert(ctx.decrypt(&gout333) == gout333clear);
    std::cerr << "\rLUT334   ";
    Ciphertext gin334 = 2 * gout324 + gout332;
    Ciphertext gout334 = ctx.eval_lut(&gin334, nand2);

    auto gin334clear = 2 * gout324clear + gout332clear;
    auto gout334clear = fnand2(gin334clear, 4);

    assert(ctx.decrypt(&gout334) == gout334clear);
    std::cerr << "\rLUT335   ";
    Ciphertext gin335 = 2 * gout331 + gout302;
    Ciphertext gout335 = ctx.eval_lut(&gin335, nand2);

    auto gin335clear = 2 * gout331clear + gout302clear;
    auto gout335clear = fnand2(gin335clear, 4);

    assert(ctx.decrypt(&gout335) == gout335clear);
    std::cerr << "\rLUT336   ";
    Ciphertext gin336 = 2 * gout303 + gout335;
    Ciphertext gout336 = ctx.eval_lut(&gin336, nand2);

    auto gin336clear = 2 * gout303clear + gout335clear;
    auto gout336clear = fnand2(gin336clear, 4);

    assert(ctx.decrypt(&gout336) == gout336clear);
    std::cerr << "\rLUT337   ";
    Ciphertext gin337 = 2 * gout336 + gout278;
    Ciphertext gout337 = ctx.eval_lut(&gin337, nand2);

    auto gin337clear = 2 * gout336clear + gout278clear;
    auto gout337clear = fnand2(gin337clear, 4);

    assert(ctx.decrypt(&gout337) == gout337clear);
    std::cerr << "\rLUT338   ";
    Ciphertext gin338 = 2 * gout279 + gout337;
    Ciphertext gout338 = ctx.eval_lut(&gin338, nand2);

    auto gin338clear = 2 * gout279clear + gout337clear;
    auto gout338clear = fnand2(gin338clear, 4);

    assert(ctx.decrypt(&gout338) == gout338clear);
    std::cerr << "\rLUT339   ";
    Ciphertext gin339 = 2 * gout158 + gout258;
    Ciphertext gout339 = ctx.eval_lut(&gin339, xor2);

    auto gin339clear = 2 * gout158clear + gout258clear;
    auto gout339clear = fxor2(gin339clear, 4);

    assert(ctx.decrypt(&gout339) == gout339clear);
    std::cerr << "\rLUT340   ";
    Ciphertext gin340 = 2 * gout103 + gout339;
    Ciphertext gout340 = ctx.eval_lut(&gin340, xor2);

    auto gin340clear = 2 * gout103clear + gout339clear;
    auto gout340clear = fxor2(gin340clear, 4);

    assert(ctx.decrypt(&gout340) == gout340clear);
    std::cerr << "\rLUT341   ";
    Ciphertext gin341 = 2 * gout187 + gout340;
    Ciphertext gout341 = ctx.eval_lut(&gin341, xor2);

    auto gin341clear = 2 * gout187clear + gout340clear;
    auto gout341clear = fxor2(gin341clear, 4);

    assert(ctx.decrypt(&gout341) == gout341clear);
    std::cerr << "\rLUT342   ";
    Ciphertext gin342 = 2 * gout187 + gout340;
    Ciphertext gout342 = ctx.eval_lut(&gin342, nand2);

    auto gin342clear = 2 * gout187clear + gout340clear;
    auto gout342clear = fnand2(gin342clear, 4);

    assert(ctx.decrypt(&gout342) == gout342clear);
    std::cerr << "\rLUT343   ";
    Ciphertext gin343 = 2 * gout103 + gout339;
    Ciphertext gout343 = ctx.eval_lut(&gin343, nand2);

    auto gin343clear = 2 * gout103clear + gout339clear;
    auto gout343clear = fnand2(gin343clear, 4);

    assert(ctx.decrypt(&gout343) == gout343clear);
    std::cerr << "\rLUT344   ";
    Ciphertext gin344 = 2 * gout259 + gout343;
    Ciphertext gout344 = ctx.eval_lut(&gin344, nand2);

    auto gin344clear = 2 * gout259clear + gout343clear;
    auto gout344clear = fnand2(gin344clear, 4);

    assert(ctx.decrypt(&gout344) == gout344clear);
    std::cerr << "\rINV345   ";
    Ciphertext gout345 = 1 - ct_y2;

    long gout345clear = 1 - ct_y2clear;

    assert(ctx.decrypt(&gout345) == gout345clear);
    std::cerr << "\rLUT346   ";
    Ciphertext gin346 = 2 * gout345 + gout6;
    Ciphertext gout346 = ctx.eval_lut(&gin346, and2);

    auto gin346clear = 2 * gout345clear + gout6clear;
    auto gout346clear = fand2(gin346clear, 4);

    assert(ctx.decrypt(&gout346) == gout346clear);
    std::cerr << "\rLUT347   ";
    Ciphertext gin347 = 2 * gout105 + gout346;
    Ciphertext gout347 = ctx.eval_lut(&gin347, and2);

    auto gin347clear = 2 * gout105clear + gout346clear;
    auto gout347clear = fand2(gin347clear, 4);

    assert(ctx.decrypt(&gout347) == gout347clear);
    std::cerr << "\rLUT348   ";
    Ciphertext gin348 = 2 * (1 - gout346) + gout211;
    Ciphertext gout348 = ctx.eval_lut(&gin348, and2);

    auto gin348clear = 2 * (1 - gout346clear) + gout211clear;
    auto gout348clear = fand2(gin348clear, 4);

    assert(ctx.decrypt(&gout348) == gout348clear);
    std::cerr << "\rLUT349   ";
    Ciphertext gin349 = 2 * gout105 + gout348;
    Ciphertext gout349 = ctx.eval_lut(&gin349, xnor2);

    auto gin349clear = 2 * gout105clear + gout348clear;
    auto gout349clear = fxnor2(gin349clear, 4);

    assert(ctx.decrypt(&gout349) == gout349clear);
    std::cerr << "\rLUT350   ";
    Ciphertext gin350 = 2 * gout79 + gout349;
    Ciphertext gout350 = ctx.eval_lut(&gin350, xnor2);

    auto gin350clear = 2 * gout79clear + gout349clear;
    auto gout350clear = fxnor2(gin350clear, 4);

    assert(ctx.decrypt(&gout350) == gout350clear);
    std::cerr << "\rLUT351   ";
    Ciphertext gin351 = 2 * ct_x3 + gout349;
    Ciphertext gout351 = ctx.eval_lut(&gin351, nand2);

    auto gin351clear = 2 * ct_x3clear + gout349clear;
    auto gout351clear = fnand2(gin351clear, 4);

    assert(ctx.decrypt(&gout351) == gout351clear);
    std::cerr << "\rLUT352   ";
    Ciphertext gin352 = 2 * gout345 + gout216;
    Ciphertext gout352 = ctx.eval_lut(&gin352, xnor2);

    auto gin352clear = 2 * gout345clear + gout216clear;
    auto gout352clear = fxnor2(gin352clear, 4);

    assert(ctx.decrypt(&gout352) == gout352clear);
    std::cerr << "\rLUT353   ";
    Ciphertext gin353 = 2 * gout99 + gout352;
    Ciphertext gout353 = ctx.eval_lut(&gin353, xnor2);

    auto gin353clear = 2 * gout99clear + gout352clear;
    auto gout353clear = fxnor2(gin353clear, 4);

    assert(ctx.decrypt(&gout353) == gout353clear);
    std::cerr << "\rLUT354   ";
    Ciphertext gin354 = 2 * ct_x2 + gout352;
    Ciphertext gout354 = ctx.eval_lut(&gin354, nand2);

    auto gin354clear = 2 * ct_x2clear + gout352clear;
    auto gout354clear = fnand2(gin354clear, 4);

    assert(ctx.decrypt(&gout354) == gout354clear);
    std::cerr << "\rLUT355   ";
    Ciphertext gin355 = 2 * ct_y6 + ct_x7;
    Ciphertext gout355 = ctx.eval_lut(&gin355, and2);

    auto gin355clear = 2 * ct_y6clear + ct_x7clear;
    auto gout355clear = fand2(gin355clear, 4);

    assert(ctx.decrypt(&gout355) == gout355clear);
    std::cerr << "\rLUT356   ";
    Ciphertext gin356 = 2 * gout355 + gout168;
    Ciphertext gout356 = ctx.eval_lut(&gin356, nand2);

    auto gin356clear = 2 * gout355clear + gout168clear;
    auto gout356clear = fnand2(gin356clear, 4);

    assert(ctx.decrypt(&gout356) == gout356clear);
    std::cerr << "\rLUT357   ";
    Ciphertext gin357 = 2 * gout356 + gout251;
    Ciphertext gout357 = ctx.eval_lut(&gin357, and2);

    auto gin357clear = 2 * gout356clear + gout251clear;
    auto gout357clear = fand2(gin357clear, 4);

    assert(ctx.decrypt(&gout357) == gout357clear);
    std::cerr << "\rLUT358   ";
    Ciphertext gin358 = 2 * gout139 + gout355;
    Ciphertext gout358 = ctx.eval_lut(&gin358, xor2);

    auto gin358clear = 2 * gout139clear + gout355clear;
    auto gout358clear = fxor2(gin358clear, 4);

    assert(ctx.decrypt(&gout358) == gout358clear);
    std::cerr << "\rLUT359   ";
    Ciphertext gin359 = 2 * gout29 + gout358;
    Ciphertext gout359 = ctx.eval_lut(&gin359, xor2);

    auto gin359clear = 2 * gout29clear + gout358clear;
    auto gout359clear = fxor2(gin359clear, 4);

    assert(ctx.decrypt(&gout359) == gout359clear);
    std::cerr << "\rLUT360   ";
    Ciphertext gin360 = 2 * gout29 + gout358;
    Ciphertext gout360 = ctx.eval_lut(&gin360, nand2);

    auto gin360clear = 2 * gout29clear + gout358clear;
    auto gout360clear = fnand2(gin360clear, 4);

    assert(ctx.decrypt(&gout360) == gout360clear);
    std::cerr << "\rLUT361   ";
    Ciphertext gin361 = 2 * gout139 + gout355;
    Ciphertext gout361 = ctx.eval_lut(&gin361, nand2);

    auto gin361clear = 2 * gout139clear + gout355clear;
    auto gout361clear = fnand2(gin361clear, 4);

    assert(ctx.decrypt(&gout361) == gout361clear);
    std::cerr << "\rLUT362   ";
    Ciphertext gin362 = 2 * gout361 + gout360;
    Ciphertext gout362 = ctx.eval_lut(&gin362, nand2);

    auto gin362clear = 2 * gout361clear + gout360clear;
    auto gout362clear = fnand2(gin362clear, 4);

    assert(ctx.decrypt(&gout362) == gout362clear);
    std::cerr << "\rLUT363   ";
    Ciphertext gin363 = 2 * ct_y1 + ct_x12;
    Ciphertext gout363 = ctx.eval_lut(&gin363, and2);

    auto gin363clear = 2 * ct_y1clear + ct_x12clear;
    auto gout363clear = fand2(gin363clear, 4);

    assert(ctx.decrypt(&gout363) == gout363clear);
    std::cerr << "\rLUT364   ";
    Ciphertext gin364 = 2 * gout363 + gout176;
    Ciphertext gout364 = ctx.eval_lut(&gin364, xor2);

    auto gin364clear = 2 * gout363clear + gout176clear;
    auto gout364clear = fxor2(gin364clear, 4);

    assert(ctx.decrypt(&gout364) == gout364clear);
    std::cerr << "\rLUT365   ";
    Ciphertext gin365 = 2 * gout300 + gout364;
    Ciphertext gout365 = ctx.eval_lut(&gin365, xnor2);

    auto gin365clear = 2 * gout300clear + gout364clear;
    auto gout365clear = fxnor2(gin365clear, 4);

    assert(ctx.decrypt(&gout365) == gout365clear);
    std::cerr << "\rLUT366   ";
    Ciphertext gin366 = 2 * gout300 + gout364;
    Ciphertext gout366 = ctx.eval_lut(&gin366, and2);

    auto gin366clear = 2 * gout300clear + gout364clear;
    auto gout366clear = fand2(gin366clear, 4);

    assert(ctx.decrypt(&gout366) == gout366clear);
    std::cerr << "\rLUT367   ";
    Ciphertext gin367 = 2 * gout363 + gout176;
    Ciphertext gout367 = ctx.eval_lut(&gin367, nand2);

    auto gin367clear = 2 * gout363clear + gout176clear;
    auto gout367clear = fnand2(gin367clear, 4);

    assert(ctx.decrypt(&gout367) == gout367clear);
    std::cerr << "\rLUT368   ";
    Ciphertext gin368 = 2 * gout174 + gout367;
    Ciphertext gout368 = ctx.eval_lut(&gin368, nand2);

    auto gin368clear = 2 * gout174clear + gout367clear;
    auto gout368clear = fnand2(gin368clear, 4);

    assert(ctx.decrypt(&gout368) == gout368clear);
    std::cerr << "\rLUT369   ";
    Ciphertext gin369 = 2 * gout368 + gout314;
    Ciphertext gout369 = ctx.eval_lut(&gin369, xnor2);

    auto gin369clear = 2 * gout368clear + gout314clear;
    auto gout369clear = fxnor2(gin369clear, 4);

    assert(ctx.decrypt(&gout369) == gout369clear);
    std::cerr << "\rLUT370   ";
    Ciphertext gin370 = 2 * gout369 + gout264;
    Ciphertext gout370 = ctx.eval_lut(&gin370, xnor2);

    auto gin370clear = 2 * gout369clear + gout264clear;
    auto gout370clear = fxnor2(gin370clear, 4);

    assert(ctx.decrypt(&gout370) == gout370clear);
    std::cerr << "\rLUT371   ";
    Ciphertext gin371 = 2 * (1 - gout369) + gout264;
    Ciphertext gout371 = ctx.eval_lut(&gin371, and2);

    auto gin371clear = 2 * (1 - gout369clear) + gout264clear;
    auto gout371clear = fand2(gin371clear, 4);

    assert(ctx.decrypt(&gout371) == gout371clear);
    std::cerr << "\rLUT372   ";
    Ciphertext gin372 = 2 * gout368 + gout314;
    Ciphertext gout372 = ctx.eval_lut(&gin372, nand2);

    auto gin372clear = 2 * gout368clear + gout314clear;
    auto gout372clear = fnand2(gin372clear, 4);

    assert(ctx.decrypt(&gout372) == gout372clear);
    std::cerr << "\rLUT373   ";
    Ciphertext gin373 = 2 * gout372 + (1 - gout371);
    Ciphertext gout373 = ctx.eval_lut(&gin373, and2);

    auto gin373clear = 2 * gout372clear + (1 - gout371clear);
    auto gout373clear = fand2(gin373clear, 4);

    assert(ctx.decrypt(&gout373) == gout373clear);
    std::cerr << "\rLUT374   ";
    Ciphertext gin374 = 2 * gout373 + gout357;
    Ciphertext gout374 = ctx.eval_lut(&gin374, xnor2);

    auto gin374clear = 2 * gout373clear + gout357clear;
    auto gout374clear = fxnor2(gin374clear, 4);

    assert(ctx.decrypt(&gout374) == gout374clear);
    std::cerr << "\rLUT375   ";
    Ciphertext gin375 = 2 * gout374 + gout323;
    Ciphertext gout375 = ctx.eval_lut(&gin375, xnor2);

    auto gin375clear = 2 * gout374clear + gout323clear;
    auto gout375clear = fxnor2(gin375clear, 4);

    assert(ctx.decrypt(&gout375) == gout375clear);
    std::cerr << "\rLUT376   ";
    Ciphertext gin376 = 2 * ct_y2 + ct_x7;
    Ciphertext gout376 = ctx.eval_lut(&gin376, and2);

    auto gin376clear = 2 * ct_y2clear + ct_x7clear;
    auto gout376clear = fand2(gin376clear, 4);

    assert(ctx.decrypt(&gout376) == gout376clear);
    std::cerr << "\rLUT377   ";
    Ciphertext gin377 = 2 * gout146 + gout134;
    Ciphertext gout377 = ctx.eval_lut(&gin377, nand2);

    auto gin377clear = 2 * gout146clear + gout134clear;
    auto gout377clear = fnand2(gin377clear, 4);

    assert(ctx.decrypt(&gout377) == gout377clear);
    std::cerr << "\rLUT378   ";
    Ciphertext gin378 = 2 * ct_x1 + gout311;
    Ciphertext gout378 = ctx.eval_lut(&gin378, nand2);

    auto gin378clear = 2 * ct_x1clear + gout311clear;
    auto gout378clear = fnand2(gin378clear, 4);

    assert(ctx.decrypt(&gout378) == gout378clear);
    std::cerr << "\rLUT379   ";
    Ciphertext gin379 = 2 * gout378 + gout330;
    Ciphertext gout379 = ctx.eval_lut(&gin379, nand2);

    auto gin379clear = 2 * gout378clear + gout330clear;
    auto gout379clear = fnand2(gin379clear, 4);

    assert(ctx.decrypt(&gout379) == gout379clear);
    std::cerr << "\rLUT380   ";
    Ciphertext gin380 = 2 * gout379 + gout353;
    Ciphertext gout380 = ctx.eval_lut(&gin380, xnor2);

    auto gin380clear = 2 * gout379clear + gout353clear;
    auto gout380clear = fxnor2(gin380clear, 4);

    assert(ctx.decrypt(&gout380) == gout380clear);
    std::cerr << "\rLUT381   ";
    Ciphertext gin381 = 2 * gout379 + gout353;
    Ciphertext gout381 = ctx.eval_lut(&gin381, nand2);

    auto gin381clear = 2 * gout379clear + gout353clear;
    auto gout381clear = fnand2(gin381clear, 4);

    assert(ctx.decrypt(&gout381) == gout381clear);
    std::cerr << "\rLUT382   ";
    Ciphertext gin382 = 2 * gout354 + gout381;
    Ciphertext gout382 = ctx.eval_lut(&gin382, nand2);

    auto gin382clear = 2 * gout354clear + gout381clear;
    auto gout382clear = fnand2(gin382clear, 4);

    assert(ctx.decrypt(&gout382) == gout382clear);
    std::cerr << "\rLUT383   ";
    Ciphertext gin383 = 2 * gout382 + gout350;
    Ciphertext gout383 = ctx.eval_lut(&gin383, xnor2);

    auto gin383clear = 2 * gout382clear + gout350clear;
    auto gout383clear = fxnor2(gin383clear, 4);

    assert(ctx.decrypt(&gout383) == gout383clear);
    std::cerr << "\rLUT384   ";
    Ciphertext gin384 = 2 * gout382 + gout350;
    Ciphertext gout384 = ctx.eval_lut(&gin384, nand2);

    auto gin384clear = 2 * gout382clear + gout350clear;
    auto gout384clear = fnand2(gin384clear, 4);

    assert(ctx.decrypt(&gout384) == gout384clear);
    std::cerr << "\rLUT385   ";
    Ciphertext gin385 = 2 * gout351 + gout384;
    Ciphertext gout385 = ctx.eval_lut(&gin385, nand2);

    auto gin385clear = 2 * gout351clear + gout384clear;
    auto gout385clear = fnand2(gin385clear, 4);

    assert(ctx.decrypt(&gout385) == gout385clear);
    std::cerr << "\rLUT386   ";
    Ciphertext gin386 = 2 * gout194 + gout127;
    Ciphertext gout386 = ctx.eval_lut(&gin386, and2);

    auto gin386clear = 2 * gout194clear + gout127clear;
    auto gout386clear = fand2(gin386clear, 4);

    assert(ctx.decrypt(&gout386) == gout386clear);
    std::cerr << "\rLUT387   ";
    Ciphertext gin387 = 2 * gout336 + gout278;
    Ciphertext gout387 = ctx.eval_lut(&gin387, xor2);

    auto gin387clear = 2 * gout336clear + gout278clear;
    auto gout387clear = fxor2(gin387clear, 4);

    assert(ctx.decrypt(&gout387) == gout387clear);
    std::cerr << "\rLUT388   ";
    Ciphertext gin388 = 2 * gout244 + gout158;
    Ciphertext gout388 = ctx.eval_lut(&gin388, and2);

    auto gin388clear = 2 * gout244clear + gout158clear;
    auto gout388clear = fand2(gin388clear, 4);

    assert(ctx.decrypt(&gout388) == gout388clear);
    std::cerr << "\rLUT389   ";
    Ciphertext gin389 = 2 * gout388 + gout341;
    Ciphertext gout389 = ctx.eval_lut(&gin389, xor2);

    auto gin389clear = 2 * gout388clear + gout341clear;
    auto gout389clear = fxor2(gin389clear, 4);

    assert(ctx.decrypt(&gout389) == gout389clear);
    std::cerr << "\rLUT390   ";
    Ciphertext gin390 = 2 * gout388 + gout341;
    Ciphertext gout390 = ctx.eval_lut(&gin390, nand2);

    auto gin390clear = 2 * gout388clear + gout341clear;
    auto gout390clear = fnand2(gin390clear, 4);

    assert(ctx.decrypt(&gout390) == gout390clear);
    std::cerr << "\rLUT391   ";
    Ciphertext gin391 = 2 * gout342 + gout390;
    Ciphertext gout391 = ctx.eval_lut(&gin391, nand2);

    auto gin391clear = 2 * gout342clear + gout390clear;
    auto gout391clear = fnand2(gin391clear, 4);

    assert(ctx.decrypt(&gout391) == gout391clear);
    std::cerr << "\rLUT392   ";
    Ciphertext gin392 = 2 * gout391 + gout227;
    Ciphertext gout392 = ctx.eval_lut(&gin392, xor2);

    auto gin392clear = 2 * gout391clear + gout227clear;
    auto gout392clear = fxor2(gin392clear, 4);

    assert(ctx.decrypt(&gout392) == gout392clear);
    std::cerr << "\rLUT393   ";
    Ciphertext gin393 = 2 * gout391 + gout227;
    Ciphertext gout393 = ctx.eval_lut(&gin393, and2);

    auto gin393clear = 2 * gout391clear + gout227clear;
    auto gout393clear = fand2(gin393clear, 4);

    assert(ctx.decrypt(&gout393) == gout393clear);
    std::cerr << "\rLUT394   ";
    Ciphertext gin394 = 2 * gout34 + gout231;
    Ciphertext gout394 = ctx.eval_lut(&gin394, nand2);

    auto gin394clear = 2 * gout34clear + gout231clear;
    auto gout394clear = fnand2(gin394clear, 4);

    assert(ctx.decrypt(&gout394) == gout394clear);
    std::cerr << "\rLUT395   ";
    Ciphertext gin395 = 2 * gout232 + gout394;
    Ciphertext gout395 = ctx.eval_lut(&gin395, nand2);

    auto gin395clear = 2 * gout232clear + gout394clear;
    auto gout395clear = fnand2(gin395clear, 4);

    assert(ctx.decrypt(&gout395) == gout395clear);
    std::cerr << "\rLUT396   ";
    Ciphertext gin396 = 2 * gout395 + gout69;
    Ciphertext gout396 = ctx.eval_lut(&gin396, xnor2);

    auto gin396clear = 2 * gout395clear + gout69clear;
    auto gout396clear = fxnor2(gin396clear, 4);

    assert(ctx.decrypt(&gout396) == gout396clear);
    std::cerr << "\rLUT397   ";
    Ciphertext gin397 = 2 * gout396 + gout132;
    Ciphertext gout397 = ctx.eval_lut(&gin397, xnor2);

    auto gin397clear = 2 * gout396clear + gout132clear;
    auto gout397clear = fxnor2(gin397clear, 4);

    assert(ctx.decrypt(&gout397) == gout397clear);
    std::cerr << "\rLUT398   ";
    Ciphertext gin398 = 2 * (1 - gout396) + gout132;
    Ciphertext gout398 = ctx.eval_lut(&gin398, and2);

    auto gin398clear = 2 * (1 - gout396clear) + gout132clear;
    auto gout398clear = fand2(gin398clear, 4);

    assert(ctx.decrypt(&gout398) == gout398clear);
    std::cerr << "\rLUT399   ";
    Ciphertext gin399 = 2 * gout395 + gout69;
    Ciphertext gout399 = ctx.eval_lut(&gin399, and2);

    auto gin399clear = 2 * gout395clear + gout69clear;
    auto gout399clear = fand2(gin399clear, 4);

    assert(ctx.decrypt(&gout399) == gout399clear);
    std::cerr << "\rLUT400   ";
    Ciphertext gin400 = 2 * gout399 + gout398;
    Ciphertext gout400 = ctx.eval_lut(&gin400, or2);

    auto gin400clear = 2 * gout399clear + gout398clear;
    auto gout400clear = for2(gin400clear, 4);

    assert(ctx.decrypt(&gout400) == gout400clear);
    std::cerr << "\rLUT401   ";
    Ciphertext gin401 = 2 * ct_y0 + ct_x13;
    Ciphertext gout401 = ctx.eval_lut(&gin401, and2);

    auto gin401clear = 2 * ct_y0clear + ct_x13clear;
    auto gout401clear = fand2(gin401clear, 4);

    assert(ctx.decrypt(&gout401) == gout401clear);
    std::cerr << "\rLUT402   ";
    Ciphertext gin402 = 2 * gout202 + gout401;
    Ciphertext gout402 = ctx.eval_lut(&gin402, xor2);

    auto gin402clear = 2 * gout202clear + gout401clear;
    auto gout402clear = fxor2(gin402clear, 4);

    assert(ctx.decrypt(&gout402) == gout402clear);
    std::cerr << "\rLUT403   ";
    Ciphertext gin403 = 2 * gout149 + gout402;
    Ciphertext gout403 = ctx.eval_lut(&gin403, xor2);

    auto gin403clear = 2 * gout149clear + gout402clear;
    auto gout403clear = fxor2(gin403clear, 4);

    assert(ctx.decrypt(&gout403) == gout403clear);
    std::cerr << "\rLUT404   ";
    Ciphertext gin404 = 2 * gout365 + gout403;
    Ciphertext gout404 = ctx.eval_lut(&gin404, xnor2);

    auto gin404clear = 2 * gout365clear + gout403clear;
    auto gout404clear = fxnor2(gin404clear, 4);

    assert(ctx.decrypt(&gout404) == gout404clear);
    std::cerr << "\rLUT405   ";
    Ciphertext gin405 = 2 * (1 - gout365) + gout403;
    Ciphertext gout405 = ctx.eval_lut(&gin405, and2);

    auto gin405clear = 2 * (1 - gout365clear) + gout403clear;
    auto gout405clear = fand2(gin405clear, 4);

    assert(ctx.decrypt(&gout405) == gout405clear);
    std::cerr << "\rLUT406   ";
    Ciphertext gin406 = 2 * gout366 + gout405;
    Ciphertext gout406 = ctx.eval_lut(&gin406, or2);

    auto gin406clear = 2 * gout366clear + gout405clear;
    auto gout406clear = for2(gin406clear, 4);

    assert(ctx.decrypt(&gout406) == gout406clear);
    std::cerr << "\rLUT407   ";
    Ciphertext gin407 = 2 * gout406 + gout370;
    Ciphertext gout407 = ctx.eval_lut(&gin407, xnor2);

    auto gin407clear = 2 * gout406clear + gout370clear;
    auto gout407clear = fxnor2(gin407clear, 4);

    assert(ctx.decrypt(&gout407) == gout407clear);
    std::cerr << "\rLUT408   ";
    Ciphertext gin408 = 2 * gout406 + gout370;
    Ciphertext gout408 = ctx.eval_lut(&gin408, and2);

    auto gin408clear = 2 * gout406clear + gout370clear;
    auto gout408clear = fand2(gin408clear, 4);

    assert(ctx.decrypt(&gout408) == gout408clear);
    std::cerr << "\rLUT409   ";
    Ciphertext gin409 = 2 * gout149 + gout402;
    Ciphertext gout409 = ctx.eval_lut(&gin409, nand2);

    auto gin409clear = 2 * gout149clear + gout402clear;
    auto gout409clear = fnand2(gin409clear, 4);

    assert(ctx.decrypt(&gout409) == gout409clear);
    std::cerr << "\rLUT410   ";
    Ciphertext gin410 = 2 * gout202 + gout401;
    Ciphertext gout410 = ctx.eval_lut(&gin410, nand2);

    auto gin410clear = 2 * gout202clear + gout401clear;
    auto gout410clear = fnand2(gin410clear, 4);

    assert(ctx.decrypt(&gout410) == gout410clear);
    std::cerr << "\rLUT411   ";
    Ciphertext gin411 = 2 * gout410 + gout409;
    Ciphertext gout411 = ctx.eval_lut(&gin411, nand2);

    auto gin411clear = 2 * gout410clear + gout409clear;
    auto gout411clear = fnand2(gin411clear, 4);

    assert(ctx.decrypt(&gout411) == gout411clear);
    std::cerr << "\rLUT412   ";
    Ciphertext gin412 = 2 * gout411 + gout250;
    Ciphertext gout412 = ctx.eval_lut(&gin412, xor2);

    auto gin412clear = 2 * gout411clear + gout250clear;
    auto gout412clear = fxor2(gin412clear, 4);

    assert(ctx.decrypt(&gout412) == gout412clear);
    std::cerr << "\rLUT413   ";
    Ciphertext gin413 = 2 * gout362 + gout412;
    Ciphertext gout413 = ctx.eval_lut(&gin413, xor2);

    auto gin413clear = 2 * gout362clear + gout412clear;
    auto gout413clear = fxor2(gin413clear, 4);

    assert(ctx.decrypt(&gout413) == gout413clear);
    std::cerr << "\rLUT414   ";
    Ciphertext gin414 = 2 * gout407 + gout413;
    Ciphertext gout414 = ctx.eval_lut(&gin414, xnor2);

    auto gin414clear = 2 * gout407clear + gout413clear;
    auto gout414clear = fxnor2(gin414clear, 4);

    assert(ctx.decrypt(&gout414) == gout414clear);
    std::cerr << "\rLUT415   ";
    Ciphertext gin415 = 2 * (1 - gout407) + gout413;
    Ciphertext gout415 = ctx.eval_lut(&gin415, and2);

    auto gin415clear = 2 * (1 - gout407clear) + gout413clear;
    auto gout415clear = fand2(gin415clear, 4);

    assert(ctx.decrypt(&gout415) == gout415clear);
    std::cerr << "\rLUT416   ";
    Ciphertext gin416 = 2 * gout408 + gout415;
    Ciphertext gout416 = ctx.eval_lut(&gin416, or2);

    auto gin416clear = 2 * gout408clear + gout415clear;
    auto gout416clear = for2(gin416clear, 4);

    assert(ctx.decrypt(&gout416) == gout416clear);
    std::cerr << "\rLUT417   ";
    Ciphertext gin417 = 2 * gout362 + gout412;
    Ciphertext gout417 = ctx.eval_lut(&gin417, nand2);

    auto gin417clear = 2 * gout362clear + gout412clear;
    auto gout417clear = fnand2(gin417clear, 4);

    assert(ctx.decrypt(&gout417) == gout417clear);
    std::cerr << "\rLUT418   ";
    Ciphertext gin418 = 2 * gout411 + gout250;
    Ciphertext gout418 = ctx.eval_lut(&gin418, nand2);

    auto gin418clear = 2 * gout411clear + gout250clear;
    auto gout418clear = fnand2(gin418clear, 4);

    assert(ctx.decrypt(&gout418) == gout418clear);
    std::cerr << "\rLUT419   ";
    Ciphertext gin419 = 2 * gout418 + gout417;
    Ciphertext gout419 = ctx.eval_lut(&gin419, and2);

    auto gin419clear = 2 * gout418clear + gout417clear;
    auto gout419clear = fand2(gin419clear, 4);

    assert(ctx.decrypt(&gout419) == gout419clear);
    std::cerr << "\rLUT420   ";
    Ciphertext gin420 = 2 * gout419 + gout286;
    Ciphertext gout420 = ctx.eval_lut(&gin420, xnor2);

    auto gin420clear = 2 * gout419clear + gout286clear;
    auto gout420clear = fxnor2(gin420clear, 4);

    assert(ctx.decrypt(&gout420) == gout420clear);
    std::cerr << "\rLUT421   ";
    Ciphertext gin421 = 2 * gout34 + gout231;
    Ciphertext gout421 = ctx.eval_lut(&gin421, xor2);

    auto gin421clear = 2 * gout34clear + gout231clear;
    auto gout421clear = fxor2(gin421clear, 4);

    assert(ctx.decrypt(&gout421) == gout421clear);
    std::cerr << "\rLUT422   ";
    Ciphertext gin422 = 2 * gout65 + gout4;
    Ciphertext gout422 = ctx.eval_lut(&gin422, nand2);

    auto gin422clear = 2 * gout65clear + gout4clear;
    auto gout422clear = fnand2(gin422clear, 4);

    assert(ctx.decrypt(&gout422) == gout422clear);
    std::cerr << "\rLUT423   ";
    Ciphertext gin423 = 2 * gout307 + gout333;
    Ciphertext gout423 = ctx.eval_lut(&gin423, xor2);

    auto gin423clear = 2 * gout307clear + gout333clear;
    auto gout423clear = fxor2(gin423clear, 4);

    assert(ctx.decrypt(&gout423) == gout423clear);
    std::cerr << "\rLUT424   ";
    Ciphertext gin424 = 2 * ct_y1 + ct_x9;
    Ciphertext gout424 = ctx.eval_lut(&gin424, and2);

    auto gin424clear = 2 * ct_y1clear + ct_x9clear;
    auto gout424clear = fand2(gin424clear, 4);

    assert(ctx.decrypt(&gout424) == gout424clear);
    std::cerr << "\rLUT425   ";
    Ciphertext gin425 = 2 * gout424 + gout196;
    Ciphertext gout425 = ctx.eval_lut(&gin425, xor2);

    auto gin425clear = 2 * gout424clear + gout196clear;
    auto gout425clear = fxor2(gin425clear, 4);

    assert(ctx.decrypt(&gout425) == gout425clear);
    std::cerr << "\rLUT426   ";
    Ciphertext gin426 = 2 * gout424 + gout196;
    Ciphertext gout426 = ctx.eval_lut(&gin426, nand2);

    auto gin426clear = 2 * gout424clear + gout196clear;
    auto gout426clear = fnand2(gin426clear, 4);

    assert(ctx.decrypt(&gout426) == gout426clear);
    std::cerr << "\rLUT427   ";
    Ciphertext gin427 = 2 * gout182 + gout426;
    Ciphertext gout427 = ctx.eval_lut(&gin427, nand2);

    auto gin427clear = 2 * gout182clear + gout426clear;
    auto gout427clear = fnand2(gin427clear, 4);

    assert(ctx.decrypt(&gout427) == gout427clear);
    std::cerr << "\rLUT428   ";
    Ciphertext gin428 = 2 * gout427 + gout294;
    Ciphertext gout428 = ctx.eval_lut(&gin428, xnor2);

    auto gin428clear = 2 * gout427clear + gout294clear;
    auto gout428clear = fxnor2(gin428clear, 4);

    assert(ctx.decrypt(&gout428) == gout428clear);
    std::cerr << "\rLUT429   ";
    Ciphertext gin429 = 2 * gout428 + gout275;
    Ciphertext gout429 = ctx.eval_lut(&gin429, xnor2);

    auto gin429clear = 2 * gout428clear + gout275clear;
    auto gout429clear = fxnor2(gin429clear, 4);

    assert(ctx.decrypt(&gout429) == gout429clear);
    std::cerr << "\rLUT430   ";
    Ciphertext gin430 = 2 * (1 - gout428) + gout275;
    Ciphertext gout430 = ctx.eval_lut(&gin430, and2);

    auto gin430clear = 2 * (1 - gout428clear) + gout275clear;
    auto gout430clear = fand2(gin430clear, 4);

    assert(ctx.decrypt(&gout430) == gout430clear);
    std::cerr << "\rLUT431   ";
    Ciphertext gin431 = 2 * gout427 + gout294;
    Ciphertext gout431 = ctx.eval_lut(&gin431, and2);

    auto gin431clear = 2 * gout427clear + gout294clear;
    auto gout431clear = fand2(gin431clear, 4);

    assert(ctx.decrypt(&gout431) == gout431clear);
    std::cerr << "\rLUT432   ";
    Ciphertext gin432 = 2 * gout431 + gout430;
    Ciphertext gout432 = ctx.eval_lut(&gin432, or2);

    auto gin432clear = 2 * gout431clear + gout430clear;
    auto gout432clear = for2(gin432clear, 4);

    assert(ctx.decrypt(&gout432) == gout432clear);
    std::cerr << "\rLUT433   ";
    Ciphertext gin433 = 2 * gout39 + gout92;
    Ciphertext gout433 = ctx.eval_lut(&gin433, xnor2);

    auto gin433clear = 2 * gout39clear + gout92clear;
    auto gout433clear = fxnor2(gin433clear, 4);

    assert(ctx.decrypt(&gout433) == gout433clear);
    std::cerr << "\rLUT434   ";
    Ciphertext gin434 = 2 * gout201 + gout433;
    Ciphertext gout434 = ctx.eval_lut(&gin434, xor2);

    auto gin434clear = 2 * gout201clear + gout433clear;
    auto gout434clear = fxor2(gin434clear, 4);

    assert(ctx.decrypt(&gout434) == gout434clear);
    std::cerr << "\rLUT435   ";
    Ciphertext gin435 = 2 * gout257 + gout281;
    Ciphertext gout435 = ctx.eval_lut(&gin435, xnor2);

    auto gin435clear = 2 * gout257clear + gout281clear;
    auto gout435clear = fxnor2(gin435clear, 4);

    assert(ctx.decrypt(&gout435) == gout435clear);
    std::cerr << "\rIMUX436  ";
    Ciphertext gin436A = 2 * gout435 + gout104;
    Ciphertext gout436A = ctx.eval_lut(&gin436A, and2);
    Ciphertext gin436B = 2 * gout380 + (1 - gout104);
    Ciphertext gout436B = ctx.eval_lut(&gin436B, and2);
    Ciphertext gout436 = gout436A + gout436B;

    long gin436Aclear = 2 * gout435clear + gout104clear;
    long gout436Aclear = fand2(gin436Aclear, 4);
    long gin436Bclear = 2 * gout380clear + (1 - gout104clear);
    long gout436Bclear = fand2(gin436Bclear, 4);
    long gout436clear = gout436Aclear + gout436Bclear;

    assert(ctx.decrypt(&gout436) == gout436clear);
    std::cerr << "\rLUT437   ";
    Ciphertext gin437 = 2 * gout218 + gout436;
    Ciphertext gout437 = ctx.eval_lut(&gin437, nand2);

    auto gin437clear = 2 * gout218clear + gout436clear;
    auto gout437clear = fnand2(gin437clear, 4);

    assert(ctx.decrypt(&gout437) == gout437clear);
    std::cerr << "\rLUT438   ";
    Ciphertext gin438 = 2 * gout203 + gout288;
    Ciphertext gout438 = ctx.eval_lut(&gin438, nand2);

    auto gin438clear = 2 * gout203clear + gout288clear;
    auto gout438clear = fnand2(gin438clear, 4);

    assert(ctx.decrypt(&gout438) == gout438clear);
    std::cerr << "\rLUT439   ";
    Ciphertext gin439 = 2 * gout128 + gout438;
    Ciphertext gout439 = ctx.eval_lut(&gin439, nand2);

    auto gin439clear = 2 * gout128clear + gout438clear;
    auto gout439clear = fnand2(gin439clear, 4);

    assert(ctx.decrypt(&gout439) == gout439clear);
    std::cerr << "\rLUT440   ";
    Ciphertext gin440 = 2 * gout439 + gout153;
    Ciphertext gout440 = ctx.eval_lut(&gin440, xor2);

    auto gin440clear = 2 * gout439clear + gout153clear;
    auto gout440clear = fxor2(gin440clear, 4);

    assert(ctx.decrypt(&gout440) == gout440clear);
    std::cerr << "\rLUT441   ";
    Ciphertext gin441 = 2 * gout252 + gout440;
    Ciphertext gout441 = ctx.eval_lut(&gin441, xnor2);

    auto gin441clear = 2 * gout252clear + gout440clear;
    auto gout441clear = fxnor2(gin441clear, 4);

    assert(ctx.decrypt(&gout441) == gout441clear);
    std::cerr << "\rLUT442   ";
    Ciphertext gin442 = 2 * gout194 + gout440;
    Ciphertext gout442 = ctx.eval_lut(&gin442, nand2);

    auto gin442clear = 2 * gout194clear + gout440clear;
    auto gout442clear = fnand2(gin442clear, 4);

    assert(ctx.decrypt(&gout442) == gout442clear);
    std::cerr << "\rLUT443   ";
    Ciphertext gin443 = 2 * gout439 + gout153;
    Ciphertext gout443 = ctx.eval_lut(&gin443, nand2);

    auto gin443clear = 2 * gout439clear + gout153clear;
    auto gout443clear = fnand2(gin443clear, 4);

    assert(ctx.decrypt(&gout443) == gout443clear);
    std::cerr << "\rLUT444   ";
    Ciphertext gin444 = 2 * gout443 + gout442;
    Ciphertext gout444 = ctx.eval_lut(&gin444, nand2);

    auto gin444clear = 2 * gout443clear + gout442clear;
    auto gout444clear = fnand2(gin444clear, 4);

    assert(ctx.decrypt(&gout444) == gout444clear);
    std::cerr << "\rLUT445   ";
    Ciphertext gin445 = 2 * gout200 + gout43;
    Ciphertext gout445 = ctx.eval_lut(&gin445, xnor2);

    auto gin445clear = 2 * gout200clear + gout43clear;
    auto gout445clear = fxnor2(gin445clear, 4);

    assert(ctx.decrypt(&gout445) == gout445clear);
    std::cerr << "\rLUT446   ";
    Ciphertext gin446 = 2 * gout160 + gout347;
    Ciphertext gout446 = ctx.eval_lut(&gin446, and2);

    auto gin446clear = 2 * gout160clear + gout347clear;
    auto gout446clear = fand2(gin446clear, 4);

    assert(ctx.decrypt(&gout446) == gout446clear);
    std::cerr << "\rLUT447   ";
    Ciphertext gin447 = 2 * gout35 + gout446;
    Ciphertext gout447 = ctx.eval_lut(&gin447, and2);

    auto gin447clear = 2 * gout35clear + gout446clear;
    auto gout447clear = fand2(gin447clear, 4);

    assert(ctx.decrypt(&gout447) == gout447clear);
    std::cerr << "\rLUT448   ";
    Ciphertext gin448 = 2 * gout88 + gout447;
    Ciphertext gout448 = ctx.eval_lut(&gin448, and2);

    auto gin448clear = 2 * gout88clear + gout447clear;
    auto gout448clear = fand2(gin448clear, 4);

    assert(ctx.decrypt(&gout448) == gout448clear);
    std::cerr << "\rLUT449   ";
    Ciphertext gin449 = 2 * gout37 + gout448;
    Ciphertext gout449 = ctx.eval_lut(&gin449, and2);

    auto gin449clear = 2 * gout37clear + gout448clear;
    auto gout449clear = fand2(gin449clear, 4);

    assert(ctx.decrypt(&gout449) == gout449clear);
    std::cerr << "\rLUT450   ";
    Ciphertext gin450 = 2 * gout199 + gout449;
    Ciphertext gout450 = ctx.eval_lut(&gin450, and2);

    auto gin450clear = 2 * gout199clear + gout449clear;
    auto gout450clear = fand2(gin450clear, 4);

    assert(ctx.decrypt(&gout450) == gout450clear);
    std::cerr << "\rLUT451   ";
    Ciphertext gin451 = 2 * gout198 + gout450;
    Ciphertext gout451 = ctx.eval_lut(&gin451, and2);

    auto gin451clear = 2 * gout198clear + gout450clear;
    auto gout451clear = fand2(gin451clear, 4);

    assert(ctx.decrypt(&gout451) == gout451clear);
    std::cerr << "\rLUT452   ";
    Ciphertext gin452 = 2 * gout20 + gout451;
    Ciphertext gout452 = ctx.eval_lut(&gin452, nand2);

    auto gin452clear = 2 * gout20clear + gout451clear;
    auto gout452clear = fnand2(gin452clear, 4);

    assert(ctx.decrypt(&gout452) == gout452clear);
    std::cerr << "\rLUT453   ";
    Ciphertext gin453 = 2 * gout211 + gout452;
    Ciphertext gout453 = ctx.eval_lut(&gin453, and2);

    auto gin453clear = 2 * gout211clear + gout452clear;
    auto gout453clear = fand2(gin453clear, 4);

    assert(ctx.decrypt(&gout453) == gout453clear);
    std::cerr << "\rLUT454   ";
    Ciphertext gin454 = 2 * (1 - gout453) + gout215;
    Ciphertext gout454 = ctx.eval_lut(&gin454, and2);

    auto gin454clear = 2 * (1 - gout453clear) + gout215clear;
    auto gout454clear = fand2(gin454clear, 4);

    assert(ctx.decrypt(&gout454) == gout454clear);
    std::cerr << "\rLUT455   ";
    Ciphertext gin455 = 2 * gout454 + gout214;
    Ciphertext gout455 = ctx.eval_lut(&gin455, nand2);

    auto gin455clear = 2 * gout454clear + gout214clear;
    auto gout455clear = fnand2(gin455clear, 4);

    assert(ctx.decrypt(&gout455) == gout455clear);
    std::cerr << "\rLUT456   ";
    Ciphertext gin456 = 2 * gout455 + gout213;
    Ciphertext gout456 = ctx.eval_lut(&gin456, or2);

    auto gin456clear = 2 * gout455clear + gout213clear;
    auto gout456clear = for2(gin456clear, 4);

    assert(ctx.decrypt(&gout456) == gout456clear);
    std::cerr << "\rLUT457   ";
    Ciphertext gin457 = 2 * gout456 + gout212;
    Ciphertext gout457 = ctx.eval_lut(&gin457, or2);

    auto gin457clear = 2 * gout456clear + gout212clear;
    auto gout457clear = for2(gin457clear, 4);

    assert(ctx.decrypt(&gout457) == gout457clear);
    std::cerr << "\rLUT458   ";
    Ciphertext gin458 = 2 * gout457 + gout23;
    Ciphertext gout458 = ctx.eval_lut(&gin458, xnor2);

    auto gin458clear = 2 * gout457clear + gout23clear;
    auto gout458clear = fxnor2(gin458clear, 4);

    assert(ctx.decrypt(&gout458) == gout458clear);
    std::cerr << "\rLUT459   ";
    Ciphertext gin459 = 2 * gout74 + gout456;
    Ciphertext gout459 = ctx.eval_lut(&gin459, xnor2);

    auto gin459clear = 2 * gout74clear + gout456clear;
    auto gout459clear = fxnor2(gin459clear, 4);

    assert(ctx.decrypt(&gout459) == gout459clear);
    std::cerr << "\rLUT460   ";
    Ciphertext gin460 = 2 * gout24 + gout459;
    Ciphertext gout460 = ctx.eval_lut(&gin460, xnor2);

    auto gin460clear = 2 * gout24clear + gout459clear;
    auto gout460clear = fxnor2(gin460clear, 4);

    assert(ctx.decrypt(&gout460) == gout460clear);
    std::cerr << "\rLUT461   ";
    Ciphertext gin461 = 2 * ct_x14 + gout459;
    Ciphertext gout461 = ctx.eval_lut(&gin461, nand2);

    auto gin461clear = 2 * ct_x14clear + gout459clear;
    auto gout461clear = fnand2(gin461clear, 4);

    assert(ctx.decrypt(&gout461) == gout461clear);
    std::cerr << "\rLUT462   ";
    Ciphertext gin462 = 2 * ct_y13 + gout455;
    Ciphertext gout462 = ctx.eval_lut(&gin462, xnor2);

    auto gin462clear = 2 * ct_y13clear + gout455clear;
    auto gout462clear = fxnor2(gin462clear, 4);

    assert(ctx.decrypt(&gout462) == gout462clear);
    std::cerr << "\rLUT463   ";
    Ciphertext gin463 = 2 * ct_x13 + gout462;
    Ciphertext gout463 = ctx.eval_lut(&gin463, xnor2);

    auto gin463clear = 2 * ct_x13clear + gout462clear;
    auto gout463clear = fxnor2(gin463clear, 4);

    assert(ctx.decrypt(&gout463) == gout463clear);
    std::cerr << "\rINV464   ";
    Ciphertext gout464 = 1 - gout463;

    long gout464clear = 1 - gout463clear;

    assert(ctx.decrypt(&gout464) == gout464clear);
    std::cerr << "\rLUT465   ";
    Ciphertext gin465 = 2 * gout197 + gout462;
    Ciphertext gout465 = ctx.eval_lut(&gin465, nand2);

    auto gin465clear = 2 * gout197clear + gout462clear;
    auto gout465clear = fnand2(gin465clear, 4);

    assert(ctx.decrypt(&gout465) == gout465clear);
    std::cerr << "\rLUT466   ";
    Ciphertext gin466 = 2 * gout197 + gout462;
    Ciphertext gout466 = ctx.eval_lut(&gin466, or2);

    auto gin466clear = 2 * gout197clear + gout462clear;
    auto gout466clear = for2(gin466clear, 4);

    assert(ctx.decrypt(&gout466) == gout466clear);
    std::cerr << "\rLUT467   ";
    Ciphertext gin467 = 2 * ct_y12 + gout454;
    Ciphertext gout467 = ctx.eval_lut(&gin467, xnor2);

    auto gin467clear = 2 * ct_y12clear + gout454clear;
    auto gout467clear = fxnor2(gin467clear, 4);

    assert(ctx.decrypt(&gout467) == gout467clear);
    std::cerr << "\rLUT468   ";
    Ciphertext gin468 = 2 * gout31 + gout467;
    Ciphertext gout468 = ctx.eval_lut(&gin468, xnor2);

    auto gin468clear = 2 * gout31clear + gout467clear;
    auto gout468clear = fxnor2(gin468clear, 4);

    assert(ctx.decrypt(&gout468) == gout468clear);
    std::cerr << "\rLUT469   ";
    Ciphertext gin469 = 2 * ct_x12 + gout467;
    Ciphertext gout469 = ctx.eval_lut(&gin469, nand2);

    auto gin469clear = 2 * ct_x12clear + gout467clear;
    auto gout469clear = fnand2(gin469clear, 4);

    assert(ctx.decrypt(&gout469) == gout469clear);
    std::cerr << "\rLUT470   ";
    Ciphertext gin470 = 2 * gout469 + gout466;
    Ciphertext gout470 = ctx.eval_lut(&gin470, nand2);

    auto gin470clear = 2 * gout469clear + gout466clear;
    auto gout470clear = fnand2(gin470clear, 4);

    assert(ctx.decrypt(&gout470) == gout470clear);
    std::cerr << "\rLUT471   ";
    Ciphertext gin471 = 2 * gout465 + gout470;
    Ciphertext gout471 = ctx.eval_lut(&gin471, nand2);

    auto gin471clear = 2 * gout465clear + gout470clear;
    auto gout471clear = fnand2(gin471clear, 4);

    assert(ctx.decrypt(&gout471) == gout471clear);
    std::cerr << "\rLUT472   ";
    Ciphertext gin472 = 2 * ct_y11 + gout453;
    Ciphertext gout472 = ctx.eval_lut(&gin472, xnor2);

    auto gin472clear = 2 * ct_y11clear + gout453clear;
    auto gout472clear = fxnor2(gin472clear, 4);

    assert(ctx.decrypt(&gout472) == gout472clear);
    std::cerr << "\rLUT473   ";
    Ciphertext gin473 = 2 * ct_x11 + gout472;
    Ciphertext gout473 = ctx.eval_lut(&gin473, xnor2);

    auto gin473clear = 2 * ct_x11clear + gout472clear;
    auto gout473clear = fxnor2(gin473clear, 4);

    assert(ctx.decrypt(&gout473) == gout473clear);
    std::cerr << "\rINV474   ";
    Ciphertext gout474 = 1 - gout473;

    long gout474clear = 1 - gout473clear;

    assert(ctx.decrypt(&gout474) == gout474clear);
    std::cerr << "\rLUT475   ";
    Ciphertext gin475 = 2 * gout73 + gout472;
    Ciphertext gout475 = ctx.eval_lut(&gin475, nand2);

    auto gin475clear = 2 * gout73clear + gout472clear;
    auto gout475clear = fnand2(gin475clear, 4);

    assert(ctx.decrypt(&gout475) == gout475clear);
    std::cerr << "\rLUT476   ";
    Ciphertext gin476 = 2 * gout73 + gout472;
    Ciphertext gout476 = ctx.eval_lut(&gin476, or2);

    auto gin476clear = 2 * gout73clear + gout472clear;
    auto gout476clear = for2(gin476clear, 4);

    assert(ctx.decrypt(&gout476) == gout476clear);
    std::cerr << "\rLUT477   ";
    Ciphertext gin477 = 2 * (1 - gout451) + gout211;
    Ciphertext gout477 = ctx.eval_lut(&gin477, and2);

    auto gin477clear = 2 * (1 - gout451clear) + gout211clear;
    auto gout477clear = fand2(gin477clear, 4);

    assert(ctx.decrypt(&gout477) == gout477clear);
    std::cerr << "\rLUT478   ";
    Ciphertext gin478 = 2 * gout20 + gout477;
    Ciphertext gout478 = ctx.eval_lut(&gin478, xnor2);

    auto gin478clear = 2 * gout20clear + gout477clear;
    auto gout478clear = fxnor2(gin478clear, 4);

    assert(ctx.decrypt(&gout478) == gout478clear);
    std::cerr << "\rLUT479   ";
    Ciphertext gin479 = 2 * gout116 + gout478;
    Ciphertext gout479 = ctx.eval_lut(&gin479, xnor2);

    auto gin479clear = 2 * gout116clear + gout478clear;
    auto gout479clear = fxnor2(gin479clear, 4);

    assert(ctx.decrypt(&gout479) == gout479clear);
    std::cerr << "\rLUT480   ";
    Ciphertext gin480 = 2 * ct_x10 + gout478;
    Ciphertext gout480 = ctx.eval_lut(&gin480, nand2);

    auto gin480clear = 2 * ct_x10clear + gout478clear;
    auto gout480clear = fnand2(gin480clear, 4);

    assert(ctx.decrypt(&gout480) == gout480clear);
    std::cerr << "\rLUT481   ";
    Ciphertext gin481 = 2 * gout480 + gout476;
    Ciphertext gout481 = ctx.eval_lut(&gin481, nand2);

    auto gin481clear = 2 * gout480clear + gout476clear;
    auto gout481clear = fnand2(gin481clear, 4);

    assert(ctx.decrypt(&gout481) == gout481clear);
    std::cerr << "\rLUT482   ";
    Ciphertext gin482 = 2 * gout475 + gout481;
    Ciphertext gout482 = ctx.eval_lut(&gin482, nand2);

    auto gin482clear = 2 * gout475clear + gout481clear;
    auto gout482clear = fnand2(gin482clear, 4);

    assert(ctx.decrypt(&gout482) == gout482clear);
    std::cerr << "\rLUT483   ";
    Ciphertext gin483 = 2 * (1 - gout450) + gout211;
    Ciphertext gout483 = ctx.eval_lut(&gin483, and2);

    auto gin483clear = 2 * (1 - gout450clear) + gout211clear;
    auto gout483clear = fand2(gin483clear, 4);

    assert(ctx.decrypt(&gout483) == gout483clear);
    std::cerr << "\rLUT484   ";
    Ciphertext gin484 = 2 * (1 - gout449) + gout211;
    Ciphertext gout484 = ctx.eval_lut(&gin484, and2);

    auto gin484clear = 2 * (1 - gout449clear) + gout211clear;
    auto gout484clear = fand2(gin484clear, 4);

    assert(ctx.decrypt(&gout484) == gout484clear);
    std::cerr << "\rLUT485   ";
    Ciphertext gin485 = 2 * gout199 + gout484;
    Ciphertext gout485 = ctx.eval_lut(&gin485, xnor2);

    auto gin485clear = 2 * gout199clear + gout484clear;
    auto gout485clear = fxnor2(gin485clear, 4);

    assert(ctx.decrypt(&gout485) == gout485clear);
    std::cerr << "\rLUT486   ";
    Ciphertext gin486 = 2 * gout27 + gout485;
    Ciphertext gout486 = ctx.eval_lut(&gin486, xnor2);

    auto gin486clear = 2 * gout27clear + gout485clear;
    auto gout486clear = fxnor2(gin486clear, 4);

    assert(ctx.decrypt(&gout486) == gout486clear);
    std::cerr << "\rLUT487   ";
    Ciphertext gin487 = 2 * ct_x8 + gout485;
    Ciphertext gout487 = ctx.eval_lut(&gin487, nand2);

    auto gin487clear = 2 * ct_x8clear + gout485clear;
    auto gout487clear = fnand2(gin487clear, 4);

    assert(ctx.decrypt(&gout487) == gout487clear);
    std::cerr << "\rLUT488   ";
    Ciphertext gin488 = 2 * (1 - gout448) + gout211;
    Ciphertext gout488 = ctx.eval_lut(&gin488, and2);

    auto gin488clear = 2 * (1 - gout448clear) + gout211clear;
    auto gout488clear = fand2(gin488clear, 4);

    assert(ctx.decrypt(&gout488) == gout488clear);
    std::cerr << "\rLUT489   ";
    Ciphertext gin489 = 2 * gout37 + gout488;
    Ciphertext gout489 = ctx.eval_lut(&gin489, xnor2);

    auto gin489clear = 2 * gout37clear + gout488clear;
    auto gout489clear = fxnor2(gin489clear, 4);

    assert(ctx.decrypt(&gout489) == gout489clear);
    std::cerr << "\rLUT490   ";
    Ciphertext gin490 = 2 * gout80 + gout489;
    Ciphertext gout490 = ctx.eval_lut(&gin490, xnor2);

    auto gin490clear = 2 * gout80clear + gout489clear;
    auto gout490clear = fxnor2(gin490clear, 4);

    assert(ctx.decrypt(&gout490) == gout490clear);
    std::cerr << "\rLUT491   ";
    Ciphertext gin491 = 2 * ct_x7 + gout489;
    Ciphertext gout491 = ctx.eval_lut(&gin491, nand2);

    auto gin491clear = 2 * ct_x7clear + gout489clear;
    auto gout491clear = fnand2(gin491clear, 4);

    assert(ctx.decrypt(&gout491) == gout491clear);
    std::cerr << "\rLUT492   ";
    Ciphertext gin492 = 2 * (1 - gout447) + gout211;
    Ciphertext gout492 = ctx.eval_lut(&gin492, and2);

    auto gin492clear = 2 * (1 - gout447clear) + gout211clear;
    auto gout492clear = fand2(gin492clear, 4);

    assert(ctx.decrypt(&gout492) == gout492clear);
    std::cerr << "\rLUT493   ";
    Ciphertext gin493 = 2 * gout88 + gout492;
    Ciphertext gout493 = ctx.eval_lut(&gin493, xnor2);

    auto gin493clear = 2 * gout88clear + gout492clear;
    auto gout493clear = fxnor2(gin493clear, 4);

    assert(ctx.decrypt(&gout493) == gout493clear);
    std::cerr << "\rLUT494   ";
    Ciphertext gin494 = 2 * gout26 + gout493;
    Ciphertext gout494 = ctx.eval_lut(&gin494, xnor2);

    auto gin494clear = 2 * gout26clear + gout493clear;
    auto gout494clear = fxnor2(gin494clear, 4);

    assert(ctx.decrypt(&gout494) == gout494clear);
    std::cerr << "\rLUT495   ";
    Ciphertext gin495 = 2 * ct_x6 + gout493;
    Ciphertext gout495 = ctx.eval_lut(&gin495, nand2);

    auto gin495clear = 2 * ct_x6clear + gout493clear;
    auto gout495clear = fnand2(gin495clear, 4);

    assert(ctx.decrypt(&gout495) == gout495clear);
    std::cerr << "\rLUT496   ";
    Ciphertext gin496 = 2 * (1 - gout446) + gout211;
    Ciphertext gout496 = ctx.eval_lut(&gin496, and2);

    auto gin496clear = 2 * (1 - gout446clear) + gout211clear;
    auto gout496clear = fand2(gin496clear, 4);

    assert(ctx.decrypt(&gout496) == gout496clear);
    std::cerr << "\rLUT497   ";
    Ciphertext gin497 = 2 * gout35 + gout496;
    Ciphertext gout497 = ctx.eval_lut(&gin497, xnor2);

    auto gin497clear = 2 * gout35clear + gout496clear;
    auto gout497clear = fxnor2(gin497clear, 4);

    assert(ctx.decrypt(&gout497) == gout497clear);
    std::cerr << "\rLUT498   ";
    Ciphertext gin498 = 2 * gout195 + gout497;
    Ciphertext gout498 = ctx.eval_lut(&gin498, xnor2);

    auto gin498clear = 2 * gout195clear + gout497clear;
    auto gout498clear = fxnor2(gin498clear, 4);

    assert(ctx.decrypt(&gout498) == gout498clear);
    std::cerr << "\rLUT499   ";
    Ciphertext gin499 = 2 * ct_x5 + gout497;
    Ciphertext gout499 = ctx.eval_lut(&gin499, nand2);

    auto gin499clear = 2 * ct_x5clear + gout497clear;
    auto gout499clear = fnand2(gin499clear, 4);

    assert(ctx.decrypt(&gout499) == gout499clear);
    std::cerr << "\rLUT500   ";
    Ciphertext gin500 = 2 * gout104 + gout254;
    Ciphertext gout500 = ctx.eval_lut(&gin500, nand2);

    auto gin500clear = 2 * gout104clear + gout254clear;
    auto gout500clear = fnand2(gin500clear, 4);

    assert(ctx.decrypt(&gout500) == gout500clear);
    std::cerr << "\rLUT501   ";
    Ciphertext gin501 = 2 * gout500 + gout220;
    Ciphertext gout501 = ctx.eval_lut(&gin501, nand2);

    auto gin501clear = 2 * gout500clear + gout220clear;
    auto gout501clear = fnand2(gin501clear, 4);

    assert(ctx.decrypt(&gout501) == gout501clear);
    std::cerr << "\rLUT502   ";
    Ciphertext gin502 = 2 * ct_y1 + ct_x2;
    Ciphertext gout502 = ctx.eval_lut(&gin502, and2);

    auto gin502clear = 2 * ct_y1clear + ct_x2clear;
    auto gout502clear = fand2(gin502clear, 4);

    assert(ctx.decrypt(&gout502) == gout502clear);
    std::cerr << "\rLUT503   ";
    Ciphertext gin503 = 2 * gout502 + gout145;
    Ciphertext gout503 = ctx.eval_lut(&gin503, xor2);

    auto gin503clear = 2 * gout502clear + gout145clear;
    auto gout503clear = fxor2(gin503clear, 4);

    assert(ctx.decrypt(&gout503) == gout503clear);
    std::cerr << "\rLUT504   ";
    Ciphertext gin504 = 2 * gout239 + gout503;
    Ciphertext gout504 = ctx.eval_lut(&gin504, xor2);

    auto gin504clear = 2 * gout239clear + gout503clear;
    auto gout504clear = fxor2(gin504clear, 4);

    assert(ctx.decrypt(&gout504) == gout504clear);
    std::cerr << "\rLUT505   ";
    Ciphertext gin505 = 2 * gout136 + gout504;
    Ciphertext gout505 = ctx.eval_lut(&gin505, xnor2);

    auto gin505clear = 2 * gout136clear + gout504clear;
    auto gout505clear = fxnor2(gin505clear, 4);

    assert(ctx.decrypt(&gout505) == gout505clear);
    std::cerr << "\rLUT506   ";
    Ciphertext gin506 = 2 * gout208 + gout505;
    Ciphertext gout506 = ctx.eval_lut(&gin506, xnor2);

    auto gin506clear = 2 * gout208clear + gout505clear;
    auto gout506clear = fxnor2(gin506clear, 4);

    assert(ctx.decrypt(&gout506) == gout506clear);
    std::cerr << "\rLUT507   ";
    Ciphertext gin507 = 2 * gout207 + gout505;
    Ciphertext gout507 = ctx.eval_lut(&gin507, and2);

    auto gin507clear = 2 * gout207clear + gout505clear;
    auto gout507clear = fand2(gin507clear, 4);

    assert(ctx.decrypt(&gout507) == gout507clear);
    std::cerr << "\rINV508   ";
    Ciphertext gout508 = 1 - gout507;

    long gout508clear = 1 - gout507clear;

    assert(ctx.decrypt(&gout508) == gout508clear);
    std::cerr << "\rLUT509   ";
    Ciphertext gin509 = 2 * gout91 + gout504;
    Ciphertext gout509 = ctx.eval_lut(&gin509, nand2);

    auto gin509clear = 2 * gout91clear + gout504clear;
    auto gout509clear = fnand2(gin509clear, 4);

    assert(ctx.decrypt(&gout509) == gout509clear);
    std::cerr << "\rLUT510   ";
    Ciphertext gin510 = 2 * gout239 + gout503;
    Ciphertext gout510 = ctx.eval_lut(&gin510, nand2);

    auto gin510clear = 2 * gout239clear + gout503clear;
    auto gout510clear = fnand2(gin510clear, 4);

    assert(ctx.decrypt(&gout510) == gout510clear);
    std::cerr << "\rLUT511   ";
    Ciphertext gin511 = 2 * gout510 + gout509;
    Ciphertext gout511 = ctx.eval_lut(&gin511, nand2);

    auto gin511clear = 2 * gout510clear + gout509clear;
    auto gout511clear = fnand2(gin511clear, 4);

    assert(ctx.decrypt(&gout511) == gout511clear);
    std::cerr << "\rLUT512   ";
    Ciphertext gin512 = 2 * gout502 + gout145;
    Ciphertext gout512 = ctx.eval_lut(&gin512, nand2);

    auto gin512clear = 2 * gout502clear + gout145clear;
    auto gout512clear = fnand2(gin512clear, 4);

    assert(ctx.decrypt(&gout512) == gout512clear);
    std::cerr << "\rLUT513   ";
    Ciphertext gin513 = 2 * gout107 + gout512;
    Ciphertext gout513 = ctx.eval_lut(&gin513, nand2);

    auto gin513clear = 2 * gout107clear + gout512clear;
    auto gout513clear = fnand2(gin513clear, 4);

    assert(ctx.decrypt(&gout513) == gout513clear);
    std::cerr << "\rLUT514   ";
    Ciphertext gin514 = 2 * gout513 + gout172;
    Ciphertext gout514 = ctx.eval_lut(&gin514, xnor2);

    auto gin514clear = 2 * gout513clear + gout172clear;
    auto gout514clear = fxnor2(gin514clear, 4);

    assert(ctx.decrypt(&gout514) == gout514clear);
    std::cerr << "\rLUT515   ";
    Ciphertext gin515 = 2 * gout514 + gout309;
    Ciphertext gout515 = ctx.eval_lut(&gin515, xnor2);

    auto gin515clear = 2 * gout514clear + gout309clear;
    auto gout515clear = fxnor2(gin515clear, 4);

    assert(ctx.decrypt(&gout515) == gout515clear);
    std::cerr << "\rLUT516   ";
    Ciphertext gin516 = 2 * gout511 + gout515;
    Ciphertext gout516 = ctx.eval_lut(&gin516, xor2);

    auto gin516clear = 2 * gout511clear + gout515clear;
    auto gout516clear = fxor2(gin516clear, 4);

    assert(ctx.decrypt(&gout516) == gout516clear);
    std::cerr << "\rLUT517   ";
    Ciphertext gin517 = 2 * gout507 + gout516;
    Ciphertext gout517 = ctx.eval_lut(&gin517, and2);

    auto gin517clear = 2 * gout507clear + gout516clear;
    auto gout517clear = fand2(gin517clear, 4);

    assert(ctx.decrypt(&gout517) == gout517clear);
    std::cerr << "\rLUT518   ";
    Ciphertext gin518 = 2 * gout511 + gout515;
    Ciphertext gout518 = ctx.eval_lut(&gin518, and2);

    auto gin518clear = 2 * gout511clear + gout515clear;
    auto gout518clear = fand2(gin518clear, 4);

    assert(ctx.decrypt(&gout518) == gout518clear);
    std::cerr << "\rLUT519   ";
    Ciphertext gin519 = 2 * gout518 + gout517;
    Ciphertext gout519 = ctx.eval_lut(&gin519, or2);

    auto gin519clear = 2 * gout518clear + gout517clear;
    auto gout519clear = for2(gin519clear, 4);

    assert(ctx.decrypt(&gout519) == gout519clear);
    std::cerr << "\rLUT520   ";
    Ciphertext gin520 = 2 * (1 - gout514) + gout309;
    Ciphertext gout520 = ctx.eval_lut(&gin520, and2);

    auto gin520clear = 2 * (1 - gout514clear) + gout309clear;
    auto gout520clear = fand2(gin520clear, 4);

    assert(ctx.decrypt(&gout520) == gout520clear);
    std::cerr << "\rLUT521   ";
    Ciphertext gin521 = 2 * gout513 + gout172;
    Ciphertext gout521 = ctx.eval_lut(&gin521, and2);

    auto gin521clear = 2 * gout513clear + gout172clear;
    auto gout521clear = fand2(gin521clear, 4);

    assert(ctx.decrypt(&gout521) == gout521clear);
    std::cerr << "\rLUT522   ";
    Ciphertext gin522 = 2 * gout521 + gout520;
    Ciphertext gout522 = ctx.eval_lut(&gin522, or2);

    auto gin522clear = 2 * gout521clear + gout520clear;
    auto gout522clear = for2(gin522clear, 4);

    assert(ctx.decrypt(&gout522) == gout522clear);
    std::cerr << "\rLUT523   ";
    Ciphertext gin523 = 2 * gout307 + gout333;
    Ciphertext gout523 = ctx.eval_lut(&gin523, nand2);

    auto gin523clear = 2 * gout307clear + gout333clear;
    auto gout523clear = fnand2(gin523clear, 4);

    assert(ctx.decrypt(&gout523) == gout523clear);
    std::cerr << "\rLUT524   ";
    Ciphertext gin524 = 2 * gout334 + gout523;
    Ciphertext gout524 = ctx.eval_lut(&gin524, nand2);

    auto gin524clear = 2 * gout334clear + gout523clear;
    auto gout524clear = fnand2(gin524clear, 4);

    assert(ctx.decrypt(&gout524) == gout524clear);
    std::cerr << "\rLUT525   ";
    Ciphertext gin525 = 2 * gout524 + gout441;
    Ciphertext gout525 = ctx.eval_lut(&gin525, xor2);

    auto gin525clear = 2 * gout524clear + gout441clear;
    auto gout525clear = fxor2(gin525clear, 4);

    assert(ctx.decrypt(&gout525) == gout525clear);
    std::cerr << "\rLUT526   ";
    Ciphertext gin526 = 2 * gout291 + gout525;
    Ciphertext gout526 = ctx.eval_lut(&gin526, xor2);

    auto gin526clear = 2 * gout291clear + gout525clear;
    auto gout526clear = fxor2(gin526clear, 4);

    assert(ctx.decrypt(&gout526) == gout526clear);
    std::cerr << "\rLUT527   ";
    Ciphertext gin527 = 2 * gout291 + gout525;
    Ciphertext gout527 = ctx.eval_lut(&gin527, nand2);

    auto gin527clear = 2 * gout291clear + gout525clear;
    auto gout527clear = fnand2(gin527clear, 4);

    assert(ctx.decrypt(&gout527) == gout527clear);
    std::cerr << "\rLUT528   ";
    Ciphertext gin528 = 2 * gout524 + gout441;
    Ciphertext gout528 = ctx.eval_lut(&gin528, nand2);

    auto gin528clear = 2 * gout524clear + gout441clear;
    auto gout528clear = fnand2(gin528clear, 4);

    assert(ctx.decrypt(&gout528) == gout528clear);
    std::cerr << "\rLUT529   ";
    Ciphertext gin529 = 2 * gout528 + gout527;
    Ciphertext gout529 = ctx.eval_lut(&gin529, nand2);

    auto gin529clear = 2 * gout528clear + gout527clear;
    auto gout529clear = fnand2(gin529clear, 4);

    assert(ctx.decrypt(&gout529) == gout529clear);
    std::cerr << "\rLUT530   ";
    Ciphertext gin530 = 2 * ct_y4 + ct_x8;
    Ciphertext gout530 = ctx.eval_lut(&gin530, and2);

    auto gin530clear = 2 * ct_y4clear + ct_x8clear;
    auto gout530clear = fand2(gin530clear, 4);

    assert(ctx.decrypt(&gout530) == gout530clear);
    std::cerr << "\rLUT531   ";
    Ciphertext gin531 = 2 * gout530 + gout253;
    Ciphertext gout531 = ctx.eval_lut(&gin531, xor2);

    auto gin531clear = 2 * gout530clear + gout253clear;
    auto gout531clear = fxor2(gin531clear, 4);

    assert(ctx.decrypt(&gout531) == gout531clear);
    std::cerr << "\rLUT532   ";
    Ciphertext gin532 = 2 * gout3 + gout531;
    Ciphertext gout532 = ctx.eval_lut(&gin532, xor2);

    auto gin532clear = 2 * gout3clear + gout531clear;
    auto gout532clear = fxor2(gin532clear, 4);

    assert(ctx.decrypt(&gout532) == gout532clear);
    std::cerr << "\rLUT533   ";
    Ciphertext gin533 = 2 * (1 - gout298) + gout532;
    Ciphertext gout533 = ctx.eval_lut(&gin533, and2);

    auto gin533clear = 2 * (1 - gout298clear) + gout532clear;
    auto gout533clear = fand2(gin533clear, 4);

    assert(ctx.decrypt(&gout533) == gout533clear);
    std::cerr << "\rLUT534   ";
    Ciphertext gin534 = 2 * gout299 + gout533;
    Ciphertext gout534 = ctx.eval_lut(&gin534, or2);

    auto gin534clear = 2 * gout299clear + gout533clear;
    auto gout534clear = for2(gin534clear, 4);

    assert(ctx.decrypt(&gout534) == gout534clear);
    std::cerr << "\rLUT535   ";
    Ciphertext gin535 = 2 * gout534 + gout404;
    Ciphertext gout535 = ctx.eval_lut(&gin535, xnor2);

    auto gin535clear = 2 * gout534clear + gout404clear;
    auto gout535clear = fxnor2(gin535clear, 4);

    assert(ctx.decrypt(&gout535) == gout535clear);
    std::cerr << "\rLUT536   ";
    Ciphertext gin536 = 2 * gout534 + gout404;
    Ciphertext gout536 = ctx.eval_lut(&gin536, and2);

    auto gin536clear = 2 * gout534clear + gout404clear;
    auto gout536clear = fand2(gin536clear, 4);

    assert(ctx.decrypt(&gout536) == gout536clear);
    std::cerr << "\rLUT537   ";
    Ciphertext gin537 = 2 * gout3 + gout531;
    Ciphertext gout537 = ctx.eval_lut(&gin537, nand2);

    auto gin537clear = 2 * gout3clear + gout531clear;
    auto gout537clear = fnand2(gin537clear, 4);

    assert(ctx.decrypt(&gout537) == gout537clear);
    std::cerr << "\rLUT538   ";
    Ciphertext gin538 = 2 * gout530 + gout253;
    Ciphertext gout538 = ctx.eval_lut(&gin538, nand2);

    auto gin538clear = 2 * gout530clear + gout253clear;
    auto gout538clear = fnand2(gin538clear, 4);

    assert(ctx.decrypt(&gout538) == gout538clear);
    std::cerr << "\rLUT539   ";
    Ciphertext gin539 = 2 * gout538 + gout537;
    Ciphertext gout539 = ctx.eval_lut(&gin539, nand2);

    auto gin539clear = 2 * gout538clear + gout537clear;
    auto gout539clear = fnand2(gin539clear, 4);

    assert(ctx.decrypt(&gout539) == gout539clear);
    std::cerr << "\rLUT540   ";
    Ciphertext gin540 = 2 * gout539 + gout359;
    Ciphertext gout540 = ctx.eval_lut(&gin540, xor2);

    auto gin540clear = 2 * gout539clear + gout359clear;
    auto gout540clear = fxor2(gin540clear, 4);

    assert(ctx.decrypt(&gout540) == gout540clear);
    std::cerr << "\rLUT541   ";
    Ciphertext gin541 = 2 * gout243 + gout540;
    Ciphertext gout541 = ctx.eval_lut(&gin541, xor2);

    auto gin541clear = 2 * gout243clear + gout540clear;
    auto gout541clear = fxor2(gin541clear, 4);

    assert(ctx.decrypt(&gout541) == gout541clear);
    std::cerr << "\rLUT542   ";
    Ciphertext gin542 = 2 * gout535 + gout541;
    Ciphertext gout542 = ctx.eval_lut(&gin542, xnor2);

    auto gin542clear = 2 * gout535clear + gout541clear;
    auto gout542clear = fxnor2(gin542clear, 4);

    assert(ctx.decrypt(&gout542) == gout542clear);
    std::cerr << "\rLUT543   ";
    Ciphertext gin543 = 2 * (1 - gout535) + gout541;
    Ciphertext gout543 = ctx.eval_lut(&gin543, and2);

    auto gin543clear = 2 * (1 - gout535clear) + gout541clear;
    auto gout543clear = fand2(gin543clear, 4);

    assert(ctx.decrypt(&gout543) == gout543clear);
    std::cerr << "\rLUT544   ";
    Ciphertext gin544 = 2 * gout536 + gout543;
    Ciphertext gout544 = ctx.eval_lut(&gin544, or2);

    auto gin544clear = 2 * gout536clear + gout543clear;
    auto gout544clear = for2(gin544clear, 4);

    assert(ctx.decrypt(&gout544) == gout544clear);
    std::cerr << "\rLUT545   ";
    Ciphertext gin545 = 2 * gout544 + gout414;
    Ciphertext gout545 = ctx.eval_lut(&gin545, xnor2);

    auto gin545clear = 2 * gout544clear + gout414clear;
    auto gout545clear = fxnor2(gin545clear, 4);

    assert(ctx.decrypt(&gout545) == gout545clear);
    std::cerr << "\rLUT546   ";
    Ciphertext gin546 = 2 * gout544 + gout414;
    Ciphertext gout546 = ctx.eval_lut(&gin546, and2);

    auto gin546clear = 2 * gout544clear + gout414clear;
    auto gout546clear = fand2(gin546clear, 4);

    assert(ctx.decrypt(&gout546) == gout546clear);
    std::cerr << "\rLUT547   ";
    Ciphertext gin547 = 2 * gout243 + gout540;
    Ciphertext gout547 = ctx.eval_lut(&gin547, nand2);

    auto gin547clear = 2 * gout243clear + gout540clear;
    auto gout547clear = fnand2(gin547clear, 4);

    assert(ctx.decrypt(&gout547) == gout547clear);
    std::cerr << "\rLUT548   ";
    Ciphertext gin548 = 2 * gout539 + gout359;
    Ciphertext gout548 = ctx.eval_lut(&gin548, nand2);

    auto gin548clear = 2 * gout539clear + gout359clear;
    auto gout548clear = fnand2(gin548clear, 4);

    assert(ctx.decrypt(&gout548) == gout548clear);
    std::cerr << "\rLUT549   ";
    Ciphertext gin549 = 2 * gout548 + gout547;
    Ciphertext gout549 = ctx.eval_lut(&gin549, nand2);

    auto gin549clear = 2 * gout548clear + gout547clear;
    auto gout549clear = fnand2(gin549clear, 4);

    assert(ctx.decrypt(&gout549) == gout549clear);
    std::cerr << "\rLUT550   ";
    Ciphertext gin550 = 2 * gout308 + (1 - gout530);
    Ciphertext gout550 = ctx.eval_lut(&gin550, or2);

    auto gin550clear = 2 * gout308clear + (1 - gout530clear);
    auto gout550clear = for2(gin550clear, 4);

    assert(ctx.decrypt(&gout550) == gout550clear);
    std::cerr << "\rLUT551   ";
    Ciphertext gin551 = 2 * gout550 + gout133;
    Ciphertext gout551 = ctx.eval_lut(&gin551, nand2);

    auto gin551clear = 2 * gout550clear + gout133clear;
    auto gout551clear = fnand2(gin551clear, 4);

    assert(ctx.decrypt(&gout551) == gout551clear);
    std::cerr << "\rLUT552   ";
    Ciphertext gin552 = 2 * gout551 + gout235;
    Ciphertext gout552 = ctx.eval_lut(&gin552, xor2);

    auto gin552clear = 2 * gout551clear + gout235clear;
    auto gout552clear = fxor2(gin552clear, 4);

    assert(ctx.decrypt(&gout552) == gout552clear);
    std::cerr << "\rLUT553   ";
    Ciphertext gin553 = 2 * gout344 + gout552;
    Ciphertext gout553 = ctx.eval_lut(&gin553, xor2);

    auto gin553clear = 2 * gout344clear + gout552clear;
    auto gout553clear = fxor2(gin553clear, 4);

    assert(ctx.decrypt(&gout553) == gout553clear);
    std::cerr << "\rLUT554   ";
    Ciphertext gin554 = 2 * gout551 + gout235;
    Ciphertext gout554 = ctx.eval_lut(&gin554, nand2);

    auto gin554clear = 2 * gout551clear + gout235clear;
    auto gout554clear = fnand2(gin554clear, 4);

    assert(ctx.decrypt(&gout554) == gout554clear);
    std::cerr << "\rLUT555   ";
    Ciphertext gin555 = 2 * ct_y0 + ct_x5;
    Ciphertext gout555 = ctx.eval_lut(&gin555, nand2);

    auto gin555clear = 2 * ct_y0clear + ct_x5clear;
    auto gout555clear = fnand2(gin555clear, 4);

    assert(ctx.decrypt(&gout555) == gout555clear);
    std::cerr << "\rLUT556   ";
    Ciphertext gin556 = 2 * gout555 + (1 - gout202);
    Ciphertext gout556 = ctx.eval_lut(&gin556, or2);

    auto gin556clear = 2 * gout555clear + (1 - gout202clear);
    auto gout556clear = for2(gin556clear, 4);

    assert(ctx.decrypt(&gout556) == gout556clear);
    std::cerr << "\rLUT557   ";
    Ciphertext gin557 = 2 * gout556 + gout120;
    Ciphertext gout557 = ctx.eval_lut(&gin557, nand2);

    auto gin557clear = 2 * gout556clear + gout120clear;
    auto gout557clear = fnand2(gin557clear, 4);

    assert(ctx.decrypt(&gout557) == gout557clear);
    std::cerr << "\rLUT558   ";
    Ciphertext gin558 = 2 * gout557 + gout305;
    Ciphertext gout558 = ctx.eval_lut(&gin558, xor2);

    auto gin558clear = 2 * gout557clear + gout305clear;
    auto gout558clear = fxor2(gin558clear, 4);

    assert(ctx.decrypt(&gout558) == gout558clear);
    std::cerr << "\rLUT559   ";
    Ciphertext gin559 = 2 * gout280 + gout558;
    Ciphertext gout559 = ctx.eval_lut(&gin559, xor2);

    auto gin559clear = 2 * gout280clear + gout558clear;
    auto gout559clear = fxor2(gin559clear, 4);

    assert(ctx.decrypt(&gout559) == gout559clear);
    std::cerr << "\rLUT560   ";
    Ciphertext gin560 = 2 * gout280 + gout558;
    Ciphertext gout560 = ctx.eval_lut(&gin560, nand2);

    auto gin560clear = 2 * gout280clear + gout558clear;
    auto gout560clear = fnand2(gin560clear, 4);

    assert(ctx.decrypt(&gout560) == gout560clear);
    std::cerr << "\rLUT561   ";
    Ciphertext gin561 = 2 * gout557 + gout305;
    Ciphertext gout561 = ctx.eval_lut(&gin561, nand2);

    auto gin561clear = 2 * gout557clear + gout305clear;
    auto gout561clear = fnand2(gin561clear, 4);

    assert(ctx.decrypt(&gout561) == gout561clear);
    std::cerr << "\rLUT562   ";
    Ciphertext gin562 = 2 * gout561 + gout560;
    Ciphertext gout562 = ctx.eval_lut(&gin562, nand2);

    auto gin562clear = 2 * gout561clear + gout560clear;
    auto gout562clear = fnand2(gin562clear, 4);

    assert(ctx.decrypt(&gout562) == gout562clear);
    std::cerr << "\rLUT563   ";
    Ciphertext gin563 = 2 * gout562 + gout290;
    Ciphertext gout563 = ctx.eval_lut(&gin563, xor2);

    auto gin563clear = 2 * gout562clear + gout290clear;
    auto gout563clear = fxor2(gin563clear, 4);

    assert(ctx.decrypt(&gout563) == gout563clear);
    std::cerr << "\rLUT564   ";
    Ciphertext gin564 = 2 * gout562 + gout290;
    Ciphertext gout564 = ctx.eval_lut(&gin564, and2);

    auto gin564clear = 2 * gout562clear + gout290clear;
    auto gout564clear = fand2(gin564clear, 4);

    assert(ctx.decrypt(&gout564) == gout564clear);
    std::cerr << "\rLUT565   ";
    Ciphertext gin565 = 2 * gout555 + gout55;
    Ciphertext gout565 = ctx.eval_lut(&gin565, xnor2);

    auto gin565clear = 2 * gout555clear + gout55clear;
    auto gout565clear = fxnor2(gin565clear, 4);

    assert(ctx.decrypt(&gout565) == gout565clear);
    std::cerr << "\rLUT566   ";
    Ciphertext gin566 = 2 * gout135 + gout565;
    Ciphertext gout566 = ctx.eval_lut(&gin566, xor2);

    auto gin566clear = 2 * gout135clear + gout565clear;
    auto gout566clear = fxor2(gin566clear, 4);

    assert(ctx.decrypt(&gout566) == gout566clear);
    std::cerr << "\rLUT567   ";
    Ciphertext gin567 = 2 * gout190 + gout566;
    Ciphertext gout567 = ctx.eval_lut(&gin567, xnor2);

    auto gin567clear = 2 * gout190clear + gout566clear;
    auto gout567clear = fxnor2(gin567clear, 4);

    assert(ctx.decrypt(&gout567) == gout567clear);
    std::cerr << "\rLUT568   ";
    Ciphertext gin568 = 2 * gout522 + gout567;
    Ciphertext gout568 = ctx.eval_lut(&gin568, xor2);

    auto gin568clear = 2 * gout522clear + gout567clear;
    auto gout568clear = fxor2(gin568clear, 4);

    assert(ctx.decrypt(&gout568) == gout568clear);
    std::cerr << "\rLUT569   ";
    Ciphertext gin569 = 2 * gout256 + gout568;
    Ciphertext gout569 = ctx.eval_lut(&gin569, xnor2);

    auto gin569clear = 2 * gout256clear + gout568clear;
    auto gout569clear = fxnor2(gin569clear, 4);

    assert(ctx.decrypt(&gout569) == gout569clear);
    std::cerr << "\rLUT570   ";
    Ciphertext gin570 = 2 * gout569 + gout519;
    Ciphertext gout570 = ctx.eval_lut(&gin570, xor2);

    auto gin570clear = 2 * gout569clear + gout519clear;
    auto gout570clear = fxor2(gin570clear, 4);

    assert(ctx.decrypt(&gout570) == gout570clear);
    std::cerr << "\rLUT571   ";
    Ciphertext gin571 = 2 * gout517 + gout569;
    Ciphertext gout571 = ctx.eval_lut(&gin571, and2);

    auto gin571clear = 2 * gout517clear + gout569clear;
    auto gout571clear = fand2(gin571clear, 4);

    assert(ctx.decrypt(&gout571) == gout571clear);
    std::cerr << "\rINV572   ";
    Ciphertext gout572 = 1 - gout571;

    long gout572clear = 1 - gout571clear;

    assert(ctx.decrypt(&gout572) == gout572clear);
    std::cerr << "\rLUT573   ";
    Ciphertext gin573 = 2 * gout518 + gout569;
    Ciphertext gout573 = ctx.eval_lut(&gin573, and2);

    auto gin573clear = 2 * gout518clear + gout569clear;
    auto gout573clear = fand2(gin573clear, 4);

    assert(ctx.decrypt(&gout573) == gout573clear);
    std::cerr << "\rINV574   ";
    Ciphertext gout574 = 1 - gout573;

    long gout574clear = 1 - gout573clear;

    assert(ctx.decrypt(&gout574) == gout574clear);
    std::cerr << "\rLUT575   ";
    Ciphertext gin575 = 2 * gout255 + gout568;
    Ciphertext gout575 = ctx.eval_lut(&gin575, nand2);

    auto gin575clear = 2 * gout255clear + gout568clear;
    auto gout575clear = fnand2(gin575clear, 4);

    assert(ctx.decrypt(&gout575) == gout575clear);
    std::cerr << "\rLUT576   ";
    Ciphertext gin576 = 2 * gout522 + gout567;
    Ciphertext gout576 = ctx.eval_lut(&gin576, nand2);

    auto gin576clear = 2 * gout522clear + gout567clear;
    auto gout576clear = fnand2(gin576clear, 4);

    assert(ctx.decrypt(&gout576) == gout576clear);
    std::cerr << "\rLUT577   ";
    Ciphertext gin577 = 2 * gout576 + gout575;
    Ciphertext gout577 = ctx.eval_lut(&gin577, nand2);

    auto gin577clear = 2 * gout576clear + gout575clear;
    auto gout577clear = fnand2(gin577clear, 4);

    assert(ctx.decrypt(&gout577) == gout577clear);
    std::cerr << "\rLUT578   ";
    Ciphertext gin578 = 2 * (1 - gout190) + gout566;
    Ciphertext gout578 = ctx.eval_lut(&gin578, and2);

    auto gin578clear = 2 * (1 - gout190clear) + gout566clear;
    auto gout578clear = fand2(gin578clear, 4);

    assert(ctx.decrypt(&gout578) == gout578clear);
    std::cerr << "\rLUT579   ";
    Ciphertext gin579 = 2 * gout191 + gout578;
    Ciphertext gout579 = ctx.eval_lut(&gin579, or2);

    auto gin579clear = 2 * gout191clear + gout578clear;
    auto gout579clear = for2(gin579clear, 4);

    assert(ctx.decrypt(&gout579) == gout579clear);
    std::cerr << "\rLUT580   ";
    Ciphertext gin580 = 2 * gout135 + gout565;
    Ciphertext gout580 = ctx.eval_lut(&gin580, nand2);

    auto gin580clear = 2 * gout135clear + gout565clear;
    auto gout580clear = fnand2(gin580clear, 4);

    assert(ctx.decrypt(&gout580) == gout580clear);
    std::cerr << "\rLUT581   ";
    Ciphertext gin581 = 2 * gout204 + gout580;
    Ciphertext gout581 = ctx.eval_lut(&gin581, nand2);

    auto gin581clear = 2 * gout204clear + gout580clear;
    auto gout581clear = fnand2(gin581clear, 4);

    assert(ctx.decrypt(&gout581) == gout581clear);
    std::cerr << "\rLUT582   ";
    Ciphertext gin582 = 2 * gout581 + gout244;
    Ciphertext gout582 = ctx.eval_lut(&gin582, xor2);

    auto gin582clear = 2 * gout581clear + gout244clear;
    auto gout582clear = fxor2(gin582clear, 4);

    assert(ctx.decrypt(&gout582) == gout582clear);
    std::cerr << "\rLUT583   ";
    Ciphertext gin583 = 2 * gout581 + gout244;
    Ciphertext gout583 = ctx.eval_lut(&gin583, and2);

    auto gin583clear = 2 * gout581clear + gout244clear;
    auto gout583clear = fand2(gin583clear, 4);

    assert(ctx.decrypt(&gout583) == gout583clear);
    std::cerr << "\rLUT584   ";
    Ciphertext gin584 = 2 * gout257 + gout281;
    Ciphertext gout584 = ctx.eval_lut(&gin584, and2);

    auto gin584clear = 2 * gout257clear + gout281clear;
    auto gout584clear = fand2(gin584clear, 4);

    assert(ctx.decrypt(&gout584) == gout584clear);
    std::cerr << "\rLUT585   ";
    Ciphertext gin585 = 2 * gout584 + gout506;
    Ciphertext gout585 = ctx.eval_lut(&gin585, xnor2);

    auto gin585clear = 2 * gout584clear + gout506clear;
    auto gout585clear = fxnor2(gin585clear, 4);

    assert(ctx.decrypt(&gout585) == gout585clear);
    std::cerr << "\rIMUX586  ";
    Ciphertext gin586A = 2 * gout585 + gout104;
    Ciphertext gout586A = ctx.eval_lut(&gin586A, and2);
    Ciphertext gin586B = 2 * gout383 + (1 - gout104);
    Ciphertext gout586B = ctx.eval_lut(&gin586B, and2);
    Ciphertext gout586 = gout586A + gout586B;

    long gin586Aclear = 2 * gout585clear + gout104clear;
    long gout586Aclear = fand2(gin586Aclear, 4);
    long gin586Bclear = 2 * gout383clear + (1 - gout104clear);
    long gout586Bclear = fand2(gin586Bclear, 4);
    long gout586clear = gout586Aclear + gout586Bclear;

    assert(ctx.decrypt(&gout586) == gout586clear);
    std::cerr << "\rLUT587   ";
    Ciphertext gin587 = 2 * gout218 + gout586;
    Ciphertext gout587 = ctx.eval_lut(&gin587, nand2);

    auto gin587clear = 2 * gout218clear + gout586clear;
    auto gout587clear = fnand2(gin587clear, 4);

    assert(ctx.decrypt(&gout587) == gout587clear);
    std::cerr << "\rLUT588   ";
    Ciphertext gin588 = 2 * gout584 + gout506;
    Ciphertext gout588 = ctx.eval_lut(&gin588, nand2);

    auto gin588clear = 2 * gout584clear + gout506clear;
    auto gout588clear = fnand2(gin588clear, 4);

    assert(ctx.decrypt(&gout588) == gout588clear);
    std::cerr << "\rLUT589   ";
    Ciphertext gin589 = 2 * (1 - gout588) + gout516;
    Ciphertext gout589 = ctx.eval_lut(&gin589, and2);

    auto gin589clear = 2 * (1 - gout588clear) + gout516clear;
    auto gout589clear = fand2(gin589clear, 4);

    assert(ctx.decrypt(&gout589) == gout589clear);
    std::cerr << "\rLUT590   ";
    Ciphertext gin590 = 2 * gout589 + gout570;
    Ciphertext gout590 = ctx.eval_lut(&gin590, xnor2);

    auto gin590clear = 2 * gout589clear + gout570clear;
    auto gout590clear = fxnor2(gin590clear, 4);

    assert(ctx.decrypt(&gout590) == gout590clear);
    std::cerr << "\rLUT591   ";
    Ciphertext gin591 = 2 * gout589 + gout570;
    Ciphertext gout591 = ctx.eval_lut(&gin591, nand2);

    auto gin591clear = 2 * gout589clear + gout570clear;
    auto gout591clear = fnand2(gin591clear, 4);

    assert(ctx.decrypt(&gout591) == gout591clear);
    std::cerr << "\rINV592   ";
    Ciphertext gout592 = 1 - gout591;

    long gout592clear = 1 - gout591clear;

    assert(ctx.decrypt(&gout592) == gout592clear);
    std::cerr << "\rLUT593   ";
    Ciphertext gin593 = 2 * gout508 + gout588;
    Ciphertext gout593 = ctx.eval_lut(&gin593, nand2);

    auto gin593clear = 2 * gout508clear + gout588clear;
    auto gout593clear = fnand2(gin593clear, 4);

    assert(ctx.decrypt(&gout593) == gout593clear);
    std::cerr << "\rLUT594   ";
    Ciphertext gin594 = 2 * gout516 + gout593;
    Ciphertext gout594 = ctx.eval_lut(&gin594, xnor2);

    auto gin594clear = 2 * gout516clear + gout593clear;
    auto gout594clear = fxnor2(gin594clear, 4);

    assert(ctx.decrypt(&gout594) == gout594clear);
    std::cerr << "\rLUT595   ";
    Ciphertext gin595 = 2 * ct_y10 + ct_x3;
    Ciphertext gout595 = ctx.eval_lut(&gin595, and2);

    auto gin595clear = 2 * ct_y10clear + ct_x3clear;
    auto gout595clear = fand2(gin595clear, 4);

    assert(ctx.decrypt(&gout595) == gout595clear);
    std::cerr << "\rLUT596   ";
    Ciphertext gin596 = 2 * gout595 + gout265;
    Ciphertext gout596 = ctx.eval_lut(&gin596, xor2);

    auto gin596clear = 2 * gout595clear + gout265clear;
    auto gout596clear = fxor2(gin596clear, 4);

    assert(ctx.decrypt(&gout596) == gout596clear);
    std::cerr << "\rLUT597   ";
    Ciphertext gin597 = 2 * gout8 + gout596;
    Ciphertext gout597 = ctx.eval_lut(&gin597, xor2);

    auto gin597clear = 2 * gout8clear + gout596clear;
    auto gout597clear = fxor2(gin597clear, 4);

    assert(ctx.decrypt(&gout597) == gout597clear);
    std::cerr << "\rLUT598   ";
    Ciphertext gin598 = 2 * gout138 + gout597;
    Ciphertext gout598 = ctx.eval_lut(&gin598, xnor2);

    auto gin598clear = 2 * gout138clear + gout597clear;
    auto gout598clear = fxnor2(gin598clear, 4);

    assert(ctx.decrypt(&gout598) == gout598clear);
    std::cerr << "\rLUT599   ";
    Ciphertext gin599 = 2 * gout138 + gout597;
    Ciphertext gout599 = ctx.eval_lut(&gin599, and2);

    auto gin599clear = 2 * gout138clear + gout597clear;
    auto gout599clear = fand2(gin599clear, 4);

    assert(ctx.decrypt(&gout599) == gout599clear);
    std::cerr << "\rLUT600   ";
    Ciphertext gin600 = 2 * gout8 + gout596;
    Ciphertext gout600 = ctx.eval_lut(&gin600, nand2);

    auto gin600clear = 2 * gout8clear + gout596clear;
    auto gout600clear = fnand2(gin600clear, 4);

    assert(ctx.decrypt(&gout600) == gout600clear);
    std::cerr << "\rLUT601   ";
    Ciphertext gin601 = 2 * gout595 + gout265;
    Ciphertext gout601 = ctx.eval_lut(&gin601, nand2);

    auto gin601clear = 2 * gout595clear + gout265clear;
    auto gout601clear = fnand2(gin601clear, 4);

    assert(ctx.decrypt(&gout601) == gout601clear);
    std::cerr << "\rLUT602   ";
    Ciphertext gin602 = 2 * gout601 + gout600;
    Ciphertext gout602 = ctx.eval_lut(&gin602, nand2);

    auto gin602clear = 2 * gout601clear + gout600clear;
    auto gout602clear = fnand2(gin602clear, 4);

    assert(ctx.decrypt(&gout602) == gout602clear);
    std::cerr << "\rLUT603   ";
    Ciphertext gin603 = 2 * gout602 + gout287;
    Ciphertext gout603 = ctx.eval_lut(&gin603, xnor2);

    auto gin603clear = 2 * gout602clear + gout287clear;
    auto gout603clear = fxnor2(gin603clear, 4);

    assert(ctx.decrypt(&gout603) == gout603clear);
    std::cerr << "\rLUT604   ";
    Ciphertext gin604 = 2 * gout603 + gout273;
    Ciphertext gout604 = ctx.eval_lut(&gin604, xnor2);

    auto gin604clear = 2 * gout603clear + gout273clear;
    auto gout604clear = fxnor2(gin604clear, 4);

    assert(ctx.decrypt(&gout604) == gout604clear);
    std::cerr << "\rLUT605   ";
    Ciphertext gin605 = 2 * gout549 + gout604;
    Ciphertext gout605 = ctx.eval_lut(&gin605, xor2);

    auto gin605clear = 2 * gout549clear + gout604clear;
    auto gout605clear = fxor2(gin605clear, 4);

    assert(ctx.decrypt(&gout605) == gout605clear);
    std::cerr << "\rLUT606   ";
    Ciphertext gin606 = 2 * gout549 + gout604;
    Ciphertext gout606 = ctx.eval_lut(&gin606, nand2);

    auto gin606clear = 2 * gout549clear + gout604clear;
    auto gout606clear = fnand2(gin606clear, 4);

    assert(ctx.decrypt(&gout606) == gout606clear);
    std::cerr << "\rLUT607   ";
    Ciphertext gin607 = 2 * (1 - gout603) + gout273;
    Ciphertext gout607 = ctx.eval_lut(&gin607, and2);

    auto gin607clear = 2 * (1 - gout603clear) + gout273clear;
    auto gout607clear = fand2(gin607clear, 4);

    assert(ctx.decrypt(&gout607) == gout607clear);
    std::cerr << "\rLUT608   ";
    Ciphertext gin608 = 2 * gout602 + gout287;
    Ciphertext gout608 = ctx.eval_lut(&gin608, nand2);

    auto gin608clear = 2 * gout602clear + gout287clear;
    auto gout608clear = fnand2(gin608clear, 4);

    assert(ctx.decrypt(&gout608) == gout608clear);
    std::cerr << "\rLUT609   ";
    Ciphertext gin609 = 2 * gout608 + (1 - gout607);
    Ciphertext gout609 = ctx.eval_lut(&gin609, and2);

    auto gin609clear = 2 * gout608clear + (1 - gout607clear);
    auto gout609clear = fand2(gin609clear, 4);

    assert(ctx.decrypt(&gout609) == gout609clear);
    std::cerr << "\rLUT610   ";
    Ciphertext gin610 = 2 * gout420 + gout609;
    Ciphertext gout610 = ctx.eval_lut(&gin610, xnor2);

    auto gin610clear = 2 * gout420clear + gout609clear;
    auto gout610clear = fxnor2(gin610clear, 4);

    assert(ctx.decrypt(&gout610) == gout610clear);
    std::cerr << "\rLUT611   ";
    Ciphertext gin611 = 2 * gout610 + gout375;
    Ciphertext gout611 = ctx.eval_lut(&gin611, xnor2);

    auto gin611clear = 2 * gout610clear + gout375clear;
    auto gout611clear = fxnor2(gin611clear, 4);

    assert(ctx.decrypt(&gout611) == gout611clear);
    std::cerr << "\rLUT612   ";
    Ciphertext gin612 = 2 * gout416 + gout611;
    Ciphertext gout612 = ctx.eval_lut(&gin612, xnor2);

    auto gin612clear = 2 * gout416clear + gout611clear;
    auto gout612clear = fxnor2(gin612clear, 4);

    assert(ctx.decrypt(&gout612) == gout612clear);
    std::cerr << "\rLUT613   ";
    Ciphertext gin613 = 2 * gout344 + gout552;
    Ciphertext gout613 = ctx.eval_lut(&gin613, nand2);

    auto gin613clear = 2 * gout344clear + gout552clear;
    auto gout613clear = fnand2(gin613clear, 4);

    assert(ctx.decrypt(&gout613) == gout613clear);
    std::cerr << "\rLUT614   ";
    Ciphertext gin614 = 2 * gout554 + gout613;
    Ciphertext gout614 = ctx.eval_lut(&gin614, nand2);

    auto gin614clear = 2 * gout554clear + gout613clear;
    auto gout614clear = fnand2(gin614clear, 4);

    assert(ctx.decrypt(&gout614) == gout614clear);
    std::cerr << "\rLUT615   ";
    Ciphertext gin615 = 2 * gout614 + gout165;
    Ciphertext gout615 = ctx.eval_lut(&gin615, xor2);

    auto gin615clear = 2 * gout614clear + gout165clear;
    auto gout615clear = fxor2(gin615clear, 4);

    assert(ctx.decrypt(&gout615) == gout615clear);
    std::cerr << "\rLUT616   ";
    Ciphertext gin616 = 2 * gout614 + gout165;
    Ciphertext gout616 = ctx.eval_lut(&gin616, and2);

    auto gin616clear = 2 * gout614clear + gout165clear;
    auto gout616clear = fand2(gin616clear, 4);

    assert(ctx.decrypt(&gout616) == gout616clear);
    std::cerr << "\rLUT617   ";
    Ciphertext gin617 = 2 * ct_y3 + ct_x6;
    Ciphertext gout617 = ctx.eval_lut(&gin617, and2);

    auto gin617clear = 2 * ct_y3clear + ct_x6clear;
    auto gout617clear = fand2(gin617clear, 4);

    assert(ctx.decrypt(&gout617) == gout617clear);
    std::cerr << "\rLUT618   ";
    Ciphertext gin618 = 2 * gout617 + gout376;
    Ciphertext gout618 = ctx.eval_lut(&gin618, xor2);

    auto gin618clear = 2 * gout617clear + gout376clear;
    auto gout618clear = fxor2(gin618clear, 4);

    assert(ctx.decrypt(&gout618) == gout618clear);
    std::cerr << "\rLUT619   ";
    Ciphertext gin619 = 2 * gout126 + gout618;
    Ciphertext gout619 = ctx.eval_lut(&gin619, xor2);

    auto gin619clear = 2 * gout126clear + gout618clear;
    auto gout619clear = fxor2(gin619clear, 4);

    assert(ctx.decrypt(&gout619) == gout619clear);
    std::cerr << "\rLUT620   ";
    Ciphertext gin620 = 2 * gout114 + gout619;
    Ciphertext gout620 = ctx.eval_lut(&gin620, xnor2);

    auto gin620clear = 2 * gout114clear + gout619clear;
    auto gout620clear = fxnor2(gin620clear, 4);

    assert(ctx.decrypt(&gout620) == gout620clear);
    std::cerr << "\rLUT621   ";
    Ciphertext gin621 = 2 * gout620 + gout119;
    Ciphertext gout621 = ctx.eval_lut(&gin621, xnor2);

    auto gin621clear = 2 * gout620clear + gout119clear;
    auto gout621clear = fxnor2(gin621clear, 4);

    assert(ctx.decrypt(&gout621) == gout621clear);
    std::cerr << "\rLUT622   ";
    Ciphertext gin622 = 2 * gout400 + gout621;
    Ciphertext gout622 = ctx.eval_lut(&gin622, xnor2);

    auto gin622clear = 2 * gout400clear + gout621clear;
    auto gout622clear = fxnor2(gin622clear, 4);

    assert(ctx.decrypt(&gout622) == gout622clear);
    std::cerr << "\rLUT623   ";
    Ciphertext gin623 = 2 * gout622 + gout553;
    Ciphertext gout623 = ctx.eval_lut(&gin623, xnor2);

    auto gin623clear = 2 * gout622clear + gout553clear;
    auto gout623clear = fxnor2(gin623clear, 4);

    assert(ctx.decrypt(&gout623) == gout623clear);
    std::cerr << "\rLUT624   ";
    Ciphertext gin624 = 2 * (1 - gout622) + gout553;
    Ciphertext gout624 = ctx.eval_lut(&gin624, and2);

    auto gin624clear = 2 * (1 - gout622clear) + gout553clear;
    auto gout624clear = fand2(gin624clear, 4);

    assert(ctx.decrypt(&gout624) == gout624clear);
    std::cerr << "\rLUT625   ";
    Ciphertext gin625 = 2 * gout400 + gout621;
    Ciphertext gout625 = ctx.eval_lut(&gin625, and2);

    auto gin625clear = 2 * gout400clear + gout621clear;
    auto gout625clear = fand2(gin625clear, 4);

    assert(ctx.decrypt(&gout625) == gout625clear);
    std::cerr << "\rLUT626   ";
    Ciphertext gin626 = 2 * gout625 + gout624;
    Ciphertext gout626 = ctx.eval_lut(&gin626, or2);

    auto gin626clear = 2 * gout625clear + gout624clear;
    auto gout626clear = for2(gin626clear, 4);

    assert(ctx.decrypt(&gout626) == gout626clear);
    std::cerr << "\rLUT627   ";
    Ciphertext gin627 = 2 * (1 - gout620) + gout119;
    Ciphertext gout627 = ctx.eval_lut(&gin627, and2);

    auto gin627clear = 2 * (1 - gout620clear) + gout119clear;
    auto gout627clear = fand2(gin627clear, 4);

    assert(ctx.decrypt(&gout627) == gout627clear);
    std::cerr << "\rLUT628   ";
    Ciphertext gin628 = 2 * gout114 + gout619;
    Ciphertext gout628 = ctx.eval_lut(&gin628, and2);

    auto gin628clear = 2 * gout114clear + gout619clear;
    auto gout628clear = fand2(gin628clear, 4);

    assert(ctx.decrypt(&gout628) == gout628clear);
    std::cerr << "\rLUT629   ";
    Ciphertext gin629 = 2 * gout628 + gout627;
    Ciphertext gout629 = ctx.eval_lut(&gin629, or2);

    auto gin629clear = 2 * gout628clear + gout627clear;
    auto gout629clear = for2(gin629clear, 4);

    assert(ctx.decrypt(&gout629) == gout629clear);
    std::cerr << "\rLUT630   ";
    Ciphertext gin630 = 2 * gout126 + gout618;
    Ciphertext gout630 = ctx.eval_lut(&gin630, nand2);

    auto gin630clear = 2 * gout126clear + gout618clear;
    auto gout630clear = fnand2(gin630clear, 4);

    assert(ctx.decrypt(&gout630) == gout630clear);
    std::cerr << "\rLUT631   ";
    Ciphertext gin631 = 2 * gout617 + gout376;
    Ciphertext gout631 = ctx.eval_lut(&gin631, nand2);

    auto gin631clear = 2 * gout617clear + gout376clear;
    auto gout631clear = fnand2(gin631clear, 4);

    assert(ctx.decrypt(&gout631) == gout631clear);
    std::cerr << "\rLUT632   ";
    Ciphertext gin632 = 2 * gout631 + gout630;
    Ciphertext gout632 = ctx.eval_lut(&gin632, nand2);

    auto gin632clear = 2 * gout631clear + gout630clear;
    auto gout632clear = fnand2(gin632clear, 4);

    assert(ctx.decrypt(&gout632) == gout632clear);
    std::cerr << "\rLUT633   ";
    Ciphertext gin633 = 2 * gout632 + gout425;
    Ciphertext gout633 = ctx.eval_lut(&gin633, xnor2);

    auto gin633clear = 2 * gout632clear + gout425clear;
    auto gout633clear = fxnor2(gin633clear, 4);

    assert(ctx.decrypt(&gout633) == gout633clear);
    std::cerr << "\rLUT634   ";
    Ciphertext gin634 = 2 * gout633 + gout270;
    Ciphertext gout634 = ctx.eval_lut(&gin634, xnor2);

    auto gin634clear = 2 * gout633clear + gout270clear;
    auto gout634clear = fxnor2(gin634clear, 4);

    assert(ctx.decrypt(&gout634) == gout634clear);
    std::cerr << "\rLUT635   ";
    Ciphertext gin635 = 2 * gout629 + gout634;
    Ciphertext gout635 = ctx.eval_lut(&gin635, xnor2);

    auto gin635clear = 2 * gout629clear + gout634clear;
    auto gout635clear = fxnor2(gin635clear, 4);

    assert(ctx.decrypt(&gout635) == gout635clear);
    std::cerr << "\rLUT636   ";
    Ciphertext gin636 = 2 * gout635 + gout559;
    Ciphertext gout636 = ctx.eval_lut(&gin636, xnor2);

    auto gin636clear = 2 * gout635clear + gout559clear;
    auto gout636clear = fxnor2(gin636clear, 4);

    assert(ctx.decrypt(&gout636) == gout636clear);
    std::cerr << "\rLUT637   ";
    Ciphertext gin637 = 2 * gout626 + gout636;
    Ciphertext gout637 = ctx.eval_lut(&gin637, xnor2);

    auto gin637clear = 2 * gout626clear + gout636clear;
    auto gout637clear = fxnor2(gin637clear, 4);

    assert(ctx.decrypt(&gout637) == gout637clear);
    std::cerr << "\rLUT638   ";
    Ciphertext gin638 = 2 * gout637 + gout615;
    Ciphertext gout638 = ctx.eval_lut(&gin638, xnor2);

    auto gin638clear = 2 * gout637clear + gout615clear;
    auto gout638clear = fxnor2(gin638clear, 4);

    assert(ctx.decrypt(&gout638) == gout638clear);
    std::cerr << "\rLUT639   ";
    Ciphertext gin639 = 2 * (1 - gout637) + gout615;
    Ciphertext gout639 = ctx.eval_lut(&gin639, and2);

    auto gin639clear = 2 * (1 - gout637clear) + gout615clear;
    auto gout639clear = fand2(gin639clear, 4);

    assert(ctx.decrypt(&gout639) == gout639clear);
    std::cerr << "\rLUT640   ";
    Ciphertext gin640 = 2 * gout626 + gout636;
    Ciphertext gout640 = ctx.eval_lut(&gin640, and2);

    auto gin640clear = 2 * gout626clear + gout636clear;
    auto gout640clear = fand2(gin640clear, 4);

    assert(ctx.decrypt(&gout640) == gout640clear);
    std::cerr << "\rLUT641   ";
    Ciphertext gin641 = 2 * gout640 + gout639;
    Ciphertext gout641 = ctx.eval_lut(&gin641, or2);

    auto gin641clear = 2 * gout640clear + gout639clear;
    auto gout641clear = for2(gin641clear, 4);

    assert(ctx.decrypt(&gout641) == gout641clear);
    std::cerr << "\rLUT642   ";
    Ciphertext gin642 = 2 * (1 - gout635) + gout559;
    Ciphertext gout642 = ctx.eval_lut(&gin642, and2);

    auto gin642clear = 2 * (1 - gout635clear) + gout559clear;
    auto gout642clear = fand2(gin642clear, 4);

    assert(ctx.decrypt(&gout642) == gout642clear);
    std::cerr << "\rLUT643   ";
    Ciphertext gin643 = 2 * gout629 + gout634;
    Ciphertext gout643 = ctx.eval_lut(&gin643, and2);

    auto gin643clear = 2 * gout629clear + gout634clear;
    auto gout643clear = fand2(gin643clear, 4);

    assert(ctx.decrypt(&gout643) == gout643clear);
    std::cerr << "\rLUT644   ";
    Ciphertext gin644 = 2 * gout643 + gout642;
    Ciphertext gout644 = ctx.eval_lut(&gin644, or2);

    auto gin644clear = 2 * gout643clear + gout642clear;
    auto gout644clear = for2(gin644clear, 4);

    assert(ctx.decrypt(&gout644) == gout644clear);
    std::cerr << "\rLUT645   ";
    Ciphertext gin645 = 2 * (1 - gout633) + gout270;
    Ciphertext gout645 = ctx.eval_lut(&gin645, and2);

    auto gin645clear = 2 * (1 - gout633clear) + gout270clear;
    auto gout645clear = fand2(gin645clear, 4);

    assert(ctx.decrypt(&gout645) == gout645clear);
    std::cerr << "\rLUT646   ";
    Ciphertext gin646 = 2 * gout632 + gout425;
    Ciphertext gout646 = ctx.eval_lut(&gin646, and2);

    auto gin646clear = 2 * gout632clear + gout425clear;
    auto gout646clear = fand2(gin646clear, 4);

    assert(ctx.decrypt(&gout646) == gout646clear);
    std::cerr << "\rLUT647   ";
    Ciphertext gin647 = 2 * gout646 + gout645;
    Ciphertext gout647 = ctx.eval_lut(&gin647, or2);

    auto gin647clear = 2 * gout646clear + gout645clear;
    auto gout647clear = for2(gin647clear, 4);

    assert(ctx.decrypt(&gout647) == gout647clear);
    std::cerr << "\rLUT648   ";
    Ciphertext gin648 = 2 * gout647 + gout429;
    Ciphertext gout648 = ctx.eval_lut(&gin648, xnor2);

    auto gin648clear = 2 * gout647clear + gout429clear;
    auto gout648clear = fxnor2(gin648clear, 4);

    assert(ctx.decrypt(&gout648) == gout648clear);
    std::cerr << "\rLUT649   ";
    Ciphertext gin649 = 2 * gout648 + gout423;
    Ciphertext gout649 = ctx.eval_lut(&gin649, xnor2);

    auto gin649clear = 2 * gout648clear + gout423clear;
    auto gout649clear = fxnor2(gin649clear, 4);

    assert(ctx.decrypt(&gout649) == gout649clear);
    std::cerr << "\rLUT650   ";
    Ciphertext gin650 = 2 * gout644 + gout649;
    Ciphertext gout650 = ctx.eval_lut(&gin650, xnor2);

    auto gin650clear = 2 * gout644clear + gout649clear;
    auto gout650clear = fxnor2(gin650clear, 4);

    assert(ctx.decrypt(&gout650) == gout650clear);
    std::cerr << "\rLUT651   ";
    Ciphertext gin651 = 2 * gout650 + gout563;
    Ciphertext gout651 = ctx.eval_lut(&gin651, xnor2);

    auto gin651clear = 2 * gout650clear + gout563clear;
    auto gout651clear = fxnor2(gin651clear, 4);

    assert(ctx.decrypt(&gout651) == gout651clear);
    std::cerr << "\rLUT652   ";
    Ciphertext gin652 = 2 * gout641 + gout651;
    Ciphertext gout652 = ctx.eval_lut(&gin652, xor2);

    auto gin652clear = 2 * gout641clear + gout651clear;
    auto gout652clear = fxor2(gin652clear, 4);

    assert(ctx.decrypt(&gout652) == gout652clear);
    std::cerr << "\rLUT653   ";
    Ciphertext gin653 = 2 * gout616 + gout652;
    Ciphertext gout653 = ctx.eval_lut(&gin653, xor2);

    auto gin653clear = 2 * gout616clear + gout652clear;
    auto gout653clear = fxor2(gin653clear, 4);

    assert(ctx.decrypt(&gout653) == gout653clear);
    std::cerr << "\rLUT654   ";
    Ciphertext gin654 = 2 * gout616 + gout652;
    Ciphertext gout654 = ctx.eval_lut(&gin654, nand2);

    auto gin654clear = 2 * gout616clear + gout652clear;
    auto gout654clear = fnand2(gin654clear, 4);

    assert(ctx.decrypt(&gout654) == gout654clear);
    std::cerr << "\rLUT655   ";
    Ciphertext gin655 = 2 * gout641 + gout651;
    Ciphertext gout655 = ctx.eval_lut(&gin655, nand2);

    auto gin655clear = 2 * gout641clear + gout651clear;
    auto gout655clear = fnand2(gin655clear, 4);

    assert(ctx.decrypt(&gout655) == gout655clear);
    std::cerr << "\rLUT656   ";
    Ciphertext gin656 = 2 * gout655 + gout654;
    Ciphertext gout656 = ctx.eval_lut(&gin656, nand2);

    auto gin656clear = 2 * gout655clear + gout654clear;
    auto gout656clear = fnand2(gin656clear, 4);

    assert(ctx.decrypt(&gout656) == gout656clear);
    std::cerr << "\rLUT657   ";
    Ciphertext gin657 = 2 * (1 - gout650) + gout563;
    Ciphertext gout657 = ctx.eval_lut(&gin657, and2);

    auto gin657clear = 2 * (1 - gout650clear) + gout563clear;
    auto gout657clear = fand2(gin657clear, 4);

    assert(ctx.decrypt(&gout657) == gout657clear);
    std::cerr << "\rLUT658   ";
    Ciphertext gin658 = 2 * gout644 + gout649;
    Ciphertext gout658 = ctx.eval_lut(&gin658, and2);

    auto gin658clear = 2 * gout644clear + gout649clear;
    auto gout658clear = fand2(gin658clear, 4);

    assert(ctx.decrypt(&gout658) == gout658clear);
    std::cerr << "\rLUT659   ";
    Ciphertext gin659 = 2 * gout658 + gout657;
    Ciphertext gout659 = ctx.eval_lut(&gin659, or2);

    auto gin659clear = 2 * gout658clear + gout657clear;
    auto gout659clear = for2(gin659clear, 4);

    assert(ctx.decrypt(&gout659) == gout659clear);
    std::cerr << "\rLUT660   ";
    Ciphertext gin660 = 2 * (1 - gout648) + gout423;
    Ciphertext gout660 = ctx.eval_lut(&gin660, and2);

    auto gin660clear = 2 * (1 - gout648clear) + gout423clear;
    auto gout660clear = fand2(gin660clear, 4);

    assert(ctx.decrypt(&gout660) == gout660clear);
    std::cerr << "\rLUT661   ";
    Ciphertext gin661 = 2 * gout647 + gout429;
    Ciphertext gout661 = ctx.eval_lut(&gin661, and2);

    auto gin661clear = 2 * gout647clear + gout429clear;
    auto gout661clear = fand2(gin661clear, 4);

    assert(ctx.decrypt(&gout661) == gout661clear);
    std::cerr << "\rLUT662   ";
    Ciphertext gin662 = 2 * gout661 + gout660;
    Ciphertext gout662 = ctx.eval_lut(&gin662, or2);

    auto gin662clear = 2 * gout661clear + gout660clear;
    auto gout662clear = for2(gin662clear, 4);

    assert(ctx.decrypt(&gout662) == gout662clear);
    std::cerr << "\rLUT663   ";
    Ciphertext gin663 = 2 * gout65 + gout4;
    Ciphertext gout663 = ctx.eval_lut(&gin663, xor2);

    auto gin663clear = 2 * gout65clear + gout4clear;
    auto gout663clear = fxor2(gin663clear, 4);

    assert(ctx.decrypt(&gout663) == gout663clear);
    std::cerr << "\rLUT664   ";
    Ciphertext gin664 = 2 * gout57 + gout663;
    Ciphertext gout664 = ctx.eval_lut(&gin664, xor2);

    auto gin664clear = 2 * gout57clear + gout663clear;
    auto gout664clear = fxor2(gin664clear, 4);

    assert(ctx.decrypt(&gout664) == gout664clear);
    std::cerr << "\rLUT665   ";
    Ciphertext gin665 = 2 * gout193 + gout664;
    Ciphertext gout665 = ctx.eval_lut(&gin665, xnor2);

    auto gin665clear = 2 * gout193clear + gout664clear;
    auto gout665clear = fxnor2(gin665clear, 4);

    assert(ctx.decrypt(&gout665) == gout665clear);
    std::cerr << "\rLUT666   ";
    Ciphertext gin666 = 2 * gout665 + gout434;
    Ciphertext gout666 = ctx.eval_lut(&gin666, xnor2);

    auto gin666clear = 2 * gout665clear + gout434clear;
    auto gout666clear = fxnor2(gin666clear, 4);

    assert(ctx.decrypt(&gout666) == gout666clear);
    std::cerr << "\rLUT667   ";
    Ciphertext gin667 = 2 * gout579 + gout666;
    Ciphertext gout667 = ctx.eval_lut(&gin667, xnor2);

    auto gin667clear = 2 * gout579clear + gout666clear;
    auto gout667clear = fxnor2(gin667clear, 4);

    assert(ctx.decrypt(&gout667) == gout667clear);
    std::cerr << "\rLUT668   ";
    Ciphertext gin668 = 2 * gout667 + gout582;
    Ciphertext gout668 = ctx.eval_lut(&gin668, xnor2);

    auto gin668clear = 2 * gout667clear + gout582clear;
    auto gout668clear = fxnor2(gin668clear, 4);

    assert(ctx.decrypt(&gout668) == gout668clear);
    std::cerr << "\rLUT669   ";
    Ciphertext gin669 = 2 * gout577 + gout668;
    Ciphertext gout669 = ctx.eval_lut(&gin669, and2);

    auto gin669clear = 2 * gout577clear + gout668clear;
    auto gout669clear = fand2(gin669clear, 4);

    assert(ctx.decrypt(&gout669) == gout669clear);
    std::cerr << "\rINV670   ";
    Ciphertext gout670 = 1 - gout669;

    long gout670clear = 1 - gout669clear;

    assert(ctx.decrypt(&gout670) == gout670clear);
    std::cerr << "\rINV671   ";
    Ciphertext gout671 = 1 - gout668;

    long gout671clear = 1 - gout668clear;

    assert(ctx.decrypt(&gout671) == gout671clear);
    std::cerr << "\rLUT672   ";
    Ciphertext gin672 = 2 * gout577 + gout671;
    Ciphertext gout672 = ctx.eval_lut(&gin672, xnor2);

    auto gin672clear = 2 * gout577clear + gout671clear;
    auto gout672clear = fxnor2(gin672clear, 4);

    assert(ctx.decrypt(&gout672) == gout672clear);
    std::cerr << "\rLUT673   ";
    Ciphertext gin673 = 2 * gout574 + gout672;
    Ciphertext gout673 = ctx.eval_lut(&gin673, xnor2);

    auto gin673clear = 2 * gout574clear + gout672clear;
    auto gout673clear = fxnor2(gin673clear, 4);

    assert(ctx.decrypt(&gout673) == gout673clear);
    std::cerr << "\rLUT674   ";
    Ciphertext gin674 = 2 * gout572 + gout673;
    Ciphertext gout674 = ctx.eval_lut(&gin674, xnor2);

    auto gin674clear = 2 * gout572clear + gout673clear;
    auto gout674clear = fxnor2(gin674clear, 4);

    assert(ctx.decrypt(&gout674) == gout674clear);
    std::cerr << "\rLUT675   ";
    Ciphertext gin675 = 2 * gout592 + gout674;
    Ciphertext gout675 = ctx.eval_lut(&gin675, xnor2);

    auto gin675clear = 2 * gout592clear + gout674clear;
    auto gout675clear = fxnor2(gin675clear, 4);

    assert(ctx.decrypt(&gout675) == gout675clear);
    std::cerr << "\rLUT676   ";
    Ciphertext gin676 = 2 * gout592 + gout674;
    Ciphertext gout676 = ctx.eval_lut(&gin676, nand2);

    auto gin676clear = 2 * gout592clear + gout674clear;
    auto gout676clear = fnand2(gin676clear, 4);

    assert(ctx.decrypt(&gout676) == gout676clear);
    std::cerr << "\rLUT677   ";
    Ciphertext gin677 = 2 * gout571 + gout673;
    Ciphertext gout677 = ctx.eval_lut(&gin677, nand2);

    auto gin677clear = 2 * gout571clear + gout673clear;
    auto gout677clear = fnand2(gin677clear, 4);

    assert(ctx.decrypt(&gout677) == gout677clear);
    std::cerr << "\rLUT678   ";
    Ciphertext gin678 = 2 * gout677 + gout676;
    Ciphertext gout678 = ctx.eval_lut(&gin678, nand2);

    auto gin678clear = 2 * gout677clear + gout676clear;
    auto gout678clear = fnand2(gin678clear, 4);

    assert(ctx.decrypt(&gout678) == gout678clear);
    std::cerr << "\rLUT679   ";
    Ciphertext gin679 = 2 * gout573 + gout672;
    Ciphertext gout679 = ctx.eval_lut(&gin679, and2);

    auto gin679clear = 2 * gout573clear + gout672clear;
    auto gout679clear = fand2(gin679clear, 4);

    assert(ctx.decrypt(&gout679) == gout679clear);
    std::cerr << "\rINV680   ";
    Ciphertext gout680 = 1 - gout679;

    long gout680clear = 1 - gout679clear;

    assert(ctx.decrypt(&gout680) == gout680clear);
    std::cerr << "\rLUT681   ";
    Ciphertext gin681 = 2 * (1 - gout667) + gout582;
    Ciphertext gout681 = ctx.eval_lut(&gin681, and2);

    auto gin681clear = 2 * (1 - gout667clear) + gout582clear;
    auto gout681clear = fand2(gin681clear, 4);

    assert(ctx.decrypt(&gout681) == gout681clear);
    std::cerr << "\rLUT682   ";
    Ciphertext gin682 = 2 * gout579 + gout666;
    Ciphertext gout682 = ctx.eval_lut(&gin682, and2);

    auto gin682clear = 2 * gout579clear + gout666clear;
    auto gout682clear = fand2(gin682clear, 4);

    assert(ctx.decrypt(&gout682) == gout682clear);
    std::cerr << "\rLUT683   ";
    Ciphertext gin683 = 2 * gout682 + gout681;
    Ciphertext gout683 = ctx.eval_lut(&gin683, or2);

    auto gin683clear = 2 * gout682clear + gout681clear;
    auto gout683clear = for2(gin683clear, 4);

    assert(ctx.decrypt(&gout683) == gout683clear);
    std::cerr << "\rLUT684   ";
    Ciphertext gin684 = 2 * (1 - gout665) + gout434;
    Ciphertext gout684 = ctx.eval_lut(&gin684, and2);

    auto gin684clear = 2 * (1 - gout665clear) + gout434clear;
    auto gout684clear = fand2(gin684clear, 4);

    assert(ctx.decrypt(&gout684) == gout684clear);
    std::cerr << "\rLUT685   ";
    Ciphertext gin685 = 2 * gout193 + gout664;
    Ciphertext gout685 = ctx.eval_lut(&gin685, and2);

    auto gin685clear = 2 * gout193clear + gout664clear;
    auto gout685clear = fand2(gin685clear, 4);

    assert(ctx.decrypt(&gout685) == gout685clear);
    std::cerr << "\rLUT686   ";
    Ciphertext gin686 = 2 * gout685 + gout684;
    Ciphertext gout686 = ctx.eval_lut(&gin686, or2);

    auto gin686clear = 2 * gout685clear + gout684clear;
    auto gout686clear = for2(gin686clear, 4);

    assert(ctx.decrypt(&gout686) == gout686clear);
    std::cerr << "\rLUT687   ";
    Ciphertext gin687 = 2 * gout57 + gout663;
    Ciphertext gout687 = ctx.eval_lut(&gin687, nand2);

    auto gin687clear = 2 * gout57clear + gout663clear;
    auto gout687clear = fnand2(gin687clear, 4);

    assert(ctx.decrypt(&gout687) == gout687clear);
    std::cerr << "\rLUT688   ";
    Ciphertext gin688 = 2 * gout422 + gout687;
    Ciphertext gout688 = ctx.eval_lut(&gin688, nand2);

    auto gin688clear = 2 * gout422clear + gout687clear;
    auto gout688clear = fnand2(gin688clear, 4);

    assert(ctx.decrypt(&gout688) == gout688clear);
    std::cerr << "\rLUT689   ";
    Ciphertext gin689 = 2 * gout688 + gout421;
    Ciphertext gout689 = ctx.eval_lut(&gin689, xnor2);

    auto gin689clear = 2 * gout688clear + gout421clear;
    auto gout689clear = fxnor2(gin689clear, 4);

    assert(ctx.decrypt(&gout689) == gout689clear);
    std::cerr << "\rLUT690   ";
    Ciphertext gin690 = 2 * gout689 + gout185;
    Ciphertext gout690 = ctx.eval_lut(&gin690, xnor2);

    auto gin690clear = 2 * gout689clear + gout185clear;
    auto gout690clear = fxnor2(gin690clear, 4);

    assert(ctx.decrypt(&gout690) == gout690clear);
    std::cerr << "\rLUT691   ";
    Ciphertext gin691 = 2 * gout686 + gout690;
    Ciphertext gout691 = ctx.eval_lut(&gin691, xnor2);

    auto gin691clear = 2 * gout686clear + gout690clear;
    auto gout691clear = fxnor2(gin691clear, 4);

    assert(ctx.decrypt(&gout691) == gout691clear);
    std::cerr << "\rLUT692   ";
    Ciphertext gin692 = 2 * gout686 + gout690;
    Ciphertext gout692 = ctx.eval_lut(&gin692, and2);

    auto gin692clear = 2 * gout686clear + gout690clear;
    auto gout692clear = fand2(gin692clear, 4);

    assert(ctx.decrypt(&gout692) == gout692clear);
    std::cerr << "\rLUT693   ";
    Ciphertext gin693 = 2 * (1 - gout689) + gout185;
    Ciphertext gout693 = ctx.eval_lut(&gin693, and2);

    auto gin693clear = 2 * (1 - gout689clear) + gout185clear;
    auto gout693clear = fand2(gin693clear, 4);

    assert(ctx.decrypt(&gout693) == gout693clear);
    std::cerr << "\rLUT694   ";
    Ciphertext gin694 = 2 * gout688 + gout421;
    Ciphertext gout694 = ctx.eval_lut(&gin694, and2);

    auto gin694clear = 2 * gout688clear + gout421clear;
    auto gout694clear = fand2(gin694clear, 4);

    assert(ctx.decrypt(&gout694) == gout694clear);
    std::cerr << "\rLUT695   ";
    Ciphertext gin695 = 2 * gout694 + gout693;
    Ciphertext gout695 = ctx.eval_lut(&gin695, or2);

    auto gin695clear = 2 * gout694clear + gout693clear;
    auto gout695clear = for2(gin695clear, 4);

    assert(ctx.decrypt(&gout695) == gout695clear);
    std::cerr << "\rLUT696   ";
    Ciphertext gin696 = 2 * gout695 + gout397;
    Ciphertext gout696 = ctx.eval_lut(&gin696, xnor2);

    auto gin696clear = 2 * gout695clear + gout397clear;
    auto gout696clear = fxnor2(gin696clear, 4);

    assert(ctx.decrypt(&gout696) == gout696clear);
    std::cerr << "\rLUT697   ";
    Ciphertext gin697 = 2 * gout696 + gout389;
    Ciphertext gout697 = ctx.eval_lut(&gin697, xnor2);

    auto gin697clear = 2 * gout696clear + gout389clear;
    auto gout697clear = fxnor2(gin697clear, 4);

    assert(ctx.decrypt(&gout697) == gout697clear);
    std::cerr << "\rLUT698   ";
    Ciphertext gin698 = 2 * (1 - gout696) + gout389;
    Ciphertext gout698 = ctx.eval_lut(&gin698, and2);

    auto gin698clear = 2 * (1 - gout696clear) + gout389clear;
    auto gout698clear = fand2(gin698clear, 4);

    assert(ctx.decrypt(&gout698) == gout698clear);
    std::cerr << "\rLUT699   ";
    Ciphertext gin699 = 2 * gout695 + gout397;
    Ciphertext gout699 = ctx.eval_lut(&gin699, and2);

    auto gin699clear = 2 * gout695clear + gout397clear;
    auto gout699clear = fand2(gin699clear, 4);

    assert(ctx.decrypt(&gout699) == gout699clear);
    std::cerr << "\rLUT700   ";
    Ciphertext gin700 = 2 * gout699 + gout698;
    Ciphertext gout700 = ctx.eval_lut(&gin700, or2);

    auto gin700clear = 2 * gout699clear + gout698clear;
    auto gout700clear = for2(gin700clear, 4);

    assert(ctx.decrypt(&gout700) == gout700clear);
    std::cerr << "\rLUT701   ";
    Ciphertext gin701 = 2 * gout700 + gout623;
    Ciphertext gout701 = ctx.eval_lut(&gin701, xnor2);

    auto gin701clear = 2 * gout700clear + gout623clear;
    auto gout701clear = fxnor2(gin701clear, 4);

    assert(ctx.decrypt(&gout701) == gout701clear);
    std::cerr << "\rLUT702   ";
    Ciphertext gin702 = 2 * gout701 + gout392;
    Ciphertext gout702 = ctx.eval_lut(&gin702, xnor2);

    auto gin702clear = 2 * gout701clear + gout392clear;
    auto gout702clear = fxnor2(gin702clear, 4);

    assert(ctx.decrypt(&gout702) == gout702clear);
    std::cerr << "\rLUT703   ";
    Ciphertext gin703 = 2 * (1 - gout701) + gout392;
    Ciphertext gout703 = ctx.eval_lut(&gin703, and2);

    auto gin703clear = 2 * (1 - gout701clear) + gout392clear;
    auto gout703clear = fand2(gin703clear, 4);

    assert(ctx.decrypt(&gout703) == gout703clear);
    std::cerr << "\rLUT704   ";
    Ciphertext gin704 = 2 * gout700 + gout623;
    Ciphertext gout704 = ctx.eval_lut(&gin704, and2);

    auto gin704clear = 2 * gout700clear + gout623clear;
    auto gout704clear = fand2(gin704clear, 4);

    assert(ctx.decrypt(&gout704) == gout704clear);
    std::cerr << "\rLUT705   ";
    Ciphertext gin705 = 2 * gout704 + gout703;
    Ciphertext gout705 = ctx.eval_lut(&gin705, or2);

    auto gin705clear = 2 * gout704clear + gout703clear;
    auto gout705clear = for2(gin705clear, 4);

    assert(ctx.decrypt(&gout705) == gout705clear);
    std::cerr << "\rLUT706   ";
    Ciphertext gin706 = 2 * gout705 + gout638;
    Ciphertext gout706 = ctx.eval_lut(&gin706, xor2);

    auto gin706clear = 2 * gout705clear + gout638clear;
    auto gout706clear = fxor2(gin706clear, 4);

    assert(ctx.decrypt(&gout706) == gout706clear);
    std::cerr << "\rLUT707   ";
    Ciphertext gin707 = 2 * gout393 + gout706;
    Ciphertext gout707 = ctx.eval_lut(&gin707, xor2);

    auto gin707clear = 2 * gout393clear + gout706clear;
    auto gout707clear = fxor2(gin707clear, 4);

    assert(ctx.decrypt(&gout707) == gout707clear);
    std::cerr << "\rLUT708   ";
    Ciphertext gin708 = 2 * gout393 + gout706;
    Ciphertext gout708 = ctx.eval_lut(&gin708, nand2);

    auto gin708clear = 2 * gout393clear + gout706clear;
    auto gout708clear = fnand2(gin708clear, 4);

    assert(ctx.decrypt(&gout708) == gout708clear);
    std::cerr << "\rLUT709   ";
    Ciphertext gin709 = 2 * gout705 + gout638;
    Ciphertext gout709 = ctx.eval_lut(&gin709, nand2);

    auto gin709clear = 2 * gout705clear + gout638clear;
    auto gout709clear = fnand2(gin709clear, 4);

    assert(ctx.decrypt(&gout709) == gout709clear);
    std::cerr << "\rLUT710   ";
    Ciphertext gin710 = 2 * gout709 + gout708;
    Ciphertext gout710 = ctx.eval_lut(&gin710, nand2);

    auto gin710clear = 2 * gout709clear + gout708clear;
    auto gout710clear = fnand2(gin710clear, 4);

    assert(ctx.decrypt(&gout710) == gout710clear);
    std::cerr << "\rLUT711   ";
    Ciphertext gin711 = 2 * gout710 + gout653;
    Ciphertext gout711 = ctx.eval_lut(&gin711, xor2);

    auto gin711clear = 2 * gout710clear + gout653clear;
    auto gout711clear = fxor2(gin711clear, 4);

    assert(ctx.decrypt(&gout711) == gout711clear);
    std::cerr << "\rLUT712   ";
    Ciphertext gin712 = 2 * gout710 + gout653;
    Ciphertext gout712 = ctx.eval_lut(&gin712, and2);

    auto gin712clear = 2 * gout710clear + gout653clear;
    auto gout712clear = fand2(gin712clear, 4);

    assert(ctx.decrypt(&gout712) == gout712clear);
    std::cerr << "\rLUT713   ";
    Ciphertext gin713 = 2 * (1 - gout347) + gout211;
    Ciphertext gout713 = ctx.eval_lut(&gin713, and2);

    auto gin713clear = 2 * (1 - gout347clear) + gout211clear;
    auto gout713clear = fand2(gin713clear, 4);

    assert(ctx.decrypt(&gout713) == gout713clear);
    std::cerr << "\rLUT714   ";
    Ciphertext gin714 = 2 * gout160 + gout713;
    Ciphertext gout714 = ctx.eval_lut(&gin714, xnor2);

    auto gin714clear = 2 * gout160clear + gout713clear;
    auto gout714clear = fxnor2(gin714clear, 4);

    assert(ctx.decrypt(&gout714) == gout714clear);
    std::cerr << "\rLUT715   ";
    Ciphertext gin715 = 2 * gout25 + gout714;
    Ciphertext gout715 = ctx.eval_lut(&gin715, xnor2);

    auto gin715clear = 2 * gout25clear + gout714clear;
    auto gout715clear = fxnor2(gin715clear, 4);

    assert(ctx.decrypt(&gout715) == gout715clear);
    std::cerr << "\rLUT716   ";
    Ciphertext gin716 = 2 * gout385 + gout715;
    Ciphertext gout716 = ctx.eval_lut(&gin716, xnor2);

    auto gin716clear = 2 * gout385clear + gout715clear;
    auto gout716clear = fxnor2(gin716clear, 4);

    assert(ctx.decrypt(&gout716) == gout716clear);
    std::cerr << "\rIMUX717  ";
    Ciphertext gin717A = 2 * gout716 + gout115;
    Ciphertext gout717A = ctx.eval_lut(&gin717A, and2);
    Ciphertext gin717B = 2 * gout594 + (1 - gout115);
    Ciphertext gout717B = ctx.eval_lut(&gin717B, and2);
    Ciphertext gout717 = gout717A + gout717B;

    long gin717Aclear = 2 * gout716clear + gout115clear;
    long gout717Aclear = fand2(gin717Aclear, 4);
    long gin717Bclear = 2 * gout594clear + (1 - gout115clear);
    long gout717Bclear = fand2(gin717Bclear, 4);
    long gout717clear = gout717Aclear + gout717Bclear;

    assert(ctx.decrypt(&gout717) == gout717clear);
    std::cerr << "\rLUT718   ";
    Ciphertext gin718 = 2 * gout218 + gout717;
    Ciphertext gout718 = ctx.eval_lut(&gin718, nand2);

    auto gin718clear = 2 * gout218clear + gout717clear;
    auto gout718clear = fnand2(gin718clear, 4);

    assert(ctx.decrypt(&gout718) == gout718clear);
    std::cerr << "\rLUT719   ";
    Ciphertext gin719 = 2 * gout385 + gout715;
    Ciphertext gout719 = ctx.eval_lut(&gin719, nand2);

    auto gin719clear = 2 * gout385clear + gout715clear;
    auto gout719clear = fnand2(gin719clear, 4);

    assert(ctx.decrypt(&gout719) == gout719clear);
    std::cerr << "\rLUT720   ";
    Ciphertext gin720 = 2 * ct_x4 + gout714;
    Ciphertext gout720 = ctx.eval_lut(&gin720, nand2);

    auto gin720clear = 2 * ct_x4clear + gout714clear;
    auto gout720clear = fnand2(gin720clear, 4);

    assert(ctx.decrypt(&gout720) == gout720clear);
    std::cerr << "\rLUT721   ";
    Ciphertext gin721 = 2 * gout720 + gout719;
    Ciphertext gout721 = ctx.eval_lut(&gin721, nand2);

    auto gin721clear = 2 * gout720clear + gout719clear;
    auto gout721clear = fnand2(gin721clear, 4);

    assert(ctx.decrypt(&gout721) == gout721clear);
    std::cerr << "\rLUT722   ";
    Ciphertext gin722 = 2 * gout721 + gout498;
    Ciphertext gout722 = ctx.eval_lut(&gin722, xnor2);

    auto gin722clear = 2 * gout721clear + gout498clear;
    auto gout722clear = fxnor2(gin722clear, 4);

    assert(ctx.decrypt(&gout722) == gout722clear);
    std::cerr << "\rIMUX723  ";
    Ciphertext gin723A = 2 * gout590 + gout104;
    Ciphertext gout723A = ctx.eval_lut(&gin723A, and2);
    Ciphertext gin723B = 2 * gout722 + (1 - gout104);
    Ciphertext gout723B = ctx.eval_lut(&gin723B, and2);
    Ciphertext gout723 = gout723A + gout723B;

    long gin723Aclear = 2 * gout590clear + gout104clear;
    long gout723Aclear = fand2(gin723Aclear, 4);
    long gin723Bclear = 2 * gout722clear + (1 - gout104clear);
    long gout723Bclear = fand2(gin723Bclear, 4);
    long gout723clear = gout723Aclear + gout723Bclear;

    assert(ctx.decrypt(&gout723) == gout723clear);
    std::cerr << "\rLUT724   ";
    Ciphertext gin724 = 2 * gout218 + gout723;
    Ciphertext gout724 = ctx.eval_lut(&gin724, nand2);

    auto gin724clear = 2 * gout218clear + gout723clear;
    auto gout724clear = fnand2(gin724clear, 4);

    assert(ctx.decrypt(&gout724) == gout724clear);
    std::cerr << "\rLUT725   ";
    Ciphertext gin725 = 2 * gout721 + gout498;
    Ciphertext gout725 = ctx.eval_lut(&gin725, nand2);

    auto gin725clear = 2 * gout721clear + gout498clear;
    auto gout725clear = fnand2(gin725clear, 4);

    assert(ctx.decrypt(&gout725) == gout725clear);
    std::cerr << "\rLUT726   ";
    Ciphertext gin726 = 2 * gout499 + gout725;
    Ciphertext gout726 = ctx.eval_lut(&gin726, nand2);

    auto gin726clear = 2 * gout499clear + gout725clear;
    auto gout726clear = fnand2(gin726clear, 4);

    assert(ctx.decrypt(&gout726) == gout726clear);
    std::cerr << "\rLUT727   ";
    Ciphertext gin727 = 2 * gout726 + gout494;
    Ciphertext gout727 = ctx.eval_lut(&gin727, xnor2);

    auto gin727clear = 2 * gout726clear + gout494clear;
    auto gout727clear = fxnor2(gin727clear, 4);

    assert(ctx.decrypt(&gout727) == gout727clear);
    std::cerr << "\rIMUX728  ";
    Ciphertext gin728A = 2 * gout675 + gout104;
    Ciphertext gout728A = ctx.eval_lut(&gin728A, and2);
    Ciphertext gin728B = 2 * gout727 + (1 - gout104);
    Ciphertext gout728B = ctx.eval_lut(&gin728B, and2);
    Ciphertext gout728 = gout728A + gout728B;

    long gin728Aclear = 2 * gout675clear + gout104clear;
    long gout728Aclear = fand2(gin728Aclear, 4);
    long gin728Bclear = 2 * gout727clear + (1 - gout104clear);
    long gout728Bclear = fand2(gin728Bclear, 4);
    long gout728clear = gout728Aclear + gout728Bclear;

    assert(ctx.decrypt(&gout728) == gout728clear);
    std::cerr << "\rLUT729   ";
    Ciphertext gin729 = 2 * gout218 + gout728;
    Ciphertext gout729 = ctx.eval_lut(&gin729, nand2);

    auto gin729clear = 2 * gout218clear + gout728clear;
    auto gout729clear = fnand2(gin729clear, 4);

    assert(ctx.decrypt(&gout729) == gout729clear);
    std::cerr << "\rLUT730   ";
    Ciphertext gin730 = 2 * gout726 + gout494;
    Ciphertext gout730 = ctx.eval_lut(&gin730, nand2);

    auto gin730clear = 2 * gout726clear + gout494clear;
    auto gout730clear = fnand2(gin730clear, 4);

    assert(ctx.decrypt(&gout730) == gout730clear);
    std::cerr << "\rLUT731   ";
    Ciphertext gin731 = 2 * gout495 + gout730;
    Ciphertext gout731 = ctx.eval_lut(&gin731, nand2);

    auto gin731clear = 2 * gout495clear + gout730clear;
    auto gout731clear = fnand2(gin731clear, 4);

    assert(ctx.decrypt(&gout731) == gout731clear);
    std::cerr << "\rLUT732   ";
    Ciphertext gin732 = 2 * gout731 + gout490;
    Ciphertext gout732 = ctx.eval_lut(&gin732, xnor2);

    auto gin732clear = 2 * gout731clear + gout490clear;
    auto gout732clear = fxnor2(gin732clear, 4);

    assert(ctx.decrypt(&gout732) == gout732clear);
    std::cerr << "\rLUT733   ";
    Ciphertext gin733 = 2 * gout731 + gout490;
    Ciphertext gout733 = ctx.eval_lut(&gin733, nand2);

    auto gin733clear = 2 * gout731clear + gout490clear;
    auto gout733clear = fnand2(gin733clear, 4);

    assert(ctx.decrypt(&gout733) == gout733clear);
    std::cerr << "\rLUT734   ";
    Ciphertext gin734 = 2 * gout491 + gout733;
    Ciphertext gout734 = ctx.eval_lut(&gin734, nand2);

    auto gin734clear = 2 * gout491clear + gout733clear;
    auto gout734clear = fnand2(gin734clear, 4);

    assert(ctx.decrypt(&gout734) == gout734clear);
    std::cerr << "\rLUT735   ";
    Ciphertext gin735 = 2 * gout734 + gout486;
    Ciphertext gout735 = ctx.eval_lut(&gin735, xnor2);

    auto gin735clear = 2 * gout734clear + gout486clear;
    auto gout735clear = fxnor2(gin735clear, 4);

    assert(ctx.decrypt(&gout735) == gout735clear);
    std::cerr << "\rLUT736   ";
    Ciphertext gin736 = 2 * gout734 + gout486;
    Ciphertext gout736 = ctx.eval_lut(&gin736, nand2);

    auto gin736clear = 2 * gout734clear + gout486clear;
    auto gout736clear = fnand2(gin736clear, 4);

    assert(ctx.decrypt(&gout736) == gout736clear);
    std::cerr << "\rLUT737   ";
    Ciphertext gin737 = 2 * gout487 + gout736;
    Ciphertext gout737 = ctx.eval_lut(&gin737, nand2);

    auto gin737clear = 2 * gout487clear + gout736clear;
    auto gout737clear = fnand2(gin737clear, 4);

    assert(ctx.decrypt(&gout737) == gout737clear);
    std::cerr << "\rLUT738   ";
    Ciphertext gin738 = 2 * gout62 + gout111;
    Ciphertext gout738 = ctx.eval_lut(&gin738, xnor2);

    auto gin738clear = 2 * gout62clear + gout111clear;
    auto gout738clear = fxnor2(gin738clear, 4);

    assert(ctx.decrypt(&gout738) == gout738clear);
    std::cerr << "\rLUT739   ";
    Ciphertext gin739 = 2 * gout598 + gout738;
    Ciphertext gout739 = ctx.eval_lut(&gin739, xnor2);

    auto gin739clear = 2 * gout598clear + gout738clear;
    auto gout739clear = fxnor2(gin739clear, 4);

    assert(ctx.decrypt(&gout739) == gout739clear);
    std::cerr << "\rLUT740   ";
    Ciphertext gin740 = 2 * gout338 + gout739;
    Ciphertext gout740 = ctx.eval_lut(&gin740, xor2);

    auto gin740clear = 2 * gout338clear + gout739clear;
    auto gout740clear = fxor2(gin740clear, 4);

    assert(ctx.decrypt(&gout740) == gout740clear);
    std::cerr << "\rLUT741   ";
    Ciphertext gin741 = 2 * gout444 + gout740;
    Ciphertext gout741 = ctx.eval_lut(&gin741, xor2);

    auto gin741clear = 2 * gout444clear + gout740clear;
    auto gout741clear = fxor2(gin741clear, 4);

    assert(ctx.decrypt(&gout741) == gout741clear);
    std::cerr << "\rLUT742   ";
    Ciphertext gin742 = 2 * gout444 + gout740;
    Ciphertext gout742 = ctx.eval_lut(&gin742, nand2);

    auto gin742clear = 2 * gout444clear + gout740clear;
    auto gout742clear = fnand2(gin742clear, 4);

    assert(ctx.decrypt(&gout742) == gout742clear);
    std::cerr << "\rLUT743   ";
    Ciphertext gin743 = 2 * gout338 + gout739;
    Ciphertext gout743 = ctx.eval_lut(&gin743, nand2);

    auto gin743clear = 2 * gout338clear + gout739clear;
    auto gout743clear = fnand2(gin743clear, 4);

    assert(ctx.decrypt(&gout743) == gout743clear);
    std::cerr << "\rLUT744   ";
    Ciphertext gin744 = 2 * gout743 + gout742;
    Ciphertext gout744 = ctx.eval_lut(&gin744, nand2);

    auto gin744clear = 2 * gout743clear + gout742clear;
    auto gout744clear = fnand2(gin744clear, 4);

    assert(ctx.decrypt(&gout744) == gout744clear);
    std::cerr << "\rLUT745   ";
    Ciphertext gin745 = 2 * gout386 + gout744;
    Ciphertext gout745 = ctx.eval_lut(&gin745, xor2);

    auto gin745clear = 2 * gout386clear + gout744clear;
    auto gout745clear = fxor2(gin745clear, 4);

    assert(ctx.decrypt(&gout745) == gout745clear);
    std::cerr << "\rLUT746   ";
    Ciphertext gin746 = 2 * gout386 + gout744;
    Ciphertext gout746 = ctx.eval_lut(&gin746, and2);

    auto gin746clear = 2 * gout386clear + gout744clear;
    auto gout746clear = fand2(gin746clear, 4);

    assert(ctx.decrypt(&gout746) == gout746clear);
    std::cerr << "\rLUT747   ";
    Ciphertext gin747 = 2 * (1 - gout598) + gout738;
    Ciphertext gout747 = ctx.eval_lut(&gin747, and2);

    auto gin747clear = 2 * (1 - gout598clear) + gout738clear;
    auto gout747clear = fand2(gin747clear, 4);

    assert(ctx.decrypt(&gout747) == gout747clear);
    std::cerr << "\rLUT748   ";
    Ciphertext gin748 = 2 * gout599 + gout747;
    Ciphertext gout748 = ctx.eval_lut(&gin748, or2);

    auto gin748clear = 2 * gout599clear + gout747clear;
    auto gout748clear = for2(gin748clear, 4);

    assert(ctx.decrypt(&gout748) == gout748clear);
    std::cerr << "\rLUT749   ";
    Ciphertext gin749 = 2 * gout748 + gout605;
    Ciphertext gout749 = ctx.eval_lut(&gin749, xor2);

    auto gin749clear = 2 * gout748clear + gout605clear;
    auto gout749clear = fxor2(gin749clear, 4);

    assert(ctx.decrypt(&gout749) == gout749clear);
    std::cerr << "\rLUT750   ";
    Ciphertext gin750 = 2 * gout545 + gout749;
    Ciphertext gout750 = ctx.eval_lut(&gin750, xnor2);

    auto gin750clear = 2 * gout545clear + gout749clear;
    auto gout750clear = fxnor2(gin750clear, 4);

    assert(ctx.decrypt(&gout750) == gout750clear);
    std::cerr << "\rLUT751   ";
    Ciphertext gin751 = 2 * (1 - gout545) + gout749;
    Ciphertext gout751 = ctx.eval_lut(&gin751, and2);

    auto gin751clear = 2 * (1 - gout545clear) + gout749clear;
    auto gout751clear = fand2(gin751clear, 4);

    assert(ctx.decrypt(&gout751) == gout751clear);
    std::cerr << "\rLUT752   ";
    Ciphertext gin752 = 2 * gout546 + gout751;
    Ciphertext gout752 = ctx.eval_lut(&gin752, or2);

    auto gin752clear = 2 * gout546clear + gout751clear;
    auto gout752clear = for2(gin752clear, 4);

    assert(ctx.decrypt(&gout752) == gout752clear);
    std::cerr << "\rLUT753   ";
    Ciphertext gin753 = 2 * gout748 + gout605;
    Ciphertext gout753 = ctx.eval_lut(&gin753, nand2);

    auto gin753clear = 2 * gout748clear + gout605clear;
    auto gout753clear = fnand2(gin753clear, 4);

    assert(ctx.decrypt(&gout753) == gout753clear);
    std::cerr << "\rLUT754   ";
    Ciphertext gin754 = 2 * gout606 + gout753;
    Ciphertext gout754 = ctx.eval_lut(&gin754, nand2);

    auto gin754clear = 2 * gout606clear + gout753clear;
    auto gout754clear = fnand2(gin754clear, 4);

    assert(ctx.decrypt(&gout754) == gout754clear);
    std::cerr << "\rLUT755   ";
    Ciphertext gin755 = 2 * gout754 + gout247;
    Ciphertext gout755 = ctx.eval_lut(&gin755, xnor2);

    auto gin755clear = 2 * gout754clear + gout247clear;
    auto gout755clear = fxnor2(gin755clear, 4);

    assert(ctx.decrypt(&gout755) == gout755clear);
    std::cerr << "\rLUT756   ";
    Ciphertext gin756 = 2 * gout755 + gout612;
    Ciphertext gout756 = ctx.eval_lut(&gin756, xnor2);

    auto gin756clear = 2 * gout755clear + gout612clear;
    auto gout756clear = fxnor2(gin756clear, 4);

    assert(ctx.decrypt(&gout756) == gout756clear);
    std::cerr << "\rLUT757   ";
    Ciphertext gin757 = 2 * gout752 + gout756;
    Ciphertext gout757 = ctx.eval_lut(&gin757, xnor2);

    auto gin757clear = 2 * gout752clear + gout756clear;
    auto gout757clear = fxnor2(gin757clear, 4);

    assert(ctx.decrypt(&gout757) == gout757clear);
    std::cerr << "\rLUT758   ";
    Ciphertext gin758 = 2 * gout298 + gout532;
    Ciphertext gout758 = ctx.eval_lut(&gin758, xnor2);

    auto gin758clear = 2 * gout298clear + gout532clear;
    auto gout758clear = fxnor2(gin758clear, 4);

    assert(ctx.decrypt(&gout758) == gout758clear);
    std::cerr << "\rLUT759   ";
    Ciphertext gin759 = 2 * gout432 + gout758;
    Ciphertext gout759 = ctx.eval_lut(&gin759, xnor2);

    auto gin759clear = 2 * gout432clear + gout758clear;
    auto gout759clear = fxnor2(gin759clear, 4);

    assert(ctx.decrypt(&gout759) == gout759clear);
    std::cerr << "\rLUT760   ";
    Ciphertext gin760 = 2 * gout759 + gout387;
    Ciphertext gout760 = ctx.eval_lut(&gin760, xnor2);

    auto gin760clear = 2 * gout759clear + gout387clear;
    auto gout760clear = fxnor2(gin760clear, 4);

    assert(ctx.decrypt(&gout760) == gout760clear);
    std::cerr << "\rLUT761   ";
    Ciphertext gin761 = 2 * gout662 + gout760;
    Ciphertext gout761 = ctx.eval_lut(&gin761, xnor2);

    auto gin761clear = 2 * gout662clear + gout760clear;
    auto gout761clear = fxnor2(gin761clear, 4);

    assert(ctx.decrypt(&gout761) == gout761clear);
    std::cerr << "\rLUT762   ";
    Ciphertext gin762 = 2 * gout761 + gout526;
    Ciphertext gout762 = ctx.eval_lut(&gin762, xnor2);

    auto gin762clear = 2 * gout761clear + gout526clear;
    auto gout762clear = fxnor2(gin762clear, 4);

    assert(ctx.decrypt(&gout762) == gout762clear);
    std::cerr << "\rLUT763   ";
    Ciphertext gin763 = 2 * gout659 + gout762;
    Ciphertext gout763 = ctx.eval_lut(&gin763, xor2);

    auto gin763clear = 2 * gout659clear + gout762clear;
    auto gout763clear = fxor2(gin763clear, 4);

    assert(ctx.decrypt(&gout763) == gout763clear);
    std::cerr << "\rLUT764   ";
    Ciphertext gin764 = 2 * gout564 + gout763;
    Ciphertext gout764 = ctx.eval_lut(&gin764, xor2);

    auto gin764clear = 2 * gout564clear + gout763clear;
    auto gout764clear = fxor2(gin764clear, 4);

    assert(ctx.decrypt(&gout764) == gout764clear);
    std::cerr << "\rLUT765   ";
    Ciphertext gin765 = 2 * gout656 + gout764;
    Ciphertext gout765 = ctx.eval_lut(&gin765, xor2);

    auto gin765clear = 2 * gout656clear + gout764clear;
    auto gout765clear = fxor2(gin765clear, 4);

    assert(ctx.decrypt(&gout765) == gout765clear);
    std::cerr << "\rLUT766   ";
    Ciphertext gin766 = 2 * gout712 + gout765;
    Ciphertext gout766 = ctx.eval_lut(&gin766, xor2);

    auto gin766clear = 2 * gout712clear + gout765clear;
    auto gout766clear = fxor2(gin766clear, 4);

    assert(ctx.decrypt(&gout766) == gout766clear);
    std::cerr << "\rLUT767   ";
    Ciphertext gin767 = 2 * gout712 + gout765;
    Ciphertext gout767 = ctx.eval_lut(&gin767, nand2);

    auto gin767clear = 2 * gout712clear + gout765clear;
    auto gout767clear = fnand2(gin767clear, 4);

    assert(ctx.decrypt(&gout767) == gout767clear);
    std::cerr << "\rLUT768   ";
    Ciphertext gin768 = 2 * gout656 + gout764;
    Ciphertext gout768 = ctx.eval_lut(&gin768, and2);

    auto gin768clear = 2 * gout656clear + gout764clear;
    auto gout768clear = fand2(gin768clear, 4);

    assert(ctx.decrypt(&gout768) == gout768clear);
    std::cerr << "\rLUT769   ";
    Ciphertext gin769 = 2 * gout564 + gout763;
    Ciphertext gout769 = ctx.eval_lut(&gin769, nand2);

    auto gin769clear = 2 * gout564clear + gout763clear;
    auto gout769clear = fnand2(gin769clear, 4);

    assert(ctx.decrypt(&gout769) == gout769clear);
    std::cerr << "\rLUT770   ";
    Ciphertext gin770 = 2 * gout659 + gout762;
    Ciphertext gout770 = ctx.eval_lut(&gin770, nand2);

    auto gin770clear = 2 * gout659clear + gout762clear;
    auto gout770clear = fnand2(gin770clear, 4);

    assert(ctx.decrypt(&gout770) == gout770clear);
    std::cerr << "\rLUT771   ";
    Ciphertext gin771 = 2 * gout770 + gout769;
    Ciphertext gout771 = ctx.eval_lut(&gin771, nand2);

    auto gin771clear = 2 * gout770clear + gout769clear;
    auto gout771clear = fnand2(gin771clear, 4);

    assert(ctx.decrypt(&gout771) == gout771clear);
    std::cerr << "\rLUT772   ";
    Ciphertext gin772 = 2 * (1 - gout761) + gout526;
    Ciphertext gout772 = ctx.eval_lut(&gin772, and2);

    auto gin772clear = 2 * (1 - gout761clear) + gout526clear;
    auto gout772clear = fand2(gin772clear, 4);

    assert(ctx.decrypt(&gout772) == gout772clear);
    std::cerr << "\rLUT773   ";
    Ciphertext gin773 = 2 * gout662 + gout760;
    Ciphertext gout773 = ctx.eval_lut(&gin773, and2);

    auto gin773clear = 2 * gout662clear + gout760clear;
    auto gout773clear = fand2(gin773clear, 4);

    assert(ctx.decrypt(&gout773) == gout773clear);
    std::cerr << "\rLUT774   ";
    Ciphertext gin774 = 2 * gout773 + gout772;
    Ciphertext gout774 = ctx.eval_lut(&gin774, or2);

    auto gin774clear = 2 * gout773clear + gout772clear;
    auto gout774clear = for2(gin774clear, 4);

    assert(ctx.decrypt(&gout774) == gout774clear);
    std::cerr << "\rLUT775   ";
    Ciphertext gin775 = 2 * (1 - gout759) + gout387;
    Ciphertext gout775 = ctx.eval_lut(&gin775, and2);

    auto gin775clear = 2 * (1 - gout759clear) + gout387clear;
    auto gout775clear = fand2(gin775clear, 4);

    assert(ctx.decrypt(&gout775) == gout775clear);
    std::cerr << "\rLUT776   ";
    Ciphertext gin776 = 2 * gout432 + gout758;
    Ciphertext gout776 = ctx.eval_lut(&gin776, and2);

    auto gin776clear = 2 * gout432clear + gout758clear;
    auto gout776clear = fand2(gin776clear, 4);

    assert(ctx.decrypt(&gout776) == gout776clear);
    std::cerr << "\rLUT777   ";
    Ciphertext gin777 = 2 * gout776 + gout775;
    Ciphertext gout777 = ctx.eval_lut(&gin777, or2);

    auto gin777clear = 2 * gout776clear + gout775clear;
    auto gout777clear = for2(gin777clear, 4);

    assert(ctx.decrypt(&gout777) == gout777clear);
    std::cerr << "\rLUT778   ";
    Ciphertext gin778 = 2 * gout777 + gout542;
    Ciphertext gout778 = ctx.eval_lut(&gin778, xnor2);

    auto gin778clear = 2 * gout777clear + gout542clear;
    auto gout778clear = fxnor2(gin778clear, 4);

    assert(ctx.decrypt(&gout778) == gout778clear);
    std::cerr << "\rLUT779   ";
    Ciphertext gin779 = 2 * gout778 + gout741;
    Ciphertext gout779 = ctx.eval_lut(&gin779, xnor2);

    auto gin779clear = 2 * gout778clear + gout741clear;
    auto gout779clear = fxnor2(gin779clear, 4);

    assert(ctx.decrypt(&gout779) == gout779clear);
    std::cerr << "\rLUT780   ";
    Ciphertext gin780 = 2 * gout774 + gout779;
    Ciphertext gout780 = ctx.eval_lut(&gin780, xor2);

    auto gin780clear = 2 * gout774clear + gout779clear;
    auto gout780clear = fxor2(gin780clear, 4);

    assert(ctx.decrypt(&gout780) == gout780clear);
    std::cerr << "\rLUT781   ";
    Ciphertext gin781 = 2 * gout529 + gout780;
    Ciphertext gout781 = ctx.eval_lut(&gin781, xor2);

    auto gin781clear = 2 * gout529clear + gout780clear;
    auto gout781clear = fxor2(gin781clear, 4);

    assert(ctx.decrypt(&gout781) == gout781clear);
    std::cerr << "\rLUT782   ";
    Ciphertext gin782 = 2 * gout771 + gout781;
    Ciphertext gout782 = ctx.eval_lut(&gin782, xor2);

    auto gin782clear = 2 * gout771clear + gout781clear;
    auto gout782clear = fxor2(gin782clear, 4);

    assert(ctx.decrypt(&gout782) == gout782clear);
    std::cerr << "\rLUT783   ";
    Ciphertext gin783 = 2 * gout768 + gout782;
    Ciphertext gout783 = ctx.eval_lut(&gin783, xor2);

    auto gin783clear = 2 * gout768clear + gout782clear;
    auto gout783clear = fxor2(gin783clear, 4);

    assert(ctx.decrypt(&gout783) == gout783clear);
    std::cerr << "\rLUT784   ";
    Ciphertext gin784 = 2 * gout768 + gout782;
    Ciphertext gout784 = ctx.eval_lut(&gin784, nand2);

    auto gin784clear = 2 * gout768clear + gout782clear;
    auto gout784clear = fnand2(gin784clear, 4);

    assert(ctx.decrypt(&gout784) == gout784clear);
    std::cerr << "\rLUT785   ";
    Ciphertext gin785 = 2 * gout771 + gout781;
    Ciphertext gout785 = ctx.eval_lut(&gin785, and2);

    auto gin785clear = 2 * gout771clear + gout781clear;
    auto gout785clear = fand2(gin785clear, 4);

    assert(ctx.decrypt(&gout785) == gout785clear);
    std::cerr << "\rLUT786   ";
    Ciphertext gin786 = 2 * gout529 + gout780;
    Ciphertext gout786 = ctx.eval_lut(&gin786, nand2);

    auto gin786clear = 2 * gout529clear + gout780clear;
    auto gout786clear = fnand2(gin786clear, 4);

    assert(ctx.decrypt(&gout786) == gout786clear);
    std::cerr << "\rLUT787   ";
    Ciphertext gin787 = 2 * gout774 + gout779;
    Ciphertext gout787 = ctx.eval_lut(&gin787, nand2);

    auto gin787clear = 2 * gout774clear + gout779clear;
    auto gout787clear = fnand2(gin787clear, 4);

    assert(ctx.decrypt(&gout787) == gout787clear);
    std::cerr << "\rLUT788   ";
    Ciphertext gin788 = 2 * gout787 + gout786;
    Ciphertext gout788 = ctx.eval_lut(&gin788, nand2);

    auto gin788clear = 2 * gout787clear + gout786clear;
    auto gout788clear = fnand2(gin788clear, 4);

    assert(ctx.decrypt(&gout788) == gout788clear);
    std::cerr << "\rLUT789   ";
    Ciphertext gin789 = 2 * (1 - gout778) + gout741;
    Ciphertext gout789 = ctx.eval_lut(&gin789, and2);

    auto gin789clear = 2 * (1 - gout778clear) + gout741clear;
    auto gout789clear = fand2(gin789clear, 4);

    assert(ctx.decrypt(&gout789) == gout789clear);
    std::cerr << "\rLUT790   ";
    Ciphertext gin790 = 2 * gout777 + gout542;
    Ciphertext gout790 = ctx.eval_lut(&gin790, and2);

    auto gin790clear = 2 * gout777clear + gout542clear;
    auto gout790clear = fand2(gin790clear, 4);

    assert(ctx.decrypt(&gout790) == gout790clear);
    std::cerr << "\rLUT791   ";
    Ciphertext gin791 = 2 * gout790 + gout789;
    Ciphertext gout791 = ctx.eval_lut(&gin791, or2);

    auto gin791clear = 2 * gout790clear + gout789clear;
    auto gout791clear = for2(gin791clear, 4);

    assert(ctx.decrypt(&gout791) == gout791clear);
    std::cerr << "\rLUT792   ";
    Ciphertext gin792 = 2 * gout791 + gout750;
    Ciphertext gout792 = ctx.eval_lut(&gin792, xnor2);

    auto gin792clear = 2 * gout791clear + gout750clear;
    auto gout792clear = fxnor2(gin792clear, 4);

    assert(ctx.decrypt(&gout792) == gout792clear);
    std::cerr << "\rLUT793   ";
    Ciphertext gin793 = 2 * gout792 + gout745;
    Ciphertext gout793 = ctx.eval_lut(&gin793, xnor2);

    auto gin793clear = 2 * gout792clear + gout745clear;
    auto gout793clear = fxnor2(gin793clear, 4);

    assert(ctx.decrypt(&gout793) == gout793clear);
    std::cerr << "\rLUT794   ";
    Ciphertext gin794 = 2 * gout788 + gout793;
    Ciphertext gout794 = ctx.eval_lut(&gin794, xor2);

    auto gin794clear = 2 * gout788clear + gout793clear;
    auto gout794clear = fxor2(gin794clear, 4);

    assert(ctx.decrypt(&gout794) == gout794clear);
    std::cerr << "\rLUT795   ";
    Ciphertext gin795 = 2 * gout785 + gout794;
    Ciphertext gout795 = ctx.eval_lut(&gin795, xor2);

    auto gin795clear = 2 * gout785clear + gout794clear;
    auto gout795clear = fxor2(gin795clear, 4);

    assert(ctx.decrypt(&gout795) == gout795clear);
    std::cerr << "\rLUT796   ";
    Ciphertext gin796 = 2 * gout785 + gout794;
    Ciphertext gout796 = ctx.eval_lut(&gin796, nand2);

    auto gin796clear = 2 * gout785clear + gout794clear;
    auto gout796clear = fnand2(gin796clear, 4);

    assert(ctx.decrypt(&gout796) == gout796clear);
    std::cerr << "\rLUT797   ";
    Ciphertext gin797 = 2 * gout788 + gout793;
    Ciphertext gout797 = ctx.eval_lut(&gin797, and2);

    auto gin797clear = 2 * gout788clear + gout793clear;
    auto gout797clear = fand2(gin797clear, 4);

    assert(ctx.decrypt(&gout797) == gout797clear);
    std::cerr << "\rLUT798   ";
    Ciphertext gin798 = 2 * gout746 + gout797;
    Ciphertext gout798 = ctx.eval_lut(&gin798, xnor2);

    auto gin798clear = 2 * gout746clear + gout797clear;
    auto gout798clear = fxnor2(gin798clear, 4);

    assert(ctx.decrypt(&gout798) == gout798clear);
    std::cerr << "\rLUT799   ";
    Ciphertext gin799 = 2 * (1 - gout792) + gout745;
    Ciphertext gout799 = ctx.eval_lut(&gin799, and2);

    auto gin799clear = 2 * (1 - gout792clear) + gout745clear;
    auto gout799clear = fand2(gin799clear, 4);

    assert(ctx.decrypt(&gout799) == gout799clear);
    std::cerr << "\rLUT800   ";
    Ciphertext gin800 = 2 * gout791 + gout750;
    Ciphertext gout800 = ctx.eval_lut(&gin800, nand2);

    auto gin800clear = 2 * gout791clear + gout750clear;
    auto gout800clear = fnand2(gin800clear, 4);

    assert(ctx.decrypt(&gout800) == gout800clear);
    std::cerr << "\rLUT801   ";
    Ciphertext gin801 = 2 * gout800 + (1 - gout799);
    Ciphertext gout801 = ctx.eval_lut(&gin801, and2);

    auto gin801clear = 2 * gout800clear + (1 - gout799clear);
    auto gout801clear = fand2(gin801clear, 4);

    assert(ctx.decrypt(&gout801) == gout801clear);
    std::cerr << "\rLUT802   ";
    Ciphertext gin802 = 2 * gout801 + gout757;
    Ciphertext gout802 = ctx.eval_lut(&gin802, xnor2);

    auto gin802clear = 2 * gout801clear + gout757clear;
    auto gout802clear = fxnor2(gin802clear, 4);

    assert(ctx.decrypt(&gout802) == gout802clear);
    std::cerr << "\rLUT803   ";
    Ciphertext gin803 = 2 * gout802 + gout798;
    Ciphertext gout803 = ctx.eval_lut(&gin803, xnor2);

    auto gin803clear = 2 * gout802clear + gout798clear;
    auto gout803clear = fxnor2(gin803clear, 4);

    assert(ctx.decrypt(&gout803) == gout803clear);
    std::cerr << "\rLUT804   ";
    Ciphertext gin804 = 2 * gout198 + gout483;
    Ciphertext gout804 = ctx.eval_lut(&gin804, xnor2);

    auto gin804clear = 2 * gout198clear + gout483clear;
    auto gout804clear = fxnor2(gin804clear, 4);

    assert(ctx.decrypt(&gout804) == gout804clear);
    std::cerr << "\rLUT805   ";
    Ciphertext gin805 = 2 * gout310 + gout804;
    Ciphertext gout805 = ctx.eval_lut(&gin805, xnor2);

    auto gin805clear = 2 * gout310clear + gout804clear;
    auto gout805clear = fxnor2(gin805clear, 4);

    assert(ctx.decrypt(&gout805) == gout805clear);
    std::cerr << "\rLUT806   ";
    Ciphertext gin806 = 2 * gout737 + gout805;
    Ciphertext gout806 = ctx.eval_lut(&gin806, or2);

    auto gin806clear = 2 * gout737clear + gout805clear;
    auto gout806clear = for2(gin806clear, 4);

    assert(ctx.decrypt(&gout806) == gout806clear);
    std::cerr << "\rLUT807   ";
    Ciphertext gin807 = 2 * gout115 + gout806;
    Ciphertext gout807 = ctx.eval_lut(&gin807, and2);

    auto gin807clear = 2 * gout115clear + gout806clear;
    auto gout807clear = fand2(gin807clear, 4);

    assert(ctx.decrypt(&gout807) == gout807clear);
    std::cerr << "\rLUT808   ";
    Ciphertext gin808 = 2 * gout737 + gout805;
    Ciphertext gout808 = ctx.eval_lut(&gin808, nand2);

    auto gin808clear = 2 * gout737clear + gout805clear;
    auto gout808clear = fnand2(gin808clear, 4);

    assert(ctx.decrypt(&gout808) == gout808clear);
    std::cerr << "\rLUT809   ";
    Ciphertext gin809 = 2 * gout808 + gout807;
    Ciphertext gout809 = ctx.eval_lut(&gin809, nand2);

    auto gin809clear = 2 * gout808clear + gout807clear;
    auto gout809clear = fnand2(gin809clear, 4);

    assert(ctx.decrypt(&gout809) == gout809clear);
    std::cerr << "\rINV810   ";
    Ciphertext gout810 = 1 - gout805;

    long gout810clear = 1 - gout805clear;

    assert(ctx.decrypt(&gout810) == gout810clear);
    std::cerr << "\rLUT811   ";
    Ciphertext gin811 = 2 * gout736 + gout810;
    Ciphertext gout811 = ctx.eval_lut(&gin811, or2);

    auto gin811clear = 2 * gout736clear + gout810clear;
    auto gout811clear = for2(gin811clear, 4);

    assert(ctx.decrypt(&gout811) == gout811clear);
    std::cerr << "\rLUT812   ";
    Ciphertext gin812 = 2 * ct_x9 + gout804;
    Ciphertext gout812 = ctx.eval_lut(&gin812, or2);

    auto gin812clear = 2 * ct_x9clear + gout804clear;
    auto gout812clear = for2(gin812clear, 4);

    assert(ctx.decrypt(&gout812) == gout812clear);
    std::cerr << "\rLUT813   ";
    Ciphertext gin813 = 2 * ct_x9 + gout804;
    Ciphertext gout813 = ctx.eval_lut(&gin813, nand2);

    auto gin813clear = 2 * ct_x9clear + gout804clear;
    auto gout813clear = fnand2(gin813clear, 4);

    assert(ctx.decrypt(&gout813) == gout813clear);
    std::cerr << "\rLUT814   ";
    Ciphertext gin814 = 2 * gout487 + gout813;
    Ciphertext gout814 = ctx.eval_lut(&gin814, nand2);

    auto gin814clear = 2 * gout487clear + gout813clear;
    auto gout814clear = fnand2(gin814clear, 4);

    assert(ctx.decrypt(&gout814) == gout814clear);
    std::cerr << "\rLUT815   ";
    Ciphertext gin815 = 2 * gout812 + gout814;
    Ciphertext gout815 = ctx.eval_lut(&gin815, nand2);

    auto gin815clear = 2 * gout812clear + gout814clear;
    auto gout815clear = fnand2(gin815clear, 4);

    assert(ctx.decrypt(&gout815) == gout815clear);
    std::cerr << "\rLUT816   ";
    Ciphertext gin816 = 2 * gout811 + gout815;
    Ciphertext gout816 = ctx.eval_lut(&gin816, nand2);

    auto gin816clear = 2 * gout811clear + gout815clear;
    auto gout816clear = fnand2(gin816clear, 4);

    assert(ctx.decrypt(&gout816) == gout816clear);
    std::cerr << "\rLUT817   ";
    Ciphertext gin817 = 2 * gout816 + gout479;
    Ciphertext gout817 = ctx.eval_lut(&gin817, xnor2);

    auto gin817clear = 2 * gout816clear + gout479clear;
    auto gout817clear = fxnor2(gin817clear, 4);

    assert(ctx.decrypt(&gout817) == gout817clear);
    std::cerr << "\rLUT818   ";
    Ciphertext gin818 = 2 * gout816 + gout479;
    Ciphertext gout818 = ctx.eval_lut(&gin818, nand2);

    auto gin818clear = 2 * gout816clear + gout479clear;
    auto gout818clear = fnand2(gin818clear, 4);

    assert(ctx.decrypt(&gout818) == gout818clear);
    std::cerr << "\rLUT819   ";
    Ciphertext gin819 = 2 * gout818 + gout474;
    Ciphertext gout819 = ctx.eval_lut(&gin819, or2);

    auto gin819clear = 2 * gout818clear + gout474clear;
    auto gout819clear = for2(gin819clear, 4);

    assert(ctx.decrypt(&gout819) == gout819clear);
    std::cerr << "\rLUT820   ";
    Ciphertext gin820 = 2 * gout819 + gout482;
    Ciphertext gout820 = ctx.eval_lut(&gin820, nand2);

    auto gin820clear = 2 * gout819clear + gout482clear;
    auto gout820clear = fnand2(gin820clear, 4);

    assert(ctx.decrypt(&gout820) == gout820clear);
    std::cerr << "\rLUT821   ";
    Ciphertext gin821 = 2 * gout820 + gout468;
    Ciphertext gout821 = ctx.eval_lut(&gin821, xnor2);

    auto gin821clear = 2 * gout820clear + gout468clear;
    auto gout821clear = fxnor2(gin821clear, 4);

    assert(ctx.decrypt(&gout821) == gout821clear);
    std::cerr << "\rLUT822   ";
    Ciphertext gin822 = 2 * gout820 + gout468;
    Ciphertext gout822 = ctx.eval_lut(&gin822, nand2);

    auto gin822clear = 2 * gout820clear + gout468clear;
    auto gout822clear = fnand2(gin822clear, 4);

    assert(ctx.decrypt(&gout822) == gout822clear);
    std::cerr << "\rLUT823   ";
    Ciphertext gin823 = 2 * gout822 + gout464;
    Ciphertext gout823 = ctx.eval_lut(&gin823, or2);

    auto gin823clear = 2 * gout822clear + gout464clear;
    auto gout823clear = for2(gin823clear, 4);

    assert(ctx.decrypt(&gout823) == gout823clear);
    std::cerr << "\rLUT824   ";
    Ciphertext gin824 = 2 * gout823 + gout471;
    Ciphertext gout824 = ctx.eval_lut(&gin824, nand2);

    auto gin824clear = 2 * gout823clear + gout471clear;
    auto gout824clear = fnand2(gin824clear, 4);

    assert(ctx.decrypt(&gout824) == gout824clear);
    std::cerr << "\rLUT825   ";
    Ciphertext gin825 = 2 * gout824 + gout460;
    Ciphertext gout825 = ctx.eval_lut(&gin825, xnor2);

    auto gin825clear = 2 * gout824clear + gout460clear;
    auto gout825clear = fxnor2(gin825clear, 4);

    assert(ctx.decrypt(&gout825) == gout825clear);
    std::cerr << "\rLUT826   ";
    Ciphertext gin826 = 2 * gout824 + gout460;
    Ciphertext gout826 = ctx.eval_lut(&gin826, nand2);

    auto gin826clear = 2 * gout824clear + gout460clear;
    auto gout826clear = fnand2(gin826clear, 4);

    assert(ctx.decrypt(&gout826) == gout826clear);
    std::cerr << "\rLUT827   ";
    Ciphertext gin827 = 2 * gout461 + gout826;
    Ciphertext gout827 = ctx.eval_lut(&gin827, and2);

    auto gin827clear = 2 * gout461clear + gout826clear;
    auto gout827clear = fand2(gin827clear, 4);

    assert(ctx.decrypt(&gout827) == gout827clear);
    std::cerr << "\rLUT828   ";
    Ciphertext gin828 = 2 * gout827 + gout458;
    Ciphertext gout828 = ctx.eval_lut(&gin828, or2);

    auto gin828clear = 2 * gout827clear + gout458clear;
    auto gout828clear = for2(gin828clear, 4);

    assert(ctx.decrypt(&gout828) == gout828clear);
    std::cerr << "\rLUT829   ";
    Ciphertext gin829 = 2 * gout115 + gout828;
    Ciphertext gout829 = ctx.eval_lut(&gin829, and2);

    auto gin829clear = 2 * gout115clear + gout828clear;
    auto gout829clear = fand2(gin829clear, 4);

    assert(ctx.decrypt(&gout829) == gout829clear);
    std::cerr << "\rLUT830   ";
    Ciphertext gin830 = 2 * gout827 + gout458;
    Ciphertext gout830 = ctx.eval_lut(&gin830, nand2);

    auto gin830clear = 2 * gout827clear + gout458clear;
    auto gout830clear = fnand2(gin830clear, 4);

    assert(ctx.decrypt(&gout830) == gout830clear);
    std::cerr << "\rLUT831   ";
    Ciphertext gin831 = 2 * gout830 + gout829;
    Ciphertext gout831 = ctx.eval_lut(&gin831, nand2);

    auto gin831clear = 2 * gout830clear + gout829clear;
    auto gout831clear = fnand2(gin831clear, 4);

    assert(ctx.decrypt(&gout831) == gout831clear);
    std::cerr << "\rLUT832   ";
    Ciphertext gin832 = 2 * gout218 + gout831;
    Ciphertext gout832 = ctx.eval_lut(&gin832, and2);

    auto gin832clear = 2 * gout218clear + gout831clear;
    auto gout832clear = fand2(gin832clear, 4);

    assert(ctx.decrypt(&gout832) == gout832clear);
    std::cerr << "\rLUT833   ";
    Ciphertext gin833 = 2 * gout469 + gout822;
    Ciphertext gout833 = ctx.eval_lut(&gin833, nand2);

    auto gin833clear = 2 * gout469clear + gout822clear;
    auto gout833clear = fnand2(gin833clear, 4);

    assert(ctx.decrypt(&gout833) == gout833clear);
    std::cerr << "\rLUT834   ";
    Ciphertext gin834 = 2 * gout833 + gout463;
    Ciphertext gout834 = ctx.eval_lut(&gin834, or2);

    auto gin834clear = 2 * gout833clear + gout463clear;
    auto gout834clear = for2(gin834clear, 4);

    assert(ctx.decrypt(&gout834) == gout834clear);
    std::cerr << "\rLUT835   ";
    Ciphertext gin835 = 2 * gout115 + gout834;
    Ciphertext gout835 = ctx.eval_lut(&gin835, and2);

    auto gin835clear = 2 * gout115clear + gout834clear;
    auto gout835clear = fand2(gin835clear, 4);

    assert(ctx.decrypt(&gout835) == gout835clear);
    std::cerr << "\rLUT836   ";
    Ciphertext gin836 = 2 * gout833 + gout463;
    Ciphertext gout836 = ctx.eval_lut(&gin836, nand2);

    auto gin836clear = 2 * gout833clear + gout463clear;
    auto gout836clear = fnand2(gin836clear, 4);

    assert(ctx.decrypt(&gout836) == gout836clear);
    std::cerr << "\rLUT837   ";
    Ciphertext gin837 = 2 * gout836 + gout835;
    Ciphertext gout837 = ctx.eval_lut(&gin837, nand2);

    auto gin837clear = 2 * gout836clear + gout835clear;
    auto gout837clear = fnand2(gin837clear, 4);

    assert(ctx.decrypt(&gout837) == gout837clear);
    std::cerr << "\rLUT838   ";
    Ciphertext gin838 = 2 * gout480 + gout818;
    Ciphertext gout838 = ctx.eval_lut(&gin838, nand2);

    auto gin838clear = 2 * gout480clear + gout818clear;
    auto gout838clear = fnand2(gin838clear, 4);

    assert(ctx.decrypt(&gout838) == gout838clear);
    std::cerr << "\rLUT839   ";
    Ciphertext gin839 = 2 * gout838 + gout473;
    Ciphertext gout839 = ctx.eval_lut(&gin839, or2);

    auto gin839clear = 2 * gout838clear + gout473clear;
    auto gout839clear = for2(gin839clear, 4);

    assert(ctx.decrypt(&gout839) == gout839clear);
    std::cerr << "\rLUT840   ";
    Ciphertext gin840 = 2 * gout115 + gout839;
    Ciphertext gout840 = ctx.eval_lut(&gin840, and2);

    auto gin840clear = 2 * gout115clear + gout839clear;
    auto gout840clear = fand2(gin840clear, 4);

    assert(ctx.decrypt(&gout840) == gout840clear);
    std::cerr << "\rLUT841   ";
    Ciphertext gin841 = 2 * gout838 + gout473;
    Ciphertext gout841 = ctx.eval_lut(&gin841, nand2);

    auto gin841clear = 2 * gout838clear + gout473clear;
    auto gout841clear = fnand2(gin841clear, 4);

    assert(ctx.decrypt(&gout841) == gout841clear);
    std::cerr << "\rLUT842   ";
    Ciphertext gin842 = 2 * gout841 + gout840;
    Ciphertext gout842 = ctx.eval_lut(&gin842, nand2);

    auto gin842clear = 2 * gout841clear + gout840clear;
    auto gout842clear = fnand2(gin842clear, 4);

    assert(ctx.decrypt(&gout842) == gout842clear);
    std::cerr << "\rLUT843   ";
    Ciphertext gin843 = 2 * gout201 + gout433;
    Ciphertext gout843 = ctx.eval_lut(&gin843, nand2);

    auto gin843clear = 2 * gout201clear + gout433clear;
    auto gout843clear = fnand2(gin843clear, 4);

    assert(ctx.decrypt(&gout843) == gout843clear);
    std::cerr << "\rLUT844   ";
    Ciphertext gin844 = 2 * gout377 + gout843;
    Ciphertext gout844 = ctx.eval_lut(&gin844, nand2);

    auto gin844clear = 2 * gout377clear + gout843clear;
    auto gout844clear = fnand2(gin844clear, 4);

    assert(ctx.decrypt(&gout844) == gout844clear);
    std::cerr << "\rLUT845   ";
    Ciphertext gin845 = 2 * gout844 + gout445;
    Ciphertext gout845 = ctx.eval_lut(&gin845, xor2);

    auto gin845clear = 2 * gout844clear + gout445clear;
    auto gout845clear = fxor2(gin845clear, 4);

    assert(ctx.decrypt(&gout845) == gout845clear);
    std::cerr << "\rLUT846   ";
    Ciphertext gin846 = 2 * gout691 + gout845;
    Ciphertext gout846 = ctx.eval_lut(&gin846, xnor2);

    auto gin846clear = 2 * gout691clear + gout845clear;
    auto gout846clear = fxnor2(gin846clear, 4);

    assert(ctx.decrypt(&gout846) == gout846clear);
    std::cerr << "\rLUT847   ";
    Ciphertext gin847 = 2 * gout683 + gout846;
    Ciphertext gout847 = ctx.eval_lut(&gin847, xor2);

    auto gin847clear = 2 * gout683clear + gout846clear;
    auto gout847clear = fxor2(gin847clear, 4);

    assert(ctx.decrypt(&gout847) == gout847clear);
    std::cerr << "\rLUT848   ";
    Ciphertext gin848 = 2 * gout583 + gout847;
    Ciphertext gout848 = ctx.eval_lut(&gin848, xor2);

    auto gin848clear = 2 * gout583clear + gout847clear;
    auto gout848clear = fxor2(gin848clear, 4);

    assert(ctx.decrypt(&gout848) == gout848clear);
    std::cerr << "\rLUT849   ";
    Ciphertext gin849 = 2 * gout670 + gout848;
    Ciphertext gout849 = ctx.eval_lut(&gin849, xnor2);

    auto gin849clear = 2 * gout670clear + gout848clear;
    auto gout849clear = fxnor2(gin849clear, 4);

    assert(ctx.decrypt(&gout849) == gout849clear);
    std::cerr << "\rLUT850   ";
    Ciphertext gin850 = 2 * gout680 + gout849;
    Ciphertext gout850 = ctx.eval_lut(&gin850, xnor2);

    auto gin850clear = 2 * gout680clear + gout849clear;
    auto gout850clear = fxnor2(gin850clear, 4);

    assert(ctx.decrypt(&gout850) == gout850clear);
    std::cerr << "\rLUT851   ";
    Ciphertext gin851 = 2 * gout850 + gout678;
    Ciphertext gout851 = ctx.eval_lut(&gin851, xnor2);

    auto gin851clear = 2 * gout850clear + gout678clear;
    auto gout851clear = fxnor2(gin851clear, 4);

    assert(ctx.decrypt(&gout851) == gout851clear);
    std::cerr << "\rIMUX852  ";
    Ciphertext gin852A = 2 * gout851 + gout104;
    Ciphertext gout852A = ctx.eval_lut(&gin852A, and2);
    Ciphertext gin852B = 2 * gout732 + (1 - gout104);
    Ciphertext gout852B = ctx.eval_lut(&gin852B, and2);
    Ciphertext gout852 = gout852A + gout852B;

    long gin852Aclear = 2 * gout851clear + gout104clear;
    long gout852Aclear = fand2(gin852Aclear, 4);
    long gin852Bclear = 2 * gout732clear + (1 - gout104clear);
    long gout852Bclear = fand2(gin852Bclear, 4);
    long gout852clear = gout852Aclear + gout852Bclear;

    assert(ctx.decrypt(&gout852) == gout852clear);
    std::cerr << "\rLUT853   ";
    Ciphertext gin853 = 2 * gout218 + gout852;
    Ciphertext gout853 = ctx.eval_lut(&gin853, nand2);

    auto gin853clear = 2 * gout218clear + gout852clear;
    auto gout853clear = fnand2(gin853clear, 4);

    assert(ctx.decrypt(&gout853) == gout853clear);
    std::cerr << "\rLUT854   ";
    Ciphertext gin854 = 2 * gout850 + gout678;
    Ciphertext gout854 = ctx.eval_lut(&gin854, and2);

    auto gin854clear = 2 * gout850clear + gout678clear;
    auto gout854clear = fand2(gin854clear, 4);

    assert(ctx.decrypt(&gout854) == gout854clear);
    std::cerr << "\rLUT855   ";
    Ciphertext gin855 = 2 * gout679 + gout849;
    Ciphertext gout855 = ctx.eval_lut(&gin855, nand2);

    auto gin855clear = 2 * gout679clear + gout849clear;
    auto gout855clear = fnand2(gin855clear, 4);

    assert(ctx.decrypt(&gout855) == gout855clear);
    std::cerr << "\rLUT856   ";
    Ciphertext gin856 = 2 * gout669 + gout848;
    Ciphertext gout856 = ctx.eval_lut(&gin856, and2);

    auto gin856clear = 2 * gout669clear + gout848clear;
    auto gout856clear = fand2(gin856clear, 4);

    assert(ctx.decrypt(&gout856) == gout856clear);
    std::cerr << "\rINV857   ";
    Ciphertext gout857 = 1 - gout856;

    long gout857clear = 1 - gout856clear;

    assert(ctx.decrypt(&gout857) == gout857clear);
    std::cerr << "\rLUT858   ";
    Ciphertext gin858 = 2 * gout857 + gout855;
    Ciphertext gout858 = ctx.eval_lut(&gin858, and2);

    auto gin858clear = 2 * gout857clear + gout855clear;
    auto gout858clear = fand2(gin858clear, 4);

    assert(ctx.decrypt(&gout858) == gout858clear);
    std::cerr << "\rLUT859   ";
    Ciphertext gin859 = 2 * gout583 + gout847;
    Ciphertext gout859 = ctx.eval_lut(&gin859, nand2);

    auto gin859clear = 2 * gout583clear + gout847clear;
    auto gout859clear = fnand2(gin859clear, 4);

    assert(ctx.decrypt(&gout859) == gout859clear);
    std::cerr << "\rLUT860   ";
    Ciphertext gin860 = 2 * gout683 + gout846;
    Ciphertext gout860 = ctx.eval_lut(&gin860, nand2);

    auto gin860clear = 2 * gout683clear + gout846clear;
    auto gout860clear = fnand2(gin860clear, 4);

    assert(ctx.decrypt(&gout860) == gout860clear);
    std::cerr << "\rLUT861   ";
    Ciphertext gin861 = 2 * gout860 + gout859;
    Ciphertext gout861 = ctx.eval_lut(&gin861, nand2);

    auto gin861clear = 2 * gout860clear + gout859clear;
    auto gout861clear = fnand2(gin861clear, 4);

    assert(ctx.decrypt(&gout861) == gout861clear);
    std::cerr << "\rLUT862   ";
    Ciphertext gin862 = 2 * (1 - gout691) + gout845;
    Ciphertext gout862 = ctx.eval_lut(&gin862, and2);

    auto gin862clear = 2 * (1 - gout691clear) + gout845clear;
    auto gout862clear = fand2(gin862clear, 4);

    assert(ctx.decrypt(&gout862) == gout862clear);
    std::cerr << "\rLUT863   ";
    Ciphertext gin863 = 2 * gout692 + gout862;
    Ciphertext gout863 = ctx.eval_lut(&gin863, or2);

    auto gin863clear = 2 * gout692clear + gout862clear;
    auto gout863clear = for2(gin863clear, 4);

    assert(ctx.decrypt(&gout863) == gout863clear);
    std::cerr << "\rLUT864   ";
    Ciphertext gin864 = 2 * gout863 + gout697;
    Ciphertext gout864 = ctx.eval_lut(&gin864, xor2);

    auto gin864clear = 2 * gout863clear + gout697clear;
    auto gout864clear = fxor2(gin864clear, 4);

    assert(ctx.decrypt(&gout864) == gout864clear);
    std::cerr << "\rLUT865   ";
    Ciphertext gin865 = 2 * gout863 + gout697;
    Ciphertext gout865 = ctx.eval_lut(&gin865, nand2);

    auto gin865clear = 2 * gout863clear + gout697clear;
    auto gout865clear = fnand2(gin865clear, 4);

    assert(ctx.decrypt(&gout865) == gout865clear);
    std::cerr << "\rLUT866   ";
    Ciphertext gin866 = 2 * gout844 + gout445;
    Ciphertext gout866 = ctx.eval_lut(&gin866, and2);

    auto gin866clear = 2 * gout844clear + gout445clear;
    auto gout866clear = fand2(gin866clear, 4);

    assert(ctx.decrypt(&gout866) == gout866clear);
    std::cerr << "\rLUT867   ";
    Ciphertext gin867 = 2 * gout866 + gout864;
    Ciphertext gout867 = ctx.eval_lut(&gin867, xor2);

    auto gin867clear = 2 * gout866clear + gout864clear;
    auto gout867clear = fxor2(gin867clear, 4);

    assert(ctx.decrypt(&gout867) == gout867clear);
    std::cerr << "\rLUT868   ";
    Ciphertext gin868 = 2 * gout861 + gout867;
    Ciphertext gout868 = ctx.eval_lut(&gin868, xor2);

    auto gin868clear = 2 * gout861clear + gout867clear;
    auto gout868clear = fxor2(gin868clear, 4);

    assert(ctx.decrypt(&gout868) == gout868clear);
    std::cerr << "\rLUT869   ";
    Ciphertext gin869 = 2 * gout856 + gout868;
    Ciphertext gout869 = ctx.eval_lut(&gin869, and2);

    auto gin869clear = 2 * gout856clear + gout868clear;
    auto gout869clear = fand2(gin869clear, 4);

    assert(ctx.decrypt(&gout869) == gout869clear);
    std::cerr << "\rLUT870   ";
    Ciphertext gin870 = 2 * gout855 + (1 - gout868);
    Ciphertext gout870 = ctx.eval_lut(&gin870, or2);

    auto gin870clear = 2 * gout855clear + (1 - gout868clear);
    auto gout870clear = for2(gin870clear, 4);

    assert(ctx.decrypt(&gout870) == gout870clear);
    std::cerr << "\rLUT871   ";
    Ciphertext gin871 = 2 * gout868 + gout858;
    Ciphertext gout871 = ctx.eval_lut(&gin871, xnor2);

    auto gin871clear = 2 * gout868clear + gout858clear;
    auto gout871clear = fxnor2(gin871clear, 4);

    assert(ctx.decrypt(&gout871) == gout871clear);
    std::cerr << "\rLUT872   ";
    Ciphertext gin872 = 2 * gout854 + gout871;
    Ciphertext gout872 = ctx.eval_lut(&gin872, xnor2);

    auto gin872clear = 2 * gout854clear + gout871clear;
    auto gout872clear = fxnor2(gin872clear, 4);

    assert(ctx.decrypt(&gout872) == gout872clear);
    std::cerr << "\rIMUX873  ";
    Ciphertext gin873A = 2 * gout872 + gout104;
    Ciphertext gout873A = ctx.eval_lut(&gin873A, and2);
    Ciphertext gin873B = 2 * gout735 + (1 - gout104);
    Ciphertext gout873B = ctx.eval_lut(&gin873B, and2);
    Ciphertext gout873 = gout873A + gout873B;

    long gin873Aclear = 2 * gout872clear + gout104clear;
    long gout873Aclear = fand2(gin873Aclear, 4);
    long gin873Bclear = 2 * gout735clear + (1 - gout104clear);
    long gout873Bclear = fand2(gin873Bclear, 4);
    long gout873clear = gout873Aclear + gout873Bclear;

    assert(ctx.decrypt(&gout873) == gout873clear);
    std::cerr << "\rLUT874   ";
    Ciphertext gin874 = 2 * gout218 + gout873;
    Ciphertext gout874 = ctx.eval_lut(&gin874, nand2);

    auto gin874clear = 2 * gout218clear + gout873clear;
    auto gout874clear = fnand2(gin874clear, 4);

    assert(ctx.decrypt(&gout874) == gout874clear);
    std::cerr << "\rLUT875   ";
    Ciphertext gin875 = 2 * gout854 + gout871;
    Ciphertext gout875 = ctx.eval_lut(&gin875, nand2);

    auto gin875clear = 2 * gout854clear + gout871clear;
    auto gout875clear = fnand2(gin875clear, 4);

    assert(ctx.decrypt(&gout875) == gout875clear);
    std::cerr << "\rLUT876   ";
    Ciphertext gin876 = 2 * gout875 + gout870;
    Ciphertext gout876 = ctx.eval_lut(&gin876, and2);

    auto gin876clear = 2 * gout875clear + gout870clear;
    auto gout876clear = fand2(gin876clear, 4);

    assert(ctx.decrypt(&gout876) == gout876clear);
    std::cerr << "\rLUT877   ";
    Ciphertext gin877 = 2 * gout861 + gout867;
    Ciphertext gout877 = ctx.eval_lut(&gin877, and2);

    auto gin877clear = 2 * gout861clear + gout867clear;
    auto gout877clear = fand2(gin877clear, 4);

    assert(ctx.decrypt(&gout877) == gout877clear);
    std::cerr << "\rLUT878   ";
    Ciphertext gin878 = 2 * gout866 + gout864;
    Ciphertext gout878 = ctx.eval_lut(&gin878, nand2);

    auto gin878clear = 2 * gout866clear + gout864clear;
    auto gout878clear = fnand2(gin878clear, 4);

    assert(ctx.decrypt(&gout878) == gout878clear);
    std::cerr << "\rLUT879   ";
    Ciphertext gin879 = 2 * gout865 + gout878;
    Ciphertext gout879 = ctx.eval_lut(&gin879, nand2);

    auto gin879clear = 2 * gout865clear + gout878clear;
    auto gout879clear = fnand2(gin879clear, 4);

    assert(ctx.decrypt(&gout879) == gout879clear);
    std::cerr << "\rLUT880   ";
    Ciphertext gin880 = 2 * gout879 + gout702;
    Ciphertext gout880 = ctx.eval_lut(&gin880, xor2);

    auto gin880clear = 2 * gout879clear + gout702clear;
    auto gout880clear = fxor2(gin880clear, 4);

    assert(ctx.decrypt(&gout880) == gout880clear);
    std::cerr << "\rLUT881   ";
    Ciphertext gin881 = 2 * gout877 + gout880;
    Ciphertext gout881 = ctx.eval_lut(&gin881, xor2);

    auto gin881clear = 2 * gout877clear + gout880clear;
    auto gout881clear = fxor2(gin881clear, 4);

    assert(ctx.decrypt(&gout881) == gout881clear);
    std::cerr << "\rLUT882   ";
    Ciphertext gin882 = 2 * gout869 + gout881;
    Ciphertext gout882 = ctx.eval_lut(&gin882, xnor2);

    auto gin882clear = 2 * gout869clear + gout881clear;
    auto gout882clear = fxnor2(gin882clear, 4);

    assert(ctx.decrypt(&gout882) == gout882clear);
    std::cerr << "\rLUT883   ";
    Ciphertext gin883 = 2 * gout876 + gout882;
    Ciphertext gout883 = ctx.eval_lut(&gin883, or2);

    auto gin883clear = 2 * gout876clear + gout882clear;
    auto gout883clear = for2(gin883clear, 4);

    assert(ctx.decrypt(&gout883) == gout883clear);
    std::cerr << "\rLUT884   ";
    Ciphertext gin884 = 2 * gout104 + gout883;
    Ciphertext gout884 = ctx.eval_lut(&gin884, and2);

    auto gin884clear = 2 * gout104clear + gout883clear;
    auto gout884clear = fand2(gin884clear, 4);

    assert(ctx.decrypt(&gout884) == gout884clear);
    std::cerr << "\rLUT885   ";
    Ciphertext gin885 = 2 * gout876 + gout882;
    Ciphertext gout885 = ctx.eval_lut(&gin885, nand2);

    auto gin885clear = 2 * gout876clear + gout882clear;
    auto gout885clear = fnand2(gin885clear, 4);

    assert(ctx.decrypt(&gout885) == gout885clear);
    std::cerr << "\rLUT886   ";
    Ciphertext gin886 = 2 * gout885 + gout884;
    Ciphertext gout886 = ctx.eval_lut(&gin886, nand2);

    auto gin886clear = 2 * gout885clear + gout884clear;
    auto gout886clear = fnand2(gin886clear, 4);

    assert(ctx.decrypt(&gout886) == gout886clear);
    std::cerr << "\rLUT887   ";
    Ciphertext gin887 = 2 * gout218 + gout886;
    Ciphertext gout887 = ctx.eval_lut(&gin887, and2);

    auto gin887clear = 2 * gout218clear + gout886clear;
    auto gout887clear = fand2(gin887clear, 4);

    assert(ctx.decrypt(&gout887) == gout887clear);
    std::cerr << "\rLUT888   ";
    Ciphertext gin888 = 2 * gout809 + gout887;
    Ciphertext gout888 = ctx.eval_lut(&gin888, nand2);

    auto gin888clear = 2 * gout809clear + gout887clear;
    auto gout888clear = fnand2(gin888clear, 4);

    assert(ctx.decrypt(&gout888) == gout888clear);
    std::cerr << "\rLUT889   ";
    Ciphertext gin889 = 2 * gout869 + gout881;
    Ciphertext gout889 = ctx.eval_lut(&gin889, nand2);

    auto gin889clear = 2 * gout869clear + gout881clear;
    auto gout889clear = fnand2(gin889clear, 4);

    assert(ctx.decrypt(&gout889) == gout889clear);
    std::cerr << "\rLUT890   ";
    Ciphertext gin890 = 2 * gout889 + gout883;
    Ciphertext gout890 = ctx.eval_lut(&gin890, nand2);

    auto gin890clear = 2 * gout889clear + gout883clear;
    auto gout890clear = fnand2(gin890clear, 4);

    assert(ctx.decrypt(&gout890) == gout890clear);
    std::cerr << "\rLUT891   ";
    Ciphertext gin891 = 2 * gout877 + gout880;
    Ciphertext gout891 = ctx.eval_lut(&gin891, and2);

    auto gin891clear = 2 * gout877clear + gout880clear;
    auto gout891clear = fand2(gin891clear, 4);

    assert(ctx.decrypt(&gout891) == gout891clear);
    std::cerr << "\rLUT892   ";
    Ciphertext gin892 = 2 * gout879 + gout702;
    Ciphertext gout892 = ctx.eval_lut(&gin892, and2);

    auto gin892clear = 2 * gout879clear + gout702clear;
    auto gout892clear = fand2(gin892clear, 4);

    assert(ctx.decrypt(&gout892) == gout892clear);
    std::cerr << "\rLUT893   ";
    Ciphertext gin893 = 2 * gout892 + gout707;
    Ciphertext gout893 = ctx.eval_lut(&gin893, and2);

    auto gin893clear = 2 * gout892clear + gout707clear;
    auto gout893clear = fand2(gin893clear, 4);

    assert(ctx.decrypt(&gout893) == gout893clear);
    std::cerr << "\rLUT894   ";
    Ciphertext gin894 = 2 * gout893 + gout711;
    Ciphertext gout894 = ctx.eval_lut(&gin894, nand2);

    auto gin894clear = 2 * gout893clear + gout711clear;
    auto gout894clear = fnand2(gin894clear, 4);

    assert(ctx.decrypt(&gout894) == gout894clear);
    std::cerr << "\rINV895   ";
    Ciphertext gout895 = 1 - gout893;

    long gout895clear = 1 - gout893clear;

    assert(ctx.decrypt(&gout895) == gout895clear);
    std::cerr << "\rLUT896   ";
    Ciphertext gin896 = 2 * gout895 + gout711;
    Ciphertext gout896 = ctx.eval_lut(&gin896, xnor2);

    auto gin896clear = 2 * gout895clear + gout711clear;
    auto gout896clear = fxnor2(gin896clear, 4);

    assert(ctx.decrypt(&gout896) == gout896clear);
    std::cerr << "\rINV897   ";
    Ciphertext gout897 = 1 - gout892;

    long gout897clear = 1 - gout892clear;

    assert(ctx.decrypt(&gout897) == gout897clear);
    std::cerr << "\rLUT898   ";
    Ciphertext gin898 = 2 * gout897 + gout707;
    Ciphertext gout898 = ctx.eval_lut(&gin898, xnor2);

    auto gin898clear = 2 * gout897clear + gout707clear;
    auto gout898clear = fxnor2(gin898clear, 4);

    assert(ctx.decrypt(&gout898) == gout898clear);
    std::cerr << "\rLUT899   ";
    Ciphertext gin899 = 2 * gout891 + gout898;
    Ciphertext gout899 = ctx.eval_lut(&gin899, xor2);

    auto gin899clear = 2 * gout891clear + gout898clear;
    auto gout899clear = fxor2(gin899clear, 4);

    assert(ctx.decrypt(&gout899) == gout899clear);
    std::cerr << "\rLUT900   ";
    Ciphertext gin900 = 2 * gout890 + gout899;
    Ciphertext gout900 = ctx.eval_lut(&gin900, xnor2);

    auto gin900clear = 2 * gout890clear + gout899clear;
    auto gout900clear = fxnor2(gin900clear, 4);

    assert(ctx.decrypt(&gout900) == gout900clear);
    std::cerr << "\rIMUX901  ";
    Ciphertext gin901A = 2 * gout900 + gout104;
    Ciphertext gout901A = ctx.eval_lut(&gin901A, and2);
    Ciphertext gin901B = 2 * gout817 + (1 - gout104);
    Ciphertext gout901B = ctx.eval_lut(&gin901B, and2);
    Ciphertext gout901 = gout901A + gout901B;

    long gin901Aclear = 2 * gout900clear + gout104clear;
    long gout901Aclear = fand2(gin901Aclear, 4);
    long gin901Bclear = 2 * gout817clear + (1 - gout104clear);
    long gout901Bclear = fand2(gin901Bclear, 4);
    long gout901clear = gout901Aclear + gout901Bclear;

    assert(ctx.decrypt(&gout901) == gout901clear);
    std::cerr << "\rLUT902   ";
    Ciphertext gin902 = 2 * gout218 + gout901;
    Ciphertext gout902 = ctx.eval_lut(&gin902, nand2);

    auto gin902clear = 2 * gout218clear + gout901clear;
    auto gout902clear = fnand2(gin902clear, 4);

    assert(ctx.decrypt(&gout902) == gout902clear);
    std::cerr << "\rLUT903   ";
    Ciphertext gin903 = 2 * gout890 + gout899;
    Ciphertext gout903 = ctx.eval_lut(&gin903, nand2);

    auto gin903clear = 2 * gout890clear + gout899clear;
    auto gout903clear = fnand2(gin903clear, 4);

    assert(ctx.decrypt(&gout903) == gout903clear);
    std::cerr << "\rLUT904   ";
    Ciphertext gin904 = 2 * gout891 + gout898;
    Ciphertext gout904 = ctx.eval_lut(&gin904, nand2);

    auto gin904clear = 2 * gout891clear + gout898clear;
    auto gout904clear = fnand2(gin904clear, 4);

    assert(ctx.decrypt(&gout904) == gout904clear);
    std::cerr << "\rLUT905   ";
    Ciphertext gin905 = 2 * gout904 + gout903;
    Ciphertext gout905 = ctx.eval_lut(&gin905, nand2);

    auto gin905clear = 2 * gout904clear + gout903clear;
    auto gout905clear = fnand2(gin905clear, 4);

    assert(ctx.decrypt(&gout905) == gout905clear);
    std::cerr << "\rLUT906   ";
    Ciphertext gin906 = 2 * gout905 + gout896;
    Ciphertext gout906 = ctx.eval_lut(&gin906, or2);

    auto gin906clear = 2 * gout905clear + gout896clear;
    auto gout906clear = for2(gin906clear, 4);

    assert(ctx.decrypt(&gout906) == gout906clear);
    std::cerr << "\rLUT907   ";
    Ciphertext gin907 = 2 * gout104 + gout906;
    Ciphertext gout907 = ctx.eval_lut(&gin907, and2);

    auto gin907clear = 2 * gout104clear + gout906clear;
    auto gout907clear = fand2(gin907clear, 4);

    assert(ctx.decrypt(&gout907) == gout907clear);
    std::cerr << "\rLUT908   ";
    Ciphertext gin908 = 2 * gout905 + gout896;
    Ciphertext gout908 = ctx.eval_lut(&gin908, nand2);

    auto gin908clear = 2 * gout905clear + gout896clear;
    auto gout908clear = fnand2(gin908clear, 4);

    assert(ctx.decrypt(&gout908) == gout908clear);
    std::cerr << "\rLUT909   ";
    Ciphertext gin909 = 2 * gout894 + gout908;
    Ciphertext gout909 = ctx.eval_lut(&gin909, nand2);

    auto gin909clear = 2 * gout894clear + gout908clear;
    auto gout909clear = fnand2(gin909clear, 4);

    assert(ctx.decrypt(&gout909) == gout909clear);
    std::cerr << "\rLUT910   ";
    Ciphertext gin910 = 2 * gout909 + gout766;
    Ciphertext gout910 = ctx.eval_lut(&gin910, xnor2);

    auto gin910clear = 2 * gout909clear + gout766clear;
    auto gout910clear = fxnor2(gin910clear, 4);

    assert(ctx.decrypt(&gout910) == gout910clear);
    std::cerr << "\rIMUX911  ";
    Ciphertext gin911A = 2 * gout910 + gout104;
    Ciphertext gout911A = ctx.eval_lut(&gin911A, and2);
    Ciphertext gin911B = 2 * gout821 + (1 - gout104);
    Ciphertext gout911B = ctx.eval_lut(&gin911B, and2);
    Ciphertext gout911 = gout911A + gout911B;

    long gin911Aclear = 2 * gout910clear + gout104clear;
    long gout911Aclear = fand2(gin911Aclear, 4);
    long gin911Bclear = 2 * gout821clear + (1 - gout104clear);
    long gout911Bclear = fand2(gin911Bclear, 4);
    long gout911clear = gout911Aclear + gout911Bclear;

    assert(ctx.decrypt(&gout911) == gout911clear);
    std::cerr << "\rLUT912   ";
    Ciphertext gin912 = 2 * gout218 + gout911;
    Ciphertext gout912 = ctx.eval_lut(&gin912, nand2);

    auto gin912clear = 2 * gout218clear + gout911clear;
    auto gout912clear = fnand2(gin912clear, 4);

    assert(ctx.decrypt(&gout912) == gout912clear);
    std::cerr << "\rLUT913   ";
    Ciphertext gin913 = 2 * gout909 + gout766;
    Ciphertext gout913 = ctx.eval_lut(&gin913, nand2);

    auto gin913clear = 2 * gout909clear + gout766clear;
    auto gout913clear = fnand2(gin913clear, 4);

    assert(ctx.decrypt(&gout913) == gout913clear);
    std::cerr << "\rLUT914   ";
    Ciphertext gin914 = 2 * gout767 + gout913;
    Ciphertext gout914 = ctx.eval_lut(&gin914, nand2);

    auto gin914clear = 2 * gout767clear + gout913clear;
    auto gout914clear = fnand2(gin914clear, 4);

    assert(ctx.decrypt(&gout914) == gout914clear);
    std::cerr << "\rLUT915   ";
    Ciphertext gin915 = 2 * gout914 + gout783;
    Ciphertext gout915 = ctx.eval_lut(&gin915, or2);

    auto gin915clear = 2 * gout914clear + gout783clear;
    auto gout915clear = for2(gin915clear, 4);

    assert(ctx.decrypt(&gout915) == gout915clear);
    std::cerr << "\rLUT916   ";
    Ciphertext gin916 = 2 * gout104 + gout915;
    Ciphertext gout916 = ctx.eval_lut(&gin916, and2);

    auto gin916clear = 2 * gout104clear + gout915clear;
    auto gout916clear = fand2(gin916clear, 4);

    assert(ctx.decrypt(&gout916) == gout916clear);
    std::cerr << "\rLUT917   ";
    Ciphertext gin917 = 2 * gout914 + gout783;
    Ciphertext gout917 = ctx.eval_lut(&gin917, nand2);

    auto gin917clear = 2 * gout914clear + gout783clear;
    auto gout917clear = fnand2(gin917clear, 4);

    assert(ctx.decrypt(&gout917) == gout917clear);
    std::cerr << "\rLUT918   ";
    Ciphertext gin918 = 2 * gout784 + gout917;
    Ciphertext gout918 = ctx.eval_lut(&gin918, nand2);

    auto gin918clear = 2 * gout784clear + gout917clear;
    auto gout918clear = fnand2(gin918clear, 4);

    assert(ctx.decrypt(&gout918) == gout918clear);
    std::cerr << "\rLUT919   ";
    Ciphertext gin919 = 2 * gout918 + gout795;
    Ciphertext gout919 = ctx.eval_lut(&gin919, xnor2);

    auto gin919clear = 2 * gout918clear + gout795clear;
    auto gout919clear = fxnor2(gin919clear, 4);

    assert(ctx.decrypt(&gout919) == gout919clear);
    std::cerr << "\rIMUX920  ";
    Ciphertext gin920A = 2 * gout919 + gout104;
    Ciphertext gout920A = ctx.eval_lut(&gin920A, and2);
    Ciphertext gin920B = 2 * gout825 + (1 - gout104);
    Ciphertext gout920B = ctx.eval_lut(&gin920B, and2);
    Ciphertext gout920 = gout920A + gout920B;

    long gin920Aclear = 2 * gout919clear + gout104clear;
    long gout920Aclear = fand2(gin920Aclear, 4);
    long gin920Bclear = 2 * gout825clear + (1 - gout104clear);
    long gout920Bclear = fand2(gin920Bclear, 4);
    long gout920clear = gout920Aclear + gout920Bclear;

    assert(ctx.decrypt(&gout920) == gout920clear);
    std::cerr << "\rLUT921   ";
    Ciphertext gin921 = 2 * gout218 + gout920;
    Ciphertext gout921 = ctx.eval_lut(&gin921, nand2);

    auto gin921clear = 2 * gout218clear + gout920clear;
    auto gout921clear = fnand2(gin921clear, 4);

    assert(ctx.decrypt(&gout921) == gout921clear);
    std::cerr << "\rLUT922   ";
    Ciphertext gin922 = 2 * gout918 + gout795;
    Ciphertext gout922 = ctx.eval_lut(&gin922, nand2);

    auto gin922clear = 2 * gout918clear + gout795clear;
    auto gout922clear = fnand2(gin922clear, 4);

    assert(ctx.decrypt(&gout922) == gout922clear);
    std::cerr << "\rLUT923   ";
    Ciphertext gin923 = 2 * gout796 + gout922;
    Ciphertext gout923 = ctx.eval_lut(&gin923, and2);

    auto gin923clear = 2 * gout796clear + gout922clear;
    auto gout923clear = fand2(gin923clear, 4);

    assert(ctx.decrypt(&gout923) == gout923clear);
    std::cerr << "\rLUT924   ";
    Ciphertext gin924 = 2 * gout923 + gout803;
    Ciphertext gout924 = ctx.eval_lut(&gin924, or2);

    auto gin924clear = 2 * gout923clear + gout803clear;
    auto gout924clear = for2(gin924clear, 4);

    assert(ctx.decrypt(&gout924) == gout924clear);
    std::cerr << "\rLUT925   ";
    Ciphertext gin925 = 2 * gout104 + gout924;
    Ciphertext gout925 = ctx.eval_lut(&gin925, and2);

    auto gin925clear = 2 * gout104clear + gout924clear;
    auto gout925clear = fand2(gin925clear, 4);

    assert(ctx.decrypt(&gout925) == gout925clear);
    std::cerr << "\rLUT926   ";
    Ciphertext gin926 = 2 * gout923 + gout803;
    Ciphertext gout926 = ctx.eval_lut(&gin926, nand2);

    auto gin926clear = 2 * gout923clear + gout803clear;
    auto gout926clear = fnand2(gin926clear, 4);

    assert(ctx.decrypt(&gout926) == gout926clear);
    std::cerr << "\rLUT927   ";
    Ciphertext gin927 = 2 * gout926 + gout925;
    Ciphertext gout927 = ctx.eval_lut(&gin927, nand2);

    auto gin927clear = 2 * gout926clear + gout925clear;
    auto gout927clear = fnand2(gin927clear, 4);

    assert(ctx.decrypt(&gout927) == gout927clear);
    std::cerr << "\rLUT928   ";
    Ciphertext gin928 = 2 * gout927 + gout832;
    Ciphertext gout928 = ctx.eval_lut(&gin928, nand2);

    auto gin928clear = 2 * gout927clear + gout832clear;
    auto gout928clear = fnand2(gin928clear, 4);

    assert(ctx.decrypt(&gout928) == gout928clear);
    std::cerr << "\rLUT929   ";
    Ciphertext gin929 = 2 * gout917 + gout916;
    Ciphertext gout929 = ctx.eval_lut(&gin929, nand2);

    auto gin929clear = 2 * gout917clear + gout916clear;
    auto gout929clear = fnand2(gin929clear, 4);

    assert(ctx.decrypt(&gout929) == gout929clear);
    std::cerr << "\rLUT930   ";
    Ciphertext gin930 = 2 * gout218 + gout929;
    Ciphertext gout930 = ctx.eval_lut(&gin930, and2);

    auto gin930clear = 2 * gout218clear + gout929clear;
    auto gout930clear = fand2(gin930clear, 4);

    assert(ctx.decrypt(&gout930) == gout930clear);
    std::cerr << "\rLUT931   ";
    Ciphertext gin931 = 2 * gout837 + gout930;
    Ciphertext gout931 = ctx.eval_lut(&gin931, nand2);

    auto gin931clear = 2 * gout837clear + gout930clear;
    auto gout931clear = fnand2(gin931clear, 4);

    assert(ctx.decrypt(&gout931) == gout931clear);
    std::cerr << "\rLUT932   ";
    Ciphertext gin932 = 2 * gout908 + gout907;
    Ciphertext gout932 = ctx.eval_lut(&gin932, nand2);

    auto gin932clear = 2 * gout908clear + gout907clear;
    auto gout932clear = fnand2(gin932clear, 4);

    assert(ctx.decrypt(&gout932) == gout932clear);
    std::cerr << "\rLUT933   ";
    Ciphertext gin933 = 2 * gout218 + gout932;
    Ciphertext gout933 = ctx.eval_lut(&gin933, and2);

    auto gin933clear = 2 * gout218clear + gout932clear;
    auto gout933clear = fand2(gin933clear, 4);

    assert(ctx.decrypt(&gout933) == gout933clear);
    std::cerr << "\rLUT934   ";
    Ciphertext gin934 = 2 * gout842 + gout933;
    Ciphertext gout934 = ctx.eval_lut(&gin934, nand2);

    auto gin934clear = 2 * gout842clear + gout933clear;
    auto gout934clear = fnand2(gin934clear, 4);

    assert(ctx.decrypt(&gout934) == gout934clear);
    std::cerr << "\r          \r";
    std::vector<long> out;
    out.push_back(ctx.decrypt(&gout501)); /* out0 */
    assert(ctx.decrypt(&gout501) == gout501clear);
    out.push_back(ctx.decrypt(&gout329)); /* out1 */
    assert(ctx.decrypt(&gout329) == gout329clear);
    out.push_back(ctx.decrypt(&gout437)); /* out2 */
    assert(ctx.decrypt(&gout437) == gout437clear);
    out.push_back(ctx.decrypt(&gout587)); /* out3 */
    assert(ctx.decrypt(&gout587) == gout587clear);
    out.push_back(ctx.decrypt(&gout718)); /* out4 */
    assert(ctx.decrypt(&gout718) == gout718clear);
    out.push_back(ctx.decrypt(&gout724)); /* out5 */
    assert(ctx.decrypt(&gout724) == gout724clear);
    out.push_back(ctx.decrypt(&gout729)); /* out6 */
    assert(ctx.decrypt(&gout729) == gout729clear);
    out.push_back(ctx.decrypt(&gout853)); /* out7 */
    assert(ctx.decrypt(&gout853) == gout853clear);
    out.push_back(ctx.decrypt(&gout874)); /* out8 */
    assert(ctx.decrypt(&gout874) == gout874clear);
    out.push_back(ctx.decrypt(&gout888)); /* out9 */
    assert(ctx.decrypt(&gout888) == gout888clear);
    out.push_back(ctx.decrypt(&gout902)); /* out10 */
    assert(ctx.decrypt(&gout902) == gout902clear);
    out.push_back(ctx.decrypt(&gout934)); /* out11 */
    assert(ctx.decrypt(&gout934) == gout934clear);
    out.push_back(ctx.decrypt(&gout912)); /* out12 */
    assert(ctx.decrypt(&gout912) == gout912clear);
    out.push_back(ctx.decrypt(&gout931)); /* out13 */
    assert(ctx.decrypt(&gout931) == gout931clear);
    out.push_back(ctx.decrypt(&gout921)); /* out14 */
    assert(ctx.decrypt(&gout921) == gout921clear);
    out.push_back(ctx.decrypt(&gout928)); /* out15 */
    assert(ctx.decrypt(&gout928) == gout928clear);
    return out;
}

int
main(void)
{
    /* setup */
    FHEContext ctx;
    long out;

    std::cout << "[+] ";
    ctx.generate_context(rlwe_hom_acc_scheme_C_11_NTT);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(4);

    /* add4 tests *//*
    std::cout << "[+] Testing add4" << std::endl;
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            std::cerr << i << " + " << j;
            out = compose(test_add4_boolean(ctx, i, j));
            assert(out == i + j);
        }
    } */

    /* calculator tests */
    std::cout << "[+] Testing calculator" << std::endl;
    std::cout << "[>] 0 0 0" << std::endl;
    std::cout << "exp:    1111111111111111" << std::endl;
    out = compose(test_calculator_boolean(ctx, 0, 0, 0));
    std::cout << "bool:   " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 6 + 7" << std::endl;
    std::cout << "exp:    0000000000001101" << std::endl;
    out = compose(test_calculator_boolean(ctx, '+', 6, 7));
    std::cout << "bool:   " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 6 - 7" << std::endl;
    std::cout << "exp:    1111111111111111" << std::endl;
    out = compose(test_calculator_boolean(ctx, '-', 6, 7));
    std::cout << "bool:   " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 6 * 7" << std::endl;
    std::cout << "exp:    0000000000101010" << std::endl;
    out = compose(test_calculator_boolean(ctx, '*', 6, 7));
    std::cout << "bool:   " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 0xba + 0xbe" << std::endl;
    std::cout << "exp:    0000000101111000" << std::endl;
    out = compose(test_calculator_boolean(ctx, '+', 0xba, 0xbe));
    std::cout << "bool:   " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 0xba - 0xbe" << std::endl;
    std::cout << "exp:    1111111111111100" << std::endl;
    out = compose(test_calculator_boolean(ctx, '-', 0xba, 0xbe));
    std::cout << "bool:   " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 0xba * 0xbe" << std::endl;
    std::cout << "exp:    1000101000001100" << std::endl;
    out = compose(test_calculator_boolean(ctx, '*', 0xba, 0xbe));
    std::cout << "bool:   " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 0xffff + 0xffff" << std::endl;
    std::cout << "exp:    1111111111111110" << std::endl;
    out = compose(test_calculator_boolean(ctx, '+', 0xffff, 0xffff));
    std::cout << "bool:   " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 0xffff - 0xffff" << std::endl;
    std::cout << "exp:    0000000000000000" << std::endl;
    out = compose(test_calculator_boolean(ctx, '-', 0xffff, 0xffff));
    std::cout << "bool:   " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 0xffff * 0xffff" << std::endl;
    std::cout << "exp:    0000000000000001" << std::endl;
    out = compose(test_calculator_boolean(ctx, '*', 0xffff, 0xffff));
    std::cout << "bool:   " << std::bitset<16>(out) << std::endl;

    return 0;
}
