#include "foreign.hpp"
#include "../ee/vm.hpp"

#define REPEAT_ARGS_1(args) args[0]
#define REPEAT_ARGS_2(args) REPEAT_ARGS_1(args), args[1]
#define REPEAT_ARGS_3(args) REPEAT_ARGS_2(args), args[2]
#define REPEAT_ARGS_4(args) REPEAT_ARGS_3(args), args[3]
#define REPEAT_ARGS_5(args) REPEAT_ARGS_4(args), args[4]
#define REPEAT_ARGS_6(args) REPEAT_ARGS_5(args), args[5]
#define REPEAT_ARGS_7(args) REPEAT_ARGS_6(args), args[6]
#define REPEAT_ARGS_8(args) REPEAT_ARGS_7(args), args[7]
#define REPEAT_ARGS_9(args) REPEAT_ARGS_8(args), args[8]
#define REPEAT_ARGS_10(args) REPEAT_ARGS_9(args), args[9]
#define REPEAT_ARGS_11(args) REPEAT_ARGS_10(args), args[10]
#define REPEAT_ARGS_12(args) REPEAT_ARGS_11(args), args[11]
#define REPEAT_ARGS_13(args) REPEAT_ARGS_12(args), args[12]
#define REPEAT_ARGS_14(args) REPEAT_ARGS_13(args), args[13]
#define REPEAT_ARGS_15(args) REPEAT_ARGS_14(args), args[14]
#define REPEAT_ARGS_16(args) REPEAT_ARGS_15(args), args[15]
#define REPEAT_ARGS_17(args) REPEAT_ARGS_16(args), args[16]
#define REPEAT_ARGS_18(args) REPEAT_ARGS_17(args), args[17]
#define REPEAT_ARGS_19(args) REPEAT_ARGS_18(args), args[18]
#define REPEAT_ARGS_20(args) REPEAT_ARGS_19(args), args[19]
#define REPEAT_ARGS_21(args) REPEAT_ARGS_20(args), args[20]
#define REPEAT_ARGS_22(args) REPEAT_ARGS_21(args), args[21]
#define REPEAT_ARGS_23(args) REPEAT_ARGS_22(args), args[22]
#define REPEAT_ARGS_24(args) REPEAT_ARGS_23(args), args[23]
#define REPEAT_ARGS_25(args) REPEAT_ARGS_24(args), args[24]
#define REPEAT_ARGS_26(args) REPEAT_ARGS_25(args), args[25]
#define REPEAT_ARGS_27(args) REPEAT_ARGS_26(args), args[26]
#define REPEAT_ARGS_28(args) REPEAT_ARGS_27(args), args[27]
#define REPEAT_ARGS_29(args) REPEAT_ARGS_28(args), args[28]
#define REPEAT_ARGS_30(args) REPEAT_ARGS_29(args), args[29]
#define REPEAT_ARGS_31(args) REPEAT_ARGS_30(args), args[30]
#define REPEAT_ARGS_32(args) REPEAT_ARGS_31(args), args[31]
#define REPEAT_ARGS_33(args) REPEAT_ARGS_32(args), args[32]
#define REPEAT_ARGS_34(args) REPEAT_ARGS_33(args), args[33]
#define REPEAT_ARGS_35(args) REPEAT_ARGS_34(args), args[34]
#define REPEAT_ARGS_36(args) REPEAT_ARGS_35(args), args[35]
#define REPEAT_ARGS_37(args) REPEAT_ARGS_36(args), args[36]
#define REPEAT_ARGS_38(args) REPEAT_ARGS_37(args), args[37]
#define REPEAT_ARGS_39(args) REPEAT_ARGS_38(args), args[38]
#define REPEAT_ARGS_40(args) REPEAT_ARGS_39(args), args[39]
#define REPEAT_ARGS_41(args) REPEAT_ARGS_40(args), args[40]
#define REPEAT_ARGS_42(args) REPEAT_ARGS_41(args), args[41]
#define REPEAT_ARGS_43(args) REPEAT_ARGS_42(args), args[42]
#define REPEAT_ARGS_44(args) REPEAT_ARGS_43(args), args[43]
#define REPEAT_ARGS_45(args) REPEAT_ARGS_44(args), args[44]
#define REPEAT_ARGS_46(args) REPEAT_ARGS_45(args), args[45]
#define REPEAT_ARGS_47(args) REPEAT_ARGS_46(args), args[46]
#define REPEAT_ARGS_48(args) REPEAT_ARGS_47(args), args[47]
#define REPEAT_ARGS_49(args) REPEAT_ARGS_48(args), args[48]
#define REPEAT_ARGS_50(args) REPEAT_ARGS_49(args), args[49]
#define REPEAT_ARGS_51(args) REPEAT_ARGS_50(args), args[50]
#define REPEAT_ARGS_52(args) REPEAT_ARGS_51(args), args[51]
#define REPEAT_ARGS_53(args) REPEAT_ARGS_52(args), args[52]
#define REPEAT_ARGS_54(args) REPEAT_ARGS_53(args), args[53]
#define REPEAT_ARGS_55(args) REPEAT_ARGS_54(args), args[54]
#define REPEAT_ARGS_56(args) REPEAT_ARGS_55(args), args[55]
#define REPEAT_ARGS_57(args) REPEAT_ARGS_56(args), args[56]
#define REPEAT_ARGS_58(args) REPEAT_ARGS_57(args), args[57]
#define REPEAT_ARGS_59(args) REPEAT_ARGS_58(args), args[58]
#define REPEAT_ARGS_60(args) REPEAT_ARGS_59(args), args[59]
#define REPEAT_ARGS_61(args) REPEAT_ARGS_60(args), args[60]
#define REPEAT_ARGS_62(args) REPEAT_ARGS_61(args), args[61]
#define REPEAT_ARGS_63(args) REPEAT_ARGS_62(args), args[62]
#define REPEAT_ARGS_64(args) REPEAT_ARGS_63(args), args[63]
#define REPEAT_ARGS_65(args) REPEAT_ARGS_64(args), args[64]
#define REPEAT_ARGS_66(args) REPEAT_ARGS_65(args), args[65]
#define REPEAT_ARGS_67(args) REPEAT_ARGS_66(args), args[66]
#define REPEAT_ARGS_68(args) REPEAT_ARGS_67(args), args[67]
#define REPEAT_ARGS_69(args) REPEAT_ARGS_68(args), args[68]
#define REPEAT_ARGS_70(args) REPEAT_ARGS_69(args), args[69]
#define REPEAT_ARGS_71(args) REPEAT_ARGS_70(args), args[70]
#define REPEAT_ARGS_72(args) REPEAT_ARGS_71(args), args[71]
#define REPEAT_ARGS_73(args) REPEAT_ARGS_72(args), args[72]
#define REPEAT_ARGS_74(args) REPEAT_ARGS_73(args), args[73]
#define REPEAT_ARGS_75(args) REPEAT_ARGS_74(args), args[74]
#define REPEAT_ARGS_76(args) REPEAT_ARGS_75(args), args[75]
#define REPEAT_ARGS_77(args) REPEAT_ARGS_76(args), args[76]
#define REPEAT_ARGS_78(args) REPEAT_ARGS_77(args), args[77]
#define REPEAT_ARGS_79(args) REPEAT_ARGS_78(args), args[78]
#define REPEAT_ARGS_80(args) REPEAT_ARGS_79(args), args[79]
#define REPEAT_ARGS_81(args) REPEAT_ARGS_80(args), args[80]
#define REPEAT_ARGS_82(args) REPEAT_ARGS_81(args), args[81]
#define REPEAT_ARGS_83(args) REPEAT_ARGS_82(args), args[82]
#define REPEAT_ARGS_84(args) REPEAT_ARGS_83(args), args[83]
#define REPEAT_ARGS_85(args) REPEAT_ARGS_84(args), args[84]
#define REPEAT_ARGS_86(args) REPEAT_ARGS_85(args), args[85]
#define REPEAT_ARGS_87(args) REPEAT_ARGS_86(args), args[86]
#define REPEAT_ARGS_88(args) REPEAT_ARGS_87(args), args[87]
#define REPEAT_ARGS_89(args) REPEAT_ARGS_88(args), args[88]
#define REPEAT_ARGS_90(args) REPEAT_ARGS_89(args), args[89]
#define REPEAT_ARGS_91(args) REPEAT_ARGS_90(args), args[90]
#define REPEAT_ARGS_92(args) REPEAT_ARGS_91(args), args[91]
#define REPEAT_ARGS_93(args) REPEAT_ARGS_92(args), args[92]
#define REPEAT_ARGS_94(args) REPEAT_ARGS_93(args), args[93]
#define REPEAT_ARGS_95(args) REPEAT_ARGS_94(args), args[94]
#define REPEAT_ARGS_96(args) REPEAT_ARGS_95(args), args[95]
#define REPEAT_ARGS_97(args) REPEAT_ARGS_96(args), args[96]
#define REPEAT_ARGS_98(args) REPEAT_ARGS_97(args), args[97]
#define REPEAT_ARGS_99(args) REPEAT_ARGS_98(args), args[98]
#define REPEAT_ARGS_100(args) REPEAT_ARGS_99(args), args[99]
#define REPEAT_ARGS_101(args) REPEAT_ARGS_100(args), args[100]
#define REPEAT_ARGS_102(args) REPEAT_ARGS_101(args), args[101]
#define REPEAT_ARGS_103(args) REPEAT_ARGS_102(args), args[102]
#define REPEAT_ARGS_104(args) REPEAT_ARGS_103(args), args[103]
#define REPEAT_ARGS_105(args) REPEAT_ARGS_104(args), args[104]
#define REPEAT_ARGS_106(args) REPEAT_ARGS_105(args), args[105]
#define REPEAT_ARGS_107(args) REPEAT_ARGS_106(args), args[106]
#define REPEAT_ARGS_108(args) REPEAT_ARGS_107(args), args[107]
#define REPEAT_ARGS_109(args) REPEAT_ARGS_108(args), args[108]
#define REPEAT_ARGS_110(args) REPEAT_ARGS_109(args), args[109]
#define REPEAT_ARGS_111(args) REPEAT_ARGS_110(args), args[110]
#define REPEAT_ARGS_112(args) REPEAT_ARGS_111(args), args[111]
#define REPEAT_ARGS_113(args) REPEAT_ARGS_112(args), args[112]
#define REPEAT_ARGS_114(args) REPEAT_ARGS_113(args), args[113]
#define REPEAT_ARGS_115(args) REPEAT_ARGS_114(args), args[114]
#define REPEAT_ARGS_116(args) REPEAT_ARGS_115(args), args[115]
#define REPEAT_ARGS_117(args) REPEAT_ARGS_116(args), args[116]
#define REPEAT_ARGS_118(args) REPEAT_ARGS_117(args), args[117]
#define REPEAT_ARGS_119(args) REPEAT_ARGS_118(args), args[118]
#define REPEAT_ARGS_120(args) REPEAT_ARGS_119(args), args[119]
#define REPEAT_ARGS_121(args) REPEAT_ARGS_120(args), args[120]
#define REPEAT_ARGS_122(args) REPEAT_ARGS_121(args), args[121]
#define REPEAT_ARGS_123(args) REPEAT_ARGS_122(args), args[122]
#define REPEAT_ARGS_124(args) REPEAT_ARGS_123(args), args[123]
#define REPEAT_ARGS_125(args) REPEAT_ARGS_124(args), args[124]
#define REPEAT_ARGS_126(args) REPEAT_ARGS_125(args), args[125]
#define REPEAT_ARGS_127(args) REPEAT_ARGS_126(args), args[126]
#define REPEAT_ARGS_128(args) REPEAT_ARGS_127(args), args[127]
#define REPEAT_ARGS_129(args) REPEAT_ARGS_128(args), args[128]
#define REPEAT_ARGS_130(args) REPEAT_ARGS_129(args), args[129]
#define REPEAT_ARGS_131(args) REPEAT_ARGS_130(args), args[130]
#define REPEAT_ARGS_132(args) REPEAT_ARGS_131(args), args[131]
#define REPEAT_ARGS_133(args) REPEAT_ARGS_132(args), args[132]
#define REPEAT_ARGS_134(args) REPEAT_ARGS_133(args), args[133]
#define REPEAT_ARGS_135(args) REPEAT_ARGS_134(args), args[134]
#define REPEAT_ARGS_136(args) REPEAT_ARGS_135(args), args[135]
#define REPEAT_ARGS_137(args) REPEAT_ARGS_136(args), args[136]
#define REPEAT_ARGS_138(args) REPEAT_ARGS_137(args), args[137]
#define REPEAT_ARGS_139(args) REPEAT_ARGS_138(args), args[138]
#define REPEAT_ARGS_140(args) REPEAT_ARGS_139(args), args[139]
#define REPEAT_ARGS_141(args) REPEAT_ARGS_140(args), args[140]
#define REPEAT_ARGS_142(args) REPEAT_ARGS_141(args), args[141]
#define REPEAT_ARGS_143(args) REPEAT_ARGS_142(args), args[142]
#define REPEAT_ARGS_144(args) REPEAT_ARGS_143(args), args[143]
#define REPEAT_ARGS_145(args) REPEAT_ARGS_144(args), args[144]
#define REPEAT_ARGS_146(args) REPEAT_ARGS_145(args), args[145]
#define REPEAT_ARGS_147(args) REPEAT_ARGS_146(args), args[146]
#define REPEAT_ARGS_148(args) REPEAT_ARGS_147(args), args[147]
#define REPEAT_ARGS_149(args) REPEAT_ARGS_148(args), args[148]
#define REPEAT_ARGS_150(args) REPEAT_ARGS_149(args), args[149]
#define REPEAT_ARGS_151(args) REPEAT_ARGS_150(args), args[150]
#define REPEAT_ARGS_152(args) REPEAT_ARGS_151(args), args[151]
#define REPEAT_ARGS_153(args) REPEAT_ARGS_152(args), args[152]
#define REPEAT_ARGS_154(args) REPEAT_ARGS_153(args), args[153]
#define REPEAT_ARGS_155(args) REPEAT_ARGS_154(args), args[154]
#define REPEAT_ARGS_156(args) REPEAT_ARGS_155(args), args[155]
#define REPEAT_ARGS_157(args) REPEAT_ARGS_156(args), args[156]
#define REPEAT_ARGS_158(args) REPEAT_ARGS_157(args), args[157]
#define REPEAT_ARGS_159(args) REPEAT_ARGS_158(args), args[158]
#define REPEAT_ARGS_160(args) REPEAT_ARGS_159(args), args[159]
#define REPEAT_ARGS_161(args) REPEAT_ARGS_160(args), args[160]
#define REPEAT_ARGS_162(args) REPEAT_ARGS_161(args), args[161]
#define REPEAT_ARGS_163(args) REPEAT_ARGS_162(args), args[162]
#define REPEAT_ARGS_164(args) REPEAT_ARGS_163(args), args[163]
#define REPEAT_ARGS_165(args) REPEAT_ARGS_164(args), args[164]
#define REPEAT_ARGS_166(args) REPEAT_ARGS_165(args), args[165]
#define REPEAT_ARGS_167(args) REPEAT_ARGS_166(args), args[166]
#define REPEAT_ARGS_168(args) REPEAT_ARGS_167(args), args[167]
#define REPEAT_ARGS_169(args) REPEAT_ARGS_168(args), args[168]
#define REPEAT_ARGS_170(args) REPEAT_ARGS_169(args), args[169]
#define REPEAT_ARGS_171(args) REPEAT_ARGS_170(args), args[170]
#define REPEAT_ARGS_172(args) REPEAT_ARGS_171(args), args[171]
#define REPEAT_ARGS_173(args) REPEAT_ARGS_172(args), args[172]
#define REPEAT_ARGS_174(args) REPEAT_ARGS_173(args), args[173]
#define REPEAT_ARGS_175(args) REPEAT_ARGS_174(args), args[174]
#define REPEAT_ARGS_176(args) REPEAT_ARGS_175(args), args[175]
#define REPEAT_ARGS_177(args) REPEAT_ARGS_176(args), args[176]
#define REPEAT_ARGS_178(args) REPEAT_ARGS_177(args), args[177]
#define REPEAT_ARGS_179(args) REPEAT_ARGS_178(args), args[178]
#define REPEAT_ARGS_180(args) REPEAT_ARGS_179(args), args[179]
#define REPEAT_ARGS_181(args) REPEAT_ARGS_180(args), args[180]
#define REPEAT_ARGS_182(args) REPEAT_ARGS_181(args), args[181]
#define REPEAT_ARGS_183(args) REPEAT_ARGS_182(args), args[182]
#define REPEAT_ARGS_184(args) REPEAT_ARGS_183(args), args[183]
#define REPEAT_ARGS_185(args) REPEAT_ARGS_184(args), args[184]
#define REPEAT_ARGS_186(args) REPEAT_ARGS_185(args), args[185]
#define REPEAT_ARGS_187(args) REPEAT_ARGS_186(args), args[186]
#define REPEAT_ARGS_188(args) REPEAT_ARGS_187(args), args[187]
#define REPEAT_ARGS_189(args) REPEAT_ARGS_188(args), args[188]
#define REPEAT_ARGS_190(args) REPEAT_ARGS_189(args), args[189]
#define REPEAT_ARGS_191(args) REPEAT_ARGS_190(args), args[190]
#define REPEAT_ARGS_192(args) REPEAT_ARGS_191(args), args[191]
#define REPEAT_ARGS_193(args) REPEAT_ARGS_192(args), args[192]
#define REPEAT_ARGS_194(args) REPEAT_ARGS_193(args), args[193]
#define REPEAT_ARGS_195(args) REPEAT_ARGS_194(args), args[194]
#define REPEAT_ARGS_196(args) REPEAT_ARGS_195(args), args[195]
#define REPEAT_ARGS_197(args) REPEAT_ARGS_196(args), args[196]
#define REPEAT_ARGS_198(args) REPEAT_ARGS_197(args), args[197]
#define REPEAT_ARGS_199(args) REPEAT_ARGS_198(args), args[198]
#define REPEAT_ARGS_200(args) REPEAT_ARGS_199(args), args[199]
#define REPEAT_ARGS_201(args) REPEAT_ARGS_200(args), args[200]
#define REPEAT_ARGS_202(args) REPEAT_ARGS_201(args), args[201]
#define REPEAT_ARGS_203(args) REPEAT_ARGS_202(args), args[202]
#define REPEAT_ARGS_204(args) REPEAT_ARGS_203(args), args[203]
#define REPEAT_ARGS_205(args) REPEAT_ARGS_204(args), args[204]
#define REPEAT_ARGS_206(args) REPEAT_ARGS_205(args), args[205]
#define REPEAT_ARGS_207(args) REPEAT_ARGS_206(args), args[206]
#define REPEAT_ARGS_208(args) REPEAT_ARGS_207(args), args[207]
#define REPEAT_ARGS_209(args) REPEAT_ARGS_208(args), args[208]
#define REPEAT_ARGS_210(args) REPEAT_ARGS_209(args), args[209]
#define REPEAT_ARGS_211(args) REPEAT_ARGS_210(args), args[210]
#define REPEAT_ARGS_212(args) REPEAT_ARGS_211(args), args[211]
#define REPEAT_ARGS_213(args) REPEAT_ARGS_212(args), args[212]
#define REPEAT_ARGS_214(args) REPEAT_ARGS_213(args), args[213]
#define REPEAT_ARGS_215(args) REPEAT_ARGS_214(args), args[214]
#define REPEAT_ARGS_216(args) REPEAT_ARGS_215(args), args[215]
#define REPEAT_ARGS_217(args) REPEAT_ARGS_216(args), args[216]
#define REPEAT_ARGS_218(args) REPEAT_ARGS_217(args), args[217]
#define REPEAT_ARGS_219(args) REPEAT_ARGS_218(args), args[218]
#define REPEAT_ARGS_220(args) REPEAT_ARGS_219(args), args[219]
#define REPEAT_ARGS_221(args) REPEAT_ARGS_220(args), args[220]
#define REPEAT_ARGS_222(args) REPEAT_ARGS_221(args), args[221]
#define REPEAT_ARGS_223(args) REPEAT_ARGS_222(args), args[222]
#define REPEAT_ARGS_224(args) REPEAT_ARGS_223(args), args[223]
#define REPEAT_ARGS_225(args) REPEAT_ARGS_224(args), args[224]
#define REPEAT_ARGS_226(args) REPEAT_ARGS_225(args), args[225]
#define REPEAT_ARGS_227(args) REPEAT_ARGS_226(args), args[226]
#define REPEAT_ARGS_228(args) REPEAT_ARGS_227(args), args[227]
#define REPEAT_ARGS_229(args) REPEAT_ARGS_228(args), args[228]
#define REPEAT_ARGS_230(args) REPEAT_ARGS_229(args), args[229]
#define REPEAT_ARGS_231(args) REPEAT_ARGS_230(args), args[230]
#define REPEAT_ARGS_232(args) REPEAT_ARGS_231(args), args[231]
#define REPEAT_ARGS_233(args) REPEAT_ARGS_232(args), args[232]
#define REPEAT_ARGS_234(args) REPEAT_ARGS_233(args), args[233]
#define REPEAT_ARGS_235(args) REPEAT_ARGS_234(args), args[234]
#define REPEAT_ARGS_236(args) REPEAT_ARGS_235(args), args[235]
#define REPEAT_ARGS_237(args) REPEAT_ARGS_236(args), args[236]
#define REPEAT_ARGS_238(args) REPEAT_ARGS_237(args), args[237]
#define REPEAT_ARGS_239(args) REPEAT_ARGS_238(args), args[238]
#define REPEAT_ARGS_240(args) REPEAT_ARGS_239(args), args[239]
#define REPEAT_ARGS_241(args) REPEAT_ARGS_240(args), args[240]
#define REPEAT_ARGS_242(args) REPEAT_ARGS_241(args), args[241]
#define REPEAT_ARGS_243(args) REPEAT_ARGS_242(args), args[242]
#define REPEAT_ARGS_244(args) REPEAT_ARGS_243(args), args[243]
#define REPEAT_ARGS_245(args) REPEAT_ARGS_244(args), args[244]
#define REPEAT_ARGS_246(args) REPEAT_ARGS_245(args), args[245]
#define REPEAT_ARGS_247(args) REPEAT_ARGS_246(args), args[246]
#define REPEAT_ARGS_248(args) REPEAT_ARGS_247(args), args[247]
#define REPEAT_ARGS_249(args) REPEAT_ARGS_248(args), args[248]
#define REPEAT_ARGS_250(args) REPEAT_ARGS_249(args), args[249]
#define REPEAT_ARGS_251(args) REPEAT_ARGS_250(args), args[250]
#define REPEAT_ARGS_252(args) REPEAT_ARGS_251(args), args[251]
#define REPEAT_ARGS_253(args) REPEAT_ARGS_252(args), args[252]
#define REPEAT_ARGS_254(args) REPEAT_ARGS_253(args), args[253]
#define REPEAT_ARGS_255(args) REPEAT_ARGS_254(args), args[254]
#define REPEAT_ARGS_256(args) REPEAT_ARGS_255(args), args[255]

