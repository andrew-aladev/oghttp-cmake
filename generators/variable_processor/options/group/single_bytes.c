// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "single_bytes.h"

#include <libxml/xpath.h>
#include <stdint.h>
#include <stdlib.h>

#include "print.h"

#define SINGLE_BYTE_XPATH ".//byte"

static inline int read_group_single_byte_values(const xmlNodeSetPtr nodes, bool* group_bytes)
{
  xmlChar* value = xmlNodeGetContent(node);
  if (value == NULL) {
    PRINT_ERROR("failed to read byte value");
    return 1;
  }

  xmlFree(value);

  return 0;
}

int read_group_single_bytes(const xmlNodePtr group, bool* group_bytes_result)
{
  const xmlXPathContextPtr xpath_context = xmlXPathNewContext(document);
  if (xpath_context == NULL) {
    PRINT_ERROR("failed to create xpath context");
    return 1;
  }

  xpath_context->node = group;

  const xmlXPathObjectPtr xpath_object = xmlXPathEvalExpression((const xmlChar*)SINGLE_BYTE_XPATH, xpath_context);
  if (xpath_object == NULL) {
    PRINTF_ERROR("failed to evaluate xpath: %s", SINGLE_BYTE_XPATH);
    xmlXPathFreeContext(xpath_context);
    return 2;
  }

  const xmlNodeSetPtr nodes = xpath_object->nodesetval;
  if (nodes->nodeNr < 0) {
    PRINTF_ERROR("failed to find single bytes, xpath: %s", SINGLE_BYTE_XPATH);
    xmlXPathFreeObject(xpath_object);
    xmlXPathFreeContext(xpath_context);
    return 3;
  }

  bool group_bytes[UINT8_MAX];
  int  result = read_group_single_byte_values(nodes, group_bytes);

  xmlXPathFreeObject(xpath_object);
  xmlXPathFreeContext(xpath_context);

  if (result != 0) {
    return 4;
  }

  for (size_t index = 0; index < UINT8_MAX; index++) {
    group_bytes_result[index] = group_bytes[index];
  }

  return 0;
}
