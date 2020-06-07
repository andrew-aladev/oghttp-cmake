// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "options.h"
#include "options_schema.h"
#include "print.h"

int main(int argc, const char** argv)
{
  if (argc != 2) {
    PRINT_ERROR("required argument: options path");
    return 1;
  }

  const char* options_path = argv[1];
  if (validate_options_schema(options_path) != 0) {
    return 2;
  }

  bool   allowed_bytes[UINT8_MAX];
  size_t min_length;
  size_t max_length;
  if (read_options(options_path, allowed_bytes, &min_length, &max_length) != 0) {
    return 3;
  }

  return 0;
}