#define REPEAT_ARGS(args, n) REPEAT_ARGS_##n(args)

#define WRITE_CASE(n) case n: result = library->call<Obj *>(name, REPEAT_ARGS(args,n)); break

void ObjForeign::linkLibrary() {
    auto foreignAnnoType = SpadeVM::current()->getSymbol("spade::foreign.Foreign");
    auto annos = cast<ObjArray *>(getMember("$annotations"));
    Obj *foreignAnno;
    annos->foreach([foreignAnnoType, &foreignAnno](Obj *anno) {
        if (anno->getType() == foreignAnnoType) {
            foreignAnno = anno;
        }
    });
    auto libraryPath = foreignAnno->getMember("path")->toString();
    auto metName = foreignAnno->getMember("name")->toString();

}

void ObjForeign::call(Thread *thread, vector<Obj *> args) {
    call(thread, args.data());
}

void ObjForeign::call(Thread *thread, Obj **args) {
    Obj *result;
    switch (sign.getParams().size()) {
        case 0:
            result = library->call<Obj *>(name);
            break;
        WRITE_CASE(1);
        WRITE_CASE(2);
        WRITE_CASE(3);
        WRITE_CASE(4);
        WRITE_CASE(5);
        WRITE_CASE(6);
        WRITE_CASE(7);
        WRITE_CASE(8);
        WRITE_CASE(9);
        WRITE_CASE(10);
        WRITE_CASE(11);
        WRITE_CASE(12);
        WRITE_CASE(13);
        WRITE_CASE(14);
        WRITE_CASE(15);
        WRITE_CASE(16);
        WRITE_CASE(17);
        WRITE_CASE(18);
        WRITE_CASE(19);
        WRITE_CASE(20);
        WRITE_CASE(21);
        WRITE_CASE(22);
        WRITE_CASE(23);
        WRITE_CASE(24);
        WRITE_CASE(25);
        WRITE_CASE(26);
        WRITE_CASE(27);
        WRITE_CASE(28);
        WRITE_CASE(29);
        WRITE_CASE(30);
        WRITE_CASE(31);
        WRITE_CASE(32);
        WRITE_CASE(33);
        WRITE_CASE(34);
        WRITE_CASE(35);
        WRITE_CASE(36);
        WRITE_CASE(37);
        WRITE_CASE(38);
        WRITE_CASE(39);
        WRITE_CASE(40);
        WRITE_CASE(41);
        WRITE_CASE(42);
        WRITE_CASE(43);
        WRITE_CASE(44);
        WRITE_CASE(45);
        WRITE_CASE(46);
        WRITE_CASE(47);
        WRITE_CASE(48);
        WRITE_CASE(49);
        WRITE_CASE(50);
        WRITE_CASE(51);
        WRITE_CASE(52);
        WRITE_CASE(53);
        WRITE_CASE(54);
        WRITE_CASE(55);
        WRITE_CASE(56);
        WRITE_CASE(57);
        WRITE_CASE(58);
        WRITE_CASE(59);
        WRITE_CASE(60);
        WRITE_CASE(61);
        WRITE_CASE(62);
        WRITE_CASE(63);
        WRITE_CASE(64);
        WRITE_CASE(65);
        WRITE_CASE(66);
        WRITE_CASE(67);
        WRITE_CASE(68);
        WRITE_CASE(69);
        WRITE_CASE(70);
        WRITE_CASE(71);
        WRITE_CASE(72);
        WRITE_CASE(73);
        WRITE_CASE(74);
        WRITE_CASE(75);
        WRITE_CASE(76);
        WRITE_CASE(77);
        WRITE_CASE(78);
        WRITE_CASE(79);
        WRITE_CASE(80);
        WRITE_CASE(81);
        WRITE_CASE(82);
        WRITE_CASE(83);
        WRITE_CASE(84);
        WRITE_CASE(85);
        WRITE_CASE(86);
        WRITE_CASE(87);
        WRITE_CASE(88);
        WRITE_CASE(89);
        WRITE_CASE(90);
        WRITE_CASE(91);
        WRITE_CASE(92);
        WRITE_CASE(93);
        WRITE_CASE(94);
        WRITE_CASE(95);
        WRITE_CASE(96);
        WRITE_CASE(97);
        WRITE_CASE(98);
        WRITE_CASE(99);
        WRITE_CASE(100);
        WRITE_CASE(101);
        WRITE_CASE(102);
        WRITE_CASE(103);
        WRITE_CASE(104);
        WRITE_CASE(105);
        WRITE_CASE(106);
        WRITE_CASE(107);
        WRITE_CASE(108);
        WRITE_CASE(109);
        WRITE_CASE(110);
        WRITE_CASE(111);
        WRITE_CASE(112);
        WRITE_CASE(113);
        WRITE_CASE(114);
        WRITE_CASE(115);
        WRITE_CASE(116);
        WRITE_CASE(117);
        WRITE_CASE(118);
        WRITE_CASE(119);
        WRITE_CASE(120);
        WRITE_CASE(121);
        WRITE_CASE(122);
        WRITE_CASE(123);
        WRITE_CASE(124);
        WRITE_CASE(125);
        WRITE_CASE(126);
        WRITE_CASE(127);
        WRITE_CASE(128);
        WRITE_CASE(129);
        WRITE_CASE(130);
        WRITE_CASE(131);
        WRITE_CASE(132);
        WRITE_CASE(133);
        WRITE_CASE(134);
        WRITE_CASE(135);
        WRITE_CASE(136);
        WRITE_CASE(137);
        WRITE_CASE(138);
        WRITE_CASE(139);
        WRITE_CASE(140);
        WRITE_CASE(141);
        WRITE_CASE(142);
        WRITE_CASE(143);
        WRITE_CASE(144);
        WRITE_CASE(145);
        WRITE_CASE(146);
        WRITE_CASE(147);
        WRITE_CASE(148);
        WRITE_CASE(149);
        WRITE_CASE(150);
        WRITE_CASE(151);
        WRITE_CASE(152);
        WRITE_CASE(153);
        WRITE_CASE(154);
        WRITE_CASE(155);
        WRITE_CASE(156);
        WRITE_CASE(157);
        WRITE_CASE(158);
        WRITE_CASE(159);
        WRITE_CASE(160);
        WRITE_CASE(161);
        WRITE_CASE(162);
        WRITE_CASE(163);
        WRITE_CASE(164);
        WRITE_CASE(165);
        WRITE_CASE(166);
        WRITE_CASE(167);
        WRITE_CASE(168);
        WRITE_CASE(169);
        WRITE_CASE(170);
        WRITE_CASE(171);
        WRITE_CASE(172);
        WRITE_CASE(173);
        WRITE_CASE(174);
        WRITE_CASE(175);
        WRITE_CASE(176);
        WRITE_CASE(177);
        WRITE_CASE(178);
        WRITE_CASE(179);
        WRITE_CASE(180);
        WRITE_CASE(181);
        WRITE_CASE(182);
        WRITE_CASE(183);
        WRITE_CASE(184);
        WRITE_CASE(185);
        WRITE_CASE(186);
        WRITE_CASE(187);
        WRITE_CASE(188);
        WRITE_CASE(189);
        WRITE_CASE(190);
        WRITE_CASE(191);
        WRITE_CASE(192);
        WRITE_CASE(193);
        WRITE_CASE(194);
        WRITE_CASE(195);
        WRITE_CASE(196);
        WRITE_CASE(197);
        WRITE_CASE(198);
        WRITE_CASE(199);
        WRITE_CASE(200);
        WRITE_CASE(201);
        WRITE_CASE(202);
        WRITE_CASE(203);
        WRITE_CASE(204);
        WRITE_CASE(205);
        WRITE_CASE(206);
        WRITE_CASE(207);
        WRITE_CASE(208);
        WRITE_CASE(209);
        WRITE_CASE(210);
        WRITE_CASE(211);
        WRITE_CASE(212);
        WRITE_CASE(213);
        WRITE_CASE(214);
        WRITE_CASE(215);
        WRITE_CASE(216);
        WRITE_CASE(217);
        WRITE_CASE(218);
        WRITE_CASE(219);
        WRITE_CASE(220);
        WRITE_CASE(221);
        WRITE_CASE(222);
        WRITE_CASE(223);
        WRITE_CASE(224);
        WRITE_CASE(225);
        WRITE_CASE(226);
        WRITE_CASE(227);
        WRITE_CASE(228);
        WRITE_CASE(229);
        WRITE_CASE(230);
        WRITE_CASE(231);
        WRITE_CASE(232);
        WRITE_CASE(233);
        WRITE_CASE(234);
        WRITE_CASE(235);
        WRITE_CASE(236);
        WRITE_CASE(237);
        WRITE_CASE(238);
        WRITE_CASE(239);
        WRITE_CASE(240);
        WRITE_CASE(241);
        WRITE_CASE(242);
        WRITE_CASE(243);
        WRITE_CASE(244);
        WRITE_CASE(245);
        WRITE_CASE(246);
        WRITE_CASE(247);
        WRITE_CASE(248);
        WRITE_CASE(249);
        WRITE_CASE(250);
        WRITE_CASE(251);
        WRITE_CASE(252);
        WRITE_CASE(253);
        WRITE_CASE(254);
        WRITE_CASE(255);
        WRITE_CASE(256);
        default:
            result = Obj::alloc<ObjNull>(thread->getState()->getVM()->getMemoryManager());
            break;
    }
    thread->getState()->push(result);
}

string ObjForeign::toString() const {
    static string kindNames[] = {
            "function",
            "method",
            "constructor"
    };
    return format("<foreign %s '%s'>", kindNames[kind].c_str(), sign.toString().c_str());
}
