// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(DATA_CONSTANTS_H)
#define DATA_CONSTANTS_H

#include <stdlib.h>

void print_constants_length(size_t constants_length);
int  print_constant_states(const char** constants, size_t constants_length);

#endif // DATA_CONSTANTS_H
