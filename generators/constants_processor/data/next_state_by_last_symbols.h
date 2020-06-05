// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(DATA_NEXT_STATE_BY_LAST_SYMBOLS_H)
#define DATA_NEXT_STATE_BY_LAST_SYMBOLS_H

#include <stdint.h>
#include <stdlib.h>

int init_next_state_by_last_symbols(
  size_t** next_state_by_last_symbols_ptr, size_t* next_state_by_last_symbols_length_ptr,
  const uint8_t* symbol_by_bytes, size_t alphabet_length, size_t max_state);

void print_next_state_by_last_symbols(const size_t* next_state_by_last_symbols, size_t next_state_by_last_symbols_length);

#endif // DATA_NEXT_STATE_BY_LAST_SYMBOLS_H
