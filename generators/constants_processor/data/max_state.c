// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "max_state.h"

#include "options.h"
#include "print.h"

void init_max_state(size_t* max_state_ptr, size_t prefixes_length)
{
  // Max state will be equal to constants + empty string (1) + prefixes - 1.
  *max_state_ptr = OGH_CONSTANTS_LENGTH + prefixes_length;
}

#define MAX_STATE_TEMPLATE "%zu"

#define PRINT_MAX_STATE(max_state) printf(MAX_STATE_TEMPLATE, max_state);

void print_max_state(size_t max_state)
{
  PRINT_MAX_STATE(max_state);
  PRINT_GLUE();
}
