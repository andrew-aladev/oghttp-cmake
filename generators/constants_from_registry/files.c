// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "files.h"

#include <libxml/HTMLparser.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>

#include "constants.h"
#include "print.h"

static inline int process_file(const char* file_path, const char* xpath, bool is_first_file)
{
  xmlInitParser();
  LIBXML_TEST_VERSION

  const htmlDocPtr document = htmlParseFile(file_path, NULL);
  if (document == NULL) {
    PRINTF_ERROR("failed to parse HTML file, path: %s", file_path);
    xmlCleanupParser();
    return 1;
  }

  const xmlXPathContextPtr xpath_context = xmlXPathNewContext(document);
  if (xpath_context == NULL) {
    PRINT_ERROR("failed to create xpath context");
    xmlFreeDoc(document);
    xmlCleanupParser();
    return 2;
  }

  const xmlXPathObjectPtr xpath_object = xmlXPathEvalExpression((const xmlChar*)xpath, xpath_context);
  if (xpath_object == NULL) {
    PRINTF_ERROR("failed to create xpath: %s", xpath);
    xmlXPathFreeContext(xpath_context);
    xmlFreeDoc(document);
    xmlCleanupParser();
    return 3;
  }

  const xmlNodeSetPtr nodes = xpath_object->nodesetval;

  int result = print_constants(nodes, nodes->nodeNr, is_first_file);

  xmlXPathFreeObject(xpath_object);
  xmlXPathFreeContext(xpath_context);
  xmlFreeDoc(document);
  xmlCleanupParser();

  if (result != 0) {
    return 4;
  }

  return 0;
}

int process_files(const char** file_datas, size_t file_datas_length)
{
  int result;

  for (size_t index = 0; index + 1 < file_datas_length; index += 2) {
    result = process_file(file_datas[index], file_datas[index + 1], index == 0);
    if (result != 0) {
      return result;
    }
  }

  return 0;
}
