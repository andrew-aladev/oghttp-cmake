// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "data.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "print.h"
#include "print_data.h"

void print_data(const char* constant)
{
  INITIALIZE_SPACERS();

  size_t constant_length = strlen(constant);

  for (size_t index = 0; index < constant_length; index++) {
    uint8_t byte = constant[index];

    PRINT_SPACER();
    PRINT_BYTE(byte);
  }

  PRINT_GLUE();

  PRINT_LENGTH(constant_length);
  PRINT_GLUE();
}
