// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

// This file was generated, do not edit manually.

// It may not be possible to run generator while cross compiling.
// So generated file should be distributed with its template.

#if !defined(OGH_PROCESSOR_HEADER_NAME_1_0_H)
#define OGH_PROCESSOR_HEADER_NAME_1_0_H

#include <stdbool.h>

#include "../../../common.h"
#include "../../../log.h"

typedef uint8_t ogh_processor_header_name_1_0_state_t;

// Constant id equals to its bytes hex values.
// For example constant "ab" will have id "9798".
#undef OGH_PROCESSOR_CONSTANT
#define OGH_PROCESSOR_CONSTANT(ID) OGH_PROCESSOR_HEADER_NAME_1_0_CONSTANT_##ID

// clang-format off
enum {
OGH_PROCESSOR_CONSTANT(416C6C6F77) = 0,
OGH_PROCESSOR_CONSTANT(417574686F72697A6174696F6E) = 1,
OGH_PROCESSOR_CONSTANT(436F6E74656E742D456E636F64696E67) = 2,
OGH_PROCESSOR_CONSTANT(436F6E74656E742D4C656E677468) = 3,
OGH_PROCESSOR_CONSTANT(436F6E74656E742D54797065) = 4,
OGH_PROCESSOR_CONSTANT(44617465) = 5,
OGH_PROCESSOR_CONSTANT(45787069726573) = 6,
OGH_PROCESSOR_CONSTANT(46726F6D) = 7,
OGH_PROCESSOR_CONSTANT(49662D4D6F6469666965642D53696E6365) = 8,
OGH_PROCESSOR_CONSTANT(4C6173742D4D6F646966696564) = 9,
OGH_PROCESSOR_CONSTANT(4C6F636174696F6E) = 10,
OGH_PROCESSOR_CONSTANT(507261676D61) = 11,
OGH_PROCESSOR_CONSTANT(52656665726572) = 12,
OGH_PROCESSOR_CONSTANT(536572766572) = 13,
OGH_PROCESSOR_CONSTANT(557365722D4167656E74) = 14,
OGH_PROCESSOR_CONSTANT(5757572D41757468656E746963617465) = 15};
// clang-format on

extern const ogh_processor_state_t OGH_PROCESSOR_HEADER_NAME_1_0_INITIAL_STATE;
extern const size_t                OGH_PROCESSOR_HEADER_NAME_1_0_CONSTANTS_LENGTH;

extern const size_t OGH_PROCESSOR_HEADER_NAME_1_0_ALPHABET_LENGTH;
extern const size_t OGH_PROCESSOR_HEADER_NAME_1_0_ALPHABET_MAX_LENGTH;

extern const ogh_byte_t OGH_PROCESSOR_HEADER_NAME_1_0_UNDEFINED_SYMBOL;
extern const ogh_byte_t OGH_PROCESSOR_HEADER_NAME_1_0_SYMBOL_BY_BYTES[];

extern const ogh_processor_header_name_1_0_state_t OGH_PROCESSOR_HEADER_NAME_1_0_NEXT_STATE_BY_LAST_SYMBOLS[];

inline ogh_processor_state_t ogh_processor_header_name_1_0_get_next_state(ogh_processor_state_t state, ogh_byte_t byte)
{
  ogh_byte_t symbol = OGH_PROCESSOR_HEADER_NAME_1_0_SYMBOL_BY_BYTES[byte];

  // We need to verify symbol if alphabet is not full.
  if (OGH_PROCESSOR_HEADER_NAME_1_0_ALPHABET_LENGTH != OGH_PROCESSOR_HEADER_NAME_1_0_ALPHABET_MAX_LENGTH &&
      symbol == OGH_PROCESSOR_HEADER_NAME_1_0_UNDEFINED_SYMBOL) {
    OGH_LOG_ERROR("header_name_1_0 processor received invalid byte: %u", byte);
    return OGH_PROCESSOR_HEADER_NAME_1_0_INITIAL_STATE;
  }

  return OGH_PROCESSOR_HEADER_NAME_1_0_NEXT_STATE_BY_LAST_SYMBOLS[state *
                                                                    OGH_PROCESSOR_HEADER_NAME_1_0_ALPHABET_LENGTH +
                                                                  symbol];
}

inline bool ogh_processor_header_name_1_0_is_finished(ogh_processor_state_t state)
{
  // State of each constant equals to its index.
  return state < OGH_PROCESSOR_HEADER_NAME_1_0_CONSTANTS_LENGTH;
}

#endif // OGH_PROCESSOR_HEADER_NAME_1_0_H
