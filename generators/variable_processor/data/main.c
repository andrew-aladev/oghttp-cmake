// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "main.h"

#include "allowed_bytes.h"
#include "length.h"

void process_data(const bool* allowed_bytes, size_t min_length, size_t max_length)
{
  print_allowed_bytes(allowed_bytes);
  print_length(min_length);
  print_length(max_length);
}
