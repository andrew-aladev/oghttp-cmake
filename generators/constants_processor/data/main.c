// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "main.h"

#include "constants.h"
#include "prefix.h"

int process_data(const char** constants, size_t constants_length)
{
  size_t prefixes_length;
  if (init_prefixes_length(constants, constants_length, &prefixes_length) != 0) {
    return 1;
  }

  // print

  print_constants_length(constants_length);

  if (print_constant_states(constants, constants_length) != 0) {
    return 2;
  }

  return 0;
}
