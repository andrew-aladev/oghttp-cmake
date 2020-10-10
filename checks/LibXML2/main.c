// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include <assert.h>
#include <libxml/HTMLparser.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>

const char DATA[] =
  "<!DOCTYPE html>\
    <html>\
      <body>\
        <span key=\"value\">text</span>\
      </body>\
    </html>";

const char XPATH[]           = "//span";
const char ATTRIBUTE_KEY[]   = "key";
const char ATTRIBUTE_VALUE[] = "value";
const char TEXT[]            = "text";

int main()
{
  xmlInitParser();
  LIBXML_TEST_VERSION

  const htmlDocPtr document = htmlParseDoc((const xmlChar*) DATA, NULL);
  assert(document != NULL);

  const xmlXPathContextPtr xpath_context = xmlXPathNewContext(document);
  assert(xpath_context != NULL);

  const xmlXPathObjectPtr xpath = xmlXPathEvalExpression((const xmlChar*) XPATH, xpath_context);
  assert(xpath != NULL);

  const xmlNodeSetPtr nodes = xpath->nodesetval;
  assert(nodes->nodeNr == 1);

  const xmlNodePtr node = nodes->nodeTab[0];
  assert(node != NULL);

  const xmlAttrPtr attribute = xmlHasProp(node, (const xmlChar*) ATTRIBUTE_KEY);
  assert(attribute != NULL);

  const char* attribute_value = (const char*) xmlGetProp(node, (const xmlChar*) ATTRIBUTE_KEY);
  assert(attribute_value != NULL);
  assert(strcmp(attribute_value, ATTRIBUTE_VALUE) == 0);

  xmlChar* text = xmlNodeGetContent(node);
  assert(text != NULL);
  assert(strcmp((const char*) text, TEXT) == 0);

  xmlFree(text);
  xmlXPathFreeObject(xpath);
  xmlXPathFreeContext(xpath_context);
  xmlFreeDoc(document);
  xmlCleanupParser();

  return 0;
}
