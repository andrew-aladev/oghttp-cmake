// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "constants.h"

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

  char* constant_duplicate = strdup((const char*) constant);
  if (constant_duplicate == NULL) {
    PRINTF_ERROR("failed to duplicate constant value: %s", (const char*) constant);

    xmlFree(constant);

    return 2;
  }

  xmlFree(constant);

  *constant_ptr = constant_duplicate;

  return 0;
}

static inline int read_constant_values(const xmlNodeSetPtr nodes, char*** constants_ptr, size_t* constants_length_ptr)
{
  size_t constants_length = nodes->nodeNr;
  size_t constants_size   = constants_length * sizeof(char*);

  char** constants = malloc(constants_size);
  if (constants == NULL) {
    PRINTF_ERROR("failed to allocate memory for constants, size: %zu", constants_size);
    return 1;
  }

  for (size_t index = 0; index < constants_length; index++) {
    char* constant;
    if (read_constant_value(nodes->nodeTab[index], &constant) != 0) {
      for (size_t jndex = 0; jndex < index; jndex++) {
        free(constants[jndex]);
      }
      free(constants);

      return 2;
    }

    constants[index] = constant;
  }

  *constants_ptr        = constants;
  *constants_length_ptr = constants_length;

  return 0;
}

int read_constants(const xmlDocPtr document, char*** constants_ptr, size_t* constants_length_ptr)
{
  const xmlXPathContextPtr xpath_context = xmlXPathNewContext(document);
  if (xpath_context == NULL) {
    PRINT_ERROR("failed to create xpath context");
    return 1;
  }

  const xmlXPathObjectPtr xpath_object = xmlXPathEvalExpression((const xmlChar*) CONSTANT_XPATH, xpath_context);
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

  char** constants;
  size_t constants_length;
  int    result = read_constant_values(nodes, &constants, &constants_length);

  xmlXPathFreeObject(xpath_object);
  xmlXPathFreeContext(xpath_context);

  if (result != 0) {
    return 4;
  }

  *constants_ptr        = constants;
  *constants_length_ptr = constants_length;

  return 0;
}
