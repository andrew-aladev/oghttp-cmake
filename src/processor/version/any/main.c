// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

// This file was generated, do not edit manually.

// It may not be possible to run generator while cross compiling.
// So generated file should be distributed with its template.

#include "main.h"

const ogh_processor_state_t OGH_PROCESSOR_VERSION_ANY_INITIAL_STATE = 0;

#define ALLOWED_BYTES_LENGTH OGH_MAX_BYTE + 1

// clang-format off
const bool OGH_PROCESSOR_VERSION_ANY_ALLOWED_BYTES[ALLOWED_BYTES_LENGTH] = {
[0 ... ALLOWED_BYTES_LENGTH - 1] = false,
[0] = true,
[1] = true,
[2] = true,
[3] = true,
[4] = true,
[5] = true,
[6] = true,
[7] = true,
[8] = true,
[14] = true,
[15] = true,
[16] = true,
[17] = true,
[18] = true,
[19] = true,
[20] = true,
[21] = true,
[22] = true,
[23] = true,
[24] = true,
[25] = true,
[26] = true,
[27] = true,
[28] = true,
[29] = true,
[30] = true,
[31] = true,
[33] = true,
[34] = true,
[35] = true,
[36] = true,
[37] = true,
[38] = true,
[39] = true,
[40] = true,
[41] = true,
[42] = true,
[43] = true,
[44] = true,
[45] = true,
[46] = true,
[47] = true,
[48] = true,
[49] = true,
[50] = true,
[51] = true,
[52] = true,
[53] = true,
[54] = true,
[55] = true,
[56] = true,
[57] = true,
[58] = true,
[59] = true,
[60] = true,
[61] = true,
[62] = true,
[63] = true,
[64] = true,
[65] = true,
[66] = true,
[67] = true,
[68] = true,
[69] = true,
[70] = true,
[71] = true,
[72] = true,
[73] = true,
[74] = true,
[75] = true,
[76] = true,
[77] = true,
[78] = true,
[79] = true,
[80] = true,
[81] = true,
[82] = true,
[83] = true,
[84] = true,
[85] = true,
[86] = true,
[87] = true,
[88] = true,
[89] = true,
[90] = true,
[91] = true,
[92] = true,
[93] = true,
[94] = true,
[95] = true,
[96] = true,
[97] = true,
[98] = true,
[99] = true,
[100] = true,
[101] = true,
[102] = true,
[103] = true,
[104] = true,
[105] = true,
[106] = true,
[107] = true,
[108] = true,
[109] = true,
[110] = true,
[111] = true,
[112] = true,
[113] = true,
[114] = true,
[115] = true,
[116] = true,
[117] = true,
[118] = true,
[119] = true,
[120] = true,
[121] = true,
[122] = true,
[123] = true,
[124] = true,
[125] = true,
[126] = true,
[127] = true,
[128] = true,
[129] = true,
[130] = true,
[131] = true,
[132] = true,
[133] = true,
[134] = true,
[135] = true,
[136] = true,
[137] = true,
[138] = true,
[139] = true,
[140] = true,
[141] = true,
[142] = true,
[143] = true,
[144] = true,
[145] = true,
[146] = true,
[147] = true,
[148] = true,
[149] = true,
[150] = true,
[151] = true,
[152] = true,
[153] = true,
[154] = true,
[155] = true,
[156] = true,
[157] = true,
[158] = true,
[159] = true,
[160] = true,
[161] = true,
[162] = true,
[163] = true,
[164] = true,
[165] = true,
[166] = true,
[167] = true,
[168] = true,
[169] = true,
[170] = true,
[171] = true,
[172] = true,
[173] = true,
[174] = true,
[175] = true,
[176] = true,
[177] = true,
[178] = true,
[179] = true,
[180] = true,
[181] = true,
[182] = true,
[183] = true,
[184] = true,
[185] = true,
[186] = true,
[187] = true,
[188] = true,
[189] = true,
[190] = true,
[191] = true,
[192] = true,
[193] = true,
[194] = true,
[195] = true,
[196] = true,
[197] = true,
[198] = true,
[199] = true,
[200] = true,
[201] = true,
[202] = true,
[203] = true,
[204] = true,
[205] = true,
[206] = true,
[207] = true,
[208] = true,
[209] = true,
[210] = true,
[211] = true,
[212] = true,
[213] = true,
[214] = true,
[215] = true,
[216] = true,
[217] = true,
[218] = true,
[219] = true,
[220] = true,
[221] = true,
[222] = true,
[223] = true,
[224] = true,
[225] = true,
[226] = true,
[227] = true,
[228] = true,
[229] = true,
[230] = true,
[231] = true,
[232] = true,
[233] = true,
[234] = true,
[235] = true,
[236] = true,
[237] = true,
[238] = true,
[239] = true,
[240] = true,
[241] = true,
[242] = true,
[243] = true,
[244] = true,
[245] = true,
[246] = true,
[247] = true,
[248] = true,
[249] = true,
[250] = true,
[251] = true,
[252] = true,
[253] = true,
[254] = true,
[255] = true};
// clang-format on

const size_t OGH_PROCESSOR_VERSION_ANY_MIN_LENGTH = 1;
const size_t OGH_PROCESSOR_VERSION_ANY_MAX_LENGTH = 65535;

extern inline ogh_processor_state_t ogh_processor_version_any_get_next_state(ogh_processor_state_t state, ogh_byte_t byte);
extern inline bool                  ogh_processor_version_any_is_finished(ogh_processor_state_t state);
