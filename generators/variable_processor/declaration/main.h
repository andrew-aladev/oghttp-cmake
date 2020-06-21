// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(DECLARATION_MAIN_H)
#define DECLARATION_MAIN_H

#include <stdbool.h>
#include <stdlib.h>

int read_declaration(const char* path, bool* allowed_bytes, size_t* min_length_ptr, size_t* max_length_ptr);

#endif // DECLARATION_MAIN_H
