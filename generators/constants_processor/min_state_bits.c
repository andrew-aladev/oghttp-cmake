// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "min_state_bits.h"

#include <stdint.h>

#include "print.h"

int print_min_state_bits(size_t max_state)
{
  char* min_state_bits;

  if (max_state <= UINT8_MAX) {
    min_state_bits = "8";
  }
  else if (max_state <= UINT16_MAX) {
    min_state_bits = "16";
  }
  else if (max_state <= UINT32_MAX) {
    min_state_bits = "32";
  }
  else {
    PRINT_ERROR("max state is too big");
    return 1;
  }

  PRINT(min_state_bits);
  PRINT_GLUE();

  return 0;
}
