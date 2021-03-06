// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "declaration_schema.h"

#include <libxml/xmlschemas.h>

#include "config.h"
#include "macro.h"
#include "print.h"

#define SCHEMA_PATH PROCESSOR_PATH "/declaration/main.xsd"

static inline void print_error(void* UNUSED(context), const char* message, ...)
{
  PRINTF_ERROR("error: %s", message);
}

static inline void print_warning(void* UNUSED(context), const char* message, ...)
{
  PRINTF_ERROR("warning: %s", message);
}

static inline void print_structured_error(void* UNUSED(argument), xmlErrorPtr error)
{
  PRINTF_ERROR("error at line %d, column %d: %s", error->line, error->int2, error->message);
}

int validate_declaration_schema(const char* path)
{
  xmlSchemaParserCtxtPtr schema_context = xmlSchemaNewParserCtxt(SCHEMA_PATH);
  if (schema_context == NULL) {
    PRINTF_ERROR("failed to create parser for declaration schema, path: %s", SCHEMA_PATH);
    return 1;
  }

  xmlSchemaSetParserErrors(schema_context, print_error, print_warning, NULL);
  xmlSchemaSetParserStructuredErrors(schema_context, print_structured_error, NULL);

  xmlSchemaPtr schema = xmlSchemaParse(schema_context);
  if (schema == NULL) {
    PRINTF_ERROR("failed to parse declaration schema, path: %s", SCHEMA_PATH);

    xmlSchemaFreeParserCtxt(schema_context);

    return 2;
  }

  xmlSchemaValidCtxtPtr validation_context = xmlSchemaNewValidCtxt(schema);
  if (validation_context == NULL) {
    PRINTF_ERROR("failed to create validation context for declaration schema, path: %s", SCHEMA_PATH);

    xmlSchemaFree(schema);
    xmlSchemaFreeParserCtxt(schema_context);

    return 3;
  }

  xmlSchemaSetValidErrors(validation_context, print_error, print_warning, NULL);
  xmlSchemaSetValidStructuredErrors(validation_context, print_structured_error, NULL);

  int result = xmlSchemaValidateFile(validation_context, path, 0);

  xmlSchemaFreeValidCtxt(validation_context);
  xmlSchemaFree(schema);
  xmlSchemaFreeParserCtxt(schema_context);

  if (result != 0) {
    PRINTF_ERROR("failed to validate declaration schema, path: %s", SCHEMA_PATH);
    return 4;
  }

  return 0;
}
