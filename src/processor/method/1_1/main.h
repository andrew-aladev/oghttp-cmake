// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

// This file was generated, do not edit manually.

// It may not be possible to run generator while cross compiling.
// So generated file should be distributed with its template.

#if !defined(OGH_PROCESSOR_METHOD_1_1_H)
#define OGH_PROCESSOR_METHOD_1_1_H

#include <stdbool.h>

#include "../../../common.h"
#include "../../../log.h"

typedef uint8_t ogh_processor_method_1_1_state_t;

extern const ogh_processor_state_t OGH_PROCESSOR_METHOD_1_1_INITIAL_STATE;
extern const size_t                OGH_PROCESSOR_METHOD_1_1_CONSTANTS_LENGTH;

#undef OGH_PROCESSOR_CONSTANT
#define OGH_PROCESSOR_CONSTANT OGH_PROCESSOR_METHOD_1_1_CONSTANT

// clang-format off
enum {
OGH_PROCESSOR_CONSTANT(41434C) = 0,
OGH_PROCESSOR_CONSTANT(424153454C494E452D434F4E54524F4C) = 1,
OGH_PROCESSOR_CONSTANT(42494E44) = 2,
OGH_PROCESSOR_CONSTANT(434845434B494E) = 3,
OGH_PROCESSOR_CONSTANT(434845434B4F5554) = 4,
OGH_PROCESSOR_CONSTANT(434F4E4E454354) = 5,
OGH_PROCESSOR_CONSTANT(434F5059) = 6,
OGH_PROCESSOR_CONSTANT(44454C455445) = 7,
OGH_PROCESSOR_CONSTANT(474554) = 8,
OGH_PROCESSOR_CONSTANT(48454144) = 9,
OGH_PROCESSOR_CONSTANT(4C4142454C) = 10,
OGH_PROCESSOR_CONSTANT(4C494E4B) = 11,
OGH_PROCESSOR_CONSTANT(4C4F434B) = 12,
OGH_PROCESSOR_CONSTANT(4D45524745) = 13,
OGH_PROCESSOR_CONSTANT(4D4B4143544956495459) = 14,
OGH_PROCESSOR_CONSTANT(4D4B43414C454E444152) = 15,
OGH_PROCESSOR_CONSTANT(4D4B434F4C) = 16,
OGH_PROCESSOR_CONSTANT(4D4B5245444952454354524546) = 17,
OGH_PROCESSOR_CONSTANT(4D4B574F524B5350414345) = 18,
OGH_PROCESSOR_CONSTANT(4D4F5645) = 19,
OGH_PROCESSOR_CONSTANT(4F5054494F4E53) = 20,
OGH_PROCESSOR_CONSTANT(4F524445525041544348) = 21,
OGH_PROCESSOR_CONSTANT(5041544348) = 22,
OGH_PROCESSOR_CONSTANT(504F5354) = 23,
OGH_PROCESSOR_CONSTANT(505249) = 24,
OGH_PROCESSOR_CONSTANT(50524F5046494E44) = 25,
OGH_PROCESSOR_CONSTANT(50524F505041544348) = 26,
OGH_PROCESSOR_CONSTANT(505554) = 27,
OGH_PROCESSOR_CONSTANT(524542494E44) = 28,
OGH_PROCESSOR_CONSTANT(5245504F5254) = 29,
OGH_PROCESSOR_CONSTANT(534541524348) = 30,
OGH_PROCESSOR_CONSTANT(5452414345) = 31,
OGH_PROCESSOR_CONSTANT(554E42494E44) = 32,
OGH_PROCESSOR_CONSTANT(554E434845434B4F5554) = 33,
OGH_PROCESSOR_CONSTANT(554E4C494E4B) = 34,
OGH_PROCESSOR_CONSTANT(554E4C4F434B) = 35,
OGH_PROCESSOR_CONSTANT(555044415445) = 36,
OGH_PROCESSOR_CONSTANT(5550444154455245444952454354524546) = 37,
OGH_PROCESSOR_CONSTANT(56455253494F4E2D434F4E54524F4C) = 38};
// clang-format on

extern const size_t OGH_PROCESSOR_METHOD_1_1_ALPHABET_LENGTH;
extern const size_t OGH_PROCESSOR_METHOD_1_1_ALPHABET_MAX_LENGTH;

extern const ogh_byte_t OGH_PROCESSOR_METHOD_1_1_UNDEFINED_SYMBOL;
extern const ogh_byte_t OGH_PROCESSOR_METHOD_1_1_SYMBOL_BY_BYTES[];

extern const ogh_processor_method_1_1_state_t OGH_PROCESSOR_METHOD_1_1_NEXT_STATE_BY_LAST_SYMBOLS[];

inline ogh_processor_state_t ogh_processor_method_1_1_get_next_state(ogh_processor_state_t state, ogh_byte_t byte)
{
  ogh_byte_t symbol = OGH_PROCESSOR_METHOD_1_1_SYMBOL_BY_BYTES[byte];

  // We need to verify symbol if alphabet is not full.
  if (OGH_PROCESSOR_METHOD_1_1_ALPHABET_LENGTH != OGH_PROCESSOR_METHOD_1_1_ALPHABET_MAX_LENGTH && symbol == OGH_PROCESSOR_METHOD_1_1_UNDEFINED_SYMBOL) {
    OGH_LOG_ERROR("method_1_1 processor received invalid byte: %u", byte);
    return OGH_PROCESSOR_METHOD_1_1_INITIAL_STATE;
  }

  return OGH_PROCESSOR_METHOD_1_1_NEXT_STATE_BY_LAST_SYMBOLS[state * OGH_PROCESSOR_METHOD_1_1_ALPHABET_LENGTH + symbol];
}

inline bool ogh_processor_method_1_1_is_finished(ogh_processor_state_t state)
{
  // State of each constant equals to its index.
  return state < OGH_PROCESSOR_METHOD_1_1_CONSTANTS_LENGTH;
}

#endif // OGH_PROCESSOR_METHOD_1_1_H