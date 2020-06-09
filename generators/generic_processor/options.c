// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "options.h"

#include <libxml/HTMLparser.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>

#include "print.h"

#define MIN_LENGTH_XPATH "//min-length"
#define MAX_LENGTH_XPATH "//max-length"

static inline int parse_length(const char* value, size_t* length_ptr)
{
  if (sscanf(value, "%zu", length_ptr) == 1) {
    return 0;
  }

  if (sscanf(value, "0x%zx", length_ptr) == 1) {
    return 0;
  }

  PRINTF_ERROR("failed to parse length, value: %s", value);
  return 1;
}

static inline int read_length(const htmlDocPtr document, const char* xpath, size_t* length_ptr)
{
  const xmlXPathContextPtr xpath_context = xmlXPathNewContext(document);
  if (xpath_context == NULL) {
    PRINT_ERROR("failed to create xpath context");
    return 1;
  }

  const xmlXPathObjectPtr xpath_object = xmlXPathEvalExpression((const xmlChar*)xpath, xpath_context);
  if (xpath_object == NULL) {
    PRINTF_ERROR("failed to evaluate xpath: %s", xpath);
    xmlXPathFreeContext(xpath_context);
    return 2;
  }

  const xmlNodeSetPtr nodes = xpath_object->nodesetval;
  if (nodes->nodeNr != 1) {
    PRINTF_ERROR("failed to find single length value, xpath: %s", xpath);
    xmlXPathFreeObject(xpath_object);
    xmlXPathFreeContext(xpath_context);
    return 3;
  }

  const char* value = (const char*)xmlNodeGetContent(nodes->nodeTab[0]);
  size_t      length;

  int result = parse_length(value, &length);

  xmlXPathFreeObject(xpath_object);
  xmlXPathFreeContext(xpath_context);

  if (result != 0) {
    return 4;
  }

  *length_ptr = length;

  return 0;
}

static inline int read_data(const htmlDocPtr document, bool* allowed_bytes, size_t* min_length_ptr, size_t* max_length_ptr)
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

  const htmlDocPtr document = htmlParseFile(path, NULL);
  if (document == NULL) {
    PRINTF_ERROR("failed to parse HTML file, path: %s", path);
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
