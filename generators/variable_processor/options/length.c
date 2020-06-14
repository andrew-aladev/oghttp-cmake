// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "length.h"

#include <libxml/xpath.h>
#include <string.h>

#include "print.h"

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

int read_length(const xmlDocPtr document, const char* xpath, size_t* length_ptr)
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

  xmlChar* value = xmlNodeGetContent(nodes->nodeTab[0]);
  size_t   length;

  int result = parse_length((const char*)value, &length);

  xmlFree(value);
  xmlXPathFreeObject(xpath_object);
  xmlXPathFreeContext(xpath_context);

  if (result != 0) {
    return 4;
  }

  *length_ptr = length;

  return 0;
}
