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
test_lut3(FHEContext& ctx)
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

    std::vector<RotationPoly> lut;
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
    std::cerr << "\rLUT3(0)";

    out = ctx.eval_lut_amortized(&ct1, lut);
    assert(ctx.decrypt(&out[0]) == 1);
    assert(ctx.decrypt(&out[1]) == 0);
    assert(ctx.decrypt(&out[2]) == 0);
    std::cerr << "\rLUT3(1)";

    out = ctx.eval_lut_amortized(&ct2, lut);
    assert(ctx.decrypt(&out[0]) == 0);
    assert(ctx.decrypt(&out[1]) == 1);
    assert(ctx.decrypt(&out[2]) == 0);
    std::cerr << "\rLUT3(2)";

    out = ctx.eval_lut_amortized(&ct3, lut);
    assert(ctx.decrypt(&out[0]) == 1);
    assert(ctx.decrypt(&out[1]) == 1);
    assert(ctx.decrypt(&out[2]) == 0);
    std::cerr << "\rLUT3(3)";

    out = ctx.eval_lut_amortized(&ct4, lut);
    assert(ctx.decrypt(&out[0]) == 0);
    assert(ctx.decrypt(&out[1]) == 0);
    assert(ctx.decrypt(&out[2]) == 1);
    std::cerr << "\rLUT3(4)";

    out = ctx.eval_lut_amortized(&ct5, lut);
    assert(ctx.decrypt(&out[0]) == 1);
    assert(ctx.decrypt(&out[1]) == 0);
    assert(ctx.decrypt(&out[2]) == 1);
    std::cerr << "\rLUT3(5)";

    out = ctx.eval_lut_amortized(&ct6, lut);
    assert(ctx.decrypt(&out[0]) == 0);
    assert(ctx.decrypt(&out[1]) == 1);
    assert(ctx.decrypt(&out[2]) == 1);
    std::cerr << "\rLUT3(6)";

    out = ctx.eval_lut_amortized(&ct7, lut);
    assert(ctx.decrypt(&out[0]) == 1);
    assert(ctx.decrypt(&out[1]) == 1);
    assert(ctx.decrypt(&out[2]) == 1);
    std::cerr << "\rLUT3(7)";

    std::cerr << "\r";
}

std::vector<long>
test_add4_lut3fa(FHEContext& ctx, uint8_t a, uint8_t b)
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
            default: assert(0);
        };
    };
    decomp.push_back(ctx.genrate_lut(decomp2));
    fdecomp.push_back(decomp2);

    auto vdecomp = [fdecomp](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 3; ++i)
            ret.push_back(fdecomp[i](I));
        return ret;
    };


    std::cerr << "\rFA0    ";
    Ciphertext gin0 = 1 * ct_a0 + 2 * ct_a1 + 1 * ct_b0 + 2 * ct_b1;
    std::vector<Ciphertext> gout0 = ctx.eval_lut_amortized(&gin0, decomp);

    long gin0clear = 1 * ct_a0clear + 2 * ct_a1clear + 1 * ct_b0clear + 2 * ct_b1clear;
    std::vector<long> gout0clear = vdecomp(gin0clear);

    assert(ctx.decrypt(&gout0[0]) == gout0clear[0]);
    assert(ctx.decrypt(&gout0[1]) == gout0clear[1]);
    std::cerr << "\rFA1    ";
    Ciphertext gin1 = gout0[2] + 1 * ct_a2 + 2 * ct_a3 + 1 * ct_b2 + 2 * ct_b3;
    std::vector<Ciphertext> gout1 = ctx.eval_lut_amortized(&gin1, decomp);

    long gin1clear = gout0clear[2] + 1 * ct_a2clear + 2 * ct_a3clear + 1 * ct_b2clear + 2 * ct_b3clear;
    std::vector<long> gout1clear = vdecomp(gin1clear);

    assert(ctx.decrypt(&gout1[0]) == gout1clear[0]);
    assert(ctx.decrypt(&gout1[1]) == gout1clear[1]);
    std::cerr << "\r          \r";
    std::vector<long> out;
    out.push_back(ctx.decrypt(&gout0[0])); /* out0 */
    assert(ctx.decrypt(&gout0[0]) == gout0clear[0]);
    out.push_back(ctx.decrypt(&gout0[1])); /* out1 */
    assert(ctx.decrypt(&gout0[1]) == gout0clear[1]);
    out.push_back(ctx.decrypt(&gout1[0])); /* out2 */
    assert(ctx.decrypt(&gout1[0]) == gout1clear[0]);
    out.push_back(ctx.decrypt(&gout1[1])); /* out3 */
    assert(ctx.decrypt(&gout1[1]) == gout1clear[1]);
    out.push_back(ctx.decrypt(&gout1[2])); /* out4 */
    assert(ctx.decrypt(&gout1[2]) == gout1clear[2]);
    return out;
}
std::vector<long>
test_calculator_lut3fa(FHEContext& ctx, uint8_t op, uint16_t x, uint16_t y)
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
            default: assert(0);
        };
    };
    decomp.push_back(ctx.genrate_lut(decomp2));
    fdecomp.push_back(decomp2);

    auto vdecomp = [fdecomp](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 3; ++i)
            ret.push_back(fdecomp[i](I));
        return ret;
    };


    std::cerr << "\rINV0   ";
    std::vector<Ciphertext> gout0;
    gout0.push_back(1 - ct_y9);

    std::vector<long> gout0clear;
    gout0clear.push_back(1 - ct_y9clear);

    assert(ctx.decrypt(&gout0[0]) == gout0clear[0]);
    std::cerr << "\rINV1   ";
    std::vector<Ciphertext> gout1;
    gout1.push_back(1 - ct_y8);

    std::vector<long> gout1clear;
    gout1clear.push_back(1 - ct_y8clear);

    assert(ctx.decrypt(&gout1[0]) == gout1clear[0]);
    std::cerr << "\rINV2   ";
    std::vector<Ciphertext> gout2;
    gout2.push_back(1 - ct_y14);

    std::vector<long> gout2clear;
    gout2clear.push_back(1 - ct_y14clear);

    assert(ctx.decrypt(&gout2[0]) == gout2clear[0]);
    std::cerr << "\rINV3   ";
    std::vector<Ciphertext> gout3;
    gout3.push_back(1 - ct_y7);

    std::vector<long> gout3clear;
    gout3clear.push_back(1 - ct_y7clear);

    assert(ctx.decrypt(&gout3[0]) == gout3clear[0]);
    std::cerr << "\rINV4   ";
    std::vector<Ciphertext> gout4;
    gout4.push_back(1 - ct_y15);

    std::vector<long> gout4clear;
    gout4clear.push_back(1 - ct_y15clear);

    assert(ctx.decrypt(&gout4[0]) == gout4clear[0]);
    std::cerr << "\rINV5   ";
    std::vector<Ciphertext> gout5;
    gout5.push_back(1 - ct_y6);

    std::vector<long> gout5clear;
    gout5clear.push_back(1 - ct_y6clear);

    assert(ctx.decrypt(&gout5[0]) == gout5clear[0]);
    std::cerr << "\rINV6   ";
    std::vector<Ciphertext> gout6;
    gout6.push_back(1 - ct_y1);

    std::vector<long> gout6clear;
    gout6clear.push_back(1 - ct_y1clear);

    assert(ctx.decrypt(&gout6[0]) == gout6clear[0]);
    std::cerr << "\rINV7   ";
    std::vector<Ciphertext> gout7;
    gout7.push_back(1 - ct_y5);

    std::vector<long> gout7clear;
    gout7clear.push_back(1 - ct_y5clear);

    assert(ctx.decrypt(&gout7[0]) == gout7clear[0]);
    std::cerr << "\rINV8   ";
    std::vector<Ciphertext> gout8;
    gout8.push_back(1 - ct_y2);

    std::vector<long> gout8clear;
    gout8clear.push_back(1 - ct_y2clear);

    assert(ctx.decrypt(&gout8[0]) == gout8clear[0]);
    std::cerr << "\rINV9   ";
    std::vector<Ciphertext> gout9;
    gout9.push_back(1 - ct_y4);

    std::vector<long> gout9clear;
    gout9clear.push_back(1 - ct_y4clear);

    assert(ctx.decrypt(&gout9[0]) == gout9clear[0]);
    std::cerr << "\rINV10   ";
    std::vector<Ciphertext> gout10;
    gout10.push_back(1 - ct_y3);

    std::vector<long> gout10clear;
    gout10clear.push_back(1 - ct_y3clear);

    assert(ctx.decrypt(&gout10[0]) == gout10clear[0]);
    std::cerr << "\rINV11   ";
    std::vector<Ciphertext> gout11;
    gout11.push_back(1 - ct_y13);

    std::vector<long> gout11clear;
    gout11clear.push_back(1 - ct_y13clear);

    assert(ctx.decrypt(&gout11[0]) == gout11clear[0]);
    std::cerr << "\rINV12   ";
    std::vector<Ciphertext> gout12;
    gout12.push_back(1 - ct_y12);

    std::vector<long> gout12clear;
    gout12clear.push_back(1 - ct_y12clear);

    assert(ctx.decrypt(&gout12[0]) == gout12clear[0]);
    std::cerr << "\rINV13   ";
    std::vector<Ciphertext> gout13;
    gout13.push_back(1 - ct_y10);

    std::vector<long> gout13clear;
    gout13clear.push_back(1 - ct_y10clear);

    assert(ctx.decrypt(&gout13[0]) == gout13clear[0]);
    std::cerr << "\rINV14   ";
    std::vector<Ciphertext> gout14;
    gout14.push_back(1 - ct_y11);

    std::vector<long> gout14clear;
    gout14clear.push_back(1 - ct_y11clear);

    assert(ctx.decrypt(&gout14[0]) == gout14clear[0]);
    std::cerr << "\rINV15   ";
    std::vector<Ciphertext> gout15;
    gout15.push_back(1 - ct_y0);

    std::vector<long> gout15clear;
    gout15clear.push_back(1 - ct_y0clear);

    assert(ctx.decrypt(&gout15[0]) == gout15clear[0]);
    std::vector<RotationPoly> lut16;
    std::vector<long (*)(long)> flut16;
    auto lut16idx0 = [](long I) -> long {
        /* GATE 108 (LUT2 _1483_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut16.push_back(ctx.genrate_lut(lut16idx0));
    flut16.push_back(lut16idx0);

    auto fvec16 = [flut16](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut16[i](I));
        return ret;
    };

    std::cerr << "\rLUT16   ";
    Ciphertext gin16 = 1 * ct_y2 + 2 * ct_x5;
    std::vector<Ciphertext> gout16 = ctx.eval_lut_amortized(&gin16, lut16);

    long gin16clear = 1 * ct_y2clear + 2 * ct_x5clear;
    std::vector<long> gout16clear = fvec16(gin16clear);

    assert(ctx.decrypt(&gout16[0]) == gout16clear[0]);
    std::vector<RotationPoly> lut17;
    std::vector<long (*)(long)> flut17;
    auto lut17idx0 = [](long I) -> long {
        /* GATE 68 (LUT2 _1443_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut17.push_back(ctx.genrate_lut(lut17idx0));
    flut17.push_back(lut17idx0);

    auto fvec17 = [flut17](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut17[i](I));
        return ret;
    };

    std::cerr << "\rLUT17   ";
    Ciphertext gin17 = 1 * ct_x2 + 2 * ct_y3;
    std::vector<Ciphertext> gout17 = ctx.eval_lut_amortized(&gin17, lut17);

    long gin17clear = 1 * ct_x2clear + 2 * ct_y3clear;
    std::vector<long> gout17clear = fvec17(gin17clear);

    assert(ctx.decrypt(&gout17[0]) == gout17clear[0]);
    std::vector<RotationPoly> lut18;
    std::vector<long (*)(long)> flut18;
    auto lut18idx0 = [](long I) -> long {
        /* GATE 45 (LUT2 _1420_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut18.push_back(ctx.genrate_lut(lut18idx0));
    flut18.push_back(lut18idx0);

    auto fvec18 = [flut18](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut18[i](I));
        return ret;
    };

    std::cerr << "\rLUT18   ";
    Ciphertext gin18 = 1 * ct_y1 + 2 * ct_x3;
    std::vector<Ciphertext> gout18 = ctx.eval_lut_amortized(&gin18, lut18);

    long gin18clear = 1 * ct_y1clear + 2 * ct_x3clear;
    std::vector<long> gout18clear = fvec18(gin18clear);

    assert(ctx.decrypt(&gout18[0]) == gout18clear[0]);
    std::vector<RotationPoly> lut19;
    std::vector<long (*)(long)> flut19;
    auto lut19idx0 = [](long I) -> long {
        /* GATE 92 (LUT2 _1467_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut19.push_back(ctx.genrate_lut(lut19idx0));
    flut19.push_back(lut19idx0);

    auto fvec19 = [flut19](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut19[i](I));
        return ret;
    };

    std::cerr << "\rLUT19   ";
    Ciphertext gin19 = 1 * ct_y3 + 2 * ct_x3;
    std::vector<Ciphertext> gout19 = ctx.eval_lut_amortized(&gin19, lut19);

    long gin19clear = 1 * ct_y3clear + 2 * ct_x3clear;
    std::vector<long> gout19clear = fvec19(gin19clear);

    assert(ctx.decrypt(&gout19[0]) == gout19clear[0]);
    std::vector<RotationPoly> lut20;
    std::vector<long (*)(long)> flut20;
    auto lut20idx0 = [](long I) -> long {
        /* GATE 5 (LUT2 _1380_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut20.push_back(ctx.genrate_lut(lut20idx0));
    flut20.push_back(lut20idx0);

    auto fvec20 = [flut20](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut20[i](I));
        return ret;
    };

    std::cerr << "\rLUT20   ";
    Ciphertext gin20 = 1 * ct_op6 + 2 * ct_op7;
    std::vector<Ciphertext> gout20 = ctx.eval_lut_amortized(&gin20, lut20);

    long gin20clear = 1 * ct_op6clear + 2 * ct_op7clear;
    std::vector<long> gout20clear = fvec20(gin20clear);

    assert(ctx.decrypt(&gout20[0]) == gout20clear[0]);
    std::vector<RotationPoly> lut21;
    std::vector<long (*)(long)> flut21;
    auto lut21idx0 = [](long I) -> long {
        /* GATE 4 (LUT3 _1379_ INIT 0x40 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut21.push_back(ctx.genrate_lut(lut21idx0));
    flut21.push_back(lut21idx0);

    auto fvec21 = [flut21](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut21[i](I));
        return ret;
    };

    std::cerr << "\rLUT21   ";
    Ciphertext gin21 = 1 * ct_op4 + 2 * ct_op5 + 4 * gout20[0];
    std::vector<Ciphertext> gout21 = ctx.eval_lut_amortized(&gin21, lut21);

    long gin21clear = 1 * ct_op4clear + 2 * ct_op5clear + 4 * gout20clear[0];
    std::vector<long> gout21clear = fvec21(gin21clear);

    assert(ctx.decrypt(&gout21[0]) == gout21clear[0]);
    std::vector<RotationPoly> lut22;
    std::vector<long (*)(long)> flut22;
    auto lut22idx0 = [](long I) -> long {
        /* GATE 251 (LUT2 _1626_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut22.push_back(ctx.genrate_lut(lut22idx0));
    flut22.push_back(lut22idx0);

    auto fvec22 = [flut22](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut22[i](I));
        return ret;
    };

    std::cerr << "\rLUT22   ";
    Ciphertext gin22 = 1 * ct_y5 + 2 * ct_x6;
    std::vector<Ciphertext> gout22 = ctx.eval_lut_amortized(&gin22, lut22);

    long gin22clear = 1 * ct_y5clear + 2 * ct_x6clear;
    std::vector<long> gout22clear = fvec22(gin22clear);

    assert(ctx.decrypt(&gout22[0]) == gout22clear[0]);
    std::vector<RotationPoly> lut23;
    std::vector<long (*)(long)> flut23;
    auto lut23idx0 = [](long I) -> long {
        /* GATE 117 (LUT2 _1492_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut23.push_back(ctx.genrate_lut(lut23idx0));
    flut23.push_back(lut23idx0);

    auto fvec23 = [flut23](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut23[i](I));
        return ret;
    };

    std::cerr << "\rLUT23   ";
    Ciphertext gin23 = 1 * ct_x1 + 2 * ct_y6;
    std::vector<Ciphertext> gout23 = ctx.eval_lut_amortized(&gin23, lut23);

    long gin23clear = 1 * ct_x1clear + 2 * ct_y6clear;
    std::vector<long> gout23clear = fvec23(gin23clear);

    assert(ctx.decrypt(&gout23[0]) == gout23clear[0]);
    std::vector<RotationPoly> lut24;
    std::vector<long (*)(long)> flut24;
    auto lut24idx0 = [](long I) -> long {
        /* GATE 312 (LUT2 _1687_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut24.push_back(ctx.genrate_lut(lut24idx0));
    flut24.push_back(lut24idx0);

    auto fvec24 = [flut24](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut24[i](I));
        return ret;
    };

    std::cerr << "\rLUT24   ";
    Ciphertext gin24 = 1 * ct_x0 + 2 * ct_y12;
    std::vector<Ciphertext> gout24 = ctx.eval_lut_amortized(&gin24, lut24);

    long gin24clear = 1 * ct_x0clear + 2 * ct_y12clear;
    std::vector<long> gout24clear = fvec24(gin24clear);

    assert(ctx.decrypt(&gout24[0]) == gout24clear[0]);
    std::vector<RotationPoly> lut25;
    std::vector<long (*)(long)> flut25;
    auto lut25idx0 = [](long I) -> long {
        /* GATE 212 (LUT2 _1587_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut25.push_back(ctx.genrate_lut(lut25idx0));
    flut25.push_back(lut25idx0);

    auto fvec25 = [flut25](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut25[i](I));
        return ret;
    };

    std::cerr << "\rLUT25   ";
    Ciphertext gin25 = 1 * ct_y5 + 2 * ct_x5;
    std::vector<Ciphertext> gout25 = ctx.eval_lut_amortized(&gin25, lut25);

    long gin25clear = 1 * ct_y5clear + 2 * ct_x5clear;
    std::vector<long> gout25clear = fvec25(gin25clear);

    assert(ctx.decrypt(&gout25[0]) == gout25clear[0]);
    std::vector<RotationPoly> lut26;
    std::vector<long (*)(long)> flut26;
    auto lut26idx0 = [](long I) -> long {
        /* GATE 62 (LUT2 _1437_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut26.push_back(ctx.genrate_lut(lut26idx0));
    flut26.push_back(lut26idx0);

    auto fvec26 = [flut26](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut26[i](I));
        return ret;
    };

    std::cerr << "\rLUT26   ";
    Ciphertext gin26 = 1 * ct_x4 + 2 * ct_y1;
    std::vector<Ciphertext> gout26 = ctx.eval_lut_amortized(&gin26, lut26);

    long gin26clear = 1 * ct_x4clear + 2 * ct_y1clear;
    std::vector<long> gout26clear = fvec26(gin26clear);

    assert(ctx.decrypt(&gout26[0]) == gout26clear[0]);
    std::vector<RotationPoly> lut27;
    std::vector<long (*)(long)> flut27;
    auto lut27idx0 = [](long I) -> long {
        /* GATE 266 (LUT2 _1641_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut27.push_back(ctx.genrate_lut(lut27idx0));
    flut27.push_back(lut27idx0);

    auto fvec27 = [flut27](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut27[i](I));
        return ret;
    };

    std::cerr << "\rLUT27   ";
    Ciphertext gin27 = 1 * ct_x0 + 2 * ct_y11;
    std::vector<Ciphertext> gout27 = ctx.eval_lut_amortized(&gin27, lut27);

    long gin27clear = 1 * ct_x0clear + 2 * ct_y11clear;
    std::vector<long> gout27clear = fvec27(gin27clear);

    assert(ctx.decrypt(&gout27[0]) == gout27clear[0]);
    std::vector<RotationPoly> lut28;
    std::vector<long (*)(long)> flut28;
    auto lut28idx0 = [](long I) -> long {
        /* GATE 34 (LUT2 _1409_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut28.push_back(ctx.genrate_lut(lut28idx0));
    flut28.push_back(lut28idx0);

    auto fvec28 = [flut28](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut28[i](I));
        return ret;
    };

    std::cerr << "\rLUT28   ";
    Ciphertext gin28 = 1 * ct_x0 + 2 * ct_y3;
    std::vector<Ciphertext> gout28 = ctx.eval_lut_amortized(&gin28, lut28);

    long gin28clear = 1 * ct_x0clear + 2 * ct_y3clear;
    std::vector<long> gout28clear = fvec28(gin28clear);

    assert(ctx.decrypt(&gout28[0]) == gout28clear[0]);
    std::vector<RotationPoly> lut29;
    std::vector<long (*)(long)> flut29;
    auto lut29idx0 = [](long I) -> long {
        /* GATE 378 (LUT2 _1753_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut29.push_back(ctx.genrate_lut(lut29idx0));
    flut29.push_back(lut29idx0);

    auto fvec29 = [flut29](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut29[i](I));
        return ret;
    };

    std::cerr << "\rLUT29   ";
    Ciphertext gin29 = 1 * ct_x13 + 2 * ct_y1;
    std::vector<Ciphertext> gout29 = ctx.eval_lut_amortized(&gin29, lut29);

    long gin29clear = 1 * ct_x13clear + 2 * ct_y1clear;
    std::vector<long> gout29clear = fvec29(gin29clear);

    assert(ctx.decrypt(&gout29[0]) == gout29clear[0]);
    std::vector<RotationPoly> lut30;
    std::vector<long (*)(long)> flut30;
    auto lut30idx0 = [](long I) -> long {
        /* GATE 116 (LUT3 _1491_ INIT 0x78 PERM 120) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut30.push_back(ctx.genrate_lut(lut30idx0));
    flut30.push_back(lut30idx0);

    auto lut30idx1 = [](long I) -> long {
        /* GATE 144 (LUT3 _1519_ INIT 0x80 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut30.push_back(ctx.genrate_lut(lut30idx1));
    flut30.push_back(lut30idx1);

    auto fvec30 = [flut30](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut30[i](I));
        return ret;
    };

    std::cerr << "\rLUT30   ";
    Ciphertext gin30 = 1 * gout23[0] + 2 * ct_x0 + 4 * ct_y7;
    std::vector<Ciphertext> gout30 = ctx.eval_lut_amortized(&gin30, lut30);

    long gin30clear = 1 * gout23clear[0] + 2 * ct_x0clear + 4 * ct_y7clear;
    std::vector<long> gout30clear = fvec30(gin30clear);

    assert(ctx.decrypt(&gout30[0]) == gout30clear[0]);
    assert(ctx.decrypt(&gout30[1]) == gout30clear[1]);
    std::vector<RotationPoly> lut31;
    std::vector<long (*)(long)> flut31;
    auto lut31idx0 = [](long I) -> long {
        /* GATE 289 (LUT2 _1664_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut31.push_back(ctx.genrate_lut(lut31idx0));
    flut31.push_back(lut31idx0);

    auto fvec31 = [flut31](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut31[i](I));
        return ret;
    };

    std::cerr << "\rLUT31   ";
    Ciphertext gin31 = 1 * ct_x11 + 2 * ct_y1;
    std::vector<Ciphertext> gout31 = ctx.eval_lut_amortized(&gin31, lut31);

    long gin31clear = 1 * ct_x11clear + 2 * ct_y1clear;
    std::vector<long> gout31clear = fvec31(gin31clear);

    assert(ctx.decrypt(&gout31[0]) == gout31clear[0]);
    std::vector<RotationPoly> lut32;
    std::vector<long (*)(long)> flut32;
    auto lut32idx0 = [](long I) -> long {
        /* GATE 355 (LUT2 _1730_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut32.push_back(ctx.genrate_lut(lut32idx0));
    flut32.push_back(lut32idx0);

    auto fvec32 = [flut32](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut32[i](I));
        return ret;
    };

    std::cerr << "\rLUT32   ";
    Ciphertext gin32 = 1 * ct_x2 + 2 * ct_y11;
    std::vector<Ciphertext> gout32 = ctx.eval_lut_amortized(&gin32, lut32);

    long gin32clear = 1 * ct_x2clear + 2 * ct_y11clear;
    std::vector<long> gout32clear = fvec32(gin32clear);

    assert(ctx.decrypt(&gout32[0]) == gout32clear[0]);
    std::vector<RotationPoly> lut33;
    std::vector<long (*)(long)> flut33;
    auto lut33idx0 = [](long I) -> long {
        /* GATE 310 (LUT2 _1685_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut33.push_back(ctx.genrate_lut(lut33idx0));
    flut33.push_back(lut33idx0);

    auto fvec33 = [flut33](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut33[i](I));
        return ret;
    };

    std::cerr << "\rLUT33   ";
    Ciphertext gin33 = 1 * ct_x1 + 2 * ct_y11;
    std::vector<Ciphertext> gout33 = ctx.eval_lut_amortized(&gin33, lut33);

    long gin33clear = 1 * ct_x1clear + 2 * ct_y11clear;
    std::vector<long> gout33clear = fvec33(gin33clear);

    assert(ctx.decrypt(&gout33[0]) == gout33clear[0]);
    std::vector<RotationPoly> lut34;
    std::vector<long (*)(long)> flut34;
    auto lut34idx0 = [](long I) -> long {
        /* GATE 111 (LUT2 _1486_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut34.push_back(ctx.genrate_lut(lut34idx0));
    flut34.push_back(lut34idx0);

    auto fvec34 = [flut34](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut34[i](I));
        return ret;
    };

    std::cerr << "\rLUT34   ";
    Ciphertext gin34 = 1 * ct_y4 + 2 * ct_x3;
    std::vector<Ciphertext> gout34 = ctx.eval_lut_amortized(&gin34, lut34);

    long gin34clear = 1 * ct_y4clear + 2 * ct_x3clear;
    std::vector<long> gout34clear = fvec34(gin34clear);

    assert(ctx.decrypt(&gout34[0]) == gout34clear[0]);
    std::vector<RotationPoly> lut35;
    std::vector<long (*)(long)> flut35;
    auto lut35idx0 = [](long I) -> long {
        /* GATE 148 (LUT2 _1523_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut35.push_back(ctx.genrate_lut(lut35idx0));
    flut35.push_back(lut35idx0);

    auto fvec35 = [flut35](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut35[i](I));
        return ret;
    };

    std::cerr << "\rLUT35   ";
    Ciphertext gin35 = 1 * ct_x0 + 2 * ct_y8;
    std::vector<Ciphertext> gout35 = ctx.eval_lut_amortized(&gin35, lut35);

    long gin35clear = 1 * ct_x0clear + 2 * ct_y8clear;
    std::vector<long> gout35clear = fvec35(gin35clear);

    assert(ctx.decrypt(&gout35[0]) == gout35clear[0]);
    std::vector<RotationPoly> lut36;
    std::vector<long (*)(long)> flut36;
    auto lut36idx0 = [](long I) -> long {
        /* GATE 107 (LUT2 _1482_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut36.push_back(ctx.genrate_lut(lut36idx0));
    flut36.push_back(lut36idx0);

    auto fvec36 = [flut36](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut36[i](I));
        return ret;
    };

    std::cerr << "\rLUT36   ";
    Ciphertext gin36 = 1 * ct_y1 + 2 * ct_x6;
    std::vector<Ciphertext> gout36 = ctx.eval_lut_amortized(&gin36, lut36);

    long gin36clear = 1 * ct_y1clear + 2 * ct_x6clear;
    std::vector<long> gout36clear = fvec36(gin36clear);

    assert(ctx.decrypt(&gout36[0]) == gout36clear[0]);
    std::vector<RotationPoly> lut37;
    std::vector<long (*)(long)> flut37;
    auto lut37idx0 = [](long I) -> long {
        /* GATE 8 (LUT3 _1383_ INIT 0x40 PERM 120) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut37.push_back(ctx.genrate_lut(lut37idx0));
    flut37.push_back(lut37idx0);

    auto fvec37 = [flut37](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut37[i](I));
        return ret;
    };

    std::cerr << "\rLUT37   ";
    Ciphertext gin37 = 1 * ct_op1 + 2 * ct_op2 + 4 * ct_op3;
    std::vector<Ciphertext> gout37 = ctx.eval_lut_amortized(&gin37, lut37);

    long gin37clear = 1 * ct_op1clear + 2 * ct_op2clear + 4 * ct_op3clear;
    std::vector<long> gout37clear = fvec37(gin37clear);

    assert(ctx.decrypt(&gout37[0]) == gout37clear[0]);
    std::vector<RotationPoly> lut38;
    std::vector<long (*)(long)> flut38;
    auto lut38idx0 = [](long I) -> long {
        /* GATE 293 (LUT2 _1668_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut38.push_back(ctx.genrate_lut(lut38idx0));
    flut38.push_back(lut38idx0);

    auto fvec38 = [flut38](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut38[i](I));
        return ret;
    };

    std::cerr << "\rLUT38   ";
    Ciphertext gin38 = 1 * ct_y4 + 2 * ct_x8;
    std::vector<Ciphertext> gout38 = ctx.eval_lut_amortized(&gin38, lut38);

    long gin38clear = 1 * ct_y4clear + 2 * ct_x8clear;
    std::vector<long> gout38clear = fvec38(gin38clear);

    assert(ctx.decrypt(&gout38[0]) == gout38clear[0]);
    std::vector<RotationPoly> lut39;
    std::vector<long (*)(long)> flut39;
    auto lut39idx0 = [](long I) -> long {
        /* GATE 388 (LUT2 _1763_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut39.push_back(ctx.genrate_lut(lut39idx0));
    flut39.push_back(lut39idx0);

    auto fvec39 = [flut39](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut39[i](I));
        return ret;
    };

    std::cerr << "\rLUT39   ";
    Ciphertext gin39 = 1 * ct_y6 + 2 * ct_x8;
    std::vector<Ciphertext> gout39 = ctx.eval_lut_amortized(&gin39, lut39);

    long gin39clear = 1 * ct_y6clear + 2 * ct_x8clear;
    std::vector<long> gout39clear = fvec39(gin39clear);

    assert(ctx.decrypt(&gout39[0]) == gout39clear[0]);
    std::vector<RotationPoly> lut40;
    std::vector<long (*)(long)> flut40;
    auto lut40idx0 = [](long I) -> long {
        /* GATE 347 (LUT2 _1722_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut40.push_back(ctx.genrate_lut(lut40idx0));
    flut40.push_back(lut40idx0);

    auto fvec40 = [flut40](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut40[i](I));
        return ret;
    };

    std::cerr << "\rLUT40   ";
    Ciphertext gin40 = 1 * ct_y6 + 2 * ct_x7;
    std::vector<Ciphertext> gout40 = ctx.eval_lut_amortized(&gin40, lut40);

    long gin40clear = 1 * ct_y6clear + 2 * ct_x7clear;
    std::vector<long> gout40clear = fvec40(gin40clear);

    assert(ctx.decrypt(&gout40[0]) == gout40clear[0]);
    std::vector<RotationPoly> lut41;
    std::vector<long (*)(long)> flut41;
    auto lut41idx0 = [](long I) -> long {
        /* GATE 22 (LUT2 _1397_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut41.push_back(ctx.genrate_lut(lut41idx0));
    flut41.push_back(lut41idx0);

    auto fvec41 = [flut41](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut41[i](I));
        return ret;
    };

    std::cerr << "\rLUT41   ";
    Ciphertext gin41 = 1 * ct_x2 + 2 * ct_y0;
    std::vector<Ciphertext> gout41 = ctx.eval_lut_amortized(&gin41, lut41);

    long gin41clear = 1 * ct_x2clear + 2 * ct_y0clear;
    std::vector<long> gout41clear = fvec41(gin41clear);

    assert(ctx.decrypt(&gout41[0]) == gout41clear[0]);
    std::vector<RotationPoly> lut42;
    std::vector<long (*)(long)> flut42;
    auto lut42idx0 = [](long I) -> long {
        /* GATE 91 (LUT2 _1466_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut42.push_back(ctx.genrate_lut(lut42idx0));
    flut42.push_back(lut42idx0);

    auto fvec42 = [flut42](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut42[i](I));
        return ret;
    };

    std::cerr << "\rLUT42   ";
    Ciphertext gin42 = 1 * ct_x1 + 2 * ct_y5;
    std::vector<Ciphertext> gout42 = ctx.eval_lut_amortized(&gin42, lut42);

    long gin42clear = 1 * ct_x1clear + 2 * ct_y5clear;
    std::vector<long> gout42clear = fvec42(gin42clear);

    assert(ctx.decrypt(&gout42[0]) == gout42clear[0]);
    std::vector<RotationPoly> lut43;
    std::vector<long (*)(long)> flut43;
    auto lut43idx0 = [](long I) -> long {
        /* GATE 339 (LUT2 _1714_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut43.push_back(ctx.genrate_lut(lut43idx0));
    flut43.push_back(lut43idx0);

    auto fvec43 = [flut43](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut43[i](I));
        return ret;
    };

    std::cerr << "\rLUT43   ";
    Ciphertext gin43 = 1 * ct_x8 + 2 * ct_y5;
    std::vector<Ciphertext> gout43 = ctx.eval_lut_amortized(&gin43, lut43);

    long gin43clear = 1 * ct_x8clear + 2 * ct_y5clear;
    std::vector<long> gout43clear = fvec43(gin43clear);

    assert(ctx.decrypt(&gout43[0]) == gout43clear[0]);
    std::cerr << "\rFA44    ";
    Ciphertext gin44 = 1 + 1 * ct_x0 + 2 * ct_x1 + 1 * gout15[0] + 2 * gout6[0];
    std::vector<Ciphertext> gout44 = ctx.eval_lut_amortized(&gin44, decomp);

    long gin44clear = 1 * ct_x0clear + 2 * ct_x1clear + 1 * gout15clear[0] + 2 * gout6clear[0];
    std::vector<long> gout44clear = vdecomp(gin44clear);

    assert(ctx.decrypt(&gout44[0]) == gout44clear[0]);
    assert(ctx.decrypt(&gout44[1]) == gout44clear[1]);
    std::vector<RotationPoly> lut45;
    std::vector<long (*)(long)> flut45;
    auto lut45idx0 = [](long I) -> long {
        /* GATE 173 (LUT2 _1548_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut45.push_back(ctx.genrate_lut(lut45idx0));
    flut45.push_back(lut45idx0);

    auto fvec45 = [flut45](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut45[i](I));
        return ret;
    };

    std::cerr << "\rLUT45   ";
    Ciphertext gin45 = 1 * ct_x9 + 2 * ct_y0;
    std::vector<Ciphertext> gout45 = ctx.eval_lut_amortized(&gin45, lut45);

    long gin45clear = 1 * ct_x9clear + 2 * ct_y0clear;
    std::vector<long> gout45clear = fvec45(gin45clear);

    assert(ctx.decrypt(&gout45[0]) == gout45clear[0]);
    std::vector<RotationPoly> lut46;
    std::vector<long (*)(long)> flut46;
    auto lut46idx0 = [](long I) -> long {
        /* GATE 421 (LUT2 _1796_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut46.push_back(ctx.genrate_lut(lut46idx0));
    flut46.push_back(lut46idx0);

    auto fvec46 = [flut46](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut46[i](I));
        return ret;
    };

    std::cerr << "\rLUT46   ";
    Ciphertext gin46 = 1 * ct_x5 + 2 * ct_y10;
    std::vector<Ciphertext> gout46 = ctx.eval_lut_amortized(&gin46, lut46);

    long gin46clear = 1 * ct_x5clear + 2 * ct_y10clear;
    std::vector<long> gout46clear = fvec46(gin46clear);

    assert(ctx.decrypt(&gout46[0]) == gout46clear[0]);
    std::vector<RotationPoly> lut47;
    std::vector<long (*)(long)> flut47;
    auto lut47idx0 = [](long I) -> long {
        /* GATE 309 (LUT2 _1684_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut47.push_back(ctx.genrate_lut(lut47idx0));
    flut47.push_back(lut47idx0);

    auto fvec47 = [flut47](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut47[i](I));
        return ret;
    };

    std::cerr << "\rLUT47   ";
    Ciphertext gin47 = 1 * ct_x2 + 2 * ct_y10;
    std::vector<Ciphertext> gout47 = ctx.eval_lut_amortized(&gin47, lut47);

    long gin47clear = 1 * ct_x2clear + 2 * ct_y10clear;
    std::vector<long> gout47clear = fvec47(gin47clear);

    assert(ctx.decrypt(&gout47[0]) == gout47clear[0]);
    std::vector<RotationPoly> lut48;
    std::vector<long (*)(long)> flut48;
    auto lut48idx0 = [](long I) -> long {
        /* GATE 213 (LUT2 _1588_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut48.push_back(ctx.genrate_lut(lut48idx0));
    flut48.push_back(lut48idx0);

    auto fvec48 = [flut48](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut48[i](I));
        return ret;
    };

    std::cerr << "\rLUT48   ";
    Ciphertext gin48 = 1 * ct_y3 + 2 * ct_x7;
    std::vector<Ciphertext> gout48 = ctx.eval_lut_amortized(&gin48, lut48);

    long gin48clear = 1 * ct_y3clear + 2 * ct_x7clear;
    std::vector<long> gout48clear = fvec48(gin48clear);

    assert(ctx.decrypt(&gout48[0]) == gout48clear[0]);
    std::vector<RotationPoly> lut49;
    std::vector<long (*)(long)> flut49;
    auto lut49idx0 = [](long I) -> long {
        /* GATE 137 (LUT2 _1512_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut49.push_back(ctx.genrate_lut(lut49idx0));
    flut49.push_back(lut49idx0);

    auto fvec49 = [flut49](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut49[i](I));
        return ret;
    };

    std::cerr << "\rLUT49   ";
    Ciphertext gin49 = 1 * ct_y2 + 2 * ct_x6;
    std::vector<Ciphertext> gout49 = ctx.eval_lut_amortized(&gin49, lut49);

    long gin49clear = 1 * ct_y2clear + 2 * ct_x6clear;
    std::vector<long> gout49clear = fvec49(gin49clear);

    assert(ctx.decrypt(&gout49[0]) == gout49clear[0]);
    std::vector<RotationPoly> lut50;
    std::vector<long (*)(long)> flut50;
    auto lut50idx0 = [](long I) -> long {
        /* GATE 224 (LUT2 _1599_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut50.push_back(ctx.genrate_lut(lut50idx0));
    flut50.push_back(lut50idx0);

    auto fvec50 = [flut50](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut50[i](I));
        return ret;
    };

    std::cerr << "\rLUT50   ";
    Ciphertext gin50 = 1 * ct_x1 + 2 * ct_y9;
    std::vector<Ciphertext> gout50 = ctx.eval_lut_amortized(&gin50, lut50);

    long gin50clear = 1 * ct_x1clear + 2 * ct_y9clear;
    std::vector<long> gout50clear = fvec50(gin50clear);

    assert(ctx.decrypt(&gout50[0]) == gout50clear[0]);
    std::vector<RotationPoly> lut51;
    std::vector<long (*)(long)> flut51;
    auto lut51idx0 = [](long I) -> long {
        /* GATE 223 (LUT3 _1598_ INIT 0x78 PERM 120) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut51.push_back(ctx.genrate_lut(lut51idx0));
    flut51.push_back(lut51idx0);

    auto lut51idx1 = [](long I) -> long {
        /* GATE 263 (LUT3 _1638_ INIT 0x80 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut51.push_back(ctx.genrate_lut(lut51idx1));
    flut51.push_back(lut51idx1);

    auto fvec51 = [flut51](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut51[i](I));
        return ret;
    };

    std::cerr << "\rLUT51   ";
    Ciphertext gin51 = 1 * gout50[0] + 2 * ct_x0 + 4 * ct_y10;
    std::vector<Ciphertext> gout51 = ctx.eval_lut_amortized(&gin51, lut51);

    long gin51clear = 1 * gout50clear[0] + 2 * ct_x0clear + 4 * ct_y10clear;
    std::vector<long> gout51clear = fvec51(gin51clear);

    assert(ctx.decrypt(&gout51[0]) == gout51clear[0]);
    assert(ctx.decrypt(&gout51[1]) == gout51clear[1]);
    std::vector<RotationPoly> lut52;
    std::vector<long (*)(long)> flut52;
    auto lut52idx0 = [](long I) -> long {
        /* GATE 47 (LUT2 _1422_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut52.push_back(ctx.genrate_lut(lut52idx0));
    flut52.push_back(lut52idx0);

    auto fvec52 = [flut52](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut52[i](I));
        return ret;
    };

    std::cerr << "\rLUT52   ";
    Ciphertext gin52 = 1 * ct_x4 + 2 * ct_y0;
    std::vector<Ciphertext> gout52 = ctx.eval_lut_amortized(&gin52, lut52);

    long gin52clear = 1 * ct_x4clear + 2 * ct_y0clear;
    std::vector<long> gout52clear = fvec52(gin52clear);

    assert(ctx.decrypt(&gout52[0]) == gout52clear[0]);
    std::vector<RotationPoly> lut53;
    std::vector<long (*)(long)> flut53;
    auto lut53idx0 = [](long I) -> long {
        /* GATE 393 (LUT2 _1768_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut53.push_back(ctx.genrate_lut(lut53idx0));
    flut53.push_back(lut53idx0);

    auto fvec53 = [flut53](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut53[i](I));
        return ret;
    };

    std::cerr << "\rLUT53   ";
    Ciphertext gin53 = 1 * ct_x4 + 2 * ct_y10;
    std::vector<Ciphertext> gout53 = ctx.eval_lut_amortized(&gin53, lut53);

    long gin53clear = 1 * ct_x4clear + 2 * ct_y10clear;
    std::vector<long> gout53clear = fvec53(gin53clear);

    assert(ctx.decrypt(&gout53[0]) == gout53clear[0]);
    std::vector<RotationPoly> lut54;
    std::vector<long (*)(long)> flut54;
    auto lut54idx0 = [](long I) -> long {
        /* GATE 140 (LUT2 _1515_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut54.push_back(ctx.genrate_lut(lut54idx0));
    flut54.push_back(lut54idx0);

    auto fvec54 = [flut54](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut54[i](I));
        return ret;
    };

    std::cerr << "\rLUT54   ";
    Ciphertext gin54 = 1 * ct_x4 + 2 * ct_y4;
    std::vector<Ciphertext> gout54 = ctx.eval_lut_amortized(&gin54, lut54);

    long gin54clear = 1 * ct_x4clear + 2 * ct_y4clear;
    std::vector<long> gout54clear = fvec54(gin54clear);

    assert(ctx.decrypt(&gout54[0]) == gout54clear[0]);
    std::vector<RotationPoly> lut55;
    std::vector<long (*)(long)> flut55;
    auto lut55idx0 = [](long I) -> long {
        /* GATE 295 (LUT2 _1670_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut55.push_back(ctx.genrate_lut(lut55idx0));
    flut55.push_back(lut55idx0);

    auto fvec55 = [flut55](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut55[i](I));
        return ret;
    };

    std::cerr << "\rLUT55   ";
    Ciphertext gin55 = 1 * ct_y3 + 2 * ct_x9;
    std::vector<Ciphertext> gout55 = ctx.eval_lut_amortized(&gin55, lut55);

    long gin55clear = 1 * ct_y3clear + 2 * ct_x9clear;
    std::vector<long> gout55clear = fvec55(gin55clear);

    assert(ctx.decrypt(&gout55[0]) == gout55clear[0]);
    std::vector<RotationPoly> lut56;
    std::vector<long (*)(long)> flut56;
    auto lut56idx0 = [](long I) -> long {
        /* GATE 248 (LUT2 _1623_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut56.push_back(ctx.genrate_lut(lut56idx0));
    flut56.push_back(lut56idx0);

    auto fvec56 = [flut56](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut56[i](I));
        return ret;
    };

    std::cerr << "\rLUT56   ";
    Ciphertext gin56 = 1 * ct_x11 + 2 * ct_y0;
    std::vector<Ciphertext> gout56 = ctx.eval_lut_amortized(&gin56, lut56);

    long gin56clear = 1 * ct_x11clear + 2 * ct_y0clear;
    std::vector<long> gout56clear = fvec56(gin56clear);

    assert(ctx.decrypt(&gout56[0]) == gout56clear[0]);
    std::vector<RotationPoly> lut57;
    std::vector<long (*)(long)> flut57;
    auto lut57idx0 = [](long I) -> long {
        /* GATE 265 (LUT2 _1640_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut57.push_back(ctx.genrate_lut(lut57idx0));
    flut57.push_back(lut57idx0);

    auto fvec57 = [flut57](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut57[i](I));
        return ret;
    };

    std::cerr << "\rLUT57   ";
    Ciphertext gin57 = 1 * ct_x1 + 2 * ct_y10;
    std::vector<Ciphertext> gout57 = ctx.eval_lut_amortized(&gin57, lut57);

    long gin57clear = 1 * ct_x1clear + 2 * ct_y10clear;
    std::vector<long> gout57clear = fvec57(gin57clear);

    assert(ctx.decrypt(&gout57[0]) == gout57clear[0]);
    std::vector<RotationPoly> lut58;
    std::vector<long (*)(long)> flut58;
    auto lut58idx0 = [](long I) -> long {
        /* GATE 209 (LUT2 _1584_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut58.push_back(ctx.genrate_lut(lut58idx0));
    flut58.push_back(lut58idx0);

    auto fvec58 = [flut58](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut58[i](I));
        return ret;
    };

    std::cerr << "\rLUT58   ";
    Ciphertext gin58 = 1 * ct_x10 + 2 * ct_y0;
    std::vector<Ciphertext> gout58 = ctx.eval_lut_amortized(&gin58, lut58);

    long gin58clear = 1 * ct_x10clear + 2 * ct_y0clear;
    std::vector<long> gout58clear = fvec58(gin58clear);

    assert(ctx.decrypt(&gout58[0]) == gout58clear[0]);
    std::vector<RotationPoly> lut59;
    std::vector<long (*)(long)> flut59;
    auto lut59idx0 = [](long I) -> long {
        /* GATE 294 (LUT2 _1669_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut59.push_back(ctx.genrate_lut(lut59idx0));
    flut59.push_back(lut59idx0);

    auto fvec59 = [flut59](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut59[i](I));
        return ret;
    };

    std::cerr << "\rLUT59   ";
    Ciphertext gin59 = 1 * ct_y5 + 2 * ct_x7;
    std::vector<Ciphertext> gout59 = ctx.eval_lut_amortized(&gin59, lut59);

    long gin59clear = 1 * ct_y5clear + 2 * ct_x7clear;
    std::vector<long> gout59clear = fvec59(gin59clear);

    assert(ctx.decrypt(&gout59[0]) == gout59clear[0]);
    std::vector<RotationPoly> lut60;
    std::vector<long (*)(long)> flut60;
    auto lut60idx0 = [](long I) -> long {
        /* GATE 292 (LUT3 _1667_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut60.push_back(ctx.genrate_lut(lut60idx0));
    flut60.push_back(lut60idx0);

    auto lut60idx1 = [](long I) -> long {
        /* GATE 343 (LUT3 _1718_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut60.push_back(ctx.genrate_lut(lut60idx1));
    flut60.push_back(lut60idx1);

    auto fvec60 = [flut60](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut60[i](I));
        return ret;
    };

    std::cerr << "\rLUT60   ";
    Ciphertext gin60 = 1 * gout38[0] + 2 * gout59[0] + 4 * gout55[0];
    std::vector<Ciphertext> gout60 = ctx.eval_lut_amortized(&gin60, lut60);

    long gin60clear = 1 * gout38clear[0] + 2 * gout59clear[0] + 4 * gout55clear[0];
    std::vector<long> gout60clear = fvec60(gin60clear);

    assert(ctx.decrypt(&gout60[0]) == gout60clear[0]);
    assert(ctx.decrypt(&gout60[1]) == gout60clear[1]);
    std::vector<RotationPoly> lut61;
    std::vector<long (*)(long)> flut61;
    auto lut61idx0 = [](long I) -> long {
        /* GATE 147 (LUT2 _1522_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut61.push_back(ctx.genrate_lut(lut61idx0));
    flut61.push_back(lut61idx0);

    auto fvec61 = [flut61](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut61[i](I));
        return ret;
    };

    std::cerr << "\rLUT61   ";
    Ciphertext gin61 = 1 * ct_x1 + 2 * ct_y7;
    std::vector<Ciphertext> gout61 = ctx.eval_lut_amortized(&gin61, lut61);

    long gin61clear = 1 * ct_x1clear + 2 * ct_y7clear;
    std::vector<long> gout61clear = fvec61(gin61clear);

    assert(ctx.decrypt(&gout61[0]) == gout61clear[0]);
    std::vector<RotationPoly> lut62;
    std::vector<long (*)(long)> flut62;
    auto lut62idx0 = [](long I) -> long {
        /* GATE 387 (LUT2 _1762_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut62.push_back(ctx.genrate_lut(lut62idx0));
    flut62.push_back(lut62idx0);

    auto fvec62 = [flut62](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut62[i](I));
        return ret;
    };

    std::cerr << "\rLUT62   ";
    Ciphertext gin62 = 1 * ct_x6 + 2 * ct_y8;
    std::vector<Ciphertext> gout62 = ctx.eval_lut_amortized(&gin62, lut62);

    long gin62clear = 1 * ct_x6clear + 2 * ct_y8clear;
    std::vector<long> gout62clear = fvec62(gin62clear);

    assert(ctx.decrypt(&gout62[0]) == gout62clear[0]);
    std::vector<RotationPoly> lut63;
    std::vector<long (*)(long)> flut63;
    auto lut63idx0 = [](long I) -> long {
        /* GATE 346 (LUT2 _1721_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut63.push_back(ctx.genrate_lut(lut63idx0));
    flut63.push_back(lut63idx0);

    auto fvec63 = [flut63](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut63[i](I));
        return ret;
    };

    std::cerr << "\rLUT63   ";
    Ciphertext gin63 = 1 * ct_y8 + 2 * ct_x5;
    std::vector<Ciphertext> gout63 = ctx.eval_lut_amortized(&gin63, lut63);

    long gin63clear = 1 * ct_y8clear + 2 * ct_x5clear;
    std::vector<long> gout63clear = fvec63(gin63clear);

    assert(ctx.decrypt(&gout63[0]) == gout63clear[0]);
    std::vector<RotationPoly> lut64;
    std::vector<long (*)(long)> flut64;
    auto lut64idx0 = [](long I) -> long {
        /* GATE 220 (LUT2 _1595_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut64.push_back(ctx.genrate_lut(lut64idx0));
    flut64.push_back(lut64idx0);

    auto fvec64 = [flut64](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut64[i](I));
        return ret;
    };

    std::cerr << "\rLUT64   ";
    Ciphertext gin64 = 1 * ct_y6 + 2 * ct_x4;
    std::vector<Ciphertext> gout64 = ctx.eval_lut_amortized(&gin64, lut64);

    long gin64clear = 1 * ct_y6clear + 2 * ct_x4clear;
    std::vector<long> gout64clear = fvec64(gin64clear);

    assert(ctx.decrypt(&gout64[0]) == gout64clear[0]);
    std::vector<RotationPoly> lut65;
    std::vector<long (*)(long)> flut65;
    auto lut65idx0 = [](long I) -> long {
        /* GATE 67 (LUT2 _1442_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut65.push_back(ctx.genrate_lut(lut65idx0));
    flut65.push_back(lut65idx0);

    auto fvec65 = [flut65](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut65[i](I));
        return ret;
    };

    std::cerr << "\rLUT65   ";
    Ciphertext gin65 = 1 * ct_x0 + 2 * ct_y5;
    std::vector<Ciphertext> gout65 = ctx.eval_lut_amortized(&gin65, lut65);

    long gin65clear = 1 * ct_x0clear + 2 * ct_y5clear;
    std::vector<long> gout65clear = fvec65(gin65clear);

    assert(ctx.decrypt(&gout65[0]) == gout65clear[0]);
    std::vector<RotationPoly> lut66;
    std::vector<long (*)(long)> flut66;
    auto lut66idx0 = [](long I) -> long {
        /* GATE 336 (LUT2 _1711_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut66.push_back(ctx.genrate_lut(lut66idx0));
    flut66.push_back(lut66idx0);

    auto fvec66 = [flut66](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut66[i](I));
        return ret;
    };

    std::cerr << "\rLUT66   ";
    Ciphertext gin66 = 1 * ct_x13 + 2 * ct_y0;
    std::vector<Ciphertext> gout66 = ctx.eval_lut_amortized(&gin66, lut66);

    long gin66clear = 1 * ct_x13clear + 2 * ct_y0clear;
    std::vector<long> gout66clear = fvec66(gin66clear);

    assert(ctx.decrypt(&gout66[0]) == gout66clear[0]);
    std::vector<RotationPoly> lut67;
    std::vector<long (*)(long)> flut67;
    auto lut67idx0 = [](long I) -> long {
        /* GATE 7 (LUT2 _1382_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut67.push_back(ctx.genrate_lut(lut67idx0));
    flut67.push_back(lut67idx0);

    auto fvec67 = [flut67](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut67[i](I));
        return ret;
    };

    std::cerr << "\rLUT67   ";
    Ciphertext gin67 = 1 * gout37[0] + 2 * gout21[0];
    std::vector<Ciphertext> gout67 = ctx.eval_lut_amortized(&gin67, lut67);

    long gin67clear = 1 * gout37clear[0] + 2 * gout21clear[0];
    std::vector<long> gout67clear = fvec67(gin67clear);

    assert(ctx.decrypt(&gout67[0]) == gout67clear[0]);
    std::vector<RotationPoly> lut68;
    std::vector<long (*)(long)> flut68;
    auto lut68idx0 = [](long I) -> long {
        /* GATE 46 (LUT2 _1421_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut68.push_back(ctx.genrate_lut(lut68idx0));
    flut68.push_back(lut68idx0);

    auto fvec68 = [flut68](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut68[i](I));
        return ret;
    };

    std::cerr << "\rLUT68   ";
    Ciphertext gin68 = 1 * ct_x2 + 2 * ct_y2;
    std::vector<Ciphertext> gout68 = ctx.eval_lut_amortized(&gin68, lut68);

    long gin68clear = 1 * ct_x2clear + 2 * ct_y2clear;
    std::vector<long> gout68clear = fvec68(gin68clear);

    assert(ctx.decrypt(&gout68[0]) == gout68clear[0]);
    std::vector<RotationPoly> lut69;
    std::vector<long (*)(long)> flut69;
    auto lut69idx0 = [](long I) -> long {
        /* GATE 44 (LUT3 _1419_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut69.push_back(ctx.genrate_lut(lut69idx0));
    flut69.push_back(lut69idx0);

    auto lut69idx1 = [](long I) -> long {
        /* GATE 60 (LUT3 _1435_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut69.push_back(ctx.genrate_lut(lut69idx1));
    flut69.push_back(lut69idx1);

    auto fvec69 = [flut69](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut69[i](I));
        return ret;
    };

    std::cerr << "\rLUT69   ";
    Ciphertext gin69 = 1 * gout18[0] + 2 * gout68[0] + 4 * gout52[0];
    std::vector<Ciphertext> gout69 = ctx.eval_lut_amortized(&gin69, lut69);

    long gin69clear = 1 * gout18clear[0] + 2 * gout68clear[0] + 4 * gout52clear[0];
    std::vector<long> gout69clear = fvec69(gin69clear);

    assert(ctx.decrypt(&gout69[0]) == gout69clear[0]);
    assert(ctx.decrypt(&gout69[1]) == gout69clear[1]);
    std::vector<RotationPoly> lut70;
    std::vector<long (*)(long)> flut70;
    auto lut70idx0 = [](long I) -> long {
        /* GATE 33 (LUT2 _1408_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut70.push_back(ctx.genrate_lut(lut70idx0));
    flut70.push_back(lut70idx0);

    auto fvec70 = [flut70](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut70[i](I));
        return ret;
    };

    std::cerr << "\rLUT70   ";
    Ciphertext gin70 = 1 * ct_y0 + 2 * ct_x3;
    std::vector<Ciphertext> gout70 = ctx.eval_lut_amortized(&gin70, lut70);

    long gin70clear = 1 * ct_y0clear + 2 * ct_x3clear;
    std::vector<long> gout70clear = fvec70(gin70clear);

    assert(ctx.decrypt(&gout70[0]) == gout70clear[0]);
    std::vector<RotationPoly> lut71;
    std::vector<long (*)(long)> flut71;
    auto lut71idx0 = [](long I) -> long {
        /* GATE 431 (LUT2 _1806_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut71.push_back(ctx.genrate_lut(lut71idx0));
    flut71.push_back(lut71idx0);

    auto fvec71 = [flut71](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut71[i](I));
        return ret;
    };

    std::cerr << "\rLUT71   ";
    Ciphertext gin71 = 1 * ct_y6 + 2 * ct_x9;
    std::vector<Ciphertext> gout71 = ctx.eval_lut_amortized(&gin71, lut71);

    long gin71clear = 1 * ct_y6clear + 2 * ct_x9clear;
    std::vector<long> gout71clear = fvec71(gin71clear);

    assert(ctx.decrypt(&gout71[0]) == gout71clear[0]);
    std::vector<RotationPoly> lut72;
    std::vector<long (*)(long)> flut72;
    auto lut72idx0 = [](long I) -> long {
        /* GATE 430 (LUT3 _1805_ INIT 0x87 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut72.push_back(ctx.genrate_lut(lut72idx0));
    flut72.push_back(lut72idx0);

    auto fvec72 = [flut72](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut72[i](I));
        return ret;
    };

    std::cerr << "\rLUT72   ";
    Ciphertext gin72 = 1 * ct_x10 + 2 * gout71[0] + 4 * ct_y5;
    std::vector<Ciphertext> gout72 = ctx.eval_lut_amortized(&gin72, lut72);

    long gin72clear = 1 * ct_x10clear + 2 * gout71clear[0] + 4 * ct_y5clear;
    std::vector<long> gout72clear = fvec72(gin72clear);

    assert(ctx.decrypt(&gout72[0]) == gout72clear[0]);
    std::vector<RotationPoly> lut73;
    std::vector<long (*)(long)> flut73;
    auto lut73idx0 = [](long I) -> long {
        /* GATE 345 (LUT2 _1720_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut73.push_back(ctx.genrate_lut(lut73idx0));
    flut73.push_back(lut73idx0);

    auto fvec73 = [flut73](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut73[i](I));
        return ret;
    };

    std::cerr << "\rLUT73   ";
    Ciphertext gin73 = 1 * ct_y7 + 2 * ct_x6;
    std::vector<Ciphertext> gout73 = ctx.eval_lut_amortized(&gin73, lut73);

    long gin73clear = 1 * ct_y7clear + 2 * ct_x6clear;
    std::vector<long> gout73clear = fvec73(gin73clear);

    assert(ctx.decrypt(&gout73[0]) == gout73clear[0]);
    std::cerr << "\rFA74    ";
    Ciphertext gin74 = gout44[2] + 1 * ct_x2 + 2 * ct_x3 + 1 * gout8[0] + 2 * gout10[0];
    std::vector<Ciphertext> gout74 = ctx.eval_lut_amortized(&gin74, decomp);

    long gin74clear = gout44clear[2] + 1 * ct_x2clear + 2 * ct_x3clear + 1 * gout8clear[0] + 2 * gout10clear[0];
    std::vector<long> gout74clear = vdecomp(gin74clear);

    assert(ctx.decrypt(&gout74[0]) == gout74clear[0]);
    assert(ctx.decrypt(&gout74[1]) == gout74clear[1]);
    std::cerr << "\rFA75    ";
    Ciphertext gin75 = gout74[2] + 1 * ct_x4 + 2 * ct_x5 + 1 * gout9[0] + 2 * gout7[0];
    std::vector<Ciphertext> gout75 = ctx.eval_lut_amortized(&gin75, decomp);

    long gin75clear = gout74clear[2] + 1 * ct_x4clear + 2 * ct_x5clear + 1 * gout9clear[0] + 2 * gout7clear[0];
    std::vector<long> gout75clear = vdecomp(gin75clear);

    assert(ctx.decrypt(&gout75[0]) == gout75clear[0]);
    assert(ctx.decrypt(&gout75[1]) == gout75clear[1]);
    std::vector<RotationPoly> lut76;
    std::vector<long (*)(long)> flut76;
    auto lut76idx0 = [](long I) -> long {
        /* GATE 354 (LUT2 _1729_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut76.push_back(ctx.genrate_lut(lut76idx0));
    flut76.push_back(lut76idx0);

    auto fvec76 = [flut76](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut76[i](I));
        return ret;
    };

    std::cerr << "\rLUT76   ";
    Ciphertext gin76 = 1 * ct_y10 + 2 * ct_x3;
    std::vector<Ciphertext> gout76 = ctx.eval_lut_amortized(&gin76, lut76);

    long gin76clear = 1 * ct_y10clear + 2 * ct_x3clear;
    std::vector<long> gout76clear = fvec76(gin76clear);

    assert(ctx.decrypt(&gout76[0]) == gout76clear[0]);
    std::vector<RotationPoly> lut77;
    std::vector<long (*)(long)> flut77;
    auto lut77idx0 = [](long I) -> long {
        /* GATE 88 (LUT2 _1463_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut77.push_back(ctx.genrate_lut(lut77idx0));
    flut77.push_back(lut77idx0);

    auto fvec77 = [flut77](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut77[i](I));
        return ret;
    };

    std::cerr << "\rLUT77   ";
    Ciphertext gin77 = 1 * ct_y0 + 2 * ct_x6;
    std::vector<Ciphertext> gout77 = ctx.eval_lut_amortized(&gin77, lut77);

    long gin77clear = 1 * ct_y0clear + 2 * ct_x6clear;
    std::vector<long> gout77clear = fvec77(gin77clear);

    assert(ctx.decrypt(&gout77[0]) == gout77clear[0]);
    std::cerr << "\rFA78    ";
    Ciphertext gin78 = 1 * ct_x0 + 2 * ct_x1 + 1 * ct_y0 + 2 * ct_y1;
    std::vector<Ciphertext> gout78 = ctx.eval_lut_amortized(&gin78, decomp);

    long gin78clear = 1 * ct_x0clear + 2 * ct_x1clear + 1 * ct_y0clear + 2 * ct_y1clear;
    std::vector<long> gout78clear = vdecomp(gin78clear);

    assert(ctx.decrypt(&gout78[0]) == gout78clear[0]);
    assert(ctx.decrypt(&gout78[1]) == gout78clear[1]);
    std::vector<RotationPoly> lut79;
    std::vector<long (*)(long)> flut79;
    auto lut79idx0 = [](long I) -> long {
        /* GATE 208 (LUT2 _1583_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut79.push_back(ctx.genrate_lut(lut79idx0));
    flut79.push_back(lut79idx0);

    auto fvec79 = [flut79](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut79[i](I));
        return ret;
    };

    std::cerr << "\rLUT79   ";
    Ciphertext gin79 = 1 * ct_x8 + 2 * ct_y2;
    std::vector<Ciphertext> gout79 = ctx.eval_lut_amortized(&gin79, lut79);

    long gin79clear = 1 * ct_x8clear + 2 * ct_y2clear;
    std::vector<long> gout79clear = fvec79(gin79clear);

    assert(ctx.decrypt(&gout79[0]) == gout79clear[0]);
    std::vector<RotationPoly> lut80;
    std::vector<long (*)(long)> flut80;
    auto lut80idx0 = [](long I) -> long {
        /* GATE 259 (LUT2 _1634_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut80.push_back(ctx.genrate_lut(lut80idx0));
    flut80.push_back(lut80idx0);

    auto fvec80 = [flut80](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut80[i](I));
        return ret;
    };

    std::cerr << "\rLUT80   ";
    Ciphertext gin80 = 1 * ct_y6 + 2 * ct_x5;
    std::vector<Ciphertext> gout80 = ctx.eval_lut_amortized(&gin80, lut80);

    long gin80clear = 1 * ct_y6clear + 2 * ct_x5clear;
    std::vector<long> gout80clear = fvec80(gin80clear);

    assert(ctx.decrypt(&gout80[0]) == gout80clear[0]);
    std::vector<RotationPoly> lut81;
    std::vector<long (*)(long)> flut81;
    auto lut81idx0 = [](long I) -> long {
        /* GATE 183 (LUT2 _1558_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut81.push_back(ctx.genrate_lut(lut81idx0));
    flut81.push_back(lut81idx0);

    auto fvec81 = [flut81](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut81[i](I));
        return ret;
    };

    std::cerr << "\rLUT81   ";
    Ciphertext gin81 = 1 * ct_x1 + 2 * ct_y8;
    std::vector<Ciphertext> gout81 = ctx.eval_lut_amortized(&gin81, lut81);

    long gin81clear = 1 * ct_x1clear + 2 * ct_y8clear;
    std::vector<long> gout81clear = fvec81(gin81clear);

    assert(ctx.decrypt(&gout81[0]) == gout81clear[0]);
    std::vector<RotationPoly> lut82;
    std::vector<long (*)(long)> flut82;
    auto lut82idx0 = [](long I) -> long {
        /* GATE 90 (LUT2 _1465_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut82.push_back(ctx.genrate_lut(lut82idx0));
    flut82.push_back(lut82idx0);

    auto fvec82 = [flut82](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut82[i](I));
        return ret;
    };

    std::cerr << "\rLUT82   ";
    Ciphertext gin82 = 1 * ct_x2 + 2 * ct_y4;
    std::vector<Ciphertext> gout82 = ctx.eval_lut_amortized(&gin82, lut82);

    long gin82clear = 1 * ct_x2clear + 2 * ct_y4clear;
    std::vector<long> gout82clear = fvec82(gin82clear);

    assert(ctx.decrypt(&gout82[0]) == gout82clear[0]);
    std::vector<RotationPoly> lut83;
    std::vector<long (*)(long)> flut83;
    auto lut83idx0 = [](long I) -> long {
        /* GATE 115 (LUT3 _1490_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut83.push_back(ctx.genrate_lut(lut83idx0));
    flut83.push_back(lut83idx0);

    auto lut83idx1 = [](long I) -> long {
        /* GATE 89 (LUT3 _1464_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut83.push_back(ctx.genrate_lut(lut83idx1));
    flut83.push_back(lut83idx1);

    auto fvec83 = [flut83](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut83[i](I));
        return ret;
    };

    std::cerr << "\rLUT83   ";
    Ciphertext gin83 = 1 * gout82[0] + 2 * gout42[0] + 4 * gout19[0];
    std::vector<Ciphertext> gout83 = ctx.eval_lut_amortized(&gin83, lut83);

    long gin83clear = 1 * gout82clear[0] + 2 * gout42clear[0] + 4 * gout19clear[0];
    std::vector<long> gout83clear = fvec83(gin83clear);

    assert(ctx.decrypt(&gout83[0]) == gout83clear[0]);
    assert(ctx.decrypt(&gout83[1]) == gout83clear[1]);
    std::vector<RotationPoly> lut84;
    std::vector<long (*)(long)> flut84;
    auto lut84idx0 = [](long I) -> long {
        /* GATE 335 (LUT2 _1710_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut84.push_back(ctx.genrate_lut(lut84idx0));
    flut84.push_back(lut84idx0);

    auto fvec84 = [flut84](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut84[i](I));
        return ret;
    };

    std::cerr << "\rLUT84   ";
    Ciphertext gin84 = 1 * ct_x11 + 2 * ct_y2;
    std::vector<Ciphertext> gout84 = ctx.eval_lut_amortized(&gin84, lut84);

    long gin84clear = 1 * ct_x11clear + 2 * ct_y2clear;
    std::vector<long> gout84clear = fvec84(gin84clear);

    assert(ctx.decrypt(&gout84[0]) == gout84clear[0]);
    std::vector<RotationPoly> lut85;
    std::vector<long (*)(long)> flut85;
    auto lut85idx0 = [](long I) -> long {
        /* GATE 207 (LUT2 _1582_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut85.push_back(ctx.genrate_lut(lut85idx0));
    flut85.push_back(lut85idx0);

    auto fvec85 = [flut85](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut85[i](I));
        return ret;
    };

    std::cerr << "\rLUT85   ";
    Ciphertext gin85 = 1 * ct_x9 + 2 * ct_y1;
    std::vector<Ciphertext> gout85 = ctx.eval_lut_amortized(&gin85, lut85);

    long gin85clear = 1 * ct_x9clear + 2 * ct_y1clear;
    std::vector<long> gout85clear = fvec85(gin85clear);

    assert(ctx.decrypt(&gout85[0]) == gout85clear[0]);
    std::vector<RotationPoly> lut86;
    std::vector<long (*)(long)> flut86;
    auto lut86idx0 = [](long I) -> long {
        /* GATE 244 (LUT3 _1619_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut86.push_back(ctx.genrate_lut(lut86idx0));
    flut86.push_back(lut86idx0);

    auto lut86idx1 = [](long I) -> long {
        /* GATE 206 (LUT3 _1581_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut86.push_back(ctx.genrate_lut(lut86idx1));
    flut86.push_back(lut86idx1);

    auto fvec86 = [flut86](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut86[i](I));
        return ret;
    };

    std::cerr << "\rLUT86   ";
    Ciphertext gin86 = 1 * gout85[0] + 2 * gout79[0] + 4 * gout58[0];
    std::vector<Ciphertext> gout86 = ctx.eval_lut_amortized(&gin86, lut86);

    long gin86clear = 1 * gout85clear[0] + 2 * gout79clear[0] + 4 * gout58clear[0];
    std::vector<long> gout86clear = fvec86(gin86clear);

    assert(ctx.decrypt(&gout86[0]) == gout86clear[0]);
    assert(ctx.decrypt(&gout86[1]) == gout86clear[1]);
    std::vector<RotationPoly> lut87;
    std::vector<long (*)(long)> flut87;
    auto lut87idx0 = [](long I) -> long {
        /* GATE 49 (LUT2 _1424_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut87.push_back(ctx.genrate_lut(lut87idx0));
    flut87.push_back(lut87idx0);

    auto fvec87 = [flut87](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut87[i](I));
        return ret;
    };

    std::cerr << "\rLUT87   ";
    Ciphertext gin87 = 1 * ct_x1 + 2 * ct_y3;
    std::vector<Ciphertext> gout87 = ctx.eval_lut_amortized(&gin87, lut87);

    long gin87clear = 1 * ct_x1clear + 2 * ct_y3clear;
    std::vector<long> gout87clear = fvec87(gin87clear);

    assert(ctx.decrypt(&gout87[0]) == gout87clear[0]);
    std::vector<RotationPoly> lut88;
    std::vector<long (*)(long)> flut88;
    auto lut88idx0 = [](long I) -> long {
        /* GATE 87 (LUT2 _1462_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut88.push_back(ctx.genrate_lut(lut88idx0));
    flut88.push_back(lut88idx0);

    auto fvec88 = [flut88](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut88[i](I));
        return ret;
    };

    std::cerr << "\rLUT88   ";
    Ciphertext gin88 = 1 * ct_x4 + 2 * ct_y2;
    std::vector<Ciphertext> gout88 = ctx.eval_lut_amortized(&gin88, lut88);

    long gin88clear = 1 * ct_x4clear + 2 * ct_y2clear;
    std::vector<long> gout88clear = fvec88(gin88clear);

    assert(ctx.decrypt(&gout88[0]) == gout88clear[0]);
    std::vector<RotationPoly> lut89;
    std::vector<long (*)(long)> flut89;
    auto lut89idx0 = [](long I) -> long {
        /* GATE 301 (LUT2 _1676_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut89.push_back(ctx.genrate_lut(lut89idx0));
    flut89.push_back(lut89idx0);

    auto fvec89 = [flut89](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut89[i](I));
        return ret;
    };

    std::cerr << "\rLUT89   ";
    Ciphertext gin89 = 1 * ct_x4 + 2 * ct_y8;
    std::vector<Ciphertext> gout89 = ctx.eval_lut_amortized(&gin89, lut89);

    long gin89clear = 1 * ct_x4clear + 2 * ct_y8clear;
    std::vector<long> gout89clear = fvec89(gin89clear);

    assert(ctx.decrypt(&gout89[0]) == gout89clear[0]);
    std::vector<RotationPoly> lut90;
    std::vector<long (*)(long)> flut90;
    auto lut90idx0 = [](long I) -> long {
        /* GATE 182 (LUT2 _1557_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut90.push_back(ctx.genrate_lut(lut90idx0));
    flut90.push_back(lut90idx0);

    auto fvec90 = [flut90](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut90[i](I));
        return ret;
    };

    std::cerr << "\rLUT90   ";
    Ciphertext gin90 = 1 * ct_x2 + 2 * ct_y7;
    std::vector<Ciphertext> gout90 = ctx.eval_lut_amortized(&gin90, lut90);

    long gin90clear = 1 * ct_x2clear + 2 * ct_y7clear;
    std::vector<long> gout90clear = fvec90(gin90clear);

    assert(ctx.decrypt(&gout90[0]) == gout90clear[0]);
    std::vector<RotationPoly> lut91;
    std::vector<long (*)(long)> flut91;
    auto lut91idx0 = [](long I) -> long {
        /* GATE 211 (LUT2 _1586_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut91.push_back(ctx.genrate_lut(lut91idx0));
    flut91.push_back(lut91idx0);

    auto fvec91 = [flut91](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut91[i](I));
        return ret;
    };

    std::cerr << "\rLUT91   ";
    Ciphertext gin91 = 1 * ct_y4 + 2 * ct_x6;
    std::vector<Ciphertext> gout91 = ctx.eval_lut_amortized(&gin91, lut91);

    long gin91clear = 1 * ct_y4clear + 2 * ct_x6clear;
    std::vector<long> gout91clear = fvec91(gin91clear);

    assert(ctx.decrypt(&gout91[0]) == gout91clear[0]);
    std::vector<RotationPoly> lut92;
    std::vector<long (*)(long)> flut92;
    auto lut92idx0 = [](long I) -> long {
        /* GATE 255 (LUT3 _1630_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut92.push_back(ctx.genrate_lut(lut92idx0));
    flut92.push_back(lut92idx0);

    auto lut92idx1 = [](long I) -> long {
        /* GATE 210 (LUT3 _1585_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut92.push_back(ctx.genrate_lut(lut92idx1));
    flut92.push_back(lut92idx1);

    auto fvec92 = [flut92](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut92[i](I));
        return ret;
    };

    std::cerr << "\rLUT92   ";
    Ciphertext gin92 = 1 * gout91[0] + 2 * gout25[0] + 4 * gout48[0];
    std::vector<Ciphertext> gout92 = ctx.eval_lut_amortized(&gin92, lut92);

    long gin92clear = 1 * gout91clear[0] + 2 * gout25clear[0] + 4 * gout48clear[0];
    std::vector<long> gout92clear = fvec92(gin92clear);

    assert(ctx.decrypt(&gout92[0]) == gout92clear[0]);
    assert(ctx.decrypt(&gout92[1]) == gout92clear[1]);
    std::vector<RotationPoly> lut93;
    std::vector<long (*)(long)> flut93;
    auto lut93idx0 = [](long I) -> long {
        /* GATE 32 (LUT2 _1407_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut93.push_back(ctx.genrate_lut(lut93idx0));
    flut93.push_back(lut93idx0);

    auto fvec93 = [flut93](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut93[i](I));
        return ret;
    };

    std::cerr << "\rLUT93   ";
    Ciphertext gin93 = 1 * ct_x1 + 2 * ct_y2;
    std::vector<Ciphertext> gout93 = ctx.eval_lut_amortized(&gin93, lut93);

    long gin93clear = 1 * ct_x1clear + 2 * ct_y2clear;
    std::vector<long> gout93clear = fvec93(gin93clear);

    assert(ctx.decrypt(&gout93[0]) == gout93clear[0]);
    std::vector<RotationPoly> lut94;
    std::vector<long (*)(long)> flut94;
    auto lut94idx0 = [](long I) -> long {
        /* GATE 334 (LUT2 _1709_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut94.push_back(ctx.genrate_lut(lut94idx0));
    flut94.push_back(lut94idx0);

    auto fvec94 = [flut94](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut94[i](I));
        return ret;
    };

    std::cerr << "\rLUT94   ";
    Ciphertext gin94 = 1 * ct_x12 + 2 * ct_y1;
    std::vector<Ciphertext> gout94 = ctx.eval_lut_amortized(&gin94, lut94);

    long gin94clear = 1 * ct_x12clear + 2 * ct_y1clear;
    std::vector<long> gout94clear = fvec94(gin94clear);

    assert(ctx.decrypt(&gout94[0]) == gout94clear[0]);
    std::vector<RotationPoly> lut95;
    std::vector<long (*)(long)> flut95;
    auto lut95idx0 = [](long I) -> long {
        /* GATE 333 (LUT3 _1708_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut95.push_back(ctx.genrate_lut(lut95idx0));
    flut95.push_back(lut95idx0);

    auto lut95idx1 = [](long I) -> long {
        /* GATE 376 (LUT3 _1751_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut95.push_back(ctx.genrate_lut(lut95idx1));
    flut95.push_back(lut95idx1);

    auto fvec95 = [flut95](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut95[i](I));
        return ret;
    };

    std::cerr << "\rLUT95   ";
    Ciphertext gin95 = 1 * gout94[0] + 2 * gout84[0] + 4 * gout66[0];
    std::vector<Ciphertext> gout95 = ctx.eval_lut_amortized(&gin95, lut95);

    long gin95clear = 1 * gout94clear[0] + 2 * gout84clear[0] + 4 * gout66clear[0];
    std::vector<long> gout95clear = fvec95(gin95clear);

    assert(ctx.decrypt(&gout95[0]) == gout95clear[0]);
    assert(ctx.decrypt(&gout95[1]) == gout95clear[1]);
    std::vector<RotationPoly> lut96;
    std::vector<long (*)(long)> flut96;
    auto lut96idx0 = [](long I) -> long {
        /* GATE 356 (LUT2 _1731_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut96.push_back(ctx.genrate_lut(lut96idx0));
    flut96.push_back(lut96idx0);

    auto fvec96 = [flut96](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut96[i](I));
        return ret;
    };

    std::cerr << "\rLUT96   ";
    Ciphertext gin96 = 1 * ct_x4 + 2 * ct_y9;
    std::vector<Ciphertext> gout96 = ctx.eval_lut_amortized(&gin96, lut96);

    long gin96clear = 1 * ct_x4clear + 2 * ct_y9clear;
    std::vector<long> gout96clear = fvec96(gin96clear);

    assert(ctx.decrypt(&gout96[0]) == gout96clear[0]);
    std::vector<RotationPoly> lut97;
    std::vector<long (*)(long)> flut97;
    auto lut97idx0 = [](long I) -> long {
        /* GATE 397 (LUT3 _1772_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut97.push_back(ctx.genrate_lut(lut97idx0));
    flut97.push_back(lut97idx0);

    auto lut97idx1 = [](long I) -> long {
        /* GATE 353 (LUT3 _1728_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut97.push_back(ctx.genrate_lut(lut97idx1));
    flut97.push_back(lut97idx1);

    auto fvec97 = [flut97](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut97[i](I));
        return ret;
    };

    std::cerr << "\rLUT97   ";
    Ciphertext gin97 = 1 * gout76[0] + 2 * gout32[0] + 4 * gout96[0];
    std::vector<Ciphertext> gout97 = ctx.eval_lut_amortized(&gin97, lut97);

    long gin97clear = 1 * gout76clear[0] + 2 * gout32clear[0] + 4 * gout96clear[0];
    std::vector<long> gout97clear = fvec97(gin97clear);

    assert(ctx.decrypt(&gout97[0]) == gout97clear[0]);
    assert(ctx.decrypt(&gout97[1]) == gout97clear[1]);
    std::vector<RotationPoly> lut98;
    std::vector<long (*)(long)> flut98;
    auto lut98idx0 = [](long I) -> long {
        /* GATE 258 (LUT2 _1633_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut98.push_back(ctx.genrate_lut(lut98idx0));
    flut98.push_back(lut98idx0);

    auto fvec98 = [flut98](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut98[i](I));
        return ret;
    };

    std::cerr << "\rLUT98   ";
    Ciphertext gin98 = 1 * ct_y8 + 2 * ct_x3;
    std::vector<Ciphertext> gout98 = ctx.eval_lut_amortized(&gin98, lut98);

    long gin98clear = 1 * ct_y8clear + 2 * ct_x3clear;
    std::vector<long> gout98clear = fvec98(gin98clear);

    assert(ctx.decrypt(&gout98[0]) == gout98clear[0]);
    std::cerr << "\rFA99    ";
    Ciphertext gin99 = gout78[2] + 1 * ct_x2 + 2 * ct_x3 + 1 * ct_y2 + 2 * ct_y3;
    std::vector<Ciphertext> gout99 = ctx.eval_lut_amortized(&gin99, decomp);

    long gin99clear = gout78clear[2] + 1 * ct_x2clear + 2 * ct_x3clear + 1 * ct_y2clear + 2 * ct_y3clear;
    std::vector<long> gout99clear = vdecomp(gin99clear);

    assert(ctx.decrypt(&gout99[0]) == gout99clear[0]);
    assert(ctx.decrypt(&gout99[1]) == gout99clear[1]);
    std::vector<RotationPoly> lut100;
    std::vector<long (*)(long)> flut100;
    auto lut100idx0 = [](long I) -> long {
        /* GATE 86 (LUT2 _1461_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut100.push_back(ctx.genrate_lut(lut100idx0));
    flut100.push_back(lut100idx0);

    auto fvec100 = [flut100](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut100[i](I));
        return ret;
    };

    std::cerr << "\rLUT100   ";
    Ciphertext gin100 = 1 * ct_y1 + 2 * ct_x5;
    std::vector<Ciphertext> gout100 = ctx.eval_lut_amortized(&gin100, lut100);

    long gin100clear = 1 * ct_y1clear + 2 * ct_x5clear;
    std::vector<long> gout100clear = fvec100(gin100clear);

    assert(ctx.decrypt(&gout100[0]) == gout100clear[0]);
    std::vector<RotationPoly> lut101;
    std::vector<long (*)(long)> flut101;
    auto lut101idx0 = [](long I) -> long {
        /* GATE 85 (LUT3 _1460_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut101.push_back(ctx.genrate_lut(lut101idx0));
    flut101.push_back(lut101idx0);

    auto lut101idx1 = [](long I) -> long {
        /* GATE 105 (LUT3 _1480_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut101.push_back(ctx.genrate_lut(lut101idx1));
    flut101.push_back(lut101idx1);

    auto fvec101 = [flut101](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut101[i](I));
        return ret;
    };

    std::cerr << "\rLUT101   ";
    Ciphertext gin101 = 1 * gout100[0] + 2 * gout88[0] + 4 * gout77[0];
    std::vector<Ciphertext> gout101 = ctx.eval_lut_amortized(&gin101, lut101);

    long gin101clear = 1 * gout100clear[0] + 2 * gout88clear[0] + 4 * gout77clear[0];
    std::vector<long> gout101clear = fvec101(gin101clear);

    assert(ctx.decrypt(&gout101[0]) == gout101clear[0]);
    assert(ctx.decrypt(&gout101[1]) == gout101clear[1]);
    std::vector<RotationPoly> lut102;
    std::vector<long (*)(long)> flut102;
    auto lut102idx0 = [](long I) -> long {
        /* GATE 435 (LUT2 _1810_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut102.push_back(ctx.genrate_lut(lut102idx0));
    flut102.push_back(lut102idx0);

    auto fvec102 = [flut102](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut102[i](I));
        return ret;
    };

    std::cerr << "\rLUT102   ";
    Ciphertext gin102 = 1 * ct_x12 + 2 * ct_y3;
    std::vector<Ciphertext> gout102 = ctx.eval_lut_amortized(&gin102, lut102);

    long gin102clear = 1 * ct_x12clear + 2 * ct_y3clear;
    std::vector<long> gout102clear = fvec102(gin102clear);

    assert(ctx.decrypt(&gout102[0]) == gout102clear[0]);
    std::vector<RotationPoly> lut103;
    std::vector<long (*)(long)> flut103;
    auto lut103idx0 = [](long I) -> long {
        /* GATE 31 (LUT2 _1406_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut103.push_back(ctx.genrate_lut(lut103idx0));
    flut103.push_back(lut103idx0);

    auto fvec103 = [flut103](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut103[i](I));
        return ret;
    };

    std::cerr << "\rLUT103   ";
    Ciphertext gin103 = 1 * ct_x2 + 2 * ct_y1;
    std::vector<Ciphertext> gout103 = ctx.eval_lut_amortized(&gin103, lut103);

    long gin103clear = 1 * ct_x2clear + 2 * ct_y1clear;
    std::vector<long> gout103clear = fvec103(gin103clear);

    assert(ctx.decrypt(&gout103[0]) == gout103clear[0]);
    std::vector<RotationPoly> lut104;
    std::vector<long (*)(long)> flut104;
    auto lut104idx0 = [](long I) -> long {
        /* GATE 43 (LUT3 _1418_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut104.push_back(ctx.genrate_lut(lut104idx0));
    flut104.push_back(lut104idx0);

    auto lut104idx1 = [](long I) -> long {
        /* GATE 30 (LUT3 _1405_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut104.push_back(ctx.genrate_lut(lut104idx1));
    flut104.push_back(lut104idx1);

    auto fvec104 = [flut104](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut104[i](I));
        return ret;
    };

    std::cerr << "\rLUT104   ";
    Ciphertext gin104 = 1 * gout103[0] + 2 * gout93[0] + 4 * gout70[0];
    std::vector<Ciphertext> gout104 = ctx.eval_lut_amortized(&gin104, lut104);

    long gin104clear = 1 * gout103clear[0] + 2 * gout93clear[0] + 4 * gout70clear[0];
    std::vector<long> gout104clear = fvec104(gin104clear);

    assert(ctx.decrypt(&gout104[0]) == gout104clear[0]);
    assert(ctx.decrypt(&gout104[1]) == gout104clear[1]);
    std::vector<RotationPoly> lut105;
    std::vector<long (*)(long)> flut105;
    auto lut105idx0 = [](long I) -> long {
        /* GATE 300 (LUT2 _1675_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut105.push_back(ctx.genrate_lut(lut105idx0));
    flut105.push_back(lut105idx0);

    auto fvec105 = [flut105](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut105[i](I));
        return ret;
    };

    std::cerr << "\rLUT105   ";
    Ciphertext gin105 = 1 * ct_y7 + 2 * ct_x5;
    std::vector<Ciphertext> gout105 = ctx.eval_lut_amortized(&gin105, lut105);

    long gin105clear = 1 * ct_y7clear + 2 * ct_x5clear;
    std::vector<long> gout105clear = fvec105(gin105clear);

    assert(ctx.decrypt(&gout105[0]) == gout105clear[0]);
    std::vector<RotationPoly> lut106;
    std::vector<long (*)(long)> flut106;
    auto lut106idx0 = [](long I) -> long {
        /* GATE 338 (LUT2 _1713_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut106.push_back(ctx.genrate_lut(lut106idx0));
    flut106.push_back(lut106idx0);

    auto fvec106 = [flut106](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut106[i](I));
        return ret;
    };

    std::cerr << "\rLUT106   ";
    Ciphertext gin106 = 1 * ct_y4 + 2 * ct_x9;
    std::vector<Ciphertext> gout106 = ctx.eval_lut_amortized(&gin106, lut106);

    long gin106clear = 1 * ct_y4clear + 2 * ct_x9clear;
    std::vector<long> gout106clear = fvec106(gin106clear);

    assert(ctx.decrypt(&gout106[0]) == gout106clear[0]);
    std::vector<RotationPoly> lut107;
    std::vector<long (*)(long)> flut107;
    auto lut107idx0 = [](long I) -> long {
        /* GATE 66 (LUT2 _1441_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut107.push_back(ctx.genrate_lut(lut107idx0));
    flut107.push_back(lut107idx0);

    auto fvec107 = [flut107](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut107[i](I));
        return ret;
    };

    std::cerr << "\rLUT107   ";
    Ciphertext gin107 = 1 * ct_x1 + 2 * ct_y4;
    std::vector<Ciphertext> gout107 = ctx.eval_lut_amortized(&gin107, lut107);

    long gin107clear = 1 * ct_x1clear + 2 * ct_y4clear;
    std::vector<long> gout107clear = fvec107(gin107clear);

    assert(ctx.decrypt(&gout107[0]) == gout107clear[0]);
    std::vector<RotationPoly> lut108;
    std::vector<long (*)(long)> flut108;
    auto lut108idx0 = [](long I) -> long {
        /* GATE 65 (LUT3 _1440_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut108.push_back(ctx.genrate_lut(lut108idx0));
    flut108.push_back(lut108idx0);

    auto lut108idx1 = [](long I) -> long {
        /* GATE 94 (LUT3 _1469_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut108.push_back(ctx.genrate_lut(lut108idx1));
    flut108.push_back(lut108idx1);

    auto fvec108 = [flut108](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut108[i](I));
        return ret;
    };

    std::cerr << "\rLUT108   ";
    Ciphertext gin108 = 1 * gout107[0] + 2 * gout65[0] + 4 * gout17[0];
    std::vector<Ciphertext> gout108 = ctx.eval_lut_amortized(&gin108, lut108);

    long gin108clear = 1 * gout107clear[0] + 2 * gout65clear[0] + 4 * gout17clear[0];
    std::vector<long> gout108clear = fvec108(gin108clear);

    assert(ctx.decrypt(&gout108[0]) == gout108clear[0]);
    assert(ctx.decrypt(&gout108[1]) == gout108clear[1]);
    std::vector<RotationPoly> lut109;
    std::vector<long (*)(long)> flut109;
    auto lut109idx0 = [](long I) -> long {
        /* GATE 311 (LUT2 _1686_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut109.push_back(ctx.genrate_lut(lut109idx0));
    flut109.push_back(lut109idx0);

    auto fvec109 = [flut109](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut109[i](I));
        return ret;
    };

    std::cerr << "\rLUT109   ";
    Ciphertext gin109 = 1 * ct_y9 + 2 * ct_x3;
    std::vector<Ciphertext> gout109 = ctx.eval_lut_amortized(&gin109, lut109);

    long gin109clear = 1 * ct_y9clear + 2 * ct_x3clear;
    std::vector<long> gout109clear = fvec109(gin109clear);

    assert(ctx.decrypt(&gout109[0]) == gout109clear[0]);
    std::vector<RotationPoly> lut110;
    std::vector<long (*)(long)> flut110;
    auto lut110idx0 = [](long I) -> long {
        /* GATE 352 (LUT3 _1727_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut110.push_back(ctx.genrate_lut(lut110idx0));
    flut110.push_back(lut110idx0);

    auto lut110idx1 = [](long I) -> long {
        /* GATE 308 (LUT3 _1683_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut110.push_back(ctx.genrate_lut(lut110idx1));
    flut110.push_back(lut110idx1);

    auto fvec110 = [flut110](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut110[i](I));
        return ret;
    };

    std::cerr << "\rLUT110   ";
    Ciphertext gin110 = 1 * gout47[0] + 2 * gout33[0] + 4 * gout109[0];
    std::vector<Ciphertext> gout110 = ctx.eval_lut_amortized(&gin110, lut110);

    long gin110clear = 1 * gout47clear[0] + 2 * gout33clear[0] + 4 * gout109clear[0];
    std::vector<long> gout110clear = fvec110(gin110clear);

    assert(ctx.decrypt(&gout110[0]) == gout110clear[0]);
    assert(ctx.decrypt(&gout110[1]) == gout110clear[1]);
    std::vector<RotationPoly> lut111;
    std::vector<long (*)(long)> flut111;
    auto lut111idx0 = [](long I) -> long {
        /* GATE 114 (LUT2 _1489_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut111.push_back(ctx.genrate_lut(lut111idx0));
    flut111.push_back(lut111idx0);

    auto lut111idx1 = [](long I) -> long {
        /* GATE 150 (LUT2 _1525_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut111.push_back(ctx.genrate_lut(lut111idx1));
    flut111.push_back(lut111idx1);

    auto fvec111 = [flut111](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut111[i](I));
        return ret;
    };

    std::cerr << "\rLUT111   ";
    Ciphertext gin111 = 1 * gout83[0] + 2 * gout30[0];
    std::vector<Ciphertext> gout111 = ctx.eval_lut_amortized(&gin111, lut111);

    long gin111clear = 1 * gout83clear[0] + 2 * gout30clear[0];
    std::vector<long> gout111clear = fvec111(gin111clear);

    assert(ctx.decrypt(&gout111[0]) == gout111clear[0]);
    assert(ctx.decrypt(&gout111[1]) == gout111clear[1]);
    std::vector<RotationPoly> lut112;
    std::vector<long (*)(long)> flut112;
    auto lut112idx0 = [](long I) -> long {
        /* GATE 257 (LUT2 _1632_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut112.push_back(ctx.genrate_lut(lut112idx0));
    flut112.push_back(lut112idx0);

    auto fvec112 = [flut112](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut112[i](I));
        return ret;
    };

    std::cerr << "\rLUT112   ";
    Ciphertext gin112 = 1 * ct_x4 + 2 * ct_y7;
    std::vector<Ciphertext> gout112 = ctx.eval_lut_amortized(&gin112, lut112);

    long gin112clear = 1 * ct_x4clear + 2 * ct_y7clear;
    std::vector<long> gout112clear = fvec112(gin112clear);

    assert(ctx.decrypt(&gout112[0]) == gout112clear[0]);
    std::vector<RotationPoly> lut113;
    std::vector<long (*)(long)> flut113;
    auto lut113idx0 = [](long I) -> long {
        /* GATE 297 (LUT3 _1672_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut113.push_back(ctx.genrate_lut(lut113idx0));
    flut113.push_back(lut113idx0);

    auto lut113idx1 = [](long I) -> long {
        /* GATE 256 (LUT3 _1631_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut113.push_back(ctx.genrate_lut(lut113idx1));
    flut113.push_back(lut113idx1);

    auto fvec113 = [flut113](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut113[i](I));
        return ret;
    };

    std::cerr << "\rLUT113   ";
    Ciphertext gin113 = 1 * gout112[0] + 2 * gout98[0] + 4 * gout80[0];
    std::vector<Ciphertext> gout113 = ctx.eval_lut_amortized(&gin113, lut113);

    long gin113clear = 1 * gout112clear[0] + 2 * gout98clear[0] + 4 * gout80clear[0];
    std::vector<long> gout113clear = fvec113(gin113clear);

    assert(ctx.decrypt(&gout113[0]) == gout113clear[0]);
    assert(ctx.decrypt(&gout113[1]) == gout113clear[1]);
    std::vector<RotationPoly> lut114;
    std::vector<long (*)(long)> flut114;
    auto lut114idx0 = [](long I) -> long {
        /* GATE 396 (LUT2 _1771_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut114.push_back(ctx.genrate_lut(lut114idx0));
    flut114.push_back(lut114idx0);

    auto fvec114 = [flut114](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut114[i](I));
        return ret;
    };

    std::cerr << "\rLUT114   ";
    Ciphertext gin114 = 1 * ct_x1 + 2 * ct_y13;
    std::vector<Ciphertext> gout114 = ctx.eval_lut_amortized(&gin114, lut114);

    long gin114clear = 1 * ct_x1clear + 2 * ct_y13clear;
    std::vector<long> gout114clear = fvec114(gin114clear);

    assert(ctx.decrypt(&gout114[0]) == gout114clear[0]);
    std::vector<RotationPoly> lut115;
    std::vector<long (*)(long)> flut115;
    auto lut115idx0 = [](long I) -> long {
        /* GATE 452 (LUT3 _1827_ INIT 0x80 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut115.push_back(ctx.genrate_lut(lut115idx0));
    flut115.push_back(lut115idx0);

    auto lut115idx1 = [](long I) -> long {
        /* GATE 395 (LUT3 _1770_ INIT 0x78 PERM 210) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut115.push_back(ctx.genrate_lut(lut115idx1));
    flut115.push_back(lut115idx1);

    auto fvec115 = [flut115](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut115[i](I));
        return ret;
    };

    std::cerr << "\rLUT115   ";
    Ciphertext gin115 = 1 * gout114[0] + 2 * ct_y12 + 4 * ct_x2;
    std::vector<Ciphertext> gout115 = ctx.eval_lut_amortized(&gin115, lut115);

    long gin115clear = 1 * gout114clear[0] + 2 * ct_y12clear + 4 * ct_x2clear;
    std::vector<long> gout115clear = fvec115(gin115clear);

    assert(ctx.decrypt(&gout115[0]) == gout115clear[0]);
    assert(ctx.decrypt(&gout115[1]) == gout115clear[1]);
    std::vector<RotationPoly> lut116;
    std::vector<long (*)(long)> flut116;
    auto lut116idx0 = [](long I) -> long {
        /* GATE 404 (LUT2 _1779_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut116.push_back(ctx.genrate_lut(lut116idx0));
    flut116.push_back(lut116idx0);

    auto fvec116 = [flut116](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut116[i](I));
        return ret;
    };

    std::cerr << "\rLUT116   ";
    Ciphertext gin116 = 1 * gout24[0] + 2 * gout114[0];
    std::vector<Ciphertext> gout116 = ctx.eval_lut_amortized(&gin116, lut116);

    long gin116clear = 1 * gout24clear[0] + 2 * gout114clear[0];
    std::vector<long> gout116clear = fvec116(gin116clear);

    assert(ctx.decrypt(&gout116[0]) == gout116clear[0]);
    std::vector<RotationPoly> lut117;
    std::vector<long (*)(long)> flut117;
    auto lut117idx0 = [](long I) -> long {
        /* GATE 451 (LUT3 _1826_ INIT 0x80 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut117.push_back(ctx.genrate_lut(lut117idx0));
    flut117.push_back(lut117idx0);

    auto lut117idx1 = [](long I) -> long {
        /* GATE 394 (LUT3 _1769_ INIT 0x78 PERM 210) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut117.push_back(ctx.genrate_lut(lut117idx1));
    flut117.push_back(lut117idx1);

    auto fvec117 = [flut117](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut117[i](I));
        return ret;
    };

    std::cerr << "\rLUT117   ";
    Ciphertext gin117 = 1 * gout115[1] + 2 * ct_y14 + 4 * ct_x0;
    std::vector<Ciphertext> gout117 = ctx.eval_lut_amortized(&gin117, lut117);

    long gin117clear = 1 * gout115clear[1] + 2 * ct_y14clear + 4 * ct_x0clear;
    std::vector<long> gout117clear = fvec117(gin117clear);

    assert(ctx.decrypt(&gout117[0]) == gout117clear[0]);
    assert(ctx.decrypt(&gout117[1]) == gout117clear[1]);
    std::vector<RotationPoly> lut118;
    std::vector<long (*)(long)> flut118;
    auto lut118idx0 = [](long I) -> long {
        /* GATE 184 (LUT2 _1559_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut118.push_back(ctx.genrate_lut(lut118idx0));
    flut118.push_back(lut118idx0);

    auto fvec118 = [flut118](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut118[i](I));
        return ret;
    };

    std::cerr << "\rLUT118   ";
    Ciphertext gin118 = 1 * ct_y6 + 2 * ct_x3;
    std::vector<Ciphertext> gout118 = ctx.eval_lut_amortized(&gin118, lut118);

    long gin118clear = 1 * ct_y6clear + 2 * ct_x3clear;
    std::vector<long> gout118clear = fvec118(gin118clear);

    assert(ctx.decrypt(&gout118[0]) == gout118clear[0]);
    std::cerr << "\rFA119    ";
    Ciphertext gin119 = gout75[2] + 1 * ct_x6 + 2 * ct_x7 + 1 * gout5[0] + 2 * gout3[0];
    std::vector<Ciphertext> gout119 = ctx.eval_lut_amortized(&gin119, decomp);

    long gin119clear = gout75clear[2] + 1 * ct_x6clear + 2 * ct_x7clear + 1 * gout5clear[0] + 2 * gout3clear[0];
    std::vector<long> gout119clear = vdecomp(gin119clear);

    assert(ctx.decrypt(&gout119[0]) == gout119clear[0]);
    assert(ctx.decrypt(&gout119[1]) == gout119clear[1]);
    std::vector<RotationPoly> lut120;
    std::vector<long (*)(long)> flut120;
    auto lut120idx0 = [](long I) -> long {
        /* GATE 375 (LUT2 _1750_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut120.push_back(ctx.genrate_lut(lut120idx0));
    flut120.push_back(lut120idx0);

    auto fvec120 = [flut120](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut120[i](I));
        return ret;
    };

    std::cerr << "\rLUT120   ";
    Ciphertext gin120 = 1 * ct_x10 + 2 * ct_y4;
    std::vector<Ciphertext> gout120 = ctx.eval_lut_amortized(&gin120, lut120);

    long gin120clear = 1 * ct_x10clear + 2 * ct_y4clear;
    std::vector<long> gout120clear = fvec120(gin120clear);

    assert(ctx.decrypt(&gout120[0]) == gout120clear[0]);
    std::vector<RotationPoly> lut121;
    std::vector<long (*)(long)> flut121;
    auto lut121idx0 = [](long I) -> long {
        /* GATE 432 (LUT3 _1807_ INIT 0x80 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut121.push_back(ctx.genrate_lut(lut121idx0));
    flut121.push_back(lut121idx0);

    auto lut121idx1 = [](long I) -> long {
        /* GATE 374 (LUT3 _1749_ INIT 0x78 PERM 120) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut121.push_back(ctx.genrate_lut(lut121idx1));
    flut121.push_back(lut121idx1);

    auto fvec121 = [flut121](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut121[i](I));
        return ret;
    };

    std::cerr << "\rLUT121   ";
    Ciphertext gin121 = 1 * gout120[0] + 2 * ct_x11 + 4 * ct_y3;
    std::vector<Ciphertext> gout121 = ctx.eval_lut_amortized(&gin121, lut121);

    long gin121clear = 1 * gout120clear[0] + 2 * ct_x11clear + 4 * ct_y3clear;
    std::vector<long> gout121clear = fvec121(gin121clear);

    assert(ctx.decrypt(&gout121[0]) == gout121clear[0]);
    assert(ctx.decrypt(&gout121[1]) == gout121clear[1]);
    std::vector<RotationPoly> lut122;
    std::vector<long (*)(long)> flut122;
    auto lut122idx0 = [](long I) -> long {
        /* GATE 428 (LUT3 _1803_ INIT 0x80 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut122.push_back(ctx.genrate_lut(lut122idx0));
    flut122.push_back(lut122idx0);

    auto lut122idx1 = [](long I) -> long {
        /* GATE 373 (LUT3 _1748_ INIT 0x78 PERM 120) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut122.push_back(ctx.genrate_lut(lut122idx1));
    flut122.push_back(lut122idx1);

    auto fvec122 = [flut122](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut122[i](I));
        return ret;
    };

    std::cerr << "\rLUT122   ";
    Ciphertext gin122 = 1 * gout121[1] + 2 * ct_x9 + 4 * ct_y5;
    std::vector<Ciphertext> gout122 = ctx.eval_lut_amortized(&gin122, lut122);

    long gin122clear = 1 * gout121clear[1] + 2 * ct_x9clear + 4 * ct_y5clear;
    std::vector<long> gout122clear = fvec122(gin122clear);

    assert(ctx.decrypt(&gout122[0]) == gout122clear[0]);
    assert(ctx.decrypt(&gout122[1]) == gout122clear[1]);
    std::vector<RotationPoly> lut123;
    std::vector<long (*)(long)> flut123;
    auto lut123idx0 = [](long I) -> long {
        /* GATE 454 (LUT2 _1829_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut123.push_back(ctx.genrate_lut(lut123idx0));
    flut123.push_back(lut123idx0);

    auto fvec123 = [flut123](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut123[i](I));
        return ret;
    };

    std::cerr << "\rLUT123   ";
    Ciphertext gin123 = 1 * ct_x1 + 2 * ct_y14;
    std::vector<Ciphertext> gout123 = ctx.eval_lut_amortized(&gin123, lut123);

    long gin123clear = 1 * ct_x1clear + 2 * ct_y14clear;
    std::vector<long> gout123clear = fvec123(gin123clear);

    assert(ctx.decrypt(&gout123[0]) == gout123clear[0]);
    std::vector<RotationPoly> lut124;
    std::vector<long (*)(long)> flut124;
    auto lut124idx0 = [](long I) -> long {
        /* GATE 136 (LUT2 _1511_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut124.push_back(ctx.genrate_lut(lut124idx0));
    flut124.push_back(lut124idx0);

    auto fvec124 = [flut124](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut124[i](I));
        return ret;
    };

    std::cerr << "\rLUT124   ";
    Ciphertext gin124 = 1 * ct_y1 + 2 * ct_x7;
    std::vector<Ciphertext> gout124 = ctx.eval_lut_amortized(&gin124, lut124);

    long gin124clear = 1 * ct_y1clear + 2 * ct_x7clear;
    std::vector<long> gout124clear = fvec124(gin124clear);

    assert(ctx.decrypt(&gout124[0]) == gout124clear[0]);
    std::vector<RotationPoly> lut125;
    std::vector<long (*)(long)> flut125;
    auto lut125idx0 = [](long I) -> long {
        /* GATE 172 (LUT2 _1547_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut125.push_back(ctx.genrate_lut(lut125idx0));
    flut125.push_back(lut125idx0);

    auto fvec125 = [flut125](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut125[i](I));
        return ret;
    };

    std::cerr << "\rLUT125   ";
    Ciphertext gin125 = 1 * ct_y2 + 2 * ct_x7;
    std::vector<Ciphertext> gout125 = ctx.eval_lut_amortized(&gin125, lut125);

    long gin125clear = 1 * ct_y2clear + 2 * ct_x7clear;
    std::vector<long> gout125clear = fvec125(gin125clear);

    assert(ctx.decrypt(&gout125[0]) == gout125clear[0]);
    std::vector<RotationPoly> lut126;
    std::vector<long (*)(long)> flut126;
    auto lut126idx0 = [](long I) -> long {
        /* GATE 113 (LUT2 _1488_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut126.push_back(ctx.genrate_lut(lut126idx0));
    flut126.push_back(lut126idx0);

    auto fvec126 = [flut126](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut126[i](I));
        return ret;
    };

    std::cerr << "\rLUT126   ";
    Ciphertext gin126 = 1 * ct_x4 + 2 * ct_y3;
    std::vector<Ciphertext> gout126 = ctx.eval_lut_amortized(&gin126, lut126);

    long gin126clear = 1 * ct_x4clear + 2 * ct_y3clear;
    std::vector<long> gout126clear = fvec126(gin126clear);

    assert(ctx.decrypt(&gout126[0]) == gout126clear[0]);
    std::vector<RotationPoly> lut127;
    std::vector<long (*)(long)> flut127;
    auto lut127idx0 = [](long I) -> long {
        /* GATE 21 (LUT2 _1396_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut127.push_back(ctx.genrate_lut(lut127idx0));
    flut127.push_back(lut127idx0);

    auto fvec127 = [flut127](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut127[i](I));
        return ret;
    };

    std::cerr << "\rLUT127   ";
    Ciphertext gin127 = 1 * ct_x0 + 2 * ct_y2;
    std::vector<Ciphertext> gout127 = ctx.eval_lut_amortized(&gin127, lut127);

    long gin127clear = 1 * ct_x0clear + 2 * ct_y2clear;
    std::vector<long> gout127clear = fvec127(gin127clear);

    assert(ctx.decrypt(&gout127[0]) == gout127clear[0]);
    std::vector<RotationPoly> lut128;
    std::vector<long (*)(long)> flut128;
    auto lut128idx0 = [](long I) -> long {
        /* GATE 73 (LUT3 _1448_ INIT 0x40 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut128.push_back(ctx.genrate_lut(lut128idx0));
    flut128.push_back(lut128idx0);

    auto fvec128 = [flut128](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut128[i](I));
        return ret;
    };

    std::cerr << "\rLUT128   ";
    Ciphertext gin128 = 1 * ct_op1 + 2 * ct_op0 + 4 * gout21[0];
    std::vector<Ciphertext> gout128 = ctx.eval_lut_amortized(&gin128, lut128);

    long gin128clear = 1 * ct_op1clear + 2 * ct_op0clear + 4 * gout21clear[0];
    std::vector<long> gout128clear = fvec128(gin128clear);

    assert(ctx.decrypt(&gout128[0]) == gout128clear[0]);
    std::vector<RotationPoly> lut129;
    std::vector<long (*)(long)> flut129;
    auto lut129idx0 = [](long I) -> long {
        /* GATE 72 (LUT3 _1447_ INIT 0x80 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut129.push_back(ctx.genrate_lut(lut129idx0));
    flut129.push_back(lut129idx0);

    auto fvec129 = [flut129](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut129[i](I));
        return ret;
    };

    std::cerr << "\rLUT129   ";
    Ciphertext gin129 = 1 * gout128[0] + 2 * ct_op2 + 4 * ct_op3;
    std::vector<Ciphertext> gout129 = ctx.eval_lut_amortized(&gin129, lut129);

    long gin129clear = 1 * gout128clear[0] + 2 * ct_op2clear + 4 * ct_op3clear;
    std::vector<long> gout129clear = fvec129(gin129clear);

    assert(ctx.decrypt(&gout129[0]) == gout129clear[0]);
    std::vector<RotationPoly> lut130;
    std::vector<long (*)(long)> flut130;
    auto lut130idx0 = [](long I) -> long {
        /* GATE 24 (LUT3 _1399_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut130.push_back(ctx.genrate_lut(lut130idx0));
    flut130.push_back(lut130idx0);

    auto fvec130 = [flut130](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut130[i](I));
        return ret;
    };

    std::cerr << "\rLUT130   ";
    Ciphertext gin130 = 1 * gout99[0] + 2 * gout74[0] + 4 * gout129[0];
    std::vector<Ciphertext> gout130 = ctx.eval_lut_amortized(&gin130, lut130);

    long gin130clear = 1 * gout99clear[0] + 2 * gout74clear[0] + 4 * gout129clear[0];
    std::vector<long> gout130clear = fvec130(gin130clear);

    assert(ctx.decrypt(&gout130[0]) == gout130clear[0]);
    std::vector<RotationPoly> lut131;
    std::vector<long (*)(long)> flut131;
    auto lut131idx0 = [](long I) -> long {
        /* GATE 10 (LUT2 _1385_ INIT 0x1 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut131.push_back(ctx.genrate_lut(lut131idx0));
    flut131.push_back(lut131idx0);

    auto fvec131 = [flut131](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut131[i](I));
        return ret;
    };

    std::cerr << "\rLUT131   ";
    Ciphertext gin131 = 1 * gout67[0] + 2 * gout129[0];
    std::vector<Ciphertext> gout131 = ctx.eval_lut_amortized(&gin131, lut131);

    long gin131clear = 1 * gout67clear[0] + 2 * gout129clear[0];
    std::vector<long> gout131clear = fvec131(gin131clear);

    assert(ctx.decrypt(&gout131[0]) == gout131clear[0]);
    std::vector<RotationPoly> lut132;
    std::vector<long (*)(long)> flut132;
    auto lut132idx0 = [](long I) -> long {
        /* GATE 267 (LUT2 _1642_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut132.push_back(ctx.genrate_lut(lut132idx0));
    flut132.push_back(lut132idx0);

    auto fvec132 = [flut132](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut132[i](I));
        return ret;
    };

    std::cerr << "\rLUT132   ";
    Ciphertext gin132 = 1 * ct_x2 + 2 * ct_y9;
    std::vector<Ciphertext> gout132 = ctx.eval_lut_amortized(&gin132, lut132);

    long gin132clear = 1 * ct_x2clear + 2 * ct_y9clear;
    std::vector<long> gout132clear = fvec132(gin132clear);

    assert(ctx.decrypt(&gout132[0]) == gout132clear[0]);
    std::vector<RotationPoly> lut133;
    std::vector<long (*)(long)> flut133;
    auto lut133idx0 = [](long I) -> long {
        /* GATE 307 (LUT3 _1682_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut133.push_back(ctx.genrate_lut(lut133idx0));
    flut133.push_back(lut133idx0);

    auto lut133idx1 = [](long I) -> long {
        /* GATE 264 (LUT3 _1639_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut133.push_back(ctx.genrate_lut(lut133idx1));
    flut133.push_back(lut133idx1);

    auto fvec133 = [flut133](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut133[i](I));
        return ret;
    };

    std::cerr << "\rLUT133   ";
    Ciphertext gin133 = 1 * gout57[0] + 2 * gout27[0] + 4 * gout132[0];
    std::vector<Ciphertext> gout133 = ctx.eval_lut_amortized(&gin133, lut133);

    long gin133clear = 1 * gout57clear[0] + 2 * gout27clear[0] + 4 * gout132clear[0];
    std::vector<long> gout133clear = fvec133(gin133clear);

    assert(ctx.decrypt(&gout133[0]) == gout133clear[0]);
    assert(ctx.decrypt(&gout133[1]) == gout133clear[1]);
    std::vector<RotationPoly> lut134;
    std::vector<long (*)(long)> flut134;
    auto lut134idx0 = [](long I) -> long {
        /* GATE 349 (LUT3 _1724_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut134.push_back(ctx.genrate_lut(lut134idx0));
    flut134.push_back(lut134idx0);

    auto lut134idx1 = [](long I) -> long {
        /* GATE 306 (LUT3 _1681_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut134.push_back(ctx.genrate_lut(lut134idx1));
    flut134.push_back(lut134idx1);

    auto fvec134 = [flut134](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut134[i](I));
        return ret;
    };

    std::cerr << "\rLUT134   ";
    Ciphertext gin134 = 1 * gout133[0] + 2 * gout110[1] + 4 * gout24[0];
    std::vector<Ciphertext> gout134 = ctx.eval_lut_amortized(&gin134, lut134);

    long gin134clear = 1 * gout133clear[0] + 2 * gout110clear[1] + 4 * gout24clear[0];
    std::vector<long> gout134clear = fvec134(gin134clear);

    assert(ctx.decrypt(&gout134[0]) == gout134clear[0]);
    assert(ctx.decrypt(&gout134[1]) == gout134clear[1]);
    std::vector<RotationPoly> lut135;
    std::vector<long (*)(long)> flut135;
    auto lut135idx0 = [](long I) -> long {
        /* GATE 141 (LUT2 _1516_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut135.push_back(ctx.genrate_lut(lut135idx0));
    flut135.push_back(lut135idx0);

    auto fvec135 = [flut135](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut135[i](I));
        return ret;
    };

    std::cerr << "\rLUT135   ";
    Ciphertext gin135 = 1 * ct_y5 + 2 * ct_x3;
    std::vector<Ciphertext> gout135 = ctx.eval_lut_amortized(&gin135, lut135);

    long gin135clear = 1 * ct_y5clear + 2 * ct_x3clear;
    std::vector<long> gout135clear = fvec135(gin135clear);

    assert(ctx.decrypt(&gout135[0]) == gout135clear[0]);
    std::cerr << "\rFA136    ";
    Ciphertext gin136 = gout119[2] + 1 * ct_x8 + 2 * ct_x9 + 1 * gout1[0] + 2 * gout0[0];
    std::vector<Ciphertext> gout136 = ctx.eval_lut_amortized(&gin136, decomp);

    long gin136clear = gout119clear[2] + 1 * ct_x8clear + 2 * ct_x9clear + 1 * gout1clear[0] + 2 * gout0clear[0];
    std::vector<long> gout136clear = vdecomp(gin136clear);

    assert(ctx.decrypt(&gout136[0]) == gout136clear[0]);
    assert(ctx.decrypt(&gout136[1]) == gout136clear[1]);
    std::vector<RotationPoly> lut137;
    std::vector<long (*)(long)> flut137;
    auto lut137idx0 = [](long I) -> long {
        /* GATE 171 (LUT2 _1546_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut137.push_back(ctx.genrate_lut(lut137idx0));
    flut137.push_back(lut137idx0);

    auto fvec137 = [flut137](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut137[i](I));
        return ret;
    };

    std::cerr << "\rLUT137   ";
    Ciphertext gin137 = 1 * ct_x8 + 2 * ct_y1;
    std::vector<Ciphertext> gout137 = ctx.eval_lut_amortized(&gin137, lut137);

    long gin137clear = 1 * ct_x8clear + 2 * ct_y1clear;
    std::vector<long> gout137clear = fvec137(gin137clear);

    assert(ctx.decrypt(&gout137[0]) == gout137clear[0]);
    std::vector<RotationPoly> lut138;
    std::vector<long (*)(long)> flut138;
    auto lut138idx0 = [](long I) -> long {
        /* GATE 205 (LUT3 _1580_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut138.push_back(ctx.genrate_lut(lut138idx0));
    flut138.push_back(lut138idx0);

    auto lut138idx1 = [](long I) -> long {
        /* GATE 170 (LUT3 _1545_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut138.push_back(ctx.genrate_lut(lut138idx1));
    flut138.push_back(lut138idx1);

    auto fvec138 = [flut138](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut138[i](I));
        return ret;
    };

    std::cerr << "\rLUT138   ";
    Ciphertext gin138 = 1 * gout137[0] + 2 * gout125[0] + 4 * gout45[0];
    std::vector<Ciphertext> gout138 = ctx.eval_lut_amortized(&gin138, lut138);

    long gin138clear = 1 * gout137clear[0] + 2 * gout125clear[0] + 4 * gout45clear[0];
    std::vector<long> gout138clear = fvec138(gin138clear);

    assert(ctx.decrypt(&gout138[0]) == gout138clear[0]);
    assert(ctx.decrypt(&gout138[1]) == gout138clear[1]);
    std::vector<RotationPoly> lut139;
    std::vector<long (*)(long)> flut139;
    auto lut139idx0 = [](long I) -> long {
        /* GATE 424 (LUT2 _1799_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut139.push_back(ctx.genrate_lut(lut139idx0));
    flut139.push_back(lut139idx0);

    auto fvec139 = [flut139](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut139[i](I));
        return ret;
    };

    std::cerr << "\rLUT139   ";
    Ciphertext gin139 = 1 * ct_y12 + 2 * ct_x3;
    std::vector<Ciphertext> gout139 = ctx.eval_lut_amortized(&gin139, lut139);

    long gin139clear = 1 * ct_y12clear + 2 * ct_x3clear;
    std::vector<long> gout139clear = fvec139(gin139clear);

    assert(ctx.decrypt(&gout139[0]) == gout139clear[0]);
    std::vector<RotationPoly> lut140;
    std::vector<long (*)(long)> flut140;
    auto lut140idx0 = [](long I) -> long {
        /* GATE 423 (LUT3 _1798_ INIT 0x78 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut140.push_back(ctx.genrate_lut(lut140idx0));
    flut140.push_back(lut140idx0);

    auto fvec140 = [flut140](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut140[i](I));
        return ret;
    };

    std::cerr << "\rLUT140   ";
    Ciphertext gin140 = 1 * ct_x4 + 2 * gout139[0] + 4 * ct_y11;
    std::vector<Ciphertext> gout140 = ctx.eval_lut_amortized(&gin140, lut140);

    long gin140clear = 1 * ct_x4clear + 2 * gout139clear[0] + 4 * ct_y11clear;
    std::vector<long> gout140clear = fvec140(gin140clear);

    assert(ctx.decrypt(&gout140[0]) == gout140clear[0]);
    std::vector<RotationPoly> lut141;
    std::vector<long (*)(long)> flut141;
    auto lut141idx0 = [](long I) -> long {
        /* GATE 422 (LUT3 _1797_ INIT 0x87 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut141.push_back(ctx.genrate_lut(lut141idx0));
    flut141.push_back(lut141idx0);

    auto fvec141 = [flut141](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut141[i](I));
        return ret;
    };

    std::cerr << "\rLUT141   ";
    Ciphertext gin141 = 1 * ct_x2 + 2 * ct_y13 + 4 * gout140[0];
    std::vector<Ciphertext> gout141 = ctx.eval_lut_amortized(&gin141, lut141);

    long gin141clear = 1 * ct_x2clear + 2 * ct_y13clear + 4 * gout140clear[0];
    std::vector<long> gout141clear = fvec141(gin141clear);

    assert(ctx.decrypt(&gout141[0]) == gout141clear[0]);
    std::vector<RotationPoly> lut142;
    std::vector<long (*)(long)> flut142;
    auto lut142idx0 = [](long I) -> long {
        /* GATE 247 (LUT2 _1622_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut142.push_back(ctx.genrate_lut(lut142idx0));
    flut142.push_back(lut142idx0);

    auto fvec142 = [flut142](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut142[i](I));
        return ret;
    };

    std::cerr << "\rLUT142   ";
    Ciphertext gin142 = 1 * ct_y2 + 2 * ct_x9;
    std::vector<Ciphertext> gout142 = ctx.eval_lut_amortized(&gin142, lut142);

    long gin142clear = 1 * ct_y2clear + 2 * ct_x9clear;
    std::vector<long> gout142clear = fvec142(gin142clear);

    assert(ctx.decrypt(&gout142[0]) == gout142clear[0]);
    std::vector<RotationPoly> lut143;
    std::vector<long (*)(long)> flut143;
    auto lut143idx0 = [](long I) -> long {
        /* GATE 219 (LUT2 _1594_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut143.push_back(ctx.genrate_lut(lut143idx0));
    flut143.push_back(lut143idx0);

    auto fvec143 = [flut143](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut143[i](I));
        return ret;
    };

    std::cerr << "\rLUT143   ";
    Ciphertext gin143 = 1 * ct_x2 + 2 * ct_y8;
    std::vector<Ciphertext> gout143 = ctx.eval_lut_amortized(&gin143, lut143);

    long gin143clear = 1 * ct_x2clear + 2 * ct_y8clear;
    std::vector<long> gout143clear = fvec143(gin143clear);

    assert(ctx.decrypt(&gout143[0]) == gout143clear[0]);
    std::cerr << "\rFA144    ";
    Ciphertext gin144 = gout136[2] + 1 * ct_x10 + 2 * ct_x11 + 1 * gout13[0] + 2 * gout14[0];
    std::vector<Ciphertext> gout144 = ctx.eval_lut_amortized(&gin144, decomp);

    long gin144clear = gout136clear[2] + 1 * ct_x10clear + 2 * ct_x11clear + 1 * gout13clear[0] + 2 * gout14clear[0];
    std::vector<long> gout144clear = vdecomp(gin144clear);

    assert(ctx.decrypt(&gout144[0]) == gout144clear[0]);
    assert(ctx.decrypt(&gout144[1]) == gout144clear[1]);
    std::cerr << "\rFA145    ";
    Ciphertext gin145 = gout144[2] + 1 * ct_x12 + 2 * ct_x13 + 1 * gout12[0] + 2 * gout11[0];
    std::vector<Ciphertext> gout145 = ctx.eval_lut_amortized(&gin145, decomp);

    long gin145clear = gout144clear[2] + 1 * ct_x12clear + 2 * ct_x13clear + 1 * gout12clear[0] + 2 * gout11clear[0];
    std::vector<long> gout145clear = vdecomp(gin145clear);

    assert(ctx.decrypt(&gout145[0]) == gout145clear[0]);
    assert(ctx.decrypt(&gout145[1]) == gout145clear[1]);
    std::cerr << "\rFA146    ";
    Ciphertext gin146 = gout145[2] + 1 * ct_x14 + 2 * ct_x15 + 1 * gout2[0] + 2 * gout4[0];
    std::vector<Ciphertext> gout146 = ctx.eval_lut_amortized(&gin146, decomp);

    long gin146clear = gout145clear[2] + 1 * ct_x14clear + 2 * ct_x15clear + 1 * gout2clear[0] + 2 * gout4clear[0];
    std::vector<long> gout146clear = vdecomp(gin146clear);

    assert(ctx.decrypt(&gout146[0]) == gout146clear[0]);
    assert(ctx.decrypt(&gout146[1]) == gout146clear[1]);
    std::vector<RotationPoly> lut147;
    std::vector<long (*)(long)> flut147;
    auto lut147idx0 = [](long I) -> long {
        /* GATE 426 (LUT2 _1801_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut147.push_back(ctx.genrate_lut(lut147idx0));
    flut147.push_back(lut147idx0);

    auto fvec147 = [flut147](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut147[i](I));
        return ret;
    };

    std::cerr << "\rLUT147   ";
    Ciphertext gin147 = 1 * ct_x6 + 2 * ct_y9;
    std::vector<Ciphertext> gout147 = ctx.eval_lut_amortized(&gin147, lut147);

    long gin147clear = 1 * ct_x6clear + 2 * ct_y9clear;
    std::vector<long> gout147clear = fvec147(gin147clear);

    assert(ctx.decrypt(&gout147[0]) == gout147clear[0]);
    std::vector<RotationPoly> lut148;
    std::vector<long (*)(long)> flut148;
    auto lut148idx0 = [](long I) -> long {
        /* GATE 425 (LUT3 _1800_ INIT 0x87 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut148.push_back(ctx.genrate_lut(lut148idx0));
    flut148.push_back(lut148idx0);

    auto fvec148 = [flut148](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut148[i](I));
        return ret;
    };

    std::cerr << "\rLUT148   ";
    Ciphertext gin148 = 1 * ct_x7 + 2 * ct_y8 + 4 * gout147[0];
    std::vector<Ciphertext> gout148 = ctx.eval_lut_amortized(&gin148, lut148);

    long gin148clear = 1 * ct_x7clear + 2 * ct_y8clear + 4 * gout147clear[0];
    std::vector<long> gout148clear = fvec148(gin148clear);

    assert(ctx.decrypt(&gout148[0]) == gout148clear[0]);
    std::vector<RotationPoly> lut149;
    std::vector<long (*)(long)> flut149;
    auto lut149idx0 = [](long I) -> long {
        /* GATE 48 (LUT3 _1423_ INIT 0x78 PERM 120) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut149.push_back(ctx.genrate_lut(lut149idx0));
    flut149.push_back(lut149idx0);

    auto fvec149 = [flut149](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut149[i](I));
        return ret;
    };

    std::cerr << "\rLUT149   ";
    Ciphertext gin149 = 1 * gout87[0] + 2 * ct_x0 + 4 * ct_y4;
    std::vector<Ciphertext> gout149 = ctx.eval_lut_amortized(&gin149, lut149);

    long gin149clear = 1 * gout87clear[0] + 2 * ct_x0clear + 4 * ct_y4clear;
    std::vector<long> gout149clear = fvec149(gin149clear);

    assert(ctx.decrypt(&gout149[0]) == gout149clear[0]);
    std::vector<RotationPoly> lut150;
    std::vector<long (*)(long)> flut150;
    auto lut150idx0 = [](long I) -> long {
        /* GATE 58 (LUT3 _1433_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut150.push_back(ctx.genrate_lut(lut150idx0));
    flut150.push_back(lut150idx0);

    auto lut150idx1 = [](long I) -> long {
        /* GATE 42 (LUT3 _1417_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut150.push_back(ctx.genrate_lut(lut150idx1));
    flut150.push_back(lut150idx1);

    auto fvec150 = [flut150](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut150[i](I));
        return ret;
    };

    std::cerr << "\rLUT150   ";
    Ciphertext gin150 = 1 * gout104[0] + 2 * gout69[0] + 4 * gout149[0];
    std::vector<Ciphertext> gout150 = ctx.eval_lut_amortized(&gin150, lut150);

    long gin150clear = 1 * gout104clear[0] + 2 * gout69clear[0] + 4 * gout149clear[0];
    std::vector<long> gout150clear = fvec150(gin150clear);

    assert(ctx.decrypt(&gout150[0]) == gout150clear[0]);
    assert(ctx.decrypt(&gout150[1]) == gout150clear[1]);
    std::vector<RotationPoly> lut151;
    std::vector<long (*)(long)> flut151;
    auto lut151idx0 = [](long I) -> long {
        /* GATE 386 (LUT2 _1761_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut151.push_back(ctx.genrate_lut(lut151idx0));
    flut151.push_back(lut151idx0);

    auto fvec151 = [flut151](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut151[i](I));
        return ret;
    };

    std::cerr << "\rLUT151   ";
    Ciphertext gin151 = 1 * ct_y7 + 2 * ct_x7;
    std::vector<Ciphertext> gout151 = ctx.eval_lut_amortized(&gin151, lut151);

    long gin151clear = 1 * ct_y7clear + 2 * ct_x7clear;
    std::vector<long> gout151clear = fvec151(gin151clear);

    assert(ctx.decrypt(&gout151[0]) == gout151clear[0]);
    std::vector<RotationPoly> lut152;
    std::vector<long (*)(long)> flut152;
    auto lut152idx0 = [](long I) -> long {
        /* GATE 385 (LUT3 _1760_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut152.push_back(ctx.genrate_lut(lut152idx0));
    flut152.push_back(lut152idx0);

    auto lut152idx1 = [](long I) -> long {
        /* GATE 446 (LUT3 _1821_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut152.push_back(ctx.genrate_lut(lut152idx1));
    flut152.push_back(lut152idx1);

    auto fvec152 = [flut152](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut152[i](I));
        return ret;
    };

    std::cerr << "\rLUT152   ";
    Ciphertext gin152 = 1 * gout151[0] + 2 * gout62[0] + 4 * gout39[0];
    std::vector<Ciphertext> gout152 = ctx.eval_lut_amortized(&gin152, lut152);

    long gin152clear = 1 * gout151clear[0] + 2 * gout62clear[0] + 4 * gout39clear[0];
    std::vector<long> gout152clear = fvec152(gin152clear);

    assert(ctx.decrypt(&gout152[0]) == gout152clear[0]);
    assert(ctx.decrypt(&gout152[1]) == gout152clear[1]);
    std::vector<RotationPoly> lut153;
    std::vector<long (*)(long)> flut153;
    auto lut153idx0 = [](long I) -> long {
        /* GATE 175 (LUT2 _1550_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut153.push_back(ctx.genrate_lut(lut153idx0));
    flut153.push_back(lut153idx0);

    auto fvec153 = [flut153](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut153[i](I));
        return ret;
    };

    std::cerr << "\rLUT153   ";
    Ciphertext gin153 = 1 * ct_y4 + 2 * ct_x5;
    std::vector<Ciphertext> gout153 = ctx.eval_lut_amortized(&gin153, lut153);

    long gin153clear = 1 * ct_y4clear + 2 * ct_x5clear;
    std::vector<long> gout153clear = fvec153(gin153clear);

    assert(ctx.decrypt(&gout153[0]) == gout153clear[0]);
    std::vector<RotationPoly> lut154;
    std::vector<long (*)(long)> flut154;
    auto lut154idx0 = [](long I) -> long {
        /* GATE 13 (LUT3 _1388_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut154.push_back(ctx.genrate_lut(lut154idx0));
    flut154.push_back(lut154idx0);

    auto fvec154 = [flut154](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut154[i](I));
        return ret;
    };

    std::cerr << "\rLUT154   ";
    Ciphertext gin154 = 1 * gout78[1] + 2 * gout44[1] + 4 * gout129[0];
    std::vector<Ciphertext> gout154 = ctx.eval_lut_amortized(&gin154, lut154);

    long gin154clear = 1 * gout78clear[1] + 2 * gout44clear[1] + 4 * gout129clear[0];
    std::vector<long> gout154clear = fvec154(gin154clear);

    assert(ctx.decrypt(&gout154[0]) == gout154clear[0]);
    std::vector<RotationPoly> lut155;
    std::vector<long (*)(long)> flut155;
    auto lut155idx0 = [](long I) -> long {
        /* GATE 246 (LUT2 _1621_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut155.push_back(ctx.genrate_lut(lut155idx0));
    flut155.push_back(lut155idx0);

    auto fvec155 = [flut155](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut155[i](I));
        return ret;
    };

    std::cerr << "\rLUT155   ";
    Ciphertext gin155 = 1 * ct_x10 + 2 * ct_y1;
    std::vector<Ciphertext> gout155 = ctx.eval_lut_amortized(&gin155, lut155);

    long gin155clear = 1 * ct_x10clear + 2 * ct_y1clear;
    std::vector<long> gout155clear = fvec155(gin155clear);

    assert(ctx.decrypt(&gout155[0]) == gout155clear[0]);
    std::vector<RotationPoly> lut156;
    std::vector<long (*)(long)> flut156;
    auto lut156idx0 = [](long I) -> long {
        /* GATE 245 (LUT3 _1620_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut156.push_back(ctx.genrate_lut(lut156idx0));
    flut156.push_back(lut156idx0);

    auto lut156idx1 = [](long I) -> long {
        /* GATE 287 (LUT3 _1662_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut156.push_back(ctx.genrate_lut(lut156idx1));
    flut156.push_back(lut156idx1);

    auto fvec156 = [flut156](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut156[i](I));
        return ret;
    };

    std::cerr << "\rLUT156   ";
    Ciphertext gin156 = 1 * gout155[0] + 2 * gout142[0] + 4 * gout56[0];
    std::vector<Ciphertext> gout156 = ctx.eval_lut_amortized(&gin156, lut156);

    long gin156clear = 1 * gout155clear[0] + 2 * gout142clear[0] + 4 * gout56clear[0];
    std::vector<long> gout156clear = fvec156(gin156clear);

    assert(ctx.decrypt(&gout156[0]) == gout156clear[0]);
    assert(ctx.decrypt(&gout156[1]) == gout156clear[1]);
    std::vector<RotationPoly> lut157;
    std::vector<long (*)(long)> flut157;
    auto lut157idx0 = [](long I) -> long {
        /* GATE 64 (LUT2 _1439_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut157.push_back(ctx.genrate_lut(lut157idx0));
    flut157.push_back(lut157idx0);

    auto fvec157 = [flut157](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut157[i](I));
        return ret;
    };

    std::cerr << "\rLUT157   ";
    Ciphertext gin157 = 1 * ct_y0 + 2 * ct_x5;
    std::vector<Ciphertext> gout157 = ctx.eval_lut_amortized(&gin157, lut157);

    long gin157clear = 1 * ct_y0clear + 2 * ct_x5clear;
    std::vector<long> gout157clear = fvec157(gin157clear);

    assert(ctx.decrypt(&gout157[0]) == gout157clear[0]);
    std::vector<RotationPoly> lut158;
    std::vector<long (*)(long)> flut158;
    auto lut158idx0 = [](long I) -> long {
        /* GATE 380 (LUT2 _1755_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut158.push_back(ctx.genrate_lut(lut158idx0));
    flut158.push_back(lut158idx0);

    auto fvec158 = [flut158](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut158[i](I));
        return ret;
    };

    std::cerr << "\rLUT158   ";
    Ciphertext gin158 = 1 * ct_x14 + 2 * ct_y0;
    std::vector<Ciphertext> gout158 = ctx.eval_lut_amortized(&gin158, lut158);

    long gin158clear = 1 * ct_x14clear + 2 * ct_y0clear;
    std::vector<long> gout158clear = fvec158(gin158clear);

    assert(ctx.decrypt(&gout158[0]) == gout158clear[0]);
    std::vector<RotationPoly> lut159;
    std::vector<long (*)(long)> flut159;
    auto lut159idx0 = [](long I) -> long {
        /* GATE 344 (LUT3 _1719_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut159.push_back(ctx.genrate_lut(lut159idx0));
    flut159.push_back(lut159idx0);

    auto lut159idx1 = [](long I) -> long {
        /* GATE 383 (LUT3 _1758_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut159.push_back(ctx.genrate_lut(lut159idx1));
    flut159.push_back(lut159idx1);

    auto fvec159 = [flut159](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut159[i](I));
        return ret;
    };

    std::cerr << "\rLUT159   ";
    Ciphertext gin159 = 1 * gout73[0] + 2 * gout63[0] + 4 * gout40[0];
    std::vector<Ciphertext> gout159 = ctx.eval_lut_amortized(&gin159, lut159);

    long gin159clear = 1 * gout73clear[0] + 2 * gout63clear[0] + 4 * gout40clear[0];
    std::vector<long> gout159clear = fvec159(gin159clear);

    assert(ctx.decrypt(&gout159[0]) == gout159clear[0]);
    assert(ctx.decrypt(&gout159[1]) == gout159clear[1]);
    std::vector<RotationPoly> lut160;
    std::vector<long (*)(long)> flut160;
    auto lut160idx0 = [](long I) -> long {
        /* GATE 302 (LUT2 _1677_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut160.push_back(ctx.genrate_lut(lut160idx0));
    flut160.push_back(lut160idx0);

    auto fvec160 = [flut160](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut160[i](I));
        return ret;
    };

    std::cerr << "\rLUT160   ";
    Ciphertext gin160 = 1 * ct_y6 + 2 * ct_x6;
    std::vector<Ciphertext> gout160 = ctx.eval_lut_amortized(&gin160, lut160);

    long gin160clear = 1 * ct_y6clear + 2 * ct_x6clear;
    std::vector<long> gout160clear = fvec160(gin160clear);

    assert(ctx.decrypt(&gout160[0]) == gout160clear[0]);
    std::vector<RotationPoly> lut161;
    std::vector<long (*)(long)> flut161;
    auto lut161idx0 = [](long I) -> long {
        /* GATE 342 (LUT3 _1717_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut161.push_back(ctx.genrate_lut(lut161idx0));
    flut161.push_back(lut161idx0);

    auto lut161idx1 = [](long I) -> long {
        /* GATE 299 (LUT3 _1674_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut161.push_back(ctx.genrate_lut(lut161idx1));
    flut161.push_back(lut161idx1);

    auto fvec161 = [flut161](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut161[i](I));
        return ret;
    };

    std::cerr << "\rLUT161   ";
    Ciphertext gin161 = 1 * gout105[0] + 2 * gout89[0] + 4 * gout160[0];
    std::vector<Ciphertext> gout161 = ctx.eval_lut_amortized(&gin161, lut161);

    long gin161clear = 1 * gout105clear[0] + 2 * gout89clear[0] + 4 * gout160clear[0];
    std::vector<long> gout161clear = fvec161(gin161clear);

    assert(ctx.decrypt(&gout161[0]) == gout161clear[0]);
    assert(ctx.decrypt(&gout161[1]) == gout161clear[1]);
    std::vector<RotationPoly> lut162;
    std::vector<long (*)(long)> flut162;
    auto lut162idx0 = [](long I) -> long {
        /* GATE 399 (LUT3 _1774_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut162.push_back(ctx.genrate_lut(lut162idx0));
    flut162.push_back(lut162idx0);

    auto lut162idx1 = [](long I) -> long {
        /* GATE 341 (LUT3 _1716_ INIT 0x96 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut162.push_back(ctx.genrate_lut(lut162idx1));
    flut162.push_back(lut162idx1);

    auto fvec162 = [flut162](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut162[i](I));
        return ret;
    };

    std::cerr << "\rLUT162   ";
    Ciphertext gin162 = 1 * gout161[0] + 2 * gout159[0] + 4 * gout60[1];
    std::vector<Ciphertext> gout162 = ctx.eval_lut_amortized(&gin162, lut162);

    long gin162clear = 1 * gout161clear[0] + 2 * gout159clear[0] + 4 * gout60clear[1];
    std::vector<long> gout162clear = fvec162(gin162clear);

    assert(ctx.decrypt(&gout162[0]) == gout162clear[0]);
    assert(ctx.decrypt(&gout162[1]) == gout162clear[1]);
    std::vector<RotationPoly> lut163;
    std::vector<long (*)(long)> flut163;
    auto lut163idx0 = [](long I) -> long {
        /* GATE 36 (LUT3 _1411_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut163.push_back(ctx.genrate_lut(lut163idx0));
    flut163.push_back(lut163idx0);

    auto fvec163 = [flut163](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut163[i](I));
        return ret;
    };

    std::cerr << "\rLUT163   ";
    Ciphertext gin163 = 1 * gout99[1] + 2 * gout74[1] + 4 * gout129[0];
    std::vector<Ciphertext> gout163 = ctx.eval_lut_amortized(&gin163, lut163);

    long gin163clear = 1 * gout99clear[1] + 2 * gout74clear[1] + 4 * gout129clear[0];
    std::vector<long> gout163clear = fvec163(gin163clear);

    assert(ctx.decrypt(&gout163[0]) == gout163clear[0]);
    std::vector<RotationPoly> lut164;
    std::vector<long (*)(long)> flut164;
    auto lut164idx0 = [](long I) -> long {
        /* GATE 291 (LUT2 _1666_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut164.push_back(ctx.genrate_lut(lut164idx0));
    flut164.push_back(lut164idx0);

    auto fvec164 = [flut164](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut164[i](I));
        return ret;
    };

    std::cerr << "\rLUT164   ";
    Ciphertext gin164 = 1 * ct_x12 + 2 * ct_y0;
    std::vector<Ciphertext> gout164 = ctx.eval_lut_amortized(&gin164, lut164);

    long gin164clear = 1 * ct_x12clear + 2 * ct_y0clear;
    std::vector<long> gout164clear = fvec164(gin164clear);

    assert(ctx.decrypt(&gout164[0]) == gout164clear[0]);
    std::vector<RotationPoly> lut165;
    std::vector<long (*)(long)> flut165;
    auto lut165idx0 = [](long I) -> long {
        /* GATE 304 (LUT2 _1679_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut165.push_back(ctx.genrate_lut(lut165idx0));
    flut165.push_back(lut165idx0);

    auto lut165idx1 = [](long I) -> long {
        /* GATE 262 (LUT2 _1637_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut165.push_back(ctx.genrate_lut(lut165idx1));
    flut165.push_back(lut165idx1);

    auto fvec165 = [flut165](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut165[i](I));
        return ret;
    };

    std::cerr << "\rLUT165   ";
    Ciphertext gin165 = 1 * gout51[1] + 2 * gout133[1];
    std::vector<Ciphertext> gout165 = ctx.eval_lut_amortized(&gin165, lut165);

    long gin165clear = 1 * gout51clear[1] + 2 * gout133clear[1];
    std::vector<long> gout165clear = fvec165(gin165clear);

    assert(ctx.decrypt(&gout165[0]) == gout165clear[0]);
    assert(ctx.decrypt(&gout165[1]) == gout165clear[1]);
    std::vector<RotationPoly> lut166;
    std::vector<long (*)(long)> flut166;
    auto lut166idx0 = [](long I) -> long {
        /* GATE 434 (LUT3 _1809_ INIT 0x87 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut166.push_back(ctx.genrate_lut(lut166idx0));
    flut166.push_back(lut166idx0);

    auto fvec166 = [flut166](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut166[i](I));
        return ret;
    };

    std::cerr << "\rLUT166   ";
    Ciphertext gin166 = 1 * ct_x13 + 2 * ct_y2 + 4 * gout102[0];
    std::vector<Ciphertext> gout166 = ctx.eval_lut_amortized(&gin166, lut166);

    long gin166clear = 1 * ct_x13clear + 2 * ct_y2clear + 4 * gout102clear[0];
    std::vector<long> gout166clear = fvec166(gin166clear);

    assert(ctx.decrypt(&gout166[0]) == gout166clear[0]);
    std::vector<RotationPoly> lut167;
    std::vector<long (*)(long)> flut167;
    auto lut167idx0 = [](long I) -> long {
        /* GATE 358 (LUT2 _1733_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut167.push_back(ctx.genrate_lut(lut167idx0));
    flut167.push_back(lut167idx0);

    auto fvec167 = [flut167](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut167[i](I));
        return ret;
    };

    std::cerr << "\rLUT167   ";
    Ciphertext gin167 = 1 * ct_x1 + 2 * ct_y12;
    std::vector<Ciphertext> gout167 = ctx.eval_lut_amortized(&gin167, lut167);

    long gin167clear = 1 * ct_x1clear + 2 * ct_y12clear;
    std::vector<long> gout167clear = fvec167(gin167clear);

    assert(ctx.decrypt(&gout167[0]) == gout167clear[0]);
    std::vector<RotationPoly> lut168;
    std::vector<long (*)(long)> flut168;
    auto lut168idx0 = [](long I) -> long {
        /* GATE 357 (LUT3 _1732_ INIT 0x78 PERM 120) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut168.push_back(ctx.genrate_lut(lut168idx0));
    flut168.push_back(lut168idx0);

    auto fvec168 = [flut168](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut168[i](I));
        return ret;
    };

    std::cerr << "\rLUT168   ";
    Ciphertext gin168 = 1 * gout167[0] + 2 * ct_x0 + 4 * ct_y13;
    std::vector<Ciphertext> gout168 = ctx.eval_lut_amortized(&gin168, lut168);

    long gin168clear = 1 * gout167clear[0] + 2 * ct_x0clear + 4 * ct_y13clear;
    std::vector<long> gout168clear = fvec168(gin168clear);

    assert(ctx.decrypt(&gout168[0]) == gout168clear[0]);
    std::vector<RotationPoly> lut169;
    std::vector<long (*)(long)> flut169;
    auto lut169idx0 = [](long I) -> long {
        /* GATE 398 (LUT3 _1773_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut169.push_back(ctx.genrate_lut(lut169idx0));
    flut169.push_back(lut169idx0);

    auto lut169idx1 = [](long I) -> long {
        /* GATE 351 (LUT3 _1726_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut169.push_back(ctx.genrate_lut(lut169idx1));
    flut169.push_back(lut169idx1);

    auto fvec169 = [flut169](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut169[i](I));
        return ret;
    };

    std::cerr << "\rLUT169   ";
    Ciphertext gin169 = 1 * gout110[0] + 2 * gout97[1] + 4 * gout168[0];
    std::vector<Ciphertext> gout169 = ctx.eval_lut_amortized(&gin169, lut169);

    long gin169clear = 1 * gout110clear[0] + 2 * gout97clear[1] + 4 * gout168clear[0];
    std::vector<long> gout169clear = fvec169(gin169clear);

    assert(ctx.decrypt(&gout169[0]) == gout169clear[0]);
    assert(ctx.decrypt(&gout169[1]) == gout169clear[1]);
    std::vector<RotationPoly> lut170;
    std::vector<long (*)(long)> flut170;
    auto lut170idx0 = [](long I) -> long {
        /* GATE 112 (LUT2 _1487_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut170.push_back(ctx.genrate_lut(lut170idx0));
    flut170.push_back(lut170idx0);

    auto fvec170 = [flut170](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut170[i](I));
        return ret;
    };

    std::cerr << "\rLUT170   ";
    Ciphertext gin170 = 1 * ct_x2 + 2 * ct_y5;
    std::vector<Ciphertext> gout170 = ctx.eval_lut_amortized(&gin170, lut170);

    long gin170clear = 1 * ct_x2clear + 2 * ct_y5clear;
    std::vector<long> gout170clear = fvec170(gin170clear);

    assert(ctx.decrypt(&gout170[0]) == gout170clear[0]);
    std::vector<RotationPoly> lut171;
    std::vector<long (*)(long)> flut171;
    auto lut171idx0 = [](long I) -> long {
        /* GATE 145 (LUT3 _1520_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut171.push_back(ctx.genrate_lut(lut171idx0));
    flut171.push_back(lut171idx0);

    auto lut171idx1 = [](long I) -> long {
        /* GATE 110 (LUT3 _1485_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut171.push_back(ctx.genrate_lut(lut171idx1));
    flut171.push_back(lut171idx1);

    auto fvec171 = [flut171](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut171[i](I));
        return ret;
    };

    std::cerr << "\rLUT171   ";
    Ciphertext gin171 = 1 * gout34[0] + 2 * gout170[0] + 4 * gout126[0];
    std::vector<Ciphertext> gout171 = ctx.eval_lut_amortized(&gin171, lut171);

    long gin171clear = 1 * gout34clear[0] + 2 * gout170clear[0] + 4 * gout126clear[0];
    std::vector<long> gout171clear = fvec171(gin171clear);

    assert(ctx.decrypt(&gout171[0]) == gout171clear[0]);
    assert(ctx.decrypt(&gout171[1]) == gout171clear[1]);
    std::vector<RotationPoly> lut172;
    std::vector<long (*)(long)> flut172;
    auto lut172idx0 = [](long I) -> long {
        /* GATE 20 (LUT2 _1395_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut172.push_back(ctx.genrate_lut(lut172idx0));
    flut172.push_back(lut172idx0);

    auto fvec172 = [flut172](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut172[i](I));
        return ret;
    };

    std::cerr << "\rLUT172   ";
    Ciphertext gin172 = 1 * ct_x1 + 2 * ct_y1;
    std::vector<Ciphertext> gout172 = ctx.eval_lut_amortized(&gin172, lut172);

    long gin172clear = 1 * ct_x1clear + 2 * ct_y1clear;
    std::vector<long> gout172clear = fvec172(gin172clear);

    assert(ctx.decrypt(&gout172[0]) == gout172clear[0]);
    std::vector<RotationPoly> lut173;
    std::vector<long (*)(long)> flut173;
    auto lut173idx0 = [](long I) -> long {
        /* GATE 29 (LUT3 _1404_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut173.push_back(ctx.genrate_lut(lut173idx0));
    flut173.push_back(lut173idx0);

    auto lut173idx1 = [](long I) -> long {
        /* GATE 19 (LUT3 _1394_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut173.push_back(ctx.genrate_lut(lut173idx1));
    flut173.push_back(lut173idx1);

    auto fvec173 = [flut173](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut173[i](I));
        return ret;
    };

    std::cerr << "\rLUT173   ";
    Ciphertext gin173 = 1 * gout172[0] + 2 * gout127[0] + 4 * gout41[0];
    std::vector<Ciphertext> gout173 = ctx.eval_lut_amortized(&gin173, lut173);

    long gin173clear = 1 * gout172clear[0] + 2 * gout127clear[0] + 4 * gout41clear[0];
    std::vector<long> gout173clear = fvec173(gin173clear);

    assert(ctx.decrypt(&gout173[0]) == gout173clear[0]);
    assert(ctx.decrypt(&gout173[1]) == gout173clear[1]);
    std::vector<RotationPoly> lut174;
    std::vector<long (*)(long)> flut174;
    auto lut174idx0 = [](long I) -> long {
        /* GATE 41 (LUT3 _1416_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut174.push_back(ctx.genrate_lut(lut174idx0));
    flut174.push_back(lut174idx0);

    auto lut174idx1 = [](long I) -> long {
        /* GATE 28 (LUT3 _1403_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut174.push_back(ctx.genrate_lut(lut174idx1));
    flut174.push_back(lut174idx1);

    auto fvec174 = [flut174](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut174[i](I));
        return ret;
    };

    std::cerr << "\rLUT174   ";
    Ciphertext gin174 = 1 * gout173[0] + 2 * gout104[1] + 4 * gout28[0];
    std::vector<Ciphertext> gout174 = ctx.eval_lut_amortized(&gin174, lut174);

    long gin174clear = 1 * gout173clear[0] + 2 * gout104clear[1] + 4 * gout28clear[0];
    std::vector<long> gout174clear = fvec174(gin174clear);

    assert(ctx.decrypt(&gout174[0]) == gout174clear[0]);
    assert(ctx.decrypt(&gout174[1]) == gout174clear[1]);
    std::vector<RotationPoly> lut175;
    std::vector<long (*)(long)> flut175;
    auto lut175idx0 = [](long I) -> long {
        /* GATE 437 (LUT3 _1812_ INIT 0x78 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut175.push_back(ctx.genrate_lut(lut175idx0));
    flut175.push_back(lut175idx0);

    auto fvec175 = [flut175](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut175[i](I));
        return ret;
    };

    std::cerr << "\rLUT175   ";
    Ciphertext gin175 = 1 * ct_x14 + 2 * ct_y1 + 4 * ct_y15;
    std::vector<Ciphertext> gout175 = ctx.eval_lut_amortized(&gin175, lut175);

    long gin175clear = 1 * ct_x14clear + 2 * ct_y1clear + 4 * ct_y15clear;
    std::vector<long> gout175clear = fvec175(gin175clear);

    assert(ctx.decrypt(&gout175[0]) == gout175clear[0]);
    std::vector<RotationPoly> lut176;
    std::vector<long (*)(long)> flut176;
    auto lut176idx0 = [](long I) -> long {
        /* GATE 436 (LUT3 _1811_ INIT 0x87 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut176.push_back(ctx.genrate_lut(lut176idx0));
    flut176.push_back(lut176idx0);

    auto fvec176 = [flut176](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut176[i](I));
        return ret;
    };

    std::cerr << "\rLUT176   ";
    Ciphertext gin176 = 1 * ct_y0 + 2 * ct_x15 + 4 * gout175[0];
    std::vector<Ciphertext> gout176 = ctx.eval_lut_amortized(&gin176, lut176);

    long gin176clear = 1 * ct_y0clear + 2 * ct_x15clear + 4 * gout175clear[0];
    std::vector<long> gout176clear = fvec176(gin176clear);

    assert(ctx.decrypt(&gout176[0]) == gout176clear[0]);
    std::vector<RotationPoly> lut177;
    std::vector<long (*)(long)> flut177;
    auto lut177idx0 = [](long I) -> long {
        /* GATE 433 (LUT2 _1808_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut177.push_back(ctx.genrate_lut(lut177idx0));
    flut177.push_back(lut177idx0);

    auto fvec177 = [flut177](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut177[i](I));
        return ret;
    };

    std::cerr << "\rLUT177   ";
    Ciphertext gin177 = 1 * gout166[0] + 2 * gout176[0];
    std::vector<Ciphertext> gout177 = ctx.eval_lut_amortized(&gin177, lut177);

    long gin177clear = 1 * gout166clear[0] + 2 * gout176clear[0];
    std::vector<long> gout177clear = fvec177(gin177clear);

    assert(ctx.decrypt(&gout177[0]) == gout177clear[0]);
    std::vector<RotationPoly> lut178;
    std::vector<long (*)(long)> flut178;
    auto lut178idx0 = [](long I) -> long {
        /* GATE 3 (LUT3 _1378_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut178.push_back(ctx.genrate_lut(lut178idx0));
    flut178.push_back(lut178idx0);

    auto fvec178 = [flut178](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut178[i](I));
        return ret;
    };

    std::cerr << "\rLUT178   ";
    Ciphertext gin178 = 1 * gout78[0] + 2 * gout44[0] + 4 * gout129[0];
    std::vector<Ciphertext> gout178 = ctx.eval_lut_amortized(&gin178, lut178);

    long gin178clear = 1 * gout78clear[0] + 2 * gout44clear[0] + 4 * gout129clear[0];
    std::vector<long> gout178clear = fvec178(gin178clear);

    assert(ctx.decrypt(&gout178[0]) == gout178clear[0]);
    std::vector<RotationPoly> lut179;
    std::vector<long (*)(long)> flut179;
    auto lut179idx0 = [](long I) -> long {
        /* GATE 215 (LUT3 _1590_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut179.push_back(ctx.genrate_lut(lut179idx0));
    flut179.push_back(lut179idx0);

    auto lut179idx1 = [](long I) -> long {
        /* GATE 181 (LUT3 _1556_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut179.push_back(ctx.genrate_lut(lut179idx1));
    flut179.push_back(lut179idx1);

    auto fvec179 = [flut179](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut179[i](I));
        return ret;
    };

    std::cerr << "\rLUT179   ";
    Ciphertext gin179 = 1 * gout90[0] + 2 * gout81[0] + 4 * gout118[0];
    std::vector<Ciphertext> gout179 = ctx.eval_lut_amortized(&gin179, lut179);

    long gin179clear = 1 * gout90clear[0] + 2 * gout81clear[0] + 4 * gout118clear[0];
    std::vector<long> gout179clear = fvec179(gin179clear);

    assert(ctx.decrypt(&gout179[0]) == gout179clear[0]);
    assert(ctx.decrypt(&gout179[1]) == gout179clear[1]);
    std::vector<RotationPoly> lut180;
    std::vector<long (*)(long)> flut180;
    auto lut180idx0 = [](long I) -> long {
        /* GATE 118 (LUT3 _1493_ INIT 0x40 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut180.push_back(ctx.genrate_lut(lut180idx0));
    flut180.push_back(lut180idx0);

    auto lut180idx1 = [](long I) -> long {
        /* GATE 93 (LUT3 _1468_ INIT 0x87 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut180.push_back(ctx.genrate_lut(lut180idx1));
    flut180.push_back(lut180idx1);

    auto fvec180 = [flut180](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut180[i](I));
        return ret;
    };

    std::cerr << "\rLUT180   ";
    Ciphertext gin180 = 1 * gout108[1] + 2 * ct_x0 + 4 * ct_y6;
    std::vector<Ciphertext> gout180 = ctx.eval_lut_amortized(&gin180, lut180);

    long gin180clear = 1 * gout108clear[1] + 2 * ct_x0clear + 4 * ct_y6clear;
    std::vector<long> gout180clear = fvec180(gin180clear);

    assert(ctx.decrypt(&gout180[0]) == gout180clear[0]);
    assert(ctx.decrypt(&gout180[1]) == gout180clear[1]);
    std::vector<RotationPoly> lut181;
    std::vector<long (*)(long)> flut181;
    auto lut181idx0 = [](long I) -> long {
        /* GATE 429 (LUT3 _1804_ INIT 0x78 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut181.push_back(ctx.genrate_lut(lut181idx0));
    flut181.push_back(lut181idx0);

    auto fvec181 = [flut181](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut181[i](I));
        return ret;
    };

    std::cerr << "\rLUT181   ";
    Ciphertext gin181 = 1 * ct_x8 + 2 * ct_y7 + 4 * gout72[0];
    std::vector<Ciphertext> gout181 = ctx.eval_lut_amortized(&gin181, lut181);

    long gin181clear = 1 * ct_x8clear + 2 * ct_y7clear + 4 * gout72clear[0];
    std::vector<long> gout181clear = fvec181(gin181clear);

    assert(ctx.decrypt(&gout181[0]) == gout181clear[0]);
    std::vector<RotationPoly> lut182;
    std::vector<long (*)(long)> flut182;
    auto lut182idx0 = [](long I) -> long {
        /* GATE 427 (LUT3 _1802_ INIT 0xe1 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut182.push_back(ctx.genrate_lut(lut182idx0));
    flut182.push_back(lut182idx0);

    auto fvec182 = [flut182](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut182[i](I));
        return ret;
    };

    std::cerr << "\rLUT182   ";
    Ciphertext gin182 = 1 * gout122[0] + 2 * gout121[0] + 4 * gout181[0];
    std::vector<Ciphertext> gout182 = ctx.eval_lut_amortized(&gin182, lut182);

    long gin182clear = 1 * gout122clear[0] + 2 * gout121clear[0] + 4 * gout181clear[0];
    std::vector<long> gout182clear = fvec182(gin182clear);

    assert(ctx.decrypt(&gout182[0]) == gout182clear[0]);
    std::vector<RotationPoly> lut183;
    std::vector<long (*)(long)> flut183;
    auto lut183idx0 = [](long I) -> long {
        /* GATE 340 (LUT2 _1715_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut183.push_back(ctx.genrate_lut(lut183idx0));
    flut183.push_back(lut183idx0);

    auto fvec183 = [flut183](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut183[i](I));
        return ret;
    };

    std::cerr << "\rLUT183   ";
    Ciphertext gin183 = 1 * ct_x10 + 2 * ct_y3;
    std::vector<Ciphertext> gout183 = ctx.eval_lut_amortized(&gin183, lut183);

    long gin183clear = 1 * ct_x10clear + 2 * ct_y3clear;
    std::vector<long> gout183clear = fvec183(gin183clear);

    assert(ctx.decrypt(&gout183[0]) == gout183clear[0]);
    std::vector<RotationPoly> lut184;
    std::vector<long (*)(long)> flut184;
    auto lut184idx0 = [](long I) -> long {
        /* GATE 384 (LUT3 _1759_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut184.push_back(ctx.genrate_lut(lut184idx0));
    flut184.push_back(lut184idx0);

    auto lut184idx1 = [](long I) -> long {
        /* GATE 337 (LUT3 _1712_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut184.push_back(ctx.genrate_lut(lut184idx1));
    flut184.push_back(lut184idx1);

    auto fvec184 = [flut184](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut184[i](I));
        return ret;
    };

    std::cerr << "\rLUT184   ";
    Ciphertext gin184 = 1 * gout106[0] + 2 * gout43[0] + 4 * gout183[0];
    std::vector<Ciphertext> gout184 = ctx.eval_lut_amortized(&gin184, lut184);

    long gin184clear = 1 * gout106clear[0] + 2 * gout43clear[0] + 4 * gout183clear[0];
    std::vector<long> gout184clear = fvec184(gin184clear);

    assert(ctx.decrypt(&gout184[0]) == gout184clear[0]);
    assert(ctx.decrypt(&gout184[1]) == gout184clear[1]);
    std::vector<RotationPoly> lut185;
    std::vector<long (*)(long)> flut185;
    auto lut185idx0 = [](long I) -> long {
        /* GATE 441 (LUT3 _1816_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut185.push_back(ctx.genrate_lut(lut185idx0));
    flut185.push_back(lut185idx0);

    auto lut185idx1 = [](long I) -> long {
        /* GATE 382 (LUT3 _1757_ INIT 0x96 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut185.push_back(ctx.genrate_lut(lut185idx1));
    flut185.push_back(lut185idx1);

    auto fvec185 = [flut185](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut185[i](I));
        return ret;
    };

    std::cerr << "\rLUT185   ";
    Ciphertext gin185 = 1 * gout159[1] + 2 * gout152[0] + 4 * gout184[0];
    std::vector<Ciphertext> gout185 = ctx.eval_lut_amortized(&gin185, lut185);

    long gin185clear = 1 * gout159clear[1] + 2 * gout152clear[0] + 4 * gout184clear[0];
    std::vector<long> gout185clear = fvec185(gin185clear);

    assert(ctx.decrypt(&gout185[0]) == gout185clear[0]);
    assert(ctx.decrypt(&gout185[1]) == gout185clear[1]);
    std::vector<RotationPoly> lut186;
    std::vector<long (*)(long)> flut186;
    auto lut186idx0 = [](long I) -> long {
        /* GATE 15 (LUT2 _1390_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut186.push_back(ctx.genrate_lut(lut186idx0));
    flut186.push_back(lut186idx0);

    auto fvec186 = [flut186](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut186[i](I));
        return ret;
    };

    std::cerr << "\rLUT186   ";
    Ciphertext gin186 = 1 * ct_x1 + 2 * ct_y0;
    std::vector<Ciphertext> gout186 = ctx.eval_lut_amortized(&gin186, lut186);

    long gin186clear = 1 * ct_x1clear + 2 * ct_y0clear;
    std::vector<long> gout186clear = fvec186(gin186clear);

    assert(ctx.decrypt(&gout186[0]) == gout186clear[0]);
    std::vector<RotationPoly> lut187;
    std::vector<long (*)(long)> flut187;
    auto lut187idx0 = [](long I) -> long {
        /* GATE 18 (LUT3 _1393_ INIT 0x80 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut187.push_back(ctx.genrate_lut(lut187idx0));
    flut187.push_back(lut187idx0);

    auto lut187idx1 = [](long I) -> long {
        /* GATE 14 (LUT3 _1389_ INIT 0x78 PERM 120) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut187.push_back(ctx.genrate_lut(lut187idx1));
    flut187.push_back(lut187idx1);

    auto fvec187 = [flut187](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut187[i](I));
        return ret;
    };

    std::cerr << "\rLUT187   ";
    Ciphertext gin187 = 1 * gout186[0] + 2 * ct_x0 + 4 * ct_y1;
    std::vector<Ciphertext> gout187 = ctx.eval_lut_amortized(&gin187, lut187);

    long gin187clear = 1 * gout186clear[0] + 2 * ct_x0clear + 4 * ct_y1clear;
    std::vector<long> gout187clear = fvec187(gin187clear);

    assert(ctx.decrypt(&gout187[0]) == gout187clear[0]);
    assert(ctx.decrypt(&gout187[1]) == gout187clear[1]);
    std::vector<RotationPoly> lut188;
    std::vector<long (*)(long)> flut188;
    auto lut188idx0 = [](long I) -> long {
        /* GATE 27 (LUT2 _1402_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut188.push_back(ctx.genrate_lut(lut188idx0));
    flut188.push_back(lut188idx0);

    auto fvec188 = [flut188](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut188[i](I));
        return ret;
    };

    std::cerr << "\rLUT188   ";
    Ciphertext gin188 = 1 * gout187[0] + 2 * gout173[1];
    std::vector<Ciphertext> gout188 = ctx.eval_lut_amortized(&gin188, lut188);

    long gin188clear = 1 * gout187clear[0] + 2 * gout173clear[1];
    std::vector<long> gout188clear = fvec188(gin188clear);

    assert(ctx.decrypt(&gout188[0]) == gout188clear[0]);
    std::vector<RotationPoly> lut189;
    std::vector<long (*)(long)> flut189;
    auto lut189idx0 = [](long I) -> long {
        /* GATE 39 (LUT2 _1414_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut189.push_back(ctx.genrate_lut(lut189idx0));
    flut189.push_back(lut189idx0);

    auto fvec189 = [flut189](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut189[i](I));
        return ret;
    };

    std::cerr << "\rLUT189   ";
    Ciphertext gin189 = 1 * gout188[0] + 2 * gout174[1];
    std::vector<Ciphertext> gout189 = ctx.eval_lut_amortized(&gin189, lut189);

    long gin189clear = 1 * gout188clear[0] + 2 * gout174clear[1];
    std::vector<long> gout189clear = fvec189(gin189clear);

    assert(ctx.decrypt(&gout189[0]) == gout189clear[0]);
    std::vector<RotationPoly> lut190;
    std::vector<long (*)(long)> flut190;
    auto lut190idx0 = [](long I) -> long {
        /* GATE 392 (LUT3 _1767_ INIT 0x87 PERM 210) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut190.push_back(ctx.genrate_lut(lut190idx0));
    flut190.push_back(lut190idx0);

    auto fvec190 = [flut190](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut190[i](I));
        return ret;
    };

    std::cerr << "\rLUT190   ";
    Ciphertext gin190 = 1 * gout53[0] + 2 * ct_y9 + 4 * ct_x5;
    std::vector<Ciphertext> gout190 = ctx.eval_lut_amortized(&gin190, lut190);

    long gin190clear = 1 * gout53clear[0] + 2 * ct_y9clear + 4 * ct_x5clear;
    std::vector<long> gout190clear = fvec190(gin190clear);

    assert(ctx.decrypt(&gout190[0]) == gout190clear[0]);
    std::vector<RotationPoly> lut191;
    std::vector<long (*)(long)> flut191;
    auto lut191idx0 = [](long I) -> long {
        /* GATE 420 (LUT3 _1795_ INIT 0x40 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut191.push_back(ctx.genrate_lut(lut191idx0));
    flut191.push_back(lut191idx0);

    auto lut191idx1 = [](long I) -> long {
        /* GATE 391 (LUT3 _1766_ INIT 0x87 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut191.push_back(ctx.genrate_lut(lut191idx1));
    flut191.push_back(lut191idx1);

    auto fvec191 = [flut191](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut191[i](I));
        return ret;
    };

    std::cerr << "\rLUT191   ";
    Ciphertext gin191 = 1 * gout190[0] + 2 * ct_x3 + 4 * ct_y11;
    std::vector<Ciphertext> gout191 = ctx.eval_lut_amortized(&gin191, lut191);

    long gin191clear = 1 * gout190clear[0] + 2 * ct_x3clear + 4 * ct_y11clear;
    std::vector<long> gout191clear = fvec191(gin191clear);

    assert(ctx.decrypt(&gout191[0]) == gout191clear[0]);
    assert(ctx.decrypt(&gout191[1]) == gout191clear[1]);
    std::vector<RotationPoly> lut192;
    std::vector<long (*)(long)> flut192;
    auto lut192idx0 = [](long I) -> long {
        /* GATE 419 (LUT3 _1794_ INIT 0xe3 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut192.push_back(ctx.genrate_lut(lut192idx0));
    flut192.push_back(lut192idx0);

    auto fvec192 = [flut192](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut192[i](I));
        return ret;
    };

    std::cerr << "\rLUT192   ";
    Ciphertext gin192 = 1 * gout96[0] + 2 * gout191[0] + 4 * gout46[0];
    std::vector<Ciphertext> gout192 = ctx.eval_lut_amortized(&gin192, lut192);

    long gin192clear = 1 * gout96clear[0] + 2 * gout191clear[0] + 4 * gout46clear[0];
    std::vector<long> gout192clear = fvec192(gin192clear);

    assert(ctx.decrypt(&gout192[0]) == gout192clear[0]);
    std::vector<RotationPoly> lut193;
    std::vector<long (*)(long)> flut193;
    auto lut193idx0 = [](long I) -> long {
        /* GATE 418 (LUT3 _1793_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut193.push_back(ctx.genrate_lut(lut193idx0));
    flut193.push_back(lut193idx0);

    auto fvec193 = [flut193](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut193[i](I));
        return ret;
    };

    std::cerr << "\rLUT193   ";
    Ciphertext gin193 = 1 * gout192[0] + 2 * gout141[0] + 4 * gout148[0];
    std::vector<Ciphertext> gout193 = ctx.eval_lut_amortized(&gin193, lut193);

    long gin193clear = 1 * gout192clear[0] + 2 * gout141clear[0] + 4 * gout148clear[0];
    std::vector<long> gout193clear = fvec193(gin193clear);

    assert(ctx.decrypt(&gout193[0]) == gout193clear[0]);
    std::vector<RotationPoly> lut194;
    std::vector<long (*)(long)> flut194;
    auto lut194idx0 = [](long I) -> long {
        /* GATE 417 (LUT3 _1792_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut194.push_back(ctx.genrate_lut(lut194idx0));
    flut194.push_back(lut194idx0);

    auto fvec194 = [flut194](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut194[i](I));
        return ret;
    };

    std::cerr << "\rLUT194   ";
    Ciphertext gin194 = 1 * gout193[0] + 2 * gout182[0] + 4 * gout177[0];
    std::vector<Ciphertext> gout194 = ctx.eval_lut_amortized(&gin194, lut194);

    long gin194clear = 1 * gout193clear[0] + 2 * gout182clear[0] + 4 * gout177clear[0];
    std::vector<long> gout194clear = fvec194(gin194clear);

    assert(ctx.decrypt(&gout194[0]) == gout194clear[0]);
    std::vector<RotationPoly> lut195;
    std::vector<long (*)(long)> flut195;
    auto lut195idx0 = [](long I) -> long {
        /* GATE 443 (LUT3 _1818_ INIT 0x71 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut195.push_back(ctx.genrate_lut(lut195idx0));
    flut195.push_back(lut195idx0);

    auto lut195idx1 = [](long I) -> long {
        /* GATE 390 (LUT3 _1765_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut195.push_back(ctx.genrate_lut(lut195idx1));
    flut195.push_back(lut195idx1);

    auto fvec195 = [flut195](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut195[i](I));
        return ret;
    };

    std::cerr << "\rLUT195   ";
    Ciphertext gin195 = 1 * gout191[1] + 2 * gout117[1] + 4 * gout97[0];
    std::vector<Ciphertext> gout195 = ctx.eval_lut_amortized(&gin195, lut195);

    long gin195clear = 1 * gout191clear[1] + 2 * gout117clear[1] + 4 * gout97clear[0];
    std::vector<long> gout195clear = fvec195(gin195clear);

    assert(ctx.decrypt(&gout195[0]) == gout195clear[0]);
    assert(ctx.decrypt(&gout195[1]) == gout195clear[1]);
    std::vector<RotationPoly> lut196;
    std::vector<long (*)(long)> flut196;
    auto lut196idx0 = [](long I) -> long {
        /* GATE 290 (LUT2 _1665_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut196.push_back(ctx.genrate_lut(lut196idx0));
    flut196.push_back(lut196idx0);

    auto fvec196 = [flut196](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut196[i](I));
        return ret;
    };

    std::cerr << "\rLUT196   ";
    Ciphertext gin196 = 1 * ct_x10 + 2 * ct_y2;
    std::vector<Ciphertext> gout196 = ctx.eval_lut_amortized(&gin196, lut196);

    long gin196clear = 1 * ct_x10clear + 2 * ct_y2clear;
    std::vector<long> gout196clear = fvec196(gin196clear);

    assert(ctx.decrypt(&gout196[0]) == gout196clear[0]);
    std::vector<RotationPoly> lut197;
    std::vector<long (*)(long)> flut197;
    auto lut197idx0 = [](long I) -> long {
        /* GATE 332 (LUT3 _1707_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut197.push_back(ctx.genrate_lut(lut197idx0));
    flut197.push_back(lut197idx0);

    auto lut197idx1 = [](long I) -> long {
        /* GATE 288 (LUT3 _1663_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut197.push_back(ctx.genrate_lut(lut197idx1));
    flut197.push_back(lut197idx1);

    auto fvec197 = [flut197](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut197[i](I));
        return ret;
    };

    std::cerr << "\rLUT197   ";
    Ciphertext gin197 = 1 * gout31[0] + 2 * gout196[0] + 4 * gout164[0];
    std::vector<Ciphertext> gout197 = ctx.eval_lut_amortized(&gin197, lut197);

    long gin197clear = 1 * gout31clear[0] + 2 * gout196clear[0] + 4 * gout164clear[0];
    std::vector<long> gout197clear = fvec197(gin197clear);

    assert(ctx.decrypt(&gout197[0]) == gout197clear[0]);
    assert(ctx.decrypt(&gout197[1]) == gout197clear[1]);
    std::vector<RotationPoly> lut198;
    std::vector<long (*)(long)> flut198;
    auto lut198idx0 = [](long I) -> long {
        /* GATE 381 (LUT3 _1756_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut198.push_back(ctx.genrate_lut(lut198idx0));
    flut198.push_back(lut198idx0);

    auto lut198idx1 = [](long I) -> long {
        /* GATE 331 (LUT3 _1706_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut198.push_back(ctx.genrate_lut(lut198idx1));
    flut198.push_back(lut198idx1);

    auto fvec198 = [flut198](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut198[i](I));
        return ret;
    };

    std::cerr << "\rLUT198   ";
    Ciphertext gin198 = 1 * gout197[0] + 2 * gout95[0] + 4 * gout184[1];
    std::vector<Ciphertext> gout198 = ctx.eval_lut_amortized(&gin198, lut198);

    long gin198clear = 1 * gout197clear[0] + 2 * gout95clear[0] + 4 * gout184clear[1];
    std::vector<long> gout198clear = fvec198(gin198clear);

    assert(ctx.decrypt(&gout198[0]) == gout198clear[0]);
    assert(ctx.decrypt(&gout198[1]) == gout198clear[1]);
    std::vector<RotationPoly> lut199;
    std::vector<long (*)(long)> flut199;
    auto lut199idx0 = [](long I) -> long {
        /* GATE 138 (LUT2 _1513_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut199.push_back(ctx.genrate_lut(lut199idx0));
    flut199.push_back(lut199idx0);

    auto fvec199 = [flut199](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut199[i](I));
        return ret;
    };

    std::cerr << "\rLUT199   ";
    Ciphertext gin199 = 1 * ct_x8 + 2 * ct_y0;
    std::vector<Ciphertext> gout199 = ctx.eval_lut_amortized(&gin199, lut199);

    long gin199clear = 1 * ct_x8clear + 2 * ct_y0clear;
    std::vector<long> gout199clear = fvec199(gin199clear);

    assert(ctx.decrypt(&gout199[0]) == gout199clear[0]);
    std::vector<RotationPoly> lut200;
    std::vector<long (*)(long)> flut200;
    auto lut200idx0 = [](long I) -> long {
        /* GATE 169 (LUT3 _1544_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut200.push_back(ctx.genrate_lut(lut200idx0));
    flut200.push_back(lut200idx0);

    auto lut200idx1 = [](long I) -> long {
        /* GATE 135 (LUT3 _1510_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut200.push_back(ctx.genrate_lut(lut200idx1));
    flut200.push_back(lut200idx1);

    auto fvec200 = [flut200](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut200[i](I));
        return ret;
    };

    std::cerr << "\rLUT200   ";
    Ciphertext gin200 = 1 * gout124[0] + 2 * gout49[0] + 4 * gout199[0];
    std::vector<Ciphertext> gout200 = ctx.eval_lut_amortized(&gin200, lut200);

    long gin200clear = 1 * gout124clear[0] + 2 * gout49clear[0] + 4 * gout199clear[0];
    std::vector<long> gout200clear = fvec200(gin200clear);

    assert(ctx.decrypt(&gout200[0]) == gout200clear[0]);
    assert(ctx.decrypt(&gout200[1]) == gout200clear[1]);
    std::vector<RotationPoly> lut201;
    std::vector<long (*)(long)> flut201;
    auto lut201idx0 = [](long I) -> long {
        /* GATE 63 (LUT2 _1438_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut201.push_back(ctx.genrate_lut(lut201idx0));
    flut201.push_back(lut201idx0);

    auto fvec201 = [flut201](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut201[i](I));
        return ret;
    };

    std::cerr << "\rLUT201   ";
    Ciphertext gin201 = 1 * ct_y2 + 2 * ct_x3;
    std::vector<Ciphertext> gout201 = ctx.eval_lut_amortized(&gin201, lut201);

    long gin201clear = 1 * ct_y2clear + 2 * ct_x3clear;
    std::vector<long> gout201clear = fvec201(gin201clear);

    assert(ctx.decrypt(&gout201[0]) == gout201clear[0]);
    std::vector<RotationPoly> lut202;
    std::vector<long (*)(long)> flut202;
    auto lut202idx0 = [](long I) -> long {
        /* GATE 84 (LUT3 _1459_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut202.push_back(ctx.genrate_lut(lut202idx0));
    flut202.push_back(lut202idx0);

    auto lut202idx1 = [](long I) -> long {
        /* GATE 61 (LUT3 _1436_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut202.push_back(ctx.genrate_lut(lut202idx1));
    flut202.push_back(lut202idx1);

    auto fvec202 = [flut202](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut202[i](I));
        return ret;
    };

    std::cerr << "\rLUT202   ";
    Ciphertext gin202 = 1 * gout26[0] + 2 * gout201[0] + 4 * gout157[0];
    std::vector<Ciphertext> gout202 = ctx.eval_lut_amortized(&gin202, lut202);

    long gin202clear = 1 * gout26clear[0] + 2 * gout201clear[0] + 4 * gout157clear[0];
    std::vector<long> gout202clear = fvec202(gin202clear);

    assert(ctx.decrypt(&gout202[0]) == gout202clear[0]);
    assert(ctx.decrypt(&gout202[1]) == gout202clear[1]);
    std::vector<RotationPoly> lut203;
    std::vector<long (*)(long)> flut203;
    auto lut203idx0 = [](long I) -> long {
        /* GATE 82 (LUT3 _1457_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut203.push_back(ctx.genrate_lut(lut203idx0));
    flut203.push_back(lut203idx0);

    auto lut203idx1 = [](long I) -> long {
        /* GATE 59 (LUT3 _1434_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut203.push_back(ctx.genrate_lut(lut203idx1));
    flut203.push_back(lut203idx1);

    auto fvec203 = [flut203](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut203[i](I));
        return ret;
    };

    std::cerr << "\rLUT203   ";
    Ciphertext gin203 = 1 * gout69[1] + 2 * gout202[1] + 4 * gout108[0];
    std::vector<Ciphertext> gout203 = ctx.eval_lut_amortized(&gin203, lut203);

    long gin203clear = 1 * gout69clear[1] + 2 * gout202clear[1] + 4 * gout108clear[0];
    std::vector<long> gout203clear = fvec203(gin203clear);

    assert(ctx.decrypt(&gout203[0]) == gout203clear[0]);
    assert(ctx.decrypt(&gout203[1]) == gout203clear[1]);
    std::vector<RotationPoly> lut204;
    std::vector<long (*)(long)> flut204;
    auto lut204idx0 = [](long I) -> long {
        /* GATE 330 (LUT3 _1705_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut204.push_back(ctx.genrate_lut(lut204idx0));
    flut204.push_back(lut204idx0);

    auto lut204idx1 = [](long I) -> long {
        /* GATE 286 (LUT3 _1661_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut204.push_back(ctx.genrate_lut(lut204idx1));
    flut204.push_back(lut204idx1);

    auto fvec204 = [flut204](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut204[i](I));
        return ret;
    };

    std::cerr << "\rLUT204   ";
    Ciphertext gin204 = 1 * gout156[1] + 2 * gout197[1] + 4 * gout60[0];
    std::vector<Ciphertext> gout204 = ctx.eval_lut_amortized(&gin204, lut204);

    long gin204clear = 1 * gout156clear[1] + 2 * gout197clear[1] + 4 * gout60clear[0];
    std::vector<long> gout204clear = fvec204(gin204clear);

    assert(ctx.decrypt(&gout204[0]) == gout204clear[0]);
    assert(ctx.decrypt(&gout204[1]) == gout204clear[1]);
    std::vector<RotationPoly> lut205;
    std::vector<long (*)(long)> flut205;
    auto lut205idx0 = [](long I) -> long {
        /* GATE 400 (LUT3 _1775_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut205.push_back(ctx.genrate_lut(lut205idx0));
    flut205.push_back(lut205idx0);

    auto lut205idx1 = [](long I) -> long {
        /* GATE 329 (LUT3 _1704_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut205.push_back(ctx.genrate_lut(lut205idx1));
    flut205.push_back(lut205idx1);

    auto fvec205 = [flut205](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut205[i](I));
        return ret;
    };

    std::cerr << "\rLUT205   ";
    Ciphertext gin205 = 1 * gout204[0] + 2 * gout198[1] + 4 * gout162[1];
    std::vector<Ciphertext> gout205 = ctx.eval_lut_amortized(&gin205, lut205);

    long gin205clear = 1 * gout204clear[0] + 2 * gout198clear[1] + 4 * gout162clear[1];
    std::vector<long> gout205clear = fvec205(gin205clear);

    assert(ctx.decrypt(&gout205[0]) == gout205clear[0]);
    assert(ctx.decrypt(&gout205[1]) == gout205clear[1]);
    std::vector<RotationPoly> lut206;
    std::vector<long (*)(long)> flut206;
    auto lut206idx0 = [](long I) -> long {
        /* GATE 109 (LUT2 _1484_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut206.push_back(ctx.genrate_lut(lut206idx0));
    flut206.push_back(lut206idx0);

    auto fvec206 = [flut206](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut206[i](I));
        return ret;
    };

    std::cerr << "\rLUT206   ";
    Ciphertext gin206 = 1 * ct_y0 + 2 * ct_x7;
    std::vector<Ciphertext> gout206 = ctx.eval_lut_amortized(&gin206, lut206);

    long gin206clear = 1 * ct_y0clear + 2 * ct_x7clear;
    std::vector<long> gout206clear = fvec206(gin206clear);

    assert(ctx.decrypt(&gout206[0]) == gout206clear[0]);
    std::vector<RotationPoly> lut207;
    std::vector<long (*)(long)> flut207;
    auto lut207idx0 = [](long I) -> long {
        /* GATE 134 (LUT3 _1509_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut207.push_back(ctx.genrate_lut(lut207idx0));
    flut207.push_back(lut207idx0);

    auto lut207idx1 = [](long I) -> long {
        /* GATE 106 (LUT3 _1481_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut207.push_back(ctx.genrate_lut(lut207idx1));
    flut207.push_back(lut207idx1);

    auto fvec207 = [flut207](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut207[i](I));
        return ret;
    };

    std::cerr << "\rLUT207   ";
    Ciphertext gin207 = 1 * gout36[0] + 2 * gout16[0] + 4 * gout206[0];
    std::vector<Ciphertext> gout207 = ctx.eval_lut_amortized(&gin207, lut207);

    long gin207clear = 1 * gout36clear[0] + 2 * gout16clear[0] + 4 * gout206clear[0];
    std::vector<long> gout207clear = fvec207(gin207clear);

    assert(ctx.decrypt(&gout207[0]) == gout207clear[0]);
    assert(ctx.decrypt(&gout207[1]) == gout207clear[1]);
    std::vector<RotationPoly> lut208;
    std::vector<long (*)(long)> flut208;
    auto lut208idx0 = [](long I) -> long {
        /* GATE 132 (LUT3 _1507_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut208.push_back(ctx.genrate_lut(lut208idx0));
    flut208.push_back(lut208idx0);

    auto lut208idx1 = [](long I) -> long {
        /* GATE 104 (LUT3 _1479_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut208.push_back(ctx.genrate_lut(lut208idx1));
    flut208.push_back(lut208idx1);

    auto fvec208 = [flut208](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut208[i](I));
        return ret;
    };

    std::cerr << "\rLUT208   ";
    Ciphertext gin208 = 1 * gout101[1] + 2 * gout207[1] + 4 * gout171[1];
    std::vector<Ciphertext> gout208 = ctx.eval_lut_amortized(&gin208, lut208);

    long gin208clear = 1 * gout101clear[1] + 2 * gout207clear[1] + 4 * gout171clear[1];
    std::vector<long> gout208clear = fvec208(gin208clear);

    assert(ctx.decrypt(&gout208[0]) == gout208clear[0]);
    assert(ctx.decrypt(&gout208[1]) == gout208clear[1]);
    std::vector<RotationPoly> lut209;
    std::vector<long (*)(long)> flut209;
    auto lut209idx0 = [](long I) -> long {
        /* GATE 69 (LUT2 _1444_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut209.push_back(ctx.genrate_lut(lut209idx0));
    flut209.push_back(lut209idx0);

    auto fvec209 = [flut209](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut209[i](I));
        return ret;
    };

    std::cerr << "\rLUT209   ";
    Ciphertext gin209 = 1 * gout28[0] + 2 * gout107[0];
    std::vector<Ciphertext> gout209 = ctx.eval_lut_amortized(&gin209, lut209);

    long gin209clear = 1 * gout28clear[0] + 2 * gout107clear[0];
    std::vector<long> gout209clear = fvec209(gin209clear);

    assert(ctx.decrypt(&gout209[0]) == gout209clear[0]);
    std::vector<RotationPoly> lut210;
    std::vector<long (*)(long)> flut210;
    auto lut210idx0 = [](long I) -> long {
        /* GATE 80 (LUT3 _1455_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut210.push_back(ctx.genrate_lut(lut210idx0));
    flut210.push_back(lut210idx0);

    auto lut210idx1 = [](long I) -> long {
        /* GATE 57 (LUT3 _1432_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut210.push_back(ctx.genrate_lut(lut210idx1));
    flut210.push_back(lut210idx1);

    auto fvec210 = [flut210](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut210[i](I));
        return ret;
    };

    std::cerr << "\rLUT210   ";
    Ciphertext gin210 = 1 * gout150[0] + 2 * gout203[1] + 4 * gout209[0];
    std::vector<Ciphertext> gout210 = ctx.eval_lut_amortized(&gin210, lut210);

    long gin210clear = 1 * gout150clear[0] + 2 * gout203clear[1] + 4 * gout209clear[0];
    std::vector<long> gout210clear = fvec210(gin210clear);

    assert(ctx.decrypt(&gout210[0]) == gout210clear[0]);
    assert(ctx.decrypt(&gout210[1]) == gout210clear[1]);
    std::vector<RotationPoly> lut211;
    std::vector<long (*)(long)> flut211;
    auto lut211idx0 = [](long I) -> long {
        /* GATE 250 (LUT2 _1625_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut211.push_back(ctx.genrate_lut(lut211idx0));
    flut211.push_back(lut211idx0);

    auto fvec211 = [flut211](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut211[i](I));
        return ret;
    };

    std::cerr << "\rLUT211   ";
    Ciphertext gin211 = 1 * ct_y4 + 2 * ct_x7;
    std::vector<Ciphertext> gout211 = ctx.eval_lut_amortized(&gin211, lut211);

    long gin211clear = 1 * ct_y4clear + 2 * ct_x7clear;
    std::vector<long> gout211clear = fvec211(gin211clear);

    assert(ctx.decrypt(&gout211[0]) == gout211clear[0]);
    std::vector<RotationPoly> lut212;
    std::vector<long (*)(long)> flut212;
    auto lut212idx0 = [](long I) -> long {
        /* GATE 149 (LUT2 _1524_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut212.push_back(ctx.genrate_lut(lut212idx0));
    flut212.push_back(lut212idx0);

    auto fvec212 = [flut212](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut212[i](I));
        return ret;
    };

    std::cerr << "\rLUT212   ";
    Ciphertext gin212 = 1 * ct_y6 + 2 * ct_x2;
    std::vector<Ciphertext> gout212 = ctx.eval_lut_amortized(&gin212, lut212);

    long gin212clear = 1 * ct_y6clear + 2 * ct_x2clear;
    std::vector<long> gout212clear = fvec212(gin212clear);

    assert(ctx.decrypt(&gout212[0]) == gout212clear[0]);
    std::vector<RotationPoly> lut213;
    std::vector<long (*)(long)> flut213;
    auto lut213idx0 = [](long I) -> long {
        /* GATE 179 (LUT3 _1554_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut213.push_back(ctx.genrate_lut(lut213idx0));
    flut213.push_back(lut213idx0);

    auto lut213idx1 = [](long I) -> long {
        /* GATE 146 (LUT3 _1521_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut213.push_back(ctx.genrate_lut(lut213idx1));
    flut213.push_back(lut213idx1);

    auto fvec213 = [flut213](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut213[i](I));
        return ret;
    };

    std::cerr << "\rLUT213   ";
    Ciphertext gin213 = 1 * gout61[0] + 2 * gout35[0] + 4 * gout212[0];
    std::vector<Ciphertext> gout213 = ctx.eval_lut_amortized(&gin213, lut213);

    long gin213clear = 1 * gout61clear[0] + 2 * gout35clear[0] + 4 * gout212clear[0];
    std::vector<long> gout213clear = fvec213(gin213clear);

    assert(ctx.decrypt(&gout213[0]) == gout213clear[0]);
    assert(ctx.decrypt(&gout213[1]) == gout213clear[1]);
    std::vector<RotationPoly> lut214;
    std::vector<long (*)(long)> flut214;
    auto lut214idx0 = [](long I) -> long {
        /* GATE 186 (LUT3 _1561_ INIT 0x71 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut214.push_back(ctx.genrate_lut(lut214idx0));
    flut214.push_back(lut214idx0);

    auto lut214idx1 = [](long I) -> long {
        /* GATE 143 (LUT3 _1518_ INIT 0x69 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut214.push_back(ctx.genrate_lut(lut214idx1));
    flut214.push_back(lut214idx1);

    auto fvec214 = [flut214](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut214[i](I));
        return ret;
    };

    std::cerr << "\rLUT214   ";
    Ciphertext gin214 = 1 * gout30[1] + 2 * gout213[1] + 4 * gout171[0];
    std::vector<Ciphertext> gout214 = ctx.eval_lut_amortized(&gin214, lut214);

    long gin214clear = 1 * gout30clear[1] + 2 * gout213clear[1] + 4 * gout171clear[0];
    std::vector<long> gout214clear = fvec214(gin214clear);

    assert(ctx.decrypt(&gout214[0]) == gout214clear[0]);
    assert(ctx.decrypt(&gout214[1]) == gout214clear[1]);
    std::vector<RotationPoly> lut215;
    std::vector<long (*)(long)> flut215;
    auto lut215idx0 = [](long I) -> long {
        /* GATE 225 (LUT3 _1600_ INIT 0x40 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut215.push_back(ctx.genrate_lut(lut215idx0));
    flut215.push_back(lut215idx0);

    auto lut215idx1 = [](long I) -> long {
        /* GATE 185 (LUT3 _1560_ INIT 0x87 PERM 120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut215.push_back(ctx.genrate_lut(lut215idx1));
    flut215.push_back(lut215idx1);

    auto fvec215 = [flut215](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut215[i](I));
        return ret;
    };

    std::cerr << "\rLUT215   ";
    Ciphertext gin215 = 1 * gout214[0] + 2 * ct_x0 + 4 * ct_y9;
    std::vector<Ciphertext> gout215 = ctx.eval_lut_amortized(&gin215, lut215);

    long gin215clear = 1 * gout214clear[0] + 2 * ct_x0clear + 4 * ct_y9clear;
    std::vector<long> gout215clear = fvec215(gin215clear);

    assert(ctx.decrypt(&gout215[0]) == gout215clear[0]);
    assert(ctx.decrypt(&gout215[1]) == gout215clear[1]);
    std::vector<RotationPoly> lut216;
    std::vector<long (*)(long)> flut216;
    auto lut216idx0 = [](long I) -> long {
        /* GATE 142 (LUT2 _1517_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut216.push_back(ctx.genrate_lut(lut216idx0));
    flut216.push_back(lut216idx0);

    auto fvec216 = [flut216](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut216[i](I));
        return ret;
    };

    std::cerr << "\rLUT216   ";
    Ciphertext gin216 = 1 * ct_y3 + 2 * ct_x5;
    std::vector<Ciphertext> gout216 = ctx.eval_lut_amortized(&gin216, lut216);

    long gin216clear = 1 * ct_y3clear + 2 * ct_x5clear;
    std::vector<long> gout216clear = fvec216(gin216clear);

    assert(ctx.decrypt(&gout216[0]) == gout216clear[0]);
    std::vector<RotationPoly> lut217;
    std::vector<long (*)(long)> flut217;
    auto lut217idx0 = [](long I) -> long {
        /* GATE 180 (LUT3 _1555_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut217.push_back(ctx.genrate_lut(lut217idx0));
    flut217.push_back(lut217idx0);

    auto lut217idx1 = [](long I) -> long {
        /* GATE 139 (LUT3 _1514_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut217.push_back(ctx.genrate_lut(lut217idx1));
    flut217.push_back(lut217idx1);

    auto fvec217 = [flut217](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut217[i](I));
        return ret;
    };

    std::cerr << "\rLUT217   ";
    Ciphertext gin217 = 1 * gout54[0] + 2 * gout135[0] + 4 * gout216[0];
    std::vector<Ciphertext> gout217 = ctx.eval_lut_amortized(&gin217, lut217);

    long gin217clear = 1 * gout54clear[0] + 2 * gout135clear[0] + 4 * gout216clear[0];
    std::vector<long> gout217clear = fvec217(gin217clear);

    assert(ctx.decrypt(&gout217[0]) == gout217clear[0]);
    assert(ctx.decrypt(&gout217[1]) == gout217clear[1]);
    std::vector<RotationPoly> lut218;
    std::vector<long (*)(long)> flut218;
    auto lut218idx0 = [](long I) -> long {
        /* GATE 222 (LUT3 _1597_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut218.push_back(ctx.genrate_lut(lut218idx0));
    flut218.push_back(lut218idx0);

    auto lut218idx1 = [](long I) -> long {
        /* GATE 178 (LUT3 _1553_ INIT 0x96 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut218.push_back(ctx.genrate_lut(lut218idx1));
    flut218.push_back(lut218idx1);

    auto fvec218 = [flut218](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut218[i](I));
        return ret;
    };

    std::cerr << "\rLUT218   ";
    Ciphertext gin218 = 1 * gout213[0] + 2 * gout179[1] + 4 * gout217[0];
    std::vector<Ciphertext> gout218 = ctx.eval_lut_amortized(&gin218, lut218);

    long gin218clear = 1 * gout213clear[0] + 2 * gout179clear[1] + 4 * gout217clear[0];
    std::vector<long> gout218clear = fvec218(gin218clear);

    assert(ctx.decrypt(&gout218[0]) == gout218clear[0]);
    assert(ctx.decrypt(&gout218[1]) == gout218clear[1]);
    std::vector<RotationPoly> lut219;
    std::vector<long (*)(long)> flut219;
    auto lut219idx0 = [](long I) -> long {
        /* GATE 268 (LUT2 _1643_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut219.push_back(ctx.genrate_lut(lut219idx0));
    flut219.push_back(lut219idx0);

    auto lut219idx1 = [](long I) -> long {
        /* GATE 221 (LUT2 _1596_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut219.push_back(ctx.genrate_lut(lut219idx1));
    flut219.push_back(lut219idx1);

    auto fvec219 = [flut219](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut219[i](I));
        return ret;
    };

    std::cerr << "\rLUT219   ";
    Ciphertext gin219 = 1 * gout218[0] + 2 * gout51[0];
    std::vector<Ciphertext> gout219 = ctx.eval_lut_amortized(&gin219, lut219);

    long gin219clear = 1 * gout218clear[0] + 2 * gout51clear[0];
    std::vector<long> gout219clear = fvec219(gin219clear);

    assert(ctx.decrypt(&gout219[0]) == gout219clear[0]);
    assert(ctx.decrypt(&gout219[1]) == gout219clear[1]);
    std::vector<RotationPoly> lut220;
    std::vector<long (*)(long)> flut220;
    auto lut220idx0 = [](long I) -> long {
        /* GATE 167 (LUT3 _1542_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut220.push_back(ctx.genrate_lut(lut220idx0));
    flut220.push_back(lut220idx0);

    auto lut220idx1 = [](long I) -> long {
        /* GATE 133 (LUT3 _1508_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut220.push_back(ctx.genrate_lut(lut220idx1));
    flut220.push_back(lut220idx1);

    auto fvec220 = [flut220](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut220[i](I));
        return ret;
    };

    std::cerr << "\rLUT220   ";
    Ciphertext gin220 = 1 * gout207[0] + 2 * gout200[1] + 4 * gout217[1];
    std::vector<Ciphertext> gout220 = ctx.eval_lut_amortized(&gin220, lut220);

    long gin220clear = 1 * gout207clear[0] + 2 * gout200clear[1] + 4 * gout217clear[1];
    std::vector<long> gout220clear = fvec220(gin220clear);

    assert(ctx.decrypt(&gout220[0]) == gout220clear[0]);
    assert(ctx.decrypt(&gout220[1]) == gout220clear[1]);
    std::vector<RotationPoly> lut221;
    std::vector<long (*)(long)> flut221;
    auto lut221idx0 = [](long I) -> long {
        /* GATE 165 (LUT3 _1540_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut221.push_back(ctx.genrate_lut(lut221idx0));
    flut221.push_back(lut221idx0);

    auto lut221idx1 = [](long I) -> long {
        /* GATE 131 (LUT3 _1506_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut221.push_back(ctx.genrate_lut(lut221idx1));
    flut221.push_back(lut221idx1);

    auto fvec221 = [flut221](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut221[i](I));
        return ret;
    };

    std::cerr << "\rLUT221   ";
    Ciphertext gin221 = 1 * gout208[0] + 2 * gout220[1] + 4 * gout214[1];
    std::vector<Ciphertext> gout221 = ctx.eval_lut_amortized(&gin221, lut221);

    long gin221clear = 1 * gout208clear[0] + 2 * gout220clear[1] + 4 * gout214clear[1];
    std::vector<long> gout221clear = fvec221(gin221clear);

    assert(ctx.decrypt(&gout221[0]) == gout221clear[0]);
    assert(ctx.decrypt(&gout221[1]) == gout221clear[1]);
    std::vector<RotationPoly> lut222;
    std::vector<long (*)(long)> flut222;
    auto lut222idx0 = [](long I) -> long {
        /* GATE 449 (LUT3 _1824_ INIT 0xd4 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut222.push_back(ctx.genrate_lut(lut222idx0));
    flut222.push_back(lut222idx0);

    auto lut222idx1 = [](long I) -> long {
        /* GATE 389 (LUT3 _1764_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut222.push_back(ctx.genrate_lut(lut222idx1));
    flut222.push_back(lut222idx1);

    auto fvec222 = [flut222](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut222[i](I));
        return ret;
    };

    std::cerr << "\rLUT222   ";
    Ciphertext gin222 = 1 * gout195[1] + 2 * gout169[0] + 4 * gout162[0];
    std::vector<Ciphertext> gout222 = ctx.eval_lut_amortized(&gin222, lut222);

    long gin222clear = 1 * gout195clear[1] + 2 * gout169clear[0] + 4 * gout162clear[0];
    std::vector<long> gout222clear = fvec222(gin222clear);

    assert(ctx.decrypt(&gout222[0]) == gout222clear[0]);
    assert(ctx.decrypt(&gout222[1]) == gout222clear[1]);
    std::vector<RotationPoly> lut223;
    std::vector<long (*)(long)> flut223;
    auto lut223idx0 = [](long I) -> long {
        /* GATE 218 (LUT2 _1593_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut223.push_back(ctx.genrate_lut(lut223idx0));
    flut223.push_back(lut223idx0);

    auto fvec223 = [flut223](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut223[i](I));
        return ret;
    };

    std::cerr << "\rLUT223   ";
    Ciphertext gin223 = 1 * ct_y7 + 2 * ct_x3;
    std::vector<Ciphertext> gout223 = ctx.eval_lut_amortized(&gin223, lut223);

    long gin223clear = 1 * ct_y7clear + 2 * ct_x3clear;
    std::vector<long> gout223clear = fvec223(gin223clear);

    assert(ctx.decrypt(&gout223[0]) == gout223clear[0]);
    std::vector<RotationPoly> lut224;
    std::vector<long (*)(long)> flut224;
    auto lut224idx0 = [](long I) -> long {
        /* GATE 254 (LUT3 _1629_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut224.push_back(ctx.genrate_lut(lut224idx0));
    flut224.push_back(lut224idx0);

    auto lut224idx1 = [](long I) -> long {
        /* GATE 217 (LUT3 _1592_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut224.push_back(ctx.genrate_lut(lut224idx1));
    flut224.push_back(lut224idx1);

    auto fvec224 = [flut224](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut224[i](I));
        return ret;
    };

    std::cerr << "\rLUT224   ";
    Ciphertext gin224 = 1 * gout223[0] + 2 * gout143[0] + 4 * gout64[0];
    std::vector<Ciphertext> gout224 = ctx.eval_lut_amortized(&gin224, lut224);

    long gin224clear = 1 * gout223clear[0] + 2 * gout143clear[0] + 4 * gout64clear[0];
    std::vector<long> gout224clear = fvec224(gin224clear);

    assert(ctx.decrypt(&gout224[0]) == gout224clear[0]);
    assert(ctx.decrypt(&gout224[1]) == gout224clear[1]);
    std::vector<RotationPoly> lut225;
    std::vector<long (*)(long)> flut225;
    auto lut225idx0 = [](long I) -> long {
        /* GATE 305 (LUT3 _1680_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut225.push_back(ctx.genrate_lut(lut225idx0));
    flut225.push_back(lut225idx0);

    auto lut225idx1 = [](long I) -> long {
        /* GATE 253 (LUT3 _1628_ INIT 0x96 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut225.push_back(ctx.genrate_lut(lut225idx1));
    flut225.push_back(lut225idx1);

    auto fvec225 = [flut225](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut225[i](I));
        return ret;
    };

    std::cerr << "\rLUT225   ";
    Ciphertext gin225 = 1 * gout224[0] + 2 * gout113[1] + 4 * gout92[0];
    std::vector<Ciphertext> gout225 = ctx.eval_lut_amortized(&gin225, lut225);

    long gin225clear = 1 * gout224clear[0] + 2 * gout113clear[1] + 4 * gout92clear[0];
    std::vector<long> gout225clear = fvec225(gin225clear);

    assert(ctx.decrypt(&gout225[0]) == gout225clear[0]);
    assert(ctx.decrypt(&gout225[1]) == gout225clear[1]);
    std::vector<RotationPoly> lut226;
    std::vector<long (*)(long)> flut226;
    auto lut226idx0 = [](long I) -> long {
        /* GATE 359 (LUT3 _1734_ INIT 0x71 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut226.push_back(ctx.genrate_lut(lut226idx0));
    flut226.push_back(lut226idx0);

    auto lut226idx1 = [](long I) -> long {
        /* GATE 303 (LUT3 _1678_ INIT 0x69 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut226.push_back(ctx.genrate_lut(lut226idx1));
    flut226.push_back(lut226idx1);

    auto fvec226 = [flut226](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut226[i](I));
        return ret;
    };

    std::cerr << "\rLUT226   ";
    Ciphertext gin226 = 1 * gout165[0] + 2 * gout134[1] + 4 * gout225[0];
    std::vector<Ciphertext> gout226 = ctx.eval_lut_amortized(&gin226, lut226);

    long gin226clear = 1 * gout165clear[0] + 2 * gout134clear[1] + 4 * gout225clear[0];
    std::vector<long> gout226clear = fvec226(gin226clear);

    assert(ctx.decrypt(&gout226[0]) == gout226clear[0]);
    assert(ctx.decrypt(&gout226[1]) == gout226clear[1]);
    std::vector<RotationPoly> lut227;
    std::vector<long (*)(long)> flut227;
    auto lut227idx0 = [](long I) -> long {
        /* GATE 103 (LUT3 _1478_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut227.push_back(ctx.genrate_lut(lut227idx0));
    flut227.push_back(lut227idx0);

    auto lut227idx1 = [](long I) -> long {
        /* GATE 83 (LUT3 _1458_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut227.push_back(ctx.genrate_lut(lut227idx1));
    flut227.push_back(lut227idx1);

    auto fvec227 = [flut227](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut227[i](I));
        return ret;
    };

    std::cerr << "\rLUT227   ";
    Ciphertext gin227 = 1 * gout202[0] + 2 * gout101[0] + 4 * gout83[1];
    std::vector<Ciphertext> gout227 = ctx.eval_lut_amortized(&gin227, lut227);

    long gin227clear = 1 * gout202clear[0] + 2 * gout101clear[0] + 4 * gout83clear[1];
    std::vector<long> gout227clear = fvec227(gin227clear);

    assert(ctx.decrypt(&gout227[0]) == gout227clear[0]);
    assert(ctx.decrypt(&gout227[1]) == gout227clear[1]);
    std::vector<RotationPoly> lut228;
    std::vector<long (*)(long)> flut228;
    auto lut228idx0 = [](long I) -> long {
        /* GATE 130 (LUT3 _1505_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut228.push_back(ctx.genrate_lut(lut228idx0));
    flut228.push_back(lut228idx0);

    auto lut228idx1 = [](long I) -> long {
        /* GATE 102 (LUT3 _1477_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut228.push_back(ctx.genrate_lut(lut228idx1));
    flut228.push_back(lut228idx1);

    auto fvec228 = [flut228](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut228[i](I));
        return ret;
    };

    std::cerr << "\rLUT228   ";
    Ciphertext gin228 = 1 * gout227[0] + 2 * gout208[1] + 4 * gout111[0];
    std::vector<Ciphertext> gout228 = ctx.eval_lut_amortized(&gin228, lut228);

    long gin228clear = 1 * gout227clear[0] + 2 * gout208clear[1] + 4 * gout111clear[0];
    std::vector<long> gout228clear = fvec228(gin228clear);

    assert(ctx.decrypt(&gout228[0]) == gout228clear[0]);
    assert(ctx.decrypt(&gout228[1]) == gout228clear[1]);
    std::vector<RotationPoly> lut229;
    std::vector<long (*)(long)> flut229;
    auto lut229idx0 = [](long I) -> long {
        /* GATE 101 (LUT3 _1476_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut229.push_back(ctx.genrate_lut(lut229idx0));
    flut229.push_back(lut229idx0);

    auto lut229idx1 = [](long I) -> long {
        /* GATE 81 (LUT3 _1456_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut229.push_back(ctx.genrate_lut(lut229idx1));
    flut229.push_back(lut229idx1);

    auto fvec229 = [flut229](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut229[i](I));
        return ret;
    };

    std::cerr << "\rLUT229   ";
    Ciphertext gin229 = 1 * gout203[0] + 2 * gout227[1] + 4 * gout180[1];
    std::vector<Ciphertext> gout229 = ctx.eval_lut_amortized(&gin229, lut229);

    long gin229clear = 1 * gout203clear[0] + 2 * gout227clear[1] + 4 * gout180clear[1];
    std::vector<long> gout229clear = fvec229(gin229clear);

    assert(ctx.decrypt(&gout229[0]) == gout229clear[0]);
    assert(ctx.decrypt(&gout229[1]) == gout229clear[1]);
    std::vector<RotationPoly> lut230;
    std::vector<long (*)(long)> flut230;
    auto lut230idx0 = [](long I) -> long {
        /* GATE 128 (LUT3 _1503_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut230.push_back(ctx.genrate_lut(lut230idx0));
    flut230.push_back(lut230idx0);

    auto lut230idx1 = [](long I) -> long {
        /* GATE 100 (LUT3 _1475_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut230.push_back(ctx.genrate_lut(lut230idx1));
    flut230.push_back(lut230idx1);

    auto fvec230 = [flut230](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut230[i](I));
        return ret;
    };

    std::cerr << "\rLUT230   ";
    Ciphertext gin230 = 1 * gout229[0] + 2 * gout228[1] + 4 * gout180[0];
    std::vector<Ciphertext> gout230 = ctx.eval_lut_amortized(&gin230, lut230);

    long gin230clear = 1 * gout229clear[0] + 2 * gout228clear[1] + 4 * gout180clear[0];
    std::vector<long> gout230clear = fvec230(gin230clear);

    assert(ctx.decrypt(&gout230[0]) == gout230clear[0]);
    assert(ctx.decrypt(&gout230[1]) == gout230clear[1]);
    std::vector<RotationPoly> lut231;
    std::vector<long (*)(long)> flut231;
    auto lut231idx0 = [](long I) -> long {
        /* GATE 99 (LUT2 _1474_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut231.push_back(ctx.genrate_lut(lut231idx0));
    flut231.push_back(lut231idx0);

    auto lut231idx1 = [](long I) -> long {
        /* GATE 79 (LUT2 _1454_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut231.push_back(ctx.genrate_lut(lut231idx1));
    flut231.push_back(lut231idx1);

    auto fvec231 = [flut231](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut231[i](I));
        return ret;
    };

    std::cerr << "\rLUT231   ";
    Ciphertext gin231 = 1 * gout210[0] + 2 * gout229[1];
    std::vector<Ciphertext> gout231 = ctx.eval_lut_amortized(&gin231, lut231);

    long gin231clear = 1 * gout210clear[0] + 2 * gout229clear[1];
    std::vector<long> gout231clear = fvec231(gin231clear);

    assert(ctx.decrypt(&gout231[0]) == gout231clear[0]);
    assert(ctx.decrypt(&gout231[1]) == gout231clear[1]);
    std::vector<RotationPoly> lut232;
    std::vector<long (*)(long)> flut232;
    auto lut232idx0 = [](long I) -> long {
        /* GATE 126 (LUT2 _1501_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut232.push_back(ctx.genrate_lut(lut232idx0));
    flut232.push_back(lut232idx0);

    auto lut232idx1 = [](long I) -> long {
        /* GATE 98 (LUT2 _1473_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut232.push_back(ctx.genrate_lut(lut232idx1));
    flut232.push_back(lut232idx1);

    auto fvec232 = [flut232](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut232[i](I));
        return ret;
    };

    std::cerr << "\rLUT232   ";
    Ciphertext gin232 = 1 * gout231[0] + 2 * gout230[1];
    std::vector<Ciphertext> gout232 = ctx.eval_lut_amortized(&gin232, lut232);

    long gin232clear = 1 * gout231clear[0] + 2 * gout230clear[1];
    std::vector<long> gout232clear = fvec232(gin232clear);

    assert(ctx.decrypt(&gout232[0]) == gout232clear[0]);
    assert(ctx.decrypt(&gout232[1]) == gout232clear[1]);
    std::vector<RotationPoly> lut233;
    std::vector<long (*)(long)> flut233;
    auto lut233idx0 = [](long I) -> long {
        /* GATE 56 (LUT2 _1431_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut233.push_back(ctx.genrate_lut(lut233idx0));
    flut233.push_back(lut233idx0);

    auto lut233idx1 = [](long I) -> long {
        /* GATE 40 (LUT2 _1415_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut233.push_back(ctx.genrate_lut(lut233idx1));
    flut233.push_back(lut233idx1);

    auto fvec233 = [flut233](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut233[i](I));
        return ret;
    };

    std::cerr << "\rLUT233   ";
    Ciphertext gin233 = 1 * gout174[0] + 2 * gout150[1];
    std::vector<Ciphertext> gout233 = ctx.eval_lut_amortized(&gin233, lut233);

    long gin233clear = 1 * gout174clear[0] + 2 * gout150clear[1];
    std::vector<long> gout233clear = fvec233(gin233clear);

    assert(ctx.decrypt(&gout233[0]) == gout233clear[0]);
    assert(ctx.decrypt(&gout233[1]) == gout233clear[1]);
    std::vector<RotationPoly> lut234;
    std::vector<long (*)(long)> flut234;
    auto lut234idx0 = [](long I) -> long {
        /* GATE 78 (LUT2 _1453_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut234.push_back(ctx.genrate_lut(lut234idx0));
    flut234.push_back(lut234idx0);

    auto lut234idx1 = [](long I) -> long {
        /* GATE 55 (LUT2 _1430_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut234.push_back(ctx.genrate_lut(lut234idx1));
    flut234.push_back(lut234idx1);

    auto fvec234 = [flut234](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut234[i](I));
        return ret;
    };

    std::cerr << "\rLUT234   ";
    Ciphertext gin234 = 1 * gout233[0] + 2 * gout210[1];
    std::vector<Ciphertext> gout234 = ctx.eval_lut_amortized(&gin234, lut234);

    long gin234clear = 1 * gout233clear[0] + 2 * gout210clear[1];
    std::vector<long> gout234clear = fvec234(gin234clear);

    assert(ctx.decrypt(&gout234[0]) == gout234clear[0]);
    assert(ctx.decrypt(&gout234[1]) == gout234clear[1]);
    std::vector<RotationPoly> lut235;
    std::vector<long (*)(long)> flut235;
    auto lut235idx0 = [](long I) -> long {
        /* GATE 97 (LUT2 _1472_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut235.push_back(ctx.genrate_lut(lut235idx0));
    flut235.push_back(lut235idx0);

    auto lut235idx1 = [](long I) -> long {
        /* GATE 77 (LUT2 _1452_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut235.push_back(ctx.genrate_lut(lut235idx1));
    flut235.push_back(lut235idx1);

    auto fvec235 = [flut235](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut235[i](I));
        return ret;
    };

    std::cerr << "\rLUT235   ";
    Ciphertext gin235 = 1 * gout234[0] + 2 * gout231[1];
    std::vector<Ciphertext> gout235 = ctx.eval_lut_amortized(&gin235, lut235);

    long gin235clear = 1 * gout234clear[0] + 2 * gout231clear[1];
    std::vector<long> gout235clear = fvec235(gin235clear);

    assert(ctx.decrypt(&gout235[0]) == gout235clear[0]);
    assert(ctx.decrypt(&gout235[1]) == gout235clear[1]);
    std::vector<RotationPoly> lut236;
    std::vector<long (*)(long)> flut236;
    auto lut236idx0 = [](long I) -> long {
        /* GATE 124 (LUT2 _1499_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut236.push_back(ctx.genrate_lut(lut236idx0));
    flut236.push_back(lut236idx0);

    auto fvec236 = [flut236](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut236[i](I));
        return ret;
    };

    std::cerr << "\rLUT236   ";
    Ciphertext gin236 = 1 * gout235[0] + 2 * gout232[1];
    std::vector<Ciphertext> gout236 = ctx.eval_lut_amortized(&gin236, lut236);

    long gin236clear = 1 * gout235clear[0] + 2 * gout232clear[1];
    std::vector<long> gout236clear = fvec236(gin236clear);

    assert(ctx.decrypt(&gout236[0]) == gout236clear[0]);
    std::vector<RotationPoly> lut237;
    std::vector<long (*)(long)> flut237;
    auto lut237idx0 = [](long I) -> long {
        /* GATE 54 (LUT2 _1429_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut237.push_back(ctx.genrate_lut(lut237idx0));
    flut237.push_back(lut237idx0);

    auto fvec237 = [flut237](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut237[i](I));
        return ret;
    };

    std::cerr << "\rLUT237   ";
    Ciphertext gin237 = 1 * gout189[0] + 2 * gout233[1];
    std::vector<Ciphertext> gout237 = ctx.eval_lut_amortized(&gin237, lut237);

    long gin237clear = 1 * gout189clear[0] + 2 * gout233clear[1];
    std::vector<long> gout237clear = fvec237(gin237clear);

    assert(ctx.decrypt(&gout237[0]) == gout237clear[0]);
    std::vector<RotationPoly> lut238;
    std::vector<long (*)(long)> flut238;
    auto lut238idx0 = [](long I) -> long {
        /* GATE 76 (LUT2 _1451_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut238.push_back(ctx.genrate_lut(lut238idx0));
    flut238.push_back(lut238idx0);

    auto fvec238 = [flut238](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut238[i](I));
        return ret;
    };

    std::cerr << "\rLUT238   ";
    Ciphertext gin238 = 1 * gout237[0] + 2 * gout234[1];
    std::vector<Ciphertext> gout238 = ctx.eval_lut_amortized(&gin238, lut238);

    long gin238clear = 1 * gout237clear[0] + 2 * gout234clear[1];
    std::vector<long> gout238clear = fvec238(gin238clear);

    assert(ctx.decrypt(&gout238[0]) == gout238clear[0]);
    std::vector<RotationPoly> lut239;
    std::vector<long (*)(long)> flut239;
    auto lut239idx0 = [](long I) -> long {
        /* GATE 460 (LUT3 _1835_ INIT 0x7 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut239.push_back(ctx.genrate_lut(lut239idx0));
    flut239.push_back(lut239idx0);

    auto fvec239 = [flut239](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut239[i](I));
        return ret;
    };

    std::cerr << "\rLUT239   ";
    Ciphertext gin239 = 1 * gout235[1] + 2 * gout238[0] + 4 * gout235[0];
    std::vector<Ciphertext> gout239 = ctx.eval_lut_amortized(&gin239, lut239);

    long gin239clear = 1 * gout235clear[1] + 2 * gout238clear[0] + 4 * gout235clear[0];
    std::vector<long> gout239clear = fvec239(gin239clear);

    assert(ctx.decrypt(&gout239[0]) == gout239clear[0]);
    std::vector<RotationPoly> lut240;
    std::vector<long (*)(long)> flut240;
    auto lut240idx0 = [](long I) -> long {
        /* GATE 461 (LUT2 _1836_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut240.push_back(ctx.genrate_lut(lut240idx0));
    flut240.push_back(lut240idx0);

    auto fvec240 = [flut240](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut240[i](I));
        return ret;
    };

    std::cerr << "\rLUT240   ";
    Ciphertext gin240 = 1 * gout239[0] + 2 * gout232[1];
    std::vector<Ciphertext> gout240 = ctx.eval_lut_amortized(&gin240, lut240);

    long gin240clear = 1 * gout239clear[0] + 2 * gout232clear[1];
    std::vector<long> gout240clear = fvec240(gin240clear);

    assert(ctx.decrypt(&gout240[0]) == gout240clear[0]);
    std::vector<RotationPoly> lut241;
    std::vector<long (*)(long)> flut241;
    auto lut241idx0 = [](long I) -> long {
        /* GATE 119 (LUT3 _1494_ INIT 0x80 PERM 102) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut241.push_back(ctx.genrate_lut(lut241idx0));
    flut241.push_back(lut241idx0);

    auto fvec241 = [flut241](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut241[i](I));
        return ret;
    };

    std::cerr << "\rLUT241   ";
    Ciphertext gin241 = 1 * gout235[1] + 2 * gout238[0] + 4 * gout232[1];
    std::vector<Ciphertext> gout241 = ctx.eval_lut_amortized(&gin241, lut241);

    long gin241clear = 1 * gout235clear[1] + 2 * gout238clear[0] + 4 * gout232clear[1];
    std::vector<long> gout241clear = fvec241(gin241clear);

    assert(ctx.decrypt(&gout241[0]) == gout241clear[0]);
    std::vector<RotationPoly> lut242;
    std::vector<long (*)(long)> flut242;
    auto lut242idx0 = [](long I) -> long {
        /* GATE 176 (LUT2 _1551_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut242.push_back(ctx.genrate_lut(lut242idx0));
    flut242.push_back(lut242idx0);

    auto fvec242 = [flut242](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut242[i](I));
        return ret;
    };

    std::cerr << "\rLUT242   ";
    Ciphertext gin242 = 1 * ct_x4 + 2 * ct_y5;
    std::vector<Ciphertext> gout242 = ctx.eval_lut_amortized(&gin242, lut242);

    long gin242clear = 1 * ct_x4clear + 2 * ct_y5clear;
    std::vector<long> gout242clear = fvec242(gin242clear);

    assert(ctx.decrypt(&gout242[0]) == gout242clear[0]);
    std::vector<RotationPoly> lut243;
    std::vector<long (*)(long)> flut243;
    auto lut243idx0 = [](long I) -> long {
        /* GATE 163 (LUT3 _1538_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut243.push_back(ctx.genrate_lut(lut243idx0));
    flut243.push_back(lut243idx0);

    auto lut243idx1 = [](long I) -> long {
        /* GATE 129 (LUT3 _1504_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut243.push_back(ctx.genrate_lut(lut243idx1));
    flut243.push_back(lut243idx1);

    auto fvec243 = [flut243](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut243[i](I));
        return ret;
    };

    std::cerr << "\rLUT243   ";
    Ciphertext gin243 = 1 * gout228[0] + 2 * gout221[1] + 4 * gout111[1];
    std::vector<Ciphertext> gout243 = ctx.eval_lut_amortized(&gin243, lut243);

    long gin243clear = 1 * gout228clear[0] + 2 * gout221clear[1] + 4 * gout111clear[1];
    std::vector<long> gout243clear = fvec243(gin243clear);

    assert(ctx.decrypt(&gout243[0]) == gout243clear[0]);
    assert(ctx.decrypt(&gout243[1]) == gout243clear[1]);
    std::vector<RotationPoly> lut244;
    std::vector<long (*)(long)> flut244;
    auto lut244idx0 = [](long I) -> long {
        /* GATE 161 (LUT2 _1536_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut244.push_back(ctx.genrate_lut(lut244idx0));
    flut244.push_back(lut244idx0);

    auto lut244idx1 = [](long I) -> long {
        /* GATE 127 (LUT2 _1502_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut244.push_back(ctx.genrate_lut(lut244idx1));
    flut244.push_back(lut244idx1);

    auto fvec244 = [flut244](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut244[i](I));
        return ret;
    };

    std::cerr << "\rLUT244   ";
    Ciphertext gin244 = 1 * gout230[0] + 2 * gout243[1];
    std::vector<Ciphertext> gout244 = ctx.eval_lut_amortized(&gin244, lut244);

    long gin244clear = 1 * gout230clear[0] + 2 * gout243clear[1];
    std::vector<long> gout244clear = fvec244(gin244clear);

    assert(ctx.decrypt(&gout244[0]) == gout244clear[0]);
    assert(ctx.decrypt(&gout244[1]) == gout244clear[1]);
    std::vector<RotationPoly> lut245;
    std::vector<long (*)(long)> flut245;
    auto lut245idx0 = [](long I) -> long {
        /* GATE 159 (LUT2 _1534_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut245.push_back(ctx.genrate_lut(lut245idx0));
    flut245.push_back(lut245idx0);

    auto lut245idx1 = [](long I) -> long {
        /* GATE 125 (LUT2 _1500_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut245.push_back(ctx.genrate_lut(lut245idx1));
    flut245.push_back(lut245idx1);

    auto fvec245 = [flut245](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut245[i](I));
        return ret;
    };

    std::cerr << "\rLUT245   ";
    Ciphertext gin245 = 1 * gout232[0] + 2 * gout244[1];
    std::vector<Ciphertext> gout245 = ctx.eval_lut_amortized(&gin245, lut245);

    long gin245clear = 1 * gout232clear[0] + 2 * gout244clear[1];
    std::vector<long> gout245clear = fvec245(gin245clear);

    assert(ctx.decrypt(&gout245[0]) == gout245clear[0]);
    assert(ctx.decrypt(&gout245[1]) == gout245clear[1]);
    std::vector<RotationPoly> lut246;
    std::vector<long (*)(long)> flut246;
    auto lut246idx0 = [](long I) -> long {
        /* GATE 157 (LUT2 _1532_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut246.push_back(ctx.genrate_lut(lut246idx0));
    flut246.push_back(lut246idx0);

    auto fvec246 = [flut246](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut246[i](I));
        return ret;
    };

    std::cerr << "\rLUT246   ";
    Ciphertext gin246 = 1 * gout245[1] + 2 * gout241[0];
    std::vector<Ciphertext> gout246 = ctx.eval_lut_amortized(&gin246, lut246);

    long gin246clear = 1 * gout245clear[1] + 2 * gout241clear[0];
    std::vector<long> gout246clear = fvec246(gin246clear);

    assert(ctx.decrypt(&gout246[0]) == gout246clear[0]);
    std::vector<RotationPoly> lut247;
    std::vector<long (*)(long)> flut247;
    auto lut247idx0 = [](long I) -> long {
        /* GATE 156 (LUT2 _1531_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut247.push_back(ctx.genrate_lut(lut247idx0));
    flut247.push_back(lut247idx0);

    auto lut247idx1 = [](long I) -> long {
        /* GATE 123 (LUT2 _1498_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut247.push_back(ctx.genrate_lut(lut247idx1));
    flut247.push_back(lut247idx1);

    auto fvec247 = [flut247](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut247[i](I));
        return ret;
    };

    std::cerr << "\rLUT247   ";
    Ciphertext gin247 = 1 * gout236[0] + 2 * gout245[1];
    std::vector<Ciphertext> gout247 = ctx.eval_lut_amortized(&gin247, lut247);

    long gin247clear = 1 * gout236clear[0] + 2 * gout245clear[1];
    std::vector<long> gout247clear = fvec247(gin247clear);

    assert(ctx.decrypt(&gout247[0]) == gout247clear[0]);
    assert(ctx.decrypt(&gout247[1]) == gout247clear[1]);
    std::vector<RotationPoly> lut248;
    std::vector<long (*)(long)> flut248;
    auto lut248idx0 = [](long I) -> long {
        /* GATE 155 (LUT2 _1530_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut248.push_back(ctx.genrate_lut(lut248idx0));
    flut248.push_back(lut248idx0);

    auto fvec248 = [flut248](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut248[i](I));
        return ret;
    };

    std::cerr << "\rLUT248   ";
    Ciphertext gin248 = 1 * gout247[0] + 2 * gout246[0];
    std::vector<Ciphertext> gout248 = ctx.eval_lut_amortized(&gin248, lut248);

    long gin248clear = 1 * gout247clear[0] + 2 * gout246clear[0];
    std::vector<long> gout248clear = fvec248(gin248clear);

    assert(ctx.decrypt(&gout248[0]) == gout248clear[0]);
    std::vector<RotationPoly> lut249;
    std::vector<long (*)(long)> flut249;
    auto lut249idx0 = [](long I) -> long {
        /* GATE 6 (LUT2 _1381_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut249.push_back(ctx.genrate_lut(lut249idx0));
    flut249.push_back(lut249idx0);

    auto fvec249 = [flut249](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut249[i](I));
        return ret;
    };

    std::cerr << "\rLUT249   ";
    Ciphertext gin249 = 1 * ct_op0 + 2 * gout67[0];
    std::vector<Ciphertext> gout249 = ctx.eval_lut_amortized(&gin249, lut249);

    long gin249clear = 1 * ct_op0clear + 2 * gout67clear[0];
    std::vector<long> gout249clear = fvec249(gin249clear);

    assert(ctx.decrypt(&gout249[0]) == gout249clear[0]);
    std::vector<RotationPoly> lut250;
    std::vector<long (*)(long)> flut250;
    auto lut250idx0 = [](long I) -> long {
        /* GATE 122 (LUT3 _1497_ INIT 0x60 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut250.push_back(ctx.genrate_lut(lut250idx0));
    flut250.push_back(lut250idx0);

    auto fvec250 = [flut250](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut250[i](I));
        return ret;
    };

    std::cerr << "\rLUT250   ";
    Ciphertext gin250 = 1 * gout247[1] + 2 * gout241[0] + 4 * gout249[0];
    std::vector<Ciphertext> gout250 = ctx.eval_lut_amortized(&gin250, lut250);

    long gin250clear = 1 * gout247clear[1] + 2 * gout241clear[0] + 4 * gout249clear[0];
    std::vector<long> gout250clear = fvec250(gin250clear);

    assert(ctx.decrypt(&gout250[0]) == gout250clear[0]);
    std::vector<RotationPoly> lut251;
    std::vector<long (*)(long)> flut251;
    auto lut251idx0 = [](long I) -> long {
        /* GATE 75 (LUT3 _1450_ INIT 0x60 PERM 102) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut251.push_back(ctx.genrate_lut(lut251idx0));
    flut251.push_back(lut251idx0);

    auto fvec251 = [flut251](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut251[i](I));
        return ret;
    };

    std::cerr << "\rLUT251   ";
    Ciphertext gin251 = 1 * gout235[1] + 2 * gout238[0] + 4 * gout249[0];
    std::vector<Ciphertext> gout251 = ctx.eval_lut_amortized(&gin251, lut251);

    long gin251clear = 1 * gout235clear[1] + 2 * gout238clear[0] + 4 * gout249clear[0];
    std::vector<long> gout251clear = fvec251(gin251clear);

    assert(ctx.decrypt(&gout251[0]) == gout251clear[0]);
    std::vector<RotationPoly> lut252;
    std::vector<long (*)(long)> flut252;
    auto lut252idx0 = [](long I) -> long {
        /* GATE 53 (LUT3 _1428_ INIT 0x60 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut252.push_back(ctx.genrate_lut(lut252idx0));
    flut252.push_back(lut252idx0);

    auto fvec252 = [flut252](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut252[i](I));
        return ret;
    };

    std::cerr << "\rLUT252   ";
    Ciphertext gin252 = 1 * gout237[0] + 2 * gout234[1] + 4 * gout249[0];
    std::vector<Ciphertext> gout252 = ctx.eval_lut_amortized(&gin252, lut252);

    long gin252clear = 1 * gout237clear[0] + 2 * gout234clear[1] + 4 * gout249clear[0];
    std::vector<long> gout252clear = fvec252(gin252clear);

    assert(ctx.decrypt(&gout252[0]) == gout252clear[0]);
    std::vector<RotationPoly> lut253;
    std::vector<long (*)(long)> flut253;
    auto lut253idx0 = [](long I) -> long {
        /* GATE 38 (LUT3 _1413_ INIT 0x60 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut253.push_back(ctx.genrate_lut(lut253idx0));
    flut253.push_back(lut253idx0);

    auto fvec253 = [flut253](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut253[i](I));
        return ret;
    };

    std::cerr << "\rLUT253   ";
    Ciphertext gin253 = 1 * gout189[0] + 2 * gout233[1] + 4 * gout249[0];
    std::vector<Ciphertext> gout253 = ctx.eval_lut_amortized(&gin253, lut253);

    long gin253clear = 1 * gout189clear[0] + 2 * gout233clear[1] + 4 * gout249clear[0];
    std::vector<long> gout253clear = fvec253(gin253clear);

    assert(ctx.decrypt(&gout253[0]) == gout253clear[0]);
    std::vector<RotationPoly> lut254;
    std::vector<long (*)(long)> flut254;
    auto lut254idx0 = [](long I) -> long {
        /* GATE 35 (LUT2 _1410_ INIT 0x1 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut254.push_back(ctx.genrate_lut(lut254idx0));
    flut254.push_back(lut254idx0);

    auto fvec254 = [flut254](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut254[i](I));
        return ret;
    };

    std::cerr << "\rLUT254   ";
    Ciphertext gin254 = 1 * gout163[0] + 2 * gout249[0];
    std::vector<Ciphertext> gout254 = ctx.eval_lut_amortized(&gin254, lut254);

    long gin254clear = 1 * gout163clear[0] + 2 * gout249clear[0];
    std::vector<long> gout254clear = fvec254(gin254clear);

    assert(ctx.decrypt(&gout254[0]) == gout254clear[0]);
    std::vector<RotationPoly> lut255;
    std::vector<long (*)(long)> flut255;
    auto lut255idx0 = [](long I) -> long {
        /* GATE 26 (LUT3 _1401_ INIT 0x60 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut255.push_back(ctx.genrate_lut(lut255idx0));
    flut255.push_back(lut255idx0);

    auto fvec255 = [flut255](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut255[i](I));
        return ret;
    };

    std::cerr << "\rLUT255   ";
    Ciphertext gin255 = 1 * gout188[0] + 2 * gout174[1] + 4 * gout249[0];
    std::vector<Ciphertext> gout255 = ctx.eval_lut_amortized(&gin255, lut255);

    long gin255clear = 1 * gout188clear[0] + 2 * gout174clear[1] + 4 * gout249clear[0];
    std::vector<long> gout255clear = fvec255(gin255clear);

    assert(ctx.decrypt(&gout255[0]) == gout255clear[0]);
    std::vector<RotationPoly> lut256;
    std::vector<long (*)(long)> flut256;
    auto lut256idx0 = [](long I) -> long {
        /* GATE 25 (LUT3 _1400_ INIT 0xfe PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut256.push_back(ctx.genrate_lut(lut256idx0));
    flut256.push_back(lut256idx0);

    auto fvec256 = [flut256](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut256[i](I));
        return ret;
    };

    std::cerr << "\rLUT256   ";
    Ciphertext gin256 = 1 * gout255[0] + 2 * gout254[0] + 4 * gout131[0];
    std::vector<Ciphertext> gout256 = ctx.eval_lut_amortized(&gin256, lut256);

    long gin256clear = 1 * gout255clear[0] + 2 * gout254clear[0] + 4 * gout131clear[0];
    std::vector<long> gout256clear = fvec256(gin256clear);

    assert(ctx.decrypt(&gout256[0]) == gout256clear[0]);
    std::vector<RotationPoly> lut257;
    std::vector<long (*)(long)> flut257;
    auto lut257idx0 = [](long I) -> long {
        /* GATE 23 (LUT2 _1398_ INIT 0x1 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut257.push_back(ctx.genrate_lut(lut257idx0));
    flut257.push_back(lut257idx0);

    auto fvec257 = [flut257](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut257[i](I));
        return ret;
    };

    std::cerr << "\rLUT257   ";
    Ciphertext gin257 = 1 * gout130[0] + 2 * gout249[0];
    std::vector<Ciphertext> gout257 = ctx.eval_lut_amortized(&gin257, lut257);

    long gin257clear = 1 * gout130clear[0] + 2 * gout249clear[0];
    std::vector<long> gout257clear = fvec257(gin257clear);

    assert(ctx.decrypt(&gout257[0]) == gout257clear[0]);
    std::vector<RotationPoly> lut258;
    std::vector<long (*)(long)> flut258;
    auto lut258idx0 = [](long I) -> long {
        /* GATE 17 (LUT3 _1392_ INIT 0x60 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut258.push_back(ctx.genrate_lut(lut258idx0));
    flut258.push_back(lut258idx0);

    auto fvec258 = [flut258](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut258[i](I));
        return ret;
    };

    std::cerr << "\rLUT258   ";
    Ciphertext gin258 = 1 * gout187[0] + 2 * gout173[1] + 4 * gout249[0];
    std::vector<Ciphertext> gout258 = ctx.eval_lut_amortized(&gin258, lut258);

    long gin258clear = 1 * gout187clear[0] + 2 * gout173clear[1] + 4 * gout249clear[0];
    std::vector<long> gout258clear = fvec258(gin258clear);

    assert(ctx.decrypt(&gout258[0]) == gout258clear[0]);
    std::vector<RotationPoly> lut259;
    std::vector<long (*)(long)> flut259;
    auto lut259idx0 = [](long I) -> long {
        /* GATE 16 (LUT3 _1391_ INIT 0xfe PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut259.push_back(ctx.genrate_lut(lut259idx0));
    flut259.push_back(lut259idx0);

    auto fvec259 = [flut259](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut259[i](I));
        return ret;
    };

    std::cerr << "\rLUT259   ";
    Ciphertext gin259 = 1 * gout258[0] + 2 * gout257[0] + 4 * gout131[0];
    std::vector<Ciphertext> gout259 = ctx.eval_lut_amortized(&gin259, lut259);

    long gin259clear = 1 * gout258clear[0] + 2 * gout257clear[0] + 4 * gout131clear[0];
    std::vector<long> gout259clear = fvec259(gin259clear);

    assert(ctx.decrypt(&gout259[0]) == gout259clear[0]);
    std::vector<RotationPoly> lut260;
    std::vector<long (*)(long)> flut260;
    auto lut260idx0 = [](long I) -> long {
        /* GATE 12 (LUT3 _1387_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut260.push_back(ctx.genrate_lut(lut260idx0));
    flut260.push_back(lut260idx0);

    auto fvec260 = [flut260](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut260[i](I));
        return ret;
    };

    std::cerr << "\rLUT260   ";
    Ciphertext gin260 = 1 * gout154[0] + 2 * gout187[1] + 4 * gout249[0];
    std::vector<Ciphertext> gout260 = ctx.eval_lut_amortized(&gin260, lut260);

    long gin260clear = 1 * gout154clear[0] + 2 * gout187clear[1] + 4 * gout249clear[0];
    std::vector<long> gout260clear = fvec260(gin260clear);

    assert(ctx.decrypt(&gout260[0]) == gout260clear[0]);
    std::vector<RotationPoly> lut261;
    std::vector<long (*)(long)> flut261;
    auto lut261idx0 = [](long I) -> long {
        /* GATE 11 (LUT2 _1386_ INIT 0xe PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut261.push_back(ctx.genrate_lut(lut261idx0));
    flut261.push_back(lut261idx0);

    auto fvec261 = [flut261](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut261[i](I));
        return ret;
    };

    std::cerr << "\rLUT261   ";
    Ciphertext gin261 = 1 * gout260[0] + 2 * gout131[0];
    std::vector<Ciphertext> gout261 = ctx.eval_lut_amortized(&gin261, lut261);

    long gin261clear = 1 * gout260clear[0] + 2 * gout131clear[0];
    std::vector<long> gout261clear = fvec261(gin261clear);

    assert(ctx.decrypt(&gout261[0]) == gout261clear[0]);
    std::vector<RotationPoly> lut262;
    std::vector<long (*)(long)> flut262;
    auto lut262idx0 = [](long I) -> long {
        /* GATE 9 (LUT3 _1384_ INIT 0x80 PERM 201) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut262.push_back(ctx.genrate_lut(lut262idx0));
    flut262.push_back(lut262idx0);

    auto fvec262 = [flut262](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut262[i](I));
        return ret;
    };

    std::cerr << "\rLUT262   ";
    Ciphertext gin262 = 1 * ct_x0 + 2 * ct_y0 + 4 * gout249[0];
    std::vector<Ciphertext> gout262 = ctx.eval_lut_amortized(&gin262, lut262);

    long gin262clear = 1 * ct_x0clear + 2 * ct_y0clear + 4 * gout249clear[0];
    std::vector<long> gout262clear = fvec262(gin262clear);

    assert(ctx.decrypt(&gout262[0]) == gout262clear[0]);
    std::vector<RotationPoly> lut263;
    std::vector<long (*)(long)> flut263;
    auto lut263idx0 = [](long I) -> long {
        /* GATE 2 (LUT2 _1377_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut263.push_back(ctx.genrate_lut(lut263idx0));
    flut263.push_back(lut263idx0);

    auto fvec263 = [flut263](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut263[i](I));
        return ret;
    };

    std::cerr << "\rLUT263   ";
    Ciphertext gin263 = 1 * gout178[0] + 2 * gout249[0];
    std::vector<Ciphertext> gout263 = ctx.eval_lut_amortized(&gin263, lut263);

    long gin263clear = 1 * gout178clear[0] + 2 * gout249clear[0];
    std::vector<long> gout263clear = fvec263(gin263clear);

    assert(ctx.decrypt(&gout263[0]) == gout263clear[0]);
    std::vector<RotationPoly> lut264;
    std::vector<long (*)(long)> flut264;
    auto lut264idx0 = [](long I) -> long {
        /* GATE 1 (LUT3 _1376_ INIT 0xfe PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut264.push_back(ctx.genrate_lut(lut264idx0));
    flut264.push_back(lut264idx0);

    auto fvec264 = [flut264](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut264[i](I));
        return ret;
    };

    std::cerr << "\rLUT264   ";
    Ciphertext gin264 = 1 * gout263[0] + 2 * gout262[0] + 4 * gout131[0];
    std::vector<Ciphertext> gout264 = ctx.eval_lut_amortized(&gin264, lut264);

    long gin264clear = 1 * gout263clear[0] + 2 * gout262clear[0] + 4 * gout131clear[0];
    std::vector<long> gout264clear = fvec264(gin264clear);

    assert(ctx.decrypt(&gout264[0]) == gout264clear[0]);
    std::vector<RotationPoly> lut265;
    std::vector<long (*)(long)> flut265;
    auto lut265idx0 = [](long I) -> long {
        /* GATE 252 (LUT2 _1627_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut265.push_back(ctx.genrate_lut(lut265idx0));
    flut265.push_back(lut265idx0);

    auto fvec265 = [flut265](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut265[i](I));
        return ret;
    };

    std::cerr << "\rLUT265   ";
    Ciphertext gin265 = 1 * ct_x8 + 2 * ct_y3;
    std::vector<Ciphertext> gout265 = ctx.eval_lut_amortized(&gin265, lut265);

    long gin265clear = 1 * ct_x8clear + 2 * ct_y3clear;
    std::vector<long> gout265clear = fvec265(gin265clear);

    assert(ctx.decrypt(&gout265[0]) == gout265clear[0]);
    std::vector<RotationPoly> lut266;
    std::vector<long (*)(long)> flut266;
    auto lut266idx0 = [](long I) -> long {
        /* GATE 298 (LUT3 _1673_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut266.push_back(ctx.genrate_lut(lut266idx0));
    flut266.push_back(lut266idx0);

    auto lut266idx1 = [](long I) -> long {
        /* GATE 249 (LUT3 _1624_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut266.push_back(ctx.genrate_lut(lut266idx1));
    flut266.push_back(lut266idx1);

    auto fvec266 = [flut266](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut266[i](I));
        return ret;
    };

    std::cerr << "\rLUT266   ";
    Ciphertext gin266 = 1 * gout211[0] + 2 * gout22[0] + 4 * gout265[0];
    std::vector<Ciphertext> gout266 = ctx.eval_lut_amortized(&gin266, lut266);

    long gin266clear = 1 * gout211clear[0] + 2 * gout22clear[0] + 4 * gout265clear[0];
    std::vector<long> gout266clear = fvec266(gin266clear);

    assert(ctx.decrypt(&gout266[0]) == gout266clear[0]);
    assert(ctx.decrypt(&gout266[1]) == gout266clear[1]);
    std::vector<RotationPoly> lut267;
    std::vector<long (*)(long)> flut267;
    auto lut267idx0 = [](long I) -> long {
        /* GATE 350 (LUT3 _1725_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut267.push_back(ctx.genrate_lut(lut267idx0));
    flut267.push_back(lut267idx0);

    auto lut267idx1 = [](long I) -> long {
        /* GATE 296 (LUT3 _1671_ INIT 0x96 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut267.push_back(ctx.genrate_lut(lut267idx1));
    flut267.push_back(lut267idx1);

    auto fvec267 = [flut267](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut267[i](I));
        return ret;
    };

    std::cerr << "\rLUT267   ";
    Ciphertext gin267 = 1 * gout113[0] + 2 * gout161[1] + 4 * gout266[0];
    std::vector<Ciphertext> gout267 = ctx.eval_lut_amortized(&gin267, lut267);

    long gin267clear = 1 * gout113clear[0] + 2 * gout161clear[1] + 4 * gout266clear[0];
    std::vector<long> gout267clear = fvec267(gin267clear);

    assert(ctx.decrypt(&gout267[0]) == gout267clear[0]);
    assert(ctx.decrypt(&gout267[1]) == gout267clear[1]);
    std::vector<RotationPoly> lut268;
    std::vector<long (*)(long)> flut268;
    auto lut268idx0 = [](long I) -> long {
        /* GATE 403 (LUT3 _1778_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut268.push_back(ctx.genrate_lut(lut268idx0));
    flut268.push_back(lut268idx0);

    auto lut268idx1 = [](long I) -> long {
        /* GATE 348 (LUT3 _1723_ INIT 0x96 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut268.push_back(ctx.genrate_lut(lut268idx1));
    flut268.push_back(lut268idx1);

    auto fvec268 = [flut268](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut268[i](I));
        return ret;
    };

    std::cerr << "\rLUT268   ";
    Ciphertext gin268 = 1 * gout134[0] + 2 * gout169[1] + 4 * gout267[0];
    std::vector<Ciphertext> gout268 = ctx.eval_lut_amortized(&gin268, lut268);

    long gin268clear = 1 * gout134clear[0] + 2 * gout169clear[1] + 4 * gout267clear[0];
    std::vector<long> gout268clear = fvec268(gin268clear);

    assert(ctx.decrypt(&gout268[0]) == gout268clear[0]);
    assert(ctx.decrypt(&gout268[1]) == gout268clear[1]);
    std::vector<RotationPoly> lut269;
    std::vector<long (*)(long)> flut269;
    auto lut269idx0 = [](long I) -> long {
        /* GATE 457 (LUT2 _1832_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut269.push_back(ctx.genrate_lut(lut269idx0));
    flut269.push_back(lut269idx0);

    auto lut269idx1 = [](long I) -> long {
        /* GATE 402 (LUT2 _1777_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut269.push_back(ctx.genrate_lut(lut269idx1));
    flut269.push_back(lut269idx1);

    auto fvec269 = [flut269](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut269[i](I));
        return ret;
    };

    std::cerr << "\rLUT269   ";
    Ciphertext gin269 = 1 * gout268[0] + 2 * gout116[0];
    std::vector<Ciphertext> gout269 = ctx.eval_lut_amortized(&gin269, lut269);

    long gin269clear = 1 * gout268clear[0] + 2 * gout116clear[0];
    std::vector<long> gout269clear = fvec269(gin269clear);

    assert(ctx.decrypt(&gout269[0]) == gout269clear[0]);
    assert(ctx.decrypt(&gout269[1]) == gout269clear[1]);
    std::vector<RotationPoly> lut270;
    std::vector<long (*)(long)> flut270;
    auto lut270idx0 = [](long I) -> long {
        /* GATE 285 (LUT3 _1660_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut270.push_back(ctx.genrate_lut(lut270idx0));
    flut270.push_back(lut270idx0);

    auto lut270idx1 = [](long I) -> long {
        /* GATE 243 (LUT3 _1618_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut270.push_back(ctx.genrate_lut(lut270idx1));
    flut270.push_back(lut270idx1);

    auto fvec270 = [flut270](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut270[i](I));
        return ret;
    };

    std::cerr << "\rLUT270   ";
    Ciphertext gin270 = 1 * gout86[0] + 2 * gout156[0] + 4 * gout266[1];
    std::vector<Ciphertext> gout270 = ctx.eval_lut_amortized(&gin270, lut270);

    long gin270clear = 1 * gout86clear[0] + 2 * gout156clear[0] + 4 * gout266clear[1];
    std::vector<long> gout270clear = fvec270(gin270clear);

    assert(ctx.decrypt(&gout270[0]) == gout270clear[0]);
    assert(ctx.decrypt(&gout270[1]) == gout270clear[1]);
    std::vector<RotationPoly> lut271;
    std::vector<long (*)(long)> flut271;
    auto lut271idx0 = [](long I) -> long {
        /* GATE 328 (LUT3 _1703_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut271.push_back(ctx.genrate_lut(lut271idx0));
    flut271.push_back(lut271idx0);

    auto lut271idx1 = [](long I) -> long {
        /* GATE 284 (LUT3 _1659_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut271.push_back(ctx.genrate_lut(lut271idx1));
    flut271.push_back(lut271idx1);

    auto fvec271 = [flut271](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut271[i](I));
        return ret;
    };

    std::cerr << "\rLUT271   ";
    Ciphertext gin271 = 1 * gout270[0] + 2 * gout204[1] + 4 * gout267[1];
    std::vector<Ciphertext> gout271 = ctx.eval_lut_amortized(&gin271, lut271);

    long gin271clear = 1 * gout270clear[0] + 2 * gout204clear[1] + 4 * gout267clear[1];
    std::vector<long> gout271clear = fvec271(gin271clear);

    assert(ctx.decrypt(&gout271[0]) == gout271clear[0]);
    assert(ctx.decrypt(&gout271[1]) == gout271clear[1]);
    std::vector<RotationPoly> lut272;
    std::vector<long (*)(long)> flut272;
    auto lut272idx0 = [](long I) -> long {
        /* GATE 401 (LUT3 _1776_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut272.push_back(ctx.genrate_lut(lut272idx0));
    flut272.push_back(lut272idx0);

    auto lut272idx1 = [](long I) -> long {
        /* GATE 327 (LUT3 _1702_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut272.push_back(ctx.genrate_lut(lut272idx1));
    flut272.push_back(lut272idx1);

    auto fvec272 = [flut272](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut272[i](I));
        return ret;
    };

    std::cerr << "\rLUT272   ";
    Ciphertext gin272 = 1 * gout271[0] + 2 * gout205[1] + 4 * gout268[1];
    std::vector<Ciphertext> gout272 = ctx.eval_lut_amortized(&gin272, lut272);

    long gin272clear = 1 * gout271clear[0] + 2 * gout205clear[1] + 4 * gout268clear[1];
    std::vector<long> gout272clear = fvec272(gin272clear);

    assert(ctx.decrypt(&gout272[0]) == gout272clear[0]);
    assert(ctx.decrypt(&gout272[1]) == gout272clear[1]);
    std::vector<RotationPoly> lut273;
    std::vector<long (*)(long)> flut273;
    auto lut273idx0 = [](long I) -> long {
        /* GATE 453 (LUT3 _1828_ INIT 0x4b PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut273.push_back(ctx.genrate_lut(lut273idx0));
    flut273.push_back(lut273idx0);

    auto fvec273 = [flut273](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut273[i](I));
        return ret;
    };

    std::cerr << "\rLUT273   ";
    Ciphertext gin273 = 1 * ct_x0 + 2 * gout123[0] + 4 * ct_y15;
    std::vector<Ciphertext> gout273 = ctx.eval_lut_amortized(&gin273, lut273);

    long gin273clear = 1 * ct_x0clear + 2 * gout123clear[0] + 4 * ct_y15clear;
    std::vector<long> gout273clear = fvec273(gin273clear);

    assert(ctx.decrypt(&gout273[0]) == gout273clear[0]);
    std::vector<RotationPoly> lut274;
    std::vector<long (*)(long)> flut274;
    auto lut274idx0 = [](long I) -> long {
        /* GATE 450 (LUT3 _1825_ INIT 0xe1 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut274.push_back(ctx.genrate_lut(lut274idx0));
    flut274.push_back(lut274idx0);

    auto fvec274 = [flut274](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut274[i](I));
        return ret;
    };

    std::cerr << "\rLUT274   ";
    Ciphertext gin274 = 1 * gout117[0] + 2 * gout115[0] + 4 * gout273[0];
    std::vector<Ciphertext> gout274 = ctx.eval_lut_amortized(&gin274, lut274);

    long gin274clear = 1 * gout117clear[0] + 2 * gout115clear[0] + 4 * gout273clear[0];
    std::vector<long> gout274clear = fvec274(gin274clear);

    assert(ctx.decrypt(&gout274[0]) == gout274clear[0]);
    std::vector<RotationPoly> lut275;
    std::vector<long (*)(long)> flut275;
    auto lut275idx0 = [](long I) -> long {
        /* GATE 448 (LUT2 _1823_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut275.push_back(ctx.genrate_lut(lut275idx0));
    flut275.push_back(lut275idx0);

    auto fvec275 = [flut275](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut275[i](I));
        return ret;
    };

    std::cerr << "\rLUT275   ";
    Ciphertext gin275 = 1 * gout222[0] + 2 * gout274[0];
    std::vector<Ciphertext> gout275 = ctx.eval_lut_amortized(&gin275, lut275);

    long gin275clear = 1 * gout222clear[0] + 2 * gout274clear[0];
    std::vector<long> gout275clear = fvec275(gin275clear);

    assert(ctx.decrypt(&gout275[0]) == gout275clear[0]);
    std::cerr << "\rFA276    ";
    Ciphertext gin276 = gout99[2] + 1 * ct_x4 + 2 * ct_x5 + 1 * ct_y4 + 2 * ct_y5;
    std::vector<Ciphertext> gout276 = ctx.eval_lut_amortized(&gin276, decomp);

    long gin276clear = gout99clear[2] + 1 * ct_x4clear + 2 * ct_x5clear + 1 * ct_y4clear + 2 * ct_y5clear;
    std::vector<long> gout276clear = vdecomp(gin276clear);

    assert(ctx.decrypt(&gout276[0]) == gout276clear[0]);
    assert(ctx.decrypt(&gout276[1]) == gout276clear[1]);
    std::vector<RotationPoly> lut277;
    std::vector<long (*)(long)> flut277;
    auto lut277idx0 = [](long I) -> long {
        /* GATE 51 (LUT3 _1426_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut277.push_back(ctx.genrate_lut(lut277idx0));
    flut277.push_back(lut277idx0);

    auto fvec277 = [flut277](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut277[i](I));
        return ret;
    };

    std::cerr << "\rLUT277   ";
    Ciphertext gin277 = 1 * gout276[0] + 2 * gout75[0] + 4 * gout129[0];
    std::vector<Ciphertext> gout277 = ctx.eval_lut_amortized(&gin277, lut277);

    long gin277clear = 1 * gout276clear[0] + 2 * gout75clear[0] + 4 * gout129clear[0];
    std::vector<long> gout277clear = fvec277(gin277clear);

    assert(ctx.decrypt(&gout277[0]) == gout277clear[0]);
    std::vector<RotationPoly> lut278;
    std::vector<long (*)(long)> flut278;
    auto lut278idx0 = [](long I) -> long {
        /* GATE 50 (LUT2 _1425_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut278.push_back(ctx.genrate_lut(lut278idx0));
    flut278.push_back(lut278idx0);

    auto fvec278 = [flut278](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut278[i](I));
        return ret;
    };

    std::cerr << "\rLUT278   ";
    Ciphertext gin278 = 1 * gout277[0] + 2 * gout249[0];
    std::vector<Ciphertext> gout278 = ctx.eval_lut_amortized(&gin278, lut278);

    long gin278clear = 1 * gout277clear[0] + 2 * gout249clear[0];
    std::vector<long> gout278clear = fvec278(gin278clear);

    assert(ctx.decrypt(&gout278[0]) == gout278clear[0]);
    std::vector<RotationPoly> lut279;
    std::vector<long (*)(long)> flut279;
    auto lut279idx0 = [](long I) -> long {
        /* GATE 37 (LUT3 _1412_ INIT 0xfe PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut279.push_back(ctx.genrate_lut(lut279idx0));
    flut279.push_back(lut279idx0);

    auto fvec279 = [flut279](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut279[i](I));
        return ret;
    };

    std::cerr << "\rLUT279   ";
    Ciphertext gin279 = 1 * gout253[0] + 2 * gout278[0] + 4 * gout131[0];
    std::vector<Ciphertext> gout279 = ctx.eval_lut_amortized(&gin279, lut279);

    long gin279clear = 1 * gout253clear[0] + 2 * gout278clear[0] + 4 * gout131clear[0];
    std::vector<long> gout279clear = fvec279(gin279clear);

    assert(ctx.decrypt(&gout279[0]) == gout279clear[0]);
    std::vector<RotationPoly> lut280;
    std::vector<long (*)(long)> flut280;
    auto lut280idx0 = [](long I) -> long {
        /* GATE 71 (LUT3 _1446_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut280.push_back(ctx.genrate_lut(lut280idx0));
    flut280.push_back(lut280idx0);

    auto fvec280 = [flut280](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut280[i](I));
        return ret;
    };

    std::cerr << "\rLUT280   ";
    Ciphertext gin280 = 1 * gout276[1] + 2 * gout75[1] + 4 * gout129[0];
    std::vector<Ciphertext> gout280 = ctx.eval_lut_amortized(&gin280, lut280);

    long gin280clear = 1 * gout276clear[1] + 2 * gout75clear[1] + 4 * gout129clear[0];
    std::vector<long> gout280clear = fvec280(gin280clear);

    assert(ctx.decrypt(&gout280[0]) == gout280clear[0]);
    std::vector<RotationPoly> lut281;
    std::vector<long (*)(long)> flut281;
    auto lut281idx0 = [](long I) -> long {
        /* GATE 70 (LUT2 _1445_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut281.push_back(ctx.genrate_lut(lut281idx0));
    flut281.push_back(lut281idx0);

    auto fvec281 = [flut281](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut281[i](I));
        return ret;
    };

    std::cerr << "\rLUT281   ";
    Ciphertext gin281 = 1 * gout280[0] + 2 * gout249[0];
    std::vector<Ciphertext> gout281 = ctx.eval_lut_amortized(&gin281, lut281);

    long gin281clear = 1 * gout280clear[0] + 2 * gout249clear[0];
    std::vector<long> gout281clear = fvec281(gin281clear);

    assert(ctx.decrypt(&gout281[0]) == gout281clear[0]);
    std::vector<RotationPoly> lut282;
    std::vector<long (*)(long)> flut282;
    auto lut282idx0 = [](long I) -> long {
        /* GATE 52 (LUT3 _1427_ INIT 0xfe PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut282.push_back(ctx.genrate_lut(lut282idx0));
    flut282.push_back(lut282idx0);

    auto fvec282 = [flut282](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut282[i](I));
        return ret;
    };

    std::cerr << "\rLUT282   ";
    Ciphertext gin282 = 1 * gout252[0] + 2 * gout281[0] + 4 * gout131[0];
    std::vector<Ciphertext> gout282 = ctx.eval_lut_amortized(&gin282, lut282);

    long gin282clear = 1 * gout252clear[0] + 2 * gout281clear[0] + 4 * gout131clear[0];
    std::vector<long> gout282clear = fvec282(gin282clear);

    assert(ctx.decrypt(&gout282[0]) == gout282clear[0]);
    std::cerr << "\rFA283    ";
    Ciphertext gin283 = gout276[2] + 1 * ct_x6 + 2 * ct_x7 + 1 * ct_y6 + 2 * ct_y7;
    std::vector<Ciphertext> gout283 = ctx.eval_lut_amortized(&gin283, decomp);

    long gin283clear = gout276clear[2] + 1 * ct_x6clear + 2 * ct_x7clear + 1 * ct_y6clear + 2 * ct_y7clear;
    std::vector<long> gout283clear = vdecomp(gin283clear);

    assert(ctx.decrypt(&gout283[0]) == gout283clear[0]);
    assert(ctx.decrypt(&gout283[1]) == gout283clear[1]);
    std::vector<RotationPoly> lut284;
    std::vector<long (*)(long)> flut284;
    auto lut284idx0 = [](long I) -> long {
        /* GATE 96 (LUT3 _1471_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut284.push_back(ctx.genrate_lut(lut284idx0));
    flut284.push_back(lut284idx0);

    auto fvec284 = [flut284](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut284[i](I));
        return ret;
    };

    std::cerr << "\rLUT284   ";
    Ciphertext gin284 = 1 * gout283[0] + 2 * gout119[0] + 4 * gout129[0];
    std::vector<Ciphertext> gout284 = ctx.eval_lut_amortized(&gin284, lut284);

    long gin284clear = 1 * gout283clear[0] + 2 * gout119clear[0] + 4 * gout129clear[0];
    std::vector<long> gout284clear = fvec284(gin284clear);

    assert(ctx.decrypt(&gout284[0]) == gout284clear[0]);
    std::vector<RotationPoly> lut285;
    std::vector<long (*)(long)> flut285;
    auto lut285idx0 = [](long I) -> long {
        /* GATE 95 (LUT2 _1470_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut285.push_back(ctx.genrate_lut(lut285idx0));
    flut285.push_back(lut285idx0);

    auto fvec285 = [flut285](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut285[i](I));
        return ret;
    };

    std::cerr << "\rLUT285   ";
    Ciphertext gin285 = 1 * gout284[0] + 2 * gout249[0];
    std::vector<Ciphertext> gout285 = ctx.eval_lut_amortized(&gin285, lut285);

    long gin285clear = 1 * gout284clear[0] + 2 * gout249clear[0];
    std::vector<long> gout285clear = fvec285(gin285clear);

    assert(ctx.decrypt(&gout285[0]) == gout285clear[0]);
    std::vector<RotationPoly> lut286;
    std::vector<long (*)(long)> flut286;
    auto lut286idx0 = [](long I) -> long {
        /* GATE 74 (LUT3 _1449_ INIT 0xfe PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut286.push_back(ctx.genrate_lut(lut286idx0));
    flut286.push_back(lut286idx0);

    auto fvec286 = [flut286](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut286[i](I));
        return ret;
    };

    std::cerr << "\rLUT286   ";
    Ciphertext gin286 = 1 * gout251[0] + 2 * gout285[0] + 4 * gout131[0];
    std::vector<Ciphertext> gout286 = ctx.eval_lut_amortized(&gin286, lut286);

    long gin286clear = 1 * gout251clear[0] + 2 * gout285clear[0] + 4 * gout131clear[0];
    std::vector<long> gout286clear = fvec286(gin286clear);

    assert(ctx.decrypt(&gout286[0]) == gout286clear[0]);
    std::vector<RotationPoly> lut287;
    std::vector<long (*)(long)> flut287;
    auto lut287idx0 = [](long I) -> long {
        /* GATE 120 (LUT3 _1495_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut287.push_back(ctx.genrate_lut(lut287idx0));
    flut287.push_back(lut287idx0);

    auto fvec287 = [flut287](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut287[i](I));
        return ret;
    };

    std::cerr << "\rLUT287   ";
    Ciphertext gin287 = 1 * gout283[1] + 2 * gout119[1] + 4 * gout129[0];
    std::vector<Ciphertext> gout287 = ctx.eval_lut_amortized(&gin287, lut287);

    long gin287clear = 1 * gout283clear[1] + 2 * gout119clear[1] + 4 * gout129clear[0];
    std::vector<long> gout287clear = fvec287(gin287clear);

    assert(ctx.decrypt(&gout287[0]) == gout287clear[0]);
    std::vector<RotationPoly> lut288;
    std::vector<long (*)(long)> flut288;
    auto lut288idx0 = [](long I) -> long {
        /* GATE 462 (LUT3 _1837_ INIT 0xc5 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut288.push_back(ctx.genrate_lut(lut288idx0));
    flut288.push_back(lut288idx0);

    auto fvec288 = [flut288](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut288[i](I));
        return ret;
    };

    std::cerr << "\rLUT288   ";
    Ciphertext gin288 = 1 * gout287[0] + 2 * gout240[0] + 4 * gout249[0];
    std::vector<Ciphertext> gout288 = ctx.eval_lut_amortized(&gin288, lut288);

    long gin288clear = 1 * gout287clear[0] + 2 * gout240clear[0] + 4 * gout249clear[0];
    std::vector<long> gout288clear = fvec288(gin288clear);

    assert(ctx.decrypt(&gout288[0]) == gout288clear[0]);
    std::vector<RotationPoly> lut289;
    std::vector<long (*)(long)> flut289;
    auto lut289idx0 = [](long I) -> long {
        /* GATE 463 (LUT2 _1838_ INIT 0xb PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut289.push_back(ctx.genrate_lut(lut289idx0));
    flut289.push_back(lut289idx0);

    auto fvec289 = [flut289](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut289[i](I));
        return ret;
    };

    std::cerr << "\rLUT289   ";
    Ciphertext gin289 = 1 * gout131[0] + 2 * gout288[0];
    std::vector<Ciphertext> gout289 = ctx.eval_lut_amortized(&gin289, lut289);

    long gin289clear = 1 * gout131clear[0] + 2 * gout288clear[0];
    std::vector<long> gout289clear = fvec289(gin289clear);

    assert(ctx.decrypt(&gout289[0]) == gout289clear[0]);
    std::cerr << "\rFA290    ";
    Ciphertext gin290 = gout283[2] + 1 * ct_x8 + 2 * ct_x9 + 1 * ct_y8 + 2 * ct_y9;
    std::vector<Ciphertext> gout290 = ctx.eval_lut_amortized(&gin290, decomp);

    long gin290clear = gout283clear[2] + 1 * ct_x8clear + 2 * ct_x9clear + 1 * ct_y8clear + 2 * ct_y9clear;
    std::vector<long> gout290clear = vdecomp(gin290clear);

    assert(ctx.decrypt(&gout290[0]) == gout290clear[0]);
    assert(ctx.decrypt(&gout290[1]) == gout290clear[1]);
    std::vector<RotationPoly> lut291;
    std::vector<long (*)(long)> flut291;
    auto lut291idx0 = [](long I) -> long {
        /* GATE 152 (LUT3 _1527_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut291.push_back(ctx.genrate_lut(lut291idx0));
    flut291.push_back(lut291idx0);

    auto fvec291 = [flut291](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut291[i](I));
        return ret;
    };

    std::cerr << "\rLUT291   ";
    Ciphertext gin291 = 1 * gout290[0] + 2 * gout136[0] + 4 * gout129[0];
    std::vector<Ciphertext> gout291 = ctx.eval_lut_amortized(&gin291, lut291);

    long gin291clear = 1 * gout290clear[0] + 2 * gout136clear[0] + 4 * gout129clear[0];
    std::vector<long> gout291clear = fvec291(gin291clear);

    assert(ctx.decrypt(&gout291[0]) == gout291clear[0]);
    std::vector<RotationPoly> lut292;
    std::vector<long (*)(long)> flut292;
    auto lut292idx0 = [](long I) -> long {
        /* GATE 151 (LUT2 _1526_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut292.push_back(ctx.genrate_lut(lut292idx0));
    flut292.push_back(lut292idx0);

    auto fvec292 = [flut292](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut292[i](I));
        return ret;
    };

    std::cerr << "\rLUT292   ";
    Ciphertext gin292 = 1 * gout291[0] + 2 * gout249[0];
    std::vector<Ciphertext> gout292 = ctx.eval_lut_amortized(&gin292, lut292);

    long gin292clear = 1 * gout291clear[0] + 2 * gout249clear[0];
    std::vector<long> gout292clear = fvec292(gin292clear);

    assert(ctx.decrypt(&gout292[0]) == gout292clear[0]);
    std::vector<RotationPoly> lut293;
    std::vector<long (*)(long)> flut293;
    auto lut293idx0 = [](long I) -> long {
        /* GATE 121 (LUT3 _1496_ INIT 0xfe PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut293.push_back(ctx.genrate_lut(lut293idx0));
    flut293.push_back(lut293idx0);

    auto fvec293 = [flut293](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut293[i](I));
        return ret;
    };

    std::cerr << "\rLUT293   ";
    Ciphertext gin293 = 1 * gout250[0] + 2 * gout292[0] + 4 * gout131[0];
    std::vector<Ciphertext> gout293 = ctx.eval_lut_amortized(&gin293, lut293);

    long gin293clear = 1 * gout250clear[0] + 2 * gout292clear[0] + 4 * gout131clear[0];
    std::vector<long> gout293clear = fvec293(gin293clear);

    assert(ctx.decrypt(&gout293[0]) == gout293clear[0]);
    std::vector<RotationPoly> lut294;
    std::vector<long (*)(long)> flut294;
    auto lut294idx0 = [](long I) -> long {
        /* GATE 188 (LUT3 _1563_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut294.push_back(ctx.genrate_lut(lut294idx0));
    flut294.push_back(lut294idx0);

    auto fvec294 = [flut294](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut294[i](I));
        return ret;
    };

    std::cerr << "\rLUT294   ";
    Ciphertext gin294 = 1 * gout290[1] + 2 * gout136[1] + 4 * gout129[0];
    std::vector<Ciphertext> gout294 = ctx.eval_lut_amortized(&gin294, lut294);

    long gin294clear = 1 * gout290clear[1] + 2 * gout136clear[1] + 4 * gout129clear[0];
    std::vector<long> gout294clear = fvec294(gin294clear);

    assert(ctx.decrypt(&gout294[0]) == gout294clear[0]);
    std::vector<RotationPoly> lut295;
    std::vector<long (*)(long)> flut295;
    auto lut295idx0 = [](long I) -> long {
        /* GATE 187 (LUT2 _1562_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut295.push_back(ctx.genrate_lut(lut295idx0));
    flut295.push_back(lut295idx0);

    auto fvec295 = [flut295](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut295[i](I));
        return ret;
    };

    std::cerr << "\rLUT295   ";
    Ciphertext gin295 = 1 * gout294[0] + 2 * gout249[0];
    std::vector<Ciphertext> gout295 = ctx.eval_lut_amortized(&gin295, lut295);

    long gin295clear = 1 * gout294clear[0] + 2 * gout249clear[0];
    std::vector<long> gout295clear = fvec295(gin295clear);

    assert(ctx.decrypt(&gout295[0]) == gout295clear[0]);
    std::cerr << "\rFA296    ";
    Ciphertext gin296 = gout290[2] + 1 * ct_x10 + 2 * ct_x11 + 1 * ct_y10 + 2 * ct_y11;
    std::vector<Ciphertext> gout296 = ctx.eval_lut_amortized(&gin296, decomp);

    long gin296clear = gout290clear[2] + 1 * ct_x10clear + 2 * ct_x11clear + 1 * ct_y10clear + 2 * ct_y11clear;
    std::vector<long> gout296clear = vdecomp(gin296clear);

    assert(ctx.decrypt(&gout296[0]) == gout296clear[0]);
    assert(ctx.decrypt(&gout296[1]) == gout296clear[1]);
    std::vector<RotationPoly> lut297;
    std::vector<long (*)(long)> flut297;
    auto lut297idx0 = [](long I) -> long {
        /* GATE 227 (LUT3 _1602_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut297.push_back(ctx.genrate_lut(lut297idx0));
    flut297.push_back(lut297idx0);

    auto fvec297 = [flut297](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut297[i](I));
        return ret;
    };

    std::cerr << "\rLUT297   ";
    Ciphertext gin297 = 1 * gout296[0] + 2 * gout144[0] + 4 * gout129[0];
    std::vector<Ciphertext> gout297 = ctx.eval_lut_amortized(&gin297, lut297);

    long gin297clear = 1 * gout296clear[0] + 2 * gout144clear[0] + 4 * gout129clear[0];
    std::vector<long> gout297clear = fvec297(gin297clear);

    assert(ctx.decrypt(&gout297[0]) == gout297clear[0]);
    std::vector<RotationPoly> lut298;
    std::vector<long (*)(long)> flut298;
    auto lut298idx0 = [](long I) -> long {
        /* GATE 226 (LUT2 _1601_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut298.push_back(ctx.genrate_lut(lut298idx0));
    flut298.push_back(lut298idx0);

    auto fvec298 = [flut298](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut298[i](I));
        return ret;
    };

    std::cerr << "\rLUT298   ";
    Ciphertext gin298 = 1 * gout297[0] + 2 * gout249[0];
    std::vector<Ciphertext> gout298 = ctx.eval_lut_amortized(&gin298, lut298);

    long gin298clear = 1 * gout297clear[0] + 2 * gout249clear[0];
    std::vector<long> gout298clear = fvec298(gin298clear);

    assert(ctx.decrypt(&gout298[0]) == gout298clear[0]);
    std::vector<RotationPoly> lut299;
    std::vector<long (*)(long)> flut299;
    auto lut299idx0 = [](long I) -> long {
        /* GATE 270 (LUT3 _1645_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut299.push_back(ctx.genrate_lut(lut299idx0));
    flut299.push_back(lut299idx0);

    auto fvec299 = [flut299](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut299[i](I));
        return ret;
    };

    std::cerr << "\rLUT299   ";
    Ciphertext gin299 = 1 * gout296[1] + 2 * gout144[1] + 4 * gout129[0];
    std::vector<Ciphertext> gout299 = ctx.eval_lut_amortized(&gin299, lut299);

    long gin299clear = 1 * gout296clear[1] + 2 * gout144clear[1] + 4 * gout129clear[0];
    std::vector<long> gout299clear = fvec299(gin299clear);

    assert(ctx.decrypt(&gout299[0]) == gout299clear[0]);
    std::cerr << "\rFA300    ";
    Ciphertext gin300 = gout296[2] + 1 * ct_x12 + 2 * ct_x13 + 1 * ct_y12 + 2 * ct_y13;
    std::vector<Ciphertext> gout300 = ctx.eval_lut_amortized(&gin300, decomp);

    long gin300clear = gout296clear[2] + 1 * ct_x12clear + 2 * ct_x13clear + 1 * ct_y12clear + 2 * ct_y13clear;
    std::vector<long> gout300clear = vdecomp(gin300clear);

    assert(ctx.decrypt(&gout300[0]) == gout300clear[0]);
    assert(ctx.decrypt(&gout300[1]) == gout300clear[1]);
    std::vector<RotationPoly> lut301;
    std::vector<long (*)(long)> flut301;
    auto lut301idx0 = [](long I) -> long {
        /* GATE 315 (LUT3 _1690_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut301.push_back(ctx.genrate_lut(lut301idx0));
    flut301.push_back(lut301idx0);

    auto fvec301 = [flut301](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut301[i](I));
        return ret;
    };

    std::cerr << "\rLUT301   ";
    Ciphertext gin301 = 1 * gout300[0] + 2 * gout145[0] + 4 * gout129[0];
    std::vector<Ciphertext> gout301 = ctx.eval_lut_amortized(&gin301, lut301);

    long gin301clear = 1 * gout300clear[0] + 2 * gout145clear[0] + 4 * gout129clear[0];
    std::vector<long> gout301clear = fvec301(gin301clear);

    assert(ctx.decrypt(&gout301[0]) == gout301clear[0]);
    std::vector<RotationPoly> lut302;
    std::vector<long (*)(long)> flut302;
    auto lut302idx0 = [](long I) -> long {
        /* GATE 314 (LUT2 _1689_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut302.push_back(ctx.genrate_lut(lut302idx0));
    flut302.push_back(lut302idx0);

    auto fvec302 = [flut302](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut302[i](I));
        return ret;
    };

    std::cerr << "\rLUT302   ";
    Ciphertext gin302 = 1 * gout301[0] + 2 * gout249[0];
    std::vector<Ciphertext> gout302 = ctx.eval_lut_amortized(&gin302, lut302);

    long gin302clear = 1 * gout301clear[0] + 2 * gout249clear[0];
    std::vector<long> gout302clear = fvec302(gin302clear);

    assert(ctx.decrypt(&gout302[0]) == gout302clear[0]);
    std::vector<RotationPoly> lut303;
    std::vector<long (*)(long)> flut303;
    auto lut303idx0 = [](long I) -> long {
        /* GATE 361 (LUT3 _1736_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut303.push_back(ctx.genrate_lut(lut303idx0));
    flut303.push_back(lut303idx0);

    auto fvec303 = [flut303](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut303[i](I));
        return ret;
    };

    std::cerr << "\rLUT303   ";
    Ciphertext gin303 = 1 * gout300[1] + 2 * gout145[1] + 4 * gout129[0];
    std::vector<Ciphertext> gout303 = ctx.eval_lut_amortized(&gin303, lut303);

    long gin303clear = 1 * gout300clear[1] + 2 * gout145clear[1] + 4 * gout129clear[0];
    std::vector<long> gout303clear = fvec303(gin303clear);

    assert(ctx.decrypt(&gout303[0]) == gout303clear[0]);
    std::vector<RotationPoly> lut304;
    std::vector<long (*)(long)> flut304;
    auto lut304idx0 = [](long I) -> long {
        /* GATE 360 (LUT2 _1735_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut304.push_back(ctx.genrate_lut(lut304idx0));
    flut304.push_back(lut304idx0);

    auto fvec304 = [flut304](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut304[i](I));
        return ret;
    };

    std::cerr << "\rLUT304   ";
    Ciphertext gin304 = 1 * gout303[0] + 2 * gout249[0];
    std::vector<Ciphertext> gout304 = ctx.eval_lut_amortized(&gin304, lut304);

    long gin304clear = 1 * gout303clear[0] + 2 * gout249clear[0];
    std::vector<long> gout304clear = fvec304(gin304clear);

    assert(ctx.decrypt(&gout304[0]) == gout304clear[0]);
    std::cerr << "\rFA305    ";
    Ciphertext gin305 = gout300[2] + 1 * ct_x14 + 2 * ct_x15 + 1 * ct_y14 + 2 * ct_y15;
    std::vector<Ciphertext> gout305 = ctx.eval_lut_amortized(&gin305, decomp);

    long gin305clear = gout300clear[2] + 1 * ct_x14clear + 2 * ct_x15clear + 1 * ct_y14clear + 2 * ct_y15clear;
    std::vector<long> gout305clear = vdecomp(gin305clear);

    assert(ctx.decrypt(&gout305[0]) == gout305clear[0]);
    assert(ctx.decrypt(&gout305[1]) == gout305clear[1]);
    std::vector<RotationPoly> lut306;
    std::vector<long (*)(long)> flut306;
    auto lut306idx0 = [](long I) -> long {
        /* GATE 408 (LUT3 _1783_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut306.push_back(ctx.genrate_lut(lut306idx0));
    flut306.push_back(lut306idx0);

    auto fvec306 = [flut306](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut306[i](I));
        return ret;
    };

    std::cerr << "\rLUT306   ";
    Ciphertext gin306 = 1 * gout305[0] + 2 * gout146[0] + 4 * gout129[0];
    std::vector<Ciphertext> gout306 = ctx.eval_lut_amortized(&gin306, lut306);

    long gin306clear = 1 * gout305clear[0] + 2 * gout146clear[0] + 4 * gout129clear[0];
    std::vector<long> gout306clear = fvec306(gin306clear);

    assert(ctx.decrypt(&gout306[0]) == gout306clear[0]);
    std::vector<RotationPoly> lut307;
    std::vector<long (*)(long)> flut307;
    auto lut307idx0 = [](long I) -> long {
        /* GATE 407 (LUT2 _1782_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut307.push_back(ctx.genrate_lut(lut307idx0));
    flut307.push_back(lut307idx0);

    auto fvec307 = [flut307](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut307[i](I));
        return ret;
    };

    std::cerr << "\rLUT307   ";
    Ciphertext gin307 = 1 * gout306[0] + 2 * gout249[0];
    std::vector<Ciphertext> gout307 = ctx.eval_lut_amortized(&gin307, lut307);

    long gin307clear = 1 * gout306clear[0] + 2 * gout249clear[0];
    std::vector<long> gout307clear = fvec307(gin307clear);

    assert(ctx.decrypt(&gout307[0]) == gout307clear[0]);
    std::vector<RotationPoly> lut308;
    std::vector<long (*)(long)> flut308;
    auto lut308idx0 = [](long I) -> long {
        /* GATE 269 (LUT2 _1644_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut308.push_back(ctx.genrate_lut(lut308idx0));
    flut308.push_back(lut308idx0);

    auto fvec308 = [flut308](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut308[i](I));
        return ret;
    };

    std::cerr << "\rLUT308   ";
    Ciphertext gin308 = 1 * gout299[0] + 2 * gout249[0];
    std::vector<Ciphertext> gout308 = ctx.eval_lut_amortized(&gin308, lut308);

    long gin308clear = 1 * gout299clear[0] + 2 * gout249clear[0];
    std::vector<long> gout308clear = fvec308(gin308clear);

    assert(ctx.decrypt(&gout308[0]) == gout308clear[0]);
    std::vector<RotationPoly> lut309;
    std::vector<long (*)(long)> flut309;
    auto lut309idx0 = [](long I) -> long {
        /* GATE 459 (LUT3 _1834_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut309.push_back(ctx.genrate_lut(lut309idx0));
    flut309.push_back(lut309idx0);

    auto fvec309 = [flut309](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut309[i](I));
        return ret;
    };

    std::cerr << "\rLUT309   ";
    Ciphertext gin309 = 1 * gout305[1] + 2 * gout146[1] + 4 * gout129[0];
    std::vector<Ciphertext> gout309 = ctx.eval_lut_amortized(&gin309, lut309);

    long gin309clear = 1 * gout305clear[1] + 2 * gout146clear[1] + 4 * gout129clear[0];
    std::vector<long> gout309clear = fvec309(gin309clear);

    assert(ctx.decrypt(&gout309[0]) == gout309clear[0]);
    std::vector<RotationPoly> lut310;
    std::vector<long (*)(long)> flut310;
    auto lut310idx0 = [](long I) -> long {
        /* GATE 458 (LUT2 _1833_ INIT 0x4 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut310.push_back(ctx.genrate_lut(lut310idx0));
    flut310.push_back(lut310idx0);

    auto fvec310 = [flut310](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut310[i](I));
        return ret;
    };

    std::cerr << "\rLUT310   ";
    Ciphertext gin310 = 1 * gout309[0] + 2 * gout249[0];
    std::vector<Ciphertext> gout310 = ctx.eval_lut_amortized(&gin310, lut310);

    long gin310clear = 1 * gout309clear[0] + 2 * gout249clear[0];
    std::vector<long> gout310clear = fvec310(gin310clear);

    assert(ctx.decrypt(&gout310[0]) == gout310clear[0]);
    std::vector<RotationPoly> lut311;
    std::vector<long (*)(long)> flut311;
    auto lut311idx0 = [](long I) -> long {
        /* GATE 379 (LUT2 _1754_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut311.push_back(ctx.genrate_lut(lut311idx0));
    flut311.push_back(lut311idx0);

    auto fvec311 = [flut311](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut311[i](I));
        return ret;
    };

    std::cerr << "\rLUT311   ";
    Ciphertext gin311 = 1 * ct_x12 + 2 * ct_y2;
    std::vector<Ciphertext> gout311 = ctx.eval_lut_amortized(&gin311, lut311);

    long gin311clear = 1 * ct_x12clear + 2 * ct_y2clear;
    std::vector<long> gout311clear = fvec311(gin311clear);

    assert(ctx.decrypt(&gout311[0]) == gout311clear[0]);
    std::vector<RotationPoly> lut312;
    std::vector<long (*)(long)> flut312;
    auto lut312idx0 = [](long I) -> long {
        /* GATE 445 (LUT3 _1820_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut312.push_back(ctx.genrate_lut(lut312idx0));
    flut312.push_back(lut312idx0);

    auto lut312idx1 = [](long I) -> long {
        /* GATE 377 (LUT3 _1752_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut312.push_back(ctx.genrate_lut(lut312idx1));
    flut312.push_back(lut312idx1);

    auto fvec312 = [flut312](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut312[i](I));
        return ret;
    };

    std::cerr << "\rLUT312   ";
    Ciphertext gin312 = 1 * gout29[0] + 2 * gout311[0] + 4 * gout158[0];
    std::vector<Ciphertext> gout312 = ctx.eval_lut_amortized(&gin312, lut312);

    long gin312clear = 1 * gout29clear[0] + 2 * gout311clear[0] + 4 * gout158clear[0];
    std::vector<long> gout312clear = fvec312(gin312clear);

    assert(ctx.decrypt(&gout312[0]) == gout312clear[0]);
    assert(ctx.decrypt(&gout312[1]) == gout312clear[1]);
    std::vector<RotationPoly> lut313;
    std::vector<long (*)(long)> flut313;
    auto lut313idx0 = [](long I) -> long {
        /* GATE 444 (LUT3 _1819_ INIT 0x87 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut313.push_back(ctx.genrate_lut(lut313idx0));
    flut313.push_back(lut313idx0);

    auto fvec313 = [flut313](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut313[i](I));
        return ret;
    };

    std::cerr << "\rLUT313   ";
    Ciphertext gin313 = 1 * ct_x11 + 2 * ct_y4 + 4 * gout312[0];
    std::vector<Ciphertext> gout313 = ctx.eval_lut_amortized(&gin313, lut313);

    long gin313clear = 1 * ct_x11clear + 2 * ct_y4clear + 4 * gout312clear[0];
    std::vector<long> gout313clear = fvec313(gin313clear);

    assert(ctx.decrypt(&gout313[0]) == gout313clear[0]);
    std::vector<RotationPoly> lut314;
    std::vector<long (*)(long)> flut314;
    auto lut314idx0 = [](long I) -> long {
        /* GATE 442 (LUT3 _1817_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut314.push_back(ctx.genrate_lut(lut314idx0));
    flut314.push_back(lut314idx0);

    auto fvec314 = [flut314](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut314[i](I));
        return ret;
    };

    std::cerr << "\rLUT314   ";
    Ciphertext gin314 = 1 * gout195[0] + 2 * gout313[0] + 4 * gout152[1];
    std::vector<Ciphertext> gout314 = ctx.eval_lut_amortized(&gin314, lut314);

    long gin314clear = 1 * gout195clear[0] + 2 * gout313clear[0] + 4 * gout152clear[1];
    std::vector<long> gout314clear = fvec314(gin314clear);

    assert(ctx.decrypt(&gout314[0]) == gout314clear[0]);
    std::vector<RotationPoly> lut315;
    std::vector<long (*)(long)> flut315;
    auto lut315idx0 = [](long I) -> long {
        /* GATE 440 (LUT3 _1815_ INIT 0x71 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut315.push_back(ctx.genrate_lut(lut315idx0));
    flut315.push_back(lut315idx0);

    auto lut315idx1 = [](long I) -> long {
        /* GATE 372 (LUT3 _1747_ INIT 0x69 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut315.push_back(ctx.genrate_lut(lut315idx1));
    flut315.push_back(lut315idx1);

    auto fvec315 = [flut315](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut315[i](I));
        return ret;
    };

    std::cerr << "\rLUT315   ";
    Ciphertext gin315 = 1 * gout122[1] + 2 * gout312[1] + 4 * gout95[1];
    std::vector<Ciphertext> gout315 = ctx.eval_lut_amortized(&gin315, lut315);

    long gin315clear = 1 * gout122clear[1] + 2 * gout312clear[1] + 4 * gout95clear[1];
    std::vector<long> gout315clear = fvec315(gin315clear);

    assert(ctx.decrypt(&gout315[0]) == gout315clear[0]);
    assert(ctx.decrypt(&gout315[1]) == gout315clear[1]);
    std::vector<RotationPoly> lut316;
    std::vector<long (*)(long)> flut316;
    auto lut316idx0 = [](long I) -> long {
        /* GATE 439 (LUT3 _1814_ INIT 0x71 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut316.push_back(ctx.genrate_lut(lut316idx0));
    flut316.push_back(lut316idx0);

    auto lut316idx1 = [](long I) -> long {
        /* GATE 371 (LUT3 _1746_ INIT 0x69 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut316.push_back(ctx.genrate_lut(lut316idx1));
    flut316.push_back(lut316idx1);

    auto fvec316 = [flut316](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut316[i](I));
        return ret;
    };

    std::cerr << "\rLUT316   ";
    Ciphertext gin316 = 1 * gout315[1] + 2 * gout185[1] + 4 * gout198[0];
    std::vector<Ciphertext> gout316 = ctx.eval_lut_amortized(&gin316, lut316);

    long gin316clear = 1 * gout315clear[1] + 2 * gout185clear[1] + 4 * gout198clear[0];
    std::vector<long> gout316clear = fvec316(gin316clear);

    assert(ctx.decrypt(&gout316[0]) == gout316clear[0]);
    assert(ctx.decrypt(&gout316[1]) == gout316clear[1]);
    std::vector<RotationPoly> lut317;
    std::vector<long (*)(long)> flut317;
    auto lut317idx0 = [](long I) -> long {
        /* GATE 438 (LUT3 _1813_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut317.push_back(ctx.genrate_lut(lut317idx0));
    flut317.push_back(lut317idx0);

    auto fvec317 = [flut317](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut317[i](I));
        return ret;
    };

    std::cerr << "\rLUT317   ";
    Ciphertext gin317 = 1 * gout316[0] + 2 * gout315[0] + 4 * gout185[0];
    std::vector<Ciphertext> gout317 = ctx.eval_lut_amortized(&gin317, lut317);

    long gin317clear = 1 * gout316clear[0] + 2 * gout315clear[0] + 4 * gout185clear[0];
    std::vector<long> gout317clear = fvec317(gin317clear);

    assert(ctx.decrypt(&gout317[0]) == gout317clear[0]);
    std::vector<RotationPoly> lut318;
    std::vector<long (*)(long)> flut318;
    auto lut318idx0 = [](long I) -> long {
        /* GATE 416 (LUT3 _1791_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut318.push_back(ctx.genrate_lut(lut318idx0));
    flut318.push_back(lut318idx0);

    auto fvec318 = [flut318](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut318[i](I));
        return ret;
    };

    std::cerr << "\rLUT318   ";
    Ciphertext gin318 = 1 * gout194[0] + 2 * gout317[0] + 4 * gout314[0];
    std::vector<Ciphertext> gout318 = ctx.eval_lut_amortized(&gin318, lut318);

    long gin318clear = 1 * gout194clear[0] + 2 * gout317clear[0] + 4 * gout314clear[0];
    std::vector<long> gout318clear = fvec318(gin318clear);

    assert(ctx.decrypt(&gout318[0]) == gout318clear[0]);
    std::vector<RotationPoly> lut319;
    std::vector<long (*)(long)> flut319;
    auto lut319idx0 = [](long I) -> long {
        /* GATE 447 (LUT3 _1822_ INIT 0x71 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut319.push_back(ctx.genrate_lut(lut319idx0));
    flut319.push_back(lut319idx0);

    auto lut319idx1 = [](long I) -> long {
        /* GATE 370 (LUT3 _1745_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut319.push_back(ctx.genrate_lut(lut319idx1));
    flut319.push_back(lut319idx1);

    auto fvec319 = [flut319](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut319[i](I));
        return ret;
    };

    std::cerr << "\rLUT319   ";
    Ciphertext gin319 = 1 * gout316[1] + 2 * gout222[1] + 4 * gout205[0];
    std::vector<Ciphertext> gout319 = ctx.eval_lut_amortized(&gin319, lut319);

    long gin319clear = 1 * gout316clear[1] + 2 * gout222clear[1] + 4 * gout205clear[0];
    std::vector<long> gout319clear = fvec319(gin319clear);

    assert(ctx.decrypt(&gout319[0]) == gout319clear[0]);
    assert(ctx.decrypt(&gout319[1]) == gout319clear[1]);
    std::vector<RotationPoly> lut320;
    std::vector<long (*)(long)> flut320;
    auto lut320idx0 = [](long I) -> long {
        /* GATE 415 (LUT3 _1790_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut320.push_back(ctx.genrate_lut(lut320idx0));
    flut320.push_back(lut320idx0);

    auto fvec320 = [flut320](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut320[i](I));
        return ret;
    };

    std::cerr << "\rLUT320   ";
    Ciphertext gin320 = 1 * gout318[0] + 2 * gout319[0] + 4 * gout275[0];
    std::vector<Ciphertext> gout320 = ctx.eval_lut_amortized(&gin320, lut320);

    long gin320clear = 1 * gout318clear[0] + 2 * gout319clear[0] + 4 * gout275clear[0];
    std::vector<long> gout320clear = fvec320(gin320clear);

    assert(ctx.decrypt(&gout320[0]) == gout320clear[0]);
    std::vector<RotationPoly> lut321;
    std::vector<long (*)(long)> flut321;
    auto lut321idx0 = [](long I) -> long {
        /* GATE 455 (LUT3 _1830_ INIT 0x71 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut321.push_back(ctx.genrate_lut(lut321idx0));
    flut321.push_back(lut321idx0);

    auto lut321idx1 = [](long I) -> long {
        /* GATE 369 (LUT3 _1744_ INIT 0x69 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut321.push_back(ctx.genrate_lut(lut321idx1));
    flut321.push_back(lut321idx1);

    auto fvec321 = [flut321](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut321[i](I));
        return ret;
    };

    std::cerr << "\rLUT321   ";
    Ciphertext gin321 = 1 * gout319[1] + 2 * gout269[1] + 4 * gout272[0];
    std::vector<Ciphertext> gout321 = ctx.eval_lut_amortized(&gin321, lut321);

    long gin321clear = 1 * gout319clear[1] + 2 * gout269clear[1] + 4 * gout272clear[0];
    std::vector<long> gout321clear = fvec321(gin321clear);

    assert(ctx.decrypt(&gout321[0]) == gout321clear[0]);
    assert(ctx.decrypt(&gout321[1]) == gout321clear[1]);
    std::vector<RotationPoly> lut322;
    std::vector<long (*)(long)> flut322;
    auto lut322idx0 = [](long I) -> long {
        /* GATE 414 (LUT2 _1789_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut322.push_back(ctx.genrate_lut(lut322idx0));
    flut322.push_back(lut322idx0);

    auto fvec322 = [flut322](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut322[i](I));
        return ret;
    };

    std::cerr << "\rLUT322   ";
    Ciphertext gin322 = 1 * gout320[0] + 2 * gout321[0];
    std::vector<Ciphertext> gout322 = ctx.eval_lut_amortized(&gin322, lut322);

    long gin322clear = 1 * gout320clear[0] + 2 * gout321clear[0];
    std::vector<long> gout322clear = fvec322(gin322clear);

    assert(ctx.decrypt(&gout322[0]) == gout322clear[0]);
    std::vector<RotationPoly> lut323;
    std::vector<long (*)(long)> flut323;
    auto lut323idx0 = [](long I) -> long {
        /* GATE 242 (LUT3 _1617_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut323.push_back(ctx.genrate_lut(lut323idx0));
    flut323.push_back(lut323idx0);

    auto lut323idx1 = [](long I) -> long {
        /* GATE 204 (LUT3 _1579_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut323.push_back(ctx.genrate_lut(lut323idx1));
    flut323.push_back(lut323idx1);

    auto fvec323 = [flut323](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut323[i](I));
        return ret;
    };

    std::cerr << "\rLUT323   ";
    Ciphertext gin323 = 1 * gout138[0] + 2 * gout86[1] + 4 * gout92[1];
    std::vector<Ciphertext> gout323 = ctx.eval_lut_amortized(&gin323, lut323);

    long gin323clear = 1 * gout138clear[0] + 2 * gout86clear[1] + 4 * gout92clear[1];
    std::vector<long> gout323clear = fvec323(gin323clear);

    assert(ctx.decrypt(&gout323[0]) == gout323clear[0]);
    assert(ctx.decrypt(&gout323[1]) == gout323clear[1]);
    std::vector<RotationPoly> lut324;
    std::vector<long (*)(long)> flut324;
    auto lut324idx0 = [](long I) -> long {
        /* GATE 283 (LUT3 _1658_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut324.push_back(ctx.genrate_lut(lut324idx0));
    flut324.push_back(lut324idx0);

    auto lut324idx1 = [](long I) -> long {
        /* GATE 241 (LUT3 _1616_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut324.push_back(ctx.genrate_lut(lut324idx1));
    flut324.push_back(lut324idx1);

    auto fvec324 = [flut324](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut324[i](I));
        return ret;
    };

    std::cerr << "\rLUT324   ";
    Ciphertext gin324 = 1 * gout323[0] + 2 * gout270[1] + 4 * gout225[1];
    std::vector<Ciphertext> gout324 = ctx.eval_lut_amortized(&gin324, lut324);

    long gin324clear = 1 * gout323clear[0] + 2 * gout270clear[1] + 4 * gout225clear[1];
    std::vector<long> gout324clear = fvec324(gin324clear);

    assert(ctx.decrypt(&gout324[0]) == gout324clear[0]);
    assert(ctx.decrypt(&gout324[1]) == gout324clear[1]);
    std::vector<RotationPoly> lut325;
    std::vector<long (*)(long)> flut325;
    auto lut325idx0 = [](long I) -> long {
        /* GATE 326 (LUT3 _1701_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut325.push_back(ctx.genrate_lut(lut325idx0));
    flut325.push_back(lut325idx0);

    auto lut325idx1 = [](long I) -> long {
        /* GATE 282 (LUT3 _1657_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut325.push_back(ctx.genrate_lut(lut325idx1));
    flut325.push_back(lut325idx1);

    auto fvec325 = [flut325](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut325[i](I));
        return ret;
    };

    std::cerr << "\rLUT325   ";
    Ciphertext gin325 = 1 * gout324[0] + 2 * gout271[1] + 4 * gout226[1];
    std::vector<Ciphertext> gout325 = ctx.eval_lut_amortized(&gin325, lut325);

    long gin325clear = 1 * gout324clear[0] + 2 * gout271clear[1] + 4 * gout226clear[1];
    std::vector<long> gout325clear = fvec325(gin325clear);

    assert(ctx.decrypt(&gout325[0]) == gout325clear[0]);
    assert(ctx.decrypt(&gout325[1]) == gout325clear[1]);
    std::vector<RotationPoly> lut326;
    std::vector<long (*)(long)> flut326;
    auto lut326idx0 = [](long I) -> long {
        /* GATE 405 (LUT3 _1780_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut326.push_back(ctx.genrate_lut(lut326idx0));
    flut326.push_back(lut326idx0);

    auto lut326idx1 = [](long I) -> long {
        /* GATE 325 (LUT3 _1700_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut326.push_back(ctx.genrate_lut(lut326idx1));
    flut326.push_back(lut326idx1);

    auto fvec326 = [flut326](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut326[i](I));
        return ret;
    };

    std::cerr << "\rLUT326   ";
    Ciphertext gin326 = 1 * gout325[0] + 2 * gout272[1] + 4 * gout226[0];
    std::vector<Ciphertext> gout326 = ctx.eval_lut_amortized(&gin326, lut326);

    long gin326clear = 1 * gout325clear[0] + 2 * gout272clear[1] + 4 * gout226clear[0];
    std::vector<long> gout326clear = fvec326(gin326clear);

    assert(ctx.decrypt(&gout326[0]) == gout326clear[0]);
    assert(ctx.decrypt(&gout326[1]) == gout326clear[1]);
    std::vector<RotationPoly> lut327;
    std::vector<long (*)(long)> flut327;
    auto lut327idx0 = [](long I) -> long {
        /* GATE 456 (LUT2 _1831_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut327.push_back(ctx.genrate_lut(lut327idx0));
    flut327.push_back(lut327idx0);

    auto lut327idx1 = [](long I) -> long {
        /* GATE 368 (LUT2 _1743_ INIT 0x9 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut327.push_back(ctx.genrate_lut(lut327idx1));
    flut327.push_back(lut327idx1);

    auto fvec327 = [flut327](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut327[i](I));
        return ret;
    };

    std::cerr << "\rLUT327   ";
    Ciphertext gin327 = 1 * gout326[0] + 2 * gout321[1];
    std::vector<Ciphertext> gout327 = ctx.eval_lut_amortized(&gin327, lut327);

    long gin327clear = 1 * gout326clear[0] + 2 * gout321clear[1];
    std::vector<long> gout327clear = fvec327(gin327clear);

    assert(ctx.decrypt(&gout327[0]) == gout327clear[0]);
    assert(ctx.decrypt(&gout327[1]) == gout327clear[1]);
    std::vector<RotationPoly> lut328;
    std::vector<long (*)(long)> flut328;
    auto lut328idx0 = [](long I) -> long {
        /* GATE 413 (LUT3 _1788_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut328.push_back(ctx.genrate_lut(lut328idx0));
    flut328.push_back(lut328idx0);

    auto fvec328 = [flut328](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut328[i](I));
        return ret;
    };

    std::cerr << "\rLUT328   ";
    Ciphertext gin328 = 1 * gout322[0] + 2 * gout327[0] + 4 * gout269[0];
    std::vector<Ciphertext> gout328 = ctx.eval_lut_amortized(&gin328, lut328);

    long gin328clear = 1 * gout322clear[0] + 2 * gout327clear[0] + 4 * gout269clear[0];
    std::vector<long> gout328clear = fvec328(gin328clear);

    assert(ctx.decrypt(&gout328[0]) == gout328clear[0]);
    std::vector<RotationPoly> lut329;
    std::vector<long (*)(long)> flut329;
    auto lut329idx0 = [](long I) -> long {
        /* GATE 177 (LUT2 _1552_ INIT 0x8 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut329.push_back(ctx.genrate_lut(lut329idx0));
    flut329.push_back(lut329idx0);

    auto fvec329 = [flut329](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut329[i](I));
        return ret;
    };

    std::cerr << "\rLUT329   ";
    Ciphertext gin329 = 1 * ct_y3 + 2 * ct_x6;
    std::vector<Ciphertext> gout329 = ctx.eval_lut_amortized(&gin329, lut329);

    long gin329clear = 1 * ct_y3clear + 2 * ct_x6clear;
    std::vector<long> gout329clear = fvec329(gin329clear);

    assert(ctx.decrypt(&gout329[0]) == gout329clear[0]);
    std::vector<RotationPoly> lut330;
    std::vector<long (*)(long)> flut330;
    auto lut330idx0 = [](long I) -> long {
        /* GATE 216 (LUT3 _1591_ INIT 0x17 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut330.push_back(ctx.genrate_lut(lut330idx0));
    flut330.push_back(lut330idx0);

    auto lut330idx1 = [](long I) -> long {
        /* GATE 174 (LUT3 _1549_ INIT 0x96 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut330.push_back(ctx.genrate_lut(lut330idx1));
    flut330.push_back(lut330idx1);

    auto fvec330 = [flut330](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut330[i](I));
        return ret;
    };

    std::cerr << "\rLUT330   ";
    Ciphertext gin330 = 1 * gout153[0] + 2 * gout242[0] + 4 * gout329[0];
    std::vector<Ciphertext> gout330 = ctx.eval_lut_amortized(&gin330, lut330);

    long gin330clear = 1 * gout153clear[0] + 2 * gout242clear[0] + 4 * gout329clear[0];
    std::vector<long> gout330clear = fvec330(gin330clear);

    assert(ctx.decrypt(&gout330[0]) == gout330clear[0]);
    assert(ctx.decrypt(&gout330[1]) == gout330clear[1]);
    std::vector<RotationPoly> lut331;
    std::vector<long (*)(long)> flut331;
    auto lut331idx0 = [](long I) -> long {
        /* GATE 261 (LUT3 _1636_ INIT 0xb2 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut331.push_back(ctx.genrate_lut(lut331idx0));
    flut331.push_back(lut331idx0);

    auto lut331idx1 = [](long I) -> long {
        /* GATE 214 (LUT3 _1589_ INIT 0x96 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut331.push_back(ctx.genrate_lut(lut331idx1));
    flut331.push_back(lut331idx1);

    auto fvec331 = [flut331](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut331[i](I));
        return ret;
    };

    std::cerr << "\rLUT331   ";
    Ciphertext gin331 = 1 * gout179[0] + 2 * gout224[1] + 4 * gout330[0];
    std::vector<Ciphertext> gout331 = ctx.eval_lut_amortized(&gin331, lut331);

    long gin331clear = 1 * gout179clear[0] + 2 * gout224clear[1] + 4 * gout330clear[0];
    std::vector<long> gout331clear = fvec331(gin331clear);

    assert(ctx.decrypt(&gout331[0]) == gout331clear[0]);
    assert(ctx.decrypt(&gout331[1]) == gout331clear[1]);
    std::vector<RotationPoly> lut332;
    std::vector<long (*)(long)> flut332;
    auto lut332idx0 = [](long I) -> long {
        /* GATE 313 (LUT2 _1688_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut332.push_back(ctx.genrate_lut(lut332idx0));
    flut332.push_back(lut332idx0);

    auto lut332idx1 = [](long I) -> long {
        /* GATE 260 (LUT2 _1635_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut332.push_back(ctx.genrate_lut(lut332idx1));
    flut332.push_back(lut332idx1);

    auto fvec332 = [flut332](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut332[i](I));
        return ret;
    };

    std::cerr << "\rLUT332   ";
    Ciphertext gin332 = 1 * gout331[0] + 2 * gout165[1];
    std::vector<Ciphertext> gout332 = ctx.eval_lut_amortized(&gin332, lut332);

    long gin332clear = 1 * gout331clear[0] + 2 * gout165clear[1];
    std::vector<long> gout332clear = fvec332(gin332clear);

    assert(ctx.decrypt(&gout332[0]) == gout332clear[0]);
    assert(ctx.decrypt(&gout332[1]) == gout332clear[1]);
    std::vector<RotationPoly> lut333;
    std::vector<long (*)(long)> flut333;
    auto lut333idx0 = [](long I) -> long {
        /* GATE 203 (LUT3 _1578_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut333.push_back(ctx.genrate_lut(lut333idx0));
    flut333.push_back(lut333idx0);

    auto lut333idx1 = [](long I) -> long {
        /* GATE 168 (LUT3 _1543_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut333.push_back(ctx.genrate_lut(lut333idx1));
    flut333.push_back(lut333idx1);

    auto fvec333 = [flut333](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut333[i](I));
        return ret;
    };

    std::cerr << "\rLUT333   ";
    Ciphertext gin333 = 1 * gout200[0] + 2 * gout138[1] + 4 * gout330[1];
    std::vector<Ciphertext> gout333 = ctx.eval_lut_amortized(&gin333, lut333);

    long gin333clear = 1 * gout200clear[0] + 2 * gout138clear[1] + 4 * gout330clear[1];
    std::vector<long> gout333clear = fvec333(gin333clear);

    assert(ctx.decrypt(&gout333[0]) == gout333clear[0]);
    assert(ctx.decrypt(&gout333[1]) == gout333clear[1]);
    std::vector<RotationPoly> lut334;
    std::vector<long (*)(long)> flut334;
    auto lut334idx0 = [](long I) -> long {
        /* GATE 240 (LUT3 _1615_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut334.push_back(ctx.genrate_lut(lut334idx0));
    flut334.push_back(lut334idx0);

    auto lut334idx1 = [](long I) -> long {
        /* GATE 202 (LUT3 _1577_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut334.push_back(ctx.genrate_lut(lut334idx1));
    flut334.push_back(lut334idx1);

    auto fvec334 = [flut334](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut334[i](I));
        return ret;
    };

    std::cerr << "\rLUT334   ";
    Ciphertext gin334 = 1 * gout333[0] + 2 * gout323[1] + 4 * gout331[1];
    std::vector<Ciphertext> gout334 = ctx.eval_lut_amortized(&gin334, lut334);

    long gin334clear = 1 * gout333clear[0] + 2 * gout323clear[1] + 4 * gout331clear[1];
    std::vector<long> gout334clear = fvec334(gin334clear);

    assert(ctx.decrypt(&gout334[0]) == gout334clear[0]);
    assert(ctx.decrypt(&gout334[1]) == gout334clear[1]);
    std::vector<RotationPoly> lut335;
    std::vector<long (*)(long)> flut335;
    auto lut335idx0 = [](long I) -> long {
        /* GATE 281 (LUT3 _1656_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut335.push_back(ctx.genrate_lut(lut335idx0));
    flut335.push_back(lut335idx0);

    auto lut335idx1 = [](long I) -> long {
        /* GATE 239 (LUT3 _1614_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut335.push_back(ctx.genrate_lut(lut335idx1));
    flut335.push_back(lut335idx1);

    auto fvec335 = [flut335](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut335[i](I));
        return ret;
    };

    std::cerr << "\rLUT335   ";
    Ciphertext gin335 = 1 * gout334[0] + 2 * gout324[1] + 4 * gout332[1];
    std::vector<Ciphertext> gout335 = ctx.eval_lut_amortized(&gin335, lut335);

    long gin335clear = 1 * gout334clear[0] + 2 * gout324clear[1] + 4 * gout332clear[1];
    std::vector<long> gout335clear = fvec335(gin335clear);

    assert(ctx.decrypt(&gout335[0]) == gout335clear[0]);
    assert(ctx.decrypt(&gout335[1]) == gout335clear[1]);
    std::vector<RotationPoly> lut336;
    std::vector<long (*)(long)> flut336;
    auto lut336idx0 = [](long I) -> long {
        /* GATE 324 (LUT3 _1699_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut336.push_back(ctx.genrate_lut(lut336idx0));
    flut336.push_back(lut336idx0);

    auto lut336idx1 = [](long I) -> long {
        /* GATE 280 (LUT3 _1655_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut336.push_back(ctx.genrate_lut(lut336idx1));
    flut336.push_back(lut336idx1);

    auto fvec336 = [flut336](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut336[i](I));
        return ret;
    };

    std::cerr << "\rLUT336   ";
    Ciphertext gin336 = 1 * gout335[0] + 2 * gout325[1] + 4 * gout332[0];
    std::vector<Ciphertext> gout336 = ctx.eval_lut_amortized(&gin336, lut336);

    long gin336clear = 1 * gout335clear[0] + 2 * gout325clear[1] + 4 * gout332clear[0];
    std::vector<long> gout336clear = fvec336(gin336clear);

    assert(ctx.decrypt(&gout336[0]) == gout336clear[0]);
    assert(ctx.decrypt(&gout336[1]) == gout336clear[1]);
    std::vector<RotationPoly> lut337;
    std::vector<long (*)(long)> flut337;
    auto lut337idx0 = [](long I) -> long {
        /* GATE 406 (LUT2 _1781_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut337.push_back(ctx.genrate_lut(lut337idx0));
    flut337.push_back(lut337idx0);

    auto lut337idx1 = [](long I) -> long {
        /* GATE 323 (LUT2 _1698_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut337.push_back(ctx.genrate_lut(lut337idx1));
    flut337.push_back(lut337idx1);

    auto fvec337 = [flut337](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut337[i](I));
        return ret;
    };

    std::cerr << "\rLUT337   ";
    Ciphertext gin337 = 1 * gout336[0] + 2 * gout326[1];
    std::vector<Ciphertext> gout337 = ctx.eval_lut_amortized(&gin337, lut337);

    long gin337clear = 1 * gout336clear[0] + 2 * gout326clear[1];
    std::vector<long> gout337clear = fvec337(gin337clear);

    assert(ctx.decrypt(&gout337[0]) == gout337clear[0]);
    assert(ctx.decrypt(&gout337[1]) == gout337clear[1]);
    std::vector<RotationPoly> lut338;
    std::vector<long (*)(long)> flut338;
    auto lut338idx0 = [](long I) -> long {
        /* GATE 367 (LUT2 _1742_ INIT 0x6 PERM 10) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut338.push_back(ctx.genrate_lut(lut338idx0));
    flut338.push_back(lut338idx0);

    auto fvec338 = [flut338](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut338[i](I));
        return ret;
    };

    std::cerr << "\rLUT338   ";
    Ciphertext gin338 = 1 * gout337[0] + 2 * gout327[1];
    std::vector<Ciphertext> gout338 = ctx.eval_lut_amortized(&gin338, lut338);

    long gin338clear = 1 * gout337clear[0] + 2 * gout327clear[1];
    std::vector<long> gout338clear = fvec338(gin338clear);

    assert(ctx.decrypt(&gout338[0]) == gout338clear[0]);
    std::vector<RotationPoly> lut339;
    std::vector<long (*)(long)> flut339;
    auto lut339idx0 = [](long I) -> long {
        /* GATE 201 (LUT3 _1576_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut339.push_back(ctx.genrate_lut(lut339idx0));
    flut339.push_back(lut339idx0);

    auto lut339idx1 = [](long I) -> long {
        /* GATE 166 (LUT3 _1541_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut339.push_back(ctx.genrate_lut(lut339idx1));
    flut339.push_back(lut339idx1);

    auto fvec339 = [flut339](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut339[i](I));
        return ret;
    };

    std::cerr << "\rLUT339   ";
    Ciphertext gin339 = 1 * gout220[0] + 2 * gout333[1] + 4 * gout218[1];
    std::vector<Ciphertext> gout339 = ctx.eval_lut_amortized(&gin339, lut339);

    long gin339clear = 1 * gout220clear[0] + 2 * gout333clear[1] + 4 * gout218clear[1];
    std::vector<long> gout339clear = fvec339(gin339clear);

    assert(ctx.decrypt(&gout339[0]) == gout339clear[0]);
    assert(ctx.decrypt(&gout339[1]) == gout339clear[1]);
    std::vector<RotationPoly> lut340;
    std::vector<long (*)(long)> flut340;
    auto lut340idx0 = [](long I) -> long {
        /* GATE 238 (LUT3 _1613_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut340.push_back(ctx.genrate_lut(lut340idx0));
    flut340.push_back(lut340idx0);

    auto lut340idx1 = [](long I) -> long {
        /* GATE 200 (LUT3 _1575_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut340.push_back(ctx.genrate_lut(lut340idx1));
    flut340.push_back(lut340idx1);

    auto fvec340 = [flut340](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut340[i](I));
        return ret;
    };

    std::cerr << "\rLUT340   ";
    Ciphertext gin340 = 1 * gout339[0] + 2 * gout334[1] + 4 * gout219[1];
    std::vector<Ciphertext> gout340 = ctx.eval_lut_amortized(&gin340, lut340);

    long gin340clear = 1 * gout339clear[0] + 2 * gout334clear[1] + 4 * gout219clear[1];
    std::vector<long> gout340clear = fvec340(gin340clear);

    assert(ctx.decrypt(&gout340[0]) == gout340clear[0]);
    assert(ctx.decrypt(&gout340[1]) == gout340clear[1]);
    std::vector<RotationPoly> lut341;
    std::vector<long (*)(long)> flut341;
    auto lut341idx0 = [](long I) -> long {
        /* GATE 279 (LUT3 _1654_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut341.push_back(ctx.genrate_lut(lut341idx0));
    flut341.push_back(lut341idx0);

    auto lut341idx1 = [](long I) -> long {
        /* GATE 237 (LUT3 _1612_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut341.push_back(ctx.genrate_lut(lut341idx1));
    flut341.push_back(lut341idx1);

    auto fvec341 = [flut341](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut341[i](I));
        return ret;
    };

    std::cerr << "\rLUT341   ";
    Ciphertext gin341 = 1 * gout340[0] + 2 * gout335[1] + 4 * gout219[0];
    std::vector<Ciphertext> gout341 = ctx.eval_lut_amortized(&gin341, lut341);

    long gin341clear = 1 * gout340clear[0] + 2 * gout335clear[1] + 4 * gout219clear[0];
    std::vector<long> gout341clear = fvec341(gin341clear);

    assert(ctx.decrypt(&gout341[0]) == gout341clear[0]);
    assert(ctx.decrypt(&gout341[1]) == gout341clear[1]);
    std::vector<RotationPoly> lut342;
    std::vector<long (*)(long)> flut342;
    auto lut342idx0 = [](long I) -> long {
        /* GATE 322 (LUT2 _1697_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut342.push_back(ctx.genrate_lut(lut342idx0));
    flut342.push_back(lut342idx0);

    auto lut342idx1 = [](long I) -> long {
        /* GATE 278 (LUT2 _1653_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut342.push_back(ctx.genrate_lut(lut342idx1));
    flut342.push_back(lut342idx1);

    auto fvec342 = [flut342](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut342[i](I));
        return ret;
    };

    std::cerr << "\rLUT342   ";
    Ciphertext gin342 = 1 * gout341[0] + 2 * gout336[1];
    std::vector<Ciphertext> gout342 = ctx.eval_lut_amortized(&gin342, lut342);

    long gin342clear = 1 * gout341clear[0] + 2 * gout336clear[1];
    std::vector<long> gout342clear = fvec342(gin342clear);

    assert(ctx.decrypt(&gout342[0]) == gout342clear[0]);
    assert(ctx.decrypt(&gout342[1]) == gout342clear[1]);
    std::vector<RotationPoly> lut343;
    std::vector<long (*)(long)> flut343;
    auto lut343idx0 = [](long I) -> long {
        /* GATE 366 (LUT2 _1741_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut343.push_back(ctx.genrate_lut(lut343idx0));
    flut343.push_back(lut343idx0);

    auto lut343idx1 = [](long I) -> long {
        /* GATE 321 (LUT2 _1696_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut343.push_back(ctx.genrate_lut(lut343idx1));
    flut343.push_back(lut343idx1);

    auto fvec343 = [flut343](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut343[i](I));
        return ret;
    };

    std::cerr << "\rLUT343   ";
    Ciphertext gin343 = 1 * gout342[0] + 2 * gout337[1];
    std::vector<Ciphertext> gout343 = ctx.eval_lut_amortized(&gin343, lut343);

    long gin343clear = 1 * gout342clear[0] + 2 * gout337clear[1];
    std::vector<long> gout343clear = fvec343(gin343clear);

    assert(ctx.decrypt(&gout343[0]) == gout343clear[0]);
    assert(ctx.decrypt(&gout343[1]) == gout343clear[1]);
    std::vector<RotationPoly> lut344;
    std::vector<long (*)(long)> flut344;
    auto lut344idx0 = [](long I) -> long {
        /* GATE 199 (LUT3 _1574_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut344.push_back(ctx.genrate_lut(lut344idx0));
    flut344.push_back(lut344idx0);

    auto lut344idx1 = [](long I) -> long {
        /* GATE 164 (LUT3 _1539_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut344.push_back(ctx.genrate_lut(lut344idx1));
    flut344.push_back(lut344idx1);

    auto fvec344 = [flut344](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut344[i](I));
        return ret;
    };

    std::cerr << "\rLUT344   ";
    Ciphertext gin344 = 1 * gout221[0] + 2 * gout339[1] + 4 * gout215[1];
    std::vector<Ciphertext> gout344 = ctx.eval_lut_amortized(&gin344, lut344);

    long gin344clear = 1 * gout221clear[0] + 2 * gout339clear[1] + 4 * gout215clear[1];
    std::vector<long> gout344clear = fvec344(gin344clear);

    assert(ctx.decrypt(&gout344[0]) == gout344clear[0]);
    assert(ctx.decrypt(&gout344[1]) == gout344clear[1]);
    std::vector<RotationPoly> lut345;
    std::vector<long (*)(long)> flut345;
    auto lut345idx0 = [](long I) -> long {
        /* GATE 236 (LUT3 _1611_ INIT 0x2b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut345.push_back(ctx.genrate_lut(lut345idx0));
    flut345.push_back(lut345idx0);

    auto lut345idx1 = [](long I) -> long {
        /* GATE 198 (LUT3 _1573_ INIT 0x69 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut345.push_back(ctx.genrate_lut(lut345idx1));
    flut345.push_back(lut345idx1);

    auto fvec345 = [flut345](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut345[i](I));
        return ret;
    };

    std::cerr << "\rLUT345   ";
    Ciphertext gin345 = 1 * gout344[0] + 2 * gout340[1] + 4 * gout215[0];
    std::vector<Ciphertext> gout345 = ctx.eval_lut_amortized(&gin345, lut345);

    long gin345clear = 1 * gout344clear[0] + 2 * gout340clear[1] + 4 * gout215clear[0];
    std::vector<long> gout345clear = fvec345(gin345clear);

    assert(ctx.decrypt(&gout345[0]) == gout345clear[0]);
    assert(ctx.decrypt(&gout345[1]) == gout345clear[1]);
    std::vector<RotationPoly> lut346;
    std::vector<long (*)(long)> flut346;
    auto lut346idx0 = [](long I) -> long {
        /* GATE 277 (LUT2 _1652_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut346.push_back(ctx.genrate_lut(lut346idx0));
    flut346.push_back(lut346idx0);

    auto lut346idx1 = [](long I) -> long {
        /* GATE 235 (LUT2 _1610_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut346.push_back(ctx.genrate_lut(lut346idx1));
    flut346.push_back(lut346idx1);

    auto fvec346 = [flut346](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut346[i](I));
        return ret;
    };

    std::cerr << "\rLUT346   ";
    Ciphertext gin346 = 1 * gout345[0] + 2 * gout341[1];
    std::vector<Ciphertext> gout346 = ctx.eval_lut_amortized(&gin346, lut346);

    long gin346clear = 1 * gout345clear[0] + 2 * gout341clear[1];
    std::vector<long> gout346clear = fvec346(gin346clear);

    assert(ctx.decrypt(&gout346[0]) == gout346clear[0]);
    assert(ctx.decrypt(&gout346[1]) == gout346clear[1]);
    std::vector<RotationPoly> lut347;
    std::vector<long (*)(long)> flut347;
    auto lut347idx0 = [](long I) -> long {
        /* GATE 320 (LUT2 _1695_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut347.push_back(ctx.genrate_lut(lut347idx0));
    flut347.push_back(lut347idx0);

    auto lut347idx1 = [](long I) -> long {
        /* GATE 276 (LUT2 _1651_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut347.push_back(ctx.genrate_lut(lut347idx1));
    flut347.push_back(lut347idx1);

    auto fvec347 = [flut347](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut347[i](I));
        return ret;
    };

    std::cerr << "\rLUT347   ";
    Ciphertext gin347 = 1 * gout346[0] + 2 * gout342[1];
    std::vector<Ciphertext> gout347 = ctx.eval_lut_amortized(&gin347, lut347);

    long gin347clear = 1 * gout346clear[0] + 2 * gout342clear[1];
    std::vector<long> gout347clear = fvec347(gin347clear);

    assert(ctx.decrypt(&gout347[0]) == gout347clear[0]);
    assert(ctx.decrypt(&gout347[1]) == gout347clear[1]);
    std::vector<RotationPoly> lut348;
    std::vector<long (*)(long)> flut348;
    auto lut348idx0 = [](long I) -> long {
        /* GATE 197 (LUT2 _1572_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut348.push_back(ctx.genrate_lut(lut348idx0));
    flut348.push_back(lut348idx0);

    auto lut348idx1 = [](long I) -> long {
        /* GATE 162 (LUT2 _1537_ INIT 0x9 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut348.push_back(ctx.genrate_lut(lut348idx1));
    flut348.push_back(lut348idx1);

    auto fvec348 = [flut348](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut348[i](I));
        return ret;
    };

    std::cerr << "\rLUT348   ";
    Ciphertext gin348 = 1 * gout243[0] + 2 * gout344[1];
    std::vector<Ciphertext> gout348 = ctx.eval_lut_amortized(&gin348, lut348);

    long gin348clear = 1 * gout243clear[0] + 2 * gout344clear[1];
    std::vector<long> gout348clear = fvec348(gin348clear);

    assert(ctx.decrypt(&gout348[0]) == gout348clear[0]);
    assert(ctx.decrypt(&gout348[1]) == gout348clear[1]);
    std::vector<RotationPoly> lut349;
    std::vector<long (*)(long)> flut349;
    auto lut349idx0 = [](long I) -> long {
        /* GATE 234 (LUT2 _1609_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut349.push_back(ctx.genrate_lut(lut349idx0));
    flut349.push_back(lut349idx0);

    auto lut349idx1 = [](long I) -> long {
        /* GATE 196 (LUT2 _1571_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut349.push_back(ctx.genrate_lut(lut349idx1));
    flut349.push_back(lut349idx1);

    auto fvec349 = [flut349](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut349[i](I));
        return ret;
    };

    std::cerr << "\rLUT349   ";
    Ciphertext gin349 = 1 * gout348[0] + 2 * gout345[1];
    std::vector<Ciphertext> gout349 = ctx.eval_lut_amortized(&gin349, lut349);

    long gin349clear = 1 * gout348clear[0] + 2 * gout345clear[1];
    std::vector<long> gout349clear = fvec349(gin349clear);

    assert(ctx.decrypt(&gout349[0]) == gout349clear[0]);
    assert(ctx.decrypt(&gout349[1]) == gout349clear[1]);
    std::vector<RotationPoly> lut350;
    std::vector<long (*)(long)> flut350;
    auto lut350idx0 = [](long I) -> long {
        /* GATE 275 (LUT2 _1650_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut350.push_back(ctx.genrate_lut(lut350idx0));
    flut350.push_back(lut350idx0);

    auto lut350idx1 = [](long I) -> long {
        /* GATE 233 (LUT2 _1608_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut350.push_back(ctx.genrate_lut(lut350idx1));
    flut350.push_back(lut350idx1);

    auto fvec350 = [flut350](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut350[i](I));
        return ret;
    };

    std::cerr << "\rLUT350   ";
    Ciphertext gin350 = 1 * gout349[0] + 2 * gout346[1];
    std::vector<Ciphertext> gout350 = ctx.eval_lut_amortized(&gin350, lut350);

    long gin350clear = 1 * gout349clear[0] + 2 * gout346clear[1];
    std::vector<long> gout350clear = fvec350(gin350clear);

    assert(ctx.decrypt(&gout350[0]) == gout350clear[0]);
    assert(ctx.decrypt(&gout350[1]) == gout350clear[1]);
    std::vector<RotationPoly> lut351;
    std::vector<long (*)(long)> flut351;
    auto lut351idx0 = [](long I) -> long {
        /* GATE 195 (LUT2 _1570_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut351.push_back(ctx.genrate_lut(lut351idx0));
    flut351.push_back(lut351idx0);

    auto lut351idx1 = [](long I) -> long {
        /* GATE 160 (LUT2 _1535_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut351.push_back(ctx.genrate_lut(lut351idx1));
    flut351.push_back(lut351idx1);

    auto fvec351 = [flut351](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut351[i](I));
        return ret;
    };

    std::cerr << "\rLUT351   ";
    Ciphertext gin351 = 1 * gout244[0] + 2 * gout348[1];
    std::vector<Ciphertext> gout351 = ctx.eval_lut_amortized(&gin351, lut351);

    long gin351clear = 1 * gout244clear[0] + 2 * gout348clear[1];
    std::vector<long> gout351clear = fvec351(gin351clear);

    assert(ctx.decrypt(&gout351[0]) == gout351clear[0]);
    assert(ctx.decrypt(&gout351[1]) == gout351clear[1]);
    std::vector<RotationPoly> lut352;
    std::vector<long (*)(long)> flut352;
    auto lut352idx0 = [](long I) -> long {
        /* GATE 232 (LUT2 _1607_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut352.push_back(ctx.genrate_lut(lut352idx0));
    flut352.push_back(lut352idx0);

    auto lut352idx1 = [](long I) -> long {
        /* GATE 194 (LUT2 _1569_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut352.push_back(ctx.genrate_lut(lut352idx1));
    flut352.push_back(lut352idx1);

    auto fvec352 = [flut352](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut352[i](I));
        return ret;
    };

    std::cerr << "\rLUT352   ";
    Ciphertext gin352 = 1 * gout351[0] + 2 * gout349[1];
    std::vector<Ciphertext> gout352 = ctx.eval_lut_amortized(&gin352, lut352);

    long gin352clear = 1 * gout351clear[0] + 2 * gout349clear[1];
    std::vector<long> gout352clear = fvec352(gin352clear);

    assert(ctx.decrypt(&gout352[0]) == gout352clear[0]);
    assert(ctx.decrypt(&gout352[1]) == gout352clear[1]);
    std::vector<RotationPoly> lut353;
    std::vector<long (*)(long)> flut353;
    auto lut353idx0 = [](long I) -> long {
        /* GATE 193 (LUT3 _1568_ INIT 0x17 PERM 201) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut353.push_back(ctx.genrate_lut(lut353idx0));
    flut353.push_back(lut353idx0);

    auto lut353idx1 = [](long I) -> long {
        /* GATE 158 (LUT2 _1533_ INIT 0x6 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut353.push_back(ctx.genrate_lut(lut353idx1));
    flut353.push_back(lut353idx1);

    auto fvec353 = [flut353](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut353[i](I));
        return ret;
    };

    std::cerr << "\rLUT353   ";
    Ciphertext gin353 = 1 * gout245[0] + 2 * gout351[1] + 4 * gout247[0];
    std::vector<Ciphertext> gout353 = ctx.eval_lut_amortized(&gin353, lut353);

    long gin353clear = 1 * gout245clear[0] + 2 * gout351clear[1] + 4 * gout247clear[0];
    std::vector<long> gout353clear = fvec353(gin353clear);

    assert(ctx.decrypt(&gout353[0]) == gout353clear[0]);
    assert(ctx.decrypt(&gout353[1]) == gout353clear[1]);
    std::vector<RotationPoly> lut354;
    std::vector<long (*)(long)> flut354;
    auto lut354idx0 = [](long I) -> long {
        /* GATE 192 (LUT2 _1567_ INIT 0x8 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut354.push_back(ctx.genrate_lut(lut354idx0));
    flut354.push_back(lut354idx0);

    auto fvec354 = [flut354](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut354[i](I));
        return ret;
    };

    std::cerr << "\rLUT354   ";
    Ciphertext gin354 = 1 * gout246[0] + 2 * gout353[1];
    std::vector<Ciphertext> gout354 = ctx.eval_lut_amortized(&gin354, lut354);

    long gin354clear = 1 * gout246clear[0] + 2 * gout353clear[1];
    std::vector<long> gout354clear = fvec354(gin354clear);

    assert(ctx.decrypt(&gout354[0]) == gout354clear[0]);
    std::vector<RotationPoly> lut355;
    std::vector<long (*)(long)> flut355;
    auto lut355idx0 = [](long I) -> long {
        /* GATE 231 (LUT3 _1606_ INIT 0xd0 PERM 102) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut355.push_back(ctx.genrate_lut(lut355idx0));
    flut355.push_back(lut355idx0);

    auto lut355idx1 = [](long I) -> long {
        /* GATE 191 (LUT2 _1566_ INIT 0x4 PERM 01) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut355.push_back(ctx.genrate_lut(lut355idx1));
    flut355.push_back(lut355idx1);

    auto fvec355 = [flut355](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut355[i](I));
        return ret;
    };

    std::cerr << "\rLUT355   ";
    Ciphertext gin355 = 1 * gout354[0] + 2 * gout353[0] + 4 * gout352[1];
    std::vector<Ciphertext> gout355 = ctx.eval_lut_amortized(&gin355, lut355);

    long gin355clear = 1 * gout354clear[0] + 2 * gout353clear[0] + 4 * gout352clear[1];
    std::vector<long> gout355clear = fvec355(gin355clear);

    assert(ctx.decrypt(&gout355[0]) == gout355clear[0]);
    assert(ctx.decrypt(&gout355[1]) == gout355clear[1]);
    std::vector<RotationPoly> lut356;
    std::vector<long (*)(long)> flut356;
    auto lut356idx0 = [](long I) -> long {
        /* GATE 274 (LUT3 _1649_ INIT 0xe0 PERM 102) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut356.push_back(ctx.genrate_lut(lut356idx0));
    flut356.push_back(lut356idx0);

    auto lut356idx1 = [](long I) -> long {
        /* GATE 230 (LUT2 _1605_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut356.push_back(ctx.genrate_lut(lut356idx1));
    flut356.push_back(lut356idx1);

    auto fvec356 = [flut356](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut356[i](I));
        return ret;
    };

    std::cerr << "\rLUT356   ";
    Ciphertext gin356 = 1 * gout355[0] + 2 * gout352[0] + 4 * gout350[1];
    std::vector<Ciphertext> gout356 = ctx.eval_lut_amortized(&gin356, lut356);

    long gin356clear = 1 * gout355clear[0] + 2 * gout352clear[0] + 4 * gout350clear[1];
    std::vector<long> gout356clear = fvec356(gin356clear);

    assert(ctx.decrypt(&gout356[0]) == gout356clear[0]);
    assert(ctx.decrypt(&gout356[1]) == gout356clear[1]);
    std::vector<RotationPoly> lut357;
    std::vector<long (*)(long)> flut357;
    auto lut357idx0 = [](long I) -> long {
        /* GATE 319 (LUT3 _1694_ INIT 0xe0 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut357.push_back(ctx.genrate_lut(lut357idx0));
    flut357.push_back(lut357idx0);

    auto lut357idx1 = [](long I) -> long {
        /* GATE 273 (LUT2 _1648_ INIT 0x1 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut357.push_back(ctx.genrate_lut(lut357idx1));
    flut357.push_back(lut357idx1);

    auto fvec357 = [flut357](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut357[i](I));
        return ret;
    };

    std::cerr << "\rLUT357   ";
    Ciphertext gin357 = 1 * gout350[0] + 2 * gout356[0] + 4 * gout347[1];
    std::vector<Ciphertext> gout357 = ctx.eval_lut_amortized(&gin357, lut357);

    long gin357clear = 1 * gout350clear[0] + 2 * gout356clear[0] + 4 * gout347clear[1];
    std::vector<long> gout357clear = fvec357(gin357clear);

    assert(ctx.decrypt(&gout357[0]) == gout357clear[0]);
    assert(ctx.decrypt(&gout357[1]) == gout357clear[1]);
    std::vector<RotationPoly> lut358;
    std::vector<long (*)(long)> flut358;
    auto lut358idx0 = [](long I) -> long {
        /* GATE 365 (LUT3 _1740_ INIT 0xe0 PERM 102) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut358.push_back(ctx.genrate_lut(lut358idx0));
    flut358.push_back(lut358idx0);

    auto lut358idx1 = [](long I) -> long {
        /* GATE 318 (LUT2 _1693_ INIT 0x1 PERM 01) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut358.push_back(ctx.genrate_lut(lut358idx1));
    flut358.push_back(lut358idx1);

    auto fvec358 = [flut358](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut358[i](I));
        return ret;
    };

    std::cerr << "\rLUT358   ";
    Ciphertext gin358 = 1 * gout357[0] + 2 * gout347[0] + 4 * gout343[1];
    std::vector<Ciphertext> gout358 = ctx.eval_lut_amortized(&gin358, lut358);

    long gin358clear = 1 * gout357clear[0] + 2 * gout347clear[0] + 4 * gout343clear[1];
    std::vector<long> gout358clear = fvec358(gin358clear);

    assert(ctx.decrypt(&gout358[0]) == gout358clear[0]);
    assert(ctx.decrypt(&gout358[1]) == gout358clear[1]);
    std::vector<RotationPoly> lut359;
    std::vector<long (*)(long)> flut359;
    auto lut359idx0 = [](long I) -> long {
        /* GATE 412 (LUT3 _1787_ INIT 0xe0 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut359.push_back(ctx.genrate_lut(lut359idx0));
    flut359.push_back(lut359idx0);

    auto lut359idx1 = [](long I) -> long {
        /* GATE 364 (LUT2 _1739_ INIT 0x1 PERM 10) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut359.push_back(ctx.genrate_lut(lut359idx1));
    flut359.push_back(lut359idx1);

    auto fvec359 = [flut359](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut359[i](I));
        return ret;
    };

    std::cerr << "\rLUT359   ";
    Ciphertext gin359 = 1 * gout343[0] + 2 * gout358[0] + 4 * gout338[0];
    std::vector<Ciphertext> gout359 = ctx.eval_lut_amortized(&gin359, lut359);

    long gin359clear = 1 * gout343clear[0] + 2 * gout358clear[0] + 4 * gout338clear[0];
    std::vector<long> gout359clear = fvec359(gin359clear);

    assert(ctx.decrypt(&gout359[0]) == gout359clear[0]);
    assert(ctx.decrypt(&gout359[1]) == gout359clear[1]);
    std::vector<RotationPoly> lut360;
    std::vector<long (*)(long)> flut360;
    auto lut360idx0 = [](long I) -> long {
        /* GATE 411 (LUT3 _1786_ INIT 0x7 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut360.push_back(ctx.genrate_lut(lut360idx0));
    flut360.push_back(lut360idx0);

    auto fvec360 = [flut360](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut360[i](I));
        return ret;
    };

    std::cerr << "\rLUT360   ";
    Ciphertext gin360 = 1 * gout337[0] + 2 * gout327[1] + 4 * gout359[0];
    std::vector<Ciphertext> gout360 = ctx.eval_lut_amortized(&gin360, lut360);

    long gin360clear = 1 * gout337clear[0] + 2 * gout327clear[1] + 4 * gout359clear[0];
    std::vector<long> gout360clear = fvec360(gin360clear);

    assert(ctx.decrypt(&gout360[0]) == gout360clear[0]);
    std::vector<RotationPoly> lut361;
    std::vector<long (*)(long)> flut361;
    auto lut361idx0 = [](long I) -> long {
        /* GATE 410 (LUT3 _1785_ INIT 0x90 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut361.push_back(ctx.genrate_lut(lut361idx0));
    flut361.push_back(lut361idx0);

    auto fvec361 = [flut361](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut361[i](I));
        return ret;
    };

    std::cerr << "\rLUT361   ";
    Ciphertext gin361 = 1 * gout360[0] + 2 * gout328[0] + 4 * gout249[0];
    std::vector<Ciphertext> gout361 = ctx.eval_lut_amortized(&gin361, lut361);

    long gin361clear = 1 * gout360clear[0] + 2 * gout328clear[0] + 4 * gout249clear[0];
    std::vector<long> gout361clear = fvec361(gin361clear);

    assert(ctx.decrypt(&gout361[0]) == gout361clear[0]);
    std::vector<RotationPoly> lut362;
    std::vector<long (*)(long)> flut362;
    auto lut362idx0 = [](long I) -> long {
        /* GATE 409 (LUT3 _1784_ INIT 0xfe PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut362.push_back(ctx.genrate_lut(lut362idx0));
    flut362.push_back(lut362idx0);

    auto fvec362 = [flut362](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut362[i](I));
        return ret;
    };

    std::cerr << "\rLUT362   ";
    Ciphertext gin362 = 1 * gout361[0] + 2 * gout310[0] + 4 * gout131[0];
    std::vector<Ciphertext> gout362 = ctx.eval_lut_amortized(&gin362, lut362);

    long gin362clear = 1 * gout361clear[0] + 2 * gout310clear[0] + 4 * gout131clear[0];
    std::vector<long> gout362clear = fvec362(gin362clear);

    assert(ctx.decrypt(&gout362[0]) == gout362clear[0]);
    std::vector<RotationPoly> lut363;
    std::vector<long (*)(long)> flut363;
    auto lut363idx0 = [](long I) -> long {
        /* GATE 363 (LUT3 _1738_ INIT 0x90 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut363.push_back(ctx.genrate_lut(lut363idx0));
    flut363.push_back(lut363idx0);

    auto fvec363 = [flut363](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut363[i](I));
        return ret;
    };

    std::cerr << "\rLUT363   ";
    Ciphertext gin363 = 1 * gout359[1] + 2 * gout338[0] + 4 * gout249[0];
    std::vector<Ciphertext> gout363 = ctx.eval_lut_amortized(&gin363, lut363);

    long gin363clear = 1 * gout359clear[1] + 2 * gout338clear[0] + 4 * gout249clear[0];
    std::vector<long> gout363clear = fvec363(gin363clear);

    assert(ctx.decrypt(&gout363[0]) == gout363clear[0]);
    std::vector<RotationPoly> lut364;
    std::vector<long (*)(long)> flut364;
    auto lut364idx0 = [](long I) -> long {
        /* GATE 362 (LUT3 _1737_ INIT 0xfe PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut364.push_back(ctx.genrate_lut(lut364idx0));
    flut364.push_back(lut364idx0);

    auto fvec364 = [flut364](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut364[i](I));
        return ret;
    };

    std::cerr << "\rLUT364   ";
    Ciphertext gin364 = 1 * gout363[0] + 2 * gout307[0] + 4 * gout131[0];
    std::vector<Ciphertext> gout364 = ctx.eval_lut_amortized(&gin364, lut364);

    long gin364clear = 1 * gout363clear[0] + 2 * gout307clear[0] + 4 * gout131clear[0];
    std::vector<long> gout364clear = fvec364(gin364clear);

    assert(ctx.decrypt(&gout364[0]) == gout364clear[0]);
    std::vector<RotationPoly> lut365;
    std::vector<long (*)(long)> flut365;
    auto lut365idx0 = [](long I) -> long {
        /* GATE 317 (LUT3 _1692_ INIT 0x90 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut365.push_back(ctx.genrate_lut(lut365idx0));
    flut365.push_back(lut365idx0);

    auto fvec365 = [flut365](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut365[i](I));
        return ret;
    };

    std::cerr << "\rLUT365   ";
    Ciphertext gin365 = 1 * gout358[1] + 2 * gout343[1] + 4 * gout249[0];
    std::vector<Ciphertext> gout365 = ctx.eval_lut_amortized(&gin365, lut365);

    long gin365clear = 1 * gout358clear[1] + 2 * gout343clear[1] + 4 * gout249clear[0];
    std::vector<long> gout365clear = fvec365(gin365clear);

    assert(ctx.decrypt(&gout365[0]) == gout365clear[0]);
    std::vector<RotationPoly> lut366;
    std::vector<long (*)(long)> flut366;
    auto lut366idx0 = [](long I) -> long {
        /* GATE 316 (LUT3 _1691_ INIT 0xfe PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut366.push_back(ctx.genrate_lut(lut366idx0));
    flut366.push_back(lut366idx0);

    auto fvec366 = [flut366](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut366[i](I));
        return ret;
    };

    std::cerr << "\rLUT366   ";
    Ciphertext gin366 = 1 * gout365[0] + 2 * gout304[0] + 4 * gout131[0];
    std::vector<Ciphertext> gout366 = ctx.eval_lut_amortized(&gin366, lut366);

    long gin366clear = 1 * gout365clear[0] + 2 * gout304clear[0] + 4 * gout131clear[0];
    std::vector<long> gout366clear = fvec366(gin366clear);

    assert(ctx.decrypt(&gout366[0]) == gout366clear[0]);
    std::vector<RotationPoly> lut367;
    std::vector<long (*)(long)> flut367;
    auto lut367idx0 = [](long I) -> long {
        /* GATE 272 (LUT3 _1647_ INIT 0x90 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut367.push_back(ctx.genrate_lut(lut367idx0));
    flut367.push_back(lut367idx0);

    auto fvec367 = [flut367](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut367[i](I));
        return ret;
    };

    std::cerr << "\rLUT367   ";
    Ciphertext gin367 = 1 * gout357[1] + 2 * gout347[1] + 4 * gout249[0];
    std::vector<Ciphertext> gout367 = ctx.eval_lut_amortized(&gin367, lut367);

    long gin367clear = 1 * gout357clear[1] + 2 * gout347clear[1] + 4 * gout249clear[0];
    std::vector<long> gout367clear = fvec367(gin367clear);

    assert(ctx.decrypt(&gout367[0]) == gout367clear[0]);
    std::vector<RotationPoly> lut368;
    std::vector<long (*)(long)> flut368;
    auto lut368idx0 = [](long I) -> long {
        /* GATE 271 (LUT3 _1646_ INIT 0xfe PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut368.push_back(ctx.genrate_lut(lut368idx0));
    flut368.push_back(lut368idx0);

    auto fvec368 = [flut368](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut368[i](I));
        return ret;
    };

    std::cerr << "\rLUT368   ";
    Ciphertext gin368 = 1 * gout367[0] + 2 * gout302[0] + 4 * gout131[0];
    std::vector<Ciphertext> gout368 = ctx.eval_lut_amortized(&gin368, lut368);

    long gin368clear = 1 * gout367clear[0] + 2 * gout302clear[0] + 4 * gout131clear[0];
    std::vector<long> gout368clear = fvec368(gin368clear);

    assert(ctx.decrypt(&gout368[0]) == gout368clear[0]);
    std::vector<RotationPoly> lut369;
    std::vector<long (*)(long)> flut369;
    auto lut369idx0 = [](long I) -> long {
        /* GATE 229 (LUT3 _1604_ INIT 0x90 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut369.push_back(ctx.genrate_lut(lut369idx0));
    flut369.push_back(lut369idx0);

    auto fvec369 = [flut369](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut369[i](I));
        return ret;
    };

    std::cerr << "\rLUT369   ";
    Ciphertext gin369 = 1 * gout356[1] + 2 * gout350[1] + 4 * gout249[0];
    std::vector<Ciphertext> gout369 = ctx.eval_lut_amortized(&gin369, lut369);

    long gin369clear = 1 * gout356clear[1] + 2 * gout350clear[1] + 4 * gout249clear[0];
    std::vector<long> gout369clear = fvec369(gin369clear);

    assert(ctx.decrypt(&gout369[0]) == gout369clear[0]);
    std::vector<RotationPoly> lut370;
    std::vector<long (*)(long)> flut370;
    auto lut370idx0 = [](long I) -> long {
        /* GATE 228 (LUT3 _1603_ INIT 0xfe PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut370.push_back(ctx.genrate_lut(lut370idx0));
    flut370.push_back(lut370idx0);

    auto fvec370 = [flut370](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut370[i](I));
        return ret;
    };

    std::cerr << "\rLUT370   ";
    Ciphertext gin370 = 1 * gout369[0] + 2 * gout308[0] + 4 * gout131[0];
    std::vector<Ciphertext> gout370 = ctx.eval_lut_amortized(&gin370, lut370);

    long gin370clear = 1 * gout369clear[0] + 2 * gout308clear[0] + 4 * gout131clear[0];
    std::vector<long> gout370clear = fvec370(gin370clear);

    assert(ctx.decrypt(&gout370[0]) == gout370clear[0]);
    std::vector<RotationPoly> lut371;
    std::vector<long (*)(long)> flut371;
    auto lut371idx0 = [](long I) -> long {
        /* GATE 190 (LUT3 _1565_ INIT 0x90 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut371.push_back(ctx.genrate_lut(lut371idx0));
    flut371.push_back(lut371idx0);

    auto fvec371 = [flut371](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut371[i](I));
        return ret;
    };

    std::cerr << "\rLUT371   ";
    Ciphertext gin371 = 1 * gout355[1] + 2 * gout352[1] + 4 * gout249[0];
    std::vector<Ciphertext> gout371 = ctx.eval_lut_amortized(&gin371, lut371);

    long gin371clear = 1 * gout355clear[1] + 2 * gout352clear[1] + 4 * gout249clear[0];
    std::vector<long> gout371clear = fvec371(gin371clear);

    assert(ctx.decrypt(&gout371[0]) == gout371clear[0]);
    std::vector<RotationPoly> lut372;
    std::vector<long (*)(long)> flut372;
    auto lut372idx0 = [](long I) -> long {
        /* GATE 189 (LUT3 _1564_ INIT 0xfe PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut372.push_back(ctx.genrate_lut(lut372idx0));
    flut372.push_back(lut372idx0);

    auto fvec372 = [flut372](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut372[i](I));
        return ret;
    };

    std::cerr << "\rLUT372   ";
    Ciphertext gin372 = 1 * gout371[0] + 2 * gout298[0] + 4 * gout131[0];
    std::vector<Ciphertext> gout372 = ctx.eval_lut_amortized(&gin372, lut372);

    long gin372clear = 1 * gout371clear[0] + 2 * gout298clear[0] + 4 * gout131clear[0];
    std::vector<long> gout372clear = fvec372(gin372clear);

    assert(ctx.decrypt(&gout372[0]) == gout372clear[0]);
    std::vector<RotationPoly> lut373;
    std::vector<long (*)(long)> flut373;
    auto lut373idx0 = [](long I) -> long {
        /* GATE 154 (LUT3 _1529_ INIT 0x90 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut373.push_back(ctx.genrate_lut(lut373idx0));
    flut373.push_back(lut373idx0);

    auto fvec373 = [flut373](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut373[i](I));
        return ret;
    };

    std::cerr << "\rLUT373   ";
    Ciphertext gin373 = 1 * gout248[0] + 2 * gout353[1] + 4 * gout249[0];
    std::vector<Ciphertext> gout373 = ctx.eval_lut_amortized(&gin373, lut373);

    long gin373clear = 1 * gout248clear[0] + 2 * gout353clear[1] + 4 * gout249clear[0];
    std::vector<long> gout373clear = fvec373(gin373clear);

    assert(ctx.decrypt(&gout373[0]) == gout373clear[0]);
    std::vector<RotationPoly> lut374;
    std::vector<long (*)(long)> flut374;
    auto lut374idx0 = [](long I) -> long {
        /* GATE 153 (LUT3 _1528_ INIT 0xfe PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut374.push_back(ctx.genrate_lut(lut374idx0));
    flut374.push_back(lut374idx0);

    auto fvec374 = [flut374](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut374[i](I));
        return ret;
    };

    std::cerr << "\rLUT374   ";
    Ciphertext gin374 = 1 * gout373[0] + 2 * gout295[0] + 4 * gout131[0];
    std::vector<Ciphertext> gout374 = ctx.eval_lut_amortized(&gin374, lut374);

    long gin374clear = 1 * gout373clear[0] + 2 * gout295clear[0] + 4 * gout131clear[0];
    std::vector<long> gout374clear = fvec374(gin374clear);

    assert(ctx.decrypt(&gout374[0]) == gout374clear[0]);
    std::cerr << "\r          \r";
    std::vector<long> out;
    out.push_back(ctx.decrypt(&gout264[0])); /* out0 */
    assert(ctx.decrypt(&gout264[0]) == gout264clear[0]);
    out.push_back(ctx.decrypt(&gout261[0])); /* out1 */
    assert(ctx.decrypt(&gout261[0]) == gout261clear[0]);
    out.push_back(ctx.decrypt(&gout259[0])); /* out2 */
    assert(ctx.decrypt(&gout259[0]) == gout259clear[0]);
    out.push_back(ctx.decrypt(&gout256[0])); /* out3 */
    assert(ctx.decrypt(&gout256[0]) == gout256clear[0]);
    out.push_back(ctx.decrypt(&gout279[0])); /* out4 */
    assert(ctx.decrypt(&gout279[0]) == gout279clear[0]);
    out.push_back(ctx.decrypt(&gout282[0])); /* out5 */
    assert(ctx.decrypt(&gout282[0]) == gout282clear[0]);
    out.push_back(ctx.decrypt(&gout286[0])); /* out6 */
    assert(ctx.decrypt(&gout286[0]) == gout286clear[0]);
    out.push_back(ctx.decrypt(&gout289[0])); /* out7 */
    assert(ctx.decrypt(&gout289[0]) == gout289clear[0]);
    out.push_back(ctx.decrypt(&gout293[0])); /* out8 */
    assert(ctx.decrypt(&gout293[0]) == gout293clear[0]);
    out.push_back(ctx.decrypt(&gout374[0])); /* out9 */
    assert(ctx.decrypt(&gout374[0]) == gout374clear[0]);
    out.push_back(ctx.decrypt(&gout372[0])); /* out10 */
    assert(ctx.decrypt(&gout372[0]) == gout372clear[0]);
    out.push_back(ctx.decrypt(&gout370[0])); /* out11 */
    assert(ctx.decrypt(&gout370[0]) == gout370clear[0]);
    out.push_back(ctx.decrypt(&gout368[0])); /* out12 */
    assert(ctx.decrypt(&gout368[0]) == gout368clear[0]);
    out.push_back(ctx.decrypt(&gout366[0])); /* out13 */
    assert(ctx.decrypt(&gout366[0]) == gout366clear[0]);
    out.push_back(ctx.decrypt(&gout364[0])); /* out14 */
    assert(ctx.decrypt(&gout364[0]) == gout364clear[0]);
    out.push_back(ctx.decrypt(&gout362[0])); /* out15 */
    assert(ctx.decrypt(&gout362[0]) == gout362clear[0]);
    return out;
}

int
main(void)
{
    /* setup */
    FHEContext ctx;
    long out;

    std::cout << "[+] ";
    ctx.generate_context(rlwe_hom_acc_scheme_C_11_NTT_amortized);
    ctx.set_default_message_encoding_type(partial_domain);

    /* LUT tests */
    std::cout << "[+] Testing LUT3" << std::endl;
    test_lut3(ctx);

    /* add4 tests *//*
    std::cout << "[+] Testing add4" << std::endl;
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            std::cerr << i << " + " << j;
            out = compose(test_add4_lut3fa(ctx, i, j));
            assert(out == i + j);

        }
    } */

    /* calculator tests */
    std::cout << "[+] Testing calculator" << std::endl;
    std::cout << "[>] 0 0 0" << std::endl;
    std::cout << "exp:    1111111111111111" << std::endl;
    out = compose(test_calculator_lut3fa(ctx, 0, 0, 0));
    std::cout << "lut3fa: " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 6 + 7" << std::endl;
    std::cout << "exp:    0000000000001101" << std::endl;
    out = compose(test_calculator_lut3fa(ctx, '+', 6, 7));
    std::cout << "lut3fa: " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 6 - 7" << std::endl;
    std::cout << "exp:    1111111111111111" << std::endl;
    out = compose(test_calculator_lut3fa(ctx, '-', 6, 7));
    std::cout << "lut3fa: " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 6 * 7" << std::endl;
    std::cout << "exp:    0000000000101010" << std::endl;
    out = compose(test_calculator_lut3fa(ctx, '*', 6, 7));
    std::cout << "lut3fa: " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 0xba + 0xbe" << std::endl;
    std::cout << "exp:    0000000101111000" << std::endl;
    out = compose(test_calculator_lut3fa(ctx, '+', 0xba, 0xbe));
    std::cout << "lut3fa: " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 0xba - 0xbe" << std::endl;
    std::cout << "exp:    1111111111111100" << std::endl;
    out = compose(test_calculator_lut3fa(ctx, '-', 0xba, 0xbe));
    std::cout << "lut3fa: " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 0xba * 0xbe" << std::endl;
    std::cout << "exp:    1000101000001100" << std::endl;
    out = compose(test_calculator_lut3fa(ctx, '*', 0xba, 0xbe));
    std::cout << "lut3fa: " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 0xffff + 0xffff" << std::endl;
    std::cout << "exp:    1111111111111110" << std::endl;
    out = compose(test_calculator_lut3fa(ctx, '+', 0xffff, 0xffff));
    std::cout << "lut3fa: " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 0xffff - 0xffff" << std::endl;
    std::cout << "exp:    0000000000000000" << std::endl;
    out = compose(test_calculator_lut3fa(ctx, '-', 0xffff, 0xffff));
    std::cout << "lut3fa: " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 0xffff * 0xffff" << std::endl;
    std::cout << "exp:    0000000000000001" << std::endl;
    out = compose(test_calculator_lut3fa(ctx, '*', 0xffff, 0xffff));
    std::cout << "lut3fa: " << std::bitset<16>(out) << std::endl;

    return 0;
}
