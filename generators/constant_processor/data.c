// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "data.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "print.h"
#include "print_data.h"

int print_data(const char* constant)
{
  size_t constant_length = strlen(constant);
  if (constant_length > UINT32_MAX) {
    PRINT_ERROR("constant length is too big");
    return 1;
  }

  INITIALIZE_SPACERS();

  for (size_t index = 0; index < constant_length; index++) {
    uint8_t byte = constant[index];

    PRINT_SPACER();
    PRINT_BYTE(byte);
  }

  PRINT_GLUE();

  PRINT_LENGTH(constant_length);
  PRINT_GLUE();

  return 0;
}
