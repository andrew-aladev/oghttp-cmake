// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "options_schema.h"

#include <libxml/xmlschemas.h>

#include "config.h"
#include "macro.h"
#include "print.h"

#define SCHEMA_PATH PROCESSOR_PATH "/options.xsd"

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

int validate_options_schema(const char* path)
{
  xmlSchemaParserCtxtPtr schema_context = xmlSchemaNewParserCtxt(SCHEMA_PATH);
  if (schema_context == NULL) {
    PRINT_ERROR("failed to create parser for options schema");
    return 1;
  }

  xmlSchemaSetParserErrors(schema_context, print_error, print_warning, NULL);
  xmlSchemaSetParserStructuredErrors(schema_context, print_structured_error, NULL);

  xmlSchemaPtr schema = xmlSchemaParse(schema_context);
  if (schema == NULL) {
    PRINT_ERROR("failed to parse options schema");
    xmlSchemaFreeParserCtxt(schema_context);
    return 2;
  }

  xmlSchemaValidCtxtPtr validation_context = xmlSchemaNewValidCtxt(schema);
  if (validation_context == NULL) {
    PRINT_ERROR("failed to create validation context for options schema");
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
    PRINT_ERROR("failed to validate options schema");
    return 4;
  }

  return 0;
}
