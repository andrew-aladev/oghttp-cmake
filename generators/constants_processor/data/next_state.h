// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(DATA_NEXT_STATE_H)
#define DATA_NEXT_STATE_H

#include <stdint.h>
#include <stdlib.h>

int print_next_state_by_last_symbols(const char** constants, size_t constants_length, const uint8_t* symbol_by_bytes,
                                     size_t alphabet_length, size_t max_state);

#endif // DATA_NEXT_STATE_H
