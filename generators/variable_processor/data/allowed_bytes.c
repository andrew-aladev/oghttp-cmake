// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "allowed_bytes.h"

#include <stdint.h>

#include "print.h"

#define ALLOWED_BYTES_TEMPLATE "[%u] = true"

void print_allowed_bytes(const bool* allowed_bytes)
{
  INITIALIZE_SPACERS(true);

  for (size_t index = 0; index <= UINT8_MAX; index++) {
    if (allowed_bytes[index]) {
      PRINT_SPACER();
      PRINTF(ALLOWED_BYTES_TEMPLATE, (uint8_t) index);
    }
  }

  PRINT_GLUE();
}
