// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "state.h"

#include <stdint.h>

#include "print.h"

size_t get_max_state(size_t constants_length, size_t prefixes_length)
{
  // Max state will be equal to constants length + empty string (1) + prefixes length - 1.
  return constants_length + prefixes_length;
}

void print_max_state(size_t max_state)
{
  PRINT_LENGTH(max_state);
  PRINT_GLUE();
}

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
  else if (max_state <= UINT64_MAX) {
    min_state_bits = "64";
  }
  else {
    PRINTF_ERROR("max state is too big, value: %zu", max_state);
    return 1;
  }

  PRINT(min_state_bits);
  PRINT_GLUE();

  return 0;
}
