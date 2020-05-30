// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(PRINT_H)
#define PRINT_H

#include <stdbool.h>
#include <stdio.h>

#define TERMINATOR ",\n"

#define PRINT(string) fputs(string, stdout)

#define PRINT_ERROR(string) \
  fputs(string, stderr);    \
  fputc('\n', stderr);

#define INITIALIZE_SPACERS(is_first) bool is_first_spacer = is_first;

#define PRINT_SPACER()       \
  if (is_first_spacer) {     \
    is_first_spacer = false; \
  }                          \
  else {                     \
    PRINT(TERMINATOR);       \
  }

#endif // PRINT_H
