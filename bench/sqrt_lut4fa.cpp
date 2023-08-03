#include <benchmark/benchmark.h>
#include "fhe_context.h"
using namespace fhe_deck;


std::vector<long>
test_sqrt_lut4fa(FHEContext& ctx, uint16_t num = 0)
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
    };
    decomp.push_back(ctx.genrate_lut(decomp2));
    fdecomp.push_back(decomp2);
    auto decomp3 = [](long I) -> long {
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
    };
    decomp.push_back(ctx.genrate_lut(decomp3));
    fdecomp.push_back(decomp3);
    auto vdecomp = [fdecomp](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 4; ++i)
            ret.push_back(fdecomp[i](I));
        return ret;
    };

    std::cerr << "\rINV0   ";
    std::vector<Ciphertext> gout0;
    gout0.push_back(ctx.encrypt_public(0));

    std::cerr << "\rINV1   ";
    std::vector<Ciphertext> gout1;
    gout1.push_back(ctx.encrypt_public(1));

    std::cerr << "\rINV2   ";
    std::vector<Ciphertext> gout2;
    gout2.push_back(ctx.encrypt_public(1));

    std::cerr << "\rINV3   ";
    std::vector<Ciphertext> gout3;
    gout3.push_back(ctx.encrypt_public(1));

    std::vector<RotationPoly> lut4;
    std::vector<long (*)(long)> flut4;
    auto lut4idx0 = [](long I) -> long {
        /* GATE 83 (LUT2 _381_ INIT 0x1 PERM 01) */
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
    Ciphertext gin4 = 1 * ct_num2 + 2 * ct_num3;
    std::vector<Ciphertext> gout4 = ctx.eval_lut_amortized(&gin4, lut4);

    std::cerr << "\rINV5   ";
    std::vector<Ciphertext> gout5;
    gout5.push_back(ctx.encrypt_public(1));

    std::cerr << "\rINV6   ";
    std::vector<Ciphertext> gout6;
    gout6.push_back(ctx.encrypt_public(0));

    std::cerr << "\rINV7   ";
    std::vector<Ciphertext> gout7;
    gout7.push_back(ctx.encrypt_public(1));

    std::cerr << "\rINV8   ";
    std::vector<Ciphertext> gout8;
    gout8.push_back(ctx.encrypt_public(1));

    std::cerr << "\rINV9   ";
    std::vector<Ciphertext> gout9;
    gout9.push_back(ctx.encrypt_public(1));

    std::cerr << "\rINV10   ";
    std::vector<Ciphertext> gout10;
    gout10.push_back(ctx.encrypt_public(1));

    std::vector<RotationPoly> lut11;
    std::vector<long (*)(long)> flut11;
    auto lut11idx0 = [](long I) -> long {
        /* GATE 92 (LUT2 _390_ INIT 0x1 PERM 01) */
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
    Ciphertext gin11 = 1 * ct_num1 + 2 * ct_num0;
    std::vector<Ciphertext> gout11 = ctx.eval_lut_amortized(&gin11, lut11);

    std::cerr << "\rINV12   ";
    std::vector<Ciphertext> gout12;
    gout12.push_back(ctx.encrypt_public(1));

    std::cerr << "\rINV13   ";
    std::vector<Ciphertext> gout13;
    gout13.push_back(ctx.encrypt_public(1));

    std::cerr << "\rINV14   ";
    std::vector<Ciphertext> gout14;
    gout14.push_back(ctx.encrypt_public(1));

    std::cerr << "\rINV15   ";
    std::vector<Ciphertext> gout15;
    gout15.push_back(ctx.encrypt_public(1));

    std::cerr << "\rINV16   ";
    std::vector<Ciphertext> gout16;
    gout16.push_back(ctx.encrypt_public(1));

    std::vector<RotationPoly> lut17;
    std::vector<long (*)(long)> flut17;
    auto lut17idx0 = [](long I) -> long {
        /* GATE 3 (LUT4 _301_ INIT 0xe PERM 3012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
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
    };
    lut17.push_back(ctx.genrate_lut(lut17idx0));
    flut17.push_back(lut17idx0);
    auto lut17idx1 = [](long I) -> long {
        /* GATE 1 (LUT2 _299_ INIT 0x4 PERM 21) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    };
    lut17.push_back(ctx.genrate_lut(lut17idx1));
    flut17.push_back(lut17idx1);
    auto lut17idx2 = [](long I) -> long {
        /* GATE 2 (LUT2 _300_ INIT 0x8 PERM 12) */
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
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    };
    lut17.push_back(ctx.genrate_lut(lut17idx2));
    flut17.push_back(lut17idx2);
    auto fvec17 = [flut17](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 3; ++i)
            ret.push_back(flut17[i](I));
        return ret;
    };

    std::cerr << "\rLUT17   ";
    Ciphertext gin17 = 1 * ct_num12 + 2 * ct_num14 + 4 * ct_num15 + 8 * ct_num13;
    std::vector<Ciphertext> gout17 = ctx.eval_lut_amortized(&gin17, lut17);

    std::cerr << "\rINV18   ";
    std::vector<Ciphertext> gout18;
    gout18.push_back(ctx.encrypt_public(1));

    std::cerr << "\rINV19   ";
    std::vector<Ciphertext> gout19;
    gout19.push_back(ctx.encrypt_public(0));

    std::cerr << "\rINV20   ";
    std::vector<Ciphertext> gout20;
    gout20.push_back(ctx.encrypt_public(1));

    std::cerr << "\rINV21   ";
    std::vector<Ciphertext> gout21;
    gout21.push_back(ctx.encrypt_public(1));

    std::vector<RotationPoly> lut22;
    std::vector<long (*)(long)> flut22;
    auto lut22idx0 = [](long I) -> long {
        /* GATE 55 (LUT2 _353_ INIT 0x1 PERM 10) */
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
    Ciphertext gin22 = 1 * ct_num5 + 2 * ct_num4;
    std::vector<Ciphertext> gout22 = ctx.eval_lut_amortized(&gin22, lut22);

    std::cerr << "\rINV23   ";
    std::vector<Ciphertext> gout23;
    gout23.push_back(ctx.encrypt_public(0));

    std::cerr << "\rINV24   ";
    std::vector<Ciphertext> gout24;
    gout24.push_back(ctx.encrypt_public(1));

    std::cerr << "\rINV25   ";
    std::vector<Ciphertext> gout25;
    gout25.push_back(ctx.encrypt_public(1));

    std::cerr << "\rINV26   ";
    std::vector<Ciphertext> gout26;
    gout26.push_back(1 - gout17[1]);

    std::cerr << "\rINV27   ";
    std::vector<Ciphertext> gout27;
    gout27.push_back(ctx.encrypt_public(1));

    std::vector<RotationPoly> lut28;
    std::vector<long (*)(long)> flut28;
    auto lut28idx0 = [](long I) -> long {
        /* GATE 20 (LUT2 _318_ INIT 0x1 PERM 10) */
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
    Ciphertext gin28 = 1 * ct_num9 + 2 * ct_num8;
    std::vector<Ciphertext> gout28 = ctx.eval_lut_amortized(&gin28, lut28);

    std::cerr << "\rINV29   ";
    std::vector<Ciphertext> gout29;
    gout29.push_back(1 - gout17[0]);

    std::cerr << "\rINV30   ";
    std::vector<Ciphertext> gout30;
    gout30.push_back(ctx.encrypt_public(1));

    std::cerr << "\rINV31   ";
    std::vector<Ciphertext> gout31;
    gout31.push_back(ctx.encrypt_public(1));

    std::cerr << "\rINV32   ";
    std::vector<Ciphertext> gout32;
    gout32.push_back(ctx.encrypt_public(0));

    std::cerr << "\rINV33   ";
    std::vector<Ciphertext> gout33;
    gout33.push_back(1 - gout17[0]);

    std::cerr << "\rINV34   ";
    std::vector<Ciphertext> gout34;
    gout34.push_back(ctx.encrypt_public(1));

    std::cerr << "\rINV35   ";
    std::vector<Ciphertext> gout35;
    gout35.push_back(ctx.encrypt_public(1));

    std::cerr << "\rINV36   ";
    std::vector<Ciphertext> gout36;
    gout36.push_back(ctx.encrypt_public(1));

    std::vector<RotationPoly> lut37;
    std::vector<long (*)(long)> flut37;
    auto lut37idx0 = [](long I) -> long {
        /* GATE 37 (LUT2 _335_ INIT 0x1 PERM 10) */
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
    Ciphertext gin37 = 1 * ct_num7 + 2 * ct_num6;
    std::vector<Ciphertext> gout37 = ctx.eval_lut_amortized(&gin37, lut37);

    std::cerr << "\rINV38   ";
    std::vector<Ciphertext> gout38;
    gout38.push_back(ctx.encrypt_public(1));

    std::cerr << "\rINV39   ";
    std::vector<Ciphertext> gout39;
    gout39.push_back(ctx.encrypt_public(1));

    std::cerr << "\rINV40   ";
    std::vector<Ciphertext> gout40;
    gout40.push_back(ctx.encrypt_public(1));

    std::cerr << "\rINV41   ";
    std::vector<Ciphertext> gout41;
    gout41.push_back(ctx.encrypt_public(0));

    std::cerr << "\rINV42   ";
    std::vector<Ciphertext> gout42;
    gout42.push_back(1 - gout17[1]);

    std::cerr << "\rINV43   ";
    std::vector<Ciphertext> gout43;
    gout43.push_back(1 - gout17[1]);

    std::cerr << "\rINV44   ";
    std::vector<Ciphertext> gout44;
    gout44.push_back(1 - gout17[0]);

    std::cerr << "\rINV45   ";
    std::vector<Ciphertext> gout45;
    gout45.push_back(1 - gout17[1]);

    std::cerr << "\rINV46   ";
    std::vector<Ciphertext> gout46;
    gout46.push_back(1 - gout17[0]);

    std::cerr << "\rINV47   ";
    std::vector<Ciphertext> gout47;
    gout47.push_back(1 - gout17[1]);

    std::cerr << "\rINV48   ";
    std::vector<Ciphertext> gout48;
    gout48.push_back(1 - gout17[1]);

    std::cerr << "\rINV49   ";
    std::vector<Ciphertext> gout49;
    gout49.push_back(1 - gout17[0]);

    std::cerr << "\rFA50    ";
    Ciphertext gin50 = 1 + 1 * ct_num12 + 2 * ct_num13 + 4 * gout17[2] + 1 * gout6[0] + 2 * gout39[0] + 4 * gout42[0];
    std::vector<Ciphertext> gout50 = ctx.eval_lut_amortized(&gin50, decomp);

    std::vector<RotationPoly> lut51;
    std::vector<long (*)(long)> flut51;
    auto lut51idx0 = [](long I) -> long {
        /* GATE 4 (LUT3 _302_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin51 = 1 * ct_num12 + 2 * gout50[0] + 4 * gout17[0];
    std::vector<Ciphertext> gout51 = ctx.eval_lut_amortized(&gin51, lut51);

    std::vector<RotationPoly> lut52;
    std::vector<long (*)(long)> flut52;
    auto lut52idx0 = [](long I) -> long {
        /* GATE 6 (LUT3 _304_ INIT 0xf8 PERM 201) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin52 = 1 * gout50[2] + 2 * gout17[2] + 4 * gout17[0];
    std::vector<Ciphertext> gout52 = ctx.eval_lut_amortized(&gin52, lut52);

    std::cerr << "\rFA53    ";
    Ciphertext gin53 = 1 + 1 * ct_num10 + 2 * ct_num11 + 4 * gout51[0] + 1 * gout32[0] + 2 * gout25[0] + 4 * gout46[0];
    std::vector<Ciphertext> gout53 = ctx.eval_lut_amortized(&gin53, decomp);

    std::cerr << "\rFA54    ";
    Ciphertext gin54 = gout50[3] + 1 * ct_num15 + 1 * gout36[0];
    std::vector<Ciphertext> gout54 = ctx.eval_lut_amortized(&gin54, decomp);

    std::vector<RotationPoly> lut55;
    std::vector<long (*)(long)> flut55;
    auto lut55idx0 = [](long I) -> long {
        /* GATE 10 (LUT4 _308_ INIT 0xe0ee PERM 2103) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 1;
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
    Ciphertext gin55 = 1 * gout50[0] + 2 * ct_num11 + 4 * ct_num10 + 8 * gout17[0];
    std::vector<Ciphertext> gout55 = ctx.eval_lut_amortized(&gin55, lut55);

    std::vector<RotationPoly> lut56;
    std::vector<long (*)(long)> flut56;
    auto lut56idx0 = [](long I) -> long {
        /* GATE 5 (LUT3 _303_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin56 = 1 * ct_num13 + 2 * gout50[1] + 4 * gout17[0];
    std::vector<Ciphertext> gout56 = ctx.eval_lut_amortized(&gin56, lut56);

    std::vector<RotationPoly> lut57;
    std::vector<long (*)(long)> flut57;
    auto lut57idx0 = [](long I) -> long {
        /* GATE 111 (LUT4 _409_ INIT 0x110f PERM 2103) */
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
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
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
    Ciphertext gin57 = 1 * ct_num12 + 2 * gout50[2] + 4 * gout50[1] + 8 * gout17[0];
    std::vector<Ciphertext> gout57 = ctx.eval_lut_amortized(&gin57, lut57);

    std::vector<RotationPoly> lut58;
    std::vector<long (*)(long)> flut58;
    auto lut58idx0 = [](long I) -> long {
        /* GATE 8 (LUT4 _306_ INIT 0xe00 PERM 3120) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
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
    Ciphertext gin58 = 1 * gout54[0] + 2 * ct_num12 + 4 * ct_num14 + 8 * ct_num13;
    std::vector<Ciphertext> gout58 = ctx.eval_lut_amortized(&gin58, lut58);

    std::vector<RotationPoly> lut59;
    std::vector<long (*)(long)> flut59;
    auto lut59idx0 = [](long I) -> long {
        /* GATE 9 (LUT4 _307_ INIT 0xb PERM 3120) */
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
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    };
    lut59.push_back(ctx.genrate_lut(lut59idx0));
    flut59.push_back(lut59idx0);
    auto lut59idx1 = [](long I) -> long {
        /* GATE 7 (LUT2 _305_ INIT 0xe PERM 02) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 1;
            case 13: return 1;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    };
    lut59.push_back(ctx.genrate_lut(lut59idx1));
    flut59.push_back(lut59idx1);
    auto fvec59 = [flut59](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut59[i](I));
        return ret;
    };

    std::cerr << "\rLUT59   ";
    Ciphertext gin59 = 1 * gout58[0] + 2 * ct_num14 + 4 * ct_num15 + 8 * ct_num13;
    std::vector<Ciphertext> gout59 = ctx.eval_lut_amortized(&gin59, lut59);

    std::vector<RotationPoly> lut60;
    std::vector<long (*)(long)> flut60;
    auto lut60idx0 = [](long I) -> long {
        /* GATE 112 (LUT3 _410_ INIT 0xb0 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
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
    Ciphertext gin60 = 1 * gout55[0] + 2 * gout57[0] + 4 * gout59[0];
    std::vector<Ciphertext> gout60 = ctx.eval_lut_amortized(&gin60, lut60);

    std::cerr << "\rINV61   ";
    std::vector<Ciphertext> gout61;
    gout61.push_back(1 - gout60[0]);

    std::cerr << "\rINV62   ";
    std::vector<Ciphertext> gout62;
    gout62.push_back(1 - gout60[0]);

    std::cerr << "\rFA63    ";
    Ciphertext gin63 = gout53[3] + 1 * gout56[0] + 2 * gout52[0] + 4 * gout59[1] + 1 * gout47[0] + 2 * gout16[0] + 4 * gout2[0];
    std::vector<Ciphertext> gout63 = ctx.eval_lut_amortized(&gin63, decomp);

    std::vector<RotationPoly> lut64;
    std::vector<long (*)(long)> flut64;
    auto lut64idx0 = [](long I) -> long {
        /* GATE 14 (LUT3 _312_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin64 = 1 * gout56[0] + 2 * gout63[0] + 4 * gout60[0];
    std::vector<Ciphertext> gout64 = ctx.eval_lut_amortized(&gin64, lut64);

    std::cerr << "\rINV65   ";
    std::vector<Ciphertext> gout65;
    gout65.push_back(1 - gout60[0]);

    std::vector<RotationPoly> lut66;
    std::vector<long (*)(long)> flut66;
    auto lut66idx0 = [](long I) -> long {
        /* GATE 12 (LUT3 _310_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin66 = 1 * ct_num11 + 2 * gout53[1] + 4 * gout60[0];
    std::vector<Ciphertext> gout66 = ctx.eval_lut_amortized(&gin66, lut66);

    std::cerr << "\rINV67   ";
    std::vector<Ciphertext> gout67;
    gout67.push_back(1 - gout60[0]);

    std::vector<RotationPoly> lut68;
    std::vector<long (*)(long)> flut68;
    auto lut68idx0 = [](long I) -> long {
        /* GATE 21 (LUT4 _319_ INIT 0x3500 PERM 0123) */
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
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    };
    lut68.push_back(ctx.genrate_lut(lut68idx0));
    flut68.push_back(lut68idx0);
    auto lut68idx1 = [](long I) -> long {
        /* GATE 13 (LUT3 _311_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    };
    lut68.push_back(ctx.genrate_lut(lut68idx1));
    flut68.push_back(lut68idx1);
    auto fvec68 = [flut68](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut68[i](I));
        return ret;
    };

    std::cerr << "\rLUT68   ";
    Ciphertext gin68 = 1 * gout51[0] + 2 * gout53[2] + 4 * gout60[0] + 8 * gout17[1];
    std::vector<Ciphertext> gout68 = ctx.eval_lut_amortized(&gin68, lut68);

    std::vector<RotationPoly> lut69;
    std::vector<long (*)(long)> flut69;
    auto lut69idx0 = [](long I) -> long {
        /* GATE 19 (LUT4 _317_ INIT 0xcaf PERM 2130) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    };
    lut69.push_back(ctx.genrate_lut(lut69idx0));
    flut69.push_back(lut69idx0);
    auto lut69idx1 = [](long I) -> long {
        /* GATE 11 (LUT3 _309_ INIT 0xca PERM 123) */
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
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin69 = 1 * gout28[0] + 2 * ct_num10 + 4 * gout53[0] + 8 * gout60[0];
    std::vector<Ciphertext> gout69 = ctx.eval_lut_amortized(&gin69, lut69);

    std::vector<RotationPoly> lut70;
    std::vector<long (*)(long)> flut70;
    auto lut70idx0 = [](long I) -> long {
        /* GATE 15 (LUT3 _313_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin70 = 1 * gout52[0] + 2 * gout63[1] + 4 * gout60[0];
    std::vector<Ciphertext> gout70 = ctx.eval_lut_amortized(&gin70, lut70);

    std::vector<RotationPoly> lut71;
    std::vector<long (*)(long)> flut71;
    auto lut71idx0 = [](long I) -> long {
        /* GATE 16 (LUT3 _314_ INIT 0xf8 PERM 201) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin71 = 1 * gout63[2] + 2 * gout59[1] + 4 * gout60[0];
    std::vector<Ciphertext> gout71 = ctx.eval_lut_amortized(&gin71, lut71);

    std::cerr << "\rFA72    ";
    Ciphertext gin72 = 1 + 1 * ct_num8 + 2 * ct_num9 + 4 * gout69[1] + 1 * gout41[0] + 2 * gout35[0] + 4 * gout65[0];
    std::vector<Ciphertext> gout72 = ctx.eval_lut_amortized(&gin72, decomp);

    std::vector<RotationPoly> lut73;
    std::vector<long (*)(long)> flut73;
    auto lut73idx0 = [](long I) -> long {
        /* GATE 18 (LUT4 _316_ INIT 0xb2 PERM 2301) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
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
    Ciphertext gin73 = 1 * gout69[0] + 2 * gout68[0] + 4 * gout66[0] + 8 * gout17[0];
    std::vector<Ciphertext> gout73 = ctx.eval_lut_amortized(&gin73, lut73);

    std::cerr << "\rFA74    ";
    Ciphertext gin74 = gout72[3] + 1 * gout66[0] + 2 * gout68[1] + 4 * gout64[0] + 1 * gout29[0] + 2 * gout26[0] + 4 * gout12[0];
    std::vector<Ciphertext> gout74 = ctx.eval_lut_amortized(&gin74, decomp);

    std::vector<RotationPoly> lut75;
    std::vector<long (*)(long)> flut75;
    auto lut75idx0 = [](long I) -> long {
        /* GATE 22 (LUT4 _320_ INIT 0xb PERM 3012) */
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
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
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
    Ciphertext gin75 = 1 * gout68[1] + 2 * gout70[0] + 4 * gout64[0] + 8 * gout17[1];
    std::vector<Ciphertext> gout75 = ctx.eval_lut_amortized(&gin75, lut75);

    std::vector<RotationPoly> lut76;
    std::vector<long (*)(long)> flut76;
    auto lut76idx0 = [](long I) -> long {
        /* GATE 17 (LUT3 _315_ INIT 0xd PERM 102) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
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
    Ciphertext gin76 = 1 * gout73[0] + 2 * gout75[0] + 4 * gout71[0];
    std::vector<Ciphertext> gout76 = ctx.eval_lut_amortized(&gin76, lut76);

    std::vector<RotationPoly> lut77;
    std::vector<long (*)(long)> flut77;
    auto lut77idx0 = [](long I) -> long {
        /* GATE 40 (LUT4 _338_ INIT 0xc0a PERM 0132) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
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
    };
    lut77.push_back(ctx.genrate_lut(lut77idx0));
    flut77.push_back(lut77idx0);
    auto lut77idx1 = [](long I) -> long {
        /* GATE 26 (LUT3 _324_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    };
    lut77.push_back(ctx.genrate_lut(lut77idx1));
    flut77.push_back(lut77idx1);
    auto fvec77 = [flut77](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut77[i](I));
        return ret;
    };

    std::cerr << "\rLUT77   ";
    Ciphertext gin77 = 1 * gout66[0] + 2 * gout74[0] + 4 * gout76[0] + 8 * gout17[1];
    std::vector<Ciphertext> gout77 = ctx.eval_lut_amortized(&gin77, lut77);

    std::cerr << "\rINV78   ";
    std::vector<Ciphertext> gout78;
    gout78.push_back(1 - gout76[0]);

    std::cerr << "\rINV79   ";
    std::vector<Ciphertext> gout79;
    gout79.push_back(1 - gout76[0]);

    std::vector<RotationPoly> lut80;
    std::vector<long (*)(long)> flut80;
    auto lut80idx0 = [](long I) -> long {
        /* GATE 24 (LUT3 _322_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin80 = 1 * ct_num9 + 2 * gout72[1] + 4 * gout76[0];
    std::vector<Ciphertext> gout80 = ctx.eval_lut_amortized(&gin80, lut80);

    std::vector<RotationPoly> lut81;
    std::vector<long (*)(long)> flut81;
    auto lut81idx0 = [](long I) -> long {
        /* GATE 33 (LUT2 _331_ INIT 0x4 PERM 01) */
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
    Ciphertext gin81 = 1 * gout77[1] + 2 * gout17[1];
    std::vector<Ciphertext> gout81 = ctx.eval_lut_amortized(&gin81, lut81);

    std::cerr << "\rFA82    ";
    Ciphertext gin82 = gout74[3] + 1 * gout70[0] + 2 * gout71[0] + 1 * gout24[0] + 2 * gout10[0];
    std::vector<Ciphertext> gout82 = ctx.eval_lut_amortized(&gin82, decomp);

    std::vector<RotationPoly> lut83;
    std::vector<long (*)(long)> flut83;
    auto lut83idx0 = [](long I) -> long {
        /* GATE 28 (LUT3 _326_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin83 = 1 * gout64[0] + 2 * gout74[2] + 4 * gout76[0];
    std::vector<Ciphertext> gout83 = ctx.eval_lut_amortized(&gin83, lut83);

    std::cerr << "\rINV84   ";
    std::vector<Ciphertext> gout84;
    gout84.push_back(1 - gout76[0]);

    std::vector<RotationPoly> lut85;
    std::vector<long (*)(long)> flut85;
    auto lut85idx0 = [](long I) -> long {
        /* GATE 36 (LUT4 _334_ INIT 0xf530 PERM 1230) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 1;
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
    Ciphertext gin85 = 1 * gout37[0] + 2 * ct_num8 + 4 * gout72[0] + 8 * gout76[0];
    std::vector<Ciphertext> gout85 = ctx.eval_lut_amortized(&gin85, lut85);

    std::vector<RotationPoly> lut86;
    std::vector<long (*)(long)> flut86;
    auto lut86idx0 = [](long I) -> long {
        /* GATE 23 (LUT3 _321_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin86 = 1 * ct_num8 + 2 * gout72[0] + 4 * gout76[0];
    std::vector<Ciphertext> gout86 = ctx.eval_lut_amortized(&gin86, lut86);

    std::vector<RotationPoly> lut87;
    std::vector<long (*)(long)> flut87;
    auto lut87idx0 = [](long I) -> long {
        /* GATE 27 (LUT3 _325_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin87 = 1 * gout68[1] + 2 * gout74[1] + 4 * gout76[0];
    std::vector<Ciphertext> gout87 = ctx.eval_lut_amortized(&gin87, lut87);

    std::vector<RotationPoly> lut88;
    std::vector<long (*)(long)> flut88;
    auto lut88idx0 = [](long I) -> long {
        /* GATE 38 (LUT4 _336_ INIT 0x3500 PERM 0123) */
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
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    };
    lut88.push_back(ctx.genrate_lut(lut88idx0));
    flut88.push_back(lut88idx0);
    auto lut88idx1 = [](long I) -> long {
        /* GATE 25 (LUT3 _323_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    };
    lut88.push_back(ctx.genrate_lut(lut88idx1));
    flut88.push_back(lut88idx1);
    auto fvec88 = [flut88](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut88[i](I));
        return ret;
    };

    std::cerr << "\rLUT88   ";
    Ciphertext gin88 = 1 * gout69[1] + 2 * gout72[2] + 4 * gout76[0] + 8 * gout17[0];
    std::vector<Ciphertext> gout88 = ctx.eval_lut_amortized(&gin88, lut88);

    std::vector<RotationPoly> lut89;
    std::vector<long (*)(long)> flut89;
    auto lut89idx0 = [](long I) -> long {
        /* GATE 30 (LUT4 _328_ INIT 0xffb0 PERM 0123) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
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
    Ciphertext gin89 = 1 * gout73[0] + 2 * gout75[0] + 4 * gout82[1] + 8 * gout71[0];
    std::vector<Ciphertext> gout89 = ctx.eval_lut_amortized(&gin89, lut89);

    std::vector<RotationPoly> lut90;
    std::vector<long (*)(long)> flut90;
    auto lut90idx0 = [](long I) -> long {
        /* GATE 29 (LUT3 _327_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin90 = 1 * gout70[0] + 2 * gout82[0] + 4 * gout76[0];
    std::vector<Ciphertext> gout90 = ctx.eval_lut_amortized(&gin90, lut90);

    std::vector<RotationPoly> lut91;
    std::vector<long (*)(long)> flut91;
    auto lut91idx0 = [](long I) -> long {
        /* GATE 39 (LUT4 _337_ INIT 0x1 PERM 1320) */
        switch (I) {
            case  0: return 1;
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
            case 15: return 0;
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
    Ciphertext gin91 = 1 * gout77[0] + 2 * gout87[0] + 4 * gout90[0] + 8 * gout83[0];
    std::vector<Ciphertext> gout91 = ctx.eval_lut_amortized(&gin91, lut91);

    std::cerr << "\rFA92    ";
    Ciphertext gin92 = 1 + 1 * ct_num6 + 2 * ct_num7 + 4 * gout86[0] + 1 * gout23[0] + 2 * gout21[0] + 4 * gout78[0];
    std::vector<Ciphertext> gout92 = ctx.eval_lut_amortized(&gin92, decomp);

    std::vector<RotationPoly> lut93;
    std::vector<long (*)(long)> flut93;
    auto lut93idx0 = [](long I) -> long {
        /* GATE 35 (LUT4 _333_ INIT 0x2b PERM 2031) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
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
    Ciphertext gin93 = 1 * gout85[0] + 2 * gout88[0] + 4 * gout80[0] + 8 * gout60[0];
    std::vector<Ciphertext> gout93 = ctx.eval_lut_amortized(&gin93, lut93);

    std::cerr << "\rFA94    ";
    Ciphertext gin94 = gout92[3] + 1 * gout80[0] + 2 * gout88[1] + 4 * gout77[1] + 1 * gout61[0] + 2 * gout49[0] + 4 * gout48[0];
    std::vector<Ciphertext> gout94 = ctx.eval_lut_amortized(&gin94, decomp);

    std::vector<RotationPoly> lut95;
    std::vector<long (*)(long)> flut95;
    auto lut95idx0 = [](long I) -> long {
        /* GATE 34 (LUT2 _332_ INIT 0x4 PERM 10) */
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
    Ciphertext gin95 = 1 * gout88[1] + 2 * gout17[0];
    std::vector<Ciphertext> gout95 = ctx.eval_lut_amortized(&gin95, lut95);

    std::vector<RotationPoly> lut96;
    std::vector<long (*)(long)> flut96;
    auto lut96idx0 = [](long I) -> long {
        /* GATE 32 (LUT4 _330_ INIT 0xf100 PERM 0123) */
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
            case 12: return 1;
            case 13: return 1;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin96 = 1 * gout95[0] + 2 * gout93[0] + 4 * gout81[0] + 8 * gout91[0];
    std::vector<Ciphertext> gout96 = ctx.eval_lut_amortized(&gin96, lut96);

    std::cerr << "\rFA97    ";
    Ciphertext gin97 = gout94[3] + 1 * gout87[0] + 2 * gout83[0] + 4 * gout90[0] + 1 * gout40[0] + 2 * gout15[0] + 4 * gout14[0];
    std::vector<Ciphertext> gout97 = ctx.eval_lut_amortized(&gin97, decomp);

    std::cerr << "\rFA98    ";
    Ciphertext gin98 = gout97[3] + 1 * gout89[0] + 1 * gout30[0];
    std::vector<Ciphertext> gout98 = ctx.eval_lut_amortized(&gin98, decomp);

    std::vector<RotationPoly> lut99;
    std::vector<long (*)(long)> flut99;
    auto lut99idx0 = [](long I) -> long {
        /* GATE 50 (LUT3 _348_ INIT 0xf4 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin99 = 1 * gout96[0] + 2 * gout98[0] + 4 * gout89[0];
    std::vector<Ciphertext> gout99 = ctx.eval_lut_amortized(&gin99, lut99);

    std::vector<RotationPoly> lut100;
    std::vector<long (*)(long)> flut100;
    auto lut100idx0 = [](long I) -> long {
        /* GATE 43 (LUT4 _341_ INIT 0xccca PERM 0123) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
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
    Ciphertext gin100 = 1 * gout92[2] + 2 * gout86[0] + 4 * gout96[0] + 8 * gout89[0];
    std::vector<Ciphertext> gout100 = ctx.eval_lut_amortized(&gin100, lut100);

    std::vector<RotationPoly> lut101;
    std::vector<long (*)(long)> flut101;
    auto lut101idx0 = [](long I) -> long {
        /* GATE 47 (LUT4 _345_ INIT 0xf044 PERM 2013) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
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
    Ciphertext gin101 = 1 * gout97[0] + 2 * gout87[0] + 4 * gout96[0] + 8 * gout89[0];
    std::vector<Ciphertext> gout101 = ctx.eval_lut_amortized(&gin101, lut101);

    std::vector<RotationPoly> lut102;
    std::vector<long (*)(long)> flut102;
    auto lut102idx0 = [](long I) -> long {
        /* GATE 49 (LUT4 _347_ INIT 0xccca PERM 0123) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
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
    Ciphertext gin102 = 1 * gout97[2] + 2 * gout90[0] + 4 * gout96[0] + 8 * gout89[0];
    std::vector<Ciphertext> gout102 = ctx.eval_lut_amortized(&gin102, lut102);

    std::vector<RotationPoly> lut103;
    std::vector<long (*)(long)> flut103;
    auto lut103idx0 = [](long I) -> long {
        /* GATE 42 (LUT4 _340_ INIT 0xccca PERM 0123) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
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
    Ciphertext gin103 = 1 * gout92[1] + 2 * ct_num7 + 4 * gout96[0] + 8 * gout89[0];
    std::vector<Ciphertext> gout103 = ctx.eval_lut_amortized(&gin103, lut103);

    std::vector<RotationPoly> lut104;
    std::vector<long (*)(long)> flut104;
    auto lut104idx0 = [](long I) -> long {
        /* GATE 44 (LUT4 _342_ INIT 0xccca PERM 0123) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
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
    };
    lut104.push_back(ctx.genrate_lut(lut104idx0));
    flut104.push_back(lut104idx0);
    auto lut104idx1 = [](long I) -> long {
        /* GATE 31 (LUT2 _329_ INIT 0x1 PERM 23) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
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
    Ciphertext gin104 = 1 * gout94[0] + 2 * gout80[0] + 4 * gout96[0] + 8 * gout89[0];
    std::vector<Ciphertext> gout104 = ctx.eval_lut_amortized(&gin104, lut104);

    std::vector<RotationPoly> lut105;
    std::vector<long (*)(long)> flut105;
    auto lut105idx0 = [](long I) -> long {
        /* GATE 54 (LUT4 _352_ INIT 0xf530 PERM 1230) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    };
    lut105.push_back(ctx.genrate_lut(lut105idx0));
    flut105.push_back(lut105idx0);
    auto lut105idx1 = [](long I) -> long {
        /* GATE 41 (LUT3 _339_ INIT 0xca PERM 123) */
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
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin105 = 1 * gout22[0] + 2 * ct_num6 + 4 * gout92[0] + 8 * gout104[1];
    std::vector<Ciphertext> gout105 = ctx.eval_lut_amortized(&gin105, lut105);

    std::vector<RotationPoly> lut106;
    std::vector<long (*)(long)> flut106;
    auto lut106idx0 = [](long I) -> long {
        /* GATE 46 (LUT3 _344_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin106 = 1 * gout77[1] + 2 * gout94[2] + 4 * gout104[1];
    std::vector<Ciphertext> gout106 = ctx.eval_lut_amortized(&gin106, lut106);

    std::vector<RotationPoly> lut107;
    std::vector<long (*)(long)> flut107;
    auto lut107idx0 = [](long I) -> long {
        /* GATE 48 (LUT3 _346_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin107 = 1 * gout83[0] + 2 * gout97[1] + 4 * gout104[1];
    std::vector<Ciphertext> gout107 = ctx.eval_lut_amortized(&gin107, lut107);

    std::vector<RotationPoly> lut108;
    std::vector<long (*)(long)> flut108;
    auto lut108idx0 = [](long I) -> long {
        /* GATE 61 (LUT4 _359_ INIT 0x305 PERM 1203) */
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
            case 10: return 1;
            case 11: return 0;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    };
    lut108.push_back(ctx.genrate_lut(lut108idx0));
    flut108.push_back(lut108idx0);
    auto fvec108 = [flut108](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut108[i](I));
        return ret;
    };

    std::cerr << "\rLUT108   ";
    Ciphertext gin108 = 1 * gout102[0] + 2 * gout83[0] + 4 * gout97[1] + 8 * gout104[1];
    std::vector<Ciphertext> gout108 = ctx.eval_lut_amortized(&gin108, lut108);

    std::vector<RotationPoly> lut109;
    std::vector<long (*)(long)> flut109;
    auto lut109idx0 = [](long I) -> long {
        /* GATE 60 (LUT4 _358_ INIT 0xc0a PERM 0132) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
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
    };
    lut109.push_back(ctx.genrate_lut(lut109idx0));
    flut109.push_back(lut109idx0);
    auto lut109idx1 = [](long I) -> long {
        /* GATE 45 (LUT3 _343_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
            default: assert(0);
        };
    };
    lut109.push_back(ctx.genrate_lut(lut109idx1));
    flut109.push_back(lut109idx1);
    auto fvec109 = [flut109](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut109[i](I));
        return ret;
    };

    std::cerr << "\rLUT109   ";
    Ciphertext gin109 = 1 * gout88[1] + 2 * gout94[1] + 4 * gout104[1] + 8 * gout17[1];
    std::vector<Ciphertext> gout109 = ctx.eval_lut_amortized(&gin109, lut109);

    std::vector<RotationPoly> lut110;
    std::vector<long (*)(long)> flut110;
    auto lut110idx0 = [](long I) -> long {
        /* GATE 56 (LUT4 _354_ INIT 0xb0bb PERM 1302) */
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
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
            default: assert(0);
        };
    };
    lut110.push_back(ctx.genrate_lut(lut110idx0));
    flut110.push_back(lut110idx0);
    auto lut110idx1 = [](long I) -> long {
        /* GATE 53 (LUT2 _351_ INIT 0x4 PERM 20) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
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
    Ciphertext gin110 = 1 * gout103[0] + 2 * gout100[0] + 4 * gout76[0] + 8 * gout60[0];
    std::vector<Ciphertext> gout110 = ctx.eval_lut_amortized(&gin110, lut110);

    std::cerr << "\rINV111   ";
    std::vector<Ciphertext> gout111;
    gout111.push_back(1 - gout104[1]);

    std::cerr << "\rINV112   ";
    std::vector<Ciphertext> gout112;
    gout112.push_back(1 - gout104[1]);

    std::vector<RotationPoly> lut113;
    std::vector<long (*)(long)> flut113;
    auto lut113idx0 = [](long I) -> long {
        /* GATE 59 (LUT4 _357_ INIT 0x100 PERM 3021) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 1;
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
    Ciphertext gin113 = 1 * gout109[0] + 2 * gout108[0] + 4 * gout101[0] + 8 * gout106[0];
    std::vector<Ciphertext> gout113 = ctx.eval_lut_amortized(&gin113, lut113);

    std::vector<RotationPoly> lut114;
    std::vector<long (*)(long)> flut114;
    auto lut114idx0 = [](long I) -> long {
        /* GATE 57 (LUT4 _355_ INIT 0xb0bb PERM 3120) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin114 = 1 * gout100[0] + 2 * gout104[0] + 4 * gout60[0] + 8 * gout17[0];
    std::vector<Ciphertext> gout114 = ctx.eval_lut_amortized(&gin114, lut114);

    std::vector<RotationPoly> lut115;
    std::vector<long (*)(long)> flut115;
    auto lut115idx0 = [](long I) -> long {
        /* GATE 58 (LUT4 _356_ INIT 0xb0bb PERM 1203) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 1;
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
    Ciphertext gin115 = 1 * gout109[1] + 2 * gout104[0] + 4 * gout17[0] + 8 * gout17[1];
    std::vector<Ciphertext> gout115 = ctx.eval_lut_amortized(&gin115, lut115);

    std::vector<RotationPoly> lut116;
    std::vector<long (*)(long)> flut116;
    auto lut116idx0 = [](long I) -> long {
        /* GATE 52 (LUT4 _350_ INIT 0x4f00 PERM 0123) */
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
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
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
    Ciphertext gin116 = 1 * gout110[1] + 2 * gout105[0] + 4 * gout110[0] + 8 * gout114[0];
    std::vector<Ciphertext> gout116 = ctx.eval_lut_amortized(&gin116, lut116);

    std::cerr << "\rFA117    ";
    Ciphertext gin117 = 1 + 1 * ct_num4 + 2 * ct_num5 + 4 * gout105[1] + 1 * gout19[0] + 2 * gout1[0] + 4 * gout112[0];
    std::vector<Ciphertext> gout117 = ctx.eval_lut_amortized(&gin117, decomp);

    std::vector<RotationPoly> lut118;
    std::vector<long (*)(long)> flut118;
    auto lut118idx0 = [](long I) -> long {
        /* GATE 51 (LUT4 _349_ INIT 0x4f PERM 0123) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
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
            case 14: return 0;
            case 15: return 0;
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
    Ciphertext gin118 = 1 * gout116[0] + 2 * gout115[0] + 4 * gout113[0] + 8 * gout99[0];
    std::vector<Ciphertext> gout118 = ctx.eval_lut_amortized(&gin118, lut118);

    std::vector<RotationPoly> lut119;
    std::vector<long (*)(long)> flut119;
    auto lut119idx0 = [](long I) -> long {
        /* GATE 82 (LUT4 _380_ INIT 0xcaf PERM 2130) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
            default: assert(0);
        };
    };
    lut119.push_back(ctx.genrate_lut(lut119idx0));
    flut119.push_back(lut119idx0);
    auto lut119idx1 = [](long I) -> long {
        /* GATE 62 (LUT3 _360_ INIT 0xca PERM 123) */
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
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin119 = 1 * gout4[0] + 2 * ct_num4 + 4 * gout117[0] + 8 * gout118[0];
    std::vector<Ciphertext> gout119 = ctx.eval_lut_amortized(&gin119, lut119);

    std::cerr << "\rFA120    ";
    Ciphertext gin120 = gout117[3] + 1 * gout103[0] + 2 * gout100[0] + 4 * gout104[0] + 1 * gout84[0] + 2 * gout67[0] + 4 * gout33[0];
    std::vector<Ciphertext> gout120 = ctx.eval_lut_amortized(&gin120, decomp);

    std::vector<RotationPoly> lut121;
    std::vector<long (*)(long)> flut121;
    auto lut121idx0 = [](long I) -> long {
        /* GATE 84 (LUT4 _382_ INIT 0xc0a PERM 0123) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    };
    lut121.push_back(ctx.genrate_lut(lut121idx0));
    flut121.push_back(lut121idx0);
    auto lut121idx1 = [](long I) -> long {
        /* GATE 64 (LUT3 _362_ INIT 0xca PERM 013) */
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
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin121 = 1 * gout105[1] + 2 * gout117[2] + 4 * gout76[0] + 8 * gout118[0];
    std::vector<Ciphertext> gout121 = ctx.eval_lut_amortized(&gin121, lut121);

    std::vector<RotationPoly> lut122;
    std::vector<long (*)(long)> flut122;
    auto lut122idx0 = [](long I) -> long {
        /* GATE 65 (LUT3 _363_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin122 = 1 * gout103[0] + 2 * gout120[0] + 4 * gout118[0];
    std::vector<Ciphertext> gout122 = ctx.eval_lut_amortized(&gin122, lut122);

    std::cerr << "\rFA123    ";
    Ciphertext gin123 = gout120[3] + 1 * gout109[1] + 2 * gout106[0] + 4 * gout101[0] + 1 * gout45[0] + 2 * gout20[0] + 4 * gout8[0];
    std::vector<Ciphertext> gout123 = ctx.eval_lut_amortized(&gin123, decomp);

    std::vector<RotationPoly> lut124;
    std::vector<long (*)(long)> flut124;
    auto lut124idx0 = [](long I) -> long {
        /* GATE 68 (LUT3 _366_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin124 = 1 * gout109[1] + 2 * gout123[0] + 4 * gout118[0];
    std::vector<Ciphertext> gout124 = ctx.eval_lut_amortized(&gin124, lut124);

    std::cerr << "\rINV125   ";
    std::vector<Ciphertext> gout125;
    gout125.push_back(1 - gout118[0]);

    std::vector<RotationPoly> lut126;
    std::vector<long (*)(long)> flut126;
    auto lut126idx0 = [](long I) -> long {
        /* GATE 70 (LUT3 _368_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin126 = 1 * gout101[0] + 2 * gout123[2] + 4 * gout118[0];
    std::vector<Ciphertext> gout126 = ctx.eval_lut_amortized(&gin126, lut126);

    std::vector<RotationPoly> lut127;
    std::vector<long (*)(long)> flut127;
    auto lut127idx0 = [](long I) -> long {
        /* GATE 63 (LUT3 _361_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin127 = 1 * ct_num5 + 2 * gout117[1] + 4 * gout118[0];
    std::vector<Ciphertext> gout127 = ctx.eval_lut_amortized(&gin127, lut127);

    std::vector<RotationPoly> lut128;
    std::vector<long (*)(long)> flut128;
    auto lut128idx0 = [](long I) -> long {
        /* GATE 67 (LUT3 _365_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin128 = 1 * gout104[0] + 2 * gout120[2] + 4 * gout118[0];
    std::vector<Ciphertext> gout128 = ctx.eval_lut_amortized(&gin128, lut128);

    std::vector<RotationPoly> lut129;
    std::vector<long (*)(long)> flut129;
    auto lut129idx0 = [](long I) -> long {
        /* GATE 66 (LUT3 _364_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin129 = 1 * gout100[0] + 2 * gout120[1] + 4 * gout118[0];
    std::vector<Ciphertext> gout129 = ctx.eval_lut_amortized(&gin129, lut129);

    std::vector<RotationPoly> lut130;
    std::vector<long (*)(long)> flut130;
    auto lut130idx0 = [](long I) -> long {
        /* GATE 86 (LUT4 _384_ INIT 0xb0bb PERM 3102) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 1;
            case 14: return 0;
            case 15: return 1;
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
    Ciphertext gin130 = 1 * gout60[0] + 2 * gout129[0] + 4 * gout122[0] + 8 * gout17[0];
    std::vector<Ciphertext> gout130 = ctx.eval_lut_amortized(&gin130, lut130);

    std::vector<RotationPoly> lut131;
    std::vector<long (*)(long)> flut131;
    auto lut131idx0 = [](long I) -> long {
        /* GATE 90 (LUT4 _388_ INIT 0xb0bb PERM 2301) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 1;
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
    Ciphertext gin131 = 1 * gout129[0] + 2 * gout17[0] + 4 * gout128[0] + 8 * gout17[1];
    std::vector<Ciphertext> gout131 = ctx.eval_lut_amortized(&gin131, lut131);

    std::vector<RotationPoly> lut132;
    std::vector<long (*)(long)> flut132;
    auto lut132idx0 = [](long I) -> long {
        /* GATE 69 (LUT3 _367_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin132 = 1 * gout106[0] + 2 * gout123[1] + 4 * gout118[0];
    std::vector<Ciphertext> gout132 = ctx.eval_lut_amortized(&gin132, lut132);

    std::cerr << "\rFA133    ";
    Ciphertext gin133 = gout123[3] + 1 * gout107[0] + 2 * gout102[0] + 4 * gout99[0] + 1 * gout3[0] + 2 * gout5[0] + 4 * gout18[0];
    std::vector<Ciphertext> gout133 = ctx.eval_lut_amortized(&gin133, decomp);

    std::vector<RotationPoly> lut134;
    std::vector<long (*)(long)> flut134;
    auto lut134idx0 = [](long I) -> long {
        /* GATE 85 (LUT4 _383_ INIT 0xb0bb PERM 3210) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin134 = 1 * gout76[0] + 2 * gout121[1] + 4 * gout60[0] + 8 * gout122[0];
    std::vector<Ciphertext> gout134 = ctx.eval_lut_amortized(&gin134, lut134);

    std::vector<RotationPoly> lut135;
    std::vector<long (*)(long)> flut135;
    auto lut135idx0 = [](long I) -> long {
        /* GATE 81 (LUT4 _379_ INIT 0x71 PERM 3021) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
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
    Ciphertext gin135 = 1 * gout119[0] + 2 * gout121[0] + 4 * gout104[1] + 8 * gout127[0];
    std::vector<Ciphertext> gout135 = ctx.eval_lut_amortized(&gin135, lut135);

    std::cerr << "\rFA136    ";
    Ciphertext gin136 = 1 + 1 * ct_num2 + 2 * ct_num3 + 4 * gout119[1] + 1 * gout0[0] + 2 * gout13[0] + 4 * gout125[0];
    std::vector<Ciphertext> gout136 = ctx.eval_lut_amortized(&gin136, decomp);

    std::vector<RotationPoly> lut137;
    std::vector<long (*)(long)> flut137;
    auto lut137idx0 = [](long I) -> long {
        /* GATE 89 (LUT2 _387_ INIT 0x1 PERM 01) */
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
    Ciphertext gin137 = 1 * gout124[0] + 2 * gout132[0];
    std::vector<Ciphertext> gout137 = ctx.eval_lut_amortized(&gin137, lut137);

    std::cerr << "\rFA138    ";
    Ciphertext gin138 = gout136[3] + 1 * gout127[0] + 2 * gout121[1] + 4 * gout122[0] + 1 * gout111[0] + 2 * gout79[0] + 4 * gout62[0];
    std::vector<Ciphertext> gout138 = ctx.eval_lut_amortized(&gin138, decomp);

    std::vector<RotationPoly> lut139;
    std::vector<long (*)(long)> flut139;
    auto lut139idx0 = [](long I) -> long {
        /* GATE 80 (LUT3 _378_ INIT 0xd0 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin139 = 1 * gout134[0] + 2 * gout135[0] + 4 * gout130[0];
    std::vector<Ciphertext> gout139 = ctx.eval_lut_amortized(&gin139, lut139);

    std::vector<RotationPoly> lut140;
    std::vector<long (*)(long)> flut140;
    auto lut140idx0 = [](long I) -> long {
        /* GATE 72 (LUT3 _370_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin140 = 1 * gout102[0] + 2 * gout133[1] + 4 * gout118[0];
    std::vector<Ciphertext> gout140 = ctx.eval_lut_amortized(&gin140, lut140);

    std::vector<RotationPoly> lut141;
    std::vector<long (*)(long)> flut141;
    auto lut141idx0 = [](long I) -> long {
        /* GATE 71 (LUT3 _369_ INIT 0xca PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 1;
            case 10: return 0;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin141 = 1 * gout107[0] + 2 * gout133[0] + 4 * gout118[0];
    std::vector<Ciphertext> gout141 = ctx.eval_lut_amortized(&gin141, lut141);

    std::vector<RotationPoly> lut142;
    std::vector<long (*)(long)> flut142;
    auto lut142idx0 = [](long I) -> long {
        /* GATE 74 (LUT4 _372_ INIT 0x4f00 PERM 0123) */
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
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
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
    Ciphertext gin142 = 1 * gout116[0] + 2 * gout115[0] + 4 * gout113[0] + 8 * gout133[2];
    std::vector<Ciphertext> gout142 = ctx.eval_lut_amortized(&gin142, lut142);

    std::cerr << "\rFA143    ";
    Ciphertext gin143 = gout138[3] + 1 * gout129[0] + 2 * gout128[0] + 4 * gout124[0] + 1 * gout44[0] + 2 * gout43[0] + 4 * gout9[0];
    std::vector<Ciphertext> gout143 = ctx.eval_lut_amortized(&gin143, decomp);

    std::vector<RotationPoly> lut144;
    std::vector<long (*)(long)> flut144;
    auto lut144idx0 = [](long I) -> long {
        /* GATE 73 (LUT2 _371_ INIT 0xe PERM 01) */
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
    };
    lut144.push_back(ctx.genrate_lut(lut144idx0));
    flut144.push_back(lut144idx0);
    auto fvec144 = [flut144](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut144[i](I));
        return ret;
    };

    std::cerr << "\rLUT144   ";
    Ciphertext gin144 = 1 * gout142[0] + 2 * gout99[0];
    std::vector<Ciphertext> gout144 = ctx.eval_lut_amortized(&gin144, lut144);

    std::cerr << "\rFA145    ";
    Ciphertext gin145 = gout143[3] + 1 * gout132[0] + 2 * gout126[0] + 4 * gout141[0] + 1 * gout7[0] + 2 * gout38[0] + 4 * gout34[0];
    std::vector<Ciphertext> gout145 = ctx.eval_lut_amortized(&gin145, decomp);

    std::vector<RotationPoly> lut146;
    std::vector<long (*)(long)> flut146;
    auto lut146idx0 = [](long I) -> long {
        /* GATE 88 (LUT3 _386_ INIT 0x1 PERM 012) */
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
    };
    lut146.push_back(ctx.genrate_lut(lut146idx0));
    flut146.push_back(lut146idx0);
    auto fvec146 = [flut146](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut146[i](I));
        return ret;
    };

    std::cerr << "\rLUT146   ";
    Ciphertext gin146 = 1 * gout126[0] + 2 * gout141[0] + 4 * gout140[0];
    std::vector<Ciphertext> gout146 = ctx.eval_lut_amortized(&gin146, lut146);

    std::vector<RotationPoly> lut147;
    std::vector<long (*)(long)> flut147;
    auto lut147idx0 = [](long I) -> long {
        /* GATE 87 (LUT4 _385_ INIT 0xb000 PERM 3201) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
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
    Ciphertext gin147 = 1 * gout146[0] + 2 * gout137[0] + 4 * gout128[0] + 8 * gout17[1];
    std::vector<Ciphertext> gout147 = ctx.eval_lut_amortized(&gin147, lut147);

    std::cerr << "\rFA148    ";
    Ciphertext gin148 = gout145[3] + 1 * gout140[0] + 2 * gout144[0] + 1 * gout31[0] + 2 * gout27[0];
    std::vector<Ciphertext> gout148 = ctx.eval_lut_amortized(&gin148, decomp);

    std::vector<RotationPoly> lut149;
    std::vector<long (*)(long)> flut149;
    auto lut149idx0 = [](long I) -> long {
        /* GATE 79 (LUT4 _377_ INIT 0x4f PERM 0123) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 1;
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
            case 14: return 0;
            case 15: return 0;
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
    Ciphertext gin149 = 1 * gout139[0] + 2 * gout131[0] + 4 * gout147[0] + 8 * gout144[0];
    std::vector<Ciphertext> gout149 = ctx.eval_lut_amortized(&gin149, lut149);

    std::vector<RotationPoly> lut150;
    std::vector<long (*)(long)> flut150;
    auto lut150idx0 = [](long I) -> long {
        /* GATE 78 (LUT3 _376_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
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
    Ciphertext gin150 = 1 * ct_num3 + 2 * gout136[1] + 4 * gout149[0];
    std::vector<Ciphertext> gout150 = ctx.eval_lut_amortized(&gin150, lut150);

    std::vector<RotationPoly> lut151;
    std::vector<long (*)(long)> flut151;
    auto lut151idx0 = [](long I) -> long {
        /* GATE 91 (LUT4 _389_ INIT 0xf530 PERM 0132) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 1;
            case  7: return 0;
            case  8: return 1;
            case  9: return 1;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin151 = 1 * ct_num2 + 2 * gout136[0] + 4 * gout11[0] + 8 * gout149[0];
    std::vector<Ciphertext> gout151 = ctx.eval_lut_amortized(&gin151, lut151);

    std::vector<RotationPoly> lut152;
    std::vector<long (*)(long)> flut152;
    auto lut152idx0 = [](long I) -> long {
        /* GATE 99 (LUT4 _397_ INIT 0x3500 PERM 0132) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
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
            case 15: return 0;
            default: assert(0);
        };
    };
    lut152.push_back(ctx.genrate_lut(lut152idx0));
    flut152.push_back(lut152idx0);
    auto lut152idx1 = [](long I) -> long {
        /* GATE 95 (LUT4 _393_ INIT 0xc0a PERM 0123) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
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
    Ciphertext gin152 = 1 * gout127[0] + 2 * gout138[0] + 4 * gout76[0] + 8 * gout149[0];
    std::vector<Ciphertext> gout152 = ctx.eval_lut_amortized(&gin152, lut152);

    std::vector<RotationPoly> lut153;
    std::vector<long (*)(long)> flut153;
    auto lut153idx0 = [](long I) -> long {
        /* GATE 109 (LUT4 _407_ INIT 0x1 PERM 0123) */
        switch (I) {
            case  0: return 1;
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
            case 15: return 0;
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
    Ciphertext gin153 = 1 * gout145[0] + 2 * gout145[1] + 4 * gout145[2] + 8 * gout148[0];
    std::vector<Ciphertext> gout153 = ctx.eval_lut_amortized(&gin153, lut153);

    std::vector<RotationPoly> lut154;
    std::vector<long (*)(long)> flut154;
    auto lut154idx0 = [](long I) -> long {
        /* GATE 110 (LUT3 _408_ INIT 0x7 PERM 021) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
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
    Ciphertext gin154 = 1 * gout148[1] + 2 * gout144[0] + 4 * gout149[0];
    std::vector<Ciphertext> gout154 = ctx.eval_lut_amortized(&gin154, lut154);

    std::vector<RotationPoly> lut155;
    std::vector<long (*)(long)> flut155;
    auto lut155idx0 = [](long I) -> long {
        /* GATE 104 (LUT3 _402_ INIT 0x35 PERM 012) */
        switch (I) {
            case  0: return 1;
            case  1: return 0;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
            case  5: return 1;
            case  6: return 0;
            case  7: return 0;
            case  8: return 1;
            case  9: return 0;
            case 10: return 1;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 0;
            case 15: return 0;
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
    Ciphertext gin155 = 1 * gout129[0] + 2 * gout143[0] + 4 * gout149[0];
    std::vector<Ciphertext> gout155 = ctx.eval_lut_amortized(&gin155, lut155);

    std::vector<RotationPoly> lut156;
    std::vector<long (*)(long)> flut156;
    auto lut156idx0 = [](long I) -> long {
        /* GATE 96 (LUT4 _394_ INIT 0xc0a PERM 0123) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    };
    lut156.push_back(ctx.genrate_lut(lut156idx0));
    flut156.push_back(lut156idx0);
    auto lut156idx1 = [](long I) -> long {
        /* GATE 93 (LUT4 _391_ INIT 0x3500 PERM 0132) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
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
            case 15: return 0;
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
    Ciphertext gin156 = 1 * gout119[1] + 2 * gout136[2] + 4 * gout104[1] + 8 * gout149[0];
    std::vector<Ciphertext> gout156 = ctx.eval_lut_amortized(&gin156, lut156);

    std::vector<RotationPoly> lut157;
    std::vector<long (*)(long)> flut157;
    auto lut157idx0 = [](long I) -> long {
        /* GATE 98 (LUT4 _396_ INIT 0x3500 PERM 0132) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
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
            case 15: return 0;
            default: assert(0);
        };
    };
    lut157.push_back(ctx.genrate_lut(lut157idx0));
    flut157.push_back(lut157idx0);
    auto lut157idx1 = [](long I) -> long {
        /* GATE 102 (LUT4 _400_ INIT 0xc0a PERM 0123) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
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
    Ciphertext gin157 = 1 * gout121[1] + 2 * gout138[1] + 4 * gout60[0] + 8 * gout149[0];
    std::vector<Ciphertext> gout157 = ctx.eval_lut_amortized(&gin157, lut157);

    std::vector<RotationPoly> lut158;
    std::vector<long (*)(long)> flut158;
    auto lut158idx0 = [](long I) -> long {
        /* GATE 105 (LUT4 _403_ INIT 0x3500 PERM 0132) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
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
            case 15: return 0;
            default: assert(0);
        };
    };
    lut158.push_back(ctx.genrate_lut(lut158idx0));
    flut158.push_back(lut158idx0);
    auto lut158idx1 = [](long I) -> long {
        /* GATE 101 (LUT4 _399_ INIT 0xc0a PERM 0123) */
        switch (I) {
            case  0: return 0;
            case  1: return 1;
            case  2: return 0;
            case  3: return 1;
            case  4: return 0;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 1;
            case 11: return 1;
            case 12: return 0;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
            default: assert(0);
        };
    };
    lut158.push_back(ctx.genrate_lut(lut158idx1));
    flut158.push_back(lut158idx1);
    auto fvec158 = [flut158](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 2; ++i)
            ret.push_back(flut158[i](I));
        return ret;
    };

    std::cerr << "\rLUT158   ";
    Ciphertext gin158 = 1 * gout122[0] + 2 * gout138[2] + 4 * gout17[0] + 8 * gout149[0];
    std::vector<Ciphertext> gout158 = ctx.eval_lut_amortized(&gin158, lut158);

    std::vector<RotationPoly> lut159;
    std::vector<long (*)(long)> flut159;
    auto lut159idx0 = [](long I) -> long {
        /* GATE 103 (LUT3 _401_ INIT 0x7 PERM 120) */
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
    Ciphertext gin159 = 1 * gout158[0] + 2 * gout17[1] + 4 * gout155[0];
    std::vector<Ciphertext> gout159 = ctx.eval_lut_amortized(&gin159, lut159);

    std::vector<RotationPoly> lut160;
    std::vector<long (*)(long)> flut160;
    auto lut160idx0 = [](long I) -> long {
        /* GATE 108 (LUT3 _406_ INIT 0x10 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 1;
            case  5: return 0;
            case  6: return 0;
            case  7: return 0;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 0;
            case 14: return 0;
            case 15: return 0;
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
    Ciphertext gin160 = 1 * gout143[1] + 2 * gout143[2] + 4 * gout153[0];
    std::vector<Ciphertext> gout160 = ctx.eval_lut_amortized(&gin160, lut160);

    std::vector<RotationPoly> lut161;
    std::vector<long (*)(long)> flut161;
    auto lut161idx0 = [](long I) -> long {
        /* GATE 107 (LUT4 _405_ INIT 0xf044 PERM 0123) */
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
            case 10: return 0;
            case 11: return 0;
            case 12: return 1;
            case 13: return 1;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin161 = 1 * gout128[0] + 2 * gout147[0] + 4 * gout160[0] + 8 * gout149[0];
    std::vector<Ciphertext> gout161 = ctx.eval_lut_amortized(&gin161, lut161);

    std::vector<RotationPoly> lut162;
    std::vector<long (*)(long)> flut162;
    auto lut162idx0 = [](long I) -> long {
        /* GATE 100 (LUT2 _398_ INIT 0x1 PERM 01) */
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
    Ciphertext gin162 = 1 * gout158[1] + 2 * gout157[1];
    std::vector<Ciphertext> gout162 = ctx.eval_lut_amortized(&gin162, lut162);

    std::vector<RotationPoly> lut163;
    std::vector<long (*)(long)> flut163;
    auto lut163idx0 = [](long I) -> long {
        /* GATE 77 (LUT4 _375_ INIT 0x17 PERM 0123) */
        switch (I) {
            case  0: return 1;
            case  1: return 1;
            case  2: return 1;
            case  3: return 0;
            case  4: return 1;
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
    Ciphertext gin163 = 1 * gout150[0] + 2 * gout151[0] + 4 * gout118[0] + 8 * gout156[1];
    std::vector<Ciphertext> gout163 = ctx.eval_lut_amortized(&gin163, lut163);

    std::vector<RotationPoly> lut164;
    std::vector<long (*)(long)> flut164;
    auto lut164idx0 = [](long I) -> long {
        /* GATE 94 (LUT2 _392_ INIT 0x1 PERM 01) */
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
    Ciphertext gin164 = 1 * gout152[1] + 2 * gout156[0];
    std::vector<Ciphertext> gout164 = ctx.eval_lut_amortized(&gin164, lut164);

    std::vector<RotationPoly> lut165;
    std::vector<long (*)(long)> flut165;
    auto lut165idx0 = [](long I) -> long {
        /* GATE 97 (LUT2 _395_ INIT 0x1 PERM 01) */
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
    };
    lut165.push_back(ctx.genrate_lut(lut165idx0));
    flut165.push_back(lut165idx0);
    auto fvec165 = [flut165](long I) -> std::vector<long> {
        std::vector<long> ret;
        for (size_t i = 0; i < 1; ++i)
            ret.push_back(flut165[i](I));
        return ret;
    };

    std::cerr << "\rLUT165   ";
    Ciphertext gin165 = 1 * gout157[0] + 2 * gout152[0];
    std::vector<Ciphertext> gout165 = ctx.eval_lut_amortized(&gin165, lut165);

    std::vector<RotationPoly> lut166;
    std::vector<long (*)(long)> flut166;
    auto lut166idx0 = [](long I) -> long {
        /* GATE 106 (LUT3 _404_ INIT 0xe0 PERM 012) */
        switch (I) {
            case  0: return 0;
            case  1: return 0;
            case  2: return 0;
            case  3: return 0;
            case  4: return 0;
            case  5: return 1;
            case  6: return 1;
            case  7: return 1;
            case  8: return 0;
            case  9: return 0;
            case 10: return 0;
            case 11: return 0;
            case 12: return 0;
            case 13: return 1;
            case 14: return 1;
            case 15: return 1;
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
    Ciphertext gin166 = 1 * gout17[1] + 2 * gout155[0] + 4 * gout161[0];
    std::vector<Ciphertext> gout166 = ctx.eval_lut_amortized(&gin166, lut166);

    std::vector<RotationPoly> lut167;
    std::vector<long (*)(long)> flut167;
    auto lut167idx0 = [](long I) -> long {
        /* GATE 76 (LUT4 _374_ INIT 0x4f00 PERM 0123) */
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
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
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
    Ciphertext gin167 = 1 * gout163[0] + 2 * gout164[0] + 4 * gout165[0] + 8 * gout162[0];
    std::vector<Ciphertext> gout167 = ctx.eval_lut_amortized(&gin167, lut167);

    std::vector<RotationPoly> lut168;
    std::vector<long (*)(long)> flut168;
    auto lut168idx0 = [](long I) -> long {
        /* GATE 75 (LUT4 _373_ INIT 0x4f00 PERM 0123) */
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
            case 12: return 0;
            case 13: return 0;
            case 14: return 1;
            case 15: return 0;
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
    Ciphertext gin168 = 1 * gout167[0] + 2 * gout159[0] + 4 * gout166[0] + 8 * gout154[0];
    std::vector<Ciphertext> gout168 = ctx.eval_lut_amortized(&gin168, lut168);

    std::cerr << "\r          \r";
    std::vector<long> test_out;
    test_out.push_back(ctx.decrypt(&gout168[0])); /* out0 */
    test_out.push_back(ctx.decrypt(&gout149[0])); /* out1 */
    test_out.push_back(ctx.decrypt(&gout118[0])); /* out2 */
    test_out.push_back(ctx.decrypt(&gout104[1])); /* out3 */
    test_out.push_back(ctx.decrypt(&gout76[0])); /* out4 */
    test_out.push_back(ctx.decrypt(&gout60[0])); /* out5 */
    test_out.push_back(ctx.decrypt(&gout17[0])); /* out6 */
    test_out.push_back(ctx.decrypt(&gout17[1])); /* out7 */
    test_out.push_back(0); /* out15 */
    return test_out;
}

static void
BM_sqrt_lut4fa(benchmark::State& state)
{
    FHEContext ctx;
    ctx.generate_context(tfhe_12_NTT_amortized);
    ctx.set_default_message_encoding_type(partial_domain);
    ctx.set_default_plaintext_space(16);

    for (auto _ : state) {
        test_sqrt_lut4fa(ctx);
    }
}

BENCHMARK(BM_sqrt_lut4fa)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
