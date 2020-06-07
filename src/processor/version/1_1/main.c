// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

// This file was generated, do not edit manually.

// It may not be possible to run generator while cross compiling.
// So generated file should be distributed with its template.

#include "main.h"

const ogh_processor_state_t OGH_PROCESSOR_VERSION_1_1_CONSTANTS_LENGTH = 5;
const size_t                OGH_PROCESSOR_VERSION_1_1_INITIAL_STATE    = OGH_PROCESSOR_VERSION_1_1_CONSTANTS_LENGTH;

const size_t OGH_PROCESSOR_VERSION_1_1_ALPHABET_LENGTH     = 6;
const size_t OGH_PROCESSOR_VERSION_1_1_ALPHABET_MAX_LENGTH = OGH_MAX_BYTE + 1;

const ogh_byte_t OGH_PROCESSOR_VERSION_1_1_UNDEFINED_SYMBOL = OGH_MAX_BYTE;

#define SYMBOL_BY_BYTES_LENGTH OGH_PROCESSOR_VERSION_1_1_ALPHABET_MAX_LENGTH

// clang-format off
const ogh_byte_t OGH_PROCESSOR_VERSION_1_1_SYMBOL_BY_BYTES[SYMBOL_BY_BYTES_LENGTH] = {
[0 ... SYMBOL_BY_BYTES_LENGTH - 1] = OGH_PROCESSOR_VERSION_1_1_UNDEFINED_SYMBOL,
[48] = 0,
[46] = 1,
[57] = 2,
[49] = 3,
[50] = 4,
[51] = 5};
// clang-format on

#define NEXT_STATE_BY_LAST_SYMBOLS_LENGTH (9 + 1) * OGH_PROCESSOR_VERSION_1_1_ALPHABET_LENGTH

// clang-format off
const ogh_processor_version_1_1_state_t OGH_PROCESSOR_VERSION_1_1_NEXT_STATE_BY_LAST_SYMBOLS[NEXT_STATE_BY_LAST_SYMBOLS_LENGTH] = {
[0 ... NEXT_STATE_BY_LAST_SYMBOLS_LENGTH - 1] = OGH_PROCESSOR_VERSION_1_1_INITIAL_STATE,
[30] = 6,
[33] = 8,
[37] = 7,
[44] = 0,
[49] = 9,
[54] = 1,
[57] = 2,
[58] = 3,
[59] = 4};
// clang-format on

extern inline ogh_processor_state_t ogh_processor_version_1_1_get_next_state(ogh_processor_state_t state, ogh_byte_t byte);
extern inline bool                  ogh_processor_version_1_1_is_finished(ogh_processor_state_t state);
