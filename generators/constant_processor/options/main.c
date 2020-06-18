// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "main.h"

#include <string.h>

#include "constant.h"
#include "print.h"

int read_options(const char* path, char** constant_ptr)
{
  xmlInitParser();
  LIBXML_TEST_VERSION

  const xmlDocPtr document = xmlParseFile(path);
  if (document == NULL) {
    PRINTF_ERROR("failed to parse XML file, path: %s", path);

    xmlCleanupParser();

    return 1;
  }

  int result = read_constant(document, constant_ptr);

  xmlFreeDoc(document);
  xmlCleanupParser();

  if (result != 0) {
    return 2;
  }

  return 0;
}
