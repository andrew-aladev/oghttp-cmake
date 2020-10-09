// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

// This file was generated, do not edit manually.

// It may not be possible to run generator while cross compiling.
// So generated file should be distributed with its template.

#include "main.h"

const ogh_processor_state_t OGH_PROCESSOR_HEADER_NAME_ANY_FROM_STANDARD_INITIAL_STATE = 0;

#define ALLOWED_BYTES_LENGTH OGH_MAX_BYTE + 1

// clang-format off
const bool OGH_PROCESSOR_HEADER_NAME_ANY_FROM_STANDARD_ALLOWED_BYTES[ALLOWED_BYTES_LENGTH] = {
[0 ... ALLOWED_BYTES_LENGTH - 1] = false,
[33] = true,
[35] = true,
[36] = true,
[37] = true,
[38] = true,
[39] = true,
[42] = true,
[43] = true,
[45] = true,
[46] = true,
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
[124] = true,
[126] = true};
// clang-format on

const size_t OGH_PROCESSOR_HEADER_NAME_ANY_FROM_STANDARD_MIN_LENGTH = 1;
const size_t OGH_PROCESSOR_HEADER_NAME_ANY_FROM_STANDARD_MAX_LENGTH = 65535;

extern inline ogh_processor_state_t ogh_processor_header_name_any_from_standard_get_next_state(
  ogh_processor_state_t state, ogh_byte_t byte);
extern inline bool ogh_processor_header_name_any_from_standard_is_finished(ogh_processor_state_t state);
