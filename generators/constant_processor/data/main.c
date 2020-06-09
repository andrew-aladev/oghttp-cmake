// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "main.h"

#include "bytes.h"
#include "length.h"

void process_data(const char* constant)
{
  print_length(constant);
  print_bytes(constant);
}
