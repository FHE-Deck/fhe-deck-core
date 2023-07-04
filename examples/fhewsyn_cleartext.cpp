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
    long ct_a0 = (a >> 0) & 1;
    long ct_a1 = (a >> 1) & 1;
    long ct_a2 = (a >> 2) & 1;
    long ct_a3 = (a >> 3) & 1;
    long ct_b0 = (b >> 0) & 1;
    long ct_b1 = (b >> 1) & 1;
    long ct_b2 = (b >> 2) & 1;
    long ct_b3 = (b >> 3) & 1;

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
    auto gin0 = 2 * ct_a3 + ct_b3;
    auto gout0 = fxor2(gin0, 4);

    std::cerr << "\rLUT1   ";
    auto gin1 = 2 * ct_a2 + ct_b2;
    auto gout1 = fxor2(gin1, 4);

    std::cerr << "\rLUT2   ";
    auto gin2 = 2 * ct_a2 + ct_b2;
    auto gout2 = fnand2(gin2, 4);

    std::cerr << "\rLUT3   ";
    auto gin3 = 2 * ct_a0 + ct_b0;
    auto gout3 = fand2(gin3, 4);

    std::cerr << "\rLUT4   ";
    auto gin4 = 2 * ct_a3 + ct_b3;
    auto gout4 = fnand2(gin4, 4);

    std::cerr << "\rLUT5   ";
    auto gin5 = 2 * ct_a0 + ct_b0;
    auto gout5 = fxor2(gin5, 4);

    std::cerr << "\rLUT6   ";
    auto gin6 = 2 * ct_a1 + ct_b1;
    auto gout6 = fxor2(gin6, 4);

    std::cerr << "\rLUT7   ";
    auto gin7 = 2 * gout3 + gout6;
    auto gout7 = fxor2(gin7, 4);

    std::cerr << "\rLUT8   ";
    auto gin8 = 2 * gout3 + gout6;
    auto gout8 = fnand2(gin8, 4);

    std::cerr << "\rLUT9   ";
    auto gin9 = 2 * ct_a1 + ct_b1;
    auto gout9 = fnand2(gin9, 4);

    std::cerr << "\rLUT10   ";
    auto gin10 = 2 * gout9 + gout8;
    auto gout10 = fnand2(gin10, 4);

    std::cerr << "\rLUT11   ";
    auto gin11 = 2 * gout10 + gout1;
    auto gout11 = fxor2(gin11, 4);

    std::cerr << "\rLUT12   ";
    auto gin12 = 2 * gout10 + gout1;
    auto gout12 = fnand2(gin12, 4);

    std::cerr << "\rLUT13   ";
    auto gin13 = 2 * gout2 + gout12;
    auto gout13 = fnand2(gin13, 4);

    std::cerr << "\rLUT14   ";
    auto gin14 = 2 * gout13 + gout0;
    auto gout14 = fxor2(gin14, 4);

    std::cerr << "\rLUT15   ";
    auto gin15 = 2 * gout13 + gout0;
    auto gout15 = fnand2(gin15, 4);

    std::cerr << "\rLUT16   ";
    auto gin16 = 2 * gout4 + gout15;
    auto gout16 = fnand2(gin16, 4);

    std::cerr << "\r          \r";
    std::vector<long> out;
    out.push_back(gout5); /* out0 */
    out.push_back(gout7); /* out1 */
    out.push_back(gout11); /* out2 */
    out.push_back(gout14); /* out3 */
    out.push_back(gout16); /* out4 */
    return out;
}

std::vector<long>
test_calculator_boolean(FHEContext& ctx, uint8_t op, uint16_t x, uint16_t y)
{
    long ct_op0 = (op >> 0) & 1;
    long ct_op1 = (op >> 1) & 1;
    long ct_op2 = (op >> 2) & 1;
    long ct_op3 = (op >> 3) & 1;
    long ct_op4 = (op >> 4) & 1;
    long ct_op5 = (op >> 5) & 1;
    long ct_op6 = (op >> 6) & 1;
    long ct_op7 = (op >> 7) & 1;
    long ct_x0 = (x >> 0) & 1;
    long ct_x1 = (x >> 1) & 1;
    long ct_x2 = (x >> 2) & 1;
    long ct_x3 = (x >> 3) & 1;
    long ct_x4 = (x >> 4) & 1;
    long ct_x5 = (x >> 5) & 1;
    long ct_x6 = (x >> 6) & 1;
    long ct_x7 = (x >> 7) & 1;
    long ct_x8 = (x >> 8) & 1;
    long ct_x9 = (x >> 9) & 1;
    long ct_x10 = (x >> 10) & 1;
    long ct_x11 = (x >> 11) & 1;
    long ct_x12 = (x >> 12) & 1;
    long ct_x13 = (x >> 13) & 1;
    long ct_x14 = (x >> 14) & 1;
    long ct_x15 = (x >> 15) & 1;
    long ct_y0 = (y >> 0) & 1;
    long ct_y1 = (y >> 1) & 1;
    long ct_y2 = (y >> 2) & 1;
    long ct_y3 = (y >> 3) & 1;
    long ct_y4 = (y >> 4) & 1;
    long ct_y5 = (y >> 5) & 1;
    long ct_y6 = (y >> 6) & 1;
    long ct_y7 = (y >> 7) & 1;
    long ct_y8 = (y >> 8) & 1;
    long ct_y9 = (y >> 9) & 1;
    long ct_y10 = (y >> 10) & 1;
    long ct_y11 = (y >> 11) & 1;
    long ct_y12 = (y >> 12) & 1;
    long ct_y13 = (y >> 13) & 1;
    long ct_y14 = (y >> 14) & 1;
    long ct_y15 = (y >> 15) & 1;

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
    auto gin0 = 2 * ct_y9 + ct_x3;
    auto gout0 = fand2(gin0, 4);

    std::cerr << "\rLUT1   ";
    auto gin1 = 2 * ct_y1 + ct_x8;
    auto gout1 = fand2(gin1, 4);

    std::cerr << "\rLUT2   ";
    auto gin2 = 2 * ct_y5 + ct_x5;
    auto gout2 = fand2(gin2, 4);

    std::cerr << "\rLUT3   ";
    auto gin3 = 2 * ct_op2 + ct_op3;
    auto gout3 = fand2(gin3, 4);

    std::cerr << "\rLUT4   ";
    auto gin4 = 2 * ct_y0 + ct_x12;
    auto gout4 = fand2(gin4, 4);

    std::cerr << "\rLUT5   ";
    auto gin5 = 2 * ct_y0 + ct_x15;
    auto gout5 = fand2(gin5, 4);

    std::cerr << "\rLUT6   ";
    auto gin6 = 2 * ct_y5 + ct_x8;
    auto gout6 = fand2(gin6, 4);

    std::cerr << "\rLUT7   ";
    auto gin7 = 2 * ct_y4 + ct_x5;
    auto gout7 = fand2(gin7, 4);

    std::cerr << "\rLUT8   ";
    auto gin8 = 2 * ct_y2 + ct_x13;
    auto gout8 = fand2(gin8, 4);

    std::cerr << "\rLUT9   ";
    auto gin9 = 2 * ct_y12 + ct_x2;
    auto gout9 = fnand2(gin9, 4);

    std::cerr << "\rLUT10   ";
    auto gin10 = 2 * ct_y0 + ct_x13;
    auto gout10 = fand2(gin10, 4);

    std::cerr << "\rLUT11   ";
    auto gin11 = 2 * ct_y3 + ct_x8;
    auto gout11 = fand2(gin11, 4);

    std::cerr << "\rLUT12   ";
    auto gin12 = 2 * ct_y3 + ct_x11;
    auto gout12 = fnand2(gin12, 4);

    std::cerr << "\rLUT13   ";
    auto gin13 = 2 * ct_y0 + ct_x10;
    auto gout13 = fnand2(gin13, 4);

    std::cerr << "\rLUT14   ";
    auto gin14 = 2 * ct_y5 + ct_x2;
    auto gout14 = fand2(gin14, 4);

    std::cerr << "\rLUT15   ";
    auto gin15 = 2 * ct_y0 + ct_x11;
    auto gout15 = fnand2(gin15, 4);

    std::cerr << "\rLUT16   ";
    auto gin16 = 2 * ct_y4 + ct_x0;
    auto gout16 = fand2(gin16, 4);

    std::cerr << "\rLUT17   ";
    auto gin17 = 2 * ct_y7 + ct_x3;
    auto gout17 = fand2(gin17, 4);

    std::cerr << "\rLUT18   ";
    auto gin18 = 2 * ct_y9 + ct_x2;
    auto gout18 = fand2(gin18, 4);

    std::cerr << "\rLUT19   ";
    auto gin19 = 2 * ct_y13 + ct_x0;
    auto gout19 = fand2(gin19, 4);

    std::cerr << "\rLUT20   ";
    auto gin20 = 2 * ct_y3 + ct_x10;
    auto gout20 = fand2(gin20, 4);

    std::cerr << "\rLUT21   ";
    auto gin21 = 2 * ct_y3 + ct_x0;
    auto gout21 = fnand2(gin21, 4);

    std::cerr << "\rLUT22   ";
    auto gin22 = 2 * ct_y8 + ct_x7;
    auto gout22 = fand2(gin22, 4);

    std::cerr << "\rLUT23   ";
    auto gin23 = 2 * ct_y7 + ct_x2;
    auto gout23 = fand2(gin23, 4);

    std::cerr << "\rINV24   ";
    long gout24 = 1 - ct_y15;

    std::cerr << "\rLUT25   ";
    auto gin25 = 2 * ct_y2 + ct_x6;
    auto gout25 = fand2(gin25, 4);

    std::cerr << "\rINV26   ";
    long gout26 = 1 - ct_x2;

    std::cerr << "\rINV27   ";
    long gout27 = 1 - ct_x4;

    std::cerr << "\rINV28   ";
    long gout28 = 1 - ct_x8;

    std::cerr << "\rINV29   ";
    long gout29 = 1 - ct_x10;

    std::cerr << "\rINV30   ";
    long gout30 = 1 - ct_x12;

    std::cerr << "\rINV31   ";
    long gout31 = 1 - ct_y7;

    std::cerr << "\rLUT32   ";
    auto gin32 = 2 * ct_y0 + ct_x9;
    auto gout32 = fnand2(gin32, 4);

    std::cerr << "\rLUT33   ";
    auto gin33 = 2 * ct_y9 + ct_x1;
    auto gout33 = fnand2(gin33, 4);

    std::cerr << "\rLUT34   ";
    auto gin34 = 2 * ct_y0 + ct_x8;
    auto gout34 = fnand2(gin34, 4);

    std::cerr << "\rLUT35   ";
    auto gin35 = 2 * ct_y4 + ct_x6;
    auto gout35 = fand2(gin35, 4);

    std::cerr << "\rLUT36   ";
    auto gin36 = 2 * ct_y5 + ct_x0;
    auto gout36 = fand2(gin36, 4);

    std::cerr << "\rLUT37   ";
    auto gin37 = 2 * ct_y7 + ct_x6;
    auto gout37 = fand2(gin37, 4);

    std::cerr << "\rLUT38   ";
    auto gin38 = 2 * ct_y8 + ct_x4;
    auto gout38 = fand2(gin38, 4);

    std::cerr << "\rLUT39   ";
    auto gin39 = 2 * ct_y6 + ct_x3;
    auto gout39 = fand2(gin39, 4);

    std::cerr << "\rLUT40   ";
    auto gin40 = 2 * gout23 + gout39;
    auto gout40 = fxor2(gin40, 4);

    std::cerr << "\rLUT41   ";
    auto gin41 = 2 * gout23 + gout39;
    auto gout41 = fnand2(gin41, 4);

    std::cerr << "\rLUT42   ";
    auto gin42 = 2 * ct_y2 + ct_x1;
    auto gout42 = fand2(gin42, 4);

    std::cerr << "\rLUT43   ";
    auto gin43 = 2 * gout42 + gout21;
    auto gout43 = fxnor2(gin43, 4);

    std::cerr << "\rLUT44   ";
    auto gin44 = 2 * ct_y5 + ct_x10;
    auto gout44 = fand2(gin44, 4);

    std::cerr << "\rLUT45   ";
    auto gin45 = 2 * ct_y1 + ct_x13;
    auto gout45 = fand2(gin45, 4);

    std::cerr << "\rLUT46   ";
    auto gin46 = 2 * ct_y3 + ct_x4;
    auto gout46 = fand2(gin46, 4);

    std::cerr << "\rLUT47   ";
    auto gin47 = 2 * ct_y0 + ct_x2;
    auto gout47 = fand2(gin47, 4);

    std::cerr << "\rLUT48   ";
    auto gin48 = 2 * ct_y7 + ct_x7;
    auto gout48 = fnand2(gin48, 4);

    std::cerr << "\rLUT49   ";
    auto gin49 = 2 * ct_y8 + ct_x5;
    auto gout49 = fand2(gin49, 4);

    std::cerr << "\rLUT50   ";
    auto gin50 = 2 * ct_y3 + ct_x7;
    auto gout50 = fand2(gin50, 4);

    std::cerr << "\rLUT51   ";
    auto gin51 = 2 * ct_y7 + ct_x1;
    auto gout51 = fand2(gin51, 4);

    std::cerr << "\rLUT52   ";
    auto gin52 = 2 * ct_y15 + ct_x15;
    auto gout52 = fxor2(gin52, 4);

    std::cerr << "\rLUT53   ";
    auto gin53 = 2 * gout35 + gout13;
    auto gout53 = fxnor2(gin53, 4);

    std::cerr << "\rLUT54   ";
    auto gin54 = 2 * ct_y0 + ct_x1;
    auto gout54 = fand2(gin54, 4);

    std::cerr << "\rLUT55   ";
    auto gin55 = 2 * ct_y2 + ct_x10;
    auto gout55 = fand2(gin55, 4);

    std::cerr << "\rLUT56   ";
    auto gin56 = 2 * ct_y4 + ct_x7;
    auto gout56 = fand2(gin56, 4);

    std::cerr << "\rINV57   ";
    long gout57 = 1 - ct_y4;

    std::cerr << "\rLUT58   ";
    auto gin58 = 2 * ct_y0 + ct_x0;
    auto gout58 = fand2(gin58, 4);

    std::cerr << "\rLUT59   ";
    auto gin59 = 2 * gout56 + gout15;
    auto gout59 = fxnor2(gin59, 4);

    std::cerr << "\rLUT60   ";
    auto gin60 = 2 * ct_y13 + ct_x1;
    auto gout60 = fand2(gin60, 4);

    std::cerr << "\rLUT61   ";
    auto gin61 = 2 * gout60 + gout9;
    auto gout61 = fxnor2(gin61, 4);

    std::cerr << "\rLUT62   ";
    auto gin62 = 2 * ct_y2 + ct_x2;
    auto gout62 = fand2(gin62, 4);

    std::cerr << "\rINV63   ";
    long gout63 = 1 - gout58;

    std::cerr << "\rLUT64   ";
    auto gin64 = 2 * ct_y5 + ct_x6;
    auto gout64 = fand2(gin64, 4);

    std::cerr << "\rLUT65   ";
    auto gin65 = 2 * ct_y3 + ct_x2;
    auto gout65 = fand2(gin65, 4);

    std::cerr << "\rLUT66   ";
    auto gin66 = 2 * ct_y0 + ct_x7;
    auto gout66 = fnand2(gin66, 4);

    std::cerr << "\rLUT67   ";
    auto gin67 = 2 * ct_y7 + ct_x5;
    auto gout67 = fand2(gin67, 4);

    std::cerr << "\rLUT68   ";
    auto gin68 = 2 * ct_y7 + ct_x8;
    auto gout68 = fand2(gin68, 4);

    std::cerr << "\rLUT69   ";
    auto gin69 = 2 * ct_y2 + ct_x9;
    auto gout69 = fand2(gin69, 4);

    std::cerr << "\rLUT70   ";
    auto gin70 = 2 * gout11 + gout69;
    auto gout70 = fxor2(gin70, 4);

    std::cerr << "\rLUT71   ";
    auto gin71 = 2 * ct_y8 + ct_x6;
    auto gout71 = fand2(gin71, 4);

    std::cerr << "\rINV72   ";
    long gout72 = 1 - ct_x9;

    std::cerr << "\rLUT73   ";
    auto gin73 = 2 * ct_y10 + ct_x0;
    auto gout73 = fand2(gin73, 4);

    std::cerr << "\rLUT74   ";
    auto gin74 = 2 * gout33 + gout73;
    auto gout74 = fxnor2(gin74, 4);

    std::cerr << "\rINV75   ";
    long gout75 = 1 - ct_x13;

    std::cerr << "\rINV76   ";
    long gout76 = 1 - ct_y9;

    std::cerr << "\rLUT77   ";
    auto gin77 = 2 * ct_y9 + ct_x4;
    auto gout77 = fand2(gin77, 4);

    std::cerr << "\rINV78   ";
    long gout78 = 1 - ct_x1;

    std::cerr << "\rLUT79   ";
    auto gin79 = 2 * gout2 + gout53;
    auto gout79 = fnand2(gin79, 4);

    std::cerr << "\rINV80   ";
    long gout80 = 1 - ct_x5;

    std::cerr << "\rLUT81   ";
    auto gin81 = 2 * ct_y12 + ct_x0;
    auto gout81 = fand2(gin81, 4);

    std::cerr << "\rLUT82   ";
    auto gin82 = 2 * gout81 + gout60;
    auto gout82 = fand2(gin82, 4);

    std::cerr << "\rINV83   ";
    long gout83 = 1 - gout81;

    std::cerr << "\rLUT84   ";
    auto gin84 = 2 * ct_y8 + ct_x2;
    auto gout84 = fand2(gin84, 4);

    std::cerr << "\rLUT85   ";
    auto gin85 = 2 * gout2 + gout53;
    auto gout85 = fxor2(gin85, 4);

    std::cerr << "\rLUT86   ";
    auto gin86 = 2 * ct_y6 + ct_x1;
    auto gout86 = fnand2(gin86, 4);

    std::cerr << "\rLUT87   ";
    auto gin87 = 2 * ct_y5 + ct_x1;
    auto gout87 = fand2(gin87, 4);

    std::cerr << "\rLUT88   ";
    auto gin88 = 2 * ct_y9 + ct_x6;
    auto gout88 = fand2(gin88, 4);

    std::cerr << "\rLUT89   ";
    auto gin89 = 2 * ct_y2 + ct_x7;
    auto gout89 = fand2(gin89, 4);

    std::cerr << "\rLUT90   ";
    auto gin90 = 2 * ct_y6 + ct_x2;
    auto gout90 = fand2(gin90, 4);

    std::cerr << "\rLUT91   ";
    auto gin91 = 2 * gout51 + gout90;
    auto gout91 = fxor2(gin91, 4);

    std::cerr << "\rLUT92   ";
    auto gin92 = 2 * gout51 + gout90;
    auto gout92 = fnand2(gin92, 4);

    std::cerr << "\rLUT93   ";
    auto gin93 = 2 * gout47 + gout35;
    auto gout93 = fnand2(gin93, 4);

    std::cerr << "\rINV94   ";
    long gout94 = 1 - ct_y8;

    std::cerr << "\rLUT95   ";
    auto gin95 = 2 * ct_y8 + ct_x3;
    auto gout95 = fand2(gin95, 4);

    std::cerr << "\rLUT96   ";
    auto gin96 = 2 * gout64 + gout59;
    auto gout96 = fnand2(gin96, 4);

    std::cerr << "\rLUT97   ";
    auto gin97 = 2 * gout54 + gout7;
    auto gout97 = fnand2(gin97, 4);

    std::cerr << "\rLUT98   ";
    auto gin98 = 2 * ct_y1 + ct_x1;
    auto gout98 = fnand2(gin98, 4);

    std::cerr << "\rINV99   ";
    long gout99 = 1 - ct_y1;

    std::cerr << "\rLUT100   ";
    auto gin100 = 2 * ct_y1 + ct_x2;
    auto gout100 = fand2(gin100, 4);

    std::cerr << "\rLUT101   ";
    auto gin101 = 2 * gout100 + gout43;
    auto gout101 = fxor2(gin101, 4);

    std::cerr << "\rLUT102   ";
    auto gin102 = 2 * gout100 + gout43;
    auto gout102 = fnand2(gin102, 4);

    std::cerr << "\rLUT103   ";
    auto gin103 = 2 * ct_y4 + ct_x9;
    auto gout103 = fand2(gin103, 4);

    std::cerr << "\rLUT104   ";
    auto gin104 = 2 * ct_y11 + ct_x0;
    auto gout104 = fand2(gin104, 4);

    std::cerr << "\rLUT105   ";
    auto gin105 = 2 * gout64 + gout59;
    auto gout105 = fxor2(gin105, 4);

    std::cerr << "\rLUT106   ";
    auto gin106 = 2 * ct_y2 + ct_x12;
    auto gout106 = fand2(gin106, 4);

    std::cerr << "\rLUT107   ";
    auto gin107 = 2 * gout12 + gout106;
    auto gout107 = fxnor2(gin107, 4);

    std::cerr << "\rLUT108   ";
    auto gin108 = 2 * gout45 + gout107;
    auto gout108 = fxor2(gin108, 4);

    std::cerr << "\rLUT109   ";
    auto gin109 = 2 * gout45 + gout107;
    auto gout109 = fnand2(gin109, 4);

    std::cerr << "\rLUT110   ";
    auto gin110 = 2 * ct_y9 + ct_x0;
    auto gout110 = fand2(gin110, 4);

    std::cerr << "\rLUT111   ";
    auto gin111 = 2 * ct_y2 + ct_x5;
    auto gout111 = fand2(gin111, 4);

    std::cerr << "\rLUT112   ";
    auto gin112 = 2 * gout46 + gout111;
    auto gout112 = fxor2(gin112, 4);

    std::cerr << "\rLUT113   ";
    auto gin113 = 2 * gout46 + gout111;
    auto gout113 = fnand2(gin113, 4);

    std::cerr << "\rLUT114   ";
    auto gin114 = 2 * ct_y4 + ct_x8;
    auto gout114 = fand2(gin114, 4);

    std::cerr << "\rLUT115   ";
    auto gin115 = 2 * ct_y0 + ct_x5;
    auto gout115 = fnand2(gin115, 4);

    std::cerr << "\rLUT116   ";
    auto gin116 = 2 * ct_y6 + ct_x6;
    auto gout116 = fand2(gin116, 4);

    std::cerr << "\rLUT117   ";
    auto gin117 = 2 * gout67 + gout116;
    auto gout117 = fnand2(gin117, 4);

    std::cerr << "\rLUT118   ";
    auto gin118 = 2 * ct_y1 + ct_x9;
    auto gout118 = fand2(gin118, 4);

    std::cerr << "\rLUT119   ";
    auto gin119 = 2 * gout67 + gout116;
    auto gout119 = fxor2(gin119, 4);

    std::cerr << "\rLUT120   ";
    auto gin120 = 2 * ct_y6 + ct_x0;
    auto gout120 = fand2(gin120, 4);

    std::cerr << "\rLUT121   ";
    auto gin121 = 2 * gout120 + gout51;
    auto gout121 = fand2(gin121, 4);

    std::cerr << "\rLUT122   ";
    auto gin122 = 2 * ct_y6 + ct_x7;
    auto gout122 = fand2(gin122, 4);

    std::cerr << "\rLUT123   ";
    auto gin123 = 2 * gout122 + gout68;
    auto gout123 = fnand2(gin123, 4);

    std::cerr << "\rLUT124   ";
    auto gin124 = 2 * ct_y1 + ct_x12;
    auto gout124 = fand2(gin124, 4);

    std::cerr << "\rLUT125   ";
    auto gin125 = 2 * ct_y10 + ct_x3;
    auto gout125 = fand2(gin125, 4);

    std::cerr << "\rLUT126   ";
    auto gin126 = 2 * ct_y3 + ct_x6;
    auto gout126 = fand2(gin126, 4);

    std::cerr << "\rLUT127   ";
    auto gin127 = 2 * ct_y0 + ct_x6;
    auto gout127 = fnand2(gin127, 4);

    std::cerr << "\rINV128   ";
    long gout128 = 1 - ct_y10;

    std::cerr << "\rINV129   ";
    long gout129 = 1 - ct_x14;

    std::cerr << "\rLUT130   ";
    auto gin130 = 2 * (1 - ct_x0) + ct_y15;
    auto gout130 = fand2(gin130, 4);

    std::cerr << "\rINV131   ";
    long gout131 = 1 - ct_x6;

    std::cerr << "\rINV132   ";
    long gout132 = 1 - ct_y5;

    std::cerr << "\rLUT133   ";
    auto gin133 = 2 * ct_y10 + ct_x4;
    auto gout133 = fnand2(gin133, 4);

    std::cerr << "\rLUT134   ";
    auto gin134 = 2 * ct_y6 + ct_x4;
    auto gout134 = fand2(gin134, 4);

    std::cerr << "\rLUT135   ";
    auto gin135 = 2 * gout17 + gout134;
    auto gout135 = fnand2(gin135, 4);

    std::cerr << "\rLUT136   ";
    auto gin136 = 2 * ct_y3 + ct_x1;
    auto gout136 = fnand2(gin136, 4);

    std::cerr << "\rLUT137   ";
    auto gin137 = 2 * ct_y10 + ct_x1;
    auto gout137 = fand2(gin137, 4);

    std::cerr << "\rLUT138   ";
    auto gin138 = 2 * gout137 + gout18;
    auto gout138 = fxor2(gin138, 4);

    std::cerr << "\rLUT139   ";
    auto gin139 = 2 * gout104 + gout138;
    auto gout139 = fxor2(gin139, 4);

    std::cerr << "\rLUT140   ";
    auto gin140 = 2 * gout104 + gout138;
    auto gout140 = fnand2(gin140, 4);

    std::cerr << "\rLUT141   ";
    auto gin141 = 2 * gout137 + gout18;
    auto gout141 = fnand2(gin141, 4);

    std::cerr << "\rLUT142   ";
    auto gin142 = 2 * ct_y1 + ct_x6;
    auto gout142 = fand2(gin142, 4);

    std::cerr << "\rLUT143   ";
    auto gin143 = 2 * gout142 + gout112;
    auto gout143 = fxor2(gin143, 4);

    std::cerr << "\rLUT144   ";
    auto gin144 = 2 * gout142 + gout112;
    auto gout144 = fnand2(gin144, 4);

    std::cerr << "\rLUT145   ";
    auto gin145 = 2 * gout58 + (1 - gout98);
    auto gout145 = fand2(gin145, 4);

    std::cerr << "\rLUT146   ";
    auto gin146 = 2 * gout115 + (1 - gout103);
    auto gout146 = for2(gin146, 4);

    std::cerr << "\rLUT147   ";
    auto gin147 = 2 * gout22 + gout88;
    auto gout147 = fxnor2(gin147, 4);

    std::cerr << "\rLUT148   ";
    auto gin148 = 2 * gout17 + gout134;
    auto gout148 = fxor2(gin148, 4);

    std::cerr << "\rLUT149   ";
    auto gin149 = 2 * ct_y7 + ct_x0;
    auto gout149 = fand2(gin149, 4);

    std::cerr << "\rLUT150   ";
    auto gin150 = 2 * gout86 + gout149;
    auto gout150 = fxnor2(gin150, 4);

    std::cerr << "\rLUT151   ";
    auto gin151 = 2 * ct_y9 + ct_x5;
    auto gout151 = fand2(gin151, 4);

    std::cerr << "\rLUT152   ";
    auto gin152 = 2 * gout133 + gout151;
    auto gout152 = fxnor2(gin152, 4);

    std::cerr << "\rLUT153   ";
    auto gin153 = 2 * ct_y0 + ct_x14;
    auto gout153 = fand2(gin153, 4);

    std::cerr << "\rLUT154   ";
    auto gin154 = 2 * gout42 + gout65;
    auto gout154 = fnand2(gin154, 4);

    std::cerr << "\rLUT155   ";
    auto gin155 = 2 * ct_y3 + ct_x9;
    auto gout155 = fand2(gin155, 4);

    std::cerr << "\rLUT156   ";
    auto gin156 = 2 * ct_y11 + ct_x4;
    auto gout156 = fand2(gin156, 4);

    std::cerr << "\rLUT157   ";
    auto gin157 = 2 * ct_y4 + ct_x1;
    auto gout157 = fand2(gin157, 4);

    std::cerr << "\rLUT158   ";
    auto gin158 = 2 * gout115 + gout157;
    auto gout158 = fxnor2(gin158, 4);

    std::cerr << "\rLUT159   ";
    auto gin159 = 2 * gout36 + gout158;
    auto gout159 = fxor2(gin159, 4);

    std::cerr << "\rLUT160   ";
    auto gin160 = 2 * gout36 + gout158;
    auto gout160 = fnand2(gin160, 4);

    std::cerr << "\rLUT161   ";
    auto gin161 = 2 * gout97 + gout160;
    auto gout161 = fnand2(gin161, 4);

    std::cerr << "\rLUT162   ";
    auto gin162 = 2 * ct_y2 + ct_x11;
    auto gout162 = fand2(gin162, 4);

    std::cerr << "\rLUT163   ";
    auto gin163 = 2 * gout20 + gout162;
    auto gout163 = fxor2(gin163, 4);

    std::cerr << "\rLUT164   ";
    auto gin164 = 2 * gout124 + gout163;
    auto gout164 = fxor2(gin164, 4);

    std::cerr << "\rLUT165   ";
    auto gin165 = 2 * gout124 + gout163;
    auto gout165 = fnand2(gin165, 4);

    std::cerr << "\rLUT166   ";
    auto gin166 = 2 * gout20 + gout162;
    auto gout166 = fnand2(gin166, 4);

    std::cerr << "\rLUT167   ";
    auto gin167 = 2 * gout166 + gout165;
    auto gout167 = fnand2(gin167, 4);

    std::cerr << "\rLUT168   ";
    auto gin168 = 2 * gout167 + gout108;
    auto gout168 = fxnor2(gin168, 4);

    std::cerr << "\rLUT169   ";
    auto gin169 = 2 * ct_y2 + ct_x8;
    auto gout169 = fand2(gin169, 4);

    std::cerr << "\rLUT170   ";
    auto gin170 = 2 * gout50 + gout169;
    auto gout170 = fxor2(gin170, 4);

    std::cerr << "\rLUT171   ";
    auto gin171 = 2 * gout118 + gout170;
    auto gout171 = fxor2(gin171, 4);

    std::cerr << "\rLUT172   ";
    auto gin172 = 2 * gout118 + gout170;
    auto gout172 = fnand2(gin172, 4);

    std::cerr << "\rLUT173   ";
    auto gin173 = 2 * gout50 + gout169;
    auto gout173 = fnand2(gin173, 4);

    std::cerr << "\rLUT174   ";
    auto gin174 = 2 * ct_y1 + ct_y0;
    auto gout174 = fnor2(gin174, 4);

    std::cerr << "\rINV175   ";
    long gout175 = 1 - gout174;

    std::cerr << "\rLUT176   ";
    auto gin176 = 2 * (1 - ct_op1) + ct_op0;
    auto gout176 = fand2(gin176, 4);

    std::cerr << "\rLUT177   ";
    auto gin177 = 2 * gout176 + gout3;
    auto gout177 = fand2(gin177, 4);

    std::cerr << "\rLUT178   ";
    auto gin178 = 2 * ct_y11 + ct_x3;
    auto gout178 = fand2(gin178, 4);

    std::cerr << "\rLUT179   ";
    auto gin179 = 2 * gout178 + gout152;
    auto gout179 = fxor2(gin179, 4);

    std::cerr << "\rLUT180   ";
    auto gin180 = 2 * gout178 + gout152;
    auto gout180 = fnand2(gin180, 4);

    std::cerr << "\rLUT181   ";
    auto gin181 = 2 * ct_y4 + ct_x10;
    auto gout181 = fand2(gin181, 4);

    std::cerr << "\rLUT182   ";
    auto gin182 = 2 * gout181 + gout153;
    auto gout182 = fxor2(gin182, 4);

    std::cerr << "\rLUT183   ";
    auto gin183 = 2 * gout127 + (1 - gout181);
    auto gout183 = for2(gin183, 4);

    std::cerr << "\rLUT184   ";
    auto gin184 = 2 * gout183 + gout79;
    auto gout184 = fnand2(gin184, 4);

    std::cerr << "\rLUT185   ";
    auto gin185 = 2 * ct_y3 + ct_x3;
    auto gout185 = fand2(gin185, 4);

    std::cerr << "\rLUT186   ";
    auto gin186 = 2 * ct_y1 + ct_x4;
    auto gout186 = fand2(gin186, 4);

    std::cerr << "\rLUT187   ";
    auto gin187 = 2 * gout103 + gout10;
    auto gout187 = fnand2(gin187, 4);

    std::cerr << "\rLUT188   ";
    auto gin188 = 2 * ct_y14 + ct_x1;
    auto gout188 = fand2(gin188, 4);

    std::cerr << "\rLUT189   ";
    auto gin189 = 2 * ct_y3 + ct_x12;
    auto gout189 = fand2(gin189, 4);

    std::cerr << "\rLUT190   ";
    auto gin190 = 2 * gout24 + gout189;
    auto gout190 = fxnor2(gin190, 4);

    std::cerr << "\rLUT191   ";
    auto gin191 = 2 * gout162 + gout189;
    auto gout191 = fnand2(gin191, 4);

    std::cerr << "\rLUT192   ";
    auto gin192 = 2 * ct_y6 + ct_x9;
    auto gout192 = fand2(gin192, 4);

    std::cerr << "\rLUT193   ";
    auto gin193 = 2 * gout44 + gout192;
    auto gout193 = fxnor2(gin193, 4);

    std::cerr << "\rLUT194   ";
    auto gin194 = 2 * gout68 + gout193;
    auto gout194 = fxnor2(gin194, 4);

    std::cerr << "\rLUT195   ";
    auto gin195 = 2 * ct_y4 + ct_x11;
    auto gout195 = fand2(gin195, 4);

    std::cerr << "\rLUT196   ";
    auto gin196 = 2 * gout66 + (1 - gout195);
    auto gout196 = for2(gin196, 4);

    std::cerr << "\rLUT197   ";
    auto gin197 = 2 * gout196 + gout96;
    auto gout197 = fnand2(gin197, 4);

    std::cerr << "\rLUT198   ";
    auto gin198 = 2 * ct_y4 + ct_x4;
    auto gout198 = fand2(gin198, 4);

    std::cerr << "\rLUT199   ";
    auto gin199 = 2 * gout198 + gout34;
    auto gout199 = fxnor2(gin199, 4);

    std::cerr << "\rLUT200   ";
    auto gin200 = 2 * gout58 + gout198;
    auto gout200 = fand2(gin200, 4);

    std::cerr << "\rINV201   ";
    long gout201 = 1 - gout200;

    std::cerr << "\rINV202   ";
    long gout202 = 1 - ct_op0;

    std::cerr << "\rINV203   ";
    long gout203 = 1 - ct_x11;

    std::cerr << "\rINV204   ";
    long gout204 = 1 - ct_x3;

    std::cerr << "\rLUT205   ";
    auto gin205 = 2 * gout155 + gout55;
    auto gout205 = fnand2(gin205, 4);

    std::cerr << "\rLUT206   ";
    auto gin206 = 2 * ct_y6 + ct_x5;
    auto gout206 = fand2(gin206, 4);

    std::cerr << "\rLUT207   ";
    auto gin207 = 2 * ct_y5 + ct_x4;
    auto gout207 = fand2(gin207, 4);

    std::cerr << "\rLUT208   ";
    auto gin208 = 2 * ct_y7 + ct_x4;
    auto gout208 = fand2(gin208, 4);

    std::cerr << "\rLUT209   ";
    auto gin209 = 2 * gout208 + gout206;
    auto gout209 = fxor2(gin209, 4);

    std::cerr << "\rLUT210   ";
    auto gin210 = 2 * gout208 + gout206;
    auto gout210 = fnand2(gin210, 4);

    std::cerr << "\rLUT211   ";
    auto gin211 = 2 * ct_y0 + ct_x4;
    auto gout211 = fnand2(gin211, 4);

    std::cerr << "\rLUT212   ";
    auto gin212 = 2 * gout211 + (1 - gout114);
    auto gout212 = for2(gin212, 4);

    std::cerr << "\rLUT213   ";
    auto gin213 = 2 * gout211 + gout16;
    auto gout213 = fxnor2(gin213, 4);

    std::cerr << "\rLUT214   ";
    auto gin214 = 2 * gout155 + gout55;
    auto gout214 = fxor2(gin214, 4);

    std::cerr << "\rLUT215   ";
    auto gin215 = 2 * ct_y2 + ct_x3;
    auto gout215 = fand2(gin215, 4);

    std::cerr << "\rLUT216   ";
    auto gin216 = 2 * gout65 + gout215;
    auto gout216 = fxor2(gin216, 4);

    std::cerr << "\rLUT217   ";
    auto gin217 = 2 * gout186 + gout216;
    auto gout217 = fxor2(gin217, 4);

    std::cerr << "\rLUT218   ";
    auto gin218 = 2 * gout186 + gout216;
    auto gout218 = fnand2(gin218, 4);

    std::cerr << "\rLUT219   ";
    auto gin219 = 2 * gout65 + gout215;
    auto gout219 = fnand2(gin219, 4);

    std::cerr << "\rLUT220   ";
    auto gin220 = 2 * ct_y2 + ct_x0;
    auto gout220 = fand2(gin220, 4);

    std::cerr << "\rLUT221   ";
    auto gin221 = 2 * (1 - ct_op2) + ct_op1;
    auto gout221 = fand2(gin221, 4);

    std::cerr << "\rINV222   ";
    long gout222 = 1 - ct_y6;

    std::cerr << "\rINV223   ";
    long gout223 = 1 - ct_y2;

    std::cerr << "\rLUT224   ";
    auto gin224 = 2 * gout223 + gout174;
    auto gout224 = fand2(gin224, 4);

    std::cerr << "\rINV225   ";
    long gout225 = 1 - gout47;

    std::cerr << "\rLUT226   ";
    auto gin226 = 2 * gout125 + gout77;
    auto gout226 = fnand2(gin226, 4);

    std::cerr << "\rLUT227   ";
    auto gin227 = 2 * ct_op3 + gout221;
    auto gout227 = fand2(gin227, 4);

    std::cerr << "\rLUT228   ";
    auto gin228 = 2 * gout167 + gout108;
    auto gout228 = fnand2(gin228, 4);

    std::cerr << "\rLUT229   ";
    auto gin229 = 2 * ct_y1 + ct_x3;
    auto gout229 = fand2(gin229, 4);

    std::cerr << "\rLUT230   ";
    auto gin230 = 2 * (1 - gout220) + gout136;
    auto gout230 = for2(gin230, 4);

    std::cerr << "\rLUT231   ";
    auto gin231 = 2 * gout230 + gout102;
    auto gout231 = fnand2(gin231, 4);

    std::cerr << "\rLUT232   ";
    auto gin232 = 2 * gout125 + gout77;
    auto gout232 = fxor2(gin232, 4);

    std::cerr << "\rLUT233   ";
    auto gin233 = 2 * gout84 + gout148;
    auto gout233 = fnand2(gin233, 4);

    std::cerr << "\rLUT234   ";
    auto gin234 = 2 * gout135 + gout233;
    auto gout234 = fnand2(gin234, 4);

    std::cerr << "\rLUT235   ";
    auto gin235 = 2 * ct_y8 + ct_x1;
    auto gout235 = fand2(gin235, 4);

    std::cerr << "\rLUT236   ";
    auto gin236 = 2 * ct_y12 + ct_x3;
    auto gout236 = fand2(gin236, 4);

    std::cerr << "\rLUT237   ";
    auto gin237 = 2 * gout156 + gout236;
    auto gout237 = fxnor2(gin237, 4);

    std::cerr << "\rLUT238   ";
    auto gin238 = 2 * gout147 + gout237;
    auto gout238 = fxnor2(gin238, 4);

    std::cerr << "\rLUT239   ";
    auto gin239 = 2 * ct_y14 + ct_x0;
    auto gout239 = fand2(gin239, 4);

    std::cerr << "\rLUT240   ";
    auto gin240 = 2 * gout239 + gout61;
    auto gout240 = fxor2(gin240, 4);

    std::cerr << "\rLUT241   ";
    auto gin241 = 2 * gout239 + gout61;
    auto gout241 = fnand2(gin241, 4);

    std::cerr << "\rLUT242   ";
    auto gin242 = 2 * gout103 + gout10;
    auto gout242 = fxor2(gin242, 4);

    std::cerr << "\rLUT243   ";
    auto gin243 = 2 * gout6 + gout242;
    auto gout243 = fxor2(gin243, 4);

    std::cerr << "\rLUT244   ";
    auto gin244 = 2 * gout6 + gout242;
    auto gout244 = fnand2(gin244, 4);

    std::cerr << "\rLUT245   ";
    auto gin245 = 2 * gout187 + gout244;
    auto gout245 = fnand2(gin245, 4);

    std::cerr << "\rLUT246   ";
    auto gin246 = 2 * gout84 + gout148;
    auto gout246 = fxor2(gin246, 4);

    std::cerr << "\rLUT247   ";
    auto gin247 = 2 * ct_y1 + ct_x0;
    auto gout247 = fand2(gin247, 4);

    std::cerr << "\rLUT248   ";
    auto gin248 = 2 * gout247 + gout42;
    auto gout248 = fand2(gin248, 4);

    std::cerr << "\rLUT249   ";
    auto gin249 = 2 * gout248 + gout101;
    auto gout249 = fxor2(gin249, 4);

    std::cerr << "\rLUT250   ";
    auto gin250 = 2 * gout248 + gout101;
    auto gout250 = fnand2(gin250, 4);

    std::cerr << "\rLUT251   ";
    auto gin251 = 2 * gout11 + gout69;
    auto gout251 = fnand2(gin251, 4);

    std::cerr << "\rLUT252   ";
    auto gin252 = 2 * ct_y5 + ct_x3;
    auto gout252 = fand2(gin252, 4);

    std::cerr << "\rLUT253   ";
    auto gin253 = 2 * gout252 + gout199;
    auto gout253 = fxor2(gin253, 4);

    std::cerr << "\rLUT254   ";
    auto gin254 = 2 * gout252 + gout199;
    auto gout254 = fnand2(gin254, 4);

    std::cerr << "\rLUT255   ";
    auto gin255 = 2 * gout212 + gout254;
    auto gout255 = fnand2(gin255, 4);

    std::cerr << "\rLUT256   ";
    auto gin256 = 2 * ct_y0 + ct_x0;
    auto gout256 = fxnor2(gin256, 4);

    std::cerr << "\rLUT257   ";
    auto gin257 = 2 * gout219 + gout218;
    auto gout257 = fnand2(gin257, 4);

    std::cerr << "\rLUT258   ";
    auto gin258 = 2 * gout113 + gout144;
    auto gout258 = fnand2(gin258, 4);

    std::cerr << "\rLUT259   ";
    auto gin259 = 2 * ct_y13 + ct_x2;
    auto gout259 = fand2(gin259, 4);

    std::cerr << "\rLUT260   ";
    auto gin260 = 2 * ct_y1 + ct_x7;
    auto gout260 = fand2(gin260, 4);

    std::cerr << "\rLUT261   ";
    auto gin261 = 2 * ct_y1 + ct_x5;
    auto gout261 = fand2(gin261, 4);

    std::cerr << "\rLUT262   ";
    auto gin262 = 2 * gout98 + gout220;
    auto gout262 = fxnor2(gin262, 4);

    std::cerr << "\rLUT263   ";
    auto gin263 = 2 * gout225 + gout262;
    auto gout263 = fxnor2(gin263, 4);

    std::cerr << "\rLUT264   ";
    auto gin264 = 2 * gout145 + gout263;
    auto gout264 = fxnor2(gin264, 4);

    std::cerr << "\rLUT265   ";
    auto gin265 = 2 * gout145 + gout263;
    auto gout265 = fand2(gin265, 4);

    std::cerr << "\rLUT266   ";
    auto gin266 = 2 * gout136 + gout62;
    auto gout266 = fxnor2(gin266, 4);

    std::cerr << "\rLUT267   ";
    auto gin267 = 2 * gout141 + gout140;
    auto gout267 = fnand2(gin267, 4);

    std::cerr << "\rLUT268   ";
    auto gin268 = 2 * gout38 + gout119;
    auto gout268 = fnand2(gin268, 4);

    std::cerr << "\rLUT269   ";
    auto gin269 = 2 * gout117 + gout268;
    auto gout269 = fnand2(gin269, 4);

    std::cerr << "\rLUT270   ";
    auto gin270 = 2 * gout161 + gout120;
    auto gout270 = fand2(gin270, 4);

    std::cerr << "\rLUT271   ";
    auto gin271 = 2 * ct_op6 + ct_op7;
    auto gout271 = fnor2(gin271, 4);

    std::cerr << "\rLUT272   ";
    auto gin272 = 2 * ct_y11 + ct_x1;
    auto gout272 = fand2(gin272, 4);

    std::cerr << "\rLUT273   ";
    auto gin273 = 2 * gout38 + gout119;
    auto gout273 = fxor2(gin273, 4);

    std::cerr << "\rLUT274   ";
    auto gin274 = 2 * gout197 + gout273;
    auto gout274 = fxor2(gin274, 4);

    std::cerr << "\rLUT275   ";
    auto gin275 = 2 * gout197 + gout273;
    auto gout275 = fnand2(gin275, 4);

    std::cerr << "\rLUT276   ";
    auto gin276 = 2 * gout247 + gout54;
    auto gout276 = fxor2(gin276, 4);

    std::cerr << "\rLUT277   ";
    auto gin277 = 2 * gout161 + gout120;
    auto gout277 = fxor2(gin277, 4);

    std::cerr << "\rLUT278   ";
    auto gin278 = 2 * gout114 + gout4;
    auto gout278 = fnand2(gin278, 4);

    std::cerr << "\rLUT279   ";
    auto gin279 = 2 * ct_y5 + ct_x7;
    auto gout279 = fand2(gin279, 4);

    std::cerr << "\rLUT280   ";
    auto gin280 = 2 * gout7 + gout32;
    auto gout280 = fxnor2(gin280, 4);

    std::cerr << "\rLUT281   ";
    auto gin281 = 2 * ct_y2 + ct_x4;
    auto gout281 = fand2(gin281, 4);

    std::cerr << "\rLUT282   ";
    auto gin282 = 2 * gout185 + gout281;
    auto gout282 = fxor2(gin282, 4);

    std::cerr << "\rLUT283   ";
    auto gin283 = 2 * gout261 + gout282;
    auto gout283 = fxor2(gin283, 4);

    std::cerr << "\rLUT284   ";
    auto gin284 = 2 * gout257 + gout283;
    auto gout284 = fxnor2(gin284, 4);

    std::cerr << "\rLUT285   ";
    auto gin285 = 2 * gout257 + gout283;
    auto gout285 = fand2(gin285, 4);

    std::cerr << "\rLUT286   ";
    auto gin286 = 2 * gout261 + gout282;
    auto gout286 = fnand2(gin286, 4);

    std::cerr << "\rLUT287   ";
    auto gin287 = 2 * gout185 + gout281;
    auto gout287 = fnand2(gin287, 4);

    std::cerr << "\rLUT288   ";
    auto gin288 = 2 * gout287 + gout286;
    auto gout288 = fnand2(gin288, 4);

    std::cerr << "\rLUT289   ";
    auto gin289 = 2 * gout288 + gout143;
    auto gout289 = fxnor2(gin289, 4);

    std::cerr << "\rLUT290   ";
    auto gin290 = 2 * gout288 + gout143;
    auto gout290 = fand2(gin290, 4);

    std::cerr << "\rLUT291   ";
    auto gin291 = 2 * ct_y1 + ct_x11;
    auto gout291 = fand2(gin291, 4);

    std::cerr << "\rLUT292   ";
    auto gin292 = 2 * gout291 + gout214;
    auto gout292 = fxor2(gin292, 4);

    std::cerr << "\rLUT293   ";
    auto gin293 = 2 * gout291 + gout214;
    auto gout293 = fnand2(gin293, 4);

    std::cerr << "\rLUT294   ";
    auto gin294 = 2 * gout205 + gout293;
    auto gout294 = fnand2(gin294, 4);

    std::cerr << "\rLUT295   ";
    auto gin295 = 2 * ct_y3 + ct_x5;
    auto gout295 = fand2(gin295, 4);

    std::cerr << "\rLUT296   ";
    auto gin296 = 2 * gout295 + gout25;
    auto gout296 = fxor2(gin296, 4);

    std::cerr << "\rLUT297   ";
    auto gin297 = 2 * gout260 + gout296;
    auto gout297 = fxor2(gin297, 4);

    std::cerr << "\rLUT298   ";
    auto gin298 = 2 * gout258 + gout297;
    auto gout298 = fxnor2(gin298, 4);

    std::cerr << "\rLUT299   ";
    auto gin299 = 2 * gout298 + gout253;
    auto gout299 = fxnor2(gin299, 4);

    std::cerr << "\rLUT300   ";
    auto gin300 = 2 * (1 - gout298) + gout253;
    auto gout300 = fand2(gin300, 4);

    std::cerr << "\rLUT301   ";
    auto gin301 = 2 * gout258 + gout297;
    auto gout301 = fand2(gin301, 4);

    std::cerr << "\rLUT302   ";
    auto gin302 = 2 * gout260 + gout296;
    auto gout302 = fnand2(gin302, 4);

    std::cerr << "\rLUT303   ";
    auto gin303 = 2 * gout295 + gout25;
    auto gout303 = fnand2(gin303, 4);

    std::cerr << "\rLUT304   ";
    auto gin304 = 2 * ct_y1 + ct_x14;
    auto gout304 = fand2(gin304, 4);

    std::cerr << "\rLUT305   ";
    auto gin305 = 2 * gout304 + gout5;
    auto gout305 = fxnor2(gin305, 4);

    std::cerr << "\rLUT306   ";
    auto gin306 = 2 * ct_y6 + ct_x8;
    auto gout306 = fand2(gin306, 4);

    std::cerr << "\rLUT307   ";
    auto gin307 = 2 * gout48 + gout306;
    auto gout307 = fxnor2(gin307, 4);

    std::cerr << "\rLUT308   ";
    auto gin308 = 2 * gout71 + gout307;
    auto gout308 = fxor2(gin308, 4);

    std::cerr << "\rLUT309   ";
    auto gin309 = 2 * gout245 + gout308;
    auto gout309 = fxor2(gin309, 4);

    std::cerr << "\rLUT310   ";
    auto gin310 = 2 * gout245 + gout308;
    auto gout310 = fnand2(gin310, 4);

    std::cerr << "\rLUT311   ";
    auto gin311 = 2 * gout71 + gout307;
    auto gout311 = fnand2(gin311, 4);

    std::cerr << "\rLUT312   ";
    auto gin312 = 2 * gout123 + gout311;
    auto gout312 = fand2(gin312, 4);

    std::cerr << "\rLUT313   ";
    auto gin313 = 2 * ct_y12 + ct_x1;
    auto gout313 = fnand2(gin313, 4);

    std::cerr << "\rLUT314   ";
    auto gin314 = 2 * gout313 + (1 - gout259);
    auto gout314 = for2(gin314, 4);

    std::cerr << "\rLUT315   ";
    auto gin315 = 2 * gout314 + gout241;
    auto gout315 = fnand2(gin315, 4);

    std::cerr << "\rLUT316   ";
    auto gin316 = 2 * gout313 + gout19;
    auto gout316 = fxnor2(gin316, 4);

    std::cerr << "\rLUT317   ";
    auto gin317 = 2 * ct_y10 + ct_x2;
    auto gout317 = fand2(gin317, 4);

    std::cerr << "\rLUT318   ";
    auto gin318 = 2 * gout317 + gout0;
    auto gout318 = fxor2(gin318, 4);

    std::cerr << "\rLUT319   ";
    auto gin319 = 2 * gout272 + gout318;
    auto gout319 = fxor2(gin319, 4);

    std::cerr << "\rLUT320   ";
    auto gin320 = 2 * gout267 + gout319;
    auto gout320 = fxor2(gin320, 4);

    std::cerr << "\rLUT321   ";
    auto gin321 = 2 * gout83 + gout320;
    auto gout321 = fxnor2(gin321, 4);

    std::cerr << "\rLUT322   ";
    auto gin322 = 2 * gout267 + gout319;
    auto gout322 = fnand2(gin322, 4);

    std::cerr << "\rLUT323   ";
    auto gin323 = 2 * gout272 + gout318;
    auto gout323 = fnand2(gin323, 4);

    std::cerr << "\rLUT324   ";
    auto gin324 = 2 * gout317 + gout0;
    auto gout324 = fnand2(gin324, 4);

    std::cerr << "\rLUT325   ";
    auto gin325 = 2 * gout110 + gout137;
    auto gout325 = fand2(gin325, 4);

    std::cerr << "\rLUT326   ";
    auto gin326 = 2 * gout325 + gout139;
    auto gout326 = fand2(gin326, 4);

    std::cerr << "\rLUT327   ";
    auto gin327 = 2 * gout235 + gout40;
    auto gout327 = fnand2(gin327, 4);

    std::cerr << "\rLUT328   ";
    auto gin328 = 2 * gout41 + gout327;
    auto gout328 = fnand2(gin328, 4);

    std::cerr << "\rINV329   ";
    long gout329 = 1 - ct_y14;

    std::cerr << "\rLUT330   ";
    auto gin330 = 2 * (1 - ct_op4) + ct_op5;
    auto gout330 = fand2(gin330, 4);

    std::cerr << "\rLUT331   ";
    auto gin331 = 2 * gout330 + gout271;
    auto gout331 = fand2(gin331, 4);

    std::cerr << "\rLUT332   ";
    auto gin332 = 2 * gout331 + gout177;
    auto gout332 = fand2(gin332, 4);

    std::cerr << "\rLUT333   ";
    auto gin333 = 2 * ct_y14 + gout332;
    auto gout333 = fand2(gin333, 4);

    std::cerr << "\rLUT334   ";
    auto gin334 = 2 * ct_y13 + gout332;
    auto gout334 = fand2(gin334, 4);

    std::cerr << "\rLUT335   ";
    auto gin335 = 2 * ct_y12 + gout332;
    auto gout335 = fnand2(gin335, 4);

    std::cerr << "\rLUT336   ";
    auto gin336 = 2 * ct_y11 + gout332;
    auto gout336 = fnand2(gin336, 4);

    std::cerr << "\rLUT337   ";
    auto gin337 = 2 * (1 - gout224) + gout332;
    auto gout337 = fand2(gin337, 4);

    std::cerr << "\rLUT338   ";
    auto gin338 = 2 * gout332 + gout175;
    auto gout338 = fand2(gin338, 4);

    std::cerr << "\rLUT339   ";
    auto gin339 = 2 * gout223 + gout338;
    auto gout339 = fxnor2(gin339, 4);

    std::cerr << "\rLUT340   ";
    auto gin340 = 2 * gout26 + gout339;
    auto gout340 = fxnor2(gin340, 4);

    std::cerr << "\rLUT341   ";
    auto gin341 = 2 * ct_x2 + gout339;
    auto gout341 = fnand2(gin341, 4);

    std::cerr << "\rLUT342   ";
    auto gin342 = 2 * ct_y0 + gout332;
    auto gout342 = fand2(gin342, 4);

    std::cerr << "\rLUT343   ";
    auto gin343 = 2 * gout99 + gout342;
    auto gout343 = fxnor2(gin343, 4);

    std::cerr << "\rLUT344   ";
    auto gin344 = 2 * gout78 + gout343;
    auto gout344 = fxnor2(gin344, 4);

    std::cerr << "\rLUT345   ";
    auto gin345 = 2 * gout63 + gout344;
    auto gout345 = fxnor2(gin345, 4);

    std::cerr << "\rLUT346   ";
    auto gin346 = 2 * gout58 + gout344;
    auto gout346 = fnand2(gin346, 4);

    std::cerr << "\rLUT347   ";
    auto gin347 = 2 * ct_x1 + gout343;
    auto gout347 = fnand2(gin347, 4);

    std::cerr << "\rLUT348   ";
    auto gin348 = 2 * gout347 + gout346;
    auto gout348 = fnand2(gin348, 4);

    std::cerr << "\rLUT349   ";
    auto gin349 = 2 * gout348 + gout340;
    auto gout349 = fxnor2(gin349, 4);

    std::cerr << "\rLUT350   ";
    auto gin350 = 2 * gout348 + gout340;
    auto gout350 = fnand2(gin350, 4);

    std::cerr << "\rLUT351   ";
    auto gin351 = 2 * gout341 + gout350;
    auto gout351 = fnand2(gin351, 4);

    std::cerr << "\rLUT352   ";
    auto gin352 = 2 * gout331 + gout227;
    auto gout352 = fand2(gin352, 4);

    std::cerr << "\rLUT353   ";
    auto gin353 = 2 * gout352 + gout332;
    auto gout353 = for2(gin353, 4);

    std::cerr << "\rLUT354   ";
    auto gin354 = 2 * gout324 + gout323;
    auto gout354 = fnand2(gin354, 4);

    std::cerr << "\rINV355   ";
    long gout355 = 1 - ct_x7;

    std::cerr << "\rLUT356   ";
    auto gin356 = 2 * ct_y11 + ct_x2;
    auto gout356 = fand2(gin356, 4);

    std::cerr << "\rLUT357   ";
    auto gin357 = 2 * gout356 + gout232;
    auto gout357 = fxor2(gin357, 4);

    std::cerr << "\rLUT358   ";
    auto gin358 = 2 * gout354 + gout357;
    auto gout358 = fxnor2(gin358, 4);

    std::cerr << "\rLUT359   ";
    auto gin359 = 2 * gout358 + gout316;
    auto gout359 = fxnor2(gin359, 4);

    std::cerr << "\rLUT360   ";
    auto gin360 = 2 * (1 - gout358) + gout316;
    auto gout360 = fand2(gin360, 4);

    std::cerr << "\rLUT361   ";
    auto gin361 = 2 * gout354 + gout357;
    auto gout361 = fand2(gin361, 4);

    std::cerr << "\rLUT362   ";
    auto gin362 = 2 * gout361 + gout360;
    auto gout362 = for2(gin362, 4);

    std::cerr << "\rLUT363   ";
    auto gin363 = 2 * gout356 + gout232;
    auto gout363 = fnand2(gin363, 4);

    std::cerr << "\rLUT364   ";
    auto gin364 = 2 * gout226 + gout363;
    auto gout364 = fnand2(gin364, 4);

    std::cerr << "\rLUT365   ";
    auto gin365 = 2 * gout364 + gout179;
    auto gout365 = fxnor2(gin365, 4);

    std::cerr << "\rLUT366   ";
    auto gin366 = 2 * gout365 + gout240;
    auto gout366 = fxnor2(gin366, 4);

    std::cerr << "\rLUT367   ";
    auto gin367 = 2 * (1 - gout365) + gout240;
    auto gout367 = fand2(gin367, 4);

    std::cerr << "\rLUT368   ";
    auto gin368 = 2 * gout364 + gout179;
    auto gout368 = fnand2(gin368, 4);

    std::cerr << "\rLUT369   ";
    auto gin369 = 2 * gout368 + (1 - gout367);
    auto gout369 = fand2(gin369, 4);

    std::cerr << "\rLUT370   ";
    auto gin370 = 2 * gout81 + gout320;
    auto gout370 = fnand2(gin370, 4);

    std::cerr << "\rLUT371   ";
    auto gin371 = 2 * gout322 + gout370;
    auto gout371 = fnand2(gin371, 4);

    std::cerr << "\rLUT372   ";
    auto gin372 = 2 * gout95 + gout209;
    auto gout372 = fnand2(gin372, 4);

    std::cerr << "\rLUT373   ";
    auto gin373 = 2 * gout210 + gout372;
    auto gout373 = fnand2(gin373, 4);

    std::cerr << "\rLUT374   ";
    auto gin374 = 2 * gout373 + gout274;
    auto gout374 = fxor2(gin374, 4);

    std::cerr << "\rLUT375   ";
    auto gin375 = 2 * gout373 + gout274;
    auto gout375 = fnand2(gin375, 4);

    std::cerr << "\rLUT376   ";
    auto gin376 = 2 * gout275 + gout375;
    auto gout376 = fnand2(gin376, 4);

    std::cerr << "\rLUT377   ";
    auto gin377 = 2 * gout376 + gout359;
    auto gout377 = fxor2(gin377, 4);

    std::cerr << "\rLUT378   ";
    auto gin378 = 2 * gout371 + gout377;
    auto gout378 = fxor2(gin378, 4);

    std::cerr << "\rLUT379   ";
    auto gin379 = 2 * gout371 + gout377;
    auto gout379 = fnand2(gin379, 4);

    std::cerr << "\rLUT380   ";
    auto gin380 = 2 * gout376 + gout359;
    auto gout380 = fnand2(gin380, 4);

    std::cerr << "\rLUT381   ";
    auto gin381 = 2 * gout380 + gout379;
    auto gout381 = fnand2(gin381, 4);

    std::cerr << "\rLUT382   ";
    auto gin382 = 2 * gout82 + gout381;
    auto gout382 = fxor2(gin382, 4);

    std::cerr << "\rLUT383   ";
    auto gin383 = 2 * gout82 + gout381;
    auto gout383 = fand2(gin383, 4);

    std::cerr << "\rLUT384   ";
    auto gin384 = 2 * ct_y4 + ct_x2;
    auto gout384 = fand2(gin384, 4);

    std::cerr << "\rLUT385   ";
    auto gin385 = 2 * gout127 + gout384;
    auto gout385 = fxnor2(gin385, 4);

    std::cerr << "\rLUT386   ";
    auto gin386 = 2 * gout87 + gout385;
    auto gout386 = fxor2(gin386, 4);

    std::cerr << "\rLUT387   ";
    auto gin387 = 2 * gout284 + gout386;
    auto gout387 = fxnor2(gin387, 4);

    std::cerr << "\rLUT388   ";
    auto gin388 = 2 * (1 - gout284) + gout386;
    auto gout388 = fand2(gin388, 4);

    std::cerr << "\rLUT389   ";
    auto gin389 = 2 * gout285 + gout388;
    auto gout389 = for2(gin389, 4);

    std::cerr << "\rLUT390   ";
    auto gin390 = 2 * gout87 + gout385;
    auto gout390 = fnand2(gin390, 4);

    std::cerr << "\rLUT391   ";
    auto gin391 = 2 * gout93 + gout390;
    auto gout391 = fnand2(gin391, 4);

    std::cerr << "\rLUT392   ";
    auto gin392 = 2 * gout391 + gout150;
    auto gout392 = fxor2(gin392, 4);

    std::cerr << "\rLUT393   ";
    auto gin393 = 2 * gout391 + gout150;
    auto gout393 = fand2(gin393, 4);

    std::cerr << "\rLUT394   ";
    auto gin394 = 2 * ct_y0 + ct_x3;
    auto gout394 = fand2(gin394, 4);

    std::cerr << "\rLUT395   ";
    auto gin395 = 2 * gout394 + gout56;
    auto gout395 = fnand2(gin395, 4);

    std::cerr << "\rLUT396   ";
    auto gin396 = 2 * gout394 + gout249;
    auto gout396 = fnand2(gin396, 4);

    std::cerr << "\rLUT397   ";
    auto gin397 = 2 * gout250 + gout396;
    auto gout397 = fnand2(gin397, 4);

    std::cerr << "\rINV398   ";
    long gout398 = 1 - gout394;

    std::cerr << "\rLUT399   ";
    auto gin399 = 2 * gout398 + gout249;
    auto gout399 = fxnor2(gin399, 4);

    std::cerr << "\rLUT400   ";
    auto gin400 = 2 * gout8 + gout190;
    auto gout400 = fxnor2(gin400, 4);

    std::cerr << "\rLUT401   ";
    auto gin401 = 2 * gout235 + gout40;
    auto gout401 = fxor2(gin401, 4);

    std::cerr << "\rLUT402   ";
    auto gin402 = 2 * gout255 + gout401;
    auto gout402 = fnand2(gin402, 4);

    std::cerr << "\rLUT403   ";
    auto gin403 = 2 * gout229 + gout266;
    auto gout403 = fnand2(gin403, 4);

    std::cerr << "\rLUT404   ";
    auto gin404 = 2 * gout154 + gout403;
    auto gout404 = fnand2(gin404, 4);

    std::cerr << "\rLUT405   ";
    auto gin405 = 2 * gout404 + gout217;
    auto gout405 = fxnor2(gin405, 4);

    std::cerr << "\rLUT406   ";
    auto gin406 = 2 * gout404 + gout217;
    auto gout406 = fand2(gin406, 4);

    std::cerr << "\rLUT407   ";
    auto gin407 = 2 * gout47 + gout262;
    auto gout407 = fand2(gin407, 4);

    std::cerr << "\rLUT408   ";
    auto gin408 = 2 * gout407 + gout399;
    auto gout408 = fand2(gin408, 4);

    std::cerr << "\rINV409   ";
    long gout409 = 1 - gout408;

    std::cerr << "\rINV410   ";
    long gout410 = 1 - gout407;

    std::cerr << "\rLUT411   ";
    auto gin411 = 2 * gout410 + gout399;
    auto gout411 = fxnor2(gin411, 4);

    std::cerr << "\rLUT412   ";
    auto gin412 = 2 * gout265 + gout411;
    auto gout412 = fxnor2(gin412, 4);

    std::cerr << "\rLUT413   ";
    auto gin413 = 2 * gout265 + gout411;
    auto gout413 = fnand2(gin413, 4);

    std::cerr << "\rLUT414   ";
    auto gin414 = 2 * gout409 + gout413;
    auto gout414 = fnand2(gin414, 4);

    std::cerr << "\rLUT415   ";
    auto gin415 = 2 * gout305 + gout400;
    auto gout415 = fxnor2(gin415, 4);

    std::cerr << "\rLUT416   ";
    auto gin416 = 2 * gout37 + gout122;
    auto gout416 = fnand2(gin416, 4);

    std::cerr << "\rLUT417   ";
    auto gin417 = 2 * gout173 + gout172;
    auto gout417 = fnand2(gin417, 4);

    std::cerr << "\rLUT418   ";
    auto gin418 = 2 * gout126 + gout89;
    auto gout418 = fnand2(gin418, 4);

    std::cerr << "\rLUT419   ";
    auto gin419 = 2 * (1 - gout405) + gout159;
    auto gout419 = fand2(gin419, 4);

    std::cerr << "\rLUT420   ";
    auto gin420 = 2 * gout406 + gout419;
    auto gout420 = for2(gin420, 4);

    std::cerr << "\rLUT421   ";
    auto gin421 = 2 * gout420 + gout387;
    auto gout421 = fxnor2(gin421, 4);

    std::cerr << "\rLUT422   ";
    auto gin422 = 2 * gout421 + gout277;
    auto gout422 = fxnor2(gin422, 4);

    std::cerr << "\rINV423   ";
    long gout423 = 1 - gout422;

    std::cerr << "\rLUT424   ";
    auto gin424 = 2 * (1 - gout421) + gout277;
    auto gout424 = fand2(gin424, 4);

    std::cerr << "\rLUT425   ";
    auto gin425 = 2 * gout420 + gout387;
    auto gout425 = fand2(gin425, 4);

    std::cerr << "\rLUT426   ";
    auto gin426 = 2 * gout425 + gout424;
    auto gout426 = for2(gin426, 4);

    std::cerr << "\rLUT427   ";
    auto gin427 = 2 * gout229 + gout266;
    auto gout427 = fxor2(gin427, 4);

    std::cerr << "\rLUT428   ";
    auto gin428 = 2 * gout231 + gout427;
    auto gout428 = fxnor2(gin428, 4);

    std::cerr << "\rLUT429   ";
    auto gin429 = 2 * gout428 + gout213;
    auto gout429 = fxnor2(gin429, 4);

    std::cerr << "\rLUT430   ";
    auto gin430 = 2 * gout397 + gout429;
    auto gout430 = fxor2(gin430, 4);

    std::cerr << "\rLUT431   ";
    auto gin431 = 2 * gout430 + gout414;
    auto gout431 = fxnor2(gin431, 4);

    std::cerr << "\rLUT432   ";
    auto gin432 = 2 * gout408 + gout430;
    auto gout432 = fand2(gin432, 4);

    std::cerr << "\rLUT433   ";
    auto gin433 = 2 * (1 - gout413) + gout430;
    auto gout433 = fand2(gin433, 4);

    std::cerr << "\rLUT434   ";
    auto gin434 = 2 * gout397 + gout429;
    auto gout434 = fand2(gin434, 4);

    std::cerr << "\rLUT435   ";
    auto gin435 = 2 * gout434 + gout432;
    auto gout435 = for2(gin435, 4);

    std::cerr << "\rLUT436   ";
    auto gin436 = 2 * (1 - gout428) + gout213;
    auto gout436 = fand2(gin436, 4);

    std::cerr << "\rLUT437   ";
    auto gin437 = 2 * gout231 + gout427;
    auto gout437 = fand2(gin437, 4);

    std::cerr << "\rLUT438   ";
    auto gin438 = 2 * gout437 + gout436;
    auto gout438 = for2(gin438, 4);

    std::cerr << "\rLUT439   ";
    auto gin439 = 2 * gout95 + gout209;
    auto gout439 = fxor2(gin439, 4);

    std::cerr << "\rLUT440   ";
    auto gin440 = 2 * gout184 + gout439;
    auto gout440 = fxor2(gin440, 4);

    std::cerr << "\rLUT441   ";
    auto gin441 = 2 * gout234 + gout440;
    auto gout441 = fxor2(gin441, 4);

    std::cerr << "\rLUT442   ";
    auto gin442 = 2 * gout234 + gout440;
    auto gout442 = fnand2(gin442, 4);

    std::cerr << "\rLUT443   ";
    auto gin443 = 2 * gout184 + gout439;
    auto gout443 = fnand2(gin443, 4);

    std::cerr << "\rLUT444   ";
    auto gin444 = 2 * gout443 + gout442;
    auto gout444 = fnand2(gin444, 4);

    std::cerr << "\rLUT445   ";
    auto gin445 = 2 * gout444 + gout321;
    auto gout445 = fxor2(gin445, 4);

    std::cerr << "\rLUT446   ";
    auto gin446 = 2 * gout326 + gout445;
    auto gout446 = fxor2(gin446, 4);

    std::cerr << "\rLUT447   ";
    auto gin447 = 2 * gout326 + gout445;
    auto gout447 = fnand2(gin447, 4);

    std::cerr << "\rLUT448   ";
    auto gin448 = 2 * gout444 + gout321;
    auto gout448 = fnand2(gin448, 4);

    std::cerr << "\rLUT449   ";
    auto gin449 = 2 * gout448 + gout447;
    auto gout449 = fnand2(gin449, 4);

    std::cerr << "\rLUT450   ";
    auto gin450 = 2 * ct_y4 + ct_x3;
    auto gout450 = fand2(gin450, 4);

    std::cerr << "\rLUT451   ";
    auto gin451 = 2 * gout66 + gout450;
    auto gout451 = fxnor2(gin451, 4);

    std::cerr << "\rLUT452   ";
    auto gin452 = 2 * gout14 + gout451;
    auto gout452 = fxor2(gin452, 4);

    std::cerr << "\rLUT453   ";
    auto gin453 = 2 * gout289 + gout452;
    auto gout453 = fxnor2(gin453, 4);

    std::cerr << "\rLUT454   ";
    auto gin454 = 2 * gout389 + gout453;
    auto gout454 = fxnor2(gin454, 4);

    std::cerr << "\rLUT455   ";
    auto gin455 = 2 * gout454 + gout392;
    auto gout455 = fxnor2(gin455, 4);

    std::cerr << "\rLUT456   ";
    auto gin456 = 2 * gout426 + gout455;
    auto gout456 = fxor2(gin456, 4);

    std::cerr << "\rLUT457   ";
    auto gin457 = 2 * gout270 + gout456;
    auto gout457 = fxor2(gin457, 4);

    std::cerr << "\rLUT458   ";
    auto gin458 = 2 * gout270 + gout456;
    auto gout458 = fnand2(gin458, 4);

    std::cerr << "\rLUT459   ";
    auto gin459 = 2 * gout426 + gout455;
    auto gout459 = fnand2(gin459, 4);

    std::cerr << "\rLUT460   ";
    auto gin460 = 2 * gout459 + gout458;
    auto gout460 = fnand2(gin460, 4);

    std::cerr << "\rLUT461   ";
    auto gin461 = 2 * (1 - gout454) + gout392;
    auto gout461 = fand2(gin461, 4);

    std::cerr << "\rLUT462   ";
    auto gin462 = 2 * gout389 + gout453;
    auto gout462 = fand2(gin462, 4);

    std::cerr << "\rLUT463   ";
    auto gin463 = 2 * gout462 + gout461;
    auto gout463 = for2(gin463, 4);

    std::cerr << "\rLUT464   ";
    auto gin464 = 2 * (1 - gout289) + gout452;
    auto gout464 = fand2(gin464, 4);

    std::cerr << "\rLUT465   ";
    auto gin465 = 2 * gout290 + gout464;
    auto gout465 = for2(gin465, 4);

    std::cerr << "\rLUT466   ";
    auto gin466 = 2 * gout465 + gout299;
    auto gout466 = fxnor2(gin466, 4);

    std::cerr << "\rLUT467   ";
    auto gin467 = 2 * gout465 + gout299;
    auto gout467 = fand2(gin467, 4);

    std::cerr << "\rLUT468   ";
    auto gin468 = 2 * gout14 + gout451;
    auto gout468 = fnand2(gin468, 4);

    std::cerr << "\rLUT469   ";
    auto gin469 = 2 * gout395 + gout468;
    auto gout469 = fnand2(gin469, 4);

    std::cerr << "\rLUT470   ";
    auto gin470 = 2 * ct_y10 + ct_x5;
    auto gout470 = fand2(gin470, 4);

    std::cerr << "\rLUT471   ";
    auto gin471 = 2 * gout470 + gout238;
    auto gout471 = fxnor2(gin471, 4);

    std::cerr << "\rLUT472   ";
    auto gin472 = 2 * gout77 + gout470;
    auto gout472 = fnand2(gin472, 4);

    std::cerr << "\rLUT473   ";
    auto gin473 = 2 * gout472 + gout180;
    auto gout473 = fand2(gin473, 4);

    std::cerr << "\rLUT474   ";
    auto gin474 = 2 * gout259 + gout473;
    auto gout474 = fxnor2(gin474, 4);

    std::cerr << "\rLUT475   ";
    auto gin475 = 2 * gout471 + gout474;
    auto gout475 = fxnor2(gin475, 4);

    std::cerr << "\rLUT476   ";
    auto gin476 = 2 * gout181 + gout153;
    auto gout476 = fnand2(gin476, 4);

    std::cerr << "\rLUT477   ";
    auto gin477 = 2 * ct_y5 + ct_x9;
    auto gout477 = fand2(gin477, 4);

    std::cerr << "\rLUT478   ";
    auto gin478 = 2 * gout477 + gout182;
    auto gout478 = fxor2(gin478, 4);

    std::cerr << "\rLUT479   ";
    auto gin479 = 2 * gout168 + gout478;
    auto gout479 = fxnor2(gin479, 4);

    std::cerr << "\rLUT480   ";
    auto gin480 = 2 * (1 - gout168) + gout478;
    auto gout480 = fand2(gin480, 4);

    std::cerr << "\rLUT481   ";
    auto gin481 = 2 * gout228 + (1 - gout480);
    auto gout481 = fand2(gin481, 4);

    std::cerr << "\rLUT482   ";
    auto gin482 = 2 * gout481 + gout312;
    auto gout482 = fxnor2(gin482, 4);

    std::cerr << "\rLUT483   ";
    auto gin483 = 2 * gout477 + gout182;
    auto gout483 = fnand2(gin483, 4);

    std::cerr << "\rLUT484   ";
    auto gin484 = 2 * gout476 + gout483;
    auto gout484 = fand2(gin484, 4);

    std::cerr << "\rLUT485   ";
    auto gin485 = 2 * gout484 + gout194;
    auto gout485 = fxnor2(gin485, 4);

    std::cerr << "\rLUT486   ";
    auto gin486 = 2 * gout294 + gout164;
    auto gout486 = fand2(gin486, 4);

    std::cerr << "\rLUT487   ";
    auto gin487 = 2 * gout114 + gout4;
    auto gout487 = fxor2(gin487, 4);

    std::cerr << "\rLUT488   ";
    auto gin488 = 2 * gout279 + gout487;
    auto gout488 = fxor2(gin488, 4);

    std::cerr << "\rLUT489   ";
    auto gin489 = 2 * gout279 + gout487;
    auto gout489 = fnand2(gin489, 4);

    std::cerr << "\rLUT490   ";
    auto gin490 = 2 * gout278 + gout489;
    auto gout490 = fnand2(gin490, 4);

    std::cerr << "\rLUT491   ";
    auto gin491 = 2 * gout207 + gout280;
    auto gout491 = fnand2(gin491, 4);

    std::cerr << "\rLUT492   ";
    auto gin492 = 2 * gout146 + gout491;
    auto gout492 = fnand2(gin492, 4);

    std::cerr << "\rLUT493   ";
    auto gin493 = 2 * gout492 + gout246;
    auto gout493 = fxor2(gin493, 4);

    std::cerr << "\rLUT494   ";
    auto gin494 = 2 * gout328 + gout493;
    auto gout494 = fxor2(gin494, 4);

    std::cerr << "\rLUT495   ";
    auto gin495 = 2 * gout328 + gout493;
    auto gout495 = fnand2(gin495, 4);

    std::cerr << "\rLUT496   ";
    auto gin496 = 2 * gout492 + gout246;
    auto gout496 = fnand2(gin496, 4);

    std::cerr << "\rLUT497   ";
    auto gin497 = 2 * gout496 + gout495;
    auto gout497 = fnand2(gin497, 4);

    std::cerr << "\rLUT498   ";
    auto gin498 = 2 * gout191 + gout109;
    auto gout498 = fand2(gin498, 4);

    std::cerr << "\rLUT499   ";
    auto gin499 = 2 * gout255 + gout401;
    auto gout499 = fxor2(gin499, 4);

    std::cerr << "\rLUT500   ";
    auto gin500 = 2 * gout195 + gout498;
    auto gout500 = fxnor2(gin500, 4);

    std::cerr << "\rLUT501   ";
    auto gin501 = 2 * gout500 + gout485;
    auto gout501 = fxnor2(gin501, 4);

    std::cerr << "\rLUT502   ";
    auto gin502 = 2 * gout415 + gout501;
    auto gout502 = fxnor2(gin502, 4);

    std::cerr << "\rLUT503   ";
    auto gin503 = 2 * gout482 + gout502;
    auto gout503 = fxnor2(gin503, 4);

    std::cerr << "\rLUT504   ";
    auto gin504 = 2 * gout303 + gout302;
    auto gout504 = fnand2(gin504, 4);

    std::cerr << "\rLUT505   ";
    auto gin505 = 2 * gout37 + gout122;
    auto gout505 = fxor2(gin505, 4);

    std::cerr << "\rLUT506   ";
    auto gin506 = 2 * gout49 + gout505;
    auto gout506 = fxor2(gin506, 4);

    std::cerr << "\rLUT507   ";
    auto gin507 = 2 * gout490 + gout506;
    auto gout507 = fxor2(gin507, 4);

    std::cerr << "\rLUT508   ";
    auto gin508 = 2 * gout269 + gout507;
    auto gout508 = fxor2(gin508, 4);

    std::cerr << "\rLUT509   ";
    auto gin509 = 2 * gout269 + gout507;
    auto gout509 = fnand2(gin509, 4);

    std::cerr << "\rLUT510   ";
    auto gin510 = 2 * gout490 + gout506;
    auto gout510 = fnand2(gin510, 4);

    std::cerr << "\rLUT511   ";
    auto gin511 = 2 * gout510 + gout509;
    auto gout511 = fnand2(gin511, 4);

    std::cerr << "\rLUT512   ";
    auto gin512 = 2 * gout511 + gout366;
    auto gout512 = fxor2(gin512, 4);

    std::cerr << "\rLUT513   ";
    auto gin513 = 2 * gout362 + gout512;
    auto gout513 = fxor2(gin513, 4);

    std::cerr << "\rLUT514   ";
    auto gin514 = 2 * gout362 + gout512;
    auto gout514 = fnand2(gin514, 4);

    std::cerr << "\rLUT515   ";
    auto gin515 = 2 * gout511 + gout366;
    auto gout515 = fnand2(gin515, 4);

    std::cerr << "\rLUT516   ";
    auto gin516 = 2 * gout515 + gout514;
    auto gout516 = fnand2(gin516, 4);

    std::cerr << "\rLUT517   ";
    auto gin517 = 2 * gout49 + gout505;
    auto gout517 = fnand2(gin517, 4);

    std::cerr << "\rLUT518   ";
    auto gin518 = 2 * gout416 + gout517;
    auto gout518 = fnand2(gin518, 4);

    std::cerr << "\rLUT519   ";
    auto gin519 = 2 * gout518 + gout309;
    auto gout519 = fxor2(gin519, 4);

    std::cerr << "\rLUT520   ";
    auto gin520 = 2 * gout518 + gout309;
    auto gout520 = fnand2(gin520, 4);

    std::cerr << "\rLUT521   ";
    auto gin521 = 2 * gout310 + gout520;
    auto gout521 = fand2(gin521, 4);

    std::cerr << "\rLUT522   ";
    auto gin522 = 2 * gout521 + gout475;
    auto gout522 = fxnor2(gin522, 4);

    std::cerr << "\rLUT523   ";
    auto gin523 = 2 * gout522 + gout369;
    auto gout523 = fxnor2(gin523, 4);

    std::cerr << "\rLUT524   ";
    auto gin524 = 2 * gout523 + gout503;
    auto gout524 = fxnor2(gin524, 4);

    std::cerr << "\rLUT525   ";
    auto gin525 = 2 * ct_y1 + ct_x10;
    auto gout525 = fand2(gin525, 4);

    std::cerr << "\rLUT526   ";
    auto gin526 = 2 * gout525 + gout70;
    auto gout526 = fxor2(gin526, 4);

    std::cerr << "\rLUT527   ";
    auto gin527 = 2 * gout417 + gout526;
    auto gout527 = fxnor2(gin527, 4);

    std::cerr << "\rLUT528   ";
    auto gin528 = 2 * gout527 + gout105;
    auto gout528 = fxnor2(gin528, 4);

    std::cerr << "\rLUT529   ";
    auto gin529 = 2 * (1 - gout527) + gout105;
    auto gout529 = fand2(gin529, 4);

    std::cerr << "\rLUT530   ";
    auto gin530 = 2 * gout417 + gout526;
    auto gout530 = fand2(gin530, 4);

    std::cerr << "\rLUT531   ";
    auto gin531 = 2 * gout530 + gout529;
    auto gout531 = for2(gin531, 4);

    std::cerr << "\rLUT532   ";
    auto gin532 = 2 * gout525 + gout70;
    auto gout532 = fnand2(gin532, 4);

    std::cerr << "\rLUT533   ";
    auto gin533 = 2 * gout251 + gout532;
    auto gout533 = fnand2(gin533, 4);

    std::cerr << "\rLUT534   ";
    auto gin534 = 2 * gout533 + gout292;
    auto gout534 = fxnor2(gin534, 4);

    std::cerr << "\rLUT535   ";
    auto gin535 = 2 * gout534 + gout488;
    auto gout535 = fxnor2(gin535, 4);

    std::cerr << "\rLUT536   ";
    auto gin536 = 2 * gout531 + gout535;
    auto gout536 = fxnor2(gin536, 4);

    std::cerr << "\rLUT537   ";
    auto gin537 = 2 * gout536 + gout374;
    auto gout537 = fxnor2(gin537, 4);

    std::cerr << "\rLUT538   ";
    auto gin538 = 2 * (1 - gout536) + gout374;
    auto gout538 = fand2(gin538, 4);

    std::cerr << "\rLUT539   ";
    auto gin539 = 2 * gout531 + gout535;
    auto gout539 = fand2(gin539, 4);

    std::cerr << "\rLUT540   ";
    auto gin540 = 2 * gout539 + gout538;
    auto gout540 = for2(gin540, 4);

    std::cerr << "\rLUT541   ";
    auto gin541 = 2 * (1 - gout534) + gout488;
    auto gout541 = fand2(gin541, 4);

    std::cerr << "\rLUT542   ";
    auto gin542 = 2 * gout533 + gout292;
    auto gout542 = fand2(gin542, 4);

    std::cerr << "\rLUT543   ";
    auto gin543 = 2 * gout542 + gout541;
    auto gout543 = for2(gin543, 4);

    std::cerr << "\rINV544   ";
    long gout544 = 1 - gout325;

    std::cerr << "\rLUT545   ";
    auto gin545 = 2 * gout544 + gout139;
    auto gout545 = fxnor2(gin545, 4);

    std::cerr << "\rLUT546   ";
    auto gin546 = 2 * gout497 + gout545;
    auto gout546 = fxor2(gin546, 4);

    std::cerr << "\rLUT547   ";
    auto gin547 = 2 * gout497 + gout545;
    auto gout547 = fand2(gin547, 4);

    std::cerr << "\rLUT548   ";
    auto gin548 = 2 * gout126 + gout89;
    auto gout548 = fxor2(gin548, 4);

    std::cerr << "\rLUT549   ";
    auto gin549 = 2 * gout1 + gout548;
    auto gout549 = fxor2(gin549, 4);

    std::cerr << "\rLUT550   ";
    auto gin550 = 2 * gout504 + gout549;
    auto gout550 = fxnor2(gin550, 4);

    std::cerr << "\rLUT551   ";
    auto gin551 = 2 * gout504 + gout549;
    auto gout551 = fand2(gin551, 4);

    std::cerr << "\rLUT552   ";
    auto gin552 = 2 * gout1 + gout548;
    auto gout552 = fnand2(gin552, 4);

    std::cerr << "\rLUT553   ";
    auto gin553 = 2 * gout418 + gout552;
    auto gout553 = fnand2(gin553, 4);

    std::cerr << "\rLUT554   ";
    auto gin554 = 2 * gout553 + gout171;
    auto gout554 = fxnor2(gin554, 4);

    std::cerr << "\rLUT555   ";
    auto gin555 = 2 * gout554 + gout85;
    auto gout555 = fxnor2(gin555, 4);

    std::cerr << "\rLUT556   ";
    auto gin556 = 2 * (1 - gout554) + gout85;
    auto gout556 = fand2(gin556, 4);

    std::cerr << "\rLUT557   ";
    auto gin557 = 2 * gout553 + gout171;
    auto gout557 = fand2(gin557, 4);

    std::cerr << "\rLUT558   ";
    auto gin558 = 2 * gout557 + gout556;
    auto gout558 = for2(gin558, 4);

    std::cerr << "\rLUT559   ";
    auto gin559 = 2 * gout558 + gout528;
    auto gout559 = fxnor2(gin559, 4);

    std::cerr << "\rLUT560   ";
    auto gin560 = 2 * gout559 + gout441;
    auto gout560 = fxnor2(gin560, 4);

    std::cerr << "\rLUT561   ";
    auto gin561 = 2 * (1 - gout559) + gout441;
    auto gout561 = fand2(gin561, 4);

    std::cerr << "\rLUT562   ";
    auto gin562 = 2 * gout558 + gout528;
    auto gout562 = fand2(gin562, 4);

    std::cerr << "\rLUT563   ";
    auto gin563 = 2 * gout562 + gout561;
    auto gout563 = for2(gin563, 4);

    std::cerr << "\rLUT564   ";
    auto gin564 = 2 * gout563 + gout537;
    auto gout564 = fxnor2(gin564, 4);

    std::cerr << "\rLUT565   ";
    auto gin565 = 2 * gout564 + gout446;
    auto gout565 = fxnor2(gin565, 4);

    std::cerr << "\rLUT566   ";
    auto gin566 = 2 * (1 - gout564) + gout446;
    auto gout566 = fand2(gin566, 4);

    std::cerr << "\rLUT567   ";
    auto gin567 = 2 * gout563 + gout537;
    auto gout567 = fand2(gin567, 4);

    std::cerr << "\rLUT568   ";
    auto gin568 = 2 * gout567 + gout566;
    auto gout568 = for2(gin568, 4);

    std::cerr << "\rLUT569   ";
    auto gin569 = 2 * gout301 + gout300;
    auto gout569 = for2(gin569, 4);

    std::cerr << "\rLUT570   ";
    auto gin570 = 2 * ct_y8 + ct_x0;
    auto gout570 = fand2(gin570, 4);

    std::cerr << "\rLUT571   ";
    auto gin571 = 2 * gout570 + gout91;
    auto gout571 = fxor2(gin571, 4);

    std::cerr << "\rLUT572   ";
    auto gin572 = 2 * gout469 + gout571;
    auto gout572 = fxor2(gin572, 4);

    std::cerr << "\rLUT573   ";
    auto gin573 = 2 * gout121 + gout572;
    auto gout573 = fxor2(gin573, 4);

    std::cerr << "\rLUT574   ";
    auto gin574 = 2 * gout466 + gout573;
    auto gout574 = fxnor2(gin574, 4);

    std::cerr << "\rLUT575   ";
    auto gin575 = 2 * gout463 + gout574;
    auto gout575 = fxor2(gin575, 4);

    std::cerr << "\rLUT576   ";
    auto gin576 = 2 * gout393 + gout575;
    auto gout576 = fxor2(gin576, 4);

    std::cerr << "\rLUT577   ";
    auto gin577 = 2 * gout460 + gout576;
    auto gout577 = fxor2(gin577, 4);

    std::cerr << "\rLUT578   ";
    auto gin578 = 2 * gout460 + gout576;
    auto gout578 = fand2(gin578, 4);

    std::cerr << "\rLUT579   ";
    auto gin579 = 2 * gout393 + gout575;
    auto gout579 = fnand2(gin579, 4);

    std::cerr << "\rLUT580   ";
    auto gin580 = 2 * gout463 + gout574;
    auto gout580 = fnand2(gin580, 4);

    std::cerr << "\rLUT581   ";
    auto gin581 = 2 * gout580 + gout579;
    auto gout581 = fnand2(gin581, 4);

    std::cerr << "\rLUT582   ";
    auto gin582 = 2 * (1 - gout466) + gout573;
    auto gout582 = fand2(gin582, 4);

    std::cerr << "\rLUT583   ";
    auto gin583 = 2 * gout467 + gout582;
    auto gout583 = for2(gin583, 4);

    std::cerr << "\rLUT584   ";
    auto gin584 = 2 * gout121 + gout572;
    auto gout584 = fnand2(gin584, 4);

    std::cerr << "\rLUT585   ";
    auto gin585 = 2 * gout469 + gout571;
    auto gout585 = fnand2(gin585, 4);

    std::cerr << "\rLUT586   ";
    auto gin586 = 2 * gout585 + gout584;
    auto gout586 = fnand2(gin586, 4);

    std::cerr << "\rLUT587   ";
    auto gin587 = 2 * gout586 + gout110;
    auto gout587 = fxor2(gin587, 4);

    std::cerr << "\rLUT588   ";
    auto gin588 = 2 * gout586 + gout110;
    auto gout588 = fand2(gin588, 4);

    std::cerr << "\rLUT589   ";
    auto gin589 = 2 * gout570 + gout91;
    auto gout589 = fnand2(gin589, 4);

    std::cerr << "\rLUT590   ";
    auto gin590 = 2 * gout92 + gout589;
    auto gout590 = fnand2(gin590, 4);

    std::cerr << "\rLUT591   ";
    auto gin591 = 2 * gout590 + gout499;
    auto gout591 = fxor2(gin591, 4);

    std::cerr << "\rLUT592   ";
    auto gin592 = 2 * gout590 + gout499;
    auto gout592 = fnand2(gin592, 4);

    std::cerr << "\rLUT593   ";
    auto gin593 = 2 * gout402 + gout592;
    auto gout593 = fnand2(gin593, 4);

    std::cerr << "\rLUT594   ";
    auto gin594 = 2 * gout593 + gout74;
    auto gout594 = fxor2(gin594, 4);

    std::cerr << "\rLUT595   ";
    auto gin595 = 2 * gout593 + gout74;
    auto gout595 = fand2(gin595, 4);

    std::cerr << "\rLUT596   ";
    auto gin596 = 2 * gout405 + gout159;
    auto gout596 = fxnor2(gin596, 4);

    std::cerr << "\rLUT597   ";
    auto gin597 = 2 * gout438 + gout596;
    auto gout597 = fxor2(gin597, 4);

    std::cerr << "\rLUT598   ";
    auto gin598 = 2 * gout201 + gout597;
    auto gout598 = fxnor2(gin598, 4);

    std::cerr << "\rLUT599   ";
    auto gin599 = 2 * gout598 + gout435;
    auto gout599 = fxor2(gin599, 4);

    std::cerr << "\rLUT600   ";
    auto gin600 = 2 * gout433 + gout599;
    auto gout600 = fxnor2(gin600, 4);

    std::cerr << "\rLUT601   ";
    auto gin601 = 2 * gout433 + gout599;
    auto gout601 = fnand2(gin601, 4);

    std::cerr << "\rINV602   ";
    long gout602 = 1 - gout601;

    std::cerr << "\rLUT603   ";
    auto gin603 = 2 * gout432 + gout598;
    auto gout603 = fand2(gin603, 4);

    std::cerr << "\rINV604   ";
    long gout604 = 1 - gout603;

    std::cerr << "\rLUT605   ";
    auto gin605 = 2 * gout434 + gout598;
    auto gout605 = fand2(gin605, 4);

    std::cerr << "\rINV606   ";
    long gout606 = 1 - gout605;

    std::cerr << "\rLUT607   ";
    auto gin607 = 2 * gout200 + gout597;
    auto gout607 = fnand2(gin607, 4);

    std::cerr << "\rLUT608   ";
    auto gin608 = 2 * gout438 + gout596;
    auto gout608 = fnand2(gin608, 4);

    std::cerr << "\rLUT609   ";
    auto gin609 = 2 * gout608 + gout607;
    auto gout609 = fnand2(gin609, 4);

    std::cerr << "\rLUT610   ";
    auto gin610 = 2 * gout609 + gout423;
    auto gout610 = fxnor2(gin610, 4);

    std::cerr << "\rLUT611   ";
    auto gin611 = 2 * gout606 + gout610;
    auto gout611 = fxnor2(gin611, 4);

    std::cerr << "\rLUT612   ";
    auto gin612 = 2 * gout604 + gout611;
    auto gout612 = fxnor2(gin612, 4);

    std::cerr << "\rLUT613   ";
    auto gin613 = 2 * gout602 + gout612;
    auto gout613 = fxnor2(gin613, 4);

    std::cerr << "\rLUT614   ";
    auto gin614 = 2 * gout602 + gout612;
    auto gout614 = fnand2(gin614, 4);

    std::cerr << "\rLUT615   ";
    auto gin615 = 2 * gout603 + gout611;
    auto gout615 = fnand2(gin615, 4);

    std::cerr << "\rLUT616   ";
    auto gin616 = 2 * gout615 + gout614;
    auto gout616 = fnand2(gin616, 4);

    std::cerr << "\rLUT617   ";
    auto gin617 = 2 * gout605 + gout610;
    auto gout617 = fand2(gin617, 4);

    std::cerr << "\rINV618   ";
    long gout618 = 1 - gout617;

    std::cerr << "\rLUT619   ";
    auto gin619 = 2 * gout609 + gout422;
    auto gout619 = fand2(gin619, 4);

    std::cerr << "\rLUT620   ";
    auto gin620 = 2 * gout619 + gout457;
    auto gout620 = fand2(gin620, 4);

    std::cerr << "\rLUT621   ";
    auto gin621 = 2 * gout620 + gout577;
    auto gout621 = fand2(gin621, 4);

    std::cerr << "\rINV622   ";
    long gout622 = 1 - gout620;

    std::cerr << "\rINV623   ";
    long gout623 = 1 - gout619;

    std::cerr << "\rLUT624   ";
    auto gin624 = 2 * gout623 + gout457;
    auto gout624 = fxnor2(gin624, 4);

    std::cerr << "\rLUT625   ";
    auto gin625 = 2 * gout618 + gout624;
    auto gout625 = fxnor2(gin625, 4);

    std::cerr << "\rLUT626   ";
    auto gin626 = 2 * gout625 + gout616;
    auto gout626 = fxnor2(gin626, 4);

    std::cerr << "\rLUT627   ";
    auto gin627 = 2 * gout625 + gout616;
    auto gout627 = fand2(gin627, 4);

    std::cerr << "\rLUT628   ";
    auto gin628 = 2 * gout617 + gout624;
    auto gout628 = fnand2(gin628, 4);

    std::cerr << "\rLUT629   ";
    auto gin629 = 2 * gout628 + (1 - gout577);
    auto gout629 = for2(gin629, 4);

    std::cerr << "\rLUT630   ";
    auto gin630 = 2 * gout622 + gout628;
    auto gout630 = fand2(gin630, 4);

    std::cerr << "\rLUT631   ";
    auto gin631 = 2 * gout577 + gout630;
    auto gout631 = fxnor2(gin631, 4);

    std::cerr << "\rLUT632   ";
    auto gin632 = 2 * gout627 + gout631;
    auto gout632 = fxnor2(gin632, 4);

    std::cerr << "\rLUT633   ";
    auto gin633 = 2 * gout627 + gout631;
    auto gout633 = fnand2(gin633, 4);

    std::cerr << "\rLUT634   ";
    auto gin634 = 2 * gout633 + gout629;
    auto gout634 = fand2(gin634, 4);

    std::cerr << "\rLUT635   ";
    auto gin635 = 2 * gout202 + gout352;
    auto gout635 = fand2(gin635, 4);

    std::cerr << "\rIMUX636  ";
    long gin636A = 2 * gout264 + gout635;
    long gout636A = fand2(gin636A, 4);
    long gin636B = 2 * gout349 + (1 - gout635);
    long gout636B = fand2(gin636B, 4);
    long gout636 = gout636A + gout636B;

    std::cerr << "\rLUT637   ";
    auto gin637 = 2 * gout353 + gout636;
    auto gout637 = fnand2(gin637, 4);

    std::cerr << "\rLUT638   ";
    auto gin638 = 2 * gout635 + gout276;
    auto gout638 = fnand2(gin638, 4);

    std::cerr << "\rLUT639   ";
    auto gin639 = 2 * gout353 + gout638;
    auto gout639 = fand2(gin639, 4);

    std::cerr << "\rLUT640   ";
    auto gin640 = 2 * gout635 + gout58;
    auto gout640 = fnand2(gin640, 4);

    std::cerr << "\rINV641   ";
    long gout641 = 1 - gout635;

    std::cerr << "\rLUT642   ";
    auto gin642 = 2 * gout641 + gout345;
    auto gout642 = fnand2(gin642, 4);

    std::cerr << "\rLUT643   ";
    auto gin643 = 2 * gout642 + gout639;
    auto gout643 = fnand2(gin643, 4);

    std::cerr << "\rINV644   ";
    long gout644 = 1 - ct_y3;

    std::cerr << "\rLUT645   ";
    auto gin645 = 2 * gout644 + gout224;
    auto gout645 = fand2(gin645, 4);

    std::cerr << "\rLUT646   ";
    auto gin646 = 2 * gout57 + gout645;
    auto gout646 = fand2(gin646, 4);

    std::cerr << "\rLUT647   ";
    auto gin647 = 2 * gout132 + gout646;
    auto gout647 = fand2(gin647, 4);

    std::cerr << "\rLUT648   ";
    auto gin648 = 2 * gout222 + gout647;
    auto gout648 = fand2(gin648, 4);

    std::cerr << "\rLUT649   ";
    auto gin649 = 2 * gout31 + gout648;
    auto gout649 = fand2(gin649, 4);

    std::cerr << "\rLUT650   ";
    auto gin650 = 2 * gout94 + gout649;
    auto gout650 = fand2(gin650, 4);

    std::cerr << "\rLUT651   ";
    auto gin651 = 2 * gout76 + gout650;
    auto gout651 = fand2(gin651, 4);

    std::cerr << "\rLUT652   ";
    auto gin652 = 2 * gout128 + gout651;
    auto gout652 = fnand2(gin652, 4);

    std::cerr << "\rLUT653   ";
    auto gin653 = 2 * gout332 + gout652;
    auto gout653 = fand2(gin653, 4);

    std::cerr << "\rLUT654   ";
    auto gin654 = 2 * (1 - gout653) + gout336;
    auto gout654 = fand2(gin654, 4);

    std::cerr << "\rLUT655   ";
    auto gin655 = 2 * gout654 + gout335;
    auto gout655 = fnand2(gin655, 4);

    std::cerr << "\rLUT656   ";
    auto gin656 = 2 * gout655 + gout334;
    auto gout656 = for2(gin656, 4);

    std::cerr << "\rLUT657   ";
    auto gin657 = 2 * gout656 + gout333;
    auto gout657 = for2(gin657, 4);

    std::cerr << "\rLUT658   ";
    auto gin658 = 2 * gout657 + gout52;
    auto gout658 = fxnor2(gin658, 4);

    std::cerr << "\rLUT659   ";
    auto gin659 = 2 * gout329 + gout656;
    auto gout659 = fxnor2(gin659, 4);

    std::cerr << "\rLUT660   ";
    auto gin660 = 2 * gout129 + gout659;
    auto gout660 = fxnor2(gin660, 4);

    std::cerr << "\rLUT661   ";
    auto gin661 = 2 * ct_x14 + gout659;
    auto gout661 = fnand2(gin661, 4);

    std::cerr << "\rLUT662   ";
    auto gin662 = 2 * ct_y13 + gout655;
    auto gout662 = fxnor2(gin662, 4);

    std::cerr << "\rLUT663   ";
    auto gin663 = 2 * ct_x13 + gout662;
    auto gout663 = fxnor2(gin663, 4);

    std::cerr << "\rINV664   ";
    long gout664 = 1 - gout663;

    std::cerr << "\rLUT665   ";
    auto gin665 = 2 * gout75 + gout662;
    auto gout665 = fnand2(gin665, 4);

    std::cerr << "\rLUT666   ";
    auto gin666 = 2 * gout75 + gout662;
    auto gout666 = for2(gin666, 4);

    std::cerr << "\rLUT667   ";
    auto gin667 = 2 * ct_y12 + gout654;
    auto gout667 = fxnor2(gin667, 4);

    std::cerr << "\rLUT668   ";
    auto gin668 = 2 * gout30 + gout667;
    auto gout668 = fxnor2(gin668, 4);

    std::cerr << "\rLUT669   ";
    auto gin669 = 2 * ct_x12 + gout667;
    auto gout669 = fnand2(gin669, 4);

    std::cerr << "\rLUT670   ";
    auto gin670 = 2 * gout669 + gout666;
    auto gout670 = fnand2(gin670, 4);

    std::cerr << "\rLUT671   ";
    auto gin671 = 2 * gout665 + gout670;
    auto gout671 = fnand2(gin671, 4);

    std::cerr << "\rLUT672   ";
    auto gin672 = 2 * ct_y11 + gout653;
    auto gout672 = fxnor2(gin672, 4);

    std::cerr << "\rLUT673   ";
    auto gin673 = 2 * ct_x11 + gout672;
    auto gout673 = fxnor2(gin673, 4);

    std::cerr << "\rINV674   ";
    long gout674 = 1 - gout673;

    std::cerr << "\rLUT675   ";
    auto gin675 = 2 * gout203 + gout672;
    auto gout675 = fnand2(gin675, 4);

    std::cerr << "\rLUT676   ";
    auto gin676 = 2 * gout203 + gout672;
    auto gout676 = for2(gin676, 4);

    std::cerr << "\rLUT677   ";
    auto gin677 = 2 * (1 - gout651) + gout332;
    auto gout677 = fand2(gin677, 4);

    std::cerr << "\rLUT678   ";
    auto gin678 = 2 * gout128 + gout677;
    auto gout678 = fxnor2(gin678, 4);

    std::cerr << "\rLUT679   ";
    auto gin679 = 2 * gout29 + gout678;
    auto gout679 = fxnor2(gin679, 4);

    std::cerr << "\rLUT680   ";
    auto gin680 = 2 * ct_x10 + gout678;
    auto gout680 = fnand2(gin680, 4);

    std::cerr << "\rLUT681   ";
    auto gin681 = 2 * gout680 + gout676;
    auto gout681 = fnand2(gin681, 4);

    std::cerr << "\rLUT682   ";
    auto gin682 = 2 * gout675 + gout681;
    auto gout682 = fnand2(gin682, 4);

    std::cerr << "\rLUT683   ";
    auto gin683 = 2 * (1 - gout650) + gout332;
    auto gout683 = fand2(gin683, 4);

    std::cerr << "\rLUT684   ";
    auto gin684 = 2 * gout76 + gout683;
    auto gout684 = fxnor2(gin684, 4);

    std::cerr << "\rLUT685   ";
    auto gin685 = 2 * gout72 + gout684;
    auto gout685 = fxnor2(gin685, 4);

    std::cerr << "\rINV686   ";
    long gout686 = 1 - gout685;

    std::cerr << "\rLUT687   ";
    auto gin687 = 2 * ct_x9 + gout684;
    auto gout687 = for2(gin687, 4);

    std::cerr << "\rLUT688   ";
    auto gin688 = 2 * ct_x9 + gout684;
    auto gout688 = fnand2(gin688, 4);

    std::cerr << "\rLUT689   ";
    auto gin689 = 2 * (1 - gout649) + gout332;
    auto gout689 = fand2(gin689, 4);

    std::cerr << "\rLUT690   ";
    auto gin690 = 2 * gout94 + gout689;
    auto gout690 = fxnor2(gin690, 4);

    std::cerr << "\rLUT691   ";
    auto gin691 = 2 * gout28 + gout690;
    auto gout691 = fxnor2(gin691, 4);

    std::cerr << "\rLUT692   ";
    auto gin692 = 2 * ct_x8 + gout690;
    auto gout692 = fnand2(gin692, 4);

    std::cerr << "\rLUT693   ";
    auto gin693 = 2 * gout692 + gout688;
    auto gout693 = fnand2(gin693, 4);

    std::cerr << "\rLUT694   ";
    auto gin694 = 2 * gout687 + gout693;
    auto gout694 = fnand2(gin694, 4);

    std::cerr << "\rLUT695   ";
    auto gin695 = 2 * (1 - gout648) + gout332;
    auto gout695 = fand2(gin695, 4);

    std::cerr << "\rLUT696   ";
    auto gin696 = 2 * gout31 + gout695;
    auto gout696 = fxnor2(gin696, 4);

    std::cerr << "\rLUT697   ";
    auto gin697 = 2 * gout355 + gout696;
    auto gout697 = fxnor2(gin697, 4);

    std::cerr << "\rLUT698   ";
    auto gin698 = 2 * ct_x7 + gout696;
    auto gout698 = fnand2(gin698, 4);

    std::cerr << "\rLUT699   ";
    auto gin699 = 2 * (1 - gout647) + gout332;
    auto gout699 = fand2(gin699, 4);

    std::cerr << "\rLUT700   ";
    auto gin700 = 2 * gout222 + gout699;
    auto gout700 = fxnor2(gin700, 4);

    std::cerr << "\rLUT701   ";
    auto gin701 = 2 * gout131 + gout700;
    auto gout701 = fxnor2(gin701, 4);

    std::cerr << "\rLUT702   ";
    auto gin702 = 2 * ct_x6 + gout700;
    auto gout702 = fnand2(gin702, 4);

    std::cerr << "\rLUT703   ";
    auto gin703 = 2 * (1 - gout646) + gout332;
    auto gout703 = fand2(gin703, 4);

    std::cerr << "\rLUT704   ";
    auto gin704 = 2 * gout132 + gout703;
    auto gout704 = fxnor2(gin704, 4);

    std::cerr << "\rLUT705   ";
    auto gin705 = 2 * gout80 + gout704;
    auto gout705 = fxnor2(gin705, 4);

    std::cerr << "\rLUT706   ";
    auto gin706 = 2 * ct_x5 + gout704;
    auto gout706 = fnand2(gin706, 4);

    std::cerr << "\rLUT707   ";
    auto gin707 = 2 * (1 - gout645) + gout332;
    auto gout707 = fand2(gin707, 4);

    std::cerr << "\rLUT708   ";
    auto gin708 = 2 * gout57 + gout707;
    auto gout708 = fxnor2(gin708, 4);

    std::cerr << "\rLUT709   ";
    auto gin709 = 2 * gout27 + gout708;
    auto gout709 = fxnor2(gin709, 4);

    std::cerr << "\rLUT710   ";
    auto gin710 = 2 * ct_x4 + gout708;
    auto gout710 = fnand2(gin710, 4);

    std::cerr << "\rLUT711   ";
    auto gin711 = 2 * gout644 + gout337;
    auto gout711 = fxnor2(gin711, 4);

    std::cerr << "\rLUT712   ";
    auto gin712 = 2 * gout204 + gout711;
    auto gout712 = fxnor2(gin712, 4);

    std::cerr << "\rLUT713   ";
    auto gin713 = 2 * gout351 + gout712;
    auto gout713 = fxnor2(gin713, 4);

    std::cerr << "\rIMUX714  ";
    long gin714A = 2 * gout412 + gout635;
    long gout714A = fand2(gin714A, 4);
    long gin714B = 2 * gout713 + (1 - gout635);
    long gout714B = fand2(gin714B, 4);
    long gout714 = gout714A + gout714B;

    std::cerr << "\rLUT715   ";
    auto gin715 = 2 * gout353 + gout714;
    auto gout715 = fnand2(gin715, 4);

    std::cerr << "\rLUT716   ";
    auto gin716 = 2 * gout351 + gout712;
    auto gout716 = fnand2(gin716, 4);

    std::cerr << "\rLUT717   ";
    auto gin717 = 2 * ct_x3 + gout711;
    auto gout717 = fnand2(gin717, 4);

    std::cerr << "\rLUT718   ";
    auto gin718 = 2 * gout717 + gout716;
    auto gout718 = fnand2(gin718, 4);

    std::cerr << "\rLUT719   ";
    auto gin719 = 2 * gout718 + gout709;
    auto gout719 = fxnor2(gin719, 4);

    std::cerr << "\rIMUX720  ";
    long gin720A = 2 * gout719 + gout641;
    long gout720A = fand2(gin720A, 4);
    long gin720B = 2 * gout431 + (1 - gout641);
    long gout720B = fand2(gin720B, 4);
    long gout720 = gout720A + gout720B;

    std::cerr << "\rLUT721   ";
    auto gin721 = 2 * gout353 + gout720;
    auto gout721 = fnand2(gin721, 4);

    std::cerr << "\rLUT722   ";
    auto gin722 = 2 * gout718 + gout709;
    auto gout722 = fnand2(gin722, 4);

    std::cerr << "\rLUT723   ";
    auto gin723 = 2 * gout710 + gout722;
    auto gout723 = fnand2(gin723, 4);

    std::cerr << "\rLUT724   ";
    auto gin724 = 2 * gout723 + gout705;
    auto gout724 = fxnor2(gin724, 4);

    std::cerr << "\rIMUX725  ";
    long gin725A = 2 * gout600 + gout635;
    long gout725A = fand2(gin725A, 4);
    long gin725B = 2 * gout724 + (1 - gout635);
    long gout725B = fand2(gin725B, 4);
    long gout725 = gout725A + gout725B;

    std::cerr << "\rLUT726   ";
    auto gin726 = 2 * gout353 + gout725;
    auto gout726 = fnand2(gin726, 4);

    std::cerr << "\rLUT727   ";
    auto gin727 = 2 * gout723 + gout705;
    auto gout727 = fnand2(gin727, 4);

    std::cerr << "\rLUT728   ";
    auto gin728 = 2 * gout706 + gout727;
    auto gout728 = fnand2(gin728, 4);

    std::cerr << "\rLUT729   ";
    auto gin729 = 2 * gout728 + gout701;
    auto gout729 = fxnor2(gin729, 4);

    std::cerr << "\rIMUX730  ";
    long gin730A = 2 * gout613 + gout635;
    long gout730A = fand2(gin730A, 4);
    long gin730B = 2 * gout729 + (1 - gout635);
    long gout730B = fand2(gin730B, 4);
    long gout730 = gout730A + gout730B;

    std::cerr << "\rLUT731   ";
    auto gin731 = 2 * gout353 + gout730;
    auto gout731 = fnand2(gin731, 4);

    std::cerr << "\rLUT732   ";
    auto gin732 = 2 * gout728 + gout701;
    auto gout732 = fnand2(gin732, 4);

    std::cerr << "\rLUT733   ";
    auto gin733 = 2 * gout702 + gout732;
    auto gout733 = fnand2(gin733, 4);

    std::cerr << "\rLUT734   ";
    auto gin734 = 2 * gout733 + gout697;
    auto gout734 = fxnor2(gin734, 4);

    std::cerr << "\rIMUX735  ";
    long gin735A = 2 * gout626 + gout635;
    long gout735A = fand2(gin735A, 4);
    long gin735B = 2 * gout734 + (1 - gout635);
    long gout735B = fand2(gin735B, 4);
    long gout735 = gout735A + gout735B;

    std::cerr << "\rLUT736   ";
    auto gin736 = 2 * gout353 + gout735;
    auto gout736 = fnand2(gin736, 4);

    std::cerr << "\rLUT737   ";
    auto gin737 = 2 * gout733 + gout697;
    auto gout737 = fnand2(gin737, 4);

    std::cerr << "\rLUT738   ";
    auto gin738 = 2 * gout698 + gout737;
    auto gout738 = fnand2(gin738, 4);

    std::cerr << "\rLUT739   ";
    auto gin739 = 2 * gout738 + gout691;
    auto gout739 = fxnor2(gin739, 4);

    std::cerr << "\rIMUX740  ";
    long gin740A = 2 * gout632 + gout635;
    long gout740A = fand2(gin740A, 4);
    long gin740B = 2 * gout739 + (1 - gout635);
    long gout740B = fand2(gin740B, 4);
    long gout740 = gout740A + gout740B;

    std::cerr << "\rLUT741   ";
    auto gin741 = 2 * gout353 + gout740;
    auto gout741 = fnand2(gin741, 4);

    std::cerr << "\rLUT742   ";
    auto gin742 = 2 * gout738 + gout691;
    auto gout742 = fnand2(gin742, 4);

    std::cerr << "\rLUT743   ";
    auto gin743 = 2 * gout742 + gout686;
    auto gout743 = for2(gin743, 4);

    std::cerr << "\rLUT744   ";
    auto gin744 = 2 * gout743 + gout694;
    auto gout744 = fnand2(gin744, 4);

    std::cerr << "\rLUT745   ";
    auto gin745 = 2 * gout744 + gout679;
    auto gout745 = fxnor2(gin745, 4);

    std::cerr << "\rLUT746   ";
    auto gin746 = 2 * gout744 + gout679;
    auto gout746 = fnand2(gin746, 4);

    std::cerr << "\rLUT747   ";
    auto gin747 = 2 * gout746 + gout674;
    auto gout747 = for2(gin747, 4);

    std::cerr << "\rLUT748   ";
    auto gin748 = 2 * gout747 + gout682;
    auto gout748 = fnand2(gin748, 4);

    std::cerr << "\rLUT749   ";
    auto gin749 = 2 * gout748 + gout668;
    auto gout749 = fxnor2(gin749, 4);

    std::cerr << "\rLUT750   ";
    auto gin750 = 2 * gout748 + gout668;
    auto gout750 = fnand2(gin750, 4);

    std::cerr << "\rLUT751   ";
    auto gin751 = 2 * gout750 + gout664;
    auto gout751 = for2(gin751, 4);

    std::cerr << "\rLUT752   ";
    auto gin752 = 2 * gout751 + gout671;
    auto gout752 = fnand2(gin752, 4);

    std::cerr << "\rLUT753   ";
    auto gin753 = 2 * gout752 + gout660;
    auto gout753 = fxnor2(gin753, 4);

    std::cerr << "\rLUT754   ";
    auto gin754 = 2 * gout752 + gout660;
    auto gout754 = fnand2(gin754, 4);

    std::cerr << "\rLUT755   ";
    auto gin755 = 2 * gout661 + gout754;
    auto gout755 = fand2(gin755, 4);

    std::cerr << "\rLUT756   ";
    auto gin756 = 2 * gout755 + gout658;
    auto gout756 = for2(gin756, 4);

    std::cerr << "\rLUT757   ";
    auto gin757 = 2 * gout641 + gout756;
    auto gout757 = fand2(gin757, 4);

    std::cerr << "\rLUT758   ";
    auto gin758 = 2 * gout755 + gout658;
    auto gout758 = fnand2(gin758, 4);

    std::cerr << "\rLUT759   ";
    auto gin759 = 2 * gout758 + gout757;
    auto gout759 = fnand2(gin759, 4);

    std::cerr << "\rLUT760   ";
    auto gin760 = 2 * gout353 + gout759;
    auto gout760 = fand2(gin760, 4);

    std::cerr << "\rLUT761   ";
    auto gin761 = 2 * gout669 + gout750;
    auto gout761 = fnand2(gin761, 4);

    std::cerr << "\rLUT762   ";
    auto gin762 = 2 * gout761 + gout663;
    auto gout762 = for2(gin762, 4);

    std::cerr << "\rLUT763   ";
    auto gin763 = 2 * gout641 + gout762;
    auto gout763 = fand2(gin763, 4);

    std::cerr << "\rLUT764   ";
    auto gin764 = 2 * gout761 + gout663;
    auto gout764 = fnand2(gin764, 4);

    std::cerr << "\rLUT765   ";
    auto gin765 = 2 * gout764 + gout763;
    auto gout765 = fnand2(gin765, 4);

    std::cerr << "\rLUT766   ";
    auto gin766 = 2 * gout680 + gout746;
    auto gout766 = fnand2(gin766, 4);

    std::cerr << "\rLUT767   ";
    auto gin767 = 2 * gout766 + gout673;
    auto gout767 = for2(gin767, 4);

    std::cerr << "\rLUT768   ";
    auto gin768 = 2 * gout641 + gout767;
    auto gout768 = fand2(gin768, 4);

    std::cerr << "\rLUT769   ";
    auto gin769 = 2 * gout766 + gout673;
    auto gout769 = fnand2(gin769, 4);

    std::cerr << "\rLUT770   ";
    auto gin770 = 2 * gout769 + gout768;
    auto gout770 = fnand2(gin770, 4);

    std::cerr << "\rLUT771   ";
    auto gin771 = 2 * gout692 + gout742;
    auto gout771 = fnand2(gin771, 4);

    std::cerr << "\rLUT772   ";
    auto gin772 = 2 * gout771 + gout685;
    auto gout772 = for2(gin772, 4);

    std::cerr << "\rLUT773   ";
    auto gin773 = 2 * gout641 + gout772;
    auto gout773 = fand2(gin773, 4);

    std::cerr << "\rLUT774   ";
    auto gin774 = 2 * gout771 + gout685;
    auto gout774 = fnand2(gin774, 4);

    std::cerr << "\rLUT775   ";
    auto gin775 = 2 * gout130 + gout188;
    auto gout775 = fxnor2(gin775, 4);

    std::cerr << "\rLUT776   ";
    auto gin776 = 2 * gout315 + gout775;
    auto gout776 = fxnor2(gin776, 4);

    std::cerr << "\rLUT777   ";
    auto gin777 = 2 * gout516 + gout776;
    auto gout777 = fxnor2(gin777, 4);

    std::cerr << "\rLUT778   ";
    auto gin778 = 2 * gout294 + gout164;
    auto gout778 = fxnor2(gin778, 4);

    std::cerr << "\rLUT779   ";
    auto gin779 = 2 * gout778 + gout243;
    auto gout779 = fxnor2(gin779, 4);

    std::cerr << "\rLUT780   ";
    auto gin780 = 2 * gout543 + gout779;
    auto gout780 = fxnor2(gin780, 4);

    std::cerr << "\rLUT781   ";
    auto gin781 = 2 * gout780 + gout508;
    auto gout781 = fxnor2(gin781, 4);

    std::cerr << "\rLUT782   ";
    auto gin782 = 2 * gout540 + gout781;
    auto gout782 = fxnor2(gin782, 4);

    std::cerr << "\rLUT783   ";
    auto gin783 = 2 * gout782 + gout378;
    auto gout783 = fxnor2(gin783, 4);

    std::cerr << "\rLUT784   ";
    auto gin784 = 2 * gout568 + gout783;
    auto gout784 = fxor2(gin784, 4);

    std::cerr << "\rLUT785   ";
    auto gin785 = 2 * gout449 + gout784;
    auto gout785 = fxor2(gin785, 4);

    std::cerr << "\rLUT786   ";
    auto gin786 = 2 * gout449 + gout784;
    auto gout786 = fnand2(gin786, 4);

    std::cerr << "\rLUT787   ";
    auto gin787 = 2 * gout568 + gout783;
    auto gout787 = fnand2(gin787, 4);

    std::cerr << "\rLUT788   ";
    auto gin788 = 2 * gout787 + gout786;
    auto gout788 = fnand2(gin788, 4);

    std::cerr << "\rLUT789   ";
    auto gin789 = 2 * (1 - gout782) + gout378;
    auto gout789 = fand2(gin789, 4);

    std::cerr << "\rLUT790   ";
    auto gin790 = 2 * gout540 + gout781;
    auto gout790 = fand2(gin790, 4);

    std::cerr << "\rLUT791   ";
    auto gin791 = 2 * gout790 + gout789;
    auto gout791 = for2(gin791, 4);

    std::cerr << "\rLUT792   ";
    auto gin792 = 2 * (1 - gout780) + gout508;
    auto gout792 = fand2(gin792, 4);

    std::cerr << "\rLUT793   ";
    auto gin793 = 2 * gout543 + gout779;
    auto gout793 = fand2(gin793, 4);

    std::cerr << "\rLUT794   ";
    auto gin794 = 2 * gout793 + gout792;
    auto gout794 = for2(gin794, 4);

    std::cerr << "\rLUT795   ";
    auto gin795 = 2 * (1 - gout778) + gout243;
    auto gout795 = fand2(gin795, 4);

    std::cerr << "\rLUT796   ";
    auto gin796 = 2 * gout486 + gout795;
    auto gout796 = for2(gin796, 4);

    std::cerr << "\rLUT797   ";
    auto gin797 = 2 * gout796 + gout479;
    auto gout797 = fxnor2(gin797, 4);

    std::cerr << "\rLUT798   ";
    auto gin798 = 2 * gout797 + gout519;
    auto gout798 = fxnor2(gin798, 4);

    std::cerr << "\rLUT799   ";
    auto gin799 = 2 * gout794 + gout798;
    auto gout799 = fxnor2(gin799, 4);

    std::cerr << "\rLUT800   ";
    auto gin800 = 2 * gout799 + gout513;
    auto gout800 = fxnor2(gin800, 4);

    std::cerr << "\rLUT801   ";
    auto gin801 = 2 * gout791 + gout800;
    auto gout801 = fxnor2(gin801, 4);

    std::cerr << "\rLUT802   ";
    auto gin802 = 2 * gout801 + gout382;
    auto gout802 = fxnor2(gin802, 4);

    std::cerr << "\rLUT803   ";
    auto gin803 = 2 * gout788 + gout802;
    auto gout803 = fxor2(gin803, 4);

    std::cerr << "\rLUT804   ";
    auto gin804 = 2 * gout788 + gout802;
    auto gout804 = fand2(gin804, 4);

    std::cerr << "\rLUT805   ";
    auto gin805 = 2 * gout383 + gout804;
    auto gout805 = fxnor2(gin805, 4);

    std::cerr << "\rLUT806   ";
    auto gin806 = 2 * (1 - gout801) + gout382;
    auto gout806 = fand2(gin806, 4);

    std::cerr << "\rLUT807   ";
    auto gin807 = 2 * gout791 + gout800;
    auto gout807 = fnand2(gin807, 4);

    std::cerr << "\rLUT808   ";
    auto gin808 = 2 * gout807 + (1 - gout806);
    auto gout808 = fand2(gin808, 4);

    std::cerr << "\rLUT809   ";
    auto gin809 = 2 * (1 - gout799) + gout513;
    auto gout809 = fand2(gin809, 4);

    std::cerr << "\rLUT810   ";
    auto gin810 = 2 * gout794 + gout798;
    auto gout810 = fand2(gin810, 4);

    std::cerr << "\rLUT811   ";
    auto gin811 = 2 * gout810 + gout809;
    auto gout811 = for2(gin811, 4);

    std::cerr << "\rLUT812   ";
    auto gin812 = 2 * (1 - gout797) + gout519;
    auto gout812 = fand2(gin812, 4);

    std::cerr << "\rLUT813   ";
    auto gin813 = 2 * gout796 + gout479;
    auto gout813 = fand2(gin813, 4);

    std::cerr << "\rLUT814   ";
    auto gin814 = 2 * gout813 + gout812;
    auto gout814 = for2(gin814, 4);

    std::cerr << "\rLUT815   ";
    auto gin815 = 2 * gout814 + gout524;
    auto gout815 = fxnor2(gin815, 4);

    std::cerr << "\rLUT816   ";
    auto gin816 = 2 * gout777 + gout815;
    auto gout816 = fxnor2(gin816, 4);

    std::cerr << "\rLUT817   ";
    auto gin817 = 2 * gout811 + gout816;
    auto gout817 = fxnor2(gin817, 4);

    std::cerr << "\rLUT818   ";
    auto gin818 = 2 * gout808 + gout817;
    auto gout818 = fxnor2(gin818, 4);

    std::cerr << "\rLUT819   ";
    auto gin819 = 2 * gout818 + gout805;
    auto gout819 = fxnor2(gin819, 4);

    std::cerr << "\rLUT820   ";
    auto gin820 = 2 * gout774 + gout773;
    auto gout820 = fnand2(gin820, 4);

    std::cerr << "\rLUT821   ";
    auto gin821 = 2 * gout207 + gout280;
    auto gout821 = fxor2(gin821, 4);

    std::cerr << "\rLUT822   ";
    auto gin822 = 2 * gout550 + gout821;
    auto gout822 = fxnor2(gin822, 4);

    std::cerr << "\rLUT823   ";
    auto gin823 = 2 * gout569 + gout822;
    auto gout823 = fxnor2(gin823, 4);

    std::cerr << "\rLUT824   ";
    auto gin824 = 2 * gout823 + gout591;
    auto gout824 = fxnor2(gin824, 4);

    std::cerr << "\rLUT825   ";
    auto gin825 = 2 * gout583 + gout824;
    auto gout825 = fxnor2(gin825, 4);

    std::cerr << "\rLUT826   ";
    auto gin826 = 2 * gout825 + gout587;
    auto gout826 = fxnor2(gin826, 4);

    std::cerr << "\rLUT827   ";
    auto gin827 = 2 * gout581 + gout826;
    auto gout827 = fxor2(gin827, 4);

    std::cerr << "\rLUT828   ";
    auto gin828 = 2 * gout578 + gout827;
    auto gout828 = fxor2(gin828, 4);

    std::cerr << "\rLUT829   ";
    auto gin829 = 2 * gout621 + gout828;
    auto gout829 = fxnor2(gin829, 4);

    std::cerr << "\rLUT830   ";
    auto gin830 = 2 * gout634 + gout829;
    auto gout830 = for2(gin830, 4);

    std::cerr << "\rLUT831   ";
    auto gin831 = 2 * gout635 + gout830;
    auto gout831 = fand2(gin831, 4);

    std::cerr << "\rLUT832   ";
    auto gin832 = 2 * gout634 + gout829;
    auto gout832 = fnand2(gin832, 4);

    std::cerr << "\rLUT833   ";
    auto gin833 = 2 * gout832 + gout831;
    auto gout833 = fnand2(gin833, 4);

    std::cerr << "\rLUT834   ";
    auto gin834 = 2 * gout353 + gout833;
    auto gout834 = fand2(gin834, 4);

    std::cerr << "\rLUT835   ";
    auto gin835 = 2 * gout820 + gout834;
    auto gout835 = fnand2(gin835, 4);

    std::cerr << "\rLUT836   ";
    auto gin836 = 2 * gout621 + gout828;
    auto gout836 = fnand2(gin836, 4);

    std::cerr << "\rLUT837   ";
    auto gin837 = 2 * gout836 + gout830;
    auto gout837 = fnand2(gin837, 4);

    std::cerr << "\rLUT838   ";
    auto gin838 = 2 * gout578 + gout827;
    auto gout838 = fand2(gin838, 4);

    std::cerr << "\rLUT839   ";
    auto gin839 = 2 * gout581 + gout826;
    auto gout839 = fand2(gin839, 4);

    std::cerr << "\rINV840   ";
    long gout840 = 1 - gout839;

    std::cerr << "\rLUT841   ";
    auto gin841 = 2 * (1 - gout825) + gout587;
    auto gout841 = fand2(gin841, 4);

    std::cerr << "\rLUT842   ";
    auto gin842 = 2 * gout583 + gout824;
    auto gout842 = fand2(gin842, 4);

    std::cerr << "\rLUT843   ";
    auto gin843 = 2 * gout842 + gout841;
    auto gout843 = for2(gin843, 4);

    std::cerr << "\rLUT844   ";
    auto gin844 = 2 * (1 - gout823) + gout591;
    auto gout844 = fand2(gin844, 4);

    std::cerr << "\rLUT845   ";
    auto gin845 = 2 * gout569 + gout822;
    auto gout845 = fand2(gin845, 4);

    std::cerr << "\rLUT846   ";
    auto gin846 = 2 * gout845 + gout844;
    auto gout846 = for2(gin846, 4);

    std::cerr << "\rLUT847   ";
    auto gin847 = 2 * (1 - gout550) + gout821;
    auto gout847 = fand2(gin847, 4);

    std::cerr << "\rLUT848   ";
    auto gin848 = 2 * gout551 + gout847;
    auto gout848 = for2(gin848, 4);

    std::cerr << "\rLUT849   ";
    auto gin849 = 2 * gout848 + gout555;
    auto gout849 = fxnor2(gin849, 4);

    std::cerr << "\rLUT850   ";
    auto gin850 = 2 * gout849 + gout494;
    auto gout850 = fxnor2(gin850, 4);

    std::cerr << "\rLUT851   ";
    auto gin851 = 2 * gout846 + gout850;
    auto gout851 = fxnor2(gin851, 4);

    std::cerr << "\rLUT852   ";
    auto gin852 = 2 * gout851 + gout594;
    auto gout852 = fxnor2(gin852, 4);

    std::cerr << "\rLUT853   ";
    auto gin853 = 2 * gout843 + gout852;
    auto gout853 = fxor2(gin853, 4);

    std::cerr << "\rLUT854   ";
    auto gin854 = 2 * gout588 + gout853;
    auto gout854 = fxor2(gin854, 4);

    std::cerr << "\rLUT855   ";
    auto gin855 = 2 * gout840 + gout854;
    auto gout855 = fxnor2(gin855, 4);

    std::cerr << "\rLUT856   ";
    auto gin856 = 2 * gout838 + gout855;
    auto gout856 = fxor2(gin856, 4);

    std::cerr << "\rLUT857   ";
    auto gin857 = 2 * gout837 + gout856;
    auto gout857 = fxnor2(gin857, 4);

    std::cerr << "\rIMUX858  ";
    long gin858A = 2 * gout857 + gout635;
    long gout858A = fand2(gin858A, 4);
    long gin858B = 2 * gout745 + (1 - gout635);
    long gout858B = fand2(gin858B, 4);
    long gout858 = gout858A + gout858B;

    std::cerr << "\rLUT859   ";
    auto gin859 = 2 * gout353 + gout858;
    auto gout859 = fnand2(gin859, 4);

    std::cerr << "\rLUT860   ";
    auto gin860 = 2 * gout837 + gout856;
    auto gout860 = fnand2(gin860, 4);

    std::cerr << "\rLUT861   ";
    auto gin861 = 2 * gout838 + gout855;
    auto gout861 = fnand2(gin861, 4);

    std::cerr << "\rLUT862   ";
    auto gin862 = 2 * gout861 + gout860;
    auto gout862 = fnand2(gin862, 4);

    std::cerr << "\rLUT863   ";
    auto gin863 = 2 * gout839 + gout854;
    auto gout863 = fand2(gin863, 4);

    std::cerr << "\rINV864   ";
    long gout864 = 1 - gout863;

    std::cerr << "\rLUT865   ";
    auto gin865 = 2 * gout588 + gout853;
    auto gout865 = fnand2(gin865, 4);

    std::cerr << "\rLUT866   ";
    auto gin866 = 2 * gout843 + gout852;
    auto gout866 = fnand2(gin866, 4);

    std::cerr << "\rLUT867   ";
    auto gin867 = 2 * gout866 + gout865;
    auto gout867 = fnand2(gin867, 4);

    std::cerr << "\rLUT868   ";
    auto gin868 = 2 * (1 - gout851) + gout594;
    auto gout868 = fand2(gin868, 4);

    std::cerr << "\rLUT869   ";
    auto gin869 = 2 * gout846 + gout850;
    auto gout869 = fand2(gin869, 4);

    std::cerr << "\rLUT870   ";
    auto gin870 = 2 * gout869 + gout868;
    auto gout870 = for2(gin870, 4);

    std::cerr << "\rLUT871   ";
    auto gin871 = 2 * (1 - gout849) + gout494;
    auto gout871 = fand2(gin871, 4);

    std::cerr << "\rLUT872   ";
    auto gin872 = 2 * gout848 + gout555;
    auto gout872 = fand2(gin872, 4);

    std::cerr << "\rLUT873   ";
    auto gin873 = 2 * gout872 + gout871;
    auto gout873 = for2(gin873, 4);

    std::cerr << "\rLUT874   ";
    auto gin874 = 2 * gout873 + gout560;
    auto gout874 = fxnor2(gin874, 4);

    std::cerr << "\rLUT875   ";
    auto gin875 = 2 * gout874 + gout546;
    auto gout875 = fxnor2(gin875, 4);

    std::cerr << "\rLUT876   ";
    auto gin876 = 2 * gout870 + gout875;
    auto gout876 = fxor2(gin876, 4);

    std::cerr << "\rLUT877   ";
    auto gin877 = 2 * gout595 + gout876;
    auto gout877 = fxor2(gin877, 4);

    std::cerr << "\rLUT878   ";
    auto gin878 = 2 * gout867 + gout877;
    auto gout878 = fxor2(gin878, 4);

    std::cerr << "\rLUT879   ";
    auto gin879 = 2 * gout864 + gout878;
    auto gout879 = fxnor2(gin879, 4);

    std::cerr << "\rLUT880   ";
    auto gin880 = 2 * gout862 + gout879;
    auto gout880 = for2(gin880, 4);

    std::cerr << "\rLUT881   ";
    auto gin881 = 2 * gout635 + gout880;
    auto gout881 = fand2(gin881, 4);

    std::cerr << "\rLUT882   ";
    auto gin882 = 2 * gout862 + gout879;
    auto gout882 = fnand2(gin882, 4);

    std::cerr << "\rLUT883   ";
    auto gin883 = 2 * gout882 + gout881;
    auto gout883 = fnand2(gin883, 4);

    std::cerr << "\rLUT884   ";
    auto gin884 = 2 * gout353 + gout883;
    auto gout884 = fand2(gin884, 4);

    std::cerr << "\rLUT885   ";
    auto gin885 = 2 * gout770 + gout884;
    auto gout885 = fnand2(gin885, 4);

    std::cerr << "\rLUT886   ";
    auto gin886 = 2 * gout863 + gout878;
    auto gout886 = fnand2(gin886, 4);

    std::cerr << "\rLUT887   ";
    auto gin887 = 2 * gout886 + gout882;
    auto gout887 = fnand2(gin887, 4);

    std::cerr << "\rLUT888   ";
    auto gin888 = 2 * gout867 + gout877;
    auto gout888 = fand2(gin888, 4);

    std::cerr << "\rLUT889   ";
    auto gin889 = 2 * gout595 + gout876;
    auto gout889 = fnand2(gin889, 4);

    std::cerr << "\rLUT890   ";
    auto gin890 = 2 * gout870 + gout875;
    auto gout890 = fnand2(gin890, 4);

    std::cerr << "\rLUT891   ";
    auto gin891 = 2 * gout890 + gout889;
    auto gout891 = fnand2(gin891, 4);

    std::cerr << "\rLUT892   ";
    auto gin892 = 2 * (1 - gout874) + gout546;
    auto gout892 = fand2(gin892, 4);

    std::cerr << "\rLUT893   ";
    auto gin893 = 2 * gout873 + gout560;
    auto gout893 = fand2(gin893, 4);

    std::cerr << "\rLUT894   ";
    auto gin894 = 2 * gout893 + gout892;
    auto gout894 = for2(gin894, 4);

    std::cerr << "\rLUT895   ";
    auto gin895 = 2 * gout894 + gout565;
    auto gout895 = fxor2(gin895, 4);

    std::cerr << "\rLUT896   ";
    auto gin896 = 2 * gout547 + gout895;
    auto gout896 = fxor2(gin896, 4);

    std::cerr << "\rLUT897   ";
    auto gin897 = 2 * gout891 + gout896;
    auto gout897 = fxor2(gin897, 4);

    std::cerr << "\rLUT898   ";
    auto gin898 = 2 * gout888 + gout897;
    auto gout898 = fxor2(gin898, 4);

    std::cerr << "\rLUT899   ";
    auto gin899 = 2 * gout887 + gout898;
    auto gout899 = fxnor2(gin899, 4);

    std::cerr << "\rIMUX900  ";
    long gin900A = 2 * gout899 + gout635;
    long gout900A = fand2(gin900A, 4);
    long gin900B = 2 * gout749 + (1 - gout635);
    long gout900B = fand2(gin900B, 4);
    long gout900 = gout900A + gout900B;

    std::cerr << "\rLUT901   ";
    auto gin901 = 2 * gout353 + gout900;
    auto gout901 = fnand2(gin901, 4);

    std::cerr << "\rLUT902   ";
    auto gin902 = 2 * gout887 + gout898;
    auto gout902 = fnand2(gin902, 4);

    std::cerr << "\rLUT903   ";
    auto gin903 = 2 * gout888 + gout897;
    auto gout903 = fnand2(gin903, 4);

    std::cerr << "\rLUT904   ";
    auto gin904 = 2 * gout903 + gout902;
    auto gout904 = fnand2(gin904, 4);

    std::cerr << "\rLUT905   ";
    auto gin905 = 2 * gout891 + gout896;
    auto gout905 = fand2(gin905, 4);

    std::cerr << "\rLUT906   ";
    auto gin906 = 2 * gout547 + gout895;
    auto gout906 = fnand2(gin906, 4);

    std::cerr << "\rLUT907   ";
    auto gin907 = 2 * gout894 + gout565;
    auto gout907 = fnand2(gin907, 4);

    std::cerr << "\rLUT908   ";
    auto gin908 = 2 * gout907 + gout906;
    auto gout908 = fnand2(gin908, 4);

    std::cerr << "\rLUT909   ";
    auto gin909 = 2 * gout908 + gout785;
    auto gout909 = fxor2(gin909, 4);

    std::cerr << "\rLUT910   ";
    auto gin910 = 2 * gout905 + gout909;
    auto gout910 = fxor2(gin910, 4);

    std::cerr << "\rLUT911   ";
    auto gin911 = 2 * gout904 + gout910;
    auto gout911 = for2(gin911, 4);

    std::cerr << "\rLUT912   ";
    auto gin912 = 2 * gout635 + gout911;
    auto gout912 = fand2(gin912, 4);

    std::cerr << "\rLUT913   ";
    auto gin913 = 2 * gout904 + gout910;
    auto gout913 = fnand2(gin913, 4);

    std::cerr << "\rLUT914   ";
    auto gin914 = 2 * gout913 + gout912;
    auto gout914 = fnand2(gin914, 4);

    std::cerr << "\rLUT915   ";
    auto gin915 = 2 * gout353 + gout914;
    auto gout915 = fand2(gin915, 4);

    std::cerr << "\rLUT916   ";
    auto gin916 = 2 * gout765 + gout915;
    auto gout916 = fnand2(gin916, 4);

    std::cerr << "\rLUT917   ";
    auto gin917 = 2 * gout905 + gout909;
    auto gout917 = fnand2(gin917, 4);

    std::cerr << "\rLUT918   ";
    auto gin918 = 2 * gout917 + gout913;
    auto gout918 = fnand2(gin918, 4);

    std::cerr << "\rLUT919   ";
    auto gin919 = 2 * gout908 + gout785;
    auto gout919 = fand2(gin919, 4);

    std::cerr << "\rLUT920   ";
    auto gin920 = 2 * gout919 + gout803;
    auto gout920 = fxor2(gin920, 4);

    std::cerr << "\rLUT921   ";
    auto gin921 = 2 * gout918 + gout920;
    auto gout921 = fxnor2(gin921, 4);

    std::cerr << "\rIMUX922  ";
    long gin922A = 2 * gout921 + gout635;
    long gout922A = fand2(gin922A, 4);
    long gin922B = 2 * gout753 + (1 - gout635);
    long gout922B = fand2(gin922B, 4);
    long gout922 = gout922A + gout922B;

    std::cerr << "\rLUT923   ";
    auto gin923 = 2 * gout353 + gout922;
    auto gout923 = fnand2(gin923, 4);

    std::cerr << "\rLUT924   ";
    auto gin924 = 2 * gout918 + gout920;
    auto gout924 = fnand2(gin924, 4);

    std::cerr << "\rLUT925   ";
    auto gin925 = 2 * gout919 + gout803;
    auto gout925 = fnand2(gin925, 4);

    std::cerr << "\rLUT926   ";
    auto gin926 = 2 * gout925 + gout924;
    auto gout926 = fand2(gin926, 4);

    std::cerr << "\rLUT927   ";
    auto gin927 = 2 * gout926 + gout819;
    auto gout927 = for2(gin927, 4);

    std::cerr << "\rLUT928   ";
    auto gin928 = 2 * gout635 + gout927;
    auto gout928 = fand2(gin928, 4);

    std::cerr << "\rLUT929   ";
    auto gin929 = 2 * gout926 + gout819;
    auto gout929 = fnand2(gin929, 4);

    std::cerr << "\rLUT930   ";
    auto gin930 = 2 * gout929 + gout928;
    auto gout930 = fnand2(gin930, 4);

    std::cerr << "\rLUT931   ";
    auto gin931 = 2 * gout930 + gout760;
    auto gout931 = fnand2(gin931, 4);

    std::cerr << "\rLUT932   ";
    auto gin932 = 2 * gout635 + gout256;
    auto gout932 = for2(gin932, 4);

    std::cerr << "\rLUT933   ";
    auto gin933 = 2 * gout353 + gout932;
    auto gout933 = fand2(gin933, 4);

    std::cerr << "\rLUT934   ";
    auto gin934 = 2 * gout640 + gout933;
    auto gout934 = fnand2(gin934, 4);

    std::cerr << "\r          \r";
    std::vector<long> out;
    out.push_back(gout934); /* out0 */
    out.push_back(gout643); /* out1 */
    out.push_back(gout637); /* out2 */
    out.push_back(gout715); /* out3 */
    out.push_back(gout721); /* out4 */
    out.push_back(gout726); /* out5 */
    out.push_back(gout731); /* out6 */
    out.push_back(gout736); /* out7 */
    out.push_back(gout741); /* out8 */
    out.push_back(gout835); /* out9 */
    out.push_back(gout859); /* out10 */
    out.push_back(gout885); /* out11 */
    out.push_back(gout901); /* out12 */
    out.push_back(gout916); /* out13 */
    out.push_back(gout923); /* out14 */
    out.push_back(gout931); /* out15 */
    return out;
}

std::vector<long>
test_add4_lut3(FHEContext& ctx, uint8_t a, uint8_t b)
{
    long ct_a0 = (a >> 0) & 1;
    long ct_a1 = (a >> 1) & 1;
    long ct_a2 = (a >> 2) & 1;
    long ct_a3 = (a >> 3) & 1;
    long ct_b0 = (b >> 0) & 1;
    long ct_b1 = (b >> 1) & 1;
    long ct_b2 = (b >> 2) & 1;
    long ct_b3 = (b >> 3) & 1;

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


    std::vector<RotationPoly> lut0;
    std::vector<long (*)(long)> flut0;
    auto lut0idx0 = [](long I) -> long {
        /* GATE 8 (LUT2 _26_ INIT 0x6 PERM 01) */
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
    lut0.push_back(ctx.genrate_lut(lut0idx0));
    flut0.push_back(lut0idx0);

    auto lut0idx1 = [](long I) -> long {
        /* GATE 4 (LUT2 _22_ INIT 0x8 PERM 01) */
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
    lut0.push_back(ctx.genrate_lut(lut0idx1));
    flut0.push_back(lut0idx1);

    auto fvec0 = [flut0](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut0[i](I));
        return ret;
    };

    std::cerr << "\rLUT0   ";
    long gin0 = 1 * ct_a0 + 2 * ct_b0;
    std::vector<long> gout0 = fvec0(gin0);

    std::vector<RotationPoly> lut1;
    std::vector<long (*)(long)> flut1;
    auto lut1idx0 = [](long I) -> long {
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
            default: assert(0);
        };
    };
    lut1.push_back(ctx.genrate_lut(lut1idx0));
    flut1.push_back(lut1idx0);

    auto lut1idx1 = [](long I) -> long {
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
            default: assert(0);
        };
    };
    lut1.push_back(ctx.genrate_lut(lut1idx1));
    flut1.push_back(lut1idx1);

    auto fvec1 = [flut1](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut1[i](I));
        return ret;
    };

    std::cerr << "\rLUT1   ";
    long gin1 = 1 * gout0[1] + 2 * ct_a1 + 4 * ct_b1;
    std::vector<long> gout1 = fvec1(gin1);

    std::vector<RotationPoly> lut2;
    std::vector<long (*)(long)> flut2;
    auto lut2idx0 = [](long I) -> long {
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
            default: assert(0);
        };
    };
    lut2.push_back(ctx.genrate_lut(lut2idx0));
    flut2.push_back(lut2idx0);

    auto lut2idx1 = [](long I) -> long {
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
            default: assert(0);
        };
    };
    lut2.push_back(ctx.genrate_lut(lut2idx1));
    flut2.push_back(lut2idx1);

    auto fvec2 = [flut2](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut2[i](I));
        return ret;
    };

    std::cerr << "\rLUT2   ";
    long gin2 = 1 * gout1[0] + 2 * ct_a2 + 4 * ct_b2;
    std::vector<long> gout2 = fvec2(gin2);

    std::vector<RotationPoly> lut3;
    std::vector<long (*)(long)> flut3;
    auto lut3idx0 = [](long I) -> long {
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
            default: assert(0);
        };
    };
    lut3.push_back(ctx.genrate_lut(lut3idx0));
    flut3.push_back(lut3idx0);

    auto lut3idx1 = [](long I) -> long {
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
            default: assert(0);
        };
    };
    lut3.push_back(ctx.genrate_lut(lut3idx1));
    flut3.push_back(lut3idx1);

    auto fvec3 = [flut3](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut3[i](I));
        return ret;
    };

    std::cerr << "\rLUT3   ";
    long gin3 = 1 * gout2[1] + 2 * ct_a3 + 4 * ct_b3;
    std::vector<long> gout3 = fvec3(gin3);

    std::cerr << "\r          \r";
    std::vector<long> out;
    out.push_back(gout0[0]); /* out0 */
    out.push_back(gout1[1]); /* out1 */
    out.push_back(gout2[0]); /* out2 */
    out.push_back(gout3[0]); /* out3 */
    out.push_back(gout3[1]); /* out4 */
    return out;
}
std::vector<long>
test_calculator_lut3(FHEContext& ctx, uint8_t op, uint16_t x, uint16_t y)
{
    long ct_op0 = (op >> 0) & 1;
    long ct_op1 = (op >> 1) & 1;
    long ct_op2 = (op >> 2) & 1;
    long ct_op3 = (op >> 3) & 1;
    long ct_op4 = (op >> 4) & 1;
    long ct_op5 = (op >> 5) & 1;
    long ct_op6 = (op >> 6) & 1;
    long ct_op7 = (op >> 7) & 1;
    long ct_x0 = (x >> 0) & 1;
    long ct_x1 = (x >> 1) & 1;
    long ct_x2 = (x >> 2) & 1;
    long ct_x3 = (x >> 3) & 1;
    long ct_x4 = (x >> 4) & 1;
    long ct_x5 = (x >> 5) & 1;
    long ct_x6 = (x >> 6) & 1;
    long ct_x7 = (x >> 7) & 1;
    long ct_x8 = (x >> 8) & 1;
    long ct_x9 = (x >> 9) & 1;
    long ct_x10 = (x >> 10) & 1;
    long ct_x11 = (x >> 11) & 1;
    long ct_x12 = (x >> 12) & 1;
    long ct_x13 = (x >> 13) & 1;
    long ct_x14 = (x >> 14) & 1;
    long ct_x15 = (x >> 15) & 1;
    long ct_y0 = (y >> 0) & 1;
    long ct_y1 = (y >> 1) & 1;
    long ct_y2 = (y >> 2) & 1;
    long ct_y3 = (y >> 3) & 1;
    long ct_y4 = (y >> 4) & 1;
    long ct_y5 = (y >> 5) & 1;
    long ct_y6 = (y >> 6) & 1;
    long ct_y7 = (y >> 7) & 1;
    long ct_y8 = (y >> 8) & 1;
    long ct_y9 = (y >> 9) & 1;
    long ct_y10 = (y >> 10) & 1;
    long ct_y11 = (y >> 11) & 1;
    long ct_y12 = (y >> 12) & 1;
    long ct_y13 = (y >> 13) & 1;
    long ct_y14 = (y >> 14) & 1;
    long ct_y15 = (y >> 15) & 1;

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


    std::vector<RotationPoly> lut0;
    std::vector<long (*)(long)> flut0;
    auto lut0idx0 = [](long I) -> long {
        /* GATE 440 (LUT2 _1896_ INIT 0x8 PERM 01) */
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
    lut0.push_back(ctx.genrate_lut(lut0idx0));
    flut0.push_back(lut0idx0);

    auto fvec0 = [flut0](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut0[i](I));
        return ret;
    };

    std::cerr << "\rLUT0   ";
    long gin0 = 1 * ct_y14 + 2 * ct_x0;
    std::vector<long> gout0 = fvec0(gin0);

    std::vector<RotationPoly> lut1;
    std::vector<long (*)(long)> flut1;
    auto lut1idx0 = [](long I) -> long {
        /* GATE 390 (LUT2 _1846_ INIT 0x8 PERM 01) */
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
    lut1.push_back(ctx.genrate_lut(lut1idx0));
    flut1.push_back(lut1idx0);

    auto fvec1 = [flut1](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut1[i](I));
        return ret;
    };

    std::cerr << "\rLUT1   ";
    long gin1 = 1 * ct_y11 + 2 * ct_x2;
    std::vector<long> gout1 = fvec1(gin1);

    std::vector<RotationPoly> lut2;
    std::vector<long (*)(long)> flut2;
    auto lut2idx0 = [](long I) -> long {
        /* GATE 81 (LUT2 _1537_ INIT 0x8 PERM 01) */
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
    lut2.push_back(ctx.genrate_lut(lut2idx0));
    flut2.push_back(lut2idx0);

    auto fvec2 = [flut2](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut2[i](I));
        return ret;
    };

    std::cerr << "\rLUT2   ";
    long gin2 = 1 * ct_y4 + 2 * ct_x1;
    std::vector<long> gout2 = fvec2(gin2);

    std::vector<RotationPoly> lut3;
    std::vector<long (*)(long)> flut3;
    auto lut3idx0 = [](long I) -> long {
        /* GATE 41 (LUT2 _1497_ INIT 0x8 PERM 01) */
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
    lut3.push_back(ctx.genrate_lut(lut3idx0));
    flut3.push_back(lut3idx0);

    auto fvec3 = [flut3](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut3[i](I));
        return ret;
    };

    std::cerr << "\rLUT3   ";
    long gin3 = 1 * ct_y2 + 2 * ct_x1;
    std::vector<long> gout3 = fvec3(gin3);

    std::vector<RotationPoly> lut4;
    std::vector<long (*)(long)> flut4;
    auto lut4idx0 = [](long I) -> long {
        /* GATE 462 (LUT2 _1918_ INIT 0x8 PERM 01) */
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
    lut4.push_back(ctx.genrate_lut(lut4idx0));
    flut4.push_back(lut4idx0);

    auto fvec4 = [flut4](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut4[i](I));
        return ret;
    };

    std::cerr << "\rLUT4   ";
    long gin4 = 1 * ct_y12 + 2 * ct_x3;
    std::vector<long> gout4 = fvec4(gin4);

    std::vector<RotationPoly> lut5;
    std::vector<long (*)(long)> flut5;
    auto lut5idx0 = [](long I) -> long {
        /* GATE 381 (LUT2 _1837_ INIT 0x8 PERM 01) */
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
    lut5.push_back(ctx.genrate_lut(lut5idx0));
    flut5.push_back(lut5idx0);

    auto fvec5 = [flut5](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut5[i](I));
        return ret;
    };

    std::cerr << "\rLUT5   ";
    long gin5 = 1 * ct_y8 + 2 * ct_x5;
    std::vector<long> gout5 = fvec5(gin5);

    std::vector<RotationPoly> lut6;
    std::vector<long (*)(long)> flut6;
    auto lut6idx0 = [](long I) -> long {
        /* GATE 415 (LUT2 _1871_ INIT 0x8 PERM 10) */
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
    lut6.push_back(ctx.genrate_lut(lut6idx0));
    flut6.push_back(lut6idx0);

    auto fvec6 = [flut6](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut6[i](I));
        return ret;
    };

    std::cerr << "\rLUT6   ";
    long gin6 = 1 * ct_x13 + 2 * ct_y1;
    std::vector<long> gout6 = fvec6(gin6);

    std::vector<RotationPoly> lut7;
    std::vector<long (*)(long)> flut7;
    auto lut7idx0 = [](long I) -> long {
        /* GATE 163 (LUT2 _1619_ INIT 0x8 PERM 01) */
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
    lut7.push_back(ctx.genrate_lut(lut7idx0));
    flut7.push_back(lut7idx0);

    auto fvec7 = [flut7](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut7[i](I));
        return ret;
    };

    std::cerr << "\rLUT7   ";
    long gin7 = 1 * ct_y2 + 2 * ct_x6;
    std::vector<long> gout7 = fvec7(gin7);

    std::vector<RotationPoly> lut8;
    std::vector<long (*)(long)> flut8;
    auto lut8idx0 = [](long I) -> long {
        /* GATE 373 (LUT2 _1829_ INIT 0x8 PERM 10) */
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
    lut8.push_back(ctx.genrate_lut(lut8idx0));
    flut8.push_back(lut8idx0);

    auto fvec8 = [flut8](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut8[i](I));
        return ret;
    };

    std::cerr << "\rLUT8   ";
    long gin8 = 1 * ct_x9 + 2 * ct_y4;
    std::vector<long> gout8 = fvec8(gin8);

    std::vector<RotationPoly> lut9;
    std::vector<long (*)(long)> flut9;
    auto lut9idx0 = [](long I) -> long {
        /* GATE 290 (LUT2 _1746_ INIT 0x8 PERM 01) */
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
    lut9.push_back(ctx.genrate_lut(lut9idx0));
    flut9.push_back(lut9idx0);

    auto fvec9 = [flut9](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut9[i](I));
        return ret;
    };

    std::cerr << "\rLUT9   ";
    long gin9 = 1 * ct_y7 + 2 * ct_x4;
    std::vector<long> gout9 = fvec9(gin9);

    std::vector<RotationPoly> lut10;
    std::vector<long (*)(long)> flut10;
    auto lut10idx0 = [](long I) -> long {
        /* GATE 426 (LUT2 _1882_ INIT 0x8 PERM 01) */
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
    lut10.push_back(ctx.genrate_lut(lut10idx0));
    flut10.push_back(lut10idx0);

    auto fvec10 = [flut10](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut10[i](I));
        return ret;
    };

    std::cerr << "\rLUT10   ";
    long gin10 = 1 * ct_y7 + 2 * ct_x7;
    std::vector<long> gout10 = fvec10(gin10);

    std::vector<RotationPoly> lut11;
    std::vector<long (*)(long)> flut11;
    auto lut11idx0 = [](long I) -> long {
        /* GATE 460 (LUT2 _1916_ INIT 0x8 PERM 01) */
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
    lut11.push_back(ctx.genrate_lut(lut11idx0));
    flut11.push_back(lut11idx0);

    auto fvec11 = [flut11](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut11[i](I));
        return ret;
    };

    std::cerr << "\rLUT11   ";
    long gin11 = 1 * ct_y9 + 2 * ct_x6;
    std::vector<long> gout11 = fvec11(gin11);

    std::vector<RotationPoly> lut12;
    std::vector<long (*)(long)> flut12;
    auto lut12idx0 = [](long I) -> long {
        /* GATE 370 (LUT2 _1826_ INIT 0x8 PERM 01) */
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
    lut12.push_back(ctx.genrate_lut(lut12idx0));
    flut12.push_back(lut12idx0);

    auto fvec12 = [flut12](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut12[i](I));
        return ret;
    };

    std::cerr << "\rLUT12   ";
    long gin12 = 1 * ct_y2 + 2 * ct_x11;
    std::vector<long> gout12 = fvec12(gin12);

    std::vector<RotationPoly> lut13;
    std::vector<long (*)(long)> flut13;
    auto lut13idx0 = [](long I) -> long {
        /* GATE 205 (LUT2 _1661_ INIT 0x8 PERM 01) */
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
    lut13.push_back(ctx.genrate_lut(lut13idx0));
    flut13.push_back(lut13idx0);

    auto fvec13 = [flut13](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut13[i](I));
        return ret;
    };

    std::cerr << "\rLUT13   ";
    long gin13 = 1 * ct_y5 + 2 * ct_x4;
    std::vector<long> gout13 = fvec13(gin13);

    std::vector<RotationPoly> lut14;
    std::vector<long (*)(long)> flut14;
    auto lut14idx0 = [](long I) -> long {
        /* GATE 173 (LUT2 _1629_ INIT 0x8 PERM 01) */
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
    lut14.push_back(ctx.genrate_lut(lut14idx0));
    flut14.push_back(lut14idx0);

    auto fvec14 = [flut14](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut14[i](I));
        return ret;
    };

    std::cerr << "\rLUT14   ";
    long gin14 = 1 * ct_y7 + 2 * ct_x1;
    std::vector<long> gout14 = fvec14(gin14);

    std::vector<RotationPoly> lut15;
    std::vector<long (*)(long)> flut15;
    auto lut15idx0 = [](long I) -> long {
        /* GATE 300 (LUT2 _1756_ INIT 0x8 PERM 01) */
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
    lut15.push_back(ctx.genrate_lut(lut15idx0));
    flut15.push_back(lut15idx0);

    auto fvec15 = [flut15](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut15[i](I));
        return ret;
    };

    std::cerr << "\rLUT15   ";
    long gin15 = 1 * ct_y9 + 2 * ct_x2;
    std::vector<long> gout15 = fvec15(gin15);

    std::vector<RotationPoly> lut16;
    std::vector<long (*)(long)> flut16;
    auto lut16idx0 = [](long I) -> long {
        /* GATE 28 (LUT2 _1484_ INIT 0x8 PERM 10) */
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
    long gin16 = 1 * ct_x2 + 2 * ct_y0;
    std::vector<long> gout16 = fvec16(gin16);

    std::vector<RotationPoly> lut17;
    std::vector<long (*)(long)> flut17;
    auto lut17idx0 = [](long I) -> long {
        /* GATE 439 (LUT2 _1895_ INIT 0x8 PERM 01) */
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
    long gin17 = 1 * ct_y13 + 2 * ct_x1;
    std::vector<long> gout17 = fvec17(gin17);

    std::vector<RotationPoly> lut18;
    std::vector<long (*)(long)> flut18;
    auto lut18idx0 = [](long I) -> long {
        /* GATE 389 (LUT2 _1845_ INIT 0x8 PERM 10) */
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
    long gin18 = 1 * ct_x3 + 2 * ct_y10;
    std::vector<long> gout18 = fvec18(gin18);

    std::vector<RotationPoly> lut19;
    std::vector<long (*)(long)> flut19;
    auto lut19idx0 = [](long I) -> long {
        /* GATE 40 (LUT2 _1496_ INIT 0x8 PERM 01) */
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
    long gin19 = 1 * ct_y1 + 2 * ct_x2;
    std::vector<long> gout19 = fvec19(gin19);

    std::vector<RotationPoly> lut20;
    std::vector<long (*)(long)> flut20;
    auto lut20idx0 = [](long I) -> long {
        /* GATE 382 (LUT2 _1838_ INIT 0x8 PERM 01) */
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
    lut20.push_back(ctx.genrate_lut(lut20idx0));
    flut20.push_back(lut20idx0);

    auto fvec20 = [flut20](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut20[i](I));
        return ret;
    };

    std::cerr << "\rLUT20   ";
    long gin20 = 1 * ct_y6 + 2 * ct_x7;
    std::vector<long> gout20 = fvec20(gin20);

    std::vector<RotationPoly> lut21;
    std::vector<long (*)(long)> flut21;
    auto lut21idx0 = [](long I) -> long {
        /* GATE 371 (LUT2 _1827_ INIT 0x8 PERM 10) */
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
    lut21.push_back(ctx.genrate_lut(lut21idx0));
    flut21.push_back(lut21idx0);

    auto fvec21 = [flut21](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut21[i](I));
        return ret;
    };

    std::cerr << "\rLUT21   ";
    long gin21 = 1 * ct_x13 + 2 * ct_y0;
    std::vector<long> gout21 = fvec21(gin21);

    std::vector<RotationPoly> lut22;
    std::vector<long (*)(long)> flut22;
    auto lut22idx0 = [](long I) -> long {
        /* GATE 162 (LUT2 _1618_ INIT 0x8 PERM 01) */
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
    long gin22 = 1 * ct_y1 + 2 * ct_x7;
    std::vector<long> gout22 = fvec22(gin22);

    std::vector<RotationPoly> lut23;
    std::vector<long (*)(long)> flut23;
    auto lut23idx0 = [](long I) -> long {
        /* GATE 79 (LUT2 _1535_ INIT 0x8 PERM 01) */
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
    long gin23 = 1 * ct_y0 + 2 * ct_x5;
    std::vector<long> gout23 = fvec23(gin23);

    std::vector<RotationPoly> lut24;
    std::vector<long (*)(long)> flut24;
    auto lut24idx0 = [](long I) -> long {
        /* GATE 243 (LUT2 _1699_ INIT 0x8 PERM 01) */
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
    long gin24 = 1 * ct_y3 + 2 * ct_x7;
    std::vector<long> gout24 = fvec24(gin24);

    std::vector<RotationPoly> lut25;
    std::vector<long (*)(long)> flut25;
    auto lut25idx0 = [](long I) -> long {
        /* GATE 479 (LUT2 _1935_ INIT 0x8 PERM 01) */
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
    long gin25 = 1 * ct_y14 + 2 * ct_x1;
    std::vector<long> gout25 = fvec25(gin25);

    std::vector<RotationPoly> lut26;
    std::vector<long (*)(long)> flut26;
    auto lut26idx0 = [](long I) -> long {
        /* GATE 299 (LUT2 _1755_ INIT 0x8 PERM 01) */
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
    long gin26 = 1 * ct_y11 + 2 * ct_x0;
    std::vector<long> gout26 = fvec26(gin26);

    std::vector<RotationPoly> lut27;
    std::vector<long (*)(long)> flut27;
    auto lut27idx0 = [](long I) -> long {
        /* GATE 175 (LUT2 _1631_ INIT 0x8 PERM 01) */
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
    long gin27 = 1 * ct_y6 + 2 * ct_x2;
    std::vector<long> gout27 = fvec27(gin27);

    std::vector<RotationPoly> lut28;
    std::vector<long (*)(long)> flut28;
    auto lut28idx0 = [](long I) -> long {
        /* GATE 61 (LUT2 _1517_ INIT 0x8 PERM 01) */
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
    long gin28 = 1 * ct_y3 + 2 * ct_x1;
    std::vector<long> gout28 = fvec28(gin28);

    std::vector<RotationPoly> lut29;
    std::vector<long (*)(long)> flut29;
    auto lut29idx0 = [](long I) -> long {
        /* GATE 204 (LUT2 _1660_ INIT 0x8 PERM 01) */
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
    long gin29 = 1 * ct_y4 + 2 * ct_x5;
    std::vector<long> gout29 = fvec29(gin29);

    std::vector<RotationPoly> lut30;
    std::vector<long (*)(long)> flut30;
    auto lut30idx0 = [](long I) -> long {
        /* GATE 369 (LUT2 _1825_ INIT 0x8 PERM 01) */
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
    lut30.push_back(ctx.genrate_lut(lut30idx0));
    flut30.push_back(lut30idx0);

    auto fvec30 = [flut30](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut30[i](I));
        return ret;
    };

    std::cerr << "\rLUT30   ";
    long gin30 = 1 * ct_y1 + 2 * ct_x12;
    std::vector<long> gout30 = fvec30(gin30);

    std::vector<RotationPoly> lut31;
    std::vector<long (*)(long)> flut31;
    auto lut31idx0 = [](long I) -> long {
        /* GATE 27 (LUT2 _1483_ INIT 0x8 PERM 01) */
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
    long gin31 = 1 * ct_y2 + 2 * ct_x0;
    std::vector<long> gout31 = fvec31(gin31);

    std::vector<RotationPoly> lut32;
    std::vector<long (*)(long)> flut32;
    auto lut32idx0 = [](long I) -> long {
        /* GATE 201 (LUT2 _1657_ INIT 0x8 PERM 01) */
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
    long gin32 = 1 * ct_y2 + 2 * ct_x7;
    std::vector<long> gout32 = fvec32(gin32);

    std::vector<RotationPoly> lut33;
    std::vector<long (*)(long)> flut33;
    auto lut33idx0 = [](long I) -> long {
        /* GATE 391 (LUT2 _1847_ INIT 0x8 PERM 10) */
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
    long gin33 = 1 * ct_x4 + 2 * ct_y9;
    std::vector<long> gout33 = fvec33(gin33);

    std::vector<RotationPoly> lut34;
    std::vector<long (*)(long)> flut34;
    auto lut34idx0 = [](long I) -> long {
        /* GATE 329 (LUT2 _1785_ INIT 0x8 PERM 10) */
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
    long gin34 = 1 * ct_x9 + 2 * ct_y3;
    std::vector<long> gout34 = fvec34(gin34);

    std::vector<RotationPoly> lut35;
    std::vector<long (*)(long)> flut35;
    auto lut35idx0 = [](long I) -> long {
        /* GATE 174 (LUT2 _1630_ INIT 0x8 PERM 01) */
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
    long gin35 = 1 * ct_y8 + 2 * ct_x0;
    std::vector<long> gout35 = fvec35(gin35);

    std::vector<RotationPoly> lut36;
    std::vector<long (*)(long)> flut36;
    auto lut36idx0 = [](long I) -> long {
        /* GATE 172 (LUT3 _1628_ INIT 0x96 PERM 012) */
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
    lut36.push_back(ctx.genrate_lut(lut36idx0));
    flut36.push_back(lut36idx0);

    auto lut36idx1 = [](long I) -> long {
        /* GATE 208 (LUT3 _1664_ INIT 0x17 PERM 012) */
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
    lut36.push_back(ctx.genrate_lut(lut36idx1));
    flut36.push_back(lut36idx1);

    auto fvec36 = [flut36](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut36[i](I));
        return ret;
    };

    std::cerr << "\rLUT36   ";
    long gin36 = 1 * gout14[0] + 2 * gout35[0] + 4 * gout27[0];
    std::vector<long> gout36 = fvec36(gin36);

    std::vector<RotationPoly> lut37;
    std::vector<long (*)(long)> flut37;
    auto lut37idx0 = [](long I) -> long {
        /* GATE 34 (LUT3 _1490_ INIT 0x1 PERM 102) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
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
    long gin37 = 1 * ct_y2 + 2 * ct_y1 + 4 * ct_y0;
    std::vector<long> gout37 = fvec37(gin37);

    std::vector<RotationPoly> lut38;
    std::vector<long (*)(long)> flut38;
    auto lut38idx0 = [](long I) -> long {
        /* GATE 67 (LUT3 _1523_ INIT 0x10 PERM 120) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
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
    long gin38 = 1 * gout37[0] + 2 * ct_y3 + 4 * ct_y4;
    std::vector<long> gout38 = fvec38(gin38);

    std::vector<RotationPoly> lut39;
    std::vector<long (*)(long)> flut39;
    auto lut39idx0 = [](long I) -> long {
        /* GATE 388 (LUT3 _1844_ INIT 0x96 PERM 012) */
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
    lut39.push_back(ctx.genrate_lut(lut39idx0));
    flut39.push_back(lut39idx0);

    auto lut39idx1 = [](long I) -> long {
        /* GATE 433 (LUT3 _1889_ INIT 0x17 PERM 012) */
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
    lut39.push_back(ctx.genrate_lut(lut39idx1));
    flut39.push_back(lut39idx1);

    auto fvec39 = [flut39](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut39[i](I));
        return ret;
    };

    std::cerr << "\rLUT39   ";
    long gin39 = 1 * gout18[0] + 2 * gout1[0] + 4 * gout33[0];
    std::vector<long> gout39 = fvec39(gin39);

    std::vector<RotationPoly> lut40;
    std::vector<long (*)(long)> flut40;
    auto lut40idx0 = [](long I) -> long {
        /* GATE 131 (LUT2 _1587_ INIT 0x8 PERM 01) */
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
    long gin40 = 1 * ct_y2 + 2 * ct_x5;
    std::vector<long> gout40 = fvec40(gin40);

    std::vector<RotationPoly> lut41;
    std::vector<long (*)(long)> flut41;
    auto lut41idx0 = [](long I) -> long {
        /* GATE 393 (LUT2 _1849_ INIT 0x8 PERM 01) */
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
    long gin41 = 1 * ct_y12 + 2 * ct_x1;
    std::vector<long> gout41 = fvec41(gin41);

    std::vector<RotationPoly> lut42;
    std::vector<long (*)(long)> flut42;
    auto lut42idx0 = [](long I) -> long {
        /* GATE 392 (LUT3 _1848_ INIT 0x78 PERM 120) */
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
    lut42.push_back(ctx.genrate_lut(lut42idx0));
    flut42.push_back(lut42idx0);

    auto fvec42 = [flut42](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut42[i](I));
        return ret;
    };

    std::cerr << "\rLUT42   ";
    long gin42 = 1 * gout41[0] + 2 * ct_y13 + 4 * ct_x0;
    std::vector<long> gout42 = fvec42(gin42);

    std::vector<RotationPoly> lut43;
    std::vector<long (*)(long)> flut43;
    auto lut43idx0 = [](long I) -> long {
        /* GATE 25 (LUT2 _1481_ INIT 0x8 PERM 01) */
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
    long gin43 = 1 * ct_y1 + 2 * ct_x1;
    std::vector<long> gout43 = fvec43(gin43);

    std::vector<RotationPoly> lut44;
    std::vector<long (*)(long)> flut44;
    auto lut44idx0 = [](long I) -> long {
        /* GATE 26 (LUT3 _1482_ INIT 0x96 PERM 012) */
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
    lut44.push_back(ctx.genrate_lut(lut44idx0));
    flut44.push_back(lut44idx0);

    auto lut44idx1 = [](long I) -> long {
        /* GATE 38 (LUT3 _1494_ INIT 0x17 PERM 012) */
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
    lut44.push_back(ctx.genrate_lut(lut44idx1));
    flut44.push_back(lut44idx1);

    auto fvec44 = [flut44](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut44[i](I));
        return ret;
    };

    std::cerr << "\rLUT44   ";
    long gin44 = 1 * gout43[0] + 2 * gout31[0] + 4 * gout16[0];
    std::vector<long> gout44 = fvec44(gin44);

    std::vector<RotationPoly> lut45;
    std::vector<long (*)(long)> flut45;
    auto lut45idx0 = [](long I) -> long {
        /* GATE 108 (LUT2 _1564_ INIT 0x8 PERM 01) */
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
    long gin45 = 1 * ct_y3 + 2 * ct_x3;
    std::vector<long> gout45 = fvec45(gin45);

    std::vector<RotationPoly> lut46;
    std::vector<long (*)(long)> flut46;
    auto lut46idx0 = [](long I) -> long {
        /* GATE 298 (LUT2 _1754_ INIT 0x8 PERM 01) */
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
    long gin46 = 1 * ct_y10 + 2 * ct_x1;
    std::vector<long> gout46 = fvec46(gin46);

    std::vector<RotationPoly> lut47;
    std::vector<long (*)(long)> flut47;
    auto lut47idx0 = [](long I) -> long {
        /* GATE 202 (LUT2 _1658_ INIT 0x8 PERM 10) */
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
    long gin47 = 1 * ct_x9 + 2 * ct_y0;
    std::vector<long> gout47 = fvec47(gin47);

    std::vector<RotationPoly> lut48;
    std::vector<long (*)(long)> flut48;
    auto lut48idx0 = [](long I) -> long {
        /* GATE 486 (LUT2 _1942_ INIT 0x8 PERM 01) */
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
    long gin48 = 1 * ct_y3 + 2 * ct_x12;
    std::vector<long> gout48 = fvec48(gin48);

    std::vector<RotationPoly> lut49;
    std::vector<long (*)(long)> flut49;
    auto lut49idx0 = [](long I) -> long {
        /* GATE 140 (LUT2 _1596_ INIT 0x8 PERM 01) */
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
    long gin49 = 1 * ct_y6 + 2 * ct_x1;
    std::vector<long> gout49 = fvec49(gin49);

    std::vector<RotationPoly> lut50;
    std::vector<long (*)(long)> flut50;
    auto lut50idx0 = [](long I) -> long {
        /* GATE 170 (LUT3 _1626_ INIT 0x80 PERM 012) */
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
    lut50.push_back(ctx.genrate_lut(lut50idx0));
    flut50.push_back(lut50idx0);

    auto lut50idx1 = [](long I) -> long {
        /* GATE 139 (LUT3 _1595_ INIT 0x78 PERM 120) */
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
    lut50.push_back(ctx.genrate_lut(lut50idx1));
    flut50.push_back(lut50idx1);

    auto fvec50 = [flut50](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut50[i](I));
        return ret;
    };

    std::cerr << "\rLUT50   ";
    long gin50 = 1 * gout49[0] + 2 * ct_y7 + 4 * ct_x0;
    std::vector<long> gout50 = fvec50(gin50);

    std::vector<RotationPoly> lut51;
    std::vector<long (*)(long)> flut51;
    auto lut51idx0 = [](long I) -> long {
        /* GATE 328 (LUT2 _1784_ INIT 0x8 PERM 01) */
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
    lut51.push_back(ctx.genrate_lut(lut51idx0));
    flut51.push_back(lut51idx0);

    auto fvec51 = [flut51](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut51[i](I));
        return ret;
    };

    std::cerr << "\rLUT51   ";
    long gin51 = 1 * ct_y5 + 2 * ct_x7;
    std::vector<long> gout51 = fvec51(gin51);

    std::vector<RotationPoly> lut52;
    std::vector<long (*)(long)> flut52;
    auto lut52idx0 = [](long I) -> long {
        /* GATE 368 (LUT3 _1824_ INIT 0x96 PERM 012) */
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
    lut52.push_back(ctx.genrate_lut(lut52idx0));
    flut52.push_back(lut52idx0);

    auto lut52idx1 = [](long I) -> long {
        /* GATE 413 (LUT3 _1869_ INIT 0x17 PERM 012) */
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
    lut52.push_back(ctx.genrate_lut(lut52idx1));
    flut52.push_back(lut52idx1);

    auto fvec52 = [flut52](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut52[i](I));
        return ret;
    };

    std::cerr << "\rLUT52   ";
    long gin52 = 1 * gout30[0] + 2 * gout12[0] + 4 * gout21[0];
    std::vector<long> gout52 = fvec52(gin52);

    std::vector<RotationPoly> lut53;
    std::vector<long (*)(long)> flut53;
    auto lut53idx0 = [](long I) -> long {
        /* GATE 136 (LUT2 _1592_ INIT 0x8 PERM 10) */
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
    long gin53 = 1 * ct_x4 + 2 * ct_y3;
    std::vector<long> gout53 = fvec53(gin53);

    std::vector<RotationPoly> lut54;
    std::vector<long (*)(long)> flut54;
    auto lut54idx0 = [](long I) -> long {
        /* GATE 380 (LUT2 _1836_ INIT 0x8 PERM 01) */
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
    long gin54 = 1 * ct_y7 + 2 * ct_x6;
    std::vector<long> gout54 = fvec54(gin54);

    std::vector<RotationPoly> lut55;
    std::vector<long (*)(long)> flut55;
    auto lut55idx0 = [](long I) -> long {
        /* GATE 423 (LUT3 _1879_ INIT 0x17 PERM 012) */
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
    lut55.push_back(ctx.genrate_lut(lut55idx0));
    flut55.push_back(lut55idx0);

    auto lut55idx1 = [](long I) -> long {
        /* GATE 379 (LUT3 _1835_ INIT 0x96 PERM 012) */
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
    lut55.push_back(ctx.genrate_lut(lut55idx1));
    flut55.push_back(lut55idx1);

    auto fvec55 = [flut55](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut55[i](I));
        return ret;
    };

    std::cerr << "\rLUT55   ";
    long gin55 = 1 * gout54[0] + 2 * gout5[0] + 4 * gout20[0];
    std::vector<long> gout55 = fvec55(gin55);

    std::vector<RotationPoly> lut56;
    std::vector<long (*)(long)> flut56;
    auto lut56idx0 = [](long I) -> long {
        /* GATE 285 (LUT2 _1741_ INIT 0x8 PERM 10) */
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
    long gin56 = 1 * ct_x8 + 2 * ct_y3;
    std::vector<long> gout56 = fvec56(gin56);

    std::vector<RotationPoly> lut57;
    std::vector<long (*)(long)> flut57;
    auto lut57idx0 = [](long I) -> long {
        /* GATE 200 (LUT2 _1656_ INIT 0x8 PERM 10) */
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
    long gin57 = 1 * ct_x8 + 2 * ct_y1;
    std::vector<long> gout57 = fvec57(gin57);

    std::vector<RotationPoly> lut58;
    std::vector<long (*)(long)> flut58;
    auto lut58idx0 = [](long I) -> long {
        /* GATE 107 (LUT2 _1563_ INIT 0x8 PERM 01) */
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
    long gin58 = 1 * ct_y5 + 2 * ct_x1;
    std::vector<long> gout58 = fvec58(gin58);

    std::vector<RotationPoly> lut59;
    std::vector<long (*)(long)> flut59;
    auto lut59idx0 = [](long I) -> long {
        /* GATE 212 (LUT2 _1668_ INIT 0x8 PERM 01) */
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
    long gin59 = 1 * ct_y8 + 2 * ct_x1;
    std::vector<long> gout59 = fvec59(gin59);

    std::vector<RotationPoly> lut60;
    std::vector<long (*)(long)> flut60;
    auto lut60idx0 = [](long I) -> long {
        /* GATE 242 (LUT2 _1698_ INIT 0x8 PERM 01) */
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
    lut60.push_back(ctx.genrate_lut(lut60idx0));
    flut60.push_back(lut60idx0);

    auto fvec60 = [flut60](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut60[i](I));
        return ret;
    };

    std::cerr << "\rLUT60   ";
    long gin60 = 1 * ct_y5 + 2 * ct_x5;
    std::vector<long> gout60 = fvec60(gin60);

    std::vector<RotationPoly> lut61;
    std::vector<long (*)(long)> flut61;
    auto lut61idx0 = [](long I) -> long {
        /* GATE 297 (LUT3 _1753_ INIT 0x96 PERM 012) */
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
    lut61.push_back(ctx.genrate_lut(lut61idx0));
    flut61.push_back(lut61idx0);

    auto lut61idx1 = [](long I) -> long {
        /* GATE 341 (LUT3 _1797_ INIT 0x17 PERM 012) */
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
    lut61.push_back(ctx.genrate_lut(lut61idx1));
    flut61.push_back(lut61idx1);

    auto fvec61 = [flut61](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut61[i](I));
        return ret;
    };

    std::cerr << "\rLUT61   ";
    long gin61 = 1 * gout46[0] + 2 * gout26[0] + 4 * gout15[0];
    std::vector<long> gout61 = fvec61(gin61);

    std::vector<RotationPoly> lut62;
    std::vector<long (*)(long)> flut62;
    auto lut62idx0 = [](long I) -> long {
        /* GATE 327 (LUT2 _1783_ INIT 0x8 PERM 10) */
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
    long gin62 = 1 * ct_x8 + 2 * ct_y4;
    std::vector<long> gout62 = fvec62(gin62);

    std::vector<RotationPoly> lut63;
    std::vector<long (*)(long)> flut63;
    auto lut63idx0 = [](long I) -> long {
        /* GATE 378 (LUT3 _1834_ INIT 0x17 PERM 012) */
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
    lut63.push_back(ctx.genrate_lut(lut63idx0));
    flut63.push_back(lut63idx0);

    auto lut63idx1 = [](long I) -> long {
        /* GATE 326 (LUT3 _1782_ INIT 0x96 PERM 012) */
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
    lut63.push_back(ctx.genrate_lut(lut63idx1));
    flut63.push_back(lut63idx1);

    auto fvec63 = [flut63](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut63[i](I));
        return ret;
    };

    std::cerr << "\rLUT63   ";
    long gin63 = 1 * gout62[0] + 2 * gout51[0] + 4 * gout34[0];
    std::vector<long> gout63 = fvec63(gin63);

    std::vector<RotationPoly> lut64;
    std::vector<long (*)(long)> flut64;
    auto lut64idx0 = [](long I) -> long {
        /* GATE 235 (LUT3 _1691_ INIT 0x17 PERM 012) */
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
    lut64.push_back(ctx.genrate_lut(lut64idx0));
    flut64.push_back(lut64idx0);

    auto lut64idx1 = [](long I) -> long {
        /* GATE 199 (LUT3 _1655_ INIT 0x96 PERM 012) */
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
    lut64.push_back(ctx.genrate_lut(lut64idx1));
    flut64.push_back(lut64idx1);

    auto fvec64 = [flut64](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut64[i](I));
        return ret;
    };

    std::cerr << "\rLUT64   ";
    long gin64 = 1 * gout57[0] + 2 * gout32[0] + 4 * gout47[0];
    std::vector<long> gout64 = fvec64(gin64);

    std::vector<RotationPoly> lut65;
    std::vector<long (*)(long)> flut65;
    auto lut65idx0 = [](long I) -> long {
        /* GATE 13 (LUT2 _1469_ INIT 0x8 PERM 10) */
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
    long gin65 = 1 * ct_y0 + 2 * ct_x0;
    std::vector<long> gout65 = fvec65(gin65);

    std::vector<RotationPoly> lut66;
    std::vector<long (*)(long)> flut66;
    auto lut66idx0 = [](long I) -> long {
        /* GATE 168 (LUT2 _1624_ INIT 0x8 PERM 01) */
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
    long gin66 = 1 * ct_y3 + 2 * ct_x5;
    std::vector<long> gout66 = fvec66(gin66);

    std::vector<RotationPoly> lut67;
    std::vector<long (*)(long)> flut67;
    auto lut67idx0 = [](long I) -> long {
        /* GATE 211 (LUT2 _1667_ INIT 0x8 PERM 01) */
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
    long gin67 = 1 * ct_y7 + 2 * ct_x2;
    std::vector<long> gout67 = fvec67(gin67);

    std::vector<RotationPoly> lut68;
    std::vector<long (*)(long)> flut68;
    auto lut68idx0 = [](long I) -> long {
        /* GATE 254 (LUT2 _1710_ INIT 0x8 PERM 01) */
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
    long gin68 = 1 * ct_y9 + 2 * ct_x1;
    std::vector<long> gout68 = fvec68(gin68);

    std::vector<RotationPoly> lut69;
    std::vector<long (*)(long)> flut69;
    auto lut69idx0 = [](long I) -> long {
        /* GATE 253 (LUT3 _1709_ INIT 0x78 PERM 120) */
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
    lut69.push_back(ctx.genrate_lut(lut69idx0));
    flut69.push_back(lut69idx0);

    auto lut69idx1 = [](long I) -> long {
        /* GATE 296 (LUT3 _1752_ INIT 0x80 PERM 012) */
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
    lut69.push_back(ctx.genrate_lut(lut69idx1));
    flut69.push_back(lut69idx1);

    auto fvec69 = [flut69](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut69[i](I));
        return ret;
    };

    std::cerr << "\rLUT69   ";
    long gin69 = 1 * gout68[0] + 2 * ct_y10 + 4 * ct_x0;
    std::vector<long> gout69 = fvec69(gin69);

    std::vector<RotationPoly> lut70;
    std::vector<long (*)(long)> flut70;
    auto lut70idx0 = [](long I) -> long {
        /* GATE 338 (LUT2 _1794_ INIT 0x8 PERM 01) */
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

    auto lut70idx1 = [](long I) -> long {
        /* GATE 295 (LUT2 _1751_ INIT 0x6 PERM 01) */
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
    lut70.push_back(ctx.genrate_lut(lut70idx1));
    flut70.push_back(lut70idx1);

    auto fvec70 = [flut70](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut70[i](I));
        return ret;
    };

    std::cerr << "\rLUT70   ";
    long gin70 = 1 * gout69[1] + 2 * gout61[0];
    std::vector<long> gout70 = fvec70(gin70);

    std::vector<RotationPoly> lut71;
    std::vector<long (*)(long)> flut71;
    auto lut71idx0 = [](long I) -> long {
        /* GATE 59 (LUT2 _1515_ INIT 0x8 PERM 10) */
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
    long gin71 = 1 * ct_x4 + 2 * ct_y0;
    std::vector<long> gout71 = fvec71(gin71);

    std::vector<RotationPoly> lut72;
    std::vector<long (*)(long)> flut72;
    auto lut72idx0 = [](long I) -> long {
        /* GATE 292 (LUT2 _1748_ INIT 0x8 PERM 01) */
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
    lut72.push_back(ctx.genrate_lut(lut72idx0));
    flut72.push_back(lut72idx0);

    auto fvec72 = [flut72](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut72[i](I));
        return ret;
    };

    std::cerr << "\rLUT72   ";
    long gin72 = 1 * ct_y6 + 2 * ct_x5;
    std::vector<long> gout72 = fvec72(gin72);

    std::vector<RotationPoly> lut73;
    std::vector<long (*)(long)> flut73;
    auto lut73idx0 = [](long I) -> long {
        /* GATE 336 (LUT2 _1792_ INIT 0x8 PERM 01) */
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
    long gin73 = 1 * ct_y6 + 2 * ct_x6;
    std::vector<long> gout73 = fvec73(gin73);

    std::vector<RotationPoly> lut74;
    std::vector<long (*)(long)> flut74;
    auto lut74idx0 = [](long I) -> long {
        /* GATE 485 (LUT3 _1941_ INIT 0x87 PERM 012) */
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
    lut74.push_back(ctx.genrate_lut(lut74idx0));
    flut74.push_back(lut74idx0);

    auto fvec74 = [flut74](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut74[i](I));
        return ret;
    };

    std::cerr << "\rLUT74   ";
    long gin74 = 1 * ct_y2 + 2 * ct_x13 + 4 * gout48[0];
    std::vector<long> gout74 = fvec74(gin74);

    std::vector<RotationPoly> lut75;
    std::vector<long (*)(long)> flut75;
    auto lut75idx0 = [](long I) -> long {
        /* GATE 16 (LUT2 _1472_ INIT 0x8 PERM 01) */
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
    lut75.push_back(ctx.genrate_lut(lut75idx0));
    flut75.push_back(lut75idx0);

    auto fvec75 = [flut75](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut75[i](I));
        return ret;
    };

    std::cerr << "\rLUT75   ";
    long gin75 = 1 * ct_y0 + 2 * ct_x1;
    std::vector<long> gout75 = fvec75(gin75);

    std::vector<RotationPoly> lut76;
    std::vector<long (*)(long)> flut76;
    auto lut76idx0 = [](long I) -> long {
        /* GATE 15 (LUT3 _1471_ INIT 0x78 PERM 021) */
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
    lut76.push_back(ctx.genrate_lut(lut76idx0));
    flut76.push_back(lut76idx0);

    auto fvec76 = [flut76](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut76[i](I));
        return ret;
    };

    std::cerr << "\rLUT76   ";
    long gin76 = 1 * ct_y1 + 2 * gout75[0] + 4 * ct_x0;
    std::vector<long> gout76 = fvec76(gin76);

    std::vector<RotationPoly> lut77;
    std::vector<long (*)(long)> flut77;
    auto lut77idx0 = [](long I) -> long {
        /* GATE 167 (LUT2 _1623_ INIT 0x8 PERM 01) */
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
    long gin77 = 1 * ct_y5 + 2 * ct_x3;
    std::vector<long> gout77 = fvec77(gin77);

    std::vector<RotationPoly> lut78;
    std::vector<long (*)(long)> flut78;
    auto lut78idx0 = [](long I) -> long {
        /* GATE 280 (LUT2 _1736_ INIT 0x8 PERM 10) */
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
    lut78.push_back(ctx.genrate_lut(lut78idx0));
    flut78.push_back(lut78idx0);

    auto fvec78 = [flut78](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut78[i](I));
        return ret;
    };

    std::cerr << "\rLUT78   ";
    long gin78 = 1 * ct_x9 + 2 * ct_y2;
    std::vector<long> gout78 = fvec78(gin78);

    std::vector<RotationPoly> lut79;
    std::vector<long (*)(long)> flut79;
    auto lut79idx0 = [](long I) -> long {
        /* GATE 291 (LUT2 _1747_ INIT 0x8 PERM 10) */
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
    long gin79 = 1 * ct_x3 + 2 * ct_y8;
    std::vector<long> gout79 = fvec79(gin79);

    std::vector<RotationPoly> lut80;
    std::vector<long (*)(long)> flut80;
    auto lut80idx0 = [](long I) -> long {
        /* GATE 289 (LUT3 _1745_ INIT 0x96 PERM 012) */
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
    lut80.push_back(ctx.genrate_lut(lut80idx0));
    flut80.push_back(lut80idx0);

    auto lut80idx1 = [](long I) -> long {
        /* GATE 331 (LUT3 _1787_ INIT 0x17 PERM 012) */
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
    lut80.push_back(ctx.genrate_lut(lut80idx1));
    flut80.push_back(lut80idx1);

    auto fvec80 = [flut80](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut80[i](I));
        return ret;
    };

    std::cerr << "\rLUT80   ";
    long gin80 = 1 * gout9[0] + 2 * gout79[0] + 4 * gout72[0];
    std::vector<long> gout80 = fvec80(gin80);

    std::vector<RotationPoly> lut81;
    std::vector<long (*)(long)> flut81;
    auto lut81idx0 = [](long I) -> long {
        /* GATE 6 (LUT3 _1462_ INIT 0x40 PERM 102) */
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
    lut81.push_back(ctx.genrate_lut(lut81idx0));
    flut81.push_back(lut81idx0);

    auto lut81idx1 = [](long I) -> long {
        /* GATE 7 (LUT3 _1463_ INIT 0x40 PERM 012) */
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
    lut81.push_back(ctx.genrate_lut(lut81idx1));
    flut81.push_back(lut81idx1);

    auto fvec81 = [flut81](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut81[i](I));
        return ret;
    };

    std::cerr << "\rLUT81   ";
    long gin81 = 1 * ct_op2 + 2 * ct_op1 + 4 * ct_op3;
    std::vector<long> gout81 = fvec81(gin81);

    std::vector<RotationPoly> lut82;
    std::vector<long (*)(long)> flut82;
    auto lut82idx0 = [](long I) -> long {
        /* GATE 238 (LUT2 _1694_ INIT 0x8 PERM 10) */
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
    long gin82 = 1 * ct_x8 + 2 * ct_y2;
    std::vector<long> gout82 = fvec82(gin82);

    std::vector<RotationPoly> lut83;
    std::vector<long (*)(long)> flut83;
    auto lut83idx0 = [](long I) -> long {
        /* GATE 335 (LUT2 _1791_ INIT 0x8 PERM 10) */
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
    lut83.push_back(ctx.genrate_lut(lut83idx0));
    flut83.push_back(lut83idx0);

    auto fvec83 = [flut83](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut83[i](I));
        return ret;
    };

    std::cerr << "\rLUT83   ";
    long gin83 = 1 * ct_x4 + 2 * ct_y8;
    std::vector<long> gout83 = fvec83(gin83);

    std::vector<RotationPoly> lut84;
    std::vector<long (*)(long)> flut84;
    auto lut84idx0 = [](long I) -> long {
        /* GATE 416 (LUT2 _1872_ INIT 0x8 PERM 01) */
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
    long gin84 = 1 * ct_y2 + 2 * ct_x12;
    std::vector<long> gout84 = fvec84(gin84);

    std::vector<RotationPoly> lut85;
    std::vector<long (*)(long)> flut85;
    auto lut85idx0 = [](long I) -> long {
        /* GATE 375 (LUT2 _1831_ INIT 0x8 PERM 10) */
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
    long gin85 = 1 * ct_x10 + 2 * ct_y3;
    std::vector<long> gout85 = fvec85(gin85);

    std::vector<RotationPoly> lut86;
    std::vector<long (*)(long)> flut86;
    auto lut86idx0 = [](long I) -> long {
        /* GATE 132 (LUT2 _1588_ INIT 0x8 PERM 01) */
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
    lut86.push_back(ctx.genrate_lut(lut86idx0));
    flut86.push_back(lut86idx0);

    auto fvec86 = [flut86](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut86[i](I));
        return ret;
    };

    std::cerr << "\rLUT86   ";
    long gin86 = 1 * ct_y0 + 2 * ct_x7;
    std::vector<long> gout86 = fvec86(gin86);

    std::vector<RotationPoly> lut87;
    std::vector<long (*)(long)> flut87;
    auto lut87idx0 = [](long I) -> long {
        /* GATE 459 (LUT3 _1915_ INIT 0x87 PERM 012) */
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
    lut87.push_back(ctx.genrate_lut(lut87idx0));
    flut87.push_back(lut87idx0);

    auto fvec87 = [flut87](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut87[i](I));
        return ret;
    };

    std::cerr << "\rLUT87   ";
    long gin87 = 1 * ct_y8 + 2 * ct_x7 + 4 * gout11[0];
    std::vector<long> gout87 = fvec87(gin87);

    std::vector<RotationPoly> lut88;
    std::vector<long (*)(long)> flut88;
    auto lut88idx0 = [](long I) -> long {
        /* GATE 116 (LUT3 _1572_ INIT 0x10 PERM 120) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
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
    long gin88 = 1 * gout38[0] + 2 * ct_y5 + 4 * ct_y6;
    std::vector<long> gout88 = fvec88(gin88);

    std::vector<RotationPoly> lut89;
    std::vector<long (*)(long)> flut89;
    auto lut89idx0 = [](long I) -> long {
        /* GATE 281 (LUT2 _1737_ INIT 0x8 PERM 10) */
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
    long gin89 = 1 * ct_x11 + 2 * ct_y0;
    std::vector<long> gout89 = fvec89(gin89);

    std::vector<RotationPoly> lut90;
    std::vector<long (*)(long)> flut90;
    auto lut90idx0 = [](long I) -> long {
        /* GATE 417 (LUT2 _1873_ INIT 0x8 PERM 01) */
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
    long gin90 = 1 * ct_y0 + 2 * ct_x14;
    std::vector<long> gout90 = fvec90(gin90);

    std::vector<RotationPoly> lut91;
    std::vector<long (*)(long)> flut91;
    auto lut91idx0 = [](long I) -> long {
        /* GATE 414 (LUT3 _1870_ INIT 0x96 PERM 012) */
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
    lut91.push_back(ctx.genrate_lut(lut91idx0));
    flut91.push_back(lut91idx0);

    auto lut91idx1 = [](long I) -> long {
        /* GATE 475 (LUT3 _1931_ INIT 0x17 PERM 012) */
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
    lut91.push_back(ctx.genrate_lut(lut91idx1));
    flut91.push_back(lut91idx1);

    auto fvec91 = [flut91](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut91[i](I));
        return ret;
    };

    std::cerr << "\rLUT91   ";
    long gin91 = 1 * gout6[0] + 2 * gout84[0] + 4 * gout90[0];
    std::vector<long> gout91 = fvec91(gin91);

    std::vector<RotationPoly> lut92;
    std::vector<long (*)(long)> flut92;
    auto lut92idx0 = [](long I) -> long {
        /* GATE 239 (LUT2 _1695_ INIT 0x8 PERM 10) */
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
    lut92.push_back(ctx.genrate_lut(lut92idx0));
    flut92.push_back(lut92idx0);

    auto fvec92 = [flut92](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut92[i](I));
        return ret;
    };

    std::cerr << "\rLUT92   ";
    long gin92 = 1 * ct_x10 + 2 * ct_y0;
    std::vector<long> gout92 = fvec92(gin92);

    std::vector<RotationPoly> lut93;
    std::vector<long (*)(long)> flut93;
    auto lut93idx0 = [](long I) -> long {
        /* GATE 166 (LUT2 _1622_ INIT 0x8 PERM 10) */
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
    long gin93 = 1 * ct_x4 + 2 * ct_y4;
    std::vector<long> gout93 = fvec93(gin93);

    std::vector<RotationPoly> lut94;
    std::vector<long (*)(long)> flut94;
    auto lut94idx0 = [](long I) -> long {
        /* GATE 209 (LUT3 _1665_ INIT 0x17 PERM 012) */
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
    lut94.push_back(ctx.genrate_lut(lut94idx0));
    flut94.push_back(lut94idx0);

    auto lut94idx1 = [](long I) -> long {
        /* GATE 165 (LUT3 _1621_ INIT 0x96 PERM 012) */
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
    lut94.push_back(ctx.genrate_lut(lut94idx1));
    flut94.push_back(lut94idx1);

    auto fvec94 = [flut94](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut94[i](I));
        return ret;
    };

    std::cerr << "\rLUT94   ";
    long gin94 = 1 * gout93[0] + 2 * gout77[0] + 4 * gout66[0];
    std::vector<long> gout94 = fvec94(gin94);

    std::vector<RotationPoly> lut95;
    std::vector<long (*)(long)> flut95;
    auto lut95idx0 = [](long I) -> long {
        /* GATE 435 (LUT2 _1891_ INIT 0x8 PERM 10) */
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
    lut95.push_back(ctx.genrate_lut(lut95idx0));
    flut95.push_back(lut95idx0);

    auto fvec95 = [flut95](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut95[i](I));
        return ret;
    };

    std::cerr << "\rLUT95   ";
    long gin95 = 1 * ct_x4 + 2 * ct_y10;
    std::vector<long> gout95 = fvec95(gin95);

    std::vector<RotationPoly> lut96;
    std::vector<long (*)(long)> flut96;
    auto lut96idx0 = [](long I) -> long {
        /* GATE 279 (LUT2 _1735_ INIT 0x8 PERM 10) */
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
    long gin96 = 1 * ct_x10 + 2 * ct_y1;
    std::vector<long> gout96 = fvec96(gin96);

    std::vector<RotationPoly> lut97;
    std::vector<long (*)(long)> flut97;
    auto lut97idx0 = [](long I) -> long {
        /* GATE 278 (LUT3 _1734_ INIT 0x96 PERM 012) */
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
    lut97.push_back(ctx.genrate_lut(lut97idx0));
    flut97.push_back(lut97idx0);

    auto lut97idx1 = [](long I) -> long {
        /* GATE 321 (LUT3 _1777_ INIT 0x17 PERM 012) */
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
    lut97.push_back(ctx.genrate_lut(lut97idx1));
    flut97.push_back(lut97idx1);

    auto fvec97 = [flut97](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut97[i](I));
        return ret;
    };

    std::cerr << "\rLUT97   ";
    long gin97 = 1 * gout96[0] + 2 * gout78[0] + 4 * gout89[0];
    std::vector<long> gout97 = fvec97(gin97);

    std::vector<RotationPoly> lut98;
    std::vector<long (*)(long)> flut98;
    auto lut98idx0 = [](long I) -> long {
        /* GATE 470 (LUT2 _1926_ INIT 0x8 PERM 10) */
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
    long gin98 = 1 * ct_x9 + 2 * ct_y6;
    std::vector<long> gout98 = fvec98(gin98);

    std::vector<RotationPoly> lut99;
    std::vector<long (*)(long)> flut99;
    auto lut99idx0 = [](long I) -> long {
        /* GATE 469 (LUT3 _1925_ INIT 0x87 PERM 012) */
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
    lut99.push_back(ctx.genrate_lut(lut99idx0));
    flut99.push_back(lut99idx0);

    auto fvec99 = [flut99](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut99[i](I));
        return ret;
    };

    std::cerr << "\rLUT99   ";
    long gin99 = 1 * ct_y5 + 2 * ct_x10 + 4 * gout98[0];
    std::vector<long> gout99 = fvec99(gin99);

    std::vector<RotationPoly> lut100;
    std::vector<long (*)(long)> flut100;
    auto lut100idx0 = [](long I) -> long {
        /* GATE 374 (LUT2 _1830_ INIT 0x8 PERM 01) */
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
    long gin100 = 1 * ct_y5 + 2 * ct_x8;
    std::vector<long> gout100 = fvec100(gin100);

    std::vector<RotationPoly> lut101;
    std::vector<long (*)(long)> flut101;
    auto lut101idx0 = [](long I) -> long {
        /* GATE 372 (LUT3 _1828_ INIT 0x96 PERM 012) */
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
        /* GATE 424 (LUT3 _1880_ INIT 0x17 PERM 012) */
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
    long gin101 = 1 * gout8[0] + 2 * gout100[0] + 4 * gout85[0];
    std::vector<long> gout101 = fvec101(gin101);

    std::vector<RotationPoly> lut102;
    std::vector<long (*)(long)> flut102;
    auto lut102idx0 = [](long I) -> long {
        /* GATE 60 (LUT3 _1516_ INIT 0x78 PERM 120) */
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
    lut102.push_back(ctx.genrate_lut(lut102idx0));
    flut102.push_back(lut102idx0);

    auto fvec102 = [flut102](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut102[i](I));
        return ret;
    };

    std::cerr << "\rLUT102   ";
    long gin102 = 1 * gout28[0] + 2 * ct_y4 + 4 * ct_x0;
    std::vector<long> gout102 = fvec102(gin102);

    std::vector<RotationPoly> lut103;
    std::vector<long (*)(long)> flut103;
    auto lut103idx0 = [](long I) -> long {
        /* GATE 103 (LUT2 _1559_ INIT 0x8 PERM 10) */
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
    long gin103 = 1 * ct_x4 + 2 * ct_y2;
    std::vector<long> gout103 = fvec103(gin103);

    std::vector<RotationPoly> lut104;
    std::vector<long (*)(long)> flut104;
    auto lut104idx0 = [](long I) -> long {
        /* GATE 237 (LUT2 _1693_ INIT 0x8 PERM 10) */
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
    lut104.push_back(ctx.genrate_lut(lut104idx0));
    flut104.push_back(lut104idx0);

    auto fvec104 = [flut104](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut104[i](I));
        return ret;
    };

    std::cerr << "\rLUT104   ";
    long gin104 = 1 * ct_x9 + 2 * ct_y1;
    std::vector<long> gout104 = fvec104(gin104);

    std::vector<RotationPoly> lut105;
    std::vector<long (*)(long)> flut105;
    auto lut105idx0 = [](long I) -> long {
        /* GATE 277 (LUT3 _1733_ INIT 0x17 PERM 012) */
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
    lut105.push_back(ctx.genrate_lut(lut105idx0));
    flut105.push_back(lut105idx0);

    auto lut105idx1 = [](long I) -> long {
        /* GATE 236 (LUT3 _1692_ INIT 0x96 PERM 012) */
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
    lut105.push_back(ctx.genrate_lut(lut105idx1));
    flut105.push_back(lut105idx1);

    auto fvec105 = [flut105](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut105[i](I));
        return ret;
    };

    std::cerr << "\rLUT105   ";
    long gin105 = 1 * gout104[0] + 2 * gout82[0] + 4 * gout92[0];
    std::vector<long> gout105 = fvec105(gin105);

    std::vector<RotationPoly> lut106;
    std::vector<long (*)(long)> flut106;
    auto lut106idx0 = [](long I) -> long {
        /* GATE 478 (LUT3 _1934_ INIT 0x4b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
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
    long gin106 = 1 * ct_x0 + 2 * ct_y15 + 4 * gout25[0];
    std::vector<long> gout106 = fvec106(gin106);

    std::vector<RotationPoly> lut107;
    std::vector<long (*)(long)> flut107;
    auto lut107idx0 = [](long I) -> long {
        /* GATE 334 (LUT2 _1790_ INIT 0x8 PERM 01) */
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
    long gin107 = 1 * ct_y7 + 2 * ct_x5;
    std::vector<long> gout107 = fvec107(gin107);

    std::vector<RotationPoly> lut108;
    std::vector<long (*)(long)> flut108;
    auto lut108idx0 = [](long I) -> long {
        /* GATE 333 (LUT3 _1789_ INIT 0x96 PERM 012) */
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
        /* GATE 377 (LUT3 _1833_ INIT 0x17 PERM 012) */
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
    long gin108 = 1 * gout107[0] + 2 * gout83[0] + 4 * gout73[0];
    std::vector<long> gout108 = fvec108(gin108);

    std::vector<RotationPoly> lut109;
    std::vector<long (*)(long)> flut109;
    auto lut109idx0 = [](long I) -> long {
        /* GATE 102 (LUT2 _1558_ INIT 0x8 PERM 01) */
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
    long gin109 = 1 * ct_y1 + 2 * ct_x5;
    std::vector<long> gout109 = fvec109(gin109);

    std::vector<RotationPoly> lut110;
    std::vector<long (*)(long)> flut110;
    auto lut110idx0 = [](long I) -> long {
        /* GATE 213 (LUT2 _1669_ INIT 0x8 PERM 01) */
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
    lut110.push_back(ctx.genrate_lut(lut110idx0));
    flut110.push_back(lut110idx0);

    auto fvec110 = [flut110](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut110[i](I));
        return ret;
    };

    std::cerr << "\rLUT110   ";
    long gin110 = 1 * ct_y6 + 2 * ct_x3;
    std::vector<long> gout110 = fvec110(gin110);

    std::vector<RotationPoly> lut111;
    std::vector<long (*)(long)> flut111;
    auto lut111idx0 = [](long I) -> long {
        /* GATE 104 (LUT2 _1560_ INIT 0x8 PERM 10) */
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
    lut111.push_back(ctx.genrate_lut(lut111idx0));
    flut111.push_back(lut111idx0);

    auto fvec111 = [flut111](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut111[i](I));
        return ret;
    };

    std::cerr << "\rLUT111   ";
    long gin111 = 1 * ct_x6 + 2 * ct_y0;
    std::vector<long> gout111 = fvec111(gin111);

    std::vector<RotationPoly> lut112;
    std::vector<long (*)(long)> flut112;
    auto lut112idx0 = [](long I) -> long {
        /* GATE 128 (LUT3 _1584_ INIT 0x17 PERM 012) */
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
    lut112.push_back(ctx.genrate_lut(lut112idx0));
    flut112.push_back(lut112idx0);

    auto lut112idx1 = [](long I) -> long {
        /* GATE 101 (LUT3 _1557_ INIT 0x96 PERM 012) */
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
    lut112.push_back(ctx.genrate_lut(lut112idx1));
    flut112.push_back(lut112idx1);

    auto fvec112 = [flut112](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut112[i](I));
        return ret;
    };

    std::cerr << "\rLUT112   ";
    long gin112 = 1 * gout109[0] + 2 * gout103[0] + 4 * gout111[0];
    std::vector<long> gout112 = fvec112(gin112);

    std::vector<RotationPoly> lut113;
    std::vector<long (*)(long)> flut113;
    auto lut113idx0 = [](long I) -> long {
        /* GATE 458 (LUT3 _1914_ INIT 0x78 PERM 021) */
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
    lut113.push_back(ctx.genrate_lut(lut113idx0));
    flut113.push_back(lut113idx0);

    auto fvec113 = [flut113](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut113[i](I));
        return ret;
    };

    std::cerr << "\rLUT113   ";
    long gin113 = 1 * ct_y10 + 2 * gout87[0] + 4 * ct_x5;
    std::vector<long> gout113 = fvec113(gin113);

    std::vector<RotationPoly> lut114;
    std::vector<long (*)(long)> flut114;
    auto lut114idx0 = [](long I) -> long {
        /* GATE 431 (LUT3 _1887_ INIT 0xb2 PERM 012) */
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
    lut114.push_back(ctx.genrate_lut(lut114idx0));
    flut114.push_back(lut114idx0);

    auto lut114idx1 = [](long I) -> long {
        /* GATE 376 (LUT3 _1832_ INIT 0x96 PERM 021) */
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
    lut114.push_back(ctx.genrate_lut(lut114idx1));
    flut114.push_back(lut114idx1);

    auto fvec114 = [flut114](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut114[i](I));
        return ret;
    };

    std::cerr << "\rLUT114   ";
    long gin114 = 1 * gout108[1] + 2 * gout55[1] + 4 * gout63[0];
    std::vector<long> gout114 = fvec114(gin114);

    std::vector<RotationPoly> lut115;
    std::vector<long (*)(long)> flut115;
    auto lut115idx0 = [](long I) -> long {
        /* GATE 42 (LUT2 _1498_ INIT 0x8 PERM 10) */
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
    lut115.push_back(ctx.genrate_lut(lut115idx0));
    flut115.push_back(lut115idx0);

    auto fvec115 = [flut115](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut115[i](I));
        return ret;
    };

    std::cerr << "\rLUT115   ";
    long gin115 = 1 * ct_x3 + 2 * ct_y0;
    std::vector<long> gout115 = fvec115(gin115);

    std::vector<RotationPoly> lut116;
    std::vector<long (*)(long)> flut116;
    auto lut116idx0 = [](long I) -> long {
        /* GATE 55 (LUT3 _1511_ INIT 0x17 PERM 012) */
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
    lut116.push_back(ctx.genrate_lut(lut116idx0));
    flut116.push_back(lut116idx0);

    auto lut116idx1 = [](long I) -> long {
        /* GATE 39 (LUT3 _1495_ INIT 0x96 PERM 012) */
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
    lut116.push_back(ctx.genrate_lut(lut116idx1));
    flut116.push_back(lut116idx1);

    auto fvec116 = [flut116](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut116[i](I));
        return ret;
    };

    std::cerr << "\rLUT116   ";
    long gin116 = 1 * gout19[0] + 2 * gout3[0] + 4 * gout115[0];
    std::vector<long> gout116 = fvec116(gin116);

    std::vector<RotationPoly> lut117;
    std::vector<long (*)(long)> flut117;
    auto lut117idx0 = [](long I) -> long {
        /* GATE 437 (LUT2 _1893_ INIT 0x8 PERM 01) */
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
    lut117.push_back(ctx.genrate_lut(lut117idx0));
    flut117.push_back(lut117idx0);

    auto fvec117 = [flut117](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut117[i](I));
        return ret;
    };

    std::cerr << "\rLUT117   ";
    long gin117 = 1 * ct_y9 + 2 * ct_x5;
    std::vector<long> gout117 = fvec117(gin117);

    std::vector<RotationPoly> lut118;
    std::vector<long (*)(long)> flut118;
    auto lut118idx0 = [](long I) -> long {
        /* GATE 130 (LUT2 _1586_ INIT 0x8 PERM 10) */
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
    long gin118 = 1 * ct_x6 + 2 * ct_y1;
    std::vector<long> gout118 = fvec118(gin118);

    std::vector<RotationPoly> lut119;
    std::vector<long (*)(long)> flut119;
    auto lut119idx0 = [](long I) -> long {
        /* GATE 160 (LUT3 _1616_ INIT 0x17 PERM 012) */
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
    lut119.push_back(ctx.genrate_lut(lut119idx0));
    flut119.push_back(lut119idx0);

    auto lut119idx1 = [](long I) -> long {
        /* GATE 129 (LUT3 _1585_ INIT 0x96 PERM 012) */
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
    lut119.push_back(ctx.genrate_lut(lut119idx1));
    flut119.push_back(lut119idx1);

    auto fvec119 = [flut119](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut119[i](I));
        return ret;
    };

    std::cerr << "\rLUT119   ";
    long gin119 = 1 * gout118[0] + 2 * gout40[0] + 4 * gout86[0];
    std::vector<long> gout119 = fvec119(gin119);

    std::vector<RotationPoly> lut120;
    std::vector<long (*)(long)> flut120;
    auto lut120idx0 = [](long I) -> long {
        /* GATE 421 (LUT2 _1877_ INIT 0x8 PERM 01) */
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
    long gin120 = 1 * ct_y3 + 2 * ct_x11;
    std::vector<long> gout120 = fvec120(gin120);

    std::vector<RotationPoly> lut121;
    std::vector<long (*)(long)> flut121;
    auto lut121idx0 = [](long I) -> long {
        /* GATE 284 (LUT2 _1740_ INIT 0x8 PERM 01) */
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
    lut121.push_back(ctx.genrate_lut(lut121idx0));
    flut121.push_back(lut121idx0);

    auto fvec121 = [flut121](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut121[i](I));
        return ret;
    };

    std::cerr << "\rLUT121   ";
    long gin121 = 1 * ct_y5 + 2 * ct_x6;
    std::vector<long> gout121 = fvec121(gin121);

    std::vector<RotationPoly> lut122;
    std::vector<long (*)(long)> flut122;
    auto lut122idx0 = [](long I) -> long {
        /* GATE 135 (LUT2 _1591_ INIT 0x8 PERM 01) */
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
    lut122.push_back(ctx.genrate_lut(lut122idx0));
    flut122.push_back(lut122idx0);

    auto fvec122 = [flut122](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut122[i](I));
        return ret;
    };

    std::cerr << "\rLUT122   ";
    long gin122 = 1 * ct_y5 + 2 * ct_x2;
    std::vector<long> gout122 = fvec122(gin122);

    std::vector<RotationPoly> lut123;
    std::vector<long (*)(long)> flut123;
    auto lut123idx0 = [](long I) -> long {
        /* GATE 43 (LUT2 _1499_ INIT 0x8 PERM 01) */
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
    long gin123 = 1 * ct_y3 + 2 * ct_x0;
    std::vector<long> gout123 = fvec123(gin123);

    std::vector<RotationPoly> lut124;
    std::vector<long (*)(long)> flut124;
    auto lut124idx0 = [](long I) -> long {
        /* GATE 436 (LUT2 _1892_ INIT 0x8 PERM 01) */
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
    long gin124 = 1 * ct_y11 + 2 * ct_x3;
    std::vector<long> gout124 = fvec124(gin124);

    std::vector<RotationPoly> lut125;
    std::vector<long (*)(long)> flut125;
    auto lut125idx0 = [](long I) -> long {
        /* GATE 465 (LUT3 _1921_ INIT 0x17 PERM 012) */
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
    lut125.push_back(ctx.genrate_lut(lut125idx0));
    flut125.push_back(lut125idx0);

    auto lut125idx1 = [](long I) -> long {
        /* GATE 434 (LUT3 _1890_ INIT 0x96 PERM 012) */
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
    lut125.push_back(ctx.genrate_lut(lut125idx1));
    flut125.push_back(lut125idx1);

    auto fvec125 = [flut125](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut125[i](I));
        return ret;
    };

    std::cerr << "\rLUT125   ";
    long gin125 = 1 * gout95[0] + 2 * gout124[0] + 4 * gout117[0];
    std::vector<long> gout125 = fvec125(gin125);

    std::vector<RotationPoly> lut126;
    std::vector<long (*)(long)> flut126;
    auto lut126idx0 = [](long I) -> long {
        /* GATE 464 (LUT3 _1920_ INIT 0x87 PERM 012) */
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
    lut126.push_back(ctx.genrate_lut(lut126idx0));
    flut126.push_back(lut126idx0);

    auto fvec126 = [flut126](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut126[i](I));
        return ret;
    };

    std::cerr << "\rLUT126   ";
    long gin126 = 1 * ct_y13 + 2 * ct_x2 + 4 * gout125[0];
    std::vector<long> gout126 = fvec126(gin126);

    std::vector<RotationPoly> lut127;
    std::vector<long (*)(long)> flut127;
    auto lut127idx0 = [](long I) -> long {
        /* GATE 346 (LUT2 _1802_ INIT 0x8 PERM 01) */
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
    long gin127 = 1 * ct_y12 + 2 * ct_x0;
    std::vector<long> gout127 = fvec127(gin127);

    std::vector<RotationPoly> lut128;
    std::vector<long (*)(long)> flut128;
    auto lut128idx0 = [](long I) -> long {
        /* GATE 444 (LUT2 _1900_ INIT 0x8 PERM 01) */
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
    lut128.push_back(ctx.genrate_lut(lut128idx0));
    flut128.push_back(lut128idx0);

    auto fvec128 = [flut128](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut128[i](I));
        return ret;
    };

    std::cerr << "\rLUT128   ";
    long gin128 = 1 * gout127[0] + 2 * gout17[0];
    std::vector<long> gout128 = fvec128(gin128);

    std::vector<RotationPoly> lut129;
    std::vector<long (*)(long)> flut129;
    auto lut129idx0 = [](long I) -> long {
        /* GATE 250 (LUT2 _1706_ INIT 0x8 PERM 01) */
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
    lut129.push_back(ctx.genrate_lut(lut129idx0));
    flut129.push_back(lut129idx0);

    auto fvec129 = [flut129](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut129[i](I));
        return ret;
    };

    std::cerr << "\rLUT129   ";
    long gin129 = 1 * ct_y6 + 2 * ct_x4;
    std::vector<long> gout129 = fvec129(gin129);

    std::vector<RotationPoly> lut130;
    std::vector<long (*)(long)> flut130;
    auto lut130idx0 = [](long I) -> long {
        /* GATE 420 (LUT2 _1876_ INIT 0x8 PERM 10) */
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
    lut130.push_back(ctx.genrate_lut(lut130idx0));
    flut130.push_back(lut130idx0);

    auto fvec130 = [flut130](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut130[i](I));
        return ret;
    };

    std::cerr << "\rLUT130   ";
    long gin130 = 1 * ct_x9 + 2 * ct_y5;
    std::vector<long> gout130 = fvec130(gin130);

    std::vector<RotationPoly> lut131;
    std::vector<long (*)(long)> flut131;
    auto lut131idx0 = [](long I) -> long {
        /* GATE 468 (LUT3 _1924_ INIT 0x78 PERM 210) */
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
    lut131.push_back(ctx.genrate_lut(lut131idx0));
    flut131.push_back(lut131idx0);

    auto fvec131 = [flut131](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut131[i](I));
        return ret;
    };

    std::cerr << "\rLUT131   ";
    long gin131 = 1 * gout99[0] + 2 * ct_x8 + 4 * ct_y7;
    std::vector<long> gout131 = fvec131(gin131);

    std::vector<RotationPoly> lut132;
    std::vector<long (*)(long)> flut132;
    auto lut132idx0 = [](long I) -> long {
        /* GATE 488 (LUT3 _1944_ INIT 0x78 PERM 021) */
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
    lut132.push_back(ctx.genrate_lut(lut132idx0));
    flut132.push_back(lut132idx0);

    auto fvec132 = [flut132](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut132[i](I));
        return ret;
    };

    std::cerr << "\rLUT132   ";
    long gin132 = 1 * ct_y1 + 2 * ct_y15 + 4 * ct_x14;
    std::vector<long> gout132 = fvec132(gin132);

    std::vector<RotationPoly> lut133;
    std::vector<long (*)(long)> flut133;
    auto lut133idx0 = [](long I) -> long {
        /* GATE 487 (LUT3 _1943_ INIT 0x87 PERM 201) */
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
    lut133.push_back(ctx.genrate_lut(lut133idx0));
    flut133.push_back(lut133idx0);

    auto fvec133 = [flut133](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut133[i](I));
        return ret;
    };

    std::cerr << "\rLUT133   ";
    long gin133 = 1 * ct_x15 + 2 * gout132[0] + 4 * ct_y0;
    std::vector<long> gout133 = fvec133(gin133);

    std::vector<RotationPoly> lut134;
    std::vector<long (*)(long)> flut134;
    auto lut134idx0 = [](long I) -> long {
        /* GATE 484 (LUT2 _1940_ INIT 0x6 PERM 01) */
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
    lut134.push_back(ctx.genrate_lut(lut134idx0));
    flut134.push_back(lut134idx0);

    auto fvec134 = [flut134](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut134[i](I));
        return ret;
    };

    std::cerr << "\rLUT134   ";
    long gin134 = 1 * gout74[0] + 2 * gout133[0];
    std::vector<long> gout134 = fvec134(gin134);

    std::vector<RotationPoly> lut135;
    std::vector<long (*)(long)> flut135;
    auto lut135idx0 = [](long I) -> long {
        /* GATE 474 (LUT3 _1930_ INIT 0x87 PERM 012) */
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
    lut135.push_back(ctx.genrate_lut(lut135idx0));
    flut135.push_back(lut135idx0);

    auto fvec135 = [flut135](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut135[i](I));
        return ret;
    };

    std::cerr << "\rLUT135   ";
    long gin135 = 1 * ct_y4 + 2 * ct_x11 + 4 * gout91[1];
    std::vector<long> gout135 = fvec135(gin135);

    std::vector<RotationPoly> lut136;
    std::vector<long (*)(long)> flut136;
    auto lut136idx0 = [](long I) -> long {
        /* GATE 58 (LUT2 _1514_ INIT 0x8 PERM 01) */
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
    lut136.push_back(ctx.genrate_lut(lut136idx0));
    flut136.push_back(lut136idx0);

    auto fvec136 = [flut136](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut136[i](I));
        return ret;
    };

    std::cerr << "\rLUT136   ";
    long gin136 = 1 * ct_y2 + 2 * ct_x2;
    std::vector<long> gout136 = fvec136(gin136);

    std::vector<RotationPoly> lut137;
    std::vector<long (*)(long)> flut137;
    auto lut137idx0 = [](long I) -> long {
        /* GATE 134 (LUT2 _1590_ INIT 0x8 PERM 10) */
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
    long gin137 = 1 * ct_x3 + 2 * ct_y4;
    std::vector<long> gout137 = fvec137(gin137);

    std::vector<RotationPoly> lut138;
    std::vector<long (*)(long)> flut138;
    auto lut138idx0 = [](long I) -> long {
        /* GATE 133 (LUT3 _1589_ INIT 0x96 PERM 012) */
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
    lut138.push_back(ctx.genrate_lut(lut138idx0));
    flut138.push_back(lut138idx0);

    auto lut138idx1 = [](long I) -> long {
        /* GATE 171 (LUT3 _1627_ INIT 0x17 PERM 012) */
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
    lut138.push_back(ctx.genrate_lut(lut138idx1));
    flut138.push_back(lut138idx1);

    auto fvec138 = [flut138](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut138[i](I));
        return ret;
    };

    std::cerr << "\rLUT138   ";
    long gin138 = 1 * gout137[0] + 2 * gout122[0] + 4 * gout53[0];
    std::vector<long> gout138 = fvec138(gin138);

    std::vector<RotationPoly> lut139;
    std::vector<long (*)(long)> flut139;
    auto lut139idx0 = [](long I) -> long {
        /* GATE 158 (LUT3 _1614_ INIT 0x2b PERM 012) */
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
    lut139.push_back(ctx.genrate_lut(lut139idx0));
    flut139.push_back(lut139idx0);

    auto lut139idx1 = [](long I) -> long {
        /* GATE 127 (LUT3 _1583_ INIT 0x69 PERM 012) */
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
    lut139.push_back(ctx.genrate_lut(lut139idx1));
    flut139.push_back(lut139idx1);

    auto fvec139 = [flut139](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut139[i](I));
        return ret;
    };

    std::cerr << "\rLUT139   ";
    long gin139 = 1 * gout112[0] + 2 * gout119[1] + 4 * gout138[0];
    std::vector<long> gout139 = fvec139(gin139);

    std::vector<RotationPoly> lut140;
    std::vector<long (*)(long)> flut140;
    auto lut140idx0 = [](long I) -> long {
        /* GATE 84 (LUT2 _1540_ INIT 0x8 PERM 10) */
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
    lut140.push_back(ctx.genrate_lut(lut140idx0));
    flut140.push_back(lut140idx0);

    auto fvec140 = [flut140](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut140[i](I));
        return ret;
    };

    std::cerr << "\rLUT140   ";
    long gin140 = 1 * gout2[0] + 2 * gout123[0];
    std::vector<long> gout140 = fvec140(gin140);

    std::vector<RotationPoly> lut141;
    std::vector<long (*)(long)> flut141;
    auto lut141idx0 = [](long I) -> long {
        /* GATE 283 (LUT2 _1739_ INIT 0x8 PERM 01) */
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
    lut141.push_back(ctx.genrate_lut(lut141idx0));
    flut141.push_back(lut141idx0);

    auto fvec141 = [flut141](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut141[i](I));
        return ret;
    };

    std::cerr << "\rLUT141   ";
    long gin141 = 1 * ct_y4 + 2 * ct_x7;
    std::vector<long> gout141 = fvec141(gin141);

    std::vector<RotationPoly> lut142;
    std::vector<long (*)(long)> flut142;
    auto lut142idx0 = [](long I) -> long {
        /* GATE 332 (LUT3 _1788_ INIT 0x17 PERM 012) */
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
    lut142.push_back(ctx.genrate_lut(lut142idx0));
    flut142.push_back(lut142idx0);

    auto lut142idx1 = [](long I) -> long {
        /* GATE 282 (LUT3 _1738_ INIT 0x96 PERM 012) */
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
    lut142.push_back(ctx.genrate_lut(lut142idx1));
    flut142.push_back(lut142idx1);

    auto fvec142 = [flut142](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut142[i](I));
        return ret;
    };

    std::cerr << "\rLUT142   ";
    long gin142 = 1 * gout141[0] + 2 * gout121[0] + 4 * gout56[0];
    std::vector<long> gout142 = fvec142(gin142);

    std::vector<RotationPoly> lut143;
    std::vector<long (*)(long)> flut143;
    auto lut143idx0 = [](long I) -> long {
        /* GATE 385 (LUT3 _1841_ INIT 0xb2 PERM 012) */
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
    lut143.push_back(ctx.genrate_lut(lut143idx0));
    flut143.push_back(lut143idx0);

    auto lut143idx1 = [](long I) -> long {
        /* GATE 330 (LUT3 _1786_ INIT 0x96 PERM 021) */
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
    lut143.push_back(ctx.genrate_lut(lut143idx1));
    flut143.push_back(lut143idx1);

    auto fvec143 = [flut143](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut143[i](I));
        return ret;
    };

    std::cerr << "\rLUT143   ";
    long gin143 = 1 * gout80[1] + 2 * gout108[0] + 4 * gout142[0];
    std::vector<long> gout143 = fvec143(gin143);

    std::vector<RotationPoly> lut144;
    std::vector<long (*)(long)> flut144;
    auto lut144idx0 = [](long I) -> long {
        /* GATE 319 (LUT3 _1775_ INIT 0x2b PERM 012) */
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
    lut144.push_back(ctx.genrate_lut(lut144idx0));
    flut144.push_back(lut144idx0);

    auto lut144idx1 = [](long I) -> long {
        /* GATE 276 (LUT3 _1732_ INIT 0x69 PERM 012) */
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
    lut144.push_back(ctx.genrate_lut(lut144idx1));
    flut144.push_back(lut144idx1);

    auto fvec144 = [flut144](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut144[i](I));
        return ret;
    };

    std::cerr << "\rLUT144   ";
    long gin144 = 1 * gout105[0] + 2 * gout97[0] + 4 * gout142[1];
    std::vector<long> gout144 = fvec144(gin144);

    std::vector<RotationPoly> lut145;
    std::vector<long (*)(long)> flut145;
    auto lut145idx0 = [](long I) -> long {
        /* GATE 241 (LUT2 _1697_ INIT 0x8 PERM 01) */
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
    lut145.push_back(ctx.genrate_lut(lut145idx0));
    flut145.push_back(lut145idx0);

    auto fvec145 = [flut145](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut145[i](I));
        return ret;
    };

    std::cerr << "\rLUT145   ";
    long gin145 = 1 * ct_y4 + 2 * ct_x6;
    std::vector<long> gout145 = fvec145(gin145);

    std::vector<RotationPoly> lut146;
    std::vector<long (*)(long)> flut146;
    auto lut146idx0 = [](long I) -> long {
        /* GATE 288 (LUT3 _1744_ INIT 0x17 PERM 012) */
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
    lut146.push_back(ctx.genrate_lut(lut146idx0));
    flut146.push_back(lut146idx0);

    auto lut146idx1 = [](long I) -> long {
        /* GATE 240 (LUT3 _1696_ INIT 0x96 PERM 012) */
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
    lut146.push_back(ctx.genrate_lut(lut146idx1));
    flut146.push_back(lut146idx1);

    auto fvec146 = [flut146](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut146[i](I));
        return ret;
    };

    std::cerr << "\rLUT146   ";
    long gin146 = 1 * gout145[0] + 2 * gout60[0] + 4 * gout24[0];
    std::vector<long> gout146 = fvec146(gin146);

    std::vector<RotationPoly> lut147;
    std::vector<long (*)(long)> flut147;
    auto lut147idx0 = [](long I) -> long {
        /* GATE 275 (LUT3 _1731_ INIT 0x2b PERM 012) */
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
    lut147.push_back(ctx.genrate_lut(lut147idx0));
    flut147.push_back(lut147idx0);

    auto lut147idx1 = [](long I) -> long {
        /* GATE 234 (LUT3 _1690_ INIT 0x69 PERM 012) */
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
    lut147.push_back(ctx.genrate_lut(lut147idx1));
    flut147.push_back(lut147idx1);

    auto fvec147 = [flut147](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut147[i](I));
        return ret;
    };

    std::cerr << "\rLUT147   ";
    long gin147 = 1 * gout64[0] + 2 * gout105[1] + 4 * gout146[1];
    std::vector<long> gout147 = fvec147(gin147);

    std::vector<RotationPoly> lut148;
    std::vector<long (*)(long)> flut148;
    auto lut148idx0 = [](long I) -> long {
        /* GATE 345 (LUT2 _1801_ INIT 0x8 PERM 01) */
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
    lut148.push_back(ctx.genrate_lut(lut148idx0));
    flut148.push_back(lut148idx0);

    auto fvec148 = [flut148](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut148[i](I));
        return ret;
    };

    std::cerr << "\rLUT148   ";
    long gin148 = 1 * ct_y9 + 2 * ct_x3;
    std::vector<long> gout148 = fvec148(gin148);

    std::vector<RotationPoly> lut149;
    std::vector<long (*)(long)> flut149;
    auto lut149idx0 = [](long I) -> long {
        /* GATE 324 (LUT2 _1780_ INIT 0x8 PERM 10) */
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
    lut149.push_back(ctx.genrate_lut(lut149idx0));
    flut149.push_back(lut149idx0);

    auto fvec149 = [flut149](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut149[i](I));
        return ret;
    };

    std::cerr << "\rLUT149   ";
    long gin149 = 1 * ct_x10 + 2 * ct_y2;
    std::vector<long> gout149 = fvec149(gin149);

    std::vector<RotationPoly> lut150;
    std::vector<long (*)(long)> flut150;
    auto lut150idx0 = [](long I) -> long {
        /* GATE 249 (LUT2 _1705_ INIT 0x8 PERM 10) */
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
    lut150.push_back(ctx.genrate_lut(lut150idx0));
    flut150.push_back(lut150idx0);

    auto fvec150 = [flut150](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut150[i](I));
        return ret;
    };

    std::cerr << "\rLUT150   ";
    long gin150 = 1 * ct_x2 + 2 * ct_y8;
    std::vector<long> gout150 = fvec150(gin150);

    std::vector<RotationPoly> lut151;
    std::vector<long (*)(long)> flut151;
    auto lut151idx0 = [](long I) -> long {
        /* GATE 215 (LUT3 _1671_ INIT 0x71 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut151.push_back(ctx.genrate_lut(lut151idx0));
    flut151.push_back(lut151idx0);

    auto lut151idx1 = [](long I) -> long {
        /* GATE 169 (LUT3 _1625_ INIT 0x69 PERM 012) */
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
    lut151.push_back(ctx.genrate_lut(lut151idx1));
    flut151.push_back(lut151idx1);

    auto fvec151 = [flut151](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut151[i](I));
        return ret;
    };

    std::cerr << "\rLUT151   ";
    long gin151 = 1 * gout50[0] + 2 * gout138[1] + 4 * gout36[0];
    std::vector<long> gout151 = fvec151(gin151);

    std::vector<RotationPoly> lut152;
    std::vector<long (*)(long)> flut152;
    auto lut152idx0 = [](long I) -> long {
        /* GATE 255 (LUT3 _1711_ INIT 0x40 PERM 012) */
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
    lut152.push_back(ctx.genrate_lut(lut152idx0));
    flut152.push_back(lut152idx0);

    auto lut152idx1 = [](long I) -> long {
        /* GATE 214 (LUT3 _1670_ INIT 0x87 PERM 120) */
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
    lut152.push_back(ctx.genrate_lut(lut152idx1));
    flut152.push_back(lut152idx1);

    auto fvec152 = [flut152](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut152[i](I));
        return ret;
    };

    std::cerr << "\rLUT152   ";
    long gin152 = 1 * gout151[0] + 2 * ct_y9 + 4 * ct_x0;
    std::vector<long> gout152 = fvec152(gin152);

    std::vector<RotationPoly> lut153;
    std::vector<long (*)(long)> flut153;
    auto lut153idx0 = [](long I) -> long {
        /* GATE 78 (LUT2 _1534_ INIT 0x8 PERM 01) */
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
    long gin153 = 1 * ct_y2 + 2 * ct_x3;
    std::vector<long> gout153 = fvec153(gin153);

    std::vector<RotationPoly> lut154;
    std::vector<long (*)(long)> flut154;
    auto lut154idx0 = [](long I) -> long {
        /* GATE 419 (LUT2 _1875_ INIT 0x8 PERM 10) */
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
    lut154.push_back(ctx.genrate_lut(lut154idx0));
    flut154.push_back(lut154idx0);

    auto fvec154 = [flut154](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut154[i](I));
        return ret;
    };

    std::cerr << "\rLUT154   ";
    long gin154 = 1 * ct_x10 + 2 * ct_y4;
    std::vector<long> gout154 = fvec154(gin154);

    std::vector<RotationPoly> lut155;
    std::vector<long (*)(long)> flut155;
    auto lut155idx0 = [](long I) -> long {
        /* GATE 471 (LUT3 _1927_ INIT 0x17 PERM 012) */
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
    lut155.push_back(ctx.genrate_lut(lut155idx0));
    flut155.push_back(lut155idx0);

    auto lut155idx1 = [](long I) -> long {
        /* GATE 418 (LUT3 _1874_ INIT 0x96 PERM 012) */
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
    lut155.push_back(ctx.genrate_lut(lut155idx1));
    flut155.push_back(lut155idx1);

    auto fvec155 = [flut155](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut155[i](I));
        return ret;
    };

    std::cerr << "\rLUT155   ";
    long gin155 = 1 * gout154[0] + 2 * gout130[0] + 4 * gout120[0];
    std::vector<long> gout155 = fvec155(gin155);

    std::vector<RotationPoly> lut156;
    std::vector<long (*)(long)> flut156;
    auto lut156idx0 = [](long I) -> long {
        /* GATE 325 (LUT2 _1781_ INIT 0x8 PERM 01) */
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
    lut156.push_back(ctx.genrate_lut(lut156idx0));
    flut156.push_back(lut156idx0);

    auto fvec156 = [flut156](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut156[i](I));
        return ret;
    };

    std::cerr << "\rLUT156   ";
    long gin156 = 1 * ct_y0 + 2 * ct_x12;
    std::vector<long> gout156 = fvec156(gin156);

    std::vector<RotationPoly> lut157;
    std::vector<long (*)(long)> flut157;
    auto lut157idx0 = [](long I) -> long {
        /* GATE 483 (LUT3 _1939_ INIT 0x2b PERM 012) */
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
    lut157.push_back(ctx.genrate_lut(lut157idx0));
    flut157.push_back(lut157idx0);

    auto lut157idx1 = [](long I) -> long {
        /* GATE 412 (LUT3 _1868_ INIT 0x69 PERM 012) */
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
    lut157.push_back(ctx.genrate_lut(lut157idx1));
    flut157.push_back(lut157idx1);

    auto fvec157 = [flut157](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut157[i](I));
        return ret;
    };

    std::cerr << "\rLUT157   ";
    long gin157 = 1 * gout52[1] + 2 * gout91[0] + 4 * gout155[1];
    std::vector<long> gout157 = fvec157(gin157);

    std::vector<RotationPoly> lut158;
    std::vector<long (*)(long)> flut158;
    auto lut158idx0 = [](long I) -> long {
        /* GATE 57 (LUT2 _1513_ INIT 0x8 PERM 10) */
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
    long gin158 = 1 * ct_x3 + 2 * ct_y1;
    std::vector<long> gout158 = fvec158(gin158);

    std::vector<RotationPoly> lut159;
    std::vector<long (*)(long)> flut159;
    auto lut159idx0 = [](long I) -> long {
        /* GATE 75 (LUT3 _1531_ INIT 0x17 PERM 012) */
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
    lut159.push_back(ctx.genrate_lut(lut159idx0));
    flut159.push_back(lut159idx0);

    auto lut159idx1 = [](long I) -> long {
        /* GATE 56 (LUT3 _1512_ INIT 0x96 PERM 012) */
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
    lut159.push_back(ctx.genrate_lut(lut159idx1));
    flut159.push_back(lut159idx1);

    auto fvec159 = [flut159](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut159[i](I));
        return ret;
    };

    std::cerr << "\rLUT159   ";
    long gin159 = 1 * gout158[0] + 2 * gout136[0] + 4 * gout71[0];
    std::vector<long> gout159 = fvec159(gin159);

    std::vector<RotationPoly> lut160;
    std::vector<long (*)(long)> flut160;
    auto lut160idx0 = [](long I) -> long {
        /* GATE 73 (LUT3 _1529_ INIT 0x2b PERM 012) */
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
    lut160.push_back(ctx.genrate_lut(lut160idx0));
    flut160.push_back(lut160idx0);

    auto lut160idx1 = [](long I) -> long {
        /* GATE 54 (LUT3 _1510_ INIT 0x69 PERM 012) */
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
    lut160.push_back(ctx.genrate_lut(lut160idx1));
    flut160.push_back(lut160idx1);

    auto fvec160 = [flut160](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut160[i](I));
        return ret;
    };

    std::cerr << "\rLUT160   ";
    long gin160 = 1 * gout116[0] + 2 * gout159[1] + 4 * gout102[0];
    std::vector<long> gout160 = fvec160(gin160);

    std::vector<RotationPoly> lut161;
    std::vector<long (*)(long)> flut161;
    auto lut161idx0 = [](long I) -> long {
        /* GATE 344 (LUT2 _1800_ INIT 0x8 PERM 01) */
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
    lut161.push_back(ctx.genrate_lut(lut161idx0));
    flut161.push_back(lut161idx0);

    auto fvec161 = [flut161](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut161[i](I));
        return ret;
    };

    std::cerr << "\rLUT161   ";
    long gin161 = 1 * ct_y11 + 2 * ct_x1;
    std::vector<long> gout161 = fvec161(gin161);

    std::vector<RotationPoly> lut162;
    std::vector<long (*)(long)> flut162;
    auto lut162idx0 = [](long I) -> long {
        /* GATE 323 (LUT2 _1779_ INIT 0x8 PERM 10) */
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
    lut162.push_back(ctx.genrate_lut(lut162idx0));
    flut162.push_back(lut162idx0);

    auto fvec162 = [flut162](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut162[i](I));
        return ret;
    };

    std::cerr << "\rLUT162   ";
    long gin162 = 1 * ct_x11 + 2 * ct_y1;
    std::vector<long> gout162 = fvec162(gin162);

    std::vector<RotationPoly> lut163;
    std::vector<long (*)(long)> flut163;
    auto lut163idx0 = [](long I) -> long {
        /* GATE 322 (LUT3 _1778_ INIT 0x96 PERM 012) */
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
    lut163.push_back(ctx.genrate_lut(lut163idx0));
    flut163.push_back(lut163idx0);

    auto lut163idx1 = [](long I) -> long {
        /* GATE 367 (LUT3 _1823_ INIT 0x17 PERM 012) */
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
    lut163.push_back(ctx.genrate_lut(lut163idx1));
    flut163.push_back(lut163idx1);

    auto fvec163 = [flut163](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut163[i](I));
        return ret;
    };

    std::cerr << "\rLUT163   ";
    long gin163 = 1 * gout162[0] + 2 * gout149[0] + 4 * gout156[0];
    std::vector<long> gout163 = fvec163(gin163);

    std::vector<RotationPoly> lut164;
    std::vector<long (*)(long)> flut164;
    auto lut164idx0 = [](long I) -> long {
        /* GATE 365 (LUT3 _1821_ INIT 0x2b PERM 012) */
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
    lut164.push_back(ctx.genrate_lut(lut164idx0));
    flut164.push_back(lut164idx0);

    auto lut164idx1 = [](long I) -> long {
        /* GATE 320 (LUT3 _1776_ INIT 0x69 PERM 012) */
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
    lut164.push_back(ctx.genrate_lut(lut164idx1));
    flut164.push_back(lut164idx1);

    auto fvec164 = [flut164](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut164[i](I));
        return ret;
    };

    std::cerr << "\rLUT164   ";
    long gin164 = 1 * gout97[1] + 2 * gout163[0] + 4 * gout63[1];
    std::vector<long> gout164 = fvec164(gin164);

    std::vector<RotationPoly> lut165;
    std::vector<long (*)(long)> flut165;
    auto lut165idx0 = [](long I) -> long {
        /* GATE 363 (LUT3 _1819_ INIT 0x2b PERM 012) */
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
    lut165.push_back(ctx.genrate_lut(lut165idx0));
    flut165.push_back(lut165idx0);

    auto lut165idx1 = [](long I) -> long {
        /* GATE 318 (LUT3 _1774_ INIT 0x69 PERM 012) */
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
    lut165.push_back(ctx.genrate_lut(lut165idx1));
    flut165.push_back(lut165idx1);

    auto fvec165 = [flut165](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut165[i](I));
        return ret;
    };

    std::cerr << "\rLUT165   ";
    long gin165 = 1 * gout144[0] + 2 * gout164[1] + 4 * gout143[1];
    std::vector<long> gout165 = fvec165(gin165);

    std::vector<RotationPoly> lut166;
    std::vector<long (*)(long)> flut166;
    auto lut166idx0 = [](long I) -> long {
        /* GATE 248 (LUT2 _1704_ INIT 0x8 PERM 01) */
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
    lut166.push_back(ctx.genrate_lut(lut166idx0));
    flut166.push_back(lut166idx0);

    auto fvec166 = [flut166](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut166[i](I));
        return ret;
    };

    std::cerr << "\rLUT166   ";
    long gin166 = 1 * ct_y7 + 2 * ct_x3;
    std::vector<long> gout166 = fvec166(gin166);

    std::vector<RotationPoly> lut167;
    std::vector<long (*)(long)> flut167;
    auto lut167idx0 = [](long I) -> long {
        /* GATE 287 (LUT3 _1743_ INIT 0x17 PERM 012) */
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
    lut167.push_back(ctx.genrate_lut(lut167idx0));
    flut167.push_back(lut167idx0);

    auto lut167idx1 = [](long I) -> long {
        /* GATE 247 (LUT3 _1703_ INIT 0x96 PERM 012) */
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
    lut167.push_back(ctx.genrate_lut(lut167idx1));
    flut167.push_back(lut167idx1);

    auto fvec167 = [flut167](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut167[i](I));
        return ret;
    };

    std::cerr << "\rLUT167   ";
    long gin167 = 1 * gout166[0] + 2 * gout150[0] + 4 * gout129[0];
    std::vector<long> gout167 = fvec167(gin167);

    std::vector<RotationPoly> lut168;
    std::vector<long (*)(long)> flut168;
    auto lut168idx0 = [](long I) -> long {
        /* GATE 339 (LUT3 _1795_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut168.push_back(ctx.genrate_lut(lut168idx0));
    flut168.push_back(lut168idx0);

    auto lut168idx1 = [](long I) -> long {
        /* GATE 286 (LUT3 _1742_ INIT 0x96 PERM 012) */
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
    lut168.push_back(ctx.genrate_lut(lut168idx1));
    flut168.push_back(lut168idx1);

    auto fvec168 = [flut168](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut168[i](I));
        return ret;
    };

    std::cerr << "\rLUT168   ";
    long gin168 = 1 * gout167[0] + 2 * gout146[0] + 4 * gout80[0];
    std::vector<long> gout168 = fvec168(gin168);

    std::vector<RotationPoly> lut169;
    std::vector<long (*)(long)> flut169;
    auto lut169idx0 = [](long I) -> long {
        /* GATE 317 (LUT3 _1773_ INIT 0x2b PERM 012) */
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
        /* GATE 274 (LUT3 _1730_ INIT 0x69 PERM 012) */
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
    long gin169 = 1 * gout147[0] + 2 * gout144[1] + 4 * gout168[1];
    std::vector<long> gout169 = fvec169(gin169);

    std::vector<RotationPoly> lut170;
    std::vector<long (*)(long)> flut170;
    auto lut170idx0 = [](long I) -> long {
        /* GATE 77 (LUT2 _1533_ INIT 0x8 PERM 10) */
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
    long gin170 = 1 * ct_x4 + 2 * ct_y1;
    std::vector<long> gout170 = fvec170(gin170);

    std::vector<RotationPoly> lut171;
    std::vector<long (*)(long)> flut171;
    auto lut171idx0 = [](long I) -> long {
        /* GATE 100 (LUT3 _1556_ INIT 0x17 PERM 012) */
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
        /* GATE 76 (LUT3 _1532_ INIT 0x96 PERM 012) */
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
    long gin171 = 1 * gout170[0] + 2 * gout153[0] + 4 * gout23[0];
    std::vector<long> gout171 = fvec171(gin171);

    std::vector<RotationPoly> lut172;
    std::vector<long (*)(long)> flut172;
    auto lut172idx0 = [](long I) -> long {
        /* GATE 106 (LUT2 _1562_ INIT 0x8 PERM 01) */
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
    long gin172 = 1 * ct_y4 + 2 * ct_x2;
    std::vector<long> gout172 = fvec172(gin172);

    std::vector<RotationPoly> lut173;
    std::vector<long (*)(long)> flut173;
    auto lut173idx0 = [](long I) -> long {
        /* GATE 138 (LUT3 _1594_ INIT 0x17 PERM 012) */
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
        /* GATE 105 (LUT3 _1561_ INIT 0x96 PERM 012) */
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
    long gin173 = 1 * gout172[0] + 2 * gout58[0] + 4 * gout45[0];
    std::vector<long> gout173 = fvec173(gin173);

    std::vector<RotationPoly> lut174;
    std::vector<long (*)(long)> flut174;
    auto lut174idx0 = [](long I) -> long {
        /* GATE 176 (LUT2 _1632_ INIT 0x4 PERM 01) */
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
    lut174.push_back(ctx.genrate_lut(lut174idx0));
    flut174.push_back(lut174idx0);

    auto lut174idx1 = [](long I) -> long {
        /* GATE 137 (LUT2 _1593_ INIT 0x9 PERM 01) */
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
    lut174.push_back(ctx.genrate_lut(lut174idx1));
    flut174.push_back(lut174idx1);

    auto fvec174 = [flut174](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut174[i](I));
        return ret;
    };

    std::cerr << "\rLUT174   ";
    long gin174 = 1 * gout173[0] + 2 * gout50[1];
    std::vector<long> gout174 = fvec174(gin174);

    std::vector<RotationPoly> lut175;
    std::vector<long (*)(long)> flut175;
    auto lut175idx0 = [](long I) -> long {
        /* GATE 126 (LUT3 _1582_ INIT 0x2b PERM 012) */
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
    lut175.push_back(ctx.genrate_lut(lut175idx0));
    flut175.push_back(lut175idx0);

    auto lut175idx1 = [](long I) -> long {
        /* GATE 99 (LUT3 _1555_ INIT 0x69 PERM 012) */
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
    lut175.push_back(ctx.genrate_lut(lut175idx1));
    flut175.push_back(lut175idx1);

    auto fvec175 = [flut175](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut175[i](I));
        return ret;
    };

    std::cerr << "\rLUT175   ";
    long gin175 = 1 * gout171[0] + 2 * gout112[1] + 4 * gout173[1];
    std::vector<long> gout175 = fvec175(gin175);

    std::vector<RotationPoly> lut176;
    std::vector<long (*)(long)> flut176;
    auto lut176idx0 = [](long I) -> long {
        /* GATE 156 (LUT3 _1612_ INIT 0x2b PERM 012) */
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
    lut176.push_back(ctx.genrate_lut(lut176idx0));
    flut176.push_back(lut176idx0);

    auto lut176idx1 = [](long I) -> long {
        /* GATE 125 (LUT3 _1581_ INIT 0x69 PERM 012) */
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
    lut176.push_back(ctx.genrate_lut(lut176idx1));
    flut176.push_back(lut176idx1);

    auto fvec176 = [flut176](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut176[i](I));
        return ret;
    };

    std::cerr << "\rLUT176   ";
    long gin176 = 1 * gout175[0] + 2 * gout139[1] + 4 * gout174[1];
    std::vector<long> gout176 = fvec176(gin176);

    std::vector<RotationPoly> lut177;
    std::vector<long (*)(long)> flut177;
    auto lut177idx0 = [](long I) -> long {
        /* GATE 53 (LUT3 _1509_ INIT 0x2b PERM 012) */
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
    lut177.push_back(ctx.genrate_lut(lut177idx0));
    flut177.push_back(lut177idx0);

    auto lut177idx1 = [](long I) -> long {
        /* GATE 37 (LUT3 _1493_ INIT 0x69 PERM 012) */
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
    lut177.push_back(ctx.genrate_lut(lut177idx1));
    flut177.push_back(lut177idx1);

    auto fvec177 = [flut177](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut177[i](I));
        return ret;
    };

    std::cerr << "\rLUT177   ";
    long gin177 = 1 * gout44[1] + 2 * gout116[1] + 4 * gout123[0];
    std::vector<long> gout177 = fvec177(gin177);

    std::vector<RotationPoly> lut178;
    std::vector<long (*)(long)> flut178;
    auto lut178idx0 = [](long I) -> long {
        /* GATE 71 (LUT2 _1527_ INIT 0x4 PERM 01) */
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
    lut178.push_back(ctx.genrate_lut(lut178idx0));
    flut178.push_back(lut178idx0);

    auto lut178idx1 = [](long I) -> long {
        /* GATE 52 (LUT2 _1508_ INIT 0x9 PERM 01) */
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
    lut178.push_back(ctx.genrate_lut(lut178idx1));
    flut178.push_back(lut178idx1);

    auto fvec178 = [flut178](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut178[i](I));
        return ret;
    };

    std::cerr << "\rLUT178   ";
    long gin178 = 1 * gout177[0] + 2 * gout160[1];
    std::vector<long> gout178 = fvec178(gin178);

    std::vector<RotationPoly> lut179;
    std::vector<long (*)(long)> flut179;
    auto lut179idx0 = [](long I) -> long {
        /* GATE 184 (LUT3 _1640_ INIT 0x10 PERM 120) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut179.push_back(ctx.genrate_lut(lut179idx0));
    flut179.push_back(lut179idx0);

    auto fvec179 = [flut179](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut179[i](I));
        return ret;
    };

    std::cerr << "\rLUT179   ";
    long gin179 = 1 * gout88[0] + 2 * ct_y7 + 4 * ct_y8;
    std::vector<long> gout179 = fvec179(gin179);

    std::vector<RotationPoly> lut180;
    std::vector<long (*)(long)> flut180;
    auto lut180idx0 = [](long I) -> long {
        /* GATE 262 (LUT3 _1718_ INIT 0x10 PERM 120) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut180.push_back(ctx.genrate_lut(lut180idx0));
    flut180.push_back(lut180idx0);

    auto fvec180 = [flut180](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut180[i](I));
        return ret;
    };

    std::cerr << "\rLUT180   ";
    long gin180 = 1 * gout179[0] + 2 * ct_y9 + 4 * ct_y10;
    std::vector<long> gout180 = fvec180(gin180);

    std::vector<RotationPoly> lut181;
    std::vector<long (*)(long)> flut181;
    auto lut181idx0 = [](long I) -> long {
        /* GATE 461 (LUT3 _1917_ INIT 0x87 PERM 012) */
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
    lut181.push_back(ctx.genrate_lut(lut181idx0));
    flut181.push_back(lut181idx0);

    auto fvec181 = [flut181](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut181[i](I));
        return ret;
    };

    std::cerr << "\rLUT181   ";
    long gin181 = 1 * ct_y11 + 2 * ct_x4 + 4 * gout4[0];
    std::vector<long> gout181 = fvec181(gin181);

    std::vector<RotationPoly> lut182;
    std::vector<long (*)(long)> flut182;
    auto lut182idx0 = [](long I) -> long {
        /* GATE 457 (LUT2 _1913_ INIT 0x9 PERM 01) */
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
    lut182.push_back(ctx.genrate_lut(lut182idx0));
    flut182.push_back(lut182idx0);

    auto fvec182 = [flut182](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut182[i](I));
        return ret;
    };

    std::cerr << "\rLUT182   ";
    long gin182 = 1 * gout113[0] + 2 * gout181[0];
    std::vector<long> gout182 = fvec182(gin182);

    std::vector<RotationPoly> lut183;
    std::vector<long (*)(long)> flut183;
    auto lut183idx0 = [](long I) -> long {
        /* GATE 343 (LUT2 _1799_ INIT 0x8 PERM 10) */
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
    long gin183 = 1 * ct_x2 + 2 * ct_y10;
    std::vector<long> gout183 = fvec183(gin183);

    std::vector<RotationPoly> lut184;
    std::vector<long (*)(long)> flut184;
    auto lut184idx0 = [](long I) -> long {
        /* GATE 387 (LUT3 _1843_ INIT 0x17 PERM 012) */
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
        /* GATE 342 (LUT3 _1798_ INIT 0x96 PERM 012) */
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
    long gin184 = 1 * gout183[0] + 2 * gout161[0] + 4 * gout148[0];
    std::vector<long> gout184 = fvec184(gin184);

    std::vector<RotationPoly> lut185;
    std::vector<long (*)(long)> flut185;
    auto lut185idx0 = [](long I) -> long {
        /* GATE 430 (LUT3 _1886_ INIT 0x2b PERM 012) */
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
    lut185.push_back(ctx.genrate_lut(lut185idx0));
    flut185.push_back(lut185idx0);

    auto lut185idx1 = [](long I) -> long {
        /* GATE 386 (LUT3 _1842_ INIT 0x69 PERM 012) */
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
    lut185.push_back(ctx.genrate_lut(lut185idx1));
    flut185.push_back(lut185idx1);

    auto fvec185 = [flut185](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut185[i](I));
        return ret;
    };

    std::cerr << "\rLUT185   ";
    long gin185 = 1 * gout184[0] + 2 * gout39[0] + 4 * gout42[0];
    std::vector<long> gout185 = fvec185(gin185);

    std::vector<RotationPoly> lut186;
    std::vector<long (*)(long)> flut186;
    auto lut186idx0 = [](long I) -> long {
        /* GATE 340 (LUT3 _1796_ INIT 0x69 PERM 012) */
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
    lut186.push_back(ctx.genrate_lut(lut186idx0));
    flut186.push_back(lut186idx0);

    auto lut186idx1 = [](long I) -> long {
        /* GATE 384 (LUT3 _1840_ INIT 0x2b PERM 012) */
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
    lut186.push_back(ctx.genrate_lut(lut186idx1));
    flut186.push_back(lut186idx1);

    auto fvec186 = [flut186](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut186[i](I));
        return ret;
    };

    std::cerr << "\rLUT186   ";
    long gin186 = 1 * gout61[1] + 2 * gout184[1] + 4 * gout127[0];
    std::vector<long> gout186 = fvec186(gin186);

    std::vector<RotationPoly> lut187;
    std::vector<long (*)(long)> flut187;
    auto lut187idx0 = [](long I) -> long {
        /* GATE 394 (LUT3 _1850_ INIT 0x71 PERM 012) */
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
    lut187.push_back(ctx.genrate_lut(lut187idx0));
    flut187.push_back(lut187idx0);

    auto lut187idx1 = [](long I) -> long {
        /* GATE 337 (LUT3 _1793_ INIT 0x69 PERM 021) */
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
    lut187.push_back(ctx.genrate_lut(lut187idx1));
    flut187.push_back(lut187idx1);

    auto fvec187 = [flut187](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut187[i](I));
        return ret;
    };

    std::cerr << "\rLUT187   ";
    long gin187 = 1 * gout70[0] + 2 * gout186[0] + 4 * gout168[0];
    std::vector<long> gout187 = fvec187(gin187);

    std::vector<RotationPoly> lut188;
    std::vector<long (*)(long)> flut188;
    auto lut188idx0 = [](long I) -> long {
        /* GATE 361 (LUT3 _1817_ INIT 0x2b PERM 012) */
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
    lut188.push_back(ctx.genrate_lut(lut188idx0));
    flut188.push_back(lut188idx0);

    auto lut188idx1 = [](long I) -> long {
        /* GATE 316 (LUT3 _1772_ INIT 0x69 PERM 012) */
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
    lut188.push_back(ctx.genrate_lut(lut188idx1));
    flut188.push_back(lut188idx1);

    auto fvec188 = [flut188](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut188[i](I));
        return ret;
    };

    std::cerr << "\rLUT188   ";
    long gin188 = 1 * gout169[0] + 2 * gout165[1] + 4 * gout187[1];
    std::vector<long> gout188 = fvec188(gin188);

    std::vector<RotationPoly> lut189;
    std::vector<long (*)(long)> flut189;
    auto lut189idx0 = [](long I) -> long {
        /* GATE 206 (LUT2 _1662_ INIT 0x8 PERM 01) */
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
    long gin189 = 1 * ct_y3 + 2 * ct_x6;
    std::vector<long> gout189 = fvec189(gin189);

    std::vector<RotationPoly> lut190;
    std::vector<long (*)(long)> flut190;
    auto lut190idx0 = [](long I) -> long {
        /* GATE 246 (LUT3 _1702_ INIT 0x17 PERM 012) */
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
    lut190.push_back(ctx.genrate_lut(lut190idx0));
    flut190.push_back(lut190idx0);

    auto lut190idx1 = [](long I) -> long {
        /* GATE 203 (LUT3 _1659_ INIT 0x96 PERM 012) */
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
    lut190.push_back(ctx.genrate_lut(lut190idx1));
    flut190.push_back(lut190idx1);

    auto fvec190 = [flut190](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut190[i](I));
        return ret;
    };

    std::cerr << "\rLUT190   ";
    long gin190 = 1 * gout29[0] + 2 * gout13[0] + 4 * gout189[0];
    std::vector<long> gout190 = fvec190(gin190);

    std::vector<RotationPoly> lut191;
    std::vector<long (*)(long)> flut191;
    auto lut191idx0 = [](long I) -> long {
        /* GATE 164 (LUT2 _1620_ INIT 0x8 PERM 10) */
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
    lut191.push_back(ctx.genrate_lut(lut191idx0));
    flut191.push_back(lut191idx0);

    auto fvec191 = [flut191](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut191[i](I));
        return ret;
    };

    std::cerr << "\rLUT191   ";
    long gin191 = 1 * ct_x8 + 2 * ct_y0;
    std::vector<long> gout191 = fvec191(gin191);

    std::vector<RotationPoly> lut192;
    std::vector<long (*)(long)> flut192;
    auto lut192idx0 = [](long I) -> long {
        /* GATE 198 (LUT3 _1654_ INIT 0x17 PERM 012) */
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
    lut192.push_back(ctx.genrate_lut(lut192idx0));
    flut192.push_back(lut192idx0);

    auto lut192idx1 = [](long I) -> long {
        /* GATE 161 (LUT3 _1617_ INIT 0x96 PERM 012) */
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
    lut192.push_back(ctx.genrate_lut(lut192idx1));
    flut192.push_back(lut192idx1);

    auto fvec192 = [flut192](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut192[i](I));
        return ret;
    };

    std::cerr << "\rLUT192   ";
    long gin192 = 1 * gout22[0] + 2 * gout7[0] + 4 * gout191[0];
    std::vector<long> gout192 = fvec192(gin192);

    std::vector<RotationPoly> lut193;
    std::vector<long (*)(long)> flut193;
    auto lut193idx0 = [](long I) -> long {
        /* GATE 233 (LUT3 _1689_ INIT 0x2b PERM 012) */
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
    lut193.push_back(ctx.genrate_lut(lut193idx0));
    flut193.push_back(lut193idx0);

    auto lut193idx1 = [](long I) -> long {
        /* GATE 197 (LUT3 _1653_ INIT 0x69 PERM 012) */
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
    lut193.push_back(ctx.genrate_lut(lut193idx1));
    flut193.push_back(lut193idx1);

    auto fvec193 = [flut193](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut193[i](I));
        return ret;
    };

    std::cerr << "\rLUT193   ";
    long gin193 = 1 * gout192[0] + 2 * gout64[1] + 4 * gout190[1];
    std::vector<long> gout193 = fvec193(gin193);

    std::vector<RotationPoly> lut194;
    std::vector<long (*)(long)> flut194;
    auto lut194idx0 = [](long I) -> long {
        /* GATE 196 (LUT3 _1652_ INIT 0x2b PERM 012) */
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
    lut194.push_back(ctx.genrate_lut(lut194idx0));
    flut194.push_back(lut194idx0);

    auto lut194idx1 = [](long I) -> long {
        /* GATE 159 (LUT3 _1615_ INIT 0x69 PERM 012) */
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
    lut194.push_back(ctx.genrate_lut(lut194idx1));
    flut194.push_back(lut194idx1);

    auto fvec194 = [flut194](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut194[i](I));
        return ret;
    };

    std::cerr << "\rLUT194   ";
    long gin194 = 1 * gout119[0] + 2 * gout192[1] + 4 * gout94[1];
    std::vector<long> gout194 = fvec194(gin194);

    std::vector<RotationPoly> lut195;
    std::vector<long (*)(long)> flut195;
    auto lut195idx0 = [](long I) -> long {
        /* GATE 194 (LUT3 _1650_ INIT 0x2b PERM 012) */
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
    lut195.push_back(ctx.genrate_lut(lut195idx0));
    flut195.push_back(lut195idx0);

    auto lut195idx1 = [](long I) -> long {
        /* GATE 157 (LUT3 _1613_ INIT 0x69 PERM 012) */
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
    long gin195 = 1 * gout139[0] + 2 * gout194[1] + 4 * gout151[1];
    std::vector<long> gout195 = fvec195(gin195);

    std::vector<RotationPoly> lut196;
    std::vector<long (*)(long)> flut196;
    auto lut196idx0 = [](long I) -> long {
        /* GATE 192 (LUT3 _1648_ INIT 0x2b PERM 012) */
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
    lut196.push_back(ctx.genrate_lut(lut196idx0));
    flut196.push_back(lut196idx0);

    auto lut196idx1 = [](long I) -> long {
        /* GATE 155 (LUT3 _1611_ INIT 0x69 PERM 012) */
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
    lut196.push_back(ctx.genrate_lut(lut196idx1));
    flut196.push_back(lut196idx1);

    auto fvec196 = [flut196](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut196[i](I));
        return ret;
    };

    std::cerr << "\rLUT196   ";
    long gin196 = 1 * gout176[0] + 2 * gout195[1] + 4 * gout174[0];
    std::vector<long> gout196 = fvec196(gin196);

    std::vector<RotationPoly> lut197;
    std::vector<long (*)(long)> flut197;
    auto lut197idx0 = [](long I) -> long {
        /* GATE 210 (LUT3 _1666_ INIT 0x96 PERM 012) */
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
    lut197.push_back(ctx.genrate_lut(lut197idx0));
    flut197.push_back(lut197idx0);

    auto lut197idx1 = [](long I) -> long {
        /* GATE 245 (LUT3 _1701_ INIT 0x17 PERM 012) */
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
    lut197.push_back(ctx.genrate_lut(lut197idx1));
    flut197.push_back(lut197idx1);

    auto fvec197 = [flut197](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut197[i](I));
        return ret;
    };

    std::cerr << "\rLUT197   ";
    long gin197 = 1 * gout67[0] + 2 * gout59[0] + 4 * gout110[0];
    std::vector<long> gout197 = fvec197(gin197);

    std::vector<RotationPoly> lut198;
    std::vector<long (*)(long)> flut198;
    auto lut198idx0 = [](long I) -> long {
        /* GATE 252 (LUT3 _1708_ INIT 0xb2 PERM 012) */
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
    lut198.push_back(ctx.genrate_lut(lut198idx0));
    flut198.push_back(lut198idx0);

    auto lut198idx1 = [](long I) -> long {
        /* GATE 207 (LUT3 _1663_ INIT 0x96 PERM 021) */
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
    lut198.push_back(ctx.genrate_lut(lut198idx1));
    flut198.push_back(lut198idx1);

    auto fvec198 = [flut198](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut198[i](I));
        return ret;
    };

    std::cerr << "\rLUT198   ";
    long gin198 = 1 * gout36[1] + 2 * gout197[0] + 4 * gout94[0];
    std::vector<long> gout198 = fvec198(gin198);

    std::vector<RotationPoly> lut199;
    std::vector<long (*)(long)> flut199;
    auto lut199idx0 = [](long I) -> long {
        /* GATE 301 (LUT2 _1757_ INIT 0x4 PERM 01) */
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
    lut199.push_back(ctx.genrate_lut(lut199idx0));
    flut199.push_back(lut199idx0);

    auto lut199idx1 = [](long I) -> long {
        /* GATE 251 (LUT2 _1707_ INIT 0x9 PERM 01) */
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
    lut199.push_back(ctx.genrate_lut(lut199idx1));
    flut199.push_back(lut199idx1);

    auto fvec199 = [flut199](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut199[i](I));
        return ret;
    };

    std::cerr << "\rLUT199   ";
    long gin199 = 1 * gout198[0] + 2 * gout69[0];
    std::vector<long> gout199 = fvec199(gin199);

    std::vector<RotationPoly> lut200;
    std::vector<long (*)(long)> flut200;
    auto lut200idx0 = [](long I) -> long {
        /* GATE 231 (LUT3 _1687_ INIT 0x2b PERM 012) */
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
    lut200.push_back(ctx.genrate_lut(lut200idx0));
    flut200.push_back(lut200idx0);

    auto lut200idx1 = [](long I) -> long {
        /* GATE 195 (LUT3 _1651_ INIT 0x69 PERM 012) */
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
    lut200.push_back(ctx.genrate_lut(lut200idx1));
    flut200.push_back(lut200idx1);

    auto fvec200 = [flut200](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut200[i](I));
        return ret;
    };

    std::cerr << "\rLUT200   ";
    long gin200 = 1 * gout194[0] + 2 * gout193[1] + 4 * gout198[1];
    std::vector<long> gout200 = fvec200(gin200);

    std::vector<RotationPoly> lut201;
    std::vector<long (*)(long)> flut201;
    auto lut201idx0 = [](long I) -> long {
        /* GATE 83 (LUT2 _1539_ INIT 0x8 PERM 01) */
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
    long gin201 = 1 * ct_y3 + 2 * ct_x2;
    std::vector<long> gout201 = fvec201(gin201);

    std::vector<RotationPoly> lut202;
    std::vector<long (*)(long)> flut202;
    auto lut202idx0 = [](long I) -> long {
        /* GATE 443 (LUT3 _1899_ INIT 0xb2 PERM 012) */
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
    lut202.push_back(ctx.genrate_lut(lut202idx0));
    flut202.push_back(lut202idx0);

    auto lut202idx1 = [](long I) -> long {
        /* GATE 383 (LUT3 _1839_ INIT 0x96 PERM 021) */
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
    long gin202 = 1 * gout186[1] + 2 * gout185[1] + 4 * gout143[0];
    std::vector<long> gout202 = fvec202(gin202);

    std::vector<RotationPoly> lut203;
    std::vector<long (*)(long)> flut203;
    auto lut203idx0 = [](long I) -> long {
        /* GATE 490 (LUT2 _1946_ INIT 0x4 PERM 01) */
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
    lut203.push_back(ctx.genrate_lut(lut203idx0));
    flut203.push_back(lut203idx0);

    auto lut203idx1 = [](long I) -> long {
        /* GATE 442 (LUT2 _1898_ INIT 0x9 PERM 01) */
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
    lut203.push_back(ctx.genrate_lut(lut203idx1));
    flut203.push_back(lut203idx1);

    auto fvec203 = [flut203](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut203[i](I));
        return ret;
    };

    std::cerr << "\rLUT203   ";
    long gin203 = 1 * gout202[0] + 2 * gout128[0];
    std::vector<long> gout203 = fvec203(gin203);

    std::vector<RotationPoly> lut204;
    std::vector<long (*)(long)> flut204;
    auto lut204idx0 = [](long I) -> long {
        /* GATE 428 (LUT2 _1884_ INIT 0x8 PERM 01) */
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
    lut204.push_back(ctx.genrate_lut(lut204idx0));
    flut204.push_back(lut204idx0);

    auto fvec204 = [flut204](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut204[i](I));
        return ret;
    };

    std::cerr << "\rLUT204   ";
    long gin204 = 1 * ct_y6 + 2 * ct_x8;
    std::vector<long> gout204 = fvec204(gin204);

    std::vector<RotationPoly> lut205;
    std::vector<long (*)(long)> flut205;
    auto lut205idx0 = [](long I) -> long {
        /* GATE 411 (LUT3 _1867_ INIT 0x2b PERM 012) */
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
        /* GATE 366 (LUT3 _1822_ INIT 0x69 PERM 012) */
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
    long gin205 = 1 * gout163[1] + 2 * gout52[0] + 4 * gout101[0];
    std::vector<long> gout205 = fvec205(gin205);

    std::vector<RotationPoly> lut206;
    std::vector<long (*)(long)> flut206;
    auto lut206idx0 = [](long I) -> long {
        /* GATE 364 (LUT3 _1820_ INIT 0x69 PERM 012) */
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
    lut206.push_back(ctx.genrate_lut(lut206idx0));
    flut206.push_back(lut206idx0);

    auto lut206idx1 = [](long I) -> long {
        /* GATE 409 (LUT3 _1865_ INIT 0x2b PERM 012) */
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
    lut206.push_back(ctx.genrate_lut(lut206idx1));
    flut206.push_back(lut206idx1);

    auto fvec206 = [flut206](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut206[i](I));
        return ret;
    };

    std::cerr << "\rLUT206   ";
    long gin206 = 1 * gout164[0] + 2 * gout205[1] + 4 * gout114[1];
    std::vector<long> gout206 = fvec206(gin206);

    std::vector<RotationPoly> lut207;
    std::vector<long (*)(long)> flut207;
    auto lut207idx0 = [](long I) -> long {
        /* GATE 407 (LUT3 _1863_ INIT 0x2b PERM 012) */
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
    lut207.push_back(ctx.genrate_lut(lut207idx0));
    flut207.push_back(lut207idx0);

    auto lut207idx1 = [](long I) -> long {
        /* GATE 362 (LUT3 _1818_ INIT 0x69 PERM 012) */
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
    lut207.push_back(ctx.genrate_lut(lut207idx1));
    flut207.push_back(lut207idx1);

    auto fvec207 = [flut207](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut207[i](I));
        return ret;
    };

    std::cerr << "\rLUT207   ";
    long gin207 = 1 * gout165[0] + 2 * gout206[0] + 4 * gout202[1];
    std::vector<long> gout207 = fvec207(gin207);

    std::vector<RotationPoly> lut208;
    std::vector<long (*)(long)> flut208;
    auto lut208idx0 = [](long I) -> long {
        /* GATE 405 (LUT3 _1861_ INIT 0xb2 PERM 012) */
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
    lut208.push_back(ctx.genrate_lut(lut208idx0));
    flut208.push_back(lut208idx0);

    auto lut208idx1 = [](long I) -> long {
        /* GATE 360 (LUT3 _1816_ INIT 0x96 PERM 012) */
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
    lut208.push_back(ctx.genrate_lut(lut208idx1));
    flut208.push_back(lut208idx1);

    auto fvec208 = [flut208](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut208[i](I));
        return ret;
    };

    std::cerr << "\rLUT208   ";
    long gin208 = 1 * gout188[0] + 2 * gout207[1] + 4 * gout187[0];
    std::vector<long> gout208 = fvec208(gin208);

    std::vector<RotationPoly> lut209;
    std::vector<long (*)(long)> flut209;
    auto lut209idx0 = [](long I) -> long {
        /* GATE 229 (LUT3 _1685_ INIT 0x2b PERM 012) */
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
    lut209.push_back(ctx.genrate_lut(lut209idx0));
    flut209.push_back(lut209idx0);

    auto lut209idx1 = [](long I) -> long {
        /* GATE 193 (LUT3 _1649_ INIT 0x69 PERM 012) */
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
    lut209.push_back(ctx.genrate_lut(lut209idx1));
    flut209.push_back(lut209idx1);

    auto fvec209 = [flut209](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut209[i](I));
        return ret;
    };

    std::cerr << "\rLUT209   ";
    long gin209 = 1 * gout195[0] + 2 * gout200[1] + 4 * gout152[1];
    std::vector<long> gout209 = fvec209(gin209);

    std::vector<RotationPoly> lut210;
    std::vector<long (*)(long)> flut210;
    auto lut210idx0 = [](long I) -> long {
        /* GATE 227 (LUT2 _1683_ INIT 0x4 PERM 01) */
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
    lut210.push_back(ctx.genrate_lut(lut210idx0));
    flut210.push_back(lut210idx0);

    auto lut210idx1 = [](long I) -> long {
        /* GATE 191 (LUT2 _1647_ INIT 0x9 PERM 01) */
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
    lut210.push_back(ctx.genrate_lut(lut210idx1));
    flut210.push_back(lut210idx1);

    auto fvec210 = [flut210](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut210[i](I));
        return ret;
    };

    std::cerr << "\rLUT210   ";
    long gin210 = 1 * gout196[0] + 2 * gout209[1];
    std::vector<long> gout210 = fvec210(gin210);

    std::vector<RotationPoly> lut211;
    std::vector<long (*)(long)> flut211;
    auto lut211idx0 = [](long I) -> long {
        /* GATE 24 (LUT2 _1480_ INIT 0x8 PERM 10) */
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
    long gin211 = 1 * gout43[0] + 2 * gout65[0];
    std::vector<long> gout211 = fvec211(gin211);

    std::vector<RotationPoly> lut212;
    std::vector<long (*)(long)> flut212;
    auto lut212idx0 = [](long I) -> long {
        /* GATE 36 (LUT2 _1492_ INIT 0x8 PERM 01) */
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

    auto lut212idx1 = [](long I) -> long {
        /* GATE 23 (LUT2 _1479_ INIT 0x6 PERM 01) */
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
    lut212.push_back(ctx.genrate_lut(lut212idx1));
    flut212.push_back(lut212idx1);

    auto fvec212 = [flut212](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut212[i](I));
        return ret;
    };

    std::cerr << "\rLUT212   ";
    long gin212 = 1 * gout211[0] + 2 * gout44[0];
    std::vector<long> gout212 = fvec212(gin212);

    std::vector<RotationPoly> lut213;
    std::vector<long (*)(long)> flut213;
    auto lut213idx0 = [](long I) -> long {
        /* GATE 51 (LUT2 _1507_ INIT 0x8 PERM 01) */
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
    lut213.push_back(ctx.genrate_lut(lut213idx0));
    flut213.push_back(lut213idx0);

    auto lut213idx1 = [](long I) -> long {
        /* GATE 35 (LUT2 _1491_ INIT 0x6 PERM 01) */
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
    lut213.push_back(ctx.genrate_lut(lut213idx1));
    flut213.push_back(lut213idx1);

    auto fvec213 = [flut213](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut213[i](I));
        return ret;
    };

    std::cerr << "\rLUT213   ";
    long gin213 = 1 * gout212[0] + 2 * gout177[1];
    std::vector<long> gout213 = fvec213(gin213);

    std::vector<RotationPoly> lut214;
    std::vector<long (*)(long)> flut214;
    auto lut214idx0 = [](long I) -> long {
        /* GATE 69 (LUT2 _1525_ INIT 0x8 PERM 01) */
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
    lut214.push_back(ctx.genrate_lut(lut214idx0));
    flut214.push_back(lut214idx0);

    auto lut214idx1 = [](long I) -> long {
        /* GATE 50 (LUT2 _1506_ INIT 0x6 PERM 01) */
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
    lut214.push_back(ctx.genrate_lut(lut214idx1));
    flut214.push_back(lut214idx1);

    auto fvec214 = [flut214](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut214[i](I));
        return ret;
    };

    std::cerr << "\rLUT214   ";
    long gin214 = 1 * gout213[0] + 2 * gout178[1];
    std::vector<long> gout214 = fvec214(gin214);

    std::vector<RotationPoly> lut215;
    std::vector<long (*)(long)> flut215;
    auto lut215idx0 = [](long I) -> long {
        /* GATE 441 (LUT2 _1897_ INIT 0x8 PERM 01) */
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
    lut215.push_back(ctx.genrate_lut(lut215idx0));
    flut215.push_back(lut215idx0);

    auto fvec215 = [flut215](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut215[i](I));
        return ret;
    };

    std::cerr << "\rLUT215   ";
    long gin215 = 1 * ct_y12 + 2 * ct_x2;
    std::vector<long> gout215 = fvec215(gin215);

    std::vector<RotationPoly> lut216;
    std::vector<long (*)(long)> flut216;
    auto lut216idx0 = [](long I) -> long {
        /* GATE 438 (LUT3 _1894_ INIT 0x96 PERM 012) */
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
    lut216.push_back(ctx.genrate_lut(lut216idx0));
    flut216.push_back(lut216idx0);

    auto lut216idx1 = [](long I) -> long {
        /* GATE 480 (LUT3 _1936_ INIT 0x17 PERM 012) */
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
    lut216.push_back(ctx.genrate_lut(lut216idx1));
    flut216.push_back(lut216idx1);

    auto fvec216 = [flut216](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut216[i](I));
        return ret;
    };

    std::cerr << "\rLUT216   ";
    long gin216 = 1 * gout17[0] + 2 * gout0[0] + 4 * gout215[0];
    std::vector<long> gout216 = fvec216(gin216);

    std::vector<RotationPoly> lut217;
    std::vector<long (*)(long)> flut217;
    auto lut217idx0 = [](long I) -> long {
        /* GATE 473 (LUT3 _1929_ INIT 0x2b PERM 012) */
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
    lut217.push_back(ctx.genrate_lut(lut217idx0));
    flut217.push_back(lut217idx0);

    auto lut217idx1 = [](long I) -> long {
        /* GATE 432 (LUT3 _1888_ INIT 0x69 PERM 012) */
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
    lut217.push_back(ctx.genrate_lut(lut217idx1));
    flut217.push_back(lut217idx1);

    auto fvec217 = [flut217](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut217[i](I));
        return ret;
    };

    std::cerr << "\rLUT217   ";
    long gin217 = 1 * gout39[1] + 2 * gout125[1] + 4 * gout216[0];
    std::vector<long> gout217 = fvec217(gin217);

    std::vector<RotationPoly> lut218;
    std::vector<long (*)(long)> flut218;
    auto lut218idx0 = [](long I) -> long {
        /* GATE 477 (LUT3 _1933_ INIT 0xb2 PERM 012) */
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
        /* GATE 429 (LUT3 _1885_ INIT 0x96 PERM 021) */
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
    long gin218 = 1 * gout185[0] + 2 * gout217[1] + 4 * gout114[0];
    std::vector<long> gout218 = fvec218(gin218);

    std::vector<RotationPoly> lut219;
    std::vector<long (*)(long)> flut219;
    auto lut219idx0 = [](long I) -> long {
        /* GATE 82 (LUT2 _1538_ INIT 0x8 PERM 01) */
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
    lut219.push_back(ctx.genrate_lut(lut219idx0));
    flut219.push_back(lut219idx0);

    auto fvec219 = [flut219](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut219[i](I));
        return ret;
    };

    std::cerr << "\rLUT219   ";
    long gin219 = 1 * ct_y5 + 2 * ct_x0;
    std::vector<long> gout219 = fvec219(gin219);

    std::vector<RotationPoly> lut220;
    std::vector<long (*)(long)> flut220;
    auto lut220idx0 = [](long I) -> long {
        /* GATE 110 (LUT3 _1566_ INIT 0x17 PERM 201) */
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
    lut220.push_back(ctx.genrate_lut(lut220idx0));
    flut220.push_back(lut220idx0);

    auto lut220idx1 = [](long I) -> long {
        /* GATE 80 (LUT3 _1536_ INIT 0x96 PERM 201) */
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
    lut220.push_back(ctx.genrate_lut(lut220idx1));
    flut220.push_back(lut220idx1);

    auto fvec220 = [flut220](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut220[i](I));
        return ret;
    };

    std::cerr << "\rLUT220   ";
    long gin220 = 1 * gout219[0] + 2 * gout201[0] + 4 * gout2[0];
    std::vector<long> gout220 = fvec220(gin220);

    std::vector<RotationPoly> lut221;
    std::vector<long (*)(long)> flut221;
    auto lut221idx0 = [](long I) -> long {
        /* GATE 141 (LUT3 _1597_ INIT 0x40 PERM 012) */
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
    lut221.push_back(ctx.genrate_lut(lut221idx0));
    flut221.push_back(lut221idx0);

    auto lut221idx1 = [](long I) -> long {
        /* GATE 109 (LUT3 _1565_ INIT 0x87 PERM 120) */
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
    lut221.push_back(ctx.genrate_lut(lut221idx1));
    flut221.push_back(lut221idx1);

    auto fvec221 = [flut221](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut221[i](I));
        return ret;
    };

    std::cerr << "\rLUT221   ";
    long gin221 = 1 * gout220[0] + 2 * ct_y6 + 4 * ct_x0;
    std::vector<long> gout221 = fvec221(gin221);

    std::vector<RotationPoly> lut222;
    std::vector<long (*)(long)> flut222;
    auto lut222idx0 = [](long I) -> long {
        /* GATE 98 (LUT3 _1554_ INIT 0x2b PERM 012) */
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
    lut222.push_back(ctx.genrate_lut(lut222idx0));
    flut222.push_back(lut222idx0);

    auto lut222idx1 = [](long I) -> long {
        /* GATE 74 (LUT3 _1530_ INIT 0x69 PERM 012) */
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
    lut222.push_back(ctx.genrate_lut(lut222idx1));
    flut222.push_back(lut222idx1);

    auto fvec222 = [flut222](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut222[i](I));
        return ret;
    };

    std::cerr << "\rLUT222   ";
    long gin222 = 1 * gout159[0] + 2 * gout171[1] + 4 * gout220[1];
    std::vector<long> gout222 = fvec222(gin222);

    std::vector<RotationPoly> lut223;
    std::vector<long (*)(long)> flut223;
    auto lut223idx0 = [](long I) -> long {
        /* GATE 124 (LUT3 _1580_ INIT 0x2b PERM 012) */
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
    lut223.push_back(ctx.genrate_lut(lut223idx0));
    flut223.push_back(lut223idx0);

    auto lut223idx1 = [](long I) -> long {
        /* GATE 97 (LUT3 _1553_ INIT 0x69 PERM 012) */
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
    lut223.push_back(ctx.genrate_lut(lut223idx1));
    flut223.push_back(lut223idx1);

    auto fvec223 = [flut223](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut223[i](I));
        return ret;
    };

    std::cerr << "\rLUT223   ";
    long gin223 = 1 * gout222[0] + 2 * gout175[1] + 4 * gout221[1];
    std::vector<long> gout223 = fvec223(gin223);

    std::vector<RotationPoly> lut224;
    std::vector<long (*)(long)> flut224;
    auto lut224idx0 = [](long I) -> long {
        /* GATE 154 (LUT3 _1610_ INIT 0x2b PERM 012) */
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
    lut224.push_back(ctx.genrate_lut(lut224idx0));
    flut224.push_back(lut224idx0);

    auto lut224idx1 = [](long I) -> long {
        /* GATE 123 (LUT3 _1579_ INIT 0x69 PERM 012) */
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
    lut224.push_back(ctx.genrate_lut(lut224idx1));
    flut224.push_back(lut224idx1);

    auto fvec224 = [flut224](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut224[i](I));
        return ret;
    };

    std::cerr << "\rLUT224   ";
    long gin224 = 1 * gout223[0] + 2 * gout176[1] + 4 * gout221[0];
    std::vector<long> gout224 = fvec224(gin224);

    std::vector<RotationPoly> lut225;
    std::vector<long (*)(long)> flut225;
    auto lut225idx0 = [](long I) -> long {
        /* GATE 190 (LUT2 _1646_ INIT 0x4 PERM 01) */
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
    lut225.push_back(ctx.genrate_lut(lut225idx0));
    flut225.push_back(lut225idx0);

    auto lut225idx1 = [](long I) -> long {
        /* GATE 153 (LUT2 _1609_ INIT 0x9 PERM 01) */
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
    lut225.push_back(ctx.genrate_lut(lut225idx1));
    flut225.push_back(lut225idx1);

    auto fvec225 = [flut225](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut225[i](I));
        return ret;
    };

    std::cerr << "\rLUT225   ";
    long gin225 = 1 * gout224[0] + 2 * gout196[1];
    std::vector<long> gout225 = fvec225(gin225);

    std::vector<RotationPoly> lut226;
    std::vector<long (*)(long)> flut226;
    auto lut226idx0 = [](long I) -> long {
        /* GATE 225 (LUT2 _1681_ INIT 0x8 PERM 01) */
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
    lut226.push_back(ctx.genrate_lut(lut226idx0));
    flut226.push_back(lut226idx0);

    auto lut226idx1 = [](long I) -> long {
        /* GATE 189 (LUT2 _1645_ INIT 0x6 PERM 01) */
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
    lut226.push_back(ctx.genrate_lut(lut226idx1));
    flut226.push_back(lut226idx1);

    auto fvec226 = [flut226](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut226[i](I));
        return ret;
    };

    std::cerr << "\rLUT226   ";
    long gin226 = 1 * gout225[0] + 2 * gout210[1];
    std::vector<long> gout226 = fvec226(gin226);

    std::vector<RotationPoly> lut227;
    std::vector<long (*)(long)> flut227;
    auto lut227idx0 = [](long I) -> long {
        /* GATE 96 (LUT3 _1552_ INIT 0x2b PERM 012) */
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
        /* GATE 72 (LUT3 _1528_ INIT 0x69 PERM 012) */
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
    long gin227 = 1 * gout160[0] + 2 * gout222[1] + 4 * gout140[0];
    std::vector<long> gout227 = fvec227(gin227);

    std::vector<RotationPoly> lut228;
    std::vector<long (*)(long)> flut228;
    auto lut228idx0 = [](long I) -> long {
        /* GATE 122 (LUT2 _1578_ INIT 0x4 PERM 01) */
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
    lut228.push_back(ctx.genrate_lut(lut228idx0));
    flut228.push_back(lut228idx0);

    auto lut228idx1 = [](long I) -> long {
        /* GATE 95 (LUT2 _1551_ INIT 0x9 PERM 01) */
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
    lut228.push_back(ctx.genrate_lut(lut228idx1));
    flut228.push_back(lut228idx1);

    auto fvec228 = [flut228](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut228[i](I));
        return ret;
    };

    std::cerr << "\rLUT228   ";
    long gin228 = 1 * gout227[0] + 2 * gout223[1];
    std::vector<long> gout228 = fvec228(gin228);

    std::vector<RotationPoly> lut229;
    std::vector<long (*)(long)> flut229;
    auto lut229idx0 = [](long I) -> long {
        /* GATE 94 (LUT2 _1550_ INIT 0x8 PERM 01) */
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
    lut229.push_back(ctx.genrate_lut(lut229idx0));
    flut229.push_back(lut229idx0);

    auto lut229idx1 = [](long I) -> long {
        /* GATE 70 (LUT2 _1526_ INIT 0x6 PERM 01) */
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
    lut229.push_back(ctx.genrate_lut(lut229idx1));
    flut229.push_back(lut229idx1);

    auto fvec229 = [flut229](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut229[i](I));
        return ret;
    };

    std::cerr << "\rLUT229   ";
    long gin229 = 1 * gout178[0] + 2 * gout227[1];
    std::vector<long> gout229 = fvec229(gin229);

    std::vector<RotationPoly> lut230;
    std::vector<long (*)(long)> flut230;
    auto lut230idx0 = [](long I) -> long {
        /* GATE 120 (LUT2 _1576_ INIT 0x8 PERM 01) */
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
    lut230.push_back(ctx.genrate_lut(lut230idx0));
    flut230.push_back(lut230idx0);

    auto lut230idx1 = [](long I) -> long {
        /* GATE 93 (LUT2 _1549_ INIT 0x6 PERM 01) */
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
    lut230.push_back(ctx.genrate_lut(lut230idx1));
    flut230.push_back(lut230idx1);

    auto fvec230 = [flut230](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut230[i](I));
        return ret;
    };

    std::cerr << "\rLUT230   ";
    long gin230 = 1 * gout229[0] + 2 * gout228[1];
    std::vector<long> gout230 = fvec230(gin230);

    std::vector<RotationPoly> lut231;
    std::vector<long (*)(long)> flut231;
    auto lut231idx0 = [](long I) -> long {
        /* GATE 92 (LUT2 _1548_ INIT 0x8 PERM 01) */
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
    lut231.push_back(ctx.genrate_lut(lut231idx0));
    flut231.push_back(lut231idx0);

    auto lut231idx1 = [](long I) -> long {
        /* GATE 68 (LUT2 _1524_ INIT 0x6 PERM 01) */
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
    lut231.push_back(ctx.genrate_lut(lut231idx1));
    flut231.push_back(lut231idx1);

    auto fvec231 = [flut231](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut231[i](I));
        return ret;
    };

    std::cerr << "\rLUT231   ";
    long gin231 = 1 * gout214[0] + 2 * gout229[1];
    std::vector<long> gout231 = fvec231(gin231);

    std::vector<RotationPoly> lut232;
    std::vector<long (*)(long)> flut232;
    auto lut232idx0 = [](long I) -> long {
        /* GATE 119 (LUT2 _1575_ INIT 0x8 PERM 01) */
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
        /* GATE 91 (LUT2 _1547_ INIT 0x6 PERM 01) */
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
    long gin232 = 1 * gout231[0] + 2 * gout230[1];
    std::vector<long> gout232 = fvec232(gin232);

    std::vector<RotationPoly> lut233;
    std::vector<long (*)(long)> flut233;
    auto lut233idx0 = [](long I) -> long {
        /* GATE 294 (LUT3 _1750_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut233.push_back(ctx.genrate_lut(lut233idx0));
    flut233.push_back(lut233idx0);

    auto lut233idx1 = [](long I) -> long {
        /* GATE 244 (LUT3 _1700_ INIT 0x96 PERM 012) */
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
    lut233.push_back(ctx.genrate_lut(lut233idx1));
    flut233.push_back(lut233idx1);

    auto fvec233 = [flut233](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut233[i](I));
        return ret;
    };

    std::cerr << "\rLUT233   ";
    long gin233 = 1 * gout197[1] + 2 * gout190[0] + 4 * gout167[1];
    std::vector<long> gout233 = fvec233(gin233);

    std::vector<RotationPoly> lut234;
    std::vector<long (*)(long)> flut234;
    auto lut234idx0 = [](long I) -> long {
        /* GATE 347 (LUT2 _1803_ INIT 0x4 PERM 01) */
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
    lut234.push_back(ctx.genrate_lut(lut234idx0));
    flut234.push_back(lut234idx0);

    auto lut234idx1 = [](long I) -> long {
        /* GATE 293 (LUT2 _1749_ INIT 0x9 PERM 01) */
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
    lut234.push_back(ctx.genrate_lut(lut234idx1));
    flut234.push_back(lut234idx1);

    auto fvec234 = [flut234](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut234[i](I));
        return ret;
    };

    std::cerr << "\rLUT234   ";
    long gin234 = 1 * gout233[0] + 2 * gout70[1];
    std::vector<long> gout234 = fvec234(gin234);

    std::vector<RotationPoly> lut235;
    std::vector<long (*)(long)> flut235;
    auto lut235idx0 = [](long I) -> long {
        /* GATE 273 (LUT3 _1729_ INIT 0x2b PERM 012) */
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
    lut235.push_back(ctx.genrate_lut(lut235idx0));
    flut235.push_back(lut235idx0);

    auto lut235idx1 = [](long I) -> long {
        /* GATE 232 (LUT3 _1688_ INIT 0x69 PERM 012) */
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
    lut235.push_back(ctx.genrate_lut(lut235idx1));
    flut235.push_back(lut235idx1);

    auto fvec235 = [flut235](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut235[i](I));
        return ret;
    };

    std::cerr << "\rLUT235   ";
    long gin235 = 1 * gout193[0] + 2 * gout147[1] + 4 * gout233[1];
    std::vector<long> gout235 = fvec235(gin235);

    std::vector<RotationPoly> lut236;
    std::vector<long (*)(long)> flut236;
    auto lut236idx0 = [](long I) -> long {
        /* GATE 315 (LUT3 _1771_ INIT 0x2b PERM 012) */
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
    lut236.push_back(ctx.genrate_lut(lut236idx0));
    flut236.push_back(lut236idx0);

    auto lut236idx1 = [](long I) -> long {
        /* GATE 272 (LUT3 _1728_ INIT 0x69 PERM 012) */
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
    lut236.push_back(ctx.genrate_lut(lut236idx1));
    flut236.push_back(lut236idx1);

    auto fvec236 = [flut236](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut236[i](I));
        return ret;
    };

    std::cerr << "\rLUT236   ";
    long gin236 = 1 * gout235[0] + 2 * gout169[1] + 4 * gout234[1];
    std::vector<long> gout236 = fvec236(gin236);

    std::vector<RotationPoly> lut237;
    std::vector<long (*)(long)> flut237;
    auto lut237idx0 = [](long I) -> long {
        /* GATE 359 (LUT3 _1815_ INIT 0x2b PERM 012) */
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
    lut237.push_back(ctx.genrate_lut(lut237idx0));
    flut237.push_back(lut237idx0);

    auto lut237idx1 = [](long I) -> long {
        /* GATE 314 (LUT3 _1770_ INIT 0x69 PERM 012) */
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
    lut237.push_back(ctx.genrate_lut(lut237idx1));
    flut237.push_back(lut237idx1);

    auto fvec237 = [flut237](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut237[i](I));
        return ret;
    };

    std::cerr << "\rLUT237   ";
    long gin237 = 1 * gout236[0] + 2 * gout188[1] + 4 * gout234[0];
    std::vector<long> gout237 = fvec237(gin237);

    std::vector<RotationPoly> lut238;
    std::vector<long (*)(long)> flut238;
    auto lut238idx0 = [](long I) -> long {
        /* GATE 403 (LUT2 _1859_ INIT 0x4 PERM 01) */
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
    lut238.push_back(ctx.genrate_lut(lut238idx0));
    flut238.push_back(lut238idx0);

    auto lut238idx1 = [](long I) -> long {
        /* GATE 358 (LUT2 _1814_ INIT 0x9 PERM 01) */
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
    lut238.push_back(ctx.genrate_lut(lut238idx1));
    flut238.push_back(lut238idx1);

    auto fvec238 = [flut238](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut238[i](I));
        return ret;
    };

    std::cerr << "\rLUT238   ";
    long gin238 = 1 * gout237[0] + 2 * gout208[1];
    std::vector<long> gout238 = fvec238(gin238);

    std::vector<RotationPoly> lut239;
    std::vector<long (*)(long)> flut239;
    auto lut239idx0 = [](long I) -> long {
        /* GATE 271 (LUT3 _1727_ INIT 0x2b PERM 012) */
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
    lut239.push_back(ctx.genrate_lut(lut239idx0));
    flut239.push_back(lut239idx0);

    auto lut239idx1 = [](long I) -> long {
        /* GATE 230 (LUT3 _1686_ INIT 0x69 PERM 012) */
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
    lut239.push_back(ctx.genrate_lut(lut239idx1));
    flut239.push_back(lut239idx1);

    auto fvec239 = [flut239](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut239[i](I));
        return ret;
    };

    std::cerr << "\rLUT239   ";
    long gin239 = 1 * gout200[0] + 2 * gout235[1] + 4 * gout199[1];
    std::vector<long> gout239 = fvec239(gin239);

    std::vector<RotationPoly> lut240;
    std::vector<long (*)(long)> flut240;
    auto lut240idx0 = [](long I) -> long {
        /* GATE 313 (LUT3 _1769_ INIT 0x2b PERM 012) */
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
    lut240.push_back(ctx.genrate_lut(lut240idx0));
    flut240.push_back(lut240idx0);

    auto lut240idx1 = [](long I) -> long {
        /* GATE 270 (LUT3 _1726_ INIT 0x69 PERM 012) */
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
    lut240.push_back(ctx.genrate_lut(lut240idx1));
    flut240.push_back(lut240idx1);

    auto fvec240 = [flut240](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut240[i](I));
        return ret;
    };

    std::cerr << "\rLUT240   ";
    long gin240 = 1 * gout239[0] + 2 * gout236[1] + 4 * gout199[0];
    std::vector<long> gout240 = fvec240(gin240);

    std::vector<RotationPoly> lut241;
    std::vector<long (*)(long)> flut241;
    auto lut241idx0 = [](long I) -> long {
        /* GATE 357 (LUT2 _1813_ INIT 0x4 PERM 01) */
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
    lut241.push_back(ctx.genrate_lut(lut241idx0));
    flut241.push_back(lut241idx0);

    auto lut241idx1 = [](long I) -> long {
        /* GATE 312 (LUT2 _1768_ INIT 0x9 PERM 01) */
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
    lut241.push_back(ctx.genrate_lut(lut241idx1));
    flut241.push_back(lut241idx1);

    auto fvec241 = [flut241](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut241[i](I));
        return ret;
    };

    std::cerr << "\rLUT241   ";
    long gin241 = 1 * gout240[0] + 2 * gout237[1];
    std::vector<long> gout241 = fvec241(gin241);

    std::vector<RotationPoly> lut242;
    std::vector<long (*)(long)> flut242;
    auto lut242idx0 = [](long I) -> long {
        /* GATE 356 (LUT2 _1812_ INIT 0x6 PERM 01) */
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
    lut242.push_back(ctx.genrate_lut(lut242idx0));
    flut242.push_back(lut242idx0);

    auto fvec242 = [flut242](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut242[i](I));
        return ret;
    };

    std::cerr << "\rLUT242   ";
    long gin242 = 1 * gout241[0] + 2 * gout238[1];
    std::vector<long> gout242 = fvec242(gin242);

    std::vector<RotationPoly> lut243;
    std::vector<long (*)(long)> flut243;
    auto lut243idx0 = [](long I) -> long {
        /* GATE 269 (LUT3 _1725_ INIT 0x2b PERM 012) */
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
        /* GATE 228 (LUT3 _1684_ INIT 0x69 PERM 012) */
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
    long gin243 = 1 * gout209[0] + 2 * gout239[1] + 4 * gout152[0];
    std::vector<long> gout243 = fvec243(gin243);

    std::vector<RotationPoly> lut244;
    std::vector<long (*)(long)> flut244;
    auto lut244idx0 = [](long I) -> long {
        /* GATE 311 (LUT2 _1767_ INIT 0x4 PERM 01) */
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
        /* GATE 268 (LUT2 _1724_ INIT 0x9 PERM 01) */
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
    long gin244 = 1 * gout243[0] + 2 * gout240[1];
    std::vector<long> gout244 = fvec244(gin244);

    std::vector<RotationPoly> lut245;
    std::vector<long (*)(long)> flut245;
    auto lut245idx0 = [](long I) -> long {
        /* GATE 267 (LUT2 _1723_ INIT 0x8 PERM 01) */
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
        /* GATE 226 (LUT2 _1682_ INIT 0x6 PERM 01) */
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
    long gin245 = 1 * gout210[0] + 2 * gout243[1];
    std::vector<long> gout245 = fvec245(gin245);

    std::vector<RotationPoly> lut246;
    std::vector<long (*)(long)> flut246;
    auto lut246idx0 = [](long I) -> long {
        /* GATE 266 (LUT2 _1722_ INIT 0x6 PERM 01) */
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
    lut246.push_back(ctx.genrate_lut(lut246idx0));
    flut246.push_back(lut246idx0);

    auto fvec246 = [flut246](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut246[i](I));
        return ret;
    };

    std::cerr << "\rLUT246   ";
    long gin246 = 1 * gout245[0] + 2 * gout244[1];
    std::vector<long> gout246 = fvec246(gin246);

    std::vector<RotationPoly> lut247;
    std::vector<long (*)(long)> flut247;
    auto lut247idx0 = [](long I) -> long {
        /* GATE 152 (LUT2 _1608_ INIT 0x8 PERM 01) */
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
        /* GATE 121 (LUT2 _1577_ INIT 0x6 PERM 01) */
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
    long gin247 = 1 * gout228[0] + 2 * gout224[1];
    std::vector<long> gout247 = fvec247(gin247);

    std::vector<RotationPoly> lut248;
    std::vector<long (*)(long)> flut248;
    auto lut248idx0 = [](long I) -> long {
        /* GATE 188 (LUT2 _1644_ INIT 0x8 PERM 01) */
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
    lut248.push_back(ctx.genrate_lut(lut248idx0));
    flut248.push_back(lut248idx0);

    auto lut248idx1 = [](long I) -> long {
        /* GATE 151 (LUT2 _1607_ INIT 0x6 PERM 01) */
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
    lut248.push_back(ctx.genrate_lut(lut248idx1));
    flut248.push_back(lut248idx1);

    auto fvec248 = [flut248](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut248[i](I));
        return ret;
    };

    std::cerr << "\rLUT248   ";
    long gin248 = 1 * gout247[0] + 2 * gout225[1];
    std::vector<long> gout248 = fvec248(gin248);

    std::vector<RotationPoly> lut249;
    std::vector<long (*)(long)> flut249;
    auto lut249idx0 = [](long I) -> long {
        /* GATE 187 (LUT2 _1643_ INIT 0x6 PERM 01) */
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
    lut249.push_back(ctx.genrate_lut(lut249idx0));
    flut249.push_back(lut249idx0);

    auto fvec249 = [flut249](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut249[i](I));
        return ret;
    };

    std::cerr << "\rLUT249   ";
    long gin249 = 1 * gout248[0] + 2 * gout226[1];
    std::vector<long> gout249 = fvec249(gin249);

    std::vector<RotationPoly> lut250;
    std::vector<long (*)(long)> flut250;
    auto lut250idx0 = [](long I) -> long {
        /* GATE 150 (LUT2 _1606_ INIT 0x8 PERM 01) */
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
    lut250.push_back(ctx.genrate_lut(lut250idx0));
    flut250.push_back(lut250idx0);

    auto fvec250 = [flut250](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut250[i](I));
        return ret;
    };

    std::cerr << "\rLUT250   ";
    long gin250 = 1 * gout230[0] + 2 * gout247[1];
    std::vector<long> gout250 = fvec250(gin250);

    std::vector<RotationPoly> lut251;
    std::vector<long (*)(long)> flut251;
    auto lut251idx0 = [](long I) -> long {
        /* GATE 149 (LUT2 _1605_ INIT 0x8 PERM 01) */
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
    lut251.push_back(ctx.genrate_lut(lut251idx0));
    flut251.push_back(lut251idx0);

    auto fvec251 = [flut251](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut251[i](I));
        return ret;
    };

    std::cerr << "\rLUT251   ";
    long gin251 = 1 * gout232[0] + 2 * gout247[1];
    std::vector<long> gout251 = fvec251(gin251);

    std::vector<RotationPoly> lut252;
    std::vector<long (*)(long)> flut252;
    auto lut252idx0 = [](long I) -> long {
        /* GATE 186 (LUT3 _1642_ INIT 0x17 PERM 012) */
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
    lut252.push_back(ctx.genrate_lut(lut252idx0));
    flut252.push_back(lut252idx0);

    auto lut252idx1 = [](long I) -> long {
        /* GATE 148 (LUT3 _1604_ INIT 0x96 PERM 012) */
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
    lut252.push_back(ctx.genrate_lut(lut252idx1));
    flut252.push_back(lut252idx1);

    auto fvec252 = [flut252](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut252[i](I));
        return ret;
    };

    std::cerr << "\rLUT252   ";
    long gin252 = 1 * gout251[0] + 2 * gout250[0] + 4 * gout248[1];
    std::vector<long> gout252 = fvec252(gin252);

    std::vector<RotationPoly> lut253;
    std::vector<long (*)(long)> flut253;
    auto lut253idx0 = [](long I) -> long {
        /* GATE 224 (LUT3 _1680_ INIT 0x2b PERM 201) */
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
    lut253.push_back(ctx.genrate_lut(lut253idx0));
    flut253.push_back(lut253idx0);

    auto fvec253 = [flut253](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut253[i](I));
        return ret;
    };

    std::cerr << "\rLUT253   ";
    long gin253 = 1 * gout248[0] + 2 * gout226[1] + 4 * gout252[0];
    std::vector<long> gout253 = fvec253(gin253);

    std::vector<RotationPoly> lut254;
    std::vector<long (*)(long)> flut254;
    auto lut254idx0 = [](long I) -> long {
        /* GATE 265 (LUT3 _1721_ INIT 0x2b PERM 012) */
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
    lut254.push_back(ctx.genrate_lut(lut254idx0));
    flut254.push_back(lut254idx0);

    auto lut254idx1 = [](long I) -> long {
        /* GATE 223 (LUT3 _1679_ INIT 0x69 PERM 012) */
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
    lut254.push_back(ctx.genrate_lut(lut254idx1));
    flut254.push_back(lut254idx1);

    auto fvec254 = [flut254](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut254[i](I));
        return ret;
    };

    std::cerr << "\rLUT254   ";
    long gin254 = 1 * gout253[0] + 2 * gout226[0] + 4 * gout245[1];
    std::vector<long> gout254 = fvec254(gin254);

    std::vector<RotationPoly> lut255;
    std::vector<long (*)(long)> flut255;
    auto lut255idx0 = [](long I) -> long {
        /* GATE 310 (LUT3 _1766_ INIT 0x2b PERM 201) */
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
    lut255.push_back(ctx.genrate_lut(lut255idx0));
    flut255.push_back(lut255idx0);

    auto fvec255 = [flut255](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut255[i](I));
        return ret;
    };

    std::cerr << "\rLUT255   ";
    long gin255 = 1 * gout245[0] + 2 * gout244[1] + 4 * gout254[0];
    std::vector<long> gout255 = fvec255(gin255);

    std::vector<RotationPoly> lut256;
    std::vector<long (*)(long)> flut256;
    auto lut256idx0 = [](long I) -> long {
        /* GATE 355 (LUT3 _1811_ INIT 0x2b PERM 012) */
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
    lut256.push_back(ctx.genrate_lut(lut256idx0));
    flut256.push_back(lut256idx0);

    auto lut256idx1 = [](long I) -> long {
        /* GATE 309 (LUT3 _1765_ INIT 0x69 PERM 012) */
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
    lut256.push_back(ctx.genrate_lut(lut256idx1));
    flut256.push_back(lut256idx1);

    auto fvec256 = [flut256](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut256[i](I));
        return ret;
    };

    std::cerr << "\rLUT256   ";
    long gin256 = 1 * gout255[0] + 2 * gout244[0] + 4 * gout241[1];
    std::vector<long> gout256 = fvec256(gin256);

    std::vector<RotationPoly> lut257;
    std::vector<long (*)(long)> flut257;
    auto lut257idx0 = [](long I) -> long {
        /* GATE 402 (LUT3 _1858_ INIT 0x2b PERM 012) */
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
    lut257.push_back(ctx.genrate_lut(lut257idx0));
    flut257.push_back(lut257idx0);

    auto fvec257 = [flut257](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut257[i](I));
        return ret;
    };

    std::cerr << "\rLUT257   ";
    long gin257 = 1 * gout256[0] + 2 * gout241[0] + 4 * gout238[1];
    std::vector<long> gout257 = fvec257(gin257);

    std::vector<RotationPoly> lut258;
    std::vector<long (*)(long)> flut258;
    auto lut258idx0 = [](long I) -> long {
        /* GATE 118 (LUT3 _1574_ INIT 0x1e PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
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
    long gin258 = 1 * gout232[0] + 2 * gout230[0] + 4 * gout247[1];
    std::vector<long> gout258 = fvec258(gin258);

    std::vector<RotationPoly> lut259;
    std::vector<long (*)(long)> flut259;
    auto lut259idx0 = [](long I) -> long {
        /* GATE 476 (LUT3 _1932_ INIT 0x69 PERM 012) */
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
    lut259.push_back(ctx.genrate_lut(lut259idx0));
    flut259.push_back(lut259idx0);

    auto fvec259 = [flut259](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut259[i](I));
        return ret;
    };

    std::cerr << "\rLUT259   ";
    long gin259 = 1 * gout218[0] + 2 * gout106[0] + 4 * gout216[1];
    std::vector<long> gout259 = fvec259(gin259);

    std::vector<RotationPoly> lut260;
    std::vector<long (*)(long)> flut260;
    auto lut260idx0 = [](long I) -> long {
        /* GATE 427 (LUT2 _1883_ INIT 0x8 PERM 10) */
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
    lut260.push_back(ctx.genrate_lut(lut260idx0));
    flut260.push_back(lut260idx0);

    auto fvec260 = [flut260](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut260[i](I));
        return ret;
    };

    std::cerr << "\rLUT260   ";
    long gin260 = 1 * ct_x6 + 2 * ct_y8;
    std::vector<long> gout260 = fvec260(gin260);

    std::vector<RotationPoly> lut261;
    std::vector<long (*)(long)> flut261;
    auto lut261idx0 = [](long I) -> long {
        /* GATE 472 (LUT3 _1928_ INIT 0x17 PERM 012) */
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
    lut261.push_back(ctx.genrate_lut(lut261idx0));
    flut261.push_back(lut261idx0);

    auto lut261idx1 = [](long I) -> long {
        /* GATE 425 (LUT3 _1881_ INIT 0x96 PERM 012) */
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
    lut261.push_back(ctx.genrate_lut(lut261idx1));
    flut261.push_back(lut261idx1);

    auto fvec261 = [flut261](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut261[i](I));
        return ret;
    };

    std::cerr << "\rLUT261   ";
    long gin261 = 1 * gout10[0] + 2 * gout260[0] + 4 * gout204[0];
    std::vector<long> gout261 = fvec261(gin261);

    std::vector<RotationPoly> lut262;
    std::vector<long (*)(long)> flut262;
    auto lut262idx0 = [](long I) -> long {
        /* GATE 467 (LUT3 _1923_ INIT 0x96 PERM 012) */
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
    lut262.push_back(ctx.genrate_lut(lut262idx0));
    flut262.push_back(lut262idx0);

    auto fvec262 = [flut262](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut262[i](I));
        return ret;
    };

    std::cerr << "\rLUT262   ";
    long gin262 = 1 * gout131[0] + 2 * gout155[0] + 4 * gout261[0];
    std::vector<long> gout262 = fvec262(gin262);

    std::vector<RotationPoly> lut263;
    std::vector<long (*)(long)> flut263;
    auto lut263idx0 = [](long I) -> long {
        /* GATE 463 (LUT3 _1919_ INIT 0xb2 PERM 012) */
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
    lut263.push_back(ctx.genrate_lut(lut263idx0));
    flut263.push_back(lut263idx0);

    auto lut263idx1 = [](long I) -> long {
        /* GATE 422 (LUT3 _1878_ INIT 0x96 PERM 021) */
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
    lut263.push_back(ctx.genrate_lut(lut263idx1));
    flut263.push_back(lut263idx1);

    auto fvec263 = [flut263](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut263[i](I));
        return ret;
    };

    std::cerr << "\rLUT263   ";
    long gin263 = 1 * gout55[0] + 2 * gout261[1] + 4 * gout101[1];
    std::vector<long> gout263 = fvec263(gin263);

    std::vector<RotationPoly> lut264;
    std::vector<long (*)(long)> flut264;
    auto lut264idx0 = [](long I) -> long {
        /* GATE 456 (LUT3 _1912_ INIT 0x96 PERM 012) */
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
    lut264.push_back(ctx.genrate_lut(lut264idx0));
    flut264.push_back(lut264idx0);

    auto fvec264 = [flut264](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut264[i](I));
        return ret;
    };

    std::cerr << "\rLUT264   ";
    long gin264 = 1 * gout182[0] + 2 * gout263[0] + 4 * gout126[0];
    std::vector<long> gout264 = fvec264(gin264);

    std::vector<RotationPoly> lut265;
    std::vector<long (*)(long)> flut265;
    auto lut265idx0 = [](long I) -> long {
        /* GATE 482 (LUT3 _1938_ INIT 0x2b PERM 012) */
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
    lut265.push_back(ctx.genrate_lut(lut265idx0));
    flut265.push_back(lut265idx0);

    auto lut265idx1 = [](long I) -> long {
        /* GATE 410 (LUT3 _1866_ INIT 0x69 PERM 012) */
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
    lut265.push_back(ctx.genrate_lut(lut265idx1));
    flut265.push_back(lut265idx1);

    auto fvec265 = [flut265](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut265[i](I));
        return ret;
    };

    std::cerr << "\rLUT265   ";
    long gin265 = 1 * gout205[0] + 2 * gout157[1] + 4 * gout263[1];
    std::vector<long> gout265 = fvec265(gin265);

    std::vector<RotationPoly> lut266;
    std::vector<long (*)(long)> flut266;
    auto lut266idx0 = [](long I) -> long {
        /* GATE 481 (LUT3 _1937_ INIT 0x96 PERM 012) */
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
    lut266.push_back(ctx.genrate_lut(lut266idx0));
    flut266.push_back(lut266idx0);

    auto fvec266 = [flut266](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut266[i](I));
        return ret;
    };

    std::cerr << "\rLUT266   ";
    long gin266 = 1 * gout265[0] + 2 * gout157[0] + 4 * gout134[0];
    std::vector<long> gout266 = fvec266(gin266);

    std::vector<RotationPoly> lut267;
    std::vector<long (*)(long)> flut267;
    auto lut267idx0 = [](long I) -> long {
        /* GATE 455 (LUT3 _1911_ INIT 0x2b PERM 012) */
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
    lut267.push_back(ctx.genrate_lut(lut267idx0));
    flut267.push_back(lut267idx0);

    auto lut267idx1 = [](long I) -> long {
        /* GATE 408 (LUT3 _1864_ INIT 0x69 PERM 012) */
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
    lut267.push_back(ctx.genrate_lut(lut267idx1));
    flut267.push_back(lut267idx1);

    auto fvec267 = [flut267](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut267[i](I));
        return ret;
    };

    std::cerr << "\rLUT267   ";
    long gin267 = 1 * gout206[1] + 2 * gout265[1] + 4 * gout218[1];
    std::vector<long> gout267 = fvec267(gin267);

    std::vector<RotationPoly> lut268;
    std::vector<long (*)(long)> flut268;
    auto lut268idx0 = [](long I) -> long {
        /* GATE 491 (LUT3 _1947_ INIT 0x2b PERM 012) */
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
    lut268.push_back(ctx.genrate_lut(lut268idx0));
    flut268.push_back(lut268idx0);

    auto lut268idx1 = [](long I) -> long {
        /* GATE 406 (LUT3 _1862_ INIT 0x69 PERM 012) */
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
    lut268.push_back(ctx.genrate_lut(lut268idx1));
    flut268.push_back(lut268idx1);

    auto fvec268 = [flut268](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut268[i](I));
        return ret;
    };

    std::cerr << "\rLUT268   ";
    long gin268 = 1 * gout207[0] + 2 * gout267[1] + 4 * gout203[1];
    std::vector<long> gout268 = fvec268(gin268);

    std::vector<RotationPoly> lut269;
    std::vector<long (*)(long)> flut269;
    auto lut269idx0 = [](long I) -> long {
        /* GATE 489 (LUT3 _1945_ INIT 0x4b PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
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
        /* GATE 404 (LUT2 _1860_ INIT 0x9 PERM 01) */
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
    long gin269 = 1 * gout208[0] + 2 * gout268[1] + 4 * gout203[0];
    std::vector<long> gout269 = fvec269(gin269);

    std::vector<RotationPoly> lut270;
    std::vector<long (*)(long)> flut270;
    auto lut270idx0 = [](long I) -> long {
        /* GATE 451 (LUT3 _1907_ INIT 0x2b PERM 012) */
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
        /* GATE 401 (LUT3 _1857_ INIT 0x69 PERM 012) */
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
    long gin270 = 1 * gout257[0] + 2 * gout238[0] + 4 * gout269[1];
    std::vector<long> gout270 = fvec270(gin270);

    std::vector<RotationPoly> lut271;
    std::vector<long (*)(long)> flut271;
    auto lut271idx0 = [](long I) -> long {
        /* GATE 5 (LUT2 _1461_ INIT 0x1 PERM 01) */
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
    lut271.push_back(ctx.genrate_lut(lut271idx0));
    flut271.push_back(lut271idx0);

    auto fvec271 = [flut271](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut271[i](I));
        return ret;
    };

    std::cerr << "\rLUT271   ";
    long gin271 = 1 * ct_op6 + 2 * ct_op7;
    std::vector<long> gout271 = fvec271(gin271);

    std::vector<RotationPoly> lut272;
    std::vector<long (*)(long)> flut272;
    auto lut272idx0 = [](long I) -> long {
        /* GATE 4 (LUT3 _1460_ INIT 0x40 PERM 012) */
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
    lut272.push_back(ctx.genrate_lut(lut272idx0));
    flut272.push_back(lut272idx0);

    auto fvec272 = [flut272](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut272[i](I));
        return ret;
    };

    std::cerr << "\rLUT272   ";
    long gin272 = 1 * ct_op4 + 2 * ct_op5 + 4 * gout271[0];
    std::vector<long> gout272 = fvec272(gin272);

    std::vector<RotationPoly> lut273;
    std::vector<long (*)(long)> flut273;
    auto lut273idx0 = [](long I) -> long {
        /* GATE 9 (LUT3 _1465_ INIT 0x40 PERM 012) */
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
    lut273.push_back(ctx.genrate_lut(lut273idx0));
    flut273.push_back(lut273idx0);

    auto fvec273 = [flut273](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut273[i](I));
        return ret;
    };

    std::cerr << "\rLUT273   ";
    long gin273 = 1 * ct_op0 + 2 * gout81[1] + 4 * gout272[0];
    std::vector<long> gout273 = fvec273(gin273);

    std::vector<RotationPoly> lut274;
    std::vector<long (*)(long)> flut274;
    auto lut274idx0 = [](long I) -> long {
        /* GATE 354 (LUT3 _1810_ INIT 0x90 PERM 102) */
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
    lut274.push_back(ctx.genrate_lut(lut274idx0));
    flut274.push_back(lut274idx0);

    auto fvec274 = [flut274](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut274[i](I));
        return ret;
    };

    std::cerr << "\rLUT274   ";
    long gin274 = 1 * gout242[0] + 2 * gout256[0] + 4 * gout273[0];
    std::vector<long> gout274 = fvec274(gin274);

    std::vector<RotationPoly> lut275;
    std::vector<long (*)(long)> flut275;
    auto lut275idx0 = [](long I) -> long {
        /* GATE 264 (LUT3 _1720_ INIT 0x90 PERM 012) */
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
    lut275.push_back(ctx.genrate_lut(lut275idx0));
    flut275.push_back(lut275idx0);

    auto fvec275 = [flut275](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut275[i](I));
        return ret;
    };

    std::cerr << "\rLUT275   ";
    long gin275 = 1 * gout254[0] + 2 * gout246[0] + 4 * gout273[0];
    std::vector<long> gout275 = fvec275(gin275);

    std::vector<RotationPoly> lut276;
    std::vector<long (*)(long)> flut276;
    auto lut276idx0 = [](long I) -> long {
        /* GATE 185 (LUT3 _1641_ INIT 0x90 PERM 012) */
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
    lut276.push_back(ctx.genrate_lut(lut276idx0));
    flut276.push_back(lut276idx0);

    auto fvec276 = [flut276](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut276[i](I));
        return ret;
    };

    std::cerr << "\rLUT276   ";
    long gin276 = 1 * gout252[0] + 2 * gout249[0] + 4 * gout273[0];
    std::vector<long> gout276 = fvec276(gin276);

    std::vector<RotationPoly> lut277;
    std::vector<long (*)(long)> flut277;
    auto lut277idx0 = [](long I) -> long {
        /* GATE 117 (LUT2 _1573_ INIT 0x4 PERM 01) */
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
    lut277.push_back(ctx.genrate_lut(lut277idx0));
    flut277.push_back(lut277idx0);

    auto fvec277 = [flut277](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut277[i](I));
        return ret;
    };

    std::cerr << "\rLUT277   ";
    long gin277 = 1 * gout258[0] + 2 * gout273[0];
    std::vector<long> gout277 = fvec277(gin277);

    std::vector<RotationPoly> lut278;
    std::vector<long (*)(long)> flut278;
    auto lut278idx0 = [](long I) -> long {
        /* GATE 8 (LUT3 _1464_ INIT 0x94 PERM 210) */
        switch (I) {
            case  0: return 0;
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
    lut278.push_back(ctx.genrate_lut(lut278idx0));
    flut278.push_back(lut278idx0);

    auto fvec278 = [flut278](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut278[i](I));
        return ret;
    };

    std::cerr << "\rLUT278   ";
    long gin278 = 1 * ct_y0 + 2 * ct_x0 + 4 * gout273[0];
    std::vector<long> gout278 = fvec278(gin278);

    std::vector<RotationPoly> lut279;
    std::vector<long (*)(long)> flut279;
    auto lut279idx0 = [](long I) -> long {
        /* GATE 3 (LUT3 _1459_ INIT 0x80 PERM 201) */
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
    lut279.push_back(ctx.genrate_lut(lut279idx0));
    flut279.push_back(lut279idx0);

    auto fvec279 = [flut279](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut279[i](I));
        return ret;
    };

    std::cerr << "\rLUT279   ";
    long gin279 = 1 * gout81[0] + 2 * ct_op0 + 4 * gout272[0];
    std::vector<long> gout279 = fvec279(gin279);

    std::vector<RotationPoly> lut280;
    std::vector<long (*)(long)> flut280;
    auto lut280idx0 = [](long I) -> long {
        /* GATE 308 (LUT3 _1764_ INIT 0x4f PERM 102) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut280.push_back(ctx.genrate_lut(lut280idx0));
    flut280.push_back(lut280idx0);

    auto lut280idx1 = [](long I) -> long {
        /* GATE 261 (LUT3 _1717_ INIT 0x4b PERM 021) */
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
    lut280.push_back(ctx.genrate_lut(lut280idx1));
    flut280.push_back(lut280idx1);

    auto fvec280 = [flut280](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut280[i](I));
        return ret;
    };

    std::cerr << "\rLUT280   ";
    long gin280 = 1 * gout180[0] + 2 * ct_y11 + 4 * gout279[0];
    std::vector<long> gout280 = fvec280(gin280);

    std::vector<RotationPoly> lut281;
    std::vector<long (*)(long)> flut281;
    auto lut281idx0 = [](long I) -> long {
        /* GATE 353 (LUT3 _1809_ INIT 0xb0 PERM 102) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut281.push_back(ctx.genrate_lut(lut281idx0));
    flut281.push_back(lut281idx0);

    auto lut281idx1 = [](long I) -> long {
        /* GATE 307 (LUT2 _1763_ INIT 0x9 PERM 01) */
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
    lut281.push_back(ctx.genrate_lut(lut281idx1));
    flut281.push_back(lut281idx1);

    auto fvec281 = [flut281](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut281[i](I));
        return ret;
    };

    std::cerr << "\rLUT281   ";
    long gin281 = 1 * gout280[0] + 2 * ct_y12 + 4 * gout279[0];
    std::vector<long> gout281 = fvec281(gin281);

    std::vector<RotationPoly> lut282;
    std::vector<long (*)(long)> flut282;
    auto lut282idx0 = [](long I) -> long {
        /* GATE 400 (LUT3 _1856_ INIT 0xf8 PERM 120) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut282.push_back(ctx.genrate_lut(lut282idx0));
    flut282.push_back(lut282idx0);

    auto lut282idx1 = [](long I) -> long {
        /* GATE 352 (LUT2 _1808_ INIT 0x9 PERM 02) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut282.push_back(ctx.genrate_lut(lut282idx1));
    flut282.push_back(lut282idx1);

    auto fvec282 = [flut282](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut282[i](I));
        return ret;
    };

    std::cerr << "\rLUT282   ";
    long gin282 = 1 * gout281[0] + 2 * gout279[0] + 4 * ct_y13;
    std::vector<long> gout282 = fvec282(gin282);

    std::vector<RotationPoly> lut283;
    std::vector<long (*)(long)> flut283;
    auto lut283idx0 = [](long I) -> long {
        /* GATE 449 (LUT3 _1905_ INIT 0xe0 PERM 201) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut283.push_back(ctx.genrate_lut(lut283idx0));
    flut283.push_back(lut283idx0);

    auto lut283idx1 = [](long I) -> long {
        /* GATE 399 (LUT2 _1855_ INIT 0x6 PERM 02) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut283.push_back(ctx.genrate_lut(lut283idx1));
    flut283.push_back(lut283idx1);

    auto fvec283 = [flut283](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut283[i](I));
        return ret;
    };

    std::cerr << "\rLUT283   ";
    long gin283 = 1 * gout282[0] + 2 * gout279[0] + 4 * ct_y14;
    std::vector<long> gout283 = fvec283(gin283);

    std::vector<RotationPoly> lut284;
    std::vector<long (*)(long)> flut284;
    auto lut284idx0 = [](long I) -> long {
        /* GATE 448 (LUT3 _1904_ INIT 0x96 PERM 021) */
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
    lut284.push_back(ctx.genrate_lut(lut284idx0));
    flut284.push_back(lut284idx0);

    auto fvec284 = [flut284](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut284[i](I));
        return ret;
    };

    std::cerr << "\rLUT284   ";
    long gin284 = 1 * gout283[0] + 2 * ct_x15 + 4 * ct_y15;
    std::vector<long> gout284 = fvec284(gin284);

    std::vector<RotationPoly> lut285;
    std::vector<long (*)(long)> flut285;
    auto lut285idx0 = [](long I) -> long {
        /* GATE 351 (LUT2 _1807_ INIT 0x9 PERM 01) */
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
    lut285.push_back(ctx.genrate_lut(lut285idx0));
    flut285.push_back(lut285idx0);

    auto fvec285 = [flut285](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut285[i](I));
        return ret;
    };

    std::cerr << "\rLUT285   ";
    long gin285 = 1 * gout282[1] + 2 * ct_x13;
    std::vector<long> gout285 = fvec285(gin285);

    std::vector<RotationPoly> lut286;
    std::vector<long (*)(long)> flut286;
    auto lut286idx0 = [](long I) -> long {
        /* GATE 260 (LUT2 _1716_ INIT 0x9 PERM 01) */
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
    lut286.push_back(ctx.genrate_lut(lut286idx0));
    flut286.push_back(lut286idx0);

    auto fvec286 = [flut286](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut286[i](I));
        return ret;
    };

    std::cerr << "\rLUT286   ";
    long gin286 = 1 * gout280[1] + 2 * ct_x11;
    std::vector<long> gout286 = fvec286(gin286);

    std::vector<RotationPoly> lut287;
    std::vector<long (*)(long)> flut287;
    auto lut287idx0 = [](long I) -> long {
        /* GATE 222 (LUT3 _1678_ INIT 0xb0 PERM 102) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut287.push_back(ctx.genrate_lut(lut287idx0));
    flut287.push_back(lut287idx0);

    auto lut287idx1 = [](long I) -> long {
        /* GATE 183 (LUT3 _1639_ INIT 0xb4 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut287.push_back(ctx.genrate_lut(lut287idx1));
    flut287.push_back(lut287idx1);

    auto fvec287 = [flut287](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut287[i](I));
        return ret;
    };

    std::cerr << "\rLUT287   ";
    long gin287 = 1 * gout179[0] + 2 * ct_y9 + 4 * gout279[0];
    std::vector<long> gout287 = fvec287(gin287);

    std::vector<RotationPoly> lut288;
    std::vector<long (*)(long)> flut288;
    auto lut288idx0 = [](long I) -> long {
        /* GATE 263 (LUT3 _1719_ INIT 0x60 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut288.push_back(ctx.genrate_lut(lut288idx0));
    flut288.push_back(lut288idx0);

    auto lut288idx1 = [](long I) -> long {
        /* GATE 221 (LUT3 _1677_ INIT 0x96 PERM 021) */
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
    lut288.push_back(ctx.genrate_lut(lut288idx1));
    flut288.push_back(lut288idx1);

    auto fvec288 = [flut288](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut288[i](I));
        return ret;
    };

    std::cerr << "\rLUT288   ";
    long gin288 = 1 * gout287[0] + 2 * ct_x10 + 4 * ct_y10;
    std::vector<long> gout288 = fvec288(gin288);

    std::vector<RotationPoly> lut289;
    std::vector<long (*)(long)> flut289;
    auto lut289idx0 = [](long I) -> long {
        /* GATE 306 (LUT3 _1762_ INIT 0xb2 PERM 201) */
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
    lut289.push_back(ctx.genrate_lut(lut289idx0));
    flut289.push_back(lut289idx0);

    auto fvec289 = [flut289](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut289[i](I));
        return ret;
    };

    std::cerr << "\rLUT289   ";
    long gin289 = 1 * gout280[1] + 2 * ct_x11 + 4 * gout288[0];
    std::vector<long> gout289 = fvec289(gin289);

    std::vector<RotationPoly> lut290;
    std::vector<long (*)(long)> flut290;
    auto lut290idx0 = [](long I) -> long {
        /* GATE 182 (LUT2 _1638_ INIT 0x6 PERM 01) */
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
    lut290.push_back(ctx.genrate_lut(lut290idx0));
    flut290.push_back(lut290idx0);

    auto fvec290 = [flut290](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut290[i](I));
        return ret;
    };

    std::cerr << "\rLUT290   ";
    long gin290 = 1 * gout287[1] + 2 * ct_x9;
    std::vector<long> gout290 = fvec290(gin290);

    std::vector<RotationPoly> lut291;
    std::vector<long (*)(long)> flut291;
    auto lut291idx0 = [](long I) -> long {
        /* GATE 147 (LUT3 _1603_ INIT 0xb0 PERM 102) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut291.push_back(ctx.genrate_lut(lut291idx0));
    flut291.push_back(lut291idx0);

    auto lut291idx1 = [](long I) -> long {
        /* GATE 115 (LUT3 _1571_ INIT 0xb4 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut291.push_back(ctx.genrate_lut(lut291idx1));
    flut291.push_back(lut291idx1);

    auto fvec291 = [flut291](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut291[i](I));
        return ret;
    };

    std::cerr << "\rLUT291   ";
    long gin291 = 1 * gout88[0] + 2 * ct_y7 + 4 * gout279[0];
    std::vector<long> gout291 = fvec291(gin291);

    std::vector<RotationPoly> lut292;
    std::vector<long (*)(long)> flut292;
    auto lut292idx0 = [](long I) -> long {
        /* GATE 181 (LUT3 _1637_ INIT 0x60 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut292.push_back(ctx.genrate_lut(lut292idx0));
    flut292.push_back(lut292idx0);

    auto lut292idx1 = [](long I) -> long {
        /* GATE 146 (LUT3 _1602_ INIT 0x96 PERM 021) */
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
    lut292.push_back(ctx.genrate_lut(lut292idx1));
    flut292.push_back(lut292idx1);

    auto fvec292 = [flut292](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut292[i](I));
        return ret;
    };

    std::cerr << "\rLUT292   ";
    long gin292 = 1 * gout291[0] + 2 * ct_x8 + 4 * ct_y8;
    std::vector<long> gout292 = fvec292(gin292);

    std::vector<RotationPoly> lut293;
    std::vector<long (*)(long)> flut293;
    auto lut293idx0 = [](long I) -> long {
        /* GATE 220 (LUT3 _1676_ INIT 0xe8 PERM 201) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
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
    long gin293 = 1 * gout287[1] + 2 * ct_x9 + 4 * gout292[0];
    std::vector<long> gout293 = fvec293(gin293);

    std::vector<RotationPoly> lut294;
    std::vector<long (*)(long)> flut294;
    auto lut294idx0 = [](long I) -> long {
        /* GATE 114 (LUT2 _1570_ INIT 0x6 PERM 01) */
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
    lut294.push_back(ctx.genrate_lut(lut294idx0));
    flut294.push_back(lut294idx0);

    auto fvec294 = [flut294](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut294[i](I));
        return ret;
    };

    std::cerr << "\rLUT294   ";
    long gin294 = 1 * gout291[1] + 2 * ct_x7;
    std::vector<long> gout294 = fvec294(gin294);

    std::vector<RotationPoly> lut295;
    std::vector<long (*)(long)> flut295;
    auto lut295idx0 = [](long I) -> long {
        /* GATE 90 (LUT3 _1546_ INIT 0xb0 PERM 102) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut295.push_back(ctx.genrate_lut(lut295idx0));
    flut295.push_back(lut295idx0);

    auto lut295idx1 = [](long I) -> long {
        /* GATE 66 (LUT3 _1522_ INIT 0xb4 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut295.push_back(ctx.genrate_lut(lut295idx1));
    flut295.push_back(lut295idx1);

    auto fvec295 = [flut295](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut295[i](I));
        return ret;
    };

    std::cerr << "\rLUT295   ";
    long gin295 = 1 * gout38[0] + 2 * ct_y5 + 4 * gout279[0];
    std::vector<long> gout295 = fvec295(gin295);

    std::vector<RotationPoly> lut296;
    std::vector<long (*)(long)> flut296;
    auto lut296idx0 = [](long I) -> long {
        /* GATE 89 (LUT2 _1545_ INIT 0x6 PERM 01) */
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
    lut296.push_back(ctx.genrate_lut(lut296idx0));
    flut296.push_back(lut296idx0);

    auto fvec296 = [flut296](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut296[i](I));
        return ret;
    };

    std::cerr << "\rLUT296   ";
    long gin296 = 1 * gout295[0] + 2 * ct_y6;
    std::vector<long> gout296 = fvec296(gin296);

    std::vector<RotationPoly> lut297;
    std::vector<long (*)(long)> flut297;
    auto lut297idx0 = [](long I) -> long {
        /* GATE 49 (LUT3 _1505_ INIT 0xb0 PERM 201) */
        switch (I) {
            case  0: return 0;
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
    lut297.push_back(ctx.genrate_lut(lut297idx0));
    flut297.push_back(lut297idx0);

    auto lut297idx1 = [](long I) -> long {
        /* GATE 33 (LUT3 _1489_ INIT 0xb4 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut297.push_back(ctx.genrate_lut(lut297idx1));
    flut297.push_back(lut297idx1);

    auto fvec297 = [flut297](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut297[i](I));
        return ret;
    };

    std::cerr << "\rLUT297   ";
    long gin297 = 1 * gout37[0] + 2 * gout279[0] + 4 * ct_y3;
    std::vector<long> gout297 = fvec297(gin297);

    std::vector<RotationPoly> lut298;
    std::vector<long (*)(long)> flut298;
    auto lut298idx0 = [](long I) -> long {
        /* GATE 48 (LUT2 _1504_ INIT 0x6 PERM 01) */
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
    lut298.push_back(ctx.genrate_lut(lut298idx0));
    flut298.push_back(lut298idx0);

    auto fvec298 = [flut298](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut298[i](I));
        return ret;
    };

    std::cerr << "\rLUT298   ";
    long gin298 = 1 * gout297[0] + 2 * ct_y4;
    std::vector<long> gout298 = fvec298(gin298);

    std::vector<RotationPoly> lut299;
    std::vector<long (*)(long)> flut299;
    auto lut299idx0 = [](long I) -> long {
        /* GATE 22 (LUT3 _1478_ INIT 0xe0 PERM 210) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut299.push_back(ctx.genrate_lut(lut299idx0));
    flut299.push_back(lut299idx0);

    auto lut299idx1 = [](long I) -> long {
        /* GATE 12 (LUT3 _1468_ INIT 0x87 PERM 021) */
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
    lut299.push_back(ctx.genrate_lut(lut299idx1));
    flut299.push_back(lut299idx1);

    auto fvec299 = [flut299](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut299[i](I));
        return ret;
    };

    std::cerr << "\rLUT299   ";
    long gin299 = 1 * gout279[0] + 2 * ct_y1 + 4 * ct_y0;
    std::vector<long> gout299 = fvec299(gin299);

    std::vector<RotationPoly> lut300;
    std::vector<long (*)(long)> flut300;
    auto lut300idx0 = [](long I) -> long {
        /* GATE 21 (LUT2 _1477_ INIT 0x6 PERM 01) */
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
    lut300.push_back(ctx.genrate_lut(lut300idx0));
    flut300.push_back(lut300idx0);

    auto fvec300 = [flut300](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut300[i](I));
        return ret;
    };

    std::cerr << "\rLUT300   ";
    long gin300 = 1 * gout299[0] + 2 * ct_y2;
    std::vector<long> gout300 = fvec300(gin300);

    std::vector<RotationPoly> lut301;
    std::vector<long (*)(long)> flut301;
    auto lut301idx0 = [](long I) -> long {
        /* GATE 20 (LUT3 _1476_ INIT 0x2b PERM 012) */
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
    lut301.push_back(ctx.genrate_lut(lut301idx0));
    flut301.push_back(lut301idx0);

    auto lut301idx1 = [](long I) -> long {
        /* GATE 11 (LUT3 _1467_ INIT 0x69 PERM 012) */
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
    lut301.push_back(ctx.genrate_lut(lut301idx1));
    flut301.push_back(lut301idx1);

    auto fvec301 = [flut301](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut301[i](I));
        return ret;
    };

    std::cerr << "\rLUT301   ";
    long gin301 = 1 * gout299[1] + 2 * gout65[0] + 4 * ct_x1;
    std::vector<long> gout301 = fvec301(gin301);

    std::vector<RotationPoly> lut302;
    std::vector<long (*)(long)> flut302;
    auto lut302idx0 = [](long I) -> long {
        /* GATE 32 (LUT3 _1488_ INIT 0x2b PERM 012) */
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
    lut302.push_back(ctx.genrate_lut(lut302idx0));
    flut302.push_back(lut302idx0);

    auto lut302idx1 = [](long I) -> long {
        /* GATE 19 (LUT3 _1475_ INIT 0x69 PERM 012) */
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
    lut302.push_back(ctx.genrate_lut(lut302idx1));
    flut302.push_back(lut302idx1);

    auto fvec302 = [flut302](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut302[i](I));
        return ret;
    };

    std::cerr << "\rLUT302   ";
    long gin302 = 1 * gout301[0] + 2 * gout300[0] + 4 * ct_x2;
    std::vector<long> gout302 = fvec302(gin302);

    std::vector<RotationPoly> lut303;
    std::vector<long (*)(long)> flut303;
    auto lut303idx0 = [](long I) -> long {
        /* GATE 47 (LUT3 _1503_ INIT 0x2b PERM 012) */
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
    lut303.push_back(ctx.genrate_lut(lut303idx0));
    flut303.push_back(lut303idx0);

    auto lut303idx1 = [](long I) -> long {
        /* GATE 31 (LUT3 _1487_ INIT 0x69 PERM 012) */
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
    lut303.push_back(ctx.genrate_lut(lut303idx1));
    flut303.push_back(lut303idx1);

    auto fvec303 = [flut303](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut303[i](I));
        return ret;
    };

    std::cerr << "\rLUT303   ";
    long gin303 = 1 * gout302[0] + 2 * gout297[1] + 4 * ct_x3;
    std::vector<long> gout303 = fvec303(gin303);

    std::vector<RotationPoly> lut304;
    std::vector<long (*)(long)> flut304;
    auto lut304idx0 = [](long I) -> long {
        /* GATE 65 (LUT3 _1521_ INIT 0x2b PERM 012) */
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
    lut304.push_back(ctx.genrate_lut(lut304idx0));
    flut304.push_back(lut304idx0);

    auto lut304idx1 = [](long I) -> long {
        /* GATE 46 (LUT3 _1502_ INIT 0x69 PERM 012) */
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
    lut304.push_back(ctx.genrate_lut(lut304idx1));
    flut304.push_back(lut304idx1);

    auto fvec304 = [flut304](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut304[i](I));
        return ret;
    };

    std::cerr << "\rLUT304   ";
    long gin304 = 1 * gout303[0] + 2 * gout298[0] + 4 * ct_x4;
    std::vector<long> gout304 = fvec304(gin304);

    std::vector<RotationPoly> lut305;
    std::vector<long (*)(long)> flut305;
    auto lut305idx0 = [](long I) -> long {
        /* GATE 88 (LUT3 _1544_ INIT 0x2b PERM 012) */
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
    lut305.push_back(ctx.genrate_lut(lut305idx0));
    flut305.push_back(lut305idx0);

    auto lut305idx1 = [](long I) -> long {
        /* GATE 64 (LUT3 _1520_ INIT 0x69 PERM 012) */
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
    lut305.push_back(ctx.genrate_lut(lut305idx1));
    flut305.push_back(lut305idx1);

    auto fvec305 = [flut305](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut305[i](I));
        return ret;
    };

    std::cerr << "\rLUT305   ";
    long gin305 = 1 * gout304[0] + 2 * gout295[1] + 4 * ct_x5;
    std::vector<long> gout305 = fvec305(gin305);

    std::vector<RotationPoly> lut306;
    std::vector<long (*)(long)> flut306;
    auto lut306idx0 = [](long I) -> long {
        /* GATE 113 (LUT3 _1569_ INIT 0x2b PERM 012) */
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
    lut306.push_back(ctx.genrate_lut(lut306idx0));
    flut306.push_back(lut306idx0);

    auto lut306idx1 = [](long I) -> long {
        /* GATE 87 (LUT3 _1543_ INIT 0x69 PERM 012) */
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
    lut306.push_back(ctx.genrate_lut(lut306idx1));
    flut306.push_back(lut306idx1);

    auto fvec306 = [flut306](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut306[i](I));
        return ret;
    };

    std::cerr << "\rLUT306   ";
    long gin306 = 1 * gout305[0] + 2 * gout296[0] + 4 * ct_x6;
    std::vector<long> gout306 = fvec306(gin306);

    std::vector<RotationPoly> lut307;
    std::vector<long (*)(long)> flut307;
    auto lut307idx0 = [](long I) -> long {
        /* GATE 145 (LUT3 _1601_ INIT 0x2b PERM 012) */
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
    lut307.push_back(ctx.genrate_lut(lut307idx0));
    flut307.push_back(lut307idx0);

    auto fvec307 = [flut307](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut307[i](I));
        return ret;
    };

    std::cerr << "\rLUT307   ";
    long gin307 = 1 * gout306[0] + 2 * gout291[1] + 4 * ct_x7;
    std::vector<long> gout307 = fvec307(gin307);

    std::vector<RotationPoly> lut308;
    std::vector<long (*)(long)> flut308;
    auto lut308idx0 = [](long I) -> long {
        /* GATE 219 (LUT3 _1675_ INIT 0x40 PERM 102) */
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
    lut308.push_back(ctx.genrate_lut(lut308idx0));
    flut308.push_back(lut308idx0);

    auto lut308idx1 = [](long I) -> long {
        /* GATE 144 (LUT2 _1600_ INIT 0x9 PERM 12) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut308.push_back(ctx.genrate_lut(lut308idx1));
    flut308.push_back(lut308idx1);

    auto fvec308 = [flut308](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut308[i](I));
        return ret;
    };

    std::cerr << "\rLUT308   ";
    long gin308 = 1 * gout290[0] + 2 * gout307[0] + 4 * gout292[1];
    std::vector<long> gout308 = fvec308(gin308);

    std::vector<RotationPoly> lut309;
    std::vector<long (*)(long)> flut309;
    auto lut309idx0 = [](long I) -> long {
        /* GATE 259 (LUT3 _1715_ INIT 0xe0 PERM 102) */
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
    lut309.push_back(ctx.genrate_lut(lut309idx0));
    flut309.push_back(lut309idx0);

    auto lut309idx1 = [](long I) -> long {
        /* GATE 218 (LUT3 _1674_ INIT 0x1e PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut309.push_back(ctx.genrate_lut(lut309idx1));
    flut309.push_back(lut309idx1);

    auto fvec309 = [flut309](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut309[i](I));
        return ret;
    };

    std::cerr << "\rLUT309   ";
    long gin309 = 1 * gout308[0] + 2 * gout293[0] + 4 * gout288[1];
    std::vector<long> gout309 = fvec309(gin309);

    std::vector<RotationPoly> lut310;
    std::vector<long (*)(long)> flut310;
    auto lut310idx0 = [](long I) -> long {
        /* GATE 305 (LUT3 _1761_ INIT 0x7 PERM 210) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
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
    long gin310 = 1 * gout289[0] + 2 * gout309[0] + 4 * gout286[0];
    std::vector<long> gout310 = fvec310(gin310);

    std::vector<RotationPoly> lut311;
    std::vector<long (*)(long)> flut311;
    auto lut311idx0 = [](long I) -> long {
        /* GATE 350 (LUT3 _1806_ INIT 0x2b PERM 012) */
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
    lut311.push_back(ctx.genrate_lut(lut311idx0));
    flut311.push_back(lut311idx0);

    auto lut311idx1 = [](long I) -> long {
        /* GATE 304 (LUT3 _1760_ INIT 0x69 PERM 012) */
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
    lut311.push_back(ctx.genrate_lut(lut311idx1));
    flut311.push_back(lut311idx1);

    auto fvec311 = [flut311](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut311[i](I));
        return ret;
    };

    std::cerr << "\rLUT311   ";
    long gin311 = 1 * gout310[0] + 2 * gout281[1] + 4 * ct_x12;
    std::vector<long> gout311 = fvec311(gin311);

    std::vector<RotationPoly> lut312;
    std::vector<long (*)(long)> flut312;
    auto lut312idx0 = [](long I) -> long {
        /* GATE 398 (LUT3 _1854_ INIT 0xb2 PERM 021) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut312.push_back(ctx.genrate_lut(lut312idx0));
    flut312.push_back(lut312idx0);

    auto fvec312 = [flut312](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut312[i](I));
        return ret;
    };

    std::cerr << "\rLUT312   ";
    long gin312 = 1 * gout311[0] + 2 * gout282[1] + 4 * ct_x13;
    std::vector<long> gout312 = fvec312(gin312);

    std::vector<RotationPoly> lut313;
    std::vector<long (*)(long)> flut313;
    auto lut313idx0 = [](long I) -> long {
        /* GATE 447 (LUT3 _1903_ INIT 0x2b PERM 012) */
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
    lut313.push_back(ctx.genrate_lut(lut313idx0));
    flut313.push_back(lut313idx0);

    auto lut313idx1 = [](long I) -> long {
        /* GATE 397 (LUT3 _1853_ INIT 0x69 PERM 012) */
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
    lut313.push_back(ctx.genrate_lut(lut313idx1));
    flut313.push_back(lut313idx1);

    auto fvec313 = [flut313](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut313[i](I));
        return ret;
    };

    std::cerr << "\rLUT313   ";
    long gin313 = 1 * gout312[0] + 2 * gout283[1] + 4 * ct_x14;
    std::vector<long> gout313 = fvec313(gin313);

    std::vector<RotationPoly> lut314;
    std::vector<long (*)(long)> flut314;
    auto lut314idx0 = [](long I) -> long {
        /* GATE 446 (LUT3 _1902_ INIT 0x41 PERM 201) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
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
    long gin314 = 1 * gout284[0] + 2 * gout313[0] + 4 * gout273[0];
    std::vector<long> gout314 = fvec314(gin314);

    std::vector<RotationPoly> lut315;
    std::vector<long (*)(long)> flut315;
    auto lut315idx0 = [](long I) -> long {
        /* GATE 396 (LUT3 _1852_ INIT 0xac PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut315.push_back(ctx.genrate_lut(lut315idx0));
    flut315.push_back(lut315idx0);

    auto fvec315 = [flut315](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut315[i](I));
        return ret;
    };

    std::cerr << "\rLUT315   ";
    long gin315 = 1 * gout270[1] + 2 * gout313[1] + 4 * gout273[0];
    std::vector<long> gout315 = fvec315(gin315);

    std::vector<RotationPoly> lut316;
    std::vector<long (*)(long)> flut316;
    auto lut316idx0 = [](long I) -> long {
        /* GATE 349 (LUT3 _1805_ INIT 0x41 PERM 201) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut316.push_back(ctx.genrate_lut(lut316idx0));
    flut316.push_back(lut316idx0);

    auto fvec316 = [flut316](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut316[i](I));
        return ret;
    };

    std::cerr << "\rLUT316   ";
    long gin316 = 1 * gout285[0] + 2 * gout311[0] + 4 * gout273[0];
    std::vector<long> gout316 = fvec316(gin316);

    std::vector<RotationPoly> lut317;
    std::vector<long (*)(long)> flut317;
    auto lut317idx0 = [](long I) -> long {
        /* GATE 303 (LUT3 _1759_ INIT 0xac PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
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
    long gin317 = 1 * gout256[1] + 2 * gout311[1] + 4 * gout273[0];
    std::vector<long> gout317 = fvec317(gin317);

    std::vector<RotationPoly> lut318;
    std::vector<long (*)(long)> flut318;
    auto lut318idx0 = [](long I) -> long {
        /* GATE 258 (LUT3 _1714_ INIT 0x1e PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
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
    long gin318 = 1 * gout309[0] + 2 * gout288[0] + 4 * gout286[0];
    std::vector<long> gout318 = fvec318(gin318);

    std::vector<RotationPoly> lut319;
    std::vector<long (*)(long)> flut319;
    auto lut319idx0 = [](long I) -> long {
        /* GATE 217 (LUT3 _1673_ INIT 0xac PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut319.push_back(ctx.genrate_lut(lut319idx0));
    flut319.push_back(lut319idx0);

    auto fvec319 = [flut319](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut319[i](I));
        return ret;
    };

    std::cerr << "\rLUT319   ";
    long gin319 = 1 * gout254[1] + 2 * gout309[1] + 4 * gout273[0];
    std::vector<long> gout319 = fvec319(gin319);

    std::vector<RotationPoly> lut320;
    std::vector<long (*)(long)> flut320;
    auto lut320idx0 = [](long I) -> long {
        /* GATE 180 (LUT3 _1636_ INIT 0xd PERM 210) */
        switch (I) {
            case  0: return 1;
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
    lut320.push_back(ctx.genrate_lut(lut320idx0));
    flut320.push_back(lut320idx0);

    auto fvec320 = [flut320](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut320[i](I));
        return ret;
    };

    std::cerr << "\rLUT320   ";
    long gin320 = 1 * gout292[0] + 2 * gout307[0] + 4 * gout292[1];
    std::vector<long> gout320 = fvec320(gin320);

    std::vector<RotationPoly> lut321;
    std::vector<long (*)(long)> flut321;
    auto lut321idx0 = [](long I) -> long {
        /* GATE 179 (LUT2 _1635_ INIT 0x9 PERM 01) */
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
    lut321.push_back(ctx.genrate_lut(lut321idx0));
    flut321.push_back(lut321idx0);

    auto fvec321 = [flut321](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut321[i](I));
        return ret;
    };

    std::cerr << "\rLUT321   ";
    long gin321 = 1 * gout320[0] + 2 * gout290[0];
    std::vector<long> gout321 = fvec321(gin321);

    std::vector<RotationPoly> lut322;
    std::vector<long (*)(long)> flut322;
    auto lut322idx0 = [](long I) -> long {
        /* GATE 143 (LUT3 _1599_ INIT 0xac PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
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
    long gin322 = 1 * gout252[1] + 2 * gout308[1] + 4 * gout273[0];
    std::vector<long> gout322 = fvec322(gin322);

    std::vector<RotationPoly> lut323;
    std::vector<long (*)(long)> flut323;
    auto lut323idx0 = [](long I) -> long {
        /* GATE 112 (LUT3 _1568_ INIT 0x14 PERM 210) */
        switch (I) {
            case  0: return 0;
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
    lut323.push_back(ctx.genrate_lut(lut323idx0));
    flut323.push_back(lut323idx0);

    auto fvec323 = [flut323](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut323[i](I));
        return ret;
    };

    std::cerr << "\rLUT323   ";
    long gin323 = 1 * gout294[0] + 2 * gout306[0] + 4 * gout273[0];
    std::vector<long> gout323 = fvec323(gin323);

    std::vector<RotationPoly> lut324;
    std::vector<long (*)(long)> flut324;
    auto lut324idx0 = [](long I) -> long {
        /* GATE 86 (LUT3 _1542_ INIT 0xac PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut324.push_back(ctx.genrate_lut(lut324idx0));
    flut324.push_back(lut324idx0);

    auto fvec324 = [flut324](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut324[i](I));
        return ret;
    };

    std::cerr << "\rLUT324   ";
    long gin324 = 1 * gout232[1] + 2 * gout306[1] + 4 * gout273[0];
    std::vector<long> gout324 = fvec324(gin324);

    std::vector<RotationPoly> lut325;
    std::vector<long (*)(long)> flut325;
    auto lut325idx0 = [](long I) -> long {
        /* GATE 63 (LUT3 _1519_ INIT 0xac PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut325.push_back(ctx.genrate_lut(lut325idx0));
    flut325.push_back(lut325idx0);

    auto fvec325 = [flut325](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut325[i](I));
        return ret;
    };

    std::cerr << "\rLUT325   ";
    long gin325 = 1 * gout231[1] + 2 * gout305[1] + 4 * gout273[0];
    std::vector<long> gout325 = fvec325(gin325);

    std::vector<RotationPoly> lut326;
    std::vector<long (*)(long)> flut326;
    auto lut326idx0 = [](long I) -> long {
        /* GATE 45 (LUT3 _1501_ INIT 0xac PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut326.push_back(ctx.genrate_lut(lut326idx0));
    flut326.push_back(lut326idx0);

    auto fvec326 = [flut326](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut326[i](I));
        return ret;
    };

    std::cerr << "\rLUT326   ";
    long gin326 = 1 * gout214[1] + 2 * gout304[1] + 4 * gout273[0];
    std::vector<long> gout326 = fvec326(gin326);

    std::vector<RotationPoly> lut327;
    std::vector<long (*)(long)> flut327;
    auto lut327idx0 = [](long I) -> long {
        /* GATE 30 (LUT3 _1486_ INIT 0xac PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
            default: assert(0);
        };
    };
    lut327.push_back(ctx.genrate_lut(lut327idx0));
    flut327.push_back(lut327idx0);

    auto fvec327 = [flut327](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut327[i](I));
        return ret;
    };

    std::cerr << "\rLUT327   ";
    long gin327 = 1 * gout213[1] + 2 * gout303[1] + 4 * gout273[0];
    std::vector<long> gout327 = fvec327(gin327);

    std::vector<RotationPoly> lut328;
    std::vector<long (*)(long)> flut328;
    auto lut328idx0 = [](long I) -> long {
        /* GATE 18 (LUT3 _1474_ INIT 0xac PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
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
    long gin328 = 1 * gout212[1] + 2 * gout302[1] + 4 * gout273[0];
    std::vector<long> gout328 = fvec328(gin328);

    std::vector<RotationPoly> lut329;
    std::vector<long (*)(long)> flut329;
    auto lut329idx0 = [](long I) -> long {
        /* GATE 2 (LUT3 _1458_ INIT 0x7 PERM 012) */
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
    lut329.push_back(ctx.genrate_lut(lut329idx0));
    flut329.push_back(lut329idx0);

    auto fvec329 = [flut329](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut329[i](I));
        return ret;
    };

    std::cerr << "\rLUT329   ";
    long gin329 = 1 * gout81[1] + 2 * gout272[0] + 4 * gout279[0];
    std::vector<long> gout329 = fvec329(gin329);

    std::vector<RotationPoly> lut330;
    std::vector<long (*)(long)> flut330;
    auto lut330idx0 = [](long I) -> long {
        /* GATE 395 (LUT2 _1851_ INIT 0xe PERM 01) */
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
    lut330.push_back(ctx.genrate_lut(lut330idx0));
    flut330.push_back(lut330idx0);

    auto fvec330 = [flut330](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut330[i](I));
        return ret;
    };

    std::cerr << "\rLUT330   ";
    long gin330 = 1 * gout315[0] + 2 * gout329[0];
    std::vector<long> gout330 = fvec330(gin330);

    std::vector<RotationPoly> lut331;
    std::vector<long (*)(long)> flut331;
    auto lut331idx0 = [](long I) -> long {
        /* GATE 348 (LUT3 _1804_ INIT 0xfe PERM 012) */
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
    lut331.push_back(ctx.genrate_lut(lut331idx0));
    flut331.push_back(lut331idx0);

    auto fvec331 = [flut331](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut331[i](I));
        return ret;
    };

    std::cerr << "\rLUT331   ";
    long gin331 = 1 * gout316[0] + 2 * gout274[0] + 4 * gout329[0];
    std::vector<long> gout331 = fvec331(gin331);

    std::vector<RotationPoly> lut332;
    std::vector<long (*)(long)> flut332;
    auto lut332idx0 = [](long I) -> long {
        /* GATE 302 (LUT2 _1758_ INIT 0xe PERM 01) */
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
    lut332.push_back(ctx.genrate_lut(lut332idx0));
    flut332.push_back(lut332idx0);

    auto fvec332 = [flut332](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut332[i](I));
        return ret;
    };

    std::cerr << "\rLUT332   ";
    long gin332 = 1 * gout317[0] + 2 * gout329[0];
    std::vector<long> gout332 = fvec332(gin332);

    std::vector<RotationPoly> lut333;
    std::vector<long (*)(long)> flut333;
    auto lut333idx0 = [](long I) -> long {
        /* GATE 257 (LUT3 _1713_ INIT 0xb PERM 102) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut333.push_back(ctx.genrate_lut(lut333idx0));
    flut333.push_back(lut333idx0);

    auto fvec333 = [flut333](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut333[i](I));
        return ret;
    };

    std::cerr << "\rLUT333   ";
    long gin333 = 1 * gout318[0] + 2 * gout273[0] + 4 * gout329[0];
    std::vector<long> gout333 = fvec333(gin333);

    std::vector<RotationPoly> lut334;
    std::vector<long (*)(long)> flut334;
    auto lut334idx0 = [](long I) -> long {
        /* GATE 256 (LUT2 _1712_ INIT 0xb PERM 01) */
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
    lut334.push_back(ctx.genrate_lut(lut334idx0));
    flut334.push_back(lut334idx0);

    auto fvec334 = [flut334](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut334[i](I));
        return ret;
    };

    std::cerr << "\rLUT334   ";
    long gin334 = 1 * gout275[0] + 2 * gout333[0];
    std::vector<long> gout334 = fvec334(gin334);

    std::vector<RotationPoly> lut335;
    std::vector<long (*)(long)> flut335;
    auto lut335idx0 = [](long I) -> long {
        /* GATE 216 (LUT2 _1672_ INIT 0xe PERM 01) */
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
    lut335.push_back(ctx.genrate_lut(lut335idx0));
    flut335.push_back(lut335idx0);

    auto fvec335 = [flut335](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut335[i](I));
        return ret;
    };

    std::cerr << "\rLUT335   ";
    long gin335 = 1 * gout319[0] + 2 * gout329[0];
    std::vector<long> gout335 = fvec335(gin335);

    std::vector<RotationPoly> lut336;
    std::vector<long (*)(long)> flut336;
    auto lut336idx0 = [](long I) -> long {
        /* GATE 178 (LUT3 _1634_ INIT 0xb PERM 102) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut336.push_back(ctx.genrate_lut(lut336idx0));
    flut336.push_back(lut336idx0);

    auto fvec336 = [flut336](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut336[i](I));
        return ret;
    };

    std::cerr << "\rLUT336   ";
    long gin336 = 1 * gout321[0] + 2 * gout273[0] + 4 * gout329[0];
    std::vector<long> gout336 = fvec336(gin336);

    std::vector<RotationPoly> lut337;
    std::vector<long (*)(long)> flut337;
    auto lut337idx0 = [](long I) -> long {
        /* GATE 177 (LUT2 _1633_ INIT 0xb PERM 01) */
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
    lut337.push_back(ctx.genrate_lut(lut337idx0));
    flut337.push_back(lut337idx0);

    auto fvec337 = [flut337](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut337[i](I));
        return ret;
    };

    std::cerr << "\rLUT337   ";
    long gin337 = 1 * gout276[0] + 2 * gout336[0];
    std::vector<long> gout337 = fvec337(gin337);

    std::vector<RotationPoly> lut338;
    std::vector<long (*)(long)> flut338;
    auto lut338idx0 = [](long I) -> long {
        /* GATE 142 (LUT2 _1598_ INIT 0xe PERM 01) */
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
    lut338.push_back(ctx.genrate_lut(lut338idx0));
    flut338.push_back(lut338idx0);

    auto fvec338 = [flut338](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut338[i](I));
        return ret;
    };

    std::cerr << "\rLUT338   ";
    long gin338 = 1 * gout322[0] + 2 * gout329[0];
    std::vector<long> gout338 = fvec338(gin338);

    std::vector<RotationPoly> lut339;
    std::vector<long (*)(long)> flut339;
    auto lut339idx0 = [](long I) -> long {
        /* GATE 111 (LUT3 _1567_ INIT 0xf1 PERM 012) */
        switch (I) {
            case  0: return 1;
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
    lut339.push_back(ctx.genrate_lut(lut339idx0));
    flut339.push_back(lut339idx0);

    auto fvec339 = [flut339](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut339[i](I));
        return ret;
    };

    std::cerr << "\rLUT339   ";
    long gin339 = 1 * gout277[0] + 2 * gout323[0] + 4 * gout329[0];
    std::vector<long> gout339 = fvec339(gin339);

    std::vector<RotationPoly> lut340;
    std::vector<long (*)(long)> flut340;
    auto lut340idx0 = [](long I) -> long {
        /* GATE 85 (LUT2 _1541_ INIT 0xe PERM 01) */
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
    lut340.push_back(ctx.genrate_lut(lut340idx0));
    flut340.push_back(lut340idx0);

    auto fvec340 = [flut340](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut340[i](I));
        return ret;
    };

    std::cerr << "\rLUT340   ";
    long gin340 = 1 * gout324[0] + 2 * gout329[0];
    std::vector<long> gout340 = fvec340(gin340);

    std::vector<RotationPoly> lut341;
    std::vector<long (*)(long)> flut341;
    auto lut341idx0 = [](long I) -> long {
        /* GATE 62 (LUT2 _1518_ INIT 0xe PERM 01) */
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
    lut341.push_back(ctx.genrate_lut(lut341idx0));
    flut341.push_back(lut341idx0);

    auto fvec341 = [flut341](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut341[i](I));
        return ret;
    };

    std::cerr << "\rLUT341   ";
    long gin341 = 1 * gout325[0] + 2 * gout329[0];
    std::vector<long> gout341 = fvec341(gin341);

    std::vector<RotationPoly> lut342;
    std::vector<long (*)(long)> flut342;
    auto lut342idx0 = [](long I) -> long {
        /* GATE 44 (LUT2 _1500_ INIT 0xe PERM 01) */
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
    lut342.push_back(ctx.genrate_lut(lut342idx0));
    flut342.push_back(lut342idx0);

    auto fvec342 = [flut342](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut342[i](I));
        return ret;
    };

    std::cerr << "\rLUT342   ";
    long gin342 = 1 * gout326[0] + 2 * gout329[0];
    std::vector<long> gout342 = fvec342(gin342);

    std::vector<RotationPoly> lut343;
    std::vector<long (*)(long)> flut343;
    auto lut343idx0 = [](long I) -> long {
        /* GATE 29 (LUT2 _1485_ INIT 0xe PERM 01) */
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
    lut343.push_back(ctx.genrate_lut(lut343idx0));
    flut343.push_back(lut343idx0);

    auto fvec343 = [flut343](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut343[i](I));
        return ret;
    };

    std::cerr << "\rLUT343   ";
    long gin343 = 1 * gout327[0] + 2 * gout329[0];
    std::vector<long> gout343 = fvec343(gin343);

    std::vector<RotationPoly> lut344;
    std::vector<long (*)(long)> flut344;
    auto lut344idx0 = [](long I) -> long {
        /* GATE 17 (LUT2 _1473_ INIT 0xe PERM 01) */
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
    lut344.push_back(ctx.genrate_lut(lut344idx0));
    flut344.push_back(lut344idx0);

    auto fvec344 = [flut344](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut344[i](I));
        return ret;
    };

    std::cerr << "\rLUT344   ";
    long gin344 = 1 * gout328[0] + 2 * gout329[0];
    std::vector<long> gout344 = fvec344(gin344);

    std::vector<RotationPoly> lut345;
    std::vector<long (*)(long)> flut345;
    auto lut345idx0 = [](long I) -> long {
        /* GATE 14 (LUT3 _1470_ INIT 0x7 PERM 012) */
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
    lut345.push_back(ctx.genrate_lut(lut345idx0));
    flut345.push_back(lut345idx0);

    auto fvec345 = [flut345](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut345[i](I));
        return ret;
    };

    std::cerr << "\rLUT345   ";
    long gin345 = 1 * gout76[0] + 2 * gout273[0] + 4 * gout329[0];
    std::vector<long> gout345 = fvec345(gin345);

    std::vector<RotationPoly> lut346;
    std::vector<long (*)(long)> flut346;
    auto lut346idx0 = [](long I) -> long {
        /* GATE 10 (LUT3 _1466_ INIT 0x4f PERM 201) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            default: assert(0);
        };
    };
    lut346.push_back(ctx.genrate_lut(lut346idx0));
    flut346.push_back(lut346idx0);

    auto fvec346 = [flut346](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut346[i](I));
        return ret;
    };

    std::cerr << "\rLUT346   ";
    long gin346 = 1 * gout301[1] + 2 * gout345[0] + 4 * gout273[0];
    std::vector<long> gout346 = fvec346(gin346);

    std::vector<RotationPoly> lut347;
    std::vector<long (*)(long)> flut347;
    auto lut347idx0 = [](long I) -> long {
        /* GATE 1 (LUT2 _1457_ INIT 0xe PERM 10) */
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
    lut347.push_back(ctx.genrate_lut(lut347idx0));
    flut347.push_back(lut347idx0);

    auto fvec347 = [flut347](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut347[i](I));
        return ret;
    };

    std::cerr << "\rLUT347   ";
    long gin347 = 1 * gout278[0] + 2 * gout329[0];
    std::vector<long> gout347 = fvec347(gin347);

    std::vector<RotationPoly> lut348;
    std::vector<long (*)(long)> flut348;
    auto lut348idx0 = [](long I) -> long {
        /* GATE 466 (LUT3 _1922_ INIT 0x96 PERM 012) */
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
    lut348.push_back(ctx.genrate_lut(lut348idx0));
    flut348.push_back(lut348idx0);

    auto fvec348 = [flut348](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut348[i](I));
        return ret;
    };

    std::cerr << "\rLUT348   ";
    long gin348 = 1 * gout262[0] + 2 * gout217[0] + 4 * gout135[0];
    std::vector<long> gout348 = fvec348(gin348);

    std::vector<RotationPoly> lut349;
    std::vector<long (*)(long)> flut349;
    auto lut349idx0 = [](long I) -> long {
        /* GATE 454 (LUT3 _1910_ INIT 0x69 PERM 012) */
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
    lut349.push_back(ctx.genrate_lut(lut349idx0));
    flut349.push_back(lut349idx0);

    auto fvec349 = [flut349](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut349[i](I));
        return ret;
    };

    std::cerr << "\rLUT349   ";
    long gin349 = 1 * gout267[0] + 2 * gout264[0] + 4 * gout348[0];
    std::vector<long> gout349 = fvec349(gin349);

    std::vector<RotationPoly> lut350;
    std::vector<long (*)(long)> flut350;
    auto lut350idx0 = [](long I) -> long {
        /* GATE 453 (LUT3 _1909_ INIT 0x69 PERM 012) */
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
    lut350.push_back(ctx.genrate_lut(lut350idx0));
    flut350.push_back(lut350idx0);

    auto fvec350 = [flut350](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut350[i](I));
        return ret;
    };

    std::cerr << "\rLUT350   ";
    long gin350 = 1 * gout349[0] + 2 * gout259[0] + 4 * gout266[0];
    std::vector<long> gout350 = fvec350(gin350);

    std::vector<RotationPoly> lut351;
    std::vector<long (*)(long)> flut351;
    auto lut351idx0 = [](long I) -> long {
        /* GATE 452 (LUT3 _1908_ INIT 0x96 PERM 012) */
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
    lut351.push_back(ctx.genrate_lut(lut351idx0));
    flut351.push_back(lut351idx0);

    auto fvec351 = [flut351](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut351[i](I));
        return ret;
    };

    std::cerr << "\rLUT351   ";
    long gin351 = 1 * gout350[0] + 2 * gout269[0] + 4 * gout268[0];
    std::vector<long> gout351 = fvec351(gin351);

    std::vector<RotationPoly> lut352;
    std::vector<long (*)(long)> flut352;
    auto lut352idx0 = [](long I) -> long {
        /* GATE 450 (LUT3 _1906_ INIT 0x60 PERM 012) */
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
    lut352.push_back(ctx.genrate_lut(lut352idx0));
    flut352.push_back(lut352idx0);

    auto fvec352 = [flut352](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut352[i](I));
        return ret;
    };

    std::cerr << "\rLUT352   ";
    long gin352 = 1 * gout270[0] + 2 * gout351[0] + 4 * gout273[0];
    std::vector<long> gout352 = fvec352(gin352);

    std::vector<RotationPoly> lut353;
    std::vector<long (*)(long)> flut353;
    auto lut353idx0 = [](long I) -> long {
        /* GATE 445 (LUT3 _1901_ INIT 0xfe PERM 012) */
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
    lut353.push_back(ctx.genrate_lut(lut353idx0));
    flut353.push_back(lut353idx0);

    auto fvec353 = [flut353](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut353[i](I));
        return ret;
    };

    std::cerr << "\rLUT353   ";
    long gin353 = 1 * gout314[0] + 2 * gout352[0] + 4 * gout329[0];
    std::vector<long> gout353 = fvec353(gin353);

    std::cerr << "\r          \r";
    std::vector<long> out;
    out.push_back(gout347[0]); /* out0 */
    out.push_back(gout346[0]); /* out1 */
    out.push_back(gout344[0]); /* out2 */
    out.push_back(gout343[0]); /* out3 */
    out.push_back(gout342[0]); /* out4 */
    out.push_back(gout341[0]); /* out5 */
    out.push_back(gout340[0]); /* out6 */
    out.push_back(gout339[0]); /* out7 */
    out.push_back(gout338[0]); /* out8 */
    out.push_back(gout337[0]); /* out9 */
    out.push_back(gout335[0]); /* out10 */
    out.push_back(gout334[0]); /* out11 */
    out.push_back(gout332[0]); /* out12 */
    out.push_back(gout331[0]); /* out13 */
    out.push_back(gout330[0]); /* out14 */
    out.push_back(gout353[0]); /* out15 */
    return out;
}

std::vector<long>
test_add4_lut3fa(FHEContext& ctx, uint8_t a, uint8_t b)
{
    long ct_a0 = (a >> 0) & 1;
    long ct_a1 = (a >> 1) & 1;
    long ct_a2 = (a >> 2) & 1;
    long ct_a3 = (a >> 3) & 1;
    long ct_b0 = (b >> 0) & 1;
    long ct_b1 = (b >> 1) & 1;
    long ct_b2 = (b >> 2) & 1;
    long ct_b3 = (b >> 3) & 1;

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
    long gin0 = 1 * ct_a0 + 2 * ct_a1 + 1 * ct_b0 + 2 * ct_b1;
    std::vector<long> gout0 = vdecomp(gin0);

    std::cerr << "\rFA1    ";
    long gin1 = gout0[2] + 1 * ct_a2 + 2 * ct_a3 + 1 * ct_b2 + 2 * ct_b3;
    std::vector<long> gout1 = vdecomp(gin1);

    std::cerr << "\r          \r";
    std::vector<long> out;
    out.push_back(gout0[0]); /* out0 */
    out.push_back(gout0[1]); /* out1 */
    out.push_back(gout1[0]); /* out2 */
    out.push_back(gout1[1]); /* out3 */
    out.push_back(gout1[2]); /* out4 */
    return out;
}
std::vector<long>
test_calculator_lut3fa(FHEContext& ctx, uint8_t op, uint16_t x, uint16_t y)
{
    long ct_op0 = (op >> 0) & 1;
    long ct_op1 = (op >> 1) & 1;
    long ct_op2 = (op >> 2) & 1;
    long ct_op3 = (op >> 3) & 1;
    long ct_op4 = (op >> 4) & 1;
    long ct_op5 = (op >> 5) & 1;
    long ct_op6 = (op >> 6) & 1;
    long ct_op7 = (op >> 7) & 1;
    long ct_x0 = (x >> 0) & 1;
    long ct_x1 = (x >> 1) & 1;
    long ct_x2 = (x >> 2) & 1;
    long ct_x3 = (x >> 3) & 1;
    long ct_x4 = (x >> 4) & 1;
    long ct_x5 = (x >> 5) & 1;
    long ct_x6 = (x >> 6) & 1;
    long ct_x7 = (x >> 7) & 1;
    long ct_x8 = (x >> 8) & 1;
    long ct_x9 = (x >> 9) & 1;
    long ct_x10 = (x >> 10) & 1;
    long ct_x11 = (x >> 11) & 1;
    long ct_x12 = (x >> 12) & 1;
    long ct_x13 = (x >> 13) & 1;
    long ct_x14 = (x >> 14) & 1;
    long ct_x15 = (x >> 15) & 1;
    long ct_y0 = (y >> 0) & 1;
    long ct_y1 = (y >> 1) & 1;
    long ct_y2 = (y >> 2) & 1;
    long ct_y3 = (y >> 3) & 1;
    long ct_y4 = (y >> 4) & 1;
    long ct_y5 = (y >> 5) & 1;
    long ct_y6 = (y >> 6) & 1;
    long ct_y7 = (y >> 7) & 1;
    long ct_y8 = (y >> 8) & 1;
    long ct_y9 = (y >> 9) & 1;
    long ct_y10 = (y >> 10) & 1;
    long ct_y11 = (y >> 11) & 1;
    long ct_y12 = (y >> 12) & 1;
    long ct_y13 = (y >> 13) & 1;
    long ct_y14 = (y >> 14) & 1;
    long ct_y15 = (y >> 15) & 1;

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
    std::vector<long> gout0;
    gout0.push_back(1 - ct_y13);

    std::cerr << "\rINV1   ";
    std::vector<long> gout1;
    gout1.push_back(1 - ct_y12);

    std::cerr << "\rINV2   ";
    std::vector<long> gout2;
    gout2.push_back(1 - ct_y11);

    std::cerr << "\rINV3   ";
    std::vector<long> gout3;
    gout3.push_back(1 - ct_y1);

    std::cerr << "\rINV4   ";
    std::vector<long> gout4;
    gout4.push_back(1 - ct_y5);

    std::cerr << "\rINV5   ";
    std::vector<long> gout5;
    gout5.push_back(1 - ct_y2);

    std::cerr << "\rINV6   ";
    std::vector<long> gout6;
    gout6.push_back(1 - ct_y4);

    std::cerr << "\rINV7   ";
    std::vector<long> gout7;
    gout7.push_back(1 - ct_y3);

    std::cerr << "\rINV8   ";
    std::vector<long> gout8;
    gout8.push_back(1 - ct_y10);

    std::cerr << "\rINV9   ";
    std::vector<long> gout9;
    gout9.push_back(1 - ct_y0);

    std::cerr << "\rINV10   ";
    std::vector<long> gout10;
    gout10.push_back(1 - ct_y14);

    std::cerr << "\rINV11   ";
    std::vector<long> gout11;
    gout11.push_back(1 - ct_y9);

    std::cerr << "\rINV12   ";
    std::vector<long> gout12;
    gout12.push_back(1 - ct_y8);

    std::cerr << "\rINV13   ";
    std::vector<long> gout13;
    gout13.push_back(1 - ct_y7);

    std::cerr << "\rINV14   ";
    std::vector<long> gout14;
    gout14.push_back(1 - ct_y15);

    std::cerr << "\rINV15   ";
    std::vector<long> gout15;
    gout15.push_back(1 - ct_y6);

    std::cerr << "\rFA16    ";
    long gin16 = 1 * ct_x0 + 2 * ct_x1 + 1 * ct_y0 + 2 * ct_y1;
    std::vector<long> gout16 = vdecomp(gin16);

    std::vector<RotationPoly> lut17;
    std::vector<long (*)(long)> flut17;
    auto lut17idx0 = [](long I) -> long {
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
    lut17.push_back(ctx.genrate_lut(lut17idx0));
    flut17.push_back(lut17idx0);

    auto fvec17 = [flut17](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut17[i](I));
        return ret;
    };

    std::cerr << "\rLUT17   ";
    long gin17 = 1 * ct_y12 + 2 * ct_x3;
    std::vector<long> gout17 = fvec17(gin17);

    std::vector<RotationPoly> lut18;
    std::vector<long (*)(long)> flut18;
    auto lut18idx0 = [](long I) -> long {
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
    lut18.push_back(ctx.genrate_lut(lut18idx0));
    flut18.push_back(lut18idx0);

    auto fvec18 = [flut18](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut18[i](I));
        return ret;
    };

    std::cerr << "\rLUT18   ";
    long gin18 = 1 * ct_y2 + 2 * ct_x9;
    std::vector<long> gout18 = fvec18(gin18);

    std::vector<RotationPoly> lut19;
    std::vector<long (*)(long)> flut19;
    auto lut19idx0 = [](long I) -> long {
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
    lut19.push_back(ctx.genrate_lut(lut19idx0));
    flut19.push_back(lut19idx0);

    auto fvec19 = [flut19](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut19[i](I));
        return ret;
    };

    std::cerr << "\rLUT19   ";
    long gin19 = 1 * ct_x2 + 2 * ct_y8;
    std::vector<long> gout19 = fvec19(gin19);

    std::vector<RotationPoly> lut20;
    std::vector<long (*)(long)> flut20;
    auto lut20idx0 = [](long I) -> long {
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
    lut20.push_back(ctx.genrate_lut(lut20idx0));
    flut20.push_back(lut20idx0);

    auto fvec20 = [flut20](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut20[i](I));
        return ret;
    };

    std::cerr << "\rLUT20   ";
    long gin20 = 1 * ct_x8 + 2 * ct_y2;
    std::vector<long> gout20 = fvec20(gin20);

    std::vector<RotationPoly> lut21;
    std::vector<long (*)(long)> flut21;
    auto lut21idx0 = [](long I) -> long {
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
    lut21.push_back(ctx.genrate_lut(lut21idx0));
    flut21.push_back(lut21idx0);

    auto fvec21 = [flut21](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut21[i](I));
        return ret;
    };

    std::cerr << "\rLUT21   ";
    long gin21 = 1 * ct_x8 + 2 * ct_y1;
    std::vector<long> gout21 = fvec21(gin21);

    std::vector<RotationPoly> lut22;
    std::vector<long (*)(long)> flut22;
    auto lut22idx0 = [](long I) -> long {
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
    lut22.push_back(ctx.genrate_lut(lut22idx0));
    flut22.push_back(lut22idx0);

    auto fvec22 = [flut22](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut22[i](I));
        return ret;
    };

    std::cerr << "\rLUT22   ";
    long gin22 = 1 * ct_x6 + 2 * ct_y9;
    std::vector<long> gout22 = fvec22(gin22);

    std::vector<RotationPoly> lut23;
    std::vector<long (*)(long)> flut23;
    auto lut23idx0 = [](long I) -> long {
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
    lut23.push_back(ctx.genrate_lut(lut23idx0));
    flut23.push_back(lut23idx0);

    auto fvec23 = [flut23](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut23[i](I));
        return ret;
    };

    std::cerr << "\rLUT23   ";
    long gin23 = 1 * ct_x1 + 2 * ct_y8;
    std::vector<long> gout23 = fvec23(gin23);

    std::vector<RotationPoly> lut24;
    std::vector<long (*)(long)> flut24;
    auto lut24idx0 = [](long I) -> long {
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
    lut24.push_back(ctx.genrate_lut(lut24idx0));
    flut24.push_back(lut24idx0);

    auto fvec24 = [flut24](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut24[i](I));
        return ret;
    };

    std::cerr << "\rLUT24   ";
    long gin24 = 1 * ct_y7 + 2 * ct_x7;
    std::vector<long> gout24 = fvec24(gin24);

    std::vector<RotationPoly> lut25;
    std::vector<long (*)(long)> flut25;
    auto lut25idx0 = [](long I) -> long {
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
    lut25.push_back(ctx.genrate_lut(lut25idx0));
    flut25.push_back(lut25idx0);

    auto fvec25 = [flut25](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut25[i](I));
        return ret;
    };

    std::cerr << "\rLUT25   ";
    long gin25 = 1 * ct_y4 + 2 * ct_x5;
    std::vector<long> gout25 = fvec25(gin25);

    std::vector<RotationPoly> lut26;
    std::vector<long (*)(long)> flut26;
    auto lut26idx0 = [](long I) -> long {
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
    lut26.push_back(ctx.genrate_lut(lut26idx0));
    flut26.push_back(lut26idx0);

    auto fvec26 = [flut26](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut26[i](I));
        return ret;
    };

    std::cerr << "\rLUT26   ";
    long gin26 = 1 * ct_y6 + 2 * ct_x5;
    std::vector<long> gout26 = fvec26(gin26);

    std::vector<RotationPoly> lut27;
    std::vector<long (*)(long)> flut27;
    auto lut27idx0 = [](long I) -> long {
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
    lut27.push_back(ctx.genrate_lut(lut27idx0));
    flut27.push_back(lut27idx0);

    auto fvec27 = [flut27](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut27[i](I));
        return ret;
    };

    std::cerr << "\rLUT27   ";
    long gin27 = 1 * ct_x2 + 2 * ct_y4;
    std::vector<long> gout27 = fvec27(gin27);

    std::vector<RotationPoly> lut28;
    std::vector<long (*)(long)> flut28;
    auto lut28idx0 = [](long I) -> long {
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
    lut28.push_back(ctx.genrate_lut(lut28idx0));
    flut28.push_back(lut28idx0);

    auto fvec28 = [flut28](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut28[i](I));
        return ret;
    };

    std::cerr << "\rLUT28   ";
    long gin28 = 1 * ct_x12 + 2 * ct_y0;
    std::vector<long> gout28 = fvec28(gin28);

    std::vector<RotationPoly> lut29;
    std::vector<long (*)(long)> flut29;
    auto lut29idx0 = [](long I) -> long {
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
    lut29.push_back(ctx.genrate_lut(lut29idx0));
    flut29.push_back(lut29idx0);

    auto fvec29 = [flut29](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut29[i](I));
        return ret;
    };

    std::cerr << "\rLUT29   ";
    long gin29 = 1 * ct_x1 + 2 * ct_y3;
    std::vector<long> gout29 = fvec29(gin29);

    std::vector<RotationPoly> lut30;
    std::vector<long (*)(long)> flut30;
    auto lut30idx0 = [](long I) -> long {
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
    lut30.push_back(ctx.genrate_lut(lut30idx0));
    flut30.push_back(lut30idx0);

    auto fvec30 = [flut30](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut30[i](I));
        return ret;
    };

    std::cerr << "\rLUT30   ";
    long gin30 = 1 * gout29[0] + 2 * ct_x0 + 4 * ct_y4;
    std::vector<long> gout30 = fvec30(gin30);

    std::vector<RotationPoly> lut31;
    std::vector<long (*)(long)> flut31;
    auto lut31idx0 = [](long I) -> long {
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
    lut31.push_back(ctx.genrate_lut(lut31idx0));
    flut31.push_back(lut31idx0);

    auto fvec31 = [flut31](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut31[i](I));
        return ret;
    };

    std::cerr << "\rLUT31   ";
    long gin31 = 1 * ct_y0 + 2 * ct_x5;
    std::vector<long> gout31 = fvec31(gin31);

    std::vector<RotationPoly> lut32;
    std::vector<long (*)(long)> flut32;
    auto lut32idx0 = [](long I) -> long {
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
    lut32.push_back(ctx.genrate_lut(lut32idx0));
    flut32.push_back(lut32idx0);

    auto fvec32 = [flut32](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut32[i](I));
        return ret;
    };

    std::cerr << "\rLUT32   ";
    long gin32 = 1 * ct_x4 + 2 * ct_y2;
    std::vector<long> gout32 = fvec32(gin32);

    std::vector<RotationPoly> lut33;
    std::vector<long (*)(long)> flut33;
    auto lut33idx0 = [](long I) -> long {
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
    lut33.push_back(ctx.genrate_lut(lut33idx0));
    flut33.push_back(lut33idx0);

    auto fvec33 = [flut33](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut33[i](I));
        return ret;
    };

    std::cerr << "\rLUT33   ";
    long gin33 = 1 * ct_x10 + 2 * ct_y1;
    std::vector<long> gout33 = fvec33(gin33);

    std::vector<RotationPoly> lut34;
    std::vector<long (*)(long)> flut34;
    auto lut34idx0 = [](long I) -> long {
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
    lut34.push_back(ctx.genrate_lut(lut34idx0));
    flut34.push_back(lut34idx0);

    auto fvec34 = [flut34](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut34[i](I));
        return ret;
    };

    std::cerr << "\rLUT34   ";
    long gin34 = 1 * ct_x11 + 2 * ct_y2;
    std::vector<long> gout34 = fvec34(gin34);

    std::vector<RotationPoly> lut35;
    std::vector<long (*)(long)> flut35;
    auto lut35idx0 = [](long I) -> long {
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
    lut35.push_back(ctx.genrate_lut(lut35idx0));
    flut35.push_back(lut35idx0);

    auto fvec35 = [flut35](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut35[i](I));
        return ret;
    };

    std::cerr << "\rLUT35   ";
    long gin35 = 1 * ct_x9 + 2 * ct_y1;
    std::vector<long> gout35 = fvec35(gin35);

    std::vector<RotationPoly> lut36;
    std::vector<long (*)(long)> flut36;
    auto lut36idx0 = [](long I) -> long {
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
    lut36.push_back(ctx.genrate_lut(lut36idx0));
    flut36.push_back(lut36idx0);

    auto fvec36 = [flut36](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut36[i](I));
        return ret;
    };

    std::cerr << "\rLUT36   ";
    long gin36 = 1 * ct_y0 + 2 * ct_x7;
    std::vector<long> gout36 = fvec36(gin36);

    std::vector<RotationPoly> lut37;
    std::vector<long (*)(long)> flut37;
    auto lut37idx0 = [](long I) -> long {
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
    lut37.push_back(ctx.genrate_lut(lut37idx0));
    flut37.push_back(lut37idx0);

    auto fvec37 = [flut37](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut37[i](I));
        return ret;
    };

    std::cerr << "\rLUT37   ";
    long gin37 = 1 * ct_x1 + 2 * ct_y2;
    std::vector<long> gout37 = fvec37(gin37);

    std::vector<RotationPoly> lut38;
    std::vector<long (*)(long)> flut38;
    auto lut38idx0 = [](long I) -> long {
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
    lut38.push_back(ctx.genrate_lut(lut38idx0));
    flut38.push_back(lut38idx0);

    auto fvec38 = [flut38](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut38[i](I));
        return ret;
    };

    std::cerr << "\rLUT38   ";
    long gin38 = 1 * ct_y4 + 2 * ct_x7;
    std::vector<long> gout38 = fvec38(gin38);

    std::vector<RotationPoly> lut39;
    std::vector<long (*)(long)> flut39;
    auto lut39idx0 = [](long I) -> long {
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
    lut39.push_back(ctx.genrate_lut(lut39idx0));
    flut39.push_back(lut39idx0);

    auto fvec39 = [flut39](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut39[i](I));
        return ret;
    };

    std::cerr << "\rLUT39   ";
    long gin39 = 1 * ct_y6 + 2 * ct_x2;
    std::vector<long> gout39 = fvec39(gin39);

    std::vector<RotationPoly> lut40;
    std::vector<long (*)(long)> flut40;
    auto lut40idx0 = [](long I) -> long {
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
    lut40.push_back(ctx.genrate_lut(lut40idx0));
    flut40.push_back(lut40idx0);

    auto fvec40 = [flut40](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut40[i](I));
        return ret;
    };

    std::cerr << "\rLUT40   ";
    long gin40 = 1 * ct_y3 + 2 * ct_x5;
    std::vector<long> gout40 = fvec40(gin40);

    std::vector<RotationPoly> lut41;
    std::vector<long (*)(long)> flut41;
    auto lut41idx0 = [](long I) -> long {
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
    lut41.push_back(ctx.genrate_lut(lut41idx0));
    flut41.push_back(lut41idx0);

    auto fvec41 = [flut41](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut41[i](I));
        return ret;
    };

    std::cerr << "\rLUT41   ";
    long gin41 = 1 * ct_x4 + 2 * ct_y8;
    std::vector<long> gout41 = fvec41(gin41);

    std::vector<RotationPoly> lut42;
    std::vector<long (*)(long)> flut42;
    auto lut42idx0 = [](long I) -> long {
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
    lut42.push_back(ctx.genrate_lut(lut42idx0));
    flut42.push_back(lut42idx0);

    auto fvec42 = [flut42](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut42[i](I));
        return ret;
    };

    std::cerr << "\rLUT42   ";
    long gin42 = 1 * ct_x2 + 2 * ct_y7;
    std::vector<long> gout42 = fvec42(gin42);

    std::vector<RotationPoly> lut43;
    std::vector<long (*)(long)> flut43;
    auto lut43idx0 = [](long I) -> long {
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
    lut43.push_back(ctx.genrate_lut(lut43idx0));
    flut43.push_back(lut43idx0);

    auto fvec43 = [flut43](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut43[i](I));
        return ret;
    };

    std::cerr << "\rLUT43   ";
    long gin43 = 1 * ct_x1 + 2 * ct_y12;
    std::vector<long> gout43 = fvec43(gin43);

    std::vector<RotationPoly> lut44;
    std::vector<long (*)(long)> flut44;
    auto lut44idx0 = [](long I) -> long {
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
    lut44.push_back(ctx.genrate_lut(lut44idx0));
    flut44.push_back(lut44idx0);

    auto fvec44 = [flut44](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut44[i](I));
        return ret;
    };

    std::cerr << "\rLUT44   ";
    long gin44 = 1 * gout43[0] + 2 * ct_x0 + 4 * ct_y13;
    std::vector<long> gout44 = fvec44(gin44);

    std::vector<RotationPoly> lut45;
    std::vector<long (*)(long)> flut45;
    auto lut45idx0 = [](long I) -> long {
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
    lut45.push_back(ctx.genrate_lut(lut45idx0));
    flut45.push_back(lut45idx0);

    auto fvec45 = [flut45](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut45[i](I));
        return ret;
    };

    std::cerr << "\rLUT45   ";
    long gin45 = 1 * ct_y4 + 2 * ct_x6;
    std::vector<long> gout45 = fvec45(gin45);

    std::vector<RotationPoly> lut46;
    std::vector<long (*)(long)> flut46;
    auto lut46idx0 = [](long I) -> long {
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
    lut46.push_back(ctx.genrate_lut(lut46idx0));
    flut46.push_back(lut46idx0);

    auto fvec46 = [flut46](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut46[i](I));
        return ret;
    };

    std::cerr << "\rLUT46   ";
    long gin46 = 1 * ct_y7 + 2 * ct_x3;
    std::vector<long> gout46 = fvec46(gin46);

    std::vector<RotationPoly> lut47;
    std::vector<long (*)(long)> flut47;
    auto lut47idx0 = [](long I) -> long {
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
    lut47.push_back(ctx.genrate_lut(lut47idx0));
    flut47.push_back(lut47idx0);

    auto fvec47 = [flut47](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut47[i](I));
        return ret;
    };

    std::cerr << "\rLUT47   ";
    long gin47 = 1 * ct_y1 + 2 * ct_x5;
    std::vector<long> gout47 = fvec47(gin47);

    std::vector<RotationPoly> lut48;
    std::vector<long (*)(long)> flut48;
    auto lut48idx0 = [](long I) -> long {
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
    lut48.push_back(ctx.genrate_lut(lut48idx0));
    flut48.push_back(lut48idx0);

    auto fvec48 = [flut48](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut48[i](I));
        return ret;
    };

    std::cerr << "\rLUT48   ";
    long gin48 = 1 * ct_x12 + 2 * ct_y1;
    std::vector<long> gout48 = fvec48(gin48);

    std::vector<RotationPoly> lut49;
    std::vector<long (*)(long)> flut49;
    auto lut49idx0 = [](long I) -> long {
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
    lut49.push_back(ctx.genrate_lut(lut49idx0));
    flut49.push_back(lut49idx0);

    auto fvec49 = [flut49](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut49[i](I));
        return ret;
    };

    std::cerr << "\rLUT49   ";
    long gin49 = 1 * ct_x14 + 2 * ct_y1 + 4 * ct_y15;
    std::vector<long> gout49 = fvec49(gin49);

    std::vector<RotationPoly> lut50;
    std::vector<long (*)(long)> flut50;
    auto lut50idx0 = [](long I) -> long {
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
    lut50.push_back(ctx.genrate_lut(lut50idx0));
    flut50.push_back(lut50idx0);

    auto fvec50 = [flut50](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut50[i](I));
        return ret;
    };

    std::cerr << "\rLUT50   ";
    long gin50 = 1 * ct_y0 + 2 * ct_x15 + 4 * gout49[0];
    std::vector<long> gout50 = fvec50(gin50);

    std::vector<RotationPoly> lut51;
    std::vector<long (*)(long)> flut51;
    auto lut51idx0 = [](long I) -> long {
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
    lut51.push_back(ctx.genrate_lut(lut51idx0));
    flut51.push_back(lut51idx0);

    auto fvec51 = [flut51](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut51[i](I));
        return ret;
    };

    std::cerr << "\rLUT51   ";
    long gin51 = 1 * ct_x4 + 2 * ct_y9;
    std::vector<long> gout51 = fvec51(gin51);

    std::vector<RotationPoly> lut52;
    std::vector<long (*)(long)> flut52;
    auto lut52idx0 = [](long I) -> long {
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
    lut52.push_back(ctx.genrate_lut(lut52idx0));
    flut52.push_back(lut52idx0);

    auto fvec52 = [flut52](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut52[i](I));
        return ret;
    };

    std::cerr << "\rLUT52   ";
    long gin52 = 1 * ct_y8 + 2 * ct_x3;
    std::vector<long> gout52 = fvec52(gin52);

    std::vector<RotationPoly> lut53;
    std::vector<long (*)(long)> flut53;
    auto lut53idx0 = [](long I) -> long {
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
    lut53.push_back(ctx.genrate_lut(lut53idx0));
    flut53.push_back(lut53idx0);

    auto fvec53 = [flut53](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut53[i](I));
        return ret;
    };

    std::cerr << "\rLUT53   ";
    long gin53 = 1 * ct_x4 + 2 * ct_y5;
    std::vector<long> gout53 = fvec53(gin53);

    std::vector<RotationPoly> lut54;
    std::vector<long (*)(long)> flut54;
    auto lut54idx0 = [](long I) -> long {
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
    lut54.push_back(ctx.genrate_lut(lut54idx0));
    flut54.push_back(lut54idx0);

    auto fvec54 = [flut54](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut54[i](I));
        return ret;
    };

    std::cerr << "\rLUT54   ";
    long gin54 = 1 * ct_y7 + 2 * ct_x5;
    std::vector<long> gout54 = fvec54(gin54);

    std::vector<RotationPoly> lut55;
    std::vector<long (*)(long)> flut55;
    auto lut55idx0 = [](long I) -> long {
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
    lut55.push_back(ctx.genrate_lut(lut55idx0));
    flut55.push_back(lut55idx0);

    auto fvec55 = [flut55](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut55[i](I));
        return ret;
    };

    std::cerr << "\rLUT55   ";
    long gin55 = 1 * ct_x10 + 2 * ct_y3;
    std::vector<long> gout55 = fvec55(gin55);

    std::vector<RotationPoly> lut56;
    std::vector<long (*)(long)> flut56;
    auto lut56idx0 = [](long I) -> long {
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
    lut56.push_back(ctx.genrate_lut(lut56idx0));
    flut56.push_back(lut56idx0);

    auto fvec56 = [flut56](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut56[i](I));
        return ret;
    };

    std::cerr << "\rLUT56   ";
    long gin56 = 1 * ct_x1 + 2 * ct_y0;
    std::vector<long> gout56 = fvec56(gin56);

    std::vector<RotationPoly> lut57;
    std::vector<long (*)(long)> flut57;
    auto lut57idx0 = [](long I) -> long {
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
    lut57.push_back(ctx.genrate_lut(lut57idx0));
    flut57.push_back(lut57idx0);

    auto lut57idx1 = [](long I) -> long {
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
    lut57.push_back(ctx.genrate_lut(lut57idx1));
    flut57.push_back(lut57idx1);

    auto fvec57 = [flut57](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut57[i](I));
        return ret;
    };

    std::cerr << "\rLUT57   ";
    long gin57 = 1 * gout56[0] + 2 * ct_x0 + 4 * ct_y1;
    std::vector<long> gout57 = fvec57(gin57);

    std::vector<RotationPoly> lut58;
    std::vector<long (*)(long)> flut58;
    auto lut58idx0 = [](long I) -> long {
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
    lut58.push_back(ctx.genrate_lut(lut58idx0));
    flut58.push_back(lut58idx0);

    auto fvec58 = [flut58](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut58[i](I));
        return ret;
    };

    std::cerr << "\rLUT58   ";
    long gin58 = 1 * ct_y4 + 2 * ct_x9;
    std::vector<long> gout58 = fvec58(gin58);

    std::vector<RotationPoly> lut59;
    std::vector<long (*)(long)> flut59;
    auto lut59idx0 = [](long I) -> long {
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
    lut59.push_back(ctx.genrate_lut(lut59idx0));
    flut59.push_back(lut59idx0);

    auto fvec59 = [flut59](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut59[i](I));
        return ret;
    };

    std::cerr << "\rLUT59   ";
    long gin59 = 1 * ct_x8 + 2 * ct_y3;
    std::vector<long> gout59 = fvec59(gin59);

    std::vector<RotationPoly> lut60;
    std::vector<long (*)(long)> flut60;
    auto lut60idx0 = [](long I) -> long {
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
    lut60.push_back(ctx.genrate_lut(lut60idx0));
    flut60.push_back(lut60idx0);

    auto fvec60 = [flut60](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut60[i](I));
        return ret;
    };

    std::cerr << "\rLUT60   ";
    long gin60 = 1 * ct_x12 + 2 * ct_y3;
    std::vector<long> gout60 = fvec60(gin60);

    std::vector<RotationPoly> lut61;
    std::vector<long (*)(long)> flut61;
    auto lut61idx0 = [](long I) -> long {
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
    lut61.push_back(ctx.genrate_lut(lut61idx0));
    flut61.push_back(lut61idx0);

    auto fvec61 = [flut61](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut61[i](I));
        return ret;
    };

    std::cerr << "\rLUT61   ";
    long gin61 = 1 * ct_x13 + 2 * ct_y2 + 4 * gout60[0];
    std::vector<long> gout61 = fvec61(gin61);

    std::vector<RotationPoly> lut62;
    std::vector<long (*)(long)> flut62;
    auto lut62idx0 = [](long I) -> long {
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
    lut62.push_back(ctx.genrate_lut(lut62idx0));
    flut62.push_back(lut62idx0);

    auto fvec62 = [flut62](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut62[i](I));
        return ret;
    };

    std::cerr << "\rLUT62   ";
    long gin62 = 1 * ct_y2 + 2 * ct_x3;
    std::vector<long> gout62 = fvec62(gin62);

    std::vector<RotationPoly> lut63;
    std::vector<long (*)(long)> flut63;
    auto lut63idx0 = [](long I) -> long {
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
    lut63.push_back(ctx.genrate_lut(lut63idx0));
    flut63.push_back(lut63idx0);

    auto fvec63 = [flut63](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut63[i](I));
        return ret;
    };

    std::cerr << "\rLUT63   ";
    long gin63 = 1 * ct_x12 + 2 * ct_y2;
    std::vector<long> gout63 = fvec63(gin63);

    std::vector<RotationPoly> lut64;
    std::vector<long (*)(long)> flut64;
    auto lut64idx0 = [](long I) -> long {
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
    lut64.push_back(ctx.genrate_lut(lut64idx0));
    flut64.push_back(lut64idx0);

    auto fvec64 = [flut64](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut64[i](I));
        return ret;
    };

    std::cerr << "\rLUT64   ";
    long gin64 = 1 * ct_y3 + 2 * ct_x6;
    std::vector<long> gout64 = fvec64(gin64);

    std::vector<RotationPoly> lut65;
    std::vector<long (*)(long)> flut65;
    auto lut65idx0 = [](long I) -> long {
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
    lut65.push_back(ctx.genrate_lut(lut65idx0));
    flut65.push_back(lut65idx0);

    auto lut65idx1 = [](long I) -> long {
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
    lut65.push_back(ctx.genrate_lut(lut65idx1));
    flut65.push_back(lut65idx1);

    auto fvec65 = [flut65](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut65[i](I));
        return ret;
    };

    std::cerr << "\rLUT65   ";
    long gin65 = 1 * gout25[0] + 2 * gout53[0] + 4 * gout64[0];
    std::vector<long> gout65 = fvec65(gin65);

    std::vector<RotationPoly> lut66;
    std::vector<long (*)(long)> flut66;
    auto lut66idx0 = [](long I) -> long {
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
    lut66.push_back(ctx.genrate_lut(lut66idx0));
    flut66.push_back(lut66idx0);

    auto fvec66 = [flut66](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut66[i](I));
        return ret;
    };

    std::cerr << "\rLUT66   ";
    long gin66 = 1 * ct_x10 + 2 * ct_y2;
    std::vector<long> gout66 = fvec66(gin66);

    std::vector<RotationPoly> lut67;
    std::vector<long (*)(long)> flut67;
    auto lut67idx0 = [](long I) -> long {
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
    lut67.push_back(ctx.genrate_lut(lut67idx0));
    flut67.push_back(lut67idx0);

    auto fvec67 = [flut67](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut67[i](I));
        return ret;
    };

    std::cerr << "\rLUT67   ";
    long gin67 = 1 * ct_x8 + 2 * ct_y0;
    std::vector<long> gout67 = fvec67(gin67);

    std::vector<RotationPoly> lut68;
    std::vector<long (*)(long)> flut68;
    auto lut68idx0 = [](long I) -> long {
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
    lut68.push_back(ctx.genrate_lut(lut68idx0));
    flut68.push_back(lut68idx0);

    auto fvec68 = [flut68](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut68[i](I));
        return ret;
    };

    std::cerr << "\rLUT68   ";
    long gin68 = 1 * ct_x14 + 2 * ct_y0;
    std::vector<long> gout68 = fvec68(gin68);

    std::vector<RotationPoly> lut69;
    std::vector<long (*)(long)> flut69;
    auto lut69idx0 = [](long I) -> long {
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
    lut69.push_back(ctx.genrate_lut(lut69idx0));
    flut69.push_back(lut69idx0);

    auto fvec69 = [flut69](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut69[i](I));
        return ret;
    };

    std::cerr << "\rLUT69   ";
    long gin69 = 1 * ct_y5 + 2 * ct_x6;
    std::vector<long> gout69 = fvec69(gin69);

    std::vector<RotationPoly> lut70;
    std::vector<long (*)(long)> flut70;
    auto lut70idx0 = [](long I) -> long {
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
    lut70.push_back(ctx.genrate_lut(lut70idx0));
    flut70.push_back(lut70idx0);

    auto fvec70 = [flut70](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut70[i](I));
        return ret;
    };

    std::cerr << "\rLUT70   ";
    long gin70 = 1 * ct_y0 + 2 * ct_x6;
    std::vector<long> gout70 = fvec70(gin70);

    std::vector<RotationPoly> lut71;
    std::vector<long (*)(long)> flut71;
    auto lut71idx0 = [](long I) -> long {
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
    lut71.push_back(ctx.genrate_lut(lut71idx0));
    flut71.push_back(lut71idx0);

    auto fvec71 = [flut71](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut71[i](I));
        return ret;
    };

    std::cerr << "\rLUT71   ";
    long gin71 = 1 * ct_x1 + 2 * ct_y6;
    std::vector<long> gout71 = fvec71(gin71);

    std::vector<RotationPoly> lut72;
    std::vector<long (*)(long)> flut72;
    auto lut72idx0 = [](long I) -> long {
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
    lut72.push_back(ctx.genrate_lut(lut72idx0));
    flut72.push_back(lut72idx0);

    auto fvec72 = [flut72](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut72[i](I));
        return ret;
    };

    std::cerr << "\rLUT72   ";
    long gin72 = 1 * ct_y2 + 2 * ct_x5;
    std::vector<long> gout72 = fvec72(gin72);

    std::vector<RotationPoly> lut73;
    std::vector<long (*)(long)> flut73;
    auto lut73idx0 = [](long I) -> long {
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
    lut73.push_back(ctx.genrate_lut(lut73idx0));
    flut73.push_back(lut73idx0);

    auto fvec73 = [flut73](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut73[i](I));
        return ret;
    };

    std::cerr << "\rLUT73   ";
    long gin73 = 1 * ct_x2 + 2 * ct_y3;
    std::vector<long> gout73 = fvec73(gin73);

    std::vector<RotationPoly> lut74;
    std::vector<long (*)(long)> flut74;
    auto lut74idx0 = [](long I) -> long {
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
    lut74.push_back(ctx.genrate_lut(lut74idx0));
    flut74.push_back(lut74idx0);

    auto fvec74 = [flut74](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut74[i](I));
        return ret;
    };

    std::cerr << "\rLUT74   ";
    long gin74 = 1 * ct_y3 + 2 * ct_x3;
    std::vector<long> gout74 = fvec74(gin74);

    std::vector<RotationPoly> lut75;
    std::vector<long (*)(long)> flut75;
    auto lut75idx0 = [](long I) -> long {
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
    lut75.push_back(ctx.genrate_lut(lut75idx0));
    flut75.push_back(lut75idx0);

    auto lut75idx1 = [](long I) -> long {
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
    lut75.push_back(ctx.genrate_lut(lut75idx1));
    flut75.push_back(lut75idx1);

    auto fvec75 = [flut75](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut75[i](I));
        return ret;
    };

    std::cerr << "\rLUT75   ";
    long gin75 = 1 * gout47[0] + 2 * gout32[0] + 4 * gout70[0];
    std::vector<long> gout75 = fvec75(gin75);

    std::vector<RotationPoly> lut76;
    std::vector<long (*)(long)> flut76;
    auto lut76idx0 = [](long I) -> long {
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
    lut76.push_back(ctx.genrate_lut(lut76idx0));
    flut76.push_back(lut76idx0);

    auto fvec76 = [flut76](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut76[i](I));
        return ret;
    };

    std::cerr << "\rLUT76   ";
    long gin76 = 1 * ct_x11 + 2 * ct_y1;
    std::vector<long> gout76 = fvec76(gin76);

    std::vector<RotationPoly> lut77;
    std::vector<long (*)(long)> flut77;
    auto lut77idx0 = [](long I) -> long {
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
    lut77.push_back(ctx.genrate_lut(lut77idx0));
    flut77.push_back(lut77idx0);

    auto fvec77 = [flut77](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut77[i](I));
        return ret;
    };

    std::cerr << "\rLUT77   ";
    long gin77 = 1 * ct_x4 + 2 * ct_y1;
    std::vector<long> gout77 = fvec77(gin77);

    std::vector<RotationPoly> lut78;
    std::vector<long (*)(long)> flut78;
    auto lut78idx0 = [](long I) -> long {
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
    lut78.push_back(ctx.genrate_lut(lut78idx0));
    flut78.push_back(lut78idx0);

    auto fvec78 = [flut78](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut78[i](I));
        return ret;
    };

    std::cerr << "\rLUT78   ";
    long gin78 = 1 * ct_x13 + 2 * ct_y1;
    std::vector<long> gout78 = fvec78(gin78);

    std::vector<RotationPoly> lut79;
    std::vector<long (*)(long)> flut79;
    auto lut79idx0 = [](long I) -> long {
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
    lut79.push_back(ctx.genrate_lut(lut79idx0));
    flut79.push_back(lut79idx0);

    auto lut79idx1 = [](long I) -> long {
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
    lut79.push_back(ctx.genrate_lut(lut79idx1));
    flut79.push_back(lut79idx1);

    auto fvec79 = [flut79](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut79[i](I));
        return ret;
    };

    std::cerr << "\rLUT79   ";
    long gin79 = 1 * gout71[0] + 2 * ct_x0 + 4 * ct_y7;
    std::vector<long> gout79 = fvec79(gin79);

    std::vector<RotationPoly> lut80;
    std::vector<long (*)(long)> flut80;
    auto lut80idx0 = [](long I) -> long {
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
    lut80.push_back(ctx.genrate_lut(lut80idx0));
    flut80.push_back(lut80idx0);

    auto fvec80 = [flut80](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut80[i](I));
        return ret;
    };

    std::cerr << "\rLUT80   ";
    long gin80 = 1 * ct_x0 + 2 * ct_y3;
    std::vector<long> gout80 = fvec80(gin80);

    std::vector<RotationPoly> lut81;
    std::vector<long (*)(long)> flut81;
    auto lut81idx0 = [](long I) -> long {
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
    lut81.push_back(ctx.genrate_lut(lut81idx0));
    flut81.push_back(lut81idx0);

    auto fvec81 = [flut81](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut81[i](I));
        return ret;
    };

    std::cerr << "\rLUT81   ";
    long gin81 = 1 * ct_x2 + 2 * ct_y5;
    std::vector<long> gout81 = fvec81(gin81);

    std::vector<RotationPoly> lut82;
    std::vector<long (*)(long)> flut82;
    auto lut82idx0 = [](long I) -> long {
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
    lut82.push_back(ctx.genrate_lut(lut82idx0));
    flut82.push_back(lut82idx0);

    auto fvec82 = [flut82](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut82[i](I));
        return ret;
    };

    std::cerr << "\rLUT82   ";
    long gin82 = 1 * ct_x1 + 2 * ct_y5;
    std::vector<long> gout82 = fvec82(gin82);

    std::vector<RotationPoly> lut83;
    std::vector<long (*)(long)> flut83;
    auto lut83idx0 = [](long I) -> long {
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
    lut83.push_back(ctx.genrate_lut(lut83idx0));
    flut83.push_back(lut83idx0);

    auto lut83idx1 = [](long I) -> long {
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
    lut83.push_back(ctx.genrate_lut(lut83idx1));
    flut83.push_back(lut83idx1);

    auto fvec83 = [flut83](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut83[i](I));
        return ret;
    };

    std::cerr << "\rLUT83   ";
    long gin83 = 1 * gout27[0] + 2 * gout82[0] + 4 * gout74[0];
    std::vector<long> gout83 = fvec83(gin83);

    std::vector<RotationPoly> lut84;
    std::vector<long (*)(long)> flut84;
    auto lut84idx0 = [](long I) -> long {
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
    lut84.push_back(ctx.genrate_lut(lut84idx0));
    flut84.push_back(lut84idx0);

    auto fvec84 = [flut84](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut84[i](I));
        return ret;
    };

    std::cerr << "\rLUT84   ";
    long gin84 = 1 * ct_x1 + 2 * ct_y4;
    std::vector<long> gout84 = fvec84(gin84);

    std::vector<RotationPoly> lut85;
    std::vector<long (*)(long)> flut85;
    auto lut85idx0 = [](long I) -> long {
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
    lut85.push_back(ctx.genrate_lut(lut85idx0));
    flut85.push_back(lut85idx0);

    auto fvec85 = [flut85](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut85[i](I));
        return ret;
    };

    std::cerr << "\rLUT85   ";
    long gin85 = 1 * ct_op1 + 2 * ct_op2 + 4 * ct_op3;
    std::vector<long> gout85 = fvec85(gin85);

    std::vector<RotationPoly> lut86;
    std::vector<long (*)(long)> flut86;
    auto lut86idx0 = [](long I) -> long {
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
    lut86.push_back(ctx.genrate_lut(lut86idx0));
    flut86.push_back(lut86idx0);

    auto fvec86 = [flut86](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut86[i](I));
        return ret;
    };

    std::cerr << "\rLUT86   ";
    long gin86 = 1 * ct_y4 + 2 * ct_x3;
    std::vector<long> gout86 = fvec86(gin86);

    std::vector<RotationPoly> lut87;
    std::vector<long (*)(long)> flut87;
    auto lut87idx0 = [](long I) -> long {
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
    lut87.push_back(ctx.genrate_lut(lut87idx0));
    flut87.push_back(lut87idx0);

    auto fvec87 = [flut87](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut87[i](I));
        return ret;
    };

    std::cerr << "\rLUT87   ";
    long gin87 = 1 * ct_x0 + 2 * ct_y8;
    std::vector<long> gout87 = fvec87(gin87);

    std::vector<RotationPoly> lut88;
    std::vector<long (*)(long)> flut88;
    auto lut88idx0 = [](long I) -> long {
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
    lut88.push_back(ctx.genrate_lut(lut88idx0));
    flut88.push_back(lut88idx0);

    auto fvec88 = [flut88](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut88[i](I));
        return ret;
    };

    std::cerr << "\rLUT88   ";
    long gin88 = 1 * ct_y1 + 2 * ct_x6;
    std::vector<long> gout88 = fvec88(gin88);

    std::vector<RotationPoly> lut89;
    std::vector<long (*)(long)> flut89;
    auto lut89idx0 = [](long I) -> long {
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
    lut89.push_back(ctx.genrate_lut(lut89idx0));
    flut89.push_back(lut89idx0);

    auto fvec89 = [flut89](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut89[i](I));
        return ret;
    };

    std::cerr << "\rLUT89   ";
    long gin89 = 1 * ct_y4 + 2 * ct_x8;
    std::vector<long> gout89 = fvec89(gin89);

    std::vector<RotationPoly> lut90;
    std::vector<long (*)(long)> flut90;
    auto lut90idx0 = [](long I) -> long {
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
    lut90.push_back(ctx.genrate_lut(lut90idx0));
    flut90.push_back(lut90idx0);

    auto fvec90 = [flut90](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut90[i](I));
        return ret;
    };

    std::cerr << "\rLUT90   ";
    long gin90 = 1 * ct_y2 + 2 * ct_x6;
    std::vector<long> gout90 = fvec90(gin90);

    std::vector<RotationPoly> lut91;
    std::vector<long (*)(long)> flut91;
    auto lut91idx0 = [](long I) -> long {
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
    lut91.push_back(ctx.genrate_lut(lut91idx0));
    flut91.push_back(lut91idx0);

    auto fvec91 = [flut91](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut91[i](I));
        return ret;
    };

    std::cerr << "\rLUT91   ";
    long gin91 = 1 * ct_y6 + 2 * ct_x6;
    std::vector<long> gout91 = fvec91(gin91);

    std::vector<RotationPoly> lut92;
    std::vector<long (*)(long)> flut92;
    auto lut92idx0 = [](long I) -> long {
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
    lut92.push_back(ctx.genrate_lut(lut92idx0));
    flut92.push_back(lut92idx0);

    auto lut92idx1 = [](long I) -> long {
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
    lut92.push_back(ctx.genrate_lut(lut92idx1));
    flut92.push_back(lut92idx1);

    auto fvec92 = [flut92](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut92[i](I));
        return ret;
    };

    std::cerr << "\rLUT92   ";
    long gin92 = 1 * gout54[0] + 2 * gout41[0] + 4 * gout91[0];
    std::vector<long> gout92 = fvec92(gin92);

    std::vector<RotationPoly> lut93;
    std::vector<long (*)(long)> flut93;
    auto lut93idx0 = [](long I) -> long {
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
    lut93.push_back(ctx.genrate_lut(lut93idx0));
    flut93.push_back(lut93idx0);

    auto fvec93 = [flut93](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut93[i](I));
        return ret;
    };

    std::cerr << "\rLUT93   ";
    long gin93 = 1 * ct_y3 + 2 * ct_x9;
    std::vector<long> gout93 = fvec93(gin93);

    std::vector<RotationPoly> lut94;
    std::vector<long (*)(long)> flut94;
    auto lut94idx0 = [](long I) -> long {
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
    lut94.push_back(ctx.genrate_lut(lut94idx0));
    flut94.push_back(lut94idx0);

    auto fvec94 = [flut94](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut94[i](I));
        return ret;
    };

    std::cerr << "\rLUT94   ";
    long gin94 = 1 * ct_x1 + 2 * ct_y1;
    std::vector<long> gout94 = fvec94(gin94);

    std::vector<RotationPoly> lut95;
    std::vector<long (*)(long)> flut95;
    auto lut95idx0 = [](long I) -> long {
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
    lut95.push_back(ctx.genrate_lut(lut95idx0));
    flut95.push_back(lut95idx0);

    auto fvec95 = [flut95](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut95[i](I));
        return ret;
    };

    std::cerr << "\rLUT95   ";
    long gin95 = 1 * ct_x1 + 2 * ct_y9;
    std::vector<long> gout95 = fvec95(gin95);

    std::vector<RotationPoly> lut96;
    std::vector<long (*)(long)> flut96;
    auto lut96idx0 = [](long I) -> long {
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
    lut96.push_back(ctx.genrate_lut(lut96idx0));
    flut96.push_back(lut96idx0);

    auto lut96idx1 = [](long I) -> long {
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
    lut96.push_back(ctx.genrate_lut(lut96idx1));
    flut96.push_back(lut96idx1);

    auto fvec96 = [flut96](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut96[i](I));
        return ret;
    };

    std::cerr << "\rLUT96   ";
    long gin96 = 1 * gout95[0] + 2 * ct_x0 + 4 * ct_y10;
    std::vector<long> gout96 = fvec96(gin96);

    std::vector<RotationPoly> lut97;
    std::vector<long (*)(long)> flut97;
    auto lut97idx0 = [](long I) -> long {
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
    lut97.push_back(ctx.genrate_lut(lut97idx0));
    flut97.push_back(lut97idx0);

    auto fvec97 = [flut97](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut97[i](I));
        return ret;
    };

    std::cerr << "\rLUT97   ";
    long gin97 = 1 * ct_x4 + 2 * ct_y0;
    std::vector<long> gout97 = fvec97(gin97);

    std::vector<RotationPoly> lut98;
    std::vector<long (*)(long)> flut98;
    auto lut98idx0 = [](long I) -> long {
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
    lut98.push_back(ctx.genrate_lut(lut98idx0));
    flut98.push_back(lut98idx0);

    auto fvec98 = [flut98](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut98[i](I));
        return ret;
    };

    std::cerr << "\rLUT98   ";
    long gin98 = 1 * ct_x4 + 2 * gout17[0] + 4 * ct_y11;
    std::vector<long> gout98 = fvec98(gin98);

    std::vector<RotationPoly> lut99;
    std::vector<long (*)(long)> flut99;
    auto lut99idx0 = [](long I) -> long {
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
    lut99.push_back(ctx.genrate_lut(lut99idx0));
    flut99.push_back(lut99idx0);

    auto fvec99 = [flut99](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut99[i](I));
        return ret;
    };

    std::cerr << "\rLUT99   ";
    long gin99 = 1 * gout80[0] + 2 * gout84[0];
    std::vector<long> gout99 = fvec99(gin99);

    std::vector<RotationPoly> lut100;
    std::vector<long (*)(long)> flut100;
    auto lut100idx0 = [](long I) -> long {
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
    lut100.push_back(ctx.genrate_lut(lut100idx0));
    flut100.push_back(lut100idx0);

    auto lut100idx1 = [](long I) -> long {
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
    lut100.push_back(ctx.genrate_lut(lut100idx1));
    flut100.push_back(lut100idx1);

    auto fvec100 = [flut100](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut100[i](I));
        return ret;
    };

    std::cerr << "\rLUT100   ";
    long gin100 = 1 * gout78[0] + 2 * gout63[0] + 4 * gout68[0];
    std::vector<long> gout100 = fvec100(gin100);

    std::vector<RotationPoly> lut101;
    std::vector<long (*)(long)> flut101;
    auto lut101idx0 = [](long I) -> long {
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
    lut101.push_back(ctx.genrate_lut(lut101idx0));
    flut101.push_back(lut101idx0);

    auto fvec101 = [flut101](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut101[i](I));
        return ret;
    };

    std::cerr << "\rLUT101   ";
    long gin101 = 1 * gout61[0] + 2 * gout50[0];
    std::vector<long> gout101 = fvec101(gin101);

    std::vector<RotationPoly> lut102;
    std::vector<long (*)(long)> flut102;
    auto lut102idx0 = [](long I) -> long {
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
    lut102.push_back(ctx.genrate_lut(lut102idx0));
    flut102.push_back(lut102idx0);

    auto fvec102 = [flut102](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut102[i](I));
        return ret;
    };

    std::cerr << "\rLUT102   ";
    long gin102 = 1 * ct_x10 + 2 * ct_y0;
    std::vector<long> gout102 = fvec102(gin102);

    std::vector<RotationPoly> lut103;
    std::vector<long (*)(long)> flut103;
    auto lut103idx0 = [](long I) -> long {
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
    lut103.push_back(ctx.genrate_lut(lut103idx0));
    flut103.push_back(lut103idx0);

    auto lut103idx1 = [](long I) -> long {
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
    lut103.push_back(ctx.genrate_lut(lut103idx1));
    flut103.push_back(lut103idx1);

    auto fvec103 = [flut103](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut103[i](I));
        return ret;
    };

    std::cerr << "\rLUT103   ";
    long gin103 = 1 * gout35[0] + 2 * gout20[0] + 4 * gout102[0];
    std::vector<long> gout103 = fvec103(gin103);

    std::vector<RotationPoly> lut104;
    std::vector<long (*)(long)> flut104;
    auto lut104idx0 = [](long I) -> long {
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
    lut104.push_back(ctx.genrate_lut(lut104idx0));
    flut104.push_back(lut104idx0);

    auto fvec104 = [flut104](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut104[i](I));
        return ret;
    };

    std::cerr << "\rLUT104   ";
    long gin104 = 1 * ct_x0 + 2 * ct_y5;
    std::vector<long> gout104 = fvec104(gin104);

    std::vector<RotationPoly> lut105;
    std::vector<long (*)(long)> flut105;
    auto lut105idx0 = [](long I) -> long {
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
    lut105.push_back(ctx.genrate_lut(lut105idx0));
    flut105.push_back(lut105idx0);

    auto fvec105 = [flut105](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut105[i](I));
        return ret;
    };

    std::cerr << "\rLUT105   ";
    long gin105 = 1 * ct_y5 + 2 * ct_x7;
    std::vector<long> gout105 = fvec105(gin105);

    std::vector<RotationPoly> lut106;
    std::vector<long (*)(long)> flut106;
    auto lut106idx0 = [](long I) -> long {
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
    lut106.push_back(ctx.genrate_lut(lut106idx0));
    flut106.push_back(lut106idx0);

    auto lut106idx1 = [](long I) -> long {
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
    lut106.push_back(ctx.genrate_lut(lut106idx1));
    flut106.push_back(lut106idx1);

    auto fvec106 = [flut106](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut106[i](I));
        return ret;
    };

    std::cerr << "\rLUT106   ";
    long gin106 = 1 * gout89[0] + 2 * gout105[0] + 4 * gout93[0];
    std::vector<long> gout106 = fvec106(gin106);

    std::vector<RotationPoly> lut107;
    std::vector<long (*)(long)> flut107;
    auto lut107idx0 = [](long I) -> long {
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
    lut107.push_back(ctx.genrate_lut(lut107idx0));
    flut107.push_back(lut107idx0);

    auto fvec107 = [flut107](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut107[i](I));
        return ret;
    };

    std::cerr << "\rLUT107   ";
    long gin107 = 1 * ct_x1 + 2 * ct_y7;
    std::vector<long> gout107 = fvec107(gin107);

    std::vector<RotationPoly> lut108;
    std::vector<long (*)(long)> flut108;
    auto lut108idx0 = [](long I) -> long {
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
    lut108.push_back(ctx.genrate_lut(lut108idx0));
    flut108.push_back(lut108idx0);

    auto lut108idx1 = [](long I) -> long {
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
    lut108.push_back(ctx.genrate_lut(lut108idx1));
    flut108.push_back(lut108idx1);

    auto fvec108 = [flut108](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut108[i](I));
        return ret;
    };

    std::cerr << "\rLUT108   ";
    long gin108 = 1 * gout107[0] + 2 * gout87[0] + 4 * gout39[0];
    std::vector<long> gout108 = fvec108(gin108);

    std::vector<RotationPoly> lut109;
    std::vector<long (*)(long)> flut109;
    auto lut109idx0 = [](long I) -> long {
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
    lut109.push_back(ctx.genrate_lut(lut109idx0));
    flut109.push_back(lut109idx0);

    auto fvec109 = [flut109](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut109[i](I));
        return ret;
    };

    std::cerr << "\rLUT109   ";
    long gin109 = 1 * ct_x6 + 2 * ct_y8;
    std::vector<long> gout109 = fvec109(gin109);

    std::vector<RotationPoly> lut110;
    std::vector<long (*)(long)> flut110;
    auto lut110idx0 = [](long I) -> long {
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
    lut110.push_back(ctx.genrate_lut(lut110idx0));
    flut110.push_back(lut110idx0);

    auto fvec110 = [flut110](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut110[i](I));
        return ret;
    };

    std::cerr << "\rLUT110   ";
    long gin110 = 1 * ct_y8 + 2 * ct_x5;
    std::vector<long> gout110 = fvec110(gin110);

    std::vector<RotationPoly> lut111;
    std::vector<long (*)(long)> flut111;
    auto lut111idx0 = [](long I) -> long {
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
    lut111.push_back(ctx.genrate_lut(lut111idx0));
    flut111.push_back(lut111idx0);

    auto fvec111 = [flut111](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut111[i](I));
        return ret;
    };

    std::cerr << "\rLUT111   ";
    long gin111 = 1 * ct_y6 + 2 * ct_x4;
    std::vector<long> gout111 = fvec111(gin111);

    std::vector<RotationPoly> lut112;
    std::vector<long (*)(long)> flut112;
    auto lut112idx0 = [](long I) -> long {
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
    lut112.push_back(ctx.genrate_lut(lut112idx0));
    flut112.push_back(lut112idx0);

    auto fvec112 = [flut112](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut112[i](I));
        return ret;
    };

    std::cerr << "\rLUT112   ";
    long gin112 = 1 * ct_x2 + 2 * ct_y2;
    std::vector<long> gout112 = fvec112(gin112);

    std::vector<RotationPoly> lut113;
    std::vector<long (*)(long)> flut113;
    auto lut113idx0 = [](long I) -> long {
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
    lut113.push_back(ctx.genrate_lut(lut113idx0));
    flut113.push_back(lut113idx0);

    auto lut113idx1 = [](long I) -> long {
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
    lut113.push_back(ctx.genrate_lut(lut113idx1));
    flut113.push_back(lut113idx1);

    auto fvec113 = [flut113](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut113[i](I));
        return ret;
    };

    std::cerr << "\rLUT113   ";
    long gin113 = 1 * gout77[0] + 2 * gout62[0] + 4 * gout31[0];
    std::vector<long> gout113 = fvec113(gin113);

    std::vector<RotationPoly> lut114;
    std::vector<long (*)(long)> flut114;
    auto lut114idx0 = [](long I) -> long {
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
    lut114.push_back(ctx.genrate_lut(lut114idx0));
    flut114.push_back(lut114idx0);

    auto lut114idx1 = [](long I) -> long {
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
    lut114.push_back(ctx.genrate_lut(lut114idx1));
    flut114.push_back(lut114idx1);

    auto fvec114 = [flut114](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut114[i](I));
        return ret;
    };

    std::cerr << "\rLUT114   ";
    long gin114 = 1 * gout113[0] + 2 * gout75[0] + 4 * gout83[0];
    std::vector<long> gout114 = fvec114(gin114);

    std::vector<RotationPoly> lut115;
    std::vector<long (*)(long)> flut115;
    auto lut115idx0 = [](long I) -> long {
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
    lut115.push_back(ctx.genrate_lut(lut115idx0));
    flut115.push_back(lut115idx0);

    auto fvec115 = [flut115](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut115[i](I));
        return ret;
    };

    std::cerr << "\rLUT115   ";
    long gin115 = 1 * ct_x13 + 2 * ct_y0;
    std::vector<long> gout115 = fvec115(gin115);

    std::vector<RotationPoly> lut116;
    std::vector<long (*)(long)> flut116;
    auto lut116idx0 = [](long I) -> long {
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
    lut116.push_back(ctx.genrate_lut(lut116idx0));
    flut116.push_back(lut116idx0);

    auto lut116idx1 = [](long I) -> long {
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
    lut116.push_back(ctx.genrate_lut(lut116idx1));
    flut116.push_back(lut116idx1);

    auto fvec116 = [flut116](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut116[i](I));
        return ret;
    };

    std::cerr << "\rLUT116   ";
    long gin116 = 1 * gout48[0] + 2 * gout34[0] + 4 * gout115[0];
    std::vector<long> gout116 = fvec116(gin116);

    std::vector<RotationPoly> lut117;
    std::vector<long (*)(long)> flut117;
    auto lut117idx0 = [](long I) -> long {
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
    lut117.push_back(ctx.genrate_lut(lut117idx0));
    flut117.push_back(lut117idx0);

    auto lut117idx1 = [](long I) -> long {
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
    lut117.push_back(ctx.genrate_lut(lut117idx1));
    flut117.push_back(lut117idx1);

    auto fvec117 = [flut117](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut117[i](I));
        return ret;
    };

    std::cerr << "\rLUT117   ";
    long gin117 = 1 * gout76[0] + 2 * gout66[0] + 4 * gout28[0];
    std::vector<long> gout117 = fvec117(gin117);

    std::vector<RotationPoly> lut118;
    std::vector<long (*)(long)> flut118;
    auto lut118idx0 = [](long I) -> long {
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
    lut118.push_back(ctx.genrate_lut(lut118idx0));
    flut118.push_back(lut118idx0);

    auto fvec118 = [flut118](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut118[i](I));
        return ret;
    };

    std::cerr << "\rLUT118   ";
    long gin118 = 1 * ct_y6 + 2 * ct_x9;
    std::vector<long> gout118 = fvec118(gin118);

    std::vector<RotationPoly> lut119;
    std::vector<long (*)(long)> flut119;
    auto lut119idx0 = [](long I) -> long {
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
    lut119.push_back(ctx.genrate_lut(lut119idx0));
    flut119.push_back(lut119idx0);

    auto fvec119 = [flut119](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut119[i](I));
        return ret;
    };

    std::cerr << "\rLUT119   ";
    long gin119 = 1 * ct_y7 + 2 * ct_x6;
    std::vector<long> gout119 = fvec119(gin119);

    std::vector<RotationPoly> lut120;
    std::vector<long (*)(long)> flut120;
    auto lut120idx0 = [](long I) -> long {
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
    lut120.push_back(ctx.genrate_lut(lut120idx0));
    flut120.push_back(lut120idx0);

    auto lut120idx1 = [](long I) -> long {
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
    lut120.push_back(ctx.genrate_lut(lut120idx1));
    flut120.push_back(lut120idx1);

    auto fvec120 = [flut120](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut120[i](I));
        return ret;
    };

    std::cerr << "\rLUT120   ";
    long gin120 = 1 * gout38[0] + 2 * gout69[0] + 4 * gout59[0];
    std::vector<long> gout120 = fvec120(gin120);

    std::vector<RotationPoly> lut121;
    std::vector<long (*)(long)> flut121;
    auto lut121idx0 = [](long I) -> long {
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
    lut121.push_back(ctx.genrate_lut(lut121idx0));
    flut121.push_back(lut121idx0);

    auto lut121idx1 = [](long I) -> long {
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
    lut121.push_back(ctx.genrate_lut(lut121idx1));
    flut121.push_back(lut121idx1);

    auto fvec121 = [flut121](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut121[i](I));
        return ret;
    };

    std::cerr << "\rLUT121   ";
    long gin121 = 1 * gout83[1] + 2 * gout79[0];
    std::vector<long> gout121 = fvec121(gin121);

    std::vector<RotationPoly> lut122;
    std::vector<long (*)(long)> flut122;
    auto lut122idx0 = [](long I) -> long {
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
    lut122.push_back(ctx.genrate_lut(lut122idx0));
    flut122.push_back(lut122idx0);

    auto fvec122 = [flut122](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut122[i](I));
        return ret;
    };

    std::cerr << "\rLUT122   ";
    long gin122 = 1 * ct_y0 + 2 * ct_x3;
    std::vector<long> gout122 = fvec122(gin122);

    std::vector<RotationPoly> lut123;
    std::vector<long (*)(long)> flut123;
    auto lut123idx0 = [](long I) -> long {
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
    lut123.push_back(ctx.genrate_lut(lut123idx0));
    flut123.push_back(lut123idx0);

    auto fvec123 = [flut123](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut123[i](I));
        return ret;
    };

    std::cerr << "\rLUT123   ";
    long gin123 = 1 * ct_x2 + 2 * ct_y1;
    std::vector<long> gout123 = fvec123(gin123);

    std::vector<RotationPoly> lut124;
    std::vector<long (*)(long)> flut124;
    auto lut124idx0 = [](long I) -> long {
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
    lut124.push_back(ctx.genrate_lut(lut124idx0));
    flut124.push_back(lut124idx0);

    auto lut124idx1 = [](long I) -> long {
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
    lut124.push_back(ctx.genrate_lut(lut124idx1));
    flut124.push_back(lut124idx1);

    auto fvec124 = [flut124](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut124[i](I));
        return ret;
    };

    std::cerr << "\rLUT124   ";
    long gin124 = 1 * gout123[0] + 2 * gout37[0] + 4 * gout122[0];
    std::vector<long> gout124 = fvec124(gin124);

    std::vector<RotationPoly> lut125;
    std::vector<long (*)(long)> flut125;
    auto lut125idx0 = [](long I) -> long {
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
    lut125.push_back(ctx.genrate_lut(lut125idx0));
    flut125.push_back(lut125idx0);

    auto fvec125 = [flut125](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut125[i](I));
        return ret;
    };

    std::cerr << "\rLUT125   ";
    long gin125 = 1 * ct_x4 + 2 * ct_y7;
    std::vector<long> gout125 = fvec125(gin125);

    std::vector<RotationPoly> lut126;
    std::vector<long (*)(long)> flut126;
    auto lut126idx0 = [](long I) -> long {
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
    lut126.push_back(ctx.genrate_lut(lut126idx0));
    flut126.push_back(lut126idx0);

    auto lut126idx1 = [](long I) -> long {
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
    lut126.push_back(ctx.genrate_lut(lut126idx1));
    flut126.push_back(lut126idx1);

    auto fvec126 = [flut126](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut126[i](I));
        return ret;
    };

    std::cerr << "\rLUT126   ";
    long gin126 = 1 * gout125[0] + 2 * gout52[0] + 4 * gout26[0];
    std::vector<long> gout126 = fvec126(gin126);

    std::vector<RotationPoly> lut127;
    std::vector<long (*)(long)> flut127;
    auto lut127idx0 = [](long I) -> long {
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
    lut127.push_back(ctx.genrate_lut(lut127idx0));
    flut127.push_back(lut127idx0);

    auto lut127idx1 = [](long I) -> long {
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
    lut127.push_back(ctx.genrate_lut(lut127idx1));
    flut127.push_back(lut127idx1);

    auto fvec127 = [flut127](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut127[i](I));
        return ret;
    };

    std::cerr << "\rLUT127   ";
    long gin127 = 1 * gout84[0] + 2 * gout104[0] + 4 * gout73[0];
    std::vector<long> gout127 = fvec127(gin127);

    std::vector<RotationPoly> lut128;
    std::vector<long (*)(long)> flut128;
    auto lut128idx0 = [](long I) -> long {
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
    lut128.push_back(ctx.genrate_lut(lut128idx0));
    flut128.push_back(lut128idx0);

    auto lut128idx1 = [](long I) -> long {
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
    lut128.push_back(ctx.genrate_lut(lut128idx1));
    flut128.push_back(lut128idx1);

    auto fvec128 = [flut128](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut128[i](I));
        return ret;
    };

    std::cerr << "\rLUT128   ";
    long gin128 = 1 * gout127[0] + 2 * ct_x0 + 4 * ct_y6;
    std::vector<long> gout128 = fvec128(gin128);

    std::vector<RotationPoly> lut129;
    std::vector<long (*)(long)> flut129;
    auto lut129idx0 = [](long I) -> long {
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
    lut129.push_back(ctx.genrate_lut(lut129idx0));
    flut129.push_back(lut129idx0);

    auto fvec129 = [flut129](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut129[i](I));
        return ret;
    };

    std::cerr << "\rLUT129   ";
    long gin129 = 1 * ct_y9 + 2 * ct_x3;
    std::vector<long> gout129 = fvec129(gin129);

    std::vector<RotationPoly> lut130;
    std::vector<long (*)(long)> flut130;
    auto lut130idx0 = [](long I) -> long {
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
    lut130.push_back(ctx.genrate_lut(lut130idx0));
    flut130.push_back(lut130idx0);

    auto lut130idx1 = [](long I) -> long {
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
    lut130.push_back(ctx.genrate_lut(lut130idx1));
    flut130.push_back(lut130idx1);

    auto fvec130 = [flut130](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut130[i](I));
        return ret;
    };

    std::cerr << "\rLUT130   ";
    long gin130 = 1 * gout126[1] + 2 * gout92[1] + 4 * gout120[0];
    std::vector<long> gout130 = fvec130(gin130);

    std::vector<RotationPoly> lut131;
    std::vector<long (*)(long)> flut131;
    auto lut131idx0 = [](long I) -> long {
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
    lut131.push_back(ctx.genrate_lut(lut131idx0));
    flut131.push_back(lut131idx0);

    auto fvec131 = [flut131](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut131[i](I));
        return ret;
    };

    std::cerr << "\rLUT131   ";
    long gin131 = 1 * ct_x0 + 2 * ct_y12;
    std::vector<long> gout131 = fvec131(gin131);

    std::vector<RotationPoly> lut132;
    std::vector<long (*)(long)> flut132;
    auto lut132idx0 = [](long I) -> long {
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
    lut132.push_back(ctx.genrate_lut(lut132idx0));
    flut132.push_back(lut132idx0);

    auto fvec132 = [flut132](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut132[i](I));
        return ret;
    };

    std::cerr << "\rLUT132   ";
    long gin132 = 1 * ct_x11 + 2 * ct_y4 + 4 * gout100[0];
    std::vector<long> gout132 = fvec132(gin132);

    std::vector<RotationPoly> lut133;
    std::vector<long (*)(long)> flut133;
    auto lut133idx0 = [](long I) -> long {
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
    lut133.push_back(ctx.genrate_lut(lut133idx0));
    flut133.push_back(lut133idx0);

    auto lut133idx1 = [](long I) -> long {
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
    lut133.push_back(ctx.genrate_lut(lut133idx1));
    flut133.push_back(lut133idx1);

    auto fvec133 = [flut133](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut133[i](I));
        return ret;
    };

    std::cerr << "\rLUT133   ";
    long gin133 = 1 * gout46[0] + 2 * gout19[0] + 4 * gout111[0];
    std::vector<long> gout133 = fvec133(gin133);

    std::vector<RotationPoly> lut134;
    std::vector<long (*)(long)> flut134;
    auto lut134idx0 = [](long I) -> long {
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
    lut134.push_back(ctx.genrate_lut(lut134idx0));
    flut134.push_back(lut134idx0);

    auto fvec134 = [flut134](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut134[i](I));
        return ret;
    };

    std::cerr << "\rLUT134   ";
    long gin134 = 1 * ct_y1 + 2 * ct_x3;
    std::vector<long> gout134 = fvec134(gin134);

    std::vector<RotationPoly> lut135;
    std::vector<long (*)(long)> flut135;
    auto lut135idx0 = [](long I) -> long {
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
    lut135.push_back(ctx.genrate_lut(lut135idx0));
    flut135.push_back(lut135idx0);

    auto lut135idx1 = [](long I) -> long {
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
    lut135.push_back(ctx.genrate_lut(lut135idx1));
    flut135.push_back(lut135idx1);

    auto fvec135 = [flut135](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut135[i](I));
        return ret;
    };

    std::cerr << "\rLUT135   ";
    long gin135 = 1 * gout134[0] + 2 * gout112[0] + 4 * gout97[0];
    std::vector<long> gout135 = fvec135(gin135);

    std::vector<RotationPoly> lut136;
    std::vector<long (*)(long)> flut136;
    auto lut136idx0 = [](long I) -> long {
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
    lut136.push_back(ctx.genrate_lut(lut136idx0));
    flut136.push_back(lut136idx0);

    auto lut136idx1 = [](long I) -> long {
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
    lut136.push_back(ctx.genrate_lut(lut136idx1));
    flut136.push_back(lut136idx1);

    auto fvec136 = [flut136](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut136[i](I));
        return ret;
    };

    std::cerr << "\rLUT136   ";
    long gin136 = 1 * gout124[0] + 2 * gout135[1] + 4 * gout30[0];
    std::vector<long> gout136 = fvec136(gin136);

    std::vector<RotationPoly> lut137;
    std::vector<long (*)(long)> flut137;
    auto lut137idx0 = [](long I) -> long {
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
    lut137.push_back(ctx.genrate_lut(lut137idx0));
    flut137.push_back(lut137idx0);

    auto fvec137 = [flut137](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut137[i](I));
        return ret;
    };

    std::cerr << "\rLUT137   ";
    long gin137 = 1 * ct_y10 + 2 * ct_x3;
    std::vector<long> gout137 = fvec137(gin137);

    std::cerr << "\rFA138    ";
    long gin138 = 1 + 1 * ct_x0 + 2 * ct_x1 + 1 * gout9[0] + 2 * gout3[0];
    std::vector<long> gout138 = vdecomp(gin138);

    std::vector<RotationPoly> lut139;
    std::vector<long (*)(long)> flut139;
    auto lut139idx0 = [](long I) -> long {
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
    lut139.push_back(ctx.genrate_lut(lut139idx0));
    flut139.push_back(lut139idx0);

    auto lut139idx1 = [](long I) -> long {
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
    lut139.push_back(ctx.genrate_lut(lut139idx1));
    flut139.push_back(lut139idx1);

    auto fvec139 = [flut139](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut139[i](I));
        return ret;
    };

    std::cerr << "\rLUT139   ";
    long gin139 = 1 * gout88[0] + 2 * gout72[0] + 4 * gout36[0];
    std::vector<long> gout139 = fvec139(gin139);

    std::vector<RotationPoly> lut140;
    std::vector<long (*)(long)> flut140;
    auto lut140idx0 = [](long I) -> long {
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
    lut140.push_back(ctx.genrate_lut(lut140idx0));
    flut140.push_back(lut140idx0);

    auto fvec140 = [flut140](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut140[i](I));
        return ret;
    };

    std::cerr << "\rLUT140   ";
    long gin140 = 1 * ct_x1 + 2 * ct_y11;
    std::vector<long> gout140 = fvec140(gin140);

    std::vector<RotationPoly> lut141;
    std::vector<long (*)(long)> flut141;
    auto lut141idx0 = [](long I) -> long {
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
    lut141.push_back(ctx.genrate_lut(lut141idx0));
    flut141.push_back(lut141idx0);

    auto fvec141 = [flut141](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut141[i](I));
        return ret;
    };

    std::cerr << "\rLUT141   ";
    long gin141 = 1 * ct_x0 + 2 * ct_y11;
    std::vector<long> gout141 = fvec141(gin141);

    std::vector<RotationPoly> lut142;
    std::vector<long (*)(long)> flut142;
    auto lut142idx0 = [](long I) -> long {
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
    lut142.push_back(ctx.genrate_lut(lut142idx0));
    flut142.push_back(lut142idx0);

    auto fvec142 = [flut142](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut142[i](I));
        return ret;
    };

    std::cerr << "\rLUT142   ";
    long gin142 = 1 * ct_x2 + 2 * ct_y13 + 4 * gout98[0];
    std::vector<long> gout142 = fvec142(gin142);

    std::vector<RotationPoly> lut143;
    std::vector<long (*)(long)> flut143;
    auto lut143idx0 = [](long I) -> long {
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
    lut143.push_back(ctx.genrate_lut(lut143idx0));
    flut143.push_back(lut143idx0);

    auto fvec143 = [flut143](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut143[i](I));
        return ret;
    };

    std::cerr << "\rLUT143   ";
    long gin143 = 1 * ct_x2 + 2 * ct_y11;
    std::vector<long> gout143 = fvec143(gin143);

    std::vector<RotationPoly> lut144;
    std::vector<long (*)(long)> flut144;
    auto lut144idx0 = [](long I) -> long {
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
    lut144.push_back(ctx.genrate_lut(lut144idx0));
    flut144.push_back(lut144idx0);

    auto lut144idx1 = [](long I) -> long {
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
    lut144.push_back(ctx.genrate_lut(lut144idx1));
    flut144.push_back(lut144idx1);

    auto fvec144 = [flut144](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut144[i](I));
        return ret;
    };

    std::cerr << "\rLUT144   ";
    long gin144 = 1 * gout137[0] + 2 * gout143[0] + 4 * gout51[0];
    std::vector<long> gout144 = fvec144(gin144);

    std::vector<RotationPoly> lut145;
    std::vector<long (*)(long)> flut145;
    auto lut145idx0 = [](long I) -> long {
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
    lut145.push_back(ctx.genrate_lut(lut145idx0));
    flut145.push_back(lut145idx0);

    auto fvec145 = [flut145](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut145[i](I));
        return ret;
    };

    std::cerr << "\rLUT145   ";
    long gin145 = 1 * ct_y6 + 2 * ct_x8;
    std::vector<long> gout145 = fvec145(gin145);

    std::vector<RotationPoly> lut146;
    std::vector<long (*)(long)> flut146;
    auto lut146idx0 = [](long I) -> long {
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
    lut146.push_back(ctx.genrate_lut(lut146idx0));
    flut146.push_back(lut146idx0);

    auto lut146idx1 = [](long I) -> long {
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
    lut146.push_back(ctx.genrate_lut(lut146idx1));
    flut146.push_back(lut146idx1);

    auto fvec146 = [flut146](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut146[i](I));
        return ret;
    };

    std::cerr << "\rLUT146   ";
    long gin146 = 1 * gout24[0] + 2 * gout109[0] + 4 * gout145[0];
    std::vector<long> gout146 = fvec146(gin146);

    std::vector<RotationPoly> lut147;
    std::vector<long (*)(long)> flut147;
    auto lut147idx0 = [](long I) -> long {
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
    lut147.push_back(ctx.genrate_lut(lut147idx0));
    flut147.push_back(lut147idx0);

    auto fvec147 = [flut147](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut147[i](I));
        return ret;
    };

    std::cerr << "\rLUT147   ";
    long gin147 = 1 * ct_y6 + 2 * ct_x7;
    std::vector<long> gout147 = fvec147(gin147);

    std::vector<RotationPoly> lut148;
    std::vector<long (*)(long)> flut148;
    auto lut148idx0 = [](long I) -> long {
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
    lut148.push_back(ctx.genrate_lut(lut148idx0));
    flut148.push_back(lut148idx0);

    auto lut148idx1 = [](long I) -> long {
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
    lut148.push_back(ctx.genrate_lut(lut148idx1));
    flut148.push_back(lut148idx1);

    auto fvec148 = [flut148](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut148[i](I));
        return ret;
    };

    std::cerr << "\rLUT148   ";
    long gin148 = 1 * gout119[0] + 2 * gout110[0] + 4 * gout147[0];
    std::vector<long> gout148 = fvec148(gin148);

    std::vector<RotationPoly> lut149;
    std::vector<long (*)(long)> flut149;
    auto lut149idx0 = [](long I) -> long {
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
    lut149.push_back(ctx.genrate_lut(lut149idx0));
    flut149.push_back(lut149idx0);

    auto lut149idx1 = [](long I) -> long {
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
    lut149.push_back(ctx.genrate_lut(lut149idx1));
    flut149.push_back(lut149idx1);

    auto fvec149 = [flut149](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut149[i](I));
        return ret;
    };

    std::cerr << "\rLUT149   ";
    long gin149 = 1 * gout92[0] + 2 * gout148[1] + 4 * gout106[0];
    std::vector<long> gout149 = fvec149(gin149);

    std::vector<RotationPoly> lut150;
    std::vector<long (*)(long)> flut150;
    auto lut150idx0 = [](long I) -> long {
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
    lut150.push_back(ctx.genrate_lut(lut150idx0));
    flut150.push_back(lut150idx0);

    auto fvec150 = [flut150](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut150[i](I));
        return ret;
    };

    std::cerr << "\rLUT150   ";
    long gin150 = 1 * ct_x2 + 2 * ct_y0;
    std::vector<long> gout150 = fvec150(gin150);

    std::vector<RotationPoly> lut151;
    std::vector<long (*)(long)> flut151;
    auto lut151idx0 = [](long I) -> long {
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
    lut151.push_back(ctx.genrate_lut(lut151idx0));
    flut151.push_back(lut151idx0);

    auto fvec151 = [flut151](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut151[i](I));
        return ret;
    };

    std::cerr << "\rLUT151   ";
    long gin151 = 1 * ct_x8 + 2 * ct_y5;
    std::vector<long> gout151 = fvec151(gin151);

    std::vector<RotationPoly> lut152;
    std::vector<long (*)(long)> flut152;
    auto lut152idx0 = [](long I) -> long {
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
    lut152.push_back(ctx.genrate_lut(lut152idx0));
    flut152.push_back(lut152idx0);

    auto lut152idx1 = [](long I) -> long {
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
    lut152.push_back(ctx.genrate_lut(lut152idx1));
    flut152.push_back(lut152idx1);

    auto fvec152 = [flut152](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut152[i](I));
        return ret;
    };

    std::cerr << "\rLUT152   ";
    long gin152 = 1 * gout58[0] + 2 * gout151[0] + 4 * gout55[0];
    std::vector<long> gout152 = fvec152(gin152);

    std::vector<RotationPoly> lut153;
    std::vector<long (*)(long)> flut153;
    auto lut153idx0 = [](long I) -> long {
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
    lut153.push_back(ctx.genrate_lut(lut153idx0));
    flut153.push_back(lut153idx0);

    auto lut153idx1 = [](long I) -> long {
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
    lut153.push_back(ctx.genrate_lut(lut153idx1));
    flut153.push_back(lut153idx1);

    auto fvec153 = [flut153](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut153[i](I));
        return ret;
    };

    std::cerr << "\rLUT153   ";
    long gin153 = 1 * gout117[0] + 2 * gout116[1] + 4 * gout152[0];
    std::vector<long> gout153 = fvec153(gin153);

    std::vector<RotationPoly> lut154;
    std::vector<long (*)(long)> flut154;
    auto lut154idx0 = [](long I) -> long {
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
    lut154.push_back(ctx.genrate_lut(lut154idx0));
    flut154.push_back(lut154idx0);

    auto fvec154 = [flut154](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut154[i](I));
        return ret;
    };

    std::cerr << "\rLUT154   ";
    long gin154 = 1 * ct_op6 + 2 * ct_op7;
    std::vector<long> gout154 = fvec154(gin154);

    std::vector<RotationPoly> lut155;
    std::vector<long (*)(long)> flut155;
    auto lut155idx0 = [](long I) -> long {
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
    lut155.push_back(ctx.genrate_lut(lut155idx0));
    flut155.push_back(lut155idx0);

    auto fvec155 = [flut155](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut155[i](I));
        return ret;
    };

    std::cerr << "\rLUT155   ";
    long gin155 = 1 * ct_op4 + 2 * ct_op5 + 4 * gout154[0];
    std::vector<long> gout155 = fvec155(gin155);

    std::vector<RotationPoly> lut156;
    std::vector<long (*)(long)> flut156;
    auto lut156idx0 = [](long I) -> long {
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
    lut156.push_back(ctx.genrate_lut(lut156idx0));
    flut156.push_back(lut156idx0);

    auto fvec156 = [flut156](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut156[i](I));
        return ret;
    };

    std::cerr << "\rLUT156   ";
    long gin156 = 1 * gout85[0] + 2 * gout155[0];
    std::vector<long> gout156 = fvec156(gin156);

    std::vector<RotationPoly> lut157;
    std::vector<long (*)(long)> flut157;
    auto lut157idx0 = [](long I) -> long {
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
    lut157.push_back(ctx.genrate_lut(lut157idx0));
    flut157.push_back(lut157idx0);

    auto fvec157 = [flut157](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut157[i](I));
        return ret;
    };

    std::cerr << "\rLUT157   ";
    long gin157 = 1 * ct_op0 + 2 * gout156[0];
    std::vector<long> gout157 = fvec157(gin157);

    std::vector<RotationPoly> lut158;
    std::vector<long (*)(long)> flut158;
    auto lut158idx0 = [](long I) -> long {
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
    lut158.push_back(ctx.genrate_lut(lut158idx0));
    flut158.push_back(lut158idx0);

    auto fvec158 = [flut158](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut158[i](I));
        return ret;
    };

    std::cerr << "\rLUT158   ";
    long gin158 = 1 * ct_x0 + 2 * ct_y0 + 4 * gout157[0];
    std::vector<long> gout158 = fvec158(gin158);

    std::vector<RotationPoly> lut159;
    std::vector<long (*)(long)> flut159;
    auto lut159idx0 = [](long I) -> long {
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
    lut159.push_back(ctx.genrate_lut(lut159idx0));
    flut159.push_back(lut159idx0);

    auto fvec159 = [flut159](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut159[i](I));
        return ret;
    };

    std::cerr << "\rLUT159   ";
    long gin159 = 1 * ct_x10 + 2 * gout118[0] + 4 * ct_y5;
    std::vector<long> gout159 = fvec159(gin159);

    std::vector<RotationPoly> lut160;
    std::vector<long (*)(long)> flut160;
    auto lut160idx0 = [](long I) -> long {
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
    lut160.push_back(ctx.genrate_lut(lut160idx0));
    flut160.push_back(lut160idx0);

    auto fvec160 = [flut160](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut160[i](I));
        return ret;
    };

    std::cerr << "\rLUT160   ";
    long gin160 = 1 * ct_x8 + 2 * ct_y7 + 4 * gout159[0];
    std::vector<long> gout160 = fvec160(gin160);

    std::vector<RotationPoly> lut161;
    std::vector<long (*)(long)> flut161;
    auto lut161idx0 = [](long I) -> long {
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
    lut161.push_back(ctx.genrate_lut(lut161idx0));
    flut161.push_back(lut161idx0);

    auto fvec161 = [flut161](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut161[i](I));
        return ret;
    };

    std::cerr << "\rLUT161   ";
    long gin161 = 1 * ct_x9 + 2 * ct_y0;
    std::vector<long> gout161 = fvec161(gin161);

    std::vector<RotationPoly> lut162;
    std::vector<long (*)(long)> flut162;
    auto lut162idx0 = [](long I) -> long {
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
    lut162.push_back(ctx.genrate_lut(lut162idx0));
    flut162.push_back(lut162idx0);

    auto fvec162 = [flut162](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut162[i](I));
        return ret;
    };

    std::cerr << "\rLUT162   ";
    long gin162 = 1 * ct_x5 + 2 * ct_y10;
    std::vector<long> gout162 = fvec162(gin162);

    std::vector<RotationPoly> lut163;
    std::vector<long (*)(long)> flut163;
    auto lut163idx0 = [](long I) -> long {
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
    lut163.push_back(ctx.genrate_lut(lut163idx0));
    flut163.push_back(lut163idx0);

    auto fvec163 = [flut163](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut163[i](I));
        return ret;
    };

    std::cerr << "\rLUT163   ";
    long gin163 = 1 * ct_x2 + 2 * ct_y10;
    std::vector<long> gout163 = fvec163(gin163);

    std::vector<RotationPoly> lut164;
    std::vector<long (*)(long)> flut164;
    auto lut164idx0 = [](long I) -> long {
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
    lut164.push_back(ctx.genrate_lut(lut164idx0));
    flut164.push_back(lut164idx0);

    auto lut164idx1 = [](long I) -> long {
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
    lut164.push_back(ctx.genrate_lut(lut164idx1));
    flut164.push_back(lut164idx1);

    auto fvec164 = [flut164](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut164[i](I));
        return ret;
    };

    std::cerr << "\rLUT164   ";
    long gin164 = 1 * gout163[0] + 2 * gout140[0] + 4 * gout129[0];
    std::vector<long> gout164 = fvec164(gin164);

    std::vector<RotationPoly> lut165;
    std::vector<long (*)(long)> flut165;
    auto lut165idx0 = [](long I) -> long {
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
    lut165.push_back(ctx.genrate_lut(lut165idx0));
    flut165.push_back(lut165idx0);

    auto lut165idx1 = [](long I) -> long {
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
    lut165.push_back(ctx.genrate_lut(lut165idx1));
    flut165.push_back(lut165idx1);

    auto fvec165 = [flut165](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut165[i](I));
        return ret;
    };

    std::cerr << "\rLUT165   ";
    long gin165 = 1 * gout164[0] + 2 * gout144[0] + 4 * gout44[0];
    std::vector<long> gout165 = fvec165(gin165);

    std::vector<RotationPoly> lut166;
    std::vector<long (*)(long)> flut166;
    auto lut166idx0 = [](long I) -> long {
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
    lut166.push_back(ctx.genrate_lut(lut166idx0));
    flut166.push_back(lut166idx0);

    auto fvec166 = [flut166](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut166[i](I));
        return ret;
    };

    std::cerr << "\rLUT166   ";
    long gin166 = 1 * ct_y3 + 2 * ct_x7;
    std::vector<long> gout166 = fvec166(gin166);

    std::vector<RotationPoly> lut167;
    std::vector<long (*)(long)> flut167;
    auto lut167idx0 = [](long I) -> long {
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
    lut167.push_back(ctx.genrate_lut(lut167idx0));
    flut167.push_back(lut167idx0);

    auto fvec167 = [flut167](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut167[i](I));
        return ret;
    };

    std::cerr << "\rLUT167   ";
    long gin167 = 1 * ct_x4 + 2 * ct_y10;
    std::vector<long> gout167 = fvec167(gin167);

    std::vector<RotationPoly> lut168;
    std::vector<long (*)(long)> flut168;
    auto lut168idx0 = [](long I) -> long {
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
    lut168.push_back(ctx.genrate_lut(lut168idx0));
    flut168.push_back(lut168idx0);

    auto fvec168 = [flut168](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut168[i](I));
        return ret;
    };

    std::cerr << "\rLUT168   ";
    long gin168 = 1 * gout167[0] + 2 * ct_y9 + 4 * ct_x5;
    std::vector<long> gout168 = fvec168(gin168);

    std::vector<RotationPoly> lut169;
    std::vector<long (*)(long)> flut169;
    auto lut169idx0 = [](long I) -> long {
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
    lut169.push_back(ctx.genrate_lut(lut169idx0));
    flut169.push_back(lut169idx0);

    auto lut169idx1 = [](long I) -> long {
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
    lut169.push_back(ctx.genrate_lut(lut169idx1));
    flut169.push_back(lut169idx1);

    auto fvec169 = [flut169](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut169[i](I));
        return ret;
    };

    std::cerr << "\rLUT169   ";
    long gin169 = 1 * gout168[0] + 2 * ct_x3 + 4 * ct_y11;
    std::vector<long> gout169 = fvec169(gin169);

    std::vector<RotationPoly> lut170;
    std::vector<long (*)(long)> flut170;
    auto lut170idx0 = [](long I) -> long {
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
    lut170.push_back(ctx.genrate_lut(lut170idx0));
    flut170.push_back(lut170idx0);

    auto fvec170 = [flut170](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut170[i](I));
        return ret;
    };

    std::cerr << "\rLUT170   ";
    long gin170 = 1 * gout51[0] + 2 * gout169[1] + 4 * gout162[0];
    std::vector<long> gout170 = fvec170(gin170);

    std::vector<RotationPoly> lut171;
    std::vector<long (*)(long)> flut171;
    auto lut171idx0 = [](long I) -> long {
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
    lut171.push_back(ctx.genrate_lut(lut171idx0));
    flut171.push_back(lut171idx0);

    auto fvec171 = [flut171](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut171[i](I));
        return ret;
    };

    std::cerr << "\rLUT171   ";
    long gin171 = 1 * ct_x4 + 2 * ct_y4;
    std::vector<long> gout171 = fvec171(gin171);

    std::vector<RotationPoly> lut172;
    std::vector<long (*)(long)> flut172;
    auto lut172idx0 = [](long I) -> long {
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
    lut172.push_back(ctx.genrate_lut(lut172idx0));
    flut172.push_back(lut172idx0);

    auto lut172idx1 = [](long I) -> long {
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
    lut172.push_back(ctx.genrate_lut(lut172idx1));
    flut172.push_back(lut172idx1);

    auto fvec172 = [flut172](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut172[i](I));
        return ret;
    };

    std::cerr << "\rLUT172   ";
    long gin172 = 1 * gout148[0] + 2 * gout146[1] + 4 * gout152[1];
    std::vector<long> gout172 = fvec172(gin172);

    std::vector<RotationPoly> lut173;
    std::vector<long (*)(long)> flut173;
    auto lut173idx0 = [](long I) -> long {
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
    lut173.push_back(ctx.genrate_lut(lut173idx0));
    flut173.push_back(lut173idx0);

    auto lut173idx1 = [](long I) -> long {
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
    lut173.push_back(ctx.genrate_lut(lut173idx1));
    flut173.push_back(lut173idx1);

    auto fvec173 = [flut173](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut173[i](I));
        return ret;
    };

    std::cerr << "\rLUT173   ";
    long gin173 = 1 * gout135[0] + 2 * gout113[1] + 4 * gout127[1];
    std::vector<long> gout173 = fvec173(gin173);

    std::vector<RotationPoly> lut174;
    std::vector<long (*)(long)> flut174;
    auto lut174idx0 = [](long I) -> long {
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
    lut174.push_back(ctx.genrate_lut(lut174idx0));
    flut174.push_back(lut174idx0);

    auto lut174idx1 = [](long I) -> long {
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
    lut174.push_back(ctx.genrate_lut(lut174idx1));
    flut174.push_back(lut174idx1);

    auto fvec174 = [flut174](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut174[i](I));
        return ret;
    };

    std::cerr << "\rLUT174   ";
    long gin174 = 1 * gout173[0] + 2 * gout114[0] + 4 * gout128[1];
    std::vector<long> gout174 = fvec174(gin174);

    std::vector<RotationPoly> lut175;
    std::vector<long (*)(long)> flut175;
    auto lut175idx0 = [](long I) -> long {
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
    lut175.push_back(ctx.genrate_lut(lut175idx0));
    flut175.push_back(lut175idx0);

    auto lut175idx1 = [](long I) -> long {
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
    lut175.push_back(ctx.genrate_lut(lut175idx1));
    flut175.push_back(lut175idx1);

    auto fvec175 = [flut175](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut175[i](I));
        return ret;
    };

    std::cerr << "\rLUT175   ";
    long gin175 = 1 * gout136[1] + 2 * gout173[1] + 4 * gout99[0];
    std::vector<long> gout175 = fvec175(gin175);

    std::vector<RotationPoly> lut176;
    std::vector<long (*)(long)> flut176;
    auto lut176idx0 = [](long I) -> long {
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
    lut176.push_back(ctx.genrate_lut(lut176idx0));
    flut176.push_back(lut176idx0);

    auto lut176idx1 = [](long I) -> long {
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
    lut176.push_back(ctx.genrate_lut(lut176idx1));
    flut176.push_back(lut176idx1);

    auto fvec176 = [flut176](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut176[i](I));
        return ret;
    };

    std::cerr << "\rLUT176   ";
    long gin176 = 1 * gout175[0] + 2 * gout174[1];
    std::vector<long> gout176 = fvec176(gin176);

    std::vector<RotationPoly> lut177;
    std::vector<long (*)(long)> flut177;
    auto lut177idx0 = [](long I) -> long {
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
    lut177.push_back(ctx.genrate_lut(lut177idx0));
    flut177.push_back(lut177idx0);

    auto fvec177 = [flut177](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut177[i](I));
        return ret;
    };

    std::cerr << "\rLUT177   ";
    long gin177 = 1 * ct_x11 + 2 * ct_y0;
    std::vector<long> gout177 = fvec177(gin177);

    std::vector<RotationPoly> lut178;
    std::vector<long (*)(long)> flut178;
    auto lut178idx0 = [](long I) -> long {
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
    lut178.push_back(ctx.genrate_lut(lut178idx0));
    flut178.push_back(lut178idx0);

    auto lut178idx1 = [](long I) -> long {
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
    lut178.push_back(ctx.genrate_lut(lut178idx1));
    flut178.push_back(lut178idx1);

    auto fvec178 = [flut178](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut178[i](I));
        return ret;
    };

    std::cerr << "\rLUT178   ";
    long gin178 = 1 * gout33[0] + 2 * gout18[0] + 4 * gout177[0];
    std::vector<long> gout178 = fvec178(gin178);

    std::vector<RotationPoly> lut179;
    std::vector<long (*)(long)> flut179;
    auto lut179idx0 = [](long I) -> long {
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
    lut179.push_back(ctx.genrate_lut(lut179idx0));
    flut179.push_back(lut179idx0);

    auto lut179idx1 = [](long I) -> long {
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
    lut179.push_back(ctx.genrate_lut(lut179idx1));
    flut179.push_back(lut179idx1);

    auto fvec179 = [flut179](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut179[i](I));
        return ret;
    };

    std::cerr << "\rLUT179   ";
    long gin179 = 1 * gout178[0] + 2 * gout117[1] + 4 * gout106[1];
    std::vector<long> gout179 = fvec179(gin179);

    std::vector<RotationPoly> lut180;
    std::vector<long (*)(long)> flut180;
    auto lut180idx0 = [](long I) -> long {
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
    lut180.push_back(ctx.genrate_lut(lut180idx0));
    flut180.push_back(lut180idx0);

    auto lut180idx1 = [](long I) -> long {
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
    lut180.push_back(ctx.genrate_lut(lut180idx1));
    flut180.push_back(lut180idx1);

    auto fvec180 = [flut180](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut180[i](I));
        return ret;
    };

    std::cerr << "\rLUT180   ";
    long gin180 = 1 * gout179[0] + 2 * gout153[0] + 4 * gout149[1];
    std::vector<long> gout180 = fvec180(gin180);

    std::vector<RotationPoly> lut181;
    std::vector<long (*)(long)> flut181;
    auto lut181idx0 = [](long I) -> long {
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
    lut181.push_back(ctx.genrate_lut(lut181idx0));
    flut181.push_back(lut181idx0);

    auto fvec181 = [flut181](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut181[i](I));
        return ret;
    };

    std::cerr << "\rLUT181   ";
    long gin181 = 1 * ct_y2 + 2 * ct_x7;
    std::vector<long> gout181 = fvec181(gin181);

    std::vector<RotationPoly> lut182;
    std::vector<long (*)(long)> flut182;
    auto lut182idx0 = [](long I) -> long {
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
    lut182.push_back(ctx.genrate_lut(lut182idx0));
    flut182.push_back(lut182idx0);

    auto lut182idx1 = [](long I) -> long {
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
    lut182.push_back(ctx.genrate_lut(lut182idx1));
    flut182.push_back(lut182idx1);

    auto fvec182 = [flut182](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut182[i](I));
        return ret;
    };

    std::cerr << "\rLUT182   ";
    long gin182 = 1 * gout21[0] + 2 * gout181[0] + 4 * gout161[0];
    std::vector<long> gout182 = fvec182(gin182);

    std::vector<RotationPoly> lut183;
    std::vector<long (*)(long)> flut183;
    auto lut183idx0 = [](long I) -> long {
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
    lut183.push_back(ctx.genrate_lut(lut183idx0));
    flut183.push_back(lut183idx0);

    auto fvec183 = [flut183](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut183[i](I));
        return ret;
    };

    std::cerr << "\rLUT183   ";
    long gin183 = 1 * ct_x7 + 2 * ct_y8 + 4 * gout22[0];
    std::vector<long> gout183 = fvec183(gin183);

    std::vector<RotationPoly> lut184;
    std::vector<long (*)(long)> flut184;
    auto lut184idx0 = [](long I) -> long {
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
    lut184.push_back(ctx.genrate_lut(lut184idx0));
    flut184.push_back(lut184idx0);

    auto fvec184 = [flut184](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut184[i](I));
        return ret;
    };

    std::cerr << "\rLUT184   ";
    long gin184 = 1 * ct_x10 + 2 * ct_y4;
    std::vector<long> gout184 = fvec184(gin184);

    std::vector<RotationPoly> lut185;
    std::vector<long (*)(long)> flut185;
    auto lut185idx0 = [](long I) -> long {
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
    lut185.push_back(ctx.genrate_lut(lut185idx0));
    flut185.push_back(lut185idx0);

    auto lut185idx1 = [](long I) -> long {
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
    lut185.push_back(ctx.genrate_lut(lut185idx1));
    flut185.push_back(lut185idx1);

    auto fvec185 = [flut185](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut185[i](I));
        return ret;
    };

    std::cerr << "\rLUT185   ";
    long gin185 = 1 * gout184[0] + 2 * ct_x11 + 4 * ct_y3;
    std::vector<long> gout185 = fvec185(gin185);

    std::vector<RotationPoly> lut186;
    std::vector<long (*)(long)> flut186;
    auto lut186idx0 = [](long I) -> long {
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
    lut186.push_back(ctx.genrate_lut(lut186idx0));
    flut186.push_back(lut186idx0);

    auto lut186idx1 = [](long I) -> long {
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
    lut186.push_back(ctx.genrate_lut(lut186idx1));
    flut186.push_back(lut186idx1);

    auto fvec186 = [flut186](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut186[i](I));
        return ret;
    };

    std::cerr << "\rLUT186   ";
    long gin186 = 1 * gout185[1] + 2 * ct_x9 + 4 * ct_y5;
    std::vector<long> gout186 = fvec186(gin186);

    std::vector<RotationPoly> lut187;
    std::vector<long (*)(long)> flut187;
    auto lut187idx0 = [](long I) -> long {
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
    lut187.push_back(ctx.genrate_lut(lut187idx0));
    flut187.push_back(lut187idx0);

    auto lut187idx1 = [](long I) -> long {
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
    lut187.push_back(ctx.genrate_lut(lut187idx1));
    flut187.push_back(lut187idx1);

    auto fvec187 = [flut187](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut187[i](I));
        return ret;
    };

    std::cerr << "\rLUT187   ";
    long gin187 = 1 * gout186[1] + 2 * gout100[1] + 4 * gout116[0];
    std::vector<long> gout187 = fvec187(gin187);

    std::vector<RotationPoly> lut188;
    std::vector<long (*)(long)> flut188;
    auto lut188idx0 = [](long I) -> long {
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
    lut188.push_back(ctx.genrate_lut(lut188idx0));
    flut188.push_back(lut188idx0);

    auto fvec188 = [flut188](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut188[i](I));
        return ret;
    };

    std::cerr << "\rLUT188   ";
    long gin188 = 1 * gout170[0] + 2 * gout142[0] + 4 * gout183[0];
    std::vector<long> gout188 = fvec188(gin188);

    std::vector<RotationPoly> lut189;
    std::vector<long (*)(long)> flut189;
    auto lut189idx0 = [](long I) -> long {
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
    lut189.push_back(ctx.genrate_lut(lut189idx0));
    flut189.push_back(lut189idx0);

    auto fvec189 = [flut189](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut189[i](I));
        return ret;
    };

    std::cerr << "\rLUT189   ";
    long gin189 = 1 * ct_x4 + 2 * ct_y3;
    std::vector<long> gout189 = fvec189(gin189);

    std::vector<RotationPoly> lut190;
    std::vector<long (*)(long)> flut190;
    auto lut190idx0 = [](long I) -> long {
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
    lut190.push_back(ctx.genrate_lut(lut190idx0));
    flut190.push_back(lut190idx0);

    auto lut190idx1 = [](long I) -> long {
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
    lut190.push_back(ctx.genrate_lut(lut190idx1));
    flut190.push_back(lut190idx1);

    auto fvec190 = [flut190](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut190[i](I));
        return ret;
    };

    std::cerr << "\rLUT190   ";
    long gin190 = 1 * gout86[0] + 2 * gout81[0] + 4 * gout189[0];
    std::vector<long> gout190 = fvec190(gin190);

    std::vector<RotationPoly> lut191;
    std::vector<long (*)(long)> flut191;
    auto lut191idx0 = [](long I) -> long {
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
    lut191.push_back(ctx.genrate_lut(lut191idx0));
    flut191.push_back(lut191idx0);

    auto lut191idx1 = [](long I) -> long {
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
    lut191.push_back(ctx.genrate_lut(lut191idx1));
    flut191.push_back(lut191idx1);

    auto fvec191 = [flut191](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut191[i](I));
        return ret;
    };

    std::cerr << "\rLUT191   ";
    long gin191 = 1 * gout79[1] + 2 * gout108[1] + 4 * gout190[0];
    std::vector<long> gout191 = fvec191(gin191);

    std::vector<RotationPoly> lut192;
    std::vector<long (*)(long)> flut192;
    auto lut192idx0 = [](long I) -> long {
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
    lut192.push_back(ctx.genrate_lut(lut192idx0));
    flut192.push_back(lut192idx0);

    auto lut192idx1 = [](long I) -> long {
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
    lut192.push_back(ctx.genrate_lut(lut192idx1));
    flut192.push_back(lut192idx1);

    auto fvec192 = [flut192](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut192[i](I));
        return ret;
    };

    std::cerr << "\rLUT192   ";
    long gin192 = 1 * gout191[0] + 2 * ct_x0 + 4 * ct_y9;
    std::vector<long> gout192 = fvec192(gin192);

    std::vector<RotationPoly> lut193;
    std::vector<long (*)(long)> flut193;
    auto lut193idx0 = [](long I) -> long {
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
    lut193.push_back(ctx.genrate_lut(lut193idx0));
    flut193.push_back(lut193idx0);

    auto fvec193 = [flut193](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut193[i](I));
        return ret;
    };

    std::cerr << "\rLUT193   ";
    long gin193 = 1 * ct_op1 + 2 * ct_op0 + 4 * gout155[0];
    std::vector<long> gout193 = fvec193(gin193);

    std::vector<RotationPoly> lut194;
    std::vector<long (*)(long)> flut194;
    auto lut194idx0 = [](long I) -> long {
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
    lut194.push_back(ctx.genrate_lut(lut194idx0));
    flut194.push_back(lut194idx0);

    auto fvec194 = [flut194](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut194[i](I));
        return ret;
    };

    std::cerr << "\rLUT194   ";
    long gin194 = 1 * gout193[0] + 2 * ct_op2 + 4 * ct_op3;
    std::vector<long> gout194 = fvec194(gin194);

    std::vector<RotationPoly> lut195;
    std::vector<long (*)(long)> flut195;
    auto lut195idx0 = [](long I) -> long {
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
    lut195.push_back(ctx.genrate_lut(lut195idx0));
    flut195.push_back(lut195idx0);

    auto fvec195 = [flut195](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut195[i](I));
        return ret;
    };

    std::cerr << "\rLUT195   ";
    long gin195 = 1 * gout156[0] + 2 * gout194[0];
    std::vector<long> gout195 = fvec195(gin195);

    std::vector<RotationPoly> lut196;
    std::vector<long (*)(long)> flut196;
    auto lut196idx0 = [](long I) -> long {
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
    lut196.push_back(ctx.genrate_lut(lut196idx0));
    flut196.push_back(lut196idx0);

    auto fvec196 = [flut196](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut196[i](I));
        return ret;
    };

    std::cerr << "\rLUT196   ";
    long gin196 = 1 * gout16[0] + 2 * gout138[0] + 4 * gout194[0];
    std::vector<long> gout196 = fvec196(gin196);

    std::vector<RotationPoly> lut197;
    std::vector<long (*)(long)> flut197;
    auto lut197idx0 = [](long I) -> long {
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
    lut197.push_back(ctx.genrate_lut(lut197idx0));
    flut197.push_back(lut197idx0);

    auto fvec197 = [flut197](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut197[i](I));
        return ret;
    };

    std::cerr << "\rLUT197   ";
    long gin197 = 1 * gout196[0] + 2 * gout157[0];
    std::vector<long> gout197 = fvec197(gin197);

    std::vector<RotationPoly> lut198;
    std::vector<long (*)(long)> flut198;
    auto lut198idx0 = [](long I) -> long {
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
    lut198.push_back(ctx.genrate_lut(lut198idx0));
    flut198.push_back(lut198idx0);

    auto fvec198 = [flut198](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut198[i](I));
        return ret;
    };

    std::cerr << "\rLUT198   ";
    long gin198 = 1 * gout197[0] + 2 * gout158[0] + 4 * gout195[0];
    std::vector<long> gout198 = fvec198(gin198);

    std::vector<RotationPoly> lut199;
    std::vector<long (*)(long)> flut199;
    auto lut199idx0 = [](long I) -> long {
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
    lut199.push_back(ctx.genrate_lut(lut199idx0));
    flut199.push_back(lut199idx0);

    auto fvec199 = [flut199](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut199[i](I));
        return ret;
    };

    std::cerr << "\rLUT199   ";
    long gin199 = 1 * ct_x0 + 2 * ct_y2;
    std::vector<long> gout199 = fvec199(gin199);

    std::vector<RotationPoly> lut200;
    std::vector<long (*)(long)> flut200;
    auto lut200idx0 = [](long I) -> long {
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
    lut200.push_back(ctx.genrate_lut(lut200idx0));
    flut200.push_back(lut200idx0);

    auto lut200idx1 = [](long I) -> long {
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
    lut200.push_back(ctx.genrate_lut(lut200idx1));
    flut200.push_back(lut200idx1);

    auto fvec200 = [flut200](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut200[i](I));
        return ret;
    };

    std::cerr << "\rLUT200   ";
    long gin200 = 1 * gout94[0] + 2 * gout199[0] + 4 * gout150[0];
    std::vector<long> gout200 = fvec200(gin200);

    std::vector<RotationPoly> lut201;
    std::vector<long (*)(long)> flut201;
    auto lut201idx0 = [](long I) -> long {
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
    lut201.push_back(ctx.genrate_lut(lut201idx0));
    flut201.push_back(lut201idx0);

    auto lut201idx1 = [](long I) -> long {
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
    lut201.push_back(ctx.genrate_lut(lut201idx1));
    flut201.push_back(lut201idx1);

    auto fvec201 = [flut201](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut201[i](I));
        return ret;
    };

    std::cerr << "\rLUT201   ";
    long gin201 = 1 * gout200[0] + 2 * gout124[1] + 4 * gout80[0];
    std::vector<long> gout201 = fvec201(gin201);

    std::vector<RotationPoly> lut202;
    std::vector<long (*)(long)> flut202;
    auto lut202idx0 = [](long I) -> long {
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
    lut202.push_back(ctx.genrate_lut(lut202idx0));
    flut202.push_back(lut202idx0);

    auto lut202idx1 = [](long I) -> long {
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
    lut202.push_back(ctx.genrate_lut(lut202idx1));
    flut202.push_back(lut202idx1);

    auto fvec202 = [flut202](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut202[i](I));
        return ret;
    };

    std::cerr << "\rLUT202   ";
    long gin202 = 1 * gout201[0] + 2 * gout136[0];
    std::vector<long> gout202 = fvec202(gin202);

    std::vector<RotationPoly> lut203;
    std::vector<long (*)(long)> flut203;
    auto lut203idx0 = [](long I) -> long {
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
    lut203.push_back(ctx.genrate_lut(lut203idx0));
    flut203.push_back(lut203idx0);

    auto lut203idx1 = [](long I) -> long {
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
    lut203.push_back(ctx.genrate_lut(lut203idx1));
    flut203.push_back(lut203idx1);

    auto fvec203 = [flut203](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut203[i](I));
        return ret;
    };

    std::cerr << "\rLUT203   ";
    long gin203 = 1 * gout202[0] + 2 * gout175[1];
    std::vector<long> gout203 = fvec203(gin203);

    std::vector<RotationPoly> lut204;
    std::vector<long (*)(long)> flut204;
    auto lut204idx0 = [](long I) -> long {
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
    lut204.push_back(ctx.genrate_lut(lut204idx0));
    flut204.push_back(lut204idx0);

    auto lut204idx1 = [](long I) -> long {
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
    lut204.push_back(ctx.genrate_lut(lut204idx1));
    flut204.push_back(lut204idx1);

    auto fvec204 = [flut204](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut204[i](I));
        return ret;
    };

    std::cerr << "\rLUT204   ";
    long gin204 = 1 * gout203[0] + 2 * gout176[1];
    std::vector<long> gout204 = fvec204(gin204);

    std::vector<RotationPoly> lut205;
    std::vector<long (*)(long)> flut205;
    auto lut205idx0 = [](long I) -> long {
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
    lut205.push_back(ctx.genrate_lut(lut205idx0));
    flut205.push_back(lut205idx0);

    auto lut205idx1 = [](long I) -> long {
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
    lut205.push_back(ctx.genrate_lut(lut205idx1));
    flut205.push_back(lut205idx1);

    auto fvec205 = [flut205](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut205[i](I));
        return ret;
    };

    std::cerr << "\rLUT205   ";
    long gin205 = 1 * gout187[0] + 2 * gout172[1] + 4 * gout153[1];
    std::vector<long> gout205 = fvec205(gin205);

    std::vector<RotationPoly> lut206;
    std::vector<long (*)(long)> flut206;
    auto lut206idx0 = [](long I) -> long {
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
    lut206.push_back(ctx.genrate_lut(lut206idx0));
    flut206.push_back(lut206idx0);

    auto fvec206 = [flut206](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut206[i](I));
        return ret;
    };

    std::cerr << "\rLUT206   ";
    long gin206 = 1 * ct_y5 + 2 * ct_x5;
    std::vector<long> gout206 = fvec206(gin206);

    std::vector<RotationPoly> lut207;
    std::vector<long (*)(long)> flut207;
    auto lut207idx0 = [](long I) -> long {
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
    lut207.push_back(ctx.genrate_lut(lut207idx0));
    flut207.push_back(lut207idx0);

    auto lut207idx1 = [](long I) -> long {
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
    lut207.push_back(ctx.genrate_lut(lut207idx1));
    flut207.push_back(lut207idx1);

    auto fvec207 = [flut207](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut207[i](I));
        return ret;
    };

    std::cerr << "\rLUT207   ";
    long gin207 = 1 * gout45[0] + 2 * gout206[0] + 4 * gout166[0];
    std::vector<long> gout207 = fvec207(gin207);

    std::vector<RotationPoly> lut208;
    std::vector<long (*)(long)> flut208;
    auto lut208idx0 = [](long I) -> long {
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
    lut208.push_back(ctx.genrate_lut(lut208idx0));
    flut208.push_back(lut208idx0);

    auto lut208idx1 = [](long I) -> long {
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
    lut208.push_back(ctx.genrate_lut(lut208idx1));
    flut208.push_back(lut208idx1);

    auto fvec208 = [flut208](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut208[i](I));
        return ret;
    };

    std::cerr << "\rLUT208   ";
    long gin208 = 1 * gout133[1] + 2 * gout126[0] + 4 * gout207[0];
    std::vector<long> gout208 = fvec208(gin208);

    std::vector<RotationPoly> lut209;
    std::vector<long (*)(long)> flut209;
    auto lut209idx0 = [](long I) -> long {
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
    lut209.push_back(ctx.genrate_lut(lut209idx0));
    flut209.push_back(lut209idx0);

    auto lut209idx1 = [](long I) -> long {
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
    lut209.push_back(ctx.genrate_lut(lut209idx1));
    flut209.push_back(lut209idx1);

    auto fvec209 = [flut209](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut209[i](I));
        return ret;
    };

    std::cerr << "\rLUT209   ";
    long gin209 = 1 * gout182[0] + 2 * gout103[0] + 4 * gout207[1];
    std::vector<long> gout209 = fvec209(gin209);

    std::cerr << "\rFA210    ";
    long gin210 = gout138[2] + 1 * ct_x2 + 2 * ct_x3 + 1 * gout5[0] + 2 * gout7[0];
    std::vector<long> gout210 = vdecomp(gin210);

    std::cerr << "\rFA211    ";
    long gin211 = gout210[2] + 1 * ct_x4 + 2 * ct_x5 + 1 * gout6[0] + 2 * gout4[0];
    std::vector<long> gout211 = vdecomp(gin211);

    std::cerr << "\rFA212    ";
    long gin212 = gout211[2] + 1 * ct_x6 + 2 * ct_x7 + 1 * gout15[0] + 2 * gout13[0];
    std::vector<long> gout212 = vdecomp(gin212);

    std::cerr << "\rFA213    ";
    long gin213 = gout212[2] + 1 * ct_x8 + 2 * ct_x9 + 1 * gout12[0] + 2 * gout11[0];
    std::vector<long> gout213 = vdecomp(gin213);

    std::cerr << "\rFA214    ";
    long gin214 = gout213[2] + 1 * ct_x10 + 2 * ct_x11 + 1 * gout8[0] + 2 * gout2[0];
    std::vector<long> gout214 = vdecomp(gin214);

    std::cerr << "\rFA215    ";
    long gin215 = gout214[2] + 1 * ct_x12 + 2 * ct_x13 + 1 * gout1[0] + 2 * gout0[0];
    std::vector<long> gout215 = vdecomp(gin215);

    std::cerr << "\rFA216    ";
    long gin216 = gout215[2] + 1 * ct_x14 + 2 * ct_x15 + 1 * gout10[0] + 2 * gout14[0];
    std::vector<long> gout216 = vdecomp(gin216);

    std::vector<RotationPoly> lut217;
    std::vector<long (*)(long)> flut217;
    auto lut217idx0 = [](long I) -> long {
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
    lut217.push_back(ctx.genrate_lut(lut217idx0));
    flut217.push_back(lut217idx0);

    auto fvec217 = [flut217](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut217[i](I));
        return ret;
    };

    std::cerr << "\rLUT217   ";
    long gin217 = 1 * ct_x1 + 2 * ct_y10;
    std::vector<long> gout217 = fvec217(gin217);

    std::vector<RotationPoly> lut218;
    std::vector<long (*)(long)> flut218;
    auto lut218idx0 = [](long I) -> long {
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
    lut218.push_back(ctx.genrate_lut(lut218idx0));
    flut218.push_back(lut218idx0);

    auto lut218idx1 = [](long I) -> long {
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
    lut218.push_back(ctx.genrate_lut(lut218idx1));
    flut218.push_back(lut218idx1);

    auto fvec218 = [flut218](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut218[i](I));
        return ret;
    };

    std::cerr << "\rLUT218   ";
    long gin218 = 1 * gout103[1] + 2 * gout178[1] + 4 * gout120[1];
    std::vector<long> gout218 = fvec218(gin218);

    std::vector<RotationPoly> lut219;
    std::vector<long (*)(long)> flut219;
    auto lut219idx0 = [](long I) -> long {
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
    lut219.push_back(ctx.genrate_lut(lut219idx0));
    flut219.push_back(lut219idx0);

    auto lut219idx1 = [](long I) -> long {
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
    lut219.push_back(ctx.genrate_lut(lut219idx1));
    flut219.push_back(lut219idx1);

    auto fvec219 = [flut219](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut219[i](I));
        return ret;
    };

    std::cerr << "\rLUT219   ";
    long gin219 = 1 * gout218[0] + 2 * gout179[1] + 4 * gout130[1];
    std::vector<long> gout219 = fvec219(gin219);

    std::vector<RotationPoly> lut220;
    std::vector<long (*)(long)> flut220;
    auto lut220idx0 = [](long I) -> long {
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
    lut220.push_back(ctx.genrate_lut(lut220idx0));
    flut220.push_back(lut220idx0);

    auto lut220idx1 = [](long I) -> long {
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
    lut220.push_back(ctx.genrate_lut(lut220idx1));
    flut220.push_back(lut220idx1);

    auto fvec220 = [flut220](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut220[i](I));
        return ret;
    };

    std::cerr << "\rLUT220   ";
    long gin220 = 1 * gout209[0] + 2 * gout218[1] + 4 * gout208[1];
    std::vector<long> gout220 = fvec220(gin220);

    std::vector<RotationPoly> lut221;
    std::vector<long (*)(long)> flut221;
    auto lut221idx0 = [](long I) -> long {
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
    lut221.push_back(ctx.genrate_lut(lut221idx0));
    flut221.push_back(lut221idx0);

    auto fvec221 = [flut221](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut221[i](I));
        return ret;
    };

    std::cerr << "\rLUT221   ";
    long gin221 = 1 * ct_x1 + 2 * ct_y13;
    std::vector<long> gout221 = fvec221(gin221);

    std::vector<RotationPoly> lut222;
    std::vector<long (*)(long)> flut222;
    auto lut222idx0 = [](long I) -> long {
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
    lut222.push_back(ctx.genrate_lut(lut222idx0));
    flut222.push_back(lut222idx0);

    auto lut222idx1 = [](long I) -> long {
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
    lut222.push_back(ctx.genrate_lut(lut222idx1));
    flut222.push_back(lut222idx1);

    auto fvec222 = [flut222](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut222[i](I));
        return ret;
    };

    std::cerr << "\rLUT222   ";
    long gin222 = 1 * gout221[0] + 2 * ct_y12 + 4 * ct_x2;
    std::vector<long> gout222 = fvec222(gin222);

    std::vector<RotationPoly> lut223;
    std::vector<long (*)(long)> flut223;
    auto lut223idx0 = [](long I) -> long {
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
    lut223.push_back(ctx.genrate_lut(lut223idx0));
    flut223.push_back(lut223idx0);

    auto fvec223 = [flut223](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut223[i](I));
        return ret;
    };

    std::cerr << "\rLUT223   ";
    long gin223 = 1 * gout131[0] + 2 * gout221[0];
    std::vector<long> gout223 = fvec223(gin223);

    std::vector<RotationPoly> lut224;
    std::vector<long (*)(long)> flut224;
    auto lut224idx0 = [](long I) -> long {
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
    lut224.push_back(ctx.genrate_lut(lut224idx0));
    flut224.push_back(lut224idx0);

    auto lut224idx1 = [](long I) -> long {
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
    lut224.push_back(ctx.genrate_lut(lut224idx1));
    flut224.push_back(lut224idx1);

    auto fvec224 = [flut224](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut224[i](I));
        return ret;
    };

    std::cerr << "\rLUT224   ";
    long gin224 = 1 * gout222[1] + 2 * ct_y14 + 4 * ct_x0;
    std::vector<long> gout224 = fvec224(gin224);

    std::vector<RotationPoly> lut225;
    std::vector<long (*)(long)> flut225;
    auto lut225idx0 = [](long I) -> long {
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
    lut225.push_back(ctx.genrate_lut(lut225idx0));
    flut225.push_back(lut225idx0);

    auto lut225idx1 = [](long I) -> long {
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
    lut225.push_back(ctx.genrate_lut(lut225idx1));
    flut225.push_back(lut225idx1);

    auto fvec225 = [flut225](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut225[i](I));
        return ret;
    };

    std::cerr << "\rLUT225   ";
    long gin225 = 1 * gout169[0] + 2 * gout224[1] + 4 * gout144[1];
    std::vector<long> gout225 = fvec225(gin225);

    std::vector<RotationPoly> lut226;
    std::vector<long (*)(long)> flut226;
    auto lut226idx0 = [](long I) -> long {
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
    lut226.push_back(ctx.genrate_lut(lut226idx0));
    flut226.push_back(lut226idx0);

    auto fvec226 = [flut226](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut226[i](I));
        return ret;
    };

    std::cerr << "\rLUT226   ";
    long gin226 = 1 * gout225[0] + 2 * gout132[0] + 4 * gout146[0];
    std::vector<long> gout226 = fvec226(gin226);

    std::vector<RotationPoly> lut227;
    std::vector<long (*)(long)> flut227;
    auto lut227idx0 = [](long I) -> long {
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
    lut227.push_back(ctx.genrate_lut(lut227idx0));
    flut227.push_back(lut227idx0);

    auto lut227idx1 = [](long I) -> long {
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
    lut227.push_back(ctx.genrate_lut(lut227idx1));
    flut227.push_back(lut227idx1);

    auto fvec227 = [flut227](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut227[i](I));
        return ret;
    };

    std::cerr << "\rLUT227   ";
    long gin227 = 1 * gout225[1] + 2 * gout165[0] + 4 * gout149[0];
    std::vector<long> gout227 = fvec227(gin227);

    std::vector<RotationPoly> lut228;
    std::vector<long (*)(long)> flut228;
    auto lut228idx0 = [](long I) -> long {
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
    lut228.push_back(ctx.genrate_lut(lut228idx0));
    flut228.push_back(lut228idx0);

    auto lut228idx1 = [](long I) -> long {
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
    lut228.push_back(ctx.genrate_lut(lut228idx1));
    flut228.push_back(lut228idx1);

    auto fvec228 = [flut228](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut228[i](I));
        return ret;
    };

    std::cerr << "\rLUT228   ";
    long gin228 = 1 * gout205[1] + 2 * gout227[1] + 4 * gout180[0];
    std::vector<long> gout228 = fvec228(gin228);

    std::vector<RotationPoly> lut229;
    std::vector<long (*)(long)> flut229;
    auto lut229idx0 = [](long I) -> long {
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
    lut229.push_back(ctx.genrate_lut(lut229idx0));
    flut229.push_back(lut229idx0);

    auto fvec229 = [flut229](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut229[i](I));
        return ret;
    };

    std::cerr << "\rLUT229   ";
    long gin229 = 1 * ct_y6 + 2 * ct_x3;
    std::vector<long> gout229 = fvec229(gin229);

    std::vector<RotationPoly> lut230;
    std::vector<long (*)(long)> flut230;
    auto lut230idx0 = [](long I) -> long {
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
    lut230.push_back(ctx.genrate_lut(lut230idx0));
    flut230.push_back(lut230idx0);

    auto lut230idx1 = [](long I) -> long {
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
    lut230.push_back(ctx.genrate_lut(lut230idx1));
    flut230.push_back(lut230idx1);

    auto fvec230 = [flut230](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut230[i](I));
        return ret;
    };

    std::cerr << "\rLUT230   ";
    long gin230 = 1 * gout42[0] + 2 * gout23[0] + 4 * gout229[0];
    std::vector<long> gout230 = fvec230(gin230);

    std::vector<RotationPoly> lut231;
    std::vector<long (*)(long)> flut231;
    auto lut231idx0 = [](long I) -> long {
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
    lut231.push_back(ctx.genrate_lut(lut231idx0));
    flut231.push_back(lut231idx0);

    auto lut231idx1 = [](long I) -> long {
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
    lut231.push_back(ctx.genrate_lut(lut231idx1));
    flut231.push_back(lut231idx1);

    auto fvec231 = [flut231](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut231[i](I));
        return ret;
    };

    std::cerr << "\rLUT231   ";
    long gin231 = 1 * gout230[0] + 2 * gout133[0] + 4 * gout65[1];
    std::vector<long> gout231 = fvec231(gin231);

    std::vector<RotationPoly> lut232;
    std::vector<long (*)(long)> flut232;
    auto lut232idx0 = [](long I) -> long {
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
    lut232.push_back(ctx.genrate_lut(lut232idx0));
    flut232.push_back(lut232idx0);

    auto lut232idx1 = [](long I) -> long {
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
    lut232.push_back(ctx.genrate_lut(lut232idx1));
    flut232.push_back(lut232idx1);

    auto fvec232 = [flut232](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut232[i](I));
        return ret;
    };

    std::cerr << "\rLUT232   ";
    long gin232 = 1 * gout75[1] + 2 * gout139[1] + 4 * gout190[1];
    std::vector<long> gout232 = fvec232(gin232);

    std::vector<RotationPoly> lut233;
    std::vector<long (*)(long)> flut233;
    auto lut233idx0 = [](long I) -> long {
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
    lut233.push_back(ctx.genrate_lut(lut233idx0));
    flut233.push_back(lut233idx0);

    auto lut233idx1 = [](long I) -> long {
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
    lut233.push_back(ctx.genrate_lut(lut233idx1));
    flut233.push_back(lut233idx1);

    auto fvec233 = [flut233](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut233[i](I));
        return ret;
    };

    std::cerr << "\rLUT233   ";
    long gin233 = 1 * gout114[1] + 2 * gout232[1] + 4 * gout121[1];
    std::vector<long> gout233 = fvec233(gin233);

    std::vector<RotationPoly> lut234;
    std::vector<long (*)(long)> flut234;
    auto lut234idx0 = [](long I) -> long {
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
    lut234.push_back(ctx.genrate_lut(lut234idx0));
    flut234.push_back(lut234idx0);

    auto lut234idx1 = [](long I) -> long {
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
    lut234.push_back(ctx.genrate_lut(lut234idx1));
    flut234.push_back(lut234idx1);

    auto fvec234 = [flut234](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut234[i](I));
        return ret;
    };

    std::cerr << "\rLUT234   ";
    long gin234 = 1 * gout174[0] + 2 * gout233[1] + 4 * gout128[0];
    std::vector<long> gout234 = fvec234(gin234);

    std::vector<RotationPoly> lut235;
    std::vector<long (*)(long)> flut235;
    auto lut235idx0 = [](long I) -> long {
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
    lut235.push_back(ctx.genrate_lut(lut235idx0));
    flut235.push_back(lut235idx0);

    auto lut235idx1 = [](long I) -> long {
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
    lut235.push_back(ctx.genrate_lut(lut235idx1));
    flut235.push_back(lut235idx1);

    auto fvec235 = [flut235](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut235[i](I));
        return ret;
    };

    std::cerr << "\rLUT235   ";
    long gin235 = 1 * gout176[0] + 2 * gout234[1];
    std::vector<long> gout235 = fvec235(gin235);

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
    long gin236 = 1 * gout204[0] + 2 * gout235[1];
    std::vector<long> gout236 = fvec236(gin236);

    std::vector<RotationPoly> lut237;
    std::vector<long (*)(long)> flut237;
    auto lut237idx0 = [](long I) -> long {
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
    lut237.push_back(ctx.genrate_lut(lut237idx0));
    flut237.push_back(lut237idx0);

    auto fvec237 = [flut237](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut237[i](I));
        return ret;
    };

    std::cerr << "\rLUT237   ";
    long gin237 = 1 * gout16[1] + 2 * gout138[1] + 4 * gout194[0];
    std::vector<long> gout237 = fvec237(gin237);

    std::vector<RotationPoly> lut238;
    std::vector<long (*)(long)> flut238;
    auto lut238idx0 = [](long I) -> long {
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
    lut238.push_back(ctx.genrate_lut(lut238idx0));
    flut238.push_back(lut238idx0);

    auto fvec238 = [flut238](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut238[i](I));
        return ret;
    };

    std::cerr << "\rLUT238   ";
    long gin238 = 1 * gout237[0] + 2 * gout57[0] + 4 * gout157[0];
    std::vector<long> gout238 = fvec238(gin238);

    std::vector<RotationPoly> lut239;
    std::vector<long (*)(long)> flut239;
    auto lut239idx0 = [](long I) -> long {
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
    lut239.push_back(ctx.genrate_lut(lut239idx0));
    flut239.push_back(lut239idx0);

    auto fvec239 = [flut239](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut239[i](I));
        return ret;
    };

    std::cerr << "\rLUT239   ";
    long gin239 = 1 * gout238[0] + 2 * gout195[0];
    std::vector<long> gout239 = fvec239(gin239);

    std::cerr << "\rFA240    ";
    long gin240 = gout16[2] + 1 * ct_x2 + 2 * ct_x3 + 1 * ct_y2 + 2 * ct_y3;
    std::vector<long> gout240 = vdecomp(gin240);

    std::vector<RotationPoly> lut241;
    std::vector<long (*)(long)> flut241;
    auto lut241idx0 = [](long I) -> long {
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
    lut241.push_back(ctx.genrate_lut(lut241idx0));
    flut241.push_back(lut241idx0);

    auto fvec241 = [flut241](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut241[i](I));
        return ret;
    };

    std::cerr << "\rLUT241   ";
    long gin241 = 1 * gout240[0] + 2 * gout210[0] + 4 * gout194[0];
    std::vector<long> gout241 = fvec241(gin241);

    std::vector<RotationPoly> lut242;
    std::vector<long (*)(long)> flut242;
    auto lut242idx0 = [](long I) -> long {
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
    lut242.push_back(ctx.genrate_lut(lut242idx0));
    flut242.push_back(lut242idx0);

    auto fvec242 = [flut242](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut242[i](I));
        return ret;
    };

    std::cerr << "\rLUT242   ";
    long gin242 = 1 * gout241[0] + 2 * gout157[0];
    std::vector<long> gout242 = fvec242(gin242);

    std::vector<RotationPoly> lut243;
    std::vector<long (*)(long)> flut243;
    auto lut243idx0 = [](long I) -> long {
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
    lut243.push_back(ctx.genrate_lut(lut243idx0));
    flut243.push_back(lut243idx0);

    auto fvec243 = [flut243](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut243[i](I));
        return ret;
    };

    std::cerr << "\rLUT243   ";
    long gin243 = 1 * gout240[1] + 2 * gout210[1] + 4 * gout194[0];
    std::vector<long> gout243 = fvec243(gin243);

    std::vector<RotationPoly> lut244;
    std::vector<long (*)(long)> flut244;
    auto lut244idx0 = [](long I) -> long {
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
    lut244.push_back(ctx.genrate_lut(lut244idx0));
    flut244.push_back(lut244idx0);

    auto fvec244 = [flut244](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut244[i](I));
        return ret;
    };

    std::cerr << "\rLUT244   ";
    long gin244 = 1 * gout243[0] + 2 * gout157[0];
    std::vector<long> gout244 = fvec244(gin244);

    std::cerr << "\rFA245    ";
    long gin245 = gout240[2] + 1 * ct_x4 + 2 * ct_x5 + 1 * ct_y4 + 2 * ct_y5;
    std::vector<long> gout245 = vdecomp(gin245);

    std::vector<RotationPoly> lut246;
    std::vector<long (*)(long)> flut246;
    auto lut246idx0 = [](long I) -> long {
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
    lut246.push_back(ctx.genrate_lut(lut246idx0));
    flut246.push_back(lut246idx0);

    auto fvec246 = [flut246](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut246[i](I));
        return ret;
    };

    std::cerr << "\rLUT246   ";
    long gin246 = 1 * gout245[0] + 2 * gout211[0] + 4 * gout194[0];
    std::vector<long> gout246 = fvec246(gin246);

    std::vector<RotationPoly> lut247;
    std::vector<long (*)(long)> flut247;
    auto lut247idx0 = [](long I) -> long {
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
    lut247.push_back(ctx.genrate_lut(lut247idx0));
    flut247.push_back(lut247idx0);

    auto fvec247 = [flut247](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut247[i](I));
        return ret;
    };

    std::cerr << "\rLUT247   ";
    long gin247 = 1 * gout246[0] + 2 * gout157[0];
    std::vector<long> gout247 = fvec247(gin247);

    std::vector<RotationPoly> lut248;
    std::vector<long (*)(long)> flut248;
    auto lut248idx0 = [](long I) -> long {
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
    lut248.push_back(ctx.genrate_lut(lut248idx0));
    flut248.push_back(lut248idx0);

    auto fvec248 = [flut248](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut248[i](I));
        return ret;
    };

    std::cerr << "\rLUT248   ";
    long gin248 = 1 * ct_x1 + 2 * ct_y14;
    std::vector<long> gout248 = fvec248(gin248);

    std::vector<RotationPoly> lut249;
    std::vector<long (*)(long)> flut249;
    auto lut249idx0 = [](long I) -> long {
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
    lut249.push_back(ctx.genrate_lut(lut249idx0));
    flut249.push_back(lut249idx0);

    auto fvec249 = [flut249](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut249[i](I));
        return ret;
    };

    std::cerr << "\rLUT249   ";
    long gin249 = 1 * ct_x0 + 2 * gout248[0] + 4 * ct_y15;
    std::vector<long> gout249 = fvec249(gin249);

    std::vector<RotationPoly> lut250;
    std::vector<long (*)(long)> flut250;
    auto lut250idx0 = [](long I) -> long {
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
    lut250.push_back(ctx.genrate_lut(lut250idx0));
    flut250.push_back(lut250idx0);

    auto fvec250 = [flut250](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut250[i](I));
        return ret;
    };

    std::cerr << "\rLUT250   ";
    long gin250 = 1 * gout224[0] + 2 * gout222[0] + 4 * gout249[0];
    std::vector<long> gout250 = fvec250(gin250);

    std::vector<RotationPoly> lut251;
    std::vector<long (*)(long)> flut251;
    auto lut251idx0 = [](long I) -> long {
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
    lut251.push_back(ctx.genrate_lut(lut251idx0));
    flut251.push_back(lut251idx0);

    auto fvec251 = [flut251](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut251[i](I));
        return ret;
    };

    std::cerr << "\rLUT251   ";
    long gin251 = 1 * gout227[0] + 2 * gout250[0];
    std::vector<long> gout251 = fvec251(gin251);

    std::vector<RotationPoly> lut252;
    std::vector<long (*)(long)> flut252;
    auto lut252idx0 = [](long I) -> long {
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
    lut252.push_back(ctx.genrate_lut(lut252idx0));
    flut252.push_back(lut252idx0);

    auto fvec252 = [flut252](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut252[i](I));
        return ret;
    };

    std::cerr << "\rLUT252   ";
    long gin252 = 1 * ct_y1 + 2 * ct_x7;
    std::vector<long> gout252 = fvec252(gin252);

    std::vector<RotationPoly> lut253;
    std::vector<long (*)(long)> flut253;
    auto lut253idx0 = [](long I) -> long {
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
    lut253.push_back(ctx.genrate_lut(lut253idx0));
    flut253.push_back(lut253idx0);

    auto lut253idx1 = [](long I) -> long {
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
    lut253.push_back(ctx.genrate_lut(lut253idx1));
    flut253.push_back(lut253idx1);

    auto fvec253 = [flut253](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut253[i](I));
        return ret;
    };

    std::cerr << "\rLUT253   ";
    long gin253 = 1 * gout252[0] + 2 * gout90[0] + 4 * gout67[0];
    std::vector<long> gout253 = fvec253(gin253);

    std::vector<RotationPoly> lut254;
    std::vector<long (*)(long)> flut254;
    auto lut254idx0 = [](long I) -> long {
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
    lut254.push_back(ctx.genrate_lut(lut254idx0));
    flut254.push_back(lut254idx0);

    auto lut254idx1 = [](long I) -> long {
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
    lut254.push_back(ctx.genrate_lut(lut254idx1));
    flut254.push_back(lut254idx1);

    auto fvec254 = [flut254](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut254[i](I));
        return ret;
    };

    std::cerr << "\rLUT254   ";
    long gin254 = 1 * gout253[0] + 2 * gout182[1] + 4 * gout65[0];
    std::vector<long> gout254 = fvec254(gin254);

    std::vector<RotationPoly> lut255;
    std::vector<long (*)(long)> flut255;
    auto lut255idx0 = [](long I) -> long {
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
    lut255.push_back(ctx.genrate_lut(lut255idx0));
    flut255.push_back(lut255idx0);

    auto fvec255 = [flut255](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut255[i](I));
        return ret;
    };

    std::cerr << "\rLUT255   ";
    long gin255 = 1 * gout245[1] + 2 * gout211[1] + 4 * gout194[0];
    std::vector<long> gout255 = fvec255(gin255);

    std::cerr << "\rFA256    ";
    long gin256 = gout245[2] + 1 * ct_x6 + 2 * ct_x7 + 1 * ct_y6 + 2 * ct_y7;
    std::vector<long> gout256 = vdecomp(gin256);

    std::vector<RotationPoly> lut257;
    std::vector<long (*)(long)> flut257;
    auto lut257idx0 = [](long I) -> long {
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
    lut257.push_back(ctx.genrate_lut(lut257idx0));
    flut257.push_back(lut257idx0);

    auto fvec257 = [flut257](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut257[i](I));
        return ret;
    };

    std::cerr << "\rLUT257   ";
    long gin257 = 1 * gout256[0] + 2 * gout212[0] + 4 * gout194[0];
    std::vector<long> gout257 = fvec257(gin257);

    std::vector<RotationPoly> lut258;
    std::vector<long (*)(long)> flut258;
    auto lut258idx0 = [](long I) -> long {
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
    lut258.push_back(ctx.genrate_lut(lut258idx0));
    flut258.push_back(lut258idx0);

    auto fvec258 = [flut258](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut258[i](I));
        return ret;
    };

    std::cerr << "\rLUT258   ";
    long gin258 = 1 * gout257[0] + 2 * gout157[0];
    std::vector<long> gout258 = fvec258(gin258);

    std::vector<RotationPoly> lut259;
    std::vector<long (*)(long)> flut259;
    auto lut259idx0 = [](long I) -> long {
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
    lut259.push_back(ctx.genrate_lut(lut259idx0));
    flut259.push_back(lut259idx0);

    auto fvec259 = [flut259](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut259[i](I));
        return ret;
    };

    std::cerr << "\rLUT259   ";
    long gin259 = 1 * gout256[1] + 2 * gout212[1] + 4 * gout194[0];
    std::vector<long> gout259 = fvec259(gin259);

    std::cerr << "\rFA260    ";
    long gin260 = gout256[2] + 1 * ct_x8 + 2 * ct_x9 + 1 * ct_y8 + 2 * ct_y9;
    std::vector<long> gout260 = vdecomp(gin260);

    std::vector<RotationPoly> lut261;
    std::vector<long (*)(long)> flut261;
    auto lut261idx0 = [](long I) -> long {
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
    lut261.push_back(ctx.genrate_lut(lut261idx0));
    flut261.push_back(lut261idx0);

    auto fvec261 = [flut261](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut261[i](I));
        return ret;
    };

    std::cerr << "\rLUT261   ";
    long gin261 = 1 * gout260[0] + 2 * gout213[0] + 4 * gout194[0];
    std::vector<long> gout261 = fvec261(gin261);

    std::vector<RotationPoly> lut262;
    std::vector<long (*)(long)> flut262;
    auto lut262idx0 = [](long I) -> long {
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
    lut262.push_back(ctx.genrate_lut(lut262idx0));
    flut262.push_back(lut262idx0);

    auto fvec262 = [flut262](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut262[i](I));
        return ret;
    };

    std::cerr << "\rLUT262   ";
    long gin262 = 1 * gout260[1] + 2 * gout213[1] + 4 * gout194[0];
    std::vector<long> gout262 = fvec262(gin262);

    std::vector<RotationPoly> lut263;
    std::vector<long (*)(long)> flut263;
    auto lut263idx0 = [](long I) -> long {
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
    lut263.push_back(ctx.genrate_lut(lut263idx0));
    flut263.push_back(lut263idx0);

    auto fvec263 = [flut263](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut263[i](I));
        return ret;
    };

    std::cerr << "\rLUT263   ";
    long gin263 = 1 * gout262[0] + 2 * gout157[0];
    std::vector<long> gout263 = fvec263(gin263);

    std::cerr << "\rFA264    ";
    long gin264 = gout260[2] + 1 * ct_x10 + 2 * ct_x11 + 1 * ct_y10 + 2 * ct_y11;
    std::vector<long> gout264 = vdecomp(gin264);

    std::vector<RotationPoly> lut265;
    std::vector<long (*)(long)> flut265;
    auto lut265idx0 = [](long I) -> long {
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
    lut265.push_back(ctx.genrate_lut(lut265idx0));
    flut265.push_back(lut265idx0);

    auto fvec265 = [flut265](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut265[i](I));
        return ret;
    };

    std::cerr << "\rLUT265   ";
    long gin265 = 1 * gout264[0] + 2 * gout214[0] + 4 * gout194[0];
    std::vector<long> gout265 = fvec265(gin265);

    std::vector<RotationPoly> lut266;
    std::vector<long (*)(long)> flut266;
    auto lut266idx0 = [](long I) -> long {
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
    lut266.push_back(ctx.genrate_lut(lut266idx0));
    flut266.push_back(lut266idx0);

    auto fvec266 = [flut266](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut266[i](I));
        return ret;
    };

    std::cerr << "\rLUT266   ";
    long gin266 = 1 * gout265[0] + 2 * gout157[0];
    std::vector<long> gout266 = fvec266(gin266);

    std::vector<RotationPoly> lut267;
    std::vector<long (*)(long)> flut267;
    auto lut267idx0 = [](long I) -> long {
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
    lut267.push_back(ctx.genrate_lut(lut267idx0));
    flut267.push_back(lut267idx0);

    auto fvec267 = [flut267](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut267[i](I));
        return ret;
    };

    std::cerr << "\rLUT267   ";
    long gin267 = 1 * gout264[1] + 2 * gout214[1] + 4 * gout194[0];
    std::vector<long> gout267 = fvec267(gin267);

    std::vector<RotationPoly> lut268;
    std::vector<long (*)(long)> flut268;
    auto lut268idx0 = [](long I) -> long {
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
    lut268.push_back(ctx.genrate_lut(lut268idx0));
    flut268.push_back(lut268idx0);

    auto fvec268 = [flut268](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut268[i](I));
        return ret;
    };

    std::cerr << "\rLUT268   ";
    long gin268 = 1 * gout267[0] + 2 * gout157[0];
    std::vector<long> gout268 = fvec268(gin268);

    std::cerr << "\rFA269    ";
    long gin269 = gout264[2] + 1 * ct_x12 + 2 * ct_x13 + 1 * ct_y12 + 2 * ct_y13;
    std::vector<long> gout269 = vdecomp(gin269);

    std::vector<RotationPoly> lut270;
    std::vector<long (*)(long)> flut270;
    auto lut270idx0 = [](long I) -> long {
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
    lut270.push_back(ctx.genrate_lut(lut270idx0));
    flut270.push_back(lut270idx0);

    auto fvec270 = [flut270](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut270[i](I));
        return ret;
    };

    std::cerr << "\rLUT270   ";
    long gin270 = 1 * gout269[0] + 2 * gout215[0] + 4 * gout194[0];
    std::vector<long> gout270 = fvec270(gin270);

    std::vector<RotationPoly> lut271;
    std::vector<long (*)(long)> flut271;
    auto lut271idx0 = [](long I) -> long {
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
    lut271.push_back(ctx.genrate_lut(lut271idx0));
    flut271.push_back(lut271idx0);

    auto fvec271 = [flut271](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut271[i](I));
        return ret;
    };

    std::cerr << "\rLUT271   ";
    long gin271 = 1 * gout270[0] + 2 * gout157[0];
    std::vector<long> gout271 = fvec271(gin271);

    std::vector<RotationPoly> lut272;
    std::vector<long (*)(long)> flut272;
    auto lut272idx0 = [](long I) -> long {
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
    lut272.push_back(ctx.genrate_lut(lut272idx0));
    flut272.push_back(lut272idx0);

    auto fvec272 = [flut272](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut272[i](I));
        return ret;
    };

    std::cerr << "\rLUT272   ";
    long gin272 = 1 * gout269[1] + 2 * gout215[1] + 4 * gout194[0];
    std::vector<long> gout272 = fvec272(gin272);

    std::vector<RotationPoly> lut273;
    std::vector<long (*)(long)> flut273;
    auto lut273idx0 = [](long I) -> long {
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
    lut273.push_back(ctx.genrate_lut(lut273idx0));
    flut273.push_back(lut273idx0);

    auto fvec273 = [flut273](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut273[i](I));
        return ret;
    };

    std::cerr << "\rLUT273   ";
    long gin273 = 1 * gout272[0] + 2 * gout157[0];
    std::vector<long> gout273 = fvec273(gin273);

    std::cerr << "\rFA274    ";
    long gin274 = gout269[2] + 1 * ct_x14 + 2 * ct_x15 + 1 * ct_y14 + 2 * ct_y15;
    std::vector<long> gout274 = vdecomp(gin274);

    std::vector<RotationPoly> lut275;
    std::vector<long (*)(long)> flut275;
    auto lut275idx0 = [](long I) -> long {
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
    lut275.push_back(ctx.genrate_lut(lut275idx0));
    flut275.push_back(lut275idx0);

    auto fvec275 = [flut275](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut275[i](I));
        return ret;
    };

    std::cerr << "\rLUT275   ";
    long gin275 = 1 * gout274[0] + 2 * gout216[0] + 4 * gout194[0];
    std::vector<long> gout275 = fvec275(gin275);

    std::vector<RotationPoly> lut276;
    std::vector<long (*)(long)> flut276;
    auto lut276idx0 = [](long I) -> long {
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
    lut276.push_back(ctx.genrate_lut(lut276idx0));
    flut276.push_back(lut276idx0);

    auto fvec276 = [flut276](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut276[i](I));
        return ret;
    };

    std::cerr << "\rLUT276   ";
    long gin276 = 1 * gout275[0] + 2 * gout157[0];
    std::vector<long> gout276 = fvec276(gin276);

    std::vector<RotationPoly> lut277;
    std::vector<long (*)(long)> flut277;
    auto lut277idx0 = [](long I) -> long {
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
    lut277.push_back(ctx.genrate_lut(lut277idx0));
    flut277.push_back(lut277idx0);

    auto fvec277 = [flut277](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut277[i](I));
        return ret;
    };

    std::cerr << "\rLUT277   ";
    long gin277 = 1 * gout274[1] + 2 * gout216[1] + 4 * gout194[0];
    std::vector<long> gout277 = fvec277(gin277);

    std::vector<RotationPoly> lut278;
    std::vector<long (*)(long)> flut278;
    auto lut278idx0 = [](long I) -> long {
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
    lut278.push_back(ctx.genrate_lut(lut278idx0));
    flut278.push_back(lut278idx0);

    auto fvec278 = [flut278](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut278[i](I));
        return ret;
    };

    std::cerr << "\rLUT278   ";
    long gin278 = 1 * gout277[0] + 2 * gout157[0];
    std::vector<long> gout278 = fvec278(gin278);

    std::vector<RotationPoly> lut279;
    std::vector<long (*)(long)> flut279;
    auto lut279idx0 = [](long I) -> long {
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
    lut279.push_back(ctx.genrate_lut(lut279idx0));
    flut279.push_back(lut279idx0);

    auto fvec279 = [flut279](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut279[i](I));
        return ret;
    };

    std::cerr << "\rLUT279   ";
    long gin279 = 1 * gout186[0] + 2 * gout185[0] + 4 * gout160[0];
    std::vector<long> gout279 = fvec279(gin279);

    std::vector<RotationPoly> lut280;
    std::vector<long (*)(long)> flut280;
    auto lut280idx0 = [](long I) -> long {
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
    lut280.push_back(ctx.genrate_lut(lut280idx0));
    flut280.push_back(lut280idx0);

    auto fvec280 = [flut280](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut280[i](I));
        return ret;
    };

    std::cerr << "\rLUT280   ";
    long gin280 = 1 * gout188[0] + 2 * gout279[0] + 4 * gout101[0];
    std::vector<long> gout280 = fvec280(gin280);

    std::vector<RotationPoly> lut281;
    std::vector<long (*)(long)> flut281;
    auto lut281idx0 = [](long I) -> long {
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
    lut281.push_back(ctx.genrate_lut(lut281idx0));
    flut281.push_back(lut281idx0);

    auto fvec281 = [flut281](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut281[i](I));
        return ret;
    };

    std::cerr << "\rLUT281   ";
    long gin281 = 1 * gout261[0] + 2 * gout157[0];
    std::vector<long> gout281 = fvec281(gin281);

    std::vector<RotationPoly> lut282;
    std::vector<long (*)(long)> flut282;
    auto lut282idx0 = [](long I) -> long {
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
    lut282.push_back(ctx.genrate_lut(lut282idx0));
    flut282.push_back(lut282idx0);

    auto fvec282 = [flut282](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut282[i](I));
        return ret;
    };

    std::cerr << "\rLUT282   ";
    long gin282 = 1 * gout255[0] + 2 * gout157[0];
    std::vector<long> gout282 = fvec282(gin282);

    std::vector<RotationPoly> lut283;
    std::vector<long (*)(long)> flut283;
    auto lut283idx0 = [](long I) -> long {
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
    lut283.push_back(ctx.genrate_lut(lut283idx0));
    flut283.push_back(lut283idx0);

    auto fvec283 = [flut283](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut283[i](I));
        return ret;
    };

    std::cerr << "\rLUT283   ";
    long gin283 = 1 * gout57[1] + 2 * gout200[1];
    std::vector<long> gout283 = fvec283(gin283);

    std::vector<RotationPoly> lut284;
    std::vector<long (*)(long)> flut284;
    auto lut284idx0 = [](long I) -> long {
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
    lut284.push_back(ctx.genrate_lut(lut284idx0));
    flut284.push_back(lut284idx0);

    auto fvec284 = [flut284](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut284[i](I));
        return ret;
    };

    std::cerr << "\rLUT284   ";
    long gin284 = 1 * gout283[0] + 2 * gout201[1];
    std::vector<long> gout284 = fvec284(gin284);

    std::vector<RotationPoly> lut285;
    std::vector<long (*)(long)> flut285;
    auto lut285idx0 = [](long I) -> long {
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
    lut285.push_back(ctx.genrate_lut(lut285idx0));
    flut285.push_back(lut285idx0);

    auto fvec285 = [flut285](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut285[i](I));
        return ret;
    };

    std::cerr << "\rLUT285   ";
    long gin285 = 1 * gout284[0] + 2 * gout202[1];
    std::vector<long> gout285 = fvec285(gin285);

    std::vector<RotationPoly> lut286;
    std::vector<long (*)(long)> flut286;
    auto lut286idx0 = [](long I) -> long {
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
    lut286.push_back(ctx.genrate_lut(lut286idx0));
    flut286.push_back(lut286idx0);

    auto fvec286 = [flut286](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut286[i](I));
        return ret;
    };

    std::cerr << "\rLUT286   ";
    long gin286 = 1 * gout285[0] + 2 * gout203[1];
    std::vector<long> gout286 = fvec286(gin286);

    std::vector<RotationPoly> lut287;
    std::vector<long (*)(long)> flut287;
    auto lut287idx0 = [](long I) -> long {
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
    lut287.push_back(ctx.genrate_lut(lut287idx0));
    flut287.push_back(lut287idx0);

    auto fvec287 = [flut287](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut287[i](I));
        return ret;
    };

    std::cerr << "\rLUT287   ";
    long gin287 = 1 * gout204[1] + 2 * gout286[0] + 4 * gout204[0];
    std::vector<long> gout287 = fvec287(gin287);

    std::vector<RotationPoly> lut288;
    std::vector<long (*)(long)> flut288;
    auto lut288idx0 = [](long I) -> long {
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
    lut288.push_back(ctx.genrate_lut(lut288idx0));
    flut288.push_back(lut288idx0);

    auto fvec288 = [flut288](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut288[i](I));
        return ret;
    };

    std::cerr << "\rLUT288   ";
    long gin288 = 1 * gout287[0] + 2 * gout235[1];
    std::vector<long> gout288 = fvec288(gin288);

    std::vector<RotationPoly> lut289;
    std::vector<long (*)(long)> flut289;
    auto lut289idx0 = [](long I) -> long {
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
    lut289.push_back(ctx.genrate_lut(lut289idx0));
    flut289.push_back(lut289idx0);

    auto fvec289 = [flut289](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut289[i](I));
        return ret;
    };

    std::cerr << "\rLUT289   ";
    long gin289 = 1 * gout259[0] + 2 * gout288[0] + 4 * gout157[0];
    std::vector<long> gout289 = fvec289(gin289);

    std::vector<RotationPoly> lut290;
    std::vector<long (*)(long)> flut290;
    auto lut290idx0 = [](long I) -> long {
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
    lut290.push_back(ctx.genrate_lut(lut290idx0));
    flut290.push_back(lut290idx0);

    auto fvec290 = [flut290](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut290[i](I));
        return ret;
    };

    std::cerr << "\rLUT290   ";
    long gin290 = 1 * gout195[0] + 2 * gout289[0];
    std::vector<long> gout290 = fvec290(gin290);

    std::vector<RotationPoly> lut291;
    std::vector<long (*)(long)> flut291;
    auto lut291idx0 = [](long I) -> long {
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
    lut291.push_back(ctx.genrate_lut(lut291idx0));
    flut291.push_back(lut291idx0);

    auto fvec291 = [flut291](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut291[i](I));
        return ret;
    };

    std::cerr << "\rLUT291   ";
    long gin291 = 1 * gout204[1] + 2 * gout286[0] + 4 * gout235[1];
    std::vector<long> gout291 = fvec291(gin291);

    std::vector<RotationPoly> lut292;
    std::vector<long (*)(long)> flut292;
    auto lut292idx0 = [](long I) -> long {
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
    lut292.push_back(ctx.genrate_lut(lut292idx0));
    flut292.push_back(lut292idx0);

    auto fvec292 = [flut292](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut292[i](I));
        return ret;
    };

    std::cerr << "\rLUT292   ";
    long gin292 = 1 * gout204[1] + 2 * gout286[0] + 4 * gout157[0];
    std::vector<long> gout292 = fvec292(gin292);

    std::vector<RotationPoly> lut293;
    std::vector<long (*)(long)> flut293;
    auto lut293idx0 = [](long I) -> long {
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
    lut293.push_back(ctx.genrate_lut(lut293idx0));
    flut293.push_back(lut293idx0);

    auto fvec293 = [flut293](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut293[i](I));
        return ret;
    };

    std::cerr << "\rLUT293   ";
    long gin293 = 1 * gout292[0] + 2 * gout258[0] + 4 * gout195[0];
    std::vector<long> gout293 = fvec293(gin293);

    std::vector<RotationPoly> lut294;
    std::vector<long (*)(long)> flut294;
    auto lut294idx0 = [](long I) -> long {
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
    lut294.push_back(ctx.genrate_lut(lut294idx0));
    flut294.push_back(lut294idx0);

    auto fvec294 = [flut294](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut294[i](I));
        return ret;
    };

    std::cerr << "\rLUT294   ";
    long gin294 = 1 * gout285[0] + 2 * gout203[1] + 4 * gout157[0];
    std::vector<long> gout294 = fvec294(gin294);

    std::vector<RotationPoly> lut295;
    std::vector<long (*)(long)> flut295;
    auto lut295idx0 = [](long I) -> long {
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
    lut295.push_back(ctx.genrate_lut(lut295idx0));
    flut295.push_back(lut295idx0);

    auto fvec295 = [flut295](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut295[i](I));
        return ret;
    };

    std::cerr << "\rLUT295   ";
    long gin295 = 1 * gout294[0] + 2 * gout282[0] + 4 * gout195[0];
    std::vector<long> gout295 = fvec295(gin295);

    std::vector<RotationPoly> lut296;
    std::vector<long (*)(long)> flut296;
    auto lut296idx0 = [](long I) -> long {
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
    lut296.push_back(ctx.genrate_lut(lut296idx0));
    flut296.push_back(lut296idx0);

    auto fvec296 = [flut296](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut296[i](I));
        return ret;
    };

    std::cerr << "\rLUT296   ";
    long gin296 = 1 * gout284[0] + 2 * gout202[1] + 4 * gout157[0];
    std::vector<long> gout296 = fvec296(gin296);

    std::vector<RotationPoly> lut297;
    std::vector<long (*)(long)> flut297;
    auto lut297idx0 = [](long I) -> long {
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
    lut297.push_back(ctx.genrate_lut(lut297idx0));
    flut297.push_back(lut297idx0);

    auto fvec297 = [flut297](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut297[i](I));
        return ret;
    };

    std::cerr << "\rLUT297   ";
    long gin297 = 1 * gout296[0] + 2 * gout247[0] + 4 * gout195[0];
    std::vector<long> gout297 = fvec297(gin297);

    std::vector<RotationPoly> lut298;
    std::vector<long (*)(long)> flut298;
    auto lut298idx0 = [](long I) -> long {
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
    lut298.push_back(ctx.genrate_lut(lut298idx0));
    flut298.push_back(lut298idx0);

    auto fvec298 = [flut298](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut298[i](I));
        return ret;
    };

    std::cerr << "\rLUT298   ";
    long gin298 = 1 * gout283[0] + 2 * gout201[1] + 4 * gout157[0];
    std::vector<long> gout298 = fvec298(gin298);

    std::vector<RotationPoly> lut299;
    std::vector<long (*)(long)> flut299;
    auto lut299idx0 = [](long I) -> long {
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
    lut299.push_back(ctx.genrate_lut(lut299idx0));
    flut299.push_back(lut299idx0);

    auto fvec299 = [flut299](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut299[i](I));
        return ret;
    };

    std::cerr << "\rLUT299   ";
    long gin299 = 1 * gout298[0] + 2 * gout244[0] + 4 * gout195[0];
    std::vector<long> gout299 = fvec299(gin299);

    std::vector<RotationPoly> lut300;
    std::vector<long (*)(long)> flut300;
    auto lut300idx0 = [](long I) -> long {
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
    lut300.push_back(ctx.genrate_lut(lut300idx0));
    flut300.push_back(lut300idx0);

    auto fvec300 = [flut300](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut300[i](I));
        return ret;
    };

    std::cerr << "\rLUT300   ";
    long gin300 = 1 * gout57[1] + 2 * gout200[1] + 4 * gout157[0];
    std::vector<long> gout300 = fvec300(gin300);

    std::vector<RotationPoly> lut301;
    std::vector<long (*)(long)> flut301;
    auto lut301idx0 = [](long I) -> long {
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
    lut301.push_back(ctx.genrate_lut(lut301idx0));
    flut301.push_back(lut301idx0);

    auto fvec301 = [flut301](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut301[i](I));
        return ret;
    };

    std::cerr << "\rLUT301   ";
    long gin301 = 1 * gout300[0] + 2 * gout242[0] + 4 * gout195[0];
    std::vector<long> gout301 = fvec301(gin301);

    std::vector<RotationPoly> lut302;
    std::vector<long (*)(long)> flut302;
    auto lut302idx0 = [](long I) -> long {
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
    lut302.push_back(ctx.genrate_lut(lut302idx0));
    flut302.push_back(lut302idx0);

    auto fvec302 = [flut302](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut302[i](I));
        return ret;
    };

    std::cerr << "\rLUT302   ";
    long gin302 = 1 * gout205[0] + 2 * gout187[1] + 4 * gout172[0];
    std::vector<long> gout302 = fvec302(gin302);

    std::vector<RotationPoly> lut303;
    std::vector<long (*)(long)> flut303;
    auto lut303idx0 = [](long I) -> long {
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
    lut303.push_back(ctx.genrate_lut(lut303idx0));
    flut303.push_back(lut303idx0);

    auto fvec303 = [flut303](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut303[i](I));
        return ret;
    };

    std::cerr << "\rLUT303   ";
    long gin303 = 1 * gout280[0] + 2 * gout302[0] + 4 * gout226[0];
    std::vector<long> gout303 = fvec303(gin303);

    std::vector<RotationPoly> lut304;
    std::vector<long (*)(long)> flut304;
    auto lut304idx0 = [](long I) -> long {
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
    lut304.push_back(ctx.genrate_lut(lut304idx0));
    flut304.push_back(lut304idx0);

    auto fvec304 = [flut304](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut304[i](I));
        return ret;
    };

    std::cerr << "\rLUT304   ";
    long gin304 = 1 * gout303[0] + 2 * gout228[1] + 4 * gout251[0];
    std::vector<long> gout304 = fvec304(gin304);

    std::vector<RotationPoly> lut305;
    std::vector<long (*)(long)> flut305;
    auto lut305idx0 = [](long I) -> long {
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
    lut305.push_back(ctx.genrate_lut(lut305idx0));
    flut305.push_back(lut305idx0);

    auto fvec305 = [flut305](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut305[i](I));
        return ret;
    };

    std::cerr << "\rLUT305   ";
    long gin305 = 1 * ct_x2 + 2 * ct_y9;
    std::vector<long> gout305 = fvec305(gin305);

    std::vector<RotationPoly> lut306;
    std::vector<long (*)(long)> flut306;
    auto lut306idx0 = [](long I) -> long {
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
    lut306.push_back(ctx.genrate_lut(lut306idx0));
    flut306.push_back(lut306idx0);

    auto lut306idx1 = [](long I) -> long {
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
    lut306.push_back(ctx.genrate_lut(lut306idx1));
    flut306.push_back(lut306idx1);

    auto fvec306 = [flut306](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut306[i](I));
        return ret;
    };

    std::cerr << "\rLUT306   ";
    long gin306 = 1 * gout217[0] + 2 * gout141[0] + 4 * gout305[0];
    std::vector<long> gout306 = fvec306(gin306);

    std::vector<RotationPoly> lut307;
    std::vector<long (*)(long)> flut307;
    auto lut307idx0 = [](long I) -> long {
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
    lut307.push_back(ctx.genrate_lut(lut307idx0));
    flut307.push_back(lut307idx0);

    auto lut307idx1 = [](long I) -> long {
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
    lut307.push_back(ctx.genrate_lut(lut307idx1));
    flut307.push_back(lut307idx1);

    auto fvec307 = [flut307](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut307[i](I));
        return ret;
    };

    std::cerr << "\rLUT307   ";
    long gin307 = 1 * gout306[0] + 2 * gout164[1] + 4 * gout131[0];
    std::vector<long> gout307 = fvec307(gin307);

    std::vector<RotationPoly> lut308;
    std::vector<long (*)(long)> flut308;
    auto lut308idx0 = [](long I) -> long {
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
    lut308.push_back(ctx.genrate_lut(lut308idx0));
    flut308.push_back(lut308idx0);

    auto lut308idx1 = [](long I) -> long {
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
    lut308.push_back(ctx.genrate_lut(lut308idx1));
    flut308.push_back(lut308idx1);

    auto fvec308 = [flut308](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut308[i](I));
        return ret;
    };

    std::cerr << "\rLUT308   ";
    long gin308 = 1 * gout307[0] + 2 * gout165[1] + 4 * gout130[0];
    std::vector<long> gout308 = fvec308(gin308);

    std::vector<RotationPoly> lut309;
    std::vector<long (*)(long)> flut309;
    auto lut309idx0 = [](long I) -> long {
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
    lut309.push_back(ctx.genrate_lut(lut309idx0));
    flut309.push_back(lut309idx0);

    auto lut309idx1 = [](long I) -> long {
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
    lut309.push_back(ctx.genrate_lut(lut309idx1));
    flut309.push_back(lut309idx1);

    auto fvec309 = [flut309](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut309[i](I));
        return ret;
    };

    std::cerr << "\rLUT309   ";
    long gin309 = 1 * gout308[0] + 2 * gout223[0];
    std::vector<long> gout309 = fvec309(gin309);

    std::vector<RotationPoly> lut310;
    std::vector<long (*)(long)> flut310;
    auto lut310idx0 = [](long I) -> long {
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
    lut310.push_back(ctx.genrate_lut(lut310idx0));
    flut310.push_back(lut310idx0);

    auto lut310idx1 = [](long I) -> long {
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
    lut310.push_back(ctx.genrate_lut(lut310idx1));
    flut310.push_back(lut310idx1);

    auto fvec310 = [flut310](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut310[i](I));
        return ret;
    };

    std::cerr << "\rLUT310   ";
    long gin310 = 1 * gout219[0] + 2 * gout180[1] + 4 * gout308[1];
    std::vector<long> gout310 = fvec310(gin310);

    std::vector<RotationPoly> lut311;
    std::vector<long (*)(long)> flut311;
    auto lut311idx0 = [](long I) -> long {
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
    lut311.push_back(ctx.genrate_lut(lut311idx0));
    flut311.push_back(lut311idx0);

    auto lut311idx1 = [](long I) -> long {
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
    lut311.push_back(ctx.genrate_lut(lut311idx1));
    flut311.push_back(lut311idx1);

    auto fvec311 = [flut311](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut311[i](I));
        return ret;
    };

    std::cerr << "\rLUT311   ";
    long gin311 = 1 * gout228[0] + 2 * gout309[1] + 4 * gout310[0];
    std::vector<long> gout311 = fvec311(gin311);

    std::vector<RotationPoly> lut312;
    std::vector<long (*)(long)> flut312;
    auto lut312idx0 = [](long I) -> long {
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
    lut312.push_back(ctx.genrate_lut(lut312idx0));
    flut312.push_back(lut312idx0);

    auto fvec312 = [flut312](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut312[i](I));
        return ret;
    };

    std::cerr << "\rLUT312   ";
    long gin312 = 1 * gout304[0] + 2 * gout311[0];
    std::vector<long> gout312 = fvec312(gin312);

    std::vector<RotationPoly> lut313;
    std::vector<long (*)(long)> flut313;
    auto lut313idx0 = [](long I) -> long {
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
    lut313.push_back(ctx.genrate_lut(lut313idx0));
    flut313.push_back(lut313idx0);

    auto lut313idx1 = [](long I) -> long {
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
    lut313.push_back(ctx.genrate_lut(lut313idx1));
    flut313.push_back(lut313idx1);

    auto fvec313 = [flut313](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut313[i](I));
        return ret;
    };

    std::cerr << "\rLUT313   ";
    long gin313 = 1 * gout96[0] + 2 * gout306[1];
    std::vector<long> gout313 = fvec313(gin313);

    std::vector<RotationPoly> lut314;
    std::vector<long (*)(long)> flut314;
    auto lut314idx0 = [](long I) -> long {
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
    lut314.push_back(ctx.genrate_lut(lut314idx0));
    flut314.push_back(lut314idx0);

    auto lut314idx1 = [](long I) -> long {
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
    lut314.push_back(ctx.genrate_lut(lut314idx1));
    flut314.push_back(lut314idx1);

    auto fvec314 = [flut314](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut314[i](I));
        return ret;
    };

    std::cerr << "\rLUT314   ";
    long gin314 = 1 * gout313[0] + 2 * gout307[1] + 4 * gout208[0];
    std::vector<long> gout314 = fvec314(gin314);

    std::vector<RotationPoly> lut315;
    std::vector<long (*)(long)> flut315;
    auto lut315idx0 = [](long I) -> long {
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
    lut315.push_back(ctx.genrate_lut(lut315idx0));
    flut315.push_back(lut315idx0);

    auto lut315idx1 = [](long I) -> long {
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
    lut315.push_back(ctx.genrate_lut(lut315idx1));
    flut315.push_back(lut315idx1);

    auto fvec315 = [flut315](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut315[i](I));
        return ret;
    };

    std::cerr << "\rLUT315   ";
    long gin315 = 1 * gout220[0] + 2 * gout219[1] + 4 * gout314[1];
    std::vector<long> gout315 = fvec315(gin315);

    std::vector<RotationPoly> lut316;
    std::vector<long (*)(long)> flut316;
    auto lut316idx0 = [](long I) -> long {
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
    lut316.push_back(ctx.genrate_lut(lut316idx0));
    flut316.push_back(lut316idx0);

    auto lut316idx1 = [](long I) -> long {
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
    lut316.push_back(ctx.genrate_lut(lut316idx1));
    flut316.push_back(lut316idx1);

    auto fvec316 = [flut316](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut316[i](I));
        return ret;
    };

    std::cerr << "\rLUT316   ";
    long gin316 = 1 * gout315[0] + 2 * gout310[1] + 4 * gout314[0];
    std::vector<long> gout316 = fvec316(gin316);

    std::vector<RotationPoly> lut317;
    std::vector<long (*)(long)> flut317;
    auto lut317idx0 = [](long I) -> long {
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
    lut317.push_back(ctx.genrate_lut(lut317idx0));
    flut317.push_back(lut317idx0);

    auto lut317idx1 = [](long I) -> long {
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
    lut317.push_back(ctx.genrate_lut(lut317idx1));
    flut317.push_back(lut317idx1);

    auto fvec317 = [flut317](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut317[i](I));
        return ret;
    };

    std::cerr << "\rLUT317   ";
    long gin317 = 1 * gout316[0] + 2 * gout311[1];
    std::vector<long> gout317 = fvec317(gin317);

    std::vector<RotationPoly> lut318;
    std::vector<long (*)(long)> flut318;
    auto lut318idx0 = [](long I) -> long {
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
    lut318.push_back(ctx.genrate_lut(lut318idx0));
    flut318.push_back(lut318idx0);

    auto fvec318 = [flut318](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut318[i](I));
        return ret;
    };

    std::cerr << "\rLUT318   ";
    long gin318 = 1 * gout312[0] + 2 * gout317[0] + 4 * gout309[0];
    std::vector<long> gout318 = fvec318(gin318);

    std::vector<RotationPoly> lut319;
    std::vector<long (*)(long)> flut319;
    auto lut319idx0 = [](long I) -> long {
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
    lut319.push_back(ctx.genrate_lut(lut319idx0));
    flut319.push_back(lut319idx0);

    auto lut319idx1 = [](long I) -> long {
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
    lut319.push_back(ctx.genrate_lut(lut319idx1));
    flut319.push_back(lut319idx1);

    auto fvec319 = [flut319](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut319[i](I));
        return ret;
    };

    std::cerr << "\rLUT319   ";
    long gin319 = 1 * gout231[0] + 2 * gout313[1];
    std::vector<long> gout319 = fvec319(gin319);

    std::vector<RotationPoly> lut320;
    std::vector<long (*)(long)> flut320;
    auto lut320idx0 = [](long I) -> long {
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
    lut320.push_back(ctx.genrate_lut(lut320idx0));
    flut320.push_back(lut320idx0);

    auto lut320idx1 = [](long I) -> long {
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
    lut320.push_back(ctx.genrate_lut(lut320idx1));
    flut320.push_back(lut320idx1);

    auto fvec320 = [flut320](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut320[i](I));
        return ret;
    };

    std::cerr << "\rLUT320   ";
    long gin320 = 1 * gout254[0] + 2 * gout209[1] + 4 * gout231[1];
    std::vector<long> gout320 = fvec320(gin320);

    std::vector<RotationPoly> lut321;
    std::vector<long (*)(long)> flut321;
    auto lut321idx0 = [](long I) -> long {
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
    lut321.push_back(ctx.genrate_lut(lut321idx0));
    flut321.push_back(lut321idx0);

    auto lut321idx1 = [](long I) -> long {
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
    lut321.push_back(ctx.genrate_lut(lut321idx1));
    flut321.push_back(lut321idx1);

    auto fvec321 = [flut321](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut321[i](I));
        return ret;
    };

    std::cerr << "\rLUT321   ";
    long gin321 = 1 * gout320[0] + 2 * gout220[1] + 4 * gout319[1];
    std::vector<long> gout321 = fvec321(gin321);

    std::vector<RotationPoly> lut322;
    std::vector<long (*)(long)> flut322;
    auto lut322idx0 = [](long I) -> long {
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
    lut322.push_back(ctx.genrate_lut(lut322idx0));
    flut322.push_back(lut322idx0);

    auto lut322idx1 = [](long I) -> long {
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
    lut322.push_back(ctx.genrate_lut(lut322idx1));
    flut322.push_back(lut322idx1);

    auto fvec322 = [flut322](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut322[i](I));
        return ret;
    };

    std::cerr << "\rLUT322   ";
    long gin322 = 1 * gout321[0] + 2 * gout315[1] + 4 * gout319[0];
    std::vector<long> gout322 = fvec322(gin322);

    std::vector<RotationPoly> lut323;
    std::vector<long (*)(long)> flut323;
    auto lut323idx0 = [](long I) -> long {
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
    lut323.push_back(ctx.genrate_lut(lut323idx0));
    flut323.push_back(lut323idx0);

    auto lut323idx1 = [](long I) -> long {
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
    lut323.push_back(ctx.genrate_lut(lut323idx1));
    flut323.push_back(lut323idx1);

    auto fvec323 = [flut323](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut323[i](I));
        return ret;
    };

    std::cerr << "\rLUT323   ";
    long gin323 = 1 * gout322[0] + 2 * gout316[1];
    std::vector<long> gout323 = fvec323(gin323);

    std::vector<RotationPoly> lut324;
    std::vector<long (*)(long)> flut324;
    auto lut324idx0 = [](long I) -> long {
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
    lut324.push_back(ctx.genrate_lut(lut324idx0));
    flut324.push_back(lut324idx0);

    auto fvec324 = [flut324](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut324[i](I));
        return ret;
    };

    std::cerr << "\rLUT324   ";
    long gin324 = 1 * gout323[0] + 2 * gout317[1];
    std::vector<long> gout324 = fvec324(gin324);

    std::vector<RotationPoly> lut325;
    std::vector<long (*)(long)> flut325;
    auto lut325idx0 = [](long I) -> long {
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
    lut325.push_back(ctx.genrate_lut(lut325idx0));
    flut325.push_back(lut325idx0);

    auto fvec325 = [flut325](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut325[i](I));
        return ret;
    };

    std::cerr << "\rLUT325   ";
    long gin325 = 1 * ct_y5 + 2 * ct_x3;
    std::vector<long> gout325 = fvec325(gin325);

    std::vector<RotationPoly> lut326;
    std::vector<long (*)(long)> flut326;
    auto lut326idx0 = [](long I) -> long {
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
    lut326.push_back(ctx.genrate_lut(lut326idx0));
    flut326.push_back(lut326idx0);

    auto lut326idx1 = [](long I) -> long {
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
    lut326.push_back(ctx.genrate_lut(lut326idx1));
    flut326.push_back(lut326idx1);

    auto fvec326 = [flut326](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut326[i](I));
        return ret;
    };

    std::cerr << "\rLUT326   ";
    long gin326 = 1 * gout171[0] + 2 * gout325[0] + 4 * gout40[0];
    std::vector<long> gout326 = fvec326(gin326);

    std::vector<RotationPoly> lut327;
    std::vector<long (*)(long)> flut327;
    auto lut327idx0 = [](long I) -> long {
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
    lut327.push_back(ctx.genrate_lut(lut327idx0));
    flut327.push_back(lut327idx0);

    auto lut327idx1 = [](long I) -> long {
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
    lut327.push_back(ctx.genrate_lut(lut327idx1));
    flut327.push_back(lut327idx1);

    auto fvec327 = [flut327](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut327[i](I));
        return ret;
    };

    std::cerr << "\rLUT327   ";
    long gin327 = 1 * gout108[0] + 2 * gout230[1] + 4 * gout326[0];
    std::vector<long> gout327 = fvec327(gin327);

    std::vector<RotationPoly> lut328;
    std::vector<long (*)(long)> flut328;
    auto lut328idx0 = [](long I) -> long {
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
    lut328.push_back(ctx.genrate_lut(lut328idx0));
    flut328.push_back(lut328idx0);

    auto lut328idx1 = [](long I) -> long {
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
    lut328.push_back(ctx.genrate_lut(lut328idx1));
    flut328.push_back(lut328idx1);

    auto fvec328 = [flut328](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut328[i](I));
        return ret;
    };

    std::cerr << "\rLUT328   ";
    long gin328 = 1 * gout327[0] + 2 * gout96[1];
    std::vector<long> gout328 = fvec328(gin328);

    std::vector<RotationPoly> lut329;
    std::vector<long (*)(long)> flut329;
    auto lut329idx0 = [](long I) -> long {
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
    lut329.push_back(ctx.genrate_lut(lut329idx0));
    flut329.push_back(lut329idx0);

    auto lut329idx1 = [](long I) -> long {
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
    lut329.push_back(ctx.genrate_lut(lut329idx1));
    flut329.push_back(lut329idx1);

    auto fvec329 = [flut329](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut329[i](I));
        return ret;
    };

    std::cerr << "\rLUT329   ";
    long gin329 = 1 * gout139[0] + 2 * gout253[1] + 4 * gout326[1];
    std::vector<long> gout329 = fvec329(gin329);

    std::vector<RotationPoly> lut330;
    std::vector<long (*)(long)> flut330;
    auto lut330idx0 = [](long I) -> long {
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
    lut330.push_back(ctx.genrate_lut(lut330idx0));
    flut330.push_back(lut330idx0);

    auto lut330idx1 = [](long I) -> long {
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
    lut330.push_back(ctx.genrate_lut(lut330idx1));
    flut330.push_back(lut330idx1);

    auto fvec330 = [flut330](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut330[i](I));
        return ret;
    };

    std::cerr << "\rLUT330   ";
    long gin330 = 1 * gout329[0] + 2 * gout254[1] + 4 * gout327[1];
    std::vector<long> gout330 = fvec330(gin330);

    std::vector<RotationPoly> lut331;
    std::vector<long (*)(long)> flut331;
    auto lut331idx0 = [](long I) -> long {
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
    lut331.push_back(ctx.genrate_lut(lut331idx0));
    flut331.push_back(lut331idx0);

    auto lut331idx1 = [](long I) -> long {
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
    lut331.push_back(ctx.genrate_lut(lut331idx1));
    flut331.push_back(lut331idx1);

    auto fvec331 = [flut331](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut331[i](I));
        return ret;
    };

    std::cerr << "\rLUT331   ";
    long gin331 = 1 * gout330[0] + 2 * gout320[1] + 4 * gout328[1];
    std::vector<long> gout331 = fvec331(gin331);

    std::vector<RotationPoly> lut332;
    std::vector<long (*)(long)> flut332;
    auto lut332idx0 = [](long I) -> long {
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
    lut332.push_back(ctx.genrate_lut(lut332idx0));
    flut332.push_back(lut332idx0);

    auto lut332idx1 = [](long I) -> long {
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
    lut332.push_back(ctx.genrate_lut(lut332idx1));
    flut332.push_back(lut332idx1);

    auto fvec332 = [flut332](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut332[i](I));
        return ret;
    };

    std::cerr << "\rLUT332   ";
    long gin332 = 1 * gout331[0] + 2 * gout321[1] + 4 * gout328[0];
    std::vector<long> gout332 = fvec332(gin332);

    std::vector<RotationPoly> lut333;
    std::vector<long (*)(long)> flut333;
    auto lut333idx0 = [](long I) -> long {
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
    lut333.push_back(ctx.genrate_lut(lut333idx0));
    flut333.push_back(lut333idx0);

    auto lut333idx1 = [](long I) -> long {
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
    lut333.push_back(ctx.genrate_lut(lut333idx1));
    flut333.push_back(lut333idx1);

    auto fvec333 = [flut333](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut333[i](I));
        return ret;
    };

    std::cerr << "\rLUT333   ";
    long gin333 = 1 * gout332[0] + 2 * gout322[1];
    std::vector<long> gout333 = fvec333(gin333);

    std::vector<RotationPoly> lut334;
    std::vector<long (*)(long)> flut334;
    auto lut334idx0 = [](long I) -> long {
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
    lut334.push_back(ctx.genrate_lut(lut334idx0));
    flut334.push_back(lut334idx0);

    auto lut334idx1 = [](long I) -> long {
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
    lut334.push_back(ctx.genrate_lut(lut334idx1));
    flut334.push_back(lut334idx1);

    auto fvec334 = [flut334](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut334[i](I));
        return ret;
    };

    std::cerr << "\rLUT334   ";
    long gin334 = 1 * gout333[0] + 2 * gout323[1];
    std::vector<long> gout334 = fvec334(gin334);

    std::vector<RotationPoly> lut335;
    std::vector<long (*)(long)> flut335;
    auto lut335idx0 = [](long I) -> long {
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
    lut335.push_back(ctx.genrate_lut(lut335idx0));
    flut335.push_back(lut335idx0);

    auto lut335idx1 = [](long I) -> long {
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
    lut335.push_back(ctx.genrate_lut(lut335idx1));
    flut335.push_back(lut335idx1);

    auto fvec335 = [flut335](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut335[i](I));
        return ret;
    };

    std::cerr << "\rLUT335   ";
    long gin335 = 1 * gout232[0] + 2 * gout329[1] + 4 * gout191[1];
    std::vector<long> gout335 = fvec335(gin335);

    std::vector<RotationPoly> lut336;
    std::vector<long (*)(long)> flut336;
    auto lut336idx0 = [](long I) -> long {
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
    lut336.push_back(ctx.genrate_lut(lut336idx0));
    flut336.push_back(lut336idx0);

    auto lut336idx1 = [](long I) -> long {
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
    lut336.push_back(ctx.genrate_lut(lut336idx1));
    flut336.push_back(lut336idx1);

    auto fvec336 = [flut336](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut336[i](I));
        return ret;
    };

    std::cerr << "\rLUT336   ";
    long gin336 = 1 * gout335[0] + 2 * gout330[1] + 4 * gout192[1];
    std::vector<long> gout336 = fvec336(gin336);

    std::vector<RotationPoly> lut337;
    std::vector<long (*)(long)> flut337;
    auto lut337idx0 = [](long I) -> long {
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
    lut337.push_back(ctx.genrate_lut(lut337idx0));
    flut337.push_back(lut337idx0);

    auto lut337idx1 = [](long I) -> long {
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
    lut337.push_back(ctx.genrate_lut(lut337idx1));
    flut337.push_back(lut337idx1);

    auto fvec337 = [flut337](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut337[i](I));
        return ret;
    };

    std::cerr << "\rLUT337   ";
    long gin337 = 1 * gout336[0] + 2 * gout331[1] + 4 * gout192[0];
    std::vector<long> gout337 = fvec337(gin337);

    std::vector<RotationPoly> lut338;
    std::vector<long (*)(long)> flut338;
    auto lut338idx0 = [](long I) -> long {
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
    lut338.push_back(ctx.genrate_lut(lut338idx0));
    flut338.push_back(lut338idx0);

    auto lut338idx1 = [](long I) -> long {
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
    lut338.push_back(ctx.genrate_lut(lut338idx1));
    flut338.push_back(lut338idx1);

    auto fvec338 = [flut338](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut338[i](I));
        return ret;
    };

    std::cerr << "\rLUT338   ";
    long gin338 = 1 * gout337[0] + 2 * gout332[1];
    std::vector<long> gout338 = fvec338(gin338);

    std::vector<RotationPoly> lut339;
    std::vector<long (*)(long)> flut339;
    auto lut339idx0 = [](long I) -> long {
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
    lut339.push_back(ctx.genrate_lut(lut339idx0));
    flut339.push_back(lut339idx0);

    auto lut339idx1 = [](long I) -> long {
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
    lut339.push_back(ctx.genrate_lut(lut339idx1));
    flut339.push_back(lut339idx1);

    auto fvec339 = [flut339](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut339[i](I));
        return ret;
    };

    std::cerr << "\rLUT339   ";
    long gin339 = 1 * gout338[0] + 2 * gout333[1];
    std::vector<long> gout339 = fvec339(gin339);

    std::vector<RotationPoly> lut340;
    std::vector<long (*)(long)> flut340;
    auto lut340idx0 = [](long I) -> long {
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
    lut340.push_back(ctx.genrate_lut(lut340idx0));
    flut340.push_back(lut340idx0);

    auto lut340idx1 = [](long I) -> long {
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
    lut340.push_back(ctx.genrate_lut(lut340idx1));
    flut340.push_back(lut340idx1);

    auto fvec340 = [flut340](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut340[i](I));
        return ret;
    };

    std::cerr << "\rLUT340   ";
    long gin340 = 1 * gout233[0] + 2 * gout335[1] + 4 * gout121[0];
    std::vector<long> gout340 = fvec340(gin340);

    std::vector<RotationPoly> lut341;
    std::vector<long (*)(long)> flut341;
    auto lut341idx0 = [](long I) -> long {
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
    lut341.push_back(ctx.genrate_lut(lut341idx0));
    flut341.push_back(lut341idx0);

    auto lut341idx1 = [](long I) -> long {
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
    lut341.push_back(ctx.genrate_lut(lut341idx1));
    flut341.push_back(lut341idx1);

    auto fvec341 = [flut341](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut341[i](I));
        return ret;
    };

    std::cerr << "\rLUT341   ";
    long gin341 = 1 * gout340[0] + 2 * gout336[1];
    std::vector<long> gout341 = fvec341(gin341);

    std::vector<RotationPoly> lut342;
    std::vector<long (*)(long)> flut342;
    auto lut342idx0 = [](long I) -> long {
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
    lut342.push_back(ctx.genrate_lut(lut342idx0));
    flut342.push_back(lut342idx0);

    auto lut342idx1 = [](long I) -> long {
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
    lut342.push_back(ctx.genrate_lut(lut342idx1));
    flut342.push_back(lut342idx1);

    auto fvec342 = [flut342](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut342[i](I));
        return ret;
    };

    std::cerr << "\rLUT342   ";
    long gin342 = 1 * gout341[0] + 2 * gout337[1];
    std::vector<long> gout342 = fvec342(gin342);

    std::vector<RotationPoly> lut343;
    std::vector<long (*)(long)> flut343;
    auto lut343idx0 = [](long I) -> long {
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
    lut343.push_back(ctx.genrate_lut(lut343idx0));
    flut343.push_back(lut343idx0);

    auto lut343idx1 = [](long I) -> long {
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
    lut343.push_back(ctx.genrate_lut(lut343idx1));
    flut343.push_back(lut343idx1);

    auto fvec343 = [flut343](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut343[i](I));
        return ret;
    };

    std::cerr << "\rLUT343   ";
    long gin343 = 1 * gout342[0] + 2 * gout338[1];
    std::vector<long> gout343 = fvec343(gin343);

    std::vector<RotationPoly> lut344;
    std::vector<long (*)(long)> flut344;
    auto lut344idx0 = [](long I) -> long {
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
    lut344.push_back(ctx.genrate_lut(lut344idx0));
    flut344.push_back(lut344idx0);

    auto lut344idx1 = [](long I) -> long {
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
    lut344.push_back(ctx.genrate_lut(lut344idx1));
    flut344.push_back(lut344idx1);

    auto fvec344 = [flut344](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut344[i](I));
        return ret;
    };

    std::cerr << "\rLUT344   ";
    long gin344 = 1 * gout234[0] + 2 * gout340[1];
    std::vector<long> gout344 = fvec344(gin344);

    std::vector<RotationPoly> lut345;
    std::vector<long (*)(long)> flut345;
    auto lut345idx0 = [](long I) -> long {
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
    lut345.push_back(ctx.genrate_lut(lut345idx0));
    flut345.push_back(lut345idx0);

    auto lut345idx1 = [](long I) -> long {
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
    lut345.push_back(ctx.genrate_lut(lut345idx1));
    flut345.push_back(lut345idx1);

    auto fvec345 = [flut345](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut345[i](I));
        return ret;
    };

    std::cerr << "\rLUT345   ";
    long gin345 = 1 * gout344[0] + 2 * gout341[1];
    std::vector<long> gout345 = fvec345(gin345);

    std::vector<RotationPoly> lut346;
    std::vector<long (*)(long)> flut346;
    auto lut346idx0 = [](long I) -> long {
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
    lut346.push_back(ctx.genrate_lut(lut346idx0));
    flut346.push_back(lut346idx0);

    auto lut346idx1 = [](long I) -> long {
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
    lut346.push_back(ctx.genrate_lut(lut346idx1));
    flut346.push_back(lut346idx1);

    auto fvec346 = [flut346](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut346[i](I));
        return ret;
    };

    std::cerr << "\rLUT346   ";
    long gin346 = 1 * gout345[0] + 2 * gout342[1];
    std::vector<long> gout346 = fvec346(gin346);

    std::vector<RotationPoly> lut347;
    std::vector<long (*)(long)> flut347;
    auto lut347idx0 = [](long I) -> long {
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
    lut347.push_back(ctx.genrate_lut(lut347idx0));
    flut347.push_back(lut347idx0);

    auto lut347idx1 = [](long I) -> long {
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
    lut347.push_back(ctx.genrate_lut(lut347idx1));
    flut347.push_back(lut347idx1);

    auto fvec347 = [flut347](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut347[i](I));
        return ret;
    };

    std::cerr << "\rLUT347   ";
    long gin347 = 1 * gout235[0] + 2 * gout344[1];
    std::vector<long> gout347 = fvec347(gin347);

    std::vector<RotationPoly> lut348;
    std::vector<long (*)(long)> flut348;
    auto lut348idx0 = [](long I) -> long {
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
    lut348.push_back(ctx.genrate_lut(lut348idx0));
    flut348.push_back(lut348idx0);

    auto fvec348 = [flut348](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut348[i](I));
        return ret;
    };

    std::cerr << "\rLUT348   ";
    long gin348 = 1 * gout347[0] + 2 * gout345[1];
    std::vector<long> gout348 = fvec348(gin348);

    std::vector<RotationPoly> lut349;
    std::vector<long (*)(long)> flut349;
    auto lut349idx0 = [](long I) -> long {
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
    lut349.push_back(ctx.genrate_lut(lut349idx0));
    flut349.push_back(lut349idx0);

    auto fvec349 = [flut349](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut349[i](I));
        return ret;
    };

    std::cerr << "\rLUT349   ";
    long gin349 = 1 * gout347[1] + 2 * gout291[0];
    std::vector<long> gout349 = fvec349(gin349);

    std::vector<RotationPoly> lut350;
    std::vector<long (*)(long)> flut350;
    auto lut350idx0 = [](long I) -> long {
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
    lut350.push_back(ctx.genrate_lut(lut350idx0));
    flut350.push_back(lut350idx0);

    auto fvec350 = [flut350](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut350[i](I));
        return ret;
    };

    std::cerr << "\rLUT350   ";
    long gin350 = 1 * gout349[0] + 2 * gout348[0];
    std::vector<long> gout350 = fvec350(gin350);

    std::vector<RotationPoly> lut351;
    std::vector<long (*)(long)> flut351;
    auto lut351idx0 = [](long I) -> long {
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
    lut351.push_back(ctx.genrate_lut(lut351idx0));
    flut351.push_back(lut351idx0);

    auto lut351idx1 = [](long I) -> long {
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
    lut351.push_back(ctx.genrate_lut(lut351idx1));
    flut351.push_back(lut351idx1);

    auto fvec351 = [flut351](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut351[i](I));
        return ret;
    };

    std::cerr << "\rLUT351   ";
    long gin351 = 1 * gout236[0] + 2 * gout347[1];
    std::vector<long> gout351 = fvec351(gin351);

    std::vector<RotationPoly> lut352;
    std::vector<long (*)(long)> flut352;
    auto lut352idx0 = [](long I) -> long {
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
    lut352.push_back(ctx.genrate_lut(lut352idx0));
    flut352.push_back(lut352idx0);

    auto fvec352 = [flut352](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut352[i](I));
        return ret;
    };

    std::cerr << "\rLUT352   ";
    long gin352 = 1 * gout347[0] + 2 * gout345[1] + 4 * gout351[0];
    std::vector<long> gout352 = fvec352(gin352);

    std::vector<RotationPoly> lut353;
    std::vector<long (*)(long)> flut353;
    auto lut353idx0 = [](long I) -> long {
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
    lut353.push_back(ctx.genrate_lut(lut353idx0));
    flut353.push_back(lut353idx0);

    auto lut353idx1 = [](long I) -> long {
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
    lut353.push_back(ctx.genrate_lut(lut353idx1));
    flut353.push_back(lut353idx1);

    auto fvec353 = [flut353](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut353[i](I));
        return ret;
    };

    std::cerr << "\rLUT353   ";
    long gin353 = 1 * gout350[0] + 2 * gout352[0] + 4 * gout346[1];
    std::vector<long> gout353 = fvec353(gin353);

    std::vector<RotationPoly> lut354;
    std::vector<long (*)(long)> flut354;
    auto lut354idx0 = [](long I) -> long {
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
    lut354.push_back(ctx.genrate_lut(lut354idx0));
    flut354.push_back(lut354idx0);

    auto lut354idx1 = [](long I) -> long {
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
    lut354.push_back(ctx.genrate_lut(lut354idx1));
    flut354.push_back(lut354idx1);

    auto fvec354 = [flut354](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut354[i](I));
        return ret;
    };

    std::cerr << "\rLUT354   ";
    long gin354 = 1 * gout353[0] + 2 * gout346[0] + 4 * gout343[1];
    std::vector<long> gout354 = fvec354(gin354);

    std::vector<RotationPoly> lut355;
    std::vector<long (*)(long)> flut355;
    auto lut355idx0 = [](long I) -> long {
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
    lut355.push_back(ctx.genrate_lut(lut355idx0));
    flut355.push_back(lut355idx0);

    auto lut355idx1 = [](long I) -> long {
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
    lut355.push_back(ctx.genrate_lut(lut355idx1));
    flut355.push_back(lut355idx1);

    auto fvec355 = [flut355](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut355[i](I));
        return ret;
    };

    std::cerr << "\rLUT355   ";
    long gin355 = 1 * gout343[0] + 2 * gout354[0] + 4 * gout339[1];
    std::vector<long> gout355 = fvec355(gin355);

    std::vector<RotationPoly> lut356;
    std::vector<long (*)(long)> flut356;
    auto lut356idx0 = [](long I) -> long {
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
    lut356.push_back(ctx.genrate_lut(lut356idx0));
    flut356.push_back(lut356idx0);

    auto lut356idx1 = [](long I) -> long {
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
    lut356.push_back(ctx.genrate_lut(lut356idx1));
    flut356.push_back(lut356idx1);

    auto fvec356 = [flut356](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut356[i](I));
        return ret;
    };

    std::cerr << "\rLUT356   ";
    long gin356 = 1 * gout355[0] + 2 * gout339[0] + 4 * gout334[1];
    std::vector<long> gout356 = fvec356(gin356);

    std::vector<RotationPoly> lut357;
    std::vector<long (*)(long)> flut357;
    auto lut357idx0 = [](long I) -> long {
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
    lut357.push_back(ctx.genrate_lut(lut357idx0));
    flut357.push_back(lut357idx0);

    auto lut357idx1 = [](long I) -> long {
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
    lut357.push_back(ctx.genrate_lut(lut357idx1));
    flut357.push_back(lut357idx1);

    auto fvec357 = [flut357](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut357[i](I));
        return ret;
    };

    std::cerr << "\rLUT357   ";
    long gin357 = 1 * gout334[0] + 2 * gout356[0] + 4 * gout324[0];
    std::vector<long> gout357 = fvec357(gin357);

    std::vector<RotationPoly> lut358;
    std::vector<long (*)(long)> flut358;
    auto lut358idx0 = [](long I) -> long {
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
    lut358.push_back(ctx.genrate_lut(lut358idx0));
    flut358.push_back(lut358idx0);

    auto fvec358 = [flut358](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut358[i](I));
        return ret;
    };

    std::cerr << "\rLUT358   ";
    long gin358 = 1 * gout323[0] + 2 * gout317[1] + 4 * gout357[0];
    std::vector<long> gout358 = fvec358(gin358);

    std::vector<RotationPoly> lut359;
    std::vector<long (*)(long)> flut359;
    auto lut359idx0 = [](long I) -> long {
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
    lut359.push_back(ctx.genrate_lut(lut359idx0));
    flut359.push_back(lut359idx0);

    auto fvec359 = [flut359](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut359[i](I));
        return ret;
    };

    std::cerr << "\rLUT359   ";
    long gin359 = 1 * gout358[0] + 2 * gout318[0] + 4 * gout157[0];
    std::vector<long> gout359 = fvec359(gin359);

    std::vector<RotationPoly> lut360;
    std::vector<long (*)(long)> flut360;
    auto lut360idx0 = [](long I) -> long {
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
    lut360.push_back(ctx.genrate_lut(lut360idx0));
    flut360.push_back(lut360idx0);

    auto fvec360 = [flut360](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut360[i](I));
        return ret;
    };

    std::cerr << "\rLUT360   ";
    long gin360 = 1 * gout359[0] + 2 * gout278[0] + 4 * gout195[0];
    std::vector<long> gout360 = fvec360(gin360);

    std::vector<RotationPoly> lut361;
    std::vector<long (*)(long)> flut361;
    auto lut361idx0 = [](long I) -> long {
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
    lut361.push_back(ctx.genrate_lut(lut361idx0));
    flut361.push_back(lut361idx0);

    auto fvec361 = [flut361](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut361[i](I));
        return ret;
    };

    std::cerr << "\rLUT361   ";
    long gin361 = 1 * gout357[1] + 2 * gout324[0] + 4 * gout157[0];
    std::vector<long> gout361 = fvec361(gin361);

    std::vector<RotationPoly> lut362;
    std::vector<long (*)(long)> flut362;
    auto lut362idx0 = [](long I) -> long {
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
    lut362.push_back(ctx.genrate_lut(lut362idx0));
    flut362.push_back(lut362idx0);

    auto fvec362 = [flut362](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut362[i](I));
        return ret;
    };

    std::cerr << "\rLUT362   ";
    long gin362 = 1 * gout361[0] + 2 * gout276[0] + 4 * gout195[0];
    std::vector<long> gout362 = fvec362(gin362);

    std::vector<RotationPoly> lut363;
    std::vector<long (*)(long)> flut363;
    auto lut363idx0 = [](long I) -> long {
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
    lut363.push_back(ctx.genrate_lut(lut363idx0));
    flut363.push_back(lut363idx0);

    auto fvec363 = [flut363](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut363[i](I));
        return ret;
    };

    std::cerr << "\rLUT363   ";
    long gin363 = 1 * gout356[1] + 2 * gout334[1] + 4 * gout157[0];
    std::vector<long> gout363 = fvec363(gin363);

    std::vector<RotationPoly> lut364;
    std::vector<long (*)(long)> flut364;
    auto lut364idx0 = [](long I) -> long {
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
    lut364.push_back(ctx.genrate_lut(lut364idx0));
    flut364.push_back(lut364idx0);

    auto fvec364 = [flut364](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut364[i](I));
        return ret;
    };

    std::cerr << "\rLUT364   ";
    long gin364 = 1 * gout363[0] + 2 * gout273[0] + 4 * gout195[0];
    std::vector<long> gout364 = fvec364(gin364);

    std::vector<RotationPoly> lut365;
    std::vector<long (*)(long)> flut365;
    auto lut365idx0 = [](long I) -> long {
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
    lut365.push_back(ctx.genrate_lut(lut365idx0));
    flut365.push_back(lut365idx0);

    auto fvec365 = [flut365](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut365[i](I));
        return ret;
    };

    std::cerr << "\rLUT365   ";
    long gin365 = 1 * gout355[1] + 2 * gout339[1] + 4 * gout157[0];
    std::vector<long> gout365 = fvec365(gin365);

    std::vector<RotationPoly> lut366;
    std::vector<long (*)(long)> flut366;
    auto lut366idx0 = [](long I) -> long {
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
    lut366.push_back(ctx.genrate_lut(lut366idx0));
    flut366.push_back(lut366idx0);

    auto fvec366 = [flut366](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut366[i](I));
        return ret;
    };

    std::cerr << "\rLUT366   ";
    long gin366 = 1 * gout365[0] + 2 * gout271[0] + 4 * gout195[0];
    std::vector<long> gout366 = fvec366(gin366);

    std::vector<RotationPoly> lut367;
    std::vector<long (*)(long)> flut367;
    auto lut367idx0 = [](long I) -> long {
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
    lut367.push_back(ctx.genrate_lut(lut367idx0));
    flut367.push_back(lut367idx0);

    auto fvec367 = [flut367](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut367[i](I));
        return ret;
    };

    std::cerr << "\rLUT367   ";
    long gin367 = 1 * gout354[1] + 2 * gout343[1] + 4 * gout157[0];
    std::vector<long> gout367 = fvec367(gin367);

    std::vector<RotationPoly> lut368;
    std::vector<long (*)(long)> flut368;
    auto lut368idx0 = [](long I) -> long {
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
    lut368.push_back(ctx.genrate_lut(lut368idx0));
    flut368.push_back(lut368idx0);

    auto fvec368 = [flut368](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut368[i](I));
        return ret;
    };

    std::cerr << "\rLUT368   ";
    long gin368 = 1 * gout367[0] + 2 * gout268[0] + 4 * gout195[0];
    std::vector<long> gout368 = fvec368(gin368);

    std::vector<RotationPoly> lut369;
    std::vector<long (*)(long)> flut369;
    auto lut369idx0 = [](long I) -> long {
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
    lut369.push_back(ctx.genrate_lut(lut369idx0));
    flut369.push_back(lut369idx0);

    auto fvec369 = [flut369](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut369[i](I));
        return ret;
    };

    std::cerr << "\rLUT369   ";
    long gin369 = 1 * gout353[1] + 2 * gout346[1] + 4 * gout157[0];
    std::vector<long> gout369 = fvec369(gin369);

    std::vector<RotationPoly> lut370;
    std::vector<long (*)(long)> flut370;
    auto lut370idx0 = [](long I) -> long {
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
    lut370.push_back(ctx.genrate_lut(lut370idx0));
    flut370.push_back(lut370idx0);

    auto fvec370 = [flut370](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut370[i](I));
        return ret;
    };

    std::cerr << "\rLUT370   ";
    long gin370 = 1 * gout369[0] + 2 * gout266[0] + 4 * gout195[0];
    std::vector<long> gout370 = fvec370(gin370);

    std::vector<RotationPoly> lut371;
    std::vector<long (*)(long)> flut371;
    auto lut371idx0 = [](long I) -> long {
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
    lut371.push_back(ctx.genrate_lut(lut371idx0));
    flut371.push_back(lut371idx0);

    auto fvec371 = [flut371](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut371[i](I));
        return ret;
    };

    std::cerr << "\rLUT371   ";
    long gin371 = 1 * gout351[0] + 2 * gout349[0];
    std::vector<long> gout371 = fvec371(gin371);

    std::vector<RotationPoly> lut372;
    std::vector<long (*)(long)> flut372;
    auto lut372idx0 = [](long I) -> long {
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
    lut372.push_back(ctx.genrate_lut(lut372idx0));
    flut372.push_back(lut372idx0);

    auto fvec372 = [flut372](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut372[i](I));
        return ret;
    };

    std::cerr << "\rLUT372   ";
    long gin372 = 1 * gout371[0] + 2 * gout348[0] + 4 * gout157[0];
    std::vector<long> gout372 = fvec372(gin372);

    std::vector<RotationPoly> lut373;
    std::vector<long (*)(long)> flut373;
    auto lut373idx0 = [](long I) -> long {
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
    lut373.push_back(ctx.genrate_lut(lut373idx0));
    flut373.push_back(lut373idx0);

    auto fvec373 = [flut373](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut373[i](I));
        return ret;
    };

    std::cerr << "\rLUT373   ";
    long gin373 = 1 * gout372[0] + 2 * gout263[0] + 4 * gout195[0];
    std::vector<long> gout373 = fvec373(gin373);

    std::vector<RotationPoly> lut374;
    std::vector<long (*)(long)> flut374;
    auto lut374idx0 = [](long I) -> long {
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
    lut374.push_back(ctx.genrate_lut(lut374idx0));
    flut374.push_back(lut374idx0);

    auto fvec374 = [flut374](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut374[i](I));
        return ret;
    };

    std::cerr << "\rLUT374   ";
    long gin374 = 1 * gout351[1] + 2 * gout291[0] + 4 * gout157[0];
    std::vector<long> gout374 = fvec374(gin374);

    std::vector<RotationPoly> lut375;
    std::vector<long (*)(long)> flut375;
    auto lut375idx0 = [](long I) -> long {
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
    lut375.push_back(ctx.genrate_lut(lut375idx0));
    flut375.push_back(lut375idx0);

    auto fvec375 = [flut375](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut375[i](I));
        return ret;
    };

    std::cerr << "\rLUT375   ";
    long gin375 = 1 * gout374[0] + 2 * gout281[0] + 4 * gout195[0];
    std::vector<long> gout375 = fvec375(gin375);

    std::cerr << "\r          \r";
    std::vector<long> out;
    out.push_back(gout198[0]); /* out0 */
    out.push_back(gout239[0]); /* out1 */
    out.push_back(gout301[0]); /* out2 */
    out.push_back(gout299[0]); /* out3 */
    out.push_back(gout297[0]); /* out4 */
    out.push_back(gout295[0]); /* out5 */
    out.push_back(gout293[0]); /* out6 */
    out.push_back(gout290[0]); /* out7 */
    out.push_back(gout375[0]); /* out8 */
    out.push_back(gout373[0]); /* out9 */
    out.push_back(gout370[0]); /* out10 */
    out.push_back(gout368[0]); /* out11 */
    out.push_back(gout366[0]); /* out12 */
    out.push_back(gout364[0]); /* out13 */
    out.push_back(gout362[0]); /* out14 */
    out.push_back(gout360[0]); /* out15 */
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
            out = compose(test_add4_lut3(ctx, i, j));
            assert(out == i + j);
            out = compose(test_add4_lut3fa(ctx, i, j));
            assert(out == i + j);
        }
    }

    /* calculator tests */
    std::cout << "[+] Testing calculator" << std::endl;
    std::cout << "[>] 0 0 0" << std::endl;
    std::cout << "exp:    1111111111111111" << std::endl;
    out = compose(test_calculator_boolean(ctx, 0, 0, 0));
    std::cout << "bool:   " << std::bitset<16>(out) << std::endl;
    out = compose(test_calculator_lut3(ctx, 0, 0, 0));
    std::cout << "lut3:   " << std::bitset<16>(out) << std::endl;
    out = compose(test_calculator_lut3fa(ctx, 0, 0, 0));
    std::cout << "lut3fa: " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 6 + 7" << std::endl;
    std::cout << "exp:    0000000000001101" << std::endl;
    out = compose(test_calculator_boolean(ctx, '+', 6, 7));
    std::cout << "bool:   " << std::bitset<16>(out) << std::endl;
    out = compose(test_calculator_lut3(ctx, '+', 6, 7));
    std::cout << "lut3:   " << std::bitset<16>(out) << std::endl;
    out = compose(test_calculator_lut3fa(ctx, '+', 6, 7));
    std::cout << "lut3fa: " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 6 - 7" << std::endl;
    std::cout << "exp:    1111111111111111" << std::endl;
    out = compose(test_calculator_boolean(ctx, '-', 6, 7));
    std::cout << "bool:   " << std::bitset<16>(out) << std::endl;
    out = compose(test_calculator_lut3(ctx, '-', 6, 7));
    std::cout << "lut3:   " << std::bitset<16>(out) << std::endl;
    out = compose(test_calculator_lut3fa(ctx, '-', 6, 7));
    std::cout << "lut3fa: " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 6 * 7" << std::endl;
    std::cout << "exp:    0000000000101010" << std::endl;
    out = compose(test_calculator_boolean(ctx, '*', 6, 7));
    std::cout << "bool:   " << std::bitset<16>(out) << std::endl;
    out = compose(test_calculator_lut3(ctx, '*', 6, 7));
    std::cout << "lut3:   " << std::bitset<16>(out) << std::endl;
    out = compose(test_calculator_lut3fa(ctx, '*', 6, 7));
    std::cout << "lut3fa: " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 0xba + 0xbe" << std::endl;
    std::cout << "exp:    0000000101111000" << std::endl;
    out = compose(test_calculator_boolean(ctx, '+', 0xba, 0xbe));
    std::cout << "bool:   " << std::bitset<16>(out) << std::endl;
    out = compose(test_calculator_lut3(ctx, '+', 0xba, 0xbe));
    std::cout << "lut3:   " << std::bitset<16>(out) << std::endl;
    out = compose(test_calculator_lut3fa(ctx, '+', 0xba, 0xbe));
    std::cout << "lut3fa: " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 0xba - 0xbe" << std::endl;
    std::cout << "exp:    1111111111111100" << std::endl;
    out = compose(test_calculator_boolean(ctx, '-', 0xba, 0xbe));
    std::cout << "bool:   " << std::bitset<16>(out) << std::endl;
    out = compose(test_calculator_lut3(ctx, '-', 0xba, 0xbe));
    std::cout << "lut3:   " << std::bitset<16>(out) << std::endl;
    out = compose(test_calculator_lut3fa(ctx, '-', 0xba, 0xbe));
    std::cout << "lut3fa: " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 0xba * 0xbe" << std::endl;
    std::cout << "exp:    1000101000001100" << std::endl;
    out = compose(test_calculator_boolean(ctx, '*', 0xba, 0xbe));
    std::cout << "bool:   " << std::bitset<16>(out) << std::endl;
    out = compose(test_calculator_lut3(ctx, '*', 0xba, 0xbe));
    std::cout << "lut3:   " << std::bitset<16>(out) << std::endl;
    out = compose(test_calculator_lut3fa(ctx, '*', 0xba, 0xbe));
    std::cout << "lut3fa: " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 0xffff + 0xffff" << std::endl;
    std::cout << "exp:    1111111111111110" << std::endl;
    out = compose(test_calculator_boolean(ctx, '+', 0xffff, 0xffff));
    std::cout << "bool:   " << std::bitset<16>(out) << std::endl;
    out = compose(test_calculator_lut3(ctx, '+', 0xffff, 0xffff));
    std::cout << "lut3:   " << std::bitset<16>(out) << std::endl;
    out = compose(test_calculator_lut3fa(ctx, '+', 0xffff, 0xffff));
    std::cout << "lut3fa: " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 0xffff - 0xffff" << std::endl;
    std::cout << "exp:    0000000000000000" << std::endl;
    out = compose(test_calculator_boolean(ctx, '-', 0xffff, 0xffff));
    std::cout << "bool:   " << std::bitset<16>(out) << std::endl;
    out = compose(test_calculator_lut3(ctx, '-', 0xffff, 0xffff));
    std::cout << "lut3:   " << std::bitset<16>(out) << std::endl;
    out = compose(test_calculator_lut3fa(ctx, '-', 0xffff, 0xffff));
    std::cout << "lut3fa: " << std::bitset<16>(out) << std::endl;

    std::cout << "[>] 0xffff * 0xffff" << std::endl;
    std::cout << "exp:    0000000000000001" << std::endl;
    out = compose(test_calculator_boolean(ctx, '*', 0xffff, 0xffff));
    std::cout << "bool:   " << std::bitset<16>(out) << std::endl;
    out = compose(test_calculator_lut3(ctx, '*', 0xffff, 0xffff));
    std::cout << "lut3:   " << std::bitset<16>(out) << std::endl;
    out = compose(test_calculator_lut3fa(ctx, '*', 0xffff, 0xffff));
    std::cout << "lut3fa: " << std::bitset<16>(out) << std::endl;

    return 0;
}
