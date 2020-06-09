// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "data/main.h"

#include <stdlib.h>

#include "options/main.h"
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

  char* constant;
  if (read_options(options_path, &constant) != 0) {
    return 3;
  }

  process_data(constant);

  free(constant);

  return 0;
}
