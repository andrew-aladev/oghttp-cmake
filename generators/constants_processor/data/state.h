// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(DATA_STATE_H)
#define DATA_STATE_H

#include <stdlib.h>

size_t get_max_state(size_t constants_length, size_t prefixes_length);
void   print_max_state(size_t max_state);

int print_min_state_bits(size_t max_state);

#endif // DATA_STATE_H
