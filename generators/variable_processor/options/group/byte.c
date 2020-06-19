// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "byte.h"

#include <string.h>

#include "print.h"

int read_byte_value(const xmlNodePtr node, uint8_t* byte_value_ptr)
{
  xmlChar* value = xmlNodeGetContent(node);
  if (value == NULL) {
    PRINT_ERROR("failed to read byte value");
    return 1;
  }

  // Format: "0x" + uint8_t (hex value).
  if (strlen((const char*)value) == 4 && sscanf((const char*)value, "0x%hhx", byte_value_ptr) == 1) {
    xmlFree(value);

    return 0;
  }

  // Format: uint8_t.
  if (sscanf((const char*)value, "%c", byte_value_ptr) == 1) {
    xmlFree(value);

    return 0;
  }

  PRINTF_ERROR("failed to read byte, value: %s", (const char*)value);

  xmlFree(value);

  return 2;
}
