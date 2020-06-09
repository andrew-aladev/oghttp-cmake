// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "length.h"

#include <string.h>

#include "print.h"

void print_length(const char* constant)
{
  PRINT_LENGTH(strlen(constant));
  PRINT_GLUE();
}
