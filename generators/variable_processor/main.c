// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "declaration/main.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "data/main.h"
#include "declaration_schema.h"
#include "print.h"

int main(int argc, const char** argv)
{
  if (argc != 2) {
    PRINT_ERROR("required argument: declaration path");
    return 1;
  }

  const char* declaration_path = argv[1];
  if (validate_declaration_schema(declaration_path) != 0) {
    return 2;
  }

  bool   allowed_bytes[UINT8_MAX + 1];
  size_t min_length;
  size_t max_length;
  if (read_declaration(declaration_path, allowed_bytes, &min_length, &max_length) != 0) {
    return 3;
  }

  process_data(allowed_bytes, min_length, max_length);

  return 0;
}
