// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "data.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "print.h"

static inline void print_constant_length(const char* constant)
{
  PRINT_LENGTH(strlen(constant));
  PRINT_GLUE();
}

static inline void print_constant_bytes(const char* constant)
{
  INITIALIZE_SPACERS(true);

  for (size_t index = 0; index < strlen(constant); index++) {
    uint8_t byte = constant[index];

    PRINT_SPACER();
    PRINT_BYTE(byte);
  }

  PRINT_GLUE();
}

void process_data(const char* constant)
{
  print_constant_length(constant);
  print_constant_bytes(constant);
}
