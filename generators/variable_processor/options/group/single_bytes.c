// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "single_bytes.h"

#include <libxml/xpath.h>
#include <stdint.h>
#include <stdlib.h>

#include "byte.h"
#include "print.h"

#define SINGLE_BYTE_XPATH ".//byte"

static inline int read_single_bytes(const xmlNodeSetPtr nodes, bool* single_bytes_result)
{
  bool single_bytes[UINT8_MAX + 1];

  // All bytes are not found by default.
  for (size_t index = 0; index <= UINT8_MAX; index++) {
    single_bytes[index] = false;
  }

  size_t single_bytes_length = nodes->nodeNr;

  for (size_t index = 0; index < single_bytes_length; index++) {
    uint8_t byte_value;
    if (read_byte_value(nodes->nodeTab[index], &byte_value) != 0) {
      return 1;
    }

    single_bytes[byte_value] = true;
  }

  for (size_t index = 0; index <= UINT8_MAX; index++) {
    single_bytes_result[index] = single_bytes[index];
  }

  return 0;
}

int read_group_single_bytes(const xmlDocPtr document, const xmlNodePtr group, bool* single_bytes)
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

  int result = read_single_bytes(nodes, single_bytes);

  xmlXPathFreeObject(xpath_object);
  xmlXPathFreeContext(xpath_context);

  if (result != 0) {
    return 4;
  }

  return 0;
}
