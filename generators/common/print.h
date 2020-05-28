// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(PRINT_H)
#define PRINT_H

#include <stdio.h>

#define PRINT(string) \
  fputs(string, stdout)

#define PRINT_ERROR(string) \
  fputs(string, stderr);    \
  fputc('\n', stderr);

#define PRINTF_ERROR(...)       \
  fprintf(stderr, __VA_ARGS__); \
  fputs("\n", stderr);

#endif // PRINT_H
