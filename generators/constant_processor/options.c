// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "options.h"

#include <libxml/HTMLparser.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>

#define CONSTANT_XPATH "/constant"

static inline int read_constant(const htmlDocPtr document, const char** constant_ptr)
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
  if (nodes->nodeNr != 1) {
    PRINT_ERROR("invalid constant value");
    xmlXPathFreeObject(xpath_object);
    xmlXPathFreeContext(xpath_context);
    return 3;
  }

  const char* constant = strdup((const char*)xmlNodeGetContent(nodes->nodeTab[0]));
  if (constant == NULL) {
    PRINT_ERROR("failed to duplicate constant value");
    xmlXPathFreeObject(xpath_object);
    xmlXPathFreeContext(xpath_context);
    return 4;
  }

  *constant_ptr = constant;

  xmlXPathFreeObject(xpath_object);
  xmlXPathFreeContext(xpath_context);

  return 0;
}

int read_options(const char* path, const char** constant_ptr)
{
  xmlInitParser();
  LIBXML_TEST_VERSION

  const htmlDocPtr document = htmlParseFile(path, NULL);
  if (document == NULL) {
    PRINT_ERROR("failed to parse HTML file");
    xmlCleanupParser();
    return 1;
  }

  int result = read_constant(document, constant_ptr);

  xmlFreeDoc(document);
  xmlCleanupParser();

  if (result != 0) {
    result = 2;
  }

  return result;
}
