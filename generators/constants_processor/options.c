// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "options.h"

#include <libxml/HTMLparser.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>

#include "print.h"

#define CONSTANT_XPATH "//constant"

static inline int read_constants(const htmlDocPtr document, char*** constants_ptr, size_t* constants_length_ptr)
{
  const xmlXPathContextPtr xpath_context = xmlXPathNewContext(document);
  if (xpath_context == NULL) {
    PRINT_ERROR("failed to create xpath context");
    return 1;
  }

  const xmlXPathObjectPtr xpath_object = xmlXPathEvalExpression((const xmlChar*)CONSTANT_XPATH, xpath_context);
  if (xpath_object == NULL) {
    PRINT_ERROR("failed to evaluate xpath");
    xmlXPathFreeContext(xpath_context);
    return 2;
  }

  const xmlNodeSetPtr nodes = xpath_object->nodesetval;
  if (nodes->nodeNr <= 0) {
    PRINT_ERROR("failed to find constant values");
    xmlXPathFreeObject(xpath_object);
    xmlXPathFreeContext(xpath_context);
    return 3;
  }

  size_t constants_length = nodes->nodeNr;

  char** constants = malloc(sizeof(char*) * constants_length);
  if (constants == NULL) {
    PRINT_ERROR("failed to allocate memory for constants");
    xmlXPathFreeObject(xpath_object);
    xmlXPathFreeContext(xpath_context);
    return 4;
  }

  for (size_t index = 0; index < constants_length; index++) {
    char* constant = strdup((const char*)xmlNodeGetContent(nodes->nodeTab[index]));
    if (constant == NULL) {
      PRINT_ERROR("failed to duplicate constant value");
      for (size_t jndex = 0; jndex < index; jndex++) {
        free(constants[jndex]);
      }
      free(constants);
      xmlXPathFreeObject(xpath_object);
      xmlXPathFreeContext(xpath_context);
      return 5;
    }

    constants[index] = constant;
  }

  *constants_ptr        = constants;
  *constants_length_ptr = constants_length;

  xmlXPathFreeObject(xpath_object);
  xmlXPathFreeContext(xpath_context);

  return 0;
}

int read_options(const char* path, char*** constants_ptr, size_t* constants_length_ptr)
{
  xmlInitParser();
  LIBXML_TEST_VERSION

  const htmlDocPtr document = htmlParseFile(path, NULL);
  if (document == NULL) {
    PRINT_ERROR("failed to parse HTML file");
    xmlCleanupParser();
    return 1;
  }

  int result = read_constants(document, constants_ptr, constants_length_ptr);

  xmlFreeDoc(document);
  xmlCleanupParser();

  if (result != 0) {
    result = 2;
  }

  return result;
}
