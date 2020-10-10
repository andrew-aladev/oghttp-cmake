// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "data/main.h"

#include <stdlib.h>

#include "declaration/main.h"
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

  char** constants;
  size_t constants_length;
  if (read_declaration(declaration_path, &constants, &constants_length) != 0) {
    return 3;
  }

  int result = process_data((const char**) constants, constants_length);

  for (size_t index = 0; index < constants_length; index++) {
    free(constants[index]);
  }

  free(constants);

  if (result != 0) {
    return 4;
  }

  return 0;
}
