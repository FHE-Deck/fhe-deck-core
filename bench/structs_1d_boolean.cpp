#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_structs_1d_boolean(FHEContext& ctx, uint64_t data = 0)
{
    Ciphertext ct_data0 = ctx.encrypt_public((data >> 0) & 1);
    Ciphertext ct_data1 = ctx.encrypt_public((data >> 1) & 1);
    Ciphertext ct_data2 = ctx.encrypt_public((data >> 2) & 1);
    Ciphertext ct_data3 = ctx.encrypt_public((data >> 3) & 1);
    Ciphertext ct_data4 = ctx.encrypt_public((data >> 4) & 1);
    Ciphertext ct_data5 = ctx.encrypt_public((data >> 5) & 1);
    Ciphertext ct_data6 = ctx.encrypt_public((data >> 6) & 1);
    Ciphertext ct_data7 = ctx.encrypt_public((data >> 7) & 1);
    Ciphertext ct_data8 = ctx.encrypt_public((data >> 8) & 1);
    Ciphertext ct_data9 = ctx.encrypt_public((data >> 9) & 1);
    Ciphertext ct_data10 = ctx.encrypt_public((data >> 10) & 1);
    Ciphertext ct_data11 = ctx.encrypt_public((data >> 11) & 1);
    Ciphertext ct_data12 = ctx.encrypt_public((data >> 12) & 1);
    Ciphertext ct_data13 = ctx.encrypt_public((data >> 13) & 1);
    Ciphertext ct_data14 = ctx.encrypt_public((data >> 14) & 1);
    Ciphertext ct_data15 = ctx.encrypt_public((data >> 15) & 1);
    Ciphertext ct_data16 = ctx.encrypt_public((data >> 16) & 1);
    Ciphertext ct_data17 = ctx.encrypt_public((data >> 17) & 1);
    Ciphertext ct_data18 = ctx.encrypt_public((data >> 18) & 1);
    Ciphertext ct_data19 = ctx.encrypt_public((data >> 19) & 1);
    Ciphertext ct_data20 = ctx.encrypt_public((data >> 20) & 1);
    Ciphertext ct_data21 = ctx.encrypt_public((data >> 21) & 1);
    Ciphertext ct_data22 = ctx.encrypt_public((data >> 22) & 1);
    Ciphertext ct_data23 = ctx.encrypt_public((data >> 23) & 1);
    Ciphertext ct_data24 = ctx.encrypt_public((data >> 24) & 1);
    Ciphertext ct_data25 = ctx.encrypt_public((data >> 25) & 1);
    Ciphertext ct_data26 = ctx.encrypt_public((data >> 26) & 1);
    Ciphertext ct_data27 = ctx.encrypt_public((data >> 27) & 1);
    Ciphertext ct_data28 = ctx.encrypt_public((data >> 28) & 1);
    Ciphertext ct_data29 = ctx.encrypt_public((data >> 29) & 1);
    Ciphertext ct_data30 = ctx.encrypt_public((data >> 30) & 1);
    Ciphertext ct_data32 = ctx.encrypt_public((data >> 31) & 1);
    Ciphertext ct_data33 = ctx.encrypt_public((data >> 32) & 1);
    Ciphertext ct_data34 = ctx.encrypt_public((data >> 33) & 1);
    Ciphertext ct_data35 = ctx.encrypt_public((data >> 34) & 1);
    Ciphertext ct_data36 = ctx.encrypt_public((data >> 35) & 1);
    Ciphertext ct_data37 = ctx.encrypt_public((data >> 36) & 1);
    Ciphertext ct_data38 = ctx.encrypt_public((data >> 37) & 1);
    Ciphertext ct_data39 = ctx.encrypt_public((data >> 38) & 1);
    Ciphertext ct_data40 = ctx.encrypt_public((data >> 39) & 1);
    Ciphertext ct_data41 = ctx.encrypt_public((data >> 40) & 1);
    Ciphertext ct_data42 = ctx.encrypt_public((data >> 41) & 1);
    Ciphertext ct_data43 = ctx.encrypt_public((data >> 42) & 1);
    Ciphertext ct_data44 = ctx.encrypt_public((data >> 43) & 1);
    Ciphertext ct_data45 = ctx.encrypt_public((data >> 44) & 1);
    Ciphertext ct_data46 = ctx.encrypt_public((data >> 45) & 1);
    Ciphertext ct_data47 = ctx.encrypt_public((data >> 46) & 1);
    Ciphertext ct_data48 = ctx.encrypt_public((data >> 47) & 1);
    Ciphertext ct_data49 = ctx.encrypt_public((data >> 48) & 1);
    Ciphertext ct_data50 = ctx.encrypt_public((data >> 49) & 1);
    Ciphertext ct_data51 = ctx.encrypt_public((data >> 50) & 1);
    Ciphertext ct_data52 = ctx.encrypt_public((data >> 51) & 1);
    Ciphertext ct_data53 = ctx.encrypt_public((data >> 52) & 1);
    Ciphertext ct_data54 = ctx.encrypt_public((data >> 53) & 1);
    Ciphertext ct_data55 = ctx.encrypt_public((data >> 54) & 1);
    Ciphertext ct_data56 = ctx.encrypt_public((data >> 55) & 1);
    Ciphertext ct_data57 = ctx.encrypt_public((data >> 56) & 1);
    Ciphertext ct_data58 = ctx.encrypt_public((data >> 57) & 1);
    Ciphertext ct_data59 = ctx.encrypt_public((data >> 58) & 1);
    Ciphertext ct_data60 = ctx.encrypt_public((data >> 59) & 1);
    Ciphertext ct_data61 = ctx.encrypt_public((data >> 60) & 1);
    Ciphertext ct_data62 = ctx.encrypt_public((data >> 61) & 1);

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
    Ciphertext gin0 = 2 * ct_data12 + ct_data44;
    Ciphertext gout0 = ctx.eval_lut(&gin0, xor2);
    std::cerr << "\rLUT1   ";
    Ciphertext gin1 = 2 * ct_data22 + ct_data54;
    Ciphertext gout1 = ctx.eval_lut(&gin1, xor2);
    std::cerr << "\rLUT2   ";
    Ciphertext gin2 = 2 * ct_data22 + ct_data54;
    Ciphertext gout2 = ctx.eval_lut(&gin2, nand2);
    std::cerr << "\rLUT3   ";
    Ciphertext gin3 = 2 * ct_data13 + ct_data45;
    Ciphertext gout3 = ctx.eval_lut(&gin3, or2);
    std::cerr << "\rLUT4   ";
    Ciphertext gin4 = 2 * ct_data19 + ct_data51;
    Ciphertext gout4 = ctx.eval_lut(&gin4, or2);
    std::cerr << "\rLUT5   ";
    Ciphertext gin5 = 2 * ct_data4 + ct_data36;
    Ciphertext gout5 = ctx.eval_lut(&gin5, xor2);
    std::cerr << "\rLUT6   ";
    Ciphertext gin6 = 2 * ct_data19 + ct_data51;
    Ciphertext gout6 = ctx.eval_lut(&gin6, xor2);
    std::cerr << "\rLUT7   ";
    Ciphertext gin7 = 2 * ct_data3 + ct_data35;
    Ciphertext gout7 = ctx.eval_lut(&gin7, nand2);
    std::cerr << "\rLUT8   ";
    Ciphertext gin8 = 2 * ct_data14 + ct_data46;
    Ciphertext gout8 = ctx.eval_lut(&gin8, nand2);
    std::cerr << "\rLUT9   ";
    Ciphertext gin9 = 2 * ct_data13 + ct_data45;
    Ciphertext gout9 = ctx.eval_lut(&gin9, xor2);
    std::cerr << "\rLUT10   ";
    Ciphertext gin10 = 2 * ct_data5 + ct_data37;
    Ciphertext gout10 = ctx.eval_lut(&gin10, nand2);
    std::cerr << "\rLUT11   ";
    Ciphertext gin11 = 2 * ct_data25 + ct_data57;
    Ciphertext gout11 = ctx.eval_lut(&gin11, xor2);
    std::cerr << "\rLUT12   ";
    Ciphertext gin12 = 2 * ct_data4 + ct_data36;
    Ciphertext gout12 = ctx.eval_lut(&gin12, nand2);
    std::cerr << "\rLUT13   ";
    Ciphertext gin13 = 2 * ct_data25 + ct_data57;
    Ciphertext gout13 = ctx.eval_lut(&gin13, nand2);
    std::cerr << "\rLUT14   ";
    Ciphertext gin14 = 2 * ct_data27 + ct_data59;
    Ciphertext gout14 = ctx.eval_lut(&gin14, nand2);
    std::cerr << "\rLUT15   ";
    Ciphertext gin15 = 2 * ct_data11 + ct_data43;
    Ciphertext gout15 = ctx.eval_lut(&gin15, xnor2);
    std::cerr << "\rLUT16   ";
    Ciphertext gin16 = 2 * ct_data20 + ct_data52;
    Ciphertext gout16 = ctx.eval_lut(&gin16, xor2);
    std::cerr << "\rLUT17   ";
    Ciphertext gin17 = 2 * ct_data10 + ct_data42;
    Ciphertext gout17 = ctx.eval_lut(&gin17, xor2);
    std::cerr << "\rLUT18   ";
    Ciphertext gin18 = 2 * ct_data14 + ct_data46;
    Ciphertext gout18 = ctx.eval_lut(&gin18, xor2);
    std::cerr << "\rLUT19   ";
    Ciphertext gin19 = 2 * ct_data17 + ct_data49;
    Ciphertext gout19 = ctx.eval_lut(&gin19, nand2);
    std::cerr << "\rLUT20   ";
    Ciphertext gin20 = 2 * ct_data17 + ct_data49;
    Ciphertext gout20 = ctx.eval_lut(&gin20, or2);
    std::cerr << "\rLUT21   ";
    Ciphertext gin21 = 2 * ct_data17 + ct_data49;
    Ciphertext gout21 = ctx.eval_lut(&gin21, xor2);
    std::cerr << "\rLUT22   ";
    Ciphertext gin22 = 2 * ct_data20 + ct_data52;
    Ciphertext gout22 = ctx.eval_lut(&gin22, nand2);
    std::cerr << "\rLUT23   ";
    Ciphertext gin23 = 2 * ct_data27 + ct_data59;
    Ciphertext gout23 = ctx.eval_lut(&gin23, or2);
    std::cerr << "\rLUT24   ";
    Ciphertext gin24 = 2 * ct_data29 + ct_data61;
    Ciphertext gout24 = ctx.eval_lut(&gin24, xor2);
    std::cerr << "\rLUT25   ";
    Ciphertext gin25 = 2 * ct_data0 + ct_data32;
    Ciphertext gout25 = ctx.eval_lut(&gin25, xor2);
    std::cerr << "\rLUT26   ";
    Ciphertext gin26 = 2 * ct_data30 + ct_data62;
    Ciphertext gout26 = ctx.eval_lut(&gin26, xnor2);
    std::cerr << "\rLUT27   ";
    Ciphertext gin27 = 2 * ct_data11 + ct_data43;
    Ciphertext gout27 = ctx.eval_lut(&gin27, nand2);
    std::cerr << "\rLUT28   ";
    Ciphertext gin28 = 2 * ct_data28 + ct_data60;
    Ciphertext gout28 = ctx.eval_lut(&gin28, nand2);
    std::cerr << "\rLUT29   ";
    Ciphertext gin29 = 2 * ct_data5 + ct_data37;
    Ciphertext gout29 = ctx.eval_lut(&gin29, xor2);
    std::cerr << "\rLUT30   ";
    Ciphertext gin30 = 2 * ct_data18 + ct_data50;
    Ciphertext gout30 = ctx.eval_lut(&gin30, nand2);
    std::cerr << "\rLUT31   ";
    Ciphertext gin31 = 2 * ct_data9 + ct_data41;
    Ciphertext gout31 = ctx.eval_lut(&gin31, or2);
    std::cerr << "\rLUT32   ";
    Ciphertext gin32 = 2 * ct_data26 + ct_data58;
    Ciphertext gout32 = ctx.eval_lut(&gin32, xor2);
    std::cerr << "\rLUT33   ";
    Ciphertext gin33 = 2 * ct_data9 + ct_data41;
    Ciphertext gout33 = ctx.eval_lut(&gin33, nand2);
    std::cerr << "\rLUT34   ";
    Ciphertext gin34 = 2 * ct_data15 + ct_data47;
    Ciphertext gout34 = ctx.eval_lut(&gin34, nand2);
    std::cerr << "\rLUT35   ";
    Ciphertext gin35 = 2 * ct_data8 + ct_data40;
    Ciphertext gout35 = ctx.eval_lut(&gin35, nand2);
    std::cerr << "\rLUT36   ";
    Ciphertext gin36 = 2 * ct_data15 + ct_data47;
    Ciphertext gout36 = ctx.eval_lut(&gin36, or2);
    std::cerr << "\rLUT37   ";
    Ciphertext gin37 = 2 * ct_data23 + ct_data55;
    Ciphertext gout37 = ctx.eval_lut(&gin37, or2);
    std::cerr << "\rLUT38   ";
    Ciphertext gin38 = 2 * ct_data23 + ct_data55;
    Ciphertext gout38 = ctx.eval_lut(&gin38, nand2);
    std::cerr << "\rLUT39   ";
    Ciphertext gin39 = 2 * ct_data7 + ct_data39;
    Ciphertext gout39 = ctx.eval_lut(&gin39, xnor2);
    std::cerr << "\rLUT40   ";
    Ciphertext gin40 = 2 * ct_data2 + ct_data34;
    Ciphertext gout40 = ctx.eval_lut(&gin40, nand2);
    std::cerr << "\rLUT41   ";
    Ciphertext gin41 = 2 * ct_data1 + ct_data33;
    Ciphertext gout41 = ctx.eval_lut(&gin41, nand2);
    std::cerr << "\rLUT42   ";
    Ciphertext gin42 = 2 * ct_data28 + ct_data60;
    Ciphertext gout42 = ctx.eval_lut(&gin42, xor2);
    std::cerr << "\rLUT43   ";
    Ciphertext gin43 = 2 * ct_data18 + ct_data50;
    Ciphertext gout43 = ctx.eval_lut(&gin43, xor2);
    std::cerr << "\rLUT44   ";
    Ciphertext gin44 = 2 * ct_data8 + ct_data40;
    Ciphertext gout44 = ctx.eval_lut(&gin44, xor2);
    std::cerr << "\rLUT45   ";
    Ciphertext gin45 = 2 * ct_data26 + ct_data58;
    Ciphertext gout45 = ctx.eval_lut(&gin45, nand2);
    std::cerr << "\rLUT46   ";
    Ciphertext gin46 = 2 * ct_data1 + ct_data33;
    Ciphertext gout46 = ctx.eval_lut(&gin46, xor2);
    std::cerr << "\rLUT47   ";
    Ciphertext gin47 = 2 * ct_data24 + ct_data56;
    Ciphertext gout47 = ctx.eval_lut(&gin47, nand2);
    std::cerr << "\rLUT48   ";
    Ciphertext gin48 = 2 * ct_data23 + ct_data55;
    Ciphertext gout48 = ctx.eval_lut(&gin48, xor2);
    std::cerr << "\rLUT49   ";
    Ciphertext gin49 = 2 * ct_data21 + ct_data53;
    Ciphertext gout49 = ctx.eval_lut(&gin49, or2);
    std::cerr << "\rLUT50   ";
    Ciphertext gin50 = 2 * ct_data0 + ct_data32;
    Ciphertext gout50 = ctx.eval_lut(&gin50, and2);
    std::cerr << "\rLUT51   ";
    Ciphertext gin51 = 2 * ct_data15 + ct_data47;
    Ciphertext gout51 = ctx.eval_lut(&gin51, xor2);
    std::cerr << "\rLUT52   ";
    Ciphertext gin52 = 2 * ct_data12 + ct_data44;
    Ciphertext gout52 = ctx.eval_lut(&gin52, nand2);
    std::cerr << "\rLUT53   ";
    Ciphertext gin53 = 2 * ct_data21 + ct_data53;
    Ciphertext gout53 = ctx.eval_lut(&gin53, nand2);
    std::cerr << "\rLUT54   ";
    Ciphertext gin54 = 2 * ct_data16 + ct_data48;
    Ciphertext gout54 = ctx.eval_lut(&gin54, xor2);
    std::cerr << "\rLUT55   ";
    Ciphertext gin55 = 2 * ct_data7 + ct_data39;
    Ciphertext gout55 = ctx.eval_lut(&gin55, nand2);
    std::cerr << "\rLUT56   ";
    Ciphertext gin56 = 2 * ct_data7 + ct_data39;
    Ciphertext gout56 = ctx.eval_lut(&gin56, or2);
    std::cerr << "\rLUT57   ";
    Ciphertext gin57 = 2 * ct_data2 + ct_data34;
    Ciphertext gout57 = ctx.eval_lut(&gin57, xor2);
    std::cerr << "\rLUT58   ";
    Ciphertext gin58 = 2 * ct_data16 + ct_data48;
    Ciphertext gout58 = ctx.eval_lut(&gin58, nand2);
    std::cerr << "\rLUT59   ";
    Ciphertext gin59 = 2 * ct_data24 + ct_data56;
    Ciphertext gout59 = ctx.eval_lut(&gin59, xor2);
    std::cerr << "\rLUT60   ";
    Ciphertext gin60 = 2 * ct_data11 + ct_data43;
    Ciphertext gout60 = ctx.eval_lut(&gin60, or2);
    std::cerr << "\rLUT61   ";
    Ciphertext gin61 = 2 * ct_data21 + ct_data53;
    Ciphertext gout61 = ctx.eval_lut(&gin61, xor2);
    std::cerr << "\rLUT62   ";
    Ciphertext gin62 = 2 * ct_data13 + ct_data45;
    Ciphertext gout62 = ctx.eval_lut(&gin62, nand2);
    std::cerr << "\rLUT63   ";
    Ciphertext gin63 = 2 * ct_data29 + ct_data61;
    Ciphertext gout63 = ctx.eval_lut(&gin63, nand2);
    std::cerr << "\rLUT64   ";
    Ciphertext gin64 = 2 * ct_data27 + ct_data59;
    Ciphertext gout64 = ctx.eval_lut(&gin64, xor2);
    std::cerr << "\rLUT65   ";
    Ciphertext gin65 = 2 * ct_data19 + ct_data51;
    Ciphertext gout65 = ctx.eval_lut(&gin65, nand2);
    std::cerr << "\rLUT66   ";
    Ciphertext gin66 = 2 * ct_data10 + ct_data42;
    Ciphertext gout66 = ctx.eval_lut(&gin66, nand2);
    std::cerr << "\rLUT67   ";
    Ciphertext gin67 = 2 * ct_data9 + ct_data41;
    Ciphertext gout67 = ctx.eval_lut(&gin67, xnor2);
    std::cerr << "\rLUT68   ";
    Ciphertext gin68 = 2 * ct_data6 + ct_data38;
    Ciphertext gout68 = ctx.eval_lut(&gin68, xor2);
    std::cerr << "\rLUT69   ";
    Ciphertext gin69 = 2 * ct_data3 + ct_data35;
    Ciphertext gout69 = ctx.eval_lut(&gin69, xor2);
    std::cerr << "\rLUT70   ";
    Ciphertext gin70 = 2 * ct_data6 + ct_data38;
    Ciphertext gout70 = ctx.eval_lut(&gin70, nand2);
    std::cerr << "\rLUT71   ";
    Ciphertext gin71 = 2 * gout50 + gout46;
    Ciphertext gout71 = ctx.eval_lut(&gin71, xor2);
    std::cerr << "\rLUT72   ";
    Ciphertext gin72 = 2 * gout50 + gout46;
    Ciphertext gout72 = ctx.eval_lut(&gin72, nand2);
    std::cerr << "\rLUT73   ";
    Ciphertext gin73 = 2 * gout41 + gout72;
    Ciphertext gout73 = ctx.eval_lut(&gin73, nand2);
    std::cerr << "\rLUT74   ";
    Ciphertext gin74 = 2 * gout73 + gout57;
    Ciphertext gout74 = ctx.eval_lut(&gin74, xor2);
    std::cerr << "\rLUT75   ";
    Ciphertext gin75 = 2 * gout73 + gout57;
    Ciphertext gout75 = ctx.eval_lut(&gin75, nand2);
    std::cerr << "\rLUT76   ";
    Ciphertext gin76 = 2 * gout40 + gout75;
    Ciphertext gout76 = ctx.eval_lut(&gin76, nand2);
    std::cerr << "\rLUT77   ";
    Ciphertext gin77 = 2 * gout76 + gout69;
    Ciphertext gout77 = ctx.eval_lut(&gin77, xor2);
    std::cerr << "\rLUT78   ";
    Ciphertext gin78 = 2 * gout76 + gout69;
    Ciphertext gout78 = ctx.eval_lut(&gin78, nand2);
    std::cerr << "\rLUT79   ";
    Ciphertext gin79 = 2 * gout7 + gout78;
    Ciphertext gout79 = ctx.eval_lut(&gin79, nand2);
    std::cerr << "\rLUT80   ";
    Ciphertext gin80 = 2 * gout79 + gout5;
    Ciphertext gout80 = ctx.eval_lut(&gin80, xor2);
    std::cerr << "\rLUT81   ";
    Ciphertext gin81 = 2 * gout79 + gout5;
    Ciphertext gout81 = ctx.eval_lut(&gin81, nand2);
    std::cerr << "\rLUT82   ";
    Ciphertext gin82 = 2 * gout12 + gout81;
    Ciphertext gout82 = ctx.eval_lut(&gin82, nand2);
    std::cerr << "\rLUT83   ";
    Ciphertext gin83 = 2 * gout82 + gout29;
    Ciphertext gout83 = ctx.eval_lut(&gin83, nand2);
    std::cerr << "\rLUT84   ";
    Ciphertext gin84 = 2 * gout82 + gout29;
    Ciphertext gout84 = ctx.eval_lut(&gin84, xor2);
    std::cerr << "\rLUT85   ";
    Ciphertext gin85 = 2 * gout10 + gout83;
    Ciphertext gout85 = ctx.eval_lut(&gin85, nand2);
    std::cerr << "\rLUT86   ";
    Ciphertext gin86 = 2 * gout68 + gout85;
    Ciphertext gout86 = ctx.eval_lut(&gin86, xor2);
    std::cerr << "\rLUT87   ";
    Ciphertext gin87 = 2 * gout68 + gout85;
    Ciphertext gout87 = ctx.eval_lut(&gin87, nand2);
    std::cerr << "\rLUT88   ";
    Ciphertext gin88 = 2 * gout70 + gout87;
    Ciphertext gout88 = ctx.eval_lut(&gin88, nand2);
    std::cerr << "\rLUT89   ";
    Ciphertext gin89 = 2 * gout56 + gout88;
    Ciphertext gout89 = ctx.eval_lut(&gin89, nand2);
    std::cerr << "\rLUT90   ";
    Ciphertext gin90 = 2 * gout88 + gout39;
    Ciphertext gout90 = ctx.eval_lut(&gin90, xnor2);
    std::cerr << "\rLUT91   ";
    Ciphertext gin91 = 2 * gout55 + gout89;
    Ciphertext gout91 = ctx.eval_lut(&gin91, nand2);
    std::cerr << "\rLUT92   ";
    Ciphertext gin92 = 2 * gout44 + gout91;
    Ciphertext gout92 = ctx.eval_lut(&gin92, nand2);
    std::cerr << "\rLUT93   ";
    Ciphertext gin93 = 2 * gout44 + gout91;
    Ciphertext gout93 = ctx.eval_lut(&gin93, xor2);
    std::cerr << "\rLUT94   ";
    Ciphertext gin94 = 2 * gout35 + gout92;
    Ciphertext gout94 = ctx.eval_lut(&gin94, nand2);
    std::cerr << "\rLUT95   ";
    Ciphertext gin95 = 2 * gout31 + gout94;
    Ciphertext gout95 = ctx.eval_lut(&gin95, nand2);
    std::cerr << "\rLUT96   ";
    Ciphertext gin96 = 2 * gout94 + gout67;
    Ciphertext gout96 = ctx.eval_lut(&gin96, xnor2);
    std::cerr << "\rLUT97   ";
    Ciphertext gin97 = 2 * gout33 + gout95;
    Ciphertext gout97 = ctx.eval_lut(&gin97, nand2);
    std::cerr << "\rLUT98   ";
    Ciphertext gin98 = 2 * gout17 + gout97;
    Ciphertext gout98 = ctx.eval_lut(&gin98, nand2);
    std::cerr << "\rLUT99   ";
    Ciphertext gin99 = 2 * gout17 + gout97;
    Ciphertext gout99 = ctx.eval_lut(&gin99, xor2);
    std::cerr << "\rLUT100   ";
    Ciphertext gin100 = 2 * gout66 + gout98;
    Ciphertext gout100 = ctx.eval_lut(&gin100, nand2);
    std::cerr << "\rLUT101   ";
    Ciphertext gin101 = 2 * gout100 + gout15;
    Ciphertext gout101 = ctx.eval_lut(&gin101, xnor2);
    std::cerr << "\rLUT102   ";
    Ciphertext gin102 = 2 * gout60 + gout100;
    Ciphertext gout102 = ctx.eval_lut(&gin102, nand2);
    std::cerr << "\rLUT103   ";
    Ciphertext gin103 = 2 * gout27 + gout102;
    Ciphertext gout103 = ctx.eval_lut(&gin103, nand2);
    std::cerr << "\rLUT104   ";
    Ciphertext gin104 = 2 * gout0 + gout103;
    Ciphertext gout104 = ctx.eval_lut(&gin104, xor2);
    std::cerr << "\rLUT105   ";
    Ciphertext gin105 = 2 * gout0 + gout103;
    Ciphertext gout105 = ctx.eval_lut(&gin105, nand2);
    std::cerr << "\rLUT106   ";
    Ciphertext gin106 = 2 * gout52 + gout105;
    Ciphertext gout106 = ctx.eval_lut(&gin106, and2);
    std::cerr << "\rLUT107   ";
    Ciphertext gin107 = 2 * gout106 + gout62;
    Ciphertext gout107 = ctx.eval_lut(&gin107, nand2);
    std::cerr << "\rLUT108   ";
    Ciphertext gin108 = 2 * gout106 + gout9;
    Ciphertext gout108 = ctx.eval_lut(&gin108, xnor2);
    std::cerr << "\rLUT109   ";
    Ciphertext gin109 = 2 * gout3 + gout107;
    Ciphertext gout109 = ctx.eval_lut(&gin109, and2);
    std::cerr << "\rLUT110   ";
    Ciphertext gin110 = 2 * gout18 + gout109;
    Ciphertext gout110 = ctx.eval_lut(&gin110, xor2);
    std::cerr << "\rLUT111   ";
    Ciphertext gin111 = 2 * gout18 + gout109;
    Ciphertext gout111 = ctx.eval_lut(&gin111, nand2);
    std::cerr << "\rLUT112   ";
    Ciphertext gin112 = 2 * gout8 + gout111;
    Ciphertext gout112 = ctx.eval_lut(&gin112, and2);
    std::cerr << "\rLUT113   ";
    Ciphertext gin113 = 2 * gout112 + gout34;
    Ciphertext gout113 = ctx.eval_lut(&gin113, nand2);
    std::cerr << "\rLUT114   ";
    Ciphertext gin114 = 2 * gout112 + gout51;
    Ciphertext gout114 = ctx.eval_lut(&gin114, xnor2);
    std::cerr << "\rLUT115   ";
    Ciphertext gin115 = 2 * gout36 + gout113;
    Ciphertext gout115 = ctx.eval_lut(&gin115, and2);
    std::cerr << "\rLUT116   ";
    Ciphertext gin116 = 2 * gout54 + gout115;
    Ciphertext gout116 = ctx.eval_lut(&gin116, nand2);
    std::cerr << "\rLUT117   ";
    Ciphertext gin117 = 2 * gout54 + gout115;
    Ciphertext gout117 = ctx.eval_lut(&gin117, xor2);
    std::cerr << "\rLUT118   ";
    Ciphertext gin118 = 2 * gout58 + gout116;
    Ciphertext gout118 = ctx.eval_lut(&gin118, and2);
    std::cerr << "\rLUT119   ";
    Ciphertext gin119 = 2 * gout118 + gout19;
    Ciphertext gout119 = ctx.eval_lut(&gin119, nand2);
    std::cerr << "\rLUT120   ";
    Ciphertext gin120 = 2 * gout118 + gout21;
    Ciphertext gout120 = ctx.eval_lut(&gin120, xnor2);
    std::cerr << "\rLUT121   ";
    Ciphertext gin121 = 2 * gout20 + gout119;
    Ciphertext gout121 = ctx.eval_lut(&gin121, and2);
    std::cerr << "\rLUT122   ";
    Ciphertext gin122 = 2 * gout43 + gout121;
    Ciphertext gout122 = ctx.eval_lut(&gin122, xor2);
    std::cerr << "\rLUT123   ";
    Ciphertext gin123 = 2 * gout43 + gout121;
    Ciphertext gout123 = ctx.eval_lut(&gin123, nand2);
    std::cerr << "\rLUT124   ";
    Ciphertext gin124 = 2 * gout30 + gout123;
    Ciphertext gout124 = ctx.eval_lut(&gin124, and2);
    std::cerr << "\rLUT125   ";
    Ciphertext gin125 = 2 * gout124 + gout65;
    Ciphertext gout125 = ctx.eval_lut(&gin125, nand2);
    std::cerr << "\rLUT126   ";
    Ciphertext gin126 = 2 * gout124 + gout6;
    Ciphertext gout126 = ctx.eval_lut(&gin126, xnor2);
    std::cerr << "\rLUT127   ";
    Ciphertext gin127 = 2 * gout4 + gout125;
    Ciphertext gout127 = ctx.eval_lut(&gin127, and2);
    std::cerr << "\rLUT128   ";
    Ciphertext gin128 = 2 * gout16 + gout127;
    Ciphertext gout128 = ctx.eval_lut(&gin128, xor2);
    std::cerr << "\rLUT129   ";
    Ciphertext gin129 = 2 * gout16 + gout127;
    Ciphertext gout129 = ctx.eval_lut(&gin129, nand2);
    std::cerr << "\rLUT130   ";
    Ciphertext gin130 = 2 * gout22 + gout129;
    Ciphertext gout130 = ctx.eval_lut(&gin130, and2);
    std::cerr << "\rLUT131   ";
    Ciphertext gin131 = 2 * gout130 + gout53;
    Ciphertext gout131 = ctx.eval_lut(&gin131, nand2);
    std::cerr << "\rLUT132   ";
    Ciphertext gin132 = 2 * gout130 + gout61;
    Ciphertext gout132 = ctx.eval_lut(&gin132, xnor2);
    std::cerr << "\rLUT133   ";
    Ciphertext gin133 = 2 * gout49 + gout131;
    Ciphertext gout133 = ctx.eval_lut(&gin133, and2);
    std::cerr << "\rLUT134   ";
    Ciphertext gin134 = 2 * gout1 + gout133;
    Ciphertext gout134 = ctx.eval_lut(&gin134, nand2);
    std::cerr << "\rLUT135   ";
    Ciphertext gin135 = 2 * gout1 + gout133;
    Ciphertext gout135 = ctx.eval_lut(&gin135, xor2);
    std::cerr << "\rLUT136   ";
    Ciphertext gin136 = 2 * gout2 + gout134;
    Ciphertext gout136 = ctx.eval_lut(&gin136, and2);
    std::cerr << "\rLUT137   ";
    Ciphertext gin137 = 2 * gout136 + gout38;
    Ciphertext gout137 = ctx.eval_lut(&gin137, nand2);
    std::cerr << "\rLUT138   ";
    Ciphertext gin138 = 2 * gout136 + gout48;
    Ciphertext gout138 = ctx.eval_lut(&gin138, xnor2);
    std::cerr << "\rLUT139   ";
    Ciphertext gin139 = 2 * gout37 + gout137;
    Ciphertext gout139 = ctx.eval_lut(&gin139, and2);
    std::cerr << "\rLUT140   ";
    Ciphertext gin140 = 2 * gout59 + gout139;
    Ciphertext gout140 = ctx.eval_lut(&gin140, nand2);
    std::cerr << "\rLUT141   ";
    Ciphertext gin141 = 2 * gout59 + gout139;
    Ciphertext gout141 = ctx.eval_lut(&gin141, xor2);
    std::cerr << "\rLUT142   ";
    Ciphertext gin142 = 2 * gout47 + gout140;
    Ciphertext gout142 = ctx.eval_lut(&gin142, nand2);
    std::cerr << "\rLUT143   ";
    Ciphertext gin143 = 2 * gout142 + gout11;
    Ciphertext gout143 = ctx.eval_lut(&gin143, nand2);
    std::cerr << "\rLUT144   ";
    Ciphertext gin144 = 2 * gout142 + gout11;
    Ciphertext gout144 = ctx.eval_lut(&gin144, xor2);
    std::cerr << "\rLUT145   ";
    Ciphertext gin145 = 2 * gout13 + gout143;
    Ciphertext gout145 = ctx.eval_lut(&gin145, nand2);
    std::cerr << "\rLUT146   ";
    Ciphertext gin146 = 2 * gout145 + gout32;
    Ciphertext gout146 = ctx.eval_lut(&gin146, xor2);
    std::cerr << "\rLUT147   ";
    Ciphertext gin147 = 2 * gout145 + gout32;
    Ciphertext gout147 = ctx.eval_lut(&gin147, nand2);
    std::cerr << "\rLUT148   ";
    Ciphertext gin148 = 2 * gout45 + gout147;
    Ciphertext gout148 = ctx.eval_lut(&gin148, and2);
    std::cerr << "\rLUT149   ";
    Ciphertext gin149 = 2 * gout148 + gout64;
    Ciphertext gout149 = ctx.eval_lut(&gin149, xnor2);
    std::cerr << "\rLUT150   ";
    Ciphertext gin150 = 2 * gout148 + gout14;
    Ciphertext gout150 = ctx.eval_lut(&gin150, nand2);
    std::cerr << "\rLUT151   ";
    Ciphertext gin151 = 2 * gout23 + gout150;
    Ciphertext gout151 = ctx.eval_lut(&gin151, and2);
    std::cerr << "\rLUT152   ";
    Ciphertext gin152 = 2 * gout42 + gout151;
    Ciphertext gout152 = ctx.eval_lut(&gin152, nand2);
    std::cerr << "\rLUT153   ";
    Ciphertext gin153 = 2 * gout42 + gout151;
    Ciphertext gout153 = ctx.eval_lut(&gin153, xor2);
    std::cerr << "\rLUT154   ";
    Ciphertext gin154 = 2 * gout28 + gout152;
    Ciphertext gout154 = ctx.eval_lut(&gin154, nand2);
    std::cerr << "\rLUT155   ";
    Ciphertext gin155 = 2 * gout154 + gout24;
    Ciphertext gout155 = ctx.eval_lut(&gin155, nand2);
    std::cerr << "\rLUT156   ";
    Ciphertext gin156 = 2 * gout154 + gout24;
    Ciphertext gout156 = ctx.eval_lut(&gin156, xor2);
    std::cerr << "\rLUT157   ";
    Ciphertext gin157 = 2 * gout63 + gout155;
    Ciphertext gout157 = ctx.eval_lut(&gin157, nand2);
    std::cerr << "\rLUT158   ";
    Ciphertext gin158 = 2 * gout157 + gout26;
    Ciphertext gout158 = ctx.eval_lut(&gin158, xnor2);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(ctx.decrypt(&gout25)); /* out1 */
    test_out.push_back(ctx.decrypt(&gout71)); /* out2 */
    test_out.push_back(ctx.decrypt(&gout74)); /* out3 */
    test_out.push_back(ctx.decrypt(&gout77)); /* out4 */
    test_out.push_back(ctx.decrypt(&gout80)); /* out5 */
    test_out.push_back(ctx.decrypt(&gout84)); /* out6 */
    test_out.push_back(ctx.decrypt(&gout86)); /* out7 */
    test_out.push_back(ctx.decrypt(&gout90)); /* out8 */
    test_out.push_back(ctx.decrypt(&gout93)); /* out9 */
    test_out.push_back(ctx.decrypt(&gout96)); /* out10 */
    test_out.push_back(ctx.decrypt(&gout99)); /* out11 */
    test_out.push_back(ctx.decrypt(&gout101)); /* out12 */
    test_out.push_back(ctx.decrypt(&gout104)); /* out13 */
    test_out.push_back(ctx.decrypt(&gout108)); /* out14 */
    test_out.push_back(ctx.decrypt(&gout110)); /* out15 */
    test_out.push_back(ctx.decrypt(&gout114)); /* out16 */
    test_out.push_back(ctx.decrypt(&gout117)); /* out17 */
    test_out.push_back(ctx.decrypt(&gout120)); /* out18 */
    test_out.push_back(ctx.decrypt(&gout122)); /* out19 */
    test_out.push_back(ctx.decrypt(&gout126)); /* out20 */
    test_out.push_back(ctx.decrypt(&gout128)); /* out21 */
    test_out.push_back(ctx.decrypt(&gout132)); /* out22 */
    test_out.push_back(ctx.decrypt(&gout135)); /* out23 */
    test_out.push_back(ctx.decrypt(&gout138)); /* out24 */
    test_out.push_back(ctx.decrypt(&gout141)); /* out25 */
    test_out.push_back(ctx.decrypt(&gout144)); /* out26 */
    test_out.push_back(ctx.decrypt(&gout146)); /* out27 */
    test_out.push_back(ctx.decrypt(&gout149)); /* out28 */
    test_out.push_back(ctx.decrypt(&gout153)); /* out29 */
    test_out.push_back(ctx.decrypt(&gout156)); /* out30 */
    test_out.push_back(ctx.decrypt(&gout158)); /* out31 */
    return test_out;
}

static void
BM_structs_1d_boolean(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(tfhe_11_NTT);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(4);

    for (auto _ : state) {
        test_structs_1d_boolean(ctx);
    }
}

BENCHMARK(BM_structs_1d_boolean)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
