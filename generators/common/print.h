// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(PRINT_H)
#define PRINT_H

#include <stdbool.h>
#include <stdio.h>

#define PRINT(string) \
  fputs(string, stdout)

#define PRINT_ERROR(string) \
  fputs(string, stderr);    \
  fputc('\n', stderr);

#define PRINTF_ERROR(...)       \
  fprintf(stderr, __VA_ARGS__); \
  fputs("\n", stderr);

// Spacers

#define TERMINATOR ",\n"

#define INITIALIZE_SPACERS(is_first) \
  bool is_first_spacer = is_first;

#define PRINT_SPACER()       \
  if (is_first_spacer) {     \
    is_first_spacer = false; \
  }                          \
  else {                     \
    PRINT(TERMINATOR);       \
  }

// Glue

#define GLUE ";"

#define PRINT_GLUE() \
  PRINT(GLUE);

// Byte

#define BYTE_TEMPLATE "0x%02x"

#define PRINT_BYTE(byte) \
  printf(BYTE_TEMPLATE, byte);

// Length

#define LENGTH_TEMPLATE "%zu"

#define PRINT_LENGTH(length) \
  printf(LENGTH_TEMPLATE, length);

#endif // PRINT_H
