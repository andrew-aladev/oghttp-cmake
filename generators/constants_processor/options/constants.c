// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "constants.h"

#include <libxml/xpath.h>
#include <string.h>

#include "print.h"

#define CONSTANT_XPATH "//constant"

int read_constants(const xmlDocPtr document, char*** constants_ptr, size_t* constants_length_ptr)
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
  if (nodes->nodeNr <= 0) {
    PRINTF_ERROR("failed to find constant values, xpath: %s", CONSTANT_XPATH);
    xmlXPathFreeObject(xpath_object);
    xmlXPathFreeContext(xpath_context);
    return 3;
  }

  size_t constants_length = nodes->nodeNr;
  size_t constants_size   = constants_length * sizeof(char*);

  char** constants = malloc(constants_size);
  if (constants == NULL) {
    PRINTF_ERROR("failed to allocate memory for constants, size: %zu", constants_size);
    xmlXPathFreeObject(xpath_object);
    xmlXPathFreeContext(xpath_context);
    return 4;
  }

  for (size_t index = 0; index < constants_length; index++) {
    const char* constant = (const char*)xmlNodeGetContent(nodes->nodeTab[index]);

    char* constant_duplicate = strdup(constant);
    if (constant_duplicate == NULL) {
      PRINTF_ERROR("failed to duplicate constant value: %s", constant);
      for (size_t jndex = 0; jndex < index; jndex++) {
        free(constants[jndex]);
      }
      free(constants);
      xmlXPathFreeObject(xpath_object);
      xmlXPathFreeContext(xpath_context);
      return 5;
    }

    constants[index] = constant_duplicate;
  }

  *constants_ptr        = constants;
  *constants_length_ptr = constants_length;

  xmlXPathFreeObject(xpath_object);
  xmlXPathFreeContext(xpath_context);

  return 0;
}
