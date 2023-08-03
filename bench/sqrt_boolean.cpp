#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_sqrt_boolean(FHEContext& ctx, uint16_t num = 0)
{
    Ciphertext ct_num0 = ctx.encrypt_public((num >> 0) & 1);
    Ciphertext ct_num1 = ctx.encrypt_public((num >> 1) & 1);
    Ciphertext ct_num2 = ctx.encrypt_public((num >> 2) & 1);
    Ciphertext ct_num3 = ctx.encrypt_public((num >> 3) & 1);
    Ciphertext ct_num4 = ctx.encrypt_public((num >> 4) & 1);
    Ciphertext ct_num5 = ctx.encrypt_public((num >> 5) & 1);
    Ciphertext ct_num6 = ctx.encrypt_public((num >> 6) & 1);
    Ciphertext ct_num7 = ctx.encrypt_public((num >> 7) & 1);
    Ciphertext ct_num8 = ctx.encrypt_public((num >> 8) & 1);
    Ciphertext ct_num9 = ctx.encrypt_public((num >> 9) & 1);
    Ciphertext ct_num10 = ctx.encrypt_public((num >> 10) & 1);
    Ciphertext ct_num11 = ctx.encrypt_public((num >> 11) & 1);
    Ciphertext ct_num12 = ctx.encrypt_public((num >> 12) & 1);
    Ciphertext ct_num13 = ctx.encrypt_public((num >> 13) & 1);
    Ciphertext ct_num14 = ctx.encrypt_public((num >> 14) & 1);
    Ciphertext ct_num15 = ctx.encrypt_public((num >> 15) & 1);

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
    Ciphertext gin0 = 2 * ct_num2 + ct_num3;
    Ciphertext gout0 = ctx.eval_lut(&gin0, nor2);
    std::cerr << "\rLUT1   ";
    Ciphertext gin1 = 2 * ct_num2 + ct_num1;
    Ciphertext gout1 = ctx.eval_lut(&gin1, nor2);
    std::cerr << "\rINV2   ";
    Ciphertext gout2 = 1 - ct_num5;

    std::cerr << "\rLUT3   ";
    Ciphertext gin3 = 2 * ct_num9 + ct_num8;
    Ciphertext gout3 = ctx.eval_lut(&gin3, nand2);
    std::cerr << "\rLUT4   ";
    Ciphertext gin4 = 2 * ct_num7 + ct_num6;
    Ciphertext gout4 = ctx.eval_lut(&gin4, or2);
    std::cerr << "\rLUT5   ";
    Ciphertext gin5 = 2 * ct_num11 + ct_num12;
    Ciphertext gout5 = ctx.eval_lut(&gin5, nor2);
    std::cerr << "\rINV6   ";
    Ciphertext gout6 = 1 - ct_num4;

    std::cerr << "\rINV7   ";
    Ciphertext gout7 = 1 - ct_num12;

    std::cerr << "\rLUT8   ";
    Ciphertext gin8 = 2 * (1 - ct_num3) + ct_num2;
    Ciphertext gout8 = ctx.eval_lut(&gin8, and2);
    std::cerr << "\rLUT9   ";
    Ciphertext gin9 = 2 * ct_num5 + ct_num4;
    Ciphertext gout9 = ctx.eval_lut(&gin9, nor2);
    std::cerr << "\rINV10   ";
    Ciphertext gout10 = 1 - ct_num10;

    std::cerr << "\rINV11   ";
    Ciphertext gout11 = 1 - ct_num9;

    std::cerr << "\rINV12   ";
    Ciphertext gout12 = 1 - ct_num11;

    std::cerr << "\rLUT13   ";
    Ciphertext gin13 = 2 * ct_num9 + ct_num8;
    Ciphertext gout13 = ctx.eval_lut(&gin13, nor2);
    std::cerr << "\rINV14   ";
    Ciphertext gout14 = 1 - ct_num0;

    std::cerr << "\rLUT15   ";
    Ciphertext gin15 = 2 * ct_num13 + ct_num12;
    Ciphertext gout15 = ctx.eval_lut(&gin15, or2);
    std::cerr << "\rINV16   ";
    Ciphertext gout16 = 1 - ct_num15;

    std::cerr << "\rLUT17   ";
    Ciphertext gin17 = 2 * (1 - ct_num14) + ct_num15;
    Ciphertext gout17 = ctx.eval_lut(&gin17, or2);
    std::cerr << "\rINV18   ";
    Ciphertext gout18 = 1 - ct_num6;

    std::cerr << "\rLUT19   ";
    Ciphertext gin19 = 2 * ct_num14 + ct_num15;
    Ciphertext gout19 = ctx.eval_lut(&gin19, nor2);
    std::cerr << "\rLUT20   ";
    Ciphertext gin20 = 2 * (1 - ct_num15) + ct_num13;
    Ciphertext gout20 = ctx.eval_lut(&gin20, and2);
    std::cerr << "\rINV21   ";
    Ciphertext gout21 = 1 - ct_num3;

    std::cerr << "\rLUT22   ";
    Ciphertext gin22 = 2 * gout6 + gout0;
    Ciphertext gout22 = ctx.eval_lut(&gin22, xnor2);
    std::cerr << "\rLUT23   ";
    Ciphertext gin23 = 2 * gout10 + gout5;
    Ciphertext gout23 = ctx.eval_lut(&gin23, nand2);
    std::cerr << "\rLUT24   ";
    Ciphertext gin24 = 2 * ct_num6 + gout9;
    Ciphertext gout24 = ctx.eval_lut(&gin24, xnor2);
    std::cerr << "\rLUT25   ";
    Ciphertext gin25 = 2 * gout14 + gout1;
    Ciphertext gout25 = ctx.eval_lut(&gin25, nand2);
    std::cerr << "\rLUT26   ";
    Ciphertext gin26 = 2 * gout19 + gout15;
    Ciphertext gout26 = ctx.eval_lut(&gin26, nand2);
    std::cerr << "\rLUT27   ";
    Ciphertext gin27 = 2 * gout7 + gout19;
    Ciphertext gout27 = ctx.eval_lut(&gin27, nand2);
    std::cerr << "\rINV28   ";
    Ciphertext gout28 = 1 - gout13;

    std::cerr << "\rLUT29   ";
    Ciphertext gin29 = 2 * ct_num12 + gout19;
    Ciphertext gout29 = ctx.eval_lut(&gin29, nand2);
    std::cerr << "\rINV30   ";
    Ciphertext gout30 = 1 - gout17;

    std::cerr << "\rLUT31   ";
    Ciphertext gin31 = 2 * gout19 + gout20;
    Ciphertext gout31 = ctx.eval_lut(&gin31, or2);
    std::cerr << "\rINV32   ";
    Ciphertext gout32 = 1 - gout26;

    std::cerr << "\rLUT33   ";
    Ciphertext gin33 = 2 * ct_num13 + gout27;
    Ciphertext gout33 = ctx.eval_lut(&gin33, and2);
    std::cerr << "\rLUT34   ";
    Ciphertext gin34 = 2 * gout29 + gout23;
    Ciphertext gout34 = ctx.eval_lut(&gin34, nand2);
    std::cerr << "\rLUT35   ";
    Ciphertext gin35 = 2 * gout17 + gout33;
    Ciphertext gout35 = ctx.eval_lut(&gin35, nand2);
    std::cerr << "\rLUT36   ";
    Ciphertext gin36 = 2 * gout35 + gout34;
    Ciphertext gout36 = ctx.eval_lut(&gin36, nand2);
    std::cerr << "\rLUT37   ";
    Ciphertext gin37 = 2 * gout36 + gout26;
    Ciphertext gout37 = ctx.eval_lut(&gin37, or2);
    std::cerr << "\rLUT38   ";
    Ciphertext gin38 = 2 * gout36 + gout31;
    Ciphertext gout38 = ctx.eval_lut(&gin38, and2);
    std::cerr << "\rLUT39   ";
    Ciphertext gin39 = 2 * gout10 + gout38;
    Ciphertext gout39 = ctx.eval_lut(&gin39, and2);
    std::cerr << "\rIMUX40  ";
    Ciphertext gin40A = 2 * gout38 + ct_num10;
    Ciphertext gout40A = ctx.eval_lut(&gin40A, and2);
    Ciphertext gin40B = 2 * gout13 + (1 - ct_num10);
    Ciphertext gout40B = ctx.eval_lut(&gin40B, and2);
    Ciphertext gout40 = gout40A + gout40B;
    std::cerr << "\rINV41   ";
    Ciphertext gout41 = 1 - gout38;

    std::cerr << "\rLUT42   ";
    Ciphertext gin42 = 2 * (1 - gout33) + gout38;
    Ciphertext gout42 = ctx.eval_lut(&gin42, or2);
    std::cerr << "\rLUT43   ";
    Ciphertext gin43 = 2 * gout12 + gout39;
    Ciphertext gout43 = ctx.eval_lut(&gin43, nand2);
    std::cerr << "\rINV44   ";
    Ciphertext gout44 = 1 - gout40;

    std::cerr << "\rLUT45   ";
    Ciphertext gin45 = 2 * ct_num11 + gout39;
    Ciphertext gout45 = ctx.eval_lut(&gin45, xnor2);
    std::cerr << "\rLUT46   ";
    Ciphertext gin46 = 2 * gout32 + gout45;
    Ciphertext gout46 = ctx.eval_lut(&gin46, or2);
    std::cerr << "\rLUT47   ";
    Ciphertext gin47 = 2 * gout43 + gout37;
    Ciphertext gout47 = ctx.eval_lut(&gin47, and2);
    std::cerr << "\rINV48   ";
    Ciphertext gout48 = 1 - gout45;

    std::cerr << "\rLUT49   ";
    Ciphertext gin49 = 2 * gout26 + gout45;
    Ciphertext gout49 = ctx.eval_lut(&gin49, xnor2);
    std::cerr << "\rLUT50   ";
    Ciphertext gin50 = 2 * ct_num12 + gout47;
    Ciphertext gout50 = ctx.eval_lut(&gin50, xnor2);
    std::cerr << "\rLUT51   ";
    Ciphertext gin51 = 2 * gout49 + gout44;
    Ciphertext gout51 = ctx.eval_lut(&gin51, nand2);
    std::cerr << "\rLUT52   ";
    Ciphertext gin52 = 2 * gout49 + gout40;
    Ciphertext gout52 = ctx.eval_lut(&gin52, xnor2);
    std::cerr << "\rLUT53   ";
    Ciphertext gin53 = 2 * gout30 + gout50;
    Ciphertext gout53 = ctx.eval_lut(&gin53, xnor2);
    std::cerr << "\rLUT54   ";
    Ciphertext gin54 = 2 * (1 - gout50) + gout42;
    Ciphertext gout54 = ctx.eval_lut(&gin54, and2);
    std::cerr << "\rLUT55   ";
    Ciphertext gin55 = 2 * gout17 + gout50;
    Ciphertext gout55 = ctx.eval_lut(&gin55, nand2);
    std::cerr << "\rLUT56   ";
    Ciphertext gin56 = 2 * gout46 + gout51;
    Ciphertext gout56 = ctx.eval_lut(&gin56, nand2);
    std::cerr << "\rLUT57   ";
    Ciphertext gin57 = 2 * gout55 + gout42;
    Ciphertext gout57 = ctx.eval_lut(&gin57, and2);
    std::cerr << "\rLUT58   ";
    Ciphertext gin58 = 2 * gout53 + gout56;
    Ciphertext gout58 = ctx.eval_lut(&gin58, nand2);
    std::cerr << "\rLUT59   ";
    Ciphertext gin59 = 2 * gout53 + gout56;
    Ciphertext gout59 = ctx.eval_lut(&gin59, xnor2);
    std::cerr << "\rLUT60   ";
    Ciphertext gin60 = 2 * gout58 + gout57;
    Ciphertext gout60 = ctx.eval_lut(&gin60, nand2);
    std::cerr << "\rLUT61   ";
    Ciphertext gin61 = 2 * gout16 + gout60;
    Ciphertext gout61 = ctx.eval_lut(&gin61, nand2);
    std::cerr << "\rLUT62   ";
    Ciphertext gin62 = 2 * gout11 + gout61;
    Ciphertext gout62 = ctx.eval_lut(&gin62, nand2);
    std::cerr << "\rINV63   ";
    Ciphertext gout63 = 1 - gout61;

    std::cerr << "\rIMUX64  ";
    Ciphertext gin64A = 2 * gout38 + gout61;
    Ciphertext gout64A = ctx.eval_lut(&gin64A, and2);
    Ciphertext gin64B = 2 * gout13 + (1 - gout61);
    Ciphertext gout64B = ctx.eval_lut(&gin64B, and2);
    Ciphertext gout64 = gout64A + gout64B;
    std::cerr << "\rIMUX65  ";
    Ciphertext gin65A = 2 * gout48 + gout61;
    Ciphertext gout65A = ctx.eval_lut(&gin65A, and2);
    Ciphertext gin65B = 2 * gout52 + (1 - gout61);
    Ciphertext gout65B = ctx.eval_lut(&gin65B, and2);
    Ciphertext gout65 = gout65A + gout65B;
    std::cerr << "\rIMUX66  ";
    Ciphertext gin66A = 2 * gout61 + ct_num8;
    Ciphertext gout66A = ctx.eval_lut(&gin66A, and2);
    Ciphertext gin66B = 2 * gout4 + (1 - ct_num8);
    Ciphertext gout66B = ctx.eval_lut(&gin66B, and2);
    Ciphertext gout66 = gout66A + gout66B;
    std::cerr << "\rIMUX67  ";
    Ciphertext gin67A = 2 * gout59 + gout63;
    Ciphertext gout67A = ctx.eval_lut(&gin67A, and2);
    Ciphertext gin67B = 2 * gout54 + (1 - gout63);
    Ciphertext gout67B = ctx.eval_lut(&gin67B, and2);
    Ciphertext gout67 = gout67A + gout67B;
    std::cerr << "\rLUT68   ";
    Ciphertext gin68 = 2 * gout17 + gout65;
    Ciphertext gout68 = ctx.eval_lut(&gin68, nand2);
    std::cerr << "\rLUT69   ";
    Ciphertext gin69 = 2 * gout30 + gout65;
    Ciphertext gout69 = ctx.eval_lut(&gin69, xnor2);
    std::cerr << "\rLUT70   ";
    Ciphertext gin70 = 2 * gout28 + gout63;
    Ciphertext gout70 = ctx.eval_lut(&gin70, and2);
    std::cerr << "\rLUT71   ";
    Ciphertext gin71 = 2 * gout10 + gout64;
    Ciphertext gout71 = ctx.eval_lut(&gin71, xnor2);
    std::cerr << "\rLUT72   ";
    Ciphertext gin72 = 2 * gout68 + gout67;
    Ciphertext gout72 = ctx.eval_lut(&gin72, and2);
    std::cerr << "\rLUT73   ";
    Ciphertext gin73 = 2 * gout70 + gout3;
    Ciphertext gout73 = ctx.eval_lut(&gin73, nand2);
    std::cerr << "\rLUT74   ";
    Ciphertext gin74 = 2 * gout26 + gout71;
    Ciphertext gout74 = ctx.eval_lut(&gin74, nand2);
    std::cerr << "\rLUT75   ";
    Ciphertext gin75 = 2 * gout32 + gout71;
    Ciphertext gout75 = ctx.eval_lut(&gin75, xnor2);
    std::cerr << "\rLUT76   ";
    Ciphertext gin76 = 2 * gout73 + gout62;
    Ciphertext gout76 = ctx.eval_lut(&gin76, and2);
    std::cerr << "\rLUT77   ";
    Ciphertext gin77 = 2 * gout73 + gout62;
    Ciphertext gout77 = ctx.eval_lut(&gin77, nand2);
    std::cerr << "\rINV78   ";
    Ciphertext gout78 = 1 - gout75;

    std::cerr << "\rLUT79   ";
    Ciphertext gin79 = 2 * gout38 + gout76;
    Ciphertext gout79 = ctx.eval_lut(&gin79, xnor2);
    std::cerr << "\rLUT80   ";
    Ciphertext gin80 = 2 * gout38 + gout77;
    Ciphertext gout80 = ctx.eval_lut(&gin80, nand2);
    std::cerr << "\rLUT81   ";
    Ciphertext gin81 = 2 * gout41 + gout76;
    Ciphertext gout81 = ctx.eval_lut(&gin81, nand2);
    std::cerr << "\rLUT82   ";
    Ciphertext gin82 = 2 * gout80 + gout66;
    Ciphertext gout82 = ctx.eval_lut(&gin82, nand2);
    std::cerr << "\rLUT83   ";
    Ciphertext gin83 = 2 * gout66 + gout79;
    Ciphertext gout83 = ctx.eval_lut(&gin83, xnor2);
    std::cerr << "\rLUT84   ";
    Ciphertext gin84 = 2 * gout81 + gout82;
    Ciphertext gout84 = ctx.eval_lut(&gin84, and2);
    std::cerr << "\rLUT85   ";
    Ciphertext gin85 = 2 * gout75 + gout84;
    Ciphertext gout85 = ctx.eval_lut(&gin85, xnor2);
    std::cerr << "\rLUT86   ";
    Ciphertext gin86 = 2 * gout78 + gout84;
    Ciphertext gout86 = ctx.eval_lut(&gin86, or2);
    std::cerr << "\rLUT87   ";
    Ciphertext gin87 = 2 * gout74 + gout86;
    Ciphertext gout87 = ctx.eval_lut(&gin87, nand2);
    std::cerr << "\rLUT88   ";
    Ciphertext gin88 = 2 * gout69 + gout87;
    Ciphertext gout88 = ctx.eval_lut(&gin88, xor2);
    std::cerr << "\rLUT89   ";
    Ciphertext gin89 = 2 * gout69 + gout87;
    Ciphertext gout89 = ctx.eval_lut(&gin89, nand2);
    std::cerr << "\rLUT90   ";
    Ciphertext gin90 = 2 * gout89 + gout72;
    Ciphertext gout90 = ctx.eval_lut(&gin90, nand2);
    std::cerr << "\rLUT91   ";
    Ciphertext gin91 = 2 * gout61 + gout90;
    Ciphertext gout91 = ctx.eval_lut(&gin91, or2);
    std::cerr << "\rLUT92   ";
    Ciphertext gin92 = 2 * gout16 + gout90;
    Ciphertext gout92 = ctx.eval_lut(&gin92, nand2);
    std::cerr << "\rIMUX93  ";
    Ciphertext gin93A = 2 * gout65 + gout92;
    Ciphertext gout93A = ctx.eval_lut(&gin93A, and2);
    Ciphertext gin93B = 2 * gout88 + (1 - gout92);
    Ciphertext gout93B = ctx.eval_lut(&gin93B, and2);
    Ciphertext gout93 = gout93A + gout93B;
    std::cerr << "\rIMUX94  ";
    Ciphertext gin94A = 2 * gout77 + gout92;
    Ciphertext gout94A = ctx.eval_lut(&gin94A, and2);
    Ciphertext gin94B = 2 * gout83 + (1 - gout92);
    Ciphertext gout94B = ctx.eval_lut(&gin94B, and2);
    Ciphertext gout94 = gout94A + gout94B;
    std::cerr << "\rLUT95   ";
    Ciphertext gin95 = 2 * (1 - gout92) + gout18;
    Ciphertext gout95 = ctx.eval_lut(&gin95, and2);
    std::cerr << "\rLUT96   ";
    Ciphertext gin96 = 2 * gout4 + gout92;
    Ciphertext gout96 = ctx.eval_lut(&gin96, or2);
    std::cerr << "\rLUT97   ";
    Ciphertext gin97 = 2 * gout18 + gout92;
    Ciphertext gout97 = ctx.eval_lut(&gin97, xnor2);
    std::cerr << "\rINV98   ";
    Ciphertext gout98 = 1 - gout92;

    std::cerr << "\rIMUX99  ";
    Ciphertext gin99A = 2 * gout71 + gout92;
    Ciphertext gout99A = ctx.eval_lut(&gin99A, and2);
    Ciphertext gin99B = 2 * gout85 + (1 - gout92);
    Ciphertext gout99B = ctx.eval_lut(&gin99B, and2);
    Ciphertext gout99 = gout99A + gout99B;
    std::cerr << "\rLUT100   ";
    Ciphertext gin100 = 2 * ct_num7 + gout95;
    Ciphertext gout100 = ctx.eval_lut(&gin100, xnor2);
    std::cerr << "\rLUT101   ";
    Ciphertext gin101 = 2 * gout32 + gout94;
    Ciphertext gout101 = ctx.eval_lut(&gin101, xnor2);
    std::cerr << "\rIMUX102  ";
    Ciphertext gin102A = 2 * gout98 + ct_num6;
    Ciphertext gout102A = ctx.eval_lut(&gin102A, and2);
    Ciphertext gin102B = 2 * gout9 + (1 - ct_num6);
    Ciphertext gout102B = ctx.eval_lut(&gin102B, and2);
    Ciphertext gout102 = gout102A + gout102B;
    std::cerr << "\rLUT103   ";
    Ciphertext gin103 = 2 * gout96 + gout91;
    Ciphertext gout103 = ctx.eval_lut(&gin103, and2);
    std::cerr << "\rLUT104   ";
    Ciphertext gin104 = 2 * gout30 + gout99;
    Ciphertext gout104 = ctx.eval_lut(&gin104, xnor2);
    std::cerr << "\rINV105   ";
    Ciphertext gout105 = 1 - gout99;

    std::cerr << "\rLUT106   ";
    Ciphertext gin106 = 2 * gout17 + gout99;
    Ciphertext gout106 = ctx.eval_lut(&gin106, nand2);
    std::cerr << "\rLUT107   ";
    Ciphertext gin107 = 2 * gout32 + gout94;
    Ciphertext gout107 = ctx.eval_lut(&gin107, or2);
    std::cerr << "\rLUT108   ";
    Ciphertext gin108 = 2 * gout63 + gout100;
    Ciphertext gout108 = ctx.eval_lut(&gin108, or2);
    std::cerr << "\rLUT109   ";
    Ciphertext gin109 = 2 * gout61 + gout100;
    Ciphertext gout109 = ctx.eval_lut(&gin109, xnor2);
    std::cerr << "\rLUT110   ";
    Ciphertext gin110 = 2 * gout109 + gout102;
    Ciphertext gout110 = ctx.eval_lut(&gin110, xnor2);
    std::cerr << "\rLUT111   ";
    Ciphertext gin111 = 2 * ct_num8 + gout103;
    Ciphertext gout111 = ctx.eval_lut(&gin111, xnor2);
    std::cerr << "\rINV112   ";
    Ciphertext gout112 = 1 - gout100;

    std::cerr << "\rINV113   ";
    Ciphertext gout113 = 1 - gout102;

    std::cerr << "\rLUT114   ";
    Ciphertext gin114 = 2 * (1 - gout93) + gout106;
    Ciphertext gout114 = ctx.eval_lut(&gin114, and2);
    std::cerr << "\rINV115   ";
    Ciphertext gout115 = 1 - gout111;

    std::cerr << "\rLUT116   ";
    Ciphertext gin116 = 2 * gout41 + gout111;
    Ciphertext gout116 = ctx.eval_lut(&gin116, nand2);
    std::cerr << "\rLUT117   ";
    Ciphertext gin117 = 2 * gout38 + gout111;
    Ciphertext gout117 = ctx.eval_lut(&gin117, xnor2);
    std::cerr << "\rLUT118   ";
    Ciphertext gin118 = 2 * gout109 + gout113;
    Ciphertext gout118 = ctx.eval_lut(&gin118, nand2);
    std::cerr << "\rLUT119   ";
    Ciphertext gin119 = 2 * gout108 + gout118;
    Ciphertext gout119 = ctx.eval_lut(&gin119, nand2);
    std::cerr << "\rLUT120   ";
    Ciphertext gin120 = 2 * gout119 + gout117;
    Ciphertext gout120 = ctx.eval_lut(&gin120, nand2);
    std::cerr << "\rLUT121   ";
    Ciphertext gin121 = 2 * gout119 + gout117;
    Ciphertext gout121 = ctx.eval_lut(&gin121, xnor2);
    std::cerr << "\rLUT122   ";
    Ciphertext gin122 = 2 * gout116 + gout120;
    Ciphertext gout122 = ctx.eval_lut(&gin122, and2);
    std::cerr << "\rLUT123   ";
    Ciphertext gin123 = 2 * gout101 + gout122;
    Ciphertext gout123 = ctx.eval_lut(&gin123, xnor2);
    std::cerr << "\rLUT124   ";
    Ciphertext gin124 = 2 * gout101 + gout122;
    Ciphertext gout124 = ctx.eval_lut(&gin124, or2);
    std::cerr << "\rLUT125   ";
    Ciphertext gin125 = 2 * gout107 + gout124;
    Ciphertext gout125 = ctx.eval_lut(&gin125, nand2);
    std::cerr << "\rLUT126   ";
    Ciphertext gin126 = 2 * gout104 + gout125;
    Ciphertext gout126 = ctx.eval_lut(&gin126, nand2);
    std::cerr << "\rLUT127   ";
    Ciphertext gin127 = 2 * gout104 + gout125;
    Ciphertext gout127 = ctx.eval_lut(&gin127, xnor2);
    std::cerr << "\rLUT128   ";
    Ciphertext gin128 = 2 * gout126 + gout114;
    Ciphertext gout128 = ctx.eval_lut(&gin128, nand2);
    std::cerr << "\rLUT129   ";
    Ciphertext gin129 = 2 * gout16 + gout128;
    Ciphertext gout129 = ctx.eval_lut(&gin129, nand2);
    std::cerr << "\rIMUX130  ";
    Ciphertext gin130A = 2 * gout94 + gout129;
    Ciphertext gout130A = ctx.eval_lut(&gin130A, and2);
    Ciphertext gin130B = 2 * gout123 + (1 - gout129);
    Ciphertext gout130B = ctx.eval_lut(&gin130B, and2);
    Ciphertext gout130 = gout130A + gout130B;
    std::cerr << "\rLUT131   ";
    Ciphertext gin131 = 2 * ct_num4 + gout129;
    Ciphertext gout131 = ctx.eval_lut(&gin131, xnor2);
    std::cerr << "\rIMUX132  ";
    Ciphertext gin132A = 2 * gout97 + gout129;
    Ciphertext gout132A = ctx.eval_lut(&gin132A, and2);
    Ciphertext gin132B = 2 * gout24 + (1 - gout129);
    Ciphertext gout132B = ctx.eval_lut(&gin132B, and2);
    Ciphertext gout132 = gout132A + gout132B;
    std::cerr << "\rINV133   ";
    Ciphertext gout133 = 1 - gout129;

    std::cerr << "\rLUT134   ";
    Ciphertext gin134 = 2 * gout129 + gout25;
    Ciphertext gout134 = ctx.eval_lut(&gin134, nand2);
    std::cerr << "\rIMUX135  ";
    Ciphertext gin135A = 2 * gout115 + gout129;
    Ciphertext gout135A = ctx.eval_lut(&gin135A, and2);
    Ciphertext gin135B = 2 * gout121 + (1 - gout129);
    Ciphertext gout135B = ctx.eval_lut(&gin135B, and2);
    Ciphertext gout135 = gout135A + gout135B;
    std::cerr << "\rIMUX136  ";
    Ciphertext gin136A = 2 * gout112 + gout129;
    Ciphertext gout136A = ctx.eval_lut(&gin136A, and2);
    Ciphertext gin136B = 2 * gout110 + (1 - gout129);
    Ciphertext gout136B = ctx.eval_lut(&gin136B, and2);
    Ciphertext gout136 = gout136A + gout136B;
    std::cerr << "\rIMUX137  ";
    Ciphertext gin137A = 2 * gout105 + gout129;
    Ciphertext gout137A = ctx.eval_lut(&gin137A, and2);
    Ciphertext gin137B = 2 * gout127 + (1 - gout129);
    Ciphertext gout137B = ctx.eval_lut(&gin137B, and2);
    Ciphertext gout137 = gout137A + gout137B;
    std::cerr << "\rLUT138   ";
    Ciphertext gin138 = 2 * gout129 + gout25;
    Ciphertext gout138 = ctx.eval_lut(&gin138, or2);
    std::cerr << "\rLUT139   ";
    Ciphertext gin139 = 2 * (1 - gout129) + gout6;
    Ciphertext gout139 = ctx.eval_lut(&gin139, and2);
    std::cerr << "\rIMUX140  ";
    Ciphertext gin140A = 2 * gout133 + ct_num4;
    Ciphertext gout140A = ctx.eval_lut(&gin140A, and2);
    Ciphertext gin140B = 2 * gout0 + (1 - ct_num4);
    Ciphertext gout140B = ctx.eval_lut(&gin140B, and2);
    Ciphertext gout140 = gout140A + gout140B;
    std::cerr << "\rLUT141   ";
    Ciphertext gin141 = 2 * gout61 + gout132;
    Ciphertext gout141 = ctx.eval_lut(&gin141, xnor2);
    std::cerr << "\rLUT142   ";
    Ciphertext gin142 = 2 * gout30 + gout130;
    Ciphertext gout142 = ctx.eval_lut(&gin142, or2);
    std::cerr << "\rLUT143   ";
    Ciphertext gin143 = 2 * gout130 + gout137;
    Ciphertext gout143 = ctx.eval_lut(&gin143, nand2);
    std::cerr << "\rLUT144   ";
    Ciphertext gin144 = 2 * gout63 + gout132;
    Ciphertext gout144 = ctx.eval_lut(&gin144, or2);
    std::cerr << "\rLUT145   ";
    Ciphertext gin145 = 2 * gout17 + gout130;
    Ciphertext gout145 = ctx.eval_lut(&gin145, xnor2);
    std::cerr << "\rLUT146   ";
    Ciphertext gin146 = 2 * gout142 + gout137;
    Ciphertext gout146 = ctx.eval_lut(&gin146, and2);
    std::cerr << "\rLUT147   ";
    Ciphertext gin147 = 2 * gout26 + gout135;
    Ciphertext gout147 = ctx.eval_lut(&gin147, xnor2);
    std::cerr << "\rLUT148   ";
    Ciphertext gin148 = 2 * gout2 + gout139;
    Ciphertext gout148 = ctx.eval_lut(&gin148, xnor2);
    std::cerr << "\rLUT149   ";
    Ciphertext gin149 = 2 * gout38 + gout136;
    Ciphertext gout149 = ctx.eval_lut(&gin149, xnor2);
    std::cerr << "\rLUT150   ";
    Ciphertext gin150 = 2 * gout41 + gout136;
    Ciphertext gout150 = ctx.eval_lut(&gin150, nand2);
    std::cerr << "\rLUT151   ";
    Ciphertext gin151 = 2 * gout32 + gout135;
    Ciphertext gout151 = ctx.eval_lut(&gin151, or2);
    std::cerr << "\rINV152   ";
    Ciphertext gout152 = 1 - gout140;

    std::cerr << "\rINV153   ";
    Ciphertext gout153 = 1 - gout141;

    std::cerr << "\rLUT154   ";
    Ciphertext gin154 = 2 * gout92 + gout148;
    Ciphertext gout154 = ctx.eval_lut(&gin154, nand2);
    std::cerr << "\rLUT155   ";
    Ciphertext gin155 = 2 * gout98 + gout148;
    Ciphertext gout155 = ctx.eval_lut(&gin155, xnor2);
    std::cerr << "\rINV156   ";
    Ciphertext gout156 = 1 - gout149;

    std::cerr << "\rLUT157   ";
    Ciphertext gin157 = 2 * gout155 + gout140;
    Ciphertext gout157 = ctx.eval_lut(&gin157, xnor2);
    std::cerr << "\rLUT158   ";
    Ciphertext gin158 = 2 * gout155 + gout152;
    Ciphertext gout158 = ctx.eval_lut(&gin158, nand2);
    std::cerr << "\rLUT159   ";
    Ciphertext gin159 = 2 * gout154 + gout158;
    Ciphertext gout159 = ctx.eval_lut(&gin159, and2);
    std::cerr << "\rLUT160   ";
    Ciphertext gin160 = 2 * gout153 + gout159;
    Ciphertext gout160 = ctx.eval_lut(&gin160, or2);
    std::cerr << "\rLUT161   ";
    Ciphertext gin161 = 2 * gout153 + gout159;
    Ciphertext gout161 = ctx.eval_lut(&gin161, xnor2);
    std::cerr << "\rLUT162   ";
    Ciphertext gin162 = 2 * gout144 + gout160;
    Ciphertext gout162 = ctx.eval_lut(&gin162, and2);
    std::cerr << "\rLUT163   ";
    Ciphertext gin163 = 2 * gout149 + gout162;
    Ciphertext gout163 = ctx.eval_lut(&gin163, xnor2);
    std::cerr << "\rLUT164   ";
    Ciphertext gin164 = 2 * gout156 + gout162;
    Ciphertext gout164 = ctx.eval_lut(&gin164, or2);
    std::cerr << "\rLUT165   ";
    Ciphertext gin165 = 2 * gout150 + gout164;
    Ciphertext gout165 = ctx.eval_lut(&gin165, nand2);
    std::cerr << "\rLUT166   ";
    Ciphertext gin166 = 2 * gout165 + gout147;
    Ciphertext gout166 = ctx.eval_lut(&gin166, nand2);
    std::cerr << "\rLUT167   ";
    Ciphertext gin167 = 2 * gout165 + gout147;
    Ciphertext gout167 = ctx.eval_lut(&gin167, xnor2);
    std::cerr << "\rLUT168   ";
    Ciphertext gin168 = 2 * gout151 + gout166;
    Ciphertext gout168 = ctx.eval_lut(&gin168, nand2);
    std::cerr << "\rLUT169   ";
    Ciphertext gin169 = 2 * gout145 + gout168;
    Ciphertext gout169 = ctx.eval_lut(&gin169, xor2);
    std::cerr << "\rLUT170   ";
    Ciphertext gin170 = 2 * gout145 + gout168;
    Ciphertext gout170 = ctx.eval_lut(&gin170, nand2);
    std::cerr << "\rLUT171   ";
    Ciphertext gin171 = 2 * gout170 + gout146;
    Ciphertext gout171 = ctx.eval_lut(&gin171, nand2);
    std::cerr << "\rLUT172   ";
    Ciphertext gin172 = 2 * gout16 + gout171;
    Ciphertext gout172 = ctx.eval_lut(&gin172, nand2);
    std::cerr << "\rIMUX173  ";
    Ciphertext gin173A = 2 * gout135 + gout172;
    Ciphertext gout173A = ctx.eval_lut(&gin173A, and2);
    Ciphertext gin173B = 2 * gout167 + (1 - gout172);
    Ciphertext gout173B = ctx.eval_lut(&gin173B, and2);
    Ciphertext gout173 = gout173A + gout173B;
    std::cerr << "\rIMUX174  ";
    Ciphertext gin174A = 2 * gout143 + gout172;
    Ciphertext gout174A = ctx.eval_lut(&gin174A, and2);
    Ciphertext gin174B = 2 * gout169 + (1 - gout172);
    Ciphertext gout174B = ctx.eval_lut(&gin174B, and2);
    Ciphertext gout174 = gout174A + gout174B;
    std::cerr << "\rIMUX175  ";
    Ciphertext gin175A = 2 * gout148 + gout172;
    Ciphertext gout175A = ctx.eval_lut(&gin175A, and2);
    Ciphertext gin175B = 2 * gout157 + (1 - gout172);
    Ciphertext gout175B = ctx.eval_lut(&gin175B, and2);
    Ciphertext gout175 = gout175A + gout175B;
    std::cerr << "\rIMUX176  ";
    Ciphertext gin176A = 2 * gout132 + gout172;
    Ciphertext gout176A = ctx.eval_lut(&gin176A, and2);
    Ciphertext gin176B = 2 * gout161 + (1 - gout172);
    Ciphertext gout176B = ctx.eval_lut(&gin176B, and2);
    Ciphertext gout176 = gout176A + gout176B;
    std::cerr << "\rINV177   ";
    Ciphertext gout177 = 1 - gout172;

    std::cerr << "\rIMUX178  ";
    Ciphertext gin178A = 2 * gout131 + gout172;
    Ciphertext gout178A = ctx.eval_lut(&gin178A, and2);
    Ciphertext gin178B = 2 * gout22 + (1 - gout172);
    Ciphertext gout178B = ctx.eval_lut(&gin178B, and2);
    Ciphertext gout178 = gout178A + gout178B;
    std::cerr << "\rLUT179   ";
    Ciphertext gin179 = 2 * gout21 + gout172;
    Ciphertext gout179 = ctx.eval_lut(&gin179, xnor2);
    std::cerr << "\rIMUX180  ";
    Ciphertext gin180A = 2 * gout136 + gout172;
    Ciphertext gout180A = ctx.eval_lut(&gin180A, and2);
    Ciphertext gin180B = 2 * gout163 + (1 - gout172);
    Ciphertext gout180B = ctx.eval_lut(&gin180B, and2);
    Ciphertext gout180 = gout180A + gout180B;
    std::cerr << "\rLUT181   ";
    Ciphertext gin181 = 2 * (1 - gout172) + gout8;
    Ciphertext gout181 = ctx.eval_lut(&gin181, and2);
    std::cerr << "\rLUT182   ";
    Ciphertext gin182 = 2 * gout61 + gout175;
    Ciphertext gout182 = ctx.eval_lut(&gin182, or2);
    std::cerr << "\rLUT183   ";
    Ciphertext gin183 = 2 * gout30 + gout173;
    Ciphertext gout183 = ctx.eval_lut(&gin183, or2);
    std::cerr << "\rLUT184   ";
    Ciphertext gin184 = 2 * gout61 + gout175;
    Ciphertext gout184 = ctx.eval_lut(&gin184, nand2);
    std::cerr << "\rLUT185   ";
    Ciphertext gin185 = 2 * gout38 + gout176;
    Ciphertext gout185 = ctx.eval_lut(&gin185, or2);
    std::cerr << "\rLUT186   ";
    Ciphertext gin186 = 2 * gout30 + gout173;
    Ciphertext gout186 = ctx.eval_lut(&gin186, nand2);
    std::cerr << "\rLUT187   ";
    Ciphertext gin187 = 2 * gout92 + gout178;
    Ciphertext gout187 = ctx.eval_lut(&gin187, or2);
    std::cerr << "\rLUT188   ";
    Ciphertext gin188 = 2 * gout92 + gout178;
    Ciphertext gout188 = ctx.eval_lut(&gin188, nand2);
    std::cerr << "\rLUT189   ";
    Ciphertext gin189 = 2 * gout26 + gout180;
    Ciphertext gout189 = ctx.eval_lut(&gin189, nand2);
    std::cerr << "\rLUT190   ";
    Ciphertext gin190 = 2 * gout38 + gout176;
    Ciphertext gout190 = ctx.eval_lut(&gin190, nand2);
    std::cerr << "\rLUT191   ";
    Ciphertext gin191 = 2 * gout134 + gout179;
    Ciphertext gout191 = ctx.eval_lut(&gin191, nand2);
    std::cerr << "\rLUT192   ";
    Ciphertext gin192 = 2 * gout26 + gout180;
    Ciphertext gout192 = ctx.eval_lut(&gin192, or2);
    std::cerr << "\rLUT193   ";
    Ciphertext gin193 = 2 * (1 - gout181) + gout138;
    Ciphertext gout193 = ctx.eval_lut(&gin193, and2);
    std::cerr << "\rLUT194   ";
    Ciphertext gin194 = 2 * gout183 + (1 - gout174);
    Ciphertext gout194 = ctx.eval_lut(&gin194, and2);
    std::cerr << "\rLUT195   ";
    Ciphertext gin195 = 2 * gout184 + gout188;
    Ciphertext gout195 = ctx.eval_lut(&gin195, and2);
    std::cerr << "\rLUT196   ";
    Ciphertext gin196 = 2 * gout189 + gout185;
    Ciphertext gout196 = ctx.eval_lut(&gin196, and2);
    std::cerr << "\rLUT197   ";
    Ciphertext gin197 = 2 * gout187 + gout193;
    Ciphertext gout197 = ctx.eval_lut(&gin197, and2);
    std::cerr << "\rLUT198   ";
    Ciphertext gin198 = 2 * gout190 + gout182;
    Ciphertext gout198 = ctx.eval_lut(&gin198, and2);
    std::cerr << "\rLUT199   ";
    Ciphertext gin199 = 2 * gout186 + gout192;
    Ciphertext gout199 = ctx.eval_lut(&gin199, and2);
    std::cerr << "\rLUT200   ";
    Ciphertext gin200 = 2 * gout191 + gout197;
    Ciphertext gout200 = ctx.eval_lut(&gin200, nand2);
    std::cerr << "\rLUT201   ";
    Ciphertext gin201 = 2 * gout200 + gout195;
    Ciphertext gout201 = ctx.eval_lut(&gin201, nand2);
    std::cerr << "\rLUT202   ";
    Ciphertext gin202 = 2 * gout201 + gout198;
    Ciphertext gout202 = ctx.eval_lut(&gin202, nand2);
    std::cerr << "\rLUT203   ";
    Ciphertext gin203 = 2 * gout202 + gout196;
    Ciphertext gout203 = ctx.eval_lut(&gin203, nand2);
    std::cerr << "\rLUT204   ";
    Ciphertext gin204 = 2 * gout203 + gout199;
    Ciphertext gout204 = ctx.eval_lut(&gin204, nand2);
    std::cerr << "\rLUT205   ";
    Ciphertext gin205 = 2 * gout204 + gout194;
    Ciphertext gout205 = ctx.eval_lut(&gin205, nand2);
    std::cerr << "\rLUT206   ";
    Ciphertext gin206 = 2 * gout16 + gout205;
    Ciphertext gout206 = ctx.eval_lut(&gin206, and2);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(ctx.decrypt(&gout206)); /* out0 */
    test_out.push_back(ctx.decrypt(&gout177)); /* out1 */
    test_out.push_back(ctx.decrypt(&gout133)); /* out2 */
    test_out.push_back(ctx.decrypt(&gout98)); /* out3 */
    test_out.push_back(ctx.decrypt(&gout63)); /* out4 */
    test_out.push_back(ctx.decrypt(&gout38)); /* out5 */
    test_out.push_back(ctx.decrypt(&gout32)); /* out6 */
    test_out.push_back(ctx.decrypt(&gout30)); /* out7 */
    return test_out;
}

static void
BM_sqrt_boolean(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(tfhe_11_NTT);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(4);

    for (auto _ : state) {
        test_sqrt_boolean(ctx);
    }
}

BENCHMARK(BM_sqrt_boolean)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
