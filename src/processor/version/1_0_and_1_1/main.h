// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

// This file was generated, do not edit manually.

// It may not be possible to run generator while cross compiling.
// So generated file should be distributed with its template.

#if !defined(OGH_PROCESSOR_VERSION_1_0_AND_1_1_H)
#define OGH_PROCESSOR_VERSION_1_0_AND_1_1_H

#include <stdbool.h>

#include "../../../common.h"
#include "../../../log.h"

typedef uint8_t ogh_processor_version_1_0_and_1_1_state_t;

// Constant id equals to its bytes hex values.
// For example constant "ab" will have id "9798".
#undef OGH_PROCESSOR_CONSTANT
#define OGH_PROCESSOR_CONSTANT(ID) OGH_PROCESSOR_VERSION_1_0_AND_1_1_CONSTANT_##ID

// clang-format off
enum {
OGH_PROCESSOR_CONSTANT(312E30) = 0,
OGH_PROCESSOR_CONSTANT(312E31) = 1};
// clang-format on

extern const ogh_processor_state_t OGH_PROCESSOR_VERSION_1_0_AND_1_1_INITIAL_STATE;
extern const size_t                OGH_PROCESSOR_VERSION_1_0_AND_1_1_CONSTANTS_LENGTH;

extern const size_t OGH_PROCESSOR_VERSION_1_0_AND_1_1_ALPHABET_LENGTH;
extern const size_t OGH_PROCESSOR_VERSION_1_0_AND_1_1_ALPHABET_MAX_LENGTH;

extern const ogh_byte_t OGH_PROCESSOR_VERSION_1_0_AND_1_1_UNDEFINED_SYMBOL;
extern const ogh_byte_t OGH_PROCESSOR_VERSION_1_0_AND_1_1_SYMBOL_BY_BYTES[];

extern const ogh_processor_version_1_0_and_1_1_state_t OGH_PROCESSOR_VERSION_1_0_AND_1_1_NEXT_STATE_BY_LAST_SYMBOLS[];

inline ogh_processor_state_t ogh_processor_version_1_0_and_1_1_get_next_state(ogh_processor_state_t state, ogh_byte_t byte)
{
  ogh_byte_t symbol = OGH_PROCESSOR_VERSION_1_0_AND_1_1_SYMBOL_BY_BYTES[byte];

  // We need to verify symbol if alphabet is not full.
  if (OGH_PROCESSOR_VERSION_1_0_AND_1_1_ALPHABET_LENGTH != OGH_PROCESSOR_VERSION_1_0_AND_1_1_ALPHABET_MAX_LENGTH && symbol == OGH_PROCESSOR_VERSION_1_0_AND_1_1_UNDEFINED_SYMBOL) {
    OGH_LOG_ERROR("version_1_0_and_1_1 processor received invalid byte: %u", byte);
    return OGH_PROCESSOR_VERSION_1_0_AND_1_1_INITIAL_STATE;
  }

  return OGH_PROCESSOR_VERSION_1_0_AND_1_1_NEXT_STATE_BY_LAST_SYMBOLS[state * OGH_PROCESSOR_VERSION_1_0_AND_1_1_ALPHABET_LENGTH + symbol];
}

inline bool ogh_processor_version_1_0_and_1_1_is_finished(ogh_processor_state_t state)
{
  // State of each constant equals to its index.
  return state < OGH_PROCESSOR_VERSION_1_0_AND_1_1_CONSTANTS_LENGTH;
}

#endif // OGH_PROCESSOR_VERSION_1_0_AND_1_1_H
