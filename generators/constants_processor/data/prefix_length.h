// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(DATA_PREFIX_LENGTH_H)
#define DATA_PREFIX_LENGTH_H

#include <stdlib.h>

int init_prefixes_length(const char** constants, size_t constants_length, size_t* prefixes_length_ptr);

#endif // DATA_PREFIX_LENGTH_H
