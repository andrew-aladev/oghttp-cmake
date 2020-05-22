// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "alphabet.h"

#include <stdint.h>
#include <stdlib.h>

#include "options.h"
#include "print.h"

#define ALLOWED_BYTE_TEMPLATE "[%u] = true"

#define PRINT_ALLOWED_BYTE(byte) printf(ALLOWED_BYTE_TEMPLATE, (uint8_t)byte);

// -- inclusive --

static inline bool find_byte_in_ranges(char target_byte)
{
  for (size_t index = 0; index < OGH_ALPHABET_RANGES_LENGTH; index++) {
    ogh_alphabet_range_t range = OGH_ALPHABET_RANGES[index];

    if (target_byte >= range.from && target_byte <= range.to) {
      return true;
    }
  }

  return false;
}

static inline void print_alphabet_including_bytes_into_ranges()
{
  INITIALIZE_SPACERS();

  size_t index;
  char   byte;

  for (index = 0; index < OGH_ALPHABET_RANGES_LENGTH; index++) {
    ogh_alphabet_range_t range = OGH_ALPHABET_RANGES[index];

    byte = range.from;

    while (true) {
      PRINT_SPACER();
      PRINT_ALLOWED_BYTE(byte);

      if (byte == range.to) {
        break;
      }
      byte++;
    }
  }

  for (index = 0; index < OGH_ALPHABET_LENGTH; index++) {
    byte = OGH_ALPHABET[index];

    if (!find_byte_in_ranges(byte)) {
      PRINT_SPACER();
      PRINT_ALLOWED_BYTE(byte);
    }
  }
}

// -- exclusive --

static inline bool find_byte_in_bytes(char target_byte)
{
  for (size_t index = 0; index < OGH_ALPHABET_LENGTH; index++) {
    char byte = OGH_ALPHABET[index];

    if (target_byte == byte) {
      return true;
    }
  }

  return false;
}

static inline void print_alphabet_excluding_bytes_from_ranges()
{
  INITIALIZE_SPACERS();

  size_t index;
  char   byte;

  for (index = 0; index < OGH_ALPHABET_RANGES_LENGTH; index++) {
    ogh_alphabet_range_t range = OGH_ALPHABET_RANGES[index];

    byte = range.from;

    while (true) {
      if (!find_byte_in_bytes(byte)) {
        PRINT_SPACER();
        PRINT_ALLOWED_BYTE(byte);
      }

      if (byte == range.to) {
        break;
      }
      byte++;
    }
  }
}

void print_allowed_bytes()
{
  if (OGH_ALPHABET_MODE == OGH_ALPHABET_INCLUDING_BYTES_INTO_RANGES) {
    print_alphabet_including_bytes_into_ranges();
  }
  else {
    print_alphabet_excluding_bytes_from_ranges();
  }

  PRINT_GLUE();
}
