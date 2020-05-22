// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "constants.h"

#include "print.h"

#define CONSTANT_TEMPLATE "\"%s\""

#define PRINT_CONSTANT(constant) printf(CONSTANT_TEMPLATE, constant);

int print_constants(const xmlNodeSetPtr nodes, int nodes_length, bool is_first_file)
{
  if (nodes_length <= 0) {
    PRINT_ERROR("can't find any constant");
    return 1;
  }

  INITIALIZE_SPACERS(is_first_file);

  for (int index = 0; index < nodes_length; index++) {
    const xmlNodePtr node = nodes->nodeTab[index];
    const char*      text = (const char*)xmlNodeGetContent(node);

    PRINT_SPACER();
    PRINT_CONSTANT(text);
  }

  return 0;
}
