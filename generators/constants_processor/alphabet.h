// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(ALPHABET_H)
#define ALPHABET_H

#include <stdint.h>
#include <stdlib.h>

int  init_alphabet(uint8_t** alphabet_ptr, uint8_t** symbol_by_bytes_ptr, size_t* alphabet_length_ptr);
void print_alphabet_length(size_t alphabet_length);
void print_symbol_by_bytes(const uint8_t* alphabet, const uint8_t* symbol_by_bytes, size_t alphabet_length);

#endif // ALPHABET_H
