// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(DECLARATION_CONSTANT_H)
#define DECLARATION_CONSTANT_H

#include <libxml/parser.h>

int read_constant(const xmlDocPtr document, char** constant_ptr);

#endif // DECLARATION_CONSTANT_H
