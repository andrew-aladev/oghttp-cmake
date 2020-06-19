// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(DATA_MAIN_H)
#define DATA_MAIN_H

#include <stdbool.h>
#include <stdlib.h>

void process_data(const bool* allowed_bytes, size_t min_length, size_t max_length);

#endif // DATA_MAIN_H
