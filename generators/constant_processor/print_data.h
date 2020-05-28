// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(PRINT_DATA_H)
#define PRINT_DATA_H

#include <stdbool.h>

#include "print.h"

#define PREFIX "  "
#define TERMINATOR ",\n"

#define INITIALIZE_SPACERS() \
  bool is_first_spacer = true;

#define PRINT_SPACER()       \
  if (is_first_spacer) {     \
    PRINT(PREFIX);           \
    is_first_spacer = false; \
  }                          \
  else {                     \
    PRINT(TERMINATOR);       \
    PRINT(PREFIX);           \
  }

#define GLUE ";"

#define PRINT_GLUE() \
  PRINT(GLUE);

#define BYTE_TEMPLATE "0x%02x"

#define PRINT_BYTE(byte) \
  printf(BYTE_TEMPLATE, byte);

#define LENGTH_TEMPLATE "%zu"

#define PRINT_LENGTH(length) \
  printf(LENGTH_TEMPLATE, length);

#endif // PRINT_DATA_H
