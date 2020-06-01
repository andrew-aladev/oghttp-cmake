// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include <stdlib.h>

#include "data.h"
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

  char** constants;
  size_t constants_length;

  if (read_options(options_path, &constants, &constants_length) != 0) {
    return 3;
  }

  print_data(constants, constants_length);

  for (size_t index = 0; index < constants_length; index++) {
    free(constants[index]);
  }

  free(constants);

  return 0;
}
