// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

// This file is intended to be used by generator only.

#if !defined(OGH_PROCESSOR_GENERATOR_GENERIC_OPTIONS_H)
#define OGH_PROCESSOR_GENERATOR_GENERIC_OPTIONS_H

#include <stdint.h>
#include <stdlib.h>

typedef struct {
  char from;
  char to;
} ogh_alphabet_range_t;

extern const ogh_alphabet_range_t OGH_ALPHABET_RANGES[];
extern const size_t               OGH_ALPHABET_RANGES_LENGTH;

extern const char   OGH_ALPHABET[];
extern const size_t OGH_ALPHABET_LENGTH;

enum {
  OGH_ALPHABET_INCLUDING_BYTES_INTO_RANGES,
  OGH_ALPHABET_EXCLUDING_BYTES_FROM_RANGES
};
typedef uint8_t ogh_alphabet_mode_t;

extern const ogh_alphabet_mode_t OGH_ALPHABET_MODE;

extern const size_t OGH_MIN_LENGTH;
extern const size_t OGH_MAX_LENGTH;

#endif // OGH_PROCESSOR_GENERATOR_GENERIC_OPTIONS_H
