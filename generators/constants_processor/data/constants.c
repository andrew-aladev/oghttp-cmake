// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "constants.h"

#include <string.h>

#include "print.h"

void print_constants_length(size_t constants_length)
{
  PRINT_LENGTH(constants_length);
  PRINT_GLUE();
}

#define MACRO_SYMBOL_TEMPLATE "%02X"
#define STATE_TEMPLATE "OGH_PROCESSOR_CONSTANT(%s) = %zu"

int print_constant_states(const char** constants, size_t constants_length)
{
  INITIALIZE_SPACERS(true);

  for (size_t index = 0; index < constants_length; index++) {
    const char* constant        = constants[index];
    size_t      constant_length = strlen(constant);

    // Each constant symbol will be printed as hex value (1 byte -> 2 bytes conversion).
    size_t constant_macro_length = constant_length * 2 + 1;

    char* constant_macro = malloc(constant_macro_length);
    if (constant_macro == NULL) {
      PRINT_ERROR("failed to allocate memory for constant macro");
      return 1;
    }

    for (size_t jndex = 0; jndex < constant_length; jndex++) {
      snprintf(constant_macro + jndex * 2, 3, MACRO_SYMBOL_TEMPLATE, constant[jndex]);
    }

    PRINT_SPACER();

    // Constant state equals to index.
    PRINTF(STATE_TEMPLATE, constant_macro, index);

    free(constant_macro);
  }

  PRINT_GLUE();

  return 0;
}
