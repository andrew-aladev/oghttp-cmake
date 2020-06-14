// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "groups.h"

#include <libxml/xpath.h>
#include <stdint.h>
#include <string.h>

#include "print.h"

#define GROUP_XPATH "//group"

enum {
  GROUP_MODE_INCLUDE,
  GROUP_MODE_EXCLUDE
};
typedef uint8_t group_mode_t;

static inline int read_group_mode(const xmlNodePtr group, group_mode_t* group_mode_ptr)
{
  xmlChar* value = xmlGetProp(group, (const xmlChar*)"mode");
  if (value == NULL) {
    PRINT_ERROR("failed to read group mode property");
    return 1;
  }

  if (strcmp((const char*)value, "include") == 0) {
    *group_mode_ptr = GROUP_MODE_INCLUDE;
  }
  else {
    *group_mode_ptr = GROUP_MODE_EXCLUDE;
  }

  xmlFree(value);

  return 0;
}

int read_groups(const xmlDocPtr document, bool* allowed_bytes_result)
{
  const xmlXPathContextPtr xpath_context = xmlXPathNewContext(document);
  if (xpath_context == NULL) {
    PRINT_ERROR("failed to create xpath context");
    return 1;
  }

  const xmlXPathObjectPtr xpath_object = xmlXPathEvalExpression((const xmlChar*)GROUP_XPATH, xpath_context);
  if (xpath_object == NULL) {
    PRINTF_ERROR("failed to evaluate xpath: %s", GROUP_XPATH);
    xmlXPathFreeContext(xpath_context);
    return 2;
  }

  const xmlNodeSetPtr nodes = xpath_object->nodesetval;
  if (nodes->nodeNr <= 0) {
    PRINTF_ERROR("failed to find groups, xpath: %s", GROUP_XPATH);
    xmlXPathFreeObject(xpath_object);
    xmlXPathFreeContext(xpath_context);
    return 3;
  }

  bool   allowed_bytes[UINT8_MAX];
  size_t groups_length = nodes->nodeNr;

  for (size_t index = 0; index < groups_length; index++) {
    const xmlNodePtr group = nodes->nodeTab[index];

    group_mode_t group_mode;
    if (read_group_mode(group, &group_mode) != 0) {
      xmlXPathFreeObject(xpath_object);
      xmlXPathFreeContext(xpath_context);
      return 4;
    }
  }

  xmlXPathFreeObject(xpath_object);
  xmlXPathFreeContext(xpath_context);

  for (size_t index = 0; index < UINT8_MAX; index++) {
    allowed_bytes_result[index] = allowed_bytes[index];
  }

  return 0;
}
