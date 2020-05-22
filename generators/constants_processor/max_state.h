// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(MAX_STATE_H)
#define MAX_STATE_H

#include <stdlib.h>

void init_max_state(size_t* max_state_ptr, size_t prefixes_length);
void print_max_state(size_t max_state);

#endif // MAX_STATE_H