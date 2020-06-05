// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(DATA_ALPHABET_H)
#define DATA_ALPHABET_H

#include <stdint.h>
#include <stdlib.h>

int init_alphabet(
  const char** constants, size_t constants_length,
  uint8_t** alphabet_ptr, size_t* alphabet_length_ptr, uint8_t** symbol_by_bytes_ptr);

void print_alphabet_length(size_t alphabet_length);
void print_symbol_by_bytes(const uint8_t* alphabet, size_t alphabet_length, const uint8_t* symbol_by_bytes);

#endif // DATA_ALPHABET_H
