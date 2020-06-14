// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "constant.h"

#include <libxml/xpath.h>
#include <string.h>

#include "print.h"

#define CONSTANT_XPATH "//constant"

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

  xmlChar* constant = xmlNodeGetContent(nodes->nodeTab[0]);
  if (constant == NULL) {
    PRINT_ERROR("failed to get constant value");
    xmlXPathFreeObject(xpath_object);
    xmlXPathFreeContext(xpath_context);
    return 4;
  }

  char* constant_duplicate = strdup((const char*)constant);
  if (constant_duplicate == NULL) {
    PRINTF_ERROR("failed to duplicate constant value: %s", (const char*)constant);
    xmlFree(constant);
    xmlXPathFreeObject(xpath_object);
    xmlXPathFreeContext(xpath_context);
    return 5;
  }

  xmlFree(constant);
  xmlXPathFreeObject(xpath_object);
  xmlXPathFreeContext(xpath_context);

  *constant_ptr = constant_duplicate;

  return 0;
}