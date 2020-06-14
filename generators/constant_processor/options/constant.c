// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "constant.h"

#include <libxml/xpath.h>
#include <string.h>

#include "print.h"

#define CONSTANT_XPATH "//constant"

static inline int read_constant_value(const xmlNodePtr node, char** constant_ptr)
{
  xmlChar* constant = xmlNodeGetContent(node);
  if (constant == NULL) {
    PRINT_ERROR("failed to read constant value");
    return 1;
  }

  char* constant_duplicate = strdup((const char*)constant);
  if (constant_duplicate == NULL) {
    PRINTF_ERROR("failed to duplicate constant value: %s", (const char*)constant);
    xmlFree(constant);
    return 2;
  }

  xmlFree(constant);

  *constant_ptr = constant_duplicate;

  return 0;
}

int read_constant(const xmlDocPtr document, char** constant_ptr)
{
  const xmlXPathContextPtr xpath_context = xmlXPathNewContext(document);
  if (xpath_context == NULL) {
    PRINT_ERROR("failed to create xpath context");
    return 1;
  }

  const xmlXPathObjectPtr xpath_object = xmlXPathEvalExpression((const xmlChar*)CONSTANT_XPATH, xpath_context);
  if (xpath_object == NULL) {
    PRINTF_ERROR("failed to evaluate xpath: %s", CONSTANT_XPATH);
    xmlXPathFreeContext(xpath_context);
    return 2;
  }

  const xmlNodeSetPtr nodes = xpath_object->nodesetval;
  if (nodes->nodeNr != 1) {
    PRINTF_ERROR("failed to find single constant value, xpath: %s", CONSTANT_XPATH);
    xmlXPathFreeObject(xpath_object);
    xmlXPathFreeContext(xpath_context);
    return 3;
  }

  char* constant;
  int   result = read_constant_value(nodes->nodeTab[0], &constant);

  xmlXPathFreeObject(xpath_object);
  xmlXPathFreeContext(xpath_context);

  if (result != 0) {
    return 4;
  }

  *constant_ptr = constant;

  return 0;
}
