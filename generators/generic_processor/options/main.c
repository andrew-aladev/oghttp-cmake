// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "main.h"

#include <string.h>

#include "length.h"
#include "print.h"

#define MIN_LENGTH_XPATH "//min-length"
#define MAX_LENGTH_XPATH "//max-length"

static inline int read_data(const xmlDocPtr document, bool* allowed_bytes, size_t* min_length_ptr, size_t* max_length_ptr)
{
  size_t min_length;
  if (read_length(document, MIN_LENGTH_XPATH, &min_length) != 0) {
    return 1;
  }

  size_t max_length;
  if (read_length(document, MAX_LENGTH_XPATH, &max_length) != 0) {
    return 2;
  }

  allowed_bytes[0] = 0;

  *min_length_ptr = min_length;
  *max_length_ptr = max_length;

  return 0;
}

int read_options(const char* path, bool* allowed_bytes, size_t* min_length_ptr, size_t* max_length_ptr)
{
  xmlInitParser();
  LIBXML_TEST_VERSION

  const xmlDocPtr document = xmlParseFile(path);
  if (document == NULL) {
    PRINTF_ERROR("failed to parse XML file, path: %s", path);
    xmlCleanupParser();
    return 1;
  }

  int result = read_data(document, allowed_bytes, min_length_ptr, max_length_ptr);

  xmlFreeDoc(document);
  xmlCleanupParser();

  if (result != 0) {
    return 2;
  }

  return 0;
}
