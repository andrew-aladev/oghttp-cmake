// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(OPTIONS_H)
#define OPTIONS_H

#include <stdlib.h>

int read_options(const char* path, char*** constants_ptr, size_t* constants_length_ptr);

#endif // OPTIONS_H
