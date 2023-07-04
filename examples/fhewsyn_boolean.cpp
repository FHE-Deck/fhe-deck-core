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
    Ciphertext gin0 = 2 * ct_a3 + ct_b3;
    Ciphertext gout0 = ctx.eval_lut(&gin0, xor2);

    std::cerr << "\rLUT1   ";
    Ciphertext gin1 = 2 * ct_a2 + ct_b2;
    Ciphertext gout1 = ctx.eval_lut(&gin1, xor2);

    std::cerr << "\rLUT2   ";
    Ciphertext gin2 = 2 * ct_a2 + ct_b2;
    Ciphertext gout2 = ctx.eval_lut(&gin2, nand2);

    std::cerr << "\rLUT3   ";
    Ciphertext gin3 = 2 * ct_a0 + ct_b0;
    Ciphertext gout3 = ctx.eval_lut(&gin3, and2);

    std::cerr << "\rLUT4   ";
    Ciphertext gin4 = 2 * ct_a3 + ct_b3;
    Ciphertext gout4 = ctx.eval_lut(&gin4, nand2);

    std::cerr << "\rLUT5   ";
    Ciphertext gin5 = 2 * ct_a0 + ct_b0;
    Ciphertext gout5 = ctx.eval_lut(&gin5, xor2);

    std::cerr << "\rLUT6   ";
    Ciphertext gin6 = 2 * ct_a1 + ct_b1;
    Ciphertext gout6 = ctx.eval_lut(&gin6, nand2);

    std::cerr << "\rLUT7   ";
    Ciphertext gin7 = 2 * ct_a1 + ct_b1;
    Ciphertext gout7 = ctx.eval_lut(&gin7, xor2);

    std::cerr << "\rLUT8   ";
    Ciphertext gin8 = 2 * gout3 + gout7;
    Ciphertext gout8 = ctx.eval_lut(&gin8, xor2);

    std::cerr << "\rLUT9   ";
    Ciphertext gin9 = 2 * gout3 + gout7;
    Ciphertext gout9 = ctx.eval_lut(&gin9, nand2);

    std::cerr << "\rLUT10   ";
    Ciphertext gin10 = 2 * gout6 + gout9;
    Ciphertext gout10 = ctx.eval_lut(&gin10, nand2);

    std::cerr << "\rLUT11   ";
    Ciphertext gin11 = 2 * gout10 + gout1;
    Ciphertext gout11 = ctx.eval_lut(&gin11, xor2);

    std::cerr << "\rLUT12   ";
    Ciphertext gin12 = 2 * gout10 + gout1;
    Ciphertext gout12 = ctx.eval_lut(&gin12, nand2);

    std::cerr << "\rLUT13   ";
    Ciphertext gin13 = 2 * gout2 + gout12;
    Ciphertext gout13 = ctx.eval_lut(&gin13, nand2);

    std::cerr << "\rLUT14   ";
    Ciphertext gin14 = 2 * gout13 + gout0;
    Ciphertext gout14 = ctx.eval_lut(&gin14, xor2);

    std::cerr << "\rLUT15   ";
    Ciphertext gin15 = 2 * gout13 + gout0;
    Ciphertext gout15 = ctx.eval_lut(&gin15, nand2);

    std::cerr << "\rLUT16   ";
    Ciphertext gin16 = 2 * gout4 + gout15;
    Ciphertext gout16 = ctx.eval_lut(&gin16, nand2);

    std::cerr << "\r          \r";
    std::vector<long> out;
    out.push_back(ctx.decrypt(&gout5)); /* out0 */
    out.push_back(ctx.decrypt(&gout8)); /* out1 */
    out.push_back(ctx.decrypt(&gout11)); /* out2 */
    out.push_back(ctx.decrypt(&gout14)); /* out3 */
    out.push_back(ctx.decrypt(&gout16)); /* out4 */
    return out;
}

