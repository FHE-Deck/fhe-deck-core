#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_sum_boolean(FHEContext& ctx, uint32_t a = 0, uint32_t b = 0)
{
    Ciphertext ct_a0 = ctx.encrypt_public((a >> 0) & 1);
    Ciphertext ct_a1 = ctx.encrypt_public((a >> 1) & 1);
    Ciphertext ct_a2 = ctx.encrypt_public((a >> 2) & 1);
    Ciphertext ct_a3 = ctx.encrypt_public((a >> 3) & 1);
    Ciphertext ct_a4 = ctx.encrypt_public((a >> 4) & 1);
    Ciphertext ct_a5 = ctx.encrypt_public((a >> 5) & 1);
    Ciphertext ct_a6 = ctx.encrypt_public((a >> 6) & 1);
    Ciphertext ct_a7 = ctx.encrypt_public((a >> 7) & 1);
    Ciphertext ct_a8 = ctx.encrypt_public((a >> 8) & 1);
    Ciphertext ct_a9 = ctx.encrypt_public((a >> 9) & 1);
    Ciphertext ct_a10 = ctx.encrypt_public((a >> 10) & 1);
    Ciphertext ct_a11 = ctx.encrypt_public((a >> 11) & 1);
    Ciphertext ct_a12 = ctx.encrypt_public((a >> 12) & 1);
    Ciphertext ct_a13 = ctx.encrypt_public((a >> 13) & 1);
    Ciphertext ct_a14 = ctx.encrypt_public((a >> 14) & 1);
    Ciphertext ct_a15 = ctx.encrypt_public((a >> 15) & 1);
    Ciphertext ct_a16 = ctx.encrypt_public((a >> 16) & 1);
    Ciphertext ct_a17 = ctx.encrypt_public((a >> 17) & 1);
    Ciphertext ct_a18 = ctx.encrypt_public((a >> 18) & 1);
    Ciphertext ct_a19 = ctx.encrypt_public((a >> 19) & 1);
    Ciphertext ct_a20 = ctx.encrypt_public((a >> 20) & 1);
    Ciphertext ct_a21 = ctx.encrypt_public((a >> 21) & 1);
    Ciphertext ct_a22 = ctx.encrypt_public((a >> 22) & 1);
    Ciphertext ct_a23 = ctx.encrypt_public((a >> 23) & 1);
    Ciphertext ct_a24 = ctx.encrypt_public((a >> 24) & 1);
    Ciphertext ct_a25 = ctx.encrypt_public((a >> 25) & 1);
    Ciphertext ct_a26 = ctx.encrypt_public((a >> 26) & 1);
    Ciphertext ct_a27 = ctx.encrypt_public((a >> 27) & 1);
    Ciphertext ct_a28 = ctx.encrypt_public((a >> 28) & 1);
    Ciphertext ct_a29 = ctx.encrypt_public((a >> 29) & 1);
    Ciphertext ct_a30 = ctx.encrypt_public((a >> 30) & 1);
    Ciphertext ct_a31 = ctx.encrypt_public((a >> 31) & 1);
    Ciphertext ct_b0 = ctx.encrypt_public((b >> 0) & 1);
    Ciphertext ct_b1 = ctx.encrypt_public((b >> 1) & 1);
    Ciphertext ct_b2 = ctx.encrypt_public((b >> 2) & 1);
    Ciphertext ct_b3 = ctx.encrypt_public((b >> 3) & 1);
    Ciphertext ct_b4 = ctx.encrypt_public((b >> 4) & 1);
    Ciphertext ct_b5 = ctx.encrypt_public((b >> 5) & 1);
    Ciphertext ct_b6 = ctx.encrypt_public((b >> 6) & 1);
    Ciphertext ct_b7 = ctx.encrypt_public((b >> 7) & 1);
    Ciphertext ct_b8 = ctx.encrypt_public((b >> 8) & 1);
    Ciphertext ct_b9 = ctx.encrypt_public((b >> 9) & 1);
    Ciphertext ct_b10 = ctx.encrypt_public((b >> 10) & 1);
    Ciphertext ct_b11 = ctx.encrypt_public((b >> 11) & 1);
    Ciphertext ct_b12 = ctx.encrypt_public((b >> 12) & 1);
    Ciphertext ct_b13 = ctx.encrypt_public((b >> 13) & 1);
    Ciphertext ct_b14 = ctx.encrypt_public((b >> 14) & 1);
    Ciphertext ct_b15 = ctx.encrypt_public((b >> 15) & 1);
    Ciphertext ct_b16 = ctx.encrypt_public((b >> 16) & 1);
    Ciphertext ct_b17 = ctx.encrypt_public((b >> 17) & 1);
    Ciphertext ct_b18 = ctx.encrypt_public((b >> 18) & 1);
    Ciphertext ct_b19 = ctx.encrypt_public((b >> 19) & 1);
    Ciphertext ct_b20 = ctx.encrypt_public((b >> 20) & 1);
    Ciphertext ct_b21 = ctx.encrypt_public((b >> 21) & 1);
    Ciphertext ct_b22 = ctx.encrypt_public((b >> 22) & 1);
    Ciphertext ct_b23 = ctx.encrypt_public((b >> 23) & 1);
    Ciphertext ct_b24 = ctx.encrypt_public((b >> 24) & 1);
    Ciphertext ct_b25 = ctx.encrypt_public((b >> 25) & 1);
    Ciphertext ct_b26 = ctx.encrypt_public((b >> 26) & 1);
    Ciphertext ct_b27 = ctx.encrypt_public((b >> 27) & 1);
    Ciphertext ct_b28 = ctx.encrypt_public((b >> 28) & 1);
    Ciphertext ct_b29 = ctx.encrypt_public((b >> 29) & 1);
    Ciphertext ct_b30 = ctx.encrypt_public((b >> 30) & 1);
    Ciphertext ct_b31 = ctx.encrypt_public((b >> 31) & 1);

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
    Ciphertext gin0 = 2 * ct_a15 + ct_b15;
    Ciphertext gout0 = ctx.eval_lut(&gin0, or2);
    std::cerr << "\rLUT1   ";
    Ciphertext gin1 = 2 * ct_a19 + ct_b19;
    Ciphertext gout1 = ctx.eval_lut(&gin1, or2);
    std::cerr << "\rLUT2   ";
    Ciphertext gin2 = 2 * ct_a27 + ct_b27;
    Ciphertext gout2 = ctx.eval_lut(&gin2, or2);
    std::cerr << "\rLUT3   ";
    Ciphertext gin3 = 2 * ct_a20 + ct_b20;
    Ciphertext gout3 = ctx.eval_lut(&gin3, nand2);
    std::cerr << "\rLUT4   ";
    Ciphertext gin4 = 2 * ct_a19 + ct_b19;
    Ciphertext gout4 = ctx.eval_lut(&gin4, xor2);
    std::cerr << "\rLUT5   ";
    Ciphertext gin5 = 2 * ct_a25 + ct_b25;
    Ciphertext gout5 = ctx.eval_lut(&gin5, nand2);
    std::cerr << "\rLUT6   ";
    Ciphertext gin6 = 2 * ct_a25 + ct_b25;
    Ciphertext gout6 = ctx.eval_lut(&gin6, or2);
    std::cerr << "\rLUT7   ";
    Ciphertext gin7 = 2 * ct_a8 + ct_b8;
    Ciphertext gout7 = ctx.eval_lut(&gin7, xor2);
    std::cerr << "\rLUT8   ";
    Ciphertext gin8 = 2 * ct_a9 + ct_b9;
    Ciphertext gout8 = ctx.eval_lut(&gin8, nand2);
    std::cerr << "\rLUT9   ";
    Ciphertext gin9 = 2 * ct_a20 + ct_b20;
    Ciphertext gout9 = ctx.eval_lut(&gin9, xor2);
    std::cerr << "\rLUT10   ";
    Ciphertext gin10 = 2 * ct_a15 + ct_b15;
    Ciphertext gout10 = ctx.eval_lut(&gin10, xor2);
    std::cerr << "\rLUT11   ";
    Ciphertext gin11 = 2 * ct_a0 + ct_b0;
    Ciphertext gout11 = ctx.eval_lut(&gin11, and2);
    std::cerr << "\rLUT12   ";
    Ciphertext gin12 = 2 * ct_a9 + ct_b9;
    Ciphertext gout12 = ctx.eval_lut(&gin12, xnor2);
    std::cerr << "\rLUT13   ";
    Ciphertext gin13 = 2 * ct_a17 + ct_b17;
    Ciphertext gout13 = ctx.eval_lut(&gin13, or2);
    std::cerr << "\rLUT14   ";
    Ciphertext gin14 = 2 * ct_a1 + ct_b1;
    Ciphertext gout14 = ctx.eval_lut(&gin14, nand2);
    std::cerr << "\rLUT15   ";
    Ciphertext gin15 = 2 * ct_a27 + ct_b27;
    Ciphertext gout15 = ctx.eval_lut(&gin15, nand2);
    std::cerr << "\rLUT16   ";
    Ciphertext gin16 = 2 * ct_a29 + ct_b29;
    Ciphertext gout16 = ctx.eval_lut(&gin16, nand2);
    std::cerr << "\rLUT17   ";
    Ciphertext gin17 = 2 * ct_a17 + ct_b17;
    Ciphertext gout17 = ctx.eval_lut(&gin17, nand2);
    std::cerr << "\rLUT18   ";
    Ciphertext gin18 = 2 * ct_a2 + ct_b2;
    Ciphertext gout18 = ctx.eval_lut(&gin18, nand2);
    std::cerr << "\rLUT19   ";
    Ciphertext gin19 = 2 * ct_a17 + ct_b17;
    Ciphertext gout19 = ctx.eval_lut(&gin19, xor2);
    std::cerr << "\rLUT20   ";
    Ciphertext gin20 = 2 * ct_a25 + ct_b25;
    Ciphertext gout20 = ctx.eval_lut(&gin20, xor2);
    std::cerr << "\rLUT21   ";
    Ciphertext gin21 = 2 * ct_a28 + ct_b28;
    Ciphertext gout21 = ctx.eval_lut(&gin21, xor2);
    std::cerr << "\rLUT22   ";
    Ciphertext gin22 = 2 * ct_a30 + ct_b30;
    Ciphertext gout22 = ctx.eval_lut(&gin22, nand2);
    std::cerr << "\rLUT23   ";
    Ciphertext gin23 = 2 * ct_a16 + ct_b16;
    Ciphertext gout23 = ctx.eval_lut(&gin23, nand2);
    std::cerr << "\rLUT24   ";
    Ciphertext gin24 = 2 * ct_a8 + ct_b8;
    Ciphertext gout24 = ctx.eval_lut(&gin24, nand2);
    std::cerr << "\rLUT25   ";
    Ciphertext gin25 = 2 * ct_a30 + ct_b30;
    Ciphertext gout25 = ctx.eval_lut(&gin25, xor2);
    std::cerr << "\rLUT26   ";
    Ciphertext gin26 = 2 * ct_a1 + ct_b1;
    Ciphertext gout26 = ctx.eval_lut(&gin26, xor2);
    std::cerr << "\rLUT27   ";
    Ciphertext gin27 = 2 * ct_a2 + ct_b2;
    Ciphertext gout27 = ctx.eval_lut(&gin27, xor2);
    std::cerr << "\rLUT28   ";
    Ciphertext gin28 = 2 * ct_a26 + ct_b26;
    Ciphertext gout28 = ctx.eval_lut(&gin28, xor2);
    std::cerr << "\rLUT29   ";
    Ciphertext gin29 = 2 * ct_a18 + ct_b18;
    Ciphertext gout29 = ctx.eval_lut(&gin29, nand2);
    std::cerr << "\rLUT30   ";
    Ciphertext gin30 = 2 * ct_a11 + ct_b11;
    Ciphertext gout30 = ctx.eval_lut(&gin30, or2);
    std::cerr << "\rLUT31   ";
    Ciphertext gin31 = 2 * ct_a13 + ct_b13;
    Ciphertext gout31 = ctx.eval_lut(&gin31, or2);
    std::cerr << "\rLUT32   ";
    Ciphertext gin32 = 2 * ct_a23 + ct_b23;
    Ciphertext gout32 = ctx.eval_lut(&gin32, nand2);
    std::cerr << "\rLUT33   ";
    Ciphertext gin33 = 2 * ct_a26 + ct_b26;
    Ciphertext gout33 = ctx.eval_lut(&gin33, nand2);
    std::cerr << "\rLUT34   ";
    Ciphertext gin34 = 2 * ct_a23 + ct_b23;
    Ciphertext gout34 = ctx.eval_lut(&gin34, or2);
    std::cerr << "\rLUT35   ";
    Ciphertext gin35 = 2 * ct_a7 + ct_b7;
    Ciphertext gout35 = ctx.eval_lut(&gin35, nand2);
    std::cerr << "\rLUT36   ";
    Ciphertext gin36 = 2 * ct_a7 + ct_b7;
    Ciphertext gout36 = ctx.eval_lut(&gin36, or2);
    std::cerr << "\rLUT37   ";
    Ciphertext gin37 = 2 * ct_a13 + ct_b13;
    Ciphertext gout37 = ctx.eval_lut(&gin37, nand2);
    std::cerr << "\rLUT38   ";
    Ciphertext gin38 = 2 * ct_a28 + ct_b28;
    Ciphertext gout38 = ctx.eval_lut(&gin38, nand2);
    std::cerr << "\rLUT39   ";
    Ciphertext gin39 = 2 * ct_a21 + ct_b21;
    Ciphertext gout39 = ctx.eval_lut(&gin39, nand2);
    std::cerr << "\rLUT40   ";
    Ciphertext gin40 = 2 * ct_a6 + ct_b6;
    Ciphertext gout40 = ctx.eval_lut(&gin40, nand2);
    std::cerr << "\rLUT41   ";
    Ciphertext gin41 = 2 * ct_a11 + ct_b11;
    Ciphertext gout41 = ctx.eval_lut(&gin41, xnor2);
    std::cerr << "\rLUT42   ";
    Ciphertext gin42 = 2 * ct_a18 + ct_b18;
    Ciphertext gout42 = ctx.eval_lut(&gin42, xor2);
    std::cerr << "\rLUT43   ";
    Ciphertext gin43 = 2 * ct_a24 + ct_b24;
    Ciphertext gout43 = ctx.eval_lut(&gin43, xor2);
    std::cerr << "\rLUT44   ";
    Ciphertext gin44 = 2 * ct_a10 + ct_b10;
    Ciphertext gout44 = ctx.eval_lut(&gin44, nand2);
    std::cerr << "\rLUT45   ";
    Ciphertext gin45 = 2 * ct_a13 + ct_b13;
    Ciphertext gout45 = ctx.eval_lut(&gin45, xor2);
    std::cerr << "\rLUT46   ";
    Ciphertext gin46 = 2 * ct_a6 + ct_b6;
    Ciphertext gout46 = ctx.eval_lut(&gin46, xor2);
    std::cerr << "\rLUT47   ";
    Ciphertext gin47 = 2 * ct_a14 + ct_b14;
    Ciphertext gout47 = ctx.eval_lut(&gin47, nand2);
    std::cerr << "\rLUT48   ";
    Ciphertext gin48 = 2 * ct_a24 + ct_b24;
    Ciphertext gout48 = ctx.eval_lut(&gin48, nand2);
    std::cerr << "\rLUT49   ";
    Ciphertext gin49 = 2 * ct_a23 + ct_b23;
    Ciphertext gout49 = ctx.eval_lut(&gin49, xor2);
    std::cerr << "\rLUT50   ";
    Ciphertext gin50 = 2 * ct_a3 + ct_b3;
    Ciphertext gout50 = ctx.eval_lut(&gin50, xor2);
    std::cerr << "\rLUT51   ";
    Ciphertext gin51 = 2 * ct_a21 + ct_b21;
    Ciphertext gout51 = ctx.eval_lut(&gin51, or2);
    std::cerr << "\rLUT52   ";
    Ciphertext gin52 = 2 * ct_a5 + ct_b5;
    Ciphertext gout52 = ctx.eval_lut(&gin52, nand2);
    std::cerr << "\rLUT53   ";
    Ciphertext gin53 = 2 * ct_a0 + ct_b0;
    Ciphertext gout53 = ctx.eval_lut(&gin53, xor2);
    std::cerr << "\rLUT54   ";
    Ciphertext gin54 = 2 * ct_a16 + ct_b16;
    Ciphertext gout54 = ctx.eval_lut(&gin54, xor2);
    std::cerr << "\rLUT55   ";
    Ciphertext gin55 = 2 * ct_a10 + ct_b10;
    Ciphertext gout55 = ctx.eval_lut(&gin55, xor2);
    std::cerr << "\rLUT56   ";
    Ciphertext gin56 = 2 * ct_a14 + ct_b14;
    Ciphertext gout56 = ctx.eval_lut(&gin56, xor2);
    std::cerr << "\rLUT57   ";
    Ciphertext gin57 = 2 * ct_a31 + ct_b31;
    Ciphertext gout57 = ctx.eval_lut(&gin57, xnor2);
    std::cerr << "\rLUT58   ";
    Ciphertext gin58 = 2 * ct_a7 + ct_b7;
    Ciphertext gout58 = ctx.eval_lut(&gin58, xnor2);
    std::cerr << "\rLUT59   ";
    Ciphertext gin59 = 2 * ct_a29 + ct_b29;
    Ciphertext gout59 = ctx.eval_lut(&gin59, xor2);
    std::cerr << "\rLUT60   ";
    Ciphertext gin60 = 2 * ct_a3 + ct_b3;
    Ciphertext gout60 = ctx.eval_lut(&gin60, nand2);
    std::cerr << "\rLUT61   ";
    Ciphertext gin61 = 2 * ct_a27 + ct_b27;
    Ciphertext gout61 = ctx.eval_lut(&gin61, xor2);
    std::cerr << "\rLUT62   ";
    Ciphertext gin62 = 2 * ct_a12 + ct_b12;
    Ciphertext gout62 = ctx.eval_lut(&gin62, xor2);
    std::cerr << "\rLUT63   ";
    Ciphertext gin63 = 2 * ct_a12 + ct_b12;
    Ciphertext gout63 = ctx.eval_lut(&gin63, nand2);
    std::cerr << "\rLUT64   ";
    Ciphertext gin64 = 2 * ct_a4 + ct_b4;
    Ciphertext gout64 = ctx.eval_lut(&gin64, nand2);
    std::cerr << "\rLUT65   ";
    Ciphertext gin65 = 2 * ct_a19 + ct_b19;
    Ciphertext gout65 = ctx.eval_lut(&gin65, nand2);
    std::cerr << "\rLUT66   ";
    Ciphertext gin66 = 2 * ct_a21 + ct_b21;
    Ciphertext gout66 = ctx.eval_lut(&gin66, xor2);
    std::cerr << "\rLUT67   ";
    Ciphertext gin67 = 2 * ct_a11 + ct_b11;
    Ciphertext gout67 = ctx.eval_lut(&gin67, nand2);
    std::cerr << "\rLUT68   ";
    Ciphertext gin68 = 2 * ct_a5 + ct_b5;
    Ciphertext gout68 = ctx.eval_lut(&gin68, xor2);
    std::cerr << "\rLUT69   ";
    Ciphertext gin69 = 2 * ct_a22 + ct_b22;
    Ciphertext gout69 = ctx.eval_lut(&gin69, xor2);
    std::cerr << "\rLUT70   ";
    Ciphertext gin70 = 2 * ct_a15 + ct_b15;
    Ciphertext gout70 = ctx.eval_lut(&gin70, nand2);
    std::cerr << "\rLUT71   ";
    Ciphertext gin71 = 2 * ct_a4 + ct_b4;
    Ciphertext gout71 = ctx.eval_lut(&gin71, xor2);
    std::cerr << "\rLUT72   ";
    Ciphertext gin72 = 2 * ct_a9 + ct_b9;
    Ciphertext gout72 = ctx.eval_lut(&gin72, or2);
    std::cerr << "\rLUT73   ";
    Ciphertext gin73 = 2 * ct_a22 + ct_b22;
    Ciphertext gout73 = ctx.eval_lut(&gin73, nand2);
    std::cerr << "\rLUT74   ";
    Ciphertext gin74 = 2 * gout11 + gout26;
    Ciphertext gout74 = ctx.eval_lut(&gin74, xor2);
    std::cerr << "\rLUT75   ";
    Ciphertext gin75 = 2 * gout11 + gout26;
    Ciphertext gout75 = ctx.eval_lut(&gin75, nand2);
    std::cerr << "\rLUT76   ";
    Ciphertext gin76 = 2 * gout14 + gout75;
    Ciphertext gout76 = ctx.eval_lut(&gin76, nand2);
    std::cerr << "\rLUT77   ";
    Ciphertext gin77 = 2 * gout76 + gout27;
    Ciphertext gout77 = ctx.eval_lut(&gin77, xor2);
    std::cerr << "\rLUT78   ";
    Ciphertext gin78 = 2 * gout76 + gout27;
    Ciphertext gout78 = ctx.eval_lut(&gin78, nand2);
    std::cerr << "\rLUT79   ";
    Ciphertext gin79 = 2 * gout18 + gout78;
    Ciphertext gout79 = ctx.eval_lut(&gin79, nand2);
    std::cerr << "\rLUT80   ";
    Ciphertext gin80 = 2 * gout79 + gout50;
    Ciphertext gout80 = ctx.eval_lut(&gin80, xor2);
    std::cerr << "\rLUT81   ";
    Ciphertext gin81 = 2 * gout79 + gout50;
    Ciphertext gout81 = ctx.eval_lut(&gin81, nand2);
    std::cerr << "\rLUT82   ";
    Ciphertext gin82 = 2 * gout60 + gout81;
    Ciphertext gout82 = ctx.eval_lut(&gin82, nand2);
    std::cerr << "\rLUT83   ";
    Ciphertext gin83 = 2 * gout82 + gout71;
    Ciphertext gout83 = ctx.eval_lut(&gin83, xor2);
    std::cerr << "\rLUT84   ";
    Ciphertext gin84 = 2 * gout82 + gout71;
    Ciphertext gout84 = ctx.eval_lut(&gin84, nand2);
    std::cerr << "\rLUT85   ";
    Ciphertext gin85 = 2 * gout64 + gout84;
    Ciphertext gout85 = ctx.eval_lut(&gin85, nand2);
    std::cerr << "\rLUT86   ";
    Ciphertext gin86 = 2 * gout85 + gout68;
    Ciphertext gout86 = ctx.eval_lut(&gin86, nand2);
    std::cerr << "\rLUT87   ";
    Ciphertext gin87 = 2 * gout85 + gout68;
    Ciphertext gout87 = ctx.eval_lut(&gin87, xor2);
    std::cerr << "\rLUT88   ";
    Ciphertext gin88 = 2 * gout52 + gout86;
    Ciphertext gout88 = ctx.eval_lut(&gin88, nand2);
    std::cerr << "\rLUT89   ";
    Ciphertext gin89 = 2 * gout46 + gout88;
    Ciphertext gout89 = ctx.eval_lut(&gin89, nand2);
    std::cerr << "\rLUT90   ";
    Ciphertext gin90 = 2 * gout46 + gout88;
    Ciphertext gout90 = ctx.eval_lut(&gin90, xor2);
    std::cerr << "\rLUT91   ";
    Ciphertext gin91 = 2 * gout40 + gout89;
    Ciphertext gout91 = ctx.eval_lut(&gin91, nand2);
    std::cerr << "\rLUT92   ";
    Ciphertext gin92 = 2 * gout36 + gout91;
    Ciphertext gout92 = ctx.eval_lut(&gin92, nand2);
    std::cerr << "\rLUT93   ";
    Ciphertext gin93 = 2 * gout91 + gout58;
    Ciphertext gout93 = ctx.eval_lut(&gin93, xnor2);
    std::cerr << "\rLUT94   ";
    Ciphertext gin94 = 2 * gout35 + gout92;
    Ciphertext gout94 = ctx.eval_lut(&gin94, nand2);
    std::cerr << "\rLUT95   ";
    Ciphertext gin95 = 2 * gout7 + gout94;
    Ciphertext gout95 = ctx.eval_lut(&gin95, nand2);
    std::cerr << "\rLUT96   ";
    Ciphertext gin96 = 2 * gout7 + gout94;
    Ciphertext gout96 = ctx.eval_lut(&gin96, xor2);
    std::cerr << "\rLUT97   ";
    Ciphertext gin97 = 2 * gout24 + gout95;
    Ciphertext gout97 = ctx.eval_lut(&gin97, nand2);
    std::cerr << "\rLUT98   ";
    Ciphertext gin98 = 2 * gout97 + gout12;
    Ciphertext gout98 = ctx.eval_lut(&gin98, xnor2);
    std::cerr << "\rLUT99   ";
    Ciphertext gin99 = 2 * gout72 + gout97;
    Ciphertext gout99 = ctx.eval_lut(&gin99, nand2);
    std::cerr << "\rLUT100   ";
    Ciphertext gin100 = 2 * gout8 + gout99;
    Ciphertext gout100 = ctx.eval_lut(&gin100, nand2);
    std::cerr << "\rLUT101   ";
    Ciphertext gin101 = 2 * gout55 + gout100;
    Ciphertext gout101 = ctx.eval_lut(&gin101, nand2);
    std::cerr << "\rLUT102   ";
    Ciphertext gin102 = 2 * gout55 + gout100;
    Ciphertext gout102 = ctx.eval_lut(&gin102, xor2);
    std::cerr << "\rLUT103   ";
    Ciphertext gin103 = 2 * gout44 + gout101;
    Ciphertext gout103 = ctx.eval_lut(&gin103, nand2);
    std::cerr << "\rLUT104   ";
    Ciphertext gin104 = 2 * gout103 + gout41;
    Ciphertext gout104 = ctx.eval_lut(&gin104, xnor2);
    std::cerr << "\rLUT105   ";
    Ciphertext gin105 = 2 * gout30 + gout103;
    Ciphertext gout105 = ctx.eval_lut(&gin105, nand2);
    std::cerr << "\rLUT106   ";
    Ciphertext gin106 = 2 * gout67 + gout105;
    Ciphertext gout106 = ctx.eval_lut(&gin106, nand2);
    std::cerr << "\rLUT107   ";
    Ciphertext gin107 = 2 * gout62 + gout106;
    Ciphertext gout107 = ctx.eval_lut(&gin107, xor2);
    std::cerr << "\rLUT108   ";
    Ciphertext gin108 = 2 * gout62 + gout106;
    Ciphertext gout108 = ctx.eval_lut(&gin108, nand2);
    std::cerr << "\rLUT109   ";
    Ciphertext gin109 = 2 * gout63 + gout108;
    Ciphertext gout109 = ctx.eval_lut(&gin109, and2);
    std::cerr << "\rLUT110   ";
    Ciphertext gin110 = 2 * gout109 + gout37;
    Ciphertext gout110 = ctx.eval_lut(&gin110, nand2);
    std::cerr << "\rLUT111   ";
    Ciphertext gin111 = 2 * gout109 + gout45;
    Ciphertext gout111 = ctx.eval_lut(&gin111, xnor2);
    std::cerr << "\rLUT112   ";
    Ciphertext gin112 = 2 * gout31 + gout110;
    Ciphertext gout112 = ctx.eval_lut(&gin112, and2);
    std::cerr << "\rLUT113   ";
    Ciphertext gin113 = 2 * gout56 + gout112;
    Ciphertext gout113 = ctx.eval_lut(&gin113, xor2);
    std::cerr << "\rLUT114   ";
    Ciphertext gin114 = 2 * gout56 + gout112;
    Ciphertext gout114 = ctx.eval_lut(&gin114, nand2);
    std::cerr << "\rLUT115   ";
    Ciphertext gin115 = 2 * gout47 + gout114;
    Ciphertext gout115 = ctx.eval_lut(&gin115, and2);
    std::cerr << "\rLUT116   ";
    Ciphertext gin116 = 2 * gout115 + gout70;
    Ciphertext gout116 = ctx.eval_lut(&gin116, nand2);
    std::cerr << "\rLUT117   ";
    Ciphertext gin117 = 2 * gout115 + gout10;
    Ciphertext gout117 = ctx.eval_lut(&gin117, xnor2);
    std::cerr << "\rLUT118   ";
    Ciphertext gin118 = 2 * gout0 + gout116;
    Ciphertext gout118 = ctx.eval_lut(&gin118, and2);
    std::cerr << "\rLUT119   ";
    Ciphertext gin119 = 2 * gout54 + gout118;
    Ciphertext gout119 = ctx.eval_lut(&gin119, nand2);
    std::cerr << "\rLUT120   ";
    Ciphertext gin120 = 2 * gout54 + gout118;
    Ciphertext gout120 = ctx.eval_lut(&gin120, xor2);
    std::cerr << "\rLUT121   ";
    Ciphertext gin121 = 2 * gout23 + gout119;
    Ciphertext gout121 = ctx.eval_lut(&gin121, and2);
    std::cerr << "\rLUT122   ";
    Ciphertext gin122 = 2 * gout121 + gout17;
    Ciphertext gout122 = ctx.eval_lut(&gin122, nand2);
    std::cerr << "\rLUT123   ";
    Ciphertext gin123 = 2 * gout121 + gout19;
    Ciphertext gout123 = ctx.eval_lut(&gin123, xnor2);
    std::cerr << "\rLUT124   ";
    Ciphertext gin124 = 2 * gout13 + gout122;
    Ciphertext gout124 = ctx.eval_lut(&gin124, and2);
    std::cerr << "\rLUT125   ";
    Ciphertext gin125 = 2 * gout42 + gout124;
    Ciphertext gout125 = ctx.eval_lut(&gin125, nand2);
    std::cerr << "\rLUT126   ";
    Ciphertext gin126 = 2 * gout42 + gout124;
    Ciphertext gout126 = ctx.eval_lut(&gin126, xor2);
    std::cerr << "\rLUT127   ";
    Ciphertext gin127 = 2 * gout29 + gout125;
    Ciphertext gout127 = ctx.eval_lut(&gin127, and2);
    std::cerr << "\rLUT128   ";
    Ciphertext gin128 = 2 * gout127 + gout65;
    Ciphertext gout128 = ctx.eval_lut(&gin128, nand2);
    std::cerr << "\rLUT129   ";
    Ciphertext gin129 = 2 * gout127 + gout4;
    Ciphertext gout129 = ctx.eval_lut(&gin129, xnor2);
    std::cerr << "\rLUT130   ";
    Ciphertext gin130 = 2 * gout1 + gout128;
    Ciphertext gout130 = ctx.eval_lut(&gin130, and2);
    std::cerr << "\rLUT131   ";
    Ciphertext gin131 = 2 * gout9 + gout130;
    Ciphertext gout131 = ctx.eval_lut(&gin131, nand2);
    std::cerr << "\rLUT132   ";
    Ciphertext gin132 = 2 * gout9 + gout130;
    Ciphertext gout132 = ctx.eval_lut(&gin132, xor2);
    std::cerr << "\rLUT133   ";
    Ciphertext gin133 = 2 * gout3 + gout131;
    Ciphertext gout133 = ctx.eval_lut(&gin133, and2);
    std::cerr << "\rLUT134   ";
    Ciphertext gin134 = 2 * gout133 + gout39;
    Ciphertext gout134 = ctx.eval_lut(&gin134, nand2);
    std::cerr << "\rLUT135   ";
    Ciphertext gin135 = 2 * gout133 + gout66;
    Ciphertext gout135 = ctx.eval_lut(&gin135, xnor2);
    std::cerr << "\rLUT136   ";
    Ciphertext gin136 = 2 * gout51 + gout134;
    Ciphertext gout136 = ctx.eval_lut(&gin136, and2);
    std::cerr << "\rLUT137   ";
    Ciphertext gin137 = 2 * gout69 + gout136;
    Ciphertext gout137 = ctx.eval_lut(&gin137, nand2);
    std::cerr << "\rLUT138   ";
    Ciphertext gin138 = 2 * gout69 + gout136;
    Ciphertext gout138 = ctx.eval_lut(&gin138, xor2);
    std::cerr << "\rLUT139   ";
    Ciphertext gin139 = 2 * gout73 + gout137;
    Ciphertext gout139 = ctx.eval_lut(&gin139, and2);
    std::cerr << "\rLUT140   ";
    Ciphertext gin140 = 2 * gout139 + gout32;
    Ciphertext gout140 = ctx.eval_lut(&gin140, nand2);
    std::cerr << "\rLUT141   ";
    Ciphertext gin141 = 2 * gout139 + gout49;
    Ciphertext gout141 = ctx.eval_lut(&gin141, xnor2);
    std::cerr << "\rLUT142   ";
    Ciphertext gin142 = 2 * gout34 + gout140;
    Ciphertext gout142 = ctx.eval_lut(&gin142, and2);
    std::cerr << "\rLUT143   ";
    Ciphertext gin143 = 2 * gout43 + gout142;
    Ciphertext gout143 = ctx.eval_lut(&gin143, nand2);
    std::cerr << "\rLUT144   ";
    Ciphertext gin144 = 2 * gout43 + gout142;
    Ciphertext gout144 = ctx.eval_lut(&gin144, xor2);
    std::cerr << "\rLUT145   ";
    Ciphertext gin145 = 2 * gout48 + gout143;
    Ciphertext gout145 = ctx.eval_lut(&gin145, and2);
    std::cerr << "\rLUT146   ";
    Ciphertext gin146 = 2 * gout145 + gout5;
    Ciphertext gout146 = ctx.eval_lut(&gin146, nand2);
    std::cerr << "\rLUT147   ";
    Ciphertext gin147 = 2 * gout145 + gout20;
    Ciphertext gout147 = ctx.eval_lut(&gin147, xnor2);
    std::cerr << "\rLUT148   ";
    Ciphertext gin148 = 2 * gout6 + gout146;
    Ciphertext gout148 = ctx.eval_lut(&gin148, and2);
    std::cerr << "\rLUT149   ";
    Ciphertext gin149 = 2 * gout28 + gout148;
    Ciphertext gout149 = ctx.eval_lut(&gin149, nand2);
    std::cerr << "\rLUT150   ";
    Ciphertext gin150 = 2 * gout28 + gout148;
    Ciphertext gout150 = ctx.eval_lut(&gin150, xor2);
    std::cerr << "\rLUT151   ";
    Ciphertext gin151 = 2 * gout33 + gout149;
    Ciphertext gout151 = ctx.eval_lut(&gin151, and2);
    std::cerr << "\rLUT152   ";
    Ciphertext gin152 = 2 * gout151 + gout61;
    Ciphertext gout152 = ctx.eval_lut(&gin152, xnor2);
    std::cerr << "\rLUT153   ";
    Ciphertext gin153 = 2 * gout151 + gout15;
    Ciphertext gout153 = ctx.eval_lut(&gin153, nand2);
    std::cerr << "\rLUT154   ";
    Ciphertext gin154 = 2 * gout2 + gout153;
    Ciphertext gout154 = ctx.eval_lut(&gin154, and2);
    std::cerr << "\rLUT155   ";
    Ciphertext gin155 = 2 * gout21 + gout154;
    Ciphertext gout155 = ctx.eval_lut(&gin155, nand2);
    std::cerr << "\rLUT156   ";
    Ciphertext gin156 = 2 * gout21 + gout154;
    Ciphertext gout156 = ctx.eval_lut(&gin156, xor2);
    std::cerr << "\rLUT157   ";
    Ciphertext gin157 = 2 * gout38 + gout155;
    Ciphertext gout157 = ctx.eval_lut(&gin157, nand2);
    std::cerr << "\rLUT158   ";
    Ciphertext gin158 = 2 * gout157 + gout59;
    Ciphertext gout158 = ctx.eval_lut(&gin158, xor2);
    std::cerr << "\rLUT159   ";
    Ciphertext gin159 = 2 * gout157 + gout59;
    Ciphertext gout159 = ctx.eval_lut(&gin159, nand2);
    std::cerr << "\rLUT160   ";
    Ciphertext gin160 = 2 * gout16 + gout159;
    Ciphertext gout160 = ctx.eval_lut(&gin160, nand2);
    std::cerr << "\rLUT161   ";
    Ciphertext gin161 = 2 * gout160 + gout25;
    Ciphertext gout161 = ctx.eval_lut(&gin161, xor2);
    std::cerr << "\rLUT162   ";
    Ciphertext gin162 = 2 * gout160 + gout25;
    Ciphertext gout162 = ctx.eval_lut(&gin162, nand2);
    std::cerr << "\rLUT163   ";
    Ciphertext gin163 = 2 * gout22 + gout162;
    Ciphertext gout163 = ctx.eval_lut(&gin163, nand2);
    std::cerr << "\rLUT164   ";
    Ciphertext gin164 = 2 * gout163 + gout57;
    Ciphertext gout164 = ctx.eval_lut(&gin164, xnor2);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(ctx.decrypt(&gout53)); /* out0 */
    test_out.push_back(ctx.decrypt(&gout74)); /* out1 */
    test_out.push_back(ctx.decrypt(&gout77)); /* out2 */
    test_out.push_back(ctx.decrypt(&gout80)); /* out3 */
    test_out.push_back(ctx.decrypt(&gout83)); /* out4 */
    test_out.push_back(ctx.decrypt(&gout87)); /* out5 */
    test_out.push_back(ctx.decrypt(&gout90)); /* out6 */
    test_out.push_back(ctx.decrypt(&gout93)); /* out7 */
    test_out.push_back(ctx.decrypt(&gout96)); /* out8 */
    test_out.push_back(ctx.decrypt(&gout98)); /* out9 */
    test_out.push_back(ctx.decrypt(&gout102)); /* out10 */
    test_out.push_back(ctx.decrypt(&gout104)); /* out11 */
    test_out.push_back(ctx.decrypt(&gout107)); /* out12 */
    test_out.push_back(ctx.decrypt(&gout111)); /* out13 */
    test_out.push_back(ctx.decrypt(&gout113)); /* out14 */
    test_out.push_back(ctx.decrypt(&gout117)); /* out15 */
    test_out.push_back(ctx.decrypt(&gout120)); /* out16 */
    test_out.push_back(ctx.decrypt(&gout123)); /* out17 */
    test_out.push_back(ctx.decrypt(&gout126)); /* out18 */
    test_out.push_back(ctx.decrypt(&gout129)); /* out19 */
    test_out.push_back(ctx.decrypt(&gout132)); /* out20 */
    test_out.push_back(ctx.decrypt(&gout135)); /* out21 */
    test_out.push_back(ctx.decrypt(&gout138)); /* out22 */
    test_out.push_back(ctx.decrypt(&gout141)); /* out23 */
    test_out.push_back(ctx.decrypt(&gout144)); /* out24 */
    test_out.push_back(ctx.decrypt(&gout147)); /* out25 */
    test_out.push_back(ctx.decrypt(&gout150)); /* out26 */
    test_out.push_back(ctx.decrypt(&gout152)); /* out27 */
    test_out.push_back(ctx.decrypt(&gout156)); /* out28 */
    test_out.push_back(ctx.decrypt(&gout158)); /* out29 */
    test_out.push_back(ctx.decrypt(&gout161)); /* out30 */
    test_out.push_back(ctx.decrypt(&gout164)); /* out31 */
    return test_out;
}

static void
BM_sum_boolean(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(tfhe_11_NTT);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(4);

    for (auto _ : state) {
        test_sum_boolean(ctx);
    }
}

BENCHMARK(BM_sum_boolean)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
