// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "ranges.h"

#include <libxml/xpath.h>
#include <stdint.h>
#include <stdlib.h>

#include "byte.h"
#include "print.h"

#define RANGE_XPATH      ".//range"
#define RANGE_FROM_XPATH ".//from"
#define RANGE_TO_XPATH   ".//to"

static inline int
  read_range_byte(const xmlDocPtr document, const xmlNodePtr range, const char* xpath, uint8_t* byte_value_ptr)
{
  const xmlXPathContextPtr xpath_context = xmlXPathNewContext(document);
  if (xpath_context == NULL) {
    PRINT_ERROR("failed to create xpath context");
    return 1;
  }

  xpath_context->node = range;

  const xmlXPathObjectPtr xpath_object = xmlXPathEvalExpression((const xmlChar*) xpath, xpath_context);
  if (xpath_object == NULL) {
    PRINTF_ERROR("failed to evaluate xpath: %s", xpath);

    xmlXPathFreeContext(xpath_context);

    return 2;
  }

  const xmlNodeSetPtr nodes = xpath_object->nodesetval;
  if (nodes->nodeNr != 1) {
    PRINTF_ERROR("failed to find single range byte, xpath: %s", xpath);

    xmlXPathFreeObject(xpath_object);
    xmlXPathFreeContext(xpath_context);

    return 3;
  }

  uint8_t byte_value;
  int     result = read_byte_value(nodes->nodeTab[0], &byte_value);

  xmlXPathFreeObject(xpath_object);
  xmlXPathFreeContext(xpath_context);

  if (result != 0) {
    return 4;
  }

  *byte_value_ptr = byte_value;

  return 0;
}

static inline int read_range_bytes(const xmlDocPtr document, const xmlNodeSetPtr nodes, bool* range_bytes_result)
{
  bool range_bytes[UINT8_MAX + 1];

  // All bytes are not found by default.
  for (size_t index = 0; index <= UINT8_MAX; index++) {
    range_bytes[index] = false;
  }

  size_t ranges_length = nodes->nodeNr;

  for (size_t index = 0; index < ranges_length; index++) {
    const xmlNodePtr range = nodes->nodeTab[index];

    uint8_t from;
    if (read_range_byte(document, range, RANGE_FROM_XPATH, &from) != 0) {
      return 1;
    }

    uint8_t to;
    if (read_range_byte(document, range, RANGE_TO_XPATH, &to) != 0) {
      return 2;
    }

    if (from > to) {
      PRINTF_ERROR("range \"from\" is greater than \"to\", from: %u, to: %u", from, to);
      return 3;
    }

    for (size_t jndex = from; jndex <= to; jndex++) {
      range_bytes[jndex] = true;
    }
  }

  for (size_t index = 0; index <= UINT8_MAX; index++) {
    range_bytes_result[index] = range_bytes[index];
  }

  return 0;
}

int read_group_range_bytes(const xmlDocPtr document, const xmlNodePtr group, bool* range_bytes)
{
  const xmlXPathContextPtr xpath_context = xmlXPathNewContext(document);
  if (xpath_context == NULL) {
    PRINT_ERROR("failed to create xpath context");
    return 1;
  }

  xpath_context->node = group;

  const xmlXPathObjectPtr xpath_object = xmlXPathEvalExpression((const xmlChar*) RANGE_XPATH, xpath_context);
  if (xpath_object == NULL) {
    PRINTF_ERROR("failed to evaluate xpath: %s", RANGE_XPATH);

    xmlXPathFreeContext(xpath_context);

    return 2;
  }

  const xmlNodeSetPtr nodes = xpath_object->nodesetval;
  if (nodes->nodeNr < 0) {
    PRINTF_ERROR("failed to find ranges, xpath: %s", RANGE_XPATH);

    xmlXPathFreeObject(xpath_object);
    xmlXPathFreeContext(xpath_context);

    return 3;
  }

  int result = read_range_bytes(document, nodes, range_bytes);

  xmlXPathFreeObject(xpath_object);
  xmlXPathFreeContext(xpath_context);

  if (result != 0) {
    return 4;
  }

  return 0;
}
