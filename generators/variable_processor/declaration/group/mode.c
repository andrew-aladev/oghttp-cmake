// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "mode.h"

#include <string.h>

#include "print.h"

#define GROUP_MODE_PROPERTY "mode"

int read_group_mode(const xmlNodePtr group, group_mode_t* group_mode_ptr)
{
  xmlChar* value = xmlGetProp(group, (const xmlChar*)GROUP_MODE_PROPERTY);
  if (value == NULL) {
    PRINT_ERROR("failed to read group mode property");
    return 1;
  }

  int result = strcmp((const char*)value, "include");

  xmlFree(value);

  if (result == 0) {
    *group_mode_ptr = GROUP_MODE_INCLUDE;
  }
  else {
    *group_mode_ptr = GROUP_MODE_EXCLUDE;
  }

  return 0;
}