std::vector<long>
test_calculator_boolean(FHEContext& ctx, uint8_t op, uint16_t x, uint16_t y)
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
    Ciphertext gin0 = 2 * ct_y7 + ct_x1;
    Ciphertext gout0 = ctx.eval_lut(&gin0, and2);

    std::cerr << "\rLUT1   ";
    Ciphertext gin1 = 2 * ct_y7 + ct_x6;
    Ciphertext gout1 = ctx.eval_lut(&gin1, and2);

    std::cerr << "\rLUT2   ";
    Ciphertext gin2 = 2 * ct_y9 + ct_x0;
    Ciphertext gout2 = ctx.eval_lut(&gin2, and2);

    std::cerr << "\rLUT3   ";
    Ciphertext gin3 = 2 * ct_y2 + ct_x5;
    Ciphertext gout3 = ctx.eval_lut(&gin3, and2);

    std::cerr << "\rLUT4   ";
    Ciphertext gin4 = 2 * ct_y1 + ct_x13;
    Ciphertext gout4 = ctx.eval_lut(&gin4, and2);

    std::cerr << "\rINV5   ";
    Ciphertext gout5 = 1 - ct_y4;

    std::cerr << "\rLUT6   ";
    Ciphertext gin6 = 2 * ct_y0 + ct_x5;
    Ciphertext gout6 = ctx.eval_lut(&gin6, nand2);

    std::cerr << "\rLUT7   ";
    Ciphertext gin7 = 2 * ct_y8 + ct_x1;
    Ciphertext gout7 = ctx.eval_lut(&gin7, and2);

    std::cerr << "\rLUT8   ";
    Ciphertext gin8 = 2 * ct_y0 + ct_x1;
    Ciphertext gout8 = ctx.eval_lut(&gin8, and2);

    std::cerr << "\rLUT9   ";
    Ciphertext gin9 = 2 * ct_y5 + ct_x10;
    Ciphertext gout9 = ctx.eval_lut(&gin9, and2);

    std::cerr << "\rLUT10   ";
    Ciphertext gin10 = 2 * ct_y6 + ct_x9;
    Ciphertext gout10 = ctx.eval_lut(&gin10, and2);

    std::cerr << "\rLUT11   ";
    Ciphertext gin11 = 2 * ct_y2 + ct_x12;
    Ciphertext gout11 = ctx.eval_lut(&gin11, and2);

    std::cerr << "\rLUT12   ";
    Ciphertext gin12 = 2 * ct_y1 + ct_x0;
    Ciphertext gout12 = ctx.eval_lut(&gin12, and2);

    std::cerr << "\rLUT13   ";
    Ciphertext gin13 = 2 * ct_y15 + ct_x15;
    Ciphertext gout13 = ctx.eval_lut(&gin13, xor2);

    std::cerr << "\rLUT14   ";
    Ciphertext gin14 = 2 * ct_y6 + ct_x0;
    Ciphertext gout14 = ctx.eval_lut(&gin14, and2);

    std::cerr << "\rLUT15   ";
    Ciphertext gin15 = 2 * ct_y5 + ct_x9;
    Ciphertext gout15 = ctx.eval_lut(&gin15, and2);

    std::cerr << "\rLUT16   ";
    Ciphertext gin16 = 2 * ct_y3 + ct_x6;
    Ciphertext gout16 = ctx.eval_lut(&gin16, and2);

    std::cerr << "\rLUT17   ";
    Ciphertext gin17 = 2 * ct_y6 + ct_x6;
    Ciphertext gout17 = ctx.eval_lut(&gin17, and2);

    std::cerr << "\rLUT18   ";
    Ciphertext gin18 = 2 * ct_y10 + ct_x5;
    Ciphertext gout18 = ctx.eval_lut(&gin18, and2);

    std::cerr << "\rLUT19   ";
    Ciphertext gin19 = 2 * ct_y1 + ct_x8;
    Ciphertext gout19 = ctx.eval_lut(&gin19, and2);

    std::cerr << "\rLUT20   ";
    Ciphertext gin20 = 2 * ct_y14 + ct_x0;
    Ciphertext gout20 = ctx.eval_lut(&gin20, and2);

    std::cerr << "\rLUT21   ";
    Ciphertext gin21 = 2 * ct_y6 + ct_x7;
    Ciphertext gout21 = ctx.eval_lut(&gin21, and2);

    std::cerr << "\rLUT22   ";
    Ciphertext gin22 = 2 * gout1 + gout21;
    Ciphertext gout22 = ctx.eval_lut(&gin22, xor2);

    std::cerr << "\rLUT23   ";
    Ciphertext gin23 = 2 * gout1 + gout21;
    Ciphertext gout23 = ctx.eval_lut(&gin23, nand2);

    std::cerr << "\rLUT24   ";
    Ciphertext gin24 = 2 * ct_y12 + ct_x3;
    Ciphertext gout24 = ctx.eval_lut(&gin24, and2);

    std::cerr << "\rLUT25   ";
    Ciphertext gin25 = 2 * ct_y1 + ct_x12;
    Ciphertext gout25 = ctx.eval_lut(&gin25, and2);

    std::cerr << "\rLUT26   ";
    Ciphertext gin26 = 2 * ct_y10 + ct_x3;
    Ciphertext gout26 = ctx.eval_lut(&gin26, and2);

    std::cerr << "\rLUT27   ";
    Ciphertext gin27 = 2 * ct_y4 + ct_x5;
    Ciphertext gout27 = ctx.eval_lut(&gin27, and2);

    std::cerr << "\rLUT28   ";
    Ciphertext gin28 = 2 * ct_y4 + ct_x7;
    Ciphertext gout28 = ctx.eval_lut(&gin28, and2);

    std::cerr << "\rLUT29   ";
    Ciphertext gin29 = 2 * ct_y4 + ct_x8;
    Ciphertext gout29 = ctx.eval_lut(&gin29, and2);

    std::cerr << "\rLUT30   ";
    Ciphertext gin30 = 2 * ct_y9 + ct_x3;
    Ciphertext gout30 = ctx.eval_lut(&gin30, and2);

    std::cerr << "\rLUT31   ";
    Ciphertext gin31 = 2 * ct_y3 + ct_x8;
    Ciphertext gout31 = ctx.eval_lut(&gin31, and2);

    std::cerr << "\rLUT32   ";
    Ciphertext gin32 = 2 * ct_y5 + ct_x2;
    Ciphertext gout32 = ctx.eval_lut(&gin32, and2);

    std::cerr << "\rINV33   ";
    Ciphertext gout33 = 1 - ct_y3;

    std::cerr << "\rLUT34   ";
    Ciphertext gin34 = 2 * ct_y8 + ct_x0;
    Ciphertext gout34 = ctx.eval_lut(&gin34, and2);

    std::cerr << "\rLUT35   ";
    Ciphertext gin35 = 2 * ct_y3 + ct_x11;
    Ciphertext gout35 = ctx.eval_lut(&gin35, nand2);

    std::cerr << "\rLUT36   ";
    Ciphertext gin36 = 2 * ct_op2 + ct_op3;
    Ciphertext gout36 = ctx.eval_lut(&gin36, and2);

    std::cerr << "\rLUT37   ";
    Ciphertext gin37 = 2 * ct_y7 + ct_x3;
    Ciphertext gout37 = ctx.eval_lut(&gin37, and2);

    std::cerr << "\rLUT38   ";
    Ciphertext gin38 = 2 * ct_y1 + ct_x10;
    Ciphertext gout38 = ctx.eval_lut(&gin38, and2);

    std::cerr << "\rLUT39   ";
    Ciphertext gin39 = 2 * ct_y13 + ct_x0;
    Ciphertext gout39 = ctx.eval_lut(&gin39, and2);

    std::cerr << "\rLUT40   ";
    Ciphertext gin40 = 2 * ct_y7 + ct_x2;
    Ciphertext gout40 = ctx.eval_lut(&gin40, and2);

    std::cerr << "\rINV41   ";
    Ciphertext gout41 = 1 - ct_y15;

    std::cerr << "\rLUT42   ";
    Ciphertext gin42 = 2 * ct_y2 + ct_x6;
    Ciphertext gout42 = ctx.eval_lut(&gin42, and2);

    std::cerr << "\rLUT43   ";
    Ciphertext gin43 = 2 * ct_y1 + ct_x3;
    Ciphertext gout43 = ctx.eval_lut(&gin43, and2);

    std::cerr << "\rINV44   ";
    Ciphertext gout44 = 1 - ct_x4;

    std::cerr << "\rINV45   ";
    Ciphertext gout45 = 1 - ct_x8;

    std::cerr << "\rLUT46   ";
    Ciphertext gin46 = 2 * ct_y0 + ct_x15;
    Ciphertext gout46 = ctx.eval_lut(&gin46, and2);

    std::cerr << "\rINV47   ";
    Ciphertext gout47 = 1 - ct_x12;

    std::cerr << "\rLUT48   ";
    Ciphertext gin48 = 2 * ct_y8 + ct_x4;
    Ciphertext gout48 = ctx.eval_lut(&gin48, and2);

    std::cerr << "\rLUT49   ";
    Ciphertext gin49 = 2 * ct_y8 + ct_x7;
    Ciphertext gout49 = ctx.eval_lut(&gin49, and2);

    std::cerr << "\rLUT50   ";
    Ciphertext gin50 = 2 * ct_y0 + ct_x9;
    Ciphertext gout50 = ctx.eval_lut(&gin50, nand2);

    std::cerr << "\rINV51   ";
    Ciphertext gout51 = 1 - ct_y7;

    std::cerr << "\rLUT52   ";
    Ciphertext gin52 = 2 * ct_y0 + ct_x8;
    Ciphertext gout52 = ctx.eval_lut(&gin52, nand2);

    std::cerr << "\rLUT53   ";
    Ciphertext gin53 = 2 * ct_y4 + ct_x6;
    Ciphertext gout53 = ctx.eval_lut(&gin53, and2);

    std::cerr << "\rLUT54   ";
    Ciphertext gin54 = 2 * ct_y5 + ct_x0;
    Ciphertext gout54 = ctx.eval_lut(&gin54, and2);

    std::cerr << "\rLUT55   ";
    Ciphertext gin55 = 2 * ct_y6 + ct_x3;
    Ciphertext gout55 = ctx.eval_lut(&gin55, and2);

    std::cerr << "\rLUT56   ";
    Ciphertext gin56 = 2 * ct_y2 + ct_x1;
    Ciphertext gout56 = ctx.eval_lut(&gin56, and2);

    std::cerr << "\rLUT57   ";
    Ciphertext gin57 = 2 * gout12 + gout56;
    Ciphertext gout57 = ctx.eval_lut(&gin57, and2);

    std::cerr << "\rLUT58   ";
    Ciphertext gin58 = 2 * ct_y3 + ct_x4;
    Ciphertext gout58 = ctx.eval_lut(&gin58, and2);

    std::cerr << "\rLUT59   ";
    Ciphertext gin59 = 2 * gout58 + gout3;
    Ciphertext gout59 = ctx.eval_lut(&gin59, xor2);

    std::cerr << "\rLUT60   ";
    Ciphertext gin60 = 2 * gout58 + gout3;
    Ciphertext gout60 = ctx.eval_lut(&gin60, nand2);

    std::cerr << "\rLUT61   ";
    Ciphertext gin61 = 2 * ct_y0 + ct_x2;
    Ciphertext gout61 = ctx.eval_lut(&gin61, and2);

    std::cerr << "\rLUT62   ";
    Ciphertext gin62 = 2 * ct_y9 + ct_x1;
    Ciphertext gout62 = ctx.eval_lut(&gin62, nand2);

    std::cerr << "\rLUT63   ";
    Ciphertext gin63 = 2 * ct_y2 + ct_x10;
    Ciphertext gout63 = ctx.eval_lut(&gin63, and2);

    std::cerr << "\rLUT64   ";
    Ciphertext gin64 = 2 * ct_y1 + ct_x9;
    Ciphertext gout64 = ctx.eval_lut(&gin64, and2);

    std::cerr << "\rLUT65   ";
    Ciphertext gin65 = 2 * ct_y2 + ct_x2;
    Ciphertext gout65 = ctx.eval_lut(&gin65, and2);

    std::cerr << "\rLUT66   ";
    Ciphertext gin66 = 2 * ct_y8 + ct_x5;
    Ciphertext gout66 = ctx.eval_lut(&gin66, and2);

    std::cerr << "\rLUT67   ";
    Ciphertext gin67 = 2 * ct_y0 + ct_x0;
    Ciphertext gout67 = ctx.eval_lut(&gin67, and2);

    std::cerr << "\rLUT68   ";
    Ciphertext gin68 = 2 * ct_y7 + ct_x7;
    Ciphertext gout68 = ctx.eval_lut(&gin68, nand2);

    std::cerr << "\rLUT69   ";
    Ciphertext gin69 = 2 * ct_y13 + ct_x1;
    Ciphertext gout69 = ctx.eval_lut(&gin69, and2);

    std::cerr << "\rLUT70   ";
    Ciphertext gin70 = 2 * gout66 + gout22;
    Ciphertext gout70 = ctx.eval_lut(&gin70, nand2);

    std::cerr << "\rINV71   ";
    Ciphertext gout71 = 1 - gout67;

    std::cerr << "\rLUT72   ";
    Ciphertext gin72 = 2 * ct_y5 + ct_x5;
    Ciphertext gout72 = ctx.eval_lut(&gin72, and2);

    std::cerr << "\rLUT73   ";
    Ciphertext gin73 = 2 * gout66 + gout22;
    Ciphertext gout73 = ctx.eval_lut(&gin73, xor2);

    std::cerr << "\rLUT74   ";
    Ciphertext gin74 = 2 * ct_y3 + ct_x2;
    Ciphertext gout74 = ctx.eval_lut(&gin74, and2);

    std::cerr << "\rLUT75   ";
    Ciphertext gin75 = 2 * ct_y5 + ct_x8;
    Ciphertext gout75 = ctx.eval_lut(&gin75, and2);

    std::cerr << "\rLUT76   ";
    Ciphertext gin76 = 2 * ct_y2 + ct_x13;
    Ciphertext gout76 = ctx.eval_lut(&gin76, and2);

    std::cerr << "\rLUT77   ";
    Ciphertext gin77 = 2 * ct_y12 + ct_x2;
    Ciphertext gout77 = ctx.eval_lut(&gin77, nand2);

    std::cerr << "\rLUT78   ";
    Ciphertext gin78 = 2 * gout69 + gout77;
    Ciphertext gout78 = ctx.eval_lut(&gin78, xnor2);

    std::cerr << "\rLUT79   ";
    Ciphertext gin79 = 2 * gout23 + gout70;
    Ciphertext gout79 = ctx.eval_lut(&gin79, nand2);

    std::cerr << "\rLUT80   ";
    Ciphertext gin80 = 2 * ct_y5 + ct_x6;
    Ciphertext gout80 = ctx.eval_lut(&gin80, and2);

    std::cerr << "\rLUT81   ";
    Ciphertext gin81 = 2 * ct_y0 + ct_x7;
    Ciphertext gout81 = ctx.eval_lut(&gin81, nand2);

    std::cerr << "\rLUT82   ";
    Ciphertext gin82 = 2 * ct_y2 + ct_x9;
    Ciphertext gout82 = ctx.eval_lut(&gin82, and2);

    std::cerr << "\rLUT83   ";
    Ciphertext gin83 = 2 * gout31 + gout82;
    Ciphertext gout83 = ctx.eval_lut(&gin83, xor2);

    std::cerr << "\rLUT84   ";
    Ciphertext gin84 = 2 * gout38 + gout83;
    Ciphertext gout84 = ctx.eval_lut(&gin84, xor2);

    std::cerr << "\rLUT85   ";
    Ciphertext gin85 = 2 * gout38 + gout83;
    Ciphertext gout85 = ctx.eval_lut(&gin85, nand2);

    std::cerr << "\rLUT86   ";
    Ciphertext gin86 = 2 * gout31 + gout82;
    Ciphertext gout86 = ctx.eval_lut(&gin86, nand2);

    std::cerr << "\rLUT87   ";
    Ciphertext gin87 = 2 * gout35 + gout11;
    Ciphertext gout87 = ctx.eval_lut(&gin87, xnor2);

    std::cerr << "\rLUT88   ";
    Ciphertext gin88 = 2 * ct_y8 + ct_x2;
    Ciphertext gout88 = ctx.eval_lut(&gin88, and2);

    std::cerr << "\rINV89   ";
    Ciphertext gout89 = 1 - ct_x9;

    std::cerr << "\rINV90   ";
    Ciphertext gout90 = 1 - ct_x13;

    std::cerr << "\rINV91   ";
    Ciphertext gout91 = 1 - ct_y9;

    std::cerr << "\rINV92   ";
    Ciphertext gout92 = 1 - ct_x1;

    std::cerr << "\rLUT93   ";
    Ciphertext gin93 = 2 * gout20 + gout78;
    Ciphertext gout93 = ctx.eval_lut(&gin93, nand2);

    std::cerr << "\rINV94   ";
    Ciphertext gout94 = 1 - ct_x5;

    std::cerr << "\rLUT95   ";
    Ciphertext gin95 = 2 * ct_y7 + ct_x8;
    Ciphertext gout95 = ctx.eval_lut(&gin95, and2);

    std::cerr << "\rLUT96   ";
    Ciphertext gin96 = 2 * ct_y8 + ct_x6;
    Ciphertext gout96 = ctx.eval_lut(&gin96, and2);

    std::cerr << "\rLUT97   ";
    Ciphertext gin97 = 2 * gout4 + gout87;
    Ciphertext gout97 = ctx.eval_lut(&gin97, nand2);

    std::cerr << "\rLUT98   ";
    Ciphertext gin98 = 2 * ct_y9 + ct_x4;
    Ciphertext gout98 = ctx.eval_lut(&gin98, and2);

    std::cerr << "\rLUT99   ";
    Ciphertext gin99 = 2 * gout98 + gout18;
    Ciphertext gout99 = ctx.eval_lut(&gin99, nand2);

    std::cerr << "\rLUT100   ";
    Ciphertext gin100 = 2 * gout26 + gout98;
    Ciphertext gout100 = ctx.eval_lut(&gin100, xor2);

    std::cerr << "\rLUT101   ";
    Ciphertext gin101 = 2 * gout26 + gout98;
    Ciphertext gout101 = ctx.eval_lut(&gin101, nand2);

    std::cerr << "\rLUT102   ";
    Ciphertext gin102 = 2 * gout20 + gout78;
    Ciphertext gout102 = ctx.eval_lut(&gin102, xor2);

    std::cerr << "\rLUT103   ";
    Ciphertext gin103 = 2 * ct_y10 + ct_x0;
    Ciphertext gout103 = ctx.eval_lut(&gin103, and2);

    std::cerr << "\rLUT104   ";
    Ciphertext gin104 = 2 * gout62 + gout103;
    Ciphertext gout104 = ctx.eval_lut(&gin104, xnor2);

    std::cerr << "\rLUT105   ";
    Ciphertext gin105 = 2 * ct_y6 + ct_x1;
    Ciphertext gout105 = ctx.eval_lut(&gin105, nand2);

    std::cerr << "\rLUT106   ";
    Ciphertext gin106 = 2 * ct_y5 + ct_x1;
    Ciphertext gout106 = ctx.eval_lut(&gin106, and2);

    std::cerr << "\rLUT107   ";
    Ciphertext gin107 = 2 * ct_y2 + ct_x7;
    Ciphertext gout107 = ctx.eval_lut(&gin107, and2);

    std::cerr << "\rLUT108   ";
    Ciphertext gin108 = 2 * gout16 + gout107;
    Ciphertext gout108 = ctx.eval_lut(&gin108, xor2);

    std::cerr << "\rLUT109   ";
    Ciphertext gin109 = 2 * gout19 + gout108;
    Ciphertext gout109 = ctx.eval_lut(&gin109, xor2);

    std::cerr << "\rLUT110   ";
    Ciphertext gin110 = 2 * gout19 + gout108;
    Ciphertext gout110 = ctx.eval_lut(&gin110, nand2);

    std::cerr << "\rLUT111   ";
    Ciphertext gin111 = 2 * ct_y6 + ct_x2;
    Ciphertext gout111 = ctx.eval_lut(&gin111, and2);

    std::cerr << "\rLUT112   ";
    Ciphertext gin112 = 2 * gout0 + gout111;
    Ciphertext gout112 = ctx.eval_lut(&gin112, nand2);

    std::cerr << "\rLUT113   ";
    Ciphertext gin113 = 2 * gout61 + gout53;
    Ciphertext gout113 = ctx.eval_lut(&gin113, nand2);

    std::cerr << "\rLUT114   ";
    Ciphertext gin114 = 2 * gout4 + gout87;
    Ciphertext gout114 = ctx.eval_lut(&gin114, xor2);

    std::cerr << "\rLUT115   ";
    Ciphertext gin115 = 2 * ct_y12 + ct_x0;
    Ciphertext gout115 = ctx.eval_lut(&gin115, and2);

    std::cerr << "\rINV116   ";
    Ciphertext gout116 = 1 - ct_y8;

    std::cerr << "\rLUT117   ";
    Ciphertext gin117 = 2 * ct_y8 + ct_x3;
    Ciphertext gout117 = ctx.eval_lut(&gin117, and2);

    std::cerr << "\rLUT118   ";
    Ciphertext gin118 = 2 * ct_y11 + ct_x3;
    Ciphertext gout118 = ctx.eval_lut(&gin118, and2);

    std::cerr << "\rLUT119   ";
    Ciphertext gin119 = 2 * ct_y11 + ct_x0;
    Ciphertext gout119 = ctx.eval_lut(&gin119, and2);

    std::cerr << "\rLUT120   ";
    Ciphertext gin120 = 2 * gout8 + gout27;
    Ciphertext gout120 = ctx.eval_lut(&gin120, nand2);

    std::cerr << "\rLUT121   ";
    Ciphertext gin121 = 2 * ct_y1 + ct_x1;
    Ciphertext gout121 = ctx.eval_lut(&gin121, nand2);

    std::cerr << "\rINV122   ";
    Ciphertext gout122 = 1 - ct_y1;

    std::cerr << "\rLUT123   ";
    Ciphertext gin123 = 2 * ct_y9 + ct_x6;
    Ciphertext gout123 = ctx.eval_lut(&gin123, and2);

    std::cerr << "\rLUT124   ";
    Ciphertext gin124 = 2 * gout14 + gout0;
    Ciphertext gout124 = ctx.eval_lut(&gin124, and2);

    std::cerr << "\rLUT125   ";
    Ciphertext gin125 = 2 * ct_y1 + ct_x2;
    Ciphertext gout125 = ctx.eval_lut(&gin125, and2);

    std::cerr << "\rLUT126   ";
    Ciphertext gin126 = 2 * ct_y4 + ct_x9;
    Ciphertext gout126 = ctx.eval_lut(&gin126, and2);

    std::cerr << "\rLUT127   ";
    Ciphertext gin127 = 2 * gout115 + gout69;
    Ciphertext gout127 = ctx.eval_lut(&gin127, and2);

    std::cerr << "\rLUT128   ";
    Ciphertext gin128 = 2 * gout0 + gout111;
    Ciphertext gout128 = ctx.eval_lut(&gin128, xor2);

    std::cerr << "\rLUT129   ";
    Ciphertext gin129 = 2 * ct_y0 + ct_x12;
    Ciphertext gout129 = ctx.eval_lut(&gin129, and2);

    std::cerr << "\rLUT130   ";
    Ciphertext gin130 = 2 * gout29 + gout129;
    Ciphertext gout130 = ctx.eval_lut(&gin130, xor2);

    std::cerr << "\rLUT131   ";
    Ciphertext gin131 = 2 * gout40 + gout55;
    Ciphertext gout131 = ctx.eval_lut(&gin131, nand2);

    std::cerr << "\rLUT132   ";
    Ciphertext gin132 = 2 * ct_y0 + ct_x10;
    Ciphertext gout132 = ctx.eval_lut(&gin132, nand2);

    std::cerr << "\rLUT133   ";
    Ciphertext gin133 = 2 * gout53 + gout132;
    Ciphertext gout133 = ctx.eval_lut(&gin133, xnor2);

    std::cerr << "\rLUT134   ";
    Ciphertext gin134 = 2 * gout72 + gout133;
    Ciphertext gout134 = ctx.eval_lut(&gin134, xor2);

    std::cerr << "\rLUT135   ";
    Ciphertext gin135 = 2 * gout72 + gout133;
    Ciphertext gout135 = ctx.eval_lut(&gin135, nand2);

    std::cerr << "\rINV136   ";
    Ciphertext gout136 = 1 - gout115;

    std::cerr << "\rLUT137   ";
    Ciphertext gin137 = 2 * ct_y0 + ct_x13;
    Ciphertext gout137 = ctx.eval_lut(&gin137, and2);

    std::cerr << "\rLUT138   ";
    Ciphertext gin138 = 2 * gout126 + gout137;
    Ciphertext gout138 = ctx.eval_lut(&gin138, xor2);

    std::cerr << "\rLUT139   ";
    Ciphertext gin139 = 2 * gout75 + gout138;
    Ciphertext gout139 = ctx.eval_lut(&gin139, xor2);

    std::cerr << "\rLUT140   ";
    Ciphertext gin140 = 2 * gout75 + gout138;
    Ciphertext gout140 = ctx.eval_lut(&gin140, nand2);

    std::cerr << "\rLUT141   ";
    Ciphertext gin141 = 2 * ct_y3 + ct_x0;
    Ciphertext gout141 = ctx.eval_lut(&gin141, nand2);

    std::cerr << "\rLUT142   ";
    Ciphertext gin142 = 2 * gout56 + gout141;
    Ciphertext gout142 = ctx.eval_lut(&gin142, xnor2);

    std::cerr << "\rLUT143   ";
    Ciphertext gin143 = 2 * gout125 + gout142;
    Ciphertext gout143 = ctx.eval_lut(&gin143, xor2);

    std::cerr << "\rLUT144   ";
    Ciphertext gin144 = 2 * gout125 + gout142;
    Ciphertext gout144 = ctx.eval_lut(&gin144, nand2);

    std::cerr << "\rLUT145   ";
    Ciphertext gin145 = 2 * gout57 + gout143;
    Ciphertext gout145 = ctx.eval_lut(&gin145, nand2);

    std::cerr << "\rLUT146   ";
    Ciphertext gin146 = 2 * ct_y4 + ct_x0;
    Ciphertext gout146 = ctx.eval_lut(&gin146, and2);

    std::cerr << "\rLUT147   ";
    Ciphertext gin147 = 2 * ct_y9 + ct_x2;
    Ciphertext gout147 = ctx.eval_lut(&gin147, and2);

    std::cerr << "\rLUT148   ";
    Ciphertext gin148 = 2 * gout40 + gout55;
    Ciphertext gout148 = ctx.eval_lut(&gin148, xor2);

    std::cerr << "\rLUT149   ";
    Ciphertext gin149 = 2 * ct_y3 + ct_x7;
    Ciphertext gout149 = ctx.eval_lut(&gin149, and2);

    std::cerr << "\rLUT150   ";
    Ciphertext gin150 = 2 * ct_y3 + ct_x10;
    Ciphertext gout150 = ctx.eval_lut(&gin150, and2);

    std::cerr << "\rLUT151   ";
    Ciphertext gin151 = 2 * ct_y7 + ct_x5;
    Ciphertext gout151 = ctx.eval_lut(&gin151, and2);

    std::cerr << "\rLUT152   ";
    Ciphertext gin152 = 2 * gout151 + gout17;
    Ciphertext gout152 = ctx.eval_lut(&gin152, xor2);

    std::cerr << "\rLUT153   ";
    Ciphertext gin153 = 2 * gout151 + gout17;
    Ciphertext gout153 = ctx.eval_lut(&gin153, nand2);

    std::cerr << "\rINV154   ";
    Ciphertext gout154 = 1 - ct_x2;

    std::cerr << "\rLUT155   ";
    Ciphertext gin155 = 2 * ct_y0 + ct_x11;
    Ciphertext gout155 = ctx.eval_lut(&gin155, nand2);

    std::cerr << "\rLUT156   ";
    Ciphertext gin156 = 2 * gout28 + gout155;
    Ciphertext gout156 = ctx.eval_lut(&gin156, xnor2);

    std::cerr << "\rLUT157   ";
    Ciphertext gin157 = 2 * gout80 + gout156;
    Ciphertext gout157 = ctx.eval_lut(&gin157, xor2);

    std::cerr << "\rLUT158   ";
    Ciphertext gin158 = 2 * gout80 + gout156;
    Ciphertext gout158 = ctx.eval_lut(&gin158, nand2);

    std::cerr << "\rINV159   ";
    Ciphertext gout159 = 1 - ct_x10;

    std::cerr << "\rLUT160   ";
    Ciphertext gin160 = 2 * ct_y0 + ct_x6;
    Ciphertext gout160 = ctx.eval_lut(&gin160, nand2);

    std::cerr << "\rINV161   ";
    Ciphertext gout161 = 1 - ct_y10;

    std::cerr << "\rINV162   ";
    Ciphertext gout162 = 1 - ct_x6;

    std::cerr << "\rLUT163   ";
    Ciphertext gin163 = 2 * gout57 + gout143;
    Ciphertext gout163 = ctx.eval_lut(&gin163, xor2);

    std::cerr << "\rINV164   ";
    Ciphertext gout164 = 1 - ct_x14;

    std::cerr << "\rINV165   ";
    Ciphertext gout165 = 1 - ct_y5;

    std::cerr << "\rINV166   ";
    Ciphertext gout166 = 1 - gout61;

    std::cerr << "\rLUT167   ";
    Ciphertext gin167 = 2 * gout21 + gout95;
    Ciphertext gout167 = ctx.eval_lut(&gin167, nand2);

    std::cerr << "\rLUT168   ";
    Ciphertext gin168 = 2 * ct_y6 + ct_x8;
    Ciphertext gout168 = ctx.eval_lut(&gin168, and2);

    std::cerr << "\rLUT169   ";
    Ciphertext gin169 = 2 * ct_y6 + ct_x4;
    Ciphertext gout169 = ctx.eval_lut(&gin169, and2);

    std::cerr << "\rLUT170   ";
    Ciphertext gin170 = 2 * gout37 + gout169;
    Ciphertext gout170 = ctx.eval_lut(&gin170, nand2);

    std::cerr << "\rLUT171   ";
    Ciphertext gin171 = 2 * ct_y3 + ct_x1;
    Ciphertext gout171 = ctx.eval_lut(&gin171, nand2);

    std::cerr << "\rLUT172   ";
    Ciphertext gin172 = 2 * gout37 + gout169;
    Ciphertext gout172 = ctx.eval_lut(&gin172, xor2);

    std::cerr << "\rLUT173   ";
    Ciphertext gin173 = 2 * gout88 + gout172;
    Ciphertext gout173 = ctx.eval_lut(&gin173, xor2);

    std::cerr << "\rLUT174   ";
    Ciphertext gin174 = 2 * gout88 + gout172;
    Ciphertext gout174 = ctx.eval_lut(&gin174, nand2);

    std::cerr << "\rLUT175   ";
    Ciphertext gin175 = 2 * gout170 + gout174;
    Ciphertext gout175 = ctx.eval_lut(&gin175, nand2);

    std::cerr << "\rLUT176   ";
    Ciphertext gin176 = 2 * ct_y10 + ct_x4;
    Ciphertext gout176 = ctx.eval_lut(&gin176, nand2);

    std::cerr << "\rLUT177   ";
    Ciphertext gin177 = 2 * gout49 + gout123;
    Ciphertext gout177 = ctx.eval_lut(&gin177, xnor2);

    std::cerr << "\rLUT178   ";
    Ciphertext gin178 = 2 * ct_y3 + ct_x9;
    Ciphertext gout178 = ctx.eval_lut(&gin178, and2);

    std::cerr << "\rLUT179   ";
    Ciphertext gin179 = 2 * ct_y4 + ct_x1;
    Ciphertext gout179 = ctx.eval_lut(&gin179, and2);

    std::cerr << "\rLUT180   ";
    Ciphertext gin180 = 2 * gout6 + gout179;
    Ciphertext gout180 = ctx.eval_lut(&gin180, xnor2);

    std::cerr << "\rLUT181   ";
    Ciphertext gin181 = 2 * gout54 + gout180;
    Ciphertext gout181 = ctx.eval_lut(&gin181, nand2);

    std::cerr << "\rLUT182   ";
    Ciphertext gin182 = 2 * gout120 + gout181;
    Ciphertext gout182 = ctx.eval_lut(&gin182, nand2);

    std::cerr << "\rLUT183   ";
    Ciphertext gin183 = 2 * ct_y11 + ct_x4;
    Ciphertext gout183 = ctx.eval_lut(&gin183, and2);

    std::cerr << "\rLUT184   ";
    Ciphertext gin184 = 2 * gout183 + gout24;
    Ciphertext gout184 = ctx.eval_lut(&gin184, xnor2);

    std::cerr << "\rLUT185   ";
    Ciphertext gin185 = 2 * gout177 + gout184;
    Ciphertext gout185 = ctx.eval_lut(&gin185, xnor2);

    std::cerr << "\rLUT186   ";
    Ciphertext gin186 = 2 * gout18 + gout185;
    Ciphertext gout186 = ctx.eval_lut(&gin186, xnor2);

    std::cerr << "\rLUT187   ";
    Ciphertext gin187 = 2 * gout9 + gout10;
    Ciphertext gout187 = ctx.eval_lut(&gin187, xnor2);

    std::cerr << "\rLUT188   ";
    Ciphertext gin188 = 2 * ct_y2 + ct_x8;
    Ciphertext gout188 = ctx.eval_lut(&gin188, and2);

    std::cerr << "\rLUT189   ";
    Ciphertext gin189 = 2 * gout149 + gout188;
    Ciphertext gout189 = ctx.eval_lut(&gin189, xor2);

    std::cerr << "\rLUT190   ";
    Ciphertext gin190 = 2 * gout149 + gout188;
    Ciphertext gout190 = ctx.eval_lut(&gin190, nand2);

    std::cerr << "\rLUT191   ";
    Ciphertext gin191 = 2 * gout34 + gout128;
    Ciphertext gout191 = ctx.eval_lut(&gin191, nand2);

    std::cerr << "\rLUT192   ";
    Ciphertext gin192 = 2 * gout95 + gout187;
    Ciphertext gout192 = ctx.eval_lut(&gin192, xnor2);

    std::cerr << "\rLUT193   ";
    Ciphertext gin193 = 2 * ct_y2 + ct_x11;
    Ciphertext gout193 = ctx.eval_lut(&gin193, and2);

    std::cerr << "\rLUT194   ";
    Ciphertext gin194 = 2 * gout150 + gout193;
    Ciphertext gout194 = ctx.eval_lut(&gin194, xor2);

    std::cerr << "\rLUT195   ";
    Ciphertext gin195 = 2 * gout150 + gout193;
    Ciphertext gout195 = ctx.eval_lut(&gin195, nand2);

    std::cerr << "\rLUT196   ";
    Ciphertext gin196 = 2 * gout34 + gout128;
    Ciphertext gout196 = ctx.eval_lut(&gin196, xor2);

    std::cerr << "\rLUT197   ";
    Ciphertext gin197 = 2 * ct_y1 + ct_y0;
    Ciphertext gout197 = ctx.eval_lut(&gin197, nor2);

    std::cerr << "\rINV198   ";
    Ciphertext gout198 = 1 - gout197;

    std::cerr << "\rLUT199   ";
    Ciphertext gin199 = 2 * (1 - ct_op1) + ct_op0;
    Ciphertext gout199 = ctx.eval_lut(&gin199, and2);

    std::cerr << "\rLUT200   ";
    Ciphertext gin200 = 2 * gout199 + gout36;
    Ciphertext gout200 = ctx.eval_lut(&gin200, and2);

    std::cerr << "\rLUT201   ";
    Ciphertext gin201 = 2 * ct_y4 + ct_x10;
    Ciphertext gout201 = ctx.eval_lut(&gin201, and2);

    std::cerr << "\rLUT202   ";
    Ciphertext gin202 = 2 * gout160 + (1 - gout201);
    Ciphertext gout202 = ctx.eval_lut(&gin202, or2);

    std::cerr << "\rLUT203   ";
    Ciphertext gin203 = 2 * gout202 + gout135;
    Ciphertext gout203 = ctx.eval_lut(&gin203, nand2);

    std::cerr << "\rLUT204   ";
    Ciphertext gin204 = 2 * ct_y3 + ct_x3;
    Ciphertext gout204 = ctx.eval_lut(&gin204, and2);

    std::cerr << "\rLUT205   ";
    Ciphertext gin205 = 2 * ct_y1 + ct_x4;
    Ciphertext gout205 = ctx.eval_lut(&gin205, and2);

    std::cerr << "\rLUT206   ";
    Ciphertext gin206 = 2 * ct_y14 + ct_x1;
    Ciphertext gout206 = ctx.eval_lut(&gin206, and2);

    std::cerr << "\rLUT207   ";
    Ciphertext gin207 = 2 * ct_y4 + ct_x4;
    Ciphertext gout207 = ctx.eval_lut(&gin207, and2);

    std::cerr << "\rLUT208   ";
    Ciphertext gin208 = 2 * gout207 + gout52;
    Ciphertext gout208 = ctx.eval_lut(&gin208, xnor2);

    std::cerr << "\rLUT209   ";
    Ciphertext gin209 = 2 * gout67 + gout207;
    Ciphertext gout209 = ctx.eval_lut(&gin209, and2);

    std::cerr << "\rINV210   ";
    Ciphertext gout210 = 1 - gout209;

    std::cerr << "\rINV211   ";
    Ciphertext gout211 = 1 - ct_op0;

    std::cerr << "\rINV212   ";
    Ciphertext gout212 = 1 - ct_x11;

    std::cerr << "\rLUT213   ";
    Ciphertext gin213 = 2 * ct_y3 + ct_x12;
    Ciphertext gout213 = ctx.eval_lut(&gin213, and2);

    std::cerr << "\rLUT214   ";
    Ciphertext gin214 = 2 * gout193 + gout213;
    Ciphertext gout214 = ctx.eval_lut(&gin214, nand2);

    std::cerr << "\rLUT215   ";
    Ciphertext gin215 = 2 * gout214 + gout97;
    Ciphertext gout215 = ctx.eval_lut(&gin215, and2);

    std::cerr << "\rLUT216   ";
    Ciphertext gin216 = 2 * ct_y5 + ct_x4;
    Ciphertext gout216 = ctx.eval_lut(&gin216, and2);

    std::cerr << "\rINV217   ";
    Ciphertext gout217 = 1 - ct_x3;

    std::cerr << "\rLUT218   ";
    Ciphertext gin218 = 2 * gout126 + gout137;
    Ciphertext gout218 = ctx.eval_lut(&gin218, nand2);

    std::cerr << "\rLUT219   ";
    Ciphertext gin219 = 2 * gout218 + gout140;
    Ciphertext gout219 = ctx.eval_lut(&gin219, nand2);

    std::cerr << "\rLUT220   ";
    Ciphertext gin220 = 2 * ct_y7 + ct_x4;
    Ciphertext gout220 = ctx.eval_lut(&gin220, and2);

    std::cerr << "\rLUT221   ";
    Ciphertext gin221 = 2 * ct_y0 + ct_x4;
    Ciphertext gout221 = ctx.eval_lut(&gin221, nand2);

    std::cerr << "\rLUT222   ";
    Ciphertext gin222 = 2 * gout221 + (1 - gout29);
    Ciphertext gout222 = ctx.eval_lut(&gin222, or2);

    std::cerr << "\rLUT223   ";
    Ciphertext gin223 = 2 * gout221 + gout146;
    Ciphertext gout223 = ctx.eval_lut(&gin223, xnor2);

    std::cerr << "\rLUT224   ";
    Ciphertext gin224 = 2 * ct_y4 + ct_x11;
    Ciphertext gout224 = ctx.eval_lut(&gin224, and2);

    std::cerr << "\rLUT225   ";
    Ciphertext gin225 = 2 * gout224 + gout215;
    Ciphertext gout225 = ctx.eval_lut(&gin225, xnor2);

    std::cerr << "\rLUT226   ";
    Ciphertext gin226 = 2 * gout81 + (1 - gout224);
    Ciphertext gout226 = ctx.eval_lut(&gin226, or2);

    std::cerr << "\rLUT227   ";
    Ciphertext gin227 = 2 * gout226 + gout158;
    Ciphertext gout227 = ctx.eval_lut(&gin227, nand2);

    std::cerr << "\rLUT228   ";
    Ciphertext gin228 = 2 * gout178 + gout63;
    Ciphertext gout228 = ctx.eval_lut(&gin228, nand2);

    std::cerr << "\rLUT229   ";
    Ciphertext gin229 = 2 * ct_y6 + ct_x5;
    Ciphertext gout229 = ctx.eval_lut(&gin229, and2);

    std::cerr << "\rLUT230   ";
    Ciphertext gin230 = 2 * gout220 + gout229;
    Ciphertext gout230 = ctx.eval_lut(&gin230, xor2);

    std::cerr << "\rLUT231   ";
    Ciphertext gin231 = 2 * gout220 + gout229;
    Ciphertext gout231 = ctx.eval_lut(&gin231, nand2);

    std::cerr << "\rLUT232   ";
    Ciphertext gin232 = 2 * gout112 + gout191;
    Ciphertext gout232 = ctx.eval_lut(&gin232, nand2);

    std::cerr << "\rLUT233   ";
    Ciphertext gin233 = 2 * ct_y2 + ct_x3;
    Ciphertext gout233 = ctx.eval_lut(&gin233, and2);

    std::cerr << "\rLUT234   ";
    Ciphertext gin234 = 2 * gout74 + gout233;
    Ciphertext gout234 = ctx.eval_lut(&gin234, xor2);

    std::cerr << "\rLUT235   ";
    Ciphertext gin235 = 2 * gout205 + gout234;
    Ciphertext gout235 = ctx.eval_lut(&gin235, xor2);

    std::cerr << "\rLUT236   ";
    Ciphertext gin236 = 2 * gout205 + gout234;
    Ciphertext gout236 = ctx.eval_lut(&gin236, nand2);

    std::cerr << "\rLUT237   ";
    Ciphertext gin237 = 2 * gout74 + gout233;
    Ciphertext gout237 = ctx.eval_lut(&gin237, nand2);

    std::cerr << "\rLUT238   ";
    Ciphertext gin238 = 2 * ct_y2 + ct_x0;
    Ciphertext gout238 = ctx.eval_lut(&gin238, and2);

    std::cerr << "\rLUT239   ";
    Ciphertext gin239 = 2 * (1 - gout238) + gout171;
    Ciphertext gout239 = ctx.eval_lut(&gin239, or2);

    std::cerr << "\rLUT240   ";
    Ciphertext gin240 = 2 * (1 - ct_op2) + ct_op1;
    Ciphertext gout240 = ctx.eval_lut(&gin240, and2);

    std::cerr << "\rINV241   ";
    Ciphertext gout241 = 1 - ct_y6;

    std::cerr << "\rINV242   ";
    Ciphertext gout242 = 1 - ct_y2;

    std::cerr << "\rLUT243   ";
    Ciphertext gin243 = 2 * gout242 + gout197;
    Ciphertext gout243 = ctx.eval_lut(&gin243, and2);

    std::cerr << "\rLUT244   ";
    Ciphertext gin244 = 2 * gout33 + gout243;
    Ciphertext gout244 = ctx.eval_lut(&gin244, and2);

    std::cerr << "\rLUT245   ";
    Ciphertext gin245 = 2 * gout5 + gout244;
    Ciphertext gout245 = ctx.eval_lut(&gin245, and2);

    std::cerr << "\rLUT246   ";
    Ciphertext gin246 = 2 * gout165 + gout245;
    Ciphertext gout246 = ctx.eval_lut(&gin246, and2);

    std::cerr << "\rLUT247   ";
    Ciphertext gin247 = 2 * gout241 + gout246;
    Ciphertext gout247 = ctx.eval_lut(&gin247, and2);

    std::cerr << "\rLUT248   ";
    Ciphertext gin248 = 2 * gout51 + gout247;
    Ciphertext gout248 = ctx.eval_lut(&gin248, and2);

    std::cerr << "\rLUT249   ";
    Ciphertext gin249 = 2 * gout116 + gout248;
    Ciphertext gout249 = ctx.eval_lut(&gin249, and2);

    std::cerr << "\rLUT250   ";
    Ciphertext gin250 = 2 * gout91 + gout249;
    Ciphertext gout250 = ctx.eval_lut(&gin250, and2);

    std::cerr << "\rLUT251   ";
    Ciphertext gin251 = 2 * gout161 + gout250;
    Ciphertext gout251 = ctx.eval_lut(&gin251, nand2);

    std::cerr << "\rLUT252   ";
    Ciphertext gin252 = 2 * gout178 + gout63;
    Ciphertext gout252 = ctx.eval_lut(&gin252, xor2);

    std::cerr << "\rLUT253   ";
    Ciphertext gin253 = 2 * ct_op3 + gout240;
    Ciphertext gout253 = ctx.eval_lut(&gin253, and2);

    std::cerr << "\rLUT254   ";
    Ciphertext gin254 = 2 * gout239 + gout144;
    Ciphertext gout254 = ctx.eval_lut(&gin254, nand2);

    std::cerr << "\rLUT255   ";
    Ciphertext gin255 = 2 * gout6 + (1 - gout126);
    Ciphertext gout255 = ctx.eval_lut(&gin255, or2);

    std::cerr << "\rLUT256   ";
    Ciphertext gin256 = 2 * gout64 + gout189;
    Ciphertext gout256 = ctx.eval_lut(&gin256, nand2);

    std::cerr << "\rLUT257   ";
    Ciphertext gin257 = 2 * ct_y1 + ct_x6;
    Ciphertext gout257 = ctx.eval_lut(&gin257, and2);

    std::cerr << "\rLUT258   ";
    Ciphertext gin258 = 2 * gout257 + gout59;
    Ciphertext gout258 = ctx.eval_lut(&gin258, xor2);

    std::cerr << "\rLUT259   ";
    Ciphertext gin259 = 2 * gout257 + gout59;
    Ciphertext gout259 = ctx.eval_lut(&gin259, nand2);

    std::cerr << "\rLUT260   ";
    Ciphertext gin260 = 2 * gout54 + gout180;
    Ciphertext gout260 = ctx.eval_lut(&gin260, xor2);

    std::cerr << "\rLUT261   ";
    Ciphertext gin261 = 2 * gout67 + (1 - gout121);
    Ciphertext gout261 = ctx.eval_lut(&gin261, and2);

    std::cerr << "\rLUT262   ";
    Ciphertext gin262 = 2 * (1 - ct_x0) + ct_y15;
    Ciphertext gout262 = ctx.eval_lut(&gin262, and2);

    std::cerr << "\rLUT263   ";
    Ciphertext gin263 = 2 * gout262 + gout206;
    Ciphertext gout263 = ctx.eval_lut(&gin263, xnor2);

    std::cerr << "\rLUT264   ";
    Ciphertext gin264 = 2 * gout41 + gout213;
    Ciphertext gout264 = ctx.eval_lut(&gin264, xnor2);

    std::cerr << "\rLUT265   ";
    Ciphertext gin265 = 2 * gout25 + gout194;
    Ciphertext gout265 = ctx.eval_lut(&gin265, nand2);

    std::cerr << "\rLUT266   ";
    Ciphertext gin266 = 2 * gout195 + gout265;
    Ciphertext gout266 = ctx.eval_lut(&gin266, nand2);

    std::cerr << "\rLUT267   ";
    Ciphertext gin267 = 2 * gout266 + gout114;
    Ciphertext gout267 = ctx.eval_lut(&gin267, nand2);

    std::cerr << "\rLUT268   ";
    Ciphertext gin268 = 2 * gout64 + gout189;
    Ciphertext gout268 = ctx.eval_lut(&gin268, xor2);

    std::cerr << "\rLUT269   ";
    Ciphertext gin269 = 2 * ct_y7 + ct_x0;
    Ciphertext gout269 = ctx.eval_lut(&gin269, and2);

    std::cerr << "\rLUT270   ";
    Ciphertext gin270 = 2 * gout105 + gout269;
    Ciphertext gout270 = ctx.eval_lut(&gin270, xnor2);

    std::cerr << "\rLUT271   ";
    Ciphertext gin271 = 2 * gout56 + gout74;
    Ciphertext gout271 = ctx.eval_lut(&gin271, nand2);

    std::cerr << "\rLUT272   ";
    Ciphertext gin272 = 2 * ct_y10 + ct_x1;
    Ciphertext gout272 = ctx.eval_lut(&gin272, and2);

    std::cerr << "\rLUT273   ";
    Ciphertext gin273 = 2 * gout272 + gout147;
    Ciphertext gout273 = ctx.eval_lut(&gin273, xor2);

    std::cerr << "\rLUT274   ";
    Ciphertext gin274 = 2 * gout119 + gout273;
    Ciphertext gout274 = ctx.eval_lut(&gin274, xor2);

    std::cerr << "\rLUT275   ";
    Ciphertext gin275 = 2 * gout119 + gout273;
    Ciphertext gout275 = ctx.eval_lut(&gin275, nand2);

    std::cerr << "\rLUT276   ";
    Ciphertext gin276 = 2 * gout272 + gout147;
    Ciphertext gout276 = ctx.eval_lut(&gin276, nand2);

    std::cerr << "\rLUT277   ";
    Ciphertext gin277 = 2 * ct_y5 + ct_x3;
    Ciphertext gout277 = ctx.eval_lut(&gin277, and2);

    std::cerr << "\rLUT278   ";
    Ciphertext gin278 = 2 * gout277 + gout208;
    Ciphertext gout278 = ctx.eval_lut(&gin278, xor2);

    std::cerr << "\rLUT279   ";
    Ciphertext gin279 = 2 * gout277 + gout208;
    Ciphertext gout279 = ctx.eval_lut(&gin279, nand2);

    std::cerr << "\rLUT280   ";
    Ciphertext gin280 = 2 * gout222 + gout279;
    Ciphertext gout280 = ctx.eval_lut(&gin280, nand2);

    std::cerr << "\rLUT281   ";
    Ciphertext gin281 = 2 * ct_y0 + ct_x0;
    Ciphertext gout281 = ctx.eval_lut(&gin281, xnor2);

    std::cerr << "\rLUT282   ";
    Ciphertext gin282 = 2 * ct_y9 + ct_x5;
    Ciphertext gout282 = ctx.eval_lut(&gin282, and2);

    std::cerr << "\rLUT283   ";
    Ciphertext gin283 = 2 * gout176 + gout282;
    Ciphertext gout283 = ctx.eval_lut(&gin283, xnor2);

    std::cerr << "\rLUT284   ";
    Ciphertext gin284 = 2 * gout118 + gout283;
    Ciphertext gout284 = ctx.eval_lut(&gin284, xor2);

    std::cerr << "\rLUT285   ";
    Ciphertext gin285 = 2 * gout118 + gout283;
    Ciphertext gout285 = ctx.eval_lut(&gin285, nand2);

    std::cerr << "\rLUT286   ";
    Ciphertext gin286 = 2 * gout99 + gout285;
    Ciphertext gout286 = ctx.eval_lut(&gin286, and2);

    std::cerr << "\rLUT287   ";
    Ciphertext gin287 = 2 * gout25 + gout194;
    Ciphertext gout287 = ctx.eval_lut(&gin287, xor2);

    std::cerr << "\rLUT288   ";
    Ciphertext gin288 = 2 * gout60 + gout259;
    Ciphertext gout288 = ctx.eval_lut(&gin288, nand2);

    std::cerr << "\rLUT289   ";
    Ciphertext gin289 = 2 * gout266 + gout114;
    Ciphertext gout289 = ctx.eval_lut(&gin289, xnor2);

    std::cerr << "\rLUT290   ";
    Ciphertext gin290 = 2 * ct_y0 + ct_x14;
    Ciphertext gout290 = ctx.eval_lut(&gin290, and2);

    std::cerr << "\rLUT291   ";
    Ciphertext gin291 = 2 * gout201 + gout290;
    Ciphertext gout291 = ctx.eval_lut(&gin291, xor2);

    std::cerr << "\rLUT292   ";
    Ciphertext gin292 = 2 * gout15 + gout291;
    Ciphertext gout292 = ctx.eval_lut(&gin292, xor2);

    std::cerr << "\rLUT293   ";
    Ciphertext gin293 = 2 * gout289 + gout292;
    Ciphertext gout293 = ctx.eval_lut(&gin293, xnor2);

    std::cerr << "\rLUT294   ";
    Ciphertext gin294 = 2 * (1 - gout289) + gout292;
    Ciphertext gout294 = ctx.eval_lut(&gin294, and2);

    std::cerr << "\rLUT295   ";
    Ciphertext gin295 = 2 * gout15 + gout291;
    Ciphertext gout295 = ctx.eval_lut(&gin295, nand2);

    std::cerr << "\rLUT296   ";
    Ciphertext gin296 = 2 * gout201 + gout290;
    Ciphertext gout296 = ctx.eval_lut(&gin296, nand2);

    std::cerr << "\rLUT297   ";
    Ciphertext gin297 = 2 * gout296 + gout295;
    Ciphertext gout297 = ctx.eval_lut(&gin297, and2);

    std::cerr << "\rLUT298   ";
    Ciphertext gin298 = 2 * gout297 + gout192;
    Ciphertext gout298 = ctx.eval_lut(&gin298, xnor2);

    std::cerr << "\rLUT299   ";
    Ciphertext gin299 = 2 * gout225 + gout298;
    Ciphertext gout299 = ctx.eval_lut(&gin299, xnor2);

    std::cerr << "\rLUT300   ";
    Ciphertext gin300 = 2 * gout237 + gout236;
    Ciphertext gout300 = ctx.eval_lut(&gin300, nand2);

    std::cerr << "\rLUT301   ";
    Ciphertext gin301 = 2 * ct_y1 + ct_x7;
    Ciphertext gout301 = ctx.eval_lut(&gin301, and2);

    std::cerr << "\rLUT302   ";
    Ciphertext gin302 = 2 * ct_y1 + ct_x5;
    Ciphertext gout302 = ctx.eval_lut(&gin302, and2);

    std::cerr << "\rLUT303   ";
    Ciphertext gin303 = 2 * gout121 + gout238;
    Ciphertext gout303 = ctx.eval_lut(&gin303, xnor2);

    std::cerr << "\rLUT304   ";
    Ciphertext gin304 = 2 * gout166 + gout303;
    Ciphertext gout304 = ctx.eval_lut(&gin304, xnor2);

    std::cerr << "\rLUT305   ";
    Ciphertext gin305 = 2 * gout261 + gout304;
    Ciphertext gout305 = ctx.eval_lut(&gin305, xnor2);

    std::cerr << "\rLUT306   ";
    Ciphertext gin306 = 2 * gout261 + gout304;
    Ciphertext gout306 = ctx.eval_lut(&gin306, and2);

    std::cerr << "\rLUT307   ";
    Ciphertext gin307 = 2 * gout68 + gout168;
    Ciphertext gout307 = ctx.eval_lut(&gin307, xnor2);

    std::cerr << "\rLUT308   ";
    Ciphertext gin308 = 2 * gout267 + (1 - gout294);
    Ciphertext gout308 = ctx.eval_lut(&gin308, and2);

    std::cerr << "\rLUT309   ";
    Ciphertext gin309 = 2 * ct_y13 + ct_x2;
    Ciphertext gout309 = ctx.eval_lut(&gin309, and2);

    std::cerr << "\rLUT310   ";
    Ciphertext gin310 = 2 * gout309 + gout286;
    Ciphertext gout310 = ctx.eval_lut(&gin310, xnor2);

    std::cerr << "\rLUT311   ";
    Ciphertext gin311 = 2 * gout186 + gout310;
    Ciphertext gout311 = ctx.eval_lut(&gin311, xnor2);

    std::cerr << "\rLUT312   ";
    Ciphertext gin312 = 2 * gout96 + gout307;
    Ciphertext gout312 = ctx.eval_lut(&gin312, nand2);

    std::cerr << "\rLUT313   ";
    Ciphertext gin313 = 2 * gout171 + gout65;
    Ciphertext gout313 = ctx.eval_lut(&gin313, xnor2);

    std::cerr << "\rLUT314   ";
    Ciphertext gin314 = 2 * gout182 + gout14;
    Ciphertext gout314 = ctx.eval_lut(&gin314, and2);

    std::cerr << "\rLUT315   ";
    Ciphertext gin315 = 2 * ct_op6 + ct_op7;
    Ciphertext gout315 = ctx.eval_lut(&gin315, nor2);

    std::cerr << "\rLUT316   ";
    Ciphertext gin316 = 2 * gout182 + gout14;
    Ciphertext gout316 = ctx.eval_lut(&gin316, xor2);

    std::cerr << "\rLUT317   ";
    Ciphertext gin317 = 2 * gout12 + gout8;
    Ciphertext gout317 = ctx.eval_lut(&gin317, xor2);

    std::cerr << "\rLUT318   ";
    Ciphertext gin318 = 2 * gout167 + gout312;
    Ciphertext gout318 = ctx.eval_lut(&gin318, and2);

    std::cerr << "\rLUT319   ";
    Ciphertext gin319 = 2 * gout96 + gout307;
    Ciphertext gout319 = ctx.eval_lut(&gin319, xor2);

    std::cerr << "\rLUT320   ";
    Ciphertext gin320 = 2 * gout219 + gout319;
    Ciphertext gout320 = ctx.eval_lut(&gin320, xor2);

    std::cerr << "\rLUT321   ";
    Ciphertext gin321 = 2 * gout79 + gout320;
    Ciphertext gout321 = ctx.eval_lut(&gin321, xor2);

    std::cerr << "\rLUT322   ";
    Ciphertext gin322 = 2 * gout79 + gout320;
    Ciphertext gout322 = ctx.eval_lut(&gin322, nand2);

    std::cerr << "\rLUT323   ";
    Ciphertext gin323 = 2 * gout219 + gout319;
    Ciphertext gout323 = ctx.eval_lut(&gin323, nand2);

    std::cerr << "\rLUT324   ";
    Ciphertext gin324 = 2 * gout323 + gout322;
    Ciphertext gout324 = ctx.eval_lut(&gin324, and2);

    std::cerr << "\rLUT325   ";
    Ciphertext gin325 = 2 * gout324 + gout311;
    Ciphertext gout325 = ctx.eval_lut(&gin325, xnor2);

    std::cerr << "\rLUT326   ";
    Ciphertext gin326 = 2 * gout276 + gout275;
    Ciphertext gout326 = ctx.eval_lut(&gin326, nand2);

    std::cerr << "\rLUT327   ";
    Ciphertext gin327 = 2 * gout48 + gout152;
    Ciphertext gout327 = ctx.eval_lut(&gin327, nand2);

    std::cerr << "\rLUT328   ";
    Ciphertext gin328 = 2 * gout153 + gout327;
    Ciphertext gout328 = ctx.eval_lut(&gin328, nand2);

    std::cerr << "\rLUT329   ";
    Ciphertext gin329 = 2 * gout308 + gout318;
    Ciphertext gout329 = ctx.eval_lut(&gin329, xnor2);

    std::cerr << "\rLUT330   ";
    Ciphertext gin330 = 2 * ct_y11 + ct_x1;
    Ciphertext gout330 = ctx.eval_lut(&gin330, and2);

    std::cerr << "\rLUT331   ";
    Ciphertext gin331 = 2 * gout48 + gout152;
    Ciphertext gout331 = ctx.eval_lut(&gin331, xor2);

    std::cerr << "\rLUT332   ";
    Ciphertext gin332 = 2 * gout227 + gout331;
    Ciphertext gout332 = ctx.eval_lut(&gin332, xor2);

    std::cerr << "\rLUT333   ";
    Ciphertext gin333 = 2 * gout227 + gout331;
    Ciphertext gout333 = ctx.eval_lut(&gin333, nand2);

    std::cerr << "\rLUT334   ";
    Ciphertext gin334 = 2 * gout86 + gout85;
    Ciphertext gout334 = ctx.eval_lut(&gin334, nand2);

    std::cerr << "\rLUT335   ";
    Ciphertext gin335 = 2 * ct_y10 + ct_x2;
    Ciphertext gout335 = ctx.eval_lut(&gin335, and2);

    std::cerr << "\rLUT336   ";
    Ciphertext gin336 = 2 * gout335 + gout30;
    Ciphertext gout336 = ctx.eval_lut(&gin336, xor2);

    std::cerr << "\rLUT337   ";
    Ciphertext gin337 = 2 * gout330 + gout336;
    Ciphertext gout337 = ctx.eval_lut(&gin337, xor2);

    std::cerr << "\rLUT338   ";
    Ciphertext gin338 = 2 * gout326 + gout337;
    Ciphertext gout338 = ctx.eval_lut(&gin338, xor2);

    std::cerr << "\rLUT339   ";
    Ciphertext gin339 = 2 * gout136 + gout338;
    Ciphertext gout339 = ctx.eval_lut(&gin339, xnor2);

    std::cerr << "\rLUT340   ";
    Ciphertext gin340 = 2 * gout326 + gout337;
    Ciphertext gout340 = ctx.eval_lut(&gin340, nand2);

    std::cerr << "\rLUT341   ";
    Ciphertext gin341 = 2 * gout330 + gout336;
    Ciphertext gout341 = ctx.eval_lut(&gin341, nand2);

    std::cerr << "\rLUT342   ";
    Ciphertext gin342 = 2 * gout335 + gout30;
    Ciphertext gout342 = ctx.eval_lut(&gin342, nand2);

    std::cerr << "\rLUT343   ";
    Ciphertext gin343 = 2 * gout7 + gout148;
    Ciphertext gout343 = ctx.eval_lut(&gin343, nand2);

    std::cerr << "\rLUT344   ";
    Ciphertext gin344 = 2 * gout131 + gout343;
    Ciphertext gout344 = ctx.eval_lut(&gin344, nand2);

    std::cerr << "\rINV345   ";
    Ciphertext gout345 = 1 - ct_y14;

    std::cerr << "\rLUT346   ";
    Ciphertext gin346 = 2 * (1 - ct_op4) + ct_op5;
    Ciphertext gout346 = ctx.eval_lut(&gin346, and2);

    std::cerr << "\rLUT347   ";
    Ciphertext gin347 = 2 * gout346 + gout315;
    Ciphertext gout347 = ctx.eval_lut(&gin347, and2);

    std::cerr << "\rLUT348   ";
    Ciphertext gin348 = 2 * gout347 + gout200;
    Ciphertext gout348 = ctx.eval_lut(&gin348, and2);

    std::cerr << "\rLUT349   ";
    Ciphertext gin349 = 2 * ct_y14 + gout348;
    Ciphertext gout349 = ctx.eval_lut(&gin349, and2);

    std::cerr << "\rLUT350   ";
    Ciphertext gin350 = 2 * ct_y13 + gout348;
    Ciphertext gout350 = ctx.eval_lut(&gin350, and2);

    std::cerr << "\rLUT351   ";
    Ciphertext gin351 = 2 * ct_y12 + gout348;
    Ciphertext gout351 = ctx.eval_lut(&gin351, nand2);

    std::cerr << "\rLUT352   ";
    Ciphertext gin352 = 2 * ct_y11 + gout348;
    Ciphertext gout352 = ctx.eval_lut(&gin352, nand2);

    std::cerr << "\rLUT353   ";
    Ciphertext gin353 = 2 * gout348 + gout251;
    Ciphertext gout353 = ctx.eval_lut(&gin353, and2);

    std::cerr << "\rLUT354   ";
    Ciphertext gin354 = 2 * (1 - gout353) + gout352;
    Ciphertext gout354 = ctx.eval_lut(&gin354, and2);

    std::cerr << "\rLUT355   ";
    Ciphertext gin355 = 2 * gout354 + gout351;
    Ciphertext gout355 = ctx.eval_lut(&gin355, nand2);

    std::cerr << "\rLUT356   ";
    Ciphertext gin356 = 2 * gout355 + gout350;
    Ciphertext gout356 = ctx.eval_lut(&gin356, or2);

    std::cerr << "\rLUT357   ";
    Ciphertext gin357 = 2 * gout356 + gout349;
    Ciphertext gout357 = ctx.eval_lut(&gin357, or2);

    std::cerr << "\rLUT358   ";
    Ciphertext gin358 = 2 * gout357 + gout13;
    Ciphertext gout358 = ctx.eval_lut(&gin358, xnor2);

    std::cerr << "\rLUT359   ";
    Ciphertext gin359 = 2 * gout345 + gout356;
    Ciphertext gout359 = ctx.eval_lut(&gin359, xnor2);

    std::cerr << "\rLUT360   ";
    Ciphertext gin360 = 2 * gout164 + gout359;
    Ciphertext gout360 = ctx.eval_lut(&gin360, xnor2);

    std::cerr << "\rLUT361   ";
    Ciphertext gin361 = 2 * ct_x14 + gout359;
    Ciphertext gout361 = ctx.eval_lut(&gin361, nand2);

    std::cerr << "\rLUT362   ";
    Ciphertext gin362 = 2 * ct_y13 + gout355;
    Ciphertext gout362 = ctx.eval_lut(&gin362, xnor2);

    std::cerr << "\rLUT363   ";
    Ciphertext gin363 = 2 * ct_x13 + gout362;
    Ciphertext gout363 = ctx.eval_lut(&gin363, xnor2);

    std::cerr << "\rINV364   ";
    Ciphertext gout364 = 1 - gout363;

    std::cerr << "\rLUT365   ";
    Ciphertext gin365 = 2 * gout90 + gout362;
    Ciphertext gout365 = ctx.eval_lut(&gin365, nand2);

    std::cerr << "\rLUT366   ";
    Ciphertext gin366 = 2 * gout90 + gout362;
    Ciphertext gout366 = ctx.eval_lut(&gin366, or2);

    std::cerr << "\rLUT367   ";
    Ciphertext gin367 = 2 * ct_y12 + gout354;
    Ciphertext gout367 = ctx.eval_lut(&gin367, xnor2);

    std::cerr << "\rLUT368   ";
    Ciphertext gin368 = 2 * gout47 + gout367;
    Ciphertext gout368 = ctx.eval_lut(&gin368, xnor2);

    std::cerr << "\rLUT369   ";
    Ciphertext gin369 = 2 * ct_x12 + gout367;
    Ciphertext gout369 = ctx.eval_lut(&gin369, nand2);

    std::cerr << "\rLUT370   ";
    Ciphertext gin370 = 2 * gout369 + gout366;
    Ciphertext gout370 = ctx.eval_lut(&gin370, nand2);

    std::cerr << "\rLUT371   ";
    Ciphertext gin371 = 2 * gout365 + gout370;
    Ciphertext gout371 = ctx.eval_lut(&gin371, nand2);

    std::cerr << "\rLUT372   ";
    Ciphertext gin372 = 2 * (1 - gout250) + gout348;
    Ciphertext gout372 = ctx.eval_lut(&gin372, and2);

    std::cerr << "\rLUT373   ";
    Ciphertext gin373 = 2 * gout161 + gout372;
    Ciphertext gout373 = ctx.eval_lut(&gin373, xnor2);

    std::cerr << "\rLUT374   ";
    Ciphertext gin374 = 2 * gout159 + gout373;
    Ciphertext gout374 = ctx.eval_lut(&gin374, xnor2);

    std::cerr << "\rLUT375   ";
    Ciphertext gin375 = 2 * ct_x10 + gout373;
    Ciphertext gout375 = ctx.eval_lut(&gin375, nand2);

    std::cerr << "\rLUT376   ";
    Ciphertext gin376 = 2 * (1 - gout249) + gout348;
    Ciphertext gout376 = ctx.eval_lut(&gin376, and2);

    std::cerr << "\rLUT377   ";
    Ciphertext gin377 = 2 * gout91 + gout376;
    Ciphertext gout377 = ctx.eval_lut(&gin377, xnor2);

    std::cerr << "\rLUT378   ";
    Ciphertext gin378 = 2 * gout89 + gout377;
    Ciphertext gout378 = ctx.eval_lut(&gin378, xnor2);

    std::cerr << "\rINV379   ";
    Ciphertext gout379 = 1 - gout378;

    std::cerr << "\rLUT380   ";
    Ciphertext gin380 = 2 * ct_x9 + gout377;
    Ciphertext gout380 = ctx.eval_lut(&gin380, or2);

    std::cerr << "\rLUT381   ";
    Ciphertext gin381 = 2 * ct_x9 + gout377;
    Ciphertext gout381 = ctx.eval_lut(&gin381, nand2);

    std::cerr << "\rLUT382   ";
    Ciphertext gin382 = 2 * (1 - gout248) + gout348;
    Ciphertext gout382 = ctx.eval_lut(&gin382, and2);

    std::cerr << "\rLUT383   ";
    Ciphertext gin383 = 2 * gout116 + gout382;
    Ciphertext gout383 = ctx.eval_lut(&gin383, xnor2);

    std::cerr << "\rLUT384   ";
    Ciphertext gin384 = 2 * gout45 + gout383;
    Ciphertext gout384 = ctx.eval_lut(&gin384, xnor2);

    std::cerr << "\rLUT385   ";
    Ciphertext gin385 = 2 * ct_x8 + gout383;
    Ciphertext gout385 = ctx.eval_lut(&gin385, nand2);

    std::cerr << "\rLUT386   ";
    Ciphertext gin386 = 2 * gout385 + gout381;
    Ciphertext gout386 = ctx.eval_lut(&gin386, nand2);

    std::cerr << "\rLUT387   ";
    Ciphertext gin387 = 2 * gout380 + gout386;
    Ciphertext gout387 = ctx.eval_lut(&gin387, nand2);

    std::cerr << "\rLUT388   ";
    Ciphertext gin388 = 2 * (1 - gout247) + gout348;
    Ciphertext gout388 = ctx.eval_lut(&gin388, and2);

    std::cerr << "\rLUT389   ";
    Ciphertext gin389 = 2 * gout51 + gout388;
    Ciphertext gout389 = ctx.eval_lut(&gin389, xnor2);

    std::cerr << "\rLUT390   ";
    Ciphertext gin390 = 2 * ct_x7 + gout389;
    Ciphertext gout390 = ctx.eval_lut(&gin390, nand2);

    std::cerr << "\rLUT391   ";
    Ciphertext gin391 = 2 * (1 - gout246) + gout348;
    Ciphertext gout391 = ctx.eval_lut(&gin391, and2);

    std::cerr << "\rLUT392   ";
    Ciphertext gin392 = 2 * gout241 + gout391;
    Ciphertext gout392 = ctx.eval_lut(&gin392, xnor2);

    std::cerr << "\rLUT393   ";
    Ciphertext gin393 = 2 * gout162 + gout392;
    Ciphertext gout393 = ctx.eval_lut(&gin393, xnor2);

    std::cerr << "\rLUT394   ";
    Ciphertext gin394 = 2 * ct_x6 + gout392;
    Ciphertext gout394 = ctx.eval_lut(&gin394, nand2);

    std::cerr << "\rLUT395   ";
    Ciphertext gin395 = 2 * (1 - gout245) + gout348;
    Ciphertext gout395 = ctx.eval_lut(&gin395, and2);

    std::cerr << "\rLUT396   ";
    Ciphertext gin396 = 2 * gout165 + gout395;
    Ciphertext gout396 = ctx.eval_lut(&gin396, xnor2);

    std::cerr << "\rLUT397   ";
    Ciphertext gin397 = 2 * gout94 + gout396;
    Ciphertext gout397 = ctx.eval_lut(&gin397, xnor2);

    std::cerr << "\rLUT398   ";
    Ciphertext gin398 = 2 * ct_x5 + gout396;
    Ciphertext gout398 = ctx.eval_lut(&gin398, nand2);

    std::cerr << "\rLUT399   ";
    Ciphertext gin399 = 2 * (1 - gout244) + gout348;
    Ciphertext gout399 = ctx.eval_lut(&gin399, and2);

    std::cerr << "\rLUT400   ";
    Ciphertext gin400 = 2 * gout5 + gout399;
    Ciphertext gout400 = ctx.eval_lut(&gin400, xnor2);

    std::cerr << "\rLUT401   ";
    Ciphertext gin401 = 2 * gout44 + gout400;
    Ciphertext gout401 = ctx.eval_lut(&gin401, xnor2);

    std::cerr << "\rLUT402   ";
    Ciphertext gin402 = 2 * ct_x4 + gout400;
    Ciphertext gout402 = ctx.eval_lut(&gin402, nand2);

    std::cerr << "\rLUT403   ";
    Ciphertext gin403 = 2 * (1 - gout243) + gout348;
    Ciphertext gout403 = ctx.eval_lut(&gin403, and2);

    std::cerr << "\rLUT404   ";
    Ciphertext gin404 = 2 * gout33 + gout403;
    Ciphertext gout404 = ctx.eval_lut(&gin404, xnor2);

    std::cerr << "\rLUT405   ";
    Ciphertext gin405 = 2 * gout217 + gout404;
    Ciphertext gout405 = ctx.eval_lut(&gin405, xnor2);

    std::cerr << "\rLUT406   ";
    Ciphertext gin406 = 2 * ct_x3 + gout404;
    Ciphertext gout406 = ctx.eval_lut(&gin406, nand2);

    std::cerr << "\rLUT407   ";
    Ciphertext gin407 = 2 * gout348 + gout198;
    Ciphertext gout407 = ctx.eval_lut(&gin407, and2);

    std::cerr << "\rLUT408   ";
    Ciphertext gin408 = 2 * gout242 + gout407;
    Ciphertext gout408 = ctx.eval_lut(&gin408, xnor2);

    std::cerr << "\rLUT409   ";
    Ciphertext gin409 = 2 * gout154 + gout408;
    Ciphertext gout409 = ctx.eval_lut(&gin409, xnor2);

    std::cerr << "\rLUT410   ";
    Ciphertext gin410 = 2 * ct_x2 + gout408;
    Ciphertext gout410 = ctx.eval_lut(&gin410, nand2);

    std::cerr << "\rLUT411   ";
    Ciphertext gin411 = 2 * ct_y0 + gout348;
    Ciphertext gout411 = ctx.eval_lut(&gin411, and2);

    std::cerr << "\rLUT412   ";
    Ciphertext gin412 = 2 * gout122 + gout411;
    Ciphertext gout412 = ctx.eval_lut(&gin412, xnor2);

    std::cerr << "\rLUT413   ";
    Ciphertext gin413 = 2 * gout92 + gout412;
    Ciphertext gout413 = ctx.eval_lut(&gin413, xnor2);

    std::cerr << "\rLUT414   ";
    Ciphertext gin414 = 2 * gout71 + gout413;
    Ciphertext gout414 = ctx.eval_lut(&gin414, xnor2);

    std::cerr << "\rLUT415   ";
    Ciphertext gin415 = 2 * gout67 + gout413;
    Ciphertext gout415 = ctx.eval_lut(&gin415, nand2);

    std::cerr << "\rLUT416   ";
    Ciphertext gin416 = 2 * ct_x1 + gout412;
    Ciphertext gout416 = ctx.eval_lut(&gin416, nand2);

    std::cerr << "\rLUT417   ";
    Ciphertext gin417 = 2 * gout416 + gout415;
    Ciphertext gout417 = ctx.eval_lut(&gin417, nand2);

    std::cerr << "\rLUT418   ";
    Ciphertext gin418 = 2 * gout417 + gout409;
    Ciphertext gout418 = ctx.eval_lut(&gin418, xnor2);

    std::cerr << "\rLUT419   ";
    Ciphertext gin419 = 2 * gout417 + gout409;
    Ciphertext gout419 = ctx.eval_lut(&gin419, nand2);

    std::cerr << "\rLUT420   ";
    Ciphertext gin420 = 2 * gout410 + gout419;
    Ciphertext gout420 = ctx.eval_lut(&gin420, nand2);

    std::cerr << "\rLUT421   ";
    Ciphertext gin421 = 2 * gout420 + gout405;
    Ciphertext gout421 = ctx.eval_lut(&gin421, nand2);

    std::cerr << "\rLUT422   ";
    Ciphertext gin422 = 2 * gout406 + gout421;
    Ciphertext gout422 = ctx.eval_lut(&gin422, nand2);

    std::cerr << "\rLUT423   ";
    Ciphertext gin423 = 2 * gout422 + gout401;
    Ciphertext gout423 = ctx.eval_lut(&gin423, xnor2);

    std::cerr << "\rLUT424   ";
    Ciphertext gin424 = 2 * gout422 + gout401;
    Ciphertext gout424 = ctx.eval_lut(&gin424, nand2);

    std::cerr << "\rLUT425   ";
    Ciphertext gin425 = 2 * gout402 + gout424;
    Ciphertext gout425 = ctx.eval_lut(&gin425, nand2);

    std::cerr << "\rLUT426   ";
    Ciphertext gin426 = 2 * gout425 + gout397;
    Ciphertext gout426 = ctx.eval_lut(&gin426, xnor2);

    std::cerr << "\rLUT427   ";
    Ciphertext gin427 = 2 * gout425 + gout397;
    Ciphertext gout427 = ctx.eval_lut(&gin427, nand2);

    std::cerr << "\rLUT428   ";
    Ciphertext gin428 = 2 * gout398 + gout427;
    Ciphertext gout428 = ctx.eval_lut(&gin428, nand2);

    std::cerr << "\rLUT429   ";
    Ciphertext gin429 = 2 * gout428 + gout393;
    Ciphertext gout429 = ctx.eval_lut(&gin429, xnor2);

    std::cerr << "\rLUT430   ";
    Ciphertext gin430 = 2 * gout428 + gout393;
    Ciphertext gout430 = ctx.eval_lut(&gin430, nand2);

    std::cerr << "\rLUT431   ";
    Ciphertext gin431 = 2 * gout394 + gout430;
    Ciphertext gout431 = ctx.eval_lut(&gin431, nand2);

    std::cerr << "\rLUT432   ";
    Ciphertext gin432 = 2 * gout347 + gout253;
    Ciphertext gout432 = ctx.eval_lut(&gin432, and2);

    std::cerr << "\rLUT433   ";
    Ciphertext gin433 = 2 * gout432 + gout348;
    Ciphertext gout433 = ctx.eval_lut(&gin433, or2);

    std::cerr << "\rLUT434   ";
    Ciphertext gin434 = 2 * gout211 + gout432;
    Ciphertext gout434 = ctx.eval_lut(&gin434, and2);

    std::cerr << "\rIMUX435  ";
    Ciphertext gin435A = 2 * gout305 + gout434;
    Ciphertext gout435A = ctx.eval_lut(&gin435A, and2);
    Ciphertext gin435B = 2 * gout418 + (1 - gout434);
    Ciphertext gout435B = ctx.eval_lut(&gin435B, and2);
    Ciphertext gout435 = gout435A + gout435B;

    std::cerr << "\rLUT436   ";
    Ciphertext gin436 = 2 * gout434 + gout281;
    Ciphertext gout436 = ctx.eval_lut(&gin436, or2);

    std::cerr << "\rLUT437   ";
    Ciphertext gin437 = 2 * gout433 + gout436;
    Ciphertext gout437 = ctx.eval_lut(&gin437, and2);

    std::cerr << "\rLUT438   ";
    Ciphertext gin438 = 2 * gout434 + gout67;
    Ciphertext gout438 = ctx.eval_lut(&gin438, nand2);

    std::cerr << "\rLUT439   ";
    Ciphertext gin439 = 2 * gout438 + gout437;
    Ciphertext gout439 = ctx.eval_lut(&gin439, nand2);

    std::cerr << "\rINV440   ";
    Ciphertext gout440 = 1 - gout434;

    std::cerr << "\rLUT441   ";
    Ciphertext gin441 = 2 * gout440 + gout414;
    Ciphertext gout441 = ctx.eval_lut(&gin441, nand2);

    std::cerr << "\rLUT442   ";
    Ciphertext gin442 = 2 * ct_y12 + ct_x1;
    Ciphertext gout442 = ctx.eval_lut(&gin442, nand2);

    std::cerr << "\rLUT443   ";
    Ciphertext gin443 = 2 * gout442 + (1 - gout309);
    Ciphertext gout443 = ctx.eval_lut(&gin443, or2);

    std::cerr << "\rLUT444   ";
    Ciphertext gin444 = 2 * gout443 + gout93;
    Ciphertext gout444 = ctx.eval_lut(&gin444, nand2);

    std::cerr << "\rLUT445   ";
    Ciphertext gin445 = 2 * gout444 + gout263;
    Ciphertext gout445 = ctx.eval_lut(&gin445, xnor2);

    std::cerr << "\rLUT446   ";
    Ciphertext gin446 = 2 * gout442 + gout39;
    Ciphertext gout446 = ctx.eval_lut(&gin446, xnor2);

    std::cerr << "\rLUT447   ";
    Ciphertext gin447 = 2 * gout117 + gout230;
    Ciphertext gout447 = ctx.eval_lut(&gin447, nand2);

    std::cerr << "\rLUT448   ";
    Ciphertext gin448 = 2 * gout231 + gout447;
    Ciphertext gout448 = ctx.eval_lut(&gin448, nand2);

    std::cerr << "\rLUT449   ";
    Ciphertext gin449 = 2 * gout448 + gout332;
    Ciphertext gout449 = ctx.eval_lut(&gin449, xor2);

    std::cerr << "\rLUT450   ";
    Ciphertext gin450 = 2 * gout448 + gout332;
    Ciphertext gout450 = ctx.eval_lut(&gin450, nand2);

    std::cerr << "\rLUT451   ";
    Ciphertext gin451 = 2 * gout333 + gout450;
    Ciphertext gout451 = ctx.eval_lut(&gin451, nand2);

    std::cerr << "\rLUT452   ";
    Ciphertext gin452 = 2 * gout2 + gout272;
    Ciphertext gout452 = ctx.eval_lut(&gin452, and2);

    std::cerr << "\rLUT453   ";
    Ciphertext gin453 = 2 * gout452 + gout274;
    Ciphertext gout453 = ctx.eval_lut(&gin453, and2);

    std::cerr << "\rINV454   ";
    Ciphertext gout454 = 1 - gout452;

    std::cerr << "\rLUT455   ";
    Ciphertext gin455 = 2 * gout454 + gout274;
    Ciphertext gout455 = ctx.eval_lut(&gin455, xnor2);

    std::cerr << "\rLUT456   ";
    Ciphertext gin456 = 2 * ct_y4 + ct_x2;
    Ciphertext gout456 = ctx.eval_lut(&gin456, and2);

    std::cerr << "\rLUT457   ";
    Ciphertext gin457 = 2 * gout160 + gout456;
    Ciphertext gout457 = ctx.eval_lut(&gin457, xnor2);

    std::cerr << "\rLUT458   ";
    Ciphertext gin458 = 2 * gout106 + gout457;
    Ciphertext gout458 = ctx.eval_lut(&gin458, xor2);

    std::cerr << "\rLUT459   ";
    Ciphertext gin459 = 2 * gout106 + gout457;
    Ciphertext gout459 = ctx.eval_lut(&gin459, nand2);

    std::cerr << "\rLUT460   ";
    Ciphertext gin460 = 2 * gout113 + gout459;
    Ciphertext gout460 = ctx.eval_lut(&gin460, nand2);

    std::cerr << "\rLUT461   ";
    Ciphertext gin461 = 2 * gout460 + gout270;
    Ciphertext gout461 = ctx.eval_lut(&gin461, xor2);

    std::cerr << "\rLUT462   ";
    Ciphertext gin462 = 2 * gout460 + gout270;
    Ciphertext gout462 = ctx.eval_lut(&gin462, and2);

    std::cerr << "\rLUT463   ";
    Ciphertext gin463 = 2 * ct_y0 + ct_x3;
    Ciphertext gout463 = ctx.eval_lut(&gin463, and2);

    std::cerr << "\rLUT464   ";
    Ciphertext gin464 = 2 * gout463 + gout28;
    Ciphertext gout464 = ctx.eval_lut(&gin464, nand2);

    std::cerr << "\rLUT465   ";
    Ciphertext gin465 = 2 * gout463 + gout163;
    Ciphertext gout465 = ctx.eval_lut(&gin465, nand2);

    std::cerr << "\rLUT466   ";
    Ciphertext gin466 = 2 * gout145 + gout465;
    Ciphertext gout466 = ctx.eval_lut(&gin466, nand2);

    std::cerr << "\rINV467   ";
    Ciphertext gout467 = 1 - gout463;

    std::cerr << "\rLUT468   ";
    Ciphertext gin468 = 2 * gout467 + gout163;
    Ciphertext gout468 = ctx.eval_lut(&gin468, xnor2);

    std::cerr << "\rLUT469   ";
    Ciphertext gin469 = 2 * ct_y1 + ct_x14;
    Ciphertext gout469 = ctx.eval_lut(&gin469, and2);

    std::cerr << "\rLUT470   ";
    Ciphertext gin470 = 2 * gout469 + gout46;
    Ciphertext gout470 = ctx.eval_lut(&gin470, xnor2);

    std::cerr << "\rLUT471   ";
    Ciphertext gin471 = 2 * ct_y11 + ct_x2;
    Ciphertext gout471 = ctx.eval_lut(&gin471, and2);

    std::cerr << "\rLUT472   ";
    Ciphertext gin472 = 2 * gout471 + gout100;
    Ciphertext gout472 = ctx.eval_lut(&gin472, xor2);

    std::cerr << "\rLUT473   ";
    Ciphertext gin473 = 2 * gout471 + gout100;
    Ciphertext gout473 = ctx.eval_lut(&gin473, nand2);

    std::cerr << "\rLUT474   ";
    Ciphertext gin474 = 2 * gout101 + gout473;
    Ciphertext gout474 = ctx.eval_lut(&gin474, nand2);

    std::cerr << "\rLUT475   ";
    Ciphertext gin475 = 2 * gout474 + gout284;
    Ciphertext gout475 = ctx.eval_lut(&gin475, xnor2);

    std::cerr << "\rLUT476   ";
    Ciphertext gin476 = 2 * gout475 + gout102;
    Ciphertext gout476 = ctx.eval_lut(&gin476, xnor2);

    std::cerr << "\rLUT477   ";
    Ciphertext gin477 = 2 * (1 - gout475) + gout102;
    Ciphertext gout477 = ctx.eval_lut(&gin477, and2);

    std::cerr << "\rLUT478   ";
    Ciphertext gin478 = 2 * gout474 + gout284;
    Ciphertext gout478 = ctx.eval_lut(&gin478, nand2);

    std::cerr << "\rLUT479   ";
    Ciphertext gin479 = 2 * gout115 + gout338;
    Ciphertext gout479 = ctx.eval_lut(&gin479, nand2);

    std::cerr << "\rLUT480   ";
    Ciphertext gin480 = 2 * gout190 + gout256;
    Ciphertext gout480 = ctx.eval_lut(&gin480, nand2);

    std::cerr << "\rLUT481   ";
    Ciphertext gin481 = 2 * gout480 + gout84;
    Ciphertext gout481 = ctx.eval_lut(&gin481, xnor2);

    std::cerr << "\rLUT482   ";
    Ciphertext gin482 = 2 * gout481 + gout157;
    Ciphertext gout482 = ctx.eval_lut(&gin482, xnor2);

    std::cerr << "\rLUT483   ";
    Ciphertext gin483 = 2 * (1 - gout481) + gout157;
    Ciphertext gout483 = ctx.eval_lut(&gin483, and2);

    std::cerr << "\rLUT484   ";
    Ciphertext gin484 = 2 * gout480 + gout84;
    Ciphertext gout484 = ctx.eval_lut(&gin484, and2);

    std::cerr << "\rLUT485   ";
    Ciphertext gin485 = 2 * gout484 + gout483;
    Ciphertext gout485 = ctx.eval_lut(&gin485, or2);

    std::cerr << "\rLUT486   ";
    Ciphertext gin486 = 2 * gout16 + gout107;
    Ciphertext gout486 = ctx.eval_lut(&gin486, nand2);

    std::cerr << "\rLUT487   ";
    Ciphertext gin487 = 2 * gout486 + gout110;
    Ciphertext gout487 = ctx.eval_lut(&gin487, nand2);

    std::cerr << "\rLUT488   ";
    Ciphertext gin488 = 2 * gout487 + gout268;
    Ciphertext gout488 = ctx.eval_lut(&gin488, xnor2);

    std::cerr << "\rLUT489   ";
    Ciphertext gin489 = 2 * gout488 + gout134;
    Ciphertext gout489 = ctx.eval_lut(&gin489, xnor2);

    std::cerr << "\rLUT490   ";
    Ciphertext gin490 = 2 * (1 - gout488) + gout134;
    Ciphertext gout490 = ctx.eval_lut(&gin490, and2);

    std::cerr << "\rLUT491   ";
    Ciphertext gin491 = 2 * gout487 + gout268;
    Ciphertext gout491 = ctx.eval_lut(&gin491, and2);

    std::cerr << "\rLUT492   ";
    Ciphertext gin492 = 2 * gout491 + gout490;
    Ciphertext gout492 = ctx.eval_lut(&gin492, or2);

    std::cerr << "\rLUT493   ";
    Ciphertext gin493 = 2 * gout492 + gout482;
    Ciphertext gout493 = ctx.eval_lut(&gin493, xnor2);

    std::cerr << "\rLUT494   ";
    Ciphertext gin494 = 2 * gout492 + gout482;
    Ciphertext gout494 = ctx.eval_lut(&gin494, and2);

    std::cerr << "\rLUT495   ";
    Ciphertext gin495 = 2 * gout43 + gout313;
    Ciphertext gout495 = ctx.eval_lut(&gin495, xor2);

    std::cerr << "\rLUT496   ";
    Ciphertext gin496 = 2 * gout254 + gout495;
    Ciphertext gout496 = ctx.eval_lut(&gin496, xnor2);

    std::cerr << "\rLUT497   ";
    Ciphertext gin497 = 2 * gout496 + gout223;
    Ciphertext gout497 = ctx.eval_lut(&gin497, xnor2);

    std::cerr << "\rLUT498   ";
    Ciphertext gin498 = 2 * gout466 + gout497;
    Ciphertext gout498 = ctx.eval_lut(&gin498, xor2);

    std::cerr << "\rLUT499   ";
    Ciphertext gin499 = 2 * gout466 + gout497;
    Ciphertext gout499 = ctx.eval_lut(&gin499, and2);

    std::cerr << "\rLUT500   ";
    Ciphertext gin500 = 2 * (1 - gout496) + gout223;
    Ciphertext gout500 = ctx.eval_lut(&gin500, and2);

    std::cerr << "\rLUT501   ";
    Ciphertext gin501 = 2 * gout254 + gout495;
    Ciphertext gout501 = ctx.eval_lut(&gin501, and2);

    std::cerr << "\rLUT502   ";
    Ciphertext gin502 = 2 * gout501 + gout500;
    Ciphertext gout502 = ctx.eval_lut(&gin502, or2);

    std::cerr << "\rLUT503   ";
    Ciphertext gin503 = 2 * gout27 + gout50;
    Ciphertext gout503 = ctx.eval_lut(&gin503, xnor2);

    std::cerr << "\rLUT504   ";
    Ciphertext gin504 = 2 * gout216 + gout503;
    Ciphertext gout504 = ctx.eval_lut(&gin504, xor2);

    std::cerr << "\rLUT505   ";
    Ciphertext gin505 = 2 * gout216 + gout503;
    Ciphertext gout505 = ctx.eval_lut(&gin505, nand2);

    std::cerr << "\rLUT506   ";
    Ciphertext gin506 = 2 * gout255 + gout505;
    Ciphertext gout506 = ctx.eval_lut(&gin506, nand2);

    std::cerr << "\rLUT507   ";
    Ciphertext gin507 = 2 * gout506 + gout173;
    Ciphertext gout507 = ctx.eval_lut(&gin507, xor2);

    std::cerr << "\rLUT508   ";
    Ciphertext gin508 = 2 * gout344 + gout507;
    Ciphertext gout508 = ctx.eval_lut(&gin508, xor2);

    std::cerr << "\rLUT509   ";
    Ciphertext gin509 = 2 * gout344 + gout507;
    Ciphertext gout509 = ctx.eval_lut(&gin509, nand2);

    std::cerr << "\rLUT510   ";
    Ciphertext gin510 = 2 * gout506 + gout173;
    Ciphertext gout510 = ctx.eval_lut(&gin510, nand2);

    std::cerr << "\rLUT511   ";
    Ciphertext gin511 = 2 * gout510 + gout509;
    Ciphertext gout511 = ctx.eval_lut(&gin511, nand2);

    std::cerr << "\rLUT512   ";
    Ciphertext gin512 = 2 * gout511 + gout455;
    Ciphertext gout512 = ctx.eval_lut(&gin512, xor2);

    std::cerr << "\rLUT513   ";
    Ciphertext gin513 = 2 * gout511 + gout455;
    Ciphertext gout513 = ctx.eval_lut(&gin513, and2);

    std::cerr << "\rLUT514   ";
    Ciphertext gin514 = 2 * ct_y2 + ct_x4;
    Ciphertext gout514 = ctx.eval_lut(&gin514, and2);

    std::cerr << "\rLUT515   ";
    Ciphertext gin515 = 2 * gout204 + gout514;
    Ciphertext gout515 = ctx.eval_lut(&gin515, xor2);

    std::cerr << "\rLUT516   ";
    Ciphertext gin516 = 2 * gout302 + gout515;
    Ciphertext gout516 = ctx.eval_lut(&gin516, xor2);

    std::cerr << "\rLUT517   ";
    Ciphertext gin517 = 2 * gout300 + gout516;
    Ciphertext gout517 = ctx.eval_lut(&gin517, xnor2);

    std::cerr << "\rLUT518   ";
    Ciphertext gin518 = 2 * gout517 + gout458;
    Ciphertext gout518 = ctx.eval_lut(&gin518, xnor2);

    std::cerr << "\rLUT519   ";
    Ciphertext gin519 = 2 * (1 - gout517) + gout458;
    Ciphertext gout519 = ctx.eval_lut(&gin519, and2);

    std::cerr << "\rLUT520   ";
    Ciphertext gin520 = 2 * gout300 + gout516;
    Ciphertext gout520 = ctx.eval_lut(&gin520, and2);

    std::cerr << "\rLUT521   ";
    Ciphertext gin521 = 2 * gout520 + gout519;
    Ciphertext gout521 = ctx.eval_lut(&gin521, or2);

    std::cerr << "\rLUT522   ";
    Ciphertext gin522 = 2 * gout302 + gout515;
    Ciphertext gout522 = ctx.eval_lut(&gin522, nand2);

    std::cerr << "\rLUT523   ";
    Ciphertext gin523 = 2 * gout204 + gout514;
    Ciphertext gout523 = ctx.eval_lut(&gin523, nand2);

    std::cerr << "\rLUT524   ";
    Ciphertext gin524 = 2 * gout523 + gout522;
    Ciphertext gout524 = ctx.eval_lut(&gin524, nand2);

    std::cerr << "\rLUT525   ";
    Ciphertext gin525 = 2 * gout524 + gout258;
    Ciphertext gout525 = ctx.eval_lut(&gin525, xnor2);

    std::cerr << "\rLUT526   ";
    Ciphertext gin526 = 2 * gout524 + gout258;
    Ciphertext gout526 = ctx.eval_lut(&gin526, and2);

    std::cerr << "\rLUT527   ";
    Ciphertext gin527 = 2 * gout433 + gout435;
    Ciphertext gout527 = ctx.eval_lut(&gin527, nand2);

    std::cerr << "\rLUT528   ";
    Ciphertext gin528 = 2 * gout340 + gout479;
    Ciphertext gout528 = ctx.eval_lut(&gin528, nand2);

    std::cerr << "\rLUT529   ";
    Ciphertext gin529 = 2 * gout29 + gout129;
    Ciphertext gout529 = ctx.eval_lut(&gin529, nand2);

    std::cerr << "\rLUT530   ";
    Ciphertext gin530 = 2 * ct_y5 + ct_x7;
    Ciphertext gout530 = ctx.eval_lut(&gin530, and2);

    std::cerr << "\rLUT531   ";
    Ciphertext gin531 = 2 * gout530 + gout130;
    Ciphertext gout531 = ctx.eval_lut(&gin531, xor2);

    std::cerr << "\rLUT532   ";
    Ciphertext gin532 = 2 * gout530 + gout130;
    Ciphertext gout532 = ctx.eval_lut(&gin532, nand2);

    std::cerr << "\rLUT533   ";
    Ciphertext gin533 = 2 * gout529 + gout532;
    Ciphertext gout533 = ctx.eval_lut(&gin533, nand2);

    std::cerr << "\rLUT534   ";
    Ciphertext gin534 = 2 * gout533 + gout73;
    Ciphertext gout534 = ctx.eval_lut(&gin534, xor2);

    std::cerr << "\rLUT535   ";
    Ciphertext gin535 = 2 * gout328 + gout534;
    Ciphertext gout535 = ctx.eval_lut(&gin535, xor2);

    std::cerr << "\rLUT536   ";
    Ciphertext gin536 = 2 * gout328 + gout534;
    Ciphertext gout536 = ctx.eval_lut(&gin536, nand2);

    std::cerr << "\rLUT537   ";
    Ciphertext gin537 = 2 * gout533 + gout73;
    Ciphertext gout537 = ctx.eval_lut(&gin537, nand2);

    std::cerr << "\rLUT538   ";
    Ciphertext gin538 = 2 * gout537 + gout536;
    Ciphertext gout538 = ctx.eval_lut(&gin538, nand2);

    std::cerr << "\rLUT539   ";
    Ciphertext gin539 = 2 * gout538 + gout476;
    Ciphertext gout539 = ctx.eval_lut(&gin539, xor2);

    std::cerr << "\rLUT540   ";
    Ciphertext gin540 = 2 * gout538 + gout476;
    Ciphertext gout540 = ctx.eval_lut(&gin540, nand2);

    std::cerr << "\rLUT541   ";
    Ciphertext gin541 = 2 * ct_y3 + ct_x5;
    Ciphertext gout541 = ctx.eval_lut(&gin541, and2);

    std::cerr << "\rLUT542   ";
    Ciphertext gin542 = 2 * gout541 + gout42;
    Ciphertext gout542 = ctx.eval_lut(&gin542, xor2);

    std::cerr << "\rLUT543   ";
    Ciphertext gin543 = 2 * gout301 + gout542;
    Ciphertext gout543 = ctx.eval_lut(&gin543, xor2);

    std::cerr << "\rLUT544   ";
    Ciphertext gin544 = 2 * gout288 + gout543;
    Ciphertext gout544 = ctx.eval_lut(&gin544, xnor2);

    std::cerr << "\rLUT545   ";
    Ciphertext gin545 = 2 * gout544 + gout278;
    Ciphertext gout545 = ctx.eval_lut(&gin545, xnor2);

    std::cerr << "\rLUT546   ";
    Ciphertext gin546 = 2 * (1 - gout544) + gout278;
    Ciphertext gout546 = ctx.eval_lut(&gin546, and2);

    std::cerr << "\rLUT547   ";
    Ciphertext gin547 = 2 * gout288 + gout543;
    Ciphertext gout547 = ctx.eval_lut(&gin547, and2);

    std::cerr << "\rLUT548   ";
    Ciphertext gin548 = 2 * gout547 + gout546;
    Ciphertext gout548 = ctx.eval_lut(&gin548, or2);

    std::cerr << "\rLUT549   ";
    Ciphertext gin549 = 2 * gout301 + gout542;
    Ciphertext gout549 = ctx.eval_lut(&gin549, nand2);

    std::cerr << "\rLUT550   ";
    Ciphertext gin550 = 2 * gout541 + gout42;
    Ciphertext gout550 = ctx.eval_lut(&gin550, nand2);

    std::cerr << "\rLUT551   ";
    Ciphertext gin551 = 2 * gout550 + gout549;
    Ciphertext gout551 = ctx.eval_lut(&gin551, nand2);

    std::cerr << "\rLUT552   ";
    Ciphertext gin552 = 2 * gout551 + gout109;
    Ciphertext gout552 = ctx.eval_lut(&gin552, xnor2);

    std::cerr << "\rLUT553   ";
    Ciphertext gin553 = 2 * gout552 + gout504;
    Ciphertext gout553 = ctx.eval_lut(&gin553, xnor2);

    std::cerr << "\rLUT554   ";
    Ciphertext gin554 = 2 * gout548 + gout553;
    Ciphertext gout554 = ctx.eval_lut(&gin554, xnor2);

    std::cerr << "\rLUT555   ";
    Ciphertext gin555 = 2 * gout548 + gout553;
    Ciphertext gout555 = ctx.eval_lut(&gin555, and2);

    std::cerr << "\rLUT556   ";
    Ciphertext gin556 = 2 * (1 - gout552) + gout504;
    Ciphertext gout556 = ctx.eval_lut(&gin556, and2);

    std::cerr << "\rLUT557   ";
    Ciphertext gin557 = 2 * gout551 + gout109;
    Ciphertext gout557 = ctx.eval_lut(&gin557, and2);

    std::cerr << "\rLUT558   ";
    Ciphertext gin558 = 2 * gout557 + gout556;
    Ciphertext gout558 = ctx.eval_lut(&gin558, or2);

    std::cerr << "\rLUT559   ";
    Ciphertext gin559 = 2 * gout558 + gout489;
    Ciphertext gout559 = ctx.eval_lut(&gin559, xnor2);

    std::cerr << "\rLUT560   ";
    Ciphertext gin560 = 2 * gout559 + gout508;
    Ciphertext gout560 = ctx.eval_lut(&gin560, xnor2);

    std::cerr << "\rLUT561   ";
    Ciphertext gin561 = 2 * (1 - gout559) + gout508;
    Ciphertext gout561 = ctx.eval_lut(&gin561, and2);

    std::cerr << "\rLUT562   ";
    Ciphertext gin562 = 2 * gout558 + gout489;
    Ciphertext gout562 = ctx.eval_lut(&gin562, and2);

    std::cerr << "\rLUT563   ";
    Ciphertext gin563 = 2 * gout562 + gout561;
    Ciphertext gout563 = ctx.eval_lut(&gin563, or2);

    std::cerr << "\rLUT564   ";
    Ciphertext gin564 = 2 * gout434 + gout317;
    Ciphertext gout564 = ctx.eval_lut(&gin564, nand2);

    std::cerr << "\rLUT565   ";
    Ciphertext gin565 = 2 * gout433 + gout564;
    Ciphertext gout565 = ctx.eval_lut(&gin565, and2);

    std::cerr << "\rLUT566   ";
    Ciphertext gin566 = 2 * gout441 + gout565;
    Ciphertext gout566 = ctx.eval_lut(&gin566, nand2);

    std::cerr << "\rLUT567   ";
    Ciphertext gin567 = 2 * gout478 + (1 - gout477);
    Ciphertext gout567 = ctx.eval_lut(&gin567, and2);

    std::cerr << "\rLUT568   ";
    Ciphertext gin568 = 2 * gout325 + gout567;
    Ciphertext gout568 = ctx.eval_lut(&gin568, xnor2);

    std::cerr << "\rLUT569   ";
    Ciphertext gin569 = 2 * ct_y1 + ct_x11;
    Ciphertext gout569 = ctx.eval_lut(&gin569, and2);

    std::cerr << "\rLUT570   ";
    Ciphertext gin570 = 2 * gout569 + gout252;
    Ciphertext gout570 = ctx.eval_lut(&gin570, xor2);

    std::cerr << "\rLUT571   ";
    Ciphertext gin571 = 2 * gout334 + gout570;
    Ciphertext gout571 = ctx.eval_lut(&gin571, xnor2);

    std::cerr << "\rLUT572   ";
    Ciphertext gin572 = 2 * gout571 + gout531;
    Ciphertext gout572 = ctx.eval_lut(&gin572, xnor2);

    std::cerr << "\rLUT573   ";
    Ciphertext gin573 = 2 * gout485 + gout572;
    Ciphertext gout573 = ctx.eval_lut(&gin573, xnor2);

    std::cerr << "\rLUT574   ";
    Ciphertext gin574 = 2 * gout573 + gout449;
    Ciphertext gout574 = ctx.eval_lut(&gin574, xnor2);

    std::cerr << "\rLUT575   ";
    Ciphertext gin575 = 2 * (1 - gout573) + gout449;
    Ciphertext gout575 = ctx.eval_lut(&gin575, and2);

    std::cerr << "\rLUT576   ";
    Ciphertext gin576 = 2 * gout485 + gout572;
    Ciphertext gout576 = ctx.eval_lut(&gin576, and2);

    std::cerr << "\rLUT577   ";
    Ciphertext gin577 = 2 * gout576 + gout575;
    Ciphertext gout577 = ctx.eval_lut(&gin577, or2);

    std::cerr << "\rLUT578   ";
    Ciphertext gin578 = 2 * (1 - gout571) + gout531;
    Ciphertext gout578 = ctx.eval_lut(&gin578, and2);

    std::cerr << "\rLUT579   ";
    Ciphertext gin579 = 2 * gout334 + gout570;
    Ciphertext gout579 = ctx.eval_lut(&gin579, and2);

    std::cerr << "\rLUT580   ";
    Ciphertext gin580 = 2 * gout579 + gout578;
    Ciphertext gout580 = ctx.eval_lut(&gin580, or2);

    std::cerr << "\rLUT581   ";
    Ciphertext gin581 = 2 * gout569 + gout252;
    Ciphertext gout581 = ctx.eval_lut(&gin581, nand2);

    std::cerr << "\rLUT582   ";
    Ciphertext gin582 = 2 * gout228 + gout581;
    Ciphertext gout582 = ctx.eval_lut(&gin582, nand2);

    std::cerr << "\rLUT583   ";
    Ciphertext gin583 = 2 * gout582 + gout287;
    Ciphertext gout583 = ctx.eval_lut(&gin583, xnor2);

    std::cerr << "\rLUT584   ";
    Ciphertext gin584 = 2 * gout583 + gout139;
    Ciphertext gout584 = ctx.eval_lut(&gin584, xnor2);

    std::cerr << "\rLUT585   ";
    Ciphertext gin585 = 2 * gout580 + gout584;
    Ciphertext gout585 = ctx.eval_lut(&gin585, xnor2);

    std::cerr << "\rLUT586   ";
    Ciphertext gin586 = 2 * gout585 + gout535;
    Ciphertext gout586 = ctx.eval_lut(&gin586, xnor2);

    std::cerr << "\rLUT587   ";
    Ciphertext gin587 = 2 * gout577 + gout586;
    Ciphertext gout587 = ctx.eval_lut(&gin587, xnor2);

    std::cerr << "\rLUT588   ";
    Ciphertext gin588 = 2 * gout577 + gout586;
    Ciphertext gout588 = ctx.eval_lut(&gin588, and2);

    std::cerr << "\rLUT589   ";
    Ciphertext gin589 = 2 * (1 - gout585) + gout535;
    Ciphertext gout589 = ctx.eval_lut(&gin589, and2);

    std::cerr << "\rLUT590   ";
    Ciphertext gin590 = 2 * gout580 + gout584;
    Ciphertext gout590 = ctx.eval_lut(&gin590, and2);

    std::cerr << "\rLUT591   ";
    Ciphertext gin591 = 2 * gout590 + gout589;
    Ciphertext gout591 = ctx.eval_lut(&gin591, or2);

    std::cerr << "\rLUT592   ";
    Ciphertext gin592 = 2 * (1 - gout583) + gout139;
    Ciphertext gout592 = ctx.eval_lut(&gin592, and2);

    std::cerr << "\rLUT593   ";
    Ciphertext gin593 = 2 * gout582 + gout287;
    Ciphertext gout593 = ctx.eval_lut(&gin593, and2);

    std::cerr << "\rLUT594   ";
    Ciphertext gin594 = 2 * gout593 + gout592;
    Ciphertext gout594 = ctx.eval_lut(&gin594, or2);

    std::cerr << "\rLUT595   ";
    Ciphertext gin595 = 2 * gout594 + gout293;
    Ciphertext gout595 = ctx.eval_lut(&gin595, xnor2);

    std::cerr << "\rLUT596   ";
    Ciphertext gin596 = 2 * gout595 + gout321;
    Ciphertext gout596 = ctx.eval_lut(&gin596, xnor2);

    std::cerr << "\rLUT597   ";
    Ciphertext gin597 = 2 * gout591 + gout596;
    Ciphertext gout597 = ctx.eval_lut(&gin597, xnor2);

    std::cerr << "\rLUT598   ";
    Ciphertext gin598 = 2 * gout591 + gout596;
    Ciphertext gout598 = ctx.eval_lut(&gin598, and2);

    std::cerr << "\rLUT599   ";
    Ciphertext gin599 = 2 * (1 - gout595) + gout321;
    Ciphertext gout599 = ctx.eval_lut(&gin599, and2);

    std::cerr << "\rLUT600   ";
    Ciphertext gin600 = 2 * gout594 + gout293;
    Ciphertext gout600 = ctx.eval_lut(&gin600, and2);

    std::cerr << "\rLUT601   ";
    Ciphertext gin601 = 2 * gout600 + gout599;
    Ciphertext gout601 = ctx.eval_lut(&gin601, or2);

    std::cerr << "\rLUT602   ";
    Ciphertext gin602 = 2 * ct_y11 + gout353;
    Ciphertext gout602 = ctx.eval_lut(&gin602, xnor2);

    std::cerr << "\rLUT603   ";
    Ciphertext gin603 = 2 * ct_x11 + gout602;
    Ciphertext gout603 = ctx.eval_lut(&gin603, xnor2);

    std::cerr << "\rINV604   ";
    Ciphertext gout604 = 1 - gout603;

    std::cerr << "\rLUT605   ";
    Ciphertext gin605 = 2 * gout212 + gout602;
    Ciphertext gout605 = ctx.eval_lut(&gin605, nand2);

    std::cerr << "\rLUT606   ";
    Ciphertext gin606 = 2 * gout212 + gout602;
    Ciphertext gout606 = ctx.eval_lut(&gin606, or2);

    std::cerr << "\rLUT607   ";
    Ciphertext gin607 = 2 * gout375 + gout606;
    Ciphertext gout607 = ctx.eval_lut(&gin607, nand2);

    std::cerr << "\rLUT608   ";
    Ciphertext gin608 = 2 * gout605 + gout607;
    Ciphertext gout608 = ctx.eval_lut(&gin608, nand2);

    std::cerr << "\rLUT609   ";
    Ciphertext gin609 = 2 * gout420 + gout405;
    Ciphertext gout609 = ctx.eval_lut(&gin609, xnor2);

    std::cerr << "\rINV610   ";
    Ciphertext gout610 = 1 - ct_x7;

    std::cerr << "\rLUT611   ";
    Ciphertext gin611 = 2 * gout610 + gout389;
    Ciphertext gout611 = ctx.eval_lut(&gin611, xnor2);

    std::cerr << "\rLUT612   ";
    Ciphertext gin612 = 2 * gout431 + gout611;
    Ciphertext gout612 = ctx.eval_lut(&gin612, xnor2);

    std::cerr << "\rLUT613   ";
    Ciphertext gin613 = 2 * gout431 + gout611;
    Ciphertext gout613 = ctx.eval_lut(&gin613, nand2);

    std::cerr << "\rLUT614   ";
    Ciphertext gin614 = 2 * gout390 + gout613;
    Ciphertext gout614 = ctx.eval_lut(&gin614, nand2);

    std::cerr << "\rLUT615   ";
    Ciphertext gin615 = 2 * gout614 + gout384;
    Ciphertext gout615 = ctx.eval_lut(&gin615, xnor2);

    std::cerr << "\rLUT616   ";
    Ciphertext gin616 = 2 * gout614 + gout384;
    Ciphertext gout616 = ctx.eval_lut(&gin616, nand2);

    std::cerr << "\rLUT617   ";
    Ciphertext gin617 = 2 * gout616 + gout379;
    Ciphertext gout617 = ctx.eval_lut(&gin617, or2);

    std::cerr << "\rLUT618   ";
    Ciphertext gin618 = 2 * gout617 + gout387;
    Ciphertext gout618 = ctx.eval_lut(&gin618, nand2);

    std::cerr << "\rLUT619   ";
    Ciphertext gin619 = 2 * gout618 + gout374;
    Ciphertext gout619 = ctx.eval_lut(&gin619, xnor2);

    std::cerr << "\rLUT620   ";
    Ciphertext gin620 = 2 * gout618 + gout374;
    Ciphertext gout620 = ctx.eval_lut(&gin620, nand2);

    std::cerr << "\rLUT621   ";
    Ciphertext gin621 = 2 * gout620 + gout604;
    Ciphertext gout621 = ctx.eval_lut(&gin621, or2);

    std::cerr << "\rLUT622   ";
    Ciphertext gin622 = 2 * gout621 + gout608;
    Ciphertext gout622 = ctx.eval_lut(&gin622, nand2);

    std::cerr << "\rLUT623   ";
    Ciphertext gin623 = 2 * gout622 + gout368;
    Ciphertext gout623 = ctx.eval_lut(&gin623, xnor2);

    std::cerr << "\rLUT624   ";
    Ciphertext gin624 = 2 * gout622 + gout368;
    Ciphertext gout624 = ctx.eval_lut(&gin624, nand2);

    std::cerr << "\rLUT625   ";
    Ciphertext gin625 = 2 * gout624 + gout364;
    Ciphertext gout625 = ctx.eval_lut(&gin625, or2);

    std::cerr << "\rLUT626   ";
    Ciphertext gin626 = 2 * gout625 + gout371;
    Ciphertext gout626 = ctx.eval_lut(&gin626, nand2);

    std::cerr << "\rLUT627   ";
    Ciphertext gin627 = 2 * gout626 + gout360;
    Ciphertext gout627 = ctx.eval_lut(&gin627, xnor2);

    std::cerr << "\rLUT628   ";
    Ciphertext gin628 = 2 * gout626 + gout360;
    Ciphertext gout628 = ctx.eval_lut(&gin628, nand2);

    std::cerr << "\rLUT629   ";
    Ciphertext gin629 = 2 * gout361 + gout628;
    Ciphertext gout629 = ctx.eval_lut(&gin629, and2);

    std::cerr << "\rLUT630   ";
    Ciphertext gin630 = 2 * gout629 + gout358;
    Ciphertext gout630 = ctx.eval_lut(&gin630, or2);

    std::cerr << "\rLUT631   ";
    Ciphertext gin631 = 2 * gout440 + gout630;
    Ciphertext gout631 = ctx.eval_lut(&gin631, and2);

    std::cerr << "\rLUT632   ";
    Ciphertext gin632 = 2 * gout629 + gout358;
    Ciphertext gout632 = ctx.eval_lut(&gin632, nand2);

    std::cerr << "\rLUT633   ";
    Ciphertext gin633 = 2 * gout632 + gout631;
    Ciphertext gout633 = ctx.eval_lut(&gin633, nand2);

    std::cerr << "\rLUT634   ";
    Ciphertext gin634 = 2 * gout433 + gout633;
    Ciphertext gout634 = ctx.eval_lut(&gin634, and2);

    std::cerr << "\rLUT635   ";
    Ciphertext gin635 = 2 * gout369 + gout624;
    Ciphertext gout635 = ctx.eval_lut(&gin635, nand2);

    std::cerr << "\rLUT636   ";
    Ciphertext gin636 = 2 * gout635 + gout363;
    Ciphertext gout636 = ctx.eval_lut(&gin636, or2);

    std::cerr << "\rLUT637   ";
    Ciphertext gin637 = 2 * gout440 + gout636;
    Ciphertext gout637 = ctx.eval_lut(&gin637, and2);

    std::cerr << "\rLUT638   ";
    Ciphertext gin638 = 2 * gout635 + gout363;
    Ciphertext gout638 = ctx.eval_lut(&gin638, nand2);

    std::cerr << "\rLUT639   ";
    Ciphertext gin639 = 2 * gout638 + gout637;
    Ciphertext gout639 = ctx.eval_lut(&gin639, nand2);

    std::cerr << "\rLUT640   ";
    Ciphertext gin640 = 2 * gout375 + gout620;
    Ciphertext gout640 = ctx.eval_lut(&gin640, nand2);

    std::cerr << "\rLUT641   ";
    Ciphertext gin641 = 2 * gout640 + gout603;
    Ciphertext gout641 = ctx.eval_lut(&gin641, or2);

    std::cerr << "\rLUT642   ";
    Ciphertext gin642 = 2 * gout440 + gout641;
    Ciphertext gout642 = ctx.eval_lut(&gin642, and2);

    std::cerr << "\rLUT643   ";
    Ciphertext gin643 = 2 * gout640 + gout603;
    Ciphertext gout643 = ctx.eval_lut(&gin643, nand2);

    std::cerr << "\rLUT644   ";
    Ciphertext gin644 = 2 * gout643 + gout642;
    Ciphertext gout644 = ctx.eval_lut(&gin644, nand2);

    std::cerr << "\rLUT645   ";
    Ciphertext gin645 = 2 * gout385 + gout616;
    Ciphertext gout645 = ctx.eval_lut(&gin645, nand2);

    std::cerr << "\rLUT646   ";
    Ciphertext gin646 = 2 * gout645 + gout378;
    Ciphertext gout646 = ctx.eval_lut(&gin646, or2);

    std::cerr << "\rLUT647   ";
    Ciphertext gin647 = 2 * gout440 + gout646;
    Ciphertext gout647 = ctx.eval_lut(&gin647, and2);

    std::cerr << "\rLUT648   ";
    Ciphertext gin648 = 2 * gout645 + gout378;
    Ciphertext gout648 = ctx.eval_lut(&gin648, nand2);

    std::cerr << "\rLUT649   ";
    Ciphertext gin649 = 2 * gout648 + gout647;
    Ciphertext gout649 = ctx.eval_lut(&gin649, nand2);

    std::cerr << "\rLUT650   ";
    Ciphertext gin650 = 2 * gout342 + gout341;
    Ciphertext gout650 = ctx.eval_lut(&gin650, nand2);

    std::cerr << "\rLUT651   ";
    Ciphertext gin651 = 2 * gout650 + gout472;
    Ciphertext gout651 = ctx.eval_lut(&gin651, xnor2);

    std::cerr << "\rLUT652   ";
    Ciphertext gin652 = 2 * gout651 + gout446;
    Ciphertext gout652 = ctx.eval_lut(&gin652, xnor2);

    std::cerr << "\rLUT653   ";
    Ciphertext gin653 = 2 * gout451 + gout652;
    Ciphertext gout653 = ctx.eval_lut(&gin653, xor2);

    std::cerr << "\rLUT654   ";
    Ciphertext gin654 = 2 * gout528 + gout653;
    Ciphertext gout654 = ctx.eval_lut(&gin654, xor2);

    std::cerr << "\rLUT655   ";
    Ciphertext gin655 = 2 * gout587 + gout654;
    Ciphertext gout655 = ctx.eval_lut(&gin655, xnor2);

    std::cerr << "\rLUT656   ";
    Ciphertext gin656 = 2 * (1 - gout587) + gout654;
    Ciphertext gout656 = ctx.eval_lut(&gin656, and2);

    std::cerr << "\rLUT657   ";
    Ciphertext gin657 = 2 * gout588 + gout656;
    Ciphertext gout657 = ctx.eval_lut(&gin657, or2);

    std::cerr << "\rLUT658   ";
    Ciphertext gin658 = 2 * gout528 + gout653;
    Ciphertext gout658 = ctx.eval_lut(&gin658, nand2);

    std::cerr << "\rLUT659   ";
    Ciphertext gin659 = 2 * gout451 + gout652;
    Ciphertext gout659 = ctx.eval_lut(&gin659, nand2);

    std::cerr << "\rLUT660   ";
    Ciphertext gin660 = 2 * gout659 + gout658;
    Ciphertext gout660 = ctx.eval_lut(&gin660, nand2);

    std::cerr << "\rLUT661   ";
    Ciphertext gin661 = 2 * gout127 + gout660;
    Ciphertext gout661 = ctx.eval_lut(&gin661, xor2);

    std::cerr << "\rLUT662   ";
    Ciphertext gin662 = 2 * gout127 + gout660;
    Ciphertext gout662 = ctx.eval_lut(&gin662, and2);

    std::cerr << "\rLUT663   ";
    Ciphertext gin663 = 2 * (1 - gout651) + gout446;
    Ciphertext gout663 = ctx.eval_lut(&gin663, and2);

    std::cerr << "\rLUT664   ";
    Ciphertext gin664 = 2 * gout650 + gout472;
    Ciphertext gout664 = ctx.eval_lut(&gin664, and2);

    std::cerr << "\rLUT665   ";
    Ciphertext gin665 = 2 * gout664 + gout663;
    Ciphertext gout665 = ctx.eval_lut(&gin665, or2);

    std::cerr << "\rLUT666   ";
    Ciphertext gin666 = 2 * gout665 + gout539;
    Ciphertext gout666 = ctx.eval_lut(&gin666, xor2);

    std::cerr << "\rLUT667   ";
    Ciphertext gin667 = 2 * gout597 + gout666;
    Ciphertext gout667 = ctx.eval_lut(&gin667, xnor2);

    std::cerr << "\rLUT668   ";
    Ciphertext gin668 = 2 * gout657 + gout667;
    Ciphertext gout668 = ctx.eval_lut(&gin668, xnor2);

    std::cerr << "\rLUT669   ";
    Ciphertext gin669 = 2 * gout668 + gout661;
    Ciphertext gout669 = ctx.eval_lut(&gin669, xnor2);

    std::cerr << "\rLUT670   ";
    Ciphertext gin670 = 2 * (1 - gout668) + gout661;
    Ciphertext gout670 = ctx.eval_lut(&gin670, and2);

    std::cerr << "\rLUT671   ";
    Ciphertext gin671 = 2 * gout657 + gout667;
    Ciphertext gout671 = ctx.eval_lut(&gin671, nand2);

    std::cerr << "\rLUT672   ";
    Ciphertext gin672 = 2 * gout671 + (1 - gout670);
    Ciphertext gout672 = ctx.eval_lut(&gin672, and2);

    std::cerr << "\rLUT673   ";
    Ciphertext gin673 = 2 * (1 - gout597) + gout666;
    Ciphertext gout673 = ctx.eval_lut(&gin673, and2);

    std::cerr << "\rLUT674   ";
    Ciphertext gin674 = 2 * gout598 + gout673;
    Ciphertext gout674 = ctx.eval_lut(&gin674, or2);

    std::cerr << "\rLUT675   ";
    Ciphertext gin675 = 2 * gout665 + gout539;
    Ciphertext gout675 = ctx.eval_lut(&gin675, nand2);

    std::cerr << "\rLUT676   ";
    Ciphertext gin676 = 2 * gout540 + gout675;
    Ciphertext gout676 = ctx.eval_lut(&gin676, nand2);

    std::cerr << "\rLUT677   ";
    Ciphertext gin677 = 2 * gout676 + gout445;
    Ciphertext gout677 = ctx.eval_lut(&gin677, xnor2);

    std::cerr << "\rLUT678   ";
    Ciphertext gin678 = 2 * gout7 + gout148;
    Ciphertext gout678 = ctx.eval_lut(&gin678, xor2);

    std::cerr << "\rLUT679   ";
    Ciphertext gin679 = 2 * gout280 + gout678;
    Ciphertext gout679 = ctx.eval_lut(&gin679, xor2);

    std::cerr << "\rLUT680   ";
    Ciphertext gin680 = 2 * gout232 + gout679;
    Ciphertext gout680 = ctx.eval_lut(&gin680, xor2);

    std::cerr << "\rLUT681   ";
    Ciphertext gin681 = 2 * gout554 + gout680;
    Ciphertext gout681 = ctx.eval_lut(&gin681, xnor2);

    std::cerr << "\rLUT682   ";
    Ciphertext gin682 = 2 * (1 - gout554) + gout680;
    Ciphertext gout682 = ctx.eval_lut(&gin682, and2);

    std::cerr << "\rLUT683   ";
    Ciphertext gin683 = 2 * gout555 + gout682;
    Ciphertext gout683 = ctx.eval_lut(&gin683, or2);

    std::cerr << "\rLUT684   ";
    Ciphertext gin684 = 2 * gout683 + gout560;
    Ciphertext gout684 = ctx.eval_lut(&gin684, xnor2);

    std::cerr << "\rLUT685   ";
    Ciphertext gin685 = 2 * gout683 + gout560;
    Ciphertext gout685 = ctx.eval_lut(&gin685, and2);

    std::cerr << "\rLUT686   ";
    Ciphertext gin686 = 2 * gout232 + gout679;
    Ciphertext gout686 = ctx.eval_lut(&gin686, nand2);

    std::cerr << "\rLUT687   ";
    Ciphertext gin687 = 2 * gout280 + gout678;
    Ciphertext gout687 = ctx.eval_lut(&gin687, nand2);

    std::cerr << "\rLUT688   ";
    Ciphertext gin688 = 2 * gout687 + gout686;
    Ciphertext gout688 = ctx.eval_lut(&gin688, nand2);

    std::cerr << "\rLUT689   ";
    Ciphertext gin689 = 2 * gout688 + gout104;
    Ciphertext gout689 = ctx.eval_lut(&gin689, xor2);

    std::cerr << "\rLUT690   ";
    Ciphertext gin690 = 2 * gout684 + gout689;
    Ciphertext gout690 = ctx.eval_lut(&gin690, xnor2);

    std::cerr << "\rLUT691   ";
    Ciphertext gin691 = 2 * (1 - gout684) + gout689;
    Ciphertext gout691 = ctx.eval_lut(&gin691, and2);

    std::cerr << "\rLUT692   ";
    Ciphertext gin692 = 2 * gout685 + gout691;
    Ciphertext gout692 = ctx.eval_lut(&gin692, or2);

    std::cerr << "\rLUT693   ";
    Ciphertext gin693 = 2 * gout688 + gout104;
    Ciphertext gout693 = ctx.eval_lut(&gin693, and2);

    std::cerr << "\rLUT694   ";
    Ciphertext gin694 = 2 * gout43 + gout313;
    Ciphertext gout694 = ctx.eval_lut(&gin694, nand2);

    std::cerr << "\rLUT695   ";
    Ciphertext gin695 = 2 * gout271 + gout694;
    Ciphertext gout695 = ctx.eval_lut(&gin695, nand2);

    std::cerr << "\rLUT696   ";
    Ciphertext gin696 = 2 * gout695 + gout235;
    Ciphertext gout696 = ctx.eval_lut(&gin696, xnor2);

    std::cerr << "\rLUT697   ";
    Ciphertext gin697 = 2 * gout696 + gout260;
    Ciphertext gout697 = ctx.eval_lut(&gin697, xnor2);

    std::cerr << "\rLUT698   ";
    Ciphertext gin698 = 2 * gout502 + gout697;
    Ciphertext gout698 = ctx.eval_lut(&gin698, xor2);

    std::cerr << "\rLUT699   ";
    Ciphertext gin699 = 2 * gout210 + gout698;
    Ciphertext gout699 = ctx.eval_lut(&gin699, xnor2);

    std::cerr << "\rLUT700   ";
    Ciphertext gin700 = 2 * gout499 + gout699;
    Ciphertext gout700 = ctx.eval_lut(&gin700, and2);

    std::cerr << "\rINV701   ";
    Ciphertext gout701 = 1 - gout700;

    std::cerr << "\rLUT702   ";
    Ciphertext gin702 = 2 * gout209 + gout698;
    Ciphertext gout702 = ctx.eval_lut(&gin702, nand2);

    std::cerr << "\rLUT703   ";
    Ciphertext gin703 = 2 * gout502 + gout697;
    Ciphertext gout703 = ctx.eval_lut(&gin703, nand2);

    std::cerr << "\rLUT704   ";
    Ciphertext gin704 = 2 * gout703 + gout702;
    Ciphertext gout704 = ctx.eval_lut(&gin704, nand2);

    std::cerr << "\rLUT705   ";
    Ciphertext gin705 = 2 * (1 - gout696) + gout260;
    Ciphertext gout705 = ctx.eval_lut(&gin705, and2);

    std::cerr << "\rLUT706   ";
    Ciphertext gin706 = 2 * gout695 + gout235;
    Ciphertext gout706 = ctx.eval_lut(&gin706, and2);

    std::cerr << "\rLUT707   ";
    Ciphertext gin707 = 2 * gout706 + gout705;
    Ciphertext gout707 = ctx.eval_lut(&gin707, or2);

    std::cerr << "\rLUT708   ";
    Ciphertext gin708 = 2 * gout707 + gout518;
    Ciphertext gout708 = ctx.eval_lut(&gin708, xnor2);

    std::cerr << "\rLUT709   ";
    Ciphertext gin709 = 2 * gout708 + gout316;
    Ciphertext gout709 = ctx.eval_lut(&gin709, xnor2);

    std::cerr << "\rLUT710   ";
    Ciphertext gin710 = 2 * gout704 + gout709;
    Ciphertext gout710 = ctx.eval_lut(&gin710, and2);

    std::cerr << "\rINV711   ";
    Ciphertext gout711 = 1 - gout710;

    std::cerr << "\rINV712   ";
    Ciphertext gout712 = 1 - gout709;

    std::cerr << "\rLUT713   ";
    Ciphertext gin713 = 2 * gout704 + gout712;
    Ciphertext gout713 = ctx.eval_lut(&gin713, xnor2);

    std::cerr << "\rLUT714   ";
    Ciphertext gin714 = 2 * gout701 + gout713;
    Ciphertext gout714 = ctx.eval_lut(&gin714, xnor2);

    std::cerr << "\rLUT715   ";
    Ciphertext gin715 = 2 * gout700 + gout713;
    Ciphertext gout715 = ctx.eval_lut(&gin715, and2);

    std::cerr << "\rINV716   ";
    Ciphertext gout716 = 1 - gout715;

    std::cerr << "\rLUT717   ";
    Ciphertext gin717 = 2 * (1 - gout708) + gout316;
    Ciphertext gout717 = ctx.eval_lut(&gin717, and2);

    std::cerr << "\rLUT718   ";
    Ciphertext gin718 = 2 * gout707 + gout518;
    Ciphertext gout718 = ctx.eval_lut(&gin718, and2);

    std::cerr << "\rLUT719   ";
    Ciphertext gin719 = 2 * gout718 + gout717;
    Ciphertext gout719 = ctx.eval_lut(&gin719, or2);

    std::cerr << "\rLUT720   ";
    Ciphertext gin720 = 2 * gout61 + gout303;
    Ciphertext gout720 = ctx.eval_lut(&gin720, and2);

    std::cerr << "\rLUT721   ";
    Ciphertext gin721 = 2 * gout720 + gout468;
    Ciphertext gout721 = ctx.eval_lut(&gin721, and2);

    std::cerr << "\rLUT722   ";
    Ciphertext gin722 = 2 * gout721 + gout498;
    Ciphertext gout722 = ctx.eval_lut(&gin722, and2);

    std::cerr << "\rLUT723   ";
    Ciphertext gin723 = 2 * gout722 + gout699;
    Ciphertext gout723 = ctx.eval_lut(&gin723, and2);

    std::cerr << "\rLUT724   ";
    Ciphertext gin724 = 2 * gout723 + gout714;
    Ciphertext gout724 = ctx.eval_lut(&gin724, nand2);

    std::cerr << "\rINV725   ";
    Ciphertext gout725 = 1 - gout723;

    std::cerr << "\rLUT726   ";
    Ciphertext gin726 = 2 * gout725 + gout714;
    Ciphertext gout726 = ctx.eval_lut(&gin726, xnor2);

    std::cerr << "\rLUT727   ";
    Ciphertext gin727 = 2 * gout499 + gout722;
    Ciphertext gout727 = ctx.eval_lut(&gin727, or2);

    std::cerr << "\rLUT728   ";
    Ciphertext gin728 = 2 * gout699 + gout727;
    Ciphertext gout728 = ctx.eval_lut(&gin728, xor2);

    std::cerr << "\rINV729   ";
    Ciphertext gout729 = 1 - gout721;

    std::cerr << "\rINV730   ";
    Ciphertext gout730 = 1 - gout720;

    std::cerr << "\rLUT731   ";
    Ciphertext gin731 = 2 * gout730 + gout468;
    Ciphertext gout731 = ctx.eval_lut(&gin731, xnor2);

    std::cerr << "\rLUT732   ";
    Ciphertext gin732 = 2 * gout306 + gout731;
    Ciphertext gout732 = ctx.eval_lut(&gin732, xnor2);

    std::cerr << "\rIMUX733  ";
    Ciphertext gin733A = 2 * gout732 + gout434;
    Ciphertext gout733A = ctx.eval_lut(&gin733A, and2);
    Ciphertext gin733B = 2 * gout609 + (1 - gout434);
    Ciphertext gout733B = ctx.eval_lut(&gin733B, and2);
    Ciphertext gout733 = gout733A + gout733B;

    std::cerr << "\rLUT734   ";
    Ciphertext gin734 = 2 * gout433 + gout733;
    Ciphertext gout734 = ctx.eval_lut(&gin734, nand2);

    std::cerr << "\rLUT735   ";
    Ciphertext gin735 = 2 * gout306 + gout731;
    Ciphertext gout735 = ctx.eval_lut(&gin735, nand2);

    std::cerr << "\rLUT736   ";
    Ciphertext gin736 = 2 * (1 - gout735) + gout498;
    Ciphertext gout736 = ctx.eval_lut(&gin736, and2);

    std::cerr << "\rLUT737   ";
    Ciphertext gin737 = 2 * gout736 + gout728;
    Ciphertext gout737 = ctx.eval_lut(&gin737, xnor2);

    std::cerr << "\rIMUX738  ";
    Ciphertext gin738A = 2 * gout737 + gout434;
    Ciphertext gout738A = ctx.eval_lut(&gin738A, and2);
    Ciphertext gin738B = 2 * gout426 + (1 - gout434);
    Ciphertext gout738B = ctx.eval_lut(&gin738B, and2);
    Ciphertext gout738 = gout738A + gout738B;

    std::cerr << "\rLUT739   ";
    Ciphertext gin739 = 2 * gout433 + gout738;
    Ciphertext gout739 = ctx.eval_lut(&gin739, nand2);

    std::cerr << "\rLUT740   ";
    Ciphertext gin740 = 2 * gout729 + gout735;
    Ciphertext gout740 = ctx.eval_lut(&gin740, nand2);

    std::cerr << "\rLUT741   ";
    Ciphertext gin741 = 2 * gout498 + gout740;
    Ciphertext gout741 = ctx.eval_lut(&gin741, xnor2);

    std::cerr << "\rIMUX742  ";
    Ciphertext gin742A = 2 * gout423 + gout440;
    Ciphertext gout742A = ctx.eval_lut(&gin742A, and2);
    Ciphertext gin742B = 2 * gout741 + (1 - gout440);
    Ciphertext gout742B = ctx.eval_lut(&gin742B, and2);
    Ciphertext gout742 = gout742A + gout742B;

    std::cerr << "\rLUT743   ";
    Ciphertext gin743 = 2 * gout433 + gout742;
    Ciphertext gout743 = ctx.eval_lut(&gin743, nand2);

    std::cerr << "\rLUT744   ";
    Ciphertext gin744 = 2 * gout76 + gout264;
    Ciphertext gout744 = ctx.eval_lut(&gin744, xnor2);

    std::cerr << "\rLUT745   ";
    Ciphertext gin745 = 2 * gout470 + gout744;
    Ciphertext gout745 = ctx.eval_lut(&gin745, xnor2);

    std::cerr << "\rLUT746   ";
    Ciphertext gin746 = 2 * gout745 + gout299;
    Ciphertext gout746 = ctx.eval_lut(&gin746, xnor2);

    std::cerr << "\rLUT747   ";
    Ciphertext gin747 = 2 * gout329 + gout746;
    Ciphertext gout747 = ctx.eval_lut(&gin747, xnor2);

    std::cerr << "\rLUT748   ";
    Ciphertext gin748 = 2 * gout568 + gout747;
    Ciphertext gout748 = ctx.eval_lut(&gin748, xnor2);

    std::cerr << "\rLUT749   ";
    Ciphertext gin749 = 2 * gout601 + gout748;
    Ciphertext gout749 = ctx.eval_lut(&gin749, xnor2);

    std::cerr << "\rLUT750   ";
    Ciphertext gin750 = 2 * gout677 + gout749;
    Ciphertext gout750 = ctx.eval_lut(&gin750, xnor2);

    std::cerr << "\rLUT751   ";
    Ciphertext gin751 = 2 * gout674 + gout750;
    Ciphertext gout751 = ctx.eval_lut(&gin751, xnor2);

    std::cerr << "\rLUT752   ";
    Ciphertext gin752 = 2 * gout672 + gout751;
    Ciphertext gout752 = ctx.eval_lut(&gin752, xnor2);

    std::cerr << "\rLUT753   ";
    Ciphertext gin753 = 2 * gout117 + gout230;
    Ciphertext gout753 = ctx.eval_lut(&gin753, xor2);

    std::cerr << "\rLUT754   ";
    Ciphertext gin754 = 2 * gout203 + gout753;
    Ciphertext gout754 = ctx.eval_lut(&gin754, xor2);

    std::cerr << "\rLUT755   ";
    Ciphertext gin755 = 2 * gout175 + gout754;
    Ciphertext gout755 = ctx.eval_lut(&gin755, xor2);

    std::cerr << "\rLUT756   ";
    Ciphertext gin756 = 2 * gout493 + gout755;
    Ciphertext gout756 = ctx.eval_lut(&gin756, xnor2);

    std::cerr << "\rLUT757   ";
    Ciphertext gin757 = 2 * gout563 + gout756;
    Ciphertext gout757 = ctx.eval_lut(&gin757, xnor2);

    std::cerr << "\rLUT758   ";
    Ciphertext gin758 = 2 * gout757 + gout512;
    Ciphertext gout758 = ctx.eval_lut(&gin758, xnor2);

    std::cerr << "\rLUT759   ";
    Ciphertext gin759 = 2 * gout692 + gout758;
    Ciphertext gout759 = ctx.eval_lut(&gin759, xor2);

    std::cerr << "\rLUT760   ";
    Ciphertext gin760 = 2 * gout693 + gout759;
    Ciphertext gout760 = ctx.eval_lut(&gin760, xor2);

    std::cerr << "\rLUT761   ";
    Ciphertext gin761 = 2 * gout693 + gout759;
    Ciphertext gout761 = ctx.eval_lut(&gin761, nand2);

    std::cerr << "\rLUT762   ";
    Ciphertext gin762 = 2 * gout692 + gout758;
    Ciphertext gout762 = ctx.eval_lut(&gin762, nand2);

    std::cerr << "\rLUT763   ";
    Ciphertext gin763 = 2 * gout762 + gout761;
    Ciphertext gout763 = ctx.eval_lut(&gin763, nand2);

    std::cerr << "\rLUT764   ";
    Ciphertext gin764 = 2 * (1 - gout757) + gout512;
    Ciphertext gout764 = ctx.eval_lut(&gin764, and2);

    std::cerr << "\rLUT765   ";
    Ciphertext gin765 = 2 * gout563 + gout756;
    Ciphertext gout765 = ctx.eval_lut(&gin765, and2);

    std::cerr << "\rLUT766   ";
    Ciphertext gin766 = 2 * gout765 + gout764;
    Ciphertext gout766 = ctx.eval_lut(&gin766, or2);

    std::cerr << "\rLUT767   ";
    Ciphertext gin767 = 2 * (1 - gout493) + gout755;
    Ciphertext gout767 = ctx.eval_lut(&gin767, and2);

    std::cerr << "\rLUT768   ";
    Ciphertext gin768 = 2 * gout494 + gout767;
    Ciphertext gout768 = ctx.eval_lut(&gin768, or2);

    std::cerr << "\rLUT769   ";
    Ciphertext gin769 = 2 * gout768 + gout574;
    Ciphertext gout769 = ctx.eval_lut(&gin769, xnor2);

    std::cerr << "\rLUT770   ";
    Ciphertext gin770 = 2 * gout768 + gout574;
    Ciphertext gout770 = ctx.eval_lut(&gin770, and2);

    std::cerr << "\rLUT771   ";
    Ciphertext gin771 = 2 * gout175 + gout754;
    Ciphertext gout771 = ctx.eval_lut(&gin771, nand2);

    std::cerr << "\rLUT772   ";
    Ciphertext gin772 = 2 * gout203 + gout753;
    Ciphertext gout772 = ctx.eval_lut(&gin772, nand2);

    std::cerr << "\rLUT773   ";
    Ciphertext gin773 = 2 * gout772 + gout771;
    Ciphertext gout773 = ctx.eval_lut(&gin773, nand2);

    std::cerr << "\rLUT774   ";
    Ciphertext gin774 = 2 * gout773 + gout339;
    Ciphertext gout774 = ctx.eval_lut(&gin774, xor2);

    std::cerr << "\rLUT775   ";
    Ciphertext gin775 = 2 * gout453 + gout774;
    Ciphertext gout775 = ctx.eval_lut(&gin775, xor2);

    std::cerr << "\rLUT776   ";
    Ciphertext gin776 = 2 * gout769 + gout775;
    Ciphertext gout776 = ctx.eval_lut(&gin776, xnor2);

    std::cerr << "\rLUT777   ";
    Ciphertext gin777 = 2 * gout766 + gout776;
    Ciphertext gout777 = ctx.eval_lut(&gin777, xor2);

    std::cerr << "\rLUT778   ";
    Ciphertext gin778 = 2 * gout513 + gout777;
    Ciphertext gout778 = ctx.eval_lut(&gin778, xor2);

    std::cerr << "\rLUT779   ";
    Ciphertext gin779 = 2 * gout763 + gout778;
    Ciphertext gout779 = ctx.eval_lut(&gin779, xor2);

    std::cerr << "\rLUT780   ";
    Ciphertext gin780 = 2 * gout763 + gout778;
    Ciphertext gout780 = ctx.eval_lut(&gin780, and2);

    std::cerr << "\rLUT781   ";
    Ciphertext gin781 = 2 * gout513 + gout777;
    Ciphertext gout781 = ctx.eval_lut(&gin781, nand2);

    std::cerr << "\rLUT782   ";
    Ciphertext gin782 = 2 * gout766 + gout776;
    Ciphertext gout782 = ctx.eval_lut(&gin782, nand2);

    std::cerr << "\rLUT783   ";
    Ciphertext gin783 = 2 * gout782 + gout781;
    Ciphertext gout783 = ctx.eval_lut(&gin783, nand2);

    std::cerr << "\rLUT784   ";
    Ciphertext gin784 = 2 * (1 - gout769) + gout775;
    Ciphertext gout784 = ctx.eval_lut(&gin784, and2);

    std::cerr << "\rLUT785   ";
    Ciphertext gin785 = 2 * gout770 + gout784;
    Ciphertext gout785 = ctx.eval_lut(&gin785, or2);

    std::cerr << "\rLUT786   ";
    Ciphertext gin786 = 2 * gout785 + gout655;
    Ciphertext gout786 = ctx.eval_lut(&gin786, xor2);

    std::cerr << "\rLUT787   ";
    Ciphertext gin787 = 2 * gout785 + gout655;
    Ciphertext gout787 = ctx.eval_lut(&gin787, nand2);

    std::cerr << "\rLUT788   ";
    Ciphertext gin788 = 2 * gout453 + gout774;
    Ciphertext gout788 = ctx.eval_lut(&gin788, nand2);

    std::cerr << "\rLUT789   ";
    Ciphertext gin789 = 2 * gout773 + gout339;
    Ciphertext gout789 = ctx.eval_lut(&gin789, nand2);

    std::cerr << "\rLUT790   ";
    Ciphertext gin790 = 2 * gout789 + gout788;
    Ciphertext gout790 = ctx.eval_lut(&gin790, nand2);

    std::cerr << "\rLUT791   ";
    Ciphertext gin791 = 2 * gout790 + gout786;
    Ciphertext gout791 = ctx.eval_lut(&gin791, xor2);

    std::cerr << "\rLUT792   ";
    Ciphertext gin792 = 2 * gout783 + gout791;
    Ciphertext gout792 = ctx.eval_lut(&gin792, xor2);

    std::cerr << "\rLUT793   ";
    Ciphertext gin793 = 2 * gout780 + gout792;
    Ciphertext gout793 = ctx.eval_lut(&gin793, xor2);

    std::cerr << "\rLUT794   ";
    Ciphertext gin794 = 2 * gout780 + gout792;
    Ciphertext gout794 = ctx.eval_lut(&gin794, nand2);

    std::cerr << "\rLUT795   ";
    Ciphertext gin795 = 2 * gout783 + gout791;
    Ciphertext gout795 = ctx.eval_lut(&gin795, and2);

    std::cerr << "\rLUT796   ";
    Ciphertext gin796 = 2 * gout790 + gout786;
    Ciphertext gout796 = ctx.eval_lut(&gin796, nand2);

    std::cerr << "\rLUT797   ";
    Ciphertext gin797 = 2 * gout787 + gout796;
    Ciphertext gout797 = ctx.eval_lut(&gin797, nand2);

    std::cerr << "\rLUT798   ";
    Ciphertext gin798 = 2 * gout797 + gout669;
    Ciphertext gout798 = ctx.eval_lut(&gin798, xor2);

    std::cerr << "\rLUT799   ";
    Ciphertext gin799 = 2 * gout795 + gout798;
    Ciphertext gout799 = ctx.eval_lut(&gin799, xor2);

    std::cerr << "\rLUT800   ";
    Ciphertext gin800 = 2 * gout795 + gout798;
    Ciphertext gout800 = ctx.eval_lut(&gin800, nand2);

    std::cerr << "\rLUT801   ";
    Ciphertext gin801 = 2 * gout797 + gout669;
    Ciphertext gout801 = ctx.eval_lut(&gin801, and2);

    std::cerr << "\rLUT802   ";
    Ciphertext gin802 = 2 * gout662 + gout801;
    Ciphertext gout802 = ctx.eval_lut(&gin802, xnor2);

    std::cerr << "\rLUT803   ";
    Ciphertext gin803 = 2 * gout752 + gout802;
    Ciphertext gout803 = ctx.eval_lut(&gin803, xnor2);

    std::cerr << "\rLUT804   ";
    Ciphertext gin804 = 2 * ct_y4 + ct_x3;
    Ciphertext gout804 = ctx.eval_lut(&gin804, and2);

    std::cerr << "\rLUT805   ";
    Ciphertext gin805 = 2 * gout81 + gout804;
    Ciphertext gout805 = ctx.eval_lut(&gin805, xnor2);

    std::cerr << "\rLUT806   ";
    Ciphertext gin806 = 2 * gout32 + gout805;
    Ciphertext gout806 = ctx.eval_lut(&gin806, xor2);

    std::cerr << "\rLUT807   ";
    Ciphertext gin807 = 2 * gout525 + gout806;
    Ciphertext gout807 = ctx.eval_lut(&gin807, xnor2);

    std::cerr << "\rLUT808   ";
    Ciphertext gin808 = 2 * gout521 + gout807;
    Ciphertext gout808 = ctx.eval_lut(&gin808, xnor2);

    std::cerr << "\rLUT809   ";
    Ciphertext gin809 = 2 * gout808 + gout461;
    Ciphertext gout809 = ctx.eval_lut(&gin809, xnor2);

    std::cerr << "\rLUT810   ";
    Ciphertext gin810 = 2 * gout719 + gout809;
    Ciphertext gout810 = ctx.eval_lut(&gin810, xor2);

    std::cerr << "\rLUT811   ";
    Ciphertext gin811 = 2 * gout314 + gout810;
    Ciphertext gout811 = ctx.eval_lut(&gin811, xor2);

    std::cerr << "\rLUT812   ";
    Ciphertext gin812 = 2 * gout711 + gout811;
    Ciphertext gout812 = ctx.eval_lut(&gin812, xnor2);

    std::cerr << "\rLUT813   ";
    Ciphertext gin813 = 2 * gout716 + gout812;
    Ciphertext gout813 = ctx.eval_lut(&gin813, xnor2);

    std::cerr << "\rLUT814   ";
    Ciphertext gin814 = 2 * gout715 + gout812;
    Ciphertext gout814 = ctx.eval_lut(&gin814, nand2);

    std::cerr << "\rLUT815   ";
    Ciphertext gin815 = 2 * gout710 + gout811;
    Ciphertext gout815 = ctx.eval_lut(&gin815, and2);

    std::cerr << "\rINV816   ";
    Ciphertext gout816 = 1 - gout815;

    std::cerr << "\rLUT817   ";
    Ciphertext gin817 = 2 * gout816 + gout814;
    Ciphertext gout817 = ctx.eval_lut(&gin817, and2);

    std::cerr << "\rLUT818   ";
    Ciphertext gin818 = 2 * gout314 + gout810;
    Ciphertext gout818 = ctx.eval_lut(&gin818, nand2);

    std::cerr << "\rLUT819   ";
    Ciphertext gin819 = 2 * gout719 + gout809;
    Ciphertext gout819 = ctx.eval_lut(&gin819, nand2);

    std::cerr << "\rLUT820   ";
    Ciphertext gin820 = 2 * gout819 + gout818;
    Ciphertext gout820 = ctx.eval_lut(&gin820, nand2);

    std::cerr << "\rLUT821   ";
    Ciphertext gin821 = 2 * (1 - gout808) + gout461;
    Ciphertext gout821 = ctx.eval_lut(&gin821, and2);

    std::cerr << "\rLUT822   ";
    Ciphertext gin822 = 2 * gout521 + gout807;
    Ciphertext gout822 = ctx.eval_lut(&gin822, and2);

    std::cerr << "\rLUT823   ";
    Ciphertext gin823 = 2 * gout822 + gout821;
    Ciphertext gout823 = ctx.eval_lut(&gin823, or2);

    std::cerr << "\rLUT824   ";
    Ciphertext gin824 = 2 * (1 - gout525) + gout806;
    Ciphertext gout824 = ctx.eval_lut(&gin824, and2);

    std::cerr << "\rLUT825   ";
    Ciphertext gin825 = 2 * gout526 + gout824;
    Ciphertext gout825 = ctx.eval_lut(&gin825, or2);

    std::cerr << "\rLUT826   ";
    Ciphertext gin826 = 2 * gout825 + gout545;
    Ciphertext gout826 = ctx.eval_lut(&gin826, xnor2);

    std::cerr << "\rLUT827   ";
    Ciphertext gin827 = 2 * gout825 + gout545;
    Ciphertext gout827 = ctx.eval_lut(&gin827, and2);

    std::cerr << "\rLUT828   ";
    Ciphertext gin828 = 2 * gout32 + gout805;
    Ciphertext gout828 = ctx.eval_lut(&gin828, nand2);

    std::cerr << "\rLUT829   ";
    Ciphertext gin829 = 2 * gout464 + gout828;
    Ciphertext gout829 = ctx.eval_lut(&gin829, nand2);

    std::cerr << "\rLUT830   ";
    Ciphertext gin830 = 2 * gout829 + gout196;
    Ciphertext gout830 = ctx.eval_lut(&gin830, xor2);

    std::cerr << "\rLUT831   ";
    Ciphertext gin831 = 2 * gout124 + gout830;
    Ciphertext gout831 = ctx.eval_lut(&gin831, xor2);

    std::cerr << "\rLUT832   ";
    Ciphertext gin832 = 2 * gout826 + gout831;
    Ciphertext gout832 = ctx.eval_lut(&gin832, xnor2);

    std::cerr << "\rLUT833   ";
    Ciphertext gin833 = 2 * gout823 + gout832;
    Ciphertext gout833 = ctx.eval_lut(&gin833, xor2);

    std::cerr << "\rLUT834   ";
    Ciphertext gin834 = 2 * gout462 + gout833;
    Ciphertext gout834 = ctx.eval_lut(&gin834, xor2);

    std::cerr << "\rLUT835   ";
    Ciphertext gin835 = 2 * gout820 + gout834;
    Ciphertext gout835 = ctx.eval_lut(&gin835, xor2);

    std::cerr << "\rLUT836   ";
    Ciphertext gin836 = 2 * gout815 + gout835;
    Ciphertext gout836 = ctx.eval_lut(&gin836, and2);

    std::cerr << "\rLUT837   ";
    Ciphertext gin837 = 2 * gout814 + (1 - gout835);
    Ciphertext gout837 = ctx.eval_lut(&gin837, or2);

    std::cerr << "\rLUT838   ";
    Ciphertext gin838 = 2 * gout835 + gout817;
    Ciphertext gout838 = ctx.eval_lut(&gin838, xnor2);

    std::cerr << "\rLUT839   ";
    Ciphertext gin839 = 2 * gout820 + gout834;
    Ciphertext gout839 = ctx.eval_lut(&gin839, and2);

    std::cerr << "\rLUT840   ";
    Ciphertext gin840 = 2 * gout462 + gout833;
    Ciphertext gout840 = ctx.eval_lut(&gin840, nand2);

    std::cerr << "\rLUT841   ";
    Ciphertext gin841 = 2 * gout823 + gout832;
    Ciphertext gout841 = ctx.eval_lut(&gin841, nand2);

    std::cerr << "\rLUT842   ";
    Ciphertext gin842 = 2 * gout841 + gout840;
    Ciphertext gout842 = ctx.eval_lut(&gin842, nand2);

    std::cerr << "\rLUT843   ";
    Ciphertext gin843 = 2 * (1 - gout826) + gout831;
    Ciphertext gout843 = ctx.eval_lut(&gin843, and2);

    std::cerr << "\rLUT844   ";
    Ciphertext gin844 = 2 * gout827 + gout843;
    Ciphertext gout844 = ctx.eval_lut(&gin844, or2);

    std::cerr << "\rLUT845   ";
    Ciphertext gin845 = 2 * gout844 + gout681;
    Ciphertext gout845 = ctx.eval_lut(&gin845, xnor2);

    std::cerr << "\rLUT846   ";
    Ciphertext gin846 = 2 * gout844 + gout681;
    Ciphertext gout846 = ctx.eval_lut(&gin846, and2);

    std::cerr << "\rLUT847   ";
    Ciphertext gin847 = 2 * gout124 + gout830;
    Ciphertext gout847 = ctx.eval_lut(&gin847, nand2);

    std::cerr << "\rLUT848   ";
    Ciphertext gin848 = 2 * gout829 + gout196;
    Ciphertext gout848 = ctx.eval_lut(&gin848, nand2);

    std::cerr << "\rLUT849   ";
    Ciphertext gin849 = 2 * gout848 + gout847;
    Ciphertext gout849 = ctx.eval_lut(&gin849, nand2);

    std::cerr << "\rLUT850   ";
    Ciphertext gin850 = 2 * gout849 + gout2;
    Ciphertext gout850 = ctx.eval_lut(&gin850, xor2);

    std::cerr << "\rLUT851   ";
    Ciphertext gin851 = 2 * gout845 + gout850;
    Ciphertext gout851 = ctx.eval_lut(&gin851, xnor2);

    std::cerr << "\rLUT852   ";
    Ciphertext gin852 = 2 * gout842 + gout851;
    Ciphertext gout852 = ctx.eval_lut(&gin852, xor2);

    std::cerr << "\rLUT853   ";
    Ciphertext gin853 = 2 * gout839 + gout852;
    Ciphertext gout853 = ctx.eval_lut(&gin853, xor2);

    std::cerr << "\rLUT854   ";
    Ciphertext gin854 = 2 * gout836 + gout853;
    Ciphertext gout854 = ctx.eval_lut(&gin854, xnor2);

    std::cerr << "\rLUT855   ";
    Ciphertext gin855 = 2 * gout836 + gout853;
    Ciphertext gout855 = ctx.eval_lut(&gin855, nand2);

    std::cerr << "\rLUT856   ";
    Ciphertext gin856 = 2 * gout839 + gout852;
    Ciphertext gout856 = ctx.eval_lut(&gin856, and2);

    std::cerr << "\rLUT857   ";
    Ciphertext gin857 = 2 * gout842 + gout851;
    Ciphertext gout857 = ctx.eval_lut(&gin857, and2);

    std::cerr << "\rINV858   ";
    Ciphertext gout858 = 1 - gout857;

    std::cerr << "\rLUT859   ";
    Ciphertext gin859 = 2 * (1 - gout845) + gout850;
    Ciphertext gout859 = ctx.eval_lut(&gin859, and2);

    std::cerr << "\rLUT860   ";
    Ciphertext gin860 = 2 * gout846 + gout859;
    Ciphertext gout860 = ctx.eval_lut(&gin860, or2);

    std::cerr << "\rLUT861   ";
    Ciphertext gin861 = 2 * gout860 + gout690;
    Ciphertext gout861 = ctx.eval_lut(&gin861, xor2);

    std::cerr << "\rLUT862   ";
    Ciphertext gin862 = 2 * gout860 + gout690;
    Ciphertext gout862 = ctx.eval_lut(&gin862, nand2);

    std::cerr << "\rLUT863   ";
    Ciphertext gin863 = 2 * gout849 + gout2;
    Ciphertext gout863 = ctx.eval_lut(&gin863, and2);

    std::cerr << "\rLUT864   ";
    Ciphertext gin864 = 2 * gout863 + gout861;
    Ciphertext gout864 = ctx.eval_lut(&gin864, xor2);

    std::cerr << "\rLUT865   ";
    Ciphertext gin865 = 2 * gout858 + gout864;
    Ciphertext gout865 = ctx.eval_lut(&gin865, xnor2);

    std::cerr << "\rLUT866   ";
    Ciphertext gin866 = 2 * gout856 + gout865;
    Ciphertext gout866 = ctx.eval_lut(&gin866, xor2);

    std::cerr << "\rLUT867   ";
    Ciphertext gin867 = 2 * gout856 + gout865;
    Ciphertext gout867 = ctx.eval_lut(&gin867, nand2);

    std::cerr << "\rLUT868   ";
    Ciphertext gin868 = 2 * gout857 + gout864;
    Ciphertext gout868 = ctx.eval_lut(&gin868, and2);

    std::cerr << "\rINV869   ";
    Ciphertext gout869 = 1 - gout868;

    std::cerr << "\rLUT870   ";
    Ciphertext gin870 = 2 * gout863 + gout861;
    Ciphertext gout870 = ctx.eval_lut(&gin870, nand2);

    std::cerr << "\rLUT871   ";
    Ciphertext gin871 = 2 * gout862 + gout870;
    Ciphertext gout871 = ctx.eval_lut(&gin871, nand2);

    std::cerr << "\rLUT872   ";
    Ciphertext gin872 = 2 * gout871 + gout760;
    Ciphertext gout872 = ctx.eval_lut(&gin872, xor2);

    std::cerr << "\rLUT873   ";
    Ciphertext gin873 = 2 * gout869 + gout872;
    Ciphertext gout873 = ctx.eval_lut(&gin873, xnor2);

    std::cerr << "\rLUT874   ";
    Ciphertext gin874 = 2 * gout868 + gout872;
    Ciphertext gout874 = ctx.eval_lut(&gin874, nand2);

    std::cerr << "\rLUT875   ";
    Ciphertext gin875 = 2 * gout871 + gout760;
    Ciphertext gout875 = ctx.eval_lut(&gin875, and2);

    std::cerr << "\rLUT876   ";
    Ciphertext gin876 = 2 * gout875 + gout779;
    Ciphertext gout876 = ctx.eval_lut(&gin876, xor2);

    std::cerr << "\rLUT877   ";
    Ciphertext gin877 = 2 * gout875 + gout779;
    Ciphertext gout877 = ctx.eval_lut(&gin877, nand2);

    std::cerr << "\rLUT878   ";
    Ciphertext gin878 = 2 * gout736 + gout728;
    Ciphertext gout878 = ctx.eval_lut(&gin878, nand2);

    std::cerr << "\rINV879   ";
    Ciphertext gout879 = 1 - gout878;

    std::cerr << "\rLUT880   ";
    Ciphertext gin880 = 2 * gout879 + gout726;
    Ciphertext gout880 = ctx.eval_lut(&gin880, xnor2);

    std::cerr << "\rIMUX881  ";
    Ciphertext gin881A = 2 * gout880 + gout434;
    Ciphertext gout881A = ctx.eval_lut(&gin881A, and2);
    Ciphertext gin881B = 2 * gout429 + (1 - gout434);
    Ciphertext gout881B = ctx.eval_lut(&gin881B, and2);
    Ciphertext gout881 = gout881A + gout881B;

    std::cerr << "\rLUT882   ";
    Ciphertext gin882 = 2 * gout433 + gout881;
    Ciphertext gout882 = ctx.eval_lut(&gin882, nand2);

    std::cerr << "\rLUT883   ";
    Ciphertext gin883 = 2 * gout879 + gout726;
    Ciphertext gout883 = ctx.eval_lut(&gin883, nand2);

    std::cerr << "\rLUT884   ";
    Ciphertext gin884 = 2 * gout724 + gout883;
    Ciphertext gout884 = ctx.eval_lut(&gin884, nand2);

    std::cerr << "\rLUT885   ";
    Ciphertext gin885 = 2 * gout813 + gout884;
    Ciphertext gout885 = ctx.eval_lut(&gin885, xnor2);

    std::cerr << "\rIMUX886  ";
    Ciphertext gin886A = 2 * gout885 + gout434;
    Ciphertext gout886A = ctx.eval_lut(&gin886A, and2);
    Ciphertext gin886B = 2 * gout612 + (1 - gout434);
    Ciphertext gout886B = ctx.eval_lut(&gin886B, and2);
    Ciphertext gout886 = gout886A + gout886B;

    std::cerr << "\rLUT887   ";
    Ciphertext gin887 = 2 * gout433 + gout886;
    Ciphertext gout887 = ctx.eval_lut(&gin887, nand2);

    std::cerr << "\rLUT888   ";
    Ciphertext gin888 = 2 * gout813 + gout884;
    Ciphertext gout888 = ctx.eval_lut(&gin888, and2);

    std::cerr << "\rLUT889   ";
    Ciphertext gin889 = 2 * gout888 + gout838;
    Ciphertext gout889 = ctx.eval_lut(&gin889, xnor2);

    std::cerr << "\rIMUX890  ";
    Ciphertext gin890A = 2 * gout889 + gout434;
    Ciphertext gout890A = ctx.eval_lut(&gin890A, and2);
    Ciphertext gin890B = 2 * gout615 + (1 - gout434);
    Ciphertext gout890B = ctx.eval_lut(&gin890B, and2);
    Ciphertext gout890 = gout890A + gout890B;

    std::cerr << "\rLUT891   ";
    Ciphertext gin891 = 2 * gout433 + gout890;
    Ciphertext gout891 = ctx.eval_lut(&gin891, nand2);

    std::cerr << "\rLUT892   ";
    Ciphertext gin892 = 2 * gout888 + gout838;
    Ciphertext gout892 = ctx.eval_lut(&gin892, nand2);

    std::cerr << "\rLUT893   ";
    Ciphertext gin893 = 2 * gout892 + gout837;
    Ciphertext gout893 = ctx.eval_lut(&gin893, and2);

    std::cerr << "\rLUT894   ";
    Ciphertext gin894 = 2 * gout893 + gout854;
    Ciphertext gout894 = ctx.eval_lut(&gin894, or2);

    std::cerr << "\rLUT895   ";
    Ciphertext gin895 = 2 * gout855 + gout894;
    Ciphertext gout895 = ctx.eval_lut(&gin895, nand2);

    std::cerr << "\rLUT896   ";
    Ciphertext gin896 = 2 * gout895 + gout866;
    Ciphertext gout896 = ctx.eval_lut(&gin896, xnor2);

    std::cerr << "\rIMUX897  ";
    Ciphertext gin897A = 2 * gout896 + gout434;
    Ciphertext gout897A = ctx.eval_lut(&gin897A, and2);
    Ciphertext gin897B = 2 * gout619 + (1 - gout434);
    Ciphertext gout897B = ctx.eval_lut(&gin897B, and2);
    Ciphertext gout897 = gout897A + gout897B;

    std::cerr << "\rLUT898   ";
    Ciphertext gin898 = 2 * gout433 + gout897;
    Ciphertext gout898 = ctx.eval_lut(&gin898, nand2);

    std::cerr << "\rLUT899   ";
    Ciphertext gin899 = 2 * gout895 + gout866;
    Ciphertext gout899 = ctx.eval_lut(&gin899, nand2);

    std::cerr << "\rLUT900   ";
    Ciphertext gin900 = 2 * gout867 + gout899;
    Ciphertext gout900 = ctx.eval_lut(&gin900, nand2);

    std::cerr << "\rLUT901   ";
    Ciphertext gin901 = 2 * gout900 + gout873;
    Ciphertext gout901 = ctx.eval_lut(&gin901, or2);

    std::cerr << "\rLUT902   ";
    Ciphertext gin902 = 2 * gout434 + gout901;
    Ciphertext gout902 = ctx.eval_lut(&gin902, and2);

    std::cerr << "\rLUT903   ";
    Ciphertext gin903 = 2 * gout900 + gout873;
    Ciphertext gout903 = ctx.eval_lut(&gin903, nand2);

    std::cerr << "\rLUT904   ";
    Ciphertext gin904 = 2 * gout874 + gout903;
    Ciphertext gout904 = ctx.eval_lut(&gin904, nand2);

    std::cerr << "\rLUT905   ";
    Ciphertext gin905 = 2 * gout904 + gout876;
    Ciphertext gout905 = ctx.eval_lut(&gin905, xnor2);

    std::cerr << "\rIMUX906  ";
    Ciphertext gin906A = 2 * gout905 + gout434;
    Ciphertext gout906A = ctx.eval_lut(&gin906A, and2);
    Ciphertext gin906B = 2 * gout623 + (1 - gout434);
    Ciphertext gout906B = ctx.eval_lut(&gin906B, and2);
    Ciphertext gout906 = gout906A + gout906B;

    std::cerr << "\rLUT907   ";
    Ciphertext gin907 = 2 * gout433 + gout906;
    Ciphertext gout907 = ctx.eval_lut(&gin907, nand2);

    std::cerr << "\rLUT908   ";
    Ciphertext gin908 = 2 * gout904 + gout876;
    Ciphertext gout908 = ctx.eval_lut(&gin908, nand2);

    std::cerr << "\rLUT909   ";
    Ciphertext gin909 = 2 * gout877 + gout908;
    Ciphertext gout909 = ctx.eval_lut(&gin909, nand2);

    std::cerr << "\rLUT910   ";
    Ciphertext gin910 = 2 * gout909 + gout793;
    Ciphertext gout910 = ctx.eval_lut(&gin910, or2);

    std::cerr << "\rLUT911   ";
    Ciphertext gin911 = 2 * gout434 + gout910;
    Ciphertext gout911 = ctx.eval_lut(&gin911, and2);

    std::cerr << "\rLUT912   ";
    Ciphertext gin912 = 2 * gout909 + gout793;
    Ciphertext gout912 = ctx.eval_lut(&gin912, nand2);

    std::cerr << "\rLUT913   ";
    Ciphertext gin913 = 2 * gout794 + gout912;
    Ciphertext gout913 = ctx.eval_lut(&gin913, nand2);

    std::cerr << "\rLUT914   ";
    Ciphertext gin914 = 2 * gout913 + gout799;
    Ciphertext gout914 = ctx.eval_lut(&gin914, xnor2);

    std::cerr << "\rIMUX915  ";
    Ciphertext gin915A = 2 * gout914 + gout434;
    Ciphertext gout915A = ctx.eval_lut(&gin915A, and2);
    Ciphertext gin915B = 2 * gout627 + (1 - gout434);
    Ciphertext gout915B = ctx.eval_lut(&gin915B, and2);
    Ciphertext gout915 = gout915A + gout915B;

    std::cerr << "\rLUT916   ";
    Ciphertext gin916 = 2 * gout433 + gout915;
    Ciphertext gout916 = ctx.eval_lut(&gin916, nand2);

    std::cerr << "\rLUT917   ";
    Ciphertext gin917 = 2 * gout913 + gout799;
    Ciphertext gout917 = ctx.eval_lut(&gin917, nand2);

    std::cerr << "\rLUT918   ";
    Ciphertext gin918 = 2 * gout800 + gout917;
    Ciphertext gout918 = ctx.eval_lut(&gin918, and2);

    std::cerr << "\rLUT919   ";
    Ciphertext gin919 = 2 * gout918 + gout803;
    Ciphertext gout919 = ctx.eval_lut(&gin919, or2);

    std::cerr << "\rLUT920   ";
    Ciphertext gin920 = 2 * gout434 + gout919;
    Ciphertext gout920 = ctx.eval_lut(&gin920, and2);

    std::cerr << "\rLUT921   ";
    Ciphertext gin921 = 2 * gout918 + gout803;
    Ciphertext gout921 = ctx.eval_lut(&gin921, nand2);

    std::cerr << "\rLUT922   ";
    Ciphertext gin922 = 2 * gout921 + gout920;
    Ciphertext gout922 = ctx.eval_lut(&gin922, nand2);

    std::cerr << "\rLUT923   ";
    Ciphertext gin923 = 2 * gout922 + gout634;
    Ciphertext gout923 = ctx.eval_lut(&gin923, nand2);

    std::cerr << "\rLUT924   ";
    Ciphertext gin924 = 2 * gout912 + gout911;
    Ciphertext gout924 = ctx.eval_lut(&gin924, nand2);

    std::cerr << "\rLUT925   ";
    Ciphertext gin925 = 2 * gout433 + gout924;
    Ciphertext gout925 = ctx.eval_lut(&gin925, and2);

    std::cerr << "\rLUT926   ";
    Ciphertext gin926 = 2 * gout639 + gout925;
    Ciphertext gout926 = ctx.eval_lut(&gin926, nand2);

    std::cerr << "\rLUT927   ";
    Ciphertext gin927 = 2 * gout903 + gout902;
    Ciphertext gout927 = ctx.eval_lut(&gin927, nand2);

    std::cerr << "\rLUT928   ";
    Ciphertext gin928 = 2 * gout433 + gout927;
    Ciphertext gout928 = ctx.eval_lut(&gin928, and2);

    std::cerr << "\rLUT929   ";
    Ciphertext gin929 = 2 * gout644 + gout928;
    Ciphertext gout929 = ctx.eval_lut(&gin929, nand2);

    std::cerr << "\rLUT930   ";
    Ciphertext gin930 = 2 * gout434 + gout894;
    Ciphertext gout930 = ctx.eval_lut(&gin930, and2);

    std::cerr << "\rLUT931   ";
    Ciphertext gin931 = 2 * gout893 + gout854;
    Ciphertext gout931 = ctx.eval_lut(&gin931, nand2);

    std::cerr << "\rLUT932   ";
    Ciphertext gin932 = 2 * gout931 + gout930;
    Ciphertext gout932 = ctx.eval_lut(&gin932, nand2);

    std::cerr << "\rLUT933   ";
    Ciphertext gin933 = 2 * gout433 + gout932;
    Ciphertext gout933 = ctx.eval_lut(&gin933, and2);

    std::cerr << "\rLUT934   ";
    Ciphertext gin934 = 2 * gout649 + gout933;
    Ciphertext gout934 = ctx.eval_lut(&gin934, nand2);

    std::cerr << "\r          \r";
    std::vector<long> out;
    out.push_back(ctx.decrypt(&gout439)); /* out0 */
    out.push_back(ctx.decrypt(&gout566)); /* out1 */
    out.push_back(ctx.decrypt(&gout527)); /* out2 */
    out.push_back(ctx.decrypt(&gout734)); /* out3 */
    out.push_back(ctx.decrypt(&gout743)); /* out4 */
    out.push_back(ctx.decrypt(&gout739)); /* out5 */
    out.push_back(ctx.decrypt(&gout882)); /* out6 */
    out.push_back(ctx.decrypt(&gout887)); /* out7 */
    out.push_back(ctx.decrypt(&gout891)); /* out8 */
    out.push_back(ctx.decrypt(&gout934)); /* out9 */
    out.push_back(ctx.decrypt(&gout898)); /* out10 */
    out.push_back(ctx.decrypt(&gout929)); /* out11 */
    out.push_back(ctx.decrypt(&gout907)); /* out12 */
    out.push_back(ctx.decrypt(&gout926)); /* out13 */
    out.push_back(ctx.decrypt(&gout916)); /* out14 */
    out.push_back(ctx.decrypt(&gout923)); /* out15 */
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

    /* add4 tests */
    std::cout << "[+] Testing add4" << std::endl;
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            std::cerr << i << " + " << j;
            out = compose(test_add4_boolean(ctx, i, j));
            assert(out == i + j);
        }
    }

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
