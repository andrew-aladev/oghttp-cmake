// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "options.h"

#include <libxml/HTMLparser.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>

#include "print.h"

static inline int read_bytes(const htmlDocPtr document, bool* allowed_bytes, size_t* min_length_ptr, size_t* max_length_ptr)
{
  return 0;
}

int read_options(const char* path, bool* allowed_bytes, size_t* min_length_ptr, size_t* max_length_ptr)
{
  xmlInitParser();
  LIBXML_TEST_VERSION

  const htmlDocPtr document = htmlParseFile(path, NULL);
  if (document == NULL) {
    PRINT_ERROR("failed to parse HTML file");
    xmlCleanupParser();
    return 1;
  }

  int result = read_bytes(document, allowed_bytes, min_length_ptr, max_length_ptr);

  xmlFreeDoc(document);
  xmlCleanupParser();

  if (result != 0) {
    return 2;
  }

  return 0;
}
