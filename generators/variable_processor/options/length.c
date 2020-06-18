// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "length.h"

#include <libxml/xpath.h>
#include <string.h>

#include "print.h"

static inline int read_length_value(const xmlNodePtr node, size_t* length_ptr)
{
  xmlChar* value = xmlNodeGetContent(node);
  if (value == NULL) {
    PRINT_ERROR("failed to read length value");
    return 1;
  }

  if (sscanf((const char*)value, "%zu", length_ptr) == 1) {
    xmlFree(value);

    return 0;
  }

  if (sscanf((const char*)value, "0x%zx", length_ptr) == 1) {
    xmlFree(value);

    return 0;
  }

  PRINTF_ERROR("failed to read length, value: %s", (const char*)value);

  xmlFree(value);

  return 2;
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

  size_t length;
  int    result = read_length_value(nodes->nodeTab[0], &length);

  xmlXPathFreeObject(xpath_object);
  xmlXPathFreeContext(xpath_context);

  if (result != 0) {
    return 4;
  }

  *length_ptr = length;

  return 0;
}
